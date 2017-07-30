; ModuleID = '/data/download/cmake/cmake-master/Utilities/cmlibuv/src/unix/getaddrinfo.c'
target datalayout = "e-m:e-i64:64-f80:128-n8:16:32:64-S128"
target triple = "x86_64-unknown-linux-gnu"

%struct.uv_loop_s = type { i8*, i32, [2 x i8*], [2 x i8*], i32, i64, i32, [2 x i8*], [2 x i8*], %struct.uv__io_s**, i32, i32, [2 x i8*], %union.pthread_mutex_t, %struct.uv_async_s, %union.pthread_rwlock_t, %struct.uv_handle_s*, [2 x i8*], [2 x i8*], [2 x i8*], [2 x i8*], [2 x i8*], void ()*, %struct.uv__io_s, i32, %struct.anon.1, i64, i64, [2 x i32], %struct.uv__io_s, %struct.uv_signal_s, i32, %struct.uv__io_s, i8*, i32 }
%union.pthread_mutex_t = type { %struct.__pthread_mutex_s }
%struct.__pthread_mutex_s = type { i32, i32, i32, i32, i32, i16, i16, %struct.__pthread_internal_list }
%struct.__pthread_internal_list = type { %struct.__pthread_internal_list*, %struct.__pthread_internal_list* }
%struct.uv_async_s = type { i8*, %struct.uv_loop_s*, i32, void (%struct.uv_handle_s*)*, [2 x i8*], %union.anon.0, %struct.uv_handle_s*, i32, void (%struct.uv_async_s*)*, [2 x i8*], i32 }
%union.anon.0 = type { [4 x i8*] }
%union.pthread_rwlock_t = type { %struct.anon }
%struct.anon = type { i32, i32, i32, i32, i32, i32, i32, i32, i64, i64, i32 }
%struct.uv_handle_s = type { i8*, %struct.uv_loop_s*, i32, {}*, [2 x i8*], %union.anon, %struct.uv_handle_s*, i32 }
%union.anon = type { [4 x i8*] }
%struct.anon.1 = type { i8*, i32 }
%struct.uv_signal_s = type { i8*, %struct.uv_loop_s*, i32, void (%struct.uv_handle_s*)*, [2 x i8*], %union.anon.2, %struct.uv_handle_s*, i32, void (%struct.uv_signal_s*, i32)*, i32, %struct.anon.3, i32, i32 }
%union.anon.2 = type { [4 x i8*] }
%struct.anon.3 = type { %struct.uv_signal_s*, %struct.uv_signal_s*, %struct.uv_signal_s*, i32 }
%struct.uv__io_s = type { void (%struct.uv_loop_s*, %struct.uv__io_s*, i32)*, [2 x i8*], [2 x i8*], i32, i32, i32 }
%struct.uv_getaddrinfo_s = type { i8*, i32, [2 x i8*], [4 x i8*], %struct.uv_loop_s*, %struct.uv__work, void (%struct.uv_getaddrinfo_s*, i32, %struct.addrinfo*)*, %struct.addrinfo*, i8*, i8*, %struct.addrinfo*, i32 }
%struct.uv__work = type { void (%struct.uv__work*)*, void (%struct.uv__work*, i32)*, %struct.uv_loop_s*, [2 x i8*] }
%struct.addrinfo = type { i32, i32, i32, i32, i32, %struct.sockaddr*, i8*, %struct.addrinfo* }
%struct.sockaddr = type { i16, [14 x i8] }

@.str = private unnamed_addr constant [28 x i8] c"!\22unknown EAI_* error code\22\00", align 1
@.str.1 = private unnamed_addr constant [75 x i8] c"/data/download/cmake/cmake-master/Utilities/cmlibuv/src/unix/getaddrinfo.c\00", align 1
@__PRETTY_FUNCTION__.uv__getaddrinfo_translate_error = private unnamed_addr constant [41 x i8] c"int uv__getaddrinfo_translate_error(int)\00", align 1
@.str.2 = private unnamed_addr constant [123 x i8] c"(((const QUEUE *) (&(req->loop)->active_reqs) == (const QUEUE *) (*(QUEUE **) &((*(&(req->loop)->active_reqs))[0]))) == 0)\00", align 1
@__PRETTY_FUNCTION__.uv__getaddrinfo_done = private unnamed_addr constant [50 x i8] c"void uv__getaddrinfo_done(struct uv__work *, int)\00", align 1
@.str.3 = private unnamed_addr constant [2 x i8] c"0\00", align 1
@.str.4 = private unnamed_addr constant [18 x i8] c"req->retcode == 0\00", align 1

; Function Attrs: nounwind uwtable
define i32 @uv__getaddrinfo_translate_error(i32 %sys_err) #0 !dbg !394 {
entry:
  %retval = alloca i32, align 4
  %sys_err.addr = alloca i32, align 4
  store i32 %sys_err, i32* %sys_err.addr, align 4
  call void @llvm.dbg.declare(metadata i32* %sys_err.addr, metadata !413, metadata !414), !dbg !415
  %0 = load i32, i32* %sys_err.addr, align 4, !dbg !416
  switch i32 %0, label %sw.epilog [
    i32 0, label %sw.bb
    i32 -9, label %sw.bb1
    i32 -3, label %sw.bb2
    i32 -1, label %sw.bb3
    i32 -101, label %sw.bb4
    i32 -4, label %sw.bb5
    i32 -6, label %sw.bb6
    i32 -10, label %sw.bb7
    i32 -5, label %sw.bb8
    i32 -2, label %sw.bb9
    i32 -12, label %sw.bb10
    i32 -8, label %sw.bb11
    i32 -7, label %sw.bb12
    i32 -11, label %sw.bb13
  ], !dbg !417

sw.bb:                                            ; preds = %entry
  store i32 0, i32* %retval, align 4, !dbg !418
  br label %return, !dbg !418

sw.bb1:                                           ; preds = %entry
  store i32 -3000, i32* %retval, align 4, !dbg !420
  br label %return, !dbg !420

sw.bb2:                                           ; preds = %entry
  store i32 -3001, i32* %retval, align 4, !dbg !421
  br label %return, !dbg !421

sw.bb3:                                           ; preds = %entry
  store i32 -3002, i32* %retval, align 4, !dbg !422
  br label %return, !dbg !422

sw.bb4:                                           ; preds = %entry
  store i32 -3003, i32* %retval, align 4, !dbg !423
  br label %return, !dbg !423

sw.bb5:                                           ; preds = %entry
  store i32 -3004, i32* %retval, align 4, !dbg !424
  br label %return, !dbg !424

sw.bb6:                                           ; preds = %entry
  store i32 -3005, i32* %retval, align 4, !dbg !425
  br label %return, !dbg !425

sw.bb7:                                           ; preds = %entry
  store i32 -3006, i32* %retval, align 4, !dbg !426
  br label %return, !dbg !426

sw.bb8:                                           ; preds = %entry
  store i32 -3007, i32* %retval, align 4, !dbg !427
  br label %return, !dbg !427

sw.bb9:                                           ; preds = %entry
  store i32 -3008, i32* %retval, align 4, !dbg !428
  br label %return, !dbg !428

sw.bb10:                                          ; preds = %entry
  store i32 -3009, i32* %retval, align 4, !dbg !429
  br label %return, !dbg !429

sw.bb11:                                          ; preds = %entry
  store i32 -3010, i32* %retval, align 4, !dbg !430
  br label %return, !dbg !430

sw.bb12:                                          ; preds = %entry
  store i32 -3011, i32* %retval, align 4, !dbg !431
  br label %return, !dbg !431

sw.bb13:                                          ; preds = %entry
  %call = call i32* @__errno_location() #1, !dbg !432
  %1 = load i32, i32* %call, align 4, !dbg !432
  %sub = sub nsw i32 0, %1, !dbg !433
  store i32 %sub, i32* %retval, align 4, !dbg !434
  br label %return, !dbg !434

sw.epilog:                                        ; preds = %entry
  call void @__assert_fail(i8* getelementptr inbounds ([28 x i8], [28 x i8]* @.str, i32 0, i32 0), i8* getelementptr inbounds ([75 x i8], [75 x i8]* @.str.1, i32 0, i32 0), i32 91, i8* getelementptr inbounds ([41 x i8], [41 x i8]* @__PRETTY_FUNCTION__.uv__getaddrinfo_translate_error, i32 0, i32 0)) #8, !dbg !435
  unreachable, !dbg !435

return:                                           ; preds = %sw.bb13, %sw.bb12, %sw.bb11, %sw.bb10, %sw.bb9, %sw.bb8, %sw.bb7, %sw.bb6, %sw.bb5, %sw.bb4, %sw.bb3, %sw.bb2, %sw.bb1, %sw.bb
  %2 = load i32, i32* %retval, align 4, !dbg !436
  ret i32 %2, !dbg !436
}

; Function Attrs: nounwind readnone
declare void @llvm.dbg.declare(metadata, metadata, metadata) #1

; Function Attrs: nounwind readnone
declare i32* @__errno_location() #2

; Function Attrs: noreturn nounwind
declare void @__assert_fail(i8*, i8*, i32, i8*) #3

; Function Attrs: nounwind uwtable
define i32 @uv_getaddrinfo(%struct.uv_loop_s* %loop, %struct.uv_getaddrinfo_s* %req, void (%struct.uv_getaddrinfo_s*, i32, %struct.addrinfo*)* %cb, i8* %hostname, i8* %service, %struct.addrinfo* %hints) #0 !dbg !398 {
entry:
  %retval = alloca i32, align 4
  %loop.addr = alloca %struct.uv_loop_s*, align 8
  %req.addr = alloca %struct.uv_getaddrinfo_s*, align 8
  %cb.addr = alloca void (%struct.uv_getaddrinfo_s*, i32, %struct.addrinfo*)*, align 8
  %hostname.addr = alloca i8*, align 8
  %service.addr = alloca i8*, align 8
  %hints.addr = alloca %struct.addrinfo*, align 8
  %hostname_len = alloca i64, align 8
  %service_len = alloca i64, align 8
  %hints_len = alloca i64, align 8
  %len = alloca i64, align 8
  %buf = alloca i8*, align 8
  store %struct.uv_loop_s* %loop, %struct.uv_loop_s** %loop.addr, align 8
  call void @llvm.dbg.declare(metadata %struct.uv_loop_s** %loop.addr, metadata !437, metadata !414), !dbg !438
  store %struct.uv_getaddrinfo_s* %req, %struct.uv_getaddrinfo_s** %req.addr, align 8
  call void @llvm.dbg.declare(metadata %struct.uv_getaddrinfo_s** %req.addr, metadata !439, metadata !414), !dbg !440
  store void (%struct.uv_getaddrinfo_s*, i32, %struct.addrinfo*)* %cb, void (%struct.uv_getaddrinfo_s*, i32, %struct.addrinfo*)** %cb.addr, align 8
  call void @llvm.dbg.declare(metadata void (%struct.uv_getaddrinfo_s*, i32, %struct.addrinfo*)** %cb.addr, metadata !441, metadata !414), !dbg !442
  store i8* %hostname, i8** %hostname.addr, align 8
  call void @llvm.dbg.declare(metadata i8** %hostname.addr, metadata !443, metadata !414), !dbg !444
  store i8* %service, i8** %service.addr, align 8
  call void @llvm.dbg.declare(metadata i8** %service.addr, metadata !445, metadata !414), !dbg !446
  store %struct.addrinfo* %hints, %struct.addrinfo** %hints.addr, align 8
  call void @llvm.dbg.declare(metadata %struct.addrinfo** %hints.addr, metadata !447, metadata !414), !dbg !448
  call void @llvm.dbg.declare(metadata i64* %hostname_len, metadata !449, metadata !414), !dbg !452
  call void @llvm.dbg.declare(metadata i64* %service_len, metadata !453, metadata !414), !dbg !454
  call void @llvm.dbg.declare(metadata i64* %hints_len, metadata !455, metadata !414), !dbg !456
  call void @llvm.dbg.declare(metadata i64* %len, metadata !457, metadata !414), !dbg !458
  call void @llvm.dbg.declare(metadata i8** %buf, metadata !459, metadata !414), !dbg !460
  %0 = load %struct.uv_getaddrinfo_s*, %struct.uv_getaddrinfo_s** %req.addr, align 8, !dbg !461
  %cmp = icmp eq %struct.uv_getaddrinfo_s* %0, null, !dbg !463
  br i1 %cmp, label %if.then, label %lor.lhs.false, !dbg !464

lor.lhs.false:                                    ; preds = %entry
  %1 = load i8*, i8** %hostname.addr, align 8, !dbg !465
  %cmp1 = icmp eq i8* %1, null, !dbg !467
  br i1 %cmp1, label %land.lhs.true, label %if.end, !dbg !468

land.lhs.true:                                    ; preds = %lor.lhs.false
  %2 = load i8*, i8** %service.addr, align 8, !dbg !469
  %cmp2 = icmp eq i8* %2, null, !dbg !471
  br i1 %cmp2, label %if.then, label %if.end, !dbg !472

if.then:                                          ; preds = %land.lhs.true, %entry
  store i32 -22, i32* %retval, align 4, !dbg !473
  br label %return, !dbg !473

if.end:                                           ; preds = %land.lhs.true, %lor.lhs.false
  %3 = load i8*, i8** %hostname.addr, align 8, !dbg !474
  %tobool = icmp ne i8* %3, null, !dbg !474
  br i1 %tobool, label %cond.true, label %cond.false, !dbg !474

cond.true:                                        ; preds = %if.end
  %4 = load i8*, i8** %hostname.addr, align 8, !dbg !475
  %call = call i64 @strlen(i8* %4) #9, !dbg !477
  %add = add i64 %call, 1, !dbg !478
  br label %cond.end, !dbg !479

cond.false:                                       ; preds = %if.end
  br label %cond.end, !dbg !480

cond.end:                                         ; preds = %cond.false, %cond.true
  %cond = phi i64 [ %add, %cond.true ], [ 0, %cond.false ], !dbg !482
  store i64 %cond, i64* %hostname_len, align 8, !dbg !484
  %5 = load i8*, i8** %service.addr, align 8, !dbg !485
  %tobool3 = icmp ne i8* %5, null, !dbg !485
  br i1 %tobool3, label %cond.true4, label %cond.false7, !dbg !485

cond.true4:                                       ; preds = %cond.end
  %6 = load i8*, i8** %service.addr, align 8, !dbg !486
  %call5 = call i64 @strlen(i8* %6) #9, !dbg !487
  %add6 = add i64 %call5, 1, !dbg !488
  br label %cond.end8, !dbg !489

cond.false7:                                      ; preds = %cond.end
  br label %cond.end8, !dbg !490

cond.end8:                                        ; preds = %cond.false7, %cond.true4
  %cond9 = phi i64 [ %add6, %cond.true4 ], [ 0, %cond.false7 ], !dbg !491
  store i64 %cond9, i64* %service_len, align 8, !dbg !492
  %7 = load %struct.addrinfo*, %struct.addrinfo** %hints.addr, align 8, !dbg !493
  %tobool10 = icmp ne %struct.addrinfo* %7, null, !dbg !493
  %cond11 = select i1 %tobool10, i64 48, i64 0, !dbg !493
  store i64 %cond11, i64* %hints_len, align 8, !dbg !494
  %8 = load i64, i64* %hostname_len, align 8, !dbg !495
  %9 = load i64, i64* %service_len, align 8, !dbg !496
  %add12 = add i64 %8, %9, !dbg !497
  %10 = load i64, i64* %hints_len, align 8, !dbg !498
  %add13 = add i64 %add12, %10, !dbg !499
  %call14 = call i8* @uv__malloc(i64 %add13), !dbg !500
  store i8* %call14, i8** %buf, align 8, !dbg !501
  %11 = load i8*, i8** %buf, align 8, !dbg !502
  %cmp15 = icmp eq i8* %11, null, !dbg !504
  br i1 %cmp15, label %if.then16, label %if.end17, !dbg !505

if.then16:                                        ; preds = %cond.end8
  store i32 -12, i32* %retval, align 4, !dbg !506
  br label %return, !dbg !506

if.end17:                                         ; preds = %cond.end8
  br label %do.body, !dbg !507

do.body:                                          ; preds = %if.end17
  br label %do.body18, !dbg !508

