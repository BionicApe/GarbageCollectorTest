# GarbageCollectorTest

## Overview

GarbageCollectorTest is a project designed to explore and compare various pointer validity checks in Unreal Engine, especially under garbage collection conditions. This project provides insights into the behavior of `IsValid()`, `IsValidLowLevel()`, `IsValidLowLevelFast()`, and `TWeakObjectPtr::IsValid()` when objects are subjected to garbage collection.

## Features

- Demonstrates the difference between `IsValid()`, `IsValidLowLevel()`, `IsValidLowLevelFast()`, and `TWeakObjectPtr::IsValid()`.
- Provides a clear test environment to observe how Unreal Engine handles garbage collection and object validity.
- Includes automated test scenarios to trigger garbage collection and evaluate pointer validity responses.

## How to Use

1. Clone the repository to your local machine:
    ```bash
    git clone git@github.com:BionicApe/GarbageCollectorTest.git
    ```

2. Open the project in Unreal Engine (5.x) or an IDE such as Rider.

### Running the Test

You can run the test in one of the following ways:

- **From Unreal Engine:** Open the project in Unreal Engine and run the included test (`FGarbageCollectionTest`) using the Automation Test framework to observe how different pointer validity checks behave under garbage collection.

- **From Rider:** Right-click the test file in Rider and select **Run**. This will execute the test directly within the IDE.

- **Using the `RunTest.bat` script:** If you prefer, you can run the test by double-clicking on the `RunTest.bat` file. However, you need to set the `UNREAL_BIN` environment variable before using the batch file (see below).

### Setting the `UNREAL_BIN` Environment Variable (for `RunTest.bat`)

If you plan to use the `RunTest.bat` file, you'll need to set the `UNREAL_BIN` environment variable to point to your Unreal Editor binaries. Here's how:

1. **Windows 10/11:**
   - Open the Start Menu, search for **Environment Variables**, and select **Edit the system environment variables**.
   - In the System Properties window, click on **Environment Variables**.
   - Under **System variables**, click **New**.
   - Set the variable name to `UNREAL_BIN` and the value to the path of your Unreal Engine `UnrealEditor-Cmd.exe` binary. For example:
     ```
     C:\Program Files\Epic Games\UE_5.3\Engine\Binaries\Win64
     ```
   - Click **OK** to save and close all windows.

2. **Verify the environment variable**:
   - Open a new command prompt and type:
     ```
     echo %UNREAL_BIN%
     ```
   - It should output the path you set.

3. **Run the Test using `RunTest.bat`:**
   - Once the environment variable is set, double-click on the `RunTest.bat` file to execute the test.
   - A log file will be generated in the same directory, named according to the current date and time (e.g., `GarbageCollectionTest_20240919191345.log`).

## Code Breakdown

- **FDelayedGarbageCollectionCheckWeakAndPtr**: The core class responsible for running the tests, which compares `WeakPtr.IsValid()`, `IsValid()`, `IsValidLowLevel()`, and `IsValidLowLevelFast()`.
- **TestObject**: An Unreal object (`UMyTestObject`) used for testing garbage collection validity in different scenarios.
- **Garbage Collection Testing**: The project forces garbage collection during the tests and logs the results of each validity check.

## Results

The results show how Unreal Engine handles garbage collection across different types of pointer validity checks:
- `TWeakObjectPtr::IsValid()` is the most reliable method when dealing with lambda-captured objects or objects not managed by `UPROPERTY()`.
- `IsValid()` may return `true` for objects that have been garbage collected under certain circumstances.
- `IsValidLowLevel()` and `IsValidLowLevelFast()` provide additional memory-level checks that may be useful but should be used with caution in production.

## Requirements

- Unreal Engine 5.x
- Basic knowledge of Unreal Engine garbage collection mechanisms.

## License

[MIT](LICENSE)

## Contributions

Contributions are welcome! Feel free to submit a pull request or report issues in the GitHub issue tracker.
