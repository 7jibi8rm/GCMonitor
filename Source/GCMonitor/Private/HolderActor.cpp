// Fill out your copyright notice in the Description page of Project Settings.


#include "HolderActor.h"

// Sets default values
AHolderActor::AHolderActor()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
}

/// <summary>
/// テストケースに応じたSubject生成関数
/// </summary>
/// <param name="InStorageLocation">格納先</param>
/// <param name="InNum"></param>
void AHolderActor::GenerateSubject(const EStorageLocation InStorageLocation, bool bProperty, const int32 InNum)
{
    // --- Unsafe（UPROPERTYなし）用生成ラムダ ---
    // 各格納先ごとにUSubjectインスタンスを生成し、対応するメンバへ格納する
    auto GenerateUnSafeSubjectPtr = [&]() {
        // TObjectPtrによる格納
        UnSafeSubjectPtr = NewObject<USubject>();
    };
    auto GenerateUnSafeSubjectRaw = [&]() {
        // 生ポインタによる格納
        UnSafeSubjectRaw = NewObject<USubject>();
    };
    auto GenerateUnSafeSubjectWeak = [&]() {
        // TWeakObjectPtrによる格納
        UnSafeSubjectWeak = NewObject<USubject>();
    };
    auto GenerateUnSafeSubjectPtrArray = [&]() {
        // TObjectPtr配列による格納
        UnSafeSubjectPtrArray.Empty();
        for (int32 i = 0; i < InNum; ++i) {
            UnSafeSubjectPtrArray.Add(NewObject<USubject>());
        }
    };
    auto GenerateUnSafeSubjectRawArray = [&]() {
        // 生ポインタ配列による格納
        UnSafeSubjectRawArray.Empty();
        for (int32 i = 0; i < InNum; ++i) {
            UnSafeSubjectRawArray.Add(NewObject<USubject>());
        }
    };
    auto GenerateUnSafeSubjectWeakArray = [&]() {
        // TWeakObjectPtr配列による格納
        UnSafeSubjectWeakArray.Empty();
        for (int32 i = 0; i < InNum; ++i) {
            UnSafeSubjectWeakArray.Add(NewObject<USubject>());
        }
    };
    auto GenerateUnSafeSubjectPtrMap = [&]() {
        // TObjectPtrマップによる格納
        UnSafeSubjectPtrMap.Empty();
        for (int32 i = 0; i < InNum; ++i) {
            UnSafeSubjectPtrMap.Add(i, NewObject<USubject>());
        }
    };
    auto GenerateUnSafeSubjectRawMap = [&]() {
        // 生ポインタマップによる格納
        UnSafeSubjectRawMap.Empty();
        for (int32 i = 0; i < InNum; ++i) {
            UnSafeSubjectRawMap.Add(i, NewObject<USubject>());
        }
    };
    auto GenerateUnSafeSubjectWeakMap = [&]() {
        // TWeakObjectPtrマップによる格納
        UnSafeSubjectWeakMap.Empty();
        for (int32 i = 0; i < InNum; ++i) {
            UnSafeSubjectWeakMap.Add(i, NewObject<USubject>());
        }
    };

    // --- Safe（UPROPERTYあり）用生成ラムダ ---
    // 各格納先ごとにUSubjectインスタンスを生成し、UPROPERTY付きメンバへ格納する
    auto GenerateSafeSubjectPtr = [&]() {
        SafeSubjectPtr = NewObject<USubject>();
    };
    auto GenerateSafeSubjectRaw = [&]() {
        SafeSubjectRaw = NewObject<USubject>();
    };
    auto GenerateSafeSubjectWeak = [&]() {
        SafeSubjectWeak = NewObject<USubject>();
    };
    auto GenerateSafeSubjectPtrArray = [&]() {
        SafeSubjectPtrArray.Empty();
        for (int32 i = 0; i < InNum; ++i) {
            SafeSubjectPtrArray.Add(NewObject<USubject>());
        }
    };
    auto GenerateSafeSubjectRawArray = [&]() {
        SafeSubjectRawArray.Empty();
        for (int32 i = 0; i < InNum; ++i) {
            SafeSubjectRawArray.Add(NewObject<USubject>());
        }
    };
    auto GenerateSafeSubjectWeakArray = [&]() {
        SafeSubjectWeakArray.Empty();
        for (int32 i = 0; i < InNum; ++i) {
            SafeSubjectWeakArray.Add(NewObject<USubject>());
        }
    };
    auto GenerateSafeSubjectPtrMap = [&]() {
        SafeSubjectPtrMap.Empty();
        for (int32 i = 0; i < InNum; ++i) {
            SafeSubjectPtrMap.Add(i, NewObject<USubject>());
        }
    };
    auto GenerateSafeSubjectRawMap = [&]() {
        SafeSubjectRawMap.Empty();
        for (int32 i = 0; i < InNum; ++i) {
            SafeSubjectRawMap.Add(i, NewObject<USubject>());
        }
    };
    auto GenerateSafeSubjectWeakMap = [&]() {
        SafeSubjectWeakMap.Empty();
        for (int32 i = 0; i < InNum; ++i) {
            SafeSubjectWeakMap.Add(i, NewObject<USubject>());
        }
    };

    // 格納先ごとに生成処理をまとめたマップ
    TMap<EStorageLocation, TFunction<void()>> GenerateSafeFunctions = {
        {EStorageLocation::Ptr, GenerateSafeSubjectPtr},
        {EStorageLocation::Raw, GenerateSafeSubjectRaw},
        {EStorageLocation::Weak, GenerateSafeSubjectWeak},
        {EStorageLocation::PtrArray, GenerateSafeSubjectPtrArray},
        {EStorageLocation::RawArray, GenerateSafeSubjectRawArray},
        {EStorageLocation::WeakArray, GenerateSafeSubjectWeakArray},
        {EStorageLocation::PtrMap, GenerateSafeSubjectPtrMap},
        {EStorageLocation::RawMap, GenerateSafeSubjectRawMap},
        {EStorageLocation::WeakMap, GenerateSafeSubjectWeakMap}
    };
    TMap<EStorageLocation, TFunction<void()>> GenerateUnsafeFunctions = {
        {EStorageLocation::Ptr, GenerateUnSafeSubjectPtr},
        {EStorageLocation::Raw, GenerateUnSafeSubjectRaw},
        {EStorageLocation::Weak, GenerateUnSafeSubjectWeak},
        {EStorageLocation::PtrArray, GenerateUnSafeSubjectPtrArray},
        {EStorageLocation::RawArray, GenerateUnSafeSubjectRawArray},
        {EStorageLocation::WeakArray, GenerateUnSafeSubjectWeakArray},
        {EStorageLocation::PtrMap, GenerateUnSafeSubjectPtrMap},
        {EStorageLocation::RawMap, GenerateUnSafeSubjectRawMap},
        {EStorageLocation::WeakMap, GenerateUnSafeSubjectWeakMap}
    };

    // --- 実際の生成処理 ---
    // bProperty（UPROPERTY有無）に応じて、格納先の生成ラムダを呼び出す
    if (bProperty)
    {
        if (GenerateSafeFunctions.Contains(InStorageLocation))
        {
            GenerateSafeFunctions[InStorageLocation]();
        }
    }
    else
    {
        if (GenerateUnsafeFunctions.Contains(InStorageLocation))
        {
            GenerateUnsafeFunctions[InStorageLocation]();
        }
    }
}

