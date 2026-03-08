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
    // UPROPETY付きの格納先への生成
	if(bProperty)
	{
		switch (InStorageLocation)
		{
		case EStorageLocation::Ptr:
			SafeSubjectPtr = NewObject<USubject>();
			break;
		case EStorageLocation::Raw:
			SafeSubjectRaw = NewObject<USubject>();
			break;
		case EStorageLocation::Weak:
			SafeSubjectWeak = NewObject<USubject>();
			break;
		case EStorageLocation::RawArray:
			for (int32 i = 0; i < InNum; ++i)
			{
				SafeSubjectRawArray.Add(NewObject<USubject>());
			}
			break;
		case EStorageLocation::PtrArray:
			for (int32 i = 0; i < InNum; ++i)
			{
				SafeSubjectPtrArray.Add(NewObject<USubject>());
			}
			break;
		case EStorageLocation::WeakArray:
			for (int32 i = 0; i < InNum; ++i)
			{
				SafeSubjectWeakArray.Add(NewObject<USubject>());
			}
			break;
		case EStorageLocation::PtrMap:
			for (int32 i = 0; i < InNum; ++i)
			{
				SafeSubjectPtrMap.Add(i, NewObject<USubject>());
			}
			break;
		case EStorageLocation::RawMap:
			for (int32 i = 0; i < InNum; ++i)
			{
				SafeSubjectRawMap.Add(i, NewObject<USubject>());
			}
			break;
		case EStorageLocation::WeakMap:
			for (int32 i = 0; i < InNum; ++i)
			{
				SafeSubjectWeakMap.Add(i, NewObject<USubject>());
			}
			break;
		}
	}
	// UPROPETYなしの格納先への生成
	else
	{
		switch (InStorageLocation)
		{
		case EStorageLocation::Ptr:
			UnSafeSubjectPtr = NewObject<USubject>();
			break;
		case EStorageLocation::Raw:
			UnSafeSubjectRaw = NewObject<USubject>();
			break;
		case EStorageLocation::Weak:
			UnSafeSubjectWeak = NewObject<USubject>();
			break;
		case EStorageLocation::RawArray:
			for (int32 i = 0; i < InNum; ++i)
			{
				UnSafeSubjectRawArray.Add(NewObject<USubject>());
			}
			break;
		case EStorageLocation::PtrArray:
			for (int32 i = 0; i < InNum; ++i)
			{
				UnSafeSubjectPtrArray.Add(NewObject<USubject>());
			}
			break;
		case EStorageLocation::WeakArray:
			for (int32 i = 0; i < InNum; ++i)
			{
				UnSafeSubjectWeakArray.Add(NewObject<USubject>());
			}
			break;
		case EStorageLocation::PtrMap:
			for (int32 i = 0; i < InNum; ++i)
			{
				UnSafeSubjectPtrMap.Add(i, NewObject<USubject>());
			}
			break;
		case EStorageLocation::RawMap:
			for (int32 i = 0; i < InNum; ++i)
			{
				UnSafeSubjectRawMap.Add(i, NewObject<USubject>());
			}
			break;
		case EStorageLocation::WeakMap:
			for (int32 i = 0; i < InNum; ++i)
			{
				UnSafeSubjectWeakMap.Add(i, NewObject<USubject>());
			}
			break;
		}
    }
}

/// <summary>
/// 全ての格納先に対して、可能な限りnullptr代入を行う。
/// </summary>
void AHolderActor::TrySetNullptrToAllSubjects()
{
	// Unsafe
	UnSafeSubjectPtr = nullptr;
	UnSafeSubjectRaw = nullptr;
	UnSafeSubjectWeak = nullptr;
	for(auto& Ptr : UnSafeSubjectPtrArray){
		Ptr = nullptr;
    }
	for (auto& Raw : UnSafeSubjectRawArray) {
		Raw = nullptr;
	}
	for (auto& Weak : UnSafeSubjectWeakArray) {
		Weak = nullptr;
	}
	for(auto& Ptr : UnSafeSubjectPtrMap) {
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
}

/// <summary>
/// 全ての格納先に対して、可能な限りReset/Empty呼び出しを行う。
/// </summary>
void AHolderActor::TyyResetToAllSubjects()
{
	// UnSafe
    UnSafeSubjectPtr = nullptr; // TObjectPtrはReset()がないためnullptr代入
    UnSafeSubjectRaw = nullptr; // 生ポインタはReset()がないためnullptr代入
	UnSafeSubjectWeak.Reset();
	UnSafeSubjectRawArray.Empty();
	UnSafeSubjectPtrArray.Empty();
	UnSafeSubjectWeakArray.Empty();
	UnSafeSubjectPtrMap.Empty();
	UnSafeSubjectRawMap.Empty();
	UnSafeSubjectWeakMap.Empty();

	// Safe
	SafeSubjectPtr = nullptr; // TObjectPtrはReset()がないためnullptr代入
	SafeSubjectRaw = nullptr;  // 生ポインタはReset()がないためnullptr代入
	SafeSubjectWeak.Reset();
	SafeSubjectRawArray.Empty();
	SafeSubjectPtrArray.Empty();
	SafeSubjectWeakArray.Empty();
	SafeSubjectPtrMap.Empty();
	SafeSubjectRawMap.Empty();
	SafeSubjectWeakMap.Empty();
}
