[Defines]
  PLATFORM_NAME                  = UEFI-Snake
  PLATFORM_GUID                  = 640e69db-8d4a-49d6-a73d-25de81244454
  PLATFORM_VERSION               = 0.1
  DSC_SPECIFICATION              = 0x00010006
  OUTPUT_DIRECTORY               = Build/UEFI-Snake
  SUPPORTED_ARCHITECTURES        = X64
  BUILD_TARGETS                  = DEBUG
  SKUID_IDENTIFIER               = DEFAULT

[Packages]
  UEFI-Snake/UEFI-Snake.dec

[LibraryClasses]
  UefiBootServicesTableLib    |MdePkg/Library/UefiBootServicesTableLib/UefiBootServicesTableLib.inf
  UefiApplicationEntryPoint   |MdePkg/Library/UefiApplicationEntryPoint/UefiApplicationEntryPoint.inf
  UefiLib                     |MdePkg/Library/UefiLib/UefiLib.inf
  BaseLib                     |MdePkg/Library/BaseLib/BaseLib.inf
  DebugLib                    |MdePkg/Library/BaseDebugLibNull/BaseDebugLibNull.inf
  BaseMemoryLib               |MdePkg/Library/BaseMemoryLib/BaseMemoryLib.inf
  MemoryAllocationLib         |MdePkg/Library/UefiMemoryAllocationLib/UefiMemoryAllocationLib.inf
  PrintLib                    |MdePkg/Library/BasePrintLib/BasePrintLib.inf
  StackCheckLib               |MdePkg/Library/StackCheckLib/StackCheckLib.inf
  StackCheckFailureHookLib    |MdePkg/Library/StackCheckFailureHookLibNull/StackCheckFailureHookLibNull.inf
  PcdLib                      |MdePkg/Library/BasePcdLibNull/BasePcdLibNull.inf
  RegisterFilterLib           |MdePkg/Library/RegisterFilterLibNull/RegisterFilterLibNull.inf
  DevicePathLib               |MdePkg/Library/UefiDevicePathLib/UefiDevicePathLib.inf
  UefiRuntimeServicesTableLib |MdePkg/Library/UefiRuntimeServicesTableLib/UefiRuntimeServicesTableLib.inf
  ConsoleLib                  |UEFI-Snake/Library/ConsoleLib/ConsoleLib.inf

[Components]
  UEFI-Snake/Application/Start.inf
  UEFI-Snake/Application/Snake.inf