/// <summary>
///  テストケースに応じたActorSubject生成関数
/// </summary>
/// <param name="InStorageLocation"></param>
/// <param name="bProperty"></param>
/// <param name="InNum"></param>
void AHolderActor::SpawnActorSubject(const EStorageLocation InStorageLocation, bool bProperty, const int32 InNum)
{
    if(GetWorld() == nullptr){
        UE_LOG(LogTemp, Warning, TEXT("AHolderActor::SpawnActorSubject - GetWorld() is null. Cannot spawn actors."));
        return; 
    }

    // --- Unsafe（UPROPERTYなし）用生成ラムダ ---
    // 各格納先ごとにAActorSubjectインスタンスを生成し、対応するメンバへ格納する
    auto GenerateUnSafeActorSubjectPtr = [&]() {
        // TObjectPtrによる格納
        UnSafeActorSubjectPtr = GetWorld()->SpawnActor<AActorSubject>();
        };
    auto GenerateUnSafeActorSubjectRaw = [&]() {
        // 生ポインタによる格納
        UnSafeActorSubjectRaw = GetWorld()->SpawnActor<AActorSubject>();
        };
    auto GenerateUnSafeActorSubjectWeak = [&]() {
        // TWeakObjectPtrによる格納
        UnSafeActorSubjectWeak = GetWorld()->SpawnActor<AActorSubject>();
        };
    auto GenerateUnSafeActorSubjectPtrArray = [&]() {
        // TObjectPtr配列による格納
        UnSafeActorSubjectPtrArray.Empty();
        for (int32 i = 0; i < InNum; ++i) {
            UnSafeActorSubjectPtrArray.Add(GetWorld()->SpawnActor<AActorSubject>());
        }
        };
    auto GenerateUnSafeActorSubjectRawArray = [&]() {
        // 生ポインタ配列による格納
        UnSafeActorSubjectRawArray.Empty();
        for (int32 i = 0; i < InNum; ++i) {
            UnSafeActorSubjectRawArray.Add(GetWorld()->SpawnActor<AActorSubject>());
        }
        };
    auto GenerateUnSafeActorSubjectWeakArray = [&]() {
        // TWeakObjectPtr配列による格納
        UnSafeActorSubjectWeakArray.Empty();
        for (int32 i = 0; i < InNum; ++i) {
            UnSafeActorSubjectWeakArray.Add(GetWorld()->SpawnActor<AActorSubject>());
        }
        };
    auto GenerateUnSafeActorSubjectPtrMap = [&]() {
        // TObjectPtrマップによる格納
        UnSafeActorSubjectPtrMap.Empty();
        for (int32 i = 0; i < InNum; ++i) {
            UnSafeActorSubjectPtrMap.Add(i, GetWorld()->SpawnActor<AActorSubject>());
        }
        };
    auto GenerateUnSafeActorSubjectRawMap = [&]() {
        // 生ポインタマップによる格納
        UnSafeActorSubjectRawMap.Empty();
        for (int32 i = 0; i < InNum; ++i) {
            UnSafeActorSubjectRawMap.Add(i, GetWorld()->SpawnActor<AActorSubject>());
        }
        };
    auto GenerateUnSafeActorSubjectWeakMap = [&]() {
        // TWeakObjectPtrマップによる格納
        UnSafeActorSubjectWeakMap.Empty();
        for (int32 i = 0; i < InNum; ++i) {
            UnSafeActorSubjectWeakMap.Add(i, GetWorld()->SpawnActor<AActorSubject>());
        }
        };

    // --- Safe（UPROPERTYあり）用生成ラムダ ---
    // 各格納先ごとにUActorSubjectインスタンスを生成し、UPROPERTY付きメンバへ格納する
    auto GenerateSafeActorSubjectPtr = [&]() {
        SafeActorSubjectPtr = GetWorld()->SpawnActor<AActorSubject>();
        };
    auto GenerateSafeActorSubjectRaw = [&]() {
        SafeActorSubjectRaw = GetWorld()->SpawnActor<AActorSubject>();
        };
    auto GenerateSafeActorSubjectWeak = [&]() {
        SafeActorSubjectWeak = GetWorld()->SpawnActor<AActorSubject>();
        };
    auto GenerateSafeActorSubjectPtrArray = [&]() {
        SafeActorSubjectPtrArray.Empty();
        for (int32 i = 0; i < InNum; ++i) {
            SafeActorSubjectPtrArray.Add(GetWorld()->SpawnActor<AActorSubject>());
        }
        };
    auto GenerateSafeActorSubjectRawArray = [&]() {
        SafeActorSubjectRawArray.Empty();
        for (int32 i = 0; i < InNum; ++i) {
            SafeActorSubjectRawArray.Add(GetWorld()->SpawnActor<AActorSubject>());
        }
        };
    auto GenerateSafeActorSubjectWeakArray = [&]() {
        SafeActorSubjectWeakArray.Empty();
        for (int32 i = 0; i < InNum; ++i) {
            SafeActorSubjectWeakArray.Add(GetWorld()->SpawnActor<AActorSubject>());
        }
        };
    auto GenerateSafeActorSubjectPtrMap = [&]() {
        SafeActorSubjectPtrMap.Empty();
        for (int32 i = 0; i < InNum; ++i) {
            SafeActorSubjectPtrMap.Add(i, GetWorld()->SpawnActor<AActorSubject>());
        }
        };
    auto GenerateSafeActorSubjectRawMap = [&]() {
        SafeActorSubjectRawMap.Empty();
        for (int32 i = 0; i < InNum; ++i) {
            SafeActorSubjectRawMap.Add(i, GetWorld()->SpawnActor<AActorSubject>());
        }
        };
    auto GenerateSafeActorSubjectWeakMap = [&]() {
        SafeActorSubjectWeakMap.Empty();
        for (int32 i = 0; i < InNum; ++i) {
            SafeActorSubjectWeakMap.Add(i, GetWorld()->SpawnActor<AActorSubject>());
        }
        };

    // 格納先ごとに生成処理をまとめたマップ
    TMap<EStorageLocation, TFunction<void()>> GenerateSafeFunctions = {
        {EStorageLocation::Ptr, GenerateSafeActorSubjectPtr},
        {EStorageLocation::Raw, GenerateSafeActorSubjectRaw},
        {EStorageLocation::Weak, GenerateSafeActorSubjectWeak},
        {EStorageLocation::PtrArray, GenerateSafeActorSubjectPtrArray},
        {EStorageLocation::RawArray, GenerateSafeActorSubjectRawArray},
        {EStorageLocation::WeakArray, GenerateSafeActorSubjectWeakArray},
        {EStorageLocation::PtrMap, GenerateSafeActorSubjectPtrMap},
        {EStorageLocation::RawMap, GenerateSafeActorSubjectRawMap},
        {EStorageLocation::WeakMap, GenerateSafeActorSubjectWeakMap}
    };
    TMap<EStorageLocation, TFunction<void()>> GenerateUnsafeFunctions = {
        {EStorageLocation::Ptr, GenerateUnSafeActorSubjectPtr},
        {EStorageLocation::Raw, GenerateUnSafeActorSubjectRaw},
        {EStorageLocation::Weak, GenerateUnSafeActorSubjectWeak},
        {EStorageLocation::PtrArray, GenerateUnSafeActorSubjectPtrArray},
        {EStorageLocation::RawArray, GenerateUnSafeActorSubjectRawArray},
        {EStorageLocation::WeakArray, GenerateUnSafeActorSubjectWeakArray},
        {EStorageLocation::PtrMap, GenerateUnSafeActorSubjectPtrMap},
        {EStorageLocation::RawMap, GenerateUnSafeActorSubjectRawMap},
        {EStorageLocation::WeakMap, GenerateUnSafeActorSubjectWeakMap}
    };

    // --- 実際の生成処理 ---
    // bProperty（UPROPERTY有無）に応じて、格納先の生成ラムダを呼び出す
    if (bProperty)
    {
        if (GenerateSafeFunctions.Contains(InStorageLocation))
        {
            GenerateSafeFunctions[InStorageLocation]();
        }
    }
    else
    {
        if (GenerateUnsafeFunctions.Contains(InStorageLocation))
        {
            GenerateUnsafeFunctions[InStorageLocation]();
        }
    }
}

