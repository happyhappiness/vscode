; ModuleID = '/data/download/cmake/cmake-master/Utilities/cmliblzma/liblzma/lz/lz_encoder.c'
target datalayout = "e-m:e-i64:64-f80:128-n8:16:32:64-S128"
target triple = "x86_64-unknown-linux-gnu"

%struct.lzma_next_coder_s = type { %struct.lzma_coder_s*, i64, i64, i32 (%struct.lzma_coder_s*, %struct.lzma_allocator*, i8*, i64*, i64, i8*, i64*, i64, i32)*, void (%struct.lzma_coder_s*, %struct.lzma_allocator*)*, i32 (%struct.lzma_coder_s*)*, i32 (%struct.lzma_coder_s*, i64*, i64*, i64)*, i32 (%struct.lzma_coder_s*, %struct.lzma_allocator*, %struct.lzma_filter*, %struct.lzma_filter*)* }
%struct.lzma_coder_s = type { %struct.lzma_lz_encoder, %struct.lzma_mf_s, %struct.lzma_next_coder_s }
%struct.lzma_lz_encoder = type { %struct.lzma_coder_s*, i32 (%struct.lzma_coder_s*, %struct.lzma_mf_s*, i8*, i64*, i64)*, void (%struct.lzma_coder_s*, %struct.lzma_allocator*)*, i32 (%struct.lzma_coder_s*, %struct.lzma_filter*)* }
%struct.lzma_filter = type { i64, i8* }
%struct.lzma_mf_s = type { i8*, i32, i32, i32, i32, i32, i32, i32, i32, i32, i32 (%struct.lzma_mf_s*, %struct.lzma_match*)*, void (%struct.lzma_mf_s*, i32)*, i32*, i32*, i32, i32, i32, i32, i32, i32, i32, i32, i32 }
%struct.lzma_match = type { i32, i32 }
%struct.lzma_allocator = type { i8* (i8*, i64, i64)*, void (i8*, i8*)*, i8* }
%struct.lzma_lz_options = type { i64, i64, i64, i64, i64, i32, i32, i8*, i32 }
%struct.lzma_filter_info_s = type { i64, i32 (%struct.lzma_next_coder_s*, %struct.lzma_allocator*, %struct.lzma_filter_info_s*)*, i8* }

@LZMA_NEXT_CODER_INIT = internal constant %struct.lzma_next_coder_s { %struct.lzma_coder_s* null, i64 -1, i64 0, i32 (%struct.lzma_coder_s*, %struct.lzma_allocator*, i8*, i64*, i64, i8*, i64*, i64, i32)* null, void (%struct.lzma_coder_s*, %struct.lzma_allocator*)* null, i32 (%struct.lzma_coder_s*)* null, i32 (%struct.lzma_coder_s*, i64*, i64*, i64)* null, i32 (%struct.lzma_coder_s*, %struct.lzma_allocator*, %struct.lzma_filter*, %struct.lzma_filter*)* null }, align 8
@.str = private unnamed_addr constant [23 x i8] c"hs < (4294967295U) / 5\00", align 1
@.str.1 = private unnamed_addr constant [78 x i8] c"/data/download/cmake/cmake-master/Utilities/cmliblzma/liblzma/lz/lz_encoder.c\00", align 1
@__PRETTY_FUNCTION__.lz_encoder_prepare = private unnamed_addr constant [79 x i8] c"_Bool lz_encoder_prepare(lzma_mf *, lzma_allocator *, const lzma_lz_options *)\00", align 1
@.str.2 = private unnamed_addr constant [42 x i8] c"coder->mf.read_pos <= coder->mf.write_pos\00", align 1
@__PRETTY_FUNCTION__.fill_window = private unnamed_addr constant [101 x i8] c"lzma_ret fill_window(lzma_coder *, lzma_allocator *, const uint8_t *, size_t *, size_t, lzma_action)\00", align 1
@.str.3 = private unnamed_addr constant [19 x i8] c"*in_pos == in_size\00", align 1
@.str.4 = private unnamed_addr constant [30 x i8] c"coder->mf.read_pos >= pending\00", align 1
@.str.5 = private unnamed_addr constant [36 x i8] c"mf->read_pos > mf->keep_size_before\00", align 1
@__PRETTY_FUNCTION__.move_window = private unnamed_addr constant [28 x i8] c"void move_window(lzma_mf *)\00", align 1
@.str.6 = private unnamed_addr constant [28 x i8] c"mf->write_pos > move_offset\00", align 1
@.str.7 = private unnamed_addr constant [36 x i8] c"move_offset + move_size <= mf->size\00", align 1

; Function Attrs: nounwind uwtable
define i64 @lzma_lz_encoder_memusage(%struct.lzma_lz_options* %lz_options) #0 !dbg !47 {
entry:
  %retval = alloca i64, align 8
  %lz_options.addr = alloca %struct.lzma_lz_options*, align 8
  %mf = alloca %struct.lzma_mf_s, align 8
  store %struct.lzma_lz_options* %lz_options, %struct.lzma_lz_options** %lz_options.addr, align 8
  call void @llvm.dbg.declare(metadata %struct.lzma_lz_options** %lz_options.addr, metadata !246, metadata !247), !dbg !248
  call void @llvm.dbg.declare(metadata %struct.lzma_mf_s* %mf, metadata !249, metadata !247), !dbg !250
  %0 = bitcast %struct.lzma_mf_s* %mf to i8*, !dbg !250
  call void @llvm.memset.p0i8.i64(i8* %0, i8 0, i64 120, i32 8, i1 false), !dbg !250
  %1 = load %struct.lzma_lz_options*, %struct.lzma_lz_options** %lz_options.addr, align 8, !dbg !251
  %call = call zeroext i1 @lz_encoder_prepare(%struct.lzma_mf_s* %mf, %struct.lzma_allocator* null, %struct.lzma_lz_options* %1), !dbg !253
  br i1 %call, label %if.then, label %if.end, !dbg !254

if.then:                                          ; preds = %entry
  store i64 -1, i64* %retval, align 8, !dbg !255
  br label %return, !dbg !255

if.end:                                           ; preds = %entry
  %hash_size_sum = getelementptr inbounds %struct.lzma_mf_s, %struct.lzma_mf_s* %mf, i32 0, i32 21, !dbg !256
  %2 = load i32, i32* %hash_size_sum, align 4, !dbg !256
  %sons_count = getelementptr inbounds %struct.lzma_mf_s, %struct.lzma_mf_s* %mf, i32 0, i32 22, !dbg !257
  %3 = load i32, i32* %sons_count, align 8, !dbg !257
  %add = add i32 %2, %3, !dbg !258
  %conv = zext i32 %add to i64, !dbg !259
  %mul = mul i64 %conv, 4, !dbg !260
  %size = getelementptr inbounds %struct.lzma_mf_s, %struct.lzma_mf_s* %mf, i32 0, i32 1, !dbg !261
  %4 = load i32, i32* %size, align 8, !dbg !261
  %conv1 = zext i32 %4 to i64, !dbg !262
  %add2 = add i64 %mul, %conv1, !dbg !263
  %add3 = add i64 %add2, 216, !dbg !264
  store i64 %add3, i64* %retval, align 8, !dbg !265
  br label %return, !dbg !265

return:                                           ; preds = %if.end, %if.then
  %5 = load i64, i64* %retval, align 8, !dbg !266
  ret i64 %5, !dbg !266
}

; Function Attrs: nounwind readnone
declare void @llvm.dbg.declare(metadata, metadata, metadata) #1

; Function Attrs: argmemonly nounwind
declare void @llvm.memset.p0i8.i64(i8* nocapture, i8, i64, i32, i1) #2

; Function Attrs: nounwind uwtable
define internal zeroext i1 @lz_encoder_prepare(%struct.lzma_mf_s* %mf, %struct.lzma_allocator* %allocator, %struct.lzma_lz_options* %lz_options) #0 !dbg !226 {
entry:
  %retval = alloca i1, align 1
  %mf.addr = alloca %struct.lzma_mf_s*, align 8
  %allocator.addr = alloca %struct.lzma_allocator*, align 8
  %lz_options.addr = alloca %struct.lzma_lz_options*, align 8
  %is_bt = alloca i8, align 1
  %new_count = alloca i32, align 4
  %reserve = alloca i32, align 4
  %old_size = alloca i32, align 4
  %hash_bytes = alloca i32, align 4
  %hs = alloca i32, align 4
  %old_count = alloca i32, align 4
  store %struct.lzma_mf_s* %mf, %struct.lzma_mf_s** %mf.addr, align 8
  call void @llvm.dbg.declare(metadata %struct.lzma_mf_s** %mf.addr, metadata !267, metadata !247), !dbg !268
  store %struct.lzma_allocator* %allocator, %struct.lzma_allocator** %allocator.addr, align 8
  call void @llvm.dbg.declare(metadata %struct.lzma_allocator** %allocator.addr, metadata !269, metadata !247), !dbg !270
  store %struct.lzma_lz_options* %lz_options, %struct.lzma_lz_options** %lz_options.addr, align 8
  call void @llvm.dbg.declare(metadata %struct.lzma_lz_options** %lz_options.addr, metadata !271, metadata !247), !dbg !272
  call void @llvm.dbg.declare(metadata i8* %is_bt, metadata !273, metadata !247), !dbg !274
  call void @llvm.dbg.declare(metadata i32* %new_count, metadata !275, metadata !247), !dbg !276
  call void @llvm.dbg.declare(metadata i32* %reserve, metadata !277, metadata !247), !dbg !278
  call void @llvm.dbg.declare(metadata i32* %old_size, metadata !279, metadata !247), !dbg !280
  call void @llvm.dbg.declare(metadata i32* %hash_bytes, metadata !281, metadata !247), !dbg !282
  call void @llvm.dbg.declare(metadata i32* %hs, metadata !283, metadata !247), !dbg !284
  call void @llvm.dbg.declare(metadata i32* %old_count, metadata !285, metadata !247), !dbg !286
  %0 = load %struct.lzma_lz_options*, %struct.lzma_lz_options** %lz_options.addr, align 8, !dbg !287
  %dict_size = getelementptr inbounds %struct.lzma_lz_options, %struct.lzma_lz_options* %0, i32 0, i32 1, !dbg !289
  %1 = load i64, i64* %dict_size, align 8, !dbg !289
  %cmp = icmp ult i64 %1, 4096, !dbg !290
  br i1 %cmp, label %if.then, label %lor.lhs.false, !dbg !291

lor.lhs.false:                                    ; preds = %entry
  %2 = load %struct.lzma_lz_options*, %struct.lzma_lz_options** %lz_options.addr, align 8, !dbg !292
  %dict_size1 = getelementptr inbounds %struct.lzma_lz_options, %struct.lzma_lz_options* %2, i32 0, i32 1, !dbg !294
  %3 = load i64, i64* %dict_size1, align 8, !dbg !294
  %cmp2 = icmp ugt i64 %3, 1610612736, !dbg !295
  br i1 %cmp2, label %if.then, label %lor.lhs.false3, !dbg !296

lor.lhs.false3:                                   ; preds = %lor.lhs.false
  %4 = load %struct.lzma_lz_options*, %struct.lzma_lz_options** %lz_options.addr, align 8, !dbg !297
  %nice_len = getelementptr inbounds %struct.lzma_lz_options, %struct.lzma_lz_options* %4, i32 0, i32 4, !dbg !298
  %5 = load i64, i64* %nice_len, align 8, !dbg !298
  %6 = load %struct.lzma_lz_options*, %struct.lzma_lz_options** %lz_options.addr, align 8, !dbg !299
  %match_len_max = getelementptr inbounds %struct.lzma_lz_options, %struct.lzma_lz_options* %6, i32 0, i32 3, !dbg !300
  %7 = load i64, i64* %match_len_max, align 8, !dbg !300
  %cmp4 = icmp ugt i64 %5, %7, !dbg !301
  br i1 %cmp4, label %if.then, label %if.end, !dbg !302

if.then:                                          ; preds = %lor.lhs.false3, %lor.lhs.false, %entry
  store i1 true, i1* %retval, align 1, !dbg !304
  br label %return, !dbg !304

if.end:                                           ; preds = %lor.lhs.false3
  %8 = load %struct.lzma_lz_options*, %struct.lzma_lz_options** %lz_options.addr, align 8, !dbg !305
  %before_size = getelementptr inbounds %struct.lzma_lz_options, %struct.lzma_lz_options* %8, i32 0, i32 0, !dbg !306
  %9 = load i64, i64* %before_size, align 8, !dbg !306
  %10 = load %struct.lzma_lz_options*, %struct.lzma_lz_options** %lz_options.addr, align 8, !dbg !307
  %dict_size5 = getelementptr inbounds %struct.lzma_lz_options, %struct.lzma_lz_options* %10, i32 0, i32 1, !dbg !308
  %11 = load i64, i64* %dict_size5, align 8, !dbg !308
  %add = add i64 %9, %11, !dbg !309
  %conv = trunc i64 %add to i32, !dbg !305
  %12 = load %struct.lzma_mf_s*, %struct.lzma_mf_s** %mf.addr, align 8, !dbg !310
  %keep_size_before = getelementptr inbounds %struct.lzma_mf_s, %struct.lzma_mf_s* %12, i32 0, i32 2, !dbg !311
  store i32 %conv, i32* %keep_size_before, align 4, !dbg !312
  %13 = load %struct.lzma_lz_options*, %struct.lzma_lz_options** %lz_options.addr, align 8, !dbg !313
  %after_size = getelementptr inbounds %struct.lzma_lz_options, %struct.lzma_lz_options* %13, i32 0, i32 2, !dbg !314
  %14 = load i64, i64* %after_size, align 8, !dbg !314
  %15 = load %struct.lzma_lz_options*, %struct.lzma_lz_options** %lz_options.addr, align 8, !dbg !315
  %match_len_max6 = getelementptr inbounds %struct.lzma_lz_options, %struct.lzma_lz_options* %15, i32 0, i32 3, !dbg !316
  %16 = load i64, i64* %match_len_max6, align 8, !dbg !316
  %add7 = add i64 %14, %16, !dbg !317
  %conv8 = trunc i64 %add7 to i32, !dbg !313
  %17 = load %struct.lzma_mf_s*, %struct.lzma_mf_s** %mf.addr, align 8, !dbg !318
  %keep_size_after = getelementptr inbounds %struct.lzma_mf_s, %struct.lzma_mf_s* %17, i32 0, i32 3, !dbg !319
  store i32 %conv8, i32* %keep_size_after, align 8, !dbg !320
  %18 = load %struct.lzma_lz_options*, %struct.lzma_lz_options** %lz_options.addr, align 8, !dbg !321
  %dict_size9 = getelementptr inbounds %struct.lzma_lz_options, %struct.lzma_lz_options* %18, i32 0, i32 1, !dbg !322
  %19 = load i64, i64* %dict_size9, align 8, !dbg !322
  %div = udiv i64 %19, 2, !dbg !323
  %conv10 = trunc i64 %div to i32, !dbg !321
  store i32 %conv10, i32* %reserve, align 4, !dbg !324
  %20 = load i32, i32* %reserve, align 4, !dbg !325
  %cmp11 = icmp ugt i32 %20, 1073741824, !dbg !327
  br i1 %cmp11, label %if.then13, label %if.end15, !dbg !328

if.then13:                                        ; preds = %if.end
  %21 = load i32, i32* %reserve, align 4, !dbg !329
  %div14 = udiv i32 %21, 2, !dbg !329
  store i32 %div14, i32* %reserve, align 4, !dbg !329
  br label %if.end15, !dbg !330

if.end15:                                         ; preds = %if.then13, %if.end
  %22 = load %struct.lzma_lz_options*, %struct.lzma_lz_options** %lz_options.addr, align 8, !dbg !331
  %before_size16 = getelementptr inbounds %struct.lzma_lz_options, %struct.lzma_lz_options* %22, i32 0, i32 0, !dbg !332
  %23 = load i64, i64* %before_size16, align 8, !dbg !332
  %24 = load %struct.lzma_lz_options*, %struct.lzma_lz_options** %lz_options.addr, align 8, !dbg !333
  %match_len_max17 = getelementptr inbounds %struct.lzma_lz_options, %struct.lzma_lz_options* %24, i32 0, i32 3, !dbg !334
  %25 = load i64, i64* %match_len_max17, align 8, !dbg !334
  %add18 = add i64 %23, %25, !dbg !335
  %26 = load %struct.lzma_lz_options*, %struct.lzma_lz_options** %lz_options.addr, align 8, !dbg !336
  %after_size19 = getelementptr inbounds %struct.lzma_lz_options, %struct.lzma_lz_options* %26, i32 0, i32 2, !dbg !337
  %27 = load i64, i64* %after_size19, align 8, !dbg !337
  %add20 = add i64 %add18, %27, !dbg !338
  %div21 = udiv i64 %add20, 2, !dbg !339
  %add22 = add i64 %div21, 524288, !dbg !340
  %28 = load i32, i32* %reserve, align 4, !dbg !341
  %conv23 = zext i32 %28 to i64, !dbg !341
  %add24 = add i64 %conv23, %add22, !dbg !341
  %conv25 = trunc i64 %add24 to i32, !dbg !341
  store i32 %conv25, i32* %reserve, align 4, !dbg !341
  %29 = load %struct.lzma_mf_s*, %struct.lzma_mf_s** %mf.addr, align 8, !dbg !342
  %size = getelementptr inbounds %struct.lzma_mf_s, %struct.lzma_mf_s* %29, i32 0, i32 1, !dbg !343
  %30 = load i32, i32* %size, align 8, !dbg !343
  store i32 %30, i32* %old_size, align 4, !dbg !344
  %31 = load %struct.lzma_mf_s*, %struct.lzma_mf_s** %mf.addr, align 8, !dbg !345
  %keep_size_before26 = getelementptr inbounds %struct.lzma_mf_s, %struct.lzma_mf_s* %31, i32 0, i32 2, !dbg !346
  %32 = load i32, i32* %keep_size_before26, align 4, !dbg !346
  %33 = load i32, i32* %reserve, align 4, !dbg !347
  %add27 = add i32 %32, %33, !dbg !348
  %34 = load %struct.lzma_mf_s*, %struct.lzma_mf_s** %mf.addr, align 8, !dbg !349
  %keep_size_after28 = getelementptr inbounds %struct.lzma_mf_s, %struct.lzma_mf_s* %34, i32 0, i32 3, !dbg !350
  %35 = load i32, i32* %keep_size_after28, align 8, !dbg !350
  %add29 = add i32 %add27, %35, !dbg !351
  %36 = load %struct.lzma_mf_s*, %struct.lzma_mf_s** %mf.addr, align 8, !dbg !352
  %size30 = getelementptr inbounds %struct.lzma_mf_s, %struct.lzma_mf_s* %36, i32 0, i32 1, !dbg !353
  store i32 %add29, i32* %size30, align 8, !dbg !354
  %37 = load %struct.lzma_mf_s*, %struct.lzma_mf_s** %mf.addr, align 8, !dbg !355
  %buffer = getelementptr inbounds %struct.lzma_mf_s, %struct.lzma_mf_s* %37, i32 0, i32 0, !dbg !357
  %38 = load i8*, i8** %buffer, align 8, !dbg !357
  %cmp31 = icmp ne i8* %38, null, !dbg !358
  br i1 %cmp31, label %land.lhs.true, label %if.end39, !dbg !359

land.lhs.true:                                    ; preds = %if.end15
  %39 = load i32, i32* %old_size, align 4, !dbg !360
  %40 = load %struct.lzma_mf_s*, %struct.lzma_mf_s** %mf.addr, align 8, !dbg !362
  %size33 = getelementptr inbounds %struct.lzma_mf_s, %struct.lzma_mf_s* %40, i32 0, i32 1, !dbg !363
  %41 = load i32, i32* %size33, align 8, !dbg !363
  %cmp34 = icmp ne i32 %39, %41, !dbg !364
  br i1 %cmp34, label %if.then36, label %if.end39, !dbg !365

if.then36:                                        ; preds = %land.lhs.true
  %42 = load %struct.lzma_mf_s*, %struct.lzma_mf_s** %mf.addr, align 8, !dbg !366
  %buffer37 = getelementptr inbounds %struct.lzma_mf_s, %struct.lzma_mf_s* %42, i32 0, i32 0, !dbg !368
  %43 = load i8*, i8** %buffer37, align 8, !dbg !368
  %44 = load %struct.lzma_allocator*, %struct.lzma_allocator** %allocator.addr, align 8, !dbg !369
  call void @lzma_free(i8* %43, %struct.lzma_allocator* %44), !dbg !370
  %45 = load %struct.lzma_mf_s*, %struct.lzma_mf_s** %mf.addr, align 8, !dbg !371
  %buffer38 = getelementptr inbounds %struct.lzma_mf_s, %struct.lzma_mf_s* %45, i32 0, i32 0, !dbg !372
  store i8* null, i8** %buffer38, align 8, !dbg !373
  br label %if.end39, !dbg !374

if.end39:                                         ; preds = %if.then36, %land.lhs.true, %if.end15
  %46 = load %struct.lzma_lz_options*, %struct.lzma_lz_options** %lz_options.addr, align 8, !dbg !375
  %match_len_max40 = getelementptr inbounds %struct.lzma_lz_options, %struct.lzma_lz_options* %46, i32 0, i32 3, !dbg !376
  %47 = load i64, i64* %match_len_max40, align 8, !dbg !376
  %conv41 = trunc i64 %47 to i32, !dbg !375
  %48 = load %struct.lzma_mf_s*, %struct.lzma_mf_s** %mf.addr, align 8, !dbg !377
  %match_len_max42 = getelementptr inbounds %struct.lzma_mf_s, %struct.lzma_mf_s* %48, i32 0, i32 19, !dbg !378
  store i32 %conv41, i32* %match_len_max42, align 4, !dbg !379
  %49 = load %struct.lzma_lz_options*, %struct.lzma_lz_options** %lz_options.addr, align 8, !dbg !380
  %nice_len43 = getelementptr inbounds %struct.lzma_lz_options, %struct.lzma_lz_options* %49, i32 0, i32 4, !dbg !381
  %50 = load i64, i64* %nice_len43, align 8, !dbg !381
  %conv44 = trunc i64 %50 to i32, !dbg !380
  %51 = load %struct.lzma_mf_s*, %struct.lzma_mf_s** %mf.addr, align 8, !dbg !382
  %nice_len45 = getelementptr inbounds %struct.lzma_mf_s, %struct.lzma_mf_s* %51, i32 0, i32 18, !dbg !383
  store i32 %conv44, i32* %nice_len45, align 8, !dbg !384
  %52 = load %struct.lzma_lz_options*, %struct.lzma_lz_options** %lz_options.addr, align 8, !dbg !385
  %dict_size46 = getelementptr inbounds %struct.lzma_lz_options, %struct.lzma_lz_options* %52, i32 0, i32 1, !dbg !386
  %53 = load i64, i64* %dict_size46, align 8, !dbg !386
  %add47 = add i64 %53, 1, !dbg !387
  %conv48 = trunc i64 %add47 to i32, !dbg !385
  %54 = load %struct.lzma_mf_s*, %struct.lzma_mf_s** %mf.addr, align 8, !dbg !388
  %cyclic_size = getelementptr inbounds %struct.lzma_mf_s, %struct.lzma_mf_s* %54, i32 0, i32 15, !dbg !389
  store i32 %conv48, i32* %cyclic_size, align 4, !dbg !390
  %55 = load %struct.lzma_lz_options*, %struct.lzma_lz_options** %lz_options.addr, align 8, !dbg !391
  %match_finder = getelementptr inbounds %struct.lzma_lz_options, %struct.lzma_lz_options* %55, i32 0, i32 5, !dbg !392
  %56 = load i32, i32* %match_finder, align 8, !dbg !392
  switch i32 %56, label %sw.default [
    i32 3, label %sw.bb
    i32 4, label %sw.bb49
    i32 18, label %sw.bb52
    i32 19, label %sw.bb55
    i32 20, label %sw.bb58
  ], !dbg !393

sw.bb:                                            ; preds = %if.end39
  %57 = load %struct.lzma_mf_s*, %struct.lzma_mf_s** %mf.addr, align 8, !dbg !394
  %find = getelementptr inbounds %struct.lzma_mf_s, %struct.lzma_mf_s* %57, i32 0, i32 10, !dbg !396
  store i32 (%struct.lzma_mf_s*, %struct.lzma_match*)* @lzma_mf_hc3_find, i32 (%struct.lzma_mf_s*, %struct.lzma_match*)** %find, align 8, !dbg !397
  %58 = load %struct.lzma_mf_s*, %struct.lzma_mf_s** %mf.addr, align 8, !dbg !398
  %skip = getelementptr inbounds %struct.lzma_mf_s, %struct.lzma_mf_s* %58, i32 0, i32 11, !dbg !399
  store void (%struct.lzma_mf_s*, i32)* @lzma_mf_hc3_skip, void (%struct.lzma_mf_s*, i32)** %skip, align 8, !dbg !400
  br label %sw.epilog, !dbg !401

sw.bb49:                                          ; preds = %if.end39
  %59 = load %struct.lzma_mf_s*, %struct.lzma_mf_s** %mf.addr, align 8, !dbg !402
  %find50 = getelementptr inbounds %struct.lzma_mf_s, %struct.lzma_mf_s* %59, i32 0, i32 10, !dbg !403
  store i32 (%struct.lzma_mf_s*, %struct.lzma_match*)* @lzma_mf_hc4_find, i32 (%struct.lzma_mf_s*, %struct.lzma_match*)** %find50, align 8, !dbg !404
  %60 = load %struct.lzma_mf_s*, %struct.lzma_mf_s** %mf.addr, align 8, !dbg !405
  %skip51 = getelementptr inbounds %struct.lzma_mf_s, %struct.lzma_mf_s* %60, i32 0, i32 11, !dbg !406
  store void (%struct.lzma_mf_s*, i32)* @lzma_mf_hc4_skip, void (%struct.lzma_mf_s*, i32)** %skip51, align 8, !dbg !407
  br label %sw.epilog, !dbg !408

sw.bb52:                                          ; preds = %if.end39
  %61 = load %struct.lzma_mf_s*, %struct.lzma_mf_s** %mf.addr, align 8, !dbg !409
  %find53 = getelementptr inbounds %struct.lzma_mf_s, %struct.lzma_mf_s* %61, i32 0, i32 10, !dbg !410
  store i32 (%struct.lzma_mf_s*, %struct.lzma_match*)* @lzma_mf_bt2_find, i32 (%struct.lzma_mf_s*, %struct.lzma_match*)** %find53, align 8, !dbg !411
  %62 = load %struct.lzma_mf_s*, %struct.lzma_mf_s** %mf.addr, align 8, !dbg !412
  %skip54 = getelementptr inbounds %struct.lzma_mf_s, %struct.lzma_mf_s* %62, i32 0, i32 11, !dbg !413
  store void (%struct.lzma_mf_s*, i32)* @lzma_mf_bt2_skip, void (%struct.lzma_mf_s*, i32)** %skip54, align 8, !dbg !414
  br label %sw.epilog, !dbg !415

sw.bb55:                                          ; preds = %if.end39
  %63 = load %struct.lzma_mf_s*, %struct.lzma_mf_s** %mf.addr, align 8, !dbg !416
  %find56 = getelementptr inbounds %struct.lzma_mf_s, %struct.lzma_mf_s* %63, i32 0, i32 10, !dbg !417
  store i32 (%struct.lzma_mf_s*, %struct.lzma_match*)* @lzma_mf_bt3_find, i32 (%struct.lzma_mf_s*, %struct.lzma_match*)** %find56, align 8, !dbg !418
  %64 = load %struct.lzma_mf_s*, %struct.lzma_mf_s** %mf.addr, align 8, !dbg !419
  %skip57 = getelementptr inbounds %struct.lzma_mf_s, %struct.lzma_mf_s* %64, i32 0, i32 11, !dbg !420
  store void (%struct.lzma_mf_s*, i32)* @lzma_mf_bt3_skip, void (%struct.lzma_mf_s*, i32)** %skip57, align 8, !dbg !421
  br label %sw.epilog, !dbg !422

sw.bb58:                                          ; preds = %if.end39
  %65 = load %struct.lzma_mf_s*, %struct.lzma_mf_s** %mf.addr, align 8, !dbg !423
  %find59 = getelementptr inbounds %struct.lzma_mf_s, %struct.lzma_mf_s* %65, i32 0, i32 10, !dbg !424
  store i32 (%struct.lzma_mf_s*, %struct.lzma_match*)* @lzma_mf_bt4_find, i32 (%struct.lzma_mf_s*, %struct.lzma_match*)** %find59, align 8, !dbg !425
  %66 = load %struct.lzma_mf_s*, %struct.lzma_mf_s** %mf.addr, align 8, !dbg !426
  %skip60 = getelementptr inbounds %struct.lzma_mf_s, %struct.lzma_mf_s* %66, i32 0, i32 11, !dbg !427
  store void (%struct.lzma_mf_s*, i32)* @lzma_mf_bt4_skip, void (%struct.lzma_mf_s*, i32)** %skip60, align 8, !dbg !428
  br label %sw.epilog, !dbg !429

sw.default:                                       ; preds = %if.end39
  store i1 true, i1* %retval, align 1, !dbg !430
  br label %return, !dbg !430

sw.epilog:                                        ; preds = %sw.bb58, %sw.bb55, %sw.bb52, %sw.bb49, %sw.bb
  %67 = load %struct.lzma_lz_options*, %struct.lzma_lz_options** %lz_options.addr, align 8, !dbg !431
  %match_finder61 = getelementptr inbounds %struct.lzma_lz_options, %struct.lzma_lz_options* %67, i32 0, i32 5, !dbg !432
  %68 = load i32, i32* %match_finder61, align 8, !dbg !432
  %and = and i32 %68, 15, !dbg !433
  store i32 %and, i32* %hash_bytes, align 4, !dbg !434
  %69 = load i32, i32* %hash_bytes, align 4, !dbg !435
  %70 = load %struct.lzma_mf_s*, %struct.lzma_mf_s** %mf.addr, align 8, !dbg !437
  %nice_len62 = getelementptr inbounds %struct.lzma_mf_s, %struct.lzma_mf_s* %70, i32 0, i32 18, !dbg !438
  %71 = load i32, i32* %nice_len62, align 8, !dbg !438
  %cmp63 = icmp ugt i32 %69, %71, !dbg !439
  br i1 %cmp63, label %if.then65, label %if.end66, !dbg !440

if.then65:                                        ; preds = %sw.epilog
  store i1 true, i1* %retval, align 1, !dbg !441
  br label %return, !dbg !441

if.end66:                                         ; preds = %sw.epilog
  %72 = load %struct.lzma_lz_options*, %struct.lzma_lz_options** %lz_options.addr, align 8, !dbg !442
  %match_finder67 = getelementptr inbounds %struct.lzma_lz_options, %struct.lzma_lz_options* %72, i32 0, i32 5, !dbg !443
  %73 = load i32, i32* %match_finder67, align 8, !dbg !443
  %and68 = and i32 %73, 16, !dbg !444
  %cmp69 = icmp ne i32 %and68, 0, !dbg !445
  %frombool = zext i1 %cmp69 to i8, !dbg !446
  store i8 %frombool, i8* %is_bt, align 1, !dbg !446
  %74 = load i32, i32* %hash_bytes, align 4, !dbg !447
  %cmp71 = icmp eq i32 %74, 2, !dbg !449
  br i1 %cmp71, label %if.then73, label %if.else, !dbg !450

if.then73:                                        ; preds = %if.end66
  store i32 65535, i32* %hs, align 4, !dbg !451
  br label %if.end94, !dbg !453

