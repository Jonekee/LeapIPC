#include "stdafx.h"
#include "IPCClientConnector.h"
#include "IPCClient.h"
#include "IPCEndpoint.h"

IPCClientConnector::IPCClientConnector(IPCClient& client):
  client(client)
{
  *this += [this] { TryConnect(); };
}

IPCClientConnector::~IPCClientConnector(void)
{}

void IPCClientConnector::TryConnect(void) {
  auto conn = client.Connect();
  if (!conn)
    return;
  conn->onConnectionLost += [this] (IPCEndpoint::Reason reason){ TryConnect(); };
  onConnected(conn);
}
