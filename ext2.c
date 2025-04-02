#include <ntifs.h>

DRIVER_INITIALIZE DriverEntry;

PDEVICE_OBJECT device_object;

void ext2_unload(PDRIVER_OBJECT driver_object) {
    UNREFERENCED_PARAMETER(driver_object);

    ObDereferenceObject(device_object);
}

//NTSTATUS ext2_create(PDEVICE_OBJECT device_object, PIRP irp) {
//
//}

NTSTATUS DriverEntry(_In_ PDRIVER_OBJECT driver_object, _In_ PUNICODE_STRING registry_path) {
    UNREFERENCED_PARAMETER(registry_path);
    
    UNICODE_STRING unicode_string;
    RtlInitUnicodeString(&unicode_string, L"\\Ext2");
    NTSTATUS status = IoCreateDevice(
        driver_object,
        0,
        &unicode_string,
        FILE_DEVICE_DISK_FILE_SYSTEM,
        0,
        FALSE,
        &device_object
    );

    if (!NT_SUCCESS(status)) {
        return status;
    }

    driver_object->DriverUnload = ext2_unload;

    // skipping a LOT of code...

    IoRegisterFileSystem(device_object);
    ObReferenceObject(device_object);

    return STATUS_SUCCESS;
}
