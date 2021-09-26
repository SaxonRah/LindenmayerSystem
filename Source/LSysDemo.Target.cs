// Fill out your copyright notice in the Description page of Project Settings.

using UnrealBuildTool;
using System.Collections.Generic;

public class LSysDemoTarget : TargetRules
{
	public LSysDemoTarget(TargetInfo Target) : base (Target)
	{
		Type = TargetType.Game;
		
		ExtraModuleNames.Add("LSysDemo");
	}
}
