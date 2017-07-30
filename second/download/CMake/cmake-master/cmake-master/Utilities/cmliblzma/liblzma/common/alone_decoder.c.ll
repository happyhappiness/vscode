; ModuleID = '/data/download/cmake/cmake-master/Utilities/cmliblzma/liblzma/common/alone_decoder.c'
target datalayout = "e-m:e-i64:64-f80:128-n8:16:32:64-S128"
target triple = "x86_64-unknown-linux-gnu"

%struct.lzma_next_coder_s = type { %struct.lzma_coder_s*, i64, i64, i32 (%struct.lzma_coder_s*, %struct.lzma_allocator*, i8*, i64*, i64, i8*, i64*, i64, i32)*, void (%struct.lzma_coder_s*, %struct.lzma_allocator*)*, i32 (%struct.lzma_coder_s*)*, i32 (%struct.lzma_coder_s*, i64*, i64*, i64)*, i32 (%struct.lzma_coder_s*, %struct.lzma_allocator*, %struct.lzma_filter*, %struct.lzma_filter*)* }
%struct.lzma_coder_s = type { %struct.lzma_next_coder_s, i32, i8, i64, i64, i64, i64, %struct.lzma_options_lzma }
%struct.lzma_options_lzma = type { i32, i8*, i32, i32, i32, i32, i32, i32, i32, i32, i32, i32, i32, i32, i32, i32, i32, i32, i32, i32, i32, i32, i8*, i8* }
%struct.lzma_allocator = type { i8* (i8*, i64, i64)*, void (i8*, i8*)*, i8* }
%struct.lzma_filter = type { i64, i8* }
%struct.lzma_filter_info_s = type { i64, i32 (%struct.lzma_next_coder_s*, %struct.lzma_allocator*, %struct.lzma_filter_info_s*)*, i8* }
%struct.lzma_stream = type { i8*, i64, i64, i8*, i64, i64, %struct.lzma_allocator*, %struct.lzma_internal_s*, i8*, i8*, i8*, i8*, i64, i64, i64, i64, i32, i32 }
%struct.lzma_internal_s = type { %struct.lzma_next_coder_s, i32, i64, [4 x i8], i8 }

@LZMA_NEXT_CODER_INIT = internal constant %struct.lzma_next_coder_s { %struct.lzma_coder_s* null, i64 -1, i64 0, i32 (%struct.lzma_coder_s*, %struct.lzma_allocator*, i8*, i64*, i64, i8*, i64*, i64, i32)* null, void (%struct.lzma_coder_s*, %struct.lzma_allocator*)* null, i32 (%struct.lzma_coder_s*)* null, i32 (%struct.lzma_coder_s*, i64*, i64*, i64)* null, i32 (%struct.lzma_coder_s*, %struct.lzma_allocator*, %struct.lzma_filter*, %struct.lzma_filter*)* null }, align 8

; Function Attrs: nounwind uwtable
define i32 @lzma_alone_decoder_init(%struct.lzma_next_coder_s* %next, %struct.lzma_allocator* %allocator, i64 %memlimit, i1 zeroext %picky) #0 !dbg !192 {
entry:
  %retval = alloca i32, align 4
  %next.addr = alloca %struct.lzma_next_coder_s*, align 8
  %allocator.addr = alloca %struct.lzma_allocator*, align 8
  %memlimit.addr = alloca i64, align 8
  %picky.addr = alloca i8, align 1
  store %struct.lzma_next_coder_s* %next, %struct.lzma_next_coder_s** %next.addr, align 8
  call void @llvm.dbg.declare(metadata %struct.lzma_next_coder_s** %next.addr, metadata !233, metadata !234), !dbg !235
  store %struct.lzma_allocator* %allocator, %struct.lzma_allocator** %allocator.addr, align 8
  call void @llvm.dbg.declare(metadata %struct.lzma_allocator** %allocator.addr, metadata !236, metadata !234), !dbg !237
  store i64 %memlimit, i64* %memlimit.addr, align 8
  call void @llvm.dbg.declare(metadata i64* %memlimit.addr, metadata !238, metadata !234), !dbg !239
  %frombool = zext i1 %picky to i8
  store i8 %frombool, i8* %picky.addr, align 1
  call void @llvm.dbg.declare(metadata i8* %picky.addr, metadata !240, metadata !234), !dbg !241
  br label %do.body, !dbg !242

do.body:                                          ; preds = %entry
  %0 = load %struct.lzma_next_coder_s*, %struct.lzma_next_coder_s** %next.addr, align 8, !dbg !243
  %init = getelementptr inbounds %struct.lzma_next_coder_s, %struct.lzma_next_coder_s* %0, i32 0, i32 2, !dbg !243
  %1 = load i64, i64* %init, align 8, !dbg !243
  %cmp = icmp ne i64 ptrtoint (i32 (%struct.lzma_next_coder_s*, %struct.lzma_allocator*, i64, i1)* @lzma_alone_decoder_init to i64), %1, !dbg !243
  br i1 %cmp, label %if.then, label %if.end, !dbg !243

if.then:                                          ; preds = %do.body
  %2 = load %struct.lzma_next_coder_s*, %struct.lzma_next_coder_s** %next.addr, align 8, !dbg !247
  %3 = load %struct.lzma_allocator*, %struct.lzma_allocator** %allocator.addr, align 8, !dbg !247
  call void @lzma_next_end(%struct.lzma_next_coder_s* %2, %struct.lzma_allocator* %3), !dbg !247
  br label %if.end, !dbg !247

if.end:                                           ; preds = %if.then, %do.body
  %4 = load %struct.lzma_next_coder_s*, %struct.lzma_next_coder_s** %next.addr, align 8, !dbg !249
  %init1 = getelementptr inbounds %struct.lzma_next_coder_s, %struct.lzma_next_coder_s* %4, i32 0, i32 2, !dbg !249
  store i64 ptrtoint (i32 (%struct.lzma_next_coder_s*, %struct.lzma_allocator*, i64, i1)* @lzma_alone_decoder_init to i64), i64* %init1, align 8, !dbg !249
  br label %do.end, !dbg !249

do.end:                                           ; preds = %if.end
  %5 = load i64, i64* %memlimit.addr, align 8, !dbg !251
  %cmp2 = icmp eq i64 %5, 0, !dbg !253
  br i1 %cmp2, label %if.then3, label %if.end4, !dbg !254

if.then3:                                         ; preds = %do.end
  store i32 11, i32* %retval, align 4, !dbg !255
  br label %return, !dbg !255

if.end4:                                          ; preds = %do.end
  %6 = load %struct.lzma_next_coder_s*, %struct.lzma_next_coder_s** %next.addr, align 8, !dbg !256
  %coder = getelementptr inbounds %struct.lzma_next_coder_s, %struct.lzma_next_coder_s* %6, i32 0, i32 0, !dbg !258
  %7 = load %struct.lzma_coder_s*, %struct.lzma_coder_s** %coder, align 8, !dbg !258
  %cmp5 = icmp eq %struct.lzma_coder_s* %7, null, !dbg !259
  br i1 %cmp5, label %if.then6, label %if.end14, !dbg !260

if.then6:                                         ; preds = %if.end4
  %8 = load %struct.lzma_allocator*, %struct.lzma_allocator** %allocator.addr, align 8, !dbg !261
  %call = call noalias i8* @lzma_alloc(i64 216, %struct.lzma_allocator* %8), !dbg !263
  %9 = bitcast i8* %call to %struct.lzma_coder_s*, !dbg !263
  %10 = load %struct.lzma_next_coder_s*, %struct.lzma_next_coder_s** %next.addr, align 8, !dbg !264
  %coder7 = getelementptr inbounds %struct.lzma_next_coder_s, %struct.lzma_next_coder_s* %10, i32 0, i32 0, !dbg !265
  store %struct.lzma_coder_s* %9, %struct.lzma_coder_s** %coder7, align 8, !dbg !266
  %11 = load %struct.lzma_next_coder_s*, %struct.lzma_next_coder_s** %next.addr, align 8, !dbg !267
  %coder8 = getelementptr inbounds %struct.lzma_next_coder_s, %struct.lzma_next_coder_s* %11, i32 0, i32 0, !dbg !269
  %12 = load %struct.lzma_coder_s*, %struct.lzma_coder_s** %coder8, align 8, !dbg !269
  %cmp9 = icmp eq %struct.lzma_coder_s* %12, null, !dbg !270
  br i1 %cmp9, label %if.then10, label %if.end11, !dbg !271

if.then10:                                        ; preds = %if.then6
  store i32 5, i32* %retval, align 4, !dbg !272
  br label %return, !dbg !272

if.end11:                                         ; preds = %if.then6
  %13 = load %struct.lzma_next_coder_s*, %struct.lzma_next_coder_s** %next.addr, align 8, !dbg !273
  %code = getelementptr inbounds %struct.lzma_next_coder_s, %struct.lzma_next_coder_s* %13, i32 0, i32 3, !dbg !274
  store i32 (%struct.lzma_coder_s*, %struct.lzma_allocator*, i8*, i64*, i64, i8*, i64*, i64, i32)* @alone_decode, i32 (%struct.lzma_coder_s*, %struct.lzma_allocator*, i8*, i64*, i64, i8*, i64*, i64, i32)** %code, align 8, !dbg !275
  %14 = load %struct.lzma_next_coder_s*, %struct.lzma_next_coder_s** %next.addr, align 8, !dbg !276
  %end = getelementptr inbounds %struct.lzma_next_coder_s, %struct.lzma_next_coder_s* %14, i32 0, i32 4, !dbg !277
  store void (%struct.lzma_coder_s*, %struct.lzma_allocator*)* @alone_decoder_end, void (%struct.lzma_coder_s*, %struct.lzma_allocator*)** %end, align 8, !dbg !278
  %15 = load %struct.lzma_next_coder_s*, %struct.lzma_next_coder_s** %next.addr, align 8, !dbg !279
  %memconfig = getelementptr inbounds %struct.lzma_next_coder_s, %struct.lzma_next_coder_s* %15, i32 0, i32 6, !dbg !280
  store i32 (%struct.lzma_coder_s*, i64*, i64*, i64)* @alone_decoder_memconfig, i32 (%struct.lzma_coder_s*, i64*, i64*, i64)** %memconfig, align 8, !dbg !281
  %16 = load %struct.lzma_next_coder_s*, %struct.lzma_next_coder_s** %next.addr, align 8, !dbg !282
  %coder12 = getelementptr inbounds %struct.lzma_next_coder_s, %struct.lzma_next_coder_s* %16, i32 0, i32 0, !dbg !283
  %17 = load %struct.lzma_coder_s*, %struct.lzma_coder_s** %coder12, align 8, !dbg !283
  %next13 = getelementptr inbounds %struct.lzma_coder_s, %struct.lzma_coder_s* %17, i32 0, i32 0, !dbg !284
  %18 = bitcast %struct.lzma_next_coder_s* %next13 to i8*, !dbg !285
  call void @llvm.memcpy.p0i8.p0i8.i64(i8* %18, i8* bitcast (%struct.lzma_next_coder_s* @LZMA_NEXT_CODER_INIT to i8*), i64 64, i32 8, i1 false), !dbg !285
  br label %if.end14, !dbg !286

if.end14:                                         ; preds = %if.end11, %if.end4
  %19 = load %struct.lzma_next_coder_s*, %struct.lzma_next_coder_s** %next.addr, align 8, !dbg !287
  %coder15 = getelementptr inbounds %struct.lzma_next_coder_s, %struct.lzma_next_coder_s* %19, i32 0, i32 0, !dbg !288
  %20 = load %struct.lzma_coder_s*, %struct.lzma_coder_s** %coder15, align 8, !dbg !288
  %sequence = getelementptr inbounds %struct.lzma_coder_s, %struct.lzma_coder_s* %20, i32 0, i32 1, !dbg !289
  store i32 0, i32* %sequence, align 8, !dbg !290
  %21 = load i8, i8* %picky.addr, align 1, !dbg !291
  %tobool = trunc i8 %21 to i1, !dbg !291
  %22 = load %struct.lzma_next_coder_s*, %struct.lzma_next_coder_s** %next.addr, align 8, !dbg !292
  %coder16 = getelementptr inbounds %struct.lzma_next_coder_s, %struct.lzma_next_coder_s* %22, i32 0, i32 0, !dbg !293
  %23 = load %struct.lzma_coder_s*, %struct.lzma_coder_s** %coder16, align 8, !dbg !293
  %picky17 = getelementptr inbounds %struct.lzma_coder_s, %struct.lzma_coder_s* %23, i32 0, i32 2, !dbg !294
  %frombool18 = zext i1 %tobool to i8, !dbg !295
  store i8 %frombool18, i8* %picky17, align 4, !dbg !295
  %24 = load %struct.lzma_next_coder_s*, %struct.lzma_next_coder_s** %next.addr, align 8, !dbg !296
  %coder19 = getelementptr inbounds %struct.lzma_next_coder_s, %struct.lzma_next_coder_s* %24, i32 0, i32 0, !dbg !297
  %25 = load %struct.lzma_coder_s*, %struct.lzma_coder_s** %coder19, align 8, !dbg !297
  %pos = getelementptr inbounds %struct.lzma_coder_s, %struct.lzma_coder_s* %25, i32 0, i32 3, !dbg !298
  store i64 0, i64* %pos, align 8, !dbg !299
  %26 = load %struct.lzma_next_coder_s*, %struct.lzma_next_coder_s** %next.addr, align 8, !dbg !300
  %coder20 = getelementptr inbounds %struct.lzma_next_coder_s, %struct.lzma_next_coder_s* %26, i32 0, i32 0, !dbg !301
  %27 = load %struct.lzma_coder_s*, %struct.lzma_coder_s** %coder20, align 8, !dbg !301
  %options = getelementptr inbounds %struct.lzma_coder_s, %struct.lzma_coder_s* %27, i32 0, i32 7, !dbg !302
  %dict_size = getelementptr inbounds %struct.lzma_options_lzma, %struct.lzma_options_lzma* %options, i32 0, i32 0, !dbg !303
  store i32 0, i32* %dict_size, align 8, !dbg !304
  %28 = load %struct.lzma_next_coder_s*, %struct.lzma_next_coder_s** %next.addr, align 8, !dbg !305
  %coder21 = getelementptr inbounds %struct.lzma_next_coder_s, %struct.lzma_next_coder_s* %28, i32 0, i32 0, !dbg !306
  %29 = load %struct.lzma_coder_s*, %struct.lzma_coder_s** %coder21, align 8, !dbg !306
  %options22 = getelementptr inbounds %struct.lzma_coder_s, %struct.lzma_coder_s* %29, i32 0, i32 7, !dbg !307
  %preset_dict = getelementptr inbounds %struct.lzma_options_lzma, %struct.lzma_options_lzma* %options22, i32 0, i32 1, !dbg !308
  store i8* null, i8** %preset_dict, align 8, !dbg !309
  %30 = load %struct.lzma_next_coder_s*, %struct.lzma_next_coder_s** %next.addr, align 8, !dbg !310
  %coder23 = getelementptr inbounds %struct.lzma_next_coder_s, %struct.lzma_next_coder_s* %30, i32 0, i32 0, !dbg !311
  %31 = load %struct.lzma_coder_s*, %struct.lzma_coder_s** %coder23, align 8, !dbg !311
  %options24 = getelementptr inbounds %struct.lzma_coder_s, %struct.lzma_coder_s* %31, i32 0, i32 7, !dbg !312
  %preset_dict_size = getelementptr inbounds %struct.lzma_options_lzma, %struct.lzma_options_lzma* %options24, i32 0, i32 2, !dbg !313
  store i32 0, i32* %preset_dict_size, align 8, !dbg !314
  %32 = load %struct.lzma_next_coder_s*, %struct.lzma_next_coder_s** %next.addr, align 8, !dbg !315
  %coder25 = getelementptr inbounds %struct.lzma_next_coder_s, %struct.lzma_next_coder_s* %32, i32 0, i32 0, !dbg !316
  %33 = load %struct.lzma_coder_s*, %struct.lzma_coder_s** %coder25, align 8, !dbg !316
  %uncompressed_size = getelementptr inbounds %struct.lzma_coder_s, %struct.lzma_coder_s* %33, i32 0, i32 4, !dbg !317
  store i64 0, i64* %uncompressed_size, align 8, !dbg !318
  %34 = load i64, i64* %memlimit.addr, align 8, !dbg !319
  %35 = load %struct.lzma_next_coder_s*, %struct.lzma_next_coder_s** %next.addr, align 8, !dbg !320
  %coder26 = getelementptr inbounds %struct.lzma_next_coder_s, %struct.lzma_next_coder_s* %35, i32 0, i32 0, !dbg !321
  %36 = load %struct.lzma_coder_s*, %struct.lzma_coder_s** %coder26, align 8, !dbg !321
  %memlimit27 = getelementptr inbounds %struct.lzma_coder_s, %struct.lzma_coder_s* %36, i32 0, i32 5, !dbg !322
  store i64 %34, i64* %memlimit27, align 8, !dbg !323
  %37 = load %struct.lzma_next_coder_s*, %struct.lzma_next_coder_s** %next.addr, align 8, !dbg !324
  %coder28 = getelementptr inbounds %struct.lzma_next_coder_s, %struct.lzma_next_coder_s* %37, i32 0, i32 0, !dbg !325
  %38 = load %struct.lzma_coder_s*, %struct.lzma_coder_s** %coder28, align 8, !dbg !325
  %memusage = getelementptr inbounds %struct.lzma_coder_s, %struct.lzma_coder_s* %38, i32 0, i32 6, !dbg !326
  store i64 32768, i64* %memusage, align 8, !dbg !327
  store i32 0, i32* %retval, align 4, !dbg !328
  br label %return, !dbg !328

