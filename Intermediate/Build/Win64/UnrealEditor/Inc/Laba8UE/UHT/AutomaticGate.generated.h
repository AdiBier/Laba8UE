// Copyright Epic Games, Inc. All Rights Reserved.
/*===========================================================================
	Generated code exported from UnrealHeaderTool.
	DO NOT modify this manually! Edit the corresponding .h files instead!
===========================================================================*/

// IWYU pragma: private, include "AutomaticGate.h"

#ifdef LABA8UE_AutomaticGate_generated_h
#error "AutomaticGate.generated.h already included, missing '#pragma once' in AutomaticGate.h"
#endif
#define LABA8UE_AutomaticGate_generated_h

#include "UObject/ObjectMacros.h"
#include "UObject/ScriptMacros.h"

PRAGMA_DISABLE_DEPRECATION_WARNINGS

// ********** Begin Class AAutomaticGate ***********************************************************
#define FID_workspace_UnrealProjects_Laba8UE_Source_Laba8UE_AutomaticGate_h_19_RPC_WRAPPERS_NO_PURE_DECLS \
	DECLARE_FUNCTION(execToggleGate); \
	DECLARE_FUNCTION(execCloseGate); \
	DECLARE_FUNCTION(execOpenGate);


#define FID_workspace_UnrealProjects_Laba8UE_Source_Laba8UE_AutomaticGate_h_19_CALLBACK_WRAPPERS
struct Z_Construct_UClass_AAutomaticGate_Statics;
LABA8UE_API UClass* Z_Construct_UClass_AAutomaticGate_NoRegister();

#define FID_workspace_UnrealProjects_Laba8UE_Source_Laba8UE_AutomaticGate_h_19_INCLASS_NO_PURE_DECLS \
private: \
	static void StaticRegisterNativesAAutomaticGate(); \
	friend struct ::Z_Construct_UClass_AAutomaticGate_Statics; \
	static UClass* GetPrivateStaticClass(); \
	friend LABA8UE_API UClass* ::Z_Construct_UClass_AAutomaticGate_NoRegister(); \
public: \
	DECLARE_CLASS2(AAutomaticGate, AActor, COMPILED_IN_FLAGS(0 | CLASS_Config), CASTCLASS_None, TEXT("/Script/Laba8UE"), Z_Construct_UClass_AAutomaticGate_NoRegister) \
	DECLARE_SERIALIZER(AAutomaticGate)


#define FID_workspace_UnrealProjects_Laba8UE_Source_Laba8UE_AutomaticGate_h_19_ENHANCED_CONSTRUCTORS \
	/** Deleted move- and copy-constructors, should never be used */ \
	AAutomaticGate(AAutomaticGate&&) = delete; \
	AAutomaticGate(const AAutomaticGate&) = delete; \
	DECLARE_VTABLE_PTR_HELPER_CTOR(NO_API, AAutomaticGate); \
	DEFINE_VTABLE_PTR_HELPER_CTOR_CALLER(AAutomaticGate); \
	DEFINE_DEFAULT_CONSTRUCTOR_CALL(AAutomaticGate) \
	NO_API virtual ~AAutomaticGate();


#define FID_workspace_UnrealProjects_Laba8UE_Source_Laba8UE_AutomaticGate_h_16_PROLOG
#define FID_workspace_UnrealProjects_Laba8UE_Source_Laba8UE_AutomaticGate_h_19_GENERATED_BODY \
PRAGMA_DISABLE_DEPRECATION_WARNINGS \
public: \
	FID_workspace_UnrealProjects_Laba8UE_Source_Laba8UE_AutomaticGate_h_19_RPC_WRAPPERS_NO_PURE_DECLS \
	FID_workspace_UnrealProjects_Laba8UE_Source_Laba8UE_AutomaticGate_h_19_CALLBACK_WRAPPERS \
	FID_workspace_UnrealProjects_Laba8UE_Source_Laba8UE_AutomaticGate_h_19_INCLASS_NO_PURE_DECLS \
	FID_workspace_UnrealProjects_Laba8UE_Source_Laba8UE_AutomaticGate_h_19_ENHANCED_CONSTRUCTORS \
private: \
PRAGMA_ENABLE_DEPRECATION_WARNINGS


class AAutomaticGate;

// ********** End Class AAutomaticGate *************************************************************

#undef CURRENT_FILE_ID
#define CURRENT_FILE_ID FID_workspace_UnrealProjects_Laba8UE_Source_Laba8UE_AutomaticGate_h

PRAGMA_ENABLE_DEPRECATION_WARNINGS
