#include "Misc/AutomationTest.h"
#include "Engine/Engine.h"
#include "UObject/WeakObjectPtr.h"
#include "MyTestObject.h"

IMPLEMENT_SIMPLE_AUTOMATION_TEST(FGarbageCollectionTest, "GarbageCollectorTest.Runtime.GarbageCollectionTest", EAutomationTestFlags::ApplicationContextMask | EAutomationTestFlags::EngineFilter)

class FDelayedGarbageCollectionCheckWeakAndPtr : public IAutomationLatentCommand
{
public:
	UMyTestObject* TestObj;
	TWeakObjectPtr<UMyTestObject> WeakPtr;
	double EndTime;
	double StartTime;

	FDelayedGarbageCollectionCheckWeakAndPtr(UMyTestObject* InTestObj, TWeakObjectPtr<UMyTestObject> InWeakPtr, float InEndTime)
		: TestObj(InTestObj), WeakPtr(InWeakPtr), EndTime(InEndTime), StartTime(FPlatformTime::Seconds())
	{
	}

	virtual bool Update() override
	{
		double CurrentTime = FPlatformTime::Seconds() - StartTime;
		UE_LOG(LogTemp, Log, TEXT("RAW ----Update() Called (Time [%f])----"), CurrentTime);

		if (CurrentTime > 0.1f)
		{
			UE_LOG(LogTemp, Log, TEXT("RAW: Calling Garbage Collector!"));
			GEngine->ForceGarbageCollection(true);
		}

		UE_LOG(LogTemp, Log, TEXT("WEAK: TESTING: WeakPtr.IsValid()"));
		if (WeakPtr.IsValid())
		{
			UE_LOG(LogTemp, Log, TEXT("WEAK: WeakPtr.IsValid() == true. Object is still valid!, The Value is: %i"), WeakPtr->MyTestValue);
		}
		else
		{
			UE_LOG(LogTemp, Log, TEXT("WEAK: WeakPtr.IsValid() == false Object has been garbage collected!"));
		}

		UE_LOG(LogTemp, Log, TEXT("RAW: TESTING: IsValid(TestObj)"));
		if (IsValid(TestObj))
		{
			UE_LOG(LogTemp, Log, TEXT("RAW: IsValid(TestObject) == true. Object is still valid!, The Value is: %i"), TestObj->MyTestValue);
		}
		else
		{
			UE_LOG(LogTemp, Log, TEXT("RAW: IsValid(TestObject) == false Object has been garbage collected!"));
		}

		UE_LOG(LogTemp, Log, TEXT("RAW: TESTING: TestObj->IsValidLowLevel()"));
		if (TestObj->IsValidLowLevel())
		{
			UE_LOG(LogTemp, Log, TEXT("RAW: TestObj->IsValidLowLevel() == true. Object is still valid!, The Value is: %i"), TestObj->MyTestValue);
		}
		else
		{
			UE_LOG(LogTemp, Log, TEXT("RAW: TestObj->IsValidLowLevel() == false Object has been garbage collected!"));
		}

		UE_LOG(LogTemp, Log, TEXT("RAW: TESTING: TestObj->IsValidLowLevelFast()"));
		if (TestObj->IsValidLowLevelFast())
		{
			UE_LOG(LogTemp, Log, TEXT("RAW: TestObj->IsValidLowLevelFast() == true. Object is still valid!, The Value is: %i"), TestObj->MyTestValue);
		}
		else
		{
			UE_LOG(LogTemp, Log, TEXT("RAW: TestObj->IsValidLowLevelFast() == false Object has been garbage collected!"));
		}

		if (CurrentTime > EndTime)
		{
			UE_LOG(LogTemp, Log, TEXT("RAW: ----Update() Finished (Time [%f])----"), CurrentTime);
			return true;
		}
		UE_LOG(LogTemp, Log, TEXT("RAW: ----Update() Pending (Time [%f])----"), CurrentTime);
		return false;
	}
};

bool FGarbageCollectionTest::RunTest(const FString& Parameters)
{
	UMyTestObject* TestObject = NewObject<UMyTestObject>();
	const TWeakObjectPtr<UMyTestObject> WeakPtr = TestObject;
	TestObject->MyTestValue = 1998;
	TestObject->RemoveFromRoot();
	UE_LOG(LogTemp, Log, TEXT("-------ADDING COMMAND FDelayedGarbageCollectionCheck-------"));
	AddCommand(new FDelayedGarbageCollectionCheckWeakAndPtr(TestObject, WeakPtr, 10.f));	
	return true;
}
