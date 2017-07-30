; ModuleID = '/data/download/cmake/cmake-master/Utilities/cmliblzma/liblzma/lz/lz_decoder.c'
target datalayout = "e-m:e-i64:64-f80:128-n8:16:32:64-S128"
target triple = "x86_64-unknown-linux-gnu"

%struct.lzma_lz_decoder = type { %struct.lzma_coder_s*, i32 (%struct.lzma_coder_s*, %struct.lzma_dict*, i8*, i64*, i64)*, void (%struct.lzma_coder_s*, i8*)*, void (%struct.lzma_coder_s*, i64)*, void (%struct.lzma_coder_s*, %struct.lzma_allocator*)* }
%struct.lzma_coder_s = type { %struct.lzma_dict, %struct.lzma_lz_decoder, %struct.lzma_next_coder_s, i8, i8, %struct.anon }
%struct.lzma_dict = type { i8*, i64, i64, i64, i64, i8 }
%struct.lzma_next_coder_s = type { %struct.lzma_coder_s*, i64, i64, i32 (%struct.lzma_coder_s*, %struct.lzma_allocator*, i8*, i64*, i64, i8*, i64*, i64, i32)*, void (%struct.lzma_coder_s*, %struct.lzma_allocator*)*, i32 (%struct.lzma_coder_s*)*, i32 (%struct.lzma_coder_s*, i64*, i64*, i64)*, i32 (%struct.lzma_coder_s*, %struct.lzma_allocator*, %struct.lzma_filter*, %struct.lzma_filter*)* }
%struct.lzma_allocator = type { i8* (i8*, i64, i64)*, void (i8*, i8*)*, i8* }
%struct.lzma_filter = type { i64, i8* }
%struct.anon = type { i64, i64, [4096 x i8] }
%struct.lzma_filter_info_s = type { i64, i32 (%struct.lzma_next_coder_s*, %struct.lzma_allocator*, %struct.lzma_filter_info_s*)*, i8* }
%struct.lzma_lz_options = type { i64, i8*, i64 }

@LZMA_LZ_DECODER_INIT = internal constant %struct.lzma_lz_decoder zeroinitializer, align 8
@LZMA_NEXT_CODER_INIT = internal constant %struct.lzma_next_coder_s { %struct.lzma_coder_s* null, i64 -1, i64 0, i32 (%struct.lzma_coder_s*, %struct.lzma_allocator*, i8*, i64*, i64, i8*, i64*, i64, i32)* null, void (%struct.lzma_coder_s*, %struct.lzma_allocator*)* null, i32 (%struct.lzma_coder_s*)* null, i32 (%struct.lzma_coder_s*, i64*, i64*, i64)* null, i32 (%struct.lzma_coder_s*, %struct.lzma_allocator*, %struct.lzma_filter*, %struct.lzma_filter*)* null }, align 8
@.str = private unnamed_addr constant [33 x i8] c"copy_size <= out_size - *out_pos\00", align 1
@.str.1 = private unnamed_addr constant [78 x i8] c"/data/download/cmake/cmake-master/Utilities/cmliblzma/liblzma/lz/lz_decoder.c\00", align 1
@__PRETTY_FUNCTION__.decode_buffer = private unnamed_addr constant [133 x i8] c"lzma_ret decode_buffer(lzma_coder *, const uint8_t *restrict, size_t *restrict, size_t, uint8_t *restrict, size_t *restrict, size_t)\00", align 1

; Function Attrs: nounwind uwtable
define i32 @lzma_lz_decoder_init(%struct.lzma_next_coder_s* %next, %struct.lzma_allocator* %allocator, %struct.lzma_filter_info_s* %filters, i32 (%struct.lzma_lz_decoder*, %struct.lzma_allocator*, i8*, %struct.lzma_lz_options*)* %lz_init) #0 !dbg !39 {
entry:
  %retval = alloca i32, align 4
  %next.addr = alloca %struct.lzma_next_coder_s*, align 8
  %allocator.addr = alloca %struct.lzma_allocator*, align 8
  %filters.addr = alloca %struct.lzma_filter_info_s*, align 8
  %lz_init.addr = alloca i32 (%struct.lzma_lz_decoder*, %struct.lzma_allocator*, i8*, %struct.lzma_lz_options*)*, align 8
  %lz_options = alloca %struct.lzma_lz_options, align 8
  %ret_ = alloca i32, align 4
  %copy_size = alloca i64, align 8
  %offset = alloca i64, align 8
  store %struct.lzma_next_coder_s* %next, %struct.lzma_next_coder_s** %next.addr, align 8
  call void @llvm.dbg.declare(metadata %struct.lzma_next_coder_s** %next.addr, metadata !206, metadata !207), !dbg !208
  store %struct.lzma_allocator* %allocator, %struct.lzma_allocator** %allocator.addr, align 8
  call void @llvm.dbg.declare(metadata %struct.lzma_allocator** %allocator.addr, metadata !209, metadata !207), !dbg !210
  store %struct.lzma_filter_info_s* %filters, %struct.lzma_filter_info_s** %filters.addr, align 8
  call void @llvm.dbg.declare(metadata %struct.lzma_filter_info_s** %filters.addr, metadata !211, metadata !207), !dbg !212
  store i32 (%struct.lzma_lz_decoder*, %struct.lzma_allocator*, i8*, %struct.lzma_lz_options*)* %lz_init, i32 (%struct.lzma_lz_decoder*, %struct.lzma_allocator*, i8*, %struct.lzma_lz_options*)** %lz_init.addr, align 8
  call void @llvm.dbg.declare(metadata i32 (%struct.lzma_lz_decoder*, %struct.lzma_allocator*, i8*, %struct.lzma_lz_options*)** %lz_init.addr, metadata !213, metadata !207), !dbg !214
  call void @llvm.dbg.declare(metadata %struct.lzma_lz_options* %lz_options, metadata !215, metadata !207), !dbg !216
  %0 = load %struct.lzma_next_coder_s*, %struct.lzma_next_coder_s** %next.addr, align 8, !dbg !217
  %coder = getelementptr inbounds %struct.lzma_next_coder_s, %struct.lzma_next_coder_s* %0, i32 0, i32 0, !dbg !219
  %1 = load %struct.lzma_coder_s*, %struct.lzma_coder_s** %coder, align 8, !dbg !219
  %cmp = icmp eq %struct.lzma_coder_s* %1, null, !dbg !220
  br i1 %cmp, label %if.then, label %if.end11, !dbg !221

if.then:                                          ; preds = %entry
  %2 = load %struct.lzma_allocator*, %struct.lzma_allocator** %allocator.addr, align 8, !dbg !222
  %call = call noalias i8* @lzma_alloc(i64 4272, %struct.lzma_allocator* %2), !dbg !224
  %3 = bitcast i8* %call to %struct.lzma_coder_s*, !dbg !224
  %4 = load %struct.lzma_next_coder_s*, %struct.lzma_next_coder_s** %next.addr, align 8, !dbg !225
  %coder1 = getelementptr inbounds %struct.lzma_next_coder_s, %struct.lzma_next_coder_s* %4, i32 0, i32 0, !dbg !226
  store %struct.lzma_coder_s* %3, %struct.lzma_coder_s** %coder1, align 8, !dbg !227
  %5 = load %struct.lzma_next_coder_s*, %struct.lzma_next_coder_s** %next.addr, align 8, !dbg !228
  %coder2 = getelementptr inbounds %struct.lzma_next_coder_s, %struct.lzma_next_coder_s* %5, i32 0, i32 0, !dbg !230
  %6 = load %struct.lzma_coder_s*, %struct.lzma_coder_s** %coder2, align 8, !dbg !230
  %cmp3 = icmp eq %struct.lzma_coder_s* %6, null, !dbg !231
  br i1 %cmp3, label %if.then4, label %if.end, !dbg !232

if.then4:                                         ; preds = %if.then
  store i32 5, i32* %retval, align 4, !dbg !233
  br label %return, !dbg !233

if.end:                                           ; preds = %if.then
  %7 = load %struct.lzma_next_coder_s*, %struct.lzma_next_coder_s** %next.addr, align 8, !dbg !234
  %code = getelementptr inbounds %struct.lzma_next_coder_s, %struct.lzma_next_coder_s* %7, i32 0, i32 3, !dbg !235
  store i32 (%struct.lzma_coder_s*, %struct.lzma_allocator*, i8*, i64*, i64, i8*, i64*, i64, i32)* @lz_decode, i32 (%struct.lzma_coder_s*, %struct.lzma_allocator*, i8*, i64*, i64, i8*, i64*, i64, i32)** %code, align 8, !dbg !236
  %8 = load %struct.lzma_next_coder_s*, %struct.lzma_next_coder_s** %next.addr, align 8, !dbg !237
  %end = getelementptr inbounds %struct.lzma_next_coder_s, %struct.lzma_next_coder_s* %8, i32 0, i32 4, !dbg !238
  store void (%struct.lzma_coder_s*, %struct.lzma_allocator*)* @lz_decoder_end, void (%struct.lzma_coder_s*, %struct.lzma_allocator*)** %end, align 8, !dbg !239
  %9 = load %struct.lzma_next_coder_s*, %struct.lzma_next_coder_s** %next.addr, align 8, !dbg !240
  %coder5 = getelementptr inbounds %struct.lzma_next_coder_s, %struct.lzma_next_coder_s* %9, i32 0, i32 0, !dbg !241
  %10 = load %struct.lzma_coder_s*, %struct.lzma_coder_s** %coder5, align 8, !dbg !241
  %dict = getelementptr inbounds %struct.lzma_coder_s, %struct.lzma_coder_s* %10, i32 0, i32 0, !dbg !242
  %buf = getelementptr inbounds %struct.lzma_dict, %struct.lzma_dict* %dict, i32 0, i32 0, !dbg !243
  store i8* null, i8** %buf, align 8, !dbg !244
  %11 = load %struct.lzma_next_coder_s*, %struct.lzma_next_coder_s** %next.addr, align 8, !dbg !245
  %coder6 = getelementptr inbounds %struct.lzma_next_coder_s, %struct.lzma_next_coder_s* %11, i32 0, i32 0, !dbg !246
  %12 = load %struct.lzma_coder_s*, %struct.lzma_coder_s** %coder6, align 8, !dbg !246
  %dict7 = getelementptr inbounds %struct.lzma_coder_s, %struct.lzma_coder_s* %12, i32 0, i32 0, !dbg !247
  %size = getelementptr inbounds %struct.lzma_dict, %struct.lzma_dict* %dict7, i32 0, i32 4, !dbg !248
  store i64 0, i64* %size, align 8, !dbg !249
  %13 = load %struct.lzma_next_coder_s*, %struct.lzma_next_coder_s** %next.addr, align 8, !dbg !250
  %coder8 = getelementptr inbounds %struct.lzma_next_coder_s, %struct.lzma_next_coder_s* %13, i32 0, i32 0, !dbg !251
  %14 = load %struct.lzma_coder_s*, %struct.lzma_coder_s** %coder8, align 8, !dbg !251
  %lz = getelementptr inbounds %struct.lzma_coder_s, %struct.lzma_coder_s* %14, i32 0, i32 1, !dbg !252
  %15 = bitcast %struct.lzma_lz_decoder* %lz to i8*, !dbg !253
  call void @llvm.memcpy.p0i8.p0i8.i64(i8* %15, i8* bitcast (%struct.lzma_lz_decoder* @LZMA_LZ_DECODER_INIT to i8*), i64 40, i32 8, i1 false), !dbg !253
  %16 = load %struct.lzma_next_coder_s*, %struct.lzma_next_coder_s** %next.addr, align 8, !dbg !254
  %coder9 = getelementptr inbounds %struct.lzma_next_coder_s, %struct.lzma_next_coder_s* %16, i32 0, i32 0, !dbg !255
  %17 = load %struct.lzma_coder_s*, %struct.lzma_coder_s** %coder9, align 8, !dbg !255
  %next10 = getelementptr inbounds %struct.lzma_coder_s, %struct.lzma_coder_s* %17, i32 0, i32 2, !dbg !256
  %18 = bitcast %struct.lzma_next_coder_s* %next10 to i8*, !dbg !257
  call void @llvm.memcpy.p0i8.p0i8.i64(i8* %18, i8* bitcast (%struct.lzma_next_coder_s* @LZMA_NEXT_CODER_INIT to i8*), i64 64, i32 8, i1 false), !dbg !257
  br label %if.end11, !dbg !258

if.end11:                                         ; preds = %if.end, %entry
  br label %do.body, !dbg !259

do.body:                                          ; preds = %if.end11
  call void @llvm.dbg.declare(metadata i32* %ret_, metadata !260, metadata !207), !dbg !263
  %19 = load i32 (%struct.lzma_lz_decoder*, %struct.lzma_allocator*, i8*, %struct.lzma_lz_options*)*, i32 (%struct.lzma_lz_decoder*, %struct.lzma_allocator*, i8*, %struct.lzma_lz_options*)** %lz_init.addr, align 8, !dbg !264
  %20 = load %struct.lzma_next_coder_s*, %struct.lzma_next_coder_s** %next.addr, align 8, !dbg !264
  %coder12 = getelementptr inbounds %struct.lzma_next_coder_s, %struct.lzma_next_coder_s* %20, i32 0, i32 0, !dbg !264
  %21 = load %struct.lzma_coder_s*, %struct.lzma_coder_s** %coder12, align 8, !dbg !264
  %lz13 = getelementptr inbounds %struct.lzma_coder_s, %struct.lzma_coder_s* %21, i32 0, i32 1, !dbg !264
  %22 = load %struct.lzma_allocator*, %struct.lzma_allocator** %allocator.addr, align 8, !dbg !264
  %23 = load %struct.lzma_filter_info_s*, %struct.lzma_filter_info_s** %filters.addr, align 8, !dbg !264
  %arrayidx = getelementptr inbounds %struct.lzma_filter_info_s, %struct.lzma_filter_info_s* %23, i64 0, !dbg !264
  %options = getelementptr inbounds %struct.lzma_filter_info_s, %struct.lzma_filter_info_s* %arrayidx, i32 0, i32 2, !dbg !264
  %24 = load i8*, i8** %options, align 8, !dbg !264
  %call14 = call i32 %19(%struct.lzma_lz_decoder* %lz13, %struct.lzma_allocator* %22, i8* %24, %struct.lzma_lz_options* %lz_options), !dbg !264
  store i32 %call14, i32* %ret_, align 4, !dbg !264
  %25 = load i32, i32* %ret_, align 4, !dbg !264
  %cmp15 = icmp ne i32 %25, 0, !dbg !264
  br i1 %cmp15, label %if.then16, label %if.end17, !dbg !264

if.then16:                                        ; preds = %do.body
  %26 = load i32, i32* %ret_, align 4, !dbg !266
  store i32 %26, i32* %retval, align 4, !dbg !266
  br label %return, !dbg !266

if.end17:                                         ; preds = %do.body
  br label %do.end, !dbg !269

do.end:                                           ; preds = %if.end17
  %dict_size = getelementptr inbounds %struct.lzma_lz_options, %struct.lzma_lz_options* %lz_options, i32 0, i32 0, !dbg !271
  %27 = load i64, i64* %dict_size, align 8, !dbg !271
  %cmp18 = icmp ult i64 %27, 4096, !dbg !273
  br i1 %cmp18, label %if.then19, label %if.end21, !dbg !274

if.then19:                                        ; preds = %do.end
  %dict_size20 = getelementptr inbounds %struct.lzma_lz_options, %struct.lzma_lz_options* %lz_options, i32 0, i32 0, !dbg !275
  store i64 4096, i64* %dict_size20, align 8, !dbg !276
  br label %if.end21, !dbg !277

if.end21:                                         ; preds = %if.then19, %do.end
  %dict_size22 = getelementptr inbounds %struct.lzma_lz_options, %struct.lzma_lz_options* %lz_options, i32 0, i32 0, !dbg !278
  %28 = load i64, i64* %dict_size22, align 8, !dbg !278
  %cmp23 = icmp ugt i64 %28, -16, !dbg !280
  br i1 %cmp23, label %if.then24, label %if.end25, !dbg !281

if.then24:                                        ; preds = %if.end21
  store i32 5, i32* %retval, align 4, !dbg !282
  br label %return, !dbg !282

if.end25:                                         ; preds = %if.end21
  %dict_size26 = getelementptr inbounds %struct.lzma_lz_options, %struct.lzma_lz_options* %lz_options, i32 0, i32 0, !dbg !283
  %29 = load i64, i64* %dict_size26, align 8, !dbg !283
  %add = add i64 %29, 15, !dbg !284
  %and = and i64 %add, -16, !dbg !285
  %dict_size27 = getelementptr inbounds %struct.lzma_lz_options, %struct.lzma_lz_options* %lz_options, i32 0, i32 0, !dbg !286
  store i64 %and, i64* %dict_size27, align 8, !dbg !287
  %30 = load %struct.lzma_next_coder_s*, %struct.lzma_next_coder_s** %next.addr, align 8, !dbg !288
  %coder28 = getelementptr inbounds %struct.lzma_next_coder_s, %struct.lzma_next_coder_s* %30, i32 0, i32 0, !dbg !290
  %31 = load %struct.lzma_coder_s*, %struct.lzma_coder_s** %coder28, align 8, !dbg !290
  %dict29 = getelementptr inbounds %struct.lzma_coder_s, %struct.lzma_coder_s* %31, i32 0, i32 0, !dbg !291
  %size30 = getelementptr inbounds %struct.lzma_dict, %struct.lzma_dict* %dict29, i32 0, i32 4, !dbg !292
  %32 = load i64, i64* %size30, align 8, !dbg !292
  %dict_size31 = getelementptr inbounds %struct.lzma_lz_options, %struct.lzma_lz_options* %lz_options, i32 0, i32 0, !dbg !293
  %33 = load i64, i64* %dict_size31, align 8, !dbg !293
  %cmp32 = icmp ne i64 %32, %33, !dbg !294
  br i1 %cmp32, label %if.then33, label %if.end52, !dbg !295

