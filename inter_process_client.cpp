#pragma once

/**************************************************************************************************

功能：共享内存客户端
作用：
1、获取共享内存地址

用法：
CShareMemClient m_VideoData(VIDEO_SOURCE_SHARE_MEM_NAME)
void* pShareMem = m_VideoData.GetAddr();

**************************************************************************************************/

#include <Windows.h>
#include <iostream>
#include <string>
using namespace std;

#define SHARE_MEM_NAME  ( L"12345578-0B4B-4e9f-AAA4-19D29CC9416A" )
class CShareMemClient
{
public:
    CShareMemClient(wchar_t* pShareMemName);
    ~CShareMemClient(void);

    void* GetAddr();                                        //获取共享内存地址

private:
    int         m_iShareMemSize;
    wstring     m_strShareMemName;

    HANDLE      m_hMapFile;
    LPVOID      m_lpMapAddress;                             //共享内存地址
};




CShareMemClient::CShareMemClient(wchar_t* pShareMemName)
: m_strShareMemName(pShareMemName)
, m_lpMapAddress(NULL)
, m_hMapFile(NULL)
{
}

CShareMemClient::~CShareMemClient(void)
{
    if ( m_lpMapAddress )
    {
        UnmapViewOfFile( m_lpMapAddress );
        m_lpMapAddress = NULL;
    }

    if ( m_hMapFile )
    {
        CloseHandle( m_hMapFile );
        m_hMapFile = NULL;
    }
}

void* CShareMemClient::GetAddr()
{
    if ( NULL == m_lpMapAddress )
    {
        if ( NULL == m_hMapFile )
        {
            m_hMapFile = OpenFileMappingW( FILE_MAP_ALL_ACCESS, false, m_strShareMemName.c_str() );
        }

        if (m_hMapFile)
        {
            m_lpMapAddress = MapViewOfFile( m_hMapFile, FILE_MAP_ALL_ACCESS, 0, 0, 0 );
        }
    }
    cout <<  "Success...共享内存（内存映射文件）获取成功!" <<  endl;
    return m_lpMapAddress;
}


int  main()
{
    CShareMemClient m_VideoData(SHARE_MEM_NAME);
    void* pShareMem = m_VideoData.GetAddr();
    return  0;
}
