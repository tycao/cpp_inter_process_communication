#pragma once

/**************************************************************************************************

功能：共享内存服务端
作用：

用法：
CShareMemServer     m_shareMem;
void* pShareMem = m_shareMem.GetAddr();

共享内存名例子
#define SHARE_MEM_NAME  ( L"12345578-0B4B-4e9f-AAA4-19D29CC9416A" )
#define SHARE_MEM_NAME  ( L"12345578-0B4B-4e9f-AAA4-19D29CC9416A-1" )
#define SHARE_MEM_NAME  ( L"12345578-0B4B-4e9f-AAA4-19D29CC9416A-2" )
#define SHARE_MEM_NAME  ( L"12345578-0B4B-4e9f-AAA4-19D29CC9416A-3" )

**************************************************************************************************/

#include <Windows.h>
#include <iostream>
#include <string>
using namespace std;


#define SHARE_MEM_NAME  ( L"12345578-0B4B-4e9f-AAA4-19D29CC9416A" )

class CShareMemServer
{
public:
    CShareMemServer(int iShareMemSize, wchar_t* pShareMemName);
    ~CShareMemServer(void);

    void* GetAddr();                                                //获取共享内存地址

private:
    int         m_iShareMemSize;
    wstring     m_strShareMemName;

    HANDLE      m_hMapFile;
    LPVOID      m_lpMapAddress;                                     //共享内存地址
};



CShareMemServer::CShareMemServer(int iShareMemSize, wchar_t* pShareMemName)
: m_iShareMemSize(iShareMemSize)
, m_strShareMemName(pShareMemName)
, m_lpMapAddress(NULL)
, m_hMapFile(NULL)
{
}

CShareMemServer::~CShareMemServer(void)
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

void* CShareMemServer::GetAddr()
{
    if ( NULL == m_lpMapAddress )
    {
        if ( NULL == m_hMapFile )
        {
            m_hMapFile = CreateFileMappingW( INVALID_HANDLE_VALUE, NULL, PAGE_READWRITE, 0, m_iShareMemSize, m_strShareMemName.c_str() );
        }

        if (m_hMapFile)
        {
            m_lpMapAddress = MapViewOfFile( m_hMapFile, FILE_MAP_ALL_ACCESS, 0, 0, 0 );
        }
    }

    cout <<  "Success...共享内存（内存映射文件）创建成功!" <<  endl;
    return m_lpMapAddress;
}


int main()
{
    CShareMemServer  m_shareMem(4096, SHARE_MEM_NAME);
    void* pShareMem = m_shareMem.GetAddr();
    return 0;
}
