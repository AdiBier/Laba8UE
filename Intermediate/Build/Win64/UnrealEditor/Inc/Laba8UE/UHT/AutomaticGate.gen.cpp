// Copyright Epic Games, Inc. All Rights Reserved.
/*===========================================================================
	Generated code exported from UnrealHeaderTool.
	DO NOT modify this manually! Edit the corresponding .h files instead!
===========================================================================*/

#include "UObject/GeneratedCppIncludes.h"
#include "AutomaticGate.h"

PRAGMA_DISABLE_DEPRECATION_WARNINGS
static_assert(!UE_WITH_CONSTINIT_UOBJECT, "This generated code can only be compiled with !UE_WITH_CONSTINIT_OBJECT");
void EmptyLinkFunctionForGeneratedCodeAutomaticGate() {}

// ********** Begin Cross Module References ********************************************************
ENGINE_API UClass* Z_Construct_UClass_AActor();
ENGINE_API UClass* Z_Construct_UClass_USceneComponent_NoRegister();
ENGINE_API UClass* Z_Construct_UClass_UStaticMeshComponent_NoRegister();
LABA8UE_API UClass* Z_Construct_UClass_AAutomaticGate();
LABA8UE_API UClass* Z_Construct_UClass_AAutomaticGate_NoRegister();
LABA8UE_API UClass* Z_Construct_UClass_ALaba8UECharacter_NoRegister();
UPackage* Z_Construct_UPackage__Script_Laba8UE();
// ********** End Cross Module References **********************************************************

// ********** Begin Class AAutomaticGate Function CloseGate ****************************************
struct Z_Construct_UFunction_AAutomaticGate_CloseGate_Statics
{
#if WITH_METADATA
	static constexpr UECodeGen_Private::FMetaDataPairParam Function_MetaDataParams[] = {
		{ "Category", "Gate|Control" },
#if !UE_BUILD_SHIPPING
		{ "Comment", "/** Zamknij wrota */" },
#endif
		{ "ModuleRelativePath", "AutomaticGate.h" },
#if !UE_BUILD_SHIPPING
		{ "ToolTip", "Zamknij wrota" },
#endif
	};
#endif // WITH_METADATA

// ********** Begin Function CloseGate constinit property declarations *****************************
// ********** End Function CloseGate constinit property declarations *******************************
	static const UECodeGen_Private::FFunctionParams FuncParams;
};
const UECodeGen_Private::FFunctionParams Z_Construct_UFunction_AAutomaticGate_CloseGate_Statics::FuncParams = { { (UObject*(*)())Z_Construct_UClass_AAutomaticGate, nullptr, "CloseGate", 	nullptr, 
	0, 
0,
RF_Public|RF_Transient|RF_MarkAsNative, (EFunctionFlags)0x04020401, 0, 0, METADATA_PARAMS(UE_ARRAY_COUNT(Z_Construct_UFunction_AAutomaticGate_CloseGate_Statics::Function_MetaDataParams), Z_Construct_UFunction_AAutomaticGate_CloseGate_Statics::Function_MetaDataParams)},  };
UFunction* Z_Construct_UFunction_AAutomaticGate_CloseGate()
{
	static UFunction* ReturnFunction = nullptr;
	if (!ReturnFunction)
	{
		UECodeGen_Private::ConstructUFunction(&ReturnFunction, Z_Construct_UFunction_AAutomaticGate_CloseGate_Statics::FuncParams);
	}
	return ReturnFunction;
}
DEFINE_FUNCTION(AAutomaticGate::execCloseGate)
{
	P_FINISH;
	P_NATIVE_BEGIN;
	P_THIS->CloseGate();
	P_NATIVE_END;
}
// ********** End Class AAutomaticGate Function CloseGate ******************************************

