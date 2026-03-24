// Fill out your copyright notice in the Description page of Project Settings.


#include "ImGuiVisualizer.h"
#include "HolderActor.h"
#include "Subject.h"
#include "TrackingSubsystem.h"

namespace
{

// 生成するUObjectのクラス。今回はテスト用のUSubjectクラスに固定。
const char* ObjectTypeNames[2] = {
    "USubject",
    "AActorSubject",
};

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
const char* ActorStorageLocationNames[static_cast<int32>(EStorageLocation::Num)] = {
    "TObjectPtr<UActorSubject>",
    "UActorSubject*",
    "TWeakObjectPtr<UActorUSubject>",
    "TArray<TObjectPtr<UActorSubject>>",
    "TArray<UActorSubject*>",
    "TArray<TWeakObjectPtr<UActorSubject>>",
    "TMap<int32, TObjectPtr<UActorSubject>>",
    "TMap<int32, UActorSubject*>",
    "TMap<int32, TWeakObjectPtr<UActorSubject>>",
};


};

/// <summary>
/// コンストラクタ
/// </summary>
AImGuiVisualizer::AImGuiVisualizer()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

/// <summary>
/// 生成・開始時に呼び出される。
/// </summary>
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

/// <summary>
/// 終了・破棄時に呼び出される。
/// </summary>
/// <param name="EndPlayReason"></param>
void AImGuiVisualizer::EndPlay(const EEndPlayReason::Type EndPlayReason)
{
	Super::EndPlay(EndPlayReason);

	// ImGuiTick関数をOnWorldDebugデリゲートから解除
	FImGuiDelegates::OnWorldDebug().RemoveAll(this);

	// ImGuiの入力モードを無効化
	FImGuiModule& ImGuiModule = FImGuiModule::Get();
	ImGuiModule.SetInputMode(false);
}


/// <summary>
/// ImGui描画用Tick関数。ImGuiのUI表示・テスト制御を行う
/// </summary>
void AImGuiVisualizer::ImGuiTick()
{
    // UObject生成テスト用ウィンドウの描画
    DrawUObjectGenerationTestWindow();

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
    // 【捕捉】以下、本メソッドでのみ使用するため静的変数で運用します。
    // AImGuiVisualizerはゲーム内に1つだけの想定ため、問題ないと判断しました。
 
    // 継承タイプ選択用の静的変数
    static int SelectedInheritanceType = 0;
    // 生成物選択用の静的変数
    static int SelectedObject = 0;
    // 格納先選択用の静的変数
    static int SelectedTarget = 0;
    // GC保護の有無選択用の静的変数
    static bool bIsGCProtected = true;
    // 生成数選択用の静的変数
    static int GenerateCount = 1;

    ImGui::SetNextWindowPos(ImVec2(20, 20), ImGuiCond_FirstUseEver);
    ImGui::SetNextWindowSize(ImVec2(360, 410), ImGuiCond_FirstUseEver);
    ImGui::Begin("操作ウィンドウ");


    ImGui::TextColored(ImVec4(0, 1, 1, 1), "オブジェクト生成");
    ImGui::Checkbox("UPROPERTY付与", &bIsGCProtected);
    ImGui::Combo("生成物タイプ", &SelectedObject, ObjectTypeNames, IM_ARRAYSIZE(ObjectTypeNames));

    if(SelectedObject == 0){
        ImGui::Combo("格納先メンバ", &SelectedTarget, StorageLocationNames, IM_ARRAYSIZE(StorageLocationNames));
        ImGui::SliderInt("生成数", &GenerateCount, 1, 10);
        if (ImGui::Button("NewObject実行！", ImVec2(-1, 0))) {
            HolderActor->GenerateSubject(static_cast<EStorageLocation>(SelectedTarget), bIsGCProtected, GenerateCount);
        }
    }
    else{
        ImGui::Combo("格納先メンバ", &SelectedTarget, ActorStorageLocationNames, IM_ARRAYSIZE(ActorStorageLocationNames));
        ImGui::SliderInt("生成数", &GenerateCount, 1, 10);
        if (ImGui::Button("SpawnActor実行！", ImVec2(-1, 0))) {
            HolderActor->SpawnActorSubject(static_cast<EStorageLocation>(SelectedTarget), bIsGCProtected, GenerateCount);
        }
    }

    ImGui::Separator();
    ImGui::TextColored(ImVec4(0, 1, 1, 1), "参照先操作");

    if(ImGui::Button("全格納先にnullptr代入", ImVec2(-1, 0))){
        HolderActor->SetNullptrToAllSubjects();
    }
    if (ImGui::Button("全コンテナのReset/Empty呼び出し", ImVec2(-1, 0))){
        HolderActor->ResetToAllContainerSubjects();
    }
    if (ImGui::Button("全ActorSubjectでDestory呼び出し", ImVec2(-1, 0))) {
        HolderActor->CallDestroyToAllSubjects();
    }

    ImGui::Separator();
    ImGui::TextColored(ImVec4(0, 1, 1, 1), "ガベージコレクション");

    ImGui::PushStyleColor(ImGuiCol_Button, ImVec4(0.6f, 0.1f, 0.1f, 1.0f));
    ImGui::PushStyleColor(ImGuiCol_ButtonHovered, ImVec4(0.8f, 0.2f, 0.2f, 1.0f));

    // 強制GCボタン
    if (ImGui::Button("GC 強制実行！", ImVec2(-1, 45))){
        // エンジンに対してGCを強制。bFullPurgeがtrueなら到達可能性を再計算して完全にクリアする
        const bool bFullPurge = false;
        GEngine->ForceGarbageCollection(bFullPurge);
    }

    ImGui::PopStyleColor(2);


    ImGui::End();
}

