; ModuleID = '/data/download/cmake/cmake-master/Utilities/cmlibuv/src/unix/getnameinfo.c'
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
%struct.uv_getnameinfo_s = type { i8*, i32, [2 x i8*], [4 x i8*], %struct.uv_loop_s*, %struct.uv__work, void (%struct.uv_getnameinfo_s*, i32, i8*, i8*)*, %struct.sockaddr_storage, i32, [1025 x i8], [32 x i8], i32 }
%struct.uv__work = type { void (%struct.uv__work*)*, void (%struct.uv__work*, i32)*, %struct.uv_loop_s*, [2 x i8*] }
%struct.sockaddr_storage = type { i16, i64, [112 x i8] }
%struct.sockaddr = type { i16, [14 x i8] }
%struct.uv_req_s = type { i8*, i32, [2 x i8*], [4 x i8*] }

@.str = private unnamed_addr constant [123 x i8] c"(((const QUEUE *) (&(req->loop)->active_reqs) == (const QUEUE *) (*(QUEUE **) &((*(&(req->loop)->active_reqs))[0]))) == 0)\00", align 1
@.str.1 = private unnamed_addr constant [75 x i8] c"/data/download/cmake/cmake-master/Utilities/cmlibuv/src/unix/getnameinfo.c\00", align 1
@__PRETTY_FUNCTION__.uv__getnameinfo_done = private unnamed_addr constant [50 x i8] c"void uv__getnameinfo_done(struct uv__work *, int)\00", align 1
@.str.2 = private unnamed_addr constant [18 x i8] c"req->retcode == 0\00", align 1

; Function Attrs: nounwind uwtable
define i32 @uv_getnameinfo(%struct.uv_loop_s* %loop, %struct.uv_getnameinfo_s* %req, void (%struct.uv_getnameinfo_s*, i32, i8*, i8*)* %getnameinfo_cb, %struct.sockaddr* %addr, i32 %flags) #0 !dbg !403 {
entry:
  %retval = alloca i32, align 4
  %loop.addr = alloca %struct.uv_loop_s*, align 8
  %req.addr = alloca %struct.uv_getnameinfo_s*, align 8
  %getnameinfo_cb.addr = alloca void (%struct.uv_getnameinfo_s*, i32, i8*, i8*)*, align 8
  %addr.addr = alloca %struct.sockaddr*, align 8
  %flags.addr = alloca i32, align 4
  store %struct.uv_loop_s* %loop, %struct.uv_loop_s** %loop.addr, align 8
  call void @llvm.dbg.declare(metadata %struct.uv_loop_s** %loop.addr, metadata !414, metadata !415), !dbg !416
  store %struct.uv_getnameinfo_s* %req, %struct.uv_getnameinfo_s** %req.addr, align 8
  call void @llvm.dbg.declare(metadata %struct.uv_getnameinfo_s** %req.addr, metadata !417, metadata !415), !dbg !418
  store void (%struct.uv_getnameinfo_s*, i32, i8*, i8*)* %getnameinfo_cb, void (%struct.uv_getnameinfo_s*, i32, i8*, i8*)** %getnameinfo_cb.addr, align 8
  call void @llvm.dbg.declare(metadata void (%struct.uv_getnameinfo_s*, i32, i8*, i8*)** %getnameinfo_cb.addr, metadata !419, metadata !415), !dbg !420
  store %struct.sockaddr* %addr, %struct.sockaddr** %addr.addr, align 8
  call void @llvm.dbg.declare(metadata %struct.sockaddr** %addr.addr, metadata !421, metadata !415), !dbg !422
  store i32 %flags, i32* %flags.addr, align 4
  call void @llvm.dbg.declare(metadata i32* %flags.addr, metadata !423, metadata !415), !dbg !424
  %0 = load %struct.uv_getnameinfo_s*, %struct.uv_getnameinfo_s** %req.addr, align 8, !dbg !425
  %cmp = icmp eq %struct.uv_getnameinfo_s* %0, null, !dbg !427
  br i1 %cmp, label %if.then, label %lor.lhs.false, !dbg !428

lor.lhs.false:                                    ; preds = %entry
  %1 = load %struct.sockaddr*, %struct.sockaddr** %addr.addr, align 8, !dbg !429
  %cmp1 = icmp eq %struct.sockaddr* %1, null, !dbg !431
  br i1 %cmp1, label %if.then, label %if.end, !dbg !432

if.then:                                          ; preds = %lor.lhs.false, %entry
  store i32 -22, i32* %retval, align 4, !dbg !433
  br label %return, !dbg !433

if.end:                                           ; preds = %lor.lhs.false
  %2 = load %struct.sockaddr*, %struct.sockaddr** %addr.addr, align 8, !dbg !434
  %sa_family = getelementptr inbounds %struct.sockaddr, %struct.sockaddr* %2, i32 0, i32 0, !dbg !436
  %3 = load i16, i16* %sa_family, align 2, !dbg !436
  %conv = zext i16 %3 to i32, !dbg !434
  %cmp2 = icmp eq i32 %conv, 2, !dbg !437
  br i1 %cmp2, label %if.then4, label %if.else, !dbg !438

if.then4:                                         ; preds = %if.end
  %4 = load %struct.uv_getnameinfo_s*, %struct.uv_getnameinfo_s** %req.addr, align 8, !dbg !439
  %storage = getelementptr inbounds %struct.uv_getnameinfo_s, %struct.uv_getnameinfo_s* %4, i32 0, i32 7, !dbg !441
  %5 = bitcast %struct.sockaddr_storage* %storage to i8*, !dbg !442
  %6 = load %struct.sockaddr*, %struct.sockaddr** %addr.addr, align 8, !dbg !443
  %7 = bitcast %struct.sockaddr* %6 to i8*, !dbg !442
  call void @llvm.memcpy.p0i8.p0i8.i64(i8* %5, i8* %7, i64 16, i32 2, i1 false), !dbg !442
  br label %if.end13, !dbg !444

if.else:                                          ; preds = %if.end
  %8 = load %struct.sockaddr*, %struct.sockaddr** %addr.addr, align 8, !dbg !445
  %sa_family5 = getelementptr inbounds %struct.sockaddr, %struct.sockaddr* %8, i32 0, i32 0, !dbg !448
  %9 = load i16, i16* %sa_family5, align 2, !dbg !448
  %conv6 = zext i16 %9 to i32, !dbg !445
  %cmp7 = icmp eq i32 %conv6, 10, !dbg !449
  br i1 %cmp7, label %if.then9, label %if.else11, !dbg !445

if.then9:                                         ; preds = %if.else
  %10 = load %struct.uv_getnameinfo_s*, %struct.uv_getnameinfo_s** %req.addr, align 8, !dbg !450
  %storage10 = getelementptr inbounds %struct.uv_getnameinfo_s, %struct.uv_getnameinfo_s* %10, i32 0, i32 7, !dbg !452
  %11 = bitcast %struct.sockaddr_storage* %storage10 to i8*, !dbg !453
  %12 = load %struct.sockaddr*, %struct.sockaddr** %addr.addr, align 8, !dbg !454
  %13 = bitcast %struct.sockaddr* %12 to i8*, !dbg !453
  call void @llvm.memcpy.p0i8.p0i8.i64(i8* %11, i8* %13, i64 28, i32 2, i1 false), !dbg !453
  br label %if.end12, !dbg !455

if.else11:                                        ; preds = %if.else
  store i32 -22, i32* %retval, align 4, !dbg !456
  br label %return, !dbg !456

if.end12:                                         ; preds = %if.then9
  br label %if.end13

if.end13:                                         ; preds = %if.end12, %if.then4
  br label %do.body, !dbg !458

do.body:                                          ; preds = %if.end13
  br label %do.body14, !dbg !459

do.body14:                                        ; preds = %do.body
  %14 = load %struct.uv_getnameinfo_s*, %struct.uv_getnameinfo_s** %req.addr, align 8, !dbg !462
  %15 = bitcast %struct.uv_getnameinfo_s* %14 to %struct.uv_req_s*, !dbg !462
  %type = getelementptr inbounds %struct.uv_req_s, %struct.uv_req_s* %15, i32 0, i32 1, !dbg !462
  store i32 9, i32* %type, align 8, !dbg !462
  br label %do.end, !dbg !462

do.end:                                           ; preds = %do.body14
  br label %do.body15, !dbg !465

do.body15:                                        ; preds = %do.end
  br label %do.body16, !dbg !467

do.body16:                                        ; preds = %do.body15
  %16 = load %struct.uv_loop_s*, %struct.uv_loop_s** %loop.addr, align 8, !dbg !470
  %active_reqs = getelementptr inbounds %struct.uv_loop_s, %struct.uv_loop_s* %16, i32 0, i32 3, !dbg !470
  %17 = load %struct.uv_getnameinfo_s*, %struct.uv_getnameinfo_s** %req.addr, align 8, !dbg !470
  %18 = bitcast %struct.uv_getnameinfo_s* %17 to %struct.uv_req_s*, !dbg !470
  %active_queue = getelementptr inbounds %struct.uv_req_s, %struct.uv_req_s* %18, i32 0, i32 2, !dbg !470
  %arrayidx = getelementptr inbounds [2 x i8*], [2 x i8*]* %active_queue, i64 0, i64 0, !dbg !470
  %19 = bitcast i8** %arrayidx to [2 x i8*]**, !dbg !470
  store [2 x i8*]* %active_reqs, [2 x i8*]** %19, align 8, !dbg !470
  %20 = load %struct.uv_loop_s*, %struct.uv_loop_s** %loop.addr, align 8, !dbg !470
  %active_reqs17 = getelementptr inbounds %struct.uv_loop_s, %struct.uv_loop_s* %20, i32 0, i32 3, !dbg !470
  %arrayidx18 = getelementptr inbounds [2 x i8*], [2 x i8*]* %active_reqs17, i64 0, i64 1, !dbg !470
  %21 = bitcast i8** %arrayidx18 to [2 x i8*]**, !dbg !470
  %22 = load [2 x i8*]*, [2 x i8*]** %21, align 8, !dbg !470
  %23 = load %struct.uv_getnameinfo_s*, %struct.uv_getnameinfo_s** %req.addr, align 8, !dbg !470
  %24 = bitcast %struct.uv_getnameinfo_s* %23 to %struct.uv_req_s*, !dbg !470
  %active_queue19 = getelementptr inbounds %struct.uv_req_s, %struct.uv_req_s* %24, i32 0, i32 2, !dbg !470
  %arrayidx20 = getelementptr inbounds [2 x i8*], [2 x i8*]* %active_queue19, i64 0, i64 1, !dbg !470
  %25 = bitcast i8** %arrayidx20 to [2 x i8*]**, !dbg !470
  store [2 x i8*]* %22, [2 x i8*]** %25, align 8, !dbg !470
  %26 = load %struct.uv_getnameinfo_s*, %struct.uv_getnameinfo_s** %req.addr, align 8, !dbg !470
  %27 = bitcast %struct.uv_getnameinfo_s* %26 to %struct.uv_req_s*, !dbg !470
  %active_queue21 = getelementptr inbounds %struct.uv_req_s, %struct.uv_req_s* %27, i32 0, i32 2, !dbg !470
  %28 = load %struct.uv_getnameinfo_s*, %struct.uv_getnameinfo_s** %req.addr, align 8, !dbg !470
  %29 = bitcast %struct.uv_getnameinfo_s* %28 to %struct.uv_req_s*, !dbg !470
  %active_queue22 = getelementptr inbounds %struct.uv_req_s, %struct.uv_req_s* %29, i32 0, i32 2, !dbg !470
  %arrayidx23 = getelementptr inbounds [2 x i8*], [2 x i8*]* %active_queue22, i64 0, i64 1, !dbg !470
  %30 = bitcast i8** %arrayidx23 to [2 x i8*]**, !dbg !470
  %31 = load [2 x i8*]*, [2 x i8*]** %30, align 8, !dbg !470
  %arrayidx24 = getelementptr inbounds [2 x i8*], [2 x i8*]* %31, i64 0, i64 0, !dbg !470
  %32 = bitcast i8** %arrayidx24 to [2 x i8*]**, !dbg !470
  store [2 x i8*]* %active_queue21, [2 x i8*]** %32, align 8, !dbg !470
  %33 = load %struct.uv_getnameinfo_s*, %struct.uv_getnameinfo_s** %req.addr, align 8, !dbg !470
  %34 = bitcast %struct.uv_getnameinfo_s* %33 to %struct.uv_req_s*, !dbg !470
  %active_queue25 = getelementptr inbounds %struct.uv_req_s, %struct.uv_req_s* %34, i32 0, i32 2, !dbg !470
  %35 = load %struct.uv_loop_s*, %struct.uv_loop_s** %loop.addr, align 8, !dbg !470
  %active_reqs26 = getelementptr inbounds %struct.uv_loop_s, %struct.uv_loop_s* %35, i32 0, i32 3, !dbg !470
  %arrayidx27 = getelementptr inbounds [2 x i8*], [2 x i8*]* %active_reqs26, i64 0, i64 1, !dbg !470
  %36 = bitcast i8** %arrayidx27 to [2 x i8*]**, !dbg !470
  store [2 x i8*]* %active_queue25, [2 x i8*]** %36, align 8, !dbg !470
  br label %do.end28, !dbg !470

do.end28:                                         ; preds = %do.body16
  br label %do.end29, !dbg !473

