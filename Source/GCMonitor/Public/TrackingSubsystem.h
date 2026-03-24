#pragma once

#include "CoreMinimal.h"
#include "Subsystems/EngineSubsystem.h"
#include "TrackingSubsystem.generated.h"


/// <summary>
/// ログエントリー構造体。ログの内容と発生時刻、対象オブジェクトの情報を保持する
/// </summary>
struct FTrackingLogEntry
{
    FString Timestamp{};     // ログの発生時刻（例: "12:34:56"）
    int32 SubjectId{};       // Subjectの通し番号
    FString SubjectName{};   // オブジェクト名
    FString EventMessage{};  // "BeginDestroy" などの内容

    FTrackingLogEntry(int32 InId, const FString& InName, const FString& InMessage)
        : SubjectId(InId), SubjectName(InName), EventMessage(InMessage){
        const auto& Now = FDateTime::Now();
        Timestamp = FString::Printf(TEXT("%02d:%02d:%02d.%03d"), Now.GetHour(), Now.GetMinute(), Now.GetSecond(), Now.GetMillisecond());
    }
};

/**
 * USubjectのライフサイクルやHolderの操作ログを管理するサブシステム
 */
UCLASS()
class GCMONITOR_API UTrackingSubsystem : public UEngineSubsystem
{
    GENERATED_BODY()

public:

    /// <summary>
    /// コンストラクタ
    /// </summary>
    UTrackingSubsystem();

    /// <summary>
    /// デストラクタ
    /// </summary>
    virtual ~UTrackingSubsystem();

    /// <summary>
    /// 新規ログ追加
    /// </summary>
    /// <param name="InTarget"></param>
    /// <param name="InMessage"></param>
    void AddLog(const UObject* InTarget, const FString& InMessage);

    /** 蓄積された全ログを取得 */
    const TArray<FTrackingLogEntry>& GetLogEntries() const { return LogHistory; }

    /// <summary>
    /// ログをすべて消去
    /// </summary>
    void ClearLogs();

private:

    /// ログの履歴
    TArray<FTrackingLogEntry> LogHistory{};
};