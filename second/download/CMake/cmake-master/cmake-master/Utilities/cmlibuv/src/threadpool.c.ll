; ModuleID = '/data/download/cmake/cmake-master/Utilities/cmlibuv/src/threadpool.c'
target datalayout = "e-m:e-i64:64-f80:128-n8:16:32:64-S128"
target triple = "x86_64-unknown-linux-gnu"

%union.pthread_mutex_t = type { %struct.__pthread_mutex_s }
%struct.__pthread_mutex_s = type { i32, i32, i32, i32, i32, i16, i16, %struct.__pthread_internal_list }
%struct.__pthread_internal_list = type { %struct.__pthread_internal_list*, %struct.__pthread_internal_list* }
%union.pthread_cond_t = type { %struct.anon }
%struct.anon = type { i32, i32, i64, i64, i64, i8*, i32, i32 }
%struct.uv_loop_s = type { i8*, i32, [2 x i8*], [2 x i8*], i32, i64, i32, [2 x i8*], [2 x i8*], %struct.uv__io_s**, i32, i32, [2 x i8*], %union.pthread_mutex_t, %struct.uv_async_s, %union.pthread_rwlock_t, %struct.uv_handle_s*, [2 x i8*], [2 x i8*], [2 x i8*], [2 x i8*], [2 x i8*], void ()*, %struct.uv__io_s, i32, %struct.anon.2, i64, i64, [2 x i32], %struct.uv__io_s, %struct.uv_signal_s, i32, %struct.uv__io_s, i8*, i32 }
%struct.uv_async_s = type { i8*, %struct.uv_loop_s*, i32, void (%struct.uv_handle_s*)*, [2 x i8*], %union.anon.0, %struct.uv_handle_s*, i32, void (%struct.uv_async_s*)*, [2 x i8*], i32 }
%union.anon.0 = type { [4 x i8*] }
%union.pthread_rwlock_t = type { %struct.anon.1 }
%struct.anon.1 = type { i32, i32, i32, i32, i32, i32, i32, i32, i64, i64, i32 }
%struct.uv_handle_s = type { i8*, %struct.uv_loop_s*, i32, {}*, [2 x i8*], %union.anon, %struct.uv_handle_s*, i32 }
%union.anon = type { [4 x i8*] }
%struct.anon.2 = type { i8*, i32 }
%struct.uv_signal_s = type { i8*, %struct.uv_loop_s*, i32, void (%struct.uv_handle_s*)*, [2 x i8*], %union.anon.3, %struct.uv_handle_s*, i32, void (%struct.uv_signal_s*, i32)*, i32, %struct.anon.4, i32, i32 }
%union.anon.3 = type { [4 x i8*] }
%struct.anon.4 = type { %struct.uv_signal_s*, %struct.uv_signal_s*, %struct.uv_signal_s*, i32 }
%struct.uv__io_s = type { void (%struct.uv_loop_s*, %struct.uv__io_s*, i32)*, [2 x i8*], [2 x i8*], i32, i32, i32 }
%struct.uv__work = type { void (%struct.uv__work*)*, void (%struct.uv__work*, i32)*, %struct.uv_loop_s*, [2 x i8*] }
%struct.uv_work_s = type { i8*, i32, [2 x i8*], [4 x i8*], %struct.uv_loop_s*, void (%struct.uv_work_s*)*, void (%struct.uv_work_s*, i32)*, %struct.uv__work }
%struct.uv_req_s = type { i8*, i32, [2 x i8*], [4 x i8*] }
%struct.uv_fs_s = type { i8*, i32, [2 x i8*], [4 x i8*], i32, %struct.uv_loop_s*, void (%struct.uv_fs_s*)*, i64, i8*, i8*, %struct.uv_stat_t, i8*, i32, i32, i32, i32, %struct.uv_buf_t*, i64, i32, i32, double, double, %struct.uv__work, [4 x %struct.uv_buf_t] }
%struct.uv_stat_t = type { i64, i64, i64, i64, i64, i64, i64, i64, i64, i64, i64, i64, %struct.uv_timespec_t, %struct.uv_timespec_t, %struct.uv_timespec_t, %struct.uv_timespec_t }
%struct.uv_timespec_t = type { i64, i64 }
%struct.uv_buf_t = type { i8*, i64 }
%struct.uv_getaddrinfo_s = type { i8*, i32, [2 x i8*], [4 x i8*], %struct.uv_loop_s*, %struct.uv__work, void (%struct.uv_getaddrinfo_s*, i32, %struct.addrinfo*)*, %struct.addrinfo*, i8*, i8*, %struct.addrinfo*, i32 }
%struct.addrinfo = type { i32, i32, i32, i32, i32, %struct.sockaddr*, i8*, %struct.addrinfo* }
%struct.sockaddr = type { i16, [14 x i8] }
%struct.uv_getnameinfo_s = type { i8*, i32, [2 x i8*], [4 x i8*], %struct.uv_loop_s*, %struct.uv__work, void (%struct.uv_getnameinfo_s*, i32, i8*, i8*)*, %struct.sockaddr_storage, i32, [1025 x i8], [32 x i8], i32 }
%struct.sockaddr_storage = type { i16, i64, [112 x i8] }

@initialized = internal global i32 0, align 4
@exit_message = internal global [2 x i8*] zeroinitializer, align 16
@nthreads = internal global i32 0, align 4
@threads = internal global i64* null, align 8
@default_threads = internal global [4 x i64] zeroinitializer, align 16
@mutex = internal global %union.pthread_mutex_t zeroinitializer, align 8
@cond = internal global %union.pthread_cond_t zeroinitializer, align 8
@once = internal global i32 0, align 4
@wq = internal global [2 x i8*] zeroinitializer, align 16
@idle_threads = internal global i32 0, align 4
@.str = private unnamed_addr constant [19 x i8] c"UV_THREADPOOL_SIZE\00", align 1
@.str.1 = private unnamed_addr constant [123 x i8] c"(((const QUEUE *) (&(req->loop)->active_reqs) == (const QUEUE *) (*(QUEUE **) &((*(&(req->loop)->active_reqs))[0]))) == 0)\00", align 1
@.str.2 = private unnamed_addr constant [69 x i8] c"/data/download/cmake/cmake-master/Utilities/cmlibuv/src/threadpool.c\00", align 1
@__PRETTY_FUNCTION__.uv__queue_done = private unnamed_addr constant [44 x i8] c"void uv__queue_done(struct uv__work *, int)\00", align 1
@llvm.global_dtors = appending global [1 x { i32, void ()*, i8* }] [{ i32, void ()*, i8* } { i32 65535, void ()* @cleanup, i8* null }]

; Function Attrs: nounwind uwtable
define internal void @cleanup() #0 !dbg !564 {
entry:
  %i = alloca i32, align 4
  call void @llvm.dbg.declare(metadata i32* %i, metadata !642, metadata !643), !dbg !644
  %0 = load volatile i32, i32* @initialized, align 4, !dbg !645
  %cmp = icmp eq i32 %0, 0, !dbg !647
  br i1 %cmp, label %if.then, label %if.end, !dbg !648

if.then:                                          ; preds = %entry
  br label %return, !dbg !649

if.end:                                           ; preds = %entry
  call void @post([2 x i8*]* @exit_message), !dbg !650
  store i32 0, i32* %i, align 4, !dbg !651
  br label %for.cond, !dbg !653

for.cond:                                         ; preds = %for.inc, %if.end
  %1 = load i32, i32* %i, align 4, !dbg !654
  %2 = load i32, i32* @nthreads, align 4, !dbg !657
  %cmp1 = icmp ult i32 %1, %2, !dbg !658
  br i1 %cmp1, label %for.body, label %for.end, !dbg !659

for.body:                                         ; preds = %for.cond
  %3 = load i64*, i64** @threads, align 8, !dbg !660
  %4 = load i32, i32* %i, align 4, !dbg !662
  %idx.ext = zext i32 %4 to i64, !dbg !663
  %add.ptr = getelementptr inbounds i64, i64* %3, i64 %idx.ext, !dbg !663
  %call = call i32 @uv_thread_join(i64* %add.ptr), !dbg !664
  %tobool = icmp ne i32 %call, 0, !dbg !664
  br i1 %tobool, label %if.then2, label %if.end3, !dbg !665

if.then2:                                         ; preds = %for.body
  call void @abort() #7, !dbg !666
  unreachable, !dbg !666

if.end3:                                          ; preds = %for.body
  br label %for.inc, !dbg !667

for.inc:                                          ; preds = %if.end3
  %5 = load i32, i32* %i, align 4, !dbg !669
  %inc = add i32 %5, 1, !dbg !669
  store i32 %inc, i32* %i, align 4, !dbg !669
  br label %for.cond, !dbg !671

for.end:                                          ; preds = %for.cond
  %6 = load i64*, i64** @threads, align 8, !dbg !672
  %cmp4 = icmp ne i64* %6, getelementptr inbounds ([4 x i64], [4 x i64]* @default_threads, i32 0, i32 0), !dbg !674
  br i1 %cmp4, label %if.then5, label %if.end6, !dbg !675

if.then5:                                         ; preds = %for.end
  %7 = load i64*, i64** @threads, align 8, !dbg !676
  %8 = bitcast i64* %7 to i8*, !dbg !676
  call void @uv__free(i8* %8), !dbg !677
  br label %if.end6, !dbg !677

if.end6:                                          ; preds = %if.then5, %for.end
  call void @uv_mutex_destroy(%union.pthread_mutex_t* @mutex), !dbg !678
  call void @uv_cond_destroy(%union.pthread_cond_t* @cond), !dbg !679
  store i64* null, i64** @threads, align 8, !dbg !680
  store i32 0, i32* @nthreads, align 4, !dbg !681
  store volatile i32 0, i32* @initialized, align 4, !dbg !682
  br label %return, !dbg !683

return:                                           ; preds = %if.end6, %if.then
  ret void, !dbg !684
}

; Function Attrs: nounwind readnone
declare void @llvm.dbg.declare(metadata, metadata, metadata) #1

; Function Attrs: nounwind uwtable
define internal void @post([2 x i8*]* %q) #0 !dbg !584 {
entry:
  %q.addr = alloca [2 x i8*]*, align 8
  store [2 x i8*]* %q, [2 x i8*]** %q.addr, align 8
  call void @llvm.dbg.declare(metadata [2 x i8*]** %q.addr, metadata !686, metadata !643), !dbg !687
  call void @uv_mutex_lock(%union.pthread_mutex_t* @mutex), !dbg !688
  br label %do.body, !dbg !689

do.body:                                          ; preds = %entry
  %0 = load [2 x i8*]*, [2 x i8*]** %q.addr, align 8, !dbg !690
  %arrayidx = getelementptr inbounds [2 x i8*], [2 x i8*]* %0, i64 0, i64 0, !dbg !690
  %1 = bitcast i8** %arrayidx to [2 x i8*]**, !dbg !690
  store [2 x i8*]* @wq, [2 x i8*]** %1, align 8, !dbg !690
  %2 = load [2 x i8*]*, [2 x i8*]** bitcast (i8** getelementptr inbounds ([2 x i8*], [2 x i8*]* @wq, i64 0, i64 1) to [2 x i8*]**), align 8, !dbg !690
  %3 = load [2 x i8*]*, [2 x i8*]** %q.addr, align 8, !dbg !690
  %arrayidx1 = getelementptr inbounds [2 x i8*], [2 x i8*]* %3, i64 0, i64 1, !dbg !690
  %4 = bitcast i8** %arrayidx1 to [2 x i8*]**, !dbg !690
  store [2 x i8*]* %2, [2 x i8*]** %4, align 8, !dbg !690
  %5 = load [2 x i8*]*, [2 x i8*]** %q.addr, align 8, !dbg !690
  %6 = load [2 x i8*]*, [2 x i8*]** %q.addr, align 8, !dbg !690
  %arrayidx2 = getelementptr inbounds [2 x i8*], [2 x i8*]* %6, i64 0, i64 1, !dbg !690
  %7 = bitcast i8** %arrayidx2 to [2 x i8*]**, !dbg !690
  %8 = load [2 x i8*]*, [2 x i8*]** %7, align 8, !dbg !690
  %arrayidx3 = getelementptr inbounds [2 x i8*], [2 x i8*]* %8, i64 0, i64 0, !dbg !690
  %9 = bitcast i8** %arrayidx3 to [2 x i8*]**, !dbg !690
  store [2 x i8*]* %5, [2 x i8*]** %9, align 8, !dbg !690
  %10 = load [2 x i8*]*, [2 x i8*]** %q.addr, align 8, !dbg !690
  store [2 x i8*]* %10, [2 x i8*]** bitcast (i8** getelementptr inbounds ([2 x i8*], [2 x i8*]* @wq, i64 0, i64 1) to [2 x i8*]**), align 8, !dbg !690
  br label %do.end, !dbg !690

do.end:                                           ; preds = %do.body
  %11 = load i32, i32* @idle_threads, align 4, !dbg !693
  %cmp = icmp ugt i32 %11, 0, !dbg !695
  br i1 %cmp, label %if.then, label %if.end, !dbg !696

if.then:                                          ; preds = %do.end
  call void @uv_cond_signal(%union.pthread_cond_t* @cond), !dbg !697
  br label %if.end, !dbg !697

if.end:                                           ; preds = %if.then, %do.end
  call void @uv_mutex_unlock(%union.pthread_mutex_t* @mutex), !dbg !698
  ret void, !dbg !699
}

declare i32 @uv_thread_join(i64*) #2

; Function Attrs: noreturn nounwind
declare void @abort() #3

declare void @uv__free(i8*) #2

declare void @uv_mutex_destroy(%union.pthread_mutex_t*) #2

declare void @uv_cond_destroy(%union.pthread_cond_t*) #2

; Function Attrs: nounwind uwtable
define void @uv__work_submit(%struct.uv_loop_s* %loop, %struct.uv__work* %w, void (%struct.uv__work*)* %work, void (%struct.uv__work*, i32)* %done) #0 !dbg !566 {
entry:
  %loop.addr = alloca %struct.uv_loop_s*, align 8
  %w.addr = alloca %struct.uv__work*, align 8
  %work.addr = alloca void (%struct.uv__work*)*, align 8
  %done.addr = alloca void (%struct.uv__work*, i32)*, align 8
  store %struct.uv_loop_s* %loop, %struct.uv_loop_s** %loop.addr, align 8
  call void @llvm.dbg.declare(metadata %struct.uv_loop_s** %loop.addr, metadata !700, metadata !643), !dbg !701
  store %struct.uv__work* %w, %struct.uv__work** %w.addr, align 8
  call void @llvm.dbg.declare(metadata %struct.uv__work** %w.addr, metadata !702, metadata !643), !dbg !703
  store void (%struct.uv__work*)* %work, void (%struct.uv__work*)** %work.addr, align 8
  call void @llvm.dbg.declare(metadata void (%struct.uv__work*)** %work.addr, metadata !704, metadata !643), !dbg !705
  store void (%struct.uv__work*, i32)* %done, void (%struct.uv__work*, i32)** %done.addr, align 8
  call void @llvm.dbg.declare(metadata void (%struct.uv__work*, i32)** %done.addr, metadata !706, metadata !643), !dbg !707
  call void @uv_once(i32* @once, void ()* @init_once), !dbg !708
  %0 = load %struct.uv_loop_s*, %struct.uv_loop_s** %loop.addr, align 8, !dbg !709
  %1 = load %struct.uv__work*, %struct.uv__work** %w.addr, align 8, !dbg !710
  %loop1 = getelementptr inbounds %struct.uv__work, %struct.uv__work* %1, i32 0, i32 2, !dbg !711
  store %struct.uv_loop_s* %0, %struct.uv_loop_s** %loop1, align 8, !dbg !712
  %2 = load void (%struct.uv__work*)*, void (%struct.uv__work*)** %work.addr, align 8, !dbg !713
  %3 = load %struct.uv__work*, %struct.uv__work** %w.addr, align 8, !dbg !714
  %work2 = getelementptr inbounds %struct.uv__work, %struct.uv__work* %3, i32 0, i32 0, !dbg !715
  store void (%struct.uv__work*)* %2, void (%struct.uv__work*)** %work2, align 8, !dbg !716
  %4 = load void (%struct.uv__work*, i32)*, void (%struct.uv__work*, i32)** %done.addr, align 8, !dbg !717
  %5 = load %struct.uv__work*, %struct.uv__work** %w.addr, align 8, !dbg !718
  %done3 = getelementptr inbounds %struct.uv__work, %struct.uv__work* %5, i32 0, i32 1, !dbg !719
  store void (%struct.uv__work*, i32)* %4, void (%struct.uv__work*, i32)** %done3, align 8, !dbg !720
  %6 = load %struct.uv__work*, %struct.uv__work** %w.addr, align 8, !dbg !721
  %wq = getelementptr inbounds %struct.uv__work, %struct.uv__work* %6, i32 0, i32 3, !dbg !722
  call void @post([2 x i8*]* %wq), !dbg !723
  ret void, !dbg !724
}

declare void @uv_once(i32*, void ()*) #2

; Function Attrs: nounwind uwtable
define internal void @init_once() #0 !dbg !587 {
entry:
  %call = call i32 @pthread_atfork(void ()* null, void ()* null, void ()* @reset_once) #8, !dbg !725
  %tobool = icmp ne i32 %call, 0, !dbg !725
  br i1 %tobool, label %if.then, label %if.end, !dbg !727

if.then:                                          ; preds = %entry
  call void @abort() #7, !dbg !728
  unreachable, !dbg !728

if.end:                                           ; preds = %entry
  call void @init_threads(), !dbg !729
  ret void, !dbg !730
}

; Function Attrs: nounwind uwtable
define void @uv__work_done(%struct.uv_async_s* %handle) #0 !dbg !569 {
entry:
  %handle.addr = alloca %struct.uv_async_s*, align 8
  %w = alloca %struct.uv__work*, align 8
  %loop = alloca %struct.uv_loop_s*, align 8
  %q = alloca [2 x i8*]*, align 8
  %wq = alloca [2 x i8*], align 16
  %err = alloca i32, align 4
  %q6 = alloca [2 x i8*]*, align 8
  store %struct.uv_async_s* %handle, %struct.uv_async_s** %handle.addr, align 8
  call void @llvm.dbg.declare(metadata %struct.uv_async_s** %handle.addr, metadata !731, metadata !643), !dbg !732
  call void @llvm.dbg.declare(metadata %struct.uv__work** %w, metadata !733, metadata !643), !dbg !734
  call void @llvm.dbg.declare(metadata %struct.uv_loop_s** %loop, metadata !735, metadata !643), !dbg !736
  call void @llvm.dbg.declare(metadata [2 x i8*]** %q, metadata !737, metadata !643), !dbg !738
  call void @llvm.dbg.declare(metadata [2 x i8*]* %wq, metadata !739, metadata !643), !dbg !740
  call void @llvm.dbg.declare(metadata i32* %err, metadata !741, metadata !643), !dbg !742
  %0 = load %struct.uv_async_s*, %struct.uv_async_s** %handle.addr, align 8, !dbg !743
  %1 = bitcast %struct.uv_async_s* %0 to i8*, !dbg !743
  %add.ptr = getelementptr inbounds i8, i8* %1, i64 -176, !dbg !743
  %2 = bitcast i8* %add.ptr to %struct.uv_loop_s*, !dbg !743
  store %struct.uv_loop_s* %2, %struct.uv_loop_s** %loop, align 8, !dbg !744
  %3 = load %struct.uv_loop_s*, %struct.uv_loop_s** %loop, align 8, !dbg !745
  %wq_mutex = getelementptr inbounds %struct.uv_loop_s, %struct.uv_loop_s* %3, i32 0, i32 13, !dbg !746
  call void @uv_mutex_lock(%union.pthread_mutex_t* %wq_mutex), !dbg !747
  br label %do.body, !dbg !748

do.body:                                          ; preds = %entry
  %4 = load %struct.uv_loop_s*, %struct.uv_loop_s** %loop, align 8, !dbg !749
  %wq1 = getelementptr inbounds %struct.uv_loop_s, %struct.uv_loop_s* %4, i32 0, i32 12, !dbg !749
  %5 = load %struct.uv_loop_s*, %struct.uv_loop_s** %loop, align 8, !dbg !749
  %wq2 = getelementptr inbounds %struct.uv_loop_s, %struct.uv_loop_s* %5, i32 0, i32 12, !dbg !749
  %arrayidx = getelementptr inbounds [2 x i8*], [2 x i8*]* %wq2, i64 0, i64 0, !dbg !749
  %6 = bitcast i8** %arrayidx to [2 x i8*]**, !dbg !749
  %7 = load [2 x i8*]*, [2 x i8*]** %6, align 8, !dbg !749
  %cmp = icmp eq [2 x i8*]* %wq1, %7, !dbg !749
  br i1 %cmp, label %if.then, label %if.else, !dbg !749

if.then:                                          ; preds = %do.body
  br label %do.body3, !dbg !753

do.body3:                                         ; preds = %if.then
  %arrayidx4 = getelementptr inbounds [2 x i8*], [2 x i8*]* %wq, i64 0, i64 0, !dbg !755
  %8 = bitcast i8** %arrayidx4 to [2 x i8*]**, !dbg !755
  store [2 x i8*]* %wq, [2 x i8*]** %8, align 16, !dbg !755
  %arrayidx5 = getelementptr inbounds [2 x i8*], [2 x i8*]* %wq, i64 0, i64 1, !dbg !755
  %9 = bitcast i8** %arrayidx5 to [2 x i8*]**, !dbg !755
  store [2 x i8*]* %wq, [2 x i8*]** %9, align 8, !dbg !755
  br label %do.end, !dbg !755

do.end:                                           ; preds = %do.body3
  br label %if.end, !dbg !758

if.else:                                          ; preds = %do.body
  call void @llvm.dbg.declare(metadata [2 x i8*]** %q6, metadata !760, metadata !643), !dbg !762
  %10 = load %struct.uv_loop_s*, %struct.uv_loop_s** %loop, align 8, !dbg !763
  %wq7 = getelementptr inbounds %struct.uv_loop_s, %struct.uv_loop_s* %10, i32 0, i32 12, !dbg !763
  %arrayidx8 = getelementptr inbounds [2 x i8*], [2 x i8*]* %wq7, i64 0, i64 0, !dbg !763
  %11 = bitcast i8** %arrayidx8 to [2 x i8*]**, !dbg !763
  %12 = load [2 x i8*]*, [2 x i8*]** %11, align 8, !dbg !763
  store [2 x i8*]* %12, [2 x i8*]** %q6, align 8, !dbg !763
  br label %do.body9, !dbg !763

do.body9:                                         ; preds = %if.else
  %13 = load %struct.uv_loop_s*, %struct.uv_loop_s** %loop, align 8, !dbg !765
  %wq10 = getelementptr inbounds %struct.uv_loop_s, %struct.uv_loop_s* %13, i32 0, i32 12, !dbg !765
  %arrayidx11 = getelementptr inbounds [2 x i8*], [2 x i8*]* %wq10, i64 0, i64 1, !dbg !765
  %14 = bitcast i8** %arrayidx11 to [2 x i8*]**, !dbg !765
  %15 = load [2 x i8*]*, [2 x i8*]** %14, align 8, !dbg !765
  %arrayidx12 = getelementptr inbounds [2 x i8*], [2 x i8*]* %wq, i64 0, i64 1, !dbg !765
  %16 = bitcast i8** %arrayidx12 to [2 x i8*]**, !dbg !765
  store [2 x i8*]* %15, [2 x i8*]** %16, align 8, !dbg !765
  %arrayidx13 = getelementptr inbounds [2 x i8*], [2 x i8*]* %wq, i64 0, i64 1, !dbg !765
  %17 = bitcast i8** %arrayidx13 to [2 x i8*]**, !dbg !765
  %18 = load [2 x i8*]*, [2 x i8*]** %17, align 8, !dbg !765
  %arrayidx14 = getelementptr inbounds [2 x i8*], [2 x i8*]* %18, i64 0, i64 0, !dbg !765
  %19 = bitcast i8** %arrayidx14 to [2 x i8*]**, !dbg !765
  store [2 x i8*]* %wq, [2 x i8*]** %19, align 8, !dbg !765
  %20 = load [2 x i8*]*, [2 x i8*]** %q6, align 8, !dbg !765
  %arrayidx15 = getelementptr inbounds [2 x i8*], [2 x i8*]* %wq, i64 0, i64 0, !dbg !765
  %21 = bitcast i8** %arrayidx15 to [2 x i8*]**, !dbg !765
  store [2 x i8*]* %20, [2 x i8*]** %21, align 16, !dbg !765
  %22 = load [2 x i8*]*, [2 x i8*]** %q6, align 8, !dbg !765
  %arrayidx16 = getelementptr inbounds [2 x i8*], [2 x i8*]* %22, i64 0, i64 1, !dbg !765
  %23 = bitcast i8** %arrayidx16 to [2 x i8*]**, !dbg !765
  %24 = load [2 x i8*]*, [2 x i8*]** %23, align 8, !dbg !765
  %25 = load %struct.uv_loop_s*, %struct.uv_loop_s** %loop, align 8, !dbg !765
  %wq17 = getelementptr inbounds %struct.uv_loop_s, %struct.uv_loop_s* %25, i32 0, i32 12, !dbg !765
  %arrayidx18 = getelementptr inbounds [2 x i8*], [2 x i8*]* %wq17, i64 0, i64 1, !dbg !765
  %26 = bitcast i8** %arrayidx18 to [2 x i8*]**, !dbg !765
  store [2 x i8*]* %24, [2 x i8*]** %26, align 8, !dbg !765
  %27 = load %struct.uv_loop_s*, %struct.uv_loop_s** %loop, align 8, !dbg !765
  %wq19 = getelementptr inbounds %struct.uv_loop_s, %struct.uv_loop_s* %27, i32 0, i32 12, !dbg !765
  %28 = load %struct.uv_loop_s*, %struct.uv_loop_s** %loop, align 8, !dbg !765
  %wq20 = getelementptr inbounds %struct.uv_loop_s, %struct.uv_loop_s* %28, i32 0, i32 12, !dbg !765
  %arrayidx21 = getelementptr inbounds [2 x i8*], [2 x i8*]* %wq20, i64 0, i64 1, !dbg !765
  %29 = bitcast i8** %arrayidx21 to [2 x i8*]**, !dbg !765
  %30 = load [2 x i8*]*, [2 x i8*]** %29, align 8, !dbg !765
  %arrayidx22 = getelementptr inbounds [2 x i8*], [2 x i8*]* %30, i64 0, i64 0, !dbg !765
  %31 = bitcast i8** %arrayidx22 to [2 x i8*]**, !dbg !765
  store [2 x i8*]* %wq19, [2 x i8*]** %31, align 8, !dbg !765
  %32 = load [2 x i8*]*, [2 x i8*]** %q6, align 8, !dbg !765
  %arrayidx23 = getelementptr inbounds [2 x i8*], [2 x i8*]* %32, i64 0, i64 1, !dbg !765
  %33 = bitcast i8** %arrayidx23 to [2 x i8*]**, !dbg !765
  store [2 x i8*]* %wq, [2 x i8*]** %33, align 8, !dbg !765
  br label %do.end24, !dbg !765