if.else:                                          ; preds = %if.end66
  %75 = load %struct.lzma_lz_options*, %struct.lzma_lz_options** %lz_options.addr, align 8, !dbg !454
  %dict_size74 = getelementptr inbounds %struct.lzma_lz_options, %struct.lzma_lz_options* %75, i32 0, i32 1, !dbg !456
  %76 = load i64, i64* %dict_size74, align 8, !dbg !456
  %sub = sub i64 %76, 1, !dbg !457
  %conv75 = trunc i64 %sub to i32, !dbg !454
  store i32 %conv75, i32* %hs, align 4, !dbg !458
  %77 = load i32, i32* %hs, align 4, !dbg !459
  %shr = lshr i32 %77, 1, !dbg !460
  %78 = load i32, i32* %hs, align 4, !dbg !461
  %or = or i32 %78, %shr, !dbg !461
  store i32 %or, i32* %hs, align 4, !dbg !461
  %79 = load i32, i32* %hs, align 4, !dbg !462
  %shr76 = lshr i32 %79, 2, !dbg !463
  %80 = load i32, i32* %hs, align 4, !dbg !464
  %or77 = or i32 %80, %shr76, !dbg !464
  store i32 %or77, i32* %hs, align 4, !dbg !464
  %81 = load i32, i32* %hs, align 4, !dbg !465
  %shr78 = lshr i32 %81, 4, !dbg !466
  %82 = load i32, i32* %hs, align 4, !dbg !467
  %or79 = or i32 %82, %shr78, !dbg !467
  store i32 %or79, i32* %hs, align 4, !dbg !467
  %83 = load i32, i32* %hs, align 4, !dbg !468
  %shr80 = lshr i32 %83, 8, !dbg !469
  %84 = load i32, i32* %hs, align 4, !dbg !470
  %or81 = or i32 %84, %shr80, !dbg !470
  store i32 %or81, i32* %hs, align 4, !dbg !470
  %85 = load i32, i32* %hs, align 4, !dbg !471
  %shr82 = lshr i32 %85, 1, !dbg !471
  store i32 %shr82, i32* %hs, align 4, !dbg !471
  %86 = load i32, i32* %hs, align 4, !dbg !472
  %or83 = or i32 %86, 65535, !dbg !472
  store i32 %or83, i32* %hs, align 4, !dbg !472
  %87 = load i32, i32* %hs, align 4, !dbg !473
  %cmp84 = icmp ugt i32 %87, 16777216, !dbg !475
  br i1 %cmp84, label %if.then86, label %if.end93, !dbg !476

if.then86:                                        ; preds = %if.else
  %88 = load i32, i32* %hash_bytes, align 4, !dbg !477
  %cmp87 = icmp eq i32 %88, 3, !dbg !480
  br i1 %cmp87, label %if.then89, label %if.else90, !dbg !481

if.then89:                                        ; preds = %if.then86
  store i32 16777215, i32* %hs, align 4, !dbg !482
  br label %if.end92, !dbg !483

if.else90:                                        ; preds = %if.then86
  %89 = load i32, i32* %hs, align 4, !dbg !484
  %shr91 = lshr i32 %89, 1, !dbg !484
  store i32 %shr91, i32* %hs, align 4, !dbg !484
  br label %if.end92

if.end92:                                         ; preds = %if.else90, %if.then89
  br label %if.end93, !dbg !485

if.end93:                                         ; preds = %if.end92, %if.else
  br label %if.end94

if.end94:                                         ; preds = %if.end93, %if.then73
  %90 = load i32, i32* %hs, align 4, !dbg !486
  %91 = load %struct.lzma_mf_s*, %struct.lzma_mf_s** %mf.addr, align 8, !dbg !487
  %hash_mask = getelementptr inbounds %struct.lzma_mf_s, %struct.lzma_mf_s* %91, i32 0, i32 16, !dbg !488
  store i32 %90, i32* %hash_mask, align 8, !dbg !489
  %92 = load i32, i32* %hs, align 4, !dbg !490
  %inc = add i32 %92, 1, !dbg !490
  store i32 %inc, i32* %hs, align 4, !dbg !490
  %93 = load i32, i32* %hash_bytes, align 4, !dbg !491
  %cmp95 = icmp ugt i32 %93, 2, !dbg !493
  br i1 %cmp95, label %if.then97, label %if.end99, !dbg !494

if.then97:                                        ; preds = %if.end94
  %94 = load i32, i32* %hs, align 4, !dbg !495
  %add98 = add i32 %94, 1024, !dbg !495
  store i32 %add98, i32* %hs, align 4, !dbg !495
  br label %if.end99, !dbg !496

if.end99:                                         ; preds = %if.then97, %if.end94
  %95 = load i32, i32* %hash_bytes, align 4, !dbg !497
  %cmp100 = icmp ugt i32 %95, 3, !dbg !499
  br i1 %cmp100, label %if.then102, label %if.end104, !dbg !500

if.then102:                                       ; preds = %if.end99
  %96 = load i32, i32* %hs, align 4, !dbg !501
  %add103 = add i32 %96, 65536, !dbg !501
  store i32 %add103, i32* %hs, align 4, !dbg !501
  br label %if.end104, !dbg !502

if.end104:                                        ; preds = %if.then102, %if.end99
  %97 = load i32, i32* %hs, align 4, !dbg !503
  %cmp105 = icmp ult i32 %97, 858993459, !dbg !503
  br i1 %cmp105, label %cond.true, label %cond.false, !dbg !503

cond.true:                                        ; preds = %if.end104
  br label %cond.end, !dbg !504

cond.false:                                       ; preds = %if.end104
  call void @__assert_fail(i8* getelementptr inbounds ([23 x i8], [23 x i8]* @.str, i32 0, i32 0), i8* getelementptr inbounds ([78 x i8], [78 x i8]* @.str.1, i32 0, i32 0), i32 345, i8* getelementptr inbounds ([79 x i8], [79 x i8]* @__PRETTY_FUNCTION__.lz_encoder_prepare, i32 0, i32 0)) #6, !dbg !505
  unreachable, !dbg !505
                                                  ; No predecessors!
  br label %cond.end, !dbg !507

cond.end:                                         ; preds = %98, %cond.true
  %99 = load %struct.lzma_mf_s*, %struct.lzma_mf_s** %mf.addr, align 8, !dbg !509
  %hash_size_sum = getelementptr inbounds %struct.lzma_mf_s, %struct.lzma_mf_s* %99, i32 0, i32 21, !dbg !510
  %100 = load i32, i32* %hash_size_sum, align 4, !dbg !510
  %101 = load %struct.lzma_mf_s*, %struct.lzma_mf_s** %mf.addr, align 8, !dbg !511
  %sons_count = getelementptr inbounds %struct.lzma_mf_s, %struct.lzma_mf_s* %101, i32 0, i32 22, !dbg !512
  %102 = load i32, i32* %sons_count, align 8, !dbg !512
  %add107 = add i32 %100, %102, !dbg !513
  store i32 %add107, i32* %old_count, align 4, !dbg !514
  %103 = load i32, i32* %hs, align 4, !dbg !515
  %104 = load %struct.lzma_mf_s*, %struct.lzma_mf_s** %mf.addr, align 8, !dbg !516
  %hash_size_sum108 = getelementptr inbounds %struct.lzma_mf_s, %struct.lzma_mf_s* %104, i32 0, i32 21, !dbg !517
  store i32 %103, i32* %hash_size_sum108, align 4, !dbg !518
  %105 = load %struct.lzma_mf_s*, %struct.lzma_mf_s** %mf.addr, align 8, !dbg !519
  %cyclic_size109 = getelementptr inbounds %struct.lzma_mf_s, %struct.lzma_mf_s* %105, i32 0, i32 15, !dbg !520
  %106 = load i32, i32* %cyclic_size109, align 4, !dbg !520
  %107 = load %struct.lzma_mf_s*, %struct.lzma_mf_s** %mf.addr, align 8, !dbg !521
  %sons_count110 = getelementptr inbounds %struct.lzma_mf_s, %struct.lzma_mf_s* %107, i32 0, i32 22, !dbg !522
  store i32 %106, i32* %sons_count110, align 8, !dbg !523
  %108 = load i8, i8* %is_bt, align 1, !dbg !524
  %tobool = trunc i8 %108 to i1, !dbg !524
  br i1 %tobool, label %if.then111, label %if.end113, !dbg !526

if.then111:                                       ; preds = %cond.end
  %109 = load %struct.lzma_mf_s*, %struct.lzma_mf_s** %mf.addr, align 8, !dbg !527
  %sons_count112 = getelementptr inbounds %struct.lzma_mf_s, %struct.lzma_mf_s* %109, i32 0, i32 22, !dbg !528
  %110 = load i32, i32* %sons_count112, align 8, !dbg !529
  %mul = mul i32 %110, 2, !dbg !529
  store i32 %mul, i32* %sons_count112, align 8, !dbg !529
  br label %if.end113, !dbg !527

if.end113:                                        ; preds = %if.then111, %cond.end
  %111 = load %struct.lzma_mf_s*, %struct.lzma_mf_s** %mf.addr, align 8, !dbg !530
  %hash_size_sum114 = getelementptr inbounds %struct.lzma_mf_s, %struct.lzma_mf_s* %111, i32 0, i32 21, !dbg !531
  %112 = load i32, i32* %hash_size_sum114, align 4, !dbg !531
  %113 = load %struct.lzma_mf_s*, %struct.lzma_mf_s** %mf.addr, align 8, !dbg !532
  %sons_count115 = getelementptr inbounds %struct.lzma_mf_s, %struct.lzma_mf_s* %113, i32 0, i32 22, !dbg !533
  %114 = load i32, i32* %sons_count115, align 8, !dbg !533
  %add116 = add i32 %112, %114, !dbg !534
  store i32 %add116, i32* %new_count, align 4, !dbg !535
  %115 = load i32, i32* %old_count, align 4, !dbg !536
  %116 = load i32, i32* %new_count, align 4, !dbg !538
  %cmp117 = icmp ne i32 %115, %116, !dbg !539
  br i1 %cmp117, label %if.then119, label %if.end121, !dbg !540

if.then119:                                       ; preds = %if.end113
  %117 = load %struct.lzma_mf_s*, %struct.lzma_mf_s** %mf.addr, align 8, !dbg !541
  %hash = getelementptr inbounds %struct.lzma_mf_s, %struct.lzma_mf_s* %117, i32 0, i32 12, !dbg !543
  %118 = load i32*, i32** %hash, align 8, !dbg !543
  %119 = bitcast i32* %118 to i8*, !dbg !541
  %120 = load %struct.lzma_allocator*, %struct.lzma_allocator** %allocator.addr, align 8, !dbg !544
  call void @lzma_free(i8* %119, %struct.lzma_allocator* %120), !dbg !545
  %121 = load %struct.lzma_mf_s*, %struct.lzma_mf_s** %mf.addr, align 8, !dbg !546
  %hash120 = getelementptr inbounds %struct.lzma_mf_s, %struct.lzma_mf_s* %121, i32 0, i32 12, !dbg !547
  store i32* null, i32** %hash120, align 8, !dbg !548
  br label %if.end121, !dbg !549

if.end121:                                        ; preds = %if.then119, %if.end113
  %122 = load %struct.lzma_lz_options*, %struct.lzma_lz_options** %lz_options.addr, align 8, !dbg !550
  %depth = getelementptr inbounds %struct.lzma_lz_options, %struct.lzma_lz_options* %122, i32 0, i32 6, !dbg !551
  %123 = load i32, i32* %depth, align 4, !dbg !551
  %124 = load %struct.lzma_mf_s*, %struct.lzma_mf_s** %mf.addr, align 8, !dbg !552
  %depth122 = getelementptr inbounds %struct.lzma_mf_s, %struct.lzma_mf_s* %124, i32 0, i32 17, !dbg !553
  store i32 %123, i32* %depth122, align 4, !dbg !554
  %125 = load %struct.lzma_mf_s*, %struct.lzma_mf_s** %mf.addr, align 8, !dbg !555
  %depth123 = getelementptr inbounds %struct.lzma_mf_s, %struct.lzma_mf_s* %125, i32 0, i32 17, !dbg !557
  %126 = load i32, i32* %depth123, align 4, !dbg !557
  %cmp124 = icmp eq i32 %126, 0, !dbg !558
  br i1 %cmp124, label %if.then126, label %if.end139, !dbg !559

if.then126:                                       ; preds = %if.end121
  %127 = load i8, i8* %is_bt, align 1, !dbg !560
  %tobool127 = trunc i8 %127 to i1, !dbg !560
  br i1 %tobool127, label %if.then128, label %if.else133, !dbg !563

if.then128:                                       ; preds = %if.then126
  %128 = load %struct.lzma_mf_s*, %struct.lzma_mf_s** %mf.addr, align 8, !dbg !564
  %nice_len129 = getelementptr inbounds %struct.lzma_mf_s, %struct.lzma_mf_s* %128, i32 0, i32 18, !dbg !565
  %129 = load i32, i32* %nice_len129, align 8, !dbg !565
  %div130 = udiv i32 %129, 2, !dbg !566
  %add131 = add i32 16, %div130, !dbg !567
  %130 = load %struct.lzma_mf_s*, %struct.lzma_mf_s** %mf.addr, align 8, !dbg !568
  %depth132 = getelementptr inbounds %struct.lzma_mf_s, %struct.lzma_mf_s* %130, i32 0, i32 17, !dbg !569
  store i32 %add131, i32* %depth132, align 4, !dbg !570
  br label %if.end138, !dbg !568

if.else133:                                       ; preds = %if.then126
  %131 = load %struct.lzma_mf_s*, %struct.lzma_mf_s** %mf.addr, align 8, !dbg !571
  %nice_len134 = getelementptr inbounds %struct.lzma_mf_s, %struct.lzma_mf_s* %131, i32 0, i32 18, !dbg !572
  %132 = load i32, i32* %nice_len134, align 8, !dbg !572
  %div135 = udiv i32 %132, 4, !dbg !573
  %add136 = add i32 4, %div135, !dbg !574
  %133 = load %struct.lzma_mf_s*, %struct.lzma_mf_s** %mf.addr, align 8, !dbg !575
  %depth137 = getelementptr inbounds %struct.lzma_mf_s, %struct.lzma_mf_s* %133, i32 0, i32 17, !dbg !576
  store i32 %add136, i32* %depth137, align 4, !dbg !577
  br label %if.end138

if.end138:                                        ; preds = %if.else133, %if.then128
  br label %if.end139, !dbg !578

if.end139:                                        ; preds = %if.end138, %if.end121
  store i1 false, i1* %retval, align 1, !dbg !579
  br label %return, !dbg !579

return:                                           ; preds = %if.end139, %if.then65, %sw.default, %if.then
  %134 = load i1, i1* %retval, align 1, !dbg !580
  ret i1 %134, !dbg !580
}

; Function Attrs: nounwind uwtable
define i32 @lzma_lz_encoder_init(%struct.lzma_next_coder_s* %next, %struct.lzma_allocator* %allocator, %struct.lzma_filter_info_s* %filters, i32 (%struct.lzma_lz_encoder*, %struct.lzma_allocator*, i8*, %struct.lzma_lz_options*)* %lz_init) #0 !dbg !73 {
entry:
  %retval = alloca i32, align 4
  %next.addr = alloca %struct.lzma_next_coder_s*, align 8
  %allocator.addr = alloca %struct.lzma_allocator*, align 8
  %filters.addr = alloca %struct.lzma_filter_info_s*, align 8
  %lz_init.addr = alloca i32 (%struct.lzma_lz_encoder*, %struct.lzma_allocator*, i8*, %struct.lzma_lz_options*)*, align 8
  %lz_options = alloca %struct.lzma_lz_options, align 8
  %ret_ = alloca i32, align 4
  store %struct.lzma_next_coder_s* %next, %struct.lzma_next_coder_s** %next.addr, align 8
  call void @llvm.dbg.declare(metadata %struct.lzma_next_coder_s** %next.addr, metadata !581, metadata !247), !dbg !582
  store %struct.lzma_allocator* %allocator, %struct.lzma_allocator** %allocator.addr, align 8
  call void @llvm.dbg.declare(metadata %struct.lzma_allocator** %allocator.addr, metadata !583, metadata !247), !dbg !584
  store %struct.lzma_filter_info_s* %filters, %struct.lzma_filter_info_s** %filters.addr, align 8
  call void @llvm.dbg.declare(metadata %struct.lzma_filter_info_s** %filters.addr, metadata !585, metadata !247), !dbg !586
  store i32 (%struct.lzma_lz_encoder*, %struct.lzma_allocator*, i8*, %struct.lzma_lz_options*)* %lz_init, i32 (%struct.lzma_lz_encoder*, %struct.lzma_allocator*, i8*, %struct.lzma_lz_options*)** %lz_init.addr, align 8
  call void @llvm.dbg.declare(metadata i32 (%struct.lzma_lz_encoder*, %struct.lzma_allocator*, i8*, %struct.lzma_lz_options*)** %lz_init.addr, metadata !587, metadata !247), !dbg !588
  call void @llvm.dbg.declare(metadata %struct.lzma_lz_options* %lz_options, metadata !589, metadata !247), !dbg !590
  %0 = load %struct.lzma_next_coder_s*, %struct.lzma_next_coder_s** %next.addr, align 8, !dbg !591
  %coder = getelementptr inbounds %struct.lzma_next_coder_s, %struct.lzma_next_coder_s* %0, i32 0, i32 0, !dbg !593
  %1 = load %struct.lzma_coder_s*, %struct.lzma_coder_s** %coder, align 8, !dbg !593
  %cmp = icmp eq %struct.lzma_coder_s* %1, null, !dbg !594
  br i1 %cmp, label %if.then, label %if.end22, !dbg !595

if.then:                                          ; preds = %entry
  %2 = load %struct.lzma_allocator*, %struct.lzma_allocator** %allocator.addr, align 8, !dbg !596
  %call = call noalias i8* @lzma_alloc(i64 216, %struct.lzma_allocator* %2), !dbg !598
  %3 = bitcast i8* %call to %struct.lzma_coder_s*, !dbg !598
  %4 = load %struct.lzma_next_coder_s*, %struct.lzma_next_coder_s** %next.addr, align 8, !dbg !599
  %coder1 = getelementptr inbounds %struct.lzma_next_coder_s, %struct.lzma_next_coder_s* %4, i32 0, i32 0, !dbg !600
  store %struct.lzma_coder_s* %3, %struct.lzma_coder_s** %coder1, align 8, !dbg !601
  %5 = load %struct.lzma_next_coder_s*, %struct.lzma_next_coder_s** %next.addr, align 8, !dbg !602
  %coder2 = getelementptr inbounds %struct.lzma_next_coder_s, %struct.lzma_next_coder_s* %5, i32 0, i32 0, !dbg !604
  %6 = load %struct.lzma_coder_s*, %struct.lzma_coder_s** %coder2, align 8, !dbg !604
  %cmp3 = icmp eq %struct.lzma_coder_s* %6, null, !dbg !605
  br i1 %cmp3, label %if.then4, label %if.end, !dbg !606

if.then4:                                         ; preds = %if.then
  store i32 5, i32* %retval, align 4, !dbg !607
  br label %return, !dbg !607

if.end:                                           ; preds = %if.then
  %7 = load %struct.lzma_next_coder_s*, %struct.lzma_next_coder_s** %next.addr, align 8, !dbg !608
  %code = getelementptr inbounds %struct.lzma_next_coder_s, %struct.lzma_next_coder_s* %7, i32 0, i32 3, !dbg !609
  store i32 (%struct.lzma_coder_s*, %struct.lzma_allocator*, i8*, i64*, i64, i8*, i64*, i64, i32)* @lz_encode, i32 (%struct.lzma_coder_s*, %struct.lzma_allocator*, i8*, i64*, i64, i8*, i64*, i64, i32)** %code, align 8, !dbg !610
  %8 = load %struct.lzma_next_coder_s*, %struct.lzma_next_coder_s** %next.addr, align 8, !dbg !611
  %end = getelementptr inbounds %struct.lzma_next_coder_s, %struct.lzma_next_coder_s* %8, i32 0, i32 4, !dbg !612
  store void (%struct.lzma_coder_s*, %struct.lzma_allocator*)* @lz_encoder_end, void (%struct.lzma_coder_s*, %struct.lzma_allocator*)** %end, align 8, !dbg !613
  %9 = load %struct.lzma_next_coder_s*, %struct.lzma_next_coder_s** %next.addr, align 8, !dbg !614
  %update = getelementptr inbounds %struct.lzma_next_coder_s, %struct.lzma_next_coder_s* %9, i32 0, i32 7, !dbg !615
  store i32 (%struct.lzma_coder_s*, %struct.lzma_allocator*, %struct.lzma_filter*, %struct.lzma_filter*)* @lz_encoder_update, i32 (%struct.lzma_coder_s*, %struct.lzma_allocator*, %struct.lzma_filter*, %struct.lzma_filter*)** %update, align 8, !dbg !616
  %10 = load %struct.lzma_next_coder_s*, %struct.lzma_next_coder_s** %next.addr, align 8, !dbg !617
  %coder5 = getelementptr inbounds %struct.lzma_next_coder_s, %struct.lzma_next_coder_s* %10, i32 0, i32 0, !dbg !618
  %11 = load %struct.lzma_coder_s*, %struct.lzma_coder_s** %coder5, align 8, !dbg !618
  %lz = getelementptr inbounds %struct.lzma_coder_s, %struct.lzma_coder_s* %11, i32 0, i32 0, !dbg !619
  %coder6 = getelementptr inbounds %struct.lzma_lz_encoder, %struct.lzma_lz_encoder* %lz, i32 0, i32 0, !dbg !620
  store %struct.lzma_coder_s* null, %struct.lzma_coder_s** %coder6, align 8, !dbg !621
  %12 = load %struct.lzma_next_coder_s*, %struct.lzma_next_coder_s** %next.addr, align 8, !dbg !622
  %coder7 = getelementptr inbounds %struct.lzma_next_coder_s, %struct.lzma_next_coder_s* %12, i32 0, i32 0, !dbg !623
  %13 = load %struct.lzma_coder_s*, %struct.lzma_coder_s** %coder7, align 8, !dbg !623
  %lz8 = getelementptr inbounds %struct.lzma_coder_s, %struct.lzma_coder_s* %13, i32 0, i32 0, !dbg !624
  %code9 = getelementptr inbounds %struct.lzma_lz_encoder, %struct.lzma_lz_encoder* %lz8, i32 0, i32 1, !dbg !625
  store i32 (%struct.lzma_coder_s*, %struct.lzma_mf_s*, i8*, i64*, i64)* null, i32 (%struct.lzma_coder_s*, %struct.lzma_mf_s*, i8*, i64*, i64)** %code9, align 8, !dbg !626
  %14 = load %struct.lzma_next_coder_s*, %struct.lzma_next_coder_s** %next.addr, align 8, !dbg !627
  %coder10 = getelementptr inbounds %struct.lzma_next_coder_s, %struct.lzma_next_coder_s* %14, i32 0, i32 0, !dbg !628
  %15 = load %struct.lzma_coder_s*, %struct.lzma_coder_s** %coder10, align 8, !dbg !628
  %lz11 = getelementptr inbounds %struct.lzma_coder_s, %struct.lzma_coder_s* %15, i32 0, i32 0, !dbg !629
  %end12 = getelementptr inbounds %struct.lzma_lz_encoder, %struct.lzma_lz_encoder* %lz11, i32 0, i32 2, !dbg !630
  store void (%struct.lzma_coder_s*, %struct.lzma_allocator*)* null, void (%struct.lzma_coder_s*, %struct.lzma_allocator*)** %end12, align 8, !dbg !631
  %16 = load %struct.lzma_next_coder_s*, %struct.lzma_next_coder_s** %next.addr, align 8, !dbg !632
  %coder13 = getelementptr inbounds %struct.lzma_next_coder_s, %struct.lzma_next_coder_s* %16, i32 0, i32 0, !dbg !633
  %17 = load %struct.lzma_coder_s*, %struct.lzma_coder_s** %coder13, align 8, !dbg !633
  %mf = getelementptr inbounds %struct.lzma_coder_s, %struct.lzma_coder_s* %17, i32 0, i32 1, !dbg !634
  %buffer = getelementptr inbounds %struct.lzma_mf_s, %struct.lzma_mf_s* %mf, i32 0, i32 0, !dbg !635
  store i8* null, i8** %buffer, align 8, !dbg !636
  %18 = load %struct.lzma_next_coder_s*, %struct.lzma_next_coder_s** %next.addr, align 8, !dbg !637
  %coder14 = getelementptr inbounds %struct.lzma_next_coder_s, %struct.lzma_next_coder_s* %18, i32 0, i32 0, !dbg !638
  %19 = load %struct.lzma_coder_s*, %struct.lzma_coder_s** %coder14, align 8, !dbg !638
  %mf15 = getelementptr inbounds %struct.lzma_coder_s, %struct.lzma_coder_s* %19, i32 0, i32 1, !dbg !639
  %hash = getelementptr inbounds %struct.lzma_mf_s, %struct.lzma_mf_s* %mf15, i32 0, i32 12, !dbg !640
  store i32* null, i32** %hash, align 8, !dbg !641
  %20 = load %struct.lzma_next_coder_s*, %struct.lzma_next_coder_s** %next.addr, align 8, !dbg !642
  %coder16 = getelementptr inbounds %struct.lzma_next_coder_s, %struct.lzma_next_coder_s* %20, i32 0, i32 0, !dbg !643
  %21 = load %struct.lzma_coder_s*, %struct.lzma_coder_s** %coder16, align 8, !dbg !643
  %mf17 = getelementptr inbounds %struct.lzma_coder_s, %struct.lzma_coder_s* %21, i32 0, i32 1, !dbg !644
  %hash_size_sum = getelementptr inbounds %struct.lzma_mf_s, %struct.lzma_mf_s* %mf17, i32 0, i32 21, !dbg !645
  store i32 0, i32* %hash_size_sum, align 4, !dbg !646
  %22 = load %struct.lzma_next_coder_s*, %struct.lzma_next_coder_s** %next.addr, align 8, !dbg !647
  %coder18 = getelementptr inbounds %struct.lzma_next_coder_s, %struct.lzma_next_coder_s* %22, i32 0, i32 0, !dbg !648
  %23 = load %struct.lzma_coder_s*, %struct.lzma_coder_s** %coder18, align 8, !dbg !648
  %mf19 = getelementptr inbounds %struct.lzma_coder_s, %struct.lzma_coder_s* %23, i32 0, i32 1, !dbg !649
  %sons_count = getelementptr inbounds %struct.lzma_mf_s, %struct.lzma_mf_s* %mf19, i32 0, i32 22, !dbg !650
  store i32 0, i32* %sons_count, align 8, !dbg !651
  %24 = load %struct.lzma_next_coder_s*, %struct.lzma_next_coder_s** %next.addr, align 8, !dbg !652
  %coder20 = getelementptr inbounds %struct.lzma_next_coder_s, %struct.lzma_next_coder_s* %24, i32 0, i32 0, !dbg !653
  %25 = load %struct.lzma_coder_s*, %struct.lzma_coder_s** %coder20, align 8, !dbg !653
  %next21 = getelementptr inbounds %struct.lzma_coder_s, %struct.lzma_coder_s* %25, i32 0, i32 2, !dbg !654
  %26 = bitcast %struct.lzma_next_coder_s* %next21 to i8*, !dbg !655
  call void @llvm.memcpy.p0i8.p0i8.i64(i8* %26, i8* bitcast (%struct.lzma_next_coder_s* @LZMA_NEXT_CODER_INIT to i8*), i64 64, i32 8, i1 false), !dbg !655
  br label %if.end22, !dbg !656

if.end22:                                         ; preds = %if.end, %entry
  br label %do.body, !dbg !657

do.body:                                          ; preds = %if.end22
  call void @llvm.dbg.declare(metadata i32* %ret_, metadata !658, metadata !247), !dbg !661
  %27 = load i32 (%struct.lzma_lz_encoder*, %struct.lzma_allocator*, i8*, %struct.lzma_lz_options*)*, i32 (%struct.lzma_lz_encoder*, %struct.lzma_allocator*, i8*, %struct.lzma_lz_options*)** %lz_init.addr, align 8, !dbg !662
  %28 = load %struct.lzma_next_coder_s*, %struct.lzma_next_coder_s** %next.addr, align 8, !dbg !662
  %coder23 = getelementptr inbounds %struct.lzma_next_coder_s, %struct.lzma_next_coder_s* %28, i32 0, i32 0, !dbg !662
  %29 = load %struct.lzma_coder_s*, %struct.lzma_coder_s** %coder23, align 8, !dbg !662
  %lz24 = getelementptr inbounds %struct.lzma_coder_s, %struct.lzma_coder_s* %29, i32 0, i32 0, !dbg !662
  %30 = load %struct.lzma_allocator*, %struct.lzma_allocator** %allocator.addr, align 8, !dbg !662
  %31 = load %struct.lzma_filter_info_s*, %struct.lzma_filter_info_s** %filters.addr, align 8, !dbg !662
  %arrayidx = getelementptr inbounds %struct.lzma_filter_info_s, %struct.lzma_filter_info_s* %31, i64 0, !dbg !662
  %options = getelementptr inbounds %struct.lzma_filter_info_s, %struct.lzma_filter_info_s* %arrayidx, i32 0, i32 2, !dbg !662
  %32 = load i8*, i8** %options, align 8, !dbg !662
  %call25 = call i32 %27(%struct.lzma_lz_encoder* %lz24, %struct.lzma_allocator* %30, i8* %32, %struct.lzma_lz_options* %lz_options), !dbg !662
  store i32 %call25, i32* %ret_, align 4, !dbg !662
  %33 = load i32, i32* %ret_, align 4, !dbg !662
  %cmp26 = icmp ne i32 %33, 0, !dbg !662
  br i1 %cmp26, label %if.then27, label %if.end28, !dbg !662

if.then27:                                        ; preds = %do.body
  %34 = load i32, i32* %ret_, align 4, !dbg !664
  store i32 %34, i32* %retval, align 4, !dbg !664
  br label %return, !dbg !664

if.end28:                                         ; preds = %do.body
  br label %do.end, !dbg !667

do.end:                                           ; preds = %if.end28
  %35 = load %struct.lzma_next_coder_s*, %struct.lzma_next_coder_s** %next.addr, align 8, !dbg !669
  %coder29 = getelementptr inbounds %struct.lzma_next_coder_s, %struct.lzma_next_coder_s* %35, i32 0, i32 0, !dbg !671
  %36 = load %struct.lzma_coder_s*, %struct.lzma_coder_s** %coder29, align 8, !dbg !671
  %mf30 = getelementptr inbounds %struct.lzma_coder_s, %struct.lzma_coder_s* %36, i32 0, i32 1, !dbg !672
  %37 = load %struct.lzma_allocator*, %struct.lzma_allocator** %allocator.addr, align 8, !dbg !673
  %call31 = call zeroext i1 @lz_encoder_prepare(%struct.lzma_mf_s* %mf30, %struct.lzma_allocator* %37, %struct.lzma_lz_options* %lz_options), !dbg !674
  br i1 %call31, label %if.then32, label %if.end33, !dbg !675

if.then32:                                        ; preds = %do.end
  store i32 8, i32* %retval, align 4, !dbg !676
  br label %return, !dbg !676

if.end33:                                         ; preds = %do.end
  %38 = load %struct.lzma_next_coder_s*, %struct.lzma_next_coder_s** %next.addr, align 8, !dbg !677
  %coder34 = getelementptr inbounds %struct.lzma_next_coder_s, %struct.lzma_next_coder_s* %38, i32 0, i32 0, !dbg !679
  %39 = load %struct.lzma_coder_s*, %struct.lzma_coder_s** %coder34, align 8, !dbg !679
  %mf35 = getelementptr inbounds %struct.lzma_coder_s, %struct.lzma_coder_s* %39, i32 0, i32 1, !dbg !680
  %40 = load %struct.lzma_allocator*, %struct.lzma_allocator** %allocator.addr, align 8, !dbg !681
  %call36 = call zeroext i1 @lz_encoder_init(%struct.lzma_mf_s* %mf35, %struct.lzma_allocator* %40, %struct.lzma_lz_options* %lz_options), !dbg !682
  br i1 %call36, label %if.then37, label %if.end38, !dbg !683

