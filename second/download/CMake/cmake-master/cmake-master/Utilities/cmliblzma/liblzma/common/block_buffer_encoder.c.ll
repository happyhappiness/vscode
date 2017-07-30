; ModuleID = '/data/download/cmake/cmake-master/Utilities/cmliblzma/liblzma/common/block_buffer_encoder.c'
target datalayout = "e-m:e-i64:64-f80:128-n8:16:32:64-S128"
target triple = "x86_64-unknown-linux-gnu"

%struct.lzma_next_coder_s = type { %struct.lzma_coder_s*, i64, i64, i32 (%struct.lzma_coder_s*, %struct.lzma_allocator*, i8*, i64*, i64, i8*, i64*, i64, i32)*, void (%struct.lzma_coder_s*, %struct.lzma_allocator*)*, i32 (%struct.lzma_coder_s*)*, i32 (%struct.lzma_coder_s*, i64*, i64*, i64)*, i32 (%struct.lzma_coder_s*, %struct.lzma_allocator*, %struct.lzma_filter*, %struct.lzma_filter*)* }
%struct.lzma_coder_s = type opaque
%struct.lzma_allocator = type { i8* (i8*, i64, i64)*, void (i8*, i8*)*, i8* }
%struct.lzma_filter = type { i64, i8* }
%struct.lzma_block = type { i32, i32, i32, i64, i64, %struct.lzma_filter*, [64 x i8], i8*, i8*, i8*, i32, i32, i64, i64, i64, i64, i64, i64, i32, i32, i32, i32, i8, i8, i8, i8, i8, i8, i8, i8 }
%struct.lzma_check_state = type { %union.anon, %union.anon.0 }
%union.anon = type { [8 x i64] }
%union.anon.0 = type { %struct.anon }
%struct.anon = type { [8 x i32], i64 }
%struct.lzma_options_lzma = type { i32, i8*, i32, i32, i32, i32, i32, i32, i32, i32, i32, i32, i32, i32, i32, i32, i32, i32, i32, i32, i32, i32, i8*, i8* }

@.str = private unnamed_addr constant [28 x i8] c"check_size != (4294967295U)\00", align 1
@.str.1 = private unnamed_addr constant [92 x i8] c"/data/download/cmake/cmake-master/Utilities/cmliblzma/liblzma/common/block_buffer_encoder.c\00", align 1
@__PRETTY_FUNCTION__.lzma_block_buffer_encode = private unnamed_addr constant [120 x i8] c"lzma_ret lzma_block_buffer_encode(lzma_block *, lzma_allocator *, const uint8_t *, size_t, uint8_t *, size_t *, size_t)\00", align 1
@.str.2 = private unnamed_addr constant [21 x i8] c"*out_pos <= out_size\00", align 1
@.str.3 = private unnamed_addr constant [20 x i8] c"*out_pos < out_size\00", align 1
@LZMA_NEXT_CODER_INIT = internal constant %struct.lzma_next_coder_s { %struct.lzma_coder_s* null, i64 -1, i64 0, i32 (%struct.lzma_coder_s*, %struct.lzma_allocator*, i8*, i64*, i64, i8*, i64*, i64, i32)* null, void (%struct.lzma_coder_s*, %struct.lzma_allocator*)* null, i32 (%struct.lzma_coder_s*)* null, i32 (%struct.lzma_coder_s*, i64*, i64*, i64)* null, i32 (%struct.lzma_coder_s*, %struct.lzma_allocator*, %struct.lzma_filter*, %struct.lzma_filter*)* null }, align 8
@.str.4 = private unnamed_addr constant [47 x i8] c"block->compressed_size == lzma2_bound(in_size)\00", align 1
@__PRETTY_FUNCTION__.block_encode_uncompressed = private unnamed_addr constant [103 x i8] c"lzma_ret block_encode_uncompressed(lzma_block *, const uint8_t *, size_t, uint8_t *, size_t *, size_t)\00", align 1
@.str.5 = private unnamed_addr constant [33 x i8] c"*out_pos + copy_size <= out_size\00", align 1

; Function Attrs: nounwind uwtable
define i64 @lzma_block_buffer_bound(i64 %uncompressed_size) #0 !dbg !53 {
entry:
  %retval = alloca i64, align 8
  %uncompressed_size.addr = alloca i64, align 8
  %lzma2_size = alloca i64, align 8
  store i64 %uncompressed_size, i64* %uncompressed_size.addr, align 8
  call void @llvm.dbg.declare(metadata i64* %uncompressed_size.addr, metadata !188, metadata !189), !dbg !190
  call void @llvm.dbg.declare(metadata i64* %lzma2_size, metadata !191, metadata !189), !dbg !192
  %0 = load i64, i64* %uncompressed_size.addr, align 8, !dbg !193
  %call = call i64 @lzma2_bound(i64 %0), !dbg !194
  store i64 %call, i64* %lzma2_size, align 8, !dbg !192
  %1 = load i64, i64* %lzma2_size, align 8, !dbg !195
  %cmp = icmp eq i64 %1, 0, !dbg !197
  br i1 %cmp, label %if.then, label %if.end, !dbg !198

if.then:                                          ; preds = %entry
  store i64 0, i64* %retval, align 8, !dbg !199
  br label %return, !dbg !199

if.end:                                           ; preds = %entry
  %2 = load i64, i64* %lzma2_size, align 8, !dbg !200
  %add = add i64 %2, 3, !dbg !201
  %and = and i64 %add, -4, !dbg !202
  store i64 %and, i64* %lzma2_size, align 8, !dbg !203
  %3 = load i64, i64* %lzma2_size, align 8, !dbg !204
  %add1 = add i64 92, %3, !dbg !205
  store i64 %add1, i64* %retval, align 8, !dbg !206
  br label %return, !dbg !206

return:                                           ; preds = %if.end, %if.then
  %4 = load i64, i64* %retval, align 8, !dbg !207
  ret i64 %4, !dbg !207
}

; Function Attrs: nounwind readnone
declare void @llvm.dbg.declare(metadata, metadata, metadata) #1

; Function Attrs: nounwind uwtable
define internal i64 @lzma2_bound(i64 %uncompressed_size) #0 !dbg !133 {
entry:
  %retval = alloca i64, align 8
  %uncompressed_size.addr = alloca i64, align 8
  %overhead = alloca i64, align 8
  store i64 %uncompressed_size, i64* %uncompressed_size.addr, align 8
  call void @llvm.dbg.declare(metadata i64* %uncompressed_size.addr, metadata !208, metadata !189), !dbg !209
  call void @llvm.dbg.declare(metadata i64* %overhead, metadata !210, metadata !189), !dbg !211
  %0 = load i64, i64* %uncompressed_size.addr, align 8, !dbg !212
  %cmp = icmp ugt i64 %0, 9223372036854774716, !dbg !214
  br i1 %cmp, label %if.then, label %if.end, !dbg !215

if.then:                                          ; preds = %entry
  store i64 0, i64* %retval, align 8, !dbg !216
  br label %return, !dbg !216

if.end:                                           ; preds = %entry
  %1 = load i64, i64* %uncompressed_size.addr, align 8, !dbg !217
  %add = add i64 %1, 65536, !dbg !218
  %sub = sub i64 %add, 1, !dbg !219
  %div = udiv i64 %sub, 65536, !dbg !220
  %mul = mul i64 %div, 3, !dbg !221
  %add1 = add i64 %mul, 1, !dbg !222
  store i64 %add1, i64* %overhead, align 8, !dbg !223
  %2 = load i64, i64* %overhead, align 8, !dbg !224
  %sub2 = sub i64 9223372036854774716, %2, !dbg !226
  %3 = load i64, i64* %uncompressed_size.addr, align 8, !dbg !227
  %cmp3 = icmp ult i64 %sub2, %3, !dbg !228
  br i1 %cmp3, label %if.then4, label %if.end5, !dbg !229

if.then4:                                         ; preds = %if.end
  store i64 0, i64* %retval, align 8, !dbg !230
  br label %return, !dbg !230

if.end5:                                          ; preds = %if.end
  %4 = load i64, i64* %uncompressed_size.addr, align 8, !dbg !231
  %5 = load i64, i64* %overhead, align 8, !dbg !232
  %add6 = add i64 %4, %5, !dbg !233
  store i64 %add6, i64* %retval, align 8, !dbg !234
  br label %return, !dbg !234

return:                                           ; preds = %if.end5, %if.then4, %if.then
  %6 = load i64, i64* %retval, align 8, !dbg !235
  ret i64 %6, !dbg !235
}

; Function Attrs: nounwind uwtable
define i32 @lzma_block_buffer_encode(%struct.lzma_block* %block, %struct.lzma_allocator* %allocator, i8* %in, i64 %in_size, i8* %out, i64* %out_pos, i64 %out_size) #0 !dbg !57 {
entry:
  %retval = alloca i32, align 4
  %block.addr = alloca %struct.lzma_block*, align 8
  %allocator.addr = alloca %struct.lzma_allocator*, align 8
  %in.addr = alloca i8*, align 8
  %in_size.addr = alloca i64, align 8
  %out.addr = alloca i8*, align 8
  %out_pos.addr = alloca i64*, align 8
  %out_size.addr = alloca i64, align 8
  %check_size = alloca i64, align 8
  %ret = alloca i32, align 4
  %i = alloca i64, align 8
  %ret_ = alloca i32, align 4
  %check61 = alloca %struct.lzma_check_state, align 8
  store %struct.lzma_block* %block, %struct.lzma_block** %block.addr, align 8
  call void @llvm.dbg.declare(metadata %struct.lzma_block** %block.addr, metadata !236, metadata !189), !dbg !237
  store %struct.lzma_allocator* %allocator, %struct.lzma_allocator** %allocator.addr, align 8
  call void @llvm.dbg.declare(metadata %struct.lzma_allocator** %allocator.addr, metadata !238, metadata !189), !dbg !239
  store i8* %in, i8** %in.addr, align 8
  call void @llvm.dbg.declare(metadata i8** %in.addr, metadata !240, metadata !189), !dbg !241
  store i64 %in_size, i64* %in_size.addr, align 8
  call void @llvm.dbg.declare(metadata i64* %in_size.addr, metadata !242, metadata !189), !dbg !243
  store i8* %out, i8** %out.addr, align 8
  call void @llvm.dbg.declare(metadata i8** %out.addr, metadata !244, metadata !189), !dbg !245
  store i64* %out_pos, i64** %out_pos.addr, align 8
  call void @llvm.dbg.declare(metadata i64** %out_pos.addr, metadata !246, metadata !189), !dbg !247
  store i64 %out_size, i64* %out_size.addr, align 8
  call void @llvm.dbg.declare(metadata i64* %out_size.addr, metadata !248, metadata !189), !dbg !249
  call void @llvm.dbg.declare(metadata i64* %check_size, metadata !250, metadata !189), !dbg !251
  call void @llvm.dbg.declare(metadata i32* %ret, metadata !252, metadata !189), !dbg !253
  call void @llvm.dbg.declare(metadata i64* %i, metadata !254, metadata !189), !dbg !255
  %0 = load %struct.lzma_block*, %struct.lzma_block** %block.addr, align 8, !dbg !256
  %cmp = icmp eq %struct.lzma_block* %0, null, !dbg !258
  br i1 %cmp, label %if.then, label %lor.lhs.false, !dbg !259

lor.lhs.false:                                    ; preds = %entry
  %1 = load i8*, i8** %in.addr, align 8, !dbg !260
  %cmp1 = icmp eq i8* %1, null, !dbg !262
  br i1 %cmp1, label %land.lhs.true, label %lor.lhs.false3, !dbg !263

land.lhs.true:                                    ; preds = %lor.lhs.false
  %2 = load i64, i64* %in_size.addr, align 8, !dbg !264
  %cmp2 = icmp ne i64 %2, 0, !dbg !266
  br i1 %cmp2, label %if.then, label %lor.lhs.false3, !dbg !267

lor.lhs.false3:                                   ; preds = %land.lhs.true, %lor.lhs.false
  %3 = load i8*, i8** %out.addr, align 8, !dbg !268
  %cmp4 = icmp eq i8* %3, null, !dbg !270
  br i1 %cmp4, label %if.then, label %lor.lhs.false5, !dbg !271

lor.lhs.false5:                                   ; preds = %lor.lhs.false3
  %4 = load i64*, i64** %out_pos.addr, align 8, !dbg !272
  %cmp6 = icmp eq i64* %4, null, !dbg !273
  br i1 %cmp6, label %if.then, label %lor.lhs.false7, !dbg !274

lor.lhs.false7:                                   ; preds = %lor.lhs.false5
  %5 = load i64*, i64** %out_pos.addr, align 8, !dbg !275
  %6 = load i64, i64* %5, align 8, !dbg !276
  %7 = load i64, i64* %out_size.addr, align 8, !dbg !277
  %cmp8 = icmp ugt i64 %6, %7, !dbg !278
  br i1 %cmp8, label %if.then, label %if.end, !dbg !279

if.then:                                          ; preds = %lor.lhs.false7, %lor.lhs.false5, %lor.lhs.false3, %land.lhs.true, %entry
  store i32 11, i32* %retval, align 4, !dbg !281
  br label %return, !dbg !281

if.end:                                           ; preds = %lor.lhs.false7
  %8 = load %struct.lzma_block*, %struct.lzma_block** %block.addr, align 8, !dbg !282
  %version = getelementptr inbounds %struct.lzma_block, %struct.lzma_block* %8, i32 0, i32 0, !dbg !284
  %9 = load i32, i32* %version, align 8, !dbg !284
  %cmp9 = icmp ne i32 %9, 0, !dbg !285
  br i1 %cmp9, label %if.then10, label %if.end11, !dbg !286

if.then10:                                        ; preds = %if.end
  store i32 8, i32* %retval, align 4, !dbg !287
  br label %return, !dbg !287

if.end11:                                         ; preds = %if.end
  %10 = load %struct.lzma_block*, %struct.lzma_block** %block.addr, align 8, !dbg !288
  %check = getelementptr inbounds %struct.lzma_block, %struct.lzma_block* %10, i32 0, i32 2, !dbg !290
  %11 = load i32, i32* %check, align 8, !dbg !290
  %cmp12 = icmp ugt i32 %11, 15, !dbg !291
  br i1 %cmp12, label %if.then15, label %lor.lhs.false13, !dbg !292

lor.lhs.false13:                                  ; preds = %if.end11
  %12 = load %struct.lzma_block*, %struct.lzma_block** %block.addr, align 8, !dbg !293
  %filters = getelementptr inbounds %struct.lzma_block, %struct.lzma_block* %12, i32 0, i32 5, !dbg !295
  %13 = load %struct.lzma_filter*, %struct.lzma_filter** %filters, align 8, !dbg !295
  %cmp14 = icmp eq %struct.lzma_filter* %13, null, !dbg !296
  br i1 %cmp14, label %if.then15, label %if.end16, !dbg !297

if.then15:                                        ; preds = %lor.lhs.false13, %if.end11
  store i32 11, i32* %retval, align 4, !dbg !299
  br label %return, !dbg !299

if.end16:                                         ; preds = %lor.lhs.false13
  %14 = load %struct.lzma_block*, %struct.lzma_block** %block.addr, align 8, !dbg !300
  %check17 = getelementptr inbounds %struct.lzma_block, %struct.lzma_block* %14, i32 0, i32 2, !dbg !302
  %15 = load i32, i32* %check17, align 8, !dbg !302
  %call = call zeroext i8 @lzma_check_is_supported(i32 %15) #1, !dbg !303
  %tobool = icmp ne i8 %call, 0, !dbg !303
  br i1 %tobool, label %if.end19, label %if.then18, !dbg !304

if.then18:                                        ; preds = %if.end16
  store i32 3, i32* %retval, align 4, !dbg !305
  br label %return, !dbg !305

if.end19:                                         ; preds = %if.end16
  %16 = load i64, i64* %out_size.addr, align 8, !dbg !306
  %17 = load i64*, i64** %out_pos.addr, align 8, !dbg !307
  %18 = load i64, i64* %17, align 8, !dbg !308
  %sub = sub i64 %16, %18, !dbg !309
  %and = and i64 %sub, 3, !dbg !310
  %19 = load i64, i64* %out_size.addr, align 8, !dbg !311
  %sub20 = sub i64 %19, %and, !dbg !311
  store i64 %sub20, i64* %out_size.addr, align 8, !dbg !311
  %20 = load %struct.lzma_block*, %struct.lzma_block** %block.addr, align 8, !dbg !312
  %check21 = getelementptr inbounds %struct.lzma_block, %struct.lzma_block* %20, i32 0, i32 2, !dbg !313
  %21 = load i32, i32* %check21, align 8, !dbg !313
  %call22 = call i32 @lzma_check_size(i32 %21) #1, !dbg !314
  %conv = zext i32 %call22 to i64, !dbg !314
  store i64 %conv, i64* %check_size, align 8, !dbg !315
  %22 = load i64, i64* %check_size, align 8, !dbg !316
  %cmp23 = icmp ne i64 %22, 4294967295, !dbg !316
  br i1 %cmp23, label %cond.true, label %cond.false, !dbg !316

cond.true:                                        ; preds = %if.end19
  br label %cond.end, !dbg !317

cond.false:                                       ; preds = %if.end19
  call void @__assert_fail(i8* getelementptr inbounds ([28 x i8], [28 x i8]* @.str, i32 0, i32 0), i8* getelementptr inbounds ([92 x i8], [92 x i8]* @.str.1, i32 0, i32 0), i32 263, i8* getelementptr inbounds ([120 x i8], [120 x i8]* @__PRETTY_FUNCTION__.lzma_block_buffer_encode, i32 0, i32 0)) #7, !dbg !318
  unreachable, !dbg !318
                                                  ; No predecessors!
  br label %cond.end, !dbg !320

