; ModuleID = '/data/download/cmake/cmake-master/Utilities/cmlibuv/src/unix/thread.c'
target datalayout = "e-m:e-i64:64-f80:128-n8:16:32:64-S128"
target triple = "x86_64-unknown-linux-gnu"

%union.pthread_attr_t = type { i64, [48 x i8] }
%union.pthread_mutex_t = type { %struct.__pthread_mutex_s }
%struct.__pthread_mutex_s = type { i32, i32, i32, i32, i32, i16, i16, %struct.__pthread_internal_list }
%struct.__pthread_internal_list = type { %struct.__pthread_internal_list*, %struct.__pthread_internal_list* }
%union.pthread_mutexattr_t = type { i32 }
%union.pthread_rwlock_t = type { %struct.anon }
%struct.anon = type { i32, i32, i32, i32, i32, i32, i32, i32, i64, i64, i32 }
%union.pthread_rwlockattr_t = type { i64 }
%union.sem_t = type { i64, [24 x i8] }
%union.pthread_cond_t = type { %struct.anon.0 }
%struct.anon.0 = type { i32, i32, i64, i64, i64, i8*, i32, i32 }
%union.pthread_condattr_t = type { i32 }
%struct.timespec = type { i64, i64 }
%union.pthread_barrier_t = type { i64, [24 x i8] }
%union.pthread_barrierattr_t = type { i32 }

; Function Attrs: nounwind uwtable
define i32 @uv_thread_create(i64* %tid, void (i8*)* %entry1, i8* %arg) #0 !dbg !17 {
entry:
  %tid.addr = alloca i64*, align 8
  %entry.addr = alloca void (i8*)*, align 8
  %arg.addr = alloca i8*, align 8
  %err = alloca i32, align 4
  %attr = alloca %union.pthread_attr_t*, align 8
  store i64* %tid, i64** %tid.addr, align 8
  call void @llvm.dbg.declare(metadata i64** %tid.addr, metadata !219, metadata !220), !dbg !221
  store void (i8*)* %entry1, void (i8*)** %entry.addr, align 8
  call void @llvm.dbg.declare(metadata void (i8*)** %entry.addr, metadata !222, metadata !220), !dbg !223
  store i8* %arg, i8** %arg.addr, align 8
  call void @llvm.dbg.declare(metadata i8** %arg.addr, metadata !224, metadata !220), !dbg !225
  call void @llvm.dbg.declare(metadata i32* %err, metadata !226, metadata !220), !dbg !227
  call void @llvm.dbg.declare(metadata %union.pthread_attr_t** %attr, metadata !228, metadata !220), !dbg !235
  store %union.pthread_attr_t* null, %union.pthread_attr_t** %attr, align 8, !dbg !236
  %0 = load i64*, i64** %tid.addr, align 8, !dbg !237
  %1 = load %union.pthread_attr_t*, %union.pthread_attr_t** %attr, align 8, !dbg !238
  %2 = load void (i8*)*, void (i8*)** %entry.addr, align 8, !dbg !239
  %3 = bitcast void (i8*)* %2 to i8* (i8*)*, !dbg !240
  %4 = load i8*, i8** %arg.addr, align 8, !dbg !241
  %call = call i32 @pthread_create(i64* %0, %union.pthread_attr_t* %1, i8* (i8*)* %3, i8* %4) #6, !dbg !242
  store i32 %call, i32* %err, align 4, !dbg !243
  %5 = load %union.pthread_attr_t*, %union.pthread_attr_t** %attr, align 8, !dbg !244
  %cmp = icmp ne %union.pthread_attr_t* %5, null, !dbg !246
  br i1 %cmp, label %if.then, label %if.end, !dbg !247

if.then:                                          ; preds = %entry
  %6 = load %union.pthread_attr_t*, %union.pthread_attr_t** %attr, align 8, !dbg !248
  %call2 = call i32 @pthread_attr_destroy(%union.pthread_attr_t* %6) #6, !dbg !249
  br label %if.end, !dbg !249

if.end:                                           ; preds = %if.then, %entry
  %7 = load i32, i32* %err, align 4, !dbg !250
  %sub = sub nsw i32 0, %7, !dbg !251
  ret i32 %sub, !dbg !252
}

; Function Attrs: nounwind readnone
declare void @llvm.dbg.declare(metadata, metadata, metadata) #1

; Function Attrs: nounwind
declare i32 @pthread_create(i64*, %union.pthread_attr_t*, i8* (i8*)*, i8*) #2

; Function Attrs: nounwind
declare i32 @pthread_attr_destroy(%union.pthread_attr_t*) #2

; Function Attrs: nounwind uwtable
define i64 @uv_thread_self() #0 !dbg !30 {
entry:
  %call = call i64 @pthread_self() #1, !dbg !253
  ret i64 %call, !dbg !254
}

; Function Attrs: nounwind readnone
declare i64 @pthread_self() #3

; Function Attrs: nounwind uwtable
define i32 @uv_thread_join(i64* %tid) #0 !dbg !33 {
entry:
  %tid.addr = alloca i64*, align 8
  store i64* %tid, i64** %tid.addr, align 8
  call void @llvm.dbg.declare(metadata i64** %tid.addr, metadata !255, metadata !220), !dbg !256
  %0 = load i64*, i64** %tid.addr, align 8, !dbg !257
  %1 = load i64, i64* %0, align 8, !dbg !258
  %call = call i32 @pthread_join(i64 %1, i8** null), !dbg !259
  %sub = sub nsw i32 0, %call, !dbg !260
  ret i32 %sub, !dbg !261
}

declare i32 @pthread_join(i64, i8**) #4

; Function Attrs: nounwind uwtable
define i32 @uv_thread_equal(i64* %t1, i64* %t2) #0 !dbg !36 {
entry:
  %t1.addr = alloca i64*, align 8
  %t2.addr = alloca i64*, align 8
  store i64* %t1, i64** %t1.addr, align 8
  call void @llvm.dbg.declare(metadata i64** %t1.addr, metadata !262, metadata !220), !dbg !263
  store i64* %t2, i64** %t2.addr, align 8
  call void @llvm.dbg.declare(metadata i64** %t2.addr, metadata !264, metadata !220), !dbg !265
  %0 = load i64*, i64** %t1.addr, align 8, !dbg !266
  %1 = load i64, i64* %0, align 8, !dbg !267
  %2 = load i64*, i64** %t2.addr, align 8, !dbg !268
  %3 = load i64, i64* %2, align 8, !dbg !269
  %call = call i32 @pthread_equal(i64 %1, i64 %3) #1, !dbg !270
  ret i32 %call, !dbg !271
}

; Function Attrs: nounwind readnone
declare i32 @pthread_equal(i64, i64) #3

; Function Attrs: nounwind uwtable
define i32 @uv_mutex_init(%union.pthread_mutex_t* %mutex) #0 !dbg !41 {
entry:
  %mutex.addr = alloca %union.pthread_mutex_t*, align 8
  store %union.pthread_mutex_t* %mutex, %union.pthread_mutex_t** %mutex.addr, align 8
  call void @llvm.dbg.declare(metadata %union.pthread_mutex_t** %mutex.addr, metadata !272, metadata !220), !dbg !273
  %0 = load %union.pthread_mutex_t*, %union.pthread_mutex_t** %mutex.addr, align 8, !dbg !274
  %call = call i32 @pthread_mutex_init(%union.pthread_mutex_t* %0, %union.pthread_mutexattr_t* null) #6, !dbg !275
  %sub = sub nsw i32 0, %call, !dbg !276
  ret i32 %sub, !dbg !277
}

; Function Attrs: nounwind
declare i32 @pthread_mutex_init(%union.pthread_mutex_t*, %union.pthread_mutexattr_t*) #2

; Function Attrs: nounwind uwtable
define void @uv_mutex_destroy(%union.pthread_mutex_t* %mutex) #0 !dbg !75 {
entry:
  %mutex.addr = alloca %union.pthread_mutex_t*, align 8
  store %union.pthread_mutex_t* %mutex, %union.pthread_mutex_t** %mutex.addr, align 8
  call void @llvm.dbg.declare(metadata %union.pthread_mutex_t** %mutex.addr, metadata !278, metadata !220), !dbg !279
  %0 = load %union.pthread_mutex_t*, %union.pthread_mutex_t** %mutex.addr, align 8, !dbg !280
  %call = call i32 @pthread_mutex_destroy(%union.pthread_mutex_t* %0) #6, !dbg !282
  %tobool = icmp ne i32 %call, 0, !dbg !282
  br i1 %tobool, label %if.then, label %if.end, !dbg !283

if.then:                                          ; preds = %entry
  call void @abort() #7, !dbg !284
  unreachable, !dbg !284

if.end:                                           ; preds = %entry
  ret void, !dbg !285
}

; Function Attrs: nounwind
declare i32 @pthread_mutex_destroy(%union.pthread_mutex_t*) #2

; Function Attrs: noreturn nounwind
declare void @abort() #5

; Function Attrs: nounwind uwtable
define void @uv_mutex_lock(%union.pthread_mutex_t* %mutex) #0 !dbg !78 {
entry:
  %mutex.addr = alloca %union.pthread_mutex_t*, align 8
  store %union.pthread_mutex_t* %mutex, %union.pthread_mutex_t** %mutex.addr, align 8
  call void @llvm.dbg.declare(metadata %union.pthread_mutex_t** %mutex.addr, metadata !286, metadata !220), !dbg !287
  %0 = load %union.pthread_mutex_t*, %union.pthread_mutex_t** %mutex.addr, align 8, !dbg !288
  %call = call i32 @pthread_mutex_lock(%union.pthread_mutex_t* %0) #6, !dbg !290
  %tobool = icmp ne i32 %call, 0, !dbg !290
  br i1 %tobool, label %if.then, label %if.end, !dbg !291

if.then:                                          ; preds = %entry
  call void @abort() #7, !dbg !292
  unreachable, !dbg !292

if.end:                                           ; preds = %entry
  ret void, !dbg !293
}

; Function Attrs: nounwind
declare i32 @pthread_mutex_lock(%union.pthread_mutex_t*) #2

; Function Attrs: nounwind uwtable
define i32 @uv_mutex_trylock(%union.pthread_mutex_t* %mutex) #0 !dbg !79 {
entry:
  %retval = alloca i32, align 4
  %mutex.addr = alloca %union.pthread_mutex_t*, align 8
  %err = alloca i32, align 4
  store %union.pthread_mutex_t* %mutex, %union.pthread_mutex_t** %mutex.addr, align 8
  call void @llvm.dbg.declare(metadata %union.pthread_mutex_t** %mutex.addr, metadata !294, metadata !220), !dbg !295
  call void @llvm.dbg.declare(metadata i32* %err, metadata !296, metadata !220), !dbg !297
  %0 = load %union.pthread_mutex_t*, %union.pthread_mutex_t** %mutex.addr, align 8, !dbg !298
  %call = call i32 @pthread_mutex_trylock(%union.pthread_mutex_t* %0) #6, !dbg !299
  store i32 %call, i32* %err, align 4, !dbg !300
  %1 = load i32, i32* %err, align 4, !dbg !301
  %tobool = icmp ne i32 %1, 0, !dbg !301
  br i1 %tobool, label %if.then, label %if.end3, !dbg !303

if.then:                                          ; preds = %entry
  %2 = load i32, i32* %err, align 4, !dbg !304
  %cmp = icmp ne i32 %2, 16, !dbg !307
  br i1 %cmp, label %land.lhs.true, label %if.end, !dbg !308

land.lhs.true:                                    ; preds = %if.then
  %3 = load i32, i32* %err, align 4, !dbg !309
  %cmp1 = icmp ne i32 %3, 11, !dbg !311
  br i1 %cmp1, label %if.then2, label %if.end, !dbg !312

if.then2:                                         ; preds = %land.lhs.true
  call void @abort() #7, !dbg !313
  unreachable, !dbg !313

if.end:                                           ; preds = %land.lhs.true, %if.then
  store i32 -16, i32* %retval, align 4, !dbg !314
  br label %return, !dbg !314

if.end3:                                          ; preds = %entry
  store i32 0, i32* %retval, align 4, !dbg !315
  br label %return, !dbg !315

return:                                           ; preds = %if.end3, %if.end
  %4 = load i32, i32* %retval, align 4, !dbg !316
  ret i32 %4, !dbg !316
}

; Function Attrs: nounwind
declare i32 @pthread_mutex_trylock(%union.pthread_mutex_t*) #2

; Function Attrs: nounwind uwtable
define void @uv_mutex_unlock(%union.pthread_mutex_t* %mutex) #0 !dbg !80 {
entry:
  %mutex.addr = alloca %union.pthread_mutex_t*, align 8
  store %union.pthread_mutex_t* %mutex, %union.pthread_mutex_t** %mutex.addr, align 8
  call void @llvm.dbg.declare(metadata %union.pthread_mutex_t** %mutex.addr, metadata !317, metadata !220), !dbg !318
  %0 = load %union.pthread_mutex_t*, %union.pthread_mutex_t** %mutex.addr, align 8, !dbg !319
  %call = call i32 @pthread_mutex_unlock(%union.pthread_mutex_t* %0) #6, !dbg !321
  %tobool = icmp ne i32 %call, 0, !dbg !321
  br i1 %tobool, label %if.then, label %if.end, !dbg !322

if.then:                                          ; preds = %entry
  call void @abort() #7, !dbg !323
  unreachable, !dbg !323

if.end:                                           ; preds = %entry
  ret void, !dbg !324
}

; Function Attrs: nounwind
declare i32 @pthread_mutex_unlock(%union.pthread_mutex_t*) #2

; Function Attrs: nounwind uwtable
define i32 @uv_rwlock_init(%union.pthread_rwlock_t* %rwlock) #0 !dbg !81 {
entry:
  %rwlock.addr = alloca %union.pthread_rwlock_t*, align 8
  store %union.pthread_rwlock_t* %rwlock, %union.pthread_rwlock_t** %rwlock.addr, align 8
  call void @llvm.dbg.declare(metadata %union.pthread_rwlock_t** %rwlock.addr, metadata !325, metadata !220), !dbg !326
  %0 = load %union.pthread_rwlock_t*, %union.pthread_rwlock_t** %rwlock.addr, align 8, !dbg !327
  %call = call i32 @pthread_rwlock_init(%union.pthread_rwlock_t* %0, %union.pthread_rwlockattr_t* null) #6, !dbg !328
  %sub = sub nsw i32 0, %call, !dbg !329
  ret i32 %sub, !dbg !330
}

; Function Attrs: nounwind
declare i32 @pthread_rwlock_init(%union.pthread_rwlock_t*, %union.pthread_rwlockattr_t*) #2

; Function Attrs: nounwind uwtable
define void @uv_rwlock_destroy(%union.pthread_rwlock_t* %rwlock) #0 !dbg !108 {
entry:
  %rwlock.addr = alloca %union.pthread_rwlock_t*, align 8
  store %union.pthread_rwlock_t* %rwlock, %union.pthread_rwlock_t** %rwlock.addr, align 8
  call void @llvm.dbg.declare(metadata %union.pthread_rwlock_t** %rwlock.addr, metadata !331, metadata !220), !dbg !332
  %0 = load %union.pthread_rwlock_t*, %union.pthread_rwlock_t** %rwlock.addr, align 8, !dbg !333
  %call = call i32 @pthread_rwlock_destroy(%union.pthread_rwlock_t* %0) #6, !dbg !335
  %tobool = icmp ne i32 %call, 0, !dbg !335
  br i1 %tobool, label %if.then, label %if.end, !dbg !336