return:                                           ; preds = %if.end14, %if.then10, %if.then3
  %39 = load i32, i32* %retval, align 4, !dbg !329
  ret i32 %39, !dbg !329
}

; Function Attrs: nounwind readnone
declare void @llvm.dbg.declare(metadata, metadata, metadata) #1

declare void @lzma_next_end(%struct.lzma_next_coder_s*, %struct.lzma_allocator*) #2

declare noalias i8* @lzma_alloc(i64, %struct.lzma_allocator*) #2

; Function Attrs: nounwind uwtable
define internal i32 @alone_decode(%struct.lzma_coder_s* %coder, %struct.lzma_allocator* %allocator, i8* noalias %in, i64* noalias %in_pos, i64 %in_size, i8* noalias %out, i64* noalias %out_pos, i64 %out_size, i32 %action) #0 !dbg !224 {
entry:
  %retval = alloca i32, align 4
  %coder.addr = alloca %struct.lzma_coder_s*, align 8
  %allocator.addr = alloca %struct.lzma_allocator*, align 8
  %in.addr = alloca i8*, align 8
  %in_pos.addr = alloca i64*, align 8
  %in_size.addr = alloca i64, align 8
  %out.addr = alloca i8*, align 8
  %out_pos.addr = alloca i64*, align 8
  %out_size.addr = alloca i64, align 8
  %action.addr = alloca i32, align 4
  %d = alloca i32, align 4
  %ret = alloca i32, align 4
  %filters = alloca [2 x %struct.lzma_filter_info_s], align 16
  store %struct.lzma_coder_s* %coder, %struct.lzma_coder_s** %coder.addr, align 8
  call void @llvm.dbg.declare(metadata %struct.lzma_coder_s** %coder.addr, metadata !330, metadata !234), !dbg !331
  store %struct.lzma_allocator* %allocator, %struct.lzma_allocator** %allocator.addr, align 8
  call void @llvm.dbg.declare(metadata %struct.lzma_allocator** %allocator.addr, metadata !332, metadata !234), !dbg !333
  store i8* %in, i8** %in.addr, align 8
  call void @llvm.dbg.declare(metadata i8** %in.addr, metadata !334, metadata !234), !dbg !335
  store i64* %in_pos, i64** %in_pos.addr, align 8
  call void @llvm.dbg.declare(metadata i64** %in_pos.addr, metadata !336, metadata !234), !dbg !337
  store i64 %in_size, i64* %in_size.addr, align 8
  call void @llvm.dbg.declare(metadata i64* %in_size.addr, metadata !338, metadata !234), !dbg !339
  store i8* %out, i8** %out.addr, align 8
  call void @llvm.dbg.declare(metadata i8** %out.addr, metadata !340, metadata !234), !dbg !341
  store i64* %out_pos, i64** %out_pos.addr, align 8
  call void @llvm.dbg.declare(metadata i64** %out_pos.addr, metadata !342, metadata !234), !dbg !343
  store i64 %out_size, i64* %out_size.addr, align 8
  call void @llvm.dbg.declare(metadata i64* %out_size.addr, metadata !344, metadata !234), !dbg !345
  store i32 %action, i32* %action.addr, align 4
  call void @llvm.dbg.declare(metadata i32* %action.addr, metadata !346, metadata !234), !dbg !347
  br label %while.cond, !dbg !348

while.cond:                                       ; preds = %sw.epilog, %entry
  %0 = load i64*, i64** %out_pos.addr, align 8, !dbg !349
  %1 = load i64, i64* %0, align 8, !dbg !351
  %2 = load i64, i64* %out_size.addr, align 8, !dbg !352
  %cmp = icmp ult i64 %1, %2, !dbg !353
  br i1 %cmp, label %land.rhs, label %land.end, !dbg !354

land.rhs:                                         ; preds = %while.cond
  %3 = load %struct.lzma_coder_s*, %struct.lzma_coder_s** %coder.addr, align 8, !dbg !355
  %sequence = getelementptr inbounds %struct.lzma_coder_s, %struct.lzma_coder_s* %3, i32 0, i32 1, !dbg !356
  %4 = load i32, i32* %sequence, align 8, !dbg !356
  %cmp1 = icmp eq i32 %4, 4, !dbg !357
  br i1 %cmp1, label %lor.end, label %lor.rhs, !dbg !358

lor.rhs:                                          ; preds = %land.rhs
  %5 = load i64*, i64** %in_pos.addr, align 8, !dbg !359
  %6 = load i64, i64* %5, align 8, !dbg !361
  %7 = load i64, i64* %in_size.addr, align 8, !dbg !362
  %cmp2 = icmp ult i64 %6, %7, !dbg !363
  br label %lor.end, !dbg !364

lor.end:                                          ; preds = %lor.rhs, %land.rhs
  %8 = phi i1 [ true, %land.rhs ], [ %cmp2, %lor.rhs ]
  br label %land.end

land.end:                                         ; preds = %lor.end, %while.cond
  %9 = phi i1 [ false, %while.cond ], [ %8, %lor.end ]
  br i1 %9, label %while.body, label %while.end, !dbg !365

while.body:                                       ; preds = %land.end
  %10 = load %struct.lzma_coder_s*, %struct.lzma_coder_s** %coder.addr, align 8, !dbg !366
  %sequence3 = getelementptr inbounds %struct.lzma_coder_s, %struct.lzma_coder_s* %10, i32 0, i32 1, !dbg !367
  %11 = load i32, i32* %sequence3, align 8, !dbg !367
  switch i32 %11, label %sw.default [
    i32 0, label %sw.bb
    i32 1, label %sw.bb5
    i32 2, label %sw.bb44
    i32 3, label %sw.bb75
    i32 4, label %sw.bb95
  ], !dbg !368

sw.bb:                                            ; preds = %while.body
  %12 = load %struct.lzma_coder_s*, %struct.lzma_coder_s** %coder.addr, align 8, !dbg !369
  %options = getelementptr inbounds %struct.lzma_coder_s, %struct.lzma_coder_s* %12, i32 0, i32 7, !dbg !372
  %13 = load i64*, i64** %in_pos.addr, align 8, !dbg !373
  %14 = load i64, i64* %13, align 8, !dbg !374
  %15 = load i8*, i8** %in.addr, align 8, !dbg !375
  %arrayidx = getelementptr inbounds i8, i8* %15, i64 %14, !dbg !375
  %16 = load i8, i8* %arrayidx, align 1, !dbg !375
  %call = call zeroext i1 @lzma_lzma_lclppb_decode(%struct.lzma_options_lzma* %options, i8 zeroext %16), !dbg !376
  br i1 %call, label %if.then, label %if.end, !dbg !377

if.then:                                          ; preds = %sw.bb
  store i32 7, i32* %retval, align 4, !dbg !378
  br label %return, !dbg !378

if.end:                                           ; preds = %sw.bb
  %17 = load %struct.lzma_coder_s*, %struct.lzma_coder_s** %coder.addr, align 8, !dbg !379
  %sequence4 = getelementptr inbounds %struct.lzma_coder_s, %struct.lzma_coder_s* %17, i32 0, i32 1, !dbg !380
  store i32 1, i32* %sequence4, align 8, !dbg !381
  %18 = load i64*, i64** %in_pos.addr, align 8, !dbg !382
  %19 = load i64, i64* %18, align 8, !dbg !383
  %inc = add i64 %19, 1, !dbg !383
  store i64 %inc, i64* %18, align 8, !dbg !383
  br label %sw.epilog, !dbg !384

sw.bb5:                                           ; preds = %while.body
  %20 = load i64*, i64** %in_pos.addr, align 8, !dbg !385
  %21 = load i64, i64* %20, align 8, !dbg !386
  %22 = load i8*, i8** %in.addr, align 8, !dbg !387
  %arrayidx6 = getelementptr inbounds i8, i8* %22, i64 %21, !dbg !387
  %23 = load i8, i8* %arrayidx6, align 1, !dbg !387
  %conv = zext i8 %23 to i64, !dbg !388
  %24 = load %struct.lzma_coder_s*, %struct.lzma_coder_s** %coder.addr, align 8, !dbg !389
  %pos = getelementptr inbounds %struct.lzma_coder_s, %struct.lzma_coder_s* %24, i32 0, i32 3, !dbg !390
  %25 = load i64, i64* %pos, align 8, !dbg !390
  %mul = mul i64 %25, 8, !dbg !391
  %shl = shl i64 %conv, %mul, !dbg !392
  %26 = load %struct.lzma_coder_s*, %struct.lzma_coder_s** %coder.addr, align 8, !dbg !393
  %options7 = getelementptr inbounds %struct.lzma_coder_s, %struct.lzma_coder_s* %26, i32 0, i32 7, !dbg !394
  %dict_size = getelementptr inbounds %struct.lzma_options_lzma, %struct.lzma_options_lzma* %options7, i32 0, i32 0, !dbg !395
  %27 = load i32, i32* %dict_size, align 8, !dbg !396
  %conv8 = zext i32 %27 to i64, !dbg !396
  %or = or i64 %conv8, %shl, !dbg !396
  %conv9 = trunc i64 %or to i32, !dbg !396
  store i32 %conv9, i32* %dict_size, align 8, !dbg !396
  %28 = load %struct.lzma_coder_s*, %struct.lzma_coder_s** %coder.addr, align 8, !dbg !397
  %pos10 = getelementptr inbounds %struct.lzma_coder_s, %struct.lzma_coder_s* %28, i32 0, i32 3, !dbg !399
  %29 = load i64, i64* %pos10, align 8, !dbg !400
  %inc11 = add i64 %29, 1, !dbg !400
  store i64 %inc11, i64* %pos10, align 8, !dbg !400
  %cmp12 = icmp eq i64 %inc11, 4, !dbg !401
  br i1 %cmp12, label %if.then14, label %if.end42, !dbg !402

if.then14:                                        ; preds = %sw.bb5
  %30 = load %struct.lzma_coder_s*, %struct.lzma_coder_s** %coder.addr, align 8, !dbg !403
  %picky = getelementptr inbounds %struct.lzma_coder_s, %struct.lzma_coder_s* %30, i32 0, i32 2, !dbg !406
  %31 = load i8, i8* %picky, align 4, !dbg !406
  %tobool = trunc i8 %31 to i1, !dbg !406
  br i1 %tobool, label %land.lhs.true, label %if.end39, !dbg !407

land.lhs.true:                                    ; preds = %if.then14
  %32 = load %struct.lzma_coder_s*, %struct.lzma_coder_s** %coder.addr, align 8, !dbg !408
  %options16 = getelementptr inbounds %struct.lzma_coder_s, %struct.lzma_coder_s* %32, i32 0, i32 7, !dbg !410
  %dict_size17 = getelementptr inbounds %struct.lzma_options_lzma, %struct.lzma_options_lzma* %options16, i32 0, i32 0, !dbg !411
  %33 = load i32, i32* %dict_size17, align 8, !dbg !411
  %cmp18 = icmp ne i32 %33, -1, !dbg !412
  br i1 %cmp18, label %if.then20, label %if.end39, !dbg !413

if.then20:                                        ; preds = %land.lhs.true
  call void @llvm.dbg.declare(metadata i32* %d, metadata !414, metadata !234), !dbg !416
  %34 = load %struct.lzma_coder_s*, %struct.lzma_coder_s** %coder.addr, align 8, !dbg !417
  %options21 = getelementptr inbounds %struct.lzma_coder_s, %struct.lzma_coder_s* %34, i32 0, i32 7, !dbg !418
  %dict_size22 = getelementptr inbounds %struct.lzma_options_lzma, %struct.lzma_options_lzma* %options21, i32 0, i32 0, !dbg !419
  %35 = load i32, i32* %dict_size22, align 8, !dbg !419
  %sub = sub i32 %35, 1, !dbg !420
  store i32 %sub, i32* %d, align 4, !dbg !416
  %36 = load i32, i32* %d, align 4, !dbg !421
  %shr = lshr i32 %36, 2, !dbg !422
  %37 = load i32, i32* %d, align 4, !dbg !423
  %or23 = or i32 %37, %shr, !dbg !423
  store i32 %or23, i32* %d, align 4, !dbg !423
  %38 = load i32, i32* %d, align 4, !dbg !424
  %shr24 = lshr i32 %38, 3, !dbg !425
  %39 = load i32, i32* %d, align 4, !dbg !426
  %or25 = or i32 %39, %shr24, !dbg !426
  store i32 %or25, i32* %d, align 4, !dbg !426
  %40 = load i32, i32* %d, align 4, !dbg !427
  %shr26 = lshr i32 %40, 4, !dbg !428
  %41 = load i32, i32* %d, align 4, !dbg !429
  %or27 = or i32 %41, %shr26, !dbg !429
  store i32 %or27, i32* %d, align 4, !dbg !429
  %42 = load i32, i32* %d, align 4, !dbg !430
  %shr28 = lshr i32 %42, 8, !dbg !431
  %43 = load i32, i32* %d, align 4, !dbg !432
  %or29 = or i32 %43, %shr28, !dbg !432
  store i32 %or29, i32* %d, align 4, !dbg !432
  %44 = load i32, i32* %d, align 4, !dbg !433
  %shr30 = lshr i32 %44, 16, !dbg !434
  %45 = load i32, i32* %d, align 4, !dbg !435
  %or31 = or i32 %45, %shr30, !dbg !435
  store i32 %or31, i32* %d, align 4, !dbg !435
  %46 = load i32, i32* %d, align 4, !dbg !436
  %inc32 = add i32 %46, 1, !dbg !436
  store i32 %inc32, i32* %d, align 4, !dbg !436
  %47 = load i32, i32* %d, align 4, !dbg !437
  %48 = load %struct.lzma_coder_s*, %struct.lzma_coder_s** %coder.addr, align 8, !dbg !439
  %options33 = getelementptr inbounds %struct.lzma_coder_s, %struct.lzma_coder_s* %48, i32 0, i32 7, !dbg !440
  %dict_size34 = getelementptr inbounds %struct.lzma_options_lzma, %struct.lzma_options_lzma* %options33, i32 0, i32 0, !dbg !441
  %49 = load i32, i32* %dict_size34, align 8, !dbg !441
  %cmp35 = icmp ne i32 %47, %49, !dbg !442
  br i1 %cmp35, label %if.then37, label %if.end38, !dbg !443

