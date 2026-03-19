## DNS Packet Structure
- Header
- Question 
- Answer
- Authority
- Additional info


- The Header describes the type of the packet and the fields present in the packet

## DNS Header Structure
- A DNS header has 6 fields, each 16 bits (2 bytes) long.

- ID ----> a 16 bit identifier assigned by the program that generates any kind of quer
- QR ----> a one bit field that tell if the message is query or a response
- OPCODE ----> a four bit field that specifies kind of query in this message
- AA ----> Authoritative Answer
- TC ----> Truncation -> specifies that the message is truncated
- RD ----> Recursion Desired
- RA ----> Recursion Available

HEADER = 12bytes

packet we are sending -> HEADER + QUESTION
/*The structure of the DNS packet will be:
	16 bits:ID
	16 bits:header
	16 bits:question
	16 bits:answer
	16 bits:authoritative answer
	16 bits:additional info*/

/*DNS header*/

### TO DO 

- Read Arguments
- Detect forward or reverse lookup
- Build dns header
- Encode the domain name
- Add Question section
- Send Udp packet to DNS server
- parse header
- parse Answers
- Decode Domain names
- result print