if.then:                                          ; preds = %entry
  call void @abort() #7, !dbg !337
  unreachable, !dbg !337

if.end:                                           ; preds = %entry
  ret void, !dbg !338
}

; Function Attrs: nounwind
declare i32 @pthread_rwlock_destroy(%union.pthread_rwlock_t*) #2

; Function Attrs: nounwind uwtable
define void @uv_rwlock_rdlock(%union.pthread_rwlock_t* %rwlock) #0 !dbg !111 {
entry:
  %rwlock.addr = alloca %union.pthread_rwlock_t*, align 8
  store %union.pthread_rwlock_t* %rwlock, %union.pthread_rwlock_t** %rwlock.addr, align 8
  call void @llvm.dbg.declare(metadata %union.pthread_rwlock_t** %rwlock.addr, metadata !339, metadata !220), !dbg !340
  %0 = load %union.pthread_rwlock_t*, %union.pthread_rwlock_t** %rwlock.addr, align 8, !dbg !341
  %call = call i32 @pthread_rwlock_rdlock(%union.pthread_rwlock_t* %0) #6, !dbg !343
  %tobool = icmp ne i32 %call, 0, !dbg !343
  br i1 %tobool, label %if.then, label %if.end, !dbg !344

if.then:                                          ; preds = %entry
  call void @abort() #7, !dbg !345
  unreachable, !dbg !345

if.end:                                           ; preds = %entry
  ret void, !dbg !346
}

; Function Attrs: nounwind
declare i32 @pthread_rwlock_rdlock(%union.pthread_rwlock_t*) #2

; Function Attrs: nounwind uwtable
define i32 @uv_rwlock_tryrdlock(%union.pthread_rwlock_t* %rwlock) #0 !dbg !112 {
entry:
  %retval = alloca i32, align 4
  %rwlock.addr = alloca %union.pthread_rwlock_t*, align 8
  %err = alloca i32, align 4
  store %union.pthread_rwlock_t* %rwlock, %union.pthread_rwlock_t** %rwlock.addr, align 8
  call void @llvm.dbg.declare(metadata %union.pthread_rwlock_t** %rwlock.addr, metadata !347, metadata !220), !dbg !348
  call void @llvm.dbg.declare(metadata i32* %err, metadata !349, metadata !220), !dbg !350
  %0 = load %union.pthread_rwlock_t*, %union.pthread_rwlock_t** %rwlock.addr, align 8, !dbg !351
  %call = call i32 @pthread_rwlock_tryrdlock(%union.pthread_rwlock_t* %0) #6, !dbg !352
  store i32 %call, i32* %err, align 4, !dbg !353
  %1 = load i32, i32* %err, align 4, !dbg !354
  %tobool = icmp ne i32 %1, 0, !dbg !354
  br i1 %tobool, label %if.then, label %if.end3, !dbg !356

if.then:                                          ; preds = %entry
  %2 = load i32, i32* %err, align 4, !dbg !357
  %cmp = icmp ne i32 %2, 16, !dbg !360
  br i1 %cmp, label %land.lhs.true, label %if.end, !dbg !361

land.lhs.true:                                    ; preds = %if.then
  %3 = load i32, i32* %err, align 4, !dbg !362
  %cmp1 = icmp ne i32 %3, 11, !dbg !364
  br i1 %cmp1, label %if.then2, label %if.end, !dbg !365

if.then2:                                         ; preds = %land.lhs.true
  call void @abort() #7, !dbg !366
  unreachable, !dbg !366

if.end:                                           ; preds = %land.lhs.true, %if.then
  store i32 -16, i32* %retval, align 4, !dbg !367
  br label %return, !dbg !367

if.end3:                                          ; preds = %entry
  store i32 0, i32* %retval, align 4, !dbg !368
  br label %return, !dbg !368

return:                                           ; preds = %if.end3, %if.end
  %4 = load i32, i32* %retval, align 4, !dbg !369
  ret i32 %4, !dbg !369
}

; Function Attrs: nounwind
declare i32 @pthread_rwlock_tryrdlock(%union.pthread_rwlock_t*) #2

; Function Attrs: nounwind uwtable
define void @uv_rwlock_rdunlock(%union.pthread_rwlock_t* %rwlock) #0 !dbg !113 {
entry:
  %rwlock.addr = alloca %union.pthread_rwlock_t*, align 8
  store %union.pthread_rwlock_t* %rwlock, %union.pthread_rwlock_t** %rwlock.addr, align 8
  call void @llvm.dbg.declare(metadata %union.pthread_rwlock_t** %rwlock.addr, metadata !370, metadata !220), !dbg !371
  %0 = load %union.pthread_rwlock_t*, %union.pthread_rwlock_t** %rwlock.addr, align 8, !dbg !372
  %call = call i32 @pthread_rwlock_unlock(%union.pthread_rwlock_t* %0) #6, !dbg !374
  %tobool = icmp ne i32 %call, 0, !dbg !374
  br i1 %tobool, label %if.then, label %if.end, !dbg !375

if.then:                                          ; preds = %entry
  call void @abort() #7, !dbg !376
  unreachable, !dbg !376

if.end:                                           ; preds = %entry
  ret void, !dbg !377
}

; Function Attrs: nounwind
declare i32 @pthread_rwlock_unlock(%union.pthread_rwlock_t*) #2

; Function Attrs: nounwind uwtable
define void @uv_rwlock_wrlock(%union.pthread_rwlock_t* %rwlock) #0 !dbg !114 {
entry:
  %rwlock.addr = alloca %union.pthread_rwlock_t*, align 8
  store %union.pthread_rwlock_t* %rwlock, %union.pthread_rwlock_t** %rwlock.addr, align 8
  call void @llvm.dbg.declare(metadata %union.pthread_rwlock_t** %rwlock.addr, metadata !378, metadata !220), !dbg !379
  %0 = load %union.pthread_rwlock_t*, %union.pthread_rwlock_t** %rwlock.addr, align 8, !dbg !380
  %call = call i32 @pthread_rwlock_wrlock(%union.pthread_rwlock_t* %0) #6, !dbg !382
  %tobool = icmp ne i32 %call, 0, !dbg !382
  br i1 %tobool, label %if.then, label %if.end, !dbg !383

if.then:                                          ; preds = %entry
  call void @abort() #7, !dbg !384
  unreachable, !dbg !384

if.end:                                           ; preds = %entry
  ret void, !dbg !385
}

; Function Attrs: nounwind
declare i32 @pthread_rwlock_wrlock(%union.pthread_rwlock_t*) #2

; Function Attrs: nounwind uwtable
define i32 @uv_rwlock_trywrlock(%union.pthread_rwlock_t* %rwlock) #0 !dbg !115 {
entry:
  %retval = alloca i32, align 4
  %rwlock.addr = alloca %union.pthread_rwlock_t*, align 8
  %err = alloca i32, align 4
  store %union.pthread_rwlock_t* %rwlock, %union.pthread_rwlock_t** %rwlock.addr, align 8
  call void @llvm.dbg.declare(metadata %union.pthread_rwlock_t** %rwlock.addr, metadata !386, metadata !220), !dbg !387
  call void @llvm.dbg.declare(metadata i32* %err, metadata !388, metadata !220), !dbg !389
  %0 = load %union.pthread_rwlock_t*, %union.pthread_rwlock_t** %rwlock.addr, align 8, !dbg !390
  %call = call i32 @pthread_rwlock_trywrlock(%union.pthread_rwlock_t* %0) #6, !dbg !391
  store i32 %call, i32* %err, align 4, !dbg !392
  %1 = load i32, i32* %err, align 4, !dbg !393
  %tobool = icmp ne i32 %1, 0, !dbg !393
  br i1 %tobool, label %if.then, label %if.end3, !dbg !395

if.then:                                          ; preds = %entry
  %2 = load i32, i32* %err, align 4, !dbg !396
  %cmp = icmp ne i32 %2, 16, !dbg !399
  br i1 %cmp, label %land.lhs.true, label %if.end, !dbg !400

land.lhs.true:                                    ; preds = %if.then
  %3 = load i32, i32* %err, align 4, !dbg !401
  %cmp1 = icmp ne i32 %3, 11, !dbg !403
  br i1 %cmp1, label %if.then2, label %if.end, !dbg !404

if.then2:                                         ; preds = %land.lhs.true
  call void @abort() #7, !dbg !405
  unreachable, !dbg !405

if.end:                                           ; preds = %land.lhs.true, %if.then
  store i32 -16, i32* %retval, align 4, !dbg !406
  br label %return, !dbg !406

if.end3:                                          ; preds = %entry
  store i32 0, i32* %retval, align 4, !dbg !407
  br label %return, !dbg !407

return:                                           ; preds = %if.end3, %if.end
  %4 = load i32, i32* %retval, align 4, !dbg !408
  ret i32 %4, !dbg !408
}

; Function Attrs: nounwind
declare i32 @pthread_rwlock_trywrlock(%union.pthread_rwlock_t*) #2

; Function Attrs: nounwind uwtable
define void @uv_rwlock_wrunlock(%union.pthread_rwlock_t* %rwlock) #0 !dbg !116 {
entry:
  %rwlock.addr = alloca %union.pthread_rwlock_t*, align 8
  store %union.pthread_rwlock_t* %rwlock, %union.pthread_rwlock_t** %rwlock.addr, align 8
  call void @llvm.dbg.declare(metadata %union.pthread_rwlock_t** %rwlock.addr, metadata !409, metadata !220), !dbg !410
  %0 = load %union.pthread_rwlock_t*, %union.pthread_rwlock_t** %rwlock.addr, align 8, !dbg !411
  %call = call i32 @pthread_rwlock_unlock(%union.pthread_rwlock_t* %0) #6, !dbg !413
  %tobool = icmp ne i32 %call, 0, !dbg !413
  br i1 %tobool, label %if.then, label %if.end, !dbg !414

if.then:                                          ; preds = %entry
  call void @abort() #7, !dbg !415
  unreachable, !dbg !415

if.end:                                           ; preds = %entry
  ret void, !dbg !416
}

; Function Attrs: nounwind uwtable
define void @uv_once(i32* %guard, void ()* %callback) #0 !dbg !117 {
entry:
  %guard.addr = alloca i32*, align 8
  %callback.addr = alloca void ()*, align 8
  store i32* %guard, i32** %guard.addr, align 8
  call void @llvm.dbg.declare(metadata i32** %guard.addr, metadata !417, metadata !220), !dbg !418
  store void ()* %callback, void ()** %callback.addr, align 8
  call void @llvm.dbg.declare(metadata void ()** %callback.addr, metadata !419, metadata !220), !dbg !420
  %0 = load i32*, i32** %guard.addr, align 8, !dbg !421
  %1 = load void ()*, void ()** %callback.addr, align 8, !dbg !423
  %call = call i32 @pthread_once(i32* %0, void ()* %1), !dbg !424
  %tobool = icmp ne i32 %call, 0, !dbg !424
  br i1 %tobool, label %if.then, label %if.end, !dbg !425

if.then:                                          ; preds = %entry
  call void @abort() #7, !dbg !426
  unreachable, !dbg !426

if.end:                                           ; preds = %entry
  ret void, !dbg !427
}

declare i32 @pthread_once(i32*, void ()*) #4

; Function Attrs: nounwind uwtable
define i32 @uv_sem_init(%union.sem_t* %sem, i32 %value) #0 !dbg !126 {
entry:
  %retval = alloca i32, align 4
  %sem.addr = alloca %union.sem_t*, align 8
  %value.addr = alloca i32, align 4
  store %union.sem_t* %sem, %union.sem_t** %sem.addr, align 8
  call void @llvm.dbg.declare(metadata %union.sem_t** %sem.addr, metadata !428, metadata !220), !dbg !429
  store i32 %value, i32* %value.addr, align 4
  call void @llvm.dbg.declare(metadata i32* %value.addr, metadata !430, metadata !220), !dbg !431
  %0 = load %union.sem_t*, %union.sem_t** %sem.addr, align 8, !dbg !432
  %1 = load i32, i32* %value.addr, align 4, !dbg !434
  %call = call i32 @sem_init(%union.sem_t* %0, i32 0, i32 %1) #6, !dbg !435
  %tobool = icmp ne i32 %call, 0, !dbg !435
  br i1 %tobool, label %if.then, label %if.end, !dbg !436

if.then:                                          ; preds = %entry
  %call1 = call i32* @__errno_location() #1, !dbg !437
  %2 = load i32, i32* %call1, align 4, !dbg !437
  %sub = sub nsw i32 0, %2, !dbg !438
  store i32 %sub, i32* %retval, align 4, !dbg !439
  br label %return, !dbg !439

if.end:                                           ; preds = %entry
  store i32 0, i32* %retval, align 4, !dbg !440
  br label %return, !dbg !440

return:                                           ; preds = %if.end, %if.then
  %3 = load i32, i32* %retval, align 4, !dbg !441
  ret i32 %3, !dbg !441
}

; Function Attrs: nounwind
declare i32 @sem_init(%union.sem_t*, i32, i32) #2

; Function Attrs: nounwind readnone
declare i32* @__errno_location() #3

; Function Attrs: nounwind uwtable
define void @uv_sem_destroy(%union.sem_t* %sem) #0 !dbg !140 {
entry:
  %sem.addr = alloca %union.sem_t*, align 8
  store %union.sem_t* %sem, %union.sem_t** %sem.addr, align 8
  call void @llvm.dbg.declare(metadata %union.sem_t** %sem.addr, metadata !442, metadata !220), !dbg !443
  %0 = load %union.sem_t*, %union.sem_t** %sem.addr, align 8, !dbg !444
  %call = call i32 @sem_destroy(%union.sem_t* %0) #6, !dbg !446
  %tobool = icmp ne i32 %call, 0, !dbg !446
  br i1 %tobool, label %if.then, label %if.end, !dbg !447

if.then:                                          ; preds = %entry
  call void @abort() #7, !dbg !448
  unreachable, !dbg !448

if.end:                                           ; preds = %entry
  ret void, !dbg !449
}

; Function Attrs: nounwind
declare i32 @sem_destroy(%union.sem_t*) #2

; Function Attrs: nounwind uwtable
define void @uv_sem_post(%union.sem_t* %sem) #0 !dbg !143 {
entry:
  %sem.addr = alloca %union.sem_t*, align 8
  store %union.sem_t* %sem, %union.sem_t** %sem.addr, align 8
  call void @llvm.dbg.declare(metadata %union.sem_t** %sem.addr, metadata !450, metadata !220), !dbg !451
  %0 = load %union.sem_t*, %union.sem_t** %sem.addr, align 8, !dbg !452
  %call = call i32 @sem_post(%union.sem_t* %0) #6, !dbg !454
  %tobool = icmp ne i32 %call, 0, !dbg !454
  br i1 %tobool, label %if.then, label %if.end, !dbg !455

if.then:                                          ; preds = %entry
  call void @abort() #7, !dbg !456
  unreachable, !dbg !456

if.end:                                           ; preds = %entry
  ret void, !dbg !457
}

; Function Attrs: nounwind
declare i32 @sem_post(%union.sem_t*) #2

; Function Attrs: nounwind uwtable
define void @uv_sem_wait(%union.sem_t* %sem) #0 !dbg !144 {
entry:
  %sem.addr = alloca %union.sem_t*, align 8
  %r = alloca i32, align 4
  store %union.sem_t* %sem, %union.sem_t** %sem.addr, align 8
  call void @llvm.dbg.declare(metadata %union.sem_t** %sem.addr, metadata !458, metadata !220), !dbg !459
  call void @llvm.dbg.declare(metadata i32* %r, metadata !460, metadata !220), !dbg !461
  br label %do.body, !dbg !462

