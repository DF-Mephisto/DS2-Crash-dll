;.MODEL FLAT, C
;.STACK
.DATA
callAddr QWORD 0

.CODE

crashProc PROC
;mov rax, 0FFh
;add rax, rcx

sub rsp,58

mov qword ptr [callAddr], rcx

mov rcx, [rcx+0160B8D0h]
mov rcx, [rcx+0D0h]
mov rcx, [rcx+0158h]
mov rdx, 0000000000000001
mov r8, 9

add qword ptr [callAddr], 015FC60h
call qword ptr [callAddr]

add rsp,58

ret
crashProc ENDP

END