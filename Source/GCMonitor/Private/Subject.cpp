// Fill out your copyright notice in the Description page of Project Settings.


#include "Subject.h"
#include "TrackingSubsystem.h"
#include "Engine/Engine.h"

USubject::USubject()
{
    // ログ登録
    AddLog(TEXT(__FUNCTION__));
}

USubject::~USubject()
{
    // ログ登録
    AddLog(TEXT(__FUNCTION__));
}

/**
 * 破棄プロセスの開始（MarkAsGarbage後、最初に呼ばれる）
 */
void USubject::BeginDestroy()
{
    Super::BeginDestroy();

    // ログ登録
    AddLog(TEXT(__FUNCTION__));
}

/**
 * 破棄準備の完了（非同期GCの場合、この後にFinishDestroyが呼ばれる）
 */
bool USubject::IsReadyForFinishDestroy()
{
    // ログ登録
    AddLog(TEXT(__FUNCTION__));

    return Super::IsReadyForFinishDestroy();
}

/**
 * メモリ解放の直前（この直後にオブジェクトがメモリから消滅する）
 */
void USubject::FinishDestroy()
{
    // ログ登録
    AddLog(TEXT(__FUNCTION__));

    Super::FinishDestroy();
}

void USubject::PostInitProperties()
{
    Super::PostInitProperties();
    AddLog(TEXT(__FUNCTION__));
}

void USubject::PostReinitProperties()
{
    Super::PostReinitProperties();
    AddLog(TEXT(__FUNCTION__));
}

void USubject::PostCDOContruct()
{
    Super::PostCDOContruct();
    AddLog(TEXT(__FUNCTION__));
}

void USubject::PreSaveRoot(FObjectPreSaveRootContext ObjectSaveContext)
{
    Super::PreSaveRoot(ObjectSaveContext);
    AddLog(TEXT(__FUNCTION__));
}

void USubject::PostSaveRoot(FObjectPostSaveRootContext ObjectSaveContext)
{
    Super::PostSaveRoot(ObjectSaveContext);
    AddLog(TEXT(__FUNCTION__));
}

void USubject::PreSave(FObjectPreSaveContext SaveContext)
{
    Super::PreSave(SaveContext);
    AddLog(TEXT(__FUNCTION__));
}

void USubject::CollectSaveOverrides(FObjectCollectSaveOverridesContext SaveContext)
{
    Super::CollectSaveOverrides(SaveContext);
    AddLog(TEXT(__FUNCTION__));
}

void USubject::PostLoad()
{
    Super::PostLoad();
    AddLog(TEXT(__FUNCTION__));
}

void USubject::PostLoadSubobjects(FObjectInstancingGraph* OuterInstanceGraph)
{
    Super::PostLoadSubobjects(OuterInstanceGraph);
    AddLog(TEXT(__FUNCTION__));
}

void USubject::ShutdownAfterError()
{
    Super::ShutdownAfterError();
    AddLog(TEXT(__FUNCTION__));
}

void USubject::PostDuplicate(bool bDuplicateForPIE)
{
    Super::PostDuplicate(bDuplicateForPIE);
    AddLog(TEXT(__FUNCTION__));
}

void USubject::PostDuplicate(EDuplicateMode::Type DuplicateMode)
{
    Super::PostDuplicate(DuplicateMode);
    AddLog(TEXT(__FUNCTION__));
}

bool USubject::NeedsLoadForClient() const
{
    return Super::NeedsLoadForClient();
}

bool USubject::NeedsLoadForServer() const
{
    return Super::NeedsLoadForServer();
}

bool USubject::NeedsLoadForTargetPlatform(const class ITargetPlatform* TargetPlatform) const
{
    return Super::NeedsLoadForTargetPlatform(TargetPlatform);
}

bool USubject::NeedsLoadForEditorGame() const
{
    return Super::NeedsLoadForEditorGame();
}

bool USubject::IsEditorOnly() const
{
    return Super::IsEditorOnly();
}

bool USubject::HasNonEditorOnlyReferences() const
{
    return Super::HasNonEditorOnlyReferences();
}

bool USubject::IsPostLoadThreadSafe() const
{
    return Super::IsPostLoadThreadSafe();
}

void USubject::GetPreloadDependencies(TArray<UObject*>& OutDeps)
{
    Super::GetPreloadDependencies(OutDeps);
    AddLog(TEXT(__FUNCTION__));
}

void USubject::GetPrestreamPackages(TArray<UObject*>& OutPrestream)
{
    Super::GetPrestreamPackages(OutPrestream);
    AddLog(TEXT(__FUNCTION__));
}

bool USubject::Rename(const TCHAR* NewName, UObject* NewOuter, ERenameFlags Flags)
{
    AddLog(TEXT(__FUNCTION__));
    return Super::Rename(NewName, NewOuter, Flags);
}

FString USubject::GetDesc()
{
    AddLog(TEXT(__FUNCTION__));
    return Super::GetDesc();
}

void USubject::GetResourceSizeEx(FResourceSizeEx& CumulativeResourceSize)
{
    Super::GetResourceSizeEx(CumulativeResourceSize);
    AddLog(TEXT(__FUNCTION__));
}

FName USubject::GetExporterName()
{
    AddLog(TEXT(__FUNCTION__));
    return Super::GetExporterName();
}

FRestoreForUObjectOverwrite* USubject::GetRestoreForUObjectOverwrite()
{
    AddLog(TEXT(__FUNCTION__));
    return Super::GetRestoreForUObjectOverwrite();
}

bool USubject::AreNativePropertiesIdenticalTo(UObject* Other) const
{
    return Super::AreNativePropertiesIdenticalTo(Other);
}

void USubject::GetAssetRegistryTags(FAssetRegistryTagsContext Context) const
{
    Super::GetAssetRegistryTags(Context);
    // const関数なのでAddLogは省略
}

void USubject::GetAssetRegistryTags(TArray<FAssetRegistryTag>& OutTags) const
{
    Super::GetAssetRegistryTags(OutTags);
    // const関数なのでAddLogは省略
}

void USubject::Serialize(FArchive& Ar)
{
    Super::Serialize(Ar);
    AddLog(TEXT(__FUNCTION__));
}

void USubject::Serialize(FStructuredArchive::FRecord Record)
{
    Super::Serialize(Record);
    AddLog(TEXT(__FUNCTION__));
}

/**
 * ログ追加処理。TrackingSubsystemに詳細ログを送信。
 */
void USubject::AddLog(const FString& InLogDetail)
{
    if (GEngine)
    {
        if (UTrackingSubsystem* Tracking = GEngine->GetEngineSubsystem<UTrackingSubsystem>())
        {
            Tracking->AddLog(this, InLogDetail);
        }
    }
}