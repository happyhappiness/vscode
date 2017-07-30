; ModuleID = '/data/download/cmake/cmake-master/Utilities/cmlibuv/src/unix/linux-syscalls.c'
target datalayout = "e-m:e-i64:64-f80:128-n8:16:32:64-S128"
target triple = "x86_64-unknown-linux-gnu"

%struct.sockaddr = type { i16, [14 x i8] }
%struct.uv__epoll_event = type <{ i32, i64 }>
%struct.uv__mmsghdr = type { %struct.msghdr, i32 }
%struct.msghdr = type { i8*, i32, %struct.iovec*, i64, i8*, i64, i32 }
%struct.iovec = type { i8*, i64 }
%struct.timespec = type { i64, i64 }

; Function Attrs: nounwind uwtable
define i32 @uv__accept4(i32 %fd, %struct.sockaddr* %addr, i32* %addrlen, i32 %flags) #0 !dbg !6 {
entry:
  %fd.addr = alloca i32, align 4
  %addr.addr = alloca %struct.sockaddr*, align 8
  %addrlen.addr = alloca i32*, align 8
  %flags.addr = alloca i32, align 4
  store i32 %fd, i32* %fd.addr, align 4
  call void @llvm.dbg.declare(metadata i32* %fd.addr, metadata !132, metadata !133), !dbg !134
  store %struct.sockaddr* %addr, %struct.sockaddr** %addr.addr, align 8
  call void @llvm.dbg.declare(metadata %struct.sockaddr** %addr.addr, metadata !135, metadata !133), !dbg !136
  store i32* %addrlen, i32** %addrlen.addr, align 8
  call void @llvm.dbg.declare(metadata i32** %addrlen.addr, metadata !137, metadata !133), !dbg !138
  store i32 %flags, i32* %flags.addr, align 4
  call void @llvm.dbg.declare(metadata i32* %flags.addr, metadata !139, metadata !133), !dbg !140
  %0 = load i32, i32* %fd.addr, align 4, !dbg !141
  %1 = load %struct.sockaddr*, %struct.sockaddr** %addr.addr, align 8, !dbg !142
  %2 = load i32*, i32** %addrlen.addr, align 8, !dbg !143
  %3 = load i32, i32* %flags.addr, align 4, !dbg !144
  %call = call i64 (i64, ...) @syscall(i64 288, i32 %0, %struct.sockaddr* %1, i32* %2, i32 %3) #3, !dbg !145
  %conv = trunc i64 %call to i32, !dbg !145
  ret i32 %conv, !dbg !146
}

; Function Attrs: nounwind readnone
declare void @llvm.dbg.declare(metadata, metadata, metadata) #1

; Function Attrs: nounwind
declare i64 @syscall(i64, ...) #2

; Function Attrs: nounwind uwtable
define i32 @uv__eventfd(i32 %count) #0 !dbg !28 {
entry:
  %count.addr = alloca i32, align 4
  store i32 %count, i32* %count.addr, align 4
  call void @llvm.dbg.declare(metadata i32* %count.addr, metadata !147, metadata !133), !dbg !148
  %0 = load i32, i32* %count.addr, align 4, !dbg !149
  %call = call i64 (i64, ...) @syscall(i64 284, i32 %0) #3, !dbg !150
  %conv = trunc i64 %call to i32, !dbg !150
  ret i32 %conv, !dbg !151
}

; Function Attrs: nounwind uwtable
define i32 @uv__eventfd2(i32 %count, i32 %flags) #0 !dbg !31 {
entry:
  %count.addr = alloca i32, align 4
  %flags.addr = alloca i32, align 4
  store i32 %count, i32* %count.addr, align 4
  call void @llvm.dbg.declare(metadata i32* %count.addr, metadata !152, metadata !133), !dbg !153
  store i32 %flags, i32* %flags.addr, align 4
  call void @llvm.dbg.declare(metadata i32* %flags.addr, metadata !154, metadata !133), !dbg !155
  %0 = load i32, i32* %count.addr, align 4, !dbg !156
  %1 = load i32, i32* %flags.addr, align 4, !dbg !157
  %call = call i64 (i64, ...) @syscall(i64 290, i32 %0, i32 %1) #3, !dbg !158
  %conv = trunc i64 %call to i32, !dbg !158
  ret i32 %conv, !dbg !159
}

; Function Attrs: nounwind uwtable
define i32 @uv__epoll_create(i32 %size) #0 !dbg !34 {
entry:
  %size.addr = alloca i32, align 4
  store i32 %size, i32* %size.addr, align 4
  call void @llvm.dbg.declare(metadata i32* %size.addr, metadata !160, metadata !133), !dbg !161
  %0 = load i32, i32* %size.addr, align 4, !dbg !162
  %call = call i64 (i64, ...) @syscall(i64 213, i32 %0) #3, !dbg !163
  %conv = trunc i64 %call to i32, !dbg !163
  ret i32 %conv, !dbg !164
}

; Function Attrs: nounwind uwtable
define i32 @uv__epoll_create1(i32 %flags) #0 !dbg !37 {
entry:
  %flags.addr = alloca i32, align 4
  store i32 %flags, i32* %flags.addr, align 4
  call void @llvm.dbg.declare(metadata i32* %flags.addr, metadata !165, metadata !133), !dbg !166
  %0 = load i32, i32* %flags.addr, align 4, !dbg !167
  %call = call i64 (i64, ...) @syscall(i64 291, i32 %0) #3, !dbg !168
  %conv = trunc i64 %call to i32, !dbg !168
  ret i32 %conv, !dbg !169
}

; Function Attrs: nounwind uwtable
define i32 @uv__epoll_ctl(i32 %epfd, i32 %op, i32 %fd, %struct.uv__epoll_event* %events) #0 !dbg !38 {
entry:
  %epfd.addr = alloca i32, align 4
  %op.addr = alloca i32, align 4
  %fd.addr = alloca i32, align 4
  %events.addr = alloca %struct.uv__epoll_event*, align 8
  store i32 %epfd, i32* %epfd.addr, align 4
  call void @llvm.dbg.declare(metadata i32* %epfd.addr, metadata !170, metadata !133), !dbg !171
  store i32 %op, i32* %op.addr, align 4
  call void @llvm.dbg.declare(metadata i32* %op.addr, metadata !172, metadata !133), !dbg !173
  store i32 %fd, i32* %fd.addr, align 4
  call void @llvm.dbg.declare(metadata i32* %fd.addr, metadata !174, metadata !133), !dbg !175
  store %struct.uv__epoll_event* %events, %struct.uv__epoll_event** %events.addr, align 8
  call void @llvm.dbg.declare(metadata %struct.uv__epoll_event** %events.addr, metadata !176, metadata !133), !dbg !177
  %0 = load i32, i32* %epfd.addr, align 4, !dbg !178
  %1 = load i32, i32* %op.addr, align 4, !dbg !179
  %2 = load i32, i32* %fd.addr, align 4, !dbg !180
  %3 = load %struct.uv__epoll_event*, %struct.uv__epoll_event** %events.addr, align 8, !dbg !181
  %call = call i64 (i64, ...) @syscall(i64 233, i32 %0, i32 %1, i32 %2, %struct.uv__epoll_event* %3) #3, !dbg !182
  %conv = trunc i64 %call to i32, !dbg !182
  ret i32 %conv, !dbg !183
}

