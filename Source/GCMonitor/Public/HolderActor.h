// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Subject.h"
#include "ActorSubject.h"
#include "HolderActor.generated.h"

UENUM()
/**
 * @brief Subjectの格納先を示す列挙型
 */
enum class EStorageLocation : uint8
{
    Ptr,        // TObjectPtrによる格納
    Raw,        // 生ポインタによる格納
    Weak,       // TWeakObjectPtrによる格納
    PtrArray,   // TObjectPtr配列による格納
    RawArray,   // 生ポインタ配列による格納
    WeakArray,  // TWeakObjectPtr配列による格納
    PtrMap,     // TObjectPtrマップによる格納
    RawMap,     // 生ポインタマップによる格納
    WeakMap,    // TWeakObjectPtrマップによる格納
    Num,        // 格納先の数
};

UCLASS()
/**
 * @brief Subjectの参照を様々な方法で保持・管理するアクター
 */
class GCMONITOR_API AHolderActor : public AActor
{
	GENERATED_BODY()
	
public:	

	/**
	 * @brief このアクターのプロパティのデフォルト値を設定
	 */
	AHolderActor();


    // --------------------------------------------------------------
    // USubject関連のメソッド
    // --------------------------------------------------------------

    /**
     * @brief テストケースに応じたSubject生成関数
     * @param InStorageLocation 格納先
     * @param bProperty UPROPERTY有無
     * @param InNum 生成数
     */
    void GenerateSubject(const EStorageLocation InStorageLocation, bool bProperty, const int32 InNum);

    // Unsafe（UPROPERTYなし）

    /** UPROPERTYなしのTObjectPtrによるSubject参照を取得 */
    TObjectPtr<USubject> GetUnSafeSubjectPtr() const { return UnSafeSubjectPtr; }
    /** UPROPERTYなしの生ポインタによるSubject参照を取得 */
    USubject* GetUnSafeSubjectRaw() const { return UnSafeSubjectRaw; }
    /** UPROPERTYなしのTWeakObjectPtrによるSubject参照を取得 */
    TWeakObjectPtr<USubject> GetUnSafeSubjectWeak() const { return UnSafeSubjectWeak; }
    /** UPROPERTYなしの生ポインタ配列によるSubject参照を取得 */
    const TArray<USubject*>& GetUnSafeSubjectRawArray() const { return UnSafeSubjectRawArray; }
    /** UPROPERTYなしのTObjectPtr配列によるSubject参照を取得 */
    const TArray<TObjectPtr<USubject>>& GetUnSafeSubjectPtrArray() const { return UnSafeSubjectPtrArray; }
    /** UPROPERTYなしのTWeakObjectPtr配列によるSubject参照を取得 */
    const TArray<TWeakObjectPtr<USubject>>& GetUnSafeSubjectWeakArray() const { return UnSafeSubjectWeakArray; }
    /** UPROPERTYなしのTObjectPtrマップによるSubject参照を取得 */
    const TMap<int32, TObjectPtr<USubject>>& GetUnSafeSubjectPtrMap() const { return UnSafeSubjectPtrMap; }
    /** UPROPERTYなしの生ポインタマップによるSubject参照を取得 */
    const TMap<int32, USubject*>& GetUnSafeSubjectRawMap() const { return UnSafeSubjectRawMap; }
    /** UPROPERTYなしのTWeakObjectPtrマップによるSubject参照を取得 */
    const TMap<int32, TWeakObjectPtr<USubject>>& GetUnSafeSubjectWeakMap() const { return UnSafeSubjectWeakMap; }

    // Safe（UPROPERTYあり）