if.then37:                                        ; preds = %if.end33
  store i32 5, i32* %retval, align 4, !dbg !684
  br label %return, !dbg !684

if.end38:                                         ; preds = %if.end33
  %41 = load %struct.lzma_next_coder_s*, %struct.lzma_next_coder_s** %next.addr, align 8, !dbg !685
  %coder39 = getelementptr inbounds %struct.lzma_next_coder_s, %struct.lzma_next_coder_s* %41, i32 0, i32 0, !dbg !686
  %42 = load %struct.lzma_coder_s*, %struct.lzma_coder_s** %coder39, align 8, !dbg !686
  %next40 = getelementptr inbounds %struct.lzma_coder_s, %struct.lzma_coder_s* %42, i32 0, i32 2, !dbg !687
  %43 = load %struct.lzma_allocator*, %struct.lzma_allocator** %allocator.addr, align 8, !dbg !688
  %44 = load %struct.lzma_filter_info_s*, %struct.lzma_filter_info_s** %filters.addr, align 8, !dbg !689
  %add.ptr = getelementptr inbounds %struct.lzma_filter_info_s, %struct.lzma_filter_info_s* %44, i64 1, !dbg !690
  %call41 = call i32 @lzma_next_filter_init(%struct.lzma_next_coder_s* %next40, %struct.lzma_allocator* %43, %struct.lzma_filter_info_s* %add.ptr), !dbg !691
  store i32 %call41, i32* %retval, align 4, !dbg !692
  br label %return, !dbg !692

return:                                           ; preds = %if.end38, %if.then37, %if.then32, %if.then27, %if.then4
  %45 = load i32, i32* %retval, align 4, !dbg !693
  ret i32 %45, !dbg !693
}

declare noalias i8* @lzma_alloc(i64, %struct.lzma_allocator*) #3

; Function Attrs: nounwind uwtable
define internal i32 @lz_encode(%struct.lzma_coder_s* %coder, %struct.lzma_allocator* %allocator, i8* noalias %in, i64* noalias %in_pos, i64 %in_size, i8* noalias %out, i64* noalias %out_pos, i64 %out_size, i32 %action) #0 !dbg !230 {
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
  %ret = alloca i32, align 4
  %ret_ = alloca i32, align 4
  store %struct.lzma_coder_s* %coder, %struct.lzma_coder_s** %coder.addr, align 8
  call void @llvm.dbg.declare(metadata %struct.lzma_coder_s** %coder.addr, metadata !694, metadata !247), !dbg !695
  store %struct.lzma_allocator* %allocator, %struct.lzma_allocator** %allocator.addr, align 8
  call void @llvm.dbg.declare(metadata %struct.lzma_allocator** %allocator.addr, metadata !696, metadata !247), !dbg !697
  store i8* %in, i8** %in.addr, align 8
  call void @llvm.dbg.declare(metadata i8** %in.addr, metadata !698, metadata !247), !dbg !699
  store i64* %in_pos, i64** %in_pos.addr, align 8
  call void @llvm.dbg.declare(metadata i64** %in_pos.addr, metadata !700, metadata !247), !dbg !701
  store i64 %in_size, i64* %in_size.addr, align 8
  call void @llvm.dbg.declare(metadata i64* %in_size.addr, metadata !702, metadata !247), !dbg !703
  store i8* %out, i8** %out.addr, align 8
  call void @llvm.dbg.declare(metadata i8** %out.addr, metadata !704, metadata !247), !dbg !705
  store i64* %out_pos, i64** %out_pos.addr, align 8
  call void @llvm.dbg.declare(metadata i64** %out_pos.addr, metadata !706, metadata !247), !dbg !707
  store i64 %out_size, i64* %out_size.addr, align 8
  call void @llvm.dbg.declare(metadata i64* %out_size.addr, metadata !708, metadata !247), !dbg !709
  store i32 %action, i32* %action.addr, align 4
  call void @llvm.dbg.declare(metadata i32* %action.addr, metadata !710, metadata !247), !dbg !711
  br label %while.cond, !dbg !712

while.cond:                                       ; preds = %if.end19, %entry
  %0 = load i64*, i64** %out_pos.addr, align 8, !dbg !713
  %1 = load i64, i64* %0, align 8, !dbg !715
  %2 = load i64, i64* %out_size.addr, align 8, !dbg !716
  %cmp = icmp ult i64 %1, %2, !dbg !717
  br i1 %cmp, label %land.rhs, label %land.end, !dbg !718

land.rhs:                                         ; preds = %while.cond
  %3 = load i64*, i64** %in_pos.addr, align 8, !dbg !719
  %4 = load i64, i64* %3, align 8, !dbg !720
  %5 = load i64, i64* %in_size.addr, align 8, !dbg !721
  %cmp1 = icmp ult i64 %4, %5, !dbg !722
  br i1 %cmp1, label %lor.end, label %lor.rhs, !dbg !723

lor.rhs:                                          ; preds = %land.rhs
  %6 = load i32, i32* %action.addr, align 4, !dbg !724
  %cmp2 = icmp ne i32 %6, 0, !dbg !726
  br label %lor.end, !dbg !727

lor.end:                                          ; preds = %lor.rhs, %land.rhs
  %7 = phi i1 [ true, %land.rhs ], [ %cmp2, %lor.rhs ]
  br label %land.end

land.end:                                         ; preds = %lor.end, %while.cond
  %8 = phi i1 [ false, %while.cond ], [ %7, %lor.end ]
  br i1 %8, label %while.body, label %while.end, !dbg !728

while.body:                                       ; preds = %land.end
  call void @llvm.dbg.declare(metadata i32* %ret, metadata !729, metadata !247), !dbg !731
  %9 = load %struct.lzma_coder_s*, %struct.lzma_coder_s** %coder.addr, align 8, !dbg !732
  %mf = getelementptr inbounds %struct.lzma_coder_s, %struct.lzma_coder_s* %9, i32 0, i32 1, !dbg !734
  %action3 = getelementptr inbounds %struct.lzma_mf_s, %struct.lzma_mf_s* %mf, i32 0, i32 20, !dbg !735
  %10 = load i32, i32* %action3, align 8, !dbg !735
  %cmp4 = icmp eq i32 %10, 0, !dbg !736
  br i1 %cmp4, label %land.lhs.true, label %if.end10, !dbg !737

land.lhs.true:                                    ; preds = %while.body
  %11 = load %struct.lzma_coder_s*, %struct.lzma_coder_s** %coder.addr, align 8, !dbg !738
  %mf5 = getelementptr inbounds %struct.lzma_coder_s, %struct.lzma_coder_s* %11, i32 0, i32 1, !dbg !740
  %read_pos = getelementptr inbounds %struct.lzma_mf_s, %struct.lzma_mf_s* %mf5, i32 0, i32 5, !dbg !741
  %12 = load i32, i32* %read_pos, align 8, !dbg !741
  %13 = load %struct.lzma_coder_s*, %struct.lzma_coder_s** %coder.addr, align 8, !dbg !742
  %mf6 = getelementptr inbounds %struct.lzma_coder_s, %struct.lzma_coder_s* %13, i32 0, i32 1, !dbg !743
  %read_limit = getelementptr inbounds %struct.lzma_mf_s, %struct.lzma_mf_s* %mf6, i32 0, i32 7, !dbg !744
  %14 = load i32, i32* %read_limit, align 8, !dbg !744
  %cmp7 = icmp uge i32 %12, %14, !dbg !745
  br i1 %cmp7, label %if.then, label %if.end10, !dbg !746

if.then:                                          ; preds = %land.lhs.true
  br label %do.body, !dbg !747

do.body:                                          ; preds = %if.then
  call void @llvm.dbg.declare(metadata i32* %ret_, metadata !748, metadata !247), !dbg !750
  %15 = load %struct.lzma_coder_s*, %struct.lzma_coder_s** %coder.addr, align 8, !dbg !751
  %16 = load %struct.lzma_allocator*, %struct.lzma_allocator** %allocator.addr, align 8, !dbg !751
  %17 = load i8*, i8** %in.addr, align 8, !dbg !751
  %18 = load i64*, i64** %in_pos.addr, align 8, !dbg !751
  %19 = load i64, i64* %in_size.addr, align 8, !dbg !751
  %20 = load i32, i32* %action.addr, align 4, !dbg !751
  %call = call i32 @fill_window(%struct.lzma_coder_s* %15, %struct.lzma_allocator* %16, i8* %17, i64* %18, i64 %19, i32 %20), !dbg !751
  store i32 %call, i32* %ret_, align 4, !dbg !751
  %21 = load i32, i32* %ret_, align 4, !dbg !751
  %cmp8 = icmp ne i32 %21, 0, !dbg !751
  br i1 %cmp8, label %if.then9, label %if.end, !dbg !751

if.then9:                                         ; preds = %do.body
  %22 = load i32, i32* %ret_, align 4, !dbg !753
  store i32 %22, i32* %retval, align 4, !dbg !753
  br label %return, !dbg !753

if.end:                                           ; preds = %do.body
  br label %do.end, !dbg !756

do.end:                                           ; preds = %if.end
  br label %if.end10, !dbg !758

if.end10:                                         ; preds = %do.end, %land.lhs.true, %while.body
  %23 = load %struct.lzma_coder_s*, %struct.lzma_coder_s** %coder.addr, align 8, !dbg !760
  %lz = getelementptr inbounds %struct.lzma_coder_s, %struct.lzma_coder_s* %23, i32 0, i32 0, !dbg !761
  %code = getelementptr inbounds %struct.lzma_lz_encoder, %struct.lzma_lz_encoder* %lz, i32 0, i32 1, !dbg !762
  %24 = load i32 (%struct.lzma_coder_s*, %struct.lzma_mf_s*, i8*, i64*, i64)*, i32 (%struct.lzma_coder_s*, %struct.lzma_mf_s*, i8*, i64*, i64)** %code, align 8, !dbg !762
  %25 = load %struct.lzma_coder_s*, %struct.lzma_coder_s** %coder.addr, align 8, !dbg !763
  %lz11 = getelementptr inbounds %struct.lzma_coder_s, %struct.lzma_coder_s* %25, i32 0, i32 0, !dbg !764
  %coder12 = getelementptr inbounds %struct.lzma_lz_encoder, %struct.lzma_lz_encoder* %lz11, i32 0, i32 0, !dbg !765
  %26 = load %struct.lzma_coder_s*, %struct.lzma_coder_s** %coder12, align 8, !dbg !765
  %27 = load %struct.lzma_coder_s*, %struct.lzma_coder_s** %coder.addr, align 8, !dbg !766
  %mf13 = getelementptr inbounds %struct.lzma_coder_s, %struct.lzma_coder_s* %27, i32 0, i32 1, !dbg !767
  %28 = load i8*, i8** %out.addr, align 8, !dbg !768
  %29 = load i64*, i64** %out_pos.addr, align 8, !dbg !769
  %30 = load i64, i64* %out_size.addr, align 8, !dbg !770
  %call14 = call i32 %24(%struct.lzma_coder_s* %26, %struct.lzma_mf_s* %mf13, i8* %28, i64* %29, i64 %30), !dbg !760
  store i32 %call14, i32* %ret, align 4, !dbg !771
  %31 = load i32, i32* %ret, align 4, !dbg !772
  %cmp15 = icmp ne i32 %31, 0, !dbg !774
  br i1 %cmp15, label %if.then16, label %if.end19, !dbg !775

if.then16:                                        ; preds = %if.end10
  %32 = load %struct.lzma_coder_s*, %struct.lzma_coder_s** %coder.addr, align 8, !dbg !776
  %mf17 = getelementptr inbounds %struct.lzma_coder_s, %struct.lzma_coder_s* %32, i32 0, i32 1, !dbg !778
  %action18 = getelementptr inbounds %struct.lzma_mf_s, %struct.lzma_mf_s* %mf17, i32 0, i32 20, !dbg !779
  store i32 0, i32* %action18, align 8, !dbg !780
  %33 = load i32, i32* %ret, align 4, !dbg !781
  store i32 %33, i32* %retval, align 4, !dbg !782
  br label %return, !dbg !782

if.end19:                                         ; preds = %if.end10
  br label %while.cond, !dbg !783

while.end:                                        ; preds = %land.end
  store i32 0, i32* %retval, align 4, !dbg !785
  br label %return, !dbg !785

return:                                           ; preds = %while.end, %if.then16, %if.then9
  %34 = load i32, i32* %retval, align 4, !dbg !786
  ret i32 %34, !dbg !786
}

; Function Attrs: nounwind uwtable
define internal void @lz_encoder_end(%struct.lzma_coder_s* %coder, %struct.lzma_allocator* %allocator) #0 !dbg !237 {
entry:
  %coder.addr = alloca %struct.lzma_coder_s*, align 8
  %allocator.addr = alloca %struct.lzma_allocator*, align 8
  store %struct.lzma_coder_s* %coder, %struct.lzma_coder_s** %coder.addr, align 8
  call void @llvm.dbg.declare(metadata %struct.lzma_coder_s** %coder.addr, metadata !787, metadata !247), !dbg !788
  store %struct.lzma_allocator* %allocator, %struct.lzma_allocator** %allocator.addr, align 8
  call void @llvm.dbg.declare(metadata %struct.lzma_allocator** %allocator.addr, metadata !789, metadata !247), !dbg !790
  %0 = load %struct.lzma_coder_s*, %struct.lzma_coder_s** %coder.addr, align 8, !dbg !791
  %next = getelementptr inbounds %struct.lzma_coder_s, %struct.lzma_coder_s* %0, i32 0, i32 2, !dbg !792
  %1 = load %struct.lzma_allocator*, %struct.lzma_allocator** %allocator.addr, align 8, !dbg !793
  call void @lzma_next_end(%struct.lzma_next_coder_s* %next, %struct.lzma_allocator* %1), !dbg !794
  %2 = load %struct.lzma_coder_s*, %struct.lzma_coder_s** %coder.addr, align 8, !dbg !795
  %mf = getelementptr inbounds %struct.lzma_coder_s, %struct.lzma_coder_s* %2, i32 0, i32 1, !dbg !796
  %hash = getelementptr inbounds %struct.lzma_mf_s, %struct.lzma_mf_s* %mf, i32 0, i32 12, !dbg !797
  %3 = load i32*, i32** %hash, align 8, !dbg !797
  %4 = bitcast i32* %3 to i8*, !dbg !795
  %5 = load %struct.lzma_allocator*, %struct.lzma_allocator** %allocator.addr, align 8, !dbg !798
  call void @lzma_free(i8* %4, %struct.lzma_allocator* %5), !dbg !799
  %6 = load %struct.lzma_coder_s*, %struct.lzma_coder_s** %coder.addr, align 8, !dbg !800
  %mf1 = getelementptr inbounds %struct.lzma_coder_s, %struct.lzma_coder_s* %6, i32 0, i32 1, !dbg !801
  %buffer = getelementptr inbounds %struct.lzma_mf_s, %struct.lzma_mf_s* %mf1, i32 0, i32 0, !dbg !802
  %7 = load i8*, i8** %buffer, align 8, !dbg !802
  %8 = load %struct.lzma_allocator*, %struct.lzma_allocator** %allocator.addr, align 8, !dbg !803
  call void @lzma_free(i8* %7, %struct.lzma_allocator* %8), !dbg !804
  %9 = load %struct.lzma_coder_s*, %struct.lzma_coder_s** %coder.addr, align 8, !dbg !805
  %lz = getelementptr inbounds %struct.lzma_coder_s, %struct.lzma_coder_s* %9, i32 0, i32 0, !dbg !807
  %end = getelementptr inbounds %struct.lzma_lz_encoder, %struct.lzma_lz_encoder* %lz, i32 0, i32 2, !dbg !808
  %10 = load void (%struct.lzma_coder_s*, %struct.lzma_allocator*)*, void (%struct.lzma_coder_s*, %struct.lzma_allocator*)** %end, align 8, !dbg !808
  %cmp = icmp ne void (%struct.lzma_coder_s*, %struct.lzma_allocator*)* %10, null, !dbg !809
  br i1 %cmp, label %if.then, label %if.else, !dbg !810

if.then:                                          ; preds = %entry
  %11 = load %struct.lzma_coder_s*, %struct.lzma_coder_s** %coder.addr, align 8, !dbg !811
  %lz2 = getelementptr inbounds %struct.lzma_coder_s, %struct.lzma_coder_s* %11, i32 0, i32 0, !dbg !812
  %end3 = getelementptr inbounds %struct.lzma_lz_encoder, %struct.lzma_lz_encoder* %lz2, i32 0, i32 2, !dbg !813
  %12 = load void (%struct.lzma_coder_s*, %struct.lzma_allocator*)*, void (%struct.lzma_coder_s*, %struct.lzma_allocator*)** %end3, align 8, !dbg !813
  %13 = load %struct.lzma_coder_s*, %struct.lzma_coder_s** %coder.addr, align 8, !dbg !814
  %lz4 = getelementptr inbounds %struct.lzma_coder_s, %struct.lzma_coder_s* %13, i32 0, i32 0, !dbg !815
  %coder5 = getelementptr inbounds %struct.lzma_lz_encoder, %struct.lzma_lz_encoder* %lz4, i32 0, i32 0, !dbg !816
  %14 = load %struct.lzma_coder_s*, %struct.lzma_coder_s** %coder5, align 8, !dbg !816
  %15 = load %struct.lzma_allocator*, %struct.lzma_allocator** %allocator.addr, align 8, !dbg !817
  call void %12(%struct.lzma_coder_s* %14, %struct.lzma_allocator* %15), !dbg !811
  br label %if.end, !dbg !811

if.else:                                          ; preds = %entry
  %16 = load %struct.lzma_coder_s*, %struct.lzma_coder_s** %coder.addr, align 8, !dbg !818
  %lz6 = getelementptr inbounds %struct.lzma_coder_s, %struct.lzma_coder_s* %16, i32 0, i32 0, !dbg !819
  %coder7 = getelementptr inbounds %struct.lzma_lz_encoder, %struct.lzma_lz_encoder* %lz6, i32 0, i32 0, !dbg !820
  %17 = load %struct.lzma_coder_s*, %struct.lzma_coder_s** %coder7, align 8, !dbg !820
  %18 = bitcast %struct.lzma_coder_s* %17 to i8*, !dbg !818
  %19 = load %struct.lzma_allocator*, %struct.lzma_allocator** %allocator.addr, align 8, !dbg !821
  call void @lzma_free(i8* %18, %struct.lzma_allocator* %19), !dbg !822
  br label %if.end

if.end:                                           ; preds = %if.else, %if.then
  %20 = load %struct.lzma_coder_s*, %struct.lzma_coder_s** %coder.addr, align 8, !dbg !823
  %21 = bitcast %struct.lzma_coder_s* %20 to i8*, !dbg !823
  %22 = load %struct.lzma_allocator*, %struct.lzma_allocator** %allocator.addr, align 8, !dbg !824
  call void @lzma_free(i8* %21, %struct.lzma_allocator* %22), !dbg !825
  ret void, !dbg !826
}

; Function Attrs: nounwind uwtable
define internal i32 @lz_encoder_update(%struct.lzma_coder_s* %coder, %struct.lzma_allocator* %allocator, %struct.lzma_filter* %filters_null, %struct.lzma_filter* %reversed_filters) #0 !dbg !238 {
entry:
  %retval = alloca i32, align 4
  %coder.addr = alloca %struct.lzma_coder_s*, align 8
  %allocator.addr = alloca %struct.lzma_allocator*, align 8
  %filters_null.addr = alloca %struct.lzma_filter*, align 8
  %reversed_filters.addr = alloca %struct.lzma_filter*, align 8
  %ret_ = alloca i32, align 4
  store %struct.lzma_coder_s* %coder, %struct.lzma_coder_s** %coder.addr, align 8
  call void @llvm.dbg.declare(metadata %struct.lzma_coder_s** %coder.addr, metadata !827, metadata !247), !dbg !828
  store %struct.lzma_allocator* %allocator, %struct.lzma_allocator** %allocator.addr, align 8
  call void @llvm.dbg.declare(metadata %struct.lzma_allocator** %allocator.addr, metadata !829, metadata !247), !dbg !830
  store %struct.lzma_filter* %filters_null, %struct.lzma_filter** %filters_null.addr, align 8
  call void @llvm.dbg.declare(metadata %struct.lzma_filter** %filters_null.addr, metadata !831, metadata !247), !dbg !832
  store %struct.lzma_filter* %reversed_filters, %struct.lzma_filter** %reversed_filters.addr, align 8
  call void @llvm.dbg.declare(metadata %struct.lzma_filter** %reversed_filters.addr, metadata !833, metadata !247), !dbg !834
  %0 = load %struct.lzma_coder_s*, %struct.lzma_coder_s** %coder.addr, align 8, !dbg !835
  %lz = getelementptr inbounds %struct.lzma_coder_s, %struct.lzma_coder_s* %0, i32 0, i32 0, !dbg !837
  %options_update = getelementptr inbounds %struct.lzma_lz_encoder, %struct.lzma_lz_encoder* %lz, i32 0, i32 3, !dbg !838
  %1 = load i32 (%struct.lzma_coder_s*, %struct.lzma_filter*)*, i32 (%struct.lzma_coder_s*, %struct.lzma_filter*)** %options_update, align 8, !dbg !838
  %cmp = icmp eq i32 (%struct.lzma_coder_s*, %struct.lzma_filter*)* %1, null, !dbg !839
  br i1 %cmp, label %if.then, label %if.end, !dbg !840

if.then:                                          ; preds = %entry
  store i32 11, i32* %retval, align 4, !dbg !841
  br label %return, !dbg !841

if.end:                                           ; preds = %entry
  br label %do.body, !dbg !842

do.body:                                          ; preds = %if.end
  call void @llvm.dbg.declare(metadata i32* %ret_, metadata !843, metadata !247), !dbg !845
  %2 = load %struct.lzma_coder_s*, %struct.lzma_coder_s** %coder.addr, align 8, !dbg !846
  %lz1 = getelementptr inbounds %struct.lzma_coder_s, %struct.lzma_coder_s* %2, i32 0, i32 0, !dbg !846
  %options_update2 = getelementptr inbounds %struct.lzma_lz_encoder, %struct.lzma_lz_encoder* %lz1, i32 0, i32 3, !dbg !846
  %3 = load i32 (%struct.lzma_coder_s*, %struct.lzma_filter*)*, i32 (%struct.lzma_coder_s*, %struct.lzma_filter*)** %options_update2, align 8, !dbg !846
  %4 = load %struct.lzma_coder_s*, %struct.lzma_coder_s** %coder.addr, align 8, !dbg !846
  %lz3 = getelementptr inbounds %struct.lzma_coder_s, %struct.lzma_coder_s* %4, i32 0, i32 0, !dbg !846
  %coder4 = getelementptr inbounds %struct.lzma_lz_encoder, %struct.lzma_lz_encoder* %lz3, i32 0, i32 0, !dbg !846
  %5 = load %struct.lzma_coder_s*, %struct.lzma_coder_s** %coder4, align 8, !dbg !846
  %6 = load %struct.lzma_filter*, %struct.lzma_filter** %reversed_filters.addr, align 8, !dbg !846
  %call = call i32 %3(%struct.lzma_coder_s* %5, %struct.lzma_filter* %6), !dbg !846
  store i32 %call, i32* %ret_, align 4, !dbg !846
  %7 = load i32, i32* %ret_, align 4, !dbg !846
  %cmp5 = icmp ne i32 %7, 0, !dbg !846
  br i1 %cmp5, label %if.then6, label %if.end7, !dbg !846

if.then6:                                         ; preds = %do.body
  %8 = load i32, i32* %ret_, align 4, !dbg !848
  store i32 %8, i32* %retval, align 4, !dbg !848
  br label %return, !dbg !848

if.end7:                                          ; preds = %do.body
  br label %do.end, !dbg !851

do.end:                                           ; preds = %if.end7
  %9 = load %struct.lzma_coder_s*, %struct.lzma_coder_s** %coder.addr, align 8, !dbg !853
  %next = getelementptr inbounds %struct.lzma_coder_s, %struct.lzma_coder_s* %9, i32 0, i32 2, !dbg !854
  %10 = load %struct.lzma_allocator*, %struct.lzma_allocator** %allocator.addr, align 8, !dbg !855
  %11 = load %struct.lzma_filter*, %struct.lzma_filter** %reversed_filters.addr, align 8, !dbg !856
  %add.ptr = getelementptr inbounds %struct.lzma_filter, %struct.lzma_filter* %11, i64 1, !dbg !857
  %call8 = call i32 @lzma_next_filter_update(%struct.lzma_next_coder_s* %next, %struct.lzma_allocator* %10, %struct.lzma_filter* %add.ptr), !dbg !858
  store i32 %call8, i32* %retval, align 4, !dbg !859
  br label %return, !dbg !859

return:                                           ; preds = %do.end, %if.then6, %if.then
  %12 = load i32, i32* %retval, align 4, !dbg !860
  ret i32 %12, !dbg !860
}

; Function Attrs: argmemonly nounwind
declare void @llvm.memcpy.p0i8.p0i8.i64(i8* nocapture, i8* nocapture readonly, i64, i32, i1) #2

; Function Attrs: nounwind uwtable
define internal zeroext i1 @lz_encoder_init(%struct.lzma_mf_s* %mf, %struct.lzma_allocator* %allocator, %struct.lzma_lz_options* %lz_options) #0 !dbg !239 {
entry:
  %retval = alloca i1, align 1
  %mf.addr = alloca %struct.lzma_mf_s*, align 8
  %allocator.addr = alloca %struct.lzma_allocator*, align 8
  %lz_options.addr = alloca %struct.lzma_lz_options*, align 8
  %alloc_count = alloca i64, align 8
  store %struct.lzma_mf_s* %mf, %struct.lzma_mf_s** %mf.addr, align 8
  call void @llvm.dbg.declare(metadata %struct.lzma_mf_s** %mf.addr, metadata !861, metadata !247), !dbg !862
  store %struct.lzma_allocator* %allocator, %struct.lzma_allocator** %allocator.addr, align 8
  call void @llvm.dbg.declare(metadata %struct.lzma_allocator** %allocator.addr, metadata !863, metadata !247), !dbg !864
  store %struct.lzma_lz_options* %lz_options, %struct.lzma_lz_options** %lz_options.addr, align 8
  call void @llvm.dbg.declare(metadata %struct.lzma_lz_options** %lz_options.addr, metadata !865, metadata !247), !dbg !866
  call void @llvm.dbg.declare(metadata i64* %alloc_count, metadata !867, metadata !247), !dbg !868
  %0 = load %struct.lzma_mf_s*, %struct.lzma_mf_s** %mf.addr, align 8, !dbg !869
  %buffer = getelementptr inbounds %struct.lzma_mf_s, %struct.lzma_mf_s* %0, i32 0, i32 0, !dbg !871
  %1 = load i8*, i8** %buffer, align 8, !dbg !871
  %cmp = icmp eq i8* %1, null, !dbg !872
  br i1 %cmp, label %if.then, label %if.end6, !dbg !873

if.then:                                          ; preds = %entry
  %2 = load %struct.lzma_mf_s*, %struct.lzma_mf_s** %mf.addr, align 8, !dbg !874
  %size = getelementptr inbounds %struct.lzma_mf_s, %struct.lzma_mf_s* %2, i32 0, i32 1, !dbg !876
  %3 = load i32, i32* %size, align 8, !dbg !876
  %conv = zext i32 %3 to i64, !dbg !874
  %4 = load %struct.lzma_allocator*, %struct.lzma_allocator** %allocator.addr, align 8, !dbg !877
  %call = call noalias i8* @lzma_alloc(i64 %conv, %struct.lzma_allocator* %4), !dbg !878
  %5 = load %struct.lzma_mf_s*, %struct.lzma_mf_s** %mf.addr, align 8, !dbg !879
  %buffer1 = getelementptr inbounds %struct.lzma_mf_s, %struct.lzma_mf_s* %5, i32 0, i32 0, !dbg !880
  store i8* %call, i8** %buffer1, align 8, !dbg !881
  %6 = load %struct.lzma_mf_s*, %struct.lzma_mf_s** %mf.addr, align 8, !dbg !882
  %buffer2 = getelementptr inbounds %struct.lzma_mf_s, %struct.lzma_mf_s* %6, i32 0, i32 0, !dbg !884
  %7 = load i8*, i8** %buffer2, align 8, !dbg !884
  %cmp3 = icmp eq i8* %7, null, !dbg !885
  br i1 %cmp3, label %if.then5, label %if.end, !dbg !886

if.then5:                                         ; preds = %if.then
  store i1 true, i1* %retval, align 1, !dbg !887
  br label %return, !dbg !887

if.end:                                           ; preds = %if.then
  br label %if.end6, !dbg !888

if.end6:                                          ; preds = %if.end, %entry
  %8 = load %struct.lzma_mf_s*, %struct.lzma_mf_s** %mf.addr, align 8, !dbg !889
  %cyclic_size = getelementptr inbounds %struct.lzma_mf_s, %struct.lzma_mf_s* %8, i32 0, i32 15, !dbg !890
  %9 = load i32, i32* %cyclic_size, align 4, !dbg !890
  %10 = load %struct.lzma_mf_s*, %struct.lzma_mf_s** %mf.addr, align 8, !dbg !891
  %offset = getelementptr inbounds %struct.lzma_mf_s, %struct.lzma_mf_s* %10, i32 0, i32 4, !dbg !892
  store i32 %9, i32* %offset, align 4, !dbg !893
  %11 = load %struct.lzma_mf_s*, %struct.lzma_mf_s** %mf.addr, align 8, !dbg !894
  %read_pos = getelementptr inbounds %struct.lzma_mf_s, %struct.lzma_mf_s* %11, i32 0, i32 5, !dbg !895
  store i32 0, i32* %read_pos, align 8, !dbg !896
  %12 = load %struct.lzma_mf_s*, %struct.lzma_mf_s** %mf.addr, align 8, !dbg !897
  %read_ahead = getelementptr inbounds %struct.lzma_mf_s, %struct.lzma_mf_s* %12, i32 0, i32 6, !dbg !898
  store i32 0, i32* %read_ahead, align 4, !dbg !899
  %13 = load %struct.lzma_mf_s*, %struct.lzma_mf_s** %mf.addr, align 8, !dbg !900
  %read_limit = getelementptr inbounds %struct.lzma_mf_s, %struct.lzma_mf_s* %13, i32 0, i32 7, !dbg !901
  store i32 0, i32* %read_limit, align 8, !dbg !902
  %14 = load %struct.lzma_mf_s*, %struct.lzma_mf_s** %mf.addr, align 8, !dbg !903
  %write_pos = getelementptr inbounds %struct.lzma_mf_s, %struct.lzma_mf_s* %14, i32 0, i32 8, !dbg !904
  store i32 0, i32* %write_pos, align 4, !dbg !905
  %15 = load %struct.lzma_mf_s*, %struct.lzma_mf_s** %mf.addr, align 8, !dbg !906
  %pending = getelementptr inbounds %struct.lzma_mf_s, %struct.lzma_mf_s* %15, i32 0, i32 9, !dbg !907
  store i32 0, i32* %pending, align 8, !dbg !908
  %16 = load %struct.lzma_mf_s*, %struct.lzma_mf_s** %mf.addr, align 8, !dbg !909
  %hash_size_sum = getelementptr inbounds %struct.lzma_mf_s, %struct.lzma_mf_s* %16, i32 0, i32 21, !dbg !910
  %17 = load i32, i32* %hash_size_sum, align 4, !dbg !910
  %18 = load %struct.lzma_mf_s*, %struct.lzma_mf_s** %mf.addr, align 8, !dbg !911
  %sons_count = getelementptr inbounds %struct.lzma_mf_s, %struct.lzma_mf_s* %18, i32 0, i32 22, !dbg !912
  %19 = load i32, i32* %sons_count, align 8, !dbg !912
  %add = add i32 %17, %19, !dbg !913
  %conv7 = zext i32 %add to i64, !dbg !909
  store i64 %conv7, i64* %alloc_count, align 8, !dbg !914
  %20 = load %struct.lzma_mf_s*, %struct.lzma_mf_s** %mf.addr, align 8, !dbg !915
  %hash = getelementptr inbounds %struct.lzma_mf_s, %struct.lzma_mf_s* %20, i32 0, i32 12, !dbg !917
  %21 = load i32*, i32** %hash, align 8, !dbg !917
  %cmp8 = icmp eq i32* %21, null, !dbg !918
  br i1 %cmp8, label %if.then10, label %if.end18, !dbg !919