// ********** Begin Class AAutomaticGate Function OnGateClosed *************************************
static FName NAME_AAutomaticGate_OnGateClosed = FName(TEXT("OnGateClosed"));
void AAutomaticGate::OnGateClosed()
{
	UFunction* Func = FindFunctionChecked(NAME_AAutomaticGate_OnGateClosed);
	ProcessEvent(Func,NULL);
}
struct Z_Construct_UFunction_AAutomaticGate_OnGateClosed_Statics
{
#if WITH_METADATA
	static constexpr UECodeGen_Private::FMetaDataPairParam Function_MetaDataParams[] = {
		{ "Category", "Gate|Events" },
#if !UE_BUILD_SHIPPING
		{ "Comment", "/** Called gdy wrota si\xc4\x99 zamkn\xc4\x85 */" },
#endif
		{ "ModuleRelativePath", "AutomaticGate.h" },
#if !UE_BUILD_SHIPPING
		{ "ToolTip", "Called gdy wrota si\xc4\x99 zamkn\xc4\x85" },
#endif
	};
#endif // WITH_METADATA

// ********** Begin Function OnGateClosed constinit property declarations **************************
// ********** End Function OnGateClosed constinit property declarations ****************************
	static const UECodeGen_Private::FFunctionParams FuncParams;
};
const UECodeGen_Private::FFunctionParams Z_Construct_UFunction_AAutomaticGate_OnGateClosed_Statics::FuncParams = { { (UObject*(*)())Z_Construct_UClass_AAutomaticGate, nullptr, "OnGateClosed", 	nullptr, 
	0, 
0,
RF_Public|RF_Transient|RF_MarkAsNative, (EFunctionFlags)0x0C080800, 0, 0, METADATA_PARAMS(UE_ARRAY_COUNT(Z_Construct_UFunction_AAutomaticGate_OnGateClosed_Statics::Function_MetaDataParams), Z_Construct_UFunction_AAutomaticGate_OnGateClosed_Statics::Function_MetaDataParams)},  };
UFunction* Z_Construct_UFunction_AAutomaticGate_OnGateClosed()
{
	static UFunction* ReturnFunction = nullptr;
	if (!ReturnFunction)
	{
		UECodeGen_Private::ConstructUFunction(&ReturnFunction, Z_Construct_UFunction_AAutomaticGate_OnGateClosed_Statics::FuncParams);
	}
	return ReturnFunction;
}
// ********** End Class AAutomaticGate Function OnGateClosed ***************************************

// ********** Begin Class AAutomaticGate Function OnGateOpened *************************************
static FName NAME_AAutomaticGate_OnGateOpened = FName(TEXT("OnGateOpened"));
void AAutomaticGate::OnGateOpened()
{
	UFunction* Func = FindFunctionChecked(NAME_AAutomaticGate_OnGateOpened);
	ProcessEvent(Func,NULL);
}
struct Z_Construct_UFunction_AAutomaticGate_OnGateOpened_Statics
{
#if WITH_METADATA
	static constexpr UECodeGen_Private::FMetaDataPairParam Function_MetaDataParams[] = {
		{ "Category", "Gate|Events" },
#if !UE_BUILD_SHIPPING
		{ "Comment", "/** Called gdy wrota si\xc4\x99 otworz\xc4\x85 */" },
#endif
		{ "ModuleRelativePath", "AutomaticGate.h" },
#if !UE_BUILD_SHIPPING
		{ "ToolTip", "Called gdy wrota si\xc4\x99 otworz\xc4\x85" },
#endif
	};
#endif // WITH_METADATA

// ********** Begin Function OnGateOpened constinit property declarations **************************
// ********** End Function OnGateOpened constinit property declarations ****************************
	static const UECodeGen_Private::FFunctionParams FuncParams;
};
const UECodeGen_Private::FFunctionParams Z_Construct_UFunction_AAutomaticGate_OnGateOpened_Statics::FuncParams = { { (UObject*(*)())Z_Construct_UClass_AAutomaticGate, nullptr, "OnGateOpened", 	nullptr, 
	0, 
0,
RF_Public|RF_Transient|RF_MarkAsNative, (EFunctionFlags)0x0C080800, 0, 0, METADATA_PARAMS(UE_ARRAY_COUNT(Z_Construct_UFunction_AAutomaticGate_OnGateOpened_Statics::Function_MetaDataParams), Z_Construct_UFunction_AAutomaticGate_OnGateOpened_Statics::Function_MetaDataParams)},  };
UFunction* Z_Construct_UFunction_AAutomaticGate_OnGateOpened()
{
	static UFunction* ReturnFunction = nullptr;
	if (!ReturnFunction)
	{
		UECodeGen_Private::ConstructUFunction(&ReturnFunction, Z_Construct_UFunction_AAutomaticGate_OnGateOpened_Statics::FuncParams);
	}
	return ReturnFunction;
}
// ********** End Class AAutomaticGate Function OnGateOpened ***************************************