do.body18:                                        ; preds = %do.body
  %12 = load %struct.uv_getaddrinfo_s*, %struct.uv_getaddrinfo_s** %req.addr, align 8, !dbg !511
  %type = getelementptr inbounds %struct.uv_getaddrinfo_s, %struct.uv_getaddrinfo_s* %12, i32 0, i32 1, !dbg !511
  store i32 8, i32* %type, align 8, !dbg !511
  br label %do.end, !dbg !511

do.end:                                           ; preds = %do.body18
  br label %do.body19, !dbg !514

do.body19:                                        ; preds = %do.end
  br label %do.body20, !dbg !516

do.body20:                                        ; preds = %do.body19
  %13 = load %struct.uv_loop_s*, %struct.uv_loop_s** %loop.addr, align 8, !dbg !519
  %active_reqs = getelementptr inbounds %struct.uv_loop_s, %struct.uv_loop_s* %13, i32 0, i32 3, !dbg !519
  %14 = load %struct.uv_getaddrinfo_s*, %struct.uv_getaddrinfo_s** %req.addr, align 8, !dbg !519
  %active_queue = getelementptr inbounds %struct.uv_getaddrinfo_s, %struct.uv_getaddrinfo_s* %14, i32 0, i32 2, !dbg !519
  %arrayidx = getelementptr inbounds [2 x i8*], [2 x i8*]* %active_queue, i64 0, i64 0, !dbg !519
  %15 = bitcast i8** %arrayidx to [2 x i8*]**, !dbg !519
  store [2 x i8*]* %active_reqs, [2 x i8*]** %15, align 8, !dbg !519
  %16 = load %struct.uv_loop_s*, %struct.uv_loop_s** %loop.addr, align 8, !dbg !519
  %active_reqs21 = getelementptr inbounds %struct.uv_loop_s, %struct.uv_loop_s* %16, i32 0, i32 3, !dbg !519
  %arrayidx22 = getelementptr inbounds [2 x i8*], [2 x i8*]* %active_reqs21, i64 0, i64 1, !dbg !519
  %17 = bitcast i8** %arrayidx22 to [2 x i8*]**, !dbg !519
  %18 = load [2 x i8*]*, [2 x i8*]** %17, align 8, !dbg !519
  %19 = load %struct.uv_getaddrinfo_s*, %struct.uv_getaddrinfo_s** %req.addr, align 8, !dbg !519
  %active_queue23 = getelementptr inbounds %struct.uv_getaddrinfo_s, %struct.uv_getaddrinfo_s* %19, i32 0, i32 2, !dbg !519
  %arrayidx24 = getelementptr inbounds [2 x i8*], [2 x i8*]* %active_queue23, i64 0, i64 1, !dbg !519
  %20 = bitcast i8** %arrayidx24 to [2 x i8*]**, !dbg !519
  store [2 x i8*]* %18, [2 x i8*]** %20, align 8, !dbg !519
  %21 = load %struct.uv_getaddrinfo_s*, %struct.uv_getaddrinfo_s** %req.addr, align 8, !dbg !519
  %active_queue25 = getelementptr inbounds %struct.uv_getaddrinfo_s, %struct.uv_getaddrinfo_s* %21, i32 0, i32 2, !dbg !519
  %22 = load %struct.uv_getaddrinfo_s*, %struct.uv_getaddrinfo_s** %req.addr, align 8, !dbg !519
  %active_queue26 = getelementptr inbounds %struct.uv_getaddrinfo_s, %struct.uv_getaddrinfo_s* %22, i32 0, i32 2, !dbg !519
  %arrayidx27 = getelementptr inbounds [2 x i8*], [2 x i8*]* %active_queue26, i64 0, i64 1, !dbg !519
  %23 = bitcast i8** %arrayidx27 to [2 x i8*]**, !dbg !519
  %24 = load [2 x i8*]*, [2 x i8*]** %23, align 8, !dbg !519
  %arrayidx28 = getelementptr inbounds [2 x i8*], [2 x i8*]* %24, i64 0, i64 0, !dbg !519
  %25 = bitcast i8** %arrayidx28 to [2 x i8*]**, !dbg !519
  store [2 x i8*]* %active_queue25, [2 x i8*]** %25, align 8, !dbg !519
  %26 = load %struct.uv_getaddrinfo_s*, %struct.uv_getaddrinfo_s** %req.addr, align 8, !dbg !519
  %active_queue29 = getelementptr inbounds %struct.uv_getaddrinfo_s, %struct.uv_getaddrinfo_s* %26, i32 0, i32 2, !dbg !519
  %27 = load %struct.uv_loop_s*, %struct.uv_loop_s** %loop.addr, align 8, !dbg !519
  %active_reqs30 = getelementptr inbounds %struct.uv_loop_s, %struct.uv_loop_s* %27, i32 0, i32 3, !dbg !519
  %arrayidx31 = getelementptr inbounds [2 x i8*], [2 x i8*]* %active_reqs30, i64 0, i64 1, !dbg !519
  %28 = bitcast i8** %arrayidx31 to [2 x i8*]**, !dbg !519
  store [2 x i8*]* %active_queue29, [2 x i8*]** %28, align 8, !dbg !519
  br label %do.end32, !dbg !519

do.end32:                                         ; preds = %do.body20
  br label %do.end33, !dbg !522

do.end33:                                         ; preds = %do.end32
  br label %do.end34, !dbg !524

do.end34:                                         ; preds = %do.end33
  %29 = load %struct.uv_loop_s*, %struct.uv_loop_s** %loop.addr, align 8, !dbg !526
  %30 = load %struct.uv_getaddrinfo_s*, %struct.uv_getaddrinfo_s** %req.addr, align 8, !dbg !527
  %loop35 = getelementptr inbounds %struct.uv_getaddrinfo_s, %struct.uv_getaddrinfo_s* %30, i32 0, i32 4, !dbg !528
  store %struct.uv_loop_s* %29, %struct.uv_loop_s** %loop35, align 8, !dbg !529
  %31 = load void (%struct.uv_getaddrinfo_s*, i32, %struct.addrinfo*)*, void (%struct.uv_getaddrinfo_s*, i32, %struct.addrinfo*)** %cb.addr, align 8, !dbg !530
  %32 = load %struct.uv_getaddrinfo_s*, %struct.uv_getaddrinfo_s** %req.addr, align 8, !dbg !531
  %cb36 = getelementptr inbounds %struct.uv_getaddrinfo_s, %struct.uv_getaddrinfo_s* %32, i32 0, i32 6, !dbg !532
  store void (%struct.uv_getaddrinfo_s*, i32, %struct.addrinfo*)* %31, void (%struct.uv_getaddrinfo_s*, i32, %struct.addrinfo*)** %cb36, align 8, !dbg !533
  %33 = load %struct.uv_getaddrinfo_s*, %struct.uv_getaddrinfo_s** %req.addr, align 8, !dbg !534
  %addrinfo = getelementptr inbounds %struct.uv_getaddrinfo_s, %struct.uv_getaddrinfo_s* %33, i32 0, i32 10, !dbg !535
  store %struct.addrinfo* null, %struct.addrinfo** %addrinfo, align 8, !dbg !536
  %34 = load %struct.uv_getaddrinfo_s*, %struct.uv_getaddrinfo_s** %req.addr, align 8, !dbg !537
  %hints37 = getelementptr inbounds %struct.uv_getaddrinfo_s, %struct.uv_getaddrinfo_s* %34, i32 0, i32 7, !dbg !538
  store %struct.addrinfo* null, %struct.addrinfo** %hints37, align 8, !dbg !539
  %35 = load %struct.uv_getaddrinfo_s*, %struct.uv_getaddrinfo_s** %req.addr, align 8, !dbg !540
  %service38 = getelementptr inbounds %struct.uv_getaddrinfo_s, %struct.uv_getaddrinfo_s* %35, i32 0, i32 9, !dbg !541
  store i8* null, i8** %service38, align 8, !dbg !542
  %36 = load %struct.uv_getaddrinfo_s*, %struct.uv_getaddrinfo_s** %req.addr, align 8, !dbg !543
  %hostname39 = getelementptr inbounds %struct.uv_getaddrinfo_s, %struct.uv_getaddrinfo_s* %36, i32 0, i32 8, !dbg !544
  store i8* null, i8** %hostname39, align 8, !dbg !545
  %37 = load %struct.uv_getaddrinfo_s*, %struct.uv_getaddrinfo_s** %req.addr, align 8, !dbg !546
  %retcode = getelementptr inbounds %struct.uv_getaddrinfo_s, %struct.uv_getaddrinfo_s* %37, i32 0, i32 11, !dbg !547
  store i32 0, i32* %retcode, align 8, !dbg !548
  store i64 0, i64* %len, align 8, !dbg !549
  %38 = load %struct.addrinfo*, %struct.addrinfo** %hints.addr, align 8, !dbg !550
  %tobool40 = icmp ne %struct.addrinfo* %38, null, !dbg !550
  br i1 %tobool40, label %if.then41, label %if.end44, !dbg !552

if.then41:                                        ; preds = %do.end34
  %39 = load i8*, i8** %buf, align 8, !dbg !553
  %40 = load i64, i64* %len, align 8, !dbg !555
  %add.ptr = getelementptr inbounds i8, i8* %39, i64 %40, !dbg !556
  %41 = load %struct.addrinfo*, %struct.addrinfo** %hints.addr, align 8, !dbg !557
  %42 = bitcast %struct.addrinfo* %41 to i8*, !dbg !558
  call void @llvm.memcpy.p0i8.p0i8.i64(i8* %add.ptr, i8* %42, i64 48, i32 1, i1 false), !dbg !558
  %43 = bitcast i8* %add.ptr to %struct.addrinfo*, !dbg !558
  %44 = load %struct.uv_getaddrinfo_s*, %struct.uv_getaddrinfo_s** %req.addr, align 8, !dbg !559
  %hints42 = getelementptr inbounds %struct.uv_getaddrinfo_s, %struct.uv_getaddrinfo_s* %44, i32 0, i32 7, !dbg !560
  store %struct.addrinfo* %43, %struct.addrinfo** %hints42, align 8, !dbg !561
  %45 = load i64, i64* %len, align 8, !dbg !562
  %add43 = add i64 %45, 48, !dbg !562
  store i64 %add43, i64* %len, align 8, !dbg !562
  br label %if.end44, !dbg !563

if.end44:                                         ; preds = %if.then41, %do.end34
  %46 = load i8*, i8** %service.addr, align 8, !dbg !564
  %tobool45 = icmp ne i8* %46, null, !dbg !564
  br i1 %tobool45, label %if.then46, label %if.end50, !dbg !566

if.then46:                                        ; preds = %if.end44
  %47 = load i8*, i8** %buf, align 8, !dbg !567
  %48 = load i64, i64* %len, align 8, !dbg !569
  %add.ptr47 = getelementptr inbounds i8, i8* %47, i64 %48, !dbg !570
  %49 = load i8*, i8** %service.addr, align 8, !dbg !571
  %50 = load i64, i64* %service_len, align 8, !dbg !572
  call void @llvm.memcpy.p0i8.p0i8.i64(i8* %add.ptr47, i8* %49, i64 %50, i32 1, i1 false), !dbg !573
  %51 = load %struct.uv_getaddrinfo_s*, %struct.uv_getaddrinfo_s** %req.addr, align 8, !dbg !574
  %service48 = getelementptr inbounds %struct.uv_getaddrinfo_s, %struct.uv_getaddrinfo_s* %51, i32 0, i32 9, !dbg !575
  store i8* %add.ptr47, i8** %service48, align 8, !dbg !576
  %52 = load i64, i64* %service_len, align 8, !dbg !577
  %53 = load i64, i64* %len, align 8, !dbg !578
  %add49 = add i64 %53, %52, !dbg !578
  store i64 %add49, i64* %len, align 8, !dbg !578
  br label %if.end50, !dbg !579

if.end50:                                         ; preds = %if.then46, %if.end44
  %54 = load i8*, i8** %hostname.addr, align 8, !dbg !580
  %tobool51 = icmp ne i8* %54, null, !dbg !580
  br i1 %tobool51, label %if.then52, label %if.end55, !dbg !582

if.then52:                                        ; preds = %if.end50
  %55 = load i8*, i8** %buf, align 8, !dbg !583
  %56 = load i64, i64* %len, align 8, !dbg !584
  %add.ptr53 = getelementptr inbounds i8, i8* %55, i64 %56, !dbg !585
  %57 = load i8*, i8** %hostname.addr, align 8, !dbg !586
  %58 = load i64, i64* %hostname_len, align 8, !dbg !587
  call void @llvm.memcpy.p0i8.p0i8.i64(i8* %add.ptr53, i8* %57, i64 %58, i32 1, i1 false), !dbg !588
  %59 = load %struct.uv_getaddrinfo_s*, %struct.uv_getaddrinfo_s** %req.addr, align 8, !dbg !589
  %hostname54 = getelementptr inbounds %struct.uv_getaddrinfo_s, %struct.uv_getaddrinfo_s* %59, i32 0, i32 8, !dbg !590
  store i8* %add.ptr53, i8** %hostname54, align 8, !dbg !591
  br label %if.end55, !dbg !589

if.end55:                                         ; preds = %if.then52, %if.end50
  %60 = load void (%struct.uv_getaddrinfo_s*, i32, %struct.addrinfo*)*, void (%struct.uv_getaddrinfo_s*, i32, %struct.addrinfo*)** %cb.addr, align 8, !dbg !592
  %tobool56 = icmp ne void (%struct.uv_getaddrinfo_s*, i32, %struct.addrinfo*)* %60, null, !dbg !592
  br i1 %tobool56, label %if.then57, label %if.else, !dbg !594

if.then57:                                        ; preds = %if.end55
  %61 = load %struct.uv_loop_s*, %struct.uv_loop_s** %loop.addr, align 8, !dbg !595
  %62 = load %struct.uv_getaddrinfo_s*, %struct.uv_getaddrinfo_s** %req.addr, align 8, !dbg !597
  %work_req = getelementptr inbounds %struct.uv_getaddrinfo_s, %struct.uv_getaddrinfo_s* %62, i32 0, i32 5, !dbg !598
  call void @uv__work_submit(%struct.uv_loop_s* %61, %struct.uv__work* %work_req, void (%struct.uv__work*)* @uv__getaddrinfo_work, void (%struct.uv__work*, i32)* @uv__getaddrinfo_done), !dbg !599
  store i32 0, i32* %retval, align 4, !dbg !600
  br label %return, !dbg !600

if.else:                                          ; preds = %if.end55
  %63 = load %struct.uv_getaddrinfo_s*, %struct.uv_getaddrinfo_s** %req.addr, align 8, !dbg !601
  %work_req58 = getelementptr inbounds %struct.uv_getaddrinfo_s, %struct.uv_getaddrinfo_s* %63, i32 0, i32 5, !dbg !603
  call void @uv__getaddrinfo_work(%struct.uv__work* %work_req58), !dbg !604
  %64 = load %struct.uv_getaddrinfo_s*, %struct.uv_getaddrinfo_s** %req.addr, align 8, !dbg !605
  %work_req59 = getelementptr inbounds %struct.uv_getaddrinfo_s, %struct.uv_getaddrinfo_s* %64, i32 0, i32 5, !dbg !606
  call void @uv__getaddrinfo_done(%struct.uv__work* %work_req59, i32 0), !dbg !607
  %65 = load %struct.uv_getaddrinfo_s*, %struct.uv_getaddrinfo_s** %req.addr, align 8, !dbg !608
  %retcode60 = getelementptr inbounds %struct.uv_getaddrinfo_s, %struct.uv_getaddrinfo_s* %65, i32 0, i32 11, !dbg !609
  %66 = load i32, i32* %retcode60, align 8, !dbg !609
  store i32 %66, i32* %retval, align 4, !dbg !610
  br label %return, !dbg !610

return:                                           ; preds = %if.else, %if.then57, %if.then16, %if.then
  %67 = load i32, i32* %retval, align 4, !dbg !611
  ret i32 %67, !dbg !611
}

; Function Attrs: nounwind readonly
declare i64 @strlen(i8*) #4

declare i8* @uv__malloc(i64) #5

; Function Attrs: argmemonly nounwind
declare void @llvm.memcpy.p0i8.p0i8.i64(i8* nocapture, i8* nocapture readonly, i64, i32, i1) #6

declare void @uv__work_submit(%struct.uv_loop_s*, %struct.uv__work*, void (%struct.uv__work*)*, void (%struct.uv__work*, i32)*) #5

