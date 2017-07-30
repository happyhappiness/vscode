; ModuleID = '/data/download/cmake/cmake-master/Utilities/cmlibrhash/librhash/rhash.c'
target datalayout = "e-m:e-i64:64-f80:128-n8:16:32:64-S128"
target triple = "x86_64-unknown-linux-gnu"

%struct.rhash_hash_info = type { %struct.rhash_info*, i64, i64, void (i8*)*, void (i8*, i8*, i64)*, void (i8*, i8*)*, void (i8*)* }
%struct.rhash_info = type { i32, i32, i64, i8*, i8* }
%struct.rhash_context = type { i64, i32 }
%struct.rhash_context_ext = type { %struct.rhash_context, i32, i32, i32, i8*, i8*, i8*, [1 x %struct.rhash_vector_item] }
%struct.rhash_vector_item = type { %struct.rhash_hash_info*, i8* }
%struct._IO_FILE = type { i32, i8*, i8*, i8*, i8*, i8*, i8*, i8*, i8*, i8*, i8*, i8*, %struct._IO_marker*, %struct._IO_FILE*, i32, i32, i64, i16, i8, [1 x i8], i8*, i64, i8*, i8*, i8*, i8*, i64, i32, [20 x i8] }
%struct._IO_marker = type { %struct._IO_marker*, %struct._IO_FILE*, i32 }

@rhash_info_size = external global i32, align 4
@.str = private unnamed_addr constant [34 x i8] c"tail_bit_index < RHASH_HASH_COUNT\00", align 1
@.str.1 = private unnamed_addr constant [72 x i8] c"/data/download/cmake/cmake-master/Utilities/cmlibrhash/librhash/rhash.c\00", align 1
@__PRETTY_FUNCTION__.rhash_init = private unnamed_addr constant [31 x i8] c"rhash rhash_init(unsigned int)\00", align 1
@rhash_info_table = external global %struct.rhash_hash_info*, align 8
@.str.2 = private unnamed_addr constant [8 x i8] c"id != 0\00", align 1
@.str.3 = private unnamed_addr constant [29 x i8] c"bit_index < RHASH_HASH_COUNT\00", align 1
@.str.4 = private unnamed_addr constant [8 x i8] c"num > 1\00", align 1
@.str.5 = private unnamed_addr constant [42 x i8] c"aligned_size >= sizeof(rhash_context_ext)\00", align 1
@.str.6 = private unnamed_addr constant [39 x i8] c"phash_ctx >= (char*)&rctx->vector[num]\00", align 1
@.str.7 = private unnamed_addr constant [23 x i8] c"info->context_size > 0\00", align 1
@.str.8 = private unnamed_addr constant [34 x i8] c"((phash_ctx - (char*)0) & 7) == 0\00", align 1
@.str.9 = private unnamed_addr constant [25 x i8] c"info->init != ((void*)0)\00", align 1
@.str.10 = private unnamed_addr constant [43 x i8] c"ectx->hash_vector_size <= RHASH_HASH_COUNT\00", align 1
@__PRETTY_FUNCTION__.rhash_free = private unnamed_addr constant [23 x i8] c"void rhash_free(rhash)\00", align 1
@.str.11 = private unnamed_addr constant [27 x i8] c"ectx->hash_vector_size > 0\00", align 1
@__PRETTY_FUNCTION__.rhash_reset = private unnamed_addr constant [24 x i8] c"void rhash_reset(rhash)\00", align 1
@__PRETTY_FUNCTION__.rhash_update = private unnamed_addr constant [46 x i8] c"int rhash_update(rhash, const void *, size_t)\00", align 1
@.str.12 = private unnamed_addr constant [18 x i8] c"info->update != 0\00", align 1
@__PRETTY_FUNCTION__.rhash_final = private unnamed_addr constant [40 x i8] c"int rhash_final(rhash, unsigned char *)\00", align 1
@.str.13 = private unnamed_addr constant [17 x i8] c"info->final != 0\00", align 1
@.str.14 = private unnamed_addr constant [41 x i8] c"info->info->digest_size < sizeof(buffer)\00", align 1
@.str.15 = private unnamed_addr constant [3 x i8] c"rb\00", align 1

; Function Attrs: nounwind uwtable
define void @rhash_library_init() #0 !dbg !98 {
entry:
  call void @rhash_init_algorithms(i32 1023), !dbg !201
  ret void, !dbg !202
}

declare void @rhash_init_algorithms(i32) #1

; Function Attrs: nounwind uwtable
define i32 @rhash_count() #0 !dbg !102 {
entry:
  %0 = load i32, i32* @rhash_info_size, align 4, !dbg !203
  ret i32 %0, !dbg !204
}

; Function Attrs: nounwind uwtable
define %struct.rhash_context* @rhash_init(i32 %hash_id) #0 !dbg !105 {
entry:
  %retval = alloca %struct.rhash_context*, align 8
  %hash_id.addr = alloca i32, align 4
  %tail_bit_index = alloca i32, align 4
  %num = alloca i32, align 4
  %rctx = alloca %struct.rhash_context_ext*, align 8
  %hash_size_sum = alloca i64, align 8
  %i = alloca i32, align 4
  %bit_index = alloca i32, align 4
  %id = alloca i32, align 4
  %info = alloca %struct.rhash_hash_info*, align 8
  %aligned_size = alloca i64, align 8
  %phash_ctx = alloca i8*, align 8
  store i32 %hash_id, i32* %hash_id.addr, align 4
  call void @llvm.dbg.declare(metadata i32* %hash_id.addr, metadata !205, metadata !206), !dbg !207
  call void @llvm.dbg.declare(metadata i32* %tail_bit_index, metadata !208, metadata !206), !dbg !209
  call void @llvm.dbg.declare(metadata i32* %num, metadata !210, metadata !206), !dbg !211
  store i32 0, i32* %num, align 4, !dbg !211
  call void @llvm.dbg.declare(metadata %struct.rhash_context_ext** %rctx, metadata !212, metadata !206), !dbg !213
  store %struct.rhash_context_ext* null, %struct.rhash_context_ext** %rctx, align 8, !dbg !213
  call void @llvm.dbg.declare(metadata i64* %hash_size_sum, metadata !214, metadata !206), !dbg !215
  store i64 0, i64* %hash_size_sum, align 8, !dbg !215
  call void @llvm.dbg.declare(metadata i32* %i, metadata !216, metadata !206), !dbg !217
  call void @llvm.dbg.declare(metadata i32* %bit_index, metadata !218, metadata !206), !dbg !219
  call void @llvm.dbg.declare(metadata i32* %id, metadata !220, metadata !206), !dbg !221
  call void @llvm.dbg.declare(metadata %struct.rhash_hash_info** %info, metadata !222, metadata !206), !dbg !223
  call void @llvm.dbg.declare(metadata i64* %aligned_size, metadata !224, metadata !206), !dbg !225
  call void @llvm.dbg.declare(metadata i8** %phash_ctx, metadata !226, metadata !206), !dbg !227
  %0 = load i32, i32* %hash_id.addr, align 4, !dbg !228
  %and = and i32 %0, 1023, !dbg !228
  store i32 %and, i32* %hash_id.addr, align 4, !dbg !228
  %1 = load i32, i32* %hash_id.addr, align 4, !dbg !229
  %cmp = icmp eq i32 %1, 0, !dbg !231
  br i1 %cmp, label %if.then, label %if.end, !dbg !232

if.then:                                          ; preds = %entry
  %call = call i32* @__errno_location() #2, !dbg !233
  store i32 22, i32* %call, align 4, !dbg !235
  store %struct.rhash_context* null, %struct.rhash_context** %retval, align 8, !dbg !236
  br label %return, !dbg !236

if.end:                                           ; preds = %entry
  %2 = load i32, i32* %hash_id.addr, align 4, !dbg !237
  %3 = call i32 @llvm.cttz.i32(i32 %2, i1 true), !dbg !237
  store i32 %3, i32* %tail_bit_index, align 4, !dbg !238
  %4 = load i32, i32* %tail_bit_index, align 4, !dbg !239
  %cmp1 = icmp ult i32 %4, 10, !dbg !239
  br i1 %cmp1, label %cond.true, label %cond.false, !dbg !239

cond.true:                                        ; preds = %if.end
  br label %cond.end, !dbg !240

cond.false:                                       ; preds = %if.end
  call void @__assert_fail(i8* getelementptr inbounds ([34 x i8], [34 x i8]* @.str, i32 0, i32 0), i8* getelementptr inbounds ([72 x i8], [72 x i8]* @.str.1, i32 0, i32 0), i32 98, i8* getelementptr inbounds ([31 x i8], [31 x i8]* @__PRETTY_FUNCTION__.rhash_init, i32 0, i32 0)) #7, !dbg !242
  unreachable, !dbg !242
                                                  ; No predecessors!
  br label %cond.end, !dbg !244

cond.end:                                         ; preds = %5, %cond.true
  %6 = load i32, i32* %tail_bit_index, align 4, !dbg !246
  %shl = shl i32 1, %6, !dbg !247
  store i32 %shl, i32* %id, align 4, !dbg !248
  %7 = load i32, i32* %hash_id.addr, align 4, !dbg !249
  %8 = load i32, i32* %id, align 4, !dbg !251
  %cmp2 = icmp eq i32 %7, %8, !dbg !252
  br i1 %cmp2, label %if.then3, label %if.else, !dbg !253

if.then3:                                         ; preds = %cond.end
  store i32 1, i32* %num, align 4, !dbg !254
  %9 = load i32, i32* %tail_bit_index, align 4, !dbg !256
  %idxprom = zext i32 %9 to i64, !dbg !257
  %10 = load %struct.rhash_hash_info*, %struct.rhash_hash_info** @rhash_info_table, align 8, !dbg !257
  %arrayidx = getelementptr inbounds %struct.rhash_hash_info, %struct.rhash_hash_info* %10, i64 %idxprom, !dbg !257
  store %struct.rhash_hash_info* %arrayidx, %struct.rhash_hash_info** %info, align 8, !dbg !258
  %11 = load %struct.rhash_hash_info*, %struct.rhash_hash_info** %info, align 8, !dbg !259
  %context_size = getelementptr inbounds %struct.rhash_hash_info, %struct.rhash_hash_info* %11, i32 0, i32 1, !dbg !260
  %12 = load i64, i64* %context_size, align 8, !dbg !260
  store i64 %12, i64* %hash_size_sum, align 8, !dbg !261
  br label %if.end27, !dbg !262

if.else:                                          ; preds = %cond.end
  %13 = load i32, i32* %tail_bit_index, align 4, !dbg !263
  store i32 %13, i32* %bit_index, align 4, !dbg !266
  br label %for.cond, !dbg !267

for.cond:                                         ; preds = %for.inc, %if.else
  %14 = load i32, i32* %id, align 4, !dbg !268
  %15 = load i32, i32* %hash_id.addr, align 4, !dbg !271
  %cmp4 = icmp ule i32 %14, %15, !dbg !272
  br i1 %cmp4, label %for.body, label %for.end, !dbg !273

for.body:                                         ; preds = %for.cond
  %16 = load i32, i32* %id, align 4, !dbg !274
  %cmp5 = icmp ne i32 %16, 0, !dbg !274
  br i1 %cmp5, label %cond.true6, label %cond.false7, !dbg !274

cond.true6:                                       ; preds = %for.body
  br label %cond.end8, !dbg !276

cond.false7:                                      ; preds = %for.body
  call void @__assert_fail(i8* getelementptr inbounds ([8 x i8], [8 x i8]* @.str.2, i32 0, i32 0), i8* getelementptr inbounds ([72 x i8], [72 x i8]* @.str.1, i32 0, i32 0), i32 110, i8* getelementptr inbounds ([31 x i8], [31 x i8]* @__PRETTY_FUNCTION__.rhash_init, i32 0, i32 0)) #7, !dbg !278
  unreachable, !dbg !278
                                                  ; No predecessors!
  br label %cond.end8, !dbg !280

cond.end8:                                        ; preds = %17, %cond.true6
  %18 = load i32, i32* %bit_index, align 4, !dbg !282
  %cmp9 = icmp ult i32 %18, 10, !dbg !282
  br i1 %cmp9, label %cond.true10, label %cond.false11, !dbg !282

cond.true10:                                      ; preds = %cond.end8
  br label %cond.end12, !dbg !283

cond.false11:                                     ; preds = %cond.end8
  call void @__assert_fail(i8* getelementptr inbounds ([29 x i8], [29 x i8]* @.str.3, i32 0, i32 0), i8* getelementptr inbounds ([72 x i8], [72 x i8]* @.str.1, i32 0, i32 0), i32 111, i8* getelementptr inbounds ([31 x i8], [31 x i8]* @__PRETTY_FUNCTION__.rhash_init, i32 0, i32 0)) #7, !dbg !284
  unreachable, !dbg !284
                                                  ; No predecessors!
  br label %cond.end12, !dbg !285

cond.end12:                                       ; preds = %19, %cond.true10
  %20 = load i32, i32* %bit_index, align 4, !dbg !286
  %idxprom13 = zext i32 %20 to i64, !dbg !287
  %21 = load %struct.rhash_hash_info*, %struct.rhash_hash_info** @rhash_info_table, align 8, !dbg !287
  %arrayidx14 = getelementptr inbounds %struct.rhash_hash_info, %struct.rhash_hash_info* %21, i64 %idxprom13, !dbg !287
  store %struct.rhash_hash_info* %arrayidx14, %struct.rhash_hash_info** %info, align 8, !dbg !288
  %22 = load i32, i32* %hash_id.addr, align 4, !dbg !289
  %23 = load i32, i32* %id, align 4, !dbg !291
  %and15 = and i32 %22, %23, !dbg !292
  %tobool = icmp ne i32 %and15, 0, !dbg !292
  br i1 %tobool, label %if.then16, label %if.end20, !dbg !293

if.then16:                                        ; preds = %cond.end12
  %24 = load %struct.rhash_hash_info*, %struct.rhash_hash_info** %info, align 8, !dbg !294
  %context_size17 = getelementptr inbounds %struct.rhash_hash_info, %struct.rhash_hash_info* %24, i32 0, i32 1, !dbg !296
  %25 = load i64, i64* %context_size17, align 8, !dbg !296
  %add = add i64 %25, 7, !dbg !297
  %and18 = and i64 %add, -8, !dbg !298
  store i64 %and18, i64* %aligned_size, align 8, !dbg !299
  %26 = load i64, i64* %aligned_size, align 8, !dbg !300
  %27 = load i64, i64* %hash_size_sum, align 8, !dbg !301
  %add19 = add i64 %27, %26, !dbg !301
  store i64 %add19, i64* %hash_size_sum, align 8, !dbg !301
  %28 = load i32, i32* %num, align 4, !dbg !302
  %inc = add i32 %28, 1, !dbg !302
  store i32 %inc, i32* %num, align 4, !dbg !302
  br label %if.end20, !dbg !303

if.end20:                                         ; preds = %if.then16, %cond.end12
  br label %for.inc, !dbg !304

for.inc:                                          ; preds = %if.end20
  %29 = load i32, i32* %bit_index, align 4, !dbg !305
  %inc21 = add i32 %29, 1, !dbg !305
  store i32 %inc21, i32* %bit_index, align 4, !dbg !305
  %30 = load i32, i32* %id, align 4, !dbg !307
  %shl22 = shl i32 %30, 1, !dbg !308
  store i32 %shl22, i32* %id, align 4, !dbg !309
  br label %for.cond, !dbg !310

for.end:                                          ; preds = %for.cond
  %31 = load i32, i32* %num, align 4, !dbg !311
  %cmp23 = icmp ugt i32 %31, 1, !dbg !311
  br i1 %cmp23, label %cond.true24, label %cond.false25, !dbg !311

cond.true24:                                      ; preds = %for.end
  br label %cond.end26, !dbg !312

cond.false25:                                     ; preds = %for.end
  call void @__assert_fail(i8* getelementptr inbounds ([8 x i8], [8 x i8]* @.str.4, i32 0, i32 0), i8* getelementptr inbounds ([72 x i8], [72 x i8]* @.str.1, i32 0, i32 0), i32 120, i8* getelementptr inbounds ([31 x i8], [31 x i8]* @__PRETTY_FUNCTION__.rhash_init, i32 0, i32 0)) #7, !dbg !314
  unreachable, !dbg !314
                                                  ; No predecessors!
  br label %cond.end26, !dbg !316

cond.end26:                                       ; preds = %32, %cond.true24
  br label %if.end27

if.end27:                                         ; preds = %cond.end26, %if.then3
  %33 = load i32, i32* %num, align 4, !dbg !318
  %conv = zext i32 %33 to i64, !dbg !318
  %34 = mul i64 %conv, 16, !dbg !318
  %35 = add i64 56, %34, !dbg !318
  %add28 = add i64 %35, 7, !dbg !319
  %and29 = and i64 %add28, -8, !dbg !320
  store i64 %and29, i64* %aligned_size, align 8, !dbg !321
  %36 = load i64, i64* %aligned_size, align 8, !dbg !322
  %cmp30 = icmp uge i64 %36, 72, !dbg !322
  br i1 %cmp30, label %cond.true32, label %cond.false33, !dbg !322

cond.true32:                                      ; preds = %if.end27
  br label %cond.end34, !dbg !323

cond.false33:                                     ; preds = %if.end27
  call void @__assert_fail(i8* getelementptr inbounds ([42 x i8], [42 x i8]* @.str.5, i32 0, i32 0), i8* getelementptr inbounds ([72 x i8], [72 x i8]* @.str.1, i32 0, i32 0), i32 125, i8* getelementptr inbounds ([31 x i8], [31 x i8]* @__PRETTY_FUNCTION__.rhash_init, i32 0, i32 0)) #7, !dbg !324
  unreachable, !dbg !324
                                                  ; No predecessors!
  br label %cond.end34, !dbg !325

cond.end34:                                       ; preds = %37, %cond.true32
  %38 = load i64, i64* %aligned_size, align 8, !dbg !326
  %39 = load i64, i64* %hash_size_sum, align 8, !dbg !327
  %add35 = add i64 %38, %39, !dbg !328
  %call36 = call noalias i8* @malloc(i64 %add35) #8, !dbg !329
  %40 = bitcast i8* %call36 to %struct.rhash_context_ext*, !dbg !330
  store %struct.rhash_context_ext* %40, %struct.rhash_context_ext** %rctx, align 8, !dbg !331
  %41 = load %struct.rhash_context_ext*, %struct.rhash_context_ext** %rctx, align 8, !dbg !332
  %cmp37 = icmp eq %struct.rhash_context_ext* %41, null, !dbg !334
  br i1 %cmp37, label %if.then39, label %if.end40, !dbg !335

if.then39:                                        ; preds = %cond.end34
  store %struct.rhash_context* null, %struct.rhash_context** %retval, align 8, !dbg !336
  br label %return, !dbg !336

if.end40:                                         ; preds = %cond.end34
  %42 = load %struct.rhash_context_ext*, %struct.rhash_context_ext** %rctx, align 8, !dbg !338
  %43 = bitcast %struct.rhash_context_ext* %42 to i8*, !dbg !339
  call void @llvm.memset.p0i8.i64(i8* %43, i8 0, i64 72, i32 8, i1 false), !dbg !339
  %44 = load i32, i32* %hash_id.addr, align 4, !dbg !340
  %45 = load %struct.rhash_context_ext*, %struct.rhash_context_ext** %rctx, align 8, !dbg !341
  %rc = getelementptr inbounds %struct.rhash_context_ext, %struct.rhash_context_ext* %45, i32 0, i32 0, !dbg !342
  %hash_id41 = getelementptr inbounds %struct.rhash_context, %struct.rhash_context* %rc, i32 0, i32 1, !dbg !343
  store i32 %44, i32* %hash_id41, align 8, !dbg !344
  %46 = load %struct.rhash_context_ext*, %struct.rhash_context_ext** %rctx, align 8, !dbg !345
  %flags = getelementptr inbounds %struct.rhash_context_ext, %struct.rhash_context_ext* %46, i32 0, i32 2, !dbg !346
  store i32 1, i32* %flags, align 4, !dbg !347
  %47 = load %struct.rhash_context_ext*, %struct.rhash_context_ext** %rctx, align 8, !dbg !348
  %state = getelementptr inbounds %struct.rhash_context_ext, %struct.rhash_context_ext* %47, i32 0, i32 3, !dbg !349
  store i32 -1340228930, i32* %state, align 8, !dbg !350
  %48 = load i32, i32* %num, align 4, !dbg !351
  %49 = load %struct.rhash_context_ext*, %struct.rhash_context_ext** %rctx, align 8, !dbg !352
  %hash_vector_size = getelementptr inbounds %struct.rhash_context_ext, %struct.rhash_context_ext* %49, i32 0, i32 1, !dbg !353
  store i32 %48, i32* %hash_vector_size, align 8, !dbg !354
  %50 = load %struct.rhash_context_ext*, %struct.rhash_context_ext** %rctx, align 8, !dbg !355
  %51 = bitcast %struct.rhash_context_ext* %50 to i8*, !dbg !356
  %52 = load i64, i64* %aligned_size, align 8, !dbg !357
  %add.ptr = getelementptr inbounds i8, i8* %51, i64 %52, !dbg !358
  store i8* %add.ptr, i8** %phash_ctx, align 8, !dbg !359
  %53 = load i8*, i8** %phash_ctx, align 8, !dbg !360
  %54 = load i32, i32* %num, align 4, !dbg !360
  %idxprom42 = zext i32 %54 to i64, !dbg !360
  %55 = load %struct.rhash_context_ext*, %struct.rhash_context_ext** %rctx, align 8, !dbg !360
  %vector = getelementptr inbounds %struct.rhash_context_ext, %struct.rhash_context_ext* %55, i32 0, i32 7, !dbg !360
  %arrayidx43 = getelementptr inbounds [1 x %struct.rhash_vector_item], [1 x %struct.rhash_vector_item]* %vector, i64 0, i64 %idxprom42, !dbg !360
  %56 = bitcast %struct.rhash_vector_item* %arrayidx43 to i8*, !dbg !360
  %cmp44 = icmp uge i8* %53, %56, !dbg !360
  br i1 %cmp44, label %cond.true46, label %cond.false47, !dbg !360

cond.true46:                                      ; preds = %if.end40
  br label %cond.end48, !dbg !361

cond.false47:                                     ; preds = %if.end40
  call void @__assert_fail(i8* getelementptr inbounds ([39 x i8], [39 x i8]* @.str.6, i32 0, i32 0), i8* getelementptr inbounds ([72 x i8], [72 x i8]* @.str.1, i32 0, i32 0), i32 140, i8* getelementptr inbounds ([31 x i8], [31 x i8]* @__PRETTY_FUNCTION__.rhash_init, i32 0, i32 0)) #7, !dbg !362
  unreachable, !dbg !362
                                                  ; No predecessors!
  br label %cond.end48, !dbg !363

cond.end48:                                       ; preds = %57, %cond.true46
  %58 = load i32, i32* %tail_bit_index, align 4, !dbg !364
  store i32 %58, i32* %bit_index, align 4, !dbg !366
  %59 = load i32, i32* %tail_bit_index, align 4, !dbg !367
  %shl49 = shl i32 1, %59, !dbg !368
  store i32 %shl49, i32* %id, align 4, !dbg !369
  store i32 0, i32* %i, align 4, !dbg !370
  br label %for.cond50, !dbg !371

for.cond50:                                       ; preds = %for.inc94, %cond.end48
  %60 = load i32, i32* %id, align 4, !dbg !372
  %61 = load i32, i32* %hash_id.addr, align 4, !dbg !374
  %cmp51 = icmp ule i32 %60, %61, !dbg !375
  br i1 %cmp51, label %for.body53, label %for.end97, !dbg !376

for.body53:                                       ; preds = %for.cond50
  %62 = load i32, i32* %hash_id.addr, align 4, !dbg !378
  %63 = load i32, i32* %id, align 4, !dbg !381
  %and54 = and i32 %62, %63, !dbg !382
  %cmp55 = icmp ne i32 %and54, 0, !dbg !383
  br i1 %cmp55, label %if.then57, label %if.end93, !dbg !384