if.then33:                                        ; preds = %if.end25
  %34 = load %struct.lzma_next_coder_s*, %struct.lzma_next_coder_s** %next.addr, align 8, !dbg !296
  %coder34 = getelementptr inbounds %struct.lzma_next_coder_s, %struct.lzma_next_coder_s* %34, i32 0, i32 0, !dbg !298
  %35 = load %struct.lzma_coder_s*, %struct.lzma_coder_s** %coder34, align 8, !dbg !298
  %dict35 = getelementptr inbounds %struct.lzma_coder_s, %struct.lzma_coder_s* %35, i32 0, i32 0, !dbg !299
  %buf36 = getelementptr inbounds %struct.lzma_dict, %struct.lzma_dict* %dict35, i32 0, i32 0, !dbg !300
  %36 = load i8*, i8** %buf36, align 8, !dbg !300
  %37 = load %struct.lzma_allocator*, %struct.lzma_allocator** %allocator.addr, align 8, !dbg !301
  call void @lzma_free(i8* %36, %struct.lzma_allocator* %37), !dbg !302
  %dict_size37 = getelementptr inbounds %struct.lzma_lz_options, %struct.lzma_lz_options* %lz_options, i32 0, i32 0, !dbg !303
  %38 = load i64, i64* %dict_size37, align 8, !dbg !303
  %39 = load %struct.lzma_allocator*, %struct.lzma_allocator** %allocator.addr, align 8, !dbg !304
  %call38 = call noalias i8* @lzma_alloc(i64 %38, %struct.lzma_allocator* %39), !dbg !305
  %40 = load %struct.lzma_next_coder_s*, %struct.lzma_next_coder_s** %next.addr, align 8, !dbg !306
  %coder39 = getelementptr inbounds %struct.lzma_next_coder_s, %struct.lzma_next_coder_s* %40, i32 0, i32 0, !dbg !307
  %41 = load %struct.lzma_coder_s*, %struct.lzma_coder_s** %coder39, align 8, !dbg !307
  %dict40 = getelementptr inbounds %struct.lzma_coder_s, %struct.lzma_coder_s* %41, i32 0, i32 0, !dbg !308
  %buf41 = getelementptr inbounds %struct.lzma_dict, %struct.lzma_dict* %dict40, i32 0, i32 0, !dbg !309
  store i8* %call38, i8** %buf41, align 8, !dbg !310
  %42 = load %struct.lzma_next_coder_s*, %struct.lzma_next_coder_s** %next.addr, align 8, !dbg !311
  %coder42 = getelementptr inbounds %struct.lzma_next_coder_s, %struct.lzma_next_coder_s* %42, i32 0, i32 0, !dbg !313
  %43 = load %struct.lzma_coder_s*, %struct.lzma_coder_s** %coder42, align 8, !dbg !313
  %dict43 = getelementptr inbounds %struct.lzma_coder_s, %struct.lzma_coder_s* %43, i32 0, i32 0, !dbg !314
  %buf44 = getelementptr inbounds %struct.lzma_dict, %struct.lzma_dict* %dict43, i32 0, i32 0, !dbg !315
  %44 = load i8*, i8** %buf44, align 8, !dbg !315
  %cmp45 = icmp eq i8* %44, null, !dbg !316
  br i1 %cmp45, label %if.then46, label %if.end47, !dbg !317

if.then46:                                        ; preds = %if.then33
  store i32 5, i32* %retval, align 4, !dbg !318
  br label %return, !dbg !318

if.end47:                                         ; preds = %if.then33
  %dict_size48 = getelementptr inbounds %struct.lzma_lz_options, %struct.lzma_lz_options* %lz_options, i32 0, i32 0, !dbg !319
  %45 = load i64, i64* %dict_size48, align 8, !dbg !319
  %46 = load %struct.lzma_next_coder_s*, %struct.lzma_next_coder_s** %next.addr, align 8, !dbg !320
  %coder49 = getelementptr inbounds %struct.lzma_next_coder_s, %struct.lzma_next_coder_s* %46, i32 0, i32 0, !dbg !321
  %47 = load %struct.lzma_coder_s*, %struct.lzma_coder_s** %coder49, align 8, !dbg !321
  %dict50 = getelementptr inbounds %struct.lzma_coder_s, %struct.lzma_coder_s* %47, i32 0, i32 0, !dbg !322
  %size51 = getelementptr inbounds %struct.lzma_dict, %struct.lzma_dict* %dict50, i32 0, i32 4, !dbg !323
  store i64 %45, i64* %size51, align 8, !dbg !324
  br label %if.end52, !dbg !325

if.end52:                                         ; preds = %if.end47, %if.end25
  %48 = load %struct.lzma_next_coder_s*, %struct.lzma_next_coder_s** %next.addr, align 8, !dbg !326
  %coder53 = getelementptr inbounds %struct.lzma_next_coder_s, %struct.lzma_next_coder_s* %48, i32 0, i32 0, !dbg !327
  %49 = load %struct.lzma_coder_s*, %struct.lzma_coder_s** %coder53, align 8, !dbg !327
  call void @lz_decoder_reset(%struct.lzma_coder_s* %49), !dbg !328
  %preset_dict = getelementptr inbounds %struct.lzma_lz_options, %struct.lzma_lz_options* %lz_options, i32 0, i32 1, !dbg !329
  %50 = load i8*, i8** %preset_dict, align 8, !dbg !329
  %cmp54 = icmp ne i8* %50, null, !dbg !331
  br i1 %cmp54, label %land.lhs.true, label %if.end71, !dbg !332

land.lhs.true:                                    ; preds = %if.end52
  %preset_dict_size = getelementptr inbounds %struct.lzma_lz_options, %struct.lzma_lz_options* %lz_options, i32 0, i32 2, !dbg !333
  %51 = load i64, i64* %preset_dict_size, align 8, !dbg !333
  %cmp55 = icmp ugt i64 %51, 0, !dbg !335
  br i1 %cmp55, label %if.then56, label %if.end71, !dbg !336

if.then56:                                        ; preds = %land.lhs.true
  call void @llvm.dbg.declare(metadata i64* %copy_size, metadata !338, metadata !207), !dbg !341
  %preset_dict_size57 = getelementptr inbounds %struct.lzma_lz_options, %struct.lzma_lz_options* %lz_options, i32 0, i32 2, !dbg !342
  %52 = load i64, i64* %preset_dict_size57, align 8, !dbg !342
  %dict_size58 = getelementptr inbounds %struct.lzma_lz_options, %struct.lzma_lz_options* %lz_options, i32 0, i32 0, !dbg !342
  %53 = load i64, i64* %dict_size58, align 8, !dbg !342
  %cmp59 = icmp ult i64 %52, %53, !dbg !342
  br i1 %cmp59, label %cond.true, label %cond.false, !dbg !342

cond.true:                                        ; preds = %if.then56
  %preset_dict_size60 = getelementptr inbounds %struct.lzma_lz_options, %struct.lzma_lz_options* %lz_options, i32 0, i32 2, !dbg !343
  %54 = load i64, i64* %preset_dict_size60, align 8, !dbg !343
  br label %cond.end, !dbg !343

cond.false:                                       ; preds = %if.then56
  %dict_size61 = getelementptr inbounds %struct.lzma_lz_options, %struct.lzma_lz_options* %lz_options, i32 0, i32 0, !dbg !345
  %55 = load i64, i64* %dict_size61, align 8, !dbg !345
  br label %cond.end, !dbg !345

cond.end:                                         ; preds = %cond.false, %cond.true
  %cond = phi i64 [ %54, %cond.true ], [ %55, %cond.false ], !dbg !347
  store i64 %cond, i64* %copy_size, align 8, !dbg !349
  call void @llvm.dbg.declare(metadata i64* %offset, metadata !350, metadata !207), !dbg !351
  %preset_dict_size62 = getelementptr inbounds %struct.lzma_lz_options, %struct.lzma_lz_options* %lz_options, i32 0, i32 2, !dbg !352
  %56 = load i64, i64* %preset_dict_size62, align 8, !dbg !352
  %57 = load i64, i64* %copy_size, align 8, !dbg !353
  %sub = sub i64 %56, %57, !dbg !354
  store i64 %sub, i64* %offset, align 8, !dbg !351
  %58 = load %struct.lzma_next_coder_s*, %struct.lzma_next_coder_s** %next.addr, align 8, !dbg !355
  %coder63 = getelementptr inbounds %struct.lzma_next_coder_s, %struct.lzma_next_coder_s* %58, i32 0, i32 0, !dbg !356
  %59 = load %struct.lzma_coder_s*, %struct.lzma_coder_s** %coder63, align 8, !dbg !356
  %dict64 = getelementptr inbounds %struct.lzma_coder_s, %struct.lzma_coder_s* %59, i32 0, i32 0, !dbg !357
  %buf65 = getelementptr inbounds %struct.lzma_dict, %struct.lzma_dict* %dict64, i32 0, i32 0, !dbg !358
  %60 = load i8*, i8** %buf65, align 8, !dbg !358
  %preset_dict66 = getelementptr inbounds %struct.lzma_lz_options, %struct.lzma_lz_options* %lz_options, i32 0, i32 1, !dbg !359
  %61 = load i8*, i8** %preset_dict66, align 8, !dbg !359
  %62 = load i64, i64* %offset, align 8, !dbg !360
  %add.ptr = getelementptr inbounds i8, i8* %61, i64 %62, !dbg !361
  %63 = load i64, i64* %copy_size, align 8, !dbg !362
  call void @llvm.memcpy.p0i8.p0i8.i64(i8* %60, i8* %add.ptr, i64 %63, i32 1, i1 false), !dbg !363
  %64 = load i64, i64* %copy_size, align 8, !dbg !364
  %65 = load %struct.lzma_next_coder_s*, %struct.lzma_next_coder_s** %next.addr, align 8, !dbg !365
  %coder67 = getelementptr inbounds %struct.lzma_next_coder_s, %struct.lzma_next_coder_s* %65, i32 0, i32 0, !dbg !366
  %66 = load %struct.lzma_coder_s*, %struct.lzma_coder_s** %coder67, align 8, !dbg !366
  %dict68 = getelementptr inbounds %struct.lzma_coder_s, %struct.lzma_coder_s* %66, i32 0, i32 0, !dbg !367
  %pos = getelementptr inbounds %struct.lzma_dict, %struct.lzma_dict* %dict68, i32 0, i32 1, !dbg !368
  store i64 %64, i64* %pos, align 8, !dbg !369
  %67 = load i64, i64* %copy_size, align 8, !dbg !370
  %68 = load %struct.lzma_next_coder_s*, %struct.lzma_next_coder_s** %next.addr, align 8, !dbg !371
  %coder69 = getelementptr inbounds %struct.lzma_next_coder_s, %struct.lzma_next_coder_s* %68, i32 0, i32 0, !dbg !372
  %69 = load %struct.lzma_coder_s*, %struct.lzma_coder_s** %coder69, align 8, !dbg !372
  %dict70 = getelementptr inbounds %struct.lzma_coder_s, %struct.lzma_coder_s* %69, i32 0, i32 0, !dbg !373
  %full = getelementptr inbounds %struct.lzma_dict, %struct.lzma_dict* %dict70, i32 0, i32 2, !dbg !374
  store i64 %67, i64* %full, align 8, !dbg !375
  br label %if.end71, !dbg !376

if.end71:                                         ; preds = %cond.end, %land.lhs.true, %if.end52
  %70 = load %struct.lzma_next_coder_s*, %struct.lzma_next_coder_s** %next.addr, align 8, !dbg !377
  %coder72 = getelementptr inbounds %struct.lzma_next_coder_s, %struct.lzma_next_coder_s* %70, i32 0, i32 0, !dbg !378
  %71 = load %struct.lzma_coder_s*, %struct.lzma_coder_s** %coder72, align 8, !dbg !378
  %next_finished = getelementptr inbounds %struct.lzma_coder_s, %struct.lzma_coder_s* %71, i32 0, i32 3, !dbg !379
  store i8 0, i8* %next_finished, align 8, !dbg !380
  %72 = load %struct.lzma_next_coder_s*, %struct.lzma_next_coder_s** %next.addr, align 8, !dbg !381
  %coder73 = getelementptr inbounds %struct.lzma_next_coder_s, %struct.lzma_next_coder_s* %72, i32 0, i32 0, !dbg !382
  %73 = load %struct.lzma_coder_s*, %struct.lzma_coder_s** %coder73, align 8, !dbg !382
  %this_finished = getelementptr inbounds %struct.lzma_coder_s, %struct.lzma_coder_s* %73, i32 0, i32 4, !dbg !383
  store i8 0, i8* %this_finished, align 1, !dbg !384
  %74 = load %struct.lzma_next_coder_s*, %struct.lzma_next_coder_s** %next.addr, align 8, !dbg !385
  %coder74 = getelementptr inbounds %struct.lzma_next_coder_s, %struct.lzma_next_coder_s* %74, i32 0, i32 0, !dbg !386
  %75 = load %struct.lzma_coder_s*, %struct.lzma_coder_s** %coder74, align 8, !dbg !386
  %temp = getelementptr inbounds %struct.lzma_coder_s, %struct.lzma_coder_s* %75, i32 0, i32 5, !dbg !387
  %pos75 = getelementptr inbounds %struct.anon, %struct.anon* %temp, i32 0, i32 0, !dbg !388
  store i64 0, i64* %pos75, align 8, !dbg !389
  %76 = load %struct.lzma_next_coder_s*, %struct.lzma_next_coder_s** %next.addr, align 8, !dbg !390
  %coder76 = getelementptr inbounds %struct.lzma_next_coder_s, %struct.lzma_next_coder_s* %76, i32 0, i32 0, !dbg !391
  %77 = load %struct.lzma_coder_s*, %struct.lzma_coder_s** %coder76, align 8, !dbg !391
  %temp77 = getelementptr inbounds %struct.lzma_coder_s, %struct.lzma_coder_s* %77, i32 0, i32 5, !dbg !392
  %size78 = getelementptr inbounds %struct.anon, %struct.anon* %temp77, i32 0, i32 1, !dbg !393
  store i64 0, i64* %size78, align 8, !dbg !394
  %78 = load %struct.lzma_next_coder_s*, %struct.lzma_next_coder_s** %next.addr, align 8, !dbg !395
  %coder79 = getelementptr inbounds %struct.lzma_next_coder_s, %struct.lzma_next_coder_s* %78, i32 0, i32 0, !dbg !396
  %79 = load %struct.lzma_coder_s*, %struct.lzma_coder_s** %coder79, align 8, !dbg !396
  %next80 = getelementptr inbounds %struct.lzma_coder_s, %struct.lzma_coder_s* %79, i32 0, i32 2, !dbg !397
  %80 = load %struct.lzma_allocator*, %struct.lzma_allocator** %allocator.addr, align 8, !dbg !398
  %81 = load %struct.lzma_filter_info_s*, %struct.lzma_filter_info_s** %filters.addr, align 8, !dbg !399
  %add.ptr81 = getelementptr inbounds %struct.lzma_filter_info_s, %struct.lzma_filter_info_s* %81, i64 1, !dbg !400
  %call82 = call i32 @lzma_next_filter_init(%struct.lzma_next_coder_s* %next80, %struct.lzma_allocator* %80, %struct.lzma_filter_info_s* %add.ptr81), !dbg !401
  store i32 %call82, i32* %retval, align 4, !dbg !402
  br label %return, !dbg !402

return:                                           ; preds = %if.end71, %if.then46, %if.then24, %if.then16, %if.then4
  %82 = load i32, i32* %retval, align 4, !dbg !403
  ret i32 %82, !dbg !403
}

; Function Attrs: nounwind readnone
declare void @llvm.dbg.declare(metadata, metadata, metadata) #1

declare noalias i8* @lzma_alloc(i64, %struct.lzma_allocator*) #2

; Function Attrs: nounwind uwtable
define internal i32 @lz_decode(%struct.lzma_coder_s* %coder, %struct.lzma_allocator* %allocator, i8* noalias %in, i64* noalias %in_pos, i64 %in_size, i8* noalias %out, i64* noalias %out_pos, i64 %out_size, i32 %action) #0 !dbg !190 {
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
  store %struct.lzma_coder_s* %coder, %struct.lzma_coder_s** %coder.addr, align 8
  call void @llvm.dbg.declare(metadata %struct.lzma_coder_s** %coder.addr, metadata !404, metadata !207), !dbg !405
  store %struct.lzma_allocator* %allocator, %struct.lzma_allocator** %allocator.addr, align 8
  call void @llvm.dbg.declare(metadata %struct.lzma_allocator** %allocator.addr, metadata !406, metadata !207), !dbg !407
  store i8* %in, i8** %in.addr, align 8
  call void @llvm.dbg.declare(metadata i8** %in.addr, metadata !408, metadata !207), !dbg !409
  store i64* %in_pos, i64** %in_pos.addr, align 8
  call void @llvm.dbg.declare(metadata i64** %in_pos.addr, metadata !410, metadata !207), !dbg !411
  store i64 %in_size, i64* %in_size.addr, align 8
  call void @llvm.dbg.declare(metadata i64* %in_size.addr, metadata !412, metadata !207), !dbg !413
  store i8* %out, i8** %out.addr, align 8
  call void @llvm.dbg.declare(metadata i8** %out.addr, metadata !414, metadata !207), !dbg !415
  store i64* %out_pos, i64** %out_pos.addr, align 8
  call void @llvm.dbg.declare(metadata i64** %out_pos.addr, metadata !416, metadata !207), !dbg !417
  store i64 %out_size, i64* %out_size.addr, align 8
  call void @llvm.dbg.declare(metadata i64* %out_size.addr, metadata !418, metadata !207), !dbg !419
  store i32 %action, i32* %action.addr, align 4
  call void @llvm.dbg.declare(metadata i32* %action.addr, metadata !420, metadata !207), !dbg !421
  %0 = load %struct.lzma_coder_s*, %struct.lzma_coder_s** %coder.addr, align 8, !dbg !422
  %next = getelementptr inbounds %struct.lzma_coder_s, %struct.lzma_coder_s* %0, i32 0, i32 2, !dbg !424
  %code = getelementptr inbounds %struct.lzma_next_coder_s, %struct.lzma_next_coder_s* %next, i32 0, i32 3, !dbg !425
  %1 = load i32 (%struct.lzma_coder_s*, %struct.lzma_allocator*, i8*, i64*, i64, i8*, i64*, i64, i32)*, i32 (%struct.lzma_coder_s*, %struct.lzma_allocator*, i8*, i64*, i64, i8*, i64*, i64, i32)** %code, align 8, !dbg !425
  %cmp = icmp eq i32 (%struct.lzma_coder_s*, %struct.lzma_allocator*, i8*, i64*, i64, i8*, i64*, i64, i32)* %1, null, !dbg !426
  br i1 %cmp, label %if.then, label %if.end, !dbg !427