// ********** Begin Class AAutomaticGate Function OpenGate *****************************************
struct Z_Construct_UFunction_AAutomaticGate_OpenGate_Statics
{
#if WITH_METADATA
	static constexpr UECodeGen_Private::FMetaDataPairParam Function_MetaDataParams[] = {
		{ "Category", "Gate|Control" },
#if !UE_BUILD_SHIPPING
		{ "Comment", "/** Otw\xc3\xb3rz wrota */" },
#endif
		{ "ModuleRelativePath", "AutomaticGate.h" },
#if !UE_BUILD_SHIPPING
		{ "ToolTip", "Otw\xc3\xb3rz wrota" },
#endif
	};
#endif // WITH_METADATA

// ********** Begin Function OpenGate constinit property declarations ******************************
// ********** End Function OpenGate constinit property declarations ********************************
	static const UECodeGen_Private::FFunctionParams FuncParams;
};
const UECodeGen_Private::FFunctionParams Z_Construct_UFunction_AAutomaticGate_OpenGate_Statics::FuncParams = { { (UObject*(*)())Z_Construct_UClass_AAutomaticGate, nullptr, "OpenGate", 	nullptr, 
	0, 
0,
RF_Public|RF_Transient|RF_MarkAsNative, (EFunctionFlags)0x04020401, 0, 0, METADATA_PARAMS(UE_ARRAY_COUNT(Z_Construct_UFunction_AAutomaticGate_OpenGate_Statics::Function_MetaDataParams), Z_Construct_UFunction_AAutomaticGate_OpenGate_Statics::Function_MetaDataParams)},  };
UFunction* Z_Construct_UFunction_AAutomaticGate_OpenGate()
{
	static UFunction* ReturnFunction = nullptr;
	if (!ReturnFunction)
	{
		UECodeGen_Private::ConstructUFunction(&ReturnFunction, Z_Construct_UFunction_AAutomaticGate_OpenGate_Statics::FuncParams);
	}
	return ReturnFunction;
}
DEFINE_FUNCTION(AAutomaticGate::execOpenGate)
{
	P_FINISH;
	P_NATIVE_BEGIN;
	P_THIS->OpenGate();
	P_NATIVE_END;
}
// ********** End Class AAutomaticGate Function OpenGate *******************************************

// ********** Begin Class AAutomaticGate Function ToggleGate ***************************************
struct Z_Construct_UFunction_AAutomaticGate_ToggleGate_Statics
{
#if WITH_METADATA
	static constexpr UECodeGen_Private::FMetaDataPairParam Function_MetaDataParams[] = {
		{ "Category", "Gate|Control" },
#if !UE_BUILD_SHIPPING
		{ "Comment", "/** Prze\xc5\x82\xc4\x85""cz stan wr\xc3\xb3t */" },
#endif
		{ "ModuleRelativePath", "AutomaticGate.h" },
#if !UE_BUILD_SHIPPING
		{ "ToolTip", "Prze\xc5\x82\xc4\x85""cz stan wr\xc3\xb3t" },
#endif
	};
#endif // WITH_METADATA

// ********** Begin Function ToggleGate constinit property declarations ****************************
// ********** End Function ToggleGate constinit property declarations ******************************
	static const UECodeGen_Private::FFunctionParams FuncParams;
};
const UECodeGen_Private::FFunctionParams Z_Construct_UFunction_AAutomaticGate_ToggleGate_Statics::FuncParams = { { (UObject*(*)())Z_Construct_UClass_AAutomaticGate, nullptr, "ToggleGate", 	nullptr, 
	0, 
0,
RF_Public|RF_Transient|RF_MarkAsNative, (EFunctionFlags)0x04020401, 0, 0, METADATA_PARAMS(UE_ARRAY_COUNT(Z_Construct_UFunction_AAutomaticGate_ToggleGate_Statics::Function_MetaDataParams), Z_Construct_UFunction_AAutomaticGate_ToggleGate_Statics::Function_MetaDataParams)},  };
UFunction* Z_Construct_UFunction_AAutomaticGate_ToggleGate()
{
	static UFunction* ReturnFunction = nullptr;
	if (!ReturnFunction)
	{
		UECodeGen_Private::ConstructUFunction(&ReturnFunction, Z_Construct_UFunction_AAutomaticGate_ToggleGate_Statics::FuncParams);
	}
	return ReturnFunction;
}
DEFINE_FUNCTION(AAutomaticGate::execToggleGate)
{
	P_FINISH;
	P_NATIVE_BEGIN;
	P_THIS->ToggleGate();
	P_NATIVE_END;
}
// ********** End Class AAutomaticGate Function ToggleGate *****************************************

