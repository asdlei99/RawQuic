#include "net/quic/raw_quic/raw_quic_api.h"

#include "net/quic/raw_quic/raw_quic.h"

RawQuicHandle RAW_QUIC_CALL RawQuicOpen(RawQuicCallbacks callback,
                                        void* opaque,
                                        bool verify) {
  net::RawQuic* raw_quic = new net::RawQuic(callback, opaque, verify);
  return (RawQuicHandle)raw_quic;
}

int32_t RAW_QUIC_CALL RawQuicClose(RawQuicHandle handle) {
  if (handle == 0) {
    return RAW_QUIC_ERROR_CODE_INVALID_HANDLE;
  }

  net::RawQuic* raw_quic = (net::RawQuic*)handle;
  raw_quic->Close();
  delete raw_quic;

  return RAW_QUIC_ERROR_CODE_SUCCESS;
}

int32_t RAW_QUIC_CALL RawQuicConnect(RawQuicHandle handle,
                                     const char* host,
                                     uint16_t port,
                                     const char* path,
                                     int32_t timeout) {
  if (handle == 0) {
    return RAW_QUIC_ERROR_CODE_INVALID_HANDLE;
  }

  net::RawQuic* raw_quic = (net::RawQuic*)handle;
  return raw_quic->Connect(host, port, path, timeout);
}

int32_t RAW_QUIC_CALL RawQuicSend(RawQuicHandle handle,
                                  uint8_t* data,
                                  uint32_t size) {
  if (handle == 0) {
    return RAW_QUIC_ERROR_CODE_INVALID_HANDLE;
  }

  net::RawQuic* raw_quic = (net::RawQuic*)handle;
  return raw_quic->Write(data, size);
}

int32_t RAW_QUIC_CALL RawQuicRecv(RawQuicHandle handle,
                                  uint8_t* data,
                                  uint32_t size,
                                  int32_t timeout) {
  if (handle == 0) {
    return RAW_QUIC_ERROR_CODE_INVALID_HANDLE;
  }

  net::RawQuic* raw_quic = (net::RawQuic*)handle;
  return raw_quic->Read(data, size, timeout);
}