/// <summary>
/// AActorHolder情報ウィンドウの描画
/// </summary>
void AImGuiVisualizer::DrawAActorHolderReferenceWindow()
{
    // 【捕捉】以下、本メソッドでのみ使用するため静的変数で運用します。
    // AImGuiVisualizerはゲーム内に1つだけの想定ため、問題ないと判断しました。

    // nullptr表示スキップ用の静的変数
    static bool bSkipNullptr = true;


    ImGui::SetNextWindowPos(ImVec2(380, 20), ImGuiCond_FirstUseEver);
    ImGui::SetNextWindowSize(ImVec2(860, 410), ImGuiCond_FirstUseEver);

    ImGui::Begin("AHolderActor（格納先クラス）詳細");
    if (HolderActor == nullptr)
    {
        ImGui::TextColored(ImVec4(1, 0.5f, 0.5f, 1), "AHolderActor is nullptr.");
        ImGui::End();
        return;
    }

    ImGui::Checkbox("nullptrスキップ", &bSkipNullptr);

    // テーブルセットアップ用ラムダ関数
    // インデックス、オブジェクト、UPROPERTY有無、格納先名を受け取り、1行描画する
    auto EasyTableSetup = [&](const int32 InIndex, UObject* InObject, bool bProperty, const char* InStorageName){
        if(InObject == nullptr && bSkipNullptr){
            return; // nullptr表示スキップ
        }

        ImGui::TableSetColumnIndex(0);
        if (InIndex == 0) {
            if (bProperty) {
                ImGui::TextColored(ImVec4(0, 1, 0, 1), "UPROPERTY()");
                ImGui::TextColored(ImVec4(0, 1, 0, 1), InStorageName);
            }
            else {
                ImGui::TextColored(ImVec4(1, 0, 0, 1), InStorageName);
            }
        }
        ImGui::TableSetColumnIndex(1);
        ImGui::Text("%d", InIndex);
        DrawObjectTableRow(InObject, 2);
        ImGui::TableNextRow();
    };

    if (ImGui::BeginTable("ObjectTable", 4, ImGuiTableFlags_Borders | ImGuiTableFlags_Resizable | ImGuiTableFlags_RowBg | ImGuiTableFlags_ScrollY | ImGuiTableFlags_ScrollX))
    {
        // テーブルヘッダー
        ImGui::TableSetupColumn("Storage",      ImGuiTableColumnFlags_WidthFixed, 250.0f);
        ImGui::TableSetupColumn("Index",        ImGuiTableColumnFlags_WidthFixed,  70.0f);
        ImGui::TableSetupColumn("Address",      ImGuiTableColumnFlags_WidthFixed, 130.0f); 
        ImGui::TableSetupColumn("IsValid",      ImGuiTableColumnFlags_WidthFixed, 130.0f);
        ImGui::TableHeadersRow();
        ImGui::TableNextRow();

        // ----------------------------------------------------------
        // USubject格納先の描画
        // ----------------------------------------------------------

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

        // ----------------------------------------------------------
        // AActorSubject格納先の描画
        // ----------------------------------------------------------

        // UPROPERTY()付き格納先
        EasyTableSetup(0, HolderActor->GetSafeActorSubjectPtr().Get(), true, ActorStorageLocationNames[static_cast<int32>(EStorageLocation::Ptr)]);
        EasyTableSetup(0, HolderActor->GetSafeActorSubjectRaw(), true, ActorStorageLocationNames[static_cast<int32>(EStorageLocation::Raw)]);
        EasyTableSetup(0, HolderActor->GetSafeActorSubjectWeak().Get(), true, ActorStorageLocationNames[static_cast<int32>(EStorageLocation::Weak)]);
        // 配列（TObjectPtr）
        for (int32 i = 0; i < HolderActor->GetSafeActorSubjectPtrArray().Num(); ++i) {
            EasyTableSetup(i, HolderActor->GetSafeActorSubjectPtrArray()[i].Get(), true, ActorStorageLocationNames[static_cast<int32>(EStorageLocation::PtrArray)]);
        }
        // 配列（Raw）
        for (int32 i = 0; i < HolderActor->GetSafeActorSubjectRawArray().Num(); ++i) {
            EasyTableSetup(i, HolderActor->GetSafeActorSubjectRawArray()[i], true, ActorStorageLocationNames[static_cast<int32>(EStorageLocation::RawArray)]);
        }
        // 配列（Weak）
        for (int32 i = 0; i < HolderActor->GetSafeActorSubjectWeakArray().Num(); ++i) {
            EasyTableSetup(i, HolderActor->GetSafeActorSubjectWeakArray()[i].Get(), true, ActorStorageLocationNames[static_cast<int32>(EStorageLocation::WeakArray)]);
        }
        // マップ（TObjectPtr）
        for (const auto& Pair : HolderActor->GetSafeActorSubjectPtrMap()) {
            EasyTableSetup(Pair.Key, Pair.Value.Get(), true, ActorStorageLocationNames[static_cast<int32>(EStorageLocation::PtrMap)]);
        }
        // マップ（Raw）
        for (const auto& Pair : HolderActor->GetSafeActorSubjectRawMap()) {
            EasyTableSetup(Pair.Key, Pair.Value, true, ActorStorageLocationNames[static_cast<int32>(EStorageLocation::RawMap)]);
        }
        // マップ（Weak）
        for (const auto& Pair : HolderActor->GetSafeActorSubjectWeakMap()) {
            EasyTableSetup(Pair.Key, Pair.Value.Get(), true, ActorStorageLocationNames[static_cast<int32>(EStorageLocation::WeakMap)]);
        }

        // 非UPROPERTY()格納先
        EasyTableSetup(0, HolderActor->GetUnSafeActorSubjectPtr().Get(), false, ActorStorageLocationNames[static_cast<int32>(EStorageLocation::Ptr)]);
        EasyTableSetup(0, HolderActor->GetUnSafeActorSubjectRaw(), false, ActorStorageLocationNames[static_cast<int32>(EStorageLocation::Raw)]);
        EasyTableSetup(0, HolderActor->GetUnSafeActorSubjectWeak().Get(), false, ActorStorageLocationNames[static_cast<int32>(EStorageLocation::Weak)]);

        // 配列（TObjectPtr, 非UPROPERTY）
        for (int32 i = 0; i < HolderActor->GetUnSafeActorSubjectPtrArray().Num(); ++i) {
            EasyTableSetup(i, HolderActor->GetUnSafeActorSubjectPtrArray()[i].Get(), false, ActorStorageLocationNames[static_cast<int32>(EStorageLocation::PtrArray)]);
        }
        // 配列（Raw, 非UPROPERTY）
        for (int32 i = 0; i < HolderActor->GetUnSafeActorSubjectRawArray().Num(); ++i) {
            EasyTableSetup(i, HolderActor->GetUnSafeActorSubjectRawArray()[i], false, ActorStorageLocationNames[static_cast<int32>(EStorageLocation::RawArray)]);
        }
        // 配列（Weak, 非UPROPERTY）
        for (int32 i = 0; i < HolderActor->GetUnSafeActorSubjectWeakArray().Num(); ++i) {
            EasyTableSetup(i, HolderActor->GetUnSafeActorSubjectWeakArray()[i].Get(), false, ActorStorageLocationNames[static_cast<int32>(EStorageLocation::WeakArray)]);
        }

        // マップ（TObjectPtr, 非UPROPERTY）
        for (const auto& Pair : HolderActor->GetUnSafeActorSubjectPtrMap()) {
            EasyTableSetup(Pair.Key, Pair.Value.Get(), false, ActorStorageLocationNames[static_cast<int32>(EStorageLocation::PtrMap)]);
        }
        // マップ（Raw, 非UPROPERTY）
        for (const auto& Pair : HolderActor->GetUnSafeActorSubjectRawMap()) {
            EasyTableSetup(Pair.Key, Pair.Value, false, ActorStorageLocationNames[static_cast<int32>(EStorageLocation::RawMap)]);
        }
        // マップ（Weak, 非UPROPERTY）
        for (const auto& Pair : HolderActor->GetUnSafeActorSubjectWeakMap()) {
            EasyTableSetup(Pair.Key, Pair.Value.Get(), false, ActorStorageLocationNames[static_cast<int32>(EStorageLocation::WeakMap)]);
        }

        ImGui::EndTable();
    }
    ImGui::End();
}