if.then37:                                        ; preds = %if.then20
  store i32 7, i32* %retval, align 4, !dbg !444
  br label %return, !dbg !444

if.end38:                                         ; preds = %if.then20
  br label %if.end39, !dbg !445

if.end39:                                         ; preds = %if.end38, %land.lhs.true, %if.then14
  %50 = load %struct.lzma_coder_s*, %struct.lzma_coder_s** %coder.addr, align 8, !dbg !446
  %pos40 = getelementptr inbounds %struct.lzma_coder_s, %struct.lzma_coder_s* %50, i32 0, i32 3, !dbg !447
  store i64 0, i64* %pos40, align 8, !dbg !448
  %51 = load %struct.lzma_coder_s*, %struct.lzma_coder_s** %coder.addr, align 8, !dbg !449
  %sequence41 = getelementptr inbounds %struct.lzma_coder_s, %struct.lzma_coder_s* %51, i32 0, i32 1, !dbg !450
  store i32 2, i32* %sequence41, align 8, !dbg !451
  br label %if.end42, !dbg !452

if.end42:                                         ; preds = %if.end39, %sw.bb5
  %52 = load i64*, i64** %in_pos.addr, align 8, !dbg !453
  %53 = load i64, i64* %52, align 8, !dbg !454
  %inc43 = add i64 %53, 1, !dbg !454
  store i64 %inc43, i64* %52, align 8, !dbg !454
  br label %sw.epilog, !dbg !455

sw.bb44:                                          ; preds = %while.body
  %54 = load i64*, i64** %in_pos.addr, align 8, !dbg !456
  %55 = load i64, i64* %54, align 8, !dbg !457
  %56 = load i8*, i8** %in.addr, align 8, !dbg !458
  %arrayidx45 = getelementptr inbounds i8, i8* %56, i64 %55, !dbg !458
  %57 = load i8, i8* %arrayidx45, align 1, !dbg !458
  %conv46 = zext i8 %57 to i64, !dbg !459
  %58 = load %struct.lzma_coder_s*, %struct.lzma_coder_s** %coder.addr, align 8, !dbg !460
  %pos47 = getelementptr inbounds %struct.lzma_coder_s, %struct.lzma_coder_s* %58, i32 0, i32 3, !dbg !461
  %59 = load i64, i64* %pos47, align 8, !dbg !461
  %mul48 = mul i64 %59, 8, !dbg !462
  %shl49 = shl i64 %conv46, %mul48, !dbg !463
  %60 = load %struct.lzma_coder_s*, %struct.lzma_coder_s** %coder.addr, align 8, !dbg !464
  %uncompressed_size = getelementptr inbounds %struct.lzma_coder_s, %struct.lzma_coder_s* %60, i32 0, i32 4, !dbg !465
  %61 = load i64, i64* %uncompressed_size, align 8, !dbg !466
  %or50 = or i64 %61, %shl49, !dbg !466
  store i64 %or50, i64* %uncompressed_size, align 8, !dbg !466
  %62 = load i64*, i64** %in_pos.addr, align 8, !dbg !467
  %63 = load i64, i64* %62, align 8, !dbg !468
  %inc51 = add i64 %63, 1, !dbg !468
  store i64 %inc51, i64* %62, align 8, !dbg !468
  %64 = load %struct.lzma_coder_s*, %struct.lzma_coder_s** %coder.addr, align 8, !dbg !469
  %pos52 = getelementptr inbounds %struct.lzma_coder_s, %struct.lzma_coder_s* %64, i32 0, i32 3, !dbg !471
  %65 = load i64, i64* %pos52, align 8, !dbg !472
  %inc53 = add i64 %65, 1, !dbg !472
  store i64 %inc53, i64* %pos52, align 8, !dbg !472
  %cmp54 = icmp ult i64 %inc53, 8, !dbg !473
  br i1 %cmp54, label %if.then56, label %if.end57, !dbg !474

if.then56:                                        ; preds = %sw.bb44
  br label %sw.epilog, !dbg !475

if.end57:                                         ; preds = %sw.bb44
  %66 = load %struct.lzma_coder_s*, %struct.lzma_coder_s** %coder.addr, align 8, !dbg !476
  %picky58 = getelementptr inbounds %struct.lzma_coder_s, %struct.lzma_coder_s* %66, i32 0, i32 2, !dbg !478
  %67 = load i8, i8* %picky58, align 4, !dbg !478
  %tobool59 = trunc i8 %67 to i1, !dbg !478
  br i1 %tobool59, label %land.lhs.true61, label %if.end70, !dbg !479

land.lhs.true61:                                  ; preds = %if.end57
  %68 = load %struct.lzma_coder_s*, %struct.lzma_coder_s** %coder.addr, align 8, !dbg !480
  %uncompressed_size62 = getelementptr inbounds %struct.lzma_coder_s, %struct.lzma_coder_s* %68, i32 0, i32 4, !dbg !482
  %69 = load i64, i64* %uncompressed_size62, align 8, !dbg !482
  %cmp63 = icmp ne i64 %69, -1, !dbg !483
  br i1 %cmp63, label %land.lhs.true65, label %if.end70, !dbg !484

land.lhs.true65:                                  ; preds = %land.lhs.true61
  %70 = load %struct.lzma_coder_s*, %struct.lzma_coder_s** %coder.addr, align 8, !dbg !485
  %uncompressed_size66 = getelementptr inbounds %struct.lzma_coder_s, %struct.lzma_coder_s* %70, i32 0, i32 4, !dbg !486
  %71 = load i64, i64* %uncompressed_size66, align 8, !dbg !486
  %cmp67 = icmp uge i64 %71, 274877906944, !dbg !487
  br i1 %cmp67, label %if.then69, label %if.end70, !dbg !488

if.then69:                                        ; preds = %land.lhs.true65
  store i32 7, i32* %retval, align 4, !dbg !490
  br label %return, !dbg !490

if.end70:                                         ; preds = %land.lhs.true65, %land.lhs.true61, %if.end57
  %72 = load %struct.lzma_coder_s*, %struct.lzma_coder_s** %coder.addr, align 8, !dbg !491
  %options71 = getelementptr inbounds %struct.lzma_coder_s, %struct.lzma_coder_s* %72, i32 0, i32 7, !dbg !492
  %73 = bitcast %struct.lzma_options_lzma* %options71 to i8*, !dbg !493
  %call72 = call i64 @lzma_lzma_decoder_memusage(i8* %73), !dbg !494
  %add = add i64 %call72, 32768, !dbg !495
  %74 = load %struct.lzma_coder_s*, %struct.lzma_coder_s** %coder.addr, align 8, !dbg !496
  %memusage = getelementptr inbounds %struct.lzma_coder_s, %struct.lzma_coder_s* %74, i32 0, i32 6, !dbg !497
  store i64 %add, i64* %memusage, align 8, !dbg !498
  %75 = load %struct.lzma_coder_s*, %struct.lzma_coder_s** %coder.addr, align 8, !dbg !499
  %pos73 = getelementptr inbounds %struct.lzma_coder_s, %struct.lzma_coder_s* %75, i32 0, i32 3, !dbg !500
  store i64 0, i64* %pos73, align 8, !dbg !501
  %76 = load %struct.lzma_coder_s*, %struct.lzma_coder_s** %coder.addr, align 8, !dbg !502
  %sequence74 = getelementptr inbounds %struct.lzma_coder_s, %struct.lzma_coder_s* %76, i32 0, i32 1, !dbg !503
  store i32 3, i32* %sequence74, align 8, !dbg !504
  br label %sw.bb75, !dbg !502

sw.bb75:                                          ; preds = %while.body, %if.end70
  call void @llvm.dbg.declare(metadata i32* %ret, metadata !505, metadata !234), !dbg !507
  call void @llvm.dbg.declare(metadata [2 x %struct.lzma_filter_info_s]* %filters, metadata !508, metadata !234), !dbg !524
  %arrayinit.begin = getelementptr inbounds [2 x %struct.lzma_filter_info_s], [2 x %struct.lzma_filter_info_s]* %filters, i64 0, i64 0, !dbg !525
  %id = getelementptr inbounds %struct.lzma_filter_info_s, %struct.lzma_filter_info_s* %arrayinit.begin, i32 0, i32 0, !dbg !526
  store i64 0, i64* %id, align 8, !dbg !526
  %init = getelementptr inbounds %struct.lzma_filter_info_s, %struct.lzma_filter_info_s* %arrayinit.begin, i32 0, i32 1, !dbg !526
  store i32 (%struct.lzma_next_coder_s*, %struct.lzma_allocator*, %struct.lzma_filter_info_s*)* @lzma_lzma_decoder_init, i32 (%struct.lzma_next_coder_s*, %struct.lzma_allocator*, %struct.lzma_filter_info_s*)** %init, align 8, !dbg !526
  %options76 = getelementptr inbounds %struct.lzma_filter_info_s, %struct.lzma_filter_info_s* %arrayinit.begin, i32 0, i32 2, !dbg !526
  %77 = load %struct.lzma_coder_s*, %struct.lzma_coder_s** %coder.addr, align 8, !dbg !527
  %options77 = getelementptr inbounds %struct.lzma_coder_s, %struct.lzma_coder_s* %77, i32 0, i32 7, !dbg !528
  %78 = bitcast %struct.lzma_options_lzma* %options77 to i8*, !dbg !529
  store i8* %78, i8** %options76, align 8, !dbg !526
  %arrayinit.element = getelementptr inbounds %struct.lzma_filter_info_s, %struct.lzma_filter_info_s* %arrayinit.begin, i64 1, !dbg !525
  %id78 = getelementptr inbounds %struct.lzma_filter_info_s, %struct.lzma_filter_info_s* %arrayinit.element, i32 0, i32 0, !dbg !530
  store i64 0, i64* %id78, align 8, !dbg !530
  %init79 = getelementptr inbounds %struct.lzma_filter_info_s, %struct.lzma_filter_info_s* %arrayinit.element, i32 0, i32 1, !dbg !530
  store i32 (%struct.lzma_next_coder_s*, %struct.lzma_allocator*, %struct.lzma_filter_info_s*)* null, i32 (%struct.lzma_next_coder_s*, %struct.lzma_allocator*, %struct.lzma_filter_info_s*)** %init79, align 8, !dbg !530
  %options80 = getelementptr inbounds %struct.lzma_filter_info_s, %struct.lzma_filter_info_s* %arrayinit.element, i32 0, i32 2, !dbg !530
  store i8* null, i8** %options80, align 8, !dbg !530
  %79 = load %struct.lzma_coder_s*, %struct.lzma_coder_s** %coder.addr, align 8, !dbg !531
  %memusage81 = getelementptr inbounds %struct.lzma_coder_s, %struct.lzma_coder_s* %79, i32 0, i32 6, !dbg !533
  %80 = load i64, i64* %memusage81, align 8, !dbg !533
  %81 = load %struct.lzma_coder_s*, %struct.lzma_coder_s** %coder.addr, align 8, !dbg !534
  %memlimit = getelementptr inbounds %struct.lzma_coder_s, %struct.lzma_coder_s* %81, i32 0, i32 5, !dbg !535
  %82 = load i64, i64* %memlimit, align 8, !dbg !535
  %cmp82 = icmp ugt i64 %80, %82, !dbg !536
  br i1 %cmp82, label %if.then84, label %if.end85, !dbg !537

if.then84:                                        ; preds = %sw.bb75
  store i32 6, i32* %retval, align 4, !dbg !538
  br label %return, !dbg !538

if.end85:                                         ; preds = %sw.bb75
  %83 = load %struct.lzma_coder_s*, %struct.lzma_coder_s** %coder.addr, align 8, !dbg !539
  %next = getelementptr inbounds %struct.lzma_coder_s, %struct.lzma_coder_s* %83, i32 0, i32 0, !dbg !540
  %84 = load %struct.lzma_allocator*, %struct.lzma_allocator** %allocator.addr, align 8, !dbg !541
  %arraydecay = getelementptr inbounds [2 x %struct.lzma_filter_info_s], [2 x %struct.lzma_filter_info_s]* %filters, i32 0, i32 0, !dbg !542
  %call86 = call i32 @lzma_next_filter_init(%struct.lzma_next_coder_s* %next, %struct.lzma_allocator* %84, %struct.lzma_filter_info_s* %arraydecay), !dbg !543
  store i32 %call86, i32* %ret, align 4, !dbg !544
  %85 = load i32, i32* %ret, align 4, !dbg !545
  %cmp87 = icmp ne i32 %85, 0, !dbg !547
  br i1 %cmp87, label %if.then89, label %if.end90, !dbg !548

if.then89:                                        ; preds = %if.end85
  %86 = load i32, i32* %ret, align 4, !dbg !549
  store i32 %86, i32* %retval, align 4, !dbg !550
  br label %return, !dbg !550

if.end90:                                         ; preds = %if.end85
  %87 = load %struct.lzma_coder_s*, %struct.lzma_coder_s** %coder.addr, align 8, !dbg !551
  %next91 = getelementptr inbounds %struct.lzma_coder_s, %struct.lzma_coder_s* %87, i32 0, i32 0, !dbg !552
  %coder92 = getelementptr inbounds %struct.lzma_next_coder_s, %struct.lzma_next_coder_s* %next91, i32 0, i32 0, !dbg !553
  %88 = load %struct.lzma_coder_s*, %struct.lzma_coder_s** %coder92, align 8, !dbg !553
  %89 = load %struct.lzma_coder_s*, %struct.lzma_coder_s** %coder.addr, align 8, !dbg !554
  %uncompressed_size93 = getelementptr inbounds %struct.lzma_coder_s, %struct.lzma_coder_s* %89, i32 0, i32 4, !dbg !555
  %90 = load i64, i64* %uncompressed_size93, align 8, !dbg !555
  call void @lzma_lz_decoder_uncompressed(%struct.lzma_coder_s* %88, i64 %90), !dbg !556
  %91 = load %struct.lzma_coder_s*, %struct.lzma_coder_s** %coder.addr, align 8, !dbg !557
  %sequence94 = getelementptr inbounds %struct.lzma_coder_s, %struct.lzma_coder_s* %91, i32 0, i32 1, !dbg !558
  store i32 4, i32* %sequence94, align 8, !dbg !559
  br label %sw.epilog, !dbg !560

