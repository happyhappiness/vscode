; ModuleID = '/data/download/cmake/cmake-master/Utilities/cmliblzma/liblzma/lzma/lzma2_decoder.c'
target datalayout = "e-m:e-i64:64-f80:128-n8:16:32:64-S128"
target triple = "x86_64-unknown-linux-gnu"

%struct.lzma_lz_decoder = type { %struct.lzma_coder_s*, i32 (%struct.lzma_coder_s*, %struct.lzma_dict*, i8*, i64*, i64)*, void (%struct.lzma_coder_s*, i8*)*, void (%struct.lzma_coder_s*, i64)*, void (%struct.lzma_coder_s*, %struct.lzma_allocator*)* }
%struct.lzma_coder_s = type { i32, i32, %struct.lzma_lz_decoder, i64, i64, i8, i8, %struct.lzma_options_lzma }
%struct.lzma_options_lzma = type { i32, i8*, i32, i32, i32, i32, i32, i32, i32, i32, i32, i32, i32, i32, i32, i32, i32, i32, i32, i32, i32, i32, i8*, i8* }
%struct.lzma_dict = type { i8*, i64, i64, i64, i64, i8 }
%struct.lzma_allocator = type { i8* (i8*, i64, i64)*, void (i8*, i8*)*, i8* }
%struct.lzma_next_coder_s = type { %struct.lzma_coder_s*, i64, i64, i32 (%struct.lzma_coder_s*, %struct.lzma_allocator*, i8*, i64*, i64, i8*, i64*, i64, i32)*, void (%struct.lzma_coder_s*, %struct.lzma_allocator*)*, i32 (%struct.lzma_coder_s*)*, i32 (%struct.lzma_coder_s*, i64*, i64*, i64)*, i32 (%struct.lzma_coder_s*, %struct.lzma_allocator*, %struct.lzma_filter*, %struct.lzma_filter*)* }
%struct.lzma_filter = type { i64, i8* }
%struct.lzma_filter_info_s = type { i64, {}*, i8* }
%struct.lzma_lz_options = type { i64, i8*, i64 }

@.str = private unnamed_addr constant [30 x i8] c"filters[1].init == ((void*)0)\00", align 1
@.str.1 = private unnamed_addr constant [83 x i8] c"/data/download/cmake/cmake-master/Utilities/cmliblzma/liblzma/lzma/lzma2_decoder.c\00", align 1
@__PRETTY_FUNCTION__.lzma_lzma2_decoder_init = private unnamed_addr constant [96 x i8] c"lzma_ret lzma_lzma2_decoder_init(lzma_next_coder *, lzma_allocator *, const lzma_filter_info *)\00", align 1
@LZMA_LZ_DECODER_INIT = internal constant %struct.lzma_lz_decoder zeroinitializer, align 8
@.str.2 = private unnamed_addr constant [2 x i8] c"0\00", align 1
@__PRETTY_FUNCTION__.lzma2_decode = private unnamed_addr constant [116 x i8] c"lzma_ret lzma2_decode(lzma_coder *restrict, lzma_dict *restrict, const uint8_t *restrict, size_t *restrict, size_t)\00", align 1
@.str.3 = private unnamed_addr constant [30 x i8] c"coder->lzma.end == ((void*)0)\00", align 1
@__PRETTY_FUNCTION__.lzma2_decoder_end = private unnamed_addr constant [55 x i8] c"void lzma2_decoder_end(lzma_coder *, lzma_allocator *)\00", align 1

; Function Attrs: nounwind uwtable
define i32 @lzma_lzma2_decoder_init(%struct.lzma_next_coder_s* %next, %struct.lzma_allocator* %allocator, %struct.lzma_filter_info_s* %filters) #0 !dbg !62 {
entry:
  %next.addr = alloca %struct.lzma_next_coder_s*, align 8
  %allocator.addr = alloca %struct.lzma_allocator*, align 8
  %filters.addr = alloca %struct.lzma_filter_info_s*, align 8
  store %struct.lzma_next_coder_s* %next, %struct.lzma_next_coder_s** %next.addr, align 8
  call void @llvm.dbg.declare(metadata %struct.lzma_next_coder_s** %next.addr, metadata !256, metadata !257), !dbg !258
  store %struct.lzma_allocator* %allocator, %struct.lzma_allocator** %allocator.addr, align 8
  call void @llvm.dbg.declare(metadata %struct.lzma_allocator** %allocator.addr, metadata !259, metadata !257), !dbg !260
  store %struct.lzma_filter_info_s* %filters, %struct.lzma_filter_info_s** %filters.addr, align 8
  call void @llvm.dbg.declare(metadata %struct.lzma_filter_info_s** %filters.addr, metadata !261, metadata !257), !dbg !262
  %0 = load %struct.lzma_filter_info_s*, %struct.lzma_filter_info_s** %filters.addr, align 8, !dbg !263
  %arrayidx = getelementptr inbounds %struct.lzma_filter_info_s, %struct.lzma_filter_info_s* %0, i64 1, !dbg !263
  %init = getelementptr inbounds %struct.lzma_filter_info_s, %struct.lzma_filter_info_s* %arrayidx, i32 0, i32 1, !dbg !263
  %init1 = bitcast {}** %init to i32 (%struct.lzma_next_coder_s*, %struct.lzma_allocator*, %struct.lzma_filter_info_s*)**, !dbg !263
  %1 = load i32 (%struct.lzma_next_coder_s*, %struct.lzma_allocator*, %struct.lzma_filter_info_s*)*, i32 (%struct.lzma_next_coder_s*, %struct.lzma_allocator*, %struct.lzma_filter_info_s*)** %init1, align 8, !dbg !263
  %cmp = icmp eq i32 (%struct.lzma_next_coder_s*, %struct.lzma_allocator*, %struct.lzma_filter_info_s*)* %1, null, !dbg !263
  br i1 %cmp, label %cond.true, label %cond.false, !dbg !263

cond.true:                                        ; preds = %entry
  br label %cond.end, !dbg !264

cond.false:                                       ; preds = %entry
  call void @__assert_fail(i8* getelementptr inbounds ([30 x i8], [30 x i8]* @.str, i32 0, i32 0), i8* getelementptr inbounds ([83 x i8], [83 x i8]* @.str.1, i32 0, i32 0), i32 256, i8* getelementptr inbounds ([96 x i8], [96 x i8]* @__PRETTY_FUNCTION__.lzma_lzma2_decoder_init, i32 0, i32 0)) #6, !dbg !266
  unreachable, !dbg !266
                                                  ; No predecessors!
  br label %cond.end, !dbg !268

cond.end:                                         ; preds = %2, %cond.true
  %3 = load %struct.lzma_next_coder_s*, %struct.lzma_next_coder_s** %next.addr, align 8, !dbg !270
  %4 = load %struct.lzma_allocator*, %struct.lzma_allocator** %allocator.addr, align 8, !dbg !271
  %5 = load %struct.lzma_filter_info_s*, %struct.lzma_filter_info_s** %filters.addr, align 8, !dbg !272
  %call = call i32 @lzma_lz_decoder_init(%struct.lzma_next_coder_s* %3, %struct.lzma_allocator* %4, %struct.lzma_filter_info_s* %5, i32 (%struct.lzma_lz_decoder*, %struct.lzma_allocator*, i8*, %struct.lzma_lz_options*)* @lzma2_decoder_init), !dbg !273
  ret i32 %call, !dbg !274
}

; Function Attrs: nounwind readnone
declare void @llvm.dbg.declare(metadata, metadata, metadata) #1

; Function Attrs: noreturn nounwind
declare void @__assert_fail(i8*, i8*, i32, i8*) #2

declare i32 @lzma_lz_decoder_init(%struct.lzma_next_coder_s*, %struct.lzma_allocator*, %struct.lzma_filter_info_s*, i32 (%struct.lzma_lz_decoder*, %struct.lzma_allocator*, i8*, %struct.lzma_lz_options*)*) #3

; Function Attrs: nounwind uwtable
define internal i32 @lzma2_decoder_init(%struct.lzma_lz_decoder* %lz, %struct.lzma_allocator* %allocator, i8* %opt, %struct.lzma_lz_options* %lz_options) #0 !dbg !231 {
entry:
  %retval = alloca i32, align 4
  %lz.addr = alloca %struct.lzma_lz_decoder*, align 8
  %allocator.addr = alloca %struct.lzma_allocator*, align 8
  %opt.addr = alloca i8*, align 8
  %lz_options.addr = alloca %struct.lzma_lz_options*, align 8
  %options = alloca %struct.lzma_options_lzma*, align 8
  store %struct.lzma_lz_decoder* %lz, %struct.lzma_lz_decoder** %lz.addr, align 8
  call void @llvm.dbg.declare(metadata %struct.lzma_lz_decoder** %lz.addr, metadata !275, metadata !257), !dbg !276
  store %struct.lzma_allocator* %allocator, %struct.lzma_allocator** %allocator.addr, align 8
  call void @llvm.dbg.declare(metadata %struct.lzma_allocator** %allocator.addr, metadata !277, metadata !257), !dbg !278
  store i8* %opt, i8** %opt.addr, align 8
  call void @llvm.dbg.declare(metadata i8** %opt.addr, metadata !279, metadata !257), !dbg !280
  store %struct.lzma_lz_options* %lz_options, %struct.lzma_lz_options** %lz_options.addr, align 8
  call void @llvm.dbg.declare(metadata %struct.lzma_lz_options** %lz_options.addr, metadata !281, metadata !257), !dbg !282
  call void @llvm.dbg.declare(metadata %struct.lzma_options_lzma** %options, metadata !283, metadata !257), !dbg !286
  %0 = load i8*, i8** %opt.addr, align 8, !dbg !287
  %1 = bitcast i8* %0 to %struct.lzma_options_lzma*, !dbg !287
  store %struct.lzma_options_lzma* %1, %struct.lzma_options_lzma** %options, align 8, !dbg !286
  %2 = load %struct.lzma_lz_decoder*, %struct.lzma_lz_decoder** %lz.addr, align 8, !dbg !288
  %coder = getelementptr inbounds %struct.lzma_lz_decoder, %struct.lzma_lz_decoder* %2, i32 0, i32 0, !dbg !290
  %3 = load %struct.lzma_coder_s*, %struct.lzma_coder_s** %coder, align 8, !dbg !290
  %cmp = icmp eq %struct.lzma_coder_s* %3, null, !dbg !291
  br i1 %cmp, label %if.then, label %if.end6, !dbg !292

if.then:                                          ; preds = %entry
  %4 = load %struct.lzma_allocator*, %struct.lzma_allocator** %allocator.addr, align 8, !dbg !293
  %call = call noalias i8* @lzma_alloc(i64 184, %struct.lzma_allocator* %4), !dbg !295
  %5 = bitcast i8* %call to %struct.lzma_coder_s*, !dbg !295
  %6 = load %struct.lzma_lz_decoder*, %struct.lzma_lz_decoder** %lz.addr, align 8, !dbg !296
  %coder1 = getelementptr inbounds %struct.lzma_lz_decoder, %struct.lzma_lz_decoder* %6, i32 0, i32 0, !dbg !297
  store %struct.lzma_coder_s* %5, %struct.lzma_coder_s** %coder1, align 8, !dbg !298
  %7 = load %struct.lzma_lz_decoder*, %struct.lzma_lz_decoder** %lz.addr, align 8, !dbg !299
  %coder2 = getelementptr inbounds %struct.lzma_lz_decoder, %struct.lzma_lz_decoder* %7, i32 0, i32 0, !dbg !301
  %8 = load %struct.lzma_coder_s*, %struct.lzma_coder_s** %coder2, align 8, !dbg !301
  %cmp3 = icmp eq %struct.lzma_coder_s* %8, null, !dbg !302
  br i1 %cmp3, label %if.then4, label %if.end, !dbg !303

if.then4:                                         ; preds = %if.then
  store i32 5, i32* %retval, align 4, !dbg !304
  br label %return, !dbg !304

if.end:                                           ; preds = %if.then
  %9 = load %struct.lzma_lz_decoder*, %struct.lzma_lz_decoder** %lz.addr, align 8, !dbg !305
  %code = getelementptr inbounds %struct.lzma_lz_decoder, %struct.lzma_lz_decoder* %9, i32 0, i32 1, !dbg !306
  store i32 (%struct.lzma_coder_s*, %struct.lzma_dict*, i8*, i64*, i64)* @lzma2_decode, i32 (%struct.lzma_coder_s*, %struct.lzma_dict*, i8*, i64*, i64)** %code, align 8, !dbg !307
  %10 = load %struct.lzma_lz_decoder*, %struct.lzma_lz_decoder** %lz.addr, align 8, !dbg !308
  %end = getelementptr inbounds %struct.lzma_lz_decoder, %struct.lzma_lz_decoder* %10, i32 0, i32 4, !dbg !309
  store void (%struct.lzma_coder_s*, %struct.lzma_allocator*)* @lzma2_decoder_end, void (%struct.lzma_coder_s*, %struct.lzma_allocator*)** %end, align 8, !dbg !310
  %11 = load %struct.lzma_lz_decoder*, %struct.lzma_lz_decoder** %lz.addr, align 8, !dbg !311
  %coder5 = getelementptr inbounds %struct.lzma_lz_decoder, %struct.lzma_lz_decoder* %11, i32 0, i32 0, !dbg !312
  %12 = load %struct.lzma_coder_s*, %struct.lzma_coder_s** %coder5, align 8, !dbg !312
  %lzma = getelementptr inbounds %struct.lzma_coder_s, %struct.lzma_coder_s* %12, i32 0, i32 2, !dbg !313
  %13 = bitcast %struct.lzma_lz_decoder* %lzma to i8*, !dbg !314
  call void @llvm.memcpy.p0i8.p0i8.i64(i8* %13, i8* bitcast (%struct.lzma_lz_decoder* @LZMA_LZ_DECODER_INIT to i8*), i64 40, i32 8, i1 false), !dbg !314
  br label %if.end6, !dbg !315

if.end6:                                          ; preds = %if.end, %entry
  %14 = load %struct.lzma_lz_decoder*, %struct.lzma_lz_decoder** %lz.addr, align 8, !dbg !316
  %coder7 = getelementptr inbounds %struct.lzma_lz_decoder, %struct.lzma_lz_decoder* %14, i32 0, i32 0, !dbg !317
  %15 = load %struct.lzma_coder_s*, %struct.lzma_coder_s** %coder7, align 8, !dbg !317
  %sequence = getelementptr inbounds %struct.lzma_coder_s, %struct.lzma_coder_s* %15, i32 0, i32 0, !dbg !318
  store i32 0, i32* %sequence, align 8, !dbg !319
  %16 = load %struct.lzma_lz_decoder*, %struct.lzma_lz_decoder** %lz.addr, align 8, !dbg !320
  %coder8 = getelementptr inbounds %struct.lzma_lz_decoder, %struct.lzma_lz_decoder* %16, i32 0, i32 0, !dbg !321
  %17 = load %struct.lzma_coder_s*, %struct.lzma_coder_s** %coder8, align 8, !dbg !321
  %need_properties = getelementptr inbounds %struct.lzma_coder_s, %struct.lzma_coder_s* %17, i32 0, i32 5, !dbg !322
  store i8 1, i8* %need_properties, align 8, !dbg !323
  %18 = load %struct.lzma_options_lzma*, %struct.lzma_options_lzma** %options, align 8, !dbg !324
  %preset_dict = getelementptr inbounds %struct.lzma_options_lzma, %struct.lzma_options_lzma* %18, i32 0, i32 1, !dbg !325
  %19 = load i8*, i8** %preset_dict, align 8, !dbg !325
  %cmp9 = icmp eq i8* %19, null, !dbg !326
  br i1 %cmp9, label %lor.end, label %lor.rhs, !dbg !327

lor.rhs:                                          ; preds = %if.end6
  %20 = load %struct.lzma_options_lzma*, %struct.lzma_options_lzma** %options, align 8, !dbg !328
  %preset_dict_size = getelementptr inbounds %struct.lzma_options_lzma, %struct.lzma_options_lzma* %20, i32 0, i32 2, !dbg !330
  %21 = load i32, i32* %preset_dict_size, align 8, !dbg !330
  %cmp10 = icmp eq i32 %21, 0, !dbg !331
  br label %lor.end, !dbg !332

lor.end:                                          ; preds = %lor.rhs, %if.end6
  %22 = phi i1 [ true, %if.end6 ], [ %cmp10, %lor.rhs ]
  %23 = load %struct.lzma_lz_decoder*, %struct.lzma_lz_decoder** %lz.addr, align 8, !dbg !333
  %coder11 = getelementptr inbounds %struct.lzma_lz_decoder, %struct.lzma_lz_decoder* %23, i32 0, i32 0, !dbg !334
  %24 = load %struct.lzma_coder_s*, %struct.lzma_coder_s** %coder11, align 8, !dbg !334
  %need_dictionary_reset = getelementptr inbounds %struct.lzma_coder_s, %struct.lzma_coder_s* %24, i32 0, i32 6, !dbg !335
  %frombool = zext i1 %22 to i8, !dbg !336
  store i8 %frombool, i8* %need_dictionary_reset, align 1, !dbg !336
  %25 = load %struct.lzma_lz_decoder*, %struct.lzma_lz_decoder** %lz.addr, align 8, !dbg !337
  %coder12 = getelementptr inbounds %struct.lzma_lz_decoder, %struct.lzma_lz_decoder* %25, i32 0, i32 0, !dbg !338
  %26 = load %struct.lzma_coder_s*, %struct.lzma_coder_s** %coder12, align 8, !dbg !338
  %lzma13 = getelementptr inbounds %struct.lzma_coder_s, %struct.lzma_coder_s* %26, i32 0, i32 2, !dbg !339
  %27 = load %struct.lzma_allocator*, %struct.lzma_allocator** %allocator.addr, align 8, !dbg !340
  %28 = load %struct.lzma_options_lzma*, %struct.lzma_options_lzma** %options, align 8, !dbg !341
  %29 = bitcast %struct.lzma_options_lzma* %28 to i8*, !dbg !341
  %30 = load %struct.lzma_lz_options*, %struct.lzma_lz_options** %lz_options.addr, align 8, !dbg !342
  %call14 = call i32 @lzma_lzma_decoder_create(%struct.lzma_lz_decoder* %lzma13, %struct.lzma_allocator* %27, i8* %29, %struct.lzma_lz_options* %30), !dbg !343
  store i32 %call14, i32* %retval, align 4, !dbg !344
  br label %return, !dbg !344

