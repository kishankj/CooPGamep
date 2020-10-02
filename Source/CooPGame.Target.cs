// Fill out your copyright notice in the Description page of Project Settings.
// Copyright @

using UnrealBuildTool;
using System.Collections.Generic;

public class CooPGameTarget : TargetRules
{
	public CooPGameTarget(TargetInfo Target) : base(Target)
	{
		Type = TargetType.Game;

		ExtraModuleNames.AddRange( new string[] { "CooPGame" } );
	}
}