do.body:                                          ; preds = %land.end, %entry
  %0 = load %union.sem_t*, %union.sem_t** %sem.addr, align 8, !dbg !463
  %call = call i32 @sem_wait(%union.sem_t* %0), !dbg !464
  store i32 %call, i32* %r, align 4, !dbg !465
  br label %do.cond, !dbg !466

do.cond:                                          ; preds = %do.body
  %1 = load i32, i32* %r, align 4, !dbg !467
  %cmp = icmp eq i32 %1, -1, !dbg !468
  br i1 %cmp, label %land.rhs, label %land.end, !dbg !469

land.rhs:                                         ; preds = %do.cond
  %call1 = call i32* @__errno_location() #1, !dbg !470
  %2 = load i32, i32* %call1, align 4, !dbg !470
  %cmp2 = icmp eq i32 %2, 4, !dbg !472
  br label %land.end

land.end:                                         ; preds = %land.rhs, %do.cond
  %3 = phi i1 [ false, %do.cond ], [ %cmp2, %land.rhs ]
  br i1 %3, label %do.body, label %do.end, !dbg !473

do.end:                                           ; preds = %land.end
  %4 = load i32, i32* %r, align 4, !dbg !474
  %tobool = icmp ne i32 %4, 0, !dbg !474
  br i1 %tobool, label %if.then, label %if.end, !dbg !476

if.then:                                          ; preds = %do.end
  call void @abort() #7, !dbg !477
  unreachable, !dbg !477

if.end:                                           ; preds = %do.end
  ret void, !dbg !478
}

declare i32 @sem_wait(%union.sem_t*) #4

; Function Attrs: nounwind uwtable
define i32 @uv_sem_trywait(%union.sem_t* %sem) #0 !dbg !145 {
entry:
  %retval = alloca i32, align 4
  %sem.addr = alloca %union.sem_t*, align 8
  %r = alloca i32, align 4
  store %union.sem_t* %sem, %union.sem_t** %sem.addr, align 8
  call void @llvm.dbg.declare(metadata %union.sem_t** %sem.addr, metadata !479, metadata !220), !dbg !480
  call void @llvm.dbg.declare(metadata i32* %r, metadata !481, metadata !220), !dbg !482
  br label %do.body, !dbg !483

do.body:                                          ; preds = %land.end, %entry
  %0 = load %union.sem_t*, %union.sem_t** %sem.addr, align 8, !dbg !484
  %call = call i32 @sem_trywait(%union.sem_t* %0) #6, !dbg !485
  store i32 %call, i32* %r, align 4, !dbg !486
  br label %do.cond, !dbg !487

do.cond:                                          ; preds = %do.body
  %1 = load i32, i32* %r, align 4, !dbg !488
  %cmp = icmp eq i32 %1, -1, !dbg !489
  br i1 %cmp, label %land.rhs, label %land.end, !dbg !490

land.rhs:                                         ; preds = %do.cond
  %call1 = call i32* @__errno_location() #1, !dbg !491
  %2 = load i32, i32* %call1, align 4, !dbg !491
  %cmp2 = icmp eq i32 %2, 4, !dbg !493
  br label %land.end

land.end:                                         ; preds = %land.rhs, %do.cond
  %3 = phi i1 [ false, %do.cond ], [ %cmp2, %land.rhs ]
  br i1 %3, label %do.body, label %do.end, !dbg !494

do.end:                                           ; preds = %land.end
  %4 = load i32, i32* %r, align 4, !dbg !495
  %tobool = icmp ne i32 %4, 0, !dbg !495
  br i1 %tobool, label %if.then, label %if.end6, !dbg !497

if.then:                                          ; preds = %do.end
  %call3 = call i32* @__errno_location() #1, !dbg !498
  %5 = load i32, i32* %call3, align 4, !dbg !498
  %cmp4 = icmp eq i32 %5, 11, !dbg !501
  br i1 %cmp4, label %if.then5, label %if.end, !dbg !502

if.then5:                                         ; preds = %if.then
  store i32 -11, i32* %retval, align 4, !dbg !503
  br label %return, !dbg !503

if.end:                                           ; preds = %if.then
  call void @abort() #7, !dbg !504
  unreachable, !dbg !504

if.end6:                                          ; preds = %do.end
  store i32 0, i32* %retval, align 4, !dbg !505
  br label %return, !dbg !505

return:                                           ; preds = %if.end6, %if.then5
  %6 = load i32, i32* %retval, align 4, !dbg !506
  ret i32 %6, !dbg !506
}

; Function Attrs: nounwind
declare i32 @sem_trywait(%union.sem_t*) #2

; Function Attrs: nounwind uwtable
define i32 @uv_cond_init(%union.pthread_cond_t* %cond) #0 !dbg !148 {
entry:
  %retval = alloca i32, align 4
  %cond.addr = alloca %union.pthread_cond_t*, align 8
  %attr = alloca %union.pthread_condattr_t, align 4
  %err = alloca i32, align 4
  store %union.pthread_cond_t* %cond, %union.pthread_cond_t** %cond.addr, align 8
  call void @llvm.dbg.declare(metadata %union.pthread_cond_t** %cond.addr, metadata !507, metadata !220), !dbg !508
  call void @llvm.dbg.declare(metadata %union.pthread_condattr_t* %attr, metadata !509, metadata !220), !dbg !518
  call void @llvm.dbg.declare(metadata i32* %err, metadata !519, metadata !220), !dbg !520
  %call = call i32 @pthread_condattr_init(%union.pthread_condattr_t* %attr) #6, !dbg !521
  store i32 %call, i32* %err, align 4, !dbg !522
  %0 = load i32, i32* %err, align 4, !dbg !523
  %tobool = icmp ne i32 %0, 0, !dbg !523
  br i1 %tobool, label %if.then, label %if.end, !dbg !525

if.then:                                          ; preds = %entry
  %1 = load i32, i32* %err, align 4, !dbg !526
  %sub = sub nsw i32 0, %1, !dbg !527
  store i32 %sub, i32* %retval, align 4, !dbg !528
  br label %return, !dbg !528

if.end:                                           ; preds = %entry
  %call1 = call i32 @pthread_condattr_setclock(%union.pthread_condattr_t* %attr, i32 1) #6, !dbg !529
  store i32 %call1, i32* %err, align 4, !dbg !530
  %2 = load i32, i32* %err, align 4, !dbg !531
  %tobool2 = icmp ne i32 %2, 0, !dbg !531
  br i1 %tobool2, label %if.then3, label %if.end4, !dbg !533

if.then3:                                         ; preds = %if.end
  br label %error2, !dbg !534

if.end4:                                          ; preds = %if.end
  %3 = load %union.pthread_cond_t*, %union.pthread_cond_t** %cond.addr, align 8, !dbg !535
  %call5 = call i32 @pthread_cond_init(%union.pthread_cond_t* %3, %union.pthread_condattr_t* %attr) #6, !dbg !536
  store i32 %call5, i32* %err, align 4, !dbg !537
  %4 = load i32, i32* %err, align 4, !dbg !538
  %tobool6 = icmp ne i32 %4, 0, !dbg !538
  br i1 %tobool6, label %if.then7, label %if.end8, !dbg !540

if.then7:                                         ; preds = %if.end4
  br label %error2, !dbg !541

if.end8:                                          ; preds = %if.end4
  %call9 = call i32 @pthread_condattr_destroy(%union.pthread_condattr_t* %attr) #6, !dbg !542
  store i32 %call9, i32* %err, align 4, !dbg !543
  %5 = load i32, i32* %err, align 4, !dbg !544
  %tobool10 = icmp ne i32 %5, 0, !dbg !544
  br i1 %tobool10, label %if.then11, label %if.end12, !dbg !546

if.then11:                                        ; preds = %if.end8
  br label %error, !dbg !547

if.end12:                                         ; preds = %if.end8
  store i32 0, i32* %retval, align 4, !dbg !548
  br label %return, !dbg !548

error:                                            ; preds = %if.then11
  %6 = load %union.pthread_cond_t*, %union.pthread_cond_t** %cond.addr, align 8, !dbg !549
  %call13 = call i32 @pthread_cond_destroy(%union.pthread_cond_t* %6) #6, !dbg !550
  br label %error2, !dbg !550

error2:                                           ; preds = %error, %if.then7, %if.then3
  %call14 = call i32 @pthread_condattr_destroy(%union.pthread_condattr_t* %attr) #6, !dbg !551
  %7 = load i32, i32* %err, align 4, !dbg !552
  %sub15 = sub nsw i32 0, %7, !dbg !553
  store i32 %sub15, i32* %retval, align 4, !dbg !554
  br label %return, !dbg !554

return:                                           ; preds = %error2, %if.end12, %if.then
  %8 = load i32, i32* %retval, align 4, !dbg !555
  ret i32 %8, !dbg !555
}

; Function Attrs: nounwind
declare i32 @pthread_condattr_init(%union.pthread_condattr_t*) #2

; Function Attrs: nounwind
declare i32 @pthread_condattr_setclock(%union.pthread_condattr_t*, i32) #2

; Function Attrs: nounwind
declare i32 @pthread_cond_init(%union.pthread_cond_t*, %union.pthread_condattr_t*) #2

; Function Attrs: nounwind
declare i32 @pthread_condattr_destroy(%union.pthread_condattr_t*) #2

; Function Attrs: nounwind
declare i32 @pthread_cond_destroy(%union.pthread_cond_t*) #2

; Function Attrs: nounwind uwtable
define void @uv_cond_destroy(%union.pthread_cond_t* %cond) #0 !dbg !174 {
entry:
  %cond.addr = alloca %union.pthread_cond_t*, align 8
  store %union.pthread_cond_t* %cond, %union.pthread_cond_t** %cond.addr, align 8
  call void @llvm.dbg.declare(metadata %union.pthread_cond_t** %cond.addr, metadata !556, metadata !220), !dbg !557
  %0 = load %union.pthread_cond_t*, %union.pthread_cond_t** %cond.addr, align 8, !dbg !558
  %call = call i32 @pthread_cond_destroy(%union.pthread_cond_t* %0) #6, !dbg !560
  %tobool = icmp ne i32 %call, 0, !dbg !560
  br i1 %tobool, label %if.then, label %if.end, !dbg !561

if.then:                                          ; preds = %entry
  call void @abort() #7, !dbg !562
  unreachable, !dbg !562

if.end:                                           ; preds = %entry
  ret void, !dbg !563
}

; Function Attrs: nounwind uwtable
define void @uv_cond_signal(%union.pthread_cond_t* %cond) #0 !dbg !177 {
entry:
  %cond.addr = alloca %union.pthread_cond_t*, align 8
  store %union.pthread_cond_t* %cond, %union.pthread_cond_t** %cond.addr, align 8
  call void @llvm.dbg.declare(metadata %union.pthread_cond_t** %cond.addr, metadata !564, metadata !220), !dbg !565
  %0 = load %union.pthread_cond_t*, %union.pthread_cond_t** %cond.addr, align 8, !dbg !566
  %call = call i32 @pthread_cond_signal(%union.pthread_cond_t* %0) #6, !dbg !568
  %tobool = icmp ne i32 %call, 0, !dbg !568
  br i1 %tobool, label %if.then, label %if.end, !dbg !569

if.then:                                          ; preds = %entry
  call void @abort() #7, !dbg !570
  unreachable, !dbg !570

if.end:                                           ; preds = %entry
  ret void, !dbg !571
}

; Function Attrs: nounwind
declare i32 @pthread_cond_signal(%union.pthread_cond_t*) #2

; Function Attrs: nounwind uwtable
define void @uv_cond_broadcast(%union.pthread_cond_t* %cond) #0 !dbg !178 {
entry:
  %cond.addr = alloca %union.pthread_cond_t*, align 8
  store %union.pthread_cond_t* %cond, %union.pthread_cond_t** %cond.addr, align 8
  call void @llvm.dbg.declare(metadata %union.pthread_cond_t** %cond.addr, metadata !572, metadata !220), !dbg !573
  %0 = load %union.pthread_cond_t*, %union.pthread_cond_t** %cond.addr, align 8, !dbg !574
  %call = call i32 @pthread_cond_broadcast(%union.pthread_cond_t* %0) #6, !dbg !576
  %tobool = icmp ne i32 %call, 0, !dbg !576
  br i1 %tobool, label %if.then, label %if.end, !dbg !577

if.then:                                          ; preds = %entry
  call void @abort() #7, !dbg !578
  unreachable, !dbg !578

if.end:                                           ; preds = %entry
  ret void, !dbg !579
}

; Function Attrs: nounwind
declare i32 @pthread_cond_broadcast(%union.pthread_cond_t*) #2

; Function Attrs: nounwind uwtable
define void @uv_cond_wait(%union.pthread_cond_t* %cond, %union.pthread_mutex_t* %mutex) #0 !dbg !179 {
entry:
  %cond.addr = alloca %union.pthread_cond_t*, align 8
  %mutex.addr = alloca %union.pthread_mutex_t*, align 8
  store %union.pthread_cond_t* %cond, %union.pthread_cond_t** %cond.addr, align 8
  call void @llvm.dbg.declare(metadata %union.pthread_cond_t** %cond.addr, metadata !580, metadata !220), !dbg !581
  store %union.pthread_mutex_t* %mutex, %union.pthread_mutex_t** %mutex.addr, align 8
  call void @llvm.dbg.declare(metadata %union.pthread_mutex_t** %mutex.addr, metadata !582, metadata !220), !dbg !583
  %0 = load %union.pthread_cond_t*, %union.pthread_cond_t** %cond.addr, align 8, !dbg !584
  %1 = load %union.pthread_mutex_t*, %union.pthread_mutex_t** %mutex.addr, align 8, !dbg !586
  %call = call i32 @pthread_cond_wait(%union.pthread_cond_t* %0, %union.pthread_mutex_t* %1), !dbg !587
  %tobool = icmp ne i32 %call, 0, !dbg !587
  br i1 %tobool, label %if.then, label %if.end, !dbg !588

if.then:                                          ; preds = %entry
  call void @abort() #7, !dbg !589
  unreachable, !dbg !589

if.end:                                           ; preds = %entry
  ret void, !dbg !590
}

declare i32 @pthread_cond_wait(%union.pthread_cond_t*, %union.pthread_mutex_t*) #4