    /** UPROPERTYありのTObjectPtrによるSubject参照を取得 */
    TObjectPtr<USubject> GetSafeSubjectPtr() const { return SafeSubjectPtr; }
    /** UPROPERTYありの生ポインタによるSubject参照を取得 */
    USubject* GetSafeSubjectRaw() const { return SafeSubjectRaw; }
    /** UPROPERTYありのTWeakObjectPtrによるSubject参照を取得 */
    TWeakObjectPtr<USubject> GetSafeSubjectWeak() const { return SafeSubjectWeak; }
    /** UPROPERTYありの生ポインタ配列によるSubject参照を取得 */
    const TArray<USubject*>& GetSafeSubjectRawArray() const { return SafeSubjectRawArray; }
    /** UPROPERTYありのTObjectPtr配列によるSubject参照を取得 */
    const TArray<TObjectPtr<USubject>>& GetSafeSubjectPtrArray() const { return SafeSubjectPtrArray; }
    /** UPROPERTYありのTWeakObjectPtr配列によるSubject参照を取得 */
    const TArray<TWeakObjectPtr<USubject>>& GetSafeSubjectWeakArray() const { return SafeSubjectWeakArray; }
    /** UPROPERTYありのTObjectPtrマップによるSubject参照を取得 */
    const TMap<int32, TObjectPtr<USubject>>& GetSafeSubjectPtrMap() const { return SafeSubjectPtrMap; }
    /** UPROPERTYありの生ポインタマップによるSubject参照を取得 */
    const TMap<int32, USubject*>& GetSafeSubjectRawMap() const { return SafeSubjectRawMap; }
    /** UPROPERTYありのTWeakObjectPtrマップによるSubject参照を取得 */
    const TMap<int32, TWeakObjectPtr<USubject>>& GetSafeSubjectWeakMap() const { return SafeSubjectWeakMap; }


    // --------------------------------------------------------------
    // AActorSubject関連のメソッド
    // --------------------------------------------------------------

    /// <summary>
    ///  テストケースに応じたActorSubject生成関数
    /// </summary>
    /// <param name="InStorageLocation"></param>
    /// <param name="bProperty"></param>
    /// <param name="InNum"></param>
    void SpawnActorSubject(const EStorageLocation InStorageLocation, bool bProperty, const int32 InNum);

    /** UPROPERTYなしのTObjectPtrによるActorSubject参照を取得 */
    TObjectPtr<AActorSubject> GetUnSafeActorSubjectPtr() const { return UnSafeActorSubjectPtr; }
    /** UPROPERTYなしの生ポインタによるActorSubject参照を取得 */
    AActorSubject* GetUnSafeActorSubjectRaw() const { return UnSafeActorSubjectRaw; }
    /** UPROPERTYなしのTWeakObjectPtrによるActorSubject参照を取得 */
    TWeakObjectPtr<AActorSubject> GetUnSafeActorSubjectWeak() const { return UnSafeActorSubjectWeak; }
    /** UPROPERTYなしの生ポインタ配列によるActorSubject参照を取得 */
    const TArray<AActorSubject*>& GetUnSafeActorSubjectRawArray() const { return UnSafeActorSubjectRawArray; }
    /** UPROPERTYなしのTObjectPtr配列によるActorSubject参照を取得 */
    const TArray<TObjectPtr<AActorSubject>>& GetUnSafeActorSubjectPtrArray() const { return UnSafeActorSubjectPtrArray; }
    /** UPROPERTYなしのTWeakObjectPtr配列によるActorSubject参照を取得 */
    const TArray<TWeakObjectPtr<AActorSubject>>& GetUnSafeActorSubjectWeakArray() const { return UnSafeActorSubjectWeakArray; }
    /** UPROPERTYなしのTObjectPtrマップによるActorSubject参照を取得 */
    const TMap<int32, TObjectPtr<AActorSubject>>& GetUnSafeActorSubjectPtrMap() const { return UnSafeActorSubjectPtrMap; }
    /** UPROPERTYなしの生ポインタマップによるActorSubject参照を取得 */
    const TMap<int32, AActorSubject*>& GetUnSafeActorSubjectRawMap() const { return UnSafeActorSubjectRawMap; }
    /** UPROPERTYなしのTWeakObjectPtrマップによるActorSubject参照を取得 */
    const TMap<int32, TWeakObjectPtr<AActorSubject>>& GetUnSafeActorSubjectWeakMap() const { return UnSafeActorSubjectWeakMap; }