// ********** Begin Class AAutomaticGate ***********************************************************
FClassRegistrationInfo Z_Registration_Info_UClass_AAutomaticGate;
UClass* AAutomaticGate::GetPrivateStaticClass()
{
	using TClass = AAutomaticGate;
	if (!Z_Registration_Info_UClass_AAutomaticGate.InnerSingleton)
	{
		GetPrivateStaticClassBody(
			TClass::StaticPackage(),
			TEXT("AutomaticGate"),
			Z_Registration_Info_UClass_AAutomaticGate.InnerSingleton,
			StaticRegisterNativesAAutomaticGate,
			sizeof(TClass),
			alignof(TClass),
			TClass::StaticClassFlags,
			TClass::StaticClassCastFlags(),
			TClass::StaticConfigName(),
			(UClass::ClassConstructorType)InternalConstructor<TClass>,
			(UClass::ClassVTableHelperCtorCallerType)InternalVTableHelperCtorCaller<TClass>,
			UOBJECT_CPPCLASS_STATICFUNCTIONS_FORCLASS(TClass),
			&TClass::Super::StaticClass,
			&TClass::WithinClass::StaticClass
		);
	}
	return Z_Registration_Info_UClass_AAutomaticGate.InnerSingleton;
}
UClass* Z_Construct_UClass_AAutomaticGate_NoRegister()
{
	return AAutomaticGate::GetPrivateStaticClass();
}
struct Z_Construct_UClass_AAutomaticGate_Statics
{
#if WITH_METADATA
	static constexpr UECodeGen_Private::FMetaDataPairParam Class_MetaDataParams[] = {
#if !UE_BUILD_SHIPPING
		{ "Comment", "/**\n * Automatyczne wrota podw\xc3\xb3jne (drzwi przesuwane)\n * Otwieraj\xc4\x85 si\xc4\x99 gdy gracz zbli\xc5\xbcy si\xc4\x99 do nich\n * Zamykaj\xc4\x85 si\xc4\x99 automatycznie po okre\xc5\x9blonym czasie\n */" },
#endif
		{ "IncludePath", "AutomaticGate.h" },
		{ "ModuleRelativePath", "AutomaticGate.h" },
#if !UE_BUILD_SHIPPING
		{ "ToolTip", "Automatyczne wrota podw\xc3\xb3jne (drzwi przesuwane)\nOtwieraj\xc4\x85 si\xc4\x99 gdy gracz zbli\xc5\xbcy si\xc4\x99 do nich\nZamykaj\xc4\x85 si\xc4\x99 automatycznie po okre\xc5\x9blonym czasie" },
#endif
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_LeftDoor_MetaData[] = {
		{ "Category", "Components" },
#if !UE_BUILD_SHIPPING
		{ "Comment", "/** Lewe skrzyd\xc5\x82o wr\xc3\xb3t */" },
#endif
		{ "EditInline", "true" },
		{ "ModuleRelativePath", "AutomaticGate.h" },
#if !UE_BUILD_SHIPPING
		{ "ToolTip", "Lewe skrzyd\xc5\x82o wr\xc3\xb3t" },
#endif
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_RightDoor_MetaData[] = {
		{ "Category", "Components" },
#if !UE_BUILD_SHIPPING
		{ "Comment", "/** Prawe skrzyd\xc5\x82o wr\xc3\xb3t */" },
#endif
		{ "EditInline", "true" },
		{ "ModuleRelativePath", "AutomaticGate.h" },
#if !UE_BUILD_SHIPPING
		{ "ToolTip", "Prawe skrzyd\xc5\x82o wr\xc3\xb3t" },
#endif
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_LeftDoorPivot_MetaData[] = {
		{ "Category", "Components" },
#if !UE_BUILD_SHIPPING
		{ "Comment", "/** Punkt obrotu lewych drzwi */" },
#endif
		{ "EditInline", "true" },
		{ "ModuleRelativePath", "AutomaticGate.h" },
#if !UE_BUILD_SHIPPING
		{ "ToolTip", "Punkt obrotu lewych drzwi" },
#endif
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_RightDoorPivot_MetaData[] = {
		{ "Category", "Components" },
#if !UE_BUILD_SHIPPING
		{ "Comment", "/** Punkt obrotu prawych drzwi */" },
#endif
		{ "EditInline", "true" },
		{ "ModuleRelativePath", "AutomaticGate.h" },
#if !UE_BUILD_SHIPPING
		{ "ToolTip", "Punkt obrotu prawych drzwi" },
#endif
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_DetectionRange_MetaData[] = {
		{ "Category", "Gate|Behavior" },
		{ "ClampMax", "5000.0" },
		{ "ClampMin", "100.0" },
#if !UE_BUILD_SHIPPING
		{ "Comment", "/** Zasi\xc4\x99g detekcji - na ile jednostek gracz musi by\xc4\x87 blisko */" },
#endif
		{ "ModuleRelativePath", "AutomaticGate.h" },
#if !UE_BUILD_SHIPPING
		{ "ToolTip", "Zasi\xc4\x99g detekcji - na ile jednostek gracz musi by\xc4\x87 blisko" },
#endif
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_SlideDistance_MetaData[] = {
		{ "Category", "Gate|Behavior" },
		{ "ClampMax", "1000.0" },
		{ "ClampMin", "10.0" },
#if !UE_BUILD_SHIPPING
		{ "Comment", "/** Odleg\xc5\x82o\xc5\x9b\xc4\x87 przesuni\xc4\x99""cia drzwi przy otwarciu (w lokalnych jednostkach Y) */" },
#endif
		{ "ModuleRelativePath", "AutomaticGate.h" },
#if !UE_BUILD_SHIPPING
		{ "ToolTip", "Odleg\xc5\x82o\xc5\x9b\xc4\x87 przesuni\xc4\x99""cia drzwi przy otwarciu (w lokalnych jednostkach Y)" },
#endif
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_OpenSpeed_MetaData[] = {
		{ "Category", "Gate|Behavior" },
		{ "ClampMax", "10.0" },
		{ "ClampMin", "0.1" },
#if !UE_BUILD_SHIPPING
		{ "Comment", "/** Pr\xc4\x99""dko\xc5\x9b\xc4\x87 otwierania/zamykania */" },
#endif
		{ "ModuleRelativePath", "AutomaticGate.h" },
#if !UE_BUILD_SHIPPING
		{ "ToolTip", "Pr\xc4\x99""dko\xc5\x9b\xc4\x87 otwierania/zamykania" },
#endif
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_AutoCloseDelay_MetaData[] = {
		{ "Category", "Gate|Behavior" },
		{ "ClampMax", "30.0" },
		{ "ClampMin", "0.5" },
#if !UE_BUILD_SHIPPING
		{ "Comment", "/** Czas przed automatycznym zamkni\xc4\x99""ciem (w sekundach) */" },
#endif
		{ "ModuleRelativePath", "AutomaticGate.h" },
#if !UE_BUILD_SHIPPING
		{ "ToolTip", "Czas przed automatycznym zamkni\xc4\x99""ciem (w sekundach)" },
#endif
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_bIsOpen_MetaData[] = {
		{ "Category", "Gate|State" },
#if !UE_BUILD_SHIPPING
		{ "Comment", "/** Czy wrota s\xc4\x85 aktualnie otwarte */" },
#endif
		{ "ModuleRelativePath", "AutomaticGate.h" },
#if !UE_BUILD_SHIPPING
		{ "ToolTip", "Czy wrota s\xc4\x85 aktualnie otwarte" },
#endif
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_bIsMoving_MetaData[] = {
		{ "Category", "Gate|State" },
#if !UE_BUILD_SHIPPING
		{ "Comment", "/** Czy wrota s\xc4\x85 w trakcie otwierania/zamykania */" },
#endif
		{ "ModuleRelativePath", "AutomaticGate.h" },
#if !UE_BUILD_SHIPPING
		{ "ToolTip", "Czy wrota s\xc4\x85 w trakcie otwierania/zamykania" },
#endif
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_PlayerCharacter_MetaData[] = {
#if !UE_BUILD_SHIPPING
		{ "Comment", "/** Referencja do gracza */" },
#endif
		{ "ModuleRelativePath", "AutomaticGate.h" },
#if !UE_BUILD_SHIPPING
		{ "ToolTip", "Referencja do gracza" },
#endif
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_bShowDebugVisualization_MetaData[] = {
		{ "Category", "Gate|Debug" },
#if !UE_BUILD_SHIPPING
		{ "Comment", "/** Czy pokazywa\xc4\x87 debug visualization */" },
#endif
		{ "ModuleRelativePath", "AutomaticGate.h" },
#if !UE_BUILD_SHIPPING
		{ "ToolTip", "Czy pokazywa\xc4\x87 debug visualization" },
#endif
	};
#endif // WITH_METADATA

// ********** Begin Class AAutomaticGate constinit property declarations ***************************
	static const UECodeGen_Private::FObjectPropertyParams NewProp_LeftDoor;
	static const UECodeGen_Private::FObjectPropertyParams NewProp_RightDoor;
	static const UECodeGen_Private::FObjectPropertyParams NewProp_LeftDoorPivot;
	static const UECodeGen_Private::FObjectPropertyParams NewProp_RightDoorPivot;
	static const UECodeGen_Private::FFloatPropertyParams NewProp_DetectionRange;
	static const UECodeGen_Private::FFloatPropertyParams NewProp_SlideDistance;
	static const UECodeGen_Private::FFloatPropertyParams NewProp_OpenSpeed;
	static const UECodeGen_Private::FFloatPropertyParams NewProp_AutoCloseDelay;
	static void NewProp_bIsOpen_SetBit(void* Obj);
	static const UECodeGen_Private::FBoolPropertyParams NewProp_bIsOpen;
	static void NewProp_bIsMoving_SetBit(void* Obj);
	static const UECodeGen_Private::FBoolPropertyParams NewProp_bIsMoving;
	static const UECodeGen_Private::FObjectPropertyParams NewProp_PlayerCharacter;
	static void NewProp_bShowDebugVisualization_SetBit(void* Obj);
	static const UECodeGen_Private::FBoolPropertyParams NewProp_bShowDebugVisualization;
	static const UECodeGen_Private::FPropertyParamsBase* const PropPointers[];
// ********** End Class AAutomaticGate constinit property declarations *****************************
	static constexpr UE::CodeGen::FClassNativeFunction Funcs[] = {
		{ .NameUTF8 = UTF8TEXT("CloseGate"), .Pointer = &AAutomaticGate::execCloseGate },
		{ .NameUTF8 = UTF8TEXT("OpenGate"), .Pointer = &AAutomaticGate::execOpenGate },
		{ .NameUTF8 = UTF8TEXT("ToggleGate"), .Pointer = &AAutomaticGate::execToggleGate },
	};
	static UObject* (*const DependentSingletons[])();
	static constexpr FClassFunctionLinkInfo FuncInfo[] = {
		{ &Z_Construct_UFunction_AAutomaticGate_CloseGate, "CloseGate" }, // 2328152213
		{ &Z_Construct_UFunction_AAutomaticGate_OnGateClosed, "OnGateClosed" }, // 1960620043
		{ &Z_Construct_UFunction_AAutomaticGate_OnGateOpened, "OnGateOpened" }, // 871596462
		{ &Z_Construct_UFunction_AAutomaticGate_OpenGate, "OpenGate" }, // 3698502325
		{ &Z_Construct_UFunction_AAutomaticGate_ToggleGate, "ToggleGate" }, // 2401401988
	};
	static_assert(UE_ARRAY_COUNT(FuncInfo) < 2048);
	static constexpr FCppClassTypeInfoStatic StaticCppClassTypeInfo = {
		TCppClassTypeTraits<AAutomaticGate>::IsAbstract,
	};
	static const UECodeGen_Private::FClassParams ClassParams;
}; // struct Z_Construct_UClass_AAutomaticGate_Statics

// ********** Begin Class AAutomaticGate Property Definitions **************************************
const UECodeGen_Private::FObjectPropertyParams Z_Construct_UClass_AAutomaticGate_Statics::NewProp_LeftDoor = { "LeftDoor", nullptr, (EPropertyFlags)0x00200800000a0009, UECodeGen_Private::EPropertyGenFlags::Object, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(AAutomaticGate, LeftDoor), Z_Construct_UClass_UStaticMeshComponent_NoRegister, METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_LeftDoor_MetaData), NewProp_LeftDoor_MetaData) };
const UECodeGen_Private::FObjectPropertyParams Z_Construct_UClass_AAutomaticGate_Statics::NewProp_RightDoor = { "RightDoor", nullptr, (EPropertyFlags)0x00200800000a0009, UECodeGen_Private::EPropertyGenFlags::Object, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(AAutomaticGate, RightDoor), Z_Construct_UClass_UStaticMeshComponent_NoRegister, METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_RightDoor_MetaData), NewProp_RightDoor_MetaData) };
const UECodeGen_Private::FObjectPropertyParams Z_Construct_UClass_AAutomaticGate_Statics::NewProp_LeftDoorPivot = { "LeftDoorPivot", nullptr, (EPropertyFlags)0x00200800000a0009, UECodeGen_Private::EPropertyGenFlags::Object, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(AAutomaticGate, LeftDoorPivot), Z_Construct_UClass_USceneComponent_NoRegister, METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_LeftDoorPivot_MetaData), NewProp_LeftDoorPivot_MetaData) };
const UECodeGen_Private::FObjectPropertyParams Z_Construct_UClass_AAutomaticGate_Statics::NewProp_RightDoorPivot = { "RightDoorPivot", nullptr, (EPropertyFlags)0x00200800000a0009, UECodeGen_Private::EPropertyGenFlags::Object, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(AAutomaticGate, RightDoorPivot), Z_Construct_UClass_USceneComponent_NoRegister, METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_RightDoorPivot_MetaData), NewProp_RightDoorPivot_MetaData) };
const UECodeGen_Private::FFloatPropertyParams Z_Construct_UClass_AAutomaticGate_Statics::NewProp_DetectionRange = { "DetectionRange", nullptr, (EPropertyFlags)0x0020080000000001, UECodeGen_Private::EPropertyGenFlags::Float, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(AAutomaticGate, DetectionRange), METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_DetectionRange_MetaData), NewProp_DetectionRange_MetaData) };
const UECodeGen_Private::FFloatPropertyParams Z_Construct_UClass_AAutomaticGate_Statics::NewProp_SlideDistance = { "SlideDistance", nullptr, (EPropertyFlags)0x0020080000000001, UECodeGen_Private::EPropertyGenFlags::Float, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(AAutomaticGate, SlideDistance), METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_SlideDistance_MetaData), NewProp_SlideDistance_MetaData) };
const UECodeGen_Private::FFloatPropertyParams Z_Construct_UClass_AAutomaticGate_Statics::NewProp_OpenSpeed = { "OpenSpeed", nullptr, (EPropertyFlags)0x0020080000000001, UECodeGen_Private::EPropertyGenFlags::Float, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(AAutomaticGate, OpenSpeed), METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_OpenSpeed_MetaData), NewProp_OpenSpeed_MetaData) };
const UECodeGen_Private::FFloatPropertyParams Z_Construct_UClass_AAutomaticGate_Statics::NewProp_AutoCloseDelay = { "AutoCloseDelay", nullptr, (EPropertyFlags)0x0020080000000001, UECodeGen_Private::EPropertyGenFlags::Float, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(AAutomaticGate, AutoCloseDelay), METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_AutoCloseDelay_MetaData), NewProp_AutoCloseDelay_MetaData) };
void Z_Construct_UClass_AAutomaticGate_Statics::NewProp_bIsOpen_SetBit(void* Obj)
{
	((AAutomaticGate*)Obj)->bIsOpen = 1;
}
const UECodeGen_Private::FBoolPropertyParams Z_Construct_UClass_AAutomaticGate_Statics::NewProp_bIsOpen = { "bIsOpen", nullptr, (EPropertyFlags)0x0020080000000014, UECodeGen_Private::EPropertyGenFlags::Bool | UECodeGen_Private::EPropertyGenFlags::NativeBool, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, sizeof(bool), sizeof(AAutomaticGate), &Z_Construct_UClass_AAutomaticGate_Statics::NewProp_bIsOpen_SetBit, METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_bIsOpen_MetaData), NewProp_bIsOpen_MetaData) };
void Z_Construct_UClass_AAutomaticGate_Statics::NewProp_bIsMoving_SetBit(void* Obj)
{
	((AAutomaticGate*)Obj)->bIsMoving = 1;
}
const UECodeGen_Private::FBoolPropertyParams Z_Construct_UClass_AAutomaticGate_Statics::NewProp_bIsMoving = { "bIsMoving", nullptr, (EPropertyFlags)0x0020080000000014, UECodeGen_Private::EPropertyGenFlags::Bool | UECodeGen_Private::EPropertyGenFlags::NativeBool, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, sizeof(bool), sizeof(AAutomaticGate), &Z_Construct_UClass_AAutomaticGate_Statics::NewProp_bIsMoving_SetBit, METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_bIsMoving_MetaData), NewProp_bIsMoving_MetaData) };
const UECodeGen_Private::FObjectPropertyParams Z_Construct_UClass_AAutomaticGate_Statics::NewProp_PlayerCharacter = { "PlayerCharacter", nullptr, (EPropertyFlags)0x0020080000002000, UECodeGen_Private::EPropertyGenFlags::Object, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(AAutomaticGate, PlayerCharacter), Z_Construct_UClass_ALaba8UECharacter_NoRegister, METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_PlayerCharacter_MetaData), NewProp_PlayerCharacter_MetaData) };
void Z_Construct_UClass_AAutomaticGate_Statics::NewProp_bShowDebugVisualization_SetBit(void* Obj)
{
	((AAutomaticGate*)Obj)->bShowDebugVisualization = 1;
}
const UECodeGen_Private::FBoolPropertyParams Z_Construct_UClass_AAutomaticGate_Statics::NewProp_bShowDebugVisualization = { "bShowDebugVisualization", nullptr, (EPropertyFlags)0x0020080000000001, UECodeGen_Private::EPropertyGenFlags::Bool | UECodeGen_Private::EPropertyGenFlags::NativeBool, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, sizeof(bool), sizeof(AAutomaticGate), &Z_Construct_UClass_AAutomaticGate_Statics::NewProp_bShowDebugVisualization_SetBit, METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_bShowDebugVisualization_MetaData), NewProp_bShowDebugVisualization_MetaData) };
const UECodeGen_Private::FPropertyParamsBase* const Z_Construct_UClass_AAutomaticGate_Statics::PropPointers[] = {
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_AAutomaticGate_Statics::NewProp_LeftDoor,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_AAutomaticGate_Statics::NewProp_RightDoor,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_AAutomaticGate_Statics::NewProp_LeftDoorPivot,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_AAutomaticGate_Statics::NewProp_RightDoorPivot,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_AAutomaticGate_Statics::NewProp_DetectionRange,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_AAutomaticGate_Statics::NewProp_SlideDistance,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_AAutomaticGate_Statics::NewProp_OpenSpeed,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_AAutomaticGate_Statics::NewProp_AutoCloseDelay,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_AAutomaticGate_Statics::NewProp_bIsOpen,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_AAutomaticGate_Statics::NewProp_bIsMoving,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_AAutomaticGate_Statics::NewProp_PlayerCharacter,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_AAutomaticGate_Statics::NewProp_bShowDebugVisualization,
};
static_assert(UE_ARRAY_COUNT(Z_Construct_UClass_AAutomaticGate_Statics::PropPointers) < 2048);
// ********** End Class AAutomaticGate Property Definitions ****************************************
UObject* (*const Z_Construct_UClass_AAutomaticGate_Statics::DependentSingletons[])() = {
	(UObject* (*)())Z_Construct_UClass_AActor,
	(UObject* (*)())Z_Construct_UPackage__Script_Laba8UE,
};
static_assert(UE_ARRAY_COUNT(Z_Construct_UClass_AAutomaticGate_Statics::DependentSingletons) < 16);
const UECodeGen_Private::FClassParams Z_Construct_UClass_AAutomaticGate_Statics::ClassParams = {
	&AAutomaticGate::StaticClass,
	"Engine",
	&StaticCppClassTypeInfo,
	DependentSingletons,
	FuncInfo,
	Z_Construct_UClass_AAutomaticGate_Statics::PropPointers,
	nullptr,
	UE_ARRAY_COUNT(DependentSingletons),
	UE_ARRAY_COUNT(FuncInfo),
	UE_ARRAY_COUNT(Z_Construct_UClass_AAutomaticGate_Statics::PropPointers),
	0,
	0x009000A4u,
	METADATA_PARAMS(UE_ARRAY_COUNT(Z_Construct_UClass_AAutomaticGate_Statics::Class_MetaDataParams), Z_Construct_UClass_AAutomaticGate_Statics::Class_MetaDataParams)
};
void AAutomaticGate::StaticRegisterNativesAAutomaticGate()
{
	UClass* Class = AAutomaticGate::StaticClass();
	FNativeFunctionRegistrar::RegisterFunctions(Class, MakeConstArrayView(Z_Construct_UClass_AAutomaticGate_Statics::Funcs));
}
UClass* Z_Construct_UClass_AAutomaticGate()
{
	if (!Z_Registration_Info_UClass_AAutomaticGate.OuterSingleton)
	{
		UECodeGen_Private::ConstructUClass(Z_Registration_Info_UClass_AAutomaticGate.OuterSingleton, Z_Construct_UClass_AAutomaticGate_Statics::ClassParams);
	}
	return Z_Registration_Info_UClass_AAutomaticGate.OuterSingleton;
}
DEFINE_VTABLE_PTR_HELPER_CTOR_NS(, AAutomaticGate);
AAutomaticGate::~AAutomaticGate() {}
// ********** End Class AAutomaticGate *************************************************************

