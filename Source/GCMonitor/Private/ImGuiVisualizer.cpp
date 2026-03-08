// Fill out your copyright notice in the Description page of Project Settings.


#include "ImGuiVisualizer.h"
#include "HolderActor.h"
#include "Subject.h"
#include "TrackingSubsystem.h"

namespace
{

// 格納先の種類を表す列挙型
// ImGuiプルダウン選択肢で使用する想定なため、const char*配列を使用。
const char* StorageLocationNames[static_cast<int32>(EStorageLocation::Num)] = {
    "TObjectPtr<USubject>",
    "USubject*",
    "TWeakObjectPtr<USubject>",
    "TArray<TObjectPtr<USubject>>",
    "TArray<USubject*>",
    "TArray<TWeakObjectPtr<USubject>>",
    "TMap<int32, TObjectPtr<USubject>>",
    "TMap<int32, USubject*>",
    "TMap<int32, TWeakObjectPtr<USubject>>",
};

};

// Sets default values
AImGuiVisualizer::AImGuiVisualizer()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void AImGuiVisualizer::BeginPlay()
{
	Super::BeginPlay();

	// ImGuiTick関数をOnWorldDebugデリゲートにバインド
	FImGuiDelegates::OnWorldDebug().AddUObject(this, &AImGuiVisualizer::ImGuiTick);

	// ImGuiの入力モードを有効化
	FImGuiModule& ImGuiModule = FImGuiModule::Get();
	ImGuiModule.SetInputMode(true);

    // 格納先オブジェクト作成
    HolderActor = GetWorld()->SpawnActor<AHolderActor>();
}

/** アクター終了時またはレベル遷移時に呼び出され、ImGui Tickデリゲートを解除する */
void AImGuiVisualizer::EndPlay(const EEndPlayReason::Type EndPlayReason)
{
	Super::EndPlay(EndPlayReason);

	// ImGuiTick関数をOnWorldDebugデリゲートから解除
	FImGuiDelegates::OnWorldDebug().RemoveAll(this);

	// ImGuiの入力モードを無効化
	FImGuiModule& ImGuiModule = FImGuiModule::Get();
	ImGuiModule.SetInputMode(false);
}


/** ImGui描画用Tick関数。ImGuiのUI表示・テスト制御を行う */
void AImGuiVisualizer::ImGuiTick()
{
    // UObject生成テスト用ウィンドウの描画
    DrawUObjectGenerationTestWindow();

    // GC操作ウィンドウの描画
    DrawGCControlWindow();

    // AActorHolder情報ウィンドウの描画
    DrawAActorHolderReferenceWindow();

    // UObjectリストウィンドウの描画
    DrawUObjectListWindow();

    // ログウィンドウの描画
    DrawLogWindow();
}

/// <summary>
/// UObject生成テスト用ウィンドウの描画
/// </summary>
void AImGuiVisualizer::DrawUObjectGenerationTestWindow()
{
    // 継承タイプ選択用の静的変数
    static int SelectedInheritanceType = 0;
    // 格納先選択用の静的変数
    static int SelectedTarget = 0;
    // GC保護の有無選択用の静的変数
    static bool bIsGCProtected = true;
    // 生成数選択用の静的変数
    static int GenerateCount = 1;

    ImGui::SetNextWindowPos(ImVec2(20, 20), ImGuiCond_FirstUseEver);
    ImGui::SetNextWindowSize(ImVec2(350, 170), ImGuiCond_FirstUseEver);
    ImGui::Begin("USubject操作");
    ImGui::Checkbox("UPROPERTY付与", &bIsGCProtected);
    ImGui::Combo("格納先メンバ", &SelectedTarget, StorageLocationNames, IM_ARRAYSIZE(StorageLocationNames));
    ImGui::SliderInt("生成数", &GenerateCount, 1, 10);
    if (ImGui::Button("生成実行！", ImVec2(-1, 0)))
    {
        HolderActor->GenerateSubject(static_cast<EStorageLocation>(SelectedTarget), bIsGCProtected, GenerateCount);
    }

    ImGui::Separator();

    if(ImGui::Button("nullptr代入", ImVec2(-1, 0)))
    {
        HolderActor->TrySetNullptrToAllSubjects();
    }
    if (ImGui::Button("Reset/Empty呼び出し", ImVec2(-1, 0)))
    {
        HolderActor->TyyResetToAllSubjects();
    }

    ImGui::End();
}

