; ModuleID = '/data/download/cmake/cmake-master/Utilities/cmlibuv/src/unix/linux-core.c'
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
%struct.uv__epoll_event = type <{ i32, i64 }>
%struct.__sigset_t = type { [16 x i64] }
%struct.timespec = type { i64, i64 }
%struct.sysinfo = type { i64, [3 x i64], i64, i64, i64, i64, i64, i64, i16, i16, i64, i64, i32, [0 x i8] }
%struct.uv_cpu_info_s = type { i8*, i32, %struct.uv_cpu_times_s }
%struct.uv_cpu_times_s = type { i64, i64, i64, i64, i64 }
%struct._IO_FILE = type { i32, i8*, i8*, i8*, i8*, i8*, i8*, i8*, i8*, i8*, i8*, i8*, %struct._IO_marker*, %struct._IO_FILE*, i32, i32, i64, i16, i8, [1 x i8], i8*, i64, i8*, i8*, i8*, i8*, i64, i32, [20 x i8] }
%struct._IO_marker = type { %struct._IO_marker*, %struct._IO_FILE*, i32 }
%struct.uv_interface_address_s = type { i8*, [6 x i8], i32, %union.anon.4, %union.anon.6 }
%union.anon.4 = type { %struct.sockaddr_in6 }
%struct.sockaddr_in6 = type { i16, i16, i32, %struct.in6_addr, i32 }
%struct.in6_addr = type { %union.anon.5 }
%union.anon.5 = type { [4 x i32] }
%union.anon.6 = type { %struct.sockaddr_in6 }
%struct.ifaddrs = type { %struct.ifaddrs*, i8*, i32, %struct.sockaddr*, %struct.sockaddr*, %union.anon.7, i8* }
%struct.sockaddr = type { i16, [14 x i8] }
%union.anon.7 = type { %struct.sockaddr* }
%struct.sockaddr_ll = type { i16, i16, i32, i16, i8, i8, [8 x i8] }
%struct.sockaddr_in = type { i16, i16, %struct.in_addr, [8 x i8] }
%struct.in_addr = type { i32 }

@.str = private unnamed_addr constant [29 x i8] c"loop->watchers != ((void*)0)\00", align 1
@.str.1 = private unnamed_addr constant [74 x i8] c"/data/download/cmake/cmake-master/Utilities/cmlibuv/src/unix/linux-core.c\00", align 1
@__PRETTY_FUNCTION__.uv__platform_invalidate_fd = private unnamed_addr constant [50 x i8] c"void uv__platform_invalidate_fd(uv_loop_t *, int)\00", align 1
@uv__io_poll.max_safe_timeout = internal constant i32 1789569, align 4
@uv__io_poll.no_epoll_pwait = internal global i32 0, align 4
@uv__io_poll.no_epoll_wait = internal global i32 0, align 4
@.str.2 = private unnamed_addr constant [106 x i8] c"((const QUEUE *) (&loop->watcher_queue) == (const QUEUE *) (*(QUEUE **) &((*(&loop->watcher_queue))[0])))\00", align 1
@__PRETTY_FUNCTION__.uv__io_poll = private unnamed_addr constant [35 x i8] c"void uv__io_poll(uv_loop_t *, int)\00", align 1
@.str.3 = private unnamed_addr constant [16 x i8] c"w->pevents != 0\00", align 1
@.str.4 = private unnamed_addr constant [11 x i8] c"w->fd >= 0\00", align 1
@.str.5 = private unnamed_addr constant [30 x i8] c"w->fd < (int) loop->nwatchers\00", align 1
@.str.6 = private unnamed_addr constant [8 x i8] c"op == 1\00", align 1
@.str.7 = private unnamed_addr constant [14 x i8] c"timeout >= -1\00", align 1
@.str.8 = private unnamed_addr constant [14 x i8] c"timeout != -1\00", align 1
@.str.9 = private unnamed_addr constant [42 x i8] c"no_epoll_wait == 0 || no_epoll_pwait == 0\00", align 1
@.str.10 = private unnamed_addr constant [8 x i8] c"fd >= 0\00", align 1
@.str.11 = private unnamed_addr constant [32 x i8] c"(unsigned) fd < loop->nwatchers\00", align 1
@.str.12 = private unnamed_addr constant [12 x i8] c"timeout > 0\00", align 1
@uv__hrtime.fast_clock_id = internal global i64 -1, align 8
@.str.13 = private unnamed_addr constant [15 x i8] c"/proc/self/exe\00", align 1
@.str.14 = private unnamed_addr constant [16 x i8] c"/proc/self/stat\00", align 1
@uv_uptime.no_clock_boottime = internal global i32 0, align 4
@.str.15 = private unnamed_addr constant [11 x i8] c"/proc/stat\00", align 1
@.str.16 = private unnamed_addr constant [4 x i8] c"cpu\00", align 1
@.str.17 = private unnamed_addr constant [55 x i8] c"/sys/devices/system/cpu/cpu%u/cpufreq/scaling_cur_freq\00", align 1
@.str.18 = private unnamed_addr constant [4 x i8] c"%lu\00", align 1
@read_models.model_marker = internal constant [14 x i8] c"model name\09: \00", align 1
@read_models.speed_marker = internal constant [12 x i8] c"cpu MHz\09\09: \00", align 1
@.str.19 = private unnamed_addr constant [14 x i8] c"/proc/cpuinfo\00", align 1
@.str.20 = private unnamed_addr constant [8 x i8] c"unknown\00", align 1
@.str.21 = private unnamed_addr constant [34 x i8] c"clock_ticks != (unsigned long) -1\00", align 1
@__PRETTY_FUNCTION__.read_times = private unnamed_addr constant [54 x i8] c"int read_times(FILE *, unsigned int, uv_cpu_info_t *)\00", align 1
@.str.22 = private unnamed_addr constant [17 x i8] c"clock_ticks != 0\00", align 1
@.str.23 = private unnamed_addr constant [7 x i8] c"cpu%u \00", align 1
@.str.24 = private unnamed_addr constant [7 x i8] c"r == 1\00", align 1
@.str.25 = private unnamed_addr constant [24 x i8] c"%lu %lu %lu %lu %lu %lu\00", align 1
@.str.26 = private unnamed_addr constant [15 x i8] c"num == numcpus\00", align 1

; Function Attrs: nounwind uwtable
define i32 @uv__platform_loop_init(%struct.uv_loop_s* %loop) #0 !dbg !548 {
entry:
  %retval = alloca i32, align 4
  %loop.addr = alloca %struct.uv_loop_s*, align 8
  %fd = alloca i32, align 4
  store %struct.uv_loop_s* %loop, %struct.uv_loop_s** %loop.addr, align 8
  call void @llvm.dbg.declare(metadata %struct.uv_loop_s** %loop.addr, metadata !759, metadata !760), !dbg !761
  call void @llvm.dbg.declare(metadata i32* %fd, metadata !762, metadata !760), !dbg !763
  %call = call i32 @uv__epoll_create1(i32 524288), !dbg !764
  store i32 %call, i32* %fd, align 4, !dbg !765
  %0 = load i32, i32* %fd, align 4, !dbg !766
  %cmp = icmp eq i32 %0, -1, !dbg !768
  br i1 %cmp, label %land.lhs.true, label %if.end9, !dbg !769

land.lhs.true:                                    ; preds = %entry
  %call1 = call i32* @__errno_location() #1, !dbg !770
  %1 = load i32, i32* %call1, align 4, !dbg !770
  %cmp2 = icmp eq i32 %1, 38, !dbg !772
  br i1 %cmp2, label %if.then, label %lor.lhs.false, !dbg !773

lor.lhs.false:                                    ; preds = %land.lhs.true
  %call3 = call i32* @__errno_location() #1, !dbg !774
  %2 = load i32, i32* %call3, align 4, !dbg !774
  %cmp4 = icmp eq i32 %2, 22, !dbg !776
  br i1 %cmp4, label %if.then, label %if.end9, !dbg !777

if.then:                                          ; preds = %lor.lhs.false, %land.lhs.true
  %call5 = call i32 @uv__epoll_create(i32 256), !dbg !778
  store i32 %call5, i32* %fd, align 4, !dbg !780
  %3 = load i32, i32* %fd, align 4, !dbg !781
  %cmp6 = icmp ne i32 %3, -1, !dbg !783
  br i1 %cmp6, label %if.then7, label %if.end, !dbg !784

if.then7:                                         ; preds = %if.then
  %4 = load i32, i32* %fd, align 4, !dbg !785
  %call8 = call i32 @uv__cloexec_ioctl(i32 %4, i32 1), !dbg !786
  br label %if.end, !dbg !786

if.end:                                           ; preds = %if.then7, %if.then
  br label %if.end9, !dbg !787

if.end9:                                          ; preds = %if.end, %lor.lhs.false, %entry
  %5 = load i32, i32* %fd, align 4, !dbg !788
  %6 = load %struct.uv_loop_s*, %struct.uv_loop_s** %loop.addr, align 8, !dbg !789
  %backend_fd = getelementptr inbounds %struct.uv_loop_s, %struct.uv_loop_s* %6, i32 0, i32 6, !dbg !790
  store i32 %5, i32* %backend_fd, align 8, !dbg !791
  %7 = load %struct.uv_loop_s*, %struct.uv_loop_s** %loop.addr, align 8, !dbg !792
  %inotify_fd = getelementptr inbounds %struct.uv_loop_s, %struct.uv_loop_s* %7, i32 0, i32 34, !dbg !793
  store i32 -1, i32* %inotify_fd, align 8, !dbg !794
  %8 = load %struct.uv_loop_s*, %struct.uv_loop_s** %loop.addr, align 8, !dbg !795
  %inotify_watchers = getelementptr inbounds %struct.uv_loop_s, %struct.uv_loop_s* %8, i32 0, i32 33, !dbg !796
  store i8* null, i8** %inotify_watchers, align 8, !dbg !797
  %9 = load i32, i32* %fd, align 4, !dbg !798
  %cmp10 = icmp eq i32 %9, -1, !dbg !800
  br i1 %cmp10, label %if.then11, label %if.end13, !dbg !801

if.then11:                                        ; preds = %if.end9
  %call12 = call i32* @__errno_location() #1, !dbg !802
  %10 = load i32, i32* %call12, align 4, !dbg !802
  %sub = sub nsw i32 0, %10, !dbg !803
  store i32 %sub, i32* %retval, align 4, !dbg !804
  br label %return, !dbg !804

if.end13:                                         ; preds = %if.end9
  store i32 0, i32* %retval, align 4, !dbg !805
  br label %return, !dbg !805

return:                                           ; preds = %if.end13, %if.then11
  %11 = load i32, i32* %retval, align 4, !dbg !806
  ret i32 %11, !dbg !806
}

; Function Attrs: nounwind readnone
declare void @llvm.dbg.declare(metadata, metadata, metadata) #1

declare i32 @uv__epoll_create1(i32) #2

; Function Attrs: nounwind readnone
declare i32* @__errno_location() #3

declare i32 @uv__epoll_create(i32) #2

declare i32 @uv__cloexec_ioctl(i32, i32) #2

; Function Attrs: nounwind uwtable
define i32 @uv__io_fork(%struct.uv_loop_s* %loop) #0 !dbg !552 {
entry:
  %retval = alloca i32, align 4
  %loop.addr = alloca %struct.uv_loop_s*, align 8
  %err = alloca i32, align 4
  %old_watchers = alloca i8*, align 8
  store %struct.uv_loop_s* %loop, %struct.uv_loop_s** %loop.addr, align 8
  call void @llvm.dbg.declare(metadata %struct.uv_loop_s** %loop.addr, metadata !807, metadata !760), !dbg !808
  call void @llvm.dbg.declare(metadata i32* %err, metadata !809, metadata !760), !dbg !810
  call void @llvm.dbg.declare(metadata i8** %old_watchers, metadata !811, metadata !760), !dbg !812
  %0 = load %struct.uv_loop_s*, %struct.uv_loop_s** %loop.addr, align 8, !dbg !813
  %inotify_watchers = getelementptr inbounds %struct.uv_loop_s, %struct.uv_loop_s* %0, i32 0, i32 33, !dbg !814
  %1 = load i8*, i8** %inotify_watchers, align 8, !dbg !814
  store i8* %1, i8** %old_watchers, align 8, !dbg !815
  %2 = load %struct.uv_loop_s*, %struct.uv_loop_s** %loop.addr, align 8, !dbg !816
  %backend_fd = getelementptr inbounds %struct.uv_loop_s, %struct.uv_loop_s* %2, i32 0, i32 6, !dbg !817
  %3 = load i32, i32* %backend_fd, align 8, !dbg !817
  %call = call i32 @uv__close(i32 %3), !dbg !818
  %4 = load %struct.uv_loop_s*, %struct.uv_loop_s** %loop.addr, align 8, !dbg !819
  %backend_fd1 = getelementptr inbounds %struct.uv_loop_s, %struct.uv_loop_s* %4, i32 0, i32 6, !dbg !820
  store i32 -1, i32* %backend_fd1, align 8, !dbg !821
  %5 = load %struct.uv_loop_s*, %struct.uv_loop_s** %loop.addr, align 8, !dbg !822
  call void @uv__platform_loop_delete(%struct.uv_loop_s* %5), !dbg !823
  %6 = load %struct.uv_loop_s*, %struct.uv_loop_s** %loop.addr, align 8, !dbg !824
  %call2 = call i32 @uv__platform_loop_init(%struct.uv_loop_s* %6), !dbg !825
  store i32 %call2, i32* %err, align 4, !dbg !826
  %7 = load i32, i32* %err, align 4, !dbg !827
  %tobool = icmp ne i32 %7, 0, !dbg !827
  br i1 %tobool, label %if.then, label %if.end, !dbg !829

if.then:                                          ; preds = %entry
  %8 = load i32, i32* %err, align 4, !dbg !830
  store i32 %8, i32* %retval, align 4, !dbg !831
  br label %return, !dbg !831

if.end:                                           ; preds = %entry
  %9 = load %struct.uv_loop_s*, %struct.uv_loop_s** %loop.addr, align 8, !dbg !832
  %10 = load i8*, i8** %old_watchers, align 8, !dbg !833
  %call3 = call i32 @uv__inotify_fork(%struct.uv_loop_s* %9, i8* %10), !dbg !834
  store i32 %call3, i32* %retval, align 4, !dbg !835
  br label %return, !dbg !835

return:                                           ; preds = %if.end, %if.then
  %11 = load i32, i32* %retval, align 4, !dbg !836
  ret i32 %11, !dbg !836
}

declare i32 @uv__close(i32) #2

; Function Attrs: nounwind uwtable
define void @uv__platform_loop_delete(%struct.uv_loop_s* %loop) #0 !dbg !553 {
entry:
  %loop.addr = alloca %struct.uv_loop_s*, align 8
  store %struct.uv_loop_s* %loop, %struct.uv_loop_s** %loop.addr, align 8
  call void @llvm.dbg.declare(metadata %struct.uv_loop_s** %loop.addr, metadata !837, metadata !760), !dbg !838
  %0 = load %struct.uv_loop_s*, %struct.uv_loop_s** %loop.addr, align 8, !dbg !839
  %inotify_fd = getelementptr inbounds %struct.uv_loop_s, %struct.uv_loop_s* %0, i32 0, i32 34, !dbg !841
  %1 = load i32, i32* %inotify_fd, align 8, !dbg !841
  %cmp = icmp eq i32 %1, -1, !dbg !842
  br i1 %cmp, label %if.then, label %if.end, !dbg !843

if.then:                                          ; preds = %entry
  br label %return, !dbg !844

if.end:                                           ; preds = %entry
  %2 = load %struct.uv_loop_s*, %struct.uv_loop_s** %loop.addr, align 8, !dbg !846
  %3 = load %struct.uv_loop_s*, %struct.uv_loop_s** %loop.addr, align 8, !dbg !847
  %inotify_read_watcher = getelementptr inbounds %struct.uv_loop_s, %struct.uv_loop_s* %3, i32 0, i32 32, !dbg !848
  call void @uv__io_stop(%struct.uv_loop_s* %2, %struct.uv__io_s* %inotify_read_watcher, i32 1), !dbg !849
  %4 = load %struct.uv_loop_s*, %struct.uv_loop_s** %loop.addr, align 8, !dbg !850
  %inotify_fd1 = getelementptr inbounds %struct.uv_loop_s, %struct.uv_loop_s* %4, i32 0, i32 34, !dbg !851
  %5 = load i32, i32* %inotify_fd1, align 8, !dbg !851
  %call = call i32 @uv__close(i32 %5), !dbg !852
  %6 = load %struct.uv_loop_s*, %struct.uv_loop_s** %loop.addr, align 8, !dbg !853
  %inotify_fd2 = getelementptr inbounds %struct.uv_loop_s, %struct.uv_loop_s* %6, i32 0, i32 34, !dbg !854
  store i32 -1, i32* %inotify_fd2, align 8, !dbg !855
  br label %return, !dbg !856

return:                                           ; preds = %if.end, %if.then
  ret void, !dbg !857
}

declare i32 @uv__inotify_fork(%struct.uv_loop_s*, i8*) #2

declare void @uv__io_stop(%struct.uv_loop_s*, %struct.uv__io_s*, i32) #2

; Function Attrs: nounwind uwtable
define void @uv__platform_invalidate_fd(%struct.uv_loop_s* %loop, i32 %fd) #0 !dbg !556 {
entry:
  %loop.addr = alloca %struct.uv_loop_s*, align 8
  %fd.addr = alloca i32, align 4
  %events = alloca %struct.uv__epoll_event*, align 8
  %dummy = alloca %struct.uv__epoll_event, align 1
  %i = alloca i64, align 8
  %nfds = alloca i64, align 8
  store %struct.uv_loop_s* %loop, %struct.uv_loop_s** %loop.addr, align 8
  call void @llvm.dbg.declare(metadata %struct.uv_loop_s** %loop.addr, metadata !859, metadata !760), !dbg !860
  store i32 %fd, i32* %fd.addr, align 4
  call void @llvm.dbg.declare(metadata i32* %fd.addr, metadata !861, metadata !760), !dbg !862
  call void @llvm.dbg.declare(metadata %struct.uv__epoll_event** %events, metadata !863, metadata !760), !dbg !864
  call void @llvm.dbg.declare(metadata %struct.uv__epoll_event* %dummy, metadata !865, metadata !760), !dbg !866
  call void @llvm.dbg.declare(metadata i64* %i, metadata !867, metadata !760), !dbg !868
  call void @llvm.dbg.declare(metadata i64* %nfds, metadata !869, metadata !760), !dbg !870
  %0 = load %struct.uv_loop_s*, %struct.uv_loop_s** %loop.addr, align 8, !dbg !871
  %watchers = getelementptr inbounds %struct.uv_loop_s, %struct.uv_loop_s* %0, i32 0, i32 9, !dbg !871
  %1 = load %struct.uv__io_s**, %struct.uv__io_s*** %watchers, align 8, !dbg !871
  %cmp = icmp ne %struct.uv__io_s** %1, null, !dbg !871
  br i1 %cmp, label %cond.true, label %cond.false, !dbg !871

cond.true:                                        ; preds = %entry
  br label %cond.end, !dbg !872

cond.false:                                       ; preds = %entry
  call void @__assert_fail(i8* getelementptr inbounds ([29 x i8], [29 x i8]* @.str, i32 0, i32 0), i8* getelementptr inbounds ([74 x i8], [74 x i8]* @.str.1, i32 0, i32 0), i32 142, i8* getelementptr inbounds ([50 x i8], [50 x i8]* @__PRETTY_FUNCTION__.uv__platform_invalidate_fd, i32 0, i32 0)) #8, !dbg !874
  unreachable, !dbg !874
                                                  ; No predecessors!
  br label %cond.end, !dbg !876

cond.end:                                         ; preds = %2, %cond.true
  %3 = load %struct.uv_loop_s*, %struct.uv_loop_s** %loop.addr, align 8, !dbg !878
  %nwatchers = getelementptr inbounds %struct.uv_loop_s, %struct.uv_loop_s* %3, i32 0, i32 10, !dbg !879
  %4 = load i32, i32* %nwatchers, align 8, !dbg !879
  %idxprom = zext i32 %4 to i64, !dbg !880
  %5 = load %struct.uv_loop_s*, %struct.uv_loop_s** %loop.addr, align 8, !dbg !880
  %watchers1 = getelementptr inbounds %struct.uv_loop_s, %struct.uv_loop_s* %5, i32 0, i32 9, !dbg !881
  %6 = load %struct.uv__io_s**, %struct.uv__io_s*** %watchers1, align 8, !dbg !881
  %arrayidx = getelementptr inbounds %struct.uv__io_s*, %struct.uv__io_s** %6, i64 %idxprom, !dbg !880
  %7 = load %struct.uv__io_s*, %struct.uv__io_s** %arrayidx, align 8, !dbg !880
  %8 = bitcast %struct.uv__io_s* %7 to %struct.uv__epoll_event*, !dbg !882
  store %struct.uv__epoll_event* %8, %struct.uv__epoll_event** %events, align 8, !dbg !883
  %9 = load %struct.uv_loop_s*, %struct.uv_loop_s** %loop.addr, align 8, !dbg !884
  %nwatchers2 = getelementptr inbounds %struct.uv_loop_s, %struct.uv_loop_s* %9, i32 0, i32 10, !dbg !885
  %10 = load i32, i32* %nwatchers2, align 8, !dbg !885
  %add = add i32 %10, 1, !dbg !886
  %idxprom3 = zext i32 %add to i64, !dbg !887
  %11 = load %struct.uv_loop_s*, %struct.uv_loop_s** %loop.addr, align 8, !dbg !887
  %watchers4 = getelementptr inbounds %struct.uv_loop_s, %struct.uv_loop_s* %11, i32 0, i32 9, !dbg !888
  %12 = load %struct.uv__io_s**, %struct.uv__io_s*** %watchers4, align 8, !dbg !888
  %arrayidx5 = getelementptr inbounds %struct.uv__io_s*, %struct.uv__io_s** %12, i64 %idxprom3, !dbg !887
  %13 = load %struct.uv__io_s*, %struct.uv__io_s** %arrayidx5, align 8, !dbg !887
  %14 = ptrtoint %struct.uv__io_s* %13 to i64, !dbg !889
  store i64 %14, i64* %nfds, align 8, !dbg !890
  %15 = load %struct.uv__epoll_event*, %struct.uv__epoll_event** %events, align 8, !dbg !891
  %cmp6 = icmp ne %struct.uv__epoll_event* %15, null, !dbg !893
  br i1 %cmp6, label %if.then, label %if.end14, !dbg !894

if.then:                                          ; preds = %cond.end
  store i64 0, i64* %i, align 8, !dbg !895
  br label %for.cond, !dbg !897

for.cond:                                         ; preds = %for.inc, %if.then
  %16 = load i64, i64* %i, align 8, !dbg !898
  %17 = load i64, i64* %nfds, align 8, !dbg !901
  %cmp7 = icmp ult i64 %16, %17, !dbg !902
  br i1 %cmp7, label %for.body, label %for.end, !dbg !903

for.body:                                         ; preds = %for.cond
  %18 = load i64, i64* %i, align 8, !dbg !904
  %19 = load %struct.uv__epoll_event*, %struct.uv__epoll_event** %events, align 8, !dbg !906
  %arrayidx8 = getelementptr inbounds %struct.uv__epoll_event, %struct.uv__epoll_event* %19, i64 %18, !dbg !906
  %data = getelementptr inbounds %struct.uv__epoll_event, %struct.uv__epoll_event* %arrayidx8, i32 0, i32 1, !dbg !907
  %20 = load i64, i64* %data, align 1, !dbg !907
  %conv = trunc i64 %20 to i32, !dbg !908
  %21 = load i32, i32* %fd.addr, align 4, !dbg !909
  %cmp9 = icmp eq i32 %conv, %21, !dbg !910
  br i1 %cmp9, label %if.then11, label %if.end, !dbg !911

if.then11:                                        ; preds = %for.body
  %22 = load i64, i64* %i, align 8, !dbg !912
  %23 = load %struct.uv__epoll_event*, %struct.uv__epoll_event** %events, align 8, !dbg !913
  %arrayidx12 = getelementptr inbounds %struct.uv__epoll_event, %struct.uv__epoll_event* %23, i64 %22, !dbg !913
  %data13 = getelementptr inbounds %struct.uv__epoll_event, %struct.uv__epoll_event* %arrayidx12, i32 0, i32 1, !dbg !914
  store i64 -1, i64* %data13, align 1, !dbg !915
  br label %if.end, !dbg !913

if.end:                                           ; preds = %if.then11, %for.body
  br label %for.inc, !dbg !916

for.inc:                                          ; preds = %if.end
  %24 = load i64, i64* %i, align 8, !dbg !918
  %inc = add i64 %24, 1, !dbg !918
  store i64 %inc, i64* %i, align 8, !dbg !918
  br label %for.cond, !dbg !920

for.end:                                          ; preds = %for.cond
  br label %if.end14, !dbg !921

if.end14:                                         ; preds = %for.end, %cond.end
  %25 = load %struct.uv_loop_s*, %struct.uv_loop_s** %loop.addr, align 8, !dbg !923
  %backend_fd = getelementptr inbounds %struct.uv_loop_s, %struct.uv_loop_s* %25, i32 0, i32 6, !dbg !925
  %26 = load i32, i32* %backend_fd, align 8, !dbg !925
  %cmp15 = icmp sge i32 %26, 0, !dbg !926
  br i1 %cmp15, label %if.then17, label %if.end19, !dbg !927

if.then17:                                        ; preds = %if.end14
  %27 = bitcast %struct.uv__epoll_event* %dummy to i8*, !dbg !928
  call void @llvm.memset.p0i8.i64(i8* %27, i8 0, i64 12, i32 1, i1 false), !dbg !928
  %28 = load %struct.uv_loop_s*, %struct.uv_loop_s** %loop.addr, align 8, !dbg !930
  %backend_fd18 = getelementptr inbounds %struct.uv_loop_s, %struct.uv_loop_s* %28, i32 0, i32 6, !dbg !931
  %29 = load i32, i32* %backend_fd18, align 8, !dbg !931
  %30 = load i32, i32* %fd.addr, align 4, !dbg !932
  %call = call i32 @uv__epoll_ctl(i32 %29, i32 2, i32 %30, %struct.uv__epoll_event* %dummy), !dbg !933
  br label %if.end19, !dbg !934

if.end19:                                         ; preds = %if.then17, %if.end14
  ret void, !dbg !935
}

; Function Attrs: noreturn nounwind
declare void @__assert_fail(i8*, i8*, i32, i8*) #4

; Function Attrs: argmemonly nounwind
declare void @llvm.memset.p0i8.i64(i8* nocapture, i8, i64, i32, i1) #5

declare i32 @uv__epoll_ctl(i32, i32, i32, %struct.uv__epoll_event*) #2

; Function Attrs: nounwind uwtable
define i32 @uv__io_check_fd(%struct.uv_loop_s* %loop, i32 %fd) #0 !dbg !559 {
entry:
  %loop.addr = alloca %struct.uv_loop_s*, align 8
  %fd.addr = alloca i32, align 4
  %e = alloca %struct.uv__epoll_event, align 1
  %rc = alloca i32, align 4
  store %struct.uv_loop_s* %loop, %struct.uv_loop_s** %loop.addr, align 8
  call void @llvm.dbg.declare(metadata %struct.uv_loop_s** %loop.addr, metadata !936, metadata !760), !dbg !937
  store i32 %fd, i32* %fd.addr, align 4
  call void @llvm.dbg.declare(metadata i32* %fd.addr, metadata !938, metadata !760), !dbg !939
  call void @llvm.dbg.declare(metadata %struct.uv__epoll_event* %e, metadata !940, metadata !760), !dbg !941
  call void @llvm.dbg.declare(metadata i32* %rc, metadata !942, metadata !760), !dbg !943
  %events = getelementptr inbounds %struct.uv__epoll_event, %struct.uv__epoll_event* %e, i32 0, i32 0, !dbg !944
  store i32 1, i32* %events, align 1, !dbg !945
  %data = getelementptr inbounds %struct.uv__epoll_event, %struct.uv__epoll_event* %e, i32 0, i32 1, !dbg !946
  store i64 -1, i64* %data, align 1, !dbg !947
  store i32 0, i32* %rc, align 4, !dbg !948
  %0 = load %struct.uv_loop_s*, %struct.uv_loop_s** %loop.addr, align 8, !dbg !949
  %backend_fd = getelementptr inbounds %struct.uv_loop_s, %struct.uv_loop_s* %0, i32 0, i32 6, !dbg !951
  %1 = load i32, i32* %backend_fd, align 8, !dbg !951
  %2 = load i32, i32* %fd.addr, align 4, !dbg !952
  %call = call i32 @uv__epoll_ctl(i32 %1, i32 1, i32 %2, %struct.uv__epoll_event* %e), !dbg !953
  %tobool = icmp ne i32 %call, 0, !dbg !953
  br i1 %tobool, label %if.then, label %if.end4, !dbg !954

if.then:                                          ; preds = %entry
  %call1 = call i32* @__errno_location() #1, !dbg !955
  %3 = load i32, i32* %call1, align 4, !dbg !955
  %cmp = icmp ne i32 %3, 17, !dbg !957
  br i1 %cmp, label %if.then2, label %if.end, !dbg !958

if.then2:                                         ; preds = %if.then
  %call3 = call i32* @__errno_location() #1, !dbg !959
  %4 = load i32, i32* %call3, align 4, !dbg !959
  %sub = sub nsw i32 0, %4, !dbg !960
  store i32 %sub, i32* %rc, align 4, !dbg !961
  br label %if.end, !dbg !962

if.end:                                           ; preds = %if.then2, %if.then
  br label %if.end4, !dbg !963

if.end4:                                          ; preds = %if.end, %entry
  %5 = load i32, i32* %rc, align 4, !dbg !965
  %cmp5 = icmp eq i32 %5, 0, !dbg !967
  br i1 %cmp5, label %if.then6, label %if.end12, !dbg !968

if.then6:                                         ; preds = %if.end4
  %6 = load %struct.uv_loop_s*, %struct.uv_loop_s** %loop.addr, align 8, !dbg !969
  %backend_fd7 = getelementptr inbounds %struct.uv_loop_s, %struct.uv_loop_s* %6, i32 0, i32 6, !dbg !971
  %7 = load i32, i32* %backend_fd7, align 8, !dbg !971
  %8 = load i32, i32* %fd.addr, align 4, !dbg !972
  %call8 = call i32 @uv__epoll_ctl(i32 %7, i32 2, i32 %8, %struct.uv__epoll_event* %e), !dbg !973
  %tobool9 = icmp ne i32 %call8, 0, !dbg !973
  br i1 %tobool9, label %if.then10, label %if.end11, !dbg !974

if.then10:                                        ; preds = %if.then6
  call void @abort() #8, !dbg !975
  unreachable, !dbg !975

if.end11:                                         ; preds = %if.then6
  br label %if.end12, !dbg !976

if.end12:                                         ; preds = %if.end11, %if.end4
  %9 = load i32, i32* %rc, align 4, !dbg !978
  ret i32 %9, !dbg !979
}

; Function Attrs: noreturn nounwind
declare void @abort() #4

; Function Attrs: nounwind uwtable
define void @uv__io_poll(%struct.uv_loop_s* %loop, i32 %timeout) #0 !dbg !562 {
entry:
  %loop.addr = alloca %struct.uv_loop_s*, align 8
  %timeout.addr = alloca i32, align 4
  %events = alloca [1024 x %struct.uv__epoll_event], align 16
  %pe = alloca %struct.uv__epoll_event*, align 8
  %e = alloca %struct.uv__epoll_event, align 1
  %real_timeout = alloca i32, align 4
  %q = alloca [2 x i8*]*, align 8
  %w = alloca %struct.uv__io_s*, align 8
  %sigset = alloca %struct.__sigset_t, align 8
  %sigmask = alloca i64, align 8
  %base = alloca i64, align 8
  %have_signals = alloca i32, align 4
  %nevents = alloca i32, align 4
  %count = alloca i32, align 4
  %nfds = alloca i32, align 4
  %fd = alloca i32, align 4
  %op = alloca i32, align 4
  %i = alloca i32, align 4
  %_saved_errno = alloca i32, align 4
  store %struct.uv_loop_s* %loop, %struct.uv_loop_s** %loop.addr, align 8
  call void @llvm.dbg.declare(metadata %struct.uv_loop_s** %loop.addr, metadata !980, metadata !760), !dbg !981
  store i32 %timeout, i32* %timeout.addr, align 4
  call void @llvm.dbg.declare(metadata i32* %timeout.addr, metadata !982, metadata !760), !dbg !983
  call void @llvm.dbg.declare(metadata [1024 x %struct.uv__epoll_event]* %events, metadata !984, metadata !760), !dbg !988
  call void @llvm.dbg.declare(metadata %struct.uv__epoll_event** %pe, metadata !989, metadata !760), !dbg !990
  call void @llvm.dbg.declare(metadata %struct.uv__epoll_event* %e, metadata !991, metadata !760), !dbg !992
  call void @llvm.dbg.declare(metadata i32* %real_timeout, metadata !993, metadata !760), !dbg !994
  call void @llvm.dbg.declare(metadata [2 x i8*]** %q, metadata !995, metadata !760), !dbg !996
  call void @llvm.dbg.declare(metadata %struct.uv__io_s** %w, metadata !997, metadata !760), !dbg !998
  call void @llvm.dbg.declare(metadata %struct.__sigset_t* %sigset, metadata !999, metadata !760), !dbg !1008
  call void @llvm.dbg.declare(metadata i64* %sigmask, metadata !1009, metadata !760), !dbg !1010
  call void @llvm.dbg.declare(metadata i64* %base, metadata !1011, metadata !760), !dbg !1012
  call void @llvm.dbg.declare(metadata i32* %have_signals, metadata !1013, metadata !760), !dbg !1014
  call void @llvm.dbg.declare(metadata i32* %nevents, metadata !1015, metadata !760), !dbg !1016
  call void @llvm.dbg.declare(metadata i32* %count, metadata !1017, metadata !760), !dbg !1018
  call void @llvm.dbg.declare(metadata i32* %nfds, metadata !1019, metadata !760), !dbg !1020
  call void @llvm.dbg.declare(metadata i32* %fd, metadata !1021, metadata !760), !dbg !1022
  call void @llvm.dbg.declare(metadata i32* %op, metadata !1023, metadata !760), !dbg !1024
  call void @llvm.dbg.declare(metadata i32* %i, metadata !1025, metadata !760), !dbg !1026
  %0 = load %struct.uv_loop_s*, %struct.uv_loop_s** %loop.addr, align 8, !dbg !1027
  %nfds1 = getelementptr inbounds %struct.uv_loop_s, %struct.uv_loop_s* %0, i32 0, i32 11, !dbg !1029
  %1 = load i32, i32* %nfds1, align 4, !dbg !1029
  %cmp = icmp eq i32 %1, 0, !dbg !1030
  br i1 %cmp, label %if.then, label %if.end, !dbg !1031

if.then:                                          ; preds = %entry
  %2 = load %struct.uv_loop_s*, %struct.uv_loop_s** %loop.addr, align 8, !dbg !1032
  %watcher_queue = getelementptr inbounds %struct.uv_loop_s, %struct.uv_loop_s* %2, i32 0, i32 8, !dbg !1032
  %3 = load %struct.uv_loop_s*, %struct.uv_loop_s** %loop.addr, align 8, !dbg !1032
  %watcher_queue2 = getelementptr inbounds %struct.uv_loop_s, %struct.uv_loop_s* %3, i32 0, i32 8, !dbg !1032
  %arrayidx = getelementptr inbounds [2 x i8*], [2 x i8*]* %watcher_queue2, i64 0, i64 0, !dbg !1032
  %4 = bitcast i8** %arrayidx to [2 x i8*]**, !dbg !1032
  %5 = load [2 x i8*]*, [2 x i8*]** %4, align 8, !dbg !1032
  %cmp3 = icmp eq [2 x i8*]* %watcher_queue, %5, !dbg !1032
  br i1 %cmp3, label %cond.true, label %cond.false, !dbg !1032

cond.true:                                        ; preds = %if.then
  br label %cond.end, !dbg !1034

cond.false:                                       ; preds = %if.then
  call void @__assert_fail(i8* getelementptr inbounds ([106 x i8], [106 x i8]* @.str.2, i32 0, i32 0), i8* getelementptr inbounds ([74 x i8], [74 x i8]* @.str.1, i32 0, i32 0), i32 218, i8* getelementptr inbounds ([35 x i8], [35 x i8]* @__PRETTY_FUNCTION__.uv__io_poll, i32 0, i32 0)) #8, !dbg !1036
  unreachable, !dbg !1036
                                                  ; No predecessors!
  br label %cond.end, !dbg !1038

cond.end:                                         ; preds = %6, %cond.true
  br label %return, !dbg !1040

if.end:                                           ; preds = %entry
  br label %while.cond, !dbg !1041

while.cond:                                       ; preds = %if.end60, %if.end
  %7 = load %struct.uv_loop_s*, %struct.uv_loop_s** %loop.addr, align 8, !dbg !1042
  %watcher_queue4 = getelementptr inbounds %struct.uv_loop_s, %struct.uv_loop_s* %7, i32 0, i32 8, !dbg !1042
  %8 = load %struct.uv_loop_s*, %struct.uv_loop_s** %loop.addr, align 8, !dbg !1042
  %watcher_queue5 = getelementptr inbounds %struct.uv_loop_s, %struct.uv_loop_s* %8, i32 0, i32 8, !dbg !1042
  %arrayidx6 = getelementptr inbounds [2 x i8*], [2 x i8*]* %watcher_queue5, i64 0, i64 0, !dbg !1042
  %9 = bitcast i8** %arrayidx6 to [2 x i8*]**, !dbg !1042
  %10 = load [2 x i8*]*, [2 x i8*]** %9, align 8, !dbg !1042
  %cmp7 = icmp eq [2 x i8*]* %watcher_queue4, %10, !dbg !1042
  %lnot = xor i1 %cmp7, true, !dbg !1044
  br i1 %lnot, label %while.body, label %while.end, !dbg !1045

while.body:                                       ; preds = %while.cond
  %11 = load %struct.uv_loop_s*, %struct.uv_loop_s** %loop.addr, align 8, !dbg !1046
  %watcher_queue8 = getelementptr inbounds %struct.uv_loop_s, %struct.uv_loop_s* %11, i32 0, i32 8, !dbg !1046
  %arrayidx9 = getelementptr inbounds [2 x i8*], [2 x i8*]* %watcher_queue8, i64 0, i64 0, !dbg !1046
  %12 = bitcast i8** %arrayidx9 to [2 x i8*]**, !dbg !1046
  %13 = load [2 x i8*]*, [2 x i8*]** %12, align 8, !dbg !1046
  store [2 x i8*]* %13, [2 x i8*]** %q, align 8, !dbg !1048
  br label %do.body, !dbg !1049

do.body:                                          ; preds = %while.body
  %14 = load [2 x i8*]*, [2 x i8*]** %q, align 8, !dbg !1050
  %arrayidx10 = getelementptr inbounds [2 x i8*], [2 x i8*]* %14, i64 0, i64 0, !dbg !1050
  %15 = bitcast i8** %arrayidx10 to [2 x i8*]**, !dbg !1050
  %16 = load [2 x i8*]*, [2 x i8*]** %15, align 8, !dbg !1050
  %17 = load [2 x i8*]*, [2 x i8*]** %q, align 8, !dbg !1050
  %arrayidx11 = getelementptr inbounds [2 x i8*], [2 x i8*]* %17, i64 0, i64 1, !dbg !1050
  %18 = bitcast i8** %arrayidx11 to [2 x i8*]**, !dbg !1050
  %19 = load [2 x i8*]*, [2 x i8*]** %18, align 8, !dbg !1050
  %arrayidx12 = getelementptr inbounds [2 x i8*], [2 x i8*]* %19, i64 0, i64 0, !dbg !1050
  %20 = bitcast i8** %arrayidx12 to [2 x i8*]**, !dbg !1050
  store [2 x i8*]* %16, [2 x i8*]** %20, align 8, !dbg !1050
  %21 = load [2 x i8*]*, [2 x i8*]** %q, align 8, !dbg !1050
  %arrayidx13 = getelementptr inbounds [2 x i8*], [2 x i8*]* %21, i64 0, i64 1, !dbg !1050
  %22 = bitcast i8** %arrayidx13 to [2 x i8*]**, !dbg !1050
  %23 = load [2 x i8*]*, [2 x i8*]** %22, align 8, !dbg !1050
  %24 = load [2 x i8*]*, [2 x i8*]** %q, align 8, !dbg !1050
  %arrayidx14 = getelementptr inbounds [2 x i8*], [2 x i8*]* %24, i64 0, i64 0, !dbg !1050
  %25 = bitcast i8** %arrayidx14 to [2 x i8*]**, !dbg !1050
  %26 = load [2 x i8*]*, [2 x i8*]** %25, align 8, !dbg !1050
  %arrayidx15 = getelementptr inbounds [2 x i8*], [2 x i8*]* %26, i64 0, i64 1, !dbg !1050
  %27 = bitcast i8** %arrayidx15 to [2 x i8*]**, !dbg !1050
  store [2 x i8*]* %23, [2 x i8*]** %27, align 8, !dbg !1050
  br label %do.end, !dbg !1050

do.end:                                           ; preds = %do.body
  br label %do.body16, !dbg !1053

do.body16:                                        ; preds = %do.end
  %28 = load [2 x i8*]*, [2 x i8*]** %q, align 8, !dbg !1054
  %29 = load [2 x i8*]*, [2 x i8*]** %q, align 8, !dbg !1054
  %arrayidx17 = getelementptr inbounds [2 x i8*], [2 x i8*]* %29, i64 0, i64 0, !dbg !1054
  %30 = bitcast i8** %arrayidx17 to [2 x i8*]**, !dbg !1054
  store [2 x i8*]* %28, [2 x i8*]** %30, align 8, !dbg !1054
  %31 = load [2 x i8*]*, [2 x i8*]** %q, align 8, !dbg !1054
  %32 = load [2 x i8*]*, [2 x i8*]** %q, align 8, !dbg !1054
  %arrayidx18 = getelementptr inbounds [2 x i8*], [2 x i8*]* %32, i64 0, i64 1, !dbg !1054
  %33 = bitcast i8** %arrayidx18 to [2 x i8*]**, !dbg !1054
  store [2 x i8*]* %31, [2 x i8*]** %33, align 8, !dbg !1054
  br label %do.end19, !dbg !1054

do.end19:                                         ; preds = %do.body16
  %34 = load [2 x i8*]*, [2 x i8*]** %q, align 8, !dbg !1057
  %35 = bitcast [2 x i8*]* %34 to i8*, !dbg !1057
  %add.ptr = getelementptr inbounds i8, i8* %35, i64 -24, !dbg !1057
  %36 = bitcast i8* %add.ptr to %struct.uv__io_s*, !dbg !1057
  store %struct.uv__io_s* %36, %struct.uv__io_s** %w, align 8, !dbg !1058
  %37 = load %struct.uv__io_s*, %struct.uv__io_s** %w, align 8, !dbg !1059
  %pevents = getelementptr inbounds %struct.uv__io_s, %struct.uv__io_s* %37, i32 0, i32 3, !dbg !1059
  %38 = load i32, i32* %pevents, align 8, !dbg !1059
  %cmp20 = icmp ne i32 %38, 0, !dbg !1059
  br i1 %cmp20, label %cond.true21, label %cond.false22, !dbg !1059

cond.true21:                                      ; preds = %do.end19
  br label %cond.end23, !dbg !1060

cond.false22:                                     ; preds = %do.end19
  call void @__assert_fail(i8* getelementptr inbounds ([16 x i8], [16 x i8]* @.str.3, i32 0, i32 0), i8* getelementptr inbounds ([74 x i8], [74 x i8]* @.str.1, i32 0, i32 0), i32 228, i8* getelementptr inbounds ([35 x i8], [35 x i8]* @__PRETTY_FUNCTION__.uv__io_poll, i32 0, i32 0)) #8, !dbg !1062
  unreachable, !dbg !1062
                                                  ; No predecessors!
  br label %cond.end23, !dbg !1064

cond.end23:                                       ; preds = %39, %cond.true21
  %40 = load %struct.uv__io_s*, %struct.uv__io_s** %w, align 8, !dbg !1066
  %fd24 = getelementptr inbounds %struct.uv__io_s, %struct.uv__io_s* %40, i32 0, i32 5, !dbg !1066
  %41 = load i32, i32* %fd24, align 8, !dbg !1066
  %cmp25 = icmp sge i32 %41, 0, !dbg !1066
  br i1 %cmp25, label %cond.true26, label %cond.false27, !dbg !1066

cond.true26:                                      ; preds = %cond.end23
  br label %cond.end28, !dbg !1067

cond.false27:                                     ; preds = %cond.end23
  call void @__assert_fail(i8* getelementptr inbounds ([11 x i8], [11 x i8]* @.str.4, i32 0, i32 0), i8* getelementptr inbounds ([74 x i8], [74 x i8]* @.str.1, i32 0, i32 0), i32 229, i8* getelementptr inbounds ([35 x i8], [35 x i8]* @__PRETTY_FUNCTION__.uv__io_poll, i32 0, i32 0)) #8, !dbg !1068
  unreachable, !dbg !1068
                                                  ; No predecessors!
  br label %cond.end28, !dbg !1069

cond.end28:                                       ; preds = %42, %cond.true26
  %43 = load %struct.uv__io_s*, %struct.uv__io_s** %w, align 8, !dbg !1070
  %fd29 = getelementptr inbounds %struct.uv__io_s, %struct.uv__io_s* %43, i32 0, i32 5, !dbg !1070
  %44 = load i32, i32* %fd29, align 8, !dbg !1070
  %45 = load %struct.uv_loop_s*, %struct.uv_loop_s** %loop.addr, align 8, !dbg !1070
  %nwatchers = getelementptr inbounds %struct.uv_loop_s, %struct.uv_loop_s* %45, i32 0, i32 10, !dbg !1070
  %46 = load i32, i32* %nwatchers, align 8, !dbg !1070
  %cmp30 = icmp slt i32 %44, %46, !dbg !1070
  br i1 %cmp30, label %cond.true31, label %cond.false32, !dbg !1070

cond.true31:                                      ; preds = %cond.end28
  br label %cond.end33, !dbg !1071

cond.false32:                                     ; preds = %cond.end28
  call void @__assert_fail(i8* getelementptr inbounds ([30 x i8], [30 x i8]* @.str.5, i32 0, i32 0), i8* getelementptr inbounds ([74 x i8], [74 x i8]* @.str.1, i32 0, i32 0), i32 230, i8* getelementptr inbounds ([35 x i8], [35 x i8]* @__PRETTY_FUNCTION__.uv__io_poll, i32 0, i32 0)) #8, !dbg !1072
  unreachable, !dbg !1072
                                                  ; No predecessors!
  br label %cond.end33, !dbg !1073

cond.end33:                                       ; preds = %47, %cond.true31
  %48 = load %struct.uv__io_s*, %struct.uv__io_s** %w, align 8, !dbg !1074
  %pevents34 = getelementptr inbounds %struct.uv__io_s, %struct.uv__io_s* %48, i32 0, i32 3, !dbg !1075
  %49 = load i32, i32* %pevents34, align 8, !dbg !1075
  %events35 = getelementptr inbounds %struct.uv__epoll_event, %struct.uv__epoll_event* %e, i32 0, i32 0, !dbg !1076
  store i32 %49, i32* %events35, align 1, !dbg !1077
  %50 = load %struct.uv__io_s*, %struct.uv__io_s** %w, align 8, !dbg !1078
  %fd36 = getelementptr inbounds %struct.uv__io_s, %struct.uv__io_s* %50, i32 0, i32 5, !dbg !1079
  %51 = load i32, i32* %fd36, align 8, !dbg !1079
  %conv = sext i32 %51 to i64, !dbg !1078
  %data = getelementptr inbounds %struct.uv__epoll_event, %struct.uv__epoll_event* %e, i32 0, i32 1, !dbg !1080
  store i64 %conv, i64* %data, align 1, !dbg !1081
  %52 = load %struct.uv__io_s*, %struct.uv__io_s** %w, align 8, !dbg !1082
  %events37 = getelementptr inbounds %struct.uv__io_s, %struct.uv__io_s* %52, i32 0, i32 4, !dbg !1084
  %53 = load i32, i32* %events37, align 4, !dbg !1084
  %cmp38 = icmp eq i32 %53, 0, !dbg !1085
  br i1 %cmp38, label %if.then40, label %if.else, !dbg !1086

if.then40:                                        ; preds = %cond.end33
  store i32 1, i32* %op, align 4, !dbg !1087
  br label %if.end41, !dbg !1088

if.else:                                          ; preds = %cond.end33
  store i32 3, i32* %op, align 4, !dbg !1089
  br label %if.end41

if.end41:                                         ; preds = %if.else, %if.then40
  %54 = load %struct.uv_loop_s*, %struct.uv_loop_s** %loop.addr, align 8, !dbg !1090
  %backend_fd = getelementptr inbounds %struct.uv_loop_s, %struct.uv_loop_s* %54, i32 0, i32 6, !dbg !1092
  %55 = load i32, i32* %backend_fd, align 8, !dbg !1092
  %56 = load i32, i32* %op, align 4, !dbg !1093
  %57 = load %struct.uv__io_s*, %struct.uv__io_s** %w, align 8, !dbg !1094
  %fd42 = getelementptr inbounds %struct.uv__io_s, %struct.uv__io_s* %57, i32 0, i32 5, !dbg !1095
  %58 = load i32, i32* %fd42, align 8, !dbg !1095
  %call = call i32 @uv__epoll_ctl(i32 %55, i32 %56, i32 %58, %struct.uv__epoll_event* %e), !dbg !1096
  %tobool = icmp ne i32 %call, 0, !dbg !1096
  br i1 %tobool, label %if.then43, label %if.end60, !dbg !1097

if.then43:                                        ; preds = %if.end41
  %call44 = call i32* @__errno_location() #1, !dbg !1098
  %59 = load i32, i32* %call44, align 4, !dbg !1098
  %cmp45 = icmp ne i32 %59, 17, !dbg !1101
  br i1 %cmp45, label %if.then47, label %if.end48, !dbg !1102

if.then47:                                        ; preds = %if.then43
  call void @abort() #8, !dbg !1103
  unreachable, !dbg !1103

if.end48:                                         ; preds = %if.then43
  %60 = load i32, i32* %op, align 4, !dbg !1104
  %cmp49 = icmp eq i32 %60, 1, !dbg !1104
  br i1 %cmp49, label %cond.true51, label %cond.false52, !dbg !1104

cond.true51:                                      ; preds = %if.end48
  br label %cond.end53, !dbg !1105

cond.false52:                                     ; preds = %if.end48
  call void @__assert_fail(i8* getelementptr inbounds ([8 x i8], [8 x i8]* @.str.6, i32 0, i32 0), i8* getelementptr inbounds ([74 x i8], [74 x i8]* @.str.1, i32 0, i32 0), i32 247, i8* getelementptr inbounds ([35 x i8], [35 x i8]* @__PRETTY_FUNCTION__.uv__io_poll, i32 0, i32 0)) #8, !dbg !1107
  unreachable, !dbg !1107
                                                  ; No predecessors!
  br label %cond.end53, !dbg !1109

cond.end53:                                       ; preds = %61, %cond.true51
  %62 = load %struct.uv_loop_s*, %struct.uv_loop_s** %loop.addr, align 8, !dbg !1111
  %backend_fd54 = getelementptr inbounds %struct.uv_loop_s, %struct.uv_loop_s* %62, i32 0, i32 6, !dbg !1113
  %63 = load i32, i32* %backend_fd54, align 8, !dbg !1113
  %64 = load %struct.uv__io_s*, %struct.uv__io_s** %w, align 8, !dbg !1114
  %fd55 = getelementptr inbounds %struct.uv__io_s, %struct.uv__io_s* %64, i32 0, i32 5, !dbg !1115
  %65 = load i32, i32* %fd55, align 8, !dbg !1115
  %call56 = call i32 @uv__epoll_ctl(i32 %63, i32 3, i32 %65, %struct.uv__epoll_event* %e), !dbg !1116
  %tobool57 = icmp ne i32 %call56, 0, !dbg !1116
  br i1 %tobool57, label %if.then58, label %if.end59, !dbg !1117

if.then58:                                        ; preds = %cond.end53
  call void @abort() #8, !dbg !1118
  unreachable, !dbg !1118

if.end59:                                         ; preds = %cond.end53
  br label %if.end60, !dbg !1119

if.end60:                                         ; preds = %if.end59, %if.end41
  %66 = load %struct.uv__io_s*, %struct.uv__io_s** %w, align 8, !dbg !1120
  %pevents61 = getelementptr inbounds %struct.uv__io_s, %struct.uv__io_s* %66, i32 0, i32 3, !dbg !1121
  %67 = load i32, i32* %pevents61, align 8, !dbg !1121
  %68 = load %struct.uv__io_s*, %struct.uv__io_s** %w, align 8, !dbg !1122
  %events62 = getelementptr inbounds %struct.uv__io_s, %struct.uv__io_s* %68, i32 0, i32 4, !dbg !1123
  store i32 %67, i32* %events62, align 4, !dbg !1124
  br label %while.cond, !dbg !1125

while.end:                                        ; preds = %while.cond
  store i64 0, i64* %sigmask, align 8, !dbg !1127
  %69 = load %struct.uv_loop_s*, %struct.uv_loop_s** %loop.addr, align 8, !dbg !1128
  %flags = getelementptr inbounds %struct.uv_loop_s, %struct.uv_loop_s* %69, i32 0, i32 5, !dbg !1130
  %70 = load i64, i64* %flags, align 8, !dbg !1130
  %and = and i64 %70, 1, !dbg !1131
  %tobool63 = icmp ne i64 %and, 0, !dbg !1131
  br i1 %tobool63, label %if.then64, label %if.end67, !dbg !1132

if.then64:                                        ; preds = %while.end
  %call65 = call i32 @sigemptyset(%struct.__sigset_t* %sigset) #9, !dbg !1133
  %call66 = call i32 @sigaddset(%struct.__sigset_t* %sigset, i32 27) #9, !dbg !1135
  %71 = load i64, i64* %sigmask, align 8, !dbg !1136
  %or = or i64 %71, 67108864, !dbg !1136
  store i64 %or, i64* %sigmask, align 8, !dbg !1136
  br label %if.end67, !dbg !1137

if.end67:                                         ; preds = %if.then64, %while.end
  %72 = load i32, i32* %timeout.addr, align 4, !dbg !1138
  %cmp68 = icmp sge i32 %72, -1, !dbg !1138
  br i1 %cmp68, label %cond.true70, label %cond.false71, !dbg !1138

cond.true70:                                      ; preds = %if.end67
  br label %cond.end72, !dbg !1139

cond.false71:                                     ; preds = %if.end67
  call void @__assert_fail(i8* getelementptr inbounds ([14 x i8], [14 x i8]* @.str.7, i32 0, i32 0), i8* getelementptr inbounds ([74 x i8], [74 x i8]* @.str.1, i32 0, i32 0), i32 264, i8* getelementptr inbounds ([35 x i8], [35 x i8]* @__PRETTY_FUNCTION__.uv__io_poll, i32 0, i32 0)) #8, !dbg !1140
  unreachable, !dbg !1140
                                                  ; No predecessors!
  br label %cond.end72, !dbg !1141

cond.end72:                                       ; preds = %73, %cond.true70
  %74 = load %struct.uv_loop_s*, %struct.uv_loop_s** %loop.addr, align 8, !dbg !1143
  %time = getelementptr inbounds %struct.uv_loop_s, %struct.uv_loop_s* %74, i32 0, i32 27, !dbg !1144
  %75 = load i64, i64* %time, align 8, !dbg !1144
  store i64 %75, i64* %base, align 8, !dbg !1145
  store i32 48, i32* %count, align 4, !dbg !1146
  %76 = load i32, i32* %timeout.addr, align 4, !dbg !1147
  store i32 %76, i32* %real_timeout, align 4, !dbg !1148
  br label %for.cond, !dbg !1149

for.cond:                                         ; preds = %if.end301, %if.then287, %if.then278, %if.then167, %cond.end158, %cond.end72
  %77 = load i64, i64* %sigmask, align 8, !dbg !1150
  %cmp73 = icmp ne i64 %77, 0, !dbg !1155
  br i1 %cmp73, label %land.lhs.true, label %if.end82, !dbg !1156

land.lhs.true:                                    ; preds = %for.cond
  %78 = load i32, i32* @uv__io_poll.no_epoll_pwait, align 4, !dbg !1157
  %cmp75 = icmp ne i32 %78, 0, !dbg !1159
  br i1 %cmp75, label %if.then77, label %if.end82, !dbg !1160

if.then77:                                        ; preds = %land.lhs.true
  %call78 = call i32 @pthread_sigmask(i32 0, %struct.__sigset_t* %sigset, %struct.__sigset_t* null) #9, !dbg !1161
  %tobool79 = icmp ne i32 %call78, 0, !dbg !1161
  br i1 %tobool79, label %if.then80, label %if.end81, !dbg !1163

if.then80:                                        ; preds = %if.then77
  call void @abort() #8, !dbg !1164
  unreachable, !dbg !1164

if.end81:                                         ; preds = %if.then77
  br label %if.end82, !dbg !1165

if.end82:                                         ; preds = %if.end81, %land.lhs.true, %for.cond
  %79 = load i32, i32* @uv__io_poll.no_epoll_wait, align 4, !dbg !1167
  %cmp83 = icmp ne i32 %79, 0, !dbg !1169
  br i1 %cmp83, label %if.then90, label %lor.lhs.false, !dbg !1170

lor.lhs.false:                                    ; preds = %if.end82
  %80 = load i64, i64* %sigmask, align 8, !dbg !1171
  %cmp85 = icmp ne i64 %80, 0, !dbg !1173
  br i1 %cmp85, label %land.lhs.true87, label %if.else101, !dbg !1174

land.lhs.true87:                                  ; preds = %lor.lhs.false
  %81 = load i32, i32* @uv__io_poll.no_epoll_pwait, align 4, !dbg !1175
  %cmp88 = icmp eq i32 %81, 0, !dbg !1177
  br i1 %cmp88, label %if.then90, label %if.else101, !dbg !1178

if.then90:                                        ; preds = %land.lhs.true87, %if.end82
  %82 = load %struct.uv_loop_s*, %struct.uv_loop_s** %loop.addr, align 8, !dbg !1179
  %backend_fd91 = getelementptr inbounds %struct.uv_loop_s, %struct.uv_loop_s* %82, i32 0, i32 6, !dbg !1181
  %83 = load i32, i32* %backend_fd91, align 8, !dbg !1181
  %arraydecay = getelementptr inbounds [1024 x %struct.uv__epoll_event], [1024 x %struct.uv__epoll_event]* %events, i32 0, i32 0, !dbg !1182
  %84 = load i32, i32* %timeout.addr, align 4, !dbg !1183
  %85 = load i64, i64* %sigmask, align 8, !dbg !1184
  %call92 = call i32 @uv__epoll_pwait(i32 %83, %struct.uv__epoll_event* %arraydecay, i32 1024, i32 %84, i64 %85), !dbg !1185
  store i32 %call92, i32* %nfds, align 4, !dbg !1186
  %86 = load i32, i32* %nfds, align 4, !dbg !1187
  %cmp93 = icmp eq i32 %86, -1, !dbg !1189
  br i1 %cmp93, label %land.lhs.true95, label %if.end100, !dbg !1190

land.lhs.true95:                                  ; preds = %if.then90
  %call96 = call i32* @__errno_location() #1, !dbg !1191
  %87 = load i32, i32* %call96, align 4, !dbg !1191
  %cmp97 = icmp eq i32 %87, 38, !dbg !1193
  br i1 %cmp97, label %if.then99, label %if.end100, !dbg !1194

if.then99:                                        ; preds = %land.lhs.true95
  store i32 1, i32* @uv__io_poll.no_epoll_pwait, align 4, !dbg !1195
  br label %if.end100, !dbg !1196

if.end100:                                        ; preds = %if.then99, %land.lhs.true95, %if.then90
  br label %if.end113, !dbg !1197

if.else101:                                       ; preds = %land.lhs.true87, %lor.lhs.false
  %88 = load %struct.uv_loop_s*, %struct.uv_loop_s** %loop.addr, align 8, !dbg !1198
  %backend_fd102 = getelementptr inbounds %struct.uv_loop_s, %struct.uv_loop_s* %88, i32 0, i32 6, !dbg !1200
  %89 = load i32, i32* %backend_fd102, align 8, !dbg !1200
  %arraydecay103 = getelementptr inbounds [1024 x %struct.uv__epoll_event], [1024 x %struct.uv__epoll_event]* %events, i32 0, i32 0, !dbg !1201
  %90 = load i32, i32* %timeout.addr, align 4, !dbg !1202
  %call104 = call i32 @uv__epoll_wait(i32 %89, %struct.uv__epoll_event* %arraydecay103, i32 1024, i32 %90), !dbg !1203
  store i32 %call104, i32* %nfds, align 4, !dbg !1204
  %91 = load i32, i32* %nfds, align 4, !dbg !1205
  %cmp105 = icmp eq i32 %91, -1, !dbg !1207
  br i1 %cmp105, label %land.lhs.true107, label %if.end112, !dbg !1208

land.lhs.true107:                                 ; preds = %if.else101
  %call108 = call i32* @__errno_location() #1, !dbg !1209
  %92 = load i32, i32* %call108, align 4, !dbg !1209
  %cmp109 = icmp eq i32 %92, 38, !dbg !1211
  br i1 %cmp109, label %if.then111, label %if.end112, !dbg !1212

if.then111:                                       ; preds = %land.lhs.true107
  store i32 1, i32* @uv__io_poll.no_epoll_wait, align 4, !dbg !1213
  br label %if.end112, !dbg !1214

if.end112:                                        ; preds = %if.then111, %land.lhs.true107, %if.else101
  br label %if.end113

if.end113:                                        ; preds = %if.end112, %if.end100
  %93 = load i64, i64* %sigmask, align 8, !dbg !1215
  %cmp114 = icmp ne i64 %93, 0, !dbg !1217
  br i1 %cmp114, label %land.lhs.true116, label %if.end124, !dbg !1218

land.lhs.true116:                                 ; preds = %if.end113
  %94 = load i32, i32* @uv__io_poll.no_epoll_pwait, align 4, !dbg !1219
  %cmp117 = icmp ne i32 %94, 0, !dbg !1221
  br i1 %cmp117, label %if.then119, label %if.end124, !dbg !1222

if.then119:                                       ; preds = %land.lhs.true116
  %call120 = call i32 @pthread_sigmask(i32 1, %struct.__sigset_t* %sigset, %struct.__sigset_t* null) #9, !dbg !1223
  %tobool121 = icmp ne i32 %call120, 0, !dbg !1223
  br i1 %tobool121, label %if.then122, label %if.end123, !dbg !1225

if.then122:                                       ; preds = %if.then119
  call void @abort() #8, !dbg !1226
  unreachable, !dbg !1226

if.end123:                                        ; preds = %if.then119
  br label %if.end124, !dbg !1227

if.end124:                                        ; preds = %if.end123, %land.lhs.true116, %if.end113
  br label %do.body125, !dbg !1229

do.body125:                                       ; preds = %if.end124
  call void @llvm.dbg.declare(metadata i32* %_saved_errno, metadata !1230, metadata !760), !dbg !1232
  %call126 = call i32* @__errno_location() #1, !dbg !1233
  %95 = load i32, i32* %call126, align 4, !dbg !1233
  store i32 %95, i32* %_saved_errno, align 4, !dbg !1233
  br label %do.body127, !dbg !1233

do.body127:                                       ; preds = %do.body125
  %96 = load %struct.uv_loop_s*, %struct.uv_loop_s** %loop.addr, align 8, !dbg !1235
  call void @uv__update_time(%struct.uv_loop_s* %96), !dbg !1235
  br label %do.end128, !dbg !1235

do.end128:                                        ; preds = %do.body127
  %97 = load i32, i32* %_saved_errno, align 4, !dbg !1238
  %call129 = call i32* @__errno_location() #1, !dbg !1238
  store i32 %97, i32* %call129, align 4, !dbg !1238
  br label %do.end130, !dbg !1238

do.end130:                                        ; preds = %do.end128
  %98 = load i32, i32* %nfds, align 4, !dbg !1240
  %cmp131 = icmp eq i32 %98, 0, !dbg !1242
  br i1 %cmp131, label %if.then133, label %if.end143, !dbg !1243

if.then133:                                       ; preds = %do.end130
  %99 = load i32, i32* %timeout.addr, align 4, !dbg !1244
  %cmp134 = icmp ne i32 %99, -1, !dbg !1244
  br i1 %cmp134, label %cond.true136, label %cond.false137, !dbg !1244

cond.true136:                                     ; preds = %if.then133
  br label %cond.end138, !dbg !1246

cond.false137:                                    ; preds = %if.then133
  call void @__assert_fail(i8* getelementptr inbounds ([14 x i8], [14 x i8]* @.str.8, i32 0, i32 0), i8* getelementptr inbounds ([74 x i8], [74 x i8]* @.str.1, i32 0, i32 0), i32 308, i8* getelementptr inbounds ([35 x i8], [35 x i8]* @__PRETTY_FUNCTION__.uv__io_poll, i32 0, i32 0)) #8, !dbg !1248
  unreachable, !dbg !1248
                                                  ; No predecessors!
  br label %cond.end138, !dbg !1250

cond.end138:                                      ; preds = %100, %cond.true136
  %101 = load i32, i32* %timeout.addr, align 4, !dbg !1252
  %cmp139 = icmp eq i32 %101, 0, !dbg !1254
  br i1 %cmp139, label %if.then141, label %if.end142, !dbg !1255

if.then141:                                       ; preds = %cond.end138
  br label %return, !dbg !1256

if.end142:                                        ; preds = %cond.end138
  br label %update_timeout, !dbg !1257

if.end143:                                        ; preds = %do.end130
  %102 = load i32, i32* %nfds, align 4, !dbg !1258
  %cmp144 = icmp eq i32 %102, -1, !dbg !1260
  br i1 %cmp144, label %if.then146, label %if.end173, !dbg !1261

if.then146:                                       ; preds = %if.end143
  %call147 = call i32* @__errno_location() #1, !dbg !1262
  %103 = load i32, i32* %call147, align 4, !dbg !1262
  %cmp148 = icmp eq i32 %103, 38, !dbg !1265
  br i1 %cmp148, label %if.then150, label %if.end159, !dbg !1266

if.then150:                                       ; preds = %if.then146
  %104 = load i32, i32* @uv__io_poll.no_epoll_wait, align 4, !dbg !1267
  %cmp151 = icmp eq i32 %104, 0, !dbg !1267
  br i1 %cmp151, label %cond.true156, label %lor.lhs.false153, !dbg !1267

lor.lhs.false153:                                 ; preds = %if.then150
  %105 = load i32, i32* @uv__io_poll.no_epoll_pwait, align 4, !dbg !1269
  %cmp154 = icmp eq i32 %105, 0, !dbg !1269
  br i1 %cmp154, label %cond.true156, label %cond.false157, !dbg !1269

cond.true156:                                     ; preds = %lor.lhs.false153, %if.then150
  br label %cond.end158, !dbg !1271

cond.false157:                                    ; preds = %lor.lhs.false153
  call void @__assert_fail(i8* getelementptr inbounds ([42 x i8], [42 x i8]* @.str.9, i32 0, i32 0), i8* getelementptr inbounds ([74 x i8], [74 x i8]* @.str.1, i32 0, i32 0), i32 322, i8* getelementptr inbounds ([35 x i8], [35 x i8]* @__PRETTY_FUNCTION__.uv__io_poll, i32 0, i32 0)) #8, !dbg !1273
  unreachable, !dbg !1273
                                                  ; No predecessors!
  br label %cond.end158, !dbg !1275

cond.end158:                                      ; preds = %106, %cond.true156
  br label %for.cond, !dbg !1277

if.end159:                                        ; preds = %if.then146
  %call160 = call i32* @__errno_location() #1, !dbg !1278
  %107 = load i32, i32* %call160, align 4, !dbg !1278
  %cmp161 = icmp ne i32 %107, 4, !dbg !1280
  br i1 %cmp161, label %if.then163, label %if.end164, !dbg !1281

if.then163:                                       ; preds = %if.end159
  call void @abort() #8, !dbg !1282
  unreachable, !dbg !1282

if.end164:                                        ; preds = %if.end159
  %108 = load i32, i32* %timeout.addr, align 4, !dbg !1283
  %cmp165 = icmp eq i32 %108, -1, !dbg !1285
  br i1 %cmp165, label %if.then167, label %if.end168, !dbg !1286

if.then167:                                       ; preds = %if.end164
  br label %for.cond, !dbg !1287

if.end168:                                        ; preds = %if.end164
  %109 = load i32, i32* %timeout.addr, align 4, !dbg !1288
  %cmp169 = icmp eq i32 %109, 0, !dbg !1290
  br i1 %cmp169, label %if.then171, label %if.end172, !dbg !1291

if.then171:                                       ; preds = %if.end168
  br label %return, !dbg !1292

if.end172:                                        ; preds = %if.end168
  br label %update_timeout, !dbg !1293

if.end173:                                        ; preds = %if.end143
  store i32 0, i32* %have_signals, align 4, !dbg !1294
  store i32 0, i32* %nevents, align 4, !dbg !1295
  %110 = load %struct.uv_loop_s*, %struct.uv_loop_s** %loop.addr, align 8, !dbg !1296
  %watchers = getelementptr inbounds %struct.uv_loop_s, %struct.uv_loop_s* %110, i32 0, i32 9, !dbg !1296
  %111 = load %struct.uv__io_s**, %struct.uv__io_s*** %watchers, align 8, !dbg !1296
  %cmp174 = icmp ne %struct.uv__io_s** %111, null, !dbg !1296
  br i1 %cmp174, label %cond.true176, label %cond.false177, !dbg !1296

cond.true176:                                     ; preds = %if.end173
  br label %cond.end178, !dbg !1297

cond.false177:                                    ; preds = %if.end173
  call void @__assert_fail(i8* getelementptr inbounds ([29 x i8], [29 x i8]* @.str, i32 0, i32 0), i8* getelementptr inbounds ([74 x i8], [74 x i8]* @.str.1, i32 0, i32 0), i32 342, i8* getelementptr inbounds ([35 x i8], [35 x i8]* @__PRETTY_FUNCTION__.uv__io_poll, i32 0, i32 0)) #8, !dbg !1299
  unreachable, !dbg !1299
                                                  ; No predecessors!
  br label %cond.end178, !dbg !1301

cond.end178:                                      ; preds = %112, %cond.true176
  %arraydecay179 = getelementptr inbounds [1024 x %struct.uv__epoll_event], [1024 x %struct.uv__epoll_event]* %events, i32 0, i32 0, !dbg !1303
  %113 = bitcast %struct.uv__epoll_event* %arraydecay179 to i8*, !dbg !1304
  %114 = bitcast i8* %113 to %struct.uv__io_s*, !dbg !1304
  %115 = load %struct.uv_loop_s*, %struct.uv_loop_s** %loop.addr, align 8, !dbg !1305
  %nwatchers180 = getelementptr inbounds %struct.uv_loop_s, %struct.uv_loop_s* %115, i32 0, i32 10, !dbg !1306
  %116 = load i32, i32* %nwatchers180, align 8, !dbg !1306
  %idxprom = zext i32 %116 to i64, !dbg !1307
  %117 = load %struct.uv_loop_s*, %struct.uv_loop_s** %loop.addr, align 8, !dbg !1307
  %watchers181 = getelementptr inbounds %struct.uv_loop_s, %struct.uv_loop_s* %117, i32 0, i32 9, !dbg !1308
  %118 = load %struct.uv__io_s**, %struct.uv__io_s*** %watchers181, align 8, !dbg !1308
  %arrayidx182 = getelementptr inbounds %struct.uv__io_s*, %struct.uv__io_s** %118, i64 %idxprom, !dbg !1307
  store %struct.uv__io_s* %114, %struct.uv__io_s** %arrayidx182, align 8, !dbg !1309
  %119 = load i32, i32* %nfds, align 4, !dbg !1310
  %conv183 = sext i32 %119 to i64, !dbg !1311
  %120 = inttoptr i64 %conv183 to i8*, !dbg !1312
  %121 = bitcast i8* %120 to %struct.uv__io_s*, !dbg !1312
  %122 = load %struct.uv_loop_s*, %struct.uv_loop_s** %loop.addr, align 8, !dbg !1313
  %nwatchers184 = getelementptr inbounds %struct.uv_loop_s, %struct.uv_loop_s* %122, i32 0, i32 10, !dbg !1314
  %123 = load i32, i32* %nwatchers184, align 8, !dbg !1314
  %add = add i32 %123, 1, !dbg !1315
  %idxprom185 = zext i32 %add to i64, !dbg !1316
  %124 = load %struct.uv_loop_s*, %struct.uv_loop_s** %loop.addr, align 8, !dbg !1316
  %watchers186 = getelementptr inbounds %struct.uv_loop_s, %struct.uv_loop_s* %124, i32 0, i32 9, !dbg !1317
  %125 = load %struct.uv__io_s**, %struct.uv__io_s*** %watchers186, align 8, !dbg !1317
  %arrayidx187 = getelementptr inbounds %struct.uv__io_s*, %struct.uv__io_s** %125, i64 %idxprom185, !dbg !1316
  store %struct.uv__io_s* %121, %struct.uv__io_s** %arrayidx187, align 8, !dbg !1318
  store i32 0, i32* %i, align 4, !dbg !1319
  br label %for.cond188, !dbg !1321

for.cond188:                                      ; preds = %for.inc, %cond.end178
  %126 = load i32, i32* %i, align 4, !dbg !1322
  %127 = load i32, i32* %nfds, align 4, !dbg !1325
  %cmp189 = icmp slt i32 %126, %127, !dbg !1326
  br i1 %cmp189, label %for.body, label %for.end, !dbg !1327

for.body:                                         ; preds = %for.cond188
  %arraydecay191 = getelementptr inbounds [1024 x %struct.uv__epoll_event], [1024 x %struct.uv__epoll_event]* %events, i32 0, i32 0, !dbg !1328
  %128 = load i32, i32* %i, align 4, !dbg !1330
  %idx.ext = sext i32 %128 to i64, !dbg !1331
  %add.ptr192 = getelementptr inbounds %struct.uv__epoll_event, %struct.uv__epoll_event* %arraydecay191, i64 %idx.ext, !dbg !1331
  store %struct.uv__epoll_event* %add.ptr192, %struct.uv__epoll_event** %pe, align 8, !dbg !1332
  %129 = load %struct.uv__epoll_event*, %struct.uv__epoll_event** %pe, align 8, !dbg !1333
  %data193 = getelementptr inbounds %struct.uv__epoll_event, %struct.uv__epoll_event* %129, i32 0, i32 1, !dbg !1334
  %130 = load i64, i64* %data193, align 1, !dbg !1334
  %conv194 = trunc i64 %130 to i32, !dbg !1333
  store i32 %conv194, i32* %fd, align 4, !dbg !1335
  %131 = load i32, i32* %fd, align 4, !dbg !1336
  %cmp195 = icmp eq i32 %131, -1, !dbg !1338
  br i1 %cmp195, label %if.then197, label %if.end198, !dbg !1339

if.then197:                                       ; preds = %for.body
  br label %for.inc, !dbg !1340

if.end198:                                        ; preds = %for.body
  %132 = load i32, i32* %fd, align 4, !dbg !1341
  %cmp199 = icmp sge i32 %132, 0, !dbg !1341
  br i1 %cmp199, label %cond.true201, label %cond.false202, !dbg !1341

cond.true201:                                     ; preds = %if.end198
  br label %cond.end203, !dbg !1342

cond.false202:                                    ; preds = %if.end198
  call void @__assert_fail(i8* getelementptr inbounds ([8 x i8], [8 x i8]* @.str.10, i32 0, i32 0), i8* getelementptr inbounds ([74 x i8], [74 x i8]* @.str.1, i32 0, i32 0), i32 353, i8* getelementptr inbounds ([35 x i8], [35 x i8]* @__PRETTY_FUNCTION__.uv__io_poll, i32 0, i32 0)) #8, !dbg !1344
  unreachable, !dbg !1344
                                                  ; No predecessors!
  br label %cond.end203, !dbg !1346

cond.end203:                                      ; preds = %133, %cond.true201
  %134 = load i32, i32* %fd, align 4, !dbg !1348
  %135 = load %struct.uv_loop_s*, %struct.uv_loop_s** %loop.addr, align 8, !dbg !1348
  %nwatchers204 = getelementptr inbounds %struct.uv_loop_s, %struct.uv_loop_s* %135, i32 0, i32 10, !dbg !1348
  %136 = load i32, i32* %nwatchers204, align 8, !dbg !1348
  %cmp205 = icmp ult i32 %134, %136, !dbg !1348
  br i1 %cmp205, label %cond.true207, label %cond.false208, !dbg !1348

cond.true207:                                     ; preds = %cond.end203
  br label %cond.end209, !dbg !1349

cond.false208:                                    ; preds = %cond.end203
  call void @__assert_fail(i8* getelementptr inbounds ([32 x i8], [32 x i8]* @.str.11, i32 0, i32 0), i8* getelementptr inbounds ([74 x i8], [74 x i8]* @.str.1, i32 0, i32 0), i32 354, i8* getelementptr inbounds ([35 x i8], [35 x i8]* @__PRETTY_FUNCTION__.uv__io_poll, i32 0, i32 0)) #8, !dbg !1350
  unreachable, !dbg !1350
                                                  ; No predecessors!
  br label %cond.end209, !dbg !1351

cond.end209:                                      ; preds = %137, %cond.true207
  %138 = load i32, i32* %fd, align 4, !dbg !1352
  %idxprom210 = sext i32 %138 to i64, !dbg !1353
  %139 = load %struct.uv_loop_s*, %struct.uv_loop_s** %loop.addr, align 8, !dbg !1353
  %watchers211 = getelementptr inbounds %struct.uv_loop_s, %struct.uv_loop_s* %139, i32 0, i32 9, !dbg !1354
  %140 = load %struct.uv__io_s**, %struct.uv__io_s*** %watchers211, align 8, !dbg !1354
  %arrayidx212 = getelementptr inbounds %struct.uv__io_s*, %struct.uv__io_s** %140, i64 %idxprom210, !dbg !1353
  %141 = load %struct.uv__io_s*, %struct.uv__io_s** %arrayidx212, align 8, !dbg !1353
  store %struct.uv__io_s* %141, %struct.uv__io_s** %w, align 8, !dbg !1355
  %142 = load %struct.uv__io_s*, %struct.uv__io_s** %w, align 8, !dbg !1356
  %cmp213 = icmp eq %struct.uv__io_s* %142, null, !dbg !1358
  br i1 %cmp213, label %if.then215, label %if.end218, !dbg !1359

if.then215:                                       ; preds = %cond.end209
  %143 = load %struct.uv_loop_s*, %struct.uv_loop_s** %loop.addr, align 8, !dbg !1360
  %backend_fd216 = getelementptr inbounds %struct.uv_loop_s, %struct.uv_loop_s* %143, i32 0, i32 6, !dbg !1362
  %144 = load i32, i32* %backend_fd216, align 8, !dbg !1362
  %145 = load i32, i32* %fd, align 4, !dbg !1363
  %146 = load %struct.uv__epoll_event*, %struct.uv__epoll_event** %pe, align 8, !dbg !1364
  %call217 = call i32 @uv__epoll_ctl(i32 %144, i32 2, i32 %145, %struct.uv__epoll_event* %146), !dbg !1365
  br label %for.inc, !dbg !1366

if.end218:                                        ; preds = %cond.end209
  %147 = load %struct.uv__io_s*, %struct.uv__io_s** %w, align 8, !dbg !1367
  %pevents219 = getelementptr inbounds %struct.uv__io_s, %struct.uv__io_s* %147, i32 0, i32 3, !dbg !1368
  %148 = load i32, i32* %pevents219, align 8, !dbg !1368
  %or220 = or i32 %148, 8, !dbg !1369
  %or221 = or i32 %or220, 16, !dbg !1370
  %149 = load %struct.uv__epoll_event*, %struct.uv__epoll_event** %pe, align 8, !dbg !1371
  %events222 = getelementptr inbounds %struct.uv__epoll_event, %struct.uv__epoll_event* %149, i32 0, i32 0, !dbg !1372
  %150 = load i32, i32* %events222, align 1, !dbg !1373
  %and223 = and i32 %150, %or221, !dbg !1373
  store i32 %and223, i32* %events222, align 1, !dbg !1373
  %151 = load %struct.uv__epoll_event*, %struct.uv__epoll_event** %pe, align 8, !dbg !1374
  %events224 = getelementptr inbounds %struct.uv__epoll_event, %struct.uv__epoll_event* %151, i32 0, i32 0, !dbg !1376
  %152 = load i32, i32* %events224, align 1, !dbg !1376
  %cmp225 = icmp eq i32 %152, 8, !dbg !1377
  br i1 %cmp225, label %if.then231, label %lor.lhs.false227, !dbg !1378

lor.lhs.false227:                                 ; preds = %if.end218
  %153 = load %struct.uv__epoll_event*, %struct.uv__epoll_event** %pe, align 8, !dbg !1379
  %events228 = getelementptr inbounds %struct.uv__epoll_event, %struct.uv__epoll_event* %153, i32 0, i32 0, !dbg !1381
  %154 = load i32, i32* %events228, align 1, !dbg !1381
  %cmp229 = icmp eq i32 %154, 16, !dbg !1382
  br i1 %cmp229, label %if.then231, label %if.end236, !dbg !1383

if.then231:                                       ; preds = %lor.lhs.false227, %if.end218
  %155 = load %struct.uv__io_s*, %struct.uv__io_s** %w, align 8, !dbg !1384
  %pevents232 = getelementptr inbounds %struct.uv__io_s, %struct.uv__io_s* %155, i32 0, i32 3, !dbg !1385
  %156 = load i32, i32* %pevents232, align 8, !dbg !1385
  %and233 = and i32 %156, 5, !dbg !1386
  %157 = load %struct.uv__epoll_event*, %struct.uv__epoll_event** %pe, align 8, !dbg !1387
  %events234 = getelementptr inbounds %struct.uv__epoll_event, %struct.uv__epoll_event* %157, i32 0, i32 0, !dbg !1388
  %158 = load i32, i32* %events234, align 1, !dbg !1389
  %or235 = or i32 %158, %and233, !dbg !1389
  store i32 %or235, i32* %events234, align 1, !dbg !1389
  br label %if.end236, !dbg !1387

if.end236:                                        ; preds = %if.then231, %lor.lhs.false227
  %159 = load %struct.uv__epoll_event*, %struct.uv__epoll_event** %pe, align 8, !dbg !1390
  %events237 = getelementptr inbounds %struct.uv__epoll_event, %struct.uv__epoll_event* %159, i32 0, i32 0, !dbg !1392
  %160 = load i32, i32* %events237, align 1, !dbg !1392
  %cmp238 = icmp ne i32 %160, 0, !dbg !1393
  br i1 %cmp238, label %if.then240, label %if.end247, !dbg !1394

if.then240:                                       ; preds = %if.end236
  %161 = load %struct.uv__io_s*, %struct.uv__io_s** %w, align 8, !dbg !1395
  %162 = load %struct.uv_loop_s*, %struct.uv_loop_s** %loop.addr, align 8, !dbg !1398
  %signal_io_watcher = getelementptr inbounds %struct.uv_loop_s, %struct.uv_loop_s* %162, i32 0, i32 29, !dbg !1399
  %cmp241 = icmp eq %struct.uv__io_s* %161, %signal_io_watcher, !dbg !1400
  br i1 %cmp241, label %if.then243, label %if.else244, !dbg !1401

if.then243:                                       ; preds = %if.then240
  store i32 1, i32* %have_signals, align 4, !dbg !1402
  br label %if.end246, !dbg !1403

if.else244:                                       ; preds = %if.then240
  %163 = load %struct.uv__io_s*, %struct.uv__io_s** %w, align 8, !dbg !1404
  %cb = getelementptr inbounds %struct.uv__io_s, %struct.uv__io_s* %163, i32 0, i32 0, !dbg !1405
  %164 = load void (%struct.uv_loop_s*, %struct.uv__io_s*, i32)*, void (%struct.uv_loop_s*, %struct.uv__io_s*, i32)** %cb, align 8, !dbg !1405
  %165 = load %struct.uv_loop_s*, %struct.uv_loop_s** %loop.addr, align 8, !dbg !1406
  %166 = load %struct.uv__io_s*, %struct.uv__io_s** %w, align 8, !dbg !1407
  %167 = load %struct.uv__epoll_event*, %struct.uv__epoll_event** %pe, align 8, !dbg !1408
  %events245 = getelementptr inbounds %struct.uv__epoll_event, %struct.uv__epoll_event* %167, i32 0, i32 0, !dbg !1409
  %168 = load i32, i32* %events245, align 1, !dbg !1409
  call void %164(%struct.uv_loop_s* %165, %struct.uv__io_s* %166, i32 %168), !dbg !1404
  br label %if.end246

if.end246:                                        ; preds = %if.else244, %if.then243
  %169 = load i32, i32* %nevents, align 4, !dbg !1410
  %inc = add nsw i32 %169, 1, !dbg !1410
  store i32 %inc, i32* %nevents, align 4, !dbg !1410
  br label %if.end247, !dbg !1411

if.end247:                                        ; preds = %if.end246, %if.end236
  br label %for.inc, !dbg !1412

for.inc:                                          ; preds = %if.end247, %if.then215, %if.then197
  %170 = load i32, i32* %i, align 4, !dbg !1413
  %inc248 = add nsw i32 %170, 1, !dbg !1413
  store i32 %inc248, i32* %i, align 4, !dbg !1413
  br label %for.cond188, !dbg !1415

for.end:                                          ; preds = %for.cond188
  %171 = load i32, i32* %have_signals, align 4, !dbg !1416
  %cmp249 = icmp ne i32 %171, 0, !dbg !1418
  br i1 %cmp249, label %if.then251, label %if.end255, !dbg !1419

if.then251:                                       ; preds = %for.end
  %172 = load %struct.uv_loop_s*, %struct.uv_loop_s** %loop.addr, align 8, !dbg !1420
  %signal_io_watcher252 = getelementptr inbounds %struct.uv_loop_s, %struct.uv_loop_s* %172, i32 0, i32 29, !dbg !1421
  %cb253 = getelementptr inbounds %struct.uv__io_s, %struct.uv__io_s* %signal_io_watcher252, i32 0, i32 0, !dbg !1422
  %173 = load void (%struct.uv_loop_s*, %struct.uv__io_s*, i32)*, void (%struct.uv_loop_s*, %struct.uv__io_s*, i32)** %cb253, align 8, !dbg !1422
  %174 = load %struct.uv_loop_s*, %struct.uv_loop_s** %loop.addr, align 8, !dbg !1423
  %175 = load %struct.uv_loop_s*, %struct.uv_loop_s** %loop.addr, align 8, !dbg !1424
  %signal_io_watcher254 = getelementptr inbounds %struct.uv_loop_s, %struct.uv_loop_s* %175, i32 0, i32 29, !dbg !1425
  call void %173(%struct.uv_loop_s* %174, %struct.uv__io_s* %signal_io_watcher254, i32 1), !dbg !1420
  br label %if.end255, !dbg !1420

if.end255:                                        ; preds = %if.then251, %for.end
  %176 = load %struct.uv_loop_s*, %struct.uv_loop_s** %loop.addr, align 8, !dbg !1426
  %nwatchers256 = getelementptr inbounds %struct.uv_loop_s, %struct.uv_loop_s* %176, i32 0, i32 10, !dbg !1427
  %177 = load i32, i32* %nwatchers256, align 8, !dbg !1427
  %idxprom257 = zext i32 %177 to i64, !dbg !1428
  %178 = load %struct.uv_loop_s*, %struct.uv_loop_s** %loop.addr, align 8, !dbg !1428
  %watchers258 = getelementptr inbounds %struct.uv_loop_s, %struct.uv_loop_s* %178, i32 0, i32 9, !dbg !1429
  %179 = load %struct.uv__io_s**, %struct.uv__io_s*** %watchers258, align 8, !dbg !1429
  %arrayidx259 = getelementptr inbounds %struct.uv__io_s*, %struct.uv__io_s** %179, i64 %idxprom257, !dbg !1428
  store %struct.uv__io_s* null, %struct.uv__io_s** %arrayidx259, align 8, !dbg !1430
  %180 = load %struct.uv_loop_s*, %struct.uv_loop_s** %loop.addr, align 8, !dbg !1431
  %nwatchers260 = getelementptr inbounds %struct.uv_loop_s, %struct.uv_loop_s* %180, i32 0, i32 10, !dbg !1432
  %181 = load i32, i32* %nwatchers260, align 8, !dbg !1432
  %add261 = add i32 %181, 1, !dbg !1433
  %idxprom262 = zext i32 %add261 to i64, !dbg !1434
  %182 = load %struct.uv_loop_s*, %struct.uv_loop_s** %loop.addr, align 8, !dbg !1434
  %watchers263 = getelementptr inbounds %struct.uv_loop_s, %struct.uv_loop_s* %182, i32 0, i32 9, !dbg !1435
  %183 = load %struct.uv__io_s**, %struct.uv__io_s*** %watchers263, align 8, !dbg !1435
  %arrayidx264 = getelementptr inbounds %struct.uv__io_s*, %struct.uv__io_s** %183, i64 %idxprom262, !dbg !1434
  store %struct.uv__io_s* null, %struct.uv__io_s** %arrayidx264, align 8, !dbg !1436
  %184 = load i32, i32* %have_signals, align 4, !dbg !1437
  %cmp265 = icmp ne i32 %184, 0, !dbg !1439
  br i1 %cmp265, label %if.then267, label %if.end268, !dbg !1440

if.then267:                                       ; preds = %if.end255
  br label %return, !dbg !1441

if.end268:                                        ; preds = %if.end255
  %185 = load i32, i32* %nevents, align 4, !dbg !1442
  %cmp269 = icmp ne i32 %185, 0, !dbg !1444
  br i1 %cmp269, label %if.then271, label %if.end280, !dbg !1445

if.then271:                                       ; preds = %if.end268
  %186 = load i32, i32* %nfds, align 4, !dbg !1446
  %conv272 = sext i32 %186 to i64, !dbg !1446
  %cmp273 = icmp eq i64 %conv272, 1024, !dbg !1449
  br i1 %cmp273, label %land.lhs.true275, label %if.end279, !dbg !1450

land.lhs.true275:                                 ; preds = %if.then271
  %187 = load i32, i32* %count, align 4, !dbg !1451
  %dec = add nsw i32 %187, -1, !dbg !1451
  store i32 %dec, i32* %count, align 4, !dbg !1451
  %cmp276 = icmp ne i32 %dec, 0, !dbg !1453
  br i1 %cmp276, label %if.then278, label %if.end279, !dbg !1454

if.then278:                                       ; preds = %land.lhs.true275
  store i32 0, i32* %timeout.addr, align 4, !dbg !1455
  br label %for.cond, !dbg !1457

if.end279:                                        ; preds = %land.lhs.true275, %if.then271
  br label %return, !dbg !1458

if.end280:                                        ; preds = %if.end268
  %188 = load i32, i32* %timeout.addr, align 4, !dbg !1459
  %cmp281 = icmp eq i32 %188, 0, !dbg !1461
  br i1 %cmp281, label %if.then283, label %if.end284, !dbg !1462

if.then283:                                       ; preds = %if.end280
  br label %return, !dbg !1463

if.end284:                                        ; preds = %if.end280
  %189 = load i32, i32* %timeout.addr, align 4, !dbg !1464
  %cmp285 = icmp eq i32 %189, -1, !dbg !1466
  br i1 %cmp285, label %if.then287, label %if.end288, !dbg !1467

if.then287:                                       ; preds = %if.end284
  br label %for.cond, !dbg !1468

if.end288:                                        ; preds = %if.end284
  br label %update_timeout, !dbg !1469

update_timeout:                                   ; preds = %if.end288, %if.end172, %if.end142
  %190 = load i32, i32* %timeout.addr, align 4, !dbg !1471
  %cmp289 = icmp sgt i32 %190, 0, !dbg !1471
  br i1 %cmp289, label %cond.true291, label %cond.false292, !dbg !1471

cond.true291:                                     ; preds = %update_timeout
  br label %cond.end293, !dbg !1472

cond.false292:                                    ; preds = %update_timeout
  call void @__assert_fail(i8* getelementptr inbounds ([12 x i8], [12 x i8]* @.str.12, i32 0, i32 0), i8* getelementptr inbounds ([74 x i8], [74 x i8]* @.str.1, i32 0, i32 0), i32 431, i8* getelementptr inbounds ([35 x i8], [35 x i8]* @__PRETTY_FUNCTION__.uv__io_poll, i32 0, i32 0)) #8, !dbg !1473
  unreachable, !dbg !1473
                                                  ; No predecessors!
  br label %cond.end293, !dbg !1474

cond.end293:                                      ; preds = %191, %cond.true291
  %192 = load %struct.uv_loop_s*, %struct.uv_loop_s** %loop.addr, align 8, !dbg !1475
  %time294 = getelementptr inbounds %struct.uv_loop_s, %struct.uv_loop_s* %192, i32 0, i32 27, !dbg !1476
  %193 = load i64, i64* %time294, align 8, !dbg !1476
  %194 = load i64, i64* %base, align 8, !dbg !1477
  %sub = sub i64 %193, %194, !dbg !1478
  %195 = load i32, i32* %real_timeout, align 4, !dbg !1479
  %conv295 = sext i32 %195 to i64, !dbg !1479
  %sub296 = sub i64 %conv295, %sub, !dbg !1479
  %conv297 = trunc i64 %sub296 to i32, !dbg !1479
  store i32 %conv297, i32* %real_timeout, align 4, !dbg !1479
  %196 = load i32, i32* %real_timeout, align 4, !dbg !1480
  %cmp298 = icmp sle i32 %196, 0, !dbg !1482
  br i1 %cmp298, label %if.then300, label %if.end301, !dbg !1483

if.then300:                                       ; preds = %cond.end293
  br label %return, !dbg !1484

if.end301:                                        ; preds = %cond.end293
  %197 = load i32, i32* %real_timeout, align 4, !dbg !1485
  store i32 %197, i32* %timeout.addr, align 4, !dbg !1486
  br label %for.cond, !dbg !1487

return:                                           ; preds = %if.then300, %if.then283, %if.end279, %if.then267, %if.then171, %if.then141, %cond.end
  ret void, !dbg !1489
}

; Function Attrs: nounwind
declare i32 @sigemptyset(%struct.__sigset_t*) #6

; Function Attrs: nounwind
declare i32 @sigaddset(%struct.__sigset_t*, i32) #6

; Function Attrs: nounwind
declare i32 @pthread_sigmask(i32, %struct.__sigset_t*, %struct.__sigset_t*) #6

declare i32 @uv__epoll_pwait(i32, %struct.uv__epoll_event*, i32, i32, i64) #2

declare i32 @uv__epoll_wait(i32, %struct.uv__epoll_event*, i32, i32) #2

; Function Attrs: nounwind uwtable
define internal void @uv__update_time(%struct.uv_loop_s* %loop) #0 !dbg !641 {
entry:
  %loop.addr = alloca %struct.uv_loop_s*, align 8
  store %struct.uv_loop_s* %loop, %struct.uv_loop_s** %loop.addr, align 8
  call void @llvm.dbg.declare(metadata %struct.uv_loop_s** %loop.addr, metadata !1490, metadata !760), !dbg !1491
  %call = call i64 @uv__hrtime(i32 1), !dbg !1492
  %div = udiv i64 %call, 1000000, !dbg !1493
  %0 = load %struct.uv_loop_s*, %struct.uv_loop_s** %loop.addr, align 8, !dbg !1494
  %time = getelementptr inbounds %struct.uv_loop_s, %struct.uv_loop_s* %0, i32 0, i32 27, !dbg !1495
  store i64 %div, i64* %time, align 8, !dbg !1496
  ret void, !dbg !1497
}

; Function Attrs: nounwind uwtable
define i64 @uv__hrtime(i32 %type) #0 !dbg !563 {
entry:
  %retval = alloca i64, align 8
  %type.addr = alloca i32, align 4
  %t = alloca %struct.timespec, align 8
  %clock_id = alloca i64, align 8
  store i32 %type, i32* %type.addr, align 4
  call void @llvm.dbg.declare(metadata i32* %type.addr, metadata !1498, metadata !760), !dbg !1499
  call void @llvm.dbg.declare(metadata %struct.timespec* %t, metadata !1500, metadata !760), !dbg !1507
  call void @llvm.dbg.declare(metadata i64* %clock_id, metadata !1508, metadata !760), !dbg !1509
  %0 = load i32, i32* %type.addr, align 4, !dbg !1510
  %cmp = icmp eq i32 %0, 1, !dbg !1512
  br i1 %cmp, label %land.lhs.true, label %if.end6, !dbg !1513

land.lhs.true:                                    ; preds = %entry
  %1 = load i64, i64* @uv__hrtime.fast_clock_id, align 8, !dbg !1514
  %cmp1 = icmp eq i64 %1, -1, !dbg !1516
  br i1 %cmp1, label %if.then, label %if.end6, !dbg !1517

if.then:                                          ; preds = %land.lhs.true
  %call = call i32 @clock_getres(i32 6, %struct.timespec* %t) #9, !dbg !1518
  %cmp2 = icmp eq i32 %call, 0, !dbg !1521
  br i1 %cmp2, label %land.lhs.true3, label %if.else, !dbg !1522

land.lhs.true3:                                   ; preds = %if.then
  %tv_nsec = getelementptr inbounds %struct.timespec, %struct.timespec* %t, i32 0, i32 1, !dbg !1523
  %2 = load i64, i64* %tv_nsec, align 8, !dbg !1523
  %cmp4 = icmp sle i64 %2, 1000000, !dbg !1524
  br i1 %cmp4, label %if.then5, label %if.else, !dbg !1525

if.then5:                                         ; preds = %land.lhs.true3
  store i64 6, i64* @uv__hrtime.fast_clock_id, align 8, !dbg !1527
  br label %if.end, !dbg !1529

if.else:                                          ; preds = %land.lhs.true3, %if.then
  store i64 1, i64* @uv__hrtime.fast_clock_id, align 8, !dbg !1530
  br label %if.end

if.end:                                           ; preds = %if.else, %if.then5
  br label %if.end6, !dbg !1532

if.end6:                                          ; preds = %if.end, %land.lhs.true, %entry
  store i64 1, i64* %clock_id, align 8, !dbg !1533
  %3 = load i32, i32* %type.addr, align 4, !dbg !1534
  %cmp7 = icmp eq i32 %3, 1, !dbg !1536
  br i1 %cmp7, label %if.then8, label %if.end9, !dbg !1537

if.then8:                                         ; preds = %if.end6
  %4 = load i64, i64* @uv__hrtime.fast_clock_id, align 8, !dbg !1538
  store i64 %4, i64* %clock_id, align 8, !dbg !1539
  br label %if.end9, !dbg !1540

if.end9:                                          ; preds = %if.then8, %if.end6
  %5 = load i64, i64* %clock_id, align 8, !dbg !1541
  %conv = trunc i64 %5 to i32, !dbg !1541
  %call10 = call i32 @clock_gettime(i32 %conv, %struct.timespec* %t) #9, !dbg !1543
  %tobool = icmp ne i32 %call10, 0, !dbg !1543
  br i1 %tobool, label %if.then11, label %if.end12, !dbg !1544

if.then11:                                        ; preds = %if.end9
  store i64 0, i64* %retval, align 8, !dbg !1545
  br label %return, !dbg !1545

if.end12:                                         ; preds = %if.end9
  %tv_sec = getelementptr inbounds %struct.timespec, %struct.timespec* %t, i32 0, i32 0, !dbg !1546
  %6 = load i64, i64* %tv_sec, align 8, !dbg !1546
  %mul = mul i64 %6, 1000000000, !dbg !1547
  %tv_nsec13 = getelementptr inbounds %struct.timespec, %struct.timespec* %t, i32 0, i32 1, !dbg !1548
  %7 = load i64, i64* %tv_nsec13, align 8, !dbg !1548
  %add = add i64 %mul, %7, !dbg !1549
  store i64 %add, i64* %retval, align 8, !dbg !1550
  br label %return, !dbg !1550

return:                                           ; preds = %if.end12, %if.then11
  %8 = load i64, i64* %retval, align 8, !dbg !1551
  ret i64 %8, !dbg !1551
}

; Function Attrs: nounwind
declare i32 @clock_getres(i32, %struct.timespec*) #6

; Function Attrs: nounwind
declare i32 @clock_gettime(i32, %struct.timespec*) #6

; Function Attrs: nounwind uwtable
define void @uv_loadavg(double* %avg) #0 !dbg !567 {
entry:
  %avg.addr = alloca double*, align 8
  %info = alloca %struct.sysinfo, align 8
  store double* %avg, double** %avg.addr, align 8
  call void @llvm.dbg.declare(metadata double** %avg.addr, metadata !1552, metadata !760), !dbg !1553
  call void @llvm.dbg.declare(metadata %struct.sysinfo* %info, metadata !1554, metadata !760), !dbg !1584
  %call = call i32 @sysinfo(%struct.sysinfo* %info) #9, !dbg !1585
  %cmp = icmp slt i32 %call, 0, !dbg !1587
  br i1 %cmp, label %if.then, label %if.end, !dbg !1588

if.then:                                          ; preds = %entry
  br label %return, !dbg !1589

if.end:                                           ; preds = %entry
  %loads = getelementptr inbounds %struct.sysinfo, %struct.sysinfo* %info, i32 0, i32 1, !dbg !1591
  %arrayidx = getelementptr inbounds [3 x i64], [3 x i64]* %loads, i64 0, i64 0, !dbg !1592
  %0 = load i64, i64* %arrayidx, align 8, !dbg !1592
  %conv = uitofp i64 %0 to double, !dbg !1593
  %div = fdiv double %conv, 6.553600e+04, !dbg !1594
  %1 = load double*, double** %avg.addr, align 8, !dbg !1595
  %arrayidx1 = getelementptr inbounds double, double* %1, i64 0, !dbg !1595
  store double %div, double* %arrayidx1, align 8, !dbg !1596
  %loads2 = getelementptr inbounds %struct.sysinfo, %struct.sysinfo* %info, i32 0, i32 1, !dbg !1597
  %arrayidx3 = getelementptr inbounds [3 x i64], [3 x i64]* %loads2, i64 0, i64 1, !dbg !1598
  %2 = load i64, i64* %arrayidx3, align 8, !dbg !1598
  %conv4 = uitofp i64 %2 to double, !dbg !1599
  %div5 = fdiv double %conv4, 6.553600e+04, !dbg !1600
  %3 = load double*, double** %avg.addr, align 8, !dbg !1601
  %arrayidx6 = getelementptr inbounds double, double* %3, i64 1, !dbg !1601
  store double %div5, double* %arrayidx6, align 8, !dbg !1602
  %loads7 = getelementptr inbounds %struct.sysinfo, %struct.sysinfo* %info, i32 0, i32 1, !dbg !1603
  %arrayidx8 = getelementptr inbounds [3 x i64], [3 x i64]* %loads7, i64 0, i64 2, !dbg !1604
  %4 = load i64, i64* %arrayidx8, align 8, !dbg !1604
  %conv9 = uitofp i64 %4 to double, !dbg !1605
  %div10 = fdiv double %conv9, 6.553600e+04, !dbg !1606
  %5 = load double*, double** %avg.addr, align 8, !dbg !1607
  %arrayidx11 = getelementptr inbounds double, double* %5, i64 2, !dbg !1607
  store double %div10, double* %arrayidx11, align 8, !dbg !1608
  br label %return, !dbg !1609

return:                                           ; preds = %if.end, %if.then
  ret void, !dbg !1610
}

; Function Attrs: nounwind
declare i32 @sysinfo(%struct.sysinfo*) #6

; Function Attrs: nounwind uwtable
define i32 @uv_exepath(i8* %buffer, i64* %size) #0 !dbg !571 {
entry:
  %retval = alloca i32, align 4
  %buffer.addr = alloca i8*, align 8
  %size.addr = alloca i64*, align 8
  %n = alloca i64, align 8
  store i8* %buffer, i8** %buffer.addr, align 8
  call void @llvm.dbg.declare(metadata i8** %buffer.addr, metadata !1612, metadata !760), !dbg !1613
  store i64* %size, i64** %size.addr, align 8
  call void @llvm.dbg.declare(metadata i64** %size.addr, metadata !1614, metadata !760), !dbg !1615
  call void @llvm.dbg.declare(metadata i64* %n, metadata !1616, metadata !760), !dbg !1619
  %0 = load i8*, i8** %buffer.addr, align 8, !dbg !1620
  %cmp = icmp eq i8* %0, null, !dbg !1622
  br i1 %cmp, label %if.then, label %lor.lhs.false, !dbg !1623

lor.lhs.false:                                    ; preds = %entry
  %1 = load i64*, i64** %size.addr, align 8, !dbg !1624
  %cmp1 = icmp eq i64* %1, null, !dbg !1626
  br i1 %cmp1, label %if.then, label %lor.lhs.false2, !dbg !1627

lor.lhs.false2:                                   ; preds = %lor.lhs.false
  %2 = load i64*, i64** %size.addr, align 8, !dbg !1628
  %3 = load i64, i64* %2, align 8, !dbg !1630
  %cmp3 = icmp eq i64 %3, 0, !dbg !1631
  br i1 %cmp3, label %if.then, label %if.end, !dbg !1632

if.then:                                          ; preds = %lor.lhs.false2, %lor.lhs.false, %entry
  store i32 -22, i32* %retval, align 4, !dbg !1633
  br label %return, !dbg !1633

if.end:                                           ; preds = %lor.lhs.false2
  %4 = load i64*, i64** %size.addr, align 8, !dbg !1634
  %5 = load i64, i64* %4, align 8, !dbg !1635
  %sub = sub i64 %5, 1, !dbg !1636
  store i64 %sub, i64* %n, align 8, !dbg !1637
  %6 = load i64, i64* %n, align 8, !dbg !1638
  %cmp4 = icmp sgt i64 %6, 0, !dbg !1640
  br i1 %cmp4, label %if.then5, label %if.end6, !dbg !1641

if.then5:                                         ; preds = %if.end
  %7 = load i8*, i8** %buffer.addr, align 8, !dbg !1642
  %8 = load i64, i64* %n, align 8, !dbg !1643
  %call = call i64 @readlink(i8* getelementptr inbounds ([15 x i8], [15 x i8]* @.str.13, i32 0, i32 0), i8* %7, i64 %8) #9, !dbg !1644
  store i64 %call, i64* %n, align 8, !dbg !1645
  br label %if.end6, !dbg !1646

if.end6:                                          ; preds = %if.then5, %if.end
  %9 = load i64, i64* %n, align 8, !dbg !1647
  %cmp7 = icmp eq i64 %9, -1, !dbg !1649
  br i1 %cmp7, label %if.then8, label %if.end11, !dbg !1650

if.then8:                                         ; preds = %if.end6
  %call9 = call i32* @__errno_location() #1, !dbg !1651
  %10 = load i32, i32* %call9, align 4, !dbg !1651
  %sub10 = sub nsw i32 0, %10, !dbg !1652
  store i32 %sub10, i32* %retval, align 4, !dbg !1653
  br label %return, !dbg !1653

if.end11:                                         ; preds = %if.end6
  %11 = load i64, i64* %n, align 8, !dbg !1654
  %12 = load i8*, i8** %buffer.addr, align 8, !dbg !1655
  %arrayidx = getelementptr inbounds i8, i8* %12, i64 %11, !dbg !1655
  store i8 0, i8* %arrayidx, align 1, !dbg !1656
  %13 = load i64, i64* %n, align 8, !dbg !1657
  %14 = load i64*, i64** %size.addr, align 8, !dbg !1658
  store i64 %13, i64* %14, align 8, !dbg !1659
  store i32 0, i32* %retval, align 4, !dbg !1660
  br label %return, !dbg !1660

return:                                           ; preds = %if.end11, %if.then8, %if.then
  %15 = load i32, i32* %retval, align 4, !dbg !1661
  ret i32 %15, !dbg !1661
}

; Function Attrs: nounwind
declare i64 @readlink(i8*, i8*, i64) #6

; Function Attrs: nounwind uwtable
define i64 @uv_get_free_memory() #0 !dbg !577 {
entry:
  %retval = alloca i64, align 8
  %info = alloca %struct.sysinfo, align 8
  call void @llvm.dbg.declare(metadata %struct.sysinfo* %info, metadata !1662, metadata !760), !dbg !1663
  %call = call i32 @sysinfo(%struct.sysinfo* %info) #9, !dbg !1664
  %cmp = icmp eq i32 %call, 0, !dbg !1666
  br i1 %cmp, label %if.then, label %if.end, !dbg !1667

if.then:                                          ; preds = %entry
  %freeram = getelementptr inbounds %struct.sysinfo, %struct.sysinfo* %info, i32 0, i32 3, !dbg !1668
  %0 = load i64, i64* %freeram, align 8, !dbg !1668
  %mem_unit = getelementptr inbounds %struct.sysinfo, %struct.sysinfo* %info, i32 0, i32 12, !dbg !1669
  %1 = load i32, i32* %mem_unit, align 8, !dbg !1669
  %conv = zext i32 %1 to i64, !dbg !1670
  %mul = mul i64 %0, %conv, !dbg !1671
  store i64 %mul, i64* %retval, align 8, !dbg !1672
  br label %return, !dbg !1672

if.end:                                           ; preds = %entry
  store i64 0, i64* %retval, align 8, !dbg !1673
  br label %return, !dbg !1673

return:                                           ; preds = %if.end, %if.then
  %2 = load i64, i64* %retval, align 8, !dbg !1674
  ret i64 %2, !dbg !1674
}

; Function Attrs: nounwind uwtable
define i64 @uv_get_total_memory() #0 !dbg !580 {
entry:
  %retval = alloca i64, align 8
  %info = alloca %struct.sysinfo, align 8
  call void @llvm.dbg.declare(metadata %struct.sysinfo* %info, metadata !1675, metadata !760), !dbg !1676
  %call = call i32 @sysinfo(%struct.sysinfo* %info) #9, !dbg !1677
  %cmp = icmp eq i32 %call, 0, !dbg !1679
  br i1 %cmp, label %if.then, label %if.end, !dbg !1680

if.then:                                          ; preds = %entry
  %totalram = getelementptr inbounds %struct.sysinfo, %struct.sysinfo* %info, i32 0, i32 2, !dbg !1681
  %0 = load i64, i64* %totalram, align 8, !dbg !1681
  %mem_unit = getelementptr inbounds %struct.sysinfo, %struct.sysinfo* %info, i32 0, i32 12, !dbg !1682
  %1 = load i32, i32* %mem_unit, align 8, !dbg !1682
  %conv = zext i32 %1 to i64, !dbg !1683
  %mul = mul i64 %0, %conv, !dbg !1684
  store i64 %mul, i64* %retval, align 8, !dbg !1685
  br label %return, !dbg !1685

if.end:                                           ; preds = %entry
  store i64 0, i64* %retval, align 8, !dbg !1686
  br label %return, !dbg !1686

return:                                           ; preds = %if.end, %if.then
  %2 = load i64, i64* %retval, align 8, !dbg !1687
  ret i64 %2, !dbg !1687
}

; Function Attrs: nounwind uwtable
define i32 @uv_resident_set_memory(i64* %rss) #0 !dbg !581 {
entry:
  %retval = alloca i32, align 4
  %rss.addr = alloca i64*, align 8
  %buf = alloca [1024 x i8], align 16
  %s = alloca i8*, align 8
  %n = alloca i64, align 8
  %val = alloca i64, align 8
  %fd = alloca i32, align 4
  %i = alloca i32, align 4
  store i64* %rss, i64** %rss.addr, align 8
  call void @llvm.dbg.declare(metadata i64** %rss.addr, metadata !1688, metadata !760), !dbg !1689
  call void @llvm.dbg.declare(metadata [1024 x i8]* %buf, metadata !1690, metadata !760), !dbg !1692
  call void @llvm.dbg.declare(metadata i8** %s, metadata !1693, metadata !760), !dbg !1694
  call void @llvm.dbg.declare(metadata i64* %n, metadata !1695, metadata !760), !dbg !1696
  call void @llvm.dbg.declare(metadata i64* %val, metadata !1697, metadata !760), !dbg !1698
  call void @llvm.dbg.declare(metadata i32* %fd, metadata !1699, metadata !760), !dbg !1700
  call void @llvm.dbg.declare(metadata i32* %i, metadata !1701, metadata !760), !dbg !1702
  br label %do.body, !dbg !1703

do.body:                                          ; preds = %land.end, %entry
  %call = call i32 (i8*, i32, ...) @open64(i8* getelementptr inbounds ([16 x i8], [16 x i8]* @.str.14, i32 0, i32 0), i32 0), !dbg !1704
  store i32 %call, i32* %fd, align 4, !dbg !1705
  br label %do.cond, !dbg !1706

do.cond:                                          ; preds = %do.body
  %0 = load i32, i32* %fd, align 4, !dbg !1707
  %cmp = icmp eq i32 %0, -1, !dbg !1708
  br i1 %cmp, label %land.rhs, label %land.end, !dbg !1709

land.rhs:                                         ; preds = %do.cond
  %call1 = call i32* @__errno_location() #1, !dbg !1710
  %1 = load i32, i32* %call1, align 4, !dbg !1710
  %cmp2 = icmp eq i32 %1, 4, !dbg !1712
  br label %land.end

land.end:                                         ; preds = %land.rhs, %do.cond
  %2 = phi i1 [ false, %do.cond ], [ %cmp2, %land.rhs ]
  br i1 %2, label %do.body, label %do.end, !dbg !1713

do.end:                                           ; preds = %land.end
  %3 = load i32, i32* %fd, align 4, !dbg !1714
  %cmp3 = icmp eq i32 %3, -1, !dbg !1716
  br i1 %cmp3, label %if.then, label %if.end, !dbg !1717

if.then:                                          ; preds = %do.end
  %call4 = call i32* @__errno_location() #1, !dbg !1718
  %4 = load i32, i32* %call4, align 4, !dbg !1718
  %sub = sub nsw i32 0, %4, !dbg !1719
  store i32 %sub, i32* %retval, align 4, !dbg !1720
  br label %return, !dbg !1720

if.end:                                           ; preds = %do.end
  br label %do.body5, !dbg !1721

do.body5:                                         ; preds = %land.end12, %if.end
  %5 = load i32, i32* %fd, align 4, !dbg !1722
  %arraydecay = getelementptr inbounds [1024 x i8], [1024 x i8]* %buf, i32 0, i32 0, !dbg !1723
  %call6 = call i64 @read(i32 %5, i8* %arraydecay, i64 1023), !dbg !1724
  store i64 %call6, i64* %n, align 8, !dbg !1725
  br label %do.cond7, !dbg !1726

do.cond7:                                         ; preds = %do.body5
  %6 = load i64, i64* %n, align 8, !dbg !1727
  %cmp8 = icmp eq i64 %6, -1, !dbg !1728
  br i1 %cmp8, label %land.rhs9, label %land.end12, !dbg !1729

land.rhs9:                                        ; preds = %do.cond7
  %call10 = call i32* @__errno_location() #1, !dbg !1730
  %7 = load i32, i32* %call10, align 4, !dbg !1730
  %cmp11 = icmp eq i32 %7, 4, !dbg !1731
  br label %land.end12

land.end12:                                       ; preds = %land.rhs9, %do.cond7
  %8 = phi i1 [ false, %do.cond7 ], [ %cmp11, %land.rhs9 ]
  br i1 %8, label %do.body5, label %do.end13, !dbg !1732

do.end13:                                         ; preds = %land.end12
  %9 = load i32, i32* %fd, align 4, !dbg !1733
  %call14 = call i32 @uv__close(i32 %9), !dbg !1734
  %10 = load i64, i64* %n, align 8, !dbg !1735
  %cmp15 = icmp eq i64 %10, -1, !dbg !1737
  br i1 %cmp15, label %if.then16, label %if.end19, !dbg !1738

if.then16:                                        ; preds = %do.end13
  %call17 = call i32* @__errno_location() #1, !dbg !1739
  %11 = load i32, i32* %call17, align 4, !dbg !1739
  %sub18 = sub nsw i32 0, %11, !dbg !1740
  store i32 %sub18, i32* %retval, align 4, !dbg !1741
  br label %return, !dbg !1741

if.end19:                                         ; preds = %do.end13
  %12 = load i64, i64* %n, align 8, !dbg !1742
  %arrayidx = getelementptr inbounds [1024 x i8], [1024 x i8]* %buf, i64 0, i64 %12, !dbg !1743
  store i8 0, i8* %arrayidx, align 1, !dbg !1744
  %arraydecay20 = getelementptr inbounds [1024 x i8], [1024 x i8]* %buf, i32 0, i32 0, !dbg !1745
  %call21 = call i8* @strchr(i8* %arraydecay20, i32 32) #10, !dbg !1746
  store i8* %call21, i8** %s, align 8, !dbg !1747
  %13 = load i8*, i8** %s, align 8, !dbg !1748
  %cmp22 = icmp eq i8* %13, null, !dbg !1750
  br i1 %cmp22, label %if.then23, label %if.end24, !dbg !1751

if.then23:                                        ; preds = %if.end19
  br label %err, !dbg !1752

if.end24:                                         ; preds = %if.end19
  %14 = load i8*, i8** %s, align 8, !dbg !1753
  %add.ptr = getelementptr inbounds i8, i8* %14, i64 1, !dbg !1753
  store i8* %add.ptr, i8** %s, align 8, !dbg !1753
  %15 = load i8*, i8** %s, align 8, !dbg !1754
  %16 = load i8, i8* %15, align 1, !dbg !1756
  %conv = sext i8 %16 to i32, !dbg !1756
  %cmp25 = icmp ne i32 %conv, 40, !dbg !1757
  br i1 %cmp25, label %if.then27, label %if.end28, !dbg !1758

if.then27:                                        ; preds = %if.end24
  br label %err, !dbg !1759

if.end28:                                         ; preds = %if.end24
  %17 = load i8*, i8** %s, align 8, !dbg !1760
  %call29 = call i8* @strchr(i8* %17, i32 41) #10, !dbg !1761
  store i8* %call29, i8** %s, align 8, !dbg !1762
  %18 = load i8*, i8** %s, align 8, !dbg !1763
  %cmp30 = icmp eq i8* %18, null, !dbg !1765
  br i1 %cmp30, label %if.then32, label %if.end33, !dbg !1766

if.then32:                                        ; preds = %if.end28
  br label %err, !dbg !1767

if.end33:                                         ; preds = %if.end28
  store i32 1, i32* %i, align 4, !dbg !1768
  br label %for.cond, !dbg !1770

for.cond:                                         ; preds = %for.inc, %if.end33
  %19 = load i32, i32* %i, align 4, !dbg !1771
  %cmp34 = icmp sle i32 %19, 22, !dbg !1774
  br i1 %cmp34, label %for.body, label %for.end, !dbg !1775

for.body:                                         ; preds = %for.cond
  %20 = load i8*, i8** %s, align 8, !dbg !1776
  %add.ptr36 = getelementptr inbounds i8, i8* %20, i64 1, !dbg !1778
  %call37 = call i8* @strchr(i8* %add.ptr36, i32 32) #10, !dbg !1779
  store i8* %call37, i8** %s, align 8, !dbg !1780
  %21 = load i8*, i8** %s, align 8, !dbg !1781
  %cmp38 = icmp eq i8* %21, null, !dbg !1783
  br i1 %cmp38, label %if.then40, label %if.end41, !dbg !1784

if.then40:                                        ; preds = %for.body
  br label %err, !dbg !1785

if.end41:                                         ; preds = %for.body
  br label %for.inc, !dbg !1786

for.inc:                                          ; preds = %if.end41
  %22 = load i32, i32* %i, align 4, !dbg !1787
  %inc = add nsw i32 %22, 1, !dbg !1787
  store i32 %inc, i32* %i, align 4, !dbg !1787
  br label %for.cond, !dbg !1789

for.end:                                          ; preds = %for.cond
  %call42 = call i32* @__errno_location() #1, !dbg !1790
  store i32 0, i32* %call42, align 4, !dbg !1791
  %23 = load i8*, i8** %s, align 8, !dbg !1792
  %call43 = call i64 @strtol(i8* %23, i8** null, i32 10) #9, !dbg !1793
  store i64 %call43, i64* %val, align 8, !dbg !1794
  %call44 = call i32* @__errno_location() #1, !dbg !1795
  %24 = load i32, i32* %call44, align 4, !dbg !1795
  %cmp45 = icmp ne i32 %24, 0, !dbg !1797
  br i1 %cmp45, label %if.then47, label %if.end48, !dbg !1798

if.then47:                                        ; preds = %for.end
  br label %err, !dbg !1799

if.end48:                                         ; preds = %for.end
  %25 = load i64, i64* %val, align 8, !dbg !1800
  %cmp49 = icmp slt i64 %25, 0, !dbg !1802
  br i1 %cmp49, label %if.then51, label %if.end52, !dbg !1803

if.then51:                                        ; preds = %if.end48
  br label %err, !dbg !1804

if.end52:                                         ; preds = %if.end48
  %26 = load i64, i64* %val, align 8, !dbg !1805
  %call53 = call i32 @getpagesize() #1, !dbg !1806
  %conv54 = sext i32 %call53 to i64, !dbg !1806
  %mul = mul nsw i64 %26, %conv54, !dbg !1807
  %27 = load i64*, i64** %rss.addr, align 8, !dbg !1808
  store i64 %mul, i64* %27, align 8, !dbg !1809
  store i32 0, i32* %retval, align 4, !dbg !1810
  br label %return, !dbg !1810

err:                                              ; preds = %if.then51, %if.then47, %if.then40, %if.then32, %if.then27, %if.then23
  store i32 -22, i32* %retval, align 4, !dbg !1811
  br label %return, !dbg !1811

return:                                           ; preds = %err, %if.end52, %if.then16, %if.then
  %28 = load i32, i32* %retval, align 4, !dbg !1812
  ret i32 %28, !dbg !1812
}

declare i32 @open64(i8*, i32, ...) #2

declare i64 @read(i32, i8*, i64) #2

; Function Attrs: nounwind readonly
declare i8* @strchr(i8*, i32) #7

; Function Attrs: nounwind
declare i64 @strtol(i8*, i8**, i32) #6

; Function Attrs: nounwind readnone
declare i32 @getpagesize() #3

; Function Attrs: nounwind uwtable
define i32 @uv_uptime(double* %uptime) #0 !dbg !584 {
entry:
  %retval = alloca i32, align 4
  %uptime.addr = alloca double*, align 8
  %now = alloca %struct.timespec, align 8
  %r = alloca i32, align 4
  store double* %uptime, double** %uptime.addr, align 8
  call void @llvm.dbg.declare(metadata double** %uptime.addr, metadata !1813, metadata !760), !dbg !1814
  call void @llvm.dbg.declare(metadata %struct.timespec* %now, metadata !1815, metadata !760), !dbg !1816
  call void @llvm.dbg.declare(metadata i32* %r, metadata !1817, metadata !760), !dbg !1818
  %0 = load volatile i32, i32* @uv_uptime.no_clock_boottime, align 4, !dbg !1819
  %tobool = icmp ne i32 %0, 0, !dbg !1819
  br i1 %tobool, label %if.then, label %if.else, !dbg !1821

if.then:                                          ; preds = %entry
  br label %retry, !dbg !1822

retry:                                            ; preds = %if.then4, %if.then
  %call = call i32 @clock_gettime(i32 1, %struct.timespec* %now) #9, !dbg !1824
  store i32 %call, i32* %r, align 4, !dbg !1826
  br label %if.end5, !dbg !1827

if.else:                                          ; preds = %entry
  %call1 = call i32 @clock_gettime(i32 7, %struct.timespec* %now) #9, !dbg !1828
  store i32 %call1, i32* %r, align 4, !dbg !1830
  %tobool2 = icmp ne i32 %call1, 0, !dbg !1830
  br i1 %tobool2, label %land.lhs.true, label %if.end, !dbg !1831

land.lhs.true:                                    ; preds = %if.else
  %call3 = call i32* @__errno_location() #1, !dbg !1832
  %1 = load i32, i32* %call3, align 4, !dbg !1832
  %cmp = icmp eq i32 %1, 22, !dbg !1834
  br i1 %cmp, label %if.then4, label %if.end, !dbg !1835

if.then4:                                         ; preds = %land.lhs.true
  store volatile i32 1, i32* @uv_uptime.no_clock_boottime, align 4, !dbg !1836
  br label %retry, !dbg !1838

if.end:                                           ; preds = %land.lhs.true, %if.else
  br label %if.end5

if.end5:                                          ; preds = %if.end, %retry
  %2 = load i32, i32* %r, align 4, !dbg !1839
  %tobool6 = icmp ne i32 %2, 0, !dbg !1839
  br i1 %tobool6, label %if.then7, label %if.end9, !dbg !1841

if.then7:                                         ; preds = %if.end5
  %call8 = call i32* @__errno_location() #1, !dbg !1842
  %3 = load i32, i32* %call8, align 4, !dbg !1842
  %sub = sub nsw i32 0, %3, !dbg !1843
  store i32 %sub, i32* %retval, align 4, !dbg !1844
  br label %return, !dbg !1844

if.end9:                                          ; preds = %if.end5
  %tv_sec = getelementptr inbounds %struct.timespec, %struct.timespec* %now, i32 0, i32 0, !dbg !1845
  %4 = load i64, i64* %tv_sec, align 8, !dbg !1845
  %conv = sitofp i64 %4 to double, !dbg !1846
  %5 = load double*, double** %uptime.addr, align 8, !dbg !1847
  store double %conv, double* %5, align 8, !dbg !1848
  store i32 0, i32* %retval, align 4, !dbg !1849
  br label %return, !dbg !1849

return:                                           ; preds = %if.end9, %if.then7
  %6 = load i32, i32* %retval, align 4, !dbg !1850
  ret i32 %6, !dbg !1850
}

; Function Attrs: nounwind uwtable
define i32 @uv_cpu_info(%struct.uv_cpu_info_s** %cpu_infos, i32* %count) #0 !dbg !587 {
entry:
  %retval = alloca i32, align 4
  %cpu_infos.addr = alloca %struct.uv_cpu_info_s**, align 8
  %count.addr = alloca i32*, align 8
  %numcpus = alloca i32, align 4
  %ci = alloca %struct.uv_cpu_info_s*, align 8
  %err = alloca i32, align 4
  %statfile_fp = alloca %struct._IO_FILE*, align 8
  store %struct.uv_cpu_info_s** %cpu_infos, %struct.uv_cpu_info_s*** %cpu_infos.addr, align 8
  call void @llvm.dbg.declare(metadata %struct.uv_cpu_info_s*** %cpu_infos.addr, metadata !1851, metadata !760), !dbg !1852
  store i32* %count, i32** %count.addr, align 8
  call void @llvm.dbg.declare(metadata i32** %count.addr, metadata !1853, metadata !760), !dbg !1854
  call void @llvm.dbg.declare(metadata i32* %numcpus, metadata !1855, metadata !760), !dbg !1856
  call void @llvm.dbg.declare(metadata %struct.uv_cpu_info_s** %ci, metadata !1857, metadata !760), !dbg !1858
  call void @llvm.dbg.declare(metadata i32* %err, metadata !1859, metadata !760), !dbg !1860
  call void @llvm.dbg.declare(metadata %struct._IO_FILE** %statfile_fp, metadata !1861, metadata !760), !dbg !1862
  %0 = load %struct.uv_cpu_info_s**, %struct.uv_cpu_info_s*** %cpu_infos.addr, align 8, !dbg !1863
  store %struct.uv_cpu_info_s* null, %struct.uv_cpu_info_s** %0, align 8, !dbg !1864
  %1 = load i32*, i32** %count.addr, align 8, !dbg !1865
  store i32 0, i32* %1, align 4, !dbg !1866
  %call = call %struct._IO_FILE* @uv__open_file(i8* getelementptr inbounds ([11 x i8], [11 x i8]* @.str.15, i32 0, i32 0)), !dbg !1867
  store %struct._IO_FILE* %call, %struct._IO_FILE** %statfile_fp, align 8, !dbg !1868
  %2 = load %struct._IO_FILE*, %struct._IO_FILE** %statfile_fp, align 8, !dbg !1869
  %cmp = icmp eq %struct._IO_FILE* %2, null, !dbg !1871
  br i1 %cmp, label %if.then, label %if.end, !dbg !1872

if.then:                                          ; preds = %entry
  %call1 = call i32* @__errno_location() #1, !dbg !1873
  %3 = load i32, i32* %call1, align 4, !dbg !1873
  %sub = sub nsw i32 0, %3, !dbg !1874
  store i32 %sub, i32* %retval, align 4, !dbg !1875
  br label %return, !dbg !1875

if.end:                                           ; preds = %entry
  %4 = load %struct._IO_FILE*, %struct._IO_FILE** %statfile_fp, align 8, !dbg !1876
  %call2 = call i32 @uv__cpu_num(%struct._IO_FILE* %4, i32* %numcpus), !dbg !1877
  store i32 %call2, i32* %err, align 4, !dbg !1878
  %5 = load i32, i32* %err, align 4, !dbg !1879
  %cmp3 = icmp slt i32 %5, 0, !dbg !1881
  br i1 %cmp3, label %if.then4, label %if.end5, !dbg !1882

if.then4:                                         ; preds = %if.end
  br label %out, !dbg !1883

if.end5:                                          ; preds = %if.end
  store i32 -12, i32* %err, align 4, !dbg !1884
  %6 = load i32, i32* %numcpus, align 4, !dbg !1885
  %conv = zext i32 %6 to i64, !dbg !1885
  %call6 = call i8* @uv__calloc(i64 %conv, i64 56), !dbg !1886
  %7 = bitcast i8* %call6 to %struct.uv_cpu_info_s*, !dbg !1886
  store %struct.uv_cpu_info_s* %7, %struct.uv_cpu_info_s** %ci, align 8, !dbg !1887
  %8 = load %struct.uv_cpu_info_s*, %struct.uv_cpu_info_s** %ci, align 8, !dbg !1888
  %cmp7 = icmp eq %struct.uv_cpu_info_s* %8, null, !dbg !1890
  br i1 %cmp7, label %if.then9, label %if.end10, !dbg !1891

if.then9:                                         ; preds = %if.end5
  br label %out, !dbg !1892

if.end10:                                         ; preds = %if.end5
  %9 = load i32, i32* %numcpus, align 4, !dbg !1893
  %10 = load %struct.uv_cpu_info_s*, %struct.uv_cpu_info_s** %ci, align 8, !dbg !1894
  %call11 = call i32 @read_models(i32 %9, %struct.uv_cpu_info_s* %10), !dbg !1895
  store i32 %call11, i32* %err, align 4, !dbg !1896
  %11 = load i32, i32* %err, align 4, !dbg !1897
  %cmp12 = icmp eq i32 %11, 0, !dbg !1899
  br i1 %cmp12, label %if.then14, label %if.end16, !dbg !1900

if.then14:                                        ; preds = %if.end10
  %12 = load %struct._IO_FILE*, %struct._IO_FILE** %statfile_fp, align 8, !dbg !1901
  %13 = load i32, i32* %numcpus, align 4, !dbg !1902
  %14 = load %struct.uv_cpu_info_s*, %struct.uv_cpu_info_s** %ci, align 8, !dbg !1903
  %call15 = call i32 @read_times(%struct._IO_FILE* %12, i32 %13, %struct.uv_cpu_info_s* %14), !dbg !1904
  store i32 %call15, i32* %err, align 4, !dbg !1905
  br label %if.end16, !dbg !1906

if.end16:                                         ; preds = %if.then14, %if.end10
  %15 = load i32, i32* %err, align 4, !dbg !1907
  %tobool = icmp ne i32 %15, 0, !dbg !1907
  br i1 %tobool, label %if.then17, label %if.end18, !dbg !1909

if.then17:                                        ; preds = %if.end16
  %16 = load %struct.uv_cpu_info_s*, %struct.uv_cpu_info_s** %ci, align 8, !dbg !1910
  %17 = load i32, i32* %numcpus, align 4, !dbg !1912
  call void @uv_free_cpu_info(%struct.uv_cpu_info_s* %16, i32 %17), !dbg !1913
  br label %out, !dbg !1914

if.end18:                                         ; preds = %if.end16
  %18 = load %struct.uv_cpu_info_s*, %struct.uv_cpu_info_s** %ci, align 8, !dbg !1915
  %arrayidx = getelementptr inbounds %struct.uv_cpu_info_s, %struct.uv_cpu_info_s* %18, i64 0, !dbg !1915
  %speed = getelementptr inbounds %struct.uv_cpu_info_s, %struct.uv_cpu_info_s* %arrayidx, i32 0, i32 1, !dbg !1917
  %19 = load i32, i32* %speed, align 8, !dbg !1917
  %cmp19 = icmp eq i32 %19, 0, !dbg !1918
  br i1 %cmp19, label %if.then21, label %if.end22, !dbg !1919

if.then21:                                        ; preds = %if.end18
  %20 = load i32, i32* %numcpus, align 4, !dbg !1920
  %21 = load %struct.uv_cpu_info_s*, %struct.uv_cpu_info_s** %ci, align 8, !dbg !1921
  call void @read_speeds(i32 %20, %struct.uv_cpu_info_s* %21), !dbg !1922
  br label %if.end22, !dbg !1922

if.end22:                                         ; preds = %if.then21, %if.end18
  %22 = load %struct.uv_cpu_info_s*, %struct.uv_cpu_info_s** %ci, align 8, !dbg !1923
  %23 = load %struct.uv_cpu_info_s**, %struct.uv_cpu_info_s*** %cpu_infos.addr, align 8, !dbg !1924
  store %struct.uv_cpu_info_s* %22, %struct.uv_cpu_info_s** %23, align 8, !dbg !1925
  %24 = load i32, i32* %numcpus, align 4, !dbg !1926
  %25 = load i32*, i32** %count.addr, align 8, !dbg !1927
  store i32 %24, i32* %25, align 4, !dbg !1928
  store i32 0, i32* %err, align 4, !dbg !1929
  br label %out, !dbg !1930

out:                                              ; preds = %if.end22, %if.then17, %if.then9, %if.then4
  %26 = load %struct._IO_FILE*, %struct._IO_FILE** %statfile_fp, align 8, !dbg !1931
  %call23 = call i32 @fclose(%struct._IO_FILE* %26), !dbg !1933
  %tobool24 = icmp ne i32 %call23, 0, !dbg !1933
  br i1 %tobool24, label %if.then25, label %if.end34, !dbg !1934

if.then25:                                        ; preds = %out
  %call26 = call i32* @__errno_location() #1, !dbg !1935
  %27 = load i32, i32* %call26, align 4, !dbg !1935
  %cmp27 = icmp ne i32 %27, 4, !dbg !1937
  br i1 %cmp27, label %land.lhs.true, label %if.end33, !dbg !1938

land.lhs.true:                                    ; preds = %if.then25
  %call29 = call i32* @__errno_location() #1, !dbg !1939
  %28 = load i32, i32* %call29, align 4, !dbg !1939
  %cmp30 = icmp ne i32 %28, 115, !dbg !1941
  br i1 %cmp30, label %if.then32, label %if.end33, !dbg !1942

if.then32:                                        ; preds = %land.lhs.true
  call void @abort() #8, !dbg !1943
  unreachable, !dbg !1943

if.end33:                                         ; preds = %land.lhs.true, %if.then25
  br label %if.end34, !dbg !1944

if.end34:                                         ; preds = %if.end33, %out
  %29 = load i32, i32* %err, align 4, !dbg !1946
  store i32 %29, i32* %retval, align 4, !dbg !1947
  br label %return, !dbg !1947

return:                                           ; preds = %if.end34, %if.then
  %30 = load i32, i32* %retval, align 4, !dbg !1948
  ret i32 %30, !dbg !1948
}

declare %struct._IO_FILE* @uv__open_file(i8*) #2

; Function Attrs: nounwind uwtable
define internal i32 @uv__cpu_num(%struct._IO_FILE* %statfile_fp, i32* %numcpus) #0 !dbg !642 {
entry:
  %retval = alloca i32, align 4
  %statfile_fp.addr = alloca %struct._IO_FILE*, align 8
  %numcpus.addr = alloca i32*, align 8
  %num = alloca i32, align 4
  %buf = alloca [1024 x i8], align 16
  store %struct._IO_FILE* %statfile_fp, %struct._IO_FILE** %statfile_fp.addr, align 8
  call void @llvm.dbg.declare(metadata %struct._IO_FILE** %statfile_fp.addr, metadata !1949, metadata !760), !dbg !1950
  store i32* %numcpus, i32** %numcpus.addr, align 8
  call void @llvm.dbg.declare(metadata i32** %numcpus.addr, metadata !1951, metadata !760), !dbg !1952
  call void @llvm.dbg.declare(metadata i32* %num, metadata !1953, metadata !760), !dbg !1954
  call void @llvm.dbg.declare(metadata [1024 x i8]* %buf, metadata !1955, metadata !760), !dbg !1956
  %arraydecay = getelementptr inbounds [1024 x i8], [1024 x i8]* %buf, i32 0, i32 0, !dbg !1957
  %0 = load %struct._IO_FILE*, %struct._IO_FILE** %statfile_fp.addr, align 8, !dbg !1959
  %call = call i8* @fgets(i8* %arraydecay, i32 1024, %struct._IO_FILE* %0), !dbg !1960
  %tobool = icmp ne i8* %call, null, !dbg !1960
  br i1 %tobool, label %if.end, label %if.then, !dbg !1961

if.then:                                          ; preds = %entry
  store i32 -5, i32* %retval, align 4, !dbg !1962
  br label %return, !dbg !1962

if.end:                                           ; preds = %entry
  store i32 0, i32* %num, align 4, !dbg !1963
  br label %while.cond, !dbg !1964

while.cond:                                       ; preds = %if.end8, %if.end
  %arraydecay1 = getelementptr inbounds [1024 x i8], [1024 x i8]* %buf, i32 0, i32 0, !dbg !1965
  %1 = load %struct._IO_FILE*, %struct._IO_FILE** %statfile_fp.addr, align 8, !dbg !1967
  %call2 = call i8* @fgets(i8* %arraydecay1, i32 1024, %struct._IO_FILE* %1), !dbg !1968
  %tobool3 = icmp ne i8* %call2, null, !dbg !1969
  br i1 %tobool3, label %while.body, label %while.end, !dbg !1969

while.body:                                       ; preds = %while.cond
  %arraydecay4 = getelementptr inbounds [1024 x i8], [1024 x i8]* %buf, i32 0, i32 0, !dbg !1970
  %call5 = call i32 @strncmp(i8* %arraydecay4, i8* getelementptr inbounds ([4 x i8], [4 x i8]* @.str.16, i32 0, i32 0), i64 3) #10, !dbg !1973
  %tobool6 = icmp ne i32 %call5, 0, !dbg !1973
  br i1 %tobool6, label %if.then7, label %if.end8, !dbg !1974

if.then7:                                         ; preds = %while.body
  br label %while.end, !dbg !1975

if.end8:                                          ; preds = %while.body
  %2 = load i32, i32* %num, align 4, !dbg !1976
  %inc = add i32 %2, 1, !dbg !1976
  store i32 %inc, i32* %num, align 4, !dbg !1976
  br label %while.cond, !dbg !1977

while.end:                                        ; preds = %if.then7, %while.cond
  %3 = load i32, i32* %num, align 4, !dbg !1979
  %cmp = icmp eq i32 %3, 0, !dbg !1981
  br i1 %cmp, label %if.then9, label %if.end10, !dbg !1982

if.then9:                                         ; preds = %while.end
  store i32 -5, i32* %retval, align 4, !dbg !1983
  br label %return, !dbg !1983

if.end10:                                         ; preds = %while.end
  %4 = load i32, i32* %num, align 4, !dbg !1984
  %5 = load i32*, i32** %numcpus.addr, align 8, !dbg !1985
  store i32 %4, i32* %5, align 4, !dbg !1986
  store i32 0, i32* %retval, align 4, !dbg !1987
  br label %return, !dbg !1987

return:                                           ; preds = %if.end10, %if.then9, %if.then
  %6 = load i32, i32* %retval, align 4, !dbg !1988
  ret i32 %6, !dbg !1988
}

declare i8* @uv__calloc(i64, i64) #2

; Function Attrs: nounwind uwtable
define internal i32 @read_models(i32 %numcpus, %struct.uv_cpu_info_s* %ci) #0 !dbg !706 {
entry:
  %retval = alloca i32, align 4
  %numcpus.addr = alloca i32, align 4
  %ci.addr = alloca %struct.uv_cpu_info_s*, align 8
  %inferred_model = alloca i8*, align 8
  %model_idx = alloca i32, align 4
  %speed_idx = alloca i32, align 4
  %buf = alloca [1024 x i8], align 16
  %model = alloca i8*, align 8
  %fp = alloca %struct._IO_FILE*, align 8
  store i32 %numcpus, i32* %numcpus.addr, align 4
  call void @llvm.dbg.declare(metadata i32* %numcpus.addr, metadata !1989, metadata !760), !dbg !1990
  store %struct.uv_cpu_info_s* %ci, %struct.uv_cpu_info_s** %ci.addr, align 8
  call void @llvm.dbg.declare(metadata %struct.uv_cpu_info_s** %ci.addr, metadata !1991, metadata !760), !dbg !1992
  call void @llvm.dbg.declare(metadata i8** %inferred_model, metadata !1993, metadata !760), !dbg !1994
  call void @llvm.dbg.declare(metadata i32* %model_idx, metadata !1995, metadata !760), !dbg !1996
  call void @llvm.dbg.declare(metadata i32* %speed_idx, metadata !1997, metadata !760), !dbg !1998
  call void @llvm.dbg.declare(metadata [1024 x i8]* %buf, metadata !1999, metadata !760), !dbg !2000
  call void @llvm.dbg.declare(metadata i8** %model, metadata !2001, metadata !760), !dbg !2002
  call void @llvm.dbg.declare(metadata %struct._IO_FILE** %fp, metadata !2003, metadata !760), !dbg !2004
  store i32 0, i32* %model_idx, align 4, !dbg !2005
  store i32 0, i32* %speed_idx, align 4, !dbg !2006
  %call = call %struct._IO_FILE* @uv__open_file(i8* getelementptr inbounds ([14 x i8], [14 x i8]* @.str.19, i32 0, i32 0)), !dbg !2007
  store %struct._IO_FILE* %call, %struct._IO_FILE** %fp, align 8, !dbg !2008
  %0 = load %struct._IO_FILE*, %struct._IO_FILE** %fp, align 8, !dbg !2009
  %cmp = icmp eq %struct._IO_FILE* %0, null, !dbg !2011
  br i1 %cmp, label %if.then, label %if.end, !dbg !2012

if.then:                                          ; preds = %entry
  %call1 = call i32* @__errno_location() #1, !dbg !2013
  %1 = load i32, i32* %call1, align 4, !dbg !2013
  %sub = sub nsw i32 0, %1, !dbg !2014
  store i32 %sub, i32* %retval, align 4, !dbg !2015
  br label %return, !dbg !2015

if.end:                                           ; preds = %entry
  br label %while.cond, !dbg !2016

while.cond:                                       ; preds = %if.end35, %if.then26, %if.end17, %if.end
  %arraydecay = getelementptr inbounds [1024 x i8], [1024 x i8]* %buf, i32 0, i32 0, !dbg !2017
  %2 = load %struct._IO_FILE*, %struct._IO_FILE** %fp, align 8, !dbg !2019
  %call2 = call i8* @fgets(i8* %arraydecay, i32 1024, %struct._IO_FILE* %2), !dbg !2020
  %tobool = icmp ne i8* %call2, null, !dbg !2021
  br i1 %tobool, label %while.body, label %while.end, !dbg !2021

while.body:                                       ; preds = %while.cond
  %3 = load i32, i32* %model_idx, align 4, !dbg !2022
  %4 = load i32, i32* %numcpus.addr, align 4, !dbg !2025
  %cmp3 = icmp ult i32 %3, %4, !dbg !2026
  br i1 %cmp3, label %if.then4, label %if.end20, !dbg !2027

if.then4:                                         ; preds = %while.body
  %arraydecay5 = getelementptr inbounds [1024 x i8], [1024 x i8]* %buf, i32 0, i32 0, !dbg !2028
  %call6 = call i32 @strncmp(i8* %arraydecay5, i8* getelementptr inbounds ([14 x i8], [14 x i8]* @read_models.model_marker, i32 0, i32 0), i64 13) #10, !dbg !2031
  %cmp7 = icmp eq i32 %call6, 0, !dbg !2032
  br i1 %cmp7, label %if.then8, label %if.end19, !dbg !2033

if.then8:                                         ; preds = %if.then4
  %arraydecay9 = getelementptr inbounds [1024 x i8], [1024 x i8]* %buf, i32 0, i32 0, !dbg !2034
  %add.ptr = getelementptr inbounds i8, i8* %arraydecay9, i64 14, !dbg !2036
  %add.ptr10 = getelementptr inbounds i8, i8* %add.ptr, i64 -1, !dbg !2037
  store i8* %add.ptr10, i8** %model, align 8, !dbg !2038
  %5 = load i8*, i8** %model, align 8, !dbg !2039
  %6 = load i8*, i8** %model, align 8, !dbg !2040
  %call11 = call i64 @strlen(i8* %6) #10, !dbg !2041
  %sub12 = sub i64 %call11, 1, !dbg !2042
  %call13 = call i8* @uv__strndup(i8* %5, i64 %sub12), !dbg !2043
  store i8* %call13, i8** %model, align 8, !dbg !2045
  %7 = load i8*, i8** %model, align 8, !dbg !2046
  %cmp14 = icmp eq i8* %7, null, !dbg !2048
  br i1 %cmp14, label %if.then15, label %if.end17, !dbg !2049

if.then15:                                        ; preds = %if.then8
  %8 = load %struct._IO_FILE*, %struct._IO_FILE** %fp, align 8, !dbg !2050
  %call16 = call i32 @fclose(%struct._IO_FILE* %8), !dbg !2052
  store i32 -12, i32* %retval, align 4, !dbg !2053
  br label %return, !dbg !2053

if.end17:                                         ; preds = %if.then8
  %9 = load i8*, i8** %model, align 8, !dbg !2054
  %10 = load i32, i32* %model_idx, align 4, !dbg !2055
  %inc = add i32 %10, 1, !dbg !2055
  store i32 %inc, i32* %model_idx, align 4, !dbg !2055
  %idxprom = zext i32 %10 to i64, !dbg !2056
  %11 = load %struct.uv_cpu_info_s*, %struct.uv_cpu_info_s** %ci.addr, align 8, !dbg !2056
  %arrayidx = getelementptr inbounds %struct.uv_cpu_info_s, %struct.uv_cpu_info_s* %11, i64 %idxprom, !dbg !2056
  %model18 = getelementptr inbounds %struct.uv_cpu_info_s, %struct.uv_cpu_info_s* %arrayidx, i32 0, i32 0, !dbg !2057
  store i8* %9, i8** %model18, align 8, !dbg !2058
  br label %while.cond, !dbg !2059

if.end19:                                         ; preds = %if.then4
  br label %if.end20, !dbg !2060

if.end20:                                         ; preds = %if.end19, %while.body
  %12 = load i32, i32* %speed_idx, align 4, !dbg !2061
  %13 = load i32, i32* %numcpus.addr, align 4, !dbg !2063
  %cmp21 = icmp ult i32 %12, %13, !dbg !2064
  br i1 %cmp21, label %if.then22, label %if.end35, !dbg !2065

if.then22:                                        ; preds = %if.end20
  %arraydecay23 = getelementptr inbounds [1024 x i8], [1024 x i8]* %buf, i32 0, i32 0, !dbg !2066
  %call24 = call i32 @strncmp(i8* %arraydecay23, i8* getelementptr inbounds ([12 x i8], [12 x i8]* @read_models.speed_marker, i32 0, i32 0), i64 11) #10, !dbg !2069
  %cmp25 = icmp eq i32 %call24, 0, !dbg !2070
  br i1 %cmp25, label %if.then26, label %if.end34, !dbg !2071

if.then26:                                        ; preds = %if.then22
  %arraydecay27 = getelementptr inbounds [1024 x i8], [1024 x i8]* %buf, i32 0, i32 0, !dbg !2072
  %add.ptr28 = getelementptr inbounds i8, i8* %arraydecay27, i64 12, !dbg !2074
  %add.ptr29 = getelementptr inbounds i8, i8* %add.ptr28, i64 -1, !dbg !2075
  %call30 = call i32 @atoi(i8* %add.ptr29) #10, !dbg !2076
  %14 = load i32, i32* %speed_idx, align 4, !dbg !2077
  %inc31 = add i32 %14, 1, !dbg !2077
  store i32 %inc31, i32* %speed_idx, align 4, !dbg !2077
  %idxprom32 = zext i32 %14 to i64, !dbg !2078
  %15 = load %struct.uv_cpu_info_s*, %struct.uv_cpu_info_s** %ci.addr, align 8, !dbg !2078
  %arrayidx33 = getelementptr inbounds %struct.uv_cpu_info_s, %struct.uv_cpu_info_s* %15, i64 %idxprom32, !dbg !2078
  %speed = getelementptr inbounds %struct.uv_cpu_info_s, %struct.uv_cpu_info_s* %arrayidx33, i32 0, i32 1, !dbg !2079
  store i32 %call30, i32* %speed, align 8, !dbg !2080
  br label %while.cond, !dbg !2081

if.end34:                                         ; preds = %if.then22
  br label %if.end35, !dbg !2082

if.end35:                                         ; preds = %if.end34, %if.end20
  br label %while.cond, !dbg !2083

while.end:                                        ; preds = %while.cond
  %16 = load %struct._IO_FILE*, %struct._IO_FILE** %fp, align 8, !dbg !2085
  %call36 = call i32 @fclose(%struct._IO_FILE* %16), !dbg !2086
  store i8* getelementptr inbounds ([8 x i8], [8 x i8]* @.str.20, i32 0, i32 0), i8** %inferred_model, align 8, !dbg !2087
  %17 = load i32, i32* %model_idx, align 4, !dbg !2088
  %cmp37 = icmp ugt i32 %17, 0, !dbg !2090
  br i1 %cmp37, label %if.then38, label %if.end43, !dbg !2091

if.then38:                                        ; preds = %while.end
  %18 = load i32, i32* %model_idx, align 4, !dbg !2092
  %sub39 = sub i32 %18, 1, !dbg !2093
  %idxprom40 = zext i32 %sub39 to i64, !dbg !2094
  %19 = load %struct.uv_cpu_info_s*, %struct.uv_cpu_info_s** %ci.addr, align 8, !dbg !2094
  %arrayidx41 = getelementptr inbounds %struct.uv_cpu_info_s, %struct.uv_cpu_info_s* %19, i64 %idxprom40, !dbg !2094
  %model42 = getelementptr inbounds %struct.uv_cpu_info_s, %struct.uv_cpu_info_s* %arrayidx41, i32 0, i32 0, !dbg !2095
  %20 = load i8*, i8** %model42, align 8, !dbg !2095
  store i8* %20, i8** %inferred_model, align 8, !dbg !2096
  br label %if.end43, !dbg !2097

if.end43:                                         ; preds = %if.then38, %while.end
  br label %while.cond44, !dbg !2098

while.cond44:                                     ; preds = %if.end51, %if.end43
  %21 = load i32, i32* %model_idx, align 4, !dbg !2099
  %22 = load i32, i32* %numcpus.addr, align 4, !dbg !2100
  %cmp45 = icmp ult i32 %21, %22, !dbg !2101
  br i1 %cmp45, label %while.body46, label %while.end56, !dbg !2102

while.body46:                                     ; preds = %while.cond44
  %23 = load i8*, i8** %inferred_model, align 8, !dbg !2103
  %24 = load i8*, i8** %inferred_model, align 8, !dbg !2105
  %call47 = call i64 @strlen(i8* %24) #10, !dbg !2106
  %call48 = call i8* @uv__strndup(i8* %23, i64 %call47), !dbg !2107
  store i8* %call48, i8** %model, align 8, !dbg !2109
  %25 = load i8*, i8** %model, align 8, !dbg !2110
  %cmp49 = icmp eq i8* %25, null, !dbg !2112
  br i1 %cmp49, label %if.then50, label %if.end51, !dbg !2113

if.then50:                                        ; preds = %while.body46
  store i32 -12, i32* %retval, align 4, !dbg !2114
  br label %return, !dbg !2114

if.end51:                                         ; preds = %while.body46
  %26 = load i8*, i8** %model, align 8, !dbg !2115
  %27 = load i32, i32* %model_idx, align 4, !dbg !2116
  %inc52 = add i32 %27, 1, !dbg !2116
  store i32 %inc52, i32* %model_idx, align 4, !dbg !2116
  %idxprom53 = zext i32 %27 to i64, !dbg !2117
  %28 = load %struct.uv_cpu_info_s*, %struct.uv_cpu_info_s** %ci.addr, align 8, !dbg !2117
  %arrayidx54 = getelementptr inbounds %struct.uv_cpu_info_s, %struct.uv_cpu_info_s* %28, i64 %idxprom53, !dbg !2117
  %model55 = getelementptr inbounds %struct.uv_cpu_info_s, %struct.uv_cpu_info_s* %arrayidx54, i32 0, i32 0, !dbg !2118
  store i8* %26, i8** %model55, align 8, !dbg !2119
  br label %while.cond44, !dbg !2120

while.end56:                                      ; preds = %while.cond44
  store i32 0, i32* %retval, align 4, !dbg !2121
  br label %return, !dbg !2121

return:                                           ; preds = %while.end56, %if.then50, %if.then15, %if.then
  %29 = load i32, i32* %retval, align 4, !dbg !2122
  ret i32 %29, !dbg !2122
}

; Function Attrs: nounwind uwtable
define internal i32 @read_times(%struct._IO_FILE* %statfile_fp, i32 %numcpus, %struct.uv_cpu_info_s* %ci) #0 !dbg !709 {
entry:
  %statfile_fp.addr = alloca %struct._IO_FILE*, align 8
  %numcpus.addr = alloca i32, align 4
  %ci.addr = alloca %struct.uv_cpu_info_s*, align 8
  %clock_ticks = alloca i64, align 8
  %ts = alloca %struct.uv_cpu_times_s, align 8
  %user = alloca i64, align 8
  %nice = alloca i64, align 8
  %sys = alloca i64, align 8
  %idle = alloca i64, align 8
  %dummy = alloca i64, align 8
  %irq = alloca i64, align 8
  %num = alloca i32, align 4
  %len = alloca i32, align 4
  %buf = alloca [1024 x i8], align 16
  %n = alloca i32, align 4
  %r = alloca i32, align 4
  store %struct._IO_FILE* %statfile_fp, %struct._IO_FILE** %statfile_fp.addr, align 8
  call void @llvm.dbg.declare(metadata %struct._IO_FILE** %statfile_fp.addr, metadata !2123, metadata !760), !dbg !2124
  store i32 %numcpus, i32* %numcpus.addr, align 4
  call void @llvm.dbg.declare(metadata i32* %numcpus.addr, metadata !2125, metadata !760), !dbg !2126
  store %struct.uv_cpu_info_s* %ci, %struct.uv_cpu_info_s** %ci.addr, align 8
  call void @llvm.dbg.declare(metadata %struct.uv_cpu_info_s** %ci.addr, metadata !2127, metadata !760), !dbg !2128
  call void @llvm.dbg.declare(metadata i64* %clock_ticks, metadata !2129, metadata !760), !dbg !2130
  call void @llvm.dbg.declare(metadata %struct.uv_cpu_times_s* %ts, metadata !2131, metadata !760), !dbg !2132
  call void @llvm.dbg.declare(metadata i64* %user, metadata !2133, metadata !760), !dbg !2134
  call void @llvm.dbg.declare(metadata i64* %nice, metadata !2135, metadata !760), !dbg !2136
  call void @llvm.dbg.declare(metadata i64* %sys, metadata !2137, metadata !760), !dbg !2138
  call void @llvm.dbg.declare(metadata i64* %idle, metadata !2139, metadata !760), !dbg !2140
  call void @llvm.dbg.declare(metadata i64* %dummy, metadata !2141, metadata !760), !dbg !2142
  call void @llvm.dbg.declare(metadata i64* %irq, metadata !2143, metadata !760), !dbg !2144
  call void @llvm.dbg.declare(metadata i32* %num, metadata !2145, metadata !760), !dbg !2146
  call void @llvm.dbg.declare(metadata i32* %len, metadata !2147, metadata !760), !dbg !2148
  call void @llvm.dbg.declare(metadata [1024 x i8]* %buf, metadata !2149, metadata !760), !dbg !2150
  %call = call i64 @sysconf(i32 2) #9, !dbg !2151
  store i64 %call, i64* %clock_ticks, align 8, !dbg !2152
  %0 = load i64, i64* %clock_ticks, align 8, !dbg !2153
  %cmp = icmp ne i64 %0, -1, !dbg !2153
  br i1 %cmp, label %cond.true, label %cond.false, !dbg !2153

cond.true:                                        ; preds = %entry
  br label %cond.end, !dbg !2154

cond.false:                                       ; preds = %entry
  call void @__assert_fail(i8* getelementptr inbounds ([34 x i8], [34 x i8]* @.str.21, i32 0, i32 0), i8* getelementptr inbounds ([74 x i8], [74 x i8]* @.str.1, i32 0, i32 0), i32 801, i8* getelementptr inbounds ([54 x i8], [54 x i8]* @__PRETTY_FUNCTION__.read_times, i32 0, i32 0)) #8, !dbg !2156
  unreachable, !dbg !2156
                                                  ; No predecessors!
  br label %cond.end, !dbg !2158

cond.end:                                         ; preds = %1, %cond.true
  %2 = load i64, i64* %clock_ticks, align 8, !dbg !2160
  %cmp1 = icmp ne i64 %2, 0, !dbg !2160
  br i1 %cmp1, label %cond.true2, label %cond.false3, !dbg !2160

cond.true2:                                       ; preds = %cond.end
  br label %cond.end4, !dbg !2161

cond.false3:                                      ; preds = %cond.end
  call void @__assert_fail(i8* getelementptr inbounds ([17 x i8], [17 x i8]* @.str.22, i32 0, i32 0), i8* getelementptr inbounds ([74 x i8], [74 x i8]* @.str.1, i32 0, i32 0), i32 802, i8* getelementptr inbounds ([54 x i8], [54 x i8]* @__PRETTY_FUNCTION__.read_times, i32 0, i32 0)) #8, !dbg !2162
  unreachable, !dbg !2162
                                                  ; No predecessors!
  br label %cond.end4, !dbg !2163

cond.end4:                                        ; preds = %3, %cond.true2
  %4 = load %struct._IO_FILE*, %struct._IO_FILE** %statfile_fp.addr, align 8, !dbg !2164
  call void @rewind(%struct._IO_FILE* %4), !dbg !2165
  %arraydecay = getelementptr inbounds [1024 x i8], [1024 x i8]* %buf, i32 0, i32 0, !dbg !2166
  %5 = load %struct._IO_FILE*, %struct._IO_FILE** %statfile_fp.addr, align 8, !dbg !2168
  %call5 = call i8* @fgets(i8* %arraydecay, i32 1024, %struct._IO_FILE* %5), !dbg !2169
  %tobool = icmp ne i8* %call5, null, !dbg !2169
  br i1 %tobool, label %if.end, label %if.then, !dbg !2170

if.then:                                          ; preds = %cond.end4
  call void @abort() #8, !dbg !2171
  unreachable, !dbg !2171

if.end:                                           ; preds = %cond.end4
  store i32 0, i32* %num, align 4, !dbg !2172
  br label %while.cond, !dbg !2173

while.cond:                                       ; preds = %if.end28, %if.end
  %arraydecay6 = getelementptr inbounds [1024 x i8], [1024 x i8]* %buf, i32 0, i32 0, !dbg !2174
  %6 = load %struct._IO_FILE*, %struct._IO_FILE** %statfile_fp.addr, align 8, !dbg !2175
  %call7 = call i8* @fgets(i8* %arraydecay6, i32 1024, %struct._IO_FILE* %6), !dbg !2176
  %tobool8 = icmp ne i8* %call7, null, !dbg !2177
  br i1 %tobool8, label %while.body, label %while.end, !dbg !2177

while.body:                                       ; preds = %while.cond
  %7 = load i32, i32* %num, align 4, !dbg !2178
  %8 = load i32, i32* %numcpus.addr, align 4, !dbg !2181
  %cmp9 = icmp uge i32 %7, %8, !dbg !2182
  br i1 %cmp9, label %if.then10, label %if.end11, !dbg !2183

if.then10:                                        ; preds = %while.body
  br label %while.end, !dbg !2184

if.end11:                                         ; preds = %while.body
  %arraydecay12 = getelementptr inbounds [1024 x i8], [1024 x i8]* %buf, i32 0, i32 0, !dbg !2185
  %call13 = call i32 @strncmp(i8* %arraydecay12, i8* getelementptr inbounds ([4 x i8], [4 x i8]* @.str.16, i32 0, i32 0), i64 3) #10, !dbg !2187
  %tobool14 = icmp ne i32 %call13, 0, !dbg !2187
  br i1 %tobool14, label %if.then15, label %if.end16, !dbg !2188

if.then15:                                        ; preds = %if.end11
  br label %while.end, !dbg !2189

if.end16:                                         ; preds = %if.end11
  call void @llvm.dbg.declare(metadata i32* %n, metadata !2190, metadata !760), !dbg !2192
  call void @llvm.dbg.declare(metadata i32* %r, metadata !2193, metadata !760), !dbg !2194
  %arraydecay17 = getelementptr inbounds [1024 x i8], [1024 x i8]* %buf, i32 0, i32 0, !dbg !2195
  %call18 = call i32 (i8*, i8*, ...) @sscanf(i8* %arraydecay17, i8* getelementptr inbounds ([7 x i8], [7 x i8]* @.str.23, i32 0, i32 0), i32* %n) #9, !dbg !2196
  store i32 %call18, i32* %r, align 4, !dbg !2194
  %9 = load i32, i32* %r, align 4, !dbg !2197
  %cmp19 = icmp eq i32 %9, 1, !dbg !2197
  br i1 %cmp19, label %cond.true20, label %cond.false21, !dbg !2197

cond.true20:                                      ; preds = %if.end16
  br label %cond.end22, !dbg !2198

cond.false21:                                     ; preds = %if.end16
  call void @__assert_fail(i8* getelementptr inbounds ([7 x i8], [7 x i8]* @.str.24, i32 0, i32 0), i8* getelementptr inbounds ([74 x i8], [74 x i8]* @.str.1, i32 0, i32 0), i32 822, i8* getelementptr inbounds ([54 x i8], [54 x i8]* @__PRETTY_FUNCTION__.read_times, i32 0, i32 0)) #8, !dbg !2200
  unreachable, !dbg !2200
                                                  ; No predecessors!
  br label %cond.end22, !dbg !2202

cond.end22:                                       ; preds = %10, %cond.true20
  %11 = load i32, i32* %r, align 4, !dbg !2204
  store i32 5, i32* %len, align 4, !dbg !2205
  br label %for.cond, !dbg !2207

for.cond:                                         ; preds = %for.inc, %cond.end22
  %12 = load i32, i32* %n, align 4, !dbg !2208
  %div = udiv i32 %12, 10, !dbg !2208
  store i32 %div, i32* %n, align 4, !dbg !2208
  %tobool23 = icmp ne i32 %div, 0, !dbg !2211
  br i1 %tobool23, label %for.body, label %for.end, !dbg !2211

for.body:                                         ; preds = %for.cond
  br label %for.inc, !dbg !2212

for.inc:                                          ; preds = %for.body
  %13 = load i32, i32* %len, align 4, !dbg !2214
  %inc = add i32 %13, 1, !dbg !2214
  store i32 %inc, i32* %len, align 4, !dbg !2214
  br label %for.cond, !dbg !2216

for.end:                                          ; preds = %for.cond
  %arraydecay24 = getelementptr inbounds [1024 x i8], [1024 x i8]* %buf, i32 0, i32 0, !dbg !2217
  %14 = load i32, i32* %len, align 4, !dbg !2219
  %idx.ext = zext i32 %14 to i64, !dbg !2220
  %add.ptr = getelementptr inbounds i8, i8* %arraydecay24, i64 %idx.ext, !dbg !2220
  %call25 = call i32 (i8*, i8*, ...) @sscanf(i8* %add.ptr, i8* getelementptr inbounds ([24 x i8], [24 x i8]* @.str.25, i32 0, i32 0), i64* %user, i64* %nice, i64* %sys, i64* %idle, i64* %dummy, i64* %irq) #9, !dbg !2221
  %cmp26 = icmp ne i32 6, %call25, !dbg !2222
  br i1 %cmp26, label %if.then27, label %if.end28, !dbg !2223

if.then27:                                        ; preds = %for.end
  call void @abort() #8, !dbg !2224
  unreachable, !dbg !2224

if.end28:                                         ; preds = %for.end
  %15 = load i64, i64* %clock_ticks, align 8, !dbg !2225
  %16 = load i64, i64* %user, align 8, !dbg !2226
  %mul = mul i64 %15, %16, !dbg !2227
  %user29 = getelementptr inbounds %struct.uv_cpu_times_s, %struct.uv_cpu_times_s* %ts, i32 0, i32 0, !dbg !2228
  store i64 %mul, i64* %user29, align 8, !dbg !2229
  %17 = load i64, i64* %clock_ticks, align 8, !dbg !2230
  %18 = load i64, i64* %nice, align 8, !dbg !2231
  %mul30 = mul i64 %17, %18, !dbg !2232
  %nice31 = getelementptr inbounds %struct.uv_cpu_times_s, %struct.uv_cpu_times_s* %ts, i32 0, i32 1, !dbg !2233
  store i64 %mul30, i64* %nice31, align 8, !dbg !2234
  %19 = load i64, i64* %clock_ticks, align 8, !dbg !2235
  %20 = load i64, i64* %sys, align 8, !dbg !2236
  %mul32 = mul i64 %19, %20, !dbg !2237
  %sys33 = getelementptr inbounds %struct.uv_cpu_times_s, %struct.uv_cpu_times_s* %ts, i32 0, i32 2, !dbg !2238
  store i64 %mul32, i64* %sys33, align 8, !dbg !2239
  %21 = load i64, i64* %clock_ticks, align 8, !dbg !2240
  %22 = load i64, i64* %idle, align 8, !dbg !2241
  %mul34 = mul i64 %21, %22, !dbg !2242
  %idle35 = getelementptr inbounds %struct.uv_cpu_times_s, %struct.uv_cpu_times_s* %ts, i32 0, i32 3, !dbg !2243
  store i64 %mul34, i64* %idle35, align 8, !dbg !2244
  %23 = load i64, i64* %clock_ticks, align 8, !dbg !2245
  %24 = load i64, i64* %irq, align 8, !dbg !2246
  %mul36 = mul i64 %23, %24, !dbg !2247
  %irq37 = getelementptr inbounds %struct.uv_cpu_times_s, %struct.uv_cpu_times_s* %ts, i32 0, i32 4, !dbg !2248
  store i64 %mul36, i64* %irq37, align 8, !dbg !2249
  %25 = load i32, i32* %num, align 4, !dbg !2250
  %inc38 = add i32 %25, 1, !dbg !2250
  store i32 %inc38, i32* %num, align 4, !dbg !2250
  %idxprom = zext i32 %25 to i64, !dbg !2251
  %26 = load %struct.uv_cpu_info_s*, %struct.uv_cpu_info_s** %ci.addr, align 8, !dbg !2251
  %arrayidx = getelementptr inbounds %struct.uv_cpu_info_s, %struct.uv_cpu_info_s* %26, i64 %idxprom, !dbg !2251
  %cpu_times = getelementptr inbounds %struct.uv_cpu_info_s, %struct.uv_cpu_info_s* %arrayidx, i32 0, i32 2, !dbg !2252
  %27 = bitcast %struct.uv_cpu_times_s* %cpu_times to i8*, !dbg !2253
  %28 = bitcast %struct.uv_cpu_times_s* %ts to i8*, !dbg !2253
  call void @llvm.memcpy.p0i8.p0i8.i64(i8* %27, i8* %28, i64 40, i32 8, i1 false), !dbg !2253
  br label %while.cond, !dbg !2254

while.end:                                        ; preds = %if.then15, %if.then10, %while.cond
  %29 = load i32, i32* %num, align 4, !dbg !2255
  %30 = load i32, i32* %numcpus.addr, align 4, !dbg !2255
  %cmp39 = icmp eq i32 %29, %30, !dbg !2255
  br i1 %cmp39, label %cond.true40, label %cond.false41, !dbg !2255

cond.true40:                                      ; preds = %while.end
  br label %cond.end42, !dbg !2256

cond.false41:                                     ; preds = %while.end
  call void @__assert_fail(i8* getelementptr inbounds ([15 x i8], [15 x i8]* @.str.26, i32 0, i32 0), i8* getelementptr inbounds ([74 x i8], [74 x i8]* @.str.1, i32 0, i32 0), i32 850, i8* getelementptr inbounds ([54 x i8], [54 x i8]* @__PRETTY_FUNCTION__.read_times, i32 0, i32 0)) #8, !dbg !2257
  unreachable, !dbg !2257
                                                  ; No predecessors!
  br label %cond.end42, !dbg !2258

cond.end42:                                       ; preds = %31, %cond.true40
  ret i32 0, !dbg !2259
}

; Function Attrs: nounwind uwtable
define void @uv_free_cpu_info(%struct.uv_cpu_info_s* %cpu_infos, i32 %count) #0 !dbg !606 {
entry:
  %cpu_infos.addr = alloca %struct.uv_cpu_info_s*, align 8
  %count.addr = alloca i32, align 4
  %i = alloca i32, align 4
  store %struct.uv_cpu_info_s* %cpu_infos, %struct.uv_cpu_info_s** %cpu_infos.addr, align 8
  call void @llvm.dbg.declare(metadata %struct.uv_cpu_info_s** %cpu_infos.addr, metadata !2260, metadata !760), !dbg !2261
  store i32 %count, i32* %count.addr, align 4
  call void @llvm.dbg.declare(metadata i32* %count.addr, metadata !2262, metadata !760), !dbg !2263
  call void @llvm.dbg.declare(metadata i32* %i, metadata !2264, metadata !760), !dbg !2265
  store i32 0, i32* %i, align 4, !dbg !2266
  br label %for.cond, !dbg !2268

for.cond:                                         ; preds = %for.inc, %entry
  %0 = load i32, i32* %i, align 4, !dbg !2269
  %1 = load i32, i32* %count.addr, align 4, !dbg !2272
  %cmp = icmp slt i32 %0, %1, !dbg !2273
  br i1 %cmp, label %for.body, label %for.end, !dbg !2274

for.body:                                         ; preds = %for.cond
  %2 = load i32, i32* %i, align 4, !dbg !2275
  %idxprom = sext i32 %2 to i64, !dbg !2277
  %3 = load %struct.uv_cpu_info_s*, %struct.uv_cpu_info_s** %cpu_infos.addr, align 8, !dbg !2277
  %arrayidx = getelementptr inbounds %struct.uv_cpu_info_s, %struct.uv_cpu_info_s* %3, i64 %idxprom, !dbg !2277
  %model = getelementptr inbounds %struct.uv_cpu_info_s, %struct.uv_cpu_info_s* %arrayidx, i32 0, i32 0, !dbg !2278
  %4 = load i8*, i8** %model, align 8, !dbg !2278
  call void @uv__free(i8* %4), !dbg !2279
  br label %for.inc, !dbg !2280

for.inc:                                          ; preds = %for.body
  %5 = load i32, i32* %i, align 4, !dbg !2281
  %inc = add nsw i32 %5, 1, !dbg !2281
  store i32 %inc, i32* %i, align 4, !dbg !2281
  br label %for.cond, !dbg !2283

for.end:                                          ; preds = %for.cond
  %6 = load %struct.uv_cpu_info_s*, %struct.uv_cpu_info_s** %cpu_infos.addr, align 8, !dbg !2284
  %7 = bitcast %struct.uv_cpu_info_s* %6 to i8*, !dbg !2284
  call void @uv__free(i8* %7), !dbg !2285
  ret void, !dbg !2286
}

; Function Attrs: nounwind uwtable
define internal void @read_speeds(i32 %numcpus, %struct.uv_cpu_info_s* %ci) #0 !dbg !700 {
entry:
  %numcpus.addr = alloca i32, align 4
  %ci.addr = alloca %struct.uv_cpu_info_s*, align 8
  %num = alloca i32, align 4
  store i32 %numcpus, i32* %numcpus.addr, align 4
  call void @llvm.dbg.declare(metadata i32* %numcpus.addr, metadata !2287, metadata !760), !dbg !2288
  store %struct.uv_cpu_info_s* %ci, %struct.uv_cpu_info_s** %ci.addr, align 8
  call void @llvm.dbg.declare(metadata %struct.uv_cpu_info_s** %ci.addr, metadata !2289, metadata !760), !dbg !2290
  call void @llvm.dbg.declare(metadata i32* %num, metadata !2291, metadata !760), !dbg !2292
  store i32 0, i32* %num, align 4, !dbg !2293
  br label %for.cond, !dbg !2295

for.cond:                                         ; preds = %for.inc, %entry
  %0 = load i32, i32* %num, align 4, !dbg !2296
  %1 = load i32, i32* %numcpus.addr, align 4, !dbg !2299
  %cmp = icmp ult i32 %0, %1, !dbg !2300
  br i1 %cmp, label %for.body, label %for.end, !dbg !2301

for.body:                                         ; preds = %for.cond
  %2 = load i32, i32* %num, align 4, !dbg !2302
  %call = call i64 @read_cpufreq(i32 %2), !dbg !2303
  %div = udiv i64 %call, 1000, !dbg !2304
  %conv = trunc i64 %div to i32, !dbg !2303
  %3 = load i32, i32* %num, align 4, !dbg !2305
  %idxprom = zext i32 %3 to i64, !dbg !2306
  %4 = load %struct.uv_cpu_info_s*, %struct.uv_cpu_info_s** %ci.addr, align 8, !dbg !2306
  %arrayidx = getelementptr inbounds %struct.uv_cpu_info_s, %struct.uv_cpu_info_s* %4, i64 %idxprom, !dbg !2306
  %speed = getelementptr inbounds %struct.uv_cpu_info_s, %struct.uv_cpu_info_s* %arrayidx, i32 0, i32 1, !dbg !2307
  store i32 %conv, i32* %speed, align 8, !dbg !2308
  br label %for.inc, !dbg !2306

for.inc:                                          ; preds = %for.body
  %5 = load i32, i32* %num, align 4, !dbg !2309
  %inc = add i32 %5, 1, !dbg !2309
  store i32 %inc, i32* %num, align 4, !dbg !2309
  br label %for.cond, !dbg !2311

for.end:                                          ; preds = %for.cond
  ret void, !dbg !2312
}

declare i32 @fclose(%struct._IO_FILE*) #2

declare void @uv__free(i8*) #2

; Function Attrs: nounwind uwtable
define i32 @uv_interface_addresses(%struct.uv_interface_address_s** %addresses, i32* %count) #0 !dbg !609 {
entry:
  %retval = alloca i32, align 4
  %addresses.addr = alloca %struct.uv_interface_address_s**, align 8
  %count.addr = alloca i32*, align 8
  %addrs = alloca %struct.ifaddrs*, align 8
  %ent = alloca %struct.ifaddrs*, align 8
  %address = alloca %struct.uv_interface_address_s*, align 8
  %i = alloca i32, align 4
  %sll = alloca %struct.sockaddr_ll*, align 8
  store %struct.uv_interface_address_s** %addresses, %struct.uv_interface_address_s*** %addresses.addr, align 8
  call void @llvm.dbg.declare(metadata %struct.uv_interface_address_s*** %addresses.addr, metadata !2313, metadata !760), !dbg !2314
  store i32* %count, i32** %count.addr, align 8
  call void @llvm.dbg.declare(metadata i32** %count.addr, metadata !2315, metadata !760), !dbg !2316
  call void @llvm.dbg.declare(metadata %struct.ifaddrs** %addrs, metadata !2317, metadata !760), !dbg !2318
  call void @llvm.dbg.declare(metadata %struct.ifaddrs** %ent, metadata !2319, metadata !760), !dbg !2320
  call void @llvm.dbg.declare(metadata %struct.uv_interface_address_s** %address, metadata !2321, metadata !760), !dbg !2322
  call void @llvm.dbg.declare(metadata i32* %i, metadata !2323, metadata !760), !dbg !2324
  call void @llvm.dbg.declare(metadata %struct.sockaddr_ll** %sll, metadata !2325, metadata !760), !dbg !2326
  %call = call i32 @getifaddrs(%struct.ifaddrs** %addrs) #9, !dbg !2327
  %tobool = icmp ne i32 %call, 0, !dbg !2327
  br i1 %tobool, label %if.then, label %if.end, !dbg !2329

if.then:                                          ; preds = %entry
  %call1 = call i32* @__errno_location() #1, !dbg !2330
  %0 = load i32, i32* %call1, align 4, !dbg !2330
  %sub = sub nsw i32 0, %0, !dbg !2331
  store i32 %sub, i32* %retval, align 4, !dbg !2332
  br label %return, !dbg !2332

if.end:                                           ; preds = %entry
  %1 = load i32*, i32** %count.addr, align 8, !dbg !2333
  store i32 0, i32* %1, align 4, !dbg !2334
  %2 = load %struct.uv_interface_address_s**, %struct.uv_interface_address_s*** %addresses.addr, align 8, !dbg !2335
  store %struct.uv_interface_address_s* null, %struct.uv_interface_address_s** %2, align 8, !dbg !2336
  %3 = load %struct.ifaddrs*, %struct.ifaddrs** %addrs, align 8, !dbg !2337
  store %struct.ifaddrs* %3, %struct.ifaddrs** %ent, align 8, !dbg !2339
  br label %for.cond, !dbg !2340

for.cond:                                         ; preds = %for.inc, %if.end
  %4 = load %struct.ifaddrs*, %struct.ifaddrs** %ent, align 8, !dbg !2341
  %cmp = icmp ne %struct.ifaddrs* %4, null, !dbg !2344
  br i1 %cmp, label %for.body, label %for.end, !dbg !2345

for.body:                                         ; preds = %for.cond
  %5 = load %struct.ifaddrs*, %struct.ifaddrs** %ent, align 8, !dbg !2346
  %call2 = call i32 @uv__ifaddr_exclude(%struct.ifaddrs* %5), !dbg !2349
  %tobool3 = icmp ne i32 %call2, 0, !dbg !2349
  br i1 %tobool3, label %if.then4, label %if.end5, !dbg !2350

if.then4:                                         ; preds = %for.body
  br label %for.inc, !dbg !2351

if.end5:                                          ; preds = %for.body
  %6 = load i32*, i32** %count.addr, align 8, !dbg !2352
  %7 = load i32, i32* %6, align 4, !dbg !2353
  %inc = add nsw i32 %7, 1, !dbg !2353
  store i32 %inc, i32* %6, align 4, !dbg !2353
  br label %for.inc, !dbg !2354

for.inc:                                          ; preds = %if.end5, %if.then4
  %8 = load %struct.ifaddrs*, %struct.ifaddrs** %ent, align 8, !dbg !2355
  %ifa_next = getelementptr inbounds %struct.ifaddrs, %struct.ifaddrs* %8, i32 0, i32 0, !dbg !2357
  %9 = load %struct.ifaddrs*, %struct.ifaddrs** %ifa_next, align 8, !dbg !2357
  store %struct.ifaddrs* %9, %struct.ifaddrs** %ent, align 8, !dbg !2358
  br label %for.cond, !dbg !2359

for.end:                                          ; preds = %for.cond
  %10 = load i32*, i32** %count.addr, align 8, !dbg !2360
  %11 = load i32, i32* %10, align 4, !dbg !2362
  %cmp6 = icmp eq i32 %11, 0, !dbg !2363
  br i1 %cmp6, label %if.then7, label %if.end8, !dbg !2364

if.then7:                                         ; preds = %for.end
  store i32 0, i32* %retval, align 4, !dbg !2365
  br label %return, !dbg !2365

if.end8:                                          ; preds = %for.end
  %12 = load i32*, i32** %count.addr, align 8, !dbg !2366
  %13 = load i32, i32* %12, align 4, !dbg !2367
  %conv = sext i32 %13 to i64, !dbg !2367
  %mul = mul i64 %conv, 80, !dbg !2368
  %call9 = call i8* @uv__malloc(i64 %mul), !dbg !2369
  %14 = bitcast i8* %call9 to %struct.uv_interface_address_s*, !dbg !2369
  %15 = load %struct.uv_interface_address_s**, %struct.uv_interface_address_s*** %addresses.addr, align 8, !dbg !2370
  store %struct.uv_interface_address_s* %14, %struct.uv_interface_address_s** %15, align 8, !dbg !2371
  %16 = load %struct.uv_interface_address_s**, %struct.uv_interface_address_s*** %addresses.addr, align 8, !dbg !2372
  %17 = load %struct.uv_interface_address_s*, %struct.uv_interface_address_s** %16, align 8, !dbg !2374
  %tobool10 = icmp ne %struct.uv_interface_address_s* %17, null, !dbg !2375
  br i1 %tobool10, label %if.end12, label %if.then11, !dbg !2376

if.then11:                                        ; preds = %if.end8
  %18 = load %struct.ifaddrs*, %struct.ifaddrs** %addrs, align 8, !dbg !2377
  call void @freeifaddrs(%struct.ifaddrs* %18) #9, !dbg !2379
  store i32 -12, i32* %retval, align 4, !dbg !2380
  br label %return, !dbg !2380

if.end12:                                         ; preds = %if.end8
  %19 = load %struct.uv_interface_address_s**, %struct.uv_interface_address_s*** %addresses.addr, align 8, !dbg !2381
  %20 = load %struct.uv_interface_address_s*, %struct.uv_interface_address_s** %19, align 8, !dbg !2382
  store %struct.uv_interface_address_s* %20, %struct.uv_interface_address_s** %address, align 8, !dbg !2383
  %21 = load %struct.ifaddrs*, %struct.ifaddrs** %addrs, align 8, !dbg !2384
  store %struct.ifaddrs* %21, %struct.ifaddrs** %ent, align 8, !dbg !2386
  br label %for.cond13, !dbg !2387

for.cond13:                                       ; preds = %for.inc43, %if.end12
  %22 = load %struct.ifaddrs*, %struct.ifaddrs** %ent, align 8, !dbg !2388
  %cmp14 = icmp ne %struct.ifaddrs* %22, null, !dbg !2391
  br i1 %cmp14, label %for.body16, label %for.end45, !dbg !2392

for.body16:                                       ; preds = %for.cond13
  %23 = load %struct.ifaddrs*, %struct.ifaddrs** %ent, align 8, !dbg !2393
  %call17 = call i32 @uv__ifaddr_exclude(%struct.ifaddrs* %23), !dbg !2396
  %tobool18 = icmp ne i32 %call17, 0, !dbg !2396
  br i1 %tobool18, label %if.then19, label %if.end20, !dbg !2397

if.then19:                                        ; preds = %for.body16
  br label %for.inc43, !dbg !2398

if.end20:                                         ; preds = %for.body16
  %24 = load %struct.ifaddrs*, %struct.ifaddrs** %ent, align 8, !dbg !2399
  %ifa_name = getelementptr inbounds %struct.ifaddrs, %struct.ifaddrs* %24, i32 0, i32 1, !dbg !2400
  %25 = load i8*, i8** %ifa_name, align 8, !dbg !2400
  %call21 = call i8* @uv__strdup(i8* %25), !dbg !2401
  %26 = load %struct.uv_interface_address_s*, %struct.uv_interface_address_s** %address, align 8, !dbg !2402
  %name = getelementptr inbounds %struct.uv_interface_address_s, %struct.uv_interface_address_s* %26, i32 0, i32 0, !dbg !2403
  store i8* %call21, i8** %name, align 8, !dbg !2404
  %27 = load %struct.ifaddrs*, %struct.ifaddrs** %ent, align 8, !dbg !2405
  %ifa_addr = getelementptr inbounds %struct.ifaddrs, %struct.ifaddrs* %27, i32 0, i32 3, !dbg !2407
  %28 = load %struct.sockaddr*, %struct.sockaddr** %ifa_addr, align 8, !dbg !2407
  %sa_family = getelementptr inbounds %struct.sockaddr, %struct.sockaddr* %28, i32 0, i32 0, !dbg !2408
  %29 = load i16, i16* %sa_family, align 2, !dbg !2408
  %conv22 = zext i16 %29 to i32, !dbg !2405
  %cmp23 = icmp eq i32 %conv22, 10, !dbg !2409
  br i1 %cmp23, label %if.then25, label %if.else, !dbg !2410

if.then25:                                        ; preds = %if.end20
  %30 = load %struct.uv_interface_address_s*, %struct.uv_interface_address_s** %address, align 8, !dbg !2411
  %address26 = getelementptr inbounds %struct.uv_interface_address_s, %struct.uv_interface_address_s* %30, i32 0, i32 3, !dbg !2413
  %address6 = bitcast %union.anon.4* %address26 to %struct.sockaddr_in6*, !dbg !2414
  %31 = load %struct.ifaddrs*, %struct.ifaddrs** %ent, align 8, !dbg !2415
  %ifa_addr27 = getelementptr inbounds %struct.ifaddrs, %struct.ifaddrs* %31, i32 0, i32 3, !dbg !2416
  %32 = load %struct.sockaddr*, %struct.sockaddr** %ifa_addr27, align 8, !dbg !2416
  %33 = bitcast %struct.sockaddr* %32 to %struct.sockaddr_in6*, !dbg !2417
  %34 = bitcast %struct.sockaddr_in6* %address6 to i8*, !dbg !2417
  %35 = bitcast %struct.sockaddr_in6* %33 to i8*, !dbg !2417
  call void @llvm.memcpy.p0i8.p0i8.i64(i8* %34, i8* %35, i64 28, i32 4, i1 false), !dbg !2417
  br label %if.end30, !dbg !2418

if.else:                                          ; preds = %if.end20
  %36 = load %struct.uv_interface_address_s*, %struct.uv_interface_address_s** %address, align 8, !dbg !2419
  %address28 = getelementptr inbounds %struct.uv_interface_address_s, %struct.uv_interface_address_s* %36, i32 0, i32 3, !dbg !2421
  %address4 = bitcast %union.anon.4* %address28 to %struct.sockaddr_in*, !dbg !2422
  %37 = load %struct.ifaddrs*, %struct.ifaddrs** %ent, align 8, !dbg !2423
  %ifa_addr29 = getelementptr inbounds %struct.ifaddrs, %struct.ifaddrs* %37, i32 0, i32 3, !dbg !2424
  %38 = load %struct.sockaddr*, %struct.sockaddr** %ifa_addr29, align 8, !dbg !2424
  %39 = bitcast %struct.sockaddr* %38 to %struct.sockaddr_in*, !dbg !2425
  %40 = bitcast %struct.sockaddr_in* %address4 to i8*, !dbg !2425
  %41 = bitcast %struct.sockaddr_in* %39 to i8*, !dbg !2425
  call void @llvm.memcpy.p0i8.p0i8.i64(i8* %40, i8* %41, i64 16, i32 4, i1 false), !dbg !2425
  br label %if.end30

if.end30:                                         ; preds = %if.else, %if.then25
  %42 = load %struct.ifaddrs*, %struct.ifaddrs** %ent, align 8, !dbg !2426
  %ifa_netmask = getelementptr inbounds %struct.ifaddrs, %struct.ifaddrs* %42, i32 0, i32 4, !dbg !2428
  %43 = load %struct.sockaddr*, %struct.sockaddr** %ifa_netmask, align 8, !dbg !2428
  %sa_family31 = getelementptr inbounds %struct.sockaddr, %struct.sockaddr* %43, i32 0, i32 0, !dbg !2429
  %44 = load i16, i16* %sa_family31, align 2, !dbg !2429
  %conv32 = zext i16 %44 to i32, !dbg !2426
  %cmp33 = icmp eq i32 %conv32, 10, !dbg !2430
  br i1 %cmp33, label %if.then35, label %if.else37, !dbg !2431

if.then35:                                        ; preds = %if.end30
  %45 = load %struct.uv_interface_address_s*, %struct.uv_interface_address_s** %address, align 8, !dbg !2432
  %netmask = getelementptr inbounds %struct.uv_interface_address_s, %struct.uv_interface_address_s* %45, i32 0, i32 4, !dbg !2434
  %netmask6 = bitcast %union.anon.6* %netmask to %struct.sockaddr_in6*, !dbg !2435
  %46 = load %struct.ifaddrs*, %struct.ifaddrs** %ent, align 8, !dbg !2436
  %ifa_netmask36 = getelementptr inbounds %struct.ifaddrs, %struct.ifaddrs* %46, i32 0, i32 4, !dbg !2437
  %47 = load %struct.sockaddr*, %struct.sockaddr** %ifa_netmask36, align 8, !dbg !2437
  %48 = bitcast %struct.sockaddr* %47 to %struct.sockaddr_in6*, !dbg !2438
  %49 = bitcast %struct.sockaddr_in6* %netmask6 to i8*, !dbg !2438
  %50 = bitcast %struct.sockaddr_in6* %48 to i8*, !dbg !2438
  call void @llvm.memcpy.p0i8.p0i8.i64(i8* %49, i8* %50, i64 28, i32 4, i1 false), !dbg !2438
  br label %if.end40, !dbg !2439

if.else37:                                        ; preds = %if.end30
  %51 = load %struct.uv_interface_address_s*, %struct.uv_interface_address_s** %address, align 8, !dbg !2440
  %netmask38 = getelementptr inbounds %struct.uv_interface_address_s, %struct.uv_interface_address_s* %51, i32 0, i32 4, !dbg !2442
  %netmask4 = bitcast %union.anon.6* %netmask38 to %struct.sockaddr_in*, !dbg !2443
  %52 = load %struct.ifaddrs*, %struct.ifaddrs** %ent, align 8, !dbg !2444
  %ifa_netmask39 = getelementptr inbounds %struct.ifaddrs, %struct.ifaddrs* %52, i32 0, i32 4, !dbg !2445
  %53 = load %struct.sockaddr*, %struct.sockaddr** %ifa_netmask39, align 8, !dbg !2445
  %54 = bitcast %struct.sockaddr* %53 to %struct.sockaddr_in*, !dbg !2446
  %55 = bitcast %struct.sockaddr_in* %netmask4 to i8*, !dbg !2446
  %56 = bitcast %struct.sockaddr_in* %54 to i8*, !dbg !2446
  call void @llvm.memcpy.p0i8.p0i8.i64(i8* %55, i8* %56, i64 16, i32 4, i1 false), !dbg !2446
  br label %if.end40

if.end40:                                         ; preds = %if.else37, %if.then35
  %57 = load %struct.ifaddrs*, %struct.ifaddrs** %ent, align 8, !dbg !2447
  %ifa_flags = getelementptr inbounds %struct.ifaddrs, %struct.ifaddrs* %57, i32 0, i32 2, !dbg !2448
  %58 = load i32, i32* %ifa_flags, align 8, !dbg !2448
  %and = and i32 %58, 8, !dbg !2449
  %tobool41 = icmp ne i32 %and, 0, !dbg !2450
  %lnot = xor i1 %tobool41, true, !dbg !2450
  %lnot42 = xor i1 %lnot, true, !dbg !2451
  %lnot.ext = zext i1 %lnot42 to i32, !dbg !2451
  %59 = load %struct.uv_interface_address_s*, %struct.uv_interface_address_s** %address, align 8, !dbg !2452
  %is_internal = getelementptr inbounds %struct.uv_interface_address_s, %struct.uv_interface_address_s* %59, i32 0, i32 2, !dbg !2453
  store i32 %lnot.ext, i32* %is_internal, align 8, !dbg !2454
  %60 = load %struct.uv_interface_address_s*, %struct.uv_interface_address_s** %address, align 8, !dbg !2455
  %incdec.ptr = getelementptr inbounds %struct.uv_interface_address_s, %struct.uv_interface_address_s* %60, i32 1, !dbg !2455
  store %struct.uv_interface_address_s* %incdec.ptr, %struct.uv_interface_address_s** %address, align 8, !dbg !2455
  br label %for.inc43, !dbg !2456

for.inc43:                                        ; preds = %if.end40, %if.then19
  %61 = load %struct.ifaddrs*, %struct.ifaddrs** %ent, align 8, !dbg !2457
  %ifa_next44 = getelementptr inbounds %struct.ifaddrs, %struct.ifaddrs* %61, i32 0, i32 0, !dbg !2459
  %62 = load %struct.ifaddrs*, %struct.ifaddrs** %ifa_next44, align 8, !dbg !2459
  store %struct.ifaddrs* %62, %struct.ifaddrs** %ent, align 8, !dbg !2460
  br label %for.cond13, !dbg !2461

for.end45:                                        ; preds = %for.cond13
  %63 = load %struct.ifaddrs*, %struct.ifaddrs** %addrs, align 8, !dbg !2462
  store %struct.ifaddrs* %63, %struct.ifaddrs** %ent, align 8, !dbg !2464
  br label %for.cond46, !dbg !2465

for.cond46:                                       ; preds = %for.inc71, %for.end45
  %64 = load %struct.ifaddrs*, %struct.ifaddrs** %ent, align 8, !dbg !2466
  %cmp47 = icmp ne %struct.ifaddrs* %64, null, !dbg !2469
  br i1 %cmp47, label %for.body49, label %for.end73, !dbg !2470

for.body49:                                       ; preds = %for.cond46
  %65 = load %struct.ifaddrs*, %struct.ifaddrs** %ent, align 8, !dbg !2471
  %call50 = call i32 @uv__ifaddr_exclude(%struct.ifaddrs* %65), !dbg !2474
  %tobool51 = icmp ne i32 %call50, 0, !dbg !2474
  br i1 %tobool51, label %if.then52, label %if.end53, !dbg !2475

if.then52:                                        ; preds = %for.body49
  br label %for.inc71, !dbg !2476

if.end53:                                         ; preds = %for.body49
  %66 = load %struct.uv_interface_address_s**, %struct.uv_interface_address_s*** %addresses.addr, align 8, !dbg !2477
  %67 = load %struct.uv_interface_address_s*, %struct.uv_interface_address_s** %66, align 8, !dbg !2478
  store %struct.uv_interface_address_s* %67, %struct.uv_interface_address_s** %address, align 8, !dbg !2479
  store i32 0, i32* %i, align 4, !dbg !2480
  br label %for.cond54, !dbg !2482

for.cond54:                                       ; preds = %for.inc68, %if.end53
  %68 = load i32, i32* %i, align 4, !dbg !2483
  %69 = load i32*, i32** %count.addr, align 8, !dbg !2486
  %70 = load i32, i32* %69, align 4, !dbg !2487
  %cmp55 = icmp slt i32 %68, %70, !dbg !2488
  br i1 %cmp55, label %for.body57, label %for.end70, !dbg !2489

for.body57:                                       ; preds = %for.cond54
  %71 = load %struct.uv_interface_address_s*, %struct.uv_interface_address_s** %address, align 8, !dbg !2490
  %name58 = getelementptr inbounds %struct.uv_interface_address_s, %struct.uv_interface_address_s* %71, i32 0, i32 0, !dbg !2493
  %72 = load i8*, i8** %name58, align 8, !dbg !2493
  %73 = load %struct.ifaddrs*, %struct.ifaddrs** %ent, align 8, !dbg !2494
  %ifa_name59 = getelementptr inbounds %struct.ifaddrs, %struct.ifaddrs* %73, i32 0, i32 1, !dbg !2495
  %74 = load i8*, i8** %ifa_name59, align 8, !dbg !2495
  %call60 = call i32 @strcmp(i8* %72, i8* %74) #10, !dbg !2496
  %cmp61 = icmp eq i32 %call60, 0, !dbg !2497
  br i1 %cmp61, label %if.then63, label %if.end66, !dbg !2498

if.then63:                                        ; preds = %for.body57
  %75 = load %struct.ifaddrs*, %struct.ifaddrs** %ent, align 8, !dbg !2499
  %ifa_addr64 = getelementptr inbounds %struct.ifaddrs, %struct.ifaddrs* %75, i32 0, i32 3, !dbg !2501
  %76 = load %struct.sockaddr*, %struct.sockaddr** %ifa_addr64, align 8, !dbg !2501
  %77 = bitcast %struct.sockaddr* %76 to %struct.sockaddr_ll*, !dbg !2502
  store %struct.sockaddr_ll* %77, %struct.sockaddr_ll** %sll, align 8, !dbg !2503
  %78 = load %struct.uv_interface_address_s*, %struct.uv_interface_address_s** %address, align 8, !dbg !2504
  %phys_addr = getelementptr inbounds %struct.uv_interface_address_s, %struct.uv_interface_address_s* %78, i32 0, i32 1, !dbg !2505
  %arraydecay = getelementptr inbounds [6 x i8], [6 x i8]* %phys_addr, i32 0, i32 0, !dbg !2506
  %79 = load %struct.sockaddr_ll*, %struct.sockaddr_ll** %sll, align 8, !dbg !2507
  %sll_addr = getelementptr inbounds %struct.sockaddr_ll, %struct.sockaddr_ll* %79, i32 0, i32 6, !dbg !2508
  %arraydecay65 = getelementptr inbounds [8 x i8], [8 x i8]* %sll_addr, i32 0, i32 0, !dbg !2506
  call void @llvm.memcpy.p0i8.p0i8.i64(i8* %arraydecay, i8* %arraydecay65, i64 6, i32 4, i1 false), !dbg !2506
  br label %if.end66, !dbg !2509

if.end66:                                         ; preds = %if.then63, %for.body57
  %80 = load %struct.uv_interface_address_s*, %struct.uv_interface_address_s** %address, align 8, !dbg !2510
  %incdec.ptr67 = getelementptr inbounds %struct.uv_interface_address_s, %struct.uv_interface_address_s* %80, i32 1, !dbg !2510
  store %struct.uv_interface_address_s* %incdec.ptr67, %struct.uv_interface_address_s** %address, align 8, !dbg !2510
  br label %for.inc68, !dbg !2511

for.inc68:                                        ; preds = %if.end66
  %81 = load i32, i32* %i, align 4, !dbg !2512
  %inc69 = add nsw i32 %81, 1, !dbg !2512
  store i32 %inc69, i32* %i, align 4, !dbg !2512
  br label %for.cond54, !dbg !2514

for.end70:                                        ; preds = %for.cond54
  br label %for.inc71, !dbg !2515

for.inc71:                                        ; preds = %for.end70, %if.then52
  %82 = load %struct.ifaddrs*, %struct.ifaddrs** %ent, align 8, !dbg !2516
  %ifa_next72 = getelementptr inbounds %struct.ifaddrs, %struct.ifaddrs* %82, i32 0, i32 0, !dbg !2518
  %83 = load %struct.ifaddrs*, %struct.ifaddrs** %ifa_next72, align 8, !dbg !2518
  store %struct.ifaddrs* %83, %struct.ifaddrs** %ent, align 8, !dbg !2519
  br label %for.cond46, !dbg !2520

for.end73:                                        ; preds = %for.cond46
  %84 = load %struct.ifaddrs*, %struct.ifaddrs** %addrs, align 8, !dbg !2521
  call void @freeifaddrs(%struct.ifaddrs* %84) #9, !dbg !2522
  store i32 0, i32* %retval, align 4, !dbg !2523
  br label %return, !dbg !2523

return:                                           ; preds = %for.end73, %if.then11, %if.then7, %if.then
  %85 = load i32, i32* %retval, align 4, !dbg !2524
  ret i32 %85, !dbg !2524
}

; Function Attrs: nounwind
declare i32 @getifaddrs(%struct.ifaddrs**) #6

; Function Attrs: nounwind uwtable
define internal i32 @uv__ifaddr_exclude(%struct.ifaddrs* %ent) #0 !dbg !712 {
entry:
  %retval = alloca i32, align 4
  %ent.addr = alloca %struct.ifaddrs*, align 8
  store %struct.ifaddrs* %ent, %struct.ifaddrs** %ent.addr, align 8
  call void @llvm.dbg.declare(metadata %struct.ifaddrs** %ent.addr, metadata !2525, metadata !760), !dbg !2526
  %0 = load %struct.ifaddrs*, %struct.ifaddrs** %ent.addr, align 8, !dbg !2527
  %ifa_flags = getelementptr inbounds %struct.ifaddrs, %struct.ifaddrs* %0, i32 0, i32 2, !dbg !2529
  %1 = load i32, i32* %ifa_flags, align 8, !dbg !2529
  %and = and i32 %1, 1, !dbg !2530
  %tobool = icmp ne i32 %and, 0, !dbg !2530
  br i1 %tobool, label %land.lhs.true, label %if.then, !dbg !2531

land.lhs.true:                                    ; preds = %entry
  %2 = load %struct.ifaddrs*, %struct.ifaddrs** %ent.addr, align 8, !dbg !2532
  %ifa_flags1 = getelementptr inbounds %struct.ifaddrs, %struct.ifaddrs* %2, i32 0, i32 2, !dbg !2534
  %3 = load i32, i32* %ifa_flags1, align 8, !dbg !2534
  %and2 = and i32 %3, 64, !dbg !2535
  %tobool3 = icmp ne i32 %and2, 0, !dbg !2535
  br i1 %tobool3, label %if.end, label %if.then, !dbg !2536

if.then:                                          ; preds = %land.lhs.true, %entry
  store i32 1, i32* %retval, align 4, !dbg !2537
  br label %return, !dbg !2537

if.end:                                           ; preds = %land.lhs.true
  %4 = load %struct.ifaddrs*, %struct.ifaddrs** %ent.addr, align 8, !dbg !2538
  %ifa_addr = getelementptr inbounds %struct.ifaddrs, %struct.ifaddrs* %4, i32 0, i32 3, !dbg !2540
  %5 = load %struct.sockaddr*, %struct.sockaddr** %ifa_addr, align 8, !dbg !2540
  %cmp = icmp eq %struct.sockaddr* %5, null, !dbg !2541
  br i1 %cmp, label %if.then4, label %if.end5, !dbg !2542

if.then4:                                         ; preds = %if.end
  store i32 1, i32* %retval, align 4, !dbg !2543
  br label %return, !dbg !2543

if.end5:                                          ; preds = %if.end
  %6 = load %struct.ifaddrs*, %struct.ifaddrs** %ent.addr, align 8, !dbg !2544
  %ifa_addr6 = getelementptr inbounds %struct.ifaddrs, %struct.ifaddrs* %6, i32 0, i32 3, !dbg !2546
  %7 = load %struct.sockaddr*, %struct.sockaddr** %ifa_addr6, align 8, !dbg !2546
  %sa_family = getelementptr inbounds %struct.sockaddr, %struct.sockaddr* %7, i32 0, i32 0, !dbg !2547
  %8 = load i16, i16* %sa_family, align 2, !dbg !2547
  %conv = zext i16 %8 to i32, !dbg !2544
  %cmp7 = icmp eq i32 %conv, 17, !dbg !2548
  br i1 %cmp7, label %if.then9, label %if.end10, !dbg !2549

if.then9:                                         ; preds = %if.end5
  store i32 1, i32* %retval, align 4, !dbg !2550
  br label %return, !dbg !2550

if.end10:                                         ; preds = %if.end5
  store i32 0, i32* %retval, align 4, !dbg !2551
  br label %return, !dbg !2551

return:                                           ; preds = %if.end10, %if.then9, %if.then4, %if.then
  %9 = load i32, i32* %retval, align 4, !dbg !2552
  ret i32 %9, !dbg !2552
}

declare i8* @uv__malloc(i64) #2

; Function Attrs: nounwind
declare void @freeifaddrs(%struct.ifaddrs*) #6

declare i8* @uv__strdup(i8*) #2

; Function Attrs: argmemonly nounwind
declare void @llvm.memcpy.p0i8.p0i8.i64(i8* nocapture, i8* nocapture readonly, i64, i32, i1) #5

; Function Attrs: nounwind readonly
declare i32 @strcmp(i8*, i8*) #7

; Function Attrs: nounwind uwtable
define void @uv_free_interface_addresses(%struct.uv_interface_address_s* %addresses, i32 %count) #0 !dbg !633 {
entry:
  %addresses.addr = alloca %struct.uv_interface_address_s*, align 8
  %count.addr = alloca i32, align 4
  %i = alloca i32, align 4
  store %struct.uv_interface_address_s* %addresses, %struct.uv_interface_address_s** %addresses.addr, align 8
  call void @llvm.dbg.declare(metadata %struct.uv_interface_address_s** %addresses.addr, metadata !2553, metadata !760), !dbg !2554
  store i32 %count, i32* %count.addr, align 4
  call void @llvm.dbg.declare(metadata i32* %count.addr, metadata !2555, metadata !760), !dbg !2556
  call void @llvm.dbg.declare(metadata i32* %i, metadata !2557, metadata !760), !dbg !2558
  store i32 0, i32* %i, align 4, !dbg !2559
  br label %for.cond, !dbg !2561

for.cond:                                         ; preds = %for.inc, %entry
  %0 = load i32, i32* %i, align 4, !dbg !2562
  %1 = load i32, i32* %count.addr, align 4, !dbg !2565
  %cmp = icmp slt i32 %0, %1, !dbg !2566
  br i1 %cmp, label %for.body, label %for.end, !dbg !2567

for.body:                                         ; preds = %for.cond
  %2 = load i32, i32* %i, align 4, !dbg !2568
  %idxprom = sext i32 %2 to i64, !dbg !2570
  %3 = load %struct.uv_interface_address_s*, %struct.uv_interface_address_s** %addresses.addr, align 8, !dbg !2570
  %arrayidx = getelementptr inbounds %struct.uv_interface_address_s, %struct.uv_interface_address_s* %3, i64 %idxprom, !dbg !2570
  %name = getelementptr inbounds %struct.uv_interface_address_s, %struct.uv_interface_address_s* %arrayidx, i32 0, i32 0, !dbg !2571
  %4 = load i8*, i8** %name, align 8, !dbg !2571
  call void @uv__free(i8* %4), !dbg !2572
  br label %for.inc, !dbg !2573

for.inc:                                          ; preds = %for.body
  %5 = load i32, i32* %i, align 4, !dbg !2574
  %inc = add nsw i32 %5, 1, !dbg !2574
  store i32 %inc, i32* %i, align 4, !dbg !2574
  br label %for.cond, !dbg !2576

for.end:                                          ; preds = %for.cond
  %6 = load %struct.uv_interface_address_s*, %struct.uv_interface_address_s** %addresses.addr, align 8, !dbg !2577
  %7 = bitcast %struct.uv_interface_address_s* %6 to i8*, !dbg !2577
  call void @uv__free(i8* %7), !dbg !2578
  ret void, !dbg !2579
}

; Function Attrs: nounwind uwtable
define void @uv__set_process_title(i8* %title) #0 !dbg !636 {
entry:
  %title.addr = alloca i8*, align 8
  store i8* %title, i8** %title.addr, align 8
  call void @llvm.dbg.declare(metadata i8** %title.addr, metadata !2580, metadata !760), !dbg !2581
  %0 = load i8*, i8** %title.addr, align 8, !dbg !2582
  %call = call i32 (i32, ...) @prctl(i32 15, i8* %0) #9, !dbg !2583
  ret void, !dbg !2584
}

; Function Attrs: nounwind
declare i32 @prctl(i32, ...) #6

declare i8* @fgets(i8*, i32, %struct._IO_FILE*) #2

; Function Attrs: nounwind readonly
declare i32 @strncmp(i8*, i8*, i64) #7

; Function Attrs: nounwind uwtable
define internal i64 @read_cpufreq(i32 %cpunum) #0 !dbg !703 {
entry:
  %retval = alloca i64, align 8
  %cpunum.addr = alloca i32, align 4
  %val = alloca i64, align 8
  %buf = alloca [1024 x i8], align 16
  %fp = alloca %struct._IO_FILE*, align 8
  store i32 %cpunum, i32* %cpunum.addr, align 4
  call void @llvm.dbg.declare(metadata i32* %cpunum.addr, metadata !2585, metadata !760), !dbg !2586
  call void @llvm.dbg.declare(metadata i64* %val, metadata !2587, metadata !760), !dbg !2588
  call void @llvm.dbg.declare(metadata [1024 x i8]* %buf, metadata !2589, metadata !760), !dbg !2590
  call void @llvm.dbg.declare(metadata %struct._IO_FILE** %fp, metadata !2591, metadata !760), !dbg !2592
  %arraydecay = getelementptr inbounds [1024 x i8], [1024 x i8]* %buf, i32 0, i32 0, !dbg !2593
  %0 = load i32, i32* %cpunum.addr, align 4, !dbg !2594
  %call = call i32 (i8*, i64, i8*, ...) @snprintf(i8* %arraydecay, i64 1024, i8* getelementptr inbounds ([55 x i8], [55 x i8]* @.str.17, i32 0, i32 0), i32 %0) #9, !dbg !2595
  %arraydecay1 = getelementptr inbounds [1024 x i8], [1024 x i8]* %buf, i32 0, i32 0, !dbg !2596
  %call2 = call %struct._IO_FILE* @uv__open_file(i8* %arraydecay1), !dbg !2597
  store %struct._IO_FILE* %call2, %struct._IO_FILE** %fp, align 8, !dbg !2598
  %1 = load %struct._IO_FILE*, %struct._IO_FILE** %fp, align 8, !dbg !2599
  %cmp = icmp eq %struct._IO_FILE* %1, null, !dbg !2601
  br i1 %cmp, label %if.then, label %if.end, !dbg !2602

if.then:                                          ; preds = %entry
  store i64 0, i64* %retval, align 8, !dbg !2603
  br label %return, !dbg !2603

if.end:                                           ; preds = %entry
  %2 = load %struct._IO_FILE*, %struct._IO_FILE** %fp, align 8, !dbg !2604
  %call3 = call i32 (%struct._IO_FILE*, i8*, ...) @fscanf(%struct._IO_FILE* %2, i8* getelementptr inbounds ([4 x i8], [4 x i8]* @.str.18, i32 0, i32 0), i64* %val), !dbg !2606
  %cmp4 = icmp ne i32 %call3, 1, !dbg !2607
  br i1 %cmp4, label %if.then5, label %if.end6, !dbg !2608

if.then5:                                         ; preds = %if.end
  store i64 0, i64* %val, align 8, !dbg !2609
  br label %if.end6, !dbg !2610

if.end6:                                          ; preds = %if.then5, %if.end
  %3 = load %struct._IO_FILE*, %struct._IO_FILE** %fp, align 8, !dbg !2611
  %call7 = call i32 @fclose(%struct._IO_FILE* %3), !dbg !2612
  %4 = load i64, i64* %val, align 8, !dbg !2613
  store i64 %4, i64* %retval, align 8, !dbg !2614
  br label %return, !dbg !2614

return:                                           ; preds = %if.end6, %if.then
  %5 = load i64, i64* %retval, align 8, !dbg !2615
  ret i64 %5, !dbg !2615
}

; Function Attrs: nounwind
declare i32 @snprintf(i8*, i64, i8*, ...) #6

declare i32 @fscanf(%struct._IO_FILE*, i8*, ...) #2

declare i8* @uv__strndup(i8*, i64) #2

; Function Attrs: nounwind readonly
declare i64 @strlen(i8*) #7

; Function Attrs: nounwind readonly
declare i32 @atoi(i8*) #7

; Function Attrs: nounwind
declare i64 @sysconf(i32) #6

declare void @rewind(%struct._IO_FILE*) #2

; Function Attrs: nounwind
declare i32 @sscanf(i8*, i8*, ...) #6

attributes #0 = { nounwind uwtable "disable-tail-calls"="false" "less-precise-fpmad"="false" "no-frame-pointer-elim"="true" "no-frame-pointer-elim-non-leaf" "no-infs-fp-math"="false" "no-nans-fp-math"="false" "stack-protector-buffer-size"="8" "target-cpu"="x86-64" "target-features"="+fxsr,+mmx,+sse,+sse2" "unsafe-fp-math"="false" "use-soft-float"="false" }
attributes #1 = { nounwind readnone }
attributes #2 = { "disable-tail-calls"="false" "less-precise-fpmad"="false" "no-frame-pointer-elim"="true" "no-frame-pointer-elim-non-leaf" "no-infs-fp-math"="false" "no-nans-fp-math"="false" "stack-protector-buffer-size"="8" "target-cpu"="x86-64" "target-features"="+fxsr,+mmx,+sse,+sse2" "unsafe-fp-math"="false" "use-soft-float"="false" }
attributes #3 = { nounwind readnone "disable-tail-calls"="false" "less-precise-fpmad"="false" "no-frame-pointer-elim"="true" "no-frame-pointer-elim-non-leaf" "no-infs-fp-math"="false" "no-nans-fp-math"="false" "stack-protector-buffer-size"="8" "target-cpu"="x86-64" "target-features"="+fxsr,+mmx,+sse,+sse2" "unsafe-fp-math"="false" "use-soft-float"="false" }
attributes #4 = { noreturn nounwind "disable-tail-calls"="false" "less-precise-fpmad"="false" "no-frame-pointer-elim"="true" "no-frame-pointer-elim-non-leaf" "no-infs-fp-math"="false" "no-nans-fp-math"="false" "stack-protector-buffer-size"="8" "target-cpu"="x86-64" "target-features"="+fxsr,+mmx,+sse,+sse2" "unsafe-fp-math"="false" "use-soft-float"="false" }
attributes #5 = { argmemonly nounwind }
attributes #6 = { nounwind "disable-tail-calls"="false" "less-precise-fpmad"="false" "no-frame-pointer-elim"="true" "no-frame-pointer-elim-non-leaf" "no-infs-fp-math"="false" "no-nans-fp-math"="false" "stack-protector-buffer-size"="8" "target-cpu"="x86-64" "target-features"="+fxsr,+mmx,+sse,+sse2" "unsafe-fp-math"="false" "use-soft-float"="false" }
attributes #7 = { nounwind readonly "disable-tail-calls"="false" "less-precise-fpmad"="false" "no-frame-pointer-elim"="true" "no-frame-pointer-elim-non-leaf" "no-infs-fp-math"="false" "no-nans-fp-math"="false" "stack-protector-buffer-size"="8" "target-cpu"="x86-64" "target-features"="+fxsr,+mmx,+sse,+sse2" "unsafe-fp-math"="false" "use-soft-float"="false" }
attributes #8 = { noreturn nounwind }
attributes #9 = { nounwind }
attributes #10 = { nounwind readonly }

!llvm.dbg.cu = !{!0}
!llvm.module.flags = !{!756, !757}
!llvm.ident = !{!758}

!0 = distinct !DICompileUnit(language: DW_LANG_C99, file: !1, producer: "clang version 3.8.0 (tags/RELEASE_380/final)", isOptimized: false, runtimeVersion: 0, emissionKind: 1, enums: !2, retainedTypes: !270, subprograms: !547, globals: !739)
!1 = !DIFile(filename: "/data/download/cmake/cmake-master/Utilities/cmlibuv/src/unix/linux-core.c", directory: "/data/download/cmake/cmake-master/Utilities/cmlibuv")
!2 = !{!3, !25, !29, !33, !52}
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
!25 = !DICompositeType(tag: DW_TAG_enumeration_type, file: !26, line: 144, size: 32, align: 32, elements: !27)
!26 = !DIFile(filename: "/data/download/cmake/cmake-master/Utilities/cmlibuv/src/unix/internal.h", directory: "/data/download/cmake/cmake-master/Utilities/cmlibuv")
!27 = !{!28}
!28 = !DIEnumerator(name: "UV_LOOP_BLOCK_SIGPROF", value: 1)
!29 = !DICompositeType(tag: DW_TAG_enumeration_type, file: !26, line: 148, size: 32, align: 32, elements: !30)
!30 = !{!31, !32}
!31 = !DIEnumerator(name: "UV_CLOCK_PRECISE", value: 0)
!32 = !DIEnumerator(name: "UV_CLOCK_FAST", value: 1)
!33 = !DICompositeType(tag: DW_TAG_enumeration_type, file: !34, line: 42, size: 32, align: 32, elements: !35)
!34 = !DIFile(filename: "/usr/include/net/if.h", directory: "/data/download/cmake/cmake-master/Utilities/cmlibuv")
!35 = !{!36, !37, !38, !39, !40, !41, !42, !43, !44, !45, !46, !47, !48, !49, !50, !51}
!36 = !DIEnumerator(name: "IFF_UP", value: 1)
!37 = !DIEnumerator(name: "IFF_BROADCAST", value: 2)
!38 = !DIEnumerator(name: "IFF_DEBUG", value: 4)
!39 = !DIEnumerator(name: "IFF_LOOPBACK", value: 8)
!40 = !DIEnumerator(name: "IFF_POINTOPOINT", value: 16)
!41 = !DIEnumerator(name: "IFF_NOTRAILERS", value: 32)
!42 = !DIEnumerator(name: "IFF_RUNNING", value: 64)
!43 = !DIEnumerator(name: "IFF_NOARP", value: 128)
!44 = !DIEnumerator(name: "IFF_PROMISC", value: 256)
!45 = !DIEnumerator(name: "IFF_ALLMULTI", value: 512)
!46 = !DIEnumerator(name: "IFF_MASTER", value: 1024)
!47 = !DIEnumerator(name: "IFF_SLAVE", value: 2048)
!48 = !DIEnumerator(name: "IFF_MULTICAST", value: 4096)
!49 = !DIEnumerator(name: "IFF_PORTSEL", value: 8192)
!50 = !DIEnumerator(name: "IFF_AUTOMEDIA", value: 16384)
!51 = !DIEnumerator(name: "IFF_DYNAMIC", value: 32768)
!52 = !DICompositeType(tag: DW_TAG_enumeration_type, file: !53, line: 71, size: 32, align: 32, elements: !54)
!53 = !DIFile(filename: "/usr/include/x86_64-linux-gnu/bits/confname.h", directory: "/data/download/cmake/cmake-master/Utilities/cmlibuv")
!54 = !{!55, !56, !57, !58, !59, !60, !61, !62, !63, !64, !65, !66, !67, !68, !69, !70, !71, !72, !73, !74, !75, !76, !77, !78, !79, !80, !81, !82, !83, !84, !85, !86, !87, !88, !89, !90, !91, !92, !93, !94, !95, !96, !97, !98, !99, !100, !101, !102, !103, !104, !105, !106, !107, !108, !109, !110, !111, !112, !113, !114, !115, !116, !117, !118, !119, !120, !121, !122, !123, !124, !125, !126, !127, !128, !129, !130, !131, !132, !133, !134, !135, !136, !137, !138, !139, !140, !141, !142, !143, !144, !145, !146, !147, !148, !149, !150, !151, !152, !153, !154, !155, !156, !157, !158, !159, !160, !161, !162, !163, !164, !165, !166, !167, !168, !169, !170, !171, !172, !173, !174, !175, !176, !177, !178, !179, !180, !181, !182, !183, !184, !185, !186, !187, !188, !189, !190, !191, !192, !193, !194, !195, !196, !197, !198, !199, !200, !201, !202, !203, !204, !205, !206, !207, !208, !209, !210, !211, !212, !213, !214, !215, !216, !217, !218, !219, !220, !221, !222, !223, !224, !225, !226, !227, !228, !229, !230, !231, !232, !233, !234, !235, !236, !237, !238, !239, !240, !241, !242, !243, !244, !245, !246, !247, !248, !249, !250, !251, !252, !253, !254, !255, !256, !257, !258, !259, !260, !261, !262, !263, !264, !265, !266, !267, !268, !269}
!55 = !DIEnumerator(name: "_SC_ARG_MAX", value: 0)
!56 = !DIEnumerator(name: "_SC_CHILD_MAX", value: 1)
!57 = !DIEnumerator(name: "_SC_CLK_TCK", value: 2)
!58 = !DIEnumerator(name: "_SC_NGROUPS_MAX", value: 3)
!59 = !DIEnumerator(name: "_SC_OPEN_MAX", value: 4)
!60 = !DIEnumerator(name: "_SC_STREAM_MAX", value: 5)
!61 = !DIEnumerator(name: "_SC_TZNAME_MAX", value: 6)
!62 = !DIEnumerator(name: "_SC_JOB_CONTROL", value: 7)
!63 = !DIEnumerator(name: "_SC_SAVED_IDS", value: 8)
!64 = !DIEnumerator(name: "_SC_REALTIME_SIGNALS", value: 9)
!65 = !DIEnumerator(name: "_SC_PRIORITY_SCHEDULING", value: 10)
!66 = !DIEnumerator(name: "_SC_TIMERS", value: 11)
!67 = !DIEnumerator(name: "_SC_ASYNCHRONOUS_IO", value: 12)
!68 = !DIEnumerator(name: "_SC_PRIORITIZED_IO", value: 13)
!69 = !DIEnumerator(name: "_SC_SYNCHRONIZED_IO", value: 14)
!70 = !DIEnumerator(name: "_SC_FSYNC", value: 15)
!71 = !DIEnumerator(name: "_SC_MAPPED_FILES", value: 16)
!72 = !DIEnumerator(name: "_SC_MEMLOCK", value: 17)
!73 = !DIEnumerator(name: "_SC_MEMLOCK_RANGE", value: 18)
!74 = !DIEnumerator(name: "_SC_MEMORY_PROTECTION", value: 19)
!75 = !DIEnumerator(name: "_SC_MESSAGE_PASSING", value: 20)
!76 = !DIEnumerator(name: "_SC_SEMAPHORES", value: 21)
!77 = !DIEnumerator(name: "_SC_SHARED_MEMORY_OBJECTS", value: 22)
!78 = !DIEnumerator(name: "_SC_AIO_LISTIO_MAX", value: 23)
!79 = !DIEnumerator(name: "_SC_AIO_MAX", value: 24)
!80 = !DIEnumerator(name: "_SC_AIO_PRIO_DELTA_MAX", value: 25)
!81 = !DIEnumerator(name: "_SC_DELAYTIMER_MAX", value: 26)
!82 = !DIEnumerator(name: "_SC_MQ_OPEN_MAX", value: 27)
!83 = !DIEnumerator(name: "_SC_MQ_PRIO_MAX", value: 28)
!84 = !DIEnumerator(name: "_SC_VERSION", value: 29)
!85 = !DIEnumerator(name: "_SC_PAGESIZE", value: 30)
!86 = !DIEnumerator(name: "_SC_RTSIG_MAX", value: 31)
!87 = !DIEnumerator(name: "_SC_SEM_NSEMS_MAX", value: 32)
!88 = !DIEnumerator(name: "_SC_SEM_VALUE_MAX", value: 33)
!89 = !DIEnumerator(name: "_SC_SIGQUEUE_MAX", value: 34)
!90 = !DIEnumerator(name: "_SC_TIMER_MAX", value: 35)
!91 = !DIEnumerator(name: "_SC_BC_BASE_MAX", value: 36)
!92 = !DIEnumerator(name: "_SC_BC_DIM_MAX", value: 37)
!93 = !DIEnumerator(name: "_SC_BC_SCALE_MAX", value: 38)
!94 = !DIEnumerator(name: "_SC_BC_STRING_MAX", value: 39)
!95 = !DIEnumerator(name: "_SC_COLL_WEIGHTS_MAX", value: 40)
!96 = !DIEnumerator(name: "_SC_EQUIV_CLASS_MAX", value: 41)
!97 = !DIEnumerator(name: "_SC_EXPR_NEST_MAX", value: 42)
!98 = !DIEnumerator(name: "_SC_LINE_MAX", value: 43)
!99 = !DIEnumerator(name: "_SC_RE_DUP_MAX", value: 44)
!100 = !DIEnumerator(name: "_SC_CHARCLASS_NAME_MAX", value: 45)
!101 = !DIEnumerator(name: "_SC_2_VERSION", value: 46)
!102 = !DIEnumerator(name: "_SC_2_C_BIND", value: 47)
!103 = !DIEnumerator(name: "_SC_2_C_DEV", value: 48)
!104 = !DIEnumerator(name: "_SC_2_FORT_DEV", value: 49)
!105 = !DIEnumerator(name: "_SC_2_FORT_RUN", value: 50)
!106 = !DIEnumerator(name: "_SC_2_SW_DEV", value: 51)
!107 = !DIEnumerator(name: "_SC_2_LOCALEDEF", value: 52)
!108 = !DIEnumerator(name: "_SC_PII", value: 53)
!109 = !DIEnumerator(name: "_SC_PII_XTI", value: 54)
!110 = !DIEnumerator(name: "_SC_PII_SOCKET", value: 55)
!111 = !DIEnumerator(name: "_SC_PII_INTERNET", value: 56)
!112 = !DIEnumerator(name: "_SC_PII_OSI", value: 57)
!113 = !DIEnumerator(name: "_SC_POLL", value: 58)
!114 = !DIEnumerator(name: "_SC_SELECT", value: 59)
!115 = !DIEnumerator(name: "_SC_UIO_MAXIOV", value: 60)
!116 = !DIEnumerator(name: "_SC_IOV_MAX", value: 60)
!117 = !DIEnumerator(name: "_SC_PII_INTERNET_STREAM", value: 61)
!118 = !DIEnumerator(name: "_SC_PII_INTERNET_DGRAM", value: 62)
!119 = !DIEnumerator(name: "_SC_PII_OSI_COTS", value: 63)
!120 = !DIEnumerator(name: "_SC_PII_OSI_CLTS", value: 64)
!121 = !DIEnumerator(name: "_SC_PII_OSI_M", value: 65)
!122 = !DIEnumerator(name: "_SC_T_IOV_MAX", value: 66)
!123 = !DIEnumerator(name: "_SC_THREADS", value: 67)
!124 = !DIEnumerator(name: "_SC_THREAD_SAFE_FUNCTIONS", value: 68)
!125 = !DIEnumerator(name: "_SC_GETGR_R_SIZE_MAX", value: 69)
!126 = !DIEnumerator(name: "_SC_GETPW_R_SIZE_MAX", value: 70)
!127 = !DIEnumerator(name: "_SC_LOGIN_NAME_MAX", value: 71)
!128 = !DIEnumerator(name: "_SC_TTY_NAME_MAX", value: 72)
!129 = !DIEnumerator(name: "_SC_THREAD_DESTRUCTOR_ITERATIONS", value: 73)
!130 = !DIEnumerator(name: "_SC_THREAD_KEYS_MAX", value: 74)
!131 = !DIEnumerator(name: "_SC_THREAD_STACK_MIN", value: 75)
!132 = !DIEnumerator(name: "_SC_THREAD_THREADS_MAX", value: 76)
!133 = !DIEnumerator(name: "_SC_THREAD_ATTR_STACKADDR", value: 77)
!134 = !DIEnumerator(name: "_SC_THREAD_ATTR_STACKSIZE", value: 78)
!135 = !DIEnumerator(name: "_SC_THREAD_PRIORITY_SCHEDULING", value: 79)
!136 = !DIEnumerator(name: "_SC_THREAD_PRIO_INHERIT", value: 80)
!137 = !DIEnumerator(name: "_SC_THREAD_PRIO_PROTECT", value: 81)
!138 = !DIEnumerator(name: "_SC_THREAD_PROCESS_SHARED", value: 82)
!139 = !DIEnumerator(name: "_SC_NPROCESSORS_CONF", value: 83)
!140 = !DIEnumerator(name: "_SC_NPROCESSORS_ONLN", value: 84)
!141 = !DIEnumerator(name: "_SC_PHYS_PAGES", value: 85)
!142 = !DIEnumerator(name: "_SC_AVPHYS_PAGES", value: 86)
!143 = !DIEnumerator(name: "_SC_ATEXIT_MAX", value: 87)
!144 = !DIEnumerator(name: "_SC_PASS_MAX", value: 88)
!145 = !DIEnumerator(name: "_SC_XOPEN_VERSION", value: 89)
!146 = !DIEnumerator(name: "_SC_XOPEN_XCU_VERSION", value: 90)
!147 = !DIEnumerator(name: "_SC_XOPEN_UNIX", value: 91)
!148 = !DIEnumerator(name: "_SC_XOPEN_CRYPT", value: 92)
!149 = !DIEnumerator(name: "_SC_XOPEN_ENH_I18N", value: 93)
!150 = !DIEnumerator(name: "_SC_XOPEN_SHM", value: 94)
!151 = !DIEnumerator(name: "_SC_2_CHAR_TERM", value: 95)
!152 = !DIEnumerator(name: "_SC_2_C_VERSION", value: 96)
!153 = !DIEnumerator(name: "_SC_2_UPE", value: 97)
!154 = !DIEnumerator(name: "_SC_XOPEN_XPG2", value: 98)
!155 = !DIEnumerator(name: "_SC_XOPEN_XPG3", value: 99)
!156 = !DIEnumerator(name: "_SC_XOPEN_XPG4", value: 100)
!157 = !DIEnumerator(name: "_SC_CHAR_BIT", value: 101)
!158 = !DIEnumerator(name: "_SC_CHAR_MAX", value: 102)
!159 = !DIEnumerator(name: "_SC_CHAR_MIN", value: 103)
!160 = !DIEnumerator(name: "_SC_INT_MAX", value: 104)
!161 = !DIEnumerator(name: "_SC_INT_MIN", value: 105)
!162 = !DIEnumerator(name: "_SC_LONG_BIT", value: 106)
!163 = !DIEnumerator(name: "_SC_WORD_BIT", value: 107)
!164 = !DIEnumerator(name: "_SC_MB_LEN_MAX", value: 108)
!165 = !DIEnumerator(name: "_SC_NZERO", value: 109)
!166 = !DIEnumerator(name: "_SC_SSIZE_MAX", value: 110)
!167 = !DIEnumerator(name: "_SC_SCHAR_MAX", value: 111)
!168 = !DIEnumerator(name: "_SC_SCHAR_MIN", value: 112)
!169 = !DIEnumerator(name: "_SC_SHRT_MAX", value: 113)
!170 = !DIEnumerator(name: "_SC_SHRT_MIN", value: 114)
!171 = !DIEnumerator(name: "_SC_UCHAR_MAX", value: 115)
!172 = !DIEnumerator(name: "_SC_UINT_MAX", value: 116)
!173 = !DIEnumerator(name: "_SC_ULONG_MAX", value: 117)
!174 = !DIEnumerator(name: "_SC_USHRT_MAX", value: 118)
!175 = !DIEnumerator(name: "_SC_NL_ARGMAX", value: 119)
!176 = !DIEnumerator(name: "_SC_NL_LANGMAX", value: 120)
!177 = !DIEnumerator(name: "_SC_NL_MSGMAX", value: 121)
!178 = !DIEnumerator(name: "_SC_NL_NMAX", value: 122)
!179 = !DIEnumerator(name: "_SC_NL_SETMAX", value: 123)
!180 = !DIEnumerator(name: "_SC_NL_TEXTMAX", value: 124)
!181 = !DIEnumerator(name: "_SC_XBS5_ILP32_OFF32", value: 125)
!182 = !DIEnumerator(name: "_SC_XBS5_ILP32_OFFBIG", value: 126)
!183 = !DIEnumerator(name: "_SC_XBS5_LP64_OFF64", value: 127)
!184 = !DIEnumerator(name: "_SC_XBS5_LPBIG_OFFBIG", value: 128)
!185 = !DIEnumerator(name: "_SC_XOPEN_LEGACY", value: 129)
!186 = !DIEnumerator(name: "_SC_XOPEN_REALTIME", value: 130)
!187 = !DIEnumerator(name: "_SC_XOPEN_REALTIME_THREADS", value: 131)
!188 = !DIEnumerator(name: "_SC_ADVISORY_INFO", value: 132)
!189 = !DIEnumerator(name: "_SC_BARRIERS", value: 133)
!190 = !DIEnumerator(name: "_SC_BASE", value: 134)
!191 = !DIEnumerator(name: "_SC_C_LANG_SUPPORT", value: 135)
!192 = !DIEnumerator(name: "_SC_C_LANG_SUPPORT_R", value: 136)
!193 = !DIEnumerator(name: "_SC_CLOCK_SELECTION", value: 137)
!194 = !DIEnumerator(name: "_SC_CPUTIME", value: 138)
!195 = !DIEnumerator(name: "_SC_THREAD_CPUTIME", value: 139)
!196 = !DIEnumerator(name: "_SC_DEVICE_IO", value: 140)
!197 = !DIEnumerator(name: "_SC_DEVICE_SPECIFIC", value: 141)
!198 = !DIEnumerator(name: "_SC_DEVICE_SPECIFIC_R", value: 142)
!199 = !DIEnumerator(name: "_SC_FD_MGMT", value: 143)
!200 = !DIEnumerator(name: "_SC_FIFO", value: 144)
!201 = !DIEnumerator(name: "_SC_PIPE", value: 145)
!202 = !DIEnumerator(name: "_SC_FILE_ATTRIBUTES", value: 146)
!203 = !DIEnumerator(name: "_SC_FILE_LOCKING", value: 147)
!204 = !DIEnumerator(name: "_SC_FILE_SYSTEM", value: 148)
!205 = !DIEnumerator(name: "_SC_MONOTONIC_CLOCK", value: 149)
!206 = !DIEnumerator(name: "_SC_MULTI_PROCESS", value: 150)
!207 = !DIEnumerator(name: "_SC_SINGLE_PROCESS", value: 151)
!208 = !DIEnumerator(name: "_SC_NETWORKING", value: 152)
!209 = !DIEnumerator(name: "_SC_READER_WRITER_LOCKS", value: 153)
!210 = !DIEnumerator(name: "_SC_SPIN_LOCKS", value: 154)
!211 = !DIEnumerator(name: "_SC_REGEXP", value: 155)
!212 = !DIEnumerator(name: "_SC_REGEX_VERSION", value: 156)
!213 = !DIEnumerator(name: "_SC_SHELL", value: 157)
!214 = !DIEnumerator(name: "_SC_SIGNALS", value: 158)
!215 = !DIEnumerator(name: "_SC_SPAWN", value: 159)
!216 = !DIEnumerator(name: "_SC_SPORADIC_SERVER", value: 160)
!217 = !DIEnumerator(name: "_SC_THREAD_SPORADIC_SERVER", value: 161)
!218 = !DIEnumerator(name: "_SC_SYSTEM_DATABASE", value: 162)
!219 = !DIEnumerator(name: "_SC_SYSTEM_DATABASE_R", value: 163)
!220 = !DIEnumerator(name: "_SC_TIMEOUTS", value: 164)
!221 = !DIEnumerator(name: "_SC_TYPED_MEMORY_OBJECTS", value: 165)
!222 = !DIEnumerator(name: "_SC_USER_GROUPS", value: 166)
!223 = !DIEnumerator(name: "_SC_USER_GROUPS_R", value: 167)
!224 = !DIEnumerator(name: "_SC_2_PBS", value: 168)
!225 = !DIEnumerator(name: "_SC_2_PBS_ACCOUNTING", value: 169)
!226 = !DIEnumerator(name: "_SC_2_PBS_LOCATE", value: 170)
!227 = !DIEnumerator(name: "_SC_2_PBS_MESSAGE", value: 171)
!228 = !DIEnumerator(name: "_SC_2_PBS_TRACK", value: 172)
!229 = !DIEnumerator(name: "_SC_SYMLOOP_MAX", value: 173)
!230 = !DIEnumerator(name: "_SC_STREAMS", value: 174)
!231 = !DIEnumerator(name: "_SC_2_PBS_CHECKPOINT", value: 175)
!232 = !DIEnumerator(name: "_SC_V6_ILP32_OFF32", value: 176)
!233 = !DIEnumerator(name: "_SC_V6_ILP32_OFFBIG", value: 177)
!234 = !DIEnumerator(name: "_SC_V6_LP64_OFF64", value: 178)
!235 = !DIEnumerator(name: "_SC_V6_LPBIG_OFFBIG", value: 179)
!236 = !DIEnumerator(name: "_SC_HOST_NAME_MAX", value: 180)
!237 = !DIEnumerator(name: "_SC_TRACE", value: 181)
!238 = !DIEnumerator(name: "_SC_TRACE_EVENT_FILTER", value: 182)
!239 = !DIEnumerator(name: "_SC_TRACE_INHERIT", value: 183)
!240 = !DIEnumerator(name: "_SC_TRACE_LOG", value: 184)
!241 = !DIEnumerator(name: "_SC_LEVEL1_ICACHE_SIZE", value: 185)
!242 = !DIEnumerator(name: "_SC_LEVEL1_ICACHE_ASSOC", value: 186)
!243 = !DIEnumerator(name: "_SC_LEVEL1_ICACHE_LINESIZE", value: 187)
!244 = !DIEnumerator(name: "_SC_LEVEL1_DCACHE_SIZE", value: 188)
!245 = !DIEnumerator(name: "_SC_LEVEL1_DCACHE_ASSOC", value: 189)
!246 = !DIEnumerator(name: "_SC_LEVEL1_DCACHE_LINESIZE", value: 190)
!247 = !DIEnumerator(name: "_SC_LEVEL2_CACHE_SIZE", value: 191)
!248 = !DIEnumerator(name: "_SC_LEVEL2_CACHE_ASSOC", value: 192)
!249 = !DIEnumerator(name: "_SC_LEVEL2_CACHE_LINESIZE", value: 193)
!250 = !DIEnumerator(name: "_SC_LEVEL3_CACHE_SIZE", value: 194)
!251 = !DIEnumerator(name: "_SC_LEVEL3_CACHE_ASSOC", value: 195)
!252 = !DIEnumerator(name: "_SC_LEVEL3_CACHE_LINESIZE", value: 196)
!253 = !DIEnumerator(name: "_SC_LEVEL4_CACHE_SIZE", value: 197)
!254 = !DIEnumerator(name: "_SC_LEVEL4_CACHE_ASSOC", value: 198)
!255 = !DIEnumerator(name: "_SC_LEVEL4_CACHE_LINESIZE", value: 199)
!256 = !DIEnumerator(name: "_SC_IPV6", value: 235)
!257 = !DIEnumerator(name: "_SC_RAW_SOCKETS", value: 236)
!258 = !DIEnumerator(name: "_SC_V7_ILP32_OFF32", value: 237)
!259 = !DIEnumerator(name: "_SC_V7_ILP32_OFFBIG", value: 238)
!260 = !DIEnumerator(name: "_SC_V7_LP64_OFF64", value: 239)
!261 = !DIEnumerator(name: "_SC_V7_LPBIG_OFFBIG", value: 240)
!262 = !DIEnumerator(name: "_SC_SS_REPL_MAX", value: 241)
!263 = !DIEnumerator(name: "_SC_TRACE_EVENT_NAME_MAX", value: 242)
!264 = !DIEnumerator(name: "_SC_TRACE_NAME_MAX", value: 243)
!265 = !DIEnumerator(name: "_SC_TRACE_SYS_MAX", value: 244)
!266 = !DIEnumerator(name: "_SC_TRACE_USER_EVENT_MAX", value: 245)
!267 = !DIEnumerator(name: "_SC_XOPEN_STREAMS", value: 246)
!268 = !DIEnumerator(name: "_SC_THREAD_ROBUST_PRIO_INHERIT", value: 247)
!269 = !DIEnumerator(name: "_SC_THREAD_ROBUST_PRIO_PROTECT", value: 248)
!270 = !{!271, !272, !283, !284, !285, !292, !294, !491, !279, !281, !492, !493, !524, !536, !282}
!271 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: null, size: 64, align: 64)
!272 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !273, size: 64, align: 64)
!273 = !DICompositeType(tag: DW_TAG_structure_type, name: "uv__epoll_event", file: !274, line: 90, size: 96, align: 8, elements: !275)
!274 = !DIFile(filename: "/data/download/cmake/cmake-master/Utilities/cmlibuv/src/unix/linux-syscalls.h", directory: "/data/download/cmake/cmake-master/Utilities/cmlibuv")
!275 = !{!276, !280}
!276 = !DIDerivedType(tag: DW_TAG_member, name: "events", scope: !273, file: !274, line: 91, baseType: !277, size: 32, align: 32)
!277 = !DIDerivedType(tag: DW_TAG_typedef, name: "uint32_t", file: !278, line: 51, baseType: !279)
!278 = !DIFile(filename: "/usr/include/stdint.h", directory: "/data/download/cmake/cmake-master/Utilities/cmlibuv")
!279 = !DIBasicType(name: "unsigned int", size: 32, align: 32, encoding: DW_ATE_unsigned)
!280 = !DIDerivedType(tag: DW_TAG_member, name: "data", scope: !273, file: !274, line: 92, baseType: !281, size: 64, align: 64, offset: 32)
!281 = !DIDerivedType(tag: DW_TAG_typedef, name: "uint64_t", file: !278, line: 55, baseType: !282)
!282 = !DIBasicType(name: "long unsigned int", size: 64, align: 64, encoding: DW_ATE_unsigned)
!283 = !DIDerivedType(tag: DW_TAG_typedef, name: "uintptr_t", file: !278, line: 122, baseType: !282)
!284 = !DIBasicType(name: "int", size: 32, align: 32, encoding: DW_ATE_signed)
!285 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !286, size: 64, align: 64)
!286 = !DIDerivedType(tag: DW_TAG_const_type, baseType: !287)
!287 = !DIDerivedType(tag: DW_TAG_typedef, name: "QUEUE", file: !288, line: 21, baseType: !289)
!288 = !DIFile(filename: "/data/download/cmake/cmake-master/Utilities/cmlibuv/src/queue.h", directory: "/data/download/cmake/cmake-master/Utilities/cmlibuv")
!289 = !DICompositeType(tag: DW_TAG_array_type, baseType: !271, size: 128, align: 64, elements: !290)
!290 = !{!291}
!291 = !DISubrange(count: 2)
!292 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !293, size: 64, align: 64)
!293 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !287, size: 64, align: 64)
!294 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !295, size: 64, align: 64)
!295 = !DIDerivedType(tag: DW_TAG_typedef, name: "uv__io_t", file: !296, line: 87, baseType: !297)
!296 = !DIFile(filename: "/data/download/cmake/cmake-master/Utilities/cmlibuv/include/uv-unix.h", directory: "/data/download/cmake/cmake-master/Utilities/cmlibuv")
!297 = !DICompositeType(tag: DW_TAG_structure_type, name: "uv__io_s", file: !296, line: 89, size: 448, align: 64, elements: !298)
!298 = !{!299, !486, !487, !488, !489, !490}
!299 = !DIDerivedType(tag: DW_TAG_member, name: "cb", scope: !297, file: !296, line: 90, baseType: !300, size: 64, align: 64)
!300 = !DIDerivedType(tag: DW_TAG_typedef, name: "uv__io_cb", file: !296, line: 84, baseType: !301)
!301 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !302, size: 64, align: 64)
!302 = !DISubroutineType(types: !303)
!303 = !{null, !304, !485, !279}
!304 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !305, size: 64, align: 64)
!305 = !DICompositeType(tag: DW_TAG_structure_type, name: "uv_loop_s", file: !4, line: 1473, size: 6784, align: 64, elements: !306)
!306 = !{!307, !308, !309, !310, !311, !312, !313, !314, !315, !316, !318, !319, !320, !321, !352, !402, !426, !427, !428, !429, !430, !431, !432, !436, !437, !438, !443, !444, !445, !447, !448, !481, !482, !483, !484}
!307 = !DIDerivedType(tag: DW_TAG_member, name: "data", scope: !305, file: !4, line: 1475, baseType: !271, size: 64, align: 64)
!308 = !DIDerivedType(tag: DW_TAG_member, name: "active_handles", scope: !305, file: !4, line: 1477, baseType: !279, size: 32, align: 32, offset: 64)
!309 = !DIDerivedType(tag: DW_TAG_member, name: "handle_queue", scope: !305, file: !4, line: 1478, baseType: !289, size: 128, align: 64, offset: 128)
!310 = !DIDerivedType(tag: DW_TAG_member, name: "active_reqs", scope: !305, file: !4, line: 1479, baseType: !289, size: 128, align: 64, offset: 256)
!311 = !DIDerivedType(tag: DW_TAG_member, name: "stop_flag", scope: !305, file: !4, line: 1481, baseType: !279, size: 32, align: 32, offset: 384)
!312 = !DIDerivedType(tag: DW_TAG_member, name: "flags", scope: !305, file: !4, line: 1482, baseType: !282, size: 64, align: 64, offset: 448)
!313 = !DIDerivedType(tag: DW_TAG_member, name: "backend_fd", scope: !305, file: !4, line: 1482, baseType: !284, size: 32, align: 32, offset: 512)
!314 = !DIDerivedType(tag: DW_TAG_member, name: "pending_queue", scope: !305, file: !4, line: 1482, baseType: !289, size: 128, align: 64, offset: 576)
!315 = !DIDerivedType(tag: DW_TAG_member, name: "watcher_queue", scope: !305, file: !4, line: 1482, baseType: !289, size: 128, align: 64, offset: 704)
!316 = !DIDerivedType(tag: DW_TAG_member, name: "watchers", scope: !305, file: !4, line: 1482, baseType: !317, size: 64, align: 64, offset: 832)
!317 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !294, size: 64, align: 64)
!318 = !DIDerivedType(tag: DW_TAG_member, name: "nwatchers", scope: !305, file: !4, line: 1482, baseType: !279, size: 32, align: 32, offset: 896)
!319 = !DIDerivedType(tag: DW_TAG_member, name: "nfds", scope: !305, file: !4, line: 1482, baseType: !279, size: 32, align: 32, offset: 928)
!320 = !DIDerivedType(tag: DW_TAG_member, name: "wq", scope: !305, file: !4, line: 1482, baseType: !289, size: 128, align: 64, offset: 960)
!321 = !DIDerivedType(tag: DW_TAG_member, name: "wq_mutex", scope: !305, file: !4, line: 1482, baseType: !322, size: 320, align: 64, offset: 1088)
!322 = !DIDerivedType(tag: DW_TAG_typedef, name: "uv_mutex_t", file: !296, line: 129, baseType: !323)
!323 = !DIDerivedType(tag: DW_TAG_typedef, name: "pthread_mutex_t", file: !324, line: 127, baseType: !325)
!324 = !DIFile(filename: "/usr/include/x86_64-linux-gnu/bits/pthreadtypes.h", directory: "/data/download/cmake/cmake-master/Utilities/cmlibuv")
!325 = !DICompositeType(tag: DW_TAG_union_type, file: !324, line: 90, size: 320, align: 64, elements: !326)
!326 = !{!327, !345, !350}
!327 = !DIDerivedType(tag: DW_TAG_member, name: "__data", scope: !325, file: !324, line: 124, baseType: !328, size: 320, align: 64)
!328 = !DICompositeType(tag: DW_TAG_structure_type, name: "__pthread_mutex_s", file: !324, line: 92, size: 320, align: 64, elements: !329)
!329 = !{!330, !331, !332, !333, !334, !335, !337, !338}
!330 = !DIDerivedType(tag: DW_TAG_member, name: "__lock", scope: !328, file: !324, line: 94, baseType: !284, size: 32, align: 32)
!331 = !DIDerivedType(tag: DW_TAG_member, name: "__count", scope: !328, file: !324, line: 95, baseType: !279, size: 32, align: 32, offset: 32)
!332 = !DIDerivedType(tag: DW_TAG_member, name: "__owner", scope: !328, file: !324, line: 96, baseType: !284, size: 32, align: 32, offset: 64)
!333 = !DIDerivedType(tag: DW_TAG_member, name: "__nusers", scope: !328, file: !324, line: 98, baseType: !279, size: 32, align: 32, offset: 96)
!334 = !DIDerivedType(tag: DW_TAG_member, name: "__kind", scope: !328, file: !324, line: 102, baseType: !284, size: 32, align: 32, offset: 128)
!335 = !DIDerivedType(tag: DW_TAG_member, name: "__spins", scope: !328, file: !324, line: 104, baseType: !336, size: 16, align: 16, offset: 160)
!336 = !DIBasicType(name: "short", size: 16, align: 16, encoding: DW_ATE_signed)
!337 = !DIDerivedType(tag: DW_TAG_member, name: "__elision", scope: !328, file: !324, line: 105, baseType: !336, size: 16, align: 16, offset: 176)
!338 = !DIDerivedType(tag: DW_TAG_member, name: "__list", scope: !328, file: !324, line: 106, baseType: !339, size: 128, align: 64, offset: 192)
!339 = !DIDerivedType(tag: DW_TAG_typedef, name: "__pthread_list_t", file: !324, line: 79, baseType: !340)
!340 = !DICompositeType(tag: DW_TAG_structure_type, name: "__pthread_internal_list", file: !324, line: 75, size: 128, align: 64, elements: !341)
!341 = !{!342, !344}
!342 = !DIDerivedType(tag: DW_TAG_member, name: "__prev", scope: !340, file: !324, line: 77, baseType: !343, size: 64, align: 64)
!343 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !340, size: 64, align: 64)
!344 = !DIDerivedType(tag: DW_TAG_member, name: "__next", scope: !340, file: !324, line: 78, baseType: !343, size: 64, align: 64, offset: 64)
!345 = !DIDerivedType(tag: DW_TAG_member, name: "__size", scope: !325, file: !324, line: 125, baseType: !346, size: 320, align: 8)
!346 = !DICompositeType(tag: DW_TAG_array_type, baseType: !347, size: 320, align: 8, elements: !348)
!347 = !DIBasicType(name: "char", size: 8, align: 8, encoding: DW_ATE_signed_char)
!348 = !{!349}
!349 = !DISubrange(count: 40)
!350 = !DIDerivedType(tag: DW_TAG_member, name: "__align", scope: !325, file: !324, line: 126, baseType: !351, size: 64, align: 64)
!351 = !DIBasicType(name: "long int", size: 64, align: 64, encoding: DW_ATE_signed)
!352 = !DIDerivedType(tag: DW_TAG_member, name: "wq_async", scope: !305, file: !4, line: 1482, baseType: !353, size: 1024, align: 64, offset: 1408)
!353 = !DIDerivedType(tag: DW_TAG_typedef, name: "uv_async_t", file: !4, line: 216, baseType: !354)
!354 = !DICompositeType(tag: DW_TAG_structure_type, name: "uv_async_s", file: !4, line: 767, size: 1024, align: 64, elements: !355)
!355 = !{!356, !357, !360, !362, !386, !387, !392, !393, !394, !400, !401}
!356 = !DIDerivedType(tag: DW_TAG_member, name: "data", scope: !354, file: !4, line: 768, baseType: !271, size: 64, align: 64)
!357 = !DIDerivedType(tag: DW_TAG_member, name: "loop", scope: !354, file: !4, line: 768, baseType: !358, size: 64, align: 64, offset: 64)
!358 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !359, size: 64, align: 64)
!359 = !DIDerivedType(tag: DW_TAG_typedef, name: "uv_loop_t", file: !4, line: 204, baseType: !305)
!360 = !DIDerivedType(tag: DW_TAG_member, name: "type", scope: !354, file: !4, line: 768, baseType: !361, size: 32, align: 32, offset: 128)
!361 = !DIDerivedType(tag: DW_TAG_typedef, name: "uv_handle_type", file: !4, line: 191, baseType: !3)
!362 = !DIDerivedType(tag: DW_TAG_member, name: "close_cb", scope: !354, file: !4, line: 768, baseType: !363, size: 64, align: 64, offset: 192)
!363 = !DIDerivedType(tag: DW_TAG_typedef, name: "uv_close_cb", file: !4, line: 306, baseType: !364)
!364 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !365, size: 64, align: 64)
!365 = !DISubroutineType(types: !366)
!366 = !{null, !367}
!367 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !368, size: 64, align: 64)
!368 = !DIDerivedType(tag: DW_TAG_typedef, name: "uv_handle_t", file: !4, line: 205, baseType: !369)
!369 = !DICompositeType(tag: DW_TAG_structure_type, name: "uv_handle_s", file: !4, line: 425, size: 768, align: 64, elements: !370)
!370 = !{!371, !372, !373, !374, !375, !376, !384, !385}
!371 = !DIDerivedType(tag: DW_TAG_member, name: "data", scope: !369, file: !4, line: 426, baseType: !271, size: 64, align: 64)
!372 = !DIDerivedType(tag: DW_TAG_member, name: "loop", scope: !369, file: !4, line: 426, baseType: !358, size: 64, align: 64, offset: 64)
!373 = !DIDerivedType(tag: DW_TAG_member, name: "type", scope: !369, file: !4, line: 426, baseType: !361, size: 32, align: 32, offset: 128)
!374 = !DIDerivedType(tag: DW_TAG_member, name: "close_cb", scope: !369, file: !4, line: 426, baseType: !363, size: 64, align: 64, offset: 192)
!375 = !DIDerivedType(tag: DW_TAG_member, name: "handle_queue", scope: !369, file: !4, line: 426, baseType: !289, size: 128, align: 64, offset: 256)
!376 = !DIDerivedType(tag: DW_TAG_member, name: "u", scope: !369, file: !4, line: 426, baseType: !377, size: 256, align: 64, offset: 384)
!377 = !DICompositeType(tag: DW_TAG_union_type, scope: !369, file: !4, line: 426, size: 256, align: 64, elements: !378)
!378 = !{!379, !380}
!379 = !DIDerivedType(tag: DW_TAG_member, name: "fd", scope: !377, file: !4, line: 426, baseType: !284, size: 32, align: 32)
!380 = !DIDerivedType(tag: DW_TAG_member, name: "reserved", scope: !377, file: !4, line: 426, baseType: !381, size: 256, align: 64)
!381 = !DICompositeType(tag: DW_TAG_array_type, baseType: !271, size: 256, align: 64, elements: !382)
!382 = !{!383}
!383 = !DISubrange(count: 4)
!384 = !DIDerivedType(tag: DW_TAG_member, name: "next_closing", scope: !369, file: !4, line: 426, baseType: !367, size: 64, align: 64, offset: 640)
!385 = !DIDerivedType(tag: DW_TAG_member, name: "flags", scope: !369, file: !4, line: 426, baseType: !279, size: 32, align: 32, offset: 704)
!386 = !DIDerivedType(tag: DW_TAG_member, name: "handle_queue", scope: !354, file: !4, line: 768, baseType: !289, size: 128, align: 64, offset: 256)
!387 = !DIDerivedType(tag: DW_TAG_member, name: "u", scope: !354, file: !4, line: 768, baseType: !388, size: 256, align: 64, offset: 384)
!388 = !DICompositeType(tag: DW_TAG_union_type, scope: !354, file: !4, line: 768, size: 256, align: 64, elements: !389)
!389 = !{!390, !391}
!390 = !DIDerivedType(tag: DW_TAG_member, name: "fd", scope: !388, file: !4, line: 768, baseType: !284, size: 32, align: 32)
!391 = !DIDerivedType(tag: DW_TAG_member, name: "reserved", scope: !388, file: !4, line: 768, baseType: !381, size: 256, align: 64)
!392 = !DIDerivedType(tag: DW_TAG_member, name: "next_closing", scope: !354, file: !4, line: 768, baseType: !367, size: 64, align: 64, offset: 640)
!393 = !DIDerivedType(tag: DW_TAG_member, name: "flags", scope: !354, file: !4, line: 768, baseType: !279, size: 32, align: 32, offset: 704)
!394 = !DIDerivedType(tag: DW_TAG_member, name: "async_cb", scope: !354, file: !4, line: 769, baseType: !395, size: 64, align: 64, offset: 768)
!395 = !DIDerivedType(tag: DW_TAG_typedef, name: "uv_async_cb", file: !4, line: 309, baseType: !396)
!396 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !397, size: 64, align: 64)
!397 = !DISubroutineType(types: !398)
!398 = !{null, !399}
!399 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !353, size: 64, align: 64)
!400 = !DIDerivedType(tag: DW_TAG_member, name: "queue", scope: !354, file: !4, line: 769, baseType: !289, size: 128, align: 64, offset: 832)
!401 = !DIDerivedType(tag: DW_TAG_member, name: "pending", scope: !354, file: !4, line: 769, baseType: !284, size: 32, align: 32, offset: 960)
!402 = !DIDerivedType(tag: DW_TAG_member, name: "cloexec_lock", scope: !305, file: !4, line: 1482, baseType: !403, size: 448, align: 64, offset: 2432)
!403 = !DIDerivedType(tag: DW_TAG_typedef, name: "uv_rwlock_t", file: !296, line: 130, baseType: !404)
!404 = !DIDerivedType(tag: DW_TAG_typedef, name: "pthread_rwlock_t", file: !324, line: 213, baseType: !405)
!405 = !DICompositeType(tag: DW_TAG_union_type, file: !324, line: 173, size: 448, align: 64, elements: !406)
!406 = !{!407, !421, !425}
!407 = !DIDerivedType(tag: DW_TAG_member, name: "__data", scope: !405, file: !324, line: 192, baseType: !408, size: 448, align: 64)
!408 = !DICompositeType(tag: DW_TAG_structure_type, scope: !405, file: !324, line: 176, size: 448, align: 64, elements: !409)
!409 = !{!410, !411, !412, !413, !414, !415, !416, !417, !418, !419, !420}
!410 = !DIDerivedType(tag: DW_TAG_member, name: "__lock", scope: !408, file: !324, line: 178, baseType: !284, size: 32, align: 32)
!411 = !DIDerivedType(tag: DW_TAG_member, name: "__nr_readers", scope: !408, file: !324, line: 179, baseType: !279, size: 32, align: 32, offset: 32)
!412 = !DIDerivedType(tag: DW_TAG_member, name: "__readers_wakeup", scope: !408, file: !324, line: 180, baseType: !279, size: 32, align: 32, offset: 64)
!413 = !DIDerivedType(tag: DW_TAG_member, name: "__writer_wakeup", scope: !408, file: !324, line: 181, baseType: !279, size: 32, align: 32, offset: 96)
!414 = !DIDerivedType(tag: DW_TAG_member, name: "__nr_readers_queued", scope: !408, file: !324, line: 182, baseType: !279, size: 32, align: 32, offset: 128)
!415 = !DIDerivedType(tag: DW_TAG_member, name: "__nr_writers_queued", scope: !408, file: !324, line: 183, baseType: !279, size: 32, align: 32, offset: 160)
!416 = !DIDerivedType(tag: DW_TAG_member, name: "__writer", scope: !408, file: !324, line: 184, baseType: !284, size: 32, align: 32, offset: 192)
!417 = !DIDerivedType(tag: DW_TAG_member, name: "__shared", scope: !408, file: !324, line: 185, baseType: !284, size: 32, align: 32, offset: 224)
!418 = !DIDerivedType(tag: DW_TAG_member, name: "__pad1", scope: !408, file: !324, line: 186, baseType: !282, size: 64, align: 64, offset: 256)
!419 = !DIDerivedType(tag: DW_TAG_member, name: "__pad2", scope: !408, file: !324, line: 187, baseType: !282, size: 64, align: 64, offset: 320)
!420 = !DIDerivedType(tag: DW_TAG_member, name: "__flags", scope: !408, file: !324, line: 190, baseType: !279, size: 32, align: 32, offset: 384)
!421 = !DIDerivedType(tag: DW_TAG_member, name: "__size", scope: !405, file: !324, line: 211, baseType: !422, size: 448, align: 8)
!422 = !DICompositeType(tag: DW_TAG_array_type, baseType: !347, size: 448, align: 8, elements: !423)
!423 = !{!424}
!424 = !DISubrange(count: 56)
!425 = !DIDerivedType(tag: DW_TAG_member, name: "__align", scope: !405, file: !324, line: 212, baseType: !351, size: 64, align: 64)
!426 = !DIDerivedType(tag: DW_TAG_member, name: "closing_handles", scope: !305, file: !4, line: 1482, baseType: !367, size: 64, align: 64, offset: 2880)
!427 = !DIDerivedType(tag: DW_TAG_member, name: "process_handles", scope: !305, file: !4, line: 1482, baseType: !289, size: 128, align: 64, offset: 2944)
!428 = !DIDerivedType(tag: DW_TAG_member, name: "prepare_handles", scope: !305, file: !4, line: 1482, baseType: !289, size: 128, align: 64, offset: 3072)
!429 = !DIDerivedType(tag: DW_TAG_member, name: "check_handles", scope: !305, file: !4, line: 1482, baseType: !289, size: 128, align: 64, offset: 3200)
!430 = !DIDerivedType(tag: DW_TAG_member, name: "idle_handles", scope: !305, file: !4, line: 1482, baseType: !289, size: 128, align: 64, offset: 3328)
!431 = !DIDerivedType(tag: DW_TAG_member, name: "async_handles", scope: !305, file: !4, line: 1482, baseType: !289, size: 128, align: 64, offset: 3456)
!432 = !DIDerivedType(tag: DW_TAG_member, name: "async_unused", scope: !305, file: !4, line: 1482, baseType: !433, size: 64, align: 64, offset: 3584)
!433 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !434, size: 64, align: 64)
!434 = !DISubroutineType(types: !435)
!435 = !{null}
!436 = !DIDerivedType(tag: DW_TAG_member, name: "async_io_watcher", scope: !305, file: !4, line: 1482, baseType: !295, size: 448, align: 64, offset: 3648)
!437 = !DIDerivedType(tag: DW_TAG_member, name: "async_wfd", scope: !305, file: !4, line: 1482, baseType: !284, size: 32, align: 32, offset: 4096)
!438 = !DIDerivedType(tag: DW_TAG_member, name: "timer_heap", scope: !305, file: !4, line: 1482, baseType: !439, size: 128, align: 64, offset: 4160)
!439 = !DICompositeType(tag: DW_TAG_structure_type, scope: !305, file: !4, line: 1482, size: 128, align: 64, elements: !440)
!440 = !{!441, !442}
!441 = !DIDerivedType(tag: DW_TAG_member, name: "min", scope: !439, file: !4, line: 1482, baseType: !271, size: 64, align: 64)
!442 = !DIDerivedType(tag: DW_TAG_member, name: "nelts", scope: !439, file: !4, line: 1482, baseType: !279, size: 32, align: 32, offset: 64)
!443 = !DIDerivedType(tag: DW_TAG_member, name: "timer_counter", scope: !305, file: !4, line: 1482, baseType: !281, size: 64, align: 64, offset: 4288)
!444 = !DIDerivedType(tag: DW_TAG_member, name: "time", scope: !305, file: !4, line: 1482, baseType: !281, size: 64, align: 64, offset: 4352)
!445 = !DIDerivedType(tag: DW_TAG_member, name: "signal_pipefd", scope: !305, file: !4, line: 1482, baseType: !446, size: 64, align: 32, offset: 4416)
!446 = !DICompositeType(tag: DW_TAG_array_type, baseType: !284, size: 64, align: 32, elements: !290)
!447 = !DIDerivedType(tag: DW_TAG_member, name: "signal_io_watcher", scope: !305, file: !4, line: 1482, baseType: !295, size: 448, align: 64, offset: 4480)
!448 = !DIDerivedType(tag: DW_TAG_member, name: "child_watcher", scope: !305, file: !4, line: 1482, baseType: !449, size: 1216, align: 64, offset: 4928)
!449 = !DIDerivedType(tag: DW_TAG_typedef, name: "uv_signal_t", file: !4, line: 220, baseType: !450)
!450 = !DICompositeType(tag: DW_TAG_structure_type, name: "uv_signal_s", file: !4, line: 1325, size: 1216, align: 64, elements: !451)
!451 = !{!452, !453, !454, !455, !456, !457, !462, !463, !464, !470, !471, !479, !480}
!452 = !DIDerivedType(tag: DW_TAG_member, name: "data", scope: !450, file: !4, line: 1326, baseType: !271, size: 64, align: 64)
!453 = !DIDerivedType(tag: DW_TAG_member, name: "loop", scope: !450, file: !4, line: 1326, baseType: !358, size: 64, align: 64, offset: 64)
!454 = !DIDerivedType(tag: DW_TAG_member, name: "type", scope: !450, file: !4, line: 1326, baseType: !361, size: 32, align: 32, offset: 128)
!455 = !DIDerivedType(tag: DW_TAG_member, name: "close_cb", scope: !450, file: !4, line: 1326, baseType: !363, size: 64, align: 64, offset: 192)
!456 = !DIDerivedType(tag: DW_TAG_member, name: "handle_queue", scope: !450, file: !4, line: 1326, baseType: !289, size: 128, align: 64, offset: 256)
!457 = !DIDerivedType(tag: DW_TAG_member, name: "u", scope: !450, file: !4, line: 1326, baseType: !458, size: 256, align: 64, offset: 384)
!458 = !DICompositeType(tag: DW_TAG_union_type, scope: !450, file: !4, line: 1326, size: 256, align: 64, elements: !459)
!459 = !{!460, !461}
!460 = !DIDerivedType(tag: DW_TAG_member, name: "fd", scope: !458, file: !4, line: 1326, baseType: !284, size: 32, align: 32)
!461 = !DIDerivedType(tag: DW_TAG_member, name: "reserved", scope: !458, file: !4, line: 1326, baseType: !381, size: 256, align: 64)
!462 = !DIDerivedType(tag: DW_TAG_member, name: "next_closing", scope: !450, file: !4, line: 1326, baseType: !367, size: 64, align: 64, offset: 640)
!463 = !DIDerivedType(tag: DW_TAG_member, name: "flags", scope: !450, file: !4, line: 1326, baseType: !279, size: 32, align: 32, offset: 704)
!464 = !DIDerivedType(tag: DW_TAG_member, name: "signal_cb", scope: !450, file: !4, line: 1327, baseType: !465, size: 64, align: 64, offset: 768)
!465 = !DIDerivedType(tag: DW_TAG_typedef, name: "uv_signal_cb", file: !4, line: 362, baseType: !466)
!466 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !467, size: 64, align: 64)
!467 = !DISubroutineType(types: !468)
!468 = !{null, !469, !284}
!469 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !449, size: 64, align: 64)
!470 = !DIDerivedType(tag: DW_TAG_member, name: "signum", scope: !450, file: !4, line: 1328, baseType: !284, size: 32, align: 32, offset: 832)
!471 = !DIDerivedType(tag: DW_TAG_member, name: "tree_entry", scope: !450, file: !4, line: 1329, baseType: !472, size: 256, align: 64, offset: 896)
!472 = !DICompositeType(tag: DW_TAG_structure_type, scope: !450, file: !4, line: 1329, size: 256, align: 64, elements: !473)
!473 = !{!474, !476, !477, !478}
!474 = !DIDerivedType(tag: DW_TAG_member, name: "rbe_left", scope: !472, file: !4, line: 1329, baseType: !475, size: 64, align: 64)
!475 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !450, size: 64, align: 64)
!476 = !DIDerivedType(tag: DW_TAG_member, name: "rbe_right", scope: !472, file: !4, line: 1329, baseType: !475, size: 64, align: 64, offset: 64)
!477 = !DIDerivedType(tag: DW_TAG_member, name: "rbe_parent", scope: !472, file: !4, line: 1329, baseType: !475, size: 64, align: 64, offset: 128)
!478 = !DIDerivedType(tag: DW_TAG_member, name: "rbe_color", scope: !472, file: !4, line: 1329, baseType: !284, size: 32, align: 32, offset: 192)
!479 = !DIDerivedType(tag: DW_TAG_member, name: "caught_signals", scope: !450, file: !4, line: 1329, baseType: !279, size: 32, align: 32, offset: 1152)
!480 = !DIDerivedType(tag: DW_TAG_member, name: "dispatched_signals", scope: !450, file: !4, line: 1329, baseType: !279, size: 32, align: 32, offset: 1184)
!481 = !DIDerivedType(tag: DW_TAG_member, name: "emfile_fd", scope: !305, file: !4, line: 1482, baseType: !284, size: 32, align: 32, offset: 6144)
!482 = !DIDerivedType(tag: DW_TAG_member, name: "inotify_read_watcher", scope: !305, file: !4, line: 1482, baseType: !295, size: 448, align: 64, offset: 6208)
!483 = !DIDerivedType(tag: DW_TAG_member, name: "inotify_watchers", scope: !305, file: !4, line: 1482, baseType: !271, size: 64, align: 64, offset: 6656)
!484 = !DIDerivedType(tag: DW_TAG_member, name: "inotify_fd", scope: !305, file: !4, line: 1482, baseType: !284, size: 32, align: 32, offset: 6720)
!485 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !297, size: 64, align: 64)
!486 = !DIDerivedType(tag: DW_TAG_member, name: "pending_queue", scope: !297, file: !296, line: 91, baseType: !289, size: 128, align: 64, offset: 64)
!487 = !DIDerivedType(tag: DW_TAG_member, name: "watcher_queue", scope: !297, file: !296, line: 92, baseType: !289, size: 128, align: 64, offset: 192)
!488 = !DIDerivedType(tag: DW_TAG_member, name: "pevents", scope: !297, file: !296, line: 93, baseType: !279, size: 32, align: 32, offset: 320)
!489 = !DIDerivedType(tag: DW_TAG_member, name: "events", scope: !297, file: !296, line: 94, baseType: !279, size: 32, align: 32, offset: 352)
!490 = !DIDerivedType(tag: DW_TAG_member, name: "fd", scope: !297, file: !296, line: 95, baseType: !284, size: 32, align: 32, offset: 384)
!491 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !347, size: 64, align: 64)
!492 = !DIBasicType(name: "double", size: 64, align: 64, encoding: DW_ATE_float)
!493 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !494, size: 64, align: 64)
!494 = !DICompositeType(tag: DW_TAG_structure_type, name: "sockaddr_in6", file: !495, line: 252, size: 224, align: 32, elements: !496)
!495 = !DIFile(filename: "/usr/include/netinet/in.h", directory: "/data/download/cmake/cmake-master/Utilities/cmlibuv")
!496 = !{!497, !501, !504, !505, !523}
!497 = !DIDerivedType(tag: DW_TAG_member, name: "sin6_family", scope: !494, file: !495, line: 254, baseType: !498, size: 16, align: 16)
!498 = !DIDerivedType(tag: DW_TAG_typedef, name: "sa_family_t", file: !499, line: 28, baseType: !500)
!499 = !DIFile(filename: "/usr/include/x86_64-linux-gnu/bits/sockaddr.h", directory: "/data/download/cmake/cmake-master/Utilities/cmlibuv")
!500 = !DIBasicType(name: "unsigned short", size: 16, align: 16, encoding: DW_ATE_unsigned)
!501 = !DIDerivedType(tag: DW_TAG_member, name: "sin6_port", scope: !494, file: !495, line: 255, baseType: !502, size: 16, align: 16, offset: 16)
!502 = !DIDerivedType(tag: DW_TAG_typedef, name: "in_port_t", file: !495, line: 117, baseType: !503)
!503 = !DIDerivedType(tag: DW_TAG_typedef, name: "uint16_t", file: !278, line: 49, baseType: !500)
!504 = !DIDerivedType(tag: DW_TAG_member, name: "sin6_flowinfo", scope: !494, file: !495, line: 256, baseType: !277, size: 32, align: 32, offset: 32)
!505 = !DIDerivedType(tag: DW_TAG_member, name: "sin6_addr", scope: !494, file: !495, line: 257, baseType: !506, size: 128, align: 32, offset: 64)
!506 = !DICompositeType(tag: DW_TAG_structure_type, name: "in6_addr", file: !495, line: 209, size: 128, align: 32, elements: !507)
!507 = !{!508}
!508 = !DIDerivedType(tag: DW_TAG_member, name: "__in6_u", scope: !506, file: !495, line: 218, baseType: !509, size: 128, align: 32)
!509 = !DICompositeType(tag: DW_TAG_union_type, scope: !506, file: !495, line: 211, size: 128, align: 32, elements: !510)
!510 = !{!511, !517, !521}
!511 = !DIDerivedType(tag: DW_TAG_member, name: "__u6_addr8", scope: !509, file: !495, line: 213, baseType: !512, size: 128, align: 8)
!512 = !DICompositeType(tag: DW_TAG_array_type, baseType: !513, size: 128, align: 8, elements: !515)
!513 = !DIDerivedType(tag: DW_TAG_typedef, name: "uint8_t", file: !278, line: 48, baseType: !514)
!514 = !DIBasicType(name: "unsigned char", size: 8, align: 8, encoding: DW_ATE_unsigned_char)
!515 = !{!516}
!516 = !DISubrange(count: 16)
!517 = !DIDerivedType(tag: DW_TAG_member, name: "__u6_addr16", scope: !509, file: !495, line: 215, baseType: !518, size: 128, align: 16)
!518 = !DICompositeType(tag: DW_TAG_array_type, baseType: !503, size: 128, align: 16, elements: !519)
!519 = !{!520}
!520 = !DISubrange(count: 8)
!521 = !DIDerivedType(tag: DW_TAG_member, name: "__u6_addr32", scope: !509, file: !495, line: 216, baseType: !522, size: 128, align: 32)
!522 = !DICompositeType(tag: DW_TAG_array_type, baseType: !277, size: 128, align: 32, elements: !382)
!523 = !DIDerivedType(tag: DW_TAG_member, name: "sin6_scope_id", scope: !494, file: !495, line: 258, baseType: !277, size: 32, align: 32, offset: 192)
!524 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !525, size: 64, align: 64)
!525 = !DICompositeType(tag: DW_TAG_structure_type, name: "sockaddr_in", file: !495, line: 237, size: 128, align: 32, elements: !526)
!526 = !{!527, !528, !529, !534}
!527 = !DIDerivedType(tag: DW_TAG_member, name: "sin_family", scope: !525, file: !495, line: 239, baseType: !498, size: 16, align: 16)
!528 = !DIDerivedType(tag: DW_TAG_member, name: "sin_port", scope: !525, file: !495, line: 240, baseType: !502, size: 16, align: 16, offset: 16)
!529 = !DIDerivedType(tag: DW_TAG_member, name: "sin_addr", scope: !525, file: !495, line: 241, baseType: !530, size: 32, align: 32, offset: 32)
!530 = !DICompositeType(tag: DW_TAG_structure_type, name: "in_addr", file: !495, line: 31, size: 32, align: 32, elements: !531)
!531 = !{!532}
!532 = !DIDerivedType(tag: DW_TAG_member, name: "s_addr", scope: !530, file: !495, line: 33, baseType: !533, size: 32, align: 32)
!533 = !DIDerivedType(tag: DW_TAG_typedef, name: "in_addr_t", file: !495, line: 30, baseType: !277)
!534 = !DIDerivedType(tag: DW_TAG_member, name: "sin_zero", scope: !525, file: !495, line: 244, baseType: !535, size: 64, align: 8, offset: 64)
!535 = !DICompositeType(tag: DW_TAG_array_type, baseType: !514, size: 64, align: 8, elements: !519)
!536 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !537, size: 64, align: 64)
!537 = !DICompositeType(tag: DW_TAG_structure_type, name: "sockaddr_ll", file: !538, line: 22, size: 160, align: 32, elements: !539)
!538 = !DIFile(filename: "/usr/include/netpacket/packet.h", directory: "/data/download/cmake/cmake-master/Utilities/cmlibuv")
!539 = !{!540, !541, !542, !543, !544, !545, !546}
!540 = !DIDerivedType(tag: DW_TAG_member, name: "sll_family", scope: !537, file: !538, line: 24, baseType: !500, size: 16, align: 16)
!541 = !DIDerivedType(tag: DW_TAG_member, name: "sll_protocol", scope: !537, file: !538, line: 25, baseType: !500, size: 16, align: 16, offset: 16)
!542 = !DIDerivedType(tag: DW_TAG_member, name: "sll_ifindex", scope: !537, file: !538, line: 26, baseType: !284, size: 32, align: 32, offset: 32)
!543 = !DIDerivedType(tag: DW_TAG_member, name: "sll_hatype", scope: !537, file: !538, line: 27, baseType: !500, size: 16, align: 16, offset: 64)
!544 = !DIDerivedType(tag: DW_TAG_member, name: "sll_pkttype", scope: !537, file: !538, line: 28, baseType: !514, size: 8, align: 8, offset: 80)
!545 = !DIDerivedType(tag: DW_TAG_member, name: "sll_halen", scope: !537, file: !538, line: 29, baseType: !514, size: 8, align: 8, offset: 88)
!546 = !DIDerivedType(tag: DW_TAG_member, name: "sll_addr", scope: !537, file: !538, line: 30, baseType: !535, size: 64, align: 8, offset: 96)
!547 = !{!548, !552, !553, !556, !559, !562, !563, !567, !571, !577, !580, !581, !584, !587, !606, !609, !633, !636, !641, !642, !700, !703, !706, !709, !712}
!548 = distinct !DISubprogram(name: "uv__platform_loop_init", scope: !1, file: !1, line: 84, type: !549, isLocal: false, isDefinition: true, scopeLine: 84, flags: DIFlagPrototyped, isOptimized: false, variables: !551)
!549 = !DISubroutineType(types: !550)
!550 = !{!284, !358}
!551 = !{}
!552 = distinct !DISubprogram(name: "uv__io_fork", scope: !1, file: !1, line: 110, type: !549, isLocal: false, isDefinition: true, scopeLine: 110, flags: DIFlagPrototyped, isOptimized: false, variables: !551)
!553 = distinct !DISubprogram(name: "uv__platform_loop_delete", scope: !1, file: !1, line: 128, type: !554, isLocal: false, isDefinition: true, scopeLine: 128, flags: DIFlagPrototyped, isOptimized: false, variables: !551)
!554 = !DISubroutineType(types: !555)
!555 = !{null, !358}
!556 = distinct !DISubprogram(name: "uv__platform_invalidate_fd", scope: !1, file: !1, line: 136, type: !557, isLocal: false, isDefinition: true, scopeLine: 136, flags: DIFlagPrototyped, isOptimized: false, variables: !551)
!557 = !DISubroutineType(types: !558)
!558 = !{null, !358, !284}
!559 = distinct !DISubprogram(name: "uv__io_check_fd", scope: !1, file: !1, line: 168, type: !560, isLocal: false, isDefinition: true, scopeLine: 168, flags: DIFlagPrototyped, isOptimized: false, variables: !551)
!560 = !DISubroutineType(types: !561)
!561 = !{!284, !358, !284}
!562 = distinct !DISubprogram(name: "uv__io_poll", scope: !1, file: !1, line: 188, type: !557, isLocal: false, isDefinition: true, scopeLine: 188, flags: DIFlagPrototyped, isOptimized: false, variables: !551)
!563 = distinct !DISubprogram(name: "uv__hrtime", scope: !1, file: !1, line: 442, type: !564, isLocal: false, isDefinition: true, scopeLine: 442, flags: DIFlagPrototyped, isOptimized: false, variables: !551)
!564 = !DISubroutineType(types: !565)
!565 = !{!281, !566}
!566 = !DIDerivedType(tag: DW_TAG_typedef, name: "uv_clocktype_t", file: !26, line: 151, baseType: !29)
!567 = distinct !DISubprogram(name: "uv_loadavg", scope: !1, file: !1, line: 475, type: !568, isLocal: false, isDefinition: true, scopeLine: 475, flags: DIFlagPrototyped, isOptimized: false, variables: !551)
!568 = !DISubroutineType(types: !569)
!569 = !{null, !570}
!570 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !492, size: 64, align: 64)
!571 = distinct !DISubprogram(name: "uv_exepath", scope: !1, file: !1, line: 486, type: !572, isLocal: false, isDefinition: true, scopeLine: 486, flags: DIFlagPrototyped, isOptimized: false, variables: !551)
!572 = !DISubroutineType(types: !573)
!573 = !{!284, !491, !574}
!574 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !575, size: 64, align: 64)
!575 = !DIDerivedType(tag: DW_TAG_typedef, name: "size_t", file: !576, line: 62, baseType: !282)
!576 = !DIFile(filename: "/opt/llvm-build/bin/../lib/clang/3.8.0/include/stddef.h", directory: "/data/download/cmake/cmake-master/Utilities/cmlibuv")
!577 = distinct !DISubprogram(name: "uv_get_free_memory", scope: !1, file: !1, line: 506, type: !578, isLocal: false, isDefinition: true, scopeLine: 506, flags: DIFlagPrototyped, isOptimized: false, variables: !551)
!578 = !DISubroutineType(types: !579)
!579 = !{!281}
!580 = distinct !DISubprogram(name: "uv_get_total_memory", scope: !1, file: !1, line: 515, type: !578, isLocal: false, isDefinition: true, scopeLine: 515, flags: DIFlagPrototyped, isOptimized: false, variables: !551)
!581 = distinct !DISubprogram(name: "uv_resident_set_memory", scope: !1, file: !1, line: 524, type: !582, isLocal: false, isDefinition: true, scopeLine: 524, flags: DIFlagPrototyped, isOptimized: false, variables: !551)
!582 = !DISubroutineType(types: !583)
!583 = !{!284, !574}
!584 = distinct !DISubprogram(name: "uv_uptime", scope: !1, file: !1, line: 581, type: !585, isLocal: false, isDefinition: true, scopeLine: 581, flags: DIFlagPrototyped, isOptimized: false, variables: !551)
!585 = !DISubroutineType(types: !586)
!586 = !{!284, !570}
!587 = distinct !DISubprogram(name: "uv_cpu_info", scope: !1, file: !1, line: 628, type: !588, isLocal: false, isDefinition: true, scopeLine: 628, flags: DIFlagPrototyped, isOptimized: false, variables: !551)
!588 = !DISubroutineType(types: !589)
!589 = !{!284, !590, !605}
!590 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !591, size: 64, align: 64)
!591 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !592, size: 64, align: 64)
!592 = !DIDerivedType(tag: DW_TAG_typedef, name: "uv_cpu_info_t", file: !4, line: 234, baseType: !593)
!593 = !DICompositeType(tag: DW_TAG_structure_type, name: "uv_cpu_info_s", file: !4, line: 986, size: 448, align: 64, elements: !594)
!594 = !{!595, !596, !597}
!595 = !DIDerivedType(tag: DW_TAG_member, name: "model", scope: !593, file: !4, line: 987, baseType: !491, size: 64, align: 64)
!596 = !DIDerivedType(tag: DW_TAG_member, name: "speed", scope: !593, file: !4, line: 988, baseType: !284, size: 32, align: 32, offset: 64)
!597 = !DIDerivedType(tag: DW_TAG_member, name: "cpu_times", scope: !593, file: !4, line: 995, baseType: !598, size: 320, align: 64, offset: 128)
!598 = !DICompositeType(tag: DW_TAG_structure_type, name: "uv_cpu_times_s", file: !4, line: 989, size: 320, align: 64, elements: !599)
!599 = !{!600, !601, !602, !603, !604}
!600 = !DIDerivedType(tag: DW_TAG_member, name: "user", scope: !598, file: !4, line: 990, baseType: !281, size: 64, align: 64)
!601 = !DIDerivedType(tag: DW_TAG_member, name: "nice", scope: !598, file: !4, line: 991, baseType: !281, size: 64, align: 64, offset: 64)
!602 = !DIDerivedType(tag: DW_TAG_member, name: "sys", scope: !598, file: !4, line: 992, baseType: !281, size: 64, align: 64, offset: 128)
!603 = !DIDerivedType(tag: DW_TAG_member, name: "idle", scope: !598, file: !4, line: 993, baseType: !281, size: 64, align: 64, offset: 192)
!604 = !DIDerivedType(tag: DW_TAG_member, name: "irq", scope: !598, file: !4, line: 994, baseType: !281, size: 64, align: 64, offset: 256)
!605 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !284, size: 64, align: 64)
!606 = distinct !DISubprogram(name: "uv_free_cpu_info", scope: !1, file: !1, line: 879, type: !607, isLocal: false, isDefinition: true, scopeLine: 879, flags: DIFlagPrototyped, isOptimized: false, variables: !551)
!607 = !DISubroutineType(types: !608)
!608 = !{null, !591, !284}
!609 = distinct !DISubprogram(name: "uv_interface_addresses", scope: !1, file: !1, line: 903, type: !610, isLocal: false, isDefinition: true, scopeLine: 904, flags: DIFlagPrototyped, isOptimized: false, variables: !551)
!610 = !DISubroutineType(types: !611)
!611 = !{!284, !612, !605}
!612 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !613, size: 64, align: 64)
!613 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !614, size: 64, align: 64)
!614 = !DIDerivedType(tag: DW_TAG_typedef, name: "uv_interface_address_t", file: !4, line: 235, baseType: !615)
!615 = !DICompositeType(tag: DW_TAG_structure_type, name: "uv_interface_address_s", file: !4, line: 998, size: 640, align: 64, elements: !616)
!616 = !{!617, !618, !622, !623, !628}
!617 = !DIDerivedType(tag: DW_TAG_member, name: "name", scope: !615, file: !4, line: 999, baseType: !491, size: 64, align: 64)
!618 = !DIDerivedType(tag: DW_TAG_member, name: "phys_addr", scope: !615, file: !4, line: 1000, baseType: !619, size: 48, align: 8, offset: 64)
!619 = !DICompositeType(tag: DW_TAG_array_type, baseType: !347, size: 48, align: 8, elements: !620)
!620 = !{!621}
!621 = !DISubrange(count: 6)
!622 = !DIDerivedType(tag: DW_TAG_member, name: "is_internal", scope: !615, file: !4, line: 1001, baseType: !284, size: 32, align: 32, offset: 128)
!623 = !DIDerivedType(tag: DW_TAG_member, name: "address", scope: !615, file: !4, line: 1005, baseType: !624, size: 224, align: 32, offset: 160)
!624 = !DICompositeType(tag: DW_TAG_union_type, scope: !615, file: !4, line: 1002, size: 224, align: 32, elements: !625)
!625 = !{!626, !627}
!626 = !DIDerivedType(tag: DW_TAG_member, name: "address4", scope: !624, file: !4, line: 1003, baseType: !525, size: 128, align: 32)
!627 = !DIDerivedType(tag: DW_TAG_member, name: "address6", scope: !624, file: !4, line: 1004, baseType: !494, size: 224, align: 32)
!628 = !DIDerivedType(tag: DW_TAG_member, name: "netmask", scope: !615, file: !4, line: 1009, baseType: !629, size: 224, align: 32, offset: 384)
!629 = !DICompositeType(tag: DW_TAG_union_type, scope: !615, file: !4, line: 1006, size: 224, align: 32, elements: !630)
!630 = !{!631, !632}
!631 = !DIDerivedType(tag: DW_TAG_member, name: "netmask4", scope: !629, file: !4, line: 1007, baseType: !525, size: 128, align: 32)
!632 = !DIDerivedType(tag: DW_TAG_member, name: "netmask6", scope: !629, file: !4, line: 1008, baseType: !494, size: 224, align: 32)
!633 = distinct !DISubprogram(name: "uv_free_interface_addresses", scope: !1, file: !1, line: 984, type: !634, isLocal: false, isDefinition: true, scopeLine: 985, flags: DIFlagPrototyped, isOptimized: false, variables: !551)
!634 = !DISubroutineType(types: !635)
!635 = !{null, !613, !284}
!636 = distinct !DISubprogram(name: "uv__set_process_title", scope: !1, file: !1, line: 996, type: !637, isLocal: false, isDefinition: true, scopeLine: 996, flags: DIFlagPrototyped, isOptimized: false, variables: !551)
!637 = !DISubroutineType(types: !638)
!638 = !{null, !639}
!639 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !640, size: 64, align: 64)
!640 = !DIDerivedType(tag: DW_TAG_const_type, baseType: !347)
!641 = distinct !DISubprogram(name: "uv__update_time", scope: !26, file: !26, line: 306, type: !554, isLocal: true, isDefinition: true, scopeLine: 306, flags: DIFlagPrototyped, isOptimized: false, variables: !551)
!642 = distinct !DISubprogram(name: "uv__cpu_num", scope: !1, file: !1, line: 606, type: !643, isLocal: true, isDefinition: true, scopeLine: 606, flags: DIFlagPrototyped, isOptimized: false, variables: !551)
!643 = !DISubroutineType(types: !644)
!644 = !{!284, !645, !699}
!645 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !646, size: 64, align: 64)
!646 = !DIDerivedType(tag: DW_TAG_typedef, name: "FILE", file: !647, line: 48, baseType: !648)
!647 = !DIFile(filename: "/usr/include/stdio.h", directory: "/data/download/cmake/cmake-master/Utilities/cmlibuv")
!648 = !DICompositeType(tag: DW_TAG_structure_type, name: "_IO_FILE", file: !649, line: 245, size: 1728, align: 64, elements: !650)
!649 = !DIFile(filename: "/usr/include/libio.h", directory: "/data/download/cmake/cmake-master/Utilities/cmlibuv")
!650 = !{!651, !652, !653, !654, !655, !656, !657, !658, !659, !660, !661, !662, !663, !671, !672, !673, !674, !677, !678, !680, !684, !687, !689, !690, !691, !692, !693, !694, !695}
!651 = !DIDerivedType(tag: DW_TAG_member, name: "_flags", scope: !648, file: !649, line: 246, baseType: !284, size: 32, align: 32)
!652 = !DIDerivedType(tag: DW_TAG_member, name: "_IO_read_ptr", scope: !648, file: !649, line: 251, baseType: !491, size: 64, align: 64, offset: 64)
!653 = !DIDerivedType(tag: DW_TAG_member, name: "_IO_read_end", scope: !648, file: !649, line: 252, baseType: !491, size: 64, align: 64, offset: 128)
!654 = !DIDerivedType(tag: DW_TAG_member, name: "_IO_read_base", scope: !648, file: !649, line: 253, baseType: !491, size: 64, align: 64, offset: 192)
!655 = !DIDerivedType(tag: DW_TAG_member, name: "_IO_write_base", scope: !648, file: !649, line: 254, baseType: !491, size: 64, align: 64, offset: 256)
!656 = !DIDerivedType(tag: DW_TAG_member, name: "_IO_write_ptr", scope: !648, file: !649, line: 255, baseType: !491, size: 64, align: 64, offset: 320)
!657 = !DIDerivedType(tag: DW_TAG_member, name: "_IO_write_end", scope: !648, file: !649, line: 256, baseType: !491, size: 64, align: 64, offset: 384)
!658 = !DIDerivedType(tag: DW_TAG_member, name: "_IO_buf_base", scope: !648, file: !649, line: 257, baseType: !491, size: 64, align: 64, offset: 448)
!659 = !DIDerivedType(tag: DW_TAG_member, name: "_IO_buf_end", scope: !648, file: !649, line: 258, baseType: !491, size: 64, align: 64, offset: 512)
!660 = !DIDerivedType(tag: DW_TAG_member, name: "_IO_save_base", scope: !648, file: !649, line: 260, baseType: !491, size: 64, align: 64, offset: 576)
!661 = !DIDerivedType(tag: DW_TAG_member, name: "_IO_backup_base", scope: !648, file: !649, line: 261, baseType: !491, size: 64, align: 64, offset: 640)
!662 = !DIDerivedType(tag: DW_TAG_member, name: "_IO_save_end", scope: !648, file: !649, line: 262, baseType: !491, size: 64, align: 64, offset: 704)
!663 = !DIDerivedType(tag: DW_TAG_member, name: "_markers", scope: !648, file: !649, line: 264, baseType: !664, size: 64, align: 64, offset: 768)
!664 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !665, size: 64, align: 64)
!665 = !DICompositeType(tag: DW_TAG_structure_type, name: "_IO_marker", file: !649, line: 160, size: 192, align: 64, elements: !666)
!666 = !{!667, !668, !670}
!667 = !DIDerivedType(tag: DW_TAG_member, name: "_next", scope: !665, file: !649, line: 161, baseType: !664, size: 64, align: 64)
!668 = !DIDerivedType(tag: DW_TAG_member, name: "_sbuf", scope: !665, file: !649, line: 162, baseType: !669, size: 64, align: 64, offset: 64)
!669 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !648, size: 64, align: 64)
!670 = !DIDerivedType(tag: DW_TAG_member, name: "_pos", scope: !665, file: !649, line: 166, baseType: !284, size: 32, align: 32, offset: 128)
!671 = !DIDerivedType(tag: DW_TAG_member, name: "_chain", scope: !648, file: !649, line: 266, baseType: !669, size: 64, align: 64, offset: 832)
!672 = !DIDerivedType(tag: DW_TAG_member, name: "_fileno", scope: !648, file: !649, line: 268, baseType: !284, size: 32, align: 32, offset: 896)
!673 = !DIDerivedType(tag: DW_TAG_member, name: "_flags2", scope: !648, file: !649, line: 272, baseType: !284, size: 32, align: 32, offset: 928)
!674 = !DIDerivedType(tag: DW_TAG_member, name: "_old_offset", scope: !648, file: !649, line: 274, baseType: !675, size: 64, align: 64, offset: 960)
!675 = !DIDerivedType(tag: DW_TAG_typedef, name: "__off_t", file: !676, line: 131, baseType: !351)
!676 = !DIFile(filename: "/usr/include/x86_64-linux-gnu/bits/types.h", directory: "/data/download/cmake/cmake-master/Utilities/cmlibuv")
!677 = !DIDerivedType(tag: DW_TAG_member, name: "_cur_column", scope: !648, file: !649, line: 278, baseType: !500, size: 16, align: 16, offset: 1024)
!678 = !DIDerivedType(tag: DW_TAG_member, name: "_vtable_offset", scope: !648, file: !649, line: 279, baseType: !679, size: 8, align: 8, offset: 1040)
!679 = !DIBasicType(name: "signed char", size: 8, align: 8, encoding: DW_ATE_signed_char)
!680 = !DIDerivedType(tag: DW_TAG_member, name: "_shortbuf", scope: !648, file: !649, line: 280, baseType: !681, size: 8, align: 8, offset: 1048)
!681 = !DICompositeType(tag: DW_TAG_array_type, baseType: !347, size: 8, align: 8, elements: !682)
!682 = !{!683}
!683 = !DISubrange(count: 1)
!684 = !DIDerivedType(tag: DW_TAG_member, name: "_lock", scope: !648, file: !649, line: 284, baseType: !685, size: 64, align: 64, offset: 1088)
!685 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !686, size: 64, align: 64)
!686 = !DIDerivedType(tag: DW_TAG_typedef, name: "_IO_lock_t", file: !649, line: 154, baseType: null)
!687 = !DIDerivedType(tag: DW_TAG_member, name: "_offset", scope: !648, file: !649, line: 293, baseType: !688, size: 64, align: 64, offset: 1152)
!688 = !DIDerivedType(tag: DW_TAG_typedef, name: "__off64_t", file: !676, line: 132, baseType: !351)
!689 = !DIDerivedType(tag: DW_TAG_member, name: "__pad1", scope: !648, file: !649, line: 302, baseType: !271, size: 64, align: 64, offset: 1216)
!690 = !DIDerivedType(tag: DW_TAG_member, name: "__pad2", scope: !648, file: !649, line: 303, baseType: !271, size: 64, align: 64, offset: 1280)
!691 = !DIDerivedType(tag: DW_TAG_member, name: "__pad3", scope: !648, file: !649, line: 304, baseType: !271, size: 64, align: 64, offset: 1344)
!692 = !DIDerivedType(tag: DW_TAG_member, name: "__pad4", scope: !648, file: !649, line: 305, baseType: !271, size: 64, align: 64, offset: 1408)
!693 = !DIDerivedType(tag: DW_TAG_member, name: "__pad5", scope: !648, file: !649, line: 306, baseType: !575, size: 64, align: 64, offset: 1472)
!694 = !DIDerivedType(tag: DW_TAG_member, name: "_mode", scope: !648, file: !649, line: 308, baseType: !284, size: 32, align: 32, offset: 1536)
!695 = !DIDerivedType(tag: DW_TAG_member, name: "_unused2", scope: !648, file: !649, line: 310, baseType: !696, size: 160, align: 8, offset: 1568)
!696 = !DICompositeType(tag: DW_TAG_array_type, baseType: !347, size: 160, align: 8, elements: !697)
!697 = !{!698}
!698 = !DISubrange(count: 20)
!699 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !279, size: 64, align: 64)
!700 = distinct !DISubprogram(name: "read_speeds", scope: !1, file: !1, line: 679, type: !701, isLocal: true, isDefinition: true, scopeLine: 679, flags: DIFlagPrototyped, isOptimized: false, variables: !551)
!701 = !DISubroutineType(types: !702)
!702 = !{null, !279, !591}
!703 = distinct !DISubprogram(name: "read_cpufreq", scope: !1, file: !1, line: 856, type: !704, isLocal: true, isDefinition: true, scopeLine: 856, flags: DIFlagPrototyped, isOptimized: false, variables: !551)
!704 = !DISubroutineType(types: !705)
!705 = !{!282, !279}
!706 = distinct !DISubprogram(name: "read_models", scope: !1, file: !1, line: 692, type: !707, isLocal: true, isDefinition: true, scopeLine: 692, flags: DIFlagPrototyped, isOptimized: false, variables: !551)
!707 = !DISubroutineType(types: !708)
!708 = !{!284, !279, !591}
!709 = distinct !DISubprogram(name: "read_times", scope: !1, file: !1, line: 785, type: !710, isLocal: true, isDefinition: true, scopeLine: 787, flags: DIFlagPrototyped, isOptimized: false, variables: !551)
!710 = !DISubroutineType(types: !711)
!711 = !{!284, !645, !279, !591}
!712 = distinct !DISubprogram(name: "uv__ifaddr_exclude", scope: !1, file: !1, line: 889, type: !713, isLocal: true, isDefinition: true, scopeLine: 889, flags: DIFlagPrototyped, isOptimized: false, variables: !551)
!713 = !DISubroutineType(types: !714)
!714 = !{!284, !715}
!715 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !716, size: 64, align: 64)
!716 = !DICompositeType(tag: DW_TAG_structure_type, name: "ifaddrs", file: !717, line: 29, size: 448, align: 64, elements: !718)
!717 = !DIFile(filename: "/usr/include/ifaddrs.h", directory: "/data/download/cmake/cmake-master/Utilities/cmlibuv")
!718 = !{!719, !720, !721, !722, !732, !733, !738}
!719 = !DIDerivedType(tag: DW_TAG_member, name: "ifa_next", scope: !716, file: !717, line: 31, baseType: !715, size: 64, align: 64)
!720 = !DIDerivedType(tag: DW_TAG_member, name: "ifa_name", scope: !716, file: !717, line: 33, baseType: !491, size: 64, align: 64, offset: 64)
!721 = !DIDerivedType(tag: DW_TAG_member, name: "ifa_flags", scope: !716, file: !717, line: 34, baseType: !279, size: 32, align: 32, offset: 128)
!722 = !DIDerivedType(tag: DW_TAG_member, name: "ifa_addr", scope: !716, file: !717, line: 36, baseType: !723, size: 64, align: 64, offset: 192)
!723 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !724, size: 64, align: 64)
!724 = !DICompositeType(tag: DW_TAG_structure_type, name: "sockaddr", file: !725, line: 149, size: 128, align: 16, elements: !726)
!725 = !DIFile(filename: "/usr/include/x86_64-linux-gnu/bits/socket.h", directory: "/data/download/cmake/cmake-master/Utilities/cmlibuv")
!726 = !{!727, !728}
!727 = !DIDerivedType(tag: DW_TAG_member, name: "sa_family", scope: !724, file: !725, line: 151, baseType: !498, size: 16, align: 16)
!728 = !DIDerivedType(tag: DW_TAG_member, name: "sa_data", scope: !724, file: !725, line: 152, baseType: !729, size: 112, align: 8, offset: 16)
!729 = !DICompositeType(tag: DW_TAG_array_type, baseType: !347, size: 112, align: 8, elements: !730)
!730 = !{!731}
!731 = !DISubrange(count: 14)
!732 = !DIDerivedType(tag: DW_TAG_member, name: "ifa_netmask", scope: !716, file: !717, line: 37, baseType: !723, size: 64, align: 64, offset: 256)
!733 = !DIDerivedType(tag: DW_TAG_member, name: "ifa_ifu", scope: !716, file: !717, line: 46, baseType: !734, size: 64, align: 64, offset: 320)
!734 = !DICompositeType(tag: DW_TAG_union_type, scope: !716, file: !717, line: 38, size: 64, align: 64, elements: !735)
!735 = !{!736, !737}
!736 = !DIDerivedType(tag: DW_TAG_member, name: "ifu_broadaddr", scope: !734, file: !717, line: 44, baseType: !723, size: 64, align: 64)
!737 = !DIDerivedType(tag: DW_TAG_member, name: "ifu_dstaddr", scope: !734, file: !717, line: 45, baseType: !723, size: 64, align: 64)
!738 = !DIDerivedType(tag: DW_TAG_member, name: "ifa_data", scope: !716, file: !717, line: 56, baseType: !271, size: 64, align: 64, offset: 384)
!739 = !{!740, !742, !743, !744, !748, !750, !752}
!740 = !DIGlobalVariable(name: "max_safe_timeout", scope: !562, file: !1, line: 197, type: !741, isLocal: true, isDefinition: true, variable: i32* @uv__io_poll.max_safe_timeout)
!741 = !DIDerivedType(tag: DW_TAG_const_type, baseType: !284)
!742 = !DIGlobalVariable(name: "no_epoll_pwait", scope: !562, file: !1, line: 198, type: !284, isLocal: true, isDefinition: true, variable: i32* @uv__io_poll.no_epoll_pwait)
!743 = !DIGlobalVariable(name: "no_epoll_wait", scope: !562, file: !1, line: 199, type: !284, isLocal: true, isDefinition: true, variable: i32* @uv__io_poll.no_epoll_wait)
!744 = !DIGlobalVariable(name: "fast_clock_id", scope: !563, file: !1, line: 443, type: !745, isLocal: true, isDefinition: true, variable: i64* @uv__hrtime.fast_clock_id)
!745 = !DIDerivedType(tag: DW_TAG_typedef, name: "clock_t", file: !746, line: 59, baseType: !747)
!746 = !DIFile(filename: "/usr/include/time.h", directory: "/data/download/cmake/cmake-master/Utilities/cmlibuv")
!747 = !DIDerivedType(tag: DW_TAG_typedef, name: "__clock_t", file: !676, line: 135, baseType: !351)
!748 = !DIGlobalVariable(name: "no_clock_boottime", scope: !584, file: !1, line: 582, type: !749, isLocal: true, isDefinition: true, variable: i32* @uv_uptime.no_clock_boottime)
!749 = !DIDerivedType(tag: DW_TAG_volatile_type, baseType: !284)
!750 = !DIGlobalVariable(name: "model_marker", scope: !706, file: !1, line: 693, type: !751, isLocal: true, isDefinition: true, variable: [14 x i8]* @read_models.model_marker)
!751 = !DICompositeType(tag: DW_TAG_array_type, baseType: !640, size: 112, align: 8, elements: !730)
!752 = !DIGlobalVariable(name: "speed_marker", scope: !706, file: !1, line: 694, type: !753, isLocal: true, isDefinition: true, variable: [12 x i8]* @read_models.speed_marker)
!753 = !DICompositeType(tag: DW_TAG_array_type, baseType: !640, size: 96, align: 8, elements: !754)
!754 = !{!755}
!755 = !DISubrange(count: 12)
!756 = !{i32 2, !"Dwarf Version", i32 4}
!757 = !{i32 2, !"Debug Info Version", i32 3}
!758 = !{!"clang version 3.8.0 (tags/RELEASE_380/final)"}
!759 = !DILocalVariable(name: "loop", arg: 1, scope: !548, file: !1, line: 84, type: !358)
!760 = !DIExpression()
!761 = !DILocation(line: 84, column: 39, scope: !548)
!762 = !DILocalVariable(name: "fd", scope: !548, file: !1, line: 85, type: !284)
!763 = !DILocation(line: 85, column: 7, scope: !548)
!764 = !DILocation(line: 87, column: 8, scope: !548)
!765 = !DILocation(line: 87, column: 6, scope: !548)
!766 = !DILocation(line: 92, column: 7, scope: !767)
!767 = distinct !DILexicalBlock(scope: !548, file: !1, line: 92, column: 7)
!768 = !DILocation(line: 92, column: 10, scope: !767)
!769 = !DILocation(line: 92, column: 16, scope: !767)
!770 = !DILocation(line: 92, column: 20, scope: !771)
!771 = !DILexicalBlockFile(scope: !767, file: !1, discriminator: 1)
!772 = !DILocation(line: 92, column: 26, scope: !771)
!773 = !DILocation(line: 92, column: 36, scope: !771)
!774 = !DILocation(line: 92, column: 39, scope: !775)
!775 = !DILexicalBlockFile(scope: !767, file: !1, discriminator: 2)
!776 = !DILocation(line: 92, column: 45, scope: !775)
!777 = !DILocation(line: 92, column: 7, scope: !775)
!778 = !DILocation(line: 93, column: 10, scope: !779)
!779 = distinct !DILexicalBlock(scope: !767, file: !1, line: 92, column: 57)
!780 = !DILocation(line: 93, column: 8, scope: !779)
!781 = !DILocation(line: 95, column: 9, scope: !782)
!782 = distinct !DILexicalBlock(scope: !779, file: !1, line: 95, column: 9)
!783 = !DILocation(line: 95, column: 12, scope: !782)
!784 = !DILocation(line: 95, column: 9, scope: !779)
!785 = !DILocation(line: 96, column: 19, scope: !782)
!786 = !DILocation(line: 96, column: 7, scope: !782)
!787 = !DILocation(line: 97, column: 3, scope: !779)
!788 = !DILocation(line: 99, column: 22, scope: !548)
!789 = !DILocation(line: 99, column: 3, scope: !548)
!790 = !DILocation(line: 99, column: 9, scope: !548)
!791 = !DILocation(line: 99, column: 20, scope: !548)
!792 = !DILocation(line: 100, column: 3, scope: !548)
!793 = !DILocation(line: 100, column: 9, scope: !548)
!794 = !DILocation(line: 100, column: 20, scope: !548)
!795 = !DILocation(line: 101, column: 3, scope: !548)
!796 = !DILocation(line: 101, column: 9, scope: !548)
!797 = !DILocation(line: 101, column: 26, scope: !548)
!798 = !DILocation(line: 103, column: 7, scope: !799)
!799 = distinct !DILexicalBlock(scope: !548, file: !1, line: 103, column: 7)
!800 = !DILocation(line: 103, column: 10, scope: !799)
!801 = !DILocation(line: 103, column: 7, scope: !548)
!802 = !DILocation(line: 104, column: 13, scope: !799)
!803 = !DILocation(line: 104, column: 12, scope: !799)
!804 = !DILocation(line: 104, column: 5, scope: !799)
!805 = !DILocation(line: 106, column: 3, scope: !548)
!806 = !DILocation(line: 107, column: 1, scope: !548)
!807 = !DILocalVariable(name: "loop", arg: 1, scope: !552, file: !1, line: 110, type: !358)
!808 = !DILocation(line: 110, column: 28, scope: !552)
!809 = !DILocalVariable(name: "err", scope: !552, file: !1, line: 111, type: !284)
!810 = !DILocation(line: 111, column: 7, scope: !552)
!811 = !DILocalVariable(name: "old_watchers", scope: !552, file: !1, line: 112, type: !271)
!812 = !DILocation(line: 112, column: 9, scope: !552)
!813 = !DILocation(line: 114, column: 18, scope: !552)
!814 = !DILocation(line: 114, column: 24, scope: !552)
!815 = !DILocation(line: 114, column: 16, scope: !552)
!816 = !DILocation(line: 116, column: 13, scope: !552)
!817 = !DILocation(line: 116, column: 19, scope: !552)
!818 = !DILocation(line: 116, column: 3, scope: !552)
!819 = !DILocation(line: 117, column: 3, scope: !552)
!820 = !DILocation(line: 117, column: 9, scope: !552)
!821 = !DILocation(line: 117, column: 20, scope: !552)
!822 = !DILocation(line: 118, column: 28, scope: !552)
!823 = !DILocation(line: 118, column: 3, scope: !552)
!824 = !DILocation(line: 120, column: 32, scope: !552)
!825 = !DILocation(line: 120, column: 9, scope: !552)
!826 = !DILocation(line: 120, column: 7, scope: !552)
!827 = !DILocation(line: 121, column: 7, scope: !828)
!828 = distinct !DILexicalBlock(scope: !552, file: !1, line: 121, column: 7)
!829 = !DILocation(line: 121, column: 7, scope: !552)
!830 = !DILocation(line: 122, column: 12, scope: !828)
!831 = !DILocation(line: 122, column: 5, scope: !828)
!832 = !DILocation(line: 124, column: 27, scope: !552)
!833 = !DILocation(line: 124, column: 33, scope: !552)
!834 = !DILocation(line: 124, column: 10, scope: !552)
!835 = !DILocation(line: 124, column: 3, scope: !552)
!836 = !DILocation(line: 125, column: 1, scope: !552)
!837 = !DILocalVariable(name: "loop", arg: 1, scope: !553, file: !1, line: 128, type: !358)
!838 = !DILocation(line: 128, column: 42, scope: !553)
!839 = !DILocation(line: 129, column: 7, scope: !840)
!840 = distinct !DILexicalBlock(scope: !553, file: !1, line: 129, column: 7)
!841 = !DILocation(line: 129, column: 13, scope: !840)
!842 = !DILocation(line: 129, column: 24, scope: !840)
!843 = !DILocation(line: 129, column: 7, scope: !553)
!844 = !DILocation(line: 129, column: 31, scope: !845)
!845 = !DILexicalBlockFile(scope: !840, file: !1, discriminator: 1)
!846 = !DILocation(line: 130, column: 15, scope: !553)
!847 = !DILocation(line: 130, column: 22, scope: !553)
!848 = !DILocation(line: 130, column: 28, scope: !553)
!849 = !DILocation(line: 130, column: 3, scope: !553)
!850 = !DILocation(line: 131, column: 13, scope: !553)
!851 = !DILocation(line: 131, column: 19, scope: !553)
!852 = !DILocation(line: 131, column: 3, scope: !553)
!853 = !DILocation(line: 132, column: 3, scope: !553)
!854 = !DILocation(line: 132, column: 9, scope: !553)
!855 = !DILocation(line: 132, column: 20, scope: !553)
!856 = !DILocation(line: 133, column: 1, scope: !553)
!857 = !DILocation(line: 133, column: 1, scope: !858)
!858 = !DILexicalBlockFile(scope: !553, file: !1, discriminator: 1)
!859 = !DILocalVariable(name: "loop", arg: 1, scope: !556, file: !1, line: 136, type: !358)
!860 = !DILocation(line: 136, column: 44, scope: !556)
!861 = !DILocalVariable(name: "fd", arg: 2, scope: !556, file: !1, line: 136, type: !284)
!862 = !DILocation(line: 136, column: 54, scope: !556)
!863 = !DILocalVariable(name: "events", scope: !556, file: !1, line: 137, type: !272)
!864 = !DILocation(line: 137, column: 27, scope: !556)
!865 = !DILocalVariable(name: "dummy", scope: !556, file: !1, line: 138, type: !273)
!866 = !DILocation(line: 138, column: 26, scope: !556)
!867 = !DILocalVariable(name: "i", scope: !556, file: !1, line: 139, type: !283)
!868 = !DILocation(line: 139, column: 13, scope: !556)
!869 = !DILocalVariable(name: "nfds", scope: !556, file: !1, line: 140, type: !283)
!870 = !DILocation(line: 140, column: 13, scope: !556)
!871 = !DILocation(line: 142, column: 3, scope: !556)
!872 = !DILocation(line: 142, column: 3, scope: !873)
!873 = !DILexicalBlockFile(scope: !556, file: !1, discriminator: 1)
!874 = !DILocation(line: 142, column: 3, scope: !875)
!875 = !DILexicalBlockFile(scope: !556, file: !1, discriminator: 2)
!876 = !DILocation(line: 142, column: 3, scope: !877)
!877 = !DILexicalBlockFile(scope: !556, file: !1, discriminator: 3)
!878 = !DILocation(line: 144, column: 53, scope: !556)
!879 = !DILocation(line: 144, column: 59, scope: !556)
!880 = !DILocation(line: 144, column: 38, scope: !556)
!881 = !DILocation(line: 144, column: 44, scope: !556)
!882 = !DILocation(line: 144, column: 12, scope: !556)
!883 = !DILocation(line: 144, column: 10, scope: !556)
!884 = !DILocation(line: 145, column: 37, scope: !556)
!885 = !DILocation(line: 145, column: 43, scope: !556)
!886 = !DILocation(line: 145, column: 53, scope: !556)
!887 = !DILocation(line: 145, column: 22, scope: !556)
!888 = !DILocation(line: 145, column: 28, scope: !556)
!889 = !DILocation(line: 145, column: 10, scope: !556)
!890 = !DILocation(line: 145, column: 8, scope: !556)
!891 = !DILocation(line: 146, column: 7, scope: !892)
!892 = distinct !DILexicalBlock(scope: !556, file: !1, line: 146, column: 7)
!893 = !DILocation(line: 146, column: 14, scope: !892)
!894 = !DILocation(line: 146, column: 7, scope: !556)
!895 = !DILocation(line: 148, column: 12, scope: !896)
!896 = distinct !DILexicalBlock(scope: !892, file: !1, line: 148, column: 5)
!897 = !DILocation(line: 148, column: 10, scope: !896)
!898 = !DILocation(line: 148, column: 17, scope: !899)
!899 = !DILexicalBlockFile(scope: !900, file: !1, discriminator: 1)
!900 = distinct !DILexicalBlock(scope: !896, file: !1, line: 148, column: 5)
!901 = !DILocation(line: 148, column: 21, scope: !899)
!902 = !DILocation(line: 148, column: 19, scope: !899)
!903 = !DILocation(line: 148, column: 5, scope: !899)
!904 = !DILocation(line: 149, column: 24, scope: !905)
!905 = distinct !DILexicalBlock(scope: !900, file: !1, line: 149, column: 11)
!906 = !DILocation(line: 149, column: 17, scope: !905)
!907 = !DILocation(line: 149, column: 27, scope: !905)
!908 = !DILocation(line: 149, column: 11, scope: !905)
!909 = !DILocation(line: 149, column: 35, scope: !905)
!910 = !DILocation(line: 149, column: 32, scope: !905)
!911 = !DILocation(line: 149, column: 11, scope: !900)
!912 = !DILocation(line: 150, column: 16, scope: !905)
!913 = !DILocation(line: 150, column: 9, scope: !905)
!914 = !DILocation(line: 150, column: 19, scope: !905)
!915 = !DILocation(line: 150, column: 24, scope: !905)
!916 = !DILocation(line: 149, column: 35, scope: !917)
!917 = !DILexicalBlockFile(scope: !905, file: !1, discriminator: 1)
!918 = !DILocation(line: 148, column: 28, scope: !919)
!919 = !DILexicalBlockFile(scope: !900, file: !1, discriminator: 2)
!920 = !DILocation(line: 148, column: 5, scope: !919)
!921 = !DILocation(line: 150, column: 27, scope: !922)
!922 = !DILexicalBlockFile(scope: !896, file: !1, discriminator: 1)
!923 = !DILocation(line: 158, column: 7, scope: !924)
!924 = distinct !DILexicalBlock(scope: !556, file: !1, line: 158, column: 7)
!925 = !DILocation(line: 158, column: 13, scope: !924)
!926 = !DILocation(line: 158, column: 24, scope: !924)
!927 = !DILocation(line: 158, column: 7, scope: !556)
!928 = !DILocation(line: 162, column: 5, scope: !929)
!929 = distinct !DILexicalBlock(scope: !924, file: !1, line: 158, column: 30)
!930 = !DILocation(line: 163, column: 19, scope: !929)
!931 = !DILocation(line: 163, column: 25, scope: !929)
!932 = !DILocation(line: 163, column: 56, scope: !929)
!933 = !DILocation(line: 163, column: 5, scope: !929)
!934 = !DILocation(line: 164, column: 3, scope: !929)
!935 = !DILocation(line: 165, column: 1, scope: !556)
!936 = !DILocalVariable(name: "loop", arg: 1, scope: !559, file: !1, line: 168, type: !358)
!937 = !DILocation(line: 168, column: 32, scope: !559)
!938 = !DILocalVariable(name: "fd", arg: 2, scope: !559, file: !1, line: 168, type: !284)
!939 = !DILocation(line: 168, column: 42, scope: !559)
!940 = !DILocalVariable(name: "e", scope: !559, file: !1, line: 169, type: !273)
!941 = !DILocation(line: 169, column: 26, scope: !559)
!942 = !DILocalVariable(name: "rc", scope: !559, file: !1, line: 170, type: !284)
!943 = !DILocation(line: 170, column: 7, scope: !559)
!944 = !DILocation(line: 172, column: 5, scope: !559)
!945 = !DILocation(line: 172, column: 12, scope: !559)
!946 = !DILocation(line: 173, column: 5, scope: !559)
!947 = !DILocation(line: 173, column: 10, scope: !559)
!948 = !DILocation(line: 175, column: 6, scope: !559)
!949 = !DILocation(line: 176, column: 21, scope: !950)
!950 = distinct !DILexicalBlock(scope: !559, file: !1, line: 176, column: 7)
!951 = !DILocation(line: 176, column: 27, scope: !950)
!952 = !DILocation(line: 176, column: 58, scope: !950)
!953 = !DILocation(line: 176, column: 7, scope: !950)
!954 = !DILocation(line: 176, column: 7, scope: !559)
!955 = !DILocation(line: 177, column: 9, scope: !956)
!956 = distinct !DILexicalBlock(scope: !950, file: !1, line: 177, column: 9)
!957 = !DILocation(line: 177, column: 15, scope: !956)
!958 = !DILocation(line: 177, column: 9, scope: !950)
!959 = !DILocation(line: 178, column: 13, scope: !956)
!960 = !DILocation(line: 178, column: 12, scope: !956)
!961 = !DILocation(line: 178, column: 10, scope: !956)
!962 = !DILocation(line: 178, column: 7, scope: !956)
!963 = !DILocation(line: 177, column: 18, scope: !964)
!964 = !DILexicalBlockFile(scope: !956, file: !1, discriminator: 1)
!965 = !DILocation(line: 180, column: 7, scope: !966)
!966 = distinct !DILexicalBlock(scope: !559, file: !1, line: 180, column: 7)
!967 = !DILocation(line: 180, column: 10, scope: !966)
!968 = !DILocation(line: 180, column: 7, scope: !559)
!969 = !DILocation(line: 181, column: 23, scope: !970)
!970 = distinct !DILexicalBlock(scope: !966, file: !1, line: 181, column: 9)
!971 = !DILocation(line: 181, column: 29, scope: !970)
!972 = !DILocation(line: 181, column: 60, scope: !970)
!973 = !DILocation(line: 181, column: 9, scope: !970)
!974 = !DILocation(line: 181, column: 9, scope: !966)
!975 = !DILocation(line: 182, column: 7, scope: !970)
!976 = !DILocation(line: 181, column: 66, scope: !977)
!977 = !DILexicalBlockFile(scope: !970, file: !1, discriminator: 1)
!978 = !DILocation(line: 184, column: 10, scope: !559)
!979 = !DILocation(line: 184, column: 3, scope: !559)
!980 = !DILocalVariable(name: "loop", arg: 1, scope: !562, file: !1, line: 188, type: !358)
!981 = !DILocation(line: 188, column: 29, scope: !562)
!982 = !DILocalVariable(name: "timeout", arg: 2, scope: !562, file: !1, line: 188, type: !284)
!983 = !DILocation(line: 188, column: 39, scope: !562)
!984 = !DILocalVariable(name: "events", scope: !562, file: !1, line: 200, type: !985)
!985 = !DICompositeType(tag: DW_TAG_array_type, baseType: !273, size: 98304, align: 8, elements: !986)
!986 = !{!987}
!987 = !DISubrange(count: 1024)
!988 = !DILocation(line: 200, column: 26, scope: !562)
!989 = !DILocalVariable(name: "pe", scope: !562, file: !1, line: 201, type: !272)
!990 = !DILocation(line: 201, column: 27, scope: !562)
!991 = !DILocalVariable(name: "e", scope: !562, file: !1, line: 202, type: !273)
!992 = !DILocation(line: 202, column: 26, scope: !562)
!993 = !DILocalVariable(name: "real_timeout", scope: !562, file: !1, line: 203, type: !284)
!994 = !DILocation(line: 203, column: 7, scope: !562)
!995 = !DILocalVariable(name: "q", scope: !562, file: !1, line: 204, type: !293)
!996 = !DILocation(line: 204, column: 10, scope: !562)
!997 = !DILocalVariable(name: "w", scope: !562, file: !1, line: 205, type: !294)
!998 = !DILocation(line: 205, column: 13, scope: !562)
!999 = !DILocalVariable(name: "sigset", scope: !562, file: !1, line: 206, type: !1000)
!1000 = !DIDerivedType(tag: DW_TAG_typedef, name: "sigset_t", file: !1001, line: 37, baseType: !1002)
!1001 = !DIFile(filename: "/usr/include/x86_64-linux-gnu/sys/select.h", directory: "/data/download/cmake/cmake-master/Utilities/cmlibuv")
!1002 = !DIDerivedType(tag: DW_TAG_typedef, name: "__sigset_t", file: !1003, line: 30, baseType: !1004)
!1003 = !DIFile(filename: "/usr/include/x86_64-linux-gnu/bits/sigset.h", directory: "/data/download/cmake/cmake-master/Utilities/cmlibuv")
!1004 = !DICompositeType(tag: DW_TAG_structure_type, file: !1003, line: 27, size: 1024, align: 64, elements: !1005)
!1005 = !{!1006}
!1006 = !DIDerivedType(tag: DW_TAG_member, name: "__val", scope: !1004, file: !1003, line: 29, baseType: !1007, size: 1024, align: 64)
!1007 = !DICompositeType(tag: DW_TAG_array_type, baseType: !282, size: 1024, align: 64, elements: !515)
!1008 = !DILocation(line: 206, column: 12, scope: !562)
!1009 = !DILocalVariable(name: "sigmask", scope: !562, file: !1, line: 207, type: !281)
!1010 = !DILocation(line: 207, column: 12, scope: !562)
!1011 = !DILocalVariable(name: "base", scope: !562, file: !1, line: 208, type: !281)
!1012 = !DILocation(line: 208, column: 12, scope: !562)
!1013 = !DILocalVariable(name: "have_signals", scope: !562, file: !1, line: 209, type: !284)
!1014 = !DILocation(line: 209, column: 7, scope: !562)
!1015 = !DILocalVariable(name: "nevents", scope: !562, file: !1, line: 210, type: !284)
!1016 = !DILocation(line: 210, column: 7, scope: !562)
!1017 = !DILocalVariable(name: "count", scope: !562, file: !1, line: 211, type: !284)
!1018 = !DILocation(line: 211, column: 7, scope: !562)
!1019 = !DILocalVariable(name: "nfds", scope: !562, file: !1, line: 212, type: !284)
!1020 = !DILocation(line: 212, column: 7, scope: !562)
!1021 = !DILocalVariable(name: "fd", scope: !562, file: !1, line: 213, type: !284)
!1022 = !DILocation(line: 213, column: 7, scope: !562)
!1023 = !DILocalVariable(name: "op", scope: !562, file: !1, line: 214, type: !284)
!1024 = !DILocation(line: 214, column: 7, scope: !562)
!1025 = !DILocalVariable(name: "i", scope: !562, file: !1, line: 215, type: !284)
!1026 = !DILocation(line: 215, column: 7, scope: !562)
!1027 = !DILocation(line: 217, column: 7, scope: !1028)
!1028 = distinct !DILexicalBlock(scope: !562, file: !1, line: 217, column: 7)
!1029 = !DILocation(line: 217, column: 13, scope: !1028)
!1030 = !DILocation(line: 217, column: 18, scope: !1028)
!1031 = !DILocation(line: 217, column: 7, scope: !562)
!1032 = !DILocation(line: 218, column: 5, scope: !1033)
!1033 = distinct !DILexicalBlock(scope: !1028, file: !1, line: 217, column: 24)
!1034 = !DILocation(line: 218, column: 5, scope: !1035)
!1035 = !DILexicalBlockFile(scope: !1033, file: !1, discriminator: 1)
!1036 = !DILocation(line: 218, column: 5, scope: !1037)
!1037 = !DILexicalBlockFile(scope: !1033, file: !1, discriminator: 2)
!1038 = !DILocation(line: 218, column: 5, scope: !1039)
!1039 = !DILexicalBlockFile(scope: !1033, file: !1, discriminator: 3)
!1040 = !DILocation(line: 219, column: 5, scope: !1033)
!1041 = !DILocation(line: 222, column: 3, scope: !562)
!1042 = !DILocation(line: 222, column: 11, scope: !1043)
!1043 = !DILexicalBlockFile(scope: !562, file: !1, discriminator: 1)
!1044 = !DILocation(line: 222, column: 10, scope: !1043)
!1045 = !DILocation(line: 222, column: 3, scope: !1043)
!1046 = !DILocation(line: 223, column: 9, scope: !1047)
!1047 = distinct !DILexicalBlock(scope: !562, file: !1, line: 222, column: 46)
!1048 = !DILocation(line: 223, column: 7, scope: !1047)
!1049 = !DILocation(line: 224, column: 5, scope: !1047)
!1050 = !DILocation(line: 224, column: 5, scope: !1051)
!1051 = !DILexicalBlockFile(scope: !1052, file: !1, discriminator: 1)
!1052 = distinct !DILexicalBlock(scope: !1047, file: !1, line: 224, column: 5)
!1053 = !DILocation(line: 225, column: 5, scope: !1047)
!1054 = !DILocation(line: 225, column: 5, scope: !1055)
!1055 = !DILexicalBlockFile(scope: !1056, file: !1, discriminator: 1)
!1056 = distinct !DILexicalBlock(scope: !1047, file: !1, line: 225, column: 5)
!1057 = !DILocation(line: 227, column: 9, scope: !1047)
!1058 = !DILocation(line: 227, column: 7, scope: !1047)
!1059 = !DILocation(line: 228, column: 5, scope: !1047)
!1060 = !DILocation(line: 228, column: 5, scope: !1061)
!1061 = !DILexicalBlockFile(scope: !1047, file: !1, discriminator: 1)
!1062 = !DILocation(line: 228, column: 5, scope: !1063)
!1063 = !DILexicalBlockFile(scope: !1047, file: !1, discriminator: 2)
!1064 = !DILocation(line: 228, column: 5, scope: !1065)
!1065 = !DILexicalBlockFile(scope: !1047, file: !1, discriminator: 3)
!1066 = !DILocation(line: 229, column: 5, scope: !1047)
!1067 = !DILocation(line: 229, column: 5, scope: !1061)
!1068 = !DILocation(line: 229, column: 5, scope: !1063)
!1069 = !DILocation(line: 229, column: 5, scope: !1065)
!1070 = !DILocation(line: 230, column: 5, scope: !1047)
!1071 = !DILocation(line: 230, column: 5, scope: !1061)
!1072 = !DILocation(line: 230, column: 5, scope: !1063)
!1073 = !DILocation(line: 230, column: 5, scope: !1065)
!1074 = !DILocation(line: 232, column: 16, scope: !1047)
!1075 = !DILocation(line: 232, column: 19, scope: !1047)
!1076 = !DILocation(line: 232, column: 7, scope: !1047)
!1077 = !DILocation(line: 232, column: 14, scope: !1047)
!1078 = !DILocation(line: 233, column: 14, scope: !1047)
!1079 = !DILocation(line: 233, column: 17, scope: !1047)
!1080 = !DILocation(line: 233, column: 7, scope: !1047)
!1081 = !DILocation(line: 233, column: 12, scope: !1047)
!1082 = !DILocation(line: 235, column: 9, scope: !1083)
!1083 = distinct !DILexicalBlock(scope: !1047, file: !1, line: 235, column: 9)
!1084 = !DILocation(line: 235, column: 12, scope: !1083)
!1085 = !DILocation(line: 235, column: 19, scope: !1083)
!1086 = !DILocation(line: 235, column: 9, scope: !1047)
!1087 = !DILocation(line: 236, column: 10, scope: !1083)
!1088 = !DILocation(line: 236, column: 7, scope: !1083)
!1089 = !DILocation(line: 238, column: 10, scope: !1083)
!1090 = !DILocation(line: 243, column: 23, scope: !1091)
!1091 = distinct !DILexicalBlock(scope: !1047, file: !1, line: 243, column: 9)
!1092 = !DILocation(line: 243, column: 29, scope: !1091)
!1093 = !DILocation(line: 243, column: 41, scope: !1091)
!1094 = !DILocation(line: 243, column: 45, scope: !1091)
!1095 = !DILocation(line: 243, column: 48, scope: !1091)
!1096 = !DILocation(line: 243, column: 9, scope: !1091)
!1097 = !DILocation(line: 243, column: 9, scope: !1047)
!1098 = !DILocation(line: 244, column: 11, scope: !1099)
!1099 = distinct !DILexicalBlock(scope: !1100, file: !1, line: 244, column: 11)
!1100 = distinct !DILexicalBlock(scope: !1091, file: !1, line: 243, column: 57)
!1101 = !DILocation(line: 244, column: 17, scope: !1099)
!1102 = !DILocation(line: 244, column: 11, scope: !1100)
!1103 = !DILocation(line: 245, column: 9, scope: !1099)
!1104 = !DILocation(line: 247, column: 7, scope: !1100)
!1105 = !DILocation(line: 247, column: 7, scope: !1106)
!1106 = !DILexicalBlockFile(scope: !1100, file: !1, discriminator: 1)
!1107 = !DILocation(line: 247, column: 7, scope: !1108)
!1108 = !DILexicalBlockFile(scope: !1100, file: !1, discriminator: 2)
!1109 = !DILocation(line: 247, column: 7, scope: !1110)
!1110 = !DILexicalBlockFile(scope: !1100, file: !1, discriminator: 3)
!1111 = !DILocation(line: 250, column: 25, scope: !1112)
!1112 = distinct !DILexicalBlock(scope: !1100, file: !1, line: 250, column: 11)
!1113 = !DILocation(line: 250, column: 31, scope: !1112)
!1114 = !DILocation(line: 250, column: 62, scope: !1112)
!1115 = !DILocation(line: 250, column: 65, scope: !1112)
!1116 = !DILocation(line: 250, column: 11, scope: !1112)
!1117 = !DILocation(line: 250, column: 11, scope: !1100)
!1118 = !DILocation(line: 251, column: 9, scope: !1112)
!1119 = !DILocation(line: 252, column: 5, scope: !1100)
!1120 = !DILocation(line: 254, column: 17, scope: !1047)
!1121 = !DILocation(line: 254, column: 20, scope: !1047)
!1122 = !DILocation(line: 254, column: 5, scope: !1047)
!1123 = !DILocation(line: 254, column: 8, scope: !1047)
!1124 = !DILocation(line: 254, column: 15, scope: !1047)
!1125 = !DILocation(line: 222, column: 3, scope: !1126)
!1126 = !DILexicalBlockFile(scope: !562, file: !1, discriminator: 2)
!1127 = !DILocation(line: 257, column: 11, scope: !562)
!1128 = !DILocation(line: 258, column: 7, scope: !1129)
!1129 = distinct !DILexicalBlock(scope: !562, file: !1, line: 258, column: 7)
!1130 = !DILocation(line: 258, column: 13, scope: !1129)
!1131 = !DILocation(line: 258, column: 19, scope: !1129)
!1132 = !DILocation(line: 258, column: 7, scope: !562)
!1133 = !DILocation(line: 259, column: 5, scope: !1134)
!1134 = distinct !DILexicalBlock(scope: !1129, file: !1, line: 258, column: 44)
!1135 = !DILocation(line: 260, column: 5, scope: !1134)
!1136 = !DILocation(line: 261, column: 13, scope: !1134)
!1137 = !DILocation(line: 262, column: 3, scope: !1134)
!1138 = !DILocation(line: 264, column: 3, scope: !562)
!1139 = !DILocation(line: 264, column: 3, scope: !1043)
!1140 = !DILocation(line: 264, column: 3, scope: !1126)
!1141 = !DILocation(line: 264, column: 3, scope: !1142)
!1142 = !DILexicalBlockFile(scope: !562, file: !1, discriminator: 3)
!1143 = !DILocation(line: 265, column: 10, scope: !562)
!1144 = !DILocation(line: 265, column: 16, scope: !562)
!1145 = !DILocation(line: 265, column: 8, scope: !562)
!1146 = !DILocation(line: 266, column: 9, scope: !562)
!1147 = !DILocation(line: 267, column: 18, scope: !562)
!1148 = !DILocation(line: 267, column: 16, scope: !562)
!1149 = !DILocation(line: 269, column: 3, scope: !562)
!1150 = !DILocation(line: 276, column: 9, scope: !1151)
!1151 = distinct !DILexicalBlock(scope: !1152, file: !1, line: 276, column: 9)
!1152 = distinct !DILexicalBlock(scope: !1153, file: !1, line: 269, column: 12)
!1153 = distinct !DILexicalBlock(scope: !1154, file: !1, line: 269, column: 3)
!1154 = distinct !DILexicalBlock(scope: !562, file: !1, line: 269, column: 3)
!1155 = !DILocation(line: 276, column: 17, scope: !1151)
!1156 = !DILocation(line: 276, column: 22, scope: !1151)
!1157 = !DILocation(line: 276, column: 25, scope: !1158)
!1158 = !DILexicalBlockFile(scope: !1151, file: !1, discriminator: 1)
!1159 = !DILocation(line: 276, column: 40, scope: !1158)
!1160 = !DILocation(line: 276, column: 9, scope: !1158)
!1161 = !DILocation(line: 277, column: 11, scope: !1162)
!1162 = distinct !DILexicalBlock(scope: !1151, file: !1, line: 277, column: 11)
!1163 = !DILocation(line: 277, column: 11, scope: !1151)
!1164 = !DILocation(line: 278, column: 9, scope: !1162)
!1165 = !DILocation(line: 277, column: 51, scope: !1166)
!1166 = !DILexicalBlockFile(scope: !1162, file: !1, discriminator: 1)
!1167 = !DILocation(line: 280, column: 9, scope: !1168)
!1168 = distinct !DILexicalBlock(scope: !1152, file: !1, line: 280, column: 9)
!1169 = !DILocation(line: 280, column: 23, scope: !1168)
!1170 = !DILocation(line: 280, column: 28, scope: !1168)
!1171 = !DILocation(line: 280, column: 32, scope: !1172)
!1172 = !DILexicalBlockFile(scope: !1168, file: !1, discriminator: 1)
!1173 = !DILocation(line: 280, column: 40, scope: !1172)
!1174 = !DILocation(line: 280, column: 45, scope: !1172)
!1175 = !DILocation(line: 280, column: 48, scope: !1176)
!1176 = !DILexicalBlockFile(scope: !1168, file: !1, discriminator: 2)
!1177 = !DILocation(line: 280, column: 63, scope: !1176)
!1178 = !DILocation(line: 280, column: 9, scope: !1176)
!1179 = !DILocation(line: 281, column: 30, scope: !1180)
!1180 = distinct !DILexicalBlock(scope: !1168, file: !1, line: 280, column: 70)
!1181 = !DILocation(line: 281, column: 36, scope: !1180)
!1182 = !DILocation(line: 282, column: 30, scope: !1180)
!1183 = !DILocation(line: 284, column: 30, scope: !1180)
!1184 = !DILocation(line: 285, column: 30, scope: !1180)
!1185 = !DILocation(line: 281, column: 14, scope: !1180)
!1186 = !DILocation(line: 281, column: 12, scope: !1180)
!1187 = !DILocation(line: 286, column: 11, scope: !1188)
!1188 = distinct !DILexicalBlock(scope: !1180, file: !1, line: 286, column: 11)
!1189 = !DILocation(line: 286, column: 16, scope: !1188)
!1190 = !DILocation(line: 286, column: 22, scope: !1188)
!1191 = !DILocation(line: 286, column: 25, scope: !1192)
!1192 = !DILexicalBlockFile(scope: !1188, file: !1, discriminator: 1)
!1193 = !DILocation(line: 286, column: 31, scope: !1192)
!1194 = !DILocation(line: 286, column: 11, scope: !1192)
!1195 = !DILocation(line: 287, column: 24, scope: !1188)
!1196 = !DILocation(line: 287, column: 9, scope: !1188)
!1197 = !DILocation(line: 288, column: 5, scope: !1180)
!1198 = !DILocation(line: 289, column: 29, scope: !1199)
!1199 = distinct !DILexicalBlock(scope: !1168, file: !1, line: 288, column: 12)
!1200 = !DILocation(line: 289, column: 35, scope: !1199)
!1201 = !DILocation(line: 290, column: 29, scope: !1199)
!1202 = !DILocation(line: 292, column: 29, scope: !1199)
!1203 = !DILocation(line: 289, column: 14, scope: !1199)
!1204 = !DILocation(line: 289, column: 12, scope: !1199)
!1205 = !DILocation(line: 293, column: 11, scope: !1206)
!1206 = distinct !DILexicalBlock(scope: !1199, file: !1, line: 293, column: 11)
!1207 = !DILocation(line: 293, column: 16, scope: !1206)
!1208 = !DILocation(line: 293, column: 22, scope: !1206)
!1209 = !DILocation(line: 293, column: 25, scope: !1210)
!1210 = !DILexicalBlockFile(scope: !1206, file: !1, discriminator: 1)
!1211 = !DILocation(line: 293, column: 31, scope: !1210)
!1212 = !DILocation(line: 293, column: 11, scope: !1210)
!1213 = !DILocation(line: 294, column: 23, scope: !1206)
!1214 = !DILocation(line: 294, column: 9, scope: !1206)
!1215 = !DILocation(line: 297, column: 9, scope: !1216)
!1216 = distinct !DILexicalBlock(scope: !1152, file: !1, line: 297, column: 9)
!1217 = !DILocation(line: 297, column: 17, scope: !1216)
!1218 = !DILocation(line: 297, column: 22, scope: !1216)
!1219 = !DILocation(line: 297, column: 25, scope: !1220)
!1220 = !DILexicalBlockFile(scope: !1216, file: !1, discriminator: 1)
!1221 = !DILocation(line: 297, column: 40, scope: !1220)
!1222 = !DILocation(line: 297, column: 9, scope: !1220)
!1223 = !DILocation(line: 298, column: 11, scope: !1224)
!1224 = distinct !DILexicalBlock(scope: !1216, file: !1, line: 298, column: 11)
!1225 = !DILocation(line: 298, column: 11, scope: !1216)
!1226 = !DILocation(line: 299, column: 9, scope: !1224)
!1227 = !DILocation(line: 298, column: 53, scope: !1228)
!1228 = !DILexicalBlockFile(scope: !1224, file: !1, discriminator: 1)
!1229 = !DILocation(line: 305, column: 5, scope: !1152)
!1230 = !DILocalVariable(name: "_saved_errno", scope: !1231, file: !1, line: 305, type: !284)
!1231 = distinct !DILexicalBlock(scope: !1152, file: !1, line: 305, column: 5)
!1232 = !DILocation(line: 305, column: 5, scope: !1231)
!1233 = !DILocation(line: 305, column: 5, scope: !1234)
!1234 = !DILexicalBlockFile(scope: !1231, file: !1, discriminator: 1)
!1235 = !DILocation(line: 305, column: 5, scope: !1236)
!1236 = !DILexicalBlockFile(scope: !1237, file: !1, discriminator: 2)
!1237 = distinct !DILexicalBlock(scope: !1231, file: !1, line: 305, column: 5)
!1238 = !DILocation(line: 305, column: 5, scope: !1239)
!1239 = !DILexicalBlockFile(scope: !1231, file: !1, discriminator: 3)
!1240 = !DILocation(line: 307, column: 9, scope: !1241)
!1241 = distinct !DILexicalBlock(scope: !1152, file: !1, line: 307, column: 9)
!1242 = !DILocation(line: 307, column: 14, scope: !1241)
!1243 = !DILocation(line: 307, column: 9, scope: !1152)
!1244 = !DILocation(line: 308, column: 7, scope: !1245)
!1245 = distinct !DILexicalBlock(scope: !1241, file: !1, line: 307, column: 20)
!1246 = !DILocation(line: 308, column: 7, scope: !1247)
!1247 = !DILexicalBlockFile(scope: !1245, file: !1, discriminator: 1)
!1248 = !DILocation(line: 308, column: 7, scope: !1249)
!1249 = !DILexicalBlockFile(scope: !1245, file: !1, discriminator: 2)
!1250 = !DILocation(line: 308, column: 7, scope: !1251)
!1251 = !DILexicalBlockFile(scope: !1245, file: !1, discriminator: 3)
!1252 = !DILocation(line: 310, column: 11, scope: !1253)
!1253 = distinct !DILexicalBlock(scope: !1245, file: !1, line: 310, column: 11)
!1254 = !DILocation(line: 310, column: 19, scope: !1253)
!1255 = !DILocation(line: 310, column: 11, scope: !1245)
!1256 = !DILocation(line: 311, column: 9, scope: !1253)
!1257 = !DILocation(line: 316, column: 7, scope: !1245)
!1258 = !DILocation(line: 319, column: 9, scope: !1259)
!1259 = distinct !DILexicalBlock(scope: !1152, file: !1, line: 319, column: 9)
!1260 = !DILocation(line: 319, column: 14, scope: !1259)
!1261 = !DILocation(line: 319, column: 9, scope: !1152)
!1262 = !DILocation(line: 320, column: 11, scope: !1263)
!1263 = distinct !DILexicalBlock(scope: !1264, file: !1, line: 320, column: 11)
!1264 = distinct !DILexicalBlock(scope: !1259, file: !1, line: 319, column: 21)
!1265 = !DILocation(line: 320, column: 17, scope: !1263)
!1266 = !DILocation(line: 320, column: 11, scope: !1264)
!1267 = !DILocation(line: 322, column: 9, scope: !1268)
!1268 = distinct !DILexicalBlock(scope: !1263, file: !1, line: 320, column: 28)
!1269 = !DILocation(line: 322, column: 9, scope: !1270)
!1270 = !DILexicalBlockFile(scope: !1268, file: !1, discriminator: 1)
!1271 = !DILocation(line: 322, column: 9, scope: !1272)
!1272 = !DILexicalBlockFile(scope: !1268, file: !1, discriminator: 2)
!1273 = !DILocation(line: 322, column: 9, scope: !1274)
!1274 = !DILexicalBlockFile(scope: !1268, file: !1, discriminator: 3)
!1275 = !DILocation(line: 322, column: 9, scope: !1276)
!1276 = !DILexicalBlockFile(scope: !1268, file: !1, discriminator: 4)
!1277 = !DILocation(line: 323, column: 9, scope: !1268)
!1278 = !DILocation(line: 326, column: 11, scope: !1279)
!1279 = distinct !DILexicalBlock(scope: !1264, file: !1, line: 326, column: 11)
!1280 = !DILocation(line: 326, column: 17, scope: !1279)
!1281 = !DILocation(line: 326, column: 11, scope: !1264)
!1282 = !DILocation(line: 327, column: 9, scope: !1279)
!1283 = !DILocation(line: 329, column: 11, scope: !1284)
!1284 = distinct !DILexicalBlock(scope: !1264, file: !1, line: 329, column: 11)
!1285 = !DILocation(line: 329, column: 19, scope: !1284)
!1286 = !DILocation(line: 329, column: 11, scope: !1264)
!1287 = !DILocation(line: 330, column: 9, scope: !1284)
!1288 = !DILocation(line: 332, column: 11, scope: !1289)
!1289 = distinct !DILexicalBlock(scope: !1264, file: !1, line: 332, column: 11)
!1290 = !DILocation(line: 332, column: 19, scope: !1289)
!1291 = !DILocation(line: 332, column: 11, scope: !1264)
!1292 = !DILocation(line: 333, column: 9, scope: !1289)
!1293 = !DILocation(line: 336, column: 7, scope: !1264)
!1294 = !DILocation(line: 339, column: 18, scope: !1152)
!1295 = !DILocation(line: 340, column: 13, scope: !1152)
!1296 = !DILocation(line: 342, column: 5, scope: !1152)
!1297 = !DILocation(line: 342, column: 5, scope: !1298)
!1298 = !DILexicalBlockFile(scope: !1152, file: !1, discriminator: 1)
!1299 = !DILocation(line: 342, column: 5, scope: !1300)
!1300 = !DILexicalBlockFile(scope: !1152, file: !1, discriminator: 2)
!1301 = !DILocation(line: 342, column: 5, scope: !1302)
!1302 = !DILexicalBlockFile(scope: !1152, file: !1, discriminator: 3)
!1303 = !DILocation(line: 343, column: 47, scope: !1152)
!1304 = !DILocation(line: 343, column: 39, scope: !1152)
!1305 = !DILocation(line: 343, column: 20, scope: !1152)
!1306 = !DILocation(line: 343, column: 26, scope: !1152)
!1307 = !DILocation(line: 343, column: 5, scope: !1152)
!1308 = !DILocation(line: 343, column: 11, scope: !1152)
!1309 = !DILocation(line: 343, column: 37, scope: !1152)
!1310 = !DILocation(line: 344, column: 63, scope: !1152)
!1311 = !DILocation(line: 344, column: 51, scope: !1152)
!1312 = !DILocation(line: 344, column: 43, scope: !1152)
!1313 = !DILocation(line: 344, column: 20, scope: !1152)
!1314 = !DILocation(line: 344, column: 26, scope: !1152)
!1315 = !DILocation(line: 344, column: 36, scope: !1152)
!1316 = !DILocation(line: 344, column: 5, scope: !1152)
!1317 = !DILocation(line: 344, column: 11, scope: !1152)
!1318 = !DILocation(line: 344, column: 41, scope: !1152)
!1319 = !DILocation(line: 345, column: 12, scope: !1320)
!1320 = distinct !DILexicalBlock(scope: !1152, file: !1, line: 345, column: 5)
!1321 = !DILocation(line: 345, column: 10, scope: !1320)
!1322 = !DILocation(line: 345, column: 17, scope: !1323)
!1323 = !DILexicalBlockFile(scope: !1324, file: !1, discriminator: 1)
!1324 = distinct !DILexicalBlock(scope: !1320, file: !1, line: 345, column: 5)
!1325 = !DILocation(line: 345, column: 21, scope: !1323)
!1326 = !DILocation(line: 345, column: 19, scope: !1323)
!1327 = !DILocation(line: 345, column: 5, scope: !1323)
!1328 = !DILocation(line: 346, column: 12, scope: !1329)
!1329 = distinct !DILexicalBlock(scope: !1324, file: !1, line: 345, column: 32)
!1330 = !DILocation(line: 346, column: 21, scope: !1329)
!1331 = !DILocation(line: 346, column: 19, scope: !1329)
!1332 = !DILocation(line: 346, column: 10, scope: !1329)
!1333 = !DILocation(line: 347, column: 12, scope: !1329)
!1334 = !DILocation(line: 347, column: 16, scope: !1329)
!1335 = !DILocation(line: 347, column: 10, scope: !1329)
!1336 = !DILocation(line: 350, column: 11, scope: !1337)
!1337 = distinct !DILexicalBlock(scope: !1329, file: !1, line: 350, column: 11)
!1338 = !DILocation(line: 350, column: 14, scope: !1337)
!1339 = !DILocation(line: 350, column: 11, scope: !1329)
!1340 = !DILocation(line: 351, column: 9, scope: !1337)
!1341 = !DILocation(line: 353, column: 7, scope: !1329)
!1342 = !DILocation(line: 353, column: 7, scope: !1343)
!1343 = !DILexicalBlockFile(scope: !1329, file: !1, discriminator: 1)
!1344 = !DILocation(line: 353, column: 7, scope: !1345)
!1345 = !DILexicalBlockFile(scope: !1329, file: !1, discriminator: 2)
!1346 = !DILocation(line: 353, column: 7, scope: !1347)
!1347 = !DILexicalBlockFile(scope: !1329, file: !1, discriminator: 3)
!1348 = !DILocation(line: 354, column: 7, scope: !1329)
!1349 = !DILocation(line: 354, column: 7, scope: !1343)
!1350 = !DILocation(line: 354, column: 7, scope: !1345)
!1351 = !DILocation(line: 354, column: 7, scope: !1347)
!1352 = !DILocation(line: 356, column: 26, scope: !1329)
!1353 = !DILocation(line: 356, column: 11, scope: !1329)
!1354 = !DILocation(line: 356, column: 17, scope: !1329)
!1355 = !DILocation(line: 356, column: 9, scope: !1329)
!1356 = !DILocation(line: 358, column: 11, scope: !1357)
!1357 = distinct !DILexicalBlock(scope: !1329, file: !1, line: 358, column: 11)
!1358 = !DILocation(line: 358, column: 13, scope: !1357)
!1359 = !DILocation(line: 358, column: 11, scope: !1329)
!1360 = !DILocation(line: 364, column: 23, scope: !1361)
!1361 = distinct !DILexicalBlock(scope: !1357, file: !1, line: 358, column: 22)
!1362 = !DILocation(line: 364, column: 29, scope: !1361)
!1363 = !DILocation(line: 364, column: 60, scope: !1361)
!1364 = !DILocation(line: 364, column: 64, scope: !1361)
!1365 = !DILocation(line: 364, column: 9, scope: !1361)
!1366 = !DILocation(line: 365, column: 9, scope: !1361)
!1367 = !DILocation(line: 373, column: 21, scope: !1329)
!1368 = !DILocation(line: 373, column: 24, scope: !1329)
!1369 = !DILocation(line: 373, column: 32, scope: !1329)
!1370 = !DILocation(line: 373, column: 42, scope: !1329)
!1371 = !DILocation(line: 373, column: 7, scope: !1329)
!1372 = !DILocation(line: 373, column: 11, scope: !1329)
!1373 = !DILocation(line: 373, column: 18, scope: !1329)
!1374 = !DILocation(line: 390, column: 11, scope: !1375)
!1375 = distinct !DILexicalBlock(scope: !1329, file: !1, line: 390, column: 11)
!1376 = !DILocation(line: 390, column: 15, scope: !1375)
!1377 = !DILocation(line: 390, column: 22, scope: !1375)
!1378 = !DILocation(line: 390, column: 33, scope: !1375)
!1379 = !DILocation(line: 390, column: 36, scope: !1380)
!1380 = !DILexicalBlockFile(scope: !1375, file: !1, discriminator: 1)
!1381 = !DILocation(line: 390, column: 40, scope: !1380)
!1382 = !DILocation(line: 390, column: 47, scope: !1380)
!1383 = !DILocation(line: 390, column: 11, scope: !1380)
!1384 = !DILocation(line: 391, column: 23, scope: !1375)
!1385 = !DILocation(line: 391, column: 26, scope: !1375)
!1386 = !DILocation(line: 391, column: 34, scope: !1375)
!1387 = !DILocation(line: 391, column: 9, scope: !1375)
!1388 = !DILocation(line: 391, column: 13, scope: !1375)
!1389 = !DILocation(line: 391, column: 20, scope: !1375)
!1390 = !DILocation(line: 393, column: 11, scope: !1391)
!1391 = distinct !DILexicalBlock(scope: !1329, file: !1, line: 393, column: 11)
!1392 = !DILocation(line: 393, column: 15, scope: !1391)
!1393 = !DILocation(line: 393, column: 22, scope: !1391)
!1394 = !DILocation(line: 393, column: 11, scope: !1329)
!1395 = !DILocation(line: 397, column: 13, scope: !1396)
!1396 = distinct !DILexicalBlock(scope: !1397, file: !1, line: 397, column: 13)
!1397 = distinct !DILexicalBlock(scope: !1391, file: !1, line: 393, column: 28)
!1398 = !DILocation(line: 397, column: 19, scope: !1396)
!1399 = !DILocation(line: 397, column: 25, scope: !1396)
!1400 = !DILocation(line: 397, column: 15, scope: !1396)
!1401 = !DILocation(line: 397, column: 13, scope: !1397)
!1402 = !DILocation(line: 398, column: 24, scope: !1396)
!1403 = !DILocation(line: 398, column: 11, scope: !1396)
!1404 = !DILocation(line: 400, column: 11, scope: !1396)
!1405 = !DILocation(line: 400, column: 14, scope: !1396)
!1406 = !DILocation(line: 400, column: 17, scope: !1396)
!1407 = !DILocation(line: 400, column: 23, scope: !1396)
!1408 = !DILocation(line: 400, column: 26, scope: !1396)
!1409 = !DILocation(line: 400, column: 30, scope: !1396)
!1410 = !DILocation(line: 402, column: 16, scope: !1397)
!1411 = !DILocation(line: 403, column: 7, scope: !1397)
!1412 = !DILocation(line: 404, column: 5, scope: !1329)
!1413 = !DILocation(line: 345, column: 28, scope: !1414)
!1414 = !DILexicalBlockFile(scope: !1324, file: !1, discriminator: 2)
!1415 = !DILocation(line: 345, column: 5, scope: !1414)
!1416 = !DILocation(line: 406, column: 9, scope: !1417)
!1417 = distinct !DILexicalBlock(scope: !1152, file: !1, line: 406, column: 9)
!1418 = !DILocation(line: 406, column: 22, scope: !1417)
!1419 = !DILocation(line: 406, column: 9, scope: !1152)
!1420 = !DILocation(line: 407, column: 7, scope: !1417)
!1421 = !DILocation(line: 407, column: 13, scope: !1417)
!1422 = !DILocation(line: 407, column: 31, scope: !1417)
!1423 = !DILocation(line: 407, column: 34, scope: !1417)
!1424 = !DILocation(line: 407, column: 41, scope: !1417)
!1425 = !DILocation(line: 407, column: 47, scope: !1417)
!1426 = !DILocation(line: 409, column: 20, scope: !1152)
!1427 = !DILocation(line: 409, column: 26, scope: !1152)
!1428 = !DILocation(line: 409, column: 5, scope: !1152)
!1429 = !DILocation(line: 409, column: 11, scope: !1152)
!1430 = !DILocation(line: 409, column: 37, scope: !1152)
!1431 = !DILocation(line: 410, column: 20, scope: !1152)
!1432 = !DILocation(line: 410, column: 26, scope: !1152)
!1433 = !DILocation(line: 410, column: 36, scope: !1152)
!1434 = !DILocation(line: 410, column: 5, scope: !1152)
!1435 = !DILocation(line: 410, column: 11, scope: !1152)
!1436 = !DILocation(line: 410, column: 41, scope: !1152)
!1437 = !DILocation(line: 412, column: 9, scope: !1438)
!1438 = distinct !DILexicalBlock(scope: !1152, file: !1, line: 412, column: 9)
!1439 = !DILocation(line: 412, column: 22, scope: !1438)
!1440 = !DILocation(line: 412, column: 9, scope: !1152)
!1441 = !DILocation(line: 413, column: 7, scope: !1438)
!1442 = !DILocation(line: 415, column: 9, scope: !1443)
!1443 = distinct !DILexicalBlock(scope: !1152, file: !1, line: 415, column: 9)
!1444 = !DILocation(line: 415, column: 17, scope: !1443)
!1445 = !DILocation(line: 415, column: 9, scope: !1152)
!1446 = !DILocation(line: 416, column: 11, scope: !1447)
!1447 = distinct !DILexicalBlock(scope: !1448, file: !1, line: 416, column: 11)
!1448 = distinct !DILexicalBlock(scope: !1443, file: !1, line: 415, column: 23)
!1449 = !DILocation(line: 416, column: 16, scope: !1447)
!1450 = !DILocation(line: 416, column: 38, scope: !1447)
!1451 = !DILocation(line: 416, column: 41, scope: !1452)
!1452 = !DILexicalBlockFile(scope: !1447, file: !1, discriminator: 1)
!1453 = !DILocation(line: 416, column: 49, scope: !1452)
!1454 = !DILocation(line: 416, column: 11, scope: !1452)
!1455 = !DILocation(line: 418, column: 17, scope: !1456)
!1456 = distinct !DILexicalBlock(scope: !1447, file: !1, line: 416, column: 55)
!1457 = !DILocation(line: 419, column: 9, scope: !1456)
!1458 = !DILocation(line: 421, column: 7, scope: !1448)
!1459 = !DILocation(line: 424, column: 9, scope: !1460)
!1460 = distinct !DILexicalBlock(scope: !1152, file: !1, line: 424, column: 9)
!1461 = !DILocation(line: 424, column: 17, scope: !1460)
!1462 = !DILocation(line: 424, column: 9, scope: !1152)
!1463 = !DILocation(line: 425, column: 7, scope: !1460)
!1464 = !DILocation(line: 427, column: 9, scope: !1465)
!1465 = distinct !DILexicalBlock(scope: !1152, file: !1, line: 427, column: 9)
!1466 = !DILocation(line: 427, column: 17, scope: !1465)
!1467 = !DILocation(line: 427, column: 9, scope: !1152)
!1468 = !DILocation(line: 428, column: 7, scope: !1465)
!1469 = !DILocation(line: 427, column: 21, scope: !1470)
!1470 = !DILexicalBlockFile(scope: !1465, file: !1, discriminator: 1)
!1471 = !DILocation(line: 431, column: 5, scope: !1152)
!1472 = !DILocation(line: 431, column: 5, scope: !1298)
!1473 = !DILocation(line: 431, column: 5, scope: !1300)
!1474 = !DILocation(line: 431, column: 5, scope: !1302)
!1475 = !DILocation(line: 433, column: 22, scope: !1152)
!1476 = !DILocation(line: 433, column: 28, scope: !1152)
!1477 = !DILocation(line: 433, column: 35, scope: !1152)
!1478 = !DILocation(line: 433, column: 33, scope: !1152)
!1479 = !DILocation(line: 433, column: 18, scope: !1152)
!1480 = !DILocation(line: 434, column: 9, scope: !1481)
!1481 = distinct !DILexicalBlock(scope: !1152, file: !1, line: 434, column: 9)
!1482 = !DILocation(line: 434, column: 22, scope: !1481)
!1483 = !DILocation(line: 434, column: 9, scope: !1152)
!1484 = !DILocation(line: 435, column: 7, scope: !1481)
!1485 = !DILocation(line: 437, column: 15, scope: !1152)
!1486 = !DILocation(line: 437, column: 13, scope: !1152)
!1487 = !DILocation(line: 269, column: 3, scope: !1488)
!1488 = !DILexicalBlockFile(scope: !1153, file: !1, discriminator: 1)
!1489 = !DILocation(line: 439, column: 1, scope: !562)
!1490 = !DILocalVariable(name: "loop", arg: 1, scope: !641, file: !26, line: 306, type: !358)
!1491 = !DILocation(line: 306, column: 1, scope: !641)
!1492 = !DILocation(line: 309, column: 16, scope: !641)
!1493 = !DILocation(line: 309, column: 42, scope: !641)
!1494 = !DILocation(line: 309, column: 3, scope: !641)
!1495 = !DILocation(line: 309, column: 9, scope: !641)
!1496 = !DILocation(line: 309, column: 14, scope: !641)
!1497 = !DILocation(line: 310, column: 1, scope: !641)
!1498 = !DILocalVariable(name: "type", arg: 1, scope: !563, file: !1, line: 442, type: !566)
!1499 = !DILocation(line: 442, column: 36, scope: !563)
!1500 = !DILocalVariable(name: "t", scope: !563, file: !1, line: 444, type: !1501)
!1501 = !DICompositeType(tag: DW_TAG_structure_type, name: "timespec", file: !746, line: 120, size: 128, align: 64, elements: !1502)
!1502 = !{!1503, !1505}
!1503 = !DIDerivedType(tag: DW_TAG_member, name: "tv_sec", scope: !1501, file: !746, line: 122, baseType: !1504, size: 64, align: 64)
!1504 = !DIDerivedType(tag: DW_TAG_typedef, name: "__time_t", file: !676, line: 139, baseType: !351)
!1505 = !DIDerivedType(tag: DW_TAG_member, name: "tv_nsec", scope: !1501, file: !746, line: 123, baseType: !1506, size: 64, align: 64, offset: 64)
!1506 = !DIDerivedType(tag: DW_TAG_typedef, name: "__syscall_slong_t", file: !676, line: 175, baseType: !351)
!1507 = !DILocation(line: 444, column: 19, scope: !563)
!1508 = !DILocalVariable(name: "clock_id", scope: !563, file: !1, line: 445, type: !745)
!1509 = !DILocation(line: 445, column: 11, scope: !563)
!1510 = !DILocation(line: 455, column: 7, scope: !1511)
!1511 = distinct !DILexicalBlock(scope: !563, file: !1, line: 455, column: 7)
!1512 = !DILocation(line: 455, column: 12, scope: !1511)
!1513 = !DILocation(line: 455, column: 29, scope: !1511)
!1514 = !DILocation(line: 455, column: 32, scope: !1515)
!1515 = !DILexicalBlockFile(scope: !1511, file: !1, discriminator: 1)
!1516 = !DILocation(line: 455, column: 46, scope: !1515)
!1517 = !DILocation(line: 455, column: 7, scope: !1515)
!1518 = !DILocation(line: 456, column: 9, scope: !1519)
!1519 = distinct !DILexicalBlock(scope: !1520, file: !1, line: 456, column: 9)
!1520 = distinct !DILexicalBlock(scope: !1511, file: !1, line: 455, column: 53)
!1521 = !DILocation(line: 456, column: 50, scope: !1519)
!1522 = !DILocation(line: 456, column: 55, scope: !1519)
!1523 = !DILocation(line: 457, column: 11, scope: !1519)
!1524 = !DILocation(line: 457, column: 19, scope: !1519)
!1525 = !DILocation(line: 456, column: 9, scope: !1526)
!1526 = !DILexicalBlockFile(scope: !1520, file: !1, discriminator: 1)
!1527 = !DILocation(line: 458, column: 21, scope: !1528)
!1528 = distinct !DILexicalBlock(scope: !1519, file: !1, line: 457, column: 39)
!1529 = !DILocation(line: 459, column: 5, scope: !1528)
!1530 = !DILocation(line: 460, column: 21, scope: !1531)
!1531 = distinct !DILexicalBlock(scope: !1519, file: !1, line: 459, column: 12)
!1532 = !DILocation(line: 462, column: 3, scope: !1520)
!1533 = !DILocation(line: 464, column: 12, scope: !563)
!1534 = !DILocation(line: 465, column: 7, scope: !1535)
!1535 = distinct !DILexicalBlock(scope: !563, file: !1, line: 465, column: 7)
!1536 = !DILocation(line: 465, column: 12, scope: !1535)
!1537 = !DILocation(line: 465, column: 7, scope: !563)
!1538 = !DILocation(line: 466, column: 16, scope: !1535)
!1539 = !DILocation(line: 466, column: 14, scope: !1535)
!1540 = !DILocation(line: 466, column: 5, scope: !1535)
!1541 = !DILocation(line: 468, column: 21, scope: !1542)
!1542 = distinct !DILexicalBlock(scope: !563, file: !1, line: 468, column: 7)
!1543 = !DILocation(line: 468, column: 7, scope: !1542)
!1544 = !DILocation(line: 468, column: 7, scope: !563)
!1545 = !DILocation(line: 469, column: 5, scope: !1542)
!1546 = !DILocation(line: 471, column: 12, scope: !563)
!1547 = !DILocation(line: 471, column: 19, scope: !563)
!1548 = !DILocation(line: 471, column: 40, scope: !563)
!1549 = !DILocation(line: 471, column: 36, scope: !563)
!1550 = !DILocation(line: 471, column: 3, scope: !563)
!1551 = !DILocation(line: 472, column: 1, scope: !563)
!1552 = !DILocalVariable(name: "avg", arg: 1, scope: !567, file: !1, line: 475, type: !570)
!1553 = !DILocation(line: 475, column: 24, scope: !567)
!1554 = !DILocalVariable(name: "info", scope: !567, file: !1, line: 476, type: !1555)
!1555 = !DICompositeType(tag: DW_TAG_structure_type, name: "sysinfo", file: !1556, line: 7, size: 896, align: 64, elements: !1557)
!1556 = !DIFile(filename: "/usr/include/linux/sysinfo.h", directory: "/data/download/cmake/cmake-master/Utilities/cmlibuv")
!1557 = !{!1558, !1561, !1566, !1567, !1568, !1569, !1570, !1571, !1572, !1575, !1576, !1577, !1578, !1580}
!1558 = !DIDerivedType(tag: DW_TAG_member, name: "uptime", scope: !1555, file: !1556, line: 8, baseType: !1559, size: 64, align: 64)
!1559 = !DIDerivedType(tag: DW_TAG_typedef, name: "__kernel_long_t", file: !1560, line: 14, baseType: !351)
!1560 = !DIFile(filename: "/usr/include/asm-generic/posix_types.h", directory: "/data/download/cmake/cmake-master/Utilities/cmlibuv")
!1561 = !DIDerivedType(tag: DW_TAG_member, name: "loads", scope: !1555, file: !1556, line: 9, baseType: !1562, size: 192, align: 64, offset: 64)
!1562 = !DICompositeType(tag: DW_TAG_array_type, baseType: !1563, size: 192, align: 64, elements: !1564)
!1563 = !DIDerivedType(tag: DW_TAG_typedef, name: "__kernel_ulong_t", file: !1560, line: 15, baseType: !282)
!1564 = !{!1565}
!1565 = !DISubrange(count: 3)
!1566 = !DIDerivedType(tag: DW_TAG_member, name: "totalram", scope: !1555, file: !1556, line: 10, baseType: !1563, size: 64, align: 64, offset: 256)
!1567 = !DIDerivedType(tag: DW_TAG_member, name: "freeram", scope: !1555, file: !1556, line: 11, baseType: !1563, size: 64, align: 64, offset: 320)
!1568 = !DIDerivedType(tag: DW_TAG_member, name: "sharedram", scope: !1555, file: !1556, line: 12, baseType: !1563, size: 64, align: 64, offset: 384)
!1569 = !DIDerivedType(tag: DW_TAG_member, name: "bufferram", scope: !1555, file: !1556, line: 13, baseType: !1563, size: 64, align: 64, offset: 448)
!1570 = !DIDerivedType(tag: DW_TAG_member, name: "totalswap", scope: !1555, file: !1556, line: 14, baseType: !1563, size: 64, align: 64, offset: 512)
!1571 = !DIDerivedType(tag: DW_TAG_member, name: "freeswap", scope: !1555, file: !1556, line: 15, baseType: !1563, size: 64, align: 64, offset: 576)
!1572 = !DIDerivedType(tag: DW_TAG_member, name: "procs", scope: !1555, file: !1556, line: 16, baseType: !1573, size: 16, align: 16, offset: 640)
!1573 = !DIDerivedType(tag: DW_TAG_typedef, name: "__u16", file: !1574, line: 23, baseType: !500)
!1574 = !DIFile(filename: "/usr/include/asm-generic/int-ll64.h", directory: "/data/download/cmake/cmake-master/Utilities/cmlibuv")
!1575 = !DIDerivedType(tag: DW_TAG_member, name: "pad", scope: !1555, file: !1556, line: 17, baseType: !1573, size: 16, align: 16, offset: 656)
!1576 = !DIDerivedType(tag: DW_TAG_member, name: "totalhigh", scope: !1555, file: !1556, line: 18, baseType: !1563, size: 64, align: 64, offset: 704)
!1577 = !DIDerivedType(tag: DW_TAG_member, name: "freehigh", scope: !1555, file: !1556, line: 19, baseType: !1563, size: 64, align: 64, offset: 768)
!1578 = !DIDerivedType(tag: DW_TAG_member, name: "mem_unit", scope: !1555, file: !1556, line: 20, baseType: !1579, size: 32, align: 32, offset: 832)
!1579 = !DIDerivedType(tag: DW_TAG_typedef, name: "__u32", file: !1574, line: 26, baseType: !279)
!1580 = !DIDerivedType(tag: DW_TAG_member, name: "_f", scope: !1555, file: !1556, line: 21, baseType: !1581, align: 8, offset: 864)
!1581 = !DICompositeType(tag: DW_TAG_array_type, baseType: !347, align: 8, elements: !1582)
!1582 = !{!1583}
!1583 = !DISubrange(count: 0)
!1584 = !DILocation(line: 476, column: 18, scope: !567)
!1585 = !DILocation(line: 478, column: 7, scope: !1586)
!1586 = distinct !DILexicalBlock(scope: !567, file: !1, line: 478, column: 7)
!1587 = !DILocation(line: 478, column: 22, scope: !1586)
!1588 = !DILocation(line: 478, column: 7, scope: !567)
!1589 = !DILocation(line: 478, column: 27, scope: !1590)
!1590 = !DILexicalBlockFile(scope: !1586, file: !1, discriminator: 1)
!1591 = !DILocation(line: 480, column: 26, scope: !567)
!1592 = !DILocation(line: 480, column: 21, scope: !567)
!1593 = !DILocation(line: 480, column: 12, scope: !567)
!1594 = !DILocation(line: 480, column: 35, scope: !567)
!1595 = !DILocation(line: 480, column: 3, scope: !567)
!1596 = !DILocation(line: 480, column: 10, scope: !567)
!1597 = !DILocation(line: 481, column: 26, scope: !567)
!1598 = !DILocation(line: 481, column: 21, scope: !567)
!1599 = !DILocation(line: 481, column: 12, scope: !567)
!1600 = !DILocation(line: 481, column: 35, scope: !567)
!1601 = !DILocation(line: 481, column: 3, scope: !567)
!1602 = !DILocation(line: 481, column: 10, scope: !567)
!1603 = !DILocation(line: 482, column: 26, scope: !567)
!1604 = !DILocation(line: 482, column: 21, scope: !567)
!1605 = !DILocation(line: 482, column: 12, scope: !567)
!1606 = !DILocation(line: 482, column: 35, scope: !567)
!1607 = !DILocation(line: 482, column: 3, scope: !567)
!1608 = !DILocation(line: 482, column: 10, scope: !567)
!1609 = !DILocation(line: 483, column: 1, scope: !567)
!1610 = !DILocation(line: 483, column: 1, scope: !1611)
!1611 = !DILexicalBlockFile(scope: !567, file: !1, discriminator: 1)
!1612 = !DILocalVariable(name: "buffer", arg: 1, scope: !571, file: !1, line: 486, type: !491)
!1613 = !DILocation(line: 486, column: 22, scope: !571)
!1614 = !DILocalVariable(name: "size", arg: 2, scope: !571, file: !1, line: 486, type: !574)
!1615 = !DILocation(line: 486, column: 38, scope: !571)
!1616 = !DILocalVariable(name: "n", scope: !571, file: !1, line: 487, type: !1617)
!1617 = !DIDerivedType(tag: DW_TAG_typedef, name: "ssize_t", file: !647, line: 102, baseType: !1618)
!1618 = !DIDerivedType(tag: DW_TAG_typedef, name: "__ssize_t", file: !676, line: 172, baseType: !351)
!1619 = !DILocation(line: 487, column: 11, scope: !571)
!1620 = !DILocation(line: 489, column: 7, scope: !1621)
!1621 = distinct !DILexicalBlock(scope: !571, file: !1, line: 489, column: 7)
!1622 = !DILocation(line: 489, column: 14, scope: !1621)
!1623 = !DILocation(line: 489, column: 22, scope: !1621)
!1624 = !DILocation(line: 489, column: 25, scope: !1625)
!1625 = !DILexicalBlockFile(scope: !1621, file: !1, discriminator: 1)
!1626 = !DILocation(line: 489, column: 30, scope: !1625)
!1627 = !DILocation(line: 489, column: 38, scope: !1625)
!1628 = !DILocation(line: 489, column: 42, scope: !1629)
!1629 = !DILexicalBlockFile(scope: !1621, file: !1, discriminator: 2)
!1630 = !DILocation(line: 489, column: 41, scope: !1629)
!1631 = !DILocation(line: 489, column: 47, scope: !1629)
!1632 = !DILocation(line: 489, column: 7, scope: !1629)
!1633 = !DILocation(line: 490, column: 5, scope: !1621)
!1634 = !DILocation(line: 492, column: 8, scope: !571)
!1635 = !DILocation(line: 492, column: 7, scope: !571)
!1636 = !DILocation(line: 492, column: 13, scope: !571)
!1637 = !DILocation(line: 492, column: 5, scope: !571)
!1638 = !DILocation(line: 493, column: 7, scope: !1639)
!1639 = distinct !DILexicalBlock(scope: !571, file: !1, line: 493, column: 7)
!1640 = !DILocation(line: 493, column: 9, scope: !1639)
!1641 = !DILocation(line: 493, column: 7, scope: !571)
!1642 = !DILocation(line: 494, column: 36, scope: !1639)
!1643 = !DILocation(line: 494, column: 44, scope: !1639)
!1644 = !DILocation(line: 494, column: 9, scope: !1639)
!1645 = !DILocation(line: 494, column: 7, scope: !1639)
!1646 = !DILocation(line: 494, column: 5, scope: !1639)
!1647 = !DILocation(line: 496, column: 7, scope: !1648)
!1648 = distinct !DILexicalBlock(scope: !571, file: !1, line: 496, column: 7)
!1649 = !DILocation(line: 496, column: 9, scope: !1648)
!1650 = !DILocation(line: 496, column: 7, scope: !571)
!1651 = !DILocation(line: 497, column: 13, scope: !1648)
!1652 = !DILocation(line: 497, column: 12, scope: !1648)
!1653 = !DILocation(line: 497, column: 5, scope: !1648)
!1654 = !DILocation(line: 499, column: 10, scope: !571)
!1655 = !DILocation(line: 499, column: 3, scope: !571)
!1656 = !DILocation(line: 499, column: 13, scope: !571)
!1657 = !DILocation(line: 500, column: 11, scope: !571)
!1658 = !DILocation(line: 500, column: 4, scope: !571)
!1659 = !DILocation(line: 500, column: 9, scope: !571)
!1660 = !DILocation(line: 502, column: 3, scope: !571)
!1661 = !DILocation(line: 503, column: 1, scope: !571)
!1662 = !DILocalVariable(name: "info", scope: !577, file: !1, line: 507, type: !1555)
!1663 = !DILocation(line: 507, column: 18, scope: !577)
!1664 = !DILocation(line: 509, column: 7, scope: !1665)
!1665 = distinct !DILexicalBlock(scope: !577, file: !1, line: 509, column: 7)
!1666 = !DILocation(line: 509, column: 22, scope: !1665)
!1667 = !DILocation(line: 509, column: 7, scope: !577)
!1668 = !DILocation(line: 510, column: 28, scope: !1665)
!1669 = !DILocation(line: 510, column: 43, scope: !1665)
!1670 = !DILocation(line: 510, column: 38, scope: !1665)
!1671 = !DILocation(line: 510, column: 36, scope: !1665)
!1672 = !DILocation(line: 510, column: 5, scope: !1665)
!1673 = !DILocation(line: 511, column: 3, scope: !577)
!1674 = !DILocation(line: 512, column: 1, scope: !577)
!1675 = !DILocalVariable(name: "info", scope: !580, file: !1, line: 516, type: !1555)
!1676 = !DILocation(line: 516, column: 18, scope: !580)
!1677 = !DILocation(line: 518, column: 7, scope: !1678)
!1678 = distinct !DILexicalBlock(scope: !580, file: !1, line: 518, column: 7)
!1679 = !DILocation(line: 518, column: 22, scope: !1678)
!1680 = !DILocation(line: 518, column: 7, scope: !580)
!1681 = !DILocation(line: 519, column: 28, scope: !1678)
!1682 = !DILocation(line: 519, column: 44, scope: !1678)
!1683 = !DILocation(line: 519, column: 39, scope: !1678)
!1684 = !DILocation(line: 519, column: 37, scope: !1678)
!1685 = !DILocation(line: 519, column: 5, scope: !1678)
!1686 = !DILocation(line: 520, column: 3, scope: !580)
!1687 = !DILocation(line: 521, column: 1, scope: !580)
!1688 = !DILocalVariable(name: "rss", arg: 1, scope: !581, file: !1, line: 524, type: !574)
!1689 = !DILocation(line: 524, column: 36, scope: !581)
!1690 = !DILocalVariable(name: "buf", scope: !581, file: !1, line: 525, type: !1691)
!1691 = !DICompositeType(tag: DW_TAG_array_type, baseType: !347, size: 8192, align: 8, elements: !986)
!1692 = !DILocation(line: 525, column: 8, scope: !581)
!1693 = !DILocalVariable(name: "s", scope: !581, file: !1, line: 526, type: !639)
!1694 = !DILocation(line: 526, column: 15, scope: !581)
!1695 = !DILocalVariable(name: "n", scope: !581, file: !1, line: 527, type: !1617)
!1696 = !DILocation(line: 527, column: 11, scope: !581)
!1697 = !DILocalVariable(name: "val", scope: !581, file: !1, line: 528, type: !351)
!1698 = !DILocation(line: 528, column: 8, scope: !581)
!1699 = !DILocalVariable(name: "fd", scope: !581, file: !1, line: 529, type: !284)
!1700 = !DILocation(line: 529, column: 7, scope: !581)
!1701 = !DILocalVariable(name: "i", scope: !581, file: !1, line: 530, type: !284)
!1702 = !DILocation(line: 530, column: 7, scope: !581)
!1703 = !DILocation(line: 532, column: 3, scope: !581)
!1704 = !DILocation(line: 533, column: 10, scope: !581)
!1705 = !DILocation(line: 533, column: 8, scope: !581)
!1706 = !DILocation(line: 533, column: 5, scope: !581)
!1707 = !DILocation(line: 534, column: 10, scope: !581)
!1708 = !DILocation(line: 534, column: 13, scope: !581)
!1709 = !DILocation(line: 534, column: 19, scope: !581)
!1710 = !DILocation(line: 534, column: 22, scope: !1711)
!1711 = !DILexicalBlockFile(scope: !581, file: !1, discriminator: 1)
!1712 = !DILocation(line: 534, column: 28, scope: !1711)
!1713 = !DILocation(line: 533, column: 5, scope: !1711)
!1714 = !DILocation(line: 536, column: 7, scope: !1715)
!1715 = distinct !DILexicalBlock(scope: !581, file: !1, line: 536, column: 7)
!1716 = !DILocation(line: 536, column: 10, scope: !1715)
!1717 = !DILocation(line: 536, column: 7, scope: !581)
!1718 = !DILocation(line: 537, column: 13, scope: !1715)
!1719 = !DILocation(line: 537, column: 12, scope: !1715)
!1720 = !DILocation(line: 537, column: 5, scope: !1715)
!1721 = !DILocation(line: 539, column: 3, scope: !581)
!1722 = !DILocation(line: 540, column: 14, scope: !581)
!1723 = !DILocation(line: 540, column: 18, scope: !581)
!1724 = !DILocation(line: 540, column: 9, scope: !581)
!1725 = !DILocation(line: 540, column: 7, scope: !581)
!1726 = !DILocation(line: 540, column: 5, scope: !581)
!1727 = !DILocation(line: 541, column: 10, scope: !581)
!1728 = !DILocation(line: 541, column: 12, scope: !581)
!1729 = !DILocation(line: 541, column: 18, scope: !581)
!1730 = !DILocation(line: 541, column: 21, scope: !1711)
!1731 = !DILocation(line: 541, column: 27, scope: !1711)
!1732 = !DILocation(line: 540, column: 5, scope: !1711)
!1733 = !DILocation(line: 543, column: 13, scope: !581)
!1734 = !DILocation(line: 543, column: 3, scope: !581)
!1735 = !DILocation(line: 544, column: 7, scope: !1736)
!1736 = distinct !DILexicalBlock(scope: !581, file: !1, line: 544, column: 7)
!1737 = !DILocation(line: 544, column: 9, scope: !1736)
!1738 = !DILocation(line: 544, column: 7, scope: !581)
!1739 = !DILocation(line: 545, column: 13, scope: !1736)
!1740 = !DILocation(line: 545, column: 12, scope: !1736)
!1741 = !DILocation(line: 545, column: 5, scope: !1736)
!1742 = !DILocation(line: 546, column: 7, scope: !581)
!1743 = !DILocation(line: 546, column: 3, scope: !581)
!1744 = !DILocation(line: 546, column: 10, scope: !581)
!1745 = !DILocation(line: 548, column: 14, scope: !581)
!1746 = !DILocation(line: 548, column: 7, scope: !581)
!1747 = !DILocation(line: 548, column: 5, scope: !581)
!1748 = !DILocation(line: 549, column: 7, scope: !1749)
!1749 = distinct !DILexicalBlock(scope: !581, file: !1, line: 549, column: 7)
!1750 = !DILocation(line: 549, column: 9, scope: !1749)
!1751 = !DILocation(line: 549, column: 7, scope: !581)
!1752 = !DILocation(line: 550, column: 5, scope: !1749)
!1753 = !DILocation(line: 552, column: 5, scope: !581)
!1754 = !DILocation(line: 553, column: 8, scope: !1755)
!1755 = distinct !DILexicalBlock(scope: !581, file: !1, line: 553, column: 7)
!1756 = !DILocation(line: 553, column: 7, scope: !1755)
!1757 = !DILocation(line: 553, column: 10, scope: !1755)
!1758 = !DILocation(line: 553, column: 7, scope: !581)
!1759 = !DILocation(line: 554, column: 5, scope: !1755)
!1760 = !DILocation(line: 556, column: 14, scope: !581)
!1761 = !DILocation(line: 556, column: 7, scope: !581)
!1762 = !DILocation(line: 556, column: 5, scope: !581)
!1763 = !DILocation(line: 557, column: 7, scope: !1764)
!1764 = distinct !DILexicalBlock(scope: !581, file: !1, line: 557, column: 7)
!1765 = !DILocation(line: 557, column: 9, scope: !1764)
!1766 = !DILocation(line: 557, column: 7, scope: !581)
!1767 = !DILocation(line: 558, column: 5, scope: !1764)
!1768 = !DILocation(line: 560, column: 10, scope: !1769)
!1769 = distinct !DILexicalBlock(scope: !581, file: !1, line: 560, column: 3)
!1770 = !DILocation(line: 560, column: 8, scope: !1769)
!1771 = !DILocation(line: 560, column: 15, scope: !1772)
!1772 = !DILexicalBlockFile(scope: !1773, file: !1, discriminator: 1)
!1773 = distinct !DILexicalBlock(scope: !1769, file: !1, line: 560, column: 3)
!1774 = !DILocation(line: 560, column: 17, scope: !1772)
!1775 = !DILocation(line: 560, column: 3, scope: !1772)
!1776 = !DILocation(line: 561, column: 16, scope: !1777)
!1777 = distinct !DILexicalBlock(scope: !1773, file: !1, line: 560, column: 29)
!1778 = !DILocation(line: 561, column: 18, scope: !1777)
!1779 = !DILocation(line: 561, column: 9, scope: !1777)
!1780 = !DILocation(line: 561, column: 7, scope: !1777)
!1781 = !DILocation(line: 562, column: 9, scope: !1782)
!1782 = distinct !DILexicalBlock(scope: !1777, file: !1, line: 562, column: 9)
!1783 = !DILocation(line: 562, column: 11, scope: !1782)
!1784 = !DILocation(line: 562, column: 9, scope: !1777)
!1785 = !DILocation(line: 563, column: 7, scope: !1782)
!1786 = !DILocation(line: 564, column: 3, scope: !1777)
!1787 = !DILocation(line: 560, column: 25, scope: !1788)
!1788 = !DILexicalBlockFile(scope: !1773, file: !1, discriminator: 2)
!1789 = !DILocation(line: 560, column: 3, scope: !1788)
!1790 = !DILocation(line: 566, column: 3, scope: !581)
!1791 = !DILocation(line: 566, column: 9, scope: !581)
!1792 = !DILocation(line: 567, column: 16, scope: !581)
!1793 = !DILocation(line: 567, column: 9, scope: !581)
!1794 = !DILocation(line: 567, column: 7, scope: !581)
!1795 = !DILocation(line: 568, column: 7, scope: !1796)
!1796 = distinct !DILexicalBlock(scope: !581, file: !1, line: 568, column: 7)
!1797 = !DILocation(line: 568, column: 13, scope: !1796)
!1798 = !DILocation(line: 568, column: 7, scope: !581)
!1799 = !DILocation(line: 569, column: 5, scope: !1796)
!1800 = !DILocation(line: 570, column: 7, scope: !1801)
!1801 = distinct !DILexicalBlock(scope: !581, file: !1, line: 570, column: 7)
!1802 = !DILocation(line: 570, column: 11, scope: !1801)
!1803 = !DILocation(line: 570, column: 7, scope: !581)
!1804 = !DILocation(line: 571, column: 5, scope: !1801)
!1805 = !DILocation(line: 573, column: 10, scope: !581)
!1806 = !DILocation(line: 573, column: 16, scope: !581)
!1807 = !DILocation(line: 573, column: 14, scope: !581)
!1808 = !DILocation(line: 573, column: 4, scope: !581)
!1809 = !DILocation(line: 573, column: 8, scope: !581)
!1810 = !DILocation(line: 574, column: 3, scope: !581)
!1811 = !DILocation(line: 577, column: 3, scope: !581)
!1812 = !DILocation(line: 578, column: 1, scope: !581)
!1813 = !DILocalVariable(name: "uptime", arg: 1, scope: !584, file: !1, line: 581, type: !570)
!1814 = !DILocation(line: 581, column: 23, scope: !584)
!1815 = !DILocalVariable(name: "now", scope: !584, file: !1, line: 583, type: !1501)
!1816 = !DILocation(line: 583, column: 19, scope: !584)
!1817 = !DILocalVariable(name: "r", scope: !584, file: !1, line: 584, type: !284)
!1818 = !DILocation(line: 584, column: 7, scope: !584)
!1819 = !DILocation(line: 590, column: 7, scope: !1820)
!1820 = distinct !DILexicalBlock(scope: !584, file: !1, line: 590, column: 7)
!1821 = !DILocation(line: 590, column: 7, scope: !584)
!1822 = !DILocation(line: 590, column: 26, scope: !1823)
!1823 = !DILexicalBlockFile(scope: !1820, file: !1, discriminator: 1)
!1824 = !DILocation(line: 591, column: 16, scope: !1825)
!1825 = distinct !DILexicalBlock(scope: !1820, file: !1, line: 590, column: 26)
!1826 = !DILocation(line: 591, column: 14, scope: !1825)
!1827 = !DILocation(line: 592, column: 3, scope: !1825)
!1828 = !DILocation(line: 593, column: 17, scope: !1829)
!1829 = distinct !DILexicalBlock(scope: !1820, file: !1, line: 593, column: 12)
!1830 = !DILocation(line: 593, column: 15, scope: !1829)
!1831 = !DILocation(line: 593, column: 54, scope: !1829)
!1832 = !DILocation(line: 593, column: 57, scope: !1833)
!1833 = !DILexicalBlockFile(scope: !1829, file: !1, discriminator: 1)
!1834 = !DILocation(line: 593, column: 63, scope: !1833)
!1835 = !DILocation(line: 593, column: 12, scope: !1833)
!1836 = !DILocation(line: 594, column: 23, scope: !1837)
!1837 = distinct !DILexicalBlock(scope: !1829, file: !1, line: 593, column: 74)
!1838 = !DILocation(line: 595, column: 5, scope: !1837)
!1839 = !DILocation(line: 598, column: 7, scope: !1840)
!1840 = distinct !DILexicalBlock(scope: !584, file: !1, line: 598, column: 7)
!1841 = !DILocation(line: 598, column: 7, scope: !584)
!1842 = !DILocation(line: 599, column: 13, scope: !1840)
!1843 = !DILocation(line: 599, column: 12, scope: !1840)
!1844 = !DILocation(line: 599, column: 5, scope: !1840)
!1845 = !DILocation(line: 601, column: 17, scope: !584)
!1846 = !DILocation(line: 601, column: 13, scope: !584)
!1847 = !DILocation(line: 601, column: 4, scope: !584)
!1848 = !DILocation(line: 601, column: 11, scope: !584)
!1849 = !DILocation(line: 602, column: 3, scope: !584)
!1850 = !DILocation(line: 603, column: 1, scope: !584)
!1851 = !DILocalVariable(name: "cpu_infos", arg: 1, scope: !587, file: !1, line: 628, type: !590)
!1852 = !DILocation(line: 628, column: 33, scope: !587)
!1853 = !DILocalVariable(name: "count", arg: 2, scope: !587, file: !1, line: 628, type: !605)
!1854 = !DILocation(line: 628, column: 49, scope: !587)
!1855 = !DILocalVariable(name: "numcpus", scope: !587, file: !1, line: 629, type: !279)
!1856 = !DILocation(line: 629, column: 16, scope: !587)
!1857 = !DILocalVariable(name: "ci", scope: !587, file: !1, line: 630, type: !591)
!1858 = !DILocation(line: 630, column: 18, scope: !587)
!1859 = !DILocalVariable(name: "err", scope: !587, file: !1, line: 631, type: !284)
!1860 = !DILocation(line: 631, column: 7, scope: !587)
!1861 = !DILocalVariable(name: "statfile_fp", scope: !587, file: !1, line: 632, type: !645)
!1862 = !DILocation(line: 632, column: 9, scope: !587)
!1863 = !DILocation(line: 634, column: 4, scope: !587)
!1864 = !DILocation(line: 634, column: 14, scope: !587)
!1865 = !DILocation(line: 635, column: 4, scope: !587)
!1866 = !DILocation(line: 635, column: 10, scope: !587)
!1867 = !DILocation(line: 637, column: 17, scope: !587)
!1868 = !DILocation(line: 637, column: 15, scope: !587)
!1869 = !DILocation(line: 638, column: 7, scope: !1870)
!1870 = distinct !DILexicalBlock(scope: !587, file: !1, line: 638, column: 7)
!1871 = !DILocation(line: 638, column: 19, scope: !1870)
!1872 = !DILocation(line: 638, column: 7, scope: !587)
!1873 = !DILocation(line: 639, column: 13, scope: !1870)
!1874 = !DILocation(line: 639, column: 12, scope: !1870)
!1875 = !DILocation(line: 639, column: 5, scope: !1870)
!1876 = !DILocation(line: 641, column: 21, scope: !587)
!1877 = !DILocation(line: 641, column: 9, scope: !587)
!1878 = !DILocation(line: 641, column: 7, scope: !587)
!1879 = !DILocation(line: 642, column: 7, scope: !1880)
!1880 = distinct !DILexicalBlock(scope: !587, file: !1, line: 642, column: 7)
!1881 = !DILocation(line: 642, column: 11, scope: !1880)
!1882 = !DILocation(line: 642, column: 7, scope: !587)
!1883 = !DILocation(line: 643, column: 5, scope: !1880)
!1884 = !DILocation(line: 645, column: 7, scope: !587)
!1885 = !DILocation(line: 646, column: 19, scope: !587)
!1886 = !DILocation(line: 646, column: 8, scope: !587)
!1887 = !DILocation(line: 646, column: 6, scope: !587)
!1888 = !DILocation(line: 647, column: 7, scope: !1889)
!1889 = distinct !DILexicalBlock(scope: !587, file: !1, line: 647, column: 7)
!1890 = !DILocation(line: 647, column: 10, scope: !1889)
!1891 = !DILocation(line: 647, column: 7, scope: !587)
!1892 = !DILocation(line: 648, column: 5, scope: !1889)
!1893 = !DILocation(line: 650, column: 21, scope: !587)
!1894 = !DILocation(line: 650, column: 30, scope: !587)
!1895 = !DILocation(line: 650, column: 9, scope: !587)
!1896 = !DILocation(line: 650, column: 7, scope: !587)
!1897 = !DILocation(line: 651, column: 7, scope: !1898)
!1898 = distinct !DILexicalBlock(scope: !587, file: !1, line: 651, column: 7)
!1899 = !DILocation(line: 651, column: 11, scope: !1898)
!1900 = !DILocation(line: 651, column: 7, scope: !587)
!1901 = !DILocation(line: 652, column: 22, scope: !1898)
!1902 = !DILocation(line: 652, column: 35, scope: !1898)
!1903 = !DILocation(line: 652, column: 44, scope: !1898)
!1904 = !DILocation(line: 652, column: 11, scope: !1898)
!1905 = !DILocation(line: 652, column: 9, scope: !1898)
!1906 = !DILocation(line: 652, column: 5, scope: !1898)
!1907 = !DILocation(line: 654, column: 7, scope: !1908)
!1908 = distinct !DILexicalBlock(scope: !587, file: !1, line: 654, column: 7)
!1909 = !DILocation(line: 654, column: 7, scope: !587)
!1910 = !DILocation(line: 655, column: 22, scope: !1911)
!1911 = distinct !DILexicalBlock(scope: !1908, file: !1, line: 654, column: 12)
!1912 = !DILocation(line: 655, column: 26, scope: !1911)
!1913 = !DILocation(line: 655, column: 5, scope: !1911)
!1914 = !DILocation(line: 656, column: 5, scope: !1911)
!1915 = !DILocation(line: 662, column: 7, scope: !1916)
!1916 = distinct !DILexicalBlock(scope: !587, file: !1, line: 662, column: 7)
!1917 = !DILocation(line: 662, column: 13, scope: !1916)
!1918 = !DILocation(line: 662, column: 19, scope: !1916)
!1919 = !DILocation(line: 662, column: 7, scope: !587)
!1920 = !DILocation(line: 663, column: 17, scope: !1916)
!1921 = !DILocation(line: 663, column: 26, scope: !1916)
!1922 = !DILocation(line: 663, column: 5, scope: !1916)
!1923 = !DILocation(line: 665, column: 16, scope: !587)
!1924 = !DILocation(line: 665, column: 4, scope: !587)
!1925 = !DILocation(line: 665, column: 14, scope: !587)
!1926 = !DILocation(line: 666, column: 12, scope: !587)
!1927 = !DILocation(line: 666, column: 4, scope: !587)
!1928 = !DILocation(line: 666, column: 10, scope: !587)
!1929 = !DILocation(line: 667, column: 7, scope: !587)
!1930 = !DILocation(line: 667, column: 3, scope: !587)
!1931 = !DILocation(line: 671, column: 14, scope: !1932)
!1932 = distinct !DILexicalBlock(scope: !587, file: !1, line: 671, column: 7)
!1933 = !DILocation(line: 671, column: 7, scope: !1932)
!1934 = !DILocation(line: 671, column: 7, scope: !587)
!1935 = !DILocation(line: 672, column: 9, scope: !1936)
!1936 = distinct !DILexicalBlock(scope: !1932, file: !1, line: 672, column: 9)
!1937 = !DILocation(line: 672, column: 15, scope: !1936)
!1938 = !DILocation(line: 672, column: 24, scope: !1936)
!1939 = !DILocation(line: 672, column: 27, scope: !1940)
!1940 = !DILexicalBlockFile(scope: !1936, file: !1, discriminator: 1)
!1941 = !DILocation(line: 672, column: 33, scope: !1940)
!1942 = !DILocation(line: 672, column: 9, scope: !1940)
!1943 = !DILocation(line: 673, column: 7, scope: !1936)
!1944 = !DILocation(line: 672, column: 36, scope: !1945)
!1945 = !DILexicalBlockFile(scope: !1936, file: !1, discriminator: 2)
!1946 = !DILocation(line: 675, column: 10, scope: !587)
!1947 = !DILocation(line: 675, column: 3, scope: !587)
!1948 = !DILocation(line: 676, column: 1, scope: !587)
!1949 = !DILocalVariable(name: "statfile_fp", arg: 1, scope: !642, file: !1, line: 606, type: !645)
!1950 = !DILocation(line: 606, column: 30, scope: !642)
!1951 = !DILocalVariable(name: "numcpus", arg: 2, scope: !642, file: !1, line: 606, type: !699)
!1952 = !DILocation(line: 606, column: 57, scope: !642)
!1953 = !DILocalVariable(name: "num", scope: !642, file: !1, line: 607, type: !279)
!1954 = !DILocation(line: 607, column: 16, scope: !642)
!1955 = !DILocalVariable(name: "buf", scope: !642, file: !1, line: 608, type: !1691)
!1956 = !DILocation(line: 608, column: 8, scope: !642)
!1957 = !DILocation(line: 610, column: 14, scope: !1958)
!1958 = distinct !DILexicalBlock(scope: !642, file: !1, line: 610, column: 7)
!1959 = !DILocation(line: 610, column: 32, scope: !1958)
!1960 = !DILocation(line: 610, column: 8, scope: !1958)
!1961 = !DILocation(line: 610, column: 7, scope: !642)
!1962 = !DILocation(line: 611, column: 5, scope: !1958)
!1963 = !DILocation(line: 613, column: 7, scope: !642)
!1964 = !DILocation(line: 614, column: 3, scope: !642)
!1965 = !DILocation(line: 614, column: 16, scope: !1966)
!1966 = !DILexicalBlockFile(scope: !642, file: !1, discriminator: 1)
!1967 = !DILocation(line: 614, column: 34, scope: !1966)
!1968 = !DILocation(line: 614, column: 10, scope: !1966)
!1969 = !DILocation(line: 614, column: 3, scope: !1966)
!1970 = !DILocation(line: 615, column: 17, scope: !1971)
!1971 = distinct !DILexicalBlock(scope: !1972, file: !1, line: 615, column: 9)
!1972 = distinct !DILexicalBlock(scope: !642, file: !1, line: 614, column: 48)
!1973 = !DILocation(line: 615, column: 9, scope: !1971)
!1974 = !DILocation(line: 615, column: 9, scope: !1972)
!1975 = !DILocation(line: 616, column: 7, scope: !1971)
!1976 = !DILocation(line: 617, column: 8, scope: !1972)
!1977 = !DILocation(line: 614, column: 3, scope: !1978)
!1978 = !DILexicalBlockFile(scope: !642, file: !1, discriminator: 2)
!1979 = !DILocation(line: 620, column: 7, scope: !1980)
!1980 = distinct !DILexicalBlock(scope: !642, file: !1, line: 620, column: 7)
!1981 = !DILocation(line: 620, column: 11, scope: !1980)
!1982 = !DILocation(line: 620, column: 7, scope: !642)
!1983 = !DILocation(line: 621, column: 5, scope: !1980)
!1984 = !DILocation(line: 623, column: 14, scope: !642)
!1985 = !DILocation(line: 623, column: 4, scope: !642)
!1986 = !DILocation(line: 623, column: 12, scope: !642)
!1987 = !DILocation(line: 624, column: 3, scope: !642)
!1988 = !DILocation(line: 625, column: 1, scope: !642)
!1989 = !DILocalVariable(name: "numcpus", arg: 1, scope: !706, file: !1, line: 692, type: !279)
!1990 = !DILocation(line: 692, column: 37, scope: !706)
!1991 = !DILocalVariable(name: "ci", arg: 2, scope: !706, file: !1, line: 692, type: !591)
!1992 = !DILocation(line: 692, column: 61, scope: !706)
!1993 = !DILocalVariable(name: "inferred_model", scope: !706, file: !1, line: 695, type: !639)
!1994 = !DILocation(line: 695, column: 15, scope: !706)
!1995 = !DILocalVariable(name: "model_idx", scope: !706, file: !1, line: 696, type: !279)
!1996 = !DILocation(line: 696, column: 16, scope: !706)
!1997 = !DILocalVariable(name: "speed_idx", scope: !706, file: !1, line: 697, type: !279)
!1998 = !DILocation(line: 697, column: 16, scope: !706)
!1999 = !DILocalVariable(name: "buf", scope: !706, file: !1, line: 698, type: !1691)
!2000 = !DILocation(line: 698, column: 8, scope: !706)
!2001 = !DILocalVariable(name: "model", scope: !706, file: !1, line: 699, type: !491)
!2002 = !DILocation(line: 699, column: 9, scope: !706)
!2003 = !DILocalVariable(name: "fp", scope: !706, file: !1, line: 700, type: !645)
!2004 = !DILocation(line: 700, column: 9, scope: !706)
!2005 = !DILocation(line: 710, column: 13, scope: !706)
!2006 = !DILocation(line: 711, column: 13, scope: !706)
!2007 = !DILocation(line: 717, column: 8, scope: !706)
!2008 = !DILocation(line: 717, column: 6, scope: !706)
!2009 = !DILocation(line: 718, column: 7, scope: !2010)
!2010 = distinct !DILexicalBlock(scope: !706, file: !1, line: 718, column: 7)
!2011 = !DILocation(line: 718, column: 10, scope: !2010)
!2012 = !DILocation(line: 718, column: 7, scope: !706)
!2013 = !DILocation(line: 719, column: 13, scope: !2010)
!2014 = !DILocation(line: 719, column: 12, scope: !2010)
!2015 = !DILocation(line: 719, column: 5, scope: !2010)
!2016 = !DILocation(line: 721, column: 3, scope: !706)
!2017 = !DILocation(line: 721, column: 16, scope: !2018)
!2018 = !DILexicalBlockFile(scope: !706, file: !1, discriminator: 1)
!2019 = !DILocation(line: 721, column: 34, scope: !2018)
!2020 = !DILocation(line: 721, column: 10, scope: !2018)
!2021 = !DILocation(line: 721, column: 3, scope: !2018)
!2022 = !DILocation(line: 722, column: 9, scope: !2023)
!2023 = distinct !DILexicalBlock(scope: !2024, file: !1, line: 722, column: 9)
!2024 = distinct !DILexicalBlock(scope: !706, file: !1, line: 721, column: 39)
!2025 = !DILocation(line: 722, column: 21, scope: !2023)
!2026 = !DILocation(line: 722, column: 19, scope: !2023)
!2027 = !DILocation(line: 722, column: 9, scope: !2024)
!2028 = !DILocation(line: 723, column: 19, scope: !2029)
!2029 = distinct !DILexicalBlock(scope: !2030, file: !1, line: 723, column: 11)
!2030 = distinct !DILexicalBlock(scope: !2023, file: !1, line: 722, column: 30)
!2031 = !DILocation(line: 723, column: 11, scope: !2029)
!2032 = !DILocation(line: 723, column: 64, scope: !2029)
!2033 = !DILocation(line: 723, column: 11, scope: !2030)
!2034 = !DILocation(line: 724, column: 17, scope: !2035)
!2035 = distinct !DILexicalBlock(scope: !2029, file: !1, line: 723, column: 70)
!2036 = !DILocation(line: 724, column: 21, scope: !2035)
!2037 = !DILocation(line: 724, column: 44, scope: !2035)
!2038 = !DILocation(line: 724, column: 15, scope: !2035)
!2039 = !DILocation(line: 725, column: 29, scope: !2035)
!2040 = !DILocation(line: 725, column: 43, scope: !2035)
!2041 = !DILocation(line: 725, column: 36, scope: !2035)
!2042 = !DILocation(line: 725, column: 50, scope: !2035)
!2043 = !DILocation(line: 725, column: 17, scope: !2044)
!2044 = !DILexicalBlockFile(scope: !2035, file: !1, discriminator: 1)
!2045 = !DILocation(line: 725, column: 15, scope: !2035)
!2046 = !DILocation(line: 726, column: 13, scope: !2047)
!2047 = distinct !DILexicalBlock(scope: !2035, file: !1, line: 726, column: 13)
!2048 = !DILocation(line: 726, column: 19, scope: !2047)
!2049 = !DILocation(line: 726, column: 13, scope: !2035)
!2050 = !DILocation(line: 727, column: 18, scope: !2051)
!2051 = distinct !DILexicalBlock(scope: !2047, file: !1, line: 726, column: 28)
!2052 = !DILocation(line: 727, column: 11, scope: !2051)
!2053 = !DILocation(line: 728, column: 11, scope: !2051)
!2054 = !DILocation(line: 730, column: 33, scope: !2035)
!2055 = !DILocation(line: 730, column: 21, scope: !2035)
!2056 = !DILocation(line: 730, column: 9, scope: !2035)
!2057 = !DILocation(line: 730, column: 25, scope: !2035)
!2058 = !DILocation(line: 730, column: 31, scope: !2035)
!2059 = !DILocation(line: 731, column: 9, scope: !2035)
!2060 = !DILocation(line: 733, column: 5, scope: !2030)
!2061 = !DILocation(line: 754, column: 9, scope: !2062)
!2062 = distinct !DILexicalBlock(scope: !2024, file: !1, line: 754, column: 9)
!2063 = !DILocation(line: 754, column: 21, scope: !2062)
!2064 = !DILocation(line: 754, column: 19, scope: !2062)
!2065 = !DILocation(line: 754, column: 9, scope: !2024)
!2066 = !DILocation(line: 755, column: 19, scope: !2067)
!2067 = distinct !DILexicalBlock(scope: !2068, file: !1, line: 755, column: 11)
!2068 = distinct !DILexicalBlock(scope: !2062, file: !1, line: 754, column: 30)
!2069 = !DILocation(line: 755, column: 11, scope: !2067)
!2070 = !DILocation(line: 755, column: 64, scope: !2067)
!2071 = !DILocation(line: 755, column: 11, scope: !2068)
!2072 = !DILocation(line: 756, column: 38, scope: !2073)
!2073 = distinct !DILexicalBlock(scope: !2067, file: !1, line: 755, column: 70)
!2074 = !DILocation(line: 756, column: 42, scope: !2073)
!2075 = !DILocation(line: 756, column: 65, scope: !2073)
!2076 = !DILocation(line: 756, column: 33, scope: !2073)
!2077 = !DILocation(line: 756, column: 21, scope: !2073)
!2078 = !DILocation(line: 756, column: 9, scope: !2073)
!2079 = !DILocation(line: 756, column: 25, scope: !2073)
!2080 = !DILocation(line: 756, column: 31, scope: !2073)
!2081 = !DILocation(line: 757, column: 9, scope: !2073)
!2082 = !DILocation(line: 759, column: 5, scope: !2068)
!2083 = !DILocation(line: 721, column: 3, scope: !2084)
!2084 = !DILexicalBlockFile(scope: !706, file: !1, discriminator: 2)
!2085 = !DILocation(line: 763, column: 10, scope: !706)
!2086 = !DILocation(line: 763, column: 3, scope: !706)
!2087 = !DILocation(line: 770, column: 18, scope: !706)
!2088 = !DILocation(line: 771, column: 7, scope: !2089)
!2089 = distinct !DILexicalBlock(scope: !706, file: !1, line: 771, column: 7)
!2090 = !DILocation(line: 771, column: 17, scope: !2089)
!2091 = !DILocation(line: 771, column: 7, scope: !706)
!2092 = !DILocation(line: 772, column: 25, scope: !2089)
!2093 = !DILocation(line: 772, column: 35, scope: !2089)
!2094 = !DILocation(line: 772, column: 22, scope: !2089)
!2095 = !DILocation(line: 772, column: 40, scope: !2089)
!2096 = !DILocation(line: 772, column: 20, scope: !2089)
!2097 = !DILocation(line: 772, column: 5, scope: !2089)
!2098 = !DILocation(line: 774, column: 3, scope: !706)
!2099 = !DILocation(line: 774, column: 10, scope: !2018)
!2100 = !DILocation(line: 774, column: 22, scope: !2018)
!2101 = !DILocation(line: 774, column: 20, scope: !2018)
!2102 = !DILocation(line: 774, column: 3, scope: !2018)
!2103 = !DILocation(line: 775, column: 25, scope: !2104)
!2104 = distinct !DILexicalBlock(scope: !706, file: !1, line: 774, column: 31)
!2105 = !DILocation(line: 775, column: 48, scope: !2104)
!2106 = !DILocation(line: 775, column: 41, scope: !2104)
!2107 = !DILocation(line: 775, column: 13, scope: !2108)
!2108 = !DILexicalBlockFile(scope: !2104, file: !1, discriminator: 1)
!2109 = !DILocation(line: 775, column: 11, scope: !2104)
!2110 = !DILocation(line: 776, column: 9, scope: !2111)
!2111 = distinct !DILexicalBlock(scope: !2104, file: !1, line: 776, column: 9)
!2112 = !DILocation(line: 776, column: 15, scope: !2111)
!2113 = !DILocation(line: 776, column: 9, scope: !2104)
!2114 = !DILocation(line: 777, column: 7, scope: !2111)
!2115 = !DILocation(line: 778, column: 29, scope: !2104)
!2116 = !DILocation(line: 778, column: 17, scope: !2104)
!2117 = !DILocation(line: 778, column: 5, scope: !2104)
!2118 = !DILocation(line: 778, column: 21, scope: !2104)
!2119 = !DILocation(line: 778, column: 27, scope: !2104)
!2120 = !DILocation(line: 774, column: 3, scope: !2084)
!2121 = !DILocation(line: 781, column: 3, scope: !706)
!2122 = !DILocation(line: 782, column: 1, scope: !706)
!2123 = !DILocalVariable(name: "statfile_fp", arg: 1, scope: !709, file: !1, line: 785, type: !645)
!2124 = !DILocation(line: 785, column: 29, scope: !709)
!2125 = !DILocalVariable(name: "numcpus", arg: 2, scope: !709, file: !1, line: 786, type: !279)
!2126 = !DILocation(line: 786, column: 36, scope: !709)
!2127 = !DILocalVariable(name: "ci", arg: 3, scope: !709, file: !1, line: 787, type: !591)
!2128 = !DILocation(line: 787, column: 38, scope: !709)
!2129 = !DILocalVariable(name: "clock_ticks", scope: !709, file: !1, line: 788, type: !282)
!2130 = !DILocation(line: 788, column: 17, scope: !709)
!2131 = !DILocalVariable(name: "ts", scope: !709, file: !1, line: 789, type: !598)
!2132 = !DILocation(line: 789, column: 25, scope: !709)
!2133 = !DILocalVariable(name: "user", scope: !709, file: !1, line: 790, type: !282)
!2134 = !DILocation(line: 790, column: 17, scope: !709)
!2135 = !DILocalVariable(name: "nice", scope: !709, file: !1, line: 791, type: !282)
!2136 = !DILocation(line: 791, column: 17, scope: !709)
!2137 = !DILocalVariable(name: "sys", scope: !709, file: !1, line: 792, type: !282)
!2138 = !DILocation(line: 792, column: 17, scope: !709)
!2139 = !DILocalVariable(name: "idle", scope: !709, file: !1, line: 793, type: !282)
!2140 = !DILocation(line: 793, column: 17, scope: !709)
!2141 = !DILocalVariable(name: "dummy", scope: !709, file: !1, line: 794, type: !282)
!2142 = !DILocation(line: 794, column: 17, scope: !709)
!2143 = !DILocalVariable(name: "irq", scope: !709, file: !1, line: 795, type: !282)
!2144 = !DILocation(line: 795, column: 17, scope: !709)
!2145 = !DILocalVariable(name: "num", scope: !709, file: !1, line: 796, type: !279)
!2146 = !DILocation(line: 796, column: 16, scope: !709)
!2147 = !DILocalVariable(name: "len", scope: !709, file: !1, line: 797, type: !279)
!2148 = !DILocation(line: 797, column: 16, scope: !709)
!2149 = !DILocalVariable(name: "buf", scope: !709, file: !1, line: 798, type: !1691)
!2150 = !DILocation(line: 798, column: 8, scope: !709)
!2151 = !DILocation(line: 800, column: 17, scope: !709)
!2152 = !DILocation(line: 800, column: 15, scope: !709)
!2153 = !DILocation(line: 801, column: 3, scope: !709)
!2154 = !DILocation(line: 801, column: 3, scope: !2155)
!2155 = !DILexicalBlockFile(scope: !709, file: !1, discriminator: 1)
!2156 = !DILocation(line: 801, column: 3, scope: !2157)
!2157 = !DILexicalBlockFile(scope: !709, file: !1, discriminator: 2)
!2158 = !DILocation(line: 801, column: 3, scope: !2159)
!2159 = !DILexicalBlockFile(scope: !709, file: !1, discriminator: 3)
!2160 = !DILocation(line: 802, column: 3, scope: !709)
!2161 = !DILocation(line: 802, column: 3, scope: !2155)
!2162 = !DILocation(line: 802, column: 3, scope: !2157)
!2163 = !DILocation(line: 802, column: 3, scope: !2159)
!2164 = !DILocation(line: 804, column: 10, scope: !709)
!2165 = !DILocation(line: 804, column: 3, scope: !709)
!2166 = !DILocation(line: 806, column: 14, scope: !2167)
!2167 = distinct !DILexicalBlock(scope: !709, file: !1, line: 806, column: 7)
!2168 = !DILocation(line: 806, column: 32, scope: !2167)
!2169 = !DILocation(line: 806, column: 8, scope: !2167)
!2170 = !DILocation(line: 806, column: 7, scope: !709)
!2171 = !DILocation(line: 807, column: 5, scope: !2167)
!2172 = !DILocation(line: 809, column: 7, scope: !709)
!2173 = !DILocation(line: 811, column: 3, scope: !709)
!2174 = !DILocation(line: 811, column: 16, scope: !2155)
!2175 = !DILocation(line: 811, column: 34, scope: !2155)
!2176 = !DILocation(line: 811, column: 10, scope: !2155)
!2177 = !DILocation(line: 811, column: 3, scope: !2155)
!2178 = !DILocation(line: 812, column: 9, scope: !2179)
!2179 = distinct !DILexicalBlock(scope: !2180, file: !1, line: 812, column: 9)
!2180 = distinct !DILexicalBlock(scope: !709, file: !1, line: 811, column: 48)
!2181 = !DILocation(line: 812, column: 16, scope: !2179)
!2182 = !DILocation(line: 812, column: 13, scope: !2179)
!2183 = !DILocation(line: 812, column: 9, scope: !2180)
!2184 = !DILocation(line: 813, column: 7, scope: !2179)
!2185 = !DILocation(line: 815, column: 17, scope: !2186)
!2186 = distinct !DILexicalBlock(scope: !2180, file: !1, line: 815, column: 9)
!2187 = !DILocation(line: 815, column: 9, scope: !2186)
!2188 = !DILocation(line: 815, column: 9, scope: !2180)
!2189 = !DILocation(line: 816, column: 7, scope: !2186)
!2190 = !DILocalVariable(name: "n", scope: !2191, file: !1, line: 820, type: !279)
!2191 = distinct !DILexicalBlock(scope: !2180, file: !1, line: 819, column: 5)
!2192 = !DILocation(line: 820, column: 20, scope: !2191)
!2193 = !DILocalVariable(name: "r", scope: !2191, file: !1, line: 821, type: !284)
!2194 = !DILocation(line: 821, column: 11, scope: !2191)
!2195 = !DILocation(line: 821, column: 22, scope: !2191)
!2196 = !DILocation(line: 821, column: 15, scope: !2191)
!2197 = !DILocation(line: 822, column: 7, scope: !2191)
!2198 = !DILocation(line: 822, column: 7, scope: !2199)
!2199 = !DILexicalBlockFile(scope: !2191, file: !1, discriminator: 1)
!2200 = !DILocation(line: 822, column: 7, scope: !2201)
!2201 = !DILexicalBlockFile(scope: !2191, file: !1, discriminator: 2)
!2202 = !DILocation(line: 822, column: 7, scope: !2203)
!2203 = !DILexicalBlockFile(scope: !2191, file: !1, discriminator: 3)
!2204 = !DILocation(line: 823, column: 14, scope: !2191)
!2205 = !DILocation(line: 824, column: 16, scope: !2206)
!2206 = distinct !DILexicalBlock(scope: !2191, file: !1, line: 824, column: 7)
!2207 = !DILocation(line: 824, column: 12, scope: !2206)
!2208 = !DILocation(line: 824, column: 36, scope: !2209)
!2209 = !DILexicalBlockFile(scope: !2210, file: !1, discriminator: 1)
!2210 = distinct !DILexicalBlock(scope: !2206, file: !1, line: 824, column: 7)
!2211 = !DILocation(line: 824, column: 7, scope: !2209)
!2212 = !DILocation(line: 824, column: 7, scope: !2213)
!2213 = !DILexicalBlockFile(scope: !2206, file: !1, discriminator: 2)
!2214 = !DILocation(line: 824, column: 46, scope: !2215)
!2215 = !DILexicalBlockFile(scope: !2210, file: !1, discriminator: 3)
!2216 = !DILocation(line: 824, column: 7, scope: !2215)
!2217 = !DILocation(line: 833, column: 21, scope: !2218)
!2218 = distinct !DILexicalBlock(scope: !2180, file: !1, line: 833, column: 9)
!2219 = !DILocation(line: 833, column: 27, scope: !2218)
!2220 = !DILocation(line: 833, column: 25, scope: !2218)
!2221 = !DILocation(line: 833, column: 14, scope: !2218)
!2222 = !DILocation(line: 833, column: 11, scope: !2218)
!2223 = !DILocation(line: 833, column: 9, scope: !2180)
!2224 = !DILocation(line: 841, column: 7, scope: !2218)
!2225 = !DILocation(line: 843, column: 15, scope: !2180)
!2226 = !DILocation(line: 843, column: 29, scope: !2180)
!2227 = !DILocation(line: 843, column: 27, scope: !2180)
!2228 = !DILocation(line: 843, column: 8, scope: !2180)
!2229 = !DILocation(line: 843, column: 13, scope: !2180)
!2230 = !DILocation(line: 844, column: 15, scope: !2180)
!2231 = !DILocation(line: 844, column: 29, scope: !2180)
!2232 = !DILocation(line: 844, column: 27, scope: !2180)
!2233 = !DILocation(line: 844, column: 8, scope: !2180)
!2234 = !DILocation(line: 844, column: 13, scope: !2180)
!2235 = !DILocation(line: 845, column: 15, scope: !2180)
!2236 = !DILocation(line: 845, column: 29, scope: !2180)
!2237 = !DILocation(line: 845, column: 27, scope: !2180)
!2238 = !DILocation(line: 845, column: 8, scope: !2180)
!2239 = !DILocation(line: 845, column: 13, scope: !2180)
!2240 = !DILocation(line: 846, column: 15, scope: !2180)
!2241 = !DILocation(line: 846, column: 29, scope: !2180)
!2242 = !DILocation(line: 846, column: 27, scope: !2180)
!2243 = !DILocation(line: 846, column: 8, scope: !2180)
!2244 = !DILocation(line: 846, column: 13, scope: !2180)
!2245 = !DILocation(line: 847, column: 15, scope: !2180)
!2246 = !DILocation(line: 847, column: 29, scope: !2180)
!2247 = !DILocation(line: 847, column: 27, scope: !2180)
!2248 = !DILocation(line: 847, column: 8, scope: !2180)
!2249 = !DILocation(line: 847, column: 13, scope: !2180)
!2250 = !DILocation(line: 848, column: 11, scope: !2180)
!2251 = !DILocation(line: 848, column: 5, scope: !2180)
!2252 = !DILocation(line: 848, column: 15, scope: !2180)
!2253 = !DILocation(line: 848, column: 27, scope: !2180)
!2254 = !DILocation(line: 811, column: 3, scope: !2157)
!2255 = !DILocation(line: 850, column: 3, scope: !709)
!2256 = !DILocation(line: 850, column: 3, scope: !2155)
!2257 = !DILocation(line: 850, column: 3, scope: !2157)
!2258 = !DILocation(line: 850, column: 3, scope: !2159)
!2259 = !DILocation(line: 852, column: 3, scope: !709)
!2260 = !DILocalVariable(name: "cpu_infos", arg: 1, scope: !606, file: !1, line: 879, type: !591)
!2261 = !DILocation(line: 879, column: 38, scope: !606)
!2262 = !DILocalVariable(name: "count", arg: 2, scope: !606, file: !1, line: 879, type: !284)
!2263 = !DILocation(line: 879, column: 53, scope: !606)
!2264 = !DILocalVariable(name: "i", scope: !606, file: !1, line: 880, type: !284)
!2265 = !DILocation(line: 880, column: 7, scope: !606)
!2266 = !DILocation(line: 882, column: 10, scope: !2267)
!2267 = distinct !DILexicalBlock(scope: !606, file: !1, line: 882, column: 3)
!2268 = !DILocation(line: 882, column: 8, scope: !2267)
!2269 = !DILocation(line: 882, column: 15, scope: !2270)
!2270 = !DILexicalBlockFile(scope: !2271, file: !1, discriminator: 1)
!2271 = distinct !DILexicalBlock(scope: !2267, file: !1, line: 882, column: 3)
!2272 = !DILocation(line: 882, column: 19, scope: !2270)
!2273 = !DILocation(line: 882, column: 17, scope: !2270)
!2274 = !DILocation(line: 882, column: 3, scope: !2270)
!2275 = !DILocation(line: 883, column: 24, scope: !2276)
!2276 = distinct !DILexicalBlock(scope: !2271, file: !1, line: 882, column: 31)
!2277 = !DILocation(line: 883, column: 14, scope: !2276)
!2278 = !DILocation(line: 883, column: 27, scope: !2276)
!2279 = !DILocation(line: 883, column: 5, scope: !2276)
!2280 = !DILocation(line: 884, column: 3, scope: !2276)
!2281 = !DILocation(line: 882, column: 27, scope: !2282)
!2282 = !DILexicalBlockFile(scope: !2271, file: !1, discriminator: 2)
!2283 = !DILocation(line: 882, column: 3, scope: !2282)
!2284 = !DILocation(line: 886, column: 12, scope: !606)
!2285 = !DILocation(line: 886, column: 3, scope: !606)
!2286 = !DILocation(line: 887, column: 1, scope: !606)
!2287 = !DILocalVariable(name: "numcpus", arg: 1, scope: !700, file: !1, line: 679, type: !279)
!2288 = !DILocation(line: 679, column: 38, scope: !700)
!2289 = !DILocalVariable(name: "ci", arg: 2, scope: !700, file: !1, line: 679, type: !591)
!2290 = !DILocation(line: 679, column: 62, scope: !700)
!2291 = !DILocalVariable(name: "num", scope: !700, file: !1, line: 680, type: !279)
!2292 = !DILocation(line: 680, column: 16, scope: !700)
!2293 = !DILocation(line: 682, column: 12, scope: !2294)
!2294 = distinct !DILexicalBlock(scope: !700, file: !1, line: 682, column: 3)
!2295 = !DILocation(line: 682, column: 8, scope: !2294)
!2296 = !DILocation(line: 682, column: 17, scope: !2297)
!2297 = !DILexicalBlockFile(scope: !2298, file: !1, discriminator: 1)
!2298 = distinct !DILexicalBlock(scope: !2294, file: !1, line: 682, column: 3)
!2299 = !DILocation(line: 682, column: 23, scope: !2297)
!2300 = !DILocation(line: 682, column: 21, scope: !2297)
!2301 = !DILocation(line: 682, column: 3, scope: !2297)
!2302 = !DILocation(line: 683, column: 34, scope: !2298)
!2303 = !DILocation(line: 683, column: 21, scope: !2298)
!2304 = !DILocation(line: 683, column: 39, scope: !2298)
!2305 = !DILocation(line: 683, column: 8, scope: !2298)
!2306 = !DILocation(line: 683, column: 5, scope: !2298)
!2307 = !DILocation(line: 683, column: 13, scope: !2298)
!2308 = !DILocation(line: 683, column: 19, scope: !2298)
!2309 = !DILocation(line: 682, column: 35, scope: !2310)
!2310 = !DILexicalBlockFile(scope: !2298, file: !1, discriminator: 2)
!2311 = !DILocation(line: 682, column: 3, scope: !2310)
!2312 = !DILocation(line: 684, column: 1, scope: !700)
!2313 = !DILocalVariable(name: "addresses", arg: 1, scope: !609, file: !1, line: 903, type: !612)
!2314 = !DILocation(line: 903, column: 53, scope: !609)
!2315 = !DILocalVariable(name: "count", arg: 2, scope: !609, file: !1, line: 904, type: !605)
!2316 = !DILocation(line: 904, column: 8, scope: !609)
!2317 = !DILocalVariable(name: "addrs", scope: !609, file: !1, line: 908, type: !715)
!2318 = !DILocation(line: 908, column: 19, scope: !609)
!2319 = !DILocalVariable(name: "ent", scope: !609, file: !1, line: 908, type: !715)
!2320 = !DILocation(line: 908, column: 27, scope: !609)
!2321 = !DILocalVariable(name: "address", scope: !609, file: !1, line: 909, type: !613)
!2322 = !DILocation(line: 909, column: 27, scope: !609)
!2323 = !DILocalVariable(name: "i", scope: !609, file: !1, line: 910, type: !284)
!2324 = !DILocation(line: 910, column: 7, scope: !609)
!2325 = !DILocalVariable(name: "sll", scope: !609, file: !1, line: 911, type: !536)
!2326 = !DILocation(line: 911, column: 23, scope: !609)
!2327 = !DILocation(line: 913, column: 7, scope: !2328)
!2328 = distinct !DILexicalBlock(scope: !609, file: !1, line: 913, column: 7)
!2329 = !DILocation(line: 913, column: 7, scope: !609)
!2330 = !DILocation(line: 914, column: 13, scope: !2328)
!2331 = !DILocation(line: 914, column: 12, scope: !2328)
!2332 = !DILocation(line: 914, column: 5, scope: !2328)
!2333 = !DILocation(line: 916, column: 4, scope: !609)
!2334 = !DILocation(line: 916, column: 10, scope: !609)
!2335 = !DILocation(line: 917, column: 4, scope: !609)
!2336 = !DILocation(line: 917, column: 14, scope: !609)
!2337 = !DILocation(line: 920, column: 14, scope: !2338)
!2338 = distinct !DILexicalBlock(scope: !609, file: !1, line: 920, column: 3)
!2339 = !DILocation(line: 920, column: 12, scope: !2338)
!2340 = !DILocation(line: 920, column: 8, scope: !2338)
!2341 = !DILocation(line: 920, column: 21, scope: !2342)
!2342 = !DILexicalBlockFile(scope: !2343, file: !1, discriminator: 1)
!2343 = distinct !DILexicalBlock(scope: !2338, file: !1, line: 920, column: 3)
!2344 = !DILocation(line: 920, column: 25, scope: !2342)
!2345 = !DILocation(line: 920, column: 3, scope: !2342)
!2346 = !DILocation(line: 921, column: 28, scope: !2347)
!2347 = distinct !DILexicalBlock(scope: !2348, file: !1, line: 921, column: 9)
!2348 = distinct !DILexicalBlock(scope: !2343, file: !1, line: 920, column: 55)
!2349 = !DILocation(line: 921, column: 9, scope: !2347)
!2350 = !DILocation(line: 921, column: 9, scope: !2348)
!2351 = !DILocation(line: 922, column: 7, scope: !2347)
!2352 = !DILocation(line: 924, column: 7, scope: !2348)
!2353 = !DILocation(line: 924, column: 13, scope: !2348)
!2354 = !DILocation(line: 925, column: 3, scope: !2348)
!2355 = !DILocation(line: 920, column: 40, scope: !2356)
!2356 = !DILexicalBlockFile(scope: !2343, file: !1, discriminator: 2)
!2357 = !DILocation(line: 920, column: 45, scope: !2356)
!2358 = !DILocation(line: 920, column: 38, scope: !2356)
!2359 = !DILocation(line: 920, column: 3, scope: !2356)
!2360 = !DILocation(line: 927, column: 8, scope: !2361)
!2361 = distinct !DILexicalBlock(scope: !609, file: !1, line: 927, column: 7)
!2362 = !DILocation(line: 927, column: 7, scope: !2361)
!2363 = !DILocation(line: 927, column: 14, scope: !2361)
!2364 = !DILocation(line: 927, column: 7, scope: !609)
!2365 = !DILocation(line: 928, column: 5, scope: !2361)
!2366 = !DILocation(line: 930, column: 28, scope: !609)
!2367 = !DILocation(line: 930, column: 27, scope: !609)
!2368 = !DILocation(line: 930, column: 34, scope: !609)
!2369 = !DILocation(line: 930, column: 16, scope: !609)
!2370 = !DILocation(line: 930, column: 4, scope: !609)
!2371 = !DILocation(line: 930, column: 14, scope: !609)
!2372 = !DILocation(line: 931, column: 10, scope: !2373)
!2373 = distinct !DILexicalBlock(scope: !609, file: !1, line: 931, column: 7)
!2374 = !DILocation(line: 931, column: 9, scope: !2373)
!2375 = !DILocation(line: 931, column: 8, scope: !2373)
!2376 = !DILocation(line: 931, column: 7, scope: !609)
!2377 = !DILocation(line: 932, column: 17, scope: !2378)
!2378 = distinct !DILexicalBlock(scope: !2373, file: !1, line: 931, column: 22)
!2379 = !DILocation(line: 932, column: 5, scope: !2378)
!2380 = !DILocation(line: 933, column: 5, scope: !2378)
!2381 = !DILocation(line: 936, column: 14, scope: !609)
!2382 = !DILocation(line: 936, column: 13, scope: !609)
!2383 = !DILocation(line: 936, column: 11, scope: !609)
!2384 = !DILocation(line: 938, column: 14, scope: !2385)
!2385 = distinct !DILexicalBlock(scope: !609, file: !1, line: 938, column: 3)
!2386 = !DILocation(line: 938, column: 12, scope: !2385)
!2387 = !DILocation(line: 938, column: 8, scope: !2385)
!2388 = !DILocation(line: 938, column: 21, scope: !2389)
!2389 = !DILexicalBlockFile(scope: !2390, file: !1, discriminator: 1)
!2390 = distinct !DILexicalBlock(scope: !2385, file: !1, line: 938, column: 3)
!2391 = !DILocation(line: 938, column: 25, scope: !2389)
!2392 = !DILocation(line: 938, column: 3, scope: !2389)
!2393 = !DILocation(line: 939, column: 28, scope: !2394)
!2394 = distinct !DILexicalBlock(scope: !2395, file: !1, line: 939, column: 9)
!2395 = distinct !DILexicalBlock(scope: !2390, file: !1, line: 938, column: 55)
!2396 = !DILocation(line: 939, column: 9, scope: !2394)
!2397 = !DILocation(line: 939, column: 9, scope: !2395)
!2398 = !DILocation(line: 940, column: 7, scope: !2394)
!2399 = !DILocation(line: 942, column: 32, scope: !2395)
!2400 = !DILocation(line: 942, column: 37, scope: !2395)
!2401 = !DILocation(line: 942, column: 21, scope: !2395)
!2402 = !DILocation(line: 942, column: 5, scope: !2395)
!2403 = !DILocation(line: 942, column: 14, scope: !2395)
!2404 = !DILocation(line: 942, column: 19, scope: !2395)
!2405 = !DILocation(line: 944, column: 9, scope: !2406)
!2406 = distinct !DILexicalBlock(scope: !2395, file: !1, line: 944, column: 9)
!2407 = !DILocation(line: 944, column: 14, scope: !2406)
!2408 = !DILocation(line: 944, column: 24, scope: !2406)
!2409 = !DILocation(line: 944, column: 34, scope: !2406)
!2410 = !DILocation(line: 944, column: 9, scope: !2395)
!2411 = !DILocation(line: 945, column: 7, scope: !2412)
!2412 = distinct !DILexicalBlock(scope: !2406, file: !1, line: 944, column: 47)
!2413 = !DILocation(line: 945, column: 16, scope: !2412)
!2414 = !DILocation(line: 945, column: 24, scope: !2412)
!2415 = !DILocation(line: 945, column: 60, scope: !2412)
!2416 = !DILocation(line: 945, column: 65, scope: !2412)
!2417 = !DILocation(line: 945, column: 35, scope: !2412)
!2418 = !DILocation(line: 946, column: 5, scope: !2412)
!2419 = !DILocation(line: 947, column: 7, scope: !2420)
!2420 = distinct !DILexicalBlock(scope: !2406, file: !1, line: 946, column: 12)
!2421 = !DILocation(line: 947, column: 16, scope: !2420)
!2422 = !DILocation(line: 947, column: 24, scope: !2420)
!2423 = !DILocation(line: 947, column: 59, scope: !2420)
!2424 = !DILocation(line: 947, column: 64, scope: !2420)
!2425 = !DILocation(line: 947, column: 35, scope: !2420)
!2426 = !DILocation(line: 950, column: 9, scope: !2427)
!2427 = distinct !DILexicalBlock(scope: !2395, file: !1, line: 950, column: 9)
!2428 = !DILocation(line: 950, column: 14, scope: !2427)
!2429 = !DILocation(line: 950, column: 27, scope: !2427)
!2430 = !DILocation(line: 950, column: 37, scope: !2427)
!2431 = !DILocation(line: 950, column: 9, scope: !2395)
!2432 = !DILocation(line: 951, column: 7, scope: !2433)
!2433 = distinct !DILexicalBlock(scope: !2427, file: !1, line: 950, column: 50)
!2434 = !DILocation(line: 951, column: 16, scope: !2433)
!2435 = !DILocation(line: 951, column: 24, scope: !2433)
!2436 = !DILocation(line: 951, column: 60, scope: !2433)
!2437 = !DILocation(line: 951, column: 65, scope: !2433)
!2438 = !DILocation(line: 951, column: 35, scope: !2433)
!2439 = !DILocation(line: 952, column: 5, scope: !2433)
!2440 = !DILocation(line: 953, column: 7, scope: !2441)
!2441 = distinct !DILexicalBlock(scope: !2427, file: !1, line: 952, column: 12)
!2442 = !DILocation(line: 953, column: 16, scope: !2441)
!2443 = !DILocation(line: 953, column: 24, scope: !2441)
!2444 = !DILocation(line: 953, column: 59, scope: !2441)
!2445 = !DILocation(line: 953, column: 64, scope: !2441)
!2446 = !DILocation(line: 953, column: 35, scope: !2441)
!2447 = !DILocation(line: 956, column: 31, scope: !2395)
!2448 = !DILocation(line: 956, column: 36, scope: !2395)
!2449 = !DILocation(line: 956, column: 46, scope: !2395)
!2450 = !DILocation(line: 956, column: 29, scope: !2395)
!2451 = !DILocation(line: 956, column: 28, scope: !2395)
!2452 = !DILocation(line: 956, column: 5, scope: !2395)
!2453 = !DILocation(line: 956, column: 14, scope: !2395)
!2454 = !DILocation(line: 956, column: 26, scope: !2395)
!2455 = !DILocation(line: 958, column: 12, scope: !2395)
!2456 = !DILocation(line: 959, column: 3, scope: !2395)
!2457 = !DILocation(line: 938, column: 40, scope: !2458)
!2458 = !DILexicalBlockFile(scope: !2390, file: !1, discriminator: 2)
!2459 = !DILocation(line: 938, column: 45, scope: !2458)
!2460 = !DILocation(line: 938, column: 38, scope: !2458)
!2461 = !DILocation(line: 938, column: 3, scope: !2458)
!2462 = !DILocation(line: 962, column: 14, scope: !2463)
!2463 = distinct !DILexicalBlock(scope: !609, file: !1, line: 962, column: 3)
!2464 = !DILocation(line: 962, column: 12, scope: !2463)
!2465 = !DILocation(line: 962, column: 8, scope: !2463)
!2466 = !DILocation(line: 962, column: 21, scope: !2467)
!2467 = !DILexicalBlockFile(scope: !2468, file: !1, discriminator: 1)
!2468 = distinct !DILexicalBlock(scope: !2463, file: !1, line: 962, column: 3)
!2469 = !DILocation(line: 962, column: 25, scope: !2467)
!2470 = !DILocation(line: 962, column: 3, scope: !2467)
!2471 = !DILocation(line: 963, column: 28, scope: !2472)
!2472 = distinct !DILexicalBlock(scope: !2473, file: !1, line: 963, column: 9)
!2473 = distinct !DILexicalBlock(scope: !2468, file: !1, line: 962, column: 55)
!2474 = !DILocation(line: 963, column: 9, scope: !2472)
!2475 = !DILocation(line: 963, column: 9, scope: !2473)
!2476 = !DILocation(line: 964, column: 7, scope: !2472)
!2477 = !DILocation(line: 966, column: 16, scope: !2473)
!2478 = !DILocation(line: 966, column: 15, scope: !2473)
!2479 = !DILocation(line: 966, column: 13, scope: !2473)
!2480 = !DILocation(line: 968, column: 12, scope: !2481)
!2481 = distinct !DILexicalBlock(scope: !2473, file: !1, line: 968, column: 5)
!2482 = !DILocation(line: 968, column: 10, scope: !2481)
!2483 = !DILocation(line: 968, column: 17, scope: !2484)
!2484 = !DILexicalBlockFile(scope: !2485, file: !1, discriminator: 1)
!2485 = distinct !DILexicalBlock(scope: !2481, file: !1, line: 968, column: 5)
!2486 = !DILocation(line: 968, column: 23, scope: !2484)
!2487 = !DILocation(line: 968, column: 22, scope: !2484)
!2488 = !DILocation(line: 968, column: 19, scope: !2484)
!2489 = !DILocation(line: 968, column: 5, scope: !2484)
!2490 = !DILocation(line: 969, column: 18, scope: !2491)
!2491 = distinct !DILexicalBlock(scope: !2492, file: !1, line: 969, column: 11)
!2492 = distinct !DILexicalBlock(scope: !2485, file: !1, line: 968, column: 36)
!2493 = !DILocation(line: 969, column: 27, scope: !2491)
!2494 = !DILocation(line: 969, column: 33, scope: !2491)
!2495 = !DILocation(line: 969, column: 38, scope: !2491)
!2496 = !DILocation(line: 969, column: 11, scope: !2491)
!2497 = !DILocation(line: 969, column: 48, scope: !2491)
!2498 = !DILocation(line: 969, column: 11, scope: !2492)
!2499 = !DILocation(line: 970, column: 36, scope: !2500)
!2500 = distinct !DILexicalBlock(scope: !2491, file: !1, line: 969, column: 54)
!2501 = !DILocation(line: 970, column: 41, scope: !2500)
!2502 = !DILocation(line: 970, column: 15, scope: !2500)
!2503 = !DILocation(line: 970, column: 13, scope: !2500)
!2504 = !DILocation(line: 971, column: 16, scope: !2500)
!2505 = !DILocation(line: 971, column: 25, scope: !2500)
!2506 = !DILocation(line: 971, column: 9, scope: !2500)
!2507 = !DILocation(line: 971, column: 36, scope: !2500)
!2508 = !DILocation(line: 971, column: 41, scope: !2500)
!2509 = !DILocation(line: 972, column: 7, scope: !2500)
!2510 = !DILocation(line: 973, column: 14, scope: !2492)
!2511 = !DILocation(line: 974, column: 5, scope: !2492)
!2512 = !DILocation(line: 968, column: 32, scope: !2513)
!2513 = !DILexicalBlockFile(scope: !2485, file: !1, discriminator: 2)
!2514 = !DILocation(line: 968, column: 5, scope: !2513)
!2515 = !DILocation(line: 975, column: 3, scope: !2473)
!2516 = !DILocation(line: 962, column: 40, scope: !2517)
!2517 = !DILexicalBlockFile(scope: !2468, file: !1, discriminator: 2)
!2518 = !DILocation(line: 962, column: 45, scope: !2517)
!2519 = !DILocation(line: 962, column: 38, scope: !2517)
!2520 = !DILocation(line: 962, column: 3, scope: !2517)
!2521 = !DILocation(line: 977, column: 15, scope: !609)
!2522 = !DILocation(line: 977, column: 3, scope: !609)
!2523 = !DILocation(line: 979, column: 3, scope: !609)
!2524 = !DILocation(line: 981, column: 1, scope: !609)
!2525 = !DILocalVariable(name: "ent", arg: 1, scope: !712, file: !1, line: 889, type: !715)
!2526 = !DILocation(line: 889, column: 47, scope: !712)
!2527 = !DILocation(line: 890, column: 10, scope: !2528)
!2528 = distinct !DILexicalBlock(scope: !712, file: !1, line: 890, column: 7)
!2529 = !DILocation(line: 890, column: 15, scope: !2528)
!2530 = !DILocation(line: 890, column: 25, scope: !2528)
!2531 = !DILocation(line: 890, column: 35, scope: !2528)
!2532 = !DILocation(line: 890, column: 39, scope: !2533)
!2533 = !DILexicalBlockFile(scope: !2528, file: !1, discriminator: 1)
!2534 = !DILocation(line: 890, column: 44, scope: !2533)
!2535 = !DILocation(line: 890, column: 54, scope: !2533)
!2536 = !DILocation(line: 890, column: 7, scope: !2533)
!2537 = !DILocation(line: 891, column: 5, scope: !2528)
!2538 = !DILocation(line: 892, column: 7, scope: !2539)
!2539 = distinct !DILexicalBlock(scope: !712, file: !1, line: 892, column: 7)
!2540 = !DILocation(line: 892, column: 12, scope: !2539)
!2541 = !DILocation(line: 892, column: 21, scope: !2539)
!2542 = !DILocation(line: 892, column: 7, scope: !712)
!2543 = !DILocation(line: 893, column: 5, scope: !2539)
!2544 = !DILocation(line: 898, column: 7, scope: !2545)
!2545 = distinct !DILexicalBlock(scope: !712, file: !1, line: 898, column: 7)
!2546 = !DILocation(line: 898, column: 12, scope: !2545)
!2547 = !DILocation(line: 898, column: 22, scope: !2545)
!2548 = !DILocation(line: 898, column: 32, scope: !2545)
!2549 = !DILocation(line: 898, column: 7, scope: !712)
!2550 = !DILocation(line: 899, column: 5, scope: !2545)
!2551 = !DILocation(line: 900, column: 3, scope: !712)
!2552 = !DILocation(line: 901, column: 1, scope: !712)
!2553 = !DILocalVariable(name: "addresses", arg: 1, scope: !633, file: !1, line: 984, type: !613)
!2554 = !DILocation(line: 984, column: 58, scope: !633)
!2555 = !DILocalVariable(name: "count", arg: 2, scope: !633, file: !1, line: 985, type: !284)
!2556 = !DILocation(line: 985, column: 7, scope: !633)
!2557 = !DILocalVariable(name: "i", scope: !633, file: !1, line: 986, type: !284)
!2558 = !DILocation(line: 986, column: 7, scope: !633)
!2559 = !DILocation(line: 988, column: 10, scope: !2560)
!2560 = distinct !DILexicalBlock(scope: !633, file: !1, line: 988, column: 3)
!2561 = !DILocation(line: 988, column: 8, scope: !2560)
!2562 = !DILocation(line: 988, column: 15, scope: !2563)
!2563 = !DILexicalBlockFile(scope: !2564, file: !1, discriminator: 1)
!2564 = distinct !DILexicalBlock(scope: !2560, file: !1, line: 988, column: 3)
!2565 = !DILocation(line: 988, column: 19, scope: !2563)
!2566 = !DILocation(line: 988, column: 17, scope: !2563)
!2567 = !DILocation(line: 988, column: 3, scope: !2563)
!2568 = !DILocation(line: 989, column: 24, scope: !2569)
!2569 = distinct !DILexicalBlock(scope: !2564, file: !1, line: 988, column: 31)
!2570 = !DILocation(line: 989, column: 14, scope: !2569)
!2571 = !DILocation(line: 989, column: 27, scope: !2569)
!2572 = !DILocation(line: 989, column: 5, scope: !2569)
!2573 = !DILocation(line: 990, column: 3, scope: !2569)
!2574 = !DILocation(line: 988, column: 27, scope: !2575)
!2575 = !DILexicalBlockFile(scope: !2564, file: !1, discriminator: 2)
!2576 = !DILocation(line: 988, column: 3, scope: !2575)
!2577 = !DILocation(line: 992, column: 12, scope: !633)
!2578 = !DILocation(line: 992, column: 3, scope: !633)
!2579 = !DILocation(line: 993, column: 1, scope: !633)
!2580 = !DILocalVariable(name: "title", arg: 1, scope: !636, file: !1, line: 996, type: !639)
!2581 = !DILocation(line: 996, column: 40, scope: !636)
!2582 = !DILocation(line: 998, column: 22, scope: !636)
!2583 = !DILocation(line: 998, column: 3, scope: !636)
!2584 = !DILocation(line: 1000, column: 1, scope: !636)
!2585 = !DILocalVariable(name: "cpunum", arg: 1, scope: !703, file: !1, line: 856, type: !279)
!2586 = !DILocation(line: 856, column: 48, scope: !703)
!2587 = !DILocalVariable(name: "val", scope: !703, file: !1, line: 857, type: !282)
!2588 = !DILocation(line: 857, column: 17, scope: !703)
!2589 = !DILocalVariable(name: "buf", scope: !703, file: !1, line: 858, type: !1691)
!2590 = !DILocation(line: 858, column: 8, scope: !703)
!2591 = !DILocalVariable(name: "fp", scope: !703, file: !1, line: 859, type: !645)
!2592 = !DILocation(line: 859, column: 9, scope: !703)
!2593 = !DILocation(line: 861, column: 12, scope: !703)
!2594 = !DILocation(line: 864, column: 12, scope: !703)
!2595 = !DILocation(line: 861, column: 3, scope: !703)
!2596 = !DILocation(line: 866, column: 22, scope: !703)
!2597 = !DILocation(line: 866, column: 8, scope: !703)
!2598 = !DILocation(line: 866, column: 6, scope: !703)
!2599 = !DILocation(line: 867, column: 7, scope: !2600)
!2600 = distinct !DILexicalBlock(scope: !703, file: !1, line: 867, column: 7)
!2601 = !DILocation(line: 867, column: 10, scope: !2600)
!2602 = !DILocation(line: 867, column: 7, scope: !703)
!2603 = !DILocation(line: 868, column: 5, scope: !2600)
!2604 = !DILocation(line: 870, column: 14, scope: !2605)
!2605 = distinct !DILexicalBlock(scope: !703, file: !1, line: 870, column: 7)
!2606 = !DILocation(line: 870, column: 7, scope: !2605)
!2607 = !DILocation(line: 870, column: 31, scope: !2605)
!2608 = !DILocation(line: 870, column: 7, scope: !703)
!2609 = !DILocation(line: 871, column: 9, scope: !2605)
!2610 = !DILocation(line: 871, column: 5, scope: !2605)
!2611 = !DILocation(line: 873, column: 10, scope: !703)
!2612 = !DILocation(line: 873, column: 3, scope: !703)
!2613 = !DILocation(line: 875, column: 10, scope: !703)
!2614 = !DILocation(line: 875, column: 3, scope: !703)
!2615 = !DILocation(line: 876, column: 1, scope: !703)
