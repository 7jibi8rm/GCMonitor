#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "ActorSubject.generated.h"

UCLASS()
class GCMONITOR_API AActorSubject : public AActor
{
	GENERATED_BODY()

public:
	// このアクターのプロパティのデフォルト値を設定
	AActorSubject();

protected:
	// ゲーム開始時またはSpawn時に呼ばれる
	virtual void BeginPlay() override;

	// アクターがDestroyされたときに呼ばれる
	virtual void Destroyed() override;

	// アクターがワールドから削除されるときに呼ばれる
	virtual void EndPlay(const EEndPlayReason::Type EndPlayReason) override;

	// アクターのプロパティ設定後に呼ばれる（コンストラクション時）
	virtual void OnConstruction(const FTransform& Transform) override;

	// 毎フレーム呼ばれる
	virtual void Tick(float DeltaTime) override;

	// アクターがネットワークで受信されたときに呼ばれる
	virtual void PostNetReceive() override;

	// アクターがロードされたときに呼ばれる
	virtual void PostLoad() override;

	// 全てのコンポーネントが登録された後に呼ばれる
	virtual void PostRegisterAllComponents() override;

	// 全てのコンポーネントが登録解除された後に呼ばれる
	virtual void PostUnregisterAllComponents() override;

	// コンポーネント初期化後に呼ばれる
	virtual void PostInitializeComponents() override;

	// アクターがDestroyされる前に呼ばれる
	virtual void BeginDestroy() override;

	// アクターがガベージコレクトされる直前に呼ばれる
	virtual void PostActorCreated() override;

	// アクターがBlueprintから生成されたときに呼ばれる
	virtual void PostEditChangeProperty(FPropertyChangedEvent& PropertyChangedEvent) override;

private:

	// ログ出力用のユーティリティ関数
    void AddLog(const FString& EventName);

};