/// <summary>
/// AActorHolder情報ウィンドウの描画
/// </summary>
void AImGuiVisualizer::DrawAActorHolderReferenceWindow()
{
    ImGui::SetNextWindowSize(ImVec2(500, 150), ImGuiCond_FirstUseEver);
    ImGui::Begin("AHolderActor（格納先クラス）詳細");
    if (HolderActor == nullptr)
    {
        ImGui::TextColored(ImVec4(1, 0.5f, 0.5f, 1), "AHolderActor is nullptr.");
        ImGui::End();
        return;
    }

    static bool bSafeMode = false;
    ImGui::Checkbox("セーフモード", &bSafeMode);

    // テーブルセットアップ用ラムダ関数
    // インデックス、オブジェクト、UPROPERTY有無、格納先名を受け取り、1行描画する
    auto EasyTableSetup = [&](const int32 InIndex, UObject* InObject, bool bProperty, const char* InStorageName){
        ImGui::TableSetColumnIndex(0);
        if (InIndex == 0) {
            if (bProperty) {
                ImGui::TextColored(ImVec4(0, 1, 0, 1), "UPROPERTY()");
                ImGui::TextColored(ImVec4(0, 1, 0, 1), InStorageName);
            }
            else {
                ImGui::TextColored(ImVec4(1, 0, 0, 1), "No UPROPERTY()");
                ImGui::TextColored(ImVec4(1, 0, 0, 1), InStorageName);
            }
        }
        ImGui::TableSetColumnIndex(1);
        ImGui::Text("%d", InIndex);
        DrawObjectTableRow(InObject, 2, bSafeMode);
        ImGui::TableNextRow();
    };

    if (ImGui::BeginTable("ObjectTable", 6, ImGuiTableFlags_Borders | ImGuiTableFlags_Resizable | ImGuiTableFlags_RowBg | ImGuiTableFlags_ScrollY | ImGuiTableFlags_ScrollX))
    {
        // テーブルヘッダー
        ImGui::TableSetupColumn("Storage",      ImGuiTableColumnFlags_WidthFixed, 250.0f);
        ImGui::TableSetupColumn("Index",        ImGuiTableColumnFlags_WidthFixed,  70.0f);
        ImGui::TableSetupColumn("Address",      ImGuiTableColumnFlags_WidthFixed, 130.0f); 
        ImGui::TableSetupColumn("Name",         ImGuiTableColumnFlags_WidthFixed, 130.0f);
        ImGui::TableSetupColumn("GCStatus",     ImGuiTableColumnFlags_WidthFixed, 150.0f);
        ImGui::TableSetupColumn("EObjectFlags", ImGuiTableColumnFlags_WidthFixed, 150.0f);
        ImGui::TableHeadersRow();
        ImGui::TableNextRow();

        // UPROPERTY()付き格納先
        EasyTableSetup(0, HolderActor->GetSafeSubjectPtr().Get(),   true, StorageLocationNames[static_cast<int32>(EStorageLocation::Ptr)]);
        EasyTableSetup(0, HolderActor->GetSafeSubjectRaw(),         true, StorageLocationNames[static_cast<int32>(EStorageLocation::Raw)]);
        EasyTableSetup(0, HolderActor->GetSafeSubjectWeak().Get(),  true, StorageLocationNames[static_cast<int32>(EStorageLocation::Weak)]);
        // 配列（TObjectPtr）
        for (int32 i = 0; i < HolderActor->GetSafeSubjectPtrArray().Num(); ++i) {
            EasyTableSetup(i, HolderActor->GetSafeSubjectPtrArray()[i].Get(), true, StorageLocationNames[static_cast<int32>(EStorageLocation::PtrArray)]);
        }
        // 配列（Raw）
        for (int32 i = 0; i < HolderActor->GetSafeSubjectRawArray().Num(); ++i) {
            EasyTableSetup(i, HolderActor->GetSafeSubjectRawArray()[i], true, StorageLocationNames[static_cast<int32>(EStorageLocation::RawArray)]);
        }
        // 配列（Weak）
        for (int32 i = 0; i < HolderActor->GetSafeSubjectWeakArray().Num(); ++i) {
            EasyTableSetup(i, HolderActor->GetSafeSubjectWeakArray()[i].Get(), true, StorageLocationNames[static_cast<int32>(EStorageLocation::WeakArray)]);
        }
        // マップ（TObjectPtr）
        for (const auto& Pair : HolderActor->GetSafeSubjectPtrMap()) {
            EasyTableSetup(Pair.Key, Pair.Value.Get(), true, StorageLocationNames[static_cast<int32>(EStorageLocation::PtrMap)]);
        }
        // マップ（Raw）
        for (const auto& Pair : HolderActor->GetSafeSubjectRawMap()) {
            EasyTableSetup(Pair.Key, Pair.Value, true, StorageLocationNames[static_cast<int32>(EStorageLocation::RawMap)]);
        }
        // マップ（Weak）
        for (const auto& Pair : HolderActor->GetSafeSubjectWeakMap()) {
            EasyTableSetup(Pair.Key, Pair.Value.Get(), true, StorageLocationNames[static_cast<int32>(EStorageLocation::WeakMap)]);
        }

        // 非UPROPERTY()格納先
        EasyTableSetup(0, HolderActor->GetUnSafeSubjectPtr().Get(),   false, StorageLocationNames[static_cast<int32>(EStorageLocation::Ptr)]);
        EasyTableSetup(0, HolderActor->GetUnSafeSubjectRaw(),         false, StorageLocationNames[static_cast<int32>(EStorageLocation::Raw)]);
        EasyTableSetup(0, HolderActor->GetUnSafeSubjectWeak().Get(),  false, StorageLocationNames[static_cast<int32>(EStorageLocation::Weak)]);

        // 配列（TObjectPtr, 非UPROPERTY）
        for (int32 i = 0; i < HolderActor->GetUnSafeSubjectPtrArray().Num(); ++i) {
            EasyTableSetup(i, HolderActor->GetUnSafeSubjectPtrArray()[i].Get(), false, StorageLocationNames[static_cast<int32>(EStorageLocation::PtrArray)]);
        }
        // 配列（Raw, 非UPROPERTY）
        for (int32 i = 0; i < HolderActor->GetUnSafeSubjectRawArray().Num(); ++i) {
            EasyTableSetup(i, HolderActor->GetUnSafeSubjectRawArray()[i], false, StorageLocationNames[static_cast<int32>(EStorageLocation::RawArray)]);
        }
        // 配列（Weak, 非UPROPERTY）
        for (int32 i = 0; i < HolderActor->GetUnSafeSubjectWeakArray().Num(); ++i) {
            EasyTableSetup(i, HolderActor->GetUnSafeSubjectWeakArray()[i].Get(), false, StorageLocationNames[static_cast<int32>(EStorageLocation::WeakArray)]);
        }

        // マップ（TObjectPtr, 非UPROPERTY）
        for (const auto& Pair : HolderActor->GetUnSafeSubjectPtrMap()) {
            EasyTableSetup(Pair.Key, Pair.Value.Get(), false, StorageLocationNames[static_cast<int32>(EStorageLocation::PtrMap)]);
        }
        // マップ（Raw, 非UPROPERTY）
        for (const auto& Pair : HolderActor->GetUnSafeSubjectRawMap()) {
            EasyTableSetup(Pair.Key, Pair.Value, false, StorageLocationNames[static_cast<int32>(EStorageLocation::RawMap)]);
        }
        // マップ（Weak, 非UPROPERTY）
        for (const auto& Pair : HolderActor->GetUnSafeSubjectWeakMap()) {
            EasyTableSetup(Pair.Key, Pair.Value.Get(), false, StorageLocationNames[static_cast<int32>(EStorageLocation::WeakMap)]);
        }

        ImGui::EndTable();
    }
    ImGui::End();
}