if.then57:                                        ; preds = %for.body53
  %64 = load i32, i32* %bit_index, align 4, !dbg !385
  %idxprom58 = zext i32 %64 to i64, !dbg !387
  %65 = load %struct.rhash_hash_info*, %struct.rhash_hash_info** @rhash_info_table, align 8, !dbg !387
  %arrayidx59 = getelementptr inbounds %struct.rhash_hash_info, %struct.rhash_hash_info* %65, i64 %idxprom58, !dbg !387
  store %struct.rhash_hash_info* %arrayidx59, %struct.rhash_hash_info** %info, align 8, !dbg !388
  %66 = load %struct.rhash_hash_info*, %struct.rhash_hash_info** %info, align 8, !dbg !389
  %context_size60 = getelementptr inbounds %struct.rhash_hash_info, %struct.rhash_hash_info* %66, i32 0, i32 1, !dbg !389
  %67 = load i64, i64* %context_size60, align 8, !dbg !389
  %cmp61 = icmp ugt i64 %67, 0, !dbg !389
  br i1 %cmp61, label %cond.true63, label %cond.false64, !dbg !389

cond.true63:                                      ; preds = %if.then57
  br label %cond.end65, !dbg !390

cond.false64:                                     ; preds = %if.then57
  call void @__assert_fail(i8* getelementptr inbounds ([23 x i8], [23 x i8]* @.str.7, i32 0, i32 0), i8* getelementptr inbounds ([72 x i8], [72 x i8]* @.str.1, i32 0, i32 0), i32 149, i8* getelementptr inbounds ([31 x i8], [31 x i8]* @__PRETTY_FUNCTION__.rhash_init, i32 0, i32 0)) #7, !dbg !392
  unreachable, !dbg !392
                                                  ; No predecessors!
  br label %cond.end65, !dbg !394

cond.end65:                                       ; preds = %68, %cond.true63
  %69 = load i8*, i8** %phash_ctx, align 8, !dbg !396
  %sub.ptr.lhs.cast = ptrtoint i8* %69 to i64, !dbg !396
  %sub.ptr.sub = sub i64 %sub.ptr.lhs.cast, 0, !dbg !396
  %and66 = and i64 %sub.ptr.sub, 7, !dbg !396
  %cmp67 = icmp eq i64 %and66, 0, !dbg !396
  br i1 %cmp67, label %cond.true69, label %cond.false70, !dbg !396

cond.true69:                                      ; preds = %cond.end65
  br label %cond.end71, !dbg !397

cond.false70:                                     ; preds = %cond.end65
  call void @__assert_fail(i8* getelementptr inbounds ([34 x i8], [34 x i8]* @.str.8, i32 0, i32 0), i8* getelementptr inbounds ([72 x i8], [72 x i8]* @.str.1, i32 0, i32 0), i32 150, i8* getelementptr inbounds ([31 x i8], [31 x i8]* @__PRETTY_FUNCTION__.rhash_init, i32 0, i32 0)) #7, !dbg !398
  unreachable, !dbg !398
                                                  ; No predecessors!
  br label %cond.end71, !dbg !399

cond.end71:                                       ; preds = %70, %cond.true69
  %71 = load %struct.rhash_hash_info*, %struct.rhash_hash_info** %info, align 8, !dbg !400
  %init = getelementptr inbounds %struct.rhash_hash_info, %struct.rhash_hash_info* %71, i32 0, i32 3, !dbg !400
  %72 = load void (i8*)*, void (i8*)** %init, align 8, !dbg !400
  %cmp72 = icmp ne void (i8*)* %72, null, !dbg !400
  br i1 %cmp72, label %cond.true74, label %cond.false75, !dbg !400

cond.true74:                                      ; preds = %cond.end71
  br label %cond.end76, !dbg !401

cond.false75:                                     ; preds = %cond.end71
  call void @__assert_fail(i8* getelementptr inbounds ([25 x i8], [25 x i8]* @.str.9, i32 0, i32 0), i8* getelementptr inbounds ([72 x i8], [72 x i8]* @.str.1, i32 0, i32 0), i32 151, i8* getelementptr inbounds ([31 x i8], [31 x i8]* @__PRETTY_FUNCTION__.rhash_init, i32 0, i32 0)) #7, !dbg !402
  unreachable, !dbg !402
                                                  ; No predecessors!
  br label %cond.end76, !dbg !403

cond.end76:                                       ; preds = %73, %cond.true74
  %74 = load %struct.rhash_hash_info*, %struct.rhash_hash_info** %info, align 8, !dbg !404
  %75 = load i32, i32* %i, align 4, !dbg !405
  %idxprom77 = zext i32 %75 to i64, !dbg !406
  %76 = load %struct.rhash_context_ext*, %struct.rhash_context_ext** %rctx, align 8, !dbg !406
  %vector78 = getelementptr inbounds %struct.rhash_context_ext, %struct.rhash_context_ext* %76, i32 0, i32 7, !dbg !407
  %arrayidx79 = getelementptr inbounds [1 x %struct.rhash_vector_item], [1 x %struct.rhash_vector_item]* %vector78, i64 0, i64 %idxprom77, !dbg !406
  %hash_info = getelementptr inbounds %struct.rhash_vector_item, %struct.rhash_vector_item* %arrayidx79, i32 0, i32 0, !dbg !408
  store %struct.rhash_hash_info* %74, %struct.rhash_hash_info** %hash_info, align 8, !dbg !409
  %77 = load i8*, i8** %phash_ctx, align 8, !dbg !410
  %78 = load i32, i32* %i, align 4, !dbg !411
  %idxprom80 = zext i32 %78 to i64, !dbg !412
  %79 = load %struct.rhash_context_ext*, %struct.rhash_context_ext** %rctx, align 8, !dbg !412
  %vector81 = getelementptr inbounds %struct.rhash_context_ext, %struct.rhash_context_ext* %79, i32 0, i32 7, !dbg !413
  %arrayidx82 = getelementptr inbounds [1 x %struct.rhash_vector_item], [1 x %struct.rhash_vector_item]* %vector81, i64 0, i64 %idxprom80, !dbg !412
  %context = getelementptr inbounds %struct.rhash_vector_item, %struct.rhash_vector_item* %arrayidx82, i32 0, i32 1, !dbg !414
  store i8* %77, i8** %context, align 8, !dbg !415
  %80 = load %struct.rhash_hash_info*, %struct.rhash_hash_info** %info, align 8, !dbg !416
  %context_size83 = getelementptr inbounds %struct.rhash_hash_info, %struct.rhash_hash_info* %80, i32 0, i32 1, !dbg !417
  %81 = load i64, i64* %context_size83, align 8, !dbg !417
  %add84 = add i64 %81, 7, !dbg !418
  %and85 = and i64 %add84, -8, !dbg !419
  %82 = load i8*, i8** %phash_ctx, align 8, !dbg !420
  %add.ptr86 = getelementptr inbounds i8, i8* %82, i64 %and85, !dbg !420
  store i8* %add.ptr86, i8** %phash_ctx, align 8, !dbg !420
  %83 = load %struct.rhash_hash_info*, %struct.rhash_hash_info** %info, align 8, !dbg !421
  %init87 = getelementptr inbounds %struct.rhash_hash_info, %struct.rhash_hash_info* %83, i32 0, i32 3, !dbg !422
  %84 = load void (i8*)*, void (i8*)** %init87, align 8, !dbg !422
  %85 = load i32, i32* %i, align 4, !dbg !423
  %idxprom88 = zext i32 %85 to i64, !dbg !424
  %86 = load %struct.rhash_context_ext*, %struct.rhash_context_ext** %rctx, align 8, !dbg !424
  %vector89 = getelementptr inbounds %struct.rhash_context_ext, %struct.rhash_context_ext* %86, i32 0, i32 7, !dbg !425
  %arrayidx90 = getelementptr inbounds [1 x %struct.rhash_vector_item], [1 x %struct.rhash_vector_item]* %vector89, i64 0, i64 %idxprom88, !dbg !424
  %context91 = getelementptr inbounds %struct.rhash_vector_item, %struct.rhash_vector_item* %arrayidx90, i32 0, i32 1, !dbg !426
  %87 = load i8*, i8** %context91, align 8, !dbg !426
  call void %84(i8* %87), !dbg !421
  %88 = load i32, i32* %i, align 4, !dbg !427
  %inc92 = add i32 %88, 1, !dbg !427
  store i32 %inc92, i32* %i, align 4, !dbg !427
  br label %if.end93, !dbg !428

if.end93:                                         ; preds = %cond.end76, %for.body53
  br label %for.inc94, !dbg !429

for.inc94:                                        ; preds = %if.end93
  %89 = load i32, i32* %bit_index, align 4, !dbg !430
  %inc95 = add i32 %89, 1, !dbg !430
  store i32 %inc95, i32* %bit_index, align 4, !dbg !430
  %90 = load i32, i32* %id, align 4, !dbg !432
  %shl96 = shl i32 %90, 1, !dbg !433
  store i32 %shl96, i32* %id, align 4, !dbg !434
  br label %for.cond50, !dbg !435

for.end97:                                        ; preds = %for.cond50
  %91 = load %struct.rhash_context_ext*, %struct.rhash_context_ext** %rctx, align 8, !dbg !437
  %rc98 = getelementptr inbounds %struct.rhash_context_ext, %struct.rhash_context_ext* %91, i32 0, i32 0, !dbg !438
  store %struct.rhash_context* %rc98, %struct.rhash_context** %retval, align 8, !dbg !439
  br label %return, !dbg !439

return:                                           ; preds = %for.end97, %if.then39, %if.then
  %92 = load %struct.rhash_context*, %struct.rhash_context** %retval, align 8, !dbg !440
  ret %struct.rhash_context* %92, !dbg !440
}

; Function Attrs: nounwind readnone
declare void @llvm.dbg.declare(metadata, metadata, metadata) #2

; Function Attrs: nounwind readnone
declare i32* @__errno_location() #3

; Function Attrs: nounwind readnone
declare i32 @llvm.cttz.i32(i32, i1) #2

; Function Attrs: noreturn nounwind
declare void @__assert_fail(i8*, i8*, i32, i8*) #4

; Function Attrs: nounwind
declare noalias i8* @malloc(i64) #5

; Function Attrs: argmemonly nounwind
declare void @llvm.memset.p0i8.i64(i8* nocapture, i8, i64, i32, i1) #6

; Function Attrs: nounwind uwtable
define void @rhash_free(%struct.rhash_context* %ctx) #0 !dbg !110 {
entry:
  %ctx.addr = alloca %struct.rhash_context*, align 8
  %ectx = alloca %struct.rhash_context_ext*, align 8
  %i = alloca i32, align 4
  %info = alloca %struct.rhash_hash_info*, align 8
  store %struct.rhash_context* %ctx, %struct.rhash_context** %ctx.addr, align 8
  call void @llvm.dbg.declare(metadata %struct.rhash_context** %ctx.addr, metadata !441, metadata !206), !dbg !442
  call void @llvm.dbg.declare(metadata %struct.rhash_context_ext** %ectx, metadata !443, metadata !206), !dbg !445
  %0 = load %struct.rhash_context*, %struct.rhash_context** %ctx.addr, align 8, !dbg !446
  %1 = bitcast %struct.rhash_context* %0 to %struct.rhash_context_ext*, !dbg !447
  store %struct.rhash_context_ext* %1, %struct.rhash_context_ext** %ectx, align 8, !dbg !445
  call void @llvm.dbg.declare(metadata i32* %i, metadata !448, metadata !206), !dbg !449
  %2 = load %struct.rhash_context*, %struct.rhash_context** %ctx.addr, align 8, !dbg !450
  %cmp = icmp eq %struct.rhash_context* %2, null, !dbg !452
  br i1 %cmp, label %if.then, label %if.end, !dbg !453

if.then:                                          ; preds = %entry
  br label %return, !dbg !454

if.end:                                           ; preds = %entry
  %3 = load %struct.rhash_context_ext*, %struct.rhash_context_ext** %ectx, align 8, !dbg !456
  %hash_vector_size = getelementptr inbounds %struct.rhash_context_ext, %struct.rhash_context_ext* %3, i32 0, i32 1, !dbg !456
  %4 = load i32, i32* %hash_vector_size, align 8, !dbg !456
  %cmp1 = icmp ule i32 %4, 10, !dbg !456
  br i1 %cmp1, label %cond.true, label %cond.false, !dbg !456

cond.true:                                        ; preds = %if.end
  br label %cond.end, !dbg !457

cond.false:                                       ; preds = %if.end
  call void @__assert_fail(i8* getelementptr inbounds ([43 x i8], [43 x i8]* @.str.10, i32 0, i32 0), i8* getelementptr inbounds ([72 x i8], [72 x i8]* @.str.1, i32 0, i32 0), i32 182, i8* getelementptr inbounds ([23 x i8], [23 x i8]* @__PRETTY_FUNCTION__.rhash_free, i32 0, i32 0)) #7, !dbg !459
  unreachable, !dbg !459
                                                  ; No predecessors!
  br label %cond.end, !dbg !461

cond.end:                                         ; preds = %5, %cond.true
  %6 = load %struct.rhash_context_ext*, %struct.rhash_context_ext** %ectx, align 8, !dbg !463
  %state = getelementptr inbounds %struct.rhash_context_ext, %struct.rhash_context_ext* %6, i32 0, i32 3, !dbg !464
  store i32 -556882451, i32* %state, align 8, !dbg !465
  store i32 0, i32* %i, align 4, !dbg !466
  br label %for.cond, !dbg !468

for.cond:                                         ; preds = %for.inc, %cond.end
  %7 = load i32, i32* %i, align 4, !dbg !469
  %8 = load %struct.rhash_context_ext*, %struct.rhash_context_ext** %ectx, align 8, !dbg !472
  %hash_vector_size2 = getelementptr inbounds %struct.rhash_context_ext, %struct.rhash_context_ext* %8, i32 0, i32 1, !dbg !473
  %9 = load i32, i32* %hash_vector_size2, align 8, !dbg !473
  %cmp3 = icmp ult i32 %7, %9, !dbg !474
  br i1 %cmp3, label %for.body, label %for.end, !dbg !475

for.body:                                         ; preds = %for.cond
  call void @llvm.dbg.declare(metadata %struct.rhash_hash_info** %info, metadata !476, metadata !206), !dbg !478
  %10 = load i32, i32* %i, align 4, !dbg !479
  %idxprom = zext i32 %10 to i64, !dbg !480
  %11 = load %struct.rhash_context_ext*, %struct.rhash_context_ext** %ectx, align 8, !dbg !480
  %vector = getelementptr inbounds %struct.rhash_context_ext, %struct.rhash_context_ext* %11, i32 0, i32 7, !dbg !481
  %arrayidx = getelementptr inbounds [1 x %struct.rhash_vector_item], [1 x %struct.rhash_vector_item]* %vector, i64 0, i64 %idxprom, !dbg !480
  %hash_info = getelementptr inbounds %struct.rhash_vector_item, %struct.rhash_vector_item* %arrayidx, i32 0, i32 0, !dbg !482
  %12 = load %struct.rhash_hash_info*, %struct.rhash_hash_info** %hash_info, align 8, !dbg !482
  store %struct.rhash_hash_info* %12, %struct.rhash_hash_info** %info, align 8, !dbg !478
  %13 = load %struct.rhash_hash_info*, %struct.rhash_hash_info** %info, align 8, !dbg !483
  %cleanup = getelementptr inbounds %struct.rhash_hash_info, %struct.rhash_hash_info* %13, i32 0, i32 6, !dbg !485
  %14 = load void (i8*)*, void (i8*)** %cleanup, align 8, !dbg !485
  %cmp4 = icmp ne void (i8*)* %14, null, !dbg !486
  br i1 %cmp4, label %if.then5, label %if.end10, !dbg !487

if.then5:                                         ; preds = %for.body
  %15 = load %struct.rhash_hash_info*, %struct.rhash_hash_info** %info, align 8, !dbg !488
  %cleanup6 = getelementptr inbounds %struct.rhash_hash_info, %struct.rhash_hash_info* %15, i32 0, i32 6, !dbg !490
  %16 = load void (i8*)*, void (i8*)** %cleanup6, align 8, !dbg !490
  %17 = load i32, i32* %i, align 4, !dbg !491
  %idxprom7 = zext i32 %17 to i64, !dbg !492
  %18 = load %struct.rhash_context_ext*, %struct.rhash_context_ext** %ectx, align 8, !dbg !492
  %vector8 = getelementptr inbounds %struct.rhash_context_ext, %struct.rhash_context_ext* %18, i32 0, i32 7, !dbg !493
  %arrayidx9 = getelementptr inbounds [1 x %struct.rhash_vector_item], [1 x %struct.rhash_vector_item]* %vector8, i64 0, i64 %idxprom7, !dbg !492
  %context = getelementptr inbounds %struct.rhash_vector_item, %struct.rhash_vector_item* %arrayidx9, i32 0, i32 1, !dbg !494
  %19 = load i8*, i8** %context, align 8, !dbg !494
  call void %16(i8* %19), !dbg !488
  br label %if.end10, !dbg !495

if.end10:                                         ; preds = %if.then5, %for.body
  br label %for.inc, !dbg !496

for.inc:                                          ; preds = %if.end10
  %20 = load i32, i32* %i, align 4, !dbg !497
  %inc = add i32 %20, 1, !dbg !497
  store i32 %inc, i32* %i, align 4, !dbg !497
  br label %for.cond, !dbg !499

for.end:                                          ; preds = %for.cond
  %21 = load %struct.rhash_context_ext*, %struct.rhash_context_ext** %ectx, align 8, !dbg !500
  %22 = bitcast %struct.rhash_context_ext* %21 to i8*, !dbg !500
  call void @free(i8* %22) #8, !dbg !501
  br label %return, !dbg !502

return:                                           ; preds = %for.end, %if.then
  ret void, !dbg !503
}

; Function Attrs: nounwind
declare void @free(i8*) #5

; Function Attrs: nounwind uwtable
define void @rhash_reset(%struct.rhash_context* %ctx) #0 !dbg !113 {
entry:
  %ctx.addr = alloca %struct.rhash_context*, align 8
  %ectx = alloca %struct.rhash_context_ext*, align 8
  %i = alloca i32, align 4
  %info = alloca %struct.rhash_hash_info*, align 8
  store %struct.rhash_context* %ctx, %struct.rhash_context** %ctx.addr, align 8
  call void @llvm.dbg.declare(metadata %struct.rhash_context** %ctx.addr, metadata !504, metadata !206), !dbg !505
  call void @llvm.dbg.declare(metadata %struct.rhash_context_ext** %ectx, metadata !506, metadata !206), !dbg !507
  %0 = load %struct.rhash_context*, %struct.rhash_context** %ctx.addr, align 8, !dbg !508
  %1 = bitcast %struct.rhash_context* %0 to %struct.rhash_context_ext*, !dbg !509
  store %struct.rhash_context_ext* %1, %struct.rhash_context_ext** %ectx, align 8, !dbg !507
  call void @llvm.dbg.declare(metadata i32* %i, metadata !510, metadata !206), !dbg !511
  %2 = load %struct.rhash_context_ext*, %struct.rhash_context_ext** %ectx, align 8, !dbg !512
  %hash_vector_size = getelementptr inbounds %struct.rhash_context_ext, %struct.rhash_context_ext* %2, i32 0, i32 1, !dbg !512
  %3 = load i32, i32* %hash_vector_size, align 8, !dbg !512
  %cmp = icmp ugt i32 %3, 0, !dbg !512
  br i1 %cmp, label %cond.true, label %cond.false, !dbg !512

cond.true:                                        ; preds = %entry
  br label %cond.end, !dbg !513

cond.false:                                       ; preds = %entry
  call void @__assert_fail(i8* getelementptr inbounds ([27 x i8], [27 x i8]* @.str.11, i32 0, i32 0), i8* getelementptr inbounds ([72 x i8], [72 x i8]* @.str.1, i32 0, i32 0), i32 207, i8* getelementptr inbounds ([24 x i8], [24 x i8]* @__PRETTY_FUNCTION__.rhash_reset, i32 0, i32 0)) #7, !dbg !515
  unreachable, !dbg !515
                                                  ; No predecessors!
  br label %cond.end, !dbg !517

cond.end:                                         ; preds = %4, %cond.true
  %5 = load %struct.rhash_context_ext*, %struct.rhash_context_ext** %ectx, align 8, !dbg !519
  %hash_vector_size1 = getelementptr inbounds %struct.rhash_context_ext, %struct.rhash_context_ext* %5, i32 0, i32 1, !dbg !519
  %6 = load i32, i32* %hash_vector_size1, align 8, !dbg !519
  %cmp2 = icmp ule i32 %6, 10, !dbg !519
  br i1 %cmp2, label %cond.true3, label %cond.false4, !dbg !519

cond.true3:                                       ; preds = %cond.end
  br label %cond.end5, !dbg !520

cond.false4:                                      ; preds = %cond.end
  call void @__assert_fail(i8* getelementptr inbounds ([43 x i8], [43 x i8]* @.str.10, i32 0, i32 0), i8* getelementptr inbounds ([72 x i8], [72 x i8]* @.str.1, i32 0, i32 0), i32 208, i8* getelementptr inbounds ([24 x i8], [24 x i8]* @__PRETTY_FUNCTION__.rhash_reset, i32 0, i32 0)) #7, !dbg !521
  unreachable, !dbg !521
                                                  ; No predecessors!
  br label %cond.end5, !dbg !522

cond.end5:                                        ; preds = %7, %cond.true3
  %8 = load %struct.rhash_context_ext*, %struct.rhash_context_ext** %ectx, align 8, !dbg !523
  %state = getelementptr inbounds %struct.rhash_context_ext, %struct.rhash_context_ext* %8, i32 0, i32 3, !dbg !524
  store i32 -1340228930, i32* %state, align 8, !dbg !525
  store i32 0, i32* %i, align 4, !dbg !526
  br label %for.cond, !dbg !528

for.cond:                                         ; preds = %for.inc, %cond.end5
  %9 = load i32, i32* %i, align 4, !dbg !529
  %10 = load %struct.rhash_context_ext*, %struct.rhash_context_ext** %ectx, align 8, !dbg !532
  %hash_vector_size6 = getelementptr inbounds %struct.rhash_context_ext, %struct.rhash_context_ext* %10, i32 0, i32 1, !dbg !533
  %11 = load i32, i32* %hash_vector_size6, align 8, !dbg !533
  %cmp7 = icmp ult i32 %9, %11, !dbg !534
  br i1 %cmp7, label %for.body, label %for.end, !dbg !535

for.body:                                         ; preds = %for.cond
  call void @llvm.dbg.declare(metadata %struct.rhash_hash_info** %info, metadata !536, metadata !206), !dbg !538
  %12 = load i32, i32* %i, align 4, !dbg !539
  %idxprom = zext i32 %12 to i64, !dbg !540
  %13 = load %struct.rhash_context_ext*, %struct.rhash_context_ext** %ectx, align 8, !dbg !540
  %vector = getelementptr inbounds %struct.rhash_context_ext, %struct.rhash_context_ext* %13, i32 0, i32 7, !dbg !541
  %arrayidx = getelementptr inbounds [1 x %struct.rhash_vector_item], [1 x %struct.rhash_vector_item]* %vector, i64 0, i64 %idxprom, !dbg !540
  %hash_info = getelementptr inbounds %struct.rhash_vector_item, %struct.rhash_vector_item* %arrayidx, i32 0, i32 0, !dbg !542
  %14 = load %struct.rhash_hash_info*, %struct.rhash_hash_info** %hash_info, align 8, !dbg !542
  store %struct.rhash_hash_info* %14, %struct.rhash_hash_info** %info, align 8, !dbg !538
  %15 = load %struct.rhash_hash_info*, %struct.rhash_hash_info** %info, align 8, !dbg !543
  %cleanup = getelementptr inbounds %struct.rhash_hash_info, %struct.rhash_hash_info* %15, i32 0, i32 6, !dbg !545
  %16 = load void (i8*)*, void (i8*)** %cleanup, align 8, !dbg !545
  %cmp8 = icmp ne void (i8*)* %16, null, !dbg !546
  br i1 %cmp8, label %if.then, label %if.end, !dbg !547