if.then10:                                        ; preds = %if.end6
  %22 = load i64, i64* %alloc_count, align 8, !dbg !920
  %mul = mul i64 %22, 4, !dbg !922
  %23 = load %struct.lzma_allocator*, %struct.lzma_allocator** %allocator.addr, align 8, !dbg !923
  %call11 = call noalias i8* @lzma_alloc(i64 %mul, %struct.lzma_allocator* %23), !dbg !924
  %24 = bitcast i8* %call11 to i32*, !dbg !924
  %25 = load %struct.lzma_mf_s*, %struct.lzma_mf_s** %mf.addr, align 8, !dbg !925
  %hash12 = getelementptr inbounds %struct.lzma_mf_s, %struct.lzma_mf_s* %25, i32 0, i32 12, !dbg !926
  store i32* %24, i32** %hash12, align 8, !dbg !927
  %26 = load %struct.lzma_mf_s*, %struct.lzma_mf_s** %mf.addr, align 8, !dbg !928
  %hash13 = getelementptr inbounds %struct.lzma_mf_s, %struct.lzma_mf_s* %26, i32 0, i32 12, !dbg !930
  %27 = load i32*, i32** %hash13, align 8, !dbg !930
  %cmp14 = icmp eq i32* %27, null, !dbg !931
  br i1 %cmp14, label %if.then16, label %if.end17, !dbg !932

if.then16:                                        ; preds = %if.then10
  store i1 true, i1* %retval, align 1, !dbg !933
  br label %return, !dbg !933

if.end17:                                         ; preds = %if.then10
  br label %if.end18, !dbg !934

if.end18:                                         ; preds = %if.end17, %if.end6
  %28 = load %struct.lzma_mf_s*, %struct.lzma_mf_s** %mf.addr, align 8, !dbg !935
  %hash19 = getelementptr inbounds %struct.lzma_mf_s, %struct.lzma_mf_s* %28, i32 0, i32 12, !dbg !936
  %29 = load i32*, i32** %hash19, align 8, !dbg !936
  %30 = load %struct.lzma_mf_s*, %struct.lzma_mf_s** %mf.addr, align 8, !dbg !937
  %hash_size_sum20 = getelementptr inbounds %struct.lzma_mf_s, %struct.lzma_mf_s* %30, i32 0, i32 21, !dbg !938
  %31 = load i32, i32* %hash_size_sum20, align 4, !dbg !938
  %idx.ext = zext i32 %31 to i64, !dbg !939
  %add.ptr = getelementptr inbounds i32, i32* %29, i64 %idx.ext, !dbg !939
  %32 = load %struct.lzma_mf_s*, %struct.lzma_mf_s** %mf.addr, align 8, !dbg !940
  %son = getelementptr inbounds %struct.lzma_mf_s, %struct.lzma_mf_s* %32, i32 0, i32 13, !dbg !941
  store i32* %add.ptr, i32** %son, align 8, !dbg !942
  %33 = load %struct.lzma_mf_s*, %struct.lzma_mf_s** %mf.addr, align 8, !dbg !943
  %cyclic_pos = getelementptr inbounds %struct.lzma_mf_s, %struct.lzma_mf_s* %33, i32 0, i32 14, !dbg !944
  store i32 0, i32* %cyclic_pos, align 8, !dbg !945
  %34 = load %struct.lzma_mf_s*, %struct.lzma_mf_s** %mf.addr, align 8, !dbg !946
  %hash21 = getelementptr inbounds %struct.lzma_mf_s, %struct.lzma_mf_s* %34, i32 0, i32 12, !dbg !946
  %35 = load i32*, i32** %hash21, align 8, !dbg !946
  %36 = bitcast i32* %35 to i8*, !dbg !946
  %37 = load %struct.lzma_mf_s*, %struct.lzma_mf_s** %mf.addr, align 8, !dbg !946
  %hash_size_sum22 = getelementptr inbounds %struct.lzma_mf_s, %struct.lzma_mf_s* %37, i32 0, i32 21, !dbg !946
  %38 = load i32, i32* %hash_size_sum22, align 4, !dbg !946
  %conv23 = zext i32 %38 to i64, !dbg !946
  %mul24 = mul i64 %conv23, 4, !dbg !946
  call void @llvm.memset.p0i8.i64(i8* %36, i8 0, i64 %mul24, i32 4, i1 false), !dbg !946
  %39 = load %struct.lzma_lz_options*, %struct.lzma_lz_options** %lz_options.addr, align 8, !dbg !947
  %preset_dict = getelementptr inbounds %struct.lzma_lz_options, %struct.lzma_lz_options* %39, i32 0, i32 7, !dbg !949
  %40 = load i8*, i8** %preset_dict, align 8, !dbg !949
  %cmp25 = icmp ne i8* %40, null, !dbg !950
  br i1 %cmp25, label %land.lhs.true, label %if.end48, !dbg !951

land.lhs.true:                                    ; preds = %if.end18
  %41 = load %struct.lzma_lz_options*, %struct.lzma_lz_options** %lz_options.addr, align 8, !dbg !952
  %preset_dict_size = getelementptr inbounds %struct.lzma_lz_options, %struct.lzma_lz_options* %41, i32 0, i32 8, !dbg !954
  %42 = load i32, i32* %preset_dict_size, align 8, !dbg !954
  %cmp27 = icmp ugt i32 %42, 0, !dbg !955
  br i1 %cmp27, label %if.then29, label %if.end48, !dbg !956

if.then29:                                        ; preds = %land.lhs.true
  %43 = load %struct.lzma_lz_options*, %struct.lzma_lz_options** %lz_options.addr, align 8, !dbg !958
  %preset_dict_size30 = getelementptr inbounds %struct.lzma_lz_options, %struct.lzma_lz_options* %43, i32 0, i32 8, !dbg !958
  %44 = load i32, i32* %preset_dict_size30, align 8, !dbg !958
  %45 = load %struct.lzma_mf_s*, %struct.lzma_mf_s** %mf.addr, align 8, !dbg !958
  %size31 = getelementptr inbounds %struct.lzma_mf_s, %struct.lzma_mf_s* %45, i32 0, i32 1, !dbg !958
  %46 = load i32, i32* %size31, align 8, !dbg !958
  %cmp32 = icmp ult i32 %44, %46, !dbg !958
  br i1 %cmp32, label %cond.true, label %cond.false, !dbg !958

cond.true:                                        ; preds = %if.then29
  %47 = load %struct.lzma_lz_options*, %struct.lzma_lz_options** %lz_options.addr, align 8, !dbg !960
  %preset_dict_size34 = getelementptr inbounds %struct.lzma_lz_options, %struct.lzma_lz_options* %47, i32 0, i32 8, !dbg !960
  %48 = load i32, i32* %preset_dict_size34, align 8, !dbg !960
  br label %cond.end, !dbg !960

cond.false:                                       ; preds = %if.then29
  %49 = load %struct.lzma_mf_s*, %struct.lzma_mf_s** %mf.addr, align 8, !dbg !962
  %size35 = getelementptr inbounds %struct.lzma_mf_s, %struct.lzma_mf_s* %49, i32 0, i32 1, !dbg !962
  %50 = load i32, i32* %size35, align 8, !dbg !962
  br label %cond.end, !dbg !962

cond.end:                                         ; preds = %cond.false, %cond.true
  %cond = phi i32 [ %48, %cond.true ], [ %50, %cond.false ], !dbg !964
  %51 = load %struct.lzma_mf_s*, %struct.lzma_mf_s** %mf.addr, align 8, !dbg !966
  %write_pos36 = getelementptr inbounds %struct.lzma_mf_s, %struct.lzma_mf_s* %51, i32 0, i32 8, !dbg !967
  store i32 %cond, i32* %write_pos36, align 4, !dbg !968
  %52 = load %struct.lzma_mf_s*, %struct.lzma_mf_s** %mf.addr, align 8, !dbg !969
  %buffer37 = getelementptr inbounds %struct.lzma_mf_s, %struct.lzma_mf_s* %52, i32 0, i32 0, !dbg !970
  %53 = load i8*, i8** %buffer37, align 8, !dbg !970
  %54 = load %struct.lzma_lz_options*, %struct.lzma_lz_options** %lz_options.addr, align 8, !dbg !971
  %preset_dict38 = getelementptr inbounds %struct.lzma_lz_options, %struct.lzma_lz_options* %54, i32 0, i32 7, !dbg !972
  %55 = load i8*, i8** %preset_dict38, align 8, !dbg !972
  %56 = load %struct.lzma_lz_options*, %struct.lzma_lz_options** %lz_options.addr, align 8, !dbg !973
  %preset_dict_size39 = getelementptr inbounds %struct.lzma_lz_options, %struct.lzma_lz_options* %56, i32 0, i32 8, !dbg !974
  %57 = load i32, i32* %preset_dict_size39, align 8, !dbg !974
  %idx.ext40 = zext i32 %57 to i64, !dbg !975
  %add.ptr41 = getelementptr inbounds i8, i8* %55, i64 %idx.ext40, !dbg !975
  %58 = load %struct.lzma_mf_s*, %struct.lzma_mf_s** %mf.addr, align 8, !dbg !976
  %write_pos42 = getelementptr inbounds %struct.lzma_mf_s, %struct.lzma_mf_s* %58, i32 0, i32 8, !dbg !977
  %59 = load i32, i32* %write_pos42, align 4, !dbg !977
  %idx.ext43 = zext i32 %59 to i64, !dbg !978
  %idx.neg = sub i64 0, %idx.ext43, !dbg !978
  %add.ptr44 = getelementptr inbounds i8, i8* %add.ptr41, i64 %idx.neg, !dbg !978
  %60 = load %struct.lzma_mf_s*, %struct.lzma_mf_s** %mf.addr, align 8, !dbg !979
  %write_pos45 = getelementptr inbounds %struct.lzma_mf_s, %struct.lzma_mf_s* %60, i32 0, i32 8, !dbg !980
  %61 = load i32, i32* %write_pos45, align 4, !dbg !980
  %conv46 = zext i32 %61 to i64, !dbg !979
  call void @llvm.memcpy.p0i8.p0i8.i64(i8* %53, i8* %add.ptr44, i64 %conv46, i32 1, i1 false), !dbg !981
  %62 = load %struct.lzma_mf_s*, %struct.lzma_mf_s** %mf.addr, align 8, !dbg !982
  %action = getelementptr inbounds %struct.lzma_mf_s, %struct.lzma_mf_s* %62, i32 0, i32 20, !dbg !983
  store i32 1, i32* %action, align 8, !dbg !984
  %63 = load %struct.lzma_mf_s*, %struct.lzma_mf_s** %mf.addr, align 8, !dbg !985
  %skip = getelementptr inbounds %struct.lzma_mf_s, %struct.lzma_mf_s* %63, i32 0, i32 11, !dbg !986
  %64 = load void (%struct.lzma_mf_s*, i32)*, void (%struct.lzma_mf_s*, i32)** %skip, align 8, !dbg !986
  %65 = load %struct.lzma_mf_s*, %struct.lzma_mf_s** %mf.addr, align 8, !dbg !987
  %66 = load %struct.lzma_mf_s*, %struct.lzma_mf_s** %mf.addr, align 8, !dbg !988
  %write_pos47 = getelementptr inbounds %struct.lzma_mf_s, %struct.lzma_mf_s* %66, i32 0, i32 8, !dbg !989
  %67 = load i32, i32* %write_pos47, align 4, !dbg !989
  call void %64(%struct.lzma_mf_s* %65, i32 %67), !dbg !985
  br label %if.end48, !dbg !990

if.end48:                                         ; preds = %cond.end, %land.lhs.true, %if.end18
  %68 = load %struct.lzma_mf_s*, %struct.lzma_mf_s** %mf.addr, align 8, !dbg !991
  %action49 = getelementptr inbounds %struct.lzma_mf_s, %struct.lzma_mf_s* %68, i32 0, i32 20, !dbg !992
  store i32 0, i32* %action49, align 8, !dbg !993
  store i1 false, i1* %retval, align 1, !dbg !994
  br label %return, !dbg !994

return:                                           ; preds = %if.end48, %if.then16, %if.then5
  %69 = load i1, i1* %retval, align 1, !dbg !995
  ret i1 %69, !dbg !995
}

declare i32 @lzma_next_filter_init(%struct.lzma_next_coder_s*, %struct.lzma_allocator*, %struct.lzma_filter_info_s*) #3

; Function Attrs: nounwind readnone uwtable
define zeroext i8 @lzma_mf_is_supported(i32 %mf) #4 !dbg !222 {
entry:
  %mf.addr = alloca i32, align 4
  %ret = alloca i8, align 1
  store i32 %mf, i32* %mf.addr, align 4
  call void @llvm.dbg.declare(metadata i32* %mf.addr, metadata !996, metadata !247), !dbg !997
  call void @llvm.dbg.declare(metadata i8* %ret, metadata !998, metadata !247), !dbg !999
  store i8 0, i8* %ret, align 1, !dbg !999
  %0 = load i32, i32* %mf.addr, align 4, !dbg !1000
  %cmp = icmp eq i32 %0, 3, !dbg !1002
  br i1 %cmp, label %if.then, label %if.end, !dbg !1003

if.then:                                          ; preds = %entry
  store i8 1, i8* %ret, align 1, !dbg !1004
  br label %if.end, !dbg !1005

if.end:                                           ; preds = %if.then, %entry
  %1 = load i32, i32* %mf.addr, align 4, !dbg !1006
  %cmp1 = icmp eq i32 %1, 4, !dbg !1008
  br i1 %cmp1, label %if.then2, label %if.end3, !dbg !1009

if.then2:                                         ; preds = %if.end
  store i8 1, i8* %ret, align 1, !dbg !1010
  br label %if.end3, !dbg !1011

if.end3:                                          ; preds = %if.then2, %if.end
  %2 = load i32, i32* %mf.addr, align 4, !dbg !1012
  %cmp4 = icmp eq i32 %2, 18, !dbg !1014
  br i1 %cmp4, label %if.then5, label %if.end6, !dbg !1015

if.then5:                                         ; preds = %if.end3
  store i8 1, i8* %ret, align 1, !dbg !1016
  br label %if.end6, !dbg !1017

if.end6:                                          ; preds = %if.then5, %if.end3
  %3 = load i32, i32* %mf.addr, align 4, !dbg !1018
  %cmp7 = icmp eq i32 %3, 19, !dbg !1020
  br i1 %cmp7, label %if.then8, label %if.end9, !dbg !1021

if.then8:                                         ; preds = %if.end6
  store i8 1, i8* %ret, align 1, !dbg !1022
  br label %if.end9, !dbg !1023

if.end9:                                          ; preds = %if.then8, %if.end6
  %4 = load i32, i32* %mf.addr, align 4, !dbg !1024
  %cmp10 = icmp eq i32 %4, 20, !dbg !1026
  br i1 %cmp10, label %if.then11, label %if.end12, !dbg !1027

if.then11:                                        ; preds = %if.end9
  store i8 1, i8* %ret, align 1, !dbg !1028
  br label %if.end12, !dbg !1029

if.end12:                                         ; preds = %if.then11, %if.end9
  %5 = load i8, i8* %ret, align 1, !dbg !1030
  %tobool = trunc i8 %5 to i1, !dbg !1030
  %conv = zext i1 %tobool to i8, !dbg !1030
  ret i8 %conv, !dbg !1031
}

declare void @lzma_free(i8*, %struct.lzma_allocator*) #3

declare i32 @lzma_mf_hc3_find(%struct.lzma_mf_s*, %struct.lzma_match*) #3

declare void @lzma_mf_hc3_skip(%struct.lzma_mf_s*, i32) #3

declare i32 @lzma_mf_hc4_find(%struct.lzma_mf_s*, %struct.lzma_match*) #3

declare void @lzma_mf_hc4_skip(%struct.lzma_mf_s*, i32) #3

declare i32 @lzma_mf_bt2_find(%struct.lzma_mf_s*, %struct.lzma_match*) #3

declare void @lzma_mf_bt2_skip(%struct.lzma_mf_s*, i32) #3

declare i32 @lzma_mf_bt3_find(%struct.lzma_mf_s*, %struct.lzma_match*) #3

declare void @lzma_mf_bt3_skip(%struct.lzma_mf_s*, i32) #3

declare i32 @lzma_mf_bt4_find(%struct.lzma_mf_s*, %struct.lzma_match*) #3

declare void @lzma_mf_bt4_skip(%struct.lzma_mf_s*, i32) #3

; Function Attrs: noreturn nounwind
declare void @__assert_fail(i8*, i8*, i32, i8*) #5

; Function Attrs: nounwind uwtable
define internal i32 @fill_window(%struct.lzma_coder_s* %coder, %struct.lzma_allocator* %allocator, i8* %in, i64* %in_pos, i64 %in_size, i32 %action) #0 !dbg !231 {
entry:
  %coder.addr = alloca %struct.lzma_coder_s*, align 8
  %allocator.addr = alloca %struct.lzma_allocator*, align 8
  %in.addr = alloca i8*, align 8
  %in_pos.addr = alloca i64*, align 8
  %in_size.addr = alloca i64, align 8
  %action.addr = alloca i32, align 4
  %write_pos = alloca i64, align 8
  %ret = alloca i32, align 4
  %pending76 = alloca i64, align 8
  store %struct.lzma_coder_s* %coder, %struct.lzma_coder_s** %coder.addr, align 8
  call void @llvm.dbg.declare(metadata %struct.lzma_coder_s** %coder.addr, metadata !1032, metadata !247), !dbg !1033
  store %struct.lzma_allocator* %allocator, %struct.lzma_allocator** %allocator.addr, align 8
  call void @llvm.dbg.declare(metadata %struct.lzma_allocator** %allocator.addr, metadata !1034, metadata !247), !dbg !1035
  store i8* %in, i8** %in.addr, align 8
  call void @llvm.dbg.declare(metadata i8** %in.addr, metadata !1036, metadata !247), !dbg !1037
  store i64* %in_pos, i64** %in_pos.addr, align 8
  call void @llvm.dbg.declare(metadata i64** %in_pos.addr, metadata !1038, metadata !247), !dbg !1039
  store i64 %in_size, i64* %in_size.addr, align 8
  call void @llvm.dbg.declare(metadata i64* %in_size.addr, metadata !1040, metadata !247), !dbg !1041
  store i32 %action, i32* %action.addr, align 4
  call void @llvm.dbg.declare(metadata i32* %action.addr, metadata !1042, metadata !247), !dbg !1043
  call void @llvm.dbg.declare(metadata i64* %write_pos, metadata !1044, metadata !247), !dbg !1045
  call void @llvm.dbg.declare(metadata i32* %ret, metadata !1046, metadata !247), !dbg !1047
  %0 = load %struct.lzma_coder_s*, %struct.lzma_coder_s** %coder.addr, align 8, !dbg !1048
  %mf = getelementptr inbounds %struct.lzma_coder_s, %struct.lzma_coder_s* %0, i32 0, i32 1, !dbg !1048
  %read_pos = getelementptr inbounds %struct.lzma_mf_s, %struct.lzma_mf_s* %mf, i32 0, i32 5, !dbg !1048
  %1 = load i32, i32* %read_pos, align 8, !dbg !1048
  %2 = load %struct.lzma_coder_s*, %struct.lzma_coder_s** %coder.addr, align 8, !dbg !1048
  %mf1 = getelementptr inbounds %struct.lzma_coder_s, %struct.lzma_coder_s* %2, i32 0, i32 1, !dbg !1048
  %write_pos2 = getelementptr inbounds %struct.lzma_mf_s, %struct.lzma_mf_s* %mf1, i32 0, i32 8, !dbg !1048
  %3 = load i32, i32* %write_pos2, align 4, !dbg !1048
  %cmp = icmp ule i32 %1, %3, !dbg !1048
  br i1 %cmp, label %cond.true, label %cond.false, !dbg !1048

cond.true:                                        ; preds = %entry
  br label %cond.end, !dbg !1049

cond.false:                                       ; preds = %entry
  call void @__assert_fail(i8* getelementptr inbounds ([42 x i8], [42 x i8]* @.str.2, i32 0, i32 0), i8* getelementptr inbounds ([78 x i8], [78 x i8]* @.str.1, i32 0, i32 0), i32 87, i8* getelementptr inbounds ([101 x i8], [101 x i8]* @__PRETTY_FUNCTION__.fill_window, i32 0, i32 0)) #6, !dbg !1051
  unreachable, !dbg !1051
                                                  ; No predecessors!
  br label %cond.end, !dbg !1053

cond.end:                                         ; preds = %4, %cond.true
  %5 = load %struct.lzma_coder_s*, %struct.lzma_coder_s** %coder.addr, align 8, !dbg !1055
  %mf3 = getelementptr inbounds %struct.lzma_coder_s, %struct.lzma_coder_s* %5, i32 0, i32 1, !dbg !1057
  %read_pos4 = getelementptr inbounds %struct.lzma_mf_s, %struct.lzma_mf_s* %mf3, i32 0, i32 5, !dbg !1058
  %6 = load i32, i32* %read_pos4, align 8, !dbg !1058
  %7 = load %struct.lzma_coder_s*, %struct.lzma_coder_s** %coder.addr, align 8, !dbg !1059
  %mf5 = getelementptr inbounds %struct.lzma_coder_s, %struct.lzma_coder_s* %7, i32 0, i32 1, !dbg !1060
  %size = getelementptr inbounds %struct.lzma_mf_s, %struct.lzma_mf_s* %mf5, i32 0, i32 1, !dbg !1061
  %8 = load i32, i32* %size, align 8, !dbg !1061
  %9 = load %struct.lzma_coder_s*, %struct.lzma_coder_s** %coder.addr, align 8, !dbg !1062
  %mf6 = getelementptr inbounds %struct.lzma_coder_s, %struct.lzma_coder_s* %9, i32 0, i32 1, !dbg !1063
  %keep_size_after = getelementptr inbounds %struct.lzma_mf_s, %struct.lzma_mf_s* %mf6, i32 0, i32 3, !dbg !1064
  %10 = load i32, i32* %keep_size_after, align 8, !dbg !1064
  %sub = sub i32 %8, %10, !dbg !1065
  %cmp7 = icmp uge i32 %6, %sub, !dbg !1066
  br i1 %cmp7, label %if.then, label %if.end, !dbg !1067

if.then:                                          ; preds = %cond.end
  %11 = load %struct.lzma_coder_s*, %struct.lzma_coder_s** %coder.addr, align 8, !dbg !1068
  %mf8 = getelementptr inbounds %struct.lzma_coder_s, %struct.lzma_coder_s* %11, i32 0, i32 1, !dbg !1069
  call void @move_window(%struct.lzma_mf_s* %mf8), !dbg !1070
  br label %if.end, !dbg !1070

if.end:                                           ; preds = %if.then, %cond.end
  %12 = load %struct.lzma_coder_s*, %struct.lzma_coder_s** %coder.addr, align 8, !dbg !1071
  %mf9 = getelementptr inbounds %struct.lzma_coder_s, %struct.lzma_coder_s* %12, i32 0, i32 1, !dbg !1072
  %write_pos10 = getelementptr inbounds %struct.lzma_mf_s, %struct.lzma_mf_s* %mf9, i32 0, i32 8, !dbg !1073
  %13 = load i32, i32* %write_pos10, align 4, !dbg !1073
  %conv = zext i32 %13 to i64, !dbg !1071
  store i64 %conv, i64* %write_pos, align 8, !dbg !1074
  %14 = load %struct.lzma_coder_s*, %struct.lzma_coder_s** %coder.addr, align 8, !dbg !1075
  %next = getelementptr inbounds %struct.lzma_coder_s, %struct.lzma_coder_s* %14, i32 0, i32 2, !dbg !1077
  %code = getelementptr inbounds %struct.lzma_next_coder_s, %struct.lzma_next_coder_s* %next, i32 0, i32 3, !dbg !1078
  %15 = load i32 (%struct.lzma_coder_s*, %struct.lzma_allocator*, i8*, i64*, i64, i8*, i64*, i64, i32)*, i32 (%struct.lzma_coder_s*, %struct.lzma_allocator*, i8*, i64*, i64, i8*, i64*, i64, i32)** %code, align 8, !dbg !1078
  %cmp11 = icmp eq i32 (%struct.lzma_coder_s*, %struct.lzma_allocator*, i8*, i64*, i64, i8*, i64*, i64, i32)* %15, null, !dbg !1079
  br i1 %cmp11, label %if.then13, label %if.else, !dbg !1080

if.then13:                                        ; preds = %if.end
  %16 = load i8*, i8** %in.addr, align 8, !dbg !1081
  %17 = load i64*, i64** %in_pos.addr, align 8, !dbg !1083
  %18 = load i64, i64* %in_size.addr, align 8, !dbg !1084
  %19 = load %struct.lzma_coder_s*, %struct.lzma_coder_s** %coder.addr, align 8, !dbg !1085
  %mf14 = getelementptr inbounds %struct.lzma_coder_s, %struct.lzma_coder_s* %19, i32 0, i32 1, !dbg !1086
  %buffer = getelementptr inbounds %struct.lzma_mf_s, %struct.lzma_mf_s* %mf14, i32 0, i32 0, !dbg !1087
  %20 = load i8*, i8** %buffer, align 8, !dbg !1087
  %21 = load %struct.lzma_coder_s*, %struct.lzma_coder_s** %coder.addr, align 8, !dbg !1088
  %mf15 = getelementptr inbounds %struct.lzma_coder_s, %struct.lzma_coder_s* %21, i32 0, i32 1, !dbg !1089
  %size16 = getelementptr inbounds %struct.lzma_mf_s, %struct.lzma_mf_s* %mf15, i32 0, i32 1, !dbg !1090
  %22 = load i32, i32* %size16, align 8, !dbg !1090
  %conv17 = zext i32 %22 to i64, !dbg !1088
  %call = call i64 @lzma_bufcpy(i8* %16, i64* %17, i64 %18, i8* %20, i64* %write_pos, i64 %conv17), !dbg !1091
  %23 = load i32, i32* %action.addr, align 4, !dbg !1092
  %cmp18 = icmp ne i32 %23, 0, !dbg !1093
  br i1 %cmp18, label %land.rhs, label %land.end, !dbg !1094

land.rhs:                                         ; preds = %if.then13
  %24 = load i64*, i64** %in_pos.addr, align 8, !dbg !1095
  %25 = load i64, i64* %24, align 8, !dbg !1097
  %26 = load i64, i64* %in_size.addr, align 8, !dbg !1098
  %cmp20 = icmp eq i64 %25, %26, !dbg !1099
  br label %land.end

land.end:                                         ; preds = %land.rhs, %if.then13
  %27 = phi i1 [ false, %if.then13 ], [ %cmp20, %land.rhs ]
  %cond = select i1 %27, i32 1, i32 0, !dbg !1100
  store i32 %cond, i32* %ret, align 4, !dbg !1102
  br label %if.end32, !dbg !1103

if.else:                                          ; preds = %if.end
  %28 = load %struct.lzma_coder_s*, %struct.lzma_coder_s** %coder.addr, align 8, !dbg !1104
  %next22 = getelementptr inbounds %struct.lzma_coder_s, %struct.lzma_coder_s* %28, i32 0, i32 2, !dbg !1106
  %code23 = getelementptr inbounds %struct.lzma_next_coder_s, %struct.lzma_next_coder_s* %next22, i32 0, i32 3, !dbg !1107
  %29 = load i32 (%struct.lzma_coder_s*, %struct.lzma_allocator*, i8*, i64*, i64, i8*, i64*, i64, i32)*, i32 (%struct.lzma_coder_s*, %struct.lzma_allocator*, i8*, i64*, i64, i8*, i64*, i64, i32)** %code23, align 8, !dbg !1107
  %30 = load %struct.lzma_coder_s*, %struct.lzma_coder_s** %coder.addr, align 8, !dbg !1108
  %next24 = getelementptr inbounds %struct.lzma_coder_s, %struct.lzma_coder_s* %30, i32 0, i32 2, !dbg !1109
  %coder25 = getelementptr inbounds %struct.lzma_next_coder_s, %struct.lzma_next_coder_s* %next24, i32 0, i32 0, !dbg !1110
  %31 = load %struct.lzma_coder_s*, %struct.lzma_coder_s** %coder25, align 8, !dbg !1110
  %32 = load %struct.lzma_allocator*, %struct.lzma_allocator** %allocator.addr, align 8, !dbg !1111
  %33 = load i8*, i8** %in.addr, align 8, !dbg !1112
  %34 = load i64*, i64** %in_pos.addr, align 8, !dbg !1113
  %35 = load i64, i64* %in_size.addr, align 8, !dbg !1114
  %36 = load %struct.lzma_coder_s*, %struct.lzma_coder_s** %coder.addr, align 8, !dbg !1115
  %mf26 = getelementptr inbounds %struct.lzma_coder_s, %struct.lzma_coder_s* %36, i32 0, i32 1, !dbg !1116
  %buffer27 = getelementptr inbounds %struct.lzma_mf_s, %struct.lzma_mf_s* %mf26, i32 0, i32 0, !dbg !1117
  %37 = load i8*, i8** %buffer27, align 8, !dbg !1117
  %38 = load %struct.lzma_coder_s*, %struct.lzma_coder_s** %coder.addr, align 8, !dbg !1118
  %mf28 = getelementptr inbounds %struct.lzma_coder_s, %struct.lzma_coder_s* %38, i32 0, i32 1, !dbg !1119
  %size29 = getelementptr inbounds %struct.lzma_mf_s, %struct.lzma_mf_s* %mf28, i32 0, i32 1, !dbg !1120
  %39 = load i32, i32* %size29, align 8, !dbg !1120
  %conv30 = zext i32 %39 to i64, !dbg !1118
  %40 = load i32, i32* %action.addr, align 4, !dbg !1121
  %call31 = call i32 %29(%struct.lzma_coder_s* %31, %struct.lzma_allocator* %32, i8* %33, i64* %34, i64 %35, i8* %37, i64* %write_pos, i64 %conv30, i32 %40), !dbg !1104
  store i32 %call31, i32* %ret, align 4, !dbg !1122
  br label %if.end32

if.end32:                                         ; preds = %if.else, %land.end
  %41 = load i64, i64* %write_pos, align 8, !dbg !1123
  %conv33 = trunc i64 %41 to i32, !dbg !1123
  %42 = load %struct.lzma_coder_s*, %struct.lzma_coder_s** %coder.addr, align 8, !dbg !1124
  %mf34 = getelementptr inbounds %struct.lzma_coder_s, %struct.lzma_coder_s* %42, i32 0, i32 1, !dbg !1125
  %write_pos35 = getelementptr inbounds %struct.lzma_mf_s, %struct.lzma_mf_s* %mf34, i32 0, i32 8, !dbg !1126
  store i32 %conv33, i32* %write_pos35, align 4, !dbg !1127
  %43 = load i32, i32* %ret, align 4, !dbg !1128
  %cmp36 = icmp eq i32 %43, 1, !dbg !1130
  br i1 %cmp36, label %if.then38, label %if.else49, !dbg !1131