return:                                           ; preds = %lor.end, %if.then4
  %31 = load i32, i32* %retval, align 4, !dbg !345
  ret i32 %31, !dbg !345
}

; Function Attrs: nounwind uwtable
define i64 @lzma_lzma2_decoder_memusage(i8* %options) #0 !dbg !224 {
entry:
  %options.addr = alloca i8*, align 8
  store i8* %options, i8** %options.addr, align 8
  call void @llvm.dbg.declare(metadata i8** %options.addr, metadata !346, metadata !257), !dbg !347
  %0 = load i8*, i8** %options.addr, align 8, !dbg !348
  %call = call i64 @lzma_lzma_decoder_memusage_nocheck(i8* %0), !dbg !349
  %add = add i64 184, %call, !dbg !350
  ret i64 %add, !dbg !351
}

declare i64 @lzma_lzma_decoder_memusage_nocheck(i8*) #3

; Function Attrs: nounwind uwtable
define i32 @lzma_lzma2_props_decode(i8** %options, %struct.lzma_allocator* %allocator, i8* %props, i64 %props_size) #0 !dbg !227 {
entry:
  %retval = alloca i32, align 4
  %options.addr = alloca i8**, align 8
  %allocator.addr = alloca %struct.lzma_allocator*, align 8
  %props.addr = alloca i8*, align 8
  %props_size.addr = alloca i64, align 8
  %opt = alloca %struct.lzma_options_lzma*, align 8
  store i8** %options, i8*** %options.addr, align 8
  call void @llvm.dbg.declare(metadata i8*** %options.addr, metadata !352, metadata !257), !dbg !353
  store %struct.lzma_allocator* %allocator, %struct.lzma_allocator** %allocator.addr, align 8
  call void @llvm.dbg.declare(metadata %struct.lzma_allocator** %allocator.addr, metadata !354, metadata !257), !dbg !355
  store i8* %props, i8** %props.addr, align 8
  call void @llvm.dbg.declare(metadata i8** %props.addr, metadata !356, metadata !257), !dbg !357
  store i64 %props_size, i64* %props_size.addr, align 8
  call void @llvm.dbg.declare(metadata i64* %props_size.addr, metadata !358, metadata !257), !dbg !359
  call void @llvm.dbg.declare(metadata %struct.lzma_options_lzma** %opt, metadata !360, metadata !257), !dbg !362
  %0 = load i64, i64* %props_size.addr, align 8, !dbg !363
  %cmp = icmp ne i64 %0, 1, !dbg !365
  br i1 %cmp, label %if.then, label %if.end, !dbg !366

if.then:                                          ; preds = %entry
  store i32 8, i32* %retval, align 4, !dbg !367
  br label %return, !dbg !367

if.end:                                           ; preds = %entry
  %1 = load i8*, i8** %props.addr, align 8, !dbg !368
  %arrayidx = getelementptr inbounds i8, i8* %1, i64 0, !dbg !368
  %2 = load i8, i8* %arrayidx, align 1, !dbg !368
  %conv = zext i8 %2 to i32, !dbg !368
  %and = and i32 %conv, 192, !dbg !370
  %tobool = icmp ne i32 %and, 0, !dbg !370
  br i1 %tobool, label %if.then1, label %if.end2, !dbg !371

if.then1:                                         ; preds = %if.end
  store i32 8, i32* %retval, align 4, !dbg !372
  br label %return, !dbg !372

if.end2:                                          ; preds = %if.end
  %3 = load i8*, i8** %props.addr, align 8, !dbg !373
  %arrayidx3 = getelementptr inbounds i8, i8* %3, i64 0, !dbg !373
  %4 = load i8, i8* %arrayidx3, align 1, !dbg !373
  %conv4 = zext i8 %4 to i32, !dbg !373
  %cmp5 = icmp sgt i32 %conv4, 40, !dbg !375
  br i1 %cmp5, label %if.then7, label %if.end8, !dbg !376

if.then7:                                         ; preds = %if.end2
  store i32 8, i32* %retval, align 4, !dbg !377
  br label %return, !dbg !377

if.end8:                                          ; preds = %if.end2
  %5 = load %struct.lzma_allocator*, %struct.lzma_allocator** %allocator.addr, align 8, !dbg !378
  %call = call noalias i8* @lzma_alloc(i64 112, %struct.lzma_allocator* %5), !dbg !379
  %6 = bitcast i8* %call to %struct.lzma_options_lzma*, !dbg !379
  store %struct.lzma_options_lzma* %6, %struct.lzma_options_lzma** %opt, align 8, !dbg !380
  %7 = load %struct.lzma_options_lzma*, %struct.lzma_options_lzma** %opt, align 8, !dbg !381
  %cmp9 = icmp eq %struct.lzma_options_lzma* %7, null, !dbg !383
  br i1 %cmp9, label %if.then11, label %if.end12, !dbg !384

if.then11:                                        ; preds = %if.end8
  store i32 5, i32* %retval, align 4, !dbg !385
  br label %return, !dbg !385

if.end12:                                         ; preds = %if.end8
  %8 = load i8*, i8** %props.addr, align 8, !dbg !386
  %arrayidx13 = getelementptr inbounds i8, i8* %8, i64 0, !dbg !386
  %9 = load i8, i8* %arrayidx13, align 1, !dbg !386
  %conv14 = zext i8 %9 to i32, !dbg !386
  %cmp15 = icmp eq i32 %conv14, 40, !dbg !388
  br i1 %cmp15, label %if.then17, label %if.else, !dbg !389

if.then17:                                        ; preds = %if.end12
  %10 = load %struct.lzma_options_lzma*, %struct.lzma_options_lzma** %opt, align 8, !dbg !390
  %dict_size = getelementptr inbounds %struct.lzma_options_lzma, %struct.lzma_options_lzma* %10, i32 0, i32 0, !dbg !392
  store i32 -1, i32* %dict_size, align 8, !dbg !393
  br label %if.end25, !dbg !394

if.else:                                          ; preds = %if.end12
  %11 = load i8*, i8** %props.addr, align 8, !dbg !395
  %arrayidx18 = getelementptr inbounds i8, i8* %11, i64 0, !dbg !395
  %12 = load i8, i8* %arrayidx18, align 1, !dbg !395
  %conv19 = zext i8 %12 to i32, !dbg !395
  %and20 = and i32 %conv19, 1, !dbg !397
  %or = or i32 2, %and20, !dbg !398
  %13 = load %struct.lzma_options_lzma*, %struct.lzma_options_lzma** %opt, align 8, !dbg !399
  %dict_size21 = getelementptr inbounds %struct.lzma_options_lzma, %struct.lzma_options_lzma* %13, i32 0, i32 0, !dbg !400
  store i32 %or, i32* %dict_size21, align 8, !dbg !401
  %14 = load i8*, i8** %props.addr, align 8, !dbg !402
  %arrayidx22 = getelementptr inbounds i8, i8* %14, i64 0, !dbg !402
  %15 = load i8, i8* %arrayidx22, align 1, !dbg !402
  %conv23 = zext i8 %15 to i32, !dbg !402
  %div = sdiv i32 %conv23, 2, !dbg !403
  %add = add nsw i32 %div, 11, !dbg !404
  %16 = load %struct.lzma_options_lzma*, %struct.lzma_options_lzma** %opt, align 8, !dbg !405
  %dict_size24 = getelementptr inbounds %struct.lzma_options_lzma, %struct.lzma_options_lzma* %16, i32 0, i32 0, !dbg !406
  %17 = load i32, i32* %dict_size24, align 8, !dbg !407
  %shl = shl i32 %17, %add, !dbg !407
  store i32 %shl, i32* %dict_size24, align 8, !dbg !407
  br label %if.end25

if.end25:                                         ; preds = %if.else, %if.then17
  %18 = load %struct.lzma_options_lzma*, %struct.lzma_options_lzma** %opt, align 8, !dbg !408
  %preset_dict = getelementptr inbounds %struct.lzma_options_lzma, %struct.lzma_options_lzma* %18, i32 0, i32 1, !dbg !409
  store i8* null, i8** %preset_dict, align 8, !dbg !410
  %19 = load %struct.lzma_options_lzma*, %struct.lzma_options_lzma** %opt, align 8, !dbg !411
  %preset_dict_size = getelementptr inbounds %struct.lzma_options_lzma, %struct.lzma_options_lzma* %19, i32 0, i32 2, !dbg !412
  store i32 0, i32* %preset_dict_size, align 8, !dbg !413
  %20 = load %struct.lzma_options_lzma*, %struct.lzma_options_lzma** %opt, align 8, !dbg !414
  %21 = bitcast %struct.lzma_options_lzma* %20 to i8*, !dbg !414
  %22 = load i8**, i8*** %options.addr, align 8, !dbg !415
  store i8* %21, i8** %22, align 8, !dbg !416
  store i32 0, i32* %retval, align 4, !dbg !417
  br label %return, !dbg !417

return:                                           ; preds = %if.end25, %if.then11, %if.then7, %if.then1, %if.then
  %23 = load i32, i32* %retval, align 4, !dbg !418
  ret i32 %23, !dbg !418
}

declare noalias i8* @lzma_alloc(i64, %struct.lzma_allocator*) #3

; Function Attrs: nounwind uwtable
define internal i32 @lzma2_decode(%struct.lzma_coder_s* noalias %coder, %struct.lzma_dict* noalias %dict, i8* noalias %in, i64* noalias %in_pos, i64 %in_size) #0 !dbg !242 {
entry:
  %retval = alloca i32, align 4
  %coder.addr = alloca %struct.lzma_coder_s*, align 8
  %dict.addr = alloca %struct.lzma_dict*, align 8
  %in.addr = alloca i8*, align 8
  %in_pos.addr = alloca i64*, align 8
  %in_size.addr = alloca i64, align 8
  %control = alloca i32, align 4
  %in_start = alloca i64, align 8
  %ret = alloca i32, align 4
  %in_used = alloca i64, align 8
  store %struct.lzma_coder_s* %coder, %struct.lzma_coder_s** %coder.addr, align 8
  call void @llvm.dbg.declare(metadata %struct.lzma_coder_s** %coder.addr, metadata !419, metadata !257), !dbg !420
  store %struct.lzma_dict* %dict, %struct.lzma_dict** %dict.addr, align 8
  call void @llvm.dbg.declare(metadata %struct.lzma_dict** %dict.addr, metadata !421, metadata !257), !dbg !422
  store i8* %in, i8** %in.addr, align 8
  call void @llvm.dbg.declare(metadata i8** %in.addr, metadata !423, metadata !257), !dbg !424
  store i64* %in_pos, i64** %in_pos.addr, align 8
  call void @llvm.dbg.declare(metadata i64** %in_pos.addr, metadata !425, metadata !257), !dbg !426
  store i64 %in_size, i64* %in_size.addr, align 8
  call void @llvm.dbg.declare(metadata i64* %in_size.addr, metadata !427, metadata !257), !dbg !428
  br label %while.cond, !dbg !429

while.cond:                                       ; preds = %sw.epilog, %entry
  %0 = load i64*, i64** %in_pos.addr, align 8, !dbg !430
  %1 = load i64, i64* %0, align 8, !dbg !432
  %2 = load i64, i64* %in_size.addr, align 8, !dbg !433
  %cmp = icmp ult i64 %1, %2, !dbg !434
  br i1 %cmp, label %lor.end, label %lor.rhs, !dbg !435

lor.rhs:                                          ; preds = %while.cond
  %3 = load %struct.lzma_coder_s*, %struct.lzma_coder_s** %coder.addr, align 8, !dbg !436
  %sequence = getelementptr inbounds %struct.lzma_coder_s, %struct.lzma_coder_s* %3, i32 0, i32 0, !dbg !438
  %4 = load i32, i32* %sequence, align 8, !dbg !438
  %cmp1 = icmp eq i32 %4, 6, !dbg !439
  br label %lor.end, !dbg !440

lor.end:                                          ; preds = %lor.rhs, %while.cond
  %5 = phi i1 [ true, %while.cond ], [ %cmp1, %lor.rhs ]
  br i1 %5, label %while.body, label %while.end, !dbg !441

while.body:                                       ; preds = %lor.end
  %6 = load %struct.lzma_coder_s*, %struct.lzma_coder_s** %coder.addr, align 8, !dbg !443
  %sequence2 = getelementptr inbounds %struct.lzma_coder_s, %struct.lzma_coder_s* %6, i32 0, i32 0, !dbg !444
  %7 = load i32, i32* %sequence2, align 8, !dbg !444
  switch i32 %7, label %sw.default [
    i32 0, label %sw.bb
    i32 1, label %sw.bb50
    i32 2, label %sw.bb58
    i32 3, label %sw.bb71
    i32 4, label %sw.bb78
    i32 5, label %sw.bb88
    i32 6, label %sw.bb100
    i32 7, label %sw.bb122
  ], !dbg !445

sw.bb:                                            ; preds = %while.body
  call void @llvm.dbg.declare(metadata i32* %control, metadata !446, metadata !257), !dbg !450
  %8 = load i64*, i64** %in_pos.addr, align 8, !dbg !451
  %9 = load i64, i64* %8, align 8, !dbg !452
  %10 = load i8*, i8** %in.addr, align 8, !dbg !453
  %arrayidx = getelementptr inbounds i8, i8* %10, i64 %9, !dbg !453
  %11 = load i8, i8* %arrayidx, align 1, !dbg !453
  %conv = zext i8 %11 to i32, !dbg !453
  store i32 %conv, i32* %control, align 4, !dbg !450
  %12 = load i64*, i64** %in_pos.addr, align 8, !dbg !454
  %13 = load i64, i64* %12, align 8, !dbg !455
  %inc = add i64 %13, 1, !dbg !455
  store i64 %inc, i64* %12, align 8, !dbg !455
  %14 = load i32, i32* %control, align 4, !dbg !456
  %cmp3 = icmp eq i32 %14, 0, !dbg !458
  br i1 %cmp3, label %if.then, label %if.end, !dbg !459

if.then:                                          ; preds = %sw.bb
  store i32 1, i32* %retval, align 4, !dbg !460
  br label %return, !dbg !460

if.end:                                           ; preds = %sw.bb
  %15 = load i32, i32* %control, align 4, !dbg !461
  %cmp5 = icmp uge i32 %15, 224, !dbg !463
  br i1 %cmp5, label %if.then9, label %lor.lhs.false, !dbg !464

lor.lhs.false:                                    ; preds = %if.end
  %16 = load i32, i32* %control, align 4, !dbg !465
  %cmp7 = icmp eq i32 %16, 1, !dbg !467
  br i1 %cmp7, label %if.then9, label %if.else, !dbg !468

if.then9:                                         ; preds = %lor.lhs.false, %if.end
  %17 = load %struct.lzma_coder_s*, %struct.lzma_coder_s** %coder.addr, align 8, !dbg !469
  %need_properties = getelementptr inbounds %struct.lzma_coder_s, %struct.lzma_coder_s* %17, i32 0, i32 5, !dbg !471
  store i8 1, i8* %need_properties, align 8, !dbg !472
  %18 = load %struct.lzma_coder_s*, %struct.lzma_coder_s** %coder.addr, align 8, !dbg !473
  %need_dictionary_reset = getelementptr inbounds %struct.lzma_coder_s, %struct.lzma_coder_s* %18, i32 0, i32 6, !dbg !474
  store i8 1, i8* %need_dictionary_reset, align 1, !dbg !475
  br label %if.end13, !dbg !476

if.else:                                          ; preds = %lor.lhs.false
  %19 = load %struct.lzma_coder_s*, %struct.lzma_coder_s** %coder.addr, align 8, !dbg !477
  %need_dictionary_reset10 = getelementptr inbounds %struct.lzma_coder_s, %struct.lzma_coder_s* %19, i32 0, i32 6, !dbg !480
  %20 = load i8, i8* %need_dictionary_reset10, align 1, !dbg !480
  %tobool = trunc i8 %20 to i1, !dbg !480
  br i1 %tobool, label %if.then11, label %if.end12, !dbg !477

if.then11:                                        ; preds = %if.else
  store i32 9, i32* %retval, align 4, !dbg !481
  br label %return, !dbg !481

if.end12:                                         ; preds = %if.else
  br label %if.end13

if.end13:                                         ; preds = %if.end12, %if.then9
  %21 = load i32, i32* %control, align 4, !dbg !483
  %cmp14 = icmp uge i32 %21, 128, !dbg !485
  br i1 %cmp14, label %if.then16, label %if.else37, !dbg !486

if.then16:                                        ; preds = %if.end13
  %22 = load i32, i32* %control, align 4, !dbg !487
  %and = and i32 %22, 31, !dbg !489
  %shl = shl i32 %and, 16, !dbg !490
  %conv17 = zext i32 %shl to i64, !dbg !491
  %23 = load %struct.lzma_coder_s*, %struct.lzma_coder_s** %coder.addr, align 8, !dbg !492
  %uncompressed_size = getelementptr inbounds %struct.lzma_coder_s, %struct.lzma_coder_s* %23, i32 0, i32 3, !dbg !493
  store i64 %conv17, i64* %uncompressed_size, align 8, !dbg !494
  %24 = load %struct.lzma_coder_s*, %struct.lzma_coder_s** %coder.addr, align 8, !dbg !495
  %sequence18 = getelementptr inbounds %struct.lzma_coder_s, %struct.lzma_coder_s* %24, i32 0, i32 0, !dbg !496
  store i32 1, i32* %sequence18, align 8, !dbg !497
  %25 = load i32, i32* %control, align 4, !dbg !498
  %cmp19 = icmp uge i32 %25, 192, !dbg !500
  br i1 %cmp19, label %if.then21, label %if.else23, !dbg !501