; Function Attrs: nounwind uwtable
define i32 @uv__epoll_wait(i32 %epfd, %struct.uv__epoll_event* %events, i32 %nevents, i32 %timeout) #0 !dbg !51 {
entry:
  %epfd.addr = alloca i32, align 4
  %events.addr = alloca %struct.uv__epoll_event*, align 8
  %nevents.addr = alloca i32, align 4
  %timeout.addr = alloca i32, align 4
  %result = alloca i32, align 4
  store i32 %epfd, i32* %epfd.addr, align 4
  call void @llvm.dbg.declare(metadata i32* %epfd.addr, metadata !184, metadata !133), !dbg !185
  store %struct.uv__epoll_event* %events, %struct.uv__epoll_event** %events.addr, align 8
  call void @llvm.dbg.declare(metadata %struct.uv__epoll_event** %events.addr, metadata !186, metadata !133), !dbg !187
  store i32 %nevents, i32* %nevents.addr, align 4
  call void @llvm.dbg.declare(metadata i32* %nevents.addr, metadata !188, metadata !133), !dbg !189
  store i32 %timeout, i32* %timeout.addr, align 4
  call void @llvm.dbg.declare(metadata i32* %timeout.addr, metadata !190, metadata !133), !dbg !191
  call void @llvm.dbg.declare(metadata i32* %result, metadata !192, metadata !133), !dbg !193
  %0 = load i32, i32* %epfd.addr, align 4, !dbg !194
  %1 = load %struct.uv__epoll_event*, %struct.uv__epoll_event** %events.addr, align 8, !dbg !195
  %2 = load i32, i32* %nevents.addr, align 4, !dbg !196
  %3 = load i32, i32* %timeout.addr, align 4, !dbg !197
  %call = call i64 (i64, ...) @syscall(i64 232, i32 %0, %struct.uv__epoll_event* %1, i32 %2, i32 %3) #3, !dbg !198
  %conv = trunc i64 %call to i32, !dbg !198
  store i32 %conv, i32* %result, align 4, !dbg !199
  %4 = load i32, i32* %result, align 4, !dbg !200
  ret i32 %4, !dbg !201
}

; Function Attrs: nounwind uwtable
define i32 @uv__epoll_pwait(i32 %epfd, %struct.uv__epoll_event* %events, i32 %nevents, i32 %timeout, i64 %sigmask) #0 !dbg !54 {
entry:
  %epfd.addr = alloca i32, align 4
  %events.addr = alloca %struct.uv__epoll_event*, align 8
  %nevents.addr = alloca i32, align 4
  %timeout.addr = alloca i32, align 4
  %sigmask.addr = alloca i64, align 8
  %result = alloca i32, align 4
  store i32 %epfd, i32* %epfd.addr, align 4
  call void @llvm.dbg.declare(metadata i32* %epfd.addr, metadata !202, metadata !133), !dbg !203
  store %struct.uv__epoll_event* %events, %struct.uv__epoll_event** %events.addr, align 8
  call void @llvm.dbg.declare(metadata %struct.uv__epoll_event** %events.addr, metadata !204, metadata !133), !dbg !205
  store i32 %nevents, i32* %nevents.addr, align 4
  call void @llvm.dbg.declare(metadata i32* %nevents.addr, metadata !206, metadata !133), !dbg !207
  store i32 %timeout, i32* %timeout.addr, align 4
  call void @llvm.dbg.declare(metadata i32* %timeout.addr, metadata !208, metadata !133), !dbg !209
  store i64 %sigmask, i64* %sigmask.addr, align 8
  call void @llvm.dbg.declare(metadata i64* %sigmask.addr, metadata !210, metadata !133), !dbg !211
  call void @llvm.dbg.declare(metadata i32* %result, metadata !212, metadata !133), !dbg !213
  %0 = load i32, i32* %epfd.addr, align 4, !dbg !214
  %1 = load %struct.uv__epoll_event*, %struct.uv__epoll_event** %events.addr, align 8, !dbg !215
  %2 = load i32, i32* %nevents.addr, align 4, !dbg !216
  %3 = load i32, i32* %timeout.addr, align 4, !dbg !217
  %call = call i64 (i64, ...) @syscall(i64 281, i32 %0, %struct.uv__epoll_event* %1, i32 %2, i32 %3, i64* %sigmask.addr, i64 8) #3, !dbg !218
  %conv = trunc i64 %call to i32, !dbg !218
  store i32 %conv, i32* %result, align 4, !dbg !219
  %4 = load i32, i32* %result, align 4, !dbg !220
  ret i32 %4, !dbg !221
}

; Function Attrs: nounwind uwtable
define i32 @uv__inotify_init() #0 !dbg !57 {
entry:
  %call = call i64 (i64, ...) @syscall(i64 253) #3, !dbg !222
  %conv = trunc i64 %call to i32, !dbg !222
  ret i32 %conv, !dbg !223
}

; Function Attrs: nounwind uwtable
define i32 @uv__inotify_init1(i32 %flags) #0 !dbg !60 {
entry:
  %flags.addr = alloca i32, align 4
  store i32 %flags, i32* %flags.addr, align 4
  call void @llvm.dbg.declare(metadata i32* %flags.addr, metadata !224, metadata !133), !dbg !225
  %0 = load i32, i32* %flags.addr, align 4, !dbg !226
  %call = call i64 (i64, ...) @syscall(i64 294, i32 %0) #3, !dbg !227
  %conv = trunc i64 %call to i32, !dbg !227
  ret i32 %conv, !dbg !228
}

; Function Attrs: nounwind uwtable
define i32 @uv__inotify_add_watch(i32 %fd, i8* %path, i32 %mask) #0 !dbg !61 {
entry:
  %fd.addr = alloca i32, align 4
  %path.addr = alloca i8*, align 8
  %mask.addr = alloca i32, align 4
  store i32 %fd, i32* %fd.addr, align 4
  call void @llvm.dbg.declare(metadata i32* %fd.addr, metadata !229, metadata !133), !dbg !230
  store i8* %path, i8** %path.addr, align 8
  call void @llvm.dbg.declare(metadata i8** %path.addr, metadata !231, metadata !133), !dbg !232
  store i32 %mask, i32* %mask.addr, align 4
  call void @llvm.dbg.declare(metadata i32* %mask.addr, metadata !233, metadata !133), !dbg !234
  %0 = load i32, i32* %fd.addr, align 4, !dbg !235
  %1 = load i8*, i8** %path.addr, align 8, !dbg !236
  %2 = load i32, i32* %mask.addr, align 4, !dbg !237
  %call = call i64 (i64, ...) @syscall(i64 254, i32 %0, i8* %1, i32 %2) #3, !dbg !238
  %conv = trunc i64 %call to i32, !dbg !238
  ret i32 %conv, !dbg !239
}

; Function Attrs: nounwind uwtable
define i32 @uv__inotify_rm_watch(i32 %fd, i32 %wd) #0 !dbg !66 {
entry:
  %fd.addr = alloca i32, align 4
  %wd.addr = alloca i32, align 4
  store i32 %fd, i32* %fd.addr, align 4
  call void @llvm.dbg.declare(metadata i32* %fd.addr, metadata !240, metadata !133), !dbg !241
  store i32 %wd, i32* %wd.addr, align 4
  call void @llvm.dbg.declare(metadata i32* %wd.addr, metadata !242, metadata !133), !dbg !243
  %0 = load i32, i32* %fd.addr, align 4, !dbg !244
  %1 = load i32, i32* %wd.addr, align 4, !dbg !245
  %call = call i64 (i64, ...) @syscall(i64 255, i32 %0, i32 %1) #3, !dbg !246
  %conv = trunc i64 %call to i32, !dbg !246
  ret i32 %conv, !dbg !247
}