    /** UPROPERTYありのTObjectPtrによるActorSubject参照を取得 */
    TObjectPtr<AActorSubject> GetSafeActorSubjectPtr() const { return SafeActorSubjectPtr; }
    /** UPROPERTYありの生ポインタによるActorSubject参照を取得 */
    AActorSubject* GetSafeActorSubjectRaw() const { return SafeActorSubjectRaw; }
    /** UPROPERTYありのTWeakObjectPtrによるActorSubject参照を取得 */
    TWeakObjectPtr<AActorSubject> GetSafeActorSubjectWeak() const { return SafeActorSubjectWeak; }
    /** UPROPERTYありの生ポインタ配列によるActorSubject参照を取得 */
    const TArray<AActorSubject*>& GetSafeActorSubjectRawArray() const { return SafeActorSubjectRawArray; }
    /** UPROPERTYありのTObjectPtr配列によるActorSubject参照を取得 */
    const TArray<TObjectPtr<AActorSubject>>& GetSafeActorSubjectPtrArray() const { return SafeActorSubjectPtrArray; }
    /** UPROPERTYありのTWeakObjectPtr配列によるActorSubject参照を取得 */
    const TArray<TWeakObjectPtr<AActorSubject>>& GetSafeActorSubjectWeakArray() const { return SafeActorSubjectWeakArray; }
    /** UPROPERTYありのTObjectPtrマップによるActorSubject参照を取得 */
    const TMap<int32, TObjectPtr<AActorSubject>>& GetSafeActorSubjectPtrMap() const { return SafeActorSubjectPtrMap; }
    /** UPROPERTYありの生ポインタマップによるActorSubject参照を取得 */
    const TMap<int32, AActorSubject*>& GetSafeActorSubjectRawMap() const { return SafeActorSubjectRawMap; }
    /** UPROPERTYありのTWeakObjectPtrマップによるActorSubject参照を取得 */
    const TMap<int32, TWeakObjectPtr<AActorSubject>>& GetSafeActorSubjectWeakMap() const { return SafeActorSubjectWeakMap; }


    // --------------------------------------------------------------
    // 参照カット関連のメソッド
    // --------------------------------------------------------------

    /// <summary>
    /// 全ての格納先に対してnullptr代入を行う。
    /// </summary>
    void SetNullptrToAllSubjects();

    /// <summary>
    /// コンテナ格納先に対してReset/Empty呼び出しを行う。
    /// </summary>
    void ResetToAllContainerSubjects();

    /// <summary>
    /// AActor格納先の各要素でDestroy呼び出しを行う。
    /// </summary>
    void CallDestroyToAllSubjects();

private:

    // USubect

    // --- Unsafe（UPROPERTYなし） ---

    /** UPROPERTYなしのTObjectPtrによるSubject参照 */
    TObjectPtr<USubject> UnSafeSubjectPtr{};
    /** UPROPERTYなしの生ポインタによるSubject参照 */
    USubject* UnSafeSubjectRaw{};
    /** UPROPERTYなしのTWeakObjectPtrによるSubject参照 */
    TWeakObjectPtr<USubject> UnSafeSubjectWeak{};
    /** UPROPERTYなしの生ポインタ配列によるSubject参照 */
    TArray<USubject*> UnSafeSubjectRawArray{};
    /** UPROPERTYなしのTObjectPtr配列によるSubject参照 */
    TArray<TObjectPtr<USubject>> UnSafeSubjectPtrArray{};
    /** UPROPERTYなしのTWeakObjectPtr配列によるSubject参照 */
    TArray<TWeakObjectPtr<USubject>> UnSafeSubjectWeakArray{};
    /** UPROPERTYなしのTObjectPtrマップによるSubject参照 */
    TMap<int32, TObjectPtr<USubject>> UnSafeSubjectPtrMap{};
    /** UPROPERTYなしの生ポインタマップによるSubject参照 */
    TMap<int32, USubject*> UnSafeSubjectRawMap{};
    /** UPROPERTYなしのTWeakObjectPtrマップによるSubject参照 */
    TMap<int32, TWeakObjectPtr<USubject>> UnSafeSubjectWeakMap{};