if.then:                                          ; preds = %entry
  %2 = load %struct.lzma_coder_s*, %struct.lzma_coder_s** %coder.addr, align 8, !dbg !428
  %3 = load i8*, i8** %in.addr, align 8, !dbg !429
  %4 = load i64*, i64** %in_pos.addr, align 8, !dbg !430
  %5 = load i64, i64* %in_size.addr, align 8, !dbg !431
  %6 = load i8*, i8** %out.addr, align 8, !dbg !432
  %7 = load i64*, i64** %out_pos.addr, align 8, !dbg !433
  %8 = load i64, i64* %out_size.addr, align 8, !dbg !434
  %call = call i32 @decode_buffer(%struct.lzma_coder_s* %2, i8* %3, i64* %4, i64 %5, i8* %6, i64* %7, i64 %8), !dbg !435
  store i32 %call, i32* %retval, align 4, !dbg !436
  br label %return, !dbg !436

if.end:                                           ; preds = %entry
  br label %while.cond, !dbg !437

while.cond:                                       ; preds = %if.end62, %if.end
  %9 = load i64*, i64** %out_pos.addr, align 8, !dbg !438
  %10 = load i64, i64* %9, align 8, !dbg !440
  %11 = load i64, i64* %out_size.addr, align 8, !dbg !441
  %cmp1 = icmp ult i64 %10, %11, !dbg !442
  br i1 %cmp1, label %while.body, label %while.end, !dbg !443

while.body:                                       ; preds = %while.cond
  call void @llvm.dbg.declare(metadata i32* %ret, metadata !444, metadata !207), !dbg !446
  %12 = load %struct.lzma_coder_s*, %struct.lzma_coder_s** %coder.addr, align 8, !dbg !447
  %next_finished = getelementptr inbounds %struct.lzma_coder_s, %struct.lzma_coder_s* %12, i32 0, i32 3, !dbg !449
  %13 = load i8, i8* %next_finished, align 8, !dbg !449
  %tobool = trunc i8 %13 to i1, !dbg !449
  br i1 %tobool, label %if.end27, label %land.lhs.true, !dbg !450

land.lhs.true:                                    ; preds = %while.body
  %14 = load %struct.lzma_coder_s*, %struct.lzma_coder_s** %coder.addr, align 8, !dbg !451
  %temp = getelementptr inbounds %struct.lzma_coder_s, %struct.lzma_coder_s* %14, i32 0, i32 5, !dbg !453
  %pos = getelementptr inbounds %struct.anon, %struct.anon* %temp, i32 0, i32 0, !dbg !454
  %15 = load i64, i64* %pos, align 8, !dbg !454
  %16 = load %struct.lzma_coder_s*, %struct.lzma_coder_s** %coder.addr, align 8, !dbg !455
  %temp2 = getelementptr inbounds %struct.lzma_coder_s, %struct.lzma_coder_s* %16, i32 0, i32 5, !dbg !456
  %size = getelementptr inbounds %struct.anon, %struct.anon* %temp2, i32 0, i32 1, !dbg !457
  %17 = load i64, i64* %size, align 8, !dbg !457
  %cmp3 = icmp eq i64 %15, %17, !dbg !458
  br i1 %cmp3, label %if.then4, label %if.end27, !dbg !459

if.then4:                                         ; preds = %land.lhs.true
  %18 = load %struct.lzma_coder_s*, %struct.lzma_coder_s** %coder.addr, align 8, !dbg !461
  %temp5 = getelementptr inbounds %struct.lzma_coder_s, %struct.lzma_coder_s* %18, i32 0, i32 5, !dbg !463
  %pos6 = getelementptr inbounds %struct.anon, %struct.anon* %temp5, i32 0, i32 0, !dbg !464
  store i64 0, i64* %pos6, align 8, !dbg !465
  %19 = load %struct.lzma_coder_s*, %struct.lzma_coder_s** %coder.addr, align 8, !dbg !466
  %temp7 = getelementptr inbounds %struct.lzma_coder_s, %struct.lzma_coder_s* %19, i32 0, i32 5, !dbg !467
  %size8 = getelementptr inbounds %struct.anon, %struct.anon* %temp7, i32 0, i32 1, !dbg !468
  store i64 0, i64* %size8, align 8, !dbg !469
  %20 = load %struct.lzma_coder_s*, %struct.lzma_coder_s** %coder.addr, align 8, !dbg !470
  %next9 = getelementptr inbounds %struct.lzma_coder_s, %struct.lzma_coder_s* %20, i32 0, i32 2, !dbg !471
  %code10 = getelementptr inbounds %struct.lzma_next_coder_s, %struct.lzma_next_coder_s* %next9, i32 0, i32 3, !dbg !472
  %21 = load i32 (%struct.lzma_coder_s*, %struct.lzma_allocator*, i8*, i64*, i64, i8*, i64*, i64, i32)*, i32 (%struct.lzma_coder_s*, %struct.lzma_allocator*, i8*, i64*, i64, i8*, i64*, i64, i32)** %code10, align 8, !dbg !472
  %22 = load %struct.lzma_coder_s*, %struct.lzma_coder_s** %coder.addr, align 8, !dbg !473
  %next11 = getelementptr inbounds %struct.lzma_coder_s, %struct.lzma_coder_s* %22, i32 0, i32 2, !dbg !474
  %coder12 = getelementptr inbounds %struct.lzma_next_coder_s, %struct.lzma_next_coder_s* %next11, i32 0, i32 0, !dbg !475
  %23 = load %struct.lzma_coder_s*, %struct.lzma_coder_s** %coder12, align 8, !dbg !475
  %24 = load %struct.lzma_allocator*, %struct.lzma_allocator** %allocator.addr, align 8, !dbg !476
  %25 = load i8*, i8** %in.addr, align 8, !dbg !477
  %26 = load i64*, i64** %in_pos.addr, align 8, !dbg !478
  %27 = load i64, i64* %in_size.addr, align 8, !dbg !479
  %28 = load %struct.lzma_coder_s*, %struct.lzma_coder_s** %coder.addr, align 8, !dbg !480
  %temp13 = getelementptr inbounds %struct.lzma_coder_s, %struct.lzma_coder_s* %28, i32 0, i32 5, !dbg !481
  %buffer = getelementptr inbounds %struct.anon, %struct.anon* %temp13, i32 0, i32 2, !dbg !482
  %arraydecay = getelementptr inbounds [4096 x i8], [4096 x i8]* %buffer, i32 0, i32 0, !dbg !480
  %29 = load %struct.lzma_coder_s*, %struct.lzma_coder_s** %coder.addr, align 8, !dbg !483
  %temp14 = getelementptr inbounds %struct.lzma_coder_s, %struct.lzma_coder_s* %29, i32 0, i32 5, !dbg !484
  %size15 = getelementptr inbounds %struct.anon, %struct.anon* %temp14, i32 0, i32 1, !dbg !485
  %30 = load i32, i32* %action.addr, align 4, !dbg !486
  %call16 = call i32 %21(%struct.lzma_coder_s* %23, %struct.lzma_allocator* %24, i8* %25, i64* %26, i64 %27, i8* %arraydecay, i64* %size15, i64 4096, i32 %30), !dbg !470
  store i32 %call16, i32* %ret, align 4, !dbg !487
  %31 = load i32, i32* %ret, align 4, !dbg !488
  %cmp17 = icmp eq i32 %31, 1, !dbg !490
  br i1 %cmp17, label %if.then18, label %if.else, !dbg !491

if.then18:                                        ; preds = %if.then4
  %32 = load %struct.lzma_coder_s*, %struct.lzma_coder_s** %coder.addr, align 8, !dbg !492
  %next_finished19 = getelementptr inbounds %struct.lzma_coder_s, %struct.lzma_coder_s* %32, i32 0, i32 3, !dbg !493
  store i8 1, i8* %next_finished19, align 8, !dbg !494
  br label %if.end26, !dbg !492

if.else:                                          ; preds = %if.then4
  %33 = load i32, i32* %ret, align 4, !dbg !495
  %cmp20 = icmp ne i32 %33, 0, !dbg !497
  br i1 %cmp20, label %if.then24, label %lor.lhs.false, !dbg !498

lor.lhs.false:                                    ; preds = %if.else
  %34 = load %struct.lzma_coder_s*, %struct.lzma_coder_s** %coder.addr, align 8, !dbg !499
  %temp21 = getelementptr inbounds %struct.lzma_coder_s, %struct.lzma_coder_s* %34, i32 0, i32 5, !dbg !501
  %size22 = getelementptr inbounds %struct.anon, %struct.anon* %temp21, i32 0, i32 1, !dbg !502
  %35 = load i64, i64* %size22, align 8, !dbg !502
  %cmp23 = icmp eq i64 %35, 0, !dbg !503
  br i1 %cmp23, label %if.then24, label %if.end25, !dbg !504

if.then24:                                        ; preds = %lor.lhs.false, %if.else
  %36 = load i32, i32* %ret, align 4, !dbg !505
  store i32 %36, i32* %retval, align 4, !dbg !506
  br label %return, !dbg !506

if.end25:                                         ; preds = %lor.lhs.false
  br label %if.end26

if.end26:                                         ; preds = %if.end25, %if.then18
  br label %if.end27, !dbg !507

if.end27:                                         ; preds = %if.end26, %land.lhs.true, %while.body
  %37 = load %struct.lzma_coder_s*, %struct.lzma_coder_s** %coder.addr, align 8, !dbg !508
  %this_finished = getelementptr inbounds %struct.lzma_coder_s, %struct.lzma_coder_s* %37, i32 0, i32 4, !dbg !510
  %38 = load i8, i8* %this_finished, align 1, !dbg !510
  %tobool28 = trunc i8 %38 to i1, !dbg !510
  br i1 %tobool28, label %if.then29, label %if.end39, !dbg !511

if.then29:                                        ; preds = %if.end27
  %39 = load %struct.lzma_coder_s*, %struct.lzma_coder_s** %coder.addr, align 8, !dbg !512
  %temp30 = getelementptr inbounds %struct.lzma_coder_s, %struct.lzma_coder_s* %39, i32 0, i32 5, !dbg !515
  %size31 = getelementptr inbounds %struct.anon, %struct.anon* %temp30, i32 0, i32 1, !dbg !516
  %40 = load i64, i64* %size31, align 8, !dbg !516
  %cmp32 = icmp ne i64 %40, 0, !dbg !517
  br i1 %cmp32, label %if.then33, label %if.end34, !dbg !518

if.then33:                                        ; preds = %if.then29
  store i32 9, i32* %retval, align 4, !dbg !519
  br label %return, !dbg !519

if.end34:                                         ; preds = %if.then29
  %41 = load %struct.lzma_coder_s*, %struct.lzma_coder_s** %coder.addr, align 8, !dbg !520
  %next_finished35 = getelementptr inbounds %struct.lzma_coder_s, %struct.lzma_coder_s* %41, i32 0, i32 3, !dbg !522
  %42 = load i8, i8* %next_finished35, align 8, !dbg !522
  %tobool36 = trunc i8 %42 to i1, !dbg !522
  br i1 %tobool36, label %if.then37, label %if.end38, !dbg !523

if.then37:                                        ; preds = %if.end34
  store i32 1, i32* %retval, align 4, !dbg !524
  br label %return, !dbg !524

if.end38:                                         ; preds = %if.end34
  store i32 0, i32* %retval, align 4, !dbg !525
  br label %return, !dbg !525

if.end39:                                         ; preds = %if.end27
  %43 = load %struct.lzma_coder_s*, %struct.lzma_coder_s** %coder.addr, align 8, !dbg !526
  %44 = load %struct.lzma_coder_s*, %struct.lzma_coder_s** %coder.addr, align 8, !dbg !527
  %temp40 = getelementptr inbounds %struct.lzma_coder_s, %struct.lzma_coder_s* %44, i32 0, i32 5, !dbg !528
  %buffer41 = getelementptr inbounds %struct.anon, %struct.anon* %temp40, i32 0, i32 2, !dbg !529
  %arraydecay42 = getelementptr inbounds [4096 x i8], [4096 x i8]* %buffer41, i32 0, i32 0, !dbg !527
  %45 = load %struct.lzma_coder_s*, %struct.lzma_coder_s** %coder.addr, align 8, !dbg !530
  %temp43 = getelementptr inbounds %struct.lzma_coder_s, %struct.lzma_coder_s* %45, i32 0, i32 5, !dbg !531
  %pos44 = getelementptr inbounds %struct.anon, %struct.anon* %temp43, i32 0, i32 0, !dbg !532
  %46 = load %struct.lzma_coder_s*, %struct.lzma_coder_s** %coder.addr, align 8, !dbg !533
  %temp45 = getelementptr inbounds %struct.lzma_coder_s, %struct.lzma_coder_s* %46, i32 0, i32 5, !dbg !534
  %size46 = getelementptr inbounds %struct.anon, %struct.anon* %temp45, i32 0, i32 1, !dbg !535
  %47 = load i64, i64* %size46, align 8, !dbg !535
  %48 = load i8*, i8** %out.addr, align 8, !dbg !536
  %49 = load i64*, i64** %out_pos.addr, align 8, !dbg !537
  %50 = load i64, i64* %out_size.addr, align 8, !dbg !538
  %call47 = call i32 @decode_buffer(%struct.lzma_coder_s* %43, i8* %arraydecay42, i64* %pos44, i64 %47, i8* %48, i64* %49, i64 %50), !dbg !539
  store i32 %call47, i32* %ret, align 4, !dbg !540
  %51 = load i32, i32* %ret, align 4, !dbg !541
  %cmp48 = icmp eq i32 %51, 1, !dbg !543
  br i1 %cmp48, label %if.then49, label %if.else51, !dbg !544

if.then49:                                        ; preds = %if.end39
  %52 = load %struct.lzma_coder_s*, %struct.lzma_coder_s** %coder.addr, align 8, !dbg !545
  %this_finished50 = getelementptr inbounds %struct.lzma_coder_s, %struct.lzma_coder_s* %52, i32 0, i32 4, !dbg !546
  store i8 1, i8* %this_finished50, align 1, !dbg !547
  br label %if.end62, !dbg !545

if.else51:                                        ; preds = %if.end39
  %53 = load i32, i32* %ret, align 4, !dbg !548
  %cmp52 = icmp ne i32 %53, 0, !dbg !550
  br i1 %cmp52, label %if.then53, label %if.else54, !dbg !551

if.then53:                                        ; preds = %if.else51
  %54 = load i32, i32* %ret, align 4, !dbg !552
  store i32 %54, i32* %retval, align 4, !dbg !553
  br label %return, !dbg !553

if.else54:                                        ; preds = %if.else51
  %55 = load %struct.lzma_coder_s*, %struct.lzma_coder_s** %coder.addr, align 8, !dbg !554
  %next_finished55 = getelementptr inbounds %struct.lzma_coder_s, %struct.lzma_coder_s* %55, i32 0, i32 3, !dbg !556
  %56 = load i8, i8* %next_finished55, align 8, !dbg !556
  %tobool56 = trunc i8 %56 to i1, !dbg !556
  br i1 %tobool56, label %land.lhs.true57, label %if.end60, !dbg !557

land.lhs.true57:                                  ; preds = %if.else54
  %57 = load i64*, i64** %out_pos.addr, align 8, !dbg !558
  %58 = load i64, i64* %57, align 8, !dbg !560
  %59 = load i64, i64* %out_size.addr, align 8, !dbg !561
  %cmp58 = icmp ult i64 %58, %59, !dbg !562
  br i1 %cmp58, label %if.then59, label %if.end60, !dbg !563

if.then59:                                        ; preds = %land.lhs.true57
  store i32 9, i32* %retval, align 4, !dbg !564
  br label %return, !dbg !564

if.end60:                                         ; preds = %land.lhs.true57, %if.else54
  br label %if.end61

if.end61:                                         ; preds = %if.end60
  br label %if.end62

if.end62:                                         ; preds = %if.end61, %if.then49
  br label %while.cond, !dbg !565

while.end:                                        ; preds = %while.cond
  store i32 0, i32* %retval, align 4, !dbg !567
  br label %return, !dbg !567

return:                                           ; preds = %while.end, %if.then59, %if.then53, %if.end38, %if.then37, %if.then33, %if.then24, %if.then
  %60 = load i32, i32* %retval, align 4, !dbg !568
  ret i32 %60, !dbg !568
}

; Function Attrs: nounwind uwtable
define internal void @lz_decoder_end(%struct.lzma_coder_s* %coder, %struct.lzma_allocator* %allocator) #0 !dbg !194 {
entry:
  %coder.addr = alloca %struct.lzma_coder_s*, align 8
  %allocator.addr = alloca %struct.lzma_allocator*, align 8
  store %struct.lzma_coder_s* %coder, %struct.lzma_coder_s** %coder.addr, align 8
  call void @llvm.dbg.declare(metadata %struct.lzma_coder_s** %coder.addr, metadata !569, metadata !207), !dbg !570
  store %struct.lzma_allocator* %allocator, %struct.lzma_allocator** %allocator.addr, align 8
  call void @llvm.dbg.declare(metadata %struct.lzma_allocator** %allocator.addr, metadata !571, metadata !207), !dbg !572
  %0 = load %struct.lzma_coder_s*, %struct.lzma_coder_s** %coder.addr, align 8, !dbg !573
  %next = getelementptr inbounds %struct.lzma_coder_s, %struct.lzma_coder_s* %0, i32 0, i32 2, !dbg !574
  %1 = load %struct.lzma_allocator*, %struct.lzma_allocator** %allocator.addr, align 8, !dbg !575
  call void @lzma_next_end(%struct.lzma_next_coder_s* %next, %struct.lzma_allocator* %1), !dbg !576
  %2 = load %struct.lzma_coder_s*, %struct.lzma_coder_s** %coder.addr, align 8, !dbg !577
  %dict = getelementptr inbounds %struct.lzma_coder_s, %struct.lzma_coder_s* %2, i32 0, i32 0, !dbg !578
  %buf = getelementptr inbounds %struct.lzma_dict, %struct.lzma_dict* %dict, i32 0, i32 0, !dbg !579
  %3 = load i8*, i8** %buf, align 8, !dbg !579
  %4 = load %struct.lzma_allocator*, %struct.lzma_allocator** %allocator.addr, align 8, !dbg !580
  call void @lzma_free(i8* %3, %struct.lzma_allocator* %4), !dbg !581
  %5 = load %struct.lzma_coder_s*, %struct.lzma_coder_s** %coder.addr, align 8, !dbg !582
  %lz = getelementptr inbounds %struct.lzma_coder_s, %struct.lzma_coder_s* %5, i32 0, i32 1, !dbg !584
  %end = getelementptr inbounds %struct.lzma_lz_decoder, %struct.lzma_lz_decoder* %lz, i32 0, i32 4, !dbg !585
  %6 = load void (%struct.lzma_coder_s*, %struct.lzma_allocator*)*, void (%struct.lzma_coder_s*, %struct.lzma_allocator*)** %end, align 8, !dbg !585
  %cmp = icmp ne void (%struct.lzma_coder_s*, %struct.lzma_allocator*)* %6, null, !dbg !586
  br i1 %cmp, label %if.then, label %if.else, !dbg !587