; Function Attrs: nounwind uwtable
define i32 @uv_cond_timedwait(%union.pthread_cond_t* %cond, %union.pthread_mutex_t* %mutex, i64 %timeout) #0 !dbg !182 {
entry:
  %retval = alloca i32, align 4
  %cond.addr = alloca %union.pthread_cond_t*, align 8
  %mutex.addr = alloca %union.pthread_mutex_t*, align 8
  %timeout.addr = alloca i64, align 8
  %r = alloca i32, align 4
  %ts = alloca %struct.timespec, align 8
  store %union.pthread_cond_t* %cond, %union.pthread_cond_t** %cond.addr, align 8
  call void @llvm.dbg.declare(metadata %union.pthread_cond_t** %cond.addr, metadata !591, metadata !220), !dbg !592
  store %union.pthread_mutex_t* %mutex, %union.pthread_mutex_t** %mutex.addr, align 8
  call void @llvm.dbg.declare(metadata %union.pthread_mutex_t** %mutex.addr, metadata !593, metadata !220), !dbg !594
  store i64 %timeout, i64* %timeout.addr, align 8
  call void @llvm.dbg.declare(metadata i64* %timeout.addr, metadata !595, metadata !220), !dbg !596
  call void @llvm.dbg.declare(metadata i32* %r, metadata !597, metadata !220), !dbg !598
  call void @llvm.dbg.declare(metadata %struct.timespec* %ts, metadata !599, metadata !220), !dbg !608
  %call = call i64 @uv__hrtime(i32 0), !dbg !609
  %0 = load i64, i64* %timeout.addr, align 8, !dbg !610
  %add = add i64 %0, %call, !dbg !610
  store i64 %add, i64* %timeout.addr, align 8, !dbg !610
  %1 = load i64, i64* %timeout.addr, align 8, !dbg !611
  %div = udiv i64 %1, 1000000000, !dbg !612
  %tv_sec = getelementptr inbounds %struct.timespec, %struct.timespec* %ts, i32 0, i32 0, !dbg !613
  store i64 %div, i64* %tv_sec, align 8, !dbg !614
  %2 = load i64, i64* %timeout.addr, align 8, !dbg !615
  %rem = urem i64 %2, 1000000000, !dbg !616
  %tv_nsec = getelementptr inbounds %struct.timespec, %struct.timespec* %ts, i32 0, i32 1, !dbg !617
  store i64 %rem, i64* %tv_nsec, align 8, !dbg !618
  %3 = load %union.pthread_cond_t*, %union.pthread_cond_t** %cond.addr, align 8, !dbg !619
  %4 = load %union.pthread_mutex_t*, %union.pthread_mutex_t** %mutex.addr, align 8, !dbg !620
  %call1 = call i32 @pthread_cond_timedwait(%union.pthread_cond_t* %3, %union.pthread_mutex_t* %4, %struct.timespec* %ts), !dbg !621
  store i32 %call1, i32* %r, align 4, !dbg !622
  %5 = load i32, i32* %r, align 4, !dbg !623
  %cmp = icmp eq i32 %5, 0, !dbg !625
  br i1 %cmp, label %if.then, label %if.end, !dbg !626

if.then:                                          ; preds = %entry
  store i32 0, i32* %retval, align 4, !dbg !627
  br label %return, !dbg !627

if.end:                                           ; preds = %entry
  %6 = load i32, i32* %r, align 4, !dbg !628
  %cmp2 = icmp eq i32 %6, 110, !dbg !630
  br i1 %cmp2, label %if.then3, label %if.end4, !dbg !631

if.then3:                                         ; preds = %if.end
  store i32 -110, i32* %retval, align 4, !dbg !632
  br label %return, !dbg !632

if.end4:                                          ; preds = %if.end
  call void @abort() #7, !dbg !633
  unreachable, !dbg !633

return:                                           ; preds = %if.then3, %if.then
  %7 = load i32, i32* %retval, align 4, !dbg !634
  ret i32 %7, !dbg !634
}

declare i64 @uv__hrtime(i32) #4

declare i32 @pthread_cond_timedwait(%union.pthread_cond_t*, %union.pthread_mutex_t*, %struct.timespec*) #4

; Function Attrs: nounwind uwtable
define i32 @uv_barrier_init(%union.pthread_barrier_t* %barrier, i32 %count) #0 !dbg !185 {
entry:
  %barrier.addr = alloca %union.pthread_barrier_t*, align 8
  %count.addr = alloca i32, align 4
  store %union.pthread_barrier_t* %barrier, %union.pthread_barrier_t** %barrier.addr, align 8
  call void @llvm.dbg.declare(metadata %union.pthread_barrier_t** %barrier.addr, metadata !635, metadata !220), !dbg !636
  store i32 %count, i32* %count.addr, align 4
  call void @llvm.dbg.declare(metadata i32* %count.addr, metadata !637, metadata !220), !dbg !638
  %0 = load %union.pthread_barrier_t*, %union.pthread_barrier_t** %barrier.addr, align 8, !dbg !639
  %1 = load i32, i32* %count.addr, align 4, !dbg !640
  %call = call i32 @pthread_barrier_init(%union.pthread_barrier_t* %0, %union.pthread_barrierattr_t* null, i32 %1) #6, !dbg !641
  %sub = sub nsw i32 0, %call, !dbg !642
  ret i32 %sub, !dbg !643
}

; Function Attrs: nounwind
declare i32 @pthread_barrier_init(%union.pthread_barrier_t*, %union.pthread_barrierattr_t*, i32) #2

; Function Attrs: nounwind uwtable
define void @uv_barrier_destroy(%union.pthread_barrier_t* %barrier) #0 !dbg !195 {
entry:
  %barrier.addr = alloca %union.pthread_barrier_t*, align 8
  store %union.pthread_barrier_t* %barrier, %union.pthread_barrier_t** %barrier.addr, align 8
  call void @llvm.dbg.declare(metadata %union.pthread_barrier_t** %barrier.addr, metadata !644, metadata !220), !dbg !645
  %0 = load %union.pthread_barrier_t*, %union.pthread_barrier_t** %barrier.addr, align 8, !dbg !646
  %call = call i32 @pthread_barrier_destroy(%union.pthread_barrier_t* %0) #6, !dbg !648
  %tobool = icmp ne i32 %call, 0, !dbg !648
  br i1 %tobool, label %if.then, label %if.end, !dbg !649

if.then:                                          ; preds = %entry
  call void @abort() #7, !dbg !650
  unreachable, !dbg !650

if.end:                                           ; preds = %entry
  ret void, !dbg !651
}

; Function Attrs: nounwind
declare i32 @pthread_barrier_destroy(%union.pthread_barrier_t*) #2

; Function Attrs: nounwind uwtable
define i32 @uv_barrier_wait(%union.pthread_barrier_t* %barrier) #0 !dbg !198 {
entry:
  %barrier.addr = alloca %union.pthread_barrier_t*, align 8
  %r = alloca i32, align 4
  store %union.pthread_barrier_t* %barrier, %union.pthread_barrier_t** %barrier.addr, align 8
  call void @llvm.dbg.declare(metadata %union.pthread_barrier_t** %barrier.addr, metadata !652, metadata !220), !dbg !653
  call void @llvm.dbg.declare(metadata i32* %r, metadata !654, metadata !220), !dbg !655
  %0 = load %union.pthread_barrier_t*, %union.pthread_barrier_t** %barrier.addr, align 8, !dbg !656
  %call = call i32 @pthread_barrier_wait(%union.pthread_barrier_t* %0) #6, !dbg !657
  store i32 %call, i32* %r, align 4, !dbg !655
  %1 = load i32, i32* %r, align 4, !dbg !658
  %tobool = icmp ne i32 %1, 0, !dbg !658
  br i1 %tobool, label %land.lhs.true, label %if.end, !dbg !660

land.lhs.true:                                    ; preds = %entry
  %2 = load i32, i32* %r, align 4, !dbg !661
  %cmp = icmp ne i32 %2, -1, !dbg !663
  br i1 %cmp, label %if.then, label %if.end, !dbg !664

if.then:                                          ; preds = %land.lhs.true
  call void @abort() #7, !dbg !665
  unreachable, !dbg !665

if.end:                                           ; preds = %land.lhs.true, %entry
  %3 = load i32, i32* %r, align 4, !dbg !666
  %cmp1 = icmp eq i32 %3, -1, !dbg !667
  %conv = zext i1 %cmp1 to i32, !dbg !667
  ret i32 %conv, !dbg !668
}

; Function Attrs: nounwind
declare i32 @pthread_barrier_wait(%union.pthread_barrier_t*) #2

; Function Attrs: nounwind uwtable
define i32 @uv_key_create(i32* %key) #0 !dbg !201 {
entry:
  %key.addr = alloca i32*, align 8
  store i32* %key, i32** %key.addr, align 8
  call void @llvm.dbg.declare(metadata i32** %key.addr, metadata !669, metadata !220), !dbg !670
  %0 = load i32*, i32** %key.addr, align 8, !dbg !671
  %call = call i32 @pthread_key_create(i32* %0, void (i8*)* null) #6, !dbg !672
  %sub = sub nsw i32 0, %call, !dbg !673
  ret i32 %sub, !dbg !674
}

; Function Attrs: nounwind
declare i32 @pthread_key_create(i32*, void (i8*)*) #2

; Function Attrs: nounwind uwtable
define void @uv_key_delete(i32* %key) #0 !dbg !207 {
entry:
  %key.addr = alloca i32*, align 8
  store i32* %key, i32** %key.addr, align 8
  call void @llvm.dbg.declare(metadata i32** %key.addr, metadata !675, metadata !220), !dbg !676
  %0 = load i32*, i32** %key.addr, align 8, !dbg !677
  %1 = load i32, i32* %0, align 4, !dbg !679
  %call = call i32 @pthread_key_delete(i32 %1) #6, !dbg !680
  %tobool = icmp ne i32 %call, 0, !dbg !680
  br i1 %tobool, label %if.then, label %if.end, !dbg !681

if.then:                                          ; preds = %entry
  call void @abort() #7, !dbg !682
  unreachable, !dbg !682

if.end:                                           ; preds = %entry
  ret void, !dbg !683
}

; Function Attrs: nounwind
declare i32 @pthread_key_delete(i32) #2

; Function Attrs: nounwind uwtable
define i8* @uv_key_get(i32* %key) #0 !dbg !210 {
entry:
  %key.addr = alloca i32*, align 8
  store i32* %key, i32** %key.addr, align 8
  call void @llvm.dbg.declare(metadata i32** %key.addr, metadata !684, metadata !220), !dbg !685
  %0 = load i32*, i32** %key.addr, align 8, !dbg !686
  %1 = load i32, i32* %0, align 4, !dbg !687
  %call = call i8* @pthread_getspecific(i32 %1) #6, !dbg !688
  ret i8* %call, !dbg !689
}

; Function Attrs: nounwind
declare i8* @pthread_getspecific(i32) #2

; Function Attrs: nounwind uwtable
define void @uv_key_set(i32* %key, i8* %value) #0 !dbg !213 {
entry:
  %key.addr = alloca i32*, align 8
  %value.addr = alloca i8*, align 8
  store i32* %key, i32** %key.addr, align 8
  call void @llvm.dbg.declare(metadata i32** %key.addr, metadata !690, metadata !220), !dbg !691
  store i8* %value, i8** %value.addr, align 8
  call void @llvm.dbg.declare(metadata i8** %value.addr, metadata !692, metadata !220), !dbg !693
  %0 = load i32*, i32** %key.addr, align 8, !dbg !694
  %1 = load i32, i32* %0, align 4, !dbg !696
  %2 = load i8*, i8** %value.addr, align 8, !dbg !697
  %call = call i32 @pthread_setspecific(i32 %1, i8* %2) #6, !dbg !698
  %tobool = icmp ne i32 %call, 0, !dbg !698
  br i1 %tobool, label %if.then, label %if.end, !dbg !699

if.then:                                          ; preds = %entry
  call void @abort() #7, !dbg !700
  unreachable, !dbg !700

if.end:                                           ; preds = %entry
  ret void, !dbg !701
}

; Function Attrs: nounwind
declare i32 @pthread_setspecific(i32, i8*) #2

attributes #0 = { nounwind uwtable "disable-tail-calls"="false" "less-precise-fpmad"="false" "no-frame-pointer-elim"="true" "no-frame-pointer-elim-non-leaf" "no-infs-fp-math"="false" "no-nans-fp-math"="false" "stack-protector-buffer-size"="8" "target-cpu"="x86-64" "target-features"="+fxsr,+mmx,+sse,+sse2" "unsafe-fp-math"="false" "use-soft-float"="false" }
attributes #1 = { nounwind readnone }
attributes #2 = { nounwind "disable-tail-calls"="false" "less-precise-fpmad"="false" "no-frame-pointer-elim"="true" "no-frame-pointer-elim-non-leaf" "no-infs-fp-math"="false" "no-nans-fp-math"="false" "stack-protector-buffer-size"="8" "target-cpu"="x86-64" "target-features"="+fxsr,+mmx,+sse,+sse2" "unsafe-fp-math"="false" "use-soft-float"="false" }
attributes #3 = { nounwind readnone "disable-tail-calls"="false" "less-precise-fpmad"="false" "no-frame-pointer-elim"="true" "no-frame-pointer-elim-non-leaf" "no-infs-fp-math"="false" "no-nans-fp-math"="false" "stack-protector-buffer-size"="8" "target-cpu"="x86-64" "target-features"="+fxsr,+mmx,+sse,+sse2" "unsafe-fp-math"="false" "use-soft-float"="false" }
attributes #4 = { "disable-tail-calls"="false" "less-precise-fpmad"="false" "no-frame-pointer-elim"="true" "no-frame-pointer-elim-non-leaf" "no-infs-fp-math"="false" "no-nans-fp-math"="false" "stack-protector-buffer-size"="8" "target-cpu"="x86-64" "target-features"="+fxsr,+mmx,+sse,+sse2" "unsafe-fp-math"="false" "use-soft-float"="false" }
attributes #5 = { noreturn nounwind "disable-tail-calls"="false" "less-precise-fpmad"="false" "no-frame-pointer-elim"="true" "no-frame-pointer-elim-non-leaf" "no-infs-fp-math"="false" "no-nans-fp-math"="false" "stack-protector-buffer-size"="8" "target-cpu"="x86-64" "target-features"="+fxsr,+mmx,+sse,+sse2" "unsafe-fp-math"="false" "use-soft-float"="false" }
attributes #6 = { nounwind }
attributes #7 = { noreturn nounwind }

!llvm.dbg.cu = !{!0}
!llvm.module.flags = !{!216, !217}
!llvm.ident = !{!218}