; Function Attrs: nounwind uwtable
define i32 @uv__pipe2(i32* %pipefd, i32 %flags) #0 !dbg !70 {
entry:
  %pipefd.addr = alloca i32*, align 8
  %flags.addr = alloca i32, align 4
  %result = alloca i32, align 4
  store i32* %pipefd, i32** %pipefd.addr, align 8
  call void @llvm.dbg.declare(metadata i32** %pipefd.addr, metadata !248, metadata !133), !dbg !249
  store i32 %flags, i32* %flags.addr, align 4
  call void @llvm.dbg.declare(metadata i32* %flags.addr, metadata !250, metadata !133), !dbg !251
  call void @llvm.dbg.declare(metadata i32* %result, metadata !252, metadata !133), !dbg !253
  %0 = load i32*, i32** %pipefd.addr, align 8, !dbg !254
  %1 = load i32, i32* %flags.addr, align 4, !dbg !255
  %call = call i64 (i64, ...) @syscall(i64 293, i32* %0, i32 %1) #3, !dbg !256
  %conv = trunc i64 %call to i32, !dbg !256
  store i32 %conv, i32* %result, align 4, !dbg !257
  %2 = load i32, i32* %result, align 4, !dbg !258
  ret i32 %2, !dbg !259
}

; Function Attrs: nounwind uwtable
define i32 @uv__sendmmsg(i32 %fd, %struct.uv__mmsghdr* %mmsg, i32 %vlen, i32 %flags) #0 !dbg !74 {
entry:
  %fd.addr = alloca i32, align 4
  %mmsg.addr = alloca %struct.uv__mmsghdr*, align 8
  %vlen.addr = alloca i32, align 4
  %flags.addr = alloca i32, align 4
  store i32 %fd, i32* %fd.addr, align 4
  call void @llvm.dbg.declare(metadata i32* %fd.addr, metadata !260, metadata !133), !dbg !261
  store %struct.uv__mmsghdr* %mmsg, %struct.uv__mmsghdr** %mmsg.addr, align 8
  call void @llvm.dbg.declare(metadata %struct.uv__mmsghdr** %mmsg.addr, metadata !262, metadata !133), !dbg !263
  store i32 %vlen, i32* %vlen.addr, align 4
  call void @llvm.dbg.declare(metadata i32* %vlen.addr, metadata !264, metadata !133), !dbg !265
  store i32 %flags, i32* %flags.addr, align 4
  call void @llvm.dbg.declare(metadata i32* %flags.addr, metadata !266, metadata !133), !dbg !267
  %0 = load i32, i32* %fd.addr, align 4, !dbg !268
  %1 = load %struct.uv__mmsghdr*, %struct.uv__mmsghdr** %mmsg.addr, align 8, !dbg !269
  %2 = load i32, i32* %vlen.addr, align 4, !dbg !270
  %3 = load i32, i32* %flags.addr, align 4, !dbg !271
  %call = call i64 (i64, ...) @syscall(i64 307, i32 %0, %struct.uv__mmsghdr* %1, i32 %2, i32 %3) #3, !dbg !272
  %conv = trunc i64 %call to i32, !dbg !272
  ret i32 %conv, !dbg !273
}

; Function Attrs: nounwind uwtable
define i32 @uv__recvmmsg(i32 %fd, %struct.uv__mmsghdr* %mmsg, i32 %vlen, i32 %flags, %struct.timespec* %timeout) #0 !dbg !100 {
entry:
  %fd.addr = alloca i32, align 4
  %mmsg.addr = alloca %struct.uv__mmsghdr*, align 8
  %vlen.addr = alloca i32, align 4
  %flags.addr = alloca i32, align 4
  %timeout.addr = alloca %struct.timespec*, align 8
  store i32 %fd, i32* %fd.addr, align 4
  call void @llvm.dbg.declare(metadata i32* %fd.addr, metadata !274, metadata !133), !dbg !275
  store %struct.uv__mmsghdr* %mmsg, %struct.uv__mmsghdr** %mmsg.addr, align 8
  call void @llvm.dbg.declare(metadata %struct.uv__mmsghdr** %mmsg.addr, metadata !276, metadata !133), !dbg !277
  store i32 %vlen, i32* %vlen.addr, align 4
  call void @llvm.dbg.declare(metadata i32* %vlen.addr, metadata !278, metadata !133), !dbg !279
  store i32 %flags, i32* %flags.addr, align 4
  call void @llvm.dbg.declare(metadata i32* %flags.addr, metadata !280, metadata !133), !dbg !281
  store %struct.timespec* %timeout, %struct.timespec** %timeout.addr, align 8
  call void @llvm.dbg.declare(metadata %struct.timespec** %timeout.addr, metadata !282, metadata !133), !dbg !283
  %0 = load i32, i32* %fd.addr, align 4, !dbg !284
  %1 = load %struct.uv__mmsghdr*, %struct.uv__mmsghdr** %mmsg.addr, align 8, !dbg !285
  %2 = load i32, i32* %vlen.addr, align 4, !dbg !286
  %3 = load i32, i32* %flags.addr, align 4, !dbg !287
  %4 = load %struct.timespec*, %struct.timespec** %timeout.addr, align 8, !dbg !288
  %call = call i64 (i64, ...) @syscall(i64 299, i32 %0, %struct.uv__mmsghdr* %1, i32 %2, i32 %3, %struct.timespec* %4) #3, !dbg !289
  %conv = trunc i64 %call to i32, !dbg !289
  ret i32 %conv, !dbg !290
}

; Function Attrs: nounwind uwtable
define i32 @uv__utimesat(i32 %dirfd, i8* %path, %struct.timespec* %times, i32 %flags) #0 !dbg !111 {
entry:
  %dirfd.addr = alloca i32, align 4
  %path.addr = alloca i8*, align 8
  %times.addr = alloca %struct.timespec*, align 8
  %flags.addr = alloca i32, align 4
  store i32 %dirfd, i32* %dirfd.addr, align 4
  call void @llvm.dbg.declare(metadata i32* %dirfd.addr, metadata !291, metadata !133), !dbg !292
  store i8* %path, i8** %path.addr, align 8
  call void @llvm.dbg.declare(metadata i8** %path.addr, metadata !293, metadata !133), !dbg !294
  store %struct.timespec* %times, %struct.timespec** %times.addr, align 8
  call void @llvm.dbg.declare(metadata %struct.timespec** %times.addr, metadata !295, metadata !133), !dbg !296
  store i32 %flags, i32* %flags.addr, align 4
  call void @llvm.dbg.declare(metadata i32* %flags.addr, metadata !297, metadata !133), !dbg !298
  %0 = load i32, i32* %dirfd.addr, align 4, !dbg !299
  %1 = load i8*, i8** %path.addr, align 8, !dbg !300
  %2 = load %struct.timespec*, %struct.timespec** %times.addr, align 8, !dbg !301
  %3 = load i32, i32* %flags.addr, align 4, !dbg !302
  %call = call i64 (i64, ...) @syscall(i64 280, i32 %0, i8* %1, %struct.timespec* %2, i32 %3) #3, !dbg !303
  %conv = trunc i64 %call to i32, !dbg !303
  ret i32 %conv, !dbg !304
}

; Function Attrs: nounwind uwtable
define i64 @uv__preadv(i32 %fd, %struct.iovec* %iov, i32 %iovcnt, i64 %offset) #0 !dbg !116 {
entry:
  %fd.addr = alloca i32, align 4
  %iov.addr = alloca %struct.iovec*, align 8
  %iovcnt.addr = alloca i32, align 4
  %offset.addr = alloca i64, align 8
  store i32 %fd, i32* %fd.addr, align 4
  call void @llvm.dbg.declare(metadata i32* %fd.addr, metadata !305, metadata !133), !dbg !306
  store %struct.iovec* %iov, %struct.iovec** %iov.addr, align 8
  call void @llvm.dbg.declare(metadata %struct.iovec** %iov.addr, metadata !307, metadata !133), !dbg !308
  store i32 %iovcnt, i32* %iovcnt.addr, align 4
  call void @llvm.dbg.declare(metadata i32* %iovcnt.addr, metadata !309, metadata !133), !dbg !310
  store i64 %offset, i64* %offset.addr, align 8
  call void @llvm.dbg.declare(metadata i64* %offset.addr, metadata !311, metadata !133), !dbg !312
  %0 = load i32, i32* %fd.addr, align 4, !dbg !313
  %1 = load %struct.iovec*, %struct.iovec** %iov.addr, align 8, !dbg !314
  %2 = load i32, i32* %iovcnt.addr, align 4, !dbg !315
  %3 = load i64, i64* %offset.addr, align 8, !dbg !316
  %4 = load i64, i64* %offset.addr, align 8, !dbg !317
  %shr = ashr i64 %4, 32, !dbg !318
  %call = call i64 (i64, ...) @syscall(i64 295, i32 %0, %struct.iovec* %1, i32 %2, i64 %3, i64 %shr) #3, !dbg !319
  ret i64 %call, !dbg !320
}

