// Fill out your copyright notice in the Description page of Project Settings.


#include "TrackingSubsystem.h"

/// <summary>
/// コンストラクタ
/// </summary>
UTrackingSubsystem::UTrackingSubsystem()
{
}

/// <summary>
/// デストラクタ
/// </summary>
UTrackingSubsystem::~UTrackingSubsystem()
{
}

/// <summary>
/// 新規ログ追加
/// </summary>
/// <param name="InLevel"></param>
/// <param name="InTarget"></param>
/// <param name="InMessage"></param>
void UTrackingSubsystem::AddLog(ELogLevel InLevel, const UObject* InTarget, const FString& InMessage)
{
    const int32 SubjectId = InTarget ? InTarget->GetUniqueID() : -1;
    const FString SubjectName = InTarget ? InTarget->GetName() : TEXT("None");

    FTrackingLogEntry NewEntry(SubjectId, SubjectName, InMessage);
    LogHistory.Add(NewEntry);

    // 最大件数を超えた場合は先頭から削除
    while (LogHistory.Num() > MaxLogCount)
    {
        LogHistory.RemoveAt(0);
    }
}

/** ログをすべて消去 */
void UTrackingSubsystem::ClearLogs()
{
    LogHistory.Empty();
}