!0 = distinct !DICompileUnit(language: DW_LANG_C99, file: !1, producer: "clang version 3.8.0 (tags/RELEASE_380/final)", isOptimized: false, runtimeVersion: 0, emissionKind: 1, enums: !2, retainedTypes: !8, subprograms: !16)
!1 = !DIFile(filename: "/data/download/cmake/cmake-master/Utilities/cmlibuv/src/unix/thread.c", directory: "/data/download/cmake/cmake-master/Utilities/cmlibuv")
!2 = !{!3}
!3 = !DICompositeType(tag: DW_TAG_enumeration_type, file: !4, line: 148, size: 32, align: 32, elements: !5)
!4 = !DIFile(filename: "/data/download/cmake/cmake-master/Utilities/cmlibuv/src/unix/internal.h", directory: "/data/download/cmake/cmake-master/Utilities/cmlibuv")
!5 = !{!6, !7}
!6 = !DIEnumerator(name: "UV_CLOCK_PRECISE", value: 0)
!7 = !DIEnumerator(name: "UV_CLOCK_FAST", value: 1)
!8 = !{!9, !12, !13}
!9 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !10, size: 64, align: 64)
!10 = !DISubroutineType(types: !11)
!11 = !{!12, !12}
!12 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: null, size: 64, align: 64)
!13 = !DIDerivedType(tag: DW_TAG_typedef, name: "uint64_t", file: !14, line: 55, baseType: !15)
!14 = !DIFile(filename: "/usr/include/stdint.h", directory: "/data/download/cmake/cmake-master/Utilities/cmlibuv")
!15 = !DIBasicType(name: "long unsigned int", size: 64, align: 64, encoding: DW_ATE_unsigned)
!16 = !{!17, !30, !33, !36, !41, !75, !78, !79, !80, !81, !108, !111, !112, !113, !114, !115, !116, !117, !126, !140, !143, !144, !145, !148, !174, !177, !178, !179, !182, !185, !195, !198, !201, !207, !210, !213}
!17 = distinct !DISubprogram(name: "uv_thread_create", scope: !1, file: !1, line: 44, type: !18, isLocal: false, isDefinition: true, scopeLine: 44, flags: DIFlagPrototyped, isOptimized: false, variables: !29)
!18 = !DISubroutineType(types: !19)
!19 = !{!20, !21, !26, !12}
!20 = !DIBasicType(name: "int", size: 32, align: 32, encoding: DW_ATE_signed)
!21 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !22, size: 64, align: 64)
!22 = !DIDerivedType(tag: DW_TAG_typedef, name: "uv_thread_t", file: !23, line: 128, baseType: !24)
!23 = !DIFile(filename: "/data/download/cmake/cmake-master/Utilities/cmlibuv/include/uv-unix.h", directory: "/data/download/cmake/cmake-master/Utilities/cmlibuv")
!24 = !DIDerivedType(tag: DW_TAG_typedef, name: "pthread_t", file: !25, line: 60, baseType: !15)
!25 = !DIFile(filename: "/usr/include/x86_64-linux-gnu/bits/pthreadtypes.h", directory: "/data/download/cmake/cmake-master/Utilities/cmlibuv")
!26 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !27, size: 64, align: 64)
!27 = !DISubroutineType(types: !28)
!28 = !{null, !12}
!29 = !{}
!30 = distinct !DISubprogram(name: "uv_thread_self", scope: !1, file: !1, line: 84, type: !31, isLocal: false, isDefinition: true, scopeLine: 84, flags: DIFlagPrototyped, isOptimized: false, variables: !29)
!31 = !DISubroutineType(types: !32)
!32 = !{!22}
!33 = distinct !DISubprogram(name: "uv_thread_join", scope: !1, file: !1, line: 88, type: !34, isLocal: false, isDefinition: true, scopeLine: 88, flags: DIFlagPrototyped, isOptimized: false, variables: !29)
!34 = !DISubroutineType(types: !35)
!35 = !{!20, !21}
!36 = distinct !DISubprogram(name: "uv_thread_equal", scope: !1, file: !1, line: 93, type: !37, isLocal: false, isDefinition: true, scopeLine: 93, flags: DIFlagPrototyped, isOptimized: false, variables: !29)
!37 = !DISubroutineType(types: !38)
!38 = !{!20, !39, !39}
!39 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !40, size: 64, align: 64)
!40 = !DIDerivedType(tag: DW_TAG_const_type, baseType: !22)
!41 = distinct !DISubprogram(name: "uv_mutex_init", scope: !1, file: !1, line: 98, type: !42, isLocal: false, isDefinition: true, scopeLine: 98, flags: DIFlagPrototyped, isOptimized: false, variables: !29)
!42 = !DISubroutineType(types: !43)
!43 = !{!20, !44}
!44 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !45, size: 64, align: 64)
!45 = !DIDerivedType(tag: DW_TAG_typedef, name: "uv_mutex_t", file: !23, line: 129, baseType: !46)
!46 = !DIDerivedType(tag: DW_TAG_typedef, name: "pthread_mutex_t", file: !25, line: 127, baseType: !47)
!47 = !DICompositeType(tag: DW_TAG_union_type, file: !25, line: 90, size: 320, align: 64, elements: !48)
!48 = !{!49, !68, !73}
!49 = !DIDerivedType(tag: DW_TAG_member, name: "__data", scope: !47, file: !25, line: 124, baseType: !50, size: 320, align: 64)
!50 = !DICompositeType(tag: DW_TAG_structure_type, name: "__pthread_mutex_s", file: !25, line: 92, size: 320, align: 64, elements: !51)
!51 = !{!52, !53, !55, !56, !57, !58, !60, !61}
!52 = !DIDerivedType(tag: DW_TAG_member, name: "__lock", scope: !50, file: !25, line: 94, baseType: !20, size: 32, align: 32)
!53 = !DIDerivedType(tag: DW_TAG_member, name: "__count", scope: !50, file: !25, line: 95, baseType: !54, size: 32, align: 32, offset: 32)
!54 = !DIBasicType(name: "unsigned int", size: 32, align: 32, encoding: DW_ATE_unsigned)
!55 = !DIDerivedType(tag: DW_TAG_member, name: "__owner", scope: !50, file: !25, line: 96, baseType: !20, size: 32, align: 32, offset: 64)
!56 = !DIDerivedType(tag: DW_TAG_member, name: "__nusers", scope: !50, file: !25, line: 98, baseType: !54, size: 32, align: 32, offset: 96)
!57 = !DIDerivedType(tag: DW_TAG_member, name: "__kind", scope: !50, file: !25, line: 102, baseType: !20, size: 32, align: 32, offset: 128)
!58 = !DIDerivedType(tag: DW_TAG_member, name: "__spins", scope: !50, file: !25, line: 104, baseType: !59, size: 16, align: 16, offset: 160)
!59 = !DIBasicType(name: "short", size: 16, align: 16, encoding: DW_ATE_signed)
!60 = !DIDerivedType(tag: DW_TAG_member, name: "__elision", scope: !50, file: !25, line: 105, baseType: !59, size: 16, align: 16, offset: 176)
!61 = !DIDerivedType(tag: DW_TAG_member, name: "__list", scope: !50, file: !25, line: 106, baseType: !62, size: 128, align: 64, offset: 192)
!62 = !DIDerivedType(tag: DW_TAG_typedef, name: "__pthread_list_t", file: !25, line: 79, baseType: !63)
!63 = !DICompositeType(tag: DW_TAG_structure_type, name: "__pthread_internal_list", file: !25, line: 75, size: 128, align: 64, elements: !64)
!64 = !{!65, !67}
!65 = !DIDerivedType(tag: DW_TAG_member, name: "__prev", scope: !63, file: !25, line: 77, baseType: !66, size: 64, align: 64)
!66 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !63, size: 64, align: 64)
!67 = !DIDerivedType(tag: DW_TAG_member, name: "__next", scope: !63, file: !25, line: 78, baseType: !66, size: 64, align: 64, offset: 64)
!68 = !DIDerivedType(tag: DW_TAG_member, name: "__size", scope: !47, file: !25, line: 125, baseType: !69, size: 320, align: 8)
!69 = !DICompositeType(tag: DW_TAG_array_type, baseType: !70, size: 320, align: 8, elements: !71)
!70 = !DIBasicType(name: "char", size: 8, align: 8, encoding: DW_ATE_signed_char)
!71 = !{!72}
!72 = !DISubrange(count: 40)
!73 = !DIDerivedType(tag: DW_TAG_member, name: "__align", scope: !47, file: !25, line: 126, baseType: !74, size: 64, align: 64)
!74 = !DIBasicType(name: "long int", size: 64, align: 64, encoding: DW_ATE_signed)
!75 = distinct !DISubprogram(name: "uv_mutex_destroy", scope: !1, file: !1, line: 121, type: !76, isLocal: false, isDefinition: true, scopeLine: 121, flags: DIFlagPrototyped, isOptimized: false, variables: !29)
!76 = !DISubroutineType(types: !77)
!77 = !{null, !44}
!78 = distinct !DISubprogram(name: "uv_mutex_lock", scope: !1, file: !1, line: 127, type: !76, isLocal: false, isDefinition: true, scopeLine: 127, flags: DIFlagPrototyped, isOptimized: false, variables: !29)
!79 = distinct !DISubprogram(name: "uv_mutex_trylock", scope: !1, file: !1, line: 133, type: !42, isLocal: false, isDefinition: true, scopeLine: 133, flags: DIFlagPrototyped, isOptimized: false, variables: !29)
!80 = distinct !DISubprogram(name: "uv_mutex_unlock", scope: !1, file: !1, line: 147, type: !76, isLocal: false, isDefinition: true, scopeLine: 147, flags: DIFlagPrototyped, isOptimized: false, variables: !29)
!81 = distinct !DISubprogram(name: "uv_rwlock_init", scope: !1, file: !1, line: 153, type: !82, isLocal: false, isDefinition: true, scopeLine: 153, flags: DIFlagPrototyped, isOptimized: false, variables: !29)
!82 = !DISubroutineType(types: !83)
!83 = !{!20, !84}
!84 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !85, size: 64, align: 64)
!85 = !DIDerivedType(tag: DW_TAG_typedef, name: "uv_rwlock_t", file: !23, line: 130, baseType: !86)
!86 = !DIDerivedType(tag: DW_TAG_typedef, name: "pthread_rwlock_t", file: !25, line: 213, baseType: !87)
!87 = !DICompositeType(tag: DW_TAG_union_type, file: !25, line: 173, size: 448, align: 64, elements: !88)
!88 = !{!89, !103, !107}
!89 = !DIDerivedType(tag: DW_TAG_member, name: "__data", scope: !87, file: !25, line: 192, baseType: !90, size: 448, align: 64)
!90 = !DICompositeType(tag: DW_TAG_structure_type, scope: !87, file: !25, line: 176, size: 448, align: 64, elements: !91)
!91 = !{!92, !93, !94, !95, !96, !97, !98, !99, !100, !101, !102}
!92 = !DIDerivedType(tag: DW_TAG_member, name: "__lock", scope: !90, file: !25, line: 178, baseType: !20, size: 32, align: 32)
!93 = !DIDerivedType(tag: DW_TAG_member, name: "__nr_readers", scope: !90, file: !25, line: 179, baseType: !54, size: 32, align: 32, offset: 32)
!94 = !DIDerivedType(tag: DW_TAG_member, name: "__readers_wakeup", scope: !90, file: !25, line: 180, baseType: !54, size: 32, align: 32, offset: 64)
!95 = !DIDerivedType(tag: DW_TAG_member, name: "__writer_wakeup", scope: !90, file: !25, line: 181, baseType: !54, size: 32, align: 32, offset: 96)
!96 = !DIDerivedType(tag: DW_TAG_member, name: "__nr_readers_queued", scope: !90, file: !25, line: 182, baseType: !54, size: 32, align: 32, offset: 128)
!97 = !DIDerivedType(tag: DW_TAG_member, name: "__nr_writers_queued", scope: !90, file: !25, line: 183, baseType: !54, size: 32, align: 32, offset: 160)
!98 = !DIDerivedType(tag: DW_TAG_member, name: "__writer", scope: !90, file: !25, line: 184, baseType: !20, size: 32, align: 32, offset: 192)
!99 = !DIDerivedType(tag: DW_TAG_member, name: "__shared", scope: !90, file: !25, line: 185, baseType: !20, size: 32, align: 32, offset: 224)
!100 = !DIDerivedType(tag: DW_TAG_member, name: "__pad1", scope: !90, file: !25, line: 186, baseType: !15, size: 64, align: 64, offset: 256)
!101 = !DIDerivedType(tag: DW_TAG_member, name: "__pad2", scope: !90, file: !25, line: 187, baseType: !15, size: 64, align: 64, offset: 320)
!102 = !DIDerivedType(tag: DW_TAG_member, name: "__flags", scope: !90, file: !25, line: 190, baseType: !54, size: 32, align: 32, offset: 384)
!103 = !DIDerivedType(tag: DW_TAG_member, name: "__size", scope: !87, file: !25, line: 211, baseType: !104, size: 448, align: 8)
!104 = !DICompositeType(tag: DW_TAG_array_type, baseType: !70, size: 448, align: 8, elements: !105)
!105 = !{!106}
!106 = !DISubrange(count: 56)
!107 = !DIDerivedType(tag: DW_TAG_member, name: "__align", scope: !87, file: !25, line: 212, baseType: !74, size: 64, align: 64)
!108 = distinct !DISubprogram(name: "uv_rwlock_destroy", scope: !1, file: !1, line: 158, type: !109, isLocal: false, isDefinition: true, scopeLine: 158, flags: DIFlagPrototyped, isOptimized: false, variables: !29)
!109 = !DISubroutineType(types: !110)
!110 = !{null, !84}
!111 = distinct !DISubprogram(name: "uv_rwlock_rdlock", scope: !1, file: !1, line: 164, type: !109, isLocal: false, isDefinition: true, scopeLine: 164, flags: DIFlagPrototyped, isOptimized: false, variables: !29)
!112 = distinct !DISubprogram(name: "uv_rwlock_tryrdlock", scope: !1, file: !1, line: 170, type: !82, isLocal: false, isDefinition: true, scopeLine: 170, flags: DIFlagPrototyped, isOptimized: false, variables: !29)
!113 = distinct !DISubprogram(name: "uv_rwlock_rdunlock", scope: !1, file: !1, line: 184, type: !109, isLocal: false, isDefinition: true, scopeLine: 184, flags: DIFlagPrototyped, isOptimized: false, variables: !29)
!114 = distinct !DISubprogram(name: "uv_rwlock_wrlock", scope: !1, file: !1, line: 190, type: !109, isLocal: false, isDefinition: true, scopeLine: 190, flags: DIFlagPrototyped, isOptimized: false, variables: !29)
!115 = distinct !DISubprogram(name: "uv_rwlock_trywrlock", scope: !1, file: !1, line: 196, type: !82, isLocal: false, isDefinition: true, scopeLine: 196, flags: DIFlagPrototyped, isOptimized: false, variables: !29)
!116 = distinct !DISubprogram(name: "uv_rwlock_wrunlock", scope: !1, file: !1, line: 210, type: !109, isLocal: false, isDefinition: true, scopeLine: 210, flags: DIFlagPrototyped, isOptimized: false, variables: !29)
!117 = distinct !DISubprogram(name: "uv_once", scope: !1, file: !1, line: 216, type: !118, isLocal: false, isDefinition: true, scopeLine: 216, flags: DIFlagPrototyped, isOptimized: false, variables: !29)
!118 = !DISubroutineType(types: !119)
!119 = !{null, !120, !123}
!120 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !121, size: 64, align: 64)
!121 = !DIDerivedType(tag: DW_TAG_typedef, name: "uv_once_t", file: !23, line: 127, baseType: !122)
!122 = !DIDerivedType(tag: DW_TAG_typedef, name: "pthread_once_t", file: !25, line: 167, baseType: !20)
!123 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !124, size: 64, align: 64)
!124 = !DISubroutineType(types: !125)
!125 = !{null}
!126 = distinct !DISubprogram(name: "uv_sem_init", scope: !1, file: !1, line: 361, type: !127, isLocal: false, isDefinition: true, scopeLine: 361, flags: DIFlagPrototyped, isOptimized: false, variables: !29)
!127 = !DISubroutineType(types: !128)
!128 = !{!20, !129, !54}
!129 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !130, size: 64, align: 64)
!130 = !DIDerivedType(tag: DW_TAG_typedef, name: "uv_sem_t", file: !23, line: 131, baseType: !131)
!131 = !DIDerivedType(tag: DW_TAG_typedef, name: "sem_t", file: !132, line: 40, baseType: !133)
!132 = !DIFile(filename: "/usr/include/x86_64-linux-gnu/bits/semaphore.h", directory: "/data/download/cmake/cmake-master/Utilities/cmlibuv")
!133 = !DICompositeType(tag: DW_TAG_union_type, file: !132, line: 36, size: 256, align: 64, elements: !134)
!134 = !{!135, !139}
!135 = !DIDerivedType(tag: DW_TAG_member, name: "__size", scope: !133, file: !132, line: 38, baseType: !136, size: 256, align: 8)
!136 = !DICompositeType(tag: DW_TAG_array_type, baseType: !70, size: 256, align: 8, elements: !137)
!137 = !{!138}
!138 = !DISubrange(count: 32)
!139 = !DIDerivedType(tag: DW_TAG_member, name: "__align", scope: !133, file: !132, line: 39, baseType: !74, size: 64, align: 64)
!140 = distinct !DISubprogram(name: "uv_sem_destroy", scope: !1, file: !1, line: 368, type: !141, isLocal: false, isDefinition: true, scopeLine: 368, flags: DIFlagPrototyped, isOptimized: false, variables: !29)
!141 = !DISubroutineType(types: !142)
!142 = !{null, !129}
!143 = distinct !DISubprogram(name: "uv_sem_post", scope: !1, file: !1, line: 374, type: !141, isLocal: false, isDefinition: true, scopeLine: 374, flags: DIFlagPrototyped, isOptimized: false, variables: !29)
!144 = distinct !DISubprogram(name: "uv_sem_wait", scope: !1, file: !1, line: 380, type: !141, isLocal: false, isDefinition: true, scopeLine: 380, flags: DIFlagPrototyped, isOptimized: false, variables: !29)
!145 = distinct !DISubprogram(name: "uv_sem_trywait", scope: !1, file: !1, line: 392, type: !146, isLocal: false, isDefinition: true, scopeLine: 392, flags: DIFlagPrototyped, isOptimized: false, variables: !29)
!146 = !DISubroutineType(types: !147)
!147 = !{!20, !129}
!148 = distinct !DISubprogram(name: "uv_cond_init", scope: !1, file: !1, line: 419, type: !149, isLocal: false, isDefinition: true, scopeLine: 419, flags: DIFlagPrototyped, isOptimized: false, variables: !29)
!149 = !DISubroutineType(types: !150)
!150 = !{!20, !151}
!151 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !152, size: 64, align: 64)
!152 = !DIDerivedType(tag: DW_TAG_typedef, name: "uv_cond_t", file: !23, line: 132, baseType: !153)
!153 = !DIDerivedType(tag: DW_TAG_typedef, name: "pthread_cond_t", file: !25, line: 153, baseType: !154)
!154 = !DICompositeType(tag: DW_TAG_union_type, file: !25, line: 138, size: 384, align: 64, elements: !155)
!155 = !{!156, !168, !172}
!156 = !DIDerivedType(tag: DW_TAG_member, name: "__data", scope: !154, file: !25, line: 150, baseType: !157, size: 384, align: 64)
!157 = !DICompositeType(tag: DW_TAG_structure_type, scope: !154, file: !25, line: 140, size: 384, align: 64, elements: !158)
!158 = !{!159, !160, !161, !163, !164, !165, !166, !167}
!159 = !DIDerivedType(tag: DW_TAG_member, name: "__lock", scope: !157, file: !25, line: 142, baseType: !20, size: 32, align: 32)
!160 = !DIDerivedType(tag: DW_TAG_member, name: "__futex", scope: !157, file: !25, line: 143, baseType: !54, size: 32, align: 32, offset: 32)
!161 = !DIDerivedType(tag: DW_TAG_member, name: "__total_seq", scope: !157, file: !25, line: 144, baseType: !162, size: 64, align: 64, offset: 64)
!162 = !DIBasicType(name: "long long unsigned int", size: 64, align: 64, encoding: DW_ATE_unsigned)
!163 = !DIDerivedType(tag: DW_TAG_member, name: "__wakeup_seq", scope: !157, file: !25, line: 145, baseType: !162, size: 64, align: 64, offset: 128)
!164 = !DIDerivedType(tag: DW_TAG_member, name: "__woken_seq", scope: !157, file: !25, line: 146, baseType: !162, size: 64, align: 64, offset: 192)
!165 = !DIDerivedType(tag: DW_TAG_member, name: "__mutex", scope: !157, file: !25, line: 147, baseType: !12, size: 64, align: 64, offset: 256)
!166 = !DIDerivedType(tag: DW_TAG_member, name: "__nwaiters", scope: !157, file: !25, line: 148, baseType: !54, size: 32, align: 32, offset: 320)
!167 = !DIDerivedType(tag: DW_TAG_member, name: "__broadcast_seq", scope: !157, file: !25, line: 149, baseType: !54, size: 32, align: 32, offset: 352)
!168 = !DIDerivedType(tag: DW_TAG_member, name: "__size", scope: !154, file: !25, line: 151, baseType: !169, size: 384, align: 8)
!169 = !DICompositeType(tag: DW_TAG_array_type, baseType: !70, size: 384, align: 8, elements: !170)
!170 = !{!171}
!171 = !DISubrange(count: 48)
!172 = !DIDerivedType(tag: DW_TAG_member, name: "__align", scope: !154, file: !25, line: 152, baseType: !173, size: 64, align: 64)
!173 = !DIBasicType(name: "long long int", size: 64, align: 64, encoding: DW_ATE_signed)
!174 = distinct !DISubprogram(name: "uv_cond_destroy", scope: !1, file: !1, line: 452, type: !175, isLocal: false, isDefinition: true, scopeLine: 452, flags: DIFlagPrototyped, isOptimized: false, variables: !29)
!175 = !DISubroutineType(types: !176)
!176 = !{null, !151}
!177 = distinct !DISubprogram(name: "uv_cond_signal", scope: !1, file: !1, line: 486, type: !175, isLocal: false, isDefinition: true, scopeLine: 486, flags: DIFlagPrototyped, isOptimized: false, variables: !29)
!178 = distinct !DISubprogram(name: "uv_cond_broadcast", scope: !1, file: !1, line: 491, type: !175, isLocal: false, isDefinition: true, scopeLine: 491, flags: DIFlagPrototyped, isOptimized: false, variables: !29)
!179 = distinct !DISubprogram(name: "uv_cond_wait", scope: !1, file: !1, line: 496, type: !180, isLocal: false, isDefinition: true, scopeLine: 496, flags: DIFlagPrototyped, isOptimized: false, variables: !29)
!180 = !DISubroutineType(types: !181)
!181 = !{null, !151, !44}
!182 = distinct !DISubprogram(name: "uv_cond_timedwait", scope: !1, file: !1, line: 502, type: !183, isLocal: false, isDefinition: true, scopeLine: 502, flags: DIFlagPrototyped, isOptimized: false, variables: !29)
!183 = !DISubroutineType(types: !184)
!184 = !{!20, !151, !44, !13}
!185 = distinct !DISubprogram(name: "uv_barrier_init", scope: !1, file: !1, line: 537, type: !186, isLocal: false, isDefinition: true, scopeLine: 537, flags: DIFlagPrototyped, isOptimized: false, variables: !29)
!186 = !DISubroutineType(types: !187)
!187 = !{!20, !188, !54}
!188 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !189, size: 64, align: 64)
!189 = !DIDerivedType(tag: DW_TAG_typedef, name: "uv_barrier_t", file: !23, line: 134, baseType: !190)
!190 = !DIDerivedType(tag: DW_TAG_typedef, name: "pthread_barrier_t", file: !25, line: 234, baseType: !191)
!191 = !DICompositeType(tag: DW_TAG_union_type, file: !25, line: 230, size: 256, align: 64, elements: !192)
!192 = !{!193, !194}
!193 = !DIDerivedType(tag: DW_TAG_member, name: "__size", scope: !191, file: !25, line: 232, baseType: !136, size: 256, align: 8)
!194 = !DIDerivedType(tag: DW_TAG_member, name: "__align", scope: !191, file: !25, line: 233, baseType: !74, size: 64, align: 64)
!195 = distinct !DISubprogram(name: "uv_barrier_destroy", scope: !1, file: !1, line: 542, type: !196, isLocal: false, isDefinition: true, scopeLine: 542, flags: DIFlagPrototyped, isOptimized: false, variables: !29)
!196 = !DISubroutineType(types: !197)
!197 = !{null, !188}
!198 = distinct !DISubprogram(name: "uv_barrier_wait", scope: !1, file: !1, line: 548, type: !199, isLocal: false, isDefinition: true, scopeLine: 548, flags: DIFlagPrototyped, isOptimized: false, variables: !29)
!199 = !DISubroutineType(types: !200)
!200 = !{!20, !188}
!201 = distinct !DISubprogram(name: "uv_key_create", scope: !1, file: !1, line: 556, type: !202, isLocal: false, isDefinition: true, scopeLine: 556, flags: DIFlagPrototyped, isOptimized: false, variables: !29)
!202 = !DISubroutineType(types: !203)
!203 = !{!20, !204}
!204 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !205, size: 64, align: 64)
!205 = !DIDerivedType(tag: DW_TAG_typedef, name: "uv_key_t", file: !23, line: 133, baseType: !206)
!206 = !DIDerivedType(tag: DW_TAG_typedef, name: "pthread_key_t", file: !25, line: 163, baseType: !54)
!207 = distinct !DISubprogram(name: "uv_key_delete", scope: !1, file: !1, line: 561, type: !208, isLocal: false, isDefinition: true, scopeLine: 561, flags: DIFlagPrototyped, isOptimized: false, variables: !29)
!208 = !DISubroutineType(types: !209)
!209 = !{null, !204}
!210 = distinct !DISubprogram(name: "uv_key_get", scope: !1, file: !1, line: 567, type: !211, isLocal: false, isDefinition: true, scopeLine: 567, flags: DIFlagPrototyped, isOptimized: false, variables: !29)
!211 = !DISubroutineType(types: !212)
!212 = !{!12, !204}
!213 = distinct !DISubprogram(name: "uv_key_set", scope: !1, file: !1, line: 572, type: !214, isLocal: false, isDefinition: true, scopeLine: 572, flags: DIFlagPrototyped, isOptimized: false, variables: !29)
!214 = !DISubroutineType(types: !215)
!215 = !{null, !204, !12}
!216 = !{i32 2, !"Dwarf Version", i32 4}
!217 = !{i32 2, !"Debug Info Version", i32 3}
!218 = !{!"clang version 3.8.0 (tags/RELEASE_380/final)"}
!219 = !DILocalVariable(name: "tid", arg: 1, scope: !17, file: !1, line: 44, type: !21)
!220 = !DIExpression()
!221 = !DILocation(line: 44, column: 35, scope: !17)
!222 = !DILocalVariable(name: "entry", arg: 2, scope: !17, file: !1, line: 44, type: !26)
!223 = !DILocation(line: 44, column: 47, scope: !17)
!224 = !DILocalVariable(name: "arg", arg: 3, scope: !17, file: !1, line: 44, type: !12)
!225 = !DILocation(line: 44, column: 72, scope: !17)
!226 = !DILocalVariable(name: "err", scope: !17, file: !1, line: 45, type: !20)
!227 = !DILocation(line: 45, column: 7, scope: !17)
!228 = !DILocalVariable(name: "attr", scope: !17, file: !1, line: 46, type: !229)
!229 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !230, size: 64, align: 64)
!230 = !DIDerivedType(tag: DW_TAG_typedef, name: "pthread_attr_t", file: !25, line: 69, baseType: !231)
!231 = !DICompositeType(tag: DW_TAG_union_type, name: "pthread_attr_t", file: !25, line: 63, size: 448, align: 64, elements: !232)
!232 = !{!233, !234}
!233 = !DIDerivedType(tag: DW_TAG_member, name: "__size", scope: !231, file: !25, line: 65, baseType: !104, size: 448, align: 8)
!234 = !DIDerivedType(tag: DW_TAG_member, name: "__align", scope: !231, file: !25, line: 66, baseType: !74, size: 64, align: 64)
!235 = !DILocation(line: 46, column: 19, scope: !17)
!236 = !DILocation(line: 72, column: 8, scope: !17)
!237 = !DILocation(line: 75, column: 24, scope: !17)
!238 = !DILocation(line: 75, column: 29, scope: !17)
!239 = !DILocation(line: 75, column: 53, scope: !17)
!240 = !DILocation(line: 75, column: 35, scope: !17)
!241 = !DILocation(line: 75, column: 60, scope: !17)
!242 = !DILocation(line: 75, column: 9, scope: !17)
!243 = !DILocation(line: 75, column: 7, scope: !17)
!244 = !DILocation(line: 77, column: 7, scope: !245)
!245 = distinct !DILexicalBlock(scope: !17, file: !1, line: 77, column: 7)
!246 = !DILocation(line: 77, column: 12, scope: !245)
!247 = !DILocation(line: 77, column: 7, scope: !17)
!248 = !DILocation(line: 78, column: 26, scope: !245)
!249 = !DILocation(line: 78, column: 5, scope: !245)
!250 = !DILocation(line: 80, column: 11, scope: !17)
!251 = !DILocation(line: 80, column: 10, scope: !17)
!252 = !DILocation(line: 80, column: 3, scope: !17)
!253 = !DILocation(line: 85, column: 10, scope: !30)
!254 = !DILocation(line: 85, column: 3, scope: !30)
!255 = !DILocalVariable(name: "tid", arg: 1, scope: !33, file: !1, line: 88, type: !21)
!256 = !DILocation(line: 88, column: 33, scope: !33)
!257 = !DILocation(line: 89, column: 25, scope: !33)
!258 = !DILocation(line: 89, column: 24, scope: !33)
!259 = !DILocation(line: 89, column: 11, scope: !33)
!260 = !DILocation(line: 89, column: 10, scope: !33)
!261 = !DILocation(line: 89, column: 3, scope: !33)
!262 = !DILocalVariable(name: "t1", arg: 1, scope: !36, file: !1, line: 93, type: !39)
!263 = !DILocation(line: 93, column: 40, scope: !36)
!264 = !DILocalVariable(name: "t2", arg: 2, scope: !36, file: !1, line: 93, type: !39)
!265 = !DILocation(line: 93, column: 63, scope: !36)
!266 = !DILocation(line: 94, column: 25, scope: !36)
!267 = !DILocation(line: 94, column: 24, scope: !36)
!268 = !DILocation(line: 94, column: 30, scope: !36)
!269 = !DILocation(line: 94, column: 29, scope: !36)
!270 = !DILocation(line: 94, column: 10, scope: !36)
!271 = !DILocation(line: 94, column: 3, scope: !36)
!272 = !DILocalVariable(name: "mutex", arg: 1, scope: !41, file: !1, line: 98, type: !44)
!273 = !DILocation(line: 98, column: 31, scope: !41)
!274 = !DILocation(line: 100, column: 30, scope: !41)
!275 = !DILocation(line: 100, column: 11, scope: !41)
!276 = !DILocation(line: 100, column: 10, scope: !41)
!277 = !DILocation(line: 100, column: 3, scope: !41)
!278 = !DILocalVariable(name: "mutex", arg: 1, scope: !75, file: !1, line: 121, type: !44)
!279 = !DILocation(line: 121, column: 35, scope: !75)
!280 = !DILocation(line: 122, column: 29, scope: !281)
!281 = distinct !DILexicalBlock(scope: !75, file: !1, line: 122, column: 7)
!282 = !DILocation(line: 122, column: 7, scope: !281)
!283 = !DILocation(line: 122, column: 7, scope: !75)
!284 = !DILocation(line: 123, column: 5, scope: !281)
!285 = !DILocation(line: 124, column: 1, scope: !75)
!286 = !DILocalVariable(name: "mutex", arg: 1, scope: !78, file: !1, line: 127, type: !44)
!287 = !DILocation(line: 127, column: 32, scope: !78)
!288 = !DILocation(line: 128, column: 26, scope: !289)
!289 = distinct !DILexicalBlock(scope: !78, file: !1, line: 128, column: 7)
!290 = !DILocation(line: 128, column: 7, scope: !289)
!291 = !DILocation(line: 128, column: 7, scope: !78)
!292 = !DILocation(line: 129, column: 5, scope: !289)
!293 = !DILocation(line: 130, column: 1, scope: !78)
!294 = !DILocalVariable(name: "mutex", arg: 1, scope: !79, file: !1, line: 133, type: !44)
!295 = !DILocation(line: 133, column: 34, scope: !79)
!296 = !DILocalVariable(name: "err", scope: !79, file: !1, line: 134, type: !20)
!297 = !DILocation(line: 134, column: 7, scope: !79)
!298 = !DILocation(line: 136, column: 31, scope: !79)
!299 = !DILocation(line: 136, column: 9, scope: !79)
!300 = !DILocation(line: 136, column: 7, scope: !79)
!301 = !DILocation(line: 137, column: 7, scope: !302)
!302 = distinct !DILexicalBlock(scope: !79, file: !1, line: 137, column: 7)
!303 = !DILocation(line: 137, column: 7, scope: !79)
!304 = !DILocation(line: 138, column: 9, scope: !305)
!305 = distinct !DILexicalBlock(scope: !306, file: !1, line: 138, column: 9)
!306 = distinct !DILexicalBlock(scope: !302, file: !1, line: 137, column: 12)
!307 = !DILocation(line: 138, column: 13, scope: !305)
!308 = !DILocation(line: 138, column: 22, scope: !305)
!309 = !DILocation(line: 138, column: 25, scope: !310)
!310 = !DILexicalBlockFile(scope: !305, file: !1, discriminator: 1)
!311 = !DILocation(line: 138, column: 29, scope: !310)
!312 = !DILocation(line: 138, column: 9, scope: !310)
!313 = !DILocation(line: 139, column: 7, scope: !305)
!314 = !DILocation(line: 140, column: 5, scope: !306)
!315 = !DILocation(line: 143, column: 3, scope: !79)
!316 = !DILocation(line: 144, column: 1, scope: !79)
!317 = !DILocalVariable(name: "mutex", arg: 1, scope: !80, file: !1, line: 147, type: !44)
!318 = !DILocation(line: 147, column: 34, scope: !80)
!319 = !DILocation(line: 148, column: 28, scope: !320)
!320 = distinct !DILexicalBlock(scope: !80, file: !1, line: 148, column: 7)
!321 = !DILocation(line: 148, column: 7, scope: !320)
!322 = !DILocation(line: 148, column: 7, scope: !80)
!323 = !DILocation(line: 149, column: 5, scope: !320)
!324 = !DILocation(line: 150, column: 1, scope: !80)
!325 = !DILocalVariable(name: "rwlock", arg: 1, scope: !81, file: !1, line: 153, type: !84)
!326 = !DILocation(line: 153, column: 33, scope: !81)
!327 = !DILocation(line: 154, column: 31, scope: !81)
!328 = !DILocation(line: 154, column: 11, scope: !81)
!329 = !DILocation(line: 154, column: 10, scope: !81)
!330 = !DILocation(line: 154, column: 3, scope: !81)
!331 = !DILocalVariable(name: "rwlock", arg: 1, scope: !108, file: !1, line: 158, type: !84)
!332 = !DILocation(line: 158, column: 37, scope: !108)
!333 = !DILocation(line: 159, column: 30, scope: !334)
!334 = distinct !DILexicalBlock(scope: !108, file: !1, line: 159, column: 7)
!335 = !DILocation(line: 159, column: 7, scope: !334)
!336 = !DILocation(line: 159, column: 7, scope: !108)
!337 = !DILocation(line: 160, column: 5, scope: !334)
!338 = !DILocation(line: 161, column: 1, scope: !108)
!339 = !DILocalVariable(name: "rwlock", arg: 1, scope: !111, file: !1, line: 164, type: !84)
!340 = !DILocation(line: 164, column: 36, scope: !111)
!341 = !DILocation(line: 165, column: 29, scope: !342)
!342 = distinct !DILexicalBlock(scope: !111, file: !1, line: 165, column: 7)
!343 = !DILocation(line: 165, column: 7, scope: !342)
!344 = !DILocation(line: 165, column: 7, scope: !111)
!345 = !DILocation(line: 166, column: 5, scope: !342)
!346 = !DILocation(line: 167, column: 1, scope: !111)
!347 = !DILocalVariable(name: "rwlock", arg: 1, scope: !112, file: !1, line: 170, type: !84)
!348 = !DILocation(line: 170, column: 38, scope: !112)
!349 = !DILocalVariable(name: "err", scope: !112, file: !1, line: 171, type: !20)
!350 = !DILocation(line: 171, column: 7, scope: !112)
!351 = !DILocation(line: 173, column: 34, scope: !112)
!352 = !DILocation(line: 173, column: 9, scope: !112)
!353 = !DILocation(line: 173, column: 7, scope: !112)
!354 = !DILocation(line: 174, column: 7, scope: !355)
!355 = distinct !DILexicalBlock(scope: !112, file: !1, line: 174, column: 7)
!356 = !DILocation(line: 174, column: 7, scope: !112)
!357 = !DILocation(line: 175, column: 9, scope: !358)
!358 = distinct !DILexicalBlock(scope: !359, file: !1, line: 175, column: 9)
!359 = distinct !DILexicalBlock(scope: !355, file: !1, line: 174, column: 12)
!360 = !DILocation(line: 175, column: 13, scope: !358)
!361 = !DILocation(line: 175, column: 22, scope: !358)
!362 = !DILocation(line: 175, column: 25, scope: !363)
!363 = !DILexicalBlockFile(scope: !358, file: !1, discriminator: 1)
!364 = !DILocation(line: 175, column: 29, scope: !363)
!365 = !DILocation(line: 175, column: 9, scope: !363)
!366 = !DILocation(line: 176, column: 7, scope: !358)
!367 = !DILocation(line: 177, column: 5, scope: !359)
!368 = !DILocation(line: 180, column: 3, scope: !112)
!369 = !DILocation(line: 181, column: 1, scope: !112)
!370 = !DILocalVariable(name: "rwlock", arg: 1, scope: !113, file: !1, line: 184, type: !84)
!371 = !DILocation(line: 184, column: 38, scope: !113)
!372 = !DILocation(line: 185, column: 29, scope: !373)
!373 = distinct !DILexicalBlock(scope: !113, file: !1, line: 185, column: 7)
!374 = !DILocation(line: 185, column: 7, scope: !373)
!375 = !DILocation(line: 185, column: 7, scope: !113)
!376 = !DILocation(line: 186, column: 5, scope: !373)
!377 = !DILocation(line: 187, column: 1, scope: !113)
!378 = !DILocalVariable(name: "rwlock", arg: 1, scope: !114, file: !1, line: 190, type: !84)
!379 = !DILocation(line: 190, column: 36, scope: !114)
!380 = !DILocation(line: 191, column: 29, scope: !381)
!381 = distinct !DILexicalBlock(scope: !114, file: !1, line: 191, column: 7)
!382 = !DILocation(line: 191, column: 7, scope: !381)
!383 = !DILocation(line: 191, column: 7, scope: !114)
!384 = !DILocation(line: 192, column: 5, scope: !381)
!385 = !DILocation(line: 193, column: 1, scope: !114)
!386 = !DILocalVariable(name: "rwlock", arg: 1, scope: !115, file: !1, line: 196, type: !84)
!387 = !DILocation(line: 196, column: 38, scope: !115)
!388 = !DILocalVariable(name: "err", scope: !115, file: !1, line: 197, type: !20)
!389 = !DILocation(line: 197, column: 7, scope: !115)
!390 = !DILocation(line: 199, column: 34, scope: !115)
!391 = !DILocation(line: 199, column: 9, scope: !115)
!392 = !DILocation(line: 199, column: 7, scope: !115)
!393 = !DILocation(line: 200, column: 7, scope: !394)
!394 = distinct !DILexicalBlock(scope: !115, file: !1, line: 200, column: 7)
!395 = !DILocation(line: 200, column: 7, scope: !115)
!396 = !DILocation(line: 201, column: 9, scope: !397)
!397 = distinct !DILexicalBlock(scope: !398, file: !1, line: 201, column: 9)
!398 = distinct !DILexicalBlock(scope: !394, file: !1, line: 200, column: 12)
!399 = !DILocation(line: 201, column: 13, scope: !397)
!400 = !DILocation(line: 201, column: 22, scope: !397)
!401 = !DILocation(line: 201, column: 25, scope: !402)
!402 = !DILexicalBlockFile(scope: !397, file: !1, discriminator: 1)
!403 = !DILocation(line: 201, column: 29, scope: !402)
!404 = !DILocation(line: 201, column: 9, scope: !402)
!405 = !DILocation(line: 202, column: 7, scope: !397)
!406 = !DILocation(line: 203, column: 5, scope: !398)
!407 = !DILocation(line: 206, column: 3, scope: !115)
!408 = !DILocation(line: 207, column: 1, scope: !115)
!409 = !DILocalVariable(name: "rwlock", arg: 1, scope: !116, file: !1, line: 210, type: !84)
!410 = !DILocation(line: 210, column: 38, scope: !116)
!411 = !DILocation(line: 211, column: 29, scope: !412)
!412 = distinct !DILexicalBlock(scope: !116, file: !1, line: 211, column: 7)
!413 = !DILocation(line: 211, column: 7, scope: !412)
!414 = !DILocation(line: 211, column: 7, scope: !116)
!415 = !DILocation(line: 212, column: 5, scope: !412)
!416 = !DILocation(line: 213, column: 1, scope: !116)
!417 = !DILocalVariable(name: "guard", arg: 1, scope: !117, file: !1, line: 216, type: !120)
!418 = !DILocation(line: 216, column: 25, scope: !117)
!419 = !DILocalVariable(name: "callback", arg: 2, scope: !117, file: !1, line: 216, type: !123)
!420 = !DILocation(line: 216, column: 39, scope: !117)
!421 = !DILocation(line: 217, column: 20, scope: !422)
!422 = distinct !DILexicalBlock(scope: !117, file: !1, line: 217, column: 7)
!423 = !DILocation(line: 217, column: 27, scope: !422)
!424 = !DILocation(line: 217, column: 7, scope: !422)
!425 = !DILocation(line: 217, column: 7, scope: !117)
!426 = !DILocation(line: 218, column: 5, scope: !422)
!427 = !DILocation(line: 219, column: 1, scope: !117)
!428 = !DILocalVariable(name: "sem", arg: 1, scope: !126, file: !1, line: 361, type: !129)
!429 = !DILocation(line: 361, column: 27, scope: !126)
!430 = !DILocalVariable(name: "value", arg: 2, scope: !126, file: !1, line: 361, type: !54)
!431 = !DILocation(line: 361, column: 45, scope: !126)
!432 = !DILocation(line: 362, column: 16, scope: !433)
!433 = distinct !DILexicalBlock(scope: !126, file: !1, line: 362, column: 7)
!434 = !DILocation(line: 362, column: 24, scope: !433)
!435 = !DILocation(line: 362, column: 7, scope: !433)
!436 = !DILocation(line: 362, column: 7, scope: !126)
!437 = !DILocation(line: 363, column: 13, scope: !433)
!438 = !DILocation(line: 363, column: 12, scope: !433)
!439 = !DILocation(line: 363, column: 5, scope: !433)
!440 = !DILocation(line: 364, column: 3, scope: !126)
!441 = !DILocation(line: 365, column: 1, scope: !126)
!442 = !DILocalVariable(name: "sem", arg: 1, scope: !140, file: !1, line: 368, type: !129)
!443 = !DILocation(line: 368, column: 31, scope: !140)
!444 = !DILocation(line: 369, column: 19, scope: !445)
!445 = distinct !DILexicalBlock(scope: !140, file: !1, line: 369, column: 7)
!446 = !DILocation(line: 369, column: 7, scope: !445)
!447 = !DILocation(line: 369, column: 7, scope: !140)
!448 = !DILocation(line: 370, column: 5, scope: !445)
!449 = !DILocation(line: 371, column: 1, scope: !140)
!450 = !DILocalVariable(name: "sem", arg: 1, scope: !143, file: !1, line: 374, type: !129)
!451 = !DILocation(line: 374, column: 28, scope: !143)
!452 = !DILocation(line: 375, column: 16, scope: !453)
!453 = distinct !DILexicalBlock(scope: !143, file: !1, line: 375, column: 7)
!454 = !DILocation(line: 375, column: 7, scope: !453)
!455 = !DILocation(line: 375, column: 7, scope: !143)
!456 = !DILocation(line: 376, column: 5, scope: !453)
!457 = !DILocation(line: 377, column: 1, scope: !143)
!458 = !DILocalVariable(name: "sem", arg: 1, scope: !144, file: !1, line: 380, type: !129)
!459 = !DILocation(line: 380, column: 28, scope: !144)
!460 = !DILocalVariable(name: "r", scope: !144, file: !1, line: 381, type: !20)
!461 = !DILocation(line: 381, column: 7, scope: !144)
!462 = !DILocation(line: 383, column: 3, scope: !144)
!463 = !DILocation(line: 384, column: 18, scope: !144)
!464 = !DILocation(line: 384, column: 9, scope: !144)
!465 = !DILocation(line: 384, column: 7, scope: !144)
!466 = !DILocation(line: 384, column: 5, scope: !144)
!467 = !DILocation(line: 385, column: 10, scope: !144)
!468 = !DILocation(line: 385, column: 12, scope: !144)
!469 = !DILocation(line: 385, column: 18, scope: !144)
!470 = !DILocation(line: 385, column: 21, scope: !471)
!471 = !DILexicalBlockFile(scope: !144, file: !1, discriminator: 1)
!472 = !DILocation(line: 385, column: 27, scope: !471)
!473 = !DILocation(line: 384, column: 5, scope: !471)
!474 = !DILocation(line: 387, column: 7, scope: !475)
!475 = distinct !DILexicalBlock(scope: !144, file: !1, line: 387, column: 7)
!476 = !DILocation(line: 387, column: 7, scope: !144)
!477 = !DILocation(line: 388, column: 5, scope: !475)
!478 = !DILocation(line: 389, column: 1, scope: !144)
!479 = !DILocalVariable(name: "sem", arg: 1, scope: !145, file: !1, line: 392, type: !129)
!480 = !DILocation(line: 392, column: 30, scope: !145)
!481 = !DILocalVariable(name: "r", scope: !145, file: !1, line: 393, type: !20)
!482 = !DILocation(line: 393, column: 7, scope: !145)
!483 = !DILocation(line: 395, column: 3, scope: !145)
!484 = !DILocation(line: 396, column: 21, scope: !145)
!485 = !DILocation(line: 396, column: 9, scope: !145)
!486 = !DILocation(line: 396, column: 7, scope: !145)
!487 = !DILocation(line: 396, column: 5, scope: !145)
!488 = !DILocation(line: 397, column: 10, scope: !145)
!489 = !DILocation(line: 397, column: 12, scope: !145)
!490 = !DILocation(line: 397, column: 18, scope: !145)
!491 = !DILocation(line: 397, column: 21, scope: !492)
!492 = !DILexicalBlockFile(scope: !145, file: !1, discriminator: 1)
!493 = !DILocation(line: 397, column: 27, scope: !492)
!494 = !DILocation(line: 396, column: 5, scope: !492)
!495 = !DILocation(line: 399, column: 7, scope: !496)
!496 = distinct !DILexicalBlock(scope: !145, file: !1, line: 399, column: 7)
!497 = !DILocation(line: 399, column: 7, scope: !145)
!498 = !DILocation(line: 400, column: 9, scope: !499)
!499 = distinct !DILexicalBlock(scope: !500, file: !1, line: 400, column: 9)
!500 = distinct !DILexicalBlock(scope: !496, file: !1, line: 399, column: 10)
!501 = !DILocation(line: 400, column: 15, scope: !499)
!502 = !DILocation(line: 400, column: 9, scope: !500)
!503 = !DILocation(line: 401, column: 7, scope: !499)
!504 = !DILocation(line: 402, column: 5, scope: !500)
!505 = !DILocation(line: 405, column: 3, scope: !145)
!506 = !DILocation(line: 406, column: 1, scope: !145)
!507 = !DILocalVariable(name: "cond", arg: 1, scope: !148, file: !1, line: 419, type: !151)
!508 = !DILocation(line: 419, column: 29, scope: !148)
!509 = !DILocalVariable(name: "attr", scope: !148, file: !1, line: 420, type: !510)
!510 = !DIDerivedType(tag: DW_TAG_typedef, name: "pthread_condattr_t", file: !25, line: 159, baseType: !511)
!511 = !DICompositeType(tag: DW_TAG_union_type, file: !25, line: 155, size: 32, align: 32, elements: !512)
!512 = !{!513, !517}
!513 = !DIDerivedType(tag: DW_TAG_member, name: "__size", scope: !511, file: !25, line: 157, baseType: !514, size: 32, align: 8)
!514 = !DICompositeType(tag: DW_TAG_array_type, baseType: !70, size: 32, align: 8, elements: !515)
!515 = !{!516}
!516 = !DISubrange(count: 4)
!517 = !DIDerivedType(tag: DW_TAG_member, name: "__align", scope: !511, file: !25, line: 158, baseType: !20, size: 32, align: 32)
!518 = !DILocation(line: 420, column: 22, scope: !148)
!519 = !DILocalVariable(name: "err", scope: !148, file: !1, line: 421, type: !20)
!520 = !DILocation(line: 421, column: 7, scope: !148)
!521 = !DILocation(line: 423, column: 9, scope: !148)
!522 = !DILocation(line: 423, column: 7, scope: !148)
!523 = !DILocation(line: 424, column: 7, scope: !524)
!524 = distinct !DILexicalBlock(scope: !148, file: !1, line: 424, column: 7)
!525 = !DILocation(line: 424, column: 7, scope: !148)
!526 = !DILocation(line: 425, column: 13, scope: !524)
!527 = !DILocation(line: 425, column: 12, scope: !524)
!528 = !DILocation(line: 425, column: 5, scope: !524)
!529 = !DILocation(line: 428, column: 9, scope: !148)
!530 = !DILocation(line: 428, column: 7, scope: !148)
!531 = !DILocation(line: 429, column: 7, scope: !532)
!532 = distinct !DILexicalBlock(scope: !148, file: !1, line: 429, column: 7)
!533 = !DILocation(line: 429, column: 7, scope: !148)
!534 = !DILocation(line: 430, column: 5, scope: !532)
!535 = !DILocation(line: 433, column: 27, scope: !148)
!536 = !DILocation(line: 433, column: 9, scope: !148)
!537 = !DILocation(line: 433, column: 7, scope: !148)
!538 = !DILocation(line: 434, column: 7, scope: !539)
!539 = distinct !DILexicalBlock(scope: !148, file: !1, line: 434, column: 7)
!540 = !DILocation(line: 434, column: 7, scope: !148)
!541 = !DILocation(line: 435, column: 5, scope: !539)
!542 = !DILocation(line: 437, column: 9, scope: !148)
!543 = !DILocation(line: 437, column: 7, scope: !148)
!544 = !DILocation(line: 438, column: 7, scope: !545)
!545 = distinct !DILexicalBlock(scope: !148, file: !1, line: 438, column: 7)
!546 = !DILocation(line: 438, column: 7, scope: !148)
!547 = !DILocation(line: 439, column: 5, scope: !545)
!548 = !DILocation(line: 441, column: 3, scope: !148)
!549 = !DILocation(line: 444, column: 24, scope: !148)
!550 = !DILocation(line: 444, column: 3, scope: !148)
!551 = !DILocation(line: 446, column: 3, scope: !148)
!552 = !DILocation(line: 447, column: 11, scope: !148)
!553 = !DILocation(line: 447, column: 10, scope: !148)
!554 = !DILocation(line: 447, column: 3, scope: !148)
!555 = !DILocation(line: 448, column: 1, scope: !148)
!556 = !DILocalVariable(name: "cond", arg: 1, scope: !174, file: !1, line: 452, type: !151)
!557 = !DILocation(line: 452, column: 33, scope: !174)
!558 = !DILocation(line: 482, column: 28, scope: !559)
!559 = distinct !DILexicalBlock(scope: !174, file: !1, line: 482, column: 7)
!560 = !DILocation(line: 482, column: 7, scope: !559)
!561 = !DILocation(line: 482, column: 7, scope: !174)
!562 = !DILocation(line: 483, column: 5, scope: !559)
!563 = !DILocation(line: 484, column: 1, scope: !174)
!564 = !DILocalVariable(name: "cond", arg: 1, scope: !177, file: !1, line: 486, type: !151)
!565 = !DILocation(line: 486, column: 32, scope: !177)
!566 = !DILocation(line: 487, column: 27, scope: !567)
!567 = distinct !DILexicalBlock(scope: !177, file: !1, line: 487, column: 7)
!568 = !DILocation(line: 487, column: 7, scope: !567)
!569 = !DILocation(line: 487, column: 7, scope: !177)
!570 = !DILocation(line: 488, column: 5, scope: !567)
!571 = !DILocation(line: 489, column: 1, scope: !177)
!572 = !DILocalVariable(name: "cond", arg: 1, scope: !178, file: !1, line: 491, type: !151)
!573 = !DILocation(line: 491, column: 35, scope: !178)
!574 = !DILocation(line: 492, column: 30, scope: !575)
!575 = distinct !DILexicalBlock(scope: !178, file: !1, line: 492, column: 7)
!576 = !DILocation(line: 492, column: 7, scope: !575)
!577 = !DILocation(line: 492, column: 7, scope: !178)
!578 = !DILocation(line: 493, column: 5, scope: !575)
!579 = !DILocation(line: 494, column: 1, scope: !178)
!580 = !DILocalVariable(name: "cond", arg: 1, scope: !179, file: !1, line: 496, type: !151)
!581 = !DILocation(line: 496, column: 30, scope: !179)
!582 = !DILocalVariable(name: "mutex", arg: 2, scope: !179, file: !1, line: 496, type: !44)
!583 = !DILocation(line: 496, column: 48, scope: !179)
!584 = !DILocation(line: 497, column: 25, scope: !585)
!585 = distinct !DILexicalBlock(scope: !179, file: !1, line: 497, column: 7)
!586 = !DILocation(line: 497, column: 31, scope: !585)
!587 = !DILocation(line: 497, column: 7, scope: !585)
!588 = !DILocation(line: 497, column: 7, scope: !179)
!589 = !DILocation(line: 498, column: 5, scope: !585)
!590 = !DILocation(line: 499, column: 1, scope: !179)
!591 = !DILocalVariable(name: "cond", arg: 1, scope: !182, file: !1, line: 502, type: !151)
!592 = !DILocation(line: 502, column: 34, scope: !182)
!593 = !DILocalVariable(name: "mutex", arg: 2, scope: !182, file: !1, line: 502, type: !44)
!594 = !DILocation(line: 502, column: 52, scope: !182)
!595 = !DILocalVariable(name: "timeout", arg: 3, scope: !182, file: !1, line: 502, type: !13)
!596 = !DILocation(line: 502, column: 68, scope: !182)
!597 = !DILocalVariable(name: "r", scope: !182, file: !1, line: 503, type: !20)
!598 = !DILocation(line: 503, column: 7, scope: !182)
!599 = !DILocalVariable(name: "ts", scope: !182, file: !1, line: 504, type: !600)
!600 = !DICompositeType(tag: DW_TAG_structure_type, name: "timespec", file: !601, line: 120, size: 128, align: 64, elements: !602)
!601 = !DIFile(filename: "/usr/include/time.h", directory: "/data/download/cmake/cmake-master/Utilities/cmlibuv")
!602 = !{!603, !606}
!603 = !DIDerivedType(tag: DW_TAG_member, name: "tv_sec", scope: !600, file: !601, line: 122, baseType: !604, size: 64, align: 64)
!604 = !DIDerivedType(tag: DW_TAG_typedef, name: "__time_t", file: !605, line: 139, baseType: !74)
!605 = !DIFile(filename: "/usr/include/x86_64-linux-gnu/bits/types.h", directory: "/data/download/cmake/cmake-master/Utilities/cmlibuv")
!606 = !DIDerivedType(tag: DW_TAG_member, name: "tv_nsec", scope: !600, file: !601, line: 123, baseType: !607, size: 64, align: 64, offset: 64)
!607 = !DIDerivedType(tag: DW_TAG_typedef, name: "__syscall_slong_t", file: !605, line: 175, baseType: !74)
!608 = !DILocation(line: 504, column: 19, scope: !182)
!609 = !DILocation(line: 511, column: 14, scope: !182)
!610 = !DILocation(line: 511, column: 11, scope: !182)
!611 = !DILocation(line: 512, column: 15, scope: !182)
!612 = !DILocation(line: 512, column: 23, scope: !182)
!613 = !DILocation(line: 512, column: 6, scope: !182)
!614 = !DILocation(line: 512, column: 13, scope: !182)
!615 = !DILocation(line: 513, column: 16, scope: !182)
!616 = !DILocation(line: 513, column: 24, scope: !182)
!617 = !DILocation(line: 513, column: 6, scope: !182)
!618 = !DILocation(line: 513, column: 14, scope: !182)
!619 = !DILocation(line: 521, column: 30, scope: !182)
!620 = !DILocation(line: 521, column: 36, scope: !182)
!621 = !DILocation(line: 521, column: 7, scope: !182)
!622 = !DILocation(line: 521, column: 5, scope: !182)
!623 = !DILocation(line: 526, column: 7, scope: !624)
!624 = distinct !DILexicalBlock(scope: !182, file: !1, line: 526, column: 7)
!625 = !DILocation(line: 526, column: 9, scope: !624)
!626 = !DILocation(line: 526, column: 7, scope: !182)
!627 = !DILocation(line: 527, column: 5, scope: !624)
!628 = !DILocation(line: 529, column: 7, scope: !629)
!629 = distinct !DILexicalBlock(scope: !182, file: !1, line: 529, column: 7)
!630 = !DILocation(line: 529, column: 9, scope: !629)
!631 = !DILocation(line: 529, column: 7, scope: !182)
!632 = !DILocation(line: 530, column: 5, scope: !629)
!633 = !DILocation(line: 532, column: 3, scope: !182)
!634 = !DILocation(line: 534, column: 1, scope: !182)
!635 = !DILocalVariable(name: "barrier", arg: 1, scope: !185, file: !1, line: 537, type: !188)
!636 = !DILocation(line: 537, column: 35, scope: !185)
!637 = !DILocalVariable(name: "count", arg: 2, scope: !185, file: !1, line: 537, type: !54)
!638 = !DILocation(line: 537, column: 57, scope: !185)
!639 = !DILocation(line: 538, column: 32, scope: !185)
!640 = !DILocation(line: 538, column: 47, scope: !185)
!641 = !DILocation(line: 538, column: 11, scope: !185)
!642 = !DILocation(line: 538, column: 10, scope: !185)
!643 = !DILocation(line: 538, column: 3, scope: !185)
!644 = !DILocalVariable(name: "barrier", arg: 1, scope: !195, file: !1, line: 542, type: !188)
!645 = !DILocation(line: 542, column: 39, scope: !195)
!646 = !DILocation(line: 543, column: 31, scope: !647)
!647 = distinct !DILexicalBlock(scope: !195, file: !1, line: 543, column: 7)
!648 = !DILocation(line: 543, column: 7, scope: !647)
!649 = !DILocation(line: 543, column: 7, scope: !195)
!650 = !DILocation(line: 544, column: 5, scope: !647)
!651 = !DILocation(line: 545, column: 1, scope: !195)
!652 = !DILocalVariable(name: "barrier", arg: 1, scope: !198, file: !1, line: 548, type: !188)
!653 = !DILocation(line: 548, column: 35, scope: !198)
!654 = !DILocalVariable(name: "r", scope: !198, file: !1, line: 549, type: !20)
!655 = !DILocation(line: 549, column: 7, scope: !198)
!656 = !DILocation(line: 549, column: 32, scope: !198)
!657 = !DILocation(line: 549, column: 11, scope: !198)
!658 = !DILocation(line: 550, column: 7, scope: !659)
!659 = distinct !DILexicalBlock(scope: !198, file: !1, line: 550, column: 7)
!660 = !DILocation(line: 550, column: 9, scope: !659)
!661 = !DILocation(line: 550, column: 12, scope: !662)
!662 = !DILexicalBlockFile(scope: !659, file: !1, discriminator: 1)
!663 = !DILocation(line: 550, column: 14, scope: !662)
!664 = !DILocation(line: 550, column: 7, scope: !662)
!665 = !DILocation(line: 551, column: 5, scope: !659)
!666 = !DILocation(line: 552, column: 10, scope: !198)
!667 = !DILocation(line: 552, column: 12, scope: !198)
!668 = !DILocation(line: 552, column: 3, scope: !198)
!669 = !DILocalVariable(name: "key", arg: 1, scope: !201, file: !1, line: 556, type: !204)
!670 = !DILocation(line: 556, column: 29, scope: !201)
!671 = !DILocation(line: 557, column: 30, scope: !201)
!672 = !DILocation(line: 557, column: 11, scope: !201)
!673 = !DILocation(line: 557, column: 10, scope: !201)
!674 = !DILocation(line: 557, column: 3, scope: !201)
!675 = !DILocalVariable(name: "key", arg: 1, scope: !207, file: !1, line: 561, type: !204)
!676 = !DILocation(line: 561, column: 30, scope: !207)
!677 = !DILocation(line: 562, column: 27, scope: !678)
!678 = distinct !DILexicalBlock(scope: !207, file: !1, line: 562, column: 7)
!679 = !DILocation(line: 562, column: 26, scope: !678)
!680 = !DILocation(line: 562, column: 7, scope: !678)
!681 = !DILocation(line: 562, column: 7, scope: !207)
!682 = !DILocation(line: 563, column: 5, scope: !678)
!683 = !DILocation(line: 564, column: 1, scope: !207)
!684 = !DILocalVariable(name: "key", arg: 1, scope: !210, file: !1, line: 567, type: !204)
!685 = !DILocation(line: 567, column: 28, scope: !210)
!686 = !DILocation(line: 568, column: 31, scope: !210)
!687 = !DILocation(line: 568, column: 30, scope: !210)
!688 = !DILocation(line: 568, column: 10, scope: !210)
!689 = !DILocation(line: 568, column: 3, scope: !210)
!690 = !DILocalVariable(name: "key", arg: 1, scope: !213, file: !1, line: 572, type: !204)
!691 = !DILocation(line: 572, column: 27, scope: !213)
!692 = !DILocalVariable(name: "value", arg: 2, scope: !213, file: !1, line: 572, type: !12)
!693 = !DILocation(line: 572, column: 38, scope: !213)
!694 = !DILocation(line: 573, column: 28, scope: !695)
!695 = distinct !DILexicalBlock(scope: !213, file: !1, line: 573, column: 7)
!696 = !DILocation(line: 573, column: 27, scope: !695)
!697 = !DILocation(line: 573, column: 33, scope: !695)
!698 = !DILocation(line: 573, column: 7, scope: !695)
!699 = !DILocation(line: 573, column: 7, scope: !213)
!700 = !DILocation(line: 574, column: 5, scope: !695)
!701 = !DILocation(line: 575, column: 1, scope: !213)