do.end24:                                         ; preds = %do.body9
  br label %if.end

if.end:                                           ; preds = %do.end24, %do.end
  br label %do.end25, !dbg !768

do.end25:                                         ; preds = %if.end
  %34 = load %struct.uv_loop_s*, %struct.uv_loop_s** %loop, align 8, !dbg !770
  %wq_mutex26 = getelementptr inbounds %struct.uv_loop_s, %struct.uv_loop_s* %34, i32 0, i32 13, !dbg !771
  call void @uv_mutex_unlock(%union.pthread_mutex_t* %wq_mutex26), !dbg !772
  br label %while.cond, !dbg !773

while.cond:                                       ; preds = %do.end37, %do.end25
  %arrayidx27 = getelementptr inbounds [2 x i8*], [2 x i8*]* %wq, i64 0, i64 0, !dbg !774
  %35 = bitcast i8** %arrayidx27 to [2 x i8*]**, !dbg !774
  %36 = load [2 x i8*]*, [2 x i8*]** %35, align 16, !dbg !774
  %cmp28 = icmp eq [2 x i8*]* %wq, %36, !dbg !774
  %lnot = xor i1 %cmp28, true, !dbg !776
  br i1 %lnot, label %while.body, label %while.end, !dbg !777

while.body:                                       ; preds = %while.cond
  %arrayidx29 = getelementptr inbounds [2 x i8*], [2 x i8*]* %wq, i64 0, i64 0, !dbg !778
  %37 = bitcast i8** %arrayidx29 to [2 x i8*]**, !dbg !778
  %38 = load [2 x i8*]*, [2 x i8*]** %37, align 16, !dbg !778
  store [2 x i8*]* %38, [2 x i8*]** %q, align 8, !dbg !780
  br label %do.body30, !dbg !781

do.body30:                                        ; preds = %while.body
  %39 = load [2 x i8*]*, [2 x i8*]** %q, align 8, !dbg !782
  %arrayidx31 = getelementptr inbounds [2 x i8*], [2 x i8*]* %39, i64 0, i64 0, !dbg !782
  %40 = bitcast i8** %arrayidx31 to [2 x i8*]**, !dbg !782
  %41 = load [2 x i8*]*, [2 x i8*]** %40, align 8, !dbg !782
  %42 = load [2 x i8*]*, [2 x i8*]** %q, align 8, !dbg !782
  %arrayidx32 = getelementptr inbounds [2 x i8*], [2 x i8*]* %42, i64 0, i64 1, !dbg !782
  %43 = bitcast i8** %arrayidx32 to [2 x i8*]**, !dbg !782
  %44 = load [2 x i8*]*, [2 x i8*]** %43, align 8, !dbg !782
  %arrayidx33 = getelementptr inbounds [2 x i8*], [2 x i8*]* %44, i64 0, i64 0, !dbg !782
  %45 = bitcast i8** %arrayidx33 to [2 x i8*]**, !dbg !782
  store [2 x i8*]* %41, [2 x i8*]** %45, align 8, !dbg !782
  %46 = load [2 x i8*]*, [2 x i8*]** %q, align 8, !dbg !782
  %arrayidx34 = getelementptr inbounds [2 x i8*], [2 x i8*]* %46, i64 0, i64 1, !dbg !782
  %47 = bitcast i8** %arrayidx34 to [2 x i8*]**, !dbg !782
  %48 = load [2 x i8*]*, [2 x i8*]** %47, align 8, !dbg !782
  %49 = load [2 x i8*]*, [2 x i8*]** %q, align 8, !dbg !782
  %arrayidx35 = getelementptr inbounds [2 x i8*], [2 x i8*]* %49, i64 0, i64 0, !dbg !782
  %50 = bitcast i8** %arrayidx35 to [2 x i8*]**, !dbg !782
  %51 = load [2 x i8*]*, [2 x i8*]** %50, align 8, !dbg !782
  %arrayidx36 = getelementptr inbounds [2 x i8*], [2 x i8*]* %51, i64 0, i64 1, !dbg !782
  %52 = bitcast i8** %arrayidx36 to [2 x i8*]**, !dbg !782
  store [2 x i8*]* %48, [2 x i8*]** %52, align 8, !dbg !782
  br label %do.end37, !dbg !782

do.end37:                                         ; preds = %do.body30
  %53 = load [2 x i8*]*, [2 x i8*]** %q, align 8, !dbg !785
  %54 = bitcast [2 x i8*]* %53 to i8*, !dbg !785
  %add.ptr38 = getelementptr inbounds i8, i8* %54, i64 -24, !dbg !785
  %55 = bitcast i8* %add.ptr38 to %struct.uv__work*, !dbg !785
  store %struct.uv__work* %55, %struct.uv__work** %w, align 8, !dbg !786
  %56 = load %struct.uv__work*, %struct.uv__work** %w, align 8, !dbg !787
  %work = getelementptr inbounds %struct.uv__work, %struct.uv__work* %56, i32 0, i32 0, !dbg !788
  %57 = load void (%struct.uv__work*)*, void (%struct.uv__work*)** %work, align 8, !dbg !788
  %cmp39 = icmp eq void (%struct.uv__work*)* %57, @uv__cancelled, !dbg !789
  %cond = select i1 %cmp39, i32 -125, i32 0, !dbg !790
  store i32 %cond, i32* %err, align 4, !dbg !791
  %58 = load %struct.uv__work*, %struct.uv__work** %w, align 8, !dbg !792
  %done = getelementptr inbounds %struct.uv__work, %struct.uv__work* %58, i32 0, i32 1, !dbg !793
  %59 = load void (%struct.uv__work*, i32)*, void (%struct.uv__work*, i32)** %done, align 8, !dbg !793
  %60 = load %struct.uv__work*, %struct.uv__work** %w, align 8, !dbg !794
  %61 = load i32, i32* %err, align 4, !dbg !795
  call void %59(%struct.uv__work* %60, i32 %61), !dbg !792
  br label %while.cond, !dbg !796

while.end:                                        ; preds = %while.cond
  ret void, !dbg !798
}

declare void @uv_mutex_lock(%union.pthread_mutex_t*) #2

declare void @uv_mutex_unlock(%union.pthread_mutex_t*) #2

; Function Attrs: nounwind uwtable
define internal void @uv__cancelled(%struct.uv__work* %w) #0 !dbg !593 {
entry:
  %w.addr = alloca %struct.uv__work*, align 8
  store %struct.uv__work* %w, %struct.uv__work** %w.addr, align 8
  call void @llvm.dbg.declare(metadata %struct.uv__work** %w.addr, metadata !799, metadata !643), !dbg !800
  call void @abort() #7, !dbg !801
  unreachable, !dbg !801

return:                                           ; No predecessors!
  ret void, !dbg !802
}

; Function Attrs: nounwind uwtable
define i32 @uv_queue_work(%struct.uv_loop_s* %loop, %struct.uv_work_s* %req, void (%struct.uv_work_s*)* %work_cb, void (%struct.uv_work_s*, i32)* %after_work_cb) #0 !dbg !570 {
entry:
  %retval = alloca i32, align 4
  %loop.addr = alloca %struct.uv_loop_s*, align 8
  %req.addr = alloca %struct.uv_work_s*, align 8
  %work_cb.addr = alloca void (%struct.uv_work_s*)*, align 8
  %after_work_cb.addr = alloca void (%struct.uv_work_s*, i32)*, align 8
  store %struct.uv_loop_s* %loop, %struct.uv_loop_s** %loop.addr, align 8
  call void @llvm.dbg.declare(metadata %struct.uv_loop_s** %loop.addr, metadata !803, metadata !643), !dbg !804
  store %struct.uv_work_s* %req, %struct.uv_work_s** %req.addr, align 8
  call void @llvm.dbg.declare(metadata %struct.uv_work_s** %req.addr, metadata !805, metadata !643), !dbg !806
  store void (%struct.uv_work_s*)* %work_cb, void (%struct.uv_work_s*)** %work_cb.addr, align 8
  call void @llvm.dbg.declare(metadata void (%struct.uv_work_s*)** %work_cb.addr, metadata !807, metadata !643), !dbg !808
  store void (%struct.uv_work_s*, i32)* %after_work_cb, void (%struct.uv_work_s*, i32)** %after_work_cb.addr, align 8
  call void @llvm.dbg.declare(metadata void (%struct.uv_work_s*, i32)** %after_work_cb.addr, metadata !809, metadata !643), !dbg !810
  %0 = load void (%struct.uv_work_s*)*, void (%struct.uv_work_s*)** %work_cb.addr, align 8, !dbg !811
  %cmp = icmp eq void (%struct.uv_work_s*)* %0, null, !dbg !813
  br i1 %cmp, label %if.then, label %if.end, !dbg !814

if.then:                                          ; preds = %entry
  store i32 -22, i32* %retval, align 4, !dbg !815
  br label %return, !dbg !815

if.end:                                           ; preds = %entry
  br label %do.body, !dbg !816

do.body:                                          ; preds = %if.end
  br label %do.body1, !dbg !817

do.body1:                                         ; preds = %do.body
  %1 = load %struct.uv_work_s*, %struct.uv_work_s** %req.addr, align 8, !dbg !820
  %type = getelementptr inbounds %struct.uv_work_s, %struct.uv_work_s* %1, i32 0, i32 1, !dbg !820
  store i32 7, i32* %type, align 8, !dbg !820
  br label %do.end, !dbg !820

do.end:                                           ; preds = %do.body1
  br label %do.body2, !dbg !823

do.body2:                                         ; preds = %do.end
  br label %do.body3, !dbg !825

do.body3:                                         ; preds = %do.body2
  %2 = load %struct.uv_loop_s*, %struct.uv_loop_s** %loop.addr, align 8, !dbg !828
  %active_reqs = getelementptr inbounds %struct.uv_loop_s, %struct.uv_loop_s* %2, i32 0, i32 3, !dbg !828
  %3 = load %struct.uv_work_s*, %struct.uv_work_s** %req.addr, align 8, !dbg !828
  %active_queue = getelementptr inbounds %struct.uv_work_s, %struct.uv_work_s* %3, i32 0, i32 2, !dbg !828
  %arrayidx = getelementptr inbounds [2 x i8*], [2 x i8*]* %active_queue, i64 0, i64 0, !dbg !828
  %4 = bitcast i8** %arrayidx to [2 x i8*]**, !dbg !828
  store [2 x i8*]* %active_reqs, [2 x i8*]** %4, align 8, !dbg !828
  %5 = load %struct.uv_loop_s*, %struct.uv_loop_s** %loop.addr, align 8, !dbg !828
  %active_reqs4 = getelementptr inbounds %struct.uv_loop_s, %struct.uv_loop_s* %5, i32 0, i32 3, !dbg !828
  %arrayidx5 = getelementptr inbounds [2 x i8*], [2 x i8*]* %active_reqs4, i64 0, i64 1, !dbg !828
  %6 = bitcast i8** %arrayidx5 to [2 x i8*]**, !dbg !828
  %7 = load [2 x i8*]*, [2 x i8*]** %6, align 8, !dbg !828
  %8 = load %struct.uv_work_s*, %struct.uv_work_s** %req.addr, align 8, !dbg !828
  %active_queue6 = getelementptr inbounds %struct.uv_work_s, %struct.uv_work_s* %8, i32 0, i32 2, !dbg !828
  %arrayidx7 = getelementptr inbounds [2 x i8*], [2 x i8*]* %active_queue6, i64 0, i64 1, !dbg !828
  %9 = bitcast i8** %arrayidx7 to [2 x i8*]**, !dbg !828
  store [2 x i8*]* %7, [2 x i8*]** %9, align 8, !dbg !828
  %10 = load %struct.uv_work_s*, %struct.uv_work_s** %req.addr, align 8, !dbg !828
  %active_queue8 = getelementptr inbounds %struct.uv_work_s, %struct.uv_work_s* %10, i32 0, i32 2, !dbg !828
  %11 = load %struct.uv_work_s*, %struct.uv_work_s** %req.addr, align 8, !dbg !828
  %active_queue9 = getelementptr inbounds %struct.uv_work_s, %struct.uv_work_s* %11, i32 0, i32 2, !dbg !828
  %arrayidx10 = getelementptr inbounds [2 x i8*], [2 x i8*]* %active_queue9, i64 0, i64 1, !dbg !828
  %12 = bitcast i8** %arrayidx10 to [2 x i8*]**, !dbg !828
  %13 = load [2 x i8*]*, [2 x i8*]** %12, align 8, !dbg !828
  %arrayidx11 = getelementptr inbounds [2 x i8*], [2 x i8*]* %13, i64 0, i64 0, !dbg !828
  %14 = bitcast i8** %arrayidx11 to [2 x i8*]**, !dbg !828
  store [2 x i8*]* %active_queue8, [2 x i8*]** %14, align 8, !dbg !828
  %15 = load %struct.uv_work_s*, %struct.uv_work_s** %req.addr, align 8, !dbg !828
  %active_queue12 = getelementptr inbounds %struct.uv_work_s, %struct.uv_work_s* %15, i32 0, i32 2, !dbg !828
  %16 = load %struct.uv_loop_s*, %struct.uv_loop_s** %loop.addr, align 8, !dbg !828
  %active_reqs13 = getelementptr inbounds %struct.uv_loop_s, %struct.uv_loop_s* %16, i32 0, i32 3, !dbg !828
  %arrayidx14 = getelementptr inbounds [2 x i8*], [2 x i8*]* %active_reqs13, i64 0, i64 1, !dbg !828
  %17 = bitcast i8** %arrayidx14 to [2 x i8*]**, !dbg !828
  store [2 x i8*]* %active_queue12, [2 x i8*]** %17, align 8, !dbg !828
  br label %do.end15, !dbg !828

do.end15:                                         ; preds = %do.body3
  br label %do.end16, !dbg !831

do.end16:                                         ; preds = %do.end15
  br label %do.end17, !dbg !833

do.end17:                                         ; preds = %do.end16
  %18 = load %struct.uv_loop_s*, %struct.uv_loop_s** %loop.addr, align 8, !dbg !835
  %19 = load %struct.uv_work_s*, %struct.uv_work_s** %req.addr, align 8, !dbg !836
  %loop18 = getelementptr inbounds %struct.uv_work_s, %struct.uv_work_s* %19, i32 0, i32 4, !dbg !837
  store %struct.uv_loop_s* %18, %struct.uv_loop_s** %loop18, align 8, !dbg !838
  %20 = load void (%struct.uv_work_s*)*, void (%struct.uv_work_s*)** %work_cb.addr, align 8, !dbg !839
  %21 = load %struct.uv_work_s*, %struct.uv_work_s** %req.addr, align 8, !dbg !840
  %work_cb19 = getelementptr inbounds %struct.uv_work_s, %struct.uv_work_s* %21, i32 0, i32 5, !dbg !841
  store void (%struct.uv_work_s*)* %20, void (%struct.uv_work_s*)** %work_cb19, align 8, !dbg !842
  %22 = load void (%struct.uv_work_s*, i32)*, void (%struct.uv_work_s*, i32)** %after_work_cb.addr, align 8, !dbg !843
  %23 = load %struct.uv_work_s*, %struct.uv_work_s** %req.addr, align 8, !dbg !844
  %after_work_cb20 = getelementptr inbounds %struct.uv_work_s, %struct.uv_work_s* %23, i32 0, i32 6, !dbg !845
  store void (%struct.uv_work_s*, i32)* %22, void (%struct.uv_work_s*, i32)** %after_work_cb20, align 8, !dbg !846
  %24 = load %struct.uv_loop_s*, %struct.uv_loop_s** %loop.addr, align 8, !dbg !847
  %25 = load %struct.uv_work_s*, %struct.uv_work_s** %req.addr, align 8, !dbg !848
  %work_req = getelementptr inbounds %struct.uv_work_s, %struct.uv_work_s* %25, i32 0, i32 7, !dbg !849
  call void @uv__work_submit(%struct.uv_loop_s* %24, %struct.uv__work* %work_req, void (%struct.uv__work*)* @uv__queue_work, void (%struct.uv__work*, i32)* @uv__queue_done), !dbg !850
  store i32 0, i32* %retval, align 4, !dbg !851
  br label %return, !dbg !851

return:                                           ; preds = %do.end17, %if.then
  %26 = load i32, i32* %retval, align 4, !dbg !852
  ret i32 %26, !dbg !852
}

; Function Attrs: nounwind uwtable
define internal void @uv__queue_work(%struct.uv__work* %w) #0 !dbg !594 {
entry:
  %w.addr = alloca %struct.uv__work*, align 8
  %req = alloca %struct.uv_work_s*, align 8
  store %struct.uv__work* %w, %struct.uv__work** %w.addr, align 8
  call void @llvm.dbg.declare(metadata %struct.uv__work** %w.addr, metadata !853, metadata !643), !dbg !854
  call void @llvm.dbg.declare(metadata %struct.uv_work_s** %req, metadata !855, metadata !643), !dbg !856
  %0 = load %struct.uv__work*, %struct.uv__work** %w.addr, align 8, !dbg !857
  %1 = bitcast %struct.uv__work* %0 to i8*, !dbg !857
  %add.ptr = getelementptr inbounds i8, i8* %1, i64 -88, !dbg !857
  %2 = bitcast i8* %add.ptr to %struct.uv_work_s*, !dbg !857
  store %struct.uv_work_s* %2, %struct.uv_work_s** %req, align 8, !dbg !856
  %3 = load %struct.uv_work_s*, %struct.uv_work_s** %req, align 8, !dbg !858
  %work_cb = getelementptr inbounds %struct.uv_work_s, %struct.uv_work_s* %3, i32 0, i32 5, !dbg !859
  %4 = load void (%struct.uv_work_s*)*, void (%struct.uv_work_s*)** %work_cb, align 8, !dbg !859
  %5 = load %struct.uv_work_s*, %struct.uv_work_s** %req, align 8, !dbg !860
  call void %4(%struct.uv_work_s* %5), !dbg !858
  ret void, !dbg !861
}

; Function Attrs: nounwind uwtable
define internal void @uv__queue_done(%struct.uv__work* %w, i32 %err) #0 !dbg !595 {
entry:
  %w.addr = alloca %struct.uv__work*, align 8
  %err.addr = alloca i32, align 4
  %req = alloca %struct.uv_work_s*, align 8
  store %struct.uv__work* %w, %struct.uv__work** %w.addr, align 8
  call void @llvm.dbg.declare(metadata %struct.uv__work** %w.addr, metadata !862, metadata !643), !dbg !863
  store i32 %err, i32* %err.addr, align 4
  call void @llvm.dbg.declare(metadata i32* %err.addr, metadata !864, metadata !643), !dbg !865
  call void @llvm.dbg.declare(metadata %struct.uv_work_s** %req, metadata !866, metadata !643), !dbg !867
  %0 = load %struct.uv__work*, %struct.uv__work** %w.addr, align 8, !dbg !868
  %1 = bitcast %struct.uv__work* %0 to i8*, !dbg !868
  %add.ptr = getelementptr inbounds i8, i8* %1, i64 -88, !dbg !868
  %2 = bitcast i8* %add.ptr to %struct.uv_work_s*, !dbg !868
  store %struct.uv_work_s* %2, %struct.uv_work_s** %req, align 8, !dbg !869
  br label %do.body, !dbg !870

do.body:                                          ; preds = %entry
  %3 = load %struct.uv_work_s*, %struct.uv_work_s** %req, align 8, !dbg !871
  %loop = getelementptr inbounds %struct.uv_work_s, %struct.uv_work_s* %3, i32 0, i32 4, !dbg !871
  %4 = load %struct.uv_loop_s*, %struct.uv_loop_s** %loop, align 8, !dbg !871
  %active_reqs = getelementptr inbounds %struct.uv_loop_s, %struct.uv_loop_s* %4, i32 0, i32 3, !dbg !871
  %5 = load %struct.uv_work_s*, %struct.uv_work_s** %req, align 8, !dbg !871
  %loop1 = getelementptr inbounds %struct.uv_work_s, %struct.uv_work_s* %5, i32 0, i32 4, !dbg !871
  %6 = load %struct.uv_loop_s*, %struct.uv_loop_s** %loop1, align 8, !dbg !871
  %active_reqs2 = getelementptr inbounds %struct.uv_loop_s, %struct.uv_loop_s* %6, i32 0, i32 3, !dbg !871
  %arrayidx = getelementptr inbounds [2 x i8*], [2 x i8*]* %active_reqs2, i64 0, i64 0, !dbg !871
  %7 = bitcast i8** %arrayidx to [2 x i8*]**, !dbg !871
  %8 = load [2 x i8*]*, [2 x i8*]** %7, align 8, !dbg !871
  %cmp = icmp eq [2 x i8*]* %active_reqs, %8, !dbg !871
  %conv = zext i1 %cmp to i32, !dbg !871
  %cmp3 = icmp eq i32 %conv, 0, !dbg !871
  br i1 %cmp3, label %cond.true, label %cond.false, !dbg !871

cond.true:                                        ; preds = %do.body
  br label %cond.end, !dbg !874

cond.false:                                       ; preds = %do.body
  call void @__assert_fail(i8* getelementptr inbounds ([123 x i8], [123 x i8]* @.str.1, i32 0, i32 0), i8* getelementptr inbounds ([69 x i8], [69 x i8]* @.str.2, i32 0, i32 0), i32 261, i8* getelementptr inbounds ([44 x i8], [44 x i8]* @__PRETTY_FUNCTION__.uv__queue_done, i32 0, i32 0)) #7, !dbg !876
  unreachable, !dbg !876
                                                  ; No predecessors!
  br label %cond.end, !dbg !878

cond.end:                                         ; preds = %9, %cond.true
  br label %do.body5, !dbg !880

do.body5:                                         ; preds = %cond.end
  %10 = load %struct.uv_work_s*, %struct.uv_work_s** %req, align 8, !dbg !882
  %active_queue = getelementptr inbounds %struct.uv_work_s, %struct.uv_work_s* %10, i32 0, i32 2, !dbg !882
  %arrayidx6 = getelementptr inbounds [2 x i8*], [2 x i8*]* %active_queue, i64 0, i64 0, !dbg !882
  %11 = bitcast i8** %arrayidx6 to [2 x i8*]**, !dbg !882
  %12 = load [2 x i8*]*, [2 x i8*]** %11, align 8, !dbg !882
  %13 = load %struct.uv_work_s*, %struct.uv_work_s** %req, align 8, !dbg !882
  %active_queue7 = getelementptr inbounds %struct.uv_work_s, %struct.uv_work_s* %13, i32 0, i32 2, !dbg !882
  %arrayidx8 = getelementptr inbounds [2 x i8*], [2 x i8*]* %active_queue7, i64 0, i64 1, !dbg !882
  %14 = bitcast i8** %arrayidx8 to [2 x i8*]**, !dbg !882
  %15 = load [2 x i8*]*, [2 x i8*]** %14, align 8, !dbg !882
  %arrayidx9 = getelementptr inbounds [2 x i8*], [2 x i8*]* %15, i64 0, i64 0, !dbg !882
  %16 = bitcast i8** %arrayidx9 to [2 x i8*]**, !dbg !882
  store [2 x i8*]* %12, [2 x i8*]** %16, align 8, !dbg !882
  %17 = load %struct.uv_work_s*, %struct.uv_work_s** %req, align 8, !dbg !882
  %active_queue10 = getelementptr inbounds %struct.uv_work_s, %struct.uv_work_s* %17, i32 0, i32 2, !dbg !882
  %arrayidx11 = getelementptr inbounds [2 x i8*], [2 x i8*]* %active_queue10, i64 0, i64 1, !dbg !882
  %18 = bitcast i8** %arrayidx11 to [2 x i8*]**, !dbg !882
  %19 = load [2 x i8*]*, [2 x i8*]** %18, align 8, !dbg !882
  %20 = load %struct.uv_work_s*, %struct.uv_work_s** %req, align 8, !dbg !882
  %active_queue12 = getelementptr inbounds %struct.uv_work_s, %struct.uv_work_s* %20, i32 0, i32 2, !dbg !882
  %arrayidx13 = getelementptr inbounds [2 x i8*], [2 x i8*]* %active_queue12, i64 0, i64 0, !dbg !882
  %21 = bitcast i8** %arrayidx13 to [2 x i8*]**, !dbg !882
  %22 = load [2 x i8*]*, [2 x i8*]** %21, align 8, !dbg !882
  %arrayidx14 = getelementptr inbounds [2 x i8*], [2 x i8*]* %22, i64 0, i64 1, !dbg !882
  %23 = bitcast i8** %arrayidx14 to [2 x i8*]**, !dbg !882
  store [2 x i8*]* %19, [2 x i8*]** %23, align 8, !dbg !882
  br label %do.end, !dbg !882

do.end:                                           ; preds = %do.body5
  br label %do.end15, !dbg !885

do.end15:                                         ; preds = %do.end
  %24 = load %struct.uv_work_s*, %struct.uv_work_s** %req, align 8, !dbg !887
  %after_work_cb = getelementptr inbounds %struct.uv_work_s, %struct.uv_work_s* %24, i32 0, i32 6, !dbg !889
  %25 = load void (%struct.uv_work_s*, i32)*, void (%struct.uv_work_s*, i32)** %after_work_cb, align 8, !dbg !889
  %cmp16 = icmp eq void (%struct.uv_work_s*, i32)* %25, null, !dbg !890
  br i1 %cmp16, label %if.then, label %if.end, !dbg !891

if.then:                                          ; preds = %do.end15
  br label %return, !dbg !892

if.end:                                           ; preds = %do.end15
  %26 = load %struct.uv_work_s*, %struct.uv_work_s** %req, align 8, !dbg !893
  %after_work_cb18 = getelementptr inbounds %struct.uv_work_s, %struct.uv_work_s* %26, i32 0, i32 6, !dbg !894
  %27 = load void (%struct.uv_work_s*, i32)*, void (%struct.uv_work_s*, i32)** %after_work_cb18, align 8, !dbg !894
  %28 = load %struct.uv_work_s*, %struct.uv_work_s** %req, align 8, !dbg !895
  %29 = load i32, i32* %err.addr, align 4, !dbg !896
  call void %27(%struct.uv_work_s* %28, i32 %29), !dbg !893
  br label %return, !dbg !897

return:                                           ; preds = %if.end, %if.then
  ret void, !dbg !898
}