/// <summary>
/// GC操作ウィンドウの描画
/// </summary>
void AImGuiVisualizer::DrawGCControlWindow()
{
    // ウィンドウの開始
    if (!ImGui::Begin("UE5 GC Controller"))
    {
        ImGui::End();
        return;
    }

    // --- 1. エンジンステータス (ReadOnly) ---
    ImGui::TextColored(ImVec4(0.2f, 0.8f, 1.0f, 1.0f), "--- Engine Status ---");

    // インクリメンタルGC（分割実行）の待機状態
    const bool bIsPending = IsIncrementalPurgePending();
    ImGui::Text("Incremental Purge Pending: %s", bIsPending ? "YES" : "No");

    // コンソール変数からGCの間隔（秒）を取得
    static IConsoleVariable* CVarTimeBetween = IConsoleManager::Get().FindConsoleVariable(TEXT("gc.TimeBetweenPurging"));
    if (CVarTimeBetween)
    {
        ImGui::Text("Auto GC Interval: %.1f sec", CVarTimeBetween->GetFloat());
    }

    ImGui::Spacing();
    ImGui::Separator();
    ImGui::Spacing();

    // --- 2. GC操作 (Actions) ---
    ImGui::TextColored(ImVec4(1.0f, 0.8f, 0.2f, 1.0f), "--- Operations ---");

    // フルパージ使用の有無を選択する
    static bool bFullPurge = false;
    ImGui::Checkbox("フルパージ（徹底的に到達可能性分析）", &bFullPurge);

    ImGui::PushStyleColor(ImGuiCol_Button, ImVec4(0.6f, 0.1f, 0.1f, 1.0f));
    ImGui::PushStyleColor(ImGuiCol_ButtonHovered, ImVec4(0.8f, 0.2f, 0.2f, 1.0f));

    // 強制GCボタン
    if (ImGui::Button("GC 実行！", ImVec2(-1, 45)))
    {
        // エンジンに対してGCを強制。bFullPurgeがtrueなら到達可能性を再計算して完全にクリアする
        GEngine->ForceGarbageCollection(bFullPurge);
    }

    ImGui::PopStyleColor(2);

    ImGui::End();
}

