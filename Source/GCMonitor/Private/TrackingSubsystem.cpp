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
/// <param name="InTarget"></param>
/// <param name="InMessage"></param>
void UTrackingSubsystem::AddLog( const UObject* InTarget, const FString& InMessage)
{
    if(InTarget != nullptr){
        FTrackingLogEntry NewEntry(InTarget->GetUniqueID(), InTarget->GetName(), InMessage);
        LogHistory.Add(NewEntry);
    }
    else{
        FTrackingLogEntry NewEntry(-1, TEXT("None"), InMessage);
        LogHistory.Add(NewEntry);
    }
}

/** ログをすべて消去 */
void UTrackingSubsystem::ClearLogs()
{
    LogHistory.Empty();
}