if.then:                                          ; preds = %for.body
  %17 = load %struct.rhash_hash_info*, %struct.rhash_hash_info** %info, align 8, !dbg !548
  %cleanup9 = getelementptr inbounds %struct.rhash_hash_info, %struct.rhash_hash_info* %17, i32 0, i32 6, !dbg !550
  %18 = load void (i8*)*, void (i8*)** %cleanup9, align 8, !dbg !550
  %19 = load i32, i32* %i, align 4, !dbg !551
  %idxprom10 = zext i32 %19 to i64, !dbg !552
  %20 = load %struct.rhash_context_ext*, %struct.rhash_context_ext** %ectx, align 8, !dbg !552
  %vector11 = getelementptr inbounds %struct.rhash_context_ext, %struct.rhash_context_ext* %20, i32 0, i32 7, !dbg !553
  %arrayidx12 = getelementptr inbounds [1 x %struct.rhash_vector_item], [1 x %struct.rhash_vector_item]* %vector11, i64 0, i64 %idxprom10, !dbg !552
  %context = getelementptr inbounds %struct.rhash_vector_item, %struct.rhash_vector_item* %arrayidx12, i32 0, i32 1, !dbg !554
  %21 = load i8*, i8** %context, align 8, !dbg !554
  call void %18(i8* %21), !dbg !548
  br label %if.end, !dbg !555

if.end:                                           ; preds = %if.then, %for.body
  %22 = load %struct.rhash_hash_info*, %struct.rhash_hash_info** %info, align 8, !dbg !556
  %init = getelementptr inbounds %struct.rhash_hash_info, %struct.rhash_hash_info* %22, i32 0, i32 3, !dbg !556
  %23 = load void (i8*)*, void (i8*)** %init, align 8, !dbg !556
  %cmp13 = icmp ne void (i8*)* %23, null, !dbg !556
  br i1 %cmp13, label %cond.true14, label %cond.false15, !dbg !556

cond.true14:                                      ; preds = %if.end
  br label %cond.end16, !dbg !557

cond.false15:                                     ; preds = %if.end
  call void @__assert_fail(i8* getelementptr inbounds ([25 x i8], [25 x i8]* @.str.9, i32 0, i32 0), i8* getelementptr inbounds ([72 x i8], [72 x i8]* @.str.1, i32 0, i32 0), i32 218, i8* getelementptr inbounds ([24 x i8], [24 x i8]* @__PRETTY_FUNCTION__.rhash_reset, i32 0, i32 0)) #7, !dbg !559
  unreachable, !dbg !559
                                                  ; No predecessors!
  br label %cond.end16, !dbg !561

cond.end16:                                       ; preds = %24, %cond.true14
  %25 = load %struct.rhash_hash_info*, %struct.rhash_hash_info** %info, align 8, !dbg !563
  %init17 = getelementptr inbounds %struct.rhash_hash_info, %struct.rhash_hash_info* %25, i32 0, i32 3, !dbg !564
  %26 = load void (i8*)*, void (i8*)** %init17, align 8, !dbg !564
  %27 = load i32, i32* %i, align 4, !dbg !565
  %idxprom18 = zext i32 %27 to i64, !dbg !566
  %28 = load %struct.rhash_context_ext*, %struct.rhash_context_ext** %ectx, align 8, !dbg !566
  %vector19 = getelementptr inbounds %struct.rhash_context_ext, %struct.rhash_context_ext* %28, i32 0, i32 7, !dbg !567
  %arrayidx20 = getelementptr inbounds [1 x %struct.rhash_vector_item], [1 x %struct.rhash_vector_item]* %vector19, i64 0, i64 %idxprom18, !dbg !566
  %context21 = getelementptr inbounds %struct.rhash_vector_item, %struct.rhash_vector_item* %arrayidx20, i32 0, i32 1, !dbg !568
  %29 = load i8*, i8** %context21, align 8, !dbg !568
  call void %26(i8* %29), !dbg !563
  br label %for.inc, !dbg !569

for.inc:                                          ; preds = %cond.end16
  %30 = load i32, i32* %i, align 4, !dbg !570
  %inc = add i32 %30, 1, !dbg !570
  store i32 %inc, i32* %i, align 4, !dbg !570
  br label %for.cond, !dbg !572

for.end:                                          ; preds = %for.cond
  %31 = load %struct.rhash_context_ext*, %struct.rhash_context_ext** %ectx, align 8, !dbg !573
  %flags = getelementptr inbounds %struct.rhash_context_ext, %struct.rhash_context_ext* %31, i32 0, i32 2, !dbg !574
  %32 = load i32, i32* %flags, align 4, !dbg !575
  %and = and i32 %32, -3, !dbg !575
  store i32 %and, i32* %flags, align 4, !dbg !575
  ret void, !dbg !576
}

; Function Attrs: nounwind uwtable
define i32 @rhash_update(%struct.rhash_context* %ctx, i8* %message, i64 %length) #0 !dbg !114 {
entry:
  %retval = alloca i32, align 4
  %ctx.addr = alloca %struct.rhash_context*, align 8
  %message.addr = alloca i8*, align 8
  %length.addr = alloca i64, align 8
  %ectx = alloca %struct.rhash_context_ext*, align 8
  %i = alloca i32, align 4
  %info = alloca %struct.rhash_hash_info*, align 8
  store %struct.rhash_context* %ctx, %struct.rhash_context** %ctx.addr, align 8
  call void @llvm.dbg.declare(metadata %struct.rhash_context** %ctx.addr, metadata !577, metadata !206), !dbg !578
  store i8* %message, i8** %message.addr, align 8
  call void @llvm.dbg.declare(metadata i8** %message.addr, metadata !579, metadata !206), !dbg !580
  store i64 %length, i64* %length.addr, align 8
  call void @llvm.dbg.declare(metadata i64* %length.addr, metadata !581, metadata !206), !dbg !582
  call void @llvm.dbg.declare(metadata %struct.rhash_context_ext** %ectx, metadata !583, metadata !206), !dbg !584
  %0 = load %struct.rhash_context*, %struct.rhash_context** %ctx.addr, align 8, !dbg !585
  %1 = bitcast %struct.rhash_context* %0 to %struct.rhash_context_ext*, !dbg !586
  store %struct.rhash_context_ext* %1, %struct.rhash_context_ext** %ectx, align 8, !dbg !584
  call void @llvm.dbg.declare(metadata i32* %i, metadata !587, metadata !206), !dbg !588
  %2 = load %struct.rhash_context_ext*, %struct.rhash_context_ext** %ectx, align 8, !dbg !589
  %hash_vector_size = getelementptr inbounds %struct.rhash_context_ext, %struct.rhash_context_ext* %2, i32 0, i32 1, !dbg !589
  %3 = load i32, i32* %hash_vector_size, align 8, !dbg !589
  %cmp = icmp ule i32 %3, 10, !dbg !589
  br i1 %cmp, label %cond.true, label %cond.false, !dbg !589

cond.true:                                        ; preds = %entry
  br label %cond.end, !dbg !590

cond.false:                                       ; preds = %entry
  call void @__assert_fail(i8* getelementptr inbounds ([43 x i8], [43 x i8]* @.str.10, i32 0, i32 0), i8* getelementptr inbounds ([72 x i8], [72 x i8]* @.str.1, i32 0, i32 0), i32 238, i8* getelementptr inbounds ([46 x i8], [46 x i8]* @__PRETTY_FUNCTION__.rhash_update, i32 0, i32 0)) #7, !dbg !592
  unreachable, !dbg !592
                                                  ; No predecessors!
  br label %cond.end, !dbg !594

cond.end:                                         ; preds = %4, %cond.true
  %5 = load %struct.rhash_context_ext*, %struct.rhash_context_ext** %ectx, align 8, !dbg !596
  %state = getelementptr inbounds %struct.rhash_context_ext, %struct.rhash_context_ext* %5, i32 0, i32 3, !dbg !598
  %6 = load i32, i32* %state, align 8, !dbg !598
  %cmp1 = icmp ne i32 %6, -1340228930, !dbg !599
  br i1 %cmp1, label %if.then, label %if.end, !dbg !600

if.then:                                          ; preds = %cond.end
  store i32 0, i32* %retval, align 4, !dbg !601
  br label %return, !dbg !601

if.end:                                           ; preds = %cond.end
  %7 = load i64, i64* %length.addr, align 8, !dbg !603
  %8 = load %struct.rhash_context*, %struct.rhash_context** %ctx.addr, align 8, !dbg !604
  %msg_size = getelementptr inbounds %struct.rhash_context, %struct.rhash_context* %8, i32 0, i32 0, !dbg !605
  %9 = load i64, i64* %msg_size, align 8, !dbg !606
  %add = add i64 %9, %7, !dbg !606
  store i64 %add, i64* %msg_size, align 8, !dbg !606
  store i32 0, i32* %i, align 4, !dbg !607
  br label %for.cond, !dbg !609

for.cond:                                         ; preds = %for.inc, %if.end
  %10 = load i32, i32* %i, align 4, !dbg !610
  %11 = load %struct.rhash_context_ext*, %struct.rhash_context_ext** %ectx, align 8, !dbg !613
  %hash_vector_size2 = getelementptr inbounds %struct.rhash_context_ext, %struct.rhash_context_ext* %11, i32 0, i32 1, !dbg !614
  %12 = load i32, i32* %hash_vector_size2, align 8, !dbg !614
  %cmp3 = icmp ult i32 %10, %12, !dbg !615
  br i1 %cmp3, label %for.body, label %for.end, !dbg !616

for.body:                                         ; preds = %for.cond
  call void @llvm.dbg.declare(metadata %struct.rhash_hash_info** %info, metadata !617, metadata !206), !dbg !619
  %13 = load i32, i32* %i, align 4, !dbg !620
  %idxprom = zext i32 %13 to i64, !dbg !621
  %14 = load %struct.rhash_context_ext*, %struct.rhash_context_ext** %ectx, align 8, !dbg !621
  %vector = getelementptr inbounds %struct.rhash_context_ext, %struct.rhash_context_ext* %14, i32 0, i32 7, !dbg !622
  %arrayidx = getelementptr inbounds [1 x %struct.rhash_vector_item], [1 x %struct.rhash_vector_item]* %vector, i64 0, i64 %idxprom, !dbg !621
  %hash_info = getelementptr inbounds %struct.rhash_vector_item, %struct.rhash_vector_item* %arrayidx, i32 0, i32 0, !dbg !623
  %15 = load %struct.rhash_hash_info*, %struct.rhash_hash_info** %hash_info, align 8, !dbg !623
  store %struct.rhash_hash_info* %15, %struct.rhash_hash_info** %info, align 8, !dbg !619
  %16 = load %struct.rhash_hash_info*, %struct.rhash_hash_info** %info, align 8, !dbg !624
  %update = getelementptr inbounds %struct.rhash_hash_info, %struct.rhash_hash_info* %16, i32 0, i32 4, !dbg !624
  %17 = load void (i8*, i8*, i64)*, void (i8*, i8*, i64)** %update, align 8, !dbg !624
  %cmp4 = icmp ne void (i8*, i8*, i64)* %17, null, !dbg !624
  br i1 %cmp4, label %cond.true5, label %cond.false6, !dbg !624

cond.true5:                                       ; preds = %for.body
  br label %cond.end7, !dbg !625

cond.false6:                                      ; preds = %for.body
  call void @__assert_fail(i8* getelementptr inbounds ([18 x i8], [18 x i8]* @.str.12, i32 0, i32 0), i8* getelementptr inbounds ([72 x i8], [72 x i8]* @.str.1, i32 0, i32 0), i32 246, i8* getelementptr inbounds ([46 x i8], [46 x i8]* @__PRETTY_FUNCTION__.rhash_update, i32 0, i32 0)) #7, !dbg !627
  unreachable, !dbg !627
                                                  ; No predecessors!
  br label %cond.end7, !dbg !629

cond.end7:                                        ; preds = %18, %cond.true5
  %19 = load %struct.rhash_hash_info*, %struct.rhash_hash_info** %info, align 8, !dbg !631
  %update8 = getelementptr inbounds %struct.rhash_hash_info, %struct.rhash_hash_info* %19, i32 0, i32 4, !dbg !632
  %20 = load void (i8*, i8*, i64)*, void (i8*, i8*, i64)** %update8, align 8, !dbg !632
  %21 = load i32, i32* %i, align 4, !dbg !633
  %idxprom9 = zext i32 %21 to i64, !dbg !634
  %22 = load %struct.rhash_context_ext*, %struct.rhash_context_ext** %ectx, align 8, !dbg !634
  %vector10 = getelementptr inbounds %struct.rhash_context_ext, %struct.rhash_context_ext* %22, i32 0, i32 7, !dbg !635
  %arrayidx11 = getelementptr inbounds [1 x %struct.rhash_vector_item], [1 x %struct.rhash_vector_item]* %vector10, i64 0, i64 %idxprom9, !dbg !634
  %context = getelementptr inbounds %struct.rhash_vector_item, %struct.rhash_vector_item* %arrayidx11, i32 0, i32 1, !dbg !636
  %23 = load i8*, i8** %context, align 8, !dbg !636
  %24 = load i8*, i8** %message.addr, align 8, !dbg !637
  %25 = load i64, i64* %length.addr, align 8, !dbg !638
  call void %20(i8* %23, i8* %24, i64 %25), !dbg !631
  br label %for.inc, !dbg !639

for.inc:                                          ; preds = %cond.end7
  %26 = load i32, i32* %i, align 4, !dbg !640
  %inc = add i32 %26, 1, !dbg !640
  store i32 %inc, i32* %i, align 4, !dbg !640
  br label %for.cond, !dbg !642

for.end:                                          ; preds = %for.cond
  store i32 0, i32* %retval, align 4, !dbg !643
  br label %return, !dbg !643

return:                                           ; preds = %for.end, %if.then
  %27 = load i32, i32* %retval, align 4, !dbg !644
  ret i32 %27, !dbg !644
}

; Function Attrs: nounwind uwtable
define i32 @rhash_final(%struct.rhash_context* %ctx, i8* %first_result) #0 !dbg !117 {
entry:
  %retval = alloca i32, align 4
  %ctx.addr = alloca %struct.rhash_context*, align 8
  %first_result.addr = alloca i8*, align 8
  %i = alloca i32, align 4
  %buffer = alloca [130 x i8], align 16
  %out = alloca i8*, align 8
  %ectx = alloca %struct.rhash_context_ext*, align 8
  %info = alloca %struct.rhash_hash_info*, align 8
  store %struct.rhash_context* %ctx, %struct.rhash_context** %ctx.addr, align 8
  call void @llvm.dbg.declare(metadata %struct.rhash_context** %ctx.addr, metadata !645, metadata !206), !dbg !646
  store i8* %first_result, i8** %first_result.addr, align 8
  call void @llvm.dbg.declare(metadata i8** %first_result.addr, metadata !647, metadata !206), !dbg !648
  call void @llvm.dbg.declare(metadata i32* %i, metadata !649, metadata !206), !dbg !650
  store i32 0, i32* %i, align 4, !dbg !650
  call void @llvm.dbg.declare(metadata [130 x i8]* %buffer, metadata !651, metadata !206), !dbg !655
  call void @llvm.dbg.declare(metadata i8** %out, metadata !656, metadata !206), !dbg !657
  %0 = load i8*, i8** %first_result.addr, align 8, !dbg !658
  %tobool = icmp ne i8* %0, null, !dbg !658
  br i1 %tobool, label %cond.true, label %cond.false, !dbg !658

cond.true:                                        ; preds = %entry
  %1 = load i8*, i8** %first_result.addr, align 8, !dbg !659
  br label %cond.end, !dbg !661

cond.false:                                       ; preds = %entry
  %arraydecay = getelementptr inbounds [130 x i8], [130 x i8]* %buffer, i32 0, i32 0, !dbg !662
  br label %cond.end, !dbg !664

cond.end:                                         ; preds = %cond.false, %cond.true
  %cond = phi i8* [ %1, %cond.true ], [ %arraydecay, %cond.false ], !dbg !665
  store i8* %cond, i8** %out, align 8, !dbg !667
  call void @llvm.dbg.declare(metadata %struct.rhash_context_ext** %ectx, metadata !668, metadata !206), !dbg !669
  %2 = load %struct.rhash_context*, %struct.rhash_context** %ctx.addr, align 8, !dbg !670
  %3 = bitcast %struct.rhash_context* %2 to %struct.rhash_context_ext*, !dbg !671
  store %struct.rhash_context_ext* %3, %struct.rhash_context_ext** %ectx, align 8, !dbg !669
  %4 = load %struct.rhash_context_ext*, %struct.rhash_context_ext** %ectx, align 8, !dbg !672
  %hash_vector_size = getelementptr inbounds %struct.rhash_context_ext, %struct.rhash_context_ext* %4, i32 0, i32 1, !dbg !672
  %5 = load i32, i32* %hash_vector_size, align 8, !dbg !672
  %cmp = icmp ule i32 %5, 10, !dbg !672
  br i1 %cmp, label %cond.true1, label %cond.false2, !dbg !672

cond.true1:                                       ; preds = %cond.end
  br label %cond.end3, !dbg !673

cond.false2:                                      ; preds = %cond.end
  call void @__assert_fail(i8* getelementptr inbounds ([43 x i8], [43 x i8]* @.str.10, i32 0, i32 0), i8* getelementptr inbounds ([72 x i8], [72 x i8]* @.str.1, i32 0, i32 0), i32 265, i8* getelementptr inbounds ([40 x i8], [40 x i8]* @__PRETTY_FUNCTION__.rhash_final, i32 0, i32 0)) #7, !dbg !674
  unreachable, !dbg !674
                                                  ; No predecessors!
  br label %cond.end3, !dbg !675

cond.end3:                                        ; preds = %6, %cond.true1
  %7 = load %struct.rhash_context_ext*, %struct.rhash_context_ext** %ectx, align 8, !dbg !676
  %flags = getelementptr inbounds %struct.rhash_context_ext, %struct.rhash_context_ext* %7, i32 0, i32 2, !dbg !678
  %8 = load i32, i32* %flags, align 4, !dbg !678
  %and = and i32 %8, 3, !dbg !679
  %cmp4 = icmp eq i32 %and, 3, !dbg !680
  br i1 %cmp4, label %if.then, label %if.end, !dbg !681

if.then:                                          ; preds = %cond.end3
  store i32 0, i32* %retval, align 4, !dbg !682
  br label %return, !dbg !682

if.end:                                           ; preds = %cond.end3
  store i32 0, i32* %i, align 4, !dbg !683
  br label %for.cond, !dbg !685

for.cond:                                         ; preds = %for.inc, %if.end
  %9 = load i32, i32* %i, align 4, !dbg !686
  %10 = load %struct.rhash_context_ext*, %struct.rhash_context_ext** %ectx, align 8, !dbg !689
  %hash_vector_size5 = getelementptr inbounds %struct.rhash_context_ext, %struct.rhash_context_ext* %10, i32 0, i32 1, !dbg !690
  %11 = load i32, i32* %hash_vector_size5, align 8, !dbg !690
  %cmp6 = icmp ult i32 %9, %11, !dbg !691
  br i1 %cmp6, label %for.body, label %for.end, !dbg !692

for.body:                                         ; preds = %for.cond
  call void @llvm.dbg.declare(metadata %struct.rhash_hash_info** %info, metadata !693, metadata !206), !dbg !695
  %12 = load i32, i32* %i, align 4, !dbg !696
  %idxprom = zext i32 %12 to i64, !dbg !697
  %13 = load %struct.rhash_context_ext*, %struct.rhash_context_ext** %ectx, align 8, !dbg !697
  %vector = getelementptr inbounds %struct.rhash_context_ext, %struct.rhash_context_ext* %13, i32 0, i32 7, !dbg !698
  %arrayidx = getelementptr inbounds [1 x %struct.rhash_vector_item], [1 x %struct.rhash_vector_item]* %vector, i64 0, i64 %idxprom, !dbg !697
  %hash_info = getelementptr inbounds %struct.rhash_vector_item, %struct.rhash_vector_item* %arrayidx, i32 0, i32 0, !dbg !699
  %14 = load %struct.rhash_hash_info*, %struct.rhash_hash_info** %hash_info, align 8, !dbg !699
  store %struct.rhash_hash_info* %14, %struct.rhash_hash_info** %info, align 8, !dbg !695
  %15 = load %struct.rhash_hash_info*, %struct.rhash_hash_info** %info, align 8, !dbg !700
  %final = getelementptr inbounds %struct.rhash_hash_info, %struct.rhash_hash_info* %15, i32 0, i32 5, !dbg !700
  %16 = load void (i8*, i8*)*, void (i8*, i8*)** %final, align 8, !dbg !700
  %cmp7 = icmp ne void (i8*, i8*)* %16, null, !dbg !700
  br i1 %cmp7, label %cond.true8, label %cond.false9, !dbg !700

cond.true8:                                       ; preds = %for.body
  br label %cond.end10, !dbg !701

cond.false9:                                      ; preds = %for.body
  call void @__assert_fail(i8* getelementptr inbounds ([17 x i8], [17 x i8]* @.str.13, i32 0, i32 0), i8* getelementptr inbounds ([72 x i8], [72 x i8]* @.str.1, i32 0, i32 0), i32 274, i8* getelementptr inbounds ([40 x i8], [40 x i8]* @__PRETTY_FUNCTION__.rhash_final, i32 0, i32 0)) #7, !dbg !703
  unreachable, !dbg !703
                                                  ; No predecessors!
  br label %cond.end10, !dbg !705

cond.end10:                                       ; preds = %17, %cond.true8
  %18 = load %struct.rhash_hash_info*, %struct.rhash_hash_info** %info, align 8, !dbg !707
  %info11 = getelementptr inbounds %struct.rhash_hash_info, %struct.rhash_hash_info* %18, i32 0, i32 0, !dbg !707
  %19 = load %struct.rhash_info*, %struct.rhash_info** %info11, align 8, !dbg !707
  %digest_size = getelementptr inbounds %struct.rhash_info, %struct.rhash_info* %19, i32 0, i32 2, !dbg !707
  %20 = load i64, i64* %digest_size, align 8, !dbg !707
  %cmp12 = icmp ult i64 %20, 130, !dbg !707
  br i1 %cmp12, label %cond.true13, label %cond.false14, !dbg !707

cond.true13:                                      ; preds = %cond.end10
  br label %cond.end15, !dbg !708

cond.false14:                                     ; preds = %cond.end10
  call void @__assert_fail(i8* getelementptr inbounds ([41 x i8], [41 x i8]* @.str.14, i32 0, i32 0), i8* getelementptr inbounds ([72 x i8], [72 x i8]* @.str.1, i32 0, i32 0), i32 275, i8* getelementptr inbounds ([40 x i8], [40 x i8]* @__PRETTY_FUNCTION__.rhash_final, i32 0, i32 0)) #7, !dbg !709
  unreachable, !dbg !709
                                                  ; No predecessors!
  br label %cond.end15, !dbg !710

cond.end15:                                       ; preds = %21, %cond.true13
  %22 = load %struct.rhash_hash_info*, %struct.rhash_hash_info** %info, align 8, !dbg !711
  %final16 = getelementptr inbounds %struct.rhash_hash_info, %struct.rhash_hash_info* %22, i32 0, i32 5, !dbg !712
  %23 = load void (i8*, i8*)*, void (i8*, i8*)** %final16, align 8, !dbg !712
  %24 = load i32, i32* %i, align 4, !dbg !713
  %idxprom17 = zext i32 %24 to i64, !dbg !714
  %25 = load %struct.rhash_context_ext*, %struct.rhash_context_ext** %ectx, align 8, !dbg !714
  %vector18 = getelementptr inbounds %struct.rhash_context_ext, %struct.rhash_context_ext* %25, i32 0, i32 7, !dbg !715
  %arrayidx19 = getelementptr inbounds [1 x %struct.rhash_vector_item], [1 x %struct.rhash_vector_item]* %vector18, i64 0, i64 %idxprom17, !dbg !714
  %context = getelementptr inbounds %struct.rhash_vector_item, %struct.rhash_vector_item* %arrayidx19, i32 0, i32 1, !dbg !716
  %26 = load i8*, i8** %context, align 8, !dbg !716
  %27 = load i8*, i8** %out, align 8, !dbg !717
  call void %23(i8* %26, i8* %27), !dbg !711
  %arraydecay20 = getelementptr inbounds [130 x i8], [130 x i8]* %buffer, i32 0, i32 0, !dbg !718
  store i8* %arraydecay20, i8** %out, align 8, !dbg !719
  br label %for.inc, !dbg !720