cond.end:                                         ; preds = %23, %cond.true
  %24 = load i64, i64* %out_size.addr, align 8, !dbg !322
  %25 = load i64*, i64** %out_pos.addr, align 8, !dbg !324
  %26 = load i64, i64* %25, align 8, !dbg !325
  %sub25 = sub i64 %24, %26, !dbg !326
  %27 = load i64, i64* %check_size, align 8, !dbg !327
  %cmp26 = icmp ule i64 %sub25, %27, !dbg !328
  br i1 %cmp26, label %if.then28, label %if.end29, !dbg !329

if.then28:                                        ; preds = %cond.end
  store i32 10, i32* %retval, align 4, !dbg !330
  br label %return, !dbg !330

if.end29:                                         ; preds = %cond.end
  %28 = load i64, i64* %check_size, align 8, !dbg !331
  %29 = load i64, i64* %out_size.addr, align 8, !dbg !332
  %sub30 = sub i64 %29, %28, !dbg !332
  store i64 %sub30, i64* %out_size.addr, align 8, !dbg !332
  %30 = load %struct.lzma_block*, %struct.lzma_block** %block.addr, align 8, !dbg !333
  %31 = load %struct.lzma_allocator*, %struct.lzma_allocator** %allocator.addr, align 8, !dbg !334
  %32 = load i8*, i8** %in.addr, align 8, !dbg !335
  %33 = load i64, i64* %in_size.addr, align 8, !dbg !336
  %34 = load i8*, i8** %out.addr, align 8, !dbg !337
  %35 = load i64*, i64** %out_pos.addr, align 8, !dbg !338
  %36 = load i64, i64* %out_size.addr, align 8, !dbg !339
  %call31 = call i32 @block_encode_normal(%struct.lzma_block* %30, %struct.lzma_allocator* %31, i8* %32, i64 %33, i8* %34, i64* %35, i64 %36), !dbg !340
  store i32 %call31, i32* %ret, align 4, !dbg !341
  %37 = load i32, i32* %ret, align 4, !dbg !342
  %cmp32 = icmp ne i32 %37, 0, !dbg !344
  br i1 %cmp32, label %if.then34, label %if.end44, !dbg !345

if.then34:                                        ; preds = %if.end29
  %38 = load i32, i32* %ret, align 4, !dbg !346
  %cmp35 = icmp ne i32 %38, 10, !dbg !349
  br i1 %cmp35, label %if.then37, label %if.end38, !dbg !350

if.then37:                                        ; preds = %if.then34
  %39 = load i32, i32* %ret, align 4, !dbg !351
  store i32 %39, i32* %retval, align 4, !dbg !352
  br label %return, !dbg !352

if.end38:                                         ; preds = %if.then34
  br label %do.body, !dbg !353

do.body:                                          ; preds = %if.end38
  call void @llvm.dbg.declare(metadata i32* %ret_, metadata !354, metadata !189), !dbg !357
  %40 = load %struct.lzma_block*, %struct.lzma_block** %block.addr, align 8, !dbg !358
  %41 = load i8*, i8** %in.addr, align 8, !dbg !358
  %42 = load i64, i64* %in_size.addr, align 8, !dbg !358
  %43 = load i8*, i8** %out.addr, align 8, !dbg !358
  %44 = load i64*, i64** %out_pos.addr, align 8, !dbg !358
  %45 = load i64, i64* %out_size.addr, align 8, !dbg !358
  %call39 = call i32 @block_encode_uncompressed(%struct.lzma_block* %40, i8* %41, i64 %42, i8* %43, i64* %44, i64 %45), !dbg !358
  store i32 %call39, i32* %ret_, align 4, !dbg !358
  %46 = load i32, i32* %ret_, align 4, !dbg !358
  %cmp40 = icmp ne i32 %46, 0, !dbg !358
  br i1 %cmp40, label %if.then42, label %if.end43, !dbg !358

if.then42:                                        ; preds = %do.body
  %47 = load i32, i32* %ret_, align 4, !dbg !360
  store i32 %47, i32* %retval, align 4, !dbg !360
  br label %return, !dbg !360

if.end43:                                         ; preds = %do.body
  br label %do.end, !dbg !363

do.end:                                           ; preds = %if.end43
  br label %if.end44, !dbg !365

if.end44:                                         ; preds = %do.end, %if.end29
  %48 = load i64*, i64** %out_pos.addr, align 8, !dbg !366
  %49 = load i64, i64* %48, align 8, !dbg !366
  %50 = load i64, i64* %out_size.addr, align 8, !dbg !366
  %cmp45 = icmp ule i64 %49, %50, !dbg !366
  br i1 %cmp45, label %cond.true47, label %cond.false48, !dbg !366

cond.true47:                                      ; preds = %if.end44
  br label %cond.end49, !dbg !367

cond.false48:                                     ; preds = %if.end44
  call void @__assert_fail(i8* getelementptr inbounds ([21 x i8], [21 x i8]* @.str.2, i32 0, i32 0), i8* getelementptr inbounds ([92 x i8], [92 x i8]* @.str.1, i32 0, i32 0), i32 289, i8* getelementptr inbounds ([120 x i8], [120 x i8]* @__PRETTY_FUNCTION__.lzma_block_buffer_encode, i32 0, i32 0)) #7, !dbg !368
  unreachable, !dbg !368
                                                  ; No predecessors!
  br label %cond.end49, !dbg !369

cond.end49:                                       ; preds = %51, %cond.true47
  %52 = load %struct.lzma_block*, %struct.lzma_block** %block.addr, align 8, !dbg !370
  %compressed_size = getelementptr inbounds %struct.lzma_block, %struct.lzma_block* %52, i32 0, i32 3, !dbg !372
  %53 = load i64, i64* %compressed_size, align 8, !dbg !372
  store i64 %53, i64* %i, align 8, !dbg !373
  br label %for.cond, !dbg !374

for.cond:                                         ; preds = %for.inc, %cond.end49
  %54 = load i64, i64* %i, align 8, !dbg !375
  %and50 = and i64 %54, 3, !dbg !378
  %tobool51 = icmp ne i64 %and50, 0, !dbg !379
  br i1 %tobool51, label %for.body, label %for.end, !dbg !379

for.body:                                         ; preds = %for.cond
  %55 = load i64*, i64** %out_pos.addr, align 8, !dbg !380
  %56 = load i64, i64* %55, align 8, !dbg !380
  %57 = load i64, i64* %out_size.addr, align 8, !dbg !380
  %cmp52 = icmp ult i64 %56, %57, !dbg !380
  br i1 %cmp52, label %cond.true54, label %cond.false55, !dbg !380

cond.true54:                                      ; preds = %for.body
  br label %cond.end56, !dbg !382

cond.false55:                                     ; preds = %for.body
  call void @__assert_fail(i8* getelementptr inbounds ([20 x i8], [20 x i8]* @.str.3, i32 0, i32 0), i8* getelementptr inbounds ([92 x i8], [92 x i8]* @.str.1, i32 0, i32 0), i32 295, i8* getelementptr inbounds ([120 x i8], [120 x i8]* @__PRETTY_FUNCTION__.lzma_block_buffer_encode, i32 0, i32 0)) #7, !dbg !384
  unreachable, !dbg !384
                                                  ; No predecessors!
  br label %cond.end56, !dbg !386

cond.end56:                                       ; preds = %58, %cond.true54
  %59 = load i64*, i64** %out_pos.addr, align 8, !dbg !388
  %60 = load i64, i64* %59, align 8, !dbg !389
  %inc = add i64 %60, 1, !dbg !389
  store i64 %inc, i64* %59, align 8, !dbg !389
  %61 = load i8*, i8** %out.addr, align 8, !dbg !390
  %arrayidx = getelementptr inbounds i8, i8* %61, i64 %60, !dbg !390
  store i8 0, i8* %arrayidx, align 1, !dbg !391
  br label %for.inc, !dbg !392

for.inc:                                          ; preds = %cond.end56
  %62 = load i64, i64* %i, align 8, !dbg !393
  %inc57 = add i64 %62, 1, !dbg !393
  store i64 %inc57, i64* %i, align 8, !dbg !393
  br label %for.cond, !dbg !395

for.end:                                          ; preds = %for.cond
  %63 = load i64, i64* %check_size, align 8, !dbg !396
  %cmp58 = icmp ugt i64 %63, 0, !dbg !398
  br i1 %cmp58, label %if.then60, label %if.end69, !dbg !399

if.then60:                                        ; preds = %for.end
  call void @llvm.dbg.declare(metadata %struct.lzma_check_state* %check61, metadata !400, metadata !189), !dbg !429
  %64 = load %struct.lzma_block*, %struct.lzma_block** %block.addr, align 8, !dbg !430
  %check62 = getelementptr inbounds %struct.lzma_block, %struct.lzma_block* %64, i32 0, i32 2, !dbg !431
  %65 = load i32, i32* %check62, align 8, !dbg !431
  call void @lzma_check_init(%struct.lzma_check_state* %check61, i32 %65), !dbg !432
  %66 = load %struct.lzma_block*, %struct.lzma_block** %block.addr, align 8, !dbg !433
  %check63 = getelementptr inbounds %struct.lzma_block, %struct.lzma_block* %66, i32 0, i32 2, !dbg !434
  %67 = load i32, i32* %check63, align 8, !dbg !434
  %68 = load i8*, i8** %in.addr, align 8, !dbg !435
  %69 = load i64, i64* %in_size.addr, align 8, !dbg !436
  call void @lzma_check_update(%struct.lzma_check_state* %check61, i32 %67, i8* %68, i64 %69), !dbg !437
  %70 = load %struct.lzma_block*, %struct.lzma_block** %block.addr, align 8, !dbg !438
  %check64 = getelementptr inbounds %struct.lzma_block, %struct.lzma_block* %70, i32 0, i32 2, !dbg !439
  %71 = load i32, i32* %check64, align 8, !dbg !439
  call void @lzma_check_finish(%struct.lzma_check_state* %check61, i32 %71), !dbg !440
  %72 = load %struct.lzma_block*, %struct.lzma_block** %block.addr, align 8, !dbg !441
  %raw_check = getelementptr inbounds %struct.lzma_block, %struct.lzma_block* %72, i32 0, i32 6, !dbg !442
  %arraydecay = getelementptr inbounds [64 x i8], [64 x i8]* %raw_check, i32 0, i32 0, !dbg !443
  %buffer = getelementptr inbounds %struct.lzma_check_state, %struct.lzma_check_state* %check61, i32 0, i32 0, !dbg !444
  %u8 = bitcast %union.anon* %buffer to [64 x i8]*, !dbg !445
  %arraydecay65 = getelementptr inbounds [64 x i8], [64 x i8]* %u8, i32 0, i32 0, !dbg !443
  %73 = load i64, i64* %check_size, align 8, !dbg !446
  call void @llvm.memcpy.p0i8.p0i8.i64(i8* %arraydecay, i8* %arraydecay65, i64 %73, i32 8, i1 false), !dbg !443
  %74 = load i8*, i8** %out.addr, align 8, !dbg !447
  %75 = load i64*, i64** %out_pos.addr, align 8, !dbg !448
  %76 = load i64, i64* %75, align 8, !dbg !449
  %add.ptr = getelementptr inbounds i8, i8* %74, i64 %76, !dbg !450
  %buffer66 = getelementptr inbounds %struct.lzma_check_state, %struct.lzma_check_state* %check61, i32 0, i32 0, !dbg !451
  %u867 = bitcast %union.anon* %buffer66 to [64 x i8]*, !dbg !452
  %arraydecay68 = getelementptr inbounds [64 x i8], [64 x i8]* %u867, i32 0, i32 0, !dbg !453
  %77 = load i64, i64* %check_size, align 8, !dbg !454
  call void @llvm.memcpy.p0i8.p0i8.i64(i8* %add.ptr, i8* %arraydecay68, i64 %77, i32 1, i1 false), !dbg !453
  %78 = load i64, i64* %check_size, align 8, !dbg !455
  %79 = load i64*, i64** %out_pos.addr, align 8, !dbg !456
  %80 = load i64, i64* %79, align 8, !dbg !457
  %add = add i64 %80, %78, !dbg !457
  store i64 %add, i64* %79, align 8, !dbg !457
  br label %if.end69, !dbg !458

if.end69:                                         ; preds = %if.then60, %for.end
  store i32 0, i32* %retval, align 4, !dbg !459
  br label %return, !dbg !459

return:                                           ; preds = %if.end69, %if.then42, %if.then37, %if.then28, %if.then18, %if.then15, %if.then10, %if.then
  %81 = load i32, i32* %retval, align 4, !dbg !460
  ret i32 %81, !dbg !460
}

; Function Attrs: nounwind readnone
declare zeroext i8 @lzma_check_is_supported(i32) #2

; Function Attrs: nounwind readnone
declare i32 @lzma_check_size(i32) #2

; Function Attrs: noreturn nounwind
declare void @__assert_fail(i8*, i8*, i32, i8*) #3

; Function Attrs: nounwind uwtable
define internal i32 @block_encode_normal(%struct.lzma_block* %block, %struct.lzma_allocator* %allocator, i8* %in, i64 %in_size, i8* %out, i64* %out_pos, i64 %out_size) #0 !dbg !136 {
entry:
  %retval = alloca i32, align 4
  %block.addr = alloca %struct.lzma_block*, align 8
  %allocator.addr = alloca %struct.lzma_allocator*, align 8
  %in.addr = alloca i8*, align 8
  %in_size.addr = alloca i64, align 8
  %out.addr = alloca i8*, align 8
  %out_pos.addr = alloca i64*, align 8
  %out_size.addr = alloca i64, align 8
  %out_start = alloca i64, align 8
  %raw_encoder = alloca %struct.lzma_next_coder_s, align 8
  %ret = alloca i32, align 4
  %ret_ = alloca i32, align 4
  %in_pos = alloca i64, align 8
  store %struct.lzma_block* %block, %struct.lzma_block** %block.addr, align 8
  call void @llvm.dbg.declare(metadata %struct.lzma_block** %block.addr, metadata !461, metadata !189), !dbg !462
  store %struct.lzma_allocator* %allocator, %struct.lzma_allocator** %allocator.addr, align 8
  call void @llvm.dbg.declare(metadata %struct.lzma_allocator** %allocator.addr, metadata !463, metadata !189), !dbg !464
  store i8* %in, i8** %in.addr, align 8
  call void @llvm.dbg.declare(metadata i8** %in.addr, metadata !465, metadata !189), !dbg !466
  store i64 %in_size, i64* %in_size.addr, align 8
  call void @llvm.dbg.declare(metadata i64* %in_size.addr, metadata !467, metadata !189), !dbg !468
  store i8* %out, i8** %out.addr, align 8
  call void @llvm.dbg.declare(metadata i8** %out.addr, metadata !469, metadata !189), !dbg !470
  store i64* %out_pos, i64** %out_pos.addr, align 8
  call void @llvm.dbg.declare(metadata i64** %out_pos.addr, metadata !471, metadata !189), !dbg !472
  store i64 %out_size, i64* %out_size.addr, align 8
  call void @llvm.dbg.declare(metadata i64* %out_size.addr, metadata !473, metadata !189), !dbg !474
  call void @llvm.dbg.declare(metadata i64* %out_start, metadata !475, metadata !189), !dbg !476
  call void @llvm.dbg.declare(metadata %struct.lzma_next_coder_s* %raw_encoder, metadata !477, metadata !189), !dbg !478
  %0 = bitcast %struct.lzma_next_coder_s* %raw_encoder to i8*, !dbg !479
  call void @llvm.memcpy.p0i8.p0i8.i64(i8* %0, i8* bitcast (%struct.lzma_next_coder_s* @LZMA_NEXT_CODER_INIT to i8*), i64 64, i32 8, i1 false), !dbg !479
  call void @llvm.dbg.declare(metadata i32* %ret, metadata !480, metadata !189), !dbg !481
  %1 = load i64, i64* %in_size.addr, align 8, !dbg !482
  %call = call i64 @lzma2_bound(i64 %1), !dbg !483
  %2 = load %struct.lzma_block*, %struct.lzma_block** %block.addr, align 8, !dbg !484
  %compressed_size = getelementptr inbounds %struct.lzma_block, %struct.lzma_block* %2, i32 0, i32 3, !dbg !485
  store i64 %call, i64* %compressed_size, align 8, !dbg !486
  %3 = load %struct.lzma_block*, %struct.lzma_block** %block.addr, align 8, !dbg !487
  %compressed_size1 = getelementptr inbounds %struct.lzma_block, %struct.lzma_block* %3, i32 0, i32 3, !dbg !489
  %4 = load i64, i64* %compressed_size1, align 8, !dbg !489
  %cmp = icmp eq i64 %4, 0, !dbg !490
  br i1 %cmp, label %if.then, label %if.end, !dbg !491

if.then:                                          ; preds = %entry
  store i32 9, i32* %retval, align 4, !dbg !492
  br label %return, !dbg !492

if.end:                                           ; preds = %entry
  %5 = load i64, i64* %in_size.addr, align 8, !dbg !493
  %6 = load %struct.lzma_block*, %struct.lzma_block** %block.addr, align 8, !dbg !494
  %uncompressed_size = getelementptr inbounds %struct.lzma_block, %struct.lzma_block* %6, i32 0, i32 4, !dbg !495
  store i64 %5, i64* %uncompressed_size, align 8, !dbg !496
  br label %do.body, !dbg !497