; Function Attrs: nounwind uwtable
define i32 @uv_cancel(%struct.uv_req_s* %req) #0 !dbg !573 {
entry:
  %retval = alloca i32, align 4
  %req.addr = alloca %struct.uv_req_s*, align 8
  %wreq = alloca %struct.uv__work*, align 8
  %loop = alloca %struct.uv_loop_s*, align 8
  store %struct.uv_req_s* %req, %struct.uv_req_s** %req.addr, align 8
  call void @llvm.dbg.declare(metadata %struct.uv_req_s** %req.addr, metadata !900, metadata !643), !dbg !901
  call void @llvm.dbg.declare(metadata %struct.uv__work** %wreq, metadata !902, metadata !643), !dbg !903
  call void @llvm.dbg.declare(metadata %struct.uv_loop_s** %loop, metadata !904, metadata !643), !dbg !905
  %0 = load %struct.uv_req_s*, %struct.uv_req_s** %req.addr, align 8, !dbg !906
  %type = getelementptr inbounds %struct.uv_req_s, %struct.uv_req_s* %0, i32 0, i32 1, !dbg !907
  %1 = load i32, i32* %type, align 8, !dbg !907
  switch i32 %1, label %sw.default [
    i32 6, label %sw.bb
    i32 8, label %sw.bb2
    i32 9, label %sw.bb5
    i32 7, label %sw.bb8
  ], !dbg !908

sw.bb:                                            ; preds = %entry
  %2 = load %struct.uv_req_s*, %struct.uv_req_s** %req.addr, align 8, !dbg !909
  %3 = bitcast %struct.uv_req_s* %2 to %struct.uv_fs_s*, !dbg !911
  %loop1 = getelementptr inbounds %struct.uv_fs_s, %struct.uv_fs_s* %3, i32 0, i32 5, !dbg !911
  %4 = load %struct.uv_loop_s*, %struct.uv_loop_s** %loop1, align 8, !dbg !911
  store %struct.uv_loop_s* %4, %struct.uv_loop_s** %loop, align 8, !dbg !912
  %5 = load %struct.uv_req_s*, %struct.uv_req_s** %req.addr, align 8, !dbg !913
  %6 = bitcast %struct.uv_req_s* %5 to %struct.uv_fs_s*, !dbg !914
  %work_req = getelementptr inbounds %struct.uv_fs_s, %struct.uv_fs_s* %6, i32 0, i32 22, !dbg !914
  store %struct.uv__work* %work_req, %struct.uv__work** %wreq, align 8, !dbg !915
  br label %sw.epilog, !dbg !916

sw.bb2:                                           ; preds = %entry
  %7 = load %struct.uv_req_s*, %struct.uv_req_s** %req.addr, align 8, !dbg !917
  %8 = bitcast %struct.uv_req_s* %7 to %struct.uv_getaddrinfo_s*, !dbg !918
  %loop3 = getelementptr inbounds %struct.uv_getaddrinfo_s, %struct.uv_getaddrinfo_s* %8, i32 0, i32 4, !dbg !918
  %9 = load %struct.uv_loop_s*, %struct.uv_loop_s** %loop3, align 8, !dbg !918
  store %struct.uv_loop_s* %9, %struct.uv_loop_s** %loop, align 8, !dbg !919
  %10 = load %struct.uv_req_s*, %struct.uv_req_s** %req.addr, align 8, !dbg !920
  %11 = bitcast %struct.uv_req_s* %10 to %struct.uv_getaddrinfo_s*, !dbg !921
  %work_req4 = getelementptr inbounds %struct.uv_getaddrinfo_s, %struct.uv_getaddrinfo_s* %11, i32 0, i32 5, !dbg !921
  store %struct.uv__work* %work_req4, %struct.uv__work** %wreq, align 8, !dbg !922
  br label %sw.epilog, !dbg !923

sw.bb5:                                           ; preds = %entry
  %12 = load %struct.uv_req_s*, %struct.uv_req_s** %req.addr, align 8, !dbg !924
  %13 = bitcast %struct.uv_req_s* %12 to %struct.uv_getnameinfo_s*, !dbg !925
  %loop6 = getelementptr inbounds %struct.uv_getnameinfo_s, %struct.uv_getnameinfo_s* %13, i32 0, i32 4, !dbg !925
  %14 = load %struct.uv_loop_s*, %struct.uv_loop_s** %loop6, align 8, !dbg !925
  store %struct.uv_loop_s* %14, %struct.uv_loop_s** %loop, align 8, !dbg !926
  %15 = load %struct.uv_req_s*, %struct.uv_req_s** %req.addr, align 8, !dbg !927
  %16 = bitcast %struct.uv_req_s* %15 to %struct.uv_getnameinfo_s*, !dbg !928
  %work_req7 = getelementptr inbounds %struct.uv_getnameinfo_s, %struct.uv_getnameinfo_s* %16, i32 0, i32 5, !dbg !928
  store %struct.uv__work* %work_req7, %struct.uv__work** %wreq, align 8, !dbg !929
  br label %sw.epilog, !dbg !930

sw.bb8:                                           ; preds = %entry
  %17 = load %struct.uv_req_s*, %struct.uv_req_s** %req.addr, align 8, !dbg !931
  %18 = bitcast %struct.uv_req_s* %17 to %struct.uv_work_s*, !dbg !932
  %loop9 = getelementptr inbounds %struct.uv_work_s, %struct.uv_work_s* %18, i32 0, i32 4, !dbg !932
  %19 = load %struct.uv_loop_s*, %struct.uv_loop_s** %loop9, align 8, !dbg !932
  store %struct.uv_loop_s* %19, %struct.uv_loop_s** %loop, align 8, !dbg !933
  %20 = load %struct.uv_req_s*, %struct.uv_req_s** %req.addr, align 8, !dbg !934
  %21 = bitcast %struct.uv_req_s* %20 to %struct.uv_work_s*, !dbg !935
  %work_req10 = getelementptr inbounds %struct.uv_work_s, %struct.uv_work_s* %21, i32 0, i32 7, !dbg !935
  store %struct.uv__work* %work_req10, %struct.uv__work** %wreq, align 8, !dbg !936
  br label %sw.epilog, !dbg !937

sw.default:                                       ; preds = %entry
  store i32 -22, i32* %retval, align 4, !dbg !938
  br label %return, !dbg !938

sw.epilog:                                        ; preds = %sw.bb8, %sw.bb5, %sw.bb2, %sw.bb
  %22 = load %struct.uv_loop_s*, %struct.uv_loop_s** %loop, align 8, !dbg !939
  %23 = load %struct.uv_req_s*, %struct.uv_req_s** %req.addr, align 8, !dbg !940
  %24 = load %struct.uv__work*, %struct.uv__work** %wreq, align 8, !dbg !941
  %call = call i32 @uv__work_cancel(%struct.uv_loop_s* %22, %struct.uv_req_s* %23, %struct.uv__work* %24), !dbg !942
  store i32 %call, i32* %retval, align 4, !dbg !943
  br label %return, !dbg !943

return:                                           ; preds = %sw.epilog, %sw.default
  %25 = load i32, i32* %retval, align 4, !dbg !944
  ret i32 %25, !dbg !944
}

; Function Attrs: nounwind uwtable
define internal i32 @uv__work_cancel(%struct.uv_loop_s* %loop, %struct.uv_req_s* %req, %struct.uv__work* %w) #0 !dbg !596 {
entry:
  %retval = alloca i32, align 4
  %loop.addr = alloca %struct.uv_loop_s*, align 8
  %req.addr = alloca %struct.uv_req_s*, align 8
  %w.addr = alloca %struct.uv__work*, align 8
  %cancelled = alloca i32, align 4
  store %struct.uv_loop_s* %loop, %struct.uv_loop_s** %loop.addr, align 8
  call void @llvm.dbg.declare(metadata %struct.uv_loop_s** %loop.addr, metadata !945, metadata !643), !dbg !946
  store %struct.uv_req_s* %req, %struct.uv_req_s** %req.addr, align 8
  call void @llvm.dbg.declare(metadata %struct.uv_req_s** %req.addr, metadata !947, metadata !643), !dbg !948
  store %struct.uv__work* %w, %struct.uv__work** %w.addr, align 8
  call void @llvm.dbg.declare(metadata %struct.uv__work** %w.addr, metadata !949, metadata !643), !dbg !950
  call void @llvm.dbg.declare(metadata i32* %cancelled, metadata !951, metadata !643), !dbg !952
  call void @uv_mutex_lock(%union.pthread_mutex_t* @mutex), !dbg !953
  %0 = load %struct.uv__work*, %struct.uv__work** %w.addr, align 8, !dbg !954
  %loop1 = getelementptr inbounds %struct.uv__work, %struct.uv__work* %0, i32 0, i32 2, !dbg !955
  %1 = load %struct.uv_loop_s*, %struct.uv_loop_s** %loop1, align 8, !dbg !955
  %wq_mutex = getelementptr inbounds %struct.uv_loop_s, %struct.uv_loop_s* %1, i32 0, i32 13, !dbg !956
  call void @uv_mutex_lock(%union.pthread_mutex_t* %wq_mutex), !dbg !957
  %2 = load %struct.uv__work*, %struct.uv__work** %w.addr, align 8, !dbg !958
  %wq = getelementptr inbounds %struct.uv__work, %struct.uv__work* %2, i32 0, i32 3, !dbg !958
  %3 = load %struct.uv__work*, %struct.uv__work** %w.addr, align 8, !dbg !958
  %wq2 = getelementptr inbounds %struct.uv__work, %struct.uv__work* %3, i32 0, i32 3, !dbg !958
  %arrayidx = getelementptr inbounds [2 x i8*], [2 x i8*]* %wq2, i64 0, i64 0, !dbg !958
  %4 = bitcast i8** %arrayidx to [2 x i8*]**, !dbg !958
  %5 = load [2 x i8*]*, [2 x i8*]** %4, align 8, !dbg !958
  %cmp = icmp eq [2 x i8*]* %wq, %5, !dbg !958
  br i1 %cmp, label %land.end, label %land.rhs, !dbg !959

land.rhs:                                         ; preds = %entry
  %6 = load %struct.uv__work*, %struct.uv__work** %w.addr, align 8, !dbg !960
  %work = getelementptr inbounds %struct.uv__work, %struct.uv__work* %6, i32 0, i32 0, !dbg !962
  %7 = load void (%struct.uv__work*)*, void (%struct.uv__work*)** %work, align 8, !dbg !962
  %cmp3 = icmp ne void (%struct.uv__work*)* %7, null, !dbg !963
  br label %land.end

land.end:                                         ; preds = %land.rhs, %entry
  %8 = phi i1 [ false, %entry ], [ %cmp3, %land.rhs ]
  %land.ext = zext i1 %8 to i32, !dbg !964
  store i32 %land.ext, i32* %cancelled, align 4, !dbg !966
  %9 = load i32, i32* %cancelled, align 4, !dbg !967
  %tobool = icmp ne i32 %9, 0, !dbg !967
  br i1 %tobool, label %if.then, label %if.end, !dbg !969

if.then:                                          ; preds = %land.end
  br label %do.body, !dbg !970

do.body:                                          ; preds = %if.then
  %10 = load %struct.uv__work*, %struct.uv__work** %w.addr, align 8, !dbg !971
  %wq4 = getelementptr inbounds %struct.uv__work, %struct.uv__work* %10, i32 0, i32 3, !dbg !971
  %arrayidx5 = getelementptr inbounds [2 x i8*], [2 x i8*]* %wq4, i64 0, i64 0, !dbg !971
  %11 = bitcast i8** %arrayidx5 to [2 x i8*]**, !dbg !971
  %12 = load [2 x i8*]*, [2 x i8*]** %11, align 8, !dbg !971
  %13 = load %struct.uv__work*, %struct.uv__work** %w.addr, align 8, !dbg !971
  %wq6 = getelementptr inbounds %struct.uv__work, %struct.uv__work* %13, i32 0, i32 3, !dbg !971
  %arrayidx7 = getelementptr inbounds [2 x i8*], [2 x i8*]* %wq6, i64 0, i64 1, !dbg !971
  %14 = bitcast i8** %arrayidx7 to [2 x i8*]**, !dbg !971
  %15 = load [2 x i8*]*, [2 x i8*]** %14, align 8, !dbg !971
  %arrayidx8 = getelementptr inbounds [2 x i8*], [2 x i8*]* %15, i64 0, i64 0, !dbg !971
  %16 = bitcast i8** %arrayidx8 to [2 x i8*]**, !dbg !971
  store [2 x i8*]* %12, [2 x i8*]** %16, align 8, !dbg !971
  %17 = load %struct.uv__work*, %struct.uv__work** %w.addr, align 8, !dbg !971
  %wq9 = getelementptr inbounds %struct.uv__work, %struct.uv__work* %17, i32 0, i32 3, !dbg !971
  %arrayidx10 = getelementptr inbounds [2 x i8*], [2 x i8*]* %wq9, i64 0, i64 1, !dbg !971
  %18 = bitcast i8** %arrayidx10 to [2 x i8*]**, !dbg !971
  %19 = load [2 x i8*]*, [2 x i8*]** %18, align 8, !dbg !971
  %20 = load %struct.uv__work*, %struct.uv__work** %w.addr, align 8, !dbg !971
  %wq11 = getelementptr inbounds %struct.uv__work, %struct.uv__work* %20, i32 0, i32 3, !dbg !971
  %arrayidx12 = getelementptr inbounds [2 x i8*], [2 x i8*]* %wq11, i64 0, i64 0, !dbg !971
  %21 = bitcast i8** %arrayidx12 to [2 x i8*]**, !dbg !971
  %22 = load [2 x i8*]*, [2 x i8*]** %21, align 8, !dbg !971
  %arrayidx13 = getelementptr inbounds [2 x i8*], [2 x i8*]* %22, i64 0, i64 1, !dbg !971
  %23 = bitcast i8** %arrayidx13 to [2 x i8*]**, !dbg !971
  store [2 x i8*]* %19, [2 x i8*]** %23, align 8, !dbg !971
  br label %do.end, !dbg !971

do.end:                                           ; preds = %do.body
  br label %if.end, !dbg !974

if.end:                                           ; preds = %do.end, %land.end
  %24 = load %struct.uv__work*, %struct.uv__work** %w.addr, align 8, !dbg !976
  %loop14 = getelementptr inbounds %struct.uv__work, %struct.uv__work* %24, i32 0, i32 2, !dbg !977
  %25 = load %struct.uv_loop_s*, %struct.uv_loop_s** %loop14, align 8, !dbg !977
  %wq_mutex15 = getelementptr inbounds %struct.uv_loop_s, %struct.uv_loop_s* %25, i32 0, i32 13, !dbg !978
  call void @uv_mutex_unlock(%union.pthread_mutex_t* %wq_mutex15), !dbg !979
  call void @uv_mutex_unlock(%union.pthread_mutex_t* @mutex), !dbg !980
  %26 = load i32, i32* %cancelled, align 4, !dbg !981
  %tobool16 = icmp ne i32 %26, 0, !dbg !981
  br i1 %tobool16, label %if.end18, label %if.then17, !dbg !983

if.then17:                                        ; preds = %if.end
  store i32 -16, i32* %retval, align 4, !dbg !984
  br label %return, !dbg !984

if.end18:                                         ; preds = %if.end
  %27 = load %struct.uv__work*, %struct.uv__work** %w.addr, align 8, !dbg !985
  %work19 = getelementptr inbounds %struct.uv__work, %struct.uv__work* %27, i32 0, i32 0, !dbg !986
  store void (%struct.uv__work*)* @uv__cancelled, void (%struct.uv__work*)** %work19, align 8, !dbg !987
  %28 = load %struct.uv_loop_s*, %struct.uv_loop_s** %loop.addr, align 8, !dbg !988
  %wq_mutex20 = getelementptr inbounds %struct.uv_loop_s, %struct.uv_loop_s* %28, i32 0, i32 13, !dbg !989
  call void @uv_mutex_lock(%union.pthread_mutex_t* %wq_mutex20), !dbg !990
  br label %do.body21, !dbg !991

do.body21:                                        ; preds = %if.end18
  %29 = load %struct.uv_loop_s*, %struct.uv_loop_s** %loop.addr, align 8, !dbg !992
  %wq22 = getelementptr inbounds %struct.uv_loop_s, %struct.uv_loop_s* %29, i32 0, i32 12, !dbg !992
  %30 = load %struct.uv__work*, %struct.uv__work** %w.addr, align 8, !dbg !992
  %wq23 = getelementptr inbounds %struct.uv__work, %struct.uv__work* %30, i32 0, i32 3, !dbg !992
  %arrayidx24 = getelementptr inbounds [2 x i8*], [2 x i8*]* %wq23, i64 0, i64 0, !dbg !992
  %31 = bitcast i8** %arrayidx24 to [2 x i8*]**, !dbg !992
  store [2 x i8*]* %wq22, [2 x i8*]** %31, align 8, !dbg !992
  %32 = load %struct.uv_loop_s*, %struct.uv_loop_s** %loop.addr, align 8, !dbg !992
  %wq25 = getelementptr inbounds %struct.uv_loop_s, %struct.uv_loop_s* %32, i32 0, i32 12, !dbg !992
  %arrayidx26 = getelementptr inbounds [2 x i8*], [2 x i8*]* %wq25, i64 0, i64 1, !dbg !992
  %33 = bitcast i8** %arrayidx26 to [2 x i8*]**, !dbg !992
  %34 = load [2 x i8*]*, [2 x i8*]** %33, align 8, !dbg !992
  %35 = load %struct.uv__work*, %struct.uv__work** %w.addr, align 8, !dbg !992
  %wq27 = getelementptr inbounds %struct.uv__work, %struct.uv__work* %35, i32 0, i32 3, !dbg !992
  %arrayidx28 = getelementptr inbounds [2 x i8*], [2 x i8*]* %wq27, i64 0, i64 1, !dbg !992
  %36 = bitcast i8** %arrayidx28 to [2 x i8*]**, !dbg !992
  store [2 x i8*]* %34, [2 x i8*]** %36, align 8, !dbg !992
  %37 = load %struct.uv__work*, %struct.uv__work** %w.addr, align 8, !dbg !992
  %wq29 = getelementptr inbounds %struct.uv__work, %struct.uv__work* %37, i32 0, i32 3, !dbg !992
  %38 = load %struct.uv__work*, %struct.uv__work** %w.addr, align 8, !dbg !992
  %wq30 = getelementptr inbounds %struct.uv__work, %struct.uv__work* %38, i32 0, i32 3, !dbg !992
  %arrayidx31 = getelementptr inbounds [2 x i8*], [2 x i8*]* %wq30, i64 0, i64 1, !dbg !992
  %39 = bitcast i8** %arrayidx31 to [2 x i8*]**, !dbg !992
  %40 = load [2 x i8*]*, [2 x i8*]** %39, align 8, !dbg !992
  %arrayidx32 = getelementptr inbounds [2 x i8*], [2 x i8*]* %40, i64 0, i64 0, !dbg !992
  %41 = bitcast i8** %arrayidx32 to [2 x i8*]**, !dbg !992
  store [2 x i8*]* %wq29, [2 x i8*]** %41, align 8, !dbg !992
  %42 = load %struct.uv__work*, %struct.uv__work** %w.addr, align 8, !dbg !992
  %wq33 = getelementptr inbounds %struct.uv__work, %struct.uv__work* %42, i32 0, i32 3, !dbg !992
  %43 = load %struct.uv_loop_s*, %struct.uv_loop_s** %loop.addr, align 8, !dbg !992
  %wq34 = getelementptr inbounds %struct.uv_loop_s, %struct.uv_loop_s* %43, i32 0, i32 12, !dbg !992
  %arrayidx35 = getelementptr inbounds [2 x i8*], [2 x i8*]* %wq34, i64 0, i64 1, !dbg !992
  %44 = bitcast i8** %arrayidx35 to [2 x i8*]**, !dbg !992
  store [2 x i8*]* %wq33, [2 x i8*]** %44, align 8, !dbg !992
  br label %do.end36, !dbg !992

do.end36:                                         ; preds = %do.body21
  %45 = load %struct.uv_loop_s*, %struct.uv_loop_s** %loop.addr, align 8, !dbg !995
  %wq_async = getelementptr inbounds %struct.uv_loop_s, %struct.uv_loop_s* %45, i32 0, i32 14, !dbg !996
  %call = call i32 @uv_async_send(%struct.uv_async_s* %wq_async), !dbg !997
  %46 = load %struct.uv_loop_s*, %struct.uv_loop_s** %loop.addr, align 8, !dbg !998
  %wq_mutex37 = getelementptr inbounds %struct.uv_loop_s, %struct.uv_loop_s* %46, i32 0, i32 13, !dbg !999
  call void @uv_mutex_unlock(%union.pthread_mutex_t* %wq_mutex37), !dbg !1000
  store i32 0, i32* %retval, align 4, !dbg !1001
  br label %return, !dbg !1001

return:                                           ; preds = %do.end36, %if.then17
  %47 = load i32, i32* %retval, align 4, !dbg !1002
  ret i32 %47, !dbg !1002
}

declare void @uv_cond_signal(%union.pthread_cond_t*) #2

; Function Attrs: nounwind
declare i32 @pthread_atfork(void ()*, void ()*, void ()*) #4

; Function Attrs: nounwind uwtable
define internal void @reset_once() #0 !dbg !588 {
entry:
  %child_once = alloca i32, align 4
  call void @llvm.dbg.declare(metadata i32* %child_once, metadata !1003, metadata !643), !dbg !1004
  store i32 0, i32* %child_once, align 4, !dbg !1004
  %0 = bitcast i32* %child_once to i8*, !dbg !1005
  call void @llvm.memcpy.p0i8.p0i8.i64(i8* bitcast (i32* @once to i8*), i8* %0, i64 4, i32 4, i1 false), !dbg !1005
  ret void, !dbg !1006
}

; Function Attrs: nounwind uwtable
define internal void @init_threads() #0 !dbg !589 {
entry:
  %i = alloca i32, align 4
  %val = alloca i8*, align 8
  call void @llvm.dbg.declare(metadata i32* %i, metadata !1007, metadata !643), !dbg !1008
  call void @llvm.dbg.declare(metadata i8** %val, metadata !1009, metadata !643), !dbg !1010
  store i32 4, i32* @nthreads, align 4, !dbg !1011
  %call = call i8* @getenv(i8* getelementptr inbounds ([19 x i8], [19 x i8]* @.str, i32 0, i32 0)) #8, !dbg !1012
  store i8* %call, i8** %val, align 8, !dbg !1013
  %0 = load i8*, i8** %val, align 8, !dbg !1014
  %cmp = icmp ne i8* %0, null, !dbg !1016
  br i1 %cmp, label %if.then, label %if.end, !dbg !1017

if.then:                                          ; preds = %entry
  %1 = load i8*, i8** %val, align 8, !dbg !1018
  %call1 = call i32 @atoi(i8* %1) #9, !dbg !1019
  store i32 %call1, i32* @nthreads, align 4, !dbg !1020
  br label %if.end, !dbg !1021

if.end:                                           ; preds = %if.then, %entry
  %2 = load i32, i32* @nthreads, align 4, !dbg !1022
  %cmp2 = icmp eq i32 %2, 0, !dbg !1024
  br i1 %cmp2, label %if.then3, label %if.end4, !dbg !1025

if.then3:                                         ; preds = %if.end
  store i32 1, i32* @nthreads, align 4, !dbg !1026
  br label %if.end4, !dbg !1027

if.end4:                                          ; preds = %if.then3, %if.end
  %3 = load i32, i32* @nthreads, align 4, !dbg !1028
  %cmp5 = icmp ugt i32 %3, 128, !dbg !1030
  br i1 %cmp5, label %if.then6, label %if.end7, !dbg !1031

if.then6:                                         ; preds = %if.end4
  store i32 128, i32* @nthreads, align 4, !dbg !1032
  br label %if.end7, !dbg !1033

if.end7:                                          ; preds = %if.then6, %if.end4
  store i64* getelementptr inbounds ([4 x i64], [4 x i64]* @default_threads, i32 0, i32 0), i64** @threads, align 8, !dbg !1034
  %4 = load i32, i32* @nthreads, align 4, !dbg !1035
  %conv = zext i32 %4 to i64, !dbg !1035
  %cmp8 = icmp ugt i64 %conv, 4, !dbg !1037
  br i1 %cmp8, label %if.then10, label %if.end17, !dbg !1038

if.then10:                                        ; preds = %if.end7
  %5 = load i32, i32* @nthreads, align 4, !dbg !1039
  %conv11 = zext i32 %5 to i64, !dbg !1039
  %mul = mul i64 %conv11, 8, !dbg !1041
  %call12 = call i8* @uv__malloc(i64 %mul), !dbg !1042
  %6 = bitcast i8* %call12 to i64*, !dbg !1042
  store i64* %6, i64** @threads, align 8, !dbg !1043
  %7 = load i64*, i64** @threads, align 8, !dbg !1044
  %cmp13 = icmp eq i64* %7, null, !dbg !1046
  br i1 %cmp13, label %if.then15, label %if.end16, !dbg !1047

if.then15:                                        ; preds = %if.then10
  store i32 4, i32* @nthreads, align 4, !dbg !1048
  store i64* getelementptr inbounds ([4 x i64], [4 x i64]* @default_threads, i32 0, i32 0), i64** @threads, align 8, !dbg !1050
  br label %if.end16, !dbg !1051

if.end16:                                         ; preds = %if.then15, %if.then10
  br label %if.end17, !dbg !1052

if.end17:                                         ; preds = %if.end16, %if.end7
  %call18 = call i32 @uv_cond_init(%union.pthread_cond_t* @cond), !dbg !1053
  %tobool = icmp ne i32 %call18, 0, !dbg !1053
  br i1 %tobool, label %if.then19, label %if.end20, !dbg !1055

if.then19:                                        ; preds = %if.end17
  call void @abort() #7, !dbg !1056
  unreachable, !dbg !1056

if.end20:                                         ; preds = %if.end17
  %call21 = call i32 @uv_mutex_init(%union.pthread_mutex_t* @mutex), !dbg !1057
  %tobool22 = icmp ne i32 %call21, 0, !dbg !1057
  br i1 %tobool22, label %if.then23, label %if.end24, !dbg !1059

if.then23:                                        ; preds = %if.end20
  call void @abort() #7, !dbg !1060
  unreachable, !dbg !1060

if.end24:                                         ; preds = %if.end20
  br label %do.body, !dbg !1061

do.body:                                          ; preds = %if.end24
  store [2 x i8*]* @wq, [2 x i8*]** bitcast ([2 x i8*]* @wq to [2 x i8*]**), align 16, !dbg !1062
  store [2 x i8*]* @wq, [2 x i8*]** bitcast (i8** getelementptr inbounds ([2 x i8*], [2 x i8*]* @wq, i64 0, i64 1) to [2 x i8*]**), align 8, !dbg !1062
  br label %do.end, !dbg !1062

do.end:                                           ; preds = %do.body
  store i32 0, i32* %i, align 4, !dbg !1065
  br label %for.cond, !dbg !1067

for.cond:                                         ; preds = %for.inc, %do.end
  %8 = load i32, i32* %i, align 4, !dbg !1068
  %9 = load i32, i32* @nthreads, align 4, !dbg !1071
  %cmp25 = icmp ult i32 %8, %9, !dbg !1072
  br i1 %cmp25, label %for.body, label %for.end, !dbg !1073