if.then38:                                        ; preds = %if.end32
  %44 = load i64*, i64** %in_pos.addr, align 8, !dbg !1132
  %45 = load i64, i64* %44, align 8, !dbg !1132
  %46 = load i64, i64* %in_size.addr, align 8, !dbg !1132
  %cmp39 = icmp eq i64 %45, %46, !dbg !1132
  br i1 %cmp39, label %cond.true41, label %cond.false42, !dbg !1132

cond.true41:                                      ; preds = %if.then38
  br label %cond.end43, !dbg !1134

cond.false42:                                     ; preds = %if.then38
  call void @__assert_fail(i8* getelementptr inbounds ([19 x i8], [19 x i8]* @.str.3, i32 0, i32 0), i8* getelementptr inbounds ([78 x i8], [78 x i8]* @.str.1, i32 0, i32 0), i32 119, i8* getelementptr inbounds ([101 x i8], [101 x i8]* @__PRETTY_FUNCTION__.fill_window, i32 0, i32 0)) #6, !dbg !1136
  unreachable, !dbg !1136
                                                  ; No predecessors!
  br label %cond.end43, !dbg !1138

cond.end43:                                       ; preds = %47, %cond.true41
  store i32 0, i32* %ret, align 4, !dbg !1140
  %48 = load i32, i32* %action.addr, align 4, !dbg !1141
  %49 = load %struct.lzma_coder_s*, %struct.lzma_coder_s** %coder.addr, align 8, !dbg !1142
  %mf44 = getelementptr inbounds %struct.lzma_coder_s, %struct.lzma_coder_s* %49, i32 0, i32 1, !dbg !1143
  %action45 = getelementptr inbounds %struct.lzma_mf_s, %struct.lzma_mf_s* %mf44, i32 0, i32 20, !dbg !1144
  store i32 %48, i32* %action45, align 8, !dbg !1145
  %50 = load %struct.lzma_coder_s*, %struct.lzma_coder_s** %coder.addr, align 8, !dbg !1146
  %mf46 = getelementptr inbounds %struct.lzma_coder_s, %struct.lzma_coder_s* %50, i32 0, i32 1, !dbg !1147
  %write_pos47 = getelementptr inbounds %struct.lzma_mf_s, %struct.lzma_mf_s* %mf46, i32 0, i32 8, !dbg !1148
  %51 = load i32, i32* %write_pos47, align 4, !dbg !1148
  %52 = load %struct.lzma_coder_s*, %struct.lzma_coder_s** %coder.addr, align 8, !dbg !1149
  %mf48 = getelementptr inbounds %struct.lzma_coder_s, %struct.lzma_coder_s* %52, i32 0, i32 1, !dbg !1150
  %read_limit = getelementptr inbounds %struct.lzma_mf_s, %struct.lzma_mf_s* %mf48, i32 0, i32 7, !dbg !1151
  store i32 %51, i32* %read_limit, align 8, !dbg !1152
  br label %if.end65, !dbg !1153

if.else49:                                        ; preds = %if.end32
  %53 = load %struct.lzma_coder_s*, %struct.lzma_coder_s** %coder.addr, align 8, !dbg !1154
  %mf50 = getelementptr inbounds %struct.lzma_coder_s, %struct.lzma_coder_s* %53, i32 0, i32 1, !dbg !1157
  %write_pos51 = getelementptr inbounds %struct.lzma_mf_s, %struct.lzma_mf_s* %mf50, i32 0, i32 8, !dbg !1158
  %54 = load i32, i32* %write_pos51, align 4, !dbg !1158
  %55 = load %struct.lzma_coder_s*, %struct.lzma_coder_s** %coder.addr, align 8, !dbg !1159
  %mf52 = getelementptr inbounds %struct.lzma_coder_s, %struct.lzma_coder_s* %55, i32 0, i32 1, !dbg !1160
  %keep_size_after53 = getelementptr inbounds %struct.lzma_mf_s, %struct.lzma_mf_s* %mf52, i32 0, i32 3, !dbg !1161
  %56 = load i32, i32* %keep_size_after53, align 8, !dbg !1161
  %cmp54 = icmp ugt i32 %54, %56, !dbg !1162
  br i1 %cmp54, label %if.then56, label %if.end64, !dbg !1154

if.then56:                                        ; preds = %if.else49
  %57 = load %struct.lzma_coder_s*, %struct.lzma_coder_s** %coder.addr, align 8, !dbg !1163
  %mf57 = getelementptr inbounds %struct.lzma_coder_s, %struct.lzma_coder_s* %57, i32 0, i32 1, !dbg !1165
  %write_pos58 = getelementptr inbounds %struct.lzma_mf_s, %struct.lzma_mf_s* %mf57, i32 0, i32 8, !dbg !1166
  %58 = load i32, i32* %write_pos58, align 4, !dbg !1166
  %59 = load %struct.lzma_coder_s*, %struct.lzma_coder_s** %coder.addr, align 8, !dbg !1167
  %mf59 = getelementptr inbounds %struct.lzma_coder_s, %struct.lzma_coder_s* %59, i32 0, i32 1, !dbg !1168
  %keep_size_after60 = getelementptr inbounds %struct.lzma_mf_s, %struct.lzma_mf_s* %mf59, i32 0, i32 3, !dbg !1169
  %60 = load i32, i32* %keep_size_after60, align 8, !dbg !1169
  %sub61 = sub i32 %58, %60, !dbg !1170
  %61 = load %struct.lzma_coder_s*, %struct.lzma_coder_s** %coder.addr, align 8, !dbg !1171
  %mf62 = getelementptr inbounds %struct.lzma_coder_s, %struct.lzma_coder_s* %61, i32 0, i32 1, !dbg !1172
  %read_limit63 = getelementptr inbounds %struct.lzma_mf_s, %struct.lzma_mf_s* %mf62, i32 0, i32 7, !dbg !1173
  store i32 %sub61, i32* %read_limit63, align 8, !dbg !1174
  br label %if.end64, !dbg !1175

if.end64:                                         ; preds = %if.then56, %if.else49
  br label %if.end65

if.end65:                                         ; preds = %if.end64, %cond.end43
  %62 = load %struct.lzma_coder_s*, %struct.lzma_coder_s** %coder.addr, align 8, !dbg !1176
  %mf66 = getelementptr inbounds %struct.lzma_coder_s, %struct.lzma_coder_s* %62, i32 0, i32 1, !dbg !1178
  %pending = getelementptr inbounds %struct.lzma_mf_s, %struct.lzma_mf_s* %mf66, i32 0, i32 9, !dbg !1179
  %63 = load i32, i32* %pending, align 8, !dbg !1179
  %cmp67 = icmp ugt i32 %63, 0, !dbg !1180
  br i1 %cmp67, label %land.lhs.true, label %if.end98, !dbg !1181

land.lhs.true:                                    ; preds = %if.end65
  %64 = load %struct.lzma_coder_s*, %struct.lzma_coder_s** %coder.addr, align 8, !dbg !1182
  %mf69 = getelementptr inbounds %struct.lzma_coder_s, %struct.lzma_coder_s* %64, i32 0, i32 1, !dbg !1184
  %read_pos70 = getelementptr inbounds %struct.lzma_mf_s, %struct.lzma_mf_s* %mf69, i32 0, i32 5, !dbg !1185
  %65 = load i32, i32* %read_pos70, align 8, !dbg !1185
  %66 = load %struct.lzma_coder_s*, %struct.lzma_coder_s** %coder.addr, align 8, !dbg !1186
  %mf71 = getelementptr inbounds %struct.lzma_coder_s, %struct.lzma_coder_s* %66, i32 0, i32 1, !dbg !1187
  %read_limit72 = getelementptr inbounds %struct.lzma_mf_s, %struct.lzma_mf_s* %mf71, i32 0, i32 7, !dbg !1188
  %67 = load i32, i32* %read_limit72, align 8, !dbg !1188
  %cmp73 = icmp ult i32 %65, %67, !dbg !1189
  br i1 %cmp73, label %if.then75, label %if.end98, !dbg !1190

if.then75:                                        ; preds = %land.lhs.true
  call void @llvm.dbg.declare(metadata i64* %pending76, metadata !1191, metadata !247), !dbg !1194
  %68 = load %struct.lzma_coder_s*, %struct.lzma_coder_s** %coder.addr, align 8, !dbg !1195
  %mf77 = getelementptr inbounds %struct.lzma_coder_s, %struct.lzma_coder_s* %68, i32 0, i32 1, !dbg !1196
  %pending78 = getelementptr inbounds %struct.lzma_mf_s, %struct.lzma_mf_s* %mf77, i32 0, i32 9, !dbg !1197
  %69 = load i32, i32* %pending78, align 8, !dbg !1197
  %conv79 = zext i32 %69 to i64, !dbg !1195
  store i64 %conv79, i64* %pending76, align 8, !dbg !1194
  %70 = load %struct.lzma_coder_s*, %struct.lzma_coder_s** %coder.addr, align 8, !dbg !1198
  %mf80 = getelementptr inbounds %struct.lzma_coder_s, %struct.lzma_coder_s* %70, i32 0, i32 1, !dbg !1199
  %pending81 = getelementptr inbounds %struct.lzma_mf_s, %struct.lzma_mf_s* %mf80, i32 0, i32 9, !dbg !1200
  store i32 0, i32* %pending81, align 8, !dbg !1201
  %71 = load %struct.lzma_coder_s*, %struct.lzma_coder_s** %coder.addr, align 8, !dbg !1202
  %mf82 = getelementptr inbounds %struct.lzma_coder_s, %struct.lzma_coder_s* %71, i32 0, i32 1, !dbg !1202
  %read_pos83 = getelementptr inbounds %struct.lzma_mf_s, %struct.lzma_mf_s* %mf82, i32 0, i32 5, !dbg !1202
  %72 = load i32, i32* %read_pos83, align 8, !dbg !1202
  %conv84 = zext i32 %72 to i64, !dbg !1202
  %73 = load i64, i64* %pending76, align 8, !dbg !1202
  %cmp85 = icmp uge i64 %conv84, %73, !dbg !1202
  br i1 %cmp85, label %cond.true87, label %cond.false88, !dbg !1202

cond.true87:                                      ; preds = %if.then75
  br label %cond.end89, !dbg !1203

cond.false88:                                     ; preds = %if.then75
  call void @__assert_fail(i8* getelementptr inbounds ([30 x i8], [30 x i8]* @.str.4, i32 0, i32 0), i8* getelementptr inbounds ([78 x i8], [78 x i8]* @.str.1, i32 0, i32 0), i32 142, i8* getelementptr inbounds ([101 x i8], [101 x i8]* @__PRETTY_FUNCTION__.fill_window, i32 0, i32 0)) #6, !dbg !1205
  unreachable, !dbg !1205
                                                  ; No predecessors!
  br label %cond.end89, !dbg !1207

cond.end89:                                       ; preds = %74, %cond.true87
  %75 = load i64, i64* %pending76, align 8, !dbg !1209
  %76 = load %struct.lzma_coder_s*, %struct.lzma_coder_s** %coder.addr, align 8, !dbg !1210
  %mf90 = getelementptr inbounds %struct.lzma_coder_s, %struct.lzma_coder_s* %76, i32 0, i32 1, !dbg !1211
  %read_pos91 = getelementptr inbounds %struct.lzma_mf_s, %struct.lzma_mf_s* %mf90, i32 0, i32 5, !dbg !1212
  %77 = load i32, i32* %read_pos91, align 8, !dbg !1213
  %conv92 = zext i32 %77 to i64, !dbg !1213
  %sub93 = sub i64 %conv92, %75, !dbg !1213
  %conv94 = trunc i64 %sub93 to i32, !dbg !1213
  store i32 %conv94, i32* %read_pos91, align 8, !dbg !1213
  %78 = load %struct.lzma_coder_s*, %struct.lzma_coder_s** %coder.addr, align 8, !dbg !1214
  %mf95 = getelementptr inbounds %struct.lzma_coder_s, %struct.lzma_coder_s* %78, i32 0, i32 1, !dbg !1215
  %skip = getelementptr inbounds %struct.lzma_mf_s, %struct.lzma_mf_s* %mf95, i32 0, i32 11, !dbg !1216
  %79 = load void (%struct.lzma_mf_s*, i32)*, void (%struct.lzma_mf_s*, i32)** %skip, align 8, !dbg !1216
  %80 = load %struct.lzma_coder_s*, %struct.lzma_coder_s** %coder.addr, align 8, !dbg !1217
  %mf96 = getelementptr inbounds %struct.lzma_coder_s, %struct.lzma_coder_s* %80, i32 0, i32 1, !dbg !1218
  %81 = load i64, i64* %pending76, align 8, !dbg !1219
  %conv97 = trunc i64 %81 to i32, !dbg !1219
  call void %79(%struct.lzma_mf_s* %mf96, i32 %conv97), !dbg !1214
  br label %if.end98, !dbg !1220

if.end98:                                         ; preds = %cond.end89, %land.lhs.true, %if.end65
  %82 = load i32, i32* %ret, align 4, !dbg !1221
  ret i32 %82, !dbg !1222
}

; Function Attrs: nounwind uwtable
define internal void @move_window(%struct.lzma_mf_s* %mf) #0 !dbg !234 {
entry:
  %mf.addr = alloca %struct.lzma_mf_s*, align 8
  %move_offset = alloca i32, align 4
  %move_size = alloca i64, align 8
  store %struct.lzma_mf_s* %mf, %struct.lzma_mf_s** %mf.addr, align 8
  call void @llvm.dbg.declare(metadata %struct.lzma_mf_s** %mf.addr, metadata !1223, metadata !247), !dbg !1224
  call void @llvm.dbg.declare(metadata i32* %move_offset, metadata !1225, metadata !247), !dbg !1226
  call void @llvm.dbg.declare(metadata i64* %move_size, metadata !1227, metadata !247), !dbg !1228
  %0 = load %struct.lzma_mf_s*, %struct.lzma_mf_s** %mf.addr, align 8, !dbg !1229
  %read_pos = getelementptr inbounds %struct.lzma_mf_s, %struct.lzma_mf_s* %0, i32 0, i32 5, !dbg !1229
  %1 = load i32, i32* %read_pos, align 8, !dbg !1229
  %2 = load %struct.lzma_mf_s*, %struct.lzma_mf_s** %mf.addr, align 8, !dbg !1229
  %keep_size_before = getelementptr inbounds %struct.lzma_mf_s, %struct.lzma_mf_s* %2, i32 0, i32 2, !dbg !1229
  %3 = load i32, i32* %keep_size_before, align 4, !dbg !1229
  %cmp = icmp ugt i32 %1, %3, !dbg !1229
  br i1 %cmp, label %cond.true, label %cond.false, !dbg !1229

cond.true:                                        ; preds = %entry
  br label %cond.end, !dbg !1230

cond.false:                                       ; preds = %entry
  call void @__assert_fail(i8* getelementptr inbounds ([36 x i8], [36 x i8]* @.str.5, i32 0, i32 0), i8* getelementptr inbounds ([78 x i8], [78 x i8]* @.str.1, i32 0, i32 0), i32 53, i8* getelementptr inbounds ([28 x i8], [28 x i8]* @__PRETTY_FUNCTION__.move_window, i32 0, i32 0)) #6, !dbg !1232
  unreachable, !dbg !1232
                                                  ; No predecessors!
  br label %cond.end, !dbg !1234

cond.end:                                         ; preds = %4, %cond.true
  %5 = load %struct.lzma_mf_s*, %struct.lzma_mf_s** %mf.addr, align 8, !dbg !1236
  %read_pos1 = getelementptr inbounds %struct.lzma_mf_s, %struct.lzma_mf_s* %5, i32 0, i32 5, !dbg !1237
  %6 = load i32, i32* %read_pos1, align 8, !dbg !1237
  %7 = load %struct.lzma_mf_s*, %struct.lzma_mf_s** %mf.addr, align 8, !dbg !1238
  %keep_size_before2 = getelementptr inbounds %struct.lzma_mf_s, %struct.lzma_mf_s* %7, i32 0, i32 2, !dbg !1239
  %8 = load i32, i32* %keep_size_before2, align 4, !dbg !1239
  %sub = sub i32 %6, %8, !dbg !1240
  %and = and i32 %sub, -16, !dbg !1241
  store i32 %and, i32* %move_offset, align 4, !dbg !1242
  %9 = load %struct.lzma_mf_s*, %struct.lzma_mf_s** %mf.addr, align 8, !dbg !1243
  %write_pos = getelementptr inbounds %struct.lzma_mf_s, %struct.lzma_mf_s* %9, i32 0, i32 8, !dbg !1243
  %10 = load i32, i32* %write_pos, align 4, !dbg !1243
  %11 = load i32, i32* %move_offset, align 4, !dbg !1243
  %cmp3 = icmp ugt i32 %10, %11, !dbg !1243
  br i1 %cmp3, label %cond.true4, label %cond.false5, !dbg !1243

cond.true4:                                       ; preds = %cond.end
  br label %cond.end6, !dbg !1244

cond.false5:                                      ; preds = %cond.end
  call void @__assert_fail(i8* getelementptr inbounds ([28 x i8], [28 x i8]* @.str.6, i32 0, i32 0), i8* getelementptr inbounds ([78 x i8], [78 x i8]* @.str.1, i32 0, i32 0), i32 56, i8* getelementptr inbounds ([28 x i8], [28 x i8]* @__PRETTY_FUNCTION__.move_window, i32 0, i32 0)) #6, !dbg !1245
  unreachable, !dbg !1245
                                                  ; No predecessors!
  br label %cond.end6, !dbg !1246

cond.end6:                                        ; preds = %12, %cond.true4
  %13 = load %struct.lzma_mf_s*, %struct.lzma_mf_s** %mf.addr, align 8, !dbg !1247
  %write_pos7 = getelementptr inbounds %struct.lzma_mf_s, %struct.lzma_mf_s* %13, i32 0, i32 8, !dbg !1248
  %14 = load i32, i32* %write_pos7, align 4, !dbg !1248
  %15 = load i32, i32* %move_offset, align 4, !dbg !1249
  %sub8 = sub i32 %14, %15, !dbg !1250
  %conv = zext i32 %sub8 to i64, !dbg !1247
  store i64 %conv, i64* %move_size, align 8, !dbg !1251
  %16 = load i32, i32* %move_offset, align 4, !dbg !1252
  %conv9 = zext i32 %16 to i64, !dbg !1252
  %17 = load i64, i64* %move_size, align 8, !dbg !1252
  %add = add i64 %conv9, %17, !dbg !1252
  %18 = load %struct.lzma_mf_s*, %struct.lzma_mf_s** %mf.addr, align 8, !dbg !1252
  %size = getelementptr inbounds %struct.lzma_mf_s, %struct.lzma_mf_s* %18, i32 0, i32 1, !dbg !1252
  %19 = load i32, i32* %size, align 8, !dbg !1252
  %conv10 = zext i32 %19 to i64, !dbg !1252
  %cmp11 = icmp ule i64 %add, %conv10, !dbg !1252
  br i1 %cmp11, label %cond.true13, label %cond.false14, !dbg !1252

cond.true13:                                      ; preds = %cond.end6
  br label %cond.end15, !dbg !1253

cond.false14:                                     ; preds = %cond.end6
  call void @__assert_fail(i8* getelementptr inbounds ([36 x i8], [36 x i8]* @.str.7, i32 0, i32 0), i8* getelementptr inbounds ([78 x i8], [78 x i8]* @.str.1, i32 0, i32 0), i32 59, i8* getelementptr inbounds ([28 x i8], [28 x i8]* @__PRETTY_FUNCTION__.move_window, i32 0, i32 0)) #6, !dbg !1254
  unreachable, !dbg !1254
                                                  ; No predecessors!
  br label %cond.end15, !dbg !1255

cond.end15:                                       ; preds = %20, %cond.true13
  %21 = load %struct.lzma_mf_s*, %struct.lzma_mf_s** %mf.addr, align 8, !dbg !1256
  %buffer = getelementptr inbounds %struct.lzma_mf_s, %struct.lzma_mf_s* %21, i32 0, i32 0, !dbg !1257
  %22 = load i8*, i8** %buffer, align 8, !dbg !1257
  %23 = load %struct.lzma_mf_s*, %struct.lzma_mf_s** %mf.addr, align 8, !dbg !1258
  %buffer16 = getelementptr inbounds %struct.lzma_mf_s, %struct.lzma_mf_s* %23, i32 0, i32 0, !dbg !1259
  %24 = load i8*, i8** %buffer16, align 8, !dbg !1259
  %25 = load i32, i32* %move_offset, align 4, !dbg !1260
  %idx.ext = zext i32 %25 to i64, !dbg !1261
  %add.ptr = getelementptr inbounds i8, i8* %24, i64 %idx.ext, !dbg !1261
  %26 = load i64, i64* %move_size, align 8, !dbg !1262
  call void @llvm.memmove.p0i8.p0i8.i64(i8* %22, i8* %add.ptr, i64 %26, i32 1, i1 false), !dbg !1263
  %27 = load i32, i32* %move_offset, align 4, !dbg !1264
  %28 = load %struct.lzma_mf_s*, %struct.lzma_mf_s** %mf.addr, align 8, !dbg !1265
  %offset = getelementptr inbounds %struct.lzma_mf_s, %struct.lzma_mf_s* %28, i32 0, i32 4, !dbg !1266
  %29 = load i32, i32* %offset, align 4, !dbg !1267
  %add17 = add i32 %29, %27, !dbg !1267
  store i32 %add17, i32* %offset, align 4, !dbg !1267
  %30 = load i32, i32* %move_offset, align 4, !dbg !1268
  %31 = load %struct.lzma_mf_s*, %struct.lzma_mf_s** %mf.addr, align 8, !dbg !1269
  %read_pos18 = getelementptr inbounds %struct.lzma_mf_s, %struct.lzma_mf_s* %31, i32 0, i32 5, !dbg !1270
  %32 = load i32, i32* %read_pos18, align 8, !dbg !1271
  %sub19 = sub i32 %32, %30, !dbg !1271
  store i32 %sub19, i32* %read_pos18, align 8, !dbg !1271
  %33 = load i32, i32* %move_offset, align 4, !dbg !1272
  %34 = load %struct.lzma_mf_s*, %struct.lzma_mf_s** %mf.addr, align 8, !dbg !1273
  %read_limit = getelementptr inbounds %struct.lzma_mf_s, %struct.lzma_mf_s* %34, i32 0, i32 7, !dbg !1274
  %35 = load i32, i32* %read_limit, align 8, !dbg !1275
  %sub20 = sub i32 %35, %33, !dbg !1275
  store i32 %sub20, i32* %read_limit, align 8, !dbg !1275
  %36 = load i32, i32* %move_offset, align 4, !dbg !1276
  %37 = load %struct.lzma_mf_s*, %struct.lzma_mf_s** %mf.addr, align 8, !dbg !1277
  %write_pos21 = getelementptr inbounds %struct.lzma_mf_s, %struct.lzma_mf_s* %37, i32 0, i32 8, !dbg !1278
  %38 = load i32, i32* %write_pos21, align 4, !dbg !1279
  %sub22 = sub i32 %38, %36, !dbg !1279
  store i32 %sub22, i32* %write_pos21, align 4, !dbg !1279
  ret void, !dbg !1280
}

declare i64 @lzma_bufcpy(i8*, i64*, i64, i8*, i64*, i64) #3

; Function Attrs: argmemonly nounwind
declare void @llvm.memmove.p0i8.p0i8.i64(i8* nocapture, i8* nocapture readonly, i64, i32, i1) #2

declare void @lzma_next_end(%struct.lzma_next_coder_s*, %struct.lzma_allocator*) #3

declare i32 @lzma_next_filter_update(%struct.lzma_next_coder_s*, %struct.lzma_allocator*, %struct.lzma_filter*) #3

attributes #0 = { nounwind uwtable "disable-tail-calls"="false" "less-precise-fpmad"="false" "no-frame-pointer-elim"="true" "no-frame-pointer-elim-non-leaf" "no-infs-fp-math"="false" "no-nans-fp-math"="false" "stack-protector-buffer-size"="8" "target-cpu"="x86-64" "target-features"="+fxsr,+mmx,+sse,+sse2" "unsafe-fp-math"="false" "use-soft-float"="false" }
attributes #1 = { nounwind readnone }
attributes #2 = { argmemonly nounwind }
attributes #3 = { "disable-tail-calls"="false" "less-precise-fpmad"="false" "no-frame-pointer-elim"="true" "no-frame-pointer-elim-non-leaf" "no-infs-fp-math"="false" "no-nans-fp-math"="false" "stack-protector-buffer-size"="8" "target-cpu"="x86-64" "target-features"="+fxsr,+mmx,+sse,+sse2" "unsafe-fp-math"="false" "use-soft-float"="false" }
attributes #4 = { nounwind readnone uwtable "disable-tail-calls"="false" "less-precise-fpmad"="false" "no-frame-pointer-elim"="true" "no-frame-pointer-elim-non-leaf" "no-infs-fp-math"="false" "no-nans-fp-math"="false" "stack-protector-buffer-size"="8" "target-cpu"="x86-64" "target-features"="+fxsr,+mmx,+sse,+sse2" "unsafe-fp-math"="false" "use-soft-float"="false" }
attributes #5 = { noreturn nounwind "disable-tail-calls"="false" "less-precise-fpmad"="false" "no-frame-pointer-elim"="true" "no-frame-pointer-elim-non-leaf" "no-infs-fp-math"="false" "no-nans-fp-math"="false" "stack-protector-buffer-size"="8" "target-cpu"="x86-64" "target-features"="+fxsr,+mmx,+sse,+sse2" "unsafe-fp-math"="false" "use-soft-float"="false" }
attributes #6 = { noreturn nounwind }

!llvm.dbg.cu = !{!0}
!llvm.module.flags = !{!243, !244}
!llvm.ident = !{!245}