sw.bb95:                                          ; preds = %while.body
  %92 = load %struct.lzma_coder_s*, %struct.lzma_coder_s** %coder.addr, align 8, !dbg !561
  %next96 = getelementptr inbounds %struct.lzma_coder_s, %struct.lzma_coder_s* %92, i32 0, i32 0, !dbg !563
  %code = getelementptr inbounds %struct.lzma_next_coder_s, %struct.lzma_next_coder_s* %next96, i32 0, i32 3, !dbg !564
  %93 = load i32 (%struct.lzma_coder_s*, %struct.lzma_allocator*, i8*, i64*, i64, i8*, i64*, i64, i32)*, i32 (%struct.lzma_coder_s*, %struct.lzma_allocator*, i8*, i64*, i64, i8*, i64*, i64, i32)** %code, align 8, !dbg !564
  %94 = load %struct.lzma_coder_s*, %struct.lzma_coder_s** %coder.addr, align 8, !dbg !565
  %next97 = getelementptr inbounds %struct.lzma_coder_s, %struct.lzma_coder_s* %94, i32 0, i32 0, !dbg !566
  %coder98 = getelementptr inbounds %struct.lzma_next_coder_s, %struct.lzma_next_coder_s* %next97, i32 0, i32 0, !dbg !567
  %95 = load %struct.lzma_coder_s*, %struct.lzma_coder_s** %coder98, align 8, !dbg !567
  %96 = load %struct.lzma_allocator*, %struct.lzma_allocator** %allocator.addr, align 8, !dbg !568
  %97 = load i8*, i8** %in.addr, align 8, !dbg !569
  %98 = load i64*, i64** %in_pos.addr, align 8, !dbg !570
  %99 = load i64, i64* %in_size.addr, align 8, !dbg !571
  %100 = load i8*, i8** %out.addr, align 8, !dbg !572
  %101 = load i64*, i64** %out_pos.addr, align 8, !dbg !573
  %102 = load i64, i64* %out_size.addr, align 8, !dbg !574
  %103 = load i32, i32* %action.addr, align 4, !dbg !575
  %call99 = call i32 %93(%struct.lzma_coder_s* %95, %struct.lzma_allocator* %96, i8* %97, i64* %98, i64 %99, i8* %100, i64* %101, i64 %102, i32 %103), !dbg !561
  store i32 %call99, i32* %retval, align 4, !dbg !576
  br label %return, !dbg !576

sw.default:                                       ; preds = %while.body
  store i32 11, i32* %retval, align 4, !dbg !577
  br label %return, !dbg !577

sw.epilog:                                        ; preds = %if.end90, %if.then56, %if.end42, %if.end
  br label %while.cond, !dbg !578

while.end:                                        ; preds = %land.end
  store i32 0, i32* %retval, align 4, !dbg !580
  br label %return, !dbg !580

return:                                           ; preds = %while.end, %sw.default, %sw.bb95, %if.then89, %if.then84, %if.then69, %if.then37, %if.then
  %104 = load i32, i32* %retval, align 4, !dbg !581
  ret i32 %104, !dbg !581
}

; Function Attrs: nounwind uwtable
define internal void @alone_decoder_end(%struct.lzma_coder_s* %coder, %struct.lzma_allocator* %allocator) #0 !dbg !225 {
entry:
  %coder.addr = alloca %struct.lzma_coder_s*, align 8
  %allocator.addr = alloca %struct.lzma_allocator*, align 8
  store %struct.lzma_coder_s* %coder, %struct.lzma_coder_s** %coder.addr, align 8
  call void @llvm.dbg.declare(metadata %struct.lzma_coder_s** %coder.addr, metadata !582, metadata !234), !dbg !583
  store %struct.lzma_allocator* %allocator, %struct.lzma_allocator** %allocator.addr, align 8
  call void @llvm.dbg.declare(metadata %struct.lzma_allocator** %allocator.addr, metadata !584, metadata !234), !dbg !585
  %0 = load %struct.lzma_coder_s*, %struct.lzma_coder_s** %coder.addr, align 8, !dbg !586
  %next = getelementptr inbounds %struct.lzma_coder_s, %struct.lzma_coder_s* %0, i32 0, i32 0, !dbg !587
  %1 = load %struct.lzma_allocator*, %struct.lzma_allocator** %allocator.addr, align 8, !dbg !588
  call void @lzma_next_end(%struct.lzma_next_coder_s* %next, %struct.lzma_allocator* %1), !dbg !589
  %2 = load %struct.lzma_coder_s*, %struct.lzma_coder_s** %coder.addr, align 8, !dbg !590
  %3 = bitcast %struct.lzma_coder_s* %2 to i8*, !dbg !590
  %4 = load %struct.lzma_allocator*, %struct.lzma_allocator** %allocator.addr, align 8, !dbg !591
  call void @lzma_free(i8* %3, %struct.lzma_allocator* %4), !dbg !592
  ret void, !dbg !593
}

; Function Attrs: nounwind uwtable
define internal i32 @alone_decoder_memconfig(%struct.lzma_coder_s* %coder, i64* %memusage, i64* %old_memlimit, i64 %new_memlimit) #0 !dbg !226 {
entry:
  %retval = alloca i32, align 4
  %coder.addr = alloca %struct.lzma_coder_s*, align 8
  %memusage.addr = alloca i64*, align 8
  %old_memlimit.addr = alloca i64*, align 8
  %new_memlimit.addr = alloca i64, align 8
  store %struct.lzma_coder_s* %coder, %struct.lzma_coder_s** %coder.addr, align 8
  call void @llvm.dbg.declare(metadata %struct.lzma_coder_s** %coder.addr, metadata !594, metadata !234), !dbg !595
  store i64* %memusage, i64** %memusage.addr, align 8
  call void @llvm.dbg.declare(metadata i64** %memusage.addr, metadata !596, metadata !234), !dbg !597
  store i64* %old_memlimit, i64** %old_memlimit.addr, align 8
  call void @llvm.dbg.declare(metadata i64** %old_memlimit.addr, metadata !598, metadata !234), !dbg !599
  store i64 %new_memlimit, i64* %new_memlimit.addr, align 8
  call void @llvm.dbg.declare(metadata i64* %new_memlimit.addr, metadata !600, metadata !234), !dbg !601
  %0 = load %struct.lzma_coder_s*, %struct.lzma_coder_s** %coder.addr, align 8, !dbg !602
  %memusage1 = getelementptr inbounds %struct.lzma_coder_s, %struct.lzma_coder_s* %0, i32 0, i32 6, !dbg !603
  %1 = load i64, i64* %memusage1, align 8, !dbg !603
  %2 = load i64*, i64** %memusage.addr, align 8, !dbg !604
  store i64 %1, i64* %2, align 8, !dbg !605
  %3 = load %struct.lzma_coder_s*, %struct.lzma_coder_s** %coder.addr, align 8, !dbg !606
  %memlimit = getelementptr inbounds %struct.lzma_coder_s, %struct.lzma_coder_s* %3, i32 0, i32 5, !dbg !607
  %4 = load i64, i64* %memlimit, align 8, !dbg !607
  %5 = load i64*, i64** %old_memlimit.addr, align 8, !dbg !608
  store i64 %4, i64* %5, align 8, !dbg !609
  %6 = load i64, i64* %new_memlimit.addr, align 8, !dbg !610
  %cmp = icmp ne i64 %6, 0, !dbg !612
  br i1 %cmp, label %if.then, label %if.end6, !dbg !613

if.then:                                          ; preds = %entry
  %7 = load i64, i64* %new_memlimit.addr, align 8, !dbg !614
  %8 = load %struct.lzma_coder_s*, %struct.lzma_coder_s** %coder.addr, align 8, !dbg !617
  %memusage2 = getelementptr inbounds %struct.lzma_coder_s, %struct.lzma_coder_s* %8, i32 0, i32 6, !dbg !618
  %9 = load i64, i64* %memusage2, align 8, !dbg !618
  %cmp3 = icmp ult i64 %7, %9, !dbg !619
  br i1 %cmp3, label %if.then4, label %if.end, !dbg !620

if.then4:                                         ; preds = %if.then
  store i32 6, i32* %retval, align 4, !dbg !621
  br label %return, !dbg !621

if.end:                                           ; preds = %if.then
  %10 = load i64, i64* %new_memlimit.addr, align 8, !dbg !622
  %11 = load %struct.lzma_coder_s*, %struct.lzma_coder_s** %coder.addr, align 8, !dbg !623
  %memlimit5 = getelementptr inbounds %struct.lzma_coder_s, %struct.lzma_coder_s* %11, i32 0, i32 5, !dbg !624
  store i64 %10, i64* %memlimit5, align 8, !dbg !625
  br label %if.end6, !dbg !626

if.end6:                                          ; preds = %if.end, %entry
  store i32 0, i32* %retval, align 4, !dbg !627
  br label %return, !dbg !627

return:                                           ; preds = %if.end6, %if.then4
  %12 = load i32, i32* %retval, align 4, !dbg !628
  ret i32 %12, !dbg !628
}

; Function Attrs: argmemonly nounwind
declare void @llvm.memcpy.p0i8.p0i8.i64(i8* nocapture, i8* nocapture readonly, i64, i32, i1) #3

; Function Attrs: nounwind uwtable
define i32 @lzma_alone_decoder(%struct.lzma_stream* %strm, i64 %memlimit) #0 !dbg !197 {
entry:
  %retval = alloca i32, align 4
  %strm.addr = alloca %struct.lzma_stream*, align 8
  %memlimit.addr = alloca i64, align 8
  %ret_ = alloca i32, align 4
  %ret_2 = alloca i32, align 4
  store %struct.lzma_stream* %strm, %struct.lzma_stream** %strm.addr, align 8
  call void @llvm.dbg.declare(metadata %struct.lzma_stream** %strm.addr, metadata !629, metadata !234), !dbg !630
  store i64 %memlimit, i64* %memlimit.addr, align 8
  call void @llvm.dbg.declare(metadata i64* %memlimit.addr, metadata !631, metadata !234), !dbg !632
  br label %do.body, !dbg !633

do.body:                                          ; preds = %entry
  call void @llvm.dbg.declare(metadata i32* %ret_, metadata !634, metadata !234), !dbg !636
  br label %do.body1, !dbg !637

do.body1:                                         ; preds = %do.body
  call void @llvm.dbg.declare(metadata i32* %ret_2, metadata !639, metadata !234), !dbg !642
  %0 = load %struct.lzma_stream*, %struct.lzma_stream** %strm.addr, align 8, !dbg !643
  %call = call i32 @lzma_strm_init(%struct.lzma_stream* %0), !dbg !643
  store i32 %call, i32* %ret_2, align 4, !dbg !643
  %1 = load i32, i32* %ret_2, align 4, !dbg !643
  %cmp = icmp ne i32 %1, 0, !dbg !643
  br i1 %cmp, label %if.then, label %if.end, !dbg !643

if.then:                                          ; preds = %do.body1
  %2 = load i32, i32* %ret_2, align 4, !dbg !645
  store i32 %2, i32* %retval, align 4, !dbg !645
  br label %return, !dbg !645

if.end:                                           ; preds = %do.body1
  br label %do.end, !dbg !648

do.end:                                           ; preds = %if.end
  %3 = load %struct.lzma_stream*, %struct.lzma_stream** %strm.addr, align 8, !dbg !650
  %internal = getelementptr inbounds %struct.lzma_stream, %struct.lzma_stream* %3, i32 0, i32 7, !dbg !650
  %4 = load %struct.lzma_internal_s*, %struct.lzma_internal_s** %internal, align 8, !dbg !650
  %next = getelementptr inbounds %struct.lzma_internal_s, %struct.lzma_internal_s* %4, i32 0, i32 0, !dbg !650
  %5 = load %struct.lzma_stream*, %struct.lzma_stream** %strm.addr, align 8, !dbg !650
  %allocator = getelementptr inbounds %struct.lzma_stream, %struct.lzma_stream* %5, i32 0, i32 6, !dbg !650
  %6 = load %struct.lzma_allocator*, %struct.lzma_allocator** %allocator, align 8, !dbg !650
  %7 = load i64, i64* %memlimit.addr, align 8, !dbg !650
  %call3 = call i32 @lzma_alone_decoder_init(%struct.lzma_next_coder_s* %next, %struct.lzma_allocator* %6, i64 %7, i1 zeroext false), !dbg !650
  store i32 %call3, i32* %ret_, align 4, !dbg !650
  %8 = load i32, i32* %ret_, align 4, !dbg !650
  %cmp4 = icmp ne i32 %8, 0, !dbg !650
  br i1 %cmp4, label %if.then5, label %if.end6, !dbg !650

if.then5:                                         ; preds = %do.end
  %9 = load %struct.lzma_stream*, %struct.lzma_stream** %strm.addr, align 8, !dbg !652
  call void @lzma_end(%struct.lzma_stream* %9) #5, !dbg !652
  %10 = load i32, i32* %ret_, align 4, !dbg !652
  store i32 %10, i32* %retval, align 4, !dbg !652
  br label %return, !dbg !652

if.end6:                                          ; preds = %do.end
  br label %do.end7, !dbg !656

do.end7:                                          ; preds = %if.end6
  %11 = load %struct.lzma_stream*, %struct.lzma_stream** %strm.addr, align 8, !dbg !658
  %internal8 = getelementptr inbounds %struct.lzma_stream, %struct.lzma_stream* %11, i32 0, i32 7, !dbg !659
  %12 = load %struct.lzma_internal_s*, %struct.lzma_internal_s** %internal8, align 8, !dbg !659
  %supported_actions = getelementptr inbounds %struct.lzma_internal_s, %struct.lzma_internal_s* %12, i32 0, i32 3, !dbg !660
  %arrayidx = getelementptr inbounds [4 x i8], [4 x i8]* %supported_actions, i64 0, i64 0, !dbg !658
  store i8 1, i8* %arrayidx, align 8, !dbg !661
  %13 = load %struct.lzma_stream*, %struct.lzma_stream** %strm.addr, align 8, !dbg !662
  %internal9 = getelementptr inbounds %struct.lzma_stream, %struct.lzma_stream* %13, i32 0, i32 7, !dbg !663
  %14 = load %struct.lzma_internal_s*, %struct.lzma_internal_s** %internal9, align 8, !dbg !663
  %supported_actions10 = getelementptr inbounds %struct.lzma_internal_s, %struct.lzma_internal_s* %14, i32 0, i32 3, !dbg !664
  %arrayidx11 = getelementptr inbounds [4 x i8], [4 x i8]* %supported_actions10, i64 0, i64 3, !dbg !662
  store i8 1, i8* %arrayidx11, align 1, !dbg !665
  store i32 0, i32* %retval, align 4, !dbg !666
  br label %return, !dbg !666

return:                                           ; preds = %do.end7, %if.then5, %if.then
  %15 = load i32, i32* %retval, align 4, !dbg !667
  ret i32 %15, !dbg !667
}

declare i32 @lzma_strm_init(%struct.lzma_stream*) #2

; Function Attrs: nounwind
declare void @lzma_end(%struct.lzma_stream*) #4

declare zeroext i1 @lzma_lzma_lclppb_decode(%struct.lzma_options_lzma*, i8 zeroext) #2

declare i64 @lzma_lzma_decoder_memusage(i8*) #2

declare i32 @lzma_lzma_decoder_init(%struct.lzma_next_coder_s*, %struct.lzma_allocator*, %struct.lzma_filter_info_s*) #2

declare i32 @lzma_next_filter_init(%struct.lzma_next_coder_s*, %struct.lzma_allocator*, %struct.lzma_filter_info_s*) #2

declare void @lzma_lz_decoder_uncompressed(%struct.lzma_coder_s*, i64) #2