for.inc:                                          ; preds = %cond.end15
  %28 = load i32, i32* %i, align 4, !dbg !721
  %inc = add i32 %28, 1, !dbg !721
  store i32 %inc, i32* %i, align 4, !dbg !721
  br label %for.cond, !dbg !723

for.end:                                          ; preds = %for.cond
  %29 = load %struct.rhash_context_ext*, %struct.rhash_context_ext** %ectx, align 8, !dbg !724
  %flags21 = getelementptr inbounds %struct.rhash_context_ext, %struct.rhash_context_ext* %29, i32 0, i32 2, !dbg !725
  %30 = load i32, i32* %flags21, align 4, !dbg !726
  %or = or i32 %30, 2, !dbg !726
  store i32 %or, i32* %flags21, align 4, !dbg !726
  store i32 0, i32* %retval, align 4, !dbg !727
  br label %return, !dbg !727

return:                                           ; preds = %for.end, %if.then
  %31 = load i32, i32* %retval, align 4, !dbg !728
  ret i32 %31, !dbg !728
}

; Function Attrs: nounwind uwtable
define void @rhash_set_callback(%struct.rhash_context* %ctx, void (i8*, i64)* %callback, i8* %callback_data) #0 !dbg !120 {
entry:
  %ctx.addr = alloca %struct.rhash_context*, align 8
  %callback.addr = alloca void (i8*, i64)*, align 8
  %callback_data.addr = alloca i8*, align 8
  store %struct.rhash_context* %ctx, %struct.rhash_context** %ctx.addr, align 8
  call void @llvm.dbg.declare(metadata %struct.rhash_context** %ctx.addr, metadata !729, metadata !206), !dbg !730
  store void (i8*, i64)* %callback, void (i8*, i64)** %callback.addr, align 8
  call void @llvm.dbg.declare(metadata void (i8*, i64)** %callback.addr, metadata !731, metadata !206), !dbg !732
  store i8* %callback_data, i8** %callback_data.addr, align 8
  call void @llvm.dbg.declare(metadata i8** %callback_data.addr, metadata !733, metadata !206), !dbg !734
  %0 = load void (i8*, i64)*, void (i8*, i64)** %callback.addr, align 8, !dbg !735
  %1 = bitcast void (i8*, i64)* %0 to i8*, !dbg !735
  %2 = load %struct.rhash_context*, %struct.rhash_context** %ctx.addr, align 8, !dbg !736
  %3 = bitcast %struct.rhash_context* %2 to %struct.rhash_context_ext*, !dbg !737
  %callback1 = getelementptr inbounds %struct.rhash_context_ext, %struct.rhash_context_ext* %3, i32 0, i32 4, !dbg !737
  store i8* %1, i8** %callback1, align 8, !dbg !738
  %4 = load i8*, i8** %callback_data.addr, align 8, !dbg !739
  %5 = load %struct.rhash_context*, %struct.rhash_context** %ctx.addr, align 8, !dbg !740
  %6 = bitcast %struct.rhash_context* %5 to %struct.rhash_context_ext*, !dbg !741
  %callback_data2 = getelementptr inbounds %struct.rhash_context_ext, %struct.rhash_context_ext* %6, i32 0, i32 5, !dbg !741
  store i8* %4, i8** %callback_data2, align 8, !dbg !742
  ret void, !dbg !743
}

; Function Attrs: nounwind uwtable
define i32 @rhash_msg(i32 %hash_id, i8* %message, i64 %length, i8* %result) #0 !dbg !123 {
entry:
  %retval = alloca i32, align 4
  %hash_id.addr = alloca i32, align 4
  %message.addr = alloca i8*, align 8
  %length.addr = alloca i64, align 8
  %result.addr = alloca i8*, align 8
  %ctx = alloca %struct.rhash_context*, align 8
  store i32 %hash_id, i32* %hash_id.addr, align 4
  call void @llvm.dbg.declare(metadata i32* %hash_id.addr, metadata !744, metadata !206), !dbg !745
  store i8* %message, i8** %message.addr, align 8
  call void @llvm.dbg.declare(metadata i8** %message.addr, metadata !746, metadata !206), !dbg !747
  store i64 %length, i64* %length.addr, align 8
  call void @llvm.dbg.declare(metadata i64* %length.addr, metadata !748, metadata !206), !dbg !749
  store i8* %result, i8** %result.addr, align 8
  call void @llvm.dbg.declare(metadata i8** %result.addr, metadata !750, metadata !206), !dbg !751
  call void @llvm.dbg.declare(metadata %struct.rhash_context** %ctx, metadata !752, metadata !206), !dbg !753
  %0 = load i32, i32* %hash_id.addr, align 4, !dbg !754
  %and = and i32 %0, 1023, !dbg !754
  store i32 %and, i32* %hash_id.addr, align 4, !dbg !754
  %1 = load i32, i32* %hash_id.addr, align 4, !dbg !755
  %call = call %struct.rhash_context* @rhash_init(i32 %1), !dbg !756
  store %struct.rhash_context* %call, %struct.rhash_context** %ctx, align 8, !dbg !757
  %2 = load %struct.rhash_context*, %struct.rhash_context** %ctx, align 8, !dbg !758
  %cmp = icmp eq %struct.rhash_context* %2, null, !dbg !760
  br i1 %cmp, label %if.then, label %if.end, !dbg !761

if.then:                                          ; preds = %entry
  store i32 -1, i32* %retval, align 4, !dbg !762
  br label %return, !dbg !762

if.end:                                           ; preds = %entry
  %3 = load %struct.rhash_context*, %struct.rhash_context** %ctx, align 8, !dbg !764
  %4 = load i8*, i8** %message.addr, align 8, !dbg !765
  %5 = load i64, i64* %length.addr, align 8, !dbg !766
  %call1 = call i32 @rhash_update(%struct.rhash_context* %3, i8* %4, i64 %5), !dbg !767
  %6 = load %struct.rhash_context*, %struct.rhash_context** %ctx, align 8, !dbg !768
  %7 = load i8*, i8** %result.addr, align 8, !dbg !769
  %call2 = call i32 @rhash_final(%struct.rhash_context* %6, i8* %7), !dbg !770
  %8 = load %struct.rhash_context*, %struct.rhash_context** %ctx, align 8, !dbg !771
  call void @rhash_free(%struct.rhash_context* %8), !dbg !772
  store i32 0, i32* %retval, align 4, !dbg !773
  br label %return, !dbg !773

return:                                           ; preds = %if.end, %if.then
  %9 = load i32, i32* %retval, align 4, !dbg !774
  ret i32 %9, !dbg !774
}

; Function Attrs: nounwind uwtable
define i32 @rhash_file_update(%struct.rhash_context* %ctx, %struct._IO_FILE* %fd) #0 !dbg !126 {
entry:
  %retval = alloca i32, align 4
  %ctx.addr = alloca %struct.rhash_context*, align 8
  %fd.addr = alloca %struct._IO_FILE*, align 8
  %ectx = alloca %struct.rhash_context_ext*, align 8
  %block_size = alloca i64, align 8
  %buffer = alloca i8*, align 8
  %pmem = alloca i8*, align 8
  %length = alloca i64, align 8
  %align8 = alloca i64, align 8
  %res = alloca i32, align 4
  store %struct.rhash_context* %ctx, %struct.rhash_context** %ctx.addr, align 8
  call void @llvm.dbg.declare(metadata %struct.rhash_context** %ctx.addr, metadata !775, metadata !206), !dbg !776
  store %struct._IO_FILE* %fd, %struct._IO_FILE** %fd.addr, align 8
  call void @llvm.dbg.declare(metadata %struct._IO_FILE** %fd.addr, metadata !777, metadata !206), !dbg !778
  call void @llvm.dbg.declare(metadata %struct.rhash_context_ext** %ectx, metadata !779, metadata !206), !dbg !780
  %0 = load %struct.rhash_context*, %struct.rhash_context** %ctx.addr, align 8, !dbg !781
  %1 = bitcast %struct.rhash_context* %0 to %struct.rhash_context_ext*, !dbg !782
  store %struct.rhash_context_ext* %1, %struct.rhash_context_ext** %ectx, align 8, !dbg !780
  call void @llvm.dbg.declare(metadata i64* %block_size, metadata !783, metadata !206), !dbg !785
  store i64 8192, i64* %block_size, align 8, !dbg !785
  call void @llvm.dbg.declare(metadata i8** %buffer, metadata !786, metadata !206), !dbg !787
  call void @llvm.dbg.declare(metadata i8** %pmem, metadata !788, metadata !206), !dbg !789
  call void @llvm.dbg.declare(metadata i64* %length, metadata !790, metadata !206), !dbg !791
  store i64 0, i64* %length, align 8, !dbg !791
  call void @llvm.dbg.declare(metadata i64* %align8, metadata !792, metadata !206), !dbg !793
  call void @llvm.dbg.declare(metadata i32* %res, metadata !794, metadata !206), !dbg !795
  store i32 0, i32* %res, align 4, !dbg !795
  %2 = load %struct.rhash_context_ext*, %struct.rhash_context_ext** %ectx, align 8, !dbg !796
  %state = getelementptr inbounds %struct.rhash_context_ext, %struct.rhash_context_ext* %2, i32 0, i32 3, !dbg !798
  %3 = load i32, i32* %state, align 8, !dbg !798
  %cmp = icmp ne i32 %3, -1340228930, !dbg !799
  br i1 %cmp, label %if.then, label %if.end, !dbg !800

if.then:                                          ; preds = %entry
  store i32 0, i32* %retval, align 4, !dbg !801
  br label %return, !dbg !801

if.end:                                           ; preds = %entry
  %4 = load %struct.rhash_context*, %struct.rhash_context** %ctx.addr, align 8, !dbg !803
  %cmp1 = icmp eq %struct.rhash_context* %4, null, !dbg !805
  br i1 %cmp1, label %if.then2, label %if.end3, !dbg !806

if.then2:                                         ; preds = %if.end
  %call = call i32* @__errno_location() #2, !dbg !807
  store i32 22, i32* %call, align 4, !dbg !809
  store i32 -1, i32* %retval, align 4, !dbg !810
  br label %return, !dbg !810

if.end3:                                          ; preds = %if.end
  %call4 = call noalias i8* @malloc(i64 8200) #8, !dbg !811
  store i8* %call4, i8** %pmem, align 8, !dbg !812
  %5 = load i8*, i8** %pmem, align 8, !dbg !813
  %tobool = icmp ne i8* %5, null, !dbg !813
  br i1 %tobool, label %if.end6, label %if.then5, !dbg !815

if.then5:                                         ; preds = %if.end3
  store i32 -1, i32* %retval, align 4, !dbg !816
  br label %return, !dbg !816

if.end6:                                          ; preds = %if.end3
  %6 = load i8*, i8** %pmem, align 8, !dbg !818
  %sub.ptr.rhs.cast = ptrtoint i8* %6 to i64, !dbg !819
  %sub.ptr.sub = sub i64 0, %sub.ptr.rhs.cast, !dbg !819
  %and = and i64 %sub.ptr.sub, 7, !dbg !820
  store i64 %and, i64* %align8, align 8, !dbg !821
  %7 = load i8*, i8** %pmem, align 8, !dbg !822
  %8 = load i64, i64* %align8, align 8, !dbg !823
  %add.ptr = getelementptr inbounds i8, i8* %7, i64 %8, !dbg !824
  store i8* %add.ptr, i8** %buffer, align 8, !dbg !825
  br label %while.cond, !dbg !826

while.cond:                                       ; preds = %if.end25, %if.end6
  %9 = load %struct._IO_FILE*, %struct._IO_FILE** %fd.addr, align 8, !dbg !827
  %call7 = call i32 @feof(%struct._IO_FILE* %9) #8, !dbg !829
  %tobool8 = icmp ne i32 %call7, 0, !dbg !830
  %lnot = xor i1 %tobool8, true, !dbg !830
  br i1 %lnot, label %while.body, label %while.end, !dbg !831

while.body:                                       ; preds = %while.cond
  %10 = load %struct.rhash_context_ext*, %struct.rhash_context_ext** %ectx, align 8, !dbg !832
  %state9 = getelementptr inbounds %struct.rhash_context_ext, %struct.rhash_context_ext* %10, i32 0, i32 3, !dbg !835
  %11 = load i32, i32* %state9, align 8, !dbg !835
  %cmp10 = icmp ne i32 %11, -1340228930, !dbg !836
  br i1 %cmp10, label %if.then11, label %if.end12, !dbg !837

if.then11:                                        ; preds = %while.body
  br label %while.end, !dbg !838

if.end12:                                         ; preds = %while.body
  %12 = load i8*, i8** %buffer, align 8, !dbg !840
  %13 = load %struct._IO_FILE*, %struct._IO_FILE** %fd.addr, align 8, !dbg !841
  %call13 = call i64 @fread(i8* %12, i64 1, i64 8192, %struct._IO_FILE* %13), !dbg !842
  store i64 %call13, i64* %length, align 8, !dbg !843
  %14 = load %struct._IO_FILE*, %struct._IO_FILE** %fd.addr, align 8, !dbg !844
  %call14 = call i32 @ferror(%struct._IO_FILE* %14) #8, !dbg !846
  %tobool15 = icmp ne i32 %call14, 0, !dbg !846
  br i1 %tobool15, label %if.then16, label %if.else, !dbg !847

if.then16:                                        ; preds = %if.end12
  store i32 -1, i32* %res, align 4, !dbg !848
  br label %while.end, !dbg !850

if.else:                                          ; preds = %if.end12
  %15 = load i64, i64* %length, align 8, !dbg !851
  %tobool17 = icmp ne i64 %15, 0, !dbg !851
  br i1 %tobool17, label %if.then18, label %if.end24, !dbg !853

if.then18:                                        ; preds = %if.else
  %16 = load %struct.rhash_context*, %struct.rhash_context** %ctx.addr, align 8, !dbg !854
  %17 = load i8*, i8** %buffer, align 8, !dbg !856
  %18 = load i64, i64* %length, align 8, !dbg !857
  %call19 = call i32 @rhash_update(%struct.rhash_context* %16, i8* %17, i64 %18), !dbg !858
  %19 = load %struct.rhash_context_ext*, %struct.rhash_context_ext** %ectx, align 8, !dbg !859
  %callback = getelementptr inbounds %struct.rhash_context_ext, %struct.rhash_context_ext* %19, i32 0, i32 4, !dbg !861
  %20 = load i8*, i8** %callback, align 8, !dbg !861
  %tobool20 = icmp ne i8* %20, null, !dbg !859
  br i1 %tobool20, label %if.then21, label %if.end23, !dbg !862

if.then21:                                        ; preds = %if.then18
  %21 = load %struct.rhash_context_ext*, %struct.rhash_context_ext** %ectx, align 8, !dbg !863
  %callback22 = getelementptr inbounds %struct.rhash_context_ext, %struct.rhash_context_ext* %21, i32 0, i32 4, !dbg !865
  %22 = load i8*, i8** %callback22, align 8, !dbg !865
  %23 = bitcast i8* %22 to void (i8*, i64)*, !dbg !866
  %24 = load %struct.rhash_context_ext*, %struct.rhash_context_ext** %ectx, align 8, !dbg !867
  %callback_data = getelementptr inbounds %struct.rhash_context_ext, %struct.rhash_context_ext* %24, i32 0, i32 5, !dbg !868
  %25 = load i8*, i8** %callback_data, align 8, !dbg !868
  %26 = load %struct.rhash_context_ext*, %struct.rhash_context_ext** %ectx, align 8, !dbg !869
  %rc = getelementptr inbounds %struct.rhash_context_ext, %struct.rhash_context_ext* %26, i32 0, i32 0, !dbg !870
  %msg_size = getelementptr inbounds %struct.rhash_context, %struct.rhash_context* %rc, i32 0, i32 0, !dbg !871
  %27 = load i64, i64* %msg_size, align 8, !dbg !871
  call void %23(i8* %25, i64 %27), !dbg !872
  br label %if.end23, !dbg !873

if.end23:                                         ; preds = %if.then21, %if.then18
  br label %if.end24, !dbg !874

if.end24:                                         ; preds = %if.end23, %if.else
  br label %if.end25

if.end25:                                         ; preds = %if.end24
  br label %while.cond, !dbg !875

while.end:                                        ; preds = %if.then16, %if.then11, %while.cond
  %28 = load i8*, i8** %buffer, align 8, !dbg !877
  call void @free(i8* %28) #8, !dbg !878
  %29 = load i32, i32* %res, align 4, !dbg !879
  store i32 %29, i32* %retval, align 4, !dbg !880
  br label %return, !dbg !880

return:                                           ; preds = %while.end, %if.then5, %if.then2, %if.then
  %30 = load i32, i32* %retval, align 4, !dbg !881
  ret i32 %30, !dbg !881
}

; Function Attrs: nounwind
declare i32 @feof(%struct._IO_FILE*) #5

declare i64 @fread(i8*, i64, i64, %struct._IO_FILE*) #1

; Function Attrs: nounwind
declare i32 @ferror(%struct._IO_FILE*) #5

; Function Attrs: nounwind uwtable
define i32 @rhash_file(i32 %hash_id, i8* %filepath, i8* %result) #0 !dbg !182 {
entry:
  %retval = alloca i32, align 4
  %hash_id.addr = alloca i32, align 4
  %filepath.addr = alloca i8*, align 8
  %result.addr = alloca i8*, align 8
  %fd = alloca %struct._IO_FILE*, align 8
  %ctx = alloca %struct.rhash_context*, align 8
  %res = alloca i32, align 4
  store i32 %hash_id, i32* %hash_id.addr, align 4
  call void @llvm.dbg.declare(metadata i32* %hash_id.addr, metadata !882, metadata !206), !dbg !883
  store i8* %filepath, i8** %filepath.addr, align 8
  call void @llvm.dbg.declare(metadata i8** %filepath.addr, metadata !884, metadata !206), !dbg !885
  store i8* %result, i8** %result.addr, align 8
  call void @llvm.dbg.declare(metadata i8** %result.addr, metadata !886, metadata !206), !dbg !887
  call void @llvm.dbg.declare(metadata %struct._IO_FILE** %fd, metadata !888, metadata !206), !dbg !889
  call void @llvm.dbg.declare(metadata %struct.rhash_context** %ctx, metadata !890, metadata !206), !dbg !891
  call void @llvm.dbg.declare(metadata i32* %res, metadata !892, metadata !206), !dbg !893
  %0 = load i32, i32* %hash_id.addr, align 4, !dbg !894
  %and = and i32 %0, 1023, !dbg !894
  store i32 %and, i32* %hash_id.addr, align 4, !dbg !894
  %1 = load i32, i32* %hash_id.addr, align 4, !dbg !895
  %cmp = icmp eq i32 %1, 0, !dbg !897
  br i1 %cmp, label %if.then, label %if.end, !dbg !898

if.then:                                          ; preds = %entry
  %call = call i32* @__errno_location() #2, !dbg !899
  store i32 22, i32* %call, align 4, !dbg !901
  store i32 -1, i32* %retval, align 4, !dbg !902
  br label %return, !dbg !902

if.end:                                           ; preds = %entry
  %2 = load i8*, i8** %filepath.addr, align 8, !dbg !903
  %call1 = call %struct._IO_FILE* @fopen64(i8* %2, i8* getelementptr inbounds ([3 x i8], [3 x i8]* @.str.15, i32 0, i32 0)), !dbg !905
  store %struct._IO_FILE* %call1, %struct._IO_FILE** %fd, align 8, !dbg !906
  %cmp2 = icmp eq %struct._IO_FILE* %call1, null, !dbg !907
  br i1 %cmp2, label %if.then3, label %if.end4, !dbg !908

if.then3:                                         ; preds = %if.end
  store i32 -1, i32* %retval, align 4, !dbg !909
  br label %return, !dbg !909

if.end4:                                          ; preds = %if.end
  %3 = load i32, i32* %hash_id.addr, align 4, !dbg !911
  %call5 = call %struct.rhash_context* @rhash_init(i32 %3), !dbg !913
  store %struct.rhash_context* %call5, %struct.rhash_context** %ctx, align 8, !dbg !914
  %cmp6 = icmp eq %struct.rhash_context* %call5, null, !dbg !915
  br i1 %cmp6, label %if.then7, label %if.end8, !dbg !916

if.then7:                                         ; preds = %if.end4
  store i32 -1, i32* %retval, align 4, !dbg !917
  br label %return, !dbg !917

if.end8:                                          ; preds = %if.end4
  %4 = load %struct.rhash_context*, %struct.rhash_context** %ctx, align 8, !dbg !919
  %5 = load %struct._IO_FILE*, %struct._IO_FILE** %fd, align 8, !dbg !920
  %call9 = call i32 @rhash_file_update(%struct.rhash_context* %4, %struct._IO_FILE* %5), !dbg !921
  store i32 %call9, i32* %res, align 4, !dbg !922
  %6 = load %struct._IO_FILE*, %struct._IO_FILE** %fd, align 8, !dbg !923
  %call10 = call i32 @fclose(%struct._IO_FILE* %6), !dbg !924
  %7 = load %struct.rhash_context*, %struct.rhash_context** %ctx, align 8, !dbg !925
  %8 = load i8*, i8** %result.addr, align 8, !dbg !926
  %call11 = call i32 @rhash_final(%struct.rhash_context* %7, i8* %8), !dbg !927
  %9 = load %struct.rhash_context*, %struct.rhash_context** %ctx, align 8, !dbg !928
  call void @rhash_free(%struct.rhash_context* %9), !dbg !929
  %10 = load i32, i32* %res, align 4, !dbg !930
  store i32 %10, i32* %retval, align 4, !dbg !931
  br label %return, !dbg !931

return:                                           ; preds = %if.end8, %if.then7, %if.then3, %if.then
  %11 = load i32, i32* %retval, align 4, !dbg !932
  ret i32 %11, !dbg !932
}

declare %struct._IO_FILE* @fopen64(i8*, i8*) #1

declare i32 @fclose(%struct._IO_FILE*) #1

; Function Attrs: nounwind uwtable
define %struct.rhash_info* @rhash_info_by_id(i32 %hash_id) #0 !dbg !185 {
entry:
  %retval = alloca %struct.rhash_info*, align 8
  %hash_id.addr = alloca i32, align 4
  store i32 %hash_id, i32* %hash_id.addr, align 4
  call void @llvm.dbg.declare(metadata i32* %hash_id.addr, metadata !933, metadata !206), !dbg !934
  %0 = load i32, i32* %hash_id.addr, align 4, !dbg !935
  %and = and i32 %0, 1023, !dbg !935
  store i32 %and, i32* %hash_id.addr, align 4, !dbg !935
  %1 = load i32, i32* %hash_id.addr, align 4, !dbg !936
  %2 = load i32, i32* %hash_id.addr, align 4, !dbg !938
  %3 = load i32, i32* %hash_id.addr, align 4, !dbg !939
  %sub = sub nsw i32 0, %3, !dbg !940
  %and1 = and i32 %2, %sub, !dbg !941
  %cmp = icmp ne i32 %1, %and1, !dbg !942
  br i1 %cmp, label %if.then, label %if.end, !dbg !943

if.then:                                          ; preds = %entry
  store %struct.rhash_info* null, %struct.rhash_info** %retval, align 8, !dbg !944
  br label %return, !dbg !944

if.end:                                           ; preds = %entry
  %4 = load i32, i32* %hash_id.addr, align 4, !dbg !946
  %5 = call i32 @llvm.cttz.i32(i32 %4, i1 true), !dbg !946
  %idxprom = sext i32 %5 to i64, !dbg !947
  %6 = load %struct.rhash_hash_info*, %struct.rhash_hash_info** @rhash_info_table, align 8, !dbg !947
  %arrayidx = getelementptr inbounds %struct.rhash_hash_info, %struct.rhash_hash_info* %6, i64 %idxprom, !dbg !947
  %info = getelementptr inbounds %struct.rhash_hash_info, %struct.rhash_hash_info* %arrayidx, i32 0, i32 0, !dbg !948
  %7 = load %struct.rhash_info*, %struct.rhash_info** %info, align 8, !dbg !948
  store %struct.rhash_info* %7, %struct.rhash_info** %retval, align 8, !dbg !949
  br label %return, !dbg !949

return:                                           ; preds = %if.end, %if.then
  %8 = load %struct.rhash_info*, %struct.rhash_info** %retval, align 8, !dbg !950
  ret %struct.rhash_info* %8, !dbg !950
}