for.body:                                         ; preds = %for.cond
  %10 = load i64*, i64** @threads, align 8, !dbg !1074
  %11 = load i32, i32* %i, align 4, !dbg !1076
  %idx.ext = zext i32 %11 to i64, !dbg !1077
  %add.ptr = getelementptr inbounds i64, i64* %10, i64 %idx.ext, !dbg !1077
  %call27 = call i32 @uv_thread_create(i64* %add.ptr, void (i8*)* @worker, i8* null), !dbg !1078
  %tobool28 = icmp ne i32 %call27, 0, !dbg !1078
  br i1 %tobool28, label %if.then29, label %if.end30, !dbg !1079

if.then29:                                        ; preds = %for.body
  call void @abort() #7, !dbg !1080
  unreachable, !dbg !1080

if.end30:                                         ; preds = %for.body
  br label %for.inc, !dbg !1081

for.inc:                                          ; preds = %if.end30
  %12 = load i32, i32* %i, align 4, !dbg !1083
  %inc = add i32 %12, 1, !dbg !1083
  store i32 %inc, i32* %i, align 4, !dbg !1083
  br label %for.cond, !dbg !1085

for.end:                                          ; preds = %for.cond
  store volatile i32 1, i32* @initialized, align 4, !dbg !1086
  ret void, !dbg !1087
}

; Function Attrs: argmemonly nounwind
declare void @llvm.memcpy.p0i8.p0i8.i64(i8* nocapture, i8* nocapture readonly, i64, i32, i1) #5

; Function Attrs: nounwind
declare i8* @getenv(i8*) #4

; Function Attrs: nounwind readonly
declare i32 @atoi(i8*) #6

declare i8* @uv__malloc(i64) #2

declare i32 @uv_cond_init(%union.pthread_cond_t*) #2

declare i32 @uv_mutex_init(%union.pthread_mutex_t*) #2

declare i32 @uv_thread_create(i64*, void (i8*)*, i8*) #2

; Function Attrs: nounwind uwtable
define internal void @worker(i8* %arg) #0 !dbg !590 {
entry:
  %arg.addr = alloca i8*, align 8
  %w = alloca %struct.uv__work*, align 8
  %q = alloca [2 x i8*]*, align 8
  store i8* %arg, i8** %arg.addr, align 8
  call void @llvm.dbg.declare(metadata i8** %arg.addr, metadata !1088, metadata !643), !dbg !1089
  call void @llvm.dbg.declare(metadata %struct.uv__work** %w, metadata !1090, metadata !643), !dbg !1091
  call void @llvm.dbg.declare(metadata [2 x i8*]** %q, metadata !1092, metadata !643), !dbg !1093
  %0 = load i8*, i8** %arg.addr, align 8, !dbg !1094
  br label %for.cond, !dbg !1095

for.cond:                                         ; preds = %do.end32, %entry
  call void @uv_mutex_lock(%union.pthread_mutex_t* @mutex), !dbg !1096
  br label %while.cond, !dbg !1100

while.cond:                                       ; preds = %while.body, %for.cond
  %1 = load [2 x i8*]*, [2 x i8*]** bitcast ([2 x i8*]* @wq to [2 x i8*]**), align 16, !dbg !1101
  %cmp = icmp eq [2 x i8*]* @wq, %1, !dbg !1101
  br i1 %cmp, label %while.body, label %while.end, !dbg !1103

while.body:                                       ; preds = %while.cond
  %2 = load i32, i32* @idle_threads, align 4, !dbg !1104
  %add = add i32 %2, 1, !dbg !1104
  store i32 %add, i32* @idle_threads, align 4, !dbg !1104
  call void @uv_cond_wait(%union.pthread_cond_t* @cond, %union.pthread_mutex_t* @mutex), !dbg !1106
  %3 = load i32, i32* @idle_threads, align 4, !dbg !1107
  %sub = sub i32 %3, 1, !dbg !1107
  store i32 %sub, i32* @idle_threads, align 4, !dbg !1107
  br label %while.cond, !dbg !1108

while.end:                                        ; preds = %while.cond
  %4 = load [2 x i8*]*, [2 x i8*]** bitcast ([2 x i8*]* @wq to [2 x i8*]**), align 16, !dbg !1110
  store [2 x i8*]* %4, [2 x i8*]** %q, align 8, !dbg !1111
  %5 = load [2 x i8*]*, [2 x i8*]** %q, align 8, !dbg !1112
  %cmp1 = icmp eq [2 x i8*]* %5, @exit_message, !dbg !1114
  br i1 %cmp1, label %if.then, label %if.else, !dbg !1115

if.then:                                          ; preds = %while.end
  call void @uv_cond_signal(%union.pthread_cond_t* @cond), !dbg !1116
  br label %if.end, !dbg !1116

if.else:                                          ; preds = %while.end
  br label %do.body, !dbg !1117

do.body:                                          ; preds = %if.else
  %6 = load [2 x i8*]*, [2 x i8*]** %q, align 8, !dbg !1119
  %arrayidx = getelementptr inbounds [2 x i8*], [2 x i8*]* %6, i64 0, i64 0, !dbg !1119
  %7 = bitcast i8** %arrayidx to [2 x i8*]**, !dbg !1119
  %8 = load [2 x i8*]*, [2 x i8*]** %7, align 8, !dbg !1119
  %9 = load [2 x i8*]*, [2 x i8*]** %q, align 8, !dbg !1119
  %arrayidx2 = getelementptr inbounds [2 x i8*], [2 x i8*]* %9, i64 0, i64 1, !dbg !1119
  %10 = bitcast i8** %arrayidx2 to [2 x i8*]**, !dbg !1119
  %11 = load [2 x i8*]*, [2 x i8*]** %10, align 8, !dbg !1119
  %arrayidx3 = getelementptr inbounds [2 x i8*], [2 x i8*]* %11, i64 0, i64 0, !dbg !1119
  %12 = bitcast i8** %arrayidx3 to [2 x i8*]**, !dbg !1119
  store [2 x i8*]* %8, [2 x i8*]** %12, align 8, !dbg !1119
  %13 = load [2 x i8*]*, [2 x i8*]** %q, align 8, !dbg !1119
  %arrayidx4 = getelementptr inbounds [2 x i8*], [2 x i8*]* %13, i64 0, i64 1, !dbg !1119
  %14 = bitcast i8** %arrayidx4 to [2 x i8*]**, !dbg !1119
  %15 = load [2 x i8*]*, [2 x i8*]** %14, align 8, !dbg !1119
  %16 = load [2 x i8*]*, [2 x i8*]** %q, align 8, !dbg !1119
  %arrayidx5 = getelementptr inbounds [2 x i8*], [2 x i8*]* %16, i64 0, i64 0, !dbg !1119
  %17 = bitcast i8** %arrayidx5 to [2 x i8*]**, !dbg !1119
  %18 = load [2 x i8*]*, [2 x i8*]** %17, align 8, !dbg !1119
  %arrayidx6 = getelementptr inbounds [2 x i8*], [2 x i8*]* %18, i64 0, i64 1, !dbg !1119
  %19 = bitcast i8** %arrayidx6 to [2 x i8*]**, !dbg !1119
  store [2 x i8*]* %15, [2 x i8*]** %19, align 8, !dbg !1119
  br label %do.end, !dbg !1119

do.end:                                           ; preds = %do.body
  br label %do.body7, !dbg !1122

do.body7:                                         ; preds = %do.end
  %20 = load [2 x i8*]*, [2 x i8*]** %q, align 8, !dbg !1123
  %21 = load [2 x i8*]*, [2 x i8*]** %q, align 8, !dbg !1123
  %arrayidx8 = getelementptr inbounds [2 x i8*], [2 x i8*]* %21, i64 0, i64 0, !dbg !1123
  %22 = bitcast i8** %arrayidx8 to [2 x i8*]**, !dbg !1123
  store [2 x i8*]* %20, [2 x i8*]** %22, align 8, !dbg !1123
  %23 = load [2 x i8*]*, [2 x i8*]** %q, align 8, !dbg !1123
  %24 = load [2 x i8*]*, [2 x i8*]** %q, align 8, !dbg !1123
  %arrayidx9 = getelementptr inbounds [2 x i8*], [2 x i8*]* %24, i64 0, i64 1, !dbg !1123
  %25 = bitcast i8** %arrayidx9 to [2 x i8*]**, !dbg !1123
  store [2 x i8*]* %23, [2 x i8*]** %25, align 8, !dbg !1123
  br label %do.end10, !dbg !1123

do.end10:                                         ; preds = %do.body7
  br label %if.end

if.end:                                           ; preds = %do.end10, %if.then
  call void @uv_mutex_unlock(%union.pthread_mutex_t* @mutex), !dbg !1126
  %26 = load [2 x i8*]*, [2 x i8*]** %q, align 8, !dbg !1127
  %cmp11 = icmp eq [2 x i8*]* %26, @exit_message, !dbg !1129
  br i1 %cmp11, label %if.then12, label %if.end13, !dbg !1130

if.then12:                                        ; preds = %if.end
  br label %for.end, !dbg !1131

if.end13:                                         ; preds = %if.end
  %27 = load [2 x i8*]*, [2 x i8*]** %q, align 8, !dbg !1132
  %28 = bitcast [2 x i8*]* %27 to i8*, !dbg !1132
  %add.ptr = getelementptr inbounds i8, i8* %28, i64 -24, !dbg !1132
  %29 = bitcast i8* %add.ptr to %struct.uv__work*, !dbg !1132
  store %struct.uv__work* %29, %struct.uv__work** %w, align 8, !dbg !1133
  %30 = load %struct.uv__work*, %struct.uv__work** %w, align 8, !dbg !1134
  %work = getelementptr inbounds %struct.uv__work, %struct.uv__work* %30, i32 0, i32 0, !dbg !1135
  %31 = load void (%struct.uv__work*)*, void (%struct.uv__work*)** %work, align 8, !dbg !1135
  %32 = load %struct.uv__work*, %struct.uv__work** %w, align 8, !dbg !1136
  call void %31(%struct.uv__work* %32), !dbg !1134
  %33 = load %struct.uv__work*, %struct.uv__work** %w, align 8, !dbg !1137
  %loop = getelementptr inbounds %struct.uv__work, %struct.uv__work* %33, i32 0, i32 2, !dbg !1138
  %34 = load %struct.uv_loop_s*, %struct.uv_loop_s** %loop, align 8, !dbg !1138
  %wq_mutex = getelementptr inbounds %struct.uv_loop_s, %struct.uv_loop_s* %34, i32 0, i32 13, !dbg !1139
  call void @uv_mutex_lock(%union.pthread_mutex_t* %wq_mutex), !dbg !1140
  %35 = load %struct.uv__work*, %struct.uv__work** %w, align 8, !dbg !1141
  %work14 = getelementptr inbounds %struct.uv__work, %struct.uv__work* %35, i32 0, i32 0, !dbg !1142
  store void (%struct.uv__work*)* null, void (%struct.uv__work*)** %work14, align 8, !dbg !1143
  br label %do.body15, !dbg !1144

do.body15:                                        ; preds = %if.end13
  %36 = load %struct.uv__work*, %struct.uv__work** %w, align 8, !dbg !1145
  %loop16 = getelementptr inbounds %struct.uv__work, %struct.uv__work* %36, i32 0, i32 2, !dbg !1145
  %37 = load %struct.uv_loop_s*, %struct.uv_loop_s** %loop16, align 8, !dbg !1145
  %wq = getelementptr inbounds %struct.uv_loop_s, %struct.uv_loop_s* %37, i32 0, i32 12, !dbg !1145
  %38 = load %struct.uv__work*, %struct.uv__work** %w, align 8, !dbg !1145
  %wq17 = getelementptr inbounds %struct.uv__work, %struct.uv__work* %38, i32 0, i32 3, !dbg !1145
  %arrayidx18 = getelementptr inbounds [2 x i8*], [2 x i8*]* %wq17, i64 0, i64 0, !dbg !1145
  %39 = bitcast i8** %arrayidx18 to [2 x i8*]**, !dbg !1145
  store [2 x i8*]* %wq, [2 x i8*]** %39, align 8, !dbg !1145
  %40 = load %struct.uv__work*, %struct.uv__work** %w, align 8, !dbg !1145
  %loop19 = getelementptr inbounds %struct.uv__work, %struct.uv__work* %40, i32 0, i32 2, !dbg !1145
  %41 = load %struct.uv_loop_s*, %struct.uv_loop_s** %loop19, align 8, !dbg !1145
  %wq20 = getelementptr inbounds %struct.uv_loop_s, %struct.uv_loop_s* %41, i32 0, i32 12, !dbg !1145
  %arrayidx21 = getelementptr inbounds [2 x i8*], [2 x i8*]* %wq20, i64 0, i64 1, !dbg !1145
  %42 = bitcast i8** %arrayidx21 to [2 x i8*]**, !dbg !1145
  %43 = load [2 x i8*]*, [2 x i8*]** %42, align 8, !dbg !1145
  %44 = load %struct.uv__work*, %struct.uv__work** %w, align 8, !dbg !1145
  %wq22 = getelementptr inbounds %struct.uv__work, %struct.uv__work* %44, i32 0, i32 3, !dbg !1145
  %arrayidx23 = getelementptr inbounds [2 x i8*], [2 x i8*]* %wq22, i64 0, i64 1, !dbg !1145
  %45 = bitcast i8** %arrayidx23 to [2 x i8*]**, !dbg !1145
  store [2 x i8*]* %43, [2 x i8*]** %45, align 8, !dbg !1145
  %46 = load %struct.uv__work*, %struct.uv__work** %w, align 8, !dbg !1145
  %wq24 = getelementptr inbounds %struct.uv__work, %struct.uv__work* %46, i32 0, i32 3, !dbg !1145
  %47 = load %struct.uv__work*, %struct.uv__work** %w, align 8, !dbg !1145
  %wq25 = getelementptr inbounds %struct.uv__work, %struct.uv__work* %47, i32 0, i32 3, !dbg !1145
  %arrayidx26 = getelementptr inbounds [2 x i8*], [2 x i8*]* %wq25, i64 0, i64 1, !dbg !1145
  %48 = bitcast i8** %arrayidx26 to [2 x i8*]**, !dbg !1145
  %49 = load [2 x i8*]*, [2 x i8*]** %48, align 8, !dbg !1145
  %arrayidx27 = getelementptr inbounds [2 x i8*], [2 x i8*]* %49, i64 0, i64 0, !dbg !1145
  %50 = bitcast i8** %arrayidx27 to [2 x i8*]**, !dbg !1145
  store [2 x i8*]* %wq24, [2 x i8*]** %50, align 8, !dbg !1145
  %51 = load %struct.uv__work*, %struct.uv__work** %w, align 8, !dbg !1145
  %wq28 = getelementptr inbounds %struct.uv__work, %struct.uv__work* %51, i32 0, i32 3, !dbg !1145
  %52 = load %struct.uv__work*, %struct.uv__work** %w, align 8, !dbg !1145
  %loop29 = getelementptr inbounds %struct.uv__work, %struct.uv__work* %52, i32 0, i32 2, !dbg !1145
  %53 = load %struct.uv_loop_s*, %struct.uv_loop_s** %loop29, align 8, !dbg !1145
  %wq30 = getelementptr inbounds %struct.uv_loop_s, %struct.uv_loop_s* %53, i32 0, i32 12, !dbg !1145
  %arrayidx31 = getelementptr inbounds [2 x i8*], [2 x i8*]* %wq30, i64 0, i64 1, !dbg !1145
  %54 = bitcast i8** %arrayidx31 to [2 x i8*]**, !dbg !1145
  store [2 x i8*]* %wq28, [2 x i8*]** %54, align 8, !dbg !1145
  br label %do.end32, !dbg !1145

do.end32:                                         ; preds = %do.body15
  %55 = load %struct.uv__work*, %struct.uv__work** %w, align 8, !dbg !1148
  %loop33 = getelementptr inbounds %struct.uv__work, %struct.uv__work* %55, i32 0, i32 2, !dbg !1149
  %56 = load %struct.uv_loop_s*, %struct.uv_loop_s** %loop33, align 8, !dbg !1149
  %wq_async = getelementptr inbounds %struct.uv_loop_s, %struct.uv_loop_s* %56, i32 0, i32 14, !dbg !1150
  %call = call i32 @uv_async_send(%struct.uv_async_s* %wq_async), !dbg !1151
  %57 = load %struct.uv__work*, %struct.uv__work** %w, align 8, !dbg !1152
  %loop34 = getelementptr inbounds %struct.uv__work, %struct.uv__work* %57, i32 0, i32 2, !dbg !1153
  %58 = load %struct.uv_loop_s*, %struct.uv_loop_s** %loop34, align 8, !dbg !1153
  %wq_mutex35 = getelementptr inbounds %struct.uv_loop_s, %struct.uv_loop_s* %58, i32 0, i32 13, !dbg !1154
  call void @uv_mutex_unlock(%union.pthread_mutex_t* %wq_mutex35), !dbg !1155
  br label %for.cond, !dbg !1156

for.end:                                          ; preds = %if.then12
  ret void, !dbg !1158
}

declare void @uv_cond_wait(%union.pthread_cond_t*, %union.pthread_mutex_t*) #2

declare i32 @uv_async_send(%struct.uv_async_s*) #2

; Function Attrs: noreturn nounwind
declare void @__assert_fail(i8*, i8*, i32, i8*) #3

attributes #0 = { nounwind uwtable "disable-tail-calls"="false" "less-precise-fpmad"="false" "no-frame-pointer-elim"="true" "no-frame-pointer-elim-non-leaf" "no-infs-fp-math"="false" "no-nans-fp-math"="false" "stack-protector-buffer-size"="8" "target-cpu"="x86-64" "target-features"="+fxsr,+mmx,+sse,+sse2" "unsafe-fp-math"="false" "use-soft-float"="false" }
attributes #1 = { nounwind readnone }
attributes #2 = { "disable-tail-calls"="false" "less-precise-fpmad"="false" "no-frame-pointer-elim"="true" "no-frame-pointer-elim-non-leaf" "no-infs-fp-math"="false" "no-nans-fp-math"="false" "stack-protector-buffer-size"="8" "target-cpu"="x86-64" "target-features"="+fxsr,+mmx,+sse,+sse2" "unsafe-fp-math"="false" "use-soft-float"="false" }
attributes #3 = { noreturn nounwind "disable-tail-calls"="false" "less-precise-fpmad"="false" "no-frame-pointer-elim"="true" "no-frame-pointer-elim-non-leaf" "no-infs-fp-math"="false" "no-nans-fp-math"="false" "stack-protector-buffer-size"="8" "target-cpu"="x86-64" "target-features"="+fxsr,+mmx,+sse,+sse2" "unsafe-fp-math"="false" "use-soft-float"="false" }
attributes #4 = { nounwind "disable-tail-calls"="false" "less-precise-fpmad"="false" "no-frame-pointer-elim"="true" "no-frame-pointer-elim-non-leaf" "no-infs-fp-math"="false" "no-nans-fp-math"="false" "stack-protector-buffer-size"="8" "target-cpu"="x86-64" "target-features"="+fxsr,+mmx,+sse,+sse2" "unsafe-fp-math"="false" "use-soft-float"="false" }
attributes #5 = { argmemonly nounwind }
attributes #6 = { nounwind readonly "disable-tail-calls"="false" "less-precise-fpmad"="false" "no-frame-pointer-elim"="true" "no-frame-pointer-elim-non-leaf" "no-infs-fp-math"="false" "no-nans-fp-math"="false" "stack-protector-buffer-size"="8" "target-cpu"="x86-64" "target-features"="+fxsr,+mmx,+sse,+sse2" "unsafe-fp-math"="false" "use-soft-float"="false" }
attributes #7 = { noreturn nounwind }
attributes #8 = { nounwind }
attributes #9 = { nounwind readonly }

!llvm.dbg.cu = !{!0}
!llvm.module.flags = !{!639, !640}
!llvm.ident = !{!641}