; Function Attrs: nounwind uwtable
define internal void @uv__getaddrinfo_work(%struct.uv__work* %w) #0 !dbg !408 {
entry:
  %w.addr = alloca %struct.uv__work*, align 8
  %req = alloca %struct.uv_getaddrinfo_s*, align 8
  %err = alloca i32, align 4
  store %struct.uv__work* %w, %struct.uv__work** %w.addr, align 8
  call void @llvm.dbg.declare(metadata %struct.uv__work** %w.addr, metadata !612, metadata !414), !dbg !613
  call void @llvm.dbg.declare(metadata %struct.uv_getaddrinfo_s** %req, metadata !614, metadata !414), !dbg !615
  call void @llvm.dbg.declare(metadata i32* %err, metadata !616, metadata !414), !dbg !617
  %0 = load %struct.uv__work*, %struct.uv__work** %w.addr, align 8, !dbg !618
  %1 = bitcast %struct.uv__work* %0 to i8*, !dbg !618
  %add.ptr = getelementptr inbounds i8, i8* %1, i64 -72, !dbg !618
  %2 = bitcast i8* %add.ptr to %struct.uv_getaddrinfo_s*, !dbg !618
  store %struct.uv_getaddrinfo_s* %2, %struct.uv_getaddrinfo_s** %req, align 8, !dbg !619
  %3 = load %struct.uv_getaddrinfo_s*, %struct.uv_getaddrinfo_s** %req, align 8, !dbg !620
  %hostname = getelementptr inbounds %struct.uv_getaddrinfo_s, %struct.uv_getaddrinfo_s* %3, i32 0, i32 8, !dbg !621
  %4 = load i8*, i8** %hostname, align 8, !dbg !621
  %5 = load %struct.uv_getaddrinfo_s*, %struct.uv_getaddrinfo_s** %req, align 8, !dbg !622
  %service = getelementptr inbounds %struct.uv_getaddrinfo_s, %struct.uv_getaddrinfo_s* %5, i32 0, i32 9, !dbg !623
  %6 = load i8*, i8** %service, align 8, !dbg !623
  %7 = load %struct.uv_getaddrinfo_s*, %struct.uv_getaddrinfo_s** %req, align 8, !dbg !624
  %hints = getelementptr inbounds %struct.uv_getaddrinfo_s, %struct.uv_getaddrinfo_s* %7, i32 0, i32 7, !dbg !625
  %8 = load %struct.addrinfo*, %struct.addrinfo** %hints, align 8, !dbg !625
  %9 = load %struct.uv_getaddrinfo_s*, %struct.uv_getaddrinfo_s** %req, align 8, !dbg !626
  %addrinfo = getelementptr inbounds %struct.uv_getaddrinfo_s, %struct.uv_getaddrinfo_s* %9, i32 0, i32 10, !dbg !627
  %call = call i32 @getaddrinfo(i8* %4, i8* %6, %struct.addrinfo* %8, %struct.addrinfo** %addrinfo), !dbg !628
  store i32 %call, i32* %err, align 4, !dbg !629
  %10 = load i32, i32* %err, align 4, !dbg !630
  %call1 = call i32 @uv__getaddrinfo_translate_error(i32 %10), !dbg !631
  %11 = load %struct.uv_getaddrinfo_s*, %struct.uv_getaddrinfo_s** %req, align 8, !dbg !632
  %retcode = getelementptr inbounds %struct.uv_getaddrinfo_s, %struct.uv_getaddrinfo_s* %11, i32 0, i32 11, !dbg !633
  store i32 %call1, i32* %retcode, align 8, !dbg !634
  ret void, !dbg !635
}

; Function Attrs: nounwind uwtable
define internal void @uv__getaddrinfo_done(%struct.uv__work* %w, i32 %status) #0 !dbg !409 {
entry:
  %w.addr = alloca %struct.uv__work*, align 8
  %status.addr = alloca i32, align 4
  %req = alloca %struct.uv_getaddrinfo_s*, align 8
  store %struct.uv__work* %w, %struct.uv__work** %w.addr, align 8
  call void @llvm.dbg.declare(metadata %struct.uv__work** %w.addr, metadata !636, metadata !414), !dbg !637
  store i32 %status, i32* %status.addr, align 4
  call void @llvm.dbg.declare(metadata i32* %status.addr, metadata !638, metadata !414), !dbg !639
  call void @llvm.dbg.declare(metadata %struct.uv_getaddrinfo_s** %req, metadata !640, metadata !414), !dbg !641
  %0 = load %struct.uv__work*, %struct.uv__work** %w.addr, align 8, !dbg !642
  %1 = bitcast %struct.uv__work* %0 to i8*, !dbg !642
  %add.ptr = getelementptr inbounds i8, i8* %1, i64 -72, !dbg !642
  %2 = bitcast i8* %add.ptr to %struct.uv_getaddrinfo_s*, !dbg !642
  store %struct.uv_getaddrinfo_s* %2, %struct.uv_getaddrinfo_s** %req, align 8, !dbg !643
  br label %do.body, !dbg !644

do.body:                                          ; preds = %entry
  %3 = load %struct.uv_getaddrinfo_s*, %struct.uv_getaddrinfo_s** %req, align 8, !dbg !645
  %loop = getelementptr inbounds %struct.uv_getaddrinfo_s, %struct.uv_getaddrinfo_s* %3, i32 0, i32 4, !dbg !645
  %4 = load %struct.uv_loop_s*, %struct.uv_loop_s** %loop, align 8, !dbg !645
  %active_reqs = getelementptr inbounds %struct.uv_loop_s, %struct.uv_loop_s* %4, i32 0, i32 3, !dbg !645
  %5 = load %struct.uv_getaddrinfo_s*, %struct.uv_getaddrinfo_s** %req, align 8, !dbg !645
  %loop1 = getelementptr inbounds %struct.uv_getaddrinfo_s, %struct.uv_getaddrinfo_s* %5, i32 0, i32 4, !dbg !645
  %6 = load %struct.uv_loop_s*, %struct.uv_loop_s** %loop1, align 8, !dbg !645
  %active_reqs2 = getelementptr inbounds %struct.uv_loop_s, %struct.uv_loop_s* %6, i32 0, i32 3, !dbg !645
  %arrayidx = getelementptr inbounds [2 x i8*], [2 x i8*]* %active_reqs2, i64 0, i64 0, !dbg !645
  %7 = bitcast i8** %arrayidx to [2 x i8*]**, !dbg !645
  %8 = load [2 x i8*]*, [2 x i8*]** %7, align 8, !dbg !645
  %cmp = icmp eq [2 x i8*]* %active_reqs, %8, !dbg !645
  %conv = zext i1 %cmp to i32, !dbg !645
  %cmp3 = icmp eq i32 %conv, 0, !dbg !645
  br i1 %cmp3, label %cond.true, label %cond.false, !dbg !645

cond.true:                                        ; preds = %do.body
  br label %cond.end, !dbg !648

cond.false:                                       ; preds = %do.body
  call void @__assert_fail(i8* getelementptr inbounds ([123 x i8], [123 x i8]* @.str.2, i32 0, i32 0), i8* getelementptr inbounds ([75 x i8], [75 x i8]* @.str.1, i32 0, i32 0), i32 111, i8* getelementptr inbounds ([50 x i8], [50 x i8]* @__PRETTY_FUNCTION__.uv__getaddrinfo_done, i32 0, i32 0)) #8, !dbg !650
  unreachable, !dbg !650
                                                  ; No predecessors!
  br label %cond.end, !dbg !652

cond.end:                                         ; preds = %9, %cond.true
  br label %do.body5, !dbg !654

do.body5:                                         ; preds = %cond.end
  %10 = load %struct.uv_getaddrinfo_s*, %struct.uv_getaddrinfo_s** %req, align 8, !dbg !656
  %active_queue = getelementptr inbounds %struct.uv_getaddrinfo_s, %struct.uv_getaddrinfo_s* %10, i32 0, i32 2, !dbg !656
  %arrayidx6 = getelementptr inbounds [2 x i8*], [2 x i8*]* %active_queue, i64 0, i64 0, !dbg !656
  %11 = bitcast i8** %arrayidx6 to [2 x i8*]**, !dbg !656
  %12 = load [2 x i8*]*, [2 x i8*]** %11, align 8, !dbg !656
  %13 = load %struct.uv_getaddrinfo_s*, %struct.uv_getaddrinfo_s** %req, align 8, !dbg !656
  %active_queue7 = getelementptr inbounds %struct.uv_getaddrinfo_s, %struct.uv_getaddrinfo_s* %13, i32 0, i32 2, !dbg !656
  %arrayidx8 = getelementptr inbounds [2 x i8*], [2 x i8*]* %active_queue7, i64 0, i64 1, !dbg !656
  %14 = bitcast i8** %arrayidx8 to [2 x i8*]**, !dbg !656
  %15 = load [2 x i8*]*, [2 x i8*]** %14, align 8, !dbg !656
  %arrayidx9 = getelementptr inbounds [2 x i8*], [2 x i8*]* %15, i64 0, i64 0, !dbg !656
  %16 = bitcast i8** %arrayidx9 to [2 x i8*]**, !dbg !656
  store [2 x i8*]* %12, [2 x i8*]** %16, align 8, !dbg !656
  %17 = load %struct.uv_getaddrinfo_s*, %struct.uv_getaddrinfo_s** %req, align 8, !dbg !656
  %active_queue10 = getelementptr inbounds %struct.uv_getaddrinfo_s, %struct.uv_getaddrinfo_s* %17, i32 0, i32 2, !dbg !656
  %arrayidx11 = getelementptr inbounds [2 x i8*], [2 x i8*]* %active_queue10, i64 0, i64 1, !dbg !656
  %18 = bitcast i8** %arrayidx11 to [2 x i8*]**, !dbg !656
  %19 = load [2 x i8*]*, [2 x i8*]** %18, align 8, !dbg !656
  %20 = load %struct.uv_getaddrinfo_s*, %struct.uv_getaddrinfo_s** %req, align 8, !dbg !656
  %active_queue12 = getelementptr inbounds %struct.uv_getaddrinfo_s, %struct.uv_getaddrinfo_s* %20, i32 0, i32 2, !dbg !656
  %arrayidx13 = getelementptr inbounds [2 x i8*], [2 x i8*]* %active_queue12, i64 0, i64 0, !dbg !656
  %21 = bitcast i8** %arrayidx13 to [2 x i8*]**, !dbg !656
  %22 = load [2 x i8*]*, [2 x i8*]** %21, align 8, !dbg !656
  %arrayidx14 = getelementptr inbounds [2 x i8*], [2 x i8*]* %22, i64 0, i64 1, !dbg !656
  %23 = bitcast i8** %arrayidx14 to [2 x i8*]**, !dbg !656
  store [2 x i8*]* %19, [2 x i8*]** %23, align 8, !dbg !656
  br label %do.end, !dbg !656

do.end:                                           ; preds = %do.body5
  br label %do.end15, !dbg !659

do.end15:                                         ; preds = %do.end
  %24 = load %struct.uv_getaddrinfo_s*, %struct.uv_getaddrinfo_s** %req, align 8, !dbg !661
  %hints = getelementptr inbounds %struct.uv_getaddrinfo_s, %struct.uv_getaddrinfo_s* %24, i32 0, i32 7, !dbg !663
  %25 = load %struct.addrinfo*, %struct.addrinfo** %hints, align 8, !dbg !663
  %tobool = icmp ne %struct.addrinfo* %25, null, !dbg !661
  br i1 %tobool, label %if.then, label %if.else, !dbg !664

if.then:                                          ; preds = %do.end15
  %26 = load %struct.uv_getaddrinfo_s*, %struct.uv_getaddrinfo_s** %req, align 8, !dbg !665
  %hints16 = getelementptr inbounds %struct.uv_getaddrinfo_s, %struct.uv_getaddrinfo_s* %26, i32 0, i32 7, !dbg !666
  %27 = load %struct.addrinfo*, %struct.addrinfo** %hints16, align 8, !dbg !666
  %28 = bitcast %struct.addrinfo* %27 to i8*, !dbg !665
  call void @uv__free(i8* %28), !dbg !667
  br label %if.end26, !dbg !667

if.else:                                          ; preds = %do.end15
  %29 = load %struct.uv_getaddrinfo_s*, %struct.uv_getaddrinfo_s** %req, align 8, !dbg !668
  %service = getelementptr inbounds %struct.uv_getaddrinfo_s, %struct.uv_getaddrinfo_s* %29, i32 0, i32 9, !dbg !670
  %30 = load i8*, i8** %service, align 8, !dbg !670
  %tobool17 = icmp ne i8* %30, null, !dbg !668
  br i1 %tobool17, label %if.then18, label %if.else20, !dbg !671

if.then18:                                        ; preds = %if.else
  %31 = load %struct.uv_getaddrinfo_s*, %struct.uv_getaddrinfo_s** %req, align 8, !dbg !672
  %service19 = getelementptr inbounds %struct.uv_getaddrinfo_s, %struct.uv_getaddrinfo_s* %31, i32 0, i32 9, !dbg !673
  %32 = load i8*, i8** %service19, align 8, !dbg !673
  call void @uv__free(i8* %32), !dbg !674
  br label %if.end25, !dbg !674

if.else20:                                        ; preds = %if.else
  %33 = load %struct.uv_getaddrinfo_s*, %struct.uv_getaddrinfo_s** %req, align 8, !dbg !675
  %hostname = getelementptr inbounds %struct.uv_getaddrinfo_s, %struct.uv_getaddrinfo_s* %33, i32 0, i32 8, !dbg !677
  %34 = load i8*, i8** %hostname, align 8, !dbg !677
  %tobool21 = icmp ne i8* %34, null, !dbg !675
  br i1 %tobool21, label %if.then22, label %if.else24, !dbg !678

if.then22:                                        ; preds = %if.else20
  %35 = load %struct.uv_getaddrinfo_s*, %struct.uv_getaddrinfo_s** %req, align 8, !dbg !679
  %hostname23 = getelementptr inbounds %struct.uv_getaddrinfo_s, %struct.uv_getaddrinfo_s* %35, i32 0, i32 8, !dbg !680
  %36 = load i8*, i8** %hostname23, align 8, !dbg !680
  call void @uv__free(i8* %36), !dbg !681
  br label %if.end, !dbg !681

if.else24:                                        ; preds = %if.else20
  call void @__assert_fail(i8* getelementptr inbounds ([2 x i8], [2 x i8]* @.str.3, i32 0, i32 0), i8* getelementptr inbounds ([75 x i8], [75 x i8]* @.str.1, i32 0, i32 0), i32 121, i8* getelementptr inbounds ([50 x i8], [50 x i8]* @__PRETTY_FUNCTION__.uv__getaddrinfo_done, i32 0, i32 0)) #8, !dbg !682
  unreachable, !dbg !682

if.end:                                           ; preds = %if.then22
  br label %if.end25

if.end25:                                         ; preds = %if.end, %if.then18
  br label %if.end26

if.end26:                                         ; preds = %if.end25, %if.then
  %37 = load %struct.uv_getaddrinfo_s*, %struct.uv_getaddrinfo_s** %req, align 8, !dbg !683
  %hints27 = getelementptr inbounds %struct.uv_getaddrinfo_s, %struct.uv_getaddrinfo_s* %37, i32 0, i32 7, !dbg !684
  store %struct.addrinfo* null, %struct.addrinfo** %hints27, align 8, !dbg !685
  %38 = load %struct.uv_getaddrinfo_s*, %struct.uv_getaddrinfo_s** %req, align 8, !dbg !686
  %service28 = getelementptr inbounds %struct.uv_getaddrinfo_s, %struct.uv_getaddrinfo_s* %38, i32 0, i32 9, !dbg !687
  store i8* null, i8** %service28, align 8, !dbg !688
  %39 = load %struct.uv_getaddrinfo_s*, %struct.uv_getaddrinfo_s** %req, align 8, !dbg !689
  %hostname29 = getelementptr inbounds %struct.uv_getaddrinfo_s, %struct.uv_getaddrinfo_s* %39, i32 0, i32 8, !dbg !690
  store i8* null, i8** %hostname29, align 8, !dbg !691
  %40 = load i32, i32* %status.addr, align 4, !dbg !692
  %cmp30 = icmp eq i32 %40, -125, !dbg !694
  br i1 %cmp30, label %if.then32, label %if.end39, !dbg !695