; Function Attrs: nounwind uwtable
define i32 @rhash_get_digest_size(i32 %hash_id) #0 !dbg !190 {
entry:
  %retval = alloca i32, align 4
  %hash_id.addr = alloca i32, align 4
  store i32 %hash_id, i32* %hash_id.addr, align 4
  call void @llvm.dbg.declare(metadata i32* %hash_id.addr, metadata !951, metadata !206), !dbg !952
  %0 = load i32, i32* %hash_id.addr, align 4, !dbg !953
  %and = and i32 %0, 1023, !dbg !953
  store i32 %and, i32* %hash_id.addr, align 4, !dbg !953
  %1 = load i32, i32* %hash_id.addr, align 4, !dbg !954
  %cmp = icmp eq i32 %1, 0, !dbg !956
  br i1 %cmp, label %if.then, label %lor.lhs.false, !dbg !957

lor.lhs.false:                                    ; preds = %entry
  %2 = load i32, i32* %hash_id.addr, align 4, !dbg !958
  %3 = load i32, i32* %hash_id.addr, align 4, !dbg !960
  %sub = sub i32 %3, 1, !dbg !961
  %and1 = and i32 %2, %sub, !dbg !962
  %cmp2 = icmp ne i32 %and1, 0, !dbg !963
  br i1 %cmp2, label %if.then, label %if.end, !dbg !964

if.then:                                          ; preds = %lor.lhs.false, %entry
  store i32 -1, i32* %retval, align 4, !dbg !965
  br label %return, !dbg !965

if.end:                                           ; preds = %lor.lhs.false
  %4 = load i32, i32* %hash_id.addr, align 4, !dbg !967
  %5 = call i32 @llvm.cttz.i32(i32 %4, i1 true), !dbg !967
  %idxprom = sext i32 %5 to i64, !dbg !968
  %6 = load %struct.rhash_hash_info*, %struct.rhash_hash_info** @rhash_info_table, align 8, !dbg !968
  %arrayidx = getelementptr inbounds %struct.rhash_hash_info, %struct.rhash_hash_info* %6, i64 %idxprom, !dbg !968
  %info = getelementptr inbounds %struct.rhash_hash_info, %struct.rhash_hash_info* %arrayidx, i32 0, i32 0, !dbg !969
  %7 = load %struct.rhash_info*, %struct.rhash_info** %info, align 8, !dbg !969
  %digest_size = getelementptr inbounds %struct.rhash_info, %struct.rhash_info* %7, i32 0, i32 2, !dbg !970
  %8 = load i64, i64* %digest_size, align 8, !dbg !970
  %conv = trunc i64 %8 to i32, !dbg !971
  store i32 %conv, i32* %retval, align 4, !dbg !972
  br label %return, !dbg !972

return:                                           ; preds = %if.end, %if.then
  %9 = load i32, i32* %retval, align 4, !dbg !973
  ret i32 %9, !dbg !973
}

; Function Attrs: nounwind uwtable
define i32 @rhash_get_hash_length(i32 %hash_id) #0 !dbg !193 {
entry:
  %hash_id.addr = alloca i32, align 4
  %info = alloca %struct.rhash_info*, align 8
  store i32 %hash_id, i32* %hash_id.addr, align 4
  call void @llvm.dbg.declare(metadata i32* %hash_id.addr, metadata !974, metadata !206), !dbg !975
  call void @llvm.dbg.declare(metadata %struct.rhash_info** %info, metadata !976, metadata !206), !dbg !977
  %0 = load i32, i32* %hash_id.addr, align 4, !dbg !978
  %call = call %struct.rhash_info* @rhash_info_by_id(i32 %0), !dbg !979
  store %struct.rhash_info* %call, %struct.rhash_info** %info, align 8, !dbg !977
  %1 = load %struct.rhash_info*, %struct.rhash_info** %info, align 8, !dbg !980
  %tobool = icmp ne %struct.rhash_info* %1, null, !dbg !980
  br i1 %tobool, label %cond.true, label %cond.false5, !dbg !980

cond.true:                                        ; preds = %entry
  %2 = load %struct.rhash_info*, %struct.rhash_info** %info, align 8, !dbg !981
  %flags = getelementptr inbounds %struct.rhash_info, %struct.rhash_info* %2, i32 0, i32 1, !dbg !983
  %3 = load i32, i32* %flags, align 4, !dbg !983
  %and = and i32 %3, 1, !dbg !984
  %tobool1 = icmp ne i32 %and, 0, !dbg !984
  br i1 %tobool1, label %cond.true2, label %cond.false, !dbg !981

cond.true2:                                       ; preds = %cond.true
  %4 = load %struct.rhash_info*, %struct.rhash_info** %info, align 8, !dbg !985
  %digest_size = getelementptr inbounds %struct.rhash_info, %struct.rhash_info* %4, i32 0, i32 2, !dbg !985
  %5 = load i64, i64* %digest_size, align 8, !dbg !985
  %mul = mul i64 %5, 8, !dbg !985
  %add = add i64 %mul, 4, !dbg !985
  %div = udiv i64 %add, 5, !dbg !985
  br label %cond.end, !dbg !986

cond.false:                                       ; preds = %cond.true
  %6 = load %struct.rhash_info*, %struct.rhash_info** %info, align 8, !dbg !988
  %digest_size3 = getelementptr inbounds %struct.rhash_info, %struct.rhash_info* %6, i32 0, i32 2, !dbg !989
  %7 = load i64, i64* %digest_size3, align 8, !dbg !989
  %mul4 = mul i64 %7, 2, !dbg !990
  br label %cond.end, !dbg !991

cond.end:                                         ; preds = %cond.false, %cond.true2
  %cond = phi i64 [ %div, %cond.true2 ], [ %mul4, %cond.false ], !dbg !993
  br label %cond.end6, !dbg !995

cond.false5:                                      ; preds = %entry
  br label %cond.end6, !dbg !996

cond.end6:                                        ; preds = %cond.false5, %cond.end
  %cond7 = phi i64 [ %cond, %cond.end ], [ 0, %cond.false5 ], !dbg !998
  %conv = trunc i64 %cond7 to i32, !dbg !1000
  ret i32 %conv, !dbg !1001
}

; Function Attrs: nounwind uwtable
define i8* @rhash_get_name(i32 %hash_id) #0 !dbg !194 {
entry:
  %hash_id.addr = alloca i32, align 4
  %info = alloca %struct.rhash_info*, align 8
  store i32 %hash_id, i32* %hash_id.addr, align 4
  call void @llvm.dbg.declare(metadata i32* %hash_id.addr, metadata !1002, metadata !206), !dbg !1003
  call void @llvm.dbg.declare(metadata %struct.rhash_info** %info, metadata !1004, metadata !206), !dbg !1005
  %0 = load i32, i32* %hash_id.addr, align 4, !dbg !1006
  %call = call %struct.rhash_info* @rhash_info_by_id(i32 %0), !dbg !1007
  store %struct.rhash_info* %call, %struct.rhash_info** %info, align 8, !dbg !1005
  %1 = load %struct.rhash_info*, %struct.rhash_info** %info, align 8, !dbg !1008
  %tobool = icmp ne %struct.rhash_info* %1, null, !dbg !1008
  br i1 %tobool, label %cond.true, label %cond.false, !dbg !1008

cond.true:                                        ; preds = %entry
  %2 = load %struct.rhash_info*, %struct.rhash_info** %info, align 8, !dbg !1009
  %name = getelementptr inbounds %struct.rhash_info, %struct.rhash_info* %2, i32 0, i32 3, !dbg !1011
  %3 = load i8*, i8** %name, align 8, !dbg !1011
  br label %cond.end, !dbg !1012

cond.false:                                       ; preds = %entry
  br label %cond.end, !dbg !1013

cond.end:                                         ; preds = %cond.false, %cond.true
  %cond = phi i8* [ %3, %cond.true ], [ null, %cond.false ], !dbg !1015
  ret i8* %cond, !dbg !1017
}

; Function Attrs: nounwind uwtable
define i8* @rhash_get_magnet_name(i32 %hash_id) #0 !dbg !197 {
entry:
  %hash_id.addr = alloca i32, align 4
  %info = alloca %struct.rhash_info*, align 8
  store i32 %hash_id, i32* %hash_id.addr, align 4
  call void @llvm.dbg.declare(metadata i32* %hash_id.addr, metadata !1018, metadata !206), !dbg !1019
  call void @llvm.dbg.declare(metadata %struct.rhash_info** %info, metadata !1020, metadata !206), !dbg !1021
  %0 = load i32, i32* %hash_id.addr, align 4, !dbg !1022
  %call = call %struct.rhash_info* @rhash_info_by_id(i32 %0), !dbg !1023
  store %struct.rhash_info* %call, %struct.rhash_info** %info, align 8, !dbg !1021
  %1 = load %struct.rhash_info*, %struct.rhash_info** %info, align 8, !dbg !1024
  %tobool = icmp ne %struct.rhash_info* %1, null, !dbg !1024
  br i1 %tobool, label %cond.true, label %cond.false, !dbg !1024

cond.true:                                        ; preds = %entry
  %2 = load %struct.rhash_info*, %struct.rhash_info** %info, align 8, !dbg !1025
  %magnet_name = getelementptr inbounds %struct.rhash_info, %struct.rhash_info* %2, i32 0, i32 4, !dbg !1027
  %3 = load i8*, i8** %magnet_name, align 8, !dbg !1027
  br label %cond.end, !dbg !1028

cond.false:                                       ; preds = %entry
  br label %cond.end, !dbg !1029

cond.end:                                         ; preds = %cond.false, %cond.true
  %cond = phi i8* [ %3, %cond.true ], [ null, %cond.false ], !dbg !1031
  ret i8* %cond, !dbg !1033
}

attributes #0 = { nounwind uwtable "disable-tail-calls"="false" "less-precise-fpmad"="false" "no-frame-pointer-elim"="true" "no-frame-pointer-elim-non-leaf" "no-infs-fp-math"="false" "no-nans-fp-math"="false" "stack-protector-buffer-size"="8" "target-cpu"="x86-64" "target-features"="+fxsr,+mmx,+sse,+sse2" "unsafe-fp-math"="false" "use-soft-float"="false" }
attributes #1 = { "disable-tail-calls"="false" "less-precise-fpmad"="false" "no-frame-pointer-elim"="true" "no-frame-pointer-elim-non-leaf" "no-infs-fp-math"="false" "no-nans-fp-math"="false" "stack-protector-buffer-size"="8" "target-cpu"="x86-64" "target-features"="+fxsr,+mmx,+sse,+sse2" "unsafe-fp-math"="false" "use-soft-float"="false" }
attributes #2 = { nounwind readnone }
attributes #3 = { nounwind readnone "disable-tail-calls"="false" "less-precise-fpmad"="false" "no-frame-pointer-elim"="true" "no-frame-pointer-elim-non-leaf" "no-infs-fp-math"="false" "no-nans-fp-math"="false" "stack-protector-buffer-size"="8" "target-cpu"="x86-64" "target-features"="+fxsr,+mmx,+sse,+sse2" "unsafe-fp-math"="false" "use-soft-float"="false" }
attributes #4 = { noreturn nounwind "disable-tail-calls"="false" "less-precise-fpmad"="false" "no-frame-pointer-elim"="true" "no-frame-pointer-elim-non-leaf" "no-infs-fp-math"="false" "no-nans-fp-math"="false" "stack-protector-buffer-size"="8" "target-cpu"="x86-64" "target-features"="+fxsr,+mmx,+sse,+sse2" "unsafe-fp-math"="false" "use-soft-float"="false" }
attributes #5 = { nounwind "disable-tail-calls"="false" "less-precise-fpmad"="false" "no-frame-pointer-elim"="true" "no-frame-pointer-elim-non-leaf" "no-infs-fp-math"="false" "no-nans-fp-math"="false" "stack-protector-buffer-size"="8" "target-cpu"="x86-64" "target-features"="+fxsr,+mmx,+sse,+sse2" "unsafe-fp-math"="false" "use-soft-float"="false" }
attributes #6 = { argmemonly nounwind }
attributes #7 = { noreturn nounwind }
attributes #8 = { nounwind }

!llvm.dbg.cu = !{!0}
!llvm.module.flags = !{!198, !199}
!llvm.ident = !{!200}

