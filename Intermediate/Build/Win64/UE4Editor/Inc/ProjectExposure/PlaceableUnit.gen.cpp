// Copyright 1998-2018 Epic Games, Inc. All Rights Reserved.
/*===========================================================================
	Generated code exported from UnrealHeaderTool.
	DO NOT modify this manually! Edit the corresponding .h files instead!
===========================================================================*/

#include "GeneratedCppIncludes.h"
#include "PlaceableUnit.h"
#ifdef _MSC_VER
#pragma warning (push)
#pragma warning (disable : 4883)
#endif
PRAGMA_DISABLE_DEPRECATION_WARNINGS
void EmptyLinkFunctionForGeneratedCodePlaceableUnit() {}
// Cross Module References
	PROJECTEXPOSURE_API UClass* Z_Construct_UClass_APlaceableUnit_NoRegister();
	PROJECTEXPOSURE_API UClass* Z_Construct_UClass_APlaceableUnit();
	ENGINE_API UClass* Z_Construct_UClass_APawn();
	UPackage* Z_Construct_UPackage__Script_ProjectExposure();
// End Cross Module References
	void APlaceableUnit::StaticRegisterNativesAPlaceableUnit()
	{
	}
	UClass* Z_Construct_UClass_APlaceableUnit_NoRegister()
	{
		return APlaceableUnit::StaticClass();
	}
	UClass* Z_Construct_UClass_APlaceableUnit()
	{
		static UClass* OuterClass = nullptr;
		if (!OuterClass)
		{
			static UObject* (*const DependentSingletons[])() = {
				(UObject* (*)())Z_Construct_UClass_APawn,
				(UObject* (*)())Z_Construct_UPackage__Script_ProjectExposure,
			};
#if WITH_METADATA
			static const UE4CodeGen_Private::FMetaDataPairParam Class_MetaDataParams[] = {
				{ "HideCategories", "Navigation" },
				{ "IncludePath", "PlaceableUnit.h" },
				{ "ModuleRelativePath", "PlaceableUnit.h" },
			};
#endif
			static const FCppClassTypeInfoStatic StaticCppClassTypeInfo = {
				TCppClassTypeTraits<APlaceableUnit>::IsAbstract,
			};
			static const UE4CodeGen_Private::FClassParams ClassParams = {
				&APlaceableUnit::StaticClass,
				DependentSingletons, ARRAY_COUNT(DependentSingletons),
				0x00900080u,
				nullptr, 0,
				nullptr, 0,
				nullptr,
				&StaticCppClassTypeInfo,
				nullptr, 0,
				METADATA_PARAMS(Class_MetaDataParams, ARRAY_COUNT(Class_MetaDataParams))
			};
			UE4CodeGen_Private::ConstructUClass(OuterClass, ClassParams);
		}
		return OuterClass;
	}
	IMPLEMENT_CLASS(APlaceableUnit, 2050191771);
	static FCompiledInDefer Z_CompiledInDefer_UClass_APlaceableUnit(Z_Construct_UClass_APlaceableUnit, &APlaceableUnit::StaticClass, TEXT("/Script/ProjectExposure"), TEXT("APlaceableUnit"), false, nullptr, nullptr, nullptr);
	DEFINE_VTABLE_PTR_HELPER_CTOR(APlaceableUnit);
PRAGMA_ENABLE_DEPRECATION_WARNINGS
#ifdef _MSC_VER
#pragma warning (pop)
#endif