    // --- Safe（UPROPERTYあり） ---
    /** UPROPERTYありのTObjectPtrによるSubject参照 */
    UPROPERTY()
    TObjectPtr<USubject> SafeSubjectPtr{};
    /** UPROPERTYありの生ポインタによるSubject参照 */
    UPROPERTY()
    USubject* SafeSubjectRaw{};
    /** UPROPERTYありのTWeakObjectPtrによるSubject参照 */
    UPROPERTY()
    TWeakObjectPtr<USubject> SafeSubjectWeak{};
    /** UPROPERTYありの生ポインタ配列によるSubject参照 */
    UPROPERTY()
    TArray<USubject*> SafeSubjectRawArray{};
    /** UPROPERTYありのTObjectPtr配列によるSubject参照 */
    UPROPERTY()
    TArray<TObjectPtr<USubject>> SafeSubjectPtrArray{};
    /** UPROPERTYありのTWeakObjectPtr配列によるSubject参照 */
    UPROPERTY()
    TArray<TWeakObjectPtr<USubject>> SafeSubjectWeakArray{};
    /** UPROPERTYありのTObjectPtrマップによるSubject参照 */
    UPROPERTY()
    TMap<int32, TObjectPtr<USubject>> SafeSubjectPtrMap{};
    /** UPROPERTYありの生ポインタマップによるSubject参照 */
    UPROPERTY()
    TMap<int32, USubject*> SafeSubjectRawMap{};
    /** UPROPERTYありのTWeakObjectPtrマップによるSubject参照 */
    UPROPERTY()
    TMap<int32, TWeakObjectPtr<USubject>> SafeSubjectWeakMap{};


    // AActorActorSubject
    // --- Unsafe（UPROPERTYなし） ---
    /** UPROPERTYなしのTObjectPtrによるActorSubject参照 */
    TObjectPtr<AActorSubject> UnSafeActorSubjectPtr{};
    /** UPROPERTYなしの生ポインタによるActorSubject参照 */
    AActorSubject* UnSafeActorSubjectRaw{};
    /** UPROPERTYなしのTWeakObjectPtrによるActorSubject参照 */
    TWeakObjectPtr<AActorSubject> UnSafeActorSubjectWeak{};
    /** UPROPERTYなしの生ポインタ配列によるActorSubject参照 */
    TArray<AActorSubject*> UnSafeActorSubjectRawArray{};
    /** UPROPERTYなしのTObjectPtr配列によるActorSubject参照 */
    TArray<TObjectPtr<AActorSubject>> UnSafeActorSubjectPtrArray{};
    /** UPROPERTYなしのTWeakObjectPtr配列によるActorSubject参照 */
    TArray<TWeakObjectPtr<AActorSubject>> UnSafeActorSubjectWeakArray{};
    /** UPROPERTYなしのTObjectPtrマップによるActorSubject参照 */
    TMap<int32, TObjectPtr<AActorSubject>> UnSafeActorSubjectPtrMap{};
    /** UPROPERTYなしの生ポインタマップによるActorSubject参照 */
    TMap<int32, AActorSubject*> UnSafeActorSubjectRawMap{};
    /** UPROPERTYなしのTWeakObjectPtrマップによるActorSubject参照 */
    TMap<int32, TWeakObjectPtr<AActorSubject>> UnSafeActorSubjectWeakMap{};

    // --- Safe（UPROPERTYあり） ---
    /** UPROPERTYありのTObjectPtrによるActorSubject参照 */
    UPROPERTY()
    TObjectPtr<AActorSubject> SafeActorSubjectPtr{};
    /** UPROPERTYありの生ポインタによるActorSubject参照 */
    UPROPERTY()
    AActorSubject* SafeActorSubjectRaw{};
    /** UPROPERTYありのTWeakObjectPtrによるActorSubject参照 */
    UPROPERTY()
    TWeakObjectPtr<AActorSubject> SafeActorSubjectWeak{};
    /** UPROPERTYありの生ポインタ配列によるActorSubject参照 */
    UPROPERTY()
    TArray<AActorSubject*> SafeActorSubjectRawArray{};
    /** UPROPERTYありのTObjectPtr配列によるActorSubject参照 */
    UPROPERTY()
    TArray<TObjectPtr<AActorSubject>> SafeActorSubjectPtrArray{};
    /** UPROPERTYありのTWeakObjectPtr配列によるActorSubject参照 */
    UPROPERTY()
    TArray<TWeakObjectPtr<AActorSubject>> SafeActorSubjectWeakArray{};
    /** UPROPERTYありのTObjectPtrマップによるActorSubject参照 */
    UPROPERTY()
    TMap<int32, TObjectPtr<AActorSubject>> SafeActorSubjectPtrMap{};
    /** UPROPERTYありの生ポインタマップによるActorSubject参照 */
    UPROPERTY()
    TMap<int32, AActorSubject*> SafeActorSubjectRawMap{};
    /** UPROPERTYありのTWeakObjectPtrマップによるActorSubject参照 */
    UPROPERTY()
    TMap<int32, TWeakObjectPtr<AActorSubject>> SafeActorSubjectWeakMap{};


};
