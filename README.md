# Getting Started

## 1. Install Arduino IDE

Install the Arduino IDE from https://www.arduino.cc/en/software/. This will be used to develop, compile and deploy embedded software to the hardware device.

## 2. Install CUTE-AUI
The following steps illustrate how to install a local library to use with Arduino

### 2.1 Install CUTE-AUI Dependencies
Within the Arduino IDE, select `Sketch > Include Library > Manage Libraries...` to open up the Library Manager.

![01-ManageLibraries.png](./docs/images/01-ManageLibraries.png)

![02-LibraryManager.png](./docs/images/02-LibraryManager.png)

Search for the Functor library and install.

![03-InstallFunctor.png](./docs/images/03-InstallFunctor.png)

### 2.2. Install CUTE-AUI Library
Next, we will install the CUTE-AUI Library from a local folder. Select `Sketch > Include Library > Add .ZIP Library` to open up the file explorer interface.

![04-AddLocalLibrary.png](./docs/images/04-AddLocalLibrary.png)

Navigate to and select the CUTE-AUI folder.

![05-SelectLocalLibrary.png](./docs/images/05-SelectLocalLibrary.png)


### 2.3 Verify

Verify the installation by locating the CUTE library in the Arduino IDE library dropdown i.e. `Sketch > Include Library`.
You should be able to find both CUTE and the other installed libraries.

![06-VerifyLibraries.png](./docs/images/06-VerifyLibraries.png)

You should also be able to open up the sample code by navigating to the examples dropdown `File > Examples > CUTE`.

![07-VerifyExamples.png](./docs/images/07-VerifyExamples.png)

These examples demonstrate some sample interactions to be used with an application with the CUTE-AUI protocol.

## Required Libraries

[Functor v1.0.1 by Rich Hickey](https://github.com/janelia-arduino/Functor.git)