if.then21:                                        ; preds = %if.then16
  %26 = load %struct.lzma_coder_s*, %struct.lzma_coder_s** %coder.addr, align 8, !dbg !502
  %need_properties22 = getelementptr inbounds %struct.lzma_coder_s, %struct.lzma_coder_s* %26, i32 0, i32 5, !dbg !504
  store i8 0, i8* %need_properties22, align 8, !dbg !505
  %27 = load %struct.lzma_coder_s*, %struct.lzma_coder_s** %coder.addr, align 8, !dbg !506
  %next_sequence = getelementptr inbounds %struct.lzma_coder_s, %struct.lzma_coder_s* %27, i32 0, i32 1, !dbg !507
  store i32 5, i32* %next_sequence, align 4, !dbg !508
  br label %if.end36, !dbg !509

if.else23:                                        ; preds = %if.then16
  %28 = load %struct.lzma_coder_s*, %struct.lzma_coder_s** %coder.addr, align 8, !dbg !510
  %need_properties24 = getelementptr inbounds %struct.lzma_coder_s, %struct.lzma_coder_s* %28, i32 0, i32 5, !dbg !513
  %29 = load i8, i8* %need_properties24, align 8, !dbg !513
  %tobool25 = trunc i8 %29 to i1, !dbg !513
  br i1 %tobool25, label %if.then26, label %if.else27, !dbg !510

if.then26:                                        ; preds = %if.else23
  store i32 9, i32* %retval, align 4, !dbg !514
  br label %return, !dbg !514

if.else27:                                        ; preds = %if.else23
  %30 = load %struct.lzma_coder_s*, %struct.lzma_coder_s** %coder.addr, align 8, !dbg !516
  %next_sequence28 = getelementptr inbounds %struct.lzma_coder_s, %struct.lzma_coder_s* %30, i32 0, i32 1, !dbg !518
  store i32 6, i32* %next_sequence28, align 4, !dbg !519
  %31 = load i32, i32* %control, align 4, !dbg !520
  %cmp29 = icmp uge i32 %31, 160, !dbg !522
  br i1 %cmp29, label %if.then31, label %if.end34, !dbg !523

if.then31:                                        ; preds = %if.else27
  %32 = load %struct.lzma_coder_s*, %struct.lzma_coder_s** %coder.addr, align 8, !dbg !524
  %lzma = getelementptr inbounds %struct.lzma_coder_s, %struct.lzma_coder_s* %32, i32 0, i32 2, !dbg !525
  %reset = getelementptr inbounds %struct.lzma_lz_decoder, %struct.lzma_lz_decoder* %lzma, i32 0, i32 2, !dbg !526
  %33 = load void (%struct.lzma_coder_s*, i8*)*, void (%struct.lzma_coder_s*, i8*)** %reset, align 8, !dbg !526
  %34 = load %struct.lzma_coder_s*, %struct.lzma_coder_s** %coder.addr, align 8, !dbg !527
  %lzma32 = getelementptr inbounds %struct.lzma_coder_s, %struct.lzma_coder_s* %34, i32 0, i32 2, !dbg !528
  %coder33 = getelementptr inbounds %struct.lzma_lz_decoder, %struct.lzma_lz_decoder* %lzma32, i32 0, i32 0, !dbg !529
  %35 = load %struct.lzma_coder_s*, %struct.lzma_coder_s** %coder33, align 8, !dbg !529
  %36 = load %struct.lzma_coder_s*, %struct.lzma_coder_s** %coder.addr, align 8, !dbg !530
  %options = getelementptr inbounds %struct.lzma_coder_s, %struct.lzma_coder_s* %36, i32 0, i32 7, !dbg !531
  %37 = bitcast %struct.lzma_options_lzma* %options to i8*, !dbg !532
  call void %33(%struct.lzma_coder_s* %35, i8* %37), !dbg !524
  br label %if.end34, !dbg !524

if.end34:                                         ; preds = %if.then31, %if.else27
  br label %if.end35

if.end35:                                         ; preds = %if.end34
  br label %if.end36

if.end36:                                         ; preds = %if.end35, %if.then21
  br label %if.end44, !dbg !533

if.else37:                                        ; preds = %if.end13
  %38 = load i32, i32* %control, align 4, !dbg !534
  %cmp38 = icmp ugt i32 %38, 2, !dbg !537
  br i1 %cmp38, label %if.then40, label %if.end41, !dbg !538

if.then40:                                        ; preds = %if.else37
  store i32 9, i32* %retval, align 4, !dbg !539
  br label %return, !dbg !539

if.end41:                                         ; preds = %if.else37
  %39 = load %struct.lzma_coder_s*, %struct.lzma_coder_s** %coder.addr, align 8, !dbg !540
  %sequence42 = getelementptr inbounds %struct.lzma_coder_s, %struct.lzma_coder_s* %39, i32 0, i32 0, !dbg !541
  store i32 3, i32* %sequence42, align 8, !dbg !542
  %40 = load %struct.lzma_coder_s*, %struct.lzma_coder_s** %coder.addr, align 8, !dbg !543
  %next_sequence43 = getelementptr inbounds %struct.lzma_coder_s, %struct.lzma_coder_s* %40, i32 0, i32 1, !dbg !544
  store i32 7, i32* %next_sequence43, align 4, !dbg !545
  br label %if.end44

if.end44:                                         ; preds = %if.end41, %if.end36
  %41 = load %struct.lzma_coder_s*, %struct.lzma_coder_s** %coder.addr, align 8, !dbg !546
  %need_dictionary_reset45 = getelementptr inbounds %struct.lzma_coder_s, %struct.lzma_coder_s* %41, i32 0, i32 6, !dbg !548
  %42 = load i8, i8* %need_dictionary_reset45, align 1, !dbg !548
  %tobool46 = trunc i8 %42 to i1, !dbg !548
  br i1 %tobool46, label %if.then47, label %if.end49, !dbg !549

if.then47:                                        ; preds = %if.end44
  %43 = load %struct.lzma_coder_s*, %struct.lzma_coder_s** %coder.addr, align 8, !dbg !550
  %need_dictionary_reset48 = getelementptr inbounds %struct.lzma_coder_s, %struct.lzma_coder_s* %43, i32 0, i32 6, !dbg !552
  store i8 0, i8* %need_dictionary_reset48, align 1, !dbg !553
  %44 = load %struct.lzma_dict*, %struct.lzma_dict** %dict.addr, align 8, !dbg !554
  call void @dict_reset(%struct.lzma_dict* %44), !dbg !555
  store i32 0, i32* %retval, align 4, !dbg !556
  br label %return, !dbg !556

if.end49:                                         ; preds = %if.end44
  br label %sw.epilog, !dbg !557

sw.bb50:                                          ; preds = %while.body
  %45 = load i64*, i64** %in_pos.addr, align 8, !dbg !558
  %46 = load i64, i64* %45, align 8, !dbg !559
  %inc51 = add i64 %46, 1, !dbg !559
  store i64 %inc51, i64* %45, align 8, !dbg !559
  %47 = load i8*, i8** %in.addr, align 8, !dbg !560
  %arrayidx52 = getelementptr inbounds i8, i8* %47, i64 %46, !dbg !560
  %48 = load i8, i8* %arrayidx52, align 1, !dbg !560
  %conv53 = zext i8 %48 to i32, !dbg !561
  %shl54 = shl i32 %conv53, 8, !dbg !562
  %conv55 = zext i32 %shl54 to i64, !dbg !561
  %49 = load %struct.lzma_coder_s*, %struct.lzma_coder_s** %coder.addr, align 8, !dbg !563
  %uncompressed_size56 = getelementptr inbounds %struct.lzma_coder_s, %struct.lzma_coder_s* %49, i32 0, i32 3, !dbg !564
  %50 = load i64, i64* %uncompressed_size56, align 8, !dbg !565
  %add = add i64 %50, %conv55, !dbg !565
  store i64 %add, i64* %uncompressed_size56, align 8, !dbg !565
  %51 = load %struct.lzma_coder_s*, %struct.lzma_coder_s** %coder.addr, align 8, !dbg !566
  %sequence57 = getelementptr inbounds %struct.lzma_coder_s, %struct.lzma_coder_s* %51, i32 0, i32 0, !dbg !567
  store i32 2, i32* %sequence57, align 8, !dbg !568
  br label %sw.epilog, !dbg !569

sw.bb58:                                          ; preds = %while.body
  %52 = load i64*, i64** %in_pos.addr, align 8, !dbg !570
  %53 = load i64, i64* %52, align 8, !dbg !571
  %inc59 = add i64 %53, 1, !dbg !571
  store i64 %inc59, i64* %52, align 8, !dbg !571
  %54 = load i8*, i8** %in.addr, align 8, !dbg !572
  %arrayidx60 = getelementptr inbounds i8, i8* %54, i64 %53, !dbg !572
  %55 = load i8, i8* %arrayidx60, align 1, !dbg !572
  %conv61 = zext i8 %55 to i32, !dbg !572
  %add62 = add nsw i32 %conv61, 1, !dbg !573
  %conv63 = sext i32 %add62 to i64, !dbg !572
  %56 = load %struct.lzma_coder_s*, %struct.lzma_coder_s** %coder.addr, align 8, !dbg !574
  %uncompressed_size64 = getelementptr inbounds %struct.lzma_coder_s, %struct.lzma_coder_s* %56, i32 0, i32 3, !dbg !575
  %57 = load i64, i64* %uncompressed_size64, align 8, !dbg !576
  %add65 = add i64 %57, %conv63, !dbg !576
  store i64 %add65, i64* %uncompressed_size64, align 8, !dbg !576
  %58 = load %struct.lzma_coder_s*, %struct.lzma_coder_s** %coder.addr, align 8, !dbg !577
  %sequence66 = getelementptr inbounds %struct.lzma_coder_s, %struct.lzma_coder_s* %58, i32 0, i32 0, !dbg !578
  store i32 3, i32* %sequence66, align 8, !dbg !579
  %59 = load %struct.lzma_coder_s*, %struct.lzma_coder_s** %coder.addr, align 8, !dbg !580
  %lzma67 = getelementptr inbounds %struct.lzma_coder_s, %struct.lzma_coder_s* %59, i32 0, i32 2, !dbg !581
  %set_uncompressed = getelementptr inbounds %struct.lzma_lz_decoder, %struct.lzma_lz_decoder* %lzma67, i32 0, i32 3, !dbg !582
  %60 = load void (%struct.lzma_coder_s*, i64)*, void (%struct.lzma_coder_s*, i64)** %set_uncompressed, align 8, !dbg !582
  %61 = load %struct.lzma_coder_s*, %struct.lzma_coder_s** %coder.addr, align 8, !dbg !583
  %lzma68 = getelementptr inbounds %struct.lzma_coder_s, %struct.lzma_coder_s* %61, i32 0, i32 2, !dbg !584
  %coder69 = getelementptr inbounds %struct.lzma_lz_decoder, %struct.lzma_lz_decoder* %lzma68, i32 0, i32 0, !dbg !585
  %62 = load %struct.lzma_coder_s*, %struct.lzma_coder_s** %coder69, align 8, !dbg !585
  %63 = load %struct.lzma_coder_s*, %struct.lzma_coder_s** %coder.addr, align 8, !dbg !586
  %uncompressed_size70 = getelementptr inbounds %struct.lzma_coder_s, %struct.lzma_coder_s* %63, i32 0, i32 3, !dbg !587
  %64 = load i64, i64* %uncompressed_size70, align 8, !dbg !587
  call void %60(%struct.lzma_coder_s* %62, i64 %64), !dbg !580
  br label %sw.epilog, !dbg !588

sw.bb71:                                          ; preds = %while.body
  %65 = load i64*, i64** %in_pos.addr, align 8, !dbg !589
  %66 = load i64, i64* %65, align 8, !dbg !590
  %inc72 = add i64 %66, 1, !dbg !590
  store i64 %inc72, i64* %65, align 8, !dbg !590
  %67 = load i8*, i8** %in.addr, align 8, !dbg !591
  %arrayidx73 = getelementptr inbounds i8, i8* %67, i64 %66, !dbg !591
  %68 = load i8, i8* %arrayidx73, align 1, !dbg !591
  %conv74 = zext i8 %68 to i32, !dbg !592
  %shl75 = shl i32 %conv74, 8, !dbg !593
  %conv76 = zext i32 %shl75 to i64, !dbg !592
  %69 = load %struct.lzma_coder_s*, %struct.lzma_coder_s** %coder.addr, align 8, !dbg !594
  %compressed_size = getelementptr inbounds %struct.lzma_coder_s, %struct.lzma_coder_s* %69, i32 0, i32 4, !dbg !595
  store i64 %conv76, i64* %compressed_size, align 8, !dbg !596
  %70 = load %struct.lzma_coder_s*, %struct.lzma_coder_s** %coder.addr, align 8, !dbg !597
  %sequence77 = getelementptr inbounds %struct.lzma_coder_s, %struct.lzma_coder_s* %70, i32 0, i32 0, !dbg !598
  store i32 4, i32* %sequence77, align 8, !dbg !599
  br label %sw.epilog, !dbg !600

sw.bb78:                                          ; preds = %while.body
  %71 = load i64*, i64** %in_pos.addr, align 8, !dbg !601
  %72 = load i64, i64* %71, align 8, !dbg !602
  %inc79 = add i64 %72, 1, !dbg !602
  store i64 %inc79, i64* %71, align 8, !dbg !602
  %73 = load i8*, i8** %in.addr, align 8, !dbg !603
  %arrayidx80 = getelementptr inbounds i8, i8* %73, i64 %72, !dbg !603
  %74 = load i8, i8* %arrayidx80, align 1, !dbg !603
  %conv81 = zext i8 %74 to i32, !dbg !603
  %add82 = add nsw i32 %conv81, 1, !dbg !604
  %conv83 = sext i32 %add82 to i64, !dbg !603
  %75 = load %struct.lzma_coder_s*, %struct.lzma_coder_s** %coder.addr, align 8, !dbg !605
  %compressed_size84 = getelementptr inbounds %struct.lzma_coder_s, %struct.lzma_coder_s* %75, i32 0, i32 4, !dbg !606
  %76 = load i64, i64* %compressed_size84, align 8, !dbg !607
  %add85 = add i64 %76, %conv83, !dbg !607
  store i64 %add85, i64* %compressed_size84, align 8, !dbg !607
  %77 = load %struct.lzma_coder_s*, %struct.lzma_coder_s** %coder.addr, align 8, !dbg !608
  %next_sequence86 = getelementptr inbounds %struct.lzma_coder_s, %struct.lzma_coder_s* %77, i32 0, i32 1, !dbg !609
  %78 = load i32, i32* %next_sequence86, align 4, !dbg !609
  %79 = load %struct.lzma_coder_s*, %struct.lzma_coder_s** %coder.addr, align 8, !dbg !610
  %sequence87 = getelementptr inbounds %struct.lzma_coder_s, %struct.lzma_coder_s* %79, i32 0, i32 0, !dbg !611
  store i32 %78, i32* %sequence87, align 8, !dbg !612
  br label %sw.epilog, !dbg !613

sw.bb88:                                          ; preds = %while.body
  %80 = load %struct.lzma_coder_s*, %struct.lzma_coder_s** %coder.addr, align 8, !dbg !614
  %options89 = getelementptr inbounds %struct.lzma_coder_s, %struct.lzma_coder_s* %80, i32 0, i32 7, !dbg !616
  %81 = load i64*, i64** %in_pos.addr, align 8, !dbg !617
  %82 = load i64, i64* %81, align 8, !dbg !618
  %inc90 = add i64 %82, 1, !dbg !618
  store i64 %inc90, i64* %81, align 8, !dbg !618
  %83 = load i8*, i8** %in.addr, align 8, !dbg !619
  %arrayidx91 = getelementptr inbounds i8, i8* %83, i64 %82, !dbg !619
  %84 = load i8, i8* %arrayidx91, align 1, !dbg !619
  %call = call zeroext i1 @lzma_lzma_lclppb_decode(%struct.lzma_options_lzma* %options89, i8 zeroext %84), !dbg !620
  br i1 %call, label %if.then92, label %if.end93, !dbg !621

if.then92:                                        ; preds = %sw.bb88
  store i32 9, i32* %retval, align 4, !dbg !622
  br label %return, !dbg !622