!0 = distinct !DICompileUnit(language: DW_LANG_C99, file: !1, producer: "clang version 3.8.0 (tags/RELEASE_380/final)", isOptimized: false, runtimeVersion: 0, emissionKind: 1, enums: !2, retainedTypes: !39, subprograms: !46, globals: !240)
!1 = !DIFile(filename: "/data/download/cmake/cmake-master/Utilities/cmliblzma/liblzma/lz/lz_encoder.c", directory: "/data/download/cmake/cmake-master/Utilities/cmliblzma")
!2 = !{!3, !11, !18, !32}
!3 = !DICompositeType(tag: DW_TAG_enumeration_type, file: !4, line: 58, size: 32, align: 32, elements: !5)
!4 = !DIFile(filename: "/data/download/cmake/cmake-master/Utilities/cmliblzma/liblzma/api/lzma/lzma.h", directory: "/data/download/cmake/cmake-master/Utilities/cmliblzma")
!5 = !{!6, !7, !8, !9, !10}
!6 = !DIEnumerator(name: "LZMA_MF_HC3", value: 3)
!7 = !DIEnumerator(name: "LZMA_MF_HC4", value: 4)
!8 = !DIEnumerator(name: "LZMA_MF_BT2", value: 18)
!9 = !DIEnumerator(name: "LZMA_MF_BT3", value: 19)
!10 = !DIEnumerator(name: "LZMA_MF_BT4", value: 20)
!11 = !DICompositeType(tag: DW_TAG_enumeration_type, file: !12, line: 250, size: 32, align: 32, elements: !13)
!12 = !DIFile(filename: "/data/download/cmake/cmake-master/Utilities/cmliblzma/liblzma/api/lzma/base.h", directory: "/data/download/cmake/cmake-master/Utilities/cmliblzma")
!13 = !{!14, !15, !16, !17}
!14 = !DIEnumerator(name: "LZMA_RUN", value: 0)
!15 = !DIEnumerator(name: "LZMA_SYNC_FLUSH", value: 1)
!16 = !DIEnumerator(name: "LZMA_FULL_FLUSH", value: 2)
!17 = !DIEnumerator(name: "LZMA_FINISH", value: 3)
!18 = !DICompositeType(tag: DW_TAG_enumeration_type, file: !12, line: 57, size: 32, align: 32, elements: !19)
!19 = !{!20, !21, !22, !23, !24, !25, !26, !27, !28, !29, !30, !31}
!20 = !DIEnumerator(name: "LZMA_OK", value: 0)
!21 = !DIEnumerator(name: "LZMA_STREAM_END", value: 1)
!22 = !DIEnumerator(name: "LZMA_NO_CHECK", value: 2)
!23 = !DIEnumerator(name: "LZMA_UNSUPPORTED_CHECK", value: 3)
!24 = !DIEnumerator(name: "LZMA_GET_CHECK", value: 4)
!25 = !DIEnumerator(name: "LZMA_MEM_ERROR", value: 5)
!26 = !DIEnumerator(name: "LZMA_MEMLIMIT_ERROR", value: 6)
!27 = !DIEnumerator(name: "LZMA_FORMAT_ERROR", value: 7)
!28 = !DIEnumerator(name: "LZMA_OPTIONS_ERROR", value: 8)
!29 = !DIEnumerator(name: "LZMA_DATA_ERROR", value: 9)
!30 = !DIEnumerator(name: "LZMA_BUF_ERROR", value: 10)
!31 = !DIEnumerator(name: "LZMA_PROG_ERROR", value: 11)
!32 = !DICompositeType(tag: DW_TAG_enumeration_type, file: !33, line: 27, size: 32, align: 32, elements: !34)
!33 = !DIFile(filename: "/data/download/cmake/cmake-master/Utilities/cmliblzma/liblzma/api/lzma/check.h", directory: "/data/download/cmake/cmake-master/Utilities/cmliblzma")
!34 = !{!35, !36, !37, !38}
!35 = !DIEnumerator(name: "LZMA_CHECK_NONE", value: 0)
!36 = !DIEnumerator(name: "LZMA_CHECK_CRC32", value: 1)
!37 = !DIEnumerator(name: "LZMA_CHECK_CRC64", value: 4)
!38 = !DIEnumerator(name: "LZMA_CHECK_SHA256", value: 10)
!39 = !{!40, !43, !44}
!40 = !DIDerivedType(tag: DW_TAG_typedef, name: "uint64_t", file: !41, line: 55, baseType: !42)
!41 = !DIFile(filename: "/usr/include/stdint.h", directory: "/data/download/cmake/cmake-master/Utilities/cmliblzma")
!42 = !DIBasicType(name: "long unsigned int", size: 64, align: 64, encoding: DW_ATE_unsigned)
!43 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: null, size: 64, align: 64)
!44 = !DIDerivedType(tag: DW_TAG_typedef, name: "size_t", file: !45, line: 62, baseType: !42)
!45 = !DIFile(filename: "/opt/llvm-build/bin/../lib/clang/3.8.0/include/stddef.h", directory: "/data/download/cmake/cmake-master/Utilities/cmliblzma")
!46 = !{!47, !73, !222, !226, !230, !231, !234, !237, !238, !239}
!47 = distinct !DISubprogram(name: "lzma_lz_encoder_memusage", scope: !1, file: !1, line: 457, type: !48, isLocal: false, isDefinition: true, scopeLine: 458, flags: DIFlagPrototyped, isOptimized: false, variables: !72)
!48 = !DISubroutineType(types: !49)
!49 = !{!40, !50}
!50 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !51, size: 64, align: 64)
!51 = !DIDerivedType(tag: DW_TAG_const_type, baseType: !52)
!52 = !DIDerivedType(tag: DW_TAG_typedef, name: "lzma_lz_options", file: !53, line: 161, baseType: !54)
!53 = !DIFile(filename: "/data/download/cmake/cmake-master/Utilities/cmliblzma/liblzma/lz/lz_encoder.h", directory: "/data/download/cmake/cmake-master/Utilities/cmliblzma")
!54 = !DICompositeType(tag: DW_TAG_structure_type, file: !53, line: 129, size: 512, align: 64, elements: !55)
!55 = !{!56, !57, !58, !59, !60, !61, !63, !66, !71}
!56 = !DIDerivedType(tag: DW_TAG_member, name: "before_size", scope: !54, file: !53, line: 132, baseType: !44, size: 64, align: 64)
!57 = !DIDerivedType(tag: DW_TAG_member, name: "dict_size", scope: !54, file: !53, line: 135, baseType: !44, size: 64, align: 64, offset: 64)
!58 = !DIDerivedType(tag: DW_TAG_member, name: "after_size", scope: !54, file: !53, line: 139, baseType: !44, size: 64, align: 64, offset: 128)
!59 = !DIDerivedType(tag: DW_TAG_member, name: "match_len_max", scope: !54, file: !53, line: 144, baseType: !44, size: 64, align: 64, offset: 192)
!60 = !DIDerivedType(tag: DW_TAG_member, name: "nice_len", scope: !54, file: !53, line: 148, baseType: !44, size: 64, align: 64, offset: 256)
!61 = !DIDerivedType(tag: DW_TAG_member, name: "match_finder", scope: !54, file: !53, line: 151, baseType: !62, size: 32, align: 32, offset: 320)
!62 = !DIDerivedType(tag: DW_TAG_typedef, name: "lzma_match_finder", file: !4, line: 111, baseType: !3)
!63 = !DIDerivedType(tag: DW_TAG_member, name: "depth", scope: !54, file: !53, line: 154, baseType: !64, size: 32, align: 32, offset: 352)
!64 = !DIDerivedType(tag: DW_TAG_typedef, name: "uint32_t", file: !41, line: 51, baseType: !65)
!65 = !DIBasicType(name: "unsigned int", size: 32, align: 32, encoding: DW_ATE_unsigned)
!66 = !DIDerivedType(tag: DW_TAG_member, name: "preset_dict", scope: !54, file: !53, line: 157, baseType: !67, size: 64, align: 64, offset: 384)
!67 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !68, size: 64, align: 64)
!68 = !DIDerivedType(tag: DW_TAG_const_type, baseType: !69)
!69 = !DIDerivedType(tag: DW_TAG_typedef, name: "uint8_t", file: !41, line: 48, baseType: !70)
!70 = !DIBasicType(name: "unsigned char", size: 8, align: 8, encoding: DW_ATE_unsigned_char)
!71 = !DIDerivedType(tag: DW_TAG_member, name: "preset_dict_size", scope: !54, file: !53, line: 159, baseType: !64, size: 32, align: 32, offset: 448)
!72 = !{}
!73 = distinct !DISubprogram(name: "lzma_lz_encoder_init", scope: !1, file: !1, line: 508, type: !74, isLocal: false, isDefinition: true, scopeLine: 513, flags: DIFlagPrototyped, isOptimized: false, variables: !72)
!74 = !DISubroutineType(types: !75)
!75 = !{!76, !77, !147, !203, !215}
!76 = !DIDerivedType(tag: DW_TAG_typedef, name: "lzma_ret", file: !12, line: 237, baseType: !18)
!77 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !78, size: 64, align: 64)
!78 = !DIDerivedType(tag: DW_TAG_typedef, name: "lzma_next_coder", file: !79, line: 75, baseType: !80)
!79 = !DIFile(filename: "/data/download/cmake/cmake-master/Utilities/cmliblzma/liblzma/common/common.h", directory: "/data/download/cmake/cmake-master/Utilities/cmliblzma")
!80 = !DICompositeType(tag: DW_TAG_structure_type, name: "lzma_next_coder_s", file: !79, line: 119, size: 512, align: 64, elements: !81)
!81 = !{!82, !176, !177, !179, !185, !187, !194, !199}
!82 = !DIDerivedType(tag: DW_TAG_member, name: "coder", scope: !80, file: !79, line: 121, baseType: !83, size: 64, align: 64)
!83 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !84, size: 64, align: 64)
!84 = !DIDerivedType(tag: DW_TAG_typedef, name: "lzma_coder", file: !79, line: 73, baseType: !85)
!85 = !DICompositeType(tag: DW_TAG_structure_type, name: "lzma_coder_s", file: !1, line: 24, size: 1728, align: 64, elements: !86)
!86 = !{!87, !174, !175}
!87 = !DIDerivedType(tag: DW_TAG_member, name: "lz", scope: !85, file: !1, line: 26, baseType: !88, size: 256, align: 64)
!88 = !DIDerivedType(tag: DW_TAG_typedef, name: "lzma_lz_encoder", file: !53, line: 208, baseType: !89)
!89 = !DICompositeType(tag: DW_TAG_structure_type, file: !53, line: 192, size: 256, align: 64, elements: !90)
!90 = !{!91, !92, !143, !160}
!91 = !DIDerivedType(tag: DW_TAG_member, name: "coder", scope: !89, file: !53, line: 194, baseType: !83, size: 64, align: 64)
!92 = !DIDerivedType(tag: DW_TAG_member, name: "code", scope: !89, file: !53, line: 197, baseType: !93, size: 64, align: 64, offset: 64)
!93 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !94, size: 64, align: 64)
!94 = !DISubroutineType(types: !95)
!95 = !{!76, !96, !97, !140, !141, !44}
!96 = !DIDerivedType(tag: DW_TAG_restrict_type, baseType: !83)
!97 = !DIDerivedType(tag: DW_TAG_restrict_type, baseType: !98)
!98 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !99, size: 64, align: 64)
!99 = !DIDerivedType(tag: DW_TAG_typedef, name: "lzma_mf", file: !53, line: 28, baseType: !100)
!100 = !DICompositeType(tag: DW_TAG_structure_type, name: "lzma_mf_s", file: !53, line: 29, size: 960, align: 64, elements: !101)
!101 = !{!102, !104, !105, !106, !107, !108, !109, !110, !111, !112, !113, !123, !127, !129, !130, !131, !132, !133, !134, !135, !136, !138, !139}
!102 = !DIDerivedType(tag: DW_TAG_member, name: "buffer", scope: !100, file: !53, line: 35, baseType: !103, size: 64, align: 64)
!103 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !69, size: 64, align: 64)
!104 = !DIDerivedType(tag: DW_TAG_member, name: "size", scope: !100, file: !53, line: 39, baseType: !64, size: 32, align: 32, offset: 64)
!105 = !DIDerivedType(tag: DW_TAG_member, name: "keep_size_before", scope: !100, file: !53, line: 45, baseType: !64, size: 32, align: 32, offset: 96)
!106 = !DIDerivedType(tag: DW_TAG_member, name: "keep_size_after", scope: !100, file: !53, line: 51, baseType: !64, size: 32, align: 32, offset: 128)
!107 = !DIDerivedType(tag: DW_TAG_member, name: "offset", scope: !100, file: !53, line: 58, baseType: !64, size: 32, align: 32, offset: 160)
!108 = !DIDerivedType(tag: DW_TAG_member, name: "read_pos", scope: !100, file: !53, line: 63, baseType: !64, size: 32, align: 32, offset: 192)
!109 = !DIDerivedType(tag: DW_TAG_member, name: "read_ahead", scope: !100, file: !53, line: 67, baseType: !64, size: 32, align: 32, offset: 224)
!110 = !DIDerivedType(tag: DW_TAG_member, name: "read_limit", scope: !100, file: !53, line: 75, baseType: !64, size: 32, align: 32, offset: 256)
!111 = !DIDerivedType(tag: DW_TAG_member, name: "write_pos", scope: !100, file: !53, line: 80, baseType: !64, size: 32, align: 32, offset: 288)
!112 = !DIDerivedType(tag: DW_TAG_member, name: "pending", scope: !100, file: !53, line: 84, baseType: !64, size: 32, align: 32, offset: 320)
!113 = !DIDerivedType(tag: DW_TAG_member, name: "find", scope: !100, file: !53, line: 92, baseType: !114, size: 64, align: 64, offset: 384)
!114 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !115, size: 64, align: 64)
!115 = !DISubroutineType(types: !116)
!116 = !{!64, !98, !117}
!117 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !118, size: 64, align: 64)
!118 = !DIDerivedType(tag: DW_TAG_typedef, name: "lzma_match", file: !53, line: 25, baseType: !119)
!119 = !DICompositeType(tag: DW_TAG_structure_type, file: !53, line: 22, size: 64, align: 32, elements: !120)
!120 = !{!121, !122}
!121 = !DIDerivedType(tag: DW_TAG_member, name: "len", scope: !119, file: !53, line: 23, baseType: !64, size: 32, align: 32)
!122 = !DIDerivedType(tag: DW_TAG_member, name: "dist", scope: !119, file: !53, line: 24, baseType: !64, size: 32, align: 32, offset: 32)
!123 = !DIDerivedType(tag: DW_TAG_member, name: "skip", scope: !100, file: !53, line: 97, baseType: !124, size: 64, align: 64, offset: 448)
!124 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !125, size: 64, align: 64)
!125 = !DISubroutineType(types: !126)
!126 = !{null, !98, !64}
!127 = !DIDerivedType(tag: DW_TAG_member, name: "hash", scope: !100, file: !53, line: 99, baseType: !128, size: 64, align: 64, offset: 512)
!128 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !64, size: 64, align: 64)
!129 = !DIDerivedType(tag: DW_TAG_member, name: "son", scope: !100, file: !53, line: 100, baseType: !128, size: 64, align: 64, offset: 576)
!130 = !DIDerivedType(tag: DW_TAG_member, name: "cyclic_pos", scope: !100, file: !53, line: 101, baseType: !64, size: 32, align: 32, offset: 640)
!131 = !DIDerivedType(tag: DW_TAG_member, name: "cyclic_size", scope: !100, file: !53, line: 102, baseType: !64, size: 32, align: 32, offset: 672)
!132 = !DIDerivedType(tag: DW_TAG_member, name: "hash_mask", scope: !100, file: !53, line: 103, baseType: !64, size: 32, align: 32, offset: 704)
!133 = !DIDerivedType(tag: DW_TAG_member, name: "depth", scope: !100, file: !53, line: 106, baseType: !64, size: 32, align: 32, offset: 736)
!134 = !DIDerivedType(tag: DW_TAG_member, name: "nice_len", scope: !100, file: !53, line: 109, baseType: !64, size: 32, align: 32, offset: 768)
!135 = !DIDerivedType(tag: DW_TAG_member, name: "match_len_max", scope: !100, file: !53, line: 114, baseType: !64, size: 32, align: 32, offset: 800)
!136 = !DIDerivedType(tag: DW_TAG_member, name: "action", scope: !100, file: !53, line: 119, baseType: !137, size: 32, align: 32, offset: 832)
!137 = !DIDerivedType(tag: DW_TAG_typedef, name: "lzma_action", file: !12, line: 322, baseType: !11)
!138 = !DIDerivedType(tag: DW_TAG_member, name: "hash_size_sum", scope: !100, file: !53, line: 122, baseType: !64, size: 32, align: 32, offset: 864)
!139 = !DIDerivedType(tag: DW_TAG_member, name: "sons_count", scope: !100, file: !53, line: 125, baseType: !64, size: 32, align: 32, offset: 896)
!140 = !DIDerivedType(tag: DW_TAG_restrict_type, baseType: !103)
!141 = !DIDerivedType(tag: DW_TAG_restrict_type, baseType: !142)
!142 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !44, size: 64, align: 64)
!143 = !DIDerivedType(tag: DW_TAG_member, name: "end", scope: !89, file: !53, line: 202, baseType: !144, size: 64, align: 64, offset: 128)
!144 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !145, size: 64, align: 64)
!145 = !DISubroutineType(types: !146)
!146 = !{null, !83, !147}
!147 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !148, size: 64, align: 64)
!148 = !DIDerivedType(tag: DW_TAG_typedef, name: "lzma_allocator", file: !12, line: 403, baseType: !149)
!149 = !DICompositeType(tag: DW_TAG_structure_type, file: !12, line: 341, size: 192, align: 64, elements: !150)
!150 = !{!151, !155, !159}
!151 = !DIDerivedType(tag: DW_TAG_member, name: "alloc", scope: !149, file: !12, line: 376, baseType: !152, size: 64, align: 64)
!152 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !153, size: 64, align: 64)
!153 = !DISubroutineType(types: !154)
!154 = !{!43, !43, !44, !44}
!155 = !DIDerivedType(tag: DW_TAG_member, name: "free", scope: !149, file: !12, line: 390, baseType: !156, size: 64, align: 64, offset: 64)
!156 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !157, size: 64, align: 64)
!157 = !DISubroutineType(types: !158)
!158 = !{null, !43, !43}
!159 = !DIDerivedType(tag: DW_TAG_member, name: "opaque", scope: !149, file: !12, line: 401, baseType: !43, size: 64, align: 64, offset: 128)
!160 = !DIDerivedType(tag: DW_TAG_member, name: "options_update", scope: !89, file: !53, line: 205, baseType: !161, size: 64, align: 64, offset: 192)
!161 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !162, size: 64, align: 64)
!162 = !DISubroutineType(types: !163)
!163 = !{!76, !83, !164}
!164 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !165, size: 64, align: 64)
!165 = !DIDerivedType(tag: DW_TAG_const_type, baseType: !166)
!166 = !DIDerivedType(tag: DW_TAG_typedef, name: "lzma_filter", file: !167, line: 65, baseType: !168)
!167 = !DIFile(filename: "/data/download/cmake/cmake-master/Utilities/cmliblzma/liblzma/api/lzma/filter.h", directory: "/data/download/cmake/cmake-master/Utilities/cmliblzma")
!168 = !DICompositeType(tag: DW_TAG_structure_type, file: !167, line: 43, size: 128, align: 64, elements: !169)
!169 = !{!170, !173}
!170 = !DIDerivedType(tag: DW_TAG_member, name: "id", scope: !168, file: !167, line: 54, baseType: !171, size: 64, align: 64)
!171 = !DIDerivedType(tag: DW_TAG_typedef, name: "lzma_vli", file: !172, line: 63, baseType: !40)
!172 = !DIFile(filename: "/data/download/cmake/cmake-master/Utilities/cmliblzma/liblzma/api/lzma/vli.h", directory: "/data/download/cmake/cmake-master/Utilities/cmliblzma")
!173 = !DIDerivedType(tag: DW_TAG_member, name: "options", scope: !168, file: !167, line: 63, baseType: !43, size: 64, align: 64, offset: 64)
!174 = !DIDerivedType(tag: DW_TAG_member, name: "mf", scope: !85, file: !1, line: 29, baseType: !99, size: 960, align: 64, offset: 256)
!175 = !DIDerivedType(tag: DW_TAG_member, name: "next", scope: !85, file: !1, line: 32, baseType: !78, size: 512, align: 64, offset: 1216)
!176 = !DIDerivedType(tag: DW_TAG_member, name: "id", scope: !80, file: !79, line: 125, baseType: !171, size: 64, align: 64, offset: 64)
!177 = !DIDerivedType(tag: DW_TAG_member, name: "init", scope: !80, file: !79, line: 131, baseType: !178, size: 64, align: 64, offset: 128)
!178 = !DIDerivedType(tag: DW_TAG_typedef, name: "uintptr_t", file: !41, line: 122, baseType: !42)
!179 = !DIDerivedType(tag: DW_TAG_member, name: "code", scope: !80, file: !79, line: 134, baseType: !180, size: 64, align: 64, offset: 192)
!180 = !DIDerivedType(tag: DW_TAG_typedef, name: "lzma_code_function", file: !79, line: 89, baseType: !181)
!181 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !182, size: 64, align: 64)
!182 = !DISubroutineType(types: !183)
!183 = !{!76, !83, !147, !184, !141, !44, !140, !141, !44, !137}
!184 = !DIDerivedType(tag: DW_TAG_restrict_type, baseType: !67)
!185 = !DIDerivedType(tag: DW_TAG_member, name: "end", scope: !80, file: !79, line: 139, baseType: !186, size: 64, align: 64, offset: 256)
!186 = !DIDerivedType(tag: DW_TAG_typedef, name: "lzma_end_function", file: !79, line: 97, baseType: !144)
!187 = !DIDerivedType(tag: DW_TAG_member, name: "get_check", scope: !80, file: !79, line: 143, baseType: !188, size: 64, align: 64, offset: 320)
!188 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !189, size: 64, align: 64)
!189 = !DISubroutineType(types: !190)
!190 = !{!191, !192}
!191 = !DIDerivedType(tag: DW_TAG_typedef, name: "lzma_check", file: !33, line: 55, baseType: !32)
!192 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !193, size: 64, align: 64)
!193 = !DIDerivedType(tag: DW_TAG_const_type, baseType: !84)
!194 = !DIDerivedType(tag: DW_TAG_member, name: "memconfig", scope: !80, file: !79, line: 147, baseType: !195, size: 64, align: 64, offset: 384)
!195 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !196, size: 64, align: 64)
!196 = !DISubroutineType(types: !197)
!197 = !{!76, !83, !198, !198, !40}
!198 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !40, size: 64, align: 64)
!199 = !DIDerivedType(tag: DW_TAG_member, name: "update", scope: !80, file: !79, line: 152, baseType: !200, size: 64, align: 64, offset: 448)
!200 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !201, size: 64, align: 64)
!201 = !DISubroutineType(types: !202)
!202 = !{!76, !83, !147, !164, !164}
!203 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !204, size: 64, align: 64)
!204 = !DIDerivedType(tag: DW_TAG_const_type, baseType: !205)
!205 = !DIDerivedType(tag: DW_TAG_typedef, name: "lzma_filter_info", file: !79, line: 77, baseType: !206)
!206 = !DICompositeType(tag: DW_TAG_structure_type, name: "lzma_filter_info_s", file: !79, line: 104, size: 192, align: 64, elements: !207)
!207 = !{!208, !209, !214}
!208 = !DIDerivedType(tag: DW_TAG_member, name: "id", scope: !206, file: !79, line: 107, baseType: !171, size: 64, align: 64)
!209 = !DIDerivedType(tag: DW_TAG_member, name: "init", scope: !206, file: !79, line: 111, baseType: !210, size: 64, align: 64, offset: 64)
!210 = !DIDerivedType(tag: DW_TAG_typedef, name: "lzma_init_function", file: !79, line: 81, baseType: !211)
!211 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !212, size: 64, align: 64)
!212 = !DISubroutineType(types: !213)
!213 = !{!76, !77, !147, !203}
!214 = !DIDerivedType(tag: DW_TAG_member, name: "options", scope: !206, file: !79, line: 114, baseType: !43, size: 64, align: 64, offset: 128)
!215 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !216, size: 64, align: 64)
!216 = !DISubroutineType(types: !217)
!217 = !{!76, !218, !147, !219, !221}
!218 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !88, size: 64, align: 64)
!219 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !220, size: 64, align: 64)
!220 = !DIDerivedType(tag: DW_TAG_const_type, baseType: null)
!221 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !52, size: 64, align: 64)
!222 = distinct !DISubprogram(name: "lzma_mf_is_supported", scope: !1, file: !1, line: 564, type: !223, isLocal: false, isDefinition: true, scopeLine: 565, flags: DIFlagPrototyped, isOptimized: false, variables: !72)
!223 = !DISubroutineType(types: !224)
!224 = !{!225, !62}
!225 = !DIDerivedType(tag: DW_TAG_typedef, name: "lzma_bool", file: !12, line: 29, baseType: !70)
!226 = distinct !DISubprogram(name: "lz_encoder_prepare", scope: !1, file: !1, line: 188, type: !227, isLocal: true, isDefinition: true, scopeLine: 190, flags: DIFlagPrototyped, isOptimized: false, variables: !72)
!227 = !DISubroutineType(types: !228)
!228 = !{!229, !98, !147, !50}
!229 = !DIBasicType(name: "_Bool", size: 8, align: 8, encoding: DW_ATE_boolean)
!230 = distinct !DISubprogram(name: "lz_encode", scope: !1, file: !1, line: 155, type: !182, isLocal: true, isDefinition: true, scopeLine: 160, flags: DIFlagPrototyped, isOptimized: false, variables: !72)
!231 = distinct !DISubprogram(name: "fill_window", scope: !1, file: !1, line: 81, type: !232, isLocal: true, isDefinition: true, scopeLine: 83, flags: DIFlagPrototyped, isOptimized: false, variables: !72)
!232 = !DISubroutineType(types: !233)
!233 = !{!76, !83, !147, !67, !142, !44, !137}
!234 = distinct !DISubprogram(name: "move_window", scope: !1, file: !1, line: 44, type: !235, isLocal: true, isDefinition: true, scopeLine: 45, flags: DIFlagPrototyped, isOptimized: false, variables: !72)
!235 = !DISubroutineType(types: !236)
!236 = !{null, !98}
!237 = distinct !DISubprogram(name: "lz_encoder_end", scope: !1, file: !1, line: 474, type: !145, isLocal: true, isDefinition: true, scopeLine: 475, flags: DIFlagPrototyped, isOptimized: false, variables: !72)
!238 = distinct !DISubprogram(name: "lz_encoder_update", scope: !1, file: !1, line: 492, type: !201, isLocal: true, isDefinition: true, scopeLine: 495, flags: DIFlagPrototyped, isOptimized: false, variables: !72)
!239 = distinct !DISubprogram(name: "lz_encoder_init", scope: !1, file: !1, line: 376, type: !227, isLocal: true, isDefinition: true, scopeLine: 378, flags: DIFlagPrototyped, isOptimized: false, variables: !72)
!240 = !{!241}
!241 = !DIGlobalVariable(name: "LZMA_NEXT_CODER_INIT", scope: !0, file: !79, line: 159, type: !242, isLocal: true, isDefinition: true, variable: %struct.lzma_next_coder_s* @LZMA_NEXT_CODER_INIT)
!242 = !DIDerivedType(tag: DW_TAG_const_type, baseType: !78)
!243 = !{i32 2, !"Dwarf Version", i32 4}
!244 = !{i32 2, !"Debug Info Version", i32 3}
!245 = !{!"clang version 3.8.0 (tags/RELEASE_380/final)"}
!246 = !DILocalVariable(name: "lz_options", arg: 1, scope: !47, file: !1, line: 457, type: !50)
!247 = !DIExpression()
!248 = !DILocation(line: 457, column: 49, scope: !47)
!249 = !DILocalVariable(name: "mf", scope: !47, file: !1, line: 460, type: !99)
!250 = !DILocation(line: 460, column: 10, scope: !47)
!251 = !DILocation(line: 463, column: 36, scope: !252)
!252 = distinct !DILexicalBlock(scope: !47, file: !1, line: 463, column: 6)
!253 = !DILocation(line: 463, column: 6, scope: !252)
!254 = !DILocation(line: 463, column: 6, scope: !47)
!255 = !DILocation(line: 464, column: 3, scope: !252)
!256 = !DILocation(line: 467, column: 23, scope: !47)
!257 = !DILocation(line: 467, column: 42, scope: !47)
!258 = !DILocation(line: 467, column: 37, scope: !47)
!259 = !DILocation(line: 467, column: 9, scope: !47)
!260 = !DILocation(line: 468, column: 5, scope: !47)
!261 = !DILocation(line: 469, column: 20, scope: !47)
!262 = !DILocation(line: 469, column: 6, scope: !47)
!263 = !DILocation(line: 469, column: 4, scope: !47)
!264 = !DILocation(line: 469, column: 26, scope: !47)
!265 = !DILocation(line: 467, column: 2, scope: !47)
!266 = !DILocation(line: 470, column: 1, scope: !47)
!267 = !DILocalVariable(name: "mf", arg: 1, scope: !226, file: !1, line: 188, type: !98)
!268 = !DILocation(line: 188, column: 29, scope: !226)
!269 = !DILocalVariable(name: "allocator", arg: 2, scope: !226, file: !1, line: 188, type: !147)
!270 = !DILocation(line: 188, column: 49, scope: !226)
!271 = !DILocalVariable(name: "lz_options", arg: 3, scope: !226, file: !1, line: 189, type: !50)
!272 = !DILocation(line: 189, column: 26, scope: !226)
!273 = !DILocalVariable(name: "is_bt", scope: !226, file: !1, line: 191, type: !229)
!274 = !DILocation(line: 191, column: 7, scope: !226)
!275 = !DILocalVariable(name: "new_count", scope: !226, file: !1, line: 192, type: !64)
!276 = !DILocation(line: 192, column: 11, scope: !226)
!277 = !DILocalVariable(name: "reserve", scope: !226, file: !1, line: 193, type: !64)
!278 = !DILocation(line: 193, column: 11, scope: !226)
!279 = !DILocalVariable(name: "old_size", scope: !226, file: !1, line: 194, type: !64)
!280 = !DILocation(line: 194, column: 11, scope: !226)
!281 = !DILocalVariable(name: "hash_bytes", scope: !226, file: !1, line: 195, type: !64)
!282 = !DILocation(line: 195, column: 11, scope: !226)
!283 = !DILocalVariable(name: "hs", scope: !226, file: !1, line: 196, type: !64)
!284 = !DILocation(line: 196, column: 11, scope: !226)
!285 = !DILocalVariable(name: "old_count", scope: !226, file: !1, line: 197, type: !64)
!286 = !DILocation(line: 197, column: 11, scope: !226)
!287 = !DILocation(line: 202, column: 6, scope: !288)
!288 = distinct !DILexicalBlock(scope: !226, file: !1, line: 202, column: 6)
!289 = !DILocation(line: 202, column: 18, scope: !288)
!290 = !DILocation(line: 202, column: 28, scope: !288)
!291 = !DILocation(line: 203, column: 4, scope: !288)
!292 = !DILocation(line: 203, column: 7, scope: !293)
!293 = !DILexicalBlockFile(scope: !288, file: !1, discriminator: 1)
!294 = !DILocation(line: 203, column: 19, scope: !293)
!295 = !DILocation(line: 204, column: 5, scope: !288)
!296 = !DILocation(line: 205, column: 4, scope: !288)
!297 = !DILocation(line: 205, column: 7, scope: !293)
!298 = !DILocation(line: 205, column: 19, scope: !293)
!299 = !DILocation(line: 205, column: 30, scope: !293)
!300 = !DILocation(line: 205, column: 42, scope: !293)
!301 = !DILocation(line: 205, column: 28, scope: !293)
!302 = !DILocation(line: 202, column: 6, scope: !303)
!303 = !DILexicalBlockFile(scope: !226, file: !1, discriminator: 1)
!304 = !DILocation(line: 206, column: 3, scope: !288)
!305 = !DILocation(line: 208, column: 25, scope: !226)
!306 = !DILocation(line: 208, column: 37, scope: !226)
!307 = !DILocation(line: 208, column: 51, scope: !226)
!308 = !DILocation(line: 208, column: 63, scope: !226)
!309 = !DILocation(line: 208, column: 49, scope: !226)
!310 = !DILocation(line: 208, column: 2, scope: !226)
!311 = !DILocation(line: 208, column: 6, scope: !226)
!312 = !DILocation(line: 208, column: 23, scope: !226)
!313 = !DILocation(line: 210, column: 24, scope: !226)
!314 = !DILocation(line: 210, column: 36, scope: !226)
!315 = !DILocation(line: 211, column: 6, scope: !226)
!316 = !DILocation(line: 211, column: 18, scope: !226)
!317 = !DILocation(line: 211, column: 4, scope: !226)
!318 = !DILocation(line: 210, column: 2, scope: !226)
!319 = !DILocation(line: 210, column: 6, scope: !226)
!320 = !DILocation(line: 210, column: 22, scope: !226)
!321 = !DILocation(line: 224, column: 12, scope: !226)
!322 = !DILocation(line: 224, column: 24, scope: !226)
!323 = !DILocation(line: 224, column: 34, scope: !226)
!324 = !DILocation(line: 224, column: 10, scope: !226)
!325 = !DILocation(line: 225, column: 6, scope: !326)
!326 = distinct !DILexicalBlock(scope: !226, file: !1, line: 225, column: 6)
!327 = !DILocation(line: 225, column: 14, scope: !326)
!328 = !DILocation(line: 225, column: 6, scope: !226)
!329 = !DILocation(line: 226, column: 11, scope: !326)
!330 = !DILocation(line: 226, column: 3, scope: !326)
!331 = !DILocation(line: 228, column: 14, scope: !226)
!332 = !DILocation(line: 228, column: 26, scope: !226)
!333 = !DILocation(line: 228, column: 40, scope: !226)
!334 = !DILocation(line: 228, column: 52, scope: !226)
!335 = !DILocation(line: 228, column: 38, scope: !226)
!336 = !DILocation(line: 229, column: 6, scope: !226)
!337 = !DILocation(line: 229, column: 18, scope: !226)
!338 = !DILocation(line: 229, column: 4, scope: !226)
!339 = !DILocation(line: 229, column: 30, scope: !226)
!340 = !DILocation(line: 229, column: 34, scope: !226)
!341 = !DILocation(line: 228, column: 10, scope: !226)
!342 = !DILocation(line: 231, column: 13, scope: !226)
!343 = !DILocation(line: 231, column: 17, scope: !226)
!344 = !DILocation(line: 231, column: 11, scope: !226)
!345 = !DILocation(line: 232, column: 13, scope: !226)
!346 = !DILocation(line: 232, column: 17, scope: !226)
!347 = !DILocation(line: 232, column: 36, scope: !226)
!348 = !DILocation(line: 232, column: 34, scope: !226)
!349 = !DILocation(line: 232, column: 46, scope: !226)
!350 = !DILocation(line: 232, column: 50, scope: !226)
!351 = !DILocation(line: 232, column: 44, scope: !226)
!352 = !DILocation(line: 232, column: 2, scope: !226)
!353 = !DILocation(line: 232, column: 6, scope: !226)
!354 = !DILocation(line: 232, column: 11, scope: !226)
!355 = !DILocation(line: 236, column: 6, scope: !356)
!356 = distinct !DILexicalBlock(scope: !226, file: !1, line: 236, column: 6)
!357 = !DILocation(line: 236, column: 10, scope: !356)
!358 = !DILocation(line: 236, column: 17, scope: !356)
!359 = !DILocation(line: 236, column: 25, scope: !356)
!360 = !DILocation(line: 236, column: 28, scope: !361)
!361 = !DILexicalBlockFile(scope: !356, file: !1, discriminator: 1)
!362 = !DILocation(line: 236, column: 40, scope: !361)
!363 = !DILocation(line: 236, column: 44, scope: !361)
!364 = !DILocation(line: 236, column: 37, scope: !361)
!365 = !DILocation(line: 236, column: 6, scope: !361)
!366 = !DILocation(line: 237, column: 13, scope: !367)
!367 = distinct !DILexicalBlock(scope: !356, file: !1, line: 236, column: 50)
!368 = !DILocation(line: 237, column: 17, scope: !367)
!369 = !DILocation(line: 237, column: 25, scope: !367)
!370 = !DILocation(line: 237, column: 3, scope: !367)
!371 = !DILocation(line: 238, column: 3, scope: !367)
!372 = !DILocation(line: 238, column: 7, scope: !367)
!373 = !DILocation(line: 238, column: 14, scope: !367)
!374 = !DILocation(line: 239, column: 2, scope: !367)
!375 = !DILocation(line: 242, column: 22, scope: !226)
!376 = !DILocation(line: 242, column: 34, scope: !226)
!377 = !DILocation(line: 242, column: 2, scope: !226)
!378 = !DILocation(line: 242, column: 6, scope: !226)
!379 = !DILocation(line: 242, column: 20, scope: !226)
!380 = !DILocation(line: 243, column: 17, scope: !226)
!381 = !DILocation(line: 243, column: 29, scope: !226)
!382 = !DILocation(line: 243, column: 2, scope: !226)
!383 = !DILocation(line: 243, column: 6, scope: !226)
!384 = !DILocation(line: 243, column: 15, scope: !226)
!385 = !DILocation(line: 260, column: 20, scope: !226)
!386 = !DILocation(line: 260, column: 32, scope: !226)
!387 = !DILocation(line: 260, column: 42, scope: !226)
!388 = !DILocation(line: 260, column: 2, scope: !226)
!389 = !DILocation(line: 260, column: 6, scope: !226)
!390 = !DILocation(line: 260, column: 18, scope: !226)
!391 = !DILocation(line: 263, column: 10, scope: !226)
!392 = !DILocation(line: 263, column: 22, scope: !226)
!393 = !DILocation(line: 263, column: 2, scope: !226)
!394 = !DILocation(line: 266, column: 3, scope: !395)
!395 = distinct !DILexicalBlock(scope: !226, file: !1, line: 263, column: 36)
!396 = !DILocation(line: 266, column: 7, scope: !395)
!397 = !DILocation(line: 266, column: 12, scope: !395)
!398 = !DILocation(line: 267, column: 3, scope: !395)
!399 = !DILocation(line: 267, column: 7, scope: !395)
!400 = !DILocation(line: 267, column: 12, scope: !395)
!401 = !DILocation(line: 268, column: 3, scope: !395)
!402 = !DILocation(line: 272, column: 3, scope: !395)
!403 = !DILocation(line: 272, column: 7, scope: !395)
!404 = !DILocation(line: 272, column: 12, scope: !395)
!405 = !DILocation(line: 273, column: 3, scope: !395)
!406 = !DILocation(line: 273, column: 7, scope: !395)
!407 = !DILocation(line: 273, column: 12, scope: !395)
!408 = !DILocation(line: 274, column: 3, scope: !395)
!409 = !DILocation(line: 278, column: 3, scope: !395)
!410 = !DILocation(line: 278, column: 7, scope: !395)
!411 = !DILocation(line: 278, column: 12, scope: !395)
!412 = !DILocation(line: 279, column: 3, scope: !395)
!413 = !DILocation(line: 279, column: 7, scope: !395)
!414 = !DILocation(line: 279, column: 12, scope: !395)
!415 = !DILocation(line: 280, column: 3, scope: !395)
!416 = !DILocation(line: 284, column: 3, scope: !395)
!417 = !DILocation(line: 284, column: 7, scope: !395)
!418 = !DILocation(line: 284, column: 12, scope: !395)
!419 = !DILocation(line: 285, column: 3, scope: !395)
!420 = !DILocation(line: 285, column: 7, scope: !395)
!421 = !DILocation(line: 285, column: 12, scope: !395)
!422 = !DILocation(line: 286, column: 3, scope: !395)
!423 = !DILocation(line: 290, column: 3, scope: !395)
!424 = !DILocation(line: 290, column: 7, scope: !395)
!425 = !DILocation(line: 290, column: 12, scope: !395)
!426 = !DILocation(line: 291, column: 3, scope: !395)
!427 = !DILocation(line: 291, column: 7, scope: !395)
!428 = !DILocation(line: 291, column: 12, scope: !395)
!429 = !DILocation(line: 292, column: 3, scope: !395)
!430 = !DILocation(line: 296, column: 3, scope: !395)
!431 = !DILocation(line: 301, column: 15, scope: !226)
!432 = !DILocation(line: 301, column: 27, scope: !226)
!433 = !DILocation(line: 301, column: 40, scope: !226)
!434 = !DILocation(line: 301, column: 13, scope: !226)
!435 = !DILocation(line: 302, column: 6, scope: !436)
!436 = distinct !DILexicalBlock(scope: !226, file: !1, line: 302, column: 6)
!437 = !DILocation(line: 302, column: 19, scope: !436)
!438 = !DILocation(line: 302, column: 23, scope: !436)
!439 = !DILocation(line: 302, column: 17, scope: !436)
!440 = !DILocation(line: 302, column: 6, scope: !226)
!441 = !DILocation(line: 303, column: 3, scope: !436)
!442 = !DILocation(line: 305, column: 11, scope: !226)
!443 = !DILocation(line: 305, column: 23, scope: !226)
!444 = !DILocation(line: 305, column: 36, scope: !226)
!445 = !DILocation(line: 305, column: 44, scope: !226)
!446 = !DILocation(line: 305, column: 8, scope: !226)
!447 = !DILocation(line: 307, column: 6, scope: !448)
!448 = distinct !DILexicalBlock(scope: !226, file: !1, line: 307, column: 6)
!449 = !DILocation(line: 307, column: 17, scope: !448)
!450 = !DILocation(line: 307, column: 6, scope: !226)
!451 = !DILocation(line: 308, column: 6, scope: !452)
!452 = distinct !DILexicalBlock(scope: !448, file: !1, line: 307, column: 23)
!453 = !DILocation(line: 309, column: 2, scope: !452)
!454 = !DILocation(line: 312, column: 8, scope: !455)
!455 = distinct !DILexicalBlock(scope: !448, file: !1, line: 309, column: 9)
!456 = !DILocation(line: 312, column: 20, scope: !455)
!457 = !DILocation(line: 312, column: 30, scope: !455)
!458 = !DILocation(line: 312, column: 6, scope: !455)
!459 = !DILocation(line: 313, column: 9, scope: !455)
!460 = !DILocation(line: 313, column: 12, scope: !455)
!461 = !DILocation(line: 313, column: 6, scope: !455)
!462 = !DILocation(line: 314, column: 9, scope: !455)
!463 = !DILocation(line: 314, column: 12, scope: !455)
!464 = !DILocation(line: 314, column: 6, scope: !455)
!465 = !DILocation(line: 315, column: 9, scope: !455)
!466 = !DILocation(line: 315, column: 12, scope: !455)
!467 = !DILocation(line: 315, column: 6, scope: !455)
!468 = !DILocation(line: 316, column: 9, scope: !455)
!469 = !DILocation(line: 316, column: 12, scope: !455)
!470 = !DILocation(line: 316, column: 6, scope: !455)
!471 = !DILocation(line: 317, column: 6, scope: !455)
!472 = !DILocation(line: 318, column: 6, scope: !455)
!473 = !DILocation(line: 320, column: 7, scope: !474)
!474 = distinct !DILexicalBlock(scope: !455, file: !1, line: 320, column: 7)
!475 = !DILocation(line: 320, column: 10, scope: !474)
!476 = !DILocation(line: 320, column: 7, scope: !455)
!477 = !DILocation(line: 321, column: 8, scope: !478)
!478 = distinct !DILexicalBlock(scope: !479, file: !1, line: 321, column: 8)
!479 = distinct !DILexicalBlock(scope: !474, file: !1, line: 320, column: 33)
!480 = !DILocation(line: 321, column: 19, scope: !478)
!481 = !DILocation(line: 321, column: 8, scope: !479)
!482 = !DILocation(line: 322, column: 8, scope: !478)
!483 = !DILocation(line: 322, column: 5, scope: !478)
!484 = !DILocation(line: 324, column: 8, scope: !478)
!485 = !DILocation(line: 325, column: 3, scope: !479)
!486 = !DILocation(line: 328, column: 18, scope: !226)
!487 = !DILocation(line: 328, column: 2, scope: !226)
!488 = !DILocation(line: 328, column: 6, scope: !226)
!489 = !DILocation(line: 328, column: 16, scope: !226)
!490 = !DILocation(line: 330, column: 2, scope: !226)
!491 = !DILocation(line: 331, column: 6, scope: !492)
!492 = distinct !DILexicalBlock(scope: !226, file: !1, line: 331, column: 6)
!493 = !DILocation(line: 331, column: 17, scope: !492)
!494 = !DILocation(line: 331, column: 6, scope: !226)
!495 = !DILocation(line: 332, column: 6, scope: !492)
!496 = !DILocation(line: 332, column: 3, scope: !492)
!497 = !DILocation(line: 333, column: 6, scope: !498)
!498 = distinct !DILexicalBlock(scope: !226, file: !1, line: 333, column: 6)
!499 = !DILocation(line: 333, column: 17, scope: !498)
!500 = !DILocation(line: 333, column: 6, scope: !226)
!501 = !DILocation(line: 334, column: 6, scope: !498)
!502 = !DILocation(line: 334, column: 3, scope: !498)
!503 = !DILocation(line: 345, column: 2, scope: !226)
!504 = !DILocation(line: 345, column: 2, scope: !303)
!505 = !DILocation(line: 345, column: 2, scope: !506)
!506 = !DILexicalBlockFile(scope: !226, file: !1, discriminator: 2)
!507 = !DILocation(line: 345, column: 2, scope: !508)
!508 = !DILexicalBlockFile(scope: !226, file: !1, discriminator: 3)
!509 = !DILocation(line: 347, column: 14, scope: !226)
!510 = !DILocation(line: 347, column: 18, scope: !226)
!511 = !DILocation(line: 347, column: 34, scope: !226)
!512 = !DILocation(line: 347, column: 38, scope: !226)
!513 = !DILocation(line: 347, column: 32, scope: !226)
!514 = !DILocation(line: 347, column: 12, scope: !226)
!515 = !DILocation(line: 348, column: 22, scope: !226)
!516 = !DILocation(line: 348, column: 2, scope: !226)
!517 = !DILocation(line: 348, column: 6, scope: !226)
!518 = !DILocation(line: 348, column: 20, scope: !226)
!519 = !DILocation(line: 349, column: 19, scope: !226)
!520 = !DILocation(line: 349, column: 23, scope: !226)
!521 = !DILocation(line: 349, column: 2, scope: !226)
!522 = !DILocation(line: 349, column: 6, scope: !226)
!523 = !DILocation(line: 349, column: 17, scope: !226)
!524 = !DILocation(line: 350, column: 6, scope: !525)
!525 = distinct !DILexicalBlock(scope: !226, file: !1, line: 350, column: 6)
!526 = !DILocation(line: 350, column: 6, scope: !226)
!527 = !DILocation(line: 351, column: 3, scope: !525)
!528 = !DILocation(line: 351, column: 7, scope: !525)
!529 = !DILocation(line: 351, column: 18, scope: !525)
!530 = !DILocation(line: 353, column: 14, scope: !226)
!531 = !DILocation(line: 353, column: 18, scope: !226)
!532 = !DILocation(line: 353, column: 34, scope: !226)
!533 = !DILocation(line: 353, column: 38, scope: !226)
!534 = !DILocation(line: 353, column: 32, scope: !226)
!535 = !DILocation(line: 353, column: 12, scope: !226)
!536 = !DILocation(line: 357, column: 6, scope: !537)
!537 = distinct !DILexicalBlock(scope: !226, file: !1, line: 357, column: 6)
!538 = !DILocation(line: 357, column: 19, scope: !537)
!539 = !DILocation(line: 357, column: 16, scope: !537)
!540 = !DILocation(line: 357, column: 6, scope: !226)
!541 = !DILocation(line: 358, column: 13, scope: !542)
!542 = distinct !DILexicalBlock(scope: !537, file: !1, line: 357, column: 30)
!543 = !DILocation(line: 358, column: 17, scope: !542)
!544 = !DILocation(line: 358, column: 23, scope: !542)
!545 = !DILocation(line: 358, column: 3, scope: !542)
!546 = !DILocation(line: 359, column: 3, scope: !542)
!547 = !DILocation(line: 359, column: 7, scope: !542)
!548 = !DILocation(line: 359, column: 12, scope: !542)
!549 = !DILocation(line: 360, column: 2, scope: !542)
!550 = !DILocation(line: 363, column: 14, scope: !226)
!551 = !DILocation(line: 363, column: 26, scope: !226)
!552 = !DILocation(line: 363, column: 2, scope: !226)
!553 = !DILocation(line: 363, column: 6, scope: !226)
!554 = !DILocation(line: 363, column: 12, scope: !226)
!555 = !DILocation(line: 364, column: 6, scope: !556)
!556 = distinct !DILexicalBlock(scope: !226, file: !1, line: 364, column: 6)
!557 = !DILocation(line: 364, column: 10, scope: !556)
!558 = !DILocation(line: 364, column: 16, scope: !556)
!559 = !DILocation(line: 364, column: 6, scope: !226)
!560 = !DILocation(line: 365, column: 7, scope: !561)
!561 = distinct !DILexicalBlock(scope: !562, file: !1, line: 365, column: 7)
!562 = distinct !DILexicalBlock(scope: !556, file: !1, line: 364, column: 22)
!563 = !DILocation(line: 365, column: 7, scope: !562)
!564 = !DILocation(line: 366, column: 21, scope: !561)
!565 = !DILocation(line: 366, column: 25, scope: !561)
!566 = !DILocation(line: 366, column: 34, scope: !561)
!567 = !DILocation(line: 366, column: 19, scope: !561)
!568 = !DILocation(line: 366, column: 4, scope: !561)
!569 = !DILocation(line: 366, column: 8, scope: !561)
!570 = !DILocation(line: 366, column: 14, scope: !561)
!571 = !DILocation(line: 368, column: 20, scope: !561)
!572 = !DILocation(line: 368, column: 24, scope: !561)
!573 = !DILocation(line: 368, column: 33, scope: !561)
!574 = !DILocation(line: 368, column: 18, scope: !561)
!575 = !DILocation(line: 368, column: 4, scope: !561)
!576 = !DILocation(line: 368, column: 8, scope: !561)
!577 = !DILocation(line: 368, column: 14, scope: !561)
!578 = !DILocation(line: 369, column: 2, scope: !562)
!579 = !DILocation(line: 371, column: 2, scope: !226)
!580 = !DILocation(line: 372, column: 1, scope: !226)
!581 = !DILocalVariable(name: "next", arg: 1, scope: !73, file: !1, line: 508, type: !77)
!582 = !DILocation(line: 508, column: 39, scope: !73)
!583 = !DILocalVariable(name: "allocator", arg: 2, scope: !73, file: !1, line: 508, type: !147)
!584 = !DILocation(line: 508, column: 61, scope: !73)
!585 = !DILocalVariable(name: "filters", arg: 3, scope: !73, file: !1, line: 509, type: !203)
!586 = !DILocation(line: 509, column: 27, scope: !73)
!587 = !DILocalVariable(name: "lz_init", arg: 4, scope: !73, file: !1, line: 510, type: !215)
!588 = !DILocation(line: 510, column: 14, scope: !73)
!589 = !DILocalVariable(name: "lz_options", scope: !73, file: !1, line: 514, type: !52)
!590 = !DILocation(line: 514, column: 18, scope: !73)
!591 = !DILocation(line: 522, column: 6, scope: !592)
!592 = distinct !DILexicalBlock(scope: !73, file: !1, line: 522, column: 6)
!593 = !DILocation(line: 522, column: 12, scope: !592)
!594 = !DILocation(line: 522, column: 18, scope: !592)
!595 = !DILocation(line: 522, column: 6, scope: !73)
!596 = !DILocation(line: 523, column: 48, scope: !597)
!597 = distinct !DILexicalBlock(scope: !592, file: !1, line: 522, column: 27)
!598 = !DILocation(line: 523, column: 17, scope: !597)
!599 = !DILocation(line: 523, column: 3, scope: !597)
!600 = !DILocation(line: 523, column: 9, scope: !597)
!601 = !DILocation(line: 523, column: 15, scope: !597)
!602 = !DILocation(line: 524, column: 7, scope: !603)
!603 = distinct !DILexicalBlock(scope: !597, file: !1, line: 524, column: 7)
!604 = !DILocation(line: 524, column: 13, scope: !603)
!605 = !DILocation(line: 524, column: 19, scope: !603)
!606 = !DILocation(line: 524, column: 7, scope: !597)
!607 = !DILocation(line: 525, column: 4, scope: !603)
!608 = !DILocation(line: 527, column: 3, scope: !597)
!609 = !DILocation(line: 527, column: 9, scope: !597)
!610 = !DILocation(line: 527, column: 14, scope: !597)
!611 = !DILocation(line: 528, column: 3, scope: !597)
!612 = !DILocation(line: 528, column: 9, scope: !597)
!613 = !DILocation(line: 528, column: 13, scope: !597)
!614 = !DILocation(line: 529, column: 3, scope: !597)
!615 = !DILocation(line: 529, column: 9, scope: !597)
!616 = !DILocation(line: 529, column: 16, scope: !597)
!617 = !DILocation(line: 531, column: 3, scope: !597)
!618 = !DILocation(line: 531, column: 9, scope: !597)
!619 = !DILocation(line: 531, column: 16, scope: !597)
!620 = !DILocation(line: 531, column: 19, scope: !597)
!621 = !DILocation(line: 531, column: 25, scope: !597)
!622 = !DILocation(line: 532, column: 3, scope: !597)
!623 = !DILocation(line: 532, column: 9, scope: !597)
!624 = !DILocation(line: 532, column: 16, scope: !597)
!625 = !DILocation(line: 532, column: 19, scope: !597)
!626 = !DILocation(line: 532, column: 24, scope: !597)
!627 = !DILocation(line: 533, column: 3, scope: !597)
!628 = !DILocation(line: 533, column: 9, scope: !597)
!629 = !DILocation(line: 533, column: 16, scope: !597)
!630 = !DILocation(line: 533, column: 19, scope: !597)
!631 = !DILocation(line: 533, column: 23, scope: !597)
!632 = !DILocation(line: 535, column: 3, scope: !597)
!633 = !DILocation(line: 535, column: 9, scope: !597)
!634 = !DILocation(line: 535, column: 16, scope: !597)
!635 = !DILocation(line: 535, column: 19, scope: !597)
!636 = !DILocation(line: 535, column: 26, scope: !597)
!637 = !DILocation(line: 536, column: 3, scope: !597)
!638 = !DILocation(line: 536, column: 9, scope: !597)
!639 = !DILocation(line: 536, column: 16, scope: !597)
!640 = !DILocation(line: 536, column: 19, scope: !597)
!641 = !DILocation(line: 536, column: 24, scope: !597)
!642 = !DILocation(line: 537, column: 3, scope: !597)
!643 = !DILocation(line: 537, column: 9, scope: !597)
!644 = !DILocation(line: 537, column: 16, scope: !597)
!645 = !DILocation(line: 537, column: 19, scope: !597)
!646 = !DILocation(line: 537, column: 33, scope: !597)
!647 = !DILocation(line: 538, column: 3, scope: !597)
!648 = !DILocation(line: 538, column: 9, scope: !597)
!649 = !DILocation(line: 538, column: 16, scope: !597)
!650 = !DILocation(line: 538, column: 19, scope: !597)
!651 = !DILocation(line: 538, column: 30, scope: !597)
!652 = !DILocation(line: 540, column: 3, scope: !597)
!653 = !DILocation(line: 540, column: 9, scope: !597)
!654 = !DILocation(line: 540, column: 16, scope: !597)
!655 = !DILocation(line: 540, column: 23, scope: !597)
!656 = !DILocation(line: 541, column: 2, scope: !597)
!657 = !DILocation(line: 544, column: 2, scope: !73)
!658 = !DILocalVariable(name: "ret_", scope: !659, file: !1, line: 544, type: !660)
!659 = distinct !DILexicalBlock(scope: !73, file: !1, line: 544, column: 2)
!660 = !DIDerivedType(tag: DW_TAG_const_type, baseType: !76)
!661 = !DILocation(line: 544, column: 2, scope: !659)
!662 = !DILocation(line: 544, column: 2, scope: !663)
!663 = !DILexicalBlockFile(scope: !659, file: !1, discriminator: 1)
!664 = !DILocation(line: 544, column: 2, scope: !665)
!665 = !DILexicalBlockFile(scope: !666, file: !1, discriminator: 2)
!666 = distinct !DILexicalBlock(scope: !659, file: !1, line: 544, column: 2)
!667 = !DILocation(line: 544, column: 2, scope: !668)
!668 = !DILexicalBlockFile(scope: !659, file: !1, discriminator: 3)
!669 = !DILocation(line: 549, column: 26, scope: !670)
!670 = distinct !DILexicalBlock(scope: !73, file: !1, line: 549, column: 6)
!671 = !DILocation(line: 549, column: 32, scope: !670)
!672 = !DILocation(line: 549, column: 39, scope: !670)
!673 = !DILocation(line: 549, column: 43, scope: !670)
!674 = !DILocation(line: 549, column: 6, scope: !670)
!675 = !DILocation(line: 549, column: 6, scope: !73)
!676 = !DILocation(line: 550, column: 3, scope: !670)
!677 = !DILocation(line: 554, column: 23, scope: !678)
!678 = distinct !DILexicalBlock(scope: !73, file: !1, line: 554, column: 6)
!679 = !DILocation(line: 554, column: 29, scope: !678)
!680 = !DILocation(line: 554, column: 36, scope: !678)
!681 = !DILocation(line: 554, column: 40, scope: !678)
!682 = !DILocation(line: 554, column: 6, scope: !678)
!683 = !DILocation(line: 554, column: 6, scope: !73)
!684 = !DILocation(line: 555, column: 3, scope: !678)
!685 = !DILocation(line: 558, column: 32, scope: !73)
!686 = !DILocation(line: 558, column: 38, scope: !73)
!687 = !DILocation(line: 558, column: 45, scope: !73)
!688 = !DILocation(line: 558, column: 51, scope: !73)
!689 = !DILocation(line: 559, column: 4, scope: !73)
!690 = !DILocation(line: 559, column: 12, scope: !73)
!691 = !DILocation(line: 558, column: 9, scope: !73)
!692 = !DILocation(line: 558, column: 2, scope: !73)
!693 = !DILocation(line: 560, column: 1, scope: !73)
!694 = !DILocalVariable(name: "coder", arg: 1, scope: !230, file: !1, line: 155, type: !83)
!695 = !DILocation(line: 155, column: 23, scope: !230)
!696 = !DILocalVariable(name: "allocator", arg: 2, scope: !230, file: !1, line: 155, type: !147)
!697 = !DILocation(line: 155, column: 46, scope: !230)
!698 = !DILocalVariable(name: "in", arg: 3, scope: !230, file: !1, line: 156, type: !184)
!699 = !DILocation(line: 156, column: 32, scope: !230)
!700 = !DILocalVariable(name: "in_pos", arg: 4, scope: !230, file: !1, line: 156, type: !141)
!701 = !DILocation(line: 156, column: 58, scope: !230)
!702 = !DILocalVariable(name: "in_size", arg: 5, scope: !230, file: !1, line: 157, type: !44)
!703 = !DILocation(line: 157, column: 10, scope: !230)
!704 = !DILocalVariable(name: "out", arg: 6, scope: !230, file: !1, line: 158, type: !140)
!705 = !DILocation(line: 158, column: 26, scope: !230)
!706 = !DILocalVariable(name: "out_pos", arg: 7, scope: !230, file: !1, line: 158, type: !141)
!707 = !DILocation(line: 158, column: 53, scope: !230)
!708 = !DILocalVariable(name: "out_size", arg: 8, scope: !230, file: !1, line: 159, type: !44)
!709 = !DILocation(line: 159, column: 10, scope: !230)
!710 = !DILocalVariable(name: "action", arg: 9, scope: !230, file: !1, line: 159, type: !137)
!711 = !DILocation(line: 159, column: 32, scope: !230)
!712 = !DILocation(line: 161, column: 2, scope: !230)
!713 = !DILocation(line: 161, column: 10, scope: !714)
!714 = !DILexicalBlockFile(scope: !230, file: !1, discriminator: 1)
!715 = !DILocation(line: 161, column: 9, scope: !714)
!716 = !DILocation(line: 161, column: 20, scope: !714)
!717 = !DILocation(line: 161, column: 18, scope: !714)
!718 = !DILocation(line: 162, column: 4, scope: !230)
!719 = !DILocation(line: 162, column: 9, scope: !714)
!720 = !DILocation(line: 162, column: 8, scope: !714)
!721 = !DILocation(line: 162, column: 18, scope: !714)
!722 = !DILocation(line: 162, column: 16, scope: !714)
!723 = !DILocation(line: 162, column: 26, scope: !714)
!724 = !DILocation(line: 162, column: 29, scope: !725)
!725 = !DILexicalBlockFile(scope: !230, file: !1, discriminator: 2)
!726 = !DILocation(line: 162, column: 36, scope: !725)
!727 = !DILocation(line: 162, column: 26, scope: !725)
!728 = !DILocation(line: 161, column: 2, scope: !725)
!729 = !DILocalVariable(name: "ret", scope: !730, file: !1, line: 163, type: !76)
!730 = distinct !DILexicalBlock(scope: !230, file: !1, line: 162, column: 50)
!731 = !DILocation(line: 163, column: 12, scope: !730)
!732 = !DILocation(line: 166, column: 7, scope: !733)
!733 = distinct !DILexicalBlock(scope: !730, file: !1, line: 166, column: 7)
!734 = !DILocation(line: 166, column: 14, scope: !733)
!735 = !DILocation(line: 166, column: 17, scope: !733)
!736 = !DILocation(line: 166, column: 24, scope: !733)
!737 = !DILocation(line: 166, column: 36, scope: !733)
!738 = !DILocation(line: 166, column: 39, scope: !739)
!739 = !DILexicalBlockFile(scope: !733, file: !1, discriminator: 1)
!740 = !DILocation(line: 166, column: 46, scope: !739)
!741 = !DILocation(line: 166, column: 49, scope: !739)
!742 = !DILocation(line: 167, column: 8, scope: !733)
!743 = !DILocation(line: 167, column: 15, scope: !733)
!744 = !DILocation(line: 167, column: 18, scope: !733)
!745 = !DILocation(line: 167, column: 5, scope: !733)
!746 = !DILocation(line: 166, column: 7, scope: !739)
!747 = !DILocation(line: 168, column: 4, scope: !733)
!748 = !DILocalVariable(name: "ret_", scope: !749, file: !1, line: 168, type: !660)
!749 = distinct !DILexicalBlock(scope: !733, file: !1, line: 168, column: 4)
!750 = !DILocation(line: 168, column: 4, scope: !749)
!751 = !DILocation(line: 168, column: 4, scope: !752)
!752 = !DILexicalBlockFile(scope: !749, file: !1, discriminator: 1)
!753 = !DILocation(line: 168, column: 4, scope: !754)
!754 = !DILexicalBlockFile(scope: !755, file: !1, discriminator: 2)
!755 = distinct !DILexicalBlock(scope: !749, file: !1, line: 168, column: 4)
!756 = !DILocation(line: 168, column: 4, scope: !757)
!757 = !DILexicalBlockFile(scope: !749, file: !1, discriminator: 3)
!758 = !DILocation(line: 168, column: 4, scope: !759)
!759 = !DILexicalBlockFile(scope: !749, file: !1, discriminator: 4)
!760 = !DILocation(line: 172, column: 9, scope: !730)
!761 = !DILocation(line: 172, column: 16, scope: !730)
!762 = !DILocation(line: 172, column: 19, scope: !730)
!763 = !DILocation(line: 172, column: 24, scope: !730)
!764 = !DILocation(line: 172, column: 31, scope: !730)
!765 = !DILocation(line: 172, column: 34, scope: !730)
!766 = !DILocation(line: 173, column: 6, scope: !730)
!767 = !DILocation(line: 173, column: 13, scope: !730)
!768 = !DILocation(line: 173, column: 17, scope: !730)
!769 = !DILocation(line: 173, column: 22, scope: !730)
!770 = !DILocation(line: 173, column: 31, scope: !730)
!771 = !DILocation(line: 172, column: 7, scope: !730)
!772 = !DILocation(line: 174, column: 7, scope: !773)
!773 = distinct !DILexicalBlock(scope: !730, file: !1, line: 174, column: 7)
!774 = !DILocation(line: 174, column: 11, scope: !773)
!775 = !DILocation(line: 174, column: 7, scope: !730)
!776 = !DILocation(line: 178, column: 4, scope: !777)
!777 = distinct !DILexicalBlock(scope: !773, file: !1, line: 174, column: 23)
!778 = !DILocation(line: 178, column: 11, scope: !777)
!779 = !DILocation(line: 178, column: 14, scope: !777)
!780 = !DILocation(line: 178, column: 21, scope: !777)
!781 = !DILocation(line: 179, column: 11, scope: !777)
!782 = !DILocation(line: 179, column: 4, scope: !777)
!783 = !DILocation(line: 161, column: 2, scope: !784)
!784 = !DILexicalBlockFile(scope: !230, file: !1, discriminator: 3)
!785 = !DILocation(line: 183, column: 2, scope: !230)
!786 = !DILocation(line: 184, column: 1, scope: !230)
!787 = !DILocalVariable(name: "coder", arg: 1, scope: !237, file: !1, line: 474, type: !83)
!788 = !DILocation(line: 474, column: 28, scope: !237)
!789 = !DILocalVariable(name: "allocator", arg: 2, scope: !237, file: !1, line: 474, type: !147)
!790 = !DILocation(line: 474, column: 51, scope: !237)
!791 = !DILocation(line: 476, column: 17, scope: !237)
!792 = !DILocation(line: 476, column: 24, scope: !237)
!793 = !DILocation(line: 476, column: 30, scope: !237)
!794 = !DILocation(line: 476, column: 2, scope: !237)
!795 = !DILocation(line: 478, column: 12, scope: !237)
!796 = !DILocation(line: 478, column: 19, scope: !237)
!797 = !DILocation(line: 478, column: 22, scope: !237)
!798 = !DILocation(line: 478, column: 28, scope: !237)
!799 = !DILocation(line: 478, column: 2, scope: !237)
!800 = !DILocation(line: 479, column: 12, scope: !237)
!801 = !DILocation(line: 479, column: 19, scope: !237)
!802 = !DILocation(line: 479, column: 22, scope: !237)
!803 = !DILocation(line: 479, column: 30, scope: !237)
!804 = !DILocation(line: 479, column: 2, scope: !237)
!805 = !DILocation(line: 481, column: 6, scope: !806)
!806 = distinct !DILexicalBlock(scope: !237, file: !1, line: 481, column: 6)
!807 = !DILocation(line: 481, column: 13, scope: !806)
!808 = !DILocation(line: 481, column: 16, scope: !806)
!809 = !DILocation(line: 481, column: 20, scope: !806)
!810 = !DILocation(line: 481, column: 6, scope: !237)
!811 = !DILocation(line: 482, column: 3, scope: !806)
!812 = !DILocation(line: 482, column: 10, scope: !806)
!813 = !DILocation(line: 482, column: 13, scope: !806)
!814 = !DILocation(line: 482, column: 17, scope: !806)
!815 = !DILocation(line: 482, column: 24, scope: !806)
!816 = !DILocation(line: 482, column: 27, scope: !806)
!817 = !DILocation(line: 482, column: 34, scope: !806)
!818 = !DILocation(line: 484, column: 13, scope: !806)
!819 = !DILocation(line: 484, column: 20, scope: !806)
!820 = !DILocation(line: 484, column: 23, scope: !806)
!821 = !DILocation(line: 484, column: 30, scope: !806)
!822 = !DILocation(line: 484, column: 3, scope: !806)
!823 = !DILocation(line: 486, column: 12, scope: !237)
!824 = !DILocation(line: 486, column: 19, scope: !237)
!825 = !DILocation(line: 486, column: 2, scope: !237)
!826 = !DILocation(line: 487, column: 2, scope: !237)
!827 = !DILocalVariable(name: "coder", arg: 1, scope: !238, file: !1, line: 492, type: !83)
!828 = !DILocation(line: 492, column: 31, scope: !238)
!829 = !DILocalVariable(name: "allocator", arg: 2, scope: !238, file: !1, line: 492, type: !147)
!830 = !DILocation(line: 492, column: 54, scope: !238)
!831 = !DILocalVariable(name: "filters_null", arg: 3, scope: !238, file: !1, line: 493, type: !164)
!832 = !DILocation(line: 493, column: 22, scope: !238)
!833 = !DILocalVariable(name: "reversed_filters", arg: 4, scope: !238, file: !1, line: 494, type: !164)
!834 = !DILocation(line: 494, column: 22, scope: !238)
!835 = !DILocation(line: 496, column: 6, scope: !836)
!836 = distinct !DILexicalBlock(scope: !238, file: !1, line: 496, column: 6)
!837 = !DILocation(line: 496, column: 13, scope: !836)
!838 = !DILocation(line: 496, column: 16, scope: !836)
!839 = !DILocation(line: 496, column: 31, scope: !836)
!840 = !DILocation(line: 496, column: 6, scope: !238)
!841 = !DILocation(line: 497, column: 3, scope: !836)
!842 = !DILocation(line: 499, column: 2, scope: !238)
!843 = !DILocalVariable(name: "ret_", scope: !844, file: !1, line: 499, type: !660)
!844 = distinct !DILexicalBlock(scope: !238, file: !1, line: 499, column: 2)
!845 = !DILocation(line: 499, column: 2, scope: !844)
!846 = !DILocation(line: 499, column: 2, scope: !847)
!847 = !DILexicalBlockFile(scope: !844, file: !1, discriminator: 1)
!848 = !DILocation(line: 499, column: 2, scope: !849)
!849 = !DILexicalBlockFile(scope: !850, file: !1, discriminator: 2)
!850 = distinct !DILexicalBlock(scope: !844, file: !1, line: 499, column: 2)
!851 = !DILocation(line: 499, column: 2, scope: !852)
!852 = !DILexicalBlockFile(scope: !844, file: !1, discriminator: 3)
!853 = !DILocation(line: 503, column: 5, scope: !238)
!854 = !DILocation(line: 503, column: 12, scope: !238)
!855 = !DILocation(line: 503, column: 18, scope: !238)
!856 = !DILocation(line: 503, column: 29, scope: !238)
!857 = !DILocation(line: 503, column: 46, scope: !238)
!858 = !DILocation(line: 502, column: 9, scope: !238)
!859 = !DILocation(line: 502, column: 2, scope: !238)
!860 = !DILocation(line: 504, column: 1, scope: !238)
!861 = !DILocalVariable(name: "mf", arg: 1, scope: !239, file: !1, line: 376, type: !98)
!862 = !DILocation(line: 376, column: 26, scope: !239)
!863 = !DILocalVariable(name: "allocator", arg: 2, scope: !239, file: !1, line: 376, type: !147)
!864 = !DILocation(line: 376, column: 46, scope: !239)
!865 = !DILocalVariable(name: "lz_options", arg: 3, scope: !239, file: !1, line: 377, type: !50)
!866 = !DILocation(line: 377, column: 26, scope: !239)
!867 = !DILocalVariable(name: "alloc_count", scope: !239, file: !1, line: 379, type: !44)
!868 = !DILocation(line: 379, column: 9, scope: !239)
!869 = !DILocation(line: 382, column: 6, scope: !870)
!870 = distinct !DILexicalBlock(scope: !239, file: !1, line: 382, column: 6)
!871 = !DILocation(line: 382, column: 10, scope: !870)
!872 = !DILocation(line: 382, column: 17, scope: !870)
!873 = !DILocation(line: 382, column: 6, scope: !239)
!874 = !DILocation(line: 383, column: 27, scope: !875)
!875 = distinct !DILexicalBlock(scope: !870, file: !1, line: 382, column: 26)
!876 = !DILocation(line: 383, column: 31, scope: !875)
!877 = !DILocation(line: 383, column: 37, scope: !875)
!878 = !DILocation(line: 383, column: 16, scope: !875)
!879 = !DILocation(line: 383, column: 3, scope: !875)
!880 = !DILocation(line: 383, column: 7, scope: !875)
!881 = !DILocation(line: 383, column: 14, scope: !875)
!882 = !DILocation(line: 384, column: 7, scope: !883)
!883 = distinct !DILexicalBlock(scope: !875, file: !1, line: 384, column: 7)
!884 = !DILocation(line: 384, column: 11, scope: !883)
!885 = !DILocation(line: 384, column: 18, scope: !883)
!886 = !DILocation(line: 384, column: 7, scope: !875)
!887 = !DILocation(line: 385, column: 4, scope: !883)
!888 = !DILocation(line: 386, column: 2, scope: !875)
!889 = !DILocation(line: 392, column: 15, scope: !239)
!890 = !DILocation(line: 392, column: 19, scope: !239)
!891 = !DILocation(line: 392, column: 2, scope: !239)
!892 = !DILocation(line: 392, column: 6, scope: !239)
!893 = !DILocation(line: 392, column: 13, scope: !239)
!894 = !DILocation(line: 393, column: 2, scope: !239)
!895 = !DILocation(line: 393, column: 6, scope: !239)
!896 = !DILocation(line: 393, column: 15, scope: !239)
!897 = !DILocation(line: 394, column: 2, scope: !239)
!898 = !DILocation(line: 394, column: 6, scope: !239)
!899 = !DILocation(line: 394, column: 17, scope: !239)
!900 = !DILocation(line: 395, column: 2, scope: !239)
!901 = !DILocation(line: 395, column: 6, scope: !239)
!902 = !DILocation(line: 395, column: 17, scope: !239)
!903 = !DILocation(line: 396, column: 2, scope: !239)
!904 = !DILocation(line: 396, column: 6, scope: !239)
!905 = !DILocation(line: 396, column: 16, scope: !239)
!906 = !DILocation(line: 397, column: 2, scope: !239)
!907 = !DILocation(line: 397, column: 6, scope: !239)
!908 = !DILocation(line: 397, column: 14, scope: !239)
!909 = !DILocation(line: 400, column: 16, scope: !239)
!910 = !DILocation(line: 400, column: 20, scope: !239)
!911 = !DILocation(line: 400, column: 36, scope: !239)
!912 = !DILocation(line: 400, column: 40, scope: !239)
!913 = !DILocation(line: 400, column: 34, scope: !239)
!914 = !DILocation(line: 400, column: 14, scope: !239)
!915 = !DILocation(line: 409, column: 6, scope: !916)
!916 = distinct !DILexicalBlock(scope: !239, file: !1, line: 409, column: 6)
!917 = !DILocation(line: 409, column: 10, scope: !916)
!918 = !DILocation(line: 409, column: 15, scope: !916)
!919 = !DILocation(line: 409, column: 6, scope: !239)
!920 = !DILocation(line: 410, column: 25, scope: !921)
!921 = distinct !DILexicalBlock(scope: !916, file: !1, line: 409, column: 24)
!922 = !DILocation(line: 410, column: 37, scope: !921)
!923 = !DILocation(line: 411, column: 5, scope: !921)
!924 = !DILocation(line: 410, column: 14, scope: !921)
!925 = !DILocation(line: 410, column: 3, scope: !921)
!926 = !DILocation(line: 410, column: 7, scope: !921)
!927 = !DILocation(line: 410, column: 12, scope: !921)
!928 = !DILocation(line: 412, column: 7, scope: !929)
!929 = distinct !DILexicalBlock(scope: !921, file: !1, line: 412, column: 7)
!930 = !DILocation(line: 412, column: 11, scope: !929)
!931 = !DILocation(line: 412, column: 16, scope: !929)
!932 = !DILocation(line: 412, column: 7, scope: !921)
!933 = !DILocation(line: 413, column: 4, scope: !929)
!934 = !DILocation(line: 414, column: 2, scope: !921)
!935 = !DILocation(line: 416, column: 12, scope: !239)
!936 = !DILocation(line: 416, column: 16, scope: !239)
!937 = !DILocation(line: 416, column: 23, scope: !239)
!938 = !DILocation(line: 416, column: 27, scope: !239)
!939 = !DILocation(line: 416, column: 21, scope: !239)
!940 = !DILocation(line: 416, column: 2, scope: !239)
!941 = !DILocation(line: 416, column: 6, scope: !239)
!942 = !DILocation(line: 416, column: 10, scope: !239)
!943 = !DILocation(line: 417, column: 2, scope: !239)
!944 = !DILocation(line: 417, column: 6, scope: !239)
!945 = !DILocation(line: 417, column: 17, scope: !239)
!946 = !DILocation(line: 425, column: 2, scope: !239)
!947 = !DILocation(line: 438, column: 6, scope: !948)
!948 = distinct !DILexicalBlock(scope: !239, file: !1, line: 438, column: 6)
!949 = !DILocation(line: 438, column: 18, scope: !948)
!950 = !DILocation(line: 438, column: 30, scope: !948)
!951 = !DILocation(line: 439, column: 4, scope: !948)
!952 = !DILocation(line: 439, column: 7, scope: !953)
!953 = !DILexicalBlockFile(scope: !948, file: !1, discriminator: 1)
!954 = !DILocation(line: 439, column: 19, scope: !953)
!955 = !DILocation(line: 439, column: 36, scope: !953)
!956 = !DILocation(line: 438, column: 6, scope: !957)
!957 = !DILexicalBlockFile(scope: !239, file: !1, discriminator: 1)
!958 = !DILocation(line: 442, column: 19, scope: !959)
!959 = distinct !DILexicalBlock(scope: !948, file: !1, line: 439, column: 41)
!960 = !DILocation(line: 442, column: 19, scope: !961)
!961 = !DILexicalBlockFile(scope: !959, file: !1, discriminator: 1)
!962 = !DILocation(line: 442, column: 19, scope: !963)
!963 = !DILexicalBlockFile(scope: !959, file: !1, discriminator: 2)
!964 = !DILocation(line: 442, column: 19, scope: !965)
!965 = !DILexicalBlockFile(scope: !959, file: !1, discriminator: 3)
!966 = !DILocation(line: 442, column: 3, scope: !965)
!967 = !DILocation(line: 442, column: 7, scope: !965)
!968 = !DILocation(line: 442, column: 17, scope: !965)
!969 = !DILocation(line: 443, column: 10, scope: !959)
!970 = !DILocation(line: 443, column: 14, scope: !959)
!971 = !DILocation(line: 443, column: 22, scope: !959)
!972 = !DILocation(line: 443, column: 34, scope: !959)
!973 = !DILocation(line: 444, column: 7, scope: !959)
!974 = !DILocation(line: 444, column: 19, scope: !959)
!975 = !DILocation(line: 444, column: 5, scope: !959)
!976 = !DILocation(line: 444, column: 38, scope: !959)
!977 = !DILocation(line: 444, column: 42, scope: !959)
!978 = !DILocation(line: 444, column: 36, scope: !959)
!979 = !DILocation(line: 445, column: 5, scope: !959)
!980 = !DILocation(line: 445, column: 9, scope: !959)
!981 = !DILocation(line: 443, column: 3, scope: !959)
!982 = !DILocation(line: 446, column: 3, scope: !959)
!983 = !DILocation(line: 446, column: 7, scope: !959)
!984 = !DILocation(line: 446, column: 14, scope: !959)
!985 = !DILocation(line: 447, column: 3, scope: !959)
!986 = !DILocation(line: 447, column: 7, scope: !959)
!987 = !DILocation(line: 447, column: 12, scope: !959)
!988 = !DILocation(line: 447, column: 16, scope: !959)
!989 = !DILocation(line: 447, column: 20, scope: !959)
!990 = !DILocation(line: 448, column: 2, scope: !959)
!991 = !DILocation(line: 450, column: 2, scope: !239)
!992 = !DILocation(line: 450, column: 6, scope: !239)
!993 = !DILocation(line: 450, column: 13, scope: !239)
!994 = !DILocation(line: 452, column: 2, scope: !239)
!995 = !DILocation(line: 453, column: 1, scope: !239)
!996 = !DILocalVariable(name: "mf", arg: 1, scope: !222, file: !1, line: 564, type: !62)
!997 = !DILocation(line: 564, column: 40, scope: !222)
!998 = !DILocalVariable(name: "ret", scope: !222, file: !1, line: 566, type: !229)
!999 = !DILocation(line: 566, column: 7, scope: !222)
!1000 = !DILocation(line: 569, column: 6, scope: !1001)
!1001 = distinct !DILexicalBlock(scope: !222, file: !1, line: 569, column: 6)
!1002 = !DILocation(line: 569, column: 9, scope: !1001)
!1003 = !DILocation(line: 569, column: 6, scope: !222)
!1004 = !DILocation(line: 570, column: 7, scope: !1001)
!1005 = !DILocation(line: 570, column: 3, scope: !1001)
!1006 = !DILocation(line: 574, column: 6, scope: !1007)
!1007 = distinct !DILexicalBlock(scope: !222, file: !1, line: 574, column: 6)
!1008 = !DILocation(line: 574, column: 9, scope: !1007)
!1009 = !DILocation(line: 574, column: 6, scope: !222)
!1010 = !DILocation(line: 575, column: 7, scope: !1007)
!1011 = !DILocation(line: 575, column: 3, scope: !1007)
!1012 = !DILocation(line: 579, column: 6, scope: !1013)
!1013 = distinct !DILexicalBlock(scope: !222, file: !1, line: 579, column: 6)
!1014 = !DILocation(line: 579, column: 9, scope: !1013)
!1015 = !DILocation(line: 579, column: 6, scope: !222)
!1016 = !DILocation(line: 580, column: 7, scope: !1013)
!1017 = !DILocation(line: 580, column: 3, scope: !1013)
!1018 = !DILocation(line: 584, column: 6, scope: !1019)
!1019 = distinct !DILexicalBlock(scope: !222, file: !1, line: 584, column: 6)
!1020 = !DILocation(line: 584, column: 9, scope: !1019)
!1021 = !DILocation(line: 584, column: 6, scope: !222)
!1022 = !DILocation(line: 585, column: 7, scope: !1019)
!1023 = !DILocation(line: 585, column: 3, scope: !1019)
!1024 = !DILocation(line: 589, column: 6, scope: !1025)
!1025 = distinct !DILexicalBlock(scope: !222, file: !1, line: 589, column: 6)
!1026 = !DILocation(line: 589, column: 9, scope: !1025)
!1027 = !DILocation(line: 589, column: 6, scope: !222)
!1028 = !DILocation(line: 590, column: 7, scope: !1025)
!1029 = !DILocation(line: 590, column: 3, scope: !1025)
!1030 = !DILocation(line: 593, column: 9, scope: !222)
!1031 = !DILocation(line: 593, column: 2, scope: !222)
!1032 = !DILocalVariable(name: "coder", arg: 1, scope: !231, file: !1, line: 81, type: !83)
!1033 = !DILocation(line: 81, column: 25, scope: !231)
!1034 = !DILocalVariable(name: "allocator", arg: 2, scope: !231, file: !1, line: 81, type: !147)
!1035 = !DILocation(line: 81, column: 48, scope: !231)
!1036 = !DILocalVariable(name: "in", arg: 3, scope: !231, file: !1, line: 81, type: !67)
!1037 = !DILocation(line: 81, column: 74, scope: !231)
!1038 = !DILocalVariable(name: "in_pos", arg: 4, scope: !231, file: !1, line: 82, type: !142)
!1039 = !DILocation(line: 82, column: 11, scope: !231)
!1040 = !DILocalVariable(name: "in_size", arg: 5, scope: !231, file: !1, line: 82, type: !44)
!1041 = !DILocation(line: 82, column: 26, scope: !231)
!1042 = !DILocalVariable(name: "action", arg: 6, scope: !231, file: !1, line: 82, type: !137)
!1043 = !DILocation(line: 82, column: 47, scope: !231)
!1044 = !DILocalVariable(name: "write_pos", scope: !231, file: !1, line: 84, type: !44)
!1045 = !DILocation(line: 84, column: 9, scope: !231)
!1046 = !DILocalVariable(name: "ret", scope: !231, file: !1, line: 85, type: !76)
!1047 = !DILocation(line: 85, column: 11, scope: !231)
!1048 = !DILocation(line: 87, column: 2, scope: !231)
!1049 = !DILocation(line: 87, column: 2, scope: !1050)
!1050 = !DILexicalBlockFile(scope: !231, file: !1, discriminator: 1)
!1051 = !DILocation(line: 87, column: 2, scope: !1052)
!1052 = !DILexicalBlockFile(scope: !231, file: !1, discriminator: 2)
!1053 = !DILocation(line: 87, column: 2, scope: !1054)
!1054 = !DILexicalBlockFile(scope: !231, file: !1, discriminator: 3)
!1055 = !DILocation(line: 90, column: 6, scope: !1056)
!1056 = distinct !DILexicalBlock(scope: !231, file: !1, line: 90, column: 6)
!1057 = !DILocation(line: 90, column: 13, scope: !1056)
!1058 = !DILocation(line: 90, column: 16, scope: !1056)
!1059 = !DILocation(line: 90, column: 28, scope: !1056)
!1060 = !DILocation(line: 90, column: 35, scope: !1056)
!1061 = !DILocation(line: 90, column: 38, scope: !1056)
!1062 = !DILocation(line: 90, column: 45, scope: !1056)
!1063 = !DILocation(line: 90, column: 52, scope: !1056)
!1064 = !DILocation(line: 90, column: 55, scope: !1056)
!1065 = !DILocation(line: 90, column: 43, scope: !1056)
!1066 = !DILocation(line: 90, column: 25, scope: !1056)
!1067 = !DILocation(line: 90, column: 6, scope: !231)
!1068 = !DILocation(line: 91, column: 16, scope: !1056)
!1069 = !DILocation(line: 91, column: 23, scope: !1056)
!1070 = !DILocation(line: 91, column: 3, scope: !1056)
!1071 = !DILocation(line: 96, column: 14, scope: !231)
!1072 = !DILocation(line: 96, column: 21, scope: !231)
!1073 = !DILocation(line: 96, column: 24, scope: !231)
!1074 = !DILocation(line: 96, column: 12, scope: !231)
!1075 = !DILocation(line: 97, column: 6, scope: !1076)
!1076 = distinct !DILexicalBlock(scope: !231, file: !1, line: 97, column: 6)
!1077 = !DILocation(line: 97, column: 13, scope: !1076)
!1078 = !DILocation(line: 97, column: 18, scope: !1076)
!1079 = !DILocation(line: 97, column: 23, scope: !1076)
!1080 = !DILocation(line: 97, column: 6, scope: !231)
!1081 = !DILocation(line: 99, column: 15, scope: !1082)
!1082 = distinct !DILexicalBlock(scope: !1076, file: !1, line: 97, column: 32)
!1083 = !DILocation(line: 99, column: 19, scope: !1082)
!1084 = !DILocation(line: 99, column: 27, scope: !1082)
!1085 = !DILocation(line: 99, column: 36, scope: !1082)
!1086 = !DILocation(line: 99, column: 43, scope: !1082)
!1087 = !DILocation(line: 99, column: 46, scope: !1082)
!1088 = !DILocation(line: 100, column: 17, scope: !1082)
!1089 = !DILocation(line: 100, column: 24, scope: !1082)
!1090 = !DILocation(line: 100, column: 27, scope: !1082)
!1091 = !DILocation(line: 99, column: 3, scope: !1082)
!1092 = !DILocation(line: 102, column: 9, scope: !1082)
!1093 = !DILocation(line: 102, column: 16, scope: !1082)
!1094 = !DILocation(line: 102, column: 28, scope: !1082)
!1095 = !DILocation(line: 102, column: 32, scope: !1096)
!1096 = !DILexicalBlockFile(scope: !1082, file: !1, discriminator: 1)
!1097 = !DILocation(line: 102, column: 31, scope: !1096)
!1098 = !DILocation(line: 102, column: 42, scope: !1096)
!1099 = !DILocation(line: 102, column: 39, scope: !1096)
!1100 = !DILocation(line: 102, column: 9, scope: !1101)
!1101 = !DILexicalBlockFile(scope: !1082, file: !1, discriminator: 2)
!1102 = !DILocation(line: 102, column: 7, scope: !1101)
!1103 = !DILocation(line: 105, column: 2, scope: !1082)
!1104 = !DILocation(line: 106, column: 9, scope: !1105)
!1105 = distinct !DILexicalBlock(scope: !1076, file: !1, line: 105, column: 9)
!1106 = !DILocation(line: 106, column: 16, scope: !1105)
!1107 = !DILocation(line: 106, column: 21, scope: !1105)
!1108 = !DILocation(line: 106, column: 26, scope: !1105)
!1109 = !DILocation(line: 106, column: 33, scope: !1105)
!1110 = !DILocation(line: 106, column: 38, scope: !1105)
!1111 = !DILocation(line: 106, column: 45, scope: !1105)
!1112 = !DILocation(line: 107, column: 5, scope: !1105)
!1113 = !DILocation(line: 107, column: 9, scope: !1105)
!1114 = !DILocation(line: 107, column: 17, scope: !1105)
!1115 = !DILocation(line: 108, column: 5, scope: !1105)
!1116 = !DILocation(line: 108, column: 12, scope: !1105)
!1117 = !DILocation(line: 108, column: 15, scope: !1105)
!1118 = !DILocation(line: 109, column: 5, scope: !1105)
!1119 = !DILocation(line: 109, column: 12, scope: !1105)
!1120 = !DILocation(line: 109, column: 15, scope: !1105)
!1121 = !DILocation(line: 109, column: 21, scope: !1105)
!1122 = !DILocation(line: 106, column: 7, scope: !1105)
!1123 = !DILocation(line: 112, column: 24, scope: !231)
!1124 = !DILocation(line: 112, column: 2, scope: !231)
!1125 = !DILocation(line: 112, column: 9, scope: !231)
!1126 = !DILocation(line: 112, column: 12, scope: !231)
!1127 = !DILocation(line: 112, column: 22, scope: !231)
!1128 = !DILocation(line: 118, column: 6, scope: !1129)
!1129 = distinct !DILexicalBlock(scope: !231, file: !1, line: 118, column: 6)
!1130 = !DILocation(line: 118, column: 10, scope: !1129)
!1131 = !DILocation(line: 118, column: 6, scope: !231)
!1132 = !DILocation(line: 119, column: 3, scope: !1133)
!1133 = distinct !DILexicalBlock(scope: !1129, file: !1, line: 118, column: 30)
!1134 = !DILocation(line: 119, column: 3, scope: !1135)
!1135 = !DILexicalBlockFile(scope: !1133, file: !1, discriminator: 1)
!1136 = !DILocation(line: 119, column: 3, scope: !1137)
!1137 = !DILexicalBlockFile(scope: !1133, file: !1, discriminator: 2)
!1138 = !DILocation(line: 119, column: 3, scope: !1139)
!1139 = !DILexicalBlockFile(scope: !1133, file: !1, discriminator: 3)
!1140 = !DILocation(line: 120, column: 7, scope: !1133)
!1141 = !DILocation(line: 121, column: 22, scope: !1133)
!1142 = !DILocation(line: 121, column: 3, scope: !1133)
!1143 = !DILocation(line: 121, column: 10, scope: !1133)
!1144 = !DILocation(line: 121, column: 13, scope: !1133)
!1145 = !DILocation(line: 121, column: 20, scope: !1133)
!1146 = !DILocation(line: 122, column: 26, scope: !1133)
!1147 = !DILocation(line: 122, column: 33, scope: !1133)
!1148 = !DILocation(line: 122, column: 36, scope: !1133)
!1149 = !DILocation(line: 122, column: 3, scope: !1133)
!1150 = !DILocation(line: 122, column: 10, scope: !1133)
!1151 = !DILocation(line: 122, column: 13, scope: !1133)
!1152 = !DILocation(line: 122, column: 24, scope: !1133)
!1153 = !DILocation(line: 124, column: 2, scope: !1133)
!1154 = !DILocation(line: 124, column: 13, scope: !1155)
!1155 = !DILexicalBlockFile(scope: !1156, file: !1, discriminator: 1)
!1156 = distinct !DILexicalBlock(scope: !1129, file: !1, line: 124, column: 13)
!1157 = !DILocation(line: 124, column: 20, scope: !1155)
!1158 = !DILocation(line: 124, column: 23, scope: !1155)
!1159 = !DILocation(line: 124, column: 35, scope: !1155)
!1160 = !DILocation(line: 124, column: 42, scope: !1155)
!1161 = !DILocation(line: 124, column: 45, scope: !1155)
!1162 = !DILocation(line: 124, column: 33, scope: !1155)
!1163 = !DILocation(line: 128, column: 26, scope: !1164)
!1164 = distinct !DILexicalBlock(scope: !1156, file: !1, line: 124, column: 62)
!1165 = !DILocation(line: 128, column: 33, scope: !1164)
!1166 = !DILocation(line: 128, column: 36, scope: !1164)
!1167 = !DILocation(line: 129, column: 7, scope: !1164)
!1168 = !DILocation(line: 129, column: 14, scope: !1164)
!1169 = !DILocation(line: 129, column: 17, scope: !1164)
!1170 = !DILocation(line: 129, column: 5, scope: !1164)
!1171 = !DILocation(line: 128, column: 3, scope: !1164)
!1172 = !DILocation(line: 128, column: 10, scope: !1164)
!1173 = !DILocation(line: 128, column: 13, scope: !1164)
!1174 = !DILocation(line: 128, column: 24, scope: !1164)
!1175 = !DILocation(line: 130, column: 2, scope: !1164)
!1176 = !DILocation(line: 133, column: 6, scope: !1177)
!1177 = distinct !DILexicalBlock(scope: !231, file: !1, line: 133, column: 6)
!1178 = !DILocation(line: 133, column: 13, scope: !1177)
!1179 = !DILocation(line: 133, column: 16, scope: !1177)
!1180 = !DILocation(line: 133, column: 24, scope: !1177)
!1181 = !DILocation(line: 134, column: 4, scope: !1177)
!1182 = !DILocation(line: 134, column: 7, scope: !1183)
!1183 = !DILexicalBlockFile(scope: !1177, file: !1, discriminator: 1)
!1184 = !DILocation(line: 134, column: 14, scope: !1183)
!1185 = !DILocation(line: 134, column: 17, scope: !1183)
!1186 = !DILocation(line: 134, column: 28, scope: !1183)
!1187 = !DILocation(line: 134, column: 35, scope: !1183)
!1188 = !DILocation(line: 134, column: 38, scope: !1183)
!1189 = !DILocation(line: 134, column: 26, scope: !1183)
!1190 = !DILocation(line: 133, column: 6, scope: !1050)
!1191 = !DILocalVariable(name: "pending", scope: !1192, file: !1, line: 137, type: !1193)
!1192 = distinct !DILexicalBlock(scope: !1177, file: !1, line: 134, column: 50)
!1193 = !DIDerivedType(tag: DW_TAG_const_type, baseType: !44)
!1194 = !DILocation(line: 137, column: 16, scope: !1192)
!1195 = !DILocation(line: 137, column: 26, scope: !1192)
!1196 = !DILocation(line: 137, column: 33, scope: !1192)
!1197 = !DILocation(line: 137, column: 36, scope: !1192)
!1198 = !DILocation(line: 138, column: 3, scope: !1192)
!1199 = !DILocation(line: 138, column: 10, scope: !1192)
!1200 = !DILocation(line: 138, column: 13, scope: !1192)
!1201 = !DILocation(line: 138, column: 21, scope: !1192)
!1202 = !DILocation(line: 142, column: 3, scope: !1192)
!1203 = !DILocation(line: 142, column: 3, scope: !1204)
!1204 = !DILexicalBlockFile(scope: !1192, file: !1, discriminator: 1)
!1205 = !DILocation(line: 142, column: 3, scope: !1206)
!1206 = !DILexicalBlockFile(scope: !1192, file: !1, discriminator: 2)
!1207 = !DILocation(line: 142, column: 3, scope: !1208)
!1208 = !DILexicalBlockFile(scope: !1192, file: !1, discriminator: 3)
!1209 = !DILocation(line: 143, column: 25, scope: !1192)
!1210 = !DILocation(line: 143, column: 3, scope: !1192)
!1211 = !DILocation(line: 143, column: 10, scope: !1192)
!1212 = !DILocation(line: 143, column: 13, scope: !1192)
!1213 = !DILocation(line: 143, column: 22, scope: !1192)
!1214 = !DILocation(line: 147, column: 3, scope: !1192)
!1215 = !DILocation(line: 147, column: 10, scope: !1192)
!1216 = !DILocation(line: 147, column: 13, scope: !1192)
!1217 = !DILocation(line: 147, column: 19, scope: !1192)
!1218 = !DILocation(line: 147, column: 26, scope: !1192)
!1219 = !DILocation(line: 147, column: 30, scope: !1192)
!1220 = !DILocation(line: 148, column: 2, scope: !1192)
!1221 = !DILocation(line: 150, column: 9, scope: !231)
!1222 = !DILocation(line: 150, column: 2, scope: !231)
!1223 = !DILocalVariable(name: "mf", arg: 1, scope: !234, file: !1, line: 44, type: !98)
!1224 = !DILocation(line: 44, column: 22, scope: !234)
!1225 = !DILocalVariable(name: "move_offset", scope: !234, file: !1, line: 46, type: !64)
!1226 = !DILocation(line: 46, column: 11, scope: !234)
!1227 = !DILocalVariable(name: "move_size", scope: !234, file: !1, line: 47, type: !44)
!1228 = !DILocation(line: 47, column: 9, scope: !234)
!1229 = !DILocation(line: 53, column: 2, scope: !234)
!1230 = !DILocation(line: 53, column: 2, scope: !1231)
!1231 = !DILexicalBlockFile(scope: !234, file: !1, discriminator: 1)
!1232 = !DILocation(line: 53, column: 2, scope: !1233)
!1233 = !DILexicalBlockFile(scope: !234, file: !1, discriminator: 2)
!1234 = !DILocation(line: 53, column: 2, scope: !1235)
!1235 = !DILexicalBlockFile(scope: !234, file: !1, discriminator: 3)
!1236 = !DILocation(line: 54, column: 17, scope: !234)
!1237 = !DILocation(line: 54, column: 21, scope: !234)
!1238 = !DILocation(line: 54, column: 32, scope: !234)
!1239 = !DILocation(line: 54, column: 36, scope: !234)
!1240 = !DILocation(line: 54, column: 30, scope: !234)
!1241 = !DILocation(line: 54, column: 54, scope: !234)
!1242 = !DILocation(line: 54, column: 14, scope: !234)
!1243 = !DILocation(line: 56, column: 2, scope: !234)
!1244 = !DILocation(line: 56, column: 2, scope: !1231)
!1245 = !DILocation(line: 56, column: 2, scope: !1233)
!1246 = !DILocation(line: 56, column: 2, scope: !1235)
!1247 = !DILocation(line: 57, column: 14, scope: !234)
!1248 = !DILocation(line: 57, column: 18, scope: !234)
!1249 = !DILocation(line: 57, column: 30, scope: !234)
!1250 = !DILocation(line: 57, column: 28, scope: !234)
!1251 = !DILocation(line: 57, column: 12, scope: !234)
!1252 = !DILocation(line: 59, column: 2, scope: !234)
!1253 = !DILocation(line: 59, column: 2, scope: !1231)
!1254 = !DILocation(line: 59, column: 2, scope: !1233)
!1255 = !DILocation(line: 59, column: 2, scope: !1235)
!1256 = !DILocation(line: 61, column: 10, scope: !234)
!1257 = !DILocation(line: 61, column: 14, scope: !234)
!1258 = !DILocation(line: 61, column: 22, scope: !234)
!1259 = !DILocation(line: 61, column: 26, scope: !234)
!1260 = !DILocation(line: 61, column: 35, scope: !234)
!1261 = !DILocation(line: 61, column: 33, scope: !234)
!1262 = !DILocation(line: 61, column: 48, scope: !234)
!1263 = !DILocation(line: 61, column: 2, scope: !234)
!1264 = !DILocation(line: 63, column: 16, scope: !234)
!1265 = !DILocation(line: 63, column: 2, scope: !234)
!1266 = !DILocation(line: 63, column: 6, scope: !234)
!1267 = !DILocation(line: 63, column: 13, scope: !234)
!1268 = !DILocation(line: 64, column: 18, scope: !234)
!1269 = !DILocation(line: 64, column: 2, scope: !234)
!1270 = !DILocation(line: 64, column: 6, scope: !234)
!1271 = !DILocation(line: 64, column: 15, scope: !234)
!1272 = !DILocation(line: 65, column: 20, scope: !234)
!1273 = !DILocation(line: 65, column: 2, scope: !234)
!1274 = !DILocation(line: 65, column: 6, scope: !234)
!1275 = !DILocation(line: 65, column: 17, scope: !234)
!1276 = !DILocation(line: 66, column: 19, scope: !234)
!1277 = !DILocation(line: 66, column: 2, scope: !234)
!1278 = !DILocation(line: 66, column: 6, scope: !234)
!1279 = !DILocation(line: 66, column: 16, scope: !234)
!1280 = !DILocation(line: 68, column: 2, scope: !234)
