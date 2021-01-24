#include "pch.h"
#include "FT60XDriver.h"

#include <iostream>



int FT60XDriver::GetNumOfConnections() {
	FT_STATUS ftStatus;
	DWORD numDevs = 0;

	ftStatus = FT_CreateDeviceInfoList(&numDevs);

	//異常終了ならば-1を返す。正常時には接続台数を返す。
	if (ftStatus != FT_OK) return -1;

	return numDevs;
}


bool FT60XDriver::Connect()
{
	int numDevs = GetNumOfConnections();
	if (numDevs != 1) {
		std::cout << "接続数が1以外の数" << std::endl;
		return false;
	};

	FT_STATUS ftStatus;
	FT60XInfo devInfo;
	ftStatus = FT_GetDeviceInfoList(&devInfo, (DWORD*)&numDevs);
	if (ftStatus != FT_OK) return false;

	std::cout << "description:" << devInfo.GetDescription() << std::endl;
	std::cout << "SerialNo:" << devInfo.GetSerialNo() << std::endl;

	if (!devInfo.isSuperSpeed()) {
		std::cout << "USB3.0ではありません" << std::endl;
	}


	//open start
	ftStatus = FT_Create(devInfo.SerialNumber, FT_OPEN_BY_SERIAL_NUMBER, &mHandle);

	if (ftStatus == FT_OK) {
		std::cout << "connect" << std::endl;
	}
	else {
		return false;
	}

	FT_GetChipConfiguration(mHandle, &mChipConfig);

	std::cout << "VID:" << "0x" << std::hex << mChipConfig.VendorID << std::endl;
	std::cout << "PID:" << "0x" << std::hex << mChipConfig.ProductID << std::endl;
	std::cout << "FIFOCLK:" << "0x" << std::hex << mChipConfig.FIFOClock << std::endl;
	std::cout << "FIFOMODE:" << "0x" << std::hex << mChipConfig.FIFOMode << std::endl;
	std::cout << "OptionalFeatureSupport:" << "0x" << std::hex << mChipConfig.OptionalFeatureSupport << std::endl;

	return true;
}

bool FT60XDriver::Close() {
	FT_Close(mHandle);
	return true;
}

bool FT60XDriver::Read(QuadBytes *pDataBuf, int pDataSize) {
	FT_STATUS ftStatus;
	OVERLAPPED vOverlapped = { 0 };
	ftStatus = FT_InitializeOverlapped(mHandle, &vOverlapped);

	QuadBytes *bufPtr = pDataBuf;
	int bufsize = pDataSize;

	ULONG ulBytesTransferred = 0;
	ftStatus = FT_ReadPipe(mHandle, 0x82, (UCHAR*)bufPtr, bufsize, &ulBytesTransferred, &vOverlapped);
	if (ftStatus == FT_IO_PENDING) {
		while (1) {
			ftStatus = FT_GetOverlappedResult(mHandle, &vOverlapped, &ulBytesTransferred, FALSE);
			if (ftStatus == FT_IO_INCOMPLETE) {
				continue;
			}
			else if (ftStatus == FT_OTHER_ERROR) {
				std::cout << "ERROR" << std::endl;
				FT_ReleaseOverlapped(mHandle, &vOverlapped);
				return false;
			}
			else if (ftStatus != FT_OK) {
				break;
			}
			else { //ftStatus == FT_OK
				ftStatus = 0;
				break;
			}
		}
	}
	FT_ReleaseOverlapped(mHandle, &vOverlapped);
	return true;
};


bool FT60XDriver::Write(QuadBytes *pDataBuf, int pDataSize) {
	//実験中
	//	//write
	//	//OVERLAPPED vOverlapped = { 0 };
	//	//ftStatus = FT_InitializeOverlapped(ftHandle, &vOverlapped);
	//	//UCHAR acBuf[BUFFER_SIZE] = { 1,2,3,4 };
	//
	//	//for (int i = 0; i < BUFFER_SIZE; i++) {
	//	//	acBuf[i] = i;
	//	//}
	//
	//	//ULONG ulBytesTransferred = 0;
	//	//ftStatus = FT_WritePipe(ftHandle, 0x02, acBuf, BUFFER_SIZE, &ulBytesTransferred, &vOverlapped);
	//	//if (ftStatus == FT_IO_PENDING)
	//	//{
	//	//	ftStatus = FT_GetOverlappedResult(ftHandle, &vOverlapped, &ulBytesTransferred, TRUE);
	//	//}
	//	//FT_ReleaseOverlapped(ftHandle, &vOverlapped);
	return true;
};