if.end93:                                         ; preds = %sw.bb88
  %85 = load %struct.lzma_coder_s*, %struct.lzma_coder_s** %coder.addr, align 8, !dbg !623
  %lzma94 = getelementptr inbounds %struct.lzma_coder_s, %struct.lzma_coder_s* %85, i32 0, i32 2, !dbg !624
  %reset95 = getelementptr inbounds %struct.lzma_lz_decoder, %struct.lzma_lz_decoder* %lzma94, i32 0, i32 2, !dbg !625
  %86 = load void (%struct.lzma_coder_s*, i8*)*, void (%struct.lzma_coder_s*, i8*)** %reset95, align 8, !dbg !625
  %87 = load %struct.lzma_coder_s*, %struct.lzma_coder_s** %coder.addr, align 8, !dbg !626
  %lzma96 = getelementptr inbounds %struct.lzma_coder_s, %struct.lzma_coder_s* %87, i32 0, i32 2, !dbg !627
  %coder97 = getelementptr inbounds %struct.lzma_lz_decoder, %struct.lzma_lz_decoder* %lzma96, i32 0, i32 0, !dbg !628
  %88 = load %struct.lzma_coder_s*, %struct.lzma_coder_s** %coder97, align 8, !dbg !628
  %89 = load %struct.lzma_coder_s*, %struct.lzma_coder_s** %coder.addr, align 8, !dbg !629
  %options98 = getelementptr inbounds %struct.lzma_coder_s, %struct.lzma_coder_s* %89, i32 0, i32 7, !dbg !630
  %90 = bitcast %struct.lzma_options_lzma* %options98 to i8*, !dbg !631
  call void %86(%struct.lzma_coder_s* %88, i8* %90), !dbg !623
  %91 = load %struct.lzma_coder_s*, %struct.lzma_coder_s** %coder.addr, align 8, !dbg !632
  %sequence99 = getelementptr inbounds %struct.lzma_coder_s, %struct.lzma_coder_s* %91, i32 0, i32 0, !dbg !633
  store i32 6, i32* %sequence99, align 8, !dbg !634
  br label %sw.epilog, !dbg !635

sw.bb100:                                         ; preds = %while.body
  call void @llvm.dbg.declare(metadata i64* %in_start, metadata !636, metadata !257), !dbg !639
  %92 = load i64*, i64** %in_pos.addr, align 8, !dbg !640
  %93 = load i64, i64* %92, align 8, !dbg !641
  store i64 %93, i64* %in_start, align 8, !dbg !639
  call void @llvm.dbg.declare(metadata i32* %ret, metadata !642, metadata !257), !dbg !644
  %94 = load %struct.lzma_coder_s*, %struct.lzma_coder_s** %coder.addr, align 8, !dbg !645
  %lzma101 = getelementptr inbounds %struct.lzma_coder_s, %struct.lzma_coder_s* %94, i32 0, i32 2, !dbg !646
  %code = getelementptr inbounds %struct.lzma_lz_decoder, %struct.lzma_lz_decoder* %lzma101, i32 0, i32 1, !dbg !647
  %95 = load i32 (%struct.lzma_coder_s*, %struct.lzma_dict*, i8*, i64*, i64)*, i32 (%struct.lzma_coder_s*, %struct.lzma_dict*, i8*, i64*, i64)** %code, align 8, !dbg !647
  %96 = load %struct.lzma_coder_s*, %struct.lzma_coder_s** %coder.addr, align 8, !dbg !648
  %lzma102 = getelementptr inbounds %struct.lzma_coder_s, %struct.lzma_coder_s* %96, i32 0, i32 2, !dbg !649
  %coder103 = getelementptr inbounds %struct.lzma_lz_decoder, %struct.lzma_lz_decoder* %lzma102, i32 0, i32 0, !dbg !650
  %97 = load %struct.lzma_coder_s*, %struct.lzma_coder_s** %coder103, align 8, !dbg !650
  %98 = load %struct.lzma_dict*, %struct.lzma_dict** %dict.addr, align 8, !dbg !651
  %99 = load i8*, i8** %in.addr, align 8, !dbg !652
  %100 = load i64*, i64** %in_pos.addr, align 8, !dbg !653
  %101 = load i64, i64* %in_size.addr, align 8, !dbg !654
  %call104 = call i32 %95(%struct.lzma_coder_s* %97, %struct.lzma_dict* %98, i8* %99, i64* %100, i64 %101), !dbg !645
  store i32 %call104, i32* %ret, align 4, !dbg !644
  call void @llvm.dbg.declare(metadata i64* %in_used, metadata !655, metadata !257), !dbg !656
  %102 = load i64*, i64** %in_pos.addr, align 8, !dbg !657
  %103 = load i64, i64* %102, align 8, !dbg !658
  %104 = load i64, i64* %in_start, align 8, !dbg !659
  %sub = sub i64 %103, %104, !dbg !660
  store i64 %sub, i64* %in_used, align 8, !dbg !656
  %105 = load i64, i64* %in_used, align 8, !dbg !661
  %106 = load %struct.lzma_coder_s*, %struct.lzma_coder_s** %coder.addr, align 8, !dbg !663
  %compressed_size105 = getelementptr inbounds %struct.lzma_coder_s, %struct.lzma_coder_s* %106, i32 0, i32 4, !dbg !664
  %107 = load i64, i64* %compressed_size105, align 8, !dbg !664
  %cmp106 = icmp ugt i64 %105, %107, !dbg !665
  br i1 %cmp106, label %if.then108, label %if.end109, !dbg !666

if.then108:                                       ; preds = %sw.bb100
  store i32 9, i32* %retval, align 4, !dbg !667
  br label %return, !dbg !667

if.end109:                                        ; preds = %sw.bb100
  %108 = load i64, i64* %in_used, align 8, !dbg !668
  %109 = load %struct.lzma_coder_s*, %struct.lzma_coder_s** %coder.addr, align 8, !dbg !669
  %compressed_size110 = getelementptr inbounds %struct.lzma_coder_s, %struct.lzma_coder_s* %109, i32 0, i32 4, !dbg !670
  %110 = load i64, i64* %compressed_size110, align 8, !dbg !671
  %sub111 = sub i64 %110, %108, !dbg !671
  store i64 %sub111, i64* %compressed_size110, align 8, !dbg !671
  %111 = load i32, i32* %ret, align 4, !dbg !672
  %cmp112 = icmp ne i32 %111, 1, !dbg !674
  br i1 %cmp112, label %if.then114, label %if.end115, !dbg !675

if.then114:                                       ; preds = %if.end109
  %112 = load i32, i32* %ret, align 4, !dbg !676
  store i32 %112, i32* %retval, align 4, !dbg !677
  br label %return, !dbg !677

if.end115:                                        ; preds = %if.end109
  %113 = load %struct.lzma_coder_s*, %struct.lzma_coder_s** %coder.addr, align 8, !dbg !678
  %compressed_size116 = getelementptr inbounds %struct.lzma_coder_s, %struct.lzma_coder_s* %113, i32 0, i32 4, !dbg !680
  %114 = load i64, i64* %compressed_size116, align 8, !dbg !680
  %cmp117 = icmp ne i64 %114, 0, !dbg !681
  br i1 %cmp117, label %if.then119, label %if.end120, !dbg !682

if.then119:                                       ; preds = %if.end115
  store i32 9, i32* %retval, align 4, !dbg !683
  br label %return, !dbg !683

if.end120:                                        ; preds = %if.end115
  %115 = load %struct.lzma_coder_s*, %struct.lzma_coder_s** %coder.addr, align 8, !dbg !684
  %sequence121 = getelementptr inbounds %struct.lzma_coder_s, %struct.lzma_coder_s* %115, i32 0, i32 0, !dbg !685
  store i32 0, i32* %sequence121, align 8, !dbg !686
  br label %sw.epilog, !dbg !687

sw.bb122:                                         ; preds = %while.body
  %116 = load %struct.lzma_dict*, %struct.lzma_dict** %dict.addr, align 8, !dbg !688
  %117 = load i8*, i8** %in.addr, align 8, !dbg !690
  %118 = load i64*, i64** %in_pos.addr, align 8, !dbg !691
  %119 = load i64, i64* %in_size.addr, align 8, !dbg !692
  %120 = load %struct.lzma_coder_s*, %struct.lzma_coder_s** %coder.addr, align 8, !dbg !693
  %compressed_size123 = getelementptr inbounds %struct.lzma_coder_s, %struct.lzma_coder_s* %120, i32 0, i32 4, !dbg !694
  call void @dict_write(%struct.lzma_dict* %116, i8* %117, i64* %118, i64 %119, i64* %compressed_size123), !dbg !695
  %121 = load %struct.lzma_coder_s*, %struct.lzma_coder_s** %coder.addr, align 8, !dbg !696
  %compressed_size124 = getelementptr inbounds %struct.lzma_coder_s, %struct.lzma_coder_s* %121, i32 0, i32 4, !dbg !698
  %122 = load i64, i64* %compressed_size124, align 8, !dbg !698
  %cmp125 = icmp ne i64 %122, 0, !dbg !699
  br i1 %cmp125, label %if.then127, label %if.end128, !dbg !700

if.then127:                                       ; preds = %sw.bb122
  store i32 0, i32* %retval, align 4, !dbg !701
  br label %return, !dbg !701

if.end128:                                        ; preds = %sw.bb122
  %123 = load %struct.lzma_coder_s*, %struct.lzma_coder_s** %coder.addr, align 8, !dbg !702
  %sequence129 = getelementptr inbounds %struct.lzma_coder_s, %struct.lzma_coder_s* %123, i32 0, i32 0, !dbg !703
  store i32 0, i32* %sequence129, align 8, !dbg !704
  br label %sw.epilog, !dbg !705

sw.default:                                       ; preds = %while.body
  call void @__assert_fail(i8* getelementptr inbounds ([2 x i8], [2 x i8]* @.str.2, i32 0, i32 0), i8* getelementptr inbounds ([83 x i8], [83 x i8]* @.str.1, i32 0, i32 0), i32 203, i8* getelementptr inbounds ([116 x i8], [116 x i8]* @__PRETTY_FUNCTION__.lzma2_decode, i32 0, i32 0)) #6, !dbg !706
  unreachable, !dbg !706

sw.epilog:                                        ; preds = %if.end128, %if.end120, %if.end93, %sw.bb78, %sw.bb71, %sw.bb58, %sw.bb50, %if.end49
  br label %while.cond, !dbg !707

while.end:                                        ; preds = %lor.end
  store i32 0, i32* %retval, align 4, !dbg !709
  br label %return, !dbg !709

return:                                           ; preds = %while.end, %if.then127, %if.then119, %if.then114, %if.then108, %if.then92, %if.then47, %if.then40, %if.then26, %if.then11, %if.then
  %124 = load i32, i32* %retval, align 4, !dbg !710
  ret i32 %124, !dbg !710
}

; Function Attrs: nounwind uwtable
define internal void @lzma2_decoder_end(%struct.lzma_coder_s* %coder, %struct.lzma_allocator* %allocator) #0 !dbg !249 {
entry:
  %coder.addr = alloca %struct.lzma_coder_s*, align 8
  %allocator.addr = alloca %struct.lzma_allocator*, align 8
  store %struct.lzma_coder_s* %coder, %struct.lzma_coder_s** %coder.addr, align 8
  call void @llvm.dbg.declare(metadata %struct.lzma_coder_s** %coder.addr, metadata !711, metadata !257), !dbg !712
  store %struct.lzma_allocator* %allocator, %struct.lzma_allocator** %allocator.addr, align 8
  call void @llvm.dbg.declare(metadata %struct.lzma_allocator** %allocator.addr, metadata !713, metadata !257), !dbg !714
  %0 = load %struct.lzma_coder_s*, %struct.lzma_coder_s** %coder.addr, align 8, !dbg !715
  %lzma = getelementptr inbounds %struct.lzma_coder_s, %struct.lzma_coder_s* %0, i32 0, i32 2, !dbg !715
  %end = getelementptr inbounds %struct.lzma_lz_decoder, %struct.lzma_lz_decoder* %lzma, i32 0, i32 4, !dbg !715
  %1 = load void (%struct.lzma_coder_s*, %struct.lzma_allocator*)*, void (%struct.lzma_coder_s*, %struct.lzma_allocator*)** %end, align 8, !dbg !715
  %cmp = icmp eq void (%struct.lzma_coder_s*, %struct.lzma_allocator*)* %1, null, !dbg !715
  br i1 %cmp, label %cond.true, label %cond.false, !dbg !715

cond.true:                                        ; preds = %entry
  br label %cond.end, !dbg !716

cond.false:                                       ; preds = %entry
  call void @__assert_fail(i8* getelementptr inbounds ([30 x i8], [30 x i8]* @.str.3, i32 0, i32 0), i8* getelementptr inbounds ([83 x i8], [83 x i8]* @.str.1, i32 0, i32 0), i32 214, i8* getelementptr inbounds ([55 x i8], [55 x i8]* @__PRETTY_FUNCTION__.lzma2_decoder_end, i32 0, i32 0)) #6, !dbg !718
  unreachable, !dbg !718
                                                  ; No predecessors!
  br label %cond.end, !dbg !720

cond.end:                                         ; preds = %2, %cond.true
  %3 = load %struct.lzma_coder_s*, %struct.lzma_coder_s** %coder.addr, align 8, !dbg !722
  %lzma1 = getelementptr inbounds %struct.lzma_coder_s, %struct.lzma_coder_s* %3, i32 0, i32 2, !dbg !723
  %coder2 = getelementptr inbounds %struct.lzma_lz_decoder, %struct.lzma_lz_decoder* %lzma1, i32 0, i32 0, !dbg !724
  %4 = load %struct.lzma_coder_s*, %struct.lzma_coder_s** %coder2, align 8, !dbg !724
  %5 = bitcast %struct.lzma_coder_s* %4 to i8*, !dbg !722
  %6 = load %struct.lzma_allocator*, %struct.lzma_allocator** %allocator.addr, align 8, !dbg !725
  call void @lzma_free(i8* %5, %struct.lzma_allocator* %6), !dbg !726
  %7 = load %struct.lzma_coder_s*, %struct.lzma_coder_s** %coder.addr, align 8, !dbg !727
  %8 = bitcast %struct.lzma_coder_s* %7 to i8*, !dbg !727
  %9 = load %struct.lzma_allocator*, %struct.lzma_allocator** %allocator.addr, align 8, !dbg !728
  call void @lzma_free(i8* %8, %struct.lzma_allocator* %9), !dbg !729
  ret void, !dbg !730
}

; Function Attrs: argmemonly nounwind
declare void @llvm.memcpy.p0i8.p0i8.i64(i8* nocapture, i8* nocapture readonly, i64, i32, i1) #4

declare i32 @lzma_lzma_decoder_create(%struct.lzma_lz_decoder*, %struct.lzma_allocator*, i8*, %struct.lzma_lz_options*) #3

; Function Attrs: inlinehint nounwind uwtable
define internal void @dict_reset(%struct.lzma_dict* %dict) #5 !dbg !243 {
entry:
  %dict.addr = alloca %struct.lzma_dict*, align 8
  store %struct.lzma_dict* %dict, %struct.lzma_dict** %dict.addr, align 8
  call void @llvm.dbg.declare(metadata %struct.lzma_dict** %dict.addr, metadata !731, metadata !257), !dbg !732
  %0 = load %struct.lzma_dict*, %struct.lzma_dict** %dict.addr, align 8, !dbg !733
  %need_reset = getelementptr inbounds %struct.lzma_dict, %struct.lzma_dict* %0, i32 0, i32 5, !dbg !734
  store i8 1, i8* %need_reset, align 8, !dbg !735
  ret void, !dbg !736
}

declare zeroext i1 @lzma_lzma_lclppb_decode(%struct.lzma_options_lzma*, i8 zeroext) #3

; Function Attrs: inlinehint nounwind uwtable
define internal void @dict_write(%struct.lzma_dict* noalias %dict, i8* noalias %in, i64* noalias %in_pos, i64 %in_size, i64* noalias %left) #5 !dbg !246 {
entry:
  %dict.addr = alloca %struct.lzma_dict*, align 8
  %in.addr = alloca i8*, align 8
  %in_pos.addr = alloca i64*, align 8
  %in_size.addr = alloca i64, align 8
  %left.addr = alloca i64*, align 8
  store %struct.lzma_dict* %dict, %struct.lzma_dict** %dict.addr, align 8
  call void @llvm.dbg.declare(metadata %struct.lzma_dict** %dict.addr, metadata !737, metadata !257), !dbg !738
  store i8* %in, i8** %in.addr, align 8
  call void @llvm.dbg.declare(metadata i8** %in.addr, metadata !739, metadata !257), !dbg !740
  store i64* %in_pos, i64** %in_pos.addr, align 8
  call void @llvm.dbg.declare(metadata i64** %in_pos.addr, metadata !741, metadata !257), !dbg !742
  store i64 %in_size, i64* %in_size.addr, align 8
  call void @llvm.dbg.declare(metadata i64* %in_size.addr, metadata !743, metadata !257), !dbg !744
  store i64* %left, i64** %left.addr, align 8
  call void @llvm.dbg.declare(metadata i64** %left.addr, metadata !745, metadata !257), !dbg !746
  %0 = load i64, i64* %in_size.addr, align 8, !dbg !747
  %1 = load i64*, i64** %in_pos.addr, align 8, !dbg !749
  %2 = load i64, i64* %1, align 8, !dbg !750
  %sub = sub i64 %0, %2, !dbg !751
  %3 = load i64*, i64** %left.addr, align 8, !dbg !752
  %4 = load i64, i64* %3, align 8, !dbg !753
  %cmp = icmp ugt i64 %sub, %4, !dbg !754
  br i1 %cmp, label %if.then, label %if.end, !dbg !755

if.then:                                          ; preds = %entry
  %5 = load i64*, i64** %in_pos.addr, align 8, !dbg !756
  %6 = load i64, i64* %5, align 8, !dbg !757
  %7 = load i64*, i64** %left.addr, align 8, !dbg !758
  %8 = load i64, i64* %7, align 8, !dbg !759
  %add = add i64 %6, %8, !dbg !760
  store i64 %add, i64* %in_size.addr, align 8, !dbg !761
  br label %if.end, !dbg !762