; Function Attrs: nounwind uwtable
define i64 @uv__pwritev(i32 %fd, %struct.iovec* %iov, i32 %iovcnt, i64 %offset) #0 !dbg !125 {
entry:
  %fd.addr = alloca i32, align 4
  %iov.addr = alloca %struct.iovec*, align 8
  %iovcnt.addr = alloca i32, align 4
  %offset.addr = alloca i64, align 8
  store i32 %fd, i32* %fd.addr, align 4
  call void @llvm.dbg.declare(metadata i32* %fd.addr, metadata !321, metadata !133), !dbg !322
  store %struct.iovec* %iov, %struct.iovec** %iov.addr, align 8
  call void @llvm.dbg.declare(metadata %struct.iovec** %iov.addr, metadata !323, metadata !133), !dbg !324
  store i32 %iovcnt, i32* %iovcnt.addr, align 4
  call void @llvm.dbg.declare(metadata i32* %iovcnt.addr, metadata !325, metadata !133), !dbg !326
  store i64 %offset, i64* %offset.addr, align 8
  call void @llvm.dbg.declare(metadata i64* %offset.addr, metadata !327, metadata !133), !dbg !328
  %0 = load i32, i32* %fd.addr, align 4, !dbg !329
  %1 = load %struct.iovec*, %struct.iovec** %iov.addr, align 8, !dbg !330
  %2 = load i32, i32* %iovcnt.addr, align 4, !dbg !331
  %3 = load i64, i64* %offset.addr, align 8, !dbg !332
  %4 = load i64, i64* %offset.addr, align 8, !dbg !333
  %shr = ashr i64 %4, 32, !dbg !334
  %call = call i64 (i64, ...) @syscall(i64 296, i32 %0, %struct.iovec* %1, i32 %2, i64 %3, i64 %shr) #3, !dbg !335
  ret i64 %call, !dbg !336
}

; Function Attrs: nounwind uwtable
define i32 @uv__dup3(i32 %oldfd, i32 %newfd, i32 %flags) #0 !dbg !126 {
entry:
  %oldfd.addr = alloca i32, align 4
  %newfd.addr = alloca i32, align 4
  %flags.addr = alloca i32, align 4
  store i32 %oldfd, i32* %oldfd.addr, align 4
  call void @llvm.dbg.declare(metadata i32* %oldfd.addr, metadata !337, metadata !133), !dbg !338
  store i32 %newfd, i32* %newfd.addr, align 4
  call void @llvm.dbg.declare(metadata i32* %newfd.addr, metadata !339, metadata !133), !dbg !340
  store i32 %flags, i32* %flags.addr, align 4
  call void @llvm.dbg.declare(metadata i32* %flags.addr, metadata !341, metadata !133), !dbg !342
  %0 = load i32, i32* %oldfd.addr, align 4, !dbg !343
  %1 = load i32, i32* %newfd.addr, align 4, !dbg !344
  %2 = load i32, i32* %flags.addr, align 4, !dbg !345
  %call = call i64 (i64, ...) @syscall(i64 292, i32 %0, i32 %1, i32 %2) #3, !dbg !346
  %conv = trunc i64 %call to i32, !dbg !346
  ret i32 %conv, !dbg !347
}

attributes #0 = { nounwind uwtable "disable-tail-calls"="false" "less-precise-fpmad"="false" "no-frame-pointer-elim"="true" "no-frame-pointer-elim-non-leaf" "no-infs-fp-math"="false" "no-nans-fp-math"="false" "stack-protector-buffer-size"="8" "target-cpu"="x86-64" "target-features"="+fxsr,+mmx,+sse,+sse2" "unsafe-fp-math"="false" "use-soft-float"="false" }
attributes #1 = { nounwind readnone }
attributes #2 = { nounwind "disable-tail-calls"="false" "less-precise-fpmad"="false" "no-frame-pointer-elim"="true" "no-frame-pointer-elim-non-leaf" "no-infs-fp-math"="false" "no-nans-fp-math"="false" "stack-protector-buffer-size"="8" "target-cpu"="x86-64" "target-features"="+fxsr,+mmx,+sse,+sse2" "unsafe-fp-math"="false" "use-soft-float"="false" }
attributes #3 = { nounwind }

!llvm.dbg.cu = !{!0}
!llvm.module.flags = !{!129, !130}
!llvm.ident = !{!131}