!0 = distinct !DICompileUnit(language: DW_LANG_C99, file: !1, producer: "clang version 3.8.0 (tags/RELEASE_380/final)", isOptimized: false, runtimeVersion: 0, emissionKind: 1, enums: !2, retainedTypes: !18, subprograms: !97)
!1 = !DIFile(filename: "/data/download/cmake/cmake-master/Utilities/cmlibrhash/librhash/rhash.c", directory: "/data/download/cmake/cmake-master/Utilities/cmlibrhash")
!2 = !{!3}
!3 = !DICompositeType(tag: DW_TAG_enumeration_type, name: "rhash_ids", file: !4, line: 21, size: 32, align: 32, elements: !5)
!4 = !DIFile(filename: "/data/download/cmake/cmake-master/Utilities/cmlibrhash/librhash/rhash.h", directory: "/data/download/cmake/cmake-master/Utilities/cmlibrhash")
!5 = !{!6, !7, !8, !9, !10, !11, !12, !13, !14, !15, !16, !17}
!6 = !DIEnumerator(name: "RHASH_MD5", value: 1)
!7 = !DIEnumerator(name: "RHASH_SHA1", value: 2)
!8 = !DIEnumerator(name: "RHASH_SHA224", value: 4)
!9 = !DIEnumerator(name: "RHASH_SHA256", value: 8)
!10 = !DIEnumerator(name: "RHASH_SHA384", value: 16)
!11 = !DIEnumerator(name: "RHASH_SHA512", value: 32)
!12 = !DIEnumerator(name: "RHASH_SHA3_224", value: 64)
!13 = !DIEnumerator(name: "RHASH_SHA3_256", value: 128)
!14 = !DIEnumerator(name: "RHASH_SHA3_384", value: 256)
!15 = !DIEnumerator(name: "RHASH_SHA3_512", value: 512)
!16 = !DIEnumerator(name: "RHASH_ALL_HASHES", value: 1023)
!17 = !DIEnumerator(name: "RHASH_HASH_COUNT", value: 10)
!18 = !{!19, !35, !91, !84, !92, !96}
!19 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !20, size: 64, align: 64)
!20 = !DIDerivedType(tag: DW_TAG_typedef, name: "rhash_context_ext", file: !21, line: 58, baseType: !22)
!21 = !DIFile(filename: "/data/download/cmake/cmake-master/Utilities/cmlibrhash/librhash/algorithms.h", directory: "/data/download/cmake/cmake-master/Utilities/cmlibrhash")
!22 = !DICompositeType(tag: DW_TAG_structure_type, name: "rhash_context_ext", file: !21, line: 49, size: 576, align: 64, elements: !23)
!23 = !{!24, !31, !32, !33, !34, !36, !37, !38}
!24 = !DIDerivedType(tag: DW_TAG_member, name: "rc", scope: !22, file: !21, line: 51, baseType: !25, size: 128, align: 64)
!25 = !DICompositeType(tag: DW_TAG_structure_type, name: "rhash_context", file: !4, line: 91, size: 128, align: 64, elements: !26)
!26 = !{!27, !29}
!27 = !DIDerivedType(tag: DW_TAG_member, name: "msg_size", scope: !25, file: !4, line: 94, baseType: !28, size: 64, align: 64)
!28 = !DIBasicType(name: "long long unsigned int", size: 64, align: 64, encoding: DW_ATE_unsigned)
!29 = !DIDerivedType(tag: DW_TAG_member, name: "hash_id", scope: !25, file: !4, line: 99, baseType: !30, size: 32, align: 32, offset: 64)
!30 = !DIBasicType(name: "unsigned int", size: 32, align: 32, encoding: DW_ATE_unsigned)
!31 = !DIDerivedType(tag: DW_TAG_member, name: "hash_vector_size", scope: !22, file: !21, line: 52, baseType: !30, size: 32, align: 32, offset: 128)
!32 = !DIDerivedType(tag: DW_TAG_member, name: "flags", scope: !22, file: !21, line: 53, baseType: !30, size: 32, align: 32, offset: 160)
!33 = !DIDerivedType(tag: DW_TAG_member, name: "state", scope: !22, file: !21, line: 54, baseType: !30, size: 32, align: 32, offset: 192)
!34 = !DIDerivedType(tag: DW_TAG_member, name: "callback", scope: !22, file: !21, line: 55, baseType: !35, size: 64, align: 64, offset: 256)
!35 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: null, size: 64, align: 64)
!36 = !DIDerivedType(tag: DW_TAG_member, name: "callback_data", scope: !22, file: !21, line: 55, baseType: !35, size: 64, align: 64, offset: 320)
!37 = !DIDerivedType(tag: DW_TAG_member, name: "bt_ctx", scope: !22, file: !21, line: 56, baseType: !35, size: 64, align: 64, offset: 384)
!38 = !DIDerivedType(tag: DW_TAG_member, name: "vector", scope: !22, file: !21, line: 57, baseType: !39, size: 128, align: 64, offset: 448)
!39 = !DICompositeType(tag: DW_TAG_array_type, baseType: !40, size: 128, align: 64, elements: !89)
!40 = !DIDerivedType(tag: DW_TAG_typedef, name: "rhash_vector_item", file: !21, line: 44, baseType: !41)
!41 = !DICompositeType(tag: DW_TAG_structure_type, name: "rhash_vector_item", file: !21, line: 40, size: 128, align: 64, elements: !42)
!42 = !{!43, !88}
!43 = !DIDerivedType(tag: DW_TAG_member, name: "hash_info", scope: !41, file: !21, line: 42, baseType: !44, size: 64, align: 64)
!44 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !45, size: 64, align: 64)
!45 = !DICompositeType(tag: DW_TAG_structure_type, name: "rhash_hash_info", file: !21, line: 26, size: 448, align: 64, elements: !46)
!46 = !{!47, !63, !64, !67, !72, !79, !86}
!47 = !DIDerivedType(tag: DW_TAG_member, name: "info", scope: !45, file: !21, line: 28, baseType: !48, size: 64, align: 64)
!48 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !49, size: 64, align: 64)
!49 = !DIDerivedType(tag: DW_TAG_typedef, name: "rhash_info", file: !4, line: 151, baseType: !50)
!50 = !DICompositeType(tag: DW_TAG_structure_type, name: "rhash_info", file: !4, line: 141, size: 256, align: 64, elements: !51)
!51 = !{!52, !53, !54, !58, !62}
!52 = !DIDerivedType(tag: DW_TAG_member, name: "hash_id", scope: !50, file: !4, line: 144, baseType: !30, size: 32, align: 32)
!53 = !DIDerivedType(tag: DW_TAG_member, name: "flags", scope: !50, file: !4, line: 146, baseType: !30, size: 32, align: 32, offset: 32)
!54 = !DIDerivedType(tag: DW_TAG_member, name: "digest_size", scope: !50, file: !4, line: 148, baseType: !55, size: 64, align: 64, offset: 64)
!55 = !DIDerivedType(tag: DW_TAG_typedef, name: "size_t", file: !56, line: 62, baseType: !57)
!56 = !DIFile(filename: "/opt/llvm-build/bin/../lib/clang/3.8.0/include/stddef.h", directory: "/data/download/cmake/cmake-master/Utilities/cmlibrhash")
!57 = !DIBasicType(name: "long unsigned int", size: 64, align: 64, encoding: DW_ATE_unsigned)
!58 = !DIDerivedType(tag: DW_TAG_member, name: "name", scope: !50, file: !4, line: 149, baseType: !59, size: 64, align: 64, offset: 128)
!59 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !60, size: 64, align: 64)
!60 = !DIDerivedType(tag: DW_TAG_const_type, baseType: !61)
!61 = !DIBasicType(name: "char", size: 8, align: 8, encoding: DW_ATE_signed_char)
!62 = !DIDerivedType(tag: DW_TAG_member, name: "magnet_name", scope: !50, file: !4, line: 150, baseType: !59, size: 64, align: 64, offset: 192)
!63 = !DIDerivedType(tag: DW_TAG_member, name: "context_size", scope: !45, file: !21, line: 29, baseType: !55, size: 64, align: 64, offset: 64)
!64 = !DIDerivedType(tag: DW_TAG_member, name: "digest_diff", scope: !45, file: !21, line: 30, baseType: !65, size: 64, align: 64, offset: 128)
!65 = !DIDerivedType(tag: DW_TAG_typedef, name: "ptrdiff_t", file: !56, line: 51, baseType: !66)
!66 = !DIBasicType(name: "long int", size: 64, align: 64, encoding: DW_ATE_signed)
!67 = !DIDerivedType(tag: DW_TAG_member, name: "init", scope: !45, file: !21, line: 31, baseType: !68, size: 64, align: 64, offset: 192)
!68 = !DIDerivedType(tag: DW_TAG_typedef, name: "pinit_t", file: !21, line: 18, baseType: !69)
!69 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !70, size: 64, align: 64)
!70 = !DISubroutineType(types: !71)
!71 = !{null, !35}
!72 = !DIDerivedType(tag: DW_TAG_member, name: "update", scope: !45, file: !21, line: 32, baseType: !73, size: 64, align: 64, offset: 256)
!73 = !DIDerivedType(tag: DW_TAG_typedef, name: "pupdate_t", file: !21, line: 19, baseType: !74)
!74 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !75, size: 64, align: 64)
!75 = !DISubroutineType(types: !76)
!76 = !{null, !35, !77, !55}
!77 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !78, size: 64, align: 64)
!78 = !DIDerivedType(tag: DW_TAG_const_type, baseType: null)
!79 = !DIDerivedType(tag: DW_TAG_member, name: "final", scope: !45, file: !21, line: 33, baseType: !80, size: 64, align: 64, offset: 320)
!80 = !DIDerivedType(tag: DW_TAG_typedef, name: "pfinal_t", file: !21, line: 20, baseType: !81)
!81 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !82, size: 64, align: 64)
!82 = !DISubroutineType(types: !83)
!83 = !{null, !35, !84}
!84 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !85, size: 64, align: 64)
!85 = !DIBasicType(name: "unsigned char", size: 8, align: 8, encoding: DW_ATE_unsigned_char)
!86 = !DIDerivedType(tag: DW_TAG_member, name: "cleanup", scope: !45, file: !21, line: 34, baseType: !87, size: 64, align: 64, offset: 384)
!87 = !DIDerivedType(tag: DW_TAG_typedef, name: "pcleanup_t", file: !21, line: 21, baseType: !69)
!88 = !DIDerivedType(tag: DW_TAG_member, name: "context", scope: !41, file: !21, line: 43, baseType: !35, size: 64, align: 64, offset: 64)
!89 = !{!90}
!90 = !DISubrange(count: 1)
!91 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !61, size: 64, align: 64)
!92 = !DIDerivedType(tag: DW_TAG_typedef, name: "rhash_callback_t", file: !4, line: 111, baseType: !93)
!93 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !94, size: 64, align: 64)
!94 = !DISubroutineType(types: !95)
!95 = !{null, !35, !28}
!96 = !DIBasicType(name: "int", size: 32, align: 32, encoding: DW_ATE_signed)
!97 = !{!98, !102, !105, !110, !113, !114, !117, !120, !123, !126, !182, !185, !190, !193, !194, !197}
!98 = distinct !DISubprogram(name: "rhash_library_init", scope: !1, file: !1, line: 51, type: !99, isLocal: false, isDefinition: true, scopeLine: 52, flags: DIFlagPrototyped, isOptimized: false, variables: !101)
!99 = !DISubroutineType(types: !100)
!100 = !{null}
!101 = !{}
!102 = distinct !DISubprogram(name: "rhash_count", scope: !1, file: !1, line: 64, type: !103, isLocal: false, isDefinition: true, scopeLine: 65, flags: DIFlagPrototyped, isOptimized: false, variables: !101)
!103 = !DISubroutineType(types: !104)
!104 = !{!96}
!105 = distinct !DISubprogram(name: "rhash_init", scope: !1, file: !1, line: 79, type: !106, isLocal: false, isDefinition: true, scopeLine: 80, flags: DIFlagPrototyped, isOptimized: false, variables: !101)
!106 = !DISubroutineType(types: !107)
!107 = !{!108, !30}
!108 = !DIDerivedType(tag: DW_TAG_typedef, name: "rhash", file: !4, line: 107, baseType: !109)
!109 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !25, size: 64, align: 64)
!110 = distinct !DISubprogram(name: "rhash_free", scope: !1, file: !1, line: 176, type: !111, isLocal: false, isDefinition: true, scopeLine: 177, flags: DIFlagPrototyped, isOptimized: false, variables: !101)
!111 = !DISubroutineType(types: !112)
!112 = !{null, !108}
!113 = distinct !DISubprogram(name: "rhash_reset", scope: !1, file: !1, line: 202, type: !111, isLocal: false, isDefinition: true, scopeLine: 203, flags: DIFlagPrototyped, isOptimized: false, variables: !101)
!114 = distinct !DISubprogram(name: "rhash_update", scope: !1, file: !1, line: 233, type: !115, isLocal: false, isDefinition: true, scopeLine: 234, flags: DIFlagPrototyped, isOptimized: false, variables: !101)
!115 = !DISubroutineType(types: !116)
!116 = !{!96, !108, !77, !55}
!117 = distinct !DISubprogram(name: "rhash_final", scope: !1, file: !1, line: 259, type: !118, isLocal: false, isDefinition: true, scopeLine: 260, flags: DIFlagPrototyped, isOptimized: false, variables: !101)
!118 = !DISubroutineType(types: !119)
!119 = !{!96, !108, !84}
!120 = distinct !DISubprogram(name: "rhash_set_callback", scope: !1, file: !1, line: 343, type: !121, isLocal: false, isDefinition: true, scopeLine: 344, flags: DIFlagPrototyped, isOptimized: false, variables: !101)
!121 = !DISubroutineType(types: !122)
!122 = !{null, !108, !92, !35}
!123 = distinct !DISubprogram(name: "rhash_msg", scope: !1, file: !1, line: 361, type: !124, isLocal: false, isDefinition: true, scopeLine: 362, flags: DIFlagPrototyped, isOptimized: false, variables: !101)
!124 = !DISubroutineType(types: !125)
!125 = !{!96, !30, !77, !55, !84}
!126 = distinct !DISubprogram(name: "rhash_file_update", scope: !1, file: !1, line: 384, type: !127, isLocal: false, isDefinition: true, scopeLine: 385, flags: DIFlagPrototyped, isOptimized: false, variables: !101)
!127 = !DISubroutineType(types: !128)
!128 = !{!96, !108, !129}
!129 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !130, size: 64, align: 64)
!130 = !DIDerivedType(tag: DW_TAG_typedef, name: "FILE", file: !131, line: 48, baseType: !132)
!131 = !DIFile(filename: "/usr/include/stdio.h", directory: "/data/download/cmake/cmake-master/Utilities/cmlibrhash")
!132 = !DICompositeType(tag: DW_TAG_structure_type, name: "_IO_FILE", file: !133, line: 245, size: 1728, align: 64, elements: !134)
!133 = !DIFile(filename: "/usr/include/libio.h", directory: "/data/download/cmake/cmake-master/Utilities/cmlibrhash")
!134 = !{!135, !136, !137, !138, !139, !140, !141, !142, !143, !144, !145, !146, !147, !155, !156, !157, !158, !161, !163, !165, !167, !170, !172, !173, !174, !175, !176, !177, !178}
!135 = !DIDerivedType(tag: DW_TAG_member, name: "_flags", scope: !132, file: !133, line: 246, baseType: !96, size: 32, align: 32)
!136 = !DIDerivedType(tag: DW_TAG_member, name: "_IO_read_ptr", scope: !132, file: !133, line: 251, baseType: !91, size: 64, align: 64, offset: 64)
!137 = !DIDerivedType(tag: DW_TAG_member, name: "_IO_read_end", scope: !132, file: !133, line: 252, baseType: !91, size: 64, align: 64, offset: 128)
!138 = !DIDerivedType(tag: DW_TAG_member, name: "_IO_read_base", scope: !132, file: !133, line: 253, baseType: !91, size: 64, align: 64, offset: 192)
!139 = !DIDerivedType(tag: DW_TAG_member, name: "_IO_write_base", scope: !132, file: !133, line: 254, baseType: !91, size: 64, align: 64, offset: 256)
!140 = !DIDerivedType(tag: DW_TAG_member, name: "_IO_write_ptr", scope: !132, file: !133, line: 255, baseType: !91, size: 64, align: 64, offset: 320)
!141 = !DIDerivedType(tag: DW_TAG_member, name: "_IO_write_end", scope: !132, file: !133, line: 256, baseType: !91, size: 64, align: 64, offset: 384)
!142 = !DIDerivedType(tag: DW_TAG_member, name: "_IO_buf_base", scope: !132, file: !133, line: 257, baseType: !91, size: 64, align: 64, offset: 448)
!143 = !DIDerivedType(tag: DW_TAG_member, name: "_IO_buf_end", scope: !132, file: !133, line: 258, baseType: !91, size: 64, align: 64, offset: 512)
!144 = !DIDerivedType(tag: DW_TAG_member, name: "_IO_save_base", scope: !132, file: !133, line: 260, baseType: !91, size: 64, align: 64, offset: 576)
!145 = !DIDerivedType(tag: DW_TAG_member, name: "_IO_backup_base", scope: !132, file: !133, line: 261, baseType: !91, size: 64, align: 64, offset: 640)
!146 = !DIDerivedType(tag: DW_TAG_member, name: "_IO_save_end", scope: !132, file: !133, line: 262, baseType: !91, size: 64, align: 64, offset: 704)
!147 = !DIDerivedType(tag: DW_TAG_member, name: "_markers", scope: !132, file: !133, line: 264, baseType: !148, size: 64, align: 64, offset: 768)
!148 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !149, size: 64, align: 64)
!149 = !DICompositeType(tag: DW_TAG_structure_type, name: "_IO_marker", file: !133, line: 160, size: 192, align: 64, elements: !150)
!150 = !{!151, !152, !154}
!151 = !DIDerivedType(tag: DW_TAG_member, name: "_next", scope: !149, file: !133, line: 161, baseType: !148, size: 64, align: 64)
!152 = !DIDerivedType(tag: DW_TAG_member, name: "_sbuf", scope: !149, file: !133, line: 162, baseType: !153, size: 64, align: 64, offset: 64)
!153 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !132, size: 64, align: 64)
!154 = !DIDerivedType(tag: DW_TAG_member, name: "_pos", scope: !149, file: !133, line: 166, baseType: !96, size: 32, align: 32, offset: 128)
!155 = !DIDerivedType(tag: DW_TAG_member, name: "_chain", scope: !132, file: !133, line: 266, baseType: !153, size: 64, align: 64, offset: 832)
!156 = !DIDerivedType(tag: DW_TAG_member, name: "_fileno", scope: !132, file: !133, line: 268, baseType: !96, size: 32, align: 32, offset: 896)
!157 = !DIDerivedType(tag: DW_TAG_member, name: "_flags2", scope: !132, file: !133, line: 272, baseType: !96, size: 32, align: 32, offset: 928)
!158 = !DIDerivedType(tag: DW_TAG_member, name: "_old_offset", scope: !132, file: !133, line: 274, baseType: !159, size: 64, align: 64, offset: 960)
!159 = !DIDerivedType(tag: DW_TAG_typedef, name: "__off_t", file: !160, line: 131, baseType: !66)
!160 = !DIFile(filename: "/usr/include/x86_64-linux-gnu/bits/types.h", directory: "/data/download/cmake/cmake-master/Utilities/cmlibrhash")
!161 = !DIDerivedType(tag: DW_TAG_member, name: "_cur_column", scope: !132, file: !133, line: 278, baseType: !162, size: 16, align: 16, offset: 1024)
!162 = !DIBasicType(name: "unsigned short", size: 16, align: 16, encoding: DW_ATE_unsigned)
!163 = !DIDerivedType(tag: DW_TAG_member, name: "_vtable_offset", scope: !132, file: !133, line: 279, baseType: !164, size: 8, align: 8, offset: 1040)
!164 = !DIBasicType(name: "signed char", size: 8, align: 8, encoding: DW_ATE_signed_char)
!165 = !DIDerivedType(tag: DW_TAG_member, name: "_shortbuf", scope: !132, file: !133, line: 280, baseType: !166, size: 8, align: 8, offset: 1048)
!166 = !DICompositeType(tag: DW_TAG_array_type, baseType: !61, size: 8, align: 8, elements: !89)
!167 = !DIDerivedType(tag: DW_TAG_member, name: "_lock", scope: !132, file: !133, line: 284, baseType: !168, size: 64, align: 64, offset: 1088)
!168 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !169, size: 64, align: 64)
!169 = !DIDerivedType(tag: DW_TAG_typedef, name: "_IO_lock_t", file: !133, line: 154, baseType: null)
!170 = !DIDerivedType(tag: DW_TAG_member, name: "_offset", scope: !132, file: !133, line: 293, baseType: !171, size: 64, align: 64, offset: 1152)
!171 = !DIDerivedType(tag: DW_TAG_typedef, name: "__off64_t", file: !160, line: 132, baseType: !66)
!172 = !DIDerivedType(tag: DW_TAG_member, name: "__pad1", scope: !132, file: !133, line: 302, baseType: !35, size: 64, align: 64, offset: 1216)
!173 = !DIDerivedType(tag: DW_TAG_member, name: "__pad2", scope: !132, file: !133, line: 303, baseType: !35, size: 64, align: 64, offset: 1280)
!174 = !DIDerivedType(tag: DW_TAG_member, name: "__pad3", scope: !132, file: !133, line: 304, baseType: !35, size: 64, align: 64, offset: 1344)
!175 = !DIDerivedType(tag: DW_TAG_member, name: "__pad4", scope: !132, file: !133, line: 305, baseType: !35, size: 64, align: 64, offset: 1408)
!176 = !DIDerivedType(tag: DW_TAG_member, name: "__pad5", scope: !132, file: !133, line: 306, baseType: !55, size: 64, align: 64, offset: 1472)
!177 = !DIDerivedType(tag: DW_TAG_member, name: "_mode", scope: !132, file: !133, line: 308, baseType: !96, size: 32, align: 32, offset: 1536)
!178 = !DIDerivedType(tag: DW_TAG_member, name: "_unused2", scope: !132, file: !133, line: 310, baseType: !179, size: 160, align: 8, offset: 1568)
!179 = !DICompositeType(tag: DW_TAG_array_type, baseType: !61, size: 160, align: 8, elements: !180)
!180 = !{!181}
!181 = !DISubrange(count: 20)
!182 = distinct !DISubprogram(name: "rhash_file", scope: !1, file: !1, line: 434, type: !183, isLocal: false, isDefinition: true, scopeLine: 435, flags: DIFlagPrototyped, isOptimized: false, variables: !101)
!183 = !DISubroutineType(types: !184)
!184 = !{!96, !30, !59, !84}
!185 = distinct !DISubprogram(name: "rhash_info_by_id", scope: !1, file: !1, line: 502, type: !186, isLocal: false, isDefinition: true, scopeLine: 503, flags: DIFlagPrototyped, isOptimized: false, variables: !101)
!186 = !DISubroutineType(types: !187)
!187 = !{!188, !30}
!188 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !189, size: 64, align: 64)
!189 = !DIDerivedType(tag: DW_TAG_const_type, baseType: !49)
!190 = distinct !DISubprogram(name: "rhash_get_digest_size", scope: !1, file: !1, line: 531, type: !191, isLocal: false, isDefinition: true, scopeLine: 532, flags: DIFlagPrototyped, isOptimized: false, variables: !101)
!191 = !DISubroutineType(types: !192)
!192 = !{!96, !30}
!193 = distinct !DISubprogram(name: "rhash_get_hash_length", scope: !1, file: !1, line: 544, type: !191, isLocal: false, isDefinition: true, scopeLine: 545, flags: DIFlagPrototyped, isOptimized: false, variables: !101)
!194 = distinct !DISubprogram(name: "rhash_get_name", scope: !1, file: !1, line: 557, type: !195, isLocal: false, isDefinition: true, scopeLine: 558, flags: DIFlagPrototyped, isOptimized: false, variables: !101)
!195 = !DISubroutineType(types: !196)
!196 = !{!59, !30}
!197 = distinct !DISubprogram(name: "rhash_get_magnet_name", scope: !1, file: !1, line: 571, type: !195, isLocal: false, isDefinition: true, scopeLine: 572, flags: DIFlagPrototyped, isOptimized: false, variables: !101)
!198 = !{i32 2, !"Dwarf Version", i32 4}
!199 = !{i32 2, !"Debug Info Version", i32 3}
!200 = !{!"clang version 3.8.0 (tags/RELEASE_380/final)"}
!201 = !DILocation(line: 53, column: 2, scope: !98)
!202 = !DILocation(line: 57, column: 1, scope: !98)
!203 = !DILocation(line: 66, column: 9, scope: !102)
!204 = !DILocation(line: 66, column: 2, scope: !102)
!205 = !DILocalVariable(name: "hash_id", arg: 1, scope: !105, file: !1, line: 79, type: !30)
!206 = !DIExpression()
!207 = !DILocation(line: 79, column: 37, scope: !105)
!208 = !DILocalVariable(name: "tail_bit_index", scope: !105, file: !1, line: 81, type: !30)
!209 = !DILocation(line: 81, column: 11, scope: !105)
!210 = !DILocalVariable(name: "num", scope: !105, file: !1, line: 82, type: !30)
!211 = !DILocation(line: 82, column: 11, scope: !105)
!212 = !DILocalVariable(name: "rctx", scope: !105, file: !1, line: 83, type: !19)
!213 = !DILocation(line: 83, column: 21, scope: !105)
!214 = !DILocalVariable(name: "hash_size_sum", scope: !105, file: !1, line: 84, type: !55)
!215 = !DILocation(line: 84, column: 9, scope: !105)
!216 = !DILocalVariable(name: "i", scope: !105, file: !1, line: 86, type: !30)
!217 = !DILocation(line: 86, column: 11, scope: !105)
!218 = !DILocalVariable(name: "bit_index", scope: !105, file: !1, line: 86, type: !30)
!219 = !DILocation(line: 86, column: 14, scope: !105)
!220 = !DILocalVariable(name: "id", scope: !105, file: !1, line: 86, type: !30)
!221 = !DILocation(line: 86, column: 25, scope: !105)
!222 = !DILocalVariable(name: "info", scope: !105, file: !1, line: 87, type: !44)
!223 = !DILocation(line: 87, column: 26, scope: !105)
!224 = !DILocalVariable(name: "aligned_size", scope: !105, file: !1, line: 88, type: !55)
!225 = !DILocation(line: 88, column: 9, scope: !105)
!226 = !DILocalVariable(name: "phash_ctx", scope: !105, file: !1, line: 89, type: !91)
!227 = !DILocation(line: 89, column: 8, scope: !105)
!228 = !DILocation(line: 91, column: 10, scope: !105)
!229 = !DILocation(line: 92, column: 6, scope: !230)
!230 = distinct !DILexicalBlock(scope: !105, file: !1, line: 92, column: 6)
!231 = !DILocation(line: 92, column: 14, scope: !230)
!232 = !DILocation(line: 92, column: 6, scope: !105)
!233 = !DILocation(line: 93, column: 3, scope: !234)
!234 = distinct !DILexicalBlock(scope: !230, file: !1, line: 92, column: 20)
!235 = !DILocation(line: 93, column: 9, scope: !234)
!236 = !DILocation(line: 94, column: 3, scope: !234)
!237 = !DILocation(line: 97, column: 19, scope: !105)
!238 = !DILocation(line: 97, column: 17, scope: !105)
!239 = !DILocation(line: 98, column: 2, scope: !105)
!240 = !DILocation(line: 98, column: 2, scope: !241)
!241 = !DILexicalBlockFile(scope: !105, file: !1, discriminator: 1)
!242 = !DILocation(line: 98, column: 2, scope: !243)
!243 = !DILexicalBlockFile(scope: !105, file: !1, discriminator: 2)
!244 = !DILocation(line: 98, column: 2, scope: !245)
!245 = !DILexicalBlockFile(scope: !105, file: !1, discriminator: 3)
!246 = !DILocation(line: 100, column: 12, scope: !105)
!247 = !DILocation(line: 100, column: 9, scope: !105)
!248 = !DILocation(line: 100, column: 5, scope: !105)
!249 = !DILocation(line: 102, column: 6, scope: !250)
!250 = distinct !DILexicalBlock(scope: !105, file: !1, line: 102, column: 6)
!251 = !DILocation(line: 102, column: 17, scope: !250)
!252 = !DILocation(line: 102, column: 14, scope: !250)
!253 = !DILocation(line: 102, column: 6, scope: !105)
!254 = !DILocation(line: 104, column: 7, scope: !255)
!255 = distinct !DILexicalBlock(scope: !250, file: !1, line: 102, column: 21)
!256 = !DILocation(line: 105, column: 28, scope: !255)
!257 = !DILocation(line: 105, column: 11, scope: !255)
!258 = !DILocation(line: 105, column: 8, scope: !255)
!259 = !DILocation(line: 106, column: 19, scope: !255)
!260 = !DILocation(line: 106, column: 25, scope: !255)
!261 = !DILocation(line: 106, column: 17, scope: !255)
!262 = !DILocation(line: 107, column: 2, scope: !255)
!263 = !DILocation(line: 109, column: 20, scope: !264)
!264 = distinct !DILexicalBlock(scope: !265, file: !1, line: 109, column: 3)
!265 = distinct !DILexicalBlock(scope: !250, file: !1, line: 107, column: 9)
!266 = !DILocation(line: 109, column: 18, scope: !264)
!267 = !DILocation(line: 109, column: 8, scope: !264)
!268 = !DILocation(line: 109, column: 36, scope: !269)
!269 = !DILexicalBlockFile(scope: !270, file: !1, discriminator: 1)
!270 = distinct !DILexicalBlock(scope: !264, file: !1, line: 109, column: 3)
!271 = !DILocation(line: 109, column: 42, scope: !269)
!272 = !DILocation(line: 109, column: 39, scope: !269)
!273 = !DILocation(line: 109, column: 3, scope: !269)
!274 = !DILocation(line: 110, column: 4, scope: !275)
!275 = distinct !DILexicalBlock(scope: !270, file: !1, line: 109, column: 78)
!276 = !DILocation(line: 110, column: 4, scope: !277)
!277 = !DILexicalBlockFile(scope: !275, file: !1, discriminator: 1)
!278 = !DILocation(line: 110, column: 4, scope: !279)
!279 = !DILexicalBlockFile(scope: !275, file: !1, discriminator: 2)
!280 = !DILocation(line: 110, column: 4, scope: !281)
!281 = !DILexicalBlockFile(scope: !275, file: !1, discriminator: 3)
!282 = !DILocation(line: 111, column: 4, scope: !275)
!283 = !DILocation(line: 111, column: 4, scope: !277)
!284 = !DILocation(line: 111, column: 4, scope: !279)
!285 = !DILocation(line: 111, column: 4, scope: !281)
!286 = !DILocation(line: 112, column: 29, scope: !275)
!287 = !DILocation(line: 112, column: 12, scope: !275)
!288 = !DILocation(line: 112, column: 9, scope: !275)
!289 = !DILocation(line: 113, column: 8, scope: !290)
!290 = distinct !DILexicalBlock(scope: !275, file: !1, line: 113, column: 8)
!291 = !DILocation(line: 113, column: 18, scope: !290)
!292 = !DILocation(line: 113, column: 16, scope: !290)
!293 = !DILocation(line: 113, column: 8, scope: !275)
!294 = !DILocation(line: 115, column: 21, scope: !295)
!295 = distinct !DILexicalBlock(scope: !290, file: !1, line: 113, column: 22)
!296 = !DILocation(line: 115, column: 27, scope: !295)
!297 = !DILocation(line: 115, column: 40, scope: !295)
!298 = !DILocation(line: 115, column: 45, scope: !295)
!299 = !DILocation(line: 115, column: 18, scope: !295)
!300 = !DILocation(line: 116, column: 22, scope: !295)
!301 = !DILocation(line: 116, column: 19, scope: !295)
!302 = !DILocation(line: 117, column: 8, scope: !295)
!303 = !DILocation(line: 118, column: 4, scope: !295)
!304 = !DILocation(line: 119, column: 3, scope: !275)
!305 = !DILocation(line: 109, column: 60, scope: !306)
!306 = !DILexicalBlockFile(scope: !270, file: !1, discriminator: 2)
!307 = !DILocation(line: 109, column: 69, scope: !306)
!308 = !DILocation(line: 109, column: 72, scope: !306)
!309 = !DILocation(line: 109, column: 67, scope: !306)
!310 = !DILocation(line: 109, column: 3, scope: !306)
!311 = !DILocation(line: 120, column: 3, scope: !265)
!312 = !DILocation(line: 120, column: 3, scope: !313)
!313 = !DILexicalBlockFile(scope: !265, file: !1, discriminator: 1)
!314 = !DILocation(line: 120, column: 3, scope: !315)
!315 = !DILexicalBlockFile(scope: !265, file: !1, discriminator: 2)
!316 = !DILocation(line: 120, column: 3, scope: !317)
!317 = !DILexicalBlockFile(scope: !265, file: !1, discriminator: 3)
!318 = !DILocation(line: 124, column: 18, scope: !105)
!319 = !DILocation(line: 124, column: 59, scope: !105)
!320 = !DILocation(line: 124, column: 64, scope: !105)
!321 = !DILocation(line: 124, column: 15, scope: !105)
!322 = !DILocation(line: 125, column: 2, scope: !105)
!323 = !DILocation(line: 125, column: 2, scope: !241)
!324 = !DILocation(line: 125, column: 2, scope: !243)
!325 = !DILocation(line: 125, column: 2, scope: !245)
!326 = !DILocation(line: 128, column: 36, scope: !105)
!327 = !DILocation(line: 128, column: 51, scope: !105)
!328 = !DILocation(line: 128, column: 49, scope: !105)
!329 = !DILocation(line: 128, column: 29, scope: !105)
!330 = !DILocation(line: 128, column: 9, scope: !105)
!331 = !DILocation(line: 128, column: 7, scope: !105)
!332 = !DILocation(line: 129, column: 6, scope: !333)
!333 = distinct !DILexicalBlock(scope: !105, file: !1, line: 129, column: 6)
!334 = !DILocation(line: 129, column: 11, scope: !333)
!335 = !DILocation(line: 129, column: 6, scope: !105)
!336 = !DILocation(line: 129, column: 20, scope: !337)
!337 = !DILexicalBlockFile(scope: !333, file: !1, discriminator: 1)
!338 = !DILocation(line: 132, column: 9, scope: !105)
!339 = !DILocation(line: 132, column: 2, scope: !105)
!340 = !DILocation(line: 133, column: 21, scope: !105)
!341 = !DILocation(line: 133, column: 2, scope: !105)
!342 = !DILocation(line: 133, column: 8, scope: !105)
!343 = !DILocation(line: 133, column: 11, scope: !105)
!344 = !DILocation(line: 133, column: 19, scope: !105)
!345 = !DILocation(line: 134, column: 2, scope: !105)
!346 = !DILocation(line: 134, column: 8, scope: !105)
!347 = !DILocation(line: 134, column: 14, scope: !105)
!348 = !DILocation(line: 135, column: 2, scope: !105)
!349 = !DILocation(line: 135, column: 8, scope: !105)
!350 = !DILocation(line: 135, column: 14, scope: !105)
!351 = !DILocation(line: 136, column: 27, scope: !105)
!352 = !DILocation(line: 136, column: 2, scope: !105)
!353 = !DILocation(line: 136, column: 8, scope: !105)
!354 = !DILocation(line: 136, column: 25, scope: !105)
!355 = !DILocation(line: 139, column: 21, scope: !105)
!356 = !DILocation(line: 139, column: 14, scope: !105)
!357 = !DILocation(line: 139, column: 28, scope: !105)
!358 = !DILocation(line: 139, column: 26, scope: !105)
!359 = !DILocation(line: 139, column: 12, scope: !105)
!360 = !DILocation(line: 140, column: 2, scope: !105)
!361 = !DILocation(line: 140, column: 2, scope: !241)
!362 = !DILocation(line: 140, column: 2, scope: !243)
!363 = !DILocation(line: 140, column: 2, scope: !245)
!364 = !DILocation(line: 143, column: 19, scope: !365)
!365 = distinct !DILexicalBlock(scope: !105, file: !1, line: 143, column: 2)
!366 = !DILocation(line: 143, column: 17, scope: !365)
!367 = !DILocation(line: 143, column: 45, scope: !365)
!368 = !DILocation(line: 143, column: 42, scope: !365)
!369 = !DILocation(line: 143, column: 38, scope: !365)
!370 = !DILocation(line: 143, column: 63, scope: !365)
!371 = !DILocation(line: 143, column: 7, scope: !365)
!372 = !DILocation(line: 144, column: 3, scope: !373)
!373 = distinct !DILexicalBlock(scope: !365, file: !1, line: 143, column: 2)
!374 = !DILocation(line: 144, column: 9, scope: !373)
!375 = !DILocation(line: 144, column: 6, scope: !373)
!376 = !DILocation(line: 143, column: 2, scope: !377)
!377 = !DILexicalBlockFile(scope: !365, file: !1, discriminator: 1)
!378 = !DILocation(line: 147, column: 8, scope: !379)
!379 = distinct !DILexicalBlock(scope: !380, file: !1, line: 147, column: 7)
!380 = distinct !DILexicalBlock(scope: !373, file: !1, line: 145, column: 2)
!381 = !DILocation(line: 147, column: 18, scope: !379)
!382 = !DILocation(line: 147, column: 16, scope: !379)
!383 = !DILocation(line: 147, column: 22, scope: !379)
!384 = !DILocation(line: 147, column: 7, scope: !380)
!385 = !DILocation(line: 148, column: 29, scope: !386)
!386 = distinct !DILexicalBlock(scope: !379, file: !1, line: 147, column: 28)
!387 = !DILocation(line: 148, column: 12, scope: !386)
!388 = !DILocation(line: 148, column: 9, scope: !386)
!389 = !DILocation(line: 149, column: 4, scope: !386)
!390 = !DILocation(line: 149, column: 4, scope: !391)
!391 = !DILexicalBlockFile(scope: !386, file: !1, discriminator: 1)
!392 = !DILocation(line: 149, column: 4, scope: !393)
!393 = !DILexicalBlockFile(scope: !386, file: !1, discriminator: 2)
!394 = !DILocation(line: 149, column: 4, scope: !395)
!395 = !DILexicalBlockFile(scope: !386, file: !1, discriminator: 3)
!396 = !DILocation(line: 150, column: 4, scope: !386)
!397 = !DILocation(line: 150, column: 4, scope: !391)
!398 = !DILocation(line: 150, column: 4, scope: !393)
!399 = !DILocation(line: 150, column: 4, scope: !395)
!400 = !DILocation(line: 151, column: 4, scope: !386)
!401 = !DILocation(line: 151, column: 4, scope: !391)
!402 = !DILocation(line: 151, column: 4, scope: !393)
!403 = !DILocation(line: 151, column: 4, scope: !395)
!404 = !DILocation(line: 153, column: 32, scope: !386)
!405 = !DILocation(line: 153, column: 17, scope: !386)
!406 = !DILocation(line: 153, column: 4, scope: !386)
!407 = !DILocation(line: 153, column: 10, scope: !386)
!408 = !DILocation(line: 153, column: 20, scope: !386)
!409 = !DILocation(line: 153, column: 30, scope: !386)
!410 = !DILocation(line: 154, column: 30, scope: !386)
!411 = !DILocation(line: 154, column: 17, scope: !386)
!412 = !DILocation(line: 154, column: 4, scope: !386)
!413 = !DILocation(line: 154, column: 10, scope: !386)
!414 = !DILocation(line: 154, column: 20, scope: !386)
!415 = !DILocation(line: 154, column: 28, scope: !386)
!416 = !DILocation(line: 160, column: 18, scope: !386)
!417 = !DILocation(line: 160, column: 24, scope: !386)
!418 = !DILocation(line: 160, column: 37, scope: !386)
!419 = !DILocation(line: 160, column: 42, scope: !386)
!420 = !DILocation(line: 160, column: 14, scope: !386)
!421 = !DILocation(line: 163, column: 4, scope: !386)
!422 = !DILocation(line: 163, column: 10, scope: !386)
!423 = !DILocation(line: 163, column: 28, scope: !386)
!424 = !DILocation(line: 163, column: 15, scope: !386)
!425 = !DILocation(line: 163, column: 21, scope: !386)
!426 = !DILocation(line: 163, column: 31, scope: !386)
!427 = !DILocation(line: 164, column: 5, scope: !386)
!428 = !DILocation(line: 165, column: 3, scope: !386)
!429 = !DILocation(line: 166, column: 2, scope: !380)
!430 = !DILocation(line: 144, column: 27, scope: !431)
!431 = !DILexicalBlockFile(scope: !373, file: !1, discriminator: 1)
!432 = !DILocation(line: 144, column: 36, scope: !431)
!433 = !DILocation(line: 144, column: 39, scope: !431)
!434 = !DILocation(line: 144, column: 34, scope: !431)
!435 = !DILocation(line: 143, column: 2, scope: !436)
!436 = !DILexicalBlockFile(scope: !373, file: !1, discriminator: 2)
!437 = !DILocation(line: 168, column: 10, scope: !105)
!438 = !DILocation(line: 168, column: 16, scope: !105)
!439 = !DILocation(line: 168, column: 2, scope: !105)
!440 = !DILocation(line: 169, column: 1, scope: !105)
!441 = !DILocalVariable(name: "ctx", arg: 1, scope: !110, file: !1, line: 176, type: !108)
!442 = !DILocation(line: 176, column: 23, scope: !110)
!443 = !DILocalVariable(name: "ectx", scope: !110, file: !1, line: 178, type: !444)
!444 = !DIDerivedType(tag: DW_TAG_const_type, baseType: !19)
!445 = !DILocation(line: 178, column: 27, scope: !110)
!446 = !DILocation(line: 178, column: 54, scope: !110)
!447 = !DILocation(line: 178, column: 34, scope: !110)
!448 = !DILocalVariable(name: "i", scope: !110, file: !1, line: 179, type: !30)
!449 = !DILocation(line: 179, column: 11, scope: !110)
!450 = !DILocation(line: 181, column: 6, scope: !451)
!451 = distinct !DILexicalBlock(scope: !110, file: !1, line: 181, column: 6)
!452 = !DILocation(line: 181, column: 10, scope: !451)
!453 = !DILocation(line: 181, column: 6, scope: !110)
!454 = !DILocation(line: 181, column: 16, scope: !455)
!455 = !DILexicalBlockFile(scope: !451, file: !1, discriminator: 1)
!456 = !DILocation(line: 182, column: 2, scope: !110)
!457 = !DILocation(line: 182, column: 2, scope: !458)
!458 = !DILexicalBlockFile(scope: !110, file: !1, discriminator: 1)
!459 = !DILocation(line: 182, column: 2, scope: !460)
!460 = !DILexicalBlockFile(scope: !110, file: !1, discriminator: 2)
!461 = !DILocation(line: 182, column: 2, scope: !462)
!462 = !DILexicalBlockFile(scope: !110, file: !1, discriminator: 3)
!463 = !DILocation(line: 183, column: 2, scope: !110)
!464 = !DILocation(line: 183, column: 8, scope: !110)
!465 = !DILocation(line: 183, column: 14, scope: !110)
!466 = !DILocation(line: 186, column: 9, scope: !467)
!467 = distinct !DILexicalBlock(scope: !110, file: !1, line: 186, column: 2)
!468 = !DILocation(line: 186, column: 7, scope: !467)
!469 = !DILocation(line: 186, column: 14, scope: !470)
!470 = !DILexicalBlockFile(scope: !471, file: !1, discriminator: 1)
!471 = distinct !DILexicalBlock(scope: !467, file: !1, line: 186, column: 2)
!472 = !DILocation(line: 186, column: 18, scope: !470)
!473 = !DILocation(line: 186, column: 24, scope: !470)
!474 = !DILocation(line: 186, column: 16, scope: !470)
!475 = !DILocation(line: 186, column: 2, scope: !470)
!476 = !DILocalVariable(name: "info", scope: !477, file: !1, line: 187, type: !44)
!477 = distinct !DILexicalBlock(scope: !471, file: !1, line: 186, column: 47)
!478 = !DILocation(line: 187, column: 27, scope: !477)
!479 = !DILocation(line: 187, column: 47, scope: !477)
!480 = !DILocation(line: 187, column: 34, scope: !477)
!481 = !DILocation(line: 187, column: 40, scope: !477)
!482 = !DILocation(line: 187, column: 50, scope: !477)
!483 = !DILocation(line: 188, column: 7, scope: !484)
!484 = distinct !DILexicalBlock(scope: !477, file: !1, line: 188, column: 7)
!485 = !DILocation(line: 188, column: 13, scope: !484)
!486 = !DILocation(line: 188, column: 21, scope: !484)
!487 = !DILocation(line: 188, column: 7, scope: !477)
!488 = !DILocation(line: 189, column: 4, scope: !489)
!489 = distinct !DILexicalBlock(scope: !484, file: !1, line: 188, column: 27)
!490 = !DILocation(line: 189, column: 10, scope: !489)
!491 = !DILocation(line: 189, column: 31, scope: !489)
!492 = !DILocation(line: 189, column: 18, scope: !489)
!493 = !DILocation(line: 189, column: 24, scope: !489)
!494 = !DILocation(line: 189, column: 34, scope: !489)
!495 = !DILocation(line: 190, column: 3, scope: !489)
!496 = !DILocation(line: 191, column: 2, scope: !477)
!497 = !DILocation(line: 186, column: 43, scope: !498)
!498 = !DILexicalBlockFile(scope: !471, file: !1, discriminator: 2)
!499 = !DILocation(line: 186, column: 2, scope: !498)
!500 = !DILocation(line: 193, column: 7, scope: !110)
!501 = !DILocation(line: 193, column: 2, scope: !110)
!502 = !DILocation(line: 194, column: 1, scope: !110)
!503 = !DILocation(line: 194, column: 1, scope: !458)
!504 = !DILocalVariable(name: "ctx", arg: 1, scope: !113, file: !1, line: 202, type: !108)
!505 = !DILocation(line: 202, column: 34, scope: !113)
!506 = !DILocalVariable(name: "ectx", scope: !113, file: !1, line: 204, type: !444)
!507 = !DILocation(line: 204, column: 27, scope: !113)
!508 = !DILocation(line: 204, column: 54, scope: !113)
!509 = !DILocation(line: 204, column: 34, scope: !113)
!510 = !DILocalVariable(name: "i", scope: !113, file: !1, line: 205, type: !30)
!511 = !DILocation(line: 205, column: 11, scope: !113)
!512 = !DILocation(line: 207, column: 2, scope: !113)
!513 = !DILocation(line: 207, column: 2, scope: !514)
!514 = !DILexicalBlockFile(scope: !113, file: !1, discriminator: 1)
!515 = !DILocation(line: 207, column: 2, scope: !516)
!516 = !DILexicalBlockFile(scope: !113, file: !1, discriminator: 2)
!517 = !DILocation(line: 207, column: 2, scope: !518)
!518 = !DILexicalBlockFile(scope: !113, file: !1, discriminator: 3)
!519 = !DILocation(line: 208, column: 2, scope: !113)
!520 = !DILocation(line: 208, column: 2, scope: !514)
!521 = !DILocation(line: 208, column: 2, scope: !516)
!522 = !DILocation(line: 208, column: 2, scope: !518)
!523 = !DILocation(line: 209, column: 2, scope: !113)
!524 = !DILocation(line: 209, column: 8, scope: !113)
!525 = !DILocation(line: 209, column: 14, scope: !113)
!526 = !DILocation(line: 212, column: 9, scope: !527)
!527 = distinct !DILexicalBlock(scope: !113, file: !1, line: 212, column: 2)
!528 = !DILocation(line: 212, column: 7, scope: !527)
!529 = !DILocation(line: 212, column: 14, scope: !530)
!530 = !DILexicalBlockFile(scope: !531, file: !1, discriminator: 1)
!531 = distinct !DILexicalBlock(scope: !527, file: !1, line: 212, column: 2)
!532 = !DILocation(line: 212, column: 18, scope: !530)
!533 = !DILocation(line: 212, column: 24, scope: !530)
!534 = !DILocation(line: 212, column: 16, scope: !530)
!535 = !DILocation(line: 212, column: 2, scope: !530)
!536 = !DILocalVariable(name: "info", scope: !537, file: !1, line: 213, type: !44)
!537 = distinct !DILexicalBlock(scope: !531, file: !1, line: 212, column: 47)
!538 = !DILocation(line: 213, column: 27, scope: !537)
!539 = !DILocation(line: 213, column: 47, scope: !537)
!540 = !DILocation(line: 213, column: 34, scope: !537)
!541 = !DILocation(line: 213, column: 40, scope: !537)
!542 = !DILocation(line: 213, column: 50, scope: !537)
!543 = !DILocation(line: 214, column: 7, scope: !544)
!544 = distinct !DILexicalBlock(scope: !537, file: !1, line: 214, column: 7)
!545 = !DILocation(line: 214, column: 13, scope: !544)
!546 = !DILocation(line: 214, column: 21, scope: !544)
!547 = !DILocation(line: 214, column: 7, scope: !537)
!548 = !DILocation(line: 215, column: 4, scope: !549)
!549 = distinct !DILexicalBlock(scope: !544, file: !1, line: 214, column: 27)
!550 = !DILocation(line: 215, column: 10, scope: !549)
!551 = !DILocation(line: 215, column: 31, scope: !549)
!552 = !DILocation(line: 215, column: 18, scope: !549)
!553 = !DILocation(line: 215, column: 24, scope: !549)
!554 = !DILocation(line: 215, column: 34, scope: !549)
!555 = !DILocation(line: 216, column: 3, scope: !549)
!556 = !DILocation(line: 218, column: 3, scope: !537)
!557 = !DILocation(line: 218, column: 3, scope: !558)
!558 = !DILexicalBlockFile(scope: !537, file: !1, discriminator: 1)
!559 = !DILocation(line: 218, column: 3, scope: !560)
!560 = !DILexicalBlockFile(scope: !537, file: !1, discriminator: 2)
!561 = !DILocation(line: 218, column: 3, scope: !562)
!562 = !DILexicalBlockFile(scope: !537, file: !1, discriminator: 3)
!563 = !DILocation(line: 219, column: 3, scope: !537)
!564 = !DILocation(line: 219, column: 9, scope: !537)
!565 = !DILocation(line: 219, column: 27, scope: !537)
!566 = !DILocation(line: 219, column: 14, scope: !537)
!567 = !DILocation(line: 219, column: 20, scope: !537)
!568 = !DILocation(line: 219, column: 30, scope: !537)
!569 = !DILocation(line: 220, column: 2, scope: !537)
!570 = !DILocation(line: 212, column: 43, scope: !571)
!571 = !DILexicalBlockFile(scope: !531, file: !1, discriminator: 2)
!572 = !DILocation(line: 212, column: 2, scope: !571)
!573 = !DILocation(line: 221, column: 2, scope: !113)
!574 = !DILocation(line: 221, column: 8, scope: !113)
!575 = !DILocation(line: 221, column: 14, scope: !113)
!576 = !DILocation(line: 222, column: 1, scope: !113)
!577 = !DILocalVariable(name: "ctx", arg: 1, scope: !114, file: !1, line: 233, type: !108)
!578 = !DILocation(line: 233, column: 34, scope: !114)
!579 = !DILocalVariable(name: "message", arg: 2, scope: !114, file: !1, line: 233, type: !77)
!580 = !DILocation(line: 233, column: 51, scope: !114)
!581 = !DILocalVariable(name: "length", arg: 3, scope: !114, file: !1, line: 233, type: !55)
!582 = !DILocation(line: 233, column: 67, scope: !114)
!583 = !DILocalVariable(name: "ectx", scope: !114, file: !1, line: 235, type: !444)
!584 = !DILocation(line: 235, column: 27, scope: !114)
!585 = !DILocation(line: 235, column: 54, scope: !114)
!586 = !DILocation(line: 235, column: 34, scope: !114)
!587 = !DILocalVariable(name: "i", scope: !114, file: !1, line: 236, type: !30)
!588 = !DILocation(line: 236, column: 11, scope: !114)
!589 = !DILocation(line: 238, column: 2, scope: !114)
!590 = !DILocation(line: 238, column: 2, scope: !591)
!591 = !DILexicalBlockFile(scope: !114, file: !1, discriminator: 1)
!592 = !DILocation(line: 238, column: 2, scope: !593)
!593 = !DILexicalBlockFile(scope: !114, file: !1, discriminator: 2)
!594 = !DILocation(line: 238, column: 2, scope: !595)
!595 = !DILexicalBlockFile(scope: !114, file: !1, discriminator: 3)
!596 = !DILocation(line: 239, column: 6, scope: !597)
!597 = distinct !DILexicalBlock(scope: !114, file: !1, line: 239, column: 6)
!598 = !DILocation(line: 239, column: 12, scope: !597)
!599 = !DILocation(line: 239, column: 18, scope: !597)
!600 = !DILocation(line: 239, column: 6, scope: !114)
!601 = !DILocation(line: 239, column: 35, scope: !602)
!602 = !DILexicalBlockFile(scope: !597, file: !1, discriminator: 1)
!603 = !DILocation(line: 241, column: 19, scope: !114)
!604 = !DILocation(line: 241, column: 2, scope: !114)
!605 = !DILocation(line: 241, column: 7, scope: !114)
!606 = !DILocation(line: 241, column: 16, scope: !114)
!607 = !DILocation(line: 244, column: 9, scope: !608)
!608 = distinct !DILexicalBlock(scope: !114, file: !1, line: 244, column: 2)
!609 = !DILocation(line: 244, column: 7, scope: !608)
!610 = !DILocation(line: 244, column: 14, scope: !611)
!611 = !DILexicalBlockFile(scope: !612, file: !1, discriminator: 1)
!612 = distinct !DILexicalBlock(scope: !608, file: !1, line: 244, column: 2)
!613 = !DILocation(line: 244, column: 18, scope: !611)
!614 = !DILocation(line: 244, column: 24, scope: !611)
!615 = !DILocation(line: 244, column: 16, scope: !611)
!616 = !DILocation(line: 244, column: 2, scope: !611)
!617 = !DILocalVariable(name: "info", scope: !618, file: !1, line: 245, type: !44)
!618 = distinct !DILexicalBlock(scope: !612, file: !1, line: 244, column: 47)
!619 = !DILocation(line: 245, column: 27, scope: !618)
!620 = !DILocation(line: 245, column: 47, scope: !618)
!621 = !DILocation(line: 245, column: 34, scope: !618)
!622 = !DILocation(line: 245, column: 40, scope: !618)
!623 = !DILocation(line: 245, column: 50, scope: !618)
!624 = !DILocation(line: 246, column: 3, scope: !618)
!625 = !DILocation(line: 246, column: 3, scope: !626)
!626 = !DILexicalBlockFile(scope: !618, file: !1, discriminator: 1)
!627 = !DILocation(line: 246, column: 3, scope: !628)
!628 = !DILexicalBlockFile(scope: !618, file: !1, discriminator: 2)
!629 = !DILocation(line: 246, column: 3, scope: !630)
!630 = !DILexicalBlockFile(scope: !618, file: !1, discriminator: 3)
!631 = !DILocation(line: 247, column: 3, scope: !618)
!632 = !DILocation(line: 247, column: 9, scope: !618)
!633 = !DILocation(line: 247, column: 29, scope: !618)
!634 = !DILocation(line: 247, column: 16, scope: !618)
!635 = !DILocation(line: 247, column: 22, scope: !618)
!636 = !DILocation(line: 247, column: 32, scope: !618)
!637 = !DILocation(line: 247, column: 41, scope: !618)
!638 = !DILocation(line: 247, column: 50, scope: !618)
!639 = !DILocation(line: 248, column: 2, scope: !618)
!640 = !DILocation(line: 244, column: 43, scope: !641)
!641 = !DILexicalBlockFile(scope: !612, file: !1, discriminator: 2)
!642 = !DILocation(line: 244, column: 2, scope: !641)
!643 = !DILocation(line: 249, column: 2, scope: !114)
!644 = !DILocation(line: 250, column: 1, scope: !114)
!645 = !DILocalVariable(name: "ctx", arg: 1, scope: !117, file: !1, line: 259, type: !108)
!646 = !DILocation(line: 259, column: 33, scope: !117)
!647 = !DILocalVariable(name: "first_result", arg: 2, scope: !117, file: !1, line: 259, type: !84)
!648 = !DILocation(line: 259, column: 53, scope: !117)
!649 = !DILocalVariable(name: "i", scope: !117, file: !1, line: 261, type: !30)
!650 = !DILocation(line: 261, column: 11, scope: !117)
!651 = !DILocalVariable(name: "buffer", scope: !117, file: !1, line: 262, type: !652)
!652 = !DICompositeType(tag: DW_TAG_array_type, baseType: !85, size: 1040, align: 8, elements: !653)
!653 = !{!654}
!654 = !DISubrange(count: 130)
!655 = !DILocation(line: 262, column: 16, scope: !117)
!656 = !DILocalVariable(name: "out", scope: !117, file: !1, line: 263, type: !84)
!657 = !DILocation(line: 263, column: 17, scope: !117)
!658 = !DILocation(line: 263, column: 24, scope: !117)
!659 = !DILocation(line: 263, column: 39, scope: !660)
!660 = !DILexicalBlockFile(scope: !117, file: !1, discriminator: 1)
!661 = !DILocation(line: 263, column: 24, scope: !660)
!662 = !DILocation(line: 263, column: 54, scope: !663)
!663 = !DILexicalBlockFile(scope: !117, file: !1, discriminator: 2)
!664 = !DILocation(line: 263, column: 24, scope: !663)
!665 = !DILocation(line: 263, column: 24, scope: !666)
!666 = !DILexicalBlockFile(scope: !117, file: !1, discriminator: 3)
!667 = !DILocation(line: 263, column: 17, scope: !666)
!668 = !DILocalVariable(name: "ectx", scope: !117, file: !1, line: 264, type: !444)
!669 = !DILocation(line: 264, column: 27, scope: !117)
!670 = !DILocation(line: 264, column: 54, scope: !117)
!671 = !DILocation(line: 264, column: 34, scope: !117)
!672 = !DILocation(line: 265, column: 2, scope: !117)
!673 = !DILocation(line: 265, column: 2, scope: !660)
!674 = !DILocation(line: 265, column: 2, scope: !663)
!675 = !DILocation(line: 265, column: 2, scope: !666)
!676 = !DILocation(line: 268, column: 7, scope: !677)
!677 = distinct !DILexicalBlock(scope: !117, file: !1, line: 268, column: 6)
!678 = !DILocation(line: 268, column: 13, scope: !677)
!679 = !DILocation(line: 268, column: 19, scope: !677)
!680 = !DILocation(line: 268, column: 42, scope: !677)
!681 = !DILocation(line: 268, column: 6, scope: !117)
!682 = !DILocation(line: 269, column: 39, scope: !677)
!683 = !DILocation(line: 272, column: 9, scope: !684)
!684 = distinct !DILexicalBlock(scope: !117, file: !1, line: 272, column: 2)
!685 = !DILocation(line: 272, column: 7, scope: !684)
!686 = !DILocation(line: 272, column: 14, scope: !687)
!687 = !DILexicalBlockFile(scope: !688, file: !1, discriminator: 1)
!688 = distinct !DILexicalBlock(scope: !684, file: !1, line: 272, column: 2)
!689 = !DILocation(line: 272, column: 18, scope: !687)
!690 = !DILocation(line: 272, column: 24, scope: !687)
!691 = !DILocation(line: 272, column: 16, scope: !687)
!692 = !DILocation(line: 272, column: 2, scope: !687)
!693 = !DILocalVariable(name: "info", scope: !694, file: !1, line: 273, type: !44)
!694 = distinct !DILexicalBlock(scope: !688, file: !1, line: 272, column: 47)
!695 = !DILocation(line: 273, column: 27, scope: !694)
!696 = !DILocation(line: 273, column: 47, scope: !694)
!697 = !DILocation(line: 273, column: 34, scope: !694)
!698 = !DILocation(line: 273, column: 40, scope: !694)
!699 = !DILocation(line: 273, column: 50, scope: !694)
!700 = !DILocation(line: 274, column: 3, scope: !694)
!701 = !DILocation(line: 274, column: 3, scope: !702)
!702 = !DILexicalBlockFile(scope: !694, file: !1, discriminator: 1)
!703 = !DILocation(line: 274, column: 3, scope: !704)
!704 = !DILexicalBlockFile(scope: !694, file: !1, discriminator: 2)
!705 = !DILocation(line: 274, column: 3, scope: !706)
!706 = !DILexicalBlockFile(scope: !694, file: !1, discriminator: 3)
!707 = !DILocation(line: 275, column: 3, scope: !694)
!708 = !DILocation(line: 275, column: 3, scope: !702)
!709 = !DILocation(line: 275, column: 3, scope: !704)
!710 = !DILocation(line: 275, column: 3, scope: !706)
!711 = !DILocation(line: 276, column: 3, scope: !694)
!712 = !DILocation(line: 276, column: 9, scope: !694)
!713 = !DILocation(line: 276, column: 28, scope: !694)
!714 = !DILocation(line: 276, column: 15, scope: !694)
!715 = !DILocation(line: 276, column: 21, scope: !694)
!716 = !DILocation(line: 276, column: 31, scope: !694)
!717 = !DILocation(line: 276, column: 40, scope: !694)
!718 = !DILocation(line: 277, column: 9, scope: !694)
!719 = !DILocation(line: 277, column: 7, scope: !694)
!720 = !DILocation(line: 278, column: 2, scope: !694)
!721 = !DILocation(line: 272, column: 43, scope: !722)
!722 = !DILexicalBlockFile(scope: !688, file: !1, discriminator: 2)
!723 = !DILocation(line: 272, column: 2, scope: !722)
!724 = !DILocation(line: 279, column: 2, scope: !117)
!725 = !DILocation(line: 279, column: 8, scope: !117)
!726 = !DILocation(line: 279, column: 14, scope: !117)
!727 = !DILocation(line: 280, column: 2, scope: !117)
!728 = !DILocation(line: 281, column: 1, scope: !117)
!729 = !DILocalVariable(name: "ctx", arg: 1, scope: !120, file: !1, line: 343, type: !108)
!730 = !DILocation(line: 343, column: 41, scope: !120)
!731 = !DILocalVariable(name: "callback", arg: 2, scope: !120, file: !1, line: 343, type: !92)
!732 = !DILocation(line: 343, column: 63, scope: !120)
!733 = !DILocalVariable(name: "callback_data", arg: 3, scope: !120, file: !1, line: 343, type: !35)
!734 = !DILocation(line: 343, column: 79, scope: !120)
!735 = !DILocation(line: 345, column: 40, scope: !120)
!736 = !DILocation(line: 345, column: 23, scope: !120)
!737 = !DILocation(line: 345, column: 29, scope: !120)
!738 = !DILocation(line: 345, column: 38, scope: !120)
!739 = !DILocation(line: 346, column: 45, scope: !120)
!740 = !DILocation(line: 346, column: 23, scope: !120)
!741 = !DILocation(line: 346, column: 29, scope: !120)
!742 = !DILocation(line: 346, column: 43, scope: !120)
!743 = !DILocation(line: 347, column: 1, scope: !120)
!744 = !DILocalVariable(name: "hash_id", arg: 1, scope: !123, file: !1, line: 361, type: !30)
!745 = !DILocation(line: 361, column: 34, scope: !123)
!746 = !DILocalVariable(name: "message", arg: 2, scope: !123, file: !1, line: 361, type: !77)
!747 = !DILocation(line: 361, column: 55, scope: !123)
!748 = !DILocalVariable(name: "length", arg: 3, scope: !123, file: !1, line: 361, type: !55)
!749 = !DILocation(line: 361, column: 71, scope: !123)
!750 = !DILocalVariable(name: "result", arg: 4, scope: !123, file: !1, line: 361, type: !84)
!751 = !DILocation(line: 361, column: 94, scope: !123)
!752 = !DILocalVariable(name: "ctx", scope: !123, file: !1, line: 363, type: !108)
!753 = !DILocation(line: 363, column: 8, scope: !123)
!754 = !DILocation(line: 364, column: 10, scope: !123)
!755 = !DILocation(line: 365, column: 19, scope: !123)
!756 = !DILocation(line: 365, column: 8, scope: !123)
!757 = !DILocation(line: 365, column: 6, scope: !123)
!758 = !DILocation(line: 366, column: 6, scope: !759)
!759 = distinct !DILexicalBlock(scope: !123, file: !1, line: 366, column: 6)
!760 = !DILocation(line: 366, column: 10, scope: !759)
!761 = !DILocation(line: 366, column: 6, scope: !123)
!762 = !DILocation(line: 366, column: 19, scope: !763)
!763 = !DILexicalBlockFile(scope: !759, file: !1, discriminator: 1)
!764 = !DILocation(line: 367, column: 15, scope: !123)
!765 = !DILocation(line: 367, column: 20, scope: !123)
!766 = !DILocation(line: 367, column: 29, scope: !123)
!767 = !DILocation(line: 367, column: 2, scope: !123)
!768 = !DILocation(line: 368, column: 14, scope: !123)
!769 = !DILocation(line: 368, column: 19, scope: !123)
!770 = !DILocation(line: 368, column: 2, scope: !123)
!771 = !DILocation(line: 369, column: 13, scope: !123)
!772 = !DILocation(line: 369, column: 2, scope: !123)
!773 = !DILocation(line: 370, column: 2, scope: !123)
!774 = !DILocation(line: 371, column: 1, scope: !123)
!775 = !DILocalVariable(name: "ctx", arg: 1, scope: !126, file: !1, line: 384, type: !108)
!776 = !DILocation(line: 384, column: 39, scope: !126)
!777 = !DILocalVariable(name: "fd", arg: 2, scope: !126, file: !1, line: 384, type: !129)
!778 = !DILocation(line: 384, column: 50, scope: !126)
!779 = !DILocalVariable(name: "ectx", scope: !126, file: !1, line: 386, type: !444)
!780 = !DILocation(line: 386, column: 27, scope: !126)
!781 = !DILocation(line: 386, column: 54, scope: !126)
!782 = !DILocation(line: 386, column: 34, scope: !126)
!783 = !DILocalVariable(name: "block_size", scope: !126, file: !1, line: 387, type: !784)
!784 = !DIDerivedType(tag: DW_TAG_const_type, baseType: !55)
!785 = !DILocation(line: 387, column: 15, scope: !126)
!786 = !DILocalVariable(name: "buffer", scope: !126, file: !1, line: 388, type: !84)
!787 = !DILocation(line: 388, column: 17, scope: !126)
!788 = !DILocalVariable(name: "pmem", scope: !126, file: !1, line: 388, type: !84)
!789 = !DILocation(line: 388, column: 26, scope: !126)
!790 = !DILocalVariable(name: "length", scope: !126, file: !1, line: 389, type: !55)
!791 = !DILocation(line: 389, column: 9, scope: !126)
!792 = !DILocalVariable(name: "align8", scope: !126, file: !1, line: 389, type: !55)
!793 = !DILocation(line: 389, column: 21, scope: !126)
!794 = !DILocalVariable(name: "res", scope: !126, file: !1, line: 390, type: !96)
!795 = !DILocation(line: 390, column: 6, scope: !126)
!796 = !DILocation(line: 391, column: 6, scope: !797)
!797 = distinct !DILexicalBlock(scope: !126, file: !1, line: 391, column: 6)
!798 = !DILocation(line: 391, column: 12, scope: !797)
!799 = !DILocation(line: 391, column: 18, scope: !797)
!800 = !DILocation(line: 391, column: 6, scope: !126)
!801 = !DILocation(line: 391, column: 35, scope: !802)
!802 = !DILexicalBlockFile(scope: !797, file: !1, discriminator: 1)
!803 = !DILocation(line: 393, column: 6, scope: !804)
!804 = distinct !DILexicalBlock(scope: !126, file: !1, line: 393, column: 6)
!805 = !DILocation(line: 393, column: 10, scope: !804)
!806 = !DILocation(line: 393, column: 6, scope: !126)
!807 = !DILocation(line: 394, column: 3, scope: !808)
!808 = distinct !DILexicalBlock(scope: !804, file: !1, line: 393, column: 19)
!809 = !DILocation(line: 394, column: 9, scope: !808)
!810 = !DILocation(line: 395, column: 3, scope: !808)
!811 = !DILocation(line: 398, column: 25, scope: !126)
!812 = !DILocation(line: 398, column: 7, scope: !126)
!813 = !DILocation(line: 399, column: 7, scope: !814)
!814 = distinct !DILexicalBlock(scope: !126, file: !1, line: 399, column: 6)
!815 = !DILocation(line: 399, column: 6, scope: !126)
!816 = !DILocation(line: 399, column: 13, scope: !817)
!817 = !DILexicalBlockFile(scope: !814, file: !1, discriminator: 1)
!818 = !DILocation(line: 401, column: 32, scope: !126)
!819 = !DILocation(line: 401, column: 30, scope: !126)
!820 = !DILocation(line: 401, column: 38, scope: !126)
!821 = !DILocation(line: 401, column: 9, scope: !126)
!822 = !DILocation(line: 402, column: 11, scope: !126)
!823 = !DILocation(line: 402, column: 18, scope: !126)
!824 = !DILocation(line: 402, column: 16, scope: !126)
!825 = !DILocation(line: 402, column: 9, scope: !126)
!826 = !DILocation(line: 404, column: 2, scope: !126)
!827 = !DILocation(line: 404, column: 15, scope: !828)
!828 = !DILexicalBlockFile(scope: !126, file: !1, discriminator: 1)
!829 = !DILocation(line: 404, column: 10, scope: !828)
!830 = !DILocation(line: 404, column: 9, scope: !828)
!831 = !DILocation(line: 404, column: 2, scope: !828)
!832 = !DILocation(line: 406, column: 7, scope: !833)
!833 = distinct !DILexicalBlock(scope: !834, file: !1, line: 406, column: 7)
!834 = distinct !DILexicalBlock(scope: !126, file: !1, line: 404, column: 20)
!835 = !DILocation(line: 406, column: 13, scope: !833)
!836 = !DILocation(line: 406, column: 19, scope: !833)
!837 = !DILocation(line: 406, column: 7, scope: !834)
!838 = !DILocation(line: 406, column: 36, scope: !839)
!839 = !DILexicalBlockFile(scope: !833, file: !1, discriminator: 1)
!840 = !DILocation(line: 408, column: 18, scope: !834)
!841 = !DILocation(line: 408, column: 41, scope: !834)
!842 = !DILocation(line: 408, column: 12, scope: !834)
!843 = !DILocation(line: 408, column: 10, scope: !834)
!844 = !DILocation(line: 410, column: 14, scope: !845)
!845 = distinct !DILexicalBlock(scope: !834, file: !1, line: 410, column: 7)
!846 = !DILocation(line: 410, column: 7, scope: !845)
!847 = !DILocation(line: 410, column: 7, scope: !834)
!848 = !DILocation(line: 411, column: 8, scope: !849)
!849 = distinct !DILexicalBlock(scope: !845, file: !1, line: 410, column: 19)
!850 = !DILocation(line: 412, column: 4, scope: !849)
!851 = !DILocation(line: 413, column: 14, scope: !852)
!852 = distinct !DILexicalBlock(scope: !845, file: !1, line: 413, column: 14)
!853 = !DILocation(line: 413, column: 14, scope: !845)
!854 = !DILocation(line: 414, column: 17, scope: !855)
!855 = distinct !DILexicalBlock(scope: !852, file: !1, line: 413, column: 22)
!856 = !DILocation(line: 414, column: 22, scope: !855)
!857 = !DILocation(line: 414, column: 30, scope: !855)
!858 = !DILocation(line: 414, column: 4, scope: !855)
!859 = !DILocation(line: 416, column: 8, scope: !860)
!860 = distinct !DILexicalBlock(scope: !855, file: !1, line: 416, column: 8)
!861 = !DILocation(line: 416, column: 14, scope: !860)
!862 = !DILocation(line: 416, column: 8, scope: !855)
!863 = !DILocation(line: 417, column: 24, scope: !864)
!864 = distinct !DILexicalBlock(scope: !860, file: !1, line: 416, column: 24)
!865 = !DILocation(line: 417, column: 30, scope: !864)
!866 = !DILocation(line: 417, column: 6, scope: !864)
!867 = !DILocation(line: 417, column: 40, scope: !864)
!868 = !DILocation(line: 417, column: 46, scope: !864)
!869 = !DILocation(line: 417, column: 61, scope: !864)
!870 = !DILocation(line: 417, column: 67, scope: !864)
!871 = !DILocation(line: 417, column: 70, scope: !864)
!872 = !DILocation(line: 417, column: 5, scope: !864)
!873 = !DILocation(line: 418, column: 4, scope: !864)
!874 = !DILocation(line: 419, column: 3, scope: !855)
!875 = !DILocation(line: 404, column: 2, scope: !876)
!876 = !DILexicalBlockFile(scope: !126, file: !1, discriminator: 2)
!877 = !DILocation(line: 422, column: 7, scope: !126)
!878 = !DILocation(line: 422, column: 2, scope: !126)
!879 = !DILocation(line: 423, column: 9, scope: !126)
!880 = !DILocation(line: 423, column: 2, scope: !126)
!881 = !DILocation(line: 424, column: 1, scope: !126)
!882 = !DILocalVariable(name: "hash_id", arg: 1, scope: !182, file: !1, line: 434, type: !30)
!883 = !DILocation(line: 434, column: 35, scope: !182)
!884 = !DILocalVariable(name: "filepath", arg: 2, scope: !182, file: !1, line: 434, type: !59)
!885 = !DILocation(line: 434, column: 56, scope: !182)
!886 = !DILocalVariable(name: "result", arg: 3, scope: !182, file: !1, line: 434, type: !84)
!887 = !DILocation(line: 434, column: 81, scope: !182)
!888 = !DILocalVariable(name: "fd", scope: !182, file: !1, line: 436, type: !129)
!889 = !DILocation(line: 436, column: 8, scope: !182)
!890 = !DILocalVariable(name: "ctx", scope: !182, file: !1, line: 437, type: !108)
!891 = !DILocation(line: 437, column: 8, scope: !182)
!892 = !DILocalVariable(name: "res", scope: !182, file: !1, line: 438, type: !96)
!893 = !DILocation(line: 438, column: 6, scope: !182)
!894 = !DILocation(line: 440, column: 10, scope: !182)
!895 = !DILocation(line: 441, column: 6, scope: !896)
!896 = distinct !DILexicalBlock(scope: !182, file: !1, line: 441, column: 6)
!897 = !DILocation(line: 441, column: 14, scope: !896)
!898 = !DILocation(line: 441, column: 6, scope: !182)
!899 = !DILocation(line: 442, column: 3, scope: !900)
!900 = distinct !DILexicalBlock(scope: !896, file: !1, line: 441, column: 20)
!901 = !DILocation(line: 442, column: 9, scope: !900)
!902 = !DILocation(line: 443, column: 3, scope: !900)
!903 = !DILocation(line: 446, column: 18, scope: !904)
!904 = distinct !DILexicalBlock(scope: !182, file: !1, line: 446, column: 6)
!905 = !DILocation(line: 446, column: 12, scope: !904)
!906 = !DILocation(line: 446, column: 10, scope: !904)
!907 = !DILocation(line: 446, column: 35, scope: !904)
!908 = !DILocation(line: 446, column: 6, scope: !182)
!909 = !DILocation(line: 446, column: 44, scope: !910)
!910 = !DILexicalBlockFile(scope: !904, file: !1, discriminator: 1)
!911 = !DILocation(line: 448, column: 24, scope: !912)
!912 = distinct !DILexicalBlock(scope: !182, file: !1, line: 448, column: 6)
!913 = !DILocation(line: 448, column: 13, scope: !912)
!914 = !DILocation(line: 448, column: 11, scope: !912)
!915 = !DILocation(line: 448, column: 34, scope: !912)
!916 = !DILocation(line: 448, column: 6, scope: !182)
!917 = !DILocation(line: 448, column: 43, scope: !918)
!918 = !DILexicalBlockFile(scope: !912, file: !1, discriminator: 1)
!919 = !DILocation(line: 450, column: 26, scope: !182)
!920 = !DILocation(line: 450, column: 31, scope: !182)
!921 = !DILocation(line: 450, column: 8, scope: !182)
!922 = !DILocation(line: 450, column: 6, scope: !182)
!923 = !DILocation(line: 451, column: 9, scope: !182)
!924 = !DILocation(line: 451, column: 2, scope: !182)
!925 = !DILocation(line: 453, column: 14, scope: !182)
!926 = !DILocation(line: 453, column: 19, scope: !182)
!927 = !DILocation(line: 453, column: 2, scope: !182)
!928 = !DILocation(line: 454, column: 13, scope: !182)
!929 = !DILocation(line: 454, column: 2, scope: !182)
!930 = !DILocation(line: 455, column: 9, scope: !182)
!931 = !DILocation(line: 455, column: 2, scope: !182)
!932 = !DILocation(line: 456, column: 1, scope: !182)
!933 = !DILocalVariable(name: "hash_id", arg: 1, scope: !185, file: !1, line: 502, type: !30)
!934 = !DILocation(line: 502, column: 45, scope: !185)
!935 = !DILocation(line: 504, column: 10, scope: !185)
!936 = !DILocation(line: 506, column: 6, scope: !937)
!937 = distinct !DILexicalBlock(scope: !185, file: !1, line: 506, column: 6)
!938 = !DILocation(line: 506, column: 18, scope: !937)
!939 = !DILocation(line: 506, column: 34, scope: !937)
!940 = !DILocation(line: 506, column: 28, scope: !937)
!941 = !DILocation(line: 506, column: 26, scope: !937)
!942 = !DILocation(line: 506, column: 14, scope: !937)
!943 = !DILocation(line: 506, column: 6, scope: !185)
!944 = !DILocation(line: 506, column: 44, scope: !945)
!945 = !DILexicalBlockFile(scope: !937, file: !1, discriminator: 1)
!946 = !DILocation(line: 508, column: 26, scope: !185)
!947 = !DILocation(line: 508, column: 9, scope: !185)
!948 = !DILocation(line: 508, column: 46, scope: !185)
!949 = !DILocation(line: 508, column: 2, scope: !185)
!950 = !DILocation(line: 509, column: 1, scope: !185)
!951 = !DILocalVariable(name: "hash_id", arg: 1, scope: !190, file: !1, line: 531, type: !30)
!952 = !DILocation(line: 531, column: 46, scope: !190)
!953 = !DILocation(line: 533, column: 10, scope: !190)
!954 = !DILocation(line: 534, column: 6, scope: !955)
!955 = distinct !DILexicalBlock(scope: !190, file: !1, line: 534, column: 6)
!956 = !DILocation(line: 534, column: 14, scope: !955)
!957 = !DILocation(line: 534, column: 19, scope: !955)
!958 = !DILocation(line: 534, column: 23, scope: !959)
!959 = !DILexicalBlockFile(scope: !955, file: !1, discriminator: 1)
!960 = !DILocation(line: 534, column: 34, scope: !959)
!961 = !DILocation(line: 534, column: 42, scope: !959)
!962 = !DILocation(line: 534, column: 31, scope: !959)
!963 = !DILocation(line: 534, column: 48, scope: !959)
!964 = !DILocation(line: 534, column: 6, scope: !959)
!965 = !DILocation(line: 534, column: 54, scope: !966)
!966 = !DILexicalBlockFile(scope: !955, file: !1, discriminator: 2)
!967 = !DILocation(line: 535, column: 31, scope: !190)
!968 = !DILocation(line: 535, column: 14, scope: !190)
!969 = !DILocation(line: 535, column: 51, scope: !190)
!970 = !DILocation(line: 535, column: 57, scope: !190)
!971 = !DILocation(line: 535, column: 9, scope: !190)
!972 = !DILocation(line: 535, column: 2, scope: !190)
!973 = !DILocation(line: 536, column: 1, scope: !190)
!974 = !DILocalVariable(name: "hash_id", arg: 1, scope: !193, file: !1, line: 544, type: !30)
!975 = !DILocation(line: 544, column: 46, scope: !193)
!976 = !DILocalVariable(name: "info", scope: !193, file: !1, line: 546, type: !188)
!977 = !DILocation(line: 546, column: 20, scope: !193)
!978 = !DILocation(line: 546, column: 44, scope: !193)
!979 = !DILocation(line: 546, column: 27, scope: !193)
!980 = !DILocation(line: 547, column: 15, scope: !193)
!981 = !DILocation(line: 547, column: 23, scope: !982)
!982 = !DILexicalBlockFile(scope: !193, file: !1, discriminator: 1)
!983 = !DILocation(line: 547, column: 29, scope: !982)
!984 = !DILocation(line: 547, column: 35, scope: !982)
!985 = !DILocation(line: 548, column: 3, scope: !193)
!986 = !DILocation(line: 547, column: 23, scope: !987)
!987 = !DILexicalBlockFile(scope: !193, file: !1, discriminator: 2)
!988 = !DILocation(line: 548, column: 38, scope: !982)
!989 = !DILocation(line: 548, column: 44, scope: !982)
!990 = !DILocation(line: 548, column: 56, scope: !982)
!991 = !DILocation(line: 547, column: 23, scope: !992)
!992 = !DILexicalBlockFile(scope: !193, file: !1, discriminator: 3)
!993 = !DILocation(line: 547, column: 23, scope: !994)
!994 = !DILexicalBlockFile(scope: !193, file: !1, discriminator: 4)
!995 = !DILocation(line: 547, column: 15, scope: !994)
!996 = !DILocation(line: 547, column: 15, scope: !997)
!997 = !DILexicalBlockFile(scope: !193, file: !1, discriminator: 5)
!998 = !DILocation(line: 547, column: 15, scope: !999)
!999 = !DILexicalBlockFile(scope: !193, file: !1, discriminator: 6)
!1000 = !DILocation(line: 547, column: 9, scope: !999)
!1001 = !DILocation(line: 547, column: 2, scope: !999)
!1002 = !DILocalVariable(name: "hash_id", arg: 1, scope: !194, file: !1, line: 557, type: !30)
!1003 = !DILocation(line: 557, column: 47, scope: !194)
!1004 = !DILocalVariable(name: "info", scope: !194, file: !1, line: 559, type: !188)
!1005 = !DILocation(line: 559, column: 20, scope: !194)
!1006 = !DILocation(line: 559, column: 44, scope: !194)
!1007 = !DILocation(line: 559, column: 27, scope: !194)
!1008 = !DILocation(line: 560, column: 10, scope: !194)
!1009 = !DILocation(line: 560, column: 17, scope: !1010)
!1010 = !DILexicalBlockFile(scope: !194, file: !1, discriminator: 1)
!1011 = !DILocation(line: 560, column: 23, scope: !1010)
!1012 = !DILocation(line: 560, column: 10, scope: !1010)
!1013 = !DILocation(line: 560, column: 10, scope: !1014)
!1014 = !DILexicalBlockFile(scope: !194, file: !1, discriminator: 2)
!1015 = !DILocation(line: 560, column: 10, scope: !1016)
!1016 = !DILexicalBlockFile(scope: !194, file: !1, discriminator: 3)
!1017 = !DILocation(line: 560, column: 2, scope: !1016)
!1018 = !DILocalVariable(name: "hash_id", arg: 1, scope: !197, file: !1, line: 571, type: !30)
!1019 = !DILocation(line: 571, column: 54, scope: !197)
!1020 = !DILocalVariable(name: "info", scope: !197, file: !1, line: 573, type: !188)
!1021 = !DILocation(line: 573, column: 20, scope: !197)
!1022 = !DILocation(line: 573, column: 44, scope: !197)
!1023 = !DILocation(line: 573, column: 27, scope: !197)
!1024 = !DILocation(line: 574, column: 10, scope: !197)
!1025 = !DILocation(line: 574, column: 17, scope: !1026)
!1026 = !DILexicalBlockFile(scope: !197, file: !1, discriminator: 1)
!1027 = !DILocation(line: 574, column: 23, scope: !1026)
!1028 = !DILocation(line: 574, column: 10, scope: !1026)
!1029 = !DILocation(line: 574, column: 10, scope: !1030)
!1030 = !DILexicalBlockFile(scope: !197, file: !1, discriminator: 2)
!1031 = !DILocation(line: 574, column: 10, scope: !1032)
!1032 = !DILexicalBlockFile(scope: !197, file: !1, discriminator: 3)
!1033 = !DILocation(line: 574, column: 2, scope: !1032)
