#pragma once

#include "CoreMinimal.h"
#include "Subsystems/EngineSubsystem.h"
#include "TrackingSubsystem.generated.h"


/// <summary>
/// ログレベル
/// </summary>
UENUM()
enum class ELogLevel : uint8
{
    Info,
    Warning,
    Error
};

/** ログの1行を表現する構造体 */
struct FTrackingLogEntry
{
    FString Timestamp{};     // ログの発生時刻（例: "12:34:56"）
    int32 SubjectId{};       // Subjectの通し番号
    FString SubjectName{};   // オブジェクト名
    FString EventMessage{};  // "BeginDestroy" などの内容

    FTrackingLogEntry(int32 InId, const FString& InName, const FString& InMessage)
        : SubjectId(InId)
        , SubjectName(InName)
        , EventMessage(InMessage)
    {
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
    /// <param name="InLevel"></param>
    /// <param name="InTarget"></param>
    /// <param name="InMessage"></param>
    void AddLog(ELogLevel InLevel, const UObject* InTarget, const FString& InMessage);

    /** 蓄積された全ログを取得 */
    const TArray<FTrackingLogEntry>& GetLogEntries() const { return LogHistory; }

    /// <summary>
    /// ログをすべて消去
    /// </summary>
    void ClearLogs();

private:
    /** ログの履歴。数が増えすぎないよう適宜管理する */
    TArray<FTrackingLogEntry> LogHistory;

    /** ログの最大保持件数 */
    const int32 MaxLogCount = 99999; // 基本的に枯渇しないようにしておく。
};