if.then:                                          ; preds = %entry
  %7 = load %struct.lzma_coder_s*, %struct.lzma_coder_s** %coder.addr, align 8, !dbg !588
  %lz1 = getelementptr inbounds %struct.lzma_coder_s, %struct.lzma_coder_s* %7, i32 0, i32 1, !dbg !589
  %end2 = getelementptr inbounds %struct.lzma_lz_decoder, %struct.lzma_lz_decoder* %lz1, i32 0, i32 4, !dbg !590
  %8 = load void (%struct.lzma_coder_s*, %struct.lzma_allocator*)*, void (%struct.lzma_coder_s*, %struct.lzma_allocator*)** %end2, align 8, !dbg !590
  %9 = load %struct.lzma_coder_s*, %struct.lzma_coder_s** %coder.addr, align 8, !dbg !591
  %lz3 = getelementptr inbounds %struct.lzma_coder_s, %struct.lzma_coder_s* %9, i32 0, i32 1, !dbg !592
  %coder4 = getelementptr inbounds %struct.lzma_lz_decoder, %struct.lzma_lz_decoder* %lz3, i32 0, i32 0, !dbg !593
  %10 = load %struct.lzma_coder_s*, %struct.lzma_coder_s** %coder4, align 8, !dbg !593
  %11 = load %struct.lzma_allocator*, %struct.lzma_allocator** %allocator.addr, align 8, !dbg !594
  call void %8(%struct.lzma_coder_s* %10, %struct.lzma_allocator* %11), !dbg !588
  br label %if.end, !dbg !588

if.else:                                          ; preds = %entry
  %12 = load %struct.lzma_coder_s*, %struct.lzma_coder_s** %coder.addr, align 8, !dbg !595
  %lz5 = getelementptr inbounds %struct.lzma_coder_s, %struct.lzma_coder_s* %12, i32 0, i32 1, !dbg !596
  %coder6 = getelementptr inbounds %struct.lzma_lz_decoder, %struct.lzma_lz_decoder* %lz5, i32 0, i32 0, !dbg !597
  %13 = load %struct.lzma_coder_s*, %struct.lzma_coder_s** %coder6, align 8, !dbg !597
  %14 = bitcast %struct.lzma_coder_s* %13 to i8*, !dbg !595
  %15 = load %struct.lzma_allocator*, %struct.lzma_allocator** %allocator.addr, align 8, !dbg !598
  call void @lzma_free(i8* %14, %struct.lzma_allocator* %15), !dbg !599
  br label %if.end

if.end:                                           ; preds = %if.else, %if.then
  %16 = load %struct.lzma_coder_s*, %struct.lzma_coder_s** %coder.addr, align 8, !dbg !600
  %17 = bitcast %struct.lzma_coder_s* %16 to i8*, !dbg !600
  %18 = load %struct.lzma_allocator*, %struct.lzma_allocator** %allocator.addr, align 8, !dbg !601
  call void @lzma_free(i8* %17, %struct.lzma_allocator* %18), !dbg !602
  ret void, !dbg !603
}

; Function Attrs: argmemonly nounwind
declare void @llvm.memcpy.p0i8.p0i8.i64(i8* nocapture, i8* nocapture readonly, i64, i32, i1) #3

declare void @lzma_free(i8*, %struct.lzma_allocator*) #2

; Function Attrs: nounwind uwtable
define internal void @lz_decoder_reset(%struct.lzma_coder_s* %coder) #0 !dbg !195 {
entry:
  %coder.addr = alloca %struct.lzma_coder_s*, align 8
  store %struct.lzma_coder_s* %coder, %struct.lzma_coder_s** %coder.addr, align 8
  call void @llvm.dbg.declare(metadata %struct.lzma_coder_s** %coder.addr, metadata !604, metadata !207), !dbg !605
  %0 = load %struct.lzma_coder_s*, %struct.lzma_coder_s** %coder.addr, align 8, !dbg !606
  %dict = getelementptr inbounds %struct.lzma_coder_s, %struct.lzma_coder_s* %0, i32 0, i32 0, !dbg !607
  %pos = getelementptr inbounds %struct.lzma_dict, %struct.lzma_dict* %dict, i32 0, i32 1, !dbg !608
  store i64 0, i64* %pos, align 8, !dbg !609
  %1 = load %struct.lzma_coder_s*, %struct.lzma_coder_s** %coder.addr, align 8, !dbg !610
  %dict1 = getelementptr inbounds %struct.lzma_coder_s, %struct.lzma_coder_s* %1, i32 0, i32 0, !dbg !611
  %full = getelementptr inbounds %struct.lzma_dict, %struct.lzma_dict* %dict1, i32 0, i32 2, !dbg !612
  store i64 0, i64* %full, align 8, !dbg !613
  %2 = load %struct.lzma_coder_s*, %struct.lzma_coder_s** %coder.addr, align 8, !dbg !614
  %dict2 = getelementptr inbounds %struct.lzma_coder_s, %struct.lzma_coder_s* %2, i32 0, i32 0, !dbg !615
  %size = getelementptr inbounds %struct.lzma_dict, %struct.lzma_dict* %dict2, i32 0, i32 4, !dbg !616
  %3 = load i64, i64* %size, align 8, !dbg !616
  %sub = sub i64 %3, 1, !dbg !617
  %4 = load %struct.lzma_coder_s*, %struct.lzma_coder_s** %coder.addr, align 8, !dbg !618
  %dict3 = getelementptr inbounds %struct.lzma_coder_s, %struct.lzma_coder_s* %4, i32 0, i32 0, !dbg !619
  %buf = getelementptr inbounds %struct.lzma_dict, %struct.lzma_dict* %dict3, i32 0, i32 0, !dbg !620
  %5 = load i8*, i8** %buf, align 8, !dbg !620
  %arrayidx = getelementptr inbounds i8, i8* %5, i64 %sub, !dbg !618
  store i8 0, i8* %arrayidx, align 1, !dbg !621
  %6 = load %struct.lzma_coder_s*, %struct.lzma_coder_s** %coder.addr, align 8, !dbg !622
  %dict4 = getelementptr inbounds %struct.lzma_coder_s, %struct.lzma_coder_s* %6, i32 0, i32 0, !dbg !623
  %need_reset = getelementptr inbounds %struct.lzma_dict, %struct.lzma_dict* %dict4, i32 0, i32 5, !dbg !624
  store i8 0, i8* %need_reset, align 8, !dbg !625
  ret void, !dbg !626
}

declare i32 @lzma_next_filter_init(%struct.lzma_next_coder_s*, %struct.lzma_allocator*, %struct.lzma_filter_info_s*) #2

; Function Attrs: nounwind uwtable
define i64 @lzma_lz_decoder_memusage(i64 %dictionary_size) #0 !dbg !186 {
entry:
  %dictionary_size.addr = alloca i64, align 8
  store i64 %dictionary_size, i64* %dictionary_size.addr, align 8
  call void @llvm.dbg.declare(metadata i64* %dictionary_size.addr, metadata !627, metadata !207), !dbg !628
  %0 = load i64, i64* %dictionary_size.addr, align 8, !dbg !629
  %add = add i64 4272, %0, !dbg !630
  ret i64 %add, !dbg !631
}

; Function Attrs: nounwind uwtable
define void @lzma_lz_decoder_uncompressed(%struct.lzma_coder_s* %coder, i64 %uncompressed_size) #0 !dbg !189 {
entry:
  %coder.addr = alloca %struct.lzma_coder_s*, align 8
  %uncompressed_size.addr = alloca i64, align 8
  store %struct.lzma_coder_s* %coder, %struct.lzma_coder_s** %coder.addr, align 8
  call void @llvm.dbg.declare(metadata %struct.lzma_coder_s** %coder.addr, metadata !632, metadata !207), !dbg !633
  store i64 %uncompressed_size, i64* %uncompressed_size.addr, align 8
  call void @llvm.dbg.declare(metadata i64* %uncompressed_size.addr, metadata !634, metadata !207), !dbg !635
  %0 = load %struct.lzma_coder_s*, %struct.lzma_coder_s** %coder.addr, align 8, !dbg !636
  %lz = getelementptr inbounds %struct.lzma_coder_s, %struct.lzma_coder_s* %0, i32 0, i32 1, !dbg !637
  %set_uncompressed = getelementptr inbounds %struct.lzma_lz_decoder, %struct.lzma_lz_decoder* %lz, i32 0, i32 3, !dbg !638
  %1 = load void (%struct.lzma_coder_s*, i64)*, void (%struct.lzma_coder_s*, i64)** %set_uncompressed, align 8, !dbg !638
  %2 = load %struct.lzma_coder_s*, %struct.lzma_coder_s** %coder.addr, align 8, !dbg !639
  %lz1 = getelementptr inbounds %struct.lzma_coder_s, %struct.lzma_coder_s* %2, i32 0, i32 1, !dbg !640
  %coder2 = getelementptr inbounds %struct.lzma_lz_decoder, %struct.lzma_lz_decoder* %lz1, i32 0, i32 0, !dbg !641
  %3 = load %struct.lzma_coder_s*, %struct.lzma_coder_s** %coder2, align 8, !dbg !641
  %4 = load i64, i64* %uncompressed_size.addr, align 8, !dbg !642
  call void %1(%struct.lzma_coder_s* %3, i64 %4), !dbg !636
  ret void, !dbg !643
}

; Function Attrs: nounwind uwtable
define internal i32 @decode_buffer(%struct.lzma_coder_s* %coder, i8* noalias %in, i64* noalias %in_pos, i64 %in_size, i8* noalias %out, i64* noalias %out_pos, i64 %out_size) #0 !dbg !191 {
entry:
  %retval = alloca i32, align 4
  %coder.addr = alloca %struct.lzma_coder_s*, align 8
  %in.addr = alloca i8*, align 8
  %in_pos.addr = alloca i64*, align 8
  %in_size.addr = alloca i64, align 8
  %out.addr = alloca i8*, align 8
  %out_pos.addr = alloca i64*, align 8
  %out_size.addr = alloca i64, align 8
  %copy_size = alloca i64, align 8
  %dict_start = alloca i64, align 8
  %ret = alloca i32, align 4
  store %struct.lzma_coder_s* %coder, %struct.lzma_coder_s** %coder.addr, align 8
  call void @llvm.dbg.declare(metadata %struct.lzma_coder_s** %coder.addr, metadata !644, metadata !207), !dbg !645
  store i8* %in, i8** %in.addr, align 8
  call void @llvm.dbg.declare(metadata i8** %in.addr, metadata !646, metadata !207), !dbg !647
  store i64* %in_pos, i64** %in_pos.addr, align 8
  call void @llvm.dbg.declare(metadata i64** %in_pos.addr, metadata !648, metadata !207), !dbg !649
  store i64 %in_size, i64* %in_size.addr, align 8
  call void @llvm.dbg.declare(metadata i64* %in_size.addr, metadata !650, metadata !207), !dbg !651
  store i8* %out, i8** %out.addr, align 8
  call void @llvm.dbg.declare(metadata i8** %out.addr, metadata !652, metadata !207), !dbg !653
  store i64* %out_pos, i64** %out_pos.addr, align 8
  call void @llvm.dbg.declare(metadata i64** %out_pos.addr, metadata !654, metadata !207), !dbg !655
  store i64 %out_size, i64* %out_size.addr, align 8
  call void @llvm.dbg.declare(metadata i64* %out_size.addr, metadata !656, metadata !207), !dbg !657
  br label %while.body, !dbg !658

while.body:                                       ; preds = %entry, %if.end52
  call void @llvm.dbg.declare(metadata i64* %copy_size, metadata !659, metadata !207), !dbg !661
  call void @llvm.dbg.declare(metadata i64* %dict_start, metadata !662, metadata !207), !dbg !663
  call void @llvm.dbg.declare(metadata i32* %ret, metadata !664, metadata !207), !dbg !665
  %0 = load %struct.lzma_coder_s*, %struct.lzma_coder_s** %coder.addr, align 8, !dbg !666
  %dict = getelementptr inbounds %struct.lzma_coder_s, %struct.lzma_coder_s* %0, i32 0, i32 0, !dbg !668
  %pos = getelementptr inbounds %struct.lzma_dict, %struct.lzma_dict* %dict, i32 0, i32 1, !dbg !669
  %1 = load i64, i64* %pos, align 8, !dbg !669
  %2 = load %struct.lzma_coder_s*, %struct.lzma_coder_s** %coder.addr, align 8, !dbg !670
  %dict1 = getelementptr inbounds %struct.lzma_coder_s, %struct.lzma_coder_s* %2, i32 0, i32 0, !dbg !671
  %size = getelementptr inbounds %struct.lzma_dict, %struct.lzma_dict* %dict1, i32 0, i32 4, !dbg !672
  %3 = load i64, i64* %size, align 8, !dbg !672
  %cmp = icmp eq i64 %1, %3, !dbg !673
  br i1 %cmp, label %if.then, label %if.end, !dbg !674

if.then:                                          ; preds = %while.body
  %4 = load %struct.lzma_coder_s*, %struct.lzma_coder_s** %coder.addr, align 8, !dbg !675
  %dict2 = getelementptr inbounds %struct.lzma_coder_s, %struct.lzma_coder_s* %4, i32 0, i32 0, !dbg !676
  %pos3 = getelementptr inbounds %struct.lzma_dict, %struct.lzma_dict* %dict2, i32 0, i32 1, !dbg !677
  store i64 0, i64* %pos3, align 8, !dbg !678
  br label %if.end, !dbg !675

if.end:                                           ; preds = %if.then, %while.body
  %5 = load %struct.lzma_coder_s*, %struct.lzma_coder_s** %coder.addr, align 8, !dbg !679
  %dict4 = getelementptr inbounds %struct.lzma_coder_s, %struct.lzma_coder_s* %5, i32 0, i32 0, !dbg !680
  %pos5 = getelementptr inbounds %struct.lzma_dict, %struct.lzma_dict* %dict4, i32 0, i32 1, !dbg !681
  %6 = load i64, i64* %pos5, align 8, !dbg !681
  store i64 %6, i64* %dict_start, align 8, !dbg !682
  %7 = load %struct.lzma_coder_s*, %struct.lzma_coder_s** %coder.addr, align 8, !dbg !683
  %dict6 = getelementptr inbounds %struct.lzma_coder_s, %struct.lzma_coder_s* %7, i32 0, i32 0, !dbg !684
  %pos7 = getelementptr inbounds %struct.lzma_dict, %struct.lzma_dict* %dict6, i32 0, i32 1, !dbg !685
  %8 = load i64, i64* %pos7, align 8, !dbg !685
  %9 = load i64, i64* %out_size.addr, align 8, !dbg !686
  %10 = load i64*, i64** %out_pos.addr, align 8, !dbg !686
  %11 = load i64, i64* %10, align 8, !dbg !686
  %sub = sub i64 %9, %11, !dbg !686
  %12 = load %struct.lzma_coder_s*, %struct.lzma_coder_s** %coder.addr, align 8, !dbg !686
  %dict8 = getelementptr inbounds %struct.lzma_coder_s, %struct.lzma_coder_s* %12, i32 0, i32 0, !dbg !686
  %size9 = getelementptr inbounds %struct.lzma_dict, %struct.lzma_dict* %dict8, i32 0, i32 4, !dbg !686
  %13 = load i64, i64* %size9, align 8, !dbg !686
  %14 = load %struct.lzma_coder_s*, %struct.lzma_coder_s** %coder.addr, align 8, !dbg !686
  %dict10 = getelementptr inbounds %struct.lzma_coder_s, %struct.lzma_coder_s* %14, i32 0, i32 0, !dbg !686
  %pos11 = getelementptr inbounds %struct.lzma_dict, %struct.lzma_dict* %dict10, i32 0, i32 1, !dbg !686
  %15 = load i64, i64* %pos11, align 8, !dbg !686
  %sub12 = sub i64 %13, %15, !dbg !686
  %cmp13 = icmp ult i64 %sub, %sub12, !dbg !686
  br i1 %cmp13, label %cond.true, label %cond.false, !dbg !686

cond.true:                                        ; preds = %if.end
  %16 = load i64, i64* %out_size.addr, align 8, !dbg !687
  %17 = load i64*, i64** %out_pos.addr, align 8, !dbg !687
  %18 = load i64, i64* %17, align 8, !dbg !687
  %sub14 = sub i64 %16, %18, !dbg !687
  br label %cond.end, !dbg !687

cond.false:                                       ; preds = %if.end
  %19 = load %struct.lzma_coder_s*, %struct.lzma_coder_s** %coder.addr, align 8, !dbg !689
  %dict15 = getelementptr inbounds %struct.lzma_coder_s, %struct.lzma_coder_s* %19, i32 0, i32 0, !dbg !689
  %size16 = getelementptr inbounds %struct.lzma_dict, %struct.lzma_dict* %dict15, i32 0, i32 4, !dbg !689
  %20 = load i64, i64* %size16, align 8, !dbg !689
  %21 = load %struct.lzma_coder_s*, %struct.lzma_coder_s** %coder.addr, align 8, !dbg !689
  %dict17 = getelementptr inbounds %struct.lzma_coder_s, %struct.lzma_coder_s* %21, i32 0, i32 0, !dbg !689
  %pos18 = getelementptr inbounds %struct.lzma_dict, %struct.lzma_dict* %dict17, i32 0, i32 1, !dbg !689
  %22 = load i64, i64* %pos18, align 8, !dbg !689
  %sub19 = sub i64 %20, %22, !dbg !689
  br label %cond.end, !dbg !689