/// <summary>
/// 全ての格納先に対してnullptr代入を行う。
/// </summary>
void AHolderActor::SetNullptrToAllSubjects()
{
    // ------------------------------------------
    // USubject
    // ------------------------------------------
    // Unsafe
    UnSafeSubjectPtr = nullptr;
    UnSafeSubjectRaw = nullptr;
    UnSafeSubjectWeak = nullptr;
    for (auto& Ptr : UnSafeSubjectPtrArray) {
        Ptr = nullptr;
    }
    for (auto& Raw : UnSafeSubjectRawArray) {
        Raw = nullptr;
    }
    for (auto& Weak : UnSafeSubjectWeakArray) {
        Weak = nullptr;
    }
    for (auto& Ptr : UnSafeSubjectPtrMap) {
        Ptr.Value = nullptr;
    }
    for (auto& Raw : UnSafeSubjectRawMap) {
        Raw.Value = nullptr;
    }
    for (auto& Weak : UnSafeSubjectWeakMap) {
        Weak.Value = nullptr;
    }

    // Safe
    SafeSubjectPtr = nullptr;
    SafeSubjectRaw = nullptr;
    SafeSubjectWeak = nullptr;
    for (auto& Ptr : SafeSubjectPtrArray) {
        Ptr = nullptr;
    }
    for (auto& Raw : SafeSubjectRawArray) {
        Raw = nullptr;
    }
    for (auto& Weak : SafeSubjectWeakArray) {
        Weak = nullptr;
    }
    for (auto& Ptr : SafeSubjectPtrMap) {
        Ptr.Value = nullptr;
    }
    for (auto& Raw : SafeSubjectRawMap) {
        Raw.Value = nullptr;
    }
    for (auto& Weak : SafeSubjectWeakMap) {
        Weak.Value = nullptr;
    }

    // ------------------------------------------
    // AActorSubject
    // ------------------------------------------
    // Unsafe
    UnSafeActorSubjectPtr = nullptr;
    UnSafeActorSubjectRaw = nullptr;
    UnSafeActorSubjectWeak = nullptr;
    for (auto& Ptr : UnSafeActorSubjectPtrArray) {
        Ptr = nullptr;
    }
    for (auto& Raw : UnSafeActorSubjectRawArray) {
        Raw = nullptr;
    }
    for (auto& Weak : UnSafeActorSubjectWeakArray) {
        Weak = nullptr;
    }
    for (auto& Ptr : UnSafeActorSubjectPtrMap) {
        Ptr.Value = nullptr;
    }
    for (auto& Raw : UnSafeActorSubjectRawMap) {
        Raw.Value = nullptr;
    }
    for (auto& Weak : UnSafeActorSubjectWeakMap) {
        Weak.Value = nullptr;
    }

    // Safe
    SafeActorSubjectPtr = nullptr;
    SafeActorSubjectRaw = nullptr;
    SafeActorSubjectWeak = nullptr;
    for (auto& Ptr : SafeActorSubjectPtrArray) {
        Ptr = nullptr;
    }
    for (auto& Raw : SafeActorSubjectRawArray) {
        Raw = nullptr;
    }
    for (auto& Weak : SafeActorSubjectWeakArray) {
        Weak = nullptr;
    }
    for (auto& Ptr : SafeActorSubjectPtrMap) {
        Ptr.Value = nullptr;
    }
    for (auto& Raw : SafeActorSubjectRawMap) {
        Raw.Value = nullptr;
    }
    for (auto& Weak : SafeActorSubjectWeakMap) {
        Weak.Value = nullptr;
    }
}