!0 = distinct !DICompileUnit(language: DW_LANG_C99, file: !1, producer: "clang version 3.8.0 (tags/RELEASE_380/final)", isOptimized: false, runtimeVersion: 0, emissionKind: 1, enums: !2, retainedTypes: !149, subprograms: !563, globals: !599)
!1 = !DIFile(filename: "/data/download/cmake/cmake-master/Utilities/cmlibuv/src/threadpool.c", directory: "/data/download/cmake/cmake-master/Utilities/cmlibuv")
!2 = !{!3, !25, !104, !117}
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
!25 = !DICompositeType(tag: DW_TAG_enumeration_type, file: !4, line: 177, size: 32, align: 32, elements: !26)
!26 = !{!27, !28, !29, !30, !31, !32, !33, !34, !35, !36, !37, !38, !39, !40, !41, !42, !43, !44, !45, !46, !47, !48, !49, !50, !51, !52, !53, !54, !55, !56, !57, !58, !59, !60, !61, !62, !63, !64, !65, !66, !67, !68, !69, !70, !71, !72, !73, !74, !75, !76, !77, !78, !79, !80, !81, !82, !83, !84, !85, !86, !87, !88, !89, !90, !91, !92, !93, !94, !95, !96, !97, !98, !99, !100, !101, !102, !103}
!27 = !DIEnumerator(name: "UV_E2BIG", value: -7)
!28 = !DIEnumerator(name: "UV_EACCES", value: -13)
!29 = !DIEnumerator(name: "UV_EADDRINUSE", value: -98)
!30 = !DIEnumerator(name: "UV_EADDRNOTAVAIL", value: -99)
!31 = !DIEnumerator(name: "UV_EAFNOSUPPORT", value: -97)
!32 = !DIEnumerator(name: "UV_EAGAIN", value: -11)
!33 = !DIEnumerator(name: "UV_EAI_ADDRFAMILY", value: -3000)
!34 = !DIEnumerator(name: "UV_EAI_AGAIN", value: -3001)
!35 = !DIEnumerator(name: "UV_EAI_BADFLAGS", value: -3002)
!36 = !DIEnumerator(name: "UV_EAI_BADHINTS", value: -3013)
!37 = !DIEnumerator(name: "UV_EAI_CANCELED", value: -3003)
!38 = !DIEnumerator(name: "UV_EAI_FAIL", value: -3004)
!39 = !DIEnumerator(name: "UV_EAI_FAMILY", value: -3005)
!40 = !DIEnumerator(name: "UV_EAI_MEMORY", value: -3006)
!41 = !DIEnumerator(name: "UV_EAI_NODATA", value: -3007)
!42 = !DIEnumerator(name: "UV_EAI_NONAME", value: -3008)
!43 = !DIEnumerator(name: "UV_EAI_OVERFLOW", value: -3009)
!44 = !DIEnumerator(name: "UV_EAI_PROTOCOL", value: -3014)
!45 = !DIEnumerator(name: "UV_EAI_SERVICE", value: -3010)
!46 = !DIEnumerator(name: "UV_EAI_SOCKTYPE", value: -3011)
!47 = !DIEnumerator(name: "UV_EALREADY", value: -114)
!48 = !DIEnumerator(name: "UV_EBADF", value: -9)
!49 = !DIEnumerator(name: "UV_EBUSY", value: -16)
!50 = !DIEnumerator(name: "UV_ECANCELED", value: -125)
!51 = !DIEnumerator(name: "UV_ECHARSET", value: -4080)
!52 = !DIEnumerator(name: "UV_ECONNABORTED", value: -103)
!53 = !DIEnumerator(name: "UV_ECONNREFUSED", value: -111)
!54 = !DIEnumerator(name: "UV_ECONNRESET", value: -104)
!55 = !DIEnumerator(name: "UV_EDESTADDRREQ", value: -89)
!56 = !DIEnumerator(name: "UV_EEXIST", value: -17)
!57 = !DIEnumerator(name: "UV_EFAULT", value: -14)
!58 = !DIEnumerator(name: "UV_EFBIG", value: -27)
!59 = !DIEnumerator(name: "UV_EHOSTUNREACH", value: -113)
!60 = !DIEnumerator(name: "UV_EINTR", value: -4)
!61 = !DIEnumerator(name: "UV_EINVAL", value: -22)
!62 = !DIEnumerator(name: "UV_EIO", value: -5)
!63 = !DIEnumerator(name: "UV_EISCONN", value: -106)
!64 = !DIEnumerator(name: "UV_EISDIR", value: -21)
!65 = !DIEnumerator(name: "UV_ELOOP", value: -40)
!66 = !DIEnumerator(name: "UV_EMFILE", value: -24)
!67 = !DIEnumerator(name: "UV_EMSGSIZE", value: -90)
!68 = !DIEnumerator(name: "UV_ENAMETOOLONG", value: -36)
!69 = !DIEnumerator(name: "UV_ENETDOWN", value: -100)
!70 = !DIEnumerator(name: "UV_ENETUNREACH", value: -101)
!71 = !DIEnumerator(name: "UV_ENFILE", value: -23)
!72 = !DIEnumerator(name: "UV_ENOBUFS", value: -105)
!73 = !DIEnumerator(name: "UV_ENODEV", value: -19)
!74 = !DIEnumerator(name: "UV_ENOENT", value: -2)
!75 = !DIEnumerator(name: "UV_ENOMEM", value: -12)
!76 = !DIEnumerator(name: "UV_ENONET", value: -64)
!77 = !DIEnumerator(name: "UV_ENOPROTOOPT", value: -92)
!78 = !DIEnumerator(name: "UV_ENOSPC", value: -28)
!79 = !DIEnumerator(name: "UV_ENOSYS", value: -38)
!80 = !DIEnumerator(name: "UV_ENOTCONN", value: -107)
!81 = !DIEnumerator(name: "UV_ENOTDIR", value: -20)
!82 = !DIEnumerator(name: "UV_ENOTEMPTY", value: -39)
!83 = !DIEnumerator(name: "UV_ENOTSOCK", value: -88)
!84 = !DIEnumerator(name: "UV_ENOTSUP", value: -95)
!85 = !DIEnumerator(name: "UV_EPERM", value: -1)
!86 = !DIEnumerator(name: "UV_EPIPE", value: -32)
!87 = !DIEnumerator(name: "UV_EPROTO", value: -71)
!88 = !DIEnumerator(name: "UV_EPROTONOSUPPORT", value: -93)
!89 = !DIEnumerator(name: "UV_EPROTOTYPE", value: -91)
!90 = !DIEnumerator(name: "UV_ERANGE", value: -34)
!91 = !DIEnumerator(name: "UV_EROFS", value: -30)
!92 = !DIEnumerator(name: "UV_ESHUTDOWN", value: -108)
!93 = !DIEnumerator(name: "UV_ESPIPE", value: -29)
!94 = !DIEnumerator(name: "UV_ESRCH", value: -3)
!95 = !DIEnumerator(name: "UV_ETIMEDOUT", value: -110)
!96 = !DIEnumerator(name: "UV_ETXTBSY", value: -26)
!97 = !DIEnumerator(name: "UV_EXDEV", value: -18)
!98 = !DIEnumerator(name: "UV_UNKNOWN", value: -4094)
!99 = !DIEnumerator(name: "UV_EOF", value: -4095)
!100 = !DIEnumerator(name: "UV_ENXIO", value: -6)
!101 = !DIEnumerator(name: "UV_EMLINK", value: -31)
!102 = !DIEnumerator(name: "UV_EHOSTDOWN", value: -112)
!103 = !DIEnumerator(name: "UV_ERRNO_MAX", value: -4096)
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
!117 = !DICompositeType(tag: DW_TAG_enumeration_type, file: !4, line: 1086, size: 32, align: 32, elements: !118)
!118 = !{!119, !120, !121, !122, !123, !124, !125, !126, !127, !128, !129, !130, !131, !132, !133, !134, !135, !136, !137, !138, !139, !140, !141, !142, !143, !144, !145, !146, !147, !148}
!119 = !DIEnumerator(name: "UV_FS_UNKNOWN", value: -1)
!120 = !DIEnumerator(name: "UV_FS_CUSTOM", value: 0)
!121 = !DIEnumerator(name: "UV_FS_OPEN", value: 1)
!122 = !DIEnumerator(name: "UV_FS_CLOSE", value: 2)
!123 = !DIEnumerator(name: "UV_FS_READ", value: 3)
!124 = !DIEnumerator(name: "UV_FS_WRITE", value: 4)
!125 = !DIEnumerator(name: "UV_FS_SENDFILE", value: 5)
!126 = !DIEnumerator(name: "UV_FS_STAT", value: 6)
!127 = !DIEnumerator(name: "UV_FS_LSTAT", value: 7)
!128 = !DIEnumerator(name: "UV_FS_FSTAT", value: 8)
!129 = !DIEnumerator(name: "UV_FS_FTRUNCATE", value: 9)
!130 = !DIEnumerator(name: "UV_FS_UTIME", value: 10)
!131 = !DIEnumerator(name: "UV_FS_FUTIME", value: 11)
!132 = !DIEnumerator(name: "UV_FS_ACCESS", value: 12)
!133 = !DIEnumerator(name: "UV_FS_CHMOD", value: 13)
!134 = !DIEnumerator(name: "UV_FS_FCHMOD", value: 14)
!135 = !DIEnumerator(name: "UV_FS_FSYNC", value: 15)
!136 = !DIEnumerator(name: "UV_FS_FDATASYNC", value: 16)
!137 = !DIEnumerator(name: "UV_FS_UNLINK", value: 17)
!138 = !DIEnumerator(name: "UV_FS_RMDIR", value: 18)
!139 = !DIEnumerator(name: "UV_FS_MKDIR", value: 19)
!140 = !DIEnumerator(name: "UV_FS_MKDTEMP", value: 20)
!141 = !DIEnumerator(name: "UV_FS_RENAME", value: 21)
!142 = !DIEnumerator(name: "UV_FS_SCANDIR", value: 22)
!143 = !DIEnumerator(name: "UV_FS_LINK", value: 23)
!144 = !DIEnumerator(name: "UV_FS_SYMLINK", value: 24)
!145 = !DIEnumerator(name: "UV_FS_READLINK", value: 25)
!146 = !DIEnumerator(name: "UV_FS_CHOWN", value: 26)
!147 = !DIEnumerator(name: "UV_FS_FCHOWN", value: 27)
!148 = !DIEnumerator(name: "UV_FS_REALPATH", value: 28)
!149 = !{!150, !356, !357, !361, !363, !155, !377, !463, !509, !543}
!150 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !151, size: 64, align: 64)
!151 = !DIDerivedType(tag: DW_TAG_typedef, name: "uv_loop_t", file: !4, line: 204, baseType: !152)
!152 = !DICompositeType(tag: DW_TAG_structure_type, name: "uv_loop_s", file: !4, line: 1473, size: 6784, align: 64, elements: !153)
!153 = !{!154, !156, !158, !162, !163, !164, !166, !168, !169, !170, !189, !190, !191, !192, !223, !271, !295, !296, !297, !298, !299, !300, !301, !305, !306, !307, !312, !315, !316, !318, !319, !352, !353, !354, !355}
!154 = !DIDerivedType(tag: DW_TAG_member, name: "data", scope: !152, file: !4, line: 1475, baseType: !155, size: 64, align: 64)
!155 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: null, size: 64, align: 64)
!156 = !DIDerivedType(tag: DW_TAG_member, name: "active_handles", scope: !152, file: !4, line: 1477, baseType: !157, size: 32, align: 32, offset: 64)
!157 = !DIBasicType(name: "unsigned int", size: 32, align: 32, encoding: DW_ATE_unsigned)
!158 = !DIDerivedType(tag: DW_TAG_member, name: "handle_queue", scope: !152, file: !4, line: 1478, baseType: !159, size: 128, align: 64, offset: 128)
!159 = !DICompositeType(tag: DW_TAG_array_type, baseType: !155, size: 128, align: 64, elements: !160)
!160 = !{!161}
!161 = !DISubrange(count: 2)
!162 = !DIDerivedType(tag: DW_TAG_member, name: "active_reqs", scope: !152, file: !4, line: 1479, baseType: !159, size: 128, align: 64, offset: 256)
!163 = !DIDerivedType(tag: DW_TAG_member, name: "stop_flag", scope: !152, file: !4, line: 1481, baseType: !157, size: 32, align: 32, offset: 384)
!164 = !DIDerivedType(tag: DW_TAG_member, name: "flags", scope: !152, file: !4, line: 1482, baseType: !165, size: 64, align: 64, offset: 448)
!165 = !DIBasicType(name: "long unsigned int", size: 64, align: 64, encoding: DW_ATE_unsigned)
!166 = !DIDerivedType(tag: DW_TAG_member, name: "backend_fd", scope: !152, file: !4, line: 1482, baseType: !167, size: 32, align: 32, offset: 512)
!167 = !DIBasicType(name: "int", size: 32, align: 32, encoding: DW_ATE_signed)
!168 = !DIDerivedType(tag: DW_TAG_member, name: "pending_queue", scope: !152, file: !4, line: 1482, baseType: !159, size: 128, align: 64, offset: 576)
!169 = !DIDerivedType(tag: DW_TAG_member, name: "watcher_queue", scope: !152, file: !4, line: 1482, baseType: !159, size: 128, align: 64, offset: 704)
!170 = !DIDerivedType(tag: DW_TAG_member, name: "watchers", scope: !152, file: !4, line: 1482, baseType: !171, size: 64, align: 64, offset: 832)
!171 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !172, size: 64, align: 64)
!172 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !173, size: 64, align: 64)
!173 = !DIDerivedType(tag: DW_TAG_typedef, name: "uv__io_t", file: !174, line: 87, baseType: !175)
!174 = !DIFile(filename: "/data/download/cmake/cmake-master/Utilities/cmlibuv/include/uv-unix.h", directory: "/data/download/cmake/cmake-master/Utilities/cmlibuv")
!175 = !DICompositeType(tag: DW_TAG_structure_type, name: "uv__io_s", file: !174, line: 89, size: 448, align: 64, elements: !176)
!176 = !{!177, !184, !185, !186, !187, !188}
!177 = !DIDerivedType(tag: DW_TAG_member, name: "cb", scope: !175, file: !174, line: 90, baseType: !178, size: 64, align: 64)
!178 = !DIDerivedType(tag: DW_TAG_typedef, name: "uv__io_cb", file: !174, line: 84, baseType: !179)
!179 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !180, size: 64, align: 64)
!180 = !DISubroutineType(types: !181)
!181 = !{null, !182, !183, !157}
!182 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !152, size: 64, align: 64)
!183 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !175, size: 64, align: 64)
!184 = !DIDerivedType(tag: DW_TAG_member, name: "pending_queue", scope: !175, file: !174, line: 91, baseType: !159, size: 128, align: 64, offset: 64)
!185 = !DIDerivedType(tag: DW_TAG_member, name: "watcher_queue", scope: !175, file: !174, line: 92, baseType: !159, size: 128, align: 64, offset: 192)
!186 = !DIDerivedType(tag: DW_TAG_member, name: "pevents", scope: !175, file: !174, line: 93, baseType: !157, size: 32, align: 32, offset: 320)
!187 = !DIDerivedType(tag: DW_TAG_member, name: "events", scope: !175, file: !174, line: 94, baseType: !157, size: 32, align: 32, offset: 352)
!188 = !DIDerivedType(tag: DW_TAG_member, name: "fd", scope: !175, file: !174, line: 95, baseType: !167, size: 32, align: 32, offset: 384)
!189 = !DIDerivedType(tag: DW_TAG_member, name: "nwatchers", scope: !152, file: !4, line: 1482, baseType: !157, size: 32, align: 32, offset: 896)
!190 = !DIDerivedType(tag: DW_TAG_member, name: "nfds", scope: !152, file: !4, line: 1482, baseType: !157, size: 32, align: 32, offset: 928)
!191 = !DIDerivedType(tag: DW_TAG_member, name: "wq", scope: !152, file: !4, line: 1482, baseType: !159, size: 128, align: 64, offset: 960)
!192 = !DIDerivedType(tag: DW_TAG_member, name: "wq_mutex", scope: !152, file: !4, line: 1482, baseType: !193, size: 320, align: 64, offset: 1088)
!193 = !DIDerivedType(tag: DW_TAG_typedef, name: "uv_mutex_t", file: !174, line: 129, baseType: !194)
!194 = !DIDerivedType(tag: DW_TAG_typedef, name: "pthread_mutex_t", file: !195, line: 127, baseType: !196)
!195 = !DIFile(filename: "/usr/include/x86_64-linux-gnu/bits/pthreadtypes.h", directory: "/data/download/cmake/cmake-master/Utilities/cmlibuv")
!196 = !DICompositeType(tag: DW_TAG_union_type, file: !195, line: 90, size: 320, align: 64, elements: !197)
!197 = !{!198, !216, !221}
!198 = !DIDerivedType(tag: DW_TAG_member, name: "__data", scope: !196, file: !195, line: 124, baseType: !199, size: 320, align: 64)
!199 = !DICompositeType(tag: DW_TAG_structure_type, name: "__pthread_mutex_s", file: !195, line: 92, size: 320, align: 64, elements: !200)
!200 = !{!201, !202, !203, !204, !205, !206, !208, !209}
!201 = !DIDerivedType(tag: DW_TAG_member, name: "__lock", scope: !199, file: !195, line: 94, baseType: !167, size: 32, align: 32)
!202 = !DIDerivedType(tag: DW_TAG_member, name: "__count", scope: !199, file: !195, line: 95, baseType: !157, size: 32, align: 32, offset: 32)
!203 = !DIDerivedType(tag: DW_TAG_member, name: "__owner", scope: !199, file: !195, line: 96, baseType: !167, size: 32, align: 32, offset: 64)
!204 = !DIDerivedType(tag: DW_TAG_member, name: "__nusers", scope: !199, file: !195, line: 98, baseType: !157, size: 32, align: 32, offset: 96)
!205 = !DIDerivedType(tag: DW_TAG_member, name: "__kind", scope: !199, file: !195, line: 102, baseType: !167, size: 32, align: 32, offset: 128)
!206 = !DIDerivedType(tag: DW_TAG_member, name: "__spins", scope: !199, file: !195, line: 104, baseType: !207, size: 16, align: 16, offset: 160)
!207 = !DIBasicType(name: "short", size: 16, align: 16, encoding: DW_ATE_signed)
!208 = !DIDerivedType(tag: DW_TAG_member, name: "__elision", scope: !199, file: !195, line: 105, baseType: !207, size: 16, align: 16, offset: 176)
!209 = !DIDerivedType(tag: DW_TAG_member, name: "__list", scope: !199, file: !195, line: 106, baseType: !210, size: 128, align: 64, offset: 192)
!210 = !DIDerivedType(tag: DW_TAG_typedef, name: "__pthread_list_t", file: !195, line: 79, baseType: !211)
!211 = !DICompositeType(tag: DW_TAG_structure_type, name: "__pthread_internal_list", file: !195, line: 75, size: 128, align: 64, elements: !212)
!212 = !{!213, !215}
!213 = !DIDerivedType(tag: DW_TAG_member, name: "__prev", scope: !211, file: !195, line: 77, baseType: !214, size: 64, align: 64)
!214 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !211, size: 64, align: 64)
!215 = !DIDerivedType(tag: DW_TAG_member, name: "__next", scope: !211, file: !195, line: 78, baseType: !214, size: 64, align: 64, offset: 64)
!216 = !DIDerivedType(tag: DW_TAG_member, name: "__size", scope: !196, file: !195, line: 125, baseType: !217, size: 320, align: 8)
!217 = !DICompositeType(tag: DW_TAG_array_type, baseType: !218, size: 320, align: 8, elements: !219)
!218 = !DIBasicType(name: "char", size: 8, align: 8, encoding: DW_ATE_signed_char)
!219 = !{!220}
!220 = !DISubrange(count: 40)
!221 = !DIDerivedType(tag: DW_TAG_member, name: "__align", scope: !196, file: !195, line: 126, baseType: !222, size: 64, align: 64)
!222 = !DIBasicType(name: "long int", size: 64, align: 64, encoding: DW_ATE_signed)
!223 = !DIDerivedType(tag: DW_TAG_member, name: "wq_async", scope: !152, file: !4, line: 1482, baseType: !224, size: 1024, align: 64, offset: 1408)
!224 = !DIDerivedType(tag: DW_TAG_typedef, name: "uv_async_t", file: !4, line: 216, baseType: !225)
!225 = !DICompositeType(tag: DW_TAG_structure_type, name: "uv_async_s", file: !4, line: 767, size: 1024, align: 64, elements: !226)
!226 = !{!227, !228, !229, !231, !255, !256, !261, !262, !263, !269, !270}
!227 = !DIDerivedType(tag: DW_TAG_member, name: "data", scope: !225, file: !4, line: 768, baseType: !155, size: 64, align: 64)
!228 = !DIDerivedType(tag: DW_TAG_member, name: "loop", scope: !225, file: !4, line: 768, baseType: !150, size: 64, align: 64, offset: 64)
!229 = !DIDerivedType(tag: DW_TAG_member, name: "type", scope: !225, file: !4, line: 768, baseType: !230, size: 32, align: 32, offset: 128)
!230 = !DIDerivedType(tag: DW_TAG_typedef, name: "uv_handle_type", file: !4, line: 191, baseType: !3)
!231 = !DIDerivedType(tag: DW_TAG_member, name: "close_cb", scope: !225, file: !4, line: 768, baseType: !232, size: 64, align: 64, offset: 192)
!232 = !DIDerivedType(tag: DW_TAG_typedef, name: "uv_close_cb", file: !4, line: 306, baseType: !233)
!233 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !234, size: 64, align: 64)
!234 = !DISubroutineType(types: !235)
!235 = !{null, !236}
!236 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !237, size: 64, align: 64)
!237 = !DIDerivedType(tag: DW_TAG_typedef, name: "uv_handle_t", file: !4, line: 205, baseType: !238)
!238 = !DICompositeType(tag: DW_TAG_structure_type, name: "uv_handle_s", file: !4, line: 425, size: 768, align: 64, elements: !239)
!239 = !{!240, !241, !242, !243, !244, !245, !253, !254}
!240 = !DIDerivedType(tag: DW_TAG_member, name: "data", scope: !238, file: !4, line: 426, baseType: !155, size: 64, align: 64)
!241 = !DIDerivedType(tag: DW_TAG_member, name: "loop", scope: !238, file: !4, line: 426, baseType: !150, size: 64, align: 64, offset: 64)
!242 = !DIDerivedType(tag: DW_TAG_member, name: "type", scope: !238, file: !4, line: 426, baseType: !230, size: 32, align: 32, offset: 128)
!243 = !DIDerivedType(tag: DW_TAG_member, name: "close_cb", scope: !238, file: !4, line: 426, baseType: !232, size: 64, align: 64, offset: 192)
!244 = !DIDerivedType(tag: DW_TAG_member, name: "handle_queue", scope: !238, file: !4, line: 426, baseType: !159, size: 128, align: 64, offset: 256)
!245 = !DIDerivedType(tag: DW_TAG_member, name: "u", scope: !238, file: !4, line: 426, baseType: !246, size: 256, align: 64, offset: 384)
!246 = !DICompositeType(tag: DW_TAG_union_type, scope: !238, file: !4, line: 426, size: 256, align: 64, elements: !247)
!247 = !{!248, !249}
!248 = !DIDerivedType(tag: DW_TAG_member, name: "fd", scope: !246, file: !4, line: 426, baseType: !167, size: 32, align: 32)
!249 = !DIDerivedType(tag: DW_TAG_member, name: "reserved", scope: !246, file: !4, line: 426, baseType: !250, size: 256, align: 64)
!250 = !DICompositeType(tag: DW_TAG_array_type, baseType: !155, size: 256, align: 64, elements: !251)
!251 = !{!252}
!252 = !DISubrange(count: 4)
!253 = !DIDerivedType(tag: DW_TAG_member, name: "next_closing", scope: !238, file: !4, line: 426, baseType: !236, size: 64, align: 64, offset: 640)
!254 = !DIDerivedType(tag: DW_TAG_member, name: "flags", scope: !238, file: !4, line: 426, baseType: !157, size: 32, align: 32, offset: 704)
!255 = !DIDerivedType(tag: DW_TAG_member, name: "handle_queue", scope: !225, file: !4, line: 768, baseType: !159, size: 128, align: 64, offset: 256)
!256 = !DIDerivedType(tag: DW_TAG_member, name: "u", scope: !225, file: !4, line: 768, baseType: !257, size: 256, align: 64, offset: 384)
!257 = !DICompositeType(tag: DW_TAG_union_type, scope: !225, file: !4, line: 768, size: 256, align: 64, elements: !258)
!258 = !{!259, !260}
!259 = !DIDerivedType(tag: DW_TAG_member, name: "fd", scope: !257, file: !4, line: 768, baseType: !167, size: 32, align: 32)
!260 = !DIDerivedType(tag: DW_TAG_member, name: "reserved", scope: !257, file: !4, line: 768, baseType: !250, size: 256, align: 64)
!261 = !DIDerivedType(tag: DW_TAG_member, name: "next_closing", scope: !225, file: !4, line: 768, baseType: !236, size: 64, align: 64, offset: 640)
!262 = !DIDerivedType(tag: DW_TAG_member, name: "flags", scope: !225, file: !4, line: 768, baseType: !157, size: 32, align: 32, offset: 704)
!263 = !DIDerivedType(tag: DW_TAG_member, name: "async_cb", scope: !225, file: !4, line: 769, baseType: !264, size: 64, align: 64, offset: 768)
!264 = !DIDerivedType(tag: DW_TAG_typedef, name: "uv_async_cb", file: !4, line: 309, baseType: !265)
!265 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !266, size: 64, align: 64)
!266 = !DISubroutineType(types: !267)
!267 = !{null, !268}
!268 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !224, size: 64, align: 64)
!269 = !DIDerivedType(tag: DW_TAG_member, name: "queue", scope: !225, file: !4, line: 769, baseType: !159, size: 128, align: 64, offset: 832)
!270 = !DIDerivedType(tag: DW_TAG_member, name: "pending", scope: !225, file: !4, line: 769, baseType: !167, size: 32, align: 32, offset: 960)
!271 = !DIDerivedType(tag: DW_TAG_member, name: "cloexec_lock", scope: !152, file: !4, line: 1482, baseType: !272, size: 448, align: 64, offset: 2432)
!272 = !DIDerivedType(tag: DW_TAG_typedef, name: "uv_rwlock_t", file: !174, line: 130, baseType: !273)
!273 = !DIDerivedType(tag: DW_TAG_typedef, name: "pthread_rwlock_t", file: !195, line: 213, baseType: !274)
!274 = !DICompositeType(tag: DW_TAG_union_type, file: !195, line: 173, size: 448, align: 64, elements: !275)
!275 = !{!276, !290, !294}
!276 = !DIDerivedType(tag: DW_TAG_member, name: "__data", scope: !274, file: !195, line: 192, baseType: !277, size: 448, align: 64)
!277 = !DICompositeType(tag: DW_TAG_structure_type, scope: !274, file: !195, line: 176, size: 448, align: 64, elements: !278)
!278 = !{!279, !280, !281, !282, !283, !284, !285, !286, !287, !288, !289}
!279 = !DIDerivedType(tag: DW_TAG_member, name: "__lock", scope: !277, file: !195, line: 178, baseType: !167, size: 32, align: 32)
!280 = !DIDerivedType(tag: DW_TAG_member, name: "__nr_readers", scope: !277, file: !195, line: 179, baseType: !157, size: 32, align: 32, offset: 32)
!281 = !DIDerivedType(tag: DW_TAG_member, name: "__readers_wakeup", scope: !277, file: !195, line: 180, baseType: !157, size: 32, align: 32, offset: 64)
!282 = !DIDerivedType(tag: DW_TAG_member, name: "__writer_wakeup", scope: !277, file: !195, line: 181, baseType: !157, size: 32, align: 32, offset: 96)
!283 = !DIDerivedType(tag: DW_TAG_member, name: "__nr_readers_queued", scope: !277, file: !195, line: 182, baseType: !157, size: 32, align: 32, offset: 128)
!284 = !DIDerivedType(tag: DW_TAG_member, name: "__nr_writers_queued", scope: !277, file: !195, line: 183, baseType: !157, size: 32, align: 32, offset: 160)
!285 = !DIDerivedType(tag: DW_TAG_member, name: "__writer", scope: !277, file: !195, line: 184, baseType: !167, size: 32, align: 32, offset: 192)
!286 = !DIDerivedType(tag: DW_TAG_member, name: "__shared", scope: !277, file: !195, line: 185, baseType: !167, size: 32, align: 32, offset: 224)
!287 = !DIDerivedType(tag: DW_TAG_member, name: "__pad1", scope: !277, file: !195, line: 186, baseType: !165, size: 64, align: 64, offset: 256)
!288 = !DIDerivedType(tag: DW_TAG_member, name: "__pad2", scope: !277, file: !195, line: 187, baseType: !165, size: 64, align: 64, offset: 320)
!289 = !DIDerivedType(tag: DW_TAG_member, name: "__flags", scope: !277, file: !195, line: 190, baseType: !157, size: 32, align: 32, offset: 384)
!290 = !DIDerivedType(tag: DW_TAG_member, name: "__size", scope: !274, file: !195, line: 211, baseType: !291, size: 448, align: 8)
!291 = !DICompositeType(tag: DW_TAG_array_type, baseType: !218, size: 448, align: 8, elements: !292)
!292 = !{!293}
!293 = !DISubrange(count: 56)
!294 = !DIDerivedType(tag: DW_TAG_member, name: "__align", scope: !274, file: !195, line: 212, baseType: !222, size: 64, align: 64)
!295 = !DIDerivedType(tag: DW_TAG_member, name: "closing_handles", scope: !152, file: !4, line: 1482, baseType: !236, size: 64, align: 64, offset: 2880)
!296 = !DIDerivedType(tag: DW_TAG_member, name: "process_handles", scope: !152, file: !4, line: 1482, baseType: !159, size: 128, align: 64, offset: 2944)
!297 = !DIDerivedType(tag: DW_TAG_member, name: "prepare_handles", scope: !152, file: !4, line: 1482, baseType: !159, size: 128, align: 64, offset: 3072)
!298 = !DIDerivedType(tag: DW_TAG_member, name: "check_handles", scope: !152, file: !4, line: 1482, baseType: !159, size: 128, align: 64, offset: 3200)
!299 = !DIDerivedType(tag: DW_TAG_member, name: "idle_handles", scope: !152, file: !4, line: 1482, baseType: !159, size: 128, align: 64, offset: 3328)
!300 = !DIDerivedType(tag: DW_TAG_member, name: "async_handles", scope: !152, file: !4, line: 1482, baseType: !159, size: 128, align: 64, offset: 3456)
!301 = !DIDerivedType(tag: DW_TAG_member, name: "async_unused", scope: !152, file: !4, line: 1482, baseType: !302, size: 64, align: 64, offset: 3584)
!302 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !303, size: 64, align: 64)
!303 = !DISubroutineType(types: !304)
!304 = !{null}
!305 = !DIDerivedType(tag: DW_TAG_member, name: "async_io_watcher", scope: !152, file: !4, line: 1482, baseType: !173, size: 448, align: 64, offset: 3648)
!306 = !DIDerivedType(tag: DW_TAG_member, name: "async_wfd", scope: !152, file: !4, line: 1482, baseType: !167, size: 32, align: 32, offset: 4096)
!307 = !DIDerivedType(tag: DW_TAG_member, name: "timer_heap", scope: !152, file: !4, line: 1482, baseType: !308, size: 128, align: 64, offset: 4160)
!308 = !DICompositeType(tag: DW_TAG_structure_type, scope: !152, file: !4, line: 1482, size: 128, align: 64, elements: !309)
!309 = !{!310, !311}
!310 = !DIDerivedType(tag: DW_TAG_member, name: "min", scope: !308, file: !4, line: 1482, baseType: !155, size: 64, align: 64)
!311 = !DIDerivedType(tag: DW_TAG_member, name: "nelts", scope: !308, file: !4, line: 1482, baseType: !157, size: 32, align: 32, offset: 64)
!312 = !DIDerivedType(tag: DW_TAG_member, name: "timer_counter", scope: !152, file: !4, line: 1482, baseType: !313, size: 64, align: 64, offset: 4288)
!313 = !DIDerivedType(tag: DW_TAG_typedef, name: "uint64_t", file: !314, line: 55, baseType: !165)
!314 = !DIFile(filename: "/usr/include/stdint.h", directory: "/data/download/cmake/cmake-master/Utilities/cmlibuv")
!315 = !DIDerivedType(tag: DW_TAG_member, name: "time", scope: !152, file: !4, line: 1482, baseType: !313, size: 64, align: 64, offset: 4352)
!316 = !DIDerivedType(tag: DW_TAG_member, name: "signal_pipefd", scope: !152, file: !4, line: 1482, baseType: !317, size: 64, align: 32, offset: 4416)
!317 = !DICompositeType(tag: DW_TAG_array_type, baseType: !167, size: 64, align: 32, elements: !160)
!318 = !DIDerivedType(tag: DW_TAG_member, name: "signal_io_watcher", scope: !152, file: !4, line: 1482, baseType: !173, size: 448, align: 64, offset: 4480)
!319 = !DIDerivedType(tag: DW_TAG_member, name: "child_watcher", scope: !152, file: !4, line: 1482, baseType: !320, size: 1216, align: 64, offset: 4928)
!320 = !DIDerivedType(tag: DW_TAG_typedef, name: "uv_signal_t", file: !4, line: 220, baseType: !321)
!321 = !DICompositeType(tag: DW_TAG_structure_type, name: "uv_signal_s", file: !4, line: 1325, size: 1216, align: 64, elements: !322)
!322 = !{!323, !324, !325, !326, !327, !328, !333, !334, !335, !341, !342, !350, !351}
!323 = !DIDerivedType(tag: DW_TAG_member, name: "data", scope: !321, file: !4, line: 1326, baseType: !155, size: 64, align: 64)
!324 = !DIDerivedType(tag: DW_TAG_member, name: "loop", scope: !321, file: !4, line: 1326, baseType: !150, size: 64, align: 64, offset: 64)
!325 = !DIDerivedType(tag: DW_TAG_member, name: "type", scope: !321, file: !4, line: 1326, baseType: !230, size: 32, align: 32, offset: 128)
!326 = !DIDerivedType(tag: DW_TAG_member, name: "close_cb", scope: !321, file: !4, line: 1326, baseType: !232, size: 64, align: 64, offset: 192)
!327 = !DIDerivedType(tag: DW_TAG_member, name: "handle_queue", scope: !321, file: !4, line: 1326, baseType: !159, size: 128, align: 64, offset: 256)
!328 = !DIDerivedType(tag: DW_TAG_member, name: "u", scope: !321, file: !4, line: 1326, baseType: !329, size: 256, align: 64, offset: 384)
!329 = !DICompositeType(tag: DW_TAG_union_type, scope: !321, file: !4, line: 1326, size: 256, align: 64, elements: !330)
!330 = !{!331, !332}
!331 = !DIDerivedType(tag: DW_TAG_member, name: "fd", scope: !329, file: !4, line: 1326, baseType: !167, size: 32, align: 32)
!332 = !DIDerivedType(tag: DW_TAG_member, name: "reserved", scope: !329, file: !4, line: 1326, baseType: !250, size: 256, align: 64)
!333 = !DIDerivedType(tag: DW_TAG_member, name: "next_closing", scope: !321, file: !4, line: 1326, baseType: !236, size: 64, align: 64, offset: 640)
!334 = !DIDerivedType(tag: DW_TAG_member, name: "flags", scope: !321, file: !4, line: 1326, baseType: !157, size: 32, align: 32, offset: 704)
!335 = !DIDerivedType(tag: DW_TAG_member, name: "signal_cb", scope: !321, file: !4, line: 1327, baseType: !336, size: 64, align: 64, offset: 768)
!336 = !DIDerivedType(tag: DW_TAG_typedef, name: "uv_signal_cb", file: !4, line: 362, baseType: !337)
!337 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !338, size: 64, align: 64)
!338 = !DISubroutineType(types: !339)
!339 = !{null, !340, !167}
!340 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !320, size: 64, align: 64)
!341 = !DIDerivedType(tag: DW_TAG_member, name: "signum", scope: !321, file: !4, line: 1328, baseType: !167, size: 32, align: 32, offset: 832)
!342 = !DIDerivedType(tag: DW_TAG_member, name: "tree_entry", scope: !321, file: !4, line: 1329, baseType: !343, size: 256, align: 64, offset: 896)
!343 = !DICompositeType(tag: DW_TAG_structure_type, scope: !321, file: !4, line: 1329, size: 256, align: 64, elements: !344)
!344 = !{!345, !347, !348, !349}
!345 = !DIDerivedType(tag: DW_TAG_member, name: "rbe_left", scope: !343, file: !4, line: 1329, baseType: !346, size: 64, align: 64)
!346 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !321, size: 64, align: 64)
!347 = !DIDerivedType(tag: DW_TAG_member, name: "rbe_right", scope: !343, file: !4, line: 1329, baseType: !346, size: 64, align: 64, offset: 64)
!348 = !DIDerivedType(tag: DW_TAG_member, name: "rbe_parent", scope: !343, file: !4, line: 1329, baseType: !346, size: 64, align: 64, offset: 128)
!349 = !DIDerivedType(tag: DW_TAG_member, name: "rbe_color", scope: !343, file: !4, line: 1329, baseType: !167, size: 32, align: 32, offset: 192)
!350 = !DIDerivedType(tag: DW_TAG_member, name: "caught_signals", scope: !321, file: !4, line: 1329, baseType: !157, size: 32, align: 32, offset: 1152)
!351 = !DIDerivedType(tag: DW_TAG_member, name: "dispatched_signals", scope: !321, file: !4, line: 1329, baseType: !157, size: 32, align: 32, offset: 1184)
!352 = !DIDerivedType(tag: DW_TAG_member, name: "emfile_fd", scope: !152, file: !4, line: 1482, baseType: !167, size: 32, align: 32, offset: 6144)
!353 = !DIDerivedType(tag: DW_TAG_member, name: "inotify_read_watcher", scope: !152, file: !4, line: 1482, baseType: !173, size: 448, align: 64, offset: 6208)
!354 = !DIDerivedType(tag: DW_TAG_member, name: "inotify_watchers", scope: !152, file: !4, line: 1482, baseType: !155, size: 64, align: 64, offset: 6656)
!355 = !DIDerivedType(tag: DW_TAG_member, name: "inotify_fd", scope: !152, file: !4, line: 1482, baseType: !167, size: 32, align: 32, offset: 6720)
!356 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !218, size: 64, align: 64)
!357 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !358, size: 64, align: 64)
!358 = !DIDerivedType(tag: DW_TAG_const_type, baseType: !359)
!359 = !DIDerivedType(tag: DW_TAG_typedef, name: "QUEUE", file: !360, line: 21, baseType: !159)
!360 = !DIFile(filename: "/data/download/cmake/cmake-master/Utilities/cmlibuv/src/queue.h", directory: "/data/download/cmake/cmake-master/Utilities/cmlibuv")
!361 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !362, size: 64, align: 64)
!362 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !359, size: 64, align: 64)
!363 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !364, size: 64, align: 64)
!364 = !DICompositeType(tag: DW_TAG_structure_type, name: "uv__work", file: !365, line: 30, size: 320, align: 64, elements: !366)
!365 = !DIFile(filename: "/data/download/cmake/cmake-master/Utilities/cmlibuv/include/uv-threadpool.h", directory: "/data/download/cmake/cmake-master/Utilities/cmlibuv")
!366 = !{!367, !371, !375, !376}
!367 = !DIDerivedType(tag: DW_TAG_member, name: "work", scope: !364, file: !365, line: 31, baseType: !368, size: 64, align: 64)
!368 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !369, size: 64, align: 64)
!369 = !DISubroutineType(types: !370)
!370 = !{null, !363}
!371 = !DIDerivedType(tag: DW_TAG_member, name: "done", scope: !364, file: !365, line: 32, baseType: !372, size: 64, align: 64, offset: 64)
!372 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !373, size: 64, align: 64)
!373 = !DISubroutineType(types: !374)
!374 = !{null, !363, !167}
!375 = !DIDerivedType(tag: DW_TAG_member, name: "loop", scope: !364, file: !365, line: 33, baseType: !182, size: 64, align: 64, offset: 128)
!376 = !DIDerivedType(tag: DW_TAG_member, name: "wq", scope: !364, file: !365, line: 34, baseType: !159, size: 128, align: 64, offset: 192)
!377 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !378, size: 64, align: 64)
!378 = !DIDerivedType(tag: DW_TAG_typedef, name: "uv_fs_t", file: !4, line: 230, baseType: !379)
!379 = !DICompositeType(tag: DW_TAG_structure_type, name: "uv_fs_s", file: !4, line: 1120, size: 3520, align: 64, elements: !380)
!380 = !{!381, !382, !384, !385, !386, !388, !389, !394, !399, !400, !403, !428, !429, !431, !432, !436, !437, !446, !449, !453, !457, !459, !460, !461}
!381 = !DIDerivedType(tag: DW_TAG_member, name: "data", scope: !379, file: !4, line: 1121, baseType: !155, size: 64, align: 64)
!382 = !DIDerivedType(tag: DW_TAG_member, name: "type", scope: !379, file: !4, line: 1121, baseType: !383, size: 32, align: 32, offset: 64)
!383 = !DIDerivedType(tag: DW_TAG_typedef, name: "uv_req_type", file: !4, line: 200, baseType: !104)
!384 = !DIDerivedType(tag: DW_TAG_member, name: "active_queue", scope: !379, file: !4, line: 1121, baseType: !159, size: 128, align: 64, offset: 128)
!385 = !DIDerivedType(tag: DW_TAG_member, name: "reserved", scope: !379, file: !4, line: 1121, baseType: !250, size: 256, align: 64, offset: 256)
!386 = !DIDerivedType(tag: DW_TAG_member, name: "fs_type", scope: !379, file: !4, line: 1122, baseType: !387, size: 32, align: 32, offset: 512)
!387 = !DIDerivedType(tag: DW_TAG_typedef, name: "uv_fs_type", file: !4, line: 1117, baseType: !117)
!388 = !DIDerivedType(tag: DW_TAG_member, name: "loop", scope: !379, file: !4, line: 1123, baseType: !150, size: 64, align: 64, offset: 576)
!389 = !DIDerivedType(tag: DW_TAG_member, name: "cb", scope: !379, file: !4, line: 1124, baseType: !390, size: 64, align: 64, offset: 640)
!390 = !DIDerivedType(tag: DW_TAG_typedef, name: "uv_fs_cb", file: !4, line: 315, baseType: !391)
!391 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !392, size: 64, align: 64)
!392 = !DISubroutineType(types: !393)
!393 = !{null, !377}
!394 = !DIDerivedType(tag: DW_TAG_member, name: "result", scope: !379, file: !4, line: 1125, baseType: !395, size: 64, align: 64, offset: 704)
!395 = !DIDerivedType(tag: DW_TAG_typedef, name: "ssize_t", file: !396, line: 102, baseType: !397)
!396 = !DIFile(filename: "/usr/include/stdio.h", directory: "/data/download/cmake/cmake-master/Utilities/cmlibuv")
!397 = !DIDerivedType(tag: DW_TAG_typedef, name: "__ssize_t", file: !398, line: 172, baseType: !222)
!398 = !DIFile(filename: "/usr/include/x86_64-linux-gnu/bits/types.h", directory: "/data/download/cmake/cmake-master/Utilities/cmlibuv")
!399 = !DIDerivedType(tag: DW_TAG_member, name: "ptr", scope: !379, file: !4, line: 1126, baseType: !155, size: 64, align: 64, offset: 768)
!400 = !DIDerivedType(tag: DW_TAG_member, name: "path", scope: !379, file: !4, line: 1127, baseType: !401, size: 64, align: 64, offset: 832)
!401 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !402, size: 64, align: 64)
!402 = !DIDerivedType(tag: DW_TAG_const_type, baseType: !218)
!403 = !DIDerivedType(tag: DW_TAG_member, name: "statbuf", scope: !379, file: !4, line: 1128, baseType: !404, size: 1280, align: 64, offset: 896)
!404 = !DIDerivedType(tag: DW_TAG_typedef, name: "uv_stat_t", file: !4, line: 349, baseType: !405)
!405 = !DICompositeType(tag: DW_TAG_structure_type, file: !4, line: 332, size: 1280, align: 64, elements: !406)
!406 = !{!407, !408, !409, !410, !411, !412, !413, !414, !415, !416, !417, !418, !419, !425, !426, !427}
!407 = !DIDerivedType(tag: DW_TAG_member, name: "st_dev", scope: !405, file: !4, line: 333, baseType: !313, size: 64, align: 64)
!408 = !DIDerivedType(tag: DW_TAG_member, name: "st_mode", scope: !405, file: !4, line: 334, baseType: !313, size: 64, align: 64, offset: 64)
!409 = !DIDerivedType(tag: DW_TAG_member, name: "st_nlink", scope: !405, file: !4, line: 335, baseType: !313, size: 64, align: 64, offset: 128)
!410 = !DIDerivedType(tag: DW_TAG_member, name: "st_uid", scope: !405, file: !4, line: 336, baseType: !313, size: 64, align: 64, offset: 192)
!411 = !DIDerivedType(tag: DW_TAG_member, name: "st_gid", scope: !405, file: !4, line: 337, baseType: !313, size: 64, align: 64, offset: 256)
!412 = !DIDerivedType(tag: DW_TAG_member, name: "st_rdev", scope: !405, file: !4, line: 338, baseType: !313, size: 64, align: 64, offset: 320)
!413 = !DIDerivedType(tag: DW_TAG_member, name: "st_ino", scope: !405, file: !4, line: 339, baseType: !313, size: 64, align: 64, offset: 384)
!414 = !DIDerivedType(tag: DW_TAG_member, name: "st_size", scope: !405, file: !4, line: 340, baseType: !313, size: 64, align: 64, offset: 448)
!415 = !DIDerivedType(tag: DW_TAG_member, name: "st_blksize", scope: !405, file: !4, line: 341, baseType: !313, size: 64, align: 64, offset: 512)
!416 = !DIDerivedType(tag: DW_TAG_member, name: "st_blocks", scope: !405, file: !4, line: 342, baseType: !313, size: 64, align: 64, offset: 576)
!417 = !DIDerivedType(tag: DW_TAG_member, name: "st_flags", scope: !405, file: !4, line: 343, baseType: !313, size: 64, align: 64, offset: 640)
!418 = !DIDerivedType(tag: DW_TAG_member, name: "st_gen", scope: !405, file: !4, line: 344, baseType: !313, size: 64, align: 64, offset: 704)
!419 = !DIDerivedType(tag: DW_TAG_member, name: "st_atim", scope: !405, file: !4, line: 345, baseType: !420, size: 128, align: 64, offset: 768)
!420 = !DIDerivedType(tag: DW_TAG_typedef, name: "uv_timespec_t", file: !4, line: 329, baseType: !421)
!421 = !DICompositeType(tag: DW_TAG_structure_type, file: !4, line: 326, size: 128, align: 64, elements: !422)
!422 = !{!423, !424}
!423 = !DIDerivedType(tag: DW_TAG_member, name: "tv_sec", scope: !421, file: !4, line: 327, baseType: !222, size: 64, align: 64)
!424 = !DIDerivedType(tag: DW_TAG_member, name: "tv_nsec", scope: !421, file: !4, line: 328, baseType: !222, size: 64, align: 64, offset: 64)
!425 = !DIDerivedType(tag: DW_TAG_member, name: "st_mtim", scope: !405, file: !4, line: 346, baseType: !420, size: 128, align: 64, offset: 896)
!426 = !DIDerivedType(tag: DW_TAG_member, name: "st_ctim", scope: !405, file: !4, line: 347, baseType: !420, size: 128, align: 64, offset: 1024)
!427 = !DIDerivedType(tag: DW_TAG_member, name: "st_birthtim", scope: !405, file: !4, line: 348, baseType: !420, size: 128, align: 64, offset: 1152)
!428 = !DIDerivedType(tag: DW_TAG_member, name: "new_path", scope: !379, file: !4, line: 1129, baseType: !401, size: 64, align: 64, offset: 2176)
!429 = !DIDerivedType(tag: DW_TAG_member, name: "file", scope: !379, file: !4, line: 1129, baseType: !430, size: 32, align: 32, offset: 2240)
!430 = !DIDerivedType(tag: DW_TAG_typedef, name: "uv_file", file: !174, line: 121, baseType: !167)
!431 = !DIDerivedType(tag: DW_TAG_member, name: "flags", scope: !379, file: !4, line: 1129, baseType: !167, size: 32, align: 32, offset: 2272)
!432 = !DIDerivedType(tag: DW_TAG_member, name: "mode", scope: !379, file: !4, line: 1129, baseType: !433, size: 32, align: 32, offset: 2304)
!433 = !DIDerivedType(tag: DW_TAG_typedef, name: "mode_t", file: !434, line: 70, baseType: !435)
!434 = !DIFile(filename: "/usr/include/x86_64-linux-gnu/sys/types.h", directory: "/data/download/cmake/cmake-master/Utilities/cmlibuv")
!435 = !DIDerivedType(tag: DW_TAG_typedef, name: "__mode_t", file: !398, line: 129, baseType: !157)
!436 = !DIDerivedType(tag: DW_TAG_member, name: "nbufs", scope: !379, file: !4, line: 1129, baseType: !157, size: 32, align: 32, offset: 2336)
!437 = !DIDerivedType(tag: DW_TAG_member, name: "bufs", scope: !379, file: !4, line: 1129, baseType: !438, size: 64, align: 64, offset: 2368)
!438 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !439, size: 64, align: 64)
!439 = !DIDerivedType(tag: DW_TAG_typedef, name: "uv_buf_t", file: !174, line: 119, baseType: !440)
!440 = !DICompositeType(tag: DW_TAG_structure_type, name: "uv_buf_t", file: !174, line: 116, size: 128, align: 64, elements: !441)
!441 = !{!442, !443}
!442 = !DIDerivedType(tag: DW_TAG_member, name: "base", scope: !440, file: !174, line: 117, baseType: !356, size: 64, align: 64)
!443 = !DIDerivedType(tag: DW_TAG_member, name: "len", scope: !440, file: !174, line: 118, baseType: !444, size: 64, align: 64, offset: 64)
!444 = !DIDerivedType(tag: DW_TAG_typedef, name: "size_t", file: !445, line: 62, baseType: !165)
!445 = !DIFile(filename: "/opt/llvm-build/bin/../lib/clang/3.8.0/include/stddef.h", directory: "/data/download/cmake/cmake-master/Utilities/cmlibuv")
!446 = !DIDerivedType(tag: DW_TAG_member, name: "off", scope: !379, file: !4, line: 1129, baseType: !447, size: 64, align: 64, offset: 2432)
!447 = !DIDerivedType(tag: DW_TAG_typedef, name: "off_t", file: !396, line: 90, baseType: !448)
!448 = !DIDerivedType(tag: DW_TAG_typedef, name: "__off_t", file: !398, line: 131, baseType: !222)
!449 = !DIDerivedType(tag: DW_TAG_member, name: "uid", scope: !379, file: !4, line: 1129, baseType: !450, size: 32, align: 32, offset: 2496)
!450 = !DIDerivedType(tag: DW_TAG_typedef, name: "uv_uid_t", file: !174, line: 139, baseType: !451)
!451 = !DIDerivedType(tag: DW_TAG_typedef, name: "uid_t", file: !434, line: 80, baseType: !452)
!452 = !DIDerivedType(tag: DW_TAG_typedef, name: "__uid_t", file: !398, line: 125, baseType: !157)
!453 = !DIDerivedType(tag: DW_TAG_member, name: "gid", scope: !379, file: !4, line: 1129, baseType: !454, size: 32, align: 32, offset: 2528)
!454 = !DIDerivedType(tag: DW_TAG_typedef, name: "uv_gid_t", file: !174, line: 138, baseType: !455)
!455 = !DIDerivedType(tag: DW_TAG_typedef, name: "gid_t", file: !434, line: 65, baseType: !456)
!456 = !DIDerivedType(tag: DW_TAG_typedef, name: "__gid_t", file: !398, line: 126, baseType: !157)
!457 = !DIDerivedType(tag: DW_TAG_member, name: "atime", scope: !379, file: !4, line: 1129, baseType: !458, size: 64, align: 64, offset: 2560)
!458 = !DIBasicType(name: "double", size: 64, align: 64, encoding: DW_ATE_float)
!459 = !DIDerivedType(tag: DW_TAG_member, name: "mtime", scope: !379, file: !4, line: 1129, baseType: !458, size: 64, align: 64, offset: 2624)
!460 = !DIDerivedType(tag: DW_TAG_member, name: "work_req", scope: !379, file: !4, line: 1129, baseType: !364, size: 320, align: 64, offset: 2688)
!461 = !DIDerivedType(tag: DW_TAG_member, name: "bufsml", scope: !379, file: !4, line: 1129, baseType: !462, size: 512, align: 64, offset: 3008)
!462 = !DICompositeType(tag: DW_TAG_array_type, baseType: !439, size: 512, align: 64, elements: !251)
!463 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !464, size: 64, align: 64)
!464 = !DIDerivedType(tag: DW_TAG_typedef, name: "uv_getaddrinfo_t", file: !4, line: 224, baseType: !465)
!465 = !DICompositeType(tag: DW_TAG_structure_type, name: "uv_getaddrinfo_s", file: !4, line: 804, size: 1280, align: 64, elements: !466)
!466 = !{!467, !468, !469, !470, !471, !472, !473, !504, !505, !506, !507, !508}
!467 = !DIDerivedType(tag: DW_TAG_member, name: "data", scope: !465, file: !4, line: 805, baseType: !155, size: 64, align: 64)
!468 = !DIDerivedType(tag: DW_TAG_member, name: "type", scope: !465, file: !4, line: 805, baseType: !383, size: 32, align: 32, offset: 64)
!469 = !DIDerivedType(tag: DW_TAG_member, name: "active_queue", scope: !465, file: !4, line: 805, baseType: !159, size: 128, align: 64, offset: 128)
!470 = !DIDerivedType(tag: DW_TAG_member, name: "reserved", scope: !465, file: !4, line: 805, baseType: !250, size: 256, align: 64, offset: 256)
!471 = !DIDerivedType(tag: DW_TAG_member, name: "loop", scope: !465, file: !4, line: 807, baseType: !150, size: 64, align: 64, offset: 512)
!472 = !DIDerivedType(tag: DW_TAG_member, name: "work_req", scope: !465, file: !4, line: 809, baseType: !364, size: 320, align: 64, offset: 576)
!473 = !DIDerivedType(tag: DW_TAG_member, name: "cb", scope: !465, file: !4, line: 809, baseType: !474, size: 64, align: 64, offset: 896)
!474 = !DIDerivedType(tag: DW_TAG_typedef, name: "uv_getaddrinfo_cb", file: !4, line: 318, baseType: !475)
!475 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !476, size: 64, align: 64)
!476 = !DISubroutineType(types: !477)
!477 = !{null, !463, !167, !478}
!478 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !479, size: 64, align: 64)
!479 = !DICompositeType(tag: DW_TAG_structure_type, name: "addrinfo", file: !480, line: 567, size: 384, align: 64, elements: !481)
!480 = !DIFile(filename: "/usr/include/netdb.h", directory: "/data/download/cmake/cmake-master/Utilities/cmlibuv")
!481 = !{!482, !483, !484, !485, !486, !490, !502, !503}
!482 = !DIDerivedType(tag: DW_TAG_member, name: "ai_flags", scope: !479, file: !480, line: 569, baseType: !167, size: 32, align: 32)
!483 = !DIDerivedType(tag: DW_TAG_member, name: "ai_family", scope: !479, file: !480, line: 570, baseType: !167, size: 32, align: 32, offset: 32)
!484 = !DIDerivedType(tag: DW_TAG_member, name: "ai_socktype", scope: !479, file: !480, line: 571, baseType: !167, size: 32, align: 32, offset: 64)
!485 = !DIDerivedType(tag: DW_TAG_member, name: "ai_protocol", scope: !479, file: !480, line: 572, baseType: !167, size: 32, align: 32, offset: 96)
!486 = !DIDerivedType(tag: DW_TAG_member, name: "ai_addrlen", scope: !479, file: !480, line: 573, baseType: !487, size: 32, align: 32, offset: 128)
!487 = !DIDerivedType(tag: DW_TAG_typedef, name: "socklen_t", file: !488, line: 33, baseType: !489)
!488 = !DIFile(filename: "/usr/include/x86_64-linux-gnu/bits/socket.h", directory: "/data/download/cmake/cmake-master/Utilities/cmlibuv")
!489 = !DIDerivedType(tag: DW_TAG_typedef, name: "__socklen_t", file: !398, line: 189, baseType: !157)
!490 = !DIDerivedType(tag: DW_TAG_member, name: "ai_addr", scope: !479, file: !480, line: 574, baseType: !491, size: 64, align: 64, offset: 192)
!491 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !492, size: 64, align: 64)
!492 = !DICompositeType(tag: DW_TAG_structure_type, name: "sockaddr", file: !488, line: 149, size: 128, align: 16, elements: !493)
!493 = !{!494, !498}
!494 = !DIDerivedType(tag: DW_TAG_member, name: "sa_family", scope: !492, file: !488, line: 151, baseType: !495, size: 16, align: 16)
!495 = !DIDerivedType(tag: DW_TAG_typedef, name: "sa_family_t", file: !496, line: 28, baseType: !497)
!496 = !DIFile(filename: "/usr/include/x86_64-linux-gnu/bits/sockaddr.h", directory: "/data/download/cmake/cmake-master/Utilities/cmlibuv")
!497 = !DIBasicType(name: "unsigned short", size: 16, align: 16, encoding: DW_ATE_unsigned)
!498 = !DIDerivedType(tag: DW_TAG_member, name: "sa_data", scope: !492, file: !488, line: 152, baseType: !499, size: 112, align: 8, offset: 16)
!499 = !DICompositeType(tag: DW_TAG_array_type, baseType: !218, size: 112, align: 8, elements: !500)
!500 = !{!501}
!501 = !DISubrange(count: 14)
!502 = !DIDerivedType(tag: DW_TAG_member, name: "ai_canonname", scope: !479, file: !480, line: 575, baseType: !356, size: 64, align: 64, offset: 256)
!503 = !DIDerivedType(tag: DW_TAG_member, name: "ai_next", scope: !479, file: !480, line: 576, baseType: !478, size: 64, align: 64, offset: 320)
!504 = !DIDerivedType(tag: DW_TAG_member, name: "hints", scope: !465, file: !4, line: 809, baseType: !478, size: 64, align: 64, offset: 960)
!505 = !DIDerivedType(tag: DW_TAG_member, name: "hostname", scope: !465, file: !4, line: 809, baseType: !356, size: 64, align: 64, offset: 1024)
!506 = !DIDerivedType(tag: DW_TAG_member, name: "service", scope: !465, file: !4, line: 809, baseType: !356, size: 64, align: 64, offset: 1088)
!507 = !DIDerivedType(tag: DW_TAG_member, name: "addrinfo", scope: !465, file: !4, line: 809, baseType: !478, size: 64, align: 64, offset: 1152)
!508 = !DIDerivedType(tag: DW_TAG_member, name: "retcode", scope: !465, file: !4, line: 809, baseType: !167, size: 32, align: 32, offset: 1216)
!509 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !510, size: 64, align: 64)
!510 = !DIDerivedType(tag: DW_TAG_typedef, name: "uv_getnameinfo_t", file: !4, line: 225, baseType: !511)
!511 = !DICompositeType(tag: DW_TAG_structure_type, name: "uv_getnameinfo_s", file: !4, line: 827, size: 10560, align: 64, elements: !512)
!512 = !{!513, !514, !515, !516, !517, !518, !519, !524, !533, !534, !538, !542}
!513 = !DIDerivedType(tag: DW_TAG_member, name: "data", scope: !511, file: !4, line: 828, baseType: !155, size: 64, align: 64)
!514 = !DIDerivedType(tag: DW_TAG_member, name: "type", scope: !511, file: !4, line: 828, baseType: !383, size: 32, align: 32, offset: 64)
!515 = !DIDerivedType(tag: DW_TAG_member, name: "active_queue", scope: !511, file: !4, line: 828, baseType: !159, size: 128, align: 64, offset: 128)
!516 = !DIDerivedType(tag: DW_TAG_member, name: "reserved", scope: !511, file: !4, line: 828, baseType: !250, size: 256, align: 64, offset: 256)
!517 = !DIDerivedType(tag: DW_TAG_member, name: "loop", scope: !511, file: !4, line: 830, baseType: !150, size: 64, align: 64, offset: 512)
!518 = !DIDerivedType(tag: DW_TAG_member, name: "work_req", scope: !511, file: !4, line: 832, baseType: !364, size: 320, align: 64, offset: 576)
!519 = !DIDerivedType(tag: DW_TAG_member, name: "getnameinfo_cb", scope: !511, file: !4, line: 832, baseType: !520, size: 64, align: 64, offset: 896)
!520 = !DIDerivedType(tag: DW_TAG_typedef, name: "uv_getnameinfo_cb", file: !4, line: 321, baseType: !521)
!521 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !522, size: 64, align: 64)
!522 = !DISubroutineType(types: !523)
!523 = !{null, !509, !167, !401, !401}
!524 = !DIDerivedType(tag: DW_TAG_member, name: "storage", scope: !511, file: !4, line: 832, baseType: !525, size: 1024, align: 64, offset: 960)
!525 = !DICompositeType(tag: DW_TAG_structure_type, name: "sockaddr_storage", file: !488, line: 162, size: 1024, align: 64, elements: !526)
!526 = !{!527, !528, !529}
!527 = !DIDerivedType(tag: DW_TAG_member, name: "ss_family", scope: !525, file: !488, line: 164, baseType: !495, size: 16, align: 16)
!528 = !DIDerivedType(tag: DW_TAG_member, name: "__ss_align", scope: !525, file: !488, line: 165, baseType: !165, size: 64, align: 64, offset: 64)
!529 = !DIDerivedType(tag: DW_TAG_member, name: "__ss_padding", scope: !525, file: !488, line: 166, baseType: !530, size: 896, align: 8, offset: 128)
!530 = !DICompositeType(tag: DW_TAG_array_type, baseType: !218, size: 896, align: 8, elements: !531)
!531 = !{!532}
!532 = !DISubrange(count: 112)
!533 = !DIDerivedType(tag: DW_TAG_member, name: "flags", scope: !511, file: !4, line: 832, baseType: !167, size: 32, align: 32, offset: 1984)
!534 = !DIDerivedType(tag: DW_TAG_member, name: "host", scope: !511, file: !4, line: 832, baseType: !535, size: 8200, align: 8, offset: 2016)
!535 = !DICompositeType(tag: DW_TAG_array_type, baseType: !218, size: 8200, align: 8, elements: !536)
!536 = !{!537}
!537 = !DISubrange(count: 1025)
!538 = !DIDerivedType(tag: DW_TAG_member, name: "service", scope: !511, file: !4, line: 832, baseType: !539, size: 256, align: 8, offset: 10216)
!539 = !DICompositeType(tag: DW_TAG_array_type, baseType: !218, size: 256, align: 8, elements: !540)
!540 = !{!541}
!541 = !DISubrange(count: 32)
!542 = !DIDerivedType(tag: DW_TAG_member, name: "retcode", scope: !511, file: !4, line: 832, baseType: !167, size: 32, align: 32, offset: 10496)
!543 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !544, size: 64, align: 64)
!544 = !DIDerivedType(tag: DW_TAG_typedef, name: "uv_work_t", file: !4, line: 231, baseType: !545)
!545 = !DICompositeType(tag: DW_TAG_structure_type, name: "uv_work_s", file: !4, line: 970, size: 1024, align: 64, elements: !546)
!546 = !{!547, !548, !549, !550, !551, !552, !557, !562}
!547 = !DIDerivedType(tag: DW_TAG_member, name: "data", scope: !545, file: !4, line: 971, baseType: !155, size: 64, align: 64)
!548 = !DIDerivedType(tag: DW_TAG_member, name: "type", scope: !545, file: !4, line: 971, baseType: !383, size: 32, align: 32, offset: 64)
!549 = !DIDerivedType(tag: DW_TAG_member, name: "active_queue", scope: !545, file: !4, line: 971, baseType: !159, size: 128, align: 64, offset: 128)
!550 = !DIDerivedType(tag: DW_TAG_member, name: "reserved", scope: !545, file: !4, line: 971, baseType: !250, size: 256, align: 64, offset: 256)
!551 = !DIDerivedType(tag: DW_TAG_member, name: "loop", scope: !545, file: !4, line: 972, baseType: !150, size: 64, align: 64, offset: 512)
!552 = !DIDerivedType(tag: DW_TAG_member, name: "work_cb", scope: !545, file: !4, line: 973, baseType: !553, size: 64, align: 64, offset: 576)
!553 = !DIDerivedType(tag: DW_TAG_typedef, name: "uv_work_cb", file: !4, line: 316, baseType: !554)
!554 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !555, size: 64, align: 64)
!555 = !DISubroutineType(types: !556)
!556 = !{null, !543}
!557 = !DIDerivedType(tag: DW_TAG_member, name: "after_work_cb", scope: !545, file: !4, line: 974, baseType: !558, size: 64, align: 64, offset: 640)
!558 = !DIDerivedType(tag: DW_TAG_typedef, name: "uv_after_work_cb", file: !4, line: 317, baseType: !559)
!559 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !560, size: 64, align: 64)
!560 = !DISubroutineType(types: !561)
!561 = !{null, !543, !167}
!562 = !DIDerivedType(tag: DW_TAG_member, name: "work_req", scope: !545, file: !4, line: 975, baseType: !364, size: 320, align: 64, offset: 704)
!563 = !{!564, !566, !569, !570, !573, !584, !587, !588, !589, !590, !593, !594, !595, !596}
!564 = distinct !DISubprogram(name: "cleanup", scope: !1, file: !1, line: 105, type: !303, isLocal: true, isDefinition: true, scopeLine: 105, flags: DIFlagPrototyped, isOptimized: false, variables: !565)
!565 = !{}
!566 = distinct !DISubprogram(name: "uv__work_submit", scope: !1, file: !1, line: 189, type: !567, isLocal: false, isDefinition: true, scopeLine: 192, flags: DIFlagPrototyped, isOptimized: false, variables: !565)
!567 = !DISubroutineType(types: !568)
!568 = !{null, !150, !363, !368, !372}
!569 = distinct !DISubprogram(name: "uv__work_done", scope: !1, file: !1, line: 227, type: !266, isLocal: false, isDefinition: true, scopeLine: 227, flags: DIFlagPrototyped, isOptimized: false, variables: !565)
!570 = distinct !DISubprogram(name: "uv_queue_work", scope: !1, file: !1, line: 270, type: !571, isLocal: false, isDefinition: true, scopeLine: 273, flags: DIFlagPrototyped, isOptimized: false, variables: !565)
!571 = !DISubroutineType(types: !572)
!572 = !{!167, !150, !543, !553, !558}
!573 = distinct !DISubprogram(name: "uv_cancel", scope: !1, file: !1, line: 286, type: !574, isLocal: false, isDefinition: true, scopeLine: 286, flags: DIFlagPrototyped, isOptimized: false, variables: !565)
!574 = !DISubroutineType(types: !575)
!575 = !{!167, !576}
!576 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !577, size: 64, align: 64)
!577 = !DIDerivedType(tag: DW_TAG_typedef, name: "uv_req_t", file: !4, line: 223, baseType: !578)
!578 = !DICompositeType(tag: DW_TAG_structure_type, name: "uv_req_s", file: !4, line: 388, size: 512, align: 64, elements: !579)
!579 = !{!580, !581, !582, !583}
!580 = !DIDerivedType(tag: DW_TAG_member, name: "data", scope: !578, file: !4, line: 389, baseType: !155, size: 64, align: 64)
!581 = !DIDerivedType(tag: DW_TAG_member, name: "type", scope: !578, file: !4, line: 389, baseType: !383, size: 32, align: 32, offset: 64)
!582 = !DIDerivedType(tag: DW_TAG_member, name: "active_queue", scope: !578, file: !4, line: 389, baseType: !159, size: 128, align: 64, offset: 128)
!583 = !DIDerivedType(tag: DW_TAG_member, name: "reserved", scope: !578, file: !4, line: 389, baseType: !250, size: 256, align: 64, offset: 256)
!584 = distinct !DISubprogram(name: "post", scope: !1, file: !1, line: 95, type: !585, isLocal: true, isDefinition: true, scopeLine: 95, flags: DIFlagPrototyped, isOptimized: false, variables: !565)
!585 = !DISubroutineType(types: !586)
!586 = !{null, !362}
!587 = distinct !DISubprogram(name: "init_once", scope: !1, file: !1, line: 176, type: !303, isLocal: true, isDefinition: true, scopeLine: 176, flags: DIFlagPrototyped, isOptimized: false, variables: !565)
!588 = distinct !DISubprogram(name: "reset_once", scope: !1, file: !1, line: 169, type: !303, isLocal: true, isDefinition: true, scopeLine: 169, flags: DIFlagPrototyped, isOptimized: false, variables: !565)
!589 = distinct !DISubprogram(name: "init_threads", scope: !1, file: !1, line: 130, type: !303, isLocal: true, isDefinition: true, scopeLine: 130, flags: DIFlagPrototyped, isOptimized: false, variables: !565)
!590 = distinct !DISubprogram(name: "worker", scope: !1, file: !1, line: 52, type: !591, isLocal: true, isDefinition: true, scopeLine: 52, flags: DIFlagPrototyped, isOptimized: false, variables: !565)
!591 = !DISubroutineType(types: !592)
!592 = !{null, !155}
!593 = distinct !DISubprogram(name: "uv__cancelled", scope: !1, file: !1, line: 44, type: !369, isLocal: true, isDefinition: true, scopeLine: 44, flags: DIFlagPrototyped, isOptimized: false, variables: !565)
!594 = distinct !DISubprogram(name: "uv__queue_work", scope: !1, file: !1, line: 250, type: !369, isLocal: true, isDefinition: true, scopeLine: 250, flags: DIFlagPrototyped, isOptimized: false, variables: !565)
!595 = distinct !DISubprogram(name: "uv__queue_done", scope: !1, file: !1, line: 257, type: !373, isLocal: true, isDefinition: true, scopeLine: 257, flags: DIFlagPrototyped, isOptimized: false, variables: !565)
!596 = distinct !DISubprogram(name: "uv__work_cancel", scope: !1, file: !1, line: 201, type: !597, isLocal: true, isDefinition: true, scopeLine: 201, flags: DIFlagPrototyped, isOptimized: false, variables: !565)
!597 = !DISubroutineType(types: !598)
!598 = !{!167, !150, !576, !363}
!599 = !{!600, !623, !624, !625, !629, !631, !632, !634, !635, !636}
!600 = !DIGlobalVariable(name: "cond", scope: !0, file: !1, line: 33, type: !601, isLocal: true, isDefinition: true, variable: %union.pthread_cond_t* @cond)
!601 = !DIDerivedType(tag: DW_TAG_typedef, name: "uv_cond_t", file: !174, line: 132, baseType: !602)
!602 = !DIDerivedType(tag: DW_TAG_typedef, name: "pthread_cond_t", file: !195, line: 153, baseType: !603)
!603 = !DICompositeType(tag: DW_TAG_union_type, file: !195, line: 138, size: 384, align: 64, elements: !604)
!604 = !{!605, !617, !621}
!605 = !DIDerivedType(tag: DW_TAG_member, name: "__data", scope: !603, file: !195, line: 150, baseType: !606, size: 384, align: 64)
!606 = !DICompositeType(tag: DW_TAG_structure_type, scope: !603, file: !195, line: 140, size: 384, align: 64, elements: !607)
!607 = !{!608, !609, !610, !612, !613, !614, !615, !616}
!608 = !DIDerivedType(tag: DW_TAG_member, name: "__lock", scope: !606, file: !195, line: 142, baseType: !167, size: 32, align: 32)
!609 = !DIDerivedType(tag: DW_TAG_member, name: "__futex", scope: !606, file: !195, line: 143, baseType: !157, size: 32, align: 32, offset: 32)
!610 = !DIDerivedType(tag: DW_TAG_member, name: "__total_seq", scope: !606, file: !195, line: 144, baseType: !611, size: 64, align: 64, offset: 64)
!611 = !DIBasicType(name: "long long unsigned int", size: 64, align: 64, encoding: DW_ATE_unsigned)
!612 = !DIDerivedType(tag: DW_TAG_member, name: "__wakeup_seq", scope: !606, file: !195, line: 145, baseType: !611, size: 64, align: 64, offset: 128)
!613 = !DIDerivedType(tag: DW_TAG_member, name: "__woken_seq", scope: !606, file: !195, line: 146, baseType: !611, size: 64, align: 64, offset: 192)
!614 = !DIDerivedType(tag: DW_TAG_member, name: "__mutex", scope: !606, file: !195, line: 147, baseType: !155, size: 64, align: 64, offset: 256)
!615 = !DIDerivedType(tag: DW_TAG_member, name: "__nwaiters", scope: !606, file: !195, line: 148, baseType: !157, size: 32, align: 32, offset: 320)
!616 = !DIDerivedType(tag: DW_TAG_member, name: "__broadcast_seq", scope: !606, file: !195, line: 149, baseType: !157, size: 32, align: 32, offset: 352)
!617 = !DIDerivedType(tag: DW_TAG_member, name: "__size", scope: !603, file: !195, line: 151, baseType: !618, size: 384, align: 8)
!618 = !DICompositeType(tag: DW_TAG_array_type, baseType: !218, size: 384, align: 8, elements: !619)
!619 = !{!620}
!620 = !DISubrange(count: 48)
!621 = !DIDerivedType(tag: DW_TAG_member, name: "__align", scope: !603, file: !195, line: 152, baseType: !622, size: 64, align: 64)
!622 = !DIBasicType(name: "long long int", size: 64, align: 64, encoding: DW_ATE_signed)
!623 = !DIGlobalVariable(name: "mutex", scope: !0, file: !1, line: 34, type: !193, isLocal: true, isDefinition: true, variable: %union.pthread_mutex_t* @mutex)
!624 = !DIGlobalVariable(name: "nthreads", scope: !0, file: !1, line: 36, type: !157, isLocal: true, isDefinition: true, variable: i32* @nthreads)
!625 = !DIGlobalVariable(name: "threads", scope: !0, file: !1, line: 37, type: !626, isLocal: true, isDefinition: true, variable: i64** @threads)
!626 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !627, size: 64, align: 64)
!627 = !DIDerivedType(tag: DW_TAG_typedef, name: "uv_thread_t", file: !174, line: 128, baseType: !628)
!628 = !DIDerivedType(tag: DW_TAG_typedef, name: "pthread_t", file: !195, line: 60, baseType: !165)
!629 = !DIGlobalVariable(name: "default_threads", scope: !0, file: !1, line: 38, type: !630, isLocal: true, isDefinition: true, variable: [4 x i64]* @default_threads)
!630 = !DICompositeType(tag: DW_TAG_array_type, baseType: !627, size: 256, align: 64, elements: !251)
!631 = !DIGlobalVariable(name: "exit_message", scope: !0, file: !1, line: 39, type: !359, isLocal: true, isDefinition: true, variable: [2 x i8*]* @exit_message)
!632 = !DIGlobalVariable(name: "initialized", scope: !0, file: !1, line: 41, type: !633, isLocal: true, isDefinition: true, variable: i32* @initialized)
!633 = !DIDerivedType(tag: DW_TAG_volatile_type, baseType: !167)
!634 = !DIGlobalVariable(name: "wq", scope: !0, file: !1, line: 40, type: !359, isLocal: true, isDefinition: true, variable: [2 x i8*]* @wq)
!635 = !DIGlobalVariable(name: "idle_threads", scope: !0, file: !1, line: 35, type: !157, isLocal: true, isDefinition: true, variable: i32* @idle_threads)
!636 = !DIGlobalVariable(name: "once", scope: !0, file: !1, line: 32, type: !637, isLocal: true, isDefinition: true, variable: i32* @once)
!637 = !DIDerivedType(tag: DW_TAG_typedef, name: "uv_once_t", file: !174, line: 127, baseType: !638)
!638 = !DIDerivedType(tag: DW_TAG_typedef, name: "pthread_once_t", file: !195, line: 167, baseType: !167)
!639 = !{i32 2, !"Dwarf Version", i32 4}
!640 = !{i32 2, !"Debug Info Version", i32 3}
!641 = !{!"clang version 3.8.0 (tags/RELEASE_380/final)"}
!642 = !DILocalVariable(name: "i", scope: !564, file: !1, line: 106, type: !157)
!643 = !DIExpression()
!644 = !DILocation(line: 106, column: 16, scope: !564)
!645 = !DILocation(line: 108, column: 7, scope: !646)
!646 = distinct !DILexicalBlock(scope: !564, file: !1, line: 108, column: 7)
!647 = !DILocation(line: 108, column: 19, scope: !646)
!648 = !DILocation(line: 108, column: 7, scope: !564)
!649 = !DILocation(line: 109, column: 5, scope: !646)
!650 = !DILocation(line: 111, column: 3, scope: !564)
!651 = !DILocation(line: 113, column: 10, scope: !652)
!652 = distinct !DILexicalBlock(scope: !564, file: !1, line: 113, column: 3)
!653 = !DILocation(line: 113, column: 8, scope: !652)
!654 = !DILocation(line: 113, column: 15, scope: !655)
!655 = !DILexicalBlockFile(scope: !656, file: !1, discriminator: 1)
!656 = distinct !DILexicalBlock(scope: !652, file: !1, line: 113, column: 3)
!657 = !DILocation(line: 113, column: 19, scope: !655)
!658 = !DILocation(line: 113, column: 17, scope: !655)
!659 = !DILocation(line: 113, column: 3, scope: !655)
!660 = !DILocation(line: 114, column: 24, scope: !661)
!661 = distinct !DILexicalBlock(scope: !656, file: !1, line: 114, column: 9)
!662 = !DILocation(line: 114, column: 34, scope: !661)
!663 = !DILocation(line: 114, column: 32, scope: !661)
!664 = !DILocation(line: 114, column: 9, scope: !661)
!665 = !DILocation(line: 114, column: 9, scope: !656)
!666 = !DILocation(line: 115, column: 7, scope: !661)
!667 = !DILocation(line: 114, column: 35, scope: !668)
!668 = !DILexicalBlockFile(scope: !661, file: !1, discriminator: 1)
!669 = !DILocation(line: 113, column: 30, scope: !670)
!670 = !DILexicalBlockFile(scope: !656, file: !1, discriminator: 2)
!671 = !DILocation(line: 113, column: 3, scope: !670)
!672 = !DILocation(line: 117, column: 7, scope: !673)
!673 = distinct !DILexicalBlock(scope: !564, file: !1, line: 117, column: 7)
!674 = !DILocation(line: 117, column: 15, scope: !673)
!675 = !DILocation(line: 117, column: 7, scope: !564)
!676 = !DILocation(line: 118, column: 14, scope: !673)
!677 = !DILocation(line: 118, column: 5, scope: !673)
!678 = !DILocation(line: 120, column: 3, scope: !564)
!679 = !DILocation(line: 121, column: 3, scope: !564)
!680 = !DILocation(line: 123, column: 11, scope: !564)
!681 = !DILocation(line: 124, column: 12, scope: !564)
!682 = !DILocation(line: 125, column: 15, scope: !564)
!683 = !DILocation(line: 126, column: 1, scope: !564)
!684 = !DILocation(line: 126, column: 1, scope: !685)
!685 = !DILexicalBlockFile(scope: !564, file: !1, discriminator: 1)
!686 = !DILocalVariable(name: "q", arg: 1, scope: !584, file: !1, line: 95, type: !362)
!687 = !DILocation(line: 95, column: 25, scope: !584)
!688 = !DILocation(line: 96, column: 3, scope: !584)
!689 = !DILocation(line: 97, column: 3, scope: !584)
!690 = !DILocation(line: 97, column: 3, scope: !691)
!691 = !DILexicalBlockFile(scope: !692, file: !1, discriminator: 1)
!692 = distinct !DILexicalBlock(scope: !584, file: !1, line: 97, column: 3)
!693 = !DILocation(line: 98, column: 7, scope: !694)
!694 = distinct !DILexicalBlock(scope: !584, file: !1, line: 98, column: 7)
!695 = !DILocation(line: 98, column: 20, scope: !694)
!696 = !DILocation(line: 98, column: 7, scope: !584)
!697 = !DILocation(line: 99, column: 5, scope: !694)
!698 = !DILocation(line: 100, column: 3, scope: !584)
!699 = !DILocation(line: 101, column: 1, scope: !584)
!700 = !DILocalVariable(name: "loop", arg: 1, scope: !566, file: !1, line: 189, type: !150)
!701 = !DILocation(line: 189, column: 33, scope: !566)
!702 = !DILocalVariable(name: "w", arg: 2, scope: !566, file: !1, line: 190, type: !363)
!703 = !DILocation(line: 190, column: 39, scope: !566)
!704 = !DILocalVariable(name: "work", arg: 3, scope: !566, file: !1, line: 191, type: !368)
!705 = !DILocation(line: 191, column: 29, scope: !566)
!706 = !DILocalVariable(name: "done", arg: 4, scope: !566, file: !1, line: 192, type: !372)
!707 = !DILocation(line: 192, column: 29, scope: !566)
!708 = !DILocation(line: 193, column: 3, scope: !566)
!709 = !DILocation(line: 194, column: 13, scope: !566)
!710 = !DILocation(line: 194, column: 3, scope: !566)
!711 = !DILocation(line: 194, column: 6, scope: !566)
!712 = !DILocation(line: 194, column: 11, scope: !566)
!713 = !DILocation(line: 195, column: 13, scope: !566)
!714 = !DILocation(line: 195, column: 3, scope: !566)
!715 = !DILocation(line: 195, column: 6, scope: !566)
!716 = !DILocation(line: 195, column: 11, scope: !566)
!717 = !DILocation(line: 196, column: 13, scope: !566)
!718 = !DILocation(line: 196, column: 3, scope: !566)
!719 = !DILocation(line: 196, column: 6, scope: !566)
!720 = !DILocation(line: 196, column: 11, scope: !566)
!721 = !DILocation(line: 197, column: 9, scope: !566)
!722 = !DILocation(line: 197, column: 12, scope: !566)
!723 = !DILocation(line: 197, column: 3, scope: !566)
!724 = !DILocation(line: 198, column: 1, scope: !566)
!725 = !DILocation(line: 182, column: 7, scope: !726)
!726 = distinct !DILexicalBlock(scope: !587, file: !1, line: 182, column: 7)
!727 = !DILocation(line: 182, column: 7, scope: !587)
!728 = !DILocation(line: 183, column: 5, scope: !726)
!729 = !DILocation(line: 185, column: 3, scope: !587)
!730 = !DILocation(line: 186, column: 1, scope: !587)
!731 = !DILocalVariable(name: "handle", arg: 1, scope: !569, file: !1, line: 227, type: !268)
!732 = !DILocation(line: 227, column: 32, scope: !569)
!733 = !DILocalVariable(name: "w", scope: !569, file: !1, line: 228, type: !363)
!734 = !DILocation(line: 228, column: 20, scope: !569)
!735 = !DILocalVariable(name: "loop", scope: !569, file: !1, line: 229, type: !150)
!736 = !DILocation(line: 229, column: 14, scope: !569)
!737 = !DILocalVariable(name: "q", scope: !569, file: !1, line: 230, type: !362)
!738 = !DILocation(line: 230, column: 10, scope: !569)
!739 = !DILocalVariable(name: "wq", scope: !569, file: !1, line: 231, type: !359)
!740 = !DILocation(line: 231, column: 9, scope: !569)
!741 = !DILocalVariable(name: "err", scope: !569, file: !1, line: 232, type: !167)
!742 = !DILocation(line: 232, column: 7, scope: !569)
!743 = !DILocation(line: 234, column: 10, scope: !569)
!744 = !DILocation(line: 234, column: 8, scope: !569)
!745 = !DILocation(line: 235, column: 18, scope: !569)
!746 = !DILocation(line: 235, column: 24, scope: !569)
!747 = !DILocation(line: 235, column: 3, scope: !569)
!748 = !DILocation(line: 236, column: 3, scope: !569)
!749 = !DILocation(line: 236, column: 3, scope: !750)
!750 = !DILexicalBlockFile(scope: !751, file: !1, discriminator: 1)
!751 = distinct !DILexicalBlock(scope: !752, file: !1, line: 236, column: 3)
!752 = distinct !DILexicalBlock(scope: !569, file: !1, line: 236, column: 3)
!753 = !DILocation(line: 236, column: 3, scope: !754)
!754 = !DILexicalBlockFile(scope: !751, file: !1, discriminator: 2)
!755 = !DILocation(line: 236, column: 3, scope: !756)
!756 = !DILexicalBlockFile(scope: !757, file: !1, discriminator: 3)
!757 = distinct !DILexicalBlock(scope: !751, file: !1, line: 236, column: 3)
!758 = !DILocation(line: 236, column: 3, scope: !759)
!759 = !DILexicalBlockFile(scope: !757, file: !1, discriminator: 4)
!760 = !DILocalVariable(name: "q", scope: !761, file: !1, line: 236, type: !362)
!761 = distinct !DILexicalBlock(scope: !751, file: !1, line: 236, column: 3)
!762 = !DILocation(line: 236, column: 3, scope: !761)
!763 = !DILocation(line: 236, column: 3, scope: !764)
!764 = !DILexicalBlockFile(scope: !761, file: !1, discriminator: 5)
!765 = !DILocation(line: 236, column: 3, scope: !766)
!766 = !DILexicalBlockFile(scope: !767, file: !1, discriminator: 6)
!767 = distinct !DILexicalBlock(scope: !761, file: !1, line: 236, column: 3)
!768 = !DILocation(line: 236, column: 3, scope: !769)
!769 = !DILexicalBlockFile(scope: !752, file: !1, discriminator: 7)
!770 = !DILocation(line: 237, column: 20, scope: !569)
!771 = !DILocation(line: 237, column: 26, scope: !569)
!772 = !DILocation(line: 237, column: 3, scope: !569)
!773 = !DILocation(line: 239, column: 3, scope: !569)
!774 = !DILocation(line: 239, column: 11, scope: !775)
!775 = !DILexicalBlockFile(scope: !569, file: !1, discriminator: 1)
!776 = !DILocation(line: 239, column: 10, scope: !775)
!777 = !DILocation(line: 239, column: 3, scope: !775)
!778 = !DILocation(line: 240, column: 9, scope: !779)
!779 = distinct !DILexicalBlock(scope: !569, file: !1, line: 239, column: 29)
!780 = !DILocation(line: 240, column: 7, scope: !779)
!781 = !DILocation(line: 241, column: 5, scope: !779)
!782 = !DILocation(line: 241, column: 5, scope: !783)
!783 = !DILexicalBlockFile(scope: !784, file: !1, discriminator: 1)
!784 = distinct !DILexicalBlock(scope: !779, file: !1, line: 241, column: 5)
!785 = !DILocation(line: 243, column: 9, scope: !779)
!786 = !DILocation(line: 243, column: 7, scope: !779)
!787 = !DILocation(line: 244, column: 12, scope: !779)
!788 = !DILocation(line: 244, column: 15, scope: !779)
!789 = !DILocation(line: 244, column: 20, scope: !779)
!790 = !DILocation(line: 244, column: 11, scope: !779)
!791 = !DILocation(line: 244, column: 9, scope: !779)
!792 = !DILocation(line: 245, column: 5, scope: !779)
!793 = !DILocation(line: 245, column: 8, scope: !779)
!794 = !DILocation(line: 245, column: 13, scope: !779)
!795 = !DILocation(line: 245, column: 16, scope: !779)
!796 = !DILocation(line: 239, column: 3, scope: !797)
!797 = !DILexicalBlockFile(scope: !569, file: !1, discriminator: 2)
!798 = !DILocation(line: 247, column: 1, scope: !569)
!799 = !DILocalVariable(name: "w", arg: 1, scope: !593, file: !1, line: 44, type: !363)
!800 = !DILocation(line: 44, column: 44, scope: !593)
!801 = !DILocation(line: 45, column: 3, scope: !593)
!802 = !DILocation(line: 46, column: 1, scope: !593)
!803 = !DILocalVariable(name: "loop", arg: 1, scope: !570, file: !1, line: 270, type: !150)
!804 = !DILocation(line: 270, column: 30, scope: !570)
!805 = !DILocalVariable(name: "req", arg: 2, scope: !570, file: !1, line: 271, type: !543)
!806 = !DILocation(line: 271, column: 30, scope: !570)
!807 = !DILocalVariable(name: "work_cb", arg: 3, scope: !570, file: !1, line: 272, type: !553)
!808 = !DILocation(line: 272, column: 30, scope: !570)
!809 = !DILocalVariable(name: "after_work_cb", arg: 4, scope: !570, file: !1, line: 273, type: !558)
!810 = !DILocation(line: 273, column: 36, scope: !570)
!811 = !DILocation(line: 274, column: 7, scope: !812)
!812 = distinct !DILexicalBlock(scope: !570, file: !1, line: 274, column: 7)
!813 = !DILocation(line: 274, column: 15, scope: !812)
!814 = !DILocation(line: 274, column: 7, scope: !570)
!815 = !DILocation(line: 275, column: 5, scope: !812)
!816 = !DILocation(line: 277, column: 3, scope: !570)
!817 = !DILocation(line: 277, column: 3, scope: !818)
!818 = !DILexicalBlockFile(scope: !819, file: !1, discriminator: 1)
!819 = distinct !DILexicalBlock(scope: !570, file: !1, line: 277, column: 3)
!820 = !DILocation(line: 277, column: 3, scope: !821)
!821 = !DILexicalBlockFile(scope: !822, file: !1, discriminator: 2)
!822 = distinct !DILexicalBlock(scope: !819, file: !1, line: 277, column: 3)
!823 = !DILocation(line: 277, column: 3, scope: !824)
!824 = !DILexicalBlockFile(scope: !819, file: !1, discriminator: 3)
!825 = !DILocation(line: 277, column: 3, scope: !826)
!826 = !DILexicalBlockFile(scope: !827, file: !1, discriminator: 4)
!827 = distinct !DILexicalBlock(scope: !819, file: !1, line: 277, column: 3)
!828 = !DILocation(line: 277, column: 3, scope: !829)
!829 = !DILexicalBlockFile(scope: !830, file: !1, discriminator: 5)
!830 = distinct !DILexicalBlock(scope: !827, file: !1, line: 277, column: 3)
!831 = !DILocation(line: 277, column: 3, scope: !832)
!832 = !DILexicalBlockFile(scope: !827, file: !1, discriminator: 6)
!833 = !DILocation(line: 277, column: 3, scope: !834)
!834 = !DILexicalBlockFile(scope: !819, file: !1, discriminator: 7)
!835 = !DILocation(line: 278, column: 15, scope: !570)
!836 = !DILocation(line: 278, column: 3, scope: !570)
!837 = !DILocation(line: 278, column: 8, scope: !570)
!838 = !DILocation(line: 278, column: 13, scope: !570)
!839 = !DILocation(line: 279, column: 18, scope: !570)
!840 = !DILocation(line: 279, column: 3, scope: !570)
!841 = !DILocation(line: 279, column: 8, scope: !570)
!842 = !DILocation(line: 279, column: 16, scope: !570)
!843 = !DILocation(line: 280, column: 24, scope: !570)
!844 = !DILocation(line: 280, column: 3, scope: !570)
!845 = !DILocation(line: 280, column: 8, scope: !570)
!846 = !DILocation(line: 280, column: 22, scope: !570)
!847 = !DILocation(line: 281, column: 19, scope: !570)
!848 = !DILocation(line: 281, column: 26, scope: !570)
!849 = !DILocation(line: 281, column: 31, scope: !570)
!850 = !DILocation(line: 281, column: 3, scope: !570)
!851 = !DILocation(line: 282, column: 3, scope: !570)
!852 = !DILocation(line: 283, column: 1, scope: !570)
!853 = !DILocalVariable(name: "w", arg: 1, scope: !594, file: !1, line: 250, type: !363)
!854 = !DILocation(line: 250, column: 45, scope: !594)
!855 = !DILocalVariable(name: "req", scope: !594, file: !1, line: 251, type: !543)
!856 = !DILocation(line: 251, column: 14, scope: !594)
!857 = !DILocation(line: 251, column: 20, scope: !594)
!858 = !DILocation(line: 253, column: 3, scope: !594)
!859 = !DILocation(line: 253, column: 8, scope: !594)
!860 = !DILocation(line: 253, column: 16, scope: !594)
!861 = !DILocation(line: 254, column: 1, scope: !594)
!862 = !DILocalVariable(name: "w", arg: 1, scope: !595, file: !1, line: 257, type: !363)
!863 = !DILocation(line: 257, column: 45, scope: !595)
!864 = !DILocalVariable(name: "err", arg: 2, scope: !595, file: !1, line: 257, type: !167)
!865 = !DILocation(line: 257, column: 52, scope: !595)
!866 = !DILocalVariable(name: "req", scope: !595, file: !1, line: 258, type: !543)
!867 = !DILocation(line: 258, column: 14, scope: !595)
!868 = !DILocation(line: 260, column: 9, scope: !595)
!869 = !DILocation(line: 260, column: 7, scope: !595)
!870 = !DILocation(line: 261, column: 3, scope: !595)
!871 = !DILocation(line: 261, column: 3, scope: !872)
!872 = !DILexicalBlockFile(scope: !873, file: !1, discriminator: 1)
!873 = distinct !DILexicalBlock(scope: !595, file: !1, line: 261, column: 3)
!874 = !DILocation(line: 261, column: 3, scope: !875)
!875 = !DILexicalBlockFile(scope: !873, file: !1, discriminator: 2)
!876 = !DILocation(line: 261, column: 3, scope: !877)
!877 = !DILexicalBlockFile(scope: !873, file: !1, discriminator: 3)
!878 = !DILocation(line: 261, column: 3, scope: !879)
!879 = !DILexicalBlockFile(scope: !873, file: !1, discriminator: 4)
!880 = !DILocation(line: 261, column: 3, scope: !881)
!881 = !DILexicalBlockFile(scope: !873, file: !1, discriminator: 5)
!882 = !DILocation(line: 261, column: 3, scope: !883)
!883 = !DILexicalBlockFile(scope: !884, file: !1, discriminator: 6)
!884 = distinct !DILexicalBlock(scope: !873, file: !1, line: 261, column: 3)
!885 = !DILocation(line: 261, column: 3, scope: !886)
!886 = !DILexicalBlockFile(scope: !873, file: !1, discriminator: 7)
!887 = !DILocation(line: 263, column: 7, scope: !888)
!888 = distinct !DILexicalBlock(scope: !595, file: !1, line: 263, column: 7)
!889 = !DILocation(line: 263, column: 12, scope: !888)
!890 = !DILocation(line: 263, column: 26, scope: !888)
!891 = !DILocation(line: 263, column: 7, scope: !595)
!892 = !DILocation(line: 264, column: 5, scope: !888)
!893 = !DILocation(line: 266, column: 3, scope: !595)
!894 = !DILocation(line: 266, column: 8, scope: !595)
!895 = !DILocation(line: 266, column: 22, scope: !595)
!896 = !DILocation(line: 266, column: 27, scope: !595)
!897 = !DILocation(line: 267, column: 1, scope: !595)
!898 = !DILocation(line: 267, column: 1, scope: !899)
!899 = !DILexicalBlockFile(scope: !595, file: !1, discriminator: 1)
!900 = !DILocalVariable(name: "req", arg: 1, scope: !573, file: !1, line: 286, type: !576)
!901 = !DILocation(line: 286, column: 25, scope: !573)
!902 = !DILocalVariable(name: "wreq", scope: !573, file: !1, line: 287, type: !363)
!903 = !DILocation(line: 287, column: 20, scope: !573)
!904 = !DILocalVariable(name: "loop", scope: !573, file: !1, line: 288, type: !150)
!905 = !DILocation(line: 288, column: 14, scope: !573)
!906 = !DILocation(line: 290, column: 11, scope: !573)
!907 = !DILocation(line: 290, column: 16, scope: !573)
!908 = !DILocation(line: 290, column: 3, scope: !573)
!909 = !DILocation(line: 292, column: 25, scope: !910)
!910 = distinct !DILexicalBlock(scope: !573, file: !1, line: 290, column: 22)
!911 = !DILocation(line: 292, column: 31, scope: !910)
!912 = !DILocation(line: 292, column: 10, scope: !910)
!913 = !DILocation(line: 293, column: 25, scope: !910)
!914 = !DILocation(line: 293, column: 31, scope: !910)
!915 = !DILocation(line: 293, column: 10, scope: !910)
!916 = !DILocation(line: 294, column: 5, scope: !910)
!917 = !DILocation(line: 296, column: 34, scope: !910)
!918 = !DILocation(line: 296, column: 40, scope: !910)
!919 = !DILocation(line: 296, column: 10, scope: !910)
!920 = !DILocation(line: 297, column: 34, scope: !910)
!921 = !DILocation(line: 297, column: 40, scope: !910)
!922 = !DILocation(line: 297, column: 10, scope: !910)
!923 = !DILocation(line: 298, column: 5, scope: !910)
!924 = !DILocation(line: 300, column: 33, scope: !910)
!925 = !DILocation(line: 300, column: 39, scope: !910)
!926 = !DILocation(line: 300, column: 10, scope: !910)
!927 = !DILocation(line: 301, column: 34, scope: !910)
!928 = !DILocation(line: 301, column: 40, scope: !910)
!929 = !DILocation(line: 301, column: 10, scope: !910)
!930 = !DILocation(line: 302, column: 5, scope: !910)
!931 = !DILocation(line: 304, column: 27, scope: !910)
!932 = !DILocation(line: 304, column: 33, scope: !910)
!933 = !DILocation(line: 304, column: 10, scope: !910)
!934 = !DILocation(line: 305, column: 27, scope: !910)
!935 = !DILocation(line: 305, column: 33, scope: !910)
!936 = !DILocation(line: 305, column: 10, scope: !910)
!937 = !DILocation(line: 306, column: 5, scope: !910)
!938 = !DILocation(line: 308, column: 5, scope: !910)
!939 = !DILocation(line: 311, column: 26, scope: !573)
!940 = !DILocation(line: 311, column: 32, scope: !573)
!941 = !DILocation(line: 311, column: 37, scope: !573)
!942 = !DILocation(line: 311, column: 10, scope: !573)
!943 = !DILocation(line: 311, column: 3, scope: !573)
!944 = !DILocation(line: 312, column: 1, scope: !573)
!945 = !DILocalVariable(name: "loop", arg: 1, scope: !596, file: !1, line: 201, type: !150)
!946 = !DILocation(line: 201, column: 39, scope: !596)
!947 = !DILocalVariable(name: "req", arg: 2, scope: !596, file: !1, line: 201, type: !576)
!948 = !DILocation(line: 201, column: 55, scope: !596)
!949 = !DILocalVariable(name: "w", arg: 3, scope: !596, file: !1, line: 201, type: !363)
!950 = !DILocation(line: 201, column: 77, scope: !596)
!951 = !DILocalVariable(name: "cancelled", scope: !596, file: !1, line: 202, type: !167)
!952 = !DILocation(line: 202, column: 7, scope: !596)
!953 = !DILocation(line: 204, column: 3, scope: !596)
!954 = !DILocation(line: 205, column: 18, scope: !596)
!955 = !DILocation(line: 205, column: 21, scope: !596)
!956 = !DILocation(line: 205, column: 27, scope: !596)
!957 = !DILocation(line: 205, column: 3, scope: !596)
!958 = !DILocation(line: 207, column: 16, scope: !596)
!959 = !DILocation(line: 207, column: 36, scope: !596)
!960 = !DILocation(line: 207, column: 39, scope: !961)
!961 = !DILexicalBlockFile(scope: !596, file: !1, discriminator: 1)
!962 = !DILocation(line: 207, column: 42, scope: !961)
!963 = !DILocation(line: 207, column: 47, scope: !961)
!964 = !DILocation(line: 207, column: 36, scope: !965)
!965 = !DILexicalBlockFile(scope: !596, file: !1, discriminator: 2)
!966 = !DILocation(line: 207, column: 13, scope: !965)
!967 = !DILocation(line: 208, column: 7, scope: !968)
!968 = distinct !DILexicalBlock(scope: !596, file: !1, line: 208, column: 7)
!969 = !DILocation(line: 208, column: 7, scope: !596)
!970 = !DILocation(line: 209, column: 5, scope: !968)
!971 = !DILocation(line: 209, column: 5, scope: !972)
!972 = !DILexicalBlockFile(scope: !973, file: !1, discriminator: 1)
!973 = distinct !DILexicalBlock(scope: !968, file: !1, line: 209, column: 5)
!974 = !DILocation(line: 209, column: 5, scope: !975)
!975 = !DILexicalBlockFile(scope: !973, file: !1, discriminator: 2)
!976 = !DILocation(line: 211, column: 20, scope: !596)
!977 = !DILocation(line: 211, column: 23, scope: !596)
!978 = !DILocation(line: 211, column: 29, scope: !596)
!979 = !DILocation(line: 211, column: 3, scope: !596)
!980 = !DILocation(line: 212, column: 3, scope: !596)
!981 = !DILocation(line: 214, column: 8, scope: !982)
!982 = distinct !DILexicalBlock(scope: !596, file: !1, line: 214, column: 7)
!983 = !DILocation(line: 214, column: 7, scope: !596)
!984 = !DILocation(line: 215, column: 5, scope: !982)
!985 = !DILocation(line: 217, column: 3, scope: !596)
!986 = !DILocation(line: 217, column: 6, scope: !596)
!987 = !DILocation(line: 217, column: 11, scope: !596)
!988 = !DILocation(line: 218, column: 18, scope: !596)
!989 = !DILocation(line: 218, column: 24, scope: !596)
!990 = !DILocation(line: 218, column: 3, scope: !596)
!991 = !DILocation(line: 219, column: 3, scope: !596)
!992 = !DILocation(line: 219, column: 3, scope: !993)
!993 = !DILexicalBlockFile(scope: !994, file: !1, discriminator: 1)
!994 = distinct !DILexicalBlock(scope: !596, file: !1, line: 219, column: 3)
!995 = !DILocation(line: 220, column: 18, scope: !596)
!996 = !DILocation(line: 220, column: 24, scope: !596)
!997 = !DILocation(line: 220, column: 3, scope: !596)
!998 = !DILocation(line: 221, column: 20, scope: !596)
!999 = !DILocation(line: 221, column: 26, scope: !596)
!1000 = !DILocation(line: 221, column: 3, scope: !596)
!1001 = !DILocation(line: 223, column: 3, scope: !596)
!1002 = !DILocation(line: 224, column: 1, scope: !596)
!1003 = !DILocalVariable(name: "child_once", scope: !588, file: !1, line: 170, type: !637)
!1004 = !DILocation(line: 170, column: 13, scope: !588)
!1005 = !DILocation(line: 171, column: 3, scope: !588)
!1006 = !DILocation(line: 172, column: 1, scope: !588)
!1007 = !DILocalVariable(name: "i", scope: !589, file: !1, line: 131, type: !157)
!1008 = !DILocation(line: 131, column: 16, scope: !589)
!1009 = !DILocalVariable(name: "val", scope: !589, file: !1, line: 132, type: !401)
!1010 = !DILocation(line: 132, column: 15, scope: !589)
!1011 = !DILocation(line: 134, column: 12, scope: !589)
!1012 = !DILocation(line: 135, column: 9, scope: !589)
!1013 = !DILocation(line: 135, column: 7, scope: !589)
!1014 = !DILocation(line: 136, column: 7, scope: !1015)
!1015 = distinct !DILexicalBlock(scope: !589, file: !1, line: 136, column: 7)
!1016 = !DILocation(line: 136, column: 11, scope: !1015)
!1017 = !DILocation(line: 136, column: 7, scope: !589)
!1018 = !DILocation(line: 137, column: 21, scope: !1015)
!1019 = !DILocation(line: 137, column: 16, scope: !1015)
!1020 = !DILocation(line: 137, column: 14, scope: !1015)
!1021 = !DILocation(line: 137, column: 5, scope: !1015)
!1022 = !DILocation(line: 138, column: 7, scope: !1023)
!1023 = distinct !DILexicalBlock(scope: !589, file: !1, line: 138, column: 7)
!1024 = !DILocation(line: 138, column: 16, scope: !1023)
!1025 = !DILocation(line: 138, column: 7, scope: !589)
!1026 = !DILocation(line: 139, column: 14, scope: !1023)
!1027 = !DILocation(line: 139, column: 5, scope: !1023)
!1028 = !DILocation(line: 140, column: 7, scope: !1029)
!1029 = distinct !DILexicalBlock(scope: !589, file: !1, line: 140, column: 7)
!1030 = !DILocation(line: 140, column: 16, scope: !1029)
!1031 = !DILocation(line: 140, column: 7, scope: !589)
!1032 = !DILocation(line: 141, column: 14, scope: !1029)
!1033 = !DILocation(line: 141, column: 5, scope: !1029)
!1034 = !DILocation(line: 143, column: 11, scope: !589)
!1035 = !DILocation(line: 144, column: 7, scope: !1036)
!1036 = distinct !DILexicalBlock(scope: !589, file: !1, line: 144, column: 7)
!1037 = !DILocation(line: 144, column: 16, scope: !1036)
!1038 = !DILocation(line: 144, column: 7, scope: !589)
!1039 = !DILocation(line: 145, column: 26, scope: !1040)
!1040 = distinct !DILexicalBlock(scope: !1036, file: !1, line: 144, column: 47)
!1041 = !DILocation(line: 145, column: 35, scope: !1040)
!1042 = !DILocation(line: 145, column: 15, scope: !1040)
!1043 = !DILocation(line: 145, column: 13, scope: !1040)
!1044 = !DILocation(line: 146, column: 9, scope: !1045)
!1045 = distinct !DILexicalBlock(scope: !1040, file: !1, line: 146, column: 9)
!1046 = !DILocation(line: 146, column: 17, scope: !1045)
!1047 = !DILocation(line: 146, column: 9, scope: !1040)
!1048 = !DILocation(line: 147, column: 16, scope: !1049)
!1049 = distinct !DILexicalBlock(scope: !1045, file: !1, line: 146, column: 26)
!1050 = !DILocation(line: 148, column: 15, scope: !1049)
!1051 = !DILocation(line: 149, column: 5, scope: !1049)
!1052 = !DILocation(line: 150, column: 3, scope: !1040)
!1053 = !DILocation(line: 152, column: 7, scope: !1054)
!1054 = distinct !DILexicalBlock(scope: !589, file: !1, line: 152, column: 7)
!1055 = !DILocation(line: 152, column: 7, scope: !589)
!1056 = !DILocation(line: 153, column: 5, scope: !1054)
!1057 = !DILocation(line: 155, column: 7, scope: !1058)
!1058 = distinct !DILexicalBlock(scope: !589, file: !1, line: 155, column: 7)
!1059 = !DILocation(line: 155, column: 7, scope: !589)
!1060 = !DILocation(line: 156, column: 5, scope: !1058)
!1061 = !DILocation(line: 158, column: 3, scope: !589)
!1062 = !DILocation(line: 158, column: 3, scope: !1063)
!1063 = !DILexicalBlockFile(scope: !1064, file: !1, discriminator: 1)
!1064 = distinct !DILexicalBlock(scope: !589, file: !1, line: 158, column: 3)
!1065 = !DILocation(line: 160, column: 10, scope: !1066)
!1066 = distinct !DILexicalBlock(scope: !589, file: !1, line: 160, column: 3)
!1067 = !DILocation(line: 160, column: 8, scope: !1066)
!1068 = !DILocation(line: 160, column: 15, scope: !1069)
!1069 = !DILexicalBlockFile(scope: !1070, file: !1, discriminator: 1)
!1070 = distinct !DILexicalBlock(scope: !1066, file: !1, line: 160, column: 3)
!1071 = !DILocation(line: 160, column: 19, scope: !1069)
!1072 = !DILocation(line: 160, column: 17, scope: !1069)
!1073 = !DILocation(line: 160, column: 3, scope: !1069)
!1074 = !DILocation(line: 161, column: 26, scope: !1075)
!1075 = distinct !DILexicalBlock(scope: !1070, file: !1, line: 161, column: 9)
!1076 = !DILocation(line: 161, column: 36, scope: !1075)
!1077 = !DILocation(line: 161, column: 34, scope: !1075)
!1078 = !DILocation(line: 161, column: 9, scope: !1075)
!1079 = !DILocation(line: 161, column: 9, scope: !1070)
!1080 = !DILocation(line: 162, column: 7, scope: !1075)
!1081 = !DILocation(line: 161, column: 51, scope: !1082)
!1082 = !DILexicalBlockFile(scope: !1075, file: !1, discriminator: 1)
!1083 = !DILocation(line: 160, column: 30, scope: !1084)
!1084 = !DILexicalBlockFile(scope: !1070, file: !1, discriminator: 2)
!1085 = !DILocation(line: 160, column: 3, scope: !1084)
!1086 = !DILocation(line: 164, column: 15, scope: !589)
!1087 = !DILocation(line: 165, column: 1, scope: !589)
!1088 = !DILocalVariable(name: "arg", arg: 1, scope: !590, file: !1, line: 52, type: !155)
!1089 = !DILocation(line: 52, column: 26, scope: !590)
!1090 = !DILocalVariable(name: "w", scope: !590, file: !1, line: 53, type: !363)
!1091 = !DILocation(line: 53, column: 20, scope: !590)
!1092 = !DILocalVariable(name: "q", scope: !590, file: !1, line: 54, type: !362)
!1093 = !DILocation(line: 54, column: 10, scope: !590)
!1094 = !DILocation(line: 56, column: 10, scope: !590)
!1095 = !DILocation(line: 58, column: 3, scope: !590)
!1096 = !DILocation(line: 59, column: 5, scope: !1097)
!1097 = distinct !DILexicalBlock(scope: !1098, file: !1, line: 58, column: 12)
!1098 = distinct !DILexicalBlock(scope: !1099, file: !1, line: 58, column: 3)
!1099 = distinct !DILexicalBlock(scope: !590, file: !1, line: 58, column: 3)
!1100 = !DILocation(line: 61, column: 5, scope: !1097)
!1101 = !DILocation(line: 61, column: 12, scope: !1102)
!1102 = !DILexicalBlockFile(scope: !1097, file: !1, discriminator: 1)
!1103 = !DILocation(line: 61, column: 5, scope: !1102)
!1104 = !DILocation(line: 62, column: 20, scope: !1105)
!1105 = distinct !DILexicalBlock(scope: !1097, file: !1, line: 61, column: 30)
!1106 = !DILocation(line: 63, column: 7, scope: !1105)
!1107 = !DILocation(line: 64, column: 20, scope: !1105)
!1108 = !DILocation(line: 61, column: 5, scope: !1109)
!1109 = !DILexicalBlockFile(scope: !1097, file: !1, discriminator: 2)
!1110 = !DILocation(line: 67, column: 9, scope: !1097)
!1111 = !DILocation(line: 67, column: 7, scope: !1097)
!1112 = !DILocation(line: 69, column: 9, scope: !1113)
!1113 = distinct !DILexicalBlock(scope: !1097, file: !1, line: 69, column: 9)
!1114 = !DILocation(line: 69, column: 11, scope: !1113)
!1115 = !DILocation(line: 69, column: 9, scope: !1097)
!1116 = !DILocation(line: 70, column: 7, scope: !1113)
!1117 = !DILocation(line: 72, column: 7, scope: !1118)
!1118 = distinct !DILexicalBlock(scope: !1113, file: !1, line: 71, column: 10)
!1119 = !DILocation(line: 72, column: 7, scope: !1120)
!1120 = !DILexicalBlockFile(scope: !1121, file: !1, discriminator: 1)
!1121 = distinct !DILexicalBlock(scope: !1118, file: !1, line: 72, column: 7)
!1122 = !DILocation(line: 73, column: 7, scope: !1118)
!1123 = !DILocation(line: 73, column: 7, scope: !1124)
!1124 = !DILexicalBlockFile(scope: !1125, file: !1, discriminator: 1)
!1125 = distinct !DILexicalBlock(scope: !1118, file: !1, line: 73, column: 7)
!1126 = !DILocation(line: 77, column: 5, scope: !1097)
!1127 = !DILocation(line: 79, column: 9, scope: !1128)
!1128 = distinct !DILexicalBlock(scope: !1097, file: !1, line: 79, column: 9)
!1129 = !DILocation(line: 79, column: 11, scope: !1128)
!1130 = !DILocation(line: 79, column: 9, scope: !1097)
!1131 = !DILocation(line: 80, column: 7, scope: !1128)
!1132 = !DILocation(line: 82, column: 9, scope: !1097)
!1133 = !DILocation(line: 82, column: 7, scope: !1097)
!1134 = !DILocation(line: 83, column: 5, scope: !1097)
!1135 = !DILocation(line: 83, column: 8, scope: !1097)
!1136 = !DILocation(line: 83, column: 13, scope: !1097)
!1137 = !DILocation(line: 85, column: 20, scope: !1097)
!1138 = !DILocation(line: 85, column: 23, scope: !1097)
!1139 = !DILocation(line: 85, column: 29, scope: !1097)
!1140 = !DILocation(line: 85, column: 5, scope: !1097)
!1141 = !DILocation(line: 86, column: 5, scope: !1097)
!1142 = !DILocation(line: 86, column: 8, scope: !1097)
!1143 = !DILocation(line: 86, column: 13, scope: !1097)
!1144 = !DILocation(line: 88, column: 5, scope: !1097)
!1145 = !DILocation(line: 88, column: 5, scope: !1146)
!1146 = !DILexicalBlockFile(scope: !1147, file: !1, discriminator: 1)
!1147 = distinct !DILexicalBlock(scope: !1097, file: !1, line: 88, column: 5)
!1148 = !DILocation(line: 89, column: 20, scope: !1097)
!1149 = !DILocation(line: 89, column: 23, scope: !1097)
!1150 = !DILocation(line: 89, column: 29, scope: !1097)
!1151 = !DILocation(line: 89, column: 5, scope: !1097)
!1152 = !DILocation(line: 90, column: 22, scope: !1097)
!1153 = !DILocation(line: 90, column: 25, scope: !1097)
!1154 = !DILocation(line: 90, column: 31, scope: !1097)
!1155 = !DILocation(line: 90, column: 5, scope: !1097)
!1156 = !DILocation(line: 58, column: 3, scope: !1157)
!1157 = !DILexicalBlockFile(scope: !1098, file: !1, discriminator: 1)
!1158 = !DILocation(line: 92, column: 1, scope: !590)