do.body:                                          ; preds = %if.end
  call void @llvm.dbg.declare(metadata i32* %ret_, metadata !498, metadata !189), !dbg !500
  %7 = load %struct.lzma_block*, %struct.lzma_block** %block.addr, align 8, !dbg !501
  %call2 = call i32 @lzma_block_header_size(%struct.lzma_block* %7) #8, !dbg !501
  store i32 %call2, i32* %ret_, align 4, !dbg !501
  %8 = load i32, i32* %ret_, align 4, !dbg !501
  %cmp3 = icmp ne i32 %8, 0, !dbg !501
  br i1 %cmp3, label %if.then4, label %if.end5, !dbg !501

if.then4:                                         ; preds = %do.body
  %9 = load i32, i32* %ret_, align 4, !dbg !503
  store i32 %9, i32* %retval, align 4, !dbg !503
  br label %return, !dbg !503

if.end5:                                          ; preds = %do.body
  br label %do.end, !dbg !506

do.end:                                           ; preds = %if.end5
  %10 = load i64, i64* %out_size.addr, align 8, !dbg !508
  %11 = load i64*, i64** %out_pos.addr, align 8, !dbg !510
  %12 = load i64, i64* %11, align 8, !dbg !511
  %sub = sub i64 %10, %12, !dbg !512
  %13 = load %struct.lzma_block*, %struct.lzma_block** %block.addr, align 8, !dbg !513
  %header_size = getelementptr inbounds %struct.lzma_block, %struct.lzma_block* %13, i32 0, i32 1, !dbg !514
  %14 = load i32, i32* %header_size, align 4, !dbg !514
  %conv = zext i32 %14 to i64, !dbg !513
  %cmp6 = icmp ule i64 %sub, %conv, !dbg !515
  br i1 %cmp6, label %if.then8, label %if.end9, !dbg !516

if.then8:                                         ; preds = %do.end
  store i32 10, i32* %retval, align 4, !dbg !517
  br label %return, !dbg !517

if.end9:                                          ; preds = %do.end
  %15 = load i64*, i64** %out_pos.addr, align 8, !dbg !518
  %16 = load i64, i64* %15, align 8, !dbg !519
  store i64 %16, i64* %out_start, align 8, !dbg !520
  %17 = load %struct.lzma_block*, %struct.lzma_block** %block.addr, align 8, !dbg !521
  %header_size10 = getelementptr inbounds %struct.lzma_block, %struct.lzma_block* %17, i32 0, i32 1, !dbg !522
  %18 = load i32, i32* %header_size10, align 4, !dbg !522
  %conv11 = zext i32 %18 to i64, !dbg !521
  %19 = load i64*, i64** %out_pos.addr, align 8, !dbg !523
  %20 = load i64, i64* %19, align 8, !dbg !524
  %add = add i64 %20, %conv11, !dbg !524
  store i64 %add, i64* %19, align 8, !dbg !524
  %21 = load i64, i64* %out_size.addr, align 8, !dbg !525
  %22 = load i64*, i64** %out_pos.addr, align 8, !dbg !527
  %23 = load i64, i64* %22, align 8, !dbg !528
  %sub12 = sub i64 %21, %23, !dbg !529
  %24 = load %struct.lzma_block*, %struct.lzma_block** %block.addr, align 8, !dbg !530
  %compressed_size13 = getelementptr inbounds %struct.lzma_block, %struct.lzma_block* %24, i32 0, i32 3, !dbg !531
  %25 = load i64, i64* %compressed_size13, align 8, !dbg !531
  %cmp14 = icmp ugt i64 %sub12, %25, !dbg !532
  br i1 %cmp14, label %if.then16, label %if.end19, !dbg !533

if.then16:                                        ; preds = %if.end9
  %26 = load i64*, i64** %out_pos.addr, align 8, !dbg !534
  %27 = load i64, i64* %26, align 8, !dbg !535
  %28 = load %struct.lzma_block*, %struct.lzma_block** %block.addr, align 8, !dbg !536
  %compressed_size17 = getelementptr inbounds %struct.lzma_block, %struct.lzma_block* %28, i32 0, i32 3, !dbg !537
  %29 = load i64, i64* %compressed_size17, align 8, !dbg !537
  %add18 = add i64 %27, %29, !dbg !538
  store i64 %add18, i64* %out_size.addr, align 8, !dbg !539
  br label %if.end19, !dbg !540

if.end19:                                         ; preds = %if.then16, %if.end9
  %30 = load %struct.lzma_allocator*, %struct.lzma_allocator** %allocator.addr, align 8, !dbg !541
  %31 = load %struct.lzma_block*, %struct.lzma_block** %block.addr, align 8, !dbg !542
  %filters = getelementptr inbounds %struct.lzma_block, %struct.lzma_block* %31, i32 0, i32 5, !dbg !543
  %32 = load %struct.lzma_filter*, %struct.lzma_filter** %filters, align 8, !dbg !543
  %call20 = call i32 @lzma_raw_encoder_init(%struct.lzma_next_coder_s* %raw_encoder, %struct.lzma_allocator* %30, %struct.lzma_filter* %32), !dbg !544
  store i32 %call20, i32* %ret, align 4, !dbg !545
  %33 = load i32, i32* %ret, align 4, !dbg !546
  %cmp21 = icmp eq i32 %33, 0, !dbg !548
  br i1 %cmp21, label %if.then23, label %if.end25, !dbg !549

if.then23:                                        ; preds = %if.end19
  call void @llvm.dbg.declare(metadata i64* %in_pos, metadata !550, metadata !189), !dbg !552
  store i64 0, i64* %in_pos, align 8, !dbg !552
  %code = getelementptr inbounds %struct.lzma_next_coder_s, %struct.lzma_next_coder_s* %raw_encoder, i32 0, i32 3, !dbg !553
  %34 = load i32 (%struct.lzma_coder_s*, %struct.lzma_allocator*, i8*, i64*, i64, i8*, i64*, i64, i32)*, i32 (%struct.lzma_coder_s*, %struct.lzma_allocator*, i8*, i64*, i64, i8*, i64*, i64, i32)** %code, align 8, !dbg !553
  %coder = getelementptr inbounds %struct.lzma_next_coder_s, %struct.lzma_next_coder_s* %raw_encoder, i32 0, i32 0, !dbg !554
  %35 = load %struct.lzma_coder_s*, %struct.lzma_coder_s** %coder, align 8, !dbg !554
  %36 = load %struct.lzma_allocator*, %struct.lzma_allocator** %allocator.addr, align 8, !dbg !555
  %37 = load i8*, i8** %in.addr, align 8, !dbg !556
  %38 = load i64, i64* %in_size.addr, align 8, !dbg !557
  %39 = load i8*, i8** %out.addr, align 8, !dbg !558
  %40 = load i64*, i64** %out_pos.addr, align 8, !dbg !559
  %41 = load i64, i64* %out_size.addr, align 8, !dbg !560
  %call24 = call i32 %34(%struct.lzma_coder_s* %35, %struct.lzma_allocator* %36, i8* %37, i64* %in_pos, i64 %38, i8* %39, i64* %40, i64 %41, i32 3), !dbg !561
  store i32 %call24, i32* %ret, align 4, !dbg !562
  br label %if.end25, !dbg !563

if.end25:                                         ; preds = %if.then23, %if.end19
  %42 = load %struct.lzma_allocator*, %struct.lzma_allocator** %allocator.addr, align 8, !dbg !564
  call void @lzma_next_end(%struct.lzma_next_coder_s* %raw_encoder, %struct.lzma_allocator* %42), !dbg !565
  %43 = load i32, i32* %ret, align 4, !dbg !566
  %cmp26 = icmp eq i32 %43, 1, !dbg !568
  br i1 %cmp26, label %if.then28, label %if.else, !dbg !569

if.then28:                                        ; preds = %if.end25
  %44 = load i64*, i64** %out_pos.addr, align 8, !dbg !570
  %45 = load i64, i64* %44, align 8, !dbg !572
  %46 = load i64, i64* %out_start, align 8, !dbg !573
  %47 = load %struct.lzma_block*, %struct.lzma_block** %block.addr, align 8, !dbg !574
  %header_size29 = getelementptr inbounds %struct.lzma_block, %struct.lzma_block* %47, i32 0, i32 1, !dbg !575
  %48 = load i32, i32* %header_size29, align 4, !dbg !575
  %conv30 = zext i32 %48 to i64, !dbg !574
  %add31 = add i64 %46, %conv30, !dbg !576
  %sub32 = sub i64 %45, %add31, !dbg !577
  %49 = load %struct.lzma_block*, %struct.lzma_block** %block.addr, align 8, !dbg !578
  %compressed_size33 = getelementptr inbounds %struct.lzma_block, %struct.lzma_block* %49, i32 0, i32 3, !dbg !579
  store i64 %sub32, i64* %compressed_size33, align 8, !dbg !580
  %50 = load %struct.lzma_block*, %struct.lzma_block** %block.addr, align 8, !dbg !581
  %51 = load i8*, i8** %out.addr, align 8, !dbg !582
  %52 = load i64, i64* %out_start, align 8, !dbg !583
  %add.ptr = getelementptr inbounds i8, i8* %51, i64 %52, !dbg !584
  %call34 = call i32 @lzma_block_header_encode(%struct.lzma_block* %50, i8* %add.ptr) #8, !dbg !585
  store i32 %call34, i32* %ret, align 4, !dbg !586
  %53 = load i32, i32* %ret, align 4, !dbg !587
  %cmp35 = icmp ne i32 %53, 0, !dbg !589
  br i1 %cmp35, label %if.then37, label %if.end38, !dbg !590

if.then37:                                        ; preds = %if.then28
  store i32 11, i32* %ret, align 4, !dbg !591
  br label %if.end38, !dbg !592

if.end38:                                         ; preds = %if.then37, %if.then28
  br label %if.end43, !dbg !593

if.else:                                          ; preds = %if.end25
  %54 = load i32, i32* %ret, align 4, !dbg !594
  %cmp39 = icmp eq i32 %54, 0, !dbg !597
  br i1 %cmp39, label %if.then41, label %if.end42, !dbg !594

if.then41:                                        ; preds = %if.else
  store i32 10, i32* %ret, align 4, !dbg !598
  br label %if.end42, !dbg !600

if.end42:                                         ; preds = %if.then41, %if.else
  br label %if.end43

if.end43:                                         ; preds = %if.end42, %if.end38
  %55 = load i32, i32* %ret, align 4, !dbg !601
  %cmp44 = icmp ne i32 %55, 0, !dbg !603
  br i1 %cmp44, label %if.then46, label %if.end47, !dbg !604

if.then46:                                        ; preds = %if.end43
  %56 = load i64, i64* %out_start, align 8, !dbg !605
  %57 = load i64*, i64** %out_pos.addr, align 8, !dbg !606
  store i64 %56, i64* %57, align 8, !dbg !607
  br label %if.end47, !dbg !608

if.end47:                                         ; preds = %if.then46, %if.end43
  %58 = load i32, i32* %ret, align 4, !dbg !609
  store i32 %58, i32* %retval, align 4, !dbg !610
  br label %return, !dbg !610

return:                                           ; preds = %if.end47, %if.then8, %if.then4, %if.then
  %59 = load i32, i32* %retval, align 4, !dbg !611
  ret i32 %59, !dbg !611
}

; Function Attrs: nounwind uwtable
define internal i32 @block_encode_uncompressed(%struct.lzma_block* %block, i8* %in, i64 %in_size, i8* %out, i64* %out_pos, i64 %out_size) #0 !dbg !137 {
entry:
  %retval = alloca i32, align 4
  %block.addr = alloca %struct.lzma_block*, align 8
  %in.addr = alloca i8*, align 8
  %in_size.addr = alloca i64, align 8
  %out.addr = alloca i8*, align 8
  %out_pos.addr = alloca i64*, align 8
  %out_size.addr = alloca i64, align 8
  %in_pos = alloca i64, align 8
  %control = alloca i8, align 1
  %filters_orig = alloca %struct.lzma_filter*, align 8
  %lzma2 = alloca %struct.lzma_options_lzma, align 8
  %filters = alloca [2 x %struct.lzma_filter], align 16
  %copy_size = alloca i64, align 8
  store %struct.lzma_block* %block, %struct.lzma_block** %block.addr, align 8
  call void @llvm.dbg.declare(metadata %struct.lzma_block** %block.addr, metadata !612, metadata !189), !dbg !613
  store i8* %in, i8** %in.addr, align 8
  call void @llvm.dbg.declare(metadata i8** %in.addr, metadata !614, metadata !189), !dbg !615
  store i64 %in_size, i64* %in_size.addr, align 8
  call void @llvm.dbg.declare(metadata i64* %in_size.addr, metadata !616, metadata !189), !dbg !617
  store i8* %out, i8** %out.addr, align 8
  call void @llvm.dbg.declare(metadata i8** %out.addr, metadata !618, metadata !189), !dbg !619
  store i64* %out_pos, i64** %out_pos.addr, align 8
  call void @llvm.dbg.declare(metadata i64** %out_pos.addr, metadata !620, metadata !189), !dbg !621
  store i64 %out_size, i64* %out_size.addr, align 8
  call void @llvm.dbg.declare(metadata i64* %out_size.addr, metadata !622, metadata !189), !dbg !623
  call void @llvm.dbg.declare(metadata i64* %in_pos, metadata !624, metadata !189), !dbg !625
  store i64 0, i64* %in_pos, align 8, !dbg !625
  call void @llvm.dbg.declare(metadata i8* %control, metadata !626, metadata !189), !dbg !627
  store i8 1, i8* %control, align 1, !dbg !627
  call void @llvm.dbg.declare(metadata %struct.lzma_filter** %filters_orig, metadata !628, metadata !189), !dbg !629
  call void @llvm.dbg.declare(metadata %struct.lzma_options_lzma* %lzma2, metadata !630, metadata !189), !dbg !660
  %0 = bitcast %struct.lzma_options_lzma* %lzma2 to i8*, !dbg !660
  call void @llvm.memset.p0i8.i64(i8* %0, i8 0, i64 112, i32 8, i1 false), !dbg !660
  %1 = bitcast i8* %0 to %struct.lzma_options_lzma*, !dbg !660
  %2 = getelementptr %struct.lzma_options_lzma, %struct.lzma_options_lzma* %1, i32 0, i32 0, !dbg !660
  store i32 4096, i32* %2, !dbg !660
  call void @llvm.dbg.declare(metadata [2 x %struct.lzma_filter]* %filters, metadata !661, metadata !189), !dbg !665
  %arrayidx = getelementptr inbounds [2 x %struct.lzma_filter], [2 x %struct.lzma_filter]* %filters, i64 0, i64 0, !dbg !666
  %id = getelementptr inbounds %struct.lzma_filter, %struct.lzma_filter* %arrayidx, i32 0, i32 0, !dbg !667
  store i64 33, i64* %id, align 16, !dbg !668
  %3 = bitcast %struct.lzma_options_lzma* %lzma2 to i8*, !dbg !669
  %arrayidx1 = getelementptr inbounds [2 x %struct.lzma_filter], [2 x %struct.lzma_filter]* %filters, i64 0, i64 0, !dbg !670
  %options = getelementptr inbounds %struct.lzma_filter, %struct.lzma_filter* %arrayidx1, i32 0, i32 1, !dbg !671
  store i8* %3, i8** %options, align 8, !dbg !672
  %arrayidx2 = getelementptr inbounds [2 x %struct.lzma_filter], [2 x %struct.lzma_filter]* %filters, i64 0, i64 1, !dbg !673
  %id3 = getelementptr inbounds %struct.lzma_filter, %struct.lzma_filter* %arrayidx2, i32 0, i32 0, !dbg !674
  store i64 -1, i64* %id3, align 16, !dbg !675
  %4 = load %struct.lzma_block*, %struct.lzma_block** %block.addr, align 8, !dbg !676
  %filters4 = getelementptr inbounds %struct.lzma_block, %struct.lzma_block* %4, i32 0, i32 5, !dbg !677
  %5 = load %struct.lzma_filter*, %struct.lzma_filter** %filters4, align 8, !dbg !677
  store %struct.lzma_filter* %5, %struct.lzma_filter** %filters_orig, align 8, !dbg !678
  %arraydecay = getelementptr inbounds [2 x %struct.lzma_filter], [2 x %struct.lzma_filter]* %filters, i32 0, i32 0, !dbg !679
  %6 = load %struct.lzma_block*, %struct.lzma_block** %block.addr, align 8, !dbg !680
  %filters5 = getelementptr inbounds %struct.lzma_block, %struct.lzma_block* %6, i32 0, i32 5, !dbg !681
  store %struct.lzma_filter* %arraydecay, %struct.lzma_filter** %filters5, align 8, !dbg !682
  %7 = load %struct.lzma_block*, %struct.lzma_block** %block.addr, align 8, !dbg !683
  %call = call i32 @lzma_block_header_size(%struct.lzma_block* %7) #8, !dbg !685
  %cmp = icmp ne i32 %call, 0, !dbg !686
  br i1 %cmp, label %if.then, label %if.end, !dbg !687

if.then:                                          ; preds = %entry
  %8 = load %struct.lzma_filter*, %struct.lzma_filter** %filters_orig, align 8, !dbg !688
  %9 = load %struct.lzma_block*, %struct.lzma_block** %block.addr, align 8, !dbg !690
  %filters6 = getelementptr inbounds %struct.lzma_block, %struct.lzma_block* %9, i32 0, i32 5, !dbg !691
  store %struct.lzma_filter* %8, %struct.lzma_filter** %filters6, align 8, !dbg !692
  store i32 11, i32* %retval, align 4, !dbg !693
  br label %return, !dbg !693