do.end29:                                         ; preds = %do.end28
  br label %do.end30, !dbg !475

do.end30:                                         ; preds = %do.end29
  %37 = load void (%struct.uv_getnameinfo_s*, i32, i8*, i8*)*, void (%struct.uv_getnameinfo_s*, i32, i8*, i8*)** %getnameinfo_cb.addr, align 8, !dbg !477
  %38 = load %struct.uv_getnameinfo_s*, %struct.uv_getnameinfo_s** %req.addr, align 8, !dbg !478
  %getnameinfo_cb31 = getelementptr inbounds %struct.uv_getnameinfo_s, %struct.uv_getnameinfo_s* %38, i32 0, i32 6, !dbg !479
  store void (%struct.uv_getnameinfo_s*, i32, i8*, i8*)* %37, void (%struct.uv_getnameinfo_s*, i32, i8*, i8*)** %getnameinfo_cb31, align 8, !dbg !480
  %39 = load i32, i32* %flags.addr, align 4, !dbg !481
  %40 = load %struct.uv_getnameinfo_s*, %struct.uv_getnameinfo_s** %req.addr, align 8, !dbg !482
  %flags32 = getelementptr inbounds %struct.uv_getnameinfo_s, %struct.uv_getnameinfo_s* %40, i32 0, i32 8, !dbg !483
  store i32 %39, i32* %flags32, align 8, !dbg !484
  %41 = load %struct.uv_getnameinfo_s*, %struct.uv_getnameinfo_s** %req.addr, align 8, !dbg !485
  %type33 = getelementptr inbounds %struct.uv_getnameinfo_s, %struct.uv_getnameinfo_s* %41, i32 0, i32 1, !dbg !486
  store i32 9, i32* %type33, align 8, !dbg !487
  %42 = load %struct.uv_loop_s*, %struct.uv_loop_s** %loop.addr, align 8, !dbg !488
  %43 = load %struct.uv_getnameinfo_s*, %struct.uv_getnameinfo_s** %req.addr, align 8, !dbg !489
  %loop34 = getelementptr inbounds %struct.uv_getnameinfo_s, %struct.uv_getnameinfo_s* %43, i32 0, i32 4, !dbg !490
  store %struct.uv_loop_s* %42, %struct.uv_loop_s** %loop34, align 8, !dbg !491
  %44 = load %struct.uv_getnameinfo_s*, %struct.uv_getnameinfo_s** %req.addr, align 8, !dbg !492
  %retcode = getelementptr inbounds %struct.uv_getnameinfo_s, %struct.uv_getnameinfo_s* %44, i32 0, i32 11, !dbg !493
  store i32 0, i32* %retcode, align 8, !dbg !494
  %45 = load void (%struct.uv_getnameinfo_s*, i32, i8*, i8*)*, void (%struct.uv_getnameinfo_s*, i32, i8*, i8*)** %getnameinfo_cb.addr, align 8, !dbg !495
  %tobool = icmp ne void (%struct.uv_getnameinfo_s*, i32, i8*, i8*)* %45, null, !dbg !495
  br i1 %tobool, label %if.then35, label %if.else36, !dbg !497

if.then35:                                        ; preds = %do.end30
  %46 = load %struct.uv_loop_s*, %struct.uv_loop_s** %loop.addr, align 8, !dbg !498
  %47 = load %struct.uv_getnameinfo_s*, %struct.uv_getnameinfo_s** %req.addr, align 8, !dbg !500
  %work_req = getelementptr inbounds %struct.uv_getnameinfo_s, %struct.uv_getnameinfo_s* %47, i32 0, i32 5, !dbg !501
  call void @uv__work_submit(%struct.uv_loop_s* %46, %struct.uv__work* %work_req, void (%struct.uv__work*)* @uv__getnameinfo_work, void (%struct.uv__work*, i32)* @uv__getnameinfo_done), !dbg !502
  store i32 0, i32* %retval, align 4, !dbg !503
  br label %return, !dbg !503

if.else36:                                        ; preds = %do.end30
  %48 = load %struct.uv_getnameinfo_s*, %struct.uv_getnameinfo_s** %req.addr, align 8, !dbg !504
  %work_req37 = getelementptr inbounds %struct.uv_getnameinfo_s, %struct.uv_getnameinfo_s* %48, i32 0, i32 5, !dbg !506
  call void @uv__getnameinfo_work(%struct.uv__work* %work_req37), !dbg !507
  %49 = load %struct.uv_getnameinfo_s*, %struct.uv_getnameinfo_s** %req.addr, align 8, !dbg !508
  %work_req38 = getelementptr inbounds %struct.uv_getnameinfo_s, %struct.uv_getnameinfo_s* %49, i32 0, i32 5, !dbg !509
  call void @uv__getnameinfo_done(%struct.uv__work* %work_req38, i32 0), !dbg !510
  %50 = load %struct.uv_getnameinfo_s*, %struct.uv_getnameinfo_s** %req.addr, align 8, !dbg !511
  %retcode39 = getelementptr inbounds %struct.uv_getnameinfo_s, %struct.uv_getnameinfo_s* %50, i32 0, i32 11, !dbg !512
  %51 = load i32, i32* %retcode39, align 8, !dbg !512
  store i32 %51, i32* %retval, align 4, !dbg !513
  br label %return, !dbg !513

return:                                           ; preds = %if.else36, %if.then35, %if.else11, %if.then
  %52 = load i32, i32* %retval, align 4, !dbg !514
  ret i32 %52, !dbg !514
}

; Function Attrs: nounwind readnone
declare void @llvm.dbg.declare(metadata, metadata, metadata) #1

; Function Attrs: argmemonly nounwind
declare void @llvm.memcpy.p0i8.p0i8.i64(i8* nocapture, i8* nocapture readonly, i64, i32, i1) #2

declare void @uv__work_submit(%struct.uv_loop_s*, %struct.uv__work*, void (%struct.uv__work*)*, void (%struct.uv__work*, i32)*) #3

; Function Attrs: nounwind uwtable
define internal void @uv__getnameinfo_work(%struct.uv__work* %w) #0 !dbg !409 {
entry:
  %w.addr = alloca %struct.uv__work*, align 8
  %req = alloca %struct.uv_getnameinfo_s*, align 8
  %err = alloca i32, align 4
  %salen = alloca i32, align 4
  store %struct.uv__work* %w, %struct.uv__work** %w.addr, align 8
  call void @llvm.dbg.declare(metadata %struct.uv__work** %w.addr, metadata !515, metadata !415), !dbg !516
  call void @llvm.dbg.declare(metadata %struct.uv_getnameinfo_s** %req, metadata !517, metadata !415), !dbg !518
  call void @llvm.dbg.declare(metadata i32* %err, metadata !519, metadata !415), !dbg !520
  call void @llvm.dbg.declare(metadata i32* %salen, metadata !521, metadata !415), !dbg !525
  %0 = load %struct.uv__work*, %struct.uv__work** %w.addr, align 8, !dbg !526
  %1 = bitcast %struct.uv__work* %0 to i8*, !dbg !526
  %add.ptr = getelementptr inbounds i8, i8* %1, i64 -72, !dbg !526
  %2 = bitcast i8* %add.ptr to %struct.uv_getnameinfo_s*, !dbg !526
  store %struct.uv_getnameinfo_s* %2, %struct.uv_getnameinfo_s** %req, align 8, !dbg !527
  %3 = load %struct.uv_getnameinfo_s*, %struct.uv_getnameinfo_s** %req, align 8, !dbg !528
  %storage = getelementptr inbounds %struct.uv_getnameinfo_s, %struct.uv_getnameinfo_s* %3, i32 0, i32 7, !dbg !530
  %ss_family = getelementptr inbounds %struct.sockaddr_storage, %struct.sockaddr_storage* %storage, i32 0, i32 0, !dbg !531
  %4 = load i16, i16* %ss_family, align 8, !dbg !531
  %conv = zext i16 %4 to i32, !dbg !528
  %cmp = icmp eq i32 %conv, 2, !dbg !532
  br i1 %cmp, label %if.then, label %if.else, !dbg !533

if.then:                                          ; preds = %entry
  store i32 16, i32* %salen, align 4, !dbg !534
  br label %if.end9, !dbg !535

if.else:                                          ; preds = %entry
  %5 = load %struct.uv_getnameinfo_s*, %struct.uv_getnameinfo_s** %req, align 8, !dbg !536
  %storage2 = getelementptr inbounds %struct.uv_getnameinfo_s, %struct.uv_getnameinfo_s* %5, i32 0, i32 7, !dbg !538
  %ss_family3 = getelementptr inbounds %struct.sockaddr_storage, %struct.sockaddr_storage* %storage2, i32 0, i32 0, !dbg !539
  %6 = load i16, i16* %ss_family3, align 8, !dbg !539
  %conv4 = zext i16 %6 to i32, !dbg !536
  %cmp5 = icmp eq i32 %conv4, 10, !dbg !540
  br i1 %cmp5, label %if.then7, label %if.else8, !dbg !541

if.then7:                                         ; preds = %if.else
  store i32 28, i32* %salen, align 4, !dbg !542
  br label %if.end, !dbg !543

if.else8:                                         ; preds = %if.else
  call void @abort() #5, !dbg !544
  unreachable, !dbg !544

if.end:                                           ; preds = %if.then7
  br label %if.end9

if.end9:                                          ; preds = %if.end, %if.then
  %7 = load %struct.uv_getnameinfo_s*, %struct.uv_getnameinfo_s** %req, align 8, !dbg !545
  %storage10 = getelementptr inbounds %struct.uv_getnameinfo_s, %struct.uv_getnameinfo_s* %7, i32 0, i32 7, !dbg !546
  %8 = bitcast %struct.sockaddr_storage* %storage10 to %struct.sockaddr*, !dbg !547
  %9 = load i32, i32* %salen, align 4, !dbg !548
  %10 = load %struct.uv_getnameinfo_s*, %struct.uv_getnameinfo_s** %req, align 8, !dbg !549
  %host = getelementptr inbounds %struct.uv_getnameinfo_s, %struct.uv_getnameinfo_s* %10, i32 0, i32 9, !dbg !550
  %arraydecay = getelementptr inbounds [1025 x i8], [1025 x i8]* %host, i32 0, i32 0, !dbg !549
  %11 = load %struct.uv_getnameinfo_s*, %struct.uv_getnameinfo_s** %req, align 8, !dbg !551
  %service = getelementptr inbounds %struct.uv_getnameinfo_s, %struct.uv_getnameinfo_s* %11, i32 0, i32 10, !dbg !552
  %arraydecay11 = getelementptr inbounds [32 x i8], [32 x i8]* %service, i32 0, i32 0, !dbg !551
  %12 = load %struct.uv_getnameinfo_s*, %struct.uv_getnameinfo_s** %req, align 8, !dbg !553
  %flags = getelementptr inbounds %struct.uv_getnameinfo_s, %struct.uv_getnameinfo_s* %12, i32 0, i32 8, !dbg !554
  %13 = load i32, i32* %flags, align 8, !dbg !554
  %call = call i32 @getnameinfo(%struct.sockaddr* %8, i32 %9, i8* %arraydecay, i32 1025, i8* %arraydecay11, i32 32, i32 %13), !dbg !555
  store i32 %call, i32* %err, align 4, !dbg !556
  %14 = load i32, i32* %err, align 4, !dbg !557
  %call12 = call i32 @uv__getaddrinfo_translate_error(i32 %14), !dbg !558
  %15 = load %struct.uv_getnameinfo_s*, %struct.uv_getnameinfo_s** %req, align 8, !dbg !559
  %retcode = getelementptr inbounds %struct.uv_getnameinfo_s, %struct.uv_getnameinfo_s* %15, i32 0, i32 11, !dbg !560
  store i32 %call12, i32* %retcode, align 8, !dbg !561
  ret void, !dbg !562
}

; Function Attrs: nounwind uwtable
define internal void @uv__getnameinfo_done(%struct.uv__work* %w, i32 %status) #0 !dbg !410 {
entry:
  %w.addr = alloca %struct.uv__work*, align 8
  %status.addr = alloca i32, align 4
  %req = alloca %struct.uv_getnameinfo_s*, align 8
  %host = alloca i8*, align 8
  %service = alloca i8*, align 8
  store %struct.uv__work* %w, %struct.uv__work** %w.addr, align 8
  call void @llvm.dbg.declare(metadata %struct.uv__work** %w.addr, metadata !563, metadata !415), !dbg !564
  store i32 %status, i32* %status.addr, align 4
  call void @llvm.dbg.declare(metadata i32* %status.addr, metadata !565, metadata !415), !dbg !566
  call void @llvm.dbg.declare(metadata %struct.uv_getnameinfo_s** %req, metadata !567, metadata !415), !dbg !568
  call void @llvm.dbg.declare(metadata i8** %host, metadata !569, metadata !415), !dbg !570
  call void @llvm.dbg.declare(metadata i8** %service, metadata !571, metadata !415), !dbg !572
  %0 = load %struct.uv__work*, %struct.uv__work** %w.addr, align 8, !dbg !573
  %1 = bitcast %struct.uv__work* %0 to i8*, !dbg !573
  %add.ptr = getelementptr inbounds i8, i8* %1, i64 -72, !dbg !573
  %2 = bitcast i8* %add.ptr to %struct.uv_getnameinfo_s*, !dbg !573
  store %struct.uv_getnameinfo_s* %2, %struct.uv_getnameinfo_s** %req, align 8, !dbg !574
  br label %do.body, !dbg !575