/// <summary>
/// コンテナ格納先に対してReset/Empty呼び出しを行う。
/// </summary>
void AHolderActor::ResetToAllContainerSubjects()
{
    // ------------------------------------------
    // USubject
    // ------------------------------------------
    // UnSafe
    UnSafeSubjectWeak.Reset();
    UnSafeSubjectRawArray.Empty();
    UnSafeSubjectPtrArray.Empty();
    UnSafeSubjectWeakArray.Empty();
    UnSafeSubjectPtrMap.Empty();
    UnSafeSubjectRawMap.Empty();
    UnSafeSubjectWeakMap.Empty();
    // Safe
    SafeSubjectWeak.Reset();
    SafeSubjectRawArray.Empty();
    SafeSubjectPtrArray.Empty();
    SafeSubjectWeakArray.Empty();
    SafeSubjectPtrMap.Empty();
    SafeSubjectRawMap.Empty();
    SafeSubjectWeakMap.Empty();


    // ------------------------------------------
    // AActorSubject
    // ------------------------------------------
    // UnSafe
    UnSafeActorSubjectWeak.Reset();
    UnSafeActorSubjectRawArray.Empty();
    UnSafeActorSubjectPtrArray.Empty();
    UnSafeActorSubjectWeakArray.Empty();
    UnSafeActorSubjectPtrMap.Empty();
    UnSafeActorSubjectRawMap.Empty();
    UnSafeActorSubjectWeakMap.Empty();
    // Safe
    SafeActorSubjectWeak.Reset();
    SafeActorSubjectRawArray.Empty();
    SafeActorSubjectPtrArray.Empty();
    SafeActorSubjectWeakArray.Empty();
    SafeActorSubjectPtrMap.Empty();
    SafeActorSubjectRawMap.Empty();
    SafeActorSubjectWeakMap.Empty();
}

