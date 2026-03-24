// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "UObject/Object.h"
#include "UObject/ObjectSaveContext.h"
#include "UObject/AssetRegistryTagsContext.h"
#include "Subject.generated.h"

UCLASS()
class GCMONITOR_API USubject : public UObject
{
    GENERATED_BODY()

public:
    /// <summary>
    /// コンストラクタ。オブジェクト生成時に呼ばれる。
    /// </summary>
    USubject();

    /// <summary>
    /// デストラクタ。オブジェクト破棄時に呼ばれる。
    /// </summary>
    virtual ~USubject();

    /// <summary>
    /// プロパティ初期化後に呼ばれる。C++コンストラクタとプロパティ初期化後の追加処理用。
    /// </summary>
    virtual void PostInitProperties() override;

    /// <summary>
    /// プロパティ再初期化後に呼ばれる。CDOやサブオブジェクトの再初期化時に利用。
    /// </summary>
    virtual void PostReinitProperties() override;

    /// <summary>
    /// クラスデフォルトオブジェクト（CDO）構築後に呼ばれる。
    /// </summary>
    virtual void PostCDOContruct() override;

    /// <summary>
    /// ルート保存前に呼ばれる。パッケージ保存前の準備処理用。
    /// </summary>
    virtual void PreSaveRoot(FObjectPreSaveRootContext ObjectSaveContext) override;

    /// <summary>
    /// ルート保存後に呼ばれる。パッケージ保存後の後処理用。
    /// </summary>
    virtual void PostSaveRoot(FObjectPostSaveRootContext ObjectSaveContext) override;

    /// <summary>
    /// 保存直前に呼ばれる。シリアライズ前の準備処理用。
    /// </summary>
    virtual void PreSave(FObjectPreSaveContext SaveContext) override;

    /// <summary>
    /// 保存時のオーバーライド情報収集用。
    /// </summary>
    virtual void CollectSaveOverrides(FObjectCollectSaveOverridesContext SaveContext) override;

    /// <summary>
    /// オブジェクトロード後に呼ばれる。ディスクからのロード直後の初期化処理用。
    /// </summary>
    virtual void PostLoad() override;

    /// <summary>
    /// サブオブジェクトロード後に呼ばれる。サブオブジェクトの参照修正などに利用。
    /// </summary>
    virtual void PostLoadSubobjects(FObjectInstancingGraph* OuterInstanceGraph) override;

    /// <summary>
    /// 破棄プロセスの開始（MarkAsGarbage後、最初に呼ばれる）。
    /// </summary>
    virtual void BeginDestroy() override;

    /// <summary>
    /// 破棄準備の完了（非同期GCの場合、この後にFinishDestroyが呼ばれる）。
    /// </summary>
    virtual bool IsReadyForFinishDestroy() override;

    /// <summary>
    /// メモリ解放の直前（この直後にオブジェクトがメモリから消滅する）。
    /// </summary>
    virtual void FinishDestroy() override;

    /// <summary>
    /// シリアライズ処理。FArchiveを使ったプロパティ保存・復元。
    /// </summary>
    virtual void Serialize(FArchive& Ar) override;

    /// <summary>
    /// 構造化アーカイブ用のシリアライズ処理。
    /// </summary>
    virtual void Serialize(FStructuredArchive::FRecord Record) override;

    /// <summary>
    /// 致命的エラー発生後のクリーンアップ処理。
    /// </summary>
    virtual void ShutdownAfterError() override;

    /// <summary>
    /// 複製後に呼ばれる。PIE用かどうかの判定も可能。
    /// </summary>
    virtual void PostDuplicate(bool bDuplicateForPIE) override;

    /// <summary>
    /// 複製後に呼ばれる（複製モード指定）。
    /// </summary>
    virtual void PostDuplicate(EDuplicateMode::Type DuplicateMode) override;

    /// <summary>
    /// クライアント用にロードが必要か判定。
    /// </summary>
    virtual bool NeedsLoadForClient() const override;

    /// <summary>
    /// サーバー用にロードが必要か判定。
    /// </summary>
    virtual bool NeedsLoadForServer() const override;

    /// <summary>
    /// 指定プラットフォーム用にロードが必要か判定。
    /// </summary>
    virtual bool NeedsLoadForTargetPlatform(const class ITargetPlatform* TargetPlatform) const override;

    /// <summary>
    /// エディタゲーム用に常にロードが必要か判定。
    /// </summary>
    virtual bool NeedsLoadForEditorGame() const override;

    /// <summary>
    /// エディタ専用オブジェクトか判定。
    /// </summary>
    virtual bool IsEditorOnly() const override;

    /// <summary>
    /// エディタ専用オブジェクトでも参照がゲームで必要か判定。
    /// </summary>
    virtual bool HasNonEditorOnlyReferences() const override;

    /// <summary>
    /// PostLoadがスレッドセーフか判定。
    /// </summary>
    virtual bool IsPostLoadThreadSafe() const override;

    /// <summary>
    /// プリロード依存オブジェクトの収集。
    /// </summary>
    virtual void GetPreloadDependencies(TArray<UObject*>& OutDeps) override;

    /// <summary>
    /// プリストリーム対象パッケージの収集。
    /// </summary>
    virtual void GetPrestreamPackages(TArray<UObject*>& OutPrestream) override;

    /// <summary>
    /// オブジェクト名やOuterの変更処理。
    /// </summary>
    virtual bool Rename(const TCHAR* NewName = nullptr, UObject* NewOuter = nullptr, ERenameFlags Flags = REN_None) override;

    /// <summary>
    /// サムネイル等で使われる1行説明文を返す。
    /// </summary>
    virtual FString GetDesc() override;

    /// <summary>
    /// メモリ使用量情報の取得。
    /// </summary>
    virtual void GetResourceSizeEx(FResourceSizeEx& CumulativeResourceSize) override;

    /// <summary>
    /// エクスポート時のファクトリ名取得。
    /// </summary>
    virtual FName GetExporterName() override;

    /// <summary>
    /// オブジェクト上書き時のリストア情報取得。
    /// </summary>
    virtual FRestoreForUObjectOverwrite* GetRestoreForUObjectOverwrite() override;

    /// <summary>
    /// ネイティブプロパティが同一か判定。
    /// </summary>
    virtual bool AreNativePropertiesIdenticalTo(UObject* Other) const override;

    /// <summary>
    /// アセットレジストリ用タグ情報の取得（新形式）。
    /// </summary>
    virtual void GetAssetRegistryTags(FAssetRegistryTagsContext Context) const override;

    /// <summary>
    /// アセットレジストリ用タグ情報の取得（旧形式）。
    /// </summary>
    virtual void GetAssetRegistryTags(TArray<FAssetRegistryTag>& OutTags) const override;

private:
    /// <summary>
    /// ログ追加処理。TrackingSubsystemに詳細ログを送信。
    /// </summary>
    void AddLog(const FString& InLogDetail);
};