if.then32:                                        ; preds = %if.end26
  %41 = load %struct.uv_getaddrinfo_s*, %struct.uv_getaddrinfo_s** %req, align 8, !dbg !696
  %retcode = getelementptr inbounds %struct.uv_getaddrinfo_s, %struct.uv_getaddrinfo_s* %41, i32 0, i32 11, !dbg !696
  %42 = load i32, i32* %retcode, align 8, !dbg !696
  %cmp33 = icmp eq i32 %42, 0, !dbg !696
  br i1 %cmp33, label %cond.true35, label %cond.false36, !dbg !696

cond.true35:                                      ; preds = %if.then32
  br label %cond.end37, !dbg !698

cond.false36:                                     ; preds = %if.then32
  call void @__assert_fail(i8* getelementptr inbounds ([18 x i8], [18 x i8]* @.str.4, i32 0, i32 0), i8* getelementptr inbounds ([75 x i8], [75 x i8]* @.str.1, i32 0, i32 0), i32 128, i8* getelementptr inbounds ([50 x i8], [50 x i8]* @__PRETTY_FUNCTION__.uv__getaddrinfo_done, i32 0, i32 0)) #8, !dbg !700
  unreachable, !dbg !700
                                                  ; No predecessors!
  br label %cond.end37, !dbg !702

cond.end37:                                       ; preds = %43, %cond.true35
  %44 = load %struct.uv_getaddrinfo_s*, %struct.uv_getaddrinfo_s** %req, align 8, !dbg !704
  %retcode38 = getelementptr inbounds %struct.uv_getaddrinfo_s, %struct.uv_getaddrinfo_s* %44, i32 0, i32 11, !dbg !705
  store i32 -3003, i32* %retcode38, align 8, !dbg !706
  br label %if.end39, !dbg !707

if.end39:                                         ; preds = %cond.end37, %if.end26
  %45 = load %struct.uv_getaddrinfo_s*, %struct.uv_getaddrinfo_s** %req, align 8, !dbg !708
  %cb = getelementptr inbounds %struct.uv_getaddrinfo_s, %struct.uv_getaddrinfo_s* %45, i32 0, i32 6, !dbg !710
  %46 = load void (%struct.uv_getaddrinfo_s*, i32, %struct.addrinfo*)*, void (%struct.uv_getaddrinfo_s*, i32, %struct.addrinfo*)** %cb, align 8, !dbg !710
  %tobool40 = icmp ne void (%struct.uv_getaddrinfo_s*, i32, %struct.addrinfo*)* %46, null, !dbg !708
  br i1 %tobool40, label %if.then41, label %if.end44, !dbg !711

if.then41:                                        ; preds = %if.end39
  %47 = load %struct.uv_getaddrinfo_s*, %struct.uv_getaddrinfo_s** %req, align 8, !dbg !712
  %cb42 = getelementptr inbounds %struct.uv_getaddrinfo_s, %struct.uv_getaddrinfo_s* %47, i32 0, i32 6, !dbg !713
  %48 = load void (%struct.uv_getaddrinfo_s*, i32, %struct.addrinfo*)*, void (%struct.uv_getaddrinfo_s*, i32, %struct.addrinfo*)** %cb42, align 8, !dbg !713
  %49 = load %struct.uv_getaddrinfo_s*, %struct.uv_getaddrinfo_s** %req, align 8, !dbg !714
  %50 = load %struct.uv_getaddrinfo_s*, %struct.uv_getaddrinfo_s** %req, align 8, !dbg !715
  %retcode43 = getelementptr inbounds %struct.uv_getaddrinfo_s, %struct.uv_getaddrinfo_s* %50, i32 0, i32 11, !dbg !716
  %51 = load i32, i32* %retcode43, align 8, !dbg !716
  %52 = load %struct.uv_getaddrinfo_s*, %struct.uv_getaddrinfo_s** %req, align 8, !dbg !717
  %addrinfo = getelementptr inbounds %struct.uv_getaddrinfo_s, %struct.uv_getaddrinfo_s* %52, i32 0, i32 10, !dbg !718
  %53 = load %struct.addrinfo*, %struct.addrinfo** %addrinfo, align 8, !dbg !718
  call void %48(%struct.uv_getaddrinfo_s* %49, i32 %51, %struct.addrinfo* %53), !dbg !712
  br label %if.end44, !dbg !712

if.end44:                                         ; preds = %if.then41, %if.end39
  ret void, !dbg !719
}

; Function Attrs: nounwind uwtable
define void @uv_freeaddrinfo(%struct.addrinfo* %ai) #0 !dbg !405 {
entry:
  %ai.addr = alloca %struct.addrinfo*, align 8
  store %struct.addrinfo* %ai, %struct.addrinfo** %ai.addr, align 8
  call void @llvm.dbg.declare(metadata %struct.addrinfo** %ai.addr, metadata !720, metadata !414), !dbg !721
  %0 = load %struct.addrinfo*, %struct.addrinfo** %ai.addr, align 8, !dbg !722
  %tobool = icmp ne %struct.addrinfo* %0, null, !dbg !722
  br i1 %tobool, label %if.then, label %if.end, !dbg !724

if.then:                                          ; preds = %entry
  %1 = load %struct.addrinfo*, %struct.addrinfo** %ai.addr, align 8, !dbg !725
  call void @freeaddrinfo(%struct.addrinfo* %1) #10, !dbg !726
  br label %if.end, !dbg !726

if.end:                                           ; preds = %if.then, %entry
  ret void, !dbg !727
}

; Function Attrs: nounwind
declare void @freeaddrinfo(%struct.addrinfo*) #7

declare i32 @getaddrinfo(i8*, i8*, %struct.addrinfo*, %struct.addrinfo**) #5

declare void @uv__free(i8*) #5

attributes #0 = { nounwind uwtable "disable-tail-calls"="false" "less-precise-fpmad"="false" "no-frame-pointer-elim"="true" "no-frame-pointer-elim-non-leaf" "no-infs-fp-math"="false" "no-nans-fp-math"="false" "stack-protector-buffer-size"="8" "target-cpu"="x86-64" "target-features"="+fxsr,+mmx,+sse,+sse2" "unsafe-fp-math"="false" "use-soft-float"="false" }
attributes #1 = { nounwind readnone }
attributes #2 = { nounwind readnone "disable-tail-calls"="false" "less-precise-fpmad"="false" "no-frame-pointer-elim"="true" "no-frame-pointer-elim-non-leaf" "no-infs-fp-math"="false" "no-nans-fp-math"="false" "stack-protector-buffer-size"="8" "target-cpu"="x86-64" "target-features"="+fxsr,+mmx,+sse,+sse2" "unsafe-fp-math"="false" "use-soft-float"="false" }
attributes #3 = { noreturn nounwind "disable-tail-calls"="false" "less-precise-fpmad"="false" "no-frame-pointer-elim"="true" "no-frame-pointer-elim-non-leaf" "no-infs-fp-math"="false" "no-nans-fp-math"="false" "stack-protector-buffer-size"="8" "target-cpu"="x86-64" "target-features"="+fxsr,+mmx,+sse,+sse2" "unsafe-fp-math"="false" "use-soft-float"="false" }
attributes #4 = { nounwind readonly "disable-tail-calls"="false" "less-precise-fpmad"="false" "no-frame-pointer-elim"="true" "no-frame-pointer-elim-non-leaf" "no-infs-fp-math"="false" "no-nans-fp-math"="false" "stack-protector-buffer-size"="8" "target-cpu"="x86-64" "target-features"="+fxsr,+mmx,+sse,+sse2" "unsafe-fp-math"="false" "use-soft-float"="false" }
attributes #5 = { "disable-tail-calls"="false" "less-precise-fpmad"="false" "no-frame-pointer-elim"="true" "no-frame-pointer-elim-non-leaf" "no-infs-fp-math"="false" "no-nans-fp-math"="false" "stack-protector-buffer-size"="8" "target-cpu"="x86-64" "target-features"="+fxsr,+mmx,+sse,+sse2" "unsafe-fp-math"="false" "use-soft-float"="false" }
attributes #6 = { argmemonly nounwind }
attributes #7 = { nounwind "disable-tail-calls"="false" "less-precise-fpmad"="false" "no-frame-pointer-elim"="true" "no-frame-pointer-elim-non-leaf" "no-infs-fp-math"="false" "no-nans-fp-math"="false" "stack-protector-buffer-size"="8" "target-cpu"="x86-64" "target-features"="+fxsr,+mmx,+sse,+sse2" "unsafe-fp-math"="false" "use-soft-float"="false" }
attributes #8 = { noreturn nounwind }
attributes #9 = { nounwind readonly }
attributes #10 = { nounwind }

!llvm.dbg.cu = !{!0}
!llvm.module.flags = !{!410, !411}
!llvm.ident = !{!412}