/// <summary>
/// UObjectリストウィンドウの描画
/// </summary>
void AImGuiVisualizer::DrawUObjectListWindow()
{
    ImGui::SetNextWindowSize(ImVec2(600, 400), ImGuiCond_FirstUseEver);

    ImGui::Begin("UObjectリスト");

    static bool bIsActive = false;
    ImGui::Checkbox("全てのObject表示", &bIsActive);

    // テーブル構成: 3列 (Name, Address, GC Flags)
    if (ImGui::BeginTable("ObjectTable", 5, ImGuiTableFlags_Borders | ImGuiTableFlags_RowBg | ImGuiTableFlags_Resizable | ImGuiTableFlags_ScrollY))
    {
        // ヘッダーの設定
        ImGui::TableSetupColumn("Index", ImGuiTableColumnFlags_WidthFixed, 70.0f);
        ImGui::TableSetupColumn("Address", ImGuiTableColumnFlags_WidthFixed, 130.0f);
        ImGui::TableSetupColumn("Name", ImGuiTableColumnFlags_WidthFixed, 130.0f);
        ImGui::TableSetupColumn("GCStatus", ImGuiTableColumnFlags_WidthFixed, 150.0f);
        ImGui::TableSetupColumn("EObjectFlags", ImGuiTableColumnFlags_WidthFixed, 150.0f);
        ImGui::TableHeadersRow();
        ImGui::TableNextRow();


        for (TObjectIterator<UObject> It; It; ++It)
        {
            UObject* Object = *It;

            // 監視対象オブジェクト以外はスキップ
            if (!bIsActive)
            {
                USubject* CheckObject = Cast<USubject>(Object);
                if (!CheckObject) {
                    continue;
                }
            }
            
            ImGui::TableSetColumnIndex(0);
            ImGui::Text("%d", It.GetIndex());
            DrawObjectTableRow(Object, 1, false/*No SafeMode*/);
            ImGui::TableNextRow();
        }
        ImGui::EndTable();
    }
    ImGui::End();
}

/// <summary>
/// ログウィンドウの描画
/// </summary>
void AImGuiVisualizer::DrawLogWindow()
{
    ImGui::SetNextWindowSize(ImVec2(500, 300), ImGuiCond_FirstUseEver);
    if (!ImGui::Begin("Object Test Log"))
    {
        ImGui::End();
        return;
    }

    // --- 上部操作エリア ---
    if (ImGui::Button("Clear")) {
        if (GEngine)
        {
            if (UTrackingSubsystem* Tracking = GEngine->GetEngineSubsystem<UTrackingSubsystem>())
            {
                Tracking->ClearLogs();
            }
        }
    }
    ImGui::SameLine();
    static bool AutoScroll = true;
    ImGui::Checkbox("Auto-scroll", &AutoScroll);

    ImGui::Separator();

    // --- ログ表示エリア ---
    ImGui::BeginChild("ScrollingRegion", ImVec2(0, 0), false, ImGuiWindowFlags_HorizontalScrollbar);

    if (GEngine)
    {
        if (UTrackingSubsystem* Tracking = GEngine->GetEngineSubsystem<UTrackingSubsystem>())
        {
            for (const auto& LogEntry : Tracking->GetLogEntries())
            {
                ImGui::Text("%s [%d - %s] : %s", TCHAR_TO_UTF8(*LogEntry.Timestamp), LogEntry.SubjectId, TCHAR_TO_UTF8(*LogEntry.SubjectName), TCHAR_TO_UTF8(*LogEntry.EventMessage));
            }
        }
    }

    // ログが追加されたときに自動で一番下までスクロール
    if (AutoScroll && ImGui::GetScrollY() >= ImGui::GetScrollMaxY())
    {
        ImGui::SetScrollHereY(1.0f);
    }

    ImGui::EndChild();
    ImGui::End();
}