do.body:                                          ; preds = %entry
  %3 = load %struct.uv_getnameinfo_s*, %struct.uv_getnameinfo_s** %req, align 8, !dbg !576
  %loop = getelementptr inbounds %struct.uv_getnameinfo_s, %struct.uv_getnameinfo_s* %3, i32 0, i32 4, !dbg !576
  %4 = load %struct.uv_loop_s*, %struct.uv_loop_s** %loop, align 8, !dbg !576
  %active_reqs = getelementptr inbounds %struct.uv_loop_s, %struct.uv_loop_s* %4, i32 0, i32 3, !dbg !576
  %5 = load %struct.uv_getnameinfo_s*, %struct.uv_getnameinfo_s** %req, align 8, !dbg !576
  %loop1 = getelementptr inbounds %struct.uv_getnameinfo_s, %struct.uv_getnameinfo_s* %5, i32 0, i32 4, !dbg !576
  %6 = load %struct.uv_loop_s*, %struct.uv_loop_s** %loop1, align 8, !dbg !576
  %active_reqs2 = getelementptr inbounds %struct.uv_loop_s, %struct.uv_loop_s* %6, i32 0, i32 3, !dbg !576
  %arrayidx = getelementptr inbounds [2 x i8*], [2 x i8*]* %active_reqs2, i64 0, i64 0, !dbg !576
  %7 = bitcast i8** %arrayidx to [2 x i8*]**, !dbg !576
  %8 = load [2 x i8*]*, [2 x i8*]** %7, align 8, !dbg !576
  %cmp = icmp eq [2 x i8*]* %active_reqs, %8, !dbg !576
  %conv = zext i1 %cmp to i32, !dbg !576
  %cmp3 = icmp eq i32 %conv, 0, !dbg !576
  br i1 %cmp3, label %cond.true, label %cond.false, !dbg !576

cond.true:                                        ; preds = %do.body
  br label %cond.end, !dbg !579

cond.false:                                       ; preds = %do.body
  call void @__assert_fail(i8* getelementptr inbounds ([123 x i8], [123 x i8]* @.str, i32 0, i32 0), i8* getelementptr inbounds ([75 x i8], [75 x i8]* @.str.1, i32 0, i32 0), i32 61, i8* getelementptr inbounds ([50 x i8], [50 x i8]* @__PRETTY_FUNCTION__.uv__getnameinfo_done, i32 0, i32 0)) #5, !dbg !581
  unreachable, !dbg !581
                                                  ; No predecessors!
  br label %cond.end, !dbg !583

cond.end:                                         ; preds = %9, %cond.true
  br label %do.body5, !dbg !585

do.body5:                                         ; preds = %cond.end
  %10 = load %struct.uv_getnameinfo_s*, %struct.uv_getnameinfo_s** %req, align 8, !dbg !587
  %active_queue = getelementptr inbounds %struct.uv_getnameinfo_s, %struct.uv_getnameinfo_s* %10, i32 0, i32 2, !dbg !587
  %arrayidx6 = getelementptr inbounds [2 x i8*], [2 x i8*]* %active_queue, i64 0, i64 0, !dbg !587
  %11 = bitcast i8** %arrayidx6 to [2 x i8*]**, !dbg !587
  %12 = load [2 x i8*]*, [2 x i8*]** %11, align 8, !dbg !587
  %13 = load %struct.uv_getnameinfo_s*, %struct.uv_getnameinfo_s** %req, align 8, !dbg !587
  %active_queue7 = getelementptr inbounds %struct.uv_getnameinfo_s, %struct.uv_getnameinfo_s* %13, i32 0, i32 2, !dbg !587
  %arrayidx8 = getelementptr inbounds [2 x i8*], [2 x i8*]* %active_queue7, i64 0, i64 1, !dbg !587
  %14 = bitcast i8** %arrayidx8 to [2 x i8*]**, !dbg !587
  %15 = load [2 x i8*]*, [2 x i8*]** %14, align 8, !dbg !587
  %arrayidx9 = getelementptr inbounds [2 x i8*], [2 x i8*]* %15, i64 0, i64 0, !dbg !587
  %16 = bitcast i8** %arrayidx9 to [2 x i8*]**, !dbg !587
  store [2 x i8*]* %12, [2 x i8*]** %16, align 8, !dbg !587
  %17 = load %struct.uv_getnameinfo_s*, %struct.uv_getnameinfo_s** %req, align 8, !dbg !587
  %active_queue10 = getelementptr inbounds %struct.uv_getnameinfo_s, %struct.uv_getnameinfo_s* %17, i32 0, i32 2, !dbg !587
  %arrayidx11 = getelementptr inbounds [2 x i8*], [2 x i8*]* %active_queue10, i64 0, i64 1, !dbg !587
  %18 = bitcast i8** %arrayidx11 to [2 x i8*]**, !dbg !587
  %19 = load [2 x i8*]*, [2 x i8*]** %18, align 8, !dbg !587
  %20 = load %struct.uv_getnameinfo_s*, %struct.uv_getnameinfo_s** %req, align 8, !dbg !587
  %active_queue12 = getelementptr inbounds %struct.uv_getnameinfo_s, %struct.uv_getnameinfo_s* %20, i32 0, i32 2, !dbg !587
  %arrayidx13 = getelementptr inbounds [2 x i8*], [2 x i8*]* %active_queue12, i64 0, i64 0, !dbg !587
  %21 = bitcast i8** %arrayidx13 to [2 x i8*]**, !dbg !587
  %22 = load [2 x i8*]*, [2 x i8*]** %21, align 8, !dbg !587
  %arrayidx14 = getelementptr inbounds [2 x i8*], [2 x i8*]* %22, i64 0, i64 1, !dbg !587
  %23 = bitcast i8** %arrayidx14 to [2 x i8*]**, !dbg !587
  store [2 x i8*]* %19, [2 x i8*]** %23, align 8, !dbg !587
  br label %do.end, !dbg !587

do.end:                                           ; preds = %do.body5
  br label %do.end15, !dbg !590

do.end15:                                         ; preds = %do.end
  store i8* null, i8** %service, align 8, !dbg !592
  store i8* null, i8** %host, align 8, !dbg !593
  %24 = load i32, i32* %status.addr, align 4, !dbg !594
  %cmp16 = icmp eq i32 %24, -125, !dbg !596
  br i1 %cmp16, label %if.then, label %if.else, !dbg !597

if.then:                                          ; preds = %do.end15
  %25 = load %struct.uv_getnameinfo_s*, %struct.uv_getnameinfo_s** %req, align 8, !dbg !598
  %retcode = getelementptr inbounds %struct.uv_getnameinfo_s, %struct.uv_getnameinfo_s* %25, i32 0, i32 11, !dbg !598
  %26 = load i32, i32* %retcode, align 8, !dbg !598
  %cmp18 = icmp eq i32 %26, 0, !dbg !598
  br i1 %cmp18, label %cond.true20, label %cond.false21, !dbg !598

cond.true20:                                      ; preds = %if.then
  br label %cond.end22, !dbg !600

cond.false21:                                     ; preds = %if.then
  call void @__assert_fail(i8* getelementptr inbounds ([18 x i8], [18 x i8]* @.str.2, i32 0, i32 0), i8* getelementptr inbounds ([75 x i8], [75 x i8]* @.str.1, i32 0, i32 0), i32 65, i8* getelementptr inbounds ([50 x i8], [50 x i8]* @__PRETTY_FUNCTION__.uv__getnameinfo_done, i32 0, i32 0)) #5, !dbg !602
  unreachable, !dbg !602
                                                  ; No predecessors!
  br label %cond.end22, !dbg !604

cond.end22:                                       ; preds = %27, %cond.true20
  %28 = load %struct.uv_getnameinfo_s*, %struct.uv_getnameinfo_s** %req, align 8, !dbg !606
  %retcode23 = getelementptr inbounds %struct.uv_getnameinfo_s, %struct.uv_getnameinfo_s* %28, i32 0, i32 11, !dbg !607
  store i32 -3003, i32* %retcode23, align 8, !dbg !608
  br label %if.end31, !dbg !609

if.else:                                          ; preds = %do.end15
  %29 = load %struct.uv_getnameinfo_s*, %struct.uv_getnameinfo_s** %req, align 8, !dbg !610
  %retcode24 = getelementptr inbounds %struct.uv_getnameinfo_s, %struct.uv_getnameinfo_s* %29, i32 0, i32 11, !dbg !613
  %30 = load i32, i32* %retcode24, align 8, !dbg !613
  %cmp25 = icmp eq i32 %30, 0, !dbg !614
  br i1 %cmp25, label %if.then27, label %if.end, !dbg !610

if.then27:                                        ; preds = %if.else
  %31 = load %struct.uv_getnameinfo_s*, %struct.uv_getnameinfo_s** %req, align 8, !dbg !615
  %host28 = getelementptr inbounds %struct.uv_getnameinfo_s, %struct.uv_getnameinfo_s* %31, i32 0, i32 9, !dbg !617
  %arraydecay = getelementptr inbounds [1025 x i8], [1025 x i8]* %host28, i32 0, i32 0, !dbg !615
  store i8* %arraydecay, i8** %host, align 8, !dbg !618
  %32 = load %struct.uv_getnameinfo_s*, %struct.uv_getnameinfo_s** %req, align 8, !dbg !619
  %service29 = getelementptr inbounds %struct.uv_getnameinfo_s, %struct.uv_getnameinfo_s* %32, i32 0, i32 10, !dbg !620
  %arraydecay30 = getelementptr inbounds [32 x i8], [32 x i8]* %service29, i32 0, i32 0, !dbg !619
  store i8* %arraydecay30, i8** %service, align 8, !dbg !621
  br label %if.end, !dbg !622

if.end:                                           ; preds = %if.then27, %if.else
  br label %if.end31

if.end31:                                         ; preds = %if.end, %cond.end22
  %33 = load %struct.uv_getnameinfo_s*, %struct.uv_getnameinfo_s** %req, align 8, !dbg !623
  %getnameinfo_cb = getelementptr inbounds %struct.uv_getnameinfo_s, %struct.uv_getnameinfo_s* %33, i32 0, i32 6, !dbg !625
  %34 = load void (%struct.uv_getnameinfo_s*, i32, i8*, i8*)*, void (%struct.uv_getnameinfo_s*, i32, i8*, i8*)** %getnameinfo_cb, align 8, !dbg !625
  %tobool = icmp ne void (%struct.uv_getnameinfo_s*, i32, i8*, i8*)* %34, null, !dbg !623
  br i1 %tobool, label %if.then32, label %if.end35, !dbg !626

if.then32:                                        ; preds = %if.end31
  %35 = load %struct.uv_getnameinfo_s*, %struct.uv_getnameinfo_s** %req, align 8, !dbg !627
  %getnameinfo_cb33 = getelementptr inbounds %struct.uv_getnameinfo_s, %struct.uv_getnameinfo_s* %35, i32 0, i32 6, !dbg !628
  %36 = load void (%struct.uv_getnameinfo_s*, i32, i8*, i8*)*, void (%struct.uv_getnameinfo_s*, i32, i8*, i8*)** %getnameinfo_cb33, align 8, !dbg !628
  %37 = load %struct.uv_getnameinfo_s*, %struct.uv_getnameinfo_s** %req, align 8, !dbg !629
  %38 = load %struct.uv_getnameinfo_s*, %struct.uv_getnameinfo_s** %req, align 8, !dbg !630
  %retcode34 = getelementptr inbounds %struct.uv_getnameinfo_s, %struct.uv_getnameinfo_s* %38, i32 0, i32 11, !dbg !631
  %39 = load i32, i32* %retcode34, align 8, !dbg !631
  %40 = load i8*, i8** %host, align 8, !dbg !632
  %41 = load i8*, i8** %service, align 8, !dbg !633
  call void %36(%struct.uv_getnameinfo_s* %37, i32 %39, i8* %40, i8* %41), !dbg !627
  br label %if.end35, !dbg !627

if.end35:                                         ; preds = %if.then32, %if.end31
  ret void, !dbg !634
}

; Function Attrs: noreturn nounwind
declare void @abort() #4

declare i32 @getnameinfo(%struct.sockaddr*, i32, i8*, i32, i8*, i32, i32) #3

declare i32 @uv__getaddrinfo_translate_error(i32) #3

; Function Attrs: noreturn nounwind
declare void @__assert_fail(i8*, i8*, i32, i8*) #4

attributes #0 = { nounwind uwtable "disable-tail-calls"="false" "less-precise-fpmad"="false" "no-frame-pointer-elim"="true" "no-frame-pointer-elim-non-leaf" "no-infs-fp-math"="false" "no-nans-fp-math"="false" "stack-protector-buffer-size"="8" "target-cpu"="x86-64" "target-features"="+fxsr,+mmx,+sse,+sse2" "unsafe-fp-math"="false" "use-soft-float"="false" }
attributes #1 = { nounwind readnone }
attributes #2 = { argmemonly nounwind }
attributes #3 = { "disable-tail-calls"="false" "less-precise-fpmad"="false" "no-frame-pointer-elim"="true" "no-frame-pointer-elim-non-leaf" "no-infs-fp-math"="false" "no-nans-fp-math"="false" "stack-protector-buffer-size"="8" "target-cpu"="x86-64" "target-features"="+fxsr,+mmx,+sse,+sse2" "unsafe-fp-math"="false" "use-soft-float"="false" }
attributes #4 = { noreturn nounwind "disable-tail-calls"="false" "less-precise-fpmad"="false" "no-frame-pointer-elim"="true" "no-frame-pointer-elim-non-leaf" "no-infs-fp-math"="false" "no-nans-fp-math"="false" "stack-protector-buffer-size"="8" "target-cpu"="x86-64" "target-features"="+fxsr,+mmx,+sse,+sse2" "unsafe-fp-math"="false" "use-soft-float"="false" }
attributes #5 = { noreturn nounwind }

