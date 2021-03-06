#ifndef CSOCKET_H
#define CSOCKET_H

#ifdef WIN32
#include <winsock2.h>
#else
#include <netinet/in.h>
#endif

#include <string>

#ifndef WIN32
#define INFINITY   -1
#endif


class csocket 
{
public:

    enum SocketState 
    {
        CLOSED,
        CONNECTED,          
        ERRORED,
    };


    csocket();
    virtual ~csocket(); 

    static int      resolveHost( const std::string& szRemoteHostName, struct sockaddr_in& sa );
    int             connect( const char* remoteHost, unsigned int remotePort );
    int             canRead( bool* readyToRead, float waitTime = INFINITY );
    virtual int     read( char* pDataBuffer, unsigned int numBytesToRead, bool bReadAll );
    virtual int     write( const char* pDataBuffer, unsigned int numBytesToWrite );
    SocketState     getState( void ) const;
    void            close();
private:


#ifdef WIN32
    SOCKET              m_socket;
#else
    int                 m_socket;
#endif

    struct sockaddr_in  m_localSocketAddr;
    struct sockaddr_in  m_remoteSocketAddr;

    SocketState         m_socketState;
    std::string         m_strRemoteHost;
    unsigned int        m_remotePort;
};

#endif // CSOCKET_H