/// <summary>
/// ImGuiのテーブルにUObjectの情報を1行描画するユーティリティ関数
/// かなり限定的な機能のため、使用には注意。
/// </summary>
/// <param name="InObject">対象のオブジェクトポインタ</param>
/// <param name="InRowIndex">先頭のカラム数</param>
/// <param name="InSafeMode">セーフモード指定</param>
void AImGuiVisualizer::DrawObjectTableRow(UObject* InObject,const int32 InRowIndex, const bool InSafeMode)
{
    if (InObject == nullptr)
    {
        int32 RowIndexCounter = InRowIndex;
        ImGui::TableSetColumnIndex(RowIndexCounter++);
        ImGui::Text("00000000");
        ImGui::TableSetColumnIndex(RowIndexCounter++);
        ImGui::Text("");
        ImGui::TableSetColumnIndex(RowIndexCounter++);
        ImGui::Text("");
        ImGui::TableSetColumnIndex(RowIndexCounter++);
        ImGui::Text("");
        return;
    }

    if(InSafeMode)
    {
        // セーフモードの場合、アドレスのみ表示する（安全のため）。その他の情報は空欄にする。
        int32 RowIndexCounter = InRowIndex;
        ImGui::TableSetColumnIndex(RowIndexCounter++);
        const auto AddressStr = FString::Printf(TEXT("%p"), InObject);
        ImGui::Text(TCHAR_TO_UTF8(*AddressStr));
        ImGui::TableSetColumnIndex(RowIndexCounter++);
        ImGui::TextColored(ImVec4(0, 1, 1, 1), "[Safe]");
        ImGui::TableSetColumnIndex(RowIndexCounter++);
        ImGui::TextColored(ImVec4(0, 1, 1, 1), "[Safe]");
        ImGui::TableSetColumnIndex(RowIndexCounter++);
        ImGui::TextColored(ImVec4(0, 1, 1, 1), "[Safe]");
        return;
    }

    int32 RowIndexCounter = InRowIndex;

    // アドレスを文字列化して表示。クリック可能にして、クリックされたら詳細ウィンドウ表示用リストに追加。
    ImGui::TableSetColumnIndex(RowIndexCounter++);
    const auto AddressStr = FString::Printf(TEXT("%p"), InObject);
    ImGui::Text(TCHAR_TO_UTF8(*AddressStr));

    // 名前の表示
    ImGui::TableSetColumnIndex(RowIndexCounter++);
    ImGui::Text(TCHAR_TO_UTF8(*InObject->GetName()));

    // GCステータスの表示
    ImGui::TableSetColumnIndex(RowIndexCounter++);
    
    bool bIsValid = IsValid(InObject);
    bool bIsRootSet = InObject->IsRooted();
    bool bIsUnreachable = InObject->IsUnreachable();

    if (bIsRootSet) { ImGui::TextColored(ImVec4(0, 1, 0, 1), "[RootSet]"); ImGui::SameLine(); }
    if (bIsUnreachable) { ImGui::TextColored(ImVec4(1, 0, 0, 1), "[Unreachable]"); ImGui::SameLine(); }
    if (!bIsValid) { ImGui::TextColored(ImVec4(1, 1, 0, 1), "[PendingKill]"); }
    if (bIsRootSet == false && bIsUnreachable == false && bIsValid) ImGui::Text("Standard");

    // --- Object Flags (EObjectFlags) ---
    ImGui::TableSetColumnIndex(RowIndexCounter++);
    EObjectFlags Flags = InObject->GetFlags();
    if (Flags & RF_Public) ImGui::TextUnformatted("RF_Public ");
    if (Flags & RF_Standalone) ImGui::TextUnformatted("RF_Standalone ");
    if (Flags & RF_Transactional) ImGui::TextUnformatted("RF_Transactional ");
    if (Flags & RF_MarkAsRootSet) ImGui::TextUnformatted("RF_MarkAsRootSet ");
    if (Flags & RF_Transient) ImGui::TextUnformatted("RF_Transient ");
}
