// Fill out your copyright notice in the Description page of Project Settings.


#include "ActorSubject.h"
#include "TrackingSubsystem.h"

// Sets default values
AActorSubject::AActorSubject()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

    // ログ登録
    AddLog(TEXT(__FUNCTION__));
}

// Called when the game starts or when spawned
void AActorSubject::BeginPlay()
{
	Super::BeginPlay();

    // ログ登録
    AddLog(TEXT(__FUNCTION__));
}

void AActorSubject::Destroyed()
{
    // アクターがDestroyされたときに呼ばれる
    Super::Destroyed();

    // ログ登録
    AddLog(TEXT(__FUNCTION__));
}

void AActorSubject::EndPlay(const EEndPlayReason::Type EndPlayReason)
{
    // アクターがワールドから削除されるときに呼ばれる
    Super::EndPlay(EndPlayReason);

    // ログ登録
    AddLog(TEXT(__FUNCTION__));
}

void AActorSubject::OnConstruction(const FTransform& Transform)
{
    // アクターのプロパティ設定後に呼ばれる（コンストラクション時）
    Super::OnConstruction(Transform);

    // ログ登録
    AddLog(TEXT(__FUNCTION__));
}

void AActorSubject::Tick(float DeltaTime)
{
    // 毎フレーム呼ばれる
	Super::Tick(DeltaTime);

}

void AActorSubject::PostNetReceive()
{
    // アクターがネットワークで受信されたときに呼ばれる
    Super::PostNetReceive();

    // ログ登録
    AddLog(TEXT(__FUNCTION__));
}

void AActorSubject::PostLoad()
{
    // アクターがロードされたときに呼ばれる
    Super::PostLoad();

    // ログ登録
    AddLog(TEXT(__FUNCTION__));
}

void AActorSubject::PostRegisterAllComponents()
{
    // 全てのコンポーネントが登録された後に呼ばれる
    Super::PostRegisterAllComponents();

    // ログ登録
    AddLog(TEXT(__FUNCTION__));
}

void AActorSubject::PostUnregisterAllComponents()
{
    // 全てのコンポーネントが登録解除された後に呼ばれる
    Super::PostUnregisterAllComponents();

    // ログ登録
    AddLog(TEXT(__FUNCTION__));
}

void AActorSubject::PostInitializeComponents()
{
    // コンポーネント初期化後に呼ばれる
    Super::PostInitializeComponents();

    // ログ登録
    AddLog(TEXT(__FUNCTION__));
}

void AActorSubject::BeginDestroy()
{
    // アクターがDestroyされる前に呼ばれる
    Super::BeginDestroy();

    // ログ登録
    AddLog(TEXT(__FUNCTION__));
}

void AActorSubject::PostActorCreated()
{
    // アクターがガベージコレクトされる直前に呼ばれる
    Super::PostActorCreated();

    // ログ登録
    AddLog(TEXT(__FUNCTION__));
}

void AActorSubject::PostEditChangeProperty(FPropertyChangedEvent& PropertyChangedEvent)
{
    // アクターがBlueprintから生成されたときに呼ばれる
    Super::PostEditChangeProperty(PropertyChangedEvent);

    // ログ登録
    AddLog(TEXT(__FUNCTION__));
}

/**
 * ログ追加処理。TrackingSubsystemに詳細ログを送信。
 */
void AActorSubject::AddLog(const FString& InLogDetail)
{
    if (GEngine)
    {
        if (UTrackingSubsystem* Tracking = GEngine->GetEngineSubsystem<UTrackingSubsystem>())
        {
            Tracking->AddLog(this, InLogDetail);
        }
    }
}