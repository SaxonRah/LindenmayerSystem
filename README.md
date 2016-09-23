# LindenmayerSystem
A simple C++ plugin containing everything needed to play with Lindenmayer Systems.

# Blueprint Usage
	Refer to the picture in the root. Then place cp in world and run.
	
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