cond.end:                                         ; preds = %cond.false, %cond.true
  %cond = phi i64 [ %sub14, %cond.true ], [ %sub19, %cond.false ], !dbg !691
  %add = add i64 %8, %cond, !dbg !693
  %23 = load %struct.lzma_coder_s*, %struct.lzma_coder_s** %coder.addr, align 8, !dbg !694
  %dict20 = getelementptr inbounds %struct.lzma_coder_s, %struct.lzma_coder_s* %23, i32 0, i32 0, !dbg !695
  %limit = getelementptr inbounds %struct.lzma_dict, %struct.lzma_dict* %dict20, i32 0, i32 3, !dbg !696
  store i64 %add, i64* %limit, align 8, !dbg !697
  %24 = load %struct.lzma_coder_s*, %struct.lzma_coder_s** %coder.addr, align 8, !dbg !698
  %lz = getelementptr inbounds %struct.lzma_coder_s, %struct.lzma_coder_s* %24, i32 0, i32 1, !dbg !699
  %code = getelementptr inbounds %struct.lzma_lz_decoder, %struct.lzma_lz_decoder* %lz, i32 0, i32 1, !dbg !700
  %25 = load i32 (%struct.lzma_coder_s*, %struct.lzma_dict*, i8*, i64*, i64)*, i32 (%struct.lzma_coder_s*, %struct.lzma_dict*, i8*, i64*, i64)** %code, align 8, !dbg !700
  %26 = load %struct.lzma_coder_s*, %struct.lzma_coder_s** %coder.addr, align 8, !dbg !701
  %lz21 = getelementptr inbounds %struct.lzma_coder_s, %struct.lzma_coder_s* %26, i32 0, i32 1, !dbg !702
  %coder22 = getelementptr inbounds %struct.lzma_lz_decoder, %struct.lzma_lz_decoder* %lz21, i32 0, i32 0, !dbg !703
  %27 = load %struct.lzma_coder_s*, %struct.lzma_coder_s** %coder22, align 8, !dbg !703
  %28 = load %struct.lzma_coder_s*, %struct.lzma_coder_s** %coder.addr, align 8, !dbg !704
  %dict23 = getelementptr inbounds %struct.lzma_coder_s, %struct.lzma_coder_s* %28, i32 0, i32 0, !dbg !705
  %29 = load i8*, i8** %in.addr, align 8, !dbg !706
  %30 = load i64*, i64** %in_pos.addr, align 8, !dbg !707
  %31 = load i64, i64* %in_size.addr, align 8, !dbg !708
  %call = call i32 %25(%struct.lzma_coder_s* %27, %struct.lzma_dict* %dict23, i8* %29, i64* %30, i64 %31), !dbg !698
  store i32 %call, i32* %ret, align 4, !dbg !709
  %32 = load %struct.lzma_coder_s*, %struct.lzma_coder_s** %coder.addr, align 8, !dbg !710
  %dict24 = getelementptr inbounds %struct.lzma_coder_s, %struct.lzma_coder_s* %32, i32 0, i32 0, !dbg !711
  %pos25 = getelementptr inbounds %struct.lzma_dict, %struct.lzma_dict* %dict24, i32 0, i32 1, !dbg !712
  %33 = load i64, i64* %pos25, align 8, !dbg !712
  %34 = load i64, i64* %dict_start, align 8, !dbg !713
  %sub26 = sub i64 %33, %34, !dbg !714
  store i64 %sub26, i64* %copy_size, align 8, !dbg !715
  %35 = load i64, i64* %copy_size, align 8, !dbg !716
  %36 = load i64, i64* %out_size.addr, align 8, !dbg !716
  %37 = load i64*, i64** %out_pos.addr, align 8, !dbg !716
  %38 = load i64, i64* %37, align 8, !dbg !716
  %sub27 = sub i64 %36, %38, !dbg !716
  %cmp28 = icmp ule i64 %35, %sub27, !dbg !716
  br i1 %cmp28, label %cond.true29, label %cond.false30, !dbg !716

cond.true29:                                      ; preds = %cond.end
  br label %cond.end31, !dbg !717

cond.false30:                                     ; preds = %cond.end
  call void @__assert_fail(i8* getelementptr inbounds ([33 x i8], [33 x i8]* @.str, i32 0, i32 0), i8* getelementptr inbounds ([78 x i8], [78 x i8]* @.str.1, i32 0, i32 0), i32 100, i8* getelementptr inbounds ([133 x i8], [133 x i8]* @__PRETTY_FUNCTION__.decode_buffer, i32 0, i32 0)) #5, !dbg !718
  unreachable, !dbg !718
                                                  ; No predecessors!
  br label %cond.end31, !dbg !719

cond.end31:                                       ; preds = %39, %cond.true29
  %40 = load i8*, i8** %out.addr, align 8, !dbg !720
  %41 = load i64*, i64** %out_pos.addr, align 8, !dbg !721
  %42 = load i64, i64* %41, align 8, !dbg !722
  %add.ptr = getelementptr inbounds i8, i8* %40, i64 %42, !dbg !723
  %43 = load %struct.lzma_coder_s*, %struct.lzma_coder_s** %coder.addr, align 8, !dbg !724
  %dict32 = getelementptr inbounds %struct.lzma_coder_s, %struct.lzma_coder_s* %43, i32 0, i32 0, !dbg !725
  %buf = getelementptr inbounds %struct.lzma_dict, %struct.lzma_dict* %dict32, i32 0, i32 0, !dbg !726
  %44 = load i8*, i8** %buf, align 8, !dbg !726
  %45 = load i64, i64* %dict_start, align 8, !dbg !727
  %add.ptr33 = getelementptr inbounds i8, i8* %44, i64 %45, !dbg !728
  %46 = load i64, i64* %copy_size, align 8, !dbg !729
  call void @llvm.memcpy.p0i8.p0i8.i64(i8* %add.ptr, i8* %add.ptr33, i64 %46, i32 1, i1 false), !dbg !730
  %47 = load i64, i64* %copy_size, align 8, !dbg !731
  %48 = load i64*, i64** %out_pos.addr, align 8, !dbg !732
  %49 = load i64, i64* %48, align 8, !dbg !733
  %add34 = add i64 %49, %47, !dbg !733
  store i64 %add34, i64* %48, align 8, !dbg !733
  %50 = load %struct.lzma_coder_s*, %struct.lzma_coder_s** %coder.addr, align 8, !dbg !734
  %dict35 = getelementptr inbounds %struct.lzma_coder_s, %struct.lzma_coder_s* %50, i32 0, i32 0, !dbg !736
  %need_reset = getelementptr inbounds %struct.lzma_dict, %struct.lzma_dict* %dict35, i32 0, i32 5, !dbg !737
  %51 = load i8, i8* %need_reset, align 8, !dbg !737
  %tobool = trunc i8 %51 to i1, !dbg !737
  br i1 %tobool, label %if.then36, label %if.else, !dbg !738

if.then36:                                        ; preds = %cond.end31
  %52 = load %struct.lzma_coder_s*, %struct.lzma_coder_s** %coder.addr, align 8, !dbg !739
  call void @lz_decoder_reset(%struct.lzma_coder_s* %52), !dbg !741
  %53 = load i32, i32* %ret, align 4, !dbg !742
  %cmp37 = icmp ne i32 %53, 0, !dbg !744
  br i1 %cmp37, label %if.then39, label %lor.lhs.false, !dbg !745

lor.lhs.false:                                    ; preds = %if.then36
  %54 = load i64*, i64** %out_pos.addr, align 8, !dbg !746
  %55 = load i64, i64* %54, align 8, !dbg !748
  %56 = load i64, i64* %out_size.addr, align 8, !dbg !749
  %cmp38 = icmp eq i64 %55, %56, !dbg !750
  br i1 %cmp38, label %if.then39, label %if.end40, !dbg !751

if.then39:                                        ; preds = %lor.lhs.false, %if.then36
  %57 = load i32, i32* %ret, align 4, !dbg !752
  store i32 %57, i32* %retval, align 4, !dbg !753
  br label %return, !dbg !753

if.end40:                                         ; preds = %lor.lhs.false
  br label %if.end52, !dbg !754

if.else:                                          ; preds = %cond.end31
  %58 = load i32, i32* %ret, align 4, !dbg !755
  %cmp41 = icmp ne i32 %58, 0, !dbg !758
  br i1 %cmp41, label %if.then50, label %lor.lhs.false42, !dbg !759

lor.lhs.false42:                                  ; preds = %if.else
  %59 = load i64*, i64** %out_pos.addr, align 8, !dbg !760
  %60 = load i64, i64* %59, align 8, !dbg !762
  %61 = load i64, i64* %out_size.addr, align 8, !dbg !763
  %cmp43 = icmp eq i64 %60, %61, !dbg !764
  br i1 %cmp43, label %if.then50, label %lor.lhs.false44, !dbg !765

lor.lhs.false44:                                  ; preds = %lor.lhs.false42
  %62 = load %struct.lzma_coder_s*, %struct.lzma_coder_s** %coder.addr, align 8, !dbg !766
  %dict45 = getelementptr inbounds %struct.lzma_coder_s, %struct.lzma_coder_s* %62, i32 0, i32 0, !dbg !767
  %pos46 = getelementptr inbounds %struct.lzma_dict, %struct.lzma_dict* %dict45, i32 0, i32 1, !dbg !768
  %63 = load i64, i64* %pos46, align 8, !dbg !768
  %64 = load %struct.lzma_coder_s*, %struct.lzma_coder_s** %coder.addr, align 8, !dbg !769
  %dict47 = getelementptr inbounds %struct.lzma_coder_s, %struct.lzma_coder_s* %64, i32 0, i32 0, !dbg !770
  %size48 = getelementptr inbounds %struct.lzma_dict, %struct.lzma_dict* %dict47, i32 0, i32 4, !dbg !771
  %65 = load i64, i64* %size48, align 8, !dbg !771
  %cmp49 = icmp ult i64 %63, %65, !dbg !772
  br i1 %cmp49, label %if.then50, label %if.end51, !dbg !773

if.then50:                                        ; preds = %lor.lhs.false44, %lor.lhs.false42, %if.else
  %66 = load i32, i32* %ret, align 4, !dbg !775
  store i32 %66, i32* %retval, align 4, !dbg !776
  br label %return, !dbg !776

if.end51:                                         ; preds = %lor.lhs.false44
  br label %if.end52

if.end52:                                         ; preds = %if.end51, %if.end40
  br label %while.body, !dbg !777

return:                                           ; preds = %if.then50, %if.then39
  %67 = load i32, i32* %retval, align 4, !dbg !779
  ret i32 %67, !dbg !779
}

; Function Attrs: noreturn nounwind
declare void @__assert_fail(i8*, i8*, i32, i8*) #4

declare void @lzma_next_end(%struct.lzma_next_coder_s*, %struct.lzma_allocator*) #2

attributes #0 = { nounwind uwtable "disable-tail-calls"="false" "less-precise-fpmad"="false" "no-frame-pointer-elim"="true" "no-frame-pointer-elim-non-leaf" "no-infs-fp-math"="false" "no-nans-fp-math"="false" "stack-protector-buffer-size"="8" "target-cpu"="x86-64" "target-features"="+fxsr,+mmx,+sse,+sse2" "unsafe-fp-math"="false" "use-soft-float"="false" }
attributes #1 = { nounwind readnone }
attributes #2 = { "disable-tail-calls"="false" "less-precise-fpmad"="false" "no-frame-pointer-elim"="true" "no-frame-pointer-elim-non-leaf" "no-infs-fp-math"="false" "no-nans-fp-math"="false" "stack-protector-buffer-size"="8" "target-cpu"="x86-64" "target-features"="+fxsr,+mmx,+sse,+sse2" "unsafe-fp-math"="false" "use-soft-float"="false" }
attributes #3 = { argmemonly nounwind }
attributes #4 = { noreturn nounwind "disable-tail-calls"="false" "less-precise-fpmad"="false" "no-frame-pointer-elim"="true" "no-frame-pointer-elim-non-leaf" "no-infs-fp-math"="false" "no-nans-fp-math"="false" "stack-protector-buffer-size"="8" "target-cpu"="x86-64" "target-features"="+fxsr,+mmx,+sse,+sse2" "unsafe-fp-math"="false" "use-soft-float"="false" }
attributes #5 = { noreturn nounwind }

!llvm.dbg.cu = !{!0}
!llvm.module.flags = !{!203, !204}
!llvm.ident = !{!205}