!llvm.dbg.cu = !{!0}
!llvm.module.flags = !{!411, !412}
!llvm.ident = !{!413}

!0 = distinct !DICompileUnit(language: DW_LANG_C99, file: !1, producer: "clang version 3.8.0 (tags/RELEASE_380/final)", isOptimized: false, runtimeVersion: 0, emissionKind: 1, enums: !2, retainedTypes: !117, subprograms: !402)
!1 = !DIFile(filename: "/data/download/cmake/cmake-master/Utilities/cmlibuv/src/unix/getnameinfo.c", directory: "/data/download/cmake/cmake-master/Utilities/cmlibuv")
!2 = !{!3, !25, !38}
!3 = !DICompositeType(tag: DW_TAG_enumeration_type, file: !4, line: 184, size: 32, align: 32, elements: !5)
!4 = !DIFile(filename: "/data/download/cmake/cmake-master/Utilities/cmlibuv/include/uv.h", directory: "/data/download/cmake/cmake-master/Utilities/cmlibuv")
!5 = !{!6, !7, !8, !9, !10, !11, !12, !13, !14, !15, !16, !17, !18, !19, !20, !21, !22, !23, !24}
!6 = !DIEnumerator(name: "UV_UNKNOWN_HANDLE", value: 0)
!7 = !DIEnumerator(name: "UV_ASYNC", value: 1)
!8 = !DIEnumerator(name: "UV_CHECK", value: 2)
!9 = !DIEnumerator(name: "UV_FS_EVENT", value: 3)
!10 = !DIEnumerator(name: "UV_FS_POLL", value: 4)
!11 = !DIEnumerator(name: "UV_HANDLE", value: 5)
!12 = !DIEnumerator(name: "UV_IDLE", value: 6)
!13 = !DIEnumerator(name: "UV_NAMED_PIPE", value: 7)
!14 = !DIEnumerator(name: "UV_POLL", value: 8)
!15 = !DIEnumerator(name: "UV_PREPARE", value: 9)
!16 = !DIEnumerator(name: "UV_PROCESS", value: 10)
!17 = !DIEnumerator(name: "UV_STREAM", value: 11)
!18 = !DIEnumerator(name: "UV_TCP", value: 12)
!19 = !DIEnumerator(name: "UV_TIMER", value: 13)
!20 = !DIEnumerator(name: "UV_TTY", value: 14)
!21 = !DIEnumerator(name: "UV_UDP", value: 15)
!22 = !DIEnumerator(name: "UV_SIGNAL", value: 16)
!23 = !DIEnumerator(name: "UV_FILE", value: 17)
!24 = !DIEnumerator(name: "UV_HANDLE_TYPE_MAX", value: 18)
!25 = !DICompositeType(tag: DW_TAG_enumeration_type, file: !4, line: 193, size: 32, align: 32, elements: !26)
!26 = !{!27, !28, !29, !30, !31, !32, !33, !34, !35, !36, !37}
!27 = !DIEnumerator(name: "UV_UNKNOWN_REQ", value: 0)
!28 = !DIEnumerator(name: "UV_REQ", value: 1)
!29 = !DIEnumerator(name: "UV_CONNECT", value: 2)
!30 = !DIEnumerator(name: "UV_WRITE", value: 3)
!31 = !DIEnumerator(name: "UV_SHUTDOWN", value: 4)
!32 = !DIEnumerator(name: "UV_UDP_SEND", value: 5)
!33 = !DIEnumerator(name: "UV_FS", value: 6)
!34 = !DIEnumerator(name: "UV_WORK", value: 7)
!35 = !DIEnumerator(name: "UV_GETADDRINFO", value: 8)
!36 = !DIEnumerator(name: "UV_GETNAMEINFO", value: 9)
!37 = !DIEnumerator(name: "UV_REQ_TYPE_MAX", value: 10)
!38 = !DICompositeType(tag: DW_TAG_enumeration_type, file: !4, line: 177, size: 32, align: 32, elements: !39)
!39 = !{!40, !41, !42, !43, !44, !45, !46, !47, !48, !49, !50, !51, !52, !53, !54, !55, !56, !57, !58, !59, !60, !61, !62, !63, !64, !65, !66, !67, !68, !69, !70, !71, !72, !73, !74, !75, !76, !77, !78, !79, !80, !81, !82, !83, !84, !85, !86, !87, !88, !89, !90, !91, !92, !93, !94, !95, !96, !97, !98, !99, !100, !101, !102, !103, !104, !105, !106, !107, !108, !109, !110, !111, !112, !113, !114, !115, !116}
!40 = !DIEnumerator(name: "UV_E2BIG", value: -7)
!41 = !DIEnumerator(name: "UV_EACCES", value: -13)
!42 = !DIEnumerator(name: "UV_EADDRINUSE", value: -98)
!43 = !DIEnumerator(name: "UV_EADDRNOTAVAIL", value: -99)
!44 = !DIEnumerator(name: "UV_EAFNOSUPPORT", value: -97)
!45 = !DIEnumerator(name: "UV_EAGAIN", value: -11)
!46 = !DIEnumerator(name: "UV_EAI_ADDRFAMILY", value: -3000)
!47 = !DIEnumerator(name: "UV_EAI_AGAIN", value: -3001)
!48 = !DIEnumerator(name: "UV_EAI_BADFLAGS", value: -3002)
!49 = !DIEnumerator(name: "UV_EAI_BADHINTS", value: -3013)
!50 = !DIEnumerator(name: "UV_EAI_CANCELED", value: -3003)
!51 = !DIEnumerator(name: "UV_EAI_FAIL", value: -3004)
!52 = !DIEnumerator(name: "UV_EAI_FAMILY", value: -3005)
!53 = !DIEnumerator(name: "UV_EAI_MEMORY", value: -3006)
!54 = !DIEnumerator(name: "UV_EAI_NODATA", value: -3007)
!55 = !DIEnumerator(name: "UV_EAI_NONAME", value: -3008)
!56 = !DIEnumerator(name: "UV_EAI_OVERFLOW", value: -3009)
!57 = !DIEnumerator(name: "UV_EAI_PROTOCOL", value: -3014)
!58 = !DIEnumerator(name: "UV_EAI_SERVICE", value: -3010)
!59 = !DIEnumerator(name: "UV_EAI_SOCKTYPE", value: -3011)
!60 = !DIEnumerator(name: "UV_EALREADY", value: -114)
!61 = !DIEnumerator(name: "UV_EBADF", value: -9)
!62 = !DIEnumerator(name: "UV_EBUSY", value: -16)
!63 = !DIEnumerator(name: "UV_ECANCELED", value: -125)
!64 = !DIEnumerator(name: "UV_ECHARSET", value: -4080)
!65 = !DIEnumerator(name: "UV_ECONNABORTED", value: -103)
!66 = !DIEnumerator(name: "UV_ECONNREFUSED", value: -111)
!67 = !DIEnumerator(name: "UV_ECONNRESET", value: -104)
!68 = !DIEnumerator(name: "UV_EDESTADDRREQ", value: -89)
!69 = !DIEnumerator(name: "UV_EEXIST", value: -17)
!70 = !DIEnumerator(name: "UV_EFAULT", value: -14)
!71 = !DIEnumerator(name: "UV_EFBIG", value: -27)
!72 = !DIEnumerator(name: "UV_EHOSTUNREACH", value: -113)
!73 = !DIEnumerator(name: "UV_EINTR", value: -4)
!74 = !DIEnumerator(name: "UV_EINVAL", value: -22)
!75 = !DIEnumerator(name: "UV_EIO", value: -5)
!76 = !DIEnumerator(name: "UV_EISCONN", value: -106)
!77 = !DIEnumerator(name: "UV_EISDIR", value: -21)
!78 = !DIEnumerator(name: "UV_ELOOP", value: -40)
!79 = !DIEnumerator(name: "UV_EMFILE", value: -24)
!80 = !DIEnumerator(name: "UV_EMSGSIZE", value: -90)
!81 = !DIEnumerator(name: "UV_ENAMETOOLONG", value: -36)
!82 = !DIEnumerator(name: "UV_ENETDOWN", value: -100)
!83 = !DIEnumerator(name: "UV_ENETUNREACH", value: -101)
!84 = !DIEnumerator(name: "UV_ENFILE", value: -23)
!85 = !DIEnumerator(name: "UV_ENOBUFS", value: -105)
!86 = !DIEnumerator(name: "UV_ENODEV", value: -19)
!87 = !DIEnumerator(name: "UV_ENOENT", value: -2)
!88 = !DIEnumerator(name: "UV_ENOMEM", value: -12)
!89 = !DIEnumerator(name: "UV_ENONET", value: -64)
!90 = !DIEnumerator(name: "UV_ENOPROTOOPT", value: -92)
!91 = !DIEnumerator(name: "UV_ENOSPC", value: -28)
!92 = !DIEnumerator(name: "UV_ENOSYS", value: -38)
!93 = !DIEnumerator(name: "UV_ENOTCONN", value: -107)
!94 = !DIEnumerator(name: "UV_ENOTDIR", value: -20)
!95 = !DIEnumerator(name: "UV_ENOTEMPTY", value: -39)
!96 = !DIEnumerator(name: "UV_ENOTSOCK", value: -88)
!97 = !DIEnumerator(name: "UV_ENOTSUP", value: -95)
!98 = !DIEnumerator(name: "UV_EPERM", value: -1)
!99 = !DIEnumerator(name: "UV_EPIPE", value: -32)
!100 = !DIEnumerator(name: "UV_EPROTO", value: -71)
!101 = !DIEnumerator(name: "UV_EPROTONOSUPPORT", value: -93)
!102 = !DIEnumerator(name: "UV_EPROTOTYPE", value: -91)
!103 = !DIEnumerator(name: "UV_ERANGE", value: -34)
!104 = !DIEnumerator(name: "UV_EROFS", value: -30)
!105 = !DIEnumerator(name: "UV_ESHUTDOWN", value: -108)
!106 = !DIEnumerator(name: "UV_ESPIPE", value: -29)
!107 = !DIEnumerator(name: "UV_ESRCH", value: -3)
!108 = !DIEnumerator(name: "UV_ETIMEDOUT", value: -110)
!109 = !DIEnumerator(name: "UV_ETXTBSY", value: -26)
!110 = !DIEnumerator(name: "UV_EXDEV", value: -18)
!111 = !DIEnumerator(name: "UV_UNKNOWN", value: -4094)
!112 = !DIEnumerator(name: "UV_EOF", value: -4095)
!113 = !DIEnumerator(name: "UV_ENXIO", value: -6)
!114 = !DIEnumerator(name: "UV_EMLINK", value: -31)
!115 = !DIEnumerator(name: "UV_EHOSTDOWN", value: -112)
!116 = !DIEnumerator(name: "UV_ERRNO_MAX", value: -4096)
!117 = !{!118, !119, !134, !138, !391, !392, !400}
!118 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: null, size: 64, align: 64)
!119 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !120, size: 64, align: 64)
!120 = !DIDerivedType(tag: DW_TAG_typedef, name: "uv_req_t", file: !4, line: 223, baseType: !121)
!121 = !DICompositeType(tag: DW_TAG_structure_type, name: "uv_req_s", file: !4, line: 388, size: 512, align: 64, elements: !122)
!122 = !{!123, !124, !126, !130}
!123 = !DIDerivedType(tag: DW_TAG_member, name: "data", scope: !121, file: !4, line: 389, baseType: !118, size: 64, align: 64)
!124 = !DIDerivedType(tag: DW_TAG_member, name: "type", scope: !121, file: !4, line: 389, baseType: !125, size: 32, align: 32, offset: 64)
!125 = !DIDerivedType(tag: DW_TAG_typedef, name: "uv_req_type", file: !4, line: 200, baseType: !25)
!126 = !DIDerivedType(tag: DW_TAG_member, name: "active_queue", scope: !121, file: !4, line: 389, baseType: !127, size: 128, align: 64, offset: 128)
!127 = !DICompositeType(tag: DW_TAG_array_type, baseType: !118, size: 128, align: 64, elements: !128)
!128 = !{!129}
!129 = !DISubrange(count: 2)
!130 = !DIDerivedType(tag: DW_TAG_member, name: "reserved", scope: !121, file: !4, line: 389, baseType: !131, size: 256, align: 64, offset: 256)
!131 = !DICompositeType(tag: DW_TAG_array_type, baseType: !118, size: 256, align: 64, elements: !132)
!132 = !{!133}
!133 = !DISubrange(count: 4)
!134 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !135, size: 64, align: 64)
!135 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !136, size: 64, align: 64)
!136 = !DIDerivedType(tag: DW_TAG_typedef, name: "QUEUE", file: !137, line: 21, baseType: !127)
!137 = !DIFile(filename: "/data/download/cmake/cmake-master/Utilities/cmlibuv/src/queue.h", directory: "/data/download/cmake/cmake-master/Utilities/cmlibuv")
!138 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !139, size: 64, align: 64)
!139 = !DIDerivedType(tag: DW_TAG_typedef, name: "uv_getnameinfo_t", file: !4, line: 225, baseType: !140)
!140 = !DICompositeType(tag: DW_TAG_structure_type, name: "uv_getnameinfo_s", file: !4, line: 827, size: 10560, align: 64, elements: !141)
!141 = !{!142, !143, !144, !145, !146, !346, !361, !368, !381, !382, !386, !390}
!142 = !DIDerivedType(tag: DW_TAG_member, name: "data", scope: !140, file: !4, line: 828, baseType: !118, size: 64, align: 64)
!143 = !DIDerivedType(tag: DW_TAG_member, name: "type", scope: !140, file: !4, line: 828, baseType: !125, size: 32, align: 32, offset: 64)
!144 = !DIDerivedType(tag: DW_TAG_member, name: "active_queue", scope: !140, file: !4, line: 828, baseType: !127, size: 128, align: 64, offset: 128)
!145 = !DIDerivedType(tag: DW_TAG_member, name: "reserved", scope: !140, file: !4, line: 828, baseType: !131, size: 256, align: 64, offset: 256)
!146 = !DIDerivedType(tag: DW_TAG_member, name: "loop", scope: !140, file: !4, line: 830, baseType: !147, size: 64, align: 64, offset: 512)
!147 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !148, size: 64, align: 64)
!148 = !DIDerivedType(tag: DW_TAG_typedef, name: "uv_loop_t", file: !4, line: 204, baseType: !149)
!149 = !DICompositeType(tag: DW_TAG_structure_type, name: "uv_loop_s", file: !4, line: 1473, size: 6784, align: 64, elements: !150)
!150 = !{!151, !152, !154, !155, !156, !157, !159, !161, !162, !163, !182, !183, !184, !185, !216, !261, !285, !286, !287, !288, !289, !290, !291, !295, !296, !297, !302, !305, !306, !308, !309, !342, !343, !344, !345}
!151 = !DIDerivedType(tag: DW_TAG_member, name: "data", scope: !149, file: !4, line: 1475, baseType: !118, size: 64, align: 64)
!152 = !DIDerivedType(tag: DW_TAG_member, name: "active_handles", scope: !149, file: !4, line: 1477, baseType: !153, size: 32, align: 32, offset: 64)
!153 = !DIBasicType(name: "unsigned int", size: 32, align: 32, encoding: DW_ATE_unsigned)
!154 = !DIDerivedType(tag: DW_TAG_member, name: "handle_queue", scope: !149, file: !4, line: 1478, baseType: !127, size: 128, align: 64, offset: 128)
!155 = !DIDerivedType(tag: DW_TAG_member, name: "active_reqs", scope: !149, file: !4, line: 1479, baseType: !127, size: 128, align: 64, offset: 256)
!156 = !DIDerivedType(tag: DW_TAG_member, name: "stop_flag", scope: !149, file: !4, line: 1481, baseType: !153, size: 32, align: 32, offset: 384)
!157 = !DIDerivedType(tag: DW_TAG_member, name: "flags", scope: !149, file: !4, line: 1482, baseType: !158, size: 64, align: 64, offset: 448)
!158 = !DIBasicType(name: "long unsigned int", size: 64, align: 64, encoding: DW_ATE_unsigned)
!159 = !DIDerivedType(tag: DW_TAG_member, name: "backend_fd", scope: !149, file: !4, line: 1482, baseType: !160, size: 32, align: 32, offset: 512)
!160 = !DIBasicType(name: "int", size: 32, align: 32, encoding: DW_ATE_signed)
!161 = !DIDerivedType(tag: DW_TAG_member, name: "pending_queue", scope: !149, file: !4, line: 1482, baseType: !127, size: 128, align: 64, offset: 576)
!162 = !DIDerivedType(tag: DW_TAG_member, name: "watcher_queue", scope: !149, file: !4, line: 1482, baseType: !127, size: 128, align: 64, offset: 704)
!163 = !DIDerivedType(tag: DW_TAG_member, name: "watchers", scope: !149, file: !4, line: 1482, baseType: !164, size: 64, align: 64, offset: 832)
!164 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !165, size: 64, align: 64)
!165 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !166, size: 64, align: 64)
!166 = !DIDerivedType(tag: DW_TAG_typedef, name: "uv__io_t", file: !167, line: 87, baseType: !168)
!167 = !DIFile(filename: "/data/download/cmake/cmake-master/Utilities/cmlibuv/include/uv-unix.h", directory: "/data/download/cmake/cmake-master/Utilities/cmlibuv")
!168 = !DICompositeType(tag: DW_TAG_structure_type, name: "uv__io_s", file: !167, line: 89, size: 448, align: 64, elements: !169)
!169 = !{!170, !177, !178, !179, !180, !181}
!170 = !DIDerivedType(tag: DW_TAG_member, name: "cb", scope: !168, file: !167, line: 90, baseType: !171, size: 64, align: 64)
!171 = !DIDerivedType(tag: DW_TAG_typedef, name: "uv__io_cb", file: !167, line: 84, baseType: !172)
!172 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !173, size: 64, align: 64)
!173 = !DISubroutineType(types: !174)
!174 = !{null, !175, !176, !153}
!175 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !149, size: 64, align: 64)
!176 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !168, size: 64, align: 64)
!177 = !DIDerivedType(tag: DW_TAG_member, name: "pending_queue", scope: !168, file: !167, line: 91, baseType: !127, size: 128, align: 64, offset: 64)
!178 = !DIDerivedType(tag: DW_TAG_member, name: "watcher_queue", scope: !168, file: !167, line: 92, baseType: !127, size: 128, align: 64, offset: 192)
!179 = !DIDerivedType(tag: DW_TAG_member, name: "pevents", scope: !168, file: !167, line: 93, baseType: !153, size: 32, align: 32, offset: 320)
!180 = !DIDerivedType(tag: DW_TAG_member, name: "events", scope: !168, file: !167, line: 94, baseType: !153, size: 32, align: 32, offset: 352)
!181 = !DIDerivedType(tag: DW_TAG_member, name: "fd", scope: !168, file: !167, line: 95, baseType: !160, size: 32, align: 32, offset: 384)
!182 = !DIDerivedType(tag: DW_TAG_member, name: "nwatchers", scope: !149, file: !4, line: 1482, baseType: !153, size: 32, align: 32, offset: 896)
!183 = !DIDerivedType(tag: DW_TAG_member, name: "nfds", scope: !149, file: !4, line: 1482, baseType: !153, size: 32, align: 32, offset: 928)
!184 = !DIDerivedType(tag: DW_TAG_member, name: "wq", scope: !149, file: !4, line: 1482, baseType: !127, size: 128, align: 64, offset: 960)
!185 = !DIDerivedType(tag: DW_TAG_member, name: "wq_mutex", scope: !149, file: !4, line: 1482, baseType: !186, size: 320, align: 64, offset: 1088)
!186 = !DIDerivedType(tag: DW_TAG_typedef, name: "uv_mutex_t", file: !167, line: 129, baseType: !187)
!187 = !DIDerivedType(tag: DW_TAG_typedef, name: "pthread_mutex_t", file: !188, line: 127, baseType: !189)
!188 = !DIFile(filename: "/usr/include/x86_64-linux-gnu/bits/pthreadtypes.h", directory: "/data/download/cmake/cmake-master/Utilities/cmlibuv")
!189 = !DICompositeType(tag: DW_TAG_union_type, file: !188, line: 90, size: 320, align: 64, elements: !190)
!190 = !{!191, !209, !214}
!191 = !DIDerivedType(tag: DW_TAG_member, name: "__data", scope: !189, file: !188, line: 124, baseType: !192, size: 320, align: 64)
!192 = !DICompositeType(tag: DW_TAG_structure_type, name: "__pthread_mutex_s", file: !188, line: 92, size: 320, align: 64, elements: !193)
!193 = !{!194, !195, !196, !197, !198, !199, !201, !202}
!194 = !DIDerivedType(tag: DW_TAG_member, name: "__lock", scope: !192, file: !188, line: 94, baseType: !160, size: 32, align: 32)
!195 = !DIDerivedType(tag: DW_TAG_member, name: "__count", scope: !192, file: !188, line: 95, baseType: !153, size: 32, align: 32, offset: 32)
!196 = !DIDerivedType(tag: DW_TAG_member, name: "__owner", scope: !192, file: !188, line: 96, baseType: !160, size: 32, align: 32, offset: 64)
!197 = !DIDerivedType(tag: DW_TAG_member, name: "__nusers", scope: !192, file: !188, line: 98, baseType: !153, size: 32, align: 32, offset: 96)
!198 = !DIDerivedType(tag: DW_TAG_member, name: "__kind", scope: !192, file: !188, line: 102, baseType: !160, size: 32, align: 32, offset: 128)
!199 = !DIDerivedType(tag: DW_TAG_member, name: "__spins", scope: !192, file: !188, line: 104, baseType: !200, size: 16, align: 16, offset: 160)
!200 = !DIBasicType(name: "short", size: 16, align: 16, encoding: DW_ATE_signed)
!201 = !DIDerivedType(tag: DW_TAG_member, name: "__elision", scope: !192, file: !188, line: 105, baseType: !200, size: 16, align: 16, offset: 176)
!202 = !DIDerivedType(tag: DW_TAG_member, name: "__list", scope: !192, file: !188, line: 106, baseType: !203, size: 128, align: 64, offset: 192)
!203 = !DIDerivedType(tag: DW_TAG_typedef, name: "__pthread_list_t", file: !188, line: 79, baseType: !204)
!204 = !DICompositeType(tag: DW_TAG_structure_type, name: "__pthread_internal_list", file: !188, line: 75, size: 128, align: 64, elements: !205)
!205 = !{!206, !208}
!206 = !DIDerivedType(tag: DW_TAG_member, name: "__prev", scope: !204, file: !188, line: 77, baseType: !207, size: 64, align: 64)
!207 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !204, size: 64, align: 64)
!208 = !DIDerivedType(tag: DW_TAG_member, name: "__next", scope: !204, file: !188, line: 78, baseType: !207, size: 64, align: 64, offset: 64)
!209 = !DIDerivedType(tag: DW_TAG_member, name: "__size", scope: !189, file: !188, line: 125, baseType: !210, size: 320, align: 8)
!210 = !DICompositeType(tag: DW_TAG_array_type, baseType: !211, size: 320, align: 8, elements: !212)
!211 = !DIBasicType(name: "char", size: 8, align: 8, encoding: DW_ATE_signed_char)
!212 = !{!213}
!213 = !DISubrange(count: 40)
!214 = !DIDerivedType(tag: DW_TAG_member, name: "__align", scope: !189, file: !188, line: 126, baseType: !215, size: 64, align: 64)
!215 = !DIBasicType(name: "long int", size: 64, align: 64, encoding: DW_ATE_signed)
!216 = !DIDerivedType(tag: DW_TAG_member, name: "wq_async", scope: !149, file: !4, line: 1482, baseType: !217, size: 1024, align: 64, offset: 1408)
!217 = !DIDerivedType(tag: DW_TAG_typedef, name: "uv_async_t", file: !4, line: 216, baseType: !218)
!218 = !DICompositeType(tag: DW_TAG_structure_type, name: "uv_async_s", file: !4, line: 767, size: 1024, align: 64, elements: !219)
!219 = !{!220, !221, !222, !224, !245, !246, !251, !252, !253, !259, !260}
!220 = !DIDerivedType(tag: DW_TAG_member, name: "data", scope: !218, file: !4, line: 768, baseType: !118, size: 64, align: 64)
!221 = !DIDerivedType(tag: DW_TAG_member, name: "loop", scope: !218, file: !4, line: 768, baseType: !147, size: 64, align: 64, offset: 64)
!222 = !DIDerivedType(tag: DW_TAG_member, name: "type", scope: !218, file: !4, line: 768, baseType: !223, size: 32, align: 32, offset: 128)
!223 = !DIDerivedType(tag: DW_TAG_typedef, name: "uv_handle_type", file: !4, line: 191, baseType: !3)
!224 = !DIDerivedType(tag: DW_TAG_member, name: "close_cb", scope: !218, file: !4, line: 768, baseType: !225, size: 64, align: 64, offset: 192)
!225 = !DIDerivedType(tag: DW_TAG_typedef, name: "uv_close_cb", file: !4, line: 306, baseType: !226)
!226 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !227, size: 64, align: 64)
!227 = !DISubroutineType(types: !228)
!228 = !{null, !229}
!229 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !230, size: 64, align: 64)
!230 = !DIDerivedType(tag: DW_TAG_typedef, name: "uv_handle_t", file: !4, line: 205, baseType: !231)
!231 = !DICompositeType(tag: DW_TAG_structure_type, name: "uv_handle_s", file: !4, line: 425, size: 768, align: 64, elements: !232)
!232 = !{!233, !234, !235, !236, !237, !238, !243, !244}
!233 = !DIDerivedType(tag: DW_TAG_member, name: "data", scope: !231, file: !4, line: 426, baseType: !118, size: 64, align: 64)
!234 = !DIDerivedType(tag: DW_TAG_member, name: "loop", scope: !231, file: !4, line: 426, baseType: !147, size: 64, align: 64, offset: 64)
!235 = !DIDerivedType(tag: DW_TAG_member, name: "type", scope: !231, file: !4, line: 426, baseType: !223, size: 32, align: 32, offset: 128)
!236 = !DIDerivedType(tag: DW_TAG_member, name: "close_cb", scope: !231, file: !4, line: 426, baseType: !225, size: 64, align: 64, offset: 192)
!237 = !DIDerivedType(tag: DW_TAG_member, name: "handle_queue", scope: !231, file: !4, line: 426, baseType: !127, size: 128, align: 64, offset: 256)
!238 = !DIDerivedType(tag: DW_TAG_member, name: "u", scope: !231, file: !4, line: 426, baseType: !239, size: 256, align: 64, offset: 384)
!239 = !DICompositeType(tag: DW_TAG_union_type, scope: !231, file: !4, line: 426, size: 256, align: 64, elements: !240)
!240 = !{!241, !242}
!241 = !DIDerivedType(tag: DW_TAG_member, name: "fd", scope: !239, file: !4, line: 426, baseType: !160, size: 32, align: 32)
!242 = !DIDerivedType(tag: DW_TAG_member, name: "reserved", scope: !239, file: !4, line: 426, baseType: !131, size: 256, align: 64)
!243 = !DIDerivedType(tag: DW_TAG_member, name: "next_closing", scope: !231, file: !4, line: 426, baseType: !229, size: 64, align: 64, offset: 640)
!244 = !DIDerivedType(tag: DW_TAG_member, name: "flags", scope: !231, file: !4, line: 426, baseType: !153, size: 32, align: 32, offset: 704)
!245 = !DIDerivedType(tag: DW_TAG_member, name: "handle_queue", scope: !218, file: !4, line: 768, baseType: !127, size: 128, align: 64, offset: 256)
!246 = !DIDerivedType(tag: DW_TAG_member, name: "u", scope: !218, file: !4, line: 768, baseType: !247, size: 256, align: 64, offset: 384)
!247 = !DICompositeType(tag: DW_TAG_union_type, scope: !218, file: !4, line: 768, size: 256, align: 64, elements: !248)
!248 = !{!249, !250}
!249 = !DIDerivedType(tag: DW_TAG_member, name: "fd", scope: !247, file: !4, line: 768, baseType: !160, size: 32, align: 32)
!250 = !DIDerivedType(tag: DW_TAG_member, name: "reserved", scope: !247, file: !4, line: 768, baseType: !131, size: 256, align: 64)
!251 = !DIDerivedType(tag: DW_TAG_member, name: "next_closing", scope: !218, file: !4, line: 768, baseType: !229, size: 64, align: 64, offset: 640)
!252 = !DIDerivedType(tag: DW_TAG_member, name: "flags", scope: !218, file: !4, line: 768, baseType: !153, size: 32, align: 32, offset: 704)
!253 = !DIDerivedType(tag: DW_TAG_member, name: "async_cb", scope: !218, file: !4, line: 769, baseType: !254, size: 64, align: 64, offset: 768)
!254 = !DIDerivedType(tag: DW_TAG_typedef, name: "uv_async_cb", file: !4, line: 309, baseType: !255)
!255 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !256, size: 64, align: 64)
!256 = !DISubroutineType(types: !257)
!257 = !{null, !258}
!258 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !217, size: 64, align: 64)
!259 = !DIDerivedType(tag: DW_TAG_member, name: "queue", scope: !218, file: !4, line: 769, baseType: !127, size: 128, align: 64, offset: 832)
!260 = !DIDerivedType(tag: DW_TAG_member, name: "pending", scope: !218, file: !4, line: 769, baseType: !160, size: 32, align: 32, offset: 960)
!261 = !DIDerivedType(tag: DW_TAG_member, name: "cloexec_lock", scope: !149, file: !4, line: 1482, baseType: !262, size: 448, align: 64, offset: 2432)
!262 = !DIDerivedType(tag: DW_TAG_typedef, name: "uv_rwlock_t", file: !167, line: 130, baseType: !263)
!263 = !DIDerivedType(tag: DW_TAG_typedef, name: "pthread_rwlock_t", file: !188, line: 213, baseType: !264)
!264 = !DICompositeType(tag: DW_TAG_union_type, file: !188, line: 173, size: 448, align: 64, elements: !265)
!265 = !{!266, !280, !284}
!266 = !DIDerivedType(tag: DW_TAG_member, name: "__data", scope: !264, file: !188, line: 192, baseType: !267, size: 448, align: 64)
!267 = !DICompositeType(tag: DW_TAG_structure_type, scope: !264, file: !188, line: 176, size: 448, align: 64, elements: !268)
!268 = !{!269, !270, !271, !272, !273, !274, !275, !276, !277, !278, !279}
!269 = !DIDerivedType(tag: DW_TAG_member, name: "__lock", scope: !267, file: !188, line: 178, baseType: !160, size: 32, align: 32)
!270 = !DIDerivedType(tag: DW_TAG_member, name: "__nr_readers", scope: !267, file: !188, line: 179, baseType: !153, size: 32, align: 32, offset: 32)
!271 = !DIDerivedType(tag: DW_TAG_member, name: "__readers_wakeup", scope: !267, file: !188, line: 180, baseType: !153, size: 32, align: 32, offset: 64)
!272 = !DIDerivedType(tag: DW_TAG_member, name: "__writer_wakeup", scope: !267, file: !188, line: 181, baseType: !153, size: 32, align: 32, offset: 96)
!273 = !DIDerivedType(tag: DW_TAG_member, name: "__nr_readers_queued", scope: !267, file: !188, line: 182, baseType: !153, size: 32, align: 32, offset: 128)
!274 = !DIDerivedType(tag: DW_TAG_member, name: "__nr_writers_queued", scope: !267, file: !188, line: 183, baseType: !153, size: 32, align: 32, offset: 160)
!275 = !DIDerivedType(tag: DW_TAG_member, name: "__writer", scope: !267, file: !188, line: 184, baseType: !160, size: 32, align: 32, offset: 192)
!276 = !DIDerivedType(tag: DW_TAG_member, name: "__shared", scope: !267, file: !188, line: 185, baseType: !160, size: 32, align: 32, offset: 224)
!277 = !DIDerivedType(tag: DW_TAG_member, name: "__pad1", scope: !267, file: !188, line: 186, baseType: !158, size: 64, align: 64, offset: 256)
!278 = !DIDerivedType(tag: DW_TAG_member, name: "__pad2", scope: !267, file: !188, line: 187, baseType: !158, size: 64, align: 64, offset: 320)
!279 = !DIDerivedType(tag: DW_TAG_member, name: "__flags", scope: !267, file: !188, line: 190, baseType: !153, size: 32, align: 32, offset: 384)
!280 = !DIDerivedType(tag: DW_TAG_member, name: "__size", scope: !264, file: !188, line: 211, baseType: !281, size: 448, align: 8)
!281 = !DICompositeType(tag: DW_TAG_array_type, baseType: !211, size: 448, align: 8, elements: !282)
!282 = !{!283}
!283 = !DISubrange(count: 56)
!284 = !DIDerivedType(tag: DW_TAG_member, name: "__align", scope: !264, file: !188, line: 212, baseType: !215, size: 64, align: 64)
!285 = !DIDerivedType(tag: DW_TAG_member, name: "closing_handles", scope: !149, file: !4, line: 1482, baseType: !229, size: 64, align: 64, offset: 2880)
!286 = !DIDerivedType(tag: DW_TAG_member, name: "process_handles", scope: !149, file: !4, line: 1482, baseType: !127, size: 128, align: 64, offset: 2944)
!287 = !DIDerivedType(tag: DW_TAG_member, name: "prepare_handles", scope: !149, file: !4, line: 1482, baseType: !127, size: 128, align: 64, offset: 3072)
!288 = !DIDerivedType(tag: DW_TAG_member, name: "check_handles", scope: !149, file: !4, line: 1482, baseType: !127, size: 128, align: 64, offset: 3200)
!289 = !DIDerivedType(tag: DW_TAG_member, name: "idle_handles", scope: !149, file: !4, line: 1482, baseType: !127, size: 128, align: 64, offset: 3328)
!290 = !DIDerivedType(tag: DW_TAG_member, name: "async_handles", scope: !149, file: !4, line: 1482, baseType: !127, size: 128, align: 64, offset: 3456)
!291 = !DIDerivedType(tag: DW_TAG_member, name: "async_unused", scope: !149, file: !4, line: 1482, baseType: !292, size: 64, align: 64, offset: 3584)
!292 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !293, size: 64, align: 64)
!293 = !DISubroutineType(types: !294)
!294 = !{null}
!295 = !DIDerivedType(tag: DW_TAG_member, name: "async_io_watcher", scope: !149, file: !4, line: 1482, baseType: !166, size: 448, align: 64, offset: 3648)
!296 = !DIDerivedType(tag: DW_TAG_member, name: "async_wfd", scope: !149, file: !4, line: 1482, baseType: !160, size: 32, align: 32, offset: 4096)
!297 = !DIDerivedType(tag: DW_TAG_member, name: "timer_heap", scope: !149, file: !4, line: 1482, baseType: !298, size: 128, align: 64, offset: 4160)
!298 = !DICompositeType(tag: DW_TAG_structure_type, scope: !149, file: !4, line: 1482, size: 128, align: 64, elements: !299)
!299 = !{!300, !301}
!300 = !DIDerivedType(tag: DW_TAG_member, name: "min", scope: !298, file: !4, line: 1482, baseType: !118, size: 64, align: 64)
!301 = !DIDerivedType(tag: DW_TAG_member, name: "nelts", scope: !298, file: !4, line: 1482, baseType: !153, size: 32, align: 32, offset: 64)
!302 = !DIDerivedType(tag: DW_TAG_member, name: "timer_counter", scope: !149, file: !4, line: 1482, baseType: !303, size: 64, align: 64, offset: 4288)
!303 = !DIDerivedType(tag: DW_TAG_typedef, name: "uint64_t", file: !304, line: 55, baseType: !158)
!304 = !DIFile(filename: "/usr/include/stdint.h", directory: "/data/download/cmake/cmake-master/Utilities/cmlibuv")
!305 = !DIDerivedType(tag: DW_TAG_member, name: "time", scope: !149, file: !4, line: 1482, baseType: !303, size: 64, align: 64, offset: 4352)
!306 = !DIDerivedType(tag: DW_TAG_member, name: "signal_pipefd", scope: !149, file: !4, line: 1482, baseType: !307, size: 64, align: 32, offset: 4416)
!307 = !DICompositeType(tag: DW_TAG_array_type, baseType: !160, size: 64, align: 32, elements: !128)
!308 = !DIDerivedType(tag: DW_TAG_member, name: "signal_io_watcher", scope: !149, file: !4, line: 1482, baseType: !166, size: 448, align: 64, offset: 4480)
!309 = !DIDerivedType(tag: DW_TAG_member, name: "child_watcher", scope: !149, file: !4, line: 1482, baseType: !310, size: 1216, align: 64, offset: 4928)
!310 = !DIDerivedType(tag: DW_TAG_typedef, name: "uv_signal_t", file: !4, line: 220, baseType: !311)
!311 = !DICompositeType(tag: DW_TAG_structure_type, name: "uv_signal_s", file: !4, line: 1325, size: 1216, align: 64, elements: !312)
!312 = !{!313, !314, !315, !316, !317, !318, !323, !324, !325, !331, !332, !340, !341}
!313 = !DIDerivedType(tag: DW_TAG_member, name: "data", scope: !311, file: !4, line: 1326, baseType: !118, size: 64, align: 64)
!314 = !DIDerivedType(tag: DW_TAG_member, name: "loop", scope: !311, file: !4, line: 1326, baseType: !147, size: 64, align: 64, offset: 64)
!315 = !DIDerivedType(tag: DW_TAG_member, name: "type", scope: !311, file: !4, line: 1326, baseType: !223, size: 32, align: 32, offset: 128)
!316 = !DIDerivedType(tag: DW_TAG_member, name: "close_cb", scope: !311, file: !4, line: 1326, baseType: !225, size: 64, align: 64, offset: 192)
!317 = !DIDerivedType(tag: DW_TAG_member, name: "handle_queue", scope: !311, file: !4, line: 1326, baseType: !127, size: 128, align: 64, offset: 256)
!318 = !DIDerivedType(tag: DW_TAG_member, name: "u", scope: !311, file: !4, line: 1326, baseType: !319, size: 256, align: 64, offset: 384)
!319 = !DICompositeType(tag: DW_TAG_union_type, scope: !311, file: !4, line: 1326, size: 256, align: 64, elements: !320)
!320 = !{!321, !322}
!321 = !DIDerivedType(tag: DW_TAG_member, name: "fd", scope: !319, file: !4, line: 1326, baseType: !160, size: 32, align: 32)
!322 = !DIDerivedType(tag: DW_TAG_member, name: "reserved", scope: !319, file: !4, line: 1326, baseType: !131, size: 256, align: 64)
!323 = !DIDerivedType(tag: DW_TAG_member, name: "next_closing", scope: !311, file: !4, line: 1326, baseType: !229, size: 64, align: 64, offset: 640)
!324 = !DIDerivedType(tag: DW_TAG_member, name: "flags", scope: !311, file: !4, line: 1326, baseType: !153, size: 32, align: 32, offset: 704)
!325 = !DIDerivedType(tag: DW_TAG_member, name: "signal_cb", scope: !311, file: !4, line: 1327, baseType: !326, size: 64, align: 64, offset: 768)
!326 = !DIDerivedType(tag: DW_TAG_typedef, name: "uv_signal_cb", file: !4, line: 362, baseType: !327)
!327 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !328, size: 64, align: 64)
!328 = !DISubroutineType(types: !329)
!329 = !{null, !330, !160}
!330 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !310, size: 64, align: 64)
!331 = !DIDerivedType(tag: DW_TAG_member, name: "signum", scope: !311, file: !4, line: 1328, baseType: !160, size: 32, align: 32, offset: 832)
!332 = !DIDerivedType(tag: DW_TAG_member, name: "tree_entry", scope: !311, file: !4, line: 1329, baseType: !333, size: 256, align: 64, offset: 896)
!333 = !DICompositeType(tag: DW_TAG_structure_type, scope: !311, file: !4, line: 1329, size: 256, align: 64, elements: !334)
!334 = !{!335, !337, !338, !339}
!335 = !DIDerivedType(tag: DW_TAG_member, name: "rbe_left", scope: !333, file: !4, line: 1329, baseType: !336, size: 64, align: 64)
!336 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !311, size: 64, align: 64)
!337 = !DIDerivedType(tag: DW_TAG_member, name: "rbe_right", scope: !333, file: !4, line: 1329, baseType: !336, size: 64, align: 64, offset: 64)
!338 = !DIDerivedType(tag: DW_TAG_member, name: "rbe_parent", scope: !333, file: !4, line: 1329, baseType: !336, size: 64, align: 64, offset: 128)
!339 = !DIDerivedType(tag: DW_TAG_member, name: "rbe_color", scope: !333, file: !4, line: 1329, baseType: !160, size: 32, align: 32, offset: 192)
!340 = !DIDerivedType(tag: DW_TAG_member, name: "caught_signals", scope: !311, file: !4, line: 1329, baseType: !153, size: 32, align: 32, offset: 1152)
!341 = !DIDerivedType(tag: DW_TAG_member, name: "dispatched_signals", scope: !311, file: !4, line: 1329, baseType: !153, size: 32, align: 32, offset: 1184)
!342 = !DIDerivedType(tag: DW_TAG_member, name: "emfile_fd", scope: !149, file: !4, line: 1482, baseType: !160, size: 32, align: 32, offset: 6144)
!343 = !DIDerivedType(tag: DW_TAG_member, name: "inotify_read_watcher", scope: !149, file: !4, line: 1482, baseType: !166, size: 448, align: 64, offset: 6208)
!344 = !DIDerivedType(tag: DW_TAG_member, name: "inotify_watchers", scope: !149, file: !4, line: 1482, baseType: !118, size: 64, align: 64, offset: 6656)
!345 = !DIDerivedType(tag: DW_TAG_member, name: "inotify_fd", scope: !149, file: !4, line: 1482, baseType: !160, size: 32, align: 32, offset: 6720)
!346 = !DIDerivedType(tag: DW_TAG_member, name: "work_req", scope: !140, file: !4, line: 832, baseType: !347, size: 320, align: 64, offset: 576)
!347 = !DICompositeType(tag: DW_TAG_structure_type, name: "uv__work", file: !348, line: 30, size: 320, align: 64, elements: !349)
!348 = !DIFile(filename: "/data/download/cmake/cmake-master/Utilities/cmlibuv/include/uv-threadpool.h", directory: "/data/download/cmake/cmake-master/Utilities/cmlibuv")
!349 = !{!350, !355, !359, !360}
!350 = !DIDerivedType(tag: DW_TAG_member, name: "work", scope: !347, file: !348, line: 31, baseType: !351, size: 64, align: 64)
!351 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !352, size: 64, align: 64)
!352 = !DISubroutineType(types: !353)
!353 = !{null, !354}
!354 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !347, size: 64, align: 64)
!355 = !DIDerivedType(tag: DW_TAG_member, name: "done", scope: !347, file: !348, line: 32, baseType: !356, size: 64, align: 64, offset: 64)
!356 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !357, size: 64, align: 64)
!357 = !DISubroutineType(types: !358)
!358 = !{null, !354, !160}
!359 = !DIDerivedType(tag: DW_TAG_member, name: "loop", scope: !347, file: !348, line: 33, baseType: !175, size: 64, align: 64, offset: 128)
!360 = !DIDerivedType(tag: DW_TAG_member, name: "wq", scope: !347, file: !348, line: 34, baseType: !127, size: 128, align: 64, offset: 192)
!361 = !DIDerivedType(tag: DW_TAG_member, name: "getnameinfo_cb", scope: !140, file: !4, line: 832, baseType: !362, size: 64, align: 64, offset: 896)
!362 = !DIDerivedType(tag: DW_TAG_typedef, name: "uv_getnameinfo_cb", file: !4, line: 321, baseType: !363)
!363 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !364, size: 64, align: 64)
!364 = !DISubroutineType(types: !365)
!365 = !{null, !138, !160, !366, !366}
!366 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !367, size: 64, align: 64)
!367 = !DIDerivedType(tag: DW_TAG_const_type, baseType: !211)
!368 = !DIDerivedType(tag: DW_TAG_member, name: "storage", scope: !140, file: !4, line: 832, baseType: !369, size: 1024, align: 64, offset: 960)
!369 = !DICompositeType(tag: DW_TAG_structure_type, name: "sockaddr_storage", file: !370, line: 162, size: 1024, align: 64, elements: !371)
!370 = !DIFile(filename: "/usr/include/x86_64-linux-gnu/bits/socket.h", directory: "/data/download/cmake/cmake-master/Utilities/cmlibuv")
!371 = !{!372, !376, !377}
!372 = !DIDerivedType(tag: DW_TAG_member, name: "ss_family", scope: !369, file: !370, line: 164, baseType: !373, size: 16, align: 16)
!373 = !DIDerivedType(tag: DW_TAG_typedef, name: "sa_family_t", file: !374, line: 28, baseType: !375)
!374 = !DIFile(filename: "/usr/include/x86_64-linux-gnu/bits/sockaddr.h", directory: "/data/download/cmake/cmake-master/Utilities/cmlibuv")
!375 = !DIBasicType(name: "unsigned short", size: 16, align: 16, encoding: DW_ATE_unsigned)
!376 = !DIDerivedType(tag: DW_TAG_member, name: "__ss_align", scope: !369, file: !370, line: 165, baseType: !158, size: 64, align: 64, offset: 64)
!377 = !DIDerivedType(tag: DW_TAG_member, name: "__ss_padding", scope: !369, file: !370, line: 166, baseType: !378, size: 896, align: 8, offset: 128)
!378 = !DICompositeType(tag: DW_TAG_array_type, baseType: !211, size: 896, align: 8, elements: !379)
!379 = !{!380}
!380 = !DISubrange(count: 112)
!381 = !DIDerivedType(tag: DW_TAG_member, name: "flags", scope: !140, file: !4, line: 832, baseType: !160, size: 32, align: 32, offset: 1984)
!382 = !DIDerivedType(tag: DW_TAG_member, name: "host", scope: !140, file: !4, line: 832, baseType: !383, size: 8200, align: 8, offset: 2016)
!383 = !DICompositeType(tag: DW_TAG_array_type, baseType: !211, size: 8200, align: 8, elements: !384)
!384 = !{!385}
!385 = !DISubrange(count: 1025)
!386 = !DIDerivedType(tag: DW_TAG_member, name: "service", scope: !140, file: !4, line: 832, baseType: !387, size: 256, align: 8, offset: 10216)
!387 = !DICompositeType(tag: DW_TAG_array_type, baseType: !211, size: 256, align: 8, elements: !388)
!388 = !{!389}
!389 = !DISubrange(count: 32)
!390 = !DIDerivedType(tag: DW_TAG_member, name: "retcode", scope: !140, file: !4, line: 832, baseType: !160, size: 32, align: 32, offset: 10496)
!391 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !211, size: 64, align: 64)
!392 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !393, size: 64, align: 64)
!393 = !DICompositeType(tag: DW_TAG_structure_type, name: "sockaddr", file: !370, line: 149, size: 128, align: 16, elements: !394)
!394 = !{!395, !396}
!395 = !DIDerivedType(tag: DW_TAG_member, name: "sa_family", scope: !393, file: !370, line: 151, baseType: !373, size: 16, align: 16)
!396 = !DIDerivedType(tag: DW_TAG_member, name: "sa_data", scope: !393, file: !370, line: 152, baseType: !397, size: 112, align: 8, offset: 16)
!397 = !DICompositeType(tag: DW_TAG_array_type, baseType: !211, size: 112, align: 8, elements: !398)
!398 = !{!399}
!399 = !DISubrange(count: 14)
!400 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !401, size: 64, align: 64)
!401 = !DIDerivedType(tag: DW_TAG_const_type, baseType: !136)
!402 = !{!403, !409, !410}
!403 = distinct !DISubprogram(name: "uv_getnameinfo", scope: !1, file: !1, line: 81, type: !404, isLocal: false, isDefinition: true, scopeLine: 85, flags: DIFlagPrototyped, isOptimized: false, variables: !408)
!404 = !DISubroutineType(types: !405)
!405 = !{!160, !147, !138, !362, !406, !160}
!406 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !407, size: 64, align: 64)
!407 = !DIDerivedType(tag: DW_TAG_const_type, baseType: !393)
!408 = !{}
!409 = distinct !DISubprogram(name: "uv__getnameinfo_work", scope: !1, file: !1, line: 31, type: !352, isLocal: true, isDefinition: true, scopeLine: 31, flags: DIFlagPrototyped, isOptimized: false, variables: !408)
!410 = distinct !DISubprogram(name: "uv__getnameinfo_done", scope: !1, file: !1, line: 55, type: !357, isLocal: true, isDefinition: true, scopeLine: 55, flags: DIFlagPrototyped, isOptimized: false, variables: !408)
!411 = !{i32 2, !"Dwarf Version", i32 4}
!412 = !{i32 2, !"Debug Info Version", i32 3}
!413 = !{!"clang version 3.8.0 (tags/RELEASE_380/final)"}
!414 = !DILocalVariable(name: "loop", arg: 1, scope: !403, file: !1, line: 81, type: !147)
!415 = !DIExpression()
!416 = !DILocation(line: 81, column: 31, scope: !403)
!417 = !DILocalVariable(name: "req", arg: 2, scope: !403, file: !1, line: 82, type: !138)
!418 = !DILocation(line: 82, column: 38, scope: !403)
!419 = !DILocalVariable(name: "getnameinfo_cb", arg: 3, scope: !403, file: !1, line: 83, type: !362)
!420 = !DILocation(line: 83, column: 38, scope: !403)
!421 = !DILocalVariable(name: "addr", arg: 4, scope: !403, file: !1, line: 84, type: !406)
!422 = !DILocation(line: 84, column: 43, scope: !403)
!423 = !DILocalVariable(name: "flags", arg: 5, scope: !403, file: !1, line: 85, type: !160)
!424 = !DILocation(line: 85, column: 24, scope: !403)
!425 = !DILocation(line: 86, column: 7, scope: !426)
!426 = distinct !DILexicalBlock(scope: !403, file: !1, line: 86, column: 7)
!427 = !DILocation(line: 86, column: 11, scope: !426)
!428 = !DILocation(line: 86, column: 19, scope: !426)
!429 = !DILocation(line: 86, column: 22, scope: !430)
!430 = !DILexicalBlockFile(scope: !426, file: !1, discriminator: 1)
!431 = !DILocation(line: 86, column: 27, scope: !430)
!432 = !DILocation(line: 86, column: 7, scope: !430)
!433 = !DILocation(line: 87, column: 5, scope: !426)
!434 = !DILocation(line: 89, column: 7, scope: !435)
!435 = distinct !DILexicalBlock(scope: !403, file: !1, line: 89, column: 7)
!436 = !DILocation(line: 89, column: 13, scope: !435)
!437 = !DILocation(line: 89, column: 23, scope: !435)
!438 = !DILocation(line: 89, column: 7, scope: !403)
!439 = !DILocation(line: 90, column: 13, scope: !440)
!440 = distinct !DILexicalBlock(scope: !435, file: !1, line: 89, column: 35)
!441 = !DILocation(line: 90, column: 18, scope: !440)
!442 = !DILocation(line: 90, column: 5, scope: !440)
!443 = !DILocation(line: 91, column: 12, scope: !440)
!444 = !DILocation(line: 93, column: 3, scope: !440)
!445 = !DILocation(line: 93, column: 14, scope: !446)
!446 = !DILexicalBlockFile(scope: !447, file: !1, discriminator: 1)
!447 = distinct !DILexicalBlock(scope: !435, file: !1, line: 93, column: 14)
!448 = !DILocation(line: 93, column: 20, scope: !446)
!449 = !DILocation(line: 93, column: 30, scope: !446)
!450 = !DILocation(line: 94, column: 13, scope: !451)
!451 = distinct !DILexicalBlock(scope: !447, file: !1, line: 93, column: 43)
!452 = !DILocation(line: 94, column: 18, scope: !451)
!453 = !DILocation(line: 94, column: 5, scope: !451)
!454 = !DILocation(line: 95, column: 12, scope: !451)
!455 = !DILocation(line: 97, column: 3, scope: !451)
!456 = !DILocation(line: 98, column: 5, scope: !457)
!457 = distinct !DILexicalBlock(scope: !447, file: !1, line: 97, column: 10)
!458 = !DILocation(line: 101, column: 3, scope: !403)
!459 = !DILocation(line: 101, column: 3, scope: !460)
!460 = !DILexicalBlockFile(scope: !461, file: !1, discriminator: 1)
!461 = distinct !DILexicalBlock(scope: !403, file: !1, line: 101, column: 3)
!462 = !DILocation(line: 101, column: 3, scope: !463)
!463 = !DILexicalBlockFile(scope: !464, file: !1, discriminator: 2)
!464 = distinct !DILexicalBlock(scope: !461, file: !1, line: 101, column: 3)
!465 = !DILocation(line: 101, column: 3, scope: !466)
!466 = !DILexicalBlockFile(scope: !461, file: !1, discriminator: 3)
!467 = !DILocation(line: 101, column: 3, scope: !468)
!468 = !DILexicalBlockFile(scope: !469, file: !1, discriminator: 4)
!469 = distinct !DILexicalBlock(scope: !461, file: !1, line: 101, column: 3)
!470 = !DILocation(line: 101, column: 3, scope: !471)
!471 = !DILexicalBlockFile(scope: !472, file: !1, discriminator: 5)
!472 = distinct !DILexicalBlock(scope: !469, file: !1, line: 101, column: 3)
!473 = !DILocation(line: 101, column: 3, scope: !474)
!474 = !DILexicalBlockFile(scope: !469, file: !1, discriminator: 6)
!475 = !DILocation(line: 101, column: 3, scope: !476)
!476 = !DILexicalBlockFile(scope: !461, file: !1, discriminator: 7)
!477 = !DILocation(line: 103, column: 25, scope: !403)
!478 = !DILocation(line: 103, column: 3, scope: !403)
!479 = !DILocation(line: 103, column: 8, scope: !403)
!480 = !DILocation(line: 103, column: 23, scope: !403)
!481 = !DILocation(line: 104, column: 16, scope: !403)
!482 = !DILocation(line: 104, column: 3, scope: !403)
!483 = !DILocation(line: 104, column: 8, scope: !403)
!484 = !DILocation(line: 104, column: 14, scope: !403)
!485 = !DILocation(line: 105, column: 3, scope: !403)
!486 = !DILocation(line: 105, column: 8, scope: !403)
!487 = !DILocation(line: 105, column: 13, scope: !403)
!488 = !DILocation(line: 106, column: 15, scope: !403)
!489 = !DILocation(line: 106, column: 3, scope: !403)
!490 = !DILocation(line: 106, column: 8, scope: !403)
!491 = !DILocation(line: 106, column: 13, scope: !403)
!492 = !DILocation(line: 107, column: 3, scope: !403)
!493 = !DILocation(line: 107, column: 8, scope: !403)
!494 = !DILocation(line: 107, column: 16, scope: !403)
!495 = !DILocation(line: 109, column: 7, scope: !496)
!496 = distinct !DILexicalBlock(scope: !403, file: !1, line: 109, column: 7)
!497 = !DILocation(line: 109, column: 7, scope: !403)
!498 = !DILocation(line: 110, column: 21, scope: !499)
!499 = distinct !DILexicalBlock(scope: !496, file: !1, line: 109, column: 23)
!500 = !DILocation(line: 111, column: 22, scope: !499)
!501 = !DILocation(line: 111, column: 27, scope: !499)
!502 = !DILocation(line: 110, column: 5, scope: !499)
!503 = !DILocation(line: 114, column: 5, scope: !499)
!504 = !DILocation(line: 116, column: 27, scope: !505)
!505 = distinct !DILexicalBlock(scope: !496, file: !1, line: 115, column: 10)
!506 = !DILocation(line: 116, column: 32, scope: !505)
!507 = !DILocation(line: 116, column: 5, scope: !505)
!508 = !DILocation(line: 117, column: 27, scope: !505)
!509 = !DILocation(line: 117, column: 32, scope: !505)
!510 = !DILocation(line: 117, column: 5, scope: !505)
!511 = !DILocation(line: 118, column: 12, scope: !505)
!512 = !DILocation(line: 118, column: 17, scope: !505)
!513 = !DILocation(line: 118, column: 5, scope: !505)
!514 = !DILocation(line: 120, column: 1, scope: !403)
!515 = !DILocalVariable(name: "w", arg: 1, scope: !409, file: !1, line: 31, type: !354)
!516 = !DILocation(line: 31, column: 51, scope: !409)
!517 = !DILocalVariable(name: "req", scope: !409, file: !1, line: 32, type: !138)
!518 = !DILocation(line: 32, column: 21, scope: !409)
!519 = !DILocalVariable(name: "err", scope: !409, file: !1, line: 33, type: !160)
!520 = !DILocation(line: 33, column: 7, scope: !409)
!521 = !DILocalVariable(name: "salen", scope: !409, file: !1, line: 34, type: !522)
!522 = !DIDerivedType(tag: DW_TAG_typedef, name: "socklen_t", file: !370, line: 33, baseType: !523)
!523 = !DIDerivedType(tag: DW_TAG_typedef, name: "__socklen_t", file: !524, line: 189, baseType: !153)
!524 = !DIFile(filename: "/usr/include/x86_64-linux-gnu/bits/types.h", directory: "/data/download/cmake/cmake-master/Utilities/cmlibuv")
!525 = !DILocation(line: 34, column: 13, scope: !409)
!526 = !DILocation(line: 36, column: 9, scope: !409)
!527 = !DILocation(line: 36, column: 7, scope: !409)
!528 = !DILocation(line: 38, column: 7, scope: !529)
!529 = distinct !DILexicalBlock(scope: !409, file: !1, line: 38, column: 7)
!530 = !DILocation(line: 38, column: 12, scope: !529)
!531 = !DILocation(line: 38, column: 20, scope: !529)
!532 = !DILocation(line: 38, column: 30, scope: !529)
!533 = !DILocation(line: 38, column: 7, scope: !409)
!534 = !DILocation(line: 39, column: 11, scope: !529)
!535 = !DILocation(line: 39, column: 5, scope: !529)
!536 = !DILocation(line: 40, column: 12, scope: !537)
!537 = distinct !DILexicalBlock(scope: !529, file: !1, line: 40, column: 12)
!538 = !DILocation(line: 40, column: 17, scope: !537)
!539 = !DILocation(line: 40, column: 25, scope: !537)
!540 = !DILocation(line: 40, column: 35, scope: !537)
!541 = !DILocation(line: 40, column: 12, scope: !529)
!542 = !DILocation(line: 41, column: 11, scope: !537)
!543 = !DILocation(line: 41, column: 5, scope: !537)
!544 = !DILocation(line: 43, column: 5, scope: !537)
!545 = !DILocation(line: 45, column: 41, scope: !409)
!546 = !DILocation(line: 45, column: 46, scope: !409)
!547 = !DILocation(line: 45, column: 21, scope: !409)
!548 = !DILocation(line: 46, column: 21, scope: !409)
!549 = !DILocation(line: 47, column: 21, scope: !409)
!550 = !DILocation(line: 47, column: 26, scope: !409)
!551 = !DILocation(line: 49, column: 21, scope: !409)
!552 = !DILocation(line: 49, column: 26, scope: !409)
!553 = !DILocation(line: 51, column: 21, scope: !409)
!554 = !DILocation(line: 51, column: 26, scope: !409)
!555 = !DILocation(line: 45, column: 9, scope: !409)
!556 = !DILocation(line: 45, column: 7, scope: !409)
!557 = !DILocation(line: 52, column: 50, scope: !409)
!558 = !DILocation(line: 52, column: 18, scope: !409)
!559 = !DILocation(line: 52, column: 3, scope: !409)
!560 = !DILocation(line: 52, column: 8, scope: !409)
!561 = !DILocation(line: 52, column: 16, scope: !409)
!562 = !DILocation(line: 53, column: 1, scope: !409)
!563 = !DILocalVariable(name: "w", arg: 1, scope: !410, file: !1, line: 55, type: !354)
!564 = !DILocation(line: 55, column: 51, scope: !410)
!565 = !DILocalVariable(name: "status", arg: 2, scope: !410, file: !1, line: 55, type: !160)
!566 = !DILocation(line: 55, column: 58, scope: !410)
!567 = !DILocalVariable(name: "req", scope: !410, file: !1, line: 56, type: !138)
!568 = !DILocation(line: 56, column: 21, scope: !410)
!569 = !DILocalVariable(name: "host", scope: !410, file: !1, line: 57, type: !391)
!570 = !DILocation(line: 57, column: 9, scope: !410)
!571 = !DILocalVariable(name: "service", scope: !410, file: !1, line: 58, type: !391)
!572 = !DILocation(line: 58, column: 9, scope: !410)
!573 = !DILocation(line: 60, column: 9, scope: !410)
!574 = !DILocation(line: 60, column: 7, scope: !410)
!575 = !DILocation(line: 61, column: 3, scope: !410)
!576 = !DILocation(line: 61, column: 3, scope: !577)
!577 = !DILexicalBlockFile(scope: !578, file: !1, discriminator: 1)
!578 = distinct !DILexicalBlock(scope: !410, file: !1, line: 61, column: 3)
!579 = !DILocation(line: 61, column: 3, scope: !580)
!580 = !DILexicalBlockFile(scope: !578, file: !1, discriminator: 2)
!581 = !DILocation(line: 61, column: 3, scope: !582)
!582 = !DILexicalBlockFile(scope: !578, file: !1, discriminator: 3)
!583 = !DILocation(line: 61, column: 3, scope: !584)
!584 = !DILexicalBlockFile(scope: !578, file: !1, discriminator: 4)
!585 = !DILocation(line: 61, column: 3, scope: !586)
!586 = !DILexicalBlockFile(scope: !578, file: !1, discriminator: 5)
!587 = !DILocation(line: 61, column: 3, scope: !588)
!588 = !DILexicalBlockFile(scope: !589, file: !1, discriminator: 6)
!589 = distinct !DILexicalBlock(scope: !578, file: !1, line: 61, column: 3)
!590 = !DILocation(line: 61, column: 3, scope: !591)
!591 = !DILexicalBlockFile(scope: !578, file: !1, discriminator: 7)
!592 = !DILocation(line: 62, column: 18, scope: !410)
!593 = !DILocation(line: 62, column: 8, scope: !410)
!594 = !DILocation(line: 64, column: 7, scope: !595)
!595 = distinct !DILexicalBlock(scope: !410, file: !1, line: 64, column: 7)
!596 = !DILocation(line: 64, column: 14, scope: !595)
!597 = !DILocation(line: 64, column: 7, scope: !410)
!598 = !DILocation(line: 65, column: 5, scope: !599)
!599 = distinct !DILexicalBlock(scope: !595, file: !1, line: 64, column: 29)
!600 = !DILocation(line: 65, column: 5, scope: !601)
!601 = !DILexicalBlockFile(scope: !599, file: !1, discriminator: 1)
!602 = !DILocation(line: 65, column: 5, scope: !603)
!603 = !DILexicalBlockFile(scope: !599, file: !1, discriminator: 2)
!604 = !DILocation(line: 65, column: 5, scope: !605)
!605 = !DILexicalBlockFile(scope: !599, file: !1, discriminator: 3)
!606 = !DILocation(line: 66, column: 5, scope: !599)
!607 = !DILocation(line: 66, column: 10, scope: !599)
!608 = !DILocation(line: 66, column: 18, scope: !599)
!609 = !DILocation(line: 67, column: 3, scope: !599)
!610 = !DILocation(line: 67, column: 14, scope: !611)
!611 = !DILexicalBlockFile(scope: !612, file: !1, discriminator: 1)
!612 = distinct !DILexicalBlock(scope: !595, file: !1, line: 67, column: 14)
!613 = !DILocation(line: 67, column: 19, scope: !611)
!614 = !DILocation(line: 67, column: 27, scope: !611)
!615 = !DILocation(line: 68, column: 12, scope: !616)
!616 = distinct !DILexicalBlock(scope: !612, file: !1, line: 67, column: 33)
!617 = !DILocation(line: 68, column: 17, scope: !616)
!618 = !DILocation(line: 68, column: 10, scope: !616)
!619 = !DILocation(line: 69, column: 15, scope: !616)
!620 = !DILocation(line: 69, column: 20, scope: !616)
!621 = !DILocation(line: 69, column: 13, scope: !616)
!622 = !DILocation(line: 70, column: 3, scope: !616)
!623 = !DILocation(line: 72, column: 7, scope: !624)
!624 = distinct !DILexicalBlock(scope: !410, file: !1, line: 72, column: 7)
!625 = !DILocation(line: 72, column: 12, scope: !624)
!626 = !DILocation(line: 72, column: 7, scope: !410)
!627 = !DILocation(line: 73, column: 5, scope: !624)
!628 = !DILocation(line: 73, column: 10, scope: !624)
!629 = !DILocation(line: 73, column: 25, scope: !624)
!630 = !DILocation(line: 73, column: 30, scope: !624)
!631 = !DILocation(line: 73, column: 35, scope: !624)
!632 = !DILocation(line: 73, column: 44, scope: !624)
!633 = !DILocation(line: 73, column: 50, scope: !624)
!634 = !DILocation(line: 74, column: 1, scope: !410)
