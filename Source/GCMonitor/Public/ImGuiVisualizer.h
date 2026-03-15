// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include <ImGuiModule.h>
#include <ImGuiDelegates.h>
#include <imgui.h>

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "ImGuiVisualizer.generated.h"

class AHolderActor;
class USubject;

UCLASS()
class GCMONITOR_API AImGuiVisualizer : public AActor
{
	GENERATED_BODY()
	
public:	

	// Sets default values for this actor's properties
	AImGuiVisualizer();

protected:

	/** アクター生成・開始時に呼び出され、ImGui Tickデリゲートを登録する */
	virtual void BeginPlay() override;

	/** アクター終了時またはレベル遷移時に呼び出され、ImGui Tickデリゲートを解除する */
	virtual void EndPlay(const EEndPlayReason::Type EndPlayReason) override;

private:

	/** ImGui描画用Tick関数。ImGuiのUI表示・テスト制御を行う */
	void ImGuiTick();

    /// <summary>
    /// UObject生成テスト用ウィンドウの描画
    /// </summary>
    void DrawUObjectGenerationTestWindow();

    /// <summary>
    /// AActorHolder情報ウィンドウの描画
	/// </summary>
    void DrawAActorHolderReferenceWindow();

    /// <summary>
    /// UObjectリストウィンドウの描画
	/// </summary>
	void DrawUObjectListWindow();

	/// <summary>
	/// ログウィンドウの描画
    /// </summary>
	void DrawLogWindow();

	/// <summary>
	/// ImGuiのテーブルにUObjectの情報を1行描画するユーティリティ関数
	/// かなり限定的な機能のため、使用には注意。
	/// </summary>
	/// <param name="InObject">対象のオブジェクトポインタ</param>
	/// <param name="InRowIndex">先頭のカラム数</param>
	void DrawObjectTableRow(UObject* InObject, const int32 InRowIndex);

private:
	
    // 検証用の格納先
    UPROPERTY()
	TObjectPtr<AHolderActor> HolderActor{};

};
