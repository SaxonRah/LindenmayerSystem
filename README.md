# LindenmayerSystem
A simple C++ plugin containing everything needed to play with Lindenmayer Systems.
Plugin was built and tested with 4.13.0

# Blueprint Usage
	Install plugin to game directory or engine directory.
	Create blueprint actor based on LMSystem Actor.
	Refer to the picture in the root.
	Then place the blueprint actor in the world and run.
	
	If using video tutorial or want this, Here are the 3D Tree Rules
	3D Tree Example Rules
	Generations :	3
	Axiom :			"1"
	Rules :			"1" -> "D-D+D+D[<+^2]-DD-D[<^-2]<^2"
					"2" -> "D+D-DD>L>>L[<+1]-DDD>L>>L>L[<-1]<1"
	
# C++ Usage
## LSystem Setup and Grow
		// Setup
		FLSInfo KochCurveInfo;
		KochCurveInfo.Generations = 4;
		KochCurveInfo.Axiom = TEXT("D");
		KochCurveInfo.AddRule(TEXT("D"), TEXT("D+D−D−D+D"));
		
		SetupLSystem(KochCurveInfo);
		
		// Will grow by KochCurveInfo.Generations
		GrowLSystem();
		// Will grow by given generation parameter
		GrowLSystemBy(6);
	
## Render LSystem Setup and Rendering
		// We use an array of rules to give users the ability to have multiple commands per variable.
		TArray<ERLSRenderRuleType> RenderRuleTypeArray; RenderRuleTypeArray.Empty();

		RenderRuleTypeArray.Add(ERLSRenderRuleType::LSRR_Draw);
		FRLSRenderRule DRule = FRLSRenderRule(TEXT("D"), RenderRuleTypeArray, 0.0f, 35.0f);
		RenderRuleTypeArray.Empty();

		RenderRuleTypeArray.Add(ERLSRenderRuleType::LSRR_TurnRight);
		FRLSRenderRule TRRule = FRLSRenderRule(TEXT("+"), RenderRuleTypeArray, 90.0f, 0.0f);
		RenderRuleTypeArray.Empty();

		RenderRuleTypeArray.Add(ERLSRenderRuleType::LSRR_TurnLeft);
		FRLSRenderRule TLRule = FRLSRenderRule(TEXT("-"), RenderRuleTypeArray, 90.0f, 0.0f);
		RenderRuleTypeArray.Empty();

		FRLSRenderInfo Info;
		Info.Rules.Add(DRule);
		Info.Rules.Add(TRRule);
		Info.Rules.Add(TLRule);
		
		LSystemRenderInfo = Info;
		
		// Render LSystem
		RenderLSystem(LSystem, LSystemRenderInfo);
		

# C++ Heierarchy
## ALMSystem.h/cpp
		ALMSystem is a LSystem Actor that has a pet turtle which has magical drawing powers.
		It also has several example LSystems. It contains several structures helping facilitate LSystems.
			FLSRule
			FLSInfo
			FLSystem
		
## RenderLSystem.h
		RenderLSystem is contains structures to help rendering.
			FRLSTInfo is a structure containing information about the turtle's transform.
			ERLSRenderRuleType is an enum containing all the different turtle commands.
			FRLSRenderRule contains a string variable and an array of associated turtle commands.
			FRLSRenderInfo contains an array of rules for the rendering.

# Things to Add
	Measure performance of LSystem struct. Maybe look at changing some functions by ref with const correctness
	Expand Turtle example functions to control debug output
	Create Turtle functions to make Spline Mesh
	Implement the procedural mesh component and do 100% procedural l system gen

# Bugs
	Rotating the parent Actor of turtle in Y Axis bends turtle movement up and down.

# MIT LICENCE
	MIT License
	
	Copyright (c) 2016 Robert Chubb
	
	Permission is hereby granted, free of charge, to any person obtaining a copy
	of this software and associated documentation files (the "Software"), to deal
	in the Software without restriction, including without limitation the rights
	to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
	copies of the Software, and to permit persons to whom the Software is
	furnished to do so, subject to the following conditions:
	
	The above copyright notice and this permission notice shall be included in all
	copies or substantial portions of the Software.
	
	THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
	IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
	FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
	AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
	LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
	OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
	SOFTWARE.	