/// <summary>
/// AActor格納先の各要素でDestroy呼び出しを行う。
/// </summary>
void AHolderActor::CallDestroyToAllSubjects()
{
    // Unsafe
    if (UnSafeActorSubjectPtr){
        UnSafeActorSubjectPtr->Destroy();
    }
    if (UnSafeActorSubjectRaw){
         UnSafeActorSubjectRaw->Destroy();
    }
    if (UnSafeActorSubjectWeak.IsValid()){
         UnSafeActorSubjectWeak.Get()->Destroy();
    }
    for (AActorSubject* Ptr : UnSafeActorSubjectPtrArray){
        if (Ptr){
            Ptr->Destroy();
        }
    }
    for (AActorSubject* Raw : UnSafeActorSubjectRawArray){
        if (Raw){
            Raw->Destroy();
        }
    }
    for (TWeakObjectPtr<AActorSubject> Weak : UnSafeActorSubjectWeakArray){
        if (Weak.IsValid()){
            Weak.Get()->Destroy();
        }
    }
    for (const auto& Pair : UnSafeActorSubjectPtrMap){
        if (Pair.Value){
            Pair.Value->Destroy();
        }
    }
    for (const auto& Pair : UnSafeActorSubjectRawMap){
        if (Pair.Value){
            Pair.Value->Destroy();
        }
    }
    for (const auto& Pair : UnSafeActorSubjectWeakMap){
        if (Pair.Value.IsValid()){
            Pair.Value.Get()->Destroy();
        }
    }

    // Safe
    if (SafeActorSubjectPtr){
        SafeActorSubjectPtr->Destroy();
    }
    if (SafeActorSubjectRaw){
        SafeActorSubjectRaw->Destroy();
    }
    if (SafeActorSubjectWeak.IsValid()){
        SafeActorSubjectWeak.Get()->Destroy();
    }
    for (AActorSubject* Ptr : SafeActorSubjectPtrArray){
        if (Ptr){
            Ptr->Destroy();
        }
    }
    for (AActorSubject* Raw : SafeActorSubjectRawArray){
        if (Raw){
            Raw->Destroy();
        }
    }
    for (TWeakObjectPtr<AActorSubject> Weak : SafeActorSubjectWeakArray){
        if (Weak.IsValid()){
            Weak.Get()->Destroy();
        }
    }
    for (const auto& Pair : SafeActorSubjectPtrMap){
        if (Pair.Value){
            Pair.Value->Destroy();
        }
    }
    for (const auto& Pair : SafeActorSubjectRawMap){
        if (Pair.Value){
            Pair.Value->Destroy();
        }
    }
    for (const auto& Pair : SafeActorSubjectWeakMap){
        if (Pair.Value.IsValid()){
            Pair.Value.Get()->Destroy();
        }
    }
}