if.end:                                           ; preds = %if.then, %entry
  %9 = load i8*, i8** %in.addr, align 8, !dbg !763
  %10 = load i64*, i64** %in_pos.addr, align 8, !dbg !764
  %11 = load i64, i64* %in_size.addr, align 8, !dbg !765
  %12 = load %struct.lzma_dict*, %struct.lzma_dict** %dict.addr, align 8, !dbg !766
  %buf = getelementptr inbounds %struct.lzma_dict, %struct.lzma_dict* %12, i32 0, i32 0, !dbg !767
  %13 = load i8*, i8** %buf, align 8, !dbg !767
  %14 = load %struct.lzma_dict*, %struct.lzma_dict** %dict.addr, align 8, !dbg !768
  %pos = getelementptr inbounds %struct.lzma_dict, %struct.lzma_dict* %14, i32 0, i32 1, !dbg !769
  %15 = load %struct.lzma_dict*, %struct.lzma_dict** %dict.addr, align 8, !dbg !770
  %limit = getelementptr inbounds %struct.lzma_dict, %struct.lzma_dict* %15, i32 0, i32 3, !dbg !771
  %16 = load i64, i64* %limit, align 8, !dbg !771
  %call = call i64 @lzma_bufcpy(i8* %9, i64* %10, i64 %11, i8* %13, i64* %pos, i64 %16), !dbg !772
  %17 = load i64*, i64** %left.addr, align 8, !dbg !773
  %18 = load i64, i64* %17, align 8, !dbg !774
  %sub1 = sub i64 %18, %call, !dbg !774
  store i64 %sub1, i64* %17, align 8, !dbg !774
  %19 = load %struct.lzma_dict*, %struct.lzma_dict** %dict.addr, align 8, !dbg !775
  %pos2 = getelementptr inbounds %struct.lzma_dict, %struct.lzma_dict* %19, i32 0, i32 1, !dbg !777
  %20 = load i64, i64* %pos2, align 8, !dbg !777
  %21 = load %struct.lzma_dict*, %struct.lzma_dict** %dict.addr, align 8, !dbg !778
  %full = getelementptr inbounds %struct.lzma_dict, %struct.lzma_dict* %21, i32 0, i32 2, !dbg !779
  %22 = load i64, i64* %full, align 8, !dbg !779
  %cmp3 = icmp ugt i64 %20, %22, !dbg !780
  br i1 %cmp3, label %if.then4, label %if.end7, !dbg !781

if.then4:                                         ; preds = %if.end
  %23 = load %struct.lzma_dict*, %struct.lzma_dict** %dict.addr, align 8, !dbg !782
  %pos5 = getelementptr inbounds %struct.lzma_dict, %struct.lzma_dict* %23, i32 0, i32 1, !dbg !783
  %24 = load i64, i64* %pos5, align 8, !dbg !783
  %25 = load %struct.lzma_dict*, %struct.lzma_dict** %dict.addr, align 8, !dbg !784
  %full6 = getelementptr inbounds %struct.lzma_dict, %struct.lzma_dict* %25, i32 0, i32 2, !dbg !785
  store i64 %24, i64* %full6, align 8, !dbg !786
  br label %if.end7, !dbg !784

if.end7:                                          ; preds = %if.then4, %if.end
  ret void, !dbg !787
}

declare i64 @lzma_bufcpy(i8*, i64*, i64, i8*, i64*, i64) #3

declare void @lzma_free(i8*, %struct.lzma_allocator*) #3

attributes #0 = { nounwind uwtable "disable-tail-calls"="false" "less-precise-fpmad"="false" "no-frame-pointer-elim"="true" "no-frame-pointer-elim-non-leaf" "no-infs-fp-math"="false" "no-nans-fp-math"="false" "stack-protector-buffer-size"="8" "target-cpu"="x86-64" "target-features"="+fxsr,+mmx,+sse,+sse2" "unsafe-fp-math"="false" "use-soft-float"="false" }
attributes #1 = { nounwind readnone }
attributes #2 = { noreturn nounwind "disable-tail-calls"="false" "less-precise-fpmad"="false" "no-frame-pointer-elim"="true" "no-frame-pointer-elim-non-leaf" "no-infs-fp-math"="false" "no-nans-fp-math"="false" "stack-protector-buffer-size"="8" "target-cpu"="x86-64" "target-features"="+fxsr,+mmx,+sse,+sse2" "unsafe-fp-math"="false" "use-soft-float"="false" }
attributes #3 = { "disable-tail-calls"="false" "less-precise-fpmad"="false" "no-frame-pointer-elim"="true" "no-frame-pointer-elim-non-leaf" "no-infs-fp-math"="false" "no-nans-fp-math"="false" "stack-protector-buffer-size"="8" "target-cpu"="x86-64" "target-features"="+fxsr,+mmx,+sse,+sse2" "unsafe-fp-math"="false" "use-soft-float"="false" }
attributes #4 = { argmemonly nounwind }
attributes #5 = { inlinehint nounwind uwtable "disable-tail-calls"="false" "less-precise-fpmad"="false" "no-frame-pointer-elim"="true" "no-frame-pointer-elim-non-leaf" "no-infs-fp-math"="false" "no-nans-fp-math"="false" "stack-protector-buffer-size"="8" "target-cpu"="x86-64" "target-features"="+fxsr,+mmx,+sse,+sse2" "unsafe-fp-math"="false" "use-soft-float"="false" }
attributes #6 = { noreturn nounwind }

!llvm.dbg.cu = !{!0}
!llvm.module.flags = !{!253, !254}
!llvm.ident = !{!255}