declare void @lzma_free(i8*, %struct.lzma_allocator*) #2

attributes #0 = { nounwind uwtable "disable-tail-calls"="false" "less-precise-fpmad"="false" "no-frame-pointer-elim"="true" "no-frame-pointer-elim-non-leaf" "no-infs-fp-math"="false" "no-nans-fp-math"="false" "stack-protector-buffer-size"="8" "target-cpu"="x86-64" "target-features"="+fxsr,+mmx,+sse,+sse2" "unsafe-fp-math"="false" "use-soft-float"="false" }
attributes #1 = { nounwind readnone }
attributes #2 = { "disable-tail-calls"="false" "less-precise-fpmad"="false" "no-frame-pointer-elim"="true" "no-frame-pointer-elim-non-leaf" "no-infs-fp-math"="false" "no-nans-fp-math"="false" "stack-protector-buffer-size"="8" "target-cpu"="x86-64" "target-features"="+fxsr,+mmx,+sse,+sse2" "unsafe-fp-math"="false" "use-soft-float"="false" }
attributes #3 = { argmemonly nounwind }
attributes #4 = { nounwind "disable-tail-calls"="false" "less-precise-fpmad"="false" "no-frame-pointer-elim"="true" "no-frame-pointer-elim-non-leaf" "no-infs-fp-math"="false" "no-nans-fp-math"="false" "stack-protector-buffer-size"="8" "target-cpu"="x86-64" "target-features"="+fxsr,+mmx,+sse,+sse2" "unsafe-fp-math"="false" "use-soft-float"="false" }
attributes #5 = { nounwind }

!llvm.dbg.cu = !{!0}
!llvm.module.flags = !{!230, !231}
!llvm.ident = !{!232}