!0 = distinct !DICompileUnit(language: DW_LANG_C99, file: !1, producer: "clang version 3.8.0 (tags/RELEASE_380/final)", isOptimized: false, runtimeVersion: 0, emissionKind: 1, enums: !2, retainedTypes: !117, subprograms: !393)
!1 = !DIFile(filename: "/data/download/cmake/cmake-master/Utilities/cmlibuv/src/unix/getaddrinfo.c", directory: "/data/download/cmake/cmake-master/Utilities/cmlibuv")
!2 = !{!3, !83, !104}
!3 = !DICompositeType(tag: DW_TAG_enumeration_type, file: !4, line: 177, size: 32, align: 32, elements: !5)
!4 = !DIFile(filename: "/data/download/cmake/cmake-master/Utilities/cmlibuv/include/uv.h", directory: "/data/download/cmake/cmake-master/Utilities/cmlibuv")
!5 = !{!6, !7, !8, !9, !10, !11, !12, !13, !14, !15, !16, !17, !18, !19, !20, !21, !22, !23, !24, !25, !26, !27, !28, !29, !30, !31, !32, !33, !34, !35, !36, !37, !38, !39, !40, !41, !42, !43, !44, !45, !46, !47, !48, !49, !50, !51, !52, !53, !54, !55, !56, !57, !58, !59, !60, !61, !62, !63, !64, !65, !66, !67, !68, !69, !70, !71, !72, !73, !74, !75, !76, !77, !78, !79, !80, !81, !82}
!6 = !DIEnumerator(name: "UV_E2BIG", value: -7)
!7 = !DIEnumerator(name: "UV_EACCES", value: -13)
!8 = !DIEnumerator(name: "UV_EADDRINUSE", value: -98)
!9 = !DIEnumerator(name: "UV_EADDRNOTAVAIL", value: -99)
!10 = !DIEnumerator(name: "UV_EAFNOSUPPORT", value: -97)
!11 = !DIEnumerator(name: "UV_EAGAIN", value: -11)
!12 = !DIEnumerator(name: "UV_EAI_ADDRFAMILY", value: -3000)
!13 = !DIEnumerator(name: "UV_EAI_AGAIN", value: -3001)
!14 = !DIEnumerator(name: "UV_EAI_BADFLAGS", value: -3002)
!15 = !DIEnumerator(name: "UV_EAI_BADHINTS", value: -3013)
!16 = !DIEnumerator(name: "UV_EAI_CANCELED", value: -3003)
!17 = !DIEnumerator(name: "UV_EAI_FAIL", value: -3004)
!18 = !DIEnumerator(name: "UV_EAI_FAMILY", value: -3005)
!19 = !DIEnumerator(name: "UV_EAI_MEMORY", value: -3006)
!20 = !DIEnumerator(name: "UV_EAI_NODATA", value: -3007)
!21 = !DIEnumerator(name: "UV_EAI_NONAME", value: -3008)
!22 = !DIEnumerator(name: "UV_EAI_OVERFLOW", value: -3009)
!23 = !DIEnumerator(name: "UV_EAI_PROTOCOL", value: -3014)
!24 = !DIEnumerator(name: "UV_EAI_SERVICE", value: -3010)
!25 = !DIEnumerator(name: "UV_EAI_SOCKTYPE", value: -3011)
!26 = !DIEnumerator(name: "UV_EALREADY", value: -114)
!27 = !DIEnumerator(name: "UV_EBADF", value: -9)
!28 = !DIEnumerator(name: "UV_EBUSY", value: -16)
!29 = !DIEnumerator(name: "UV_ECANCELED", value: -125)
!30 = !DIEnumerator(name: "UV_ECHARSET", value: -4080)
!31 = !DIEnumerator(name: "UV_ECONNABORTED", value: -103)
!32 = !DIEnumerator(name: "UV_ECONNREFUSED", value: -111)
!33 = !DIEnumerator(name: "UV_ECONNRESET", value: -104)
!34 = !DIEnumerator(name: "UV_EDESTADDRREQ", value: -89)
!35 = !DIEnumerator(name: "UV_EEXIST", value: -17)
!36 = !DIEnumerator(name: "UV_EFAULT", value: -14)
!37 = !DIEnumerator(name: "UV_EFBIG", value: -27)
!38 = !DIEnumerator(name: "UV_EHOSTUNREACH", value: -113)
!39 = !DIEnumerator(name: "UV_EINTR", value: -4)
!40 = !DIEnumerator(name: "UV_EINVAL", value: -22)
!41 = !DIEnumerator(name: "UV_EIO", value: -5)
!42 = !DIEnumerator(name: "UV_EISCONN", value: -106)
!43 = !DIEnumerator(name: "UV_EISDIR", value: -21)
!44 = !DIEnumerator(name: "UV_ELOOP", value: -40)
!45 = !DIEnumerator(name: "UV_EMFILE", value: -24)
!46 = !DIEnumerator(name: "UV_EMSGSIZE", value: -90)
!47 = !DIEnumerator(name: "UV_ENAMETOOLONG", value: -36)
!48 = !DIEnumerator(name: "UV_ENETDOWN", value: -100)
!49 = !DIEnumerator(name: "UV_ENETUNREACH", value: -101)
!50 = !DIEnumerator(name: "UV_ENFILE", value: -23)
!51 = !DIEnumerator(name: "UV_ENOBUFS", value: -105)
!52 = !DIEnumerator(name: "UV_ENODEV", value: -19)
!53 = !DIEnumerator(name: "UV_ENOENT", value: -2)
!54 = !DIEnumerator(name: "UV_ENOMEM", value: -12)
!55 = !DIEnumerator(name: "UV_ENONET", value: -64)
!56 = !DIEnumerator(name: "UV_ENOPROTOOPT", value: -92)
!57 = !DIEnumerator(name: "UV_ENOSPC", value: -28)
!58 = !DIEnumerator(name: "UV_ENOSYS", value: -38)
!59 = !DIEnumerator(name: "UV_ENOTCONN", value: -107)
!60 = !DIEnumerator(name: "UV_ENOTDIR", value: -20)
!61 = !DIEnumerator(name: "UV_ENOTEMPTY", value: -39)
!62 = !DIEnumerator(name: "UV_ENOTSOCK", value: -88)
!63 = !DIEnumerator(name: "UV_ENOTSUP", value: -95)
!64 = !DIEnumerator(name: "UV_EPERM", value: -1)
!65 = !DIEnumerator(name: "UV_EPIPE", value: -32)
!66 = !DIEnumerator(name: "UV_EPROTO", value: -71)
!67 = !DIEnumerator(name: "UV_EPROTONOSUPPORT", value: -93)
!68 = !DIEnumerator(name: "UV_EPROTOTYPE", value: -91)
!69 = !DIEnumerator(name: "UV_ERANGE", value: -34)
!70 = !DIEnumerator(name: "UV_EROFS", value: -30)
!71 = !DIEnumerator(name: "UV_ESHUTDOWN", value: -108)
!72 = !DIEnumerator(name: "UV_ESPIPE", value: -29)
!73 = !DIEnumerator(name: "UV_ESRCH", value: -3)
!74 = !DIEnumerator(name: "UV_ETIMEDOUT", value: -110)
!75 = !DIEnumerator(name: "UV_ETXTBSY", value: -26)
!76 = !DIEnumerator(name: "UV_EXDEV", value: -18)
!77 = !DIEnumerator(name: "UV_UNKNOWN", value: -4094)
!78 = !DIEnumerator(name: "UV_EOF", value: -4095)
!79 = !DIEnumerator(name: "UV_ENXIO", value: -6)
!80 = !DIEnumerator(name: "UV_EMLINK", value: -31)
!81 = !DIEnumerator(name: "UV_EHOSTDOWN", value: -112)
!82 = !DIEnumerator(name: "UV_ERRNO_MAX", value: -4096)
!83 = !DICompositeType(tag: DW_TAG_enumeration_type, file: !4, line: 184, size: 32, align: 32, elements: !84)
!84 = !{!85, !86, !87, !88, !89, !90, !91, !92, !93, !94, !95, !96, !97, !98, !99, !100, !101, !102, !103}
!85 = !DIEnumerator(name: "UV_UNKNOWN_HANDLE", value: 0)
!86 = !DIEnumerator(name: "UV_ASYNC", value: 1)
!87 = !DIEnumerator(name: "UV_CHECK", value: 2)
!88 = !DIEnumerator(name: "UV_FS_EVENT", value: 3)
!89 = !DIEnumerator(name: "UV_FS_POLL", value: 4)
!90 = !DIEnumerator(name: "UV_HANDLE", value: 5)
!91 = !DIEnumerator(name: "UV_IDLE", value: 6)
!92 = !DIEnumerator(name: "UV_NAMED_PIPE", value: 7)
!93 = !DIEnumerator(name: "UV_POLL", value: 8)
!94 = !DIEnumerator(name: "UV_PREPARE", value: 9)
!95 = !DIEnumerator(name: "UV_PROCESS", value: 10)
!96 = !DIEnumerator(name: "UV_STREAM", value: 11)
!97 = !DIEnumerator(name: "UV_TCP", value: 12)
!98 = !DIEnumerator(name: "UV_TIMER", value: 13)
!99 = !DIEnumerator(name: "UV_TTY", value: 14)
!100 = !DIEnumerator(name: "UV_UDP", value: 15)
!101 = !DIEnumerator(name: "UV_SIGNAL", value: 16)
!102 = !DIEnumerator(name: "UV_FILE", value: 17)
!103 = !DIEnumerator(name: "UV_HANDLE_TYPE_MAX", value: 18)
!104 = !DICompositeType(tag: DW_TAG_enumeration_type, file: !4, line: 193, size: 32, align: 32, elements: !105)
!105 = !{!106, !107, !108, !109, !110, !111, !112, !113, !114, !115, !116}
!106 = !DIEnumerator(name: "UV_UNKNOWN_REQ", value: 0)
!107 = !DIEnumerator(name: "UV_REQ", value: 1)
!108 = !DIEnumerator(name: "UV_CONNECT", value: 2)
!109 = !DIEnumerator(name: "UV_WRITE", value: 3)
!110 = !DIEnumerator(name: "UV_SHUTDOWN", value: 4)
!111 = !DIEnumerator(name: "UV_UDP_SEND", value: 5)
!112 = !DIEnumerator(name: "UV_FS", value: 6)
!113 = !DIEnumerator(name: "UV_WORK", value: 7)
!114 = !DIEnumerator(name: "UV_GETADDRINFO", value: 8)
!115 = !DIEnumerator(name: "UV_GETNAMEINFO", value: 9)
!116 = !DIEnumerator(name: "UV_REQ_TYPE_MAX", value: 10)
!117 = !{!118, !119, !126, !384, !391}
!118 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: null, size: 64, align: 64)
!119 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !120, size: 64, align: 64)
!120 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !121, size: 64, align: 64)
!121 = !DIDerivedType(tag: DW_TAG_typedef, name: "QUEUE", file: !122, line: 21, baseType: !123)
!122 = !DIFile(filename: "/data/download/cmake/cmake-master/Utilities/cmlibuv/src/queue.h", directory: "/data/download/cmake/cmake-master/Utilities/cmlibuv")
!123 = !DICompositeType(tag: DW_TAG_array_type, baseType: !118, size: 128, align: 64, elements: !124)
!124 = !{!125}
!125 = !DISubrange(count: 2)
!126 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !127, size: 64, align: 64)
!127 = !DIDerivedType(tag: DW_TAG_typedef, name: "uv_getaddrinfo_t", file: !4, line: 224, baseType: !128)
!128 = !DICompositeType(tag: DW_TAG_structure_type, name: "uv_getaddrinfo_s", file: !4, line: 804, size: 1280, align: 64, elements: !129)
!129 = !{!130, !131, !133, !134, !138, !338, !353, !386, !387, !388, !389, !390}
!130 = !DIDerivedType(tag: DW_TAG_member, name: "data", scope: !128, file: !4, line: 805, baseType: !118, size: 64, align: 64)
!131 = !DIDerivedType(tag: DW_TAG_member, name: "type", scope: !128, file: !4, line: 805, baseType: !132, size: 32, align: 32, offset: 64)
!132 = !DIDerivedType(tag: DW_TAG_typedef, name: "uv_req_type", file: !4, line: 200, baseType: !104)
!133 = !DIDerivedType(tag: DW_TAG_member, name: "active_queue", scope: !128, file: !4, line: 805, baseType: !123, size: 128, align: 64, offset: 128)
!134 = !DIDerivedType(tag: DW_TAG_member, name: "reserved", scope: !128, file: !4, line: 805, baseType: !135, size: 256, align: 64, offset: 256)
!135 = !DICompositeType(tag: DW_TAG_array_type, baseType: !118, size: 256, align: 64, elements: !136)
!136 = !{!137}
!137 = !DISubrange(count: 4)
!138 = !DIDerivedType(tag: DW_TAG_member, name: "loop", scope: !128, file: !4, line: 807, baseType: !139, size: 64, align: 64, offset: 512)
!139 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !140, size: 64, align: 64)
!140 = !DIDerivedType(tag: DW_TAG_typedef, name: "uv_loop_t", file: !4, line: 204, baseType: !141)
!141 = !DICompositeType(tag: DW_TAG_structure_type, name: "uv_loop_s", file: !4, line: 1473, size: 6784, align: 64, elements: !142)
!142 = !{!143, !144, !146, !147, !148, !149, !151, !153, !154, !155, !174, !175, !176, !177, !208, !253, !277, !278, !279, !280, !281, !282, !283, !287, !288, !289, !294, !297, !298, !300, !301, !334, !335, !336, !337}
!143 = !DIDerivedType(tag: DW_TAG_member, name: "data", scope: !141, file: !4, line: 1475, baseType: !118, size: 64, align: 64)
!144 = !DIDerivedType(tag: DW_TAG_member, name: "active_handles", scope: !141, file: !4, line: 1477, baseType: !145, size: 32, align: 32, offset: 64)
!145 = !DIBasicType(name: "unsigned int", size: 32, align: 32, encoding: DW_ATE_unsigned)
!146 = !DIDerivedType(tag: DW_TAG_member, name: "handle_queue", scope: !141, file: !4, line: 1478, baseType: !123, size: 128, align: 64, offset: 128)
!147 = !DIDerivedType(tag: DW_TAG_member, name: "active_reqs", scope: !141, file: !4, line: 1479, baseType: !123, size: 128, align: 64, offset: 256)
!148 = !DIDerivedType(tag: DW_TAG_member, name: "stop_flag", scope: !141, file: !4, line: 1481, baseType: !145, size: 32, align: 32, offset: 384)
!149 = !DIDerivedType(tag: DW_TAG_member, name: "flags", scope: !141, file: !4, line: 1482, baseType: !150, size: 64, align: 64, offset: 448)
!150 = !DIBasicType(name: "long unsigned int", size: 64, align: 64, encoding: DW_ATE_unsigned)
!151 = !DIDerivedType(tag: DW_TAG_member, name: "backend_fd", scope: !141, file: !4, line: 1482, baseType: !152, size: 32, align: 32, offset: 512)
!152 = !DIBasicType(name: "int", size: 32, align: 32, encoding: DW_ATE_signed)
!153 = !DIDerivedType(tag: DW_TAG_member, name: "pending_queue", scope: !141, file: !4, line: 1482, baseType: !123, size: 128, align: 64, offset: 576)
!154 = !DIDerivedType(tag: DW_TAG_member, name: "watcher_queue", scope: !141, file: !4, line: 1482, baseType: !123, size: 128, align: 64, offset: 704)
!155 = !DIDerivedType(tag: DW_TAG_member, name: "watchers", scope: !141, file: !4, line: 1482, baseType: !156, size: 64, align: 64, offset: 832)
!156 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !157, size: 64, align: 64)
!157 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !158, size: 64, align: 64)
!158 = !DIDerivedType(tag: DW_TAG_typedef, name: "uv__io_t", file: !159, line: 87, baseType: !160)
!159 = !DIFile(filename: "/data/download/cmake/cmake-master/Utilities/cmlibuv/include/uv-unix.h", directory: "/data/download/cmake/cmake-master/Utilities/cmlibuv")
!160 = !DICompositeType(tag: DW_TAG_structure_type, name: "uv__io_s", file: !159, line: 89, size: 448, align: 64, elements: !161)
!161 = !{!162, !169, !170, !171, !172, !173}
!162 = !DIDerivedType(tag: DW_TAG_member, name: "cb", scope: !160, file: !159, line: 90, baseType: !163, size: 64, align: 64)
!163 = !DIDerivedType(tag: DW_TAG_typedef, name: "uv__io_cb", file: !159, line: 84, baseType: !164)
!164 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !165, size: 64, align: 64)
!165 = !DISubroutineType(types: !166)
!166 = !{null, !167, !168, !145}
!167 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !141, size: 64, align: 64)
!168 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !160, size: 64, align: 64)
!169 = !DIDerivedType(tag: DW_TAG_member, name: "pending_queue", scope: !160, file: !159, line: 91, baseType: !123, size: 128, align: 64, offset: 64)
!170 = !DIDerivedType(tag: DW_TAG_member, name: "watcher_queue", scope: !160, file: !159, line: 92, baseType: !123, size: 128, align: 64, offset: 192)
!171 = !DIDerivedType(tag: DW_TAG_member, name: "pevents", scope: !160, file: !159, line: 93, baseType: !145, size: 32, align: 32, offset: 320)
!172 = !DIDerivedType(tag: DW_TAG_member, name: "events", scope: !160, file: !159, line: 94, baseType: !145, size: 32, align: 32, offset: 352)
!173 = !DIDerivedType(tag: DW_TAG_member, name: "fd", scope: !160, file: !159, line: 95, baseType: !152, size: 32, align: 32, offset: 384)
!174 = !DIDerivedType(tag: DW_TAG_member, name: "nwatchers", scope: !141, file: !4, line: 1482, baseType: !145, size: 32, align: 32, offset: 896)
!175 = !DIDerivedType(tag: DW_TAG_member, name: "nfds", scope: !141, file: !4, line: 1482, baseType: !145, size: 32, align: 32, offset: 928)
!176 = !DIDerivedType(tag: DW_TAG_member, name: "wq", scope: !141, file: !4, line: 1482, baseType: !123, size: 128, align: 64, offset: 960)
!177 = !DIDerivedType(tag: DW_TAG_member, name: "wq_mutex", scope: !141, file: !4, line: 1482, baseType: !178, size: 320, align: 64, offset: 1088)
!178 = !DIDerivedType(tag: DW_TAG_typedef, name: "uv_mutex_t", file: !159, line: 129, baseType: !179)
!179 = !DIDerivedType(tag: DW_TAG_typedef, name: "pthread_mutex_t", file: !180, line: 127, baseType: !181)
!180 = !DIFile(filename: "/usr/include/x86_64-linux-gnu/bits/pthreadtypes.h", directory: "/data/download/cmake/cmake-master/Utilities/cmlibuv")
!181 = !DICompositeType(tag: DW_TAG_union_type, file: !180, line: 90, size: 320, align: 64, elements: !182)
!182 = !{!183, !201, !206}
!183 = !DIDerivedType(tag: DW_TAG_member, name: "__data", scope: !181, file: !180, line: 124, baseType: !184, size: 320, align: 64)
!184 = !DICompositeType(tag: DW_TAG_structure_type, name: "__pthread_mutex_s", file: !180, line: 92, size: 320, align: 64, elements: !185)
!185 = !{!186, !187, !188, !189, !190, !191, !193, !194}
!186 = !DIDerivedType(tag: DW_TAG_member, name: "__lock", scope: !184, file: !180, line: 94, baseType: !152, size: 32, align: 32)
!187 = !DIDerivedType(tag: DW_TAG_member, name: "__count", scope: !184, file: !180, line: 95, baseType: !145, size: 32, align: 32, offset: 32)
!188 = !DIDerivedType(tag: DW_TAG_member, name: "__owner", scope: !184, file: !180, line: 96, baseType: !152, size: 32, align: 32, offset: 64)
!189 = !DIDerivedType(tag: DW_TAG_member, name: "__nusers", scope: !184, file: !180, line: 98, baseType: !145, size: 32, align: 32, offset: 96)
!190 = !DIDerivedType(tag: DW_TAG_member, name: "__kind", scope: !184, file: !180, line: 102, baseType: !152, size: 32, align: 32, offset: 128)
!191 = !DIDerivedType(tag: DW_TAG_member, name: "__spins", scope: !184, file: !180, line: 104, baseType: !192, size: 16, align: 16, offset: 160)
!192 = !DIBasicType(name: "short", size: 16, align: 16, encoding: DW_ATE_signed)
!193 = !DIDerivedType(tag: DW_TAG_member, name: "__elision", scope: !184, file: !180, line: 105, baseType: !192, size: 16, align: 16, offset: 176)
!194 = !DIDerivedType(tag: DW_TAG_member, name: "__list", scope: !184, file: !180, line: 106, baseType: !195, size: 128, align: 64, offset: 192)
!195 = !DIDerivedType(tag: DW_TAG_typedef, name: "__pthread_list_t", file: !180, line: 79, baseType: !196)
!196 = !DICompositeType(tag: DW_TAG_structure_type, name: "__pthread_internal_list", file: !180, line: 75, size: 128, align: 64, elements: !197)
!197 = !{!198, !200}
!198 = !DIDerivedType(tag: DW_TAG_member, name: "__prev", scope: !196, file: !180, line: 77, baseType: !199, size: 64, align: 64)
!199 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !196, size: 64, align: 64)
!200 = !DIDerivedType(tag: DW_TAG_member, name: "__next", scope: !196, file: !180, line: 78, baseType: !199, size: 64, align: 64, offset: 64)
!201 = !DIDerivedType(tag: DW_TAG_member, name: "__size", scope: !181, file: !180, line: 125, baseType: !202, size: 320, align: 8)
!202 = !DICompositeType(tag: DW_TAG_array_type, baseType: !203, size: 320, align: 8, elements: !204)
!203 = !DIBasicType(name: "char", size: 8, align: 8, encoding: DW_ATE_signed_char)
!204 = !{!205}
!205 = !DISubrange(count: 40)
!206 = !DIDerivedType(tag: DW_TAG_member, name: "__align", scope: !181, file: !180, line: 126, baseType: !207, size: 64, align: 64)
!207 = !DIBasicType(name: "long int", size: 64, align: 64, encoding: DW_ATE_signed)
!208 = !DIDerivedType(tag: DW_TAG_member, name: "wq_async", scope: !141, file: !4, line: 1482, baseType: !209, size: 1024, align: 64, offset: 1408)
!209 = !DIDerivedType(tag: DW_TAG_typedef, name: "uv_async_t", file: !4, line: 216, baseType: !210)
!210 = !DICompositeType(tag: DW_TAG_structure_type, name: "uv_async_s", file: !4, line: 767, size: 1024, align: 64, elements: !211)
!211 = !{!212, !213, !214, !216, !237, !238, !243, !244, !245, !251, !252}
!212 = !DIDerivedType(tag: DW_TAG_member, name: "data", scope: !210, file: !4, line: 768, baseType: !118, size: 64, align: 64)
!213 = !DIDerivedType(tag: DW_TAG_member, name: "loop", scope: !210, file: !4, line: 768, baseType: !139, size: 64, align: 64, offset: 64)
!214 = !DIDerivedType(tag: DW_TAG_member, name: "type", scope: !210, file: !4, line: 768, baseType: !215, size: 32, align: 32, offset: 128)
!215 = !DIDerivedType(tag: DW_TAG_typedef, name: "uv_handle_type", file: !4, line: 191, baseType: !83)
!216 = !DIDerivedType(tag: DW_TAG_member, name: "close_cb", scope: !210, file: !4, line: 768, baseType: !217, size: 64, align: 64, offset: 192)
!217 = !DIDerivedType(tag: DW_TAG_typedef, name: "uv_close_cb", file: !4, line: 306, baseType: !218)
!218 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !219, size: 64, align: 64)
!219 = !DISubroutineType(types: !220)
!220 = !{null, !221}
!221 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !222, size: 64, align: 64)
!222 = !DIDerivedType(tag: DW_TAG_typedef, name: "uv_handle_t", file: !4, line: 205, baseType: !223)
!223 = !DICompositeType(tag: DW_TAG_structure_type, name: "uv_handle_s", file: !4, line: 425, size: 768, align: 64, elements: !224)
!224 = !{!225, !226, !227, !228, !229, !230, !235, !236}
!225 = !DIDerivedType(tag: DW_TAG_member, name: "data", scope: !223, file: !4, line: 426, baseType: !118, size: 64, align: 64)
!226 = !DIDerivedType(tag: DW_TAG_member, name: "loop", scope: !223, file: !4, line: 426, baseType: !139, size: 64, align: 64, offset: 64)
!227 = !DIDerivedType(tag: DW_TAG_member, name: "type", scope: !223, file: !4, line: 426, baseType: !215, size: 32, align: 32, offset: 128)
!228 = !DIDerivedType(tag: DW_TAG_member, name: "close_cb", scope: !223, file: !4, line: 426, baseType: !217, size: 64, align: 64, offset: 192)
!229 = !DIDerivedType(tag: DW_TAG_member, name: "handle_queue", scope: !223, file: !4, line: 426, baseType: !123, size: 128, align: 64, offset: 256)
!230 = !DIDerivedType(tag: DW_TAG_member, name: "u", scope: !223, file: !4, line: 426, baseType: !231, size: 256, align: 64, offset: 384)
!231 = !DICompositeType(tag: DW_TAG_union_type, scope: !223, file: !4, line: 426, size: 256, align: 64, elements: !232)
!232 = !{!233, !234}
!233 = !DIDerivedType(tag: DW_TAG_member, name: "fd", scope: !231, file: !4, line: 426, baseType: !152, size: 32, align: 32)
!234 = !DIDerivedType(tag: DW_TAG_member, name: "reserved", scope: !231, file: !4, line: 426, baseType: !135, size: 256, align: 64)
!235 = !DIDerivedType(tag: DW_TAG_member, name: "next_closing", scope: !223, file: !4, line: 426, baseType: !221, size: 64, align: 64, offset: 640)
!236 = !DIDerivedType(tag: DW_TAG_member, name: "flags", scope: !223, file: !4, line: 426, baseType: !145, size: 32, align: 32, offset: 704)
!237 = !DIDerivedType(tag: DW_TAG_member, name: "handle_queue", scope: !210, file: !4, line: 768, baseType: !123, size: 128, align: 64, offset: 256)
!238 = !DIDerivedType(tag: DW_TAG_member, name: "u", scope: !210, file: !4, line: 768, baseType: !239, size: 256, align: 64, offset: 384)
!239 = !DICompositeType(tag: DW_TAG_union_type, scope: !210, file: !4, line: 768, size: 256, align: 64, elements: !240)
!240 = !{!241, !242}
!241 = !DIDerivedType(tag: DW_TAG_member, name: "fd", scope: !239, file: !4, line: 768, baseType: !152, size: 32, align: 32)
!242 = !DIDerivedType(tag: DW_TAG_member, name: "reserved", scope: !239, file: !4, line: 768, baseType: !135, size: 256, align: 64)
!243 = !DIDerivedType(tag: DW_TAG_member, name: "next_closing", scope: !210, file: !4, line: 768, baseType: !221, size: 64, align: 64, offset: 640)
!244 = !DIDerivedType(tag: DW_TAG_member, name: "flags", scope: !210, file: !4, line: 768, baseType: !145, size: 32, align: 32, offset: 704)
!245 = !DIDerivedType(tag: DW_TAG_member, name: "async_cb", scope: !210, file: !4, line: 769, baseType: !246, size: 64, align: 64, offset: 768)
!246 = !DIDerivedType(tag: DW_TAG_typedef, name: "uv_async_cb", file: !4, line: 309, baseType: !247)
!247 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !248, size: 64, align: 64)
!248 = !DISubroutineType(types: !249)
!249 = !{null, !250}
!250 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !209, size: 64, align: 64)
!251 = !DIDerivedType(tag: DW_TAG_member, name: "queue", scope: !210, file: !4, line: 769, baseType: !123, size: 128, align: 64, offset: 832)
!252 = !DIDerivedType(tag: DW_TAG_member, name: "pending", scope: !210, file: !4, line: 769, baseType: !152, size: 32, align: 32, offset: 960)
!253 = !DIDerivedType(tag: DW_TAG_member, name: "cloexec_lock", scope: !141, file: !4, line: 1482, baseType: !254, size: 448, align: 64, offset: 2432)
!254 = !DIDerivedType(tag: DW_TAG_typedef, name: "uv_rwlock_t", file: !159, line: 130, baseType: !255)
!255 = !DIDerivedType(tag: DW_TAG_typedef, name: "pthread_rwlock_t", file: !180, line: 213, baseType: !256)
!256 = !DICompositeType(tag: DW_TAG_union_type, file: !180, line: 173, size: 448, align: 64, elements: !257)
!257 = !{!258, !272, !276}
!258 = !DIDerivedType(tag: DW_TAG_member, name: "__data", scope: !256, file: !180, line: 192, baseType: !259, size: 448, align: 64)
!259 = !DICompositeType(tag: DW_TAG_structure_type, scope: !256, file: !180, line: 176, size: 448, align: 64, elements: !260)
!260 = !{!261, !262, !263, !264, !265, !266, !267, !268, !269, !270, !271}
!261 = !DIDerivedType(tag: DW_TAG_member, name: "__lock", scope: !259, file: !180, line: 178, baseType: !152, size: 32, align: 32)
!262 = !DIDerivedType(tag: DW_TAG_member, name: "__nr_readers", scope: !259, file: !180, line: 179, baseType: !145, size: 32, align: 32, offset: 32)
!263 = !DIDerivedType(tag: DW_TAG_member, name: "__readers_wakeup", scope: !259, file: !180, line: 180, baseType: !145, size: 32, align: 32, offset: 64)
!264 = !DIDerivedType(tag: DW_TAG_member, name: "__writer_wakeup", scope: !259, file: !180, line: 181, baseType: !145, size: 32, align: 32, offset: 96)
!265 = !DIDerivedType(tag: DW_TAG_member, name: "__nr_readers_queued", scope: !259, file: !180, line: 182, baseType: !145, size: 32, align: 32, offset: 128)
!266 = !DIDerivedType(tag: DW_TAG_member, name: "__nr_writers_queued", scope: !259, file: !180, line: 183, baseType: !145, size: 32, align: 32, offset: 160)
!267 = !DIDerivedType(tag: DW_TAG_member, name: "__writer", scope: !259, file: !180, line: 184, baseType: !152, size: 32, align: 32, offset: 192)
!268 = !DIDerivedType(tag: DW_TAG_member, name: "__shared", scope: !259, file: !180, line: 185, baseType: !152, size: 32, align: 32, offset: 224)
!269 = !DIDerivedType(tag: DW_TAG_member, name: "__pad1", scope: !259, file: !180, line: 186, baseType: !150, size: 64, align: 64, offset: 256)
!270 = !DIDerivedType(tag: DW_TAG_member, name: "__pad2", scope: !259, file: !180, line: 187, baseType: !150, size: 64, align: 64, offset: 320)
!271 = !DIDerivedType(tag: DW_TAG_member, name: "__flags", scope: !259, file: !180, line: 190, baseType: !145, size: 32, align: 32, offset: 384)
!272 = !DIDerivedType(tag: DW_TAG_member, name: "__size", scope: !256, file: !180, line: 211, baseType: !273, size: 448, align: 8)
!273 = !DICompositeType(tag: DW_TAG_array_type, baseType: !203, size: 448, align: 8, elements: !274)
!274 = !{!275}
!275 = !DISubrange(count: 56)
!276 = !DIDerivedType(tag: DW_TAG_member, name: "__align", scope: !256, file: !180, line: 212, baseType: !207, size: 64, align: 64)
!277 = !DIDerivedType(tag: DW_TAG_member, name: "closing_handles", scope: !141, file: !4, line: 1482, baseType: !221, size: 64, align: 64, offset: 2880)
!278 = !DIDerivedType(tag: DW_TAG_member, name: "process_handles", scope: !141, file: !4, line: 1482, baseType: !123, size: 128, align: 64, offset: 2944)
!279 = !DIDerivedType(tag: DW_TAG_member, name: "prepare_handles", scope: !141, file: !4, line: 1482, baseType: !123, size: 128, align: 64, offset: 3072)
!280 = !DIDerivedType(tag: DW_TAG_member, name: "check_handles", scope: !141, file: !4, line: 1482, baseType: !123, size: 128, align: 64, offset: 3200)
!281 = !DIDerivedType(tag: DW_TAG_member, name: "idle_handles", scope: !141, file: !4, line: 1482, baseType: !123, size: 128, align: 64, offset: 3328)
!282 = !DIDerivedType(tag: DW_TAG_member, name: "async_handles", scope: !141, file: !4, line: 1482, baseType: !123, size: 128, align: 64, offset: 3456)
!283 = !DIDerivedType(tag: DW_TAG_member, name: "async_unused", scope: !141, file: !4, line: 1482, baseType: !284, size: 64, align: 64, offset: 3584)
!284 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !285, size: 64, align: 64)
!285 = !DISubroutineType(types: !286)
!286 = !{null}
!287 = !DIDerivedType(tag: DW_TAG_member, name: "async_io_watcher", scope: !141, file: !4, line: 1482, baseType: !158, size: 448, align: 64, offset: 3648)
!288 = !DIDerivedType(tag: DW_TAG_member, name: "async_wfd", scope: !141, file: !4, line: 1482, baseType: !152, size: 32, align: 32, offset: 4096)
!289 = !DIDerivedType(tag: DW_TAG_member, name: "timer_heap", scope: !141, file: !4, line: 1482, baseType: !290, size: 128, align: 64, offset: 4160)
!290 = !DICompositeType(tag: DW_TAG_structure_type, scope: !141, file: !4, line: 1482, size: 128, align: 64, elements: !291)
!291 = !{!292, !293}
!292 = !DIDerivedType(tag: DW_TAG_member, name: "min", scope: !290, file: !4, line: 1482, baseType: !118, size: 64, align: 64)
!293 = !DIDerivedType(tag: DW_TAG_member, name: "nelts", scope: !290, file: !4, line: 1482, baseType: !145, size: 32, align: 32, offset: 64)
!294 = !DIDerivedType(tag: DW_TAG_member, name: "timer_counter", scope: !141, file: !4, line: 1482, baseType: !295, size: 64, align: 64, offset: 4288)
!295 = !DIDerivedType(tag: DW_TAG_typedef, name: "uint64_t", file: !296, line: 55, baseType: !150)
!296 = !DIFile(filename: "/usr/include/stdint.h", directory: "/data/download/cmake/cmake-master/Utilities/cmlibuv")
!297 = !DIDerivedType(tag: DW_TAG_member, name: "time", scope: !141, file: !4, line: 1482, baseType: !295, size: 64, align: 64, offset: 4352)
!298 = !DIDerivedType(tag: DW_TAG_member, name: "signal_pipefd", scope: !141, file: !4, line: 1482, baseType: !299, size: 64, align: 32, offset: 4416)
!299 = !DICompositeType(tag: DW_TAG_array_type, baseType: !152, size: 64, align: 32, elements: !124)
!300 = !DIDerivedType(tag: DW_TAG_member, name: "signal_io_watcher", scope: !141, file: !4, line: 1482, baseType: !158, size: 448, align: 64, offset: 4480)
!301 = !DIDerivedType(tag: DW_TAG_member, name: "child_watcher", scope: !141, file: !4, line: 1482, baseType: !302, size: 1216, align: 64, offset: 4928)
!302 = !DIDerivedType(tag: DW_TAG_typedef, name: "uv_signal_t", file: !4, line: 220, baseType: !303)
!303 = !DICompositeType(tag: DW_TAG_structure_type, name: "uv_signal_s", file: !4, line: 1325, size: 1216, align: 64, elements: !304)
!304 = !{!305, !306, !307, !308, !309, !310, !315, !316, !317, !323, !324, !332, !333}
!305 = !DIDerivedType(tag: DW_TAG_member, name: "data", scope: !303, file: !4, line: 1326, baseType: !118, size: 64, align: 64)
!306 = !DIDerivedType(tag: DW_TAG_member, name: "loop", scope: !303, file: !4, line: 1326, baseType: !139, size: 64, align: 64, offset: 64)
!307 = !DIDerivedType(tag: DW_TAG_member, name: "type", scope: !303, file: !4, line: 1326, baseType: !215, size: 32, align: 32, offset: 128)
!308 = !DIDerivedType(tag: DW_TAG_member, name: "close_cb", scope: !303, file: !4, line: 1326, baseType: !217, size: 64, align: 64, offset: 192)
!309 = !DIDerivedType(tag: DW_TAG_member, name: "handle_queue", scope: !303, file: !4, line: 1326, baseType: !123, size: 128, align: 64, offset: 256)
!310 = !DIDerivedType(tag: DW_TAG_member, name: "u", scope: !303, file: !4, line: 1326, baseType: !311, size: 256, align: 64, offset: 384)
!311 = !DICompositeType(tag: DW_TAG_union_type, scope: !303, file: !4, line: 1326, size: 256, align: 64, elements: !312)
!312 = !{!313, !314}
!313 = !DIDerivedType(tag: DW_TAG_member, name: "fd", scope: !311, file: !4, line: 1326, baseType: !152, size: 32, align: 32)
!314 = !DIDerivedType(tag: DW_TAG_member, name: "reserved", scope: !311, file: !4, line: 1326, baseType: !135, size: 256, align: 64)
!315 = !DIDerivedType(tag: DW_TAG_member, name: "next_closing", scope: !303, file: !4, line: 1326, baseType: !221, size: 64, align: 64, offset: 640)
!316 = !DIDerivedType(tag: DW_TAG_member, name: "flags", scope: !303, file: !4, line: 1326, baseType: !145, size: 32, align: 32, offset: 704)
!317 = !DIDerivedType(tag: DW_TAG_member, name: "signal_cb", scope: !303, file: !4, line: 1327, baseType: !318, size: 64, align: 64, offset: 768)
!318 = !DIDerivedType(tag: DW_TAG_typedef, name: "uv_signal_cb", file: !4, line: 362, baseType: !319)
!319 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !320, size: 64, align: 64)
!320 = !DISubroutineType(types: !321)
!321 = !{null, !322, !152}
!322 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !302, size: 64, align: 64)
!323 = !DIDerivedType(tag: DW_TAG_member, name: "signum", scope: !303, file: !4, line: 1328, baseType: !152, size: 32, align: 32, offset: 832)
!324 = !DIDerivedType(tag: DW_TAG_member, name: "tree_entry", scope: !303, file: !4, line: 1329, baseType: !325, size: 256, align: 64, offset: 896)
!325 = !DICompositeType(tag: DW_TAG_structure_type, scope: !303, file: !4, line: 1329, size: 256, align: 64, elements: !326)
!326 = !{!327, !329, !330, !331}
!327 = !DIDerivedType(tag: DW_TAG_member, name: "rbe_left", scope: !325, file: !4, line: 1329, baseType: !328, size: 64, align: 64)
!328 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !303, size: 64, align: 64)
!329 = !DIDerivedType(tag: DW_TAG_member, name: "rbe_right", scope: !325, file: !4, line: 1329, baseType: !328, size: 64, align: 64, offset: 64)
!330 = !DIDerivedType(tag: DW_TAG_member, name: "rbe_parent", scope: !325, file: !4, line: 1329, baseType: !328, size: 64, align: 64, offset: 128)
!331 = !DIDerivedType(tag: DW_TAG_member, name: "rbe_color", scope: !325, file: !4, line: 1329, baseType: !152, size: 32, align: 32, offset: 192)
!332 = !DIDerivedType(tag: DW_TAG_member, name: "caught_signals", scope: !303, file: !4, line: 1329, baseType: !145, size: 32, align: 32, offset: 1152)
!333 = !DIDerivedType(tag: DW_TAG_member, name: "dispatched_signals", scope: !303, file: !4, line: 1329, baseType: !145, size: 32, align: 32, offset: 1184)
!334 = !DIDerivedType(tag: DW_TAG_member, name: "emfile_fd", scope: !141, file: !4, line: 1482, baseType: !152, size: 32, align: 32, offset: 6144)
!335 = !DIDerivedType(tag: DW_TAG_member, name: "inotify_read_watcher", scope: !141, file: !4, line: 1482, baseType: !158, size: 448, align: 64, offset: 6208)
!336 = !DIDerivedType(tag: DW_TAG_member, name: "inotify_watchers", scope: !141, file: !4, line: 1482, baseType: !118, size: 64, align: 64, offset: 6656)
!337 = !DIDerivedType(tag: DW_TAG_member, name: "inotify_fd", scope: !141, file: !4, line: 1482, baseType: !152, size: 32, align: 32, offset: 6720)
!338 = !DIDerivedType(tag: DW_TAG_member, name: "work_req", scope: !128, file: !4, line: 809, baseType: !339, size: 320, align: 64, offset: 576)
!339 = !DICompositeType(tag: DW_TAG_structure_type, name: "uv__work", file: !340, line: 30, size: 320, align: 64, elements: !341)
!340 = !DIFile(filename: "/data/download/cmake/cmake-master/Utilities/cmlibuv/include/uv-threadpool.h", directory: "/data/download/cmake/cmake-master/Utilities/cmlibuv")
!341 = !{!342, !347, !351, !352}
!342 = !DIDerivedType(tag: DW_TAG_member, name: "work", scope: !339, file: !340, line: 31, baseType: !343, size: 64, align: 64)
!343 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !344, size: 64, align: 64)
!344 = !DISubroutineType(types: !345)
!345 = !{null, !346}
!346 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !339, size: 64, align: 64)
!347 = !DIDerivedType(tag: DW_TAG_member, name: "done", scope: !339, file: !340, line: 32, baseType: !348, size: 64, align: 64, offset: 64)
!348 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !349, size: 64, align: 64)
!349 = !DISubroutineType(types: !350)
!350 = !{null, !346, !152}
!351 = !DIDerivedType(tag: DW_TAG_member, name: "loop", scope: !339, file: !340, line: 33, baseType: !167, size: 64, align: 64, offset: 128)
!352 = !DIDerivedType(tag: DW_TAG_member, name: "wq", scope: !339, file: !340, line: 34, baseType: !123, size: 128, align: 64, offset: 192)
!353 = !DIDerivedType(tag: DW_TAG_member, name: "cb", scope: !128, file: !4, line: 809, baseType: !354, size: 64, align: 64, offset: 896)
!354 = !DIDerivedType(tag: DW_TAG_typedef, name: "uv_getaddrinfo_cb", file: !4, line: 318, baseType: !355)
!355 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !356, size: 64, align: 64)
!356 = !DISubroutineType(types: !357)
!357 = !{null, !126, !152, !358}
!358 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !359, size: 64, align: 64)
!359 = !DICompositeType(tag: DW_TAG_structure_type, name: "addrinfo", file: !360, line: 567, size: 384, align: 64, elements: !361)
!360 = !DIFile(filename: "/usr/include/netdb.h", directory: "/data/download/cmake/cmake-master/Utilities/cmlibuv")
!361 = !{!362, !363, !364, !365, !366, !371, !383, !385}
!362 = !DIDerivedType(tag: DW_TAG_member, name: "ai_flags", scope: !359, file: !360, line: 569, baseType: !152, size: 32, align: 32)
!363 = !DIDerivedType(tag: DW_TAG_member, name: "ai_family", scope: !359, file: !360, line: 570, baseType: !152, size: 32, align: 32, offset: 32)
!364 = !DIDerivedType(tag: DW_TAG_member, name: "ai_socktype", scope: !359, file: !360, line: 571, baseType: !152, size: 32, align: 32, offset: 64)
!365 = !DIDerivedType(tag: DW_TAG_member, name: "ai_protocol", scope: !359, file: !360, line: 572, baseType: !152, size: 32, align: 32, offset: 96)
!366 = !DIDerivedType(tag: DW_TAG_member, name: "ai_addrlen", scope: !359, file: !360, line: 573, baseType: !367, size: 32, align: 32, offset: 128)
!367 = !DIDerivedType(tag: DW_TAG_typedef, name: "socklen_t", file: !368, line: 33, baseType: !369)
!368 = !DIFile(filename: "/usr/include/x86_64-linux-gnu/bits/socket.h", directory: "/data/download/cmake/cmake-master/Utilities/cmlibuv")
!369 = !DIDerivedType(tag: DW_TAG_typedef, name: "__socklen_t", file: !370, line: 189, baseType: !145)
!370 = !DIFile(filename: "/usr/include/x86_64-linux-gnu/bits/types.h", directory: "/data/download/cmake/cmake-master/Utilities/cmlibuv")
!371 = !DIDerivedType(tag: DW_TAG_member, name: "ai_addr", scope: !359, file: !360, line: 574, baseType: !372, size: 64, align: 64, offset: 192)
!372 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !373, size: 64, align: 64)
!373 = !DICompositeType(tag: DW_TAG_structure_type, name: "sockaddr", file: !368, line: 149, size: 128, align: 16, elements: !374)
!374 = !{!375, !379}
!375 = !DIDerivedType(tag: DW_TAG_member, name: "sa_family", scope: !373, file: !368, line: 151, baseType: !376, size: 16, align: 16)
!376 = !DIDerivedType(tag: DW_TAG_typedef, name: "sa_family_t", file: !377, line: 28, baseType: !378)
!377 = !DIFile(filename: "/usr/include/x86_64-linux-gnu/bits/sockaddr.h", directory: "/data/download/cmake/cmake-master/Utilities/cmlibuv")
!378 = !DIBasicType(name: "unsigned short", size: 16, align: 16, encoding: DW_ATE_unsigned)
!379 = !DIDerivedType(tag: DW_TAG_member, name: "sa_data", scope: !373, file: !368, line: 152, baseType: !380, size: 112, align: 8, offset: 16)
!380 = !DICompositeType(tag: DW_TAG_array_type, baseType: !203, size: 112, align: 8, elements: !381)
!381 = !{!382}
!382 = !DISubrange(count: 14)
!383 = !DIDerivedType(tag: DW_TAG_member, name: "ai_canonname", scope: !359, file: !360, line: 575, baseType: !384, size: 64, align: 64, offset: 256)
!384 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !203, size: 64, align: 64)
!385 = !DIDerivedType(tag: DW_TAG_member, name: "ai_next", scope: !359, file: !360, line: 576, baseType: !358, size: 64, align: 64, offset: 320)
!386 = !DIDerivedType(tag: DW_TAG_member, name: "hints", scope: !128, file: !4, line: 809, baseType: !358, size: 64, align: 64, offset: 960)
!387 = !DIDerivedType(tag: DW_TAG_member, name: "hostname", scope: !128, file: !4, line: 809, baseType: !384, size: 64, align: 64, offset: 1024)
!388 = !DIDerivedType(tag: DW_TAG_member, name: "service", scope: !128, file: !4, line: 809, baseType: !384, size: 64, align: 64, offset: 1088)
!389 = !DIDerivedType(tag: DW_TAG_member, name: "addrinfo", scope: !128, file: !4, line: 809, baseType: !358, size: 64, align: 64, offset: 1152)
!390 = !DIDerivedType(tag: DW_TAG_member, name: "retcode", scope: !128, file: !4, line: 809, baseType: !152, size: 32, align: 32, offset: 1216)
!391 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !392, size: 64, align: 64)
!392 = !DIDerivedType(tag: DW_TAG_const_type, baseType: !121)
!393 = !{!394, !398, !405, !408, !409}
!394 = distinct !DISubprogram(name: "uv__getaddrinfo_translate_error", scope: !1, file: !1, line: 40, type: !395, isLocal: false, isDefinition: true, scopeLine: 40, flags: DIFlagPrototyped, isOptimized: false, variables: !397)
!395 = !DISubroutineType(types: !396)
!396 = !{!152, !152}
!397 = !{}
!398 = distinct !DISubprogram(name: "uv_getaddrinfo", scope: !1, file: !1, line: 137, type: !399, isLocal: false, isDefinition: true, scopeLine: 142, flags: DIFlagPrototyped, isOptimized: false, variables: !397)
!399 = !DISubroutineType(types: !400)
!400 = !{!152, !139, !126, !354, !401, !401, !403}
!401 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !402, size: 64, align: 64)
!402 = !DIDerivedType(tag: DW_TAG_const_type, baseType: !203)
!403 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !404, size: 64, align: 64)
!404 = !DIDerivedType(tag: DW_TAG_const_type, baseType: !359)
!405 = distinct !DISubprogram(name: "uv_freeaddrinfo", scope: !1, file: !1, line: 199, type: !406, isLocal: false, isDefinition: true, scopeLine: 199, flags: DIFlagPrototyped, isOptimized: false, variables: !397)
!406 = !DISubroutineType(types: !407)
!407 = !{null, !358}
!408 = distinct !DISubprogram(name: "uv__getaddrinfo_work", scope: !1, file: !1, line: 97, type: !344, isLocal: true, isDefinition: true, scopeLine: 97, flags: DIFlagPrototyped, isOptimized: false, variables: !397)
!409 = distinct !DISubprogram(name: "uv__getaddrinfo_done", scope: !1, file: !1, line: 107, type: !349, isLocal: true, isDefinition: true, scopeLine: 107, flags: DIFlagPrototyped, isOptimized: false, variables: !397)
!410 = !{i32 2, !"Dwarf Version", i32 4}
!411 = !{i32 2, !"Debug Info Version", i32 3}
!412 = !{!"clang version 3.8.0 (tags/RELEASE_380/final)"}
!413 = !DILocalVariable(name: "sys_err", arg: 1, scope: !394, file: !1, line: 40, type: !152)
!414 = !DIExpression()
!415 = !DILocation(line: 40, column: 41, scope: !394)
!416 = !DILocation(line: 41, column: 11, scope: !394)
!417 = !DILocation(line: 41, column: 3, scope: !394)
!418 = !DILocation(line: 42, column: 11, scope: !419)
!419 = distinct !DILexicalBlock(scope: !394, file: !1, line: 41, column: 20)
!420 = !DILocation(line: 44, column: 24, scope: !419)
!421 = !DILocation(line: 47, column: 19, scope: !419)
!422 = !DILocation(line: 50, column: 22, scope: !419)
!423 = !DILocation(line: 56, column: 22, scope: !419)
!424 = !DILocation(line: 59, column: 18, scope: !419)
!425 = !DILocation(line: 62, column: 20, scope: !419)
!426 = !DILocation(line: 65, column: 20, scope: !419)
!427 = !DILocation(line: 68, column: 20, scope: !419)
!428 = !DILocation(line: 72, column: 20, scope: !419)
!429 = !DILocation(line: 76, column: 22, scope: !419)
!430 = !DILocation(line: 82, column: 21, scope: !419)
!431 = !DILocation(line: 85, column: 22, scope: !419)
!432 = !DILocation(line: 88, column: 28, scope: !419)
!433 = !DILocation(line: 88, column: 27, scope: !419)
!434 = !DILocation(line: 88, column: 20, scope: !419)
!435 = !DILocation(line: 91, column: 3, scope: !394)
!436 = !DILocation(line: 94, column: 1, scope: !394)
!437 = !DILocalVariable(name: "loop", arg: 1, scope: !398, file: !1, line: 137, type: !139)
!438 = !DILocation(line: 137, column: 31, scope: !398)
!439 = !DILocalVariable(name: "req", arg: 2, scope: !398, file: !1, line: 138, type: !126)
!440 = !DILocation(line: 138, column: 38, scope: !398)
!441 = !DILocalVariable(name: "cb", arg: 3, scope: !398, file: !1, line: 139, type: !354)
!442 = !DILocation(line: 139, column: 38, scope: !398)
!443 = !DILocalVariable(name: "hostname", arg: 4, scope: !398, file: !1, line: 140, type: !401)
!444 = !DILocation(line: 140, column: 32, scope: !398)
!445 = !DILocalVariable(name: "service", arg: 5, scope: !398, file: !1, line: 141, type: !401)
!446 = !DILocation(line: 141, column: 32, scope: !398)
!447 = !DILocalVariable(name: "hints", arg: 6, scope: !398, file: !1, line: 142, type: !403)
!448 = !DILocation(line: 142, column: 43, scope: !398)
!449 = !DILocalVariable(name: "hostname_len", scope: !398, file: !1, line: 143, type: !450)
!450 = !DIDerivedType(tag: DW_TAG_typedef, name: "size_t", file: !451, line: 62, baseType: !150)
!451 = !DIFile(filename: "/opt/llvm-build/bin/../lib/clang/3.8.0/include/stddef.h", directory: "/data/download/cmake/cmake-master/Utilities/cmlibuv")
!452 = !DILocation(line: 143, column: 10, scope: !398)
!453 = !DILocalVariable(name: "service_len", scope: !398, file: !1, line: 144, type: !450)
!454 = !DILocation(line: 144, column: 10, scope: !398)
!455 = !DILocalVariable(name: "hints_len", scope: !398, file: !1, line: 145, type: !450)
!456 = !DILocation(line: 145, column: 10, scope: !398)
!457 = !DILocalVariable(name: "len", scope: !398, file: !1, line: 146, type: !450)
!458 = !DILocation(line: 146, column: 10, scope: !398)
!459 = !DILocalVariable(name: "buf", scope: !398, file: !1, line: 147, type: !384)
!460 = !DILocation(line: 147, column: 9, scope: !398)
!461 = !DILocation(line: 149, column: 7, scope: !462)
!462 = distinct !DILexicalBlock(scope: !398, file: !1, line: 149, column: 7)
!463 = !DILocation(line: 149, column: 11, scope: !462)
!464 = !DILocation(line: 149, column: 19, scope: !462)
!465 = !DILocation(line: 149, column: 23, scope: !466)
!466 = !DILexicalBlockFile(scope: !462, file: !1, discriminator: 1)
!467 = !DILocation(line: 149, column: 32, scope: !466)
!468 = !DILocation(line: 149, column: 40, scope: !466)
!469 = !DILocation(line: 149, column: 43, scope: !470)
!470 = !DILexicalBlockFile(scope: !462, file: !1, discriminator: 2)
!471 = !DILocation(line: 149, column: 51, scope: !470)
!472 = !DILocation(line: 149, column: 7, scope: !470)
!473 = !DILocation(line: 150, column: 5, scope: !462)
!474 = !DILocation(line: 152, column: 18, scope: !398)
!475 = !DILocation(line: 152, column: 36, scope: !476)
!476 = !DILexicalBlockFile(scope: !398, file: !1, discriminator: 1)
!477 = !DILocation(line: 152, column: 29, scope: !476)
!478 = !DILocation(line: 152, column: 46, scope: !476)
!479 = !DILocation(line: 152, column: 18, scope: !476)
!480 = !DILocation(line: 152, column: 18, scope: !481)
!481 = !DILexicalBlockFile(scope: !398, file: !1, discriminator: 2)
!482 = !DILocation(line: 152, column: 18, scope: !483)
!483 = !DILexicalBlockFile(scope: !398, file: !1, discriminator: 3)
!484 = !DILocation(line: 152, column: 16, scope: !483)
!485 = !DILocation(line: 153, column: 17, scope: !398)
!486 = !DILocation(line: 153, column: 34, scope: !476)
!487 = !DILocation(line: 153, column: 27, scope: !476)
!488 = !DILocation(line: 153, column: 43, scope: !476)
!489 = !DILocation(line: 153, column: 17, scope: !476)
!490 = !DILocation(line: 153, column: 17, scope: !481)
!491 = !DILocation(line: 153, column: 17, scope: !483)
!492 = !DILocation(line: 153, column: 15, scope: !483)
!493 = !DILocation(line: 154, column: 15, scope: !398)
!494 = !DILocation(line: 154, column: 13, scope: !398)
!495 = !DILocation(line: 155, column: 20, scope: !398)
!496 = !DILocation(line: 155, column: 35, scope: !398)
!497 = !DILocation(line: 155, column: 33, scope: !398)
!498 = !DILocation(line: 155, column: 49, scope: !398)
!499 = !DILocation(line: 155, column: 47, scope: !398)
!500 = !DILocation(line: 155, column: 9, scope: !398)
!501 = !DILocation(line: 155, column: 7, scope: !398)
!502 = !DILocation(line: 157, column: 7, scope: !503)
!503 = distinct !DILexicalBlock(scope: !398, file: !1, line: 157, column: 7)
!504 = !DILocation(line: 157, column: 11, scope: !503)
!505 = !DILocation(line: 157, column: 7, scope: !398)
!506 = !DILocation(line: 158, column: 5, scope: !503)
!507 = !DILocation(line: 160, column: 3, scope: !398)
!508 = !DILocation(line: 160, column: 3, scope: !509)
!509 = !DILexicalBlockFile(scope: !510, file: !1, discriminator: 1)
!510 = distinct !DILexicalBlock(scope: !398, file: !1, line: 160, column: 3)
!511 = !DILocation(line: 160, column: 3, scope: !512)
!512 = !DILexicalBlockFile(scope: !513, file: !1, discriminator: 2)
!513 = distinct !DILexicalBlock(scope: !510, file: !1, line: 160, column: 3)
!514 = !DILocation(line: 160, column: 3, scope: !515)
!515 = !DILexicalBlockFile(scope: !510, file: !1, discriminator: 3)
!516 = !DILocation(line: 160, column: 3, scope: !517)
!517 = !DILexicalBlockFile(scope: !518, file: !1, discriminator: 4)
!518 = distinct !DILexicalBlock(scope: !510, file: !1, line: 160, column: 3)
!519 = !DILocation(line: 160, column: 3, scope: !520)
!520 = !DILexicalBlockFile(scope: !521, file: !1, discriminator: 5)
!521 = distinct !DILexicalBlock(scope: !518, file: !1, line: 160, column: 3)
!522 = !DILocation(line: 160, column: 3, scope: !523)
!523 = !DILexicalBlockFile(scope: !518, file: !1, discriminator: 6)
!524 = !DILocation(line: 160, column: 3, scope: !525)
!525 = !DILexicalBlockFile(scope: !510, file: !1, discriminator: 7)
!526 = !DILocation(line: 161, column: 15, scope: !398)
!527 = !DILocation(line: 161, column: 3, scope: !398)
!528 = !DILocation(line: 161, column: 8, scope: !398)
!529 = !DILocation(line: 161, column: 13, scope: !398)
!530 = !DILocation(line: 162, column: 13, scope: !398)
!531 = !DILocation(line: 162, column: 3, scope: !398)
!532 = !DILocation(line: 162, column: 8, scope: !398)
!533 = !DILocation(line: 162, column: 11, scope: !398)
!534 = !DILocation(line: 163, column: 3, scope: !398)
!535 = !DILocation(line: 163, column: 8, scope: !398)
!536 = !DILocation(line: 163, column: 17, scope: !398)
!537 = !DILocation(line: 164, column: 3, scope: !398)
!538 = !DILocation(line: 164, column: 8, scope: !398)
!539 = !DILocation(line: 164, column: 14, scope: !398)
!540 = !DILocation(line: 165, column: 3, scope: !398)
!541 = !DILocation(line: 165, column: 8, scope: !398)
!542 = !DILocation(line: 165, column: 16, scope: !398)
!543 = !DILocation(line: 166, column: 3, scope: !398)
!544 = !DILocation(line: 166, column: 8, scope: !398)
!545 = !DILocation(line: 166, column: 17, scope: !398)
!546 = !DILocation(line: 167, column: 3, scope: !398)
!547 = !DILocation(line: 167, column: 8, scope: !398)
!548 = !DILocation(line: 167, column: 16, scope: !398)
!549 = !DILocation(line: 170, column: 7, scope: !398)
!550 = !DILocation(line: 172, column: 7, scope: !551)
!551 = distinct !DILexicalBlock(scope: !398, file: !1, line: 172, column: 7)
!552 = !DILocation(line: 172, column: 7, scope: !398)
!553 = !DILocation(line: 173, column: 25, scope: !554)
!554 = distinct !DILexicalBlock(scope: !551, file: !1, line: 172, column: 14)
!555 = !DILocation(line: 173, column: 31, scope: !554)
!556 = !DILocation(line: 173, column: 29, scope: !554)
!557 = !DILocation(line: 173, column: 36, scope: !554)
!558 = !DILocation(line: 173, column: 18, scope: !554)
!559 = !DILocation(line: 173, column: 5, scope: !554)
!560 = !DILocation(line: 173, column: 10, scope: !554)
!561 = !DILocation(line: 173, column: 16, scope: !554)
!562 = !DILocation(line: 174, column: 9, scope: !554)
!563 = !DILocation(line: 175, column: 3, scope: !554)
!564 = !DILocation(line: 177, column: 7, scope: !565)
!565 = distinct !DILexicalBlock(scope: !398, file: !1, line: 177, column: 7)
!566 = !DILocation(line: 177, column: 7, scope: !398)
!567 = !DILocation(line: 178, column: 27, scope: !568)
!568 = distinct !DILexicalBlock(scope: !565, file: !1, line: 177, column: 16)
!569 = !DILocation(line: 178, column: 33, scope: !568)
!570 = !DILocation(line: 178, column: 31, scope: !568)
!571 = !DILocation(line: 178, column: 38, scope: !568)
!572 = !DILocation(line: 178, column: 47, scope: !568)
!573 = !DILocation(line: 178, column: 20, scope: !568)
!574 = !DILocation(line: 178, column: 5, scope: !568)
!575 = !DILocation(line: 178, column: 10, scope: !568)
!576 = !DILocation(line: 178, column: 18, scope: !568)
!577 = !DILocation(line: 179, column: 12, scope: !568)
!578 = !DILocation(line: 179, column: 9, scope: !568)
!579 = !DILocation(line: 180, column: 3, scope: !568)
!580 = !DILocation(line: 182, column: 7, scope: !581)
!581 = distinct !DILexicalBlock(scope: !398, file: !1, line: 182, column: 7)
!582 = !DILocation(line: 182, column: 7, scope: !398)
!583 = !DILocation(line: 183, column: 28, scope: !581)
!584 = !DILocation(line: 183, column: 34, scope: !581)
!585 = !DILocation(line: 183, column: 32, scope: !581)
!586 = !DILocation(line: 183, column: 39, scope: !581)
!587 = !DILocation(line: 183, column: 49, scope: !581)
!588 = !DILocation(line: 183, column: 21, scope: !581)
!589 = !DILocation(line: 183, column: 5, scope: !581)
!590 = !DILocation(line: 183, column: 10, scope: !581)
!591 = !DILocation(line: 183, column: 19, scope: !581)
!592 = !DILocation(line: 185, column: 7, scope: !593)
!593 = distinct !DILexicalBlock(scope: !398, file: !1, line: 185, column: 7)
!594 = !DILocation(line: 185, column: 7, scope: !398)
!595 = !DILocation(line: 186, column: 21, scope: !596)
!596 = distinct !DILexicalBlock(scope: !593, file: !1, line: 185, column: 11)
!597 = !DILocation(line: 187, column: 22, scope: !596)
!598 = !DILocation(line: 187, column: 27, scope: !596)
!599 = !DILocation(line: 186, column: 5, scope: !596)
!600 = !DILocation(line: 190, column: 5, scope: !596)
!601 = !DILocation(line: 192, column: 27, scope: !602)
!602 = distinct !DILexicalBlock(scope: !593, file: !1, line: 191, column: 10)
!603 = !DILocation(line: 192, column: 32, scope: !602)
!604 = !DILocation(line: 192, column: 5, scope: !602)
!605 = !DILocation(line: 193, column: 27, scope: !602)
!606 = !DILocation(line: 193, column: 32, scope: !602)
!607 = !DILocation(line: 193, column: 5, scope: !602)
!608 = !DILocation(line: 194, column: 12, scope: !602)
!609 = !DILocation(line: 194, column: 17, scope: !602)
!610 = !DILocation(line: 194, column: 5, scope: !602)
!611 = !DILocation(line: 196, column: 1, scope: !398)
!612 = !DILocalVariable(name: "w", arg: 1, scope: !408, file: !1, line: 97, type: !346)
!613 = !DILocation(line: 97, column: 51, scope: !408)
!614 = !DILocalVariable(name: "req", scope: !408, file: !1, line: 98, type: !126)
!615 = !DILocation(line: 98, column: 21, scope: !408)
!616 = !DILocalVariable(name: "err", scope: !408, file: !1, line: 99, type: !152)
!617 = !DILocation(line: 99, column: 7, scope: !408)
!618 = !DILocation(line: 101, column: 9, scope: !408)
!619 = !DILocation(line: 101, column: 7, scope: !408)
!620 = !DILocation(line: 102, column: 21, scope: !408)
!621 = !DILocation(line: 102, column: 26, scope: !408)
!622 = !DILocation(line: 102, column: 36, scope: !408)
!623 = !DILocation(line: 102, column: 41, scope: !408)
!624 = !DILocation(line: 102, column: 50, scope: !408)
!625 = !DILocation(line: 102, column: 55, scope: !408)
!626 = !DILocation(line: 102, column: 63, scope: !408)
!627 = !DILocation(line: 102, column: 68, scope: !408)
!628 = !DILocation(line: 102, column: 9, scope: !408)
!629 = !DILocation(line: 102, column: 7, scope: !408)
!630 = !DILocation(line: 103, column: 50, scope: !408)
!631 = !DILocation(line: 103, column: 18, scope: !408)
!632 = !DILocation(line: 103, column: 3, scope: !408)
!633 = !DILocation(line: 103, column: 8, scope: !408)
!634 = !DILocation(line: 103, column: 16, scope: !408)
!635 = !DILocation(line: 104, column: 1, scope: !408)
!636 = !DILocalVariable(name: "w", arg: 1, scope: !409, file: !1, line: 107, type: !346)
!637 = !DILocation(line: 107, column: 51, scope: !409)
!638 = !DILocalVariable(name: "status", arg: 2, scope: !409, file: !1, line: 107, type: !152)
!639 = !DILocation(line: 107, column: 58, scope: !409)
!640 = !DILocalVariable(name: "req", scope: !409, file: !1, line: 108, type: !126)
!641 = !DILocation(line: 108, column: 21, scope: !409)
!642 = !DILocation(line: 110, column: 9, scope: !409)
!643 = !DILocation(line: 110, column: 7, scope: !409)
!644 = !DILocation(line: 111, column: 3, scope: !409)
!645 = !DILocation(line: 111, column: 3, scope: !646)
!646 = !DILexicalBlockFile(scope: !647, file: !1, discriminator: 1)
!647 = distinct !DILexicalBlock(scope: !409, file: !1, line: 111, column: 3)
!648 = !DILocation(line: 111, column: 3, scope: !649)
!649 = !DILexicalBlockFile(scope: !647, file: !1, discriminator: 2)
!650 = !DILocation(line: 111, column: 3, scope: !651)
!651 = !DILexicalBlockFile(scope: !647, file: !1, discriminator: 3)
!652 = !DILocation(line: 111, column: 3, scope: !653)
!653 = !DILexicalBlockFile(scope: !647, file: !1, discriminator: 4)
!654 = !DILocation(line: 111, column: 3, scope: !655)
!655 = !DILexicalBlockFile(scope: !647, file: !1, discriminator: 5)
!656 = !DILocation(line: 111, column: 3, scope: !657)
!657 = !DILexicalBlockFile(scope: !658, file: !1, discriminator: 6)
!658 = distinct !DILexicalBlock(scope: !647, file: !1, line: 111, column: 3)
!659 = !DILocation(line: 111, column: 3, scope: !660)
!660 = !DILexicalBlockFile(scope: !647, file: !1, discriminator: 7)
!661 = !DILocation(line: 114, column: 7, scope: !662)
!662 = distinct !DILexicalBlock(scope: !409, file: !1, line: 114, column: 7)
!663 = !DILocation(line: 114, column: 12, scope: !662)
!664 = !DILocation(line: 114, column: 7, scope: !409)
!665 = !DILocation(line: 115, column: 14, scope: !662)
!666 = !DILocation(line: 115, column: 19, scope: !662)
!667 = !DILocation(line: 115, column: 5, scope: !662)
!668 = !DILocation(line: 116, column: 12, scope: !669)
!669 = distinct !DILexicalBlock(scope: !662, file: !1, line: 116, column: 12)
!670 = !DILocation(line: 116, column: 17, scope: !669)
!671 = !DILocation(line: 116, column: 12, scope: !662)
!672 = !DILocation(line: 117, column: 14, scope: !669)
!673 = !DILocation(line: 117, column: 19, scope: !669)
!674 = !DILocation(line: 117, column: 5, scope: !669)
!675 = !DILocation(line: 118, column: 12, scope: !676)
!676 = distinct !DILexicalBlock(scope: !669, file: !1, line: 118, column: 12)
!677 = !DILocation(line: 118, column: 17, scope: !676)
!678 = !DILocation(line: 118, column: 12, scope: !669)
!679 = !DILocation(line: 119, column: 14, scope: !676)
!680 = !DILocation(line: 119, column: 19, scope: !676)
!681 = !DILocation(line: 119, column: 5, scope: !676)
!682 = !DILocation(line: 121, column: 5, scope: !676)
!683 = !DILocation(line: 123, column: 3, scope: !409)
!684 = !DILocation(line: 123, column: 8, scope: !409)
!685 = !DILocation(line: 123, column: 14, scope: !409)
!686 = !DILocation(line: 124, column: 3, scope: !409)
!687 = !DILocation(line: 124, column: 8, scope: !409)
!688 = !DILocation(line: 124, column: 16, scope: !409)
!689 = !DILocation(line: 125, column: 3, scope: !409)
!690 = !DILocation(line: 125, column: 8, scope: !409)
!691 = !DILocation(line: 125, column: 17, scope: !409)
!692 = !DILocation(line: 127, column: 7, scope: !693)
!693 = distinct !DILexicalBlock(scope: !409, file: !1, line: 127, column: 7)
!694 = !DILocation(line: 127, column: 14, scope: !693)
!695 = !DILocation(line: 127, column: 7, scope: !409)
!696 = !DILocation(line: 128, column: 5, scope: !697)
!697 = distinct !DILexicalBlock(scope: !693, file: !1, line: 127, column: 29)
!698 = !DILocation(line: 128, column: 5, scope: !699)
!699 = !DILexicalBlockFile(scope: !697, file: !1, discriminator: 1)
!700 = !DILocation(line: 128, column: 5, scope: !701)
!701 = !DILexicalBlockFile(scope: !697, file: !1, discriminator: 2)
!702 = !DILocation(line: 128, column: 5, scope: !703)
!703 = !DILexicalBlockFile(scope: !697, file: !1, discriminator: 3)
!704 = !DILocation(line: 129, column: 5, scope: !697)
!705 = !DILocation(line: 129, column: 10, scope: !697)
!706 = !DILocation(line: 129, column: 18, scope: !697)
!707 = !DILocation(line: 130, column: 3, scope: !697)
!708 = !DILocation(line: 132, column: 7, scope: !709)
!709 = distinct !DILexicalBlock(scope: !409, file: !1, line: 132, column: 7)
!710 = !DILocation(line: 132, column: 12, scope: !709)
!711 = !DILocation(line: 132, column: 7, scope: !409)
!712 = !DILocation(line: 133, column: 5, scope: !709)
!713 = !DILocation(line: 133, column: 10, scope: !709)
!714 = !DILocation(line: 133, column: 13, scope: !709)
!715 = !DILocation(line: 133, column: 18, scope: !709)
!716 = !DILocation(line: 133, column: 23, scope: !709)
!717 = !DILocation(line: 133, column: 32, scope: !709)
!718 = !DILocation(line: 133, column: 37, scope: !709)
!719 = !DILocation(line: 134, column: 1, scope: !409)
!720 = !DILocalVariable(name: "ai", arg: 1, scope: !405, file: !1, line: 199, type: !358)
!721 = !DILocation(line: 199, column: 39, scope: !405)
!722 = !DILocation(line: 200, column: 7, scope: !723)
!723 = distinct !DILexicalBlock(scope: !405, file: !1, line: 200, column: 7)
!724 = !DILocation(line: 200, column: 7, scope: !405)
!725 = !DILocation(line: 201, column: 18, scope: !723)
!726 = !DILocation(line: 201, column: 5, scope: !723)
!727 = !DILocation(line: 202, column: 1, scope: !405)