if.end:                                           ; preds = %entry
  %10 = load %struct.lzma_block*, %struct.lzma_block** %block.addr, align 8, !dbg !694
  %compressed_size = getelementptr inbounds %struct.lzma_block, %struct.lzma_block* %10, i32 0, i32 3, !dbg !694
  %11 = load i64, i64* %compressed_size, align 8, !dbg !694
  %12 = load i64, i64* %in_size.addr, align 8, !dbg !694
  %call7 = call i64 @lzma2_bound(i64 %12), !dbg !694
  %cmp8 = icmp eq i64 %11, %call7, !dbg !694
  br i1 %cmp8, label %cond.true, label %cond.false, !dbg !694

cond.true:                                        ; preds = %if.end
  br label %cond.end, !dbg !695

cond.false:                                       ; preds = %if.end
  call void @__assert_fail(i8* getelementptr inbounds ([47 x i8], [47 x i8]* @.str.4, i32 0, i32 0), i8* getelementptr inbounds ([92 x i8], [92 x i8]* @.str.1, i32 0, i32 0), i32 119, i8* getelementptr inbounds ([103 x i8], [103 x i8]* @__PRETTY_FUNCTION__.block_encode_uncompressed, i32 0, i32 0)) #7, !dbg !697
  unreachable, !dbg !697
                                                  ; No predecessors!
  br label %cond.end, !dbg !699

cond.end:                                         ; preds = %13, %cond.true
  %14 = load i64, i64* %out_size.addr, align 8, !dbg !701
  %15 = load i64*, i64** %out_pos.addr, align 8, !dbg !703
  %16 = load i64, i64* %15, align 8, !dbg !704
  %sub = sub i64 %14, %16, !dbg !705
  %17 = load %struct.lzma_block*, %struct.lzma_block** %block.addr, align 8, !dbg !706
  %header_size = getelementptr inbounds %struct.lzma_block, %struct.lzma_block* %17, i32 0, i32 1, !dbg !707
  %18 = load i32, i32* %header_size, align 4, !dbg !707
  %conv = zext i32 %18 to i64, !dbg !706
  %19 = load %struct.lzma_block*, %struct.lzma_block** %block.addr, align 8, !dbg !708
  %compressed_size9 = getelementptr inbounds %struct.lzma_block, %struct.lzma_block* %19, i32 0, i32 3, !dbg !709
  %20 = load i64, i64* %compressed_size9, align 8, !dbg !709
  %add = add i64 %conv, %20, !dbg !710
  %cmp10 = icmp ult i64 %sub, %add, !dbg !711
  br i1 %cmp10, label %if.then12, label %if.end14, !dbg !712

if.then12:                                        ; preds = %cond.end
  %21 = load %struct.lzma_filter*, %struct.lzma_filter** %filters_orig, align 8, !dbg !713
  %22 = load %struct.lzma_block*, %struct.lzma_block** %block.addr, align 8, !dbg !715
  %filters13 = getelementptr inbounds %struct.lzma_block, %struct.lzma_block* %22, i32 0, i32 5, !dbg !716
  store %struct.lzma_filter* %21, %struct.lzma_filter** %filters13, align 8, !dbg !717
  store i32 10, i32* %retval, align 4, !dbg !718
  br label %return, !dbg !718

if.end14:                                         ; preds = %cond.end
  %23 = load %struct.lzma_block*, %struct.lzma_block** %block.addr, align 8, !dbg !719
  %24 = load i8*, i8** %out.addr, align 8, !dbg !721
  %25 = load i64*, i64** %out_pos.addr, align 8, !dbg !722
  %26 = load i64, i64* %25, align 8, !dbg !723
  %add.ptr = getelementptr inbounds i8, i8* %24, i64 %26, !dbg !724
  %call15 = call i32 @lzma_block_header_encode(%struct.lzma_block* %23, i8* %add.ptr) #8, !dbg !725
  %cmp16 = icmp ne i32 %call15, 0, !dbg !726
  br i1 %cmp16, label %if.then18, label %if.end20, !dbg !727

if.then18:                                        ; preds = %if.end14
  %27 = load %struct.lzma_filter*, %struct.lzma_filter** %filters_orig, align 8, !dbg !728
  %28 = load %struct.lzma_block*, %struct.lzma_block** %block.addr, align 8, !dbg !730
  %filters19 = getelementptr inbounds %struct.lzma_block, %struct.lzma_block* %28, i32 0, i32 5, !dbg !731
  store %struct.lzma_filter* %27, %struct.lzma_filter** %filters19, align 8, !dbg !732
  store i32 11, i32* %retval, align 4, !dbg !733
  br label %return, !dbg !733

if.end20:                                         ; preds = %if.end14
  %29 = load %struct.lzma_filter*, %struct.lzma_filter** %filters_orig, align 8, !dbg !734
  %30 = load %struct.lzma_block*, %struct.lzma_block** %block.addr, align 8, !dbg !735
  %filters21 = getelementptr inbounds %struct.lzma_block, %struct.lzma_block* %30, i32 0, i32 5, !dbg !736
  store %struct.lzma_filter* %29, %struct.lzma_filter** %filters21, align 8, !dbg !737
  %31 = load %struct.lzma_block*, %struct.lzma_block** %block.addr, align 8, !dbg !738
  %header_size22 = getelementptr inbounds %struct.lzma_block, %struct.lzma_block* %31, i32 0, i32 1, !dbg !739
  %32 = load i32, i32* %header_size22, align 4, !dbg !739
  %conv23 = zext i32 %32 to i64, !dbg !738
  %33 = load i64*, i64** %out_pos.addr, align 8, !dbg !740
  %34 = load i64, i64* %33, align 8, !dbg !741
  %add24 = add i64 %34, %conv23, !dbg !741
  store i64 %add24, i64* %33, align 8, !dbg !741
  br label %while.cond, !dbg !742

while.cond:                                       ; preds = %cond.end48, %if.end20
  %35 = load i64, i64* %in_pos, align 8, !dbg !743
  %36 = load i64, i64* %in_size.addr, align 8, !dbg !744
  %cmp25 = icmp ult i64 %35, %36, !dbg !745
  br i1 %cmp25, label %while.body, label %while.end, !dbg !746

while.body:                                       ; preds = %while.cond
  call void @llvm.dbg.declare(metadata i64* %copy_size, metadata !747, metadata !189), !dbg !749
  %37 = load i8, i8* %control, align 1, !dbg !750
  %38 = load i64*, i64** %out_pos.addr, align 8, !dbg !751
  %39 = load i64, i64* %38, align 8, !dbg !752
  %inc = add i64 %39, 1, !dbg !752
  store i64 %inc, i64* %38, align 8, !dbg !752
  %40 = load i8*, i8** %out.addr, align 8, !dbg !753
  %arrayidx27 = getelementptr inbounds i8, i8* %40, i64 %39, !dbg !753
  store i8 %37, i8* %arrayidx27, align 1, !dbg !754
  store i8 2, i8* %control, align 1, !dbg !755
  %41 = load i64, i64* %in_size.addr, align 8, !dbg !756
  %42 = load i64, i64* %in_pos, align 8, !dbg !756
  %sub28 = sub i64 %41, %42, !dbg !756
  %cmp29 = icmp ult i64 %sub28, 65536, !dbg !756
  br i1 %cmp29, label %cond.true31, label %cond.false33, !dbg !756

cond.true31:                                      ; preds = %while.body
  %43 = load i64, i64* %in_size.addr, align 8, !dbg !757
  %44 = load i64, i64* %in_pos, align 8, !dbg !757
  %sub32 = sub i64 %43, %44, !dbg !757
  br label %cond.end34, !dbg !757

cond.false33:                                     ; preds = %while.body
  br label %cond.end34, !dbg !759

cond.end34:                                       ; preds = %cond.false33, %cond.true31
  %cond = phi i64 [ %sub32, %cond.true31 ], [ 65536, %cond.false33 ], !dbg !761
  store i64 %cond, i64* %copy_size, align 8, !dbg !763
  %45 = load i64, i64* %copy_size, align 8, !dbg !764
  %sub35 = sub i64 %45, 1, !dbg !765
  %shr = lshr i64 %sub35, 8, !dbg !766
  %conv36 = trunc i64 %shr to i8, !dbg !767
  %46 = load i64*, i64** %out_pos.addr, align 8, !dbg !768
  %47 = load i64, i64* %46, align 8, !dbg !769
  %inc37 = add i64 %47, 1, !dbg !769
  store i64 %inc37, i64* %46, align 8, !dbg !769
  %48 = load i8*, i8** %out.addr, align 8, !dbg !770
  %arrayidx38 = getelementptr inbounds i8, i8* %48, i64 %47, !dbg !770
  store i8 %conv36, i8* %arrayidx38, align 1, !dbg !771
  %49 = load i64, i64* %copy_size, align 8, !dbg !772
  %sub39 = sub i64 %49, 1, !dbg !773
  %and = and i64 %sub39, 255, !dbg !774
  %conv40 = trunc i64 %and to i8, !dbg !775
  %50 = load i64*, i64** %out_pos.addr, align 8, !dbg !776
  %51 = load i64, i64* %50, align 8, !dbg !777
  %inc41 = add i64 %51, 1, !dbg !777
  store i64 %inc41, i64* %50, align 8, !dbg !777
  %52 = load i8*, i8** %out.addr, align 8, !dbg !778
  %arrayidx42 = getelementptr inbounds i8, i8* %52, i64 %51, !dbg !778
  store i8 %conv40, i8* %arrayidx42, align 1, !dbg !779
  %53 = load i64*, i64** %out_pos.addr, align 8, !dbg !780
  %54 = load i64, i64* %53, align 8, !dbg !780
  %55 = load i64, i64* %copy_size, align 8, !dbg !780
  %add43 = add i64 %54, %55, !dbg !780
  %56 = load i64, i64* %out_size.addr, align 8, !dbg !780
  %cmp44 = icmp ule i64 %add43, %56, !dbg !780
  br i1 %cmp44, label %cond.true46, label %cond.false47, !dbg !780

cond.true46:                                      ; preds = %cond.end34
  br label %cond.end48, !dbg !781

cond.false47:                                     ; preds = %cond.end34
  call void @__assert_fail(i8* getelementptr inbounds ([33 x i8], [33 x i8]* @.str.5, i32 0, i32 0), i8* getelementptr inbounds ([92 x i8], [92 x i8]* @.str.1, i32 0, i32 0), i32 150, i8* getelementptr inbounds ([103 x i8], [103 x i8]* @__PRETTY_FUNCTION__.block_encode_uncompressed, i32 0, i32 0)) #7, !dbg !782
  unreachable, !dbg !782
                                                  ; No predecessors!
  br label %cond.end48, !dbg !783

cond.end48:                                       ; preds = %57, %cond.true46
  %58 = load i8*, i8** %out.addr, align 8, !dbg !784
  %59 = load i64*, i64** %out_pos.addr, align 8, !dbg !785
  %60 = load i64, i64* %59, align 8, !dbg !786
  %add.ptr49 = getelementptr inbounds i8, i8* %58, i64 %60, !dbg !787
  %61 = load i8*, i8** %in.addr, align 8, !dbg !788
  %62 = load i64, i64* %in_pos, align 8, !dbg !789
  %add.ptr50 = getelementptr inbounds i8, i8* %61, i64 %62, !dbg !790
  %63 = load i64, i64* %copy_size, align 8, !dbg !791
  call void @llvm.memcpy.p0i8.p0i8.i64(i8* %add.ptr49, i8* %add.ptr50, i64 %63, i32 1, i1 false), !dbg !792
  %64 = load i64, i64* %copy_size, align 8, !dbg !793
  %65 = load i64, i64* %in_pos, align 8, !dbg !794
  %add51 = add i64 %65, %64, !dbg !794
  store i64 %add51, i64* %in_pos, align 8, !dbg !794
  %66 = load i64, i64* %copy_size, align 8, !dbg !795
  %67 = load i64*, i64** %out_pos.addr, align 8, !dbg !796
  %68 = load i64, i64* %67, align 8, !dbg !797
  %add52 = add i64 %68, %66, !dbg !797
  store i64 %add52, i64* %67, align 8, !dbg !797
  br label %while.cond, !dbg !798

while.end:                                        ; preds = %while.cond
  %69 = load i64*, i64** %out_pos.addr, align 8, !dbg !799
  %70 = load i64, i64* %69, align 8, !dbg !800
  %inc53 = add i64 %70, 1, !dbg !800
  store i64 %inc53, i64* %69, align 8, !dbg !800
  %71 = load i8*, i8** %out.addr, align 8, !dbg !801
  %arrayidx54 = getelementptr inbounds i8, i8* %71, i64 %70, !dbg !801
  store i8 0, i8* %arrayidx54, align 1, !dbg !802
  %72 = load i64*, i64** %out_pos.addr, align 8, !dbg !803
  %73 = load i64, i64* %72, align 8, !dbg !803
  %74 = load i64, i64* %out_size.addr, align 8, !dbg !803
  %cmp55 = icmp ule i64 %73, %74, !dbg !803
  br i1 %cmp55, label %cond.true57, label %cond.false58, !dbg !803

cond.true57:                                      ; preds = %while.end
  br label %cond.end59, !dbg !804

cond.false58:                                     ; preds = %while.end
  call void @__assert_fail(i8* getelementptr inbounds ([21 x i8], [21 x i8]* @.str.2, i32 0, i32 0), i8* getelementptr inbounds ([92 x i8], [92 x i8]* @.str.1, i32 0, i32 0), i32 159, i8* getelementptr inbounds ([103 x i8], [103 x i8]* @__PRETTY_FUNCTION__.block_encode_uncompressed, i32 0, i32 0)) #7, !dbg !805
  unreachable, !dbg !805
                                                  ; No predecessors!
  br label %cond.end59, !dbg !806

cond.end59:                                       ; preds = %75, %cond.true57
  store i32 0, i32* %retval, align 4, !dbg !807
  br label %return, !dbg !807

return:                                           ; preds = %cond.end59, %if.then18, %if.then12, %if.then
  %76 = load i32, i32* %retval, align 4, !dbg !808
  ret i32 %76, !dbg !808
}

declare void @lzma_check_init(%struct.lzma_check_state*, i32) #4

declare void @lzma_check_update(%struct.lzma_check_state*, i32, i8*, i64) #4

declare void @lzma_check_finish(%struct.lzma_check_state*, i32) #4

; Function Attrs: argmemonly nounwind
declare void @llvm.memcpy.p0i8.p0i8.i64(i8* nocapture, i8* nocapture readonly, i64, i32, i1) #5

; Function Attrs: nounwind
declare i32 @lzma_block_header_size(%struct.lzma_block*) #6

declare i32 @lzma_raw_encoder_init(%struct.lzma_next_coder_s*, %struct.lzma_allocator*, %struct.lzma_filter*) #4

declare void @lzma_next_end(%struct.lzma_next_coder_s*, %struct.lzma_allocator*) #4

; Function Attrs: nounwind
declare i32 @lzma_block_header_encode(%struct.lzma_block*, i8*) #6

; Function Attrs: argmemonly nounwind
declare void @llvm.memset.p0i8.i64(i8* nocapture, i8, i64, i32, i1) #5

attributes #0 = { nounwind uwtable "disable-tail-calls"="false" "less-precise-fpmad"="false" "no-frame-pointer-elim"="true" "no-frame-pointer-elim-non-leaf" "no-infs-fp-math"="false" "no-nans-fp-math"="false" "stack-protector-buffer-size"="8" "target-cpu"="x86-64" "target-features"="+fxsr,+mmx,+sse,+sse2" "unsafe-fp-math"="false" "use-soft-float"="false" }
attributes #1 = { nounwind readnone }
attributes #2 = { nounwind readnone "disable-tail-calls"="false" "less-precise-fpmad"="false" "no-frame-pointer-elim"="true" "no-frame-pointer-elim-non-leaf" "no-infs-fp-math"="false" "no-nans-fp-math"="false" "stack-protector-buffer-size"="8" "target-cpu"="x86-64" "target-features"="+fxsr,+mmx,+sse,+sse2" "unsafe-fp-math"="false" "use-soft-float"="false" }
attributes #3 = { noreturn nounwind "disable-tail-calls"="false" "less-precise-fpmad"="false" "no-frame-pointer-elim"="true" "no-frame-pointer-elim-non-leaf" "no-infs-fp-math"="false" "no-nans-fp-math"="false" "stack-protector-buffer-size"="8" "target-cpu"="x86-64" "target-features"="+fxsr,+mmx,+sse,+sse2" "unsafe-fp-math"="false" "use-soft-float"="false" }
attributes #4 = { "disable-tail-calls"="false" "less-precise-fpmad"="false" "no-frame-pointer-elim"="true" "no-frame-pointer-elim-non-leaf" "no-infs-fp-math"="false" "no-nans-fp-math"="false" "stack-protector-buffer-size"="8" "target-cpu"="x86-64" "target-features"="+fxsr,+mmx,+sse,+sse2" "unsafe-fp-math"="false" "use-soft-float"="false" }
attributes #5 = { argmemonly nounwind }
attributes #6 = { nounwind "disable-tail-calls"="false" "less-precise-fpmad"="false" "no-frame-pointer-elim"="true" "no-frame-pointer-elim-non-leaf" "no-infs-fp-math"="false" "no-nans-fp-math"="false" "stack-protector-buffer-size"="8" "target-cpu"="x86-64" "target-features"="+fxsr,+mmx,+sse,+sse2" "unsafe-fp-math"="false" "use-soft-float"="false" }
attributes #7 = { noreturn nounwind }
attributes #8 = { nounwind }

