| No. | TCP (Transmission Control Protocol)                                     | UDP (User Datagram Protocol)                                                    |
| --- | ----------------------------------------------------------------------- | ------------------------------------------------------------------------------- |
| 1   | Connection-oriented protocol                                            | Connectionless protocol                                                         |
| 2   | Establishes a connection using **3-way handshake** before data transfer | No connection setup; data is sent directly                                      |
| 3   | Reliable – guarantees delivery of data                                  | Unreliable – data delivery is not guaranteed                                    |
| 4   | Ensures **error checking + acknowledgment + retransmission**            | Performs only **basic error checking**, no acknowledgment and no retransmission |
| 5   | Data is received **in the same order** it was sent                      | Data may **arrive out of order, duplicated, or lost**                           |
| 6   | Speed is **slower** due to reliability features                         | Speed is **faster** because of no retransmission or acknowledgment              |
| 7   | Works as a **byte stream** (continuous flow of data)                    | Works as **datagrams** (independent packets)                                    |
| 8   | Suitable for **large data transfer**                                    | Suitable for **small and time-sensitive messages**                              |
| 9   | Requires more network resources (heavy protocol)                        | Lightweight and low-resource protocol                                           |
| 10  | Supports congestion control and flow control                            | No congestion or flow control                                                   |
| 11  | Header size is **bigger (20–60 bytes)**                                 | Header size is **smaller (8 bytes)**                                            |
| 12  | Used for applications where **accuracy matters more than speed**        | Used for applications where **speed matters more than accuracy**                |
| 13  | Examples: File transfer, Web browsing (HTTP, HTTPS), Email, SSH         | Examples: Video/voice calls, Live streaming, DNS, Online gaming                 |