!0 = distinct !DICompileUnit(language: DW_LANG_C99, file: !1, producer: "clang version 3.8.0 (tags/RELEASE_380/final)", isOptimized: false, runtimeVersion: 0, emissionKind: 1, enums: !2, retainedTypes: !190, subprograms: !191, globals: !227)
!1 = !DIFile(filename: "/data/download/cmake/cmake-master/Utilities/cmliblzma/liblzma/common/alone_decoder.c", directory: "/data/download/cmake/cmake-master/Utilities/cmliblzma")
!2 = !{!3, !18, !133, !140, !158, !69, !86, !172}
!3 = !DICompositeType(tag: DW_TAG_enumeration_type, file: !4, line: 57, size: 32, align: 32, elements: !5)
!4 = !DIFile(filename: "/data/download/cmake/cmake-master/Utilities/cmliblzma/liblzma/api/lzma/base.h", directory: "/data/download/cmake/cmake-master/Utilities/cmliblzma")
!5 = !{!6, !7, !8, !9, !10, !11, !12, !13, !14, !15, !16, !17}
!6 = !DIEnumerator(name: "LZMA_OK", value: 0)
!7 = !DIEnumerator(name: "LZMA_STREAM_END", value: 1)
!8 = !DIEnumerator(name: "LZMA_NO_CHECK", value: 2)
!9 = !DIEnumerator(name: "LZMA_UNSUPPORTED_CHECK", value: 3)
!10 = !DIEnumerator(name: "LZMA_GET_CHECK", value: 4)
!11 = !DIEnumerator(name: "LZMA_MEM_ERROR", value: 5)
!12 = !DIEnumerator(name: "LZMA_MEMLIMIT_ERROR", value: 6)
!13 = !DIEnumerator(name: "LZMA_FORMAT_ERROR", value: 7)
!14 = !DIEnumerator(name: "LZMA_OPTIONS_ERROR", value: 8)
!15 = !DIEnumerator(name: "LZMA_DATA_ERROR", value: 9)
!16 = !DIEnumerator(name: "LZMA_BUF_ERROR", value: 10)
!17 = !DIEnumerator(name: "LZMA_PROG_ERROR", value: 11)
!18 = !DICompositeType(tag: DW_TAG_enumeration_type, scope: !19, file: !1, line: 21, size: 32, align: 32, elements: !166)
!19 = !DICompositeType(tag: DW_TAG_structure_type, name: "lzma_coder_s", file: !1, line: 18, size: 1728, align: 64, elements: !20)
!20 = !{!21, !111, !112, !114, !115, !116, !117, !118}
!21 = !DIDerivedType(tag: DW_TAG_member, name: "next", scope: !19, file: !1, line: 19, baseType: !22, size: 512, align: 64)
!22 = !DIDerivedType(tag: DW_TAG_typedef, name: "lzma_next_coder", file: !23, line: 75, baseType: !24)
!23 = !DIFile(filename: "/data/download/cmake/cmake-master/Utilities/cmliblzma/liblzma/common/common.h", directory: "/data/download/cmake/cmake-master/Utilities/cmliblzma")
!24 = !DICompositeType(tag: DW_TAG_structure_type, name: "lzma_next_coder_s", file: !23, line: 119, size: 512, align: 64, elements: !25)
!25 = !{!26, !29, !35, !37, !75, !80, !94, !99}
!26 = !DIDerivedType(tag: DW_TAG_member, name: "coder", scope: !24, file: !23, line: 121, baseType: !27, size: 64, align: 64)
!27 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !28, size: 64, align: 64)
!28 = !DIDerivedType(tag: DW_TAG_typedef, name: "lzma_coder", file: !23, line: 73, baseType: !19)
!29 = !DIDerivedType(tag: DW_TAG_member, name: "id", scope: !24, file: !23, line: 125, baseType: !30, size: 64, align: 64, offset: 64)
!30 = !DIDerivedType(tag: DW_TAG_typedef, name: "lzma_vli", file: !31, line: 63, baseType: !32)
!31 = !DIFile(filename: "/data/download/cmake/cmake-master/Utilities/cmliblzma/liblzma/api/lzma/vli.h", directory: "/data/download/cmake/cmake-master/Utilities/cmliblzma")
!32 = !DIDerivedType(tag: DW_TAG_typedef, name: "uint64_t", file: !33, line: 55, baseType: !34)
!33 = !DIFile(filename: "/usr/include/stdint.h", directory: "/data/download/cmake/cmake-master/Utilities/cmliblzma")
!34 = !DIBasicType(name: "long unsigned int", size: 64, align: 64, encoding: DW_ATE_unsigned)
!35 = !DIDerivedType(tag: DW_TAG_member, name: "init", scope: !24, file: !23, line: 131, baseType: !36, size: 64, align: 64, offset: 128)
!36 = !DIDerivedType(tag: DW_TAG_typedef, name: "uintptr_t", file: !33, line: 122, baseType: !34)
!37 = !DIDerivedType(tag: DW_TAG_member, name: "code", scope: !24, file: !23, line: 134, baseType: !38, size: 64, align: 64, offset: 192)
!38 = !DIDerivedType(tag: DW_TAG_typedef, name: "lzma_code_function", file: !23, line: 89, baseType: !39)
!39 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !40, size: 64, align: 64)
!40 = !DISubroutineType(types: !41)
!41 = !{!42, !27, !43, !59, !64, !52, !66, !64, !52, !68}
!42 = !DIDerivedType(tag: DW_TAG_typedef, name: "lzma_ret", file: !4, line: 237, baseType: !3)
!43 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !44, size: 64, align: 64)
!44 = !DIDerivedType(tag: DW_TAG_typedef, name: "lzma_allocator", file: !4, line: 403, baseType: !45)
!45 = !DICompositeType(tag: DW_TAG_structure_type, file: !4, line: 341, size: 192, align: 64, elements: !46)
!46 = !{!47, !54, !58}
!47 = !DIDerivedType(tag: DW_TAG_member, name: "alloc", scope: !45, file: !4, line: 376, baseType: !48, size: 64, align: 64)
!48 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !49, size: 64, align: 64)
!49 = !DISubroutineType(types: !50)
!50 = !{!51, !51, !52, !52}
!51 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: null, size: 64, align: 64)
!52 = !DIDerivedType(tag: DW_TAG_typedef, name: "size_t", file: !53, line: 62, baseType: !34)
!53 = !DIFile(filename: "/opt/llvm-build/bin/../lib/clang/3.8.0/include/stddef.h", directory: "/data/download/cmake/cmake-master/Utilities/cmliblzma")
!54 = !DIDerivedType(tag: DW_TAG_member, name: "free", scope: !45, file: !4, line: 390, baseType: !55, size: 64, align: 64, offset: 64)
!55 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !56, size: 64, align: 64)
!56 = !DISubroutineType(types: !57)
!57 = !{null, !51, !51}
!58 = !DIDerivedType(tag: DW_TAG_member, name: "opaque", scope: !45, file: !4, line: 401, baseType: !51, size: 64, align: 64, offset: 128)
!59 = !DIDerivedType(tag: DW_TAG_restrict_type, baseType: !60)
!60 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !61, size: 64, align: 64)
!61 = !DIDerivedType(tag: DW_TAG_const_type, baseType: !62)
!62 = !DIDerivedType(tag: DW_TAG_typedef, name: "uint8_t", file: !33, line: 48, baseType: !63)
!63 = !DIBasicType(name: "unsigned char", size: 8, align: 8, encoding: DW_ATE_unsigned_char)
!64 = !DIDerivedType(tag: DW_TAG_restrict_type, baseType: !65)
!65 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !52, size: 64, align: 64)
!66 = !DIDerivedType(tag: DW_TAG_restrict_type, baseType: !67)
!67 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !62, size: 64, align: 64)
!68 = !DIDerivedType(tag: DW_TAG_typedef, name: "lzma_action", file: !4, line: 322, baseType: !69)
!69 = !DICompositeType(tag: DW_TAG_enumeration_type, file: !4, line: 250, size: 32, align: 32, elements: !70)
!70 = !{!71, !72, !73, !74}
!71 = !DIEnumerator(name: "LZMA_RUN", value: 0)
!72 = !DIEnumerator(name: "LZMA_SYNC_FLUSH", value: 1)
!73 = !DIEnumerator(name: "LZMA_FULL_FLUSH", value: 2)
!74 = !DIEnumerator(name: "LZMA_FINISH", value: 3)
!75 = !DIDerivedType(tag: DW_TAG_member, name: "end", scope: !24, file: !23, line: 139, baseType: !76, size: 64, align: 64, offset: 256)
!76 = !DIDerivedType(tag: DW_TAG_typedef, name: "lzma_end_function", file: !23, line: 97, baseType: !77)
!77 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !78, size: 64, align: 64)
!78 = !DISubroutineType(types: !79)
!79 = !{null, !27, !43}
!80 = !DIDerivedType(tag: DW_TAG_member, name: "get_check", scope: !24, file: !23, line: 143, baseType: !81, size: 64, align: 64, offset: 320)
!81 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !82, size: 64, align: 64)
!82 = !DISubroutineType(types: !83)
!83 = !{!84, !92}
!84 = !DIDerivedType(tag: DW_TAG_typedef, name: "lzma_check", file: !85, line: 55, baseType: !86)
!85 = !DIFile(filename: "/data/download/cmake/cmake-master/Utilities/cmliblzma/liblzma/api/lzma/check.h", directory: "/data/download/cmake/cmake-master/Utilities/cmliblzma")
!86 = !DICompositeType(tag: DW_TAG_enumeration_type, file: !85, line: 27, size: 32, align: 32, elements: !87)
!87 = !{!88, !89, !90, !91}
!88 = !DIEnumerator(name: "LZMA_CHECK_NONE", value: 0)
!89 = !DIEnumerator(name: "LZMA_CHECK_CRC32", value: 1)
!90 = !DIEnumerator(name: "LZMA_CHECK_CRC64", value: 4)
!91 = !DIEnumerator(name: "LZMA_CHECK_SHA256", value: 10)
!92 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !93, size: 64, align: 64)
!93 = !DIDerivedType(tag: DW_TAG_const_type, baseType: !28)
!94 = !DIDerivedType(tag: DW_TAG_member, name: "memconfig", scope: !24, file: !23, line: 147, baseType: !95, size: 64, align: 64, offset: 384)
!95 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !96, size: 64, align: 64)
!96 = !DISubroutineType(types: !97)
!97 = !{!42, !27, !98, !98, !32}
!98 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !32, size: 64, align: 64)
!99 = !DIDerivedType(tag: DW_TAG_member, name: "update", scope: !24, file: !23, line: 152, baseType: !100, size: 64, align: 64, offset: 448)
!100 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !101, size: 64, align: 64)
!101 = !DISubroutineType(types: !102)
!102 = !{!42, !27, !43, !103, !103}
!103 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !104, size: 64, align: 64)
!104 = !DIDerivedType(tag: DW_TAG_const_type, baseType: !105)
!105 = !DIDerivedType(tag: DW_TAG_typedef, name: "lzma_filter", file: !106, line: 65, baseType: !107)
!106 = !DIFile(filename: "/data/download/cmake/cmake-master/Utilities/cmliblzma/liblzma/api/lzma/filter.h", directory: "/data/download/cmake/cmake-master/Utilities/cmliblzma")
!107 = !DICompositeType(tag: DW_TAG_structure_type, file: !106, line: 43, size: 128, align: 64, elements: !108)
!108 = !{!109, !110}
!109 = !DIDerivedType(tag: DW_TAG_member, name: "id", scope: !107, file: !106, line: 54, baseType: !30, size: 64, align: 64)
!110 = !DIDerivedType(tag: DW_TAG_member, name: "options", scope: !107, file: !106, line: 63, baseType: !51, size: 64, align: 64, offset: 64)
!111 = !DIDerivedType(tag: DW_TAG_member, name: "sequence", scope: !19, file: !1, line: 27, baseType: !18, size: 32, align: 32, offset: 512)
!112 = !DIDerivedType(tag: DW_TAG_member, name: "picky", scope: !19, file: !1, line: 32, baseType: !113, size: 8, align: 8, offset: 544)
!113 = !DIBasicType(name: "_Bool", size: 8, align: 8, encoding: DW_ATE_boolean)
!114 = !DIDerivedType(tag: DW_TAG_member, name: "pos", scope: !19, file: !1, line: 35, baseType: !52, size: 64, align: 64, offset: 576)
!115 = !DIDerivedType(tag: DW_TAG_member, name: "uncompressed_size", scope: !19, file: !1, line: 38, baseType: !30, size: 64, align: 64, offset: 640)
!116 = !DIDerivedType(tag: DW_TAG_member, name: "memlimit", scope: !19, file: !1, line: 41, baseType: !32, size: 64, align: 64, offset: 704)
!117 = !DIDerivedType(tag: DW_TAG_member, name: "memusage", scope: !19, file: !1, line: 44, baseType: !32, size: 64, align: 64, offset: 768)
!118 = !DIDerivedType(tag: DW_TAG_member, name: "options", scope: !19, file: !1, line: 48, baseType: !119, size: 896, align: 64, offset: 832)
!119 = !DIDerivedType(tag: DW_TAG_typedef, name: "lzma_options_lzma", file: !120, line: 399, baseType: !121)
!120 = !DIFile(filename: "/data/download/cmake/cmake-master/Utilities/cmliblzma/liblzma/api/lzma/lzma.h", directory: "/data/download/cmake/cmake-master/Utilities/cmliblzma")
!121 = !DICompositeType(tag: DW_TAG_structure_type, file: !120, line: 185, size: 896, align: 64, elements: !122)
!122 = !{!123, !126, !127, !128, !129, !130, !131, !137, !138, !147, !148, !149, !150, !151, !152, !153, !154, !155, !156, !161, !162, !163, !164, !165}
!123 = !DIDerivedType(tag: DW_TAG_member, name: "dict_size", scope: !121, file: !120, line: 217, baseType: !124, size: 32, align: 32)
!124 = !DIDerivedType(tag: DW_TAG_typedef, name: "uint32_t", file: !33, line: 51, baseType: !125)
!125 = !DIBasicType(name: "unsigned int", size: 32, align: 32, encoding: DW_ATE_unsigned)
!126 = !DIDerivedType(tag: DW_TAG_member, name: "preset_dict", scope: !121, file: !120, line: 240, baseType: !60, size: 64, align: 64, offset: 64)
!127 = !DIDerivedType(tag: DW_TAG_member, name: "preset_dict_size", scope: !121, file: !120, line: 254, baseType: !124, size: 32, align: 32, offset: 128)
!128 = !DIDerivedType(tag: DW_TAG_member, name: "lc", scope: !121, file: !120, line: 281, baseType: !124, size: 32, align: 32, offset: 160)
!129 = !DIDerivedType(tag: DW_TAG_member, name: "lp", scope: !121, file: !120, line: 293, baseType: !124, size: 32, align: 32, offset: 192)
!130 = !DIDerivedType(tag: DW_TAG_member, name: "pb", scope: !121, file: !120, line: 316, baseType: !124, size: 32, align: 32, offset: 224)
!131 = !DIDerivedType(tag: DW_TAG_member, name: "mode", scope: !121, file: !120, line: 322, baseType: !132, size: 32, align: 32, offset: 256)
!132 = !DIDerivedType(tag: DW_TAG_typedef, name: "lzma_mode", file: !120, line: 155, baseType: !133)
!133 = !DICompositeType(tag: DW_TAG_enumeration_type, file: !120, line: 138, size: 32, align: 32, elements: !134)
!134 = !{!135, !136}
!135 = !DIEnumerator(name: "LZMA_MODE_FAST", value: 1)
!136 = !DIEnumerator(name: "LZMA_MODE_NORMAL", value: 2)
!137 = !DIDerivedType(tag: DW_TAG_member, name: "nice_len", scope: !121, file: !120, line: 342, baseType: !124, size: 32, align: 32, offset: 288)
!138 = !DIDerivedType(tag: DW_TAG_member, name: "mf", scope: !121, file: !120, line: 345, baseType: !139, size: 32, align: 32, offset: 320)
!139 = !DIDerivedType(tag: DW_TAG_typedef, name: "lzma_match_finder", file: !120, line: 111, baseType: !140)
!140 = !DICompositeType(tag: DW_TAG_enumeration_type, file: !120, line: 58, size: 32, align: 32, elements: !141)
!141 = !{!142, !143, !144, !145, !146}
!142 = !DIEnumerator(name: "LZMA_MF_HC3", value: 3)
!143 = !DIEnumerator(name: "LZMA_MF_HC4", value: 4)
!144 = !DIEnumerator(name: "LZMA_MF_BT2", value: 18)
!145 = !DIEnumerator(name: "LZMA_MF_BT3", value: 19)
!146 = !DIEnumerator(name: "LZMA_MF_BT4", value: 20)
!147 = !DIDerivedType(tag: DW_TAG_member, name: "depth", scope: !121, file: !120, line: 375, baseType: !124, size: 32, align: 32, offset: 352)
!148 = !DIDerivedType(tag: DW_TAG_member, name: "reserved_int1", scope: !121, file: !120, line: 384, baseType: !124, size: 32, align: 32, offset: 384)
!149 = !DIDerivedType(tag: DW_TAG_member, name: "reserved_int2", scope: !121, file: !120, line: 385, baseType: !124, size: 32, align: 32, offset: 416)
!150 = !DIDerivedType(tag: DW_TAG_member, name: "reserved_int3", scope: !121, file: !120, line: 386, baseType: !124, size: 32, align: 32, offset: 448)
!151 = !DIDerivedType(tag: DW_TAG_member, name: "reserved_int4", scope: !121, file: !120, line: 387, baseType: !124, size: 32, align: 32, offset: 480)
!152 = !DIDerivedType(tag: DW_TAG_member, name: "reserved_int5", scope: !121, file: !120, line: 388, baseType: !124, size: 32, align: 32, offset: 512)
!153 = !DIDerivedType(tag: DW_TAG_member, name: "reserved_int6", scope: !121, file: !120, line: 389, baseType: !124, size: 32, align: 32, offset: 544)
!154 = !DIDerivedType(tag: DW_TAG_member, name: "reserved_int7", scope: !121, file: !120, line: 390, baseType: !124, size: 32, align: 32, offset: 576)
!155 = !DIDerivedType(tag: DW_TAG_member, name: "reserved_int8", scope: !121, file: !120, line: 391, baseType: !124, size: 32, align: 32, offset: 608)
!156 = !DIDerivedType(tag: DW_TAG_member, name: "reserved_enum1", scope: !121, file: !120, line: 392, baseType: !157, size: 32, align: 32, offset: 640)
!157 = !DIDerivedType(tag: DW_TAG_typedef, name: "lzma_reserved_enum", file: !4, line: 46, baseType: !158)
!158 = !DICompositeType(tag: DW_TAG_enumeration_type, file: !4, line: 44, size: 32, align: 32, elements: !159)
!159 = !{!160}
!160 = !DIEnumerator(name: "LZMA_RESERVED_ENUM", value: 0)
!161 = !DIDerivedType(tag: DW_TAG_member, name: "reserved_enum2", scope: !121, file: !120, line: 393, baseType: !157, size: 32, align: 32, offset: 672)
!162 = !DIDerivedType(tag: DW_TAG_member, name: "reserved_enum3", scope: !121, file: !120, line: 394, baseType: !157, size: 32, align: 32, offset: 704)
!163 = !DIDerivedType(tag: DW_TAG_member, name: "reserved_enum4", scope: !121, file: !120, line: 395, baseType: !157, size: 32, align: 32, offset: 736)
!164 = !DIDerivedType(tag: DW_TAG_member, name: "reserved_ptr1", scope: !121, file: !120, line: 396, baseType: !51, size: 64, align: 64, offset: 768)
!165 = !DIDerivedType(tag: DW_TAG_member, name: "reserved_ptr2", scope: !121, file: !120, line: 397, baseType: !51, size: 64, align: 64, offset: 832)
!166 = !{!167, !168, !169, !170, !171}
!167 = !DIEnumerator(name: "SEQ_PROPERTIES", value: 0)
!168 = !DIEnumerator(name: "SEQ_DICTIONARY_SIZE", value: 1)
!169 = !DIEnumerator(name: "SEQ_UNCOMPRESSED_SIZE", value: 2)
!170 = !DIEnumerator(name: "SEQ_CODER_INIT", value: 3)
!171 = !DIEnumerator(name: "SEQ_CODE", value: 4)
!172 = !DICompositeType(tag: DW_TAG_enumeration_type, scope: !173, file: !23, line: 182, size: 32, align: 32, elements: !183)
!173 = !DICompositeType(tag: DW_TAG_structure_type, name: "lzma_internal_s", file: !23, line: 174, size: 704, align: 64, elements: !174)
!174 = !{!175, !176, !177, !178, !182}
!175 = !DIDerivedType(tag: DW_TAG_member, name: "next", scope: !173, file: !23, line: 176, baseType: !22, size: 512, align: 64)
!176 = !DIDerivedType(tag: DW_TAG_member, name: "sequence", scope: !173, file: !23, line: 189, baseType: !172, size: 32, align: 32, offset: 512)
!177 = !DIDerivedType(tag: DW_TAG_member, name: "avail_in", scope: !173, file: !23, line: 194, baseType: !52, size: 64, align: 64, offset: 576)
!178 = !DIDerivedType(tag: DW_TAG_member, name: "supported_actions", scope: !173, file: !23, line: 197, baseType: !179, size: 32, align: 8, offset: 640)
!179 = !DICompositeType(tag: DW_TAG_array_type, baseType: !113, size: 32, align: 8, elements: !180)
!180 = !{!181}
!181 = !DISubrange(count: 4)
!182 = !DIDerivedType(tag: DW_TAG_member, name: "allow_buf_error", scope: !173, file: !23, line: 201, baseType: !113, size: 8, align: 8, offset: 672)
!183 = !{!184, !185, !186, !187, !188, !189}
!184 = !DIEnumerator(name: "ISEQ_RUN", value: 0)
!185 = !DIEnumerator(name: "ISEQ_SYNC_FLUSH", value: 1)
!186 = !DIEnumerator(name: "ISEQ_FULL_FLUSH", value: 2)
!187 = !DIEnumerator(name: "ISEQ_FINISH", value: 3)
!188 = !DIEnumerator(name: "ISEQ_END", value: 4)
!189 = !DIEnumerator(name: "ISEQ_ERROR", value: 5)
!190 = !{!36, !51, !52, !30}
!191 = !{!192, !197, !224, !225, !226}
!192 = distinct !DISubprogram(name: "lzma_alone_decoder_init", scope: !1, file: !1, line: 194, type: !193, isLocal: false, isDefinition: true, scopeLine: 196, flags: DIFlagPrototyped, isOptimized: false, variables: !196)
!193 = !DISubroutineType(types: !194)
!194 = !{!42, !195, !43, !32, !113}
!195 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !22, size: 64, align: 64)
!196 = !{}
!197 = distinct !DISubprogram(name: "lzma_alone_decoder", scope: !1, file: !1, line: 228, type: !198, isLocal: false, isDefinition: true, scopeLine: 229, flags: DIFlagPrototyped, isOptimized: false, variables: !196)
!198 = !DISubroutineType(types: !199)
!199 = !{!42, !200, !32}
!200 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !201, size: 64, align: 64)
!201 = !DIDerivedType(tag: DW_TAG_typedef, name: "lzma_stream", file: !4, line: 490, baseType: !202)
!202 = !DICompositeType(tag: DW_TAG_structure_type, file: !4, line: 453, size: 1088, align: 64, elements: !203)
!203 = !{!204, !205, !206, !207, !208, !209, !210, !211, !214, !215, !216, !217, !218, !219, !220, !221, !222, !223}
!204 = !DIDerivedType(tag: DW_TAG_member, name: "next_in", scope: !202, file: !4, line: 454, baseType: !60, size: 64, align: 64)
!205 = !DIDerivedType(tag: DW_TAG_member, name: "avail_in", scope: !202, file: !4, line: 455, baseType: !52, size: 64, align: 64, offset: 64)
!206 = !DIDerivedType(tag: DW_TAG_member, name: "total_in", scope: !202, file: !4, line: 456, baseType: !32, size: 64, align: 64, offset: 128)
!207 = !DIDerivedType(tag: DW_TAG_member, name: "next_out", scope: !202, file: !4, line: 458, baseType: !67, size: 64, align: 64, offset: 192)
!208 = !DIDerivedType(tag: DW_TAG_member, name: "avail_out", scope: !202, file: !4, line: 459, baseType: !52, size: 64, align: 64, offset: 256)
!209 = !DIDerivedType(tag: DW_TAG_member, name: "total_out", scope: !202, file: !4, line: 460, baseType: !32, size: 64, align: 64, offset: 320)
!210 = !DIDerivedType(tag: DW_TAG_member, name: "allocator", scope: !202, file: !4, line: 468, baseType: !43, size: 64, align: 64, offset: 384)
!211 = !DIDerivedType(tag: DW_TAG_member, name: "internal", scope: !202, file: !4, line: 471, baseType: !212, size: 64, align: 64, offset: 448)
!212 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !213, size: 64, align: 64)
!213 = !DIDerivedType(tag: DW_TAG_typedef, name: "lzma_internal", file: !4, line: 411, baseType: !173)
!214 = !DIDerivedType(tag: DW_TAG_member, name: "reserved_ptr1", scope: !202, file: !4, line: 479, baseType: !51, size: 64, align: 64, offset: 512)
!215 = !DIDerivedType(tag: DW_TAG_member, name: "reserved_ptr2", scope: !202, file: !4, line: 480, baseType: !51, size: 64, align: 64, offset: 576)
!216 = !DIDerivedType(tag: DW_TAG_member, name: "reserved_ptr3", scope: !202, file: !4, line: 481, baseType: !51, size: 64, align: 64, offset: 640)
!217 = !DIDerivedType(tag: DW_TAG_member, name: "reserved_ptr4", scope: !202, file: !4, line: 482, baseType: !51, size: 64, align: 64, offset: 704)
!218 = !DIDerivedType(tag: DW_TAG_member, name: "reserved_int1", scope: !202, file: !4, line: 483, baseType: !32, size: 64, align: 64, offset: 768)
!219 = !DIDerivedType(tag: DW_TAG_member, name: "reserved_int2", scope: !202, file: !4, line: 484, baseType: !32, size: 64, align: 64, offset: 832)
!220 = !DIDerivedType(tag: DW_TAG_member, name: "reserved_int3", scope: !202, file: !4, line: 485, baseType: !52, size: 64, align: 64, offset: 896)
!221 = !DIDerivedType(tag: DW_TAG_member, name: "reserved_int4", scope: !202, file: !4, line: 486, baseType: !52, size: 64, align: 64, offset: 960)
!222 = !DIDerivedType(tag: DW_TAG_member, name: "reserved_enum1", scope: !202, file: !4, line: 487, baseType: !157, size: 32, align: 32, offset: 1024)
!223 = !DIDerivedType(tag: DW_TAG_member, name: "reserved_enum2", scope: !202, file: !4, line: 488, baseType: !157, size: 32, align: 32, offset: 1056)
!224 = distinct !DISubprogram(name: "alone_decode", scope: !1, file: !1, line: 53, type: !40, isLocal: true, isDefinition: true, scopeLine: 59, flags: DIFlagPrototyped, isOptimized: false, variables: !196)
!225 = distinct !DISubprogram(name: "alone_decoder_end", scope: !1, file: !1, line: 167, type: !78, isLocal: true, isDefinition: true, scopeLine: 168, flags: DIFlagPrototyped, isOptimized: false, variables: !196)
!226 = distinct !DISubprogram(name: "alone_decoder_memconfig", scope: !1, file: !1, line: 176, type: !96, isLocal: true, isDefinition: true, scopeLine: 178, flags: DIFlagPrototyped, isOptimized: false, variables: !196)
!227 = !{!228}
!228 = !DIGlobalVariable(name: "LZMA_NEXT_CODER_INIT", scope: !0, file: !23, line: 159, type: !229, isLocal: true, isDefinition: true, variable: %struct.lzma_next_coder_s* @LZMA_NEXT_CODER_INIT)
!229 = !DIDerivedType(tag: DW_TAG_const_type, baseType: !22)
!230 = !{i32 2, !"Dwarf Version", i32 4}
!231 = !{i32 2, !"Debug Info Version", i32 3}
!232 = !{!"clang version 3.8.0 (tags/RELEASE_380/final)"}
!233 = !DILocalVariable(name: "next", arg: 1, scope: !192, file: !1, line: 194, type: !195)
!234 = !DIExpression()
!235 = !DILocation(line: 194, column: 42, scope: !192)
!236 = !DILocalVariable(name: "allocator", arg: 2, scope: !192, file: !1, line: 194, type: !43)
!237 = !DILocation(line: 194, column: 64, scope: !192)
!238 = !DILocalVariable(name: "memlimit", arg: 3, scope: !192, file: !1, line: 195, type: !32)
!239 = !DILocation(line: 195, column: 12, scope: !192)
!240 = !DILocalVariable(name: "picky", arg: 4, scope: !192, file: !1, line: 195, type: !113)
!241 = !DILocation(line: 195, column: 27, scope: !192)
!242 = !DILocation(line: 197, column: 2, scope: !192)
!243 = !DILocation(line: 197, column: 2, scope: !244)
!244 = !DILexicalBlockFile(scope: !245, file: !1, discriminator: 1)
!245 = distinct !DILexicalBlock(scope: !246, file: !1, line: 197, column: 2)
!246 = distinct !DILexicalBlock(scope: !192, file: !1, line: 197, column: 2)
!247 = !DILocation(line: 197, column: 2, scope: !248)
!248 = !DILexicalBlockFile(scope: !245, file: !1, discriminator: 2)
!249 = !DILocation(line: 197, column: 2, scope: !250)
!250 = !DILexicalBlockFile(scope: !246, file: !1, discriminator: 3)
!251 = !DILocation(line: 199, column: 6, scope: !252)
!252 = distinct !DILexicalBlock(scope: !192, file: !1, line: 199, column: 6)
!253 = !DILocation(line: 199, column: 15, scope: !252)
!254 = !DILocation(line: 199, column: 6, scope: !192)
!255 = !DILocation(line: 200, column: 3, scope: !252)
!256 = !DILocation(line: 202, column: 6, scope: !257)
!257 = distinct !DILexicalBlock(scope: !192, file: !1, line: 202, column: 6)
!258 = !DILocation(line: 202, column: 12, scope: !257)
!259 = !DILocation(line: 202, column: 18, scope: !257)
!260 = !DILocation(line: 202, column: 6, scope: !192)
!261 = !DILocation(line: 203, column: 48, scope: !262)
!262 = distinct !DILexicalBlock(scope: !257, file: !1, line: 202, column: 27)
!263 = !DILocation(line: 203, column: 17, scope: !262)
!264 = !DILocation(line: 203, column: 3, scope: !262)
!265 = !DILocation(line: 203, column: 9, scope: !262)
!266 = !DILocation(line: 203, column: 15, scope: !262)
!267 = !DILocation(line: 204, column: 7, scope: !268)
!268 = distinct !DILexicalBlock(scope: !262, file: !1, line: 204, column: 7)
!269 = !DILocation(line: 204, column: 13, scope: !268)
!270 = !DILocation(line: 204, column: 19, scope: !268)
!271 = !DILocation(line: 204, column: 7, scope: !262)
!272 = !DILocation(line: 205, column: 4, scope: !268)
!273 = !DILocation(line: 207, column: 3, scope: !262)
!274 = !DILocation(line: 207, column: 9, scope: !262)
!275 = !DILocation(line: 207, column: 14, scope: !262)
!276 = !DILocation(line: 208, column: 3, scope: !262)
!277 = !DILocation(line: 208, column: 9, scope: !262)
!278 = !DILocation(line: 208, column: 13, scope: !262)
!279 = !DILocation(line: 209, column: 3, scope: !262)
!280 = !DILocation(line: 209, column: 9, scope: !262)
!281 = !DILocation(line: 209, column: 19, scope: !262)
!282 = !DILocation(line: 210, column: 3, scope: !262)
!283 = !DILocation(line: 210, column: 9, scope: !262)
!284 = !DILocation(line: 210, column: 16, scope: !262)
!285 = !DILocation(line: 210, column: 23, scope: !262)
!286 = !DILocation(line: 211, column: 2, scope: !262)
!287 = !DILocation(line: 213, column: 2, scope: !192)
!288 = !DILocation(line: 213, column: 8, scope: !192)
!289 = !DILocation(line: 213, column: 15, scope: !192)
!290 = !DILocation(line: 213, column: 24, scope: !192)
!291 = !DILocation(line: 214, column: 23, scope: !192)
!292 = !DILocation(line: 214, column: 2, scope: !192)
!293 = !DILocation(line: 214, column: 8, scope: !192)
!294 = !DILocation(line: 214, column: 15, scope: !192)
!295 = !DILocation(line: 214, column: 21, scope: !192)
!296 = !DILocation(line: 215, column: 2, scope: !192)
!297 = !DILocation(line: 215, column: 8, scope: !192)
!298 = !DILocation(line: 215, column: 15, scope: !192)
!299 = !DILocation(line: 215, column: 19, scope: !192)
!300 = !DILocation(line: 216, column: 2, scope: !192)
!301 = !DILocation(line: 216, column: 8, scope: !192)
!302 = !DILocation(line: 216, column: 15, scope: !192)
!303 = !DILocation(line: 216, column: 23, scope: !192)
!304 = !DILocation(line: 216, column: 33, scope: !192)
!305 = !DILocation(line: 217, column: 2, scope: !192)
!306 = !DILocation(line: 217, column: 8, scope: !192)
!307 = !DILocation(line: 217, column: 15, scope: !192)
!308 = !DILocation(line: 217, column: 23, scope: !192)
!309 = !DILocation(line: 217, column: 35, scope: !192)
!310 = !DILocation(line: 218, column: 2, scope: !192)
!311 = !DILocation(line: 218, column: 8, scope: !192)
!312 = !DILocation(line: 218, column: 15, scope: !192)
!313 = !DILocation(line: 218, column: 23, scope: !192)
!314 = !DILocation(line: 218, column: 40, scope: !192)
!315 = !DILocation(line: 219, column: 2, scope: !192)
!316 = !DILocation(line: 219, column: 8, scope: !192)
!317 = !DILocation(line: 219, column: 15, scope: !192)
!318 = !DILocation(line: 219, column: 33, scope: !192)
!319 = !DILocation(line: 220, column: 26, scope: !192)
!320 = !DILocation(line: 220, column: 2, scope: !192)
!321 = !DILocation(line: 220, column: 8, scope: !192)
!322 = !DILocation(line: 220, column: 15, scope: !192)
!323 = !DILocation(line: 220, column: 24, scope: !192)
!324 = !DILocation(line: 221, column: 2, scope: !192)
!325 = !DILocation(line: 221, column: 8, scope: !192)
!326 = !DILocation(line: 221, column: 15, scope: !192)
!327 = !DILocation(line: 221, column: 24, scope: !192)
!328 = !DILocation(line: 223, column: 2, scope: !192)
!329 = !DILocation(line: 224, column: 1, scope: !192)
!330 = !DILocalVariable(name: "coder", arg: 1, scope: !224, file: !1, line: 53, type: !27)
!331 = !DILocation(line: 53, column: 26, scope: !224)
!332 = !DILocalVariable(name: "allocator", arg: 2, scope: !224, file: !1, line: 54, type: !43)
!333 = !DILocation(line: 54, column: 19, scope: !224)
!334 = !DILocalVariable(name: "in", arg: 3, scope: !224, file: !1, line: 55, type: !59)
!335 = !DILocation(line: 55, column: 32, scope: !224)
!336 = !DILocalVariable(name: "in_pos", arg: 4, scope: !224, file: !1, line: 55, type: !64)
!337 = !DILocation(line: 55, column: 58, scope: !224)
!338 = !DILocalVariable(name: "in_size", arg: 5, scope: !224, file: !1, line: 56, type: !52)
!339 = !DILocation(line: 56, column: 10, scope: !224)
!340 = !DILocalVariable(name: "out", arg: 6, scope: !224, file: !1, line: 56, type: !66)
!341 = !DILocation(line: 56, column: 42, scope: !224)
!342 = !DILocalVariable(name: "out_pos", arg: 7, scope: !224, file: !1, line: 57, type: !64)
!343 = !DILocation(line: 57, column: 25, scope: !224)
!344 = !DILocalVariable(name: "out_size", arg: 8, scope: !224, file: !1, line: 57, type: !52)
!345 = !DILocation(line: 57, column: 41, scope: !224)
!346 = !DILocalVariable(name: "action", arg: 9, scope: !224, file: !1, line: 58, type: !68)
!347 = !DILocation(line: 58, column: 15, scope: !224)
!348 = !DILocation(line: 60, column: 2, scope: !224)
!349 = !DILocation(line: 60, column: 10, scope: !350)
!350 = !DILexicalBlockFile(scope: !224, file: !1, discriminator: 1)
!351 = !DILocation(line: 60, column: 9, scope: !350)
!352 = !DILocation(line: 60, column: 20, scope: !350)
!353 = !DILocation(line: 60, column: 18, scope: !350)
!354 = !DILocation(line: 61, column: 4, scope: !224)
!355 = !DILocation(line: 61, column: 8, scope: !350)
!356 = !DILocation(line: 61, column: 15, scope: !350)
!357 = !DILocation(line: 61, column: 24, scope: !350)
!358 = !DILocation(line: 61, column: 36, scope: !350)
!359 = !DILocation(line: 61, column: 40, scope: !360)
!360 = !DILexicalBlockFile(scope: !224, file: !1, discriminator: 2)
!361 = !DILocation(line: 61, column: 39, scope: !360)
!362 = !DILocation(line: 61, column: 49, scope: !360)
!363 = !DILocation(line: 61, column: 47, scope: !360)
!364 = !DILocation(line: 61, column: 36, scope: !360)
!365 = !DILocation(line: 60, column: 2, scope: !360)
!366 = !DILocation(line: 62, column: 10, scope: !224)
!367 = !DILocation(line: 62, column: 17, scope: !224)
!368 = !DILocation(line: 62, column: 2, scope: !224)
!369 = !DILocation(line: 64, column: 32, scope: !370)
!370 = distinct !DILexicalBlock(scope: !371, file: !1, line: 64, column: 7)
!371 = distinct !DILexicalBlock(scope: !224, file: !1, line: 62, column: 27)
!372 = !DILocation(line: 64, column: 39, scope: !370)
!373 = !DILocation(line: 64, column: 52, scope: !370)
!374 = !DILocation(line: 64, column: 51, scope: !370)
!375 = !DILocation(line: 64, column: 48, scope: !370)
!376 = !DILocation(line: 64, column: 7, scope: !370)
!377 = !DILocation(line: 64, column: 7, scope: !371)
!378 = !DILocation(line: 65, column: 4, scope: !370)
!379 = !DILocation(line: 67, column: 3, scope: !371)
!380 = !DILocation(line: 67, column: 10, scope: !371)
!381 = !DILocation(line: 67, column: 19, scope: !371)
!382 = !DILocation(line: 68, column: 6, scope: !371)
!383 = !DILocation(line: 68, column: 3, scope: !371)
!384 = !DILocation(line: 69, column: 3, scope: !371)
!385 = !DILocation(line: 73, column: 21, scope: !371)
!386 = !DILocation(line: 73, column: 20, scope: !371)
!387 = !DILocation(line: 73, column: 17, scope: !371)
!388 = !DILocation(line: 73, column: 8, scope: !371)
!389 = !DILocation(line: 73, column: 34, scope: !371)
!390 = !DILocation(line: 73, column: 41, scope: !371)
!391 = !DILocation(line: 73, column: 45, scope: !371)
!392 = !DILocation(line: 73, column: 30, scope: !371)
!393 = !DILocation(line: 72, column: 3, scope: !371)
!394 = !DILocation(line: 72, column: 10, scope: !371)
!395 = !DILocation(line: 72, column: 18, scope: !371)
!396 = !DILocation(line: 73, column: 5, scope: !371)
!397 = !DILocation(line: 75, column: 9, scope: !398)
!398 = distinct !DILexicalBlock(scope: !371, file: !1, line: 75, column: 7)
!399 = !DILocation(line: 75, column: 16, scope: !398)
!400 = !DILocation(line: 75, column: 7, scope: !398)
!401 = !DILocation(line: 75, column: 20, scope: !398)
!402 = !DILocation(line: 75, column: 7, scope: !371)
!403 = !DILocation(line: 76, column: 8, scope: !404)
!404 = distinct !DILexicalBlock(scope: !405, file: !1, line: 76, column: 8)
!405 = distinct !DILexicalBlock(scope: !398, file: !1, line: 75, column: 26)
!406 = !DILocation(line: 76, column: 15, scope: !404)
!407 = !DILocation(line: 76, column: 21, scope: !404)
!408 = !DILocation(line: 76, column: 24, scope: !409)
!409 = !DILexicalBlockFile(scope: !404, file: !1, discriminator: 1)
!410 = !DILocation(line: 76, column: 31, scope: !409)
!411 = !DILocation(line: 76, column: 39, scope: !409)
!412 = !DILocation(line: 77, column: 6, scope: !404)
!413 = !DILocation(line: 76, column: 8, scope: !409)
!414 = !DILocalVariable(name: "d", scope: !415, file: !1, line: 83, type: !124)
!415 = distinct !DILexicalBlock(scope: !404, file: !1, line: 77, column: 21)
!416 = !DILocation(line: 83, column: 14, scope: !415)
!417 = !DILocation(line: 83, column: 18, scope: !415)
!418 = !DILocation(line: 83, column: 25, scope: !415)
!419 = !DILocation(line: 83, column: 33, scope: !415)
!420 = !DILocation(line: 83, column: 43, scope: !415)
!421 = !DILocation(line: 84, column: 10, scope: !415)
!422 = !DILocation(line: 84, column: 12, scope: !415)
!423 = !DILocation(line: 84, column: 7, scope: !415)
!424 = !DILocation(line: 85, column: 10, scope: !415)
!425 = !DILocation(line: 85, column: 12, scope: !415)
!426 = !DILocation(line: 85, column: 7, scope: !415)
!427 = !DILocation(line: 86, column: 10, scope: !415)
!428 = !DILocation(line: 86, column: 12, scope: !415)
!429 = !DILocation(line: 86, column: 7, scope: !415)
!430 = !DILocation(line: 87, column: 10, scope: !415)
!431 = !DILocation(line: 87, column: 12, scope: !415)
!432 = !DILocation(line: 87, column: 7, scope: !415)
!433 = !DILocation(line: 88, column: 10, scope: !415)
!434 = !DILocation(line: 88, column: 12, scope: !415)
!435 = !DILocation(line: 88, column: 7, scope: !415)
!436 = !DILocation(line: 89, column: 5, scope: !415)
!437 = !DILocation(line: 91, column: 9, scope: !438)
!438 = distinct !DILexicalBlock(scope: !415, file: !1, line: 91, column: 9)
!439 = !DILocation(line: 91, column: 14, scope: !438)
!440 = !DILocation(line: 91, column: 21, scope: !438)
!441 = !DILocation(line: 91, column: 29, scope: !438)
!442 = !DILocation(line: 91, column: 11, scope: !438)
!443 = !DILocation(line: 91, column: 9, scope: !415)
!444 = !DILocation(line: 92, column: 6, scope: !438)
!445 = !DILocation(line: 93, column: 4, scope: !415)
!446 = !DILocation(line: 95, column: 4, scope: !405)
!447 = !DILocation(line: 95, column: 11, scope: !405)
!448 = !DILocation(line: 95, column: 15, scope: !405)
!449 = !DILocation(line: 96, column: 4, scope: !405)
!450 = !DILocation(line: 96, column: 11, scope: !405)
!451 = !DILocation(line: 96, column: 20, scope: !405)
!452 = !DILocation(line: 97, column: 3, scope: !405)
!453 = !DILocation(line: 99, column: 6, scope: !371)
!454 = !DILocation(line: 99, column: 3, scope: !371)
!455 = !DILocation(line: 100, column: 3, scope: !371)
!456 = !DILocation(line: 104, column: 23, scope: !371)
!457 = !DILocation(line: 104, column: 22, scope: !371)
!458 = !DILocation(line: 104, column: 19, scope: !371)
!459 = !DILocation(line: 104, column: 8, scope: !371)
!460 = !DILocation(line: 104, column: 36, scope: !371)
!461 = !DILocation(line: 104, column: 43, scope: !371)
!462 = !DILocation(line: 104, column: 47, scope: !371)
!463 = !DILocation(line: 104, column: 32, scope: !371)
!464 = !DILocation(line: 103, column: 3, scope: !371)
!465 = !DILocation(line: 103, column: 10, scope: !371)
!466 = !DILocation(line: 104, column: 5, scope: !371)
!467 = !DILocation(line: 105, column: 6, scope: !371)
!468 = !DILocation(line: 105, column: 3, scope: !371)
!469 = !DILocation(line: 106, column: 9, scope: !470)
!470 = distinct !DILexicalBlock(scope: !371, file: !1, line: 106, column: 7)
!471 = !DILocation(line: 106, column: 16, scope: !470)
!472 = !DILocation(line: 106, column: 7, scope: !470)
!473 = !DILocation(line: 106, column: 20, scope: !470)
!474 = !DILocation(line: 106, column: 7, scope: !371)
!475 = !DILocation(line: 107, column: 4, scope: !470)
!476 = !DILocation(line: 112, column: 7, scope: !477)
!477 = distinct !DILexicalBlock(scope: !371, file: !1, line: 112, column: 7)
!478 = !DILocation(line: 112, column: 14, scope: !477)
!479 = !DILocation(line: 113, column: 5, scope: !477)
!480 = !DILocation(line: 113, column: 8, scope: !481)
!481 = !DILexicalBlockFile(scope: !477, file: !1, discriminator: 1)
!482 = !DILocation(line: 113, column: 15, scope: !481)
!483 = !DILocation(line: 113, column: 33, scope: !481)
!484 = !DILocation(line: 114, column: 5, scope: !477)
!485 = !DILocation(line: 114, column: 8, scope: !481)
!486 = !DILocation(line: 114, column: 15, scope: !481)
!487 = !DILocation(line: 115, column: 6, scope: !477)
!488 = !DILocation(line: 112, column: 7, scope: !489)
!489 = !DILexicalBlockFile(scope: !371, file: !1, discriminator: 1)
!490 = !DILocation(line: 116, column: 4, scope: !477)
!491 = !DILocation(line: 120, column: 49, scope: !371)
!492 = !DILocation(line: 120, column: 56, scope: !371)
!493 = !DILocation(line: 120, column: 48, scope: !371)
!494 = !DILocation(line: 120, column: 21, scope: !371)
!495 = !DILocation(line: 121, column: 5, scope: !371)
!496 = !DILocation(line: 120, column: 3, scope: !371)
!497 = !DILocation(line: 120, column: 10, scope: !371)
!498 = !DILocation(line: 120, column: 19, scope: !371)
!499 = !DILocation(line: 123, column: 3, scope: !371)
!500 = !DILocation(line: 123, column: 10, scope: !371)
!501 = !DILocation(line: 123, column: 14, scope: !371)
!502 = !DILocation(line: 124, column: 3, scope: !371)
!503 = !DILocation(line: 124, column: 10, scope: !371)
!504 = !DILocation(line: 124, column: 19, scope: !371)
!505 = !DILocalVariable(name: "ret", scope: !506, file: !1, line: 129, type: !42)
!506 = distinct !DILexicalBlock(scope: !371, file: !1, line: 128, column: 23)
!507 = !DILocation(line: 129, column: 12, scope: !506)
!508 = !DILocalVariable(name: "filters", scope: !506, file: !1, line: 131, type: !509)
!509 = !DICompositeType(tag: DW_TAG_array_type, baseType: !510, size: 384, align: 64, elements: !522)
!510 = !DIDerivedType(tag: DW_TAG_typedef, name: "lzma_filter_info", file: !23, line: 77, baseType: !511)
!511 = !DICompositeType(tag: DW_TAG_structure_type, name: "lzma_filter_info_s", file: !23, line: 104, size: 192, align: 64, elements: !512)
!512 = !{!513, !514, !521}
!513 = !DIDerivedType(tag: DW_TAG_member, name: "id", scope: !511, file: !23, line: 107, baseType: !30, size: 64, align: 64)
!514 = !DIDerivedType(tag: DW_TAG_member, name: "init", scope: !511, file: !23, line: 111, baseType: !515, size: 64, align: 64, offset: 64)
!515 = !DIDerivedType(tag: DW_TAG_typedef, name: "lzma_init_function", file: !23, line: 81, baseType: !516)
!516 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !517, size: 64, align: 64)
!517 = !DISubroutineType(types: !518)
!518 = !{!42, !195, !43, !519}
!519 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !520, size: 64, align: 64)
!520 = !DIDerivedType(tag: DW_TAG_const_type, baseType: !510)
!521 = !DIDerivedType(tag: DW_TAG_member, name: "options", scope: !511, file: !23, line: 114, baseType: !51, size: 64, align: 64, offset: 128)
!522 = !{!523}
!523 = !DISubrange(count: 2)
!524 = !DILocation(line: 131, column: 20, scope: !506)
!525 = !DILocation(line: 131, column: 33, scope: !506)
!526 = !DILocation(line: 132, column: 4, scope: !506)
!527 = !DILocation(line: 132, column: 35, scope: !506)
!528 = !DILocation(line: 132, column: 42, scope: !506)
!529 = !DILocation(line: 132, column: 34, scope: !506)
!530 = !DILocation(line: 133, column: 4, scope: !506)
!531 = !DILocation(line: 136, column: 7, scope: !532)
!532 = distinct !DILexicalBlock(scope: !506, file: !1, line: 136, column: 7)
!533 = !DILocation(line: 136, column: 14, scope: !532)
!534 = !DILocation(line: 136, column: 25, scope: !532)
!535 = !DILocation(line: 136, column: 32, scope: !532)
!536 = !DILocation(line: 136, column: 23, scope: !532)
!537 = !DILocation(line: 136, column: 7, scope: !506)
!538 = !DILocation(line: 137, column: 4, scope: !532)
!539 = !DILocation(line: 139, column: 32, scope: !506)
!540 = !DILocation(line: 139, column: 39, scope: !506)
!541 = !DILocation(line: 140, column: 5, scope: !506)
!542 = !DILocation(line: 140, column: 16, scope: !506)
!543 = !DILocation(line: 139, column: 9, scope: !506)
!544 = !DILocation(line: 139, column: 7, scope: !506)
!545 = !DILocation(line: 141, column: 7, scope: !546)
!546 = distinct !DILexicalBlock(scope: !506, file: !1, line: 141, column: 7)
!547 = !DILocation(line: 141, column: 11, scope: !546)
!548 = !DILocation(line: 141, column: 7, scope: !506)
!549 = !DILocation(line: 142, column: 11, scope: !546)
!550 = !DILocation(line: 142, column: 4, scope: !546)
!551 = !DILocation(line: 145, column: 32, scope: !506)
!552 = !DILocation(line: 145, column: 39, scope: !506)
!553 = !DILocation(line: 145, column: 44, scope: !506)
!554 = !DILocation(line: 146, column: 5, scope: !506)
!555 = !DILocation(line: 146, column: 12, scope: !506)
!556 = !DILocation(line: 145, column: 3, scope: !506)
!557 = !DILocation(line: 148, column: 3, scope: !506)
!558 = !DILocation(line: 148, column: 10, scope: !506)
!559 = !DILocation(line: 148, column: 19, scope: !506)
!560 = !DILocation(line: 149, column: 3, scope: !506)
!561 = !DILocation(line: 153, column: 10, scope: !562)
!562 = distinct !DILexicalBlock(scope: !371, file: !1, line: 152, column: 17)
!563 = !DILocation(line: 153, column: 17, scope: !562)
!564 = !DILocation(line: 153, column: 22, scope: !562)
!565 = !DILocation(line: 153, column: 27, scope: !562)
!566 = !DILocation(line: 153, column: 34, scope: !562)
!567 = !DILocation(line: 153, column: 39, scope: !562)
!568 = !DILocation(line: 154, column: 5, scope: !562)
!569 = !DILocation(line: 154, column: 16, scope: !562)
!570 = !DILocation(line: 154, column: 20, scope: !562)
!571 = !DILocation(line: 154, column: 28, scope: !562)
!572 = !DILocation(line: 155, column: 5, scope: !562)
!573 = !DILocation(line: 155, column: 10, scope: !562)
!574 = !DILocation(line: 155, column: 19, scope: !562)
!575 = !DILocation(line: 155, column: 29, scope: !562)
!576 = !DILocation(line: 153, column: 3, scope: !562)
!577 = !DILocation(line: 159, column: 3, scope: !371)
!578 = !DILocation(line: 60, column: 2, scope: !579)
!579 = !DILexicalBlockFile(scope: !224, file: !1, discriminator: 3)
!580 = !DILocation(line: 162, column: 2, scope: !224)
!581 = !DILocation(line: 163, column: 1, scope: !224)
!582 = !DILocalVariable(name: "coder", arg: 1, scope: !225, file: !1, line: 167, type: !27)
!583 = !DILocation(line: 167, column: 31, scope: !225)
!584 = !DILocalVariable(name: "allocator", arg: 2, scope: !225, file: !1, line: 167, type: !43)
!585 = !DILocation(line: 167, column: 54, scope: !225)
!586 = !DILocation(line: 169, column: 17, scope: !225)
!587 = !DILocation(line: 169, column: 24, scope: !225)
!588 = !DILocation(line: 169, column: 30, scope: !225)
!589 = !DILocation(line: 169, column: 2, scope: !225)
!590 = !DILocation(line: 170, column: 12, scope: !225)
!591 = !DILocation(line: 170, column: 19, scope: !225)
!592 = !DILocation(line: 170, column: 2, scope: !225)
!593 = !DILocation(line: 171, column: 2, scope: !225)
!594 = !DILocalVariable(name: "coder", arg: 1, scope: !226, file: !1, line: 176, type: !27)
!595 = !DILocation(line: 176, column: 37, scope: !226)
!596 = !DILocalVariable(name: "memusage", arg: 2, scope: !226, file: !1, line: 176, type: !98)
!597 = !DILocation(line: 176, column: 54, scope: !226)
!598 = !DILocalVariable(name: "old_memlimit", arg: 3, scope: !226, file: !1, line: 177, type: !98)
!599 = !DILocation(line: 177, column: 13, scope: !226)
!600 = !DILocalVariable(name: "new_memlimit", arg: 4, scope: !226, file: !1, line: 177, type: !32)
!601 = !DILocation(line: 177, column: 36, scope: !226)
!602 = !DILocation(line: 179, column: 14, scope: !226)
!603 = !DILocation(line: 179, column: 21, scope: !226)
!604 = !DILocation(line: 179, column: 3, scope: !226)
!605 = !DILocation(line: 179, column: 12, scope: !226)
!606 = !DILocation(line: 180, column: 18, scope: !226)
!607 = !DILocation(line: 180, column: 25, scope: !226)
!608 = !DILocation(line: 180, column: 3, scope: !226)
!609 = !DILocation(line: 180, column: 16, scope: !226)
!610 = !DILocation(line: 182, column: 6, scope: !611)
!611 = distinct !DILexicalBlock(scope: !226, file: !1, line: 182, column: 6)
!612 = !DILocation(line: 182, column: 19, scope: !611)
!613 = !DILocation(line: 182, column: 6, scope: !226)
!614 = !DILocation(line: 183, column: 7, scope: !615)
!615 = distinct !DILexicalBlock(scope: !616, file: !1, line: 183, column: 7)
!616 = distinct !DILexicalBlock(scope: !611, file: !1, line: 182, column: 25)
!617 = !DILocation(line: 183, column: 22, scope: !615)
!618 = !DILocation(line: 183, column: 29, scope: !615)
!619 = !DILocation(line: 183, column: 20, scope: !615)
!620 = !DILocation(line: 183, column: 7, scope: !616)
!621 = !DILocation(line: 184, column: 4, scope: !615)
!622 = !DILocation(line: 186, column: 21, scope: !616)
!623 = !DILocation(line: 186, column: 3, scope: !616)
!624 = !DILocation(line: 186, column: 10, scope: !616)
!625 = !DILocation(line: 186, column: 19, scope: !616)
!626 = !DILocation(line: 187, column: 2, scope: !616)
!627 = !DILocation(line: 189, column: 2, scope: !226)
!628 = !DILocation(line: 190, column: 1, scope: !226)
!629 = !DILocalVariable(name: "strm", arg: 1, scope: !197, file: !1, line: 228, type: !200)
!630 = !DILocation(line: 228, column: 33, scope: !197)
!631 = !DILocalVariable(name: "memlimit", arg: 2, scope: !197, file: !1, line: 228, type: !32)
!632 = !DILocation(line: 228, column: 48, scope: !197)
!633 = !DILocation(line: 230, column: 2, scope: !197)
!634 = !DILocalVariable(name: "ret_", scope: !635, file: !1, line: 230, type: !42)
!635 = distinct !DILexicalBlock(scope: !197, file: !1, line: 230, column: 2)
!636 = !DILocation(line: 230, column: 2, scope: !635)
!637 = !DILocation(line: 230, column: 2, scope: !638)
!638 = !DILexicalBlockFile(scope: !635, file: !1, discriminator: 1)
!639 = !DILocalVariable(name: "ret_", scope: !640, file: !1, line: 230, type: !641)
!640 = distinct !DILexicalBlock(scope: !635, file: !1, line: 230, column: 2)
!641 = !DIDerivedType(tag: DW_TAG_const_type, baseType: !42)
!642 = !DILocation(line: 230, column: 2, scope: !640)
!643 = !DILocation(line: 230, column: 2, scope: !644)
!644 = !DILexicalBlockFile(scope: !640, file: !1, discriminator: 2)
!645 = !DILocation(line: 230, column: 2, scope: !646)
!646 = !DILexicalBlockFile(scope: !647, file: !1, discriminator: 3)
!647 = distinct !DILexicalBlock(scope: !640, file: !1, line: 230, column: 2)
!648 = !DILocation(line: 230, column: 2, scope: !649)
!649 = !DILexicalBlockFile(scope: !640, file: !1, discriminator: 4)
!650 = !DILocation(line: 230, column: 2, scope: !651)
!651 = !DILexicalBlockFile(scope: !635, file: !1, discriminator: 5)
!652 = !DILocation(line: 230, column: 2, scope: !653)
!653 = !DILexicalBlockFile(scope: !654, file: !1, discriminator: 6)
!654 = distinct !DILexicalBlock(scope: !655, file: !1, line: 230, column: 2)
!655 = distinct !DILexicalBlock(scope: !635, file: !1, line: 230, column: 2)
!656 = !DILocation(line: 230, column: 2, scope: !657)
!657 = !DILexicalBlockFile(scope: !635, file: !1, discriminator: 7)
!658 = !DILocation(line: 232, column: 2, scope: !197)
!659 = !DILocation(line: 232, column: 8, scope: !197)
!660 = !DILocation(line: 232, column: 18, scope: !197)
!661 = !DILocation(line: 232, column: 46, scope: !197)
!662 = !DILocation(line: 233, column: 2, scope: !197)
!663 = !DILocation(line: 233, column: 8, scope: !197)
!664 = !DILocation(line: 233, column: 18, scope: !197)
!665 = !DILocation(line: 233, column: 49, scope: !197)
!666 = !DILocation(line: 235, column: 2, scope: !197)
!667 = !DILocation(line: 236, column: 1, scope: !197)