// ********** Begin Registration *******************************************************************
struct Z_CompiledInDeferFile_FID_workspace_UnrealProjects_Laba8UE_Source_Laba8UE_AutomaticGate_h__Script_Laba8UE_Statics
{
	static constexpr FClassRegisterCompiledInInfo ClassInfo[] = {
		{ Z_Construct_UClass_AAutomaticGate, AAutomaticGate::StaticClass, TEXT("AAutomaticGate"), &Z_Registration_Info_UClass_AAutomaticGate, CONSTRUCT_RELOAD_VERSION_INFO(FClassReloadVersionInfo, sizeof(AAutomaticGate), 299876621U) },
	};
}; // Z_CompiledInDeferFile_FID_workspace_UnrealProjects_Laba8UE_Source_Laba8UE_AutomaticGate_h__Script_Laba8UE_Statics 
static FRegisterCompiledInInfo Z_CompiledInDeferFile_FID_workspace_UnrealProjects_Laba8UE_Source_Laba8UE_AutomaticGate_h__Script_Laba8UE_3263528012{
	TEXT("/Script/Laba8UE"),
	Z_CompiledInDeferFile_FID_workspace_UnrealProjects_Laba8UE_Source_Laba8UE_AutomaticGate_h__Script_Laba8UE_Statics::ClassInfo, UE_ARRAY_COUNT(Z_CompiledInDeferFile_FID_workspace_UnrealProjects_Laba8UE_Source_Laba8UE_AutomaticGate_h__Script_Laba8UE_Statics::ClassInfo),
	nullptr, 0,
	nullptr, 0,
};
// ********** End Registration *********************************************************************

PRAGMA_ENABLE_DEPRECATION_WARNINGS
