; ModuleID = '/data/download/cmake/cmake-master/Utilities/cmlibuv/src/unix/fs.c'
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
%struct.uv_fs_s = type { i8*, i32, [2 x i8*], [4 x i8*], i32, %struct.uv_loop_s*, void (%struct.uv_fs_s*)*, i64, i8*, i8*, %struct.uv_stat_t, i8*, i32, i32, i32, i32, %struct.uv_buf_t*, i64, i32, i32, double, double, %struct.uv__work, [4 x %struct.uv_buf_t] }
%struct.uv_stat_t = type { i64, i64, i64, i64, i64, i64, i64, i64, i64, i64, i64, i64, %struct.uv_timespec_t, %struct.uv_timespec_t, %struct.uv_timespec_t, %struct.uv_timespec_t }
%struct.uv_timespec_t = type { i64, i64 }
%struct.uv_buf_t = type { i8*, i64 }
%struct.uv__work = type { void (%struct.uv__work*)*, void (%struct.uv__work*, i32)*, %struct.uv_loop_s*, [2 x i8*] }
%struct.stat = type { i64, i64, i64, i32, i32, i32, i32, i64, i64, i64, i64, %struct.timespec, %struct.timespec, %struct.timespec, [3 x i64] }
%struct.timespec = type { i64, i64 }
%struct.timeval = type { i64, i64 }
%struct.iovec = type { i8*, i64 }
%struct.dirent = type { i64, i64, i16, i8, [256 x i8] }
%struct.utimbuf = type { i64, i64 }
%struct.pollfd = type { i32, i16, i16 }

@.str = private unnamed_addr constant [19 x i8] c"path != ((void*)0)\00", align 1
@.str.1 = private unnamed_addr constant [66 x i8] c"/data/download/cmake/cmake-master/Utilities/cmlibuv/src/unix/fs.c\00", align 1
@__PRETTY_FUNCTION__.uv_fs_access = private unnamed_addr constant [70 x i8] c"int uv_fs_access(uv_loop_t *, uv_fs_t *, const char *, int, uv_fs_cb)\00", align 1
@.str.2 = private unnamed_addr constant [113 x i8] c"(((const QUEUE *) (&(loop)->active_reqs) == (const QUEUE *) (*(QUEUE **) &((*(&(loop)->active_reqs))[0]))) == 0)\00", align 1
@__PRETTY_FUNCTION__.uv_fs_chmod = private unnamed_addr constant [69 x i8] c"int uv_fs_chmod(uv_loop_t *, uv_fs_t *, const char *, int, uv_fs_cb)\00", align 1
@__PRETTY_FUNCTION__.uv_fs_chown = private unnamed_addr constant [84 x i8] c"int uv_fs_chown(uv_loop_t *, uv_fs_t *, const char *, uv_uid_t, uv_gid_t, uv_fs_cb)\00", align 1
@__PRETTY_FUNCTION__.uv_fs_lstat = private unnamed_addr constant [64 x i8] c"int uv_fs_lstat(uv_loop_t *, uv_fs_t *, const char *, uv_fs_cb)\00", align 1
@__PRETTY_FUNCTION__.uv_fs_link = private unnamed_addr constant [77 x i8] c"int uv_fs_link(uv_loop_t *, uv_fs_t *, const char *, const char *, uv_fs_cb)\00", align 1
@__PRETTY_FUNCTION__.uv_fs_mkdir = private unnamed_addr constant [69 x i8] c"int uv_fs_mkdir(uv_loop_t *, uv_fs_t *, const char *, int, uv_fs_cb)\00", align 1
@__PRETTY_FUNCTION__.uv_fs_mkdtemp = private unnamed_addr constant [66 x i8] c"int uv_fs_mkdtemp(uv_loop_t *, uv_fs_t *, const char *, uv_fs_cb)\00", align 1
@__PRETTY_FUNCTION__.uv_fs_open = private unnamed_addr constant [73 x i8] c"int uv_fs_open(uv_loop_t *, uv_fs_t *, const char *, int, int, uv_fs_cb)\00", align 1
@__PRETTY_FUNCTION__.uv_fs_read = private unnamed_addr constant [99 x i8] c"int uv_fs_read(uv_loop_t *, uv_fs_t *, uv_file, const uv_buf_t *, unsigned int, int64_t, uv_fs_cb)\00", align 1
@__PRETTY_FUNCTION__.uv_fs_scandir = private unnamed_addr constant [71 x i8] c"int uv_fs_scandir(uv_loop_t *, uv_fs_t *, const char *, int, uv_fs_cb)\00", align 1
@__PRETTY_FUNCTION__.uv_fs_readlink = private unnamed_addr constant [67 x i8] c"int uv_fs_readlink(uv_loop_t *, uv_fs_t *, const char *, uv_fs_cb)\00", align 1
@__PRETTY_FUNCTION__.uv_fs_realpath = private unnamed_addr constant [67 x i8] c"int uv_fs_realpath(uv_loop_t *, uv_fs_t *, const char *, uv_fs_cb)\00", align 1
@__PRETTY_FUNCTION__.uv_fs_rename = private unnamed_addr constant [79 x i8] c"int uv_fs_rename(uv_loop_t *, uv_fs_t *, const char *, const char *, uv_fs_cb)\00", align 1
@__PRETTY_FUNCTION__.uv_fs_rmdir = private unnamed_addr constant [64 x i8] c"int uv_fs_rmdir(uv_loop_t *, uv_fs_t *, const char *, uv_fs_cb)\00", align 1
@__PRETTY_FUNCTION__.uv_fs_stat = private unnamed_addr constant [63 x i8] c"int uv_fs_stat(uv_loop_t *, uv_fs_t *, const char *, uv_fs_cb)\00", align 1
@__PRETTY_FUNCTION__.uv_fs_symlink = private unnamed_addr constant [85 x i8] c"int uv_fs_symlink(uv_loop_t *, uv_fs_t *, const char *, const char *, int, uv_fs_cb)\00", align 1
@__PRETTY_FUNCTION__.uv_fs_unlink = private unnamed_addr constant [65 x i8] c"int uv_fs_unlink(uv_loop_t *, uv_fs_t *, const char *, uv_fs_cb)\00", align 1
@__PRETTY_FUNCTION__.uv_fs_utime = private unnamed_addr constant [80 x i8] c"int uv_fs_utime(uv_loop_t *, uv_fs_t *, const char *, double, double, uv_fs_cb)\00", align 1
@__PRETTY_FUNCTION__.uv_fs_write = private unnamed_addr constant [100 x i8] c"int uv_fs_write(uv_loop_t *, uv_fs_t *, uv_file, const uv_buf_t *, unsigned int, int64_t, uv_fs_cb)\00", align 1
@uv__fs_futime.no_utimesat = internal global i32 0, align 4
@.str.3 = private unnamed_addr constant [17 x i8] c"/proc/self/fd/%d\00", align 1
@uv__fs_open.no_cloexec_support = internal global i32 0, align 4
@uv__fs_read.no_preadv = internal global i32 0, align 4
@.str.4 = private unnamed_addr constant [2 x i8] c".\00", align 1
@.str.5 = private unnamed_addr constant [3 x i8] c"..\00", align 1
@uv__fs_write.no_pwritev = internal global i32 0, align 4
@.str.6 = private unnamed_addr constant [123 x i8] c"(((const QUEUE *) (&(req->loop)->active_reqs) == (const QUEUE *) (*(QUEUE **) &((*(&(req->loop)->active_reqs))[0]))) == 0)\00", align 1
@__PRETTY_FUNCTION__.uv__fs_done = private unnamed_addr constant [41 x i8] c"void uv__fs_done(struct uv__work *, int)\00", align 1
@.str.7 = private unnamed_addr constant [17 x i8] c"req->result == 0\00", align 1

; Function Attrs: nounwind uwtable
define i32 @uv_fs_access(%struct.uv_loop_s* %loop, %struct.uv_fs_s* %req, i8* %path, i32 %flags, void (%struct.uv_fs_s*)* %cb) #0 !dbg !415 {
entry:
  %retval = alloca i32, align 4
  %loop.addr = alloca %struct.uv_loop_s*, align 8
  %req.addr = alloca %struct.uv_fs_s*, align 8
  %path.addr = alloca i8*, align 8
  %flags.addr = alloca i32, align 4
  %cb.addr = alloca void (%struct.uv_fs_s*)*, align 8
  store %struct.uv_loop_s* %loop, %struct.uv_loop_s** %loop.addr, align 8
  call void @llvm.dbg.declare(metadata %struct.uv_loop_s** %loop.addr, metadata !579, metadata !580), !dbg !581
  store %struct.uv_fs_s* %req, %struct.uv_fs_s** %req.addr, align 8
  call void @llvm.dbg.declare(metadata %struct.uv_fs_s** %req.addr, metadata !582, metadata !580), !dbg !583
  store i8* %path, i8** %path.addr, align 8
  call void @llvm.dbg.declare(metadata i8** %path.addr, metadata !584, metadata !580), !dbg !585
  store i32 %flags, i32* %flags.addr, align 4
  call void @llvm.dbg.declare(metadata i32* %flags.addr, metadata !586, metadata !580), !dbg !587
  store void (%struct.uv_fs_s*)* %cb, void (%struct.uv_fs_s*)** %cb.addr, align 8
  call void @llvm.dbg.declare(metadata void (%struct.uv_fs_s*)** %cb.addr, metadata !588, metadata !580), !dbg !589
  br label %do.body, !dbg !590

do.body:                                          ; preds = %entry
  %0 = load %struct.uv_fs_s*, %struct.uv_fs_s** %req.addr, align 8, !dbg !591
  %type = getelementptr inbounds %struct.uv_fs_s, %struct.uv_fs_s* %0, i32 0, i32 1, !dbg !591
  store i32 6, i32* %type, align 8, !dbg !591
  %1 = load void (%struct.uv_fs_s*)*, void (%struct.uv_fs_s*)** %cb.addr, align 8, !dbg !591
  %cmp = icmp ne void (%struct.uv_fs_s*)* %1, null, !dbg !591
  br i1 %cmp, label %if.then, label %if.end, !dbg !591

if.then:                                          ; preds = %do.body
  br label %do.body1, !dbg !594

do.body1:                                         ; preds = %if.then
  br label %do.body2, !dbg !597

do.body2:                                         ; preds = %do.body1
  %2 = load %struct.uv_fs_s*, %struct.uv_fs_s** %req.addr, align 8, !dbg !600
  %type3 = getelementptr inbounds %struct.uv_fs_s, %struct.uv_fs_s* %2, i32 0, i32 1, !dbg !600
  store i32 6, i32* %type3, align 8, !dbg !600
  br label %do.end, !dbg !600

do.end:                                           ; preds = %do.body2
  br label %do.body4, !dbg !603

do.body4:                                         ; preds = %do.end
  br label %do.body5, !dbg !605

do.body5:                                         ; preds = %do.body4
  %3 = load %struct.uv_loop_s*, %struct.uv_loop_s** %loop.addr, align 8, !dbg !608
  %active_reqs = getelementptr inbounds %struct.uv_loop_s, %struct.uv_loop_s* %3, i32 0, i32 3, !dbg !608
  %4 = load %struct.uv_fs_s*, %struct.uv_fs_s** %req.addr, align 8, !dbg !608
  %active_queue = getelementptr inbounds %struct.uv_fs_s, %struct.uv_fs_s* %4, i32 0, i32 2, !dbg !608
  %arrayidx = getelementptr inbounds [2 x i8*], [2 x i8*]* %active_queue, i64 0, i64 0, !dbg !608
  %5 = bitcast i8** %arrayidx to [2 x i8*]**, !dbg !608
  store [2 x i8*]* %active_reqs, [2 x i8*]** %5, align 8, !dbg !608
  %6 = load %struct.uv_loop_s*, %struct.uv_loop_s** %loop.addr, align 8, !dbg !608
  %active_reqs6 = getelementptr inbounds %struct.uv_loop_s, %struct.uv_loop_s* %6, i32 0, i32 3, !dbg !608
  %arrayidx7 = getelementptr inbounds [2 x i8*], [2 x i8*]* %active_reqs6, i64 0, i64 1, !dbg !608
  %7 = bitcast i8** %arrayidx7 to [2 x i8*]**, !dbg !608
  %8 = load [2 x i8*]*, [2 x i8*]** %7, align 8, !dbg !608
  %9 = load %struct.uv_fs_s*, %struct.uv_fs_s** %req.addr, align 8, !dbg !608
  %active_queue8 = getelementptr inbounds %struct.uv_fs_s, %struct.uv_fs_s* %9, i32 0, i32 2, !dbg !608
  %arrayidx9 = getelementptr inbounds [2 x i8*], [2 x i8*]* %active_queue8, i64 0, i64 1, !dbg !608
  %10 = bitcast i8** %arrayidx9 to [2 x i8*]**, !dbg !608
  store [2 x i8*]* %8, [2 x i8*]** %10, align 8, !dbg !608
  %11 = load %struct.uv_fs_s*, %struct.uv_fs_s** %req.addr, align 8, !dbg !608
  %active_queue10 = getelementptr inbounds %struct.uv_fs_s, %struct.uv_fs_s* %11, i32 0, i32 2, !dbg !608
  %12 = load %struct.uv_fs_s*, %struct.uv_fs_s** %req.addr, align 8, !dbg !608
  %active_queue11 = getelementptr inbounds %struct.uv_fs_s, %struct.uv_fs_s* %12, i32 0, i32 2, !dbg !608
  %arrayidx12 = getelementptr inbounds [2 x i8*], [2 x i8*]* %active_queue11, i64 0, i64 1, !dbg !608
  %13 = bitcast i8** %arrayidx12 to [2 x i8*]**, !dbg !608
  %14 = load [2 x i8*]*, [2 x i8*]** %13, align 8, !dbg !608
  %arrayidx13 = getelementptr inbounds [2 x i8*], [2 x i8*]* %14, i64 0, i64 0, !dbg !608
  %15 = bitcast i8** %arrayidx13 to [2 x i8*]**, !dbg !608
  store [2 x i8*]* %active_queue10, [2 x i8*]** %15, align 8, !dbg !608
  %16 = load %struct.uv_fs_s*, %struct.uv_fs_s** %req.addr, align 8, !dbg !608
  %active_queue14 = getelementptr inbounds %struct.uv_fs_s, %struct.uv_fs_s* %16, i32 0, i32 2, !dbg !608
  %17 = load %struct.uv_loop_s*, %struct.uv_loop_s** %loop.addr, align 8, !dbg !608
  %active_reqs15 = getelementptr inbounds %struct.uv_loop_s, %struct.uv_loop_s* %17, i32 0, i32 3, !dbg !608
  %arrayidx16 = getelementptr inbounds [2 x i8*], [2 x i8*]* %active_reqs15, i64 0, i64 1, !dbg !608
  %18 = bitcast i8** %arrayidx16 to [2 x i8*]**, !dbg !608
  store [2 x i8*]* %active_queue14, [2 x i8*]** %18, align 8, !dbg !608
  br label %do.end17, !dbg !608

do.end17:                                         ; preds = %do.body5
  br label %do.end18, !dbg !611

do.end18:                                         ; preds = %do.end17
  br label %do.end19, !dbg !613

do.end19:                                         ; preds = %do.end18
  br label %if.end, !dbg !615

if.end:                                           ; preds = %do.end19, %do.body
  %19 = load %struct.uv_fs_s*, %struct.uv_fs_s** %req.addr, align 8, !dbg !617
  %fs_type = getelementptr inbounds %struct.uv_fs_s, %struct.uv_fs_s* %19, i32 0, i32 4, !dbg !617
  store i32 12, i32* %fs_type, align 8, !dbg !617
  %20 = load %struct.uv_fs_s*, %struct.uv_fs_s** %req.addr, align 8, !dbg !617
  %result = getelementptr inbounds %struct.uv_fs_s, %struct.uv_fs_s* %20, i32 0, i32 7, !dbg !617
  store i64 0, i64* %result, align 8, !dbg !617
  %21 = load %struct.uv_fs_s*, %struct.uv_fs_s** %req.addr, align 8, !dbg !617
  %ptr = getelementptr inbounds %struct.uv_fs_s, %struct.uv_fs_s* %21, i32 0, i32 8, !dbg !617
  store i8* null, i8** %ptr, align 8, !dbg !617
  %22 = load %struct.uv_loop_s*, %struct.uv_loop_s** %loop.addr, align 8, !dbg !617
  %23 = load %struct.uv_fs_s*, %struct.uv_fs_s** %req.addr, align 8, !dbg !617
  %loop20 = getelementptr inbounds %struct.uv_fs_s, %struct.uv_fs_s* %23, i32 0, i32 5, !dbg !617
  store %struct.uv_loop_s* %22, %struct.uv_loop_s** %loop20, align 8, !dbg !617
  %24 = load %struct.uv_fs_s*, %struct.uv_fs_s** %req.addr, align 8, !dbg !617
  %path21 = getelementptr inbounds %struct.uv_fs_s, %struct.uv_fs_s* %24, i32 0, i32 9, !dbg !617
  store i8* null, i8** %path21, align 8, !dbg !617
  %25 = load %struct.uv_fs_s*, %struct.uv_fs_s** %req.addr, align 8, !dbg !617
  %new_path = getelementptr inbounds %struct.uv_fs_s, %struct.uv_fs_s* %25, i32 0, i32 11, !dbg !617
  store i8* null, i8** %new_path, align 8, !dbg !617
  %26 = load void (%struct.uv_fs_s*)*, void (%struct.uv_fs_s*)** %cb.addr, align 8, !dbg !617
  %27 = load %struct.uv_fs_s*, %struct.uv_fs_s** %req.addr, align 8, !dbg !617
  %cb22 = getelementptr inbounds %struct.uv_fs_s, %struct.uv_fs_s* %27, i32 0, i32 6, !dbg !617
  store void (%struct.uv_fs_s*)* %26, void (%struct.uv_fs_s*)** %cb22, align 8, !dbg !617
  br label %do.end23, !dbg !617

do.end23:                                         ; preds = %if.end
  br label %do.body24, !dbg !619

do.body24:                                        ; preds = %do.end23
  %28 = load i8*, i8** %path.addr, align 8, !dbg !620
  %cmp25 = icmp ne i8* %28, null, !dbg !620
  br i1 %cmp25, label %cond.true, label %cond.false, !dbg !620

cond.true:                                        ; preds = %do.body24
  br label %cond.end, !dbg !623

cond.false:                                       ; preds = %do.body24
  call void @__assert_fail(i8* getelementptr inbounds ([19 x i8], [19 x i8]* @.str, i32 0, i32 0), i8* getelementptr inbounds ([66 x i8], [66 x i8]* @.str.1, i32 0, i32 0), i32 1022, i8* getelementptr inbounds ([70 x i8], [70 x i8]* @__PRETTY_FUNCTION__.uv_fs_access, i32 0, i32 0)) #8, !dbg !625
  unreachable, !dbg !625
                                                  ; No predecessors!
  br label %cond.end, !dbg !627

cond.end:                                         ; preds = %29, %cond.true
  %30 = load void (%struct.uv_fs_s*)*, void (%struct.uv_fs_s*)** %cb.addr, align 8, !dbg !629
  %cmp26 = icmp eq void (%struct.uv_fs_s*)* %30, null, !dbg !629
  br i1 %cmp26, label %if.then27, label %if.else, !dbg !629

if.then27:                                        ; preds = %cond.end
  %31 = load i8*, i8** %path.addr, align 8, !dbg !632
  %32 = load %struct.uv_fs_s*, %struct.uv_fs_s** %req.addr, align 8, !dbg !632
  %path28 = getelementptr inbounds %struct.uv_fs_s, %struct.uv_fs_s* %32, i32 0, i32 9, !dbg !632
  store i8* %31, i8** %path28, align 8, !dbg !632
  br label %if.end57, !dbg !632

if.else:                                          ; preds = %cond.end
  %33 = load i8*, i8** %path.addr, align 8, !dbg !635
  %call = call i8* @uv__strdup(i8* %33), !dbg !635
  %34 = load %struct.uv_fs_s*, %struct.uv_fs_s** %req.addr, align 8, !dbg !635
  %path29 = getelementptr inbounds %struct.uv_fs_s, %struct.uv_fs_s* %34, i32 0, i32 9, !dbg !635
  store i8* %call, i8** %path29, align 8, !dbg !635
  %35 = load %struct.uv_fs_s*, %struct.uv_fs_s** %req.addr, align 8, !dbg !635
  %path30 = getelementptr inbounds %struct.uv_fs_s, %struct.uv_fs_s* %35, i32 0, i32 9, !dbg !635
  %36 = load i8*, i8** %path30, align 8, !dbg !635
  %cmp31 = icmp eq i8* %36, null, !dbg !635
  br i1 %cmp31, label %if.then32, label %if.end56, !dbg !635

if.then32:                                        ; preds = %if.else
  br label %do.body33, !dbg !638

do.body33:                                        ; preds = %if.then32
  %37 = load %struct.uv_loop_s*, %struct.uv_loop_s** %loop.addr, align 8, !dbg !642
  %active_reqs34 = getelementptr inbounds %struct.uv_loop_s, %struct.uv_loop_s* %37, i32 0, i32 3, !dbg !642
  %38 = load %struct.uv_loop_s*, %struct.uv_loop_s** %loop.addr, align 8, !dbg !642
  %active_reqs35 = getelementptr inbounds %struct.uv_loop_s, %struct.uv_loop_s* %38, i32 0, i32 3, !dbg !642
  %arrayidx36 = getelementptr inbounds [2 x i8*], [2 x i8*]* %active_reqs35, i64 0, i64 0, !dbg !642
  %39 = bitcast i8** %arrayidx36 to [2 x i8*]**, !dbg !642
  %40 = load [2 x i8*]*, [2 x i8*]** %39, align 8, !dbg !642
  %cmp37 = icmp eq [2 x i8*]* %active_reqs34, %40, !dbg !642
  %conv = zext i1 %cmp37 to i32, !dbg !642
  %cmp38 = icmp eq i32 %conv, 0, !dbg !642
  br i1 %cmp38, label %cond.true40, label %cond.false41, !dbg !642

cond.true40:                                      ; preds = %do.body33
  br label %cond.end42, !dbg !645

cond.false41:                                     ; preds = %do.body33
  call void @__assert_fail(i8* getelementptr inbounds ([113 x i8], [113 x i8]* @.str.2, i32 0, i32 0), i8* getelementptr inbounds ([66 x i8], [66 x i8]* @.str.1, i32 0, i32 0), i32 1022, i8* getelementptr inbounds ([70 x i8], [70 x i8]* @__PRETTY_FUNCTION__.uv_fs_access, i32 0, i32 0)) #8, !dbg !647
  unreachable, !dbg !647
                                                  ; No predecessors!
  br label %cond.end42, !dbg !649

cond.end42:                                       ; preds = %41, %cond.true40
  br label %do.body43, !dbg !651

do.body43:                                        ; preds = %cond.end42
  %42 = load %struct.uv_fs_s*, %struct.uv_fs_s** %req.addr, align 8, !dbg !653
  %active_queue44 = getelementptr inbounds %struct.uv_fs_s, %struct.uv_fs_s* %42, i32 0, i32 2, !dbg !653
  %arrayidx45 = getelementptr inbounds [2 x i8*], [2 x i8*]* %active_queue44, i64 0, i64 0, !dbg !653
  %43 = bitcast i8** %arrayidx45 to [2 x i8*]**, !dbg !653
  %44 = load [2 x i8*]*, [2 x i8*]** %43, align 8, !dbg !653
  %45 = load %struct.uv_fs_s*, %struct.uv_fs_s** %req.addr, align 8, !dbg !653
  %active_queue46 = getelementptr inbounds %struct.uv_fs_s, %struct.uv_fs_s* %45, i32 0, i32 2, !dbg !653
  %arrayidx47 = getelementptr inbounds [2 x i8*], [2 x i8*]* %active_queue46, i64 0, i64 1, !dbg !653
  %46 = bitcast i8** %arrayidx47 to [2 x i8*]**, !dbg !653
  %47 = load [2 x i8*]*, [2 x i8*]** %46, align 8, !dbg !653
  %arrayidx48 = getelementptr inbounds [2 x i8*], [2 x i8*]* %47, i64 0, i64 0, !dbg !653
  %48 = bitcast i8** %arrayidx48 to [2 x i8*]**, !dbg !653
  store [2 x i8*]* %44, [2 x i8*]** %48, align 8, !dbg !653
  %49 = load %struct.uv_fs_s*, %struct.uv_fs_s** %req.addr, align 8, !dbg !653
  %active_queue49 = getelementptr inbounds %struct.uv_fs_s, %struct.uv_fs_s* %49, i32 0, i32 2, !dbg !653
  %arrayidx50 = getelementptr inbounds [2 x i8*], [2 x i8*]* %active_queue49, i64 0, i64 1, !dbg !653
  %50 = bitcast i8** %arrayidx50 to [2 x i8*]**, !dbg !653
  %51 = load [2 x i8*]*, [2 x i8*]** %50, align 8, !dbg !653
  %52 = load %struct.uv_fs_s*, %struct.uv_fs_s** %req.addr, align 8, !dbg !653
  %active_queue51 = getelementptr inbounds %struct.uv_fs_s, %struct.uv_fs_s* %52, i32 0, i32 2, !dbg !653
  %arrayidx52 = getelementptr inbounds [2 x i8*], [2 x i8*]* %active_queue51, i64 0, i64 0, !dbg !653
  %53 = bitcast i8** %arrayidx52 to [2 x i8*]**, !dbg !653
  %54 = load [2 x i8*]*, [2 x i8*]** %53, align 8, !dbg !653
  %arrayidx53 = getelementptr inbounds [2 x i8*], [2 x i8*]* %54, i64 0, i64 1, !dbg !653
  %55 = bitcast i8** %arrayidx53 to [2 x i8*]**, !dbg !653
  store [2 x i8*]* %51, [2 x i8*]** %55, align 8, !dbg !653
  br label %do.end54, !dbg !653

do.end54:                                         ; preds = %do.body43
  br label %do.end55, !dbg !656

do.end55:                                         ; preds = %do.end54
  store i32 -12, i32* %retval, align 4, !dbg !658
  br label %do.end68, !dbg !658

if.end56:                                         ; preds = %if.else
  br label %if.end57

if.end57:                                         ; preds = %if.end56, %if.then27
  br label %do.end58, !dbg !660

do.end58:                                         ; preds = %if.end57
  %56 = load i32, i32* %flags.addr, align 4, !dbg !662
  %57 = load %struct.uv_fs_s*, %struct.uv_fs_s** %req.addr, align 8, !dbg !663
  %flags59 = getelementptr inbounds %struct.uv_fs_s, %struct.uv_fs_s* %57, i32 0, i32 13, !dbg !664
  store i32 %56, i32* %flags59, align 4, !dbg !665
  br label %do.body60, !dbg !666

do.body60:                                        ; preds = %do.end58
  %58 = load void (%struct.uv_fs_s*)*, void (%struct.uv_fs_s*)** %cb.addr, align 8, !dbg !667
  %cmp61 = icmp ne void (%struct.uv_fs_s*)* %58, null, !dbg !667
  br i1 %cmp61, label %if.then63, label %if.else64, !dbg !667

if.then63:                                        ; preds = %do.body60
  %59 = load %struct.uv_loop_s*, %struct.uv_loop_s** %loop.addr, align 8, !dbg !671
  %60 = load %struct.uv_fs_s*, %struct.uv_fs_s** %req.addr, align 8, !dbg !671
  %work_req = getelementptr inbounds %struct.uv_fs_s, %struct.uv_fs_s* %60, i32 0, i32 22, !dbg !671
  call void @uv__work_submit(%struct.uv_loop_s* %59, %struct.uv__work* %work_req, void (%struct.uv__work*)* @uv__fs_work, void (%struct.uv__work*, i32)* @uv__fs_done), !dbg !671
  store i32 0, i32* %retval, align 4, !dbg !671
  br label %do.end68, !dbg !671

if.else64:                                        ; preds = %do.body60
  %61 = load %struct.uv_fs_s*, %struct.uv_fs_s** %req.addr, align 8, !dbg !674
  %work_req65 = getelementptr inbounds %struct.uv_fs_s, %struct.uv_fs_s* %61, i32 0, i32 22, !dbg !674
  call void @uv__fs_work(%struct.uv__work* %work_req65), !dbg !674
  %62 = load %struct.uv_fs_s*, %struct.uv_fs_s** %req.addr, align 8, !dbg !674
  %result66 = getelementptr inbounds %struct.uv_fs_s, %struct.uv_fs_s* %62, i32 0, i32 7, !dbg !674
  %63 = load i64, i64* %result66, align 8, !dbg !674
  %conv67 = trunc i64 %63 to i32, !dbg !674
  store i32 %conv67, i32* %retval, align 4, !dbg !674
  br label %do.end68, !dbg !674

do.end68:                                         ; preds = %do.end55, %if.then63, %if.else64
  %64 = load i32, i32* %retval, align 4, !dbg !677
  ret i32 %64, !dbg !677
}

; Function Attrs: nounwind readnone
declare void @llvm.dbg.declare(metadata, metadata, metadata) #1

; Function Attrs: noreturn nounwind
declare void @__assert_fail(i8*, i8*, i32, i8*) #2

declare i8* @uv__strdup(i8*) #3

declare void @uv__work_submit(%struct.uv_loop_s*, %struct.uv__work*, void (%struct.uv__work*)*, void (%struct.uv__work*, i32)*) #3

; Function Attrs: nounwind uwtable
define internal void @uv__fs_work(%struct.uv__work* %w) #0 !dbg !476 {
entry:
  %w.addr = alloca %struct.uv__work*, align 8
  %retry_on_eintr = alloca i32, align 4
  %req = alloca %struct.uv_fs_s*, align 8
  %r = alloca i64, align 8
  store %struct.uv__work* %w, %struct.uv__work** %w.addr, align 8
  call void @llvm.dbg.declare(metadata %struct.uv__work** %w.addr, metadata !678, metadata !580), !dbg !679
  call void @llvm.dbg.declare(metadata i32* %retry_on_eintr, metadata !680, metadata !580), !dbg !681
  call void @llvm.dbg.declare(metadata %struct.uv_fs_s** %req, metadata !682, metadata !580), !dbg !683
  call void @llvm.dbg.declare(metadata i64* %r, metadata !684, metadata !580), !dbg !685
  %0 = load %struct.uv__work*, %struct.uv__work** %w.addr, align 8, !dbg !686
  %1 = bitcast %struct.uv__work* %0 to i8*, !dbg !686
  %add.ptr = getelementptr inbounds i8, i8* %1, i64 -336, !dbg !686
  %2 = bitcast i8* %add.ptr to %struct.uv_fs_s*, !dbg !686
  store %struct.uv_fs_s* %2, %struct.uv_fs_s** %req, align 8, !dbg !687
  %3 = load %struct.uv_fs_s*, %struct.uv_fs_s** %req, align 8, !dbg !688
  %fs_type = getelementptr inbounds %struct.uv_fs_s, %struct.uv_fs_s* %3, i32 0, i32 4, !dbg !689
  %4 = load i32, i32* %fs_type, align 8, !dbg !689
  %cmp = icmp eq i32 %4, 2, !dbg !690
  %lnot = xor i1 %cmp, true, !dbg !691
  %lnot.ext = zext i1 %lnot to i32, !dbg !691
  store i32 %lnot.ext, i32* %retry_on_eintr, align 4, !dbg !692
  br label %do.body, !dbg !693

do.body:                                          ; preds = %land.end, %entry
  %call = call i32* @__errno_location() #1, !dbg !694
  store i32 0, i32* %call, align 4, !dbg !696
  %5 = load %struct.uv_fs_s*, %struct.uv_fs_s** %req, align 8, !dbg !697
  %fs_type1 = getelementptr inbounds %struct.uv_fs_s, %struct.uv_fs_s* %5, i32 0, i32 4, !dbg !698
  %6 = load i32, i32* %fs_type1, align 8, !dbg !698
  switch i32 %6, label %sw.default [
    i32 12, label %sw.bb
    i32 13, label %sw.bb3
    i32 26, label %sw.bb7
    i32 2, label %sw.bb11
    i32 14, label %sw.bb14
    i32 27, label %sw.bb19
    i32 16, label %sw.bb25
    i32 8, label %sw.bb27
    i32 15, label %sw.bb31
    i32 9, label %sw.bb33
    i32 11, label %sw.bb37
    i32 7, label %sw.bb39
    i32 23, label %sw.bb44
    i32 19, label %sw.bb48
    i32 20, label %sw.bb53
    i32 1, label %sw.bb55
    i32 3, label %sw.bb57
    i32 22, label %sw.bb59
    i32 25, label %sw.bb61
    i32 28, label %sw.bb63
    i32 21, label %sw.bb65
    i32 18, label %sw.bb70
    i32 5, label %sw.bb74
    i32 6, label %sw.bb76
    i32 24, label %sw.bb81
    i32 17, label %sw.bb86
    i32 10, label %sw.bb90
    i32 4, label %sw.bb92
  ], !dbg !699

sw.bb:                                            ; preds = %do.body
  %7 = load %struct.uv_fs_s*, %struct.uv_fs_s** %req, align 8, !dbg !700
  %path = getelementptr inbounds %struct.uv_fs_s, %struct.uv_fs_s* %7, i32 0, i32 9, !dbg !700
  %8 = load i8*, i8** %path, align 8, !dbg !700
  %9 = load %struct.uv_fs_s*, %struct.uv_fs_s** %req, align 8, !dbg !700
  %flags = getelementptr inbounds %struct.uv_fs_s, %struct.uv_fs_s* %9, i32 0, i32 13, !dbg !700
  %10 = load i32, i32* %flags, align 4, !dbg !700
  %call2 = call i32 @access(i8* %8, i32 %10) #9, !dbg !700
  %conv = sext i32 %call2 to i64, !dbg !700
  store i64 %conv, i64* %r, align 8, !dbg !700
  br label %sw.epilog, !dbg !700

sw.bb3:                                           ; preds = %do.body
  %11 = load %struct.uv_fs_s*, %struct.uv_fs_s** %req, align 8, !dbg !702
  %path4 = getelementptr inbounds %struct.uv_fs_s, %struct.uv_fs_s* %11, i32 0, i32 9, !dbg !702
  %12 = load i8*, i8** %path4, align 8, !dbg !702
  %13 = load %struct.uv_fs_s*, %struct.uv_fs_s** %req, align 8, !dbg !702
  %mode = getelementptr inbounds %struct.uv_fs_s, %struct.uv_fs_s* %13, i32 0, i32 14, !dbg !702
  %14 = load i32, i32* %mode, align 8, !dbg !702
  %call5 = call i32 @chmod(i8* %12, i32 %14) #9, !dbg !702
  %conv6 = sext i32 %call5 to i64, !dbg !702
  store i64 %conv6, i64* %r, align 8, !dbg !702
  br label %sw.epilog, !dbg !702

sw.bb7:                                           ; preds = %do.body
  %15 = load %struct.uv_fs_s*, %struct.uv_fs_s** %req, align 8, !dbg !703
  %path8 = getelementptr inbounds %struct.uv_fs_s, %struct.uv_fs_s* %15, i32 0, i32 9, !dbg !703
  %16 = load i8*, i8** %path8, align 8, !dbg !703
  %17 = load %struct.uv_fs_s*, %struct.uv_fs_s** %req, align 8, !dbg !703
  %uid = getelementptr inbounds %struct.uv_fs_s, %struct.uv_fs_s* %17, i32 0, i32 18, !dbg !703
  %18 = load i32, i32* %uid, align 8, !dbg !703
  %19 = load %struct.uv_fs_s*, %struct.uv_fs_s** %req, align 8, !dbg !703
  %gid = getelementptr inbounds %struct.uv_fs_s, %struct.uv_fs_s* %19, i32 0, i32 19, !dbg !703
  %20 = load i32, i32* %gid, align 4, !dbg !703
  %call9 = call i32 @chown(i8* %16, i32 %18, i32 %20) #9, !dbg !703
  %conv10 = sext i32 %call9 to i64, !dbg !703
  store i64 %conv10, i64* %r, align 8, !dbg !703
  br label %sw.epilog, !dbg !703

sw.bb11:                                          ; preds = %do.body
  %21 = load %struct.uv_fs_s*, %struct.uv_fs_s** %req, align 8, !dbg !704
  %file = getelementptr inbounds %struct.uv_fs_s, %struct.uv_fs_s* %21, i32 0, i32 12, !dbg !704
  %22 = load i32, i32* %file, align 8, !dbg !704
  %call12 = call i32 @close(i32 %22), !dbg !704
  %conv13 = sext i32 %call12 to i64, !dbg !704
  store i64 %conv13, i64* %r, align 8, !dbg !704
  br label %sw.epilog, !dbg !704

sw.bb14:                                          ; preds = %do.body
  %23 = load %struct.uv_fs_s*, %struct.uv_fs_s** %req, align 8, !dbg !705
  %file15 = getelementptr inbounds %struct.uv_fs_s, %struct.uv_fs_s* %23, i32 0, i32 12, !dbg !705
  %24 = load i32, i32* %file15, align 8, !dbg !705
  %25 = load %struct.uv_fs_s*, %struct.uv_fs_s** %req, align 8, !dbg !705
  %mode16 = getelementptr inbounds %struct.uv_fs_s, %struct.uv_fs_s* %25, i32 0, i32 14, !dbg !705
  %26 = load i32, i32* %mode16, align 8, !dbg !705
  %call17 = call i32 @fchmod(i32 %24, i32 %26) #9, !dbg !705
  %conv18 = sext i32 %call17 to i64, !dbg !705
  store i64 %conv18, i64* %r, align 8, !dbg !705
  br label %sw.epilog, !dbg !705

sw.bb19:                                          ; preds = %do.body
  %27 = load %struct.uv_fs_s*, %struct.uv_fs_s** %req, align 8, !dbg !706
  %file20 = getelementptr inbounds %struct.uv_fs_s, %struct.uv_fs_s* %27, i32 0, i32 12, !dbg !706
  %28 = load i32, i32* %file20, align 8, !dbg !706
  %29 = load %struct.uv_fs_s*, %struct.uv_fs_s** %req, align 8, !dbg !706
  %uid21 = getelementptr inbounds %struct.uv_fs_s, %struct.uv_fs_s* %29, i32 0, i32 18, !dbg !706
  %30 = load i32, i32* %uid21, align 8, !dbg !706
  %31 = load %struct.uv_fs_s*, %struct.uv_fs_s** %req, align 8, !dbg !706
  %gid22 = getelementptr inbounds %struct.uv_fs_s, %struct.uv_fs_s* %31, i32 0, i32 19, !dbg !706
  %32 = load i32, i32* %gid22, align 4, !dbg !706
  %call23 = call i32 @fchown(i32 %28, i32 %30, i32 %32) #9, !dbg !706
  %conv24 = sext i32 %call23 to i64, !dbg !706
  store i64 %conv24, i64* %r, align 8, !dbg !706
  br label %sw.epilog, !dbg !706

sw.bb25:                                          ; preds = %do.body
  %33 = load %struct.uv_fs_s*, %struct.uv_fs_s** %req, align 8, !dbg !707
  %call26 = call i64 @uv__fs_fdatasync(%struct.uv_fs_s* %33), !dbg !707
  store i64 %call26, i64* %r, align 8, !dbg !707
  br label %sw.epilog, !dbg !707

sw.bb27:                                          ; preds = %do.body
  %34 = load %struct.uv_fs_s*, %struct.uv_fs_s** %req, align 8, !dbg !708
  %file28 = getelementptr inbounds %struct.uv_fs_s, %struct.uv_fs_s* %34, i32 0, i32 12, !dbg !708
  %35 = load i32, i32* %file28, align 8, !dbg !708
  %36 = load %struct.uv_fs_s*, %struct.uv_fs_s** %req, align 8, !dbg !708
  %statbuf = getelementptr inbounds %struct.uv_fs_s, %struct.uv_fs_s* %36, i32 0, i32 10, !dbg !708
  %call29 = call i32 @uv__fs_fstat(i32 %35, %struct.uv_stat_t* %statbuf), !dbg !708
  %conv30 = sext i32 %call29 to i64, !dbg !708
  store i64 %conv30, i64* %r, align 8, !dbg !708
  br label %sw.epilog, !dbg !708

sw.bb31:                                          ; preds = %do.body
  %37 = load %struct.uv_fs_s*, %struct.uv_fs_s** %req, align 8, !dbg !709
  %call32 = call i64 @uv__fs_fsync(%struct.uv_fs_s* %37), !dbg !709
  store i64 %call32, i64* %r, align 8, !dbg !709
  br label %sw.epilog, !dbg !709

sw.bb33:                                          ; preds = %do.body
  %38 = load %struct.uv_fs_s*, %struct.uv_fs_s** %req, align 8, !dbg !710
  %file34 = getelementptr inbounds %struct.uv_fs_s, %struct.uv_fs_s* %38, i32 0, i32 12, !dbg !710
  %39 = load i32, i32* %file34, align 8, !dbg !710
  %40 = load %struct.uv_fs_s*, %struct.uv_fs_s** %req, align 8, !dbg !710
  %off = getelementptr inbounds %struct.uv_fs_s, %struct.uv_fs_s* %40, i32 0, i32 17, !dbg !710
  %41 = load i64, i64* %off, align 8, !dbg !710
  %call35 = call i32 @ftruncate64(i32 %39, i64 %41) #9, !dbg !710
  %conv36 = sext i32 %call35 to i64, !dbg !710
  store i64 %conv36, i64* %r, align 8, !dbg !710
  br label %sw.epilog, !dbg !710

sw.bb37:                                          ; preds = %do.body
  %42 = load %struct.uv_fs_s*, %struct.uv_fs_s** %req, align 8, !dbg !711
  %call38 = call i64 @uv__fs_futime(%struct.uv_fs_s* %42), !dbg !711
  store i64 %call38, i64* %r, align 8, !dbg !711
  br label %sw.epilog, !dbg !711

sw.bb39:                                          ; preds = %do.body
  %43 = load %struct.uv_fs_s*, %struct.uv_fs_s** %req, align 8, !dbg !712
  %path40 = getelementptr inbounds %struct.uv_fs_s, %struct.uv_fs_s* %43, i32 0, i32 9, !dbg !712
  %44 = load i8*, i8** %path40, align 8, !dbg !712
  %45 = load %struct.uv_fs_s*, %struct.uv_fs_s** %req, align 8, !dbg !712
  %statbuf41 = getelementptr inbounds %struct.uv_fs_s, %struct.uv_fs_s* %45, i32 0, i32 10, !dbg !712
  %call42 = call i32 @uv__fs_lstat(i8* %44, %struct.uv_stat_t* %statbuf41), !dbg !712
  %conv43 = sext i32 %call42 to i64, !dbg !712
  store i64 %conv43, i64* %r, align 8, !dbg !712
  br label %sw.epilog, !dbg !712

sw.bb44:                                          ; preds = %do.body
  %46 = load %struct.uv_fs_s*, %struct.uv_fs_s** %req, align 8, !dbg !713
  %path45 = getelementptr inbounds %struct.uv_fs_s, %struct.uv_fs_s* %46, i32 0, i32 9, !dbg !713
  %47 = load i8*, i8** %path45, align 8, !dbg !713
  %48 = load %struct.uv_fs_s*, %struct.uv_fs_s** %req, align 8, !dbg !713
  %new_path = getelementptr inbounds %struct.uv_fs_s, %struct.uv_fs_s* %48, i32 0, i32 11, !dbg !713
  %49 = load i8*, i8** %new_path, align 8, !dbg !713
  %call46 = call i32 @link(i8* %47, i8* %49) #9, !dbg !713
  %conv47 = sext i32 %call46 to i64, !dbg !713
  store i64 %conv47, i64* %r, align 8, !dbg !713
  br label %sw.epilog, !dbg !713

sw.bb48:                                          ; preds = %do.body
  %50 = load %struct.uv_fs_s*, %struct.uv_fs_s** %req, align 8, !dbg !714
  %path49 = getelementptr inbounds %struct.uv_fs_s, %struct.uv_fs_s* %50, i32 0, i32 9, !dbg !714
  %51 = load i8*, i8** %path49, align 8, !dbg !714
  %52 = load %struct.uv_fs_s*, %struct.uv_fs_s** %req, align 8, !dbg !714
  %mode50 = getelementptr inbounds %struct.uv_fs_s, %struct.uv_fs_s* %52, i32 0, i32 14, !dbg !714
  %53 = load i32, i32* %mode50, align 8, !dbg !714
  %call51 = call i32 @mkdir(i8* %51, i32 %53) #9, !dbg !714
  %conv52 = sext i32 %call51 to i64, !dbg !714
  store i64 %conv52, i64* %r, align 8, !dbg !714
  br label %sw.epilog, !dbg !714

sw.bb53:                                          ; preds = %do.body
  %54 = load %struct.uv_fs_s*, %struct.uv_fs_s** %req, align 8, !dbg !715
  %call54 = call i64 @uv__fs_mkdtemp(%struct.uv_fs_s* %54), !dbg !715
  store i64 %call54, i64* %r, align 8, !dbg !715
  br label %sw.epilog, !dbg !715

sw.bb55:                                          ; preds = %do.body
  %55 = load %struct.uv_fs_s*, %struct.uv_fs_s** %req, align 8, !dbg !716
  %call56 = call i64 @uv__fs_open(%struct.uv_fs_s* %55), !dbg !716
  store i64 %call56, i64* %r, align 8, !dbg !716
  br label %sw.epilog, !dbg !716

sw.bb57:                                          ; preds = %do.body
  %56 = load %struct.uv_fs_s*, %struct.uv_fs_s** %req, align 8, !dbg !717
  %call58 = call i64 @uv__fs_buf_iter(%struct.uv_fs_s* %56, i64 (%struct.uv_fs_s*)* @uv__fs_read), !dbg !717
  store i64 %call58, i64* %r, align 8, !dbg !717
  br label %sw.epilog, !dbg !717

sw.bb59:                                          ; preds = %do.body
  %57 = load %struct.uv_fs_s*, %struct.uv_fs_s** %req, align 8, !dbg !718
  %call60 = call i64 @uv__fs_scandir(%struct.uv_fs_s* %57), !dbg !718
  store i64 %call60, i64* %r, align 8, !dbg !718
  br label %sw.epilog, !dbg !718

sw.bb61:                                          ; preds = %do.body
  %58 = load %struct.uv_fs_s*, %struct.uv_fs_s** %req, align 8, !dbg !719
  %call62 = call i64 @uv__fs_readlink(%struct.uv_fs_s* %58), !dbg !719
  store i64 %call62, i64* %r, align 8, !dbg !719
  br label %sw.epilog, !dbg !719

sw.bb63:                                          ; preds = %do.body
  %59 = load %struct.uv_fs_s*, %struct.uv_fs_s** %req, align 8, !dbg !720
  %call64 = call i64 @uv__fs_realpath(%struct.uv_fs_s* %59), !dbg !720
  store i64 %call64, i64* %r, align 8, !dbg !720
  br label %sw.epilog, !dbg !720

sw.bb65:                                          ; preds = %do.body
  %60 = load %struct.uv_fs_s*, %struct.uv_fs_s** %req, align 8, !dbg !721
  %path66 = getelementptr inbounds %struct.uv_fs_s, %struct.uv_fs_s* %60, i32 0, i32 9, !dbg !721
  %61 = load i8*, i8** %path66, align 8, !dbg !721
  %62 = load %struct.uv_fs_s*, %struct.uv_fs_s** %req, align 8, !dbg !721
  %new_path67 = getelementptr inbounds %struct.uv_fs_s, %struct.uv_fs_s* %62, i32 0, i32 11, !dbg !721
  %63 = load i8*, i8** %new_path67, align 8, !dbg !721
  %call68 = call i32 @rename(i8* %61, i8* %63) #9, !dbg !721
  %conv69 = sext i32 %call68 to i64, !dbg !721
  store i64 %conv69, i64* %r, align 8, !dbg !721
  br label %sw.epilog, !dbg !721

sw.bb70:                                          ; preds = %do.body
  %64 = load %struct.uv_fs_s*, %struct.uv_fs_s** %req, align 8, !dbg !722
  %path71 = getelementptr inbounds %struct.uv_fs_s, %struct.uv_fs_s* %64, i32 0, i32 9, !dbg !722
  %65 = load i8*, i8** %path71, align 8, !dbg !722
  %call72 = call i32 @rmdir(i8* %65) #9, !dbg !722
  %conv73 = sext i32 %call72 to i64, !dbg !722
  store i64 %conv73, i64* %r, align 8, !dbg !722
  br label %sw.epilog, !dbg !722

sw.bb74:                                          ; preds = %do.body
  %66 = load %struct.uv_fs_s*, %struct.uv_fs_s** %req, align 8, !dbg !723
  %call75 = call i64 @uv__fs_sendfile(%struct.uv_fs_s* %66), !dbg !723
  store i64 %call75, i64* %r, align 8, !dbg !723
  br label %sw.epilog, !dbg !723

sw.bb76:                                          ; preds = %do.body
  %67 = load %struct.uv_fs_s*, %struct.uv_fs_s** %req, align 8, !dbg !724
  %path77 = getelementptr inbounds %struct.uv_fs_s, %struct.uv_fs_s* %67, i32 0, i32 9, !dbg !724
  %68 = load i8*, i8** %path77, align 8, !dbg !724
  %69 = load %struct.uv_fs_s*, %struct.uv_fs_s** %req, align 8, !dbg !724
  %statbuf78 = getelementptr inbounds %struct.uv_fs_s, %struct.uv_fs_s* %69, i32 0, i32 10, !dbg !724
  %call79 = call i32 @uv__fs_stat(i8* %68, %struct.uv_stat_t* %statbuf78), !dbg !724
  %conv80 = sext i32 %call79 to i64, !dbg !724
  store i64 %conv80, i64* %r, align 8, !dbg !724
  br label %sw.epilog, !dbg !724

sw.bb81:                                          ; preds = %do.body
  %70 = load %struct.uv_fs_s*, %struct.uv_fs_s** %req, align 8, !dbg !725
  %path82 = getelementptr inbounds %struct.uv_fs_s, %struct.uv_fs_s* %70, i32 0, i32 9, !dbg !725
  %71 = load i8*, i8** %path82, align 8, !dbg !725
  %72 = load %struct.uv_fs_s*, %struct.uv_fs_s** %req, align 8, !dbg !725
  %new_path83 = getelementptr inbounds %struct.uv_fs_s, %struct.uv_fs_s* %72, i32 0, i32 11, !dbg !725
  %73 = load i8*, i8** %new_path83, align 8, !dbg !725
  %call84 = call i32 @symlink(i8* %71, i8* %73) #9, !dbg !725
  %conv85 = sext i32 %call84 to i64, !dbg !725
  store i64 %conv85, i64* %r, align 8, !dbg !725
  br label %sw.epilog, !dbg !725

sw.bb86:                                          ; preds = %do.body
  %74 = load %struct.uv_fs_s*, %struct.uv_fs_s** %req, align 8, !dbg !726
  %path87 = getelementptr inbounds %struct.uv_fs_s, %struct.uv_fs_s* %74, i32 0, i32 9, !dbg !726
  %75 = load i8*, i8** %path87, align 8, !dbg !726
  %call88 = call i32 @unlink(i8* %75) #9, !dbg !726
  %conv89 = sext i32 %call88 to i64, !dbg !726
  store i64 %conv89, i64* %r, align 8, !dbg !726
  br label %sw.epilog, !dbg !726

sw.bb90:                                          ; preds = %do.body
  %76 = load %struct.uv_fs_s*, %struct.uv_fs_s** %req, align 8, !dbg !727
  %call91 = call i64 @uv__fs_utime(%struct.uv_fs_s* %76), !dbg !727
  store i64 %call91, i64* %r, align 8, !dbg !727
  br label %sw.epilog, !dbg !727

sw.bb92:                                          ; preds = %do.body
  %77 = load %struct.uv_fs_s*, %struct.uv_fs_s** %req, align 8, !dbg !728
  %call93 = call i64 @uv__fs_buf_iter(%struct.uv_fs_s* %77, i64 (%struct.uv_fs_s*)* @uv__fs_write), !dbg !728
  store i64 %call93, i64* %r, align 8, !dbg !728
  br label %sw.epilog, !dbg !728

sw.default:                                       ; preds = %do.body
  call void @abort() #8, !dbg !729
  unreachable, !dbg !729

sw.epilog:                                        ; preds = %sw.bb92, %sw.bb90, %sw.bb86, %sw.bb81, %sw.bb76, %sw.bb74, %sw.bb70, %sw.bb65, %sw.bb63, %sw.bb61, %sw.bb59, %sw.bb57, %sw.bb55, %sw.bb53, %sw.bb48, %sw.bb44, %sw.bb39, %sw.bb37, %sw.bb33, %sw.bb31, %sw.bb27, %sw.bb25, %sw.bb19, %sw.bb14, %sw.bb11, %sw.bb7, %sw.bb3, %sw.bb
  br label %do.cond, !dbg !730

do.cond:                                          ; preds = %sw.epilog
  %78 = load i64, i64* %r, align 8, !dbg !731
  %cmp94 = icmp eq i64 %78, -1, !dbg !733
  br i1 %cmp94, label %land.lhs.true, label %land.end, !dbg !734

land.lhs.true:                                    ; preds = %do.cond
  %call96 = call i32* @__errno_location() #1, !dbg !735
  %79 = load i32, i32* %call96, align 4, !dbg !735
  %cmp97 = icmp eq i32 %79, 4, !dbg !737
  br i1 %cmp97, label %land.rhs, label %land.end, !dbg !738

land.rhs:                                         ; preds = %land.lhs.true
  %80 = load i32, i32* %retry_on_eintr, align 4, !dbg !739
  %tobool = icmp ne i32 %80, 0, !dbg !741
  br label %land.end

land.end:                                         ; preds = %land.rhs, %land.lhs.true, %do.cond
  %81 = phi i1 [ false, %land.lhs.true ], [ false, %do.cond ], [ %tobool, %land.rhs ]
  br i1 %81, label %do.body, label %do.end, !dbg !742

do.end:                                           ; preds = %land.end
  %82 = load i64, i64* %r, align 8, !dbg !744
  %cmp99 = icmp eq i64 %82, -1, !dbg !746
  br i1 %cmp99, label %if.then, label %if.else, !dbg !747

if.then:                                          ; preds = %do.end
  %call101 = call i32* @__errno_location() #1, !dbg !748
  %83 = load i32, i32* %call101, align 4, !dbg !748
  %sub = sub nsw i32 0, %83, !dbg !749
  %conv102 = sext i32 %sub to i64, !dbg !749
  %84 = load %struct.uv_fs_s*, %struct.uv_fs_s** %req, align 8, !dbg !750
  %result = getelementptr inbounds %struct.uv_fs_s, %struct.uv_fs_s* %84, i32 0, i32 7, !dbg !751
  store i64 %conv102, i64* %result, align 8, !dbg !752
  br label %if.end, !dbg !750

if.else:                                          ; preds = %do.end
  %85 = load i64, i64* %r, align 8, !dbg !753
  %86 = load %struct.uv_fs_s*, %struct.uv_fs_s** %req, align 8, !dbg !754
  %result103 = getelementptr inbounds %struct.uv_fs_s, %struct.uv_fs_s* %86, i32 0, i32 7, !dbg !755
  store i64 %85, i64* %result103, align 8, !dbg !756
  br label %if.end

if.end:                                           ; preds = %if.else, %if.then
  %87 = load i64, i64* %r, align 8, !dbg !757
  %cmp104 = icmp eq i64 %87, 0, !dbg !759
  br i1 %cmp104, label %land.lhs.true106, label %if.end119, !dbg !760

land.lhs.true106:                                 ; preds = %if.end
  %88 = load %struct.uv_fs_s*, %struct.uv_fs_s** %req, align 8, !dbg !761
  %fs_type107 = getelementptr inbounds %struct.uv_fs_s, %struct.uv_fs_s* %88, i32 0, i32 4, !dbg !763
  %89 = load i32, i32* %fs_type107, align 8, !dbg !763
  %cmp108 = icmp eq i32 %89, 6, !dbg !764
  br i1 %cmp108, label %if.then117, label %lor.lhs.false, !dbg !765

lor.lhs.false:                                    ; preds = %land.lhs.true106
  %90 = load %struct.uv_fs_s*, %struct.uv_fs_s** %req, align 8, !dbg !766
  %fs_type110 = getelementptr inbounds %struct.uv_fs_s, %struct.uv_fs_s* %90, i32 0, i32 4, !dbg !767
  %91 = load i32, i32* %fs_type110, align 8, !dbg !767
  %cmp111 = icmp eq i32 %91, 8, !dbg !768
  br i1 %cmp111, label %if.then117, label %lor.lhs.false113, !dbg !769

lor.lhs.false113:                                 ; preds = %lor.lhs.false
  %92 = load %struct.uv_fs_s*, %struct.uv_fs_s** %req, align 8, !dbg !770
  %fs_type114 = getelementptr inbounds %struct.uv_fs_s, %struct.uv_fs_s* %92, i32 0, i32 4, !dbg !771
  %93 = load i32, i32* %fs_type114, align 8, !dbg !771
  %cmp115 = icmp eq i32 %93, 7, !dbg !772
  br i1 %cmp115, label %if.then117, label %if.end119, !dbg !773

if.then117:                                       ; preds = %lor.lhs.false113, %lor.lhs.false, %land.lhs.true106
  %94 = load %struct.uv_fs_s*, %struct.uv_fs_s** %req, align 8, !dbg !774
  %statbuf118 = getelementptr inbounds %struct.uv_fs_s, %struct.uv_fs_s* %94, i32 0, i32 10, !dbg !776
  %95 = bitcast %struct.uv_stat_t* %statbuf118 to i8*, !dbg !777
  %96 = load %struct.uv_fs_s*, %struct.uv_fs_s** %req, align 8, !dbg !778
  %ptr = getelementptr inbounds %struct.uv_fs_s, %struct.uv_fs_s* %96, i32 0, i32 8, !dbg !779
  store i8* %95, i8** %ptr, align 8, !dbg !780
  br label %if.end119, !dbg !781

if.end119:                                        ; preds = %if.then117, %lor.lhs.false113, %if.end
  ret void, !dbg !782
}

; Function Attrs: nounwind uwtable
define internal void @uv__fs_done(%struct.uv__work* %w, i32 %status) #0 !dbg !570 {
entry:
  %w.addr = alloca %struct.uv__work*, align 8
  %status.addr = alloca i32, align 4
  %req = alloca %struct.uv_fs_s*, align 8
  store %struct.uv__work* %w, %struct.uv__work** %w.addr, align 8
  call void @llvm.dbg.declare(metadata %struct.uv__work** %w.addr, metadata !783, metadata !580), !dbg !784
  store i32 %status, i32* %status.addr, align 4
  call void @llvm.dbg.declare(metadata i32* %status.addr, metadata !785, metadata !580), !dbg !786
  call void @llvm.dbg.declare(metadata %struct.uv_fs_s** %req, metadata !787, metadata !580), !dbg !788
  %0 = load %struct.uv__work*, %struct.uv__work** %w.addr, align 8, !dbg !789
  %1 = bitcast %struct.uv__work* %0 to i8*, !dbg !789
  %add.ptr = getelementptr inbounds i8, i8* %1, i64 -336, !dbg !789
  %2 = bitcast i8* %add.ptr to %struct.uv_fs_s*, !dbg !789
  store %struct.uv_fs_s* %2, %struct.uv_fs_s** %req, align 8, !dbg !790
  br label %do.body, !dbg !791

do.body:                                          ; preds = %entry
  %3 = load %struct.uv_fs_s*, %struct.uv_fs_s** %req, align 8, !dbg !792
  %loop = getelementptr inbounds %struct.uv_fs_s, %struct.uv_fs_s* %3, i32 0, i32 5, !dbg !792
  %4 = load %struct.uv_loop_s*, %struct.uv_loop_s** %loop, align 8, !dbg !792
  %active_reqs = getelementptr inbounds %struct.uv_loop_s, %struct.uv_loop_s* %4, i32 0, i32 3, !dbg !792
  %5 = load %struct.uv_fs_s*, %struct.uv_fs_s** %req, align 8, !dbg !792
  %loop1 = getelementptr inbounds %struct.uv_fs_s, %struct.uv_fs_s* %5, i32 0, i32 5, !dbg !792
  %6 = load %struct.uv_loop_s*, %struct.uv_loop_s** %loop1, align 8, !dbg !792
  %active_reqs2 = getelementptr inbounds %struct.uv_loop_s, %struct.uv_loop_s* %6, i32 0, i32 3, !dbg !792
  %arrayidx = getelementptr inbounds [2 x i8*], [2 x i8*]* %active_reqs2, i64 0, i64 0, !dbg !792
  %7 = bitcast i8** %arrayidx to [2 x i8*]**, !dbg !792
  %8 = load [2 x i8*]*, [2 x i8*]** %7, align 8, !dbg !792
  %cmp = icmp eq [2 x i8*]* %active_reqs, %8, !dbg !792
  %conv = zext i1 %cmp to i32, !dbg !792
  %cmp3 = icmp eq i32 %conv, 0, !dbg !792
  br i1 %cmp3, label %cond.true, label %cond.false, !dbg !792

cond.true:                                        ; preds = %do.body
  br label %cond.end, !dbg !795

cond.false:                                       ; preds = %do.body
  call void @__assert_fail(i8* getelementptr inbounds ([123 x i8], [123 x i8]* @.str.6, i32 0, i32 0), i8* getelementptr inbounds ([66 x i8], [66 x i8]* @.str.1, i32 0, i32 0), i32 1005, i8* getelementptr inbounds ([41 x i8], [41 x i8]* @__PRETTY_FUNCTION__.uv__fs_done, i32 0, i32 0)) #8, !dbg !797
  unreachable, !dbg !797
                                                  ; No predecessors!
  br label %cond.end, !dbg !799

cond.end:                                         ; preds = %9, %cond.true
  br label %do.body5, !dbg !801

do.body5:                                         ; preds = %cond.end
  %10 = load %struct.uv_fs_s*, %struct.uv_fs_s** %req, align 8, !dbg !803
  %active_queue = getelementptr inbounds %struct.uv_fs_s, %struct.uv_fs_s* %10, i32 0, i32 2, !dbg !803
  %arrayidx6 = getelementptr inbounds [2 x i8*], [2 x i8*]* %active_queue, i64 0, i64 0, !dbg !803
  %11 = bitcast i8** %arrayidx6 to [2 x i8*]**, !dbg !803
  %12 = load [2 x i8*]*, [2 x i8*]** %11, align 8, !dbg !803
  %13 = load %struct.uv_fs_s*, %struct.uv_fs_s** %req, align 8, !dbg !803
  %active_queue7 = getelementptr inbounds %struct.uv_fs_s, %struct.uv_fs_s* %13, i32 0, i32 2, !dbg !803
  %arrayidx8 = getelementptr inbounds [2 x i8*], [2 x i8*]* %active_queue7, i64 0, i64 1, !dbg !803
  %14 = bitcast i8** %arrayidx8 to [2 x i8*]**, !dbg !803
  %15 = load [2 x i8*]*, [2 x i8*]** %14, align 8, !dbg !803
  %arrayidx9 = getelementptr inbounds [2 x i8*], [2 x i8*]* %15, i64 0, i64 0, !dbg !803
  %16 = bitcast i8** %arrayidx9 to [2 x i8*]**, !dbg !803
  store [2 x i8*]* %12, [2 x i8*]** %16, align 8, !dbg !803
  %17 = load %struct.uv_fs_s*, %struct.uv_fs_s** %req, align 8, !dbg !803
  %active_queue10 = getelementptr inbounds %struct.uv_fs_s, %struct.uv_fs_s* %17, i32 0, i32 2, !dbg !803
  %arrayidx11 = getelementptr inbounds [2 x i8*], [2 x i8*]* %active_queue10, i64 0, i64 1, !dbg !803
  %18 = bitcast i8** %arrayidx11 to [2 x i8*]**, !dbg !803
  %19 = load [2 x i8*]*, [2 x i8*]** %18, align 8, !dbg !803
  %20 = load %struct.uv_fs_s*, %struct.uv_fs_s** %req, align 8, !dbg !803
  %active_queue12 = getelementptr inbounds %struct.uv_fs_s, %struct.uv_fs_s* %20, i32 0, i32 2, !dbg !803
  %arrayidx13 = getelementptr inbounds [2 x i8*], [2 x i8*]* %active_queue12, i64 0, i64 0, !dbg !803
  %21 = bitcast i8** %arrayidx13 to [2 x i8*]**, !dbg !803
  %22 = load [2 x i8*]*, [2 x i8*]** %21, align 8, !dbg !803
  %arrayidx14 = getelementptr inbounds [2 x i8*], [2 x i8*]* %22, i64 0, i64 1, !dbg !803
  %23 = bitcast i8** %arrayidx14 to [2 x i8*]**, !dbg !803
  store [2 x i8*]* %19, [2 x i8*]** %23, align 8, !dbg !803
  br label %do.end, !dbg !803

do.end:                                           ; preds = %do.body5
  br label %do.end15, !dbg !806

do.end15:                                         ; preds = %do.end
  %24 = load i32, i32* %status.addr, align 4, !dbg !808
  %cmp16 = icmp eq i32 %24, -125, !dbg !810
  br i1 %cmp16, label %if.then, label %if.end, !dbg !811

if.then:                                          ; preds = %do.end15
  %25 = load %struct.uv_fs_s*, %struct.uv_fs_s** %req, align 8, !dbg !812
  %result = getelementptr inbounds %struct.uv_fs_s, %struct.uv_fs_s* %25, i32 0, i32 7, !dbg !812
  %26 = load i64, i64* %result, align 8, !dbg !812
  %cmp18 = icmp eq i64 %26, 0, !dbg !812
  br i1 %cmp18, label %cond.true20, label %cond.false21, !dbg !812

cond.true20:                                      ; preds = %if.then
  br label %cond.end22, !dbg !814

cond.false21:                                     ; preds = %if.then
  call void @__assert_fail(i8* getelementptr inbounds ([17 x i8], [17 x i8]* @.str.7, i32 0, i32 0), i8* getelementptr inbounds ([66 x i8], [66 x i8]* @.str.1, i32 0, i32 0), i32 1008, i8* getelementptr inbounds ([41 x i8], [41 x i8]* @__PRETTY_FUNCTION__.uv__fs_done, i32 0, i32 0)) #8, !dbg !816
  unreachable, !dbg !816
                                                  ; No predecessors!
  br label %cond.end22, !dbg !818

cond.end22:                                       ; preds = %27, %cond.true20
  %28 = load %struct.uv_fs_s*, %struct.uv_fs_s** %req, align 8, !dbg !820
  %result23 = getelementptr inbounds %struct.uv_fs_s, %struct.uv_fs_s* %28, i32 0, i32 7, !dbg !821
  store i64 -125, i64* %result23, align 8, !dbg !822
  br label %if.end, !dbg !823

if.end:                                           ; preds = %cond.end22, %do.end15
  %29 = load %struct.uv_fs_s*, %struct.uv_fs_s** %req, align 8, !dbg !824
  %cb = getelementptr inbounds %struct.uv_fs_s, %struct.uv_fs_s* %29, i32 0, i32 6, !dbg !825
  %30 = load void (%struct.uv_fs_s*)*, void (%struct.uv_fs_s*)** %cb, align 8, !dbg !825
  %31 = load %struct.uv_fs_s*, %struct.uv_fs_s** %req, align 8, !dbg !826
  call void %30(%struct.uv_fs_s* %31), !dbg !824
  ret void, !dbg !827
}

; Function Attrs: nounwind uwtable
define i32 @uv_fs_chmod(%struct.uv_loop_s* %loop, %struct.uv_fs_s* %req, i8* %path, i32 %mode, void (%struct.uv_fs_s*)* %cb) #0 !dbg !419 {
entry:
  %retval = alloca i32, align 4
  %loop.addr = alloca %struct.uv_loop_s*, align 8
  %req.addr = alloca %struct.uv_fs_s*, align 8
  %path.addr = alloca i8*, align 8
  %mode.addr = alloca i32, align 4
  %cb.addr = alloca void (%struct.uv_fs_s*)*, align 8
  store %struct.uv_loop_s* %loop, %struct.uv_loop_s** %loop.addr, align 8
  call void @llvm.dbg.declare(metadata %struct.uv_loop_s** %loop.addr, metadata !828, metadata !580), !dbg !829
  store %struct.uv_fs_s* %req, %struct.uv_fs_s** %req.addr, align 8
  call void @llvm.dbg.declare(metadata %struct.uv_fs_s** %req.addr, metadata !830, metadata !580), !dbg !831
  store i8* %path, i8** %path.addr, align 8
  call void @llvm.dbg.declare(metadata i8** %path.addr, metadata !832, metadata !580), !dbg !833
  store i32 %mode, i32* %mode.addr, align 4
  call void @llvm.dbg.declare(metadata i32* %mode.addr, metadata !834, metadata !580), !dbg !835
  store void (%struct.uv_fs_s*)* %cb, void (%struct.uv_fs_s*)** %cb.addr, align 8
  call void @llvm.dbg.declare(metadata void (%struct.uv_fs_s*)** %cb.addr, metadata !836, metadata !580), !dbg !837
  br label %do.body, !dbg !838

do.body:                                          ; preds = %entry
  %0 = load %struct.uv_fs_s*, %struct.uv_fs_s** %req.addr, align 8, !dbg !839
  %type = getelementptr inbounds %struct.uv_fs_s, %struct.uv_fs_s* %0, i32 0, i32 1, !dbg !839
  store i32 6, i32* %type, align 8, !dbg !839
  %1 = load void (%struct.uv_fs_s*)*, void (%struct.uv_fs_s*)** %cb.addr, align 8, !dbg !839
  %cmp = icmp ne void (%struct.uv_fs_s*)* %1, null, !dbg !839
  br i1 %cmp, label %if.then, label %if.end, !dbg !839

if.then:                                          ; preds = %do.body
  br label %do.body1, !dbg !842

do.body1:                                         ; preds = %if.then
  br label %do.body2, !dbg !845

do.body2:                                         ; preds = %do.body1
  %2 = load %struct.uv_fs_s*, %struct.uv_fs_s** %req.addr, align 8, !dbg !848
  %type3 = getelementptr inbounds %struct.uv_fs_s, %struct.uv_fs_s* %2, i32 0, i32 1, !dbg !848
  store i32 6, i32* %type3, align 8, !dbg !848
  br label %do.end, !dbg !848

do.end:                                           ; preds = %do.body2
  br label %do.body4, !dbg !851

do.body4:                                         ; preds = %do.end
  br label %do.body5, !dbg !853

do.body5:                                         ; preds = %do.body4
  %3 = load %struct.uv_loop_s*, %struct.uv_loop_s** %loop.addr, align 8, !dbg !856
  %active_reqs = getelementptr inbounds %struct.uv_loop_s, %struct.uv_loop_s* %3, i32 0, i32 3, !dbg !856
  %4 = load %struct.uv_fs_s*, %struct.uv_fs_s** %req.addr, align 8, !dbg !856
  %active_queue = getelementptr inbounds %struct.uv_fs_s, %struct.uv_fs_s* %4, i32 0, i32 2, !dbg !856
  %arrayidx = getelementptr inbounds [2 x i8*], [2 x i8*]* %active_queue, i64 0, i64 0, !dbg !856
  %5 = bitcast i8** %arrayidx to [2 x i8*]**, !dbg !856
  store [2 x i8*]* %active_reqs, [2 x i8*]** %5, align 8, !dbg !856
  %6 = load %struct.uv_loop_s*, %struct.uv_loop_s** %loop.addr, align 8, !dbg !856
  %active_reqs6 = getelementptr inbounds %struct.uv_loop_s, %struct.uv_loop_s* %6, i32 0, i32 3, !dbg !856
  %arrayidx7 = getelementptr inbounds [2 x i8*], [2 x i8*]* %active_reqs6, i64 0, i64 1, !dbg !856
  %7 = bitcast i8** %arrayidx7 to [2 x i8*]**, !dbg !856
  %8 = load [2 x i8*]*, [2 x i8*]** %7, align 8, !dbg !856
  %9 = load %struct.uv_fs_s*, %struct.uv_fs_s** %req.addr, align 8, !dbg !856
  %active_queue8 = getelementptr inbounds %struct.uv_fs_s, %struct.uv_fs_s* %9, i32 0, i32 2, !dbg !856
  %arrayidx9 = getelementptr inbounds [2 x i8*], [2 x i8*]* %active_queue8, i64 0, i64 1, !dbg !856
  %10 = bitcast i8** %arrayidx9 to [2 x i8*]**, !dbg !856
  store [2 x i8*]* %8, [2 x i8*]** %10, align 8, !dbg !856
  %11 = load %struct.uv_fs_s*, %struct.uv_fs_s** %req.addr, align 8, !dbg !856
  %active_queue10 = getelementptr inbounds %struct.uv_fs_s, %struct.uv_fs_s* %11, i32 0, i32 2, !dbg !856
  %12 = load %struct.uv_fs_s*, %struct.uv_fs_s** %req.addr, align 8, !dbg !856
  %active_queue11 = getelementptr inbounds %struct.uv_fs_s, %struct.uv_fs_s* %12, i32 0, i32 2, !dbg !856
  %arrayidx12 = getelementptr inbounds [2 x i8*], [2 x i8*]* %active_queue11, i64 0, i64 1, !dbg !856
  %13 = bitcast i8** %arrayidx12 to [2 x i8*]**, !dbg !856
  %14 = load [2 x i8*]*, [2 x i8*]** %13, align 8, !dbg !856
  %arrayidx13 = getelementptr inbounds [2 x i8*], [2 x i8*]* %14, i64 0, i64 0, !dbg !856
  %15 = bitcast i8** %arrayidx13 to [2 x i8*]**, !dbg !856
  store [2 x i8*]* %active_queue10, [2 x i8*]** %15, align 8, !dbg !856
  %16 = load %struct.uv_fs_s*, %struct.uv_fs_s** %req.addr, align 8, !dbg !856
  %active_queue14 = getelementptr inbounds %struct.uv_fs_s, %struct.uv_fs_s* %16, i32 0, i32 2, !dbg !856
  %17 = load %struct.uv_loop_s*, %struct.uv_loop_s** %loop.addr, align 8, !dbg !856
  %active_reqs15 = getelementptr inbounds %struct.uv_loop_s, %struct.uv_loop_s* %17, i32 0, i32 3, !dbg !856
  %arrayidx16 = getelementptr inbounds [2 x i8*], [2 x i8*]* %active_reqs15, i64 0, i64 1, !dbg !856
  %18 = bitcast i8** %arrayidx16 to [2 x i8*]**, !dbg !856
  store [2 x i8*]* %active_queue14, [2 x i8*]** %18, align 8, !dbg !856
  br label %do.end17, !dbg !856

do.end17:                                         ; preds = %do.body5
  br label %do.end18, !dbg !859

do.end18:                                         ; preds = %do.end17
  br label %do.end19, !dbg !861

do.end19:                                         ; preds = %do.end18
  br label %if.end, !dbg !863

if.end:                                           ; preds = %do.end19, %do.body
  %19 = load %struct.uv_fs_s*, %struct.uv_fs_s** %req.addr, align 8, !dbg !865
  %fs_type = getelementptr inbounds %struct.uv_fs_s, %struct.uv_fs_s* %19, i32 0, i32 4, !dbg !865
  store i32 13, i32* %fs_type, align 8, !dbg !865
  %20 = load %struct.uv_fs_s*, %struct.uv_fs_s** %req.addr, align 8, !dbg !865
  %result = getelementptr inbounds %struct.uv_fs_s, %struct.uv_fs_s* %20, i32 0, i32 7, !dbg !865
  store i64 0, i64* %result, align 8, !dbg !865
  %21 = load %struct.uv_fs_s*, %struct.uv_fs_s** %req.addr, align 8, !dbg !865
  %ptr = getelementptr inbounds %struct.uv_fs_s, %struct.uv_fs_s* %21, i32 0, i32 8, !dbg !865
  store i8* null, i8** %ptr, align 8, !dbg !865
  %22 = load %struct.uv_loop_s*, %struct.uv_loop_s** %loop.addr, align 8, !dbg !865
  %23 = load %struct.uv_fs_s*, %struct.uv_fs_s** %req.addr, align 8, !dbg !865
  %loop20 = getelementptr inbounds %struct.uv_fs_s, %struct.uv_fs_s* %23, i32 0, i32 5, !dbg !865
  store %struct.uv_loop_s* %22, %struct.uv_loop_s** %loop20, align 8, !dbg !865
  %24 = load %struct.uv_fs_s*, %struct.uv_fs_s** %req.addr, align 8, !dbg !865
  %path21 = getelementptr inbounds %struct.uv_fs_s, %struct.uv_fs_s* %24, i32 0, i32 9, !dbg !865
  store i8* null, i8** %path21, align 8, !dbg !865
  %25 = load %struct.uv_fs_s*, %struct.uv_fs_s** %req.addr, align 8, !dbg !865
  %new_path = getelementptr inbounds %struct.uv_fs_s, %struct.uv_fs_s* %25, i32 0, i32 11, !dbg !865
  store i8* null, i8** %new_path, align 8, !dbg !865
  %26 = load void (%struct.uv_fs_s*)*, void (%struct.uv_fs_s*)** %cb.addr, align 8, !dbg !865
  %27 = load %struct.uv_fs_s*, %struct.uv_fs_s** %req.addr, align 8, !dbg !865
  %cb22 = getelementptr inbounds %struct.uv_fs_s, %struct.uv_fs_s* %27, i32 0, i32 6, !dbg !865
  store void (%struct.uv_fs_s*)* %26, void (%struct.uv_fs_s*)** %cb22, align 8, !dbg !865
  br label %do.end23, !dbg !865

do.end23:                                         ; preds = %if.end
  br label %do.body24, !dbg !867

do.body24:                                        ; preds = %do.end23
  %28 = load i8*, i8** %path.addr, align 8, !dbg !868
  %cmp25 = icmp ne i8* %28, null, !dbg !868
  br i1 %cmp25, label %cond.true, label %cond.false, !dbg !868

cond.true:                                        ; preds = %do.body24
  br label %cond.end, !dbg !871

cond.false:                                       ; preds = %do.body24
  call void @__assert_fail(i8* getelementptr inbounds ([19 x i8], [19 x i8]* @.str, i32 0, i32 0), i8* getelementptr inbounds ([66 x i8], [66 x i8]* @.str.1, i32 0, i32 0), i32 1034, i8* getelementptr inbounds ([69 x i8], [69 x i8]* @__PRETTY_FUNCTION__.uv_fs_chmod, i32 0, i32 0)) #8, !dbg !873
  unreachable, !dbg !873
                                                  ; No predecessors!
  br label %cond.end, !dbg !875

cond.end:                                         ; preds = %29, %cond.true
  %30 = load void (%struct.uv_fs_s*)*, void (%struct.uv_fs_s*)** %cb.addr, align 8, !dbg !877
  %cmp26 = icmp eq void (%struct.uv_fs_s*)* %30, null, !dbg !877
  br i1 %cmp26, label %if.then27, label %if.else, !dbg !877

if.then27:                                        ; preds = %cond.end
  %31 = load i8*, i8** %path.addr, align 8, !dbg !880
  %32 = load %struct.uv_fs_s*, %struct.uv_fs_s** %req.addr, align 8, !dbg !880
  %path28 = getelementptr inbounds %struct.uv_fs_s, %struct.uv_fs_s* %32, i32 0, i32 9, !dbg !880
  store i8* %31, i8** %path28, align 8, !dbg !880
  br label %if.end57, !dbg !880

if.else:                                          ; preds = %cond.end
  %33 = load i8*, i8** %path.addr, align 8, !dbg !883
  %call = call i8* @uv__strdup(i8* %33), !dbg !883
  %34 = load %struct.uv_fs_s*, %struct.uv_fs_s** %req.addr, align 8, !dbg !883
  %path29 = getelementptr inbounds %struct.uv_fs_s, %struct.uv_fs_s* %34, i32 0, i32 9, !dbg !883
  store i8* %call, i8** %path29, align 8, !dbg !883
  %35 = load %struct.uv_fs_s*, %struct.uv_fs_s** %req.addr, align 8, !dbg !883
  %path30 = getelementptr inbounds %struct.uv_fs_s, %struct.uv_fs_s* %35, i32 0, i32 9, !dbg !883
  %36 = load i8*, i8** %path30, align 8, !dbg !883
  %cmp31 = icmp eq i8* %36, null, !dbg !883
  br i1 %cmp31, label %if.then32, label %if.end56, !dbg !883

if.then32:                                        ; preds = %if.else
  br label %do.body33, !dbg !886

do.body33:                                        ; preds = %if.then32
  %37 = load %struct.uv_loop_s*, %struct.uv_loop_s** %loop.addr, align 8, !dbg !890
  %active_reqs34 = getelementptr inbounds %struct.uv_loop_s, %struct.uv_loop_s* %37, i32 0, i32 3, !dbg !890
  %38 = load %struct.uv_loop_s*, %struct.uv_loop_s** %loop.addr, align 8, !dbg !890
  %active_reqs35 = getelementptr inbounds %struct.uv_loop_s, %struct.uv_loop_s* %38, i32 0, i32 3, !dbg !890
  %arrayidx36 = getelementptr inbounds [2 x i8*], [2 x i8*]* %active_reqs35, i64 0, i64 0, !dbg !890
  %39 = bitcast i8** %arrayidx36 to [2 x i8*]**, !dbg !890
  %40 = load [2 x i8*]*, [2 x i8*]** %39, align 8, !dbg !890
  %cmp37 = icmp eq [2 x i8*]* %active_reqs34, %40, !dbg !890
  %conv = zext i1 %cmp37 to i32, !dbg !890
  %cmp38 = icmp eq i32 %conv, 0, !dbg !890
  br i1 %cmp38, label %cond.true40, label %cond.false41, !dbg !890

cond.true40:                                      ; preds = %do.body33
  br label %cond.end42, !dbg !893

cond.false41:                                     ; preds = %do.body33
  call void @__assert_fail(i8* getelementptr inbounds ([113 x i8], [113 x i8]* @.str.2, i32 0, i32 0), i8* getelementptr inbounds ([66 x i8], [66 x i8]* @.str.1, i32 0, i32 0), i32 1034, i8* getelementptr inbounds ([69 x i8], [69 x i8]* @__PRETTY_FUNCTION__.uv_fs_chmod, i32 0, i32 0)) #8, !dbg !895
  unreachable, !dbg !895
                                                  ; No predecessors!
  br label %cond.end42, !dbg !897

cond.end42:                                       ; preds = %41, %cond.true40
  br label %do.body43, !dbg !899

do.body43:                                        ; preds = %cond.end42
  %42 = load %struct.uv_fs_s*, %struct.uv_fs_s** %req.addr, align 8, !dbg !901
  %active_queue44 = getelementptr inbounds %struct.uv_fs_s, %struct.uv_fs_s* %42, i32 0, i32 2, !dbg !901
  %arrayidx45 = getelementptr inbounds [2 x i8*], [2 x i8*]* %active_queue44, i64 0, i64 0, !dbg !901
  %43 = bitcast i8** %arrayidx45 to [2 x i8*]**, !dbg !901
  %44 = load [2 x i8*]*, [2 x i8*]** %43, align 8, !dbg !901
  %45 = load %struct.uv_fs_s*, %struct.uv_fs_s** %req.addr, align 8, !dbg !901
  %active_queue46 = getelementptr inbounds %struct.uv_fs_s, %struct.uv_fs_s* %45, i32 0, i32 2, !dbg !901
  %arrayidx47 = getelementptr inbounds [2 x i8*], [2 x i8*]* %active_queue46, i64 0, i64 1, !dbg !901
  %46 = bitcast i8** %arrayidx47 to [2 x i8*]**, !dbg !901
  %47 = load [2 x i8*]*, [2 x i8*]** %46, align 8, !dbg !901
  %arrayidx48 = getelementptr inbounds [2 x i8*], [2 x i8*]* %47, i64 0, i64 0, !dbg !901
  %48 = bitcast i8** %arrayidx48 to [2 x i8*]**, !dbg !901
  store [2 x i8*]* %44, [2 x i8*]** %48, align 8, !dbg !901
  %49 = load %struct.uv_fs_s*, %struct.uv_fs_s** %req.addr, align 8, !dbg !901
  %active_queue49 = getelementptr inbounds %struct.uv_fs_s, %struct.uv_fs_s* %49, i32 0, i32 2, !dbg !901
  %arrayidx50 = getelementptr inbounds [2 x i8*], [2 x i8*]* %active_queue49, i64 0, i64 1, !dbg !901
  %50 = bitcast i8** %arrayidx50 to [2 x i8*]**, !dbg !901
  %51 = load [2 x i8*]*, [2 x i8*]** %50, align 8, !dbg !901
  %52 = load %struct.uv_fs_s*, %struct.uv_fs_s** %req.addr, align 8, !dbg !901
  %active_queue51 = getelementptr inbounds %struct.uv_fs_s, %struct.uv_fs_s* %52, i32 0, i32 2, !dbg !901
  %arrayidx52 = getelementptr inbounds [2 x i8*], [2 x i8*]* %active_queue51, i64 0, i64 0, !dbg !901
  %53 = bitcast i8** %arrayidx52 to [2 x i8*]**, !dbg !901
  %54 = load [2 x i8*]*, [2 x i8*]** %53, align 8, !dbg !901
  %arrayidx53 = getelementptr inbounds [2 x i8*], [2 x i8*]* %54, i64 0, i64 1, !dbg !901
  %55 = bitcast i8** %arrayidx53 to [2 x i8*]**, !dbg !901
  store [2 x i8*]* %51, [2 x i8*]** %55, align 8, !dbg !901
  br label %do.end54, !dbg !901

do.end54:                                         ; preds = %do.body43
  br label %do.end55, !dbg !904

do.end55:                                         ; preds = %do.end54
  store i32 -12, i32* %retval, align 4, !dbg !906
  br label %do.end68, !dbg !906

if.end56:                                         ; preds = %if.else
  br label %if.end57

if.end57:                                         ; preds = %if.end56, %if.then27
  br label %do.end58, !dbg !908

do.end58:                                         ; preds = %if.end57
  %56 = load i32, i32* %mode.addr, align 4, !dbg !910
  %57 = load %struct.uv_fs_s*, %struct.uv_fs_s** %req.addr, align 8, !dbg !911
  %mode59 = getelementptr inbounds %struct.uv_fs_s, %struct.uv_fs_s* %57, i32 0, i32 14, !dbg !912
  store i32 %56, i32* %mode59, align 8, !dbg !913
  br label %do.body60, !dbg !914

do.body60:                                        ; preds = %do.end58
  %58 = load void (%struct.uv_fs_s*)*, void (%struct.uv_fs_s*)** %cb.addr, align 8, !dbg !915
  %cmp61 = icmp ne void (%struct.uv_fs_s*)* %58, null, !dbg !915
  br i1 %cmp61, label %if.then63, label %if.else64, !dbg !915

if.then63:                                        ; preds = %do.body60
  %59 = load %struct.uv_loop_s*, %struct.uv_loop_s** %loop.addr, align 8, !dbg !919
  %60 = load %struct.uv_fs_s*, %struct.uv_fs_s** %req.addr, align 8, !dbg !919
  %work_req = getelementptr inbounds %struct.uv_fs_s, %struct.uv_fs_s* %60, i32 0, i32 22, !dbg !919
  call void @uv__work_submit(%struct.uv_loop_s* %59, %struct.uv__work* %work_req, void (%struct.uv__work*)* @uv__fs_work, void (%struct.uv__work*, i32)* @uv__fs_done), !dbg !919
  store i32 0, i32* %retval, align 4, !dbg !919
  br label %do.end68, !dbg !919

if.else64:                                        ; preds = %do.body60
  %61 = load %struct.uv_fs_s*, %struct.uv_fs_s** %req.addr, align 8, !dbg !922
  %work_req65 = getelementptr inbounds %struct.uv_fs_s, %struct.uv_fs_s* %61, i32 0, i32 22, !dbg !922
  call void @uv__fs_work(%struct.uv__work* %work_req65), !dbg !922
  %62 = load %struct.uv_fs_s*, %struct.uv_fs_s** %req.addr, align 8, !dbg !922
  %result66 = getelementptr inbounds %struct.uv_fs_s, %struct.uv_fs_s* %62, i32 0, i32 7, !dbg !922
  %63 = load i64, i64* %result66, align 8, !dbg !922
  %conv67 = trunc i64 %63 to i32, !dbg !922
  store i32 %conv67, i32* %retval, align 4, !dbg !922
  br label %do.end68, !dbg !922

do.end68:                                         ; preds = %do.end55, %if.then63, %if.else64
  %64 = load i32, i32* %retval, align 4, !dbg !925
  ret i32 %64, !dbg !925
}

; Function Attrs: nounwind uwtable
define i32 @uv_fs_chown(%struct.uv_loop_s* %loop, %struct.uv_fs_s* %req, i8* %path, i32 %uid, i32 %gid, void (%struct.uv_fs_s*)* %cb) #0 !dbg !420 {
entry:
  %retval = alloca i32, align 4
  %loop.addr = alloca %struct.uv_loop_s*, align 8
  %req.addr = alloca %struct.uv_fs_s*, align 8
  %path.addr = alloca i8*, align 8
  %uid.addr = alloca i32, align 4
  %gid.addr = alloca i32, align 4
  %cb.addr = alloca void (%struct.uv_fs_s*)*, align 8
  store %struct.uv_loop_s* %loop, %struct.uv_loop_s** %loop.addr, align 8
  call void @llvm.dbg.declare(metadata %struct.uv_loop_s** %loop.addr, metadata !926, metadata !580), !dbg !927
  store %struct.uv_fs_s* %req, %struct.uv_fs_s** %req.addr, align 8
  call void @llvm.dbg.declare(metadata %struct.uv_fs_s** %req.addr, metadata !928, metadata !580), !dbg !929
  store i8* %path, i8** %path.addr, align 8
  call void @llvm.dbg.declare(metadata i8** %path.addr, metadata !930, metadata !580), !dbg !931
  store i32 %uid, i32* %uid.addr, align 4
  call void @llvm.dbg.declare(metadata i32* %uid.addr, metadata !932, metadata !580), !dbg !933
  store i32 %gid, i32* %gid.addr, align 4
  call void @llvm.dbg.declare(metadata i32* %gid.addr, metadata !934, metadata !580), !dbg !935
  store void (%struct.uv_fs_s*)* %cb, void (%struct.uv_fs_s*)** %cb.addr, align 8
  call void @llvm.dbg.declare(metadata void (%struct.uv_fs_s*)** %cb.addr, metadata !936, metadata !580), !dbg !937
  br label %do.body, !dbg !938

do.body:                                          ; preds = %entry
  %0 = load %struct.uv_fs_s*, %struct.uv_fs_s** %req.addr, align 8, !dbg !939
  %type = getelementptr inbounds %struct.uv_fs_s, %struct.uv_fs_s* %0, i32 0, i32 1, !dbg !939
  store i32 6, i32* %type, align 8, !dbg !939
  %1 = load void (%struct.uv_fs_s*)*, void (%struct.uv_fs_s*)** %cb.addr, align 8, !dbg !939
  %cmp = icmp ne void (%struct.uv_fs_s*)* %1, null, !dbg !939
  br i1 %cmp, label %if.then, label %if.end, !dbg !939

if.then:                                          ; preds = %do.body
  br label %do.body1, !dbg !942

do.body1:                                         ; preds = %if.then
  br label %do.body2, !dbg !945

do.body2:                                         ; preds = %do.body1
  %2 = load %struct.uv_fs_s*, %struct.uv_fs_s** %req.addr, align 8, !dbg !948
  %type3 = getelementptr inbounds %struct.uv_fs_s, %struct.uv_fs_s* %2, i32 0, i32 1, !dbg !948
  store i32 6, i32* %type3, align 8, !dbg !948
  br label %do.end, !dbg !948

do.end:                                           ; preds = %do.body2
  br label %do.body4, !dbg !951

do.body4:                                         ; preds = %do.end
  br label %do.body5, !dbg !953

do.body5:                                         ; preds = %do.body4
  %3 = load %struct.uv_loop_s*, %struct.uv_loop_s** %loop.addr, align 8, !dbg !956
  %active_reqs = getelementptr inbounds %struct.uv_loop_s, %struct.uv_loop_s* %3, i32 0, i32 3, !dbg !956
  %4 = load %struct.uv_fs_s*, %struct.uv_fs_s** %req.addr, align 8, !dbg !956
  %active_queue = getelementptr inbounds %struct.uv_fs_s, %struct.uv_fs_s* %4, i32 0, i32 2, !dbg !956
  %arrayidx = getelementptr inbounds [2 x i8*], [2 x i8*]* %active_queue, i64 0, i64 0, !dbg !956
  %5 = bitcast i8** %arrayidx to [2 x i8*]**, !dbg !956
  store [2 x i8*]* %active_reqs, [2 x i8*]** %5, align 8, !dbg !956
  %6 = load %struct.uv_loop_s*, %struct.uv_loop_s** %loop.addr, align 8, !dbg !956
  %active_reqs6 = getelementptr inbounds %struct.uv_loop_s, %struct.uv_loop_s* %6, i32 0, i32 3, !dbg !956
  %arrayidx7 = getelementptr inbounds [2 x i8*], [2 x i8*]* %active_reqs6, i64 0, i64 1, !dbg !956
  %7 = bitcast i8** %arrayidx7 to [2 x i8*]**, !dbg !956
  %8 = load [2 x i8*]*, [2 x i8*]** %7, align 8, !dbg !956
  %9 = load %struct.uv_fs_s*, %struct.uv_fs_s** %req.addr, align 8, !dbg !956
  %active_queue8 = getelementptr inbounds %struct.uv_fs_s, %struct.uv_fs_s* %9, i32 0, i32 2, !dbg !956
  %arrayidx9 = getelementptr inbounds [2 x i8*], [2 x i8*]* %active_queue8, i64 0, i64 1, !dbg !956
  %10 = bitcast i8** %arrayidx9 to [2 x i8*]**, !dbg !956
  store [2 x i8*]* %8, [2 x i8*]** %10, align 8, !dbg !956
  %11 = load %struct.uv_fs_s*, %struct.uv_fs_s** %req.addr, align 8, !dbg !956
  %active_queue10 = getelementptr inbounds %struct.uv_fs_s, %struct.uv_fs_s* %11, i32 0, i32 2, !dbg !956
  %12 = load %struct.uv_fs_s*, %struct.uv_fs_s** %req.addr, align 8, !dbg !956
  %active_queue11 = getelementptr inbounds %struct.uv_fs_s, %struct.uv_fs_s* %12, i32 0, i32 2, !dbg !956
  %arrayidx12 = getelementptr inbounds [2 x i8*], [2 x i8*]* %active_queue11, i64 0, i64 1, !dbg !956
  %13 = bitcast i8** %arrayidx12 to [2 x i8*]**, !dbg !956
  %14 = load [2 x i8*]*, [2 x i8*]** %13, align 8, !dbg !956
  %arrayidx13 = getelementptr inbounds [2 x i8*], [2 x i8*]* %14, i64 0, i64 0, !dbg !956
  %15 = bitcast i8** %arrayidx13 to [2 x i8*]**, !dbg !956
  store [2 x i8*]* %active_queue10, [2 x i8*]** %15, align 8, !dbg !956
  %16 = load %struct.uv_fs_s*, %struct.uv_fs_s** %req.addr, align 8, !dbg !956
  %active_queue14 = getelementptr inbounds %struct.uv_fs_s, %struct.uv_fs_s* %16, i32 0, i32 2, !dbg !956
  %17 = load %struct.uv_loop_s*, %struct.uv_loop_s** %loop.addr, align 8, !dbg !956
  %active_reqs15 = getelementptr inbounds %struct.uv_loop_s, %struct.uv_loop_s* %17, i32 0, i32 3, !dbg !956
  %arrayidx16 = getelementptr inbounds [2 x i8*], [2 x i8*]* %active_reqs15, i64 0, i64 1, !dbg !956
  %18 = bitcast i8** %arrayidx16 to [2 x i8*]**, !dbg !956
  store [2 x i8*]* %active_queue14, [2 x i8*]** %18, align 8, !dbg !956
  br label %do.end17, !dbg !956

do.end17:                                         ; preds = %do.body5
  br label %do.end18, !dbg !959

do.end18:                                         ; preds = %do.end17
  br label %do.end19, !dbg !961

do.end19:                                         ; preds = %do.end18
  br label %if.end, !dbg !963

if.end:                                           ; preds = %do.end19, %do.body
  %19 = load %struct.uv_fs_s*, %struct.uv_fs_s** %req.addr, align 8, !dbg !965
  %fs_type = getelementptr inbounds %struct.uv_fs_s, %struct.uv_fs_s* %19, i32 0, i32 4, !dbg !965
  store i32 26, i32* %fs_type, align 8, !dbg !965
  %20 = load %struct.uv_fs_s*, %struct.uv_fs_s** %req.addr, align 8, !dbg !965
  %result = getelementptr inbounds %struct.uv_fs_s, %struct.uv_fs_s* %20, i32 0, i32 7, !dbg !965
  store i64 0, i64* %result, align 8, !dbg !965
  %21 = load %struct.uv_fs_s*, %struct.uv_fs_s** %req.addr, align 8, !dbg !965
  %ptr = getelementptr inbounds %struct.uv_fs_s, %struct.uv_fs_s* %21, i32 0, i32 8, !dbg !965
  store i8* null, i8** %ptr, align 8, !dbg !965
  %22 = load %struct.uv_loop_s*, %struct.uv_loop_s** %loop.addr, align 8, !dbg !965
  %23 = load %struct.uv_fs_s*, %struct.uv_fs_s** %req.addr, align 8, !dbg !965
  %loop20 = getelementptr inbounds %struct.uv_fs_s, %struct.uv_fs_s* %23, i32 0, i32 5, !dbg !965
  store %struct.uv_loop_s* %22, %struct.uv_loop_s** %loop20, align 8, !dbg !965
  %24 = load %struct.uv_fs_s*, %struct.uv_fs_s** %req.addr, align 8, !dbg !965
  %path21 = getelementptr inbounds %struct.uv_fs_s, %struct.uv_fs_s* %24, i32 0, i32 9, !dbg !965
  store i8* null, i8** %path21, align 8, !dbg !965
  %25 = load %struct.uv_fs_s*, %struct.uv_fs_s** %req.addr, align 8, !dbg !965
  %new_path = getelementptr inbounds %struct.uv_fs_s, %struct.uv_fs_s* %25, i32 0, i32 11, !dbg !965
  store i8* null, i8** %new_path, align 8, !dbg !965
  %26 = load void (%struct.uv_fs_s*)*, void (%struct.uv_fs_s*)** %cb.addr, align 8, !dbg !965
  %27 = load %struct.uv_fs_s*, %struct.uv_fs_s** %req.addr, align 8, !dbg !965
  %cb22 = getelementptr inbounds %struct.uv_fs_s, %struct.uv_fs_s* %27, i32 0, i32 6, !dbg !965
  store void (%struct.uv_fs_s*)* %26, void (%struct.uv_fs_s*)** %cb22, align 8, !dbg !965
  br label %do.end23, !dbg !965

do.end23:                                         ; preds = %if.end
  br label %do.body24, !dbg !967

do.body24:                                        ; preds = %do.end23
  %28 = load i8*, i8** %path.addr, align 8, !dbg !968
  %cmp25 = icmp ne i8* %28, null, !dbg !968
  br i1 %cmp25, label %cond.true, label %cond.false, !dbg !968

cond.true:                                        ; preds = %do.body24
  br label %cond.end, !dbg !971

cond.false:                                       ; preds = %do.body24
  call void @__assert_fail(i8* getelementptr inbounds ([19 x i8], [19 x i8]* @.str, i32 0, i32 0), i8* getelementptr inbounds ([66 x i8], [66 x i8]* @.str.1, i32 0, i32 0), i32 1047, i8* getelementptr inbounds ([84 x i8], [84 x i8]* @__PRETTY_FUNCTION__.uv_fs_chown, i32 0, i32 0)) #8, !dbg !973
  unreachable, !dbg !973
                                                  ; No predecessors!
  br label %cond.end, !dbg !975

cond.end:                                         ; preds = %29, %cond.true
  %30 = load void (%struct.uv_fs_s*)*, void (%struct.uv_fs_s*)** %cb.addr, align 8, !dbg !977
  %cmp26 = icmp eq void (%struct.uv_fs_s*)* %30, null, !dbg !977
  br i1 %cmp26, label %if.then27, label %if.else, !dbg !977

if.then27:                                        ; preds = %cond.end
  %31 = load i8*, i8** %path.addr, align 8, !dbg !980
  %32 = load %struct.uv_fs_s*, %struct.uv_fs_s** %req.addr, align 8, !dbg !980
  %path28 = getelementptr inbounds %struct.uv_fs_s, %struct.uv_fs_s* %32, i32 0, i32 9, !dbg !980
  store i8* %31, i8** %path28, align 8, !dbg !980
  br label %if.end57, !dbg !980

if.else:                                          ; preds = %cond.end
  %33 = load i8*, i8** %path.addr, align 8, !dbg !983
  %call = call i8* @uv__strdup(i8* %33), !dbg !983
  %34 = load %struct.uv_fs_s*, %struct.uv_fs_s** %req.addr, align 8, !dbg !983
  %path29 = getelementptr inbounds %struct.uv_fs_s, %struct.uv_fs_s* %34, i32 0, i32 9, !dbg !983
  store i8* %call, i8** %path29, align 8, !dbg !983
  %35 = load %struct.uv_fs_s*, %struct.uv_fs_s** %req.addr, align 8, !dbg !983
  %path30 = getelementptr inbounds %struct.uv_fs_s, %struct.uv_fs_s* %35, i32 0, i32 9, !dbg !983
  %36 = load i8*, i8** %path30, align 8, !dbg !983
  %cmp31 = icmp eq i8* %36, null, !dbg !983
  br i1 %cmp31, label %if.then32, label %if.end56, !dbg !983

if.then32:                                        ; preds = %if.else
  br label %do.body33, !dbg !986

do.body33:                                        ; preds = %if.then32
  %37 = load %struct.uv_loop_s*, %struct.uv_loop_s** %loop.addr, align 8, !dbg !990
  %active_reqs34 = getelementptr inbounds %struct.uv_loop_s, %struct.uv_loop_s* %37, i32 0, i32 3, !dbg !990
  %38 = load %struct.uv_loop_s*, %struct.uv_loop_s** %loop.addr, align 8, !dbg !990
  %active_reqs35 = getelementptr inbounds %struct.uv_loop_s, %struct.uv_loop_s* %38, i32 0, i32 3, !dbg !990
  %arrayidx36 = getelementptr inbounds [2 x i8*], [2 x i8*]* %active_reqs35, i64 0, i64 0, !dbg !990
  %39 = bitcast i8** %arrayidx36 to [2 x i8*]**, !dbg !990
  %40 = load [2 x i8*]*, [2 x i8*]** %39, align 8, !dbg !990
  %cmp37 = icmp eq [2 x i8*]* %active_reqs34, %40, !dbg !990
  %conv = zext i1 %cmp37 to i32, !dbg !990
  %cmp38 = icmp eq i32 %conv, 0, !dbg !990
  br i1 %cmp38, label %cond.true40, label %cond.false41, !dbg !990

cond.true40:                                      ; preds = %do.body33
  br label %cond.end42, !dbg !993

cond.false41:                                     ; preds = %do.body33
  call void @__assert_fail(i8* getelementptr inbounds ([113 x i8], [113 x i8]* @.str.2, i32 0, i32 0), i8* getelementptr inbounds ([66 x i8], [66 x i8]* @.str.1, i32 0, i32 0), i32 1047, i8* getelementptr inbounds ([84 x i8], [84 x i8]* @__PRETTY_FUNCTION__.uv_fs_chown, i32 0, i32 0)) #8, !dbg !995
  unreachable, !dbg !995
                                                  ; No predecessors!
  br label %cond.end42, !dbg !997

cond.end42:                                       ; preds = %41, %cond.true40
  br label %do.body43, !dbg !999

do.body43:                                        ; preds = %cond.end42
  %42 = load %struct.uv_fs_s*, %struct.uv_fs_s** %req.addr, align 8, !dbg !1001
  %active_queue44 = getelementptr inbounds %struct.uv_fs_s, %struct.uv_fs_s* %42, i32 0, i32 2, !dbg !1001
  %arrayidx45 = getelementptr inbounds [2 x i8*], [2 x i8*]* %active_queue44, i64 0, i64 0, !dbg !1001
  %43 = bitcast i8** %arrayidx45 to [2 x i8*]**, !dbg !1001
  %44 = load [2 x i8*]*, [2 x i8*]** %43, align 8, !dbg !1001
  %45 = load %struct.uv_fs_s*, %struct.uv_fs_s** %req.addr, align 8, !dbg !1001
  %active_queue46 = getelementptr inbounds %struct.uv_fs_s, %struct.uv_fs_s* %45, i32 0, i32 2, !dbg !1001
  %arrayidx47 = getelementptr inbounds [2 x i8*], [2 x i8*]* %active_queue46, i64 0, i64 1, !dbg !1001
  %46 = bitcast i8** %arrayidx47 to [2 x i8*]**, !dbg !1001
  %47 = load [2 x i8*]*, [2 x i8*]** %46, align 8, !dbg !1001
  %arrayidx48 = getelementptr inbounds [2 x i8*], [2 x i8*]* %47, i64 0, i64 0, !dbg !1001
  %48 = bitcast i8** %arrayidx48 to [2 x i8*]**, !dbg !1001
  store [2 x i8*]* %44, [2 x i8*]** %48, align 8, !dbg !1001
  %49 = load %struct.uv_fs_s*, %struct.uv_fs_s** %req.addr, align 8, !dbg !1001
  %active_queue49 = getelementptr inbounds %struct.uv_fs_s, %struct.uv_fs_s* %49, i32 0, i32 2, !dbg !1001
  %arrayidx50 = getelementptr inbounds [2 x i8*], [2 x i8*]* %active_queue49, i64 0, i64 1, !dbg !1001
  %50 = bitcast i8** %arrayidx50 to [2 x i8*]**, !dbg !1001
  %51 = load [2 x i8*]*, [2 x i8*]** %50, align 8, !dbg !1001
  %52 = load %struct.uv_fs_s*, %struct.uv_fs_s** %req.addr, align 8, !dbg !1001
  %active_queue51 = getelementptr inbounds %struct.uv_fs_s, %struct.uv_fs_s* %52, i32 0, i32 2, !dbg !1001
  %arrayidx52 = getelementptr inbounds [2 x i8*], [2 x i8*]* %active_queue51, i64 0, i64 0, !dbg !1001
  %53 = bitcast i8** %arrayidx52 to [2 x i8*]**, !dbg !1001
  %54 = load [2 x i8*]*, [2 x i8*]** %53, align 8, !dbg !1001
  %arrayidx53 = getelementptr inbounds [2 x i8*], [2 x i8*]* %54, i64 0, i64 1, !dbg !1001
  %55 = bitcast i8** %arrayidx53 to [2 x i8*]**, !dbg !1001
  store [2 x i8*]* %51, [2 x i8*]** %55, align 8, !dbg !1001
  br label %do.end54, !dbg !1001

do.end54:                                         ; preds = %do.body43
  br label %do.end55, !dbg !1004

do.end55:                                         ; preds = %do.end54
  store i32 -12, i32* %retval, align 4, !dbg !1006
  br label %do.end69, !dbg !1006

if.end56:                                         ; preds = %if.else
  br label %if.end57

if.end57:                                         ; preds = %if.end56, %if.then27
  br label %do.end58, !dbg !1008

do.end58:                                         ; preds = %if.end57
  %56 = load i32, i32* %uid.addr, align 4, !dbg !1010
  %57 = load %struct.uv_fs_s*, %struct.uv_fs_s** %req.addr, align 8, !dbg !1011
  %uid59 = getelementptr inbounds %struct.uv_fs_s, %struct.uv_fs_s* %57, i32 0, i32 18, !dbg !1012
  store i32 %56, i32* %uid59, align 8, !dbg !1013
  %58 = load i32, i32* %gid.addr, align 4, !dbg !1014
  %59 = load %struct.uv_fs_s*, %struct.uv_fs_s** %req.addr, align 8, !dbg !1015
  %gid60 = getelementptr inbounds %struct.uv_fs_s, %struct.uv_fs_s* %59, i32 0, i32 19, !dbg !1016
  store i32 %58, i32* %gid60, align 4, !dbg !1017
  br label %do.body61, !dbg !1018

do.body61:                                        ; preds = %do.end58
  %60 = load void (%struct.uv_fs_s*)*, void (%struct.uv_fs_s*)** %cb.addr, align 8, !dbg !1019
  %cmp62 = icmp ne void (%struct.uv_fs_s*)* %60, null, !dbg !1019
  br i1 %cmp62, label %if.then64, label %if.else65, !dbg !1019

if.then64:                                        ; preds = %do.body61
  %61 = load %struct.uv_loop_s*, %struct.uv_loop_s** %loop.addr, align 8, !dbg !1023
  %62 = load %struct.uv_fs_s*, %struct.uv_fs_s** %req.addr, align 8, !dbg !1023
  %work_req = getelementptr inbounds %struct.uv_fs_s, %struct.uv_fs_s* %62, i32 0, i32 22, !dbg !1023
  call void @uv__work_submit(%struct.uv_loop_s* %61, %struct.uv__work* %work_req, void (%struct.uv__work*)* @uv__fs_work, void (%struct.uv__work*, i32)* @uv__fs_done), !dbg !1023
  store i32 0, i32* %retval, align 4, !dbg !1023
  br label %do.end69, !dbg !1023

if.else65:                                        ; preds = %do.body61
  %63 = load %struct.uv_fs_s*, %struct.uv_fs_s** %req.addr, align 8, !dbg !1026
  %work_req66 = getelementptr inbounds %struct.uv_fs_s, %struct.uv_fs_s* %63, i32 0, i32 22, !dbg !1026
  call void @uv__fs_work(%struct.uv__work* %work_req66), !dbg !1026
  %64 = load %struct.uv_fs_s*, %struct.uv_fs_s** %req.addr, align 8, !dbg !1026
  %result67 = getelementptr inbounds %struct.uv_fs_s, %struct.uv_fs_s* %64, i32 0, i32 7, !dbg !1026
  %65 = load i64, i64* %result67, align 8, !dbg !1026
  %conv68 = trunc i64 %65 to i32, !dbg !1026
  store i32 %conv68, i32* %retval, align 4, !dbg !1026
  br label %do.end69, !dbg !1026

do.end69:                                         ; preds = %do.end55, %if.then64, %if.else65
  %66 = load i32, i32* %retval, align 4, !dbg !1029
  ret i32 %66, !dbg !1029
}

; Function Attrs: nounwind uwtable
define i32 @uv_fs_close(%struct.uv_loop_s* %loop, %struct.uv_fs_s* %req, i32 %file, void (%struct.uv_fs_s*)* %cb) #0 !dbg !423 {
entry:
  %retval = alloca i32, align 4
  %loop.addr = alloca %struct.uv_loop_s*, align 8
  %req.addr = alloca %struct.uv_fs_s*, align 8
  %file.addr = alloca i32, align 4
  %cb.addr = alloca void (%struct.uv_fs_s*)*, align 8
  store %struct.uv_loop_s* %loop, %struct.uv_loop_s** %loop.addr, align 8
  call void @llvm.dbg.declare(metadata %struct.uv_loop_s** %loop.addr, metadata !1030, metadata !580), !dbg !1031
  store %struct.uv_fs_s* %req, %struct.uv_fs_s** %req.addr, align 8
  call void @llvm.dbg.declare(metadata %struct.uv_fs_s** %req.addr, metadata !1032, metadata !580), !dbg !1033
  store i32 %file, i32* %file.addr, align 4
  call void @llvm.dbg.declare(metadata i32* %file.addr, metadata !1034, metadata !580), !dbg !1035
  store void (%struct.uv_fs_s*)* %cb, void (%struct.uv_fs_s*)** %cb.addr, align 8
  call void @llvm.dbg.declare(metadata void (%struct.uv_fs_s*)** %cb.addr, metadata !1036, metadata !580), !dbg !1037
  br label %do.body, !dbg !1038

do.body:                                          ; preds = %entry
  %0 = load %struct.uv_fs_s*, %struct.uv_fs_s** %req.addr, align 8, !dbg !1039
  %type = getelementptr inbounds %struct.uv_fs_s, %struct.uv_fs_s* %0, i32 0, i32 1, !dbg !1039
  store i32 6, i32* %type, align 8, !dbg !1039
  %1 = load void (%struct.uv_fs_s*)*, void (%struct.uv_fs_s*)** %cb.addr, align 8, !dbg !1039
  %cmp = icmp ne void (%struct.uv_fs_s*)* %1, null, !dbg !1039
  br i1 %cmp, label %if.then, label %if.end, !dbg !1039

if.then:                                          ; preds = %do.body
  br label %do.body1, !dbg !1042

do.body1:                                         ; preds = %if.then
  br label %do.body2, !dbg !1045

do.body2:                                         ; preds = %do.body1
  %2 = load %struct.uv_fs_s*, %struct.uv_fs_s** %req.addr, align 8, !dbg !1048
  %type3 = getelementptr inbounds %struct.uv_fs_s, %struct.uv_fs_s* %2, i32 0, i32 1, !dbg !1048
  store i32 6, i32* %type3, align 8, !dbg !1048
  br label %do.end, !dbg !1048

do.end:                                           ; preds = %do.body2
  br label %do.body4, !dbg !1051

do.body4:                                         ; preds = %do.end
  br label %do.body5, !dbg !1053

do.body5:                                         ; preds = %do.body4
  %3 = load %struct.uv_loop_s*, %struct.uv_loop_s** %loop.addr, align 8, !dbg !1056
  %active_reqs = getelementptr inbounds %struct.uv_loop_s, %struct.uv_loop_s* %3, i32 0, i32 3, !dbg !1056
  %4 = load %struct.uv_fs_s*, %struct.uv_fs_s** %req.addr, align 8, !dbg !1056
  %active_queue = getelementptr inbounds %struct.uv_fs_s, %struct.uv_fs_s* %4, i32 0, i32 2, !dbg !1056
  %arrayidx = getelementptr inbounds [2 x i8*], [2 x i8*]* %active_queue, i64 0, i64 0, !dbg !1056
  %5 = bitcast i8** %arrayidx to [2 x i8*]**, !dbg !1056
  store [2 x i8*]* %active_reqs, [2 x i8*]** %5, align 8, !dbg !1056
  %6 = load %struct.uv_loop_s*, %struct.uv_loop_s** %loop.addr, align 8, !dbg !1056
  %active_reqs6 = getelementptr inbounds %struct.uv_loop_s, %struct.uv_loop_s* %6, i32 0, i32 3, !dbg !1056
  %arrayidx7 = getelementptr inbounds [2 x i8*], [2 x i8*]* %active_reqs6, i64 0, i64 1, !dbg !1056
  %7 = bitcast i8** %arrayidx7 to [2 x i8*]**, !dbg !1056
  %8 = load [2 x i8*]*, [2 x i8*]** %7, align 8, !dbg !1056
  %9 = load %struct.uv_fs_s*, %struct.uv_fs_s** %req.addr, align 8, !dbg !1056
  %active_queue8 = getelementptr inbounds %struct.uv_fs_s, %struct.uv_fs_s* %9, i32 0, i32 2, !dbg !1056
  %arrayidx9 = getelementptr inbounds [2 x i8*], [2 x i8*]* %active_queue8, i64 0, i64 1, !dbg !1056
  %10 = bitcast i8** %arrayidx9 to [2 x i8*]**, !dbg !1056
  store [2 x i8*]* %8, [2 x i8*]** %10, align 8, !dbg !1056
  %11 = load %struct.uv_fs_s*, %struct.uv_fs_s** %req.addr, align 8, !dbg !1056
  %active_queue10 = getelementptr inbounds %struct.uv_fs_s, %struct.uv_fs_s* %11, i32 0, i32 2, !dbg !1056
  %12 = load %struct.uv_fs_s*, %struct.uv_fs_s** %req.addr, align 8, !dbg !1056
  %active_queue11 = getelementptr inbounds %struct.uv_fs_s, %struct.uv_fs_s* %12, i32 0, i32 2, !dbg !1056
  %arrayidx12 = getelementptr inbounds [2 x i8*], [2 x i8*]* %active_queue11, i64 0, i64 1, !dbg !1056
  %13 = bitcast i8** %arrayidx12 to [2 x i8*]**, !dbg !1056
  %14 = load [2 x i8*]*, [2 x i8*]** %13, align 8, !dbg !1056
  %arrayidx13 = getelementptr inbounds [2 x i8*], [2 x i8*]* %14, i64 0, i64 0, !dbg !1056
  %15 = bitcast i8** %arrayidx13 to [2 x i8*]**, !dbg !1056
  store [2 x i8*]* %active_queue10, [2 x i8*]** %15, align 8, !dbg !1056
  %16 = load %struct.uv_fs_s*, %struct.uv_fs_s** %req.addr, align 8, !dbg !1056
  %active_queue14 = getelementptr inbounds %struct.uv_fs_s, %struct.uv_fs_s* %16, i32 0, i32 2, !dbg !1056
  %17 = load %struct.uv_loop_s*, %struct.uv_loop_s** %loop.addr, align 8, !dbg !1056
  %active_reqs15 = getelementptr inbounds %struct.uv_loop_s, %struct.uv_loop_s* %17, i32 0, i32 3, !dbg !1056
  %arrayidx16 = getelementptr inbounds [2 x i8*], [2 x i8*]* %active_reqs15, i64 0, i64 1, !dbg !1056
  %18 = bitcast i8** %arrayidx16 to [2 x i8*]**, !dbg !1056
  store [2 x i8*]* %active_queue14, [2 x i8*]** %18, align 8, !dbg !1056
  br label %do.end17, !dbg !1056

do.end17:                                         ; preds = %do.body5
  br label %do.end18, !dbg !1059

do.end18:                                         ; preds = %do.end17
  br label %do.end19, !dbg !1061

do.end19:                                         ; preds = %do.end18
  br label %if.end, !dbg !1063

if.end:                                           ; preds = %do.end19, %do.body
  %19 = load %struct.uv_fs_s*, %struct.uv_fs_s** %req.addr, align 8, !dbg !1065
  %fs_type = getelementptr inbounds %struct.uv_fs_s, %struct.uv_fs_s* %19, i32 0, i32 4, !dbg !1065
  store i32 2, i32* %fs_type, align 8, !dbg !1065
  %20 = load %struct.uv_fs_s*, %struct.uv_fs_s** %req.addr, align 8, !dbg !1065
  %result = getelementptr inbounds %struct.uv_fs_s, %struct.uv_fs_s* %20, i32 0, i32 7, !dbg !1065
  store i64 0, i64* %result, align 8, !dbg !1065
  %21 = load %struct.uv_fs_s*, %struct.uv_fs_s** %req.addr, align 8, !dbg !1065
  %ptr = getelementptr inbounds %struct.uv_fs_s, %struct.uv_fs_s* %21, i32 0, i32 8, !dbg !1065
  store i8* null, i8** %ptr, align 8, !dbg !1065
  %22 = load %struct.uv_loop_s*, %struct.uv_loop_s** %loop.addr, align 8, !dbg !1065
  %23 = load %struct.uv_fs_s*, %struct.uv_fs_s** %req.addr, align 8, !dbg !1065
  %loop20 = getelementptr inbounds %struct.uv_fs_s, %struct.uv_fs_s* %23, i32 0, i32 5, !dbg !1065
  store %struct.uv_loop_s* %22, %struct.uv_loop_s** %loop20, align 8, !dbg !1065
  %24 = load %struct.uv_fs_s*, %struct.uv_fs_s** %req.addr, align 8, !dbg !1065
  %path = getelementptr inbounds %struct.uv_fs_s, %struct.uv_fs_s* %24, i32 0, i32 9, !dbg !1065
  store i8* null, i8** %path, align 8, !dbg !1065
  %25 = load %struct.uv_fs_s*, %struct.uv_fs_s** %req.addr, align 8, !dbg !1065
  %new_path = getelementptr inbounds %struct.uv_fs_s, %struct.uv_fs_s* %25, i32 0, i32 11, !dbg !1065
  store i8* null, i8** %new_path, align 8, !dbg !1065
  %26 = load void (%struct.uv_fs_s*)*, void (%struct.uv_fs_s*)** %cb.addr, align 8, !dbg !1065
  %27 = load %struct.uv_fs_s*, %struct.uv_fs_s** %req.addr, align 8, !dbg !1065
  %cb21 = getelementptr inbounds %struct.uv_fs_s, %struct.uv_fs_s* %27, i32 0, i32 6, !dbg !1065
  store void (%struct.uv_fs_s*)* %26, void (%struct.uv_fs_s*)** %cb21, align 8, !dbg !1065
  br label %do.end22, !dbg !1065

do.end22:                                         ; preds = %if.end
  %28 = load i32, i32* %file.addr, align 4, !dbg !1067
  %29 = load %struct.uv_fs_s*, %struct.uv_fs_s** %req.addr, align 8, !dbg !1068
  %file23 = getelementptr inbounds %struct.uv_fs_s, %struct.uv_fs_s* %29, i32 0, i32 12, !dbg !1069
  store i32 %28, i32* %file23, align 8, !dbg !1070
  br label %do.body24, !dbg !1071

do.body24:                                        ; preds = %do.end22
  %30 = load void (%struct.uv_fs_s*)*, void (%struct.uv_fs_s*)** %cb.addr, align 8, !dbg !1072
  %cmp25 = icmp ne void (%struct.uv_fs_s*)* %30, null, !dbg !1072
  br i1 %cmp25, label %if.then26, label %if.else, !dbg !1072

if.then26:                                        ; preds = %do.body24
  %31 = load %struct.uv_loop_s*, %struct.uv_loop_s** %loop.addr, align 8, !dbg !1076
  %32 = load %struct.uv_fs_s*, %struct.uv_fs_s** %req.addr, align 8, !dbg !1076
  %work_req = getelementptr inbounds %struct.uv_fs_s, %struct.uv_fs_s* %32, i32 0, i32 22, !dbg !1076
  call void @uv__work_submit(%struct.uv_loop_s* %31, %struct.uv__work* %work_req, void (%struct.uv__work*)* @uv__fs_work, void (%struct.uv__work*, i32)* @uv__fs_done), !dbg !1076
  store i32 0, i32* %retval, align 4, !dbg !1076
  br label %do.end29, !dbg !1076

if.else:                                          ; preds = %do.body24
  %33 = load %struct.uv_fs_s*, %struct.uv_fs_s** %req.addr, align 8, !dbg !1079
  %work_req27 = getelementptr inbounds %struct.uv_fs_s, %struct.uv_fs_s* %33, i32 0, i32 22, !dbg !1079
  call void @uv__fs_work(%struct.uv__work* %work_req27), !dbg !1079
  %34 = load %struct.uv_fs_s*, %struct.uv_fs_s** %req.addr, align 8, !dbg !1079
  %result28 = getelementptr inbounds %struct.uv_fs_s, %struct.uv_fs_s* %34, i32 0, i32 7, !dbg !1079
  %35 = load i64, i64* %result28, align 8, !dbg !1079
  %conv = trunc i64 %35 to i32, !dbg !1079
  store i32 %conv, i32* %retval, align 4, !dbg !1079
  br label %do.end29, !dbg !1079

do.end29:                                         ; preds = %if.then26, %if.else
  %36 = load i32, i32* %retval, align 4, !dbg !1082
  ret i32 %36, !dbg !1082
}

; Function Attrs: nounwind uwtable
define i32 @uv_fs_fchmod(%struct.uv_loop_s* %loop, %struct.uv_fs_s* %req, i32 %file, i32 %mode, void (%struct.uv_fs_s*)* %cb) #0 !dbg !426 {
entry:
  %retval = alloca i32, align 4
  %loop.addr = alloca %struct.uv_loop_s*, align 8
  %req.addr = alloca %struct.uv_fs_s*, align 8
  %file.addr = alloca i32, align 4
  %mode.addr = alloca i32, align 4
  %cb.addr = alloca void (%struct.uv_fs_s*)*, align 8
  store %struct.uv_loop_s* %loop, %struct.uv_loop_s** %loop.addr, align 8
  call void @llvm.dbg.declare(metadata %struct.uv_loop_s** %loop.addr, metadata !1083, metadata !580), !dbg !1084
  store %struct.uv_fs_s* %req, %struct.uv_fs_s** %req.addr, align 8
  call void @llvm.dbg.declare(metadata %struct.uv_fs_s** %req.addr, metadata !1085, metadata !580), !dbg !1086
  store i32 %file, i32* %file.addr, align 4
  call void @llvm.dbg.declare(metadata i32* %file.addr, metadata !1087, metadata !580), !dbg !1088
  store i32 %mode, i32* %mode.addr, align 4
  call void @llvm.dbg.declare(metadata i32* %mode.addr, metadata !1089, metadata !580), !dbg !1090
  store void (%struct.uv_fs_s*)* %cb, void (%struct.uv_fs_s*)** %cb.addr, align 8
  call void @llvm.dbg.declare(metadata void (%struct.uv_fs_s*)** %cb.addr, metadata !1091, metadata !580), !dbg !1092
  br label %do.body, !dbg !1093

do.body:                                          ; preds = %entry
  %0 = load %struct.uv_fs_s*, %struct.uv_fs_s** %req.addr, align 8, !dbg !1094
  %type = getelementptr inbounds %struct.uv_fs_s, %struct.uv_fs_s* %0, i32 0, i32 1, !dbg !1094
  store i32 6, i32* %type, align 8, !dbg !1094
  %1 = load void (%struct.uv_fs_s*)*, void (%struct.uv_fs_s*)** %cb.addr, align 8, !dbg !1094
  %cmp = icmp ne void (%struct.uv_fs_s*)* %1, null, !dbg !1094
  br i1 %cmp, label %if.then, label %if.end, !dbg !1094

if.then:                                          ; preds = %do.body
  br label %do.body1, !dbg !1097

do.body1:                                         ; preds = %if.then
  br label %do.body2, !dbg !1100

do.body2:                                         ; preds = %do.body1
  %2 = load %struct.uv_fs_s*, %struct.uv_fs_s** %req.addr, align 8, !dbg !1103
  %type3 = getelementptr inbounds %struct.uv_fs_s, %struct.uv_fs_s* %2, i32 0, i32 1, !dbg !1103
  store i32 6, i32* %type3, align 8, !dbg !1103
  br label %do.end, !dbg !1103

do.end:                                           ; preds = %do.body2
  br label %do.body4, !dbg !1106

do.body4:                                         ; preds = %do.end
  br label %do.body5, !dbg !1108

do.body5:                                         ; preds = %do.body4
  %3 = load %struct.uv_loop_s*, %struct.uv_loop_s** %loop.addr, align 8, !dbg !1111
  %active_reqs = getelementptr inbounds %struct.uv_loop_s, %struct.uv_loop_s* %3, i32 0, i32 3, !dbg !1111
  %4 = load %struct.uv_fs_s*, %struct.uv_fs_s** %req.addr, align 8, !dbg !1111
  %active_queue = getelementptr inbounds %struct.uv_fs_s, %struct.uv_fs_s* %4, i32 0, i32 2, !dbg !1111
  %arrayidx = getelementptr inbounds [2 x i8*], [2 x i8*]* %active_queue, i64 0, i64 0, !dbg !1111
  %5 = bitcast i8** %arrayidx to [2 x i8*]**, !dbg !1111
  store [2 x i8*]* %active_reqs, [2 x i8*]** %5, align 8, !dbg !1111
  %6 = load %struct.uv_loop_s*, %struct.uv_loop_s** %loop.addr, align 8, !dbg !1111
  %active_reqs6 = getelementptr inbounds %struct.uv_loop_s, %struct.uv_loop_s* %6, i32 0, i32 3, !dbg !1111
  %arrayidx7 = getelementptr inbounds [2 x i8*], [2 x i8*]* %active_reqs6, i64 0, i64 1, !dbg !1111
  %7 = bitcast i8** %arrayidx7 to [2 x i8*]**, !dbg !1111
  %8 = load [2 x i8*]*, [2 x i8*]** %7, align 8, !dbg !1111
  %9 = load %struct.uv_fs_s*, %struct.uv_fs_s** %req.addr, align 8, !dbg !1111
  %active_queue8 = getelementptr inbounds %struct.uv_fs_s, %struct.uv_fs_s* %9, i32 0, i32 2, !dbg !1111
  %arrayidx9 = getelementptr inbounds [2 x i8*], [2 x i8*]* %active_queue8, i64 0, i64 1, !dbg !1111
  %10 = bitcast i8** %arrayidx9 to [2 x i8*]**, !dbg !1111
  store [2 x i8*]* %8, [2 x i8*]** %10, align 8, !dbg !1111
  %11 = load %struct.uv_fs_s*, %struct.uv_fs_s** %req.addr, align 8, !dbg !1111
  %active_queue10 = getelementptr inbounds %struct.uv_fs_s, %struct.uv_fs_s* %11, i32 0, i32 2, !dbg !1111
  %12 = load %struct.uv_fs_s*, %struct.uv_fs_s** %req.addr, align 8, !dbg !1111
  %active_queue11 = getelementptr inbounds %struct.uv_fs_s, %struct.uv_fs_s* %12, i32 0, i32 2, !dbg !1111
  %arrayidx12 = getelementptr inbounds [2 x i8*], [2 x i8*]* %active_queue11, i64 0, i64 1, !dbg !1111
  %13 = bitcast i8** %arrayidx12 to [2 x i8*]**, !dbg !1111
  %14 = load [2 x i8*]*, [2 x i8*]** %13, align 8, !dbg !1111
  %arrayidx13 = getelementptr inbounds [2 x i8*], [2 x i8*]* %14, i64 0, i64 0, !dbg !1111
  %15 = bitcast i8** %arrayidx13 to [2 x i8*]**, !dbg !1111
  store [2 x i8*]* %active_queue10, [2 x i8*]** %15, align 8, !dbg !1111
  %16 = load %struct.uv_fs_s*, %struct.uv_fs_s** %req.addr, align 8, !dbg !1111
  %active_queue14 = getelementptr inbounds %struct.uv_fs_s, %struct.uv_fs_s* %16, i32 0, i32 2, !dbg !1111
  %17 = load %struct.uv_loop_s*, %struct.uv_loop_s** %loop.addr, align 8, !dbg !1111
  %active_reqs15 = getelementptr inbounds %struct.uv_loop_s, %struct.uv_loop_s* %17, i32 0, i32 3, !dbg !1111
  %arrayidx16 = getelementptr inbounds [2 x i8*], [2 x i8*]* %active_reqs15, i64 0, i64 1, !dbg !1111
  %18 = bitcast i8** %arrayidx16 to [2 x i8*]**, !dbg !1111
  store [2 x i8*]* %active_queue14, [2 x i8*]** %18, align 8, !dbg !1111
  br label %do.end17, !dbg !1111

do.end17:                                         ; preds = %do.body5
  br label %do.end18, !dbg !1114

do.end18:                                         ; preds = %do.end17
  br label %do.end19, !dbg !1116

do.end19:                                         ; preds = %do.end18
  br label %if.end, !dbg !1118

if.end:                                           ; preds = %do.end19, %do.body
  %19 = load %struct.uv_fs_s*, %struct.uv_fs_s** %req.addr, align 8, !dbg !1120
  %fs_type = getelementptr inbounds %struct.uv_fs_s, %struct.uv_fs_s* %19, i32 0, i32 4, !dbg !1120
  store i32 14, i32* %fs_type, align 8, !dbg !1120
  %20 = load %struct.uv_fs_s*, %struct.uv_fs_s** %req.addr, align 8, !dbg !1120
  %result = getelementptr inbounds %struct.uv_fs_s, %struct.uv_fs_s* %20, i32 0, i32 7, !dbg !1120
  store i64 0, i64* %result, align 8, !dbg !1120
  %21 = load %struct.uv_fs_s*, %struct.uv_fs_s** %req.addr, align 8, !dbg !1120
  %ptr = getelementptr inbounds %struct.uv_fs_s, %struct.uv_fs_s* %21, i32 0, i32 8, !dbg !1120
  store i8* null, i8** %ptr, align 8, !dbg !1120
  %22 = load %struct.uv_loop_s*, %struct.uv_loop_s** %loop.addr, align 8, !dbg !1120
  %23 = load %struct.uv_fs_s*, %struct.uv_fs_s** %req.addr, align 8, !dbg !1120
  %loop20 = getelementptr inbounds %struct.uv_fs_s, %struct.uv_fs_s* %23, i32 0, i32 5, !dbg !1120
  store %struct.uv_loop_s* %22, %struct.uv_loop_s** %loop20, align 8, !dbg !1120
  %24 = load %struct.uv_fs_s*, %struct.uv_fs_s** %req.addr, align 8, !dbg !1120
  %path = getelementptr inbounds %struct.uv_fs_s, %struct.uv_fs_s* %24, i32 0, i32 9, !dbg !1120
  store i8* null, i8** %path, align 8, !dbg !1120
  %25 = load %struct.uv_fs_s*, %struct.uv_fs_s** %req.addr, align 8, !dbg !1120
  %new_path = getelementptr inbounds %struct.uv_fs_s, %struct.uv_fs_s* %25, i32 0, i32 11, !dbg !1120
  store i8* null, i8** %new_path, align 8, !dbg !1120
  %26 = load void (%struct.uv_fs_s*)*, void (%struct.uv_fs_s*)** %cb.addr, align 8, !dbg !1120
  %27 = load %struct.uv_fs_s*, %struct.uv_fs_s** %req.addr, align 8, !dbg !1120
  %cb21 = getelementptr inbounds %struct.uv_fs_s, %struct.uv_fs_s* %27, i32 0, i32 6, !dbg !1120
  store void (%struct.uv_fs_s*)* %26, void (%struct.uv_fs_s*)** %cb21, align 8, !dbg !1120
  br label %do.end22, !dbg !1120

do.end22:                                         ; preds = %if.end
  %28 = load i32, i32* %file.addr, align 4, !dbg !1122
  %29 = load %struct.uv_fs_s*, %struct.uv_fs_s** %req.addr, align 8, !dbg !1123
  %file23 = getelementptr inbounds %struct.uv_fs_s, %struct.uv_fs_s* %29, i32 0, i32 12, !dbg !1124
  store i32 %28, i32* %file23, align 8, !dbg !1125
  %30 = load i32, i32* %mode.addr, align 4, !dbg !1126
  %31 = load %struct.uv_fs_s*, %struct.uv_fs_s** %req.addr, align 8, !dbg !1127
  %mode24 = getelementptr inbounds %struct.uv_fs_s, %struct.uv_fs_s* %31, i32 0, i32 14, !dbg !1128
  store i32 %30, i32* %mode24, align 8, !dbg !1129
  br label %do.body25, !dbg !1130

do.body25:                                        ; preds = %do.end22
  %32 = load void (%struct.uv_fs_s*)*, void (%struct.uv_fs_s*)** %cb.addr, align 8, !dbg !1131
  %cmp26 = icmp ne void (%struct.uv_fs_s*)* %32, null, !dbg !1131
  br i1 %cmp26, label %if.then27, label %if.else, !dbg !1131

if.then27:                                        ; preds = %do.body25
  %33 = load %struct.uv_loop_s*, %struct.uv_loop_s** %loop.addr, align 8, !dbg !1135
  %34 = load %struct.uv_fs_s*, %struct.uv_fs_s** %req.addr, align 8, !dbg !1135
  %work_req = getelementptr inbounds %struct.uv_fs_s, %struct.uv_fs_s* %34, i32 0, i32 22, !dbg !1135
  call void @uv__work_submit(%struct.uv_loop_s* %33, %struct.uv__work* %work_req, void (%struct.uv__work*)* @uv__fs_work, void (%struct.uv__work*, i32)* @uv__fs_done), !dbg !1135
  store i32 0, i32* %retval, align 4, !dbg !1135
  br label %do.end30, !dbg !1135

if.else:                                          ; preds = %do.body25
  %35 = load %struct.uv_fs_s*, %struct.uv_fs_s** %req.addr, align 8, !dbg !1138
  %work_req28 = getelementptr inbounds %struct.uv_fs_s, %struct.uv_fs_s* %35, i32 0, i32 22, !dbg !1138
  call void @uv__fs_work(%struct.uv__work* %work_req28), !dbg !1138
  %36 = load %struct.uv_fs_s*, %struct.uv_fs_s** %req.addr, align 8, !dbg !1138
  %result29 = getelementptr inbounds %struct.uv_fs_s, %struct.uv_fs_s* %36, i32 0, i32 7, !dbg !1138
  %37 = load i64, i64* %result29, align 8, !dbg !1138
  %conv = trunc i64 %37 to i32, !dbg !1138
  store i32 %conv, i32* %retval, align 4, !dbg !1138
  br label %do.end30, !dbg !1138

do.end30:                                         ; preds = %if.then27, %if.else
  %38 = load i32, i32* %retval, align 4, !dbg !1141
  ret i32 %38, !dbg !1141
}

; Function Attrs: nounwind uwtable
define i32 @uv_fs_fchown(%struct.uv_loop_s* %loop, %struct.uv_fs_s* %req, i32 %file, i32 %uid, i32 %gid, void (%struct.uv_fs_s*)* %cb) #0 !dbg !429 {
entry:
  %retval = alloca i32, align 4
  %loop.addr = alloca %struct.uv_loop_s*, align 8
  %req.addr = alloca %struct.uv_fs_s*, align 8
  %file.addr = alloca i32, align 4
  %uid.addr = alloca i32, align 4
  %gid.addr = alloca i32, align 4
  %cb.addr = alloca void (%struct.uv_fs_s*)*, align 8
  store %struct.uv_loop_s* %loop, %struct.uv_loop_s** %loop.addr, align 8
  call void @llvm.dbg.declare(metadata %struct.uv_loop_s** %loop.addr, metadata !1142, metadata !580), !dbg !1143
  store %struct.uv_fs_s* %req, %struct.uv_fs_s** %req.addr, align 8
  call void @llvm.dbg.declare(metadata %struct.uv_fs_s** %req.addr, metadata !1144, metadata !580), !dbg !1145
  store i32 %file, i32* %file.addr, align 4
  call void @llvm.dbg.declare(metadata i32* %file.addr, metadata !1146, metadata !580), !dbg !1147
  store i32 %uid, i32* %uid.addr, align 4
  call void @llvm.dbg.declare(metadata i32* %uid.addr, metadata !1148, metadata !580), !dbg !1149
  store i32 %gid, i32* %gid.addr, align 4
  call void @llvm.dbg.declare(metadata i32* %gid.addr, metadata !1150, metadata !580), !dbg !1151
  store void (%struct.uv_fs_s*)* %cb, void (%struct.uv_fs_s*)** %cb.addr, align 8
  call void @llvm.dbg.declare(metadata void (%struct.uv_fs_s*)** %cb.addr, metadata !1152, metadata !580), !dbg !1153
  br label %do.body, !dbg !1154

do.body:                                          ; preds = %entry
  %0 = load %struct.uv_fs_s*, %struct.uv_fs_s** %req.addr, align 8, !dbg !1155
  %type = getelementptr inbounds %struct.uv_fs_s, %struct.uv_fs_s* %0, i32 0, i32 1, !dbg !1155
  store i32 6, i32* %type, align 8, !dbg !1155
  %1 = load void (%struct.uv_fs_s*)*, void (%struct.uv_fs_s*)** %cb.addr, align 8, !dbg !1155
  %cmp = icmp ne void (%struct.uv_fs_s*)* %1, null, !dbg !1155
  br i1 %cmp, label %if.then, label %if.end, !dbg !1155

if.then:                                          ; preds = %do.body
  br label %do.body1, !dbg !1158

do.body1:                                         ; preds = %if.then
  br label %do.body2, !dbg !1161

do.body2:                                         ; preds = %do.body1
  %2 = load %struct.uv_fs_s*, %struct.uv_fs_s** %req.addr, align 8, !dbg !1164
  %type3 = getelementptr inbounds %struct.uv_fs_s, %struct.uv_fs_s* %2, i32 0, i32 1, !dbg !1164
  store i32 6, i32* %type3, align 8, !dbg !1164
  br label %do.end, !dbg !1164

do.end:                                           ; preds = %do.body2
  br label %do.body4, !dbg !1167

do.body4:                                         ; preds = %do.end
  br label %do.body5, !dbg !1169

do.body5:                                         ; preds = %do.body4
  %3 = load %struct.uv_loop_s*, %struct.uv_loop_s** %loop.addr, align 8, !dbg !1172
  %active_reqs = getelementptr inbounds %struct.uv_loop_s, %struct.uv_loop_s* %3, i32 0, i32 3, !dbg !1172
  %4 = load %struct.uv_fs_s*, %struct.uv_fs_s** %req.addr, align 8, !dbg !1172
  %active_queue = getelementptr inbounds %struct.uv_fs_s, %struct.uv_fs_s* %4, i32 0, i32 2, !dbg !1172
  %arrayidx = getelementptr inbounds [2 x i8*], [2 x i8*]* %active_queue, i64 0, i64 0, !dbg !1172
  %5 = bitcast i8** %arrayidx to [2 x i8*]**, !dbg !1172
  store [2 x i8*]* %active_reqs, [2 x i8*]** %5, align 8, !dbg !1172
  %6 = load %struct.uv_loop_s*, %struct.uv_loop_s** %loop.addr, align 8, !dbg !1172
  %active_reqs6 = getelementptr inbounds %struct.uv_loop_s, %struct.uv_loop_s* %6, i32 0, i32 3, !dbg !1172
  %arrayidx7 = getelementptr inbounds [2 x i8*], [2 x i8*]* %active_reqs6, i64 0, i64 1, !dbg !1172
  %7 = bitcast i8** %arrayidx7 to [2 x i8*]**, !dbg !1172
  %8 = load [2 x i8*]*, [2 x i8*]** %7, align 8, !dbg !1172
  %9 = load %struct.uv_fs_s*, %struct.uv_fs_s** %req.addr, align 8, !dbg !1172
  %active_queue8 = getelementptr inbounds %struct.uv_fs_s, %struct.uv_fs_s* %9, i32 0, i32 2, !dbg !1172
  %arrayidx9 = getelementptr inbounds [2 x i8*], [2 x i8*]* %active_queue8, i64 0, i64 1, !dbg !1172
  %10 = bitcast i8** %arrayidx9 to [2 x i8*]**, !dbg !1172
  store [2 x i8*]* %8, [2 x i8*]** %10, align 8, !dbg !1172
  %11 = load %struct.uv_fs_s*, %struct.uv_fs_s** %req.addr, align 8, !dbg !1172
  %active_queue10 = getelementptr inbounds %struct.uv_fs_s, %struct.uv_fs_s* %11, i32 0, i32 2, !dbg !1172
  %12 = load %struct.uv_fs_s*, %struct.uv_fs_s** %req.addr, align 8, !dbg !1172
  %active_queue11 = getelementptr inbounds %struct.uv_fs_s, %struct.uv_fs_s* %12, i32 0, i32 2, !dbg !1172
  %arrayidx12 = getelementptr inbounds [2 x i8*], [2 x i8*]* %active_queue11, i64 0, i64 1, !dbg !1172
  %13 = bitcast i8** %arrayidx12 to [2 x i8*]**, !dbg !1172
  %14 = load [2 x i8*]*, [2 x i8*]** %13, align 8, !dbg !1172
  %arrayidx13 = getelementptr inbounds [2 x i8*], [2 x i8*]* %14, i64 0, i64 0, !dbg !1172
  %15 = bitcast i8** %arrayidx13 to [2 x i8*]**, !dbg !1172
  store [2 x i8*]* %active_queue10, [2 x i8*]** %15, align 8, !dbg !1172
  %16 = load %struct.uv_fs_s*, %struct.uv_fs_s** %req.addr, align 8, !dbg !1172
  %active_queue14 = getelementptr inbounds %struct.uv_fs_s, %struct.uv_fs_s* %16, i32 0, i32 2, !dbg !1172
  %17 = load %struct.uv_loop_s*, %struct.uv_loop_s** %loop.addr, align 8, !dbg !1172
  %active_reqs15 = getelementptr inbounds %struct.uv_loop_s, %struct.uv_loop_s* %17, i32 0, i32 3, !dbg !1172
  %arrayidx16 = getelementptr inbounds [2 x i8*], [2 x i8*]* %active_reqs15, i64 0, i64 1, !dbg !1172
  %18 = bitcast i8** %arrayidx16 to [2 x i8*]**, !dbg !1172
  store [2 x i8*]* %active_queue14, [2 x i8*]** %18, align 8, !dbg !1172
  br label %do.end17, !dbg !1172

do.end17:                                         ; preds = %do.body5
  br label %do.end18, !dbg !1175

do.end18:                                         ; preds = %do.end17
  br label %do.end19, !dbg !1177

do.end19:                                         ; preds = %do.end18
  br label %if.end, !dbg !1179

if.end:                                           ; preds = %do.end19, %do.body
  %19 = load %struct.uv_fs_s*, %struct.uv_fs_s** %req.addr, align 8, !dbg !1181
  %fs_type = getelementptr inbounds %struct.uv_fs_s, %struct.uv_fs_s* %19, i32 0, i32 4, !dbg !1181
  store i32 27, i32* %fs_type, align 8, !dbg !1181
  %20 = load %struct.uv_fs_s*, %struct.uv_fs_s** %req.addr, align 8, !dbg !1181
  %result = getelementptr inbounds %struct.uv_fs_s, %struct.uv_fs_s* %20, i32 0, i32 7, !dbg !1181
  store i64 0, i64* %result, align 8, !dbg !1181
  %21 = load %struct.uv_fs_s*, %struct.uv_fs_s** %req.addr, align 8, !dbg !1181
  %ptr = getelementptr inbounds %struct.uv_fs_s, %struct.uv_fs_s* %21, i32 0, i32 8, !dbg !1181
  store i8* null, i8** %ptr, align 8, !dbg !1181
  %22 = load %struct.uv_loop_s*, %struct.uv_loop_s** %loop.addr, align 8, !dbg !1181
  %23 = load %struct.uv_fs_s*, %struct.uv_fs_s** %req.addr, align 8, !dbg !1181
  %loop20 = getelementptr inbounds %struct.uv_fs_s, %struct.uv_fs_s* %23, i32 0, i32 5, !dbg !1181
  store %struct.uv_loop_s* %22, %struct.uv_loop_s** %loop20, align 8, !dbg !1181
  %24 = load %struct.uv_fs_s*, %struct.uv_fs_s** %req.addr, align 8, !dbg !1181
  %path = getelementptr inbounds %struct.uv_fs_s, %struct.uv_fs_s* %24, i32 0, i32 9, !dbg !1181
  store i8* null, i8** %path, align 8, !dbg !1181
  %25 = load %struct.uv_fs_s*, %struct.uv_fs_s** %req.addr, align 8, !dbg !1181
  %new_path = getelementptr inbounds %struct.uv_fs_s, %struct.uv_fs_s* %25, i32 0, i32 11, !dbg !1181
  store i8* null, i8** %new_path, align 8, !dbg !1181
  %26 = load void (%struct.uv_fs_s*)*, void (%struct.uv_fs_s*)** %cb.addr, align 8, !dbg !1181
  %27 = load %struct.uv_fs_s*, %struct.uv_fs_s** %req.addr, align 8, !dbg !1181
  %cb21 = getelementptr inbounds %struct.uv_fs_s, %struct.uv_fs_s* %27, i32 0, i32 6, !dbg !1181
  store void (%struct.uv_fs_s*)* %26, void (%struct.uv_fs_s*)** %cb21, align 8, !dbg !1181
  br label %do.end22, !dbg !1181

do.end22:                                         ; preds = %if.end
  %28 = load i32, i32* %file.addr, align 4, !dbg !1183
  %29 = load %struct.uv_fs_s*, %struct.uv_fs_s** %req.addr, align 8, !dbg !1184
  %file23 = getelementptr inbounds %struct.uv_fs_s, %struct.uv_fs_s* %29, i32 0, i32 12, !dbg !1185
  store i32 %28, i32* %file23, align 8, !dbg !1186
  %30 = load i32, i32* %uid.addr, align 4, !dbg !1187
  %31 = load %struct.uv_fs_s*, %struct.uv_fs_s** %req.addr, align 8, !dbg !1188
  %uid24 = getelementptr inbounds %struct.uv_fs_s, %struct.uv_fs_s* %31, i32 0, i32 18, !dbg !1189
  store i32 %30, i32* %uid24, align 8, !dbg !1190
  %32 = load i32, i32* %gid.addr, align 4, !dbg !1191
  %33 = load %struct.uv_fs_s*, %struct.uv_fs_s** %req.addr, align 8, !dbg !1192
  %gid25 = getelementptr inbounds %struct.uv_fs_s, %struct.uv_fs_s* %33, i32 0, i32 19, !dbg !1193
  store i32 %32, i32* %gid25, align 4, !dbg !1194
  br label %do.body26, !dbg !1195

do.body26:                                        ; preds = %do.end22
  %34 = load void (%struct.uv_fs_s*)*, void (%struct.uv_fs_s*)** %cb.addr, align 8, !dbg !1196
  %cmp27 = icmp ne void (%struct.uv_fs_s*)* %34, null, !dbg !1196
  br i1 %cmp27, label %if.then28, label %if.else, !dbg !1196

if.then28:                                        ; preds = %do.body26
  %35 = load %struct.uv_loop_s*, %struct.uv_loop_s** %loop.addr, align 8, !dbg !1200
  %36 = load %struct.uv_fs_s*, %struct.uv_fs_s** %req.addr, align 8, !dbg !1200
  %work_req = getelementptr inbounds %struct.uv_fs_s, %struct.uv_fs_s* %36, i32 0, i32 22, !dbg !1200
  call void @uv__work_submit(%struct.uv_loop_s* %35, %struct.uv__work* %work_req, void (%struct.uv__work*)* @uv__fs_work, void (%struct.uv__work*, i32)* @uv__fs_done), !dbg !1200
  store i32 0, i32* %retval, align 4, !dbg !1200
  br label %do.end31, !dbg !1200

if.else:                                          ; preds = %do.body26
  %37 = load %struct.uv_fs_s*, %struct.uv_fs_s** %req.addr, align 8, !dbg !1203
  %work_req29 = getelementptr inbounds %struct.uv_fs_s, %struct.uv_fs_s* %37, i32 0, i32 22, !dbg !1203
  call void @uv__fs_work(%struct.uv__work* %work_req29), !dbg !1203
  %38 = load %struct.uv_fs_s*, %struct.uv_fs_s** %req.addr, align 8, !dbg !1203
  %result30 = getelementptr inbounds %struct.uv_fs_s, %struct.uv_fs_s* %38, i32 0, i32 7, !dbg !1203
  %39 = load i64, i64* %result30, align 8, !dbg !1203
  %conv = trunc i64 %39 to i32, !dbg !1203
  store i32 %conv, i32* %retval, align 4, !dbg !1203
  br label %do.end31, !dbg !1203

do.end31:                                         ; preds = %if.then28, %if.else
  %40 = load i32, i32* %retval, align 4, !dbg !1206
  ret i32 %40, !dbg !1206
}

; Function Attrs: nounwind uwtable
define i32 @uv_fs_fdatasync(%struct.uv_loop_s* %loop, %struct.uv_fs_s* %req, i32 %file, void (%struct.uv_fs_s*)* %cb) #0 !dbg !432 {
entry:
  %retval = alloca i32, align 4
  %loop.addr = alloca %struct.uv_loop_s*, align 8
  %req.addr = alloca %struct.uv_fs_s*, align 8
  %file.addr = alloca i32, align 4
  %cb.addr = alloca void (%struct.uv_fs_s*)*, align 8
  store %struct.uv_loop_s* %loop, %struct.uv_loop_s** %loop.addr, align 8
  call void @llvm.dbg.declare(metadata %struct.uv_loop_s** %loop.addr, metadata !1207, metadata !580), !dbg !1208
  store %struct.uv_fs_s* %req, %struct.uv_fs_s** %req.addr, align 8
  call void @llvm.dbg.declare(metadata %struct.uv_fs_s** %req.addr, metadata !1209, metadata !580), !dbg !1210
  store i32 %file, i32* %file.addr, align 4
  call void @llvm.dbg.declare(metadata i32* %file.addr, metadata !1211, metadata !580), !dbg !1212
  store void (%struct.uv_fs_s*)* %cb, void (%struct.uv_fs_s*)** %cb.addr, align 8
  call void @llvm.dbg.declare(metadata void (%struct.uv_fs_s*)** %cb.addr, metadata !1213, metadata !580), !dbg !1214
  br label %do.body, !dbg !1215

do.body:                                          ; preds = %entry
  %0 = load %struct.uv_fs_s*, %struct.uv_fs_s** %req.addr, align 8, !dbg !1216
  %type = getelementptr inbounds %struct.uv_fs_s, %struct.uv_fs_s* %0, i32 0, i32 1, !dbg !1216
  store i32 6, i32* %type, align 8, !dbg !1216
  %1 = load void (%struct.uv_fs_s*)*, void (%struct.uv_fs_s*)** %cb.addr, align 8, !dbg !1216
  %cmp = icmp ne void (%struct.uv_fs_s*)* %1, null, !dbg !1216
  br i1 %cmp, label %if.then, label %if.end, !dbg !1216

if.then:                                          ; preds = %do.body
  br label %do.body1, !dbg !1219

do.body1:                                         ; preds = %if.then
  br label %do.body2, !dbg !1222

do.body2:                                         ; preds = %do.body1
  %2 = load %struct.uv_fs_s*, %struct.uv_fs_s** %req.addr, align 8, !dbg !1225
  %type3 = getelementptr inbounds %struct.uv_fs_s, %struct.uv_fs_s* %2, i32 0, i32 1, !dbg !1225
  store i32 6, i32* %type3, align 8, !dbg !1225
  br label %do.end, !dbg !1225

do.end:                                           ; preds = %do.body2
  br label %do.body4, !dbg !1228

do.body4:                                         ; preds = %do.end
  br label %do.body5, !dbg !1230

do.body5:                                         ; preds = %do.body4
  %3 = load %struct.uv_loop_s*, %struct.uv_loop_s** %loop.addr, align 8, !dbg !1233
  %active_reqs = getelementptr inbounds %struct.uv_loop_s, %struct.uv_loop_s* %3, i32 0, i32 3, !dbg !1233
  %4 = load %struct.uv_fs_s*, %struct.uv_fs_s** %req.addr, align 8, !dbg !1233
  %active_queue = getelementptr inbounds %struct.uv_fs_s, %struct.uv_fs_s* %4, i32 0, i32 2, !dbg !1233
  %arrayidx = getelementptr inbounds [2 x i8*], [2 x i8*]* %active_queue, i64 0, i64 0, !dbg !1233
  %5 = bitcast i8** %arrayidx to [2 x i8*]**, !dbg !1233
  store [2 x i8*]* %active_reqs, [2 x i8*]** %5, align 8, !dbg !1233
  %6 = load %struct.uv_loop_s*, %struct.uv_loop_s** %loop.addr, align 8, !dbg !1233
  %active_reqs6 = getelementptr inbounds %struct.uv_loop_s, %struct.uv_loop_s* %6, i32 0, i32 3, !dbg !1233
  %arrayidx7 = getelementptr inbounds [2 x i8*], [2 x i8*]* %active_reqs6, i64 0, i64 1, !dbg !1233
  %7 = bitcast i8** %arrayidx7 to [2 x i8*]**, !dbg !1233
  %8 = load [2 x i8*]*, [2 x i8*]** %7, align 8, !dbg !1233
  %9 = load %struct.uv_fs_s*, %struct.uv_fs_s** %req.addr, align 8, !dbg !1233
  %active_queue8 = getelementptr inbounds %struct.uv_fs_s, %struct.uv_fs_s* %9, i32 0, i32 2, !dbg !1233
  %arrayidx9 = getelementptr inbounds [2 x i8*], [2 x i8*]* %active_queue8, i64 0, i64 1, !dbg !1233
  %10 = bitcast i8** %arrayidx9 to [2 x i8*]**, !dbg !1233
  store [2 x i8*]* %8, [2 x i8*]** %10, align 8, !dbg !1233
  %11 = load %struct.uv_fs_s*, %struct.uv_fs_s** %req.addr, align 8, !dbg !1233
  %active_queue10 = getelementptr inbounds %struct.uv_fs_s, %struct.uv_fs_s* %11, i32 0, i32 2, !dbg !1233
  %12 = load %struct.uv_fs_s*, %struct.uv_fs_s** %req.addr, align 8, !dbg !1233
  %active_queue11 = getelementptr inbounds %struct.uv_fs_s, %struct.uv_fs_s* %12, i32 0, i32 2, !dbg !1233
  %arrayidx12 = getelementptr inbounds [2 x i8*], [2 x i8*]* %active_queue11, i64 0, i64 1, !dbg !1233
  %13 = bitcast i8** %arrayidx12 to [2 x i8*]**, !dbg !1233
  %14 = load [2 x i8*]*, [2 x i8*]** %13, align 8, !dbg !1233
  %arrayidx13 = getelementptr inbounds [2 x i8*], [2 x i8*]* %14, i64 0, i64 0, !dbg !1233
  %15 = bitcast i8** %arrayidx13 to [2 x i8*]**, !dbg !1233
  store [2 x i8*]* %active_queue10, [2 x i8*]** %15, align 8, !dbg !1233
  %16 = load %struct.uv_fs_s*, %struct.uv_fs_s** %req.addr, align 8, !dbg !1233
  %active_queue14 = getelementptr inbounds %struct.uv_fs_s, %struct.uv_fs_s* %16, i32 0, i32 2, !dbg !1233
  %17 = load %struct.uv_loop_s*, %struct.uv_loop_s** %loop.addr, align 8, !dbg !1233
  %active_reqs15 = getelementptr inbounds %struct.uv_loop_s, %struct.uv_loop_s* %17, i32 0, i32 3, !dbg !1233
  %arrayidx16 = getelementptr inbounds [2 x i8*], [2 x i8*]* %active_reqs15, i64 0, i64 1, !dbg !1233
  %18 = bitcast i8** %arrayidx16 to [2 x i8*]**, !dbg !1233
  store [2 x i8*]* %active_queue14, [2 x i8*]** %18, align 8, !dbg !1233
  br label %do.end17, !dbg !1233

do.end17:                                         ; preds = %do.body5
  br label %do.end18, !dbg !1236

do.end18:                                         ; preds = %do.end17
  br label %do.end19, !dbg !1238

do.end19:                                         ; preds = %do.end18
  br label %if.end, !dbg !1240

if.end:                                           ; preds = %do.end19, %do.body
  %19 = load %struct.uv_fs_s*, %struct.uv_fs_s** %req.addr, align 8, !dbg !1242
  %fs_type = getelementptr inbounds %struct.uv_fs_s, %struct.uv_fs_s* %19, i32 0, i32 4, !dbg !1242
  store i32 16, i32* %fs_type, align 8, !dbg !1242
  %20 = load %struct.uv_fs_s*, %struct.uv_fs_s** %req.addr, align 8, !dbg !1242
  %result = getelementptr inbounds %struct.uv_fs_s, %struct.uv_fs_s* %20, i32 0, i32 7, !dbg !1242
  store i64 0, i64* %result, align 8, !dbg !1242
  %21 = load %struct.uv_fs_s*, %struct.uv_fs_s** %req.addr, align 8, !dbg !1242
  %ptr = getelementptr inbounds %struct.uv_fs_s, %struct.uv_fs_s* %21, i32 0, i32 8, !dbg !1242
  store i8* null, i8** %ptr, align 8, !dbg !1242
  %22 = load %struct.uv_loop_s*, %struct.uv_loop_s** %loop.addr, align 8, !dbg !1242
  %23 = load %struct.uv_fs_s*, %struct.uv_fs_s** %req.addr, align 8, !dbg !1242
  %loop20 = getelementptr inbounds %struct.uv_fs_s, %struct.uv_fs_s* %23, i32 0, i32 5, !dbg !1242
  store %struct.uv_loop_s* %22, %struct.uv_loop_s** %loop20, align 8, !dbg !1242
  %24 = load %struct.uv_fs_s*, %struct.uv_fs_s** %req.addr, align 8, !dbg !1242
  %path = getelementptr inbounds %struct.uv_fs_s, %struct.uv_fs_s* %24, i32 0, i32 9, !dbg !1242
  store i8* null, i8** %path, align 8, !dbg !1242
  %25 = load %struct.uv_fs_s*, %struct.uv_fs_s** %req.addr, align 8, !dbg !1242
  %new_path = getelementptr inbounds %struct.uv_fs_s, %struct.uv_fs_s* %25, i32 0, i32 11, !dbg !1242
  store i8* null, i8** %new_path, align 8, !dbg !1242
  %26 = load void (%struct.uv_fs_s*)*, void (%struct.uv_fs_s*)** %cb.addr, align 8, !dbg !1242
  %27 = load %struct.uv_fs_s*, %struct.uv_fs_s** %req.addr, align 8, !dbg !1242
  %cb21 = getelementptr inbounds %struct.uv_fs_s, %struct.uv_fs_s* %27, i32 0, i32 6, !dbg !1242
  store void (%struct.uv_fs_s*)* %26, void (%struct.uv_fs_s*)** %cb21, align 8, !dbg !1242
  br label %do.end22, !dbg !1242

do.end22:                                         ; preds = %if.end
  %28 = load i32, i32* %file.addr, align 4, !dbg !1244
  %29 = load %struct.uv_fs_s*, %struct.uv_fs_s** %req.addr, align 8, !dbg !1245
  %file23 = getelementptr inbounds %struct.uv_fs_s, %struct.uv_fs_s* %29, i32 0, i32 12, !dbg !1246
  store i32 %28, i32* %file23, align 8, !dbg !1247
  br label %do.body24, !dbg !1248

do.body24:                                        ; preds = %do.end22
  %30 = load void (%struct.uv_fs_s*)*, void (%struct.uv_fs_s*)** %cb.addr, align 8, !dbg !1249
  %cmp25 = icmp ne void (%struct.uv_fs_s*)* %30, null, !dbg !1249
  br i1 %cmp25, label %if.then26, label %if.else, !dbg !1249

if.then26:                                        ; preds = %do.body24
  %31 = load %struct.uv_loop_s*, %struct.uv_loop_s** %loop.addr, align 8, !dbg !1253
  %32 = load %struct.uv_fs_s*, %struct.uv_fs_s** %req.addr, align 8, !dbg !1253
  %work_req = getelementptr inbounds %struct.uv_fs_s, %struct.uv_fs_s* %32, i32 0, i32 22, !dbg !1253
  call void @uv__work_submit(%struct.uv_loop_s* %31, %struct.uv__work* %work_req, void (%struct.uv__work*)* @uv__fs_work, void (%struct.uv__work*, i32)* @uv__fs_done), !dbg !1253
  store i32 0, i32* %retval, align 4, !dbg !1253
  br label %do.end29, !dbg !1253

if.else:                                          ; preds = %do.body24
  %33 = load %struct.uv_fs_s*, %struct.uv_fs_s** %req.addr, align 8, !dbg !1256
  %work_req27 = getelementptr inbounds %struct.uv_fs_s, %struct.uv_fs_s* %33, i32 0, i32 22, !dbg !1256
  call void @uv__fs_work(%struct.uv__work* %work_req27), !dbg !1256
  %34 = load %struct.uv_fs_s*, %struct.uv_fs_s** %req.addr, align 8, !dbg !1256
  %result28 = getelementptr inbounds %struct.uv_fs_s, %struct.uv_fs_s* %34, i32 0, i32 7, !dbg !1256
  %35 = load i64, i64* %result28, align 8, !dbg !1256
  %conv = trunc i64 %35 to i32, !dbg !1256
  store i32 %conv, i32* %retval, align 4, !dbg !1256
  br label %do.end29, !dbg !1256

do.end29:                                         ; preds = %if.then26, %if.else
  %36 = load i32, i32* %retval, align 4, !dbg !1259
  ret i32 %36, !dbg !1259
}

; Function Attrs: nounwind uwtable
define i32 @uv_fs_fstat(%struct.uv_loop_s* %loop, %struct.uv_fs_s* %req, i32 %file, void (%struct.uv_fs_s*)* %cb) #0 !dbg !433 {
entry:
  %retval = alloca i32, align 4
  %loop.addr = alloca %struct.uv_loop_s*, align 8
  %req.addr = alloca %struct.uv_fs_s*, align 8
  %file.addr = alloca i32, align 4
  %cb.addr = alloca void (%struct.uv_fs_s*)*, align 8
  store %struct.uv_loop_s* %loop, %struct.uv_loop_s** %loop.addr, align 8
  call void @llvm.dbg.declare(metadata %struct.uv_loop_s** %loop.addr, metadata !1260, metadata !580), !dbg !1261
  store %struct.uv_fs_s* %req, %struct.uv_fs_s** %req.addr, align 8
  call void @llvm.dbg.declare(metadata %struct.uv_fs_s** %req.addr, metadata !1262, metadata !580), !dbg !1263
  store i32 %file, i32* %file.addr, align 4
  call void @llvm.dbg.declare(metadata i32* %file.addr, metadata !1264, metadata !580), !dbg !1265
  store void (%struct.uv_fs_s*)* %cb, void (%struct.uv_fs_s*)** %cb.addr, align 8
  call void @llvm.dbg.declare(metadata void (%struct.uv_fs_s*)** %cb.addr, metadata !1266, metadata !580), !dbg !1267
  br label %do.body, !dbg !1268

do.body:                                          ; preds = %entry
  %0 = load %struct.uv_fs_s*, %struct.uv_fs_s** %req.addr, align 8, !dbg !1269
  %type = getelementptr inbounds %struct.uv_fs_s, %struct.uv_fs_s* %0, i32 0, i32 1, !dbg !1269
  store i32 6, i32* %type, align 8, !dbg !1269
  %1 = load void (%struct.uv_fs_s*)*, void (%struct.uv_fs_s*)** %cb.addr, align 8, !dbg !1269
  %cmp = icmp ne void (%struct.uv_fs_s*)* %1, null, !dbg !1269
  br i1 %cmp, label %if.then, label %if.end, !dbg !1269

if.then:                                          ; preds = %do.body
  br label %do.body1, !dbg !1272

do.body1:                                         ; preds = %if.then
  br label %do.body2, !dbg !1275

do.body2:                                         ; preds = %do.body1
  %2 = load %struct.uv_fs_s*, %struct.uv_fs_s** %req.addr, align 8, !dbg !1278
  %type3 = getelementptr inbounds %struct.uv_fs_s, %struct.uv_fs_s* %2, i32 0, i32 1, !dbg !1278
  store i32 6, i32* %type3, align 8, !dbg !1278
  br label %do.end, !dbg !1278

do.end:                                           ; preds = %do.body2
  br label %do.body4, !dbg !1281

do.body4:                                         ; preds = %do.end
  br label %do.body5, !dbg !1283

do.body5:                                         ; preds = %do.body4
  %3 = load %struct.uv_loop_s*, %struct.uv_loop_s** %loop.addr, align 8, !dbg !1286
  %active_reqs = getelementptr inbounds %struct.uv_loop_s, %struct.uv_loop_s* %3, i32 0, i32 3, !dbg !1286
  %4 = load %struct.uv_fs_s*, %struct.uv_fs_s** %req.addr, align 8, !dbg !1286
  %active_queue = getelementptr inbounds %struct.uv_fs_s, %struct.uv_fs_s* %4, i32 0, i32 2, !dbg !1286
  %arrayidx = getelementptr inbounds [2 x i8*], [2 x i8*]* %active_queue, i64 0, i64 0, !dbg !1286
  %5 = bitcast i8** %arrayidx to [2 x i8*]**, !dbg !1286
  store [2 x i8*]* %active_reqs, [2 x i8*]** %5, align 8, !dbg !1286
  %6 = load %struct.uv_loop_s*, %struct.uv_loop_s** %loop.addr, align 8, !dbg !1286
  %active_reqs6 = getelementptr inbounds %struct.uv_loop_s, %struct.uv_loop_s* %6, i32 0, i32 3, !dbg !1286
  %arrayidx7 = getelementptr inbounds [2 x i8*], [2 x i8*]* %active_reqs6, i64 0, i64 1, !dbg !1286
  %7 = bitcast i8** %arrayidx7 to [2 x i8*]**, !dbg !1286
  %8 = load [2 x i8*]*, [2 x i8*]** %7, align 8, !dbg !1286
  %9 = load %struct.uv_fs_s*, %struct.uv_fs_s** %req.addr, align 8, !dbg !1286
  %active_queue8 = getelementptr inbounds %struct.uv_fs_s, %struct.uv_fs_s* %9, i32 0, i32 2, !dbg !1286
  %arrayidx9 = getelementptr inbounds [2 x i8*], [2 x i8*]* %active_queue8, i64 0, i64 1, !dbg !1286
  %10 = bitcast i8** %arrayidx9 to [2 x i8*]**, !dbg !1286
  store [2 x i8*]* %8, [2 x i8*]** %10, align 8, !dbg !1286
  %11 = load %struct.uv_fs_s*, %struct.uv_fs_s** %req.addr, align 8, !dbg !1286
  %active_queue10 = getelementptr inbounds %struct.uv_fs_s, %struct.uv_fs_s* %11, i32 0, i32 2, !dbg !1286
  %12 = load %struct.uv_fs_s*, %struct.uv_fs_s** %req.addr, align 8, !dbg !1286
  %active_queue11 = getelementptr inbounds %struct.uv_fs_s, %struct.uv_fs_s* %12, i32 0, i32 2, !dbg !1286
  %arrayidx12 = getelementptr inbounds [2 x i8*], [2 x i8*]* %active_queue11, i64 0, i64 1, !dbg !1286
  %13 = bitcast i8** %arrayidx12 to [2 x i8*]**, !dbg !1286
  %14 = load [2 x i8*]*, [2 x i8*]** %13, align 8, !dbg !1286
  %arrayidx13 = getelementptr inbounds [2 x i8*], [2 x i8*]* %14, i64 0, i64 0, !dbg !1286
  %15 = bitcast i8** %arrayidx13 to [2 x i8*]**, !dbg !1286
  store [2 x i8*]* %active_queue10, [2 x i8*]** %15, align 8, !dbg !1286
  %16 = load %struct.uv_fs_s*, %struct.uv_fs_s** %req.addr, align 8, !dbg !1286
  %active_queue14 = getelementptr inbounds %struct.uv_fs_s, %struct.uv_fs_s* %16, i32 0, i32 2, !dbg !1286
  %17 = load %struct.uv_loop_s*, %struct.uv_loop_s** %loop.addr, align 8, !dbg !1286
  %active_reqs15 = getelementptr inbounds %struct.uv_loop_s, %struct.uv_loop_s* %17, i32 0, i32 3, !dbg !1286
  %arrayidx16 = getelementptr inbounds [2 x i8*], [2 x i8*]* %active_reqs15, i64 0, i64 1, !dbg !1286
  %18 = bitcast i8** %arrayidx16 to [2 x i8*]**, !dbg !1286
  store [2 x i8*]* %active_queue14, [2 x i8*]** %18, align 8, !dbg !1286
  br label %do.end17, !dbg !1286

do.end17:                                         ; preds = %do.body5
  br label %do.end18, !dbg !1289

do.end18:                                         ; preds = %do.end17
  br label %do.end19, !dbg !1291

do.end19:                                         ; preds = %do.end18
  br label %if.end, !dbg !1293

if.end:                                           ; preds = %do.end19, %do.body
  %19 = load %struct.uv_fs_s*, %struct.uv_fs_s** %req.addr, align 8, !dbg !1295
  %fs_type = getelementptr inbounds %struct.uv_fs_s, %struct.uv_fs_s* %19, i32 0, i32 4, !dbg !1295
  store i32 8, i32* %fs_type, align 8, !dbg !1295
  %20 = load %struct.uv_fs_s*, %struct.uv_fs_s** %req.addr, align 8, !dbg !1295
  %result = getelementptr inbounds %struct.uv_fs_s, %struct.uv_fs_s* %20, i32 0, i32 7, !dbg !1295
  store i64 0, i64* %result, align 8, !dbg !1295
  %21 = load %struct.uv_fs_s*, %struct.uv_fs_s** %req.addr, align 8, !dbg !1295
  %ptr = getelementptr inbounds %struct.uv_fs_s, %struct.uv_fs_s* %21, i32 0, i32 8, !dbg !1295
  store i8* null, i8** %ptr, align 8, !dbg !1295
  %22 = load %struct.uv_loop_s*, %struct.uv_loop_s** %loop.addr, align 8, !dbg !1295
  %23 = load %struct.uv_fs_s*, %struct.uv_fs_s** %req.addr, align 8, !dbg !1295
  %loop20 = getelementptr inbounds %struct.uv_fs_s, %struct.uv_fs_s* %23, i32 0, i32 5, !dbg !1295
  store %struct.uv_loop_s* %22, %struct.uv_loop_s** %loop20, align 8, !dbg !1295
  %24 = load %struct.uv_fs_s*, %struct.uv_fs_s** %req.addr, align 8, !dbg !1295
  %path = getelementptr inbounds %struct.uv_fs_s, %struct.uv_fs_s* %24, i32 0, i32 9, !dbg !1295
  store i8* null, i8** %path, align 8, !dbg !1295
  %25 = load %struct.uv_fs_s*, %struct.uv_fs_s** %req.addr, align 8, !dbg !1295
  %new_path = getelementptr inbounds %struct.uv_fs_s, %struct.uv_fs_s* %25, i32 0, i32 11, !dbg !1295
  store i8* null, i8** %new_path, align 8, !dbg !1295
  %26 = load void (%struct.uv_fs_s*)*, void (%struct.uv_fs_s*)** %cb.addr, align 8, !dbg !1295
  %27 = load %struct.uv_fs_s*, %struct.uv_fs_s** %req.addr, align 8, !dbg !1295
  %cb21 = getelementptr inbounds %struct.uv_fs_s, %struct.uv_fs_s* %27, i32 0, i32 6, !dbg !1295
  store void (%struct.uv_fs_s*)* %26, void (%struct.uv_fs_s*)** %cb21, align 8, !dbg !1295
  br label %do.end22, !dbg !1295

do.end22:                                         ; preds = %if.end
  %28 = load i32, i32* %file.addr, align 4, !dbg !1297
  %29 = load %struct.uv_fs_s*, %struct.uv_fs_s** %req.addr, align 8, !dbg !1298
  %file23 = getelementptr inbounds %struct.uv_fs_s, %struct.uv_fs_s* %29, i32 0, i32 12, !dbg !1299
  store i32 %28, i32* %file23, align 8, !dbg !1300
  br label %do.body24, !dbg !1301

do.body24:                                        ; preds = %do.end22
  %30 = load void (%struct.uv_fs_s*)*, void (%struct.uv_fs_s*)** %cb.addr, align 8, !dbg !1302
  %cmp25 = icmp ne void (%struct.uv_fs_s*)* %30, null, !dbg !1302
  br i1 %cmp25, label %if.then26, label %if.else, !dbg !1302

if.then26:                                        ; preds = %do.body24
  %31 = load %struct.uv_loop_s*, %struct.uv_loop_s** %loop.addr, align 8, !dbg !1306
  %32 = load %struct.uv_fs_s*, %struct.uv_fs_s** %req.addr, align 8, !dbg !1306
  %work_req = getelementptr inbounds %struct.uv_fs_s, %struct.uv_fs_s* %32, i32 0, i32 22, !dbg !1306
  call void @uv__work_submit(%struct.uv_loop_s* %31, %struct.uv__work* %work_req, void (%struct.uv__work*)* @uv__fs_work, void (%struct.uv__work*, i32)* @uv__fs_done), !dbg !1306
  store i32 0, i32* %retval, align 4, !dbg !1306
  br label %do.end29, !dbg !1306

if.else:                                          ; preds = %do.body24
  %33 = load %struct.uv_fs_s*, %struct.uv_fs_s** %req.addr, align 8, !dbg !1309
  %work_req27 = getelementptr inbounds %struct.uv_fs_s, %struct.uv_fs_s* %33, i32 0, i32 22, !dbg !1309
  call void @uv__fs_work(%struct.uv__work* %work_req27), !dbg !1309
  %34 = load %struct.uv_fs_s*, %struct.uv_fs_s** %req.addr, align 8, !dbg !1309
  %result28 = getelementptr inbounds %struct.uv_fs_s, %struct.uv_fs_s* %34, i32 0, i32 7, !dbg !1309
  %35 = load i64, i64* %result28, align 8, !dbg !1309
  %conv = trunc i64 %35 to i32, !dbg !1309
  store i32 %conv, i32* %retval, align 4, !dbg !1309
  br label %do.end29, !dbg !1309

do.end29:                                         ; preds = %if.then26, %if.else
  %36 = load i32, i32* %retval, align 4, !dbg !1312
  ret i32 %36, !dbg !1312
}

; Function Attrs: nounwind uwtable
define i32 @uv_fs_fsync(%struct.uv_loop_s* %loop, %struct.uv_fs_s* %req, i32 %file, void (%struct.uv_fs_s*)* %cb) #0 !dbg !434 {
entry:
  %retval = alloca i32, align 4
  %loop.addr = alloca %struct.uv_loop_s*, align 8
  %req.addr = alloca %struct.uv_fs_s*, align 8
  %file.addr = alloca i32, align 4
  %cb.addr = alloca void (%struct.uv_fs_s*)*, align 8
  store %struct.uv_loop_s* %loop, %struct.uv_loop_s** %loop.addr, align 8
  call void @llvm.dbg.declare(metadata %struct.uv_loop_s** %loop.addr, metadata !1313, metadata !580), !dbg !1314
  store %struct.uv_fs_s* %req, %struct.uv_fs_s** %req.addr, align 8
  call void @llvm.dbg.declare(metadata %struct.uv_fs_s** %req.addr, metadata !1315, metadata !580), !dbg !1316
  store i32 %file, i32* %file.addr, align 4
  call void @llvm.dbg.declare(metadata i32* %file.addr, metadata !1317, metadata !580), !dbg !1318
  store void (%struct.uv_fs_s*)* %cb, void (%struct.uv_fs_s*)** %cb.addr, align 8
  call void @llvm.dbg.declare(metadata void (%struct.uv_fs_s*)** %cb.addr, metadata !1319, metadata !580), !dbg !1320
  br label %do.body, !dbg !1321

do.body:                                          ; preds = %entry
  %0 = load %struct.uv_fs_s*, %struct.uv_fs_s** %req.addr, align 8, !dbg !1322
  %type = getelementptr inbounds %struct.uv_fs_s, %struct.uv_fs_s* %0, i32 0, i32 1, !dbg !1322
  store i32 6, i32* %type, align 8, !dbg !1322
  %1 = load void (%struct.uv_fs_s*)*, void (%struct.uv_fs_s*)** %cb.addr, align 8, !dbg !1322
  %cmp = icmp ne void (%struct.uv_fs_s*)* %1, null, !dbg !1322
  br i1 %cmp, label %if.then, label %if.end, !dbg !1322

if.then:                                          ; preds = %do.body
  br label %do.body1, !dbg !1325

do.body1:                                         ; preds = %if.then
  br label %do.body2, !dbg !1328

do.body2:                                         ; preds = %do.body1
  %2 = load %struct.uv_fs_s*, %struct.uv_fs_s** %req.addr, align 8, !dbg !1331
  %type3 = getelementptr inbounds %struct.uv_fs_s, %struct.uv_fs_s* %2, i32 0, i32 1, !dbg !1331
  store i32 6, i32* %type3, align 8, !dbg !1331
  br label %do.end, !dbg !1331

do.end:                                           ; preds = %do.body2
  br label %do.body4, !dbg !1334

do.body4:                                         ; preds = %do.end
  br label %do.body5, !dbg !1336

do.body5:                                         ; preds = %do.body4
  %3 = load %struct.uv_loop_s*, %struct.uv_loop_s** %loop.addr, align 8, !dbg !1339
  %active_reqs = getelementptr inbounds %struct.uv_loop_s, %struct.uv_loop_s* %3, i32 0, i32 3, !dbg !1339
  %4 = load %struct.uv_fs_s*, %struct.uv_fs_s** %req.addr, align 8, !dbg !1339
  %active_queue = getelementptr inbounds %struct.uv_fs_s, %struct.uv_fs_s* %4, i32 0, i32 2, !dbg !1339
  %arrayidx = getelementptr inbounds [2 x i8*], [2 x i8*]* %active_queue, i64 0, i64 0, !dbg !1339
  %5 = bitcast i8** %arrayidx to [2 x i8*]**, !dbg !1339
  store [2 x i8*]* %active_reqs, [2 x i8*]** %5, align 8, !dbg !1339
  %6 = load %struct.uv_loop_s*, %struct.uv_loop_s** %loop.addr, align 8, !dbg !1339
  %active_reqs6 = getelementptr inbounds %struct.uv_loop_s, %struct.uv_loop_s* %6, i32 0, i32 3, !dbg !1339
  %arrayidx7 = getelementptr inbounds [2 x i8*], [2 x i8*]* %active_reqs6, i64 0, i64 1, !dbg !1339
  %7 = bitcast i8** %arrayidx7 to [2 x i8*]**, !dbg !1339
  %8 = load [2 x i8*]*, [2 x i8*]** %7, align 8, !dbg !1339
  %9 = load %struct.uv_fs_s*, %struct.uv_fs_s** %req.addr, align 8, !dbg !1339
  %active_queue8 = getelementptr inbounds %struct.uv_fs_s, %struct.uv_fs_s* %9, i32 0, i32 2, !dbg !1339
  %arrayidx9 = getelementptr inbounds [2 x i8*], [2 x i8*]* %active_queue8, i64 0, i64 1, !dbg !1339
  %10 = bitcast i8** %arrayidx9 to [2 x i8*]**, !dbg !1339
  store [2 x i8*]* %8, [2 x i8*]** %10, align 8, !dbg !1339
  %11 = load %struct.uv_fs_s*, %struct.uv_fs_s** %req.addr, align 8, !dbg !1339
  %active_queue10 = getelementptr inbounds %struct.uv_fs_s, %struct.uv_fs_s* %11, i32 0, i32 2, !dbg !1339
  %12 = load %struct.uv_fs_s*, %struct.uv_fs_s** %req.addr, align 8, !dbg !1339
  %active_queue11 = getelementptr inbounds %struct.uv_fs_s, %struct.uv_fs_s* %12, i32 0, i32 2, !dbg !1339
  %arrayidx12 = getelementptr inbounds [2 x i8*], [2 x i8*]* %active_queue11, i64 0, i64 1, !dbg !1339
  %13 = bitcast i8** %arrayidx12 to [2 x i8*]**, !dbg !1339
  %14 = load [2 x i8*]*, [2 x i8*]** %13, align 8, !dbg !1339
  %arrayidx13 = getelementptr inbounds [2 x i8*], [2 x i8*]* %14, i64 0, i64 0, !dbg !1339
  %15 = bitcast i8** %arrayidx13 to [2 x i8*]**, !dbg !1339
  store [2 x i8*]* %active_queue10, [2 x i8*]** %15, align 8, !dbg !1339
  %16 = load %struct.uv_fs_s*, %struct.uv_fs_s** %req.addr, align 8, !dbg !1339
  %active_queue14 = getelementptr inbounds %struct.uv_fs_s, %struct.uv_fs_s* %16, i32 0, i32 2, !dbg !1339
  %17 = load %struct.uv_loop_s*, %struct.uv_loop_s** %loop.addr, align 8, !dbg !1339
  %active_reqs15 = getelementptr inbounds %struct.uv_loop_s, %struct.uv_loop_s* %17, i32 0, i32 3, !dbg !1339
  %arrayidx16 = getelementptr inbounds [2 x i8*], [2 x i8*]* %active_reqs15, i64 0, i64 1, !dbg !1339
  %18 = bitcast i8** %arrayidx16 to [2 x i8*]**, !dbg !1339
  store [2 x i8*]* %active_queue14, [2 x i8*]** %18, align 8, !dbg !1339
  br label %do.end17, !dbg !1339

do.end17:                                         ; preds = %do.body5
  br label %do.end18, !dbg !1342

do.end18:                                         ; preds = %do.end17
  br label %do.end19, !dbg !1344

do.end19:                                         ; preds = %do.end18
  br label %if.end, !dbg !1346

if.end:                                           ; preds = %do.end19, %do.body
  %19 = load %struct.uv_fs_s*, %struct.uv_fs_s** %req.addr, align 8, !dbg !1348
  %fs_type = getelementptr inbounds %struct.uv_fs_s, %struct.uv_fs_s* %19, i32 0, i32 4, !dbg !1348
  store i32 15, i32* %fs_type, align 8, !dbg !1348
  %20 = load %struct.uv_fs_s*, %struct.uv_fs_s** %req.addr, align 8, !dbg !1348
  %result = getelementptr inbounds %struct.uv_fs_s, %struct.uv_fs_s* %20, i32 0, i32 7, !dbg !1348
  store i64 0, i64* %result, align 8, !dbg !1348
  %21 = load %struct.uv_fs_s*, %struct.uv_fs_s** %req.addr, align 8, !dbg !1348
  %ptr = getelementptr inbounds %struct.uv_fs_s, %struct.uv_fs_s* %21, i32 0, i32 8, !dbg !1348
  store i8* null, i8** %ptr, align 8, !dbg !1348
  %22 = load %struct.uv_loop_s*, %struct.uv_loop_s** %loop.addr, align 8, !dbg !1348
  %23 = load %struct.uv_fs_s*, %struct.uv_fs_s** %req.addr, align 8, !dbg !1348
  %loop20 = getelementptr inbounds %struct.uv_fs_s, %struct.uv_fs_s* %23, i32 0, i32 5, !dbg !1348
  store %struct.uv_loop_s* %22, %struct.uv_loop_s** %loop20, align 8, !dbg !1348
  %24 = load %struct.uv_fs_s*, %struct.uv_fs_s** %req.addr, align 8, !dbg !1348
  %path = getelementptr inbounds %struct.uv_fs_s, %struct.uv_fs_s* %24, i32 0, i32 9, !dbg !1348
  store i8* null, i8** %path, align 8, !dbg !1348
  %25 = load %struct.uv_fs_s*, %struct.uv_fs_s** %req.addr, align 8, !dbg !1348
  %new_path = getelementptr inbounds %struct.uv_fs_s, %struct.uv_fs_s* %25, i32 0, i32 11, !dbg !1348
  store i8* null, i8** %new_path, align 8, !dbg !1348
  %26 = load void (%struct.uv_fs_s*)*, void (%struct.uv_fs_s*)** %cb.addr, align 8, !dbg !1348
  %27 = load %struct.uv_fs_s*, %struct.uv_fs_s** %req.addr, align 8, !dbg !1348
  %cb21 = getelementptr inbounds %struct.uv_fs_s, %struct.uv_fs_s* %27, i32 0, i32 6, !dbg !1348
  store void (%struct.uv_fs_s*)* %26, void (%struct.uv_fs_s*)** %cb21, align 8, !dbg !1348
  br label %do.end22, !dbg !1348

do.end22:                                         ; preds = %if.end
  %28 = load i32, i32* %file.addr, align 4, !dbg !1350
  %29 = load %struct.uv_fs_s*, %struct.uv_fs_s** %req.addr, align 8, !dbg !1351
  %file23 = getelementptr inbounds %struct.uv_fs_s, %struct.uv_fs_s* %29, i32 0, i32 12, !dbg !1352
  store i32 %28, i32* %file23, align 8, !dbg !1353
  br label %do.body24, !dbg !1354

do.body24:                                        ; preds = %do.end22
  %30 = load void (%struct.uv_fs_s*)*, void (%struct.uv_fs_s*)** %cb.addr, align 8, !dbg !1355
  %cmp25 = icmp ne void (%struct.uv_fs_s*)* %30, null, !dbg !1355
  br i1 %cmp25, label %if.then26, label %if.else, !dbg !1355

if.then26:                                        ; preds = %do.body24
  %31 = load %struct.uv_loop_s*, %struct.uv_loop_s** %loop.addr, align 8, !dbg !1359
  %32 = load %struct.uv_fs_s*, %struct.uv_fs_s** %req.addr, align 8, !dbg !1359
  %work_req = getelementptr inbounds %struct.uv_fs_s, %struct.uv_fs_s* %32, i32 0, i32 22, !dbg !1359
  call void @uv__work_submit(%struct.uv_loop_s* %31, %struct.uv__work* %work_req, void (%struct.uv__work*)* @uv__fs_work, void (%struct.uv__work*, i32)* @uv__fs_done), !dbg !1359
  store i32 0, i32* %retval, align 4, !dbg !1359
  br label %do.end29, !dbg !1359

if.else:                                          ; preds = %do.body24
  %33 = load %struct.uv_fs_s*, %struct.uv_fs_s** %req.addr, align 8, !dbg !1362
  %work_req27 = getelementptr inbounds %struct.uv_fs_s, %struct.uv_fs_s* %33, i32 0, i32 22, !dbg !1362
  call void @uv__fs_work(%struct.uv__work* %work_req27), !dbg !1362
  %34 = load %struct.uv_fs_s*, %struct.uv_fs_s** %req.addr, align 8, !dbg !1362
  %result28 = getelementptr inbounds %struct.uv_fs_s, %struct.uv_fs_s* %34, i32 0, i32 7, !dbg !1362
  %35 = load i64, i64* %result28, align 8, !dbg !1362
  %conv = trunc i64 %35 to i32, !dbg !1362
  store i32 %conv, i32* %retval, align 4, !dbg !1362
  br label %do.end29, !dbg !1362

do.end29:                                         ; preds = %if.then26, %if.else
  %36 = load i32, i32* %retval, align 4, !dbg !1365
  ret i32 %36, !dbg !1365
}

; Function Attrs: nounwind uwtable
define i32 @uv_fs_ftruncate(%struct.uv_loop_s* %loop, %struct.uv_fs_s* %req, i32 %file, i64 %off, void (%struct.uv_fs_s*)* %cb) #0 !dbg !435 {
entry:
  %retval = alloca i32, align 4
  %loop.addr = alloca %struct.uv_loop_s*, align 8
  %req.addr = alloca %struct.uv_fs_s*, align 8
  %file.addr = alloca i32, align 4
  %off.addr = alloca i64, align 8
  %cb.addr = alloca void (%struct.uv_fs_s*)*, align 8
  store %struct.uv_loop_s* %loop, %struct.uv_loop_s** %loop.addr, align 8
  call void @llvm.dbg.declare(metadata %struct.uv_loop_s** %loop.addr, metadata !1366, metadata !580), !dbg !1367
  store %struct.uv_fs_s* %req, %struct.uv_fs_s** %req.addr, align 8
  call void @llvm.dbg.declare(metadata %struct.uv_fs_s** %req.addr, metadata !1368, metadata !580), !dbg !1369
  store i32 %file, i32* %file.addr, align 4
  call void @llvm.dbg.declare(metadata i32* %file.addr, metadata !1370, metadata !580), !dbg !1371
  store i64 %off, i64* %off.addr, align 8
  call void @llvm.dbg.declare(metadata i64* %off.addr, metadata !1372, metadata !580), !dbg !1373
  store void (%struct.uv_fs_s*)* %cb, void (%struct.uv_fs_s*)** %cb.addr, align 8
  call void @llvm.dbg.declare(metadata void (%struct.uv_fs_s*)** %cb.addr, metadata !1374, metadata !580), !dbg !1375
  br label %do.body, !dbg !1376

do.body:                                          ; preds = %entry
  %0 = load %struct.uv_fs_s*, %struct.uv_fs_s** %req.addr, align 8, !dbg !1377
  %type = getelementptr inbounds %struct.uv_fs_s, %struct.uv_fs_s* %0, i32 0, i32 1, !dbg !1377
  store i32 6, i32* %type, align 8, !dbg !1377
  %1 = load void (%struct.uv_fs_s*)*, void (%struct.uv_fs_s*)** %cb.addr, align 8, !dbg !1377
  %cmp = icmp ne void (%struct.uv_fs_s*)* %1, null, !dbg !1377
  br i1 %cmp, label %if.then, label %if.end, !dbg !1377

if.then:                                          ; preds = %do.body
  br label %do.body1, !dbg !1380

do.body1:                                         ; preds = %if.then
  br label %do.body2, !dbg !1383

do.body2:                                         ; preds = %do.body1
  %2 = load %struct.uv_fs_s*, %struct.uv_fs_s** %req.addr, align 8, !dbg !1386
  %type3 = getelementptr inbounds %struct.uv_fs_s, %struct.uv_fs_s* %2, i32 0, i32 1, !dbg !1386
  store i32 6, i32* %type3, align 8, !dbg !1386
  br label %do.end, !dbg !1386

do.end:                                           ; preds = %do.body2
  br label %do.body4, !dbg !1389

do.body4:                                         ; preds = %do.end
  br label %do.body5, !dbg !1391

do.body5:                                         ; preds = %do.body4
  %3 = load %struct.uv_loop_s*, %struct.uv_loop_s** %loop.addr, align 8, !dbg !1394
  %active_reqs = getelementptr inbounds %struct.uv_loop_s, %struct.uv_loop_s* %3, i32 0, i32 3, !dbg !1394
  %4 = load %struct.uv_fs_s*, %struct.uv_fs_s** %req.addr, align 8, !dbg !1394
  %active_queue = getelementptr inbounds %struct.uv_fs_s, %struct.uv_fs_s* %4, i32 0, i32 2, !dbg !1394
  %arrayidx = getelementptr inbounds [2 x i8*], [2 x i8*]* %active_queue, i64 0, i64 0, !dbg !1394
  %5 = bitcast i8** %arrayidx to [2 x i8*]**, !dbg !1394
  store [2 x i8*]* %active_reqs, [2 x i8*]** %5, align 8, !dbg !1394
  %6 = load %struct.uv_loop_s*, %struct.uv_loop_s** %loop.addr, align 8, !dbg !1394
  %active_reqs6 = getelementptr inbounds %struct.uv_loop_s, %struct.uv_loop_s* %6, i32 0, i32 3, !dbg !1394
  %arrayidx7 = getelementptr inbounds [2 x i8*], [2 x i8*]* %active_reqs6, i64 0, i64 1, !dbg !1394
  %7 = bitcast i8** %arrayidx7 to [2 x i8*]**, !dbg !1394
  %8 = load [2 x i8*]*, [2 x i8*]** %7, align 8, !dbg !1394
  %9 = load %struct.uv_fs_s*, %struct.uv_fs_s** %req.addr, align 8, !dbg !1394
  %active_queue8 = getelementptr inbounds %struct.uv_fs_s, %struct.uv_fs_s* %9, i32 0, i32 2, !dbg !1394
  %arrayidx9 = getelementptr inbounds [2 x i8*], [2 x i8*]* %active_queue8, i64 0, i64 1, !dbg !1394
  %10 = bitcast i8** %arrayidx9 to [2 x i8*]**, !dbg !1394
  store [2 x i8*]* %8, [2 x i8*]** %10, align 8, !dbg !1394
  %11 = load %struct.uv_fs_s*, %struct.uv_fs_s** %req.addr, align 8, !dbg !1394
  %active_queue10 = getelementptr inbounds %struct.uv_fs_s, %struct.uv_fs_s* %11, i32 0, i32 2, !dbg !1394
  %12 = load %struct.uv_fs_s*, %struct.uv_fs_s** %req.addr, align 8, !dbg !1394
  %active_queue11 = getelementptr inbounds %struct.uv_fs_s, %struct.uv_fs_s* %12, i32 0, i32 2, !dbg !1394
  %arrayidx12 = getelementptr inbounds [2 x i8*], [2 x i8*]* %active_queue11, i64 0, i64 1, !dbg !1394
  %13 = bitcast i8** %arrayidx12 to [2 x i8*]**, !dbg !1394
  %14 = load [2 x i8*]*, [2 x i8*]** %13, align 8, !dbg !1394
  %arrayidx13 = getelementptr inbounds [2 x i8*], [2 x i8*]* %14, i64 0, i64 0, !dbg !1394
  %15 = bitcast i8** %arrayidx13 to [2 x i8*]**, !dbg !1394
  store [2 x i8*]* %active_queue10, [2 x i8*]** %15, align 8, !dbg !1394
  %16 = load %struct.uv_fs_s*, %struct.uv_fs_s** %req.addr, align 8, !dbg !1394
  %active_queue14 = getelementptr inbounds %struct.uv_fs_s, %struct.uv_fs_s* %16, i32 0, i32 2, !dbg !1394
  %17 = load %struct.uv_loop_s*, %struct.uv_loop_s** %loop.addr, align 8, !dbg !1394
  %active_reqs15 = getelementptr inbounds %struct.uv_loop_s, %struct.uv_loop_s* %17, i32 0, i32 3, !dbg !1394
  %arrayidx16 = getelementptr inbounds [2 x i8*], [2 x i8*]* %active_reqs15, i64 0, i64 1, !dbg !1394
  %18 = bitcast i8** %arrayidx16 to [2 x i8*]**, !dbg !1394
  store [2 x i8*]* %active_queue14, [2 x i8*]** %18, align 8, !dbg !1394
  br label %do.end17, !dbg !1394

do.end17:                                         ; preds = %do.body5
  br label %do.end18, !dbg !1397

do.end18:                                         ; preds = %do.end17
  br label %do.end19, !dbg !1399

do.end19:                                         ; preds = %do.end18
  br label %if.end, !dbg !1401

if.end:                                           ; preds = %do.end19, %do.body
  %19 = load %struct.uv_fs_s*, %struct.uv_fs_s** %req.addr, align 8, !dbg !1403
  %fs_type = getelementptr inbounds %struct.uv_fs_s, %struct.uv_fs_s* %19, i32 0, i32 4, !dbg !1403
  store i32 9, i32* %fs_type, align 8, !dbg !1403
  %20 = load %struct.uv_fs_s*, %struct.uv_fs_s** %req.addr, align 8, !dbg !1403
  %result = getelementptr inbounds %struct.uv_fs_s, %struct.uv_fs_s* %20, i32 0, i32 7, !dbg !1403
  store i64 0, i64* %result, align 8, !dbg !1403
  %21 = load %struct.uv_fs_s*, %struct.uv_fs_s** %req.addr, align 8, !dbg !1403
  %ptr = getelementptr inbounds %struct.uv_fs_s, %struct.uv_fs_s* %21, i32 0, i32 8, !dbg !1403
  store i8* null, i8** %ptr, align 8, !dbg !1403
  %22 = load %struct.uv_loop_s*, %struct.uv_loop_s** %loop.addr, align 8, !dbg !1403
  %23 = load %struct.uv_fs_s*, %struct.uv_fs_s** %req.addr, align 8, !dbg !1403
  %loop20 = getelementptr inbounds %struct.uv_fs_s, %struct.uv_fs_s* %23, i32 0, i32 5, !dbg !1403
  store %struct.uv_loop_s* %22, %struct.uv_loop_s** %loop20, align 8, !dbg !1403
  %24 = load %struct.uv_fs_s*, %struct.uv_fs_s** %req.addr, align 8, !dbg !1403
  %path = getelementptr inbounds %struct.uv_fs_s, %struct.uv_fs_s* %24, i32 0, i32 9, !dbg !1403
  store i8* null, i8** %path, align 8, !dbg !1403
  %25 = load %struct.uv_fs_s*, %struct.uv_fs_s** %req.addr, align 8, !dbg !1403
  %new_path = getelementptr inbounds %struct.uv_fs_s, %struct.uv_fs_s* %25, i32 0, i32 11, !dbg !1403
  store i8* null, i8** %new_path, align 8, !dbg !1403
  %26 = load void (%struct.uv_fs_s*)*, void (%struct.uv_fs_s*)** %cb.addr, align 8, !dbg !1403
  %27 = load %struct.uv_fs_s*, %struct.uv_fs_s** %req.addr, align 8, !dbg !1403
  %cb21 = getelementptr inbounds %struct.uv_fs_s, %struct.uv_fs_s* %27, i32 0, i32 6, !dbg !1403
  store void (%struct.uv_fs_s*)* %26, void (%struct.uv_fs_s*)** %cb21, align 8, !dbg !1403
  br label %do.end22, !dbg !1403

do.end22:                                         ; preds = %if.end
  %28 = load i32, i32* %file.addr, align 4, !dbg !1405
  %29 = load %struct.uv_fs_s*, %struct.uv_fs_s** %req.addr, align 8, !dbg !1406
  %file23 = getelementptr inbounds %struct.uv_fs_s, %struct.uv_fs_s* %29, i32 0, i32 12, !dbg !1407
  store i32 %28, i32* %file23, align 8, !dbg !1408
  %30 = load i64, i64* %off.addr, align 8, !dbg !1409
  %31 = load %struct.uv_fs_s*, %struct.uv_fs_s** %req.addr, align 8, !dbg !1410
  %off24 = getelementptr inbounds %struct.uv_fs_s, %struct.uv_fs_s* %31, i32 0, i32 17, !dbg !1411
  store i64 %30, i64* %off24, align 8, !dbg !1412
  br label %do.body25, !dbg !1413

do.body25:                                        ; preds = %do.end22
  %32 = load void (%struct.uv_fs_s*)*, void (%struct.uv_fs_s*)** %cb.addr, align 8, !dbg !1414
  %cmp26 = icmp ne void (%struct.uv_fs_s*)* %32, null, !dbg !1414
  br i1 %cmp26, label %if.then27, label %if.else, !dbg !1414

if.then27:                                        ; preds = %do.body25
  %33 = load %struct.uv_loop_s*, %struct.uv_loop_s** %loop.addr, align 8, !dbg !1418
  %34 = load %struct.uv_fs_s*, %struct.uv_fs_s** %req.addr, align 8, !dbg !1418
  %work_req = getelementptr inbounds %struct.uv_fs_s, %struct.uv_fs_s* %34, i32 0, i32 22, !dbg !1418
  call void @uv__work_submit(%struct.uv_loop_s* %33, %struct.uv__work* %work_req, void (%struct.uv__work*)* @uv__fs_work, void (%struct.uv__work*, i32)* @uv__fs_done), !dbg !1418
  store i32 0, i32* %retval, align 4, !dbg !1418
  br label %do.end30, !dbg !1418

if.else:                                          ; preds = %do.body25
  %35 = load %struct.uv_fs_s*, %struct.uv_fs_s** %req.addr, align 8, !dbg !1421
  %work_req28 = getelementptr inbounds %struct.uv_fs_s, %struct.uv_fs_s* %35, i32 0, i32 22, !dbg !1421
  call void @uv__fs_work(%struct.uv__work* %work_req28), !dbg !1421
  %36 = load %struct.uv_fs_s*, %struct.uv_fs_s** %req.addr, align 8, !dbg !1421
  %result29 = getelementptr inbounds %struct.uv_fs_s, %struct.uv_fs_s* %36, i32 0, i32 7, !dbg !1421
  %37 = load i64, i64* %result29, align 8, !dbg !1421
  %conv = trunc i64 %37 to i32, !dbg !1421
  store i32 %conv, i32* %retval, align 4, !dbg !1421
  br label %do.end30, !dbg !1421

do.end30:                                         ; preds = %if.then27, %if.else
  %38 = load i32, i32* %retval, align 4, !dbg !1424
  ret i32 %38, !dbg !1424
}

; Function Attrs: nounwind uwtable
define i32 @uv_fs_futime(%struct.uv_loop_s* %loop, %struct.uv_fs_s* %req, i32 %file, double %atime, double %mtime, void (%struct.uv_fs_s*)* %cb) #0 !dbg !439 {
entry:
  %retval = alloca i32, align 4
  %loop.addr = alloca %struct.uv_loop_s*, align 8
  %req.addr = alloca %struct.uv_fs_s*, align 8
  %file.addr = alloca i32, align 4
  %atime.addr = alloca double, align 8
  %mtime.addr = alloca double, align 8
  %cb.addr = alloca void (%struct.uv_fs_s*)*, align 8
  store %struct.uv_loop_s* %loop, %struct.uv_loop_s** %loop.addr, align 8
  call void @llvm.dbg.declare(metadata %struct.uv_loop_s** %loop.addr, metadata !1425, metadata !580), !dbg !1426
  store %struct.uv_fs_s* %req, %struct.uv_fs_s** %req.addr, align 8
  call void @llvm.dbg.declare(metadata %struct.uv_fs_s** %req.addr, metadata !1427, metadata !580), !dbg !1428
  store i32 %file, i32* %file.addr, align 4
  call void @llvm.dbg.declare(metadata i32* %file.addr, metadata !1429, metadata !580), !dbg !1430
  store double %atime, double* %atime.addr, align 8
  call void @llvm.dbg.declare(metadata double* %atime.addr, metadata !1431, metadata !580), !dbg !1432
  store double %mtime, double* %mtime.addr, align 8
  call void @llvm.dbg.declare(metadata double* %mtime.addr, metadata !1433, metadata !580), !dbg !1434
  store void (%struct.uv_fs_s*)* %cb, void (%struct.uv_fs_s*)** %cb.addr, align 8
  call void @llvm.dbg.declare(metadata void (%struct.uv_fs_s*)** %cb.addr, metadata !1435, metadata !580), !dbg !1436
  br label %do.body, !dbg !1437

do.body:                                          ; preds = %entry
  %0 = load %struct.uv_fs_s*, %struct.uv_fs_s** %req.addr, align 8, !dbg !1438
  %type = getelementptr inbounds %struct.uv_fs_s, %struct.uv_fs_s* %0, i32 0, i32 1, !dbg !1438
  store i32 6, i32* %type, align 8, !dbg !1438
  %1 = load void (%struct.uv_fs_s*)*, void (%struct.uv_fs_s*)** %cb.addr, align 8, !dbg !1438
  %cmp = icmp ne void (%struct.uv_fs_s*)* %1, null, !dbg !1438
  br i1 %cmp, label %if.then, label %if.end, !dbg !1438

if.then:                                          ; preds = %do.body
  br label %do.body1, !dbg !1441

do.body1:                                         ; preds = %if.then
  br label %do.body2, !dbg !1444

do.body2:                                         ; preds = %do.body1
  %2 = load %struct.uv_fs_s*, %struct.uv_fs_s** %req.addr, align 8, !dbg !1447
  %type3 = getelementptr inbounds %struct.uv_fs_s, %struct.uv_fs_s* %2, i32 0, i32 1, !dbg !1447
  store i32 6, i32* %type3, align 8, !dbg !1447
  br label %do.end, !dbg !1447

do.end:                                           ; preds = %do.body2
  br label %do.body4, !dbg !1450

do.body4:                                         ; preds = %do.end
  br label %do.body5, !dbg !1452

do.body5:                                         ; preds = %do.body4
  %3 = load %struct.uv_loop_s*, %struct.uv_loop_s** %loop.addr, align 8, !dbg !1455
  %active_reqs = getelementptr inbounds %struct.uv_loop_s, %struct.uv_loop_s* %3, i32 0, i32 3, !dbg !1455
  %4 = load %struct.uv_fs_s*, %struct.uv_fs_s** %req.addr, align 8, !dbg !1455
  %active_queue = getelementptr inbounds %struct.uv_fs_s, %struct.uv_fs_s* %4, i32 0, i32 2, !dbg !1455
  %arrayidx = getelementptr inbounds [2 x i8*], [2 x i8*]* %active_queue, i64 0, i64 0, !dbg !1455
  %5 = bitcast i8** %arrayidx to [2 x i8*]**, !dbg !1455
  store [2 x i8*]* %active_reqs, [2 x i8*]** %5, align 8, !dbg !1455
  %6 = load %struct.uv_loop_s*, %struct.uv_loop_s** %loop.addr, align 8, !dbg !1455
  %active_reqs6 = getelementptr inbounds %struct.uv_loop_s, %struct.uv_loop_s* %6, i32 0, i32 3, !dbg !1455
  %arrayidx7 = getelementptr inbounds [2 x i8*], [2 x i8*]* %active_reqs6, i64 0, i64 1, !dbg !1455
  %7 = bitcast i8** %arrayidx7 to [2 x i8*]**, !dbg !1455
  %8 = load [2 x i8*]*, [2 x i8*]** %7, align 8, !dbg !1455
  %9 = load %struct.uv_fs_s*, %struct.uv_fs_s** %req.addr, align 8, !dbg !1455
  %active_queue8 = getelementptr inbounds %struct.uv_fs_s, %struct.uv_fs_s* %9, i32 0, i32 2, !dbg !1455
  %arrayidx9 = getelementptr inbounds [2 x i8*], [2 x i8*]* %active_queue8, i64 0, i64 1, !dbg !1455
  %10 = bitcast i8** %arrayidx9 to [2 x i8*]**, !dbg !1455
  store [2 x i8*]* %8, [2 x i8*]** %10, align 8, !dbg !1455
  %11 = load %struct.uv_fs_s*, %struct.uv_fs_s** %req.addr, align 8, !dbg !1455
  %active_queue10 = getelementptr inbounds %struct.uv_fs_s, %struct.uv_fs_s* %11, i32 0, i32 2, !dbg !1455
  %12 = load %struct.uv_fs_s*, %struct.uv_fs_s** %req.addr, align 8, !dbg !1455
  %active_queue11 = getelementptr inbounds %struct.uv_fs_s, %struct.uv_fs_s* %12, i32 0, i32 2, !dbg !1455
  %arrayidx12 = getelementptr inbounds [2 x i8*], [2 x i8*]* %active_queue11, i64 0, i64 1, !dbg !1455
  %13 = bitcast i8** %arrayidx12 to [2 x i8*]**, !dbg !1455
  %14 = load [2 x i8*]*, [2 x i8*]** %13, align 8, !dbg !1455
  %arrayidx13 = getelementptr inbounds [2 x i8*], [2 x i8*]* %14, i64 0, i64 0, !dbg !1455
  %15 = bitcast i8** %arrayidx13 to [2 x i8*]**, !dbg !1455
  store [2 x i8*]* %active_queue10, [2 x i8*]** %15, align 8, !dbg !1455
  %16 = load %struct.uv_fs_s*, %struct.uv_fs_s** %req.addr, align 8, !dbg !1455
  %active_queue14 = getelementptr inbounds %struct.uv_fs_s, %struct.uv_fs_s* %16, i32 0, i32 2, !dbg !1455
  %17 = load %struct.uv_loop_s*, %struct.uv_loop_s** %loop.addr, align 8, !dbg !1455
  %active_reqs15 = getelementptr inbounds %struct.uv_loop_s, %struct.uv_loop_s* %17, i32 0, i32 3, !dbg !1455
  %arrayidx16 = getelementptr inbounds [2 x i8*], [2 x i8*]* %active_reqs15, i64 0, i64 1, !dbg !1455
  %18 = bitcast i8** %arrayidx16 to [2 x i8*]**, !dbg !1455
  store [2 x i8*]* %active_queue14, [2 x i8*]** %18, align 8, !dbg !1455
  br label %do.end17, !dbg !1455

do.end17:                                         ; preds = %do.body5
  br label %do.end18, !dbg !1458

do.end18:                                         ; preds = %do.end17
  br label %do.end19, !dbg !1460

do.end19:                                         ; preds = %do.end18
  br label %if.end, !dbg !1462

if.end:                                           ; preds = %do.end19, %do.body
  %19 = load %struct.uv_fs_s*, %struct.uv_fs_s** %req.addr, align 8, !dbg !1464
  %fs_type = getelementptr inbounds %struct.uv_fs_s, %struct.uv_fs_s* %19, i32 0, i32 4, !dbg !1464
  store i32 11, i32* %fs_type, align 8, !dbg !1464
  %20 = load %struct.uv_fs_s*, %struct.uv_fs_s** %req.addr, align 8, !dbg !1464
  %result = getelementptr inbounds %struct.uv_fs_s, %struct.uv_fs_s* %20, i32 0, i32 7, !dbg !1464
  store i64 0, i64* %result, align 8, !dbg !1464
  %21 = load %struct.uv_fs_s*, %struct.uv_fs_s** %req.addr, align 8, !dbg !1464
  %ptr = getelementptr inbounds %struct.uv_fs_s, %struct.uv_fs_s* %21, i32 0, i32 8, !dbg !1464
  store i8* null, i8** %ptr, align 8, !dbg !1464
  %22 = load %struct.uv_loop_s*, %struct.uv_loop_s** %loop.addr, align 8, !dbg !1464
  %23 = load %struct.uv_fs_s*, %struct.uv_fs_s** %req.addr, align 8, !dbg !1464
  %loop20 = getelementptr inbounds %struct.uv_fs_s, %struct.uv_fs_s* %23, i32 0, i32 5, !dbg !1464
  store %struct.uv_loop_s* %22, %struct.uv_loop_s** %loop20, align 8, !dbg !1464
  %24 = load %struct.uv_fs_s*, %struct.uv_fs_s** %req.addr, align 8, !dbg !1464
  %path = getelementptr inbounds %struct.uv_fs_s, %struct.uv_fs_s* %24, i32 0, i32 9, !dbg !1464
  store i8* null, i8** %path, align 8, !dbg !1464
  %25 = load %struct.uv_fs_s*, %struct.uv_fs_s** %req.addr, align 8, !dbg !1464
  %new_path = getelementptr inbounds %struct.uv_fs_s, %struct.uv_fs_s* %25, i32 0, i32 11, !dbg !1464
  store i8* null, i8** %new_path, align 8, !dbg !1464
  %26 = load void (%struct.uv_fs_s*)*, void (%struct.uv_fs_s*)** %cb.addr, align 8, !dbg !1464
  %27 = load %struct.uv_fs_s*, %struct.uv_fs_s** %req.addr, align 8, !dbg !1464
  %cb21 = getelementptr inbounds %struct.uv_fs_s, %struct.uv_fs_s* %27, i32 0, i32 6, !dbg !1464
  store void (%struct.uv_fs_s*)* %26, void (%struct.uv_fs_s*)** %cb21, align 8, !dbg !1464
  br label %do.end22, !dbg !1464

do.end22:                                         ; preds = %if.end
  %28 = load i32, i32* %file.addr, align 4, !dbg !1466
  %29 = load %struct.uv_fs_s*, %struct.uv_fs_s** %req.addr, align 8, !dbg !1467
  %file23 = getelementptr inbounds %struct.uv_fs_s, %struct.uv_fs_s* %29, i32 0, i32 12, !dbg !1468
  store i32 %28, i32* %file23, align 8, !dbg !1469
  %30 = load double, double* %atime.addr, align 8, !dbg !1470
  %31 = load %struct.uv_fs_s*, %struct.uv_fs_s** %req.addr, align 8, !dbg !1471
  %atime24 = getelementptr inbounds %struct.uv_fs_s, %struct.uv_fs_s* %31, i32 0, i32 20, !dbg !1472
  store double %30, double* %atime24, align 8, !dbg !1473
  %32 = load double, double* %mtime.addr, align 8, !dbg !1474
  %33 = load %struct.uv_fs_s*, %struct.uv_fs_s** %req.addr, align 8, !dbg !1475
  %mtime25 = getelementptr inbounds %struct.uv_fs_s, %struct.uv_fs_s* %33, i32 0, i32 21, !dbg !1476
  store double %32, double* %mtime25, align 8, !dbg !1477
  br label %do.body26, !dbg !1478

do.body26:                                        ; preds = %do.end22
  %34 = load void (%struct.uv_fs_s*)*, void (%struct.uv_fs_s*)** %cb.addr, align 8, !dbg !1479
  %cmp27 = icmp ne void (%struct.uv_fs_s*)* %34, null, !dbg !1479
  br i1 %cmp27, label %if.then28, label %if.else, !dbg !1479

if.then28:                                        ; preds = %do.body26
  %35 = load %struct.uv_loop_s*, %struct.uv_loop_s** %loop.addr, align 8, !dbg !1483
  %36 = load %struct.uv_fs_s*, %struct.uv_fs_s** %req.addr, align 8, !dbg !1483
  %work_req = getelementptr inbounds %struct.uv_fs_s, %struct.uv_fs_s* %36, i32 0, i32 22, !dbg !1483
  call void @uv__work_submit(%struct.uv_loop_s* %35, %struct.uv__work* %work_req, void (%struct.uv__work*)* @uv__fs_work, void (%struct.uv__work*, i32)* @uv__fs_done), !dbg !1483
  store i32 0, i32* %retval, align 4, !dbg !1483
  br label %do.end31, !dbg !1483

if.else:                                          ; preds = %do.body26
  %37 = load %struct.uv_fs_s*, %struct.uv_fs_s** %req.addr, align 8, !dbg !1486
  %work_req29 = getelementptr inbounds %struct.uv_fs_s, %struct.uv_fs_s* %37, i32 0, i32 22, !dbg !1486
  call void @uv__fs_work(%struct.uv__work* %work_req29), !dbg !1486
  %38 = load %struct.uv_fs_s*, %struct.uv_fs_s** %req.addr, align 8, !dbg !1486
  %result30 = getelementptr inbounds %struct.uv_fs_s, %struct.uv_fs_s* %38, i32 0, i32 7, !dbg !1486
  %39 = load i64, i64* %result30, align 8, !dbg !1486
  %conv = trunc i64 %39 to i32, !dbg !1486
  store i32 %conv, i32* %retval, align 4, !dbg !1486
  br label %do.end31, !dbg !1486

do.end31:                                         ; preds = %if.then28, %if.else
  %40 = load i32, i32* %retval, align 4, !dbg !1489
  ret i32 %40, !dbg !1489
}

; Function Attrs: nounwind uwtable
define i32 @uv_fs_lstat(%struct.uv_loop_s* %loop, %struct.uv_fs_s* %req, i8* %path, void (%struct.uv_fs_s*)* %cb) #0 !dbg !442 {
entry:
  %retval = alloca i32, align 4
  %loop.addr = alloca %struct.uv_loop_s*, align 8
  %req.addr = alloca %struct.uv_fs_s*, align 8
  %path.addr = alloca i8*, align 8
  %cb.addr = alloca void (%struct.uv_fs_s*)*, align 8
  store %struct.uv_loop_s* %loop, %struct.uv_loop_s** %loop.addr, align 8
  call void @llvm.dbg.declare(metadata %struct.uv_loop_s** %loop.addr, metadata !1490, metadata !580), !dbg !1491
  store %struct.uv_fs_s* %req, %struct.uv_fs_s** %req.addr, align 8
  call void @llvm.dbg.declare(metadata %struct.uv_fs_s** %req.addr, metadata !1492, metadata !580), !dbg !1493
  store i8* %path, i8** %path.addr, align 8
  call void @llvm.dbg.declare(metadata i8** %path.addr, metadata !1494, metadata !580), !dbg !1495
  store void (%struct.uv_fs_s*)* %cb, void (%struct.uv_fs_s*)** %cb.addr, align 8
  call void @llvm.dbg.declare(metadata void (%struct.uv_fs_s*)** %cb.addr, metadata !1496, metadata !580), !dbg !1497
  br label %do.body, !dbg !1498

do.body:                                          ; preds = %entry
  %0 = load %struct.uv_fs_s*, %struct.uv_fs_s** %req.addr, align 8, !dbg !1499
  %type = getelementptr inbounds %struct.uv_fs_s, %struct.uv_fs_s* %0, i32 0, i32 1, !dbg !1499
  store i32 6, i32* %type, align 8, !dbg !1499
  %1 = load void (%struct.uv_fs_s*)*, void (%struct.uv_fs_s*)** %cb.addr, align 8, !dbg !1499
  %cmp = icmp ne void (%struct.uv_fs_s*)* %1, null, !dbg !1499
  br i1 %cmp, label %if.then, label %if.end, !dbg !1499

if.then:                                          ; preds = %do.body
  br label %do.body1, !dbg !1502

do.body1:                                         ; preds = %if.then
  br label %do.body2, !dbg !1505

do.body2:                                         ; preds = %do.body1
  %2 = load %struct.uv_fs_s*, %struct.uv_fs_s** %req.addr, align 8, !dbg !1508
  %type3 = getelementptr inbounds %struct.uv_fs_s, %struct.uv_fs_s* %2, i32 0, i32 1, !dbg !1508
  store i32 6, i32* %type3, align 8, !dbg !1508
  br label %do.end, !dbg !1508

do.end:                                           ; preds = %do.body2
  br label %do.body4, !dbg !1511

do.body4:                                         ; preds = %do.end
  br label %do.body5, !dbg !1513

do.body5:                                         ; preds = %do.body4
  %3 = load %struct.uv_loop_s*, %struct.uv_loop_s** %loop.addr, align 8, !dbg !1516
  %active_reqs = getelementptr inbounds %struct.uv_loop_s, %struct.uv_loop_s* %3, i32 0, i32 3, !dbg !1516
  %4 = load %struct.uv_fs_s*, %struct.uv_fs_s** %req.addr, align 8, !dbg !1516
  %active_queue = getelementptr inbounds %struct.uv_fs_s, %struct.uv_fs_s* %4, i32 0, i32 2, !dbg !1516
  %arrayidx = getelementptr inbounds [2 x i8*], [2 x i8*]* %active_queue, i64 0, i64 0, !dbg !1516
  %5 = bitcast i8** %arrayidx to [2 x i8*]**, !dbg !1516
  store [2 x i8*]* %active_reqs, [2 x i8*]** %5, align 8, !dbg !1516
  %6 = load %struct.uv_loop_s*, %struct.uv_loop_s** %loop.addr, align 8, !dbg !1516
  %active_reqs6 = getelementptr inbounds %struct.uv_loop_s, %struct.uv_loop_s* %6, i32 0, i32 3, !dbg !1516
  %arrayidx7 = getelementptr inbounds [2 x i8*], [2 x i8*]* %active_reqs6, i64 0, i64 1, !dbg !1516
  %7 = bitcast i8** %arrayidx7 to [2 x i8*]**, !dbg !1516
  %8 = load [2 x i8*]*, [2 x i8*]** %7, align 8, !dbg !1516
  %9 = load %struct.uv_fs_s*, %struct.uv_fs_s** %req.addr, align 8, !dbg !1516
  %active_queue8 = getelementptr inbounds %struct.uv_fs_s, %struct.uv_fs_s* %9, i32 0, i32 2, !dbg !1516
  %arrayidx9 = getelementptr inbounds [2 x i8*], [2 x i8*]* %active_queue8, i64 0, i64 1, !dbg !1516
  %10 = bitcast i8** %arrayidx9 to [2 x i8*]**, !dbg !1516
  store [2 x i8*]* %8, [2 x i8*]** %10, align 8, !dbg !1516
  %11 = load %struct.uv_fs_s*, %struct.uv_fs_s** %req.addr, align 8, !dbg !1516
  %active_queue10 = getelementptr inbounds %struct.uv_fs_s, %struct.uv_fs_s* %11, i32 0, i32 2, !dbg !1516
  %12 = load %struct.uv_fs_s*, %struct.uv_fs_s** %req.addr, align 8, !dbg !1516
  %active_queue11 = getelementptr inbounds %struct.uv_fs_s, %struct.uv_fs_s* %12, i32 0, i32 2, !dbg !1516
  %arrayidx12 = getelementptr inbounds [2 x i8*], [2 x i8*]* %active_queue11, i64 0, i64 1, !dbg !1516
  %13 = bitcast i8** %arrayidx12 to [2 x i8*]**, !dbg !1516
  %14 = load [2 x i8*]*, [2 x i8*]** %13, align 8, !dbg !1516
  %arrayidx13 = getelementptr inbounds [2 x i8*], [2 x i8*]* %14, i64 0, i64 0, !dbg !1516
  %15 = bitcast i8** %arrayidx13 to [2 x i8*]**, !dbg !1516
  store [2 x i8*]* %active_queue10, [2 x i8*]** %15, align 8, !dbg !1516
  %16 = load %struct.uv_fs_s*, %struct.uv_fs_s** %req.addr, align 8, !dbg !1516
  %active_queue14 = getelementptr inbounds %struct.uv_fs_s, %struct.uv_fs_s* %16, i32 0, i32 2, !dbg !1516
  %17 = load %struct.uv_loop_s*, %struct.uv_loop_s** %loop.addr, align 8, !dbg !1516
  %active_reqs15 = getelementptr inbounds %struct.uv_loop_s, %struct.uv_loop_s* %17, i32 0, i32 3, !dbg !1516
  %arrayidx16 = getelementptr inbounds [2 x i8*], [2 x i8*]* %active_reqs15, i64 0, i64 1, !dbg !1516
  %18 = bitcast i8** %arrayidx16 to [2 x i8*]**, !dbg !1516
  store [2 x i8*]* %active_queue14, [2 x i8*]** %18, align 8, !dbg !1516
  br label %do.end17, !dbg !1516

do.end17:                                         ; preds = %do.body5
  br label %do.end18, !dbg !1519

do.end18:                                         ; preds = %do.end17
  br label %do.end19, !dbg !1521

do.end19:                                         ; preds = %do.end18
  br label %if.end, !dbg !1523

if.end:                                           ; preds = %do.end19, %do.body
  %19 = load %struct.uv_fs_s*, %struct.uv_fs_s** %req.addr, align 8, !dbg !1525
  %fs_type = getelementptr inbounds %struct.uv_fs_s, %struct.uv_fs_s* %19, i32 0, i32 4, !dbg !1525
  store i32 7, i32* %fs_type, align 8, !dbg !1525
  %20 = load %struct.uv_fs_s*, %struct.uv_fs_s** %req.addr, align 8, !dbg !1525
  %result = getelementptr inbounds %struct.uv_fs_s, %struct.uv_fs_s* %20, i32 0, i32 7, !dbg !1525
  store i64 0, i64* %result, align 8, !dbg !1525
  %21 = load %struct.uv_fs_s*, %struct.uv_fs_s** %req.addr, align 8, !dbg !1525
  %ptr = getelementptr inbounds %struct.uv_fs_s, %struct.uv_fs_s* %21, i32 0, i32 8, !dbg !1525
  store i8* null, i8** %ptr, align 8, !dbg !1525
  %22 = load %struct.uv_loop_s*, %struct.uv_loop_s** %loop.addr, align 8, !dbg !1525
  %23 = load %struct.uv_fs_s*, %struct.uv_fs_s** %req.addr, align 8, !dbg !1525
  %loop20 = getelementptr inbounds %struct.uv_fs_s, %struct.uv_fs_s* %23, i32 0, i32 5, !dbg !1525
  store %struct.uv_loop_s* %22, %struct.uv_loop_s** %loop20, align 8, !dbg !1525
  %24 = load %struct.uv_fs_s*, %struct.uv_fs_s** %req.addr, align 8, !dbg !1525
  %path21 = getelementptr inbounds %struct.uv_fs_s, %struct.uv_fs_s* %24, i32 0, i32 9, !dbg !1525
  store i8* null, i8** %path21, align 8, !dbg !1525
  %25 = load %struct.uv_fs_s*, %struct.uv_fs_s** %req.addr, align 8, !dbg !1525
  %new_path = getelementptr inbounds %struct.uv_fs_s, %struct.uv_fs_s* %25, i32 0, i32 11, !dbg !1525
  store i8* null, i8** %new_path, align 8, !dbg !1525
  %26 = load void (%struct.uv_fs_s*)*, void (%struct.uv_fs_s*)** %cb.addr, align 8, !dbg !1525
  %27 = load %struct.uv_fs_s*, %struct.uv_fs_s** %req.addr, align 8, !dbg !1525
  %cb22 = getelementptr inbounds %struct.uv_fs_s, %struct.uv_fs_s* %27, i32 0, i32 6, !dbg !1525
  store void (%struct.uv_fs_s*)* %26, void (%struct.uv_fs_s*)** %cb22, align 8, !dbg !1525
  br label %do.end23, !dbg !1525

do.end23:                                         ; preds = %if.end
  br label %do.body24, !dbg !1527

do.body24:                                        ; preds = %do.end23
  %28 = load i8*, i8** %path.addr, align 8, !dbg !1528
  %cmp25 = icmp ne i8* %28, null, !dbg !1528
  br i1 %cmp25, label %cond.true, label %cond.false, !dbg !1528

cond.true:                                        ; preds = %do.body24
  br label %cond.end, !dbg !1531

cond.false:                                       ; preds = %do.body24
  call void @__assert_fail(i8* getelementptr inbounds ([19 x i8], [19 x i8]* @.str, i32 0, i32 0), i8* getelementptr inbounds ([66 x i8], [66 x i8]* @.str.1, i32 0, i32 0), i32 1136, i8* getelementptr inbounds ([64 x i8], [64 x i8]* @__PRETTY_FUNCTION__.uv_fs_lstat, i32 0, i32 0)) #8, !dbg !1533
  unreachable, !dbg !1533
                                                  ; No predecessors!
  br label %cond.end, !dbg !1535

cond.end:                                         ; preds = %29, %cond.true
  %30 = load void (%struct.uv_fs_s*)*, void (%struct.uv_fs_s*)** %cb.addr, align 8, !dbg !1537
  %cmp26 = icmp eq void (%struct.uv_fs_s*)* %30, null, !dbg !1537
  br i1 %cmp26, label %if.then27, label %if.else, !dbg !1537

if.then27:                                        ; preds = %cond.end
  %31 = load i8*, i8** %path.addr, align 8, !dbg !1540
  %32 = load %struct.uv_fs_s*, %struct.uv_fs_s** %req.addr, align 8, !dbg !1540
  %path28 = getelementptr inbounds %struct.uv_fs_s, %struct.uv_fs_s* %32, i32 0, i32 9, !dbg !1540
  store i8* %31, i8** %path28, align 8, !dbg !1540
  br label %if.end57, !dbg !1540

if.else:                                          ; preds = %cond.end
  %33 = load i8*, i8** %path.addr, align 8, !dbg !1543
  %call = call i8* @uv__strdup(i8* %33), !dbg !1543
  %34 = load %struct.uv_fs_s*, %struct.uv_fs_s** %req.addr, align 8, !dbg !1543
  %path29 = getelementptr inbounds %struct.uv_fs_s, %struct.uv_fs_s* %34, i32 0, i32 9, !dbg !1543
  store i8* %call, i8** %path29, align 8, !dbg !1543
  %35 = load %struct.uv_fs_s*, %struct.uv_fs_s** %req.addr, align 8, !dbg !1543
  %path30 = getelementptr inbounds %struct.uv_fs_s, %struct.uv_fs_s* %35, i32 0, i32 9, !dbg !1543
  %36 = load i8*, i8** %path30, align 8, !dbg !1543
  %cmp31 = icmp eq i8* %36, null, !dbg !1543
  br i1 %cmp31, label %if.then32, label %if.end56, !dbg !1543

if.then32:                                        ; preds = %if.else
  br label %do.body33, !dbg !1546

do.body33:                                        ; preds = %if.then32
  %37 = load %struct.uv_loop_s*, %struct.uv_loop_s** %loop.addr, align 8, !dbg !1550
  %active_reqs34 = getelementptr inbounds %struct.uv_loop_s, %struct.uv_loop_s* %37, i32 0, i32 3, !dbg !1550
  %38 = load %struct.uv_loop_s*, %struct.uv_loop_s** %loop.addr, align 8, !dbg !1550
  %active_reqs35 = getelementptr inbounds %struct.uv_loop_s, %struct.uv_loop_s* %38, i32 0, i32 3, !dbg !1550
  %arrayidx36 = getelementptr inbounds [2 x i8*], [2 x i8*]* %active_reqs35, i64 0, i64 0, !dbg !1550
  %39 = bitcast i8** %arrayidx36 to [2 x i8*]**, !dbg !1550
  %40 = load [2 x i8*]*, [2 x i8*]** %39, align 8, !dbg !1550
  %cmp37 = icmp eq [2 x i8*]* %active_reqs34, %40, !dbg !1550
  %conv = zext i1 %cmp37 to i32, !dbg !1550
  %cmp38 = icmp eq i32 %conv, 0, !dbg !1550
  br i1 %cmp38, label %cond.true40, label %cond.false41, !dbg !1550

cond.true40:                                      ; preds = %do.body33
  br label %cond.end42, !dbg !1553

cond.false41:                                     ; preds = %do.body33
  call void @__assert_fail(i8* getelementptr inbounds ([113 x i8], [113 x i8]* @.str.2, i32 0, i32 0), i8* getelementptr inbounds ([66 x i8], [66 x i8]* @.str.1, i32 0, i32 0), i32 1136, i8* getelementptr inbounds ([64 x i8], [64 x i8]* @__PRETTY_FUNCTION__.uv_fs_lstat, i32 0, i32 0)) #8, !dbg !1555
  unreachable, !dbg !1555
                                                  ; No predecessors!
  br label %cond.end42, !dbg !1557

cond.end42:                                       ; preds = %41, %cond.true40
  br label %do.body43, !dbg !1559

do.body43:                                        ; preds = %cond.end42
  %42 = load %struct.uv_fs_s*, %struct.uv_fs_s** %req.addr, align 8, !dbg !1561
  %active_queue44 = getelementptr inbounds %struct.uv_fs_s, %struct.uv_fs_s* %42, i32 0, i32 2, !dbg !1561
  %arrayidx45 = getelementptr inbounds [2 x i8*], [2 x i8*]* %active_queue44, i64 0, i64 0, !dbg !1561
  %43 = bitcast i8** %arrayidx45 to [2 x i8*]**, !dbg !1561
  %44 = load [2 x i8*]*, [2 x i8*]** %43, align 8, !dbg !1561
  %45 = load %struct.uv_fs_s*, %struct.uv_fs_s** %req.addr, align 8, !dbg !1561
  %active_queue46 = getelementptr inbounds %struct.uv_fs_s, %struct.uv_fs_s* %45, i32 0, i32 2, !dbg !1561
  %arrayidx47 = getelementptr inbounds [2 x i8*], [2 x i8*]* %active_queue46, i64 0, i64 1, !dbg !1561
  %46 = bitcast i8** %arrayidx47 to [2 x i8*]**, !dbg !1561
  %47 = load [2 x i8*]*, [2 x i8*]** %46, align 8, !dbg !1561
  %arrayidx48 = getelementptr inbounds [2 x i8*], [2 x i8*]* %47, i64 0, i64 0, !dbg !1561
  %48 = bitcast i8** %arrayidx48 to [2 x i8*]**, !dbg !1561
  store [2 x i8*]* %44, [2 x i8*]** %48, align 8, !dbg !1561
  %49 = load %struct.uv_fs_s*, %struct.uv_fs_s** %req.addr, align 8, !dbg !1561
  %active_queue49 = getelementptr inbounds %struct.uv_fs_s, %struct.uv_fs_s* %49, i32 0, i32 2, !dbg !1561
  %arrayidx50 = getelementptr inbounds [2 x i8*], [2 x i8*]* %active_queue49, i64 0, i64 1, !dbg !1561
  %50 = bitcast i8** %arrayidx50 to [2 x i8*]**, !dbg !1561
  %51 = load [2 x i8*]*, [2 x i8*]** %50, align 8, !dbg !1561
  %52 = load %struct.uv_fs_s*, %struct.uv_fs_s** %req.addr, align 8, !dbg !1561
  %active_queue51 = getelementptr inbounds %struct.uv_fs_s, %struct.uv_fs_s* %52, i32 0, i32 2, !dbg !1561
  %arrayidx52 = getelementptr inbounds [2 x i8*], [2 x i8*]* %active_queue51, i64 0, i64 0, !dbg !1561
  %53 = bitcast i8** %arrayidx52 to [2 x i8*]**, !dbg !1561
  %54 = load [2 x i8*]*, [2 x i8*]** %53, align 8, !dbg !1561
  %arrayidx53 = getelementptr inbounds [2 x i8*], [2 x i8*]* %54, i64 0, i64 1, !dbg !1561
  %55 = bitcast i8** %arrayidx53 to [2 x i8*]**, !dbg !1561
  store [2 x i8*]* %51, [2 x i8*]** %55, align 8, !dbg !1561
  br label %do.end54, !dbg !1561

do.end54:                                         ; preds = %do.body43
  br label %do.end55, !dbg !1564

do.end55:                                         ; preds = %do.end54
  store i32 -12, i32* %retval, align 4, !dbg !1566
  br label %do.end67, !dbg !1566

if.end56:                                         ; preds = %if.else
  br label %if.end57

if.end57:                                         ; preds = %if.end56, %if.then27
  br label %do.end58, !dbg !1568

do.end58:                                         ; preds = %if.end57
  br label %do.body59, !dbg !1570

do.body59:                                        ; preds = %do.end58
  %56 = load void (%struct.uv_fs_s*)*, void (%struct.uv_fs_s*)** %cb.addr, align 8, !dbg !1571
  %cmp60 = icmp ne void (%struct.uv_fs_s*)* %56, null, !dbg !1571
  br i1 %cmp60, label %if.then62, label %if.else63, !dbg !1571

if.then62:                                        ; preds = %do.body59
  %57 = load %struct.uv_loop_s*, %struct.uv_loop_s** %loop.addr, align 8, !dbg !1575
  %58 = load %struct.uv_fs_s*, %struct.uv_fs_s** %req.addr, align 8, !dbg !1575
  %work_req = getelementptr inbounds %struct.uv_fs_s, %struct.uv_fs_s* %58, i32 0, i32 22, !dbg !1575
  call void @uv__work_submit(%struct.uv_loop_s* %57, %struct.uv__work* %work_req, void (%struct.uv__work*)* @uv__fs_work, void (%struct.uv__work*, i32)* @uv__fs_done), !dbg !1575
  store i32 0, i32* %retval, align 4, !dbg !1575
  br label %do.end67, !dbg !1575

if.else63:                                        ; preds = %do.body59
  %59 = load %struct.uv_fs_s*, %struct.uv_fs_s** %req.addr, align 8, !dbg !1578
  %work_req64 = getelementptr inbounds %struct.uv_fs_s, %struct.uv_fs_s* %59, i32 0, i32 22, !dbg !1578
  call void @uv__fs_work(%struct.uv__work* %work_req64), !dbg !1578
  %60 = load %struct.uv_fs_s*, %struct.uv_fs_s** %req.addr, align 8, !dbg !1578
  %result65 = getelementptr inbounds %struct.uv_fs_s, %struct.uv_fs_s* %60, i32 0, i32 7, !dbg !1578
  %61 = load i64, i64* %result65, align 8, !dbg !1578
  %conv66 = trunc i64 %61 to i32, !dbg !1578
  store i32 %conv66, i32* %retval, align 4, !dbg !1578
  br label %do.end67, !dbg !1578

do.end67:                                         ; preds = %do.end55, %if.then62, %if.else63
  %62 = load i32, i32* %retval, align 4, !dbg !1581
  ret i32 %62, !dbg !1581
}

; Function Attrs: nounwind uwtable
define i32 @uv_fs_link(%struct.uv_loop_s* %loop, %struct.uv_fs_s* %req, i8* %path, i8* %new_path, void (%struct.uv_fs_s*)* %cb) #0 !dbg !445 {
entry:
  %retval = alloca i32, align 4
  %loop.addr = alloca %struct.uv_loop_s*, align 8
  %req.addr = alloca %struct.uv_fs_s*, align 8
  %path.addr = alloca i8*, align 8
  %new_path.addr = alloca i8*, align 8
  %cb.addr = alloca void (%struct.uv_fs_s*)*, align 8
  %path_len = alloca i64, align 8
  %new_path_len = alloca i64, align 8
  store %struct.uv_loop_s* %loop, %struct.uv_loop_s** %loop.addr, align 8
  call void @llvm.dbg.declare(metadata %struct.uv_loop_s** %loop.addr, metadata !1582, metadata !580), !dbg !1583
  store %struct.uv_fs_s* %req, %struct.uv_fs_s** %req.addr, align 8
  call void @llvm.dbg.declare(metadata %struct.uv_fs_s** %req.addr, metadata !1584, metadata !580), !dbg !1585
  store i8* %path, i8** %path.addr, align 8
  call void @llvm.dbg.declare(metadata i8** %path.addr, metadata !1586, metadata !580), !dbg !1587
  store i8* %new_path, i8** %new_path.addr, align 8
  call void @llvm.dbg.declare(metadata i8** %new_path.addr, metadata !1588, metadata !580), !dbg !1589
  store void (%struct.uv_fs_s*)* %cb, void (%struct.uv_fs_s*)** %cb.addr, align 8
  call void @llvm.dbg.declare(metadata void (%struct.uv_fs_s*)** %cb.addr, metadata !1590, metadata !580), !dbg !1591
  br label %do.body, !dbg !1592

do.body:                                          ; preds = %entry
  %0 = load %struct.uv_fs_s*, %struct.uv_fs_s** %req.addr, align 8, !dbg !1593
  %type = getelementptr inbounds %struct.uv_fs_s, %struct.uv_fs_s* %0, i32 0, i32 1, !dbg !1593
  store i32 6, i32* %type, align 8, !dbg !1593
  %1 = load void (%struct.uv_fs_s*)*, void (%struct.uv_fs_s*)** %cb.addr, align 8, !dbg !1593
  %cmp = icmp ne void (%struct.uv_fs_s*)* %1, null, !dbg !1593
  br i1 %cmp, label %if.then, label %if.end, !dbg !1593

if.then:                                          ; preds = %do.body
  br label %do.body1, !dbg !1596

do.body1:                                         ; preds = %if.then
  br label %do.body2, !dbg !1599

do.body2:                                         ; preds = %do.body1
  %2 = load %struct.uv_fs_s*, %struct.uv_fs_s** %req.addr, align 8, !dbg !1602
  %type3 = getelementptr inbounds %struct.uv_fs_s, %struct.uv_fs_s* %2, i32 0, i32 1, !dbg !1602
  store i32 6, i32* %type3, align 8, !dbg !1602
  br label %do.end, !dbg !1602

do.end:                                           ; preds = %do.body2
  br label %do.body4, !dbg !1605

do.body4:                                         ; preds = %do.end
  br label %do.body5, !dbg !1607

do.body5:                                         ; preds = %do.body4
  %3 = load %struct.uv_loop_s*, %struct.uv_loop_s** %loop.addr, align 8, !dbg !1610
  %active_reqs = getelementptr inbounds %struct.uv_loop_s, %struct.uv_loop_s* %3, i32 0, i32 3, !dbg !1610
  %4 = load %struct.uv_fs_s*, %struct.uv_fs_s** %req.addr, align 8, !dbg !1610
  %active_queue = getelementptr inbounds %struct.uv_fs_s, %struct.uv_fs_s* %4, i32 0, i32 2, !dbg !1610
  %arrayidx = getelementptr inbounds [2 x i8*], [2 x i8*]* %active_queue, i64 0, i64 0, !dbg !1610
  %5 = bitcast i8** %arrayidx to [2 x i8*]**, !dbg !1610
  store [2 x i8*]* %active_reqs, [2 x i8*]** %5, align 8, !dbg !1610
  %6 = load %struct.uv_loop_s*, %struct.uv_loop_s** %loop.addr, align 8, !dbg !1610
  %active_reqs6 = getelementptr inbounds %struct.uv_loop_s, %struct.uv_loop_s* %6, i32 0, i32 3, !dbg !1610
  %arrayidx7 = getelementptr inbounds [2 x i8*], [2 x i8*]* %active_reqs6, i64 0, i64 1, !dbg !1610
  %7 = bitcast i8** %arrayidx7 to [2 x i8*]**, !dbg !1610
  %8 = load [2 x i8*]*, [2 x i8*]** %7, align 8, !dbg !1610
  %9 = load %struct.uv_fs_s*, %struct.uv_fs_s** %req.addr, align 8, !dbg !1610
  %active_queue8 = getelementptr inbounds %struct.uv_fs_s, %struct.uv_fs_s* %9, i32 0, i32 2, !dbg !1610
  %arrayidx9 = getelementptr inbounds [2 x i8*], [2 x i8*]* %active_queue8, i64 0, i64 1, !dbg !1610
  %10 = bitcast i8** %arrayidx9 to [2 x i8*]**, !dbg !1610
  store [2 x i8*]* %8, [2 x i8*]** %10, align 8, !dbg !1610
  %11 = load %struct.uv_fs_s*, %struct.uv_fs_s** %req.addr, align 8, !dbg !1610
  %active_queue10 = getelementptr inbounds %struct.uv_fs_s, %struct.uv_fs_s* %11, i32 0, i32 2, !dbg !1610
  %12 = load %struct.uv_fs_s*, %struct.uv_fs_s** %req.addr, align 8, !dbg !1610
  %active_queue11 = getelementptr inbounds %struct.uv_fs_s, %struct.uv_fs_s* %12, i32 0, i32 2, !dbg !1610
  %arrayidx12 = getelementptr inbounds [2 x i8*], [2 x i8*]* %active_queue11, i64 0, i64 1, !dbg !1610
  %13 = bitcast i8** %arrayidx12 to [2 x i8*]**, !dbg !1610
  %14 = load [2 x i8*]*, [2 x i8*]** %13, align 8, !dbg !1610
  %arrayidx13 = getelementptr inbounds [2 x i8*], [2 x i8*]* %14, i64 0, i64 0, !dbg !1610
  %15 = bitcast i8** %arrayidx13 to [2 x i8*]**, !dbg !1610
  store [2 x i8*]* %active_queue10, [2 x i8*]** %15, align 8, !dbg !1610
  %16 = load %struct.uv_fs_s*, %struct.uv_fs_s** %req.addr, align 8, !dbg !1610
  %active_queue14 = getelementptr inbounds %struct.uv_fs_s, %struct.uv_fs_s* %16, i32 0, i32 2, !dbg !1610
  %17 = load %struct.uv_loop_s*, %struct.uv_loop_s** %loop.addr, align 8, !dbg !1610
  %active_reqs15 = getelementptr inbounds %struct.uv_loop_s, %struct.uv_loop_s* %17, i32 0, i32 3, !dbg !1610
  %arrayidx16 = getelementptr inbounds [2 x i8*], [2 x i8*]* %active_reqs15, i64 0, i64 1, !dbg !1610
  %18 = bitcast i8** %arrayidx16 to [2 x i8*]**, !dbg !1610
  store [2 x i8*]* %active_queue14, [2 x i8*]** %18, align 8, !dbg !1610
  br label %do.end17, !dbg !1610

do.end17:                                         ; preds = %do.body5
  br label %do.end18, !dbg !1613

do.end18:                                         ; preds = %do.end17
  br label %do.end19, !dbg !1615

do.end19:                                         ; preds = %do.end18
  br label %if.end, !dbg !1617

if.end:                                           ; preds = %do.end19, %do.body
  %19 = load %struct.uv_fs_s*, %struct.uv_fs_s** %req.addr, align 8, !dbg !1619
  %fs_type = getelementptr inbounds %struct.uv_fs_s, %struct.uv_fs_s* %19, i32 0, i32 4, !dbg !1619
  store i32 23, i32* %fs_type, align 8, !dbg !1619
  %20 = load %struct.uv_fs_s*, %struct.uv_fs_s** %req.addr, align 8, !dbg !1619
  %result = getelementptr inbounds %struct.uv_fs_s, %struct.uv_fs_s* %20, i32 0, i32 7, !dbg !1619
  store i64 0, i64* %result, align 8, !dbg !1619
  %21 = load %struct.uv_fs_s*, %struct.uv_fs_s** %req.addr, align 8, !dbg !1619
  %ptr = getelementptr inbounds %struct.uv_fs_s, %struct.uv_fs_s* %21, i32 0, i32 8, !dbg !1619
  store i8* null, i8** %ptr, align 8, !dbg !1619
  %22 = load %struct.uv_loop_s*, %struct.uv_loop_s** %loop.addr, align 8, !dbg !1619
  %23 = load %struct.uv_fs_s*, %struct.uv_fs_s** %req.addr, align 8, !dbg !1619
  %loop20 = getelementptr inbounds %struct.uv_fs_s, %struct.uv_fs_s* %23, i32 0, i32 5, !dbg !1619
  store %struct.uv_loop_s* %22, %struct.uv_loop_s** %loop20, align 8, !dbg !1619
  %24 = load %struct.uv_fs_s*, %struct.uv_fs_s** %req.addr, align 8, !dbg !1619
  %path21 = getelementptr inbounds %struct.uv_fs_s, %struct.uv_fs_s* %24, i32 0, i32 9, !dbg !1619
  store i8* null, i8** %path21, align 8, !dbg !1619
  %25 = load %struct.uv_fs_s*, %struct.uv_fs_s** %req.addr, align 8, !dbg !1619
  %new_path22 = getelementptr inbounds %struct.uv_fs_s, %struct.uv_fs_s* %25, i32 0, i32 11, !dbg !1619
  store i8* null, i8** %new_path22, align 8, !dbg !1619
  %26 = load void (%struct.uv_fs_s*)*, void (%struct.uv_fs_s*)** %cb.addr, align 8, !dbg !1619
  %27 = load %struct.uv_fs_s*, %struct.uv_fs_s** %req.addr, align 8, !dbg !1619
  %cb23 = getelementptr inbounds %struct.uv_fs_s, %struct.uv_fs_s* %27, i32 0, i32 6, !dbg !1619
  store void (%struct.uv_fs_s*)* %26, void (%struct.uv_fs_s*)** %cb23, align 8, !dbg !1619
  br label %do.end24, !dbg !1619

do.end24:                                         ; preds = %if.end
  br label %do.body25, !dbg !1621

do.body25:                                        ; preds = %do.end24
  %28 = load void (%struct.uv_fs_s*)*, void (%struct.uv_fs_s*)** %cb.addr, align 8, !dbg !1622
  %cmp26 = icmp eq void (%struct.uv_fs_s*)* %28, null, !dbg !1622
  br i1 %cmp26, label %if.then27, label %if.else, !dbg !1622

if.then27:                                        ; preds = %do.body25
  %29 = load i8*, i8** %path.addr, align 8, !dbg !1626
  %30 = load %struct.uv_fs_s*, %struct.uv_fs_s** %req.addr, align 8, !dbg !1626
  %path28 = getelementptr inbounds %struct.uv_fs_s, %struct.uv_fs_s* %30, i32 0, i32 9, !dbg !1626
  store i8* %29, i8** %path28, align 8, !dbg !1626
  %31 = load i8*, i8** %new_path.addr, align 8, !dbg !1626
  %32 = load %struct.uv_fs_s*, %struct.uv_fs_s** %req.addr, align 8, !dbg !1626
  %new_path29 = getelementptr inbounds %struct.uv_fs_s, %struct.uv_fs_s* %32, i32 0, i32 11, !dbg !1626
  store i8* %31, i8** %new_path29, align 8, !dbg !1626
  br label %if.end63, !dbg !1626

if.else:                                          ; preds = %do.body25
  call void @llvm.dbg.declare(metadata i64* %path_len, metadata !1629, metadata !580), !dbg !1631
  call void @llvm.dbg.declare(metadata i64* %new_path_len, metadata !1632, metadata !580), !dbg !1631
  %33 = load i8*, i8** %path.addr, align 8, !dbg !1633
  %call = call i64 @strlen(i8* %33) #10, !dbg !1633
  %add = add i64 %call, 1, !dbg !1633
  store i64 %add, i64* %path_len, align 8, !dbg !1633
  %34 = load i8*, i8** %new_path.addr, align 8, !dbg !1633
  %call30 = call i64 @strlen(i8* %34) #10, !dbg !1635
  %add31 = add i64 %call30, 1, !dbg !1633
  store i64 %add31, i64* %new_path_len, align 8, !dbg !1633
  %35 = load i64, i64* %path_len, align 8, !dbg !1633
  %36 = load i64, i64* %new_path_len, align 8, !dbg !1633
  %add32 = add i64 %35, %36, !dbg !1633
  %call33 = call i8* @uv__malloc(i64 %add32), !dbg !1637
  %37 = load %struct.uv_fs_s*, %struct.uv_fs_s** %req.addr, align 8, !dbg !1633
  %path34 = getelementptr inbounds %struct.uv_fs_s, %struct.uv_fs_s* %37, i32 0, i32 9, !dbg !1633
  store i8* %call33, i8** %path34, align 8, !dbg !1633
  %38 = load %struct.uv_fs_s*, %struct.uv_fs_s** %req.addr, align 8, !dbg !1633
  %path35 = getelementptr inbounds %struct.uv_fs_s, %struct.uv_fs_s* %38, i32 0, i32 9, !dbg !1633
  %39 = load i8*, i8** %path35, align 8, !dbg !1633
  %cmp36 = icmp eq i8* %39, null, !dbg !1633
  br i1 %cmp36, label %if.then37, label %if.end58, !dbg !1633

if.then37:                                        ; preds = %if.else
  br label %do.body38, !dbg !1639

do.body38:                                        ; preds = %if.then37
  %40 = load %struct.uv_loop_s*, %struct.uv_loop_s** %loop.addr, align 8, !dbg !1643
  %active_reqs39 = getelementptr inbounds %struct.uv_loop_s, %struct.uv_loop_s* %40, i32 0, i32 3, !dbg !1643
  %41 = load %struct.uv_loop_s*, %struct.uv_loop_s** %loop.addr, align 8, !dbg !1643
  %active_reqs40 = getelementptr inbounds %struct.uv_loop_s, %struct.uv_loop_s* %41, i32 0, i32 3, !dbg !1643
  %arrayidx41 = getelementptr inbounds [2 x i8*], [2 x i8*]* %active_reqs40, i64 0, i64 0, !dbg !1643
  %42 = bitcast i8** %arrayidx41 to [2 x i8*]**, !dbg !1643
  %43 = load [2 x i8*]*, [2 x i8*]** %42, align 8, !dbg !1643
  %cmp42 = icmp eq [2 x i8*]* %active_reqs39, %43, !dbg !1643
  %conv = zext i1 %cmp42 to i32, !dbg !1643
  %cmp43 = icmp eq i32 %conv, 0, !dbg !1643
  br i1 %cmp43, label %cond.true, label %cond.false, !dbg !1643

cond.true:                                        ; preds = %do.body38
  br label %cond.end, !dbg !1646

cond.false:                                       ; preds = %do.body38
  call void @__assert_fail(i8* getelementptr inbounds ([113 x i8], [113 x i8]* @.str.2, i32 0, i32 0), i8* getelementptr inbounds ([66 x i8], [66 x i8]* @.str.1, i32 0, i32 0), i32 1147, i8* getelementptr inbounds ([77 x i8], [77 x i8]* @__PRETTY_FUNCTION__.uv_fs_link, i32 0, i32 0)) #8, !dbg !1648
  unreachable, !dbg !1648
                                                  ; No predecessors!
  br label %cond.end, !dbg !1650

cond.end:                                         ; preds = %44, %cond.true
  br label %do.body45, !dbg !1652

do.body45:                                        ; preds = %cond.end
  %45 = load %struct.uv_fs_s*, %struct.uv_fs_s** %req.addr, align 8, !dbg !1654
  %active_queue46 = getelementptr inbounds %struct.uv_fs_s, %struct.uv_fs_s* %45, i32 0, i32 2, !dbg !1654
  %arrayidx47 = getelementptr inbounds [2 x i8*], [2 x i8*]* %active_queue46, i64 0, i64 0, !dbg !1654
  %46 = bitcast i8** %arrayidx47 to [2 x i8*]**, !dbg !1654
  %47 = load [2 x i8*]*, [2 x i8*]** %46, align 8, !dbg !1654
  %48 = load %struct.uv_fs_s*, %struct.uv_fs_s** %req.addr, align 8, !dbg !1654
  %active_queue48 = getelementptr inbounds %struct.uv_fs_s, %struct.uv_fs_s* %48, i32 0, i32 2, !dbg !1654
  %arrayidx49 = getelementptr inbounds [2 x i8*], [2 x i8*]* %active_queue48, i64 0, i64 1, !dbg !1654
  %49 = bitcast i8** %arrayidx49 to [2 x i8*]**, !dbg !1654
  %50 = load [2 x i8*]*, [2 x i8*]** %49, align 8, !dbg !1654
  %arrayidx50 = getelementptr inbounds [2 x i8*], [2 x i8*]* %50, i64 0, i64 0, !dbg !1654
  %51 = bitcast i8** %arrayidx50 to [2 x i8*]**, !dbg !1654
  store [2 x i8*]* %47, [2 x i8*]** %51, align 8, !dbg !1654
  %52 = load %struct.uv_fs_s*, %struct.uv_fs_s** %req.addr, align 8, !dbg !1654
  %active_queue51 = getelementptr inbounds %struct.uv_fs_s, %struct.uv_fs_s* %52, i32 0, i32 2, !dbg !1654
  %arrayidx52 = getelementptr inbounds [2 x i8*], [2 x i8*]* %active_queue51, i64 0, i64 1, !dbg !1654
  %53 = bitcast i8** %arrayidx52 to [2 x i8*]**, !dbg !1654
  %54 = load [2 x i8*]*, [2 x i8*]** %53, align 8, !dbg !1654
  %55 = load %struct.uv_fs_s*, %struct.uv_fs_s** %req.addr, align 8, !dbg !1654
  %active_queue53 = getelementptr inbounds %struct.uv_fs_s, %struct.uv_fs_s* %55, i32 0, i32 2, !dbg !1654
  %arrayidx54 = getelementptr inbounds [2 x i8*], [2 x i8*]* %active_queue53, i64 0, i64 0, !dbg !1654
  %56 = bitcast i8** %arrayidx54 to [2 x i8*]**, !dbg !1654
  %57 = load [2 x i8*]*, [2 x i8*]** %56, align 8, !dbg !1654
  %arrayidx55 = getelementptr inbounds [2 x i8*], [2 x i8*]* %57, i64 0, i64 1, !dbg !1654
  %58 = bitcast i8** %arrayidx55 to [2 x i8*]**, !dbg !1654
  store [2 x i8*]* %54, [2 x i8*]** %58, align 8, !dbg !1654
  br label %do.end56, !dbg !1654

do.end56:                                         ; preds = %do.body45
  br label %do.end57, !dbg !1657

do.end57:                                         ; preds = %do.end56
  store i32 -12, i32* %retval, align 4, !dbg !1659
  br label %do.end73, !dbg !1659

if.end58:                                         ; preds = %if.else
  %59 = load %struct.uv_fs_s*, %struct.uv_fs_s** %req.addr, align 8, !dbg !1661
  %path59 = getelementptr inbounds %struct.uv_fs_s, %struct.uv_fs_s* %59, i32 0, i32 9, !dbg !1661
  %60 = load i8*, i8** %path59, align 8, !dbg !1661
  %61 = load i64, i64* %path_len, align 8, !dbg !1661
  %add.ptr = getelementptr inbounds i8, i8* %60, i64 %61, !dbg !1661
  %62 = load %struct.uv_fs_s*, %struct.uv_fs_s** %req.addr, align 8, !dbg !1661
  %new_path60 = getelementptr inbounds %struct.uv_fs_s, %struct.uv_fs_s* %62, i32 0, i32 11, !dbg !1661
  store i8* %add.ptr, i8** %new_path60, align 8, !dbg !1661
  %63 = load %struct.uv_fs_s*, %struct.uv_fs_s** %req.addr, align 8, !dbg !1661
  %path61 = getelementptr inbounds %struct.uv_fs_s, %struct.uv_fs_s* %63, i32 0, i32 9, !dbg !1661
  %64 = load i8*, i8** %path61, align 8, !dbg !1661
  %65 = load i8*, i8** %path.addr, align 8, !dbg !1661
  %66 = load i64, i64* %path_len, align 8, !dbg !1661
  call void @llvm.memcpy.p0i8.p0i8.i64(i8* %64, i8* %65, i64 %66, i32 1, i1 false), !dbg !1661
  %67 = load %struct.uv_fs_s*, %struct.uv_fs_s** %req.addr, align 8, !dbg !1661
  %new_path62 = getelementptr inbounds %struct.uv_fs_s, %struct.uv_fs_s* %67, i32 0, i32 11, !dbg !1661
  %68 = load i8*, i8** %new_path62, align 8, !dbg !1661
  %69 = load i8*, i8** %new_path.addr, align 8, !dbg !1661
  %70 = load i64, i64* %new_path_len, align 8, !dbg !1661
  call void @llvm.memcpy.p0i8.p0i8.i64(i8* %68, i8* %69, i64 %70, i32 1, i1 false), !dbg !1663
  br label %if.end63

if.end63:                                         ; preds = %if.end58, %if.then27
  br label %do.end64, !dbg !1665

do.end64:                                         ; preds = %if.end63
  br label %do.body65, !dbg !1667

do.body65:                                        ; preds = %do.end64
  %71 = load void (%struct.uv_fs_s*)*, void (%struct.uv_fs_s*)** %cb.addr, align 8, !dbg !1668
  %cmp66 = icmp ne void (%struct.uv_fs_s*)* %71, null, !dbg !1668
  br i1 %cmp66, label %if.then68, label %if.else69, !dbg !1668

if.then68:                                        ; preds = %do.body65
  %72 = load %struct.uv_loop_s*, %struct.uv_loop_s** %loop.addr, align 8, !dbg !1672
  %73 = load %struct.uv_fs_s*, %struct.uv_fs_s** %req.addr, align 8, !dbg !1672
  %work_req = getelementptr inbounds %struct.uv_fs_s, %struct.uv_fs_s* %73, i32 0, i32 22, !dbg !1672
  call void @uv__work_submit(%struct.uv_loop_s* %72, %struct.uv__work* %work_req, void (%struct.uv__work*)* @uv__fs_work, void (%struct.uv__work*, i32)* @uv__fs_done), !dbg !1672
  store i32 0, i32* %retval, align 4, !dbg !1672
  br label %do.end73, !dbg !1672

if.else69:                                        ; preds = %do.body65
  %74 = load %struct.uv_fs_s*, %struct.uv_fs_s** %req.addr, align 8, !dbg !1675
  %work_req70 = getelementptr inbounds %struct.uv_fs_s, %struct.uv_fs_s* %74, i32 0, i32 22, !dbg !1675
  call void @uv__fs_work(%struct.uv__work* %work_req70), !dbg !1675
  %75 = load %struct.uv_fs_s*, %struct.uv_fs_s** %req.addr, align 8, !dbg !1675
  %result71 = getelementptr inbounds %struct.uv_fs_s, %struct.uv_fs_s* %75, i32 0, i32 7, !dbg !1675
  %76 = load i64, i64* %result71, align 8, !dbg !1675
  %conv72 = trunc i64 %76 to i32, !dbg !1675
  store i32 %conv72, i32* %retval, align 4, !dbg !1675
  br label %do.end73, !dbg !1675

do.end73:                                         ; preds = %do.end57, %if.then68, %if.else69
  %77 = load i32, i32* %retval, align 4, !dbg !1678
  ret i32 %77, !dbg !1678
}

; Function Attrs: nounwind readonly
declare i64 @strlen(i8*) #4

declare i8* @uv__malloc(i64) #3

; Function Attrs: argmemonly nounwind
declare void @llvm.memcpy.p0i8.p0i8.i64(i8* nocapture, i8* nocapture readonly, i64, i32, i1) #5

; Function Attrs: nounwind uwtable
define i32 @uv_fs_mkdir(%struct.uv_loop_s* %loop, %struct.uv_fs_s* %req, i8* %path, i32 %mode, void (%struct.uv_fs_s*)* %cb) #0 !dbg !448 {
entry:
  %retval = alloca i32, align 4
  %loop.addr = alloca %struct.uv_loop_s*, align 8
  %req.addr = alloca %struct.uv_fs_s*, align 8
  %path.addr = alloca i8*, align 8
  %mode.addr = alloca i32, align 4
  %cb.addr = alloca void (%struct.uv_fs_s*)*, align 8
  store %struct.uv_loop_s* %loop, %struct.uv_loop_s** %loop.addr, align 8
  call void @llvm.dbg.declare(metadata %struct.uv_loop_s** %loop.addr, metadata !1679, metadata !580), !dbg !1680
  store %struct.uv_fs_s* %req, %struct.uv_fs_s** %req.addr, align 8
  call void @llvm.dbg.declare(metadata %struct.uv_fs_s** %req.addr, metadata !1681, metadata !580), !dbg !1682
  store i8* %path, i8** %path.addr, align 8
  call void @llvm.dbg.declare(metadata i8** %path.addr, metadata !1683, metadata !580), !dbg !1684
  store i32 %mode, i32* %mode.addr, align 4
  call void @llvm.dbg.declare(metadata i32* %mode.addr, metadata !1685, metadata !580), !dbg !1686
  store void (%struct.uv_fs_s*)* %cb, void (%struct.uv_fs_s*)** %cb.addr, align 8
  call void @llvm.dbg.declare(metadata void (%struct.uv_fs_s*)** %cb.addr, metadata !1687, metadata !580), !dbg !1688
  br label %do.body, !dbg !1689

do.body:                                          ; preds = %entry
  %0 = load %struct.uv_fs_s*, %struct.uv_fs_s** %req.addr, align 8, !dbg !1690
  %type = getelementptr inbounds %struct.uv_fs_s, %struct.uv_fs_s* %0, i32 0, i32 1, !dbg !1690
  store i32 6, i32* %type, align 8, !dbg !1690
  %1 = load void (%struct.uv_fs_s*)*, void (%struct.uv_fs_s*)** %cb.addr, align 8, !dbg !1690
  %cmp = icmp ne void (%struct.uv_fs_s*)* %1, null, !dbg !1690
  br i1 %cmp, label %if.then, label %if.end, !dbg !1690

if.then:                                          ; preds = %do.body
  br label %do.body1, !dbg !1693

do.body1:                                         ; preds = %if.then
  br label %do.body2, !dbg !1696

do.body2:                                         ; preds = %do.body1
  %2 = load %struct.uv_fs_s*, %struct.uv_fs_s** %req.addr, align 8, !dbg !1699
  %type3 = getelementptr inbounds %struct.uv_fs_s, %struct.uv_fs_s* %2, i32 0, i32 1, !dbg !1699
  store i32 6, i32* %type3, align 8, !dbg !1699
  br label %do.end, !dbg !1699

do.end:                                           ; preds = %do.body2
  br label %do.body4, !dbg !1702

do.body4:                                         ; preds = %do.end
  br label %do.body5, !dbg !1704

do.body5:                                         ; preds = %do.body4
  %3 = load %struct.uv_loop_s*, %struct.uv_loop_s** %loop.addr, align 8, !dbg !1707
  %active_reqs = getelementptr inbounds %struct.uv_loop_s, %struct.uv_loop_s* %3, i32 0, i32 3, !dbg !1707
  %4 = load %struct.uv_fs_s*, %struct.uv_fs_s** %req.addr, align 8, !dbg !1707
  %active_queue = getelementptr inbounds %struct.uv_fs_s, %struct.uv_fs_s* %4, i32 0, i32 2, !dbg !1707
  %arrayidx = getelementptr inbounds [2 x i8*], [2 x i8*]* %active_queue, i64 0, i64 0, !dbg !1707
  %5 = bitcast i8** %arrayidx to [2 x i8*]**, !dbg !1707
  store [2 x i8*]* %active_reqs, [2 x i8*]** %5, align 8, !dbg !1707
  %6 = load %struct.uv_loop_s*, %struct.uv_loop_s** %loop.addr, align 8, !dbg !1707
  %active_reqs6 = getelementptr inbounds %struct.uv_loop_s, %struct.uv_loop_s* %6, i32 0, i32 3, !dbg !1707
  %arrayidx7 = getelementptr inbounds [2 x i8*], [2 x i8*]* %active_reqs6, i64 0, i64 1, !dbg !1707
  %7 = bitcast i8** %arrayidx7 to [2 x i8*]**, !dbg !1707
  %8 = load [2 x i8*]*, [2 x i8*]** %7, align 8, !dbg !1707
  %9 = load %struct.uv_fs_s*, %struct.uv_fs_s** %req.addr, align 8, !dbg !1707
  %active_queue8 = getelementptr inbounds %struct.uv_fs_s, %struct.uv_fs_s* %9, i32 0, i32 2, !dbg !1707
  %arrayidx9 = getelementptr inbounds [2 x i8*], [2 x i8*]* %active_queue8, i64 0, i64 1, !dbg !1707
  %10 = bitcast i8** %arrayidx9 to [2 x i8*]**, !dbg !1707
  store [2 x i8*]* %8, [2 x i8*]** %10, align 8, !dbg !1707
  %11 = load %struct.uv_fs_s*, %struct.uv_fs_s** %req.addr, align 8, !dbg !1707
  %active_queue10 = getelementptr inbounds %struct.uv_fs_s, %struct.uv_fs_s* %11, i32 0, i32 2, !dbg !1707
  %12 = load %struct.uv_fs_s*, %struct.uv_fs_s** %req.addr, align 8, !dbg !1707
  %active_queue11 = getelementptr inbounds %struct.uv_fs_s, %struct.uv_fs_s* %12, i32 0, i32 2, !dbg !1707
  %arrayidx12 = getelementptr inbounds [2 x i8*], [2 x i8*]* %active_queue11, i64 0, i64 1, !dbg !1707
  %13 = bitcast i8** %arrayidx12 to [2 x i8*]**, !dbg !1707
  %14 = load [2 x i8*]*, [2 x i8*]** %13, align 8, !dbg !1707
  %arrayidx13 = getelementptr inbounds [2 x i8*], [2 x i8*]* %14, i64 0, i64 0, !dbg !1707
  %15 = bitcast i8** %arrayidx13 to [2 x i8*]**, !dbg !1707
  store [2 x i8*]* %active_queue10, [2 x i8*]** %15, align 8, !dbg !1707
  %16 = load %struct.uv_fs_s*, %struct.uv_fs_s** %req.addr, align 8, !dbg !1707
  %active_queue14 = getelementptr inbounds %struct.uv_fs_s, %struct.uv_fs_s* %16, i32 0, i32 2, !dbg !1707
  %17 = load %struct.uv_loop_s*, %struct.uv_loop_s** %loop.addr, align 8, !dbg !1707
  %active_reqs15 = getelementptr inbounds %struct.uv_loop_s, %struct.uv_loop_s* %17, i32 0, i32 3, !dbg !1707
  %arrayidx16 = getelementptr inbounds [2 x i8*], [2 x i8*]* %active_reqs15, i64 0, i64 1, !dbg !1707
  %18 = bitcast i8** %arrayidx16 to [2 x i8*]**, !dbg !1707
  store [2 x i8*]* %active_queue14, [2 x i8*]** %18, align 8, !dbg !1707
  br label %do.end17, !dbg !1707

do.end17:                                         ; preds = %do.body5
  br label %do.end18, !dbg !1710

do.end18:                                         ; preds = %do.end17
  br label %do.end19, !dbg !1712

do.end19:                                         ; preds = %do.end18
  br label %if.end, !dbg !1714

if.end:                                           ; preds = %do.end19, %do.body
  %19 = load %struct.uv_fs_s*, %struct.uv_fs_s** %req.addr, align 8, !dbg !1716
  %fs_type = getelementptr inbounds %struct.uv_fs_s, %struct.uv_fs_s* %19, i32 0, i32 4, !dbg !1716
  store i32 19, i32* %fs_type, align 8, !dbg !1716
  %20 = load %struct.uv_fs_s*, %struct.uv_fs_s** %req.addr, align 8, !dbg !1716
  %result = getelementptr inbounds %struct.uv_fs_s, %struct.uv_fs_s* %20, i32 0, i32 7, !dbg !1716
  store i64 0, i64* %result, align 8, !dbg !1716
  %21 = load %struct.uv_fs_s*, %struct.uv_fs_s** %req.addr, align 8, !dbg !1716
  %ptr = getelementptr inbounds %struct.uv_fs_s, %struct.uv_fs_s* %21, i32 0, i32 8, !dbg !1716
  store i8* null, i8** %ptr, align 8, !dbg !1716
  %22 = load %struct.uv_loop_s*, %struct.uv_loop_s** %loop.addr, align 8, !dbg !1716
  %23 = load %struct.uv_fs_s*, %struct.uv_fs_s** %req.addr, align 8, !dbg !1716
  %loop20 = getelementptr inbounds %struct.uv_fs_s, %struct.uv_fs_s* %23, i32 0, i32 5, !dbg !1716
  store %struct.uv_loop_s* %22, %struct.uv_loop_s** %loop20, align 8, !dbg !1716
  %24 = load %struct.uv_fs_s*, %struct.uv_fs_s** %req.addr, align 8, !dbg !1716
  %path21 = getelementptr inbounds %struct.uv_fs_s, %struct.uv_fs_s* %24, i32 0, i32 9, !dbg !1716
  store i8* null, i8** %path21, align 8, !dbg !1716
  %25 = load %struct.uv_fs_s*, %struct.uv_fs_s** %req.addr, align 8, !dbg !1716
  %new_path = getelementptr inbounds %struct.uv_fs_s, %struct.uv_fs_s* %25, i32 0, i32 11, !dbg !1716
  store i8* null, i8** %new_path, align 8, !dbg !1716
  %26 = load void (%struct.uv_fs_s*)*, void (%struct.uv_fs_s*)** %cb.addr, align 8, !dbg !1716
  %27 = load %struct.uv_fs_s*, %struct.uv_fs_s** %req.addr, align 8, !dbg !1716
  %cb22 = getelementptr inbounds %struct.uv_fs_s, %struct.uv_fs_s* %27, i32 0, i32 6, !dbg !1716
  store void (%struct.uv_fs_s*)* %26, void (%struct.uv_fs_s*)** %cb22, align 8, !dbg !1716
  br label %do.end23, !dbg !1716

do.end23:                                         ; preds = %if.end
  br label %do.body24, !dbg !1718

do.body24:                                        ; preds = %do.end23
  %28 = load i8*, i8** %path.addr, align 8, !dbg !1719
  %cmp25 = icmp ne i8* %28, null, !dbg !1719
  br i1 %cmp25, label %cond.true, label %cond.false, !dbg !1719

cond.true:                                        ; preds = %do.body24
  br label %cond.end, !dbg !1722

cond.false:                                       ; preds = %do.body24
  call void @__assert_fail(i8* getelementptr inbounds ([19 x i8], [19 x i8]* @.str, i32 0, i32 0), i8* getelementptr inbounds ([66 x i8], [66 x i8]* @.str.1, i32 0, i32 0), i32 1158, i8* getelementptr inbounds ([69 x i8], [69 x i8]* @__PRETTY_FUNCTION__.uv_fs_mkdir, i32 0, i32 0)) #8, !dbg !1724
  unreachable, !dbg !1724
                                                  ; No predecessors!
  br label %cond.end, !dbg !1726

cond.end:                                         ; preds = %29, %cond.true
  %30 = load void (%struct.uv_fs_s*)*, void (%struct.uv_fs_s*)** %cb.addr, align 8, !dbg !1728
  %cmp26 = icmp eq void (%struct.uv_fs_s*)* %30, null, !dbg !1728
  br i1 %cmp26, label %if.then27, label %if.else, !dbg !1728

if.then27:                                        ; preds = %cond.end
  %31 = load i8*, i8** %path.addr, align 8, !dbg !1731
  %32 = load %struct.uv_fs_s*, %struct.uv_fs_s** %req.addr, align 8, !dbg !1731
  %path28 = getelementptr inbounds %struct.uv_fs_s, %struct.uv_fs_s* %32, i32 0, i32 9, !dbg !1731
  store i8* %31, i8** %path28, align 8, !dbg !1731
  br label %if.end57, !dbg !1731

if.else:                                          ; preds = %cond.end
  %33 = load i8*, i8** %path.addr, align 8, !dbg !1734
  %call = call i8* @uv__strdup(i8* %33), !dbg !1734
  %34 = load %struct.uv_fs_s*, %struct.uv_fs_s** %req.addr, align 8, !dbg !1734
  %path29 = getelementptr inbounds %struct.uv_fs_s, %struct.uv_fs_s* %34, i32 0, i32 9, !dbg !1734
  store i8* %call, i8** %path29, align 8, !dbg !1734
  %35 = load %struct.uv_fs_s*, %struct.uv_fs_s** %req.addr, align 8, !dbg !1734
  %path30 = getelementptr inbounds %struct.uv_fs_s, %struct.uv_fs_s* %35, i32 0, i32 9, !dbg !1734
  %36 = load i8*, i8** %path30, align 8, !dbg !1734
  %cmp31 = icmp eq i8* %36, null, !dbg !1734
  br i1 %cmp31, label %if.then32, label %if.end56, !dbg !1734

if.then32:                                        ; preds = %if.else
  br label %do.body33, !dbg !1737

do.body33:                                        ; preds = %if.then32
  %37 = load %struct.uv_loop_s*, %struct.uv_loop_s** %loop.addr, align 8, !dbg !1741
  %active_reqs34 = getelementptr inbounds %struct.uv_loop_s, %struct.uv_loop_s* %37, i32 0, i32 3, !dbg !1741
  %38 = load %struct.uv_loop_s*, %struct.uv_loop_s** %loop.addr, align 8, !dbg !1741
  %active_reqs35 = getelementptr inbounds %struct.uv_loop_s, %struct.uv_loop_s* %38, i32 0, i32 3, !dbg !1741
  %arrayidx36 = getelementptr inbounds [2 x i8*], [2 x i8*]* %active_reqs35, i64 0, i64 0, !dbg !1741
  %39 = bitcast i8** %arrayidx36 to [2 x i8*]**, !dbg !1741
  %40 = load [2 x i8*]*, [2 x i8*]** %39, align 8, !dbg !1741
  %cmp37 = icmp eq [2 x i8*]* %active_reqs34, %40, !dbg !1741
  %conv = zext i1 %cmp37 to i32, !dbg !1741
  %cmp38 = icmp eq i32 %conv, 0, !dbg !1741
  br i1 %cmp38, label %cond.true40, label %cond.false41, !dbg !1741

cond.true40:                                      ; preds = %do.body33
  br label %cond.end42, !dbg !1744

cond.false41:                                     ; preds = %do.body33
  call void @__assert_fail(i8* getelementptr inbounds ([113 x i8], [113 x i8]* @.str.2, i32 0, i32 0), i8* getelementptr inbounds ([66 x i8], [66 x i8]* @.str.1, i32 0, i32 0), i32 1158, i8* getelementptr inbounds ([69 x i8], [69 x i8]* @__PRETTY_FUNCTION__.uv_fs_mkdir, i32 0, i32 0)) #8, !dbg !1746
  unreachable, !dbg !1746
                                                  ; No predecessors!
  br label %cond.end42, !dbg !1748

cond.end42:                                       ; preds = %41, %cond.true40
  br label %do.body43, !dbg !1750

do.body43:                                        ; preds = %cond.end42
  %42 = load %struct.uv_fs_s*, %struct.uv_fs_s** %req.addr, align 8, !dbg !1752
  %active_queue44 = getelementptr inbounds %struct.uv_fs_s, %struct.uv_fs_s* %42, i32 0, i32 2, !dbg !1752
  %arrayidx45 = getelementptr inbounds [2 x i8*], [2 x i8*]* %active_queue44, i64 0, i64 0, !dbg !1752
  %43 = bitcast i8** %arrayidx45 to [2 x i8*]**, !dbg !1752
  %44 = load [2 x i8*]*, [2 x i8*]** %43, align 8, !dbg !1752
  %45 = load %struct.uv_fs_s*, %struct.uv_fs_s** %req.addr, align 8, !dbg !1752
  %active_queue46 = getelementptr inbounds %struct.uv_fs_s, %struct.uv_fs_s* %45, i32 0, i32 2, !dbg !1752
  %arrayidx47 = getelementptr inbounds [2 x i8*], [2 x i8*]* %active_queue46, i64 0, i64 1, !dbg !1752
  %46 = bitcast i8** %arrayidx47 to [2 x i8*]**, !dbg !1752
  %47 = load [2 x i8*]*, [2 x i8*]** %46, align 8, !dbg !1752
  %arrayidx48 = getelementptr inbounds [2 x i8*], [2 x i8*]* %47, i64 0, i64 0, !dbg !1752
  %48 = bitcast i8** %arrayidx48 to [2 x i8*]**, !dbg !1752
  store [2 x i8*]* %44, [2 x i8*]** %48, align 8, !dbg !1752
  %49 = load %struct.uv_fs_s*, %struct.uv_fs_s** %req.addr, align 8, !dbg !1752
  %active_queue49 = getelementptr inbounds %struct.uv_fs_s, %struct.uv_fs_s* %49, i32 0, i32 2, !dbg !1752
  %arrayidx50 = getelementptr inbounds [2 x i8*], [2 x i8*]* %active_queue49, i64 0, i64 1, !dbg !1752
  %50 = bitcast i8** %arrayidx50 to [2 x i8*]**, !dbg !1752
  %51 = load [2 x i8*]*, [2 x i8*]** %50, align 8, !dbg !1752
  %52 = load %struct.uv_fs_s*, %struct.uv_fs_s** %req.addr, align 8, !dbg !1752
  %active_queue51 = getelementptr inbounds %struct.uv_fs_s, %struct.uv_fs_s* %52, i32 0, i32 2, !dbg !1752
  %arrayidx52 = getelementptr inbounds [2 x i8*], [2 x i8*]* %active_queue51, i64 0, i64 0, !dbg !1752
  %53 = bitcast i8** %arrayidx52 to [2 x i8*]**, !dbg !1752
  %54 = load [2 x i8*]*, [2 x i8*]** %53, align 8, !dbg !1752
  %arrayidx53 = getelementptr inbounds [2 x i8*], [2 x i8*]* %54, i64 0, i64 1, !dbg !1752
  %55 = bitcast i8** %arrayidx53 to [2 x i8*]**, !dbg !1752
  store [2 x i8*]* %51, [2 x i8*]** %55, align 8, !dbg !1752
  br label %do.end54, !dbg !1752

do.end54:                                         ; preds = %do.body43
  br label %do.end55, !dbg !1755

do.end55:                                         ; preds = %do.end54
  store i32 -12, i32* %retval, align 4, !dbg !1757
  br label %do.end68, !dbg !1757

if.end56:                                         ; preds = %if.else
  br label %if.end57

if.end57:                                         ; preds = %if.end56, %if.then27
  br label %do.end58, !dbg !1759

do.end58:                                         ; preds = %if.end57
  %56 = load i32, i32* %mode.addr, align 4, !dbg !1761
  %57 = load %struct.uv_fs_s*, %struct.uv_fs_s** %req.addr, align 8, !dbg !1762
  %mode59 = getelementptr inbounds %struct.uv_fs_s, %struct.uv_fs_s* %57, i32 0, i32 14, !dbg !1763
  store i32 %56, i32* %mode59, align 8, !dbg !1764
  br label %do.body60, !dbg !1765

do.body60:                                        ; preds = %do.end58
  %58 = load void (%struct.uv_fs_s*)*, void (%struct.uv_fs_s*)** %cb.addr, align 8, !dbg !1766
  %cmp61 = icmp ne void (%struct.uv_fs_s*)* %58, null, !dbg !1766
  br i1 %cmp61, label %if.then63, label %if.else64, !dbg !1766

if.then63:                                        ; preds = %do.body60
  %59 = load %struct.uv_loop_s*, %struct.uv_loop_s** %loop.addr, align 8, !dbg !1770
  %60 = load %struct.uv_fs_s*, %struct.uv_fs_s** %req.addr, align 8, !dbg !1770
  %work_req = getelementptr inbounds %struct.uv_fs_s, %struct.uv_fs_s* %60, i32 0, i32 22, !dbg !1770
  call void @uv__work_submit(%struct.uv_loop_s* %59, %struct.uv__work* %work_req, void (%struct.uv__work*)* @uv__fs_work, void (%struct.uv__work*, i32)* @uv__fs_done), !dbg !1770
  store i32 0, i32* %retval, align 4, !dbg !1770
  br label %do.end68, !dbg !1770

if.else64:                                        ; preds = %do.body60
  %61 = load %struct.uv_fs_s*, %struct.uv_fs_s** %req.addr, align 8, !dbg !1773
  %work_req65 = getelementptr inbounds %struct.uv_fs_s, %struct.uv_fs_s* %61, i32 0, i32 22, !dbg !1773
  call void @uv__fs_work(%struct.uv__work* %work_req65), !dbg !1773
  %62 = load %struct.uv_fs_s*, %struct.uv_fs_s** %req.addr, align 8, !dbg !1773
  %result66 = getelementptr inbounds %struct.uv_fs_s, %struct.uv_fs_s* %62, i32 0, i32 7, !dbg !1773
  %63 = load i64, i64* %result66, align 8, !dbg !1773
  %conv67 = trunc i64 %63 to i32, !dbg !1773
  store i32 %conv67, i32* %retval, align 4, !dbg !1773
  br label %do.end68, !dbg !1773

do.end68:                                         ; preds = %do.end55, %if.then63, %if.else64
  %64 = load i32, i32* %retval, align 4, !dbg !1776
  ret i32 %64, !dbg !1776
}

; Function Attrs: nounwind uwtable
define i32 @uv_fs_mkdtemp(%struct.uv_loop_s* %loop, %struct.uv_fs_s* %req, i8* %tpl, void (%struct.uv_fs_s*)* %cb) #0 !dbg !449 {
entry:
  %retval = alloca i32, align 4
  %loop.addr = alloca %struct.uv_loop_s*, align 8
  %req.addr = alloca %struct.uv_fs_s*, align 8
  %tpl.addr = alloca i8*, align 8
  %cb.addr = alloca void (%struct.uv_fs_s*)*, align 8
  store %struct.uv_loop_s* %loop, %struct.uv_loop_s** %loop.addr, align 8
  call void @llvm.dbg.declare(metadata %struct.uv_loop_s** %loop.addr, metadata !1777, metadata !580), !dbg !1778
  store %struct.uv_fs_s* %req, %struct.uv_fs_s** %req.addr, align 8
  call void @llvm.dbg.declare(metadata %struct.uv_fs_s** %req.addr, metadata !1779, metadata !580), !dbg !1780
  store i8* %tpl, i8** %tpl.addr, align 8
  call void @llvm.dbg.declare(metadata i8** %tpl.addr, metadata !1781, metadata !580), !dbg !1782
  store void (%struct.uv_fs_s*)* %cb, void (%struct.uv_fs_s*)** %cb.addr, align 8
  call void @llvm.dbg.declare(metadata void (%struct.uv_fs_s*)** %cb.addr, metadata !1783, metadata !580), !dbg !1784
  br label %do.body, !dbg !1785

do.body:                                          ; preds = %entry
  %0 = load %struct.uv_fs_s*, %struct.uv_fs_s** %req.addr, align 8, !dbg !1786
  %type = getelementptr inbounds %struct.uv_fs_s, %struct.uv_fs_s* %0, i32 0, i32 1, !dbg !1786
  store i32 6, i32* %type, align 8, !dbg !1786
  %1 = load void (%struct.uv_fs_s*)*, void (%struct.uv_fs_s*)** %cb.addr, align 8, !dbg !1786
  %cmp = icmp ne void (%struct.uv_fs_s*)* %1, null, !dbg !1786
  br i1 %cmp, label %if.then, label %if.end, !dbg !1786

if.then:                                          ; preds = %do.body
  br label %do.body1, !dbg !1789

do.body1:                                         ; preds = %if.then
  br label %do.body2, !dbg !1792

do.body2:                                         ; preds = %do.body1
  %2 = load %struct.uv_fs_s*, %struct.uv_fs_s** %req.addr, align 8, !dbg !1795
  %type3 = getelementptr inbounds %struct.uv_fs_s, %struct.uv_fs_s* %2, i32 0, i32 1, !dbg !1795
  store i32 6, i32* %type3, align 8, !dbg !1795
  br label %do.end, !dbg !1795

do.end:                                           ; preds = %do.body2
  br label %do.body4, !dbg !1798

do.body4:                                         ; preds = %do.end
  br label %do.body5, !dbg !1800

do.body5:                                         ; preds = %do.body4
  %3 = load %struct.uv_loop_s*, %struct.uv_loop_s** %loop.addr, align 8, !dbg !1803
  %active_reqs = getelementptr inbounds %struct.uv_loop_s, %struct.uv_loop_s* %3, i32 0, i32 3, !dbg !1803
  %4 = load %struct.uv_fs_s*, %struct.uv_fs_s** %req.addr, align 8, !dbg !1803
  %active_queue = getelementptr inbounds %struct.uv_fs_s, %struct.uv_fs_s* %4, i32 0, i32 2, !dbg !1803
  %arrayidx = getelementptr inbounds [2 x i8*], [2 x i8*]* %active_queue, i64 0, i64 0, !dbg !1803
  %5 = bitcast i8** %arrayidx to [2 x i8*]**, !dbg !1803
  store [2 x i8*]* %active_reqs, [2 x i8*]** %5, align 8, !dbg !1803
  %6 = load %struct.uv_loop_s*, %struct.uv_loop_s** %loop.addr, align 8, !dbg !1803
  %active_reqs6 = getelementptr inbounds %struct.uv_loop_s, %struct.uv_loop_s* %6, i32 0, i32 3, !dbg !1803
  %arrayidx7 = getelementptr inbounds [2 x i8*], [2 x i8*]* %active_reqs6, i64 0, i64 1, !dbg !1803
  %7 = bitcast i8** %arrayidx7 to [2 x i8*]**, !dbg !1803
  %8 = load [2 x i8*]*, [2 x i8*]** %7, align 8, !dbg !1803
  %9 = load %struct.uv_fs_s*, %struct.uv_fs_s** %req.addr, align 8, !dbg !1803
  %active_queue8 = getelementptr inbounds %struct.uv_fs_s, %struct.uv_fs_s* %9, i32 0, i32 2, !dbg !1803
  %arrayidx9 = getelementptr inbounds [2 x i8*], [2 x i8*]* %active_queue8, i64 0, i64 1, !dbg !1803
  %10 = bitcast i8** %arrayidx9 to [2 x i8*]**, !dbg !1803
  store [2 x i8*]* %8, [2 x i8*]** %10, align 8, !dbg !1803
  %11 = load %struct.uv_fs_s*, %struct.uv_fs_s** %req.addr, align 8, !dbg !1803
  %active_queue10 = getelementptr inbounds %struct.uv_fs_s, %struct.uv_fs_s* %11, i32 0, i32 2, !dbg !1803
  %12 = load %struct.uv_fs_s*, %struct.uv_fs_s** %req.addr, align 8, !dbg !1803
  %active_queue11 = getelementptr inbounds %struct.uv_fs_s, %struct.uv_fs_s* %12, i32 0, i32 2, !dbg !1803
  %arrayidx12 = getelementptr inbounds [2 x i8*], [2 x i8*]* %active_queue11, i64 0, i64 1, !dbg !1803
  %13 = bitcast i8** %arrayidx12 to [2 x i8*]**, !dbg !1803
  %14 = load [2 x i8*]*, [2 x i8*]** %13, align 8, !dbg !1803
  %arrayidx13 = getelementptr inbounds [2 x i8*], [2 x i8*]* %14, i64 0, i64 0, !dbg !1803
  %15 = bitcast i8** %arrayidx13 to [2 x i8*]**, !dbg !1803
  store [2 x i8*]* %active_queue10, [2 x i8*]** %15, align 8, !dbg !1803
  %16 = load %struct.uv_fs_s*, %struct.uv_fs_s** %req.addr, align 8, !dbg !1803
  %active_queue14 = getelementptr inbounds %struct.uv_fs_s, %struct.uv_fs_s* %16, i32 0, i32 2, !dbg !1803
  %17 = load %struct.uv_loop_s*, %struct.uv_loop_s** %loop.addr, align 8, !dbg !1803
  %active_reqs15 = getelementptr inbounds %struct.uv_loop_s, %struct.uv_loop_s* %17, i32 0, i32 3, !dbg !1803
  %arrayidx16 = getelementptr inbounds [2 x i8*], [2 x i8*]* %active_reqs15, i64 0, i64 1, !dbg !1803
  %18 = bitcast i8** %arrayidx16 to [2 x i8*]**, !dbg !1803
  store [2 x i8*]* %active_queue14, [2 x i8*]** %18, align 8, !dbg !1803
  br label %do.end17, !dbg !1803

do.end17:                                         ; preds = %do.body5
  br label %do.end18, !dbg !1806

do.end18:                                         ; preds = %do.end17
  br label %do.end19, !dbg !1808

do.end19:                                         ; preds = %do.end18
  br label %if.end, !dbg !1810

if.end:                                           ; preds = %do.end19, %do.body
  %19 = load %struct.uv_fs_s*, %struct.uv_fs_s** %req.addr, align 8, !dbg !1812
  %fs_type = getelementptr inbounds %struct.uv_fs_s, %struct.uv_fs_s* %19, i32 0, i32 4, !dbg !1812
  store i32 20, i32* %fs_type, align 8, !dbg !1812
  %20 = load %struct.uv_fs_s*, %struct.uv_fs_s** %req.addr, align 8, !dbg !1812
  %result = getelementptr inbounds %struct.uv_fs_s, %struct.uv_fs_s* %20, i32 0, i32 7, !dbg !1812
  store i64 0, i64* %result, align 8, !dbg !1812
  %21 = load %struct.uv_fs_s*, %struct.uv_fs_s** %req.addr, align 8, !dbg !1812
  %ptr = getelementptr inbounds %struct.uv_fs_s, %struct.uv_fs_s* %21, i32 0, i32 8, !dbg !1812
  store i8* null, i8** %ptr, align 8, !dbg !1812
  %22 = load %struct.uv_loop_s*, %struct.uv_loop_s** %loop.addr, align 8, !dbg !1812
  %23 = load %struct.uv_fs_s*, %struct.uv_fs_s** %req.addr, align 8, !dbg !1812
  %loop20 = getelementptr inbounds %struct.uv_fs_s, %struct.uv_fs_s* %23, i32 0, i32 5, !dbg !1812
  store %struct.uv_loop_s* %22, %struct.uv_loop_s** %loop20, align 8, !dbg !1812
  %24 = load %struct.uv_fs_s*, %struct.uv_fs_s** %req.addr, align 8, !dbg !1812
  %path = getelementptr inbounds %struct.uv_fs_s, %struct.uv_fs_s* %24, i32 0, i32 9, !dbg !1812
  store i8* null, i8** %path, align 8, !dbg !1812
  %25 = load %struct.uv_fs_s*, %struct.uv_fs_s** %req.addr, align 8, !dbg !1812
  %new_path = getelementptr inbounds %struct.uv_fs_s, %struct.uv_fs_s* %25, i32 0, i32 11, !dbg !1812
  store i8* null, i8** %new_path, align 8, !dbg !1812
  %26 = load void (%struct.uv_fs_s*)*, void (%struct.uv_fs_s*)** %cb.addr, align 8, !dbg !1812
  %27 = load %struct.uv_fs_s*, %struct.uv_fs_s** %req.addr, align 8, !dbg !1812
  %cb21 = getelementptr inbounds %struct.uv_fs_s, %struct.uv_fs_s* %27, i32 0, i32 6, !dbg !1812
  store void (%struct.uv_fs_s*)* %26, void (%struct.uv_fs_s*)** %cb21, align 8, !dbg !1812
  br label %do.end22, !dbg !1812

do.end22:                                         ; preds = %if.end
  %28 = load i8*, i8** %tpl.addr, align 8, !dbg !1814
  %call = call i8* @uv__strdup(i8* %28), !dbg !1815
  %29 = load %struct.uv_fs_s*, %struct.uv_fs_s** %req.addr, align 8, !dbg !1816
  %path23 = getelementptr inbounds %struct.uv_fs_s, %struct.uv_fs_s* %29, i32 0, i32 9, !dbg !1817
  store i8* %call, i8** %path23, align 8, !dbg !1818
  %30 = load %struct.uv_fs_s*, %struct.uv_fs_s** %req.addr, align 8, !dbg !1819
  %path24 = getelementptr inbounds %struct.uv_fs_s, %struct.uv_fs_s* %30, i32 0, i32 9, !dbg !1821
  %31 = load i8*, i8** %path24, align 8, !dbg !1821
  %cmp25 = icmp eq i8* %31, null, !dbg !1822
  br i1 %cmp25, label %if.then26, label %if.end50, !dbg !1823

if.then26:                                        ; preds = %do.end22
  %32 = load void (%struct.uv_fs_s*)*, void (%struct.uv_fs_s*)** %cb.addr, align 8, !dbg !1824
  %cmp27 = icmp ne void (%struct.uv_fs_s*)* %32, null, !dbg !1827
  br i1 %cmp27, label %if.then28, label %if.end49, !dbg !1828

if.then28:                                        ; preds = %if.then26
  br label %do.body29, !dbg !1829

do.body29:                                        ; preds = %if.then28
  %33 = load %struct.uv_loop_s*, %struct.uv_loop_s** %loop.addr, align 8, !dbg !1830
  %active_reqs30 = getelementptr inbounds %struct.uv_loop_s, %struct.uv_loop_s* %33, i32 0, i32 3, !dbg !1830
  %34 = load %struct.uv_loop_s*, %struct.uv_loop_s** %loop.addr, align 8, !dbg !1830
  %active_reqs31 = getelementptr inbounds %struct.uv_loop_s, %struct.uv_loop_s* %34, i32 0, i32 3, !dbg !1830
  %arrayidx32 = getelementptr inbounds [2 x i8*], [2 x i8*]* %active_reqs31, i64 0, i64 0, !dbg !1830
  %35 = bitcast i8** %arrayidx32 to [2 x i8*]**, !dbg !1830
  %36 = load [2 x i8*]*, [2 x i8*]** %35, align 8, !dbg !1830
  %cmp33 = icmp eq [2 x i8*]* %active_reqs30, %36, !dbg !1830
  %conv = zext i1 %cmp33 to i32, !dbg !1830
  %cmp34 = icmp eq i32 %conv, 0, !dbg !1830
  br i1 %cmp34, label %cond.true, label %cond.false, !dbg !1830

cond.true:                                        ; preds = %do.body29
  br label %cond.end, !dbg !1833

cond.false:                                       ; preds = %do.body29
  call void @__assert_fail(i8* getelementptr inbounds ([113 x i8], [113 x i8]* @.str.2, i32 0, i32 0), i8* getelementptr inbounds ([66 x i8], [66 x i8]* @.str.1, i32 0, i32 0), i32 1172, i8* getelementptr inbounds ([66 x i8], [66 x i8]* @__PRETTY_FUNCTION__.uv_fs_mkdtemp, i32 0, i32 0)) #8, !dbg !1835
  unreachable, !dbg !1835
                                                  ; No predecessors!
  br label %cond.end, !dbg !1837

cond.end:                                         ; preds = %37, %cond.true
  br label %do.body36, !dbg !1839

do.body36:                                        ; preds = %cond.end
  %38 = load %struct.uv_fs_s*, %struct.uv_fs_s** %req.addr, align 8, !dbg !1841
  %active_queue37 = getelementptr inbounds %struct.uv_fs_s, %struct.uv_fs_s* %38, i32 0, i32 2, !dbg !1841
  %arrayidx38 = getelementptr inbounds [2 x i8*], [2 x i8*]* %active_queue37, i64 0, i64 0, !dbg !1841
  %39 = bitcast i8** %arrayidx38 to [2 x i8*]**, !dbg !1841
  %40 = load [2 x i8*]*, [2 x i8*]** %39, align 8, !dbg !1841
  %41 = load %struct.uv_fs_s*, %struct.uv_fs_s** %req.addr, align 8, !dbg !1841
  %active_queue39 = getelementptr inbounds %struct.uv_fs_s, %struct.uv_fs_s* %41, i32 0, i32 2, !dbg !1841
  %arrayidx40 = getelementptr inbounds [2 x i8*], [2 x i8*]* %active_queue39, i64 0, i64 1, !dbg !1841
  %42 = bitcast i8** %arrayidx40 to [2 x i8*]**, !dbg !1841
  %43 = load [2 x i8*]*, [2 x i8*]** %42, align 8, !dbg !1841
  %arrayidx41 = getelementptr inbounds [2 x i8*], [2 x i8*]* %43, i64 0, i64 0, !dbg !1841
  %44 = bitcast i8** %arrayidx41 to [2 x i8*]**, !dbg !1841
  store [2 x i8*]* %40, [2 x i8*]** %44, align 8, !dbg !1841
  %45 = load %struct.uv_fs_s*, %struct.uv_fs_s** %req.addr, align 8, !dbg !1841
  %active_queue42 = getelementptr inbounds %struct.uv_fs_s, %struct.uv_fs_s* %45, i32 0, i32 2, !dbg !1841
  %arrayidx43 = getelementptr inbounds [2 x i8*], [2 x i8*]* %active_queue42, i64 0, i64 1, !dbg !1841
  %46 = bitcast i8** %arrayidx43 to [2 x i8*]**, !dbg !1841
  %47 = load [2 x i8*]*, [2 x i8*]** %46, align 8, !dbg !1841
  %48 = load %struct.uv_fs_s*, %struct.uv_fs_s** %req.addr, align 8, !dbg !1841
  %active_queue44 = getelementptr inbounds %struct.uv_fs_s, %struct.uv_fs_s* %48, i32 0, i32 2, !dbg !1841
  %arrayidx45 = getelementptr inbounds [2 x i8*], [2 x i8*]* %active_queue44, i64 0, i64 0, !dbg !1841
  %49 = bitcast i8** %arrayidx45 to [2 x i8*]**, !dbg !1841
  %50 = load [2 x i8*]*, [2 x i8*]** %49, align 8, !dbg !1841
  %arrayidx46 = getelementptr inbounds [2 x i8*], [2 x i8*]* %50, i64 0, i64 1, !dbg !1841
  %51 = bitcast i8** %arrayidx46 to [2 x i8*]**, !dbg !1841
  store [2 x i8*]* %47, [2 x i8*]** %51, align 8, !dbg !1841
  br label %do.end47, !dbg !1841

do.end47:                                         ; preds = %do.body36
  br label %do.end48, !dbg !1844

do.end48:                                         ; preds = %do.end47
  br label %if.end49, !dbg !1846

if.end49:                                         ; preds = %do.end48, %if.then26
  store i32 -12, i32* %retval, align 4, !dbg !1848
  br label %do.end58, !dbg !1848

if.end50:                                         ; preds = %do.end22
  br label %do.body51, !dbg !1849

do.body51:                                        ; preds = %if.end50
  %52 = load void (%struct.uv_fs_s*)*, void (%struct.uv_fs_s*)** %cb.addr, align 8, !dbg !1850
  %cmp52 = icmp ne void (%struct.uv_fs_s*)* %52, null, !dbg !1850
  br i1 %cmp52, label %if.then54, label %if.else, !dbg !1850

if.then54:                                        ; preds = %do.body51
  %53 = load %struct.uv_loop_s*, %struct.uv_loop_s** %loop.addr, align 8, !dbg !1854
  %54 = load %struct.uv_fs_s*, %struct.uv_fs_s** %req.addr, align 8, !dbg !1854
  %work_req = getelementptr inbounds %struct.uv_fs_s, %struct.uv_fs_s* %54, i32 0, i32 22, !dbg !1854
  call void @uv__work_submit(%struct.uv_loop_s* %53, %struct.uv__work* %work_req, void (%struct.uv__work*)* @uv__fs_work, void (%struct.uv__work*, i32)* @uv__fs_done), !dbg !1854
  store i32 0, i32* %retval, align 4, !dbg !1854
  br label %do.end58, !dbg !1854

if.else:                                          ; preds = %do.body51
  %55 = load %struct.uv_fs_s*, %struct.uv_fs_s** %req.addr, align 8, !dbg !1857
  %work_req55 = getelementptr inbounds %struct.uv_fs_s, %struct.uv_fs_s* %55, i32 0, i32 22, !dbg !1857
  call void @uv__fs_work(%struct.uv__work* %work_req55), !dbg !1857
  %56 = load %struct.uv_fs_s*, %struct.uv_fs_s** %req.addr, align 8, !dbg !1857
  %result56 = getelementptr inbounds %struct.uv_fs_s, %struct.uv_fs_s* %56, i32 0, i32 7, !dbg !1857
  %57 = load i64, i64* %result56, align 8, !dbg !1857
  %conv57 = trunc i64 %57 to i32, !dbg !1857
  store i32 %conv57, i32* %retval, align 4, !dbg !1857
  br label %do.end58, !dbg !1857

do.end58:                                         ; preds = %if.end49, %if.then54, %if.else
  %58 = load i32, i32* %retval, align 4, !dbg !1860
  ret i32 %58, !dbg !1860
}

; Function Attrs: nounwind uwtable
define i32 @uv_fs_open(%struct.uv_loop_s* %loop, %struct.uv_fs_s* %req, i8* %path, i32 %flags, i32 %mode, void (%struct.uv_fs_s*)* %cb) #0 !dbg !450 {
entry:
  %retval = alloca i32, align 4
  %loop.addr = alloca %struct.uv_loop_s*, align 8
  %req.addr = alloca %struct.uv_fs_s*, align 8
  %path.addr = alloca i8*, align 8
  %flags.addr = alloca i32, align 4
  %mode.addr = alloca i32, align 4
  %cb.addr = alloca void (%struct.uv_fs_s*)*, align 8
  store %struct.uv_loop_s* %loop, %struct.uv_loop_s** %loop.addr, align 8
  call void @llvm.dbg.declare(metadata %struct.uv_loop_s** %loop.addr, metadata !1861, metadata !580), !dbg !1862
  store %struct.uv_fs_s* %req, %struct.uv_fs_s** %req.addr, align 8
  call void @llvm.dbg.declare(metadata %struct.uv_fs_s** %req.addr, metadata !1863, metadata !580), !dbg !1864
  store i8* %path, i8** %path.addr, align 8
  call void @llvm.dbg.declare(metadata i8** %path.addr, metadata !1865, metadata !580), !dbg !1866
  store i32 %flags, i32* %flags.addr, align 4
  call void @llvm.dbg.declare(metadata i32* %flags.addr, metadata !1867, metadata !580), !dbg !1868
  store i32 %mode, i32* %mode.addr, align 4
  call void @llvm.dbg.declare(metadata i32* %mode.addr, metadata !1869, metadata !580), !dbg !1870
  store void (%struct.uv_fs_s*)* %cb, void (%struct.uv_fs_s*)** %cb.addr, align 8
  call void @llvm.dbg.declare(metadata void (%struct.uv_fs_s*)** %cb.addr, metadata !1871, metadata !580), !dbg !1872
  br label %do.body, !dbg !1873

do.body:                                          ; preds = %entry
  %0 = load %struct.uv_fs_s*, %struct.uv_fs_s** %req.addr, align 8, !dbg !1874
  %type = getelementptr inbounds %struct.uv_fs_s, %struct.uv_fs_s* %0, i32 0, i32 1, !dbg !1874
  store i32 6, i32* %type, align 8, !dbg !1874
  %1 = load void (%struct.uv_fs_s*)*, void (%struct.uv_fs_s*)** %cb.addr, align 8, !dbg !1874
  %cmp = icmp ne void (%struct.uv_fs_s*)* %1, null, !dbg !1874
  br i1 %cmp, label %if.then, label %if.end, !dbg !1874

if.then:                                          ; preds = %do.body
  br label %do.body1, !dbg !1877

do.body1:                                         ; preds = %if.then
  br label %do.body2, !dbg !1880

do.body2:                                         ; preds = %do.body1
  %2 = load %struct.uv_fs_s*, %struct.uv_fs_s** %req.addr, align 8, !dbg !1883
  %type3 = getelementptr inbounds %struct.uv_fs_s, %struct.uv_fs_s* %2, i32 0, i32 1, !dbg !1883
  store i32 6, i32* %type3, align 8, !dbg !1883
  br label %do.end, !dbg !1883

do.end:                                           ; preds = %do.body2
  br label %do.body4, !dbg !1886

do.body4:                                         ; preds = %do.end
  br label %do.body5, !dbg !1888

do.body5:                                         ; preds = %do.body4
  %3 = load %struct.uv_loop_s*, %struct.uv_loop_s** %loop.addr, align 8, !dbg !1891
  %active_reqs = getelementptr inbounds %struct.uv_loop_s, %struct.uv_loop_s* %3, i32 0, i32 3, !dbg !1891
  %4 = load %struct.uv_fs_s*, %struct.uv_fs_s** %req.addr, align 8, !dbg !1891
  %active_queue = getelementptr inbounds %struct.uv_fs_s, %struct.uv_fs_s* %4, i32 0, i32 2, !dbg !1891
  %arrayidx = getelementptr inbounds [2 x i8*], [2 x i8*]* %active_queue, i64 0, i64 0, !dbg !1891
  %5 = bitcast i8** %arrayidx to [2 x i8*]**, !dbg !1891
  store [2 x i8*]* %active_reqs, [2 x i8*]** %5, align 8, !dbg !1891
  %6 = load %struct.uv_loop_s*, %struct.uv_loop_s** %loop.addr, align 8, !dbg !1891
  %active_reqs6 = getelementptr inbounds %struct.uv_loop_s, %struct.uv_loop_s* %6, i32 0, i32 3, !dbg !1891
  %arrayidx7 = getelementptr inbounds [2 x i8*], [2 x i8*]* %active_reqs6, i64 0, i64 1, !dbg !1891
  %7 = bitcast i8** %arrayidx7 to [2 x i8*]**, !dbg !1891
  %8 = load [2 x i8*]*, [2 x i8*]** %7, align 8, !dbg !1891
  %9 = load %struct.uv_fs_s*, %struct.uv_fs_s** %req.addr, align 8, !dbg !1891
  %active_queue8 = getelementptr inbounds %struct.uv_fs_s, %struct.uv_fs_s* %9, i32 0, i32 2, !dbg !1891
  %arrayidx9 = getelementptr inbounds [2 x i8*], [2 x i8*]* %active_queue8, i64 0, i64 1, !dbg !1891
  %10 = bitcast i8** %arrayidx9 to [2 x i8*]**, !dbg !1891
  store [2 x i8*]* %8, [2 x i8*]** %10, align 8, !dbg !1891
  %11 = load %struct.uv_fs_s*, %struct.uv_fs_s** %req.addr, align 8, !dbg !1891
  %active_queue10 = getelementptr inbounds %struct.uv_fs_s, %struct.uv_fs_s* %11, i32 0, i32 2, !dbg !1891
  %12 = load %struct.uv_fs_s*, %struct.uv_fs_s** %req.addr, align 8, !dbg !1891
  %active_queue11 = getelementptr inbounds %struct.uv_fs_s, %struct.uv_fs_s* %12, i32 0, i32 2, !dbg !1891
  %arrayidx12 = getelementptr inbounds [2 x i8*], [2 x i8*]* %active_queue11, i64 0, i64 1, !dbg !1891
  %13 = bitcast i8** %arrayidx12 to [2 x i8*]**, !dbg !1891
  %14 = load [2 x i8*]*, [2 x i8*]** %13, align 8, !dbg !1891
  %arrayidx13 = getelementptr inbounds [2 x i8*], [2 x i8*]* %14, i64 0, i64 0, !dbg !1891
  %15 = bitcast i8** %arrayidx13 to [2 x i8*]**, !dbg !1891
  store [2 x i8*]* %active_queue10, [2 x i8*]** %15, align 8, !dbg !1891
  %16 = load %struct.uv_fs_s*, %struct.uv_fs_s** %req.addr, align 8, !dbg !1891
  %active_queue14 = getelementptr inbounds %struct.uv_fs_s, %struct.uv_fs_s* %16, i32 0, i32 2, !dbg !1891
  %17 = load %struct.uv_loop_s*, %struct.uv_loop_s** %loop.addr, align 8, !dbg !1891
  %active_reqs15 = getelementptr inbounds %struct.uv_loop_s, %struct.uv_loop_s* %17, i32 0, i32 3, !dbg !1891
  %arrayidx16 = getelementptr inbounds [2 x i8*], [2 x i8*]* %active_reqs15, i64 0, i64 1, !dbg !1891
  %18 = bitcast i8** %arrayidx16 to [2 x i8*]**, !dbg !1891
  store [2 x i8*]* %active_queue14, [2 x i8*]** %18, align 8, !dbg !1891
  br label %do.end17, !dbg !1891

do.end17:                                         ; preds = %do.body5
  br label %do.end18, !dbg !1894

do.end18:                                         ; preds = %do.end17
  br label %do.end19, !dbg !1896

do.end19:                                         ; preds = %do.end18
  br label %if.end, !dbg !1898

if.end:                                           ; preds = %do.end19, %do.body
  %19 = load %struct.uv_fs_s*, %struct.uv_fs_s** %req.addr, align 8, !dbg !1900
  %fs_type = getelementptr inbounds %struct.uv_fs_s, %struct.uv_fs_s* %19, i32 0, i32 4, !dbg !1900
  store i32 1, i32* %fs_type, align 8, !dbg !1900
  %20 = load %struct.uv_fs_s*, %struct.uv_fs_s** %req.addr, align 8, !dbg !1900
  %result = getelementptr inbounds %struct.uv_fs_s, %struct.uv_fs_s* %20, i32 0, i32 7, !dbg !1900
  store i64 0, i64* %result, align 8, !dbg !1900
  %21 = load %struct.uv_fs_s*, %struct.uv_fs_s** %req.addr, align 8, !dbg !1900
  %ptr = getelementptr inbounds %struct.uv_fs_s, %struct.uv_fs_s* %21, i32 0, i32 8, !dbg !1900
  store i8* null, i8** %ptr, align 8, !dbg !1900
  %22 = load %struct.uv_loop_s*, %struct.uv_loop_s** %loop.addr, align 8, !dbg !1900
  %23 = load %struct.uv_fs_s*, %struct.uv_fs_s** %req.addr, align 8, !dbg !1900
  %loop20 = getelementptr inbounds %struct.uv_fs_s, %struct.uv_fs_s* %23, i32 0, i32 5, !dbg !1900
  store %struct.uv_loop_s* %22, %struct.uv_loop_s** %loop20, align 8, !dbg !1900
  %24 = load %struct.uv_fs_s*, %struct.uv_fs_s** %req.addr, align 8, !dbg !1900
  %path21 = getelementptr inbounds %struct.uv_fs_s, %struct.uv_fs_s* %24, i32 0, i32 9, !dbg !1900
  store i8* null, i8** %path21, align 8, !dbg !1900
  %25 = load %struct.uv_fs_s*, %struct.uv_fs_s** %req.addr, align 8, !dbg !1900
  %new_path = getelementptr inbounds %struct.uv_fs_s, %struct.uv_fs_s* %25, i32 0, i32 11, !dbg !1900
  store i8* null, i8** %new_path, align 8, !dbg !1900
  %26 = load void (%struct.uv_fs_s*)*, void (%struct.uv_fs_s*)** %cb.addr, align 8, !dbg !1900
  %27 = load %struct.uv_fs_s*, %struct.uv_fs_s** %req.addr, align 8, !dbg !1900
  %cb22 = getelementptr inbounds %struct.uv_fs_s, %struct.uv_fs_s* %27, i32 0, i32 6, !dbg !1900
  store void (%struct.uv_fs_s*)* %26, void (%struct.uv_fs_s*)** %cb22, align 8, !dbg !1900
  br label %do.end23, !dbg !1900

do.end23:                                         ; preds = %if.end
  br label %do.body24, !dbg !1902

do.body24:                                        ; preds = %do.end23
  %28 = load i8*, i8** %path.addr, align 8, !dbg !1903
  %cmp25 = icmp ne i8* %28, null, !dbg !1903
  br i1 %cmp25, label %cond.true, label %cond.false, !dbg !1903

cond.true:                                        ; preds = %do.body24
  br label %cond.end, !dbg !1906

cond.false:                                       ; preds = %do.body24
  call void @__assert_fail(i8* getelementptr inbounds ([19 x i8], [19 x i8]* @.str, i32 0, i32 0), i8* getelementptr inbounds ([66 x i8], [66 x i8]* @.str.1, i32 0, i32 0), i32 1186, i8* getelementptr inbounds ([73 x i8], [73 x i8]* @__PRETTY_FUNCTION__.uv_fs_open, i32 0, i32 0)) #8, !dbg !1908
  unreachable, !dbg !1908
                                                  ; No predecessors!
  br label %cond.end, !dbg !1910

cond.end:                                         ; preds = %29, %cond.true
  %30 = load void (%struct.uv_fs_s*)*, void (%struct.uv_fs_s*)** %cb.addr, align 8, !dbg !1912
  %cmp26 = icmp eq void (%struct.uv_fs_s*)* %30, null, !dbg !1912
  br i1 %cmp26, label %if.then27, label %if.else, !dbg !1912

if.then27:                                        ; preds = %cond.end
  %31 = load i8*, i8** %path.addr, align 8, !dbg !1915
  %32 = load %struct.uv_fs_s*, %struct.uv_fs_s** %req.addr, align 8, !dbg !1915
  %path28 = getelementptr inbounds %struct.uv_fs_s, %struct.uv_fs_s* %32, i32 0, i32 9, !dbg !1915
  store i8* %31, i8** %path28, align 8, !dbg !1915
  br label %if.end57, !dbg !1915

if.else:                                          ; preds = %cond.end
  %33 = load i8*, i8** %path.addr, align 8, !dbg !1918
  %call = call i8* @uv__strdup(i8* %33), !dbg !1918
  %34 = load %struct.uv_fs_s*, %struct.uv_fs_s** %req.addr, align 8, !dbg !1918
  %path29 = getelementptr inbounds %struct.uv_fs_s, %struct.uv_fs_s* %34, i32 0, i32 9, !dbg !1918
  store i8* %call, i8** %path29, align 8, !dbg !1918
  %35 = load %struct.uv_fs_s*, %struct.uv_fs_s** %req.addr, align 8, !dbg !1918
  %path30 = getelementptr inbounds %struct.uv_fs_s, %struct.uv_fs_s* %35, i32 0, i32 9, !dbg !1918
  %36 = load i8*, i8** %path30, align 8, !dbg !1918
  %cmp31 = icmp eq i8* %36, null, !dbg !1918
  br i1 %cmp31, label %if.then32, label %if.end56, !dbg !1918

if.then32:                                        ; preds = %if.else
  br label %do.body33, !dbg !1921

do.body33:                                        ; preds = %if.then32
  %37 = load %struct.uv_loop_s*, %struct.uv_loop_s** %loop.addr, align 8, !dbg !1925
  %active_reqs34 = getelementptr inbounds %struct.uv_loop_s, %struct.uv_loop_s* %37, i32 0, i32 3, !dbg !1925
  %38 = load %struct.uv_loop_s*, %struct.uv_loop_s** %loop.addr, align 8, !dbg !1925
  %active_reqs35 = getelementptr inbounds %struct.uv_loop_s, %struct.uv_loop_s* %38, i32 0, i32 3, !dbg !1925
  %arrayidx36 = getelementptr inbounds [2 x i8*], [2 x i8*]* %active_reqs35, i64 0, i64 0, !dbg !1925
  %39 = bitcast i8** %arrayidx36 to [2 x i8*]**, !dbg !1925
  %40 = load [2 x i8*]*, [2 x i8*]** %39, align 8, !dbg !1925
  %cmp37 = icmp eq [2 x i8*]* %active_reqs34, %40, !dbg !1925
  %conv = zext i1 %cmp37 to i32, !dbg !1925
  %cmp38 = icmp eq i32 %conv, 0, !dbg !1925
  br i1 %cmp38, label %cond.true40, label %cond.false41, !dbg !1925

cond.true40:                                      ; preds = %do.body33
  br label %cond.end42, !dbg !1928

cond.false41:                                     ; preds = %do.body33
  call void @__assert_fail(i8* getelementptr inbounds ([113 x i8], [113 x i8]* @.str.2, i32 0, i32 0), i8* getelementptr inbounds ([66 x i8], [66 x i8]* @.str.1, i32 0, i32 0), i32 1186, i8* getelementptr inbounds ([73 x i8], [73 x i8]* @__PRETTY_FUNCTION__.uv_fs_open, i32 0, i32 0)) #8, !dbg !1930
  unreachable, !dbg !1930
                                                  ; No predecessors!
  br label %cond.end42, !dbg !1932

cond.end42:                                       ; preds = %41, %cond.true40
  br label %do.body43, !dbg !1934

do.body43:                                        ; preds = %cond.end42
  %42 = load %struct.uv_fs_s*, %struct.uv_fs_s** %req.addr, align 8, !dbg !1936
  %active_queue44 = getelementptr inbounds %struct.uv_fs_s, %struct.uv_fs_s* %42, i32 0, i32 2, !dbg !1936
  %arrayidx45 = getelementptr inbounds [2 x i8*], [2 x i8*]* %active_queue44, i64 0, i64 0, !dbg !1936
  %43 = bitcast i8** %arrayidx45 to [2 x i8*]**, !dbg !1936
  %44 = load [2 x i8*]*, [2 x i8*]** %43, align 8, !dbg !1936
  %45 = load %struct.uv_fs_s*, %struct.uv_fs_s** %req.addr, align 8, !dbg !1936
  %active_queue46 = getelementptr inbounds %struct.uv_fs_s, %struct.uv_fs_s* %45, i32 0, i32 2, !dbg !1936
  %arrayidx47 = getelementptr inbounds [2 x i8*], [2 x i8*]* %active_queue46, i64 0, i64 1, !dbg !1936
  %46 = bitcast i8** %arrayidx47 to [2 x i8*]**, !dbg !1936
  %47 = load [2 x i8*]*, [2 x i8*]** %46, align 8, !dbg !1936
  %arrayidx48 = getelementptr inbounds [2 x i8*], [2 x i8*]* %47, i64 0, i64 0, !dbg !1936
  %48 = bitcast i8** %arrayidx48 to [2 x i8*]**, !dbg !1936
  store [2 x i8*]* %44, [2 x i8*]** %48, align 8, !dbg !1936
  %49 = load %struct.uv_fs_s*, %struct.uv_fs_s** %req.addr, align 8, !dbg !1936
  %active_queue49 = getelementptr inbounds %struct.uv_fs_s, %struct.uv_fs_s* %49, i32 0, i32 2, !dbg !1936
  %arrayidx50 = getelementptr inbounds [2 x i8*], [2 x i8*]* %active_queue49, i64 0, i64 1, !dbg !1936
  %50 = bitcast i8** %arrayidx50 to [2 x i8*]**, !dbg !1936
  %51 = load [2 x i8*]*, [2 x i8*]** %50, align 8, !dbg !1936
  %52 = load %struct.uv_fs_s*, %struct.uv_fs_s** %req.addr, align 8, !dbg !1936
  %active_queue51 = getelementptr inbounds %struct.uv_fs_s, %struct.uv_fs_s* %52, i32 0, i32 2, !dbg !1936
  %arrayidx52 = getelementptr inbounds [2 x i8*], [2 x i8*]* %active_queue51, i64 0, i64 0, !dbg !1936
  %53 = bitcast i8** %arrayidx52 to [2 x i8*]**, !dbg !1936
  %54 = load [2 x i8*]*, [2 x i8*]** %53, align 8, !dbg !1936
  %arrayidx53 = getelementptr inbounds [2 x i8*], [2 x i8*]* %54, i64 0, i64 1, !dbg !1936
  %55 = bitcast i8** %arrayidx53 to [2 x i8*]**, !dbg !1936
  store [2 x i8*]* %51, [2 x i8*]** %55, align 8, !dbg !1936
  br label %do.end54, !dbg !1936

do.end54:                                         ; preds = %do.body43
  br label %do.end55, !dbg !1939

do.end55:                                         ; preds = %do.end54
  store i32 -12, i32* %retval, align 4, !dbg !1941
  br label %do.end69, !dbg !1941

if.end56:                                         ; preds = %if.else
  br label %if.end57

if.end57:                                         ; preds = %if.end56, %if.then27
  br label %do.end58, !dbg !1943

do.end58:                                         ; preds = %if.end57
  %56 = load i32, i32* %flags.addr, align 4, !dbg !1945
  %57 = load %struct.uv_fs_s*, %struct.uv_fs_s** %req.addr, align 8, !dbg !1946
  %flags59 = getelementptr inbounds %struct.uv_fs_s, %struct.uv_fs_s* %57, i32 0, i32 13, !dbg !1947
  store i32 %56, i32* %flags59, align 4, !dbg !1948
  %58 = load i32, i32* %mode.addr, align 4, !dbg !1949
  %59 = load %struct.uv_fs_s*, %struct.uv_fs_s** %req.addr, align 8, !dbg !1950
  %mode60 = getelementptr inbounds %struct.uv_fs_s, %struct.uv_fs_s* %59, i32 0, i32 14, !dbg !1951
  store i32 %58, i32* %mode60, align 8, !dbg !1952
  br label %do.body61, !dbg !1953

do.body61:                                        ; preds = %do.end58
  %60 = load void (%struct.uv_fs_s*)*, void (%struct.uv_fs_s*)** %cb.addr, align 8, !dbg !1954
  %cmp62 = icmp ne void (%struct.uv_fs_s*)* %60, null, !dbg !1954
  br i1 %cmp62, label %if.then64, label %if.else65, !dbg !1954

if.then64:                                        ; preds = %do.body61
  %61 = load %struct.uv_loop_s*, %struct.uv_loop_s** %loop.addr, align 8, !dbg !1958
  %62 = load %struct.uv_fs_s*, %struct.uv_fs_s** %req.addr, align 8, !dbg !1958
  %work_req = getelementptr inbounds %struct.uv_fs_s, %struct.uv_fs_s* %62, i32 0, i32 22, !dbg !1958
  call void @uv__work_submit(%struct.uv_loop_s* %61, %struct.uv__work* %work_req, void (%struct.uv__work*)* @uv__fs_work, void (%struct.uv__work*, i32)* @uv__fs_done), !dbg !1958
  store i32 0, i32* %retval, align 4, !dbg !1958
  br label %do.end69, !dbg !1958

if.else65:                                        ; preds = %do.body61
  %63 = load %struct.uv_fs_s*, %struct.uv_fs_s** %req.addr, align 8, !dbg !1961
  %work_req66 = getelementptr inbounds %struct.uv_fs_s, %struct.uv_fs_s* %63, i32 0, i32 22, !dbg !1961
  call void @uv__fs_work(%struct.uv__work* %work_req66), !dbg !1961
  %64 = load %struct.uv_fs_s*, %struct.uv_fs_s** %req.addr, align 8, !dbg !1961
  %result67 = getelementptr inbounds %struct.uv_fs_s, %struct.uv_fs_s* %64, i32 0, i32 7, !dbg !1961
  %65 = load i64, i64* %result67, align 8, !dbg !1961
  %conv68 = trunc i64 %65 to i32, !dbg !1961
  store i32 %conv68, i32* %retval, align 4, !dbg !1961
  br label %do.end69, !dbg !1961

do.end69:                                         ; preds = %do.end55, %if.then64, %if.else65
  %66 = load i32, i32* %retval, align 4, !dbg !1964
  ret i32 %66, !dbg !1964
}

; Function Attrs: nounwind uwtable
define i32 @uv_fs_read(%struct.uv_loop_s* %loop, %struct.uv_fs_s* %req, i32 %file, %struct.uv_buf_t* %bufs, i32 %nbufs, i64 %off, void (%struct.uv_fs_s*)* %cb) #0 !dbg !453 {
entry:
  %retval = alloca i32, align 4
  %loop.addr = alloca %struct.uv_loop_s*, align 8
  %req.addr = alloca %struct.uv_fs_s*, align 8
  %file.addr = alloca i32, align 4
  %bufs.addr = alloca %struct.uv_buf_t*, align 8
  %nbufs.addr = alloca i32, align 4
  %off.addr = alloca i64, align 8
  %cb.addr = alloca void (%struct.uv_fs_s*)*, align 8
  store %struct.uv_loop_s* %loop, %struct.uv_loop_s** %loop.addr, align 8
  call void @llvm.dbg.declare(metadata %struct.uv_loop_s** %loop.addr, metadata !1965, metadata !580), !dbg !1966
  store %struct.uv_fs_s* %req, %struct.uv_fs_s** %req.addr, align 8
  call void @llvm.dbg.declare(metadata %struct.uv_fs_s** %req.addr, metadata !1967, metadata !580), !dbg !1968
  store i32 %file, i32* %file.addr, align 4
  call void @llvm.dbg.declare(metadata i32* %file.addr, metadata !1969, metadata !580), !dbg !1970
  store %struct.uv_buf_t* %bufs, %struct.uv_buf_t** %bufs.addr, align 8
  call void @llvm.dbg.declare(metadata %struct.uv_buf_t** %bufs.addr, metadata !1971, metadata !580), !dbg !1972
  store i32 %nbufs, i32* %nbufs.addr, align 4
  call void @llvm.dbg.declare(metadata i32* %nbufs.addr, metadata !1973, metadata !580), !dbg !1974
  store i64 %off, i64* %off.addr, align 8
  call void @llvm.dbg.declare(metadata i64* %off.addr, metadata !1975, metadata !580), !dbg !1976
  store void (%struct.uv_fs_s*)* %cb, void (%struct.uv_fs_s*)** %cb.addr, align 8
  call void @llvm.dbg.declare(metadata void (%struct.uv_fs_s*)** %cb.addr, metadata !1977, metadata !580), !dbg !1978
  %0 = load %struct.uv_buf_t*, %struct.uv_buf_t** %bufs.addr, align 8, !dbg !1979
  %cmp = icmp eq %struct.uv_buf_t* %0, null, !dbg !1981
  br i1 %cmp, label %if.then, label %lor.lhs.false, !dbg !1982

lor.lhs.false:                                    ; preds = %entry
  %1 = load i32, i32* %nbufs.addr, align 4, !dbg !1983
  %cmp1 = icmp eq i32 %1, 0, !dbg !1985
  br i1 %cmp1, label %if.then, label %if.end, !dbg !1986

if.then:                                          ; preds = %lor.lhs.false, %entry
  store i32 -22, i32* %retval, align 4, !dbg !1987
  br label %do.end77, !dbg !1987

if.end:                                           ; preds = %lor.lhs.false
  br label %do.body, !dbg !1988

do.body:                                          ; preds = %if.end
  %2 = load %struct.uv_fs_s*, %struct.uv_fs_s** %req.addr, align 8, !dbg !1989
  %type = getelementptr inbounds %struct.uv_fs_s, %struct.uv_fs_s* %2, i32 0, i32 1, !dbg !1989
  store i32 6, i32* %type, align 8, !dbg !1989
  %3 = load void (%struct.uv_fs_s*)*, void (%struct.uv_fs_s*)** %cb.addr, align 8, !dbg !1989
  %cmp2 = icmp ne void (%struct.uv_fs_s*)* %3, null, !dbg !1989
  br i1 %cmp2, label %if.then3, label %if.end23, !dbg !1989

if.then3:                                         ; preds = %do.body
  br label %do.body4, !dbg !1992

do.body4:                                         ; preds = %if.then3
  br label %do.body5, !dbg !1995

do.body5:                                         ; preds = %do.body4
  %4 = load %struct.uv_fs_s*, %struct.uv_fs_s** %req.addr, align 8, !dbg !1998
  %type6 = getelementptr inbounds %struct.uv_fs_s, %struct.uv_fs_s* %4, i32 0, i32 1, !dbg !1998
  store i32 6, i32* %type6, align 8, !dbg !1998
  br label %do.end, !dbg !1998

do.end:                                           ; preds = %do.body5
  br label %do.body7, !dbg !2001

do.body7:                                         ; preds = %do.end
  br label %do.body8, !dbg !2003

do.body8:                                         ; preds = %do.body7
  %5 = load %struct.uv_loop_s*, %struct.uv_loop_s** %loop.addr, align 8, !dbg !2006
  %active_reqs = getelementptr inbounds %struct.uv_loop_s, %struct.uv_loop_s* %5, i32 0, i32 3, !dbg !2006
  %6 = load %struct.uv_fs_s*, %struct.uv_fs_s** %req.addr, align 8, !dbg !2006
  %active_queue = getelementptr inbounds %struct.uv_fs_s, %struct.uv_fs_s* %6, i32 0, i32 2, !dbg !2006
  %arrayidx = getelementptr inbounds [2 x i8*], [2 x i8*]* %active_queue, i64 0, i64 0, !dbg !2006
  %7 = bitcast i8** %arrayidx to [2 x i8*]**, !dbg !2006
  store [2 x i8*]* %active_reqs, [2 x i8*]** %7, align 8, !dbg !2006
  %8 = load %struct.uv_loop_s*, %struct.uv_loop_s** %loop.addr, align 8, !dbg !2006
  %active_reqs9 = getelementptr inbounds %struct.uv_loop_s, %struct.uv_loop_s* %8, i32 0, i32 3, !dbg !2006
  %arrayidx10 = getelementptr inbounds [2 x i8*], [2 x i8*]* %active_reqs9, i64 0, i64 1, !dbg !2006
  %9 = bitcast i8** %arrayidx10 to [2 x i8*]**, !dbg !2006
  %10 = load [2 x i8*]*, [2 x i8*]** %9, align 8, !dbg !2006
  %11 = load %struct.uv_fs_s*, %struct.uv_fs_s** %req.addr, align 8, !dbg !2006
  %active_queue11 = getelementptr inbounds %struct.uv_fs_s, %struct.uv_fs_s* %11, i32 0, i32 2, !dbg !2006
  %arrayidx12 = getelementptr inbounds [2 x i8*], [2 x i8*]* %active_queue11, i64 0, i64 1, !dbg !2006
  %12 = bitcast i8** %arrayidx12 to [2 x i8*]**, !dbg !2006
  store [2 x i8*]* %10, [2 x i8*]** %12, align 8, !dbg !2006
  %13 = load %struct.uv_fs_s*, %struct.uv_fs_s** %req.addr, align 8, !dbg !2006
  %active_queue13 = getelementptr inbounds %struct.uv_fs_s, %struct.uv_fs_s* %13, i32 0, i32 2, !dbg !2006
  %14 = load %struct.uv_fs_s*, %struct.uv_fs_s** %req.addr, align 8, !dbg !2006
  %active_queue14 = getelementptr inbounds %struct.uv_fs_s, %struct.uv_fs_s* %14, i32 0, i32 2, !dbg !2006
  %arrayidx15 = getelementptr inbounds [2 x i8*], [2 x i8*]* %active_queue14, i64 0, i64 1, !dbg !2006
  %15 = bitcast i8** %arrayidx15 to [2 x i8*]**, !dbg !2006
  %16 = load [2 x i8*]*, [2 x i8*]** %15, align 8, !dbg !2006
  %arrayidx16 = getelementptr inbounds [2 x i8*], [2 x i8*]* %16, i64 0, i64 0, !dbg !2006
  %17 = bitcast i8** %arrayidx16 to [2 x i8*]**, !dbg !2006
  store [2 x i8*]* %active_queue13, [2 x i8*]** %17, align 8, !dbg !2006
  %18 = load %struct.uv_fs_s*, %struct.uv_fs_s** %req.addr, align 8, !dbg !2006
  %active_queue17 = getelementptr inbounds %struct.uv_fs_s, %struct.uv_fs_s* %18, i32 0, i32 2, !dbg !2006
  %19 = load %struct.uv_loop_s*, %struct.uv_loop_s** %loop.addr, align 8, !dbg !2006
  %active_reqs18 = getelementptr inbounds %struct.uv_loop_s, %struct.uv_loop_s* %19, i32 0, i32 3, !dbg !2006
  %arrayidx19 = getelementptr inbounds [2 x i8*], [2 x i8*]* %active_reqs18, i64 0, i64 1, !dbg !2006
  %20 = bitcast i8** %arrayidx19 to [2 x i8*]**, !dbg !2006
  store [2 x i8*]* %active_queue17, [2 x i8*]** %20, align 8, !dbg !2006
  br label %do.end20, !dbg !2006

do.end20:                                         ; preds = %do.body8
  br label %do.end21, !dbg !2009

do.end21:                                         ; preds = %do.end20
  br label %do.end22, !dbg !2011

do.end22:                                         ; preds = %do.end21
  br label %if.end23, !dbg !2013

if.end23:                                         ; preds = %do.end22, %do.body
  %21 = load %struct.uv_fs_s*, %struct.uv_fs_s** %req.addr, align 8, !dbg !2015
  %fs_type = getelementptr inbounds %struct.uv_fs_s, %struct.uv_fs_s* %21, i32 0, i32 4, !dbg !2015
  store i32 3, i32* %fs_type, align 8, !dbg !2015
  %22 = load %struct.uv_fs_s*, %struct.uv_fs_s** %req.addr, align 8, !dbg !2015
  %result = getelementptr inbounds %struct.uv_fs_s, %struct.uv_fs_s* %22, i32 0, i32 7, !dbg !2015
  store i64 0, i64* %result, align 8, !dbg !2015
  %23 = load %struct.uv_fs_s*, %struct.uv_fs_s** %req.addr, align 8, !dbg !2015
  %ptr = getelementptr inbounds %struct.uv_fs_s, %struct.uv_fs_s* %23, i32 0, i32 8, !dbg !2015
  store i8* null, i8** %ptr, align 8, !dbg !2015
  %24 = load %struct.uv_loop_s*, %struct.uv_loop_s** %loop.addr, align 8, !dbg !2015
  %25 = load %struct.uv_fs_s*, %struct.uv_fs_s** %req.addr, align 8, !dbg !2015
  %loop24 = getelementptr inbounds %struct.uv_fs_s, %struct.uv_fs_s* %25, i32 0, i32 5, !dbg !2015
  store %struct.uv_loop_s* %24, %struct.uv_loop_s** %loop24, align 8, !dbg !2015
  %26 = load %struct.uv_fs_s*, %struct.uv_fs_s** %req.addr, align 8, !dbg !2015
  %path = getelementptr inbounds %struct.uv_fs_s, %struct.uv_fs_s* %26, i32 0, i32 9, !dbg !2015
  store i8* null, i8** %path, align 8, !dbg !2015
  %27 = load %struct.uv_fs_s*, %struct.uv_fs_s** %req.addr, align 8, !dbg !2015
  %new_path = getelementptr inbounds %struct.uv_fs_s, %struct.uv_fs_s* %27, i32 0, i32 11, !dbg !2015
  store i8* null, i8** %new_path, align 8, !dbg !2015
  %28 = load void (%struct.uv_fs_s*)*, void (%struct.uv_fs_s*)** %cb.addr, align 8, !dbg !2015
  %29 = load %struct.uv_fs_s*, %struct.uv_fs_s** %req.addr, align 8, !dbg !2015
  %cb25 = getelementptr inbounds %struct.uv_fs_s, %struct.uv_fs_s* %29, i32 0, i32 6, !dbg !2015
  store void (%struct.uv_fs_s*)* %28, void (%struct.uv_fs_s*)** %cb25, align 8, !dbg !2015
  br label %do.end26, !dbg !2015

do.end26:                                         ; preds = %if.end23
  %30 = load i32, i32* %file.addr, align 4, !dbg !2017
  %31 = load %struct.uv_fs_s*, %struct.uv_fs_s** %req.addr, align 8, !dbg !2018
  %file27 = getelementptr inbounds %struct.uv_fs_s, %struct.uv_fs_s* %31, i32 0, i32 12, !dbg !2019
  store i32 %30, i32* %file27, align 8, !dbg !2020
  %32 = load i32, i32* %nbufs.addr, align 4, !dbg !2021
  %33 = load %struct.uv_fs_s*, %struct.uv_fs_s** %req.addr, align 8, !dbg !2022
  %nbufs28 = getelementptr inbounds %struct.uv_fs_s, %struct.uv_fs_s* %33, i32 0, i32 15, !dbg !2023
  store i32 %32, i32* %nbufs28, align 4, !dbg !2024
  %34 = load %struct.uv_fs_s*, %struct.uv_fs_s** %req.addr, align 8, !dbg !2025
  %bufsml = getelementptr inbounds %struct.uv_fs_s, %struct.uv_fs_s* %34, i32 0, i32 23, !dbg !2026
  %arraydecay = getelementptr inbounds [4 x %struct.uv_buf_t], [4 x %struct.uv_buf_t]* %bufsml, i32 0, i32 0, !dbg !2025
  %35 = load %struct.uv_fs_s*, %struct.uv_fs_s** %req.addr, align 8, !dbg !2027
  %bufs29 = getelementptr inbounds %struct.uv_fs_s, %struct.uv_fs_s* %35, i32 0, i32 16, !dbg !2028
  store %struct.uv_buf_t* %arraydecay, %struct.uv_buf_t** %bufs29, align 8, !dbg !2029
  %36 = load i32, i32* %nbufs.addr, align 4, !dbg !2030
  %conv = zext i32 %36 to i64, !dbg !2030
  %cmp30 = icmp ugt i64 %conv, 4, !dbg !2032
  br i1 %cmp30, label %if.then32, label %if.end35, !dbg !2033

if.then32:                                        ; preds = %do.end26
  %37 = load i32, i32* %nbufs.addr, align 4, !dbg !2034
  %conv33 = zext i32 %37 to i64, !dbg !2034
  %mul = mul i64 %conv33, 16, !dbg !2035
  %call = call i8* @uv__malloc(i64 %mul), !dbg !2036
  %38 = bitcast i8* %call to %struct.uv_buf_t*, !dbg !2036
  %39 = load %struct.uv_fs_s*, %struct.uv_fs_s** %req.addr, align 8, !dbg !2037
  %bufs34 = getelementptr inbounds %struct.uv_fs_s, %struct.uv_fs_s* %39, i32 0, i32 16, !dbg !2038
  store %struct.uv_buf_t* %38, %struct.uv_buf_t** %bufs34, align 8, !dbg !2039
  br label %if.end35, !dbg !2037

if.end35:                                         ; preds = %if.then32, %do.end26
  %40 = load %struct.uv_fs_s*, %struct.uv_fs_s** %req.addr, align 8, !dbg !2040
  %bufs36 = getelementptr inbounds %struct.uv_fs_s, %struct.uv_fs_s* %40, i32 0, i32 16, !dbg !2042
  %41 = load %struct.uv_buf_t*, %struct.uv_buf_t** %bufs36, align 8, !dbg !2042
  %cmp37 = icmp eq %struct.uv_buf_t* %41, null, !dbg !2043
  br i1 %cmp37, label %if.then39, label %if.end65, !dbg !2044

if.then39:                                        ; preds = %if.end35
  %42 = load void (%struct.uv_fs_s*)*, void (%struct.uv_fs_s*)** %cb.addr, align 8, !dbg !2045
  %cmp40 = icmp ne void (%struct.uv_fs_s*)* %42, null, !dbg !2048
  br i1 %cmp40, label %if.then42, label %if.end64, !dbg !2049

if.then42:                                        ; preds = %if.then39
  br label %do.body43, !dbg !2050

do.body43:                                        ; preds = %if.then42
  %43 = load %struct.uv_loop_s*, %struct.uv_loop_s** %loop.addr, align 8, !dbg !2051
  %active_reqs44 = getelementptr inbounds %struct.uv_loop_s, %struct.uv_loop_s* %43, i32 0, i32 3, !dbg !2051
  %44 = load %struct.uv_loop_s*, %struct.uv_loop_s** %loop.addr, align 8, !dbg !2051
  %active_reqs45 = getelementptr inbounds %struct.uv_loop_s, %struct.uv_loop_s* %44, i32 0, i32 3, !dbg !2051
  %arrayidx46 = getelementptr inbounds [2 x i8*], [2 x i8*]* %active_reqs45, i64 0, i64 0, !dbg !2051
  %45 = bitcast i8** %arrayidx46 to [2 x i8*]**, !dbg !2051
  %46 = load [2 x i8*]*, [2 x i8*]** %45, align 8, !dbg !2051
  %cmp47 = icmp eq [2 x i8*]* %active_reqs44, %46, !dbg !2051
  %conv48 = zext i1 %cmp47 to i32, !dbg !2051
  %cmp49 = icmp eq i32 %conv48, 0, !dbg !2051
  br i1 %cmp49, label %cond.true, label %cond.false, !dbg !2051

cond.true:                                        ; preds = %do.body43
  br label %cond.end, !dbg !2054

cond.false:                                       ; preds = %do.body43
  call void @__assert_fail(i8* getelementptr inbounds ([113 x i8], [113 x i8]* @.str.2, i32 0, i32 0), i8* getelementptr inbounds ([66 x i8], [66 x i8]* @.str.1, i32 0, i32 0), i32 1212, i8* getelementptr inbounds ([99 x i8], [99 x i8]* @__PRETTY_FUNCTION__.uv_fs_read, i32 0, i32 0)) #8, !dbg !2056
  unreachable, !dbg !2056
                                                  ; No predecessors!
  br label %cond.end, !dbg !2058

cond.end:                                         ; preds = %47, %cond.true
  br label %do.body51, !dbg !2060

do.body51:                                        ; preds = %cond.end
  %48 = load %struct.uv_fs_s*, %struct.uv_fs_s** %req.addr, align 8, !dbg !2062
  %active_queue52 = getelementptr inbounds %struct.uv_fs_s, %struct.uv_fs_s* %48, i32 0, i32 2, !dbg !2062
  %arrayidx53 = getelementptr inbounds [2 x i8*], [2 x i8*]* %active_queue52, i64 0, i64 0, !dbg !2062
  %49 = bitcast i8** %arrayidx53 to [2 x i8*]**, !dbg !2062
  %50 = load [2 x i8*]*, [2 x i8*]** %49, align 8, !dbg !2062
  %51 = load %struct.uv_fs_s*, %struct.uv_fs_s** %req.addr, align 8, !dbg !2062
  %active_queue54 = getelementptr inbounds %struct.uv_fs_s, %struct.uv_fs_s* %51, i32 0, i32 2, !dbg !2062
  %arrayidx55 = getelementptr inbounds [2 x i8*], [2 x i8*]* %active_queue54, i64 0, i64 1, !dbg !2062
  %52 = bitcast i8** %arrayidx55 to [2 x i8*]**, !dbg !2062
  %53 = load [2 x i8*]*, [2 x i8*]** %52, align 8, !dbg !2062
  %arrayidx56 = getelementptr inbounds [2 x i8*], [2 x i8*]* %53, i64 0, i64 0, !dbg !2062
  %54 = bitcast i8** %arrayidx56 to [2 x i8*]**, !dbg !2062
  store [2 x i8*]* %50, [2 x i8*]** %54, align 8, !dbg !2062
  %55 = load %struct.uv_fs_s*, %struct.uv_fs_s** %req.addr, align 8, !dbg !2062
  %active_queue57 = getelementptr inbounds %struct.uv_fs_s, %struct.uv_fs_s* %55, i32 0, i32 2, !dbg !2062
  %arrayidx58 = getelementptr inbounds [2 x i8*], [2 x i8*]* %active_queue57, i64 0, i64 1, !dbg !2062
  %56 = bitcast i8** %arrayidx58 to [2 x i8*]**, !dbg !2062
  %57 = load [2 x i8*]*, [2 x i8*]** %56, align 8, !dbg !2062
  %58 = load %struct.uv_fs_s*, %struct.uv_fs_s** %req.addr, align 8, !dbg !2062
  %active_queue59 = getelementptr inbounds %struct.uv_fs_s, %struct.uv_fs_s* %58, i32 0, i32 2, !dbg !2062
  %arrayidx60 = getelementptr inbounds [2 x i8*], [2 x i8*]* %active_queue59, i64 0, i64 0, !dbg !2062
  %59 = bitcast i8** %arrayidx60 to [2 x i8*]**, !dbg !2062
  %60 = load [2 x i8*]*, [2 x i8*]** %59, align 8, !dbg !2062
  %arrayidx61 = getelementptr inbounds [2 x i8*], [2 x i8*]* %60, i64 0, i64 1, !dbg !2062
  %61 = bitcast i8** %arrayidx61 to [2 x i8*]**, !dbg !2062
  store [2 x i8*]* %57, [2 x i8*]** %61, align 8, !dbg !2062
  br label %do.end62, !dbg !2062

do.end62:                                         ; preds = %do.body51
  br label %do.end63, !dbg !2065

do.end63:                                         ; preds = %do.end62
  br label %if.end64, !dbg !2067

if.end64:                                         ; preds = %do.end63, %if.then39
  store i32 -12, i32* %retval, align 4, !dbg !2069
  br label %do.end77, !dbg !2069

if.end65:                                         ; preds = %if.end35
  %62 = load %struct.uv_fs_s*, %struct.uv_fs_s** %req.addr, align 8, !dbg !2070
  %bufs66 = getelementptr inbounds %struct.uv_fs_s, %struct.uv_fs_s* %62, i32 0, i32 16, !dbg !2071
  %63 = load %struct.uv_buf_t*, %struct.uv_buf_t** %bufs66, align 8, !dbg !2071
  %64 = bitcast %struct.uv_buf_t* %63 to i8*, !dbg !2072
  %65 = load %struct.uv_buf_t*, %struct.uv_buf_t** %bufs.addr, align 8, !dbg !2073
  %66 = bitcast %struct.uv_buf_t* %65 to i8*, !dbg !2072
  %67 = load i32, i32* %nbufs.addr, align 4, !dbg !2074
  %conv67 = zext i32 %67 to i64, !dbg !2074
  %mul68 = mul i64 %conv67, 16, !dbg !2075
  call void @llvm.memcpy.p0i8.p0i8.i64(i8* %64, i8* %66, i64 %mul68, i32 8, i1 false), !dbg !2072
  %68 = load i64, i64* %off.addr, align 8, !dbg !2076
  %69 = load %struct.uv_fs_s*, %struct.uv_fs_s** %req.addr, align 8, !dbg !2077
  %off69 = getelementptr inbounds %struct.uv_fs_s, %struct.uv_fs_s* %69, i32 0, i32 17, !dbg !2078
  store i64 %68, i64* %off69, align 8, !dbg !2079
  br label %do.body70, !dbg !2080

do.body70:                                        ; preds = %if.end65
  %70 = load void (%struct.uv_fs_s*)*, void (%struct.uv_fs_s*)** %cb.addr, align 8, !dbg !2081
  %cmp71 = icmp ne void (%struct.uv_fs_s*)* %70, null, !dbg !2081
  br i1 %cmp71, label %if.then73, label %if.else, !dbg !2081

if.then73:                                        ; preds = %do.body70
  %71 = load %struct.uv_loop_s*, %struct.uv_loop_s** %loop.addr, align 8, !dbg !2085
  %72 = load %struct.uv_fs_s*, %struct.uv_fs_s** %req.addr, align 8, !dbg !2085
  %work_req = getelementptr inbounds %struct.uv_fs_s, %struct.uv_fs_s* %72, i32 0, i32 22, !dbg !2085
  call void @uv__work_submit(%struct.uv_loop_s* %71, %struct.uv__work* %work_req, void (%struct.uv__work*)* @uv__fs_work, void (%struct.uv__work*, i32)* @uv__fs_done), !dbg !2085
  store i32 0, i32* %retval, align 4, !dbg !2085
  br label %do.end77, !dbg !2085

if.else:                                          ; preds = %do.body70
  %73 = load %struct.uv_fs_s*, %struct.uv_fs_s** %req.addr, align 8, !dbg !2088
  %work_req74 = getelementptr inbounds %struct.uv_fs_s, %struct.uv_fs_s* %73, i32 0, i32 22, !dbg !2088
  call void @uv__fs_work(%struct.uv__work* %work_req74), !dbg !2088
  %74 = load %struct.uv_fs_s*, %struct.uv_fs_s** %req.addr, align 8, !dbg !2088
  %result75 = getelementptr inbounds %struct.uv_fs_s, %struct.uv_fs_s* %74, i32 0, i32 7, !dbg !2088
  %75 = load i64, i64* %result75, align 8, !dbg !2088
  %conv76 = trunc i64 %75 to i32, !dbg !2088
  store i32 %conv76, i32* %retval, align 4, !dbg !2088
  br label %do.end77, !dbg !2088

do.end77:                                         ; preds = %if.then, %if.end64, %if.then73, %if.else
  %76 = load i32, i32* %retval, align 4, !dbg !2091
  ret i32 %76, !dbg !2091
}

; Function Attrs: nounwind uwtable
define i32 @uv_fs_scandir(%struct.uv_loop_s* %loop, %struct.uv_fs_s* %req, i8* %path, i32 %flags, void (%struct.uv_fs_s*)* %cb) #0 !dbg !458 {
entry:
  %retval = alloca i32, align 4
  %loop.addr = alloca %struct.uv_loop_s*, align 8
  %req.addr = alloca %struct.uv_fs_s*, align 8
  %path.addr = alloca i8*, align 8
  %flags.addr = alloca i32, align 4
  %cb.addr = alloca void (%struct.uv_fs_s*)*, align 8
  store %struct.uv_loop_s* %loop, %struct.uv_loop_s** %loop.addr, align 8
  call void @llvm.dbg.declare(metadata %struct.uv_loop_s** %loop.addr, metadata !2092, metadata !580), !dbg !2093
  store %struct.uv_fs_s* %req, %struct.uv_fs_s** %req.addr, align 8
  call void @llvm.dbg.declare(metadata %struct.uv_fs_s** %req.addr, metadata !2094, metadata !580), !dbg !2095
  store i8* %path, i8** %path.addr, align 8
  call void @llvm.dbg.declare(metadata i8** %path.addr, metadata !2096, metadata !580), !dbg !2097
  store i32 %flags, i32* %flags.addr, align 4
  call void @llvm.dbg.declare(metadata i32* %flags.addr, metadata !2098, metadata !580), !dbg !2099
  store void (%struct.uv_fs_s*)* %cb, void (%struct.uv_fs_s*)** %cb.addr, align 8
  call void @llvm.dbg.declare(metadata void (%struct.uv_fs_s*)** %cb.addr, metadata !2100, metadata !580), !dbg !2101
  br label %do.body, !dbg !2102

do.body:                                          ; preds = %entry
  %0 = load %struct.uv_fs_s*, %struct.uv_fs_s** %req.addr, align 8, !dbg !2103
  %type = getelementptr inbounds %struct.uv_fs_s, %struct.uv_fs_s* %0, i32 0, i32 1, !dbg !2103
  store i32 6, i32* %type, align 8, !dbg !2103
  %1 = load void (%struct.uv_fs_s*)*, void (%struct.uv_fs_s*)** %cb.addr, align 8, !dbg !2103
  %cmp = icmp ne void (%struct.uv_fs_s*)* %1, null, !dbg !2103
  br i1 %cmp, label %if.then, label %if.end, !dbg !2103

if.then:                                          ; preds = %do.body
  br label %do.body1, !dbg !2106

do.body1:                                         ; preds = %if.then
  br label %do.body2, !dbg !2109

do.body2:                                         ; preds = %do.body1
  %2 = load %struct.uv_fs_s*, %struct.uv_fs_s** %req.addr, align 8, !dbg !2112
  %type3 = getelementptr inbounds %struct.uv_fs_s, %struct.uv_fs_s* %2, i32 0, i32 1, !dbg !2112
  store i32 6, i32* %type3, align 8, !dbg !2112
  br label %do.end, !dbg !2112

do.end:                                           ; preds = %do.body2
  br label %do.body4, !dbg !2115

do.body4:                                         ; preds = %do.end
  br label %do.body5, !dbg !2117

do.body5:                                         ; preds = %do.body4
  %3 = load %struct.uv_loop_s*, %struct.uv_loop_s** %loop.addr, align 8, !dbg !2120
  %active_reqs = getelementptr inbounds %struct.uv_loop_s, %struct.uv_loop_s* %3, i32 0, i32 3, !dbg !2120
  %4 = load %struct.uv_fs_s*, %struct.uv_fs_s** %req.addr, align 8, !dbg !2120
  %active_queue = getelementptr inbounds %struct.uv_fs_s, %struct.uv_fs_s* %4, i32 0, i32 2, !dbg !2120
  %arrayidx = getelementptr inbounds [2 x i8*], [2 x i8*]* %active_queue, i64 0, i64 0, !dbg !2120
  %5 = bitcast i8** %arrayidx to [2 x i8*]**, !dbg !2120
  store [2 x i8*]* %active_reqs, [2 x i8*]** %5, align 8, !dbg !2120
  %6 = load %struct.uv_loop_s*, %struct.uv_loop_s** %loop.addr, align 8, !dbg !2120
  %active_reqs6 = getelementptr inbounds %struct.uv_loop_s, %struct.uv_loop_s* %6, i32 0, i32 3, !dbg !2120
  %arrayidx7 = getelementptr inbounds [2 x i8*], [2 x i8*]* %active_reqs6, i64 0, i64 1, !dbg !2120
  %7 = bitcast i8** %arrayidx7 to [2 x i8*]**, !dbg !2120
  %8 = load [2 x i8*]*, [2 x i8*]** %7, align 8, !dbg !2120
  %9 = load %struct.uv_fs_s*, %struct.uv_fs_s** %req.addr, align 8, !dbg !2120
  %active_queue8 = getelementptr inbounds %struct.uv_fs_s, %struct.uv_fs_s* %9, i32 0, i32 2, !dbg !2120
  %arrayidx9 = getelementptr inbounds [2 x i8*], [2 x i8*]* %active_queue8, i64 0, i64 1, !dbg !2120
  %10 = bitcast i8** %arrayidx9 to [2 x i8*]**, !dbg !2120
  store [2 x i8*]* %8, [2 x i8*]** %10, align 8, !dbg !2120
  %11 = load %struct.uv_fs_s*, %struct.uv_fs_s** %req.addr, align 8, !dbg !2120
  %active_queue10 = getelementptr inbounds %struct.uv_fs_s, %struct.uv_fs_s* %11, i32 0, i32 2, !dbg !2120
  %12 = load %struct.uv_fs_s*, %struct.uv_fs_s** %req.addr, align 8, !dbg !2120
  %active_queue11 = getelementptr inbounds %struct.uv_fs_s, %struct.uv_fs_s* %12, i32 0, i32 2, !dbg !2120
  %arrayidx12 = getelementptr inbounds [2 x i8*], [2 x i8*]* %active_queue11, i64 0, i64 1, !dbg !2120
  %13 = bitcast i8** %arrayidx12 to [2 x i8*]**, !dbg !2120
  %14 = load [2 x i8*]*, [2 x i8*]** %13, align 8, !dbg !2120
  %arrayidx13 = getelementptr inbounds [2 x i8*], [2 x i8*]* %14, i64 0, i64 0, !dbg !2120
  %15 = bitcast i8** %arrayidx13 to [2 x i8*]**, !dbg !2120
  store [2 x i8*]* %active_queue10, [2 x i8*]** %15, align 8, !dbg !2120
  %16 = load %struct.uv_fs_s*, %struct.uv_fs_s** %req.addr, align 8, !dbg !2120
  %active_queue14 = getelementptr inbounds %struct.uv_fs_s, %struct.uv_fs_s* %16, i32 0, i32 2, !dbg !2120
  %17 = load %struct.uv_loop_s*, %struct.uv_loop_s** %loop.addr, align 8, !dbg !2120
  %active_reqs15 = getelementptr inbounds %struct.uv_loop_s, %struct.uv_loop_s* %17, i32 0, i32 3, !dbg !2120
  %arrayidx16 = getelementptr inbounds [2 x i8*], [2 x i8*]* %active_reqs15, i64 0, i64 1, !dbg !2120
  %18 = bitcast i8** %arrayidx16 to [2 x i8*]**, !dbg !2120
  store [2 x i8*]* %active_queue14, [2 x i8*]** %18, align 8, !dbg !2120
  br label %do.end17, !dbg !2120

do.end17:                                         ; preds = %do.body5
  br label %do.end18, !dbg !2123

do.end18:                                         ; preds = %do.end17
  br label %do.end19, !dbg !2125

do.end19:                                         ; preds = %do.end18
  br label %if.end, !dbg !2127

if.end:                                           ; preds = %do.end19, %do.body
  %19 = load %struct.uv_fs_s*, %struct.uv_fs_s** %req.addr, align 8, !dbg !2129
  %fs_type = getelementptr inbounds %struct.uv_fs_s, %struct.uv_fs_s* %19, i32 0, i32 4, !dbg !2129
  store i32 22, i32* %fs_type, align 8, !dbg !2129
  %20 = load %struct.uv_fs_s*, %struct.uv_fs_s** %req.addr, align 8, !dbg !2129
  %result = getelementptr inbounds %struct.uv_fs_s, %struct.uv_fs_s* %20, i32 0, i32 7, !dbg !2129
  store i64 0, i64* %result, align 8, !dbg !2129
  %21 = load %struct.uv_fs_s*, %struct.uv_fs_s** %req.addr, align 8, !dbg !2129
  %ptr = getelementptr inbounds %struct.uv_fs_s, %struct.uv_fs_s* %21, i32 0, i32 8, !dbg !2129
  store i8* null, i8** %ptr, align 8, !dbg !2129
  %22 = load %struct.uv_loop_s*, %struct.uv_loop_s** %loop.addr, align 8, !dbg !2129
  %23 = load %struct.uv_fs_s*, %struct.uv_fs_s** %req.addr, align 8, !dbg !2129
  %loop20 = getelementptr inbounds %struct.uv_fs_s, %struct.uv_fs_s* %23, i32 0, i32 5, !dbg !2129
  store %struct.uv_loop_s* %22, %struct.uv_loop_s** %loop20, align 8, !dbg !2129
  %24 = load %struct.uv_fs_s*, %struct.uv_fs_s** %req.addr, align 8, !dbg !2129
  %path21 = getelementptr inbounds %struct.uv_fs_s, %struct.uv_fs_s* %24, i32 0, i32 9, !dbg !2129
  store i8* null, i8** %path21, align 8, !dbg !2129
  %25 = load %struct.uv_fs_s*, %struct.uv_fs_s** %req.addr, align 8, !dbg !2129
  %new_path = getelementptr inbounds %struct.uv_fs_s, %struct.uv_fs_s* %25, i32 0, i32 11, !dbg !2129
  store i8* null, i8** %new_path, align 8, !dbg !2129
  %26 = load void (%struct.uv_fs_s*)*, void (%struct.uv_fs_s*)** %cb.addr, align 8, !dbg !2129
  %27 = load %struct.uv_fs_s*, %struct.uv_fs_s** %req.addr, align 8, !dbg !2129
  %cb22 = getelementptr inbounds %struct.uv_fs_s, %struct.uv_fs_s* %27, i32 0, i32 6, !dbg !2129
  store void (%struct.uv_fs_s*)* %26, void (%struct.uv_fs_s*)** %cb22, align 8, !dbg !2129
  br label %do.end23, !dbg !2129

do.end23:                                         ; preds = %if.end
  br label %do.body24, !dbg !2131

do.body24:                                        ; preds = %do.end23
  %28 = load i8*, i8** %path.addr, align 8, !dbg !2132
  %cmp25 = icmp ne i8* %28, null, !dbg !2132
  br i1 %cmp25, label %cond.true, label %cond.false, !dbg !2132

cond.true:                                        ; preds = %do.body24
  br label %cond.end, !dbg !2135

cond.false:                                       ; preds = %do.body24
  call void @__assert_fail(i8* getelementptr inbounds ([19 x i8], [19 x i8]* @.str, i32 0, i32 0), i8* getelementptr inbounds ([66 x i8], [66 x i8]* @.str.1, i32 0, i32 0), i32 1229, i8* getelementptr inbounds ([71 x i8], [71 x i8]* @__PRETTY_FUNCTION__.uv_fs_scandir, i32 0, i32 0)) #8, !dbg !2137
  unreachable, !dbg !2137
                                                  ; No predecessors!
  br label %cond.end, !dbg !2139

cond.end:                                         ; preds = %29, %cond.true
  %30 = load void (%struct.uv_fs_s*)*, void (%struct.uv_fs_s*)** %cb.addr, align 8, !dbg !2141
  %cmp26 = icmp eq void (%struct.uv_fs_s*)* %30, null, !dbg !2141
  br i1 %cmp26, label %if.then27, label %if.else, !dbg !2141

if.then27:                                        ; preds = %cond.end
  %31 = load i8*, i8** %path.addr, align 8, !dbg !2144
  %32 = load %struct.uv_fs_s*, %struct.uv_fs_s** %req.addr, align 8, !dbg !2144
  %path28 = getelementptr inbounds %struct.uv_fs_s, %struct.uv_fs_s* %32, i32 0, i32 9, !dbg !2144
  store i8* %31, i8** %path28, align 8, !dbg !2144
  br label %if.end57, !dbg !2144

if.else:                                          ; preds = %cond.end
  %33 = load i8*, i8** %path.addr, align 8, !dbg !2147
  %call = call i8* @uv__strdup(i8* %33), !dbg !2147
  %34 = load %struct.uv_fs_s*, %struct.uv_fs_s** %req.addr, align 8, !dbg !2147
  %path29 = getelementptr inbounds %struct.uv_fs_s, %struct.uv_fs_s* %34, i32 0, i32 9, !dbg !2147
  store i8* %call, i8** %path29, align 8, !dbg !2147
  %35 = load %struct.uv_fs_s*, %struct.uv_fs_s** %req.addr, align 8, !dbg !2147
  %path30 = getelementptr inbounds %struct.uv_fs_s, %struct.uv_fs_s* %35, i32 0, i32 9, !dbg !2147
  %36 = load i8*, i8** %path30, align 8, !dbg !2147
  %cmp31 = icmp eq i8* %36, null, !dbg !2147
  br i1 %cmp31, label %if.then32, label %if.end56, !dbg !2147

if.then32:                                        ; preds = %if.else
  br label %do.body33, !dbg !2150

do.body33:                                        ; preds = %if.then32
  %37 = load %struct.uv_loop_s*, %struct.uv_loop_s** %loop.addr, align 8, !dbg !2154
  %active_reqs34 = getelementptr inbounds %struct.uv_loop_s, %struct.uv_loop_s* %37, i32 0, i32 3, !dbg !2154
  %38 = load %struct.uv_loop_s*, %struct.uv_loop_s** %loop.addr, align 8, !dbg !2154
  %active_reqs35 = getelementptr inbounds %struct.uv_loop_s, %struct.uv_loop_s* %38, i32 0, i32 3, !dbg !2154
  %arrayidx36 = getelementptr inbounds [2 x i8*], [2 x i8*]* %active_reqs35, i64 0, i64 0, !dbg !2154
  %39 = bitcast i8** %arrayidx36 to [2 x i8*]**, !dbg !2154
  %40 = load [2 x i8*]*, [2 x i8*]** %39, align 8, !dbg !2154
  %cmp37 = icmp eq [2 x i8*]* %active_reqs34, %40, !dbg !2154
  %conv = zext i1 %cmp37 to i32, !dbg !2154
  %cmp38 = icmp eq i32 %conv, 0, !dbg !2154
  br i1 %cmp38, label %cond.true40, label %cond.false41, !dbg !2154

cond.true40:                                      ; preds = %do.body33
  br label %cond.end42, !dbg !2157

cond.false41:                                     ; preds = %do.body33
  call void @__assert_fail(i8* getelementptr inbounds ([113 x i8], [113 x i8]* @.str.2, i32 0, i32 0), i8* getelementptr inbounds ([66 x i8], [66 x i8]* @.str.1, i32 0, i32 0), i32 1229, i8* getelementptr inbounds ([71 x i8], [71 x i8]* @__PRETTY_FUNCTION__.uv_fs_scandir, i32 0, i32 0)) #8, !dbg !2159
  unreachable, !dbg !2159
                                                  ; No predecessors!
  br label %cond.end42, !dbg !2161

cond.end42:                                       ; preds = %41, %cond.true40
  br label %do.body43, !dbg !2163

do.body43:                                        ; preds = %cond.end42
  %42 = load %struct.uv_fs_s*, %struct.uv_fs_s** %req.addr, align 8, !dbg !2165
  %active_queue44 = getelementptr inbounds %struct.uv_fs_s, %struct.uv_fs_s* %42, i32 0, i32 2, !dbg !2165
  %arrayidx45 = getelementptr inbounds [2 x i8*], [2 x i8*]* %active_queue44, i64 0, i64 0, !dbg !2165
  %43 = bitcast i8** %arrayidx45 to [2 x i8*]**, !dbg !2165
  %44 = load [2 x i8*]*, [2 x i8*]** %43, align 8, !dbg !2165
  %45 = load %struct.uv_fs_s*, %struct.uv_fs_s** %req.addr, align 8, !dbg !2165
  %active_queue46 = getelementptr inbounds %struct.uv_fs_s, %struct.uv_fs_s* %45, i32 0, i32 2, !dbg !2165
  %arrayidx47 = getelementptr inbounds [2 x i8*], [2 x i8*]* %active_queue46, i64 0, i64 1, !dbg !2165
  %46 = bitcast i8** %arrayidx47 to [2 x i8*]**, !dbg !2165
  %47 = load [2 x i8*]*, [2 x i8*]** %46, align 8, !dbg !2165
  %arrayidx48 = getelementptr inbounds [2 x i8*], [2 x i8*]* %47, i64 0, i64 0, !dbg !2165
  %48 = bitcast i8** %arrayidx48 to [2 x i8*]**, !dbg !2165
  store [2 x i8*]* %44, [2 x i8*]** %48, align 8, !dbg !2165
  %49 = load %struct.uv_fs_s*, %struct.uv_fs_s** %req.addr, align 8, !dbg !2165
  %active_queue49 = getelementptr inbounds %struct.uv_fs_s, %struct.uv_fs_s* %49, i32 0, i32 2, !dbg !2165
  %arrayidx50 = getelementptr inbounds [2 x i8*], [2 x i8*]* %active_queue49, i64 0, i64 1, !dbg !2165
  %50 = bitcast i8** %arrayidx50 to [2 x i8*]**, !dbg !2165
  %51 = load [2 x i8*]*, [2 x i8*]** %50, align 8, !dbg !2165
  %52 = load %struct.uv_fs_s*, %struct.uv_fs_s** %req.addr, align 8, !dbg !2165
  %active_queue51 = getelementptr inbounds %struct.uv_fs_s, %struct.uv_fs_s* %52, i32 0, i32 2, !dbg !2165
  %arrayidx52 = getelementptr inbounds [2 x i8*], [2 x i8*]* %active_queue51, i64 0, i64 0, !dbg !2165
  %53 = bitcast i8** %arrayidx52 to [2 x i8*]**, !dbg !2165
  %54 = load [2 x i8*]*, [2 x i8*]** %53, align 8, !dbg !2165
  %arrayidx53 = getelementptr inbounds [2 x i8*], [2 x i8*]* %54, i64 0, i64 1, !dbg !2165
  %55 = bitcast i8** %arrayidx53 to [2 x i8*]**, !dbg !2165
  store [2 x i8*]* %51, [2 x i8*]** %55, align 8, !dbg !2165
  br label %do.end54, !dbg !2165

do.end54:                                         ; preds = %do.body43
  br label %do.end55, !dbg !2168

do.end55:                                         ; preds = %do.end54
  store i32 -12, i32* %retval, align 4, !dbg !2170
  br label %do.end68, !dbg !2170

if.end56:                                         ; preds = %if.else
  br label %if.end57

if.end57:                                         ; preds = %if.end56, %if.then27
  br label %do.end58, !dbg !2172

do.end58:                                         ; preds = %if.end57
  %56 = load i32, i32* %flags.addr, align 4, !dbg !2174
  %57 = load %struct.uv_fs_s*, %struct.uv_fs_s** %req.addr, align 8, !dbg !2175
  %flags59 = getelementptr inbounds %struct.uv_fs_s, %struct.uv_fs_s* %57, i32 0, i32 13, !dbg !2176
  store i32 %56, i32* %flags59, align 4, !dbg !2177
  br label %do.body60, !dbg !2178

do.body60:                                        ; preds = %do.end58
  %58 = load void (%struct.uv_fs_s*)*, void (%struct.uv_fs_s*)** %cb.addr, align 8, !dbg !2179
  %cmp61 = icmp ne void (%struct.uv_fs_s*)* %58, null, !dbg !2179
  br i1 %cmp61, label %if.then63, label %if.else64, !dbg !2179

if.then63:                                        ; preds = %do.body60
  %59 = load %struct.uv_loop_s*, %struct.uv_loop_s** %loop.addr, align 8, !dbg !2183
  %60 = load %struct.uv_fs_s*, %struct.uv_fs_s** %req.addr, align 8, !dbg !2183
  %work_req = getelementptr inbounds %struct.uv_fs_s, %struct.uv_fs_s* %60, i32 0, i32 22, !dbg !2183
  call void @uv__work_submit(%struct.uv_loop_s* %59, %struct.uv__work* %work_req, void (%struct.uv__work*)* @uv__fs_work, void (%struct.uv__work*, i32)* @uv__fs_done), !dbg !2183
  store i32 0, i32* %retval, align 4, !dbg !2183
  br label %do.end68, !dbg !2183

if.else64:                                        ; preds = %do.body60
  %61 = load %struct.uv_fs_s*, %struct.uv_fs_s** %req.addr, align 8, !dbg !2186
  %work_req65 = getelementptr inbounds %struct.uv_fs_s, %struct.uv_fs_s* %61, i32 0, i32 22, !dbg !2186
  call void @uv__fs_work(%struct.uv__work* %work_req65), !dbg !2186
  %62 = load %struct.uv_fs_s*, %struct.uv_fs_s** %req.addr, align 8, !dbg !2186
  %result66 = getelementptr inbounds %struct.uv_fs_s, %struct.uv_fs_s* %62, i32 0, i32 7, !dbg !2186
  %63 = load i64, i64* %result66, align 8, !dbg !2186
  %conv67 = trunc i64 %63 to i32, !dbg !2186
  store i32 %conv67, i32* %retval, align 4, !dbg !2186
  br label %do.end68, !dbg !2186

do.end68:                                         ; preds = %do.end55, %if.then63, %if.else64
  %64 = load i32, i32* %retval, align 4, !dbg !2189
  ret i32 %64, !dbg !2189
}

; Function Attrs: nounwind uwtable
define i32 @uv_fs_readlink(%struct.uv_loop_s* %loop, %struct.uv_fs_s* %req, i8* %path, void (%struct.uv_fs_s*)* %cb) #0 !dbg !459 {
entry:
  %retval = alloca i32, align 4
  %loop.addr = alloca %struct.uv_loop_s*, align 8
  %req.addr = alloca %struct.uv_fs_s*, align 8
  %path.addr = alloca i8*, align 8
  %cb.addr = alloca void (%struct.uv_fs_s*)*, align 8
  store %struct.uv_loop_s* %loop, %struct.uv_loop_s** %loop.addr, align 8
  call void @llvm.dbg.declare(metadata %struct.uv_loop_s** %loop.addr, metadata !2190, metadata !580), !dbg !2191
  store %struct.uv_fs_s* %req, %struct.uv_fs_s** %req.addr, align 8
  call void @llvm.dbg.declare(metadata %struct.uv_fs_s** %req.addr, metadata !2192, metadata !580), !dbg !2193
  store i8* %path, i8** %path.addr, align 8
  call void @llvm.dbg.declare(metadata i8** %path.addr, metadata !2194, metadata !580), !dbg !2195
  store void (%struct.uv_fs_s*)* %cb, void (%struct.uv_fs_s*)** %cb.addr, align 8
  call void @llvm.dbg.declare(metadata void (%struct.uv_fs_s*)** %cb.addr, metadata !2196, metadata !580), !dbg !2197
  br label %do.body, !dbg !2198

do.body:                                          ; preds = %entry
  %0 = load %struct.uv_fs_s*, %struct.uv_fs_s** %req.addr, align 8, !dbg !2199
  %type = getelementptr inbounds %struct.uv_fs_s, %struct.uv_fs_s* %0, i32 0, i32 1, !dbg !2199
  store i32 6, i32* %type, align 8, !dbg !2199
  %1 = load void (%struct.uv_fs_s*)*, void (%struct.uv_fs_s*)** %cb.addr, align 8, !dbg !2199
  %cmp = icmp ne void (%struct.uv_fs_s*)* %1, null, !dbg !2199
  br i1 %cmp, label %if.then, label %if.end, !dbg !2199

if.then:                                          ; preds = %do.body
  br label %do.body1, !dbg !2202

do.body1:                                         ; preds = %if.then
  br label %do.body2, !dbg !2205

do.body2:                                         ; preds = %do.body1
  %2 = load %struct.uv_fs_s*, %struct.uv_fs_s** %req.addr, align 8, !dbg !2208
  %type3 = getelementptr inbounds %struct.uv_fs_s, %struct.uv_fs_s* %2, i32 0, i32 1, !dbg !2208
  store i32 6, i32* %type3, align 8, !dbg !2208
  br label %do.end, !dbg !2208

do.end:                                           ; preds = %do.body2
  br label %do.body4, !dbg !2211

do.body4:                                         ; preds = %do.end
  br label %do.body5, !dbg !2213

do.body5:                                         ; preds = %do.body4
  %3 = load %struct.uv_loop_s*, %struct.uv_loop_s** %loop.addr, align 8, !dbg !2216
  %active_reqs = getelementptr inbounds %struct.uv_loop_s, %struct.uv_loop_s* %3, i32 0, i32 3, !dbg !2216
  %4 = load %struct.uv_fs_s*, %struct.uv_fs_s** %req.addr, align 8, !dbg !2216
  %active_queue = getelementptr inbounds %struct.uv_fs_s, %struct.uv_fs_s* %4, i32 0, i32 2, !dbg !2216
  %arrayidx = getelementptr inbounds [2 x i8*], [2 x i8*]* %active_queue, i64 0, i64 0, !dbg !2216
  %5 = bitcast i8** %arrayidx to [2 x i8*]**, !dbg !2216
  store [2 x i8*]* %active_reqs, [2 x i8*]** %5, align 8, !dbg !2216
  %6 = load %struct.uv_loop_s*, %struct.uv_loop_s** %loop.addr, align 8, !dbg !2216
  %active_reqs6 = getelementptr inbounds %struct.uv_loop_s, %struct.uv_loop_s* %6, i32 0, i32 3, !dbg !2216
  %arrayidx7 = getelementptr inbounds [2 x i8*], [2 x i8*]* %active_reqs6, i64 0, i64 1, !dbg !2216
  %7 = bitcast i8** %arrayidx7 to [2 x i8*]**, !dbg !2216
  %8 = load [2 x i8*]*, [2 x i8*]** %7, align 8, !dbg !2216
  %9 = load %struct.uv_fs_s*, %struct.uv_fs_s** %req.addr, align 8, !dbg !2216
  %active_queue8 = getelementptr inbounds %struct.uv_fs_s, %struct.uv_fs_s* %9, i32 0, i32 2, !dbg !2216
  %arrayidx9 = getelementptr inbounds [2 x i8*], [2 x i8*]* %active_queue8, i64 0, i64 1, !dbg !2216
  %10 = bitcast i8** %arrayidx9 to [2 x i8*]**, !dbg !2216
  store [2 x i8*]* %8, [2 x i8*]** %10, align 8, !dbg !2216
  %11 = load %struct.uv_fs_s*, %struct.uv_fs_s** %req.addr, align 8, !dbg !2216
  %active_queue10 = getelementptr inbounds %struct.uv_fs_s, %struct.uv_fs_s* %11, i32 0, i32 2, !dbg !2216
  %12 = load %struct.uv_fs_s*, %struct.uv_fs_s** %req.addr, align 8, !dbg !2216
  %active_queue11 = getelementptr inbounds %struct.uv_fs_s, %struct.uv_fs_s* %12, i32 0, i32 2, !dbg !2216
  %arrayidx12 = getelementptr inbounds [2 x i8*], [2 x i8*]* %active_queue11, i64 0, i64 1, !dbg !2216
  %13 = bitcast i8** %arrayidx12 to [2 x i8*]**, !dbg !2216
  %14 = load [2 x i8*]*, [2 x i8*]** %13, align 8, !dbg !2216
  %arrayidx13 = getelementptr inbounds [2 x i8*], [2 x i8*]* %14, i64 0, i64 0, !dbg !2216
  %15 = bitcast i8** %arrayidx13 to [2 x i8*]**, !dbg !2216
  store [2 x i8*]* %active_queue10, [2 x i8*]** %15, align 8, !dbg !2216
  %16 = load %struct.uv_fs_s*, %struct.uv_fs_s** %req.addr, align 8, !dbg !2216
  %active_queue14 = getelementptr inbounds %struct.uv_fs_s, %struct.uv_fs_s* %16, i32 0, i32 2, !dbg !2216
  %17 = load %struct.uv_loop_s*, %struct.uv_loop_s** %loop.addr, align 8, !dbg !2216
  %active_reqs15 = getelementptr inbounds %struct.uv_loop_s, %struct.uv_loop_s* %17, i32 0, i32 3, !dbg !2216
  %arrayidx16 = getelementptr inbounds [2 x i8*], [2 x i8*]* %active_reqs15, i64 0, i64 1, !dbg !2216
  %18 = bitcast i8** %arrayidx16 to [2 x i8*]**, !dbg !2216
  store [2 x i8*]* %active_queue14, [2 x i8*]** %18, align 8, !dbg !2216
  br label %do.end17, !dbg !2216

do.end17:                                         ; preds = %do.body5
  br label %do.end18, !dbg !2219

do.end18:                                         ; preds = %do.end17
  br label %do.end19, !dbg !2221

do.end19:                                         ; preds = %do.end18
  br label %if.end, !dbg !2223

if.end:                                           ; preds = %do.end19, %do.body
  %19 = load %struct.uv_fs_s*, %struct.uv_fs_s** %req.addr, align 8, !dbg !2225
  %fs_type = getelementptr inbounds %struct.uv_fs_s, %struct.uv_fs_s* %19, i32 0, i32 4, !dbg !2225
  store i32 25, i32* %fs_type, align 8, !dbg !2225
  %20 = load %struct.uv_fs_s*, %struct.uv_fs_s** %req.addr, align 8, !dbg !2225
  %result = getelementptr inbounds %struct.uv_fs_s, %struct.uv_fs_s* %20, i32 0, i32 7, !dbg !2225
  store i64 0, i64* %result, align 8, !dbg !2225
  %21 = load %struct.uv_fs_s*, %struct.uv_fs_s** %req.addr, align 8, !dbg !2225
  %ptr = getelementptr inbounds %struct.uv_fs_s, %struct.uv_fs_s* %21, i32 0, i32 8, !dbg !2225
  store i8* null, i8** %ptr, align 8, !dbg !2225
  %22 = load %struct.uv_loop_s*, %struct.uv_loop_s** %loop.addr, align 8, !dbg !2225
  %23 = load %struct.uv_fs_s*, %struct.uv_fs_s** %req.addr, align 8, !dbg !2225
  %loop20 = getelementptr inbounds %struct.uv_fs_s, %struct.uv_fs_s* %23, i32 0, i32 5, !dbg !2225
  store %struct.uv_loop_s* %22, %struct.uv_loop_s** %loop20, align 8, !dbg !2225
  %24 = load %struct.uv_fs_s*, %struct.uv_fs_s** %req.addr, align 8, !dbg !2225
  %path21 = getelementptr inbounds %struct.uv_fs_s, %struct.uv_fs_s* %24, i32 0, i32 9, !dbg !2225
  store i8* null, i8** %path21, align 8, !dbg !2225
  %25 = load %struct.uv_fs_s*, %struct.uv_fs_s** %req.addr, align 8, !dbg !2225
  %new_path = getelementptr inbounds %struct.uv_fs_s, %struct.uv_fs_s* %25, i32 0, i32 11, !dbg !2225
  store i8* null, i8** %new_path, align 8, !dbg !2225
  %26 = load void (%struct.uv_fs_s*)*, void (%struct.uv_fs_s*)** %cb.addr, align 8, !dbg !2225
  %27 = load %struct.uv_fs_s*, %struct.uv_fs_s** %req.addr, align 8, !dbg !2225
  %cb22 = getelementptr inbounds %struct.uv_fs_s, %struct.uv_fs_s* %27, i32 0, i32 6, !dbg !2225
  store void (%struct.uv_fs_s*)* %26, void (%struct.uv_fs_s*)** %cb22, align 8, !dbg !2225
  br label %do.end23, !dbg !2225

do.end23:                                         ; preds = %if.end
  br label %do.body24, !dbg !2227

do.body24:                                        ; preds = %do.end23
  %28 = load i8*, i8** %path.addr, align 8, !dbg !2228
  %cmp25 = icmp ne i8* %28, null, !dbg !2228
  br i1 %cmp25, label %cond.true, label %cond.false, !dbg !2228

cond.true:                                        ; preds = %do.body24
  br label %cond.end, !dbg !2231

cond.false:                                       ; preds = %do.body24
  call void @__assert_fail(i8* getelementptr inbounds ([19 x i8], [19 x i8]* @.str, i32 0, i32 0), i8* getelementptr inbounds ([66 x i8], [66 x i8]* @.str.1, i32 0, i32 0), i32 1240, i8* getelementptr inbounds ([67 x i8], [67 x i8]* @__PRETTY_FUNCTION__.uv_fs_readlink, i32 0, i32 0)) #8, !dbg !2233
  unreachable, !dbg !2233
                                                  ; No predecessors!
  br label %cond.end, !dbg !2235

cond.end:                                         ; preds = %29, %cond.true
  %30 = load void (%struct.uv_fs_s*)*, void (%struct.uv_fs_s*)** %cb.addr, align 8, !dbg !2237
  %cmp26 = icmp eq void (%struct.uv_fs_s*)* %30, null, !dbg !2237
  br i1 %cmp26, label %if.then27, label %if.else, !dbg !2237

if.then27:                                        ; preds = %cond.end
  %31 = load i8*, i8** %path.addr, align 8, !dbg !2240
  %32 = load %struct.uv_fs_s*, %struct.uv_fs_s** %req.addr, align 8, !dbg !2240
  %path28 = getelementptr inbounds %struct.uv_fs_s, %struct.uv_fs_s* %32, i32 0, i32 9, !dbg !2240
  store i8* %31, i8** %path28, align 8, !dbg !2240
  br label %if.end57, !dbg !2240

if.else:                                          ; preds = %cond.end
  %33 = load i8*, i8** %path.addr, align 8, !dbg !2243
  %call = call i8* @uv__strdup(i8* %33), !dbg !2243
  %34 = load %struct.uv_fs_s*, %struct.uv_fs_s** %req.addr, align 8, !dbg !2243
  %path29 = getelementptr inbounds %struct.uv_fs_s, %struct.uv_fs_s* %34, i32 0, i32 9, !dbg !2243
  store i8* %call, i8** %path29, align 8, !dbg !2243
  %35 = load %struct.uv_fs_s*, %struct.uv_fs_s** %req.addr, align 8, !dbg !2243
  %path30 = getelementptr inbounds %struct.uv_fs_s, %struct.uv_fs_s* %35, i32 0, i32 9, !dbg !2243
  %36 = load i8*, i8** %path30, align 8, !dbg !2243
  %cmp31 = icmp eq i8* %36, null, !dbg !2243
  br i1 %cmp31, label %if.then32, label %if.end56, !dbg !2243

if.then32:                                        ; preds = %if.else
  br label %do.body33, !dbg !2246

do.body33:                                        ; preds = %if.then32
  %37 = load %struct.uv_loop_s*, %struct.uv_loop_s** %loop.addr, align 8, !dbg !2250
  %active_reqs34 = getelementptr inbounds %struct.uv_loop_s, %struct.uv_loop_s* %37, i32 0, i32 3, !dbg !2250
  %38 = load %struct.uv_loop_s*, %struct.uv_loop_s** %loop.addr, align 8, !dbg !2250
  %active_reqs35 = getelementptr inbounds %struct.uv_loop_s, %struct.uv_loop_s* %38, i32 0, i32 3, !dbg !2250
  %arrayidx36 = getelementptr inbounds [2 x i8*], [2 x i8*]* %active_reqs35, i64 0, i64 0, !dbg !2250
  %39 = bitcast i8** %arrayidx36 to [2 x i8*]**, !dbg !2250
  %40 = load [2 x i8*]*, [2 x i8*]** %39, align 8, !dbg !2250
  %cmp37 = icmp eq [2 x i8*]* %active_reqs34, %40, !dbg !2250
  %conv = zext i1 %cmp37 to i32, !dbg !2250
  %cmp38 = icmp eq i32 %conv, 0, !dbg !2250
  br i1 %cmp38, label %cond.true40, label %cond.false41, !dbg !2250

cond.true40:                                      ; preds = %do.body33
  br label %cond.end42, !dbg !2253

cond.false41:                                     ; preds = %do.body33
  call void @__assert_fail(i8* getelementptr inbounds ([113 x i8], [113 x i8]* @.str.2, i32 0, i32 0), i8* getelementptr inbounds ([66 x i8], [66 x i8]* @.str.1, i32 0, i32 0), i32 1240, i8* getelementptr inbounds ([67 x i8], [67 x i8]* @__PRETTY_FUNCTION__.uv_fs_readlink, i32 0, i32 0)) #8, !dbg !2255
  unreachable, !dbg !2255
                                                  ; No predecessors!
  br label %cond.end42, !dbg !2257

cond.end42:                                       ; preds = %41, %cond.true40
  br label %do.body43, !dbg !2259

do.body43:                                        ; preds = %cond.end42
  %42 = load %struct.uv_fs_s*, %struct.uv_fs_s** %req.addr, align 8, !dbg !2261
  %active_queue44 = getelementptr inbounds %struct.uv_fs_s, %struct.uv_fs_s* %42, i32 0, i32 2, !dbg !2261
  %arrayidx45 = getelementptr inbounds [2 x i8*], [2 x i8*]* %active_queue44, i64 0, i64 0, !dbg !2261
  %43 = bitcast i8** %arrayidx45 to [2 x i8*]**, !dbg !2261
  %44 = load [2 x i8*]*, [2 x i8*]** %43, align 8, !dbg !2261
  %45 = load %struct.uv_fs_s*, %struct.uv_fs_s** %req.addr, align 8, !dbg !2261
  %active_queue46 = getelementptr inbounds %struct.uv_fs_s, %struct.uv_fs_s* %45, i32 0, i32 2, !dbg !2261
  %arrayidx47 = getelementptr inbounds [2 x i8*], [2 x i8*]* %active_queue46, i64 0, i64 1, !dbg !2261
  %46 = bitcast i8** %arrayidx47 to [2 x i8*]**, !dbg !2261
  %47 = load [2 x i8*]*, [2 x i8*]** %46, align 8, !dbg !2261
  %arrayidx48 = getelementptr inbounds [2 x i8*], [2 x i8*]* %47, i64 0, i64 0, !dbg !2261
  %48 = bitcast i8** %arrayidx48 to [2 x i8*]**, !dbg !2261
  store [2 x i8*]* %44, [2 x i8*]** %48, align 8, !dbg !2261
  %49 = load %struct.uv_fs_s*, %struct.uv_fs_s** %req.addr, align 8, !dbg !2261
  %active_queue49 = getelementptr inbounds %struct.uv_fs_s, %struct.uv_fs_s* %49, i32 0, i32 2, !dbg !2261
  %arrayidx50 = getelementptr inbounds [2 x i8*], [2 x i8*]* %active_queue49, i64 0, i64 1, !dbg !2261
  %50 = bitcast i8** %arrayidx50 to [2 x i8*]**, !dbg !2261
  %51 = load [2 x i8*]*, [2 x i8*]** %50, align 8, !dbg !2261
  %52 = load %struct.uv_fs_s*, %struct.uv_fs_s** %req.addr, align 8, !dbg !2261
  %active_queue51 = getelementptr inbounds %struct.uv_fs_s, %struct.uv_fs_s* %52, i32 0, i32 2, !dbg !2261
  %arrayidx52 = getelementptr inbounds [2 x i8*], [2 x i8*]* %active_queue51, i64 0, i64 0, !dbg !2261
  %53 = bitcast i8** %arrayidx52 to [2 x i8*]**, !dbg !2261
  %54 = load [2 x i8*]*, [2 x i8*]** %53, align 8, !dbg !2261
  %arrayidx53 = getelementptr inbounds [2 x i8*], [2 x i8*]* %54, i64 0, i64 1, !dbg !2261
  %55 = bitcast i8** %arrayidx53 to [2 x i8*]**, !dbg !2261
  store [2 x i8*]* %51, [2 x i8*]** %55, align 8, !dbg !2261
  br label %do.end54, !dbg !2261

do.end54:                                         ; preds = %do.body43
  br label %do.end55, !dbg !2264

do.end55:                                         ; preds = %do.end54
  store i32 -12, i32* %retval, align 4, !dbg !2266
  br label %do.end67, !dbg !2266

if.end56:                                         ; preds = %if.else
  br label %if.end57

if.end57:                                         ; preds = %if.end56, %if.then27
  br label %do.end58, !dbg !2268

do.end58:                                         ; preds = %if.end57
  br label %do.body59, !dbg !2270

do.body59:                                        ; preds = %do.end58
  %56 = load void (%struct.uv_fs_s*)*, void (%struct.uv_fs_s*)** %cb.addr, align 8, !dbg !2271
  %cmp60 = icmp ne void (%struct.uv_fs_s*)* %56, null, !dbg !2271
  br i1 %cmp60, label %if.then62, label %if.else63, !dbg !2271

if.then62:                                        ; preds = %do.body59
  %57 = load %struct.uv_loop_s*, %struct.uv_loop_s** %loop.addr, align 8, !dbg !2275
  %58 = load %struct.uv_fs_s*, %struct.uv_fs_s** %req.addr, align 8, !dbg !2275
  %work_req = getelementptr inbounds %struct.uv_fs_s, %struct.uv_fs_s* %58, i32 0, i32 22, !dbg !2275
  call void @uv__work_submit(%struct.uv_loop_s* %57, %struct.uv__work* %work_req, void (%struct.uv__work*)* @uv__fs_work, void (%struct.uv__work*, i32)* @uv__fs_done), !dbg !2275
  store i32 0, i32* %retval, align 4, !dbg !2275
  br label %do.end67, !dbg !2275

if.else63:                                        ; preds = %do.body59
  %59 = load %struct.uv_fs_s*, %struct.uv_fs_s** %req.addr, align 8, !dbg !2278
  %work_req64 = getelementptr inbounds %struct.uv_fs_s, %struct.uv_fs_s* %59, i32 0, i32 22, !dbg !2278
  call void @uv__fs_work(%struct.uv__work* %work_req64), !dbg !2278
  %60 = load %struct.uv_fs_s*, %struct.uv_fs_s** %req.addr, align 8, !dbg !2278
  %result65 = getelementptr inbounds %struct.uv_fs_s, %struct.uv_fs_s* %60, i32 0, i32 7, !dbg !2278
  %61 = load i64, i64* %result65, align 8, !dbg !2278
  %conv66 = trunc i64 %61 to i32, !dbg !2278
  store i32 %conv66, i32* %retval, align 4, !dbg !2278
  br label %do.end67, !dbg !2278

do.end67:                                         ; preds = %do.end55, %if.then62, %if.else63
  %62 = load i32, i32* %retval, align 4, !dbg !2281
  ret i32 %62, !dbg !2281
}

; Function Attrs: nounwind uwtable
define i32 @uv_fs_realpath(%struct.uv_loop_s* %loop, %struct.uv_fs_s* %req, i8* %path, void (%struct.uv_fs_s*)* %cb) #0 !dbg !460 {
entry:
  %retval = alloca i32, align 4
  %loop.addr = alloca %struct.uv_loop_s*, align 8
  %req.addr = alloca %struct.uv_fs_s*, align 8
  %path.addr = alloca i8*, align 8
  %cb.addr = alloca void (%struct.uv_fs_s*)*, align 8
  store %struct.uv_loop_s* %loop, %struct.uv_loop_s** %loop.addr, align 8
  call void @llvm.dbg.declare(metadata %struct.uv_loop_s** %loop.addr, metadata !2282, metadata !580), !dbg !2283
  store %struct.uv_fs_s* %req, %struct.uv_fs_s** %req.addr, align 8
  call void @llvm.dbg.declare(metadata %struct.uv_fs_s** %req.addr, metadata !2284, metadata !580), !dbg !2285
  store i8* %path, i8** %path.addr, align 8
  call void @llvm.dbg.declare(metadata i8** %path.addr, metadata !2286, metadata !580), !dbg !2287
  store void (%struct.uv_fs_s*)* %cb, void (%struct.uv_fs_s*)** %cb.addr, align 8
  call void @llvm.dbg.declare(metadata void (%struct.uv_fs_s*)** %cb.addr, metadata !2288, metadata !580), !dbg !2289
  br label %do.body, !dbg !2290

do.body:                                          ; preds = %entry
  %0 = load %struct.uv_fs_s*, %struct.uv_fs_s** %req.addr, align 8, !dbg !2291
  %type = getelementptr inbounds %struct.uv_fs_s, %struct.uv_fs_s* %0, i32 0, i32 1, !dbg !2291
  store i32 6, i32* %type, align 8, !dbg !2291
  %1 = load void (%struct.uv_fs_s*)*, void (%struct.uv_fs_s*)** %cb.addr, align 8, !dbg !2291
  %cmp = icmp ne void (%struct.uv_fs_s*)* %1, null, !dbg !2291
  br i1 %cmp, label %if.then, label %if.end, !dbg !2291

if.then:                                          ; preds = %do.body
  br label %do.body1, !dbg !2294

do.body1:                                         ; preds = %if.then
  br label %do.body2, !dbg !2297

do.body2:                                         ; preds = %do.body1
  %2 = load %struct.uv_fs_s*, %struct.uv_fs_s** %req.addr, align 8, !dbg !2300
  %type3 = getelementptr inbounds %struct.uv_fs_s, %struct.uv_fs_s* %2, i32 0, i32 1, !dbg !2300
  store i32 6, i32* %type3, align 8, !dbg !2300
  br label %do.end, !dbg !2300

do.end:                                           ; preds = %do.body2
  br label %do.body4, !dbg !2303

do.body4:                                         ; preds = %do.end
  br label %do.body5, !dbg !2305

do.body5:                                         ; preds = %do.body4
  %3 = load %struct.uv_loop_s*, %struct.uv_loop_s** %loop.addr, align 8, !dbg !2308
  %active_reqs = getelementptr inbounds %struct.uv_loop_s, %struct.uv_loop_s* %3, i32 0, i32 3, !dbg !2308
  %4 = load %struct.uv_fs_s*, %struct.uv_fs_s** %req.addr, align 8, !dbg !2308
  %active_queue = getelementptr inbounds %struct.uv_fs_s, %struct.uv_fs_s* %4, i32 0, i32 2, !dbg !2308
  %arrayidx = getelementptr inbounds [2 x i8*], [2 x i8*]* %active_queue, i64 0, i64 0, !dbg !2308
  %5 = bitcast i8** %arrayidx to [2 x i8*]**, !dbg !2308
  store [2 x i8*]* %active_reqs, [2 x i8*]** %5, align 8, !dbg !2308
  %6 = load %struct.uv_loop_s*, %struct.uv_loop_s** %loop.addr, align 8, !dbg !2308
  %active_reqs6 = getelementptr inbounds %struct.uv_loop_s, %struct.uv_loop_s* %6, i32 0, i32 3, !dbg !2308
  %arrayidx7 = getelementptr inbounds [2 x i8*], [2 x i8*]* %active_reqs6, i64 0, i64 1, !dbg !2308
  %7 = bitcast i8** %arrayidx7 to [2 x i8*]**, !dbg !2308
  %8 = load [2 x i8*]*, [2 x i8*]** %7, align 8, !dbg !2308
  %9 = load %struct.uv_fs_s*, %struct.uv_fs_s** %req.addr, align 8, !dbg !2308
  %active_queue8 = getelementptr inbounds %struct.uv_fs_s, %struct.uv_fs_s* %9, i32 0, i32 2, !dbg !2308
  %arrayidx9 = getelementptr inbounds [2 x i8*], [2 x i8*]* %active_queue8, i64 0, i64 1, !dbg !2308
  %10 = bitcast i8** %arrayidx9 to [2 x i8*]**, !dbg !2308
  store [2 x i8*]* %8, [2 x i8*]** %10, align 8, !dbg !2308
  %11 = load %struct.uv_fs_s*, %struct.uv_fs_s** %req.addr, align 8, !dbg !2308
  %active_queue10 = getelementptr inbounds %struct.uv_fs_s, %struct.uv_fs_s* %11, i32 0, i32 2, !dbg !2308
  %12 = load %struct.uv_fs_s*, %struct.uv_fs_s** %req.addr, align 8, !dbg !2308
  %active_queue11 = getelementptr inbounds %struct.uv_fs_s, %struct.uv_fs_s* %12, i32 0, i32 2, !dbg !2308
  %arrayidx12 = getelementptr inbounds [2 x i8*], [2 x i8*]* %active_queue11, i64 0, i64 1, !dbg !2308
  %13 = bitcast i8** %arrayidx12 to [2 x i8*]**, !dbg !2308
  %14 = load [2 x i8*]*, [2 x i8*]** %13, align 8, !dbg !2308
  %arrayidx13 = getelementptr inbounds [2 x i8*], [2 x i8*]* %14, i64 0, i64 0, !dbg !2308
  %15 = bitcast i8** %arrayidx13 to [2 x i8*]**, !dbg !2308
  store [2 x i8*]* %active_queue10, [2 x i8*]** %15, align 8, !dbg !2308
  %16 = load %struct.uv_fs_s*, %struct.uv_fs_s** %req.addr, align 8, !dbg !2308
  %active_queue14 = getelementptr inbounds %struct.uv_fs_s, %struct.uv_fs_s* %16, i32 0, i32 2, !dbg !2308
  %17 = load %struct.uv_loop_s*, %struct.uv_loop_s** %loop.addr, align 8, !dbg !2308
  %active_reqs15 = getelementptr inbounds %struct.uv_loop_s, %struct.uv_loop_s* %17, i32 0, i32 3, !dbg !2308
  %arrayidx16 = getelementptr inbounds [2 x i8*], [2 x i8*]* %active_reqs15, i64 0, i64 1, !dbg !2308
  %18 = bitcast i8** %arrayidx16 to [2 x i8*]**, !dbg !2308
  store [2 x i8*]* %active_queue14, [2 x i8*]** %18, align 8, !dbg !2308
  br label %do.end17, !dbg !2308

do.end17:                                         ; preds = %do.body5
  br label %do.end18, !dbg !2311

do.end18:                                         ; preds = %do.end17
  br label %do.end19, !dbg !2313

do.end19:                                         ; preds = %do.end18
  br label %if.end, !dbg !2315

if.end:                                           ; preds = %do.end19, %do.body
  %19 = load %struct.uv_fs_s*, %struct.uv_fs_s** %req.addr, align 8, !dbg !2317
  %fs_type = getelementptr inbounds %struct.uv_fs_s, %struct.uv_fs_s* %19, i32 0, i32 4, !dbg !2317
  store i32 28, i32* %fs_type, align 8, !dbg !2317
  %20 = load %struct.uv_fs_s*, %struct.uv_fs_s** %req.addr, align 8, !dbg !2317
  %result = getelementptr inbounds %struct.uv_fs_s, %struct.uv_fs_s* %20, i32 0, i32 7, !dbg !2317
  store i64 0, i64* %result, align 8, !dbg !2317
  %21 = load %struct.uv_fs_s*, %struct.uv_fs_s** %req.addr, align 8, !dbg !2317
  %ptr = getelementptr inbounds %struct.uv_fs_s, %struct.uv_fs_s* %21, i32 0, i32 8, !dbg !2317
  store i8* null, i8** %ptr, align 8, !dbg !2317
  %22 = load %struct.uv_loop_s*, %struct.uv_loop_s** %loop.addr, align 8, !dbg !2317
  %23 = load %struct.uv_fs_s*, %struct.uv_fs_s** %req.addr, align 8, !dbg !2317
  %loop20 = getelementptr inbounds %struct.uv_fs_s, %struct.uv_fs_s* %23, i32 0, i32 5, !dbg !2317
  store %struct.uv_loop_s* %22, %struct.uv_loop_s** %loop20, align 8, !dbg !2317
  %24 = load %struct.uv_fs_s*, %struct.uv_fs_s** %req.addr, align 8, !dbg !2317
  %path21 = getelementptr inbounds %struct.uv_fs_s, %struct.uv_fs_s* %24, i32 0, i32 9, !dbg !2317
  store i8* null, i8** %path21, align 8, !dbg !2317
  %25 = load %struct.uv_fs_s*, %struct.uv_fs_s** %req.addr, align 8, !dbg !2317
  %new_path = getelementptr inbounds %struct.uv_fs_s, %struct.uv_fs_s* %25, i32 0, i32 11, !dbg !2317
  store i8* null, i8** %new_path, align 8, !dbg !2317
  %26 = load void (%struct.uv_fs_s*)*, void (%struct.uv_fs_s*)** %cb.addr, align 8, !dbg !2317
  %27 = load %struct.uv_fs_s*, %struct.uv_fs_s** %req.addr, align 8, !dbg !2317
  %cb22 = getelementptr inbounds %struct.uv_fs_s, %struct.uv_fs_s* %27, i32 0, i32 6, !dbg !2317
  store void (%struct.uv_fs_s*)* %26, void (%struct.uv_fs_s*)** %cb22, align 8, !dbg !2317
  br label %do.end23, !dbg !2317

do.end23:                                         ; preds = %if.end
  br label %do.body24, !dbg !2319

do.body24:                                        ; preds = %do.end23
  %28 = load i8*, i8** %path.addr, align 8, !dbg !2320
  %cmp25 = icmp ne i8* %28, null, !dbg !2320
  br i1 %cmp25, label %cond.true, label %cond.false, !dbg !2320

cond.true:                                        ; preds = %do.body24
  br label %cond.end, !dbg !2323

cond.false:                                       ; preds = %do.body24
  call void @__assert_fail(i8* getelementptr inbounds ([19 x i8], [19 x i8]* @.str, i32 0, i32 0), i8* getelementptr inbounds ([66 x i8], [66 x i8]* @.str.1, i32 0, i32 0), i32 1250, i8* getelementptr inbounds ([67 x i8], [67 x i8]* @__PRETTY_FUNCTION__.uv_fs_realpath, i32 0, i32 0)) #8, !dbg !2325
  unreachable, !dbg !2325
                                                  ; No predecessors!
  br label %cond.end, !dbg !2327

cond.end:                                         ; preds = %29, %cond.true
  %30 = load void (%struct.uv_fs_s*)*, void (%struct.uv_fs_s*)** %cb.addr, align 8, !dbg !2329
  %cmp26 = icmp eq void (%struct.uv_fs_s*)* %30, null, !dbg !2329
  br i1 %cmp26, label %if.then27, label %if.else, !dbg !2329

if.then27:                                        ; preds = %cond.end
  %31 = load i8*, i8** %path.addr, align 8, !dbg !2332
  %32 = load %struct.uv_fs_s*, %struct.uv_fs_s** %req.addr, align 8, !dbg !2332
  %path28 = getelementptr inbounds %struct.uv_fs_s, %struct.uv_fs_s* %32, i32 0, i32 9, !dbg !2332
  store i8* %31, i8** %path28, align 8, !dbg !2332
  br label %if.end57, !dbg !2332

if.else:                                          ; preds = %cond.end
  %33 = load i8*, i8** %path.addr, align 8, !dbg !2335
  %call = call i8* @uv__strdup(i8* %33), !dbg !2335
  %34 = load %struct.uv_fs_s*, %struct.uv_fs_s** %req.addr, align 8, !dbg !2335
  %path29 = getelementptr inbounds %struct.uv_fs_s, %struct.uv_fs_s* %34, i32 0, i32 9, !dbg !2335
  store i8* %call, i8** %path29, align 8, !dbg !2335
  %35 = load %struct.uv_fs_s*, %struct.uv_fs_s** %req.addr, align 8, !dbg !2335
  %path30 = getelementptr inbounds %struct.uv_fs_s, %struct.uv_fs_s* %35, i32 0, i32 9, !dbg !2335
  %36 = load i8*, i8** %path30, align 8, !dbg !2335
  %cmp31 = icmp eq i8* %36, null, !dbg !2335
  br i1 %cmp31, label %if.then32, label %if.end56, !dbg !2335

if.then32:                                        ; preds = %if.else
  br label %do.body33, !dbg !2338

do.body33:                                        ; preds = %if.then32
  %37 = load %struct.uv_loop_s*, %struct.uv_loop_s** %loop.addr, align 8, !dbg !2342
  %active_reqs34 = getelementptr inbounds %struct.uv_loop_s, %struct.uv_loop_s* %37, i32 0, i32 3, !dbg !2342
  %38 = load %struct.uv_loop_s*, %struct.uv_loop_s** %loop.addr, align 8, !dbg !2342
  %active_reqs35 = getelementptr inbounds %struct.uv_loop_s, %struct.uv_loop_s* %38, i32 0, i32 3, !dbg !2342
  %arrayidx36 = getelementptr inbounds [2 x i8*], [2 x i8*]* %active_reqs35, i64 0, i64 0, !dbg !2342
  %39 = bitcast i8** %arrayidx36 to [2 x i8*]**, !dbg !2342
  %40 = load [2 x i8*]*, [2 x i8*]** %39, align 8, !dbg !2342
  %cmp37 = icmp eq [2 x i8*]* %active_reqs34, %40, !dbg !2342
  %conv = zext i1 %cmp37 to i32, !dbg !2342
  %cmp38 = icmp eq i32 %conv, 0, !dbg !2342
  br i1 %cmp38, label %cond.true40, label %cond.false41, !dbg !2342

cond.true40:                                      ; preds = %do.body33
  br label %cond.end42, !dbg !2345

cond.false41:                                     ; preds = %do.body33
  call void @__assert_fail(i8* getelementptr inbounds ([113 x i8], [113 x i8]* @.str.2, i32 0, i32 0), i8* getelementptr inbounds ([66 x i8], [66 x i8]* @.str.1, i32 0, i32 0), i32 1250, i8* getelementptr inbounds ([67 x i8], [67 x i8]* @__PRETTY_FUNCTION__.uv_fs_realpath, i32 0, i32 0)) #8, !dbg !2347
  unreachable, !dbg !2347
                                                  ; No predecessors!
  br label %cond.end42, !dbg !2349

cond.end42:                                       ; preds = %41, %cond.true40
  br label %do.body43, !dbg !2351

do.body43:                                        ; preds = %cond.end42
  %42 = load %struct.uv_fs_s*, %struct.uv_fs_s** %req.addr, align 8, !dbg !2353
  %active_queue44 = getelementptr inbounds %struct.uv_fs_s, %struct.uv_fs_s* %42, i32 0, i32 2, !dbg !2353
  %arrayidx45 = getelementptr inbounds [2 x i8*], [2 x i8*]* %active_queue44, i64 0, i64 0, !dbg !2353
  %43 = bitcast i8** %arrayidx45 to [2 x i8*]**, !dbg !2353
  %44 = load [2 x i8*]*, [2 x i8*]** %43, align 8, !dbg !2353
  %45 = load %struct.uv_fs_s*, %struct.uv_fs_s** %req.addr, align 8, !dbg !2353
  %active_queue46 = getelementptr inbounds %struct.uv_fs_s, %struct.uv_fs_s* %45, i32 0, i32 2, !dbg !2353
  %arrayidx47 = getelementptr inbounds [2 x i8*], [2 x i8*]* %active_queue46, i64 0, i64 1, !dbg !2353
  %46 = bitcast i8** %arrayidx47 to [2 x i8*]**, !dbg !2353
  %47 = load [2 x i8*]*, [2 x i8*]** %46, align 8, !dbg !2353
  %arrayidx48 = getelementptr inbounds [2 x i8*], [2 x i8*]* %47, i64 0, i64 0, !dbg !2353
  %48 = bitcast i8** %arrayidx48 to [2 x i8*]**, !dbg !2353
  store [2 x i8*]* %44, [2 x i8*]** %48, align 8, !dbg !2353
  %49 = load %struct.uv_fs_s*, %struct.uv_fs_s** %req.addr, align 8, !dbg !2353
  %active_queue49 = getelementptr inbounds %struct.uv_fs_s, %struct.uv_fs_s* %49, i32 0, i32 2, !dbg !2353
  %arrayidx50 = getelementptr inbounds [2 x i8*], [2 x i8*]* %active_queue49, i64 0, i64 1, !dbg !2353
  %50 = bitcast i8** %arrayidx50 to [2 x i8*]**, !dbg !2353
  %51 = load [2 x i8*]*, [2 x i8*]** %50, align 8, !dbg !2353
  %52 = load %struct.uv_fs_s*, %struct.uv_fs_s** %req.addr, align 8, !dbg !2353
  %active_queue51 = getelementptr inbounds %struct.uv_fs_s, %struct.uv_fs_s* %52, i32 0, i32 2, !dbg !2353
  %arrayidx52 = getelementptr inbounds [2 x i8*], [2 x i8*]* %active_queue51, i64 0, i64 0, !dbg !2353
  %53 = bitcast i8** %arrayidx52 to [2 x i8*]**, !dbg !2353
  %54 = load [2 x i8*]*, [2 x i8*]** %53, align 8, !dbg !2353
  %arrayidx53 = getelementptr inbounds [2 x i8*], [2 x i8*]* %54, i64 0, i64 1, !dbg !2353
  %55 = bitcast i8** %arrayidx53 to [2 x i8*]**, !dbg !2353
  store [2 x i8*]* %51, [2 x i8*]** %55, align 8, !dbg !2353
  br label %do.end54, !dbg !2353

do.end54:                                         ; preds = %do.body43
  br label %do.end55, !dbg !2356

do.end55:                                         ; preds = %do.end54
  store i32 -12, i32* %retval, align 4, !dbg !2358
  br label %do.end67, !dbg !2358

if.end56:                                         ; preds = %if.else
  br label %if.end57

if.end57:                                         ; preds = %if.end56, %if.then27
  br label %do.end58, !dbg !2360

do.end58:                                         ; preds = %if.end57
  br label %do.body59, !dbg !2362

do.body59:                                        ; preds = %do.end58
  %56 = load void (%struct.uv_fs_s*)*, void (%struct.uv_fs_s*)** %cb.addr, align 8, !dbg !2363
  %cmp60 = icmp ne void (%struct.uv_fs_s*)* %56, null, !dbg !2363
  br i1 %cmp60, label %if.then62, label %if.else63, !dbg !2363

if.then62:                                        ; preds = %do.body59
  %57 = load %struct.uv_loop_s*, %struct.uv_loop_s** %loop.addr, align 8, !dbg !2367
  %58 = load %struct.uv_fs_s*, %struct.uv_fs_s** %req.addr, align 8, !dbg !2367
  %work_req = getelementptr inbounds %struct.uv_fs_s, %struct.uv_fs_s* %58, i32 0, i32 22, !dbg !2367
  call void @uv__work_submit(%struct.uv_loop_s* %57, %struct.uv__work* %work_req, void (%struct.uv__work*)* @uv__fs_work, void (%struct.uv__work*, i32)* @uv__fs_done), !dbg !2367
  store i32 0, i32* %retval, align 4, !dbg !2367
  br label %do.end67, !dbg !2367

if.else63:                                        ; preds = %do.body59
  %59 = load %struct.uv_fs_s*, %struct.uv_fs_s** %req.addr, align 8, !dbg !2370
  %work_req64 = getelementptr inbounds %struct.uv_fs_s, %struct.uv_fs_s* %59, i32 0, i32 22, !dbg !2370
  call void @uv__fs_work(%struct.uv__work* %work_req64), !dbg !2370
  %60 = load %struct.uv_fs_s*, %struct.uv_fs_s** %req.addr, align 8, !dbg !2370
  %result65 = getelementptr inbounds %struct.uv_fs_s, %struct.uv_fs_s* %60, i32 0, i32 7, !dbg !2370
  %61 = load i64, i64* %result65, align 8, !dbg !2370
  %conv66 = trunc i64 %61 to i32, !dbg !2370
  store i32 %conv66, i32* %retval, align 4, !dbg !2370
  br label %do.end67, !dbg !2370

do.end67:                                         ; preds = %do.end55, %if.then62, %if.else63
  %62 = load i32, i32* %retval, align 4, !dbg !2373
  ret i32 %62, !dbg !2373
}

; Function Attrs: nounwind uwtable
define i32 @uv_fs_rename(%struct.uv_loop_s* %loop, %struct.uv_fs_s* %req, i8* %path, i8* %new_path, void (%struct.uv_fs_s*)* %cb) #0 !dbg !461 {
entry:
  %retval = alloca i32, align 4
  %loop.addr = alloca %struct.uv_loop_s*, align 8
  %req.addr = alloca %struct.uv_fs_s*, align 8
  %path.addr = alloca i8*, align 8
  %new_path.addr = alloca i8*, align 8
  %cb.addr = alloca void (%struct.uv_fs_s*)*, align 8
  %path_len = alloca i64, align 8
  %new_path_len = alloca i64, align 8
  store %struct.uv_loop_s* %loop, %struct.uv_loop_s** %loop.addr, align 8
  call void @llvm.dbg.declare(metadata %struct.uv_loop_s** %loop.addr, metadata !2374, metadata !580), !dbg !2375
  store %struct.uv_fs_s* %req, %struct.uv_fs_s** %req.addr, align 8
  call void @llvm.dbg.declare(metadata %struct.uv_fs_s** %req.addr, metadata !2376, metadata !580), !dbg !2377
  store i8* %path, i8** %path.addr, align 8
  call void @llvm.dbg.declare(metadata i8** %path.addr, metadata !2378, metadata !580), !dbg !2379
  store i8* %new_path, i8** %new_path.addr, align 8
  call void @llvm.dbg.declare(metadata i8** %new_path.addr, metadata !2380, metadata !580), !dbg !2381
  store void (%struct.uv_fs_s*)* %cb, void (%struct.uv_fs_s*)** %cb.addr, align 8
  call void @llvm.dbg.declare(metadata void (%struct.uv_fs_s*)** %cb.addr, metadata !2382, metadata !580), !dbg !2383
  br label %do.body, !dbg !2384

do.body:                                          ; preds = %entry
  %0 = load %struct.uv_fs_s*, %struct.uv_fs_s** %req.addr, align 8, !dbg !2385
  %type = getelementptr inbounds %struct.uv_fs_s, %struct.uv_fs_s* %0, i32 0, i32 1, !dbg !2385
  store i32 6, i32* %type, align 8, !dbg !2385
  %1 = load void (%struct.uv_fs_s*)*, void (%struct.uv_fs_s*)** %cb.addr, align 8, !dbg !2385
  %cmp = icmp ne void (%struct.uv_fs_s*)* %1, null, !dbg !2385
  br i1 %cmp, label %if.then, label %if.end, !dbg !2385

if.then:                                          ; preds = %do.body
  br label %do.body1, !dbg !2388

do.body1:                                         ; preds = %if.then
  br label %do.body2, !dbg !2391

do.body2:                                         ; preds = %do.body1
  %2 = load %struct.uv_fs_s*, %struct.uv_fs_s** %req.addr, align 8, !dbg !2394
  %type3 = getelementptr inbounds %struct.uv_fs_s, %struct.uv_fs_s* %2, i32 0, i32 1, !dbg !2394
  store i32 6, i32* %type3, align 8, !dbg !2394
  br label %do.end, !dbg !2394

do.end:                                           ; preds = %do.body2
  br label %do.body4, !dbg !2397

do.body4:                                         ; preds = %do.end
  br label %do.body5, !dbg !2399

do.body5:                                         ; preds = %do.body4
  %3 = load %struct.uv_loop_s*, %struct.uv_loop_s** %loop.addr, align 8, !dbg !2402
  %active_reqs = getelementptr inbounds %struct.uv_loop_s, %struct.uv_loop_s* %3, i32 0, i32 3, !dbg !2402
  %4 = load %struct.uv_fs_s*, %struct.uv_fs_s** %req.addr, align 8, !dbg !2402
  %active_queue = getelementptr inbounds %struct.uv_fs_s, %struct.uv_fs_s* %4, i32 0, i32 2, !dbg !2402
  %arrayidx = getelementptr inbounds [2 x i8*], [2 x i8*]* %active_queue, i64 0, i64 0, !dbg !2402
  %5 = bitcast i8** %arrayidx to [2 x i8*]**, !dbg !2402
  store [2 x i8*]* %active_reqs, [2 x i8*]** %5, align 8, !dbg !2402
  %6 = load %struct.uv_loop_s*, %struct.uv_loop_s** %loop.addr, align 8, !dbg !2402
  %active_reqs6 = getelementptr inbounds %struct.uv_loop_s, %struct.uv_loop_s* %6, i32 0, i32 3, !dbg !2402
  %arrayidx7 = getelementptr inbounds [2 x i8*], [2 x i8*]* %active_reqs6, i64 0, i64 1, !dbg !2402
  %7 = bitcast i8** %arrayidx7 to [2 x i8*]**, !dbg !2402
  %8 = load [2 x i8*]*, [2 x i8*]** %7, align 8, !dbg !2402
  %9 = load %struct.uv_fs_s*, %struct.uv_fs_s** %req.addr, align 8, !dbg !2402
  %active_queue8 = getelementptr inbounds %struct.uv_fs_s, %struct.uv_fs_s* %9, i32 0, i32 2, !dbg !2402
  %arrayidx9 = getelementptr inbounds [2 x i8*], [2 x i8*]* %active_queue8, i64 0, i64 1, !dbg !2402
  %10 = bitcast i8** %arrayidx9 to [2 x i8*]**, !dbg !2402
  store [2 x i8*]* %8, [2 x i8*]** %10, align 8, !dbg !2402
  %11 = load %struct.uv_fs_s*, %struct.uv_fs_s** %req.addr, align 8, !dbg !2402
  %active_queue10 = getelementptr inbounds %struct.uv_fs_s, %struct.uv_fs_s* %11, i32 0, i32 2, !dbg !2402
  %12 = load %struct.uv_fs_s*, %struct.uv_fs_s** %req.addr, align 8, !dbg !2402
  %active_queue11 = getelementptr inbounds %struct.uv_fs_s, %struct.uv_fs_s* %12, i32 0, i32 2, !dbg !2402
  %arrayidx12 = getelementptr inbounds [2 x i8*], [2 x i8*]* %active_queue11, i64 0, i64 1, !dbg !2402
  %13 = bitcast i8** %arrayidx12 to [2 x i8*]**, !dbg !2402
  %14 = load [2 x i8*]*, [2 x i8*]** %13, align 8, !dbg !2402
  %arrayidx13 = getelementptr inbounds [2 x i8*], [2 x i8*]* %14, i64 0, i64 0, !dbg !2402
  %15 = bitcast i8** %arrayidx13 to [2 x i8*]**, !dbg !2402
  store [2 x i8*]* %active_queue10, [2 x i8*]** %15, align 8, !dbg !2402
  %16 = load %struct.uv_fs_s*, %struct.uv_fs_s** %req.addr, align 8, !dbg !2402
  %active_queue14 = getelementptr inbounds %struct.uv_fs_s, %struct.uv_fs_s* %16, i32 0, i32 2, !dbg !2402
  %17 = load %struct.uv_loop_s*, %struct.uv_loop_s** %loop.addr, align 8, !dbg !2402
  %active_reqs15 = getelementptr inbounds %struct.uv_loop_s, %struct.uv_loop_s* %17, i32 0, i32 3, !dbg !2402
  %arrayidx16 = getelementptr inbounds [2 x i8*], [2 x i8*]* %active_reqs15, i64 0, i64 1, !dbg !2402
  %18 = bitcast i8** %arrayidx16 to [2 x i8*]**, !dbg !2402
  store [2 x i8*]* %active_queue14, [2 x i8*]** %18, align 8, !dbg !2402
  br label %do.end17, !dbg !2402

do.end17:                                         ; preds = %do.body5
  br label %do.end18, !dbg !2405

do.end18:                                         ; preds = %do.end17
  br label %do.end19, !dbg !2407

do.end19:                                         ; preds = %do.end18
  br label %if.end, !dbg !2409

if.end:                                           ; preds = %do.end19, %do.body
  %19 = load %struct.uv_fs_s*, %struct.uv_fs_s** %req.addr, align 8, !dbg !2411
  %fs_type = getelementptr inbounds %struct.uv_fs_s, %struct.uv_fs_s* %19, i32 0, i32 4, !dbg !2411
  store i32 21, i32* %fs_type, align 8, !dbg !2411
  %20 = load %struct.uv_fs_s*, %struct.uv_fs_s** %req.addr, align 8, !dbg !2411
  %result = getelementptr inbounds %struct.uv_fs_s, %struct.uv_fs_s* %20, i32 0, i32 7, !dbg !2411
  store i64 0, i64* %result, align 8, !dbg !2411
  %21 = load %struct.uv_fs_s*, %struct.uv_fs_s** %req.addr, align 8, !dbg !2411
  %ptr = getelementptr inbounds %struct.uv_fs_s, %struct.uv_fs_s* %21, i32 0, i32 8, !dbg !2411
  store i8* null, i8** %ptr, align 8, !dbg !2411
  %22 = load %struct.uv_loop_s*, %struct.uv_loop_s** %loop.addr, align 8, !dbg !2411
  %23 = load %struct.uv_fs_s*, %struct.uv_fs_s** %req.addr, align 8, !dbg !2411
  %loop20 = getelementptr inbounds %struct.uv_fs_s, %struct.uv_fs_s* %23, i32 0, i32 5, !dbg !2411
  store %struct.uv_loop_s* %22, %struct.uv_loop_s** %loop20, align 8, !dbg !2411
  %24 = load %struct.uv_fs_s*, %struct.uv_fs_s** %req.addr, align 8, !dbg !2411
  %path21 = getelementptr inbounds %struct.uv_fs_s, %struct.uv_fs_s* %24, i32 0, i32 9, !dbg !2411
  store i8* null, i8** %path21, align 8, !dbg !2411
  %25 = load %struct.uv_fs_s*, %struct.uv_fs_s** %req.addr, align 8, !dbg !2411
  %new_path22 = getelementptr inbounds %struct.uv_fs_s, %struct.uv_fs_s* %25, i32 0, i32 11, !dbg !2411
  store i8* null, i8** %new_path22, align 8, !dbg !2411
  %26 = load void (%struct.uv_fs_s*)*, void (%struct.uv_fs_s*)** %cb.addr, align 8, !dbg !2411
  %27 = load %struct.uv_fs_s*, %struct.uv_fs_s** %req.addr, align 8, !dbg !2411
  %cb23 = getelementptr inbounds %struct.uv_fs_s, %struct.uv_fs_s* %27, i32 0, i32 6, !dbg !2411
  store void (%struct.uv_fs_s*)* %26, void (%struct.uv_fs_s*)** %cb23, align 8, !dbg !2411
  br label %do.end24, !dbg !2411

do.end24:                                         ; preds = %if.end
  br label %do.body25, !dbg !2413

do.body25:                                        ; preds = %do.end24
  %28 = load void (%struct.uv_fs_s*)*, void (%struct.uv_fs_s*)** %cb.addr, align 8, !dbg !2414
  %cmp26 = icmp eq void (%struct.uv_fs_s*)* %28, null, !dbg !2414
  br i1 %cmp26, label %if.then27, label %if.else, !dbg !2414

if.then27:                                        ; preds = %do.body25
  %29 = load i8*, i8** %path.addr, align 8, !dbg !2418
  %30 = load %struct.uv_fs_s*, %struct.uv_fs_s** %req.addr, align 8, !dbg !2418
  %path28 = getelementptr inbounds %struct.uv_fs_s, %struct.uv_fs_s* %30, i32 0, i32 9, !dbg !2418
  store i8* %29, i8** %path28, align 8, !dbg !2418
  %31 = load i8*, i8** %new_path.addr, align 8, !dbg !2418
  %32 = load %struct.uv_fs_s*, %struct.uv_fs_s** %req.addr, align 8, !dbg !2418
  %new_path29 = getelementptr inbounds %struct.uv_fs_s, %struct.uv_fs_s* %32, i32 0, i32 11, !dbg !2418
  store i8* %31, i8** %new_path29, align 8, !dbg !2418
  br label %if.end63, !dbg !2418

if.else:                                          ; preds = %do.body25
  call void @llvm.dbg.declare(metadata i64* %path_len, metadata !2421, metadata !580), !dbg !2423
  call void @llvm.dbg.declare(metadata i64* %new_path_len, metadata !2424, metadata !580), !dbg !2423
  %33 = load i8*, i8** %path.addr, align 8, !dbg !2425
  %call = call i64 @strlen(i8* %33) #10, !dbg !2425
  %add = add i64 %call, 1, !dbg !2425
  store i64 %add, i64* %path_len, align 8, !dbg !2425
  %34 = load i8*, i8** %new_path.addr, align 8, !dbg !2425
  %call30 = call i64 @strlen(i8* %34) #10, !dbg !2427
  %add31 = add i64 %call30, 1, !dbg !2425
  store i64 %add31, i64* %new_path_len, align 8, !dbg !2425
  %35 = load i64, i64* %path_len, align 8, !dbg !2425
  %36 = load i64, i64* %new_path_len, align 8, !dbg !2425
  %add32 = add i64 %35, %36, !dbg !2425
  %call33 = call i8* @uv__malloc(i64 %add32), !dbg !2429
  %37 = load %struct.uv_fs_s*, %struct.uv_fs_s** %req.addr, align 8, !dbg !2425
  %path34 = getelementptr inbounds %struct.uv_fs_s, %struct.uv_fs_s* %37, i32 0, i32 9, !dbg !2425
  store i8* %call33, i8** %path34, align 8, !dbg !2425
  %38 = load %struct.uv_fs_s*, %struct.uv_fs_s** %req.addr, align 8, !dbg !2425
  %path35 = getelementptr inbounds %struct.uv_fs_s, %struct.uv_fs_s* %38, i32 0, i32 9, !dbg !2425
  %39 = load i8*, i8** %path35, align 8, !dbg !2425
  %cmp36 = icmp eq i8* %39, null, !dbg !2425
  br i1 %cmp36, label %if.then37, label %if.end58, !dbg !2425

if.then37:                                        ; preds = %if.else
  br label %do.body38, !dbg !2431

do.body38:                                        ; preds = %if.then37
  %40 = load %struct.uv_loop_s*, %struct.uv_loop_s** %loop.addr, align 8, !dbg !2435
  %active_reqs39 = getelementptr inbounds %struct.uv_loop_s, %struct.uv_loop_s* %40, i32 0, i32 3, !dbg !2435
  %41 = load %struct.uv_loop_s*, %struct.uv_loop_s** %loop.addr, align 8, !dbg !2435
  %active_reqs40 = getelementptr inbounds %struct.uv_loop_s, %struct.uv_loop_s* %41, i32 0, i32 3, !dbg !2435
  %arrayidx41 = getelementptr inbounds [2 x i8*], [2 x i8*]* %active_reqs40, i64 0, i64 0, !dbg !2435
  %42 = bitcast i8** %arrayidx41 to [2 x i8*]**, !dbg !2435
  %43 = load [2 x i8*]*, [2 x i8*]** %42, align 8, !dbg !2435
  %cmp42 = icmp eq [2 x i8*]* %active_reqs39, %43, !dbg !2435
  %conv = zext i1 %cmp42 to i32, !dbg !2435
  %cmp43 = icmp eq i32 %conv, 0, !dbg !2435
  br i1 %cmp43, label %cond.true, label %cond.false, !dbg !2435

cond.true:                                        ; preds = %do.body38
  br label %cond.end, !dbg !2438

cond.false:                                       ; preds = %do.body38
  call void @__assert_fail(i8* getelementptr inbounds ([113 x i8], [113 x i8]* @.str.2, i32 0, i32 0), i8* getelementptr inbounds ([66 x i8], [66 x i8]* @.str.1, i32 0, i32 0), i32 1261, i8* getelementptr inbounds ([79 x i8], [79 x i8]* @__PRETTY_FUNCTION__.uv_fs_rename, i32 0, i32 0)) #8, !dbg !2440
  unreachable, !dbg !2440
                                                  ; No predecessors!
  br label %cond.end, !dbg !2442

cond.end:                                         ; preds = %44, %cond.true
  br label %do.body45, !dbg !2444

do.body45:                                        ; preds = %cond.end
  %45 = load %struct.uv_fs_s*, %struct.uv_fs_s** %req.addr, align 8, !dbg !2446
  %active_queue46 = getelementptr inbounds %struct.uv_fs_s, %struct.uv_fs_s* %45, i32 0, i32 2, !dbg !2446
  %arrayidx47 = getelementptr inbounds [2 x i8*], [2 x i8*]* %active_queue46, i64 0, i64 0, !dbg !2446
  %46 = bitcast i8** %arrayidx47 to [2 x i8*]**, !dbg !2446
  %47 = load [2 x i8*]*, [2 x i8*]** %46, align 8, !dbg !2446
  %48 = load %struct.uv_fs_s*, %struct.uv_fs_s** %req.addr, align 8, !dbg !2446
  %active_queue48 = getelementptr inbounds %struct.uv_fs_s, %struct.uv_fs_s* %48, i32 0, i32 2, !dbg !2446
  %arrayidx49 = getelementptr inbounds [2 x i8*], [2 x i8*]* %active_queue48, i64 0, i64 1, !dbg !2446
  %49 = bitcast i8** %arrayidx49 to [2 x i8*]**, !dbg !2446
  %50 = load [2 x i8*]*, [2 x i8*]** %49, align 8, !dbg !2446
  %arrayidx50 = getelementptr inbounds [2 x i8*], [2 x i8*]* %50, i64 0, i64 0, !dbg !2446
  %51 = bitcast i8** %arrayidx50 to [2 x i8*]**, !dbg !2446
  store [2 x i8*]* %47, [2 x i8*]** %51, align 8, !dbg !2446
  %52 = load %struct.uv_fs_s*, %struct.uv_fs_s** %req.addr, align 8, !dbg !2446
  %active_queue51 = getelementptr inbounds %struct.uv_fs_s, %struct.uv_fs_s* %52, i32 0, i32 2, !dbg !2446
  %arrayidx52 = getelementptr inbounds [2 x i8*], [2 x i8*]* %active_queue51, i64 0, i64 1, !dbg !2446
  %53 = bitcast i8** %arrayidx52 to [2 x i8*]**, !dbg !2446
  %54 = load [2 x i8*]*, [2 x i8*]** %53, align 8, !dbg !2446
  %55 = load %struct.uv_fs_s*, %struct.uv_fs_s** %req.addr, align 8, !dbg !2446
  %active_queue53 = getelementptr inbounds %struct.uv_fs_s, %struct.uv_fs_s* %55, i32 0, i32 2, !dbg !2446
  %arrayidx54 = getelementptr inbounds [2 x i8*], [2 x i8*]* %active_queue53, i64 0, i64 0, !dbg !2446
  %56 = bitcast i8** %arrayidx54 to [2 x i8*]**, !dbg !2446
  %57 = load [2 x i8*]*, [2 x i8*]** %56, align 8, !dbg !2446
  %arrayidx55 = getelementptr inbounds [2 x i8*], [2 x i8*]* %57, i64 0, i64 1, !dbg !2446
  %58 = bitcast i8** %arrayidx55 to [2 x i8*]**, !dbg !2446
  store [2 x i8*]* %54, [2 x i8*]** %58, align 8, !dbg !2446
  br label %do.end56, !dbg !2446

do.end56:                                         ; preds = %do.body45
  br label %do.end57, !dbg !2449

do.end57:                                         ; preds = %do.end56
  store i32 -12, i32* %retval, align 4, !dbg !2451
  br label %do.end73, !dbg !2451

if.end58:                                         ; preds = %if.else
  %59 = load %struct.uv_fs_s*, %struct.uv_fs_s** %req.addr, align 8, !dbg !2453
  %path59 = getelementptr inbounds %struct.uv_fs_s, %struct.uv_fs_s* %59, i32 0, i32 9, !dbg !2453
  %60 = load i8*, i8** %path59, align 8, !dbg !2453
  %61 = load i64, i64* %path_len, align 8, !dbg !2453
  %add.ptr = getelementptr inbounds i8, i8* %60, i64 %61, !dbg !2453
  %62 = load %struct.uv_fs_s*, %struct.uv_fs_s** %req.addr, align 8, !dbg !2453
  %new_path60 = getelementptr inbounds %struct.uv_fs_s, %struct.uv_fs_s* %62, i32 0, i32 11, !dbg !2453
  store i8* %add.ptr, i8** %new_path60, align 8, !dbg !2453
  %63 = load %struct.uv_fs_s*, %struct.uv_fs_s** %req.addr, align 8, !dbg !2453
  %path61 = getelementptr inbounds %struct.uv_fs_s, %struct.uv_fs_s* %63, i32 0, i32 9, !dbg !2453
  %64 = load i8*, i8** %path61, align 8, !dbg !2453
  %65 = load i8*, i8** %path.addr, align 8, !dbg !2453
  %66 = load i64, i64* %path_len, align 8, !dbg !2453
  call void @llvm.memcpy.p0i8.p0i8.i64(i8* %64, i8* %65, i64 %66, i32 1, i1 false), !dbg !2453
  %67 = load %struct.uv_fs_s*, %struct.uv_fs_s** %req.addr, align 8, !dbg !2453
  %new_path62 = getelementptr inbounds %struct.uv_fs_s, %struct.uv_fs_s* %67, i32 0, i32 11, !dbg !2453
  %68 = load i8*, i8** %new_path62, align 8, !dbg !2453
  %69 = load i8*, i8** %new_path.addr, align 8, !dbg !2453
  %70 = load i64, i64* %new_path_len, align 8, !dbg !2453
  call void @llvm.memcpy.p0i8.p0i8.i64(i8* %68, i8* %69, i64 %70, i32 1, i1 false), !dbg !2455
  br label %if.end63

if.end63:                                         ; preds = %if.end58, %if.then27
  br label %do.end64, !dbg !2457

do.end64:                                         ; preds = %if.end63
  br label %do.body65, !dbg !2459

do.body65:                                        ; preds = %do.end64
  %71 = load void (%struct.uv_fs_s*)*, void (%struct.uv_fs_s*)** %cb.addr, align 8, !dbg !2460
  %cmp66 = icmp ne void (%struct.uv_fs_s*)* %71, null, !dbg !2460
  br i1 %cmp66, label %if.then68, label %if.else69, !dbg !2460

if.then68:                                        ; preds = %do.body65
  %72 = load %struct.uv_loop_s*, %struct.uv_loop_s** %loop.addr, align 8, !dbg !2464
  %73 = load %struct.uv_fs_s*, %struct.uv_fs_s** %req.addr, align 8, !dbg !2464
  %work_req = getelementptr inbounds %struct.uv_fs_s, %struct.uv_fs_s* %73, i32 0, i32 22, !dbg !2464
  call void @uv__work_submit(%struct.uv_loop_s* %72, %struct.uv__work* %work_req, void (%struct.uv__work*)* @uv__fs_work, void (%struct.uv__work*, i32)* @uv__fs_done), !dbg !2464
  store i32 0, i32* %retval, align 4, !dbg !2464
  br label %do.end73, !dbg !2464

if.else69:                                        ; preds = %do.body65
  %74 = load %struct.uv_fs_s*, %struct.uv_fs_s** %req.addr, align 8, !dbg !2467
  %work_req70 = getelementptr inbounds %struct.uv_fs_s, %struct.uv_fs_s* %74, i32 0, i32 22, !dbg !2467
  call void @uv__fs_work(%struct.uv__work* %work_req70), !dbg !2467
  %75 = load %struct.uv_fs_s*, %struct.uv_fs_s** %req.addr, align 8, !dbg !2467
  %result71 = getelementptr inbounds %struct.uv_fs_s, %struct.uv_fs_s* %75, i32 0, i32 7, !dbg !2467
  %76 = load i64, i64* %result71, align 8, !dbg !2467
  %conv72 = trunc i64 %76 to i32, !dbg !2467
  store i32 %conv72, i32* %retval, align 4, !dbg !2467
  br label %do.end73, !dbg !2467

do.end73:                                         ; preds = %do.end57, %if.then68, %if.else69
  %77 = load i32, i32* %retval, align 4, !dbg !2470
  ret i32 %77, !dbg !2470
}

; Function Attrs: nounwind uwtable
define i32 @uv_fs_rmdir(%struct.uv_loop_s* %loop, %struct.uv_fs_s* %req, i8* %path, void (%struct.uv_fs_s*)* %cb) #0 !dbg !462 {
entry:
  %retval = alloca i32, align 4
  %loop.addr = alloca %struct.uv_loop_s*, align 8
  %req.addr = alloca %struct.uv_fs_s*, align 8
  %path.addr = alloca i8*, align 8
  %cb.addr = alloca void (%struct.uv_fs_s*)*, align 8
  store %struct.uv_loop_s* %loop, %struct.uv_loop_s** %loop.addr, align 8
  call void @llvm.dbg.declare(metadata %struct.uv_loop_s** %loop.addr, metadata !2471, metadata !580), !dbg !2472
  store %struct.uv_fs_s* %req, %struct.uv_fs_s** %req.addr, align 8
  call void @llvm.dbg.declare(metadata %struct.uv_fs_s** %req.addr, metadata !2473, metadata !580), !dbg !2474
  store i8* %path, i8** %path.addr, align 8
  call void @llvm.dbg.declare(metadata i8** %path.addr, metadata !2475, metadata !580), !dbg !2476
  store void (%struct.uv_fs_s*)* %cb, void (%struct.uv_fs_s*)** %cb.addr, align 8
  call void @llvm.dbg.declare(metadata void (%struct.uv_fs_s*)** %cb.addr, metadata !2477, metadata !580), !dbg !2478
  br label %do.body, !dbg !2479

do.body:                                          ; preds = %entry
  %0 = load %struct.uv_fs_s*, %struct.uv_fs_s** %req.addr, align 8, !dbg !2480
  %type = getelementptr inbounds %struct.uv_fs_s, %struct.uv_fs_s* %0, i32 0, i32 1, !dbg !2480
  store i32 6, i32* %type, align 8, !dbg !2480
  %1 = load void (%struct.uv_fs_s*)*, void (%struct.uv_fs_s*)** %cb.addr, align 8, !dbg !2480
  %cmp = icmp ne void (%struct.uv_fs_s*)* %1, null, !dbg !2480
  br i1 %cmp, label %if.then, label %if.end, !dbg !2480

if.then:                                          ; preds = %do.body
  br label %do.body1, !dbg !2483

do.body1:                                         ; preds = %if.then
  br label %do.body2, !dbg !2486

do.body2:                                         ; preds = %do.body1
  %2 = load %struct.uv_fs_s*, %struct.uv_fs_s** %req.addr, align 8, !dbg !2489
  %type3 = getelementptr inbounds %struct.uv_fs_s, %struct.uv_fs_s* %2, i32 0, i32 1, !dbg !2489
  store i32 6, i32* %type3, align 8, !dbg !2489
  br label %do.end, !dbg !2489

do.end:                                           ; preds = %do.body2
  br label %do.body4, !dbg !2492

do.body4:                                         ; preds = %do.end
  br label %do.body5, !dbg !2494

do.body5:                                         ; preds = %do.body4
  %3 = load %struct.uv_loop_s*, %struct.uv_loop_s** %loop.addr, align 8, !dbg !2497
  %active_reqs = getelementptr inbounds %struct.uv_loop_s, %struct.uv_loop_s* %3, i32 0, i32 3, !dbg !2497
  %4 = load %struct.uv_fs_s*, %struct.uv_fs_s** %req.addr, align 8, !dbg !2497
  %active_queue = getelementptr inbounds %struct.uv_fs_s, %struct.uv_fs_s* %4, i32 0, i32 2, !dbg !2497
  %arrayidx = getelementptr inbounds [2 x i8*], [2 x i8*]* %active_queue, i64 0, i64 0, !dbg !2497
  %5 = bitcast i8** %arrayidx to [2 x i8*]**, !dbg !2497
  store [2 x i8*]* %active_reqs, [2 x i8*]** %5, align 8, !dbg !2497
  %6 = load %struct.uv_loop_s*, %struct.uv_loop_s** %loop.addr, align 8, !dbg !2497
  %active_reqs6 = getelementptr inbounds %struct.uv_loop_s, %struct.uv_loop_s* %6, i32 0, i32 3, !dbg !2497
  %arrayidx7 = getelementptr inbounds [2 x i8*], [2 x i8*]* %active_reqs6, i64 0, i64 1, !dbg !2497
  %7 = bitcast i8** %arrayidx7 to [2 x i8*]**, !dbg !2497
  %8 = load [2 x i8*]*, [2 x i8*]** %7, align 8, !dbg !2497
  %9 = load %struct.uv_fs_s*, %struct.uv_fs_s** %req.addr, align 8, !dbg !2497
  %active_queue8 = getelementptr inbounds %struct.uv_fs_s, %struct.uv_fs_s* %9, i32 0, i32 2, !dbg !2497
  %arrayidx9 = getelementptr inbounds [2 x i8*], [2 x i8*]* %active_queue8, i64 0, i64 1, !dbg !2497
  %10 = bitcast i8** %arrayidx9 to [2 x i8*]**, !dbg !2497
  store [2 x i8*]* %8, [2 x i8*]** %10, align 8, !dbg !2497
  %11 = load %struct.uv_fs_s*, %struct.uv_fs_s** %req.addr, align 8, !dbg !2497
  %active_queue10 = getelementptr inbounds %struct.uv_fs_s, %struct.uv_fs_s* %11, i32 0, i32 2, !dbg !2497
  %12 = load %struct.uv_fs_s*, %struct.uv_fs_s** %req.addr, align 8, !dbg !2497
  %active_queue11 = getelementptr inbounds %struct.uv_fs_s, %struct.uv_fs_s* %12, i32 0, i32 2, !dbg !2497
  %arrayidx12 = getelementptr inbounds [2 x i8*], [2 x i8*]* %active_queue11, i64 0, i64 1, !dbg !2497
  %13 = bitcast i8** %arrayidx12 to [2 x i8*]**, !dbg !2497
  %14 = load [2 x i8*]*, [2 x i8*]** %13, align 8, !dbg !2497
  %arrayidx13 = getelementptr inbounds [2 x i8*], [2 x i8*]* %14, i64 0, i64 0, !dbg !2497
  %15 = bitcast i8** %arrayidx13 to [2 x i8*]**, !dbg !2497
  store [2 x i8*]* %active_queue10, [2 x i8*]** %15, align 8, !dbg !2497
  %16 = load %struct.uv_fs_s*, %struct.uv_fs_s** %req.addr, align 8, !dbg !2497
  %active_queue14 = getelementptr inbounds %struct.uv_fs_s, %struct.uv_fs_s* %16, i32 0, i32 2, !dbg !2497
  %17 = load %struct.uv_loop_s*, %struct.uv_loop_s** %loop.addr, align 8, !dbg !2497
  %active_reqs15 = getelementptr inbounds %struct.uv_loop_s, %struct.uv_loop_s* %17, i32 0, i32 3, !dbg !2497
  %arrayidx16 = getelementptr inbounds [2 x i8*], [2 x i8*]* %active_reqs15, i64 0, i64 1, !dbg !2497
  %18 = bitcast i8** %arrayidx16 to [2 x i8*]**, !dbg !2497
  store [2 x i8*]* %active_queue14, [2 x i8*]** %18, align 8, !dbg !2497
  br label %do.end17, !dbg !2497

do.end17:                                         ; preds = %do.body5
  br label %do.end18, !dbg !2500

do.end18:                                         ; preds = %do.end17
  br label %do.end19, !dbg !2502

do.end19:                                         ; preds = %do.end18
  br label %if.end, !dbg !2504

if.end:                                           ; preds = %do.end19, %do.body
  %19 = load %struct.uv_fs_s*, %struct.uv_fs_s** %req.addr, align 8, !dbg !2506
  %fs_type = getelementptr inbounds %struct.uv_fs_s, %struct.uv_fs_s* %19, i32 0, i32 4, !dbg !2506
  store i32 18, i32* %fs_type, align 8, !dbg !2506
  %20 = load %struct.uv_fs_s*, %struct.uv_fs_s** %req.addr, align 8, !dbg !2506
  %result = getelementptr inbounds %struct.uv_fs_s, %struct.uv_fs_s* %20, i32 0, i32 7, !dbg !2506
  store i64 0, i64* %result, align 8, !dbg !2506
  %21 = load %struct.uv_fs_s*, %struct.uv_fs_s** %req.addr, align 8, !dbg !2506
  %ptr = getelementptr inbounds %struct.uv_fs_s, %struct.uv_fs_s* %21, i32 0, i32 8, !dbg !2506
  store i8* null, i8** %ptr, align 8, !dbg !2506
  %22 = load %struct.uv_loop_s*, %struct.uv_loop_s** %loop.addr, align 8, !dbg !2506
  %23 = load %struct.uv_fs_s*, %struct.uv_fs_s** %req.addr, align 8, !dbg !2506
  %loop20 = getelementptr inbounds %struct.uv_fs_s, %struct.uv_fs_s* %23, i32 0, i32 5, !dbg !2506
  store %struct.uv_loop_s* %22, %struct.uv_loop_s** %loop20, align 8, !dbg !2506
  %24 = load %struct.uv_fs_s*, %struct.uv_fs_s** %req.addr, align 8, !dbg !2506
  %path21 = getelementptr inbounds %struct.uv_fs_s, %struct.uv_fs_s* %24, i32 0, i32 9, !dbg !2506
  store i8* null, i8** %path21, align 8, !dbg !2506
  %25 = load %struct.uv_fs_s*, %struct.uv_fs_s** %req.addr, align 8, !dbg !2506
  %new_path = getelementptr inbounds %struct.uv_fs_s, %struct.uv_fs_s* %25, i32 0, i32 11, !dbg !2506
  store i8* null, i8** %new_path, align 8, !dbg !2506
  %26 = load void (%struct.uv_fs_s*)*, void (%struct.uv_fs_s*)** %cb.addr, align 8, !dbg !2506
  %27 = load %struct.uv_fs_s*, %struct.uv_fs_s** %req.addr, align 8, !dbg !2506
  %cb22 = getelementptr inbounds %struct.uv_fs_s, %struct.uv_fs_s* %27, i32 0, i32 6, !dbg !2506
  store void (%struct.uv_fs_s*)* %26, void (%struct.uv_fs_s*)** %cb22, align 8, !dbg !2506
  br label %do.end23, !dbg !2506

do.end23:                                         ; preds = %if.end
  br label %do.body24, !dbg !2508

do.body24:                                        ; preds = %do.end23
  %28 = load i8*, i8** %path.addr, align 8, !dbg !2509
  %cmp25 = icmp ne i8* %28, null, !dbg !2509
  br i1 %cmp25, label %cond.true, label %cond.false, !dbg !2509

cond.true:                                        ; preds = %do.body24
  br label %cond.end, !dbg !2512

cond.false:                                       ; preds = %do.body24
  call void @__assert_fail(i8* getelementptr inbounds ([19 x i8], [19 x i8]* @.str, i32 0, i32 0), i8* getelementptr inbounds ([66 x i8], [66 x i8]* @.str.1, i32 0, i32 0), i32 1268, i8* getelementptr inbounds ([64 x i8], [64 x i8]* @__PRETTY_FUNCTION__.uv_fs_rmdir, i32 0, i32 0)) #8, !dbg !2514
  unreachable, !dbg !2514
                                                  ; No predecessors!
  br label %cond.end, !dbg !2516

cond.end:                                         ; preds = %29, %cond.true
  %30 = load void (%struct.uv_fs_s*)*, void (%struct.uv_fs_s*)** %cb.addr, align 8, !dbg !2518
  %cmp26 = icmp eq void (%struct.uv_fs_s*)* %30, null, !dbg !2518
  br i1 %cmp26, label %if.then27, label %if.else, !dbg !2518

if.then27:                                        ; preds = %cond.end
  %31 = load i8*, i8** %path.addr, align 8, !dbg !2521
  %32 = load %struct.uv_fs_s*, %struct.uv_fs_s** %req.addr, align 8, !dbg !2521
  %path28 = getelementptr inbounds %struct.uv_fs_s, %struct.uv_fs_s* %32, i32 0, i32 9, !dbg !2521
  store i8* %31, i8** %path28, align 8, !dbg !2521
  br label %if.end57, !dbg !2521

if.else:                                          ; preds = %cond.end
  %33 = load i8*, i8** %path.addr, align 8, !dbg !2524
  %call = call i8* @uv__strdup(i8* %33), !dbg !2524
  %34 = load %struct.uv_fs_s*, %struct.uv_fs_s** %req.addr, align 8, !dbg !2524
  %path29 = getelementptr inbounds %struct.uv_fs_s, %struct.uv_fs_s* %34, i32 0, i32 9, !dbg !2524
  store i8* %call, i8** %path29, align 8, !dbg !2524
  %35 = load %struct.uv_fs_s*, %struct.uv_fs_s** %req.addr, align 8, !dbg !2524
  %path30 = getelementptr inbounds %struct.uv_fs_s, %struct.uv_fs_s* %35, i32 0, i32 9, !dbg !2524
  %36 = load i8*, i8** %path30, align 8, !dbg !2524
  %cmp31 = icmp eq i8* %36, null, !dbg !2524
  br i1 %cmp31, label %if.then32, label %if.end56, !dbg !2524

if.then32:                                        ; preds = %if.else
  br label %do.body33, !dbg !2527

do.body33:                                        ; preds = %if.then32
  %37 = load %struct.uv_loop_s*, %struct.uv_loop_s** %loop.addr, align 8, !dbg !2531
  %active_reqs34 = getelementptr inbounds %struct.uv_loop_s, %struct.uv_loop_s* %37, i32 0, i32 3, !dbg !2531
  %38 = load %struct.uv_loop_s*, %struct.uv_loop_s** %loop.addr, align 8, !dbg !2531
  %active_reqs35 = getelementptr inbounds %struct.uv_loop_s, %struct.uv_loop_s* %38, i32 0, i32 3, !dbg !2531
  %arrayidx36 = getelementptr inbounds [2 x i8*], [2 x i8*]* %active_reqs35, i64 0, i64 0, !dbg !2531
  %39 = bitcast i8** %arrayidx36 to [2 x i8*]**, !dbg !2531
  %40 = load [2 x i8*]*, [2 x i8*]** %39, align 8, !dbg !2531
  %cmp37 = icmp eq [2 x i8*]* %active_reqs34, %40, !dbg !2531
  %conv = zext i1 %cmp37 to i32, !dbg !2531
  %cmp38 = icmp eq i32 %conv, 0, !dbg !2531
  br i1 %cmp38, label %cond.true40, label %cond.false41, !dbg !2531

cond.true40:                                      ; preds = %do.body33
  br label %cond.end42, !dbg !2534

cond.false41:                                     ; preds = %do.body33
  call void @__assert_fail(i8* getelementptr inbounds ([113 x i8], [113 x i8]* @.str.2, i32 0, i32 0), i8* getelementptr inbounds ([66 x i8], [66 x i8]* @.str.1, i32 0, i32 0), i32 1268, i8* getelementptr inbounds ([64 x i8], [64 x i8]* @__PRETTY_FUNCTION__.uv_fs_rmdir, i32 0, i32 0)) #8, !dbg !2536
  unreachable, !dbg !2536
                                                  ; No predecessors!
  br label %cond.end42, !dbg !2538

cond.end42:                                       ; preds = %41, %cond.true40
  br label %do.body43, !dbg !2540

do.body43:                                        ; preds = %cond.end42
  %42 = load %struct.uv_fs_s*, %struct.uv_fs_s** %req.addr, align 8, !dbg !2542
  %active_queue44 = getelementptr inbounds %struct.uv_fs_s, %struct.uv_fs_s* %42, i32 0, i32 2, !dbg !2542
  %arrayidx45 = getelementptr inbounds [2 x i8*], [2 x i8*]* %active_queue44, i64 0, i64 0, !dbg !2542
  %43 = bitcast i8** %arrayidx45 to [2 x i8*]**, !dbg !2542
  %44 = load [2 x i8*]*, [2 x i8*]** %43, align 8, !dbg !2542
  %45 = load %struct.uv_fs_s*, %struct.uv_fs_s** %req.addr, align 8, !dbg !2542
  %active_queue46 = getelementptr inbounds %struct.uv_fs_s, %struct.uv_fs_s* %45, i32 0, i32 2, !dbg !2542
  %arrayidx47 = getelementptr inbounds [2 x i8*], [2 x i8*]* %active_queue46, i64 0, i64 1, !dbg !2542
  %46 = bitcast i8** %arrayidx47 to [2 x i8*]**, !dbg !2542
  %47 = load [2 x i8*]*, [2 x i8*]** %46, align 8, !dbg !2542
  %arrayidx48 = getelementptr inbounds [2 x i8*], [2 x i8*]* %47, i64 0, i64 0, !dbg !2542
  %48 = bitcast i8** %arrayidx48 to [2 x i8*]**, !dbg !2542
  store [2 x i8*]* %44, [2 x i8*]** %48, align 8, !dbg !2542
  %49 = load %struct.uv_fs_s*, %struct.uv_fs_s** %req.addr, align 8, !dbg !2542
  %active_queue49 = getelementptr inbounds %struct.uv_fs_s, %struct.uv_fs_s* %49, i32 0, i32 2, !dbg !2542
  %arrayidx50 = getelementptr inbounds [2 x i8*], [2 x i8*]* %active_queue49, i64 0, i64 1, !dbg !2542
  %50 = bitcast i8** %arrayidx50 to [2 x i8*]**, !dbg !2542
  %51 = load [2 x i8*]*, [2 x i8*]** %50, align 8, !dbg !2542
  %52 = load %struct.uv_fs_s*, %struct.uv_fs_s** %req.addr, align 8, !dbg !2542
  %active_queue51 = getelementptr inbounds %struct.uv_fs_s, %struct.uv_fs_s* %52, i32 0, i32 2, !dbg !2542
  %arrayidx52 = getelementptr inbounds [2 x i8*], [2 x i8*]* %active_queue51, i64 0, i64 0, !dbg !2542
  %53 = bitcast i8** %arrayidx52 to [2 x i8*]**, !dbg !2542
  %54 = load [2 x i8*]*, [2 x i8*]** %53, align 8, !dbg !2542
  %arrayidx53 = getelementptr inbounds [2 x i8*], [2 x i8*]* %54, i64 0, i64 1, !dbg !2542
  %55 = bitcast i8** %arrayidx53 to [2 x i8*]**, !dbg !2542
  store [2 x i8*]* %51, [2 x i8*]** %55, align 8, !dbg !2542
  br label %do.end54, !dbg !2542

do.end54:                                         ; preds = %do.body43
  br label %do.end55, !dbg !2545

do.end55:                                         ; preds = %do.end54
  store i32 -12, i32* %retval, align 4, !dbg !2547
  br label %do.end67, !dbg !2547

if.end56:                                         ; preds = %if.else
  br label %if.end57

if.end57:                                         ; preds = %if.end56, %if.then27
  br label %do.end58, !dbg !2549

do.end58:                                         ; preds = %if.end57
  br label %do.body59, !dbg !2551

do.body59:                                        ; preds = %do.end58
  %56 = load void (%struct.uv_fs_s*)*, void (%struct.uv_fs_s*)** %cb.addr, align 8, !dbg !2552
  %cmp60 = icmp ne void (%struct.uv_fs_s*)* %56, null, !dbg !2552
  br i1 %cmp60, label %if.then62, label %if.else63, !dbg !2552

if.then62:                                        ; preds = %do.body59
  %57 = load %struct.uv_loop_s*, %struct.uv_loop_s** %loop.addr, align 8, !dbg !2556
  %58 = load %struct.uv_fs_s*, %struct.uv_fs_s** %req.addr, align 8, !dbg !2556
  %work_req = getelementptr inbounds %struct.uv_fs_s, %struct.uv_fs_s* %58, i32 0, i32 22, !dbg !2556
  call void @uv__work_submit(%struct.uv_loop_s* %57, %struct.uv__work* %work_req, void (%struct.uv__work*)* @uv__fs_work, void (%struct.uv__work*, i32)* @uv__fs_done), !dbg !2556
  store i32 0, i32* %retval, align 4, !dbg !2556
  br label %do.end67, !dbg !2556

if.else63:                                        ; preds = %do.body59
  %59 = load %struct.uv_fs_s*, %struct.uv_fs_s** %req.addr, align 8, !dbg !2559
  %work_req64 = getelementptr inbounds %struct.uv_fs_s, %struct.uv_fs_s* %59, i32 0, i32 22, !dbg !2559
  call void @uv__fs_work(%struct.uv__work* %work_req64), !dbg !2559
  %60 = load %struct.uv_fs_s*, %struct.uv_fs_s** %req.addr, align 8, !dbg !2559
  %result65 = getelementptr inbounds %struct.uv_fs_s, %struct.uv_fs_s* %60, i32 0, i32 7, !dbg !2559
  %61 = load i64, i64* %result65, align 8, !dbg !2559
  %conv66 = trunc i64 %61 to i32, !dbg !2559
  store i32 %conv66, i32* %retval, align 4, !dbg !2559
  br label %do.end67, !dbg !2559

do.end67:                                         ; preds = %do.end55, %if.then62, %if.else63
  %62 = load i32, i32* %retval, align 4, !dbg !2562
  ret i32 %62, !dbg !2562
}

; Function Attrs: nounwind uwtable
define i32 @uv_fs_sendfile(%struct.uv_loop_s* %loop, %struct.uv_fs_s* %req, i32 %out_fd, i32 %in_fd, i64 %off, i64 %len, void (%struct.uv_fs_s*)* %cb) #0 !dbg !463 {
entry:
  %retval = alloca i32, align 4
  %loop.addr = alloca %struct.uv_loop_s*, align 8
  %req.addr = alloca %struct.uv_fs_s*, align 8
  %out_fd.addr = alloca i32, align 4
  %in_fd.addr = alloca i32, align 4
  %off.addr = alloca i64, align 8
  %len.addr = alloca i64, align 8
  %cb.addr = alloca void (%struct.uv_fs_s*)*, align 8
  store %struct.uv_loop_s* %loop, %struct.uv_loop_s** %loop.addr, align 8
  call void @llvm.dbg.declare(metadata %struct.uv_loop_s** %loop.addr, metadata !2563, metadata !580), !dbg !2564
  store %struct.uv_fs_s* %req, %struct.uv_fs_s** %req.addr, align 8
  call void @llvm.dbg.declare(metadata %struct.uv_fs_s** %req.addr, metadata !2565, metadata !580), !dbg !2566
  store i32 %out_fd, i32* %out_fd.addr, align 4
  call void @llvm.dbg.declare(metadata i32* %out_fd.addr, metadata !2567, metadata !580), !dbg !2568
  store i32 %in_fd, i32* %in_fd.addr, align 4
  call void @llvm.dbg.declare(metadata i32* %in_fd.addr, metadata !2569, metadata !580), !dbg !2570
  store i64 %off, i64* %off.addr, align 8
  call void @llvm.dbg.declare(metadata i64* %off.addr, metadata !2571, metadata !580), !dbg !2572
  store i64 %len, i64* %len.addr, align 8
  call void @llvm.dbg.declare(metadata i64* %len.addr, metadata !2573, metadata !580), !dbg !2574
  store void (%struct.uv_fs_s*)* %cb, void (%struct.uv_fs_s*)** %cb.addr, align 8
  call void @llvm.dbg.declare(metadata void (%struct.uv_fs_s*)** %cb.addr, metadata !2575, metadata !580), !dbg !2576
  br label %do.body, !dbg !2577

do.body:                                          ; preds = %entry
  %0 = load %struct.uv_fs_s*, %struct.uv_fs_s** %req.addr, align 8, !dbg !2578
  %type = getelementptr inbounds %struct.uv_fs_s, %struct.uv_fs_s* %0, i32 0, i32 1, !dbg !2578
  store i32 6, i32* %type, align 8, !dbg !2578
  %1 = load void (%struct.uv_fs_s*)*, void (%struct.uv_fs_s*)** %cb.addr, align 8, !dbg !2578
  %cmp = icmp ne void (%struct.uv_fs_s*)* %1, null, !dbg !2578
  br i1 %cmp, label %if.then, label %if.end, !dbg !2578

if.then:                                          ; preds = %do.body
  br label %do.body1, !dbg !2581

do.body1:                                         ; preds = %if.then
  br label %do.body2, !dbg !2584

do.body2:                                         ; preds = %do.body1
  %2 = load %struct.uv_fs_s*, %struct.uv_fs_s** %req.addr, align 8, !dbg !2587
  %type3 = getelementptr inbounds %struct.uv_fs_s, %struct.uv_fs_s* %2, i32 0, i32 1, !dbg !2587
  store i32 6, i32* %type3, align 8, !dbg !2587
  br label %do.end, !dbg !2587

do.end:                                           ; preds = %do.body2
  br label %do.body4, !dbg !2590

do.body4:                                         ; preds = %do.end
  br label %do.body5, !dbg !2592

do.body5:                                         ; preds = %do.body4
  %3 = load %struct.uv_loop_s*, %struct.uv_loop_s** %loop.addr, align 8, !dbg !2595
  %active_reqs = getelementptr inbounds %struct.uv_loop_s, %struct.uv_loop_s* %3, i32 0, i32 3, !dbg !2595
  %4 = load %struct.uv_fs_s*, %struct.uv_fs_s** %req.addr, align 8, !dbg !2595
  %active_queue = getelementptr inbounds %struct.uv_fs_s, %struct.uv_fs_s* %4, i32 0, i32 2, !dbg !2595
  %arrayidx = getelementptr inbounds [2 x i8*], [2 x i8*]* %active_queue, i64 0, i64 0, !dbg !2595
  %5 = bitcast i8** %arrayidx to [2 x i8*]**, !dbg !2595
  store [2 x i8*]* %active_reqs, [2 x i8*]** %5, align 8, !dbg !2595
  %6 = load %struct.uv_loop_s*, %struct.uv_loop_s** %loop.addr, align 8, !dbg !2595
  %active_reqs6 = getelementptr inbounds %struct.uv_loop_s, %struct.uv_loop_s* %6, i32 0, i32 3, !dbg !2595
  %arrayidx7 = getelementptr inbounds [2 x i8*], [2 x i8*]* %active_reqs6, i64 0, i64 1, !dbg !2595
  %7 = bitcast i8** %arrayidx7 to [2 x i8*]**, !dbg !2595
  %8 = load [2 x i8*]*, [2 x i8*]** %7, align 8, !dbg !2595
  %9 = load %struct.uv_fs_s*, %struct.uv_fs_s** %req.addr, align 8, !dbg !2595
  %active_queue8 = getelementptr inbounds %struct.uv_fs_s, %struct.uv_fs_s* %9, i32 0, i32 2, !dbg !2595
  %arrayidx9 = getelementptr inbounds [2 x i8*], [2 x i8*]* %active_queue8, i64 0, i64 1, !dbg !2595
  %10 = bitcast i8** %arrayidx9 to [2 x i8*]**, !dbg !2595
  store [2 x i8*]* %8, [2 x i8*]** %10, align 8, !dbg !2595
  %11 = load %struct.uv_fs_s*, %struct.uv_fs_s** %req.addr, align 8, !dbg !2595
  %active_queue10 = getelementptr inbounds %struct.uv_fs_s, %struct.uv_fs_s* %11, i32 0, i32 2, !dbg !2595
  %12 = load %struct.uv_fs_s*, %struct.uv_fs_s** %req.addr, align 8, !dbg !2595
  %active_queue11 = getelementptr inbounds %struct.uv_fs_s, %struct.uv_fs_s* %12, i32 0, i32 2, !dbg !2595
  %arrayidx12 = getelementptr inbounds [2 x i8*], [2 x i8*]* %active_queue11, i64 0, i64 1, !dbg !2595
  %13 = bitcast i8** %arrayidx12 to [2 x i8*]**, !dbg !2595
  %14 = load [2 x i8*]*, [2 x i8*]** %13, align 8, !dbg !2595
  %arrayidx13 = getelementptr inbounds [2 x i8*], [2 x i8*]* %14, i64 0, i64 0, !dbg !2595
  %15 = bitcast i8** %arrayidx13 to [2 x i8*]**, !dbg !2595
  store [2 x i8*]* %active_queue10, [2 x i8*]** %15, align 8, !dbg !2595
  %16 = load %struct.uv_fs_s*, %struct.uv_fs_s** %req.addr, align 8, !dbg !2595
  %active_queue14 = getelementptr inbounds %struct.uv_fs_s, %struct.uv_fs_s* %16, i32 0, i32 2, !dbg !2595
  %17 = load %struct.uv_loop_s*, %struct.uv_loop_s** %loop.addr, align 8, !dbg !2595
  %active_reqs15 = getelementptr inbounds %struct.uv_loop_s, %struct.uv_loop_s* %17, i32 0, i32 3, !dbg !2595
  %arrayidx16 = getelementptr inbounds [2 x i8*], [2 x i8*]* %active_reqs15, i64 0, i64 1, !dbg !2595
  %18 = bitcast i8** %arrayidx16 to [2 x i8*]**, !dbg !2595
  store [2 x i8*]* %active_queue14, [2 x i8*]** %18, align 8, !dbg !2595
  br label %do.end17, !dbg !2595

do.end17:                                         ; preds = %do.body5
  br label %do.end18, !dbg !2598

do.end18:                                         ; preds = %do.end17
  br label %do.end19, !dbg !2600

do.end19:                                         ; preds = %do.end18
  br label %if.end, !dbg !2602

if.end:                                           ; preds = %do.end19, %do.body
  %19 = load %struct.uv_fs_s*, %struct.uv_fs_s** %req.addr, align 8, !dbg !2604
  %fs_type = getelementptr inbounds %struct.uv_fs_s, %struct.uv_fs_s* %19, i32 0, i32 4, !dbg !2604
  store i32 5, i32* %fs_type, align 8, !dbg !2604
  %20 = load %struct.uv_fs_s*, %struct.uv_fs_s** %req.addr, align 8, !dbg !2604
  %result = getelementptr inbounds %struct.uv_fs_s, %struct.uv_fs_s* %20, i32 0, i32 7, !dbg !2604
  store i64 0, i64* %result, align 8, !dbg !2604
  %21 = load %struct.uv_fs_s*, %struct.uv_fs_s** %req.addr, align 8, !dbg !2604
  %ptr = getelementptr inbounds %struct.uv_fs_s, %struct.uv_fs_s* %21, i32 0, i32 8, !dbg !2604
  store i8* null, i8** %ptr, align 8, !dbg !2604
  %22 = load %struct.uv_loop_s*, %struct.uv_loop_s** %loop.addr, align 8, !dbg !2604
  %23 = load %struct.uv_fs_s*, %struct.uv_fs_s** %req.addr, align 8, !dbg !2604
  %loop20 = getelementptr inbounds %struct.uv_fs_s, %struct.uv_fs_s* %23, i32 0, i32 5, !dbg !2604
  store %struct.uv_loop_s* %22, %struct.uv_loop_s** %loop20, align 8, !dbg !2604
  %24 = load %struct.uv_fs_s*, %struct.uv_fs_s** %req.addr, align 8, !dbg !2604
  %path = getelementptr inbounds %struct.uv_fs_s, %struct.uv_fs_s* %24, i32 0, i32 9, !dbg !2604
  store i8* null, i8** %path, align 8, !dbg !2604
  %25 = load %struct.uv_fs_s*, %struct.uv_fs_s** %req.addr, align 8, !dbg !2604
  %new_path = getelementptr inbounds %struct.uv_fs_s, %struct.uv_fs_s* %25, i32 0, i32 11, !dbg !2604
  store i8* null, i8** %new_path, align 8, !dbg !2604
  %26 = load void (%struct.uv_fs_s*)*, void (%struct.uv_fs_s*)** %cb.addr, align 8, !dbg !2604
  %27 = load %struct.uv_fs_s*, %struct.uv_fs_s** %req.addr, align 8, !dbg !2604
  %cb21 = getelementptr inbounds %struct.uv_fs_s, %struct.uv_fs_s* %27, i32 0, i32 6, !dbg !2604
  store void (%struct.uv_fs_s*)* %26, void (%struct.uv_fs_s*)** %cb21, align 8, !dbg !2604
  br label %do.end22, !dbg !2604

do.end22:                                         ; preds = %if.end
  %28 = load i32, i32* %in_fd.addr, align 4, !dbg !2606
  %29 = load %struct.uv_fs_s*, %struct.uv_fs_s** %req.addr, align 8, !dbg !2607
  %flags = getelementptr inbounds %struct.uv_fs_s, %struct.uv_fs_s* %29, i32 0, i32 13, !dbg !2608
  store i32 %28, i32* %flags, align 4, !dbg !2609
  %30 = load i32, i32* %out_fd.addr, align 4, !dbg !2610
  %31 = load %struct.uv_fs_s*, %struct.uv_fs_s** %req.addr, align 8, !dbg !2611
  %file = getelementptr inbounds %struct.uv_fs_s, %struct.uv_fs_s* %31, i32 0, i32 12, !dbg !2612
  store i32 %30, i32* %file, align 8, !dbg !2613
  %32 = load i64, i64* %off.addr, align 8, !dbg !2614
  %33 = load %struct.uv_fs_s*, %struct.uv_fs_s** %req.addr, align 8, !dbg !2615
  %off23 = getelementptr inbounds %struct.uv_fs_s, %struct.uv_fs_s* %33, i32 0, i32 17, !dbg !2616
  store i64 %32, i64* %off23, align 8, !dbg !2617
  %34 = load i64, i64* %len.addr, align 8, !dbg !2618
  %35 = load %struct.uv_fs_s*, %struct.uv_fs_s** %req.addr, align 8, !dbg !2619
  %bufsml = getelementptr inbounds %struct.uv_fs_s, %struct.uv_fs_s* %35, i32 0, i32 23, !dbg !2620
  %arrayidx24 = getelementptr inbounds [4 x %struct.uv_buf_t], [4 x %struct.uv_buf_t]* %bufsml, i64 0, i64 0, !dbg !2619
  %len25 = getelementptr inbounds %struct.uv_buf_t, %struct.uv_buf_t* %arrayidx24, i32 0, i32 1, !dbg !2621
  store i64 %34, i64* %len25, align 8, !dbg !2622
  br label %do.body26, !dbg !2623

do.body26:                                        ; preds = %do.end22
  %36 = load void (%struct.uv_fs_s*)*, void (%struct.uv_fs_s*)** %cb.addr, align 8, !dbg !2624
  %cmp27 = icmp ne void (%struct.uv_fs_s*)* %36, null, !dbg !2624
  br i1 %cmp27, label %if.then28, label %if.else, !dbg !2624

if.then28:                                        ; preds = %do.body26
  %37 = load %struct.uv_loop_s*, %struct.uv_loop_s** %loop.addr, align 8, !dbg !2628
  %38 = load %struct.uv_fs_s*, %struct.uv_fs_s** %req.addr, align 8, !dbg !2628
  %work_req = getelementptr inbounds %struct.uv_fs_s, %struct.uv_fs_s* %38, i32 0, i32 22, !dbg !2628
  call void @uv__work_submit(%struct.uv_loop_s* %37, %struct.uv__work* %work_req, void (%struct.uv__work*)* @uv__fs_work, void (%struct.uv__work*, i32)* @uv__fs_done), !dbg !2628
  store i32 0, i32* %retval, align 4, !dbg !2628
  br label %do.end31, !dbg !2628

if.else:                                          ; preds = %do.body26
  %39 = load %struct.uv_fs_s*, %struct.uv_fs_s** %req.addr, align 8, !dbg !2631
  %work_req29 = getelementptr inbounds %struct.uv_fs_s, %struct.uv_fs_s* %39, i32 0, i32 22, !dbg !2631
  call void @uv__fs_work(%struct.uv__work* %work_req29), !dbg !2631
  %40 = load %struct.uv_fs_s*, %struct.uv_fs_s** %req.addr, align 8, !dbg !2631
  %result30 = getelementptr inbounds %struct.uv_fs_s, %struct.uv_fs_s* %40, i32 0, i32 7, !dbg !2631
  %41 = load i64, i64* %result30, align 8, !dbg !2631
  %conv = trunc i64 %41 to i32, !dbg !2631
  store i32 %conv, i32* %retval, align 4, !dbg !2631
  br label %do.end31, !dbg !2631

do.end31:                                         ; preds = %if.then28, %if.else
  %42 = load i32, i32* %retval, align 4, !dbg !2634
  ret i32 %42, !dbg !2634
}

; Function Attrs: nounwind uwtable
define i32 @uv_fs_stat(%struct.uv_loop_s* %loop, %struct.uv_fs_s* %req, i8* %path, void (%struct.uv_fs_s*)* %cb) #0 !dbg !466 {
entry:
  %retval = alloca i32, align 4
  %loop.addr = alloca %struct.uv_loop_s*, align 8
  %req.addr = alloca %struct.uv_fs_s*, align 8
  %path.addr = alloca i8*, align 8
  %cb.addr = alloca void (%struct.uv_fs_s*)*, align 8
  store %struct.uv_loop_s* %loop, %struct.uv_loop_s** %loop.addr, align 8
  call void @llvm.dbg.declare(metadata %struct.uv_loop_s** %loop.addr, metadata !2635, metadata !580), !dbg !2636
  store %struct.uv_fs_s* %req, %struct.uv_fs_s** %req.addr, align 8
  call void @llvm.dbg.declare(metadata %struct.uv_fs_s** %req.addr, metadata !2637, metadata !580), !dbg !2638
  store i8* %path, i8** %path.addr, align 8
  call void @llvm.dbg.declare(metadata i8** %path.addr, metadata !2639, metadata !580), !dbg !2640
  store void (%struct.uv_fs_s*)* %cb, void (%struct.uv_fs_s*)** %cb.addr, align 8
  call void @llvm.dbg.declare(metadata void (%struct.uv_fs_s*)** %cb.addr, metadata !2641, metadata !580), !dbg !2642
  br label %do.body, !dbg !2643

do.body:                                          ; preds = %entry
  %0 = load %struct.uv_fs_s*, %struct.uv_fs_s** %req.addr, align 8, !dbg !2644
  %type = getelementptr inbounds %struct.uv_fs_s, %struct.uv_fs_s* %0, i32 0, i32 1, !dbg !2644
  store i32 6, i32* %type, align 8, !dbg !2644
  %1 = load void (%struct.uv_fs_s*)*, void (%struct.uv_fs_s*)** %cb.addr, align 8, !dbg !2644
  %cmp = icmp ne void (%struct.uv_fs_s*)* %1, null, !dbg !2644
  br i1 %cmp, label %if.then, label %if.end, !dbg !2644

if.then:                                          ; preds = %do.body
  br label %do.body1, !dbg !2647

do.body1:                                         ; preds = %if.then
  br label %do.body2, !dbg !2650

do.body2:                                         ; preds = %do.body1
  %2 = load %struct.uv_fs_s*, %struct.uv_fs_s** %req.addr, align 8, !dbg !2653
  %type3 = getelementptr inbounds %struct.uv_fs_s, %struct.uv_fs_s* %2, i32 0, i32 1, !dbg !2653
  store i32 6, i32* %type3, align 8, !dbg !2653
  br label %do.end, !dbg !2653

do.end:                                           ; preds = %do.body2
  br label %do.body4, !dbg !2656

do.body4:                                         ; preds = %do.end
  br label %do.body5, !dbg !2658

do.body5:                                         ; preds = %do.body4
  %3 = load %struct.uv_loop_s*, %struct.uv_loop_s** %loop.addr, align 8, !dbg !2661
  %active_reqs = getelementptr inbounds %struct.uv_loop_s, %struct.uv_loop_s* %3, i32 0, i32 3, !dbg !2661
  %4 = load %struct.uv_fs_s*, %struct.uv_fs_s** %req.addr, align 8, !dbg !2661
  %active_queue = getelementptr inbounds %struct.uv_fs_s, %struct.uv_fs_s* %4, i32 0, i32 2, !dbg !2661
  %arrayidx = getelementptr inbounds [2 x i8*], [2 x i8*]* %active_queue, i64 0, i64 0, !dbg !2661
  %5 = bitcast i8** %arrayidx to [2 x i8*]**, !dbg !2661
  store [2 x i8*]* %active_reqs, [2 x i8*]** %5, align 8, !dbg !2661
  %6 = load %struct.uv_loop_s*, %struct.uv_loop_s** %loop.addr, align 8, !dbg !2661
  %active_reqs6 = getelementptr inbounds %struct.uv_loop_s, %struct.uv_loop_s* %6, i32 0, i32 3, !dbg !2661
  %arrayidx7 = getelementptr inbounds [2 x i8*], [2 x i8*]* %active_reqs6, i64 0, i64 1, !dbg !2661
  %7 = bitcast i8** %arrayidx7 to [2 x i8*]**, !dbg !2661
  %8 = load [2 x i8*]*, [2 x i8*]** %7, align 8, !dbg !2661
  %9 = load %struct.uv_fs_s*, %struct.uv_fs_s** %req.addr, align 8, !dbg !2661
  %active_queue8 = getelementptr inbounds %struct.uv_fs_s, %struct.uv_fs_s* %9, i32 0, i32 2, !dbg !2661
  %arrayidx9 = getelementptr inbounds [2 x i8*], [2 x i8*]* %active_queue8, i64 0, i64 1, !dbg !2661
  %10 = bitcast i8** %arrayidx9 to [2 x i8*]**, !dbg !2661
  store [2 x i8*]* %8, [2 x i8*]** %10, align 8, !dbg !2661
  %11 = load %struct.uv_fs_s*, %struct.uv_fs_s** %req.addr, align 8, !dbg !2661
  %active_queue10 = getelementptr inbounds %struct.uv_fs_s, %struct.uv_fs_s* %11, i32 0, i32 2, !dbg !2661
  %12 = load %struct.uv_fs_s*, %struct.uv_fs_s** %req.addr, align 8, !dbg !2661
  %active_queue11 = getelementptr inbounds %struct.uv_fs_s, %struct.uv_fs_s* %12, i32 0, i32 2, !dbg !2661
  %arrayidx12 = getelementptr inbounds [2 x i8*], [2 x i8*]* %active_queue11, i64 0, i64 1, !dbg !2661
  %13 = bitcast i8** %arrayidx12 to [2 x i8*]**, !dbg !2661
  %14 = load [2 x i8*]*, [2 x i8*]** %13, align 8, !dbg !2661
  %arrayidx13 = getelementptr inbounds [2 x i8*], [2 x i8*]* %14, i64 0, i64 0, !dbg !2661
  %15 = bitcast i8** %arrayidx13 to [2 x i8*]**, !dbg !2661
  store [2 x i8*]* %active_queue10, [2 x i8*]** %15, align 8, !dbg !2661
  %16 = load %struct.uv_fs_s*, %struct.uv_fs_s** %req.addr, align 8, !dbg !2661
  %active_queue14 = getelementptr inbounds %struct.uv_fs_s, %struct.uv_fs_s* %16, i32 0, i32 2, !dbg !2661
  %17 = load %struct.uv_loop_s*, %struct.uv_loop_s** %loop.addr, align 8, !dbg !2661
  %active_reqs15 = getelementptr inbounds %struct.uv_loop_s, %struct.uv_loop_s* %17, i32 0, i32 3, !dbg !2661
  %arrayidx16 = getelementptr inbounds [2 x i8*], [2 x i8*]* %active_reqs15, i64 0, i64 1, !dbg !2661
  %18 = bitcast i8** %arrayidx16 to [2 x i8*]**, !dbg !2661
  store [2 x i8*]* %active_queue14, [2 x i8*]** %18, align 8, !dbg !2661
  br label %do.end17, !dbg !2661

do.end17:                                         ; preds = %do.body5
  br label %do.end18, !dbg !2664

do.end18:                                         ; preds = %do.end17
  br label %do.end19, !dbg !2666

do.end19:                                         ; preds = %do.end18
  br label %if.end, !dbg !2668

if.end:                                           ; preds = %do.end19, %do.body
  %19 = load %struct.uv_fs_s*, %struct.uv_fs_s** %req.addr, align 8, !dbg !2670
  %fs_type = getelementptr inbounds %struct.uv_fs_s, %struct.uv_fs_s* %19, i32 0, i32 4, !dbg !2670
  store i32 6, i32* %fs_type, align 8, !dbg !2670
  %20 = load %struct.uv_fs_s*, %struct.uv_fs_s** %req.addr, align 8, !dbg !2670
  %result = getelementptr inbounds %struct.uv_fs_s, %struct.uv_fs_s* %20, i32 0, i32 7, !dbg !2670
  store i64 0, i64* %result, align 8, !dbg !2670
  %21 = load %struct.uv_fs_s*, %struct.uv_fs_s** %req.addr, align 8, !dbg !2670
  %ptr = getelementptr inbounds %struct.uv_fs_s, %struct.uv_fs_s* %21, i32 0, i32 8, !dbg !2670
  store i8* null, i8** %ptr, align 8, !dbg !2670
  %22 = load %struct.uv_loop_s*, %struct.uv_loop_s** %loop.addr, align 8, !dbg !2670
  %23 = load %struct.uv_fs_s*, %struct.uv_fs_s** %req.addr, align 8, !dbg !2670
  %loop20 = getelementptr inbounds %struct.uv_fs_s, %struct.uv_fs_s* %23, i32 0, i32 5, !dbg !2670
  store %struct.uv_loop_s* %22, %struct.uv_loop_s** %loop20, align 8, !dbg !2670
  %24 = load %struct.uv_fs_s*, %struct.uv_fs_s** %req.addr, align 8, !dbg !2670
  %path21 = getelementptr inbounds %struct.uv_fs_s, %struct.uv_fs_s* %24, i32 0, i32 9, !dbg !2670
  store i8* null, i8** %path21, align 8, !dbg !2670
  %25 = load %struct.uv_fs_s*, %struct.uv_fs_s** %req.addr, align 8, !dbg !2670
  %new_path = getelementptr inbounds %struct.uv_fs_s, %struct.uv_fs_s* %25, i32 0, i32 11, !dbg !2670
  store i8* null, i8** %new_path, align 8, !dbg !2670
  %26 = load void (%struct.uv_fs_s*)*, void (%struct.uv_fs_s*)** %cb.addr, align 8, !dbg !2670
  %27 = load %struct.uv_fs_s*, %struct.uv_fs_s** %req.addr, align 8, !dbg !2670
  %cb22 = getelementptr inbounds %struct.uv_fs_s, %struct.uv_fs_s* %27, i32 0, i32 6, !dbg !2670
  store void (%struct.uv_fs_s*)* %26, void (%struct.uv_fs_s*)** %cb22, align 8, !dbg !2670
  br label %do.end23, !dbg !2670

do.end23:                                         ; preds = %if.end
  br label %do.body24, !dbg !2672

do.body24:                                        ; preds = %do.end23
  %28 = load i8*, i8** %path.addr, align 8, !dbg !2673
  %cmp25 = icmp ne i8* %28, null, !dbg !2673
  br i1 %cmp25, label %cond.true, label %cond.false, !dbg !2673

cond.true:                                        ; preds = %do.body24
  br label %cond.end, !dbg !2676

cond.false:                                       ; preds = %do.body24
  call void @__assert_fail(i8* getelementptr inbounds ([19 x i8], [19 x i8]* @.str, i32 0, i32 0), i8* getelementptr inbounds ([66 x i8], [66 x i8]* @.str.1, i32 0, i32 0), i32 1291, i8* getelementptr inbounds ([63 x i8], [63 x i8]* @__PRETTY_FUNCTION__.uv_fs_stat, i32 0, i32 0)) #8, !dbg !2678
  unreachable, !dbg !2678
                                                  ; No predecessors!
  br label %cond.end, !dbg !2680

cond.end:                                         ; preds = %29, %cond.true
  %30 = load void (%struct.uv_fs_s*)*, void (%struct.uv_fs_s*)** %cb.addr, align 8, !dbg !2682
  %cmp26 = icmp eq void (%struct.uv_fs_s*)* %30, null, !dbg !2682
  br i1 %cmp26, label %if.then27, label %if.else, !dbg !2682

if.then27:                                        ; preds = %cond.end
  %31 = load i8*, i8** %path.addr, align 8, !dbg !2685
  %32 = load %struct.uv_fs_s*, %struct.uv_fs_s** %req.addr, align 8, !dbg !2685
  %path28 = getelementptr inbounds %struct.uv_fs_s, %struct.uv_fs_s* %32, i32 0, i32 9, !dbg !2685
  store i8* %31, i8** %path28, align 8, !dbg !2685
  br label %if.end57, !dbg !2685

if.else:                                          ; preds = %cond.end
  %33 = load i8*, i8** %path.addr, align 8, !dbg !2688
  %call = call i8* @uv__strdup(i8* %33), !dbg !2688
  %34 = load %struct.uv_fs_s*, %struct.uv_fs_s** %req.addr, align 8, !dbg !2688
  %path29 = getelementptr inbounds %struct.uv_fs_s, %struct.uv_fs_s* %34, i32 0, i32 9, !dbg !2688
  store i8* %call, i8** %path29, align 8, !dbg !2688
  %35 = load %struct.uv_fs_s*, %struct.uv_fs_s** %req.addr, align 8, !dbg !2688
  %path30 = getelementptr inbounds %struct.uv_fs_s, %struct.uv_fs_s* %35, i32 0, i32 9, !dbg !2688
  %36 = load i8*, i8** %path30, align 8, !dbg !2688
  %cmp31 = icmp eq i8* %36, null, !dbg !2688
  br i1 %cmp31, label %if.then32, label %if.end56, !dbg !2688

if.then32:                                        ; preds = %if.else
  br label %do.body33, !dbg !2691

do.body33:                                        ; preds = %if.then32
  %37 = load %struct.uv_loop_s*, %struct.uv_loop_s** %loop.addr, align 8, !dbg !2695
  %active_reqs34 = getelementptr inbounds %struct.uv_loop_s, %struct.uv_loop_s* %37, i32 0, i32 3, !dbg !2695
  %38 = load %struct.uv_loop_s*, %struct.uv_loop_s** %loop.addr, align 8, !dbg !2695
  %active_reqs35 = getelementptr inbounds %struct.uv_loop_s, %struct.uv_loop_s* %38, i32 0, i32 3, !dbg !2695
  %arrayidx36 = getelementptr inbounds [2 x i8*], [2 x i8*]* %active_reqs35, i64 0, i64 0, !dbg !2695
  %39 = bitcast i8** %arrayidx36 to [2 x i8*]**, !dbg !2695
  %40 = load [2 x i8*]*, [2 x i8*]** %39, align 8, !dbg !2695
  %cmp37 = icmp eq [2 x i8*]* %active_reqs34, %40, !dbg !2695
  %conv = zext i1 %cmp37 to i32, !dbg !2695
  %cmp38 = icmp eq i32 %conv, 0, !dbg !2695
  br i1 %cmp38, label %cond.true40, label %cond.false41, !dbg !2695

cond.true40:                                      ; preds = %do.body33
  br label %cond.end42, !dbg !2698

cond.false41:                                     ; preds = %do.body33
  call void @__assert_fail(i8* getelementptr inbounds ([113 x i8], [113 x i8]* @.str.2, i32 0, i32 0), i8* getelementptr inbounds ([66 x i8], [66 x i8]* @.str.1, i32 0, i32 0), i32 1291, i8* getelementptr inbounds ([63 x i8], [63 x i8]* @__PRETTY_FUNCTION__.uv_fs_stat, i32 0, i32 0)) #8, !dbg !2700
  unreachable, !dbg !2700
                                                  ; No predecessors!
  br label %cond.end42, !dbg !2702

cond.end42:                                       ; preds = %41, %cond.true40
  br label %do.body43, !dbg !2704

do.body43:                                        ; preds = %cond.end42
  %42 = load %struct.uv_fs_s*, %struct.uv_fs_s** %req.addr, align 8, !dbg !2706
  %active_queue44 = getelementptr inbounds %struct.uv_fs_s, %struct.uv_fs_s* %42, i32 0, i32 2, !dbg !2706
  %arrayidx45 = getelementptr inbounds [2 x i8*], [2 x i8*]* %active_queue44, i64 0, i64 0, !dbg !2706
  %43 = bitcast i8** %arrayidx45 to [2 x i8*]**, !dbg !2706
  %44 = load [2 x i8*]*, [2 x i8*]** %43, align 8, !dbg !2706
  %45 = load %struct.uv_fs_s*, %struct.uv_fs_s** %req.addr, align 8, !dbg !2706
  %active_queue46 = getelementptr inbounds %struct.uv_fs_s, %struct.uv_fs_s* %45, i32 0, i32 2, !dbg !2706
  %arrayidx47 = getelementptr inbounds [2 x i8*], [2 x i8*]* %active_queue46, i64 0, i64 1, !dbg !2706
  %46 = bitcast i8** %arrayidx47 to [2 x i8*]**, !dbg !2706
  %47 = load [2 x i8*]*, [2 x i8*]** %46, align 8, !dbg !2706
  %arrayidx48 = getelementptr inbounds [2 x i8*], [2 x i8*]* %47, i64 0, i64 0, !dbg !2706
  %48 = bitcast i8** %arrayidx48 to [2 x i8*]**, !dbg !2706
  store [2 x i8*]* %44, [2 x i8*]** %48, align 8, !dbg !2706
  %49 = load %struct.uv_fs_s*, %struct.uv_fs_s** %req.addr, align 8, !dbg !2706
  %active_queue49 = getelementptr inbounds %struct.uv_fs_s, %struct.uv_fs_s* %49, i32 0, i32 2, !dbg !2706
  %arrayidx50 = getelementptr inbounds [2 x i8*], [2 x i8*]* %active_queue49, i64 0, i64 1, !dbg !2706
  %50 = bitcast i8** %arrayidx50 to [2 x i8*]**, !dbg !2706
  %51 = load [2 x i8*]*, [2 x i8*]** %50, align 8, !dbg !2706
  %52 = load %struct.uv_fs_s*, %struct.uv_fs_s** %req.addr, align 8, !dbg !2706
  %active_queue51 = getelementptr inbounds %struct.uv_fs_s, %struct.uv_fs_s* %52, i32 0, i32 2, !dbg !2706
  %arrayidx52 = getelementptr inbounds [2 x i8*], [2 x i8*]* %active_queue51, i64 0, i64 0, !dbg !2706
  %53 = bitcast i8** %arrayidx52 to [2 x i8*]**, !dbg !2706
  %54 = load [2 x i8*]*, [2 x i8*]** %53, align 8, !dbg !2706
  %arrayidx53 = getelementptr inbounds [2 x i8*], [2 x i8*]* %54, i64 0, i64 1, !dbg !2706
  %55 = bitcast i8** %arrayidx53 to [2 x i8*]**, !dbg !2706
  store [2 x i8*]* %51, [2 x i8*]** %55, align 8, !dbg !2706
  br label %do.end54, !dbg !2706

do.end54:                                         ; preds = %do.body43
  br label %do.end55, !dbg !2709

do.end55:                                         ; preds = %do.end54
  store i32 -12, i32* %retval, align 4, !dbg !2711
  br label %do.end67, !dbg !2711

if.end56:                                         ; preds = %if.else
  br label %if.end57

if.end57:                                         ; preds = %if.end56, %if.then27
  br label %do.end58, !dbg !2713

do.end58:                                         ; preds = %if.end57
  br label %do.body59, !dbg !2715

do.body59:                                        ; preds = %do.end58
  %56 = load void (%struct.uv_fs_s*)*, void (%struct.uv_fs_s*)** %cb.addr, align 8, !dbg !2716
  %cmp60 = icmp ne void (%struct.uv_fs_s*)* %56, null, !dbg !2716
  br i1 %cmp60, label %if.then62, label %if.else63, !dbg !2716

if.then62:                                        ; preds = %do.body59
  %57 = load %struct.uv_loop_s*, %struct.uv_loop_s** %loop.addr, align 8, !dbg !2720
  %58 = load %struct.uv_fs_s*, %struct.uv_fs_s** %req.addr, align 8, !dbg !2720
  %work_req = getelementptr inbounds %struct.uv_fs_s, %struct.uv_fs_s* %58, i32 0, i32 22, !dbg !2720
  call void @uv__work_submit(%struct.uv_loop_s* %57, %struct.uv__work* %work_req, void (%struct.uv__work*)* @uv__fs_work, void (%struct.uv__work*, i32)* @uv__fs_done), !dbg !2720
  store i32 0, i32* %retval, align 4, !dbg !2720
  br label %do.end67, !dbg !2720

if.else63:                                        ; preds = %do.body59
  %59 = load %struct.uv_fs_s*, %struct.uv_fs_s** %req.addr, align 8, !dbg !2723
  %work_req64 = getelementptr inbounds %struct.uv_fs_s, %struct.uv_fs_s* %59, i32 0, i32 22, !dbg !2723
  call void @uv__fs_work(%struct.uv__work* %work_req64), !dbg !2723
  %60 = load %struct.uv_fs_s*, %struct.uv_fs_s** %req.addr, align 8, !dbg !2723
  %result65 = getelementptr inbounds %struct.uv_fs_s, %struct.uv_fs_s* %60, i32 0, i32 7, !dbg !2723
  %61 = load i64, i64* %result65, align 8, !dbg !2723
  %conv66 = trunc i64 %61 to i32, !dbg !2723
  store i32 %conv66, i32* %retval, align 4, !dbg !2723
  br label %do.end67, !dbg !2723

do.end67:                                         ; preds = %do.end55, %if.then62, %if.else63
  %62 = load i32, i32* %retval, align 4, !dbg !2726
  ret i32 %62, !dbg !2726
}

; Function Attrs: nounwind uwtable
define i32 @uv_fs_symlink(%struct.uv_loop_s* %loop, %struct.uv_fs_s* %req, i8* %path, i8* %new_path, i32 %flags, void (%struct.uv_fs_s*)* %cb) #0 !dbg !467 {
entry:
  %retval = alloca i32, align 4
  %loop.addr = alloca %struct.uv_loop_s*, align 8
  %req.addr = alloca %struct.uv_fs_s*, align 8
  %path.addr = alloca i8*, align 8
  %new_path.addr = alloca i8*, align 8
  %flags.addr = alloca i32, align 4
  %cb.addr = alloca void (%struct.uv_fs_s*)*, align 8
  %path_len = alloca i64, align 8
  %new_path_len = alloca i64, align 8
  store %struct.uv_loop_s* %loop, %struct.uv_loop_s** %loop.addr, align 8
  call void @llvm.dbg.declare(metadata %struct.uv_loop_s** %loop.addr, metadata !2727, metadata !580), !dbg !2728
  store %struct.uv_fs_s* %req, %struct.uv_fs_s** %req.addr, align 8
  call void @llvm.dbg.declare(metadata %struct.uv_fs_s** %req.addr, metadata !2729, metadata !580), !dbg !2730
  store i8* %path, i8** %path.addr, align 8
  call void @llvm.dbg.declare(metadata i8** %path.addr, metadata !2731, metadata !580), !dbg !2732
  store i8* %new_path, i8** %new_path.addr, align 8
  call void @llvm.dbg.declare(metadata i8** %new_path.addr, metadata !2733, metadata !580), !dbg !2734
  store i32 %flags, i32* %flags.addr, align 4
  call void @llvm.dbg.declare(metadata i32* %flags.addr, metadata !2735, metadata !580), !dbg !2736
  store void (%struct.uv_fs_s*)* %cb, void (%struct.uv_fs_s*)** %cb.addr, align 8
  call void @llvm.dbg.declare(metadata void (%struct.uv_fs_s*)** %cb.addr, metadata !2737, metadata !580), !dbg !2738
  br label %do.body, !dbg !2739

do.body:                                          ; preds = %entry
  %0 = load %struct.uv_fs_s*, %struct.uv_fs_s** %req.addr, align 8, !dbg !2740
  %type = getelementptr inbounds %struct.uv_fs_s, %struct.uv_fs_s* %0, i32 0, i32 1, !dbg !2740
  store i32 6, i32* %type, align 8, !dbg !2740
  %1 = load void (%struct.uv_fs_s*)*, void (%struct.uv_fs_s*)** %cb.addr, align 8, !dbg !2740
  %cmp = icmp ne void (%struct.uv_fs_s*)* %1, null, !dbg !2740
  br i1 %cmp, label %if.then, label %if.end, !dbg !2740

if.then:                                          ; preds = %do.body
  br label %do.body1, !dbg !2743

do.body1:                                         ; preds = %if.then
  br label %do.body2, !dbg !2746

do.body2:                                         ; preds = %do.body1
  %2 = load %struct.uv_fs_s*, %struct.uv_fs_s** %req.addr, align 8, !dbg !2749
  %type3 = getelementptr inbounds %struct.uv_fs_s, %struct.uv_fs_s* %2, i32 0, i32 1, !dbg !2749
  store i32 6, i32* %type3, align 8, !dbg !2749
  br label %do.end, !dbg !2749

do.end:                                           ; preds = %do.body2
  br label %do.body4, !dbg !2752

do.body4:                                         ; preds = %do.end
  br label %do.body5, !dbg !2754

do.body5:                                         ; preds = %do.body4
  %3 = load %struct.uv_loop_s*, %struct.uv_loop_s** %loop.addr, align 8, !dbg !2757
  %active_reqs = getelementptr inbounds %struct.uv_loop_s, %struct.uv_loop_s* %3, i32 0, i32 3, !dbg !2757
  %4 = load %struct.uv_fs_s*, %struct.uv_fs_s** %req.addr, align 8, !dbg !2757
  %active_queue = getelementptr inbounds %struct.uv_fs_s, %struct.uv_fs_s* %4, i32 0, i32 2, !dbg !2757
  %arrayidx = getelementptr inbounds [2 x i8*], [2 x i8*]* %active_queue, i64 0, i64 0, !dbg !2757
  %5 = bitcast i8** %arrayidx to [2 x i8*]**, !dbg !2757
  store [2 x i8*]* %active_reqs, [2 x i8*]** %5, align 8, !dbg !2757
  %6 = load %struct.uv_loop_s*, %struct.uv_loop_s** %loop.addr, align 8, !dbg !2757
  %active_reqs6 = getelementptr inbounds %struct.uv_loop_s, %struct.uv_loop_s* %6, i32 0, i32 3, !dbg !2757
  %arrayidx7 = getelementptr inbounds [2 x i8*], [2 x i8*]* %active_reqs6, i64 0, i64 1, !dbg !2757
  %7 = bitcast i8** %arrayidx7 to [2 x i8*]**, !dbg !2757
  %8 = load [2 x i8*]*, [2 x i8*]** %7, align 8, !dbg !2757
  %9 = load %struct.uv_fs_s*, %struct.uv_fs_s** %req.addr, align 8, !dbg !2757
  %active_queue8 = getelementptr inbounds %struct.uv_fs_s, %struct.uv_fs_s* %9, i32 0, i32 2, !dbg !2757
  %arrayidx9 = getelementptr inbounds [2 x i8*], [2 x i8*]* %active_queue8, i64 0, i64 1, !dbg !2757
  %10 = bitcast i8** %arrayidx9 to [2 x i8*]**, !dbg !2757
  store [2 x i8*]* %8, [2 x i8*]** %10, align 8, !dbg !2757
  %11 = load %struct.uv_fs_s*, %struct.uv_fs_s** %req.addr, align 8, !dbg !2757
  %active_queue10 = getelementptr inbounds %struct.uv_fs_s, %struct.uv_fs_s* %11, i32 0, i32 2, !dbg !2757
  %12 = load %struct.uv_fs_s*, %struct.uv_fs_s** %req.addr, align 8, !dbg !2757
  %active_queue11 = getelementptr inbounds %struct.uv_fs_s, %struct.uv_fs_s* %12, i32 0, i32 2, !dbg !2757
  %arrayidx12 = getelementptr inbounds [2 x i8*], [2 x i8*]* %active_queue11, i64 0, i64 1, !dbg !2757
  %13 = bitcast i8** %arrayidx12 to [2 x i8*]**, !dbg !2757
  %14 = load [2 x i8*]*, [2 x i8*]** %13, align 8, !dbg !2757
  %arrayidx13 = getelementptr inbounds [2 x i8*], [2 x i8*]* %14, i64 0, i64 0, !dbg !2757
  %15 = bitcast i8** %arrayidx13 to [2 x i8*]**, !dbg !2757
  store [2 x i8*]* %active_queue10, [2 x i8*]** %15, align 8, !dbg !2757
  %16 = load %struct.uv_fs_s*, %struct.uv_fs_s** %req.addr, align 8, !dbg !2757
  %active_queue14 = getelementptr inbounds %struct.uv_fs_s, %struct.uv_fs_s* %16, i32 0, i32 2, !dbg !2757
  %17 = load %struct.uv_loop_s*, %struct.uv_loop_s** %loop.addr, align 8, !dbg !2757
  %active_reqs15 = getelementptr inbounds %struct.uv_loop_s, %struct.uv_loop_s* %17, i32 0, i32 3, !dbg !2757
  %arrayidx16 = getelementptr inbounds [2 x i8*], [2 x i8*]* %active_reqs15, i64 0, i64 1, !dbg !2757
  %18 = bitcast i8** %arrayidx16 to [2 x i8*]**, !dbg !2757
  store [2 x i8*]* %active_queue14, [2 x i8*]** %18, align 8, !dbg !2757
  br label %do.end17, !dbg !2757

do.end17:                                         ; preds = %do.body5
  br label %do.end18, !dbg !2760

do.end18:                                         ; preds = %do.end17
  br label %do.end19, !dbg !2762

do.end19:                                         ; preds = %do.end18
  br label %if.end, !dbg !2764

if.end:                                           ; preds = %do.end19, %do.body
  %19 = load %struct.uv_fs_s*, %struct.uv_fs_s** %req.addr, align 8, !dbg !2766
  %fs_type = getelementptr inbounds %struct.uv_fs_s, %struct.uv_fs_s* %19, i32 0, i32 4, !dbg !2766
  store i32 24, i32* %fs_type, align 8, !dbg !2766
  %20 = load %struct.uv_fs_s*, %struct.uv_fs_s** %req.addr, align 8, !dbg !2766
  %result = getelementptr inbounds %struct.uv_fs_s, %struct.uv_fs_s* %20, i32 0, i32 7, !dbg !2766
  store i64 0, i64* %result, align 8, !dbg !2766
  %21 = load %struct.uv_fs_s*, %struct.uv_fs_s** %req.addr, align 8, !dbg !2766
  %ptr = getelementptr inbounds %struct.uv_fs_s, %struct.uv_fs_s* %21, i32 0, i32 8, !dbg !2766
  store i8* null, i8** %ptr, align 8, !dbg !2766
  %22 = load %struct.uv_loop_s*, %struct.uv_loop_s** %loop.addr, align 8, !dbg !2766
  %23 = load %struct.uv_fs_s*, %struct.uv_fs_s** %req.addr, align 8, !dbg !2766
  %loop20 = getelementptr inbounds %struct.uv_fs_s, %struct.uv_fs_s* %23, i32 0, i32 5, !dbg !2766
  store %struct.uv_loop_s* %22, %struct.uv_loop_s** %loop20, align 8, !dbg !2766
  %24 = load %struct.uv_fs_s*, %struct.uv_fs_s** %req.addr, align 8, !dbg !2766
  %path21 = getelementptr inbounds %struct.uv_fs_s, %struct.uv_fs_s* %24, i32 0, i32 9, !dbg !2766
  store i8* null, i8** %path21, align 8, !dbg !2766
  %25 = load %struct.uv_fs_s*, %struct.uv_fs_s** %req.addr, align 8, !dbg !2766
  %new_path22 = getelementptr inbounds %struct.uv_fs_s, %struct.uv_fs_s* %25, i32 0, i32 11, !dbg !2766
  store i8* null, i8** %new_path22, align 8, !dbg !2766
  %26 = load void (%struct.uv_fs_s*)*, void (%struct.uv_fs_s*)** %cb.addr, align 8, !dbg !2766
  %27 = load %struct.uv_fs_s*, %struct.uv_fs_s** %req.addr, align 8, !dbg !2766
  %cb23 = getelementptr inbounds %struct.uv_fs_s, %struct.uv_fs_s* %27, i32 0, i32 6, !dbg !2766
  store void (%struct.uv_fs_s*)* %26, void (%struct.uv_fs_s*)** %cb23, align 8, !dbg !2766
  br label %do.end24, !dbg !2766

do.end24:                                         ; preds = %if.end
  br label %do.body25, !dbg !2768

do.body25:                                        ; preds = %do.end24
  %28 = load void (%struct.uv_fs_s*)*, void (%struct.uv_fs_s*)** %cb.addr, align 8, !dbg !2769
  %cmp26 = icmp eq void (%struct.uv_fs_s*)* %28, null, !dbg !2769
  br i1 %cmp26, label %if.then27, label %if.else, !dbg !2769

if.then27:                                        ; preds = %do.body25
  %29 = load i8*, i8** %path.addr, align 8, !dbg !2773
  %30 = load %struct.uv_fs_s*, %struct.uv_fs_s** %req.addr, align 8, !dbg !2773
  %path28 = getelementptr inbounds %struct.uv_fs_s, %struct.uv_fs_s* %30, i32 0, i32 9, !dbg !2773
  store i8* %29, i8** %path28, align 8, !dbg !2773
  %31 = load i8*, i8** %new_path.addr, align 8, !dbg !2773
  %32 = load %struct.uv_fs_s*, %struct.uv_fs_s** %req.addr, align 8, !dbg !2773
  %new_path29 = getelementptr inbounds %struct.uv_fs_s, %struct.uv_fs_s* %32, i32 0, i32 11, !dbg !2773
  store i8* %31, i8** %new_path29, align 8, !dbg !2773
  br label %if.end63, !dbg !2773

if.else:                                          ; preds = %do.body25
  call void @llvm.dbg.declare(metadata i64* %path_len, metadata !2776, metadata !580), !dbg !2778
  call void @llvm.dbg.declare(metadata i64* %new_path_len, metadata !2779, metadata !580), !dbg !2778
  %33 = load i8*, i8** %path.addr, align 8, !dbg !2780
  %call = call i64 @strlen(i8* %33) #10, !dbg !2780
  %add = add i64 %call, 1, !dbg !2780
  store i64 %add, i64* %path_len, align 8, !dbg !2780
  %34 = load i8*, i8** %new_path.addr, align 8, !dbg !2780
  %call30 = call i64 @strlen(i8* %34) #10, !dbg !2782
  %add31 = add i64 %call30, 1, !dbg !2780
  store i64 %add31, i64* %new_path_len, align 8, !dbg !2780
  %35 = load i64, i64* %path_len, align 8, !dbg !2780
  %36 = load i64, i64* %new_path_len, align 8, !dbg !2780
  %add32 = add i64 %35, %36, !dbg !2780
  %call33 = call i8* @uv__malloc(i64 %add32), !dbg !2784
  %37 = load %struct.uv_fs_s*, %struct.uv_fs_s** %req.addr, align 8, !dbg !2780
  %path34 = getelementptr inbounds %struct.uv_fs_s, %struct.uv_fs_s* %37, i32 0, i32 9, !dbg !2780
  store i8* %call33, i8** %path34, align 8, !dbg !2780
  %38 = load %struct.uv_fs_s*, %struct.uv_fs_s** %req.addr, align 8, !dbg !2780
  %path35 = getelementptr inbounds %struct.uv_fs_s, %struct.uv_fs_s* %38, i32 0, i32 9, !dbg !2780
  %39 = load i8*, i8** %path35, align 8, !dbg !2780
  %cmp36 = icmp eq i8* %39, null, !dbg !2780
  br i1 %cmp36, label %if.then37, label %if.end58, !dbg !2780

if.then37:                                        ; preds = %if.else
  br label %do.body38, !dbg !2786

do.body38:                                        ; preds = %if.then37
  %40 = load %struct.uv_loop_s*, %struct.uv_loop_s** %loop.addr, align 8, !dbg !2790
  %active_reqs39 = getelementptr inbounds %struct.uv_loop_s, %struct.uv_loop_s* %40, i32 0, i32 3, !dbg !2790
  %41 = load %struct.uv_loop_s*, %struct.uv_loop_s** %loop.addr, align 8, !dbg !2790
  %active_reqs40 = getelementptr inbounds %struct.uv_loop_s, %struct.uv_loop_s* %41, i32 0, i32 3, !dbg !2790
  %arrayidx41 = getelementptr inbounds [2 x i8*], [2 x i8*]* %active_reqs40, i64 0, i64 0, !dbg !2790
  %42 = bitcast i8** %arrayidx41 to [2 x i8*]**, !dbg !2790
  %43 = load [2 x i8*]*, [2 x i8*]** %42, align 8, !dbg !2790
  %cmp42 = icmp eq [2 x i8*]* %active_reqs39, %43, !dbg !2790
  %conv = zext i1 %cmp42 to i32, !dbg !2790
  %cmp43 = icmp eq i32 %conv, 0, !dbg !2790
  br i1 %cmp43, label %cond.true, label %cond.false, !dbg !2790

cond.true:                                        ; preds = %do.body38
  br label %cond.end, !dbg !2793

cond.false:                                       ; preds = %do.body38
  call void @__assert_fail(i8* getelementptr inbounds ([113 x i8], [113 x i8]* @.str.2, i32 0, i32 0), i8* getelementptr inbounds ([66 x i8], [66 x i8]* @.str.1, i32 0, i32 0), i32 1303, i8* getelementptr inbounds ([85 x i8], [85 x i8]* @__PRETTY_FUNCTION__.uv_fs_symlink, i32 0, i32 0)) #8, !dbg !2795
  unreachable, !dbg !2795
                                                  ; No predecessors!
  br label %cond.end, !dbg !2797

cond.end:                                         ; preds = %44, %cond.true
  br label %do.body45, !dbg !2799

do.body45:                                        ; preds = %cond.end
  %45 = load %struct.uv_fs_s*, %struct.uv_fs_s** %req.addr, align 8, !dbg !2801
  %active_queue46 = getelementptr inbounds %struct.uv_fs_s, %struct.uv_fs_s* %45, i32 0, i32 2, !dbg !2801
  %arrayidx47 = getelementptr inbounds [2 x i8*], [2 x i8*]* %active_queue46, i64 0, i64 0, !dbg !2801
  %46 = bitcast i8** %arrayidx47 to [2 x i8*]**, !dbg !2801
  %47 = load [2 x i8*]*, [2 x i8*]** %46, align 8, !dbg !2801
  %48 = load %struct.uv_fs_s*, %struct.uv_fs_s** %req.addr, align 8, !dbg !2801
  %active_queue48 = getelementptr inbounds %struct.uv_fs_s, %struct.uv_fs_s* %48, i32 0, i32 2, !dbg !2801
  %arrayidx49 = getelementptr inbounds [2 x i8*], [2 x i8*]* %active_queue48, i64 0, i64 1, !dbg !2801
  %49 = bitcast i8** %arrayidx49 to [2 x i8*]**, !dbg !2801
  %50 = load [2 x i8*]*, [2 x i8*]** %49, align 8, !dbg !2801
  %arrayidx50 = getelementptr inbounds [2 x i8*], [2 x i8*]* %50, i64 0, i64 0, !dbg !2801
  %51 = bitcast i8** %arrayidx50 to [2 x i8*]**, !dbg !2801
  store [2 x i8*]* %47, [2 x i8*]** %51, align 8, !dbg !2801
  %52 = load %struct.uv_fs_s*, %struct.uv_fs_s** %req.addr, align 8, !dbg !2801
  %active_queue51 = getelementptr inbounds %struct.uv_fs_s, %struct.uv_fs_s* %52, i32 0, i32 2, !dbg !2801
  %arrayidx52 = getelementptr inbounds [2 x i8*], [2 x i8*]* %active_queue51, i64 0, i64 1, !dbg !2801
  %53 = bitcast i8** %arrayidx52 to [2 x i8*]**, !dbg !2801
  %54 = load [2 x i8*]*, [2 x i8*]** %53, align 8, !dbg !2801
  %55 = load %struct.uv_fs_s*, %struct.uv_fs_s** %req.addr, align 8, !dbg !2801
  %active_queue53 = getelementptr inbounds %struct.uv_fs_s, %struct.uv_fs_s* %55, i32 0, i32 2, !dbg !2801
  %arrayidx54 = getelementptr inbounds [2 x i8*], [2 x i8*]* %active_queue53, i64 0, i64 0, !dbg !2801
  %56 = bitcast i8** %arrayidx54 to [2 x i8*]**, !dbg !2801
  %57 = load [2 x i8*]*, [2 x i8*]** %56, align 8, !dbg !2801
  %arrayidx55 = getelementptr inbounds [2 x i8*], [2 x i8*]* %57, i64 0, i64 1, !dbg !2801
  %58 = bitcast i8** %arrayidx55 to [2 x i8*]**, !dbg !2801
  store [2 x i8*]* %54, [2 x i8*]** %58, align 8, !dbg !2801
  br label %do.end56, !dbg !2801

do.end56:                                         ; preds = %do.body45
  br label %do.end57, !dbg !2804

do.end57:                                         ; preds = %do.end56
  store i32 -12, i32* %retval, align 4, !dbg !2806
  br label %do.end74, !dbg !2806

if.end58:                                         ; preds = %if.else
  %59 = load %struct.uv_fs_s*, %struct.uv_fs_s** %req.addr, align 8, !dbg !2808
  %path59 = getelementptr inbounds %struct.uv_fs_s, %struct.uv_fs_s* %59, i32 0, i32 9, !dbg !2808
  %60 = load i8*, i8** %path59, align 8, !dbg !2808
  %61 = load i64, i64* %path_len, align 8, !dbg !2808
  %add.ptr = getelementptr inbounds i8, i8* %60, i64 %61, !dbg !2808
  %62 = load %struct.uv_fs_s*, %struct.uv_fs_s** %req.addr, align 8, !dbg !2808
  %new_path60 = getelementptr inbounds %struct.uv_fs_s, %struct.uv_fs_s* %62, i32 0, i32 11, !dbg !2808
  store i8* %add.ptr, i8** %new_path60, align 8, !dbg !2808
  %63 = load %struct.uv_fs_s*, %struct.uv_fs_s** %req.addr, align 8, !dbg !2808
  %path61 = getelementptr inbounds %struct.uv_fs_s, %struct.uv_fs_s* %63, i32 0, i32 9, !dbg !2808
  %64 = load i8*, i8** %path61, align 8, !dbg !2808
  %65 = load i8*, i8** %path.addr, align 8, !dbg !2808
  %66 = load i64, i64* %path_len, align 8, !dbg !2808
  call void @llvm.memcpy.p0i8.p0i8.i64(i8* %64, i8* %65, i64 %66, i32 1, i1 false), !dbg !2808
  %67 = load %struct.uv_fs_s*, %struct.uv_fs_s** %req.addr, align 8, !dbg !2808
  %new_path62 = getelementptr inbounds %struct.uv_fs_s, %struct.uv_fs_s* %67, i32 0, i32 11, !dbg !2808
  %68 = load i8*, i8** %new_path62, align 8, !dbg !2808
  %69 = load i8*, i8** %new_path.addr, align 8, !dbg !2808
  %70 = load i64, i64* %new_path_len, align 8, !dbg !2808
  call void @llvm.memcpy.p0i8.p0i8.i64(i8* %68, i8* %69, i64 %70, i32 1, i1 false), !dbg !2810
  br label %if.end63

if.end63:                                         ; preds = %if.end58, %if.then27
  br label %do.end64, !dbg !2812

do.end64:                                         ; preds = %if.end63
  %71 = load i32, i32* %flags.addr, align 4, !dbg !2814
  %72 = load %struct.uv_fs_s*, %struct.uv_fs_s** %req.addr, align 8, !dbg !2815
  %flags65 = getelementptr inbounds %struct.uv_fs_s, %struct.uv_fs_s* %72, i32 0, i32 13, !dbg !2816
  store i32 %71, i32* %flags65, align 4, !dbg !2817
  br label %do.body66, !dbg !2818

do.body66:                                        ; preds = %do.end64
  %73 = load void (%struct.uv_fs_s*)*, void (%struct.uv_fs_s*)** %cb.addr, align 8, !dbg !2819
  %cmp67 = icmp ne void (%struct.uv_fs_s*)* %73, null, !dbg !2819
  br i1 %cmp67, label %if.then69, label %if.else70, !dbg !2819

if.then69:                                        ; preds = %do.body66
  %74 = load %struct.uv_loop_s*, %struct.uv_loop_s** %loop.addr, align 8, !dbg !2823
  %75 = load %struct.uv_fs_s*, %struct.uv_fs_s** %req.addr, align 8, !dbg !2823
  %work_req = getelementptr inbounds %struct.uv_fs_s, %struct.uv_fs_s* %75, i32 0, i32 22, !dbg !2823
  call void @uv__work_submit(%struct.uv_loop_s* %74, %struct.uv__work* %work_req, void (%struct.uv__work*)* @uv__fs_work, void (%struct.uv__work*, i32)* @uv__fs_done), !dbg !2823
  store i32 0, i32* %retval, align 4, !dbg !2823
  br label %do.end74, !dbg !2823

if.else70:                                        ; preds = %do.body66
  %76 = load %struct.uv_fs_s*, %struct.uv_fs_s** %req.addr, align 8, !dbg !2826
  %work_req71 = getelementptr inbounds %struct.uv_fs_s, %struct.uv_fs_s* %76, i32 0, i32 22, !dbg !2826
  call void @uv__fs_work(%struct.uv__work* %work_req71), !dbg !2826
  %77 = load %struct.uv_fs_s*, %struct.uv_fs_s** %req.addr, align 8, !dbg !2826
  %result72 = getelementptr inbounds %struct.uv_fs_s, %struct.uv_fs_s* %77, i32 0, i32 7, !dbg !2826
  %78 = load i64, i64* %result72, align 8, !dbg !2826
  %conv73 = trunc i64 %78 to i32, !dbg !2826
  store i32 %conv73, i32* %retval, align 4, !dbg !2826
  br label %do.end74, !dbg !2826

do.end74:                                         ; preds = %do.end57, %if.then69, %if.else70
  %79 = load i32, i32* %retval, align 4, !dbg !2829
  ret i32 %79, !dbg !2829
}

; Function Attrs: nounwind uwtable
define i32 @uv_fs_unlink(%struct.uv_loop_s* %loop, %struct.uv_fs_s* %req, i8* %path, void (%struct.uv_fs_s*)* %cb) #0 !dbg !470 {
entry:
  %retval = alloca i32, align 4
  %loop.addr = alloca %struct.uv_loop_s*, align 8
  %req.addr = alloca %struct.uv_fs_s*, align 8
  %path.addr = alloca i8*, align 8
  %cb.addr = alloca void (%struct.uv_fs_s*)*, align 8
  store %struct.uv_loop_s* %loop, %struct.uv_loop_s** %loop.addr, align 8
  call void @llvm.dbg.declare(metadata %struct.uv_loop_s** %loop.addr, metadata !2830, metadata !580), !dbg !2831
  store %struct.uv_fs_s* %req, %struct.uv_fs_s** %req.addr, align 8
  call void @llvm.dbg.declare(metadata %struct.uv_fs_s** %req.addr, metadata !2832, metadata !580), !dbg !2833
  store i8* %path, i8** %path.addr, align 8
  call void @llvm.dbg.declare(metadata i8** %path.addr, metadata !2834, metadata !580), !dbg !2835
  store void (%struct.uv_fs_s*)* %cb, void (%struct.uv_fs_s*)** %cb.addr, align 8
  call void @llvm.dbg.declare(metadata void (%struct.uv_fs_s*)** %cb.addr, metadata !2836, metadata !580), !dbg !2837
  br label %do.body, !dbg !2838

do.body:                                          ; preds = %entry
  %0 = load %struct.uv_fs_s*, %struct.uv_fs_s** %req.addr, align 8, !dbg !2839
  %type = getelementptr inbounds %struct.uv_fs_s, %struct.uv_fs_s* %0, i32 0, i32 1, !dbg !2839
  store i32 6, i32* %type, align 8, !dbg !2839
  %1 = load void (%struct.uv_fs_s*)*, void (%struct.uv_fs_s*)** %cb.addr, align 8, !dbg !2839
  %cmp = icmp ne void (%struct.uv_fs_s*)* %1, null, !dbg !2839
  br i1 %cmp, label %if.then, label %if.end, !dbg !2839

if.then:                                          ; preds = %do.body
  br label %do.body1, !dbg !2842

do.body1:                                         ; preds = %if.then
  br label %do.body2, !dbg !2845

do.body2:                                         ; preds = %do.body1
  %2 = load %struct.uv_fs_s*, %struct.uv_fs_s** %req.addr, align 8, !dbg !2848
  %type3 = getelementptr inbounds %struct.uv_fs_s, %struct.uv_fs_s* %2, i32 0, i32 1, !dbg !2848
  store i32 6, i32* %type3, align 8, !dbg !2848
  br label %do.end, !dbg !2848

do.end:                                           ; preds = %do.body2
  br label %do.body4, !dbg !2851

do.body4:                                         ; preds = %do.end
  br label %do.body5, !dbg !2853

do.body5:                                         ; preds = %do.body4
  %3 = load %struct.uv_loop_s*, %struct.uv_loop_s** %loop.addr, align 8, !dbg !2856
  %active_reqs = getelementptr inbounds %struct.uv_loop_s, %struct.uv_loop_s* %3, i32 0, i32 3, !dbg !2856
  %4 = load %struct.uv_fs_s*, %struct.uv_fs_s** %req.addr, align 8, !dbg !2856
  %active_queue = getelementptr inbounds %struct.uv_fs_s, %struct.uv_fs_s* %4, i32 0, i32 2, !dbg !2856
  %arrayidx = getelementptr inbounds [2 x i8*], [2 x i8*]* %active_queue, i64 0, i64 0, !dbg !2856
  %5 = bitcast i8** %arrayidx to [2 x i8*]**, !dbg !2856
  store [2 x i8*]* %active_reqs, [2 x i8*]** %5, align 8, !dbg !2856
  %6 = load %struct.uv_loop_s*, %struct.uv_loop_s** %loop.addr, align 8, !dbg !2856
  %active_reqs6 = getelementptr inbounds %struct.uv_loop_s, %struct.uv_loop_s* %6, i32 0, i32 3, !dbg !2856
  %arrayidx7 = getelementptr inbounds [2 x i8*], [2 x i8*]* %active_reqs6, i64 0, i64 1, !dbg !2856
  %7 = bitcast i8** %arrayidx7 to [2 x i8*]**, !dbg !2856
  %8 = load [2 x i8*]*, [2 x i8*]** %7, align 8, !dbg !2856
  %9 = load %struct.uv_fs_s*, %struct.uv_fs_s** %req.addr, align 8, !dbg !2856
  %active_queue8 = getelementptr inbounds %struct.uv_fs_s, %struct.uv_fs_s* %9, i32 0, i32 2, !dbg !2856
  %arrayidx9 = getelementptr inbounds [2 x i8*], [2 x i8*]* %active_queue8, i64 0, i64 1, !dbg !2856
  %10 = bitcast i8** %arrayidx9 to [2 x i8*]**, !dbg !2856
  store [2 x i8*]* %8, [2 x i8*]** %10, align 8, !dbg !2856
  %11 = load %struct.uv_fs_s*, %struct.uv_fs_s** %req.addr, align 8, !dbg !2856
  %active_queue10 = getelementptr inbounds %struct.uv_fs_s, %struct.uv_fs_s* %11, i32 0, i32 2, !dbg !2856
  %12 = load %struct.uv_fs_s*, %struct.uv_fs_s** %req.addr, align 8, !dbg !2856
  %active_queue11 = getelementptr inbounds %struct.uv_fs_s, %struct.uv_fs_s* %12, i32 0, i32 2, !dbg !2856
  %arrayidx12 = getelementptr inbounds [2 x i8*], [2 x i8*]* %active_queue11, i64 0, i64 1, !dbg !2856
  %13 = bitcast i8** %arrayidx12 to [2 x i8*]**, !dbg !2856
  %14 = load [2 x i8*]*, [2 x i8*]** %13, align 8, !dbg !2856
  %arrayidx13 = getelementptr inbounds [2 x i8*], [2 x i8*]* %14, i64 0, i64 0, !dbg !2856
  %15 = bitcast i8** %arrayidx13 to [2 x i8*]**, !dbg !2856
  store [2 x i8*]* %active_queue10, [2 x i8*]** %15, align 8, !dbg !2856
  %16 = load %struct.uv_fs_s*, %struct.uv_fs_s** %req.addr, align 8, !dbg !2856
  %active_queue14 = getelementptr inbounds %struct.uv_fs_s, %struct.uv_fs_s* %16, i32 0, i32 2, !dbg !2856
  %17 = load %struct.uv_loop_s*, %struct.uv_loop_s** %loop.addr, align 8, !dbg !2856
  %active_reqs15 = getelementptr inbounds %struct.uv_loop_s, %struct.uv_loop_s* %17, i32 0, i32 3, !dbg !2856
  %arrayidx16 = getelementptr inbounds [2 x i8*], [2 x i8*]* %active_reqs15, i64 0, i64 1, !dbg !2856
  %18 = bitcast i8** %arrayidx16 to [2 x i8*]**, !dbg !2856
  store [2 x i8*]* %active_queue14, [2 x i8*]** %18, align 8, !dbg !2856
  br label %do.end17, !dbg !2856

do.end17:                                         ; preds = %do.body5
  br label %do.end18, !dbg !2859

do.end18:                                         ; preds = %do.end17
  br label %do.end19, !dbg !2861

do.end19:                                         ; preds = %do.end18
  br label %if.end, !dbg !2863

if.end:                                           ; preds = %do.end19, %do.body
  %19 = load %struct.uv_fs_s*, %struct.uv_fs_s** %req.addr, align 8, !dbg !2865
  %fs_type = getelementptr inbounds %struct.uv_fs_s, %struct.uv_fs_s* %19, i32 0, i32 4, !dbg !2865
  store i32 17, i32* %fs_type, align 8, !dbg !2865
  %20 = load %struct.uv_fs_s*, %struct.uv_fs_s** %req.addr, align 8, !dbg !2865
  %result = getelementptr inbounds %struct.uv_fs_s, %struct.uv_fs_s* %20, i32 0, i32 7, !dbg !2865
  store i64 0, i64* %result, align 8, !dbg !2865
  %21 = load %struct.uv_fs_s*, %struct.uv_fs_s** %req.addr, align 8, !dbg !2865
  %ptr = getelementptr inbounds %struct.uv_fs_s, %struct.uv_fs_s* %21, i32 0, i32 8, !dbg !2865
  store i8* null, i8** %ptr, align 8, !dbg !2865
  %22 = load %struct.uv_loop_s*, %struct.uv_loop_s** %loop.addr, align 8, !dbg !2865
  %23 = load %struct.uv_fs_s*, %struct.uv_fs_s** %req.addr, align 8, !dbg !2865
  %loop20 = getelementptr inbounds %struct.uv_fs_s, %struct.uv_fs_s* %23, i32 0, i32 5, !dbg !2865
  store %struct.uv_loop_s* %22, %struct.uv_loop_s** %loop20, align 8, !dbg !2865
  %24 = load %struct.uv_fs_s*, %struct.uv_fs_s** %req.addr, align 8, !dbg !2865
  %path21 = getelementptr inbounds %struct.uv_fs_s, %struct.uv_fs_s* %24, i32 0, i32 9, !dbg !2865
  store i8* null, i8** %path21, align 8, !dbg !2865
  %25 = load %struct.uv_fs_s*, %struct.uv_fs_s** %req.addr, align 8, !dbg !2865
  %new_path = getelementptr inbounds %struct.uv_fs_s, %struct.uv_fs_s* %25, i32 0, i32 11, !dbg !2865
  store i8* null, i8** %new_path, align 8, !dbg !2865
  %26 = load void (%struct.uv_fs_s*)*, void (%struct.uv_fs_s*)** %cb.addr, align 8, !dbg !2865
  %27 = load %struct.uv_fs_s*, %struct.uv_fs_s** %req.addr, align 8, !dbg !2865
  %cb22 = getelementptr inbounds %struct.uv_fs_s, %struct.uv_fs_s* %27, i32 0, i32 6, !dbg !2865
  store void (%struct.uv_fs_s*)* %26, void (%struct.uv_fs_s*)** %cb22, align 8, !dbg !2865
  br label %do.end23, !dbg !2865

do.end23:                                         ; preds = %if.end
  br label %do.body24, !dbg !2867

do.body24:                                        ; preds = %do.end23
  %28 = load i8*, i8** %path.addr, align 8, !dbg !2868
  %cmp25 = icmp ne i8* %28, null, !dbg !2868
  br i1 %cmp25, label %cond.true, label %cond.false, !dbg !2868

cond.true:                                        ; preds = %do.body24
  br label %cond.end, !dbg !2871

cond.false:                                       ; preds = %do.body24
  call void @__assert_fail(i8* getelementptr inbounds ([19 x i8], [19 x i8]* @.str, i32 0, i32 0), i8* getelementptr inbounds ([66 x i8], [66 x i8]* @.str.1, i32 0, i32 0), i32 1311, i8* getelementptr inbounds ([65 x i8], [65 x i8]* @__PRETTY_FUNCTION__.uv_fs_unlink, i32 0, i32 0)) #8, !dbg !2873
  unreachable, !dbg !2873
                                                  ; No predecessors!
  br label %cond.end, !dbg !2875

cond.end:                                         ; preds = %29, %cond.true
  %30 = load void (%struct.uv_fs_s*)*, void (%struct.uv_fs_s*)** %cb.addr, align 8, !dbg !2877
  %cmp26 = icmp eq void (%struct.uv_fs_s*)* %30, null, !dbg !2877
  br i1 %cmp26, label %if.then27, label %if.else, !dbg !2877

if.then27:                                        ; preds = %cond.end
  %31 = load i8*, i8** %path.addr, align 8, !dbg !2880
  %32 = load %struct.uv_fs_s*, %struct.uv_fs_s** %req.addr, align 8, !dbg !2880
  %path28 = getelementptr inbounds %struct.uv_fs_s, %struct.uv_fs_s* %32, i32 0, i32 9, !dbg !2880
  store i8* %31, i8** %path28, align 8, !dbg !2880
  br label %if.end57, !dbg !2880

if.else:                                          ; preds = %cond.end
  %33 = load i8*, i8** %path.addr, align 8, !dbg !2883
  %call = call i8* @uv__strdup(i8* %33), !dbg !2883
  %34 = load %struct.uv_fs_s*, %struct.uv_fs_s** %req.addr, align 8, !dbg !2883
  %path29 = getelementptr inbounds %struct.uv_fs_s, %struct.uv_fs_s* %34, i32 0, i32 9, !dbg !2883
  store i8* %call, i8** %path29, align 8, !dbg !2883
  %35 = load %struct.uv_fs_s*, %struct.uv_fs_s** %req.addr, align 8, !dbg !2883
  %path30 = getelementptr inbounds %struct.uv_fs_s, %struct.uv_fs_s* %35, i32 0, i32 9, !dbg !2883
  %36 = load i8*, i8** %path30, align 8, !dbg !2883
  %cmp31 = icmp eq i8* %36, null, !dbg !2883
  br i1 %cmp31, label %if.then32, label %if.end56, !dbg !2883

if.then32:                                        ; preds = %if.else
  br label %do.body33, !dbg !2886

do.body33:                                        ; preds = %if.then32
  %37 = load %struct.uv_loop_s*, %struct.uv_loop_s** %loop.addr, align 8, !dbg !2890
  %active_reqs34 = getelementptr inbounds %struct.uv_loop_s, %struct.uv_loop_s* %37, i32 0, i32 3, !dbg !2890
  %38 = load %struct.uv_loop_s*, %struct.uv_loop_s** %loop.addr, align 8, !dbg !2890
  %active_reqs35 = getelementptr inbounds %struct.uv_loop_s, %struct.uv_loop_s* %38, i32 0, i32 3, !dbg !2890
  %arrayidx36 = getelementptr inbounds [2 x i8*], [2 x i8*]* %active_reqs35, i64 0, i64 0, !dbg !2890
  %39 = bitcast i8** %arrayidx36 to [2 x i8*]**, !dbg !2890
  %40 = load [2 x i8*]*, [2 x i8*]** %39, align 8, !dbg !2890
  %cmp37 = icmp eq [2 x i8*]* %active_reqs34, %40, !dbg !2890
  %conv = zext i1 %cmp37 to i32, !dbg !2890
  %cmp38 = icmp eq i32 %conv, 0, !dbg !2890
  br i1 %cmp38, label %cond.true40, label %cond.false41, !dbg !2890

cond.true40:                                      ; preds = %do.body33
  br label %cond.end42, !dbg !2893

cond.false41:                                     ; preds = %do.body33
  call void @__assert_fail(i8* getelementptr inbounds ([113 x i8], [113 x i8]* @.str.2, i32 0, i32 0), i8* getelementptr inbounds ([66 x i8], [66 x i8]* @.str.1, i32 0, i32 0), i32 1311, i8* getelementptr inbounds ([65 x i8], [65 x i8]* @__PRETTY_FUNCTION__.uv_fs_unlink, i32 0, i32 0)) #8, !dbg !2895
  unreachable, !dbg !2895
                                                  ; No predecessors!
  br label %cond.end42, !dbg !2897

cond.end42:                                       ; preds = %41, %cond.true40
  br label %do.body43, !dbg !2899

do.body43:                                        ; preds = %cond.end42
  %42 = load %struct.uv_fs_s*, %struct.uv_fs_s** %req.addr, align 8, !dbg !2901
  %active_queue44 = getelementptr inbounds %struct.uv_fs_s, %struct.uv_fs_s* %42, i32 0, i32 2, !dbg !2901
  %arrayidx45 = getelementptr inbounds [2 x i8*], [2 x i8*]* %active_queue44, i64 0, i64 0, !dbg !2901
  %43 = bitcast i8** %arrayidx45 to [2 x i8*]**, !dbg !2901
  %44 = load [2 x i8*]*, [2 x i8*]** %43, align 8, !dbg !2901
  %45 = load %struct.uv_fs_s*, %struct.uv_fs_s** %req.addr, align 8, !dbg !2901
  %active_queue46 = getelementptr inbounds %struct.uv_fs_s, %struct.uv_fs_s* %45, i32 0, i32 2, !dbg !2901
  %arrayidx47 = getelementptr inbounds [2 x i8*], [2 x i8*]* %active_queue46, i64 0, i64 1, !dbg !2901
  %46 = bitcast i8** %arrayidx47 to [2 x i8*]**, !dbg !2901
  %47 = load [2 x i8*]*, [2 x i8*]** %46, align 8, !dbg !2901
  %arrayidx48 = getelementptr inbounds [2 x i8*], [2 x i8*]* %47, i64 0, i64 0, !dbg !2901
  %48 = bitcast i8** %arrayidx48 to [2 x i8*]**, !dbg !2901
  store [2 x i8*]* %44, [2 x i8*]** %48, align 8, !dbg !2901
  %49 = load %struct.uv_fs_s*, %struct.uv_fs_s** %req.addr, align 8, !dbg !2901
  %active_queue49 = getelementptr inbounds %struct.uv_fs_s, %struct.uv_fs_s* %49, i32 0, i32 2, !dbg !2901
  %arrayidx50 = getelementptr inbounds [2 x i8*], [2 x i8*]* %active_queue49, i64 0, i64 1, !dbg !2901
  %50 = bitcast i8** %arrayidx50 to [2 x i8*]**, !dbg !2901
  %51 = load [2 x i8*]*, [2 x i8*]** %50, align 8, !dbg !2901
  %52 = load %struct.uv_fs_s*, %struct.uv_fs_s** %req.addr, align 8, !dbg !2901
  %active_queue51 = getelementptr inbounds %struct.uv_fs_s, %struct.uv_fs_s* %52, i32 0, i32 2, !dbg !2901
  %arrayidx52 = getelementptr inbounds [2 x i8*], [2 x i8*]* %active_queue51, i64 0, i64 0, !dbg !2901
  %53 = bitcast i8** %arrayidx52 to [2 x i8*]**, !dbg !2901
  %54 = load [2 x i8*]*, [2 x i8*]** %53, align 8, !dbg !2901
  %arrayidx53 = getelementptr inbounds [2 x i8*], [2 x i8*]* %54, i64 0, i64 1, !dbg !2901
  %55 = bitcast i8** %arrayidx53 to [2 x i8*]**, !dbg !2901
  store [2 x i8*]* %51, [2 x i8*]** %55, align 8, !dbg !2901
  br label %do.end54, !dbg !2901

do.end54:                                         ; preds = %do.body43
  br label %do.end55, !dbg !2904

do.end55:                                         ; preds = %do.end54
  store i32 -12, i32* %retval, align 4, !dbg !2906
  br label %do.end67, !dbg !2906

if.end56:                                         ; preds = %if.else
  br label %if.end57

if.end57:                                         ; preds = %if.end56, %if.then27
  br label %do.end58, !dbg !2908

do.end58:                                         ; preds = %if.end57
  br label %do.body59, !dbg !2910

do.body59:                                        ; preds = %do.end58
  %56 = load void (%struct.uv_fs_s*)*, void (%struct.uv_fs_s*)** %cb.addr, align 8, !dbg !2911
  %cmp60 = icmp ne void (%struct.uv_fs_s*)* %56, null, !dbg !2911
  br i1 %cmp60, label %if.then62, label %if.else63, !dbg !2911

if.then62:                                        ; preds = %do.body59
  %57 = load %struct.uv_loop_s*, %struct.uv_loop_s** %loop.addr, align 8, !dbg !2915
  %58 = load %struct.uv_fs_s*, %struct.uv_fs_s** %req.addr, align 8, !dbg !2915
  %work_req = getelementptr inbounds %struct.uv_fs_s, %struct.uv_fs_s* %58, i32 0, i32 22, !dbg !2915
  call void @uv__work_submit(%struct.uv_loop_s* %57, %struct.uv__work* %work_req, void (%struct.uv__work*)* @uv__fs_work, void (%struct.uv__work*, i32)* @uv__fs_done), !dbg !2915
  store i32 0, i32* %retval, align 4, !dbg !2915
  br label %do.end67, !dbg !2915

if.else63:                                        ; preds = %do.body59
  %59 = load %struct.uv_fs_s*, %struct.uv_fs_s** %req.addr, align 8, !dbg !2918
  %work_req64 = getelementptr inbounds %struct.uv_fs_s, %struct.uv_fs_s* %59, i32 0, i32 22, !dbg !2918
  call void @uv__fs_work(%struct.uv__work* %work_req64), !dbg !2918
  %60 = load %struct.uv_fs_s*, %struct.uv_fs_s** %req.addr, align 8, !dbg !2918
  %result65 = getelementptr inbounds %struct.uv_fs_s, %struct.uv_fs_s* %60, i32 0, i32 7, !dbg !2918
  %61 = load i64, i64* %result65, align 8, !dbg !2918
  %conv66 = trunc i64 %61 to i32, !dbg !2918
  store i32 %conv66, i32* %retval, align 4, !dbg !2918
  br label %do.end67, !dbg !2918

do.end67:                                         ; preds = %do.end55, %if.then62, %if.else63
  %62 = load i32, i32* %retval, align 4, !dbg !2921
  ret i32 %62, !dbg !2921
}

; Function Attrs: nounwind uwtable
define i32 @uv_fs_utime(%struct.uv_loop_s* %loop, %struct.uv_fs_s* %req, i8* %path, double %atime, double %mtime, void (%struct.uv_fs_s*)* %cb) #0 !dbg !471 {
entry:
  %retval = alloca i32, align 4
  %loop.addr = alloca %struct.uv_loop_s*, align 8
  %req.addr = alloca %struct.uv_fs_s*, align 8
  %path.addr = alloca i8*, align 8
  %atime.addr = alloca double, align 8
  %mtime.addr = alloca double, align 8
  %cb.addr = alloca void (%struct.uv_fs_s*)*, align 8
  store %struct.uv_loop_s* %loop, %struct.uv_loop_s** %loop.addr, align 8
  call void @llvm.dbg.declare(metadata %struct.uv_loop_s** %loop.addr, metadata !2922, metadata !580), !dbg !2923
  store %struct.uv_fs_s* %req, %struct.uv_fs_s** %req.addr, align 8
  call void @llvm.dbg.declare(metadata %struct.uv_fs_s** %req.addr, metadata !2924, metadata !580), !dbg !2925
  store i8* %path, i8** %path.addr, align 8
  call void @llvm.dbg.declare(metadata i8** %path.addr, metadata !2926, metadata !580), !dbg !2927
  store double %atime, double* %atime.addr, align 8
  call void @llvm.dbg.declare(metadata double* %atime.addr, metadata !2928, metadata !580), !dbg !2929
  store double %mtime, double* %mtime.addr, align 8
  call void @llvm.dbg.declare(metadata double* %mtime.addr, metadata !2930, metadata !580), !dbg !2931
  store void (%struct.uv_fs_s*)* %cb, void (%struct.uv_fs_s*)** %cb.addr, align 8
  call void @llvm.dbg.declare(metadata void (%struct.uv_fs_s*)** %cb.addr, metadata !2932, metadata !580), !dbg !2933
  br label %do.body, !dbg !2934

do.body:                                          ; preds = %entry
  %0 = load %struct.uv_fs_s*, %struct.uv_fs_s** %req.addr, align 8, !dbg !2935
  %type = getelementptr inbounds %struct.uv_fs_s, %struct.uv_fs_s* %0, i32 0, i32 1, !dbg !2935
  store i32 6, i32* %type, align 8, !dbg !2935
  %1 = load void (%struct.uv_fs_s*)*, void (%struct.uv_fs_s*)** %cb.addr, align 8, !dbg !2935
  %cmp = icmp ne void (%struct.uv_fs_s*)* %1, null, !dbg !2935
  br i1 %cmp, label %if.then, label %if.end, !dbg !2935

if.then:                                          ; preds = %do.body
  br label %do.body1, !dbg !2938

do.body1:                                         ; preds = %if.then
  br label %do.body2, !dbg !2941

do.body2:                                         ; preds = %do.body1
  %2 = load %struct.uv_fs_s*, %struct.uv_fs_s** %req.addr, align 8, !dbg !2944
  %type3 = getelementptr inbounds %struct.uv_fs_s, %struct.uv_fs_s* %2, i32 0, i32 1, !dbg !2944
  store i32 6, i32* %type3, align 8, !dbg !2944
  br label %do.end, !dbg !2944

do.end:                                           ; preds = %do.body2
  br label %do.body4, !dbg !2947

do.body4:                                         ; preds = %do.end
  br label %do.body5, !dbg !2949

do.body5:                                         ; preds = %do.body4
  %3 = load %struct.uv_loop_s*, %struct.uv_loop_s** %loop.addr, align 8, !dbg !2952
  %active_reqs = getelementptr inbounds %struct.uv_loop_s, %struct.uv_loop_s* %3, i32 0, i32 3, !dbg !2952
  %4 = load %struct.uv_fs_s*, %struct.uv_fs_s** %req.addr, align 8, !dbg !2952
  %active_queue = getelementptr inbounds %struct.uv_fs_s, %struct.uv_fs_s* %4, i32 0, i32 2, !dbg !2952
  %arrayidx = getelementptr inbounds [2 x i8*], [2 x i8*]* %active_queue, i64 0, i64 0, !dbg !2952
  %5 = bitcast i8** %arrayidx to [2 x i8*]**, !dbg !2952
  store [2 x i8*]* %active_reqs, [2 x i8*]** %5, align 8, !dbg !2952
  %6 = load %struct.uv_loop_s*, %struct.uv_loop_s** %loop.addr, align 8, !dbg !2952
  %active_reqs6 = getelementptr inbounds %struct.uv_loop_s, %struct.uv_loop_s* %6, i32 0, i32 3, !dbg !2952
  %arrayidx7 = getelementptr inbounds [2 x i8*], [2 x i8*]* %active_reqs6, i64 0, i64 1, !dbg !2952
  %7 = bitcast i8** %arrayidx7 to [2 x i8*]**, !dbg !2952
  %8 = load [2 x i8*]*, [2 x i8*]** %7, align 8, !dbg !2952
  %9 = load %struct.uv_fs_s*, %struct.uv_fs_s** %req.addr, align 8, !dbg !2952
  %active_queue8 = getelementptr inbounds %struct.uv_fs_s, %struct.uv_fs_s* %9, i32 0, i32 2, !dbg !2952
  %arrayidx9 = getelementptr inbounds [2 x i8*], [2 x i8*]* %active_queue8, i64 0, i64 1, !dbg !2952
  %10 = bitcast i8** %arrayidx9 to [2 x i8*]**, !dbg !2952
  store [2 x i8*]* %8, [2 x i8*]** %10, align 8, !dbg !2952
  %11 = load %struct.uv_fs_s*, %struct.uv_fs_s** %req.addr, align 8, !dbg !2952
  %active_queue10 = getelementptr inbounds %struct.uv_fs_s, %struct.uv_fs_s* %11, i32 0, i32 2, !dbg !2952
  %12 = load %struct.uv_fs_s*, %struct.uv_fs_s** %req.addr, align 8, !dbg !2952
  %active_queue11 = getelementptr inbounds %struct.uv_fs_s, %struct.uv_fs_s* %12, i32 0, i32 2, !dbg !2952
  %arrayidx12 = getelementptr inbounds [2 x i8*], [2 x i8*]* %active_queue11, i64 0, i64 1, !dbg !2952
  %13 = bitcast i8** %arrayidx12 to [2 x i8*]**, !dbg !2952
  %14 = load [2 x i8*]*, [2 x i8*]** %13, align 8, !dbg !2952
  %arrayidx13 = getelementptr inbounds [2 x i8*], [2 x i8*]* %14, i64 0, i64 0, !dbg !2952
  %15 = bitcast i8** %arrayidx13 to [2 x i8*]**, !dbg !2952
  store [2 x i8*]* %active_queue10, [2 x i8*]** %15, align 8, !dbg !2952
  %16 = load %struct.uv_fs_s*, %struct.uv_fs_s** %req.addr, align 8, !dbg !2952
  %active_queue14 = getelementptr inbounds %struct.uv_fs_s, %struct.uv_fs_s* %16, i32 0, i32 2, !dbg !2952
  %17 = load %struct.uv_loop_s*, %struct.uv_loop_s** %loop.addr, align 8, !dbg !2952
  %active_reqs15 = getelementptr inbounds %struct.uv_loop_s, %struct.uv_loop_s* %17, i32 0, i32 3, !dbg !2952
  %arrayidx16 = getelementptr inbounds [2 x i8*], [2 x i8*]* %active_reqs15, i64 0, i64 1, !dbg !2952
  %18 = bitcast i8** %arrayidx16 to [2 x i8*]**, !dbg !2952
  store [2 x i8*]* %active_queue14, [2 x i8*]** %18, align 8, !dbg !2952
  br label %do.end17, !dbg !2952

do.end17:                                         ; preds = %do.body5
  br label %do.end18, !dbg !2955

do.end18:                                         ; preds = %do.end17
  br label %do.end19, !dbg !2957

do.end19:                                         ; preds = %do.end18
  br label %if.end, !dbg !2959

if.end:                                           ; preds = %do.end19, %do.body
  %19 = load %struct.uv_fs_s*, %struct.uv_fs_s** %req.addr, align 8, !dbg !2961
  %fs_type = getelementptr inbounds %struct.uv_fs_s, %struct.uv_fs_s* %19, i32 0, i32 4, !dbg !2961
  store i32 10, i32* %fs_type, align 8, !dbg !2961
  %20 = load %struct.uv_fs_s*, %struct.uv_fs_s** %req.addr, align 8, !dbg !2961
  %result = getelementptr inbounds %struct.uv_fs_s, %struct.uv_fs_s* %20, i32 0, i32 7, !dbg !2961
  store i64 0, i64* %result, align 8, !dbg !2961
  %21 = load %struct.uv_fs_s*, %struct.uv_fs_s** %req.addr, align 8, !dbg !2961
  %ptr = getelementptr inbounds %struct.uv_fs_s, %struct.uv_fs_s* %21, i32 0, i32 8, !dbg !2961
  store i8* null, i8** %ptr, align 8, !dbg !2961
  %22 = load %struct.uv_loop_s*, %struct.uv_loop_s** %loop.addr, align 8, !dbg !2961
  %23 = load %struct.uv_fs_s*, %struct.uv_fs_s** %req.addr, align 8, !dbg !2961
  %loop20 = getelementptr inbounds %struct.uv_fs_s, %struct.uv_fs_s* %23, i32 0, i32 5, !dbg !2961
  store %struct.uv_loop_s* %22, %struct.uv_loop_s** %loop20, align 8, !dbg !2961
  %24 = load %struct.uv_fs_s*, %struct.uv_fs_s** %req.addr, align 8, !dbg !2961
  %path21 = getelementptr inbounds %struct.uv_fs_s, %struct.uv_fs_s* %24, i32 0, i32 9, !dbg !2961
  store i8* null, i8** %path21, align 8, !dbg !2961
  %25 = load %struct.uv_fs_s*, %struct.uv_fs_s** %req.addr, align 8, !dbg !2961
  %new_path = getelementptr inbounds %struct.uv_fs_s, %struct.uv_fs_s* %25, i32 0, i32 11, !dbg !2961
  store i8* null, i8** %new_path, align 8, !dbg !2961
  %26 = load void (%struct.uv_fs_s*)*, void (%struct.uv_fs_s*)** %cb.addr, align 8, !dbg !2961
  %27 = load %struct.uv_fs_s*, %struct.uv_fs_s** %req.addr, align 8, !dbg !2961
  %cb22 = getelementptr inbounds %struct.uv_fs_s, %struct.uv_fs_s* %27, i32 0, i32 6, !dbg !2961
  store void (%struct.uv_fs_s*)* %26, void (%struct.uv_fs_s*)** %cb22, align 8, !dbg !2961
  br label %do.end23, !dbg !2961

do.end23:                                         ; preds = %if.end
  br label %do.body24, !dbg !2963

do.body24:                                        ; preds = %do.end23
  %28 = load i8*, i8** %path.addr, align 8, !dbg !2964
  %cmp25 = icmp ne i8* %28, null, !dbg !2964
  br i1 %cmp25, label %cond.true, label %cond.false, !dbg !2964

cond.true:                                        ; preds = %do.body24
  br label %cond.end, !dbg !2967

cond.false:                                       ; preds = %do.body24
  call void @__assert_fail(i8* getelementptr inbounds ([19 x i8], [19 x i8]* @.str, i32 0, i32 0), i8* getelementptr inbounds ([66 x i8], [66 x i8]* @.str.1, i32 0, i32 0), i32 1323, i8* getelementptr inbounds ([80 x i8], [80 x i8]* @__PRETTY_FUNCTION__.uv_fs_utime, i32 0, i32 0)) #8, !dbg !2969
  unreachable, !dbg !2969
                                                  ; No predecessors!
  br label %cond.end, !dbg !2971

cond.end:                                         ; preds = %29, %cond.true
  %30 = load void (%struct.uv_fs_s*)*, void (%struct.uv_fs_s*)** %cb.addr, align 8, !dbg !2973
  %cmp26 = icmp eq void (%struct.uv_fs_s*)* %30, null, !dbg !2973
  br i1 %cmp26, label %if.then27, label %if.else, !dbg !2973

if.then27:                                        ; preds = %cond.end
  %31 = load i8*, i8** %path.addr, align 8, !dbg !2976
  %32 = load %struct.uv_fs_s*, %struct.uv_fs_s** %req.addr, align 8, !dbg !2976
  %path28 = getelementptr inbounds %struct.uv_fs_s, %struct.uv_fs_s* %32, i32 0, i32 9, !dbg !2976
  store i8* %31, i8** %path28, align 8, !dbg !2976
  br label %if.end57, !dbg !2976

if.else:                                          ; preds = %cond.end
  %33 = load i8*, i8** %path.addr, align 8, !dbg !2979
  %call = call i8* @uv__strdup(i8* %33), !dbg !2979
  %34 = load %struct.uv_fs_s*, %struct.uv_fs_s** %req.addr, align 8, !dbg !2979
  %path29 = getelementptr inbounds %struct.uv_fs_s, %struct.uv_fs_s* %34, i32 0, i32 9, !dbg !2979
  store i8* %call, i8** %path29, align 8, !dbg !2979
  %35 = load %struct.uv_fs_s*, %struct.uv_fs_s** %req.addr, align 8, !dbg !2979
  %path30 = getelementptr inbounds %struct.uv_fs_s, %struct.uv_fs_s* %35, i32 0, i32 9, !dbg !2979
  %36 = load i8*, i8** %path30, align 8, !dbg !2979
  %cmp31 = icmp eq i8* %36, null, !dbg !2979
  br i1 %cmp31, label %if.then32, label %if.end56, !dbg !2979

if.then32:                                        ; preds = %if.else
  br label %do.body33, !dbg !2982

do.body33:                                        ; preds = %if.then32
  %37 = load %struct.uv_loop_s*, %struct.uv_loop_s** %loop.addr, align 8, !dbg !2986
  %active_reqs34 = getelementptr inbounds %struct.uv_loop_s, %struct.uv_loop_s* %37, i32 0, i32 3, !dbg !2986
  %38 = load %struct.uv_loop_s*, %struct.uv_loop_s** %loop.addr, align 8, !dbg !2986
  %active_reqs35 = getelementptr inbounds %struct.uv_loop_s, %struct.uv_loop_s* %38, i32 0, i32 3, !dbg !2986
  %arrayidx36 = getelementptr inbounds [2 x i8*], [2 x i8*]* %active_reqs35, i64 0, i64 0, !dbg !2986
  %39 = bitcast i8** %arrayidx36 to [2 x i8*]**, !dbg !2986
  %40 = load [2 x i8*]*, [2 x i8*]** %39, align 8, !dbg !2986
  %cmp37 = icmp eq [2 x i8*]* %active_reqs34, %40, !dbg !2986
  %conv = zext i1 %cmp37 to i32, !dbg !2986
  %cmp38 = icmp eq i32 %conv, 0, !dbg !2986
  br i1 %cmp38, label %cond.true40, label %cond.false41, !dbg !2986

cond.true40:                                      ; preds = %do.body33
  br label %cond.end42, !dbg !2989

cond.false41:                                     ; preds = %do.body33
  call void @__assert_fail(i8* getelementptr inbounds ([113 x i8], [113 x i8]* @.str.2, i32 0, i32 0), i8* getelementptr inbounds ([66 x i8], [66 x i8]* @.str.1, i32 0, i32 0), i32 1323, i8* getelementptr inbounds ([80 x i8], [80 x i8]* @__PRETTY_FUNCTION__.uv_fs_utime, i32 0, i32 0)) #8, !dbg !2991
  unreachable, !dbg !2991
                                                  ; No predecessors!
  br label %cond.end42, !dbg !2993

cond.end42:                                       ; preds = %41, %cond.true40
  br label %do.body43, !dbg !2995

do.body43:                                        ; preds = %cond.end42
  %42 = load %struct.uv_fs_s*, %struct.uv_fs_s** %req.addr, align 8, !dbg !2997
  %active_queue44 = getelementptr inbounds %struct.uv_fs_s, %struct.uv_fs_s* %42, i32 0, i32 2, !dbg !2997
  %arrayidx45 = getelementptr inbounds [2 x i8*], [2 x i8*]* %active_queue44, i64 0, i64 0, !dbg !2997
  %43 = bitcast i8** %arrayidx45 to [2 x i8*]**, !dbg !2997
  %44 = load [2 x i8*]*, [2 x i8*]** %43, align 8, !dbg !2997
  %45 = load %struct.uv_fs_s*, %struct.uv_fs_s** %req.addr, align 8, !dbg !2997
  %active_queue46 = getelementptr inbounds %struct.uv_fs_s, %struct.uv_fs_s* %45, i32 0, i32 2, !dbg !2997
  %arrayidx47 = getelementptr inbounds [2 x i8*], [2 x i8*]* %active_queue46, i64 0, i64 1, !dbg !2997
  %46 = bitcast i8** %arrayidx47 to [2 x i8*]**, !dbg !2997
  %47 = load [2 x i8*]*, [2 x i8*]** %46, align 8, !dbg !2997
  %arrayidx48 = getelementptr inbounds [2 x i8*], [2 x i8*]* %47, i64 0, i64 0, !dbg !2997
  %48 = bitcast i8** %arrayidx48 to [2 x i8*]**, !dbg !2997
  store [2 x i8*]* %44, [2 x i8*]** %48, align 8, !dbg !2997
  %49 = load %struct.uv_fs_s*, %struct.uv_fs_s** %req.addr, align 8, !dbg !2997
  %active_queue49 = getelementptr inbounds %struct.uv_fs_s, %struct.uv_fs_s* %49, i32 0, i32 2, !dbg !2997
  %arrayidx50 = getelementptr inbounds [2 x i8*], [2 x i8*]* %active_queue49, i64 0, i64 1, !dbg !2997
  %50 = bitcast i8** %arrayidx50 to [2 x i8*]**, !dbg !2997
  %51 = load [2 x i8*]*, [2 x i8*]** %50, align 8, !dbg !2997
  %52 = load %struct.uv_fs_s*, %struct.uv_fs_s** %req.addr, align 8, !dbg !2997
  %active_queue51 = getelementptr inbounds %struct.uv_fs_s, %struct.uv_fs_s* %52, i32 0, i32 2, !dbg !2997
  %arrayidx52 = getelementptr inbounds [2 x i8*], [2 x i8*]* %active_queue51, i64 0, i64 0, !dbg !2997
  %53 = bitcast i8** %arrayidx52 to [2 x i8*]**, !dbg !2997
  %54 = load [2 x i8*]*, [2 x i8*]** %53, align 8, !dbg !2997
  %arrayidx53 = getelementptr inbounds [2 x i8*], [2 x i8*]* %54, i64 0, i64 1, !dbg !2997
  %55 = bitcast i8** %arrayidx53 to [2 x i8*]**, !dbg !2997
  store [2 x i8*]* %51, [2 x i8*]** %55, align 8, !dbg !2997
  br label %do.end54, !dbg !2997

do.end54:                                         ; preds = %do.body43
  br label %do.end55, !dbg !3000

do.end55:                                         ; preds = %do.end54
  store i32 -12, i32* %retval, align 4, !dbg !3002
  br label %do.end69, !dbg !3002

if.end56:                                         ; preds = %if.else
  br label %if.end57

if.end57:                                         ; preds = %if.end56, %if.then27
  br label %do.end58, !dbg !3004

do.end58:                                         ; preds = %if.end57
  %56 = load double, double* %atime.addr, align 8, !dbg !3006
  %57 = load %struct.uv_fs_s*, %struct.uv_fs_s** %req.addr, align 8, !dbg !3007
  %atime59 = getelementptr inbounds %struct.uv_fs_s, %struct.uv_fs_s* %57, i32 0, i32 20, !dbg !3008
  store double %56, double* %atime59, align 8, !dbg !3009
  %58 = load double, double* %mtime.addr, align 8, !dbg !3010
  %59 = load %struct.uv_fs_s*, %struct.uv_fs_s** %req.addr, align 8, !dbg !3011
  %mtime60 = getelementptr inbounds %struct.uv_fs_s, %struct.uv_fs_s* %59, i32 0, i32 21, !dbg !3012
  store double %58, double* %mtime60, align 8, !dbg !3013
  br label %do.body61, !dbg !3014

do.body61:                                        ; preds = %do.end58
  %60 = load void (%struct.uv_fs_s*)*, void (%struct.uv_fs_s*)** %cb.addr, align 8, !dbg !3015
  %cmp62 = icmp ne void (%struct.uv_fs_s*)* %60, null, !dbg !3015
  br i1 %cmp62, label %if.then64, label %if.else65, !dbg !3015

if.then64:                                        ; preds = %do.body61
  %61 = load %struct.uv_loop_s*, %struct.uv_loop_s** %loop.addr, align 8, !dbg !3019
  %62 = load %struct.uv_fs_s*, %struct.uv_fs_s** %req.addr, align 8, !dbg !3019
  %work_req = getelementptr inbounds %struct.uv_fs_s, %struct.uv_fs_s* %62, i32 0, i32 22, !dbg !3019
  call void @uv__work_submit(%struct.uv_loop_s* %61, %struct.uv__work* %work_req, void (%struct.uv__work*)* @uv__fs_work, void (%struct.uv__work*, i32)* @uv__fs_done), !dbg !3019
  store i32 0, i32* %retval, align 4, !dbg !3019
  br label %do.end69, !dbg !3019

if.else65:                                        ; preds = %do.body61
  %63 = load %struct.uv_fs_s*, %struct.uv_fs_s** %req.addr, align 8, !dbg !3022
  %work_req66 = getelementptr inbounds %struct.uv_fs_s, %struct.uv_fs_s* %63, i32 0, i32 22, !dbg !3022
  call void @uv__fs_work(%struct.uv__work* %work_req66), !dbg !3022
  %64 = load %struct.uv_fs_s*, %struct.uv_fs_s** %req.addr, align 8, !dbg !3022
  %result67 = getelementptr inbounds %struct.uv_fs_s, %struct.uv_fs_s* %64, i32 0, i32 7, !dbg !3022
  %65 = load i64, i64* %result67, align 8, !dbg !3022
  %conv68 = trunc i64 %65 to i32, !dbg !3022
  store i32 %conv68, i32* %retval, align 4, !dbg !3022
  br label %do.end69, !dbg !3022

do.end69:                                         ; preds = %do.end55, %if.then64, %if.else65
  %66 = load i32, i32* %retval, align 4, !dbg !3025
  ret i32 %66, !dbg !3025
}

; Function Attrs: nounwind uwtable
define i32 @uv_fs_write(%struct.uv_loop_s* %loop, %struct.uv_fs_s* %req, i32 %file, %struct.uv_buf_t* %bufs, i32 %nbufs, i64 %off, void (%struct.uv_fs_s*)* %cb) #0 !dbg !474 {
entry:
  %retval = alloca i32, align 4
  %loop.addr = alloca %struct.uv_loop_s*, align 8
  %req.addr = alloca %struct.uv_fs_s*, align 8
  %file.addr = alloca i32, align 4
  %bufs.addr = alloca %struct.uv_buf_t*, align 8
  %nbufs.addr = alloca i32, align 4
  %off.addr = alloca i64, align 8
  %cb.addr = alloca void (%struct.uv_fs_s*)*, align 8
  store %struct.uv_loop_s* %loop, %struct.uv_loop_s** %loop.addr, align 8
  call void @llvm.dbg.declare(metadata %struct.uv_loop_s** %loop.addr, metadata !3026, metadata !580), !dbg !3027
  store %struct.uv_fs_s* %req, %struct.uv_fs_s** %req.addr, align 8
  call void @llvm.dbg.declare(metadata %struct.uv_fs_s** %req.addr, metadata !3028, metadata !580), !dbg !3029
  store i32 %file, i32* %file.addr, align 4
  call void @llvm.dbg.declare(metadata i32* %file.addr, metadata !3030, metadata !580), !dbg !3031
  store %struct.uv_buf_t* %bufs, %struct.uv_buf_t** %bufs.addr, align 8
  call void @llvm.dbg.declare(metadata %struct.uv_buf_t** %bufs.addr, metadata !3032, metadata !580), !dbg !3033
  store i32 %nbufs, i32* %nbufs.addr, align 4
  call void @llvm.dbg.declare(metadata i32* %nbufs.addr, metadata !3034, metadata !580), !dbg !3035
  store i64 %off, i64* %off.addr, align 8
  call void @llvm.dbg.declare(metadata i64* %off.addr, metadata !3036, metadata !580), !dbg !3037
  store void (%struct.uv_fs_s*)* %cb, void (%struct.uv_fs_s*)** %cb.addr, align 8
  call void @llvm.dbg.declare(metadata void (%struct.uv_fs_s*)** %cb.addr, metadata !3038, metadata !580), !dbg !3039
  %0 = load %struct.uv_buf_t*, %struct.uv_buf_t** %bufs.addr, align 8, !dbg !3040
  %cmp = icmp eq %struct.uv_buf_t* %0, null, !dbg !3042
  br i1 %cmp, label %if.then, label %lor.lhs.false, !dbg !3043

lor.lhs.false:                                    ; preds = %entry
  %1 = load i32, i32* %nbufs.addr, align 4, !dbg !3044
  %cmp1 = icmp eq i32 %1, 0, !dbg !3046
  br i1 %cmp1, label %if.then, label %if.end, !dbg !3047

if.then:                                          ; preds = %lor.lhs.false, %entry
  store i32 -22, i32* %retval, align 4, !dbg !3048
  br label %do.end77, !dbg !3048

if.end:                                           ; preds = %lor.lhs.false
  br label %do.body, !dbg !3049

do.body:                                          ; preds = %if.end
  %2 = load %struct.uv_fs_s*, %struct.uv_fs_s** %req.addr, align 8, !dbg !3050
  %type = getelementptr inbounds %struct.uv_fs_s, %struct.uv_fs_s* %2, i32 0, i32 1, !dbg !3050
  store i32 6, i32* %type, align 8, !dbg !3050
  %3 = load void (%struct.uv_fs_s*)*, void (%struct.uv_fs_s*)** %cb.addr, align 8, !dbg !3050
  %cmp2 = icmp ne void (%struct.uv_fs_s*)* %3, null, !dbg !3050
  br i1 %cmp2, label %if.then3, label %if.end23, !dbg !3050

if.then3:                                         ; preds = %do.body
  br label %do.body4, !dbg !3053

do.body4:                                         ; preds = %if.then3
  br label %do.body5, !dbg !3056

do.body5:                                         ; preds = %do.body4
  %4 = load %struct.uv_fs_s*, %struct.uv_fs_s** %req.addr, align 8, !dbg !3059
  %type6 = getelementptr inbounds %struct.uv_fs_s, %struct.uv_fs_s* %4, i32 0, i32 1, !dbg !3059
  store i32 6, i32* %type6, align 8, !dbg !3059
  br label %do.end, !dbg !3059

do.end:                                           ; preds = %do.body5
  br label %do.body7, !dbg !3062

do.body7:                                         ; preds = %do.end
  br label %do.body8, !dbg !3064

do.body8:                                         ; preds = %do.body7
  %5 = load %struct.uv_loop_s*, %struct.uv_loop_s** %loop.addr, align 8, !dbg !3067
  %active_reqs = getelementptr inbounds %struct.uv_loop_s, %struct.uv_loop_s* %5, i32 0, i32 3, !dbg !3067
  %6 = load %struct.uv_fs_s*, %struct.uv_fs_s** %req.addr, align 8, !dbg !3067
  %active_queue = getelementptr inbounds %struct.uv_fs_s, %struct.uv_fs_s* %6, i32 0, i32 2, !dbg !3067
  %arrayidx = getelementptr inbounds [2 x i8*], [2 x i8*]* %active_queue, i64 0, i64 0, !dbg !3067
  %7 = bitcast i8** %arrayidx to [2 x i8*]**, !dbg !3067
  store [2 x i8*]* %active_reqs, [2 x i8*]** %7, align 8, !dbg !3067
  %8 = load %struct.uv_loop_s*, %struct.uv_loop_s** %loop.addr, align 8, !dbg !3067
  %active_reqs9 = getelementptr inbounds %struct.uv_loop_s, %struct.uv_loop_s* %8, i32 0, i32 3, !dbg !3067
  %arrayidx10 = getelementptr inbounds [2 x i8*], [2 x i8*]* %active_reqs9, i64 0, i64 1, !dbg !3067
  %9 = bitcast i8** %arrayidx10 to [2 x i8*]**, !dbg !3067
  %10 = load [2 x i8*]*, [2 x i8*]** %9, align 8, !dbg !3067
  %11 = load %struct.uv_fs_s*, %struct.uv_fs_s** %req.addr, align 8, !dbg !3067
  %active_queue11 = getelementptr inbounds %struct.uv_fs_s, %struct.uv_fs_s* %11, i32 0, i32 2, !dbg !3067
  %arrayidx12 = getelementptr inbounds [2 x i8*], [2 x i8*]* %active_queue11, i64 0, i64 1, !dbg !3067
  %12 = bitcast i8** %arrayidx12 to [2 x i8*]**, !dbg !3067
  store [2 x i8*]* %10, [2 x i8*]** %12, align 8, !dbg !3067
  %13 = load %struct.uv_fs_s*, %struct.uv_fs_s** %req.addr, align 8, !dbg !3067
  %active_queue13 = getelementptr inbounds %struct.uv_fs_s, %struct.uv_fs_s* %13, i32 0, i32 2, !dbg !3067
  %14 = load %struct.uv_fs_s*, %struct.uv_fs_s** %req.addr, align 8, !dbg !3067
  %active_queue14 = getelementptr inbounds %struct.uv_fs_s, %struct.uv_fs_s* %14, i32 0, i32 2, !dbg !3067
  %arrayidx15 = getelementptr inbounds [2 x i8*], [2 x i8*]* %active_queue14, i64 0, i64 1, !dbg !3067
  %15 = bitcast i8** %arrayidx15 to [2 x i8*]**, !dbg !3067
  %16 = load [2 x i8*]*, [2 x i8*]** %15, align 8, !dbg !3067
  %arrayidx16 = getelementptr inbounds [2 x i8*], [2 x i8*]* %16, i64 0, i64 0, !dbg !3067
  %17 = bitcast i8** %arrayidx16 to [2 x i8*]**, !dbg !3067
  store [2 x i8*]* %active_queue13, [2 x i8*]** %17, align 8, !dbg !3067
  %18 = load %struct.uv_fs_s*, %struct.uv_fs_s** %req.addr, align 8, !dbg !3067
  %active_queue17 = getelementptr inbounds %struct.uv_fs_s, %struct.uv_fs_s* %18, i32 0, i32 2, !dbg !3067
  %19 = load %struct.uv_loop_s*, %struct.uv_loop_s** %loop.addr, align 8, !dbg !3067
  %active_reqs18 = getelementptr inbounds %struct.uv_loop_s, %struct.uv_loop_s* %19, i32 0, i32 3, !dbg !3067
  %arrayidx19 = getelementptr inbounds [2 x i8*], [2 x i8*]* %active_reqs18, i64 0, i64 1, !dbg !3067
  %20 = bitcast i8** %arrayidx19 to [2 x i8*]**, !dbg !3067
  store [2 x i8*]* %active_queue17, [2 x i8*]** %20, align 8, !dbg !3067
  br label %do.end20, !dbg !3067

do.end20:                                         ; preds = %do.body8
  br label %do.end21, !dbg !3070

do.end21:                                         ; preds = %do.end20
  br label %do.end22, !dbg !3072

do.end22:                                         ; preds = %do.end21
  br label %if.end23, !dbg !3074

if.end23:                                         ; preds = %do.end22, %do.body
  %21 = load %struct.uv_fs_s*, %struct.uv_fs_s** %req.addr, align 8, !dbg !3076
  %fs_type = getelementptr inbounds %struct.uv_fs_s, %struct.uv_fs_s* %21, i32 0, i32 4, !dbg !3076
  store i32 4, i32* %fs_type, align 8, !dbg !3076
  %22 = load %struct.uv_fs_s*, %struct.uv_fs_s** %req.addr, align 8, !dbg !3076
  %result = getelementptr inbounds %struct.uv_fs_s, %struct.uv_fs_s* %22, i32 0, i32 7, !dbg !3076
  store i64 0, i64* %result, align 8, !dbg !3076
  %23 = load %struct.uv_fs_s*, %struct.uv_fs_s** %req.addr, align 8, !dbg !3076
  %ptr = getelementptr inbounds %struct.uv_fs_s, %struct.uv_fs_s* %23, i32 0, i32 8, !dbg !3076
  store i8* null, i8** %ptr, align 8, !dbg !3076
  %24 = load %struct.uv_loop_s*, %struct.uv_loop_s** %loop.addr, align 8, !dbg !3076
  %25 = load %struct.uv_fs_s*, %struct.uv_fs_s** %req.addr, align 8, !dbg !3076
  %loop24 = getelementptr inbounds %struct.uv_fs_s, %struct.uv_fs_s* %25, i32 0, i32 5, !dbg !3076
  store %struct.uv_loop_s* %24, %struct.uv_loop_s** %loop24, align 8, !dbg !3076
  %26 = load %struct.uv_fs_s*, %struct.uv_fs_s** %req.addr, align 8, !dbg !3076
  %path = getelementptr inbounds %struct.uv_fs_s, %struct.uv_fs_s* %26, i32 0, i32 9, !dbg !3076
  store i8* null, i8** %path, align 8, !dbg !3076
  %27 = load %struct.uv_fs_s*, %struct.uv_fs_s** %req.addr, align 8, !dbg !3076
  %new_path = getelementptr inbounds %struct.uv_fs_s, %struct.uv_fs_s* %27, i32 0, i32 11, !dbg !3076
  store i8* null, i8** %new_path, align 8, !dbg !3076
  %28 = load void (%struct.uv_fs_s*)*, void (%struct.uv_fs_s*)** %cb.addr, align 8, !dbg !3076
  %29 = load %struct.uv_fs_s*, %struct.uv_fs_s** %req.addr, align 8, !dbg !3076
  %cb25 = getelementptr inbounds %struct.uv_fs_s, %struct.uv_fs_s* %29, i32 0, i32 6, !dbg !3076
  store void (%struct.uv_fs_s*)* %28, void (%struct.uv_fs_s*)** %cb25, align 8, !dbg !3076
  br label %do.end26, !dbg !3076

do.end26:                                         ; preds = %if.end23
  %30 = load i32, i32* %file.addr, align 4, !dbg !3078
  %31 = load %struct.uv_fs_s*, %struct.uv_fs_s** %req.addr, align 8, !dbg !3079
  %file27 = getelementptr inbounds %struct.uv_fs_s, %struct.uv_fs_s* %31, i32 0, i32 12, !dbg !3080
  store i32 %30, i32* %file27, align 8, !dbg !3081
  %32 = load i32, i32* %nbufs.addr, align 4, !dbg !3082
  %33 = load %struct.uv_fs_s*, %struct.uv_fs_s** %req.addr, align 8, !dbg !3083
  %nbufs28 = getelementptr inbounds %struct.uv_fs_s, %struct.uv_fs_s* %33, i32 0, i32 15, !dbg !3084
  store i32 %32, i32* %nbufs28, align 4, !dbg !3085
  %34 = load %struct.uv_fs_s*, %struct.uv_fs_s** %req.addr, align 8, !dbg !3086
  %bufsml = getelementptr inbounds %struct.uv_fs_s, %struct.uv_fs_s* %34, i32 0, i32 23, !dbg !3087
  %arraydecay = getelementptr inbounds [4 x %struct.uv_buf_t], [4 x %struct.uv_buf_t]* %bufsml, i32 0, i32 0, !dbg !3086
  %35 = load %struct.uv_fs_s*, %struct.uv_fs_s** %req.addr, align 8, !dbg !3088
  %bufs29 = getelementptr inbounds %struct.uv_fs_s, %struct.uv_fs_s* %35, i32 0, i32 16, !dbg !3089
  store %struct.uv_buf_t* %arraydecay, %struct.uv_buf_t** %bufs29, align 8, !dbg !3090
  %36 = load i32, i32* %nbufs.addr, align 4, !dbg !3091
  %conv = zext i32 %36 to i64, !dbg !3091
  %cmp30 = icmp ugt i64 %conv, 4, !dbg !3093
  br i1 %cmp30, label %if.then32, label %if.end35, !dbg !3094

if.then32:                                        ; preds = %do.end26
  %37 = load i32, i32* %nbufs.addr, align 4, !dbg !3095
  %conv33 = zext i32 %37 to i64, !dbg !3095
  %mul = mul i64 %conv33, 16, !dbg !3096
  %call = call i8* @uv__malloc(i64 %mul), !dbg !3097
  %38 = bitcast i8* %call to %struct.uv_buf_t*, !dbg !3097
  %39 = load %struct.uv_fs_s*, %struct.uv_fs_s** %req.addr, align 8, !dbg !3098
  %bufs34 = getelementptr inbounds %struct.uv_fs_s, %struct.uv_fs_s* %39, i32 0, i32 16, !dbg !3099
  store %struct.uv_buf_t* %38, %struct.uv_buf_t** %bufs34, align 8, !dbg !3100
  br label %if.end35, !dbg !3098

if.end35:                                         ; preds = %if.then32, %do.end26
  %40 = load %struct.uv_fs_s*, %struct.uv_fs_s** %req.addr, align 8, !dbg !3101
  %bufs36 = getelementptr inbounds %struct.uv_fs_s, %struct.uv_fs_s* %40, i32 0, i32 16, !dbg !3103
  %41 = load %struct.uv_buf_t*, %struct.uv_buf_t** %bufs36, align 8, !dbg !3103
  %cmp37 = icmp eq %struct.uv_buf_t* %41, null, !dbg !3104
  br i1 %cmp37, label %if.then39, label %if.end65, !dbg !3105

if.then39:                                        ; preds = %if.end35
  %42 = load void (%struct.uv_fs_s*)*, void (%struct.uv_fs_s*)** %cb.addr, align 8, !dbg !3106
  %cmp40 = icmp ne void (%struct.uv_fs_s*)* %42, null, !dbg !3109
  br i1 %cmp40, label %if.then42, label %if.end64, !dbg !3110

if.then42:                                        ; preds = %if.then39
  br label %do.body43, !dbg !3111

do.body43:                                        ; preds = %if.then42
  %43 = load %struct.uv_loop_s*, %struct.uv_loop_s** %loop.addr, align 8, !dbg !3112
  %active_reqs44 = getelementptr inbounds %struct.uv_loop_s, %struct.uv_loop_s* %43, i32 0, i32 3, !dbg !3112
  %44 = load %struct.uv_loop_s*, %struct.uv_loop_s** %loop.addr, align 8, !dbg !3112
  %active_reqs45 = getelementptr inbounds %struct.uv_loop_s, %struct.uv_loop_s* %44, i32 0, i32 3, !dbg !3112
  %arrayidx46 = getelementptr inbounds [2 x i8*], [2 x i8*]* %active_reqs45, i64 0, i64 0, !dbg !3112
  %45 = bitcast i8** %arrayidx46 to [2 x i8*]**, !dbg !3112
  %46 = load [2 x i8*]*, [2 x i8*]** %45, align 8, !dbg !3112
  %cmp47 = icmp eq [2 x i8*]* %active_reqs44, %46, !dbg !3112
  %conv48 = zext i1 %cmp47 to i32, !dbg !3112
  %cmp49 = icmp eq i32 %conv48, 0, !dbg !3112
  br i1 %cmp49, label %cond.true, label %cond.false, !dbg !3112

cond.true:                                        ; preds = %do.body43
  br label %cond.end, !dbg !3115

cond.false:                                       ; preds = %do.body43
  call void @__assert_fail(i8* getelementptr inbounds ([113 x i8], [113 x i8]* @.str.2, i32 0, i32 0), i8* getelementptr inbounds ([66 x i8], [66 x i8]* @.str.1, i32 0, i32 0), i32 1350, i8* getelementptr inbounds ([100 x i8], [100 x i8]* @__PRETTY_FUNCTION__.uv_fs_write, i32 0, i32 0)) #8, !dbg !3117
  unreachable, !dbg !3117
                                                  ; No predecessors!
  br label %cond.end, !dbg !3119

cond.end:                                         ; preds = %47, %cond.true
  br label %do.body51, !dbg !3121

do.body51:                                        ; preds = %cond.end
  %48 = load %struct.uv_fs_s*, %struct.uv_fs_s** %req.addr, align 8, !dbg !3123
  %active_queue52 = getelementptr inbounds %struct.uv_fs_s, %struct.uv_fs_s* %48, i32 0, i32 2, !dbg !3123
  %arrayidx53 = getelementptr inbounds [2 x i8*], [2 x i8*]* %active_queue52, i64 0, i64 0, !dbg !3123
  %49 = bitcast i8** %arrayidx53 to [2 x i8*]**, !dbg !3123
  %50 = load [2 x i8*]*, [2 x i8*]** %49, align 8, !dbg !3123
  %51 = load %struct.uv_fs_s*, %struct.uv_fs_s** %req.addr, align 8, !dbg !3123
  %active_queue54 = getelementptr inbounds %struct.uv_fs_s, %struct.uv_fs_s* %51, i32 0, i32 2, !dbg !3123
  %arrayidx55 = getelementptr inbounds [2 x i8*], [2 x i8*]* %active_queue54, i64 0, i64 1, !dbg !3123
  %52 = bitcast i8** %arrayidx55 to [2 x i8*]**, !dbg !3123
  %53 = load [2 x i8*]*, [2 x i8*]** %52, align 8, !dbg !3123
  %arrayidx56 = getelementptr inbounds [2 x i8*], [2 x i8*]* %53, i64 0, i64 0, !dbg !3123
  %54 = bitcast i8** %arrayidx56 to [2 x i8*]**, !dbg !3123
  store [2 x i8*]* %50, [2 x i8*]** %54, align 8, !dbg !3123
  %55 = load %struct.uv_fs_s*, %struct.uv_fs_s** %req.addr, align 8, !dbg !3123
  %active_queue57 = getelementptr inbounds %struct.uv_fs_s, %struct.uv_fs_s* %55, i32 0, i32 2, !dbg !3123
  %arrayidx58 = getelementptr inbounds [2 x i8*], [2 x i8*]* %active_queue57, i64 0, i64 1, !dbg !3123
  %56 = bitcast i8** %arrayidx58 to [2 x i8*]**, !dbg !3123
  %57 = load [2 x i8*]*, [2 x i8*]** %56, align 8, !dbg !3123
  %58 = load %struct.uv_fs_s*, %struct.uv_fs_s** %req.addr, align 8, !dbg !3123
  %active_queue59 = getelementptr inbounds %struct.uv_fs_s, %struct.uv_fs_s* %58, i32 0, i32 2, !dbg !3123
  %arrayidx60 = getelementptr inbounds [2 x i8*], [2 x i8*]* %active_queue59, i64 0, i64 0, !dbg !3123
  %59 = bitcast i8** %arrayidx60 to [2 x i8*]**, !dbg !3123
  %60 = load [2 x i8*]*, [2 x i8*]** %59, align 8, !dbg !3123
  %arrayidx61 = getelementptr inbounds [2 x i8*], [2 x i8*]* %60, i64 0, i64 1, !dbg !3123
  %61 = bitcast i8** %arrayidx61 to [2 x i8*]**, !dbg !3123
  store [2 x i8*]* %57, [2 x i8*]** %61, align 8, !dbg !3123
  br label %do.end62, !dbg !3123

do.end62:                                         ; preds = %do.body51
  br label %do.end63, !dbg !3126

do.end63:                                         ; preds = %do.end62
  br label %if.end64, !dbg !3128

if.end64:                                         ; preds = %do.end63, %if.then39
  store i32 -12, i32* %retval, align 4, !dbg !3130
  br label %do.end77, !dbg !3130

if.end65:                                         ; preds = %if.end35
  %62 = load %struct.uv_fs_s*, %struct.uv_fs_s** %req.addr, align 8, !dbg !3131
  %bufs66 = getelementptr inbounds %struct.uv_fs_s, %struct.uv_fs_s* %62, i32 0, i32 16, !dbg !3132
  %63 = load %struct.uv_buf_t*, %struct.uv_buf_t** %bufs66, align 8, !dbg !3132
  %64 = bitcast %struct.uv_buf_t* %63 to i8*, !dbg !3133
  %65 = load %struct.uv_buf_t*, %struct.uv_buf_t** %bufs.addr, align 8, !dbg !3134
  %66 = bitcast %struct.uv_buf_t* %65 to i8*, !dbg !3133
  %67 = load i32, i32* %nbufs.addr, align 4, !dbg !3135
  %conv67 = zext i32 %67 to i64, !dbg !3135
  %mul68 = mul i64 %conv67, 16, !dbg !3136
  call void @llvm.memcpy.p0i8.p0i8.i64(i8* %64, i8* %66, i64 %mul68, i32 8, i1 false), !dbg !3133
  %68 = load i64, i64* %off.addr, align 8, !dbg !3137
  %69 = load %struct.uv_fs_s*, %struct.uv_fs_s** %req.addr, align 8, !dbg !3138
  %off69 = getelementptr inbounds %struct.uv_fs_s, %struct.uv_fs_s* %69, i32 0, i32 17, !dbg !3139
  store i64 %68, i64* %off69, align 8, !dbg !3140
  br label %do.body70, !dbg !3141

do.body70:                                        ; preds = %if.end65
  %70 = load void (%struct.uv_fs_s*)*, void (%struct.uv_fs_s*)** %cb.addr, align 8, !dbg !3142
  %cmp71 = icmp ne void (%struct.uv_fs_s*)* %70, null, !dbg !3142
  br i1 %cmp71, label %if.then73, label %if.else, !dbg !3142

if.then73:                                        ; preds = %do.body70
  %71 = load %struct.uv_loop_s*, %struct.uv_loop_s** %loop.addr, align 8, !dbg !3146
  %72 = load %struct.uv_fs_s*, %struct.uv_fs_s** %req.addr, align 8, !dbg !3146
  %work_req = getelementptr inbounds %struct.uv_fs_s, %struct.uv_fs_s* %72, i32 0, i32 22, !dbg !3146
  call void @uv__work_submit(%struct.uv_loop_s* %71, %struct.uv__work* %work_req, void (%struct.uv__work*)* @uv__fs_work, void (%struct.uv__work*, i32)* @uv__fs_done), !dbg !3146
  store i32 0, i32* %retval, align 4, !dbg !3146
  br label %do.end77, !dbg !3146

if.else:                                          ; preds = %do.body70
  %73 = load %struct.uv_fs_s*, %struct.uv_fs_s** %req.addr, align 8, !dbg !3149
  %work_req74 = getelementptr inbounds %struct.uv_fs_s, %struct.uv_fs_s* %73, i32 0, i32 22, !dbg !3149
  call void @uv__fs_work(%struct.uv__work* %work_req74), !dbg !3149
  %74 = load %struct.uv_fs_s*, %struct.uv_fs_s** %req.addr, align 8, !dbg !3149
  %result75 = getelementptr inbounds %struct.uv_fs_s, %struct.uv_fs_s* %74, i32 0, i32 7, !dbg !3149
  %75 = load i64, i64* %result75, align 8, !dbg !3149
  %conv76 = trunc i64 %75 to i32, !dbg !3149
  store i32 %conv76, i32* %retval, align 4, !dbg !3149
  br label %do.end77, !dbg !3149

do.end77:                                         ; preds = %if.then, %if.end64, %if.then73, %if.else
  %76 = load i32, i32* %retval, align 4, !dbg !3152
  ret i32 %76, !dbg !3152
}

; Function Attrs: nounwind uwtable
define void @uv_fs_req_cleanup(%struct.uv_fs_s* %req) #0 !dbg !475 {
entry:
  %req.addr = alloca %struct.uv_fs_s*, align 8
  store %struct.uv_fs_s* %req, %struct.uv_fs_s** %req.addr, align 8
  call void @llvm.dbg.declare(metadata %struct.uv_fs_s** %req.addr, metadata !3153, metadata !580), !dbg !3154
  %0 = load %struct.uv_fs_s*, %struct.uv_fs_s** %req.addr, align 8, !dbg !3155
  %path = getelementptr inbounds %struct.uv_fs_s, %struct.uv_fs_s* %0, i32 0, i32 9, !dbg !3157
  %1 = load i8*, i8** %path, align 8, !dbg !3157
  %cmp = icmp ne i8* %1, null, !dbg !3158
  br i1 %cmp, label %land.lhs.true, label %if.end, !dbg !3159

land.lhs.true:                                    ; preds = %entry
  %2 = load %struct.uv_fs_s*, %struct.uv_fs_s** %req.addr, align 8, !dbg !3160
  %cb = getelementptr inbounds %struct.uv_fs_s, %struct.uv_fs_s* %2, i32 0, i32 6, !dbg !3162
  %3 = load void (%struct.uv_fs_s*)*, void (%struct.uv_fs_s*)** %cb, align 8, !dbg !3162
  %cmp1 = icmp ne void (%struct.uv_fs_s*)* %3, null, !dbg !3163
  br i1 %cmp1, label %if.then, label %lor.lhs.false, !dbg !3164

lor.lhs.false:                                    ; preds = %land.lhs.true
  %4 = load %struct.uv_fs_s*, %struct.uv_fs_s** %req.addr, align 8, !dbg !3165
  %fs_type = getelementptr inbounds %struct.uv_fs_s, %struct.uv_fs_s* %4, i32 0, i32 4, !dbg !3167
  %5 = load i32, i32* %fs_type, align 8, !dbg !3167
  %cmp2 = icmp eq i32 %5, 20, !dbg !3168
  br i1 %cmp2, label %if.then, label %if.end, !dbg !3169

if.then:                                          ; preds = %lor.lhs.false, %land.lhs.true
  %6 = load %struct.uv_fs_s*, %struct.uv_fs_s** %req.addr, align 8, !dbg !3170
  %path3 = getelementptr inbounds %struct.uv_fs_s, %struct.uv_fs_s* %6, i32 0, i32 9, !dbg !3171
  %7 = load i8*, i8** %path3, align 8, !dbg !3171
  call void @uv__free(i8* %7), !dbg !3172
  br label %if.end, !dbg !3172

if.end:                                           ; preds = %if.then, %lor.lhs.false, %entry
  %8 = load %struct.uv_fs_s*, %struct.uv_fs_s** %req.addr, align 8, !dbg !3173
  %path4 = getelementptr inbounds %struct.uv_fs_s, %struct.uv_fs_s* %8, i32 0, i32 9, !dbg !3174
  store i8* null, i8** %path4, align 8, !dbg !3175
  %9 = load %struct.uv_fs_s*, %struct.uv_fs_s** %req.addr, align 8, !dbg !3176
  %new_path = getelementptr inbounds %struct.uv_fs_s, %struct.uv_fs_s* %9, i32 0, i32 11, !dbg !3177
  store i8* null, i8** %new_path, align 8, !dbg !3178
  %10 = load %struct.uv_fs_s*, %struct.uv_fs_s** %req.addr, align 8, !dbg !3179
  %fs_type5 = getelementptr inbounds %struct.uv_fs_s, %struct.uv_fs_s* %10, i32 0, i32 4, !dbg !3181
  %11 = load i32, i32* %fs_type5, align 8, !dbg !3181
  %cmp6 = icmp eq i32 %11, 22, !dbg !3182
  br i1 %cmp6, label %land.lhs.true7, label %if.end10, !dbg !3183

land.lhs.true7:                                   ; preds = %if.end
  %12 = load %struct.uv_fs_s*, %struct.uv_fs_s** %req.addr, align 8, !dbg !3184
  %ptr = getelementptr inbounds %struct.uv_fs_s, %struct.uv_fs_s* %12, i32 0, i32 8, !dbg !3186
  %13 = load i8*, i8** %ptr, align 8, !dbg !3186
  %cmp8 = icmp ne i8* %13, null, !dbg !3187
  br i1 %cmp8, label %if.then9, label %if.end10, !dbg !3188

if.then9:                                         ; preds = %land.lhs.true7
  %14 = load %struct.uv_fs_s*, %struct.uv_fs_s** %req.addr, align 8, !dbg !3189
  call void @uv__fs_scandir_cleanup(%struct.uv_fs_s* %14), !dbg !3190
  br label %if.end10, !dbg !3190

if.end10:                                         ; preds = %if.then9, %land.lhs.true7, %if.end
  %15 = load %struct.uv_fs_s*, %struct.uv_fs_s** %req.addr, align 8, !dbg !3191
  %ptr11 = getelementptr inbounds %struct.uv_fs_s, %struct.uv_fs_s* %15, i32 0, i32 8, !dbg !3193
  %16 = load i8*, i8** %ptr11, align 8, !dbg !3193
  %17 = load %struct.uv_fs_s*, %struct.uv_fs_s** %req.addr, align 8, !dbg !3194
  %statbuf = getelementptr inbounds %struct.uv_fs_s, %struct.uv_fs_s* %17, i32 0, i32 10, !dbg !3195
  %18 = bitcast %struct.uv_stat_t* %statbuf to i8*, !dbg !3196
  %cmp12 = icmp ne i8* %16, %18, !dbg !3197
  br i1 %cmp12, label %if.then13, label %if.end15, !dbg !3198

if.then13:                                        ; preds = %if.end10
  %19 = load %struct.uv_fs_s*, %struct.uv_fs_s** %req.addr, align 8, !dbg !3199
  %ptr14 = getelementptr inbounds %struct.uv_fs_s, %struct.uv_fs_s* %19, i32 0, i32 8, !dbg !3200
  %20 = load i8*, i8** %ptr14, align 8, !dbg !3200
  call void @uv__free(i8* %20), !dbg !3201
  br label %if.end15, !dbg !3201

if.end15:                                         ; preds = %if.then13, %if.end10
  %21 = load %struct.uv_fs_s*, %struct.uv_fs_s** %req.addr, align 8, !dbg !3202
  %ptr16 = getelementptr inbounds %struct.uv_fs_s, %struct.uv_fs_s* %21, i32 0, i32 8, !dbg !3203
  store i8* null, i8** %ptr16, align 8, !dbg !3204
  ret void, !dbg !3205
}

declare void @uv__free(i8*) #3

declare void @uv__fs_scandir_cleanup(%struct.uv_fs_s*) #3

; Function Attrs: nounwind readnone
declare i32* @__errno_location() #6

; Function Attrs: nounwind
declare i32 @access(i8*, i32) #7

; Function Attrs: nounwind
declare i32 @chmod(i8*, i32) #7

; Function Attrs: nounwind
declare i32 @chown(i8*, i32, i32) #7

declare i32 @close(i32) #3

; Function Attrs: nounwind
declare i32 @fchmod(i32, i32) #7

; Function Attrs: nounwind
declare i32 @fchown(i32, i32, i32) #7

; Function Attrs: nounwind uwtable
define internal i64 @uv__fs_fdatasync(%struct.uv_fs_s* %req) #0 !dbg !477 {
entry:
  %req.addr = alloca %struct.uv_fs_s*, align 8
  store %struct.uv_fs_s* %req, %struct.uv_fs_s** %req.addr, align 8
  call void @llvm.dbg.declare(metadata %struct.uv_fs_s** %req.addr, metadata !3206, metadata !580), !dbg !3207
  %0 = load %struct.uv_fs_s*, %struct.uv_fs_s** %req.addr, align 8, !dbg !3208
  %file = getelementptr inbounds %struct.uv_fs_s, %struct.uv_fs_s* %0, i32 0, i32 12, !dbg !3209
  %1 = load i32, i32* %file, align 8, !dbg !3209
  %call = call i32 @fdatasync(i32 %1), !dbg !3210
  %conv = sext i32 %call to i64, !dbg !3210
  ret i64 %conv, !dbg !3211
}

; Function Attrs: nounwind uwtable
define internal i32 @uv__fs_fstat(i32 %fd, %struct.uv_stat_t* %buf) #0 !dbg !480 {
entry:
  %fd.addr = alloca i32, align 4
  %buf.addr = alloca %struct.uv_stat_t*, align 8
  %pbuf = alloca %struct.stat, align 8
  %ret = alloca i32, align 4
  store i32 %fd, i32* %fd.addr, align 4
  call void @llvm.dbg.declare(metadata i32* %fd.addr, metadata !3212, metadata !580), !dbg !3213
  store %struct.uv_stat_t* %buf, %struct.uv_stat_t** %buf.addr, align 8
  call void @llvm.dbg.declare(metadata %struct.uv_stat_t** %buf.addr, metadata !3214, metadata !580), !dbg !3215
  call void @llvm.dbg.declare(metadata %struct.stat* %pbuf, metadata !3216, metadata !580), !dbg !3217
  call void @llvm.dbg.declare(metadata i32* %ret, metadata !3218, metadata !580), !dbg !3219
  %0 = load i32, i32* %fd.addr, align 4, !dbg !3220
  %call = call i32 @fstat64(i32 %0, %struct.stat* %pbuf) #9, !dbg !3221
  store i32 %call, i32* %ret, align 4, !dbg !3222
  %1 = load i32, i32* %ret, align 4, !dbg !3223
  %cmp = icmp eq i32 %1, 0, !dbg !3225
  br i1 %cmp, label %if.then, label %if.end, !dbg !3226

if.then:                                          ; preds = %entry
  %2 = load %struct.uv_stat_t*, %struct.uv_stat_t** %buf.addr, align 8, !dbg !3227
  call void @uv__to_stat(%struct.stat* %pbuf, %struct.uv_stat_t* %2), !dbg !3228
  br label %if.end, !dbg !3228

if.end:                                           ; preds = %if.then, %entry
  %3 = load i32, i32* %ret, align 4, !dbg !3229
  ret i32 %3, !dbg !3230
}

; Function Attrs: nounwind uwtable
define internal i64 @uv__fs_fsync(%struct.uv_fs_s* %req) #0 !dbg !522 {
entry:
  %req.addr = alloca %struct.uv_fs_s*, align 8
  store %struct.uv_fs_s* %req, %struct.uv_fs_s** %req.addr, align 8
  call void @llvm.dbg.declare(metadata %struct.uv_fs_s** %req.addr, metadata !3231, metadata !580), !dbg !3232
  %0 = load %struct.uv_fs_s*, %struct.uv_fs_s** %req.addr, align 8, !dbg !3233
  %file = getelementptr inbounds %struct.uv_fs_s, %struct.uv_fs_s* %0, i32 0, i32 12, !dbg !3234
  %1 = load i32, i32* %file, align 8, !dbg !3234
  %call = call i32 @fsync(i32 %1), !dbg !3235
  %conv = sext i32 %call to i64, !dbg !3235
  ret i64 %conv, !dbg !3236
}

; Function Attrs: nounwind
declare i32 @ftruncate64(i32, i64) #7

; Function Attrs: nounwind uwtable
define internal i64 @uv__fs_futime(%struct.uv_fs_s* %req) #0 !dbg !523 {
entry:
  %retval = alloca i64, align 8
  %req.addr = alloca %struct.uv_fs_s*, align 8
  %ts = alloca [2 x %struct.timespec], align 16
  %tv = alloca [2 x %struct.timeval], align 16
  %path = alloca [27 x i8], align 16
  %r = alloca i32, align 4
  store %struct.uv_fs_s* %req, %struct.uv_fs_s** %req.addr, align 8
  call void @llvm.dbg.declare(metadata %struct.uv_fs_s** %req.addr, metadata !3237, metadata !580), !dbg !3238
  call void @llvm.dbg.declare(metadata [2 x %struct.timespec]* %ts, metadata !3239, metadata !580), !dbg !3241
  call void @llvm.dbg.declare(metadata [2 x %struct.timeval]* %tv, metadata !3242, metadata !580), !dbg !3250
  call void @llvm.dbg.declare(metadata [27 x i8]* %path, metadata !3251, metadata !580), !dbg !3255
  call void @llvm.dbg.declare(metadata i32* %r, metadata !3256, metadata !580), !dbg !3257
  %0 = load i32, i32* @uv__fs_futime.no_utimesat, align 4, !dbg !3258
  %tobool = icmp ne i32 %0, 0, !dbg !3258
  br i1 %tobool, label %if.then, label %if.end, !dbg !3260

if.then:                                          ; preds = %entry
  br label %skip, !dbg !3261

if.end:                                           ; preds = %entry
  %1 = load %struct.uv_fs_s*, %struct.uv_fs_s** %req.addr, align 8, !dbg !3262
  %atime = getelementptr inbounds %struct.uv_fs_s, %struct.uv_fs_s* %1, i32 0, i32 20, !dbg !3263
  %2 = load double, double* %atime, align 8, !dbg !3263
  %conv = fptosi double %2 to i64, !dbg !3262
  %arrayidx = getelementptr inbounds [2 x %struct.timespec], [2 x %struct.timespec]* %ts, i64 0, i64 0, !dbg !3264
  %tv_sec = getelementptr inbounds %struct.timespec, %struct.timespec* %arrayidx, i32 0, i32 0, !dbg !3265
  store i64 %conv, i64* %tv_sec, align 16, !dbg !3266
  %3 = load %struct.uv_fs_s*, %struct.uv_fs_s** %req.addr, align 8, !dbg !3267
  %atime1 = getelementptr inbounds %struct.uv_fs_s, %struct.uv_fs_s* %3, i32 0, i32 20, !dbg !3268
  %4 = load double, double* %atime1, align 8, !dbg !3268
  %mul = fmul double %4, 1.000000e+06, !dbg !3269
  %conv2 = fptoui double %mul to i64, !dbg !3270
  %rem = urem i64 %conv2, 1000000, !dbg !3271
  %mul3 = mul i64 %rem, 1000, !dbg !3272
  %arrayidx4 = getelementptr inbounds [2 x %struct.timespec], [2 x %struct.timespec]* %ts, i64 0, i64 0, !dbg !3273
  %tv_nsec = getelementptr inbounds %struct.timespec, %struct.timespec* %arrayidx4, i32 0, i32 1, !dbg !3274
  store i64 %mul3, i64* %tv_nsec, align 8, !dbg !3275
  %5 = load %struct.uv_fs_s*, %struct.uv_fs_s** %req.addr, align 8, !dbg !3276
  %mtime = getelementptr inbounds %struct.uv_fs_s, %struct.uv_fs_s* %5, i32 0, i32 21, !dbg !3277
  %6 = load double, double* %mtime, align 8, !dbg !3277
  %conv5 = fptosi double %6 to i64, !dbg !3276
  %arrayidx6 = getelementptr inbounds [2 x %struct.timespec], [2 x %struct.timespec]* %ts, i64 0, i64 1, !dbg !3278
  %tv_sec7 = getelementptr inbounds %struct.timespec, %struct.timespec* %arrayidx6, i32 0, i32 0, !dbg !3279
  store i64 %conv5, i64* %tv_sec7, align 16, !dbg !3280
  %7 = load %struct.uv_fs_s*, %struct.uv_fs_s** %req.addr, align 8, !dbg !3281
  %mtime8 = getelementptr inbounds %struct.uv_fs_s, %struct.uv_fs_s* %7, i32 0, i32 21, !dbg !3282
  %8 = load double, double* %mtime8, align 8, !dbg !3282
  %mul9 = fmul double %8, 1.000000e+06, !dbg !3283
  %conv10 = fptoui double %mul9 to i64, !dbg !3284
  %rem11 = urem i64 %conv10, 1000000, !dbg !3285
  %mul12 = mul i64 %rem11, 1000, !dbg !3286
  %arrayidx13 = getelementptr inbounds [2 x %struct.timespec], [2 x %struct.timespec]* %ts, i64 0, i64 1, !dbg !3287
  %tv_nsec14 = getelementptr inbounds %struct.timespec, %struct.timespec* %arrayidx13, i32 0, i32 1, !dbg !3288
  store i64 %mul12, i64* %tv_nsec14, align 8, !dbg !3289
  %9 = load %struct.uv_fs_s*, %struct.uv_fs_s** %req.addr, align 8, !dbg !3290
  %file = getelementptr inbounds %struct.uv_fs_s, %struct.uv_fs_s* %9, i32 0, i32 12, !dbg !3291
  %10 = load i32, i32* %file, align 8, !dbg !3291
  %arraydecay = getelementptr inbounds [2 x %struct.timespec], [2 x %struct.timespec]* %ts, i32 0, i32 0, !dbg !3292
  %call = call i32 @uv__utimesat(i32 %10, i8* null, %struct.timespec* %arraydecay, i32 0), !dbg !3293
  store i32 %call, i32* %r, align 4, !dbg !3294
  %11 = load i32, i32* %r, align 4, !dbg !3295
  %cmp = icmp eq i32 %11, 0, !dbg !3297
  br i1 %cmp, label %if.then16, label %if.end18, !dbg !3298

if.then16:                                        ; preds = %if.end
  %12 = load i32, i32* %r, align 4, !dbg !3299
  %conv17 = sext i32 %12 to i64, !dbg !3299
  store i64 %conv17, i64* %retval, align 8, !dbg !3300
  br label %return, !dbg !3300

if.end18:                                         ; preds = %if.end
  %call19 = call i32* @__errno_location() #1, !dbg !3301
  %13 = load i32, i32* %call19, align 4, !dbg !3301
  %cmp20 = icmp ne i32 %13, 38, !dbg !3303
  br i1 %cmp20, label %if.then22, label %if.end24, !dbg !3304

if.then22:                                        ; preds = %if.end18
  %14 = load i32, i32* %r, align 4, !dbg !3305
  %conv23 = sext i32 %14 to i64, !dbg !3305
  store i64 %conv23, i64* %retval, align 8, !dbg !3306
  br label %return, !dbg !3306

if.end24:                                         ; preds = %if.end18
  store i32 1, i32* @uv__fs_futime.no_utimesat, align 4, !dbg !3307
  br label %skip, !dbg !3308

skip:                                             ; preds = %if.end24, %if.then
  %15 = load %struct.uv_fs_s*, %struct.uv_fs_s** %req.addr, align 8, !dbg !3309
  %atime25 = getelementptr inbounds %struct.uv_fs_s, %struct.uv_fs_s* %15, i32 0, i32 20, !dbg !3310
  %16 = load double, double* %atime25, align 8, !dbg !3310
  %conv26 = fptosi double %16 to i64, !dbg !3309
  %arrayidx27 = getelementptr inbounds [2 x %struct.timeval], [2 x %struct.timeval]* %tv, i64 0, i64 0, !dbg !3311
  %tv_sec28 = getelementptr inbounds %struct.timeval, %struct.timeval* %arrayidx27, i32 0, i32 0, !dbg !3312
  store i64 %conv26, i64* %tv_sec28, align 16, !dbg !3313
  %17 = load %struct.uv_fs_s*, %struct.uv_fs_s** %req.addr, align 8, !dbg !3314
  %atime29 = getelementptr inbounds %struct.uv_fs_s, %struct.uv_fs_s* %17, i32 0, i32 20, !dbg !3315
  %18 = load double, double* %atime29, align 8, !dbg !3315
  %mul30 = fmul double %18, 1.000000e+06, !dbg !3316
  %conv31 = fptoui double %mul30 to i64, !dbg !3317
  %rem32 = urem i64 %conv31, 1000000, !dbg !3318
  %arrayidx33 = getelementptr inbounds [2 x %struct.timeval], [2 x %struct.timeval]* %tv, i64 0, i64 0, !dbg !3319
  %tv_usec = getelementptr inbounds %struct.timeval, %struct.timeval* %arrayidx33, i32 0, i32 1, !dbg !3320
  store i64 %rem32, i64* %tv_usec, align 8, !dbg !3321
  %19 = load %struct.uv_fs_s*, %struct.uv_fs_s** %req.addr, align 8, !dbg !3322
  %mtime34 = getelementptr inbounds %struct.uv_fs_s, %struct.uv_fs_s* %19, i32 0, i32 21, !dbg !3323
  %20 = load double, double* %mtime34, align 8, !dbg !3323
  %conv35 = fptosi double %20 to i64, !dbg !3322
  %arrayidx36 = getelementptr inbounds [2 x %struct.timeval], [2 x %struct.timeval]* %tv, i64 0, i64 1, !dbg !3324
  %tv_sec37 = getelementptr inbounds %struct.timeval, %struct.timeval* %arrayidx36, i32 0, i32 0, !dbg !3325
  store i64 %conv35, i64* %tv_sec37, align 16, !dbg !3326
  %21 = load %struct.uv_fs_s*, %struct.uv_fs_s** %req.addr, align 8, !dbg !3327
  %mtime38 = getelementptr inbounds %struct.uv_fs_s, %struct.uv_fs_s* %21, i32 0, i32 21, !dbg !3328
  %22 = load double, double* %mtime38, align 8, !dbg !3328
  %mul39 = fmul double %22, 1.000000e+06, !dbg !3329
  %conv40 = fptoui double %mul39 to i64, !dbg !3330
  %rem41 = urem i64 %conv40, 1000000, !dbg !3331
  %arrayidx42 = getelementptr inbounds [2 x %struct.timeval], [2 x %struct.timeval]* %tv, i64 0, i64 1, !dbg !3332
  %tv_usec43 = getelementptr inbounds %struct.timeval, %struct.timeval* %arrayidx42, i32 0, i32 1, !dbg !3333
  store i64 %rem41, i64* %tv_usec43, align 8, !dbg !3334
  %arraydecay44 = getelementptr inbounds [27 x i8], [27 x i8]* %path, i32 0, i32 0, !dbg !3335
  %23 = load %struct.uv_fs_s*, %struct.uv_fs_s** %req.addr, align 8, !dbg !3336
  %file45 = getelementptr inbounds %struct.uv_fs_s, %struct.uv_fs_s* %23, i32 0, i32 12, !dbg !3337
  %24 = load i32, i32* %file45, align 8, !dbg !3337
  %call46 = call i32 (i8*, i64, i8*, ...) @snprintf(i8* %arraydecay44, i64 27, i8* getelementptr inbounds ([17 x i8], [17 x i8]* @.str.3, i32 0, i32 0), i32 %24) #9, !dbg !3338
  %arraydecay47 = getelementptr inbounds [27 x i8], [27 x i8]* %path, i32 0, i32 0, !dbg !3339
  %arraydecay48 = getelementptr inbounds [2 x %struct.timeval], [2 x %struct.timeval]* %tv, i32 0, i32 0, !dbg !3340
  %call49 = call i32 @utimes(i8* %arraydecay47, %struct.timeval* %arraydecay48) #9, !dbg !3341
  store i32 %call49, i32* %r, align 4, !dbg !3342
  %25 = load i32, i32* %r, align 4, !dbg !3343
  %cmp50 = icmp eq i32 %25, 0, !dbg !3345
  br i1 %cmp50, label %if.then52, label %if.end54, !dbg !3346

if.then52:                                        ; preds = %skip
  %26 = load i32, i32* %r, align 4, !dbg !3347
  %conv53 = sext i32 %26 to i64, !dbg !3347
  store i64 %conv53, i64* %retval, align 8, !dbg !3348
  br label %return, !dbg !3348

if.end54:                                         ; preds = %skip
  %call55 = call i32* @__errno_location() #1, !dbg !3349
  %27 = load i32, i32* %call55, align 4, !dbg !3349
  switch i32 %27, label %sw.epilog [
    i32 2, label %sw.bb
    i32 13, label %sw.bb65
    i32 20, label %sw.bb65
  ], !dbg !3350

sw.bb:                                            ; preds = %if.end54
  %28 = load %struct.uv_fs_s*, %struct.uv_fs_s** %req.addr, align 8, !dbg !3351
  %file56 = getelementptr inbounds %struct.uv_fs_s, %struct.uv_fs_s* %28, i32 0, i32 12, !dbg !3354
  %29 = load i32, i32* %file56, align 8, !dbg !3354
  %call57 = call i32 (i32, i32, ...) @fcntl(i32 %29, i32 3), !dbg !3355
  %cmp58 = icmp eq i32 %call57, -1, !dbg !3356
  br i1 %cmp58, label %land.lhs.true, label %if.end64, !dbg !3357

land.lhs.true:                                    ; preds = %sw.bb
  %call60 = call i32* @__errno_location() #1, !dbg !3358
  %30 = load i32, i32* %call60, align 4, !dbg !3358
  %cmp61 = icmp eq i32 %30, 9, !dbg !3360
  br i1 %cmp61, label %if.then63, label %if.end64, !dbg !3361

if.then63:                                        ; preds = %land.lhs.true
  br label %sw.epilog, !dbg !3362

if.end64:                                         ; preds = %land.lhs.true, %sw.bb
  br label %sw.bb65, !dbg !3363

sw.bb65:                                          ; preds = %if.end54, %if.end54, %if.end64
  %call66 = call i32* @__errno_location() #1, !dbg !3365
  store i32 38, i32* %call66, align 4, !dbg !3366
  br label %sw.epilog, !dbg !3367

sw.epilog:                                        ; preds = %if.end54, %sw.bb65, %if.then63
  %31 = load i32, i32* %r, align 4, !dbg !3368
  %conv67 = sext i32 %31 to i64, !dbg !3368
  store i64 %conv67, i64* %retval, align 8, !dbg !3369
  br label %return, !dbg !3369

return:                                           ; preds = %sw.epilog, %if.then52, %if.then22, %if.then16
  %32 = load i64, i64* %retval, align 8, !dbg !3370
  ret i64 %32, !dbg !3370
}

; Function Attrs: nounwind uwtable
define internal i32 @uv__fs_lstat(i8* %path, %struct.uv_stat_t* %buf) #0 !dbg !524 {
entry:
  %path.addr = alloca i8*, align 8
  %buf.addr = alloca %struct.uv_stat_t*, align 8
  %pbuf = alloca %struct.stat, align 8
  %ret = alloca i32, align 4
  store i8* %path, i8** %path.addr, align 8
  call void @llvm.dbg.declare(metadata i8** %path.addr, metadata !3371, metadata !580), !dbg !3372
  store %struct.uv_stat_t* %buf, %struct.uv_stat_t** %buf.addr, align 8
  call void @llvm.dbg.declare(metadata %struct.uv_stat_t** %buf.addr, metadata !3373, metadata !580), !dbg !3374
  call void @llvm.dbg.declare(metadata %struct.stat* %pbuf, metadata !3375, metadata !580), !dbg !3376
  call void @llvm.dbg.declare(metadata i32* %ret, metadata !3377, metadata !580), !dbg !3378
  %0 = load i8*, i8** %path.addr, align 8, !dbg !3379
  %call = call i32 @lstat64(i8* %0, %struct.stat* %pbuf) #9, !dbg !3380
  store i32 %call, i32* %ret, align 4, !dbg !3381
  %1 = load i32, i32* %ret, align 4, !dbg !3382
  %cmp = icmp eq i32 %1, 0, !dbg !3384
  br i1 %cmp, label %if.then, label %if.end, !dbg !3385

if.then:                                          ; preds = %entry
  %2 = load %struct.uv_stat_t*, %struct.uv_stat_t** %buf.addr, align 8, !dbg !3386
  call void @uv__to_stat(%struct.stat* %pbuf, %struct.uv_stat_t* %2), !dbg !3387
  br label %if.end, !dbg !3387

if.end:                                           ; preds = %if.then, %entry
  %3 = load i32, i32* %ret, align 4, !dbg !3388
  ret i32 %3, !dbg !3389
}

; Function Attrs: nounwind
declare i32 @link(i8*, i8*) #7

; Function Attrs: nounwind
declare i32 @mkdir(i8*, i32) #7

; Function Attrs: nounwind uwtable
define internal i64 @uv__fs_mkdtemp(%struct.uv_fs_s* %req) #0 !dbg !527 {
entry:
  %req.addr = alloca %struct.uv_fs_s*, align 8
  store %struct.uv_fs_s* %req, %struct.uv_fs_s** %req.addr, align 8
  call void @llvm.dbg.declare(metadata %struct.uv_fs_s** %req.addr, metadata !3390, metadata !580), !dbg !3391
  %0 = load %struct.uv_fs_s*, %struct.uv_fs_s** %req.addr, align 8, !dbg !3392
  %path = getelementptr inbounds %struct.uv_fs_s, %struct.uv_fs_s* %0, i32 0, i32 9, !dbg !3393
  %1 = load i8*, i8** %path, align 8, !dbg !3393
  %call = call i8* @mkdtemp(i8* %1) #9, !dbg !3394
  %tobool = icmp ne i8* %call, null, !dbg !3394
  %cond = select i1 %tobool, i32 0, i32 -1, !dbg !3394
  %conv = sext i32 %cond to i64, !dbg !3394
  ret i64 %conv, !dbg !3395
}

; Function Attrs: nounwind uwtable
define internal i64 @uv__fs_open(%struct.uv_fs_s* %req) #0 !dbg !528 {
entry:
  %retval = alloca i64, align 8
  %req.addr = alloca %struct.uv_fs_s*, align 8
  %r = alloca i32, align 4
  store %struct.uv_fs_s* %req, %struct.uv_fs_s** %req.addr, align 8
  call void @llvm.dbg.declare(metadata %struct.uv_fs_s** %req.addr, metadata !3396, metadata !580), !dbg !3397
  call void @llvm.dbg.declare(metadata i32* %r, metadata !3398, metadata !580), !dbg !3399
  %0 = load i32, i32* @uv__fs_open.no_cloexec_support, align 4, !dbg !3400
  %cmp = icmp eq i32 %0, 0, !dbg !3402
  br i1 %cmp, label %if.then, label %if.end9, !dbg !3403

if.then:                                          ; preds = %entry
  %1 = load %struct.uv_fs_s*, %struct.uv_fs_s** %req.addr, align 8, !dbg !3404
  %path = getelementptr inbounds %struct.uv_fs_s, %struct.uv_fs_s* %1, i32 0, i32 9, !dbg !3406
  %2 = load i8*, i8** %path, align 8, !dbg !3406
  %3 = load %struct.uv_fs_s*, %struct.uv_fs_s** %req.addr, align 8, !dbg !3407
  %flags = getelementptr inbounds %struct.uv_fs_s, %struct.uv_fs_s* %3, i32 0, i32 13, !dbg !3408
  %4 = load i32, i32* %flags, align 4, !dbg !3408
  %or = or i32 %4, 524288, !dbg !3409
  %5 = load %struct.uv_fs_s*, %struct.uv_fs_s** %req.addr, align 8, !dbg !3410
  %mode = getelementptr inbounds %struct.uv_fs_s, %struct.uv_fs_s* %5, i32 0, i32 14, !dbg !3411
  %6 = load i32, i32* %mode, align 8, !dbg !3411
  %call = call i32 (i8*, i32, ...) @open64(i8* %2, i32 %or, i32 %6), !dbg !3412
  store i32 %call, i32* %r, align 4, !dbg !3413
  %7 = load i32, i32* %r, align 4, !dbg !3414
  %cmp1 = icmp sge i32 %7, 0, !dbg !3416
  br i1 %cmp1, label %if.then2, label %if.end, !dbg !3417

if.then2:                                         ; preds = %if.then
  %8 = load i32, i32* %r, align 4, !dbg !3418
  %conv = sext i32 %8 to i64, !dbg !3418
  store i64 %conv, i64* %retval, align 8, !dbg !3419
  br label %return, !dbg !3419

if.end:                                           ; preds = %if.then
  %call3 = call i32* @__errno_location() #1, !dbg !3420
  %9 = load i32, i32* %call3, align 4, !dbg !3420
  %cmp4 = icmp ne i32 %9, 22, !dbg !3422
  br i1 %cmp4, label %if.then6, label %if.end8, !dbg !3423

if.then6:                                         ; preds = %if.end
  %10 = load i32, i32* %r, align 4, !dbg !3424
  %conv7 = sext i32 %10 to i64, !dbg !3424
  store i64 %conv7, i64* %retval, align 8, !dbg !3425
  br label %return, !dbg !3425

if.end8:                                          ; preds = %if.end
  store i32 1, i32* @uv__fs_open.no_cloexec_support, align 4, !dbg !3426
  br label %if.end9, !dbg !3427

if.end9:                                          ; preds = %if.end8, %entry
  %11 = load %struct.uv_fs_s*, %struct.uv_fs_s** %req.addr, align 8, !dbg !3428
  %cb = getelementptr inbounds %struct.uv_fs_s, %struct.uv_fs_s* %11, i32 0, i32 6, !dbg !3430
  %12 = load void (%struct.uv_fs_s*)*, void (%struct.uv_fs_s*)** %cb, align 8, !dbg !3430
  %cmp10 = icmp ne void (%struct.uv_fs_s*)* %12, null, !dbg !3431
  br i1 %cmp10, label %if.then12, label %if.end13, !dbg !3432

if.then12:                                        ; preds = %if.end9
  %13 = load %struct.uv_fs_s*, %struct.uv_fs_s** %req.addr, align 8, !dbg !3433
  %loop = getelementptr inbounds %struct.uv_fs_s, %struct.uv_fs_s* %13, i32 0, i32 5, !dbg !3434
  %14 = load %struct.uv_loop_s*, %struct.uv_loop_s** %loop, align 8, !dbg !3434
  %cloexec_lock = getelementptr inbounds %struct.uv_loop_s, %struct.uv_loop_s* %14, i32 0, i32 15, !dbg !3435
  call void @uv_rwlock_rdlock(%union.pthread_rwlock_t* %cloexec_lock), !dbg !3436
  br label %if.end13, !dbg !3436

if.end13:                                         ; preds = %if.then12, %if.end9
  %15 = load %struct.uv_fs_s*, %struct.uv_fs_s** %req.addr, align 8, !dbg !3437
  %path14 = getelementptr inbounds %struct.uv_fs_s, %struct.uv_fs_s* %15, i32 0, i32 9, !dbg !3438
  %16 = load i8*, i8** %path14, align 8, !dbg !3438
  %17 = load %struct.uv_fs_s*, %struct.uv_fs_s** %req.addr, align 8, !dbg !3439
  %flags15 = getelementptr inbounds %struct.uv_fs_s, %struct.uv_fs_s* %17, i32 0, i32 13, !dbg !3440
  %18 = load i32, i32* %flags15, align 4, !dbg !3440
  %19 = load %struct.uv_fs_s*, %struct.uv_fs_s** %req.addr, align 8, !dbg !3441
  %mode16 = getelementptr inbounds %struct.uv_fs_s, %struct.uv_fs_s* %19, i32 0, i32 14, !dbg !3442
  %20 = load i32, i32* %mode16, align 8, !dbg !3442
  %call17 = call i32 (i8*, i32, ...) @open64(i8* %16, i32 %18, i32 %20), !dbg !3443
  store i32 %call17, i32* %r, align 4, !dbg !3444
  %21 = load i32, i32* %r, align 4, !dbg !3445
  %cmp18 = icmp sge i32 %21, 0, !dbg !3447
  br i1 %cmp18, label %land.lhs.true, label %if.end29, !dbg !3448

land.lhs.true:                                    ; preds = %if.end13
  %22 = load i32, i32* %r, align 4, !dbg !3449
  %call20 = call i32 @uv__cloexec_ioctl(i32 %22, i32 1), !dbg !3451
  %cmp21 = icmp ne i32 %call20, 0, !dbg !3452
  br i1 %cmp21, label %if.then23, label %if.end29, !dbg !3453

if.then23:                                        ; preds = %land.lhs.true
  %23 = load i32, i32* %r, align 4, !dbg !3454
  %call24 = call i32 @uv__close(i32 %23), !dbg !3456
  store i32 %call24, i32* %r, align 4, !dbg !3457
  %24 = load i32, i32* %r, align 4, !dbg !3458
  %cmp25 = icmp ne i32 %24, 0, !dbg !3460
  br i1 %cmp25, label %if.then27, label %if.end28, !dbg !3461

if.then27:                                        ; preds = %if.then23
  call void @abort() #8, !dbg !3462
  unreachable, !dbg !3462

if.end28:                                         ; preds = %if.then23
  store i32 -1, i32* %r, align 4, !dbg !3463
  br label %if.end29, !dbg !3464

if.end29:                                         ; preds = %if.end28, %land.lhs.true, %if.end13
  %25 = load %struct.uv_fs_s*, %struct.uv_fs_s** %req.addr, align 8, !dbg !3465
  %cb30 = getelementptr inbounds %struct.uv_fs_s, %struct.uv_fs_s* %25, i32 0, i32 6, !dbg !3467
  %26 = load void (%struct.uv_fs_s*)*, void (%struct.uv_fs_s*)** %cb30, align 8, !dbg !3467
  %cmp31 = icmp ne void (%struct.uv_fs_s*)* %26, null, !dbg !3468
  br i1 %cmp31, label %if.then33, label %if.end36, !dbg !3469

if.then33:                                        ; preds = %if.end29
  %27 = load %struct.uv_fs_s*, %struct.uv_fs_s** %req.addr, align 8, !dbg !3470
  %loop34 = getelementptr inbounds %struct.uv_fs_s, %struct.uv_fs_s* %27, i32 0, i32 5, !dbg !3471
  %28 = load %struct.uv_loop_s*, %struct.uv_loop_s** %loop34, align 8, !dbg !3471
  %cloexec_lock35 = getelementptr inbounds %struct.uv_loop_s, %struct.uv_loop_s* %28, i32 0, i32 15, !dbg !3472
  call void @uv_rwlock_rdunlock(%union.pthread_rwlock_t* %cloexec_lock35), !dbg !3473
  br label %if.end36, !dbg !3473

if.end36:                                         ; preds = %if.then33, %if.end29
  %29 = load i32, i32* %r, align 4, !dbg !3474
  %conv37 = sext i32 %29 to i64, !dbg !3474
  store i64 %conv37, i64* %retval, align 8, !dbg !3475
  br label %return, !dbg !3475

return:                                           ; preds = %if.end36, %if.then6, %if.then2
  %30 = load i64, i64* %retval, align 8, !dbg !3476
  ret i64 %30, !dbg !3476
}

; Function Attrs: nounwind uwtable
define internal i64 @uv__fs_buf_iter(%struct.uv_fs_s* %req, i64 (%struct.uv_fs_s*)* %process) #0 !dbg !529 {
entry:
  %retval = alloca i64, align 8
  %req.addr = alloca %struct.uv_fs_s*, align 8
  %process.addr = alloca i64 (%struct.uv_fs_s*)*, align 8
  %iovmax = alloca i32, align 4
  %nbufs = alloca i32, align 4
  %bufs = alloca %struct.uv_buf_t*, align 8
  %total = alloca i64, align 8
  %result = alloca i64, align 8
  store %struct.uv_fs_s* %req, %struct.uv_fs_s** %req.addr, align 8
  call void @llvm.dbg.declare(metadata %struct.uv_fs_s** %req.addr, metadata !3477, metadata !580), !dbg !3478
  store i64 (%struct.uv_fs_s*)* %process, i64 (%struct.uv_fs_s*)** %process.addr, align 8
  call void @llvm.dbg.declare(metadata i64 (%struct.uv_fs_s*)** %process.addr, metadata !3479, metadata !580), !dbg !3480
  call void @llvm.dbg.declare(metadata i32* %iovmax, metadata !3481, metadata !580), !dbg !3482
  call void @llvm.dbg.declare(metadata i32* %nbufs, metadata !3483, metadata !580), !dbg !3484
  call void @llvm.dbg.declare(metadata %struct.uv_buf_t** %bufs, metadata !3485, metadata !580), !dbg !3486
  call void @llvm.dbg.declare(metadata i64* %total, metadata !3487, metadata !580), !dbg !3488
  call void @llvm.dbg.declare(metadata i64* %result, metadata !3489, metadata !580), !dbg !3490
  %call = call i32 @uv__getiovmax(), !dbg !3491
  store i32 %call, i32* %iovmax, align 4, !dbg !3492
  %0 = load %struct.uv_fs_s*, %struct.uv_fs_s** %req.addr, align 8, !dbg !3493
  %nbufs1 = getelementptr inbounds %struct.uv_fs_s, %struct.uv_fs_s* %0, i32 0, i32 15, !dbg !3494
  %1 = load i32, i32* %nbufs1, align 4, !dbg !3494
  store i32 %1, i32* %nbufs, align 4, !dbg !3495
  %2 = load %struct.uv_fs_s*, %struct.uv_fs_s** %req.addr, align 8, !dbg !3496
  %bufs2 = getelementptr inbounds %struct.uv_fs_s, %struct.uv_fs_s* %2, i32 0, i32 16, !dbg !3497
  %3 = load %struct.uv_buf_t*, %struct.uv_buf_t** %bufs2, align 8, !dbg !3497
  store %struct.uv_buf_t* %3, %struct.uv_buf_t** %bufs, align 8, !dbg !3498
  store i64 0, i64* %total, align 8, !dbg !3499
  br label %while.cond, !dbg !3500

while.cond:                                       ; preds = %if.end17, %entry
  %4 = load i32, i32* %nbufs, align 4, !dbg !3501
  %cmp = icmp ugt i32 %4, 0, !dbg !3503
  br i1 %cmp, label %while.body, label %while.end, !dbg !3504

while.body:                                       ; preds = %while.cond
  %5 = load i32, i32* %nbufs, align 4, !dbg !3505
  %6 = load %struct.uv_fs_s*, %struct.uv_fs_s** %req.addr, align 8, !dbg !3507
  %nbufs3 = getelementptr inbounds %struct.uv_fs_s, %struct.uv_fs_s* %6, i32 0, i32 15, !dbg !3508
  store i32 %5, i32* %nbufs3, align 4, !dbg !3509
  %7 = load %struct.uv_fs_s*, %struct.uv_fs_s** %req.addr, align 8, !dbg !3510
  %nbufs4 = getelementptr inbounds %struct.uv_fs_s, %struct.uv_fs_s* %7, i32 0, i32 15, !dbg !3512
  %8 = load i32, i32* %nbufs4, align 4, !dbg !3512
  %9 = load i32, i32* %iovmax, align 4, !dbg !3513
  %cmp5 = icmp ugt i32 %8, %9, !dbg !3514
  br i1 %cmp5, label %if.then, label %if.end, !dbg !3515

if.then:                                          ; preds = %while.body
  %10 = load i32, i32* %iovmax, align 4, !dbg !3516
  %11 = load %struct.uv_fs_s*, %struct.uv_fs_s** %req.addr, align 8, !dbg !3517
  %nbufs6 = getelementptr inbounds %struct.uv_fs_s, %struct.uv_fs_s* %11, i32 0, i32 15, !dbg !3518
  store i32 %10, i32* %nbufs6, align 4, !dbg !3519
  br label %if.end, !dbg !3517

if.end:                                           ; preds = %if.then, %while.body
  %12 = load i64 (%struct.uv_fs_s*)*, i64 (%struct.uv_fs_s*)** %process.addr, align 8, !dbg !3520
  %13 = load %struct.uv_fs_s*, %struct.uv_fs_s** %req.addr, align 8, !dbg !3521
  %call7 = call i64 %12(%struct.uv_fs_s* %13), !dbg !3520
  store i64 %call7, i64* %result, align 8, !dbg !3522
  %14 = load i64, i64* %result, align 8, !dbg !3523
  %cmp8 = icmp sle i64 %14, 0, !dbg !3525
  br i1 %cmp8, label %if.then9, label %if.end13, !dbg !3526

if.then9:                                         ; preds = %if.end
  %15 = load i64, i64* %total, align 8, !dbg !3527
  %cmp10 = icmp eq i64 %15, 0, !dbg !3530
  br i1 %cmp10, label %if.then11, label %if.end12, !dbg !3531

if.then11:                                        ; preds = %if.then9
  %16 = load i64, i64* %result, align 8, !dbg !3532
  store i64 %16, i64* %total, align 8, !dbg !3533
  br label %if.end12, !dbg !3534

if.end12:                                         ; preds = %if.then11, %if.then9
  br label %while.end, !dbg !3535

if.end13:                                         ; preds = %if.end
  %17 = load %struct.uv_fs_s*, %struct.uv_fs_s** %req.addr, align 8, !dbg !3536
  %off = getelementptr inbounds %struct.uv_fs_s, %struct.uv_fs_s* %17, i32 0, i32 17, !dbg !3538
  %18 = load i64, i64* %off, align 8, !dbg !3538
  %cmp14 = icmp sge i64 %18, 0, !dbg !3539
  br i1 %cmp14, label %if.then15, label %if.end17, !dbg !3540

if.then15:                                        ; preds = %if.end13
  %19 = load i64, i64* %result, align 8, !dbg !3541
  %20 = load %struct.uv_fs_s*, %struct.uv_fs_s** %req.addr, align 8, !dbg !3542
  %off16 = getelementptr inbounds %struct.uv_fs_s, %struct.uv_fs_s* %20, i32 0, i32 17, !dbg !3543
  %21 = load i64, i64* %off16, align 8, !dbg !3544
  %add = add nsw i64 %21, %19, !dbg !3544
  store i64 %add, i64* %off16, align 8, !dbg !3544
  br label %if.end17, !dbg !3542

if.end17:                                         ; preds = %if.then15, %if.end13
  %22 = load %struct.uv_fs_s*, %struct.uv_fs_s** %req.addr, align 8, !dbg !3545
  %nbufs18 = getelementptr inbounds %struct.uv_fs_s, %struct.uv_fs_s* %22, i32 0, i32 15, !dbg !3546
  %23 = load i32, i32* %nbufs18, align 4, !dbg !3546
  %24 = load %struct.uv_fs_s*, %struct.uv_fs_s** %req.addr, align 8, !dbg !3547
  %bufs19 = getelementptr inbounds %struct.uv_fs_s, %struct.uv_fs_s* %24, i32 0, i32 16, !dbg !3548
  %25 = load %struct.uv_buf_t*, %struct.uv_buf_t** %bufs19, align 8, !dbg !3549
  %idx.ext = zext i32 %23 to i64, !dbg !3549
  %add.ptr = getelementptr inbounds %struct.uv_buf_t, %struct.uv_buf_t* %25, i64 %idx.ext, !dbg !3549
  store %struct.uv_buf_t* %add.ptr, %struct.uv_buf_t** %bufs19, align 8, !dbg !3549
  %26 = load %struct.uv_fs_s*, %struct.uv_fs_s** %req.addr, align 8, !dbg !3550
  %nbufs20 = getelementptr inbounds %struct.uv_fs_s, %struct.uv_fs_s* %26, i32 0, i32 15, !dbg !3551
  %27 = load i32, i32* %nbufs20, align 4, !dbg !3551
  %28 = load i32, i32* %nbufs, align 4, !dbg !3552
  %sub = sub i32 %28, %27, !dbg !3552
  store i32 %sub, i32* %nbufs, align 4, !dbg !3552
  %29 = load i64, i64* %result, align 8, !dbg !3553
  %30 = load i64, i64* %total, align 8, !dbg !3554
  %add21 = add nsw i64 %30, %29, !dbg !3554
  store i64 %add21, i64* %total, align 8, !dbg !3554
  br label %while.cond, !dbg !3555

while.end:                                        ; preds = %if.end12, %while.cond
  %call22 = call i32* @__errno_location() #1, !dbg !3557
  %31 = load i32, i32* %call22, align 4, !dbg !3557
  %cmp23 = icmp eq i32 %31, 4, !dbg !3559
  br i1 %cmp23, label %land.lhs.true, label %if.end26, !dbg !3560

land.lhs.true:                                    ; preds = %while.end
  %32 = load i64, i64* %total, align 8, !dbg !3561
  %cmp24 = icmp eq i64 %32, -1, !dbg !3563
  br i1 %cmp24, label %if.then25, label %if.end26, !dbg !3564

if.then25:                                        ; preds = %land.lhs.true
  %33 = load i64, i64* %total, align 8, !dbg !3565
  store i64 %33, i64* %retval, align 8, !dbg !3566
  br label %return, !dbg !3566

if.end26:                                         ; preds = %land.lhs.true, %while.end
  %34 = load %struct.uv_buf_t*, %struct.uv_buf_t** %bufs, align 8, !dbg !3567
  %35 = load %struct.uv_fs_s*, %struct.uv_fs_s** %req.addr, align 8, !dbg !3569
  %bufsml = getelementptr inbounds %struct.uv_fs_s, %struct.uv_fs_s* %35, i32 0, i32 23, !dbg !3570
  %arraydecay = getelementptr inbounds [4 x %struct.uv_buf_t], [4 x %struct.uv_buf_t]* %bufsml, i32 0, i32 0, !dbg !3569
  %cmp27 = icmp ne %struct.uv_buf_t* %34, %arraydecay, !dbg !3571
  br i1 %cmp27, label %if.then28, label %if.end29, !dbg !3572

if.then28:                                        ; preds = %if.end26
  %36 = load %struct.uv_buf_t*, %struct.uv_buf_t** %bufs, align 8, !dbg !3573
  %37 = bitcast %struct.uv_buf_t* %36 to i8*, !dbg !3573
  call void @uv__free(i8* %37), !dbg !3574
  br label %if.end29, !dbg !3574

if.end29:                                         ; preds = %if.then28, %if.end26
  %38 = load %struct.uv_fs_s*, %struct.uv_fs_s** %req.addr, align 8, !dbg !3575
  %bufs30 = getelementptr inbounds %struct.uv_fs_s, %struct.uv_fs_s* %38, i32 0, i32 16, !dbg !3576
  store %struct.uv_buf_t* null, %struct.uv_buf_t** %bufs30, align 8, !dbg !3577
  %39 = load %struct.uv_fs_s*, %struct.uv_fs_s** %req.addr, align 8, !dbg !3578
  %nbufs31 = getelementptr inbounds %struct.uv_fs_s, %struct.uv_fs_s* %39, i32 0, i32 15, !dbg !3579
  store i32 0, i32* %nbufs31, align 4, !dbg !3580
  %40 = load i64, i64* %total, align 8, !dbg !3581
  store i64 %40, i64* %retval, align 8, !dbg !3582
  br label %return, !dbg !3582

return:                                           ; preds = %if.end29, %if.then25
  %41 = load i64, i64* %retval, align 8, !dbg !3583
  ret i64 %41, !dbg !3583
}

; Function Attrs: nounwind uwtable
define internal i64 @uv__fs_read(%struct.uv_fs_s* %req) #0 !dbg !534 {
entry:
  %req.addr = alloca %struct.uv_fs_s*, align 8
  %result = alloca i64, align 8
  %nread = alloca i64, align 8
  %index = alloca i64, align 8
  store %struct.uv_fs_s* %req, %struct.uv_fs_s** %req.addr, align 8
  call void @llvm.dbg.declare(metadata %struct.uv_fs_s** %req.addr, metadata !3584, metadata !580), !dbg !3585
  call void @llvm.dbg.declare(metadata i64* %result, metadata !3586, metadata !580), !dbg !3587
  %0 = load %struct.uv_fs_s*, %struct.uv_fs_s** %req.addr, align 8, !dbg !3588
  %off = getelementptr inbounds %struct.uv_fs_s, %struct.uv_fs_s* %0, i32 0, i32 17, !dbg !3590
  %1 = load i64, i64* %off, align 8, !dbg !3590
  %cmp = icmp slt i64 %1, 0, !dbg !3591
  br i1 %cmp, label %if.then, label %if.else9, !dbg !3592

if.then:                                          ; preds = %entry
  %2 = load %struct.uv_fs_s*, %struct.uv_fs_s** %req.addr, align 8, !dbg !3593
  %nbufs = getelementptr inbounds %struct.uv_fs_s, %struct.uv_fs_s* %2, i32 0, i32 15, !dbg !3596
  %3 = load i32, i32* %nbufs, align 4, !dbg !3596
  %cmp1 = icmp eq i32 %3, 1, !dbg !3597
  br i1 %cmp1, label %if.then2, label %if.else, !dbg !3598

if.then2:                                         ; preds = %if.then
  %4 = load %struct.uv_fs_s*, %struct.uv_fs_s** %req.addr, align 8, !dbg !3599
  %file = getelementptr inbounds %struct.uv_fs_s, %struct.uv_fs_s* %4, i32 0, i32 12, !dbg !3600
  %5 = load i32, i32* %file, align 8, !dbg !3600
  %6 = load %struct.uv_fs_s*, %struct.uv_fs_s** %req.addr, align 8, !dbg !3601
  %bufs = getelementptr inbounds %struct.uv_fs_s, %struct.uv_fs_s* %6, i32 0, i32 16, !dbg !3602
  %7 = load %struct.uv_buf_t*, %struct.uv_buf_t** %bufs, align 8, !dbg !3602
  %arrayidx = getelementptr inbounds %struct.uv_buf_t, %struct.uv_buf_t* %7, i64 0, !dbg !3601
  %base = getelementptr inbounds %struct.uv_buf_t, %struct.uv_buf_t* %arrayidx, i32 0, i32 0, !dbg !3603
  %8 = load i8*, i8** %base, align 8, !dbg !3603
  %9 = load %struct.uv_fs_s*, %struct.uv_fs_s** %req.addr, align 8, !dbg !3604
  %bufs3 = getelementptr inbounds %struct.uv_fs_s, %struct.uv_fs_s* %9, i32 0, i32 16, !dbg !3605
  %10 = load %struct.uv_buf_t*, %struct.uv_buf_t** %bufs3, align 8, !dbg !3605
  %arrayidx4 = getelementptr inbounds %struct.uv_buf_t, %struct.uv_buf_t* %10, i64 0, !dbg !3604
  %len = getelementptr inbounds %struct.uv_buf_t, %struct.uv_buf_t* %arrayidx4, i32 0, i32 1, !dbg !3606
  %11 = load i64, i64* %len, align 8, !dbg !3606
  %call = call i64 @read(i32 %5, i8* %8, i64 %11), !dbg !3607
  store i64 %call, i64* %result, align 8, !dbg !3608
  br label %if.end, !dbg !3609

if.else:                                          ; preds = %if.then
  %12 = load %struct.uv_fs_s*, %struct.uv_fs_s** %req.addr, align 8, !dbg !3610
  %file5 = getelementptr inbounds %struct.uv_fs_s, %struct.uv_fs_s* %12, i32 0, i32 12, !dbg !3611
  %13 = load i32, i32* %file5, align 8, !dbg !3611
  %14 = load %struct.uv_fs_s*, %struct.uv_fs_s** %req.addr, align 8, !dbg !3612
  %bufs6 = getelementptr inbounds %struct.uv_fs_s, %struct.uv_fs_s* %14, i32 0, i32 16, !dbg !3613
  %15 = load %struct.uv_buf_t*, %struct.uv_buf_t** %bufs6, align 8, !dbg !3613
  %16 = bitcast %struct.uv_buf_t* %15 to %struct.iovec*, !dbg !3614
  %17 = load %struct.uv_fs_s*, %struct.uv_fs_s** %req.addr, align 8, !dbg !3615
  %nbufs7 = getelementptr inbounds %struct.uv_fs_s, %struct.uv_fs_s* %17, i32 0, i32 15, !dbg !3616
  %18 = load i32, i32* %nbufs7, align 4, !dbg !3616
  %call8 = call i64 @readv(i32 %13, %struct.iovec* %16, i32 %18), !dbg !3617
  store i64 %call8, i64* %result, align 8, !dbg !3618
  br label %if.end

if.end:                                           ; preds = %if.else, %if.then2
  br label %if.end66, !dbg !3619

if.else9:                                         ; preds = %entry
  %19 = load %struct.uv_fs_s*, %struct.uv_fs_s** %req.addr, align 8, !dbg !3620
  %nbufs10 = getelementptr inbounds %struct.uv_fs_s, %struct.uv_fs_s* %19, i32 0, i32 15, !dbg !3623
  %20 = load i32, i32* %nbufs10, align 4, !dbg !3623
  %cmp11 = icmp eq i32 %20, 1, !dbg !3624
  br i1 %cmp11, label %if.then12, label %if.end22, !dbg !3625

if.then12:                                        ; preds = %if.else9
  %21 = load %struct.uv_fs_s*, %struct.uv_fs_s** %req.addr, align 8, !dbg !3626
  %file13 = getelementptr inbounds %struct.uv_fs_s, %struct.uv_fs_s* %21, i32 0, i32 12, !dbg !3628
  %22 = load i32, i32* %file13, align 8, !dbg !3628
  %23 = load %struct.uv_fs_s*, %struct.uv_fs_s** %req.addr, align 8, !dbg !3629
  %bufs14 = getelementptr inbounds %struct.uv_fs_s, %struct.uv_fs_s* %23, i32 0, i32 16, !dbg !3630
  %24 = load %struct.uv_buf_t*, %struct.uv_buf_t** %bufs14, align 8, !dbg !3630
  %arrayidx15 = getelementptr inbounds %struct.uv_buf_t, %struct.uv_buf_t* %24, i64 0, !dbg !3629
  %base16 = getelementptr inbounds %struct.uv_buf_t, %struct.uv_buf_t* %arrayidx15, i32 0, i32 0, !dbg !3631
  %25 = load i8*, i8** %base16, align 8, !dbg !3631
  %26 = load %struct.uv_fs_s*, %struct.uv_fs_s** %req.addr, align 8, !dbg !3632
  %bufs17 = getelementptr inbounds %struct.uv_fs_s, %struct.uv_fs_s* %26, i32 0, i32 16, !dbg !3633
  %27 = load %struct.uv_buf_t*, %struct.uv_buf_t** %bufs17, align 8, !dbg !3633
  %arrayidx18 = getelementptr inbounds %struct.uv_buf_t, %struct.uv_buf_t* %27, i64 0, !dbg !3632
  %len19 = getelementptr inbounds %struct.uv_buf_t, %struct.uv_buf_t* %arrayidx18, i32 0, i32 1, !dbg !3634
  %28 = load i64, i64* %len19, align 8, !dbg !3634
  %29 = load %struct.uv_fs_s*, %struct.uv_fs_s** %req.addr, align 8, !dbg !3635
  %off20 = getelementptr inbounds %struct.uv_fs_s, %struct.uv_fs_s* %29, i32 0, i32 17, !dbg !3636
  %30 = load i64, i64* %off20, align 8, !dbg !3636
  %call21 = call i64 @pread64(i32 %22, i8* %25, i64 %28, i64 %30), !dbg !3637
  store i64 %call21, i64* %result, align 8, !dbg !3638
  br label %done, !dbg !3639

if.end22:                                         ; preds = %if.else9
  %31 = load i32, i32* @uv__fs_read.no_preadv, align 4, !dbg !3640
  %tobool = icmp ne i32 %31, 0, !dbg !3640
  br i1 %tobool, label %if.then23, label %if.else52, !dbg !3642

if.then23:                                        ; preds = %if.end22
  br label %retry, !dbg !3643

retry:                                            ; preds = %if.then63, %if.then23
  call void @llvm.dbg.declare(metadata i64* %nread, metadata !3645, metadata !580), !dbg !3647
  call void @llvm.dbg.declare(metadata i64* %index, metadata !3648, metadata !580), !dbg !3649
  store i64 0, i64* %nread, align 8, !dbg !3650
  store i64 0, i64* %index, align 8, !dbg !3651
  store i64 1, i64* %result, align 8, !dbg !3652
  br label %do.body, !dbg !3653

do.body:                                          ; preds = %land.end, %retry
  %32 = load i64, i64* %index, align 8, !dbg !3654
  %33 = load %struct.uv_fs_s*, %struct.uv_fs_s** %req.addr, align 8, !dbg !3657
  %bufs24 = getelementptr inbounds %struct.uv_fs_s, %struct.uv_fs_s* %33, i32 0, i32 16, !dbg !3658
  %34 = load %struct.uv_buf_t*, %struct.uv_buf_t** %bufs24, align 8, !dbg !3658
  %arrayidx25 = getelementptr inbounds %struct.uv_buf_t, %struct.uv_buf_t* %34, i64 %32, !dbg !3657
  %len26 = getelementptr inbounds %struct.uv_buf_t, %struct.uv_buf_t* %arrayidx25, i32 0, i32 1, !dbg !3659
  %35 = load i64, i64* %len26, align 8, !dbg !3659
  %cmp27 = icmp ugt i64 %35, 0, !dbg !3660
  br i1 %cmp27, label %if.then28, label %if.end42, !dbg !3661

if.then28:                                        ; preds = %do.body
  %36 = load %struct.uv_fs_s*, %struct.uv_fs_s** %req.addr, align 8, !dbg !3662
  %file29 = getelementptr inbounds %struct.uv_fs_s, %struct.uv_fs_s* %36, i32 0, i32 12, !dbg !3664
  %37 = load i32, i32* %file29, align 8, !dbg !3664
  %38 = load i64, i64* %index, align 8, !dbg !3665
  %39 = load %struct.uv_fs_s*, %struct.uv_fs_s** %req.addr, align 8, !dbg !3666
  %bufs30 = getelementptr inbounds %struct.uv_fs_s, %struct.uv_fs_s* %39, i32 0, i32 16, !dbg !3667
  %40 = load %struct.uv_buf_t*, %struct.uv_buf_t** %bufs30, align 8, !dbg !3667
  %arrayidx31 = getelementptr inbounds %struct.uv_buf_t, %struct.uv_buf_t* %40, i64 %38, !dbg !3666
  %base32 = getelementptr inbounds %struct.uv_buf_t, %struct.uv_buf_t* %arrayidx31, i32 0, i32 0, !dbg !3668
  %41 = load i8*, i8** %base32, align 8, !dbg !3668
  %42 = load i64, i64* %index, align 8, !dbg !3669
  %43 = load %struct.uv_fs_s*, %struct.uv_fs_s** %req.addr, align 8, !dbg !3670
  %bufs33 = getelementptr inbounds %struct.uv_fs_s, %struct.uv_fs_s* %43, i32 0, i32 16, !dbg !3671
  %44 = load %struct.uv_buf_t*, %struct.uv_buf_t** %bufs33, align 8, !dbg !3671
  %arrayidx34 = getelementptr inbounds %struct.uv_buf_t, %struct.uv_buf_t* %44, i64 %42, !dbg !3670
  %len35 = getelementptr inbounds %struct.uv_buf_t, %struct.uv_buf_t* %arrayidx34, i32 0, i32 1, !dbg !3672
  %45 = load i64, i64* %len35, align 8, !dbg !3672
  %46 = load %struct.uv_fs_s*, %struct.uv_fs_s** %req.addr, align 8, !dbg !3673
  %off36 = getelementptr inbounds %struct.uv_fs_s, %struct.uv_fs_s* %46, i32 0, i32 17, !dbg !3674
  %47 = load i64, i64* %off36, align 8, !dbg !3674
  %48 = load i64, i64* %nread, align 8, !dbg !3675
  %add = add nsw i64 %47, %48, !dbg !3676
  %call37 = call i64 @pread64(i32 %37, i8* %41, i64 %45, i64 %add), !dbg !3677
  store i64 %call37, i64* %result, align 8, !dbg !3678
  %49 = load i64, i64* %result, align 8, !dbg !3679
  %cmp38 = icmp sgt i64 %49, 0, !dbg !3681
  br i1 %cmp38, label %if.then39, label %if.end41, !dbg !3682

if.then39:                                        ; preds = %if.then28
  %50 = load i64, i64* %result, align 8, !dbg !3683
  %51 = load i64, i64* %nread, align 8, !dbg !3684
  %add40 = add nsw i64 %51, %50, !dbg !3684
  store i64 %add40, i64* %nread, align 8, !dbg !3684
  br label %if.end41, !dbg !3685

if.end41:                                         ; preds = %if.then39, %if.then28
  br label %if.end42, !dbg !3686

if.end42:                                         ; preds = %if.end41, %do.body
  %52 = load i64, i64* %index, align 8, !dbg !3687
  %inc = add i64 %52, 1, !dbg !3687
  store i64 %inc, i64* %index, align 8, !dbg !3687
  br label %do.cond, !dbg !3688

do.cond:                                          ; preds = %if.end42
  %53 = load i64, i64* %index, align 8, !dbg !3689
  %54 = load %struct.uv_fs_s*, %struct.uv_fs_s** %req.addr, align 8, !dbg !3691
  %nbufs43 = getelementptr inbounds %struct.uv_fs_s, %struct.uv_fs_s* %54, i32 0, i32 15, !dbg !3692
  %55 = load i32, i32* %nbufs43, align 4, !dbg !3692
  %conv = zext i32 %55 to i64, !dbg !3691
  %cmp44 = icmp ult i64 %53, %conv, !dbg !3693
  br i1 %cmp44, label %land.rhs, label %land.end, !dbg !3694

land.rhs:                                         ; preds = %do.cond
  %56 = load i64, i64* %result, align 8, !dbg !3695
  %cmp46 = icmp sgt i64 %56, 0, !dbg !3697
  br label %land.end

land.end:                                         ; preds = %land.rhs, %do.cond
  %57 = phi i1 [ false, %do.cond ], [ %cmp46, %land.rhs ]
  br i1 %57, label %do.body, label %do.end, !dbg !3698

do.end:                                           ; preds = %land.end
  %58 = load i64, i64* %nread, align 8, !dbg !3700
  %cmp48 = icmp sgt i64 %58, 0, !dbg !3702
  br i1 %cmp48, label %if.then50, label %if.end51, !dbg !3703

if.then50:                                        ; preds = %do.end
  %59 = load i64, i64* %nread, align 8, !dbg !3704
  store i64 %59, i64* %result, align 8, !dbg !3705
  br label %if.end51, !dbg !3706

if.end51:                                         ; preds = %if.then50, %do.end
  br label %if.end65, !dbg !3707

if.else52:                                        ; preds = %if.end22
  %60 = load %struct.uv_fs_s*, %struct.uv_fs_s** %req.addr, align 8, !dbg !3708
  %file53 = getelementptr inbounds %struct.uv_fs_s, %struct.uv_fs_s* %60, i32 0, i32 12, !dbg !3710
  %61 = load i32, i32* %file53, align 8, !dbg !3710
  %62 = load %struct.uv_fs_s*, %struct.uv_fs_s** %req.addr, align 8, !dbg !3711
  %bufs54 = getelementptr inbounds %struct.uv_fs_s, %struct.uv_fs_s* %62, i32 0, i32 16, !dbg !3712
  %63 = load %struct.uv_buf_t*, %struct.uv_buf_t** %bufs54, align 8, !dbg !3712
  %64 = bitcast %struct.uv_buf_t* %63 to %struct.iovec*, !dbg !3713
  %65 = load %struct.uv_fs_s*, %struct.uv_fs_s** %req.addr, align 8, !dbg !3714
  %nbufs55 = getelementptr inbounds %struct.uv_fs_s, %struct.uv_fs_s* %65, i32 0, i32 15, !dbg !3715
  %66 = load i32, i32* %nbufs55, align 4, !dbg !3715
  %67 = load %struct.uv_fs_s*, %struct.uv_fs_s** %req.addr, align 8, !dbg !3716
  %off56 = getelementptr inbounds %struct.uv_fs_s, %struct.uv_fs_s* %67, i32 0, i32 17, !dbg !3717
  %68 = load i64, i64* %off56, align 8, !dbg !3717
  %call57 = call i64 @uv__preadv(i32 %61, %struct.iovec* %64, i32 %66, i64 %68), !dbg !3718
  store i64 %call57, i64* %result, align 8, !dbg !3719
  %69 = load i64, i64* %result, align 8, !dbg !3720
  %cmp58 = icmp eq i64 %69, -1, !dbg !3722
  br i1 %cmp58, label %land.lhs.true, label %if.end64, !dbg !3723

land.lhs.true:                                    ; preds = %if.else52
  %call60 = call i32* @__errno_location() #1, !dbg !3724
  %70 = load i32, i32* %call60, align 4, !dbg !3724
  %cmp61 = icmp eq i32 %70, 38, !dbg !3726
  br i1 %cmp61, label %if.then63, label %if.end64, !dbg !3727

if.then63:                                        ; preds = %land.lhs.true
  store i32 1, i32* @uv__fs_read.no_preadv, align 4, !dbg !3728
  br label %retry, !dbg !3730

if.end64:                                         ; preds = %land.lhs.true, %if.else52
  br label %if.end65

if.end65:                                         ; preds = %if.end64, %if.end51
  br label %if.end66

if.end66:                                         ; preds = %if.end65, %if.end
  br label %done, !dbg !3731

done:                                             ; preds = %if.end66, %if.then12
  %71 = load i64, i64* %result, align 8, !dbg !3733
  ret i64 %71, !dbg !3734
}

; Function Attrs: nounwind uwtable
define internal i64 @uv__fs_scandir(%struct.uv_fs_s* %req) #0 !dbg !535 {
entry:
  %retval = alloca i64, align 8
  %req.addr = alloca %struct.uv_fs_s*, align 8
  %dents = alloca %struct.dirent**, align 8
  %n = alloca i32, align 4
  store %struct.uv_fs_s* %req, %struct.uv_fs_s** %req.addr, align 8
  call void @llvm.dbg.declare(metadata %struct.uv_fs_s** %req.addr, metadata !3735, metadata !580), !dbg !3736
  call void @llvm.dbg.declare(metadata %struct.dirent*** %dents, metadata !3737, metadata !580), !dbg !3740
  call void @llvm.dbg.declare(metadata i32* %n, metadata !3741, metadata !580), !dbg !3742
  store %struct.dirent** null, %struct.dirent*** %dents, align 8, !dbg !3743
  %0 = load %struct.uv_fs_s*, %struct.uv_fs_s** %req.addr, align 8, !dbg !3744
  %path = getelementptr inbounds %struct.uv_fs_s, %struct.uv_fs_s* %0, i32 0, i32 9, !dbg !3745
  %1 = load i8*, i8** %path, align 8, !dbg !3745
  %call = call i32 @scandir64(i8* %1, %struct.dirent*** %dents, i32 (%struct.dirent*)* @uv__fs_scandir_filter, i32 (%struct.dirent**, %struct.dirent**)* @uv__fs_scandir_sort), !dbg !3746
  store i32 %call, i32* %n, align 4, !dbg !3747
  %2 = load %struct.uv_fs_s*, %struct.uv_fs_s** %req.addr, align 8, !dbg !3748
  %nbufs = getelementptr inbounds %struct.uv_fs_s, %struct.uv_fs_s* %2, i32 0, i32 15, !dbg !3749
  store i32 0, i32* %nbufs, align 4, !dbg !3750
  %3 = load i32, i32* %n, align 4, !dbg !3751
  %cmp = icmp eq i32 %3, 0, !dbg !3753
  br i1 %cmp, label %if.then, label %if.else, !dbg !3754

if.then:                                          ; preds = %entry
  %4 = load %struct.dirent**, %struct.dirent*** %dents, align 8, !dbg !3755
  %5 = bitcast %struct.dirent** %4 to i8*, !dbg !3755
  call void @free(i8* %5) #9, !dbg !3757
  store %struct.dirent** null, %struct.dirent*** %dents, align 8, !dbg !3758
  br label %if.end3, !dbg !3759

if.else:                                          ; preds = %entry
  %6 = load i32, i32* %n, align 4, !dbg !3760
  %cmp1 = icmp eq i32 %6, -1, !dbg !3763
  br i1 %cmp1, label %if.then2, label %if.end, !dbg !3760

if.then2:                                         ; preds = %if.else
  %7 = load i32, i32* %n, align 4, !dbg !3764
  %conv = sext i32 %7 to i64, !dbg !3764
  store i64 %conv, i64* %retval, align 8, !dbg !3766
  br label %return, !dbg !3766

if.end:                                           ; preds = %if.else
  br label %if.end3

if.end3:                                          ; preds = %if.end, %if.then
  %8 = load %struct.dirent**, %struct.dirent*** %dents, align 8, !dbg !3767
  %9 = bitcast %struct.dirent** %8 to i8*, !dbg !3767
  %10 = load %struct.uv_fs_s*, %struct.uv_fs_s** %req.addr, align 8, !dbg !3768
  %ptr = getelementptr inbounds %struct.uv_fs_s, %struct.uv_fs_s* %10, i32 0, i32 8, !dbg !3769
  store i8* %9, i8** %ptr, align 8, !dbg !3770
  %11 = load i32, i32* %n, align 4, !dbg !3771
  %conv4 = sext i32 %11 to i64, !dbg !3771
  store i64 %conv4, i64* %retval, align 8, !dbg !3772
  br label %return, !dbg !3772

return:                                           ; preds = %if.end3, %if.then2
  %12 = load i64, i64* %retval, align 8, !dbg !3773
  ret i64 %12, !dbg !3773
}

; Function Attrs: nounwind uwtable
define internal i64 @uv__fs_readlink(%struct.uv_fs_s* %req) #0 !dbg !560 {
entry:
  %retval = alloca i64, align 8
  %req.addr = alloca %struct.uv_fs_s*, align 8
  %len = alloca i64, align 8
  %buf = alloca i8*, align 8
  store %struct.uv_fs_s* %req, %struct.uv_fs_s** %req.addr, align 8
  call void @llvm.dbg.declare(metadata %struct.uv_fs_s** %req.addr, metadata !3774, metadata !580), !dbg !3775
  call void @llvm.dbg.declare(metadata i64* %len, metadata !3776, metadata !580), !dbg !3777
  call void @llvm.dbg.declare(metadata i8** %buf, metadata !3778, metadata !580), !dbg !3779
  %0 = load %struct.uv_fs_s*, %struct.uv_fs_s** %req.addr, align 8, !dbg !3780
  %path = getelementptr inbounds %struct.uv_fs_s, %struct.uv_fs_s* %0, i32 0, i32 9, !dbg !3781
  %1 = load i8*, i8** %path, align 8, !dbg !3781
  %call = call i64 @uv__fs_pathmax_size(i8* %1), !dbg !3782
  store i64 %call, i64* %len, align 8, !dbg !3783
  %2 = load i64, i64* %len, align 8, !dbg !3784
  %add = add nsw i64 %2, 1, !dbg !3785
  %call1 = call i8* @uv__malloc(i64 %add), !dbg !3786
  store i8* %call1, i8** %buf, align 8, !dbg !3787
  %3 = load i8*, i8** %buf, align 8, !dbg !3788
  %cmp = icmp eq i8* %3, null, !dbg !3790
  br i1 %cmp, label %if.then, label %if.end, !dbg !3791

if.then:                                          ; preds = %entry
  %call2 = call i32* @__errno_location() #1, !dbg !3792
  store i32 12, i32* %call2, align 4, !dbg !3794
  store i64 -1, i64* %retval, align 8, !dbg !3795
  br label %return, !dbg !3795

if.end:                                           ; preds = %entry
  %4 = load %struct.uv_fs_s*, %struct.uv_fs_s** %req.addr, align 8, !dbg !3796
  %path3 = getelementptr inbounds %struct.uv_fs_s, %struct.uv_fs_s* %4, i32 0, i32 9, !dbg !3797
  %5 = load i8*, i8** %path3, align 8, !dbg !3797
  %6 = load i8*, i8** %buf, align 8, !dbg !3798
  %7 = load i64, i64* %len, align 8, !dbg !3799
  %call4 = call i64 @readlink(i8* %5, i8* %6, i64 %7) #9, !dbg !3800
  store i64 %call4, i64* %len, align 8, !dbg !3801
  %8 = load i64, i64* %len, align 8, !dbg !3802
  %cmp5 = icmp eq i64 %8, -1, !dbg !3804
  br i1 %cmp5, label %if.then6, label %if.end7, !dbg !3805

if.then6:                                         ; preds = %if.end
  %9 = load i8*, i8** %buf, align 8, !dbg !3806
  call void @uv__free(i8* %9), !dbg !3808
  store i64 -1, i64* %retval, align 8, !dbg !3809
  br label %return, !dbg !3809

if.end7:                                          ; preds = %if.end
  %10 = load i64, i64* %len, align 8, !dbg !3810
  %11 = load i8*, i8** %buf, align 8, !dbg !3811
  %arrayidx = getelementptr inbounds i8, i8* %11, i64 %10, !dbg !3811
  store i8 0, i8* %arrayidx, align 1, !dbg !3812
  %12 = load i8*, i8** %buf, align 8, !dbg !3813
  %13 = load %struct.uv_fs_s*, %struct.uv_fs_s** %req.addr, align 8, !dbg !3814
  %ptr = getelementptr inbounds %struct.uv_fs_s, %struct.uv_fs_s* %13, i32 0, i32 8, !dbg !3815
  store i8* %12, i8** %ptr, align 8, !dbg !3816
  store i64 0, i64* %retval, align 8, !dbg !3817
  br label %return, !dbg !3817

return:                                           ; preds = %if.end7, %if.then6, %if.then
  %14 = load i64, i64* %retval, align 8, !dbg !3818
  ret i64 %14, !dbg !3818
}

; Function Attrs: nounwind uwtable
define internal i64 @uv__fs_realpath(%struct.uv_fs_s* %req) #0 !dbg !564 {
entry:
  %retval = alloca i64, align 8
  %req.addr = alloca %struct.uv_fs_s*, align 8
  %len = alloca i64, align 8
  %buf = alloca i8*, align 8
  store %struct.uv_fs_s* %req, %struct.uv_fs_s** %req.addr, align 8
  call void @llvm.dbg.declare(metadata %struct.uv_fs_s** %req.addr, metadata !3819, metadata !580), !dbg !3820
  call void @llvm.dbg.declare(metadata i64* %len, metadata !3821, metadata !580), !dbg !3822
  call void @llvm.dbg.declare(metadata i8** %buf, metadata !3823, metadata !580), !dbg !3824
  %0 = load %struct.uv_fs_s*, %struct.uv_fs_s** %req.addr, align 8, !dbg !3825
  %path = getelementptr inbounds %struct.uv_fs_s, %struct.uv_fs_s* %0, i32 0, i32 9, !dbg !3826
  %1 = load i8*, i8** %path, align 8, !dbg !3826
  %call = call i64 @uv__fs_pathmax_size(i8* %1), !dbg !3827
  store i64 %call, i64* %len, align 8, !dbg !3828
  %2 = load i64, i64* %len, align 8, !dbg !3829
  %add = add nsw i64 %2, 1, !dbg !3830
  %call1 = call i8* @uv__malloc(i64 %add), !dbg !3831
  store i8* %call1, i8** %buf, align 8, !dbg !3832
  %3 = load i8*, i8** %buf, align 8, !dbg !3833
  %cmp = icmp eq i8* %3, null, !dbg !3835
  br i1 %cmp, label %if.then, label %if.end, !dbg !3836

if.then:                                          ; preds = %entry
  %call2 = call i32* @__errno_location() #1, !dbg !3837
  store i32 12, i32* %call2, align 4, !dbg !3839
  store i64 -1, i64* %retval, align 8, !dbg !3840
  br label %return, !dbg !3840

if.end:                                           ; preds = %entry
  %4 = load %struct.uv_fs_s*, %struct.uv_fs_s** %req.addr, align 8, !dbg !3841
  %path3 = getelementptr inbounds %struct.uv_fs_s, %struct.uv_fs_s* %4, i32 0, i32 9, !dbg !3843
  %5 = load i8*, i8** %path3, align 8, !dbg !3843
  %6 = load i8*, i8** %buf, align 8, !dbg !3844
  %call4 = call i8* @realpath(i8* %5, i8* %6) #9, !dbg !3845
  %cmp5 = icmp eq i8* %call4, null, !dbg !3846
  br i1 %cmp5, label %if.then6, label %if.end7, !dbg !3847

if.then6:                                         ; preds = %if.end
  %7 = load i8*, i8** %buf, align 8, !dbg !3848
  call void @uv__free(i8* %7), !dbg !3850
  store i64 -1, i64* %retval, align 8, !dbg !3851
  br label %return, !dbg !3851

if.end7:                                          ; preds = %if.end
  %8 = load i8*, i8** %buf, align 8, !dbg !3852
  %9 = load %struct.uv_fs_s*, %struct.uv_fs_s** %req.addr, align 8, !dbg !3853
  %ptr = getelementptr inbounds %struct.uv_fs_s, %struct.uv_fs_s* %9, i32 0, i32 8, !dbg !3854
  store i8* %8, i8** %ptr, align 8, !dbg !3855
  store i64 0, i64* %retval, align 8, !dbg !3856
  br label %return, !dbg !3856

return:                                           ; preds = %if.end7, %if.then6, %if.then
  %10 = load i64, i64* %retval, align 8, !dbg !3857
  ret i64 %10, !dbg !3857
}

; Function Attrs: nounwind
declare i32 @rename(i8*, i8*) #7

; Function Attrs: nounwind
declare i32 @rmdir(i8*) #7

; Function Attrs: nounwind uwtable
define internal i64 @uv__fs_sendfile(%struct.uv_fs_s* %req) #0 !dbg !565 {
entry:
  %retval = alloca i64, align 8
  %req.addr = alloca %struct.uv_fs_s*, align 8
  %in_fd = alloca i32, align 4
  %out_fd = alloca i32, align 4
  %off = alloca i64, align 8
  %r = alloca i64, align 8
  store %struct.uv_fs_s* %req, %struct.uv_fs_s** %req.addr, align 8
  call void @llvm.dbg.declare(metadata %struct.uv_fs_s** %req.addr, metadata !3858, metadata !580), !dbg !3859
  call void @llvm.dbg.declare(metadata i32* %in_fd, metadata !3860, metadata !580), !dbg !3861
  call void @llvm.dbg.declare(metadata i32* %out_fd, metadata !3862, metadata !580), !dbg !3863
  %0 = load %struct.uv_fs_s*, %struct.uv_fs_s** %req.addr, align 8, !dbg !3864
  %flags = getelementptr inbounds %struct.uv_fs_s, %struct.uv_fs_s* %0, i32 0, i32 13, !dbg !3865
  %1 = load i32, i32* %flags, align 4, !dbg !3865
  store i32 %1, i32* %in_fd, align 4, !dbg !3866
  %2 = load %struct.uv_fs_s*, %struct.uv_fs_s** %req.addr, align 8, !dbg !3867
  %file = getelementptr inbounds %struct.uv_fs_s, %struct.uv_fs_s* %2, i32 0, i32 12, !dbg !3868
  %3 = load i32, i32* %file, align 8, !dbg !3868
  store i32 %3, i32* %out_fd, align 4, !dbg !3869
  call void @llvm.dbg.declare(metadata i64* %off, metadata !3870, metadata !580), !dbg !3872
  call void @llvm.dbg.declare(metadata i64* %r, metadata !3873, metadata !580), !dbg !3874
  %4 = load %struct.uv_fs_s*, %struct.uv_fs_s** %req.addr, align 8, !dbg !3875
  %off1 = getelementptr inbounds %struct.uv_fs_s, %struct.uv_fs_s* %4, i32 0, i32 17, !dbg !3876
  %5 = load i64, i64* %off1, align 8, !dbg !3876
  store i64 %5, i64* %off, align 8, !dbg !3877
  %6 = load i32, i32* %out_fd, align 4, !dbg !3878
  %7 = load i32, i32* %in_fd, align 4, !dbg !3879
  %8 = load %struct.uv_fs_s*, %struct.uv_fs_s** %req.addr, align 8, !dbg !3880
  %bufsml = getelementptr inbounds %struct.uv_fs_s, %struct.uv_fs_s* %8, i32 0, i32 23, !dbg !3881
  %arrayidx = getelementptr inbounds [4 x %struct.uv_buf_t], [4 x %struct.uv_buf_t]* %bufsml, i64 0, i64 0, !dbg !3880
  %len = getelementptr inbounds %struct.uv_buf_t, %struct.uv_buf_t* %arrayidx, i32 0, i32 1, !dbg !3882
  %9 = load i64, i64* %len, align 8, !dbg !3882
  %call = call i64 @sendfile64(i32 %6, i32 %7, i64* %off, i64 %9) #9, !dbg !3883
  store i64 %call, i64* %r, align 8, !dbg !3884
  %10 = load i64, i64* %r, align 8, !dbg !3885
  %cmp = icmp ne i64 %10, -1, !dbg !3887
  br i1 %cmp, label %if.then, label %lor.lhs.false, !dbg !3888

lor.lhs.false:                                    ; preds = %entry
  %11 = load i64, i64* %off, align 8, !dbg !3889
  %12 = load %struct.uv_fs_s*, %struct.uv_fs_s** %req.addr, align 8, !dbg !3891
  %off2 = getelementptr inbounds %struct.uv_fs_s, %struct.uv_fs_s* %12, i32 0, i32 17, !dbg !3892
  %13 = load i64, i64* %off2, align 8, !dbg !3892
  %cmp3 = icmp sgt i64 %11, %13, !dbg !3893
  br i1 %cmp3, label %if.then, label %if.end, !dbg !3894

if.then:                                          ; preds = %lor.lhs.false, %entry
  %14 = load i64, i64* %off, align 8, !dbg !3895
  %15 = load %struct.uv_fs_s*, %struct.uv_fs_s** %req.addr, align 8, !dbg !3897
  %off4 = getelementptr inbounds %struct.uv_fs_s, %struct.uv_fs_s* %15, i32 0, i32 17, !dbg !3898
  %16 = load i64, i64* %off4, align 8, !dbg !3898
  %sub = sub nsw i64 %14, %16, !dbg !3899
  store i64 %sub, i64* %r, align 8, !dbg !3900
  %17 = load i64, i64* %off, align 8, !dbg !3901
  %18 = load %struct.uv_fs_s*, %struct.uv_fs_s** %req.addr, align 8, !dbg !3902
  %off5 = getelementptr inbounds %struct.uv_fs_s, %struct.uv_fs_s* %18, i32 0, i32 17, !dbg !3903
  store i64 %17, i64* %off5, align 8, !dbg !3904
  %19 = load i64, i64* %r, align 8, !dbg !3905
  store i64 %19, i64* %retval, align 8, !dbg !3906
  br label %return, !dbg !3906

if.end:                                           ; preds = %lor.lhs.false
  %call6 = call i32* @__errno_location() #1, !dbg !3907
  %20 = load i32, i32* %call6, align 4, !dbg !3907
  %cmp7 = icmp eq i32 %20, 22, !dbg !3909
  br i1 %cmp7, label %if.then17, label %lor.lhs.false8, !dbg !3910

lor.lhs.false8:                                   ; preds = %if.end
  %call9 = call i32* @__errno_location() #1, !dbg !3911
  %21 = load i32, i32* %call9, align 4, !dbg !3911
  %cmp10 = icmp eq i32 %21, 5, !dbg !3912
  br i1 %cmp10, label %if.then17, label %lor.lhs.false11, !dbg !3913

lor.lhs.false11:                                  ; preds = %lor.lhs.false8
  %call12 = call i32* @__errno_location() #1, !dbg !3914
  %22 = load i32, i32* %call12, align 4, !dbg !3914
  %cmp13 = icmp eq i32 %22, 88, !dbg !3915
  br i1 %cmp13, label %if.then17, label %lor.lhs.false14, !dbg !3916

lor.lhs.false14:                                  ; preds = %lor.lhs.false11
  %call15 = call i32* @__errno_location() #1, !dbg !3917
  %23 = load i32, i32* %call15, align 4, !dbg !3917
  %cmp16 = icmp eq i32 %23, 18, !dbg !3918
  br i1 %cmp16, label %if.then17, label %if.end20, !dbg !3919

if.then17:                                        ; preds = %lor.lhs.false14, %lor.lhs.false11, %lor.lhs.false8, %if.end
  %call18 = call i32* @__errno_location() #1, !dbg !3921
  store i32 0, i32* %call18, align 4, !dbg !3923
  %24 = load %struct.uv_fs_s*, %struct.uv_fs_s** %req.addr, align 8, !dbg !3924
  %call19 = call i64 @uv__fs_sendfile_emul(%struct.uv_fs_s* %24), !dbg !3925
  store i64 %call19, i64* %retval, align 8, !dbg !3926
  br label %return, !dbg !3926

if.end20:                                         ; preds = %lor.lhs.false14
  store i64 -1, i64* %retval, align 8, !dbg !3927
  br label %return, !dbg !3927

return:                                           ; preds = %if.end20, %if.then17, %if.then
  %25 = load i64, i64* %retval, align 8, !dbg !3928
  ret i64 %25, !dbg !3928
}

; Function Attrs: nounwind uwtable
define internal i32 @uv__fs_stat(i8* %path, %struct.uv_stat_t* %buf) #0 !dbg !567 {
entry:
  %path.addr = alloca i8*, align 8
  %buf.addr = alloca %struct.uv_stat_t*, align 8
  %pbuf = alloca %struct.stat, align 8
  %ret = alloca i32, align 4
  store i8* %path, i8** %path.addr, align 8
  call void @llvm.dbg.declare(metadata i8** %path.addr, metadata !3929, metadata !580), !dbg !3930
  store %struct.uv_stat_t* %buf, %struct.uv_stat_t** %buf.addr, align 8
  call void @llvm.dbg.declare(metadata %struct.uv_stat_t** %buf.addr, metadata !3931, metadata !580), !dbg !3932
  call void @llvm.dbg.declare(metadata %struct.stat* %pbuf, metadata !3933, metadata !580), !dbg !3934
  call void @llvm.dbg.declare(metadata i32* %ret, metadata !3935, metadata !580), !dbg !3936
  %0 = load i8*, i8** %path.addr, align 8, !dbg !3937
  %call = call i32 @stat64(i8* %0, %struct.stat* %pbuf) #9, !dbg !3938
  store i32 %call, i32* %ret, align 4, !dbg !3939
  %1 = load i32, i32* %ret, align 4, !dbg !3940
  %cmp = icmp eq i32 %1, 0, !dbg !3942
  br i1 %cmp, label %if.then, label %if.end, !dbg !3943

if.then:                                          ; preds = %entry
  %2 = load %struct.uv_stat_t*, %struct.uv_stat_t** %buf.addr, align 8, !dbg !3944
  call void @uv__to_stat(%struct.stat* %pbuf, %struct.uv_stat_t* %2), !dbg !3945
  br label %if.end, !dbg !3945

if.end:                                           ; preds = %if.then, %entry
  %3 = load i32, i32* %ret, align 4, !dbg !3946
  ret i32 %3, !dbg !3947
}

; Function Attrs: nounwind
declare i32 @symlink(i8*, i8*) #7

; Function Attrs: nounwind
declare i32 @unlink(i8*) #7

; Function Attrs: nounwind uwtable
define internal i64 @uv__fs_utime(%struct.uv_fs_s* %req) #0 !dbg !568 {
entry:
  %req.addr = alloca %struct.uv_fs_s*, align 8
  %buf = alloca %struct.utimbuf, align 8
  store %struct.uv_fs_s* %req, %struct.uv_fs_s** %req.addr, align 8
  call void @llvm.dbg.declare(metadata %struct.uv_fs_s** %req.addr, metadata !3948, metadata !580), !dbg !3949
  call void @llvm.dbg.declare(metadata %struct.utimbuf* %buf, metadata !3950, metadata !580), !dbg !3956
  %0 = load %struct.uv_fs_s*, %struct.uv_fs_s** %req.addr, align 8, !dbg !3957
  %atime = getelementptr inbounds %struct.uv_fs_s, %struct.uv_fs_s* %0, i32 0, i32 20, !dbg !3958
  %1 = load double, double* %atime, align 8, !dbg !3958
  %conv = fptosi double %1 to i64, !dbg !3957
  %actime = getelementptr inbounds %struct.utimbuf, %struct.utimbuf* %buf, i32 0, i32 0, !dbg !3959
  store i64 %conv, i64* %actime, align 8, !dbg !3960
  %2 = load %struct.uv_fs_s*, %struct.uv_fs_s** %req.addr, align 8, !dbg !3961
  %mtime = getelementptr inbounds %struct.uv_fs_s, %struct.uv_fs_s* %2, i32 0, i32 21, !dbg !3962
  %3 = load double, double* %mtime, align 8, !dbg !3962
  %conv1 = fptosi double %3 to i64, !dbg !3961
  %modtime = getelementptr inbounds %struct.utimbuf, %struct.utimbuf* %buf, i32 0, i32 1, !dbg !3963
  store i64 %conv1, i64* %modtime, align 8, !dbg !3964
  %4 = load %struct.uv_fs_s*, %struct.uv_fs_s** %req.addr, align 8, !dbg !3965
  %path = getelementptr inbounds %struct.uv_fs_s, %struct.uv_fs_s* %4, i32 0, i32 9, !dbg !3966
  %5 = load i8*, i8** %path, align 8, !dbg !3966
  %call = call i32 @utime(i8* %5, %struct.utimbuf* %buf) #9, !dbg !3967
  %conv2 = sext i32 %call to i64, !dbg !3967
  ret i64 %conv2, !dbg !3968
}

; Function Attrs: nounwind uwtable
define internal i64 @uv__fs_write(%struct.uv_fs_s* %req) #0 !dbg !569 {
entry:
  %req.addr = alloca %struct.uv_fs_s*, align 8
  %r = alloca i64, align 8
  %written = alloca i64, align 8
  %index = alloca i64, align 8
  store %struct.uv_fs_s* %req, %struct.uv_fs_s** %req.addr, align 8
  call void @llvm.dbg.declare(metadata %struct.uv_fs_s** %req.addr, metadata !3969, metadata !580), !dbg !3970
  call void @llvm.dbg.declare(metadata i64* %r, metadata !3971, metadata !580), !dbg !3972
  %0 = load %struct.uv_fs_s*, %struct.uv_fs_s** %req.addr, align 8, !dbg !3973
  %off = getelementptr inbounds %struct.uv_fs_s, %struct.uv_fs_s* %0, i32 0, i32 17, !dbg !3975
  %1 = load i64, i64* %off, align 8, !dbg !3975
  %cmp = icmp slt i64 %1, 0, !dbg !3976
  br i1 %cmp, label %if.then, label %if.else9, !dbg !3977

if.then:                                          ; preds = %entry
  %2 = load %struct.uv_fs_s*, %struct.uv_fs_s** %req.addr, align 8, !dbg !3978
  %nbufs = getelementptr inbounds %struct.uv_fs_s, %struct.uv_fs_s* %2, i32 0, i32 15, !dbg !3981
  %3 = load i32, i32* %nbufs, align 4, !dbg !3981
  %cmp1 = icmp eq i32 %3, 1, !dbg !3982
  br i1 %cmp1, label %if.then2, label %if.else, !dbg !3983

if.then2:                                         ; preds = %if.then
  %4 = load %struct.uv_fs_s*, %struct.uv_fs_s** %req.addr, align 8, !dbg !3984
  %file = getelementptr inbounds %struct.uv_fs_s, %struct.uv_fs_s* %4, i32 0, i32 12, !dbg !3985
  %5 = load i32, i32* %file, align 8, !dbg !3985
  %6 = load %struct.uv_fs_s*, %struct.uv_fs_s** %req.addr, align 8, !dbg !3986
  %bufs = getelementptr inbounds %struct.uv_fs_s, %struct.uv_fs_s* %6, i32 0, i32 16, !dbg !3987
  %7 = load %struct.uv_buf_t*, %struct.uv_buf_t** %bufs, align 8, !dbg !3987
  %arrayidx = getelementptr inbounds %struct.uv_buf_t, %struct.uv_buf_t* %7, i64 0, !dbg !3986
  %base = getelementptr inbounds %struct.uv_buf_t, %struct.uv_buf_t* %arrayidx, i32 0, i32 0, !dbg !3988
  %8 = load i8*, i8** %base, align 8, !dbg !3988
  %9 = load %struct.uv_fs_s*, %struct.uv_fs_s** %req.addr, align 8, !dbg !3989
  %bufs3 = getelementptr inbounds %struct.uv_fs_s, %struct.uv_fs_s* %9, i32 0, i32 16, !dbg !3990
  %10 = load %struct.uv_buf_t*, %struct.uv_buf_t** %bufs3, align 8, !dbg !3990
  %arrayidx4 = getelementptr inbounds %struct.uv_buf_t, %struct.uv_buf_t* %10, i64 0, !dbg !3989
  %len = getelementptr inbounds %struct.uv_buf_t, %struct.uv_buf_t* %arrayidx4, i32 0, i32 1, !dbg !3991
  %11 = load i64, i64* %len, align 8, !dbg !3991
  %call = call i64 @write(i32 %5, i8* %8, i64 %11), !dbg !3992
  store i64 %call, i64* %r, align 8, !dbg !3993
  br label %if.end, !dbg !3994

if.else:                                          ; preds = %if.then
  %12 = load %struct.uv_fs_s*, %struct.uv_fs_s** %req.addr, align 8, !dbg !3995
  %file5 = getelementptr inbounds %struct.uv_fs_s, %struct.uv_fs_s* %12, i32 0, i32 12, !dbg !3996
  %13 = load i32, i32* %file5, align 8, !dbg !3996
  %14 = load %struct.uv_fs_s*, %struct.uv_fs_s** %req.addr, align 8, !dbg !3997
  %bufs6 = getelementptr inbounds %struct.uv_fs_s, %struct.uv_fs_s* %14, i32 0, i32 16, !dbg !3998
  %15 = load %struct.uv_buf_t*, %struct.uv_buf_t** %bufs6, align 8, !dbg !3998
  %16 = bitcast %struct.uv_buf_t* %15 to %struct.iovec*, !dbg !3999
  %17 = load %struct.uv_fs_s*, %struct.uv_fs_s** %req.addr, align 8, !dbg !4000
  %nbufs7 = getelementptr inbounds %struct.uv_fs_s, %struct.uv_fs_s* %17, i32 0, i32 15, !dbg !4001
  %18 = load i32, i32* %nbufs7, align 4, !dbg !4001
  %call8 = call i64 @writev(i32 %13, %struct.iovec* %16, i32 %18), !dbg !4002
  store i64 %call8, i64* %r, align 8, !dbg !4003
  br label %if.end

if.end:                                           ; preds = %if.else, %if.then2
  br label %if.end66, !dbg !4004

if.else9:                                         ; preds = %entry
  %19 = load %struct.uv_fs_s*, %struct.uv_fs_s** %req.addr, align 8, !dbg !4005
  %nbufs10 = getelementptr inbounds %struct.uv_fs_s, %struct.uv_fs_s* %19, i32 0, i32 15, !dbg !4008
  %20 = load i32, i32* %nbufs10, align 4, !dbg !4008
  %cmp11 = icmp eq i32 %20, 1, !dbg !4009
  br i1 %cmp11, label %if.then12, label %if.end22, !dbg !4010

if.then12:                                        ; preds = %if.else9
  %21 = load %struct.uv_fs_s*, %struct.uv_fs_s** %req.addr, align 8, !dbg !4011
  %file13 = getelementptr inbounds %struct.uv_fs_s, %struct.uv_fs_s* %21, i32 0, i32 12, !dbg !4013
  %22 = load i32, i32* %file13, align 8, !dbg !4013
  %23 = load %struct.uv_fs_s*, %struct.uv_fs_s** %req.addr, align 8, !dbg !4014
  %bufs14 = getelementptr inbounds %struct.uv_fs_s, %struct.uv_fs_s* %23, i32 0, i32 16, !dbg !4015
  %24 = load %struct.uv_buf_t*, %struct.uv_buf_t** %bufs14, align 8, !dbg !4015
  %arrayidx15 = getelementptr inbounds %struct.uv_buf_t, %struct.uv_buf_t* %24, i64 0, !dbg !4014
  %base16 = getelementptr inbounds %struct.uv_buf_t, %struct.uv_buf_t* %arrayidx15, i32 0, i32 0, !dbg !4016
  %25 = load i8*, i8** %base16, align 8, !dbg !4016
  %26 = load %struct.uv_fs_s*, %struct.uv_fs_s** %req.addr, align 8, !dbg !4017
  %bufs17 = getelementptr inbounds %struct.uv_fs_s, %struct.uv_fs_s* %26, i32 0, i32 16, !dbg !4018
  %27 = load %struct.uv_buf_t*, %struct.uv_buf_t** %bufs17, align 8, !dbg !4018
  %arrayidx18 = getelementptr inbounds %struct.uv_buf_t, %struct.uv_buf_t* %27, i64 0, !dbg !4017
  %len19 = getelementptr inbounds %struct.uv_buf_t, %struct.uv_buf_t* %arrayidx18, i32 0, i32 1, !dbg !4019
  %28 = load i64, i64* %len19, align 8, !dbg !4019
  %29 = load %struct.uv_fs_s*, %struct.uv_fs_s** %req.addr, align 8, !dbg !4020
  %off20 = getelementptr inbounds %struct.uv_fs_s, %struct.uv_fs_s* %29, i32 0, i32 17, !dbg !4021
  %30 = load i64, i64* %off20, align 8, !dbg !4021
  %call21 = call i64 @pwrite64(i32 %22, i8* %25, i64 %28, i64 %30), !dbg !4022
  store i64 %call21, i64* %r, align 8, !dbg !4023
  br label %done, !dbg !4024

if.end22:                                         ; preds = %if.else9
  %31 = load i32, i32* @uv__fs_write.no_pwritev, align 4, !dbg !4025
  %tobool = icmp ne i32 %31, 0, !dbg !4025
  br i1 %tobool, label %if.then23, label %if.else52, !dbg !4027

if.then23:                                        ; preds = %if.end22
  br label %retry, !dbg !4028

retry:                                            ; preds = %if.then63, %if.then23
  call void @llvm.dbg.declare(metadata i64* %written, metadata !4030, metadata !580), !dbg !4032
  call void @llvm.dbg.declare(metadata i64* %index, metadata !4033, metadata !580), !dbg !4034
  store i64 0, i64* %written, align 8, !dbg !4035
  store i64 0, i64* %index, align 8, !dbg !4036
  store i64 0, i64* %r, align 8, !dbg !4037
  br label %do.body, !dbg !4038

do.body:                                          ; preds = %land.end, %retry
  %32 = load i64, i64* %index, align 8, !dbg !4039
  %33 = load %struct.uv_fs_s*, %struct.uv_fs_s** %req.addr, align 8, !dbg !4042
  %bufs24 = getelementptr inbounds %struct.uv_fs_s, %struct.uv_fs_s* %33, i32 0, i32 16, !dbg !4043
  %34 = load %struct.uv_buf_t*, %struct.uv_buf_t** %bufs24, align 8, !dbg !4043
  %arrayidx25 = getelementptr inbounds %struct.uv_buf_t, %struct.uv_buf_t* %34, i64 %32, !dbg !4042
  %len26 = getelementptr inbounds %struct.uv_buf_t, %struct.uv_buf_t* %arrayidx25, i32 0, i32 1, !dbg !4044
  %35 = load i64, i64* %len26, align 8, !dbg !4044
  %cmp27 = icmp ugt i64 %35, 0, !dbg !4045
  br i1 %cmp27, label %if.then28, label %if.end42, !dbg !4046

if.then28:                                        ; preds = %do.body
  %36 = load %struct.uv_fs_s*, %struct.uv_fs_s** %req.addr, align 8, !dbg !4047
  %file29 = getelementptr inbounds %struct.uv_fs_s, %struct.uv_fs_s* %36, i32 0, i32 12, !dbg !4049
  %37 = load i32, i32* %file29, align 8, !dbg !4049
  %38 = load i64, i64* %index, align 8, !dbg !4050
  %39 = load %struct.uv_fs_s*, %struct.uv_fs_s** %req.addr, align 8, !dbg !4051
  %bufs30 = getelementptr inbounds %struct.uv_fs_s, %struct.uv_fs_s* %39, i32 0, i32 16, !dbg !4052
  %40 = load %struct.uv_buf_t*, %struct.uv_buf_t** %bufs30, align 8, !dbg !4052
  %arrayidx31 = getelementptr inbounds %struct.uv_buf_t, %struct.uv_buf_t* %40, i64 %38, !dbg !4051
  %base32 = getelementptr inbounds %struct.uv_buf_t, %struct.uv_buf_t* %arrayidx31, i32 0, i32 0, !dbg !4053
  %41 = load i8*, i8** %base32, align 8, !dbg !4053
  %42 = load i64, i64* %index, align 8, !dbg !4054
  %43 = load %struct.uv_fs_s*, %struct.uv_fs_s** %req.addr, align 8, !dbg !4055
  %bufs33 = getelementptr inbounds %struct.uv_fs_s, %struct.uv_fs_s* %43, i32 0, i32 16, !dbg !4056
  %44 = load %struct.uv_buf_t*, %struct.uv_buf_t** %bufs33, align 8, !dbg !4056
  %arrayidx34 = getelementptr inbounds %struct.uv_buf_t, %struct.uv_buf_t* %44, i64 %42, !dbg !4055
  %len35 = getelementptr inbounds %struct.uv_buf_t, %struct.uv_buf_t* %arrayidx34, i32 0, i32 1, !dbg !4057
  %45 = load i64, i64* %len35, align 8, !dbg !4057
  %46 = load %struct.uv_fs_s*, %struct.uv_fs_s** %req.addr, align 8, !dbg !4058
  %off36 = getelementptr inbounds %struct.uv_fs_s, %struct.uv_fs_s* %46, i32 0, i32 17, !dbg !4059
  %47 = load i64, i64* %off36, align 8, !dbg !4059
  %48 = load i64, i64* %written, align 8, !dbg !4060
  %add = add nsw i64 %47, %48, !dbg !4061
  %call37 = call i64 @pwrite64(i32 %37, i8* %41, i64 %45, i64 %add), !dbg !4062
  store i64 %call37, i64* %r, align 8, !dbg !4063
  %49 = load i64, i64* %r, align 8, !dbg !4064
  %cmp38 = icmp sgt i64 %49, 0, !dbg !4066
  br i1 %cmp38, label %if.then39, label %if.end41, !dbg !4067

if.then39:                                        ; preds = %if.then28
  %50 = load i64, i64* %r, align 8, !dbg !4068
  %51 = load i64, i64* %written, align 8, !dbg !4069
  %add40 = add nsw i64 %51, %50, !dbg !4069
  store i64 %add40, i64* %written, align 8, !dbg !4069
  br label %if.end41, !dbg !4070

if.end41:                                         ; preds = %if.then39, %if.then28
  br label %if.end42, !dbg !4071

if.end42:                                         ; preds = %if.end41, %do.body
  %52 = load i64, i64* %index, align 8, !dbg !4072
  %inc = add i64 %52, 1, !dbg !4072
  store i64 %inc, i64* %index, align 8, !dbg !4072
  br label %do.cond, !dbg !4073

do.cond:                                          ; preds = %if.end42
  %53 = load i64, i64* %index, align 8, !dbg !4074
  %54 = load %struct.uv_fs_s*, %struct.uv_fs_s** %req.addr, align 8, !dbg !4076
  %nbufs43 = getelementptr inbounds %struct.uv_fs_s, %struct.uv_fs_s* %54, i32 0, i32 15, !dbg !4077
  %55 = load i32, i32* %nbufs43, align 4, !dbg !4077
  %conv = zext i32 %55 to i64, !dbg !4076
  %cmp44 = icmp ult i64 %53, %conv, !dbg !4078
  br i1 %cmp44, label %land.rhs, label %land.end, !dbg !4079

land.rhs:                                         ; preds = %do.cond
  %56 = load i64, i64* %r, align 8, !dbg !4080
  %cmp46 = icmp sge i64 %56, 0, !dbg !4082
  br label %land.end

land.end:                                         ; preds = %land.rhs, %do.cond
  %57 = phi i1 [ false, %do.cond ], [ %cmp46, %land.rhs ]
  br i1 %57, label %do.body, label %do.end, !dbg !4083

do.end:                                           ; preds = %land.end
  %58 = load i64, i64* %written, align 8, !dbg !4085
  %cmp48 = icmp sgt i64 %58, 0, !dbg !4087
  br i1 %cmp48, label %if.then50, label %if.end51, !dbg !4088

if.then50:                                        ; preds = %do.end
  %59 = load i64, i64* %written, align 8, !dbg !4089
  store i64 %59, i64* %r, align 8, !dbg !4090
  br label %if.end51, !dbg !4091

if.end51:                                         ; preds = %if.then50, %do.end
  br label %if.end65, !dbg !4092

if.else52:                                        ; preds = %if.end22
  %60 = load %struct.uv_fs_s*, %struct.uv_fs_s** %req.addr, align 8, !dbg !4093
  %file53 = getelementptr inbounds %struct.uv_fs_s, %struct.uv_fs_s* %60, i32 0, i32 12, !dbg !4095
  %61 = load i32, i32* %file53, align 8, !dbg !4095
  %62 = load %struct.uv_fs_s*, %struct.uv_fs_s** %req.addr, align 8, !dbg !4096
  %bufs54 = getelementptr inbounds %struct.uv_fs_s, %struct.uv_fs_s* %62, i32 0, i32 16, !dbg !4097
  %63 = load %struct.uv_buf_t*, %struct.uv_buf_t** %bufs54, align 8, !dbg !4097
  %64 = bitcast %struct.uv_buf_t* %63 to %struct.iovec*, !dbg !4098
  %65 = load %struct.uv_fs_s*, %struct.uv_fs_s** %req.addr, align 8, !dbg !4099
  %nbufs55 = getelementptr inbounds %struct.uv_fs_s, %struct.uv_fs_s* %65, i32 0, i32 15, !dbg !4100
  %66 = load i32, i32* %nbufs55, align 4, !dbg !4100
  %67 = load %struct.uv_fs_s*, %struct.uv_fs_s** %req.addr, align 8, !dbg !4101
  %off56 = getelementptr inbounds %struct.uv_fs_s, %struct.uv_fs_s* %67, i32 0, i32 17, !dbg !4102
  %68 = load i64, i64* %off56, align 8, !dbg !4102
  %call57 = call i64 @uv__pwritev(i32 %61, %struct.iovec* %64, i32 %66, i64 %68), !dbg !4103
  store i64 %call57, i64* %r, align 8, !dbg !4104
  %69 = load i64, i64* %r, align 8, !dbg !4105
  %cmp58 = icmp eq i64 %69, -1, !dbg !4107
  br i1 %cmp58, label %land.lhs.true, label %if.end64, !dbg !4108

land.lhs.true:                                    ; preds = %if.else52
  %call60 = call i32* @__errno_location() #1, !dbg !4109
  %70 = load i32, i32* %call60, align 4, !dbg !4109
  %cmp61 = icmp eq i32 %70, 38, !dbg !4111
  br i1 %cmp61, label %if.then63, label %if.end64, !dbg !4112

if.then63:                                        ; preds = %land.lhs.true
  store i32 1, i32* @uv__fs_write.no_pwritev, align 4, !dbg !4113
  br label %retry, !dbg !4115

if.end64:                                         ; preds = %land.lhs.true, %if.else52
  br label %if.end65

if.end65:                                         ; preds = %if.end64, %if.end51
  br label %if.end66

if.end66:                                         ; preds = %if.end65, %if.end
  br label %done, !dbg !4116

done:                                             ; preds = %if.end66, %if.then12
  %71 = load i64, i64* %r, align 8, !dbg !4118
  ret i64 %71, !dbg !4119
}

; Function Attrs: noreturn nounwind
declare void @abort() #2

declare i32 @fdatasync(i32) #3

; Function Attrs: nounwind
declare i32 @fstat64(i32, %struct.stat*) #7

; Function Attrs: nounwind uwtable
define internal void @uv__to_stat(%struct.stat* %src, %struct.uv_stat_t* %dst) #0 !dbg !484 {
entry:
  %src.addr = alloca %struct.stat*, align 8
  %dst.addr = alloca %struct.uv_stat_t*, align 8
  store %struct.stat* %src, %struct.stat** %src.addr, align 8
  call void @llvm.dbg.declare(metadata %struct.stat** %src.addr, metadata !4120, metadata !580), !dbg !4121
  store %struct.uv_stat_t* %dst, %struct.uv_stat_t** %dst.addr, align 8
  call void @llvm.dbg.declare(metadata %struct.uv_stat_t** %dst.addr, metadata !4122, metadata !580), !dbg !4123
  %0 = load %struct.stat*, %struct.stat** %src.addr, align 8, !dbg !4124
  %st_dev = getelementptr inbounds %struct.stat, %struct.stat* %0, i32 0, i32 0, !dbg !4125
  %1 = load i64, i64* %st_dev, align 8, !dbg !4125
  %2 = load %struct.uv_stat_t*, %struct.uv_stat_t** %dst.addr, align 8, !dbg !4126
  %st_dev1 = getelementptr inbounds %struct.uv_stat_t, %struct.uv_stat_t* %2, i32 0, i32 0, !dbg !4127
  store i64 %1, i64* %st_dev1, align 8, !dbg !4128
  %3 = load %struct.stat*, %struct.stat** %src.addr, align 8, !dbg !4129
  %st_mode = getelementptr inbounds %struct.stat, %struct.stat* %3, i32 0, i32 3, !dbg !4130
  %4 = load i32, i32* %st_mode, align 8, !dbg !4130
  %conv = zext i32 %4 to i64, !dbg !4129
  %5 = load %struct.uv_stat_t*, %struct.uv_stat_t** %dst.addr, align 8, !dbg !4131
  %st_mode2 = getelementptr inbounds %struct.uv_stat_t, %struct.uv_stat_t* %5, i32 0, i32 1, !dbg !4132
  store i64 %conv, i64* %st_mode2, align 8, !dbg !4133
  %6 = load %struct.stat*, %struct.stat** %src.addr, align 8, !dbg !4134
  %st_nlink = getelementptr inbounds %struct.stat, %struct.stat* %6, i32 0, i32 2, !dbg !4135
  %7 = load i64, i64* %st_nlink, align 8, !dbg !4135
  %8 = load %struct.uv_stat_t*, %struct.uv_stat_t** %dst.addr, align 8, !dbg !4136
  %st_nlink3 = getelementptr inbounds %struct.uv_stat_t, %struct.uv_stat_t* %8, i32 0, i32 2, !dbg !4137
  store i64 %7, i64* %st_nlink3, align 8, !dbg !4138
  %9 = load %struct.stat*, %struct.stat** %src.addr, align 8, !dbg !4139
  %st_uid = getelementptr inbounds %struct.stat, %struct.stat* %9, i32 0, i32 4, !dbg !4140
  %10 = load i32, i32* %st_uid, align 4, !dbg !4140
  %conv4 = zext i32 %10 to i64, !dbg !4139
  %11 = load %struct.uv_stat_t*, %struct.uv_stat_t** %dst.addr, align 8, !dbg !4141
  %st_uid5 = getelementptr inbounds %struct.uv_stat_t, %struct.uv_stat_t* %11, i32 0, i32 3, !dbg !4142
  store i64 %conv4, i64* %st_uid5, align 8, !dbg !4143
  %12 = load %struct.stat*, %struct.stat** %src.addr, align 8, !dbg !4144
  %st_gid = getelementptr inbounds %struct.stat, %struct.stat* %12, i32 0, i32 5, !dbg !4145
  %13 = load i32, i32* %st_gid, align 8, !dbg !4145
  %conv6 = zext i32 %13 to i64, !dbg !4144
  %14 = load %struct.uv_stat_t*, %struct.uv_stat_t** %dst.addr, align 8, !dbg !4146
  %st_gid7 = getelementptr inbounds %struct.uv_stat_t, %struct.uv_stat_t* %14, i32 0, i32 4, !dbg !4147
  store i64 %conv6, i64* %st_gid7, align 8, !dbg !4148
  %15 = load %struct.stat*, %struct.stat** %src.addr, align 8, !dbg !4149
  %st_rdev = getelementptr inbounds %struct.stat, %struct.stat* %15, i32 0, i32 7, !dbg !4150
  %16 = load i64, i64* %st_rdev, align 8, !dbg !4150
  %17 = load %struct.uv_stat_t*, %struct.uv_stat_t** %dst.addr, align 8, !dbg !4151
  %st_rdev8 = getelementptr inbounds %struct.uv_stat_t, %struct.uv_stat_t* %17, i32 0, i32 5, !dbg !4152
  store i64 %16, i64* %st_rdev8, align 8, !dbg !4153
  %18 = load %struct.stat*, %struct.stat** %src.addr, align 8, !dbg !4154
  %st_ino = getelementptr inbounds %struct.stat, %struct.stat* %18, i32 0, i32 1, !dbg !4155
  %19 = load i64, i64* %st_ino, align 8, !dbg !4155
  %20 = load %struct.uv_stat_t*, %struct.uv_stat_t** %dst.addr, align 8, !dbg !4156
  %st_ino9 = getelementptr inbounds %struct.uv_stat_t, %struct.uv_stat_t* %20, i32 0, i32 6, !dbg !4157
  store i64 %19, i64* %st_ino9, align 8, !dbg !4158
  %21 = load %struct.stat*, %struct.stat** %src.addr, align 8, !dbg !4159
  %st_size = getelementptr inbounds %struct.stat, %struct.stat* %21, i32 0, i32 8, !dbg !4160
  %22 = load i64, i64* %st_size, align 8, !dbg !4160
  %23 = load %struct.uv_stat_t*, %struct.uv_stat_t** %dst.addr, align 8, !dbg !4161
  %st_size10 = getelementptr inbounds %struct.uv_stat_t, %struct.uv_stat_t* %23, i32 0, i32 7, !dbg !4162
  store i64 %22, i64* %st_size10, align 8, !dbg !4163
  %24 = load %struct.stat*, %struct.stat** %src.addr, align 8, !dbg !4164
  %st_blksize = getelementptr inbounds %struct.stat, %struct.stat* %24, i32 0, i32 9, !dbg !4165
  %25 = load i64, i64* %st_blksize, align 8, !dbg !4165
  %26 = load %struct.uv_stat_t*, %struct.uv_stat_t** %dst.addr, align 8, !dbg !4166
  %st_blksize11 = getelementptr inbounds %struct.uv_stat_t, %struct.uv_stat_t* %26, i32 0, i32 8, !dbg !4167
  store i64 %25, i64* %st_blksize11, align 8, !dbg !4168
  %27 = load %struct.stat*, %struct.stat** %src.addr, align 8, !dbg !4169
  %st_blocks = getelementptr inbounds %struct.stat, %struct.stat* %27, i32 0, i32 10, !dbg !4170
  %28 = load i64, i64* %st_blocks, align 8, !dbg !4170
  %29 = load %struct.uv_stat_t*, %struct.uv_stat_t** %dst.addr, align 8, !dbg !4171
  %st_blocks12 = getelementptr inbounds %struct.uv_stat_t, %struct.uv_stat_t* %29, i32 0, i32 9, !dbg !4172
  store i64 %28, i64* %st_blocks12, align 8, !dbg !4173
  %30 = load %struct.stat*, %struct.stat** %src.addr, align 8, !dbg !4174
  %st_atim = getelementptr inbounds %struct.stat, %struct.stat* %30, i32 0, i32 11, !dbg !4175
  %tv_sec = getelementptr inbounds %struct.timespec, %struct.timespec* %st_atim, i32 0, i32 0, !dbg !4176
  %31 = load i64, i64* %tv_sec, align 8, !dbg !4176
  %32 = load %struct.uv_stat_t*, %struct.uv_stat_t** %dst.addr, align 8, !dbg !4177
  %st_atim13 = getelementptr inbounds %struct.uv_stat_t, %struct.uv_stat_t* %32, i32 0, i32 12, !dbg !4178
  %tv_sec14 = getelementptr inbounds %struct.uv_timespec_t, %struct.uv_timespec_t* %st_atim13, i32 0, i32 0, !dbg !4179
  store i64 %31, i64* %tv_sec14, align 8, !dbg !4180
  %33 = load %struct.stat*, %struct.stat** %src.addr, align 8, !dbg !4181
  %st_atim15 = getelementptr inbounds %struct.stat, %struct.stat* %33, i32 0, i32 11, !dbg !4182
  %tv_nsec = getelementptr inbounds %struct.timespec, %struct.timespec* %st_atim15, i32 0, i32 1, !dbg !4183
  %34 = load i64, i64* %tv_nsec, align 8, !dbg !4183
  %35 = load %struct.uv_stat_t*, %struct.uv_stat_t** %dst.addr, align 8, !dbg !4184
  %st_atim16 = getelementptr inbounds %struct.uv_stat_t, %struct.uv_stat_t* %35, i32 0, i32 12, !dbg !4185
  %tv_nsec17 = getelementptr inbounds %struct.uv_timespec_t, %struct.uv_timespec_t* %st_atim16, i32 0, i32 1, !dbg !4186
  store i64 %34, i64* %tv_nsec17, align 8, !dbg !4187
  %36 = load %struct.stat*, %struct.stat** %src.addr, align 8, !dbg !4188
  %st_mtim = getelementptr inbounds %struct.stat, %struct.stat* %36, i32 0, i32 12, !dbg !4189
  %tv_sec18 = getelementptr inbounds %struct.timespec, %struct.timespec* %st_mtim, i32 0, i32 0, !dbg !4190
  %37 = load i64, i64* %tv_sec18, align 8, !dbg !4190
  %38 = load %struct.uv_stat_t*, %struct.uv_stat_t** %dst.addr, align 8, !dbg !4191
  %st_mtim19 = getelementptr inbounds %struct.uv_stat_t, %struct.uv_stat_t* %38, i32 0, i32 13, !dbg !4192
  %tv_sec20 = getelementptr inbounds %struct.uv_timespec_t, %struct.uv_timespec_t* %st_mtim19, i32 0, i32 0, !dbg !4193
  store i64 %37, i64* %tv_sec20, align 8, !dbg !4194
  %39 = load %struct.stat*, %struct.stat** %src.addr, align 8, !dbg !4195
  %st_mtim21 = getelementptr inbounds %struct.stat, %struct.stat* %39, i32 0, i32 12, !dbg !4196
  %tv_nsec22 = getelementptr inbounds %struct.timespec, %struct.timespec* %st_mtim21, i32 0, i32 1, !dbg !4197
  %40 = load i64, i64* %tv_nsec22, align 8, !dbg !4197
  %41 = load %struct.uv_stat_t*, %struct.uv_stat_t** %dst.addr, align 8, !dbg !4198
  %st_mtim23 = getelementptr inbounds %struct.uv_stat_t, %struct.uv_stat_t* %41, i32 0, i32 13, !dbg !4199
  %tv_nsec24 = getelementptr inbounds %struct.uv_timespec_t, %struct.uv_timespec_t* %st_mtim23, i32 0, i32 1, !dbg !4200
  store i64 %40, i64* %tv_nsec24, align 8, !dbg !4201
  %42 = load %struct.stat*, %struct.stat** %src.addr, align 8, !dbg !4202
  %st_ctim = getelementptr inbounds %struct.stat, %struct.stat* %42, i32 0, i32 13, !dbg !4203
  %tv_sec25 = getelementptr inbounds %struct.timespec, %struct.timespec* %st_ctim, i32 0, i32 0, !dbg !4204
  %43 = load i64, i64* %tv_sec25, align 8, !dbg !4204
  %44 = load %struct.uv_stat_t*, %struct.uv_stat_t** %dst.addr, align 8, !dbg !4205
  %st_ctim26 = getelementptr inbounds %struct.uv_stat_t, %struct.uv_stat_t* %44, i32 0, i32 14, !dbg !4206
  %tv_sec27 = getelementptr inbounds %struct.uv_timespec_t, %struct.uv_timespec_t* %st_ctim26, i32 0, i32 0, !dbg !4207
  store i64 %43, i64* %tv_sec27, align 8, !dbg !4208
  %45 = load %struct.stat*, %struct.stat** %src.addr, align 8, !dbg !4209
  %st_ctim28 = getelementptr inbounds %struct.stat, %struct.stat* %45, i32 0, i32 13, !dbg !4210
  %tv_nsec29 = getelementptr inbounds %struct.timespec, %struct.timespec* %st_ctim28, i32 0, i32 1, !dbg !4211
  %46 = load i64, i64* %tv_nsec29, align 8, !dbg !4211
  %47 = load %struct.uv_stat_t*, %struct.uv_stat_t** %dst.addr, align 8, !dbg !4212
  %st_ctim30 = getelementptr inbounds %struct.uv_stat_t, %struct.uv_stat_t* %47, i32 0, i32 14, !dbg !4213
  %tv_nsec31 = getelementptr inbounds %struct.uv_timespec_t, %struct.uv_timespec_t* %st_ctim30, i32 0, i32 1, !dbg !4214
  store i64 %46, i64* %tv_nsec31, align 8, !dbg !4215
  %48 = load %struct.stat*, %struct.stat** %src.addr, align 8, !dbg !4216
  %st_ctim32 = getelementptr inbounds %struct.stat, %struct.stat* %48, i32 0, i32 13, !dbg !4217
  %tv_sec33 = getelementptr inbounds %struct.timespec, %struct.timespec* %st_ctim32, i32 0, i32 0, !dbg !4218
  %49 = load i64, i64* %tv_sec33, align 8, !dbg !4218
  %50 = load %struct.uv_stat_t*, %struct.uv_stat_t** %dst.addr, align 8, !dbg !4219
  %st_birthtim = getelementptr inbounds %struct.uv_stat_t, %struct.uv_stat_t* %50, i32 0, i32 15, !dbg !4220
  %tv_sec34 = getelementptr inbounds %struct.uv_timespec_t, %struct.uv_timespec_t* %st_birthtim, i32 0, i32 0, !dbg !4221
  store i64 %49, i64* %tv_sec34, align 8, !dbg !4222
  %51 = load %struct.stat*, %struct.stat** %src.addr, align 8, !dbg !4223
  %st_ctim35 = getelementptr inbounds %struct.stat, %struct.stat* %51, i32 0, i32 13, !dbg !4224
  %tv_nsec36 = getelementptr inbounds %struct.timespec, %struct.timespec* %st_ctim35, i32 0, i32 1, !dbg !4225
  %52 = load i64, i64* %tv_nsec36, align 8, !dbg !4225
  %53 = load %struct.uv_stat_t*, %struct.uv_stat_t** %dst.addr, align 8, !dbg !4226
  %st_birthtim37 = getelementptr inbounds %struct.uv_stat_t, %struct.uv_stat_t* %53, i32 0, i32 15, !dbg !4227
  %tv_nsec38 = getelementptr inbounds %struct.uv_timespec_t, %struct.uv_timespec_t* %st_birthtim37, i32 0, i32 1, !dbg !4228
  store i64 %52, i64* %tv_nsec38, align 8, !dbg !4229
  %54 = load %struct.uv_stat_t*, %struct.uv_stat_t** %dst.addr, align 8, !dbg !4230
  %st_flags = getelementptr inbounds %struct.uv_stat_t, %struct.uv_stat_t* %54, i32 0, i32 10, !dbg !4231
  store i64 0, i64* %st_flags, align 8, !dbg !4232
  %55 = load %struct.uv_stat_t*, %struct.uv_stat_t** %dst.addr, align 8, !dbg !4233
  %st_gen = getelementptr inbounds %struct.uv_stat_t, %struct.uv_stat_t* %55, i32 0, i32 11, !dbg !4234
  store i64 0, i64* %st_gen, align 8, !dbg !4235
  ret void, !dbg !4236
}

declare i32 @fsync(i32) #3

declare i32 @uv__utimesat(i32, i8*, %struct.timespec*, i32) #3

; Function Attrs: nounwind
declare i32 @snprintf(i8*, i64, i8*, ...) #7

; Function Attrs: nounwind
declare i32 @utimes(i8*, %struct.timeval*) #7

declare i32 @fcntl(i32, i32, ...) #3

; Function Attrs: nounwind
declare i32 @lstat64(i8*, %struct.stat*) #7

; Function Attrs: nounwind
declare i8* @mkdtemp(i8*) #7

declare i32 @open64(i8*, i32, ...) #3

declare void @uv_rwlock_rdlock(%union.pthread_rwlock_t*) #3

declare i32 @uv__cloexec_ioctl(i32, i32) #3

declare i32 @uv__close(i32) #3

declare void @uv_rwlock_rdunlock(%union.pthread_rwlock_t*) #3

declare i32 @uv__getiovmax() #3

declare i64 @read(i32, i8*, i64) #3

declare i64 @readv(i32, %struct.iovec*, i32) #3

declare i64 @pread64(i32, i8*, i64, i64) #3

declare i64 @uv__preadv(i32, %struct.iovec*, i32, i64) #3

declare i32 @scandir64(i8*, %struct.dirent***, i32 (%struct.dirent*)*, i32 (%struct.dirent**, %struct.dirent**)*) #3

; Function Attrs: nounwind uwtable
define internal i32 @uv__fs_scandir_filter(%struct.dirent* %dent) #0 !dbg !536 {
entry:
  %dent.addr = alloca %struct.dirent*, align 8
  store %struct.dirent* %dent, %struct.dirent** %dent.addr, align 8
  call void @llvm.dbg.declare(metadata %struct.dirent** %dent.addr, metadata !4237, metadata !580), !dbg !4238
  %0 = load %struct.dirent*, %struct.dirent** %dent.addr, align 8, !dbg !4239
  %d_name = getelementptr inbounds %struct.dirent, %struct.dirent* %0, i32 0, i32 4, !dbg !4240
  %arraydecay = getelementptr inbounds [256 x i8], [256 x i8]* %d_name, i32 0, i32 0, !dbg !4239
  %call = call i32 @strcmp(i8* %arraydecay, i8* getelementptr inbounds ([2 x i8], [2 x i8]* @.str.4, i32 0, i32 0)) #10, !dbg !4241
  %cmp = icmp ne i32 %call, 0, !dbg !4242
  br i1 %cmp, label %land.rhs, label %land.end, !dbg !4243

land.rhs:                                         ; preds = %entry
  %1 = load %struct.dirent*, %struct.dirent** %dent.addr, align 8, !dbg !4244
  %d_name1 = getelementptr inbounds %struct.dirent, %struct.dirent* %1, i32 0, i32 4, !dbg !4246
  %arraydecay2 = getelementptr inbounds [256 x i8], [256 x i8]* %d_name1, i32 0, i32 0, !dbg !4244
  %call3 = call i32 @strcmp(i8* %arraydecay2, i8* getelementptr inbounds ([3 x i8], [3 x i8]* @.str.5, i32 0, i32 0)) #10, !dbg !4247
  %cmp4 = icmp ne i32 %call3, 0, !dbg !4248
  br label %land.end

land.end:                                         ; preds = %land.rhs, %entry
  %2 = phi i1 [ false, %entry ], [ %cmp4, %land.rhs ]
  %land.ext = zext i1 %2 to i32, !dbg !4249
  ret i32 %land.ext, !dbg !4251
}

; Function Attrs: nounwind uwtable
define internal i32 @uv__fs_scandir_sort(%struct.dirent** %a, %struct.dirent** %b) #0 !dbg !556 {
entry:
  %a.addr = alloca %struct.dirent**, align 8
  %b.addr = alloca %struct.dirent**, align 8
  store %struct.dirent** %a, %struct.dirent*** %a.addr, align 8
  call void @llvm.dbg.declare(metadata %struct.dirent*** %a.addr, metadata !4252, metadata !580), !dbg !4253
  store %struct.dirent** %b, %struct.dirent*** %b.addr, align 8
  call void @llvm.dbg.declare(metadata %struct.dirent*** %b.addr, metadata !4254, metadata !580), !dbg !4255
  %0 = load %struct.dirent**, %struct.dirent*** %a.addr, align 8, !dbg !4256
  %1 = load %struct.dirent*, %struct.dirent** %0, align 8, !dbg !4257
  %d_name = getelementptr inbounds %struct.dirent, %struct.dirent* %1, i32 0, i32 4, !dbg !4258
  %arraydecay = getelementptr inbounds [256 x i8], [256 x i8]* %d_name, i32 0, i32 0, !dbg !4259
  %2 = load %struct.dirent**, %struct.dirent*** %b.addr, align 8, !dbg !4260
  %3 = load %struct.dirent*, %struct.dirent** %2, align 8, !dbg !4261
  %d_name1 = getelementptr inbounds %struct.dirent, %struct.dirent* %3, i32 0, i32 4, !dbg !4262
  %arraydecay2 = getelementptr inbounds [256 x i8], [256 x i8]* %d_name1, i32 0, i32 0, !dbg !4263
  %call = call i32 @strcmp(i8* %arraydecay, i8* %arraydecay2) #10, !dbg !4264
  ret i32 %call, !dbg !4265
}

; Function Attrs: nounwind
declare void @free(i8*) #7

; Function Attrs: nounwind readonly
declare i32 @strcmp(i8*, i8*) #4

; Function Attrs: nounwind uwtable
define internal i64 @uv__fs_pathmax_size(i8* %path) #0 !dbg !561 {
entry:
  %retval = alloca i64, align 8
  %path.addr = alloca i8*, align 8
  %pathmax = alloca i64, align 8
  store i8* %path, i8** %path.addr, align 8
  call void @llvm.dbg.declare(metadata i8** %path.addr, metadata !4266, metadata !580), !dbg !4267
  call void @llvm.dbg.declare(metadata i64* %pathmax, metadata !4268, metadata !580), !dbg !4269
  %0 = load i8*, i8** %path.addr, align 8, !dbg !4270
  %call = call i64 @pathconf(i8* %0, i32 4) #9, !dbg !4271
  store i64 %call, i64* %pathmax, align 8, !dbg !4272
  %1 = load i64, i64* %pathmax, align 8, !dbg !4273
  %cmp = icmp eq i64 %1, -1, !dbg !4275
  br i1 %cmp, label %if.then, label %if.end, !dbg !4276

if.then:                                          ; preds = %entry
  store i64 4096, i64* %retval, align 8, !dbg !4277
  br label %return, !dbg !4277

if.end:                                           ; preds = %entry
  %2 = load i64, i64* %pathmax, align 8, !dbg !4279
  store i64 %2, i64* %retval, align 8, !dbg !4280
  br label %return, !dbg !4280

return:                                           ; preds = %if.end, %if.then
  %3 = load i64, i64* %retval, align 8, !dbg !4281
  ret i64 %3, !dbg !4281
}

; Function Attrs: nounwind
declare i64 @readlink(i8*, i8*, i64) #7

; Function Attrs: nounwind
declare i64 @pathconf(i8*, i32) #7

; Function Attrs: nounwind
declare i8* @realpath(i8*, i8*) #7

; Function Attrs: nounwind
declare i64 @sendfile64(i32, i32, i64*, i64) #7

; Function Attrs: nounwind uwtable
define internal i64 @uv__fs_sendfile_emul(%struct.uv_fs_s* %req) #0 !dbg !566 {
entry:
  %req.addr = alloca %struct.uv_fs_s*, align 8
  %pfd = alloca %struct.pollfd, align 4
  %use_pread = alloca i32, align 4
  %offset = alloca i64, align 8
  %nsent = alloca i64, align 8
  %nread = alloca i64, align 8
  %nwritten = alloca i64, align 8
  %buflen = alloca i64, align 8
  %len = alloca i64, align 8
  %n = alloca i64, align 8
  %in_fd = alloca i32, align 4
  %out_fd = alloca i32, align 4
  %buf = alloca [8192 x i8], align 16
  store %struct.uv_fs_s* %req, %struct.uv_fs_s** %req.addr, align 8
  call void @llvm.dbg.declare(metadata %struct.uv_fs_s** %req.addr, metadata !4282, metadata !580), !dbg !4283
  call void @llvm.dbg.declare(metadata %struct.pollfd* %pfd, metadata !4284, metadata !580), !dbg !4291
  call void @llvm.dbg.declare(metadata i32* %use_pread, metadata !4292, metadata !580), !dbg !4293
  call void @llvm.dbg.declare(metadata i64* %offset, metadata !4294, metadata !580), !dbg !4295
  call void @llvm.dbg.declare(metadata i64* %nsent, metadata !4296, metadata !580), !dbg !4297
  call void @llvm.dbg.declare(metadata i64* %nread, metadata !4298, metadata !580), !dbg !4299
  call void @llvm.dbg.declare(metadata i64* %nwritten, metadata !4300, metadata !580), !dbg !4301
  call void @llvm.dbg.declare(metadata i64* %buflen, metadata !4302, metadata !580), !dbg !4303
  call void @llvm.dbg.declare(metadata i64* %len, metadata !4304, metadata !580), !dbg !4305
  call void @llvm.dbg.declare(metadata i64* %n, metadata !4306, metadata !580), !dbg !4307
  call void @llvm.dbg.declare(metadata i32* %in_fd, metadata !4308, metadata !580), !dbg !4309
  call void @llvm.dbg.declare(metadata i32* %out_fd, metadata !4310, metadata !580), !dbg !4311
  call void @llvm.dbg.declare(metadata [8192 x i8]* %buf, metadata !4312, metadata !580), !dbg !4316
  %0 = load %struct.uv_fs_s*, %struct.uv_fs_s** %req.addr, align 8, !dbg !4317
  %bufsml = getelementptr inbounds %struct.uv_fs_s, %struct.uv_fs_s* %0, i32 0, i32 23, !dbg !4318
  %arrayidx = getelementptr inbounds [4 x %struct.uv_buf_t], [4 x %struct.uv_buf_t]* %bufsml, i64 0, i64 0, !dbg !4317
  %len1 = getelementptr inbounds %struct.uv_buf_t, %struct.uv_buf_t* %arrayidx, i32 0, i32 1, !dbg !4319
  %1 = load i64, i64* %len1, align 8, !dbg !4319
  store i64 %1, i64* %len, align 8, !dbg !4320
  %2 = load %struct.uv_fs_s*, %struct.uv_fs_s** %req.addr, align 8, !dbg !4321
  %flags = getelementptr inbounds %struct.uv_fs_s, %struct.uv_fs_s* %2, i32 0, i32 13, !dbg !4322
  %3 = load i32, i32* %flags, align 4, !dbg !4322
  store i32 %3, i32* %in_fd, align 4, !dbg !4323
  %4 = load %struct.uv_fs_s*, %struct.uv_fs_s** %req.addr, align 8, !dbg !4324
  %file = getelementptr inbounds %struct.uv_fs_s, %struct.uv_fs_s* %4, i32 0, i32 12, !dbg !4325
  %5 = load i32, i32* %file, align 8, !dbg !4325
  store i32 %5, i32* %out_fd, align 4, !dbg !4326
  %6 = load %struct.uv_fs_s*, %struct.uv_fs_s** %req.addr, align 8, !dbg !4327
  %off = getelementptr inbounds %struct.uv_fs_s, %struct.uv_fs_s* %6, i32 0, i32 17, !dbg !4328
  %7 = load i64, i64* %off, align 8, !dbg !4328
  store i64 %7, i64* %offset, align 8, !dbg !4329
  store i32 1, i32* %use_pread, align 4, !dbg !4330
  store i64 0, i64* %nsent, align 8, !dbg !4331
  br label %for.cond, !dbg !4333

for.cond:                                         ; preds = %for.end, %if.then22, %entry
  %8 = load i64, i64* %nsent, align 8, !dbg !4334
  %9 = load i64, i64* %len, align 8, !dbg !4337
  %cmp = icmp ult i64 %8, %9, !dbg !4338
  br i1 %cmp, label %for.body, label %for.end75, !dbg !4339

for.body:                                         ; preds = %for.cond
  %10 = load i64, i64* %len, align 8, !dbg !4340
  %11 = load i64, i64* %nsent, align 8, !dbg !4342
  %sub = sub i64 %10, %11, !dbg !4343
  store i64 %sub, i64* %buflen, align 8, !dbg !4344
  %12 = load i64, i64* %buflen, align 8, !dbg !4345
  %cmp2 = icmp ugt i64 %12, 8192, !dbg !4347
  br i1 %cmp2, label %if.then, label %if.end, !dbg !4348

if.then:                                          ; preds = %for.body
  store i64 8192, i64* %buflen, align 8, !dbg !4349
  br label %if.end, !dbg !4350

if.end:                                           ; preds = %if.then, %for.body
  br label %do.body, !dbg !4351

do.body:                                          ; preds = %land.end, %if.end
  %13 = load i32, i32* %use_pread, align 4, !dbg !4352
  %tobool = icmp ne i32 %13, 0, !dbg !4352
  br i1 %tobool, label %if.then3, label %if.else, !dbg !4354

if.then3:                                         ; preds = %do.body
  %14 = load i32, i32* %in_fd, align 4, !dbg !4355
  %arraydecay = getelementptr inbounds [8192 x i8], [8192 x i8]* %buf, i32 0, i32 0, !dbg !4356
  %15 = load i64, i64* %buflen, align 8, !dbg !4357
  %16 = load i64, i64* %offset, align 8, !dbg !4358
  %call = call i64 @pread64(i32 %14, i8* %arraydecay, i64 %15, i64 %16), !dbg !4359
  store i64 %call, i64* %nread, align 8, !dbg !4360
  br label %if.end6, !dbg !4361

if.else:                                          ; preds = %do.body
  %17 = load i32, i32* %in_fd, align 4, !dbg !4362
  %arraydecay4 = getelementptr inbounds [8192 x i8], [8192 x i8]* %buf, i32 0, i32 0, !dbg !4363
  %18 = load i64, i64* %buflen, align 8, !dbg !4364
  %call5 = call i64 @read(i32 %17, i8* %arraydecay4, i64 %18), !dbg !4365
  store i64 %call5, i64* %nread, align 8, !dbg !4366
  br label %if.end6

if.end6:                                          ; preds = %if.else, %if.then3
  br label %do.cond, !dbg !4367

do.cond:                                          ; preds = %if.end6
  %19 = load i64, i64* %nread, align 8, !dbg !4369
  %cmp7 = icmp eq i64 %19, -1, !dbg !4370
  br i1 %cmp7, label %land.rhs, label %land.end, !dbg !4371

land.rhs:                                         ; preds = %do.cond
  %call8 = call i32* @__errno_location() #1, !dbg !4372
  %20 = load i32, i32* %call8, align 4, !dbg !4372
  %cmp9 = icmp eq i32 %20, 4, !dbg !4374
  br label %land.end

land.end:                                         ; preds = %land.rhs, %do.cond
  %21 = phi i1 [ false, %do.cond ], [ %cmp9, %land.rhs ]
  br i1 %21, label %do.body, label %do.end, !dbg !4375

do.end:                                           ; preds = %land.end
  %22 = load i64, i64* %nread, align 8, !dbg !4377
  %cmp10 = icmp eq i64 %22, 0, !dbg !4379
  br i1 %cmp10, label %if.then11, label %if.end12, !dbg !4380

if.then11:                                        ; preds = %do.end
  br label %out, !dbg !4381

if.end12:                                         ; preds = %do.end
  %23 = load i64, i64* %nread, align 8, !dbg !4382
  %cmp13 = icmp eq i64 %23, -1, !dbg !4384
  br i1 %cmp13, label %if.then14, label %if.end27, !dbg !4385

if.then14:                                        ; preds = %if.end12
  %24 = load i32, i32* %use_pread, align 4, !dbg !4386
  %tobool15 = icmp ne i32 %24, 0, !dbg !4386
  br i1 %tobool15, label %land.lhs.true, label %if.end23, !dbg !4389

land.lhs.true:                                    ; preds = %if.then14
  %25 = load i64, i64* %nsent, align 8, !dbg !4390
  %cmp16 = icmp eq i64 %25, 0, !dbg !4392
  br i1 %cmp16, label %land.lhs.true17, label %if.end23, !dbg !4393

land.lhs.true17:                                  ; preds = %land.lhs.true
  %call18 = call i32* @__errno_location() #1, !dbg !4394
  %26 = load i32, i32* %call18, align 4, !dbg !4394
  %cmp19 = icmp eq i32 %26, 5, !dbg !4396
  br i1 %cmp19, label %if.then22, label %lor.lhs.false, !dbg !4397

lor.lhs.false:                                    ; preds = %land.lhs.true17
  %call20 = call i32* @__errno_location() #1, !dbg !4398
  %27 = load i32, i32* %call20, align 4, !dbg !4398
  %cmp21 = icmp eq i32 %27, 29, !dbg !4400
  br i1 %cmp21, label %if.then22, label %if.end23, !dbg !4401

if.then22:                                        ; preds = %lor.lhs.false, %land.lhs.true17
  store i32 0, i32* %use_pread, align 4, !dbg !4402
  br label %for.cond, !dbg !4404

if.end23:                                         ; preds = %lor.lhs.false, %land.lhs.true, %if.then14
  %28 = load i64, i64* %nsent, align 8, !dbg !4405
  %cmp24 = icmp eq i64 %28, 0, !dbg !4407
  br i1 %cmp24, label %if.then25, label %if.end26, !dbg !4408

if.then25:                                        ; preds = %if.end23
  store i64 -1, i64* %nsent, align 8, !dbg !4409
  br label %if.end26, !dbg !4410

if.end26:                                         ; preds = %if.then25, %if.end23
  br label %out, !dbg !4411

if.end27:                                         ; preds = %if.end12
  store i64 0, i64* %nwritten, align 8, !dbg !4412
  br label %for.cond28, !dbg !4414

for.cond28:                                       ; preds = %if.end72, %if.then43, %if.end27
  %29 = load i64, i64* %nwritten, align 8, !dbg !4415
  %30 = load i64, i64* %nread, align 8, !dbg !4418
  %cmp29 = icmp slt i64 %29, %30, !dbg !4419
  br i1 %cmp29, label %for.body30, label %for.end, !dbg !4420

for.body30:                                       ; preds = %for.cond28
  br label %do.body31, !dbg !4421

do.body31:                                        ; preds = %land.end40, %for.body30
  %31 = load i32, i32* %out_fd, align 4, !dbg !4423
  %arraydecay32 = getelementptr inbounds [8192 x i8], [8192 x i8]* %buf, i32 0, i32 0, !dbg !4424
  %32 = load i64, i64* %nwritten, align 8, !dbg !4425
  %add.ptr = getelementptr inbounds i8, i8* %arraydecay32, i64 %32, !dbg !4426
  %33 = load i64, i64* %nread, align 8, !dbg !4427
  %34 = load i64, i64* %nwritten, align 8, !dbg !4428
  %sub33 = sub nsw i64 %33, %34, !dbg !4429
  %call34 = call i64 @write(i32 %31, i8* %add.ptr, i64 %sub33), !dbg !4430
  store i64 %call34, i64* %n, align 8, !dbg !4431
  br label %do.cond35, !dbg !4432

do.cond35:                                        ; preds = %do.body31
  %35 = load i64, i64* %n, align 8, !dbg !4433
  %cmp36 = icmp eq i64 %35, -1, !dbg !4434
  br i1 %cmp36, label %land.rhs37, label %land.end40, !dbg !4435

land.rhs37:                                       ; preds = %do.cond35
  %call38 = call i32* @__errno_location() #1, !dbg !4436
  %36 = load i32, i32* %call38, align 4, !dbg !4436
  %cmp39 = icmp eq i32 %36, 4, !dbg !4438
  br label %land.end40

land.end40:                                       ; preds = %land.rhs37, %do.cond35
  %37 = phi i1 [ false, %do.cond35 ], [ %cmp39, %land.rhs37 ]
  br i1 %37, label %do.body31, label %do.end41, !dbg !4439

do.end41:                                         ; preds = %land.end40
  %38 = load i64, i64* %n, align 8, !dbg !4440
  %cmp42 = icmp ne i64 %38, -1, !dbg !4442
  br i1 %cmp42, label %if.then43, label %if.end44, !dbg !4443

if.then43:                                        ; preds = %do.end41
  %39 = load i64, i64* %n, align 8, !dbg !4444
  %40 = load i64, i64* %nwritten, align 8, !dbg !4446
  %add = add nsw i64 %40, %39, !dbg !4446
  store i64 %add, i64* %nwritten, align 8, !dbg !4446
  br label %for.cond28, !dbg !4447

if.end44:                                         ; preds = %do.end41
  %call45 = call i32* @__errno_location() #1, !dbg !4448
  %41 = load i32, i32* %call45, align 4, !dbg !4448
  %cmp46 = icmp ne i32 %41, 11, !dbg !4450
  br i1 %cmp46, label %land.lhs.true47, label %if.end51, !dbg !4451

land.lhs.true47:                                  ; preds = %if.end44
  %call48 = call i32* @__errno_location() #1, !dbg !4452
  %42 = load i32, i32* %call48, align 4, !dbg !4452
  %cmp49 = icmp ne i32 %42, 11, !dbg !4454
  br i1 %cmp49, label %if.then50, label %if.end51, !dbg !4455

if.then50:                                        ; preds = %land.lhs.true47
  store i64 -1, i64* %nsent, align 8, !dbg !4456
  br label %out, !dbg !4458

if.end51:                                         ; preds = %land.lhs.true47, %if.end44
  %43 = load i32, i32* %out_fd, align 4, !dbg !4459
  %fd = getelementptr inbounds %struct.pollfd, %struct.pollfd* %pfd, i32 0, i32 0, !dbg !4460
  store i32 %43, i32* %fd, align 4, !dbg !4461
  %events = getelementptr inbounds %struct.pollfd, %struct.pollfd* %pfd, i32 0, i32 1, !dbg !4462
  store i16 4, i16* %events, align 4, !dbg !4463
  %revents = getelementptr inbounds %struct.pollfd, %struct.pollfd* %pfd, i32 0, i32 2, !dbg !4464
  store i16 0, i16* %revents, align 2, !dbg !4465
  br label %do.body52, !dbg !4466

do.body52:                                        ; preds = %land.end61, %if.end51
  %call53 = call i32 @poll(%struct.pollfd* %pfd, i64 1, i32 -1), !dbg !4467
  %conv = sext i32 %call53 to i64, !dbg !4467
  store i64 %conv, i64* %n, align 8, !dbg !4468
  br label %do.cond54, !dbg !4469

do.cond54:                                        ; preds = %do.body52
  %44 = load i64, i64* %n, align 8, !dbg !4470
  %cmp55 = icmp eq i64 %44, -1, !dbg !4471
  br i1 %cmp55, label %land.rhs57, label %land.end61, !dbg !4472

land.rhs57:                                       ; preds = %do.cond54
  %call58 = call i32* @__errno_location() #1, !dbg !4473
  %45 = load i32, i32* %call58, align 4, !dbg !4473
  %cmp59 = icmp eq i32 %45, 4, !dbg !4474
  br label %land.end61

land.end61:                                       ; preds = %land.rhs57, %do.cond54
  %46 = phi i1 [ false, %do.cond54 ], [ %cmp59, %land.rhs57 ]
  br i1 %46, label %do.body52, label %do.end62, !dbg !4475

do.end62:                                         ; preds = %land.end61
  %47 = load i64, i64* %n, align 8, !dbg !4476
  %cmp63 = icmp eq i64 %47, -1, !dbg !4478
  br i1 %cmp63, label %if.then70, label %lor.lhs.false65, !dbg !4479

lor.lhs.false65:                                  ; preds = %do.end62
  %revents66 = getelementptr inbounds %struct.pollfd, %struct.pollfd* %pfd, i32 0, i32 2, !dbg !4480
  %48 = load i16, i16* %revents66, align 2, !dbg !4480
  %conv67 = sext i16 %48 to i32, !dbg !4482
  %and = and i32 %conv67, -5, !dbg !4483
  %cmp68 = icmp ne i32 %and, 0, !dbg !4484
  br i1 %cmp68, label %if.then70, label %if.end72, !dbg !4485

if.then70:                                        ; preds = %lor.lhs.false65, %do.end62
  %call71 = call i32* @__errno_location() #1, !dbg !4486
  store i32 5, i32* %call71, align 4, !dbg !4488
  store i64 -1, i64* %nsent, align 8, !dbg !4489
  br label %out, !dbg !4490

if.end72:                                         ; preds = %lor.lhs.false65
  br label %for.cond28, !dbg !4491

for.end:                                          ; preds = %for.cond28
  %49 = load i64, i64* %nread, align 8, !dbg !4493
  %50 = load i64, i64* %offset, align 8, !dbg !4494
  %add73 = add nsw i64 %50, %49, !dbg !4494
  store i64 %add73, i64* %offset, align 8, !dbg !4494
  %51 = load i64, i64* %nread, align 8, !dbg !4495
  %52 = load i64, i64* %nsent, align 8, !dbg !4496
  %add74 = add nsw i64 %52, %51, !dbg !4496
  store i64 %add74, i64* %nsent, align 8, !dbg !4496
  br label %for.cond, !dbg !4497

for.end75:                                        ; preds = %for.cond
  br label %out, !dbg !4499

out:                                              ; preds = %for.end75, %if.then70, %if.then50, %if.end26, %if.then11
  %53 = load i64, i64* %nsent, align 8, !dbg !4500
  %cmp76 = icmp ne i64 %53, -1, !dbg !4502
  br i1 %cmp76, label %if.then78, label %if.end80, !dbg !4503

if.then78:                                        ; preds = %out
  %54 = load i64, i64* %offset, align 8, !dbg !4504
  %55 = load %struct.uv_fs_s*, %struct.uv_fs_s** %req.addr, align 8, !dbg !4505
  %off79 = getelementptr inbounds %struct.uv_fs_s, %struct.uv_fs_s* %55, i32 0, i32 17, !dbg !4506
  store i64 %54, i64* %off79, align 8, !dbg !4507
  br label %if.end80, !dbg !4505

if.end80:                                         ; preds = %if.then78, %out
  %56 = load i64, i64* %nsent, align 8, !dbg !4508
  ret i64 %56, !dbg !4509
}

declare i64 @write(i32, i8*, i64) #3

declare i32 @poll(%struct.pollfd*, i64, i32) #3

; Function Attrs: nounwind
declare i32 @stat64(i8*, %struct.stat*) #7

; Function Attrs: nounwind
declare i32 @utime(i8*, %struct.utimbuf*) #7

declare i64 @writev(i32, %struct.iovec*, i32) #3

declare i64 @pwrite64(i32, i8*, i64, i64) #3

declare i64 @uv__pwritev(i32, %struct.iovec*, i32, i64) #3

attributes #0 = { nounwind uwtable "disable-tail-calls"="false" "less-precise-fpmad"="false" "no-frame-pointer-elim"="true" "no-frame-pointer-elim-non-leaf" "no-infs-fp-math"="false" "no-nans-fp-math"="false" "stack-protector-buffer-size"="8" "target-cpu"="x86-64" "target-features"="+fxsr,+mmx,+sse,+sse2" "unsafe-fp-math"="false" "use-soft-float"="false" }
attributes #1 = { nounwind readnone }
attributes #2 = { noreturn nounwind "disable-tail-calls"="false" "less-precise-fpmad"="false" "no-frame-pointer-elim"="true" "no-frame-pointer-elim-non-leaf" "no-infs-fp-math"="false" "no-nans-fp-math"="false" "stack-protector-buffer-size"="8" "target-cpu"="x86-64" "target-features"="+fxsr,+mmx,+sse,+sse2" "unsafe-fp-math"="false" "use-soft-float"="false" }
attributes #3 = { "disable-tail-calls"="false" "less-precise-fpmad"="false" "no-frame-pointer-elim"="true" "no-frame-pointer-elim-non-leaf" "no-infs-fp-math"="false" "no-nans-fp-math"="false" "stack-protector-buffer-size"="8" "target-cpu"="x86-64" "target-features"="+fxsr,+mmx,+sse,+sse2" "unsafe-fp-math"="false" "use-soft-float"="false" }
attributes #4 = { nounwind readonly "disable-tail-calls"="false" "less-precise-fpmad"="false" "no-frame-pointer-elim"="true" "no-frame-pointer-elim-non-leaf" "no-infs-fp-math"="false" "no-nans-fp-math"="false" "stack-protector-buffer-size"="8" "target-cpu"="x86-64" "target-features"="+fxsr,+mmx,+sse,+sse2" "unsafe-fp-math"="false" "use-soft-float"="false" }
attributes #5 = { argmemonly nounwind }
attributes #6 = { nounwind readnone "disable-tail-calls"="false" "less-precise-fpmad"="false" "no-frame-pointer-elim"="true" "no-frame-pointer-elim-non-leaf" "no-infs-fp-math"="false" "no-nans-fp-math"="false" "stack-protector-buffer-size"="8" "target-cpu"="x86-64" "target-features"="+fxsr,+mmx,+sse,+sse2" "unsafe-fp-math"="false" "use-soft-float"="false" }
attributes #7 = { nounwind "disable-tail-calls"="false" "less-precise-fpmad"="false" "no-frame-pointer-elim"="true" "no-frame-pointer-elim-non-leaf" "no-infs-fp-math"="false" "no-nans-fp-math"="false" "stack-protector-buffer-size"="8" "target-cpu"="x86-64" "target-features"="+fxsr,+mmx,+sse,+sse2" "unsafe-fp-math"="false" "use-soft-float"="false" }
attributes #8 = { noreturn nounwind }
attributes #9 = { nounwind }
attributes #10 = { nounwind readonly }

!llvm.dbg.cu = !{!0}
!llvm.module.flags = !{!576, !577}
!llvm.ident = !{!578}

!0 = distinct !DICompileUnit(language: DW_LANG_C99, file: !1, producer: "clang version 3.8.0 (tags/RELEASE_380/final)", isOptimized: false, runtimeVersion: 0, emissionKind: 1, enums: !2, retainedTypes: !94, subprograms: !414, globals: !571)
!1 = !DIFile(filename: "/data/download/cmake/cmake-master/Utilities/cmlibuv/src/unix/fs.c", directory: "/data/download/cmake/cmake-master/Utilities/cmlibuv")
!2 = !{!3, !25, !38, !70}
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
!38 = !DICompositeType(tag: DW_TAG_enumeration_type, file: !4, line: 1086, size: 32, align: 32, elements: !39)
!39 = !{!40, !41, !42, !43, !44, !45, !46, !47, !48, !49, !50, !51, !52, !53, !54, !55, !56, !57, !58, !59, !60, !61, !62, !63, !64, !65, !66, !67, !68, !69}
!40 = !DIEnumerator(name: "UV_FS_UNKNOWN", value: -1)
!41 = !DIEnumerator(name: "UV_FS_CUSTOM", value: 0)
!42 = !DIEnumerator(name: "UV_FS_OPEN", value: 1)
!43 = !DIEnumerator(name: "UV_FS_CLOSE", value: 2)
!44 = !DIEnumerator(name: "UV_FS_READ", value: 3)
!45 = !DIEnumerator(name: "UV_FS_WRITE", value: 4)
!46 = !DIEnumerator(name: "UV_FS_SENDFILE", value: 5)
!47 = !DIEnumerator(name: "UV_FS_STAT", value: 6)
!48 = !DIEnumerator(name: "UV_FS_LSTAT", value: 7)
!49 = !DIEnumerator(name: "UV_FS_FSTAT", value: 8)
!50 = !DIEnumerator(name: "UV_FS_FTRUNCATE", value: 9)
!51 = !DIEnumerator(name: "UV_FS_UTIME", value: 10)
!52 = !DIEnumerator(name: "UV_FS_FUTIME", value: 11)
!53 = !DIEnumerator(name: "UV_FS_ACCESS", value: 12)
!54 = !DIEnumerator(name: "UV_FS_CHMOD", value: 13)
!55 = !DIEnumerator(name: "UV_FS_FCHMOD", value: 14)
!56 = !DIEnumerator(name: "UV_FS_FSYNC", value: 15)
!57 = !DIEnumerator(name: "UV_FS_FDATASYNC", value: 16)
!58 = !DIEnumerator(name: "UV_FS_UNLINK", value: 17)
!59 = !DIEnumerator(name: "UV_FS_RMDIR", value: 18)
!60 = !DIEnumerator(name: "UV_FS_MKDIR", value: 19)
!61 = !DIEnumerator(name: "UV_FS_MKDTEMP", value: 20)
!62 = !DIEnumerator(name: "UV_FS_RENAME", value: 21)
!63 = !DIEnumerator(name: "UV_FS_SCANDIR", value: 22)
!64 = !DIEnumerator(name: "UV_FS_LINK", value: 23)
!65 = !DIEnumerator(name: "UV_FS_SYMLINK", value: 24)
!66 = !DIEnumerator(name: "UV_FS_READLINK", value: 25)
!67 = !DIEnumerator(name: "UV_FS_CHOWN", value: 26)
!68 = !DIEnumerator(name: "UV_FS_FCHOWN", value: 27)
!69 = !DIEnumerator(name: "UV_FS_REALPATH", value: 28)
!70 = !DICompositeType(tag: DW_TAG_enumeration_type, file: !71, line: 24, size: 32, align: 32, elements: !72)
!71 = !DIFile(filename: "/usr/include/x86_64-linux-gnu/bits/confname.h", directory: "/data/download/cmake/cmake-master/Utilities/cmlibuv")
!72 = !{!73, !74, !75, !76, !77, !78, !79, !80, !81, !82, !83, !84, !85, !86, !87, !88, !89, !90, !91, !92, !93}
!73 = !DIEnumerator(name: "_PC_LINK_MAX", value: 0)
!74 = !DIEnumerator(name: "_PC_MAX_CANON", value: 1)
!75 = !DIEnumerator(name: "_PC_MAX_INPUT", value: 2)
!76 = !DIEnumerator(name: "_PC_NAME_MAX", value: 3)
!77 = !DIEnumerator(name: "_PC_PATH_MAX", value: 4)
!78 = !DIEnumerator(name: "_PC_PIPE_BUF", value: 5)
!79 = !DIEnumerator(name: "_PC_CHOWN_RESTRICTED", value: 6)
!80 = !DIEnumerator(name: "_PC_NO_TRUNC", value: 7)
!81 = !DIEnumerator(name: "_PC_VDISABLE", value: 8)
!82 = !DIEnumerator(name: "_PC_SYNC_IO", value: 9)
!83 = !DIEnumerator(name: "_PC_ASYNC_IO", value: 10)
!84 = !DIEnumerator(name: "_PC_PRIO_IO", value: 11)
!85 = !DIEnumerator(name: "_PC_SOCK_MAXBUF", value: 12)
!86 = !DIEnumerator(name: "_PC_FILESIZEBITS", value: 13)
!87 = !DIEnumerator(name: "_PC_REC_INCR_XFER_SIZE", value: 14)
!88 = !DIEnumerator(name: "_PC_REC_MAX_XFER_SIZE", value: 15)
!89 = !DIEnumerator(name: "_PC_REC_MIN_XFER_SIZE", value: 16)
!90 = !DIEnumerator(name: "_PC_REC_XFER_ALIGN", value: 17)
!91 = !DIEnumerator(name: "_PC_ALLOC_SIZE_MIN", value: 18)
!92 = !DIEnumerator(name: "_PC_SYMLINK_MAX", value: 19)
!93 = !DIEnumerator(name: "_PC_2_SYMLINKS", value: 20)
!94 = !{!95, !96, !103, !105, !373, !276, !133, !408, !375}
!95 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: null, size: 64, align: 64)
!96 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !97, size: 64, align: 64)
!97 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !98, size: 64, align: 64)
!98 = !DIDerivedType(tag: DW_TAG_typedef, name: "QUEUE", file: !99, line: 21, baseType: !100)
!99 = !DIFile(filename: "/data/download/cmake/cmake-master/Utilities/cmlibuv/src/queue.h", directory: "/data/download/cmake/cmake-master/Utilities/cmlibuv")
!100 = !DICompositeType(tag: DW_TAG_array_type, baseType: !95, size: 128, align: 64, elements: !101)
!101 = !{!102}
!102 = !DISubrange(count: 2)
!103 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !104, size: 64, align: 64)
!104 = !DIDerivedType(tag: DW_TAG_const_type, baseType: !98)
!105 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !106, size: 64, align: 64)
!106 = !DIDerivedType(tag: DW_TAG_typedef, name: "uv_fs_t", file: !4, line: 230, baseType: !107)
!107 = !DICompositeType(tag: DW_TAG_structure_type, name: "uv_fs_s", file: !4, line: 1120, size: 3520, align: 64, elements: !108)
!108 = !{!109, !110, !112, !113, !117, !119, !319, !324, !329, !330, !333, !358, !359, !361, !362, !366, !367, !377, !380, !384, !388, !390, !391, !406}
!109 = !DIDerivedType(tag: DW_TAG_member, name: "data", scope: !107, file: !4, line: 1121, baseType: !95, size: 64, align: 64)
!110 = !DIDerivedType(tag: DW_TAG_member, name: "type", scope: !107, file: !4, line: 1121, baseType: !111, size: 32, align: 32, offset: 64)
!111 = !DIDerivedType(tag: DW_TAG_typedef, name: "uv_req_type", file: !4, line: 200, baseType: !25)
!112 = !DIDerivedType(tag: DW_TAG_member, name: "active_queue", scope: !107, file: !4, line: 1121, baseType: !100, size: 128, align: 64, offset: 128)
!113 = !DIDerivedType(tag: DW_TAG_member, name: "reserved", scope: !107, file: !4, line: 1121, baseType: !114, size: 256, align: 64, offset: 256)
!114 = !DICompositeType(tag: DW_TAG_array_type, baseType: !95, size: 256, align: 64, elements: !115)
!115 = !{!116}
!116 = !DISubrange(count: 4)
!117 = !DIDerivedType(tag: DW_TAG_member, name: "fs_type", scope: !107, file: !4, line: 1122, baseType: !118, size: 32, align: 32, offset: 512)
!118 = !DIDerivedType(tag: DW_TAG_typedef, name: "uv_fs_type", file: !4, line: 1117, baseType: !38)
!119 = !DIDerivedType(tag: DW_TAG_member, name: "loop", scope: !107, file: !4, line: 1123, baseType: !120, size: 64, align: 64, offset: 576)
!120 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !121, size: 64, align: 64)
!121 = !DIDerivedType(tag: DW_TAG_typedef, name: "uv_loop_t", file: !4, line: 204, baseType: !122)
!122 = !DICompositeType(tag: DW_TAG_structure_type, name: "uv_loop_s", file: !4, line: 1473, size: 6784, align: 64, elements: !123)
!123 = !{!124, !125, !127, !128, !129, !130, !132, !134, !135, !136, !155, !156, !157, !158, !189, !234, !258, !259, !260, !261, !262, !263, !264, !268, !269, !270, !275, !278, !279, !281, !282, !315, !316, !317, !318}
!124 = !DIDerivedType(tag: DW_TAG_member, name: "data", scope: !122, file: !4, line: 1475, baseType: !95, size: 64, align: 64)
!125 = !DIDerivedType(tag: DW_TAG_member, name: "active_handles", scope: !122, file: !4, line: 1477, baseType: !126, size: 32, align: 32, offset: 64)
!126 = !DIBasicType(name: "unsigned int", size: 32, align: 32, encoding: DW_ATE_unsigned)
!127 = !DIDerivedType(tag: DW_TAG_member, name: "handle_queue", scope: !122, file: !4, line: 1478, baseType: !100, size: 128, align: 64, offset: 128)
!128 = !DIDerivedType(tag: DW_TAG_member, name: "active_reqs", scope: !122, file: !4, line: 1479, baseType: !100, size: 128, align: 64, offset: 256)
!129 = !DIDerivedType(tag: DW_TAG_member, name: "stop_flag", scope: !122, file: !4, line: 1481, baseType: !126, size: 32, align: 32, offset: 384)
!130 = !DIDerivedType(tag: DW_TAG_member, name: "flags", scope: !122, file: !4, line: 1482, baseType: !131, size: 64, align: 64, offset: 448)
!131 = !DIBasicType(name: "long unsigned int", size: 64, align: 64, encoding: DW_ATE_unsigned)
!132 = !DIDerivedType(tag: DW_TAG_member, name: "backend_fd", scope: !122, file: !4, line: 1482, baseType: !133, size: 32, align: 32, offset: 512)
!133 = !DIBasicType(name: "int", size: 32, align: 32, encoding: DW_ATE_signed)
!134 = !DIDerivedType(tag: DW_TAG_member, name: "pending_queue", scope: !122, file: !4, line: 1482, baseType: !100, size: 128, align: 64, offset: 576)
!135 = !DIDerivedType(tag: DW_TAG_member, name: "watcher_queue", scope: !122, file: !4, line: 1482, baseType: !100, size: 128, align: 64, offset: 704)
!136 = !DIDerivedType(tag: DW_TAG_member, name: "watchers", scope: !122, file: !4, line: 1482, baseType: !137, size: 64, align: 64, offset: 832)
!137 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !138, size: 64, align: 64)
!138 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !139, size: 64, align: 64)
!139 = !DIDerivedType(tag: DW_TAG_typedef, name: "uv__io_t", file: !140, line: 87, baseType: !141)
!140 = !DIFile(filename: "/data/download/cmake/cmake-master/Utilities/cmlibuv/include/uv-unix.h", directory: "/data/download/cmake/cmake-master/Utilities/cmlibuv")
!141 = !DICompositeType(tag: DW_TAG_structure_type, name: "uv__io_s", file: !140, line: 89, size: 448, align: 64, elements: !142)
!142 = !{!143, !150, !151, !152, !153, !154}
!143 = !DIDerivedType(tag: DW_TAG_member, name: "cb", scope: !141, file: !140, line: 90, baseType: !144, size: 64, align: 64)
!144 = !DIDerivedType(tag: DW_TAG_typedef, name: "uv__io_cb", file: !140, line: 84, baseType: !145)
!145 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !146, size: 64, align: 64)
!146 = !DISubroutineType(types: !147)
!147 = !{null, !148, !149, !126}
!148 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !122, size: 64, align: 64)
!149 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !141, size: 64, align: 64)
!150 = !DIDerivedType(tag: DW_TAG_member, name: "pending_queue", scope: !141, file: !140, line: 91, baseType: !100, size: 128, align: 64, offset: 64)
!151 = !DIDerivedType(tag: DW_TAG_member, name: "watcher_queue", scope: !141, file: !140, line: 92, baseType: !100, size: 128, align: 64, offset: 192)
!152 = !DIDerivedType(tag: DW_TAG_member, name: "pevents", scope: !141, file: !140, line: 93, baseType: !126, size: 32, align: 32, offset: 320)
!153 = !DIDerivedType(tag: DW_TAG_member, name: "events", scope: !141, file: !140, line: 94, baseType: !126, size: 32, align: 32, offset: 352)
!154 = !DIDerivedType(tag: DW_TAG_member, name: "fd", scope: !141, file: !140, line: 95, baseType: !133, size: 32, align: 32, offset: 384)
!155 = !DIDerivedType(tag: DW_TAG_member, name: "nwatchers", scope: !122, file: !4, line: 1482, baseType: !126, size: 32, align: 32, offset: 896)
!156 = !DIDerivedType(tag: DW_TAG_member, name: "nfds", scope: !122, file: !4, line: 1482, baseType: !126, size: 32, align: 32, offset: 928)
!157 = !DIDerivedType(tag: DW_TAG_member, name: "wq", scope: !122, file: !4, line: 1482, baseType: !100, size: 128, align: 64, offset: 960)
!158 = !DIDerivedType(tag: DW_TAG_member, name: "wq_mutex", scope: !122, file: !4, line: 1482, baseType: !159, size: 320, align: 64, offset: 1088)
!159 = !DIDerivedType(tag: DW_TAG_typedef, name: "uv_mutex_t", file: !140, line: 129, baseType: !160)
!160 = !DIDerivedType(tag: DW_TAG_typedef, name: "pthread_mutex_t", file: !161, line: 127, baseType: !162)
!161 = !DIFile(filename: "/usr/include/x86_64-linux-gnu/bits/pthreadtypes.h", directory: "/data/download/cmake/cmake-master/Utilities/cmlibuv")
!162 = !DICompositeType(tag: DW_TAG_union_type, file: !161, line: 90, size: 320, align: 64, elements: !163)
!163 = !{!164, !182, !187}
!164 = !DIDerivedType(tag: DW_TAG_member, name: "__data", scope: !162, file: !161, line: 124, baseType: !165, size: 320, align: 64)
!165 = !DICompositeType(tag: DW_TAG_structure_type, name: "__pthread_mutex_s", file: !161, line: 92, size: 320, align: 64, elements: !166)
!166 = !{!167, !168, !169, !170, !171, !172, !174, !175}
!167 = !DIDerivedType(tag: DW_TAG_member, name: "__lock", scope: !165, file: !161, line: 94, baseType: !133, size: 32, align: 32)
!168 = !DIDerivedType(tag: DW_TAG_member, name: "__count", scope: !165, file: !161, line: 95, baseType: !126, size: 32, align: 32, offset: 32)
!169 = !DIDerivedType(tag: DW_TAG_member, name: "__owner", scope: !165, file: !161, line: 96, baseType: !133, size: 32, align: 32, offset: 64)
!170 = !DIDerivedType(tag: DW_TAG_member, name: "__nusers", scope: !165, file: !161, line: 98, baseType: !126, size: 32, align: 32, offset: 96)
!171 = !DIDerivedType(tag: DW_TAG_member, name: "__kind", scope: !165, file: !161, line: 102, baseType: !133, size: 32, align: 32, offset: 128)
!172 = !DIDerivedType(tag: DW_TAG_member, name: "__spins", scope: !165, file: !161, line: 104, baseType: !173, size: 16, align: 16, offset: 160)
!173 = !DIBasicType(name: "short", size: 16, align: 16, encoding: DW_ATE_signed)
!174 = !DIDerivedType(tag: DW_TAG_member, name: "__elision", scope: !165, file: !161, line: 105, baseType: !173, size: 16, align: 16, offset: 176)
!175 = !DIDerivedType(tag: DW_TAG_member, name: "__list", scope: !165, file: !161, line: 106, baseType: !176, size: 128, align: 64, offset: 192)
!176 = !DIDerivedType(tag: DW_TAG_typedef, name: "__pthread_list_t", file: !161, line: 79, baseType: !177)
!177 = !DICompositeType(tag: DW_TAG_structure_type, name: "__pthread_internal_list", file: !161, line: 75, size: 128, align: 64, elements: !178)
!178 = !{!179, !181}
!179 = !DIDerivedType(tag: DW_TAG_member, name: "__prev", scope: !177, file: !161, line: 77, baseType: !180, size: 64, align: 64)
!180 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !177, size: 64, align: 64)
!181 = !DIDerivedType(tag: DW_TAG_member, name: "__next", scope: !177, file: !161, line: 78, baseType: !180, size: 64, align: 64, offset: 64)
!182 = !DIDerivedType(tag: DW_TAG_member, name: "__size", scope: !162, file: !161, line: 125, baseType: !183, size: 320, align: 8)
!183 = !DICompositeType(tag: DW_TAG_array_type, baseType: !184, size: 320, align: 8, elements: !185)
!184 = !DIBasicType(name: "char", size: 8, align: 8, encoding: DW_ATE_signed_char)
!185 = !{!186}
!186 = !DISubrange(count: 40)
!187 = !DIDerivedType(tag: DW_TAG_member, name: "__align", scope: !162, file: !161, line: 126, baseType: !188, size: 64, align: 64)
!188 = !DIBasicType(name: "long int", size: 64, align: 64, encoding: DW_ATE_signed)
!189 = !DIDerivedType(tag: DW_TAG_member, name: "wq_async", scope: !122, file: !4, line: 1482, baseType: !190, size: 1024, align: 64, offset: 1408)
!190 = !DIDerivedType(tag: DW_TAG_typedef, name: "uv_async_t", file: !4, line: 216, baseType: !191)
!191 = !DICompositeType(tag: DW_TAG_structure_type, name: "uv_async_s", file: !4, line: 767, size: 1024, align: 64, elements: !192)
!192 = !{!193, !194, !195, !197, !218, !219, !224, !225, !226, !232, !233}
!193 = !DIDerivedType(tag: DW_TAG_member, name: "data", scope: !191, file: !4, line: 768, baseType: !95, size: 64, align: 64)
!194 = !DIDerivedType(tag: DW_TAG_member, name: "loop", scope: !191, file: !4, line: 768, baseType: !120, size: 64, align: 64, offset: 64)
!195 = !DIDerivedType(tag: DW_TAG_member, name: "type", scope: !191, file: !4, line: 768, baseType: !196, size: 32, align: 32, offset: 128)
!196 = !DIDerivedType(tag: DW_TAG_typedef, name: "uv_handle_type", file: !4, line: 191, baseType: !3)
!197 = !DIDerivedType(tag: DW_TAG_member, name: "close_cb", scope: !191, file: !4, line: 768, baseType: !198, size: 64, align: 64, offset: 192)
!198 = !DIDerivedType(tag: DW_TAG_typedef, name: "uv_close_cb", file: !4, line: 306, baseType: !199)
!199 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !200, size: 64, align: 64)
!200 = !DISubroutineType(types: !201)
!201 = !{null, !202}
!202 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !203, size: 64, align: 64)
!203 = !DIDerivedType(tag: DW_TAG_typedef, name: "uv_handle_t", file: !4, line: 205, baseType: !204)
!204 = !DICompositeType(tag: DW_TAG_structure_type, name: "uv_handle_s", file: !4, line: 425, size: 768, align: 64, elements: !205)
!205 = !{!206, !207, !208, !209, !210, !211, !216, !217}
!206 = !DIDerivedType(tag: DW_TAG_member, name: "data", scope: !204, file: !4, line: 426, baseType: !95, size: 64, align: 64)
!207 = !DIDerivedType(tag: DW_TAG_member, name: "loop", scope: !204, file: !4, line: 426, baseType: !120, size: 64, align: 64, offset: 64)
!208 = !DIDerivedType(tag: DW_TAG_member, name: "type", scope: !204, file: !4, line: 426, baseType: !196, size: 32, align: 32, offset: 128)
!209 = !DIDerivedType(tag: DW_TAG_member, name: "close_cb", scope: !204, file: !4, line: 426, baseType: !198, size: 64, align: 64, offset: 192)
!210 = !DIDerivedType(tag: DW_TAG_member, name: "handle_queue", scope: !204, file: !4, line: 426, baseType: !100, size: 128, align: 64, offset: 256)
!211 = !DIDerivedType(tag: DW_TAG_member, name: "u", scope: !204, file: !4, line: 426, baseType: !212, size: 256, align: 64, offset: 384)
!212 = !DICompositeType(tag: DW_TAG_union_type, scope: !204, file: !4, line: 426, size: 256, align: 64, elements: !213)
!213 = !{!214, !215}
!214 = !DIDerivedType(tag: DW_TAG_member, name: "fd", scope: !212, file: !4, line: 426, baseType: !133, size: 32, align: 32)
!215 = !DIDerivedType(tag: DW_TAG_member, name: "reserved", scope: !212, file: !4, line: 426, baseType: !114, size: 256, align: 64)
!216 = !DIDerivedType(tag: DW_TAG_member, name: "next_closing", scope: !204, file: !4, line: 426, baseType: !202, size: 64, align: 64, offset: 640)
!217 = !DIDerivedType(tag: DW_TAG_member, name: "flags", scope: !204, file: !4, line: 426, baseType: !126, size: 32, align: 32, offset: 704)
!218 = !DIDerivedType(tag: DW_TAG_member, name: "handle_queue", scope: !191, file: !4, line: 768, baseType: !100, size: 128, align: 64, offset: 256)
!219 = !DIDerivedType(tag: DW_TAG_member, name: "u", scope: !191, file: !4, line: 768, baseType: !220, size: 256, align: 64, offset: 384)
!220 = !DICompositeType(tag: DW_TAG_union_type, scope: !191, file: !4, line: 768, size: 256, align: 64, elements: !221)
!221 = !{!222, !223}
!222 = !DIDerivedType(tag: DW_TAG_member, name: "fd", scope: !220, file: !4, line: 768, baseType: !133, size: 32, align: 32)
!223 = !DIDerivedType(tag: DW_TAG_member, name: "reserved", scope: !220, file: !4, line: 768, baseType: !114, size: 256, align: 64)
!224 = !DIDerivedType(tag: DW_TAG_member, name: "next_closing", scope: !191, file: !4, line: 768, baseType: !202, size: 64, align: 64, offset: 640)
!225 = !DIDerivedType(tag: DW_TAG_member, name: "flags", scope: !191, file: !4, line: 768, baseType: !126, size: 32, align: 32, offset: 704)
!226 = !DIDerivedType(tag: DW_TAG_member, name: "async_cb", scope: !191, file: !4, line: 769, baseType: !227, size: 64, align: 64, offset: 768)
!227 = !DIDerivedType(tag: DW_TAG_typedef, name: "uv_async_cb", file: !4, line: 309, baseType: !228)
!228 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !229, size: 64, align: 64)
!229 = !DISubroutineType(types: !230)
!230 = !{null, !231}
!231 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !190, size: 64, align: 64)
!232 = !DIDerivedType(tag: DW_TAG_member, name: "queue", scope: !191, file: !4, line: 769, baseType: !100, size: 128, align: 64, offset: 832)
!233 = !DIDerivedType(tag: DW_TAG_member, name: "pending", scope: !191, file: !4, line: 769, baseType: !133, size: 32, align: 32, offset: 960)
!234 = !DIDerivedType(tag: DW_TAG_member, name: "cloexec_lock", scope: !122, file: !4, line: 1482, baseType: !235, size: 448, align: 64, offset: 2432)
!235 = !DIDerivedType(tag: DW_TAG_typedef, name: "uv_rwlock_t", file: !140, line: 130, baseType: !236)
!236 = !DIDerivedType(tag: DW_TAG_typedef, name: "pthread_rwlock_t", file: !161, line: 213, baseType: !237)
!237 = !DICompositeType(tag: DW_TAG_union_type, file: !161, line: 173, size: 448, align: 64, elements: !238)
!238 = !{!239, !253, !257}
!239 = !DIDerivedType(tag: DW_TAG_member, name: "__data", scope: !237, file: !161, line: 192, baseType: !240, size: 448, align: 64)
!240 = !DICompositeType(tag: DW_TAG_structure_type, scope: !237, file: !161, line: 176, size: 448, align: 64, elements: !241)
!241 = !{!242, !243, !244, !245, !246, !247, !248, !249, !250, !251, !252}
!242 = !DIDerivedType(tag: DW_TAG_member, name: "__lock", scope: !240, file: !161, line: 178, baseType: !133, size: 32, align: 32)
!243 = !DIDerivedType(tag: DW_TAG_member, name: "__nr_readers", scope: !240, file: !161, line: 179, baseType: !126, size: 32, align: 32, offset: 32)
!244 = !DIDerivedType(tag: DW_TAG_member, name: "__readers_wakeup", scope: !240, file: !161, line: 180, baseType: !126, size: 32, align: 32, offset: 64)
!245 = !DIDerivedType(tag: DW_TAG_member, name: "__writer_wakeup", scope: !240, file: !161, line: 181, baseType: !126, size: 32, align: 32, offset: 96)
!246 = !DIDerivedType(tag: DW_TAG_member, name: "__nr_readers_queued", scope: !240, file: !161, line: 182, baseType: !126, size: 32, align: 32, offset: 128)
!247 = !DIDerivedType(tag: DW_TAG_member, name: "__nr_writers_queued", scope: !240, file: !161, line: 183, baseType: !126, size: 32, align: 32, offset: 160)
!248 = !DIDerivedType(tag: DW_TAG_member, name: "__writer", scope: !240, file: !161, line: 184, baseType: !133, size: 32, align: 32, offset: 192)
!249 = !DIDerivedType(tag: DW_TAG_member, name: "__shared", scope: !240, file: !161, line: 185, baseType: !133, size: 32, align: 32, offset: 224)
!250 = !DIDerivedType(tag: DW_TAG_member, name: "__pad1", scope: !240, file: !161, line: 186, baseType: !131, size: 64, align: 64, offset: 256)
!251 = !DIDerivedType(tag: DW_TAG_member, name: "__pad2", scope: !240, file: !161, line: 187, baseType: !131, size: 64, align: 64, offset: 320)
!252 = !DIDerivedType(tag: DW_TAG_member, name: "__flags", scope: !240, file: !161, line: 190, baseType: !126, size: 32, align: 32, offset: 384)
!253 = !DIDerivedType(tag: DW_TAG_member, name: "__size", scope: !237, file: !161, line: 211, baseType: !254, size: 448, align: 8)
!254 = !DICompositeType(tag: DW_TAG_array_type, baseType: !184, size: 448, align: 8, elements: !255)
!255 = !{!256}
!256 = !DISubrange(count: 56)
!257 = !DIDerivedType(tag: DW_TAG_member, name: "__align", scope: !237, file: !161, line: 212, baseType: !188, size: 64, align: 64)
!258 = !DIDerivedType(tag: DW_TAG_member, name: "closing_handles", scope: !122, file: !4, line: 1482, baseType: !202, size: 64, align: 64, offset: 2880)
!259 = !DIDerivedType(tag: DW_TAG_member, name: "process_handles", scope: !122, file: !4, line: 1482, baseType: !100, size: 128, align: 64, offset: 2944)
!260 = !DIDerivedType(tag: DW_TAG_member, name: "prepare_handles", scope: !122, file: !4, line: 1482, baseType: !100, size: 128, align: 64, offset: 3072)
!261 = !DIDerivedType(tag: DW_TAG_member, name: "check_handles", scope: !122, file: !4, line: 1482, baseType: !100, size: 128, align: 64, offset: 3200)
!262 = !DIDerivedType(tag: DW_TAG_member, name: "idle_handles", scope: !122, file: !4, line: 1482, baseType: !100, size: 128, align: 64, offset: 3328)
!263 = !DIDerivedType(tag: DW_TAG_member, name: "async_handles", scope: !122, file: !4, line: 1482, baseType: !100, size: 128, align: 64, offset: 3456)
!264 = !DIDerivedType(tag: DW_TAG_member, name: "async_unused", scope: !122, file: !4, line: 1482, baseType: !265, size: 64, align: 64, offset: 3584)
!265 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !266, size: 64, align: 64)
!266 = !DISubroutineType(types: !267)
!267 = !{null}
!268 = !DIDerivedType(tag: DW_TAG_member, name: "async_io_watcher", scope: !122, file: !4, line: 1482, baseType: !139, size: 448, align: 64, offset: 3648)
!269 = !DIDerivedType(tag: DW_TAG_member, name: "async_wfd", scope: !122, file: !4, line: 1482, baseType: !133, size: 32, align: 32, offset: 4096)
!270 = !DIDerivedType(tag: DW_TAG_member, name: "timer_heap", scope: !122, file: !4, line: 1482, baseType: !271, size: 128, align: 64, offset: 4160)
!271 = !DICompositeType(tag: DW_TAG_structure_type, scope: !122, file: !4, line: 1482, size: 128, align: 64, elements: !272)
!272 = !{!273, !274}
!273 = !DIDerivedType(tag: DW_TAG_member, name: "min", scope: !271, file: !4, line: 1482, baseType: !95, size: 64, align: 64)
!274 = !DIDerivedType(tag: DW_TAG_member, name: "nelts", scope: !271, file: !4, line: 1482, baseType: !126, size: 32, align: 32, offset: 64)
!275 = !DIDerivedType(tag: DW_TAG_member, name: "timer_counter", scope: !122, file: !4, line: 1482, baseType: !276, size: 64, align: 64, offset: 4288)
!276 = !DIDerivedType(tag: DW_TAG_typedef, name: "uint64_t", file: !277, line: 55, baseType: !131)
!277 = !DIFile(filename: "/usr/include/stdint.h", directory: "/data/download/cmake/cmake-master/Utilities/cmlibuv")
!278 = !DIDerivedType(tag: DW_TAG_member, name: "time", scope: !122, file: !4, line: 1482, baseType: !276, size: 64, align: 64, offset: 4352)
!279 = !DIDerivedType(tag: DW_TAG_member, name: "signal_pipefd", scope: !122, file: !4, line: 1482, baseType: !280, size: 64, align: 32, offset: 4416)
!280 = !DICompositeType(tag: DW_TAG_array_type, baseType: !133, size: 64, align: 32, elements: !101)
!281 = !DIDerivedType(tag: DW_TAG_member, name: "signal_io_watcher", scope: !122, file: !4, line: 1482, baseType: !139, size: 448, align: 64, offset: 4480)
!282 = !DIDerivedType(tag: DW_TAG_member, name: "child_watcher", scope: !122, file: !4, line: 1482, baseType: !283, size: 1216, align: 64, offset: 4928)
!283 = !DIDerivedType(tag: DW_TAG_typedef, name: "uv_signal_t", file: !4, line: 220, baseType: !284)
!284 = !DICompositeType(tag: DW_TAG_structure_type, name: "uv_signal_s", file: !4, line: 1325, size: 1216, align: 64, elements: !285)
!285 = !{!286, !287, !288, !289, !290, !291, !296, !297, !298, !304, !305, !313, !314}
!286 = !DIDerivedType(tag: DW_TAG_member, name: "data", scope: !284, file: !4, line: 1326, baseType: !95, size: 64, align: 64)
!287 = !DIDerivedType(tag: DW_TAG_member, name: "loop", scope: !284, file: !4, line: 1326, baseType: !120, size: 64, align: 64, offset: 64)
!288 = !DIDerivedType(tag: DW_TAG_member, name: "type", scope: !284, file: !4, line: 1326, baseType: !196, size: 32, align: 32, offset: 128)
!289 = !DIDerivedType(tag: DW_TAG_member, name: "close_cb", scope: !284, file: !4, line: 1326, baseType: !198, size: 64, align: 64, offset: 192)
!290 = !DIDerivedType(tag: DW_TAG_member, name: "handle_queue", scope: !284, file: !4, line: 1326, baseType: !100, size: 128, align: 64, offset: 256)
!291 = !DIDerivedType(tag: DW_TAG_member, name: "u", scope: !284, file: !4, line: 1326, baseType: !292, size: 256, align: 64, offset: 384)
!292 = !DICompositeType(tag: DW_TAG_union_type, scope: !284, file: !4, line: 1326, size: 256, align: 64, elements: !293)
!293 = !{!294, !295}
!294 = !DIDerivedType(tag: DW_TAG_member, name: "fd", scope: !292, file: !4, line: 1326, baseType: !133, size: 32, align: 32)
!295 = !DIDerivedType(tag: DW_TAG_member, name: "reserved", scope: !292, file: !4, line: 1326, baseType: !114, size: 256, align: 64)
!296 = !DIDerivedType(tag: DW_TAG_member, name: "next_closing", scope: !284, file: !4, line: 1326, baseType: !202, size: 64, align: 64, offset: 640)
!297 = !DIDerivedType(tag: DW_TAG_member, name: "flags", scope: !284, file: !4, line: 1326, baseType: !126, size: 32, align: 32, offset: 704)
!298 = !DIDerivedType(tag: DW_TAG_member, name: "signal_cb", scope: !284, file: !4, line: 1327, baseType: !299, size: 64, align: 64, offset: 768)
!299 = !DIDerivedType(tag: DW_TAG_typedef, name: "uv_signal_cb", file: !4, line: 362, baseType: !300)
!300 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !301, size: 64, align: 64)
!301 = !DISubroutineType(types: !302)
!302 = !{null, !303, !133}
!303 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !283, size: 64, align: 64)
!304 = !DIDerivedType(tag: DW_TAG_member, name: "signum", scope: !284, file: !4, line: 1328, baseType: !133, size: 32, align: 32, offset: 832)
!305 = !DIDerivedType(tag: DW_TAG_member, name: "tree_entry", scope: !284, file: !4, line: 1329, baseType: !306, size: 256, align: 64, offset: 896)
!306 = !DICompositeType(tag: DW_TAG_structure_type, scope: !284, file: !4, line: 1329, size: 256, align: 64, elements: !307)
!307 = !{!308, !310, !311, !312}
!308 = !DIDerivedType(tag: DW_TAG_member, name: "rbe_left", scope: !306, file: !4, line: 1329, baseType: !309, size: 64, align: 64)
!309 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !284, size: 64, align: 64)
!310 = !DIDerivedType(tag: DW_TAG_member, name: "rbe_right", scope: !306, file: !4, line: 1329, baseType: !309, size: 64, align: 64, offset: 64)
!311 = !DIDerivedType(tag: DW_TAG_member, name: "rbe_parent", scope: !306, file: !4, line: 1329, baseType: !309, size: 64, align: 64, offset: 128)
!312 = !DIDerivedType(tag: DW_TAG_member, name: "rbe_color", scope: !306, file: !4, line: 1329, baseType: !133, size: 32, align: 32, offset: 192)
!313 = !DIDerivedType(tag: DW_TAG_member, name: "caught_signals", scope: !284, file: !4, line: 1329, baseType: !126, size: 32, align: 32, offset: 1152)
!314 = !DIDerivedType(tag: DW_TAG_member, name: "dispatched_signals", scope: !284, file: !4, line: 1329, baseType: !126, size: 32, align: 32, offset: 1184)
!315 = !DIDerivedType(tag: DW_TAG_member, name: "emfile_fd", scope: !122, file: !4, line: 1482, baseType: !133, size: 32, align: 32, offset: 6144)
!316 = !DIDerivedType(tag: DW_TAG_member, name: "inotify_read_watcher", scope: !122, file: !4, line: 1482, baseType: !139, size: 448, align: 64, offset: 6208)
!317 = !DIDerivedType(tag: DW_TAG_member, name: "inotify_watchers", scope: !122, file: !4, line: 1482, baseType: !95, size: 64, align: 64, offset: 6656)
!318 = !DIDerivedType(tag: DW_TAG_member, name: "inotify_fd", scope: !122, file: !4, line: 1482, baseType: !133, size: 32, align: 32, offset: 6720)
!319 = !DIDerivedType(tag: DW_TAG_member, name: "cb", scope: !107, file: !4, line: 1124, baseType: !320, size: 64, align: 64, offset: 640)
!320 = !DIDerivedType(tag: DW_TAG_typedef, name: "uv_fs_cb", file: !4, line: 315, baseType: !321)
!321 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !322, size: 64, align: 64)
!322 = !DISubroutineType(types: !323)
!323 = !{null, !105}
!324 = !DIDerivedType(tag: DW_TAG_member, name: "result", scope: !107, file: !4, line: 1125, baseType: !325, size: 64, align: 64, offset: 704)
!325 = !DIDerivedType(tag: DW_TAG_typedef, name: "ssize_t", file: !326, line: 102, baseType: !327)
!326 = !DIFile(filename: "/usr/include/stdio.h", directory: "/data/download/cmake/cmake-master/Utilities/cmlibuv")
!327 = !DIDerivedType(tag: DW_TAG_typedef, name: "__ssize_t", file: !328, line: 172, baseType: !188)
!328 = !DIFile(filename: "/usr/include/x86_64-linux-gnu/bits/types.h", directory: "/data/download/cmake/cmake-master/Utilities/cmlibuv")
!329 = !DIDerivedType(tag: DW_TAG_member, name: "ptr", scope: !107, file: !4, line: 1126, baseType: !95, size: 64, align: 64, offset: 768)
!330 = !DIDerivedType(tag: DW_TAG_member, name: "path", scope: !107, file: !4, line: 1127, baseType: !331, size: 64, align: 64, offset: 832)
!331 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !332, size: 64, align: 64)
!332 = !DIDerivedType(tag: DW_TAG_const_type, baseType: !184)
!333 = !DIDerivedType(tag: DW_TAG_member, name: "statbuf", scope: !107, file: !4, line: 1128, baseType: !334, size: 1280, align: 64, offset: 896)
!334 = !DIDerivedType(tag: DW_TAG_typedef, name: "uv_stat_t", file: !4, line: 349, baseType: !335)
!335 = !DICompositeType(tag: DW_TAG_structure_type, file: !4, line: 332, size: 1280, align: 64, elements: !336)
!336 = !{!337, !338, !339, !340, !341, !342, !343, !344, !345, !346, !347, !348, !349, !355, !356, !357}
!337 = !DIDerivedType(tag: DW_TAG_member, name: "st_dev", scope: !335, file: !4, line: 333, baseType: !276, size: 64, align: 64)
!338 = !DIDerivedType(tag: DW_TAG_member, name: "st_mode", scope: !335, file: !4, line: 334, baseType: !276, size: 64, align: 64, offset: 64)
!339 = !DIDerivedType(tag: DW_TAG_member, name: "st_nlink", scope: !335, file: !4, line: 335, baseType: !276, size: 64, align: 64, offset: 128)
!340 = !DIDerivedType(tag: DW_TAG_member, name: "st_uid", scope: !335, file: !4, line: 336, baseType: !276, size: 64, align: 64, offset: 192)
!341 = !DIDerivedType(tag: DW_TAG_member, name: "st_gid", scope: !335, file: !4, line: 337, baseType: !276, size: 64, align: 64, offset: 256)
!342 = !DIDerivedType(tag: DW_TAG_member, name: "st_rdev", scope: !335, file: !4, line: 338, baseType: !276, size: 64, align: 64, offset: 320)
!343 = !DIDerivedType(tag: DW_TAG_member, name: "st_ino", scope: !335, file: !4, line: 339, baseType: !276, size: 64, align: 64, offset: 384)
!344 = !DIDerivedType(tag: DW_TAG_member, name: "st_size", scope: !335, file: !4, line: 340, baseType: !276, size: 64, align: 64, offset: 448)
!345 = !DIDerivedType(tag: DW_TAG_member, name: "st_blksize", scope: !335, file: !4, line: 341, baseType: !276, size: 64, align: 64, offset: 512)
!346 = !DIDerivedType(tag: DW_TAG_member, name: "st_blocks", scope: !335, file: !4, line: 342, baseType: !276, size: 64, align: 64, offset: 576)
!347 = !DIDerivedType(tag: DW_TAG_member, name: "st_flags", scope: !335, file: !4, line: 343, baseType: !276, size: 64, align: 64, offset: 640)
!348 = !DIDerivedType(tag: DW_TAG_member, name: "st_gen", scope: !335, file: !4, line: 344, baseType: !276, size: 64, align: 64, offset: 704)
!349 = !DIDerivedType(tag: DW_TAG_member, name: "st_atim", scope: !335, file: !4, line: 345, baseType: !350, size: 128, align: 64, offset: 768)
!350 = !DIDerivedType(tag: DW_TAG_typedef, name: "uv_timespec_t", file: !4, line: 329, baseType: !351)
!351 = !DICompositeType(tag: DW_TAG_structure_type, file: !4, line: 326, size: 128, align: 64, elements: !352)
!352 = !{!353, !354}
!353 = !DIDerivedType(tag: DW_TAG_member, name: "tv_sec", scope: !351, file: !4, line: 327, baseType: !188, size: 64, align: 64)
!354 = !DIDerivedType(tag: DW_TAG_member, name: "tv_nsec", scope: !351, file: !4, line: 328, baseType: !188, size: 64, align: 64, offset: 64)
!355 = !DIDerivedType(tag: DW_TAG_member, name: "st_mtim", scope: !335, file: !4, line: 346, baseType: !350, size: 128, align: 64, offset: 896)
!356 = !DIDerivedType(tag: DW_TAG_member, name: "st_ctim", scope: !335, file: !4, line: 347, baseType: !350, size: 128, align: 64, offset: 1024)
!357 = !DIDerivedType(tag: DW_TAG_member, name: "st_birthtim", scope: !335, file: !4, line: 348, baseType: !350, size: 128, align: 64, offset: 1152)
!358 = !DIDerivedType(tag: DW_TAG_member, name: "new_path", scope: !107, file: !4, line: 1129, baseType: !331, size: 64, align: 64, offset: 2176)
!359 = !DIDerivedType(tag: DW_TAG_member, name: "file", scope: !107, file: !4, line: 1129, baseType: !360, size: 32, align: 32, offset: 2240)
!360 = !DIDerivedType(tag: DW_TAG_typedef, name: "uv_file", file: !140, line: 121, baseType: !133)
!361 = !DIDerivedType(tag: DW_TAG_member, name: "flags", scope: !107, file: !4, line: 1129, baseType: !133, size: 32, align: 32, offset: 2272)
!362 = !DIDerivedType(tag: DW_TAG_member, name: "mode", scope: !107, file: !4, line: 1129, baseType: !363, size: 32, align: 32, offset: 2304)
!363 = !DIDerivedType(tag: DW_TAG_typedef, name: "mode_t", file: !364, line: 70, baseType: !365)
!364 = !DIFile(filename: "/usr/include/x86_64-linux-gnu/sys/types.h", directory: "/data/download/cmake/cmake-master/Utilities/cmlibuv")
!365 = !DIDerivedType(tag: DW_TAG_typedef, name: "__mode_t", file: !328, line: 129, baseType: !126)
!366 = !DIDerivedType(tag: DW_TAG_member, name: "nbufs", scope: !107, file: !4, line: 1129, baseType: !126, size: 32, align: 32, offset: 2336)
!367 = !DIDerivedType(tag: DW_TAG_member, name: "bufs", scope: !107, file: !4, line: 1129, baseType: !368, size: 64, align: 64, offset: 2368)
!368 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !369, size: 64, align: 64)
!369 = !DIDerivedType(tag: DW_TAG_typedef, name: "uv_buf_t", file: !140, line: 119, baseType: !370)
!370 = !DICompositeType(tag: DW_TAG_structure_type, name: "uv_buf_t", file: !140, line: 116, size: 128, align: 64, elements: !371)
!371 = !{!372, !374}
!372 = !DIDerivedType(tag: DW_TAG_member, name: "base", scope: !370, file: !140, line: 117, baseType: !373, size: 64, align: 64)
!373 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !184, size: 64, align: 64)
!374 = !DIDerivedType(tag: DW_TAG_member, name: "len", scope: !370, file: !140, line: 118, baseType: !375, size: 64, align: 64, offset: 64)
!375 = !DIDerivedType(tag: DW_TAG_typedef, name: "size_t", file: !376, line: 62, baseType: !131)
!376 = !DIFile(filename: "/opt/llvm-build/bin/../lib/clang/3.8.0/include/stddef.h", directory: "/data/download/cmake/cmake-master/Utilities/cmlibuv")
!377 = !DIDerivedType(tag: DW_TAG_member, name: "off", scope: !107, file: !4, line: 1129, baseType: !378, size: 64, align: 64, offset: 2432)
!378 = !DIDerivedType(tag: DW_TAG_typedef, name: "off_t", file: !326, line: 92, baseType: !379)
!379 = !DIDerivedType(tag: DW_TAG_typedef, name: "__off64_t", file: !328, line: 132, baseType: !188)
!380 = !DIDerivedType(tag: DW_TAG_member, name: "uid", scope: !107, file: !4, line: 1129, baseType: !381, size: 32, align: 32, offset: 2496)
!381 = !DIDerivedType(tag: DW_TAG_typedef, name: "uv_uid_t", file: !140, line: 139, baseType: !382)
!382 = !DIDerivedType(tag: DW_TAG_typedef, name: "uid_t", file: !364, line: 80, baseType: !383)
!383 = !DIDerivedType(tag: DW_TAG_typedef, name: "__uid_t", file: !328, line: 125, baseType: !126)
!384 = !DIDerivedType(tag: DW_TAG_member, name: "gid", scope: !107, file: !4, line: 1129, baseType: !385, size: 32, align: 32, offset: 2528)
!385 = !DIDerivedType(tag: DW_TAG_typedef, name: "uv_gid_t", file: !140, line: 138, baseType: !386)
!386 = !DIDerivedType(tag: DW_TAG_typedef, name: "gid_t", file: !364, line: 65, baseType: !387)
!387 = !DIDerivedType(tag: DW_TAG_typedef, name: "__gid_t", file: !328, line: 126, baseType: !126)
!388 = !DIDerivedType(tag: DW_TAG_member, name: "atime", scope: !107, file: !4, line: 1129, baseType: !389, size: 64, align: 64, offset: 2560)
!389 = !DIBasicType(name: "double", size: 64, align: 64, encoding: DW_ATE_float)
!390 = !DIDerivedType(tag: DW_TAG_member, name: "mtime", scope: !107, file: !4, line: 1129, baseType: !389, size: 64, align: 64, offset: 2624)
!391 = !DIDerivedType(tag: DW_TAG_member, name: "work_req", scope: !107, file: !4, line: 1129, baseType: !392, size: 320, align: 64, offset: 2688)
!392 = !DICompositeType(tag: DW_TAG_structure_type, name: "uv__work", file: !393, line: 30, size: 320, align: 64, elements: !394)
!393 = !DIFile(filename: "/data/download/cmake/cmake-master/Utilities/cmlibuv/include/uv-threadpool.h", directory: "/data/download/cmake/cmake-master/Utilities/cmlibuv")
!394 = !{!395, !400, !404, !405}
!395 = !DIDerivedType(tag: DW_TAG_member, name: "work", scope: !392, file: !393, line: 31, baseType: !396, size: 64, align: 64)
!396 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !397, size: 64, align: 64)
!397 = !DISubroutineType(types: !398)
!398 = !{null, !399}
!399 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !392, size: 64, align: 64)
!400 = !DIDerivedType(tag: DW_TAG_member, name: "done", scope: !392, file: !393, line: 32, baseType: !401, size: 64, align: 64, offset: 64)
!401 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !402, size: 64, align: 64)
!402 = !DISubroutineType(types: !403)
!403 = !{null, !399, !133}
!404 = !DIDerivedType(tag: DW_TAG_member, name: "loop", scope: !392, file: !393, line: 33, baseType: !148, size: 64, align: 64, offset: 128)
!405 = !DIDerivedType(tag: DW_TAG_member, name: "wq", scope: !392, file: !393, line: 34, baseType: !100, size: 128, align: 64, offset: 192)
!406 = !DIDerivedType(tag: DW_TAG_member, name: "bufsml", scope: !107, file: !4, line: 1129, baseType: !407, size: 512, align: 64, offset: 3008)
!407 = !DICompositeType(tag: DW_TAG_array_type, baseType: !369, size: 512, align: 64, elements: !115)
!408 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !409, size: 64, align: 64)
!409 = !DICompositeType(tag: DW_TAG_structure_type, name: "iovec", file: !410, line: 43, size: 128, align: 64, elements: !411)
!410 = !DIFile(filename: "/usr/include/x86_64-linux-gnu/bits/uio.h", directory: "/data/download/cmake/cmake-master/Utilities/cmlibuv")
!411 = !{!412, !413}
!412 = !DIDerivedType(tag: DW_TAG_member, name: "iov_base", scope: !409, file: !410, line: 45, baseType: !95, size: 64, align: 64)
!413 = !DIDerivedType(tag: DW_TAG_member, name: "iov_len", scope: !409, file: !410, line: 46, baseType: !375, size: 64, align: 64, offset: 64)
!414 = !{!415, !419, !420, !423, !426, !429, !432, !433, !434, !435, !439, !442, !445, !448, !449, !450, !453, !458, !459, !460, !461, !462, !463, !466, !467, !470, !471, !474, !475, !476, !477, !480, !484, !522, !523, !524, !527, !528, !529, !534, !535, !536, !556, !560, !561, !564, !565, !566, !567, !568, !569, !570}
!415 = distinct !DISubprogram(name: "uv_fs_access", scope: !1, file: !1, line: 1016, type: !416, isLocal: false, isDefinition: true, scopeLine: 1020, flags: DIFlagPrototyped, isOptimized: false, variables: !418)
!416 = !DISubroutineType(types: !417)
!417 = !{!133, !120, !105, !331, !133, !320}
!418 = !{}
!419 = distinct !DISubprogram(name: "uv_fs_chmod", scope: !1, file: !1, line: 1028, type: !416, isLocal: false, isDefinition: true, scopeLine: 1032, flags: DIFlagPrototyped, isOptimized: false, variables: !418)
!420 = distinct !DISubprogram(name: "uv_fs_chown", scope: !1, file: !1, line: 1040, type: !421, isLocal: false, isDefinition: true, scopeLine: 1045, flags: DIFlagPrototyped, isOptimized: false, variables: !418)
!421 = !DISubroutineType(types: !422)
!422 = !{!133, !120, !105, !331, !381, !385, !320}
!423 = distinct !DISubprogram(name: "uv_fs_close", scope: !1, file: !1, line: 1054, type: !424, isLocal: false, isDefinition: true, scopeLine: 1054, flags: DIFlagPrototyped, isOptimized: false, variables: !418)
!424 = !DISubroutineType(types: !425)
!425 = !{!133, !120, !105, !360, !320}
!426 = distinct !DISubprogram(name: "uv_fs_fchmod", scope: !1, file: !1, line: 1061, type: !427, isLocal: false, isDefinition: true, scopeLine: 1065, flags: DIFlagPrototyped, isOptimized: false, variables: !418)
!427 = !DISubroutineType(types: !428)
!428 = !{!133, !120, !105, !360, !133, !320}
!429 = distinct !DISubprogram(name: "uv_fs_fchown", scope: !1, file: !1, line: 1073, type: !430, isLocal: false, isDefinition: true, scopeLine: 1078, flags: DIFlagPrototyped, isOptimized: false, variables: !418)
!430 = !DISubroutineType(types: !431)
!431 = !{!133, !120, !105, !360, !381, !385, !320}
!432 = distinct !DISubprogram(name: "uv_fs_fdatasync", scope: !1, file: !1, line: 1087, type: !424, isLocal: false, isDefinition: true, scopeLine: 1087, flags: DIFlagPrototyped, isOptimized: false, variables: !418)
!433 = distinct !DISubprogram(name: "uv_fs_fstat", scope: !1, file: !1, line: 1094, type: !424, isLocal: false, isDefinition: true, scopeLine: 1094, flags: DIFlagPrototyped, isOptimized: false, variables: !418)
!434 = distinct !DISubprogram(name: "uv_fs_fsync", scope: !1, file: !1, line: 1101, type: !424, isLocal: false, isDefinition: true, scopeLine: 1101, flags: DIFlagPrototyped, isOptimized: false, variables: !418)
!435 = distinct !DISubprogram(name: "uv_fs_ftruncate", scope: !1, file: !1, line: 1108, type: !436, isLocal: false, isDefinition: true, scopeLine: 1112, flags: DIFlagPrototyped, isOptimized: false, variables: !418)
!436 = !DISubroutineType(types: !437)
!437 = !{!133, !120, !105, !360, !438, !320}
!438 = !DIDerivedType(tag: DW_TAG_typedef, name: "int64_t", file: !277, line: 40, baseType: !188)
!439 = distinct !DISubprogram(name: "uv_fs_futime", scope: !1, file: !1, line: 1120, type: !440, isLocal: false, isDefinition: true, scopeLine: 1125, flags: DIFlagPrototyped, isOptimized: false, variables: !418)
!440 = !DISubroutineType(types: !441)
!441 = !{!133, !120, !105, !360, !389, !389, !320}
!442 = distinct !DISubprogram(name: "uv_fs_lstat", scope: !1, file: !1, line: 1134, type: !443, isLocal: false, isDefinition: true, scopeLine: 1134, flags: DIFlagPrototyped, isOptimized: false, variables: !418)
!443 = !DISubroutineType(types: !444)
!444 = !{!133, !120, !105, !331, !320}
!445 = distinct !DISubprogram(name: "uv_fs_link", scope: !1, file: !1, line: 1141, type: !446, isLocal: false, isDefinition: true, scopeLine: 1145, flags: DIFlagPrototyped, isOptimized: false, variables: !418)
!446 = !DISubroutineType(types: !447)
!447 = !{!133, !120, !105, !331, !331, !320}
!448 = distinct !DISubprogram(name: "uv_fs_mkdir", scope: !1, file: !1, line: 1152, type: !416, isLocal: false, isDefinition: true, scopeLine: 1156, flags: DIFlagPrototyped, isOptimized: false, variables: !418)
!449 = distinct !DISubprogram(name: "uv_fs_mkdtemp", scope: !1, file: !1, line: 1164, type: !443, isLocal: false, isDefinition: true, scopeLine: 1167, flags: DIFlagPrototyped, isOptimized: false, variables: !418)
!450 = distinct !DISubprogram(name: "uv_fs_open", scope: !1, file: !1, line: 1179, type: !451, isLocal: false, isDefinition: true, scopeLine: 1184, flags: DIFlagPrototyped, isOptimized: false, variables: !418)
!451 = !DISubroutineType(types: !452)
!452 = !{!133, !120, !105, !331, !133, !133, !320}
!453 = distinct !DISubprogram(name: "uv_fs_read", scope: !1, file: !1, line: 1193, type: !454, isLocal: false, isDefinition: true, scopeLine: 1198, flags: DIFlagPrototyped, isOptimized: false, variables: !418)
!454 = !DISubroutineType(types: !455)
!455 = !{!133, !120, !105, !360, !456, !126, !438, !320}
!456 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !457, size: 64, align: 64)
!457 = !DIDerivedType(tag: DW_TAG_const_type, baseType: !369)
!458 = distinct !DISubprogram(name: "uv_fs_scandir", scope: !1, file: !1, line: 1223, type: !416, isLocal: false, isDefinition: true, scopeLine: 1227, flags: DIFlagPrototyped, isOptimized: false, variables: !418)
!459 = distinct !DISubprogram(name: "uv_fs_readlink", scope: !1, file: !1, line: 1235, type: !443, isLocal: false, isDefinition: true, scopeLine: 1238, flags: DIFlagPrototyped, isOptimized: false, variables: !418)
!460 = distinct !DISubprogram(name: "uv_fs_realpath", scope: !1, file: !1, line: 1245, type: !443, isLocal: false, isDefinition: true, scopeLine: 1248, flags: DIFlagPrototyped, isOptimized: false, variables: !418)
!461 = distinct !DISubprogram(name: "uv_fs_rename", scope: !1, file: !1, line: 1255, type: !446, isLocal: false, isDefinition: true, scopeLine: 1259, flags: DIFlagPrototyped, isOptimized: false, variables: !418)
!462 = distinct !DISubprogram(name: "uv_fs_rmdir", scope: !1, file: !1, line: 1266, type: !443, isLocal: false, isDefinition: true, scopeLine: 1266, flags: DIFlagPrototyped, isOptimized: false, variables: !418)
!463 = distinct !DISubprogram(name: "uv_fs_sendfile", scope: !1, file: !1, line: 1273, type: !464, isLocal: false, isDefinition: true, scopeLine: 1279, flags: DIFlagPrototyped, isOptimized: false, variables: !418)
!464 = !DISubroutineType(types: !465)
!465 = !{!133, !120, !105, !360, !360, !438, !375, !320}
!466 = distinct !DISubprogram(name: "uv_fs_stat", scope: !1, file: !1, line: 1289, type: !443, isLocal: false, isDefinition: true, scopeLine: 1289, flags: DIFlagPrototyped, isOptimized: false, variables: !418)
!467 = distinct !DISubprogram(name: "uv_fs_symlink", scope: !1, file: !1, line: 1296, type: !468, isLocal: false, isDefinition: true, scopeLine: 1301, flags: DIFlagPrototyped, isOptimized: false, variables: !418)
!468 = !DISubroutineType(types: !469)
!469 = !{!133, !120, !105, !331, !331, !133, !320}
!470 = distinct !DISubprogram(name: "uv_fs_unlink", scope: !1, file: !1, line: 1309, type: !443, isLocal: false, isDefinition: true, scopeLine: 1309, flags: DIFlagPrototyped, isOptimized: false, variables: !418)
!471 = distinct !DISubprogram(name: "uv_fs_utime", scope: !1, file: !1, line: 1316, type: !472, isLocal: false, isDefinition: true, scopeLine: 1321, flags: DIFlagPrototyped, isOptimized: false, variables: !418)
!472 = !DISubroutineType(types: !473)
!473 = !{!133, !120, !105, !331, !389, !389, !320}
!474 = distinct !DISubprogram(name: "uv_fs_write", scope: !1, file: !1, line: 1330, type: !454, isLocal: false, isDefinition: true, scopeLine: 1336, flags: DIFlagPrototyped, isOptimized: false, variables: !418)
!475 = distinct !DISubprogram(name: "uv_fs_req_cleanup", scope: !1, file: !1, line: 1361, type: !322, isLocal: false, isDefinition: true, scopeLine: 1361, flags: DIFlagPrototyped, isOptimized: false, variables: !418)
!476 = distinct !DISubprogram(name: "uv__fs_work", scope: !1, file: !1, line: 938, type: !397, isLocal: true, isDefinition: true, scopeLine: 938, flags: DIFlagPrototyped, isOptimized: false, variables: !418)
!477 = distinct !DISubprogram(name: "uv__fs_fdatasync", scope: !1, file: !1, line: 129, type: !478, isLocal: true, isDefinition: true, scopeLine: 129, flags: DIFlagPrototyped, isOptimized: false, variables: !418)
!478 = !DISubroutineType(types: !479)
!479 = !{!325, !105}
!480 = distinct !DISubprogram(name: "uv__fs_fstat", scope: !1, file: !1, line: 880, type: !481, isLocal: true, isDefinition: true, scopeLine: 880, flags: DIFlagPrototyped, isOptimized: false, variables: !418)
!481 = !DISubroutineType(types: !482)
!482 = !{!133, !133, !483}
!483 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !334, size: 64, align: 64)
!484 = distinct !DISubprogram(name: "uv__to_stat", scope: !1, file: !1, line: 779, type: !485, isLocal: true, isDefinition: true, scopeLine: 779, flags: DIFlagPrototyped, isOptimized: false, variables: !418)
!485 = !DISubroutineType(types: !486)
!486 = !{null, !487, !483}
!487 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !488, size: 64, align: 64)
!488 = !DICompositeType(tag: DW_TAG_structure_type, name: "stat", file: !489, line: 46, size: 1152, align: 64, elements: !490)
!489 = !DIFile(filename: "/usr/include/x86_64-linux-gnu/bits/stat.h", directory: "/data/download/cmake/cmake-master/Utilities/cmlibuv")
!490 = !{!491, !493, !495, !497, !498, !499, !500, !501, !502, !504, !506, !508, !516, !517, !518}
!491 = !DIDerivedType(tag: DW_TAG_member, name: "st_dev", scope: !488, file: !489, line: 48, baseType: !492, size: 64, align: 64)
!492 = !DIDerivedType(tag: DW_TAG_typedef, name: "__dev_t", file: !328, line: 124, baseType: !131)
!493 = !DIDerivedType(tag: DW_TAG_member, name: "st_ino", scope: !488, file: !489, line: 53, baseType: !494, size: 64, align: 64, offset: 64)
!494 = !DIDerivedType(tag: DW_TAG_typedef, name: "__ino_t", file: !328, line: 127, baseType: !131)
!495 = !DIDerivedType(tag: DW_TAG_member, name: "st_nlink", scope: !488, file: !489, line: 61, baseType: !496, size: 64, align: 64, offset: 128)
!496 = !DIDerivedType(tag: DW_TAG_typedef, name: "__nlink_t", file: !328, line: 130, baseType: !131)
!497 = !DIDerivedType(tag: DW_TAG_member, name: "st_mode", scope: !488, file: !489, line: 62, baseType: !365, size: 32, align: 32, offset: 192)
!498 = !DIDerivedType(tag: DW_TAG_member, name: "st_uid", scope: !488, file: !489, line: 64, baseType: !383, size: 32, align: 32, offset: 224)
!499 = !DIDerivedType(tag: DW_TAG_member, name: "st_gid", scope: !488, file: !489, line: 65, baseType: !387, size: 32, align: 32, offset: 256)
!500 = !DIDerivedType(tag: DW_TAG_member, name: "__pad0", scope: !488, file: !489, line: 67, baseType: !133, size: 32, align: 32, offset: 288)
!501 = !DIDerivedType(tag: DW_TAG_member, name: "st_rdev", scope: !488, file: !489, line: 69, baseType: !492, size: 64, align: 64, offset: 320)
!502 = !DIDerivedType(tag: DW_TAG_member, name: "st_size", scope: !488, file: !489, line: 74, baseType: !503, size: 64, align: 64, offset: 384)
!503 = !DIDerivedType(tag: DW_TAG_typedef, name: "__off_t", file: !328, line: 131, baseType: !188)
!504 = !DIDerivedType(tag: DW_TAG_member, name: "st_blksize", scope: !488, file: !489, line: 78, baseType: !505, size: 64, align: 64, offset: 448)
!505 = !DIDerivedType(tag: DW_TAG_typedef, name: "__blksize_t", file: !328, line: 153, baseType: !188)
!506 = !DIDerivedType(tag: DW_TAG_member, name: "st_blocks", scope: !488, file: !489, line: 80, baseType: !507, size: 64, align: 64, offset: 512)
!507 = !DIDerivedType(tag: DW_TAG_typedef, name: "__blkcnt_t", file: !328, line: 158, baseType: !188)
!508 = !DIDerivedType(tag: DW_TAG_member, name: "st_atim", scope: !488, file: !489, line: 91, baseType: !509, size: 128, align: 64, offset: 576)
!509 = !DICompositeType(tag: DW_TAG_structure_type, name: "timespec", file: !510, line: 120, size: 128, align: 64, elements: !511)
!510 = !DIFile(filename: "/usr/include/time.h", directory: "/data/download/cmake/cmake-master/Utilities/cmlibuv")
!511 = !{!512, !514}
!512 = !DIDerivedType(tag: DW_TAG_member, name: "tv_sec", scope: !509, file: !510, line: 122, baseType: !513, size: 64, align: 64)
!513 = !DIDerivedType(tag: DW_TAG_typedef, name: "__time_t", file: !328, line: 139, baseType: !188)
!514 = !DIDerivedType(tag: DW_TAG_member, name: "tv_nsec", scope: !509, file: !510, line: 123, baseType: !515, size: 64, align: 64, offset: 64)
!515 = !DIDerivedType(tag: DW_TAG_typedef, name: "__syscall_slong_t", file: !328, line: 175, baseType: !188)
!516 = !DIDerivedType(tag: DW_TAG_member, name: "st_mtim", scope: !488, file: !489, line: 92, baseType: !509, size: 128, align: 64, offset: 704)
!517 = !DIDerivedType(tag: DW_TAG_member, name: "st_ctim", scope: !488, file: !489, line: 93, baseType: !509, size: 128, align: 64, offset: 832)
!518 = !DIDerivedType(tag: DW_TAG_member, name: "__glibc_reserved", scope: !488, file: !489, line: 106, baseType: !519, size: 192, align: 64, offset: 960)
!519 = !DICompositeType(tag: DW_TAG_array_type, baseType: !515, size: 192, align: 64, elements: !520)
!520 = !{!521}
!521 = !DISubrange(count: 3)
!522 = distinct !DISubprogram(name: "uv__fs_fsync", scope: !1, file: !1, line: 145, type: !478, isLocal: true, isDefinition: true, scopeLine: 145, flags: DIFlagPrototyped, isOptimized: false, variables: !418)
!523 = distinct !DISubprogram(name: "uv__fs_futime", scope: !1, file: !1, line: 155, type: !478, isLocal: true, isDefinition: true, scopeLine: 155, flags: DIFlagPrototyped, isOptimized: false, variables: !418)
!524 = distinct !DISubprogram(name: "uv__fs_lstat", scope: !1, file: !1, line: 868, type: !525, isLocal: true, isDefinition: true, scopeLine: 868, flags: DIFlagPrototyped, isOptimized: false, variables: !418)
!525 = !DISubroutineType(types: !526)
!526 = !{!133, !331, !483}
!527 = distinct !DISubprogram(name: "uv__fs_mkdtemp", scope: !1, file: !1, line: 258, type: !478, isLocal: true, isDefinition: true, scopeLine: 258, flags: DIFlagPrototyped, isOptimized: false, variables: !418)
!528 = distinct !DISubprogram(name: "uv__fs_open", scope: !1, file: !1, line: 263, type: !478, isLocal: true, isDefinition: true, scopeLine: 263, flags: DIFlagPrototyped, isOptimized: false, variables: !418)
!529 = distinct !DISubprogram(name: "uv__fs_buf_iter", scope: !1, file: !1, line: 893, type: !530, isLocal: true, isDefinition: true, scopeLine: 893, flags: DIFlagPrototyped, isOptimized: false, variables: !418)
!530 = !DISubroutineType(types: !531)
!531 = !{!325, !105, !532}
!532 = !DIDerivedType(tag: DW_TAG_typedef, name: "uv__fs_buf_iter_processor", file: !1, line: 892, baseType: !533)
!533 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !478, size: 64, align: 64)
!534 = distinct !DISubprogram(name: "uv__fs_read", scope: !1, file: !1, line: 301, type: !478, isLocal: true, isDefinition: true, scopeLine: 301, flags: DIFlagPrototyped, isOptimized: false, variables: !418)
!535 = distinct !DISubprogram(name: "uv__fs_scandir", scope: !1, file: !1, line: 391, type: !478, isLocal: true, isDefinition: true, scopeLine: 391, flags: DIFlagPrototyped, isOptimized: false, variables: !418)
!536 = distinct !DISubprogram(name: "uv__fs_scandir_filter", scope: !1, file: !1, line: 381, type: !537, isLocal: true, isDefinition: true, scopeLine: 381, flags: DIFlagPrototyped, isOptimized: false, variables: !418)
!537 = !DISubroutineType(types: !538)
!538 = !{!133, !539}
!539 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !540, size: 64, align: 64)
!540 = !DIDerivedType(tag: DW_TAG_const_type, baseType: !541)
!541 = !DIDerivedType(tag: DW_TAG_typedef, name: "uv__dirent_t", file: !140, line: 141, baseType: !542)
!542 = !DICompositeType(tag: DW_TAG_structure_type, name: "dirent", file: !543, line: 22, size: 2240, align: 64, elements: !544)
!543 = !DIFile(filename: "/usr/include/x86_64-linux-gnu/bits/dirent.h", directory: "/data/download/cmake/cmake-master/Utilities/cmlibuv")
!544 = !{!545, !547, !548, !550, !552}
!545 = !DIDerivedType(tag: DW_TAG_member, name: "d_ino", scope: !542, file: !543, line: 28, baseType: !546, size: 64, align: 64)
!546 = !DIDerivedType(tag: DW_TAG_typedef, name: "__ino64_t", file: !328, line: 128, baseType: !131)
!547 = !DIDerivedType(tag: DW_TAG_member, name: "d_off", scope: !542, file: !543, line: 29, baseType: !379, size: 64, align: 64, offset: 64)
!548 = !DIDerivedType(tag: DW_TAG_member, name: "d_reclen", scope: !542, file: !543, line: 31, baseType: !549, size: 16, align: 16, offset: 128)
!549 = !DIBasicType(name: "unsigned short", size: 16, align: 16, encoding: DW_ATE_unsigned)
!550 = !DIDerivedType(tag: DW_TAG_member, name: "d_type", scope: !542, file: !543, line: 32, baseType: !551, size: 8, align: 8, offset: 144)
!551 = !DIBasicType(name: "unsigned char", size: 8, align: 8, encoding: DW_ATE_unsigned_char)
!552 = !DIDerivedType(tag: DW_TAG_member, name: "d_name", scope: !542, file: !543, line: 33, baseType: !553, size: 2048, align: 8, offset: 152)
!553 = !DICompositeType(tag: DW_TAG_array_type, baseType: !184, size: 2048, align: 8, elements: !554)
!554 = !{!555}
!555 = !DISubrange(count: 256)
!556 = distinct !DISubprogram(name: "uv__fs_scandir_sort", scope: !1, file: !1, line: 386, type: !557, isLocal: true, isDefinition: true, scopeLine: 386, flags: DIFlagPrototyped, isOptimized: false, variables: !418)
!557 = !DISubroutineType(types: !558)
!558 = !{!133, !559, !559}
!559 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !539, size: 64, align: 64)
!560 = distinct !DISubprogram(name: "uv__fs_readlink", scope: !1, file: !1, line: 433, type: !478, isLocal: true, isDefinition: true, scopeLine: 433, flags: DIFlagPrototyped, isOptimized: false, variables: !418)
!561 = distinct !DISubprogram(name: "uv__fs_pathmax_size", scope: !1, file: !1, line: 417, type: !562, isLocal: true, isDefinition: true, scopeLine: 417, flags: DIFlagPrototyped, isOptimized: false, variables: !418)
!562 = !DISubroutineType(types: !563)
!563 = !{!325, !331}
!564 = distinct !DISubprogram(name: "uv__fs_realpath", scope: !1, file: !1, line: 458, type: !478, isLocal: true, isDefinition: true, scopeLine: 458, flags: DIFlagPrototyped, isOptimized: false, variables: !418)
!565 = distinct !DISubprogram(name: "uv__fs_sendfile", scope: !1, file: !1, line: 594, type: !478, isLocal: true, isDefinition: true, scopeLine: 594, flags: DIFlagPrototyped, isOptimized: false, variables: !418)
!566 = distinct !DISubprogram(name: "uv__fs_sendfile_emul", scope: !1, file: !1, line: 480, type: !478, isLocal: true, isDefinition: true, scopeLine: 480, flags: DIFlagPrototyped, isOptimized: false, variables: !418)
!567 = distinct !DISubprogram(name: "uv__fs_stat", scope: !1, file: !1, line: 856, type: !525, isLocal: true, isDefinition: true, scopeLine: 856, flags: DIFlagPrototyped, isOptimized: false, variables: !418)
!568 = distinct !DISubprogram(name: "uv__fs_utime", scope: !1, file: !1, line: 693, type: !478, isLocal: true, isDefinition: true, scopeLine: 693, flags: DIFlagPrototyped, isOptimized: false, variables: !418)
!569 = distinct !DISubprogram(name: "uv__fs_write", scope: !1, file: !1, line: 701, type: !478, isLocal: true, isDefinition: true, scopeLine: 701, flags: DIFlagPrototyped, isOptimized: false, variables: !418)
!570 = distinct !DISubprogram(name: "uv__fs_done", scope: !1, file: !1, line: 1001, type: !402, isLocal: true, isDefinition: true, scopeLine: 1001, flags: DIFlagPrototyped, isOptimized: false, variables: !418)
!571 = !{!572, !573, !574, !575}
!572 = !DIGlobalVariable(name: "no_utimesat", scope: !523, file: !1, line: 160, type: !133, isLocal: true, isDefinition: true, variable: i32* @uv__fs_futime.no_utimesat)
!573 = !DIGlobalVariable(name: "no_cloexec_support", scope: !528, file: !1, line: 264, type: !133, isLocal: true, isDefinition: true, variable: i32* @uv__fs_open.no_cloexec_support)
!574 = !DIGlobalVariable(name: "no_preadv", scope: !534, file: !1, line: 303, type: !133, isLocal: true, isDefinition: true, variable: i32* @uv__fs_read.no_preadv)
!575 = !DIGlobalVariable(name: "no_pwritev", scope: !569, file: !1, line: 703, type: !133, isLocal: true, isDefinition: true, variable: i32* @uv__fs_write.no_pwritev)
!576 = !{i32 2, !"Dwarf Version", i32 4}
!577 = !{i32 2, !"Debug Info Version", i32 3}
!578 = !{!"clang version 3.8.0 (tags/RELEASE_380/final)"}
!579 = !DILocalVariable(name: "loop", arg: 1, scope: !415, file: !1, line: 1016, type: !120)
!580 = !DIExpression()
!581 = !DILocation(line: 1016, column: 29, scope: !415)
!582 = !DILocalVariable(name: "req", arg: 2, scope: !415, file: !1, line: 1017, type: !105)
!583 = !DILocation(line: 1017, column: 27, scope: !415)
!584 = !DILocalVariable(name: "path", arg: 3, scope: !415, file: !1, line: 1018, type: !331)
!585 = !DILocation(line: 1018, column: 30, scope: !415)
!586 = !DILocalVariable(name: "flags", arg: 4, scope: !415, file: !1, line: 1019, type: !133)
!587 = !DILocation(line: 1019, column: 22, scope: !415)
!588 = !DILocalVariable(name: "cb", arg: 5, scope: !415, file: !1, line: 1020, type: !320)
!589 = !DILocation(line: 1020, column: 27, scope: !415)
!590 = !DILocation(line: 1021, column: 3, scope: !415)
!591 = !DILocation(line: 1021, column: 3, scope: !592)
!592 = !DILexicalBlockFile(scope: !593, file: !1, discriminator: 1)
!593 = distinct !DILexicalBlock(scope: !415, file: !1, line: 1021, column: 3)
!594 = !DILocation(line: 1021, column: 3, scope: !595)
!595 = !DILexicalBlockFile(scope: !596, file: !1, discriminator: 2)
!596 = distinct !DILexicalBlock(scope: !593, file: !1, line: 1021, column: 3)
!597 = !DILocation(line: 1021, column: 3, scope: !598)
!598 = !DILexicalBlockFile(scope: !599, file: !1, discriminator: 3)
!599 = distinct !DILexicalBlock(scope: !596, file: !1, line: 1021, column: 3)
!600 = !DILocation(line: 1021, column: 3, scope: !601)
!601 = !DILexicalBlockFile(scope: !602, file: !1, discriminator: 4)
!602 = distinct !DILexicalBlock(scope: !599, file: !1, line: 1021, column: 3)
!603 = !DILocation(line: 1021, column: 3, scope: !604)
!604 = !DILexicalBlockFile(scope: !599, file: !1, discriminator: 5)
!605 = !DILocation(line: 1021, column: 3, scope: !606)
!606 = !DILexicalBlockFile(scope: !607, file: !1, discriminator: 6)
!607 = distinct !DILexicalBlock(scope: !599, file: !1, line: 1021, column: 3)
!608 = !DILocation(line: 1021, column: 3, scope: !609)
!609 = !DILexicalBlockFile(scope: !610, file: !1, discriminator: 7)
!610 = distinct !DILexicalBlock(scope: !607, file: !1, line: 1021, column: 3)
!611 = !DILocation(line: 1021, column: 3, scope: !612)
!612 = !DILexicalBlockFile(scope: !607, file: !1, discriminator: 8)
!613 = !DILocation(line: 1021, column: 3, scope: !614)
!614 = !DILexicalBlockFile(scope: !599, file: !1, discriminator: 9)
!615 = !DILocation(line: 1021, column: 3, scope: !616)
!616 = !DILexicalBlockFile(scope: !599, file: !1, discriminator: 10)
!617 = !DILocation(line: 1021, column: 3, scope: !618)
!618 = !DILexicalBlockFile(scope: !593, file: !1, discriminator: 11)
!619 = !DILocation(line: 1022, column: 3, scope: !415)
!620 = !DILocation(line: 1022, column: 3, scope: !621)
!621 = !DILexicalBlockFile(scope: !622, file: !1, discriminator: 1)
!622 = distinct !DILexicalBlock(scope: !415, file: !1, line: 1022, column: 3)
!623 = !DILocation(line: 1022, column: 3, scope: !624)
!624 = !DILexicalBlockFile(scope: !622, file: !1, discriminator: 2)
!625 = !DILocation(line: 1022, column: 3, scope: !626)
!626 = !DILexicalBlockFile(scope: !622, file: !1, discriminator: 3)
!627 = !DILocation(line: 1022, column: 3, scope: !628)
!628 = !DILexicalBlockFile(scope: !622, file: !1, discriminator: 4)
!629 = !DILocation(line: 1022, column: 3, scope: !630)
!630 = !DILexicalBlockFile(scope: !631, file: !1, discriminator: 5)
!631 = distinct !DILexicalBlock(scope: !622, file: !1, line: 1022, column: 3)
!632 = !DILocation(line: 1022, column: 3, scope: !633)
!633 = !DILexicalBlockFile(scope: !634, file: !1, discriminator: 6)
!634 = distinct !DILexicalBlock(scope: !631, file: !1, line: 1022, column: 3)
!635 = !DILocation(line: 1022, column: 3, scope: !636)
!636 = !DILexicalBlockFile(scope: !637, file: !1, discriminator: 7)
!637 = distinct !DILexicalBlock(scope: !631, file: !1, line: 1022, column: 3)
!638 = !DILocation(line: 1022, column: 3, scope: !639)
!639 = !DILexicalBlockFile(scope: !640, file: !1, discriminator: 8)
!640 = distinct !DILexicalBlock(scope: !641, file: !1, line: 1022, column: 3)
!641 = distinct !DILexicalBlock(scope: !637, file: !1, line: 1022, column: 3)
!642 = !DILocation(line: 1022, column: 3, scope: !643)
!643 = !DILexicalBlockFile(scope: !644, file: !1, discriminator: 9)
!644 = distinct !DILexicalBlock(scope: !640, file: !1, line: 1022, column: 3)
!645 = !DILocation(line: 1022, column: 3, scope: !646)
!646 = !DILexicalBlockFile(scope: !644, file: !1, discriminator: 10)
!647 = !DILocation(line: 1022, column: 3, scope: !648)
!648 = !DILexicalBlockFile(scope: !644, file: !1, discriminator: 11)
!649 = !DILocation(line: 1022, column: 3, scope: !650)
!650 = !DILexicalBlockFile(scope: !644, file: !1, discriminator: 12)
!651 = !DILocation(line: 1022, column: 3, scope: !652)
!652 = !DILexicalBlockFile(scope: !644, file: !1, discriminator: 13)
!653 = !DILocation(line: 1022, column: 3, scope: !654)
!654 = !DILexicalBlockFile(scope: !655, file: !1, discriminator: 14)
!655 = distinct !DILexicalBlock(scope: !644, file: !1, line: 1022, column: 3)
!656 = !DILocation(line: 1022, column: 3, scope: !657)
!657 = !DILexicalBlockFile(scope: !644, file: !1, discriminator: 15)
!658 = !DILocation(line: 1022, column: 3, scope: !659)
!659 = !DILexicalBlockFile(scope: !640, file: !1, discriminator: 16)
!660 = !DILocation(line: 1022, column: 3, scope: !661)
!661 = !DILexicalBlockFile(scope: !622, file: !1, discriminator: 17)
!662 = !DILocation(line: 1023, column: 16, scope: !415)
!663 = !DILocation(line: 1023, column: 3, scope: !415)
!664 = !DILocation(line: 1023, column: 8, scope: !415)
!665 = !DILocation(line: 1023, column: 14, scope: !415)
!666 = !DILocation(line: 1024, column: 3, scope: !415)
!667 = !DILocation(line: 1024, column: 3, scope: !668)
!668 = !DILexicalBlockFile(scope: !669, file: !1, discriminator: 1)
!669 = distinct !DILexicalBlock(scope: !670, file: !1, line: 1024, column: 3)
!670 = distinct !DILexicalBlock(scope: !415, file: !1, line: 1024, column: 3)
!671 = !DILocation(line: 1024, column: 3, scope: !672)
!672 = !DILexicalBlockFile(scope: !673, file: !1, discriminator: 2)
!673 = distinct !DILexicalBlock(scope: !669, file: !1, line: 1024, column: 3)
!674 = !DILocation(line: 1024, column: 3, scope: !675)
!675 = !DILexicalBlockFile(scope: !676, file: !1, discriminator: 3)
!676 = distinct !DILexicalBlock(scope: !669, file: !1, line: 1024, column: 3)
!677 = !DILocation(line: 1025, column: 1, scope: !415)
!678 = !DILocalVariable(name: "w", arg: 1, scope: !476, file: !1, line: 938, type: !399)
!679 = !DILocation(line: 938, column: 42, scope: !476)
!680 = !DILocalVariable(name: "retry_on_eintr", scope: !476, file: !1, line: 939, type: !133)
!681 = !DILocation(line: 939, column: 7, scope: !476)
!682 = !DILocalVariable(name: "req", scope: !476, file: !1, line: 940, type: !105)
!683 = !DILocation(line: 940, column: 12, scope: !476)
!684 = !DILocalVariable(name: "r", scope: !476, file: !1, line: 941, type: !325)
!685 = !DILocation(line: 941, column: 11, scope: !476)
!686 = !DILocation(line: 943, column: 9, scope: !476)
!687 = !DILocation(line: 943, column: 7, scope: !476)
!688 = !DILocation(line: 944, column: 22, scope: !476)
!689 = !DILocation(line: 944, column: 27, scope: !476)
!690 = !DILocation(line: 944, column: 35, scope: !476)
!691 = !DILocation(line: 944, column: 20, scope: !476)
!692 = !DILocation(line: 944, column: 18, scope: !476)
!693 = !DILocation(line: 946, column: 3, scope: !476)
!694 = !DILocation(line: 947, column: 5, scope: !695)
!695 = distinct !DILexicalBlock(scope: !476, file: !1, line: 946, column: 6)
!696 = !DILocation(line: 947, column: 11, scope: !695)
!697 = !DILocation(line: 954, column: 13, scope: !695)
!698 = !DILocation(line: 954, column: 18, scope: !695)
!699 = !DILocation(line: 954, column: 5, scope: !695)
!700 = !DILocation(line: 955, column: 5, scope: !701)
!701 = distinct !DILexicalBlock(scope: !695, file: !1, line: 954, column: 27)
!702 = !DILocation(line: 956, column: 5, scope: !701)
!703 = !DILocation(line: 957, column: 5, scope: !701)
!704 = !DILocation(line: 958, column: 5, scope: !701)
!705 = !DILocation(line: 959, column: 5, scope: !701)
!706 = !DILocation(line: 960, column: 5, scope: !701)
!707 = !DILocation(line: 961, column: 5, scope: !701)
!708 = !DILocation(line: 962, column: 5, scope: !701)
!709 = !DILocation(line: 963, column: 5, scope: !701)
!710 = !DILocation(line: 964, column: 5, scope: !701)
!711 = !DILocation(line: 965, column: 5, scope: !701)
!712 = !DILocation(line: 966, column: 5, scope: !701)
!713 = !DILocation(line: 967, column: 5, scope: !701)
!714 = !DILocation(line: 968, column: 5, scope: !701)
!715 = !DILocation(line: 969, column: 5, scope: !701)
!716 = !DILocation(line: 970, column: 5, scope: !701)
!717 = !DILocation(line: 971, column: 5, scope: !701)
!718 = !DILocation(line: 972, column: 5, scope: !701)
!719 = !DILocation(line: 973, column: 5, scope: !701)
!720 = !DILocation(line: 974, column: 5, scope: !701)
!721 = !DILocation(line: 975, column: 5, scope: !701)
!722 = !DILocation(line: 976, column: 5, scope: !701)
!723 = !DILocation(line: 977, column: 5, scope: !701)
!724 = !DILocation(line: 978, column: 5, scope: !701)
!725 = !DILocation(line: 979, column: 5, scope: !701)
!726 = !DILocation(line: 980, column: 5, scope: !701)
!727 = !DILocation(line: 981, column: 5, scope: !701)
!728 = !DILocation(line: 982, column: 5, scope: !701)
!729 = !DILocation(line: 983, column: 14, scope: !701)
!730 = !DILocation(line: 986, column: 3, scope: !695)
!731 = !DILocation(line: 986, column: 12, scope: !732)
!732 = !DILexicalBlockFile(scope: !476, file: !1, discriminator: 1)
!733 = !DILocation(line: 986, column: 14, scope: !732)
!734 = !DILocation(line: 986, column: 20, scope: !732)
!735 = !DILocation(line: 986, column: 23, scope: !736)
!736 = !DILexicalBlockFile(scope: !476, file: !1, discriminator: 2)
!737 = !DILocation(line: 986, column: 29, scope: !736)
!738 = !DILocation(line: 986, column: 38, scope: !736)
!739 = !DILocation(line: 986, column: 41, scope: !740)
!740 = !DILexicalBlockFile(scope: !476, file: !1, discriminator: 3)
!741 = !DILocation(line: 986, column: 38, scope: !740)
!742 = !DILocation(line: 986, column: 3, scope: !743)
!743 = !DILexicalBlockFile(scope: !695, file: !1, discriminator: 4)
!744 = !DILocation(line: 988, column: 7, scope: !745)
!745 = distinct !DILexicalBlock(scope: !476, file: !1, line: 988, column: 7)
!746 = !DILocation(line: 988, column: 9, scope: !745)
!747 = !DILocation(line: 988, column: 7, scope: !476)
!748 = !DILocation(line: 989, column: 20, scope: !745)
!749 = !DILocation(line: 989, column: 19, scope: !745)
!750 = !DILocation(line: 989, column: 5, scope: !745)
!751 = !DILocation(line: 989, column: 10, scope: !745)
!752 = !DILocation(line: 989, column: 17, scope: !745)
!753 = !DILocation(line: 991, column: 19, scope: !745)
!754 = !DILocation(line: 991, column: 5, scope: !745)
!755 = !DILocation(line: 991, column: 10, scope: !745)
!756 = !DILocation(line: 991, column: 17, scope: !745)
!757 = !DILocation(line: 993, column: 7, scope: !758)
!758 = distinct !DILexicalBlock(scope: !476, file: !1, line: 993, column: 7)
!759 = !DILocation(line: 993, column: 9, scope: !758)
!760 = !DILocation(line: 993, column: 14, scope: !758)
!761 = !DILocation(line: 993, column: 18, scope: !762)
!762 = !DILexicalBlockFile(scope: !758, file: !1, discriminator: 1)
!763 = !DILocation(line: 993, column: 23, scope: !762)
!764 = !DILocation(line: 993, column: 31, scope: !762)
!765 = !DILocation(line: 993, column: 45, scope: !762)
!766 = !DILocation(line: 994, column: 18, scope: !758)
!767 = !DILocation(line: 994, column: 23, scope: !758)
!768 = !DILocation(line: 994, column: 31, scope: !758)
!769 = !DILocation(line: 994, column: 46, scope: !758)
!770 = !DILocation(line: 995, column: 18, scope: !758)
!771 = !DILocation(line: 995, column: 23, scope: !758)
!772 = !DILocation(line: 995, column: 31, scope: !758)
!773 = !DILocation(line: 993, column: 7, scope: !736)
!774 = !DILocation(line: 996, column: 17, scope: !775)
!775 = distinct !DILexicalBlock(scope: !758, file: !1, line: 995, column: 48)
!776 = !DILocation(line: 996, column: 22, scope: !775)
!777 = !DILocation(line: 996, column: 16, scope: !775)
!778 = !DILocation(line: 996, column: 5, scope: !775)
!779 = !DILocation(line: 996, column: 10, scope: !775)
!780 = !DILocation(line: 996, column: 14, scope: !775)
!781 = !DILocation(line: 997, column: 3, scope: !775)
!782 = !DILocation(line: 998, column: 1, scope: !476)
!783 = !DILocalVariable(name: "w", arg: 1, scope: !570, file: !1, line: 1001, type: !399)
!784 = !DILocation(line: 1001, column: 42, scope: !570)
!785 = !DILocalVariable(name: "status", arg: 2, scope: !570, file: !1, line: 1001, type: !133)
!786 = !DILocation(line: 1001, column: 49, scope: !570)
!787 = !DILocalVariable(name: "req", scope: !570, file: !1, line: 1002, type: !105)
!788 = !DILocation(line: 1002, column: 12, scope: !570)
!789 = !DILocation(line: 1004, column: 9, scope: !570)
!790 = !DILocation(line: 1004, column: 7, scope: !570)
!791 = !DILocation(line: 1005, column: 3, scope: !570)
!792 = !DILocation(line: 1005, column: 3, scope: !793)
!793 = !DILexicalBlockFile(scope: !794, file: !1, discriminator: 1)
!794 = distinct !DILexicalBlock(scope: !570, file: !1, line: 1005, column: 3)
!795 = !DILocation(line: 1005, column: 3, scope: !796)
!796 = !DILexicalBlockFile(scope: !794, file: !1, discriminator: 2)
!797 = !DILocation(line: 1005, column: 3, scope: !798)
!798 = !DILexicalBlockFile(scope: !794, file: !1, discriminator: 3)
!799 = !DILocation(line: 1005, column: 3, scope: !800)
!800 = !DILexicalBlockFile(scope: !794, file: !1, discriminator: 4)
!801 = !DILocation(line: 1005, column: 3, scope: !802)
!802 = !DILexicalBlockFile(scope: !794, file: !1, discriminator: 5)
!803 = !DILocation(line: 1005, column: 3, scope: !804)
!804 = !DILexicalBlockFile(scope: !805, file: !1, discriminator: 6)
!805 = distinct !DILexicalBlock(scope: !794, file: !1, line: 1005, column: 3)
!806 = !DILocation(line: 1005, column: 3, scope: !807)
!807 = !DILexicalBlockFile(scope: !794, file: !1, discriminator: 7)
!808 = !DILocation(line: 1007, column: 7, scope: !809)
!809 = distinct !DILexicalBlock(scope: !570, file: !1, line: 1007, column: 7)
!810 = !DILocation(line: 1007, column: 14, scope: !809)
!811 = !DILocation(line: 1007, column: 7, scope: !570)
!812 = !DILocation(line: 1008, column: 5, scope: !813)
!813 = distinct !DILexicalBlock(scope: !809, file: !1, line: 1007, column: 29)
!814 = !DILocation(line: 1008, column: 5, scope: !815)
!815 = !DILexicalBlockFile(scope: !813, file: !1, discriminator: 1)
!816 = !DILocation(line: 1008, column: 5, scope: !817)
!817 = !DILexicalBlockFile(scope: !813, file: !1, discriminator: 2)
!818 = !DILocation(line: 1008, column: 5, scope: !819)
!819 = !DILexicalBlockFile(scope: !813, file: !1, discriminator: 3)
!820 = !DILocation(line: 1009, column: 5, scope: !813)
!821 = !DILocation(line: 1009, column: 10, scope: !813)
!822 = !DILocation(line: 1009, column: 17, scope: !813)
!823 = !DILocation(line: 1010, column: 3, scope: !813)
!824 = !DILocation(line: 1012, column: 3, scope: !570)
!825 = !DILocation(line: 1012, column: 8, scope: !570)
!826 = !DILocation(line: 1012, column: 11, scope: !570)
!827 = !DILocation(line: 1013, column: 1, scope: !570)
!828 = !DILocalVariable(name: "loop", arg: 1, scope: !419, file: !1, line: 1028, type: !120)
!829 = !DILocation(line: 1028, column: 28, scope: !419)
!830 = !DILocalVariable(name: "req", arg: 2, scope: !419, file: !1, line: 1029, type: !105)
!831 = !DILocation(line: 1029, column: 26, scope: !419)
!832 = !DILocalVariable(name: "path", arg: 3, scope: !419, file: !1, line: 1030, type: !331)
!833 = !DILocation(line: 1030, column: 29, scope: !419)
!834 = !DILocalVariable(name: "mode", arg: 4, scope: !419, file: !1, line: 1031, type: !133)
!835 = !DILocation(line: 1031, column: 21, scope: !419)
!836 = !DILocalVariable(name: "cb", arg: 5, scope: !419, file: !1, line: 1032, type: !320)
!837 = !DILocation(line: 1032, column: 26, scope: !419)
!838 = !DILocation(line: 1033, column: 3, scope: !419)
!839 = !DILocation(line: 1033, column: 3, scope: !840)
!840 = !DILexicalBlockFile(scope: !841, file: !1, discriminator: 1)
!841 = distinct !DILexicalBlock(scope: !419, file: !1, line: 1033, column: 3)
!842 = !DILocation(line: 1033, column: 3, scope: !843)
!843 = !DILexicalBlockFile(scope: !844, file: !1, discriminator: 2)
!844 = distinct !DILexicalBlock(scope: !841, file: !1, line: 1033, column: 3)
!845 = !DILocation(line: 1033, column: 3, scope: !846)
!846 = !DILexicalBlockFile(scope: !847, file: !1, discriminator: 3)
!847 = distinct !DILexicalBlock(scope: !844, file: !1, line: 1033, column: 3)
!848 = !DILocation(line: 1033, column: 3, scope: !849)
!849 = !DILexicalBlockFile(scope: !850, file: !1, discriminator: 4)
!850 = distinct !DILexicalBlock(scope: !847, file: !1, line: 1033, column: 3)
!851 = !DILocation(line: 1033, column: 3, scope: !852)
!852 = !DILexicalBlockFile(scope: !847, file: !1, discriminator: 5)
!853 = !DILocation(line: 1033, column: 3, scope: !854)
!854 = !DILexicalBlockFile(scope: !855, file: !1, discriminator: 6)
!855 = distinct !DILexicalBlock(scope: !847, file: !1, line: 1033, column: 3)
!856 = !DILocation(line: 1033, column: 3, scope: !857)
!857 = !DILexicalBlockFile(scope: !858, file: !1, discriminator: 7)
!858 = distinct !DILexicalBlock(scope: !855, file: !1, line: 1033, column: 3)
!859 = !DILocation(line: 1033, column: 3, scope: !860)
!860 = !DILexicalBlockFile(scope: !855, file: !1, discriminator: 8)
!861 = !DILocation(line: 1033, column: 3, scope: !862)
!862 = !DILexicalBlockFile(scope: !847, file: !1, discriminator: 9)
!863 = !DILocation(line: 1033, column: 3, scope: !864)
!864 = !DILexicalBlockFile(scope: !847, file: !1, discriminator: 10)
!865 = !DILocation(line: 1033, column: 3, scope: !866)
!866 = !DILexicalBlockFile(scope: !841, file: !1, discriminator: 11)
!867 = !DILocation(line: 1034, column: 3, scope: !419)
!868 = !DILocation(line: 1034, column: 3, scope: !869)
!869 = !DILexicalBlockFile(scope: !870, file: !1, discriminator: 1)
!870 = distinct !DILexicalBlock(scope: !419, file: !1, line: 1034, column: 3)
!871 = !DILocation(line: 1034, column: 3, scope: !872)
!872 = !DILexicalBlockFile(scope: !870, file: !1, discriminator: 2)
!873 = !DILocation(line: 1034, column: 3, scope: !874)
!874 = !DILexicalBlockFile(scope: !870, file: !1, discriminator: 3)
!875 = !DILocation(line: 1034, column: 3, scope: !876)
!876 = !DILexicalBlockFile(scope: !870, file: !1, discriminator: 4)
!877 = !DILocation(line: 1034, column: 3, scope: !878)
!878 = !DILexicalBlockFile(scope: !879, file: !1, discriminator: 5)
!879 = distinct !DILexicalBlock(scope: !870, file: !1, line: 1034, column: 3)
!880 = !DILocation(line: 1034, column: 3, scope: !881)
!881 = !DILexicalBlockFile(scope: !882, file: !1, discriminator: 6)
!882 = distinct !DILexicalBlock(scope: !879, file: !1, line: 1034, column: 3)
!883 = !DILocation(line: 1034, column: 3, scope: !884)
!884 = !DILexicalBlockFile(scope: !885, file: !1, discriminator: 7)
!885 = distinct !DILexicalBlock(scope: !879, file: !1, line: 1034, column: 3)
!886 = !DILocation(line: 1034, column: 3, scope: !887)
!887 = !DILexicalBlockFile(scope: !888, file: !1, discriminator: 8)
!888 = distinct !DILexicalBlock(scope: !889, file: !1, line: 1034, column: 3)
!889 = distinct !DILexicalBlock(scope: !885, file: !1, line: 1034, column: 3)
!890 = !DILocation(line: 1034, column: 3, scope: !891)
!891 = !DILexicalBlockFile(scope: !892, file: !1, discriminator: 9)
!892 = distinct !DILexicalBlock(scope: !888, file: !1, line: 1034, column: 3)
!893 = !DILocation(line: 1034, column: 3, scope: !894)
!894 = !DILexicalBlockFile(scope: !892, file: !1, discriminator: 10)
!895 = !DILocation(line: 1034, column: 3, scope: !896)
!896 = !DILexicalBlockFile(scope: !892, file: !1, discriminator: 11)
!897 = !DILocation(line: 1034, column: 3, scope: !898)
!898 = !DILexicalBlockFile(scope: !892, file: !1, discriminator: 12)
!899 = !DILocation(line: 1034, column: 3, scope: !900)
!900 = !DILexicalBlockFile(scope: !892, file: !1, discriminator: 13)
!901 = !DILocation(line: 1034, column: 3, scope: !902)
!902 = !DILexicalBlockFile(scope: !903, file: !1, discriminator: 14)
!903 = distinct !DILexicalBlock(scope: !892, file: !1, line: 1034, column: 3)
!904 = !DILocation(line: 1034, column: 3, scope: !905)
!905 = !DILexicalBlockFile(scope: !892, file: !1, discriminator: 15)
!906 = !DILocation(line: 1034, column: 3, scope: !907)
!907 = !DILexicalBlockFile(scope: !888, file: !1, discriminator: 16)
!908 = !DILocation(line: 1034, column: 3, scope: !909)
!909 = !DILexicalBlockFile(scope: !870, file: !1, discriminator: 17)
!910 = !DILocation(line: 1035, column: 15, scope: !419)
!911 = !DILocation(line: 1035, column: 3, scope: !419)
!912 = !DILocation(line: 1035, column: 8, scope: !419)
!913 = !DILocation(line: 1035, column: 13, scope: !419)
!914 = !DILocation(line: 1036, column: 3, scope: !419)
!915 = !DILocation(line: 1036, column: 3, scope: !916)
!916 = !DILexicalBlockFile(scope: !917, file: !1, discriminator: 1)
!917 = distinct !DILexicalBlock(scope: !918, file: !1, line: 1036, column: 3)
!918 = distinct !DILexicalBlock(scope: !419, file: !1, line: 1036, column: 3)
!919 = !DILocation(line: 1036, column: 3, scope: !920)
!920 = !DILexicalBlockFile(scope: !921, file: !1, discriminator: 2)
!921 = distinct !DILexicalBlock(scope: !917, file: !1, line: 1036, column: 3)
!922 = !DILocation(line: 1036, column: 3, scope: !923)
!923 = !DILexicalBlockFile(scope: !924, file: !1, discriminator: 3)
!924 = distinct !DILexicalBlock(scope: !917, file: !1, line: 1036, column: 3)
!925 = !DILocation(line: 1037, column: 1, scope: !419)
!926 = !DILocalVariable(name: "loop", arg: 1, scope: !420, file: !1, line: 1040, type: !120)
!927 = !DILocation(line: 1040, column: 28, scope: !420)
!928 = !DILocalVariable(name: "req", arg: 2, scope: !420, file: !1, line: 1041, type: !105)
!929 = !DILocation(line: 1041, column: 26, scope: !420)
!930 = !DILocalVariable(name: "path", arg: 3, scope: !420, file: !1, line: 1042, type: !331)
!931 = !DILocation(line: 1042, column: 29, scope: !420)
!932 = !DILocalVariable(name: "uid", arg: 4, scope: !420, file: !1, line: 1043, type: !381)
!933 = !DILocation(line: 1043, column: 26, scope: !420)
!934 = !DILocalVariable(name: "gid", arg: 5, scope: !420, file: !1, line: 1044, type: !385)
!935 = !DILocation(line: 1044, column: 26, scope: !420)
!936 = !DILocalVariable(name: "cb", arg: 6, scope: !420, file: !1, line: 1045, type: !320)
!937 = !DILocation(line: 1045, column: 26, scope: !420)
!938 = !DILocation(line: 1046, column: 3, scope: !420)
!939 = !DILocation(line: 1046, column: 3, scope: !940)
!940 = !DILexicalBlockFile(scope: !941, file: !1, discriminator: 1)
!941 = distinct !DILexicalBlock(scope: !420, file: !1, line: 1046, column: 3)
!942 = !DILocation(line: 1046, column: 3, scope: !943)
!943 = !DILexicalBlockFile(scope: !944, file: !1, discriminator: 2)
!944 = distinct !DILexicalBlock(scope: !941, file: !1, line: 1046, column: 3)
!945 = !DILocation(line: 1046, column: 3, scope: !946)
!946 = !DILexicalBlockFile(scope: !947, file: !1, discriminator: 3)
!947 = distinct !DILexicalBlock(scope: !944, file: !1, line: 1046, column: 3)
!948 = !DILocation(line: 1046, column: 3, scope: !949)
!949 = !DILexicalBlockFile(scope: !950, file: !1, discriminator: 4)
!950 = distinct !DILexicalBlock(scope: !947, file: !1, line: 1046, column: 3)
!951 = !DILocation(line: 1046, column: 3, scope: !952)
!952 = !DILexicalBlockFile(scope: !947, file: !1, discriminator: 5)
!953 = !DILocation(line: 1046, column: 3, scope: !954)
!954 = !DILexicalBlockFile(scope: !955, file: !1, discriminator: 6)
!955 = distinct !DILexicalBlock(scope: !947, file: !1, line: 1046, column: 3)
!956 = !DILocation(line: 1046, column: 3, scope: !957)
!957 = !DILexicalBlockFile(scope: !958, file: !1, discriminator: 7)
!958 = distinct !DILexicalBlock(scope: !955, file: !1, line: 1046, column: 3)
!959 = !DILocation(line: 1046, column: 3, scope: !960)
!960 = !DILexicalBlockFile(scope: !955, file: !1, discriminator: 8)
!961 = !DILocation(line: 1046, column: 3, scope: !962)
!962 = !DILexicalBlockFile(scope: !947, file: !1, discriminator: 9)
!963 = !DILocation(line: 1046, column: 3, scope: !964)
!964 = !DILexicalBlockFile(scope: !947, file: !1, discriminator: 10)
!965 = !DILocation(line: 1046, column: 3, scope: !966)
!966 = !DILexicalBlockFile(scope: !941, file: !1, discriminator: 11)
!967 = !DILocation(line: 1047, column: 3, scope: !420)
!968 = !DILocation(line: 1047, column: 3, scope: !969)
!969 = !DILexicalBlockFile(scope: !970, file: !1, discriminator: 1)
!970 = distinct !DILexicalBlock(scope: !420, file: !1, line: 1047, column: 3)
!971 = !DILocation(line: 1047, column: 3, scope: !972)
!972 = !DILexicalBlockFile(scope: !970, file: !1, discriminator: 2)
!973 = !DILocation(line: 1047, column: 3, scope: !974)
!974 = !DILexicalBlockFile(scope: !970, file: !1, discriminator: 3)
!975 = !DILocation(line: 1047, column: 3, scope: !976)
!976 = !DILexicalBlockFile(scope: !970, file: !1, discriminator: 4)
!977 = !DILocation(line: 1047, column: 3, scope: !978)
!978 = !DILexicalBlockFile(scope: !979, file: !1, discriminator: 5)
!979 = distinct !DILexicalBlock(scope: !970, file: !1, line: 1047, column: 3)
!980 = !DILocation(line: 1047, column: 3, scope: !981)
!981 = !DILexicalBlockFile(scope: !982, file: !1, discriminator: 6)
!982 = distinct !DILexicalBlock(scope: !979, file: !1, line: 1047, column: 3)
!983 = !DILocation(line: 1047, column: 3, scope: !984)
!984 = !DILexicalBlockFile(scope: !985, file: !1, discriminator: 7)
!985 = distinct !DILexicalBlock(scope: !979, file: !1, line: 1047, column: 3)
!986 = !DILocation(line: 1047, column: 3, scope: !987)
!987 = !DILexicalBlockFile(scope: !988, file: !1, discriminator: 8)
!988 = distinct !DILexicalBlock(scope: !989, file: !1, line: 1047, column: 3)
!989 = distinct !DILexicalBlock(scope: !985, file: !1, line: 1047, column: 3)
!990 = !DILocation(line: 1047, column: 3, scope: !991)
!991 = !DILexicalBlockFile(scope: !992, file: !1, discriminator: 9)
!992 = distinct !DILexicalBlock(scope: !988, file: !1, line: 1047, column: 3)
!993 = !DILocation(line: 1047, column: 3, scope: !994)
!994 = !DILexicalBlockFile(scope: !992, file: !1, discriminator: 10)
!995 = !DILocation(line: 1047, column: 3, scope: !996)
!996 = !DILexicalBlockFile(scope: !992, file: !1, discriminator: 11)
!997 = !DILocation(line: 1047, column: 3, scope: !998)
!998 = !DILexicalBlockFile(scope: !992, file: !1, discriminator: 12)
!999 = !DILocation(line: 1047, column: 3, scope: !1000)
!1000 = !DILexicalBlockFile(scope: !992, file: !1, discriminator: 13)
!1001 = !DILocation(line: 1047, column: 3, scope: !1002)
!1002 = !DILexicalBlockFile(scope: !1003, file: !1, discriminator: 14)
!1003 = distinct !DILexicalBlock(scope: !992, file: !1, line: 1047, column: 3)
!1004 = !DILocation(line: 1047, column: 3, scope: !1005)
!1005 = !DILexicalBlockFile(scope: !992, file: !1, discriminator: 15)
!1006 = !DILocation(line: 1047, column: 3, scope: !1007)
!1007 = !DILexicalBlockFile(scope: !988, file: !1, discriminator: 16)
!1008 = !DILocation(line: 1047, column: 3, scope: !1009)
!1009 = !DILexicalBlockFile(scope: !970, file: !1, discriminator: 17)
!1010 = !DILocation(line: 1048, column: 14, scope: !420)
!1011 = !DILocation(line: 1048, column: 3, scope: !420)
!1012 = !DILocation(line: 1048, column: 8, scope: !420)
!1013 = !DILocation(line: 1048, column: 12, scope: !420)
!1014 = !DILocation(line: 1049, column: 14, scope: !420)
!1015 = !DILocation(line: 1049, column: 3, scope: !420)
!1016 = !DILocation(line: 1049, column: 8, scope: !420)
!1017 = !DILocation(line: 1049, column: 12, scope: !420)
!1018 = !DILocation(line: 1050, column: 3, scope: !420)
!1019 = !DILocation(line: 1050, column: 3, scope: !1020)
!1020 = !DILexicalBlockFile(scope: !1021, file: !1, discriminator: 1)
!1021 = distinct !DILexicalBlock(scope: !1022, file: !1, line: 1050, column: 3)
!1022 = distinct !DILexicalBlock(scope: !420, file: !1, line: 1050, column: 3)
!1023 = !DILocation(line: 1050, column: 3, scope: !1024)
!1024 = !DILexicalBlockFile(scope: !1025, file: !1, discriminator: 2)
!1025 = distinct !DILexicalBlock(scope: !1021, file: !1, line: 1050, column: 3)
!1026 = !DILocation(line: 1050, column: 3, scope: !1027)
!1027 = !DILexicalBlockFile(scope: !1028, file: !1, discriminator: 3)
!1028 = distinct !DILexicalBlock(scope: !1021, file: !1, line: 1050, column: 3)
!1029 = !DILocation(line: 1051, column: 1, scope: !420)
!1030 = !DILocalVariable(name: "loop", arg: 1, scope: !423, file: !1, line: 1054, type: !120)
!1031 = !DILocation(line: 1054, column: 28, scope: !423)
!1032 = !DILocalVariable(name: "req", arg: 2, scope: !423, file: !1, line: 1054, type: !105)
!1033 = !DILocation(line: 1054, column: 43, scope: !423)
!1034 = !DILocalVariable(name: "file", arg: 3, scope: !423, file: !1, line: 1054, type: !360)
!1035 = !DILocation(line: 1054, column: 56, scope: !423)
!1036 = !DILocalVariable(name: "cb", arg: 4, scope: !423, file: !1, line: 1054, type: !320)
!1037 = !DILocation(line: 1054, column: 71, scope: !423)
!1038 = !DILocation(line: 1055, column: 3, scope: !423)
!1039 = !DILocation(line: 1055, column: 3, scope: !1040)
!1040 = !DILexicalBlockFile(scope: !1041, file: !1, discriminator: 1)
!1041 = distinct !DILexicalBlock(scope: !423, file: !1, line: 1055, column: 3)
!1042 = !DILocation(line: 1055, column: 3, scope: !1043)
!1043 = !DILexicalBlockFile(scope: !1044, file: !1, discriminator: 2)
!1044 = distinct !DILexicalBlock(scope: !1041, file: !1, line: 1055, column: 3)
!1045 = !DILocation(line: 1055, column: 3, scope: !1046)
!1046 = !DILexicalBlockFile(scope: !1047, file: !1, discriminator: 3)
!1047 = distinct !DILexicalBlock(scope: !1044, file: !1, line: 1055, column: 3)
!1048 = !DILocation(line: 1055, column: 3, scope: !1049)
!1049 = !DILexicalBlockFile(scope: !1050, file: !1, discriminator: 4)
!1050 = distinct !DILexicalBlock(scope: !1047, file: !1, line: 1055, column: 3)
!1051 = !DILocation(line: 1055, column: 3, scope: !1052)
!1052 = !DILexicalBlockFile(scope: !1047, file: !1, discriminator: 5)
!1053 = !DILocation(line: 1055, column: 3, scope: !1054)
!1054 = !DILexicalBlockFile(scope: !1055, file: !1, discriminator: 6)
!1055 = distinct !DILexicalBlock(scope: !1047, file: !1, line: 1055, column: 3)
!1056 = !DILocation(line: 1055, column: 3, scope: !1057)
!1057 = !DILexicalBlockFile(scope: !1058, file: !1, discriminator: 7)
!1058 = distinct !DILexicalBlock(scope: !1055, file: !1, line: 1055, column: 3)
!1059 = !DILocation(line: 1055, column: 3, scope: !1060)
!1060 = !DILexicalBlockFile(scope: !1055, file: !1, discriminator: 8)
!1061 = !DILocation(line: 1055, column: 3, scope: !1062)
!1062 = !DILexicalBlockFile(scope: !1047, file: !1, discriminator: 9)
!1063 = !DILocation(line: 1055, column: 3, scope: !1064)
!1064 = !DILexicalBlockFile(scope: !1047, file: !1, discriminator: 10)
!1065 = !DILocation(line: 1055, column: 3, scope: !1066)
!1066 = !DILexicalBlockFile(scope: !1041, file: !1, discriminator: 11)
!1067 = !DILocation(line: 1056, column: 15, scope: !423)
!1068 = !DILocation(line: 1056, column: 3, scope: !423)
!1069 = !DILocation(line: 1056, column: 8, scope: !423)
!1070 = !DILocation(line: 1056, column: 13, scope: !423)
!1071 = !DILocation(line: 1057, column: 3, scope: !423)
!1072 = !DILocation(line: 1057, column: 3, scope: !1073)
!1073 = !DILexicalBlockFile(scope: !1074, file: !1, discriminator: 1)
!1074 = distinct !DILexicalBlock(scope: !1075, file: !1, line: 1057, column: 3)
!1075 = distinct !DILexicalBlock(scope: !423, file: !1, line: 1057, column: 3)
!1076 = !DILocation(line: 1057, column: 3, scope: !1077)
!1077 = !DILexicalBlockFile(scope: !1078, file: !1, discriminator: 2)
!1078 = distinct !DILexicalBlock(scope: !1074, file: !1, line: 1057, column: 3)
!1079 = !DILocation(line: 1057, column: 3, scope: !1080)
!1080 = !DILexicalBlockFile(scope: !1081, file: !1, discriminator: 3)
!1081 = distinct !DILexicalBlock(scope: !1074, file: !1, line: 1057, column: 3)
!1082 = !DILocation(line: 1058, column: 1, scope: !423)
!1083 = !DILocalVariable(name: "loop", arg: 1, scope: !426, file: !1, line: 1061, type: !120)
!1084 = !DILocation(line: 1061, column: 29, scope: !426)
!1085 = !DILocalVariable(name: "req", arg: 2, scope: !426, file: !1, line: 1062, type: !105)
!1086 = !DILocation(line: 1062, column: 27, scope: !426)
!1087 = !DILocalVariable(name: "file", arg: 3, scope: !426, file: !1, line: 1063, type: !360)
!1088 = !DILocation(line: 1063, column: 26, scope: !426)
!1089 = !DILocalVariable(name: "mode", arg: 4, scope: !426, file: !1, line: 1064, type: !133)
!1090 = !DILocation(line: 1064, column: 22, scope: !426)
!1091 = !DILocalVariable(name: "cb", arg: 5, scope: !426, file: !1, line: 1065, type: !320)
!1092 = !DILocation(line: 1065, column: 27, scope: !426)
!1093 = !DILocation(line: 1066, column: 3, scope: !426)
!1094 = !DILocation(line: 1066, column: 3, scope: !1095)
!1095 = !DILexicalBlockFile(scope: !1096, file: !1, discriminator: 1)
!1096 = distinct !DILexicalBlock(scope: !426, file: !1, line: 1066, column: 3)
!1097 = !DILocation(line: 1066, column: 3, scope: !1098)
!1098 = !DILexicalBlockFile(scope: !1099, file: !1, discriminator: 2)
!1099 = distinct !DILexicalBlock(scope: !1096, file: !1, line: 1066, column: 3)
!1100 = !DILocation(line: 1066, column: 3, scope: !1101)
!1101 = !DILexicalBlockFile(scope: !1102, file: !1, discriminator: 3)
!1102 = distinct !DILexicalBlock(scope: !1099, file: !1, line: 1066, column: 3)
!1103 = !DILocation(line: 1066, column: 3, scope: !1104)
!1104 = !DILexicalBlockFile(scope: !1105, file: !1, discriminator: 4)
!1105 = distinct !DILexicalBlock(scope: !1102, file: !1, line: 1066, column: 3)
!1106 = !DILocation(line: 1066, column: 3, scope: !1107)
!1107 = !DILexicalBlockFile(scope: !1102, file: !1, discriminator: 5)
!1108 = !DILocation(line: 1066, column: 3, scope: !1109)
!1109 = !DILexicalBlockFile(scope: !1110, file: !1, discriminator: 6)
!1110 = distinct !DILexicalBlock(scope: !1102, file: !1, line: 1066, column: 3)
!1111 = !DILocation(line: 1066, column: 3, scope: !1112)
!1112 = !DILexicalBlockFile(scope: !1113, file: !1, discriminator: 7)
!1113 = distinct !DILexicalBlock(scope: !1110, file: !1, line: 1066, column: 3)
!1114 = !DILocation(line: 1066, column: 3, scope: !1115)
!1115 = !DILexicalBlockFile(scope: !1110, file: !1, discriminator: 8)
!1116 = !DILocation(line: 1066, column: 3, scope: !1117)
!1117 = !DILexicalBlockFile(scope: !1102, file: !1, discriminator: 9)
!1118 = !DILocation(line: 1066, column: 3, scope: !1119)
!1119 = !DILexicalBlockFile(scope: !1102, file: !1, discriminator: 10)
!1120 = !DILocation(line: 1066, column: 3, scope: !1121)
!1121 = !DILexicalBlockFile(scope: !1096, file: !1, discriminator: 11)
!1122 = !DILocation(line: 1067, column: 15, scope: !426)
!1123 = !DILocation(line: 1067, column: 3, scope: !426)
!1124 = !DILocation(line: 1067, column: 8, scope: !426)
!1125 = !DILocation(line: 1067, column: 13, scope: !426)
!1126 = !DILocation(line: 1068, column: 15, scope: !426)
!1127 = !DILocation(line: 1068, column: 3, scope: !426)
!1128 = !DILocation(line: 1068, column: 8, scope: !426)
!1129 = !DILocation(line: 1068, column: 13, scope: !426)
!1130 = !DILocation(line: 1069, column: 3, scope: !426)
!1131 = !DILocation(line: 1069, column: 3, scope: !1132)
!1132 = !DILexicalBlockFile(scope: !1133, file: !1, discriminator: 1)
!1133 = distinct !DILexicalBlock(scope: !1134, file: !1, line: 1069, column: 3)
!1134 = distinct !DILexicalBlock(scope: !426, file: !1, line: 1069, column: 3)
!1135 = !DILocation(line: 1069, column: 3, scope: !1136)
!1136 = !DILexicalBlockFile(scope: !1137, file: !1, discriminator: 2)
!1137 = distinct !DILexicalBlock(scope: !1133, file: !1, line: 1069, column: 3)
!1138 = !DILocation(line: 1069, column: 3, scope: !1139)
!1139 = !DILexicalBlockFile(scope: !1140, file: !1, discriminator: 3)
!1140 = distinct !DILexicalBlock(scope: !1133, file: !1, line: 1069, column: 3)
!1141 = !DILocation(line: 1070, column: 1, scope: !426)
!1142 = !DILocalVariable(name: "loop", arg: 1, scope: !429, file: !1, line: 1073, type: !120)
!1143 = !DILocation(line: 1073, column: 29, scope: !429)
!1144 = !DILocalVariable(name: "req", arg: 2, scope: !429, file: !1, line: 1074, type: !105)
!1145 = !DILocation(line: 1074, column: 27, scope: !429)
!1146 = !DILocalVariable(name: "file", arg: 3, scope: !429, file: !1, line: 1075, type: !360)
!1147 = !DILocation(line: 1075, column: 26, scope: !429)
!1148 = !DILocalVariable(name: "uid", arg: 4, scope: !429, file: !1, line: 1076, type: !381)
!1149 = !DILocation(line: 1076, column: 27, scope: !429)
!1150 = !DILocalVariable(name: "gid", arg: 5, scope: !429, file: !1, line: 1077, type: !385)
!1151 = !DILocation(line: 1077, column: 27, scope: !429)
!1152 = !DILocalVariable(name: "cb", arg: 6, scope: !429, file: !1, line: 1078, type: !320)
!1153 = !DILocation(line: 1078, column: 27, scope: !429)
!1154 = !DILocation(line: 1079, column: 3, scope: !429)
!1155 = !DILocation(line: 1079, column: 3, scope: !1156)
!1156 = !DILexicalBlockFile(scope: !1157, file: !1, discriminator: 1)
!1157 = distinct !DILexicalBlock(scope: !429, file: !1, line: 1079, column: 3)
!1158 = !DILocation(line: 1079, column: 3, scope: !1159)
!1159 = !DILexicalBlockFile(scope: !1160, file: !1, discriminator: 2)
!1160 = distinct !DILexicalBlock(scope: !1157, file: !1, line: 1079, column: 3)
!1161 = !DILocation(line: 1079, column: 3, scope: !1162)
!1162 = !DILexicalBlockFile(scope: !1163, file: !1, discriminator: 3)
!1163 = distinct !DILexicalBlock(scope: !1160, file: !1, line: 1079, column: 3)
!1164 = !DILocation(line: 1079, column: 3, scope: !1165)
!1165 = !DILexicalBlockFile(scope: !1166, file: !1, discriminator: 4)
!1166 = distinct !DILexicalBlock(scope: !1163, file: !1, line: 1079, column: 3)
!1167 = !DILocation(line: 1079, column: 3, scope: !1168)
!1168 = !DILexicalBlockFile(scope: !1163, file: !1, discriminator: 5)
!1169 = !DILocation(line: 1079, column: 3, scope: !1170)
!1170 = !DILexicalBlockFile(scope: !1171, file: !1, discriminator: 6)
!1171 = distinct !DILexicalBlock(scope: !1163, file: !1, line: 1079, column: 3)
!1172 = !DILocation(line: 1079, column: 3, scope: !1173)
!1173 = !DILexicalBlockFile(scope: !1174, file: !1, discriminator: 7)
!1174 = distinct !DILexicalBlock(scope: !1171, file: !1, line: 1079, column: 3)
!1175 = !DILocation(line: 1079, column: 3, scope: !1176)
!1176 = !DILexicalBlockFile(scope: !1171, file: !1, discriminator: 8)
!1177 = !DILocation(line: 1079, column: 3, scope: !1178)
!1178 = !DILexicalBlockFile(scope: !1163, file: !1, discriminator: 9)
!1179 = !DILocation(line: 1079, column: 3, scope: !1180)
!1180 = !DILexicalBlockFile(scope: !1163, file: !1, discriminator: 10)
!1181 = !DILocation(line: 1079, column: 3, scope: !1182)
!1182 = !DILexicalBlockFile(scope: !1157, file: !1, discriminator: 11)
!1183 = !DILocation(line: 1080, column: 15, scope: !429)
!1184 = !DILocation(line: 1080, column: 3, scope: !429)
!1185 = !DILocation(line: 1080, column: 8, scope: !429)
!1186 = !DILocation(line: 1080, column: 13, scope: !429)
!1187 = !DILocation(line: 1081, column: 14, scope: !429)
!1188 = !DILocation(line: 1081, column: 3, scope: !429)
!1189 = !DILocation(line: 1081, column: 8, scope: !429)
!1190 = !DILocation(line: 1081, column: 12, scope: !429)
!1191 = !DILocation(line: 1082, column: 14, scope: !429)
!1192 = !DILocation(line: 1082, column: 3, scope: !429)
!1193 = !DILocation(line: 1082, column: 8, scope: !429)
!1194 = !DILocation(line: 1082, column: 12, scope: !429)
!1195 = !DILocation(line: 1083, column: 3, scope: !429)
!1196 = !DILocation(line: 1083, column: 3, scope: !1197)
!1197 = !DILexicalBlockFile(scope: !1198, file: !1, discriminator: 1)
!1198 = distinct !DILexicalBlock(scope: !1199, file: !1, line: 1083, column: 3)
!1199 = distinct !DILexicalBlock(scope: !429, file: !1, line: 1083, column: 3)
!1200 = !DILocation(line: 1083, column: 3, scope: !1201)
!1201 = !DILexicalBlockFile(scope: !1202, file: !1, discriminator: 2)
!1202 = distinct !DILexicalBlock(scope: !1198, file: !1, line: 1083, column: 3)
!1203 = !DILocation(line: 1083, column: 3, scope: !1204)
!1204 = !DILexicalBlockFile(scope: !1205, file: !1, discriminator: 3)
!1205 = distinct !DILexicalBlock(scope: !1198, file: !1, line: 1083, column: 3)
!1206 = !DILocation(line: 1084, column: 1, scope: !429)
!1207 = !DILocalVariable(name: "loop", arg: 1, scope: !432, file: !1, line: 1087, type: !120)
!1208 = !DILocation(line: 1087, column: 32, scope: !432)
!1209 = !DILocalVariable(name: "req", arg: 2, scope: !432, file: !1, line: 1087, type: !105)
!1210 = !DILocation(line: 1087, column: 47, scope: !432)
!1211 = !DILocalVariable(name: "file", arg: 3, scope: !432, file: !1, line: 1087, type: !360)
!1212 = !DILocation(line: 1087, column: 60, scope: !432)
!1213 = !DILocalVariable(name: "cb", arg: 4, scope: !432, file: !1, line: 1087, type: !320)
!1214 = !DILocation(line: 1087, column: 75, scope: !432)
!1215 = !DILocation(line: 1088, column: 3, scope: !432)
!1216 = !DILocation(line: 1088, column: 3, scope: !1217)
!1217 = !DILexicalBlockFile(scope: !1218, file: !1, discriminator: 1)
!1218 = distinct !DILexicalBlock(scope: !432, file: !1, line: 1088, column: 3)
!1219 = !DILocation(line: 1088, column: 3, scope: !1220)
!1220 = !DILexicalBlockFile(scope: !1221, file: !1, discriminator: 2)
!1221 = distinct !DILexicalBlock(scope: !1218, file: !1, line: 1088, column: 3)
!1222 = !DILocation(line: 1088, column: 3, scope: !1223)
!1223 = !DILexicalBlockFile(scope: !1224, file: !1, discriminator: 3)
!1224 = distinct !DILexicalBlock(scope: !1221, file: !1, line: 1088, column: 3)
!1225 = !DILocation(line: 1088, column: 3, scope: !1226)
!1226 = !DILexicalBlockFile(scope: !1227, file: !1, discriminator: 4)
!1227 = distinct !DILexicalBlock(scope: !1224, file: !1, line: 1088, column: 3)
!1228 = !DILocation(line: 1088, column: 3, scope: !1229)
!1229 = !DILexicalBlockFile(scope: !1224, file: !1, discriminator: 5)
!1230 = !DILocation(line: 1088, column: 3, scope: !1231)
!1231 = !DILexicalBlockFile(scope: !1232, file: !1, discriminator: 6)
!1232 = distinct !DILexicalBlock(scope: !1224, file: !1, line: 1088, column: 3)
!1233 = !DILocation(line: 1088, column: 3, scope: !1234)
!1234 = !DILexicalBlockFile(scope: !1235, file: !1, discriminator: 7)
!1235 = distinct !DILexicalBlock(scope: !1232, file: !1, line: 1088, column: 3)
!1236 = !DILocation(line: 1088, column: 3, scope: !1237)
!1237 = !DILexicalBlockFile(scope: !1232, file: !1, discriminator: 8)
!1238 = !DILocation(line: 1088, column: 3, scope: !1239)
!1239 = !DILexicalBlockFile(scope: !1224, file: !1, discriminator: 9)
!1240 = !DILocation(line: 1088, column: 3, scope: !1241)
!1241 = !DILexicalBlockFile(scope: !1224, file: !1, discriminator: 10)
!1242 = !DILocation(line: 1088, column: 3, scope: !1243)
!1243 = !DILexicalBlockFile(scope: !1218, file: !1, discriminator: 11)
!1244 = !DILocation(line: 1089, column: 15, scope: !432)
!1245 = !DILocation(line: 1089, column: 3, scope: !432)
!1246 = !DILocation(line: 1089, column: 8, scope: !432)
!1247 = !DILocation(line: 1089, column: 13, scope: !432)
!1248 = !DILocation(line: 1090, column: 3, scope: !432)
!1249 = !DILocation(line: 1090, column: 3, scope: !1250)
!1250 = !DILexicalBlockFile(scope: !1251, file: !1, discriminator: 1)
!1251 = distinct !DILexicalBlock(scope: !1252, file: !1, line: 1090, column: 3)
!1252 = distinct !DILexicalBlock(scope: !432, file: !1, line: 1090, column: 3)
!1253 = !DILocation(line: 1090, column: 3, scope: !1254)
!1254 = !DILexicalBlockFile(scope: !1255, file: !1, discriminator: 2)
!1255 = distinct !DILexicalBlock(scope: !1251, file: !1, line: 1090, column: 3)
!1256 = !DILocation(line: 1090, column: 3, scope: !1257)
!1257 = !DILexicalBlockFile(scope: !1258, file: !1, discriminator: 3)
!1258 = distinct !DILexicalBlock(scope: !1251, file: !1, line: 1090, column: 3)
!1259 = !DILocation(line: 1091, column: 1, scope: !432)
!1260 = !DILocalVariable(name: "loop", arg: 1, scope: !433, file: !1, line: 1094, type: !120)
!1261 = !DILocation(line: 1094, column: 28, scope: !433)
!1262 = !DILocalVariable(name: "req", arg: 2, scope: !433, file: !1, line: 1094, type: !105)
!1263 = !DILocation(line: 1094, column: 43, scope: !433)
!1264 = !DILocalVariable(name: "file", arg: 3, scope: !433, file: !1, line: 1094, type: !360)
!1265 = !DILocation(line: 1094, column: 56, scope: !433)
!1266 = !DILocalVariable(name: "cb", arg: 4, scope: !433, file: !1, line: 1094, type: !320)
!1267 = !DILocation(line: 1094, column: 71, scope: !433)
!1268 = !DILocation(line: 1095, column: 3, scope: !433)
!1269 = !DILocation(line: 1095, column: 3, scope: !1270)
!1270 = !DILexicalBlockFile(scope: !1271, file: !1, discriminator: 1)
!1271 = distinct !DILexicalBlock(scope: !433, file: !1, line: 1095, column: 3)
!1272 = !DILocation(line: 1095, column: 3, scope: !1273)
!1273 = !DILexicalBlockFile(scope: !1274, file: !1, discriminator: 2)
!1274 = distinct !DILexicalBlock(scope: !1271, file: !1, line: 1095, column: 3)
!1275 = !DILocation(line: 1095, column: 3, scope: !1276)
!1276 = !DILexicalBlockFile(scope: !1277, file: !1, discriminator: 3)
!1277 = distinct !DILexicalBlock(scope: !1274, file: !1, line: 1095, column: 3)
!1278 = !DILocation(line: 1095, column: 3, scope: !1279)
!1279 = !DILexicalBlockFile(scope: !1280, file: !1, discriminator: 4)
!1280 = distinct !DILexicalBlock(scope: !1277, file: !1, line: 1095, column: 3)
!1281 = !DILocation(line: 1095, column: 3, scope: !1282)
!1282 = !DILexicalBlockFile(scope: !1277, file: !1, discriminator: 5)
!1283 = !DILocation(line: 1095, column: 3, scope: !1284)
!1284 = !DILexicalBlockFile(scope: !1285, file: !1, discriminator: 6)
!1285 = distinct !DILexicalBlock(scope: !1277, file: !1, line: 1095, column: 3)
!1286 = !DILocation(line: 1095, column: 3, scope: !1287)
!1287 = !DILexicalBlockFile(scope: !1288, file: !1, discriminator: 7)
!1288 = distinct !DILexicalBlock(scope: !1285, file: !1, line: 1095, column: 3)
!1289 = !DILocation(line: 1095, column: 3, scope: !1290)
!1290 = !DILexicalBlockFile(scope: !1285, file: !1, discriminator: 8)
!1291 = !DILocation(line: 1095, column: 3, scope: !1292)
!1292 = !DILexicalBlockFile(scope: !1277, file: !1, discriminator: 9)
!1293 = !DILocation(line: 1095, column: 3, scope: !1294)
!1294 = !DILexicalBlockFile(scope: !1277, file: !1, discriminator: 10)
!1295 = !DILocation(line: 1095, column: 3, scope: !1296)
!1296 = !DILexicalBlockFile(scope: !1271, file: !1, discriminator: 11)
!1297 = !DILocation(line: 1096, column: 15, scope: !433)
!1298 = !DILocation(line: 1096, column: 3, scope: !433)
!1299 = !DILocation(line: 1096, column: 8, scope: !433)
!1300 = !DILocation(line: 1096, column: 13, scope: !433)
!1301 = !DILocation(line: 1097, column: 3, scope: !433)
!1302 = !DILocation(line: 1097, column: 3, scope: !1303)
!1303 = !DILexicalBlockFile(scope: !1304, file: !1, discriminator: 1)
!1304 = distinct !DILexicalBlock(scope: !1305, file: !1, line: 1097, column: 3)
!1305 = distinct !DILexicalBlock(scope: !433, file: !1, line: 1097, column: 3)
!1306 = !DILocation(line: 1097, column: 3, scope: !1307)
!1307 = !DILexicalBlockFile(scope: !1308, file: !1, discriminator: 2)
!1308 = distinct !DILexicalBlock(scope: !1304, file: !1, line: 1097, column: 3)
!1309 = !DILocation(line: 1097, column: 3, scope: !1310)
!1310 = !DILexicalBlockFile(scope: !1311, file: !1, discriminator: 3)
!1311 = distinct !DILexicalBlock(scope: !1304, file: !1, line: 1097, column: 3)
!1312 = !DILocation(line: 1098, column: 1, scope: !433)
!1313 = !DILocalVariable(name: "loop", arg: 1, scope: !434, file: !1, line: 1101, type: !120)
!1314 = !DILocation(line: 1101, column: 28, scope: !434)
!1315 = !DILocalVariable(name: "req", arg: 2, scope: !434, file: !1, line: 1101, type: !105)
!1316 = !DILocation(line: 1101, column: 43, scope: !434)
!1317 = !DILocalVariable(name: "file", arg: 3, scope: !434, file: !1, line: 1101, type: !360)
!1318 = !DILocation(line: 1101, column: 56, scope: !434)
!1319 = !DILocalVariable(name: "cb", arg: 4, scope: !434, file: !1, line: 1101, type: !320)
!1320 = !DILocation(line: 1101, column: 71, scope: !434)
!1321 = !DILocation(line: 1102, column: 3, scope: !434)
!1322 = !DILocation(line: 1102, column: 3, scope: !1323)
!1323 = !DILexicalBlockFile(scope: !1324, file: !1, discriminator: 1)
!1324 = distinct !DILexicalBlock(scope: !434, file: !1, line: 1102, column: 3)
!1325 = !DILocation(line: 1102, column: 3, scope: !1326)
!1326 = !DILexicalBlockFile(scope: !1327, file: !1, discriminator: 2)
!1327 = distinct !DILexicalBlock(scope: !1324, file: !1, line: 1102, column: 3)
!1328 = !DILocation(line: 1102, column: 3, scope: !1329)
!1329 = !DILexicalBlockFile(scope: !1330, file: !1, discriminator: 3)
!1330 = distinct !DILexicalBlock(scope: !1327, file: !1, line: 1102, column: 3)
!1331 = !DILocation(line: 1102, column: 3, scope: !1332)
!1332 = !DILexicalBlockFile(scope: !1333, file: !1, discriminator: 4)
!1333 = distinct !DILexicalBlock(scope: !1330, file: !1, line: 1102, column: 3)
!1334 = !DILocation(line: 1102, column: 3, scope: !1335)
!1335 = !DILexicalBlockFile(scope: !1330, file: !1, discriminator: 5)
!1336 = !DILocation(line: 1102, column: 3, scope: !1337)
!1337 = !DILexicalBlockFile(scope: !1338, file: !1, discriminator: 6)
!1338 = distinct !DILexicalBlock(scope: !1330, file: !1, line: 1102, column: 3)
!1339 = !DILocation(line: 1102, column: 3, scope: !1340)
!1340 = !DILexicalBlockFile(scope: !1341, file: !1, discriminator: 7)
!1341 = distinct !DILexicalBlock(scope: !1338, file: !1, line: 1102, column: 3)
!1342 = !DILocation(line: 1102, column: 3, scope: !1343)
!1343 = !DILexicalBlockFile(scope: !1338, file: !1, discriminator: 8)
!1344 = !DILocation(line: 1102, column: 3, scope: !1345)
!1345 = !DILexicalBlockFile(scope: !1330, file: !1, discriminator: 9)
!1346 = !DILocation(line: 1102, column: 3, scope: !1347)
!1347 = !DILexicalBlockFile(scope: !1330, file: !1, discriminator: 10)
!1348 = !DILocation(line: 1102, column: 3, scope: !1349)
!1349 = !DILexicalBlockFile(scope: !1324, file: !1, discriminator: 11)
!1350 = !DILocation(line: 1103, column: 15, scope: !434)
!1351 = !DILocation(line: 1103, column: 3, scope: !434)
!1352 = !DILocation(line: 1103, column: 8, scope: !434)
!1353 = !DILocation(line: 1103, column: 13, scope: !434)
!1354 = !DILocation(line: 1104, column: 3, scope: !434)
!1355 = !DILocation(line: 1104, column: 3, scope: !1356)
!1356 = !DILexicalBlockFile(scope: !1357, file: !1, discriminator: 1)
!1357 = distinct !DILexicalBlock(scope: !1358, file: !1, line: 1104, column: 3)
!1358 = distinct !DILexicalBlock(scope: !434, file: !1, line: 1104, column: 3)
!1359 = !DILocation(line: 1104, column: 3, scope: !1360)
!1360 = !DILexicalBlockFile(scope: !1361, file: !1, discriminator: 2)
!1361 = distinct !DILexicalBlock(scope: !1357, file: !1, line: 1104, column: 3)
!1362 = !DILocation(line: 1104, column: 3, scope: !1363)
!1363 = !DILexicalBlockFile(scope: !1364, file: !1, discriminator: 3)
!1364 = distinct !DILexicalBlock(scope: !1357, file: !1, line: 1104, column: 3)
!1365 = !DILocation(line: 1105, column: 1, scope: !434)
!1366 = !DILocalVariable(name: "loop", arg: 1, scope: !435, file: !1, line: 1108, type: !120)
!1367 = !DILocation(line: 1108, column: 32, scope: !435)
!1368 = !DILocalVariable(name: "req", arg: 2, scope: !435, file: !1, line: 1109, type: !105)
!1369 = !DILocation(line: 1109, column: 30, scope: !435)
!1370 = !DILocalVariable(name: "file", arg: 3, scope: !435, file: !1, line: 1110, type: !360)
!1371 = !DILocation(line: 1110, column: 29, scope: !435)
!1372 = !DILocalVariable(name: "off", arg: 4, scope: !435, file: !1, line: 1111, type: !438)
!1373 = !DILocation(line: 1111, column: 29, scope: !435)
!1374 = !DILocalVariable(name: "cb", arg: 5, scope: !435, file: !1, line: 1112, type: !320)
!1375 = !DILocation(line: 1112, column: 30, scope: !435)
!1376 = !DILocation(line: 1113, column: 3, scope: !435)
!1377 = !DILocation(line: 1113, column: 3, scope: !1378)
!1378 = !DILexicalBlockFile(scope: !1379, file: !1, discriminator: 1)
!1379 = distinct !DILexicalBlock(scope: !435, file: !1, line: 1113, column: 3)
!1380 = !DILocation(line: 1113, column: 3, scope: !1381)
!1381 = !DILexicalBlockFile(scope: !1382, file: !1, discriminator: 2)
!1382 = distinct !DILexicalBlock(scope: !1379, file: !1, line: 1113, column: 3)
!1383 = !DILocation(line: 1113, column: 3, scope: !1384)
!1384 = !DILexicalBlockFile(scope: !1385, file: !1, discriminator: 3)
!1385 = distinct !DILexicalBlock(scope: !1382, file: !1, line: 1113, column: 3)
!1386 = !DILocation(line: 1113, column: 3, scope: !1387)
!1387 = !DILexicalBlockFile(scope: !1388, file: !1, discriminator: 4)
!1388 = distinct !DILexicalBlock(scope: !1385, file: !1, line: 1113, column: 3)
!1389 = !DILocation(line: 1113, column: 3, scope: !1390)
!1390 = !DILexicalBlockFile(scope: !1385, file: !1, discriminator: 5)
!1391 = !DILocation(line: 1113, column: 3, scope: !1392)
!1392 = !DILexicalBlockFile(scope: !1393, file: !1, discriminator: 6)
!1393 = distinct !DILexicalBlock(scope: !1385, file: !1, line: 1113, column: 3)
!1394 = !DILocation(line: 1113, column: 3, scope: !1395)
!1395 = !DILexicalBlockFile(scope: !1396, file: !1, discriminator: 7)
!1396 = distinct !DILexicalBlock(scope: !1393, file: !1, line: 1113, column: 3)
!1397 = !DILocation(line: 1113, column: 3, scope: !1398)
!1398 = !DILexicalBlockFile(scope: !1393, file: !1, discriminator: 8)
!1399 = !DILocation(line: 1113, column: 3, scope: !1400)
!1400 = !DILexicalBlockFile(scope: !1385, file: !1, discriminator: 9)
!1401 = !DILocation(line: 1113, column: 3, scope: !1402)
!1402 = !DILexicalBlockFile(scope: !1385, file: !1, discriminator: 10)
!1403 = !DILocation(line: 1113, column: 3, scope: !1404)
!1404 = !DILexicalBlockFile(scope: !1379, file: !1, discriminator: 11)
!1405 = !DILocation(line: 1114, column: 15, scope: !435)
!1406 = !DILocation(line: 1114, column: 3, scope: !435)
!1407 = !DILocation(line: 1114, column: 8, scope: !435)
!1408 = !DILocation(line: 1114, column: 13, scope: !435)
!1409 = !DILocation(line: 1115, column: 14, scope: !435)
!1410 = !DILocation(line: 1115, column: 3, scope: !435)
!1411 = !DILocation(line: 1115, column: 8, scope: !435)
!1412 = !DILocation(line: 1115, column: 12, scope: !435)
!1413 = !DILocation(line: 1116, column: 3, scope: !435)
!1414 = !DILocation(line: 1116, column: 3, scope: !1415)
!1415 = !DILexicalBlockFile(scope: !1416, file: !1, discriminator: 1)
!1416 = distinct !DILexicalBlock(scope: !1417, file: !1, line: 1116, column: 3)
!1417 = distinct !DILexicalBlock(scope: !435, file: !1, line: 1116, column: 3)
!1418 = !DILocation(line: 1116, column: 3, scope: !1419)
!1419 = !DILexicalBlockFile(scope: !1420, file: !1, discriminator: 2)
!1420 = distinct !DILexicalBlock(scope: !1416, file: !1, line: 1116, column: 3)
!1421 = !DILocation(line: 1116, column: 3, scope: !1422)
!1422 = !DILexicalBlockFile(scope: !1423, file: !1, discriminator: 3)
!1423 = distinct !DILexicalBlock(scope: !1416, file: !1, line: 1116, column: 3)
!1424 = !DILocation(line: 1117, column: 1, scope: !435)
!1425 = !DILocalVariable(name: "loop", arg: 1, scope: !439, file: !1, line: 1120, type: !120)
!1426 = !DILocation(line: 1120, column: 29, scope: !439)
!1427 = !DILocalVariable(name: "req", arg: 2, scope: !439, file: !1, line: 1121, type: !105)
!1428 = !DILocation(line: 1121, column: 27, scope: !439)
!1429 = !DILocalVariable(name: "file", arg: 3, scope: !439, file: !1, line: 1122, type: !360)
!1430 = !DILocation(line: 1122, column: 26, scope: !439)
!1431 = !DILocalVariable(name: "atime", arg: 4, scope: !439, file: !1, line: 1123, type: !389)
!1432 = !DILocation(line: 1123, column: 25, scope: !439)
!1433 = !DILocalVariable(name: "mtime", arg: 5, scope: !439, file: !1, line: 1124, type: !389)
!1434 = !DILocation(line: 1124, column: 25, scope: !439)
!1435 = !DILocalVariable(name: "cb", arg: 6, scope: !439, file: !1, line: 1125, type: !320)
!1436 = !DILocation(line: 1125, column: 27, scope: !439)
!1437 = !DILocation(line: 1126, column: 3, scope: !439)
!1438 = !DILocation(line: 1126, column: 3, scope: !1439)
!1439 = !DILexicalBlockFile(scope: !1440, file: !1, discriminator: 1)
!1440 = distinct !DILexicalBlock(scope: !439, file: !1, line: 1126, column: 3)
!1441 = !DILocation(line: 1126, column: 3, scope: !1442)
!1442 = !DILexicalBlockFile(scope: !1443, file: !1, discriminator: 2)
!1443 = distinct !DILexicalBlock(scope: !1440, file: !1, line: 1126, column: 3)
!1444 = !DILocation(line: 1126, column: 3, scope: !1445)
!1445 = !DILexicalBlockFile(scope: !1446, file: !1, discriminator: 3)
!1446 = distinct !DILexicalBlock(scope: !1443, file: !1, line: 1126, column: 3)
!1447 = !DILocation(line: 1126, column: 3, scope: !1448)
!1448 = !DILexicalBlockFile(scope: !1449, file: !1, discriminator: 4)
!1449 = distinct !DILexicalBlock(scope: !1446, file: !1, line: 1126, column: 3)
!1450 = !DILocation(line: 1126, column: 3, scope: !1451)
!1451 = !DILexicalBlockFile(scope: !1446, file: !1, discriminator: 5)
!1452 = !DILocation(line: 1126, column: 3, scope: !1453)
!1453 = !DILexicalBlockFile(scope: !1454, file: !1, discriminator: 6)
!1454 = distinct !DILexicalBlock(scope: !1446, file: !1, line: 1126, column: 3)
!1455 = !DILocation(line: 1126, column: 3, scope: !1456)
!1456 = !DILexicalBlockFile(scope: !1457, file: !1, discriminator: 7)
!1457 = distinct !DILexicalBlock(scope: !1454, file: !1, line: 1126, column: 3)
!1458 = !DILocation(line: 1126, column: 3, scope: !1459)
!1459 = !DILexicalBlockFile(scope: !1454, file: !1, discriminator: 8)
!1460 = !DILocation(line: 1126, column: 3, scope: !1461)
!1461 = !DILexicalBlockFile(scope: !1446, file: !1, discriminator: 9)
!1462 = !DILocation(line: 1126, column: 3, scope: !1463)
!1463 = !DILexicalBlockFile(scope: !1446, file: !1, discriminator: 10)
!1464 = !DILocation(line: 1126, column: 3, scope: !1465)
!1465 = !DILexicalBlockFile(scope: !1440, file: !1, discriminator: 11)
!1466 = !DILocation(line: 1127, column: 15, scope: !439)
!1467 = !DILocation(line: 1127, column: 3, scope: !439)
!1468 = !DILocation(line: 1127, column: 8, scope: !439)
!1469 = !DILocation(line: 1127, column: 13, scope: !439)
!1470 = !DILocation(line: 1128, column: 16, scope: !439)
!1471 = !DILocation(line: 1128, column: 3, scope: !439)
!1472 = !DILocation(line: 1128, column: 8, scope: !439)
!1473 = !DILocation(line: 1128, column: 14, scope: !439)
!1474 = !DILocation(line: 1129, column: 16, scope: !439)
!1475 = !DILocation(line: 1129, column: 3, scope: !439)
!1476 = !DILocation(line: 1129, column: 8, scope: !439)
!1477 = !DILocation(line: 1129, column: 14, scope: !439)
!1478 = !DILocation(line: 1130, column: 3, scope: !439)
!1479 = !DILocation(line: 1130, column: 3, scope: !1480)
!1480 = !DILexicalBlockFile(scope: !1481, file: !1, discriminator: 1)
!1481 = distinct !DILexicalBlock(scope: !1482, file: !1, line: 1130, column: 3)
!1482 = distinct !DILexicalBlock(scope: !439, file: !1, line: 1130, column: 3)
!1483 = !DILocation(line: 1130, column: 3, scope: !1484)
!1484 = !DILexicalBlockFile(scope: !1485, file: !1, discriminator: 2)
!1485 = distinct !DILexicalBlock(scope: !1481, file: !1, line: 1130, column: 3)
!1486 = !DILocation(line: 1130, column: 3, scope: !1487)
!1487 = !DILexicalBlockFile(scope: !1488, file: !1, discriminator: 3)
!1488 = distinct !DILexicalBlock(scope: !1481, file: !1, line: 1130, column: 3)
!1489 = !DILocation(line: 1131, column: 1, scope: !439)
!1490 = !DILocalVariable(name: "loop", arg: 1, scope: !442, file: !1, line: 1134, type: !120)
!1491 = !DILocation(line: 1134, column: 28, scope: !442)
!1492 = !DILocalVariable(name: "req", arg: 2, scope: !442, file: !1, line: 1134, type: !105)
!1493 = !DILocation(line: 1134, column: 43, scope: !442)
!1494 = !DILocalVariable(name: "path", arg: 3, scope: !442, file: !1, line: 1134, type: !331)
!1495 = !DILocation(line: 1134, column: 60, scope: !442)
!1496 = !DILocalVariable(name: "cb", arg: 4, scope: !442, file: !1, line: 1134, type: !320)
!1497 = !DILocation(line: 1134, column: 75, scope: !442)
!1498 = !DILocation(line: 1135, column: 3, scope: !442)
!1499 = !DILocation(line: 1135, column: 3, scope: !1500)
!1500 = !DILexicalBlockFile(scope: !1501, file: !1, discriminator: 1)
!1501 = distinct !DILexicalBlock(scope: !442, file: !1, line: 1135, column: 3)
!1502 = !DILocation(line: 1135, column: 3, scope: !1503)
!1503 = !DILexicalBlockFile(scope: !1504, file: !1, discriminator: 2)
!1504 = distinct !DILexicalBlock(scope: !1501, file: !1, line: 1135, column: 3)
!1505 = !DILocation(line: 1135, column: 3, scope: !1506)
!1506 = !DILexicalBlockFile(scope: !1507, file: !1, discriminator: 3)
!1507 = distinct !DILexicalBlock(scope: !1504, file: !1, line: 1135, column: 3)
!1508 = !DILocation(line: 1135, column: 3, scope: !1509)
!1509 = !DILexicalBlockFile(scope: !1510, file: !1, discriminator: 4)
!1510 = distinct !DILexicalBlock(scope: !1507, file: !1, line: 1135, column: 3)
!1511 = !DILocation(line: 1135, column: 3, scope: !1512)
!1512 = !DILexicalBlockFile(scope: !1507, file: !1, discriminator: 5)
!1513 = !DILocation(line: 1135, column: 3, scope: !1514)
!1514 = !DILexicalBlockFile(scope: !1515, file: !1, discriminator: 6)
!1515 = distinct !DILexicalBlock(scope: !1507, file: !1, line: 1135, column: 3)
!1516 = !DILocation(line: 1135, column: 3, scope: !1517)
!1517 = !DILexicalBlockFile(scope: !1518, file: !1, discriminator: 7)
!1518 = distinct !DILexicalBlock(scope: !1515, file: !1, line: 1135, column: 3)
!1519 = !DILocation(line: 1135, column: 3, scope: !1520)
!1520 = !DILexicalBlockFile(scope: !1515, file: !1, discriminator: 8)
!1521 = !DILocation(line: 1135, column: 3, scope: !1522)
!1522 = !DILexicalBlockFile(scope: !1507, file: !1, discriminator: 9)
!1523 = !DILocation(line: 1135, column: 3, scope: !1524)
!1524 = !DILexicalBlockFile(scope: !1507, file: !1, discriminator: 10)
!1525 = !DILocation(line: 1135, column: 3, scope: !1526)
!1526 = !DILexicalBlockFile(scope: !1501, file: !1, discriminator: 11)
!1527 = !DILocation(line: 1136, column: 3, scope: !442)
!1528 = !DILocation(line: 1136, column: 3, scope: !1529)
!1529 = !DILexicalBlockFile(scope: !1530, file: !1, discriminator: 1)
!1530 = distinct !DILexicalBlock(scope: !442, file: !1, line: 1136, column: 3)
!1531 = !DILocation(line: 1136, column: 3, scope: !1532)
!1532 = !DILexicalBlockFile(scope: !1530, file: !1, discriminator: 2)
!1533 = !DILocation(line: 1136, column: 3, scope: !1534)
!1534 = !DILexicalBlockFile(scope: !1530, file: !1, discriminator: 3)
!1535 = !DILocation(line: 1136, column: 3, scope: !1536)
!1536 = !DILexicalBlockFile(scope: !1530, file: !1, discriminator: 4)
!1537 = !DILocation(line: 1136, column: 3, scope: !1538)
!1538 = !DILexicalBlockFile(scope: !1539, file: !1, discriminator: 5)
!1539 = distinct !DILexicalBlock(scope: !1530, file: !1, line: 1136, column: 3)
!1540 = !DILocation(line: 1136, column: 3, scope: !1541)
!1541 = !DILexicalBlockFile(scope: !1542, file: !1, discriminator: 6)
!1542 = distinct !DILexicalBlock(scope: !1539, file: !1, line: 1136, column: 3)
!1543 = !DILocation(line: 1136, column: 3, scope: !1544)
!1544 = !DILexicalBlockFile(scope: !1545, file: !1, discriminator: 7)
!1545 = distinct !DILexicalBlock(scope: !1539, file: !1, line: 1136, column: 3)
!1546 = !DILocation(line: 1136, column: 3, scope: !1547)
!1547 = !DILexicalBlockFile(scope: !1548, file: !1, discriminator: 8)
!1548 = distinct !DILexicalBlock(scope: !1549, file: !1, line: 1136, column: 3)
!1549 = distinct !DILexicalBlock(scope: !1545, file: !1, line: 1136, column: 3)
!1550 = !DILocation(line: 1136, column: 3, scope: !1551)
!1551 = !DILexicalBlockFile(scope: !1552, file: !1, discriminator: 9)
!1552 = distinct !DILexicalBlock(scope: !1548, file: !1, line: 1136, column: 3)
!1553 = !DILocation(line: 1136, column: 3, scope: !1554)
!1554 = !DILexicalBlockFile(scope: !1552, file: !1, discriminator: 10)
!1555 = !DILocation(line: 1136, column: 3, scope: !1556)
!1556 = !DILexicalBlockFile(scope: !1552, file: !1, discriminator: 11)
!1557 = !DILocation(line: 1136, column: 3, scope: !1558)
!1558 = !DILexicalBlockFile(scope: !1552, file: !1, discriminator: 12)
!1559 = !DILocation(line: 1136, column: 3, scope: !1560)
!1560 = !DILexicalBlockFile(scope: !1552, file: !1, discriminator: 13)
!1561 = !DILocation(line: 1136, column: 3, scope: !1562)
!1562 = !DILexicalBlockFile(scope: !1563, file: !1, discriminator: 14)
!1563 = distinct !DILexicalBlock(scope: !1552, file: !1, line: 1136, column: 3)
!1564 = !DILocation(line: 1136, column: 3, scope: !1565)
!1565 = !DILexicalBlockFile(scope: !1552, file: !1, discriminator: 15)
!1566 = !DILocation(line: 1136, column: 3, scope: !1567)
!1567 = !DILexicalBlockFile(scope: !1548, file: !1, discriminator: 16)
!1568 = !DILocation(line: 1136, column: 3, scope: !1569)
!1569 = !DILexicalBlockFile(scope: !1530, file: !1, discriminator: 17)
!1570 = !DILocation(line: 1137, column: 3, scope: !442)
!1571 = !DILocation(line: 1137, column: 3, scope: !1572)
!1572 = !DILexicalBlockFile(scope: !1573, file: !1, discriminator: 1)
!1573 = distinct !DILexicalBlock(scope: !1574, file: !1, line: 1137, column: 3)
!1574 = distinct !DILexicalBlock(scope: !442, file: !1, line: 1137, column: 3)
!1575 = !DILocation(line: 1137, column: 3, scope: !1576)
!1576 = !DILexicalBlockFile(scope: !1577, file: !1, discriminator: 2)
!1577 = distinct !DILexicalBlock(scope: !1573, file: !1, line: 1137, column: 3)
!1578 = !DILocation(line: 1137, column: 3, scope: !1579)
!1579 = !DILexicalBlockFile(scope: !1580, file: !1, discriminator: 3)
!1580 = distinct !DILexicalBlock(scope: !1573, file: !1, line: 1137, column: 3)
!1581 = !DILocation(line: 1138, column: 1, scope: !442)
!1582 = !DILocalVariable(name: "loop", arg: 1, scope: !445, file: !1, line: 1141, type: !120)
!1583 = !DILocation(line: 1141, column: 27, scope: !445)
!1584 = !DILocalVariable(name: "req", arg: 2, scope: !445, file: !1, line: 1142, type: !105)
!1585 = !DILocation(line: 1142, column: 25, scope: !445)
!1586 = !DILocalVariable(name: "path", arg: 3, scope: !445, file: !1, line: 1143, type: !331)
!1587 = !DILocation(line: 1143, column: 28, scope: !445)
!1588 = !DILocalVariable(name: "new_path", arg: 4, scope: !445, file: !1, line: 1144, type: !331)
!1589 = !DILocation(line: 1144, column: 28, scope: !445)
!1590 = !DILocalVariable(name: "cb", arg: 5, scope: !445, file: !1, line: 1145, type: !320)
!1591 = !DILocation(line: 1145, column: 25, scope: !445)
!1592 = !DILocation(line: 1146, column: 3, scope: !445)
!1593 = !DILocation(line: 1146, column: 3, scope: !1594)
!1594 = !DILexicalBlockFile(scope: !1595, file: !1, discriminator: 1)
!1595 = distinct !DILexicalBlock(scope: !445, file: !1, line: 1146, column: 3)
!1596 = !DILocation(line: 1146, column: 3, scope: !1597)
!1597 = !DILexicalBlockFile(scope: !1598, file: !1, discriminator: 2)
!1598 = distinct !DILexicalBlock(scope: !1595, file: !1, line: 1146, column: 3)
!1599 = !DILocation(line: 1146, column: 3, scope: !1600)
!1600 = !DILexicalBlockFile(scope: !1601, file: !1, discriminator: 3)
!1601 = distinct !DILexicalBlock(scope: !1598, file: !1, line: 1146, column: 3)
!1602 = !DILocation(line: 1146, column: 3, scope: !1603)
!1603 = !DILexicalBlockFile(scope: !1604, file: !1, discriminator: 4)
!1604 = distinct !DILexicalBlock(scope: !1601, file: !1, line: 1146, column: 3)
!1605 = !DILocation(line: 1146, column: 3, scope: !1606)
!1606 = !DILexicalBlockFile(scope: !1601, file: !1, discriminator: 5)
!1607 = !DILocation(line: 1146, column: 3, scope: !1608)
!1608 = !DILexicalBlockFile(scope: !1609, file: !1, discriminator: 6)
!1609 = distinct !DILexicalBlock(scope: !1601, file: !1, line: 1146, column: 3)
!1610 = !DILocation(line: 1146, column: 3, scope: !1611)
!1611 = !DILexicalBlockFile(scope: !1612, file: !1, discriminator: 7)
!1612 = distinct !DILexicalBlock(scope: !1609, file: !1, line: 1146, column: 3)
!1613 = !DILocation(line: 1146, column: 3, scope: !1614)
!1614 = !DILexicalBlockFile(scope: !1609, file: !1, discriminator: 8)
!1615 = !DILocation(line: 1146, column: 3, scope: !1616)
!1616 = !DILexicalBlockFile(scope: !1601, file: !1, discriminator: 9)
!1617 = !DILocation(line: 1146, column: 3, scope: !1618)
!1618 = !DILexicalBlockFile(scope: !1601, file: !1, discriminator: 10)
!1619 = !DILocation(line: 1146, column: 3, scope: !1620)
!1620 = !DILexicalBlockFile(scope: !1595, file: !1, discriminator: 11)
!1621 = !DILocation(line: 1147, column: 3, scope: !445)
!1622 = !DILocation(line: 1147, column: 3, scope: !1623)
!1623 = !DILexicalBlockFile(scope: !1624, file: !1, discriminator: 1)
!1624 = distinct !DILexicalBlock(scope: !1625, file: !1, line: 1147, column: 3)
!1625 = distinct !DILexicalBlock(scope: !445, file: !1, line: 1147, column: 3)
!1626 = !DILocation(line: 1147, column: 3, scope: !1627)
!1627 = !DILexicalBlockFile(scope: !1628, file: !1, discriminator: 2)
!1628 = distinct !DILexicalBlock(scope: !1624, file: !1, line: 1147, column: 3)
!1629 = !DILocalVariable(name: "path_len", scope: !1630, file: !1, line: 1147, type: !375)
!1630 = distinct !DILexicalBlock(scope: !1624, file: !1, line: 1147, column: 3)
!1631 = !DILocation(line: 1147, column: 3, scope: !1630)
!1632 = !DILocalVariable(name: "new_path_len", scope: !1630, file: !1, line: 1147, type: !375)
!1633 = !DILocation(line: 1147, column: 3, scope: !1634)
!1634 = !DILexicalBlockFile(scope: !1630, file: !1, discriminator: 3)
!1635 = !DILocation(line: 1147, column: 3, scope: !1636)
!1636 = !DILexicalBlockFile(scope: !1634, file: !1, discriminator: 15)
!1637 = !DILocation(line: 1147, column: 3, scope: !1638)
!1638 = !DILexicalBlockFile(scope: !1634, file: !1, discriminator: 16)
!1639 = !DILocation(line: 1147, column: 3, scope: !1640)
!1640 = !DILexicalBlockFile(scope: !1641, file: !1, discriminator: 4)
!1641 = distinct !DILexicalBlock(scope: !1642, file: !1, line: 1147, column: 3)
!1642 = distinct !DILexicalBlock(scope: !1630, file: !1, line: 1147, column: 3)
!1643 = !DILocation(line: 1147, column: 3, scope: !1644)
!1644 = !DILexicalBlockFile(scope: !1645, file: !1, discriminator: 5)
!1645 = distinct !DILexicalBlock(scope: !1641, file: !1, line: 1147, column: 3)
!1646 = !DILocation(line: 1147, column: 3, scope: !1647)
!1647 = !DILexicalBlockFile(scope: !1645, file: !1, discriminator: 6)
!1648 = !DILocation(line: 1147, column: 3, scope: !1649)
!1649 = !DILexicalBlockFile(scope: !1645, file: !1, discriminator: 7)
!1650 = !DILocation(line: 1147, column: 3, scope: !1651)
!1651 = !DILexicalBlockFile(scope: !1645, file: !1, discriminator: 8)
!1652 = !DILocation(line: 1147, column: 3, scope: !1653)
!1653 = !DILexicalBlockFile(scope: !1645, file: !1, discriminator: 9)
!1654 = !DILocation(line: 1147, column: 3, scope: !1655)
!1655 = !DILexicalBlockFile(scope: !1656, file: !1, discriminator: 10)
!1656 = distinct !DILexicalBlock(scope: !1645, file: !1, line: 1147, column: 3)
!1657 = !DILocation(line: 1147, column: 3, scope: !1658)
!1658 = !DILexicalBlockFile(scope: !1645, file: !1, discriminator: 11)
!1659 = !DILocation(line: 1147, column: 3, scope: !1660)
!1660 = !DILexicalBlockFile(scope: !1641, file: !1, discriminator: 12)
!1661 = !DILocation(line: 1147, column: 3, scope: !1662)
!1662 = !DILexicalBlockFile(scope: !1630, file: !1, discriminator: 13)
!1663 = !DILocation(line: 1147, column: 3, scope: !1664)
!1664 = !DILexicalBlockFile(scope: !1662, file: !1, discriminator: 17)
!1665 = !DILocation(line: 1147, column: 3, scope: !1666)
!1666 = !DILexicalBlockFile(scope: !1625, file: !1, discriminator: 14)
!1667 = !DILocation(line: 1148, column: 3, scope: !445)
!1668 = !DILocation(line: 1148, column: 3, scope: !1669)
!1669 = !DILexicalBlockFile(scope: !1670, file: !1, discriminator: 1)
!1670 = distinct !DILexicalBlock(scope: !1671, file: !1, line: 1148, column: 3)
!1671 = distinct !DILexicalBlock(scope: !445, file: !1, line: 1148, column: 3)
!1672 = !DILocation(line: 1148, column: 3, scope: !1673)
!1673 = !DILexicalBlockFile(scope: !1674, file: !1, discriminator: 2)
!1674 = distinct !DILexicalBlock(scope: !1670, file: !1, line: 1148, column: 3)
!1675 = !DILocation(line: 1148, column: 3, scope: !1676)
!1676 = !DILexicalBlockFile(scope: !1677, file: !1, discriminator: 3)
!1677 = distinct !DILexicalBlock(scope: !1670, file: !1, line: 1148, column: 3)
!1678 = !DILocation(line: 1149, column: 1, scope: !445)
!1679 = !DILocalVariable(name: "loop", arg: 1, scope: !448, file: !1, line: 1152, type: !120)
!1680 = !DILocation(line: 1152, column: 28, scope: !448)
!1681 = !DILocalVariable(name: "req", arg: 2, scope: !448, file: !1, line: 1153, type: !105)
!1682 = !DILocation(line: 1153, column: 26, scope: !448)
!1683 = !DILocalVariable(name: "path", arg: 3, scope: !448, file: !1, line: 1154, type: !331)
!1684 = !DILocation(line: 1154, column: 29, scope: !448)
!1685 = !DILocalVariable(name: "mode", arg: 4, scope: !448, file: !1, line: 1155, type: !133)
!1686 = !DILocation(line: 1155, column: 21, scope: !448)
!1687 = !DILocalVariable(name: "cb", arg: 5, scope: !448, file: !1, line: 1156, type: !320)
!1688 = !DILocation(line: 1156, column: 26, scope: !448)
!1689 = !DILocation(line: 1157, column: 3, scope: !448)
!1690 = !DILocation(line: 1157, column: 3, scope: !1691)
!1691 = !DILexicalBlockFile(scope: !1692, file: !1, discriminator: 1)
!1692 = distinct !DILexicalBlock(scope: !448, file: !1, line: 1157, column: 3)
!1693 = !DILocation(line: 1157, column: 3, scope: !1694)
!1694 = !DILexicalBlockFile(scope: !1695, file: !1, discriminator: 2)
!1695 = distinct !DILexicalBlock(scope: !1692, file: !1, line: 1157, column: 3)
!1696 = !DILocation(line: 1157, column: 3, scope: !1697)
!1697 = !DILexicalBlockFile(scope: !1698, file: !1, discriminator: 3)
!1698 = distinct !DILexicalBlock(scope: !1695, file: !1, line: 1157, column: 3)
!1699 = !DILocation(line: 1157, column: 3, scope: !1700)
!1700 = !DILexicalBlockFile(scope: !1701, file: !1, discriminator: 4)
!1701 = distinct !DILexicalBlock(scope: !1698, file: !1, line: 1157, column: 3)
!1702 = !DILocation(line: 1157, column: 3, scope: !1703)
!1703 = !DILexicalBlockFile(scope: !1698, file: !1, discriminator: 5)
!1704 = !DILocation(line: 1157, column: 3, scope: !1705)
!1705 = !DILexicalBlockFile(scope: !1706, file: !1, discriminator: 6)
!1706 = distinct !DILexicalBlock(scope: !1698, file: !1, line: 1157, column: 3)
!1707 = !DILocation(line: 1157, column: 3, scope: !1708)
!1708 = !DILexicalBlockFile(scope: !1709, file: !1, discriminator: 7)
!1709 = distinct !DILexicalBlock(scope: !1706, file: !1, line: 1157, column: 3)
!1710 = !DILocation(line: 1157, column: 3, scope: !1711)
!1711 = !DILexicalBlockFile(scope: !1706, file: !1, discriminator: 8)
!1712 = !DILocation(line: 1157, column: 3, scope: !1713)
!1713 = !DILexicalBlockFile(scope: !1698, file: !1, discriminator: 9)
!1714 = !DILocation(line: 1157, column: 3, scope: !1715)
!1715 = !DILexicalBlockFile(scope: !1698, file: !1, discriminator: 10)
!1716 = !DILocation(line: 1157, column: 3, scope: !1717)
!1717 = !DILexicalBlockFile(scope: !1692, file: !1, discriminator: 11)
!1718 = !DILocation(line: 1158, column: 3, scope: !448)
!1719 = !DILocation(line: 1158, column: 3, scope: !1720)
!1720 = !DILexicalBlockFile(scope: !1721, file: !1, discriminator: 1)
!1721 = distinct !DILexicalBlock(scope: !448, file: !1, line: 1158, column: 3)
!1722 = !DILocation(line: 1158, column: 3, scope: !1723)
!1723 = !DILexicalBlockFile(scope: !1721, file: !1, discriminator: 2)
!1724 = !DILocation(line: 1158, column: 3, scope: !1725)
!1725 = !DILexicalBlockFile(scope: !1721, file: !1, discriminator: 3)
!1726 = !DILocation(line: 1158, column: 3, scope: !1727)
!1727 = !DILexicalBlockFile(scope: !1721, file: !1, discriminator: 4)
!1728 = !DILocation(line: 1158, column: 3, scope: !1729)
!1729 = !DILexicalBlockFile(scope: !1730, file: !1, discriminator: 5)
!1730 = distinct !DILexicalBlock(scope: !1721, file: !1, line: 1158, column: 3)
!1731 = !DILocation(line: 1158, column: 3, scope: !1732)
!1732 = !DILexicalBlockFile(scope: !1733, file: !1, discriminator: 6)
!1733 = distinct !DILexicalBlock(scope: !1730, file: !1, line: 1158, column: 3)
!1734 = !DILocation(line: 1158, column: 3, scope: !1735)
!1735 = !DILexicalBlockFile(scope: !1736, file: !1, discriminator: 7)
!1736 = distinct !DILexicalBlock(scope: !1730, file: !1, line: 1158, column: 3)
!1737 = !DILocation(line: 1158, column: 3, scope: !1738)
!1738 = !DILexicalBlockFile(scope: !1739, file: !1, discriminator: 8)
!1739 = distinct !DILexicalBlock(scope: !1740, file: !1, line: 1158, column: 3)
!1740 = distinct !DILexicalBlock(scope: !1736, file: !1, line: 1158, column: 3)
!1741 = !DILocation(line: 1158, column: 3, scope: !1742)
!1742 = !DILexicalBlockFile(scope: !1743, file: !1, discriminator: 9)
!1743 = distinct !DILexicalBlock(scope: !1739, file: !1, line: 1158, column: 3)
!1744 = !DILocation(line: 1158, column: 3, scope: !1745)
!1745 = !DILexicalBlockFile(scope: !1743, file: !1, discriminator: 10)
!1746 = !DILocation(line: 1158, column: 3, scope: !1747)
!1747 = !DILexicalBlockFile(scope: !1743, file: !1, discriminator: 11)
!1748 = !DILocation(line: 1158, column: 3, scope: !1749)
!1749 = !DILexicalBlockFile(scope: !1743, file: !1, discriminator: 12)
!1750 = !DILocation(line: 1158, column: 3, scope: !1751)
!1751 = !DILexicalBlockFile(scope: !1743, file: !1, discriminator: 13)
!1752 = !DILocation(line: 1158, column: 3, scope: !1753)
!1753 = !DILexicalBlockFile(scope: !1754, file: !1, discriminator: 14)
!1754 = distinct !DILexicalBlock(scope: !1743, file: !1, line: 1158, column: 3)
!1755 = !DILocation(line: 1158, column: 3, scope: !1756)
!1756 = !DILexicalBlockFile(scope: !1743, file: !1, discriminator: 15)
!1757 = !DILocation(line: 1158, column: 3, scope: !1758)
!1758 = !DILexicalBlockFile(scope: !1739, file: !1, discriminator: 16)
!1759 = !DILocation(line: 1158, column: 3, scope: !1760)
!1760 = !DILexicalBlockFile(scope: !1721, file: !1, discriminator: 17)
!1761 = !DILocation(line: 1159, column: 15, scope: !448)
!1762 = !DILocation(line: 1159, column: 3, scope: !448)
!1763 = !DILocation(line: 1159, column: 8, scope: !448)
!1764 = !DILocation(line: 1159, column: 13, scope: !448)
!1765 = !DILocation(line: 1160, column: 3, scope: !448)
!1766 = !DILocation(line: 1160, column: 3, scope: !1767)
!1767 = !DILexicalBlockFile(scope: !1768, file: !1, discriminator: 1)
!1768 = distinct !DILexicalBlock(scope: !1769, file: !1, line: 1160, column: 3)
!1769 = distinct !DILexicalBlock(scope: !448, file: !1, line: 1160, column: 3)
!1770 = !DILocation(line: 1160, column: 3, scope: !1771)
!1771 = !DILexicalBlockFile(scope: !1772, file: !1, discriminator: 2)
!1772 = distinct !DILexicalBlock(scope: !1768, file: !1, line: 1160, column: 3)
!1773 = !DILocation(line: 1160, column: 3, scope: !1774)
!1774 = !DILexicalBlockFile(scope: !1775, file: !1, discriminator: 3)
!1775 = distinct !DILexicalBlock(scope: !1768, file: !1, line: 1160, column: 3)
!1776 = !DILocation(line: 1161, column: 1, scope: !448)
!1777 = !DILocalVariable(name: "loop", arg: 1, scope: !449, file: !1, line: 1164, type: !120)
!1778 = !DILocation(line: 1164, column: 30, scope: !449)
!1779 = !DILocalVariable(name: "req", arg: 2, scope: !449, file: !1, line: 1165, type: !105)
!1780 = !DILocation(line: 1165, column: 28, scope: !449)
!1781 = !DILocalVariable(name: "tpl", arg: 3, scope: !449, file: !1, line: 1166, type: !331)
!1782 = !DILocation(line: 1166, column: 31, scope: !449)
!1783 = !DILocalVariable(name: "cb", arg: 4, scope: !449, file: !1, line: 1167, type: !320)
!1784 = !DILocation(line: 1167, column: 28, scope: !449)
!1785 = !DILocation(line: 1168, column: 3, scope: !449)
!1786 = !DILocation(line: 1168, column: 3, scope: !1787)
!1787 = !DILexicalBlockFile(scope: !1788, file: !1, discriminator: 1)
!1788 = distinct !DILexicalBlock(scope: !449, file: !1, line: 1168, column: 3)
!1789 = !DILocation(line: 1168, column: 3, scope: !1790)
!1790 = !DILexicalBlockFile(scope: !1791, file: !1, discriminator: 2)
!1791 = distinct !DILexicalBlock(scope: !1788, file: !1, line: 1168, column: 3)
!1792 = !DILocation(line: 1168, column: 3, scope: !1793)
!1793 = !DILexicalBlockFile(scope: !1794, file: !1, discriminator: 3)
!1794 = distinct !DILexicalBlock(scope: !1791, file: !1, line: 1168, column: 3)
!1795 = !DILocation(line: 1168, column: 3, scope: !1796)
!1796 = !DILexicalBlockFile(scope: !1797, file: !1, discriminator: 4)
!1797 = distinct !DILexicalBlock(scope: !1794, file: !1, line: 1168, column: 3)
!1798 = !DILocation(line: 1168, column: 3, scope: !1799)
!1799 = !DILexicalBlockFile(scope: !1794, file: !1, discriminator: 5)
!1800 = !DILocation(line: 1168, column: 3, scope: !1801)
!1801 = !DILexicalBlockFile(scope: !1802, file: !1, discriminator: 6)
!1802 = distinct !DILexicalBlock(scope: !1794, file: !1, line: 1168, column: 3)
!1803 = !DILocation(line: 1168, column: 3, scope: !1804)
!1804 = !DILexicalBlockFile(scope: !1805, file: !1, discriminator: 7)
!1805 = distinct !DILexicalBlock(scope: !1802, file: !1, line: 1168, column: 3)
!1806 = !DILocation(line: 1168, column: 3, scope: !1807)
!1807 = !DILexicalBlockFile(scope: !1802, file: !1, discriminator: 8)
!1808 = !DILocation(line: 1168, column: 3, scope: !1809)
!1809 = !DILexicalBlockFile(scope: !1794, file: !1, discriminator: 9)
!1810 = !DILocation(line: 1168, column: 3, scope: !1811)
!1811 = !DILexicalBlockFile(scope: !1794, file: !1, discriminator: 10)
!1812 = !DILocation(line: 1168, column: 3, scope: !1813)
!1813 = !DILexicalBlockFile(scope: !1788, file: !1, discriminator: 11)
!1814 = !DILocation(line: 1169, column: 26, scope: !449)
!1815 = !DILocation(line: 1169, column: 15, scope: !449)
!1816 = !DILocation(line: 1169, column: 3, scope: !449)
!1817 = !DILocation(line: 1169, column: 8, scope: !449)
!1818 = !DILocation(line: 1169, column: 13, scope: !449)
!1819 = !DILocation(line: 1170, column: 7, scope: !1820)
!1820 = distinct !DILexicalBlock(scope: !449, file: !1, line: 1170, column: 7)
!1821 = !DILocation(line: 1170, column: 12, scope: !1820)
!1822 = !DILocation(line: 1170, column: 17, scope: !1820)
!1823 = !DILocation(line: 1170, column: 7, scope: !449)
!1824 = !DILocation(line: 1171, column: 9, scope: !1825)
!1825 = distinct !DILexicalBlock(scope: !1826, file: !1, line: 1171, column: 9)
!1826 = distinct !DILexicalBlock(scope: !1820, file: !1, line: 1170, column: 26)
!1827 = !DILocation(line: 1171, column: 12, scope: !1825)
!1828 = !DILocation(line: 1171, column: 9, scope: !1826)
!1829 = !DILocation(line: 1172, column: 7, scope: !1825)
!1830 = !DILocation(line: 1172, column: 7, scope: !1831)
!1831 = !DILexicalBlockFile(scope: !1832, file: !1, discriminator: 1)
!1832 = distinct !DILexicalBlock(scope: !1825, file: !1, line: 1172, column: 7)
!1833 = !DILocation(line: 1172, column: 7, scope: !1834)
!1834 = !DILexicalBlockFile(scope: !1832, file: !1, discriminator: 2)
!1835 = !DILocation(line: 1172, column: 7, scope: !1836)
!1836 = !DILexicalBlockFile(scope: !1832, file: !1, discriminator: 3)
!1837 = !DILocation(line: 1172, column: 7, scope: !1838)
!1838 = !DILexicalBlockFile(scope: !1832, file: !1, discriminator: 4)
!1839 = !DILocation(line: 1172, column: 7, scope: !1840)
!1840 = !DILexicalBlockFile(scope: !1832, file: !1, discriminator: 5)
!1841 = !DILocation(line: 1172, column: 7, scope: !1842)
!1842 = !DILexicalBlockFile(scope: !1843, file: !1, discriminator: 6)
!1843 = distinct !DILexicalBlock(scope: !1832, file: !1, line: 1172, column: 7)
!1844 = !DILocation(line: 1172, column: 7, scope: !1845)
!1845 = !DILexicalBlockFile(scope: !1832, file: !1, discriminator: 7)
!1846 = !DILocation(line: 1172, column: 7, scope: !1847)
!1847 = !DILexicalBlockFile(scope: !1832, file: !1, discriminator: 8)
!1848 = !DILocation(line: 1173, column: 5, scope: !1826)
!1849 = !DILocation(line: 1175, column: 3, scope: !449)
!1850 = !DILocation(line: 1175, column: 3, scope: !1851)
!1851 = !DILexicalBlockFile(scope: !1852, file: !1, discriminator: 1)
!1852 = distinct !DILexicalBlock(scope: !1853, file: !1, line: 1175, column: 3)
!1853 = distinct !DILexicalBlock(scope: !449, file: !1, line: 1175, column: 3)
!1854 = !DILocation(line: 1175, column: 3, scope: !1855)
!1855 = !DILexicalBlockFile(scope: !1856, file: !1, discriminator: 2)
!1856 = distinct !DILexicalBlock(scope: !1852, file: !1, line: 1175, column: 3)
!1857 = !DILocation(line: 1175, column: 3, scope: !1858)
!1858 = !DILexicalBlockFile(scope: !1859, file: !1, discriminator: 3)
!1859 = distinct !DILexicalBlock(scope: !1852, file: !1, line: 1175, column: 3)
!1860 = !DILocation(line: 1176, column: 1, scope: !449)
!1861 = !DILocalVariable(name: "loop", arg: 1, scope: !450, file: !1, line: 1179, type: !120)
!1862 = !DILocation(line: 1179, column: 27, scope: !450)
!1863 = !DILocalVariable(name: "req", arg: 2, scope: !450, file: !1, line: 1180, type: !105)
!1864 = !DILocation(line: 1180, column: 25, scope: !450)
!1865 = !DILocalVariable(name: "path", arg: 3, scope: !450, file: !1, line: 1181, type: !331)
!1866 = !DILocation(line: 1181, column: 28, scope: !450)
!1867 = !DILocalVariable(name: "flags", arg: 4, scope: !450, file: !1, line: 1182, type: !133)
!1868 = !DILocation(line: 1182, column: 20, scope: !450)
!1869 = !DILocalVariable(name: "mode", arg: 5, scope: !450, file: !1, line: 1183, type: !133)
!1870 = !DILocation(line: 1183, column: 20, scope: !450)
!1871 = !DILocalVariable(name: "cb", arg: 6, scope: !450, file: !1, line: 1184, type: !320)
!1872 = !DILocation(line: 1184, column: 25, scope: !450)
!1873 = !DILocation(line: 1185, column: 3, scope: !450)
!1874 = !DILocation(line: 1185, column: 3, scope: !1875)
!1875 = !DILexicalBlockFile(scope: !1876, file: !1, discriminator: 1)
!1876 = distinct !DILexicalBlock(scope: !450, file: !1, line: 1185, column: 3)
!1877 = !DILocation(line: 1185, column: 3, scope: !1878)
!1878 = !DILexicalBlockFile(scope: !1879, file: !1, discriminator: 2)
!1879 = distinct !DILexicalBlock(scope: !1876, file: !1, line: 1185, column: 3)
!1880 = !DILocation(line: 1185, column: 3, scope: !1881)
!1881 = !DILexicalBlockFile(scope: !1882, file: !1, discriminator: 3)
!1882 = distinct !DILexicalBlock(scope: !1879, file: !1, line: 1185, column: 3)
!1883 = !DILocation(line: 1185, column: 3, scope: !1884)
!1884 = !DILexicalBlockFile(scope: !1885, file: !1, discriminator: 4)
!1885 = distinct !DILexicalBlock(scope: !1882, file: !1, line: 1185, column: 3)
!1886 = !DILocation(line: 1185, column: 3, scope: !1887)
!1887 = !DILexicalBlockFile(scope: !1882, file: !1, discriminator: 5)
!1888 = !DILocation(line: 1185, column: 3, scope: !1889)
!1889 = !DILexicalBlockFile(scope: !1890, file: !1, discriminator: 6)
!1890 = distinct !DILexicalBlock(scope: !1882, file: !1, line: 1185, column: 3)
!1891 = !DILocation(line: 1185, column: 3, scope: !1892)
!1892 = !DILexicalBlockFile(scope: !1893, file: !1, discriminator: 7)
!1893 = distinct !DILexicalBlock(scope: !1890, file: !1, line: 1185, column: 3)
!1894 = !DILocation(line: 1185, column: 3, scope: !1895)
!1895 = !DILexicalBlockFile(scope: !1890, file: !1, discriminator: 8)
!1896 = !DILocation(line: 1185, column: 3, scope: !1897)
!1897 = !DILexicalBlockFile(scope: !1882, file: !1, discriminator: 9)
!1898 = !DILocation(line: 1185, column: 3, scope: !1899)
!1899 = !DILexicalBlockFile(scope: !1882, file: !1, discriminator: 10)
!1900 = !DILocation(line: 1185, column: 3, scope: !1901)
!1901 = !DILexicalBlockFile(scope: !1876, file: !1, discriminator: 11)
!1902 = !DILocation(line: 1186, column: 3, scope: !450)
!1903 = !DILocation(line: 1186, column: 3, scope: !1904)
!1904 = !DILexicalBlockFile(scope: !1905, file: !1, discriminator: 1)
!1905 = distinct !DILexicalBlock(scope: !450, file: !1, line: 1186, column: 3)
!1906 = !DILocation(line: 1186, column: 3, scope: !1907)
!1907 = !DILexicalBlockFile(scope: !1905, file: !1, discriminator: 2)
!1908 = !DILocation(line: 1186, column: 3, scope: !1909)
!1909 = !DILexicalBlockFile(scope: !1905, file: !1, discriminator: 3)
!1910 = !DILocation(line: 1186, column: 3, scope: !1911)
!1911 = !DILexicalBlockFile(scope: !1905, file: !1, discriminator: 4)
!1912 = !DILocation(line: 1186, column: 3, scope: !1913)
!1913 = !DILexicalBlockFile(scope: !1914, file: !1, discriminator: 5)
!1914 = distinct !DILexicalBlock(scope: !1905, file: !1, line: 1186, column: 3)
!1915 = !DILocation(line: 1186, column: 3, scope: !1916)
!1916 = !DILexicalBlockFile(scope: !1917, file: !1, discriminator: 6)
!1917 = distinct !DILexicalBlock(scope: !1914, file: !1, line: 1186, column: 3)
!1918 = !DILocation(line: 1186, column: 3, scope: !1919)
!1919 = !DILexicalBlockFile(scope: !1920, file: !1, discriminator: 7)
!1920 = distinct !DILexicalBlock(scope: !1914, file: !1, line: 1186, column: 3)
!1921 = !DILocation(line: 1186, column: 3, scope: !1922)
!1922 = !DILexicalBlockFile(scope: !1923, file: !1, discriminator: 8)
!1923 = distinct !DILexicalBlock(scope: !1924, file: !1, line: 1186, column: 3)
!1924 = distinct !DILexicalBlock(scope: !1920, file: !1, line: 1186, column: 3)
!1925 = !DILocation(line: 1186, column: 3, scope: !1926)
!1926 = !DILexicalBlockFile(scope: !1927, file: !1, discriminator: 9)
!1927 = distinct !DILexicalBlock(scope: !1923, file: !1, line: 1186, column: 3)
!1928 = !DILocation(line: 1186, column: 3, scope: !1929)
!1929 = !DILexicalBlockFile(scope: !1927, file: !1, discriminator: 10)
!1930 = !DILocation(line: 1186, column: 3, scope: !1931)
!1931 = !DILexicalBlockFile(scope: !1927, file: !1, discriminator: 11)
!1932 = !DILocation(line: 1186, column: 3, scope: !1933)
!1933 = !DILexicalBlockFile(scope: !1927, file: !1, discriminator: 12)
!1934 = !DILocation(line: 1186, column: 3, scope: !1935)
!1935 = !DILexicalBlockFile(scope: !1927, file: !1, discriminator: 13)
!1936 = !DILocation(line: 1186, column: 3, scope: !1937)
!1937 = !DILexicalBlockFile(scope: !1938, file: !1, discriminator: 14)
!1938 = distinct !DILexicalBlock(scope: !1927, file: !1, line: 1186, column: 3)
!1939 = !DILocation(line: 1186, column: 3, scope: !1940)
!1940 = !DILexicalBlockFile(scope: !1927, file: !1, discriminator: 15)
!1941 = !DILocation(line: 1186, column: 3, scope: !1942)
!1942 = !DILexicalBlockFile(scope: !1923, file: !1, discriminator: 16)
!1943 = !DILocation(line: 1186, column: 3, scope: !1944)
!1944 = !DILexicalBlockFile(scope: !1905, file: !1, discriminator: 17)
!1945 = !DILocation(line: 1187, column: 16, scope: !450)
!1946 = !DILocation(line: 1187, column: 3, scope: !450)
!1947 = !DILocation(line: 1187, column: 8, scope: !450)
!1948 = !DILocation(line: 1187, column: 14, scope: !450)
!1949 = !DILocation(line: 1188, column: 15, scope: !450)
!1950 = !DILocation(line: 1188, column: 3, scope: !450)
!1951 = !DILocation(line: 1188, column: 8, scope: !450)
!1952 = !DILocation(line: 1188, column: 13, scope: !450)
!1953 = !DILocation(line: 1189, column: 3, scope: !450)
!1954 = !DILocation(line: 1189, column: 3, scope: !1955)
!1955 = !DILexicalBlockFile(scope: !1956, file: !1, discriminator: 1)
!1956 = distinct !DILexicalBlock(scope: !1957, file: !1, line: 1189, column: 3)
!1957 = distinct !DILexicalBlock(scope: !450, file: !1, line: 1189, column: 3)
!1958 = !DILocation(line: 1189, column: 3, scope: !1959)
!1959 = !DILexicalBlockFile(scope: !1960, file: !1, discriminator: 2)
!1960 = distinct !DILexicalBlock(scope: !1956, file: !1, line: 1189, column: 3)
!1961 = !DILocation(line: 1189, column: 3, scope: !1962)
!1962 = !DILexicalBlockFile(scope: !1963, file: !1, discriminator: 3)
!1963 = distinct !DILexicalBlock(scope: !1956, file: !1, line: 1189, column: 3)
!1964 = !DILocation(line: 1190, column: 1, scope: !450)
!1965 = !DILocalVariable(name: "loop", arg: 1, scope: !453, file: !1, line: 1193, type: !120)
!1966 = !DILocation(line: 1193, column: 27, scope: !453)
!1967 = !DILocalVariable(name: "req", arg: 2, scope: !453, file: !1, line: 1193, type: !105)
!1968 = !DILocation(line: 1193, column: 42, scope: !453)
!1969 = !DILocalVariable(name: "file", arg: 3, scope: !453, file: !1, line: 1194, type: !360)
!1970 = !DILocation(line: 1194, column: 24, scope: !453)
!1971 = !DILocalVariable(name: "bufs", arg: 4, scope: !453, file: !1, line: 1195, type: !456)
!1972 = !DILocation(line: 1195, column: 31, scope: !453)
!1973 = !DILocalVariable(name: "nbufs", arg: 5, scope: !453, file: !1, line: 1196, type: !126)
!1974 = !DILocation(line: 1196, column: 29, scope: !453)
!1975 = !DILocalVariable(name: "off", arg: 6, scope: !453, file: !1, line: 1197, type: !438)
!1976 = !DILocation(line: 1197, column: 24, scope: !453)
!1977 = !DILocalVariable(name: "cb", arg: 7, scope: !453, file: !1, line: 1198, type: !320)
!1978 = !DILocation(line: 1198, column: 25, scope: !453)
!1979 = !DILocation(line: 1199, column: 7, scope: !1980)
!1980 = distinct !DILexicalBlock(scope: !453, file: !1, line: 1199, column: 7)
!1981 = !DILocation(line: 1199, column: 12, scope: !1980)
!1982 = !DILocation(line: 1199, column: 20, scope: !1980)
!1983 = !DILocation(line: 1199, column: 23, scope: !1984)
!1984 = !DILexicalBlockFile(scope: !1980, file: !1, discriminator: 1)
!1985 = !DILocation(line: 1199, column: 29, scope: !1984)
!1986 = !DILocation(line: 1199, column: 7, scope: !1984)
!1987 = !DILocation(line: 1200, column: 5, scope: !1980)
!1988 = !DILocation(line: 1202, column: 3, scope: !453)
!1989 = !DILocation(line: 1202, column: 3, scope: !1990)
!1990 = !DILexicalBlockFile(scope: !1991, file: !1, discriminator: 1)
!1991 = distinct !DILexicalBlock(scope: !453, file: !1, line: 1202, column: 3)
!1992 = !DILocation(line: 1202, column: 3, scope: !1993)
!1993 = !DILexicalBlockFile(scope: !1994, file: !1, discriminator: 2)
!1994 = distinct !DILexicalBlock(scope: !1991, file: !1, line: 1202, column: 3)
!1995 = !DILocation(line: 1202, column: 3, scope: !1996)
!1996 = !DILexicalBlockFile(scope: !1997, file: !1, discriminator: 3)
!1997 = distinct !DILexicalBlock(scope: !1994, file: !1, line: 1202, column: 3)
!1998 = !DILocation(line: 1202, column: 3, scope: !1999)
!1999 = !DILexicalBlockFile(scope: !2000, file: !1, discriminator: 4)
!2000 = distinct !DILexicalBlock(scope: !1997, file: !1, line: 1202, column: 3)
!2001 = !DILocation(line: 1202, column: 3, scope: !2002)
!2002 = !DILexicalBlockFile(scope: !1997, file: !1, discriminator: 5)
!2003 = !DILocation(line: 1202, column: 3, scope: !2004)
!2004 = !DILexicalBlockFile(scope: !2005, file: !1, discriminator: 6)
!2005 = distinct !DILexicalBlock(scope: !1997, file: !1, line: 1202, column: 3)
!2006 = !DILocation(line: 1202, column: 3, scope: !2007)
!2007 = !DILexicalBlockFile(scope: !2008, file: !1, discriminator: 7)
!2008 = distinct !DILexicalBlock(scope: !2005, file: !1, line: 1202, column: 3)
!2009 = !DILocation(line: 1202, column: 3, scope: !2010)
!2010 = !DILexicalBlockFile(scope: !2005, file: !1, discriminator: 8)
!2011 = !DILocation(line: 1202, column: 3, scope: !2012)
!2012 = !DILexicalBlockFile(scope: !1997, file: !1, discriminator: 9)
!2013 = !DILocation(line: 1202, column: 3, scope: !2014)
!2014 = !DILexicalBlockFile(scope: !1997, file: !1, discriminator: 10)
!2015 = !DILocation(line: 1202, column: 3, scope: !2016)
!2016 = !DILexicalBlockFile(scope: !1991, file: !1, discriminator: 11)
!2017 = !DILocation(line: 1203, column: 15, scope: !453)
!2018 = !DILocation(line: 1203, column: 3, scope: !453)
!2019 = !DILocation(line: 1203, column: 8, scope: !453)
!2020 = !DILocation(line: 1203, column: 13, scope: !453)
!2021 = !DILocation(line: 1205, column: 16, scope: !453)
!2022 = !DILocation(line: 1205, column: 3, scope: !453)
!2023 = !DILocation(line: 1205, column: 8, scope: !453)
!2024 = !DILocation(line: 1205, column: 14, scope: !453)
!2025 = !DILocation(line: 1206, column: 15, scope: !453)
!2026 = !DILocation(line: 1206, column: 20, scope: !453)
!2027 = !DILocation(line: 1206, column: 3, scope: !453)
!2028 = !DILocation(line: 1206, column: 8, scope: !453)
!2029 = !DILocation(line: 1206, column: 13, scope: !453)
!2030 = !DILocation(line: 1207, column: 7, scope: !2031)
!2031 = distinct !DILexicalBlock(scope: !453, file: !1, line: 1207, column: 7)
!2032 = !DILocation(line: 1207, column: 13, scope: !2031)
!2033 = !DILocation(line: 1207, column: 7, scope: !453)
!2034 = !DILocation(line: 1208, column: 28, scope: !2031)
!2035 = !DILocation(line: 1208, column: 34, scope: !2031)
!2036 = !DILocation(line: 1208, column: 17, scope: !2031)
!2037 = !DILocation(line: 1208, column: 5, scope: !2031)
!2038 = !DILocation(line: 1208, column: 10, scope: !2031)
!2039 = !DILocation(line: 1208, column: 15, scope: !2031)
!2040 = !DILocation(line: 1210, column: 7, scope: !2041)
!2041 = distinct !DILexicalBlock(scope: !453, file: !1, line: 1210, column: 7)
!2042 = !DILocation(line: 1210, column: 12, scope: !2041)
!2043 = !DILocation(line: 1210, column: 17, scope: !2041)
!2044 = !DILocation(line: 1210, column: 7, scope: !453)
!2045 = !DILocation(line: 1211, column: 9, scope: !2046)
!2046 = distinct !DILexicalBlock(scope: !2047, file: !1, line: 1211, column: 9)
!2047 = distinct !DILexicalBlock(scope: !2041, file: !1, line: 1210, column: 26)
!2048 = !DILocation(line: 1211, column: 12, scope: !2046)
!2049 = !DILocation(line: 1211, column: 9, scope: !2047)
!2050 = !DILocation(line: 1212, column: 7, scope: !2046)
!2051 = !DILocation(line: 1212, column: 7, scope: !2052)
!2052 = !DILexicalBlockFile(scope: !2053, file: !1, discriminator: 1)
!2053 = distinct !DILexicalBlock(scope: !2046, file: !1, line: 1212, column: 7)
!2054 = !DILocation(line: 1212, column: 7, scope: !2055)
!2055 = !DILexicalBlockFile(scope: !2053, file: !1, discriminator: 2)
!2056 = !DILocation(line: 1212, column: 7, scope: !2057)
!2057 = !DILexicalBlockFile(scope: !2053, file: !1, discriminator: 3)
!2058 = !DILocation(line: 1212, column: 7, scope: !2059)
!2059 = !DILexicalBlockFile(scope: !2053, file: !1, discriminator: 4)
!2060 = !DILocation(line: 1212, column: 7, scope: !2061)
!2061 = !DILexicalBlockFile(scope: !2053, file: !1, discriminator: 5)
!2062 = !DILocation(line: 1212, column: 7, scope: !2063)
!2063 = !DILexicalBlockFile(scope: !2064, file: !1, discriminator: 6)
!2064 = distinct !DILexicalBlock(scope: !2053, file: !1, line: 1212, column: 7)
!2065 = !DILocation(line: 1212, column: 7, scope: !2066)
!2066 = !DILexicalBlockFile(scope: !2053, file: !1, discriminator: 7)
!2067 = !DILocation(line: 1212, column: 7, scope: !2068)
!2068 = !DILexicalBlockFile(scope: !2053, file: !1, discriminator: 8)
!2069 = !DILocation(line: 1213, column: 5, scope: !2047)
!2070 = !DILocation(line: 1216, column: 10, scope: !453)
!2071 = !DILocation(line: 1216, column: 15, scope: !453)
!2072 = !DILocation(line: 1216, column: 3, scope: !453)
!2073 = !DILocation(line: 1216, column: 21, scope: !453)
!2074 = !DILocation(line: 1216, column: 27, scope: !453)
!2075 = !DILocation(line: 1216, column: 33, scope: !453)
!2076 = !DILocation(line: 1218, column: 14, scope: !453)
!2077 = !DILocation(line: 1218, column: 3, scope: !453)
!2078 = !DILocation(line: 1218, column: 8, scope: !453)
!2079 = !DILocation(line: 1218, column: 12, scope: !453)
!2080 = !DILocation(line: 1219, column: 3, scope: !453)
!2081 = !DILocation(line: 1219, column: 3, scope: !2082)
!2082 = !DILexicalBlockFile(scope: !2083, file: !1, discriminator: 1)
!2083 = distinct !DILexicalBlock(scope: !2084, file: !1, line: 1219, column: 3)
!2084 = distinct !DILexicalBlock(scope: !453, file: !1, line: 1219, column: 3)
!2085 = !DILocation(line: 1219, column: 3, scope: !2086)
!2086 = !DILexicalBlockFile(scope: !2087, file: !1, discriminator: 2)
!2087 = distinct !DILexicalBlock(scope: !2083, file: !1, line: 1219, column: 3)
!2088 = !DILocation(line: 1219, column: 3, scope: !2089)
!2089 = !DILexicalBlockFile(scope: !2090, file: !1, discriminator: 3)
!2090 = distinct !DILexicalBlock(scope: !2083, file: !1, line: 1219, column: 3)
!2091 = !DILocation(line: 1220, column: 1, scope: !453)
!2092 = !DILocalVariable(name: "loop", arg: 1, scope: !458, file: !1, line: 1223, type: !120)
!2093 = !DILocation(line: 1223, column: 30, scope: !458)
!2094 = !DILocalVariable(name: "req", arg: 2, scope: !458, file: !1, line: 1224, type: !105)
!2095 = !DILocation(line: 1224, column: 28, scope: !458)
!2096 = !DILocalVariable(name: "path", arg: 3, scope: !458, file: !1, line: 1225, type: !331)
!2097 = !DILocation(line: 1225, column: 31, scope: !458)
!2098 = !DILocalVariable(name: "flags", arg: 4, scope: !458, file: !1, line: 1226, type: !133)
!2099 = !DILocation(line: 1226, column: 23, scope: !458)
!2100 = !DILocalVariable(name: "cb", arg: 5, scope: !458, file: !1, line: 1227, type: !320)
!2101 = !DILocation(line: 1227, column: 28, scope: !458)
!2102 = !DILocation(line: 1228, column: 3, scope: !458)
!2103 = !DILocation(line: 1228, column: 3, scope: !2104)
!2104 = !DILexicalBlockFile(scope: !2105, file: !1, discriminator: 1)
!2105 = distinct !DILexicalBlock(scope: !458, file: !1, line: 1228, column: 3)
!2106 = !DILocation(line: 1228, column: 3, scope: !2107)
!2107 = !DILexicalBlockFile(scope: !2108, file: !1, discriminator: 2)
!2108 = distinct !DILexicalBlock(scope: !2105, file: !1, line: 1228, column: 3)
!2109 = !DILocation(line: 1228, column: 3, scope: !2110)
!2110 = !DILexicalBlockFile(scope: !2111, file: !1, discriminator: 3)
!2111 = distinct !DILexicalBlock(scope: !2108, file: !1, line: 1228, column: 3)
!2112 = !DILocation(line: 1228, column: 3, scope: !2113)
!2113 = !DILexicalBlockFile(scope: !2114, file: !1, discriminator: 4)
!2114 = distinct !DILexicalBlock(scope: !2111, file: !1, line: 1228, column: 3)
!2115 = !DILocation(line: 1228, column: 3, scope: !2116)
!2116 = !DILexicalBlockFile(scope: !2111, file: !1, discriminator: 5)
!2117 = !DILocation(line: 1228, column: 3, scope: !2118)
!2118 = !DILexicalBlockFile(scope: !2119, file: !1, discriminator: 6)
!2119 = distinct !DILexicalBlock(scope: !2111, file: !1, line: 1228, column: 3)
!2120 = !DILocation(line: 1228, column: 3, scope: !2121)
!2121 = !DILexicalBlockFile(scope: !2122, file: !1, discriminator: 7)
!2122 = distinct !DILexicalBlock(scope: !2119, file: !1, line: 1228, column: 3)
!2123 = !DILocation(line: 1228, column: 3, scope: !2124)
!2124 = !DILexicalBlockFile(scope: !2119, file: !1, discriminator: 8)
!2125 = !DILocation(line: 1228, column: 3, scope: !2126)
!2126 = !DILexicalBlockFile(scope: !2111, file: !1, discriminator: 9)
!2127 = !DILocation(line: 1228, column: 3, scope: !2128)
!2128 = !DILexicalBlockFile(scope: !2111, file: !1, discriminator: 10)
!2129 = !DILocation(line: 1228, column: 3, scope: !2130)
!2130 = !DILexicalBlockFile(scope: !2105, file: !1, discriminator: 11)
!2131 = !DILocation(line: 1229, column: 3, scope: !458)
!2132 = !DILocation(line: 1229, column: 3, scope: !2133)
!2133 = !DILexicalBlockFile(scope: !2134, file: !1, discriminator: 1)
!2134 = distinct !DILexicalBlock(scope: !458, file: !1, line: 1229, column: 3)
!2135 = !DILocation(line: 1229, column: 3, scope: !2136)
!2136 = !DILexicalBlockFile(scope: !2134, file: !1, discriminator: 2)
!2137 = !DILocation(line: 1229, column: 3, scope: !2138)
!2138 = !DILexicalBlockFile(scope: !2134, file: !1, discriminator: 3)
!2139 = !DILocation(line: 1229, column: 3, scope: !2140)
!2140 = !DILexicalBlockFile(scope: !2134, file: !1, discriminator: 4)
!2141 = !DILocation(line: 1229, column: 3, scope: !2142)
!2142 = !DILexicalBlockFile(scope: !2143, file: !1, discriminator: 5)
!2143 = distinct !DILexicalBlock(scope: !2134, file: !1, line: 1229, column: 3)
!2144 = !DILocation(line: 1229, column: 3, scope: !2145)
!2145 = !DILexicalBlockFile(scope: !2146, file: !1, discriminator: 6)
!2146 = distinct !DILexicalBlock(scope: !2143, file: !1, line: 1229, column: 3)
!2147 = !DILocation(line: 1229, column: 3, scope: !2148)
!2148 = !DILexicalBlockFile(scope: !2149, file: !1, discriminator: 7)
!2149 = distinct !DILexicalBlock(scope: !2143, file: !1, line: 1229, column: 3)
!2150 = !DILocation(line: 1229, column: 3, scope: !2151)
!2151 = !DILexicalBlockFile(scope: !2152, file: !1, discriminator: 8)
!2152 = distinct !DILexicalBlock(scope: !2153, file: !1, line: 1229, column: 3)
!2153 = distinct !DILexicalBlock(scope: !2149, file: !1, line: 1229, column: 3)
!2154 = !DILocation(line: 1229, column: 3, scope: !2155)
!2155 = !DILexicalBlockFile(scope: !2156, file: !1, discriminator: 9)
!2156 = distinct !DILexicalBlock(scope: !2152, file: !1, line: 1229, column: 3)
!2157 = !DILocation(line: 1229, column: 3, scope: !2158)
!2158 = !DILexicalBlockFile(scope: !2156, file: !1, discriminator: 10)
!2159 = !DILocation(line: 1229, column: 3, scope: !2160)
!2160 = !DILexicalBlockFile(scope: !2156, file: !1, discriminator: 11)
!2161 = !DILocation(line: 1229, column: 3, scope: !2162)
!2162 = !DILexicalBlockFile(scope: !2156, file: !1, discriminator: 12)
!2163 = !DILocation(line: 1229, column: 3, scope: !2164)
!2164 = !DILexicalBlockFile(scope: !2156, file: !1, discriminator: 13)
!2165 = !DILocation(line: 1229, column: 3, scope: !2166)
!2166 = !DILexicalBlockFile(scope: !2167, file: !1, discriminator: 14)
!2167 = distinct !DILexicalBlock(scope: !2156, file: !1, line: 1229, column: 3)
!2168 = !DILocation(line: 1229, column: 3, scope: !2169)
!2169 = !DILexicalBlockFile(scope: !2156, file: !1, discriminator: 15)
!2170 = !DILocation(line: 1229, column: 3, scope: !2171)
!2171 = !DILexicalBlockFile(scope: !2152, file: !1, discriminator: 16)
!2172 = !DILocation(line: 1229, column: 3, scope: !2173)
!2173 = !DILexicalBlockFile(scope: !2134, file: !1, discriminator: 17)
!2174 = !DILocation(line: 1230, column: 16, scope: !458)
!2175 = !DILocation(line: 1230, column: 3, scope: !458)
!2176 = !DILocation(line: 1230, column: 8, scope: !458)
!2177 = !DILocation(line: 1230, column: 14, scope: !458)
!2178 = !DILocation(line: 1231, column: 3, scope: !458)
!2179 = !DILocation(line: 1231, column: 3, scope: !2180)
!2180 = !DILexicalBlockFile(scope: !2181, file: !1, discriminator: 1)
!2181 = distinct !DILexicalBlock(scope: !2182, file: !1, line: 1231, column: 3)
!2182 = distinct !DILexicalBlock(scope: !458, file: !1, line: 1231, column: 3)
!2183 = !DILocation(line: 1231, column: 3, scope: !2184)
!2184 = !DILexicalBlockFile(scope: !2185, file: !1, discriminator: 2)
!2185 = distinct !DILexicalBlock(scope: !2181, file: !1, line: 1231, column: 3)
!2186 = !DILocation(line: 1231, column: 3, scope: !2187)
!2187 = !DILexicalBlockFile(scope: !2188, file: !1, discriminator: 3)
!2188 = distinct !DILexicalBlock(scope: !2181, file: !1, line: 1231, column: 3)
!2189 = !DILocation(line: 1232, column: 1, scope: !458)
!2190 = !DILocalVariable(name: "loop", arg: 1, scope: !459, file: !1, line: 1235, type: !120)
!2191 = !DILocation(line: 1235, column: 31, scope: !459)
!2192 = !DILocalVariable(name: "req", arg: 2, scope: !459, file: !1, line: 1236, type: !105)
!2193 = !DILocation(line: 1236, column: 29, scope: !459)
!2194 = !DILocalVariable(name: "path", arg: 3, scope: !459, file: !1, line: 1237, type: !331)
!2195 = !DILocation(line: 1237, column: 32, scope: !459)
!2196 = !DILocalVariable(name: "cb", arg: 4, scope: !459, file: !1, line: 1238, type: !320)
!2197 = !DILocation(line: 1238, column: 29, scope: !459)
!2198 = !DILocation(line: 1239, column: 3, scope: !459)
!2199 = !DILocation(line: 1239, column: 3, scope: !2200)
!2200 = !DILexicalBlockFile(scope: !2201, file: !1, discriminator: 1)
!2201 = distinct !DILexicalBlock(scope: !459, file: !1, line: 1239, column: 3)
!2202 = !DILocation(line: 1239, column: 3, scope: !2203)
!2203 = !DILexicalBlockFile(scope: !2204, file: !1, discriminator: 2)
!2204 = distinct !DILexicalBlock(scope: !2201, file: !1, line: 1239, column: 3)
!2205 = !DILocation(line: 1239, column: 3, scope: !2206)
!2206 = !DILexicalBlockFile(scope: !2207, file: !1, discriminator: 3)
!2207 = distinct !DILexicalBlock(scope: !2204, file: !1, line: 1239, column: 3)
!2208 = !DILocation(line: 1239, column: 3, scope: !2209)
!2209 = !DILexicalBlockFile(scope: !2210, file: !1, discriminator: 4)
!2210 = distinct !DILexicalBlock(scope: !2207, file: !1, line: 1239, column: 3)
!2211 = !DILocation(line: 1239, column: 3, scope: !2212)
!2212 = !DILexicalBlockFile(scope: !2207, file: !1, discriminator: 5)
!2213 = !DILocation(line: 1239, column: 3, scope: !2214)
!2214 = !DILexicalBlockFile(scope: !2215, file: !1, discriminator: 6)
!2215 = distinct !DILexicalBlock(scope: !2207, file: !1, line: 1239, column: 3)
!2216 = !DILocation(line: 1239, column: 3, scope: !2217)
!2217 = !DILexicalBlockFile(scope: !2218, file: !1, discriminator: 7)
!2218 = distinct !DILexicalBlock(scope: !2215, file: !1, line: 1239, column: 3)
!2219 = !DILocation(line: 1239, column: 3, scope: !2220)
!2220 = !DILexicalBlockFile(scope: !2215, file: !1, discriminator: 8)
!2221 = !DILocation(line: 1239, column: 3, scope: !2222)
!2222 = !DILexicalBlockFile(scope: !2207, file: !1, discriminator: 9)
!2223 = !DILocation(line: 1239, column: 3, scope: !2224)
!2224 = !DILexicalBlockFile(scope: !2207, file: !1, discriminator: 10)
!2225 = !DILocation(line: 1239, column: 3, scope: !2226)
!2226 = !DILexicalBlockFile(scope: !2201, file: !1, discriminator: 11)
!2227 = !DILocation(line: 1240, column: 3, scope: !459)
!2228 = !DILocation(line: 1240, column: 3, scope: !2229)
!2229 = !DILexicalBlockFile(scope: !2230, file: !1, discriminator: 1)
!2230 = distinct !DILexicalBlock(scope: !459, file: !1, line: 1240, column: 3)
!2231 = !DILocation(line: 1240, column: 3, scope: !2232)
!2232 = !DILexicalBlockFile(scope: !2230, file: !1, discriminator: 2)
!2233 = !DILocation(line: 1240, column: 3, scope: !2234)
!2234 = !DILexicalBlockFile(scope: !2230, file: !1, discriminator: 3)
!2235 = !DILocation(line: 1240, column: 3, scope: !2236)
!2236 = !DILexicalBlockFile(scope: !2230, file: !1, discriminator: 4)
!2237 = !DILocation(line: 1240, column: 3, scope: !2238)
!2238 = !DILexicalBlockFile(scope: !2239, file: !1, discriminator: 5)
!2239 = distinct !DILexicalBlock(scope: !2230, file: !1, line: 1240, column: 3)
!2240 = !DILocation(line: 1240, column: 3, scope: !2241)
!2241 = !DILexicalBlockFile(scope: !2242, file: !1, discriminator: 6)
!2242 = distinct !DILexicalBlock(scope: !2239, file: !1, line: 1240, column: 3)
!2243 = !DILocation(line: 1240, column: 3, scope: !2244)
!2244 = !DILexicalBlockFile(scope: !2245, file: !1, discriminator: 7)
!2245 = distinct !DILexicalBlock(scope: !2239, file: !1, line: 1240, column: 3)
!2246 = !DILocation(line: 1240, column: 3, scope: !2247)
!2247 = !DILexicalBlockFile(scope: !2248, file: !1, discriminator: 8)
!2248 = distinct !DILexicalBlock(scope: !2249, file: !1, line: 1240, column: 3)
!2249 = distinct !DILexicalBlock(scope: !2245, file: !1, line: 1240, column: 3)
!2250 = !DILocation(line: 1240, column: 3, scope: !2251)
!2251 = !DILexicalBlockFile(scope: !2252, file: !1, discriminator: 9)
!2252 = distinct !DILexicalBlock(scope: !2248, file: !1, line: 1240, column: 3)
!2253 = !DILocation(line: 1240, column: 3, scope: !2254)
!2254 = !DILexicalBlockFile(scope: !2252, file: !1, discriminator: 10)
!2255 = !DILocation(line: 1240, column: 3, scope: !2256)
!2256 = !DILexicalBlockFile(scope: !2252, file: !1, discriminator: 11)
!2257 = !DILocation(line: 1240, column: 3, scope: !2258)
!2258 = !DILexicalBlockFile(scope: !2252, file: !1, discriminator: 12)
!2259 = !DILocation(line: 1240, column: 3, scope: !2260)
!2260 = !DILexicalBlockFile(scope: !2252, file: !1, discriminator: 13)
!2261 = !DILocation(line: 1240, column: 3, scope: !2262)
!2262 = !DILexicalBlockFile(scope: !2263, file: !1, discriminator: 14)
!2263 = distinct !DILexicalBlock(scope: !2252, file: !1, line: 1240, column: 3)
!2264 = !DILocation(line: 1240, column: 3, scope: !2265)
!2265 = !DILexicalBlockFile(scope: !2252, file: !1, discriminator: 15)
!2266 = !DILocation(line: 1240, column: 3, scope: !2267)
!2267 = !DILexicalBlockFile(scope: !2248, file: !1, discriminator: 16)
!2268 = !DILocation(line: 1240, column: 3, scope: !2269)
!2269 = !DILexicalBlockFile(scope: !2230, file: !1, discriminator: 17)
!2270 = !DILocation(line: 1241, column: 3, scope: !459)
!2271 = !DILocation(line: 1241, column: 3, scope: !2272)
!2272 = !DILexicalBlockFile(scope: !2273, file: !1, discriminator: 1)
!2273 = distinct !DILexicalBlock(scope: !2274, file: !1, line: 1241, column: 3)
!2274 = distinct !DILexicalBlock(scope: !459, file: !1, line: 1241, column: 3)
!2275 = !DILocation(line: 1241, column: 3, scope: !2276)
!2276 = !DILexicalBlockFile(scope: !2277, file: !1, discriminator: 2)
!2277 = distinct !DILexicalBlock(scope: !2273, file: !1, line: 1241, column: 3)
!2278 = !DILocation(line: 1241, column: 3, scope: !2279)
!2279 = !DILexicalBlockFile(scope: !2280, file: !1, discriminator: 3)
!2280 = distinct !DILexicalBlock(scope: !2273, file: !1, line: 1241, column: 3)
!2281 = !DILocation(line: 1242, column: 1, scope: !459)
!2282 = !DILocalVariable(name: "loop", arg: 1, scope: !460, file: !1, line: 1245, type: !120)
!2283 = !DILocation(line: 1245, column: 31, scope: !460)
!2284 = !DILocalVariable(name: "req", arg: 2, scope: !460, file: !1, line: 1246, type: !105)
!2285 = !DILocation(line: 1246, column: 28, scope: !460)
!2286 = !DILocalVariable(name: "path", arg: 3, scope: !460, file: !1, line: 1247, type: !331)
!2287 = !DILocation(line: 1247, column: 32, scope: !460)
!2288 = !DILocalVariable(name: "cb", arg: 4, scope: !460, file: !1, line: 1248, type: !320)
!2289 = !DILocation(line: 1248, column: 28, scope: !460)
!2290 = !DILocation(line: 1249, column: 3, scope: !460)
!2291 = !DILocation(line: 1249, column: 3, scope: !2292)
!2292 = !DILexicalBlockFile(scope: !2293, file: !1, discriminator: 1)
!2293 = distinct !DILexicalBlock(scope: !460, file: !1, line: 1249, column: 3)
!2294 = !DILocation(line: 1249, column: 3, scope: !2295)
!2295 = !DILexicalBlockFile(scope: !2296, file: !1, discriminator: 2)
!2296 = distinct !DILexicalBlock(scope: !2293, file: !1, line: 1249, column: 3)
!2297 = !DILocation(line: 1249, column: 3, scope: !2298)
!2298 = !DILexicalBlockFile(scope: !2299, file: !1, discriminator: 3)
!2299 = distinct !DILexicalBlock(scope: !2296, file: !1, line: 1249, column: 3)
!2300 = !DILocation(line: 1249, column: 3, scope: !2301)
!2301 = !DILexicalBlockFile(scope: !2302, file: !1, discriminator: 4)
!2302 = distinct !DILexicalBlock(scope: !2299, file: !1, line: 1249, column: 3)
!2303 = !DILocation(line: 1249, column: 3, scope: !2304)
!2304 = !DILexicalBlockFile(scope: !2299, file: !1, discriminator: 5)
!2305 = !DILocation(line: 1249, column: 3, scope: !2306)
!2306 = !DILexicalBlockFile(scope: !2307, file: !1, discriminator: 6)
!2307 = distinct !DILexicalBlock(scope: !2299, file: !1, line: 1249, column: 3)
!2308 = !DILocation(line: 1249, column: 3, scope: !2309)
!2309 = !DILexicalBlockFile(scope: !2310, file: !1, discriminator: 7)
!2310 = distinct !DILexicalBlock(scope: !2307, file: !1, line: 1249, column: 3)
!2311 = !DILocation(line: 1249, column: 3, scope: !2312)
!2312 = !DILexicalBlockFile(scope: !2307, file: !1, discriminator: 8)
!2313 = !DILocation(line: 1249, column: 3, scope: !2314)
!2314 = !DILexicalBlockFile(scope: !2299, file: !1, discriminator: 9)
!2315 = !DILocation(line: 1249, column: 3, scope: !2316)
!2316 = !DILexicalBlockFile(scope: !2299, file: !1, discriminator: 10)
!2317 = !DILocation(line: 1249, column: 3, scope: !2318)
!2318 = !DILexicalBlockFile(scope: !2293, file: !1, discriminator: 11)
!2319 = !DILocation(line: 1250, column: 3, scope: !460)
!2320 = !DILocation(line: 1250, column: 3, scope: !2321)
!2321 = !DILexicalBlockFile(scope: !2322, file: !1, discriminator: 1)
!2322 = distinct !DILexicalBlock(scope: !460, file: !1, line: 1250, column: 3)
!2323 = !DILocation(line: 1250, column: 3, scope: !2324)
!2324 = !DILexicalBlockFile(scope: !2322, file: !1, discriminator: 2)
!2325 = !DILocation(line: 1250, column: 3, scope: !2326)
!2326 = !DILexicalBlockFile(scope: !2322, file: !1, discriminator: 3)
!2327 = !DILocation(line: 1250, column: 3, scope: !2328)
!2328 = !DILexicalBlockFile(scope: !2322, file: !1, discriminator: 4)
!2329 = !DILocation(line: 1250, column: 3, scope: !2330)
!2330 = !DILexicalBlockFile(scope: !2331, file: !1, discriminator: 5)
!2331 = distinct !DILexicalBlock(scope: !2322, file: !1, line: 1250, column: 3)
!2332 = !DILocation(line: 1250, column: 3, scope: !2333)
!2333 = !DILexicalBlockFile(scope: !2334, file: !1, discriminator: 6)
!2334 = distinct !DILexicalBlock(scope: !2331, file: !1, line: 1250, column: 3)
!2335 = !DILocation(line: 1250, column: 3, scope: !2336)
!2336 = !DILexicalBlockFile(scope: !2337, file: !1, discriminator: 7)
!2337 = distinct !DILexicalBlock(scope: !2331, file: !1, line: 1250, column: 3)
!2338 = !DILocation(line: 1250, column: 3, scope: !2339)
!2339 = !DILexicalBlockFile(scope: !2340, file: !1, discriminator: 8)
!2340 = distinct !DILexicalBlock(scope: !2341, file: !1, line: 1250, column: 3)
!2341 = distinct !DILexicalBlock(scope: !2337, file: !1, line: 1250, column: 3)
!2342 = !DILocation(line: 1250, column: 3, scope: !2343)
!2343 = !DILexicalBlockFile(scope: !2344, file: !1, discriminator: 9)
!2344 = distinct !DILexicalBlock(scope: !2340, file: !1, line: 1250, column: 3)
!2345 = !DILocation(line: 1250, column: 3, scope: !2346)
!2346 = !DILexicalBlockFile(scope: !2344, file: !1, discriminator: 10)
!2347 = !DILocation(line: 1250, column: 3, scope: !2348)
!2348 = !DILexicalBlockFile(scope: !2344, file: !1, discriminator: 11)
!2349 = !DILocation(line: 1250, column: 3, scope: !2350)
!2350 = !DILexicalBlockFile(scope: !2344, file: !1, discriminator: 12)
!2351 = !DILocation(line: 1250, column: 3, scope: !2352)
!2352 = !DILexicalBlockFile(scope: !2344, file: !1, discriminator: 13)
!2353 = !DILocation(line: 1250, column: 3, scope: !2354)
!2354 = !DILexicalBlockFile(scope: !2355, file: !1, discriminator: 14)
!2355 = distinct !DILexicalBlock(scope: !2344, file: !1, line: 1250, column: 3)
!2356 = !DILocation(line: 1250, column: 3, scope: !2357)
!2357 = !DILexicalBlockFile(scope: !2344, file: !1, discriminator: 15)
!2358 = !DILocation(line: 1250, column: 3, scope: !2359)
!2359 = !DILexicalBlockFile(scope: !2340, file: !1, discriminator: 16)
!2360 = !DILocation(line: 1250, column: 3, scope: !2361)
!2361 = !DILexicalBlockFile(scope: !2322, file: !1, discriminator: 17)
!2362 = !DILocation(line: 1251, column: 3, scope: !460)
!2363 = !DILocation(line: 1251, column: 3, scope: !2364)
!2364 = !DILexicalBlockFile(scope: !2365, file: !1, discriminator: 1)
!2365 = distinct !DILexicalBlock(scope: !2366, file: !1, line: 1251, column: 3)
!2366 = distinct !DILexicalBlock(scope: !460, file: !1, line: 1251, column: 3)
!2367 = !DILocation(line: 1251, column: 3, scope: !2368)
!2368 = !DILexicalBlockFile(scope: !2369, file: !1, discriminator: 2)
!2369 = distinct !DILexicalBlock(scope: !2365, file: !1, line: 1251, column: 3)
!2370 = !DILocation(line: 1251, column: 3, scope: !2371)
!2371 = !DILexicalBlockFile(scope: !2372, file: !1, discriminator: 3)
!2372 = distinct !DILexicalBlock(scope: !2365, file: !1, line: 1251, column: 3)
!2373 = !DILocation(line: 1252, column: 1, scope: !460)
!2374 = !DILocalVariable(name: "loop", arg: 1, scope: !461, file: !1, line: 1255, type: !120)
!2375 = !DILocation(line: 1255, column: 29, scope: !461)
!2376 = !DILocalVariable(name: "req", arg: 2, scope: !461, file: !1, line: 1256, type: !105)
!2377 = !DILocation(line: 1256, column: 27, scope: !461)
!2378 = !DILocalVariable(name: "path", arg: 3, scope: !461, file: !1, line: 1257, type: !331)
!2379 = !DILocation(line: 1257, column: 30, scope: !461)
!2380 = !DILocalVariable(name: "new_path", arg: 4, scope: !461, file: !1, line: 1258, type: !331)
!2381 = !DILocation(line: 1258, column: 30, scope: !461)
!2382 = !DILocalVariable(name: "cb", arg: 5, scope: !461, file: !1, line: 1259, type: !320)
!2383 = !DILocation(line: 1259, column: 27, scope: !461)
!2384 = !DILocation(line: 1260, column: 3, scope: !461)
!2385 = !DILocation(line: 1260, column: 3, scope: !2386)
!2386 = !DILexicalBlockFile(scope: !2387, file: !1, discriminator: 1)
!2387 = distinct !DILexicalBlock(scope: !461, file: !1, line: 1260, column: 3)
!2388 = !DILocation(line: 1260, column: 3, scope: !2389)
!2389 = !DILexicalBlockFile(scope: !2390, file: !1, discriminator: 2)
!2390 = distinct !DILexicalBlock(scope: !2387, file: !1, line: 1260, column: 3)
!2391 = !DILocation(line: 1260, column: 3, scope: !2392)
!2392 = !DILexicalBlockFile(scope: !2393, file: !1, discriminator: 3)
!2393 = distinct !DILexicalBlock(scope: !2390, file: !1, line: 1260, column: 3)
!2394 = !DILocation(line: 1260, column: 3, scope: !2395)
!2395 = !DILexicalBlockFile(scope: !2396, file: !1, discriminator: 4)
!2396 = distinct !DILexicalBlock(scope: !2393, file: !1, line: 1260, column: 3)
!2397 = !DILocation(line: 1260, column: 3, scope: !2398)
!2398 = !DILexicalBlockFile(scope: !2393, file: !1, discriminator: 5)
!2399 = !DILocation(line: 1260, column: 3, scope: !2400)
!2400 = !DILexicalBlockFile(scope: !2401, file: !1, discriminator: 6)
!2401 = distinct !DILexicalBlock(scope: !2393, file: !1, line: 1260, column: 3)
!2402 = !DILocation(line: 1260, column: 3, scope: !2403)
!2403 = !DILexicalBlockFile(scope: !2404, file: !1, discriminator: 7)
!2404 = distinct !DILexicalBlock(scope: !2401, file: !1, line: 1260, column: 3)
!2405 = !DILocation(line: 1260, column: 3, scope: !2406)
!2406 = !DILexicalBlockFile(scope: !2401, file: !1, discriminator: 8)
!2407 = !DILocation(line: 1260, column: 3, scope: !2408)
!2408 = !DILexicalBlockFile(scope: !2393, file: !1, discriminator: 9)
!2409 = !DILocation(line: 1260, column: 3, scope: !2410)
!2410 = !DILexicalBlockFile(scope: !2393, file: !1, discriminator: 10)
!2411 = !DILocation(line: 1260, column: 3, scope: !2412)
!2412 = !DILexicalBlockFile(scope: !2387, file: !1, discriminator: 11)
!2413 = !DILocation(line: 1261, column: 3, scope: !461)
!2414 = !DILocation(line: 1261, column: 3, scope: !2415)
!2415 = !DILexicalBlockFile(scope: !2416, file: !1, discriminator: 1)
!2416 = distinct !DILexicalBlock(scope: !2417, file: !1, line: 1261, column: 3)
!2417 = distinct !DILexicalBlock(scope: !461, file: !1, line: 1261, column: 3)
!2418 = !DILocation(line: 1261, column: 3, scope: !2419)
!2419 = !DILexicalBlockFile(scope: !2420, file: !1, discriminator: 2)
!2420 = distinct !DILexicalBlock(scope: !2416, file: !1, line: 1261, column: 3)
!2421 = !DILocalVariable(name: "path_len", scope: !2422, file: !1, line: 1261, type: !375)
!2422 = distinct !DILexicalBlock(scope: !2416, file: !1, line: 1261, column: 3)
!2423 = !DILocation(line: 1261, column: 3, scope: !2422)
!2424 = !DILocalVariable(name: "new_path_len", scope: !2422, file: !1, line: 1261, type: !375)
!2425 = !DILocation(line: 1261, column: 3, scope: !2426)
!2426 = !DILexicalBlockFile(scope: !2422, file: !1, discriminator: 3)
!2427 = !DILocation(line: 1261, column: 3, scope: !2428)
!2428 = !DILexicalBlockFile(scope: !2426, file: !1, discriminator: 15)
!2429 = !DILocation(line: 1261, column: 3, scope: !2430)
!2430 = !DILexicalBlockFile(scope: !2426, file: !1, discriminator: 16)
!2431 = !DILocation(line: 1261, column: 3, scope: !2432)
!2432 = !DILexicalBlockFile(scope: !2433, file: !1, discriminator: 4)
!2433 = distinct !DILexicalBlock(scope: !2434, file: !1, line: 1261, column: 3)
!2434 = distinct !DILexicalBlock(scope: !2422, file: !1, line: 1261, column: 3)
!2435 = !DILocation(line: 1261, column: 3, scope: !2436)
!2436 = !DILexicalBlockFile(scope: !2437, file: !1, discriminator: 5)
!2437 = distinct !DILexicalBlock(scope: !2433, file: !1, line: 1261, column: 3)
!2438 = !DILocation(line: 1261, column: 3, scope: !2439)
!2439 = !DILexicalBlockFile(scope: !2437, file: !1, discriminator: 6)
!2440 = !DILocation(line: 1261, column: 3, scope: !2441)
!2441 = !DILexicalBlockFile(scope: !2437, file: !1, discriminator: 7)
!2442 = !DILocation(line: 1261, column: 3, scope: !2443)
!2443 = !DILexicalBlockFile(scope: !2437, file: !1, discriminator: 8)
!2444 = !DILocation(line: 1261, column: 3, scope: !2445)
!2445 = !DILexicalBlockFile(scope: !2437, file: !1, discriminator: 9)
!2446 = !DILocation(line: 1261, column: 3, scope: !2447)
!2447 = !DILexicalBlockFile(scope: !2448, file: !1, discriminator: 10)
!2448 = distinct !DILexicalBlock(scope: !2437, file: !1, line: 1261, column: 3)
!2449 = !DILocation(line: 1261, column: 3, scope: !2450)
!2450 = !DILexicalBlockFile(scope: !2437, file: !1, discriminator: 11)
!2451 = !DILocation(line: 1261, column: 3, scope: !2452)
!2452 = !DILexicalBlockFile(scope: !2433, file: !1, discriminator: 12)
!2453 = !DILocation(line: 1261, column: 3, scope: !2454)
!2454 = !DILexicalBlockFile(scope: !2422, file: !1, discriminator: 13)
!2455 = !DILocation(line: 1261, column: 3, scope: !2456)
!2456 = !DILexicalBlockFile(scope: !2454, file: !1, discriminator: 17)
!2457 = !DILocation(line: 1261, column: 3, scope: !2458)
!2458 = !DILexicalBlockFile(scope: !2417, file: !1, discriminator: 14)
!2459 = !DILocation(line: 1262, column: 3, scope: !461)
!2460 = !DILocation(line: 1262, column: 3, scope: !2461)
!2461 = !DILexicalBlockFile(scope: !2462, file: !1, discriminator: 1)
!2462 = distinct !DILexicalBlock(scope: !2463, file: !1, line: 1262, column: 3)
!2463 = distinct !DILexicalBlock(scope: !461, file: !1, line: 1262, column: 3)
!2464 = !DILocation(line: 1262, column: 3, scope: !2465)
!2465 = !DILexicalBlockFile(scope: !2466, file: !1, discriminator: 2)
!2466 = distinct !DILexicalBlock(scope: !2462, file: !1, line: 1262, column: 3)
!2467 = !DILocation(line: 1262, column: 3, scope: !2468)
!2468 = !DILexicalBlockFile(scope: !2469, file: !1, discriminator: 3)
!2469 = distinct !DILexicalBlock(scope: !2462, file: !1, line: 1262, column: 3)
!2470 = !DILocation(line: 1263, column: 1, scope: !461)
!2471 = !DILocalVariable(name: "loop", arg: 1, scope: !462, file: !1, line: 1266, type: !120)
!2472 = !DILocation(line: 1266, column: 28, scope: !462)
!2473 = !DILocalVariable(name: "req", arg: 2, scope: !462, file: !1, line: 1266, type: !105)
!2474 = !DILocation(line: 1266, column: 43, scope: !462)
!2475 = !DILocalVariable(name: "path", arg: 3, scope: !462, file: !1, line: 1266, type: !331)
!2476 = !DILocation(line: 1266, column: 60, scope: !462)
!2477 = !DILocalVariable(name: "cb", arg: 4, scope: !462, file: !1, line: 1266, type: !320)
!2478 = !DILocation(line: 1266, column: 75, scope: !462)
!2479 = !DILocation(line: 1267, column: 3, scope: !462)
!2480 = !DILocation(line: 1267, column: 3, scope: !2481)
!2481 = !DILexicalBlockFile(scope: !2482, file: !1, discriminator: 1)
!2482 = distinct !DILexicalBlock(scope: !462, file: !1, line: 1267, column: 3)
!2483 = !DILocation(line: 1267, column: 3, scope: !2484)
!2484 = !DILexicalBlockFile(scope: !2485, file: !1, discriminator: 2)
!2485 = distinct !DILexicalBlock(scope: !2482, file: !1, line: 1267, column: 3)
!2486 = !DILocation(line: 1267, column: 3, scope: !2487)
!2487 = !DILexicalBlockFile(scope: !2488, file: !1, discriminator: 3)
!2488 = distinct !DILexicalBlock(scope: !2485, file: !1, line: 1267, column: 3)
!2489 = !DILocation(line: 1267, column: 3, scope: !2490)
!2490 = !DILexicalBlockFile(scope: !2491, file: !1, discriminator: 4)
!2491 = distinct !DILexicalBlock(scope: !2488, file: !1, line: 1267, column: 3)
!2492 = !DILocation(line: 1267, column: 3, scope: !2493)
!2493 = !DILexicalBlockFile(scope: !2488, file: !1, discriminator: 5)
!2494 = !DILocation(line: 1267, column: 3, scope: !2495)
!2495 = !DILexicalBlockFile(scope: !2496, file: !1, discriminator: 6)
!2496 = distinct !DILexicalBlock(scope: !2488, file: !1, line: 1267, column: 3)
!2497 = !DILocation(line: 1267, column: 3, scope: !2498)
!2498 = !DILexicalBlockFile(scope: !2499, file: !1, discriminator: 7)
!2499 = distinct !DILexicalBlock(scope: !2496, file: !1, line: 1267, column: 3)
!2500 = !DILocation(line: 1267, column: 3, scope: !2501)
!2501 = !DILexicalBlockFile(scope: !2496, file: !1, discriminator: 8)
!2502 = !DILocation(line: 1267, column: 3, scope: !2503)
!2503 = !DILexicalBlockFile(scope: !2488, file: !1, discriminator: 9)
!2504 = !DILocation(line: 1267, column: 3, scope: !2505)
!2505 = !DILexicalBlockFile(scope: !2488, file: !1, discriminator: 10)
!2506 = !DILocation(line: 1267, column: 3, scope: !2507)
!2507 = !DILexicalBlockFile(scope: !2482, file: !1, discriminator: 11)
!2508 = !DILocation(line: 1268, column: 3, scope: !462)
!2509 = !DILocation(line: 1268, column: 3, scope: !2510)
!2510 = !DILexicalBlockFile(scope: !2511, file: !1, discriminator: 1)
!2511 = distinct !DILexicalBlock(scope: !462, file: !1, line: 1268, column: 3)
!2512 = !DILocation(line: 1268, column: 3, scope: !2513)
!2513 = !DILexicalBlockFile(scope: !2511, file: !1, discriminator: 2)
!2514 = !DILocation(line: 1268, column: 3, scope: !2515)
!2515 = !DILexicalBlockFile(scope: !2511, file: !1, discriminator: 3)
!2516 = !DILocation(line: 1268, column: 3, scope: !2517)
!2517 = !DILexicalBlockFile(scope: !2511, file: !1, discriminator: 4)
!2518 = !DILocation(line: 1268, column: 3, scope: !2519)
!2519 = !DILexicalBlockFile(scope: !2520, file: !1, discriminator: 5)
!2520 = distinct !DILexicalBlock(scope: !2511, file: !1, line: 1268, column: 3)
!2521 = !DILocation(line: 1268, column: 3, scope: !2522)
!2522 = !DILexicalBlockFile(scope: !2523, file: !1, discriminator: 6)
!2523 = distinct !DILexicalBlock(scope: !2520, file: !1, line: 1268, column: 3)
!2524 = !DILocation(line: 1268, column: 3, scope: !2525)
!2525 = !DILexicalBlockFile(scope: !2526, file: !1, discriminator: 7)
!2526 = distinct !DILexicalBlock(scope: !2520, file: !1, line: 1268, column: 3)
!2527 = !DILocation(line: 1268, column: 3, scope: !2528)
!2528 = !DILexicalBlockFile(scope: !2529, file: !1, discriminator: 8)
!2529 = distinct !DILexicalBlock(scope: !2530, file: !1, line: 1268, column: 3)
!2530 = distinct !DILexicalBlock(scope: !2526, file: !1, line: 1268, column: 3)
!2531 = !DILocation(line: 1268, column: 3, scope: !2532)
!2532 = !DILexicalBlockFile(scope: !2533, file: !1, discriminator: 9)
!2533 = distinct !DILexicalBlock(scope: !2529, file: !1, line: 1268, column: 3)
!2534 = !DILocation(line: 1268, column: 3, scope: !2535)
!2535 = !DILexicalBlockFile(scope: !2533, file: !1, discriminator: 10)
!2536 = !DILocation(line: 1268, column: 3, scope: !2537)
!2537 = !DILexicalBlockFile(scope: !2533, file: !1, discriminator: 11)
!2538 = !DILocation(line: 1268, column: 3, scope: !2539)
!2539 = !DILexicalBlockFile(scope: !2533, file: !1, discriminator: 12)
!2540 = !DILocation(line: 1268, column: 3, scope: !2541)
!2541 = !DILexicalBlockFile(scope: !2533, file: !1, discriminator: 13)
!2542 = !DILocation(line: 1268, column: 3, scope: !2543)
!2543 = !DILexicalBlockFile(scope: !2544, file: !1, discriminator: 14)
!2544 = distinct !DILexicalBlock(scope: !2533, file: !1, line: 1268, column: 3)
!2545 = !DILocation(line: 1268, column: 3, scope: !2546)
!2546 = !DILexicalBlockFile(scope: !2533, file: !1, discriminator: 15)
!2547 = !DILocation(line: 1268, column: 3, scope: !2548)
!2548 = !DILexicalBlockFile(scope: !2529, file: !1, discriminator: 16)
!2549 = !DILocation(line: 1268, column: 3, scope: !2550)
!2550 = !DILexicalBlockFile(scope: !2511, file: !1, discriminator: 17)
!2551 = !DILocation(line: 1269, column: 3, scope: !462)
!2552 = !DILocation(line: 1269, column: 3, scope: !2553)
!2553 = !DILexicalBlockFile(scope: !2554, file: !1, discriminator: 1)
!2554 = distinct !DILexicalBlock(scope: !2555, file: !1, line: 1269, column: 3)
!2555 = distinct !DILexicalBlock(scope: !462, file: !1, line: 1269, column: 3)
!2556 = !DILocation(line: 1269, column: 3, scope: !2557)
!2557 = !DILexicalBlockFile(scope: !2558, file: !1, discriminator: 2)
!2558 = distinct !DILexicalBlock(scope: !2554, file: !1, line: 1269, column: 3)
!2559 = !DILocation(line: 1269, column: 3, scope: !2560)
!2560 = !DILexicalBlockFile(scope: !2561, file: !1, discriminator: 3)
!2561 = distinct !DILexicalBlock(scope: !2554, file: !1, line: 1269, column: 3)
!2562 = !DILocation(line: 1270, column: 1, scope: !462)
!2563 = !DILocalVariable(name: "loop", arg: 1, scope: !463, file: !1, line: 1273, type: !120)
!2564 = !DILocation(line: 1273, column: 31, scope: !463)
!2565 = !DILocalVariable(name: "req", arg: 2, scope: !463, file: !1, line: 1274, type: !105)
!2566 = !DILocation(line: 1274, column: 29, scope: !463)
!2567 = !DILocalVariable(name: "out_fd", arg: 3, scope: !463, file: !1, line: 1275, type: !360)
!2568 = !DILocation(line: 1275, column: 28, scope: !463)
!2569 = !DILocalVariable(name: "in_fd", arg: 4, scope: !463, file: !1, line: 1276, type: !360)
!2570 = !DILocation(line: 1276, column: 28, scope: !463)
!2571 = !DILocalVariable(name: "off", arg: 5, scope: !463, file: !1, line: 1277, type: !438)
!2572 = !DILocation(line: 1277, column: 28, scope: !463)
!2573 = !DILocalVariable(name: "len", arg: 6, scope: !463, file: !1, line: 1278, type: !375)
!2574 = !DILocation(line: 1278, column: 27, scope: !463)
!2575 = !DILocalVariable(name: "cb", arg: 7, scope: !463, file: !1, line: 1279, type: !320)
!2576 = !DILocation(line: 1279, column: 29, scope: !463)
!2577 = !DILocation(line: 1280, column: 3, scope: !463)
!2578 = !DILocation(line: 1280, column: 3, scope: !2579)
!2579 = !DILexicalBlockFile(scope: !2580, file: !1, discriminator: 1)
!2580 = distinct !DILexicalBlock(scope: !463, file: !1, line: 1280, column: 3)
!2581 = !DILocation(line: 1280, column: 3, scope: !2582)
!2582 = !DILexicalBlockFile(scope: !2583, file: !1, discriminator: 2)
!2583 = distinct !DILexicalBlock(scope: !2580, file: !1, line: 1280, column: 3)
!2584 = !DILocation(line: 1280, column: 3, scope: !2585)
!2585 = !DILexicalBlockFile(scope: !2586, file: !1, discriminator: 3)
!2586 = distinct !DILexicalBlock(scope: !2583, file: !1, line: 1280, column: 3)
!2587 = !DILocation(line: 1280, column: 3, scope: !2588)
!2588 = !DILexicalBlockFile(scope: !2589, file: !1, discriminator: 4)
!2589 = distinct !DILexicalBlock(scope: !2586, file: !1, line: 1280, column: 3)
!2590 = !DILocation(line: 1280, column: 3, scope: !2591)
!2591 = !DILexicalBlockFile(scope: !2586, file: !1, discriminator: 5)
!2592 = !DILocation(line: 1280, column: 3, scope: !2593)
!2593 = !DILexicalBlockFile(scope: !2594, file: !1, discriminator: 6)
!2594 = distinct !DILexicalBlock(scope: !2586, file: !1, line: 1280, column: 3)
!2595 = !DILocation(line: 1280, column: 3, scope: !2596)
!2596 = !DILexicalBlockFile(scope: !2597, file: !1, discriminator: 7)
!2597 = distinct !DILexicalBlock(scope: !2594, file: !1, line: 1280, column: 3)
!2598 = !DILocation(line: 1280, column: 3, scope: !2599)
!2599 = !DILexicalBlockFile(scope: !2594, file: !1, discriminator: 8)
!2600 = !DILocation(line: 1280, column: 3, scope: !2601)
!2601 = !DILexicalBlockFile(scope: !2586, file: !1, discriminator: 9)
!2602 = !DILocation(line: 1280, column: 3, scope: !2603)
!2603 = !DILexicalBlockFile(scope: !2586, file: !1, discriminator: 10)
!2604 = !DILocation(line: 1280, column: 3, scope: !2605)
!2605 = !DILexicalBlockFile(scope: !2580, file: !1, discriminator: 11)
!2606 = !DILocation(line: 1281, column: 16, scope: !463)
!2607 = !DILocation(line: 1281, column: 3, scope: !463)
!2608 = !DILocation(line: 1281, column: 8, scope: !463)
!2609 = !DILocation(line: 1281, column: 14, scope: !463)
!2610 = !DILocation(line: 1282, column: 15, scope: !463)
!2611 = !DILocation(line: 1282, column: 3, scope: !463)
!2612 = !DILocation(line: 1282, column: 8, scope: !463)
!2613 = !DILocation(line: 1282, column: 13, scope: !463)
!2614 = !DILocation(line: 1283, column: 14, scope: !463)
!2615 = !DILocation(line: 1283, column: 3, scope: !463)
!2616 = !DILocation(line: 1283, column: 8, scope: !463)
!2617 = !DILocation(line: 1283, column: 12, scope: !463)
!2618 = !DILocation(line: 1284, column: 24, scope: !463)
!2619 = !DILocation(line: 1284, column: 3, scope: !463)
!2620 = !DILocation(line: 1284, column: 8, scope: !463)
!2621 = !DILocation(line: 1284, column: 18, scope: !463)
!2622 = !DILocation(line: 1284, column: 22, scope: !463)
!2623 = !DILocation(line: 1285, column: 3, scope: !463)
!2624 = !DILocation(line: 1285, column: 3, scope: !2625)
!2625 = !DILexicalBlockFile(scope: !2626, file: !1, discriminator: 1)
!2626 = distinct !DILexicalBlock(scope: !2627, file: !1, line: 1285, column: 3)
!2627 = distinct !DILexicalBlock(scope: !463, file: !1, line: 1285, column: 3)
!2628 = !DILocation(line: 1285, column: 3, scope: !2629)
!2629 = !DILexicalBlockFile(scope: !2630, file: !1, discriminator: 2)
!2630 = distinct !DILexicalBlock(scope: !2626, file: !1, line: 1285, column: 3)
!2631 = !DILocation(line: 1285, column: 3, scope: !2632)
!2632 = !DILexicalBlockFile(scope: !2633, file: !1, discriminator: 3)
!2633 = distinct !DILexicalBlock(scope: !2626, file: !1, line: 1285, column: 3)
!2634 = !DILocation(line: 1286, column: 1, scope: !463)
!2635 = !DILocalVariable(name: "loop", arg: 1, scope: !466, file: !1, line: 1289, type: !120)
!2636 = !DILocation(line: 1289, column: 27, scope: !466)
!2637 = !DILocalVariable(name: "req", arg: 2, scope: !466, file: !1, line: 1289, type: !105)
!2638 = !DILocation(line: 1289, column: 42, scope: !466)
!2639 = !DILocalVariable(name: "path", arg: 3, scope: !466, file: !1, line: 1289, type: !331)
!2640 = !DILocation(line: 1289, column: 59, scope: !466)
!2641 = !DILocalVariable(name: "cb", arg: 4, scope: !466, file: !1, line: 1289, type: !320)
!2642 = !DILocation(line: 1289, column: 74, scope: !466)
!2643 = !DILocation(line: 1290, column: 3, scope: !466)
!2644 = !DILocation(line: 1290, column: 3, scope: !2645)
!2645 = !DILexicalBlockFile(scope: !2646, file: !1, discriminator: 1)
!2646 = distinct !DILexicalBlock(scope: !466, file: !1, line: 1290, column: 3)
!2647 = !DILocation(line: 1290, column: 3, scope: !2648)
!2648 = !DILexicalBlockFile(scope: !2649, file: !1, discriminator: 2)
!2649 = distinct !DILexicalBlock(scope: !2646, file: !1, line: 1290, column: 3)
!2650 = !DILocation(line: 1290, column: 3, scope: !2651)
!2651 = !DILexicalBlockFile(scope: !2652, file: !1, discriminator: 3)
!2652 = distinct !DILexicalBlock(scope: !2649, file: !1, line: 1290, column: 3)
!2653 = !DILocation(line: 1290, column: 3, scope: !2654)
!2654 = !DILexicalBlockFile(scope: !2655, file: !1, discriminator: 4)
!2655 = distinct !DILexicalBlock(scope: !2652, file: !1, line: 1290, column: 3)
!2656 = !DILocation(line: 1290, column: 3, scope: !2657)
!2657 = !DILexicalBlockFile(scope: !2652, file: !1, discriminator: 5)
!2658 = !DILocation(line: 1290, column: 3, scope: !2659)
!2659 = !DILexicalBlockFile(scope: !2660, file: !1, discriminator: 6)
!2660 = distinct !DILexicalBlock(scope: !2652, file: !1, line: 1290, column: 3)
!2661 = !DILocation(line: 1290, column: 3, scope: !2662)
!2662 = !DILexicalBlockFile(scope: !2663, file: !1, discriminator: 7)
!2663 = distinct !DILexicalBlock(scope: !2660, file: !1, line: 1290, column: 3)
!2664 = !DILocation(line: 1290, column: 3, scope: !2665)
!2665 = !DILexicalBlockFile(scope: !2660, file: !1, discriminator: 8)
!2666 = !DILocation(line: 1290, column: 3, scope: !2667)
!2667 = !DILexicalBlockFile(scope: !2652, file: !1, discriminator: 9)
!2668 = !DILocation(line: 1290, column: 3, scope: !2669)
!2669 = !DILexicalBlockFile(scope: !2652, file: !1, discriminator: 10)
!2670 = !DILocation(line: 1290, column: 3, scope: !2671)
!2671 = !DILexicalBlockFile(scope: !2646, file: !1, discriminator: 11)
!2672 = !DILocation(line: 1291, column: 3, scope: !466)
!2673 = !DILocation(line: 1291, column: 3, scope: !2674)
!2674 = !DILexicalBlockFile(scope: !2675, file: !1, discriminator: 1)
!2675 = distinct !DILexicalBlock(scope: !466, file: !1, line: 1291, column: 3)
!2676 = !DILocation(line: 1291, column: 3, scope: !2677)
!2677 = !DILexicalBlockFile(scope: !2675, file: !1, discriminator: 2)
!2678 = !DILocation(line: 1291, column: 3, scope: !2679)
!2679 = !DILexicalBlockFile(scope: !2675, file: !1, discriminator: 3)
!2680 = !DILocation(line: 1291, column: 3, scope: !2681)
!2681 = !DILexicalBlockFile(scope: !2675, file: !1, discriminator: 4)
!2682 = !DILocation(line: 1291, column: 3, scope: !2683)
!2683 = !DILexicalBlockFile(scope: !2684, file: !1, discriminator: 5)
!2684 = distinct !DILexicalBlock(scope: !2675, file: !1, line: 1291, column: 3)
!2685 = !DILocation(line: 1291, column: 3, scope: !2686)
!2686 = !DILexicalBlockFile(scope: !2687, file: !1, discriminator: 6)
!2687 = distinct !DILexicalBlock(scope: !2684, file: !1, line: 1291, column: 3)
!2688 = !DILocation(line: 1291, column: 3, scope: !2689)
!2689 = !DILexicalBlockFile(scope: !2690, file: !1, discriminator: 7)
!2690 = distinct !DILexicalBlock(scope: !2684, file: !1, line: 1291, column: 3)
!2691 = !DILocation(line: 1291, column: 3, scope: !2692)
!2692 = !DILexicalBlockFile(scope: !2693, file: !1, discriminator: 8)
!2693 = distinct !DILexicalBlock(scope: !2694, file: !1, line: 1291, column: 3)
!2694 = distinct !DILexicalBlock(scope: !2690, file: !1, line: 1291, column: 3)
!2695 = !DILocation(line: 1291, column: 3, scope: !2696)
!2696 = !DILexicalBlockFile(scope: !2697, file: !1, discriminator: 9)
!2697 = distinct !DILexicalBlock(scope: !2693, file: !1, line: 1291, column: 3)
!2698 = !DILocation(line: 1291, column: 3, scope: !2699)
!2699 = !DILexicalBlockFile(scope: !2697, file: !1, discriminator: 10)
!2700 = !DILocation(line: 1291, column: 3, scope: !2701)
!2701 = !DILexicalBlockFile(scope: !2697, file: !1, discriminator: 11)
!2702 = !DILocation(line: 1291, column: 3, scope: !2703)
!2703 = !DILexicalBlockFile(scope: !2697, file: !1, discriminator: 12)
!2704 = !DILocation(line: 1291, column: 3, scope: !2705)
!2705 = !DILexicalBlockFile(scope: !2697, file: !1, discriminator: 13)
!2706 = !DILocation(line: 1291, column: 3, scope: !2707)
!2707 = !DILexicalBlockFile(scope: !2708, file: !1, discriminator: 14)
!2708 = distinct !DILexicalBlock(scope: !2697, file: !1, line: 1291, column: 3)
!2709 = !DILocation(line: 1291, column: 3, scope: !2710)
!2710 = !DILexicalBlockFile(scope: !2697, file: !1, discriminator: 15)
!2711 = !DILocation(line: 1291, column: 3, scope: !2712)
!2712 = !DILexicalBlockFile(scope: !2693, file: !1, discriminator: 16)
!2713 = !DILocation(line: 1291, column: 3, scope: !2714)
!2714 = !DILexicalBlockFile(scope: !2675, file: !1, discriminator: 17)
!2715 = !DILocation(line: 1292, column: 3, scope: !466)
!2716 = !DILocation(line: 1292, column: 3, scope: !2717)
!2717 = !DILexicalBlockFile(scope: !2718, file: !1, discriminator: 1)
!2718 = distinct !DILexicalBlock(scope: !2719, file: !1, line: 1292, column: 3)
!2719 = distinct !DILexicalBlock(scope: !466, file: !1, line: 1292, column: 3)
!2720 = !DILocation(line: 1292, column: 3, scope: !2721)
!2721 = !DILexicalBlockFile(scope: !2722, file: !1, discriminator: 2)
!2722 = distinct !DILexicalBlock(scope: !2718, file: !1, line: 1292, column: 3)
!2723 = !DILocation(line: 1292, column: 3, scope: !2724)
!2724 = !DILexicalBlockFile(scope: !2725, file: !1, discriminator: 3)
!2725 = distinct !DILexicalBlock(scope: !2718, file: !1, line: 1292, column: 3)
!2726 = !DILocation(line: 1293, column: 1, scope: !466)
!2727 = !DILocalVariable(name: "loop", arg: 1, scope: !467, file: !1, line: 1296, type: !120)
!2728 = !DILocation(line: 1296, column: 30, scope: !467)
!2729 = !DILocalVariable(name: "req", arg: 2, scope: !467, file: !1, line: 1297, type: !105)
!2730 = !DILocation(line: 1297, column: 28, scope: !467)
!2731 = !DILocalVariable(name: "path", arg: 3, scope: !467, file: !1, line: 1298, type: !331)
!2732 = !DILocation(line: 1298, column: 31, scope: !467)
!2733 = !DILocalVariable(name: "new_path", arg: 4, scope: !467, file: !1, line: 1299, type: !331)
!2734 = !DILocation(line: 1299, column: 31, scope: !467)
!2735 = !DILocalVariable(name: "flags", arg: 5, scope: !467, file: !1, line: 1300, type: !133)
!2736 = !DILocation(line: 1300, column: 23, scope: !467)
!2737 = !DILocalVariable(name: "cb", arg: 6, scope: !467, file: !1, line: 1301, type: !320)
!2738 = !DILocation(line: 1301, column: 28, scope: !467)
!2739 = !DILocation(line: 1302, column: 3, scope: !467)
!2740 = !DILocation(line: 1302, column: 3, scope: !2741)
!2741 = !DILexicalBlockFile(scope: !2742, file: !1, discriminator: 1)
!2742 = distinct !DILexicalBlock(scope: !467, file: !1, line: 1302, column: 3)
!2743 = !DILocation(line: 1302, column: 3, scope: !2744)
!2744 = !DILexicalBlockFile(scope: !2745, file: !1, discriminator: 2)
!2745 = distinct !DILexicalBlock(scope: !2742, file: !1, line: 1302, column: 3)
!2746 = !DILocation(line: 1302, column: 3, scope: !2747)
!2747 = !DILexicalBlockFile(scope: !2748, file: !1, discriminator: 3)
!2748 = distinct !DILexicalBlock(scope: !2745, file: !1, line: 1302, column: 3)
!2749 = !DILocation(line: 1302, column: 3, scope: !2750)
!2750 = !DILexicalBlockFile(scope: !2751, file: !1, discriminator: 4)
!2751 = distinct !DILexicalBlock(scope: !2748, file: !1, line: 1302, column: 3)
!2752 = !DILocation(line: 1302, column: 3, scope: !2753)
!2753 = !DILexicalBlockFile(scope: !2748, file: !1, discriminator: 5)
!2754 = !DILocation(line: 1302, column: 3, scope: !2755)
!2755 = !DILexicalBlockFile(scope: !2756, file: !1, discriminator: 6)
!2756 = distinct !DILexicalBlock(scope: !2748, file: !1, line: 1302, column: 3)
!2757 = !DILocation(line: 1302, column: 3, scope: !2758)
!2758 = !DILexicalBlockFile(scope: !2759, file: !1, discriminator: 7)
!2759 = distinct !DILexicalBlock(scope: !2756, file: !1, line: 1302, column: 3)
!2760 = !DILocation(line: 1302, column: 3, scope: !2761)
!2761 = !DILexicalBlockFile(scope: !2756, file: !1, discriminator: 8)
!2762 = !DILocation(line: 1302, column: 3, scope: !2763)
!2763 = !DILexicalBlockFile(scope: !2748, file: !1, discriminator: 9)
!2764 = !DILocation(line: 1302, column: 3, scope: !2765)
!2765 = !DILexicalBlockFile(scope: !2748, file: !1, discriminator: 10)
!2766 = !DILocation(line: 1302, column: 3, scope: !2767)
!2767 = !DILexicalBlockFile(scope: !2742, file: !1, discriminator: 11)
!2768 = !DILocation(line: 1303, column: 3, scope: !467)
!2769 = !DILocation(line: 1303, column: 3, scope: !2770)
!2770 = !DILexicalBlockFile(scope: !2771, file: !1, discriminator: 1)
!2771 = distinct !DILexicalBlock(scope: !2772, file: !1, line: 1303, column: 3)
!2772 = distinct !DILexicalBlock(scope: !467, file: !1, line: 1303, column: 3)
!2773 = !DILocation(line: 1303, column: 3, scope: !2774)
!2774 = !DILexicalBlockFile(scope: !2775, file: !1, discriminator: 2)
!2775 = distinct !DILexicalBlock(scope: !2771, file: !1, line: 1303, column: 3)
!2776 = !DILocalVariable(name: "path_len", scope: !2777, file: !1, line: 1303, type: !375)
!2777 = distinct !DILexicalBlock(scope: !2771, file: !1, line: 1303, column: 3)
!2778 = !DILocation(line: 1303, column: 3, scope: !2777)
!2779 = !DILocalVariable(name: "new_path_len", scope: !2777, file: !1, line: 1303, type: !375)
!2780 = !DILocation(line: 1303, column: 3, scope: !2781)
!2781 = !DILexicalBlockFile(scope: !2777, file: !1, discriminator: 3)
!2782 = !DILocation(line: 1303, column: 3, scope: !2783)
!2783 = !DILexicalBlockFile(scope: !2781, file: !1, discriminator: 15)
!2784 = !DILocation(line: 1303, column: 3, scope: !2785)
!2785 = !DILexicalBlockFile(scope: !2781, file: !1, discriminator: 16)
!2786 = !DILocation(line: 1303, column: 3, scope: !2787)
!2787 = !DILexicalBlockFile(scope: !2788, file: !1, discriminator: 4)
!2788 = distinct !DILexicalBlock(scope: !2789, file: !1, line: 1303, column: 3)
!2789 = distinct !DILexicalBlock(scope: !2777, file: !1, line: 1303, column: 3)
!2790 = !DILocation(line: 1303, column: 3, scope: !2791)
!2791 = !DILexicalBlockFile(scope: !2792, file: !1, discriminator: 5)
!2792 = distinct !DILexicalBlock(scope: !2788, file: !1, line: 1303, column: 3)
!2793 = !DILocation(line: 1303, column: 3, scope: !2794)
!2794 = !DILexicalBlockFile(scope: !2792, file: !1, discriminator: 6)
!2795 = !DILocation(line: 1303, column: 3, scope: !2796)
!2796 = !DILexicalBlockFile(scope: !2792, file: !1, discriminator: 7)
!2797 = !DILocation(line: 1303, column: 3, scope: !2798)
!2798 = !DILexicalBlockFile(scope: !2792, file: !1, discriminator: 8)
!2799 = !DILocation(line: 1303, column: 3, scope: !2800)
!2800 = !DILexicalBlockFile(scope: !2792, file: !1, discriminator: 9)
!2801 = !DILocation(line: 1303, column: 3, scope: !2802)
!2802 = !DILexicalBlockFile(scope: !2803, file: !1, discriminator: 10)
!2803 = distinct !DILexicalBlock(scope: !2792, file: !1, line: 1303, column: 3)
!2804 = !DILocation(line: 1303, column: 3, scope: !2805)
!2805 = !DILexicalBlockFile(scope: !2792, file: !1, discriminator: 11)
!2806 = !DILocation(line: 1303, column: 3, scope: !2807)
!2807 = !DILexicalBlockFile(scope: !2788, file: !1, discriminator: 12)
!2808 = !DILocation(line: 1303, column: 3, scope: !2809)
!2809 = !DILexicalBlockFile(scope: !2777, file: !1, discriminator: 13)
!2810 = !DILocation(line: 1303, column: 3, scope: !2811)
!2811 = !DILexicalBlockFile(scope: !2809, file: !1, discriminator: 17)
!2812 = !DILocation(line: 1303, column: 3, scope: !2813)
!2813 = !DILexicalBlockFile(scope: !2772, file: !1, discriminator: 14)
!2814 = !DILocation(line: 1304, column: 16, scope: !467)
!2815 = !DILocation(line: 1304, column: 3, scope: !467)
!2816 = !DILocation(line: 1304, column: 8, scope: !467)
!2817 = !DILocation(line: 1304, column: 14, scope: !467)
!2818 = !DILocation(line: 1305, column: 3, scope: !467)
!2819 = !DILocation(line: 1305, column: 3, scope: !2820)
!2820 = !DILexicalBlockFile(scope: !2821, file: !1, discriminator: 1)
!2821 = distinct !DILexicalBlock(scope: !2822, file: !1, line: 1305, column: 3)
!2822 = distinct !DILexicalBlock(scope: !467, file: !1, line: 1305, column: 3)
!2823 = !DILocation(line: 1305, column: 3, scope: !2824)
!2824 = !DILexicalBlockFile(scope: !2825, file: !1, discriminator: 2)
!2825 = distinct !DILexicalBlock(scope: !2821, file: !1, line: 1305, column: 3)
!2826 = !DILocation(line: 1305, column: 3, scope: !2827)
!2827 = !DILexicalBlockFile(scope: !2828, file: !1, discriminator: 3)
!2828 = distinct !DILexicalBlock(scope: !2821, file: !1, line: 1305, column: 3)
!2829 = !DILocation(line: 1306, column: 1, scope: !467)
!2830 = !DILocalVariable(name: "loop", arg: 1, scope: !470, file: !1, line: 1309, type: !120)
!2831 = !DILocation(line: 1309, column: 29, scope: !470)
!2832 = !DILocalVariable(name: "req", arg: 2, scope: !470, file: !1, line: 1309, type: !105)
!2833 = !DILocation(line: 1309, column: 44, scope: !470)
!2834 = !DILocalVariable(name: "path", arg: 3, scope: !470, file: !1, line: 1309, type: !331)
!2835 = !DILocation(line: 1309, column: 61, scope: !470)
!2836 = !DILocalVariable(name: "cb", arg: 4, scope: !470, file: !1, line: 1309, type: !320)
!2837 = !DILocation(line: 1309, column: 76, scope: !470)
!2838 = !DILocation(line: 1310, column: 3, scope: !470)
!2839 = !DILocation(line: 1310, column: 3, scope: !2840)
!2840 = !DILexicalBlockFile(scope: !2841, file: !1, discriminator: 1)
!2841 = distinct !DILexicalBlock(scope: !470, file: !1, line: 1310, column: 3)
!2842 = !DILocation(line: 1310, column: 3, scope: !2843)
!2843 = !DILexicalBlockFile(scope: !2844, file: !1, discriminator: 2)
!2844 = distinct !DILexicalBlock(scope: !2841, file: !1, line: 1310, column: 3)
!2845 = !DILocation(line: 1310, column: 3, scope: !2846)
!2846 = !DILexicalBlockFile(scope: !2847, file: !1, discriminator: 3)
!2847 = distinct !DILexicalBlock(scope: !2844, file: !1, line: 1310, column: 3)
!2848 = !DILocation(line: 1310, column: 3, scope: !2849)
!2849 = !DILexicalBlockFile(scope: !2850, file: !1, discriminator: 4)
!2850 = distinct !DILexicalBlock(scope: !2847, file: !1, line: 1310, column: 3)
!2851 = !DILocation(line: 1310, column: 3, scope: !2852)
!2852 = !DILexicalBlockFile(scope: !2847, file: !1, discriminator: 5)
!2853 = !DILocation(line: 1310, column: 3, scope: !2854)
!2854 = !DILexicalBlockFile(scope: !2855, file: !1, discriminator: 6)
!2855 = distinct !DILexicalBlock(scope: !2847, file: !1, line: 1310, column: 3)
!2856 = !DILocation(line: 1310, column: 3, scope: !2857)
!2857 = !DILexicalBlockFile(scope: !2858, file: !1, discriminator: 7)
!2858 = distinct !DILexicalBlock(scope: !2855, file: !1, line: 1310, column: 3)
!2859 = !DILocation(line: 1310, column: 3, scope: !2860)
!2860 = !DILexicalBlockFile(scope: !2855, file: !1, discriminator: 8)
!2861 = !DILocation(line: 1310, column: 3, scope: !2862)
!2862 = !DILexicalBlockFile(scope: !2847, file: !1, discriminator: 9)
!2863 = !DILocation(line: 1310, column: 3, scope: !2864)
!2864 = !DILexicalBlockFile(scope: !2847, file: !1, discriminator: 10)
!2865 = !DILocation(line: 1310, column: 3, scope: !2866)
!2866 = !DILexicalBlockFile(scope: !2841, file: !1, discriminator: 11)
!2867 = !DILocation(line: 1311, column: 3, scope: !470)
!2868 = !DILocation(line: 1311, column: 3, scope: !2869)
!2869 = !DILexicalBlockFile(scope: !2870, file: !1, discriminator: 1)
!2870 = distinct !DILexicalBlock(scope: !470, file: !1, line: 1311, column: 3)
!2871 = !DILocation(line: 1311, column: 3, scope: !2872)
!2872 = !DILexicalBlockFile(scope: !2870, file: !1, discriminator: 2)
!2873 = !DILocation(line: 1311, column: 3, scope: !2874)
!2874 = !DILexicalBlockFile(scope: !2870, file: !1, discriminator: 3)
!2875 = !DILocation(line: 1311, column: 3, scope: !2876)
!2876 = !DILexicalBlockFile(scope: !2870, file: !1, discriminator: 4)
!2877 = !DILocation(line: 1311, column: 3, scope: !2878)
!2878 = !DILexicalBlockFile(scope: !2879, file: !1, discriminator: 5)
!2879 = distinct !DILexicalBlock(scope: !2870, file: !1, line: 1311, column: 3)
!2880 = !DILocation(line: 1311, column: 3, scope: !2881)
!2881 = !DILexicalBlockFile(scope: !2882, file: !1, discriminator: 6)
!2882 = distinct !DILexicalBlock(scope: !2879, file: !1, line: 1311, column: 3)
!2883 = !DILocation(line: 1311, column: 3, scope: !2884)
!2884 = !DILexicalBlockFile(scope: !2885, file: !1, discriminator: 7)
!2885 = distinct !DILexicalBlock(scope: !2879, file: !1, line: 1311, column: 3)
!2886 = !DILocation(line: 1311, column: 3, scope: !2887)
!2887 = !DILexicalBlockFile(scope: !2888, file: !1, discriminator: 8)
!2888 = distinct !DILexicalBlock(scope: !2889, file: !1, line: 1311, column: 3)
!2889 = distinct !DILexicalBlock(scope: !2885, file: !1, line: 1311, column: 3)
!2890 = !DILocation(line: 1311, column: 3, scope: !2891)
!2891 = !DILexicalBlockFile(scope: !2892, file: !1, discriminator: 9)
!2892 = distinct !DILexicalBlock(scope: !2888, file: !1, line: 1311, column: 3)
!2893 = !DILocation(line: 1311, column: 3, scope: !2894)
!2894 = !DILexicalBlockFile(scope: !2892, file: !1, discriminator: 10)
!2895 = !DILocation(line: 1311, column: 3, scope: !2896)
!2896 = !DILexicalBlockFile(scope: !2892, file: !1, discriminator: 11)
!2897 = !DILocation(line: 1311, column: 3, scope: !2898)
!2898 = !DILexicalBlockFile(scope: !2892, file: !1, discriminator: 12)
!2899 = !DILocation(line: 1311, column: 3, scope: !2900)
!2900 = !DILexicalBlockFile(scope: !2892, file: !1, discriminator: 13)
!2901 = !DILocation(line: 1311, column: 3, scope: !2902)
!2902 = !DILexicalBlockFile(scope: !2903, file: !1, discriminator: 14)
!2903 = distinct !DILexicalBlock(scope: !2892, file: !1, line: 1311, column: 3)
!2904 = !DILocation(line: 1311, column: 3, scope: !2905)
!2905 = !DILexicalBlockFile(scope: !2892, file: !1, discriminator: 15)
!2906 = !DILocation(line: 1311, column: 3, scope: !2907)
!2907 = !DILexicalBlockFile(scope: !2888, file: !1, discriminator: 16)
!2908 = !DILocation(line: 1311, column: 3, scope: !2909)
!2909 = !DILexicalBlockFile(scope: !2870, file: !1, discriminator: 17)
!2910 = !DILocation(line: 1312, column: 3, scope: !470)
!2911 = !DILocation(line: 1312, column: 3, scope: !2912)
!2912 = !DILexicalBlockFile(scope: !2913, file: !1, discriminator: 1)
!2913 = distinct !DILexicalBlock(scope: !2914, file: !1, line: 1312, column: 3)
!2914 = distinct !DILexicalBlock(scope: !470, file: !1, line: 1312, column: 3)
!2915 = !DILocation(line: 1312, column: 3, scope: !2916)
!2916 = !DILexicalBlockFile(scope: !2917, file: !1, discriminator: 2)
!2917 = distinct !DILexicalBlock(scope: !2913, file: !1, line: 1312, column: 3)
!2918 = !DILocation(line: 1312, column: 3, scope: !2919)
!2919 = !DILexicalBlockFile(scope: !2920, file: !1, discriminator: 3)
!2920 = distinct !DILexicalBlock(scope: !2913, file: !1, line: 1312, column: 3)
!2921 = !DILocation(line: 1313, column: 1, scope: !470)
!2922 = !DILocalVariable(name: "loop", arg: 1, scope: !471, file: !1, line: 1316, type: !120)
!2923 = !DILocation(line: 1316, column: 28, scope: !471)
!2924 = !DILocalVariable(name: "req", arg: 2, scope: !471, file: !1, line: 1317, type: !105)
!2925 = !DILocation(line: 1317, column: 26, scope: !471)
!2926 = !DILocalVariable(name: "path", arg: 3, scope: !471, file: !1, line: 1318, type: !331)
!2927 = !DILocation(line: 1318, column: 29, scope: !471)
!2928 = !DILocalVariable(name: "atime", arg: 4, scope: !471, file: !1, line: 1319, type: !389)
!2929 = !DILocation(line: 1319, column: 24, scope: !471)
!2930 = !DILocalVariable(name: "mtime", arg: 5, scope: !471, file: !1, line: 1320, type: !389)
!2931 = !DILocation(line: 1320, column: 24, scope: !471)
!2932 = !DILocalVariable(name: "cb", arg: 6, scope: !471, file: !1, line: 1321, type: !320)
!2933 = !DILocation(line: 1321, column: 26, scope: !471)
!2934 = !DILocation(line: 1322, column: 3, scope: !471)
!2935 = !DILocation(line: 1322, column: 3, scope: !2936)
!2936 = !DILexicalBlockFile(scope: !2937, file: !1, discriminator: 1)
!2937 = distinct !DILexicalBlock(scope: !471, file: !1, line: 1322, column: 3)
!2938 = !DILocation(line: 1322, column: 3, scope: !2939)
!2939 = !DILexicalBlockFile(scope: !2940, file: !1, discriminator: 2)
!2940 = distinct !DILexicalBlock(scope: !2937, file: !1, line: 1322, column: 3)
!2941 = !DILocation(line: 1322, column: 3, scope: !2942)
!2942 = !DILexicalBlockFile(scope: !2943, file: !1, discriminator: 3)
!2943 = distinct !DILexicalBlock(scope: !2940, file: !1, line: 1322, column: 3)
!2944 = !DILocation(line: 1322, column: 3, scope: !2945)
!2945 = !DILexicalBlockFile(scope: !2946, file: !1, discriminator: 4)
!2946 = distinct !DILexicalBlock(scope: !2943, file: !1, line: 1322, column: 3)
!2947 = !DILocation(line: 1322, column: 3, scope: !2948)
!2948 = !DILexicalBlockFile(scope: !2943, file: !1, discriminator: 5)
!2949 = !DILocation(line: 1322, column: 3, scope: !2950)
!2950 = !DILexicalBlockFile(scope: !2951, file: !1, discriminator: 6)
!2951 = distinct !DILexicalBlock(scope: !2943, file: !1, line: 1322, column: 3)
!2952 = !DILocation(line: 1322, column: 3, scope: !2953)
!2953 = !DILexicalBlockFile(scope: !2954, file: !1, discriminator: 7)
!2954 = distinct !DILexicalBlock(scope: !2951, file: !1, line: 1322, column: 3)
!2955 = !DILocation(line: 1322, column: 3, scope: !2956)
!2956 = !DILexicalBlockFile(scope: !2951, file: !1, discriminator: 8)
!2957 = !DILocation(line: 1322, column: 3, scope: !2958)
!2958 = !DILexicalBlockFile(scope: !2943, file: !1, discriminator: 9)
!2959 = !DILocation(line: 1322, column: 3, scope: !2960)
!2960 = !DILexicalBlockFile(scope: !2943, file: !1, discriminator: 10)
!2961 = !DILocation(line: 1322, column: 3, scope: !2962)
!2962 = !DILexicalBlockFile(scope: !2937, file: !1, discriminator: 11)
!2963 = !DILocation(line: 1323, column: 3, scope: !471)
!2964 = !DILocation(line: 1323, column: 3, scope: !2965)
!2965 = !DILexicalBlockFile(scope: !2966, file: !1, discriminator: 1)
!2966 = distinct !DILexicalBlock(scope: !471, file: !1, line: 1323, column: 3)
!2967 = !DILocation(line: 1323, column: 3, scope: !2968)
!2968 = !DILexicalBlockFile(scope: !2966, file: !1, discriminator: 2)
!2969 = !DILocation(line: 1323, column: 3, scope: !2970)
!2970 = !DILexicalBlockFile(scope: !2966, file: !1, discriminator: 3)
!2971 = !DILocation(line: 1323, column: 3, scope: !2972)
!2972 = !DILexicalBlockFile(scope: !2966, file: !1, discriminator: 4)
!2973 = !DILocation(line: 1323, column: 3, scope: !2974)
!2974 = !DILexicalBlockFile(scope: !2975, file: !1, discriminator: 5)
!2975 = distinct !DILexicalBlock(scope: !2966, file: !1, line: 1323, column: 3)
!2976 = !DILocation(line: 1323, column: 3, scope: !2977)
!2977 = !DILexicalBlockFile(scope: !2978, file: !1, discriminator: 6)
!2978 = distinct !DILexicalBlock(scope: !2975, file: !1, line: 1323, column: 3)
!2979 = !DILocation(line: 1323, column: 3, scope: !2980)
!2980 = !DILexicalBlockFile(scope: !2981, file: !1, discriminator: 7)
!2981 = distinct !DILexicalBlock(scope: !2975, file: !1, line: 1323, column: 3)
!2982 = !DILocation(line: 1323, column: 3, scope: !2983)
!2983 = !DILexicalBlockFile(scope: !2984, file: !1, discriminator: 8)
!2984 = distinct !DILexicalBlock(scope: !2985, file: !1, line: 1323, column: 3)
!2985 = distinct !DILexicalBlock(scope: !2981, file: !1, line: 1323, column: 3)
!2986 = !DILocation(line: 1323, column: 3, scope: !2987)
!2987 = !DILexicalBlockFile(scope: !2988, file: !1, discriminator: 9)
!2988 = distinct !DILexicalBlock(scope: !2984, file: !1, line: 1323, column: 3)
!2989 = !DILocation(line: 1323, column: 3, scope: !2990)
!2990 = !DILexicalBlockFile(scope: !2988, file: !1, discriminator: 10)
!2991 = !DILocation(line: 1323, column: 3, scope: !2992)
!2992 = !DILexicalBlockFile(scope: !2988, file: !1, discriminator: 11)
!2993 = !DILocation(line: 1323, column: 3, scope: !2994)
!2994 = !DILexicalBlockFile(scope: !2988, file: !1, discriminator: 12)
!2995 = !DILocation(line: 1323, column: 3, scope: !2996)
!2996 = !DILexicalBlockFile(scope: !2988, file: !1, discriminator: 13)
!2997 = !DILocation(line: 1323, column: 3, scope: !2998)
!2998 = !DILexicalBlockFile(scope: !2999, file: !1, discriminator: 14)
!2999 = distinct !DILexicalBlock(scope: !2988, file: !1, line: 1323, column: 3)
!3000 = !DILocation(line: 1323, column: 3, scope: !3001)
!3001 = !DILexicalBlockFile(scope: !2988, file: !1, discriminator: 15)
!3002 = !DILocation(line: 1323, column: 3, scope: !3003)
!3003 = !DILexicalBlockFile(scope: !2984, file: !1, discriminator: 16)
!3004 = !DILocation(line: 1323, column: 3, scope: !3005)
!3005 = !DILexicalBlockFile(scope: !2966, file: !1, discriminator: 17)
!3006 = !DILocation(line: 1324, column: 16, scope: !471)
!3007 = !DILocation(line: 1324, column: 3, scope: !471)
!3008 = !DILocation(line: 1324, column: 8, scope: !471)
!3009 = !DILocation(line: 1324, column: 14, scope: !471)
!3010 = !DILocation(line: 1325, column: 16, scope: !471)
!3011 = !DILocation(line: 1325, column: 3, scope: !471)
!3012 = !DILocation(line: 1325, column: 8, scope: !471)
!3013 = !DILocation(line: 1325, column: 14, scope: !471)
!3014 = !DILocation(line: 1326, column: 3, scope: !471)
!3015 = !DILocation(line: 1326, column: 3, scope: !3016)
!3016 = !DILexicalBlockFile(scope: !3017, file: !1, discriminator: 1)
!3017 = distinct !DILexicalBlock(scope: !3018, file: !1, line: 1326, column: 3)
!3018 = distinct !DILexicalBlock(scope: !471, file: !1, line: 1326, column: 3)
!3019 = !DILocation(line: 1326, column: 3, scope: !3020)
!3020 = !DILexicalBlockFile(scope: !3021, file: !1, discriminator: 2)
!3021 = distinct !DILexicalBlock(scope: !3017, file: !1, line: 1326, column: 3)
!3022 = !DILocation(line: 1326, column: 3, scope: !3023)
!3023 = !DILexicalBlockFile(scope: !3024, file: !1, discriminator: 3)
!3024 = distinct !DILexicalBlock(scope: !3017, file: !1, line: 1326, column: 3)
!3025 = !DILocation(line: 1327, column: 1, scope: !471)
!3026 = !DILocalVariable(name: "loop", arg: 1, scope: !474, file: !1, line: 1330, type: !120)
!3027 = !DILocation(line: 1330, column: 28, scope: !474)
!3028 = !DILocalVariable(name: "req", arg: 2, scope: !474, file: !1, line: 1331, type: !105)
!3029 = !DILocation(line: 1331, column: 26, scope: !474)
!3030 = !DILocalVariable(name: "file", arg: 3, scope: !474, file: !1, line: 1332, type: !360)
!3031 = !DILocation(line: 1332, column: 25, scope: !474)
!3032 = !DILocalVariable(name: "bufs", arg: 4, scope: !474, file: !1, line: 1333, type: !456)
!3033 = !DILocation(line: 1333, column: 32, scope: !474)
!3034 = !DILocalVariable(name: "nbufs", arg: 5, scope: !474, file: !1, line: 1334, type: !126)
!3035 = !DILocation(line: 1334, column: 30, scope: !474)
!3036 = !DILocalVariable(name: "off", arg: 6, scope: !474, file: !1, line: 1335, type: !438)
!3037 = !DILocation(line: 1335, column: 25, scope: !474)
!3038 = !DILocalVariable(name: "cb", arg: 7, scope: !474, file: !1, line: 1336, type: !320)
!3039 = !DILocation(line: 1336, column: 26, scope: !474)
!3040 = !DILocation(line: 1337, column: 7, scope: !3041)
!3041 = distinct !DILexicalBlock(scope: !474, file: !1, line: 1337, column: 7)
!3042 = !DILocation(line: 1337, column: 12, scope: !3041)
!3043 = !DILocation(line: 1337, column: 20, scope: !3041)
!3044 = !DILocation(line: 1337, column: 23, scope: !3045)
!3045 = !DILexicalBlockFile(scope: !3041, file: !1, discriminator: 1)
!3046 = !DILocation(line: 1337, column: 29, scope: !3045)
!3047 = !DILocation(line: 1337, column: 7, scope: !3045)
!3048 = !DILocation(line: 1338, column: 5, scope: !3041)
!3049 = !DILocation(line: 1340, column: 3, scope: !474)
!3050 = !DILocation(line: 1340, column: 3, scope: !3051)
!3051 = !DILexicalBlockFile(scope: !3052, file: !1, discriminator: 1)
!3052 = distinct !DILexicalBlock(scope: !474, file: !1, line: 1340, column: 3)
!3053 = !DILocation(line: 1340, column: 3, scope: !3054)
!3054 = !DILexicalBlockFile(scope: !3055, file: !1, discriminator: 2)
!3055 = distinct !DILexicalBlock(scope: !3052, file: !1, line: 1340, column: 3)
!3056 = !DILocation(line: 1340, column: 3, scope: !3057)
!3057 = !DILexicalBlockFile(scope: !3058, file: !1, discriminator: 3)
!3058 = distinct !DILexicalBlock(scope: !3055, file: !1, line: 1340, column: 3)
!3059 = !DILocation(line: 1340, column: 3, scope: !3060)
!3060 = !DILexicalBlockFile(scope: !3061, file: !1, discriminator: 4)
!3061 = distinct !DILexicalBlock(scope: !3058, file: !1, line: 1340, column: 3)
!3062 = !DILocation(line: 1340, column: 3, scope: !3063)
!3063 = !DILexicalBlockFile(scope: !3058, file: !1, discriminator: 5)
!3064 = !DILocation(line: 1340, column: 3, scope: !3065)
!3065 = !DILexicalBlockFile(scope: !3066, file: !1, discriminator: 6)
!3066 = distinct !DILexicalBlock(scope: !3058, file: !1, line: 1340, column: 3)
!3067 = !DILocation(line: 1340, column: 3, scope: !3068)
!3068 = !DILexicalBlockFile(scope: !3069, file: !1, discriminator: 7)
!3069 = distinct !DILexicalBlock(scope: !3066, file: !1, line: 1340, column: 3)
!3070 = !DILocation(line: 1340, column: 3, scope: !3071)
!3071 = !DILexicalBlockFile(scope: !3066, file: !1, discriminator: 8)
!3072 = !DILocation(line: 1340, column: 3, scope: !3073)
!3073 = !DILexicalBlockFile(scope: !3058, file: !1, discriminator: 9)
!3074 = !DILocation(line: 1340, column: 3, scope: !3075)
!3075 = !DILexicalBlockFile(scope: !3058, file: !1, discriminator: 10)
!3076 = !DILocation(line: 1340, column: 3, scope: !3077)
!3077 = !DILexicalBlockFile(scope: !3052, file: !1, discriminator: 11)
!3078 = !DILocation(line: 1341, column: 15, scope: !474)
!3079 = !DILocation(line: 1341, column: 3, scope: !474)
!3080 = !DILocation(line: 1341, column: 8, scope: !474)
!3081 = !DILocation(line: 1341, column: 13, scope: !474)
!3082 = !DILocation(line: 1343, column: 16, scope: !474)
!3083 = !DILocation(line: 1343, column: 3, scope: !474)
!3084 = !DILocation(line: 1343, column: 8, scope: !474)
!3085 = !DILocation(line: 1343, column: 14, scope: !474)
!3086 = !DILocation(line: 1344, column: 15, scope: !474)
!3087 = !DILocation(line: 1344, column: 20, scope: !474)
!3088 = !DILocation(line: 1344, column: 3, scope: !474)
!3089 = !DILocation(line: 1344, column: 8, scope: !474)
!3090 = !DILocation(line: 1344, column: 13, scope: !474)
!3091 = !DILocation(line: 1345, column: 7, scope: !3092)
!3092 = distinct !DILexicalBlock(scope: !474, file: !1, line: 1345, column: 7)
!3093 = !DILocation(line: 1345, column: 13, scope: !3092)
!3094 = !DILocation(line: 1345, column: 7, scope: !474)
!3095 = !DILocation(line: 1346, column: 28, scope: !3092)
!3096 = !DILocation(line: 1346, column: 34, scope: !3092)
!3097 = !DILocation(line: 1346, column: 17, scope: !3092)
!3098 = !DILocation(line: 1346, column: 5, scope: !3092)
!3099 = !DILocation(line: 1346, column: 10, scope: !3092)
!3100 = !DILocation(line: 1346, column: 15, scope: !3092)
!3101 = !DILocation(line: 1348, column: 7, scope: !3102)
!3102 = distinct !DILexicalBlock(scope: !474, file: !1, line: 1348, column: 7)
!3103 = !DILocation(line: 1348, column: 12, scope: !3102)
!3104 = !DILocation(line: 1348, column: 17, scope: !3102)
!3105 = !DILocation(line: 1348, column: 7, scope: !474)
!3106 = !DILocation(line: 1349, column: 9, scope: !3107)
!3107 = distinct !DILexicalBlock(scope: !3108, file: !1, line: 1349, column: 9)
!3108 = distinct !DILexicalBlock(scope: !3102, file: !1, line: 1348, column: 26)
!3109 = !DILocation(line: 1349, column: 12, scope: !3107)
!3110 = !DILocation(line: 1349, column: 9, scope: !3108)
!3111 = !DILocation(line: 1350, column: 7, scope: !3107)
!3112 = !DILocation(line: 1350, column: 7, scope: !3113)
!3113 = !DILexicalBlockFile(scope: !3114, file: !1, discriminator: 1)
!3114 = distinct !DILexicalBlock(scope: !3107, file: !1, line: 1350, column: 7)
!3115 = !DILocation(line: 1350, column: 7, scope: !3116)
!3116 = !DILexicalBlockFile(scope: !3114, file: !1, discriminator: 2)
!3117 = !DILocation(line: 1350, column: 7, scope: !3118)
!3118 = !DILexicalBlockFile(scope: !3114, file: !1, discriminator: 3)
!3119 = !DILocation(line: 1350, column: 7, scope: !3120)
!3120 = !DILexicalBlockFile(scope: !3114, file: !1, discriminator: 4)
!3121 = !DILocation(line: 1350, column: 7, scope: !3122)
!3122 = !DILexicalBlockFile(scope: !3114, file: !1, discriminator: 5)
!3123 = !DILocation(line: 1350, column: 7, scope: !3124)
!3124 = !DILexicalBlockFile(scope: !3125, file: !1, discriminator: 6)
!3125 = distinct !DILexicalBlock(scope: !3114, file: !1, line: 1350, column: 7)
!3126 = !DILocation(line: 1350, column: 7, scope: !3127)
!3127 = !DILexicalBlockFile(scope: !3114, file: !1, discriminator: 7)
!3128 = !DILocation(line: 1350, column: 7, scope: !3129)
!3129 = !DILexicalBlockFile(scope: !3114, file: !1, discriminator: 8)
!3130 = !DILocation(line: 1351, column: 5, scope: !3108)
!3131 = !DILocation(line: 1354, column: 10, scope: !474)
!3132 = !DILocation(line: 1354, column: 15, scope: !474)
!3133 = !DILocation(line: 1354, column: 3, scope: !474)
!3134 = !DILocation(line: 1354, column: 21, scope: !474)
!3135 = !DILocation(line: 1354, column: 27, scope: !474)
!3136 = !DILocation(line: 1354, column: 33, scope: !474)
!3137 = !DILocation(line: 1356, column: 14, scope: !474)
!3138 = !DILocation(line: 1356, column: 3, scope: !474)
!3139 = !DILocation(line: 1356, column: 8, scope: !474)
!3140 = !DILocation(line: 1356, column: 12, scope: !474)
!3141 = !DILocation(line: 1357, column: 3, scope: !474)
!3142 = !DILocation(line: 1357, column: 3, scope: !3143)
!3143 = !DILexicalBlockFile(scope: !3144, file: !1, discriminator: 1)
!3144 = distinct !DILexicalBlock(scope: !3145, file: !1, line: 1357, column: 3)
!3145 = distinct !DILexicalBlock(scope: !474, file: !1, line: 1357, column: 3)
!3146 = !DILocation(line: 1357, column: 3, scope: !3147)
!3147 = !DILexicalBlockFile(scope: !3148, file: !1, discriminator: 2)
!3148 = distinct !DILexicalBlock(scope: !3144, file: !1, line: 1357, column: 3)
!3149 = !DILocation(line: 1357, column: 3, scope: !3150)
!3150 = !DILexicalBlockFile(scope: !3151, file: !1, discriminator: 3)
!3151 = distinct !DILexicalBlock(scope: !3144, file: !1, line: 1357, column: 3)
!3152 = !DILocation(line: 1358, column: 1, scope: !474)
!3153 = !DILocalVariable(name: "req", arg: 1, scope: !475, file: !1, line: 1361, type: !105)
!3154 = !DILocation(line: 1361, column: 33, scope: !475)
!3155 = !DILocation(line: 1367, column: 7, scope: !3156)
!3156 = distinct !DILexicalBlock(scope: !475, file: !1, line: 1367, column: 7)
!3157 = !DILocation(line: 1367, column: 12, scope: !3156)
!3158 = !DILocation(line: 1367, column: 17, scope: !3156)
!3159 = !DILocation(line: 1367, column: 25, scope: !3156)
!3160 = !DILocation(line: 1367, column: 29, scope: !3161)
!3161 = !DILexicalBlockFile(scope: !3156, file: !1, discriminator: 1)
!3162 = !DILocation(line: 1367, column: 34, scope: !3161)
!3163 = !DILocation(line: 1367, column: 37, scope: !3161)
!3164 = !DILocation(line: 1367, column: 45, scope: !3161)
!3165 = !DILocation(line: 1367, column: 48, scope: !3166)
!3166 = !DILexicalBlockFile(scope: !3156, file: !1, discriminator: 2)
!3167 = !DILocation(line: 1367, column: 53, scope: !3166)
!3168 = !DILocation(line: 1367, column: 61, scope: !3166)
!3169 = !DILocation(line: 1367, column: 7, scope: !3166)
!3170 = !DILocation(line: 1368, column: 22, scope: !3156)
!3171 = !DILocation(line: 1368, column: 27, scope: !3156)
!3172 = !DILocation(line: 1368, column: 5, scope: !3156)
!3173 = !DILocation(line: 1370, column: 3, scope: !475)
!3174 = !DILocation(line: 1370, column: 8, scope: !475)
!3175 = !DILocation(line: 1370, column: 13, scope: !475)
!3176 = !DILocation(line: 1371, column: 3, scope: !475)
!3177 = !DILocation(line: 1371, column: 8, scope: !475)
!3178 = !DILocation(line: 1371, column: 17, scope: !475)
!3179 = !DILocation(line: 1373, column: 7, scope: !3180)
!3180 = distinct !DILexicalBlock(scope: !475, file: !1, line: 1373, column: 7)
!3181 = !DILocation(line: 1373, column: 12, scope: !3180)
!3182 = !DILocation(line: 1373, column: 20, scope: !3180)
!3183 = !DILocation(line: 1373, column: 37, scope: !3180)
!3184 = !DILocation(line: 1373, column: 40, scope: !3185)
!3185 = !DILexicalBlockFile(scope: !3180, file: !1, discriminator: 1)
!3186 = !DILocation(line: 1373, column: 45, scope: !3185)
!3187 = !DILocation(line: 1373, column: 49, scope: !3185)
!3188 = !DILocation(line: 1373, column: 7, scope: !3185)
!3189 = !DILocation(line: 1374, column: 28, scope: !3180)
!3190 = !DILocation(line: 1374, column: 5, scope: !3180)
!3191 = !DILocation(line: 1376, column: 7, scope: !3192)
!3192 = distinct !DILexicalBlock(scope: !475, file: !1, line: 1376, column: 7)
!3193 = !DILocation(line: 1376, column: 12, scope: !3192)
!3194 = !DILocation(line: 1376, column: 20, scope: !3192)
!3195 = !DILocation(line: 1376, column: 25, scope: !3192)
!3196 = !DILocation(line: 1376, column: 19, scope: !3192)
!3197 = !DILocation(line: 1376, column: 16, scope: !3192)
!3198 = !DILocation(line: 1376, column: 7, scope: !475)
!3199 = !DILocation(line: 1377, column: 14, scope: !3192)
!3200 = !DILocation(line: 1377, column: 19, scope: !3192)
!3201 = !DILocation(line: 1377, column: 5, scope: !3192)
!3202 = !DILocation(line: 1378, column: 3, scope: !475)
!3203 = !DILocation(line: 1378, column: 8, scope: !475)
!3204 = !DILocation(line: 1378, column: 12, scope: !475)
!3205 = !DILocation(line: 1379, column: 1, scope: !475)
!3206 = !DILocalVariable(name: "req", arg: 1, scope: !477, file: !1, line: 129, type: !105)
!3207 = !DILocation(line: 129, column: 42, scope: !477)
!3208 = !DILocation(line: 131, column: 20, scope: !477)
!3209 = !DILocation(line: 131, column: 25, scope: !477)
!3210 = !DILocation(line: 131, column: 10, scope: !477)
!3211 = !DILocation(line: 131, column: 3, scope: !477)
!3212 = !DILocalVariable(name: "fd", arg: 1, scope: !480, file: !1, line: 880, type: !133)
!3213 = !DILocation(line: 880, column: 29, scope: !480)
!3214 = !DILocalVariable(name: "buf", arg: 2, scope: !480, file: !1, line: 880, type: !483)
!3215 = !DILocation(line: 880, column: 44, scope: !480)
!3216 = !DILocalVariable(name: "pbuf", scope: !480, file: !1, line: 881, type: !488)
!3217 = !DILocation(line: 881, column: 15, scope: !480)
!3218 = !DILocalVariable(name: "ret", scope: !480, file: !1, line: 882, type: !133)
!3219 = !DILocation(line: 882, column: 7, scope: !480)
!3220 = !DILocation(line: 884, column: 15, scope: !480)
!3221 = !DILocation(line: 884, column: 9, scope: !480)
!3222 = !DILocation(line: 884, column: 7, scope: !480)
!3223 = !DILocation(line: 885, column: 7, scope: !3224)
!3224 = distinct !DILexicalBlock(scope: !480, file: !1, line: 885, column: 7)
!3225 = !DILocation(line: 885, column: 11, scope: !3224)
!3226 = !DILocation(line: 885, column: 7, scope: !480)
!3227 = !DILocation(line: 886, column: 24, scope: !3224)
!3228 = !DILocation(line: 886, column: 5, scope: !3224)
!3229 = !DILocation(line: 888, column: 10, scope: !480)
!3230 = !DILocation(line: 888, column: 3, scope: !480)
!3231 = !DILocalVariable(name: "req", arg: 1, scope: !522, file: !1, line: 145, type: !105)
!3232 = !DILocation(line: 145, column: 38, scope: !522)
!3233 = !DILocation(line: 150, column: 16, scope: !522)
!3234 = !DILocation(line: 150, column: 21, scope: !522)
!3235 = !DILocation(line: 150, column: 10, scope: !522)
!3236 = !DILocation(line: 150, column: 3, scope: !522)
!3237 = !DILocalVariable(name: "req", arg: 1, scope: !523, file: !1, line: 155, type: !105)
!3238 = !DILocation(line: 155, column: 39, scope: !523)
!3239 = !DILocalVariable(name: "ts", scope: !523, file: !1, line: 161, type: !3240)
!3240 = !DICompositeType(tag: DW_TAG_array_type, baseType: !509, size: 256, align: 64, elements: !101)
!3241 = !DILocation(line: 161, column: 19, scope: !523)
!3242 = !DILocalVariable(name: "tv", scope: !523, file: !1, line: 162, type: !3243)
!3243 = !DICompositeType(tag: DW_TAG_array_type, baseType: !3244, size: 256, align: 64, elements: !101)
!3244 = !DICompositeType(tag: DW_TAG_structure_type, name: "timeval", file: !3245, line: 30, size: 128, align: 64, elements: !3246)
!3245 = !DIFile(filename: "/usr/include/x86_64-linux-gnu/bits/time.h", directory: "/data/download/cmake/cmake-master/Utilities/cmlibuv")
!3246 = !{!3247, !3248}
!3247 = !DIDerivedType(tag: DW_TAG_member, name: "tv_sec", scope: !3244, file: !3245, line: 32, baseType: !513, size: 64, align: 64)
!3248 = !DIDerivedType(tag: DW_TAG_member, name: "tv_usec", scope: !3244, file: !3245, line: 33, baseType: !3249, size: 64, align: 64, offset: 64)
!3249 = !DIDerivedType(tag: DW_TAG_typedef, name: "__suseconds_t", file: !328, line: 141, baseType: !188)
!3250 = !DILocation(line: 162, column: 18, scope: !523)
!3251 = !DILocalVariable(name: "path", scope: !523, file: !1, line: 163, type: !3252)
!3252 = !DICompositeType(tag: DW_TAG_array_type, baseType: !184, size: 216, align: 8, elements: !3253)
!3253 = !{!3254}
!3254 = !DISubrange(count: 27)
!3255 = !DILocation(line: 163, column: 8, scope: !523)
!3256 = !DILocalVariable(name: "r", scope: !523, file: !1, line: 164, type: !133)
!3257 = !DILocation(line: 164, column: 7, scope: !523)
!3258 = !DILocation(line: 166, column: 7, scope: !3259)
!3259 = distinct !DILexicalBlock(scope: !523, file: !1, line: 166, column: 7)
!3260 = !DILocation(line: 166, column: 7, scope: !523)
!3261 = !DILocation(line: 167, column: 5, scope: !3259)
!3262 = !DILocation(line: 169, column: 19, scope: !523)
!3263 = !DILocation(line: 169, column: 24, scope: !523)
!3264 = !DILocation(line: 169, column: 3, scope: !523)
!3265 = !DILocation(line: 169, column: 9, scope: !523)
!3266 = !DILocation(line: 169, column: 17, scope: !523)
!3267 = !DILocation(line: 170, column: 30, scope: !523)
!3268 = !DILocation(line: 170, column: 35, scope: !523)
!3269 = !DILocation(line: 170, column: 41, scope: !523)
!3270 = !DILocation(line: 170, column: 19, scope: !523)
!3271 = !DILocation(line: 170, column: 52, scope: !523)
!3272 = !DILocation(line: 170, column: 62, scope: !523)
!3273 = !DILocation(line: 170, column: 3, scope: !523)
!3274 = !DILocation(line: 170, column: 9, scope: !523)
!3275 = !DILocation(line: 170, column: 17, scope: !523)
!3276 = !DILocation(line: 171, column: 19, scope: !523)
!3277 = !DILocation(line: 171, column: 24, scope: !523)
!3278 = !DILocation(line: 171, column: 3, scope: !523)
!3279 = !DILocation(line: 171, column: 9, scope: !523)
!3280 = !DILocation(line: 171, column: 17, scope: !523)
!3281 = !DILocation(line: 172, column: 30, scope: !523)
!3282 = !DILocation(line: 172, column: 35, scope: !523)
!3283 = !DILocation(line: 172, column: 41, scope: !523)
!3284 = !DILocation(line: 172, column: 19, scope: !523)
!3285 = !DILocation(line: 172, column: 52, scope: !523)
!3286 = !DILocation(line: 172, column: 62, scope: !523)
!3287 = !DILocation(line: 172, column: 3, scope: !523)
!3288 = !DILocation(line: 172, column: 9, scope: !523)
!3289 = !DILocation(line: 172, column: 17, scope: !523)
!3290 = !DILocation(line: 174, column: 20, scope: !523)
!3291 = !DILocation(line: 174, column: 25, scope: !523)
!3292 = !DILocation(line: 174, column: 37, scope: !523)
!3293 = !DILocation(line: 174, column: 7, scope: !523)
!3294 = !DILocation(line: 174, column: 5, scope: !523)
!3295 = !DILocation(line: 175, column: 7, scope: !3296)
!3296 = distinct !DILexicalBlock(scope: !523, file: !1, line: 175, column: 7)
!3297 = !DILocation(line: 175, column: 9, scope: !3296)
!3298 = !DILocation(line: 175, column: 7, scope: !523)
!3299 = !DILocation(line: 176, column: 12, scope: !3296)
!3300 = !DILocation(line: 176, column: 5, scope: !3296)
!3301 = !DILocation(line: 178, column: 7, scope: !3302)
!3302 = distinct !DILexicalBlock(scope: !523, file: !1, line: 178, column: 7)
!3303 = !DILocation(line: 178, column: 13, scope: !3302)
!3304 = !DILocation(line: 178, column: 7, scope: !523)
!3305 = !DILocation(line: 179, column: 12, scope: !3302)
!3306 = !DILocation(line: 179, column: 5, scope: !3302)
!3307 = !DILocation(line: 181, column: 15, scope: !523)
!3308 = !DILocation(line: 181, column: 3, scope: !523)
!3309 = !DILocation(line: 185, column: 19, scope: !523)
!3310 = !DILocation(line: 185, column: 24, scope: !523)
!3311 = !DILocation(line: 185, column: 3, scope: !523)
!3312 = !DILocation(line: 185, column: 9, scope: !523)
!3313 = !DILocation(line: 185, column: 17, scope: !523)
!3314 = !DILocation(line: 186, column: 30, scope: !523)
!3315 = !DILocation(line: 186, column: 35, scope: !523)
!3316 = !DILocation(line: 186, column: 41, scope: !523)
!3317 = !DILocation(line: 186, column: 19, scope: !523)
!3318 = !DILocation(line: 186, column: 52, scope: !523)
!3319 = !DILocation(line: 186, column: 3, scope: !523)
!3320 = !DILocation(line: 186, column: 9, scope: !523)
!3321 = !DILocation(line: 186, column: 17, scope: !523)
!3322 = !DILocation(line: 187, column: 19, scope: !523)
!3323 = !DILocation(line: 187, column: 24, scope: !523)
!3324 = !DILocation(line: 187, column: 3, scope: !523)
!3325 = !DILocation(line: 187, column: 9, scope: !523)
!3326 = !DILocation(line: 187, column: 17, scope: !523)
!3327 = !DILocation(line: 188, column: 30, scope: !523)
!3328 = !DILocation(line: 188, column: 35, scope: !523)
!3329 = !DILocation(line: 188, column: 41, scope: !523)
!3330 = !DILocation(line: 188, column: 19, scope: !523)
!3331 = !DILocation(line: 188, column: 52, scope: !523)
!3332 = !DILocation(line: 188, column: 3, scope: !523)
!3333 = !DILocation(line: 188, column: 9, scope: !523)
!3334 = !DILocation(line: 188, column: 17, scope: !523)
!3335 = !DILocation(line: 189, column: 12, scope: !523)
!3336 = !DILocation(line: 189, column: 58, scope: !523)
!3337 = !DILocation(line: 189, column: 63, scope: !523)
!3338 = !DILocation(line: 189, column: 3, scope: !523)
!3339 = !DILocation(line: 191, column: 14, scope: !523)
!3340 = !DILocation(line: 191, column: 20, scope: !523)
!3341 = !DILocation(line: 191, column: 7, scope: !523)
!3342 = !DILocation(line: 191, column: 5, scope: !523)
!3343 = !DILocation(line: 192, column: 7, scope: !3344)
!3344 = distinct !DILexicalBlock(scope: !523, file: !1, line: 192, column: 7)
!3345 = !DILocation(line: 192, column: 9, scope: !3344)
!3346 = !DILocation(line: 192, column: 7, scope: !523)
!3347 = !DILocation(line: 193, column: 12, scope: !3344)
!3348 = !DILocation(line: 193, column: 5, scope: !3344)
!3349 = !DILocation(line: 195, column: 11, scope: !523)
!3350 = !DILocation(line: 195, column: 3, scope: !523)
!3351 = !DILocation(line: 197, column: 15, scope: !3352)
!3352 = distinct !DILexicalBlock(scope: !3353, file: !1, line: 197, column: 9)
!3353 = distinct !DILexicalBlock(scope: !523, file: !1, line: 195, column: 18)
!3354 = !DILocation(line: 197, column: 20, scope: !3352)
!3355 = !DILocation(line: 197, column: 9, scope: !3352)
!3356 = !DILocation(line: 197, column: 35, scope: !3352)
!3357 = !DILocation(line: 197, column: 41, scope: !3352)
!3358 = !DILocation(line: 197, column: 44, scope: !3359)
!3359 = !DILexicalBlockFile(scope: !3352, file: !1, discriminator: 1)
!3360 = !DILocation(line: 197, column: 50, scope: !3359)
!3361 = !DILocation(line: 197, column: 9, scope: !3359)
!3362 = !DILocation(line: 198, column: 7, scope: !3352)
!3363 = !DILocation(line: 197, column: 53, scope: !3364)
!3364 = !DILexicalBlockFile(scope: !3352, file: !1, discriminator: 2)
!3365 = !DILocation(line: 203, column: 5, scope: !3353)
!3366 = !DILocation(line: 203, column: 11, scope: !3353)
!3367 = !DILocation(line: 204, column: 5, scope: !3353)
!3368 = !DILocation(line: 207, column: 10, scope: !523)
!3369 = !DILocation(line: 207, column: 3, scope: !523)
!3370 = !DILocation(line: 245, column: 1, scope: !523)
!3371 = !DILocalVariable(name: "path", arg: 1, scope: !524, file: !1, line: 868, type: !331)
!3372 = !DILocation(line: 868, column: 37, scope: !524)
!3373 = !DILocalVariable(name: "buf", arg: 2, scope: !524, file: !1, line: 868, type: !483)
!3374 = !DILocation(line: 868, column: 54, scope: !524)
!3375 = !DILocalVariable(name: "pbuf", scope: !524, file: !1, line: 869, type: !488)
!3376 = !DILocation(line: 869, column: 15, scope: !524)
!3377 = !DILocalVariable(name: "ret", scope: !524, file: !1, line: 870, type: !133)
!3378 = !DILocation(line: 870, column: 7, scope: !524)
!3379 = !DILocation(line: 872, column: 15, scope: !524)
!3380 = !DILocation(line: 872, column: 9, scope: !524)
!3381 = !DILocation(line: 872, column: 7, scope: !524)
!3382 = !DILocation(line: 873, column: 7, scope: !3383)
!3383 = distinct !DILexicalBlock(scope: !524, file: !1, line: 873, column: 7)
!3384 = !DILocation(line: 873, column: 11, scope: !3383)
!3385 = !DILocation(line: 873, column: 7, scope: !524)
!3386 = !DILocation(line: 874, column: 24, scope: !3383)
!3387 = !DILocation(line: 874, column: 5, scope: !3383)
!3388 = !DILocation(line: 876, column: 10, scope: !524)
!3389 = !DILocation(line: 876, column: 3, scope: !524)
!3390 = !DILocalVariable(name: "req", arg: 1, scope: !527, file: !1, line: 258, type: !105)
!3391 = !DILocation(line: 258, column: 40, scope: !527)
!3392 = !DILocation(line: 259, column: 30, scope: !527)
!3393 = !DILocation(line: 259, column: 35, scope: !527)
!3394 = !DILocation(line: 259, column: 10, scope: !527)
!3395 = !DILocation(line: 259, column: 3, scope: !527)
!3396 = !DILocalVariable(name: "req", arg: 1, scope: !528, file: !1, line: 263, type: !105)
!3397 = !DILocation(line: 263, column: 37, scope: !528)
!3398 = !DILocalVariable(name: "r", scope: !528, file: !1, line: 265, type: !133)
!3399 = !DILocation(line: 265, column: 7, scope: !528)
!3400 = !DILocation(line: 268, column: 7, scope: !3401)
!3401 = distinct !DILexicalBlock(scope: !528, file: !1, line: 268, column: 7)
!3402 = !DILocation(line: 268, column: 26, scope: !3401)
!3403 = !DILocation(line: 268, column: 7, scope: !528)
!3404 = !DILocation(line: 270, column: 14, scope: !3405)
!3405 = distinct !DILexicalBlock(scope: !3401, file: !1, line: 268, column: 32)
!3406 = !DILocation(line: 270, column: 19, scope: !3405)
!3407 = !DILocation(line: 270, column: 25, scope: !3405)
!3408 = !DILocation(line: 270, column: 30, scope: !3405)
!3409 = !DILocation(line: 270, column: 36, scope: !3405)
!3410 = !DILocation(line: 270, column: 49, scope: !3405)
!3411 = !DILocation(line: 270, column: 54, scope: !3405)
!3412 = !DILocation(line: 270, column: 9, scope: !3405)
!3413 = !DILocation(line: 270, column: 7, scope: !3405)
!3414 = !DILocation(line: 271, column: 9, scope: !3415)
!3415 = distinct !DILexicalBlock(scope: !3405, file: !1, line: 271, column: 9)
!3416 = !DILocation(line: 271, column: 11, scope: !3415)
!3417 = !DILocation(line: 271, column: 9, scope: !3405)
!3418 = !DILocation(line: 272, column: 14, scope: !3415)
!3419 = !DILocation(line: 272, column: 7, scope: !3415)
!3420 = !DILocation(line: 273, column: 9, scope: !3421)
!3421 = distinct !DILexicalBlock(scope: !3405, file: !1, line: 273, column: 9)
!3422 = !DILocation(line: 273, column: 15, scope: !3421)
!3423 = !DILocation(line: 273, column: 9, scope: !3405)
!3424 = !DILocation(line: 274, column: 14, scope: !3421)
!3425 = !DILocation(line: 274, column: 7, scope: !3421)
!3426 = !DILocation(line: 275, column: 24, scope: !3405)
!3427 = !DILocation(line: 277, column: 3, scope: !3405)
!3428 = !DILocation(line: 279, column: 7, scope: !3429)
!3429 = distinct !DILexicalBlock(scope: !528, file: !1, line: 279, column: 7)
!3430 = !DILocation(line: 279, column: 12, scope: !3429)
!3431 = !DILocation(line: 279, column: 15, scope: !3429)
!3432 = !DILocation(line: 279, column: 7, scope: !528)
!3433 = !DILocation(line: 280, column: 23, scope: !3429)
!3434 = !DILocation(line: 280, column: 28, scope: !3429)
!3435 = !DILocation(line: 280, column: 34, scope: !3429)
!3436 = !DILocation(line: 280, column: 5, scope: !3429)
!3437 = !DILocation(line: 282, column: 12, scope: !528)
!3438 = !DILocation(line: 282, column: 17, scope: !528)
!3439 = !DILocation(line: 282, column: 23, scope: !528)
!3440 = !DILocation(line: 282, column: 28, scope: !528)
!3441 = !DILocation(line: 282, column: 35, scope: !528)
!3442 = !DILocation(line: 282, column: 40, scope: !528)
!3443 = !DILocation(line: 282, column: 7, scope: !528)
!3444 = !DILocation(line: 282, column: 5, scope: !528)
!3445 = !DILocation(line: 287, column: 7, scope: !3446)
!3446 = distinct !DILexicalBlock(scope: !528, file: !1, line: 287, column: 7)
!3447 = !DILocation(line: 287, column: 9, scope: !3446)
!3448 = !DILocation(line: 287, column: 14, scope: !3446)
!3449 = !DILocation(line: 287, column: 29, scope: !3450)
!3450 = !DILexicalBlockFile(scope: !3446, file: !1, discriminator: 1)
!3451 = !DILocation(line: 287, column: 17, scope: !3450)
!3452 = !DILocation(line: 287, column: 35, scope: !3450)
!3453 = !DILocation(line: 287, column: 7, scope: !3450)
!3454 = !DILocation(line: 288, column: 19, scope: !3455)
!3455 = distinct !DILexicalBlock(scope: !3446, file: !1, line: 287, column: 41)
!3456 = !DILocation(line: 288, column: 9, scope: !3455)
!3457 = !DILocation(line: 288, column: 7, scope: !3455)
!3458 = !DILocation(line: 289, column: 9, scope: !3459)
!3459 = distinct !DILexicalBlock(scope: !3455, file: !1, line: 289, column: 9)
!3460 = !DILocation(line: 289, column: 11, scope: !3459)
!3461 = !DILocation(line: 289, column: 9, scope: !3455)
!3462 = !DILocation(line: 290, column: 7, scope: !3459)
!3463 = !DILocation(line: 291, column: 7, scope: !3455)
!3464 = !DILocation(line: 292, column: 3, scope: !3455)
!3465 = !DILocation(line: 294, column: 7, scope: !3466)
!3466 = distinct !DILexicalBlock(scope: !528, file: !1, line: 294, column: 7)
!3467 = !DILocation(line: 294, column: 12, scope: !3466)
!3468 = !DILocation(line: 294, column: 15, scope: !3466)
!3469 = !DILocation(line: 294, column: 7, scope: !528)
!3470 = !DILocation(line: 295, column: 25, scope: !3466)
!3471 = !DILocation(line: 295, column: 30, scope: !3466)
!3472 = !DILocation(line: 295, column: 36, scope: !3466)
!3473 = !DILocation(line: 295, column: 5, scope: !3466)
!3474 = !DILocation(line: 297, column: 10, scope: !528)
!3475 = !DILocation(line: 297, column: 3, scope: !528)
!3476 = !DILocation(line: 298, column: 1, scope: !528)
!3477 = !DILocalVariable(name: "req", arg: 1, scope: !529, file: !1, line: 893, type: !105)
!3478 = !DILocation(line: 893, column: 41, scope: !529)
!3479 = !DILocalVariable(name: "process", arg: 2, scope: !529, file: !1, line: 893, type: !532)
!3480 = !DILocation(line: 893, column: 72, scope: !529)
!3481 = !DILocalVariable(name: "iovmax", scope: !529, file: !1, line: 894, type: !126)
!3482 = !DILocation(line: 894, column: 16, scope: !529)
!3483 = !DILocalVariable(name: "nbufs", scope: !529, file: !1, line: 895, type: !126)
!3484 = !DILocation(line: 895, column: 16, scope: !529)
!3485 = !DILocalVariable(name: "bufs", scope: !529, file: !1, line: 896, type: !368)
!3486 = !DILocation(line: 896, column: 13, scope: !529)
!3487 = !DILocalVariable(name: "total", scope: !529, file: !1, line: 897, type: !325)
!3488 = !DILocation(line: 897, column: 11, scope: !529)
!3489 = !DILocalVariable(name: "result", scope: !529, file: !1, line: 898, type: !325)
!3490 = !DILocation(line: 898, column: 11, scope: !529)
!3491 = !DILocation(line: 900, column: 12, scope: !529)
!3492 = !DILocation(line: 900, column: 10, scope: !529)
!3493 = !DILocation(line: 901, column: 11, scope: !529)
!3494 = !DILocation(line: 901, column: 16, scope: !529)
!3495 = !DILocation(line: 901, column: 9, scope: !529)
!3496 = !DILocation(line: 902, column: 10, scope: !529)
!3497 = !DILocation(line: 902, column: 15, scope: !529)
!3498 = !DILocation(line: 902, column: 8, scope: !529)
!3499 = !DILocation(line: 903, column: 9, scope: !529)
!3500 = !DILocation(line: 905, column: 3, scope: !529)
!3501 = !DILocation(line: 905, column: 10, scope: !3502)
!3502 = !DILexicalBlockFile(scope: !529, file: !1, discriminator: 1)
!3503 = !DILocation(line: 905, column: 16, scope: !3502)
!3504 = !DILocation(line: 905, column: 3, scope: !3502)
!3505 = !DILocation(line: 906, column: 18, scope: !3506)
!3506 = distinct !DILexicalBlock(scope: !529, file: !1, line: 905, column: 21)
!3507 = !DILocation(line: 906, column: 5, scope: !3506)
!3508 = !DILocation(line: 906, column: 10, scope: !3506)
!3509 = !DILocation(line: 906, column: 16, scope: !3506)
!3510 = !DILocation(line: 907, column: 9, scope: !3511)
!3511 = distinct !DILexicalBlock(scope: !3506, file: !1, line: 907, column: 9)
!3512 = !DILocation(line: 907, column: 14, scope: !3511)
!3513 = !DILocation(line: 907, column: 22, scope: !3511)
!3514 = !DILocation(line: 907, column: 20, scope: !3511)
!3515 = !DILocation(line: 907, column: 9, scope: !3506)
!3516 = !DILocation(line: 908, column: 20, scope: !3511)
!3517 = !DILocation(line: 908, column: 7, scope: !3511)
!3518 = !DILocation(line: 908, column: 12, scope: !3511)
!3519 = !DILocation(line: 908, column: 18, scope: !3511)
!3520 = !DILocation(line: 910, column: 14, scope: !3506)
!3521 = !DILocation(line: 910, column: 22, scope: !3506)
!3522 = !DILocation(line: 910, column: 12, scope: !3506)
!3523 = !DILocation(line: 911, column: 9, scope: !3524)
!3524 = distinct !DILexicalBlock(scope: !3506, file: !1, line: 911, column: 9)
!3525 = !DILocation(line: 911, column: 16, scope: !3524)
!3526 = !DILocation(line: 911, column: 9, scope: !3506)
!3527 = !DILocation(line: 912, column: 11, scope: !3528)
!3528 = distinct !DILexicalBlock(scope: !3529, file: !1, line: 912, column: 11)
!3529 = distinct !DILexicalBlock(scope: !3524, file: !1, line: 911, column: 22)
!3530 = !DILocation(line: 912, column: 17, scope: !3528)
!3531 = !DILocation(line: 912, column: 11, scope: !3529)
!3532 = !DILocation(line: 913, column: 17, scope: !3528)
!3533 = !DILocation(line: 913, column: 15, scope: !3528)
!3534 = !DILocation(line: 913, column: 9, scope: !3528)
!3535 = !DILocation(line: 914, column: 7, scope: !3529)
!3536 = !DILocation(line: 917, column: 9, scope: !3537)
!3537 = distinct !DILexicalBlock(scope: !3506, file: !1, line: 917, column: 9)
!3538 = !DILocation(line: 917, column: 14, scope: !3537)
!3539 = !DILocation(line: 917, column: 18, scope: !3537)
!3540 = !DILocation(line: 917, column: 9, scope: !3506)
!3541 = !DILocation(line: 918, column: 19, scope: !3537)
!3542 = !DILocation(line: 918, column: 7, scope: !3537)
!3543 = !DILocation(line: 918, column: 12, scope: !3537)
!3544 = !DILocation(line: 918, column: 16, scope: !3537)
!3545 = !DILocation(line: 920, column: 18, scope: !3506)
!3546 = !DILocation(line: 920, column: 23, scope: !3506)
!3547 = !DILocation(line: 920, column: 5, scope: !3506)
!3548 = !DILocation(line: 920, column: 10, scope: !3506)
!3549 = !DILocation(line: 920, column: 15, scope: !3506)
!3550 = !DILocation(line: 921, column: 14, scope: !3506)
!3551 = !DILocation(line: 921, column: 19, scope: !3506)
!3552 = !DILocation(line: 921, column: 11, scope: !3506)
!3553 = !DILocation(line: 922, column: 14, scope: !3506)
!3554 = !DILocation(line: 922, column: 11, scope: !3506)
!3555 = !DILocation(line: 905, column: 3, scope: !3556)
!3556 = !DILexicalBlockFile(scope: !529, file: !1, discriminator: 2)
!3557 = !DILocation(line: 925, column: 7, scope: !3558)
!3558 = distinct !DILexicalBlock(scope: !529, file: !1, line: 925, column: 7)
!3559 = !DILocation(line: 925, column: 13, scope: !3558)
!3560 = !DILocation(line: 925, column: 22, scope: !3558)
!3561 = !DILocation(line: 925, column: 25, scope: !3562)
!3562 = !DILexicalBlockFile(scope: !3558, file: !1, discriminator: 1)
!3563 = !DILocation(line: 925, column: 31, scope: !3562)
!3564 = !DILocation(line: 925, column: 7, scope: !3562)
!3565 = !DILocation(line: 926, column: 12, scope: !3558)
!3566 = !DILocation(line: 926, column: 5, scope: !3558)
!3567 = !DILocation(line: 928, column: 7, scope: !3568)
!3568 = distinct !DILexicalBlock(scope: !529, file: !1, line: 928, column: 7)
!3569 = !DILocation(line: 928, column: 15, scope: !3568)
!3570 = !DILocation(line: 928, column: 20, scope: !3568)
!3571 = !DILocation(line: 928, column: 12, scope: !3568)
!3572 = !DILocation(line: 928, column: 7, scope: !529)
!3573 = !DILocation(line: 929, column: 14, scope: !3568)
!3574 = !DILocation(line: 929, column: 5, scope: !3568)
!3575 = !DILocation(line: 931, column: 3, scope: !529)
!3576 = !DILocation(line: 931, column: 8, scope: !529)
!3577 = !DILocation(line: 931, column: 13, scope: !529)
!3578 = !DILocation(line: 932, column: 3, scope: !529)
!3579 = !DILocation(line: 932, column: 8, scope: !529)
!3580 = !DILocation(line: 932, column: 14, scope: !529)
!3581 = !DILocation(line: 934, column: 10, scope: !529)
!3582 = !DILocation(line: 934, column: 3, scope: !529)
!3583 = !DILocation(line: 935, column: 1, scope: !529)
!3584 = !DILocalVariable(name: "req", arg: 1, scope: !534, file: !1, line: 301, type: !105)
!3585 = !DILocation(line: 301, column: 37, scope: !534)
!3586 = !DILocalVariable(name: "result", scope: !534, file: !1, line: 305, type: !325)
!3587 = !DILocation(line: 305, column: 11, scope: !534)
!3588 = !DILocation(line: 316, column: 7, scope: !3589)
!3589 = distinct !DILexicalBlock(scope: !534, file: !1, line: 316, column: 7)
!3590 = !DILocation(line: 316, column: 12, scope: !3589)
!3591 = !DILocation(line: 316, column: 16, scope: !3589)
!3592 = !DILocation(line: 316, column: 7, scope: !534)
!3593 = !DILocation(line: 317, column: 9, scope: !3594)
!3594 = distinct !DILexicalBlock(scope: !3595, file: !1, line: 317, column: 9)
!3595 = distinct !DILexicalBlock(scope: !3589, file: !1, line: 316, column: 21)
!3596 = !DILocation(line: 317, column: 14, scope: !3594)
!3597 = !DILocation(line: 317, column: 20, scope: !3594)
!3598 = !DILocation(line: 317, column: 9, scope: !3595)
!3599 = !DILocation(line: 318, column: 21, scope: !3594)
!3600 = !DILocation(line: 318, column: 26, scope: !3594)
!3601 = !DILocation(line: 318, column: 32, scope: !3594)
!3602 = !DILocation(line: 318, column: 37, scope: !3594)
!3603 = !DILocation(line: 318, column: 45, scope: !3594)
!3604 = !DILocation(line: 318, column: 51, scope: !3594)
!3605 = !DILocation(line: 318, column: 56, scope: !3594)
!3606 = !DILocation(line: 318, column: 64, scope: !3594)
!3607 = !DILocation(line: 318, column: 16, scope: !3594)
!3608 = !DILocation(line: 318, column: 14, scope: !3594)
!3609 = !DILocation(line: 318, column: 7, scope: !3594)
!3610 = !DILocation(line: 320, column: 22, scope: !3594)
!3611 = !DILocation(line: 320, column: 27, scope: !3594)
!3612 = !DILocation(line: 320, column: 49, scope: !3594)
!3613 = !DILocation(line: 320, column: 54, scope: !3594)
!3614 = !DILocation(line: 320, column: 33, scope: !3594)
!3615 = !DILocation(line: 320, column: 60, scope: !3594)
!3616 = !DILocation(line: 320, column: 65, scope: !3594)
!3617 = !DILocation(line: 320, column: 16, scope: !3594)
!3618 = !DILocation(line: 320, column: 14, scope: !3594)
!3619 = !DILocation(line: 321, column: 3, scope: !3595)
!3620 = !DILocation(line: 322, column: 9, scope: !3621)
!3621 = distinct !DILexicalBlock(scope: !3622, file: !1, line: 322, column: 9)
!3622 = distinct !DILexicalBlock(scope: !3589, file: !1, line: 321, column: 10)
!3623 = !DILocation(line: 322, column: 14, scope: !3621)
!3624 = !DILocation(line: 322, column: 20, scope: !3621)
!3625 = !DILocation(line: 322, column: 9, scope: !3622)
!3626 = !DILocation(line: 323, column: 22, scope: !3627)
!3627 = distinct !DILexicalBlock(scope: !3621, file: !1, line: 322, column: 26)
!3628 = !DILocation(line: 323, column: 27, scope: !3627)
!3629 = !DILocation(line: 323, column: 33, scope: !3627)
!3630 = !DILocation(line: 323, column: 38, scope: !3627)
!3631 = !DILocation(line: 323, column: 46, scope: !3627)
!3632 = !DILocation(line: 323, column: 52, scope: !3627)
!3633 = !DILocation(line: 323, column: 57, scope: !3627)
!3634 = !DILocation(line: 323, column: 65, scope: !3627)
!3635 = !DILocation(line: 323, column: 70, scope: !3627)
!3636 = !DILocation(line: 323, column: 75, scope: !3627)
!3637 = !DILocation(line: 323, column: 16, scope: !3627)
!3638 = !DILocation(line: 323, column: 14, scope: !3627)
!3639 = !DILocation(line: 324, column: 7, scope: !3627)
!3640 = !DILocation(line: 331, column: 9, scope: !3641)
!3641 = distinct !DILexicalBlock(scope: !3622, file: !1, line: 331, column: 9)
!3642 = !DILocation(line: 331, column: 9, scope: !3622)
!3643 = !DILocation(line: 331, column: 9, scope: !3644)
!3644 = !DILexicalBlockFile(scope: !3622, file: !1, discriminator: 1)
!3645 = !DILocalVariable(name: "nread", scope: !3646, file: !1, line: 334, type: !378)
!3646 = distinct !DILexicalBlock(scope: !3641, file: !1, line: 333, column: 5)
!3647 = !DILocation(line: 334, column: 13, scope: !3646)
!3648 = !DILocalVariable(name: "index", scope: !3646, file: !1, line: 335, type: !375)
!3649 = !DILocation(line: 335, column: 14, scope: !3646)
!3650 = !DILocation(line: 337, column: 13, scope: !3646)
!3651 = !DILocation(line: 338, column: 13, scope: !3646)
!3652 = !DILocation(line: 339, column: 14, scope: !3646)
!3653 = !DILocation(line: 340, column: 7, scope: !3646)
!3654 = !DILocation(line: 341, column: 23, scope: !3655)
!3655 = distinct !DILexicalBlock(scope: !3656, file: !1, line: 341, column: 13)
!3656 = distinct !DILexicalBlock(scope: !3646, file: !1, line: 340, column: 10)
!3657 = !DILocation(line: 341, column: 13, scope: !3655)
!3658 = !DILocation(line: 341, column: 18, scope: !3655)
!3659 = !DILocation(line: 341, column: 30, scope: !3655)
!3660 = !DILocation(line: 341, column: 34, scope: !3655)
!3661 = !DILocation(line: 341, column: 13, scope: !3656)
!3662 = !DILocation(line: 342, column: 26, scope: !3663)
!3663 = distinct !DILexicalBlock(scope: !3655, file: !1, line: 341, column: 39)
!3664 = !DILocation(line: 342, column: 31, scope: !3663)
!3665 = !DILocation(line: 343, column: 36, scope: !3663)
!3666 = !DILocation(line: 343, column: 26, scope: !3663)
!3667 = !DILocation(line: 343, column: 31, scope: !3663)
!3668 = !DILocation(line: 343, column: 43, scope: !3663)
!3669 = !DILocation(line: 344, column: 36, scope: !3663)
!3670 = !DILocation(line: 344, column: 26, scope: !3663)
!3671 = !DILocation(line: 344, column: 31, scope: !3663)
!3672 = !DILocation(line: 344, column: 43, scope: !3663)
!3673 = !DILocation(line: 345, column: 26, scope: !3663)
!3674 = !DILocation(line: 345, column: 31, scope: !3663)
!3675 = !DILocation(line: 345, column: 37, scope: !3663)
!3676 = !DILocation(line: 345, column: 35, scope: !3663)
!3677 = !DILocation(line: 342, column: 20, scope: !3663)
!3678 = !DILocation(line: 342, column: 18, scope: !3663)
!3679 = !DILocation(line: 346, column: 15, scope: !3680)
!3680 = distinct !DILexicalBlock(scope: !3663, file: !1, line: 346, column: 15)
!3681 = !DILocation(line: 346, column: 22, scope: !3680)
!3682 = !DILocation(line: 346, column: 15, scope: !3663)
!3683 = !DILocation(line: 347, column: 22, scope: !3680)
!3684 = !DILocation(line: 347, column: 19, scope: !3680)
!3685 = !DILocation(line: 347, column: 13, scope: !3680)
!3686 = !DILocation(line: 348, column: 9, scope: !3663)
!3687 = !DILocation(line: 349, column: 14, scope: !3656)
!3688 = !DILocation(line: 350, column: 7, scope: !3656)
!3689 = !DILocation(line: 350, column: 16, scope: !3690)
!3690 = !DILexicalBlockFile(scope: !3646, file: !1, discriminator: 1)
!3691 = !DILocation(line: 350, column: 24, scope: !3690)
!3692 = !DILocation(line: 350, column: 29, scope: !3690)
!3693 = !DILocation(line: 350, column: 22, scope: !3690)
!3694 = !DILocation(line: 350, column: 35, scope: !3690)
!3695 = !DILocation(line: 350, column: 38, scope: !3696)
!3696 = !DILexicalBlockFile(scope: !3646, file: !1, discriminator: 2)
!3697 = !DILocation(line: 350, column: 45, scope: !3696)
!3698 = !DILocation(line: 350, column: 7, scope: !3699)
!3699 = !DILexicalBlockFile(scope: !3656, file: !1, discriminator: 3)
!3700 = !DILocation(line: 351, column: 11, scope: !3701)
!3701 = distinct !DILexicalBlock(scope: !3646, file: !1, line: 351, column: 11)
!3702 = !DILocation(line: 351, column: 17, scope: !3701)
!3703 = !DILocation(line: 351, column: 11, scope: !3646)
!3704 = !DILocation(line: 352, column: 18, scope: !3701)
!3705 = !DILocation(line: 352, column: 16, scope: !3701)
!3706 = !DILocation(line: 352, column: 9, scope: !3701)
!3707 = !DILocation(line: 353, column: 5, scope: !3646)
!3708 = !DILocation(line: 356, column: 27, scope: !3709)
!3709 = distinct !DILexicalBlock(scope: !3641, file: !1, line: 355, column: 10)
!3710 = !DILocation(line: 356, column: 32, scope: !3709)
!3711 = !DILocation(line: 357, column: 42, scope: !3709)
!3712 = !DILocation(line: 357, column: 47, scope: !3709)
!3713 = !DILocation(line: 357, column: 27, scope: !3709)
!3714 = !DILocation(line: 358, column: 27, scope: !3709)
!3715 = !DILocation(line: 358, column: 32, scope: !3709)
!3716 = !DILocation(line: 359, column: 27, scope: !3709)
!3717 = !DILocation(line: 359, column: 32, scope: !3709)
!3718 = !DILocation(line: 356, column: 16, scope: !3709)
!3719 = !DILocation(line: 356, column: 14, scope: !3709)
!3720 = !DILocation(line: 360, column: 11, scope: !3721)
!3721 = distinct !DILexicalBlock(scope: !3709, file: !1, line: 360, column: 11)
!3722 = !DILocation(line: 360, column: 18, scope: !3721)
!3723 = !DILocation(line: 360, column: 24, scope: !3721)
!3724 = !DILocation(line: 360, column: 27, scope: !3725)
!3725 = !DILexicalBlockFile(scope: !3721, file: !1, discriminator: 1)
!3726 = !DILocation(line: 360, column: 33, scope: !3725)
!3727 = !DILocation(line: 360, column: 11, scope: !3725)
!3728 = !DILocation(line: 361, column: 19, scope: !3729)
!3729 = distinct !DILexicalBlock(scope: !3721, file: !1, line: 360, column: 44)
!3730 = !DILocation(line: 362, column: 9, scope: !3729)
!3731 = !DILocation(line: 316, column: 18, scope: !3732)
!3732 = !DILexicalBlockFile(scope: !3589, file: !1, discriminator: 1)
!3733 = !DILocation(line: 370, column: 10, scope: !534)
!3734 = !DILocation(line: 370, column: 3, scope: !534)
!3735 = !DILocalVariable(name: "req", arg: 1, scope: !535, file: !1, line: 391, type: !105)
!3736 = !DILocation(line: 391, column: 40, scope: !535)
!3737 = !DILocalVariable(name: "dents", scope: !535, file: !1, line: 392, type: !3738)
!3738 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !3739, size: 64, align: 64)
!3739 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !541, size: 64, align: 64)
!3740 = !DILocation(line: 392, column: 18, scope: !535)
!3741 = !DILocalVariable(name: "n", scope: !535, file: !1, line: 393, type: !133)
!3742 = !DILocation(line: 393, column: 7, scope: !535)
!3743 = !DILocation(line: 395, column: 9, scope: !535)
!3744 = !DILocation(line: 396, column: 15, scope: !535)
!3745 = !DILocation(line: 396, column: 20, scope: !535)
!3746 = !DILocation(line: 396, column: 7, scope: !535)
!3747 = !DILocation(line: 396, column: 5, scope: !535)
!3748 = !DILocation(line: 399, column: 3, scope: !535)
!3749 = !DILocation(line: 399, column: 8, scope: !535)
!3750 = !DILocation(line: 399, column: 14, scope: !535)
!3751 = !DILocation(line: 401, column: 7, scope: !3752)
!3752 = distinct !DILexicalBlock(scope: !535, file: !1, line: 401, column: 7)
!3753 = !DILocation(line: 401, column: 9, scope: !3752)
!3754 = !DILocation(line: 401, column: 7, scope: !535)
!3755 = !DILocation(line: 405, column: 10, scope: !3756)
!3756 = distinct !DILexicalBlock(scope: !3752, file: !1, line: 401, column: 15)
!3757 = !DILocation(line: 405, column: 5, scope: !3756)
!3758 = !DILocation(line: 406, column: 11, scope: !3756)
!3759 = !DILocation(line: 407, column: 3, scope: !3756)
!3760 = !DILocation(line: 407, column: 14, scope: !3761)
!3761 = !DILexicalBlockFile(scope: !3762, file: !1, discriminator: 1)
!3762 = distinct !DILexicalBlock(scope: !3752, file: !1, line: 407, column: 14)
!3763 = !DILocation(line: 407, column: 16, scope: !3761)
!3764 = !DILocation(line: 408, column: 12, scope: !3765)
!3765 = distinct !DILexicalBlock(scope: !3762, file: !1, line: 407, column: 23)
!3766 = !DILocation(line: 408, column: 5, scope: !3765)
!3767 = !DILocation(line: 411, column: 14, scope: !535)
!3768 = !DILocation(line: 411, column: 3, scope: !535)
!3769 = !DILocation(line: 411, column: 8, scope: !535)
!3770 = !DILocation(line: 411, column: 12, scope: !535)
!3771 = !DILocation(line: 413, column: 10, scope: !535)
!3772 = !DILocation(line: 413, column: 3, scope: !535)
!3773 = !DILocation(line: 414, column: 1, scope: !535)
!3774 = !DILocalVariable(name: "req", arg: 1, scope: !560, file: !1, line: 433, type: !105)
!3775 = !DILocation(line: 433, column: 41, scope: !560)
!3776 = !DILocalVariable(name: "len", scope: !560, file: !1, line: 434, type: !325)
!3777 = !DILocation(line: 434, column: 11, scope: !560)
!3778 = !DILocalVariable(name: "buf", scope: !560, file: !1, line: 435, type: !373)
!3779 = !DILocation(line: 435, column: 9, scope: !560)
!3780 = !DILocation(line: 437, column: 29, scope: !560)
!3781 = !DILocation(line: 437, column: 34, scope: !560)
!3782 = !DILocation(line: 437, column: 9, scope: !560)
!3783 = !DILocation(line: 437, column: 7, scope: !560)
!3784 = !DILocation(line: 438, column: 20, scope: !560)
!3785 = !DILocation(line: 438, column: 24, scope: !560)
!3786 = !DILocation(line: 438, column: 9, scope: !560)
!3787 = !DILocation(line: 438, column: 7, scope: !560)
!3788 = !DILocation(line: 440, column: 7, scope: !3789)
!3789 = distinct !DILexicalBlock(scope: !560, file: !1, line: 440, column: 7)
!3790 = !DILocation(line: 440, column: 11, scope: !3789)
!3791 = !DILocation(line: 440, column: 7, scope: !560)
!3792 = !DILocation(line: 441, column: 5, scope: !3793)
!3793 = distinct !DILexicalBlock(scope: !3789, file: !1, line: 440, column: 20)
!3794 = !DILocation(line: 441, column: 11, scope: !3793)
!3795 = !DILocation(line: 442, column: 5, scope: !3793)
!3796 = !DILocation(line: 445, column: 18, scope: !560)
!3797 = !DILocation(line: 445, column: 23, scope: !560)
!3798 = !DILocation(line: 445, column: 29, scope: !560)
!3799 = !DILocation(line: 445, column: 34, scope: !560)
!3800 = !DILocation(line: 445, column: 9, scope: !560)
!3801 = !DILocation(line: 445, column: 7, scope: !560)
!3802 = !DILocation(line: 447, column: 7, scope: !3803)
!3803 = distinct !DILexicalBlock(scope: !560, file: !1, line: 447, column: 7)
!3804 = !DILocation(line: 447, column: 11, scope: !3803)
!3805 = !DILocation(line: 447, column: 7, scope: !560)
!3806 = !DILocation(line: 448, column: 14, scope: !3807)
!3807 = distinct !DILexicalBlock(scope: !3803, file: !1, line: 447, column: 18)
!3808 = !DILocation(line: 448, column: 5, scope: !3807)
!3809 = !DILocation(line: 449, column: 5, scope: !3807)
!3810 = !DILocation(line: 452, column: 7, scope: !560)
!3811 = !DILocation(line: 452, column: 3, scope: !560)
!3812 = !DILocation(line: 452, column: 12, scope: !560)
!3813 = !DILocation(line: 453, column: 14, scope: !560)
!3814 = !DILocation(line: 453, column: 3, scope: !560)
!3815 = !DILocation(line: 453, column: 8, scope: !560)
!3816 = !DILocation(line: 453, column: 12, scope: !560)
!3817 = !DILocation(line: 455, column: 3, scope: !560)
!3818 = !DILocation(line: 456, column: 1, scope: !560)
!3819 = !DILocalVariable(name: "req", arg: 1, scope: !564, file: !1, line: 458, type: !105)
!3820 = !DILocation(line: 458, column: 41, scope: !564)
!3821 = !DILocalVariable(name: "len", scope: !564, file: !1, line: 459, type: !325)
!3822 = !DILocation(line: 459, column: 11, scope: !564)
!3823 = !DILocalVariable(name: "buf", scope: !564, file: !1, line: 460, type: !373)
!3824 = !DILocation(line: 460, column: 9, scope: !564)
!3825 = !DILocation(line: 462, column: 29, scope: !564)
!3826 = !DILocation(line: 462, column: 34, scope: !564)
!3827 = !DILocation(line: 462, column: 9, scope: !564)
!3828 = !DILocation(line: 462, column: 7, scope: !564)
!3829 = !DILocation(line: 463, column: 20, scope: !564)
!3830 = !DILocation(line: 463, column: 24, scope: !564)
!3831 = !DILocation(line: 463, column: 9, scope: !564)
!3832 = !DILocation(line: 463, column: 7, scope: !564)
!3833 = !DILocation(line: 465, column: 7, scope: !3834)
!3834 = distinct !DILexicalBlock(scope: !564, file: !1, line: 465, column: 7)
!3835 = !DILocation(line: 465, column: 11, scope: !3834)
!3836 = !DILocation(line: 465, column: 7, scope: !564)
!3837 = !DILocation(line: 466, column: 5, scope: !3838)
!3838 = distinct !DILexicalBlock(scope: !3834, file: !1, line: 465, column: 20)
!3839 = !DILocation(line: 466, column: 11, scope: !3838)
!3840 = !DILocation(line: 467, column: 5, scope: !3838)
!3841 = !DILocation(line: 470, column: 16, scope: !3842)
!3842 = distinct !DILexicalBlock(scope: !564, file: !1, line: 470, column: 7)
!3843 = !DILocation(line: 470, column: 21, scope: !3842)
!3844 = !DILocation(line: 470, column: 27, scope: !3842)
!3845 = !DILocation(line: 470, column: 7, scope: !3842)
!3846 = !DILocation(line: 470, column: 32, scope: !3842)
!3847 = !DILocation(line: 470, column: 7, scope: !564)
!3848 = !DILocation(line: 471, column: 14, scope: !3849)
!3849 = distinct !DILexicalBlock(scope: !3842, file: !1, line: 470, column: 41)
!3850 = !DILocation(line: 471, column: 5, scope: !3849)
!3851 = !DILocation(line: 472, column: 5, scope: !3849)
!3852 = !DILocation(line: 475, column: 14, scope: !564)
!3853 = !DILocation(line: 475, column: 3, scope: !564)
!3854 = !DILocation(line: 475, column: 8, scope: !564)
!3855 = !DILocation(line: 475, column: 12, scope: !564)
!3856 = !DILocation(line: 477, column: 3, scope: !564)
!3857 = !DILocation(line: 478, column: 1, scope: !564)
!3858 = !DILocalVariable(name: "req", arg: 1, scope: !565, file: !1, line: 594, type: !105)
!3859 = !DILocation(line: 594, column: 41, scope: !565)
!3860 = !DILocalVariable(name: "in_fd", scope: !565, file: !1, line: 595, type: !133)
!3861 = !DILocation(line: 595, column: 7, scope: !565)
!3862 = !DILocalVariable(name: "out_fd", scope: !565, file: !1, line: 596, type: !133)
!3863 = !DILocation(line: 596, column: 7, scope: !565)
!3864 = !DILocation(line: 598, column: 11, scope: !565)
!3865 = !DILocation(line: 598, column: 16, scope: !565)
!3866 = !DILocation(line: 598, column: 9, scope: !565)
!3867 = !DILocation(line: 599, column: 12, scope: !565)
!3868 = !DILocation(line: 599, column: 17, scope: !565)
!3869 = !DILocation(line: 599, column: 10, scope: !565)
!3870 = !DILocalVariable(name: "off", scope: !3871, file: !1, line: 603, type: !378)
!3871 = distinct !DILexicalBlock(scope: !565, file: !1, line: 602, column: 3)
!3872 = !DILocation(line: 603, column: 11, scope: !3871)
!3873 = !DILocalVariable(name: "r", scope: !3871, file: !1, line: 604, type: !325)
!3874 = !DILocation(line: 604, column: 13, scope: !3871)
!3875 = !DILocation(line: 606, column: 11, scope: !3871)
!3876 = !DILocation(line: 606, column: 16, scope: !3871)
!3877 = !DILocation(line: 606, column: 9, scope: !3871)
!3878 = !DILocation(line: 607, column: 18, scope: !3871)
!3879 = !DILocation(line: 607, column: 26, scope: !3871)
!3880 = !DILocation(line: 607, column: 39, scope: !3871)
!3881 = !DILocation(line: 607, column: 44, scope: !3871)
!3882 = !DILocation(line: 607, column: 54, scope: !3871)
!3883 = !DILocation(line: 607, column: 9, scope: !3871)
!3884 = !DILocation(line: 607, column: 7, scope: !3871)
!3885 = !DILocation(line: 613, column: 9, scope: !3886)
!3886 = distinct !DILexicalBlock(scope: !3871, file: !1, line: 613, column: 9)
!3887 = !DILocation(line: 613, column: 11, scope: !3886)
!3888 = !DILocation(line: 613, column: 17, scope: !3886)
!3889 = !DILocation(line: 613, column: 20, scope: !3890)
!3890 = !DILexicalBlockFile(scope: !3886, file: !1, discriminator: 1)
!3891 = !DILocation(line: 613, column: 26, scope: !3890)
!3892 = !DILocation(line: 613, column: 31, scope: !3890)
!3893 = !DILocation(line: 613, column: 24, scope: !3890)
!3894 = !DILocation(line: 613, column: 9, scope: !3890)
!3895 = !DILocation(line: 614, column: 11, scope: !3896)
!3896 = distinct !DILexicalBlock(scope: !3886, file: !1, line: 613, column: 36)
!3897 = !DILocation(line: 614, column: 17, scope: !3896)
!3898 = !DILocation(line: 614, column: 22, scope: !3896)
!3899 = !DILocation(line: 614, column: 15, scope: !3896)
!3900 = !DILocation(line: 614, column: 9, scope: !3896)
!3901 = !DILocation(line: 615, column: 18, scope: !3896)
!3902 = !DILocation(line: 615, column: 7, scope: !3896)
!3903 = !DILocation(line: 615, column: 12, scope: !3896)
!3904 = !DILocation(line: 615, column: 16, scope: !3896)
!3905 = !DILocation(line: 616, column: 14, scope: !3896)
!3906 = !DILocation(line: 616, column: 7, scope: !3896)
!3907 = !DILocation(line: 619, column: 9, scope: !3908)
!3908 = distinct !DILexicalBlock(scope: !3871, file: !1, line: 619, column: 9)
!3909 = !DILocation(line: 619, column: 15, scope: !3908)
!3910 = !DILocation(line: 619, column: 25, scope: !3908)
!3911 = !DILocation(line: 620, column: 9, scope: !3908)
!3912 = !DILocation(line: 620, column: 15, scope: !3908)
!3913 = !DILocation(line: 620, column: 22, scope: !3908)
!3914 = !DILocation(line: 621, column: 9, scope: !3908)
!3915 = !DILocation(line: 621, column: 15, scope: !3908)
!3916 = !DILocation(line: 621, column: 27, scope: !3908)
!3917 = !DILocation(line: 622, column: 9, scope: !3908)
!3918 = !DILocation(line: 622, column: 15, scope: !3908)
!3919 = !DILocation(line: 619, column: 9, scope: !3920)
!3920 = !DILexicalBlockFile(scope: !3871, file: !1, discriminator: 1)
!3921 = !DILocation(line: 623, column: 7, scope: !3922)
!3922 = distinct !DILexicalBlock(scope: !3908, file: !1, line: 622, column: 25)
!3923 = !DILocation(line: 623, column: 13, scope: !3922)
!3924 = !DILocation(line: 624, column: 35, scope: !3922)
!3925 = !DILocation(line: 624, column: 14, scope: !3922)
!3926 = !DILocation(line: 624, column: 7, scope: !3922)
!3927 = !DILocation(line: 627, column: 5, scope: !3871)
!3928 = !DILocation(line: 690, column: 1, scope: !565)
!3929 = !DILocalVariable(name: "path", arg: 1, scope: !567, file: !1, line: 856, type: !331)
!3930 = !DILocation(line: 856, column: 36, scope: !567)
!3931 = !DILocalVariable(name: "buf", arg: 2, scope: !567, file: !1, line: 856, type: !483)
!3932 = !DILocation(line: 856, column: 53, scope: !567)
!3933 = !DILocalVariable(name: "pbuf", scope: !567, file: !1, line: 857, type: !488)
!3934 = !DILocation(line: 857, column: 15, scope: !567)
!3935 = !DILocalVariable(name: "ret", scope: !567, file: !1, line: 858, type: !133)
!3936 = !DILocation(line: 858, column: 7, scope: !567)
!3937 = !DILocation(line: 860, column: 14, scope: !567)
!3938 = !DILocation(line: 860, column: 9, scope: !567)
!3939 = !DILocation(line: 860, column: 7, scope: !567)
!3940 = !DILocation(line: 861, column: 7, scope: !3941)
!3941 = distinct !DILexicalBlock(scope: !567, file: !1, line: 861, column: 7)
!3942 = !DILocation(line: 861, column: 11, scope: !3941)
!3943 = !DILocation(line: 861, column: 7, scope: !567)
!3944 = !DILocation(line: 862, column: 24, scope: !3941)
!3945 = !DILocation(line: 862, column: 5, scope: !3941)
!3946 = !DILocation(line: 864, column: 10, scope: !567)
!3947 = !DILocation(line: 864, column: 3, scope: !567)
!3948 = !DILocalVariable(name: "req", arg: 1, scope: !568, file: !1, line: 693, type: !105)
!3949 = !DILocation(line: 693, column: 38, scope: !568)
!3950 = !DILocalVariable(name: "buf", scope: !568, file: !1, line: 694, type: !3951)
!3951 = !DICompositeType(tag: DW_TAG_structure_type, name: "utimbuf", file: !3952, line: 37, size: 128, align: 64, elements: !3953)
!3952 = !DIFile(filename: "/usr/include/utime.h", directory: "/data/download/cmake/cmake-master/Utilities/cmlibuv")
!3953 = !{!3954, !3955}
!3954 = !DIDerivedType(tag: DW_TAG_member, name: "actime", scope: !3951, file: !3952, line: 39, baseType: !513, size: 64, align: 64)
!3955 = !DIDerivedType(tag: DW_TAG_member, name: "modtime", scope: !3951, file: !3952, line: 40, baseType: !513, size: 64, align: 64, offset: 64)
!3956 = !DILocation(line: 694, column: 18, scope: !568)
!3957 = !DILocation(line: 695, column: 16, scope: !568)
!3958 = !DILocation(line: 695, column: 21, scope: !568)
!3959 = !DILocation(line: 695, column: 7, scope: !568)
!3960 = !DILocation(line: 695, column: 14, scope: !568)
!3961 = !DILocation(line: 696, column: 17, scope: !568)
!3962 = !DILocation(line: 696, column: 22, scope: !568)
!3963 = !DILocation(line: 696, column: 7, scope: !568)
!3964 = !DILocation(line: 696, column: 15, scope: !568)
!3965 = !DILocation(line: 697, column: 16, scope: !568)
!3966 = !DILocation(line: 697, column: 21, scope: !568)
!3967 = !DILocation(line: 697, column: 10, scope: !568)
!3968 = !DILocation(line: 697, column: 3, scope: !568)
!3969 = !DILocalVariable(name: "req", arg: 1, scope: !569, file: !1, line: 701, type: !105)
!3970 = !DILocation(line: 701, column: 38, scope: !569)
!3971 = !DILocalVariable(name: "r", scope: !569, file: !1, line: 705, type: !325)
!3972 = !DILocation(line: 705, column: 11, scope: !569)
!3973 = !DILocation(line: 718, column: 7, scope: !3974)
!3974 = distinct !DILexicalBlock(scope: !569, file: !1, line: 718, column: 7)
!3975 = !DILocation(line: 718, column: 12, scope: !3974)
!3976 = !DILocation(line: 718, column: 16, scope: !3974)
!3977 = !DILocation(line: 718, column: 7, scope: !569)
!3978 = !DILocation(line: 719, column: 9, scope: !3979)
!3979 = distinct !DILexicalBlock(scope: !3980, file: !1, line: 719, column: 9)
!3980 = distinct !DILexicalBlock(scope: !3974, file: !1, line: 718, column: 21)
!3981 = !DILocation(line: 719, column: 14, scope: !3979)
!3982 = !DILocation(line: 719, column: 20, scope: !3979)
!3983 = !DILocation(line: 719, column: 9, scope: !3980)
!3984 = !DILocation(line: 720, column: 17, scope: !3979)
!3985 = !DILocation(line: 720, column: 22, scope: !3979)
!3986 = !DILocation(line: 720, column: 28, scope: !3979)
!3987 = !DILocation(line: 720, column: 33, scope: !3979)
!3988 = !DILocation(line: 720, column: 41, scope: !3979)
!3989 = !DILocation(line: 720, column: 47, scope: !3979)
!3990 = !DILocation(line: 720, column: 52, scope: !3979)
!3991 = !DILocation(line: 720, column: 60, scope: !3979)
!3992 = !DILocation(line: 720, column: 11, scope: !3979)
!3993 = !DILocation(line: 720, column: 9, scope: !3979)
!3994 = !DILocation(line: 720, column: 7, scope: !3979)
!3995 = !DILocation(line: 722, column: 18, scope: !3979)
!3996 = !DILocation(line: 722, column: 23, scope: !3979)
!3997 = !DILocation(line: 722, column: 45, scope: !3979)
!3998 = !DILocation(line: 722, column: 50, scope: !3979)
!3999 = !DILocation(line: 722, column: 29, scope: !3979)
!4000 = !DILocation(line: 722, column: 56, scope: !3979)
!4001 = !DILocation(line: 722, column: 61, scope: !3979)
!4002 = !DILocation(line: 722, column: 11, scope: !3979)
!4003 = !DILocation(line: 722, column: 9, scope: !3979)
!4004 = !DILocation(line: 723, column: 3, scope: !3980)
!4005 = !DILocation(line: 724, column: 9, scope: !4006)
!4006 = distinct !DILexicalBlock(scope: !4007, file: !1, line: 724, column: 9)
!4007 = distinct !DILexicalBlock(scope: !3974, file: !1, line: 723, column: 10)
!4008 = !DILocation(line: 724, column: 14, scope: !4006)
!4009 = !DILocation(line: 724, column: 20, scope: !4006)
!4010 = !DILocation(line: 724, column: 9, scope: !4007)
!4011 = !DILocation(line: 725, column: 18, scope: !4012)
!4012 = distinct !DILexicalBlock(scope: !4006, file: !1, line: 724, column: 26)
!4013 = !DILocation(line: 725, column: 23, scope: !4012)
!4014 = !DILocation(line: 725, column: 29, scope: !4012)
!4015 = !DILocation(line: 725, column: 34, scope: !4012)
!4016 = !DILocation(line: 725, column: 42, scope: !4012)
!4017 = !DILocation(line: 725, column: 48, scope: !4012)
!4018 = !DILocation(line: 725, column: 53, scope: !4012)
!4019 = !DILocation(line: 725, column: 61, scope: !4012)
!4020 = !DILocation(line: 725, column: 66, scope: !4012)
!4021 = !DILocation(line: 725, column: 71, scope: !4012)
!4022 = !DILocation(line: 725, column: 11, scope: !4012)
!4023 = !DILocation(line: 725, column: 9, scope: !4012)
!4024 = !DILocation(line: 726, column: 7, scope: !4012)
!4025 = !DILocation(line: 732, column: 9, scope: !4026)
!4026 = distinct !DILexicalBlock(scope: !4007, file: !1, line: 732, column: 9)
!4027 = !DILocation(line: 732, column: 9, scope: !4007)
!4028 = !DILocation(line: 732, column: 9, scope: !4029)
!4029 = !DILexicalBlockFile(scope: !4007, file: !1, discriminator: 1)
!4030 = !DILocalVariable(name: "written", scope: !4031, file: !1, line: 735, type: !378)
!4031 = distinct !DILexicalBlock(scope: !4026, file: !1, line: 734, column: 5)
!4032 = !DILocation(line: 735, column: 13, scope: !4031)
!4033 = !DILocalVariable(name: "index", scope: !4031, file: !1, line: 736, type: !375)
!4034 = !DILocation(line: 736, column: 14, scope: !4031)
!4035 = !DILocation(line: 738, column: 15, scope: !4031)
!4036 = !DILocation(line: 739, column: 13, scope: !4031)
!4037 = !DILocation(line: 740, column: 9, scope: !4031)
!4038 = !DILocation(line: 741, column: 7, scope: !4031)
!4039 = !DILocation(line: 742, column: 23, scope: !4040)
!4040 = distinct !DILexicalBlock(scope: !4041, file: !1, line: 742, column: 13)
!4041 = distinct !DILexicalBlock(scope: !4031, file: !1, line: 741, column: 10)
!4042 = !DILocation(line: 742, column: 13, scope: !4040)
!4043 = !DILocation(line: 742, column: 18, scope: !4040)
!4044 = !DILocation(line: 742, column: 30, scope: !4040)
!4045 = !DILocation(line: 742, column: 34, scope: !4040)
!4046 = !DILocation(line: 742, column: 13, scope: !4041)
!4047 = !DILocation(line: 743, column: 22, scope: !4048)
!4048 = distinct !DILexicalBlock(scope: !4040, file: !1, line: 742, column: 39)
!4049 = !DILocation(line: 743, column: 27, scope: !4048)
!4050 = !DILocation(line: 744, column: 32, scope: !4048)
!4051 = !DILocation(line: 744, column: 22, scope: !4048)
!4052 = !DILocation(line: 744, column: 27, scope: !4048)
!4053 = !DILocation(line: 744, column: 39, scope: !4048)
!4054 = !DILocation(line: 745, column: 32, scope: !4048)
!4055 = !DILocation(line: 745, column: 22, scope: !4048)
!4056 = !DILocation(line: 745, column: 27, scope: !4048)
!4057 = !DILocation(line: 745, column: 39, scope: !4048)
!4058 = !DILocation(line: 746, column: 22, scope: !4048)
!4059 = !DILocation(line: 746, column: 27, scope: !4048)
!4060 = !DILocation(line: 746, column: 33, scope: !4048)
!4061 = !DILocation(line: 746, column: 31, scope: !4048)
!4062 = !DILocation(line: 743, column: 15, scope: !4048)
!4063 = !DILocation(line: 743, column: 13, scope: !4048)
!4064 = !DILocation(line: 747, column: 15, scope: !4065)
!4065 = distinct !DILexicalBlock(scope: !4048, file: !1, line: 747, column: 15)
!4066 = !DILocation(line: 747, column: 17, scope: !4065)
!4067 = !DILocation(line: 747, column: 15, scope: !4048)
!4068 = !DILocation(line: 748, column: 24, scope: !4065)
!4069 = !DILocation(line: 748, column: 21, scope: !4065)
!4070 = !DILocation(line: 748, column: 13, scope: !4065)
!4071 = !DILocation(line: 749, column: 9, scope: !4048)
!4072 = !DILocation(line: 750, column: 14, scope: !4041)
!4073 = !DILocation(line: 751, column: 7, scope: !4041)
!4074 = !DILocation(line: 751, column: 16, scope: !4075)
!4075 = !DILexicalBlockFile(scope: !4031, file: !1, discriminator: 1)
!4076 = !DILocation(line: 751, column: 24, scope: !4075)
!4077 = !DILocation(line: 751, column: 29, scope: !4075)
!4078 = !DILocation(line: 751, column: 22, scope: !4075)
!4079 = !DILocation(line: 751, column: 35, scope: !4075)
!4080 = !DILocation(line: 751, column: 38, scope: !4081)
!4081 = !DILexicalBlockFile(scope: !4031, file: !1, discriminator: 2)
!4082 = !DILocation(line: 751, column: 40, scope: !4081)
!4083 = !DILocation(line: 751, column: 7, scope: !4084)
!4084 = !DILexicalBlockFile(scope: !4041, file: !1, discriminator: 3)
!4085 = !DILocation(line: 752, column: 11, scope: !4086)
!4086 = distinct !DILexicalBlock(scope: !4031, file: !1, line: 752, column: 11)
!4087 = !DILocation(line: 752, column: 19, scope: !4086)
!4088 = !DILocation(line: 752, column: 11, scope: !4031)
!4089 = !DILocation(line: 753, column: 13, scope: !4086)
!4090 = !DILocation(line: 753, column: 11, scope: !4086)
!4091 = !DILocation(line: 753, column: 9, scope: !4086)
!4092 = !DILocation(line: 754, column: 5, scope: !4031)
!4093 = !DILocation(line: 757, column: 23, scope: !4094)
!4094 = distinct !DILexicalBlock(scope: !4026, file: !1, line: 756, column: 10)
!4095 = !DILocation(line: 757, column: 28, scope: !4094)
!4096 = !DILocation(line: 758, column: 39, scope: !4094)
!4097 = !DILocation(line: 758, column: 44, scope: !4094)
!4098 = !DILocation(line: 758, column: 23, scope: !4094)
!4099 = !DILocation(line: 759, column: 23, scope: !4094)
!4100 = !DILocation(line: 759, column: 28, scope: !4094)
!4101 = !DILocation(line: 760, column: 23, scope: !4094)
!4102 = !DILocation(line: 760, column: 28, scope: !4094)
!4103 = !DILocation(line: 757, column: 11, scope: !4094)
!4104 = !DILocation(line: 757, column: 9, scope: !4094)
!4105 = !DILocation(line: 761, column: 11, scope: !4106)
!4106 = distinct !DILexicalBlock(scope: !4094, file: !1, line: 761, column: 11)
!4107 = !DILocation(line: 761, column: 13, scope: !4106)
!4108 = !DILocation(line: 761, column: 19, scope: !4106)
!4109 = !DILocation(line: 761, column: 22, scope: !4110)
!4110 = !DILexicalBlockFile(scope: !4106, file: !1, discriminator: 1)
!4111 = !DILocation(line: 761, column: 28, scope: !4110)
!4112 = !DILocation(line: 761, column: 11, scope: !4110)
!4113 = !DILocation(line: 762, column: 20, scope: !4114)
!4114 = distinct !DILexicalBlock(scope: !4106, file: !1, line: 761, column: 39)
!4115 = !DILocation(line: 763, column: 9, scope: !4114)
!4116 = !DILocation(line: 718, column: 18, scope: !4117)
!4117 = !DILexicalBlockFile(scope: !3974, file: !1, discriminator: 1)
!4118 = !DILocation(line: 776, column: 10, scope: !569)
!4119 = !DILocation(line: 776, column: 3, scope: !569)
!4120 = !DILocalVariable(name: "src", arg: 1, scope: !484, file: !1, line: 779, type: !487)
!4121 = !DILocation(line: 779, column: 38, scope: !484)
!4122 = !DILocalVariable(name: "dst", arg: 2, scope: !484, file: !1, line: 779, type: !483)
!4123 = !DILocation(line: 779, column: 54, scope: !484)
!4124 = !DILocation(line: 780, column: 17, scope: !484)
!4125 = !DILocation(line: 780, column: 22, scope: !484)
!4126 = !DILocation(line: 780, column: 3, scope: !484)
!4127 = !DILocation(line: 780, column: 8, scope: !484)
!4128 = !DILocation(line: 780, column: 15, scope: !484)
!4129 = !DILocation(line: 781, column: 18, scope: !484)
!4130 = !DILocation(line: 781, column: 23, scope: !484)
!4131 = !DILocation(line: 781, column: 3, scope: !484)
!4132 = !DILocation(line: 781, column: 8, scope: !484)
!4133 = !DILocation(line: 781, column: 16, scope: !484)
!4134 = !DILocation(line: 782, column: 19, scope: !484)
!4135 = !DILocation(line: 782, column: 24, scope: !484)
!4136 = !DILocation(line: 782, column: 3, scope: !484)
!4137 = !DILocation(line: 782, column: 8, scope: !484)
!4138 = !DILocation(line: 782, column: 17, scope: !484)
!4139 = !DILocation(line: 783, column: 17, scope: !484)
!4140 = !DILocation(line: 783, column: 22, scope: !484)
!4141 = !DILocation(line: 783, column: 3, scope: !484)
!4142 = !DILocation(line: 783, column: 8, scope: !484)
!4143 = !DILocation(line: 783, column: 15, scope: !484)
!4144 = !DILocation(line: 784, column: 17, scope: !484)
!4145 = !DILocation(line: 784, column: 22, scope: !484)
!4146 = !DILocation(line: 784, column: 3, scope: !484)
!4147 = !DILocation(line: 784, column: 8, scope: !484)
!4148 = !DILocation(line: 784, column: 15, scope: !484)
!4149 = !DILocation(line: 785, column: 18, scope: !484)
!4150 = !DILocation(line: 785, column: 23, scope: !484)
!4151 = !DILocation(line: 785, column: 3, scope: !484)
!4152 = !DILocation(line: 785, column: 8, scope: !484)
!4153 = !DILocation(line: 785, column: 16, scope: !484)
!4154 = !DILocation(line: 786, column: 17, scope: !484)
!4155 = !DILocation(line: 786, column: 22, scope: !484)
!4156 = !DILocation(line: 786, column: 3, scope: !484)
!4157 = !DILocation(line: 786, column: 8, scope: !484)
!4158 = !DILocation(line: 786, column: 15, scope: !484)
!4159 = !DILocation(line: 787, column: 18, scope: !484)
!4160 = !DILocation(line: 787, column: 23, scope: !484)
!4161 = !DILocation(line: 787, column: 3, scope: !484)
!4162 = !DILocation(line: 787, column: 8, scope: !484)
!4163 = !DILocation(line: 787, column: 16, scope: !484)
!4164 = !DILocation(line: 788, column: 21, scope: !484)
!4165 = !DILocation(line: 788, column: 26, scope: !484)
!4166 = !DILocation(line: 788, column: 3, scope: !484)
!4167 = !DILocation(line: 788, column: 8, scope: !484)
!4168 = !DILocation(line: 788, column: 19, scope: !484)
!4169 = !DILocation(line: 789, column: 20, scope: !484)
!4170 = !DILocation(line: 789, column: 25, scope: !484)
!4171 = !DILocation(line: 789, column: 3, scope: !484)
!4172 = !DILocation(line: 789, column: 8, scope: !484)
!4173 = !DILocation(line: 789, column: 18, scope: !484)
!4174 = !DILocation(line: 823, column: 25, scope: !484)
!4175 = !DILocation(line: 823, column: 30, scope: !484)
!4176 = !DILocation(line: 823, column: 38, scope: !484)
!4177 = !DILocation(line: 823, column: 3, scope: !484)
!4178 = !DILocation(line: 823, column: 8, scope: !484)
!4179 = !DILocation(line: 823, column: 16, scope: !484)
!4180 = !DILocation(line: 823, column: 23, scope: !484)
!4181 = !DILocation(line: 824, column: 26, scope: !484)
!4182 = !DILocation(line: 824, column: 31, scope: !484)
!4183 = !DILocation(line: 824, column: 39, scope: !484)
!4184 = !DILocation(line: 824, column: 3, scope: !484)
!4185 = !DILocation(line: 824, column: 8, scope: !484)
!4186 = !DILocation(line: 824, column: 16, scope: !484)
!4187 = !DILocation(line: 824, column: 24, scope: !484)
!4188 = !DILocation(line: 825, column: 25, scope: !484)
!4189 = !DILocation(line: 825, column: 30, scope: !484)
!4190 = !DILocation(line: 825, column: 38, scope: !484)
!4191 = !DILocation(line: 825, column: 3, scope: !484)
!4192 = !DILocation(line: 825, column: 8, scope: !484)
!4193 = !DILocation(line: 825, column: 16, scope: !484)
!4194 = !DILocation(line: 825, column: 23, scope: !484)
!4195 = !DILocation(line: 826, column: 26, scope: !484)
!4196 = !DILocation(line: 826, column: 31, scope: !484)
!4197 = !DILocation(line: 826, column: 39, scope: !484)
!4198 = !DILocation(line: 826, column: 3, scope: !484)
!4199 = !DILocation(line: 826, column: 8, scope: !484)
!4200 = !DILocation(line: 826, column: 16, scope: !484)
!4201 = !DILocation(line: 826, column: 24, scope: !484)
!4202 = !DILocation(line: 827, column: 25, scope: !484)
!4203 = !DILocation(line: 827, column: 30, scope: !484)
!4204 = !DILocation(line: 827, column: 38, scope: !484)
!4205 = !DILocation(line: 827, column: 3, scope: !484)
!4206 = !DILocation(line: 827, column: 8, scope: !484)
!4207 = !DILocation(line: 827, column: 16, scope: !484)
!4208 = !DILocation(line: 827, column: 23, scope: !484)
!4209 = !DILocation(line: 828, column: 26, scope: !484)
!4210 = !DILocation(line: 828, column: 31, scope: !484)
!4211 = !DILocation(line: 828, column: 39, scope: !484)
!4212 = !DILocation(line: 828, column: 3, scope: !484)
!4213 = !DILocation(line: 828, column: 8, scope: !484)
!4214 = !DILocation(line: 828, column: 16, scope: !484)
!4215 = !DILocation(line: 828, column: 24, scope: !484)
!4216 = !DILocation(line: 836, column: 29, scope: !484)
!4217 = !DILocation(line: 836, column: 34, scope: !484)
!4218 = !DILocation(line: 836, column: 42, scope: !484)
!4219 = !DILocation(line: 836, column: 3, scope: !484)
!4220 = !DILocation(line: 836, column: 8, scope: !484)
!4221 = !DILocation(line: 836, column: 20, scope: !484)
!4222 = !DILocation(line: 836, column: 27, scope: !484)
!4223 = !DILocation(line: 837, column: 30, scope: !484)
!4224 = !DILocation(line: 837, column: 35, scope: !484)
!4225 = !DILocation(line: 837, column: 43, scope: !484)
!4226 = !DILocation(line: 837, column: 3, scope: !484)
!4227 = !DILocation(line: 837, column: 8, scope: !484)
!4228 = !DILocation(line: 837, column: 20, scope: !484)
!4229 = !DILocation(line: 837, column: 28, scope: !484)
!4230 = !DILocation(line: 838, column: 3, scope: !484)
!4231 = !DILocation(line: 838, column: 8, scope: !484)
!4232 = !DILocation(line: 838, column: 17, scope: !484)
!4233 = !DILocation(line: 839, column: 3, scope: !484)
!4234 = !DILocation(line: 839, column: 8, scope: !484)
!4235 = !DILocation(line: 839, column: 15, scope: !484)
!4236 = !DILocation(line: 853, column: 1, scope: !484)
!4237 = !DILocalVariable(name: "dent", arg: 1, scope: !536, file: !1, line: 381, type: !539)
!4238 = !DILocation(line: 381, column: 51, scope: !536)
!4239 = !DILocation(line: 382, column: 17, scope: !536)
!4240 = !DILocation(line: 382, column: 23, scope: !536)
!4241 = !DILocation(line: 382, column: 10, scope: !536)
!4242 = !DILocation(line: 382, column: 36, scope: !536)
!4243 = !DILocation(line: 382, column: 41, scope: !536)
!4244 = !DILocation(line: 382, column: 51, scope: !4245)
!4245 = !DILexicalBlockFile(scope: !536, file: !1, discriminator: 1)
!4246 = !DILocation(line: 382, column: 57, scope: !4245)
!4247 = !DILocation(line: 382, column: 44, scope: !4245)
!4248 = !DILocation(line: 382, column: 71, scope: !4245)
!4249 = !DILocation(line: 382, column: 41, scope: !4250)
!4250 = !DILexicalBlockFile(scope: !536, file: !1, discriminator: 2)
!4251 = !DILocation(line: 382, column: 3, scope: !4250)
!4252 = !DILocalVariable(name: "a", arg: 1, scope: !556, file: !1, line: 386, type: !559)
!4253 = !DILocation(line: 386, column: 50, scope: !556)
!4254 = !DILocalVariable(name: "b", arg: 2, scope: !556, file: !1, line: 386, type: !559)
!4255 = !DILocation(line: 386, column: 71, scope: !556)
!4256 = !DILocation(line: 387, column: 19, scope: !556)
!4257 = !DILocation(line: 387, column: 18, scope: !556)
!4258 = !DILocation(line: 387, column: 23, scope: !556)
!4259 = !DILocation(line: 387, column: 17, scope: !556)
!4260 = !DILocation(line: 387, column: 33, scope: !556)
!4261 = !DILocation(line: 387, column: 32, scope: !556)
!4262 = !DILocation(line: 387, column: 37, scope: !556)
!4263 = !DILocation(line: 387, column: 31, scope: !556)
!4264 = !DILocation(line: 387, column: 10, scope: !556)
!4265 = !DILocation(line: 387, column: 3, scope: !556)
!4266 = !DILocalVariable(name: "path", arg: 1, scope: !561, file: !1, line: 417, type: !331)
!4267 = !DILocation(line: 417, column: 48, scope: !561)
!4268 = !DILocalVariable(name: "pathmax", scope: !561, file: !1, line: 418, type: !325)
!4269 = !DILocation(line: 418, column: 11, scope: !561)
!4270 = !DILocation(line: 420, column: 22, scope: !561)
!4271 = !DILocation(line: 420, column: 13, scope: !561)
!4272 = !DILocation(line: 420, column: 11, scope: !561)
!4273 = !DILocation(line: 422, column: 7, scope: !4274)
!4274 = distinct !DILexicalBlock(scope: !561, file: !1, line: 422, column: 7)
!4275 = !DILocation(line: 422, column: 15, scope: !4274)
!4276 = !DILocation(line: 422, column: 7, scope: !561)
!4277 = !DILocation(line: 424, column: 5, scope: !4278)
!4278 = distinct !DILexicalBlock(scope: !4274, file: !1, line: 422, column: 22)
!4279 = !DILocation(line: 430, column: 10, scope: !561)
!4280 = !DILocation(line: 430, column: 3, scope: !561)
!4281 = !DILocation(line: 431, column: 1, scope: !561)
!4282 = !DILocalVariable(name: "req", arg: 1, scope: !566, file: !1, line: 480, type: !105)
!4283 = !DILocation(line: 480, column: 46, scope: !566)
!4284 = !DILocalVariable(name: "pfd", scope: !566, file: !1, line: 481, type: !4285)
!4285 = !DICompositeType(tag: DW_TAG_structure_type, name: "pollfd", file: !4286, line: 39, size: 64, align: 32, elements: !4287)
!4286 = !DIFile(filename: "/usr/include/x86_64-linux-gnu/sys/poll.h", directory: "/data/download/cmake/cmake-master/Utilities/cmlibuv")
!4287 = !{!4288, !4289, !4290}
!4288 = !DIDerivedType(tag: DW_TAG_member, name: "fd", scope: !4285, file: !4286, line: 41, baseType: !133, size: 32, align: 32)
!4289 = !DIDerivedType(tag: DW_TAG_member, name: "events", scope: !4285, file: !4286, line: 42, baseType: !173, size: 16, align: 16, offset: 32)
!4290 = !DIDerivedType(tag: DW_TAG_member, name: "revents", scope: !4285, file: !4286, line: 43, baseType: !173, size: 16, align: 16, offset: 48)
!4291 = !DILocation(line: 481, column: 17, scope: !566)
!4292 = !DILocalVariable(name: "use_pread", scope: !566, file: !1, line: 482, type: !133)
!4293 = !DILocation(line: 482, column: 7, scope: !566)
!4294 = !DILocalVariable(name: "offset", scope: !566, file: !1, line: 483, type: !378)
!4295 = !DILocation(line: 483, column: 9, scope: !566)
!4296 = !DILocalVariable(name: "nsent", scope: !566, file: !1, line: 484, type: !325)
!4297 = !DILocation(line: 484, column: 11, scope: !566)
!4298 = !DILocalVariable(name: "nread", scope: !566, file: !1, line: 485, type: !325)
!4299 = !DILocation(line: 485, column: 11, scope: !566)
!4300 = !DILocalVariable(name: "nwritten", scope: !566, file: !1, line: 486, type: !325)
!4301 = !DILocation(line: 486, column: 11, scope: !566)
!4302 = !DILocalVariable(name: "buflen", scope: !566, file: !1, line: 487, type: !375)
!4303 = !DILocation(line: 487, column: 10, scope: !566)
!4304 = !DILocalVariable(name: "len", scope: !566, file: !1, line: 488, type: !375)
!4305 = !DILocation(line: 488, column: 10, scope: !566)
!4306 = !DILocalVariable(name: "n", scope: !566, file: !1, line: 489, type: !325)
!4307 = !DILocation(line: 489, column: 11, scope: !566)
!4308 = !DILocalVariable(name: "in_fd", scope: !566, file: !1, line: 490, type: !133)
!4309 = !DILocation(line: 490, column: 7, scope: !566)
!4310 = !DILocalVariable(name: "out_fd", scope: !566, file: !1, line: 491, type: !133)
!4311 = !DILocation(line: 491, column: 7, scope: !566)
!4312 = !DILocalVariable(name: "buf", scope: !566, file: !1, line: 492, type: !4313)
!4313 = !DICompositeType(tag: DW_TAG_array_type, baseType: !184, size: 65536, align: 8, elements: !4314)
!4314 = !{!4315}
!4315 = !DISubrange(count: 8192)
!4316 = !DILocation(line: 492, column: 8, scope: !566)
!4317 = !DILocation(line: 494, column: 9, scope: !566)
!4318 = !DILocation(line: 494, column: 14, scope: !566)
!4319 = !DILocation(line: 494, column: 24, scope: !566)
!4320 = !DILocation(line: 494, column: 7, scope: !566)
!4321 = !DILocation(line: 495, column: 11, scope: !566)
!4322 = !DILocation(line: 495, column: 16, scope: !566)
!4323 = !DILocation(line: 495, column: 9, scope: !566)
!4324 = !DILocation(line: 496, column: 12, scope: !566)
!4325 = !DILocation(line: 496, column: 17, scope: !566)
!4326 = !DILocation(line: 496, column: 10, scope: !566)
!4327 = !DILocation(line: 497, column: 12, scope: !566)
!4328 = !DILocation(line: 497, column: 17, scope: !566)
!4329 = !DILocation(line: 497, column: 10, scope: !566)
!4330 = !DILocation(line: 498, column: 13, scope: !566)
!4331 = !DILocation(line: 524, column: 14, scope: !4332)
!4332 = distinct !DILexicalBlock(scope: !566, file: !1, line: 524, column: 3)
!4333 = !DILocation(line: 524, column: 8, scope: !4332)
!4334 = !DILocation(line: 524, column: 28, scope: !4335)
!4335 = !DILexicalBlockFile(scope: !4336, file: !1, discriminator: 1)
!4336 = distinct !DILexicalBlock(scope: !4332, file: !1, line: 524, column: 3)
!4337 = !DILocation(line: 524, column: 36, scope: !4335)
!4338 = !DILocation(line: 524, column: 34, scope: !4335)
!4339 = !DILocation(line: 524, column: 3, scope: !4335)
!4340 = !DILocation(line: 525, column: 14, scope: !4341)
!4341 = distinct !DILexicalBlock(scope: !4336, file: !1, line: 524, column: 43)
!4342 = !DILocation(line: 525, column: 20, scope: !4341)
!4343 = !DILocation(line: 525, column: 18, scope: !4341)
!4344 = !DILocation(line: 525, column: 12, scope: !4341)
!4345 = !DILocation(line: 527, column: 9, scope: !4346)
!4346 = distinct !DILexicalBlock(scope: !4341, file: !1, line: 527, column: 9)
!4347 = !DILocation(line: 527, column: 16, scope: !4346)
!4348 = !DILocation(line: 527, column: 9, scope: !4341)
!4349 = !DILocation(line: 528, column: 14, scope: !4346)
!4350 = !DILocation(line: 528, column: 7, scope: !4346)
!4351 = !DILocation(line: 530, column: 5, scope: !4341)
!4352 = !DILocation(line: 531, column: 11, scope: !4353)
!4353 = distinct !DILexicalBlock(scope: !4341, file: !1, line: 531, column: 11)
!4354 = !DILocation(line: 531, column: 11, scope: !4341)
!4355 = !DILocation(line: 532, column: 23, scope: !4353)
!4356 = !DILocation(line: 532, column: 30, scope: !4353)
!4357 = !DILocation(line: 532, column: 35, scope: !4353)
!4358 = !DILocation(line: 532, column: 43, scope: !4353)
!4359 = !DILocation(line: 532, column: 17, scope: !4353)
!4360 = !DILocation(line: 532, column: 15, scope: !4353)
!4361 = !DILocation(line: 532, column: 9, scope: !4353)
!4362 = !DILocation(line: 534, column: 22, scope: !4353)
!4363 = !DILocation(line: 534, column: 29, scope: !4353)
!4364 = !DILocation(line: 534, column: 34, scope: !4353)
!4365 = !DILocation(line: 534, column: 17, scope: !4353)
!4366 = !DILocation(line: 534, column: 15, scope: !4353)
!4367 = !DILocation(line: 531, column: 11, scope: !4368)
!4368 = !DILexicalBlockFile(scope: !4353, file: !1, discriminator: 1)
!4369 = !DILocation(line: 535, column: 12, scope: !4341)
!4370 = !DILocation(line: 535, column: 18, scope: !4341)
!4371 = !DILocation(line: 535, column: 24, scope: !4341)
!4372 = !DILocation(line: 535, column: 27, scope: !4373)
!4373 = !DILexicalBlockFile(scope: !4341, file: !1, discriminator: 1)
!4374 = !DILocation(line: 535, column: 33, scope: !4373)
!4375 = !DILocation(line: 531, column: 11, scope: !4376)
!4376 = !DILexicalBlockFile(scope: !4353, file: !1, discriminator: 2)
!4377 = !DILocation(line: 537, column: 9, scope: !4378)
!4378 = distinct !DILexicalBlock(scope: !4341, file: !1, line: 537, column: 9)
!4379 = !DILocation(line: 537, column: 15, scope: !4378)
!4380 = !DILocation(line: 537, column: 9, scope: !4341)
!4381 = !DILocation(line: 538, column: 7, scope: !4378)
!4382 = !DILocation(line: 540, column: 9, scope: !4383)
!4383 = distinct !DILexicalBlock(scope: !4341, file: !1, line: 540, column: 9)
!4384 = !DILocation(line: 540, column: 15, scope: !4383)
!4385 = !DILocation(line: 540, column: 9, scope: !4341)
!4386 = !DILocation(line: 541, column: 11, scope: !4387)
!4387 = distinct !DILexicalBlock(scope: !4388, file: !1, line: 541, column: 11)
!4388 = distinct !DILexicalBlock(scope: !4383, file: !1, line: 540, column: 22)
!4389 = !DILocation(line: 541, column: 21, scope: !4387)
!4390 = !DILocation(line: 541, column: 24, scope: !4391)
!4391 = !DILexicalBlockFile(scope: !4387, file: !1, discriminator: 1)
!4392 = !DILocation(line: 541, column: 30, scope: !4391)
!4393 = !DILocation(line: 541, column: 35, scope: !4391)
!4394 = !DILocation(line: 541, column: 39, scope: !4395)
!4395 = !DILexicalBlockFile(scope: !4387, file: !1, discriminator: 2)
!4396 = !DILocation(line: 541, column: 45, scope: !4395)
!4397 = !DILocation(line: 541, column: 52, scope: !4395)
!4398 = !DILocation(line: 541, column: 55, scope: !4399)
!4399 = !DILexicalBlockFile(scope: !4387, file: !1, discriminator: 3)
!4400 = !DILocation(line: 541, column: 61, scope: !4399)
!4401 = !DILocation(line: 541, column: 11, scope: !4399)
!4402 = !DILocation(line: 542, column: 19, scope: !4403)
!4403 = distinct !DILexicalBlock(scope: !4387, file: !1, line: 541, column: 73)
!4404 = !DILocation(line: 543, column: 9, scope: !4403)
!4405 = !DILocation(line: 546, column: 11, scope: !4406)
!4406 = distinct !DILexicalBlock(scope: !4388, file: !1, line: 546, column: 11)
!4407 = !DILocation(line: 546, column: 17, scope: !4406)
!4408 = !DILocation(line: 546, column: 11, scope: !4388)
!4409 = !DILocation(line: 547, column: 15, scope: !4406)
!4410 = !DILocation(line: 547, column: 9, scope: !4406)
!4411 = !DILocation(line: 549, column: 7, scope: !4388)
!4412 = !DILocation(line: 552, column: 19, scope: !4413)
!4413 = distinct !DILexicalBlock(scope: !4341, file: !1, line: 552, column: 5)
!4414 = !DILocation(line: 552, column: 10, scope: !4413)
!4415 = !DILocation(line: 552, column: 24, scope: !4416)
!4416 = !DILexicalBlockFile(scope: !4417, file: !1, discriminator: 1)
!4417 = distinct !DILexicalBlock(scope: !4413, file: !1, line: 552, column: 5)
!4418 = !DILocation(line: 552, column: 35, scope: !4416)
!4419 = !DILocation(line: 552, column: 33, scope: !4416)
!4420 = !DILocation(line: 552, column: 5, scope: !4416)
!4421 = !DILocation(line: 553, column: 7, scope: !4422)
!4422 = distinct !DILexicalBlock(scope: !4417, file: !1, line: 552, column: 44)
!4423 = !DILocation(line: 554, column: 19, scope: !4422)
!4424 = !DILocation(line: 554, column: 27, scope: !4422)
!4425 = !DILocation(line: 554, column: 33, scope: !4422)
!4426 = !DILocation(line: 554, column: 31, scope: !4422)
!4427 = !DILocation(line: 554, column: 43, scope: !4422)
!4428 = !DILocation(line: 554, column: 51, scope: !4422)
!4429 = !DILocation(line: 554, column: 49, scope: !4422)
!4430 = !DILocation(line: 554, column: 13, scope: !4422)
!4431 = !DILocation(line: 554, column: 11, scope: !4422)
!4432 = !DILocation(line: 554, column: 9, scope: !4422)
!4433 = !DILocation(line: 555, column: 14, scope: !4422)
!4434 = !DILocation(line: 555, column: 16, scope: !4422)
!4435 = !DILocation(line: 555, column: 22, scope: !4422)
!4436 = !DILocation(line: 555, column: 25, scope: !4437)
!4437 = !DILexicalBlockFile(scope: !4422, file: !1, discriminator: 1)
!4438 = !DILocation(line: 555, column: 31, scope: !4437)
!4439 = !DILocation(line: 554, column: 9, scope: !4437)
!4440 = !DILocation(line: 557, column: 11, scope: !4441)
!4441 = distinct !DILexicalBlock(scope: !4422, file: !1, line: 557, column: 11)
!4442 = !DILocation(line: 557, column: 13, scope: !4441)
!4443 = !DILocation(line: 557, column: 11, scope: !4422)
!4444 = !DILocation(line: 558, column: 21, scope: !4445)
!4445 = distinct !DILexicalBlock(scope: !4441, file: !1, line: 557, column: 20)
!4446 = !DILocation(line: 558, column: 18, scope: !4445)
!4447 = !DILocation(line: 559, column: 9, scope: !4445)
!4448 = !DILocation(line: 562, column: 11, scope: !4449)
!4449 = distinct !DILexicalBlock(scope: !4422, file: !1, line: 562, column: 11)
!4450 = !DILocation(line: 562, column: 17, scope: !4449)
!4451 = !DILocation(line: 562, column: 27, scope: !4449)
!4452 = !DILocation(line: 562, column: 30, scope: !4453)
!4453 = !DILexicalBlockFile(scope: !4449, file: !1, discriminator: 1)
!4454 = !DILocation(line: 562, column: 36, scope: !4453)
!4455 = !DILocation(line: 562, column: 11, scope: !4453)
!4456 = !DILocation(line: 563, column: 15, scope: !4457)
!4457 = distinct !DILexicalBlock(scope: !4449, file: !1, line: 562, column: 52)
!4458 = !DILocation(line: 564, column: 9, scope: !4457)
!4459 = !DILocation(line: 567, column: 16, scope: !4422)
!4460 = !DILocation(line: 567, column: 11, scope: !4422)
!4461 = !DILocation(line: 567, column: 14, scope: !4422)
!4462 = !DILocation(line: 568, column: 11, scope: !4422)
!4463 = !DILocation(line: 568, column: 18, scope: !4422)
!4464 = !DILocation(line: 569, column: 11, scope: !4422)
!4465 = !DILocation(line: 569, column: 19, scope: !4422)
!4466 = !DILocation(line: 571, column: 7, scope: !4422)
!4467 = !DILocation(line: 572, column: 13, scope: !4422)
!4468 = !DILocation(line: 572, column: 11, scope: !4422)
!4469 = !DILocation(line: 572, column: 9, scope: !4422)
!4470 = !DILocation(line: 573, column: 14, scope: !4422)
!4471 = !DILocation(line: 573, column: 16, scope: !4422)
!4472 = !DILocation(line: 573, column: 22, scope: !4422)
!4473 = !DILocation(line: 573, column: 25, scope: !4437)
!4474 = !DILocation(line: 573, column: 31, scope: !4437)
!4475 = !DILocation(line: 572, column: 9, scope: !4437)
!4476 = !DILocation(line: 575, column: 11, scope: !4477)
!4477 = distinct !DILexicalBlock(scope: !4422, file: !1, line: 575, column: 11)
!4478 = !DILocation(line: 575, column: 13, scope: !4477)
!4479 = !DILocation(line: 575, column: 19, scope: !4477)
!4480 = !DILocation(line: 575, column: 27, scope: !4481)
!4481 = !DILexicalBlockFile(scope: !4477, file: !1, discriminator: 1)
!4482 = !DILocation(line: 575, column: 23, scope: !4481)
!4483 = !DILocation(line: 575, column: 35, scope: !4481)
!4484 = !DILocation(line: 575, column: 47, scope: !4481)
!4485 = !DILocation(line: 575, column: 11, scope: !4481)
!4486 = !DILocation(line: 576, column: 9, scope: !4487)
!4487 = distinct !DILexicalBlock(scope: !4477, file: !1, line: 575, column: 53)
!4488 = !DILocation(line: 576, column: 15, scope: !4487)
!4489 = !DILocation(line: 577, column: 15, scope: !4487)
!4490 = !DILocation(line: 578, column: 9, scope: !4487)
!4491 = !DILocation(line: 552, column: 5, scope: !4492)
!4492 = !DILexicalBlockFile(scope: !4417, file: !1, discriminator: 2)
!4493 = !DILocation(line: 582, column: 15, scope: !4341)
!4494 = !DILocation(line: 582, column: 12, scope: !4341)
!4495 = !DILocation(line: 583, column: 14, scope: !4341)
!4496 = !DILocation(line: 583, column: 11, scope: !4341)
!4497 = !DILocation(line: 524, column: 3, scope: !4498)
!4498 = !DILexicalBlockFile(scope: !4336, file: !1, discriminator: 2)
!4499 = !DILocation(line: 584, column: 3, scope: !4332)
!4500 = !DILocation(line: 587, column: 7, scope: !4501)
!4501 = distinct !DILexicalBlock(scope: !566, file: !1, line: 587, column: 7)
!4502 = !DILocation(line: 587, column: 13, scope: !4501)
!4503 = !DILocation(line: 587, column: 7, scope: !566)
!4504 = !DILocation(line: 588, column: 16, scope: !4501)
!4505 = !DILocation(line: 588, column: 5, scope: !4501)
!4506 = !DILocation(line: 588, column: 10, scope: !4501)
!4507 = !DILocation(line: 588, column: 14, scope: !4501)
!4508 = !DILocation(line: 590, column: 10, scope: !566)
!4509 = !DILocation(line: 590, column: 3, scope: !566)