!0 = distinct !DICompileUnit(language: DW_LANG_C99, file: !1, producer: "clang version 3.8.0 (tags/RELEASE_380/final)", isOptimized: false, runtimeVersion: 0, emissionKind: 1, enums: !2, retainedTypes: !31, subprograms: !38, globals: !198)
!1 = !DIFile(filename: "/data/download/cmake/cmake-master/Utilities/cmliblzma/liblzma/lz/lz_decoder.c", directory: "/data/download/cmake/cmake-master/Utilities/cmliblzma")
!2 = !{!3, !18, !24}
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
!18 = !DICompositeType(tag: DW_TAG_enumeration_type, file: !4, line: 250, size: 32, align: 32, elements: !19)
!19 = !{!20, !21, !22, !23}
!20 = !DIEnumerator(name: "LZMA_RUN", value: 0)
!21 = !DIEnumerator(name: "LZMA_SYNC_FLUSH", value: 1)
!22 = !DIEnumerator(name: "LZMA_FULL_FLUSH", value: 2)
!23 = !DIEnumerator(name: "LZMA_FINISH", value: 3)
!24 = !DICompositeType(tag: DW_TAG_enumeration_type, file: !25, line: 27, size: 32, align: 32, elements: !26)
!25 = !DIFile(filename: "/data/download/cmake/cmake-master/Utilities/cmliblzma/liblzma/api/lzma/check.h", directory: "/data/download/cmake/cmake-master/Utilities/cmliblzma")
!26 = !{!27, !28, !29, !30}
!27 = !DIEnumerator(name: "LZMA_CHECK_NONE", value: 0)
!28 = !DIEnumerator(name: "LZMA_CHECK_CRC32", value: 1)
!29 = !DIEnumerator(name: "LZMA_CHECK_CRC64", value: 4)
!30 = !DIEnumerator(name: "LZMA_CHECK_SHA256", value: 10)
!31 = !{!32, !33, !36}
!32 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: null, size: 64, align: 64)
!33 = !DIDerivedType(tag: DW_TAG_typedef, name: "size_t", file: !34, line: 62, baseType: !35)
!34 = !DIFile(filename: "/opt/llvm-build/bin/../lib/clang/3.8.0/include/stddef.h", directory: "/data/download/cmake/cmake-master/Utilities/cmliblzma")
!35 = !DIBasicType(name: "long unsigned int", size: 64, align: 64, encoding: DW_ATE_unsigned)
!36 = !DIDerivedType(tag: DW_TAG_typedef, name: "uint64_t", file: !37, line: 55, baseType: !35)
!37 = !DIFile(filename: "/usr/include/stdint.h", directory: "/data/download/cmake/cmake-master/Utilities/cmliblzma")
!38 = !{!39, !186, !189, !190, !191, !194, !195}
!39 = distinct !DISubprogram(name: "lzma_lz_decoder_init", scope: !1, file: !1, line: 209, type: !40, isLocal: false, isDefinition: true, scopeLine: 214, flags: DIFlagPrototyped, isOptimized: false, variables: !185)
!40 = !DISubroutineType(types: !41)
!41 = !{!42, !43, !101, !162, !174}
!42 = !DIDerivedType(tag: DW_TAG_typedef, name: "lzma_ret", file: !4, line: 237, baseType: !3)
!43 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !44, size: 64, align: 64)
!44 = !DIDerivedType(tag: DW_TAG_typedef, name: "lzma_next_coder", file: !45, line: 75, baseType: !46)
!45 = !DIFile(filename: "/data/download/cmake/cmake-master/Utilities/cmliblzma/liblzma/common/common.h", directory: "/data/download/cmake/cmake-master/Utilities/cmliblzma")
!46 = !DICompositeType(tag: DW_TAG_structure_type, name: "lzma_next_coder_s", file: !45, line: 119, size: 512, align: 64, elements: !47)
!47 = !{!48, !126, !127, !129, !136, !138, !145, !150}
!48 = !DIDerivedType(tag: DW_TAG_member, name: "coder", scope: !46, file: !45, line: 121, baseType: !49, size: 64, align: 64)
!49 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !50, size: 64, align: 64)
!50 = !DIDerivedType(tag: DW_TAG_typedef, name: "lzma_coder", file: !45, line: 73, baseType: !51)
!51 = !DICompositeType(tag: DW_TAG_structure_type, name: "lzma_coder_s", file: !1, line: 23, size: 34176, align: 64, elements: !52)
!52 = !{!53, !68, !114, !115, !116, !117}
!53 = !DIDerivedType(tag: DW_TAG_member, name: "dict", scope: !51, file: !1, line: 25, baseType: !54, size: 384, align: 64)
!54 = !DIDerivedType(tag: DW_TAG_typedef, name: "lzma_dict", file: !55, line: 44, baseType: !56)
!55 = !DIFile(filename: "/data/download/cmake/cmake-master/Utilities/cmliblzma/liblzma/lz/lz_decoder.h", directory: "/data/download/cmake/cmake-master/Utilities/cmliblzma")
!56 = !DICompositeType(tag: DW_TAG_structure_type, file: !55, line: 20, size: 384, align: 64, elements: !57)
!57 = !{!58, !62, !63, !64, !65, !66}
!58 = !DIDerivedType(tag: DW_TAG_member, name: "buf", scope: !56, file: !55, line: 24, baseType: !59, size: 64, align: 64)
!59 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !60, size: 64, align: 64)
!60 = !DIDerivedType(tag: DW_TAG_typedef, name: "uint8_t", file: !37, line: 48, baseType: !61)
!61 = !DIBasicType(name: "unsigned char", size: 8, align: 8, encoding: DW_ATE_unsigned_char)
!62 = !DIDerivedType(tag: DW_TAG_member, name: "pos", scope: !56, file: !55, line: 28, baseType: !33, size: 64, align: 64, offset: 64)
!63 = !DIDerivedType(tag: DW_TAG_member, name: "full", scope: !56, file: !55, line: 33, baseType: !33, size: 64, align: 64, offset: 128)
!64 = !DIDerivedType(tag: DW_TAG_member, name: "limit", scope: !56, file: !55, line: 36, baseType: !33, size: 64, align: 64, offset: 192)
!65 = !DIDerivedType(tag: DW_TAG_member, name: "size", scope: !56, file: !55, line: 39, baseType: !33, size: 64, align: 64, offset: 256)
!66 = !DIDerivedType(tag: DW_TAG_member, name: "need_reset", scope: !56, file: !55, line: 42, baseType: !67, size: 8, align: 8, offset: 320)
!67 = !DIBasicType(name: "_Bool", size: 8, align: 8, encoding: DW_ATE_boolean)
!68 = !DIDerivedType(tag: DW_TAG_member, name: "lz", scope: !51, file: !1, line: 28, baseType: !69, size: 320, align: 64, offset: 384)
!69 = !DIDerivedType(tag: DW_TAG_typedef, name: "lzma_lz_decoder", file: !55, line: 72, baseType: !70)
!70 = !DICompositeType(tag: DW_TAG_structure_type, file: !55, line: 54, size: 320, align: 64, elements: !71)
!71 = !{!72, !73, !85, !91, !97}
!72 = !DIDerivedType(tag: DW_TAG_member, name: "coder", scope: !70, file: !55, line: 56, baseType: !49, size: 64, align: 64)
!73 = !DIDerivedType(tag: DW_TAG_member, name: "code", scope: !70, file: !55, line: 59, baseType: !74, size: 64, align: 64, offset: 64)
!74 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !75, size: 64, align: 64)
!75 = !DISubroutineType(types: !76)
!76 = !{!42, !77, !78, !80, !83, !33}
!77 = !DIDerivedType(tag: DW_TAG_restrict_type, baseType: !49)
!78 = !DIDerivedType(tag: DW_TAG_restrict_type, baseType: !79)
!79 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !54, size: 64, align: 64)
!80 = !DIDerivedType(tag: DW_TAG_restrict_type, baseType: !81)
!81 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !82, size: 64, align: 64)
!82 = !DIDerivedType(tag: DW_TAG_const_type, baseType: !60)
!83 = !DIDerivedType(tag: DW_TAG_restrict_type, baseType: !84)
!84 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !33, size: 64, align: 64)
!85 = !DIDerivedType(tag: DW_TAG_member, name: "reset", scope: !70, file: !55, line: 63, baseType: !86, size: 64, align: 64, offset: 128)
!86 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !87, size: 64, align: 64)
!87 = !DISubroutineType(types: !88)
!88 = !{null, !49, !89}
!89 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !90, size: 64, align: 64)
!90 = !DIDerivedType(tag: DW_TAG_const_type, baseType: null)
!91 = !DIDerivedType(tag: DW_TAG_member, name: "set_uncompressed", scope: !70, file: !55, line: 66, baseType: !92, size: 64, align: 64, offset: 192)
!92 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !93, size: 64, align: 64)
!93 = !DISubroutineType(types: !94)
!94 = !{null, !49, !95}
!95 = !DIDerivedType(tag: DW_TAG_typedef, name: "lzma_vli", file: !96, line: 63, baseType: !36)
!96 = !DIFile(filename: "/data/download/cmake/cmake-master/Utilities/cmliblzma/liblzma/api/lzma/vli.h", directory: "/data/download/cmake/cmake-master/Utilities/cmliblzma")
!97 = !DIDerivedType(tag: DW_TAG_member, name: "end", scope: !70, file: !55, line: 70, baseType: !98, size: 64, align: 64, offset: 256)
!98 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !99, size: 64, align: 64)
!99 = !DISubroutineType(types: !100)
!100 = !{null, !49, !101}
!101 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !102, size: 64, align: 64)
!102 = !DIDerivedType(tag: DW_TAG_typedef, name: "lzma_allocator", file: !4, line: 403, baseType: !103)
!103 = !DICompositeType(tag: DW_TAG_structure_type, file: !4, line: 341, size: 192, align: 64, elements: !104)
!104 = !{!105, !109, !113}
!105 = !DIDerivedType(tag: DW_TAG_member, name: "alloc", scope: !103, file: !4, line: 376, baseType: !106, size: 64, align: 64)
!106 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !107, size: 64, align: 64)
!107 = !DISubroutineType(types: !108)
!108 = !{!32, !32, !33, !33}
!109 = !DIDerivedType(tag: DW_TAG_member, name: "free", scope: !103, file: !4, line: 390, baseType: !110, size: 64, align: 64, offset: 64)
!110 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !111, size: 64, align: 64)
!111 = !DISubroutineType(types: !112)
!112 = !{null, !32, !32}
!113 = !DIDerivedType(tag: DW_TAG_member, name: "opaque", scope: !103, file: !4, line: 401, baseType: !32, size: 64, align: 64, offset: 128)
!114 = !DIDerivedType(tag: DW_TAG_member, name: "next", scope: !51, file: !1, line: 33, baseType: !44, size: 512, align: 64, offset: 704)
!115 = !DIDerivedType(tag: DW_TAG_member, name: "next_finished", scope: !51, file: !1, line: 36, baseType: !67, size: 8, align: 8, offset: 1216)
!116 = !DIDerivedType(tag: DW_TAG_member, name: "this_finished", scope: !51, file: !1, line: 40, baseType: !67, size: 8, align: 8, offset: 1224)
!117 = !DIDerivedType(tag: DW_TAG_member, name: "temp", scope: !51, file: !1, line: 50, baseType: !118, size: 32896, align: 64, offset: 1280)
!118 = !DICompositeType(tag: DW_TAG_structure_type, scope: !51, file: !1, line: 46, size: 32896, align: 64, elements: !119)
!119 = !{!120, !121, !122}
!120 = !DIDerivedType(tag: DW_TAG_member, name: "pos", scope: !118, file: !1, line: 47, baseType: !33, size: 64, align: 64)
!121 = !DIDerivedType(tag: DW_TAG_member, name: "size", scope: !118, file: !1, line: 48, baseType: !33, size: 64, align: 64, offset: 64)
!122 = !DIDerivedType(tag: DW_TAG_member, name: "buffer", scope: !118, file: !1, line: 49, baseType: !123, size: 32768, align: 8, offset: 128)
!123 = !DICompositeType(tag: DW_TAG_array_type, baseType: !60, size: 32768, align: 8, elements: !124)
!124 = !{!125}
!125 = !DISubrange(count: 4096)
!126 = !DIDerivedType(tag: DW_TAG_member, name: "id", scope: !46, file: !45, line: 125, baseType: !95, size: 64, align: 64, offset: 64)
!127 = !DIDerivedType(tag: DW_TAG_member, name: "init", scope: !46, file: !45, line: 131, baseType: !128, size: 64, align: 64, offset: 128)
!128 = !DIDerivedType(tag: DW_TAG_typedef, name: "uintptr_t", file: !37, line: 122, baseType: !35)
!129 = !DIDerivedType(tag: DW_TAG_member, name: "code", scope: !46, file: !45, line: 134, baseType: !130, size: 64, align: 64, offset: 192)
!130 = !DIDerivedType(tag: DW_TAG_typedef, name: "lzma_code_function", file: !45, line: 89, baseType: !131)
!131 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !132, size: 64, align: 64)
!132 = !DISubroutineType(types: !133)
!133 = !{!42, !49, !101, !80, !83, !33, !134, !83, !33, !135}
!134 = !DIDerivedType(tag: DW_TAG_restrict_type, baseType: !59)
!135 = !DIDerivedType(tag: DW_TAG_typedef, name: "lzma_action", file: !4, line: 322, baseType: !18)
!136 = !DIDerivedType(tag: DW_TAG_member, name: "end", scope: !46, file: !45, line: 139, baseType: !137, size: 64, align: 64, offset: 256)
!137 = !DIDerivedType(tag: DW_TAG_typedef, name: "lzma_end_function", file: !45, line: 97, baseType: !98)
!138 = !DIDerivedType(tag: DW_TAG_member, name: "get_check", scope: !46, file: !45, line: 143, baseType: !139, size: 64, align: 64, offset: 320)
!139 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !140, size: 64, align: 64)
!140 = !DISubroutineType(types: !141)
!141 = !{!142, !143}
!142 = !DIDerivedType(tag: DW_TAG_typedef, name: "lzma_check", file: !25, line: 55, baseType: !24)
!143 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !144, size: 64, align: 64)
!144 = !DIDerivedType(tag: DW_TAG_const_type, baseType: !50)
!145 = !DIDerivedType(tag: DW_TAG_member, name: "memconfig", scope: !46, file: !45, line: 147, baseType: !146, size: 64, align: 64, offset: 384)
!146 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !147, size: 64, align: 64)
!147 = !DISubroutineType(types: !148)
!148 = !{!42, !49, !149, !149, !36}
!149 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !36, size: 64, align: 64)
!150 = !DIDerivedType(tag: DW_TAG_member, name: "update", scope: !46, file: !45, line: 152, baseType: !151, size: 64, align: 64, offset: 448)
!151 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !152, size: 64, align: 64)
!152 = !DISubroutineType(types: !153)
!153 = !{!42, !49, !101, !154, !154}
!154 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !155, size: 64, align: 64)
!155 = !DIDerivedType(tag: DW_TAG_const_type, baseType: !156)
!156 = !DIDerivedType(tag: DW_TAG_typedef, name: "lzma_filter", file: !157, line: 65, baseType: !158)
!157 = !DIFile(filename: "/data/download/cmake/cmake-master/Utilities/cmliblzma/liblzma/api/lzma/filter.h", directory: "/data/download/cmake/cmake-master/Utilities/cmliblzma")
!158 = !DICompositeType(tag: DW_TAG_structure_type, file: !157, line: 43, size: 128, align: 64, elements: !159)
!159 = !{!160, !161}
!160 = !DIDerivedType(tag: DW_TAG_member, name: "id", scope: !158, file: !157, line: 54, baseType: !95, size: 64, align: 64)
!161 = !DIDerivedType(tag: DW_TAG_member, name: "options", scope: !158, file: !157, line: 63, baseType: !32, size: 64, align: 64, offset: 64)
!162 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !163, size: 64, align: 64)
!163 = !DIDerivedType(tag: DW_TAG_const_type, baseType: !164)
!164 = !DIDerivedType(tag: DW_TAG_typedef, name: "lzma_filter_info", file: !45, line: 77, baseType: !165)
!165 = !DICompositeType(tag: DW_TAG_structure_type, name: "lzma_filter_info_s", file: !45, line: 104, size: 192, align: 64, elements: !166)
!166 = !{!167, !168, !173}
!167 = !DIDerivedType(tag: DW_TAG_member, name: "id", scope: !165, file: !45, line: 107, baseType: !95, size: 64, align: 64)
!168 = !DIDerivedType(tag: DW_TAG_member, name: "init", scope: !165, file: !45, line: 111, baseType: !169, size: 64, align: 64, offset: 64)
!169 = !DIDerivedType(tag: DW_TAG_typedef, name: "lzma_init_function", file: !45, line: 81, baseType: !170)
!170 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !171, size: 64, align: 64)
!171 = !DISubroutineType(types: !172)
!172 = !{!42, !43, !101, !162}
!173 = !DIDerivedType(tag: DW_TAG_member, name: "options", scope: !165, file: !45, line: 114, baseType: !32, size: 64, align: 64, offset: 128)
!174 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !175, size: 64, align: 64)
!175 = !DISubroutineType(types: !176)
!176 = !{!42, !177, !101, !89, !178}
!177 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !69, size: 64, align: 64)
!178 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !179, size: 64, align: 64)
!179 = !DIDerivedType(tag: DW_TAG_typedef, name: "lzma_lz_options", file: !55, line: 51, baseType: !180)
!180 = !DICompositeType(tag: DW_TAG_structure_type, file: !55, line: 47, size: 192, align: 64, elements: !181)
!181 = !{!182, !183, !184}
!182 = !DIDerivedType(tag: DW_TAG_member, name: "dict_size", scope: !180, file: !55, line: 48, baseType: !33, size: 64, align: 64)
!183 = !DIDerivedType(tag: DW_TAG_member, name: "preset_dict", scope: !180, file: !55, line: 49, baseType: !81, size: 64, align: 64, offset: 64)
!184 = !DIDerivedType(tag: DW_TAG_member, name: "preset_dict_size", scope: !180, file: !55, line: 50, baseType: !33, size: 64, align: 64, offset: 128)
!185 = !{}
!186 = distinct !DISubprogram(name: "lzma_lz_decoder_memusage", scope: !1, file: !1, line: 297, type: !187, isLocal: false, isDefinition: true, scopeLine: 298, flags: DIFlagPrototyped, isOptimized: false, variables: !185)
!187 = !DISubroutineType(types: !188)
!188 = !{!36, !33}
!189 = distinct !DISubprogram(name: "lzma_lz_decoder_uncompressed", scope: !1, file: !1, line: 304, type: !93, isLocal: false, isDefinition: true, scopeLine: 305, flags: DIFlagPrototyped, isOptimized: false, variables: !185)
!190 = distinct !DISubprogram(name: "lz_decode", scope: !1, file: !1, line: 132, type: !132, isLocal: true, isDefinition: true, scopeLine: 138, flags: DIFlagPrototyped, isOptimized: false, variables: !185)
!191 = distinct !DISubprogram(name: "decode_buffer", scope: !1, file: !1, line: 66, type: !192, isLocal: true, isDefinition: true, scopeLine: 70, flags: DIFlagPrototyped, isOptimized: false, variables: !185)
!192 = !DISubroutineType(types: !193)
!193 = !{!42, !49, !80, !83, !33, !134, !83, !33}
!194 = distinct !DISubprogram(name: "lz_decoder_end", scope: !1, file: !1, line: 193, type: !99, isLocal: true, isDefinition: true, scopeLine: 194, flags: DIFlagPrototyped, isOptimized: false, variables: !185)
!195 = distinct !DISubprogram(name: "lz_decoder_reset", scope: !1, file: !1, line: 55, type: !196, isLocal: true, isDefinition: true, scopeLine: 56, flags: DIFlagPrototyped, isOptimized: false, variables: !185)
!196 = !DISubroutineType(types: !197)
!197 = !{null, !49}
!198 = !{!199, !201}
!199 = !DIGlobalVariable(name: "LZMA_LZ_DECODER_INIT", scope: !0, file: !55, line: 75, type: !200, isLocal: true, isDefinition: true, variable: %struct.lzma_lz_decoder* @LZMA_LZ_DECODER_INIT)
!200 = !DIDerivedType(tag: DW_TAG_const_type, baseType: !69)
!201 = !DIGlobalVariable(name: "LZMA_NEXT_CODER_INIT", scope: !0, file: !45, line: 159, type: !202, isLocal: true, isDefinition: true, variable: %struct.lzma_next_coder_s* @LZMA_NEXT_CODER_INIT)
!202 = !DIDerivedType(tag: DW_TAG_const_type, baseType: !44)
!203 = !{i32 2, !"Dwarf Version", i32 4}
!204 = !{i32 2, !"Debug Info Version", i32 3}
!205 = !{!"clang version 3.8.0 (tags/RELEASE_380/final)"}
!206 = !DILocalVariable(name: "next", arg: 1, scope: !39, file: !1, line: 209, type: !43)
!207 = !DIExpression()
!208 = !DILocation(line: 209, column: 39, scope: !39)
!209 = !DILocalVariable(name: "allocator", arg: 2, scope: !39, file: !1, line: 209, type: !101)
!210 = !DILocation(line: 209, column: 61, scope: !39)
!211 = !DILocalVariable(name: "filters", arg: 3, scope: !39, file: !1, line: 210, type: !162)
!212 = !DILocation(line: 210, column: 27, scope: !39)
!213 = !DILocalVariable(name: "lz_init", arg: 4, scope: !39, file: !1, line: 211, type: !174)
!214 = !DILocation(line: 211, column: 14, scope: !39)
!215 = !DILocalVariable(name: "lz_options", scope: !39, file: !1, line: 215, type: !179)
!216 = !DILocation(line: 215, column: 18, scope: !39)
!217 = !DILocation(line: 218, column: 6, scope: !218)
!218 = distinct !DILexicalBlock(scope: !39, file: !1, line: 218, column: 6)
!219 = !DILocation(line: 218, column: 12, scope: !218)
!220 = !DILocation(line: 218, column: 18, scope: !218)
!221 = !DILocation(line: 218, column: 6, scope: !39)
!222 = !DILocation(line: 219, column: 48, scope: !223)
!223 = distinct !DILexicalBlock(scope: !218, file: !1, line: 218, column: 27)
!224 = !DILocation(line: 219, column: 17, scope: !223)
!225 = !DILocation(line: 219, column: 3, scope: !223)
!226 = !DILocation(line: 219, column: 9, scope: !223)
!227 = !DILocation(line: 219, column: 15, scope: !223)
!228 = !DILocation(line: 220, column: 7, scope: !229)
!229 = distinct !DILexicalBlock(scope: !223, file: !1, line: 220, column: 7)
!230 = !DILocation(line: 220, column: 13, scope: !229)
!231 = !DILocation(line: 220, column: 19, scope: !229)
!232 = !DILocation(line: 220, column: 7, scope: !223)
!233 = !DILocation(line: 221, column: 4, scope: !229)
!234 = !DILocation(line: 223, column: 3, scope: !223)
!235 = !DILocation(line: 223, column: 9, scope: !223)
!236 = !DILocation(line: 223, column: 14, scope: !223)
!237 = !DILocation(line: 224, column: 3, scope: !223)
!238 = !DILocation(line: 224, column: 9, scope: !223)
!239 = !DILocation(line: 224, column: 13, scope: !223)
!240 = !DILocation(line: 226, column: 3, scope: !223)
!241 = !DILocation(line: 226, column: 9, scope: !223)
!242 = !DILocation(line: 226, column: 16, scope: !223)
!243 = !DILocation(line: 226, column: 21, scope: !223)
!244 = !DILocation(line: 226, column: 25, scope: !223)
!245 = !DILocation(line: 227, column: 3, scope: !223)
!246 = !DILocation(line: 227, column: 9, scope: !223)
!247 = !DILocation(line: 227, column: 16, scope: !223)
!248 = !DILocation(line: 227, column: 21, scope: !223)
!249 = !DILocation(line: 227, column: 26, scope: !223)
!250 = !DILocation(line: 228, column: 3, scope: !223)
!251 = !DILocation(line: 228, column: 9, scope: !223)
!252 = !DILocation(line: 228, column: 16, scope: !223)
!253 = !DILocation(line: 228, column: 21, scope: !223)
!254 = !DILocation(line: 229, column: 3, scope: !223)
!255 = !DILocation(line: 229, column: 9, scope: !223)
!256 = !DILocation(line: 229, column: 16, scope: !223)
!257 = !DILocation(line: 229, column: 23, scope: !223)
!258 = !DILocation(line: 230, column: 2, scope: !223)
!259 = !DILocation(line: 234, column: 2, scope: !39)
!260 = !DILocalVariable(name: "ret_", scope: !261, file: !1, line: 234, type: !262)
!261 = distinct !DILexicalBlock(scope: !39, file: !1, line: 234, column: 2)
!262 = !DIDerivedType(tag: DW_TAG_const_type, baseType: !42)
!263 = !DILocation(line: 234, column: 2, scope: !261)
!264 = !DILocation(line: 234, column: 2, scope: !265)
!265 = !DILexicalBlockFile(scope: !261, file: !1, discriminator: 1)
!266 = !DILocation(line: 234, column: 2, scope: !267)
!267 = !DILexicalBlockFile(scope: !268, file: !1, discriminator: 2)
!268 = distinct !DILexicalBlock(scope: !261, file: !1, line: 234, column: 2)
!269 = !DILocation(line: 234, column: 2, scope: !270)
!270 = !DILexicalBlockFile(scope: !261, file: !1, discriminator: 3)
!271 = !DILocation(line: 242, column: 17, scope: !272)
!272 = distinct !DILexicalBlock(scope: !39, file: !1, line: 242, column: 6)
!273 = !DILocation(line: 242, column: 27, scope: !272)
!274 = !DILocation(line: 242, column: 6, scope: !39)
!275 = !DILocation(line: 243, column: 14, scope: !272)
!276 = !DILocation(line: 243, column: 24, scope: !272)
!277 = !DILocation(line: 243, column: 3, scope: !272)
!278 = !DILocation(line: 252, column: 17, scope: !279)
!279 = distinct !DILexicalBlock(scope: !39, file: !1, line: 252, column: 6)
!280 = !DILocation(line: 252, column: 27, scope: !279)
!281 = !DILocation(line: 252, column: 6, scope: !39)
!282 = !DILocation(line: 253, column: 3, scope: !279)
!283 = !DILocation(line: 255, column: 37, scope: !39)
!284 = !DILocation(line: 255, column: 47, scope: !39)
!285 = !DILocation(line: 255, column: 53, scope: !39)
!286 = !DILocation(line: 255, column: 13, scope: !39)
!287 = !DILocation(line: 255, column: 23, scope: !39)
!288 = !DILocation(line: 258, column: 6, scope: !289)
!289 = distinct !DILexicalBlock(scope: !39, file: !1, line: 258, column: 6)
!290 = !DILocation(line: 258, column: 12, scope: !289)
!291 = !DILocation(line: 258, column: 19, scope: !289)
!292 = !DILocation(line: 258, column: 24, scope: !289)
!293 = !DILocation(line: 258, column: 43, scope: !289)
!294 = !DILocation(line: 258, column: 29, scope: !289)
!295 = !DILocation(line: 258, column: 6, scope: !39)
!296 = !DILocation(line: 259, column: 13, scope: !297)
!297 = distinct !DILexicalBlock(scope: !289, file: !1, line: 258, column: 54)
!298 = !DILocation(line: 259, column: 19, scope: !297)
!299 = !DILocation(line: 259, column: 26, scope: !297)
!300 = !DILocation(line: 259, column: 31, scope: !297)
!301 = !DILocation(line: 259, column: 36, scope: !297)
!302 = !DILocation(line: 259, column: 3, scope: !297)
!303 = !DILocation(line: 261, column: 29, scope: !297)
!304 = !DILocation(line: 261, column: 40, scope: !297)
!305 = !DILocation(line: 261, column: 7, scope: !297)
!306 = !DILocation(line: 260, column: 3, scope: !297)
!307 = !DILocation(line: 260, column: 9, scope: !297)
!308 = !DILocation(line: 260, column: 16, scope: !297)
!309 = !DILocation(line: 260, column: 21, scope: !297)
!310 = !DILocation(line: 261, column: 5, scope: !297)
!311 = !DILocation(line: 262, column: 7, scope: !312)
!312 = distinct !DILexicalBlock(scope: !297, file: !1, line: 262, column: 7)
!313 = !DILocation(line: 262, column: 13, scope: !312)
!314 = !DILocation(line: 262, column: 20, scope: !312)
!315 = !DILocation(line: 262, column: 25, scope: !312)
!316 = !DILocation(line: 262, column: 29, scope: !312)
!317 = !DILocation(line: 262, column: 7, scope: !297)
!318 = !DILocation(line: 263, column: 4, scope: !312)
!319 = !DILocation(line: 265, column: 39, scope: !297)
!320 = !DILocation(line: 265, column: 3, scope: !297)
!321 = !DILocation(line: 265, column: 9, scope: !297)
!322 = !DILocation(line: 265, column: 16, scope: !297)
!323 = !DILocation(line: 265, column: 21, scope: !297)
!324 = !DILocation(line: 265, column: 26, scope: !297)
!325 = !DILocation(line: 266, column: 2, scope: !297)
!326 = !DILocation(line: 268, column: 19, scope: !39)
!327 = !DILocation(line: 268, column: 25, scope: !39)
!328 = !DILocation(line: 268, column: 2, scope: !39)
!329 = !DILocation(line: 271, column: 17, scope: !330)
!330 = distinct !DILexicalBlock(scope: !39, file: !1, line: 271, column: 6)
!331 = !DILocation(line: 271, column: 29, scope: !330)
!332 = !DILocation(line: 272, column: 4, scope: !330)
!333 = !DILocation(line: 272, column: 18, scope: !334)
!334 = !DILexicalBlockFile(scope: !330, file: !1, discriminator: 1)
!335 = !DILocation(line: 272, column: 35, scope: !334)
!336 = !DILocation(line: 271, column: 6, scope: !337)
!337 = !DILexicalBlockFile(scope: !39, file: !1, discriminator: 1)
!338 = !DILocalVariable(name: "copy_size", scope: !339, file: !1, line: 275, type: !340)
!339 = distinct !DILexicalBlock(scope: !330, file: !1, line: 272, column: 40)
!340 = !DIDerivedType(tag: DW_TAG_const_type, baseType: !33)
!341 = !DILocation(line: 275, column: 16, scope: !339)
!342 = !DILocation(line: 275, column: 28, scope: !339)
!343 = !DILocation(line: 275, column: 28, scope: !344)
!344 = !DILexicalBlockFile(scope: !339, file: !1, discriminator: 1)
!345 = !DILocation(line: 275, column: 28, scope: !346)
!346 = !DILexicalBlockFile(scope: !339, file: !1, discriminator: 2)
!347 = !DILocation(line: 275, column: 28, scope: !348)
!348 = !DILexicalBlockFile(scope: !339, file: !1, discriminator: 3)
!349 = !DILocation(line: 275, column: 16, scope: !348)
!350 = !DILocalVariable(name: "offset", scope: !339, file: !1, line: 277, type: !340)
!351 = !DILocation(line: 277, column: 16, scope: !339)
!352 = !DILocation(line: 277, column: 36, scope: !339)
!353 = !DILocation(line: 277, column: 55, scope: !339)
!354 = !DILocation(line: 277, column: 53, scope: !339)
!355 = !DILocation(line: 278, column: 10, scope: !339)
!356 = !DILocation(line: 278, column: 16, scope: !339)
!357 = !DILocation(line: 278, column: 23, scope: !339)
!358 = !DILocation(line: 278, column: 28, scope: !339)
!359 = !DILocation(line: 278, column: 44, scope: !339)
!360 = !DILocation(line: 278, column: 58, scope: !339)
!361 = !DILocation(line: 278, column: 56, scope: !339)
!362 = !DILocation(line: 279, column: 5, scope: !339)
!363 = !DILocation(line: 278, column: 3, scope: !339)
!364 = !DILocation(line: 280, column: 27, scope: !339)
!365 = !DILocation(line: 280, column: 3, scope: !339)
!366 = !DILocation(line: 280, column: 9, scope: !339)
!367 = !DILocation(line: 280, column: 16, scope: !339)
!368 = !DILocation(line: 280, column: 21, scope: !339)
!369 = !DILocation(line: 280, column: 25, scope: !339)
!370 = !DILocation(line: 281, column: 28, scope: !339)
!371 = !DILocation(line: 281, column: 3, scope: !339)
!372 = !DILocation(line: 281, column: 9, scope: !339)
!373 = !DILocation(line: 281, column: 16, scope: !339)
!374 = !DILocation(line: 281, column: 21, scope: !339)
!375 = !DILocation(line: 281, column: 26, scope: !339)
!376 = !DILocation(line: 282, column: 2, scope: !339)
!377 = !DILocation(line: 285, column: 2, scope: !39)
!378 = !DILocation(line: 285, column: 8, scope: !39)
!379 = !DILocation(line: 285, column: 15, scope: !39)
!380 = !DILocation(line: 285, column: 29, scope: !39)
!381 = !DILocation(line: 286, column: 2, scope: !39)
!382 = !DILocation(line: 286, column: 8, scope: !39)
!383 = !DILocation(line: 286, column: 15, scope: !39)
!384 = !DILocation(line: 286, column: 29, scope: !39)
!385 = !DILocation(line: 287, column: 2, scope: !39)
!386 = !DILocation(line: 287, column: 8, scope: !39)
!387 = !DILocation(line: 287, column: 15, scope: !39)
!388 = !DILocation(line: 287, column: 20, scope: !39)
!389 = !DILocation(line: 287, column: 24, scope: !39)
!390 = !DILocation(line: 288, column: 2, scope: !39)
!391 = !DILocation(line: 288, column: 8, scope: !39)
!392 = !DILocation(line: 288, column: 15, scope: !39)
!393 = !DILocation(line: 288, column: 20, scope: !39)
!394 = !DILocation(line: 288, column: 25, scope: !39)
!395 = !DILocation(line: 291, column: 32, scope: !39)
!396 = !DILocation(line: 291, column: 38, scope: !39)
!397 = !DILocation(line: 291, column: 45, scope: !39)
!398 = !DILocation(line: 291, column: 51, scope: !39)
!399 = !DILocation(line: 292, column: 4, scope: !39)
!400 = !DILocation(line: 292, column: 12, scope: !39)
!401 = !DILocation(line: 291, column: 9, scope: !39)
!402 = !DILocation(line: 291, column: 2, scope: !39)
!403 = !DILocation(line: 293, column: 1, scope: !39)
!404 = !DILocalVariable(name: "coder", arg: 1, scope: !190, file: !1, line: 132, type: !49)
!405 = !DILocation(line: 132, column: 23, scope: !190)
!406 = !DILocalVariable(name: "allocator", arg: 2, scope: !190, file: !1, line: 133, type: !101)
!407 = !DILocation(line: 133, column: 19, scope: !190)
!408 = !DILocalVariable(name: "in", arg: 3, scope: !190, file: !1, line: 134, type: !80)
!409 = !DILocation(line: 134, column: 32, scope: !190)
!410 = !DILocalVariable(name: "in_pos", arg: 4, scope: !190, file: !1, line: 134, type: !83)
!411 = !DILocation(line: 134, column: 58, scope: !190)
!412 = !DILocalVariable(name: "in_size", arg: 5, scope: !190, file: !1, line: 135, type: !33)
!413 = !DILocation(line: 135, column: 10, scope: !190)
!414 = !DILocalVariable(name: "out", arg: 6, scope: !190, file: !1, line: 135, type: !134)
!415 = !DILocation(line: 135, column: 42, scope: !190)
!416 = !DILocalVariable(name: "out_pos", arg: 7, scope: !190, file: !1, line: 136, type: !83)
!417 = !DILocation(line: 136, column: 25, scope: !190)
!418 = !DILocalVariable(name: "out_size", arg: 8, scope: !190, file: !1, line: 136, type: !33)
!419 = !DILocation(line: 136, column: 41, scope: !190)
!420 = !DILocalVariable(name: "action", arg: 9, scope: !190, file: !1, line: 137, type: !135)
!421 = !DILocation(line: 137, column: 15, scope: !190)
!422 = !DILocation(line: 139, column: 6, scope: !423)
!423 = distinct !DILexicalBlock(scope: !190, file: !1, line: 139, column: 6)
!424 = !DILocation(line: 139, column: 13, scope: !423)
!425 = !DILocation(line: 139, column: 18, scope: !423)
!426 = !DILocation(line: 139, column: 23, scope: !423)
!427 = !DILocation(line: 139, column: 6, scope: !190)
!428 = !DILocation(line: 140, column: 24, scope: !423)
!429 = !DILocation(line: 140, column: 31, scope: !423)
!430 = !DILocation(line: 140, column: 35, scope: !423)
!431 = !DILocation(line: 140, column: 43, scope: !423)
!432 = !DILocation(line: 141, column: 5, scope: !423)
!433 = !DILocation(line: 141, column: 10, scope: !423)
!434 = !DILocation(line: 141, column: 19, scope: !423)
!435 = !DILocation(line: 140, column: 10, scope: !423)
!436 = !DILocation(line: 140, column: 3, scope: !423)
!437 = !DILocation(line: 145, column: 2, scope: !190)
!438 = !DILocation(line: 145, column: 10, scope: !439)
!439 = !DILexicalBlockFile(scope: !190, file: !1, discriminator: 1)
!440 = !DILocation(line: 145, column: 9, scope: !439)
!441 = !DILocation(line: 145, column: 20, scope: !439)
!442 = !DILocation(line: 145, column: 18, scope: !439)
!443 = !DILocation(line: 145, column: 2, scope: !439)
!444 = !DILocalVariable(name: "ret", scope: !445, file: !1, line: 146, type: !42)
!445 = distinct !DILexicalBlock(scope: !190, file: !1, line: 145, column: 30)
!446 = !DILocation(line: 146, column: 12, scope: !445)
!447 = !DILocation(line: 149, column: 8, scope: !448)
!448 = distinct !DILexicalBlock(scope: !445, file: !1, line: 149, column: 7)
!449 = !DILocation(line: 149, column: 15, scope: !448)
!450 = !DILocation(line: 150, column: 5, scope: !448)
!451 = !DILocation(line: 150, column: 8, scope: !452)
!452 = !DILexicalBlockFile(scope: !448, file: !1, discriminator: 1)
!453 = !DILocation(line: 150, column: 15, scope: !452)
!454 = !DILocation(line: 150, column: 20, scope: !452)
!455 = !DILocation(line: 150, column: 27, scope: !452)
!456 = !DILocation(line: 150, column: 34, scope: !452)
!457 = !DILocation(line: 150, column: 39, scope: !452)
!458 = !DILocation(line: 150, column: 24, scope: !452)
!459 = !DILocation(line: 149, column: 7, scope: !460)
!460 = !DILexicalBlockFile(scope: !445, file: !1, discriminator: 1)
!461 = !DILocation(line: 151, column: 4, scope: !462)
!462 = distinct !DILexicalBlock(scope: !448, file: !1, line: 150, column: 45)
!463 = !DILocation(line: 151, column: 11, scope: !462)
!464 = !DILocation(line: 151, column: 16, scope: !462)
!465 = !DILocation(line: 151, column: 20, scope: !462)
!466 = !DILocation(line: 152, column: 4, scope: !462)
!467 = !DILocation(line: 152, column: 11, scope: !462)
!468 = !DILocation(line: 152, column: 16, scope: !462)
!469 = !DILocation(line: 152, column: 21, scope: !462)
!470 = !DILocation(line: 154, column: 10, scope: !462)
!471 = !DILocation(line: 154, column: 17, scope: !462)
!472 = !DILocation(line: 154, column: 22, scope: !462)
!473 = !DILocation(line: 155, column: 6, scope: !462)
!474 = !DILocation(line: 155, column: 13, scope: !462)
!475 = !DILocation(line: 155, column: 18, scope: !462)
!476 = !DILocation(line: 156, column: 6, scope: !462)
!477 = !DILocation(line: 156, column: 17, scope: !462)
!478 = !DILocation(line: 156, column: 21, scope: !462)
!479 = !DILocation(line: 156, column: 29, scope: !462)
!480 = !DILocation(line: 157, column: 6, scope: !462)
!481 = !DILocation(line: 157, column: 13, scope: !462)
!482 = !DILocation(line: 157, column: 18, scope: !462)
!483 = !DILocation(line: 157, column: 27, scope: !462)
!484 = !DILocation(line: 157, column: 34, scope: !462)
!485 = !DILocation(line: 157, column: 39, scope: !462)
!486 = !DILocation(line: 158, column: 24, scope: !462)
!487 = !DILocation(line: 154, column: 8, scope: !462)
!488 = !DILocation(line: 160, column: 8, scope: !489)
!489 = distinct !DILexicalBlock(scope: !462, file: !1, line: 160, column: 8)
!490 = !DILocation(line: 160, column: 12, scope: !489)
!491 = !DILocation(line: 160, column: 8, scope: !462)
!492 = !DILocation(line: 161, column: 5, scope: !489)
!493 = !DILocation(line: 161, column: 12, scope: !489)
!494 = !DILocation(line: 161, column: 26, scope: !489)
!495 = !DILocation(line: 162, column: 13, scope: !496)
!496 = distinct !DILexicalBlock(scope: !489, file: !1, line: 162, column: 13)
!497 = !DILocation(line: 162, column: 17, scope: !496)
!498 = !DILocation(line: 162, column: 28, scope: !496)
!499 = !DILocation(line: 162, column: 31, scope: !500)
!500 = !DILexicalBlockFile(scope: !496, file: !1, discriminator: 1)
!501 = !DILocation(line: 162, column: 38, scope: !500)
!502 = !DILocation(line: 162, column: 43, scope: !500)
!503 = !DILocation(line: 162, column: 48, scope: !500)
!504 = !DILocation(line: 162, column: 13, scope: !500)
!505 = !DILocation(line: 163, column: 12, scope: !496)
!506 = !DILocation(line: 163, column: 5, scope: !496)
!507 = !DILocation(line: 164, column: 3, scope: !462)
!508 = !DILocation(line: 166, column: 7, scope: !509)
!509 = distinct !DILexicalBlock(scope: !445, file: !1, line: 166, column: 7)
!510 = !DILocation(line: 166, column: 14, scope: !509)
!511 = !DILocation(line: 166, column: 7, scope: !445)
!512 = !DILocation(line: 167, column: 8, scope: !513)
!513 = distinct !DILexicalBlock(scope: !514, file: !1, line: 167, column: 8)
!514 = distinct !DILexicalBlock(scope: !509, file: !1, line: 166, column: 29)
!515 = !DILocation(line: 167, column: 15, scope: !513)
!516 = !DILocation(line: 167, column: 20, scope: !513)
!517 = !DILocation(line: 167, column: 25, scope: !513)
!518 = !DILocation(line: 167, column: 8, scope: !514)
!519 = !DILocation(line: 168, column: 5, scope: !513)
!520 = !DILocation(line: 170, column: 8, scope: !521)
!521 = distinct !DILexicalBlock(scope: !514, file: !1, line: 170, column: 8)
!522 = !DILocation(line: 170, column: 15, scope: !521)
!523 = !DILocation(line: 170, column: 8, scope: !514)
!524 = !DILocation(line: 171, column: 5, scope: !521)
!525 = !DILocation(line: 173, column: 4, scope: !514)
!526 = !DILocation(line: 176, column: 23, scope: !445)
!527 = !DILocation(line: 176, column: 30, scope: !445)
!528 = !DILocation(line: 176, column: 37, scope: !445)
!529 = !DILocation(line: 176, column: 42, scope: !445)
!530 = !DILocation(line: 177, column: 6, scope: !445)
!531 = !DILocation(line: 177, column: 13, scope: !445)
!532 = !DILocation(line: 177, column: 18, scope: !445)
!533 = !DILocation(line: 177, column: 23, scope: !445)
!534 = !DILocation(line: 177, column: 30, scope: !445)
!535 = !DILocation(line: 177, column: 35, scope: !445)
!536 = !DILocation(line: 178, column: 5, scope: !445)
!537 = !DILocation(line: 178, column: 10, scope: !445)
!538 = !DILocation(line: 178, column: 19, scope: !445)
!539 = !DILocation(line: 176, column: 9, scope: !445)
!540 = !DILocation(line: 176, column: 7, scope: !445)
!541 = !DILocation(line: 180, column: 7, scope: !542)
!542 = distinct !DILexicalBlock(scope: !445, file: !1, line: 180, column: 7)
!543 = !DILocation(line: 180, column: 11, scope: !542)
!544 = !DILocation(line: 180, column: 7, scope: !445)
!545 = !DILocation(line: 181, column: 4, scope: !542)
!546 = !DILocation(line: 181, column: 11, scope: !542)
!547 = !DILocation(line: 181, column: 25, scope: !542)
!548 = !DILocation(line: 182, column: 12, scope: !549)
!549 = distinct !DILexicalBlock(scope: !542, file: !1, line: 182, column: 12)
!550 = !DILocation(line: 182, column: 16, scope: !549)
!551 = !DILocation(line: 182, column: 12, scope: !542)
!552 = !DILocation(line: 183, column: 11, scope: !549)
!553 = !DILocation(line: 183, column: 4, scope: !549)
!554 = !DILocation(line: 184, column: 12, scope: !555)
!555 = distinct !DILexicalBlock(scope: !549, file: !1, line: 184, column: 12)
!556 = !DILocation(line: 184, column: 19, scope: !555)
!557 = !DILocation(line: 184, column: 33, scope: !555)
!558 = !DILocation(line: 184, column: 37, scope: !559)
!559 = !DILexicalBlockFile(scope: !555, file: !1, discriminator: 1)
!560 = !DILocation(line: 184, column: 36, scope: !559)
!561 = !DILocation(line: 184, column: 47, scope: !559)
!562 = !DILocation(line: 184, column: 45, scope: !559)
!563 = !DILocation(line: 184, column: 12, scope: !559)
!564 = !DILocation(line: 185, column: 4, scope: !555)
!565 = !DILocation(line: 145, column: 2, scope: !566)
!566 = !DILexicalBlockFile(scope: !190, file: !1, discriminator: 2)
!567 = !DILocation(line: 188, column: 2, scope: !190)
!568 = !DILocation(line: 189, column: 1, scope: !190)
!569 = !DILocalVariable(name: "coder", arg: 1, scope: !194, file: !1, line: 193, type: !49)
!570 = !DILocation(line: 193, column: 28, scope: !194)
!571 = !DILocalVariable(name: "allocator", arg: 2, scope: !194, file: !1, line: 193, type: !101)
!572 = !DILocation(line: 193, column: 51, scope: !194)
!573 = !DILocation(line: 195, column: 17, scope: !194)
!574 = !DILocation(line: 195, column: 24, scope: !194)
!575 = !DILocation(line: 195, column: 30, scope: !194)
!576 = !DILocation(line: 195, column: 2, scope: !194)
!577 = !DILocation(line: 196, column: 12, scope: !194)
!578 = !DILocation(line: 196, column: 19, scope: !194)
!579 = !DILocation(line: 196, column: 24, scope: !194)
!580 = !DILocation(line: 196, column: 29, scope: !194)
!581 = !DILocation(line: 196, column: 2, scope: !194)
!582 = !DILocation(line: 198, column: 6, scope: !583)
!583 = distinct !DILexicalBlock(scope: !194, file: !1, line: 198, column: 6)
!584 = !DILocation(line: 198, column: 13, scope: !583)
!585 = !DILocation(line: 198, column: 16, scope: !583)
!586 = !DILocation(line: 198, column: 20, scope: !583)
!587 = !DILocation(line: 198, column: 6, scope: !194)
!588 = !DILocation(line: 199, column: 3, scope: !583)
!589 = !DILocation(line: 199, column: 10, scope: !583)
!590 = !DILocation(line: 199, column: 13, scope: !583)
!591 = !DILocation(line: 199, column: 17, scope: !583)
!592 = !DILocation(line: 199, column: 24, scope: !583)
!593 = !DILocation(line: 199, column: 27, scope: !583)
!594 = !DILocation(line: 199, column: 34, scope: !583)
!595 = !DILocation(line: 201, column: 13, scope: !583)
!596 = !DILocation(line: 201, column: 20, scope: !583)
!597 = !DILocation(line: 201, column: 23, scope: !583)
!598 = !DILocation(line: 201, column: 30, scope: !583)
!599 = !DILocation(line: 201, column: 3, scope: !583)
!600 = !DILocation(line: 203, column: 12, scope: !194)
!601 = !DILocation(line: 203, column: 19, scope: !194)
!602 = !DILocation(line: 203, column: 2, scope: !194)
!603 = !DILocation(line: 204, column: 2, scope: !194)
!604 = !DILocalVariable(name: "coder", arg: 1, scope: !195, file: !1, line: 55, type: !49)
!605 = !DILocation(line: 55, column: 30, scope: !195)
!606 = !DILocation(line: 57, column: 2, scope: !195)
!607 = !DILocation(line: 57, column: 9, scope: !195)
!608 = !DILocation(line: 57, column: 14, scope: !195)
!609 = !DILocation(line: 57, column: 18, scope: !195)
!610 = !DILocation(line: 58, column: 2, scope: !195)
!611 = !DILocation(line: 58, column: 9, scope: !195)
!612 = !DILocation(line: 58, column: 14, scope: !195)
!613 = !DILocation(line: 58, column: 19, scope: !195)
!614 = !DILocation(line: 59, column: 18, scope: !195)
!615 = !DILocation(line: 59, column: 25, scope: !195)
!616 = !DILocation(line: 59, column: 30, scope: !195)
!617 = !DILocation(line: 59, column: 35, scope: !195)
!618 = !DILocation(line: 59, column: 2, scope: !195)
!619 = !DILocation(line: 59, column: 9, scope: !195)
!620 = !DILocation(line: 59, column: 14, scope: !195)
!621 = !DILocation(line: 59, column: 40, scope: !195)
!622 = !DILocation(line: 60, column: 2, scope: !195)
!623 = !DILocation(line: 60, column: 9, scope: !195)
!624 = !DILocation(line: 60, column: 14, scope: !195)
!625 = !DILocation(line: 60, column: 25, scope: !195)
!626 = !DILocation(line: 61, column: 2, scope: !195)
!627 = !DILocalVariable(name: "dictionary_size", arg: 1, scope: !186, file: !1, line: 297, type: !33)
!628 = !DILocation(line: 297, column: 33, scope: !186)
!629 = !DILocation(line: 299, column: 41, scope: !186)
!630 = !DILocation(line: 299, column: 28, scope: !186)
!631 = !DILocation(line: 299, column: 2, scope: !186)
!632 = !DILocalVariable(name: "coder", arg: 1, scope: !189, file: !1, line: 304, type: !49)
!633 = !DILocation(line: 304, column: 42, scope: !189)
!634 = !DILocalVariable(name: "uncompressed_size", arg: 2, scope: !189, file: !1, line: 304, type: !95)
!635 = !DILocation(line: 304, column: 58, scope: !189)
!636 = !DILocation(line: 306, column: 2, scope: !189)
!637 = !DILocation(line: 306, column: 9, scope: !189)
!638 = !DILocation(line: 306, column: 12, scope: !189)
!639 = !DILocation(line: 306, column: 29, scope: !189)
!640 = !DILocation(line: 306, column: 36, scope: !189)
!641 = !DILocation(line: 306, column: 39, scope: !189)
!642 = !DILocation(line: 306, column: 46, scope: !189)
!643 = !DILocation(line: 307, column: 1, scope: !189)
!644 = !DILocalVariable(name: "coder", arg: 1, scope: !191, file: !1, line: 66, type: !49)
!645 = !DILocation(line: 66, column: 27, scope: !191)
!646 = !DILocalVariable(name: "in", arg: 2, scope: !191, file: !1, line: 67, type: !80)
!647 = !DILocation(line: 67, column: 32, scope: !191)
!648 = !DILocalVariable(name: "in_pos", arg: 3, scope: !191, file: !1, line: 67, type: !83)
!649 = !DILocation(line: 67, column: 58, scope: !191)
!650 = !DILocalVariable(name: "in_size", arg: 4, scope: !191, file: !1, line: 68, type: !33)
!651 = !DILocation(line: 68, column: 10, scope: !191)
!652 = !DILocalVariable(name: "out", arg: 5, scope: !191, file: !1, line: 68, type: !134)
!653 = !DILocation(line: 68, column: 42, scope: !191)
!654 = !DILocalVariable(name: "out_pos", arg: 6, scope: !191, file: !1, line: 69, type: !83)
!655 = !DILocation(line: 69, column: 25, scope: !191)
!656 = !DILocalVariable(name: "out_size", arg: 7, scope: !191, file: !1, line: 69, type: !33)
!657 = !DILocation(line: 69, column: 41, scope: !191)
!658 = !DILocation(line: 71, column: 2, scope: !191)
!659 = !DILocalVariable(name: "copy_size", scope: !660, file: !1, line: 72, type: !33)
!660 = distinct !DILexicalBlock(scope: !191, file: !1, line: 71, column: 15)
!661 = !DILocation(line: 72, column: 10, scope: !660)
!662 = !DILocalVariable(name: "dict_start", scope: !660, file: !1, line: 73, type: !33)
!663 = !DILocation(line: 73, column: 10, scope: !660)
!664 = !DILocalVariable(name: "ret", scope: !660, file: !1, line: 74, type: !42)
!665 = !DILocation(line: 74, column: 12, scope: !660)
!666 = !DILocation(line: 77, column: 7, scope: !667)
!667 = distinct !DILexicalBlock(scope: !660, file: !1, line: 77, column: 7)
!668 = !DILocation(line: 77, column: 14, scope: !667)
!669 = !DILocation(line: 77, column: 19, scope: !667)
!670 = !DILocation(line: 77, column: 26, scope: !667)
!671 = !DILocation(line: 77, column: 33, scope: !667)
!672 = !DILocation(line: 77, column: 38, scope: !667)
!673 = !DILocation(line: 77, column: 23, scope: !667)
!674 = !DILocation(line: 77, column: 7, scope: !660)
!675 = !DILocation(line: 78, column: 4, scope: !667)
!676 = !DILocation(line: 78, column: 11, scope: !667)
!677 = !DILocation(line: 78, column: 16, scope: !667)
!678 = !DILocation(line: 78, column: 20, scope: !667)
!679 = !DILocation(line: 82, column: 16, scope: !660)
!680 = !DILocation(line: 82, column: 23, scope: !660)
!681 = !DILocation(line: 82, column: 28, scope: !660)
!682 = !DILocation(line: 82, column: 14, scope: !660)
!683 = !DILocation(line: 88, column: 23, scope: !660)
!684 = !DILocation(line: 88, column: 30, scope: !660)
!685 = !DILocation(line: 88, column: 35, scope: !660)
!686 = !DILocation(line: 89, column: 7, scope: !660)
!687 = !DILocation(line: 89, column: 7, scope: !688)
!688 = !DILexicalBlockFile(scope: !660, file: !1, discriminator: 1)
!689 = !DILocation(line: 89, column: 7, scope: !690)
!690 = !DILexicalBlockFile(scope: !660, file: !1, discriminator: 2)
!691 = !DILocation(line: 89, column: 7, scope: !692)
!692 = !DILexicalBlockFile(scope: !660, file: !1, discriminator: 3)
!693 = !DILocation(line: 89, column: 5, scope: !692)
!694 = !DILocation(line: 88, column: 3, scope: !688)
!695 = !DILocation(line: 88, column: 10, scope: !688)
!696 = !DILocation(line: 88, column: 15, scope: !688)
!697 = !DILocation(line: 88, column: 21, scope: !688)
!698 = !DILocation(line: 93, column: 9, scope: !660)
!699 = !DILocation(line: 93, column: 16, scope: !660)
!700 = !DILocation(line: 93, column: 19, scope: !660)
!701 = !DILocation(line: 94, column: 5, scope: !660)
!702 = !DILocation(line: 94, column: 12, scope: !660)
!703 = !DILocation(line: 94, column: 15, scope: !660)
!704 = !DILocation(line: 94, column: 23, scope: !660)
!705 = !DILocation(line: 94, column: 30, scope: !660)
!706 = !DILocation(line: 95, column: 5, scope: !660)
!707 = !DILocation(line: 95, column: 9, scope: !660)
!708 = !DILocation(line: 95, column: 17, scope: !660)
!709 = !DILocation(line: 93, column: 7, scope: !660)
!710 = !DILocation(line: 99, column: 15, scope: !660)
!711 = !DILocation(line: 99, column: 22, scope: !660)
!712 = !DILocation(line: 99, column: 27, scope: !660)
!713 = !DILocation(line: 99, column: 33, scope: !660)
!714 = !DILocation(line: 99, column: 31, scope: !660)
!715 = !DILocation(line: 99, column: 13, scope: !660)
!716 = !DILocation(line: 100, column: 3, scope: !660)
!717 = !DILocation(line: 100, column: 3, scope: !688)
!718 = !DILocation(line: 100, column: 3, scope: !690)
!719 = !DILocation(line: 100, column: 3, scope: !692)
!720 = !DILocation(line: 101, column: 10, scope: !660)
!721 = !DILocation(line: 101, column: 17, scope: !660)
!722 = !DILocation(line: 101, column: 16, scope: !660)
!723 = !DILocation(line: 101, column: 14, scope: !660)
!724 = !DILocation(line: 101, column: 26, scope: !660)
!725 = !DILocation(line: 101, column: 33, scope: !660)
!726 = !DILocation(line: 101, column: 38, scope: !660)
!727 = !DILocation(line: 101, column: 44, scope: !660)
!728 = !DILocation(line: 101, column: 42, scope: !660)
!729 = !DILocation(line: 102, column: 5, scope: !660)
!730 = !DILocation(line: 101, column: 3, scope: !660)
!731 = !DILocation(line: 103, column: 15, scope: !660)
!732 = !DILocation(line: 103, column: 4, scope: !660)
!733 = !DILocation(line: 103, column: 12, scope: !660)
!734 = !DILocation(line: 106, column: 7, scope: !735)
!735 = distinct !DILexicalBlock(scope: !660, file: !1, line: 106, column: 7)
!736 = !DILocation(line: 106, column: 14, scope: !735)
!737 = !DILocation(line: 106, column: 19, scope: !735)
!738 = !DILocation(line: 106, column: 7, scope: !660)
!739 = !DILocation(line: 107, column: 21, scope: !740)
!740 = distinct !DILexicalBlock(scope: !735, file: !1, line: 106, column: 31)
!741 = !DILocation(line: 107, column: 4, scope: !740)
!742 = !DILocation(line: 111, column: 8, scope: !743)
!743 = distinct !DILexicalBlock(scope: !740, file: !1, line: 111, column: 8)
!744 = !DILocation(line: 111, column: 12, scope: !743)
!745 = !DILocation(line: 111, column: 23, scope: !743)
!746 = !DILocation(line: 111, column: 27, scope: !747)
!747 = !DILexicalBlockFile(scope: !743, file: !1, discriminator: 1)
!748 = !DILocation(line: 111, column: 26, scope: !747)
!749 = !DILocation(line: 111, column: 38, scope: !747)
!750 = !DILocation(line: 111, column: 35, scope: !747)
!751 = !DILocation(line: 111, column: 8, scope: !747)
!752 = !DILocation(line: 112, column: 12, scope: !743)
!753 = !DILocation(line: 112, column: 5, scope: !743)
!754 = !DILocation(line: 113, column: 3, scope: !740)
!755 = !DILocation(line: 123, column: 8, scope: !756)
!756 = distinct !DILexicalBlock(scope: !757, file: !1, line: 123, column: 8)
!757 = distinct !DILexicalBlock(scope: !735, file: !1, line: 113, column: 10)
!758 = !DILocation(line: 123, column: 12, scope: !756)
!759 = !DILocation(line: 123, column: 23, scope: !756)
!760 = !DILocation(line: 123, column: 27, scope: !761)
!761 = !DILexicalBlockFile(scope: !756, file: !1, discriminator: 1)
!762 = !DILocation(line: 123, column: 26, scope: !761)
!763 = !DILocation(line: 123, column: 38, scope: !761)
!764 = !DILocation(line: 123, column: 35, scope: !761)
!765 = !DILocation(line: 124, column: 6, scope: !756)
!766 = !DILocation(line: 124, column: 9, scope: !761)
!767 = !DILocation(line: 124, column: 16, scope: !761)
!768 = !DILocation(line: 124, column: 21, scope: !761)
!769 = !DILocation(line: 124, column: 27, scope: !761)
!770 = !DILocation(line: 124, column: 34, scope: !761)
!771 = !DILocation(line: 124, column: 39, scope: !761)
!772 = !DILocation(line: 124, column: 25, scope: !761)
!773 = !DILocation(line: 123, column: 8, scope: !774)
!774 = !DILexicalBlockFile(scope: !757, file: !1, discriminator: 2)
!775 = !DILocation(line: 125, column: 12, scope: !756)
!776 = !DILocation(line: 125, column: 5, scope: !756)
!777 = !DILocation(line: 71, column: 2, scope: !778)
!778 = !DILexicalBlockFile(scope: !191, file: !1, discriminator: 1)
!779 = !DILocation(line: 128, column: 1, scope: !191)
