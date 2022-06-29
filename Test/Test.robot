*** Settings ***
Library    udpossum



*** Test Cases ***
Test Simple Message
    ${result}=     Send UDP datagram   127.0.0.1   ${1802}    127.0.0.1   ${1800}     FEED      # Local / Dest
    Should Be Equal As Strings    ${result}    Success

    ${result}   ${message} =      Read UDP datagram   127.0.0.1   ${1803}   ${10}
    ${message} =                  convert to string    ${message}

    Should Be Equal As Strings           ${result}    Success
    Should Be Equal As Strings           ${message}    0xfeed

Test Big Message
    ${result}=     Send UDP datagram   127.0.0.1   ${1802}    127.0.0.1   ${1800}     123456789ABCDEF      # Local / Dest
    Should Be Equal As Strings    ${result}    Success

    ${result}   ${message} =      Read UDP datagram   127.0.0.1   ${1803}   ${10}
    ${message} =                  convert to string    ${message}

    Should Be Equal As Strings           ${result}    Success
    Should Be Equal As Strings           ${message}    0x123456789abcdef