!llvm.dbg.cu = !{!0}
!llvm.module.flags = !{!185, !186}
!llvm.ident = !{!187}

!0 = distinct !DICompileUnit(language: DW_LANG_C99, file: !1, producer: "clang version 3.8.0 (tags/RELEASE_380/final)", isOptimized: false, runtimeVersion: 0, emissionKind: 1, enums: !2, retainedTypes: !46, subprograms: !52, globals: !140)
!1 = !DIFile(filename: "/data/download/cmake/cmake-master/Utilities/cmliblzma/liblzma/common/block_buffer_encoder.c", directory: "/data/download/cmake/cmake-master/Utilities/cmliblzma")
!2 = !{!3, !18, !25, !28, !34, !39}
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
!18 = !DICompositeType(tag: DW_TAG_enumeration_type, file: !19, line: 27, size: 32, align: 32, elements: !20)
!19 = !DIFile(filename: "/data/download/cmake/cmake-master/Utilities/cmliblzma/liblzma/api/lzma/check.h", directory: "/data/download/cmake/cmake-master/Utilities/cmliblzma")
!20 = !{!21, !22, !23, !24}
!21 = !DIEnumerator(name: "LZMA_CHECK_NONE", value: 0)
!22 = !DIEnumerator(name: "LZMA_CHECK_CRC32", value: 1)
!23 = !DIEnumerator(name: "LZMA_CHECK_CRC64", value: 4)
!24 = !DIEnumerator(name: "LZMA_CHECK_SHA256", value: 10)
!25 = !DICompositeType(tag: DW_TAG_enumeration_type, file: !4, line: 44, size: 32, align: 32, elements: !26)
!26 = !{!27}
!27 = !DIEnumerator(name: "LZMA_RESERVED_ENUM", value: 0)
!28 = !DICompositeType(tag: DW_TAG_enumeration_type, file: !4, line: 250, size: 32, align: 32, elements: !29)
!29 = !{!30, !31, !32, !33}
!30 = !DIEnumerator(name: "LZMA_RUN", value: 0)
!31 = !DIEnumerator(name: "LZMA_SYNC_FLUSH", value: 1)
!32 = !DIEnumerator(name: "LZMA_FULL_FLUSH", value: 2)
!33 = !DIEnumerator(name: "LZMA_FINISH", value: 3)
!34 = !DICompositeType(tag: DW_TAG_enumeration_type, file: !35, line: 138, size: 32, align: 32, elements: !36)
!35 = !DIFile(filename: "/data/download/cmake/cmake-master/Utilities/cmliblzma/liblzma/api/lzma/lzma.h", directory: "/data/download/cmake/cmake-master/Utilities/cmliblzma")
!36 = !{!37, !38}
!37 = !DIEnumerator(name: "LZMA_MODE_FAST", value: 1)
!38 = !DIEnumerator(name: "LZMA_MODE_NORMAL", value: 2)
!39 = !DICompositeType(tag: DW_TAG_enumeration_type, file: !35, line: 58, size: 32, align: 32, elements: !40)
!40 = !{!41, !42, !43, !44, !45}
!41 = !DIEnumerator(name: "LZMA_MF_HC3", value: 3)
!42 = !DIEnumerator(name: "LZMA_MF_HC4", value: 4)
!43 = !DIEnumerator(name: "LZMA_MF_BT2", value: 18)
!44 = !DIEnumerator(name: "LZMA_MF_BT3", value: 19)
!45 = !DIEnumerator(name: "LZMA_MF_BT4", value: 20)
!46 = !{!47, !48, !49}
!47 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: null, size: 64, align: 64)
!48 = !DIBasicType(name: "unsigned int", size: 32, align: 32, encoding: DW_ATE_unsigned)
!49 = !DIDerivedType(tag: DW_TAG_typedef, name: "size_t", file: !50, line: 62, baseType: !51)
!50 = !DIFile(filename: "/opt/llvm-build/bin/../lib/clang/3.8.0/include/stddef.h", directory: "/data/download/cmake/cmake-master/Utilities/cmliblzma")
!51 = !DIBasicType(name: "long unsigned int", size: 64, align: 64, encoding: DW_ATE_unsigned)
!52 = !{!53, !57, !133, !136, !137}
!53 = distinct !DISubprogram(name: "lzma_block_buffer_bound", scope: !1, file: !1, line: 57, type: !54, isLocal: false, isDefinition: true, scopeLine: 58, flags: DIFlagPrototyped, isOptimized: false, variables: !56)
!54 = !DISubroutineType(types: !55)
!55 = !{!49, !49}
!56 = !{}
!57 = distinct !DISubprogram(name: "lzma_block_buffer_encode", scope: !1, file: !1, line: 231, type: !58, isLocal: false, isDefinition: true, scopeLine: 234, flags: DIFlagPrototyped, isOptimized: false, variables: !56)
!58 = !DISubroutineType(types: !59)
!59 = !{!60, !61, !116, !129, !49, !131, !132, !49}
!60 = !DIDerivedType(tag: DW_TAG_typedef, name: "lzma_ret", file: !4, line: 237, baseType: !3)
!61 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !62, size: 64, align: 64)
!62 = !DIDerivedType(tag: DW_TAG_typedef, name: "lzma_block", file: !63, line: 245, baseType: !64)
!63 = !DIFile(filename: "/data/download/cmake/cmake-master/Utilities/cmliblzma/liblzma/api/lzma/block.h", directory: "/data/download/cmake/cmake-master/Utilities/cmliblzma")
!64 = !DICompositeType(tag: DW_TAG_structure_type, file: !63, line: 30, size: 1664, align: 64, elements: !65)
!65 = !{!66, !69, !70, !72, !76, !77, !85, !91, !92, !93, !94, !95, !96, !97, !98, !99, !100, !101, !102, !104, !105, !106, !107, !109, !110, !111, !112, !113, !114, !115}
!66 = !DIDerivedType(tag: DW_TAG_member, name: "version", scope: !64, file: !63, line: 47, baseType: !67, size: 32, align: 32)
!67 = !DIDerivedType(tag: DW_TAG_typedef, name: "uint32_t", file: !68, line: 51, baseType: !48)
!68 = !DIFile(filename: "/usr/include/stdint.h", directory: "/data/download/cmake/cmake-master/Utilities/cmliblzma")
!69 = !DIDerivedType(tag: DW_TAG_member, name: "header_size", scope: !64, file: !63, line: 67, baseType: !67, size: 32, align: 32, offset: 32)
!70 = !DIDerivedType(tag: DW_TAG_member, name: "check", scope: !64, file: !63, line: 88, baseType: !71, size: 32, align: 32, offset: 64)
!71 = !DIDerivedType(tag: DW_TAG_typedef, name: "lzma_check", file: !19, line: 55, baseType: !18)
!72 = !DIDerivedType(tag: DW_TAG_member, name: "compressed_size", scope: !64, file: !63, line: 143, baseType: !73, size: 64, align: 64, offset: 128)
!73 = !DIDerivedType(tag: DW_TAG_typedef, name: "lzma_vli", file: !74, line: 63, baseType: !75)
!74 = !DIFile(filename: "/data/download/cmake/cmake-master/Utilities/cmliblzma/liblzma/api/lzma/vli.h", directory: "/data/download/cmake/cmake-master/Utilities/cmliblzma")
!75 = !DIDerivedType(tag: DW_TAG_typedef, name: "uint64_t", file: !68, line: 55, baseType: !51)
!76 = !DIDerivedType(tag: DW_TAG_member, name: "uncompressed_size", scope: !64, file: !63, line: 167, baseType: !73, size: 64, align: 64, offset: 192)
!77 = !DIDerivedType(tag: DW_TAG_member, name: "filters", scope: !64, file: !63, line: 195, baseType: !78, size: 64, align: 64, offset: 256)
!78 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !79, size: 64, align: 64)
!79 = !DIDerivedType(tag: DW_TAG_typedef, name: "lzma_filter", file: !80, line: 65, baseType: !81)
!80 = !DIFile(filename: "/data/download/cmake/cmake-master/Utilities/cmliblzma/liblzma/api/lzma/filter.h", directory: "/data/download/cmake/cmake-master/Utilities/cmliblzma")
!81 = !DICompositeType(tag: DW_TAG_structure_type, file: !80, line: 43, size: 128, align: 64, elements: !82)
!82 = !{!83, !84}
!83 = !DIDerivedType(tag: DW_TAG_member, name: "id", scope: !81, file: !80, line: 54, baseType: !73, size: 64, align: 64)
!84 = !DIDerivedType(tag: DW_TAG_member, name: "options", scope: !81, file: !80, line: 63, baseType: !47, size: 64, align: 64, offset: 64)
!85 = !DIDerivedType(tag: DW_TAG_member, name: "raw_check", scope: !64, file: !63, line: 212, baseType: !86, size: 512, align: 8, offset: 320)
!86 = !DICompositeType(tag: DW_TAG_array_type, baseType: !87, size: 512, align: 8, elements: !89)
!87 = !DIDerivedType(tag: DW_TAG_typedef, name: "uint8_t", file: !68, line: 48, baseType: !88)
!88 = !DIBasicType(name: "unsigned char", size: 8, align: 8, encoding: DW_ATE_unsigned_char)
!89 = !{!90}
!90 = !DISubrange(count: 64)
!91 = !DIDerivedType(tag: DW_TAG_member, name: "reserved_ptr1", scope: !64, file: !63, line: 221, baseType: !47, size: 64, align: 64, offset: 832)
!92 = !DIDerivedType(tag: DW_TAG_member, name: "reserved_ptr2", scope: !64, file: !63, line: 222, baseType: !47, size: 64, align: 64, offset: 896)
!93 = !DIDerivedType(tag: DW_TAG_member, name: "reserved_ptr3", scope: !64, file: !63, line: 223, baseType: !47, size: 64, align: 64, offset: 960)
!94 = !DIDerivedType(tag: DW_TAG_member, name: "reserved_int1", scope: !64, file: !63, line: 224, baseType: !67, size: 32, align: 32, offset: 1024)
!95 = !DIDerivedType(tag: DW_TAG_member, name: "reserved_int2", scope: !64, file: !63, line: 225, baseType: !67, size: 32, align: 32, offset: 1056)
!96 = !DIDerivedType(tag: DW_TAG_member, name: "reserved_int3", scope: !64, file: !63, line: 226, baseType: !73, size: 64, align: 64, offset: 1088)
!97 = !DIDerivedType(tag: DW_TAG_member, name: "reserved_int4", scope: !64, file: !63, line: 227, baseType: !73, size: 64, align: 64, offset: 1152)
!98 = !DIDerivedType(tag: DW_TAG_member, name: "reserved_int5", scope: !64, file: !63, line: 228, baseType: !73, size: 64, align: 64, offset: 1216)
!99 = !DIDerivedType(tag: DW_TAG_member, name: "reserved_int6", scope: !64, file: !63, line: 229, baseType: !73, size: 64, align: 64, offset: 1280)
!100 = !DIDerivedType(tag: DW_TAG_member, name: "reserved_int7", scope: !64, file: !63, line: 230, baseType: !73, size: 64, align: 64, offset: 1344)
!101 = !DIDerivedType(tag: DW_TAG_member, name: "reserved_int8", scope: !64, file: !63, line: 231, baseType: !73, size: 64, align: 64, offset: 1408)
!102 = !DIDerivedType(tag: DW_TAG_member, name: "reserved_enum1", scope: !64, file: !63, line: 232, baseType: !103, size: 32, align: 32, offset: 1472)
!103 = !DIDerivedType(tag: DW_TAG_typedef, name: "lzma_reserved_enum", file: !4, line: 46, baseType: !25)
!104 = !DIDerivedType(tag: DW_TAG_member, name: "reserved_enum2", scope: !64, file: !63, line: 233, baseType: !103, size: 32, align: 32, offset: 1504)
!105 = !DIDerivedType(tag: DW_TAG_member, name: "reserved_enum3", scope: !64, file: !63, line: 234, baseType: !103, size: 32, align: 32, offset: 1536)
!106 = !DIDerivedType(tag: DW_TAG_member, name: "reserved_enum4", scope: !64, file: !63, line: 235, baseType: !103, size: 32, align: 32, offset: 1568)
!107 = !DIDerivedType(tag: DW_TAG_member, name: "reserved_bool1", scope: !64, file: !63, line: 236, baseType: !108, size: 8, align: 8, offset: 1600)
!108 = !DIDerivedType(tag: DW_TAG_typedef, name: "lzma_bool", file: !4, line: 29, baseType: !88)
!109 = !DIDerivedType(tag: DW_TAG_member, name: "reserved_bool2", scope: !64, file: !63, line: 237, baseType: !108, size: 8, align: 8, offset: 1608)
!110 = !DIDerivedType(tag: DW_TAG_member, name: "reserved_bool3", scope: !64, file: !63, line: 238, baseType: !108, size: 8, align: 8, offset: 1616)
!111 = !DIDerivedType(tag: DW_TAG_member, name: "reserved_bool4", scope: !64, file: !63, line: 239, baseType: !108, size: 8, align: 8, offset: 1624)
!112 = !DIDerivedType(tag: DW_TAG_member, name: "reserved_bool5", scope: !64, file: !63, line: 240, baseType: !108, size: 8, align: 8, offset: 1632)
!113 = !DIDerivedType(tag: DW_TAG_member, name: "reserved_bool6", scope: !64, file: !63, line: 241, baseType: !108, size: 8, align: 8, offset: 1640)
!114 = !DIDerivedType(tag: DW_TAG_member, name: "reserved_bool7", scope: !64, file: !63, line: 242, baseType: !108, size: 8, align: 8, offset: 1648)
!115 = !DIDerivedType(tag: DW_TAG_member, name: "reserved_bool8", scope: !64, file: !63, line: 243, baseType: !108, size: 8, align: 8, offset: 1656)
!116 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !117, size: 64, align: 64)
!117 = !DIDerivedType(tag: DW_TAG_typedef, name: "lzma_allocator", file: !4, line: 403, baseType: !118)
!118 = !DICompositeType(tag: DW_TAG_structure_type, file: !4, line: 341, size: 192, align: 64, elements: !119)
!119 = !{!120, !124, !128}
!120 = !DIDerivedType(tag: DW_TAG_member, name: "alloc", scope: !118, file: !4, line: 376, baseType: !121, size: 64, align: 64)
!121 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !122, size: 64, align: 64)
!122 = !DISubroutineType(types: !123)
!123 = !{!47, !47, !49, !49}
!124 = !DIDerivedType(tag: DW_TAG_member, name: "free", scope: !118, file: !4, line: 390, baseType: !125, size: 64, align: 64, offset: 64)
!125 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !126, size: 64, align: 64)
!126 = !DISubroutineType(types: !127)
!127 = !{null, !47, !47}
!128 = !DIDerivedType(tag: DW_TAG_member, name: "opaque", scope: !118, file: !4, line: 401, baseType: !47, size: 64, align: 64, offset: 128)
!129 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !130, size: 64, align: 64)
!130 = !DIDerivedType(tag: DW_TAG_const_type, baseType: !87)
!131 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !87, size: 64, align: 64)
!132 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !49, size: 64, align: 64)
!133 = distinct !DISubprogram(name: "lzma2_bound", scope: !1, file: !1, line: 32, type: !134, isLocal: true, isDefinition: true, scopeLine: 33, flags: DIFlagPrototyped, isOptimized: false, variables: !56)
!134 = !DISubroutineType(types: !135)
!135 = !{!73, !73}
!136 = distinct !DISubprogram(name: "block_encode_normal", scope: !1, file: !1, line: 166, type: !58, isLocal: true, isDefinition: true, scopeLine: 169, flags: DIFlagPrototyped, isOptimized: false, variables: !56)
!137 = distinct !DISubprogram(name: "block_encode_uncompressed", scope: !1, file: !1, line: 84, type: !138, isLocal: true, isDefinition: true, scopeLine: 86, flags: DIFlagPrototyped, isOptimized: false, variables: !56)
!138 = !DISubroutineType(types: !139)
!139 = !{!60, !61, !129, !49, !131, !132, !49}
!140 = !{!141}
!141 = !DIGlobalVariable(name: "LZMA_NEXT_CODER_INIT", scope: !0, file: !142, line: 159, type: !143, isLocal: true, isDefinition: true, variable: %struct.lzma_next_coder_s* @LZMA_NEXT_CODER_INIT)
!142 = !DIFile(filename: "/data/download/cmake/cmake-master/Utilities/cmliblzma/liblzma/common/common.h", directory: "/data/download/cmake/cmake-master/Utilities/cmliblzma")
!143 = !DIDerivedType(tag: DW_TAG_const_type, baseType: !144)
!144 = !DIDerivedType(tag: DW_TAG_typedef, name: "lzma_next_coder", file: !142, line: 75, baseType: !145)
!145 = !DICompositeType(tag: DW_TAG_structure_type, name: "lzma_next_coder_s", file: !142, line: 119, size: 512, align: 64, elements: !146)
!146 = !{!147, !151, !152, !154, !163, !168, !174, !179}
!147 = !DIDerivedType(tag: DW_TAG_member, name: "coder", scope: !145, file: !142, line: 121, baseType: !148, size: 64, align: 64)
!148 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !149, size: 64, align: 64)
!149 = !DIDerivedType(tag: DW_TAG_typedef, name: "lzma_coder", file: !142, line: 73, baseType: !150)
!150 = !DICompositeType(tag: DW_TAG_structure_type, name: "lzma_coder_s", file: !142, line: 73, flags: DIFlagFwdDecl)
!151 = !DIDerivedType(tag: DW_TAG_member, name: "id", scope: !145, file: !142, line: 125, baseType: !73, size: 64, align: 64, offset: 64)
!152 = !DIDerivedType(tag: DW_TAG_member, name: "init", scope: !145, file: !142, line: 131, baseType: !153, size: 64, align: 64, offset: 128)
!153 = !DIDerivedType(tag: DW_TAG_typedef, name: "uintptr_t", file: !68, line: 122, baseType: !51)
!154 = !DIDerivedType(tag: DW_TAG_member, name: "code", scope: !145, file: !142, line: 134, baseType: !155, size: 64, align: 64, offset: 192)
!155 = !DIDerivedType(tag: DW_TAG_typedef, name: "lzma_code_function", file: !142, line: 89, baseType: !156)
!156 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !157, size: 64, align: 64)
!157 = !DISubroutineType(types: !158)
!158 = !{!60, !148, !116, !159, !160, !49, !161, !160, !49, !162}
!159 = !DIDerivedType(tag: DW_TAG_restrict_type, baseType: !129)
!160 = !DIDerivedType(tag: DW_TAG_restrict_type, baseType: !132)
!161 = !DIDerivedType(tag: DW_TAG_restrict_type, baseType: !131)
!162 = !DIDerivedType(tag: DW_TAG_typedef, name: "lzma_action", file: !4, line: 322, baseType: !28)
!163 = !DIDerivedType(tag: DW_TAG_member, name: "end", scope: !145, file: !142, line: 139, baseType: !164, size: 64, align: 64, offset: 256)
!164 = !DIDerivedType(tag: DW_TAG_typedef, name: "lzma_end_function", file: !142, line: 97, baseType: !165)
!165 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !166, size: 64, align: 64)
!166 = !DISubroutineType(types: !167)
!167 = !{null, !148, !116}
!168 = !DIDerivedType(tag: DW_TAG_member, name: "get_check", scope: !145, file: !142, line: 143, baseType: !169, size: 64, align: 64, offset: 320)
!169 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !170, size: 64, align: 64)
!170 = !DISubroutineType(types: !171)
!171 = !{!71, !172}
!172 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !173, size: 64, align: 64)
!173 = !DIDerivedType(tag: DW_TAG_const_type, baseType: !149)
!174 = !DIDerivedType(tag: DW_TAG_member, name: "memconfig", scope: !145, file: !142, line: 147, baseType: !175, size: 64, align: 64, offset: 384)
!175 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !176, size: 64, align: 64)
!176 = !DISubroutineType(types: !177)
!177 = !{!60, !148, !178, !178, !75}
!178 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !75, size: 64, align: 64)
!179 = !DIDerivedType(tag: DW_TAG_member, name: "update", scope: !145, file: !142, line: 152, baseType: !180, size: 64, align: 64, offset: 448)
!180 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !181, size: 64, align: 64)
!181 = !DISubroutineType(types: !182)
!182 = !{!60, !148, !116, !183, !183}
!183 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !184, size: 64, align: 64)
!184 = !DIDerivedType(tag: DW_TAG_const_type, baseType: !79)
!185 = !{i32 2, !"Dwarf Version", i32 4}
!186 = !{i32 2, !"Debug Info Version", i32 3}
!187 = !{!"clang version 3.8.0 (tags/RELEASE_380/final)"}
!188 = !DILocalVariable(name: "uncompressed_size", arg: 1, scope: !53, file: !1, line: 57, type: !49)
!189 = !DIExpression()
!190 = !DILocation(line: 57, column: 32, scope: !53)
!191 = !DILocalVariable(name: "lzma2_size", scope: !53, file: !1, line: 64, type: !73)
!192 = !DILocation(line: 64, column: 11, scope: !53)
!193 = !DILocation(line: 64, column: 36, scope: !53)
!194 = !DILocation(line: 64, column: 24, scope: !53)
!195 = !DILocation(line: 65, column: 6, scope: !196)
!196 = distinct !DILexicalBlock(scope: !53, file: !1, line: 65, column: 6)
!197 = !DILocation(line: 65, column: 17, scope: !196)
!198 = !DILocation(line: 65, column: 6, scope: !53)
!199 = !DILocation(line: 66, column: 3, scope: !196)
!200 = !DILocation(line: 69, column: 16, scope: !53)
!201 = !DILocation(line: 69, column: 27, scope: !53)
!202 = !DILocation(line: 69, column: 32, scope: !53)
!203 = !DILocation(line: 69, column: 13, scope: !53)
!204 = !DILocation(line: 79, column: 25, scope: !53)
!205 = !DILocation(line: 79, column: 23, scope: !53)
!206 = !DILocation(line: 79, column: 2, scope: !53)
!207 = !DILocation(line: 80, column: 1, scope: !53)
!208 = !DILocalVariable(name: "uncompressed_size", arg: 1, scope: !133, file: !1, line: 32, type: !73)
!209 = !DILocation(line: 32, column: 22, scope: !133)
!210 = !DILocalVariable(name: "overhead", scope: !133, file: !1, line: 34, type: !73)
!211 = !DILocation(line: 34, column: 11, scope: !133)
!212 = !DILocation(line: 37, column: 6, scope: !213)
!213 = distinct !DILexicalBlock(scope: !133, file: !1, line: 37, column: 6)
!214 = !DILocation(line: 37, column: 24, scope: !213)
!215 = !DILocation(line: 37, column: 6, scope: !133)
!216 = !DILocation(line: 38, column: 3, scope: !213)
!217 = !DILocation(line: 44, column: 15, scope: !133)
!218 = !DILocation(line: 44, column: 33, scope: !133)
!219 = !DILocation(line: 44, column: 51, scope: !133)
!220 = !DILocation(line: 45, column: 5, scope: !133)
!221 = !DILocation(line: 46, column: 4, scope: !133)
!222 = !DILocation(line: 46, column: 32, scope: !133)
!223 = !DILocation(line: 44, column: 11, scope: !133)
!224 = !DILocation(line: 49, column: 28, scope: !225)
!225 = distinct !DILexicalBlock(scope: !133, file: !1, line: 49, column: 6)
!226 = !DILocation(line: 49, column: 26, scope: !225)
!227 = !DILocation(line: 49, column: 39, scope: !225)
!228 = !DILocation(line: 49, column: 37, scope: !225)
!229 = !DILocation(line: 49, column: 6, scope: !133)
!230 = !DILocation(line: 50, column: 3, scope: !225)
!231 = !DILocation(line: 52, column: 9, scope: !133)
!232 = !DILocation(line: 52, column: 29, scope: !133)
!233 = !DILocation(line: 52, column: 27, scope: !133)
!234 = !DILocation(line: 52, column: 2, scope: !133)
!235 = !DILocation(line: 53, column: 1, scope: !133)
!236 = !DILocalVariable(name: "block", arg: 1, scope: !57, file: !1, line: 231, type: !61)
!237 = !DILocation(line: 231, column: 38, scope: !57)
!238 = !DILocalVariable(name: "allocator", arg: 2, scope: !57, file: !1, line: 231, type: !116)
!239 = !DILocation(line: 231, column: 61, scope: !57)
!240 = !DILocalVariable(name: "in", arg: 3, scope: !57, file: !1, line: 232, type: !129)
!241 = !DILocation(line: 232, column: 18, scope: !57)
!242 = !DILocalVariable(name: "in_size", arg: 4, scope: !57, file: !1, line: 232, type: !49)
!243 = !DILocation(line: 232, column: 29, scope: !57)
!244 = !DILocalVariable(name: "out", arg: 5, scope: !57, file: !1, line: 233, type: !131)
!245 = !DILocation(line: 233, column: 12, scope: !57)
!246 = !DILocalVariable(name: "out_pos", arg: 6, scope: !57, file: !1, line: 233, type: !132)
!247 = !DILocation(line: 233, column: 25, scope: !57)
!248 = !DILocalVariable(name: "out_size", arg: 7, scope: !57, file: !1, line: 233, type: !49)
!249 = !DILocation(line: 233, column: 41, scope: !57)
!250 = !DILocalVariable(name: "check_size", scope: !57, file: !1, line: 235, type: !49)
!251 = !DILocation(line: 235, column: 9, scope: !57)
!252 = !DILocalVariable(name: "ret", scope: !57, file: !1, line: 236, type: !60)
!253 = !DILocation(line: 236, column: 11, scope: !57)
!254 = !DILocalVariable(name: "i", scope: !57, file: !1, line: 237, type: !49)
!255 = !DILocation(line: 237, column: 9, scope: !57)
!256 = !DILocation(line: 240, column: 6, scope: !257)
!257 = distinct !DILexicalBlock(scope: !57, file: !1, line: 240, column: 6)
!258 = !DILocation(line: 240, column: 12, scope: !257)
!259 = !DILocation(line: 240, column: 20, scope: !257)
!260 = !DILocation(line: 240, column: 24, scope: !261)
!261 = !DILexicalBlockFile(scope: !257, file: !1, discriminator: 1)
!262 = !DILocation(line: 240, column: 27, scope: !261)
!263 = !DILocation(line: 240, column: 35, scope: !261)
!264 = !DILocation(line: 240, column: 38, scope: !265)
!265 = !DILexicalBlockFile(scope: !257, file: !1, discriminator: 2)
!266 = !DILocation(line: 240, column: 46, scope: !265)
!267 = !DILocation(line: 240, column: 52, scope: !265)
!268 = !DILocation(line: 240, column: 55, scope: !269)
!269 = !DILexicalBlockFile(scope: !257, file: !1, discriminator: 3)
!270 = !DILocation(line: 240, column: 59, scope: !269)
!271 = !DILocation(line: 241, column: 4, scope: !257)
!272 = !DILocation(line: 241, column: 7, scope: !261)
!273 = !DILocation(line: 241, column: 15, scope: !261)
!274 = !DILocation(line: 241, column: 23, scope: !261)
!275 = !DILocation(line: 241, column: 27, scope: !265)
!276 = !DILocation(line: 241, column: 26, scope: !265)
!277 = !DILocation(line: 241, column: 37, scope: !265)
!278 = !DILocation(line: 241, column: 35, scope: !265)
!279 = !DILocation(line: 240, column: 6, scope: !280)
!280 = !DILexicalBlockFile(scope: !57, file: !1, discriminator: 4)
!281 = !DILocation(line: 242, column: 3, scope: !257)
!282 = !DILocation(line: 246, column: 6, scope: !283)
!283 = distinct !DILexicalBlock(scope: !57, file: !1, line: 246, column: 6)
!284 = !DILocation(line: 246, column: 13, scope: !283)
!285 = !DILocation(line: 246, column: 21, scope: !283)
!286 = !DILocation(line: 246, column: 6, scope: !57)
!287 = !DILocation(line: 247, column: 3, scope: !283)
!288 = !DILocation(line: 249, column: 21, scope: !289)
!289 = distinct !DILexicalBlock(scope: !57, file: !1, line: 249, column: 6)
!290 = !DILocation(line: 249, column: 28, scope: !289)
!291 = !DILocation(line: 249, column: 35, scope: !289)
!292 = !DILocation(line: 250, column: 4, scope: !289)
!293 = !DILocation(line: 250, column: 7, scope: !294)
!294 = !DILexicalBlockFile(scope: !289, file: !1, discriminator: 1)
!295 = !DILocation(line: 250, column: 14, scope: !294)
!296 = !DILocation(line: 250, column: 22, scope: !294)
!297 = !DILocation(line: 249, column: 6, scope: !298)
!298 = !DILexicalBlockFile(scope: !57, file: !1, discriminator: 1)
!299 = !DILocation(line: 251, column: 3, scope: !289)
!300 = !DILocation(line: 253, column: 31, scope: !301)
!301 = distinct !DILexicalBlock(scope: !57, file: !1, line: 253, column: 6)
!302 = !DILocation(line: 253, column: 38, scope: !301)
!303 = !DILocation(line: 253, column: 7, scope: !301)
!304 = !DILocation(line: 253, column: 6, scope: !57)
!305 = !DILocation(line: 254, column: 3, scope: !301)
!306 = !DILocation(line: 259, column: 15, scope: !57)
!307 = !DILocation(line: 259, column: 27, scope: !57)
!308 = !DILocation(line: 259, column: 26, scope: !57)
!309 = !DILocation(line: 259, column: 24, scope: !57)
!310 = !DILocation(line: 259, column: 36, scope: !57)
!311 = !DILocation(line: 259, column: 11, scope: !57)
!312 = !DILocation(line: 262, column: 31, scope: !57)
!313 = !DILocation(line: 262, column: 38, scope: !57)
!314 = !DILocation(line: 262, column: 15, scope: !57)
!315 = !DILocation(line: 262, column: 13, scope: !57)
!316 = !DILocation(line: 263, column: 2, scope: !57)
!317 = !DILocation(line: 263, column: 2, scope: !298)
!318 = !DILocation(line: 263, column: 2, scope: !319)
!319 = !DILexicalBlockFile(scope: !57, file: !1, discriminator: 2)
!320 = !DILocation(line: 263, column: 2, scope: !321)
!321 = !DILexicalBlockFile(scope: !57, file: !1, discriminator: 3)
!322 = !DILocation(line: 266, column: 6, scope: !323)
!323 = distinct !DILexicalBlock(scope: !57, file: !1, line: 266, column: 6)
!324 = !DILocation(line: 266, column: 18, scope: !323)
!325 = !DILocation(line: 266, column: 17, scope: !323)
!326 = !DILocation(line: 266, column: 15, scope: !323)
!327 = !DILocation(line: 266, column: 29, scope: !323)
!328 = !DILocation(line: 266, column: 26, scope: !323)
!329 = !DILocation(line: 266, column: 6, scope: !57)
!330 = !DILocation(line: 267, column: 3, scope: !323)
!331 = !DILocation(line: 269, column: 14, scope: !57)
!332 = !DILocation(line: 269, column: 11, scope: !57)
!333 = !DILocation(line: 272, column: 28, scope: !57)
!334 = !DILocation(line: 272, column: 35, scope: !57)
!335 = !DILocation(line: 273, column: 4, scope: !57)
!336 = !DILocation(line: 273, column: 8, scope: !57)
!337 = !DILocation(line: 273, column: 17, scope: !57)
!338 = !DILocation(line: 273, column: 22, scope: !57)
!339 = !DILocation(line: 273, column: 31, scope: !57)
!340 = !DILocation(line: 272, column: 8, scope: !57)
!341 = !DILocation(line: 272, column: 6, scope: !57)
!342 = !DILocation(line: 274, column: 6, scope: !343)
!343 = distinct !DILexicalBlock(scope: !57, file: !1, line: 274, column: 6)
!344 = !DILocation(line: 274, column: 10, scope: !343)
!345 = !DILocation(line: 274, column: 6, scope: !57)
!346 = !DILocation(line: 277, column: 7, scope: !347)
!347 = distinct !DILexicalBlock(scope: !348, file: !1, line: 277, column: 7)
!348 = distinct !DILexicalBlock(scope: !343, file: !1, line: 274, column: 22)
!349 = !DILocation(line: 277, column: 11, scope: !347)
!350 = !DILocation(line: 277, column: 7, scope: !348)
!351 = !DILocation(line: 278, column: 11, scope: !347)
!352 = !DILocation(line: 278, column: 4, scope: !347)
!353 = !DILocation(line: 285, column: 3, scope: !348)
!354 = !DILocalVariable(name: "ret_", scope: !355, file: !1, line: 285, type: !356)
!355 = distinct !DILexicalBlock(scope: !348, file: !1, line: 285, column: 3)
!356 = !DIDerivedType(tag: DW_TAG_const_type, baseType: !60)
!357 = !DILocation(line: 285, column: 3, scope: !355)
!358 = !DILocation(line: 285, column: 3, scope: !359)
!359 = !DILexicalBlockFile(scope: !355, file: !1, discriminator: 1)
!360 = !DILocation(line: 285, column: 3, scope: !361)
!361 = !DILexicalBlockFile(scope: !362, file: !1, discriminator: 2)
!362 = distinct !DILexicalBlock(scope: !355, file: !1, line: 285, column: 3)
!363 = !DILocation(line: 285, column: 3, scope: !364)
!364 = !DILexicalBlockFile(scope: !355, file: !1, discriminator: 3)
!365 = !DILocation(line: 287, column: 2, scope: !348)
!366 = !DILocation(line: 289, column: 2, scope: !57)
!367 = !DILocation(line: 289, column: 2, scope: !298)
!368 = !DILocation(line: 289, column: 2, scope: !319)
!369 = !DILocation(line: 289, column: 2, scope: !321)
!370 = !DILocation(line: 294, column: 20, scope: !371)
!371 = distinct !DILexicalBlock(scope: !57, file: !1, line: 294, column: 2)
!372 = !DILocation(line: 294, column: 27, scope: !371)
!373 = !DILocation(line: 294, column: 9, scope: !371)
!374 = !DILocation(line: 294, column: 7, scope: !371)
!375 = !DILocation(line: 294, column: 45, scope: !376)
!376 = !DILexicalBlockFile(scope: !377, file: !1, discriminator: 1)
!377 = distinct !DILexicalBlock(scope: !371, file: !1, line: 294, column: 2)
!378 = !DILocation(line: 294, column: 47, scope: !376)
!379 = !DILocation(line: 294, column: 2, scope: !376)
!380 = !DILocation(line: 295, column: 3, scope: !381)
!381 = distinct !DILexicalBlock(scope: !377, file: !1, line: 294, column: 57)
!382 = !DILocation(line: 295, column: 3, scope: !383)
!383 = !DILexicalBlockFile(scope: !381, file: !1, discriminator: 1)
!384 = !DILocation(line: 295, column: 3, scope: !385)
!385 = !DILexicalBlockFile(scope: !381, file: !1, discriminator: 2)
!386 = !DILocation(line: 295, column: 3, scope: !387)
!387 = !DILexicalBlockFile(scope: !381, file: !1, discriminator: 3)
!388 = !DILocation(line: 296, column: 9, scope: !381)
!389 = !DILocation(line: 296, column: 17, scope: !381)
!390 = !DILocation(line: 296, column: 3, scope: !381)
!391 = !DILocation(line: 296, column: 21, scope: !381)
!392 = !DILocation(line: 297, column: 2, scope: !381)
!393 = !DILocation(line: 294, column: 52, scope: !394)
!394 = !DILexicalBlockFile(scope: !377, file: !1, discriminator: 2)
!395 = !DILocation(line: 294, column: 2, scope: !394)
!396 = !DILocation(line: 300, column: 6, scope: !397)
!397 = distinct !DILexicalBlock(scope: !57, file: !1, line: 300, column: 6)
!398 = !DILocation(line: 300, column: 17, scope: !397)
!399 = !DILocation(line: 300, column: 6, scope: !57)
!400 = !DILocalVariable(name: "check", scope: !401, file: !1, line: 304, type: !402)
!401 = distinct !DILexicalBlock(scope: !397, file: !1, line: 300, column: 22)
!402 = !DIDerivedType(tag: DW_TAG_typedef, name: "lzma_check_state", file: !403, line: 56, baseType: !404)
!403 = !DIFile(filename: "/data/download/cmake/cmake-master/Utilities/cmliblzma/liblzma/check/check.h", directory: "/data/download/cmake/cmake-master/Utilities/cmliblzma")
!404 = !DICompositeType(tag: DW_TAG_structure_type, file: !403, line: 34, size: 832, align: 64, elements: !405)
!405 = !{!406, !418}
!406 = !DIDerivedType(tag: DW_TAG_member, name: "buffer", scope: !404, file: !403, line: 40, baseType: !407, size: 512, align: 64)
!407 = !DICompositeType(tag: DW_TAG_union_type, scope: !404, file: !403, line: 36, size: 512, align: 64, elements: !408)
!408 = !{!409, !410, !414}
!409 = !DIDerivedType(tag: DW_TAG_member, name: "u8", scope: !407, file: !403, line: 37, baseType: !86, size: 512, align: 8)
!410 = !DIDerivedType(tag: DW_TAG_member, name: "u32", scope: !407, file: !403, line: 38, baseType: !411, size: 512, align: 32)
!411 = !DICompositeType(tag: DW_TAG_array_type, baseType: !67, size: 512, align: 32, elements: !412)
!412 = !{!413}
!413 = !DISubrange(count: 16)
!414 = !DIDerivedType(tag: DW_TAG_member, name: "u64", scope: !407, file: !403, line: 39, baseType: !415, size: 512, align: 64)
!415 = !DICompositeType(tag: DW_TAG_array_type, baseType: !75, size: 512, align: 64, elements: !416)
!416 = !{!417}
!417 = !DISubrange(count: 8)
!418 = !DIDerivedType(tag: DW_TAG_member, name: "state", scope: !404, file: !403, line: 54, baseType: !419, size: 320, align: 64, offset: 512)
!419 = !DICompositeType(tag: DW_TAG_union_type, scope: !404, file: !403, line: 43, size: 320, align: 64, elements: !420)
!420 = !{!421, !422, !423}
!421 = !DIDerivedType(tag: DW_TAG_member, name: "crc32", scope: !419, file: !403, line: 44, baseType: !67, size: 32, align: 32)
!422 = !DIDerivedType(tag: DW_TAG_member, name: "crc64", scope: !419, file: !403, line: 45, baseType: !75, size: 64, align: 64)
!423 = !DIDerivedType(tag: DW_TAG_member, name: "sha256", scope: !419, file: !403, line: 53, baseType: !424, size: 320, align: 64)
!424 = !DICompositeType(tag: DW_TAG_structure_type, scope: !419, file: !403, line: 47, size: 320, align: 64, elements: !425)
!425 = !{!426, !428}
!426 = !DIDerivedType(tag: DW_TAG_member, name: "state", scope: !424, file: !403, line: 49, baseType: !427, size: 256, align: 32)
!427 = !DICompositeType(tag: DW_TAG_array_type, baseType: !67, size: 256, align: 32, elements: !416)
!428 = !DIDerivedType(tag: DW_TAG_member, name: "size", scope: !424, file: !403, line: 52, baseType: !75, size: 64, align: 64, offset: 256)
!429 = !DILocation(line: 304, column: 20, scope: !401)
!430 = !DILocation(line: 305, column: 27, scope: !401)
!431 = !DILocation(line: 305, column: 34, scope: !401)
!432 = !DILocation(line: 305, column: 3, scope: !401)
!433 = !DILocation(line: 306, column: 29, scope: !401)
!434 = !DILocation(line: 306, column: 36, scope: !401)
!435 = !DILocation(line: 306, column: 43, scope: !401)
!436 = !DILocation(line: 306, column: 47, scope: !401)
!437 = !DILocation(line: 306, column: 3, scope: !401)
!438 = !DILocation(line: 307, column: 29, scope: !401)
!439 = !DILocation(line: 307, column: 36, scope: !401)
!440 = !DILocation(line: 307, column: 3, scope: !401)
!441 = !DILocation(line: 309, column: 10, scope: !401)
!442 = !DILocation(line: 309, column: 17, scope: !401)
!443 = !DILocation(line: 309, column: 3, scope: !401)
!444 = !DILocation(line: 309, column: 34, scope: !401)
!445 = !DILocation(line: 309, column: 41, scope: !401)
!446 = !DILocation(line: 309, column: 45, scope: !401)
!447 = !DILocation(line: 310, column: 10, scope: !401)
!448 = !DILocation(line: 310, column: 17, scope: !401)
!449 = !DILocation(line: 310, column: 16, scope: !401)
!450 = !DILocation(line: 310, column: 14, scope: !401)
!451 = !DILocation(line: 310, column: 32, scope: !401)
!452 = !DILocation(line: 310, column: 39, scope: !401)
!453 = !DILocation(line: 310, column: 3, scope: !401)
!454 = !DILocation(line: 310, column: 43, scope: !401)
!455 = !DILocation(line: 311, column: 15, scope: !401)
!456 = !DILocation(line: 311, column: 4, scope: !401)
!457 = !DILocation(line: 311, column: 12, scope: !401)
!458 = !DILocation(line: 312, column: 2, scope: !401)
!459 = !DILocation(line: 314, column: 2, scope: !57)
!460 = !DILocation(line: 315, column: 1, scope: !57)
!461 = !DILocalVariable(name: "block", arg: 1, scope: !136, file: !1, line: 166, type: !61)
!462 = !DILocation(line: 166, column: 33, scope: !136)
!463 = !DILocalVariable(name: "allocator", arg: 2, scope: !136, file: !1, line: 166, type: !116)
!464 = !DILocation(line: 166, column: 56, scope: !136)
!465 = !DILocalVariable(name: "in", arg: 3, scope: !136, file: !1, line: 167, type: !129)
!466 = !DILocation(line: 167, column: 18, scope: !136)
!467 = !DILocalVariable(name: "in_size", arg: 4, scope: !136, file: !1, line: 167, type: !49)
!468 = !DILocation(line: 167, column: 29, scope: !136)
!469 = !DILocalVariable(name: "out", arg: 5, scope: !136, file: !1, line: 168, type: !131)
!470 = !DILocation(line: 168, column: 12, scope: !136)
!471 = !DILocalVariable(name: "out_pos", arg: 6, scope: !136, file: !1, line: 168, type: !132)
!472 = !DILocation(line: 168, column: 25, scope: !136)
!473 = !DILocalVariable(name: "out_size", arg: 7, scope: !136, file: !1, line: 168, type: !49)
!474 = !DILocation(line: 168, column: 41, scope: !136)
!475 = !DILocalVariable(name: "out_start", scope: !136, file: !1, line: 170, type: !49)
!476 = !DILocation(line: 170, column: 9, scope: !136)
!477 = !DILocalVariable(name: "raw_encoder", scope: !136, file: !1, line: 171, type: !144)
!478 = !DILocation(line: 171, column: 18, scope: !136)
!479 = !DILocation(line: 171, column: 32, scope: !136)
!480 = !DILocalVariable(name: "ret", scope: !136, file: !1, line: 172, type: !60)
!481 = !DILocation(line: 172, column: 11, scope: !136)
!482 = !DILocation(line: 175, column: 39, scope: !136)
!483 = !DILocation(line: 175, column: 27, scope: !136)
!484 = !DILocation(line: 175, column: 2, scope: !136)
!485 = !DILocation(line: 175, column: 9, scope: !136)
!486 = !DILocation(line: 175, column: 25, scope: !136)
!487 = !DILocation(line: 176, column: 6, scope: !488)
!488 = distinct !DILexicalBlock(scope: !136, file: !1, line: 176, column: 6)
!489 = !DILocation(line: 176, column: 13, scope: !488)
!490 = !DILocation(line: 176, column: 29, scope: !488)
!491 = !DILocation(line: 176, column: 6, scope: !136)
!492 = !DILocation(line: 177, column: 3, scope: !488)
!493 = !DILocation(line: 179, column: 29, scope: !136)
!494 = !DILocation(line: 179, column: 2, scope: !136)
!495 = !DILocation(line: 179, column: 9, scope: !136)
!496 = !DILocation(line: 179, column: 27, scope: !136)
!497 = !DILocation(line: 180, column: 2, scope: !136)
!498 = !DILocalVariable(name: "ret_", scope: !499, file: !1, line: 180, type: !356)
!499 = distinct !DILexicalBlock(scope: !136, file: !1, line: 180, column: 2)
!500 = !DILocation(line: 180, column: 2, scope: !499)
!501 = !DILocation(line: 180, column: 2, scope: !502)
!502 = !DILexicalBlockFile(scope: !499, file: !1, discriminator: 1)
!503 = !DILocation(line: 180, column: 2, scope: !504)
!504 = !DILexicalBlockFile(scope: !505, file: !1, discriminator: 2)
!505 = distinct !DILexicalBlock(scope: !499, file: !1, line: 180, column: 2)
!506 = !DILocation(line: 180, column: 2, scope: !507)
!507 = !DILexicalBlockFile(scope: !499, file: !1, discriminator: 3)
!508 = !DILocation(line: 183, column: 6, scope: !509)
!509 = distinct !DILexicalBlock(scope: !136, file: !1, line: 183, column: 6)
!510 = !DILocation(line: 183, column: 18, scope: !509)
!511 = !DILocation(line: 183, column: 17, scope: !509)
!512 = !DILocation(line: 183, column: 15, scope: !509)
!513 = !DILocation(line: 183, column: 29, scope: !509)
!514 = !DILocation(line: 183, column: 36, scope: !509)
!515 = !DILocation(line: 183, column: 26, scope: !509)
!516 = !DILocation(line: 183, column: 6, scope: !136)
!517 = !DILocation(line: 184, column: 3, scope: !509)
!518 = !DILocation(line: 186, column: 15, scope: !136)
!519 = !DILocation(line: 186, column: 14, scope: !136)
!520 = !DILocation(line: 186, column: 12, scope: !136)
!521 = !DILocation(line: 187, column: 14, scope: !136)
!522 = !DILocation(line: 187, column: 21, scope: !136)
!523 = !DILocation(line: 187, column: 3, scope: !136)
!524 = !DILocation(line: 187, column: 11, scope: !136)
!525 = !DILocation(line: 191, column: 6, scope: !526)
!526 = distinct !DILexicalBlock(scope: !136, file: !1, line: 191, column: 6)
!527 = !DILocation(line: 191, column: 18, scope: !526)
!528 = !DILocation(line: 191, column: 17, scope: !526)
!529 = !DILocation(line: 191, column: 15, scope: !526)
!530 = !DILocation(line: 191, column: 28, scope: !526)
!531 = !DILocation(line: 191, column: 35, scope: !526)
!532 = !DILocation(line: 191, column: 26, scope: !526)
!533 = !DILocation(line: 191, column: 6, scope: !136)
!534 = !DILocation(line: 192, column: 15, scope: !526)
!535 = !DILocation(line: 192, column: 14, scope: !526)
!536 = !DILocation(line: 192, column: 25, scope: !526)
!537 = !DILocation(line: 192, column: 32, scope: !526)
!538 = !DILocation(line: 192, column: 23, scope: !526)
!539 = !DILocation(line: 192, column: 12, scope: !526)
!540 = !DILocation(line: 192, column: 3, scope: !526)
!541 = !DILocation(line: 197, column: 18, scope: !136)
!542 = !DILocation(line: 197, column: 29, scope: !136)
!543 = !DILocation(line: 197, column: 36, scope: !136)
!544 = !DILocation(line: 196, column: 8, scope: !136)
!545 = !DILocation(line: 196, column: 6, scope: !136)
!546 = !DILocation(line: 199, column: 6, scope: !547)
!547 = distinct !DILexicalBlock(scope: !136, file: !1, line: 199, column: 6)
!548 = !DILocation(line: 199, column: 10, scope: !547)
!549 = !DILocation(line: 199, column: 6, scope: !136)
!550 = !DILocalVariable(name: "in_pos", scope: !551, file: !1, line: 200, type: !49)
!551 = distinct !DILexicalBlock(scope: !547, file: !1, line: 199, column: 22)
!552 = !DILocation(line: 200, column: 10, scope: !551)
!553 = !DILocation(line: 201, column: 21, scope: !551)
!554 = !DILocation(line: 201, column: 38, scope: !551)
!555 = !DILocation(line: 201, column: 45, scope: !551)
!556 = !DILocation(line: 202, column: 5, scope: !551)
!557 = !DILocation(line: 202, column: 18, scope: !551)
!558 = !DILocation(line: 202, column: 27, scope: !551)
!559 = !DILocation(line: 202, column: 32, scope: !551)
!560 = !DILocation(line: 202, column: 41, scope: !551)
!561 = !DILocation(line: 201, column: 9, scope: !551)
!562 = !DILocation(line: 201, column: 7, scope: !551)
!563 = !DILocation(line: 204, column: 2, scope: !551)
!564 = !DILocation(line: 207, column: 30, scope: !136)
!565 = !DILocation(line: 207, column: 2, scope: !136)
!566 = !DILocation(line: 209, column: 6, scope: !567)
!567 = distinct !DILexicalBlock(scope: !136, file: !1, line: 209, column: 6)
!568 = !DILocation(line: 209, column: 10, scope: !567)
!569 = !DILocation(line: 209, column: 6, scope: !136)
!570 = !DILocation(line: 212, column: 8, scope: !571)
!571 = distinct !DILexicalBlock(scope: !567, file: !1, line: 209, column: 30)
!572 = !DILocation(line: 212, column: 7, scope: !571)
!573 = !DILocation(line: 212, column: 19, scope: !571)
!574 = !DILocation(line: 212, column: 31, scope: !571)
!575 = !DILocation(line: 212, column: 38, scope: !571)
!576 = !DILocation(line: 212, column: 29, scope: !571)
!577 = !DILocation(line: 212, column: 16, scope: !571)
!578 = !DILocation(line: 211, column: 3, scope: !571)
!579 = !DILocation(line: 211, column: 10, scope: !571)
!580 = !DILocation(line: 212, column: 5, scope: !571)
!581 = !DILocation(line: 213, column: 34, scope: !571)
!582 = !DILocation(line: 213, column: 41, scope: !571)
!583 = !DILocation(line: 213, column: 47, scope: !571)
!584 = !DILocation(line: 213, column: 45, scope: !571)
!585 = !DILocation(line: 213, column: 9, scope: !571)
!586 = !DILocation(line: 213, column: 7, scope: !571)
!587 = !DILocation(line: 214, column: 7, scope: !588)
!588 = distinct !DILexicalBlock(scope: !571, file: !1, line: 214, column: 7)
!589 = !DILocation(line: 214, column: 11, scope: !588)
!590 = !DILocation(line: 214, column: 7, scope: !571)
!591 = !DILocation(line: 215, column: 8, scope: !588)
!592 = !DILocation(line: 215, column: 4, scope: !588)
!593 = !DILocation(line: 217, column: 2, scope: !571)
!594 = !DILocation(line: 217, column: 13, scope: !595)
!595 = !DILexicalBlockFile(scope: !596, file: !1, discriminator: 1)
!596 = distinct !DILexicalBlock(scope: !567, file: !1, line: 217, column: 13)
!597 = !DILocation(line: 217, column: 17, scope: !595)
!598 = !DILocation(line: 219, column: 7, scope: !599)
!599 = distinct !DILexicalBlock(scope: !596, file: !1, line: 217, column: 29)
!600 = !DILocation(line: 220, column: 2, scope: !599)
!601 = !DILocation(line: 223, column: 6, scope: !602)
!602 = distinct !DILexicalBlock(scope: !136, file: !1, line: 223, column: 6)
!603 = !DILocation(line: 223, column: 10, scope: !602)
!604 = !DILocation(line: 223, column: 6, scope: !136)
!605 = !DILocation(line: 224, column: 14, scope: !602)
!606 = !DILocation(line: 224, column: 4, scope: !602)
!607 = !DILocation(line: 224, column: 12, scope: !602)
!608 = !DILocation(line: 224, column: 3, scope: !602)
!609 = !DILocation(line: 226, column: 9, scope: !136)
!610 = !DILocation(line: 226, column: 2, scope: !136)
!611 = !DILocation(line: 227, column: 1, scope: !136)
!612 = !DILocalVariable(name: "block", arg: 1, scope: !137, file: !1, line: 84, type: !61)
!613 = !DILocation(line: 84, column: 39, scope: !137)
!614 = !DILocalVariable(name: "in", arg: 2, scope: !137, file: !1, line: 84, type: !129)
!615 = !DILocation(line: 84, column: 61, scope: !137)
!616 = !DILocalVariable(name: "in_size", arg: 3, scope: !137, file: !1, line: 84, type: !49)
!617 = !DILocation(line: 84, column: 72, scope: !137)
!618 = !DILocalVariable(name: "out", arg: 4, scope: !137, file: !1, line: 85, type: !131)
!619 = !DILocation(line: 85, column: 12, scope: !137)
!620 = !DILocalVariable(name: "out_pos", arg: 5, scope: !137, file: !1, line: 85, type: !132)
!621 = !DILocation(line: 85, column: 25, scope: !137)
!622 = !DILocalVariable(name: "out_size", arg: 6, scope: !137, file: !1, line: 85, type: !49)
!623 = !DILocation(line: 85, column: 41, scope: !137)
!624 = !DILocalVariable(name: "in_pos", scope: !137, file: !1, line: 87, type: !49)
!625 = !DILocation(line: 87, column: 9, scope: !137)
!626 = !DILocalVariable(name: "control", scope: !137, file: !1, line: 88, type: !87)
!627 = !DILocation(line: 88, column: 10, scope: !137)
!628 = !DILocalVariable(name: "filters_orig", scope: !137, file: !1, line: 89, type: !78)
!629 = !DILocation(line: 89, column: 15, scope: !137)
!630 = !DILocalVariable(name: "lzma2", scope: !137, file: !1, line: 97, type: !631)
!631 = !DIDerivedType(tag: DW_TAG_typedef, name: "lzma_options_lzma", file: !35, line: 399, baseType: !632)
!632 = !DICompositeType(tag: DW_TAG_structure_type, file: !35, line: 185, size: 896, align: 64, elements: !633)
!633 = !{!634, !635, !636, !637, !638, !639, !640, !642, !643, !645, !646, !647, !648, !649, !650, !651, !652, !653, !654, !655, !656, !657, !658, !659}
!634 = !DIDerivedType(tag: DW_TAG_member, name: "dict_size", scope: !632, file: !35, line: 217, baseType: !67, size: 32, align: 32)
!635 = !DIDerivedType(tag: DW_TAG_member, name: "preset_dict", scope: !632, file: !35, line: 240, baseType: !129, size: 64, align: 64, offset: 64)
!636 = !DIDerivedType(tag: DW_TAG_member, name: "preset_dict_size", scope: !632, file: !35, line: 254, baseType: !67, size: 32, align: 32, offset: 128)
!637 = !DIDerivedType(tag: DW_TAG_member, name: "lc", scope: !632, file: !35, line: 281, baseType: !67, size: 32, align: 32, offset: 160)
!638 = !DIDerivedType(tag: DW_TAG_member, name: "lp", scope: !632, file: !35, line: 293, baseType: !67, size: 32, align: 32, offset: 192)
!639 = !DIDerivedType(tag: DW_TAG_member, name: "pb", scope: !632, file: !35, line: 316, baseType: !67, size: 32, align: 32, offset: 224)
!640 = !DIDerivedType(tag: DW_TAG_member, name: "mode", scope: !632, file: !35, line: 322, baseType: !641, size: 32, align: 32, offset: 256)
!641 = !DIDerivedType(tag: DW_TAG_typedef, name: "lzma_mode", file: !35, line: 155, baseType: !34)
!642 = !DIDerivedType(tag: DW_TAG_member, name: "nice_len", scope: !632, file: !35, line: 342, baseType: !67, size: 32, align: 32, offset: 288)
!643 = !DIDerivedType(tag: DW_TAG_member, name: "mf", scope: !632, file: !35, line: 345, baseType: !644, size: 32, align: 32, offset: 320)
!644 = !DIDerivedType(tag: DW_TAG_typedef, name: "lzma_match_finder", file: !35, line: 111, baseType: !39)
!645 = !DIDerivedType(tag: DW_TAG_member, name: "depth", scope: !632, file: !35, line: 375, baseType: !67, size: 32, align: 32, offset: 352)
!646 = !DIDerivedType(tag: DW_TAG_member, name: "reserved_int1", scope: !632, file: !35, line: 384, baseType: !67, size: 32, align: 32, offset: 384)
!647 = !DIDerivedType(tag: DW_TAG_member, name: "reserved_int2", scope: !632, file: !35, line: 385, baseType: !67, size: 32, align: 32, offset: 416)
!648 = !DIDerivedType(tag: DW_TAG_member, name: "reserved_int3", scope: !632, file: !35, line: 386, baseType: !67, size: 32, align: 32, offset: 448)
!649 = !DIDerivedType(tag: DW_TAG_member, name: "reserved_int4", scope: !632, file: !35, line: 387, baseType: !67, size: 32, align: 32, offset: 480)
!650 = !DIDerivedType(tag: DW_TAG_member, name: "reserved_int5", scope: !632, file: !35, line: 388, baseType: !67, size: 32, align: 32, offset: 512)
!651 = !DIDerivedType(tag: DW_TAG_member, name: "reserved_int6", scope: !632, file: !35, line: 389, baseType: !67, size: 32, align: 32, offset: 544)
!652 = !DIDerivedType(tag: DW_TAG_member, name: "reserved_int7", scope: !632, file: !35, line: 390, baseType: !67, size: 32, align: 32, offset: 576)
!653 = !DIDerivedType(tag: DW_TAG_member, name: "reserved_int8", scope: !632, file: !35, line: 391, baseType: !67, size: 32, align: 32, offset: 608)
!654 = !DIDerivedType(tag: DW_TAG_member, name: "reserved_enum1", scope: !632, file: !35, line: 392, baseType: !103, size: 32, align: 32, offset: 640)
!655 = !DIDerivedType(tag: DW_TAG_member, name: "reserved_enum2", scope: !632, file: !35, line: 393, baseType: !103, size: 32, align: 32, offset: 672)
!656 = !DIDerivedType(tag: DW_TAG_member, name: "reserved_enum3", scope: !632, file: !35, line: 394, baseType: !103, size: 32, align: 32, offset: 704)
!657 = !DIDerivedType(tag: DW_TAG_member, name: "reserved_enum4", scope: !632, file: !35, line: 395, baseType: !103, size: 32, align: 32, offset: 736)
!658 = !DIDerivedType(tag: DW_TAG_member, name: "reserved_ptr1", scope: !632, file: !35, line: 396, baseType: !47, size: 64, align: 64, offset: 768)
!659 = !DIDerivedType(tag: DW_TAG_member, name: "reserved_ptr2", scope: !632, file: !35, line: 397, baseType: !47, size: 64, align: 64, offset: 832)
!660 = !DILocation(line: 97, column: 20, scope: !137)
!661 = !DILocalVariable(name: "filters", scope: !137, file: !1, line: 99, type: !662)
!662 = !DICompositeType(tag: DW_TAG_array_type, baseType: !79, size: 256, align: 64, elements: !663)
!663 = !{!664}
!664 = !DISubrange(count: 2)
!665 = !DILocation(line: 99, column: 14, scope: !137)
!666 = !DILocation(line: 100, column: 2, scope: !137)
!667 = !DILocation(line: 100, column: 13, scope: !137)
!668 = !DILocation(line: 100, column: 16, scope: !137)
!669 = !DILocation(line: 101, column: 23, scope: !137)
!670 = !DILocation(line: 101, column: 2, scope: !137)
!671 = !DILocation(line: 101, column: 13, scope: !137)
!672 = !DILocation(line: 101, column: 21, scope: !137)
!673 = !DILocation(line: 102, column: 2, scope: !137)
!674 = !DILocation(line: 102, column: 13, scope: !137)
!675 = !DILocation(line: 102, column: 16, scope: !137)
!676 = !DILocation(line: 106, column: 17, scope: !137)
!677 = !DILocation(line: 106, column: 24, scope: !137)
!678 = !DILocation(line: 106, column: 15, scope: !137)
!679 = !DILocation(line: 107, column: 19, scope: !137)
!680 = !DILocation(line: 107, column: 2, scope: !137)
!681 = !DILocation(line: 107, column: 9, scope: !137)
!682 = !DILocation(line: 107, column: 17, scope: !137)
!683 = !DILocation(line: 109, column: 29, scope: !684)
!684 = distinct !DILexicalBlock(scope: !137, file: !1, line: 109, column: 6)
!685 = !DILocation(line: 109, column: 6, scope: !684)
!686 = !DILocation(line: 109, column: 36, scope: !684)
!687 = !DILocation(line: 109, column: 6, scope: !137)
!688 = !DILocation(line: 110, column: 20, scope: !689)
!689 = distinct !DILexicalBlock(scope: !684, file: !1, line: 109, column: 48)
!690 = !DILocation(line: 110, column: 3, scope: !689)
!691 = !DILocation(line: 110, column: 10, scope: !689)
!692 = !DILocation(line: 110, column: 18, scope: !689)
!693 = !DILocation(line: 111, column: 3, scope: !689)
!694 = !DILocation(line: 119, column: 2, scope: !137)
!695 = !DILocation(line: 119, column: 2, scope: !696)
!696 = !DILexicalBlockFile(scope: !137, file: !1, discriminator: 1)
!697 = !DILocation(line: 119, column: 2, scope: !698)
!698 = !DILexicalBlockFile(scope: !137, file: !1, discriminator: 2)
!699 = !DILocation(line: 119, column: 2, scope: !700)
!700 = !DILexicalBlockFile(scope: !137, file: !1, discriminator: 3)
!701 = !DILocation(line: 120, column: 6, scope: !702)
!702 = distinct !DILexicalBlock(scope: !137, file: !1, line: 120, column: 6)
!703 = !DILocation(line: 120, column: 18, scope: !702)
!704 = !DILocation(line: 120, column: 17, scope: !702)
!705 = !DILocation(line: 120, column: 15, scope: !702)
!706 = !DILocation(line: 121, column: 6, scope: !702)
!707 = !DILocation(line: 121, column: 13, scope: !702)
!708 = !DILocation(line: 121, column: 27, scope: !702)
!709 = !DILocation(line: 121, column: 34, scope: !702)
!710 = !DILocation(line: 121, column: 25, scope: !702)
!711 = !DILocation(line: 121, column: 4, scope: !702)
!712 = !DILocation(line: 120, column: 6, scope: !137)
!713 = !DILocation(line: 122, column: 20, scope: !714)
!714 = distinct !DILexicalBlock(scope: !702, file: !1, line: 121, column: 51)
!715 = !DILocation(line: 122, column: 3, scope: !714)
!716 = !DILocation(line: 122, column: 10, scope: !714)
!717 = !DILocation(line: 122, column: 18, scope: !714)
!718 = !DILocation(line: 123, column: 3, scope: !714)
!719 = !DILocation(line: 126, column: 31, scope: !720)
!720 = distinct !DILexicalBlock(scope: !137, file: !1, line: 126, column: 6)
!721 = !DILocation(line: 126, column: 38, scope: !720)
!722 = !DILocation(line: 126, column: 45, scope: !720)
!723 = !DILocation(line: 126, column: 44, scope: !720)
!724 = !DILocation(line: 126, column: 42, scope: !720)
!725 = !DILocation(line: 126, column: 6, scope: !720)
!726 = !DILocation(line: 126, column: 54, scope: !720)
!727 = !DILocation(line: 126, column: 6, scope: !137)
!728 = !DILocation(line: 127, column: 20, scope: !729)
!729 = distinct !DILexicalBlock(scope: !720, file: !1, line: 126, column: 66)
!730 = !DILocation(line: 127, column: 3, scope: !729)
!731 = !DILocation(line: 127, column: 10, scope: !729)
!732 = !DILocation(line: 127, column: 18, scope: !729)
!733 = !DILocation(line: 128, column: 3, scope: !729)
!734 = !DILocation(line: 131, column: 19, scope: !137)
!735 = !DILocation(line: 131, column: 2, scope: !137)
!736 = !DILocation(line: 131, column: 9, scope: !137)
!737 = !DILocation(line: 131, column: 17, scope: !137)
!738 = !DILocation(line: 132, column: 14, scope: !137)
!739 = !DILocation(line: 132, column: 21, scope: !137)
!740 = !DILocation(line: 132, column: 3, scope: !137)
!741 = !DILocation(line: 132, column: 11, scope: !137)
!742 = !DILocation(line: 136, column: 2, scope: !137)
!743 = !DILocation(line: 136, column: 9, scope: !696)
!744 = !DILocation(line: 136, column: 18, scope: !696)
!745 = !DILocation(line: 136, column: 16, scope: !696)
!746 = !DILocation(line: 136, column: 2, scope: !696)
!747 = !DILocalVariable(name: "copy_size", scope: !748, file: !1, line: 137, type: !49)
!748 = distinct !DILexicalBlock(scope: !137, file: !1, line: 136, column: 27)
!749 = !DILocation(line: 137, column: 10, scope: !748)
!750 = !DILocation(line: 141, column: 23, scope: !748)
!751 = !DILocation(line: 141, column: 9, scope: !748)
!752 = !DILocation(line: 141, column: 17, scope: !748)
!753 = !DILocation(line: 141, column: 3, scope: !748)
!754 = !DILocation(line: 141, column: 21, scope: !748)
!755 = !DILocation(line: 142, column: 11, scope: !748)
!756 = !DILocation(line: 145, column: 15, scope: !748)
!757 = !DILocation(line: 145, column: 15, scope: !758)
!758 = !DILexicalBlockFile(scope: !748, file: !1, discriminator: 1)
!759 = !DILocation(line: 145, column: 15, scope: !760)
!760 = !DILexicalBlockFile(scope: !748, file: !1, discriminator: 2)
!761 = !DILocation(line: 145, column: 15, scope: !762)
!762 = !DILexicalBlockFile(scope: !748, file: !1, discriminator: 3)
!763 = !DILocation(line: 145, column: 13, scope: !762)
!764 = !DILocation(line: 146, column: 24, scope: !748)
!765 = !DILocation(line: 146, column: 34, scope: !748)
!766 = !DILocation(line: 146, column: 39, scope: !748)
!767 = !DILocation(line: 146, column: 23, scope: !748)
!768 = !DILocation(line: 146, column: 9, scope: !748)
!769 = !DILocation(line: 146, column: 17, scope: !748)
!770 = !DILocation(line: 146, column: 3, scope: !748)
!771 = !DILocation(line: 146, column: 21, scope: !748)
!772 = !DILocation(line: 147, column: 24, scope: !748)
!773 = !DILocation(line: 147, column: 34, scope: !748)
!774 = !DILocation(line: 147, column: 39, scope: !748)
!775 = !DILocation(line: 147, column: 23, scope: !748)
!776 = !DILocation(line: 147, column: 9, scope: !748)
!777 = !DILocation(line: 147, column: 17, scope: !748)
!778 = !DILocation(line: 147, column: 3, scope: !748)
!779 = !DILocation(line: 147, column: 21, scope: !748)
!780 = !DILocation(line: 150, column: 3, scope: !748)
!781 = !DILocation(line: 150, column: 3, scope: !758)
!782 = !DILocation(line: 150, column: 3, scope: !760)
!783 = !DILocation(line: 150, column: 3, scope: !762)
!784 = !DILocation(line: 151, column: 10, scope: !748)
!785 = !DILocation(line: 151, column: 17, scope: !748)
!786 = !DILocation(line: 151, column: 16, scope: !748)
!787 = !DILocation(line: 151, column: 14, scope: !748)
!788 = !DILocation(line: 151, column: 26, scope: !748)
!789 = !DILocation(line: 151, column: 31, scope: !748)
!790 = !DILocation(line: 151, column: 29, scope: !748)
!791 = !DILocation(line: 151, column: 39, scope: !748)
!792 = !DILocation(line: 151, column: 3, scope: !748)
!793 = !DILocation(line: 153, column: 13, scope: !748)
!794 = !DILocation(line: 153, column: 10, scope: !748)
!795 = !DILocation(line: 154, column: 15, scope: !748)
!796 = !DILocation(line: 154, column: 4, scope: !748)
!797 = !DILocation(line: 154, column: 12, scope: !748)
!798 = !DILocation(line: 136, column: 2, scope: !698)
!799 = !DILocation(line: 158, column: 8, scope: !137)
!800 = !DILocation(line: 158, column: 16, scope: !137)
!801 = !DILocation(line: 158, column: 2, scope: !137)
!802 = !DILocation(line: 158, column: 20, scope: !137)
!803 = !DILocation(line: 159, column: 2, scope: !137)
!804 = !DILocation(line: 159, column: 2, scope: !696)
!805 = !DILocation(line: 159, column: 2, scope: !698)
!806 = !DILocation(line: 159, column: 2, scope: !700)
!807 = !DILocation(line: 161, column: 2, scope: !137)
!808 = !DILocation(line: 162, column: 1, scope: !137)