/// <summary>
/// UObjectリストウィンドウの描画
/// </summary>
void AImGuiVisualizer::DrawUObjectListWindow()
{
    // 【捕捉】以下、本メソッドでのみ使用するため静的変数で運用します。
    // AImGuiVisualizerはゲーム内に1つだけの想定ため、問題ないと判断しました。

    // 監視対象オブジェクト以外の表示切り替え用の静的変数
    static bool bIsActive = false;


    ImGui::SetNextWindowPos(ImVec2(765, 440), ImGuiCond_FirstUseEver);
    ImGui::SetNextWindowSize(ImVec2(485, 280), ImGuiCond_FirstUseEver);

    ImGui::Begin("UObjectリスト");

    ImGui::Checkbox("全てのObject表示", &bIsActive);

    // テーブル構成: 3列 (Name, Address, GC Flags)
    if (ImGui::BeginTable("ObjectTable", 3, ImGuiTableFlags_Borders | ImGuiTableFlags_RowBg | ImGuiTableFlags_Resizable | ImGuiTableFlags_ScrollY))
    {
        // ヘッダーの設定
        ImGui::TableSetupColumn("Index", ImGuiTableColumnFlags_WidthFixed, 70.0f);
        ImGui::TableSetupColumn("Address", ImGuiTableColumnFlags_WidthFixed, 130.0f);
        ImGui::TableSetupColumn("IsValid", ImGuiTableColumnFlags_WidthFixed, 130.0f);
        ImGui::TableHeadersRow();
        ImGui::TableNextRow();

        for (TObjectIterator<UObject> It; It; ++It)
        {
            UObject* Object = *It;

            // 監視対象オブジェクト以外はスキップ
            if (!bIsActive){
                USubject* CheckSubject = Cast<USubject>(Object);
                AActorSubject* CheckActorSubject = Cast<AActorSubject>(Object);
                if (!CheckSubject && !CheckActorSubject) {
                    continue;
                }
            }
            
            ImGui::TableSetColumnIndex(0);
            ImGui::Text("%d", It.GetIndex());
            DrawObjectTableRow(Object, 1);
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
    if (!GEngine){
        return;
    }

    ImGui::SetNextWindowPos(ImVec2(20, 440), ImGuiCond_FirstUseEver);
    ImGui::SetNextWindowSize(ImVec2(750, 290), ImGuiCond_FirstUseEver);
    ImGui::Begin("ログ");

    // --- 上部操作エリア ---
    if (ImGui::Button("Clear")) {
        if (UTrackingSubsystem* Tracking = GEngine->GetEngineSubsystem<UTrackingSubsystem>()){
            Tracking->ClearLogs();
        }
    }

    ImGui::Separator();

    // --- ログ表示エリア ---
    ImGui::BeginChild("ScrollingRegion", ImVec2(0, 0), false, ImGuiWindowFlags_HorizontalScrollbar);
    if (UTrackingSubsystem* Tracking = GEngine->GetEngineSubsystem<UTrackingSubsystem>()){
        for (const auto& LogEntry : Tracking->GetLogEntries()){
            ImGui::Text("%s [%d - %s] : %s", TCHAR_TO_UTF8(*LogEntry.Timestamp), LogEntry.SubjectId, TCHAR_TO_UTF8(*LogEntry.SubjectName), TCHAR_TO_UTF8(*LogEntry.EventMessage));
        }
    }

    // ログが追加されたときに自動で一番下までスクロール
    if (ImGui::GetScrollY() >= ImGui::GetScrollMaxY()){
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
void AImGuiVisualizer::DrawObjectTableRow(UObject* InObject,const int32 InRowIndex)
{
    int32 RowIndexCounter = InRowIndex;

    // アドレスを文字列化して表示。
    ImGui::TableSetColumnIndex(RowIndexCounter++);
    const auto AddressStr = FString::Printf(TEXT("%p"), InObject);
    ImGui::Text(TCHAR_TO_UTF8(*AddressStr));
    // 
    ImGui::TableSetColumnIndex(RowIndexCounter++);
    if(IsValid(InObject)){
        ImGui::TextColored(ImVec4(0, 1, 0, 1), "True");
    }
    else{
        ImGui::TextColored(ImVec4(1, 0, 0, 1), "False");
    }
}
