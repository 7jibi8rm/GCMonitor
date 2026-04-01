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


	/// <summary>
	/// コンストラクタ
	/// </summary>
	AImGuiVisualizer();

protected:

	/// <summary>
	/// 生成・開始時に呼び出される。
	/// </summary>
	virtual void BeginPlay() override;

	/// <summary>
	/// 終了・破棄時に呼び出される。
	/// </summary>
	/// <param name="EndPlayReason"></param>
	virtual void EndPlay(const EEndPlayReason::Type EndPlayReason) override;

private:

	/// <summary>
	/// ImGui描画用Tick関数。ImGuiのUI表示・テスト制御を行う
	/// </summary>
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


	// ------------------------------------------
	// 以下、ImGui制御用の変数です。
	// 組み込み型を使用し、リフレクションを外してあります。
	// ------------------------------------------

	// 継承タイプ選択用の静的変数
	int SelectedInheritanceType{0};

	// 生成物選択用の静的変数
	int SelectedObject{0};

	// 格納先選択用の静的変数
	int SelectedTarget{0};

	// GC保護の有無選択用の静的変数
	bool bIsGCProtected{true};

	// 生成数選択用の静的変数
	int GenerateCount{1};

	// nullptr表示スキップ用の静的変数
	bool bSkipNullptr{true};

	// 監視対象オブジェクト以外の表示切り替え用の静的変数
	bool bIsActive{false};

};