!0 = distinct !DICompileUnit(language: DW_LANG_C99, file: !1, producer: "clang version 3.8.0 (tags/RELEASE_380/final)", isOptimized: false, runtimeVersion: 0, emissionKind: 1, enums: !2, retainedTypes: !3, subprograms: !5)
!1 = !DIFile(filename: "/data/download/cmake/cmake-master/Utilities/cmlibuv/src/unix/linux-syscalls.c", directory: "/data/download/cmake/cmake-master/Utilities/cmlibuv")
!2 = !{}
!3 = !{!4}
!4 = !DIBasicType(name: "long int", size: 64, align: 64, encoding: DW_ATE_signed)
!5 = !{!6, !28, !31, !34, !37, !38, !51, !54, !57, !60, !61, !66, !70, !74, !100, !111, !116, !125, !126}
!6 = distinct !DISubprogram(name: "uv__accept4", scope: !1, file: !1, line: 241, type: !7, isLocal: false, isDefinition: true, scopeLine: 241, flags: DIFlagPrototyped, isOptimized: false, variables: !2)
!7 = !DISubroutineType(types: !8)
!8 = !{!9, !9, !10, !23, !9}
!9 = !DIBasicType(name: "int", size: 32, align: 32, encoding: DW_ATE_signed)
!10 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !11, size: 64, align: 64)
!11 = !DICompositeType(tag: DW_TAG_structure_type, name: "sockaddr", file: !12, line: 149, size: 128, align: 16, elements: !13)
!12 = !DIFile(filename: "/usr/include/x86_64-linux-gnu/bits/socket.h", directory: "/data/download/cmake/cmake-master/Utilities/cmlibuv")
!13 = !{!14, !18}
!14 = !DIDerivedType(tag: DW_TAG_member, name: "sa_family", scope: !11, file: !12, line: 151, baseType: !15, size: 16, align: 16)
!15 = !DIDerivedType(tag: DW_TAG_typedef, name: "sa_family_t", file: !16, line: 28, baseType: !17)
!16 = !DIFile(filename: "/usr/include/x86_64-linux-gnu/bits/sockaddr.h", directory: "/data/download/cmake/cmake-master/Utilities/cmlibuv")
!17 = !DIBasicType(name: "unsigned short", size: 16, align: 16, encoding: DW_ATE_unsigned)
!18 = !DIDerivedType(tag: DW_TAG_member, name: "sa_data", scope: !11, file: !12, line: 152, baseType: !19, size: 112, align: 8, offset: 16)
!19 = !DICompositeType(tag: DW_TAG_array_type, baseType: !20, size: 112, align: 8, elements: !21)
!20 = !DIBasicType(name: "char", size: 8, align: 8, encoding: DW_ATE_signed_char)
!21 = !{!22}
!22 = !DISubrange(count: 14)
!23 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !24, size: 64, align: 64)
!24 = !DIDerivedType(tag: DW_TAG_typedef, name: "socklen_t", file: !12, line: 33, baseType: !25)
!25 = !DIDerivedType(tag: DW_TAG_typedef, name: "__socklen_t", file: !26, line: 189, baseType: !27)
!26 = !DIFile(filename: "/usr/include/x86_64-linux-gnu/bits/types.h", directory: "/data/download/cmake/cmake-master/Utilities/cmlibuv")
!27 = !DIBasicType(name: "unsigned int", size: 32, align: 32, encoding: DW_ATE_unsigned)
!28 = distinct !DISubprogram(name: "uv__eventfd", scope: !1, file: !1, line: 270, type: !29, isLocal: false, isDefinition: true, scopeLine: 270, flags: DIFlagPrototyped, isOptimized: false, variables: !2)
!29 = !DISubroutineType(types: !30)
!30 = !{!9, !27}
!31 = distinct !DISubprogram(name: "uv__eventfd2", scope: !1, file: !1, line: 279, type: !32, isLocal: false, isDefinition: true, scopeLine: 279, flags: DIFlagPrototyped, isOptimized: false, variables: !2)
!32 = !DISubroutineType(types: !33)
!33 = !{!9, !27, !9}
!34 = distinct !DISubprogram(name: "uv__epoll_create", scope: !1, file: !1, line: 288, type: !35, isLocal: false, isDefinition: true, scopeLine: 288, flags: DIFlagPrototyped, isOptimized: false, variables: !2)
!35 = !DISubroutineType(types: !36)
!36 = !{!9, !9}
!37 = distinct !DISubprogram(name: "uv__epoll_create1", scope: !1, file: !1, line: 297, type: !35, isLocal: false, isDefinition: true, scopeLine: 297, flags: DIFlagPrototyped, isOptimized: false, variables: !2)
!38 = distinct !DISubprogram(name: "uv__epoll_ctl", scope: !1, file: !1, line: 306, type: !39, isLocal: false, isDefinition: true, scopeLine: 306, flags: DIFlagPrototyped, isOptimized: false, variables: !2)
!39 = !DISubroutineType(types: !40)
!40 = !{!9, !9, !9, !9, !41}
!41 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !42, size: 64, align: 64)
!42 = !DICompositeType(tag: DW_TAG_structure_type, name: "uv__epoll_event", file: !43, line: 90, size: 96, align: 8, elements: !44)
!43 = !DIFile(filename: "/data/download/cmake/cmake-master/Utilities/cmlibuv/src/unix/linux-syscalls.h", directory: "/data/download/cmake/cmake-master/Utilities/cmlibuv")
!44 = !{!45, !48}
!45 = !DIDerivedType(tag: DW_TAG_member, name: "events", scope: !42, file: !43, line: 91, baseType: !46, size: 32, align: 32)
!46 = !DIDerivedType(tag: DW_TAG_typedef, name: "uint32_t", file: !47, line: 51, baseType: !27)
!47 = !DIFile(filename: "/usr/include/stdint.h", directory: "/data/download/cmake/cmake-master/Utilities/cmlibuv")
!48 = !DIDerivedType(tag: DW_TAG_member, name: "data", scope: !42, file: !43, line: 92, baseType: !49, size: 64, align: 64, offset: 32)
!49 = !DIDerivedType(tag: DW_TAG_typedef, name: "uint64_t", file: !47, line: 55, baseType: !50)
!50 = !DIBasicType(name: "long unsigned int", size: 64, align: 64, encoding: DW_ATE_unsigned)
!51 = distinct !DISubprogram(name: "uv__epoll_wait", scope: !1, file: !1, line: 315, type: !52, isLocal: false, isDefinition: true, scopeLine: 318, flags: DIFlagPrototyped, isOptimized: false, variables: !2)
!52 = !DISubroutineType(types: !53)
!53 = !{!9, !9, !41, !9, !9}
!54 = distinct !DISubprogram(name: "uv__epoll_pwait", scope: !1, file: !1, line: 333, type: !55, isLocal: false, isDefinition: true, scopeLine: 337, flags: DIFlagPrototyped, isOptimized: false, variables: !2)
!55 = !DISubroutineType(types: !56)
!56 = !{!9, !9, !41, !9, !9, !49}
!57 = distinct !DISubprogram(name: "uv__inotify_init", scope: !1, file: !1, line: 358, type: !58, isLocal: false, isDefinition: true, scopeLine: 358, flags: DIFlagPrototyped, isOptimized: false, variables: !2)
!58 = !DISubroutineType(types: !59)
!59 = !{!9}
!60 = distinct !DISubprogram(name: "uv__inotify_init1", scope: !1, file: !1, line: 367, type: !35, isLocal: false, isDefinition: true, scopeLine: 367, flags: DIFlagPrototyped, isOptimized: false, variables: !2)
!61 = distinct !DISubprogram(name: "uv__inotify_add_watch", scope: !1, file: !1, line: 376, type: !62, isLocal: false, isDefinition: true, scopeLine: 376, flags: DIFlagPrototyped, isOptimized: false, variables: !2)
!62 = !DISubroutineType(types: !63)
!63 = !{!9, !9, !64, !46}
!64 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !65, size: 64, align: 64)
!65 = !DIDerivedType(tag: DW_TAG_const_type, baseType: !20)
!66 = distinct !DISubprogram(name: "uv__inotify_rm_watch", scope: !1, file: !1, line: 385, type: !67, isLocal: false, isDefinition: true, scopeLine: 385, flags: DIFlagPrototyped, isOptimized: false, variables: !2)
!67 = !DISubroutineType(types: !68)
!68 = !{!9, !9, !69}
!69 = !DIDerivedType(tag: DW_TAG_typedef, name: "int32_t", file: !47, line: 38, baseType: !9)
!70 = distinct !DISubprogram(name: "uv__pipe2", scope: !1, file: !1, line: 394, type: !71, isLocal: false, isDefinition: true, scopeLine: 394, flags: DIFlagPrototyped, isOptimized: false, variables: !2)
!71 = !DISubroutineType(types: !72)
!72 = !{!9, !73, !9}
!73 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !9, size: 64, align: 64)
!74 = distinct !DISubprogram(name: "uv__sendmmsg", scope: !1, file: !1, line: 409, type: !75, isLocal: false, isDefinition: true, scopeLine: 412, flags: DIFlagPrototyped, isOptimized: false, variables: !2)
!75 = !DISubroutineType(types: !76)
!76 = !{!9, !9, !77, !27, !27}
!77 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !78, size: 64, align: 64)
!78 = !DICompositeType(tag: DW_TAG_structure_type, name: "uv__mmsghdr", file: !43, line: 109, size: 512, align: 64, elements: !79)
!79 = !{!80, !99}
!80 = !DIDerivedType(tag: DW_TAG_member, name: "msg_hdr", scope: !78, file: !43, line: 110, baseType: !81, size: 448, align: 64)
!81 = !DICompositeType(tag: DW_TAG_structure_type, name: "msghdr", file: !12, line: 224, size: 448, align: 64, elements: !82)
!82 = !{!83, !85, !86, !95, !96, !97, !98}
!83 = !DIDerivedType(tag: DW_TAG_member, name: "msg_name", scope: !81, file: !12, line: 226, baseType: !84, size: 64, align: 64)
!84 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: null, size: 64, align: 64)
!85 = !DIDerivedType(tag: DW_TAG_member, name: "msg_namelen", scope: !81, file: !12, line: 227, baseType: !24, size: 32, align: 32, offset: 64)
!86 = !DIDerivedType(tag: DW_TAG_member, name: "msg_iov", scope: !81, file: !12, line: 229, baseType: !87, size: 64, align: 64, offset: 128)
!87 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !88, size: 64, align: 64)
!88 = !DICompositeType(tag: DW_TAG_structure_type, name: "iovec", file: !89, line: 43, size: 128, align: 64, elements: !90)
!89 = !DIFile(filename: "/usr/include/x86_64-linux-gnu/bits/uio.h", directory: "/data/download/cmake/cmake-master/Utilities/cmlibuv")
!90 = !{!91, !92}
!91 = !DIDerivedType(tag: DW_TAG_member, name: "iov_base", scope: !88, file: !89, line: 45, baseType: !84, size: 64, align: 64)
!92 = !DIDerivedType(tag: DW_TAG_member, name: "iov_len", scope: !88, file: !89, line: 46, baseType: !93, size: 64, align: 64, offset: 64)
!93 = !DIDerivedType(tag: DW_TAG_typedef, name: "size_t", file: !94, line: 62, baseType: !50)
!94 = !DIFile(filename: "/opt/llvm-build/bin/../lib/clang/3.8.0/include/stddef.h", directory: "/data/download/cmake/cmake-master/Utilities/cmlibuv")
!95 = !DIDerivedType(tag: DW_TAG_member, name: "msg_iovlen", scope: !81, file: !12, line: 230, baseType: !93, size: 64, align: 64, offset: 192)
!96 = !DIDerivedType(tag: DW_TAG_member, name: "msg_control", scope: !81, file: !12, line: 232, baseType: !84, size: 64, align: 64, offset: 256)
!97 = !DIDerivedType(tag: DW_TAG_member, name: "msg_controllen", scope: !81, file: !12, line: 233, baseType: !93, size: 64, align: 64, offset: 320)
!98 = !DIDerivedType(tag: DW_TAG_member, name: "msg_flags", scope: !81, file: !12, line: 238, baseType: !9, size: 32, align: 32, offset: 384)
!99 = !DIDerivedType(tag: DW_TAG_member, name: "msg_len", scope: !78, file: !43, line: 111, baseType: !27, size: 32, align: 32, offset: 448)
!100 = distinct !DISubprogram(name: "uv__recvmmsg", scope: !1, file: !1, line: 421, type: !101, isLocal: false, isDefinition: true, scopeLine: 425, flags: DIFlagPrototyped, isOptimized: false, variables: !2)
!101 = !DISubroutineType(types: !102)
!102 = !{!9, !9, !77, !27, !27, !103}
!103 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !104, size: 64, align: 64)
!104 = !DICompositeType(tag: DW_TAG_structure_type, name: "timespec", file: !105, line: 120, size: 128, align: 64, elements: !106)
!105 = !DIFile(filename: "/usr/include/time.h", directory: "/data/download/cmake/cmake-master/Utilities/cmlibuv")
!106 = !{!107, !109}
!107 = !DIDerivedType(tag: DW_TAG_member, name: "tv_sec", scope: !104, file: !105, line: 122, baseType: !108, size: 64, align: 64)
!108 = !DIDerivedType(tag: DW_TAG_typedef, name: "__time_t", file: !26, line: 139, baseType: !4)
!109 = !DIDerivedType(tag: DW_TAG_member, name: "tv_nsec", scope: !104, file: !105, line: 123, baseType: !110, size: 64, align: 64, offset: 64)
!110 = !DIDerivedType(tag: DW_TAG_typedef, name: "__syscall_slong_t", file: !26, line: 175, baseType: !4)
!111 = distinct !DISubprogram(name: "uv__utimesat", scope: !1, file: !1, line: 434, type: !112, isLocal: false, isDefinition: true, scopeLine: 438, flags: DIFlagPrototyped, isOptimized: false, variables: !2)
!112 = !DISubroutineType(types: !113)
!113 = !{!9, !9, !64, !114, !9}
!114 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !115, size: 64, align: 64)
!115 = !DIDerivedType(tag: DW_TAG_const_type, baseType: !104)
!116 = distinct !DISubprogram(name: "uv__preadv", scope: !1, file: !1, line: 447, type: !117, isLocal: false, isDefinition: true, scopeLine: 447, flags: DIFlagPrototyped, isOptimized: false, variables: !2)
!117 = !DISubroutineType(types: !118)
!118 = !{!119, !9, !122, !9, !124}
!119 = !DIDerivedType(tag: DW_TAG_typedef, name: "ssize_t", file: !120, line: 109, baseType: !121)
!120 = !DIFile(filename: "/usr/include/x86_64-linux-gnu/sys/types.h", directory: "/data/download/cmake/cmake-master/Utilities/cmlibuv")
!121 = !DIDerivedType(tag: DW_TAG_typedef, name: "__ssize_t", file: !26, line: 172, baseType: !4)
!122 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !123, size: 64, align: 64)
!123 = !DIDerivedType(tag: DW_TAG_const_type, baseType: !88)
!124 = !DIDerivedType(tag: DW_TAG_typedef, name: "int64_t", file: !47, line: 40, baseType: !4)
!125 = distinct !DISubprogram(name: "uv__pwritev", scope: !1, file: !1, line: 456, type: !117, isLocal: false, isDefinition: true, scopeLine: 456, flags: DIFlagPrototyped, isOptimized: false, variables: !2)
!126 = distinct !DISubprogram(name: "uv__dup3", scope: !1, file: !1, line: 465, type: !127, isLocal: false, isDefinition: true, scopeLine: 465, flags: DIFlagPrototyped, isOptimized: false, variables: !2)
!127 = !DISubroutineType(types: !128)
!128 = !{!9, !9, !9, !9}
!129 = !{i32 2, !"Dwarf Version", i32 4}
!130 = !{i32 2, !"Debug Info Version", i32 3}
!131 = !{!"clang version 3.8.0 (tags/RELEASE_380/final)"}
!132 = !DILocalVariable(name: "fd", arg: 1, scope: !6, file: !1, line: 241, type: !9)
!133 = !DIExpression()
!134 = !DILocation(line: 241, column: 21, scope: !6)
!135 = !DILocalVariable(name: "addr", arg: 2, scope: !6, file: !1, line: 241, type: !10)
!136 = !DILocation(line: 241, column: 42, scope: !6)
!137 = !DILocalVariable(name: "addrlen", arg: 3, scope: !6, file: !1, line: 241, type: !23)
!138 = !DILocation(line: 241, column: 59, scope: !6)
!139 = !DILocalVariable(name: "flags", arg: 4, scope: !6, file: !1, line: 241, type: !9)
!140 = !DILocation(line: 241, column: 72, scope: !6)
!141 = !DILocation(line: 263, column: 32, scope: !6)
!142 = !DILocation(line: 263, column: 36, scope: !6)
!143 = !DILocation(line: 263, column: 42, scope: !6)
!144 = !DILocation(line: 263, column: 51, scope: !6)
!145 = !DILocation(line: 263, column: 10, scope: !6)
!146 = !DILocation(line: 263, column: 3, scope: !6)
!147 = !DILocalVariable(name: "count", arg: 1, scope: !28, file: !1, line: 270, type: !27)
!148 = !DILocation(line: 270, column: 30, scope: !28)
!149 = !DILocation(line: 272, column: 32, scope: !28)
!150 = !DILocation(line: 272, column: 10, scope: !28)
!151 = !DILocation(line: 272, column: 3, scope: !28)
!152 = !DILocalVariable(name: "count", arg: 1, scope: !31, file: !1, line: 279, type: !27)
!153 = !DILocation(line: 279, column: 31, scope: !31)
!154 = !DILocalVariable(name: "flags", arg: 2, scope: !31, file: !1, line: 279, type: !9)
!155 = !DILocation(line: 279, column: 42, scope: !31)
!156 = !DILocation(line: 281, column: 33, scope: !31)
!157 = !DILocation(line: 281, column: 40, scope: !31)
!158 = !DILocation(line: 281, column: 10, scope: !31)
!159 = !DILocation(line: 281, column: 3, scope: !31)
!160 = !DILocalVariable(name: "size", arg: 1, scope: !34, file: !1, line: 288, type: !9)
!161 = !DILocation(line: 288, column: 26, scope: !34)
!162 = !DILocation(line: 290, column: 37, scope: !34)
!163 = !DILocation(line: 290, column: 10, scope: !34)
!164 = !DILocation(line: 290, column: 3, scope: !34)
!165 = !DILocalVariable(name: "flags", arg: 1, scope: !37, file: !1, line: 297, type: !9)
!166 = !DILocation(line: 297, column: 27, scope: !37)
!167 = !DILocation(line: 299, column: 38, scope: !37)
!168 = !DILocation(line: 299, column: 10, scope: !37)
!169 = !DILocation(line: 299, column: 3, scope: !37)
!170 = !DILocalVariable(name: "epfd", arg: 1, scope: !38, file: !1, line: 306, type: !9)
!171 = !DILocation(line: 306, column: 23, scope: !38)
!172 = !DILocalVariable(name: "op", arg: 2, scope: !38, file: !1, line: 306, type: !9)
!173 = !DILocation(line: 306, column: 33, scope: !38)
!174 = !DILocalVariable(name: "fd", arg: 3, scope: !38, file: !1, line: 306, type: !9)
!175 = !DILocation(line: 306, column: 41, scope: !38)
!176 = !DILocalVariable(name: "events", arg: 4, scope: !38, file: !1, line: 306, type: !41)
!177 = !DILocation(line: 306, column: 69, scope: !38)
!178 = !DILocation(line: 308, column: 34, scope: !38)
!179 = !DILocation(line: 308, column: 40, scope: !38)
!180 = !DILocation(line: 308, column: 44, scope: !38)
!181 = !DILocation(line: 308, column: 48, scope: !38)
!182 = !DILocation(line: 308, column: 10, scope: !38)
!183 = !DILocation(line: 308, column: 3, scope: !38)
!184 = !DILocalVariable(name: "epfd", arg: 1, scope: !51, file: !1, line: 315, type: !9)
!185 = !DILocation(line: 315, column: 24, scope: !51)
!186 = !DILocalVariable(name: "events", arg: 2, scope: !51, file: !1, line: 316, type: !41)
!187 = !DILocation(line: 316, column: 44, scope: !51)
!188 = !DILocalVariable(name: "nevents", arg: 3, scope: !51, file: !1, line: 317, type: !9)
!189 = !DILocation(line: 317, column: 24, scope: !51)
!190 = !DILocalVariable(name: "timeout", arg: 4, scope: !51, file: !1, line: 318, type: !9)
!191 = !DILocation(line: 318, column: 24, scope: !51)
!192 = !DILocalVariable(name: "result", scope: !51, file: !1, line: 320, type: !9)
!193 = !DILocation(line: 320, column: 7, scope: !51)
!194 = !DILocation(line: 321, column: 37, scope: !51)
!195 = !DILocation(line: 321, column: 43, scope: !51)
!196 = !DILocation(line: 321, column: 51, scope: !51)
!197 = !DILocation(line: 321, column: 60, scope: !51)
!198 = !DILocation(line: 321, column: 12, scope: !51)
!199 = !DILocation(line: 321, column: 10, scope: !51)
!200 = !DILocation(line: 326, column: 10, scope: !51)
!201 = !DILocation(line: 326, column: 3, scope: !51)
!202 = !DILocalVariable(name: "epfd", arg: 1, scope: !54, file: !1, line: 333, type: !9)
!203 = !DILocation(line: 333, column: 25, scope: !54)
!204 = !DILocalVariable(name: "events", arg: 2, scope: !54, file: !1, line: 334, type: !41)
!205 = !DILocation(line: 334, column: 45, scope: !54)
!206 = !DILocalVariable(name: "nevents", arg: 3, scope: !54, file: !1, line: 335, type: !9)
!207 = !DILocation(line: 335, column: 25, scope: !54)
!208 = !DILocalVariable(name: "timeout", arg: 4, scope: !54, file: !1, line: 336, type: !9)
!209 = !DILocation(line: 336, column: 25, scope: !54)
!210 = !DILocalVariable(name: "sigmask", arg: 5, scope: !54, file: !1, line: 337, type: !49)
!211 = !DILocation(line: 337, column: 30, scope: !54)
!212 = !DILocalVariable(name: "result", scope: !54, file: !1, line: 339, type: !9)
!213 = !DILocation(line: 339, column: 7, scope: !54)
!214 = !DILocation(line: 341, column: 20, scope: !54)
!215 = !DILocation(line: 342, column: 20, scope: !54)
!216 = !DILocation(line: 343, column: 20, scope: !54)
!217 = !DILocation(line: 344, column: 20, scope: !54)
!218 = !DILocation(line: 340, column: 12, scope: !54)
!219 = !DILocation(line: 340, column: 10, scope: !54)
!220 = !DILocation(line: 351, column: 10, scope: !54)
!221 = !DILocation(line: 351, column: 3, scope: !54)
!222 = !DILocation(line: 360, column: 10, scope: !57)
!223 = !DILocation(line: 360, column: 3, scope: !57)
!224 = !DILocalVariable(name: "flags", arg: 1, scope: !60, file: !1, line: 367, type: !9)
!225 = !DILocation(line: 367, column: 27, scope: !60)
!226 = !DILocation(line: 369, column: 38, scope: !60)
!227 = !DILocation(line: 369, column: 10, scope: !60)
!228 = !DILocation(line: 369, column: 3, scope: !60)
!229 = !DILocalVariable(name: "fd", arg: 1, scope: !61, file: !1, line: 376, type: !9)
!230 = !DILocation(line: 376, column: 31, scope: !61)
!231 = !DILocalVariable(name: "path", arg: 2, scope: !61, file: !1, line: 376, type: !64)
!232 = !DILocation(line: 376, column: 47, scope: !61)
!233 = !DILocalVariable(name: "mask", arg: 3, scope: !61, file: !1, line: 376, type: !46)
!234 = !DILocation(line: 376, column: 62, scope: !61)
!235 = !DILocation(line: 378, column: 42, scope: !61)
!236 = !DILocation(line: 378, column: 46, scope: !61)
!237 = !DILocation(line: 378, column: 52, scope: !61)
!238 = !DILocation(line: 378, column: 10, scope: !61)
!239 = !DILocation(line: 378, column: 3, scope: !61)
!240 = !DILocalVariable(name: "fd", arg: 1, scope: !66, file: !1, line: 385, type: !9)
!241 = !DILocation(line: 385, column: 30, scope: !66)
!242 = !DILocalVariable(name: "wd", arg: 2, scope: !66, file: !1, line: 385, type: !69)
!243 = !DILocation(line: 385, column: 42, scope: !66)
!244 = !DILocation(line: 387, column: 41, scope: !66)
!245 = !DILocation(line: 387, column: 45, scope: !66)
!246 = !DILocation(line: 387, column: 10, scope: !66)
!247 = !DILocation(line: 387, column: 3, scope: !66)
!248 = !DILocalVariable(name: "pipefd", arg: 1, scope: !70, file: !1, line: 394, type: !73)
!249 = !DILocation(line: 394, column: 19, scope: !70)
!250 = !DILocalVariable(name: "flags", arg: 2, scope: !70, file: !1, line: 394, type: !9)
!251 = !DILocation(line: 394, column: 34, scope: !70)
!252 = !DILocalVariable(name: "result", scope: !70, file: !1, line: 396, type: !9)
!253 = !DILocation(line: 396, column: 7, scope: !70)
!254 = !DILocation(line: 397, column: 32, scope: !70)
!255 = !DILocation(line: 397, column: 40, scope: !70)
!256 = !DILocation(line: 397, column: 12, scope: !70)
!257 = !DILocation(line: 397, column: 10, scope: !70)
!258 = !DILocation(line: 402, column: 10, scope: !70)
!259 = !DILocation(line: 402, column: 3, scope: !70)
!260 = !DILocalVariable(name: "fd", arg: 1, scope: !74, file: !1, line: 409, type: !9)
!261 = !DILocation(line: 409, column: 22, scope: !74)
!262 = !DILocalVariable(name: "mmsg", arg: 2, scope: !74, file: !1, line: 410, type: !77)
!263 = !DILocation(line: 410, column: 38, scope: !74)
!264 = !DILocalVariable(name: "vlen", arg: 3, scope: !74, file: !1, line: 411, type: !27)
!265 = !DILocation(line: 411, column: 31, scope: !74)
!266 = !DILocalVariable(name: "flags", arg: 4, scope: !74, file: !1, line: 412, type: !27)
!267 = !DILocation(line: 412, column: 31, scope: !74)
!268 = !DILocation(line: 414, column: 33, scope: !74)
!269 = !DILocation(line: 414, column: 37, scope: !74)
!270 = !DILocation(line: 414, column: 43, scope: !74)
!271 = !DILocation(line: 414, column: 49, scope: !74)
!272 = !DILocation(line: 414, column: 10, scope: !74)
!273 = !DILocation(line: 414, column: 3, scope: !74)
!274 = !DILocalVariable(name: "fd", arg: 1, scope: !100, file: !1, line: 421, type: !9)
!275 = !DILocation(line: 421, column: 22, scope: !100)
!276 = !DILocalVariable(name: "mmsg", arg: 2, scope: !100, file: !1, line: 422, type: !77)
!277 = !DILocation(line: 422, column: 38, scope: !100)
!278 = !DILocalVariable(name: "vlen", arg: 3, scope: !100, file: !1, line: 423, type: !27)
!279 = !DILocation(line: 423, column: 31, scope: !100)
!280 = !DILocalVariable(name: "flags", arg: 4, scope: !100, file: !1, line: 424, type: !27)
!281 = !DILocation(line: 424, column: 31, scope: !100)
!282 = !DILocalVariable(name: "timeout", arg: 5, scope: !100, file: !1, line: 425, type: !103)
!283 = !DILocation(line: 425, column: 35, scope: !100)
!284 = !DILocation(line: 427, column: 33, scope: !100)
!285 = !DILocation(line: 427, column: 37, scope: !100)
!286 = !DILocation(line: 427, column: 43, scope: !100)
!287 = !DILocation(line: 427, column: 49, scope: !100)
!288 = !DILocation(line: 427, column: 56, scope: !100)
!289 = !DILocation(line: 427, column: 10, scope: !100)
!290 = !DILocation(line: 427, column: 3, scope: !100)
!291 = !DILocalVariable(name: "dirfd", arg: 1, scope: !111, file: !1, line: 434, type: !9)
!292 = !DILocation(line: 434, column: 22, scope: !111)
!293 = !DILocalVariable(name: "path", arg: 2, scope: !111, file: !1, line: 435, type: !64)
!294 = !DILocation(line: 435, column: 30, scope: !111)
!295 = !DILocalVariable(name: "times", arg: 3, scope: !111, file: !1, line: 436, type: !114)
!296 = !DILocation(line: 436, column: 40, scope: !111)
!297 = !DILocalVariable(name: "flags", arg: 4, scope: !111, file: !1, line: 437, type: !9)
!298 = !DILocation(line: 437, column: 22, scope: !111)
!299 = !DILocation(line: 440, column: 34, scope: !111)
!300 = !DILocation(line: 440, column: 41, scope: !111)
!301 = !DILocation(line: 440, column: 47, scope: !111)
!302 = !DILocation(line: 440, column: 54, scope: !111)
!303 = !DILocation(line: 440, column: 10, scope: !111)
!304 = !DILocation(line: 440, column: 3, scope: !111)
!305 = !DILocalVariable(name: "fd", arg: 1, scope: !116, file: !1, line: 447, type: !9)
!306 = !DILocation(line: 447, column: 24, scope: !116)
!307 = !DILocalVariable(name: "iov", arg: 2, scope: !116, file: !1, line: 447, type: !122)
!308 = !DILocation(line: 447, column: 48, scope: !116)
!309 = !DILocalVariable(name: "iovcnt", arg: 3, scope: !116, file: !1, line: 447, type: !9)
!310 = !DILocation(line: 447, column: 57, scope: !116)
!311 = !DILocalVariable(name: "offset", arg: 4, scope: !116, file: !1, line: 447, type: !124)
!312 = !DILocation(line: 447, column: 73, scope: !116)
!313 = !DILocation(line: 449, column: 31, scope: !116)
!314 = !DILocation(line: 449, column: 35, scope: !116)
!315 = !DILocation(line: 449, column: 40, scope: !116)
!316 = !DILocation(line: 449, column: 54, scope: !116)
!317 = !DILocation(line: 449, column: 69, scope: !116)
!318 = !DILocation(line: 449, column: 76, scope: !116)
!319 = !DILocation(line: 449, column: 10, scope: !116)
!320 = !DILocation(line: 449, column: 3, scope: !116)
!321 = !DILocalVariable(name: "fd", arg: 1, scope: !125, file: !1, line: 456, type: !9)
!322 = !DILocation(line: 456, column: 25, scope: !125)
!323 = !DILocalVariable(name: "iov", arg: 2, scope: !125, file: !1, line: 456, type: !122)
!324 = !DILocation(line: 456, column: 49, scope: !125)
!325 = !DILocalVariable(name: "iovcnt", arg: 3, scope: !125, file: !1, line: 456, type: !9)
!326 = !DILocation(line: 456, column: 58, scope: !125)
!327 = !DILocalVariable(name: "offset", arg: 4, scope: !125, file: !1, line: 456, type: !124)
!328 = !DILocation(line: 456, column: 74, scope: !125)
!329 = !DILocation(line: 458, column: 32, scope: !125)
!330 = !DILocation(line: 458, column: 36, scope: !125)
!331 = !DILocation(line: 458, column: 41, scope: !125)
!332 = !DILocation(line: 458, column: 55, scope: !125)
!333 = !DILocation(line: 458, column: 70, scope: !125)
!334 = !DILocation(line: 458, column: 77, scope: !125)
!335 = !DILocation(line: 458, column: 10, scope: !125)
!336 = !DILocation(line: 458, column: 3, scope: !125)
!337 = !DILocalVariable(name: "oldfd", arg: 1, scope: !126, file: !1, line: 465, type: !9)
!338 = !DILocation(line: 465, column: 18, scope: !126)
!339 = !DILocalVariable(name: "newfd", arg: 2, scope: !126, file: !1, line: 465, type: !9)
!340 = !DILocation(line: 465, column: 29, scope: !126)
!341 = !DILocalVariable(name: "flags", arg: 3, scope: !126, file: !1, line: 465, type: !9)
!342 = !DILocation(line: 465, column: 40, scope: !126)
!343 = !DILocation(line: 467, column: 29, scope: !126)
!344 = !DILocation(line: 467, column: 36, scope: !126)
!345 = !DILocation(line: 467, column: 43, scope: !126)
!346 = !DILocation(line: 467, column: 10, scope: !126)
!347 = !DILocation(line: 467, column: 3, scope: !126)