!0 = distinct !DICompileUnit(language: DW_LANG_C99, file: !1, producer: "clang version 3.8.0 (tags/RELEASE_380/final)", isOptimized: false, runtimeVersion: 0, emissionKind: 1, enums: !2, retainedTypes: !56, subprograms: !61, globals: !250)
!1 = !DIFile(filename: "/data/download/cmake/cmake-master/Utilities/cmliblzma/liblzma/lzma/lzma2_decoder.c", directory: "/data/download/cmake/cmake-master/Utilities/cmliblzma")
!2 = !{!3, !18, !28, !33, !40, !43, !49}
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
!18 = !DICompositeType(tag: DW_TAG_enumeration_type, name: "sequence", file: !1, line: 20, size: 32, align: 32, elements: !19)
!19 = !{!20, !21, !22, !23, !24, !25, !26, !27}
!20 = !DIEnumerator(name: "SEQ_CONTROL", value: 0)
!21 = !DIEnumerator(name: "SEQ_UNCOMPRESSED_1", value: 1)
!22 = !DIEnumerator(name: "SEQ_UNCOMPRESSED_2", value: 2)
!23 = !DIEnumerator(name: "SEQ_COMPRESSED_0", value: 3)
!24 = !DIEnumerator(name: "SEQ_COMPRESSED_1", value: 4)
!25 = !DIEnumerator(name: "SEQ_PROPERTIES", value: 5)
!26 = !DIEnumerator(name: "SEQ_LZMA", value: 6)
!27 = !DIEnumerator(name: "SEQ_COPY", value: 7)
!28 = !DICompositeType(tag: DW_TAG_enumeration_type, file: !29, line: 138, size: 32, align: 32, elements: !30)
!29 = !DIFile(filename: "/data/download/cmake/cmake-master/Utilities/cmliblzma/liblzma/api/lzma/lzma.h", directory: "/data/download/cmake/cmake-master/Utilities/cmliblzma")
!30 = !{!31, !32}
!31 = !DIEnumerator(name: "LZMA_MODE_FAST", value: 1)
!32 = !DIEnumerator(name: "LZMA_MODE_NORMAL", value: 2)
!33 = !DICompositeType(tag: DW_TAG_enumeration_type, file: !29, line: 58, size: 32, align: 32, elements: !34)
!34 = !{!35, !36, !37, !38, !39}
!35 = !DIEnumerator(name: "LZMA_MF_HC3", value: 3)
!36 = !DIEnumerator(name: "LZMA_MF_HC4", value: 4)
!37 = !DIEnumerator(name: "LZMA_MF_BT2", value: 18)
!38 = !DIEnumerator(name: "LZMA_MF_BT3", value: 19)
!39 = !DIEnumerator(name: "LZMA_MF_BT4", value: 20)
!40 = !DICompositeType(tag: DW_TAG_enumeration_type, file: !4, line: 44, size: 32, align: 32, elements: !41)
!41 = !{!42}
!42 = !DIEnumerator(name: "LZMA_RESERVED_ENUM", value: 0)
!43 = !DICompositeType(tag: DW_TAG_enumeration_type, file: !4, line: 250, size: 32, align: 32, elements: !44)
!44 = !{!45, !46, !47, !48}
!45 = !DIEnumerator(name: "LZMA_RUN", value: 0)
!46 = !DIEnumerator(name: "LZMA_SYNC_FLUSH", value: 1)
!47 = !DIEnumerator(name: "LZMA_FULL_FLUSH", value: 2)
!48 = !DIEnumerator(name: "LZMA_FINISH", value: 3)
!49 = !DICompositeType(tag: DW_TAG_enumeration_type, file: !50, line: 27, size: 32, align: 32, elements: !51)
!50 = !DIFile(filename: "/data/download/cmake/cmake-master/Utilities/cmliblzma/liblzma/api/lzma/check.h", directory: "/data/download/cmake/cmake-master/Utilities/cmliblzma")
!51 = !{!52, !53, !54, !55}
!52 = !DIEnumerator(name: "LZMA_CHECK_NONE", value: 0)
!53 = !DIEnumerator(name: "LZMA_CHECK_CRC32", value: 1)
!54 = !DIEnumerator(name: "LZMA_CHECK_CRC64", value: 4)
!55 = !DIEnumerator(name: "LZMA_CHECK_SHA256", value: 10)
!56 = !{!57, !58}
!57 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: null, size: 64, align: 64)
!58 = !DIDerivedType(tag: DW_TAG_typedef, name: "uint32_t", file: !59, line: 51, baseType: !60)
!59 = !DIFile(filename: "/usr/include/stdint.h", directory: "/data/download/cmake/cmake-master/Utilities/cmliblzma")
!60 = !DIBasicType(name: "unsigned int", size: 32, align: 32, encoding: DW_ATE_unsigned)
!61 = !{!62, !224, !227, !231, !242, !243, !246, !249}
!62 = distinct !DISubprogram(name: "lzma_lzma2_decoder_init", scope: !1, file: !1, line: 251, type: !63, isLocal: false, isDefinition: true, scopeLine: 253, flags: DIFlagPrototyped, isOptimized: false, variables: !223)
!63 = !DISubroutineType(types: !64)
!64 = !{!65, !66, !129, !213}
!65 = !DIDerivedType(tag: DW_TAG_typedef, name: "lzma_ret", file: !4, line: 237, baseType: !3)
!66 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !67, size: 64, align: 64)
!67 = !DIDerivedType(tag: DW_TAG_typedef, name: "lzma_next_coder", file: !68, line: 75, baseType: !69)
!68 = !DIFile(filename: "/data/download/cmake/cmake-master/Utilities/cmliblzma/liblzma/common/common.h", directory: "/data/download/cmake/cmake-master/Utilities/cmliblzma")
!69 = !DICompositeType(tag: DW_TAG_structure_type, name: "lzma_next_coder_s", file: !68, line: 119, size: 512, align: 64, elements: !70)
!70 = !{!71, !177, !178, !180, !187, !189, !196, !201}
!71 = !DIDerivedType(tag: DW_TAG_member, name: "coder", scope: !69, file: !68, line: 121, baseType: !72, size: 64, align: 64)
!72 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !73, size: 64, align: 64)
!73 = !DIDerivedType(tag: DW_TAG_typedef, name: "lzma_coder", file: !68, line: 73, baseType: !74)
!74 = !DICompositeType(tag: DW_TAG_structure_type, name: "lzma_coder_s", file: !1, line: 19, size: 1472, align: 64, elements: !75)
!75 = !{!76, !77, !78, !142, !143, !144, !145, !146}
!76 = !DIDerivedType(tag: DW_TAG_member, name: "sequence", scope: !74, file: !1, line: 29, baseType: !18, size: 32, align: 32)
!77 = !DIDerivedType(tag: DW_TAG_member, name: "next_sequence", scope: !74, file: !1, line: 32, baseType: !18, size: 32, align: 32, offset: 32)
!78 = !DIDerivedType(tag: DW_TAG_member, name: "lzma", scope: !74, file: !1, line: 35, baseType: !79, size: 320, align: 64, offset: 64)
!79 = !DIDerivedType(tag: DW_TAG_typedef, name: "lzma_lz_decoder", file: !80, line: 72, baseType: !81)
!80 = !DIFile(filename: "/data/download/cmake/cmake-master/Utilities/cmliblzma/liblzma/lz/lz_decoder.h", directory: "/data/download/cmake/cmake-master/Utilities/cmliblzma")
!81 = !DICompositeType(tag: DW_TAG_structure_type, file: !80, line: 54, size: 320, align: 64, elements: !82)
!82 = !{!83, !84, !112, !118, !125}
!83 = !DIDerivedType(tag: DW_TAG_member, name: "coder", scope: !81, file: !80, line: 56, baseType: !72, size: 64, align: 64)
!84 = !DIDerivedType(tag: DW_TAG_member, name: "code", scope: !81, file: !80, line: 59, baseType: !85, size: 64, align: 64, offset: 64)
!85 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !86, size: 64, align: 64)
!86 = !DISubroutineType(types: !87)
!87 = !{!65, !88, !89, !107, !110, !99}
!88 = !DIDerivedType(tag: DW_TAG_restrict_type, baseType: !72)
!89 = !DIDerivedType(tag: DW_TAG_restrict_type, baseType: !90)
!90 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !91, size: 64, align: 64)
!91 = !DIDerivedType(tag: DW_TAG_typedef, name: "lzma_dict", file: !80, line: 44, baseType: !92)
!92 = !DICompositeType(tag: DW_TAG_structure_type, file: !80, line: 20, size: 384, align: 64, elements: !93)
!93 = !{!94, !98, !102, !103, !104, !105}
!94 = !DIDerivedType(tag: DW_TAG_member, name: "buf", scope: !92, file: !80, line: 24, baseType: !95, size: 64, align: 64)
!95 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !96, size: 64, align: 64)
!96 = !DIDerivedType(tag: DW_TAG_typedef, name: "uint8_t", file: !59, line: 48, baseType: !97)
!97 = !DIBasicType(name: "unsigned char", size: 8, align: 8, encoding: DW_ATE_unsigned_char)
!98 = !DIDerivedType(tag: DW_TAG_member, name: "pos", scope: !92, file: !80, line: 28, baseType: !99, size: 64, align: 64, offset: 64)
!99 = !DIDerivedType(tag: DW_TAG_typedef, name: "size_t", file: !100, line: 62, baseType: !101)
!100 = !DIFile(filename: "/opt/llvm-build/bin/../lib/clang/3.8.0/include/stddef.h", directory: "/data/download/cmake/cmake-master/Utilities/cmliblzma")
!101 = !DIBasicType(name: "long unsigned int", size: 64, align: 64, encoding: DW_ATE_unsigned)
!102 = !DIDerivedType(tag: DW_TAG_member, name: "full", scope: !92, file: !80, line: 33, baseType: !99, size: 64, align: 64, offset: 128)
!103 = !DIDerivedType(tag: DW_TAG_member, name: "limit", scope: !92, file: !80, line: 36, baseType: !99, size: 64, align: 64, offset: 192)
!104 = !DIDerivedType(tag: DW_TAG_member, name: "size", scope: !92, file: !80, line: 39, baseType: !99, size: 64, align: 64, offset: 256)
!105 = !DIDerivedType(tag: DW_TAG_member, name: "need_reset", scope: !92, file: !80, line: 42, baseType: !106, size: 8, align: 8, offset: 320)
!106 = !DIBasicType(name: "_Bool", size: 8, align: 8, encoding: DW_ATE_boolean)
!107 = !DIDerivedType(tag: DW_TAG_restrict_type, baseType: !108)
!108 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !109, size: 64, align: 64)
!109 = !DIDerivedType(tag: DW_TAG_const_type, baseType: !96)
!110 = !DIDerivedType(tag: DW_TAG_restrict_type, baseType: !111)
!111 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !99, size: 64, align: 64)
!112 = !DIDerivedType(tag: DW_TAG_member, name: "reset", scope: !81, file: !80, line: 63, baseType: !113, size: 64, align: 64, offset: 128)
!113 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !114, size: 64, align: 64)
!114 = !DISubroutineType(types: !115)
!115 = !{null, !72, !116}
!116 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !117, size: 64, align: 64)
!117 = !DIDerivedType(tag: DW_TAG_const_type, baseType: null)
!118 = !DIDerivedType(tag: DW_TAG_member, name: "set_uncompressed", scope: !81, file: !80, line: 66, baseType: !119, size: 64, align: 64, offset: 192)
!119 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !120, size: 64, align: 64)
!120 = !DISubroutineType(types: !121)
!121 = !{null, !72, !122}
!122 = !DIDerivedType(tag: DW_TAG_typedef, name: "lzma_vli", file: !123, line: 63, baseType: !124)
!123 = !DIFile(filename: "/data/download/cmake/cmake-master/Utilities/cmliblzma/liblzma/api/lzma/vli.h", directory: "/data/download/cmake/cmake-master/Utilities/cmliblzma")
!124 = !DIDerivedType(tag: DW_TAG_typedef, name: "uint64_t", file: !59, line: 55, baseType: !101)
!125 = !DIDerivedType(tag: DW_TAG_member, name: "end", scope: !81, file: !80, line: 70, baseType: !126, size: 64, align: 64, offset: 256)
!126 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !127, size: 64, align: 64)
!127 = !DISubroutineType(types: !128)
!128 = !{null, !72, !129}
!129 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !130, size: 64, align: 64)
!130 = !DIDerivedType(tag: DW_TAG_typedef, name: "lzma_allocator", file: !4, line: 403, baseType: !131)
!131 = !DICompositeType(tag: DW_TAG_structure_type, file: !4, line: 341, size: 192, align: 64, elements: !132)
!132 = !{!133, !137, !141}
!133 = !DIDerivedType(tag: DW_TAG_member, name: "alloc", scope: !131, file: !4, line: 376, baseType: !134, size: 64, align: 64)
!134 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !135, size: 64, align: 64)
!135 = !DISubroutineType(types: !136)
!136 = !{!57, !57, !99, !99}
!137 = !DIDerivedType(tag: DW_TAG_member, name: "free", scope: !131, file: !4, line: 390, baseType: !138, size: 64, align: 64, offset: 64)
!138 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !139, size: 64, align: 64)
!139 = !DISubroutineType(types: !140)
!140 = !{null, !57, !57}
!141 = !DIDerivedType(tag: DW_TAG_member, name: "opaque", scope: !131, file: !4, line: 401, baseType: !57, size: 64, align: 64, offset: 128)
!142 = !DIDerivedType(tag: DW_TAG_member, name: "uncompressed_size", scope: !74, file: !1, line: 38, baseType: !99, size: 64, align: 64, offset: 384)
!143 = !DIDerivedType(tag: DW_TAG_member, name: "compressed_size", scope: !74, file: !1, line: 42, baseType: !99, size: 64, align: 64, offset: 448)
!144 = !DIDerivedType(tag: DW_TAG_member, name: "need_properties", scope: !74, file: !1, line: 46, baseType: !106, size: 8, align: 8, offset: 512)
!145 = !DIDerivedType(tag: DW_TAG_member, name: "need_dictionary_reset", scope: !74, file: !1, line: 50, baseType: !106, size: 8, align: 8, offset: 520)
!146 = !DIDerivedType(tag: DW_TAG_member, name: "options", scope: !74, file: !1, line: 52, baseType: !147, size: 896, align: 64, offset: 576)
!147 = !DIDerivedType(tag: DW_TAG_typedef, name: "lzma_options_lzma", file: !29, line: 399, baseType: !148)
!148 = !DICompositeType(tag: DW_TAG_structure_type, file: !29, line: 185, size: 896, align: 64, elements: !149)
!149 = !{!150, !151, !152, !153, !154, !155, !156, !158, !159, !161, !162, !163, !164, !165, !166, !167, !168, !169, !170, !172, !173, !174, !175, !176}
!150 = !DIDerivedType(tag: DW_TAG_member, name: "dict_size", scope: !148, file: !29, line: 217, baseType: !58, size: 32, align: 32)
!151 = !DIDerivedType(tag: DW_TAG_member, name: "preset_dict", scope: !148, file: !29, line: 240, baseType: !108, size: 64, align: 64, offset: 64)
!152 = !DIDerivedType(tag: DW_TAG_member, name: "preset_dict_size", scope: !148, file: !29, line: 254, baseType: !58, size: 32, align: 32, offset: 128)
!153 = !DIDerivedType(tag: DW_TAG_member, name: "lc", scope: !148, file: !29, line: 281, baseType: !58, size: 32, align: 32, offset: 160)
!154 = !DIDerivedType(tag: DW_TAG_member, name: "lp", scope: !148, file: !29, line: 293, baseType: !58, size: 32, align: 32, offset: 192)
!155 = !DIDerivedType(tag: DW_TAG_member, name: "pb", scope: !148, file: !29, line: 316, baseType: !58, size: 32, align: 32, offset: 224)
!156 = !DIDerivedType(tag: DW_TAG_member, name: "mode", scope: !148, file: !29, line: 322, baseType: !157, size: 32, align: 32, offset: 256)
!157 = !DIDerivedType(tag: DW_TAG_typedef, name: "lzma_mode", file: !29, line: 155, baseType: !28)
!158 = !DIDerivedType(tag: DW_TAG_member, name: "nice_len", scope: !148, file: !29, line: 342, baseType: !58, size: 32, align: 32, offset: 288)
!159 = !DIDerivedType(tag: DW_TAG_member, name: "mf", scope: !148, file: !29, line: 345, baseType: !160, size: 32, align: 32, offset: 320)
!160 = !DIDerivedType(tag: DW_TAG_typedef, name: "lzma_match_finder", file: !29, line: 111, baseType: !33)
!161 = !DIDerivedType(tag: DW_TAG_member, name: "depth", scope: !148, file: !29, line: 375, baseType: !58, size: 32, align: 32, offset: 352)
!162 = !DIDerivedType(tag: DW_TAG_member, name: "reserved_int1", scope: !148, file: !29, line: 384, baseType: !58, size: 32, align: 32, offset: 384)
!163 = !DIDerivedType(tag: DW_TAG_member, name: "reserved_int2", scope: !148, file: !29, line: 385, baseType: !58, size: 32, align: 32, offset: 416)
!164 = !DIDerivedType(tag: DW_TAG_member, name: "reserved_int3", scope: !148, file: !29, line: 386, baseType: !58, size: 32, align: 32, offset: 448)
!165 = !DIDerivedType(tag: DW_TAG_member, name: "reserved_int4", scope: !148, file: !29, line: 387, baseType: !58, size: 32, align: 32, offset: 480)
!166 = !DIDerivedType(tag: DW_TAG_member, name: "reserved_int5", scope: !148, file: !29, line: 388, baseType: !58, size: 32, align: 32, offset: 512)
!167 = !DIDerivedType(tag: DW_TAG_member, name: "reserved_int6", scope: !148, file: !29, line: 389, baseType: !58, size: 32, align: 32, offset: 544)
!168 = !DIDerivedType(tag: DW_TAG_member, name: "reserved_int7", scope: !148, file: !29, line: 390, baseType: !58, size: 32, align: 32, offset: 576)
!169 = !DIDerivedType(tag: DW_TAG_member, name: "reserved_int8", scope: !148, file: !29, line: 391, baseType: !58, size: 32, align: 32, offset: 608)
!170 = !DIDerivedType(tag: DW_TAG_member, name: "reserved_enum1", scope: !148, file: !29, line: 392, baseType: !171, size: 32, align: 32, offset: 640)
!171 = !DIDerivedType(tag: DW_TAG_typedef, name: "lzma_reserved_enum", file: !4, line: 46, baseType: !40)
!172 = !DIDerivedType(tag: DW_TAG_member, name: "reserved_enum2", scope: !148, file: !29, line: 393, baseType: !171, size: 32, align: 32, offset: 672)
!173 = !DIDerivedType(tag: DW_TAG_member, name: "reserved_enum3", scope: !148, file: !29, line: 394, baseType: !171, size: 32, align: 32, offset: 704)
!174 = !DIDerivedType(tag: DW_TAG_member, name: "reserved_enum4", scope: !148, file: !29, line: 395, baseType: !171, size: 32, align: 32, offset: 736)
!175 = !DIDerivedType(tag: DW_TAG_member, name: "reserved_ptr1", scope: !148, file: !29, line: 396, baseType: !57, size: 64, align: 64, offset: 768)
!176 = !DIDerivedType(tag: DW_TAG_member, name: "reserved_ptr2", scope: !148, file: !29, line: 397, baseType: !57, size: 64, align: 64, offset: 832)
!177 = !DIDerivedType(tag: DW_TAG_member, name: "id", scope: !69, file: !68, line: 125, baseType: !122, size: 64, align: 64, offset: 64)
!178 = !DIDerivedType(tag: DW_TAG_member, name: "init", scope: !69, file: !68, line: 131, baseType: !179, size: 64, align: 64, offset: 128)
!179 = !DIDerivedType(tag: DW_TAG_typedef, name: "uintptr_t", file: !59, line: 122, baseType: !101)
!180 = !DIDerivedType(tag: DW_TAG_member, name: "code", scope: !69, file: !68, line: 134, baseType: !181, size: 64, align: 64, offset: 192)
!181 = !DIDerivedType(tag: DW_TAG_typedef, name: "lzma_code_function", file: !68, line: 89, baseType: !182)
!182 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !183, size: 64, align: 64)
!183 = !DISubroutineType(types: !184)
!184 = !{!65, !72, !129, !107, !110, !99, !185, !110, !99, !186}
!185 = !DIDerivedType(tag: DW_TAG_restrict_type, baseType: !95)
!186 = !DIDerivedType(tag: DW_TAG_typedef, name: "lzma_action", file: !4, line: 322, baseType: !43)
!187 = !DIDerivedType(tag: DW_TAG_member, name: "end", scope: !69, file: !68, line: 139, baseType: !188, size: 64, align: 64, offset: 256)
!188 = !DIDerivedType(tag: DW_TAG_typedef, name: "lzma_end_function", file: !68, line: 97, baseType: !126)
!189 = !DIDerivedType(tag: DW_TAG_member, name: "get_check", scope: !69, file: !68, line: 143, baseType: !190, size: 64, align: 64, offset: 320)
!190 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !191, size: 64, align: 64)
!191 = !DISubroutineType(types: !192)
!192 = !{!193, !194}
!193 = !DIDerivedType(tag: DW_TAG_typedef, name: "lzma_check", file: !50, line: 55, baseType: !49)
!194 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !195, size: 64, align: 64)
!195 = !DIDerivedType(tag: DW_TAG_const_type, baseType: !73)
!196 = !DIDerivedType(tag: DW_TAG_member, name: "memconfig", scope: !69, file: !68, line: 147, baseType: !197, size: 64, align: 64, offset: 384)
!197 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !198, size: 64, align: 64)
!198 = !DISubroutineType(types: !199)
!199 = !{!65, !72, !200, !200, !124}
!200 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !124, size: 64, align: 64)
!201 = !DIDerivedType(tag: DW_TAG_member, name: "update", scope: !69, file: !68, line: 152, baseType: !202, size: 64, align: 64, offset: 448)
!202 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !203, size: 64, align: 64)
!203 = !DISubroutineType(types: !204)
!204 = !{!65, !72, !129, !205, !205}
!205 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !206, size: 64, align: 64)
!206 = !DIDerivedType(tag: DW_TAG_const_type, baseType: !207)
!207 = !DIDerivedType(tag: DW_TAG_typedef, name: "lzma_filter", file: !208, line: 65, baseType: !209)
!208 = !DIFile(filename: "/data/download/cmake/cmake-master/Utilities/cmliblzma/liblzma/api/lzma/filter.h", directory: "/data/download/cmake/cmake-master/Utilities/cmliblzma")
!209 = !DICompositeType(tag: DW_TAG_structure_type, file: !208, line: 43, size: 128, align: 64, elements: !210)
!210 = !{!211, !212}
!211 = !DIDerivedType(tag: DW_TAG_member, name: "id", scope: !209, file: !208, line: 54, baseType: !122, size: 64, align: 64)
!212 = !DIDerivedType(tag: DW_TAG_member, name: "options", scope: !209, file: !208, line: 63, baseType: !57, size: 64, align: 64, offset: 64)
!213 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !214, size: 64, align: 64)
!214 = !DIDerivedType(tag: DW_TAG_const_type, baseType: !215)
!215 = !DIDerivedType(tag: DW_TAG_typedef, name: "lzma_filter_info", file: !68, line: 77, baseType: !216)
!216 = !DICompositeType(tag: DW_TAG_structure_type, name: "lzma_filter_info_s", file: !68, line: 104, size: 192, align: 64, elements: !217)
!217 = !{!218, !219, !222}
!218 = !DIDerivedType(tag: DW_TAG_member, name: "id", scope: !216, file: !68, line: 107, baseType: !122, size: 64, align: 64)
!219 = !DIDerivedType(tag: DW_TAG_member, name: "init", scope: !216, file: !68, line: 111, baseType: !220, size: 64, align: 64, offset: 64)
!220 = !DIDerivedType(tag: DW_TAG_typedef, name: "lzma_init_function", file: !68, line: 81, baseType: !221)
!221 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !63, size: 64, align: 64)
!222 = !DIDerivedType(tag: DW_TAG_member, name: "options", scope: !216, file: !68, line: 114, baseType: !57, size: 64, align: 64, offset: 128)
!223 = !{}
!224 = distinct !DISubprogram(name: "lzma_lzma2_decoder_memusage", scope: !1, file: !1, line: 264, type: !225, isLocal: false, isDefinition: true, scopeLine: 265, flags: DIFlagPrototyped, isOptimized: false, variables: !223)
!225 = !DISubroutineType(types: !226)
!226 = !{!124, !116}
!227 = distinct !DISubprogram(name: "lzma_lzma2_props_decode", scope: !1, file: !1, line: 272, type: !228, isLocal: false, isDefinition: true, scopeLine: 274, flags: DIFlagPrototyped, isOptimized: false, variables: !223)
!228 = !DISubroutineType(types: !229)
!229 = !{!65, !230, !129, !108, !99}
!230 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !57, size: 64, align: 64)
!231 = distinct !DISubprogram(name: "lzma2_decoder_init", scope: !1, file: !1, line: 224, type: !232, isLocal: true, isDefinition: true, scopeLine: 226, flags: DIFlagPrototyped, isOptimized: false, variables: !223)
!232 = !DISubroutineType(types: !233)
!233 = !{!65, !234, !129, !116, !235}
!234 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !79, size: 64, align: 64)
!235 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !236, size: 64, align: 64)
!236 = !DIDerivedType(tag: DW_TAG_typedef, name: "lzma_lz_options", file: !80, line: 51, baseType: !237)
!237 = !DICompositeType(tag: DW_TAG_structure_type, file: !80, line: 47, size: 192, align: 64, elements: !238)
!238 = !{!239, !240, !241}
!239 = !DIDerivedType(tag: DW_TAG_member, name: "dict_size", scope: !237, file: !80, line: 48, baseType: !99, size: 64, align: 64)
!240 = !DIDerivedType(tag: DW_TAG_member, name: "preset_dict", scope: !237, file: !80, line: 49, baseType: !108, size: 64, align: 64, offset: 64)
!241 = !DIDerivedType(tag: DW_TAG_member, name: "preset_dict_size", scope: !237, file: !80, line: 50, baseType: !99, size: 64, align: 64, offset: 128)
!242 = distinct !DISubprogram(name: "lzma2_decode", scope: !1, file: !1, line: 57, type: !86, isLocal: true, isDefinition: true, scopeLine: 60, flags: DIFlagPrototyped, isOptimized: false, variables: !223)
!243 = distinct !DISubprogram(name: "dict_reset", scope: !80, file: !80, line: 230, type: !244, isLocal: true, isDefinition: true, scopeLine: 231, flags: DIFlagPrototyped, isOptimized: false, variables: !223)
!244 = !DISubroutineType(types: !245)
!245 = !{null, !90}
!246 = distinct !DISubprogram(name: "dict_write", scope: !80, file: !80, line: 205, type: !247, isLocal: true, isDefinition: true, scopeLine: 208, flags: DIFlagPrototyped, isOptimized: false, variables: !223)
!247 = !DISubroutineType(types: !248)
!248 = !{null, !89, !107, !110, !99, !110}
!249 = distinct !DISubprogram(name: "lzma2_decoder_end", scope: !1, file: !1, line: 212, type: !127, isLocal: true, isDefinition: true, scopeLine: 213, flags: DIFlagPrototyped, isOptimized: false, variables: !223)
!250 = !{!251}
!251 = !DIGlobalVariable(name: "LZMA_LZ_DECODER_INIT", scope: !0, file: !80, line: 75, type: !252, isLocal: true, isDefinition: true, variable: %struct.lzma_lz_decoder* @LZMA_LZ_DECODER_INIT)
!252 = !DIDerivedType(tag: DW_TAG_const_type, baseType: !79)
!253 = !{i32 2, !"Dwarf Version", i32 4}
!254 = !{i32 2, !"Debug Info Version", i32 3}
!255 = !{!"clang version 3.8.0 (tags/RELEASE_380/final)"}
!256 = !DILocalVariable(name: "next", arg: 1, scope: !62, file: !1, line: 251, type: !66)
!257 = !DIExpression()
!258 = !DILocation(line: 251, column: 42, scope: !62)
!259 = !DILocalVariable(name: "allocator", arg: 2, scope: !62, file: !1, line: 251, type: !129)
!260 = !DILocation(line: 251, column: 64, scope: !62)
!261 = !DILocalVariable(name: "filters", arg: 3, scope: !62, file: !1, line: 252, type: !213)
!262 = !DILocation(line: 252, column: 27, scope: !62)
!263 = !DILocation(line: 256, column: 2, scope: !62)
!264 = !DILocation(line: 256, column: 2, scope: !265)
!265 = !DILexicalBlockFile(scope: !62, file: !1, discriminator: 1)
!266 = !DILocation(line: 256, column: 2, scope: !267)
!267 = !DILexicalBlockFile(scope: !62, file: !1, discriminator: 2)
!268 = !DILocation(line: 256, column: 2, scope: !269)
!269 = !DILexicalBlockFile(scope: !62, file: !1, discriminator: 3)
!270 = !DILocation(line: 258, column: 30, scope: !62)
!271 = !DILocation(line: 258, column: 36, scope: !62)
!272 = !DILocation(line: 258, column: 47, scope: !62)
!273 = !DILocation(line: 258, column: 9, scope: !62)
!274 = !DILocation(line: 258, column: 2, scope: !62)
!275 = !DILocalVariable(name: "lz", arg: 1, scope: !231, file: !1, line: 224, type: !234)
!276 = !DILocation(line: 224, column: 37, scope: !231)
!277 = !DILocalVariable(name: "allocator", arg: 2, scope: !231, file: !1, line: 224, type: !129)
!278 = !DILocation(line: 224, column: 57, scope: !231)
!279 = !DILocalVariable(name: "opt", arg: 3, scope: !231, file: !1, line: 225, type: !116)
!280 = !DILocation(line: 225, column: 15, scope: !231)
!281 = !DILocalVariable(name: "lz_options", arg: 4, scope: !231, file: !1, line: 225, type: !235)
!282 = !DILocation(line: 225, column: 37, scope: !231)
!283 = !DILocalVariable(name: "options", scope: !231, file: !1, line: 227, type: !284)
!284 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !285, size: 64, align: 64)
!285 = !DIDerivedType(tag: DW_TAG_const_type, baseType: !147)
!286 = !DILocation(line: 227, column: 27, scope: !231)
!287 = !DILocation(line: 227, column: 37, scope: !231)
!288 = !DILocation(line: 229, column: 6, scope: !289)
!289 = distinct !DILexicalBlock(scope: !231, file: !1, line: 229, column: 6)
!290 = !DILocation(line: 229, column: 10, scope: !289)
!291 = !DILocation(line: 229, column: 16, scope: !289)
!292 = !DILocation(line: 229, column: 6, scope: !231)
!293 = !DILocation(line: 230, column: 46, scope: !294)
!294 = distinct !DILexicalBlock(scope: !289, file: !1, line: 229, column: 25)
!295 = !DILocation(line: 230, column: 15, scope: !294)
!296 = !DILocation(line: 230, column: 3, scope: !294)
!297 = !DILocation(line: 230, column: 7, scope: !294)
!298 = !DILocation(line: 230, column: 13, scope: !294)
!299 = !DILocation(line: 231, column: 7, scope: !300)
!300 = distinct !DILexicalBlock(scope: !294, file: !1, line: 231, column: 7)
!301 = !DILocation(line: 231, column: 11, scope: !300)
!302 = !DILocation(line: 231, column: 17, scope: !300)
!303 = !DILocation(line: 231, column: 7, scope: !294)
!304 = !DILocation(line: 232, column: 4, scope: !300)
!305 = !DILocation(line: 234, column: 3, scope: !294)
!306 = !DILocation(line: 234, column: 7, scope: !294)
!307 = !DILocation(line: 234, column: 12, scope: !294)
!308 = !DILocation(line: 235, column: 3, scope: !294)
!309 = !DILocation(line: 235, column: 7, scope: !294)
!310 = !DILocation(line: 235, column: 11, scope: !294)
!311 = !DILocation(line: 237, column: 3, scope: !294)
!312 = !DILocation(line: 237, column: 7, scope: !294)
!313 = !DILocation(line: 237, column: 14, scope: !294)
!314 = !DILocation(line: 237, column: 21, scope: !294)
!315 = !DILocation(line: 238, column: 2, scope: !294)
!316 = !DILocation(line: 240, column: 2, scope: !231)
!317 = !DILocation(line: 240, column: 6, scope: !231)
!318 = !DILocation(line: 240, column: 13, scope: !231)
!319 = !DILocation(line: 240, column: 22, scope: !231)
!320 = !DILocation(line: 241, column: 2, scope: !231)
!321 = !DILocation(line: 241, column: 6, scope: !231)
!322 = !DILocation(line: 241, column: 13, scope: !231)
!323 = !DILocation(line: 241, column: 29, scope: !231)
!324 = !DILocation(line: 242, column: 37, scope: !231)
!325 = !DILocation(line: 242, column: 46, scope: !231)
!326 = !DILocation(line: 242, column: 58, scope: !231)
!327 = !DILocation(line: 243, column: 4, scope: !231)
!328 = !DILocation(line: 243, column: 7, scope: !329)
!329 = !DILexicalBlockFile(scope: !231, file: !1, discriminator: 1)
!330 = !DILocation(line: 243, column: 16, scope: !329)
!331 = !DILocation(line: 243, column: 33, scope: !329)
!332 = !DILocation(line: 243, column: 4, scope: !329)
!333 = !DILocation(line: 242, column: 2, scope: !329)
!334 = !DILocation(line: 242, column: 6, scope: !329)
!335 = !DILocation(line: 242, column: 13, scope: !329)
!336 = !DILocation(line: 242, column: 35, scope: !329)
!337 = !DILocation(line: 245, column: 35, scope: !231)
!338 = !DILocation(line: 245, column: 39, scope: !231)
!339 = !DILocation(line: 245, column: 46, scope: !231)
!340 = !DILocation(line: 246, column: 4, scope: !231)
!341 = !DILocation(line: 246, column: 15, scope: !231)
!342 = !DILocation(line: 246, column: 24, scope: !231)
!343 = !DILocation(line: 245, column: 9, scope: !231)
!344 = !DILocation(line: 245, column: 2, scope: !231)
!345 = !DILocation(line: 247, column: 1, scope: !231)
!346 = !DILocalVariable(name: "options", arg: 1, scope: !224, file: !1, line: 264, type: !116)
!347 = !DILocation(line: 264, column: 41, scope: !224)
!348 = !DILocation(line: 267, column: 41, scope: !224)
!349 = !DILocation(line: 267, column: 6, scope: !224)
!350 = !DILocation(line: 267, column: 4, scope: !224)
!351 = !DILocation(line: 266, column: 2, scope: !224)
!352 = !DILocalVariable(name: "options", arg: 1, scope: !227, file: !1, line: 272, type: !230)
!353 = !DILocation(line: 272, column: 32, scope: !227)
!354 = !DILocalVariable(name: "allocator", arg: 2, scope: !227, file: !1, line: 272, type: !129)
!355 = !DILocation(line: 272, column: 57, scope: !227)
!356 = !DILocalVariable(name: "props", arg: 3, scope: !227, file: !1, line: 273, type: !108)
!357 = !DILocation(line: 273, column: 18, scope: !227)
!358 = !DILocalVariable(name: "props_size", arg: 4, scope: !227, file: !1, line: 273, type: !99)
!359 = !DILocation(line: 273, column: 32, scope: !227)
!360 = !DILocalVariable(name: "opt", scope: !227, file: !1, line: 275, type: !361)
!361 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !147, size: 64, align: 64)
!362 = !DILocation(line: 275, column: 21, scope: !227)
!363 = !DILocation(line: 277, column: 6, scope: !364)
!364 = distinct !DILexicalBlock(scope: !227, file: !1, line: 277, column: 6)
!365 = !DILocation(line: 277, column: 17, scope: !364)
!366 = !DILocation(line: 277, column: 6, scope: !227)
!367 = !DILocation(line: 278, column: 3, scope: !364)
!368 = !DILocation(line: 281, column: 6, scope: !369)
!369 = distinct !DILexicalBlock(scope: !227, file: !1, line: 281, column: 6)
!370 = !DILocation(line: 281, column: 15, scope: !369)
!371 = !DILocation(line: 281, column: 6, scope: !227)
!372 = !DILocation(line: 282, column: 3, scope: !369)
!373 = !DILocation(line: 285, column: 6, scope: !374)
!374 = distinct !DILexicalBlock(scope: !227, file: !1, line: 285, column: 6)
!375 = !DILocation(line: 285, column: 15, scope: !374)
!376 = !DILocation(line: 285, column: 6, scope: !227)
!377 = !DILocation(line: 286, column: 3, scope: !374)
!378 = !DILocation(line: 288, column: 46, scope: !227)
!379 = !DILocation(line: 288, column: 8, scope: !227)
!380 = !DILocation(line: 288, column: 6, scope: !227)
!381 = !DILocation(line: 289, column: 6, scope: !382)
!382 = distinct !DILexicalBlock(scope: !227, file: !1, line: 289, column: 6)
!383 = !DILocation(line: 289, column: 10, scope: !382)
!384 = !DILocation(line: 289, column: 6, scope: !227)
!385 = !DILocation(line: 290, column: 3, scope: !382)
!386 = !DILocation(line: 292, column: 6, scope: !387)
!387 = distinct !DILexicalBlock(scope: !227, file: !1, line: 292, column: 6)
!388 = !DILocation(line: 292, column: 15, scope: !387)
!389 = !DILocation(line: 292, column: 6, scope: !227)
!390 = !DILocation(line: 293, column: 3, scope: !391)
!391 = distinct !DILexicalBlock(scope: !387, file: !1, line: 292, column: 22)
!392 = !DILocation(line: 293, column: 8, scope: !391)
!393 = !DILocation(line: 293, column: 18, scope: !391)
!394 = !DILocation(line: 294, column: 2, scope: !391)
!395 = !DILocation(line: 295, column: 25, scope: !396)
!396 = distinct !DILexicalBlock(scope: !387, file: !1, line: 294, column: 9)
!397 = !DILocation(line: 295, column: 34, scope: !396)
!398 = !DILocation(line: 295, column: 22, scope: !396)
!399 = !DILocation(line: 295, column: 3, scope: !396)
!400 = !DILocation(line: 295, column: 8, scope: !396)
!401 = !DILocation(line: 295, column: 18, scope: !396)
!402 = !DILocation(line: 296, column: 22, scope: !396)
!403 = !DILocation(line: 296, column: 31, scope: !396)
!404 = !DILocation(line: 296, column: 35, scope: !396)
!405 = !DILocation(line: 296, column: 3, scope: !396)
!406 = !DILocation(line: 296, column: 8, scope: !396)
!407 = !DILocation(line: 296, column: 18, scope: !396)
!408 = !DILocation(line: 299, column: 2, scope: !227)
!409 = !DILocation(line: 299, column: 7, scope: !227)
!410 = !DILocation(line: 299, column: 19, scope: !227)
!411 = !DILocation(line: 300, column: 2, scope: !227)
!412 = !DILocation(line: 300, column: 7, scope: !227)
!413 = !DILocation(line: 300, column: 24, scope: !227)
!414 = !DILocation(line: 302, column: 13, scope: !227)
!415 = !DILocation(line: 302, column: 3, scope: !227)
!416 = !DILocation(line: 302, column: 11, scope: !227)
!417 = !DILocation(line: 304, column: 2, scope: !227)
!418 = !DILocation(line: 305, column: 1, scope: !227)
!419 = !DILocalVariable(name: "coder", arg: 1, scope: !242, file: !1, line: 57, type: !88)
!420 = !DILocation(line: 57, column: 40, scope: !242)
!421 = !DILocalVariable(name: "dict", arg: 2, scope: !242, file: !1, line: 57, type: !89)
!422 = !DILocation(line: 57, column: 72, scope: !242)
!423 = !DILocalVariable(name: "in", arg: 3, scope: !242, file: !1, line: 58, type: !107)
!424 = !DILocation(line: 58, column: 32, scope: !242)
!425 = !DILocalVariable(name: "in_pos", arg: 4, scope: !242, file: !1, line: 58, type: !110)
!426 = !DILocation(line: 58, column: 58, scope: !242)
!427 = !DILocalVariable(name: "in_size", arg: 5, scope: !242, file: !1, line: 59, type: !99)
!428 = !DILocation(line: 59, column: 10, scope: !242)
!429 = !DILocation(line: 64, column: 2, scope: !242)
!430 = !DILocation(line: 64, column: 10, scope: !431)
!431 = !DILexicalBlockFile(scope: !242, file: !1, discriminator: 1)
!432 = !DILocation(line: 64, column: 9, scope: !431)
!433 = !DILocation(line: 64, column: 19, scope: !431)
!434 = !DILocation(line: 64, column: 17, scope: !431)
!435 = !DILocation(line: 64, column: 27, scope: !431)
!436 = !DILocation(line: 64, column: 30, scope: !437)
!437 = !DILexicalBlockFile(scope: !242, file: !1, discriminator: 2)
!438 = !DILocation(line: 64, column: 37, scope: !437)
!439 = !DILocation(line: 64, column: 46, scope: !437)
!440 = !DILocation(line: 64, column: 27, scope: !437)
!441 = !DILocation(line: 64, column: 2, scope: !442)
!442 = !DILexicalBlockFile(scope: !242, file: !1, discriminator: 3)
!443 = !DILocation(line: 65, column: 10, scope: !242)
!444 = !DILocation(line: 65, column: 17, scope: !242)
!445 = !DILocation(line: 65, column: 2, scope: !242)
!446 = !DILocalVariable(name: "control", scope: !447, file: !1, line: 67, type: !449)
!447 = distinct !DILexicalBlock(scope: !448, file: !1, line: 66, column: 20)
!448 = distinct !DILexicalBlock(scope: !242, file: !1, line: 65, column: 27)
!449 = !DIDerivedType(tag: DW_TAG_const_type, baseType: !58)
!450 = !DILocation(line: 67, column: 18, scope: !447)
!451 = !DILocation(line: 67, column: 32, scope: !447)
!452 = !DILocation(line: 67, column: 31, scope: !447)
!453 = !DILocation(line: 67, column: 28, scope: !447)
!454 = !DILocation(line: 68, column: 6, scope: !447)
!455 = !DILocation(line: 68, column: 3, scope: !447)
!456 = !DILocation(line: 71, column: 7, scope: !457)
!457 = distinct !DILexicalBlock(scope: !447, file: !1, line: 71, column: 7)
!458 = !DILocation(line: 71, column: 15, scope: !457)
!459 = !DILocation(line: 71, column: 7, scope: !447)
!460 = !DILocation(line: 72, column: 4, scope: !457)
!461 = !DILocation(line: 74, column: 7, scope: !462)
!462 = distinct !DILexicalBlock(scope: !447, file: !1, line: 74, column: 7)
!463 = !DILocation(line: 74, column: 15, scope: !462)
!464 = !DILocation(line: 74, column: 23, scope: !462)
!465 = !DILocation(line: 74, column: 26, scope: !466)
!466 = !DILexicalBlockFile(scope: !462, file: !1, discriminator: 1)
!467 = !DILocation(line: 74, column: 34, scope: !466)
!468 = !DILocation(line: 74, column: 7, scope: !466)
!469 = !DILocation(line: 77, column: 4, scope: !470)
!470 = distinct !DILexicalBlock(scope: !462, file: !1, line: 74, column: 40)
!471 = !DILocation(line: 77, column: 11, scope: !470)
!472 = !DILocation(line: 77, column: 27, scope: !470)
!473 = !DILocation(line: 78, column: 4, scope: !470)
!474 = !DILocation(line: 78, column: 11, scope: !470)
!475 = !DILocation(line: 78, column: 33, scope: !470)
!476 = !DILocation(line: 79, column: 3, scope: !470)
!477 = !DILocation(line: 79, column: 14, scope: !478)
!478 = !DILexicalBlockFile(scope: !479, file: !1, discriminator: 1)
!479 = distinct !DILexicalBlock(scope: !462, file: !1, line: 79, column: 14)
!480 = !DILocation(line: 79, column: 21, scope: !478)
!481 = !DILocation(line: 80, column: 4, scope: !482)
!482 = distinct !DILexicalBlock(scope: !479, file: !1, line: 79, column: 44)
!483 = !DILocation(line: 83, column: 7, scope: !484)
!484 = distinct !DILexicalBlock(scope: !447, file: !1, line: 83, column: 7)
!485 = !DILocation(line: 83, column: 15, scope: !484)
!486 = !DILocation(line: 83, column: 7, scope: !447)
!487 = !DILocation(line: 86, column: 32, scope: !488)
!488 = distinct !DILexicalBlock(scope: !484, file: !1, line: 83, column: 24)
!489 = !DILocation(line: 86, column: 40, scope: !488)
!490 = !DILocation(line: 86, column: 48, scope: !488)
!491 = !DILocation(line: 86, column: 31, scope: !488)
!492 = !DILocation(line: 86, column: 4, scope: !488)
!493 = !DILocation(line: 86, column: 11, scope: !488)
!494 = !DILocation(line: 86, column: 29, scope: !488)
!495 = !DILocation(line: 87, column: 4, scope: !488)
!496 = !DILocation(line: 87, column: 11, scope: !488)
!497 = !DILocation(line: 87, column: 20, scope: !488)
!498 = !DILocation(line: 91, column: 8, scope: !499)
!499 = distinct !DILexicalBlock(scope: !488, file: !1, line: 91, column: 8)
!500 = !DILocation(line: 91, column: 16, scope: !499)
!501 = !DILocation(line: 91, column: 8, scope: !488)
!502 = !DILocation(line: 94, column: 5, scope: !503)
!503 = distinct !DILexicalBlock(scope: !499, file: !1, line: 91, column: 25)
!504 = !DILocation(line: 94, column: 12, scope: !503)
!505 = !DILocation(line: 94, column: 28, scope: !503)
!506 = !DILocation(line: 95, column: 5, scope: !503)
!507 = !DILocation(line: 95, column: 12, scope: !503)
!508 = !DILocation(line: 95, column: 26, scope: !503)
!509 = !DILocation(line: 97, column: 4, scope: !503)
!510 = !DILocation(line: 97, column: 15, scope: !511)
!511 = !DILexicalBlockFile(scope: !512, file: !1, discriminator: 1)
!512 = distinct !DILexicalBlock(scope: !499, file: !1, line: 97, column: 15)
!513 = !DILocation(line: 97, column: 22, scope: !511)
!514 = !DILocation(line: 98, column: 5, scope: !515)
!515 = distinct !DILexicalBlock(scope: !512, file: !1, line: 97, column: 39)
!516 = !DILocation(line: 101, column: 5, scope: !517)
!517 = distinct !DILexicalBlock(scope: !512, file: !1, line: 100, column: 11)
!518 = !DILocation(line: 101, column: 12, scope: !517)
!519 = !DILocation(line: 101, column: 26, scope: !517)
!520 = !DILocation(line: 106, column: 9, scope: !521)
!521 = distinct !DILexicalBlock(scope: !517, file: !1, line: 106, column: 9)
!522 = !DILocation(line: 106, column: 17, scope: !521)
!523 = !DILocation(line: 106, column: 9, scope: !517)
!524 = !DILocation(line: 107, column: 6, scope: !521)
!525 = !DILocation(line: 107, column: 13, scope: !521)
!526 = !DILocation(line: 107, column: 18, scope: !521)
!527 = !DILocation(line: 107, column: 24, scope: !521)
!528 = !DILocation(line: 107, column: 31, scope: !521)
!529 = !DILocation(line: 107, column: 36, scope: !521)
!530 = !DILocation(line: 108, column: 9, scope: !521)
!531 = !DILocation(line: 108, column: 16, scope: !521)
!532 = !DILocation(line: 108, column: 8, scope: !521)
!533 = !DILocation(line: 110, column: 3, scope: !488)
!534 = !DILocation(line: 112, column: 8, scope: !535)
!535 = distinct !DILexicalBlock(scope: !536, file: !1, line: 112, column: 8)
!536 = distinct !DILexicalBlock(scope: !484, file: !1, line: 110, column: 10)
!537 = !DILocation(line: 112, column: 16, scope: !535)
!538 = !DILocation(line: 112, column: 8, scope: !536)
!539 = !DILocation(line: 113, column: 5, scope: !535)
!540 = !DILocation(line: 116, column: 4, scope: !536)
!541 = !DILocation(line: 116, column: 11, scope: !536)
!542 = !DILocation(line: 116, column: 20, scope: !536)
!543 = !DILocation(line: 117, column: 4, scope: !536)
!544 = !DILocation(line: 117, column: 11, scope: !536)
!545 = !DILocation(line: 117, column: 25, scope: !536)
!546 = !DILocation(line: 120, column: 7, scope: !547)
!547 = distinct !DILexicalBlock(scope: !447, file: !1, line: 120, column: 7)
!548 = !DILocation(line: 120, column: 14, scope: !547)
!549 = !DILocation(line: 120, column: 7, scope: !447)
!550 = !DILocation(line: 123, column: 4, scope: !551)
!551 = distinct !DILexicalBlock(scope: !547, file: !1, line: 120, column: 37)
!552 = !DILocation(line: 123, column: 11, scope: !551)
!553 = !DILocation(line: 123, column: 33, scope: !551)
!554 = !DILocation(line: 124, column: 15, scope: !551)
!555 = !DILocation(line: 124, column: 4, scope: !551)
!556 = !DILocation(line: 125, column: 4, scope: !551)
!557 = !DILocation(line: 128, column: 3, scope: !447)
!558 = !DILocation(line: 132, column: 47, scope: !448)
!559 = !DILocation(line: 132, column: 54, scope: !448)
!560 = !DILocation(line: 132, column: 42, scope: !448)
!561 = !DILocation(line: 132, column: 31, scope: !448)
!562 = !DILocation(line: 132, column: 59, scope: !448)
!563 = !DILocation(line: 132, column: 3, scope: !448)
!564 = !DILocation(line: 132, column: 10, scope: !448)
!565 = !DILocation(line: 132, column: 28, scope: !448)
!566 = !DILocation(line: 133, column: 3, scope: !448)
!567 = !DILocation(line: 133, column: 10, scope: !448)
!568 = !DILocation(line: 133, column: 19, scope: !448)
!569 = !DILocation(line: 134, column: 3, scope: !448)
!570 = !DILocation(line: 137, column: 36, scope: !448)
!571 = !DILocation(line: 137, column: 43, scope: !448)
!572 = !DILocation(line: 137, column: 31, scope: !448)
!573 = !DILocation(line: 137, column: 47, scope: !448)
!574 = !DILocation(line: 137, column: 3, scope: !448)
!575 = !DILocation(line: 137, column: 10, scope: !448)
!576 = !DILocation(line: 137, column: 28, scope: !448)
!577 = !DILocation(line: 138, column: 3, scope: !448)
!578 = !DILocation(line: 138, column: 10, scope: !448)
!579 = !DILocation(line: 138, column: 19, scope: !448)
!580 = !DILocation(line: 139, column: 3, scope: !448)
!581 = !DILocation(line: 139, column: 10, scope: !448)
!582 = !DILocation(line: 139, column: 15, scope: !448)
!583 = !DILocation(line: 139, column: 32, scope: !448)
!584 = !DILocation(line: 139, column: 39, scope: !448)
!585 = !DILocation(line: 139, column: 44, scope: !448)
!586 = !DILocation(line: 140, column: 5, scope: !448)
!587 = !DILocation(line: 140, column: 12, scope: !448)
!588 = !DILocation(line: 141, column: 3, scope: !448)
!589 = !DILocation(line: 144, column: 44, scope: !448)
!590 = !DILocation(line: 144, column: 51, scope: !448)
!591 = !DILocation(line: 144, column: 39, scope: !448)
!592 = !DILocation(line: 144, column: 28, scope: !448)
!593 = !DILocation(line: 144, column: 56, scope: !448)
!594 = !DILocation(line: 144, column: 3, scope: !448)
!595 = !DILocation(line: 144, column: 10, scope: !448)
!596 = !DILocation(line: 144, column: 26, scope: !448)
!597 = !DILocation(line: 145, column: 3, scope: !448)
!598 = !DILocation(line: 145, column: 10, scope: !448)
!599 = !DILocation(line: 145, column: 19, scope: !448)
!600 = !DILocation(line: 146, column: 3, scope: !448)
!601 = !DILocation(line: 149, column: 34, scope: !448)
!602 = !DILocation(line: 149, column: 41, scope: !448)
!603 = !DILocation(line: 149, column: 29, scope: !448)
!604 = !DILocation(line: 149, column: 45, scope: !448)
!605 = !DILocation(line: 149, column: 3, scope: !448)
!606 = !DILocation(line: 149, column: 10, scope: !448)
!607 = !DILocation(line: 149, column: 26, scope: !448)
!608 = !DILocation(line: 150, column: 21, scope: !448)
!609 = !DILocation(line: 150, column: 28, scope: !448)
!610 = !DILocation(line: 150, column: 3, scope: !448)
!611 = !DILocation(line: 150, column: 10, scope: !448)
!612 = !DILocation(line: 150, column: 19, scope: !448)
!613 = !DILocation(line: 151, column: 3, scope: !448)
!614 = !DILocation(line: 154, column: 32, scope: !615)
!615 = distinct !DILexicalBlock(scope: !448, file: !1, line: 154, column: 7)
!616 = !DILocation(line: 154, column: 39, scope: !615)
!617 = !DILocation(line: 154, column: 53, scope: !615)
!618 = !DILocation(line: 154, column: 60, scope: !615)
!619 = !DILocation(line: 154, column: 48, scope: !615)
!620 = !DILocation(line: 154, column: 7, scope: !615)
!621 = !DILocation(line: 154, column: 7, scope: !448)
!622 = !DILocation(line: 155, column: 4, scope: !615)
!623 = !DILocation(line: 157, column: 3, scope: !448)
!624 = !DILocation(line: 157, column: 10, scope: !448)
!625 = !DILocation(line: 157, column: 15, scope: !448)
!626 = !DILocation(line: 157, column: 21, scope: !448)
!627 = !DILocation(line: 157, column: 28, scope: !448)
!628 = !DILocation(line: 157, column: 33, scope: !448)
!629 = !DILocation(line: 157, column: 41, scope: !448)
!630 = !DILocation(line: 157, column: 48, scope: !448)
!631 = !DILocation(line: 157, column: 40, scope: !448)
!632 = !DILocation(line: 159, column: 3, scope: !448)
!633 = !DILocation(line: 159, column: 10, scope: !448)
!634 = !DILocation(line: 159, column: 19, scope: !448)
!635 = !DILocation(line: 160, column: 3, scope: !448)
!636 = !DILocalVariable(name: "in_start", scope: !637, file: !1, line: 165, type: !638)
!637 = distinct !DILexicalBlock(scope: !448, file: !1, line: 162, column: 17)
!638 = !DIDerivedType(tag: DW_TAG_const_type, baseType: !99)
!639 = !DILocation(line: 165, column: 16, scope: !637)
!640 = !DILocation(line: 165, column: 28, scope: !637)
!641 = !DILocation(line: 165, column: 27, scope: !637)
!642 = !DILocalVariable(name: "ret", scope: !637, file: !1, line: 168, type: !643)
!643 = !DIDerivedType(tag: DW_TAG_const_type, baseType: !65)
!644 = !DILocation(line: 168, column: 18, scope: !637)
!645 = !DILocation(line: 168, column: 24, scope: !637)
!646 = !DILocation(line: 168, column: 31, scope: !637)
!647 = !DILocation(line: 168, column: 36, scope: !637)
!648 = !DILocation(line: 168, column: 41, scope: !637)
!649 = !DILocation(line: 168, column: 48, scope: !637)
!650 = !DILocation(line: 168, column: 53, scope: !637)
!651 = !DILocation(line: 169, column: 5, scope: !637)
!652 = !DILocation(line: 169, column: 11, scope: !637)
!653 = !DILocation(line: 169, column: 15, scope: !637)
!654 = !DILocation(line: 169, column: 23, scope: !637)
!655 = !DILocalVariable(name: "in_used", scope: !637, file: !1, line: 172, type: !638)
!656 = !DILocation(line: 172, column: 16, scope: !637)
!657 = !DILocation(line: 172, column: 27, scope: !637)
!658 = !DILocation(line: 172, column: 26, scope: !637)
!659 = !DILocation(line: 172, column: 36, scope: !637)
!660 = !DILocation(line: 172, column: 34, scope: !637)
!661 = !DILocation(line: 173, column: 7, scope: !662)
!662 = distinct !DILexicalBlock(scope: !637, file: !1, line: 173, column: 7)
!663 = !DILocation(line: 173, column: 17, scope: !662)
!664 = !DILocation(line: 173, column: 24, scope: !662)
!665 = !DILocation(line: 173, column: 15, scope: !662)
!666 = !DILocation(line: 173, column: 7, scope: !637)
!667 = !DILocation(line: 174, column: 4, scope: !662)
!668 = !DILocation(line: 176, column: 29, scope: !637)
!669 = !DILocation(line: 176, column: 3, scope: !637)
!670 = !DILocation(line: 176, column: 10, scope: !637)
!671 = !DILocation(line: 176, column: 26, scope: !637)
!672 = !DILocation(line: 179, column: 7, scope: !673)
!673 = distinct !DILexicalBlock(scope: !637, file: !1, line: 179, column: 7)
!674 = !DILocation(line: 179, column: 11, scope: !673)
!675 = !DILocation(line: 179, column: 7, scope: !637)
!676 = !DILocation(line: 180, column: 11, scope: !673)
!677 = !DILocation(line: 180, column: 4, scope: !673)
!678 = !DILocation(line: 185, column: 7, scope: !679)
!679 = distinct !DILexicalBlock(scope: !637, file: !1, line: 185, column: 7)
!680 = !DILocation(line: 185, column: 14, scope: !679)
!681 = !DILocation(line: 185, column: 30, scope: !679)
!682 = !DILocation(line: 185, column: 7, scope: !637)
!683 = !DILocation(line: 186, column: 4, scope: !679)
!684 = !DILocation(line: 188, column: 3, scope: !637)
!685 = !DILocation(line: 188, column: 10, scope: !637)
!686 = !DILocation(line: 188, column: 19, scope: !637)
!687 = !DILocation(line: 189, column: 3, scope: !637)
!688 = !DILocation(line: 194, column: 14, scope: !689)
!689 = distinct !DILexicalBlock(scope: !448, file: !1, line: 192, column: 17)
!690 = !DILocation(line: 194, column: 20, scope: !689)
!691 = !DILocation(line: 194, column: 24, scope: !689)
!692 = !DILocation(line: 194, column: 32, scope: !689)
!693 = !DILocation(line: 194, column: 42, scope: !689)
!694 = !DILocation(line: 194, column: 49, scope: !689)
!695 = !DILocation(line: 194, column: 3, scope: !689)
!696 = !DILocation(line: 195, column: 7, scope: !697)
!697 = distinct !DILexicalBlock(scope: !689, file: !1, line: 195, column: 7)
!698 = !DILocation(line: 195, column: 14, scope: !697)
!699 = !DILocation(line: 195, column: 30, scope: !697)
!700 = !DILocation(line: 195, column: 7, scope: !689)
!701 = !DILocation(line: 196, column: 4, scope: !697)
!702 = !DILocation(line: 198, column: 3, scope: !689)
!703 = !DILocation(line: 198, column: 10, scope: !689)
!704 = !DILocation(line: 198, column: 19, scope: !689)
!705 = !DILocation(line: 199, column: 3, scope: !689)
!706 = !DILocation(line: 203, column: 3, scope: !448)
!707 = !DILocation(line: 64, column: 2, scope: !708)
!708 = !DILexicalBlockFile(scope: !242, file: !1, discriminator: 4)
!709 = !DILocation(line: 207, column: 2, scope: !242)
!710 = !DILocation(line: 208, column: 1, scope: !242)
!711 = !DILocalVariable(name: "coder", arg: 1, scope: !249, file: !1, line: 212, type: !72)
!712 = !DILocation(line: 212, column: 31, scope: !249)
!713 = !DILocalVariable(name: "allocator", arg: 2, scope: !249, file: !1, line: 212, type: !129)
!714 = !DILocation(line: 212, column: 54, scope: !249)
!715 = !DILocation(line: 214, column: 2, scope: !249)
!716 = !DILocation(line: 214, column: 2, scope: !717)
!717 = !DILexicalBlockFile(scope: !249, file: !1, discriminator: 1)
!718 = !DILocation(line: 214, column: 2, scope: !719)
!719 = !DILexicalBlockFile(scope: !249, file: !1, discriminator: 2)
!720 = !DILocation(line: 214, column: 2, scope: !721)
!721 = !DILexicalBlockFile(scope: !249, file: !1, discriminator: 3)
!722 = !DILocation(line: 215, column: 12, scope: !249)
!723 = !DILocation(line: 215, column: 19, scope: !249)
!724 = !DILocation(line: 215, column: 24, scope: !249)
!725 = !DILocation(line: 215, column: 31, scope: !249)
!726 = !DILocation(line: 215, column: 2, scope: !249)
!727 = !DILocation(line: 217, column: 12, scope: !249)
!728 = !DILocation(line: 217, column: 19, scope: !249)
!729 = !DILocation(line: 217, column: 2, scope: !249)
!730 = !DILocation(line: 219, column: 2, scope: !249)
!731 = !DILocalVariable(name: "dict", arg: 1, scope: !243, file: !80, line: 230, type: !90)
!732 = !DILocation(line: 230, column: 23, scope: !243)
!733 = !DILocation(line: 232, column: 2, scope: !243)
!734 = !DILocation(line: 232, column: 8, scope: !243)
!735 = !DILocation(line: 232, column: 19, scope: !243)
!736 = !DILocation(line: 233, column: 2, scope: !243)
!737 = !DILocalVariable(name: "dict", arg: 1, scope: !246, file: !80, line: 205, type: !89)
!738 = !DILocation(line: 205, column: 37, scope: !246)
!739 = !DILocalVariable(name: "in", arg: 2, scope: !246, file: !80, line: 205, type: !107)
!740 = !DILocation(line: 205, column: 72, scope: !246)
!741 = !DILocalVariable(name: "in_pos", arg: 3, scope: !246, file: !80, line: 206, type: !110)
!742 = !DILocation(line: 206, column: 25, scope: !246)
!743 = !DILocalVariable(name: "in_size", arg: 4, scope: !246, file: !80, line: 206, type: !99)
!744 = !DILocation(line: 206, column: 40, scope: !246)
!745 = !DILocalVariable(name: "left", arg: 5, scope: !246, file: !80, line: 207, type: !110)
!746 = !DILocation(line: 207, column: 25, scope: !246)
!747 = !DILocation(line: 216, column: 6, scope: !748)
!748 = distinct !DILexicalBlock(scope: !246, file: !80, line: 216, column: 6)
!749 = !DILocation(line: 216, column: 17, scope: !748)
!750 = !DILocation(line: 216, column: 16, scope: !748)
!751 = !DILocation(line: 216, column: 14, scope: !748)
!752 = !DILocation(line: 216, column: 27, scope: !748)
!753 = !DILocation(line: 216, column: 26, scope: !748)
!754 = !DILocation(line: 216, column: 24, scope: !748)
!755 = !DILocation(line: 216, column: 6, scope: !246)
!756 = !DILocation(line: 217, column: 14, scope: !748)
!757 = !DILocation(line: 217, column: 13, scope: !748)
!758 = !DILocation(line: 217, column: 24, scope: !748)
!759 = !DILocation(line: 217, column: 23, scope: !748)
!760 = !DILocation(line: 217, column: 21, scope: !748)
!761 = !DILocation(line: 217, column: 11, scope: !748)
!762 = !DILocation(line: 217, column: 3, scope: !748)
!763 = !DILocation(line: 219, column: 23, scope: !246)
!764 = !DILocation(line: 219, column: 27, scope: !246)
!765 = !DILocation(line: 219, column: 35, scope: !246)
!766 = !DILocation(line: 220, column: 4, scope: !246)
!767 = !DILocation(line: 220, column: 10, scope: !246)
!768 = !DILocation(line: 220, column: 16, scope: !246)
!769 = !DILocation(line: 220, column: 22, scope: !246)
!770 = !DILocation(line: 220, column: 27, scope: !246)
!771 = !DILocation(line: 220, column: 33, scope: !246)
!772 = !DILocation(line: 219, column: 11, scope: !246)
!773 = !DILocation(line: 219, column: 3, scope: !246)
!774 = !DILocation(line: 219, column: 8, scope: !246)
!775 = !DILocation(line: 222, column: 6, scope: !776)
!776 = distinct !DILexicalBlock(scope: !246, file: !80, line: 222, column: 6)
!777 = !DILocation(line: 222, column: 12, scope: !776)
!778 = !DILocation(line: 222, column: 18, scope: !776)
!779 = !DILocation(line: 222, column: 24, scope: !776)
!780 = !DILocation(line: 222, column: 16, scope: !776)
!781 = !DILocation(line: 222, column: 6, scope: !246)
!782 = !DILocation(line: 223, column: 16, scope: !776)
!783 = !DILocation(line: 223, column: 22, scope: !776)
!784 = !DILocation(line: 223, column: 3, scope: !776)
!785 = !DILocation(line: 223, column: 9, scope: !776)
!786 = !DILocation(line: 223, column: 14, scope: !776)
!787 = !DILocation(line: 225, column: 2, scope: !246)
