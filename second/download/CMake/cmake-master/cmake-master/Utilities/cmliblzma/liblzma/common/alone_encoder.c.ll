; ModuleID = '/data/download/cmake/cmake-master/Utilities/cmliblzma/liblzma/common/alone_encoder.c'
target datalayout = "e-m:e-i64:64-f80:128-n8:16:32:64-S128"
target triple = "x86_64-unknown-linux-gnu"

%struct.lzma_next_coder_s = type { %struct.lzma_coder_s*, i64, i64, i32 (%struct.lzma_coder_s*, %struct.lzma_allocator*, i8*, i64*, i64, i8*, i64*, i64, i32)*, void (%struct.lzma_coder_s*, %struct.lzma_allocator*)*, i32 (%struct.lzma_coder_s*)*, i32 (%struct.lzma_coder_s*, i64*, i64*, i64)*, i32 (%struct.lzma_coder_s*, %struct.lzma_allocator*, %struct.lzma_filter*, %struct.lzma_filter*)* }
%struct.lzma_coder_s = type { %struct.lzma_next_coder_s, i32, i64, [13 x i8] }
%struct.lzma_allocator = type { i8* (i8*, i64, i64)*, void (i8*, i8*)*, i8* }
%struct.lzma_filter = type { i64, i8* }
%struct.lzma_stream = type { i8*, i64, i64, i8*, i64, i64, %struct.lzma_allocator*, %struct.lzma_internal_s*, i8*, i8*, i8*, i8*, i64, i64, i64, i64, i32, i32 }
%struct.lzma_internal_s = type { %struct.lzma_next_coder_s, i32, i64, [4 x i8], i8 }
%struct.lzma_options_lzma = type { i32, i8*, i32, i32, i32, i32, i32, i32, i32, i32, i32, i32, i32, i32, i32, i32, i32, i32, i32, i32, i32, i32, i8*, i8* }
%struct.lzma_filter_info_s = type { i64, i32 (%struct.lzma_next_coder_s*, %struct.lzma_allocator*, %struct.lzma_filter_info_s*)*, i8* }

@LZMA_NEXT_CODER_INIT = internal constant %struct.lzma_next_coder_s { %struct.lzma_coder_s* null, i64 -1, i64 0, i32 (%struct.lzma_coder_s*, %struct.lzma_allocator*, i8*, i64*, i64, i8*, i64*, i64, i32)* null, void (%struct.lzma_coder_s*, %struct.lzma_allocator*)* null, i32 (%struct.lzma_coder_s*)* null, i32 (%struct.lzma_coder_s*, i64*, i64*, i64)* null, i32 (%struct.lzma_coder_s*, %struct.lzma_allocator*, %struct.lzma_filter*, %struct.lzma_filter*)* null }, align 8
@.str = private unnamed_addr constant [2 x i8] c"0\00", align 1
@.str.1 = private unnamed_addr constant [85 x i8] c"/data/download/cmake/cmake-master/Utilities/cmliblzma/liblzma/common/alone_encoder.c\00", align 1
@__PRETTY_FUNCTION__.alone_encode = private unnamed_addr constant [163 x i8] c"lzma_ret alone_encode(lzma_coder *, lzma_allocator *, const uint8_t *restrict, size_t *restrict, size_t, uint8_t *restrict, size_t *restrict, size_t, lzma_action)\00", align 1

; Function Attrs: nounwind uwtable
define i32 @lzma_alone_encoder(%struct.lzma_stream* %strm, %struct.lzma_options_lzma* %options) #0 !dbg !159 {
entry:
  %retval = alloca i32, align 4
  %strm.addr = alloca %struct.lzma_stream*, align 8
  %options.addr = alloca %struct.lzma_options_lzma*, align 8
  %ret_ = alloca i32, align 4
  %ret_2 = alloca i32, align 4
  store %struct.lzma_stream* %strm, %struct.lzma_stream** %strm.addr, align 8
  call void @llvm.dbg.declare(metadata %struct.lzma_stream** %strm.addr, metadata !235, metadata !236), !dbg !237
  store %struct.lzma_options_lzma* %options, %struct.lzma_options_lzma** %options.addr, align 8
  call void @llvm.dbg.declare(metadata %struct.lzma_options_lzma** %options.addr, metadata !238, metadata !236), !dbg !239
  br label %do.body, !dbg !240

do.body:                                          ; preds = %entry
  call void @llvm.dbg.declare(metadata i32* %ret_, metadata !241, metadata !236), !dbg !243
  br label %do.body1, !dbg !244

do.body1:                                         ; preds = %do.body
  call void @llvm.dbg.declare(metadata i32* %ret_2, metadata !246, metadata !236), !dbg !249
  %0 = load %struct.lzma_stream*, %struct.lzma_stream** %strm.addr, align 8, !dbg !250
  %call = call i32 @lzma_strm_init(%struct.lzma_stream* %0), !dbg !250
  store i32 %call, i32* %ret_2, align 4, !dbg !250
  %1 = load i32, i32* %ret_2, align 4, !dbg !250
  %cmp = icmp ne i32 %1, 0, !dbg !250
  br i1 %cmp, label %if.then, label %if.end, !dbg !250

if.then:                                          ; preds = %do.body1
  %2 = load i32, i32* %ret_2, align 4, !dbg !252
  store i32 %2, i32* %retval, align 4, !dbg !252
  br label %return, !dbg !252

if.end:                                           ; preds = %do.body1
  br label %do.end, !dbg !255

do.end:                                           ; preds = %if.end
  %3 = load %struct.lzma_stream*, %struct.lzma_stream** %strm.addr, align 8, !dbg !257
  %internal = getelementptr inbounds %struct.lzma_stream, %struct.lzma_stream* %3, i32 0, i32 7, !dbg !257
  %4 = load %struct.lzma_internal_s*, %struct.lzma_internal_s** %internal, align 8, !dbg !257
  %next = getelementptr inbounds %struct.lzma_internal_s, %struct.lzma_internal_s* %4, i32 0, i32 0, !dbg !257
  %5 = load %struct.lzma_stream*, %struct.lzma_stream** %strm.addr, align 8, !dbg !257
  %allocator = getelementptr inbounds %struct.lzma_stream, %struct.lzma_stream* %5, i32 0, i32 6, !dbg !257
  %6 = load %struct.lzma_allocator*, %struct.lzma_allocator** %allocator, align 8, !dbg !257
  %7 = load %struct.lzma_options_lzma*, %struct.lzma_options_lzma** %options.addr, align 8, !dbg !257
  %call3 = call i32 @alone_encoder_init(%struct.lzma_next_coder_s* %next, %struct.lzma_allocator* %6, %struct.lzma_options_lzma* %7), !dbg !257
  store i32 %call3, i32* %ret_, align 4, !dbg !257
  %8 = load i32, i32* %ret_, align 4, !dbg !257
  %cmp4 = icmp ne i32 %8, 0, !dbg !257
  br i1 %cmp4, label %if.then5, label %if.end6, !dbg !257

if.then5:                                         ; preds = %do.end
  %9 = load %struct.lzma_stream*, %struct.lzma_stream** %strm.addr, align 8, !dbg !259
  call void @lzma_end(%struct.lzma_stream* %9) #7, !dbg !259
  %10 = load i32, i32* %ret_, align 4, !dbg !259
  store i32 %10, i32* %retval, align 4, !dbg !259
  br label %return, !dbg !259

if.end6:                                          ; preds = %do.end
  br label %do.end7, !dbg !263

do.end7:                                          ; preds = %if.end6
  %11 = load %struct.lzma_stream*, %struct.lzma_stream** %strm.addr, align 8, !dbg !265
  %internal8 = getelementptr inbounds %struct.lzma_stream, %struct.lzma_stream* %11, i32 0, i32 7, !dbg !266
  %12 = load %struct.lzma_internal_s*, %struct.lzma_internal_s** %internal8, align 8, !dbg !266
  %supported_actions = getelementptr inbounds %struct.lzma_internal_s, %struct.lzma_internal_s* %12, i32 0, i32 3, !dbg !267
  %arrayidx = getelementptr inbounds [4 x i8], [4 x i8]* %supported_actions, i64 0, i64 0, !dbg !265
  store i8 1, i8* %arrayidx, align 8, !dbg !268
  %13 = load %struct.lzma_stream*, %struct.lzma_stream** %strm.addr, align 8, !dbg !269
  %internal9 = getelementptr inbounds %struct.lzma_stream, %struct.lzma_stream* %13, i32 0, i32 7, !dbg !270
  %14 = load %struct.lzma_internal_s*, %struct.lzma_internal_s** %internal9, align 8, !dbg !270
  %supported_actions10 = getelementptr inbounds %struct.lzma_internal_s, %struct.lzma_internal_s* %14, i32 0, i32 3, !dbg !271
  %arrayidx11 = getelementptr inbounds [4 x i8], [4 x i8]* %supported_actions10, i64 0, i64 3, !dbg !269
  store i8 1, i8* %arrayidx11, align 1, !dbg !272
  store i32 0, i32* %retval, align 4, !dbg !273
  br label %return, !dbg !273

return:                                           ; preds = %do.end7, %if.then5, %if.then
  %15 = load i32, i32* %retval, align 4, !dbg !274
  ret i32 %15, !dbg !274
}

; Function Attrs: nounwind readnone
declare void @llvm.dbg.declare(metadata, metadata, metadata) #1

declare i32 @lzma_strm_init(%struct.lzma_stream*) #2

; Function Attrs: nounwind uwtable
define internal i32 @alone_encoder_init(%struct.lzma_next_coder_s* %next, %struct.lzma_allocator* %allocator, %struct.lzma_options_lzma* %options) #0 !dbg !219 {
entry:
  %retval = alloca i32, align 4
  %next.addr = alloca %struct.lzma_next_coder_s*, align 8
  %allocator.addr = alloca %struct.lzma_allocator*, align 8
  %options.addr = alloca %struct.lzma_options_lzma*, align 8
  %d = alloca i32, align 4
  %filters = alloca [2 x %struct.lzma_filter_info_s], align 16
  store %struct.lzma_next_coder_s* %next, %struct.lzma_next_coder_s** %next.addr, align 8
  call void @llvm.dbg.declare(metadata %struct.lzma_next_coder_s** %next.addr, metadata !275, metadata !236), !dbg !276
  store %struct.lzma_allocator* %allocator, %struct.lzma_allocator** %allocator.addr, align 8
  call void @llvm.dbg.declare(metadata %struct.lzma_allocator** %allocator.addr, metadata !277, metadata !236), !dbg !278
  store %struct.lzma_options_lzma* %options, %struct.lzma_options_lzma** %options.addr, align 8
  call void @llvm.dbg.declare(metadata %struct.lzma_options_lzma** %options.addr, metadata !279, metadata !236), !dbg !280
  call void @llvm.dbg.declare(metadata i32* %d, metadata !281, metadata !236), !dbg !282
  call void @llvm.dbg.declare(metadata [2 x %struct.lzma_filter_info_s]* %filters, metadata !283, metadata !236), !dbg !299
  %arrayinit.begin = getelementptr inbounds [2 x %struct.lzma_filter_info_s], [2 x %struct.lzma_filter_info_s]* %filters, i64 0, i64 0, !dbg !300
  %id = getelementptr inbounds %struct.lzma_filter_info_s, %struct.lzma_filter_info_s* %arrayinit.begin, i32 0, i32 0, !dbg !301
  store i64 0, i64* %id, align 8, !dbg !301
  %init = getelementptr inbounds %struct.lzma_filter_info_s, %struct.lzma_filter_info_s* %arrayinit.begin, i32 0, i32 1, !dbg !301
  store i32 (%struct.lzma_next_coder_s*, %struct.lzma_allocator*, %struct.lzma_filter_info_s*)* @lzma_lzma_encoder_init, i32 (%struct.lzma_next_coder_s*, %struct.lzma_allocator*, %struct.lzma_filter_info_s*)** %init, align 8, !dbg !301
  %options1 = getelementptr inbounds %struct.lzma_filter_info_s, %struct.lzma_filter_info_s* %arrayinit.begin, i32 0, i32 2, !dbg !301
  %0 = load %struct.lzma_options_lzma*, %struct.lzma_options_lzma** %options.addr, align 8, !dbg !302
  %1 = bitcast %struct.lzma_options_lzma* %0 to i8*, !dbg !303
  store i8* %1, i8** %options1, align 8, !dbg !301
  %arrayinit.element = getelementptr inbounds %struct.lzma_filter_info_s, %struct.lzma_filter_info_s* %arrayinit.begin, i64 1, !dbg !300
  %id2 = getelementptr inbounds %struct.lzma_filter_info_s, %struct.lzma_filter_info_s* %arrayinit.element, i32 0, i32 0, !dbg !304
  store i64 0, i64* %id2, align 8, !dbg !304
  %init3 = getelementptr inbounds %struct.lzma_filter_info_s, %struct.lzma_filter_info_s* %arrayinit.element, i32 0, i32 1, !dbg !304
  store i32 (%struct.lzma_next_coder_s*, %struct.lzma_allocator*, %struct.lzma_filter_info_s*)* null, i32 (%struct.lzma_next_coder_s*, %struct.lzma_allocator*, %struct.lzma_filter_info_s*)** %init3, align 8, !dbg !304
  %options4 = getelementptr inbounds %struct.lzma_filter_info_s, %struct.lzma_filter_info_s* %arrayinit.element, i32 0, i32 2, !dbg !304
  store i8* null, i8** %options4, align 8, !dbg !304
  br label %do.body, !dbg !305

do.body:                                          ; preds = %entry
  %2 = load %struct.lzma_next_coder_s*, %struct.lzma_next_coder_s** %next.addr, align 8, !dbg !306
  %init5 = getelementptr inbounds %struct.lzma_next_coder_s, %struct.lzma_next_coder_s* %2, i32 0, i32 2, !dbg !306
  %3 = load i64, i64* %init5, align 8, !dbg !306
  %cmp = icmp ne i64 ptrtoint (i32 (%struct.lzma_next_coder_s*, %struct.lzma_allocator*, %struct.lzma_options_lzma*)* @alone_encoder_init to i64), %3, !dbg !306
  br i1 %cmp, label %if.then, label %if.end, !dbg !306

if.then:                                          ; preds = %do.body
  %4 = load %struct.lzma_next_coder_s*, %struct.lzma_next_coder_s** %next.addr, align 8, !dbg !310
  %5 = load %struct.lzma_allocator*, %struct.lzma_allocator** %allocator.addr, align 8, !dbg !310
  call void @lzma_next_end(%struct.lzma_next_coder_s* %4, %struct.lzma_allocator* %5), !dbg !310
  br label %if.end, !dbg !310

if.end:                                           ; preds = %if.then, %do.body
  %6 = load %struct.lzma_next_coder_s*, %struct.lzma_next_coder_s** %next.addr, align 8, !dbg !312
  %init6 = getelementptr inbounds %struct.lzma_next_coder_s, %struct.lzma_next_coder_s* %6, i32 0, i32 2, !dbg !312
  store i64 ptrtoint (i32 (%struct.lzma_next_coder_s*, %struct.lzma_allocator*, %struct.lzma_options_lzma*)* @alone_encoder_init to i64), i64* %init6, align 8, !dbg !312
  br label %do.end, !dbg !312

do.end:                                           ; preds = %if.end
  %7 = load %struct.lzma_next_coder_s*, %struct.lzma_next_coder_s** %next.addr, align 8, !dbg !314
  %coder = getelementptr inbounds %struct.lzma_next_coder_s, %struct.lzma_next_coder_s* %7, i32 0, i32 0, !dbg !316
  %8 = load %struct.lzma_coder_s*, %struct.lzma_coder_s** %coder, align 8, !dbg !316
  %cmp7 = icmp eq %struct.lzma_coder_s* %8, null, !dbg !317
  br i1 %cmp7, label %if.then8, label %if.end16, !dbg !318

if.then8:                                         ; preds = %do.end
  %9 = load %struct.lzma_allocator*, %struct.lzma_allocator** %allocator.addr, align 8, !dbg !319
  %call = call noalias i8* @lzma_alloc(i64 96, %struct.lzma_allocator* %9), !dbg !321
  %10 = bitcast i8* %call to %struct.lzma_coder_s*, !dbg !321
  %11 = load %struct.lzma_next_coder_s*, %struct.lzma_next_coder_s** %next.addr, align 8, !dbg !322
  %coder9 = getelementptr inbounds %struct.lzma_next_coder_s, %struct.lzma_next_coder_s* %11, i32 0, i32 0, !dbg !323
  store %struct.lzma_coder_s* %10, %struct.lzma_coder_s** %coder9, align 8, !dbg !324
  %12 = load %struct.lzma_next_coder_s*, %struct.lzma_next_coder_s** %next.addr, align 8, !dbg !325
  %coder10 = getelementptr inbounds %struct.lzma_next_coder_s, %struct.lzma_next_coder_s* %12, i32 0, i32 0, !dbg !327
  %13 = load %struct.lzma_coder_s*, %struct.lzma_coder_s** %coder10, align 8, !dbg !327
  %cmp11 = icmp eq %struct.lzma_coder_s* %13, null, !dbg !328
  br i1 %cmp11, label %if.then12, label %if.end13, !dbg !329

if.then12:                                        ; preds = %if.then8
  store i32 5, i32* %retval, align 4, !dbg !330
  br label %return, !dbg !330

if.end13:                                         ; preds = %if.then8
  %14 = load %struct.lzma_next_coder_s*, %struct.lzma_next_coder_s** %next.addr, align 8, !dbg !331
  %code = getelementptr inbounds %struct.lzma_next_coder_s, %struct.lzma_next_coder_s* %14, i32 0, i32 3, !dbg !332
  store i32 (%struct.lzma_coder_s*, %struct.lzma_allocator*, i8*, i64*, i64, i8*, i64*, i64, i32)* @alone_encode, i32 (%struct.lzma_coder_s*, %struct.lzma_allocator*, i8*, i64*, i64, i8*, i64*, i64, i32)** %code, align 8, !dbg !333
  %15 = load %struct.lzma_next_coder_s*, %struct.lzma_next_coder_s** %next.addr, align 8, !dbg !334
  %end = getelementptr inbounds %struct.lzma_next_coder_s, %struct.lzma_next_coder_s* %15, i32 0, i32 4, !dbg !335
  store void (%struct.lzma_coder_s*, %struct.lzma_allocator*)* @alone_encoder_end, void (%struct.lzma_coder_s*, %struct.lzma_allocator*)** %end, align 8, !dbg !336
  %16 = load %struct.lzma_next_coder_s*, %struct.lzma_next_coder_s** %next.addr, align 8, !dbg !337
  %coder14 = getelementptr inbounds %struct.lzma_next_coder_s, %struct.lzma_next_coder_s* %16, i32 0, i32 0, !dbg !338
  %17 = load %struct.lzma_coder_s*, %struct.lzma_coder_s** %coder14, align 8, !dbg !338
  %next15 = getelementptr inbounds %struct.lzma_coder_s, %struct.lzma_coder_s* %17, i32 0, i32 0, !dbg !339
  %18 = bitcast %struct.lzma_next_coder_s* %next15 to i8*, !dbg !340
  call void @llvm.memcpy.p0i8.p0i8.i64(i8* %18, i8* bitcast (%struct.lzma_next_coder_s* @LZMA_NEXT_CODER_INIT to i8*), i64 64, i32 8, i1 false), !dbg !340
  br label %if.end16, !dbg !341

if.end16:                                         ; preds = %if.end13, %do.end
  %19 = load %struct.lzma_next_coder_s*, %struct.lzma_next_coder_s** %next.addr, align 8, !dbg !342
  %coder17 = getelementptr inbounds %struct.lzma_next_coder_s, %struct.lzma_next_coder_s* %19, i32 0, i32 0, !dbg !343
  %20 = load %struct.lzma_coder_s*, %struct.lzma_coder_s** %coder17, align 8, !dbg !343
  %sequence = getelementptr inbounds %struct.lzma_coder_s, %struct.lzma_coder_s* %20, i32 0, i32 1, !dbg !344
  store i32 0, i32* %sequence, align 8, !dbg !345
  %21 = load %struct.lzma_next_coder_s*, %struct.lzma_next_coder_s** %next.addr, align 8, !dbg !346
  %coder18 = getelementptr inbounds %struct.lzma_next_coder_s, %struct.lzma_next_coder_s* %21, i32 0, i32 0, !dbg !347
  %22 = load %struct.lzma_coder_s*, %struct.lzma_coder_s** %coder18, align 8, !dbg !347
  %header_pos = getelementptr inbounds %struct.lzma_coder_s, %struct.lzma_coder_s* %22, i32 0, i32 2, !dbg !348
  store i64 0, i64* %header_pos, align 8, !dbg !349
  %23 = load %struct.lzma_options_lzma*, %struct.lzma_options_lzma** %options.addr, align 8, !dbg !350
  %24 = load %struct.lzma_next_coder_s*, %struct.lzma_next_coder_s** %next.addr, align 8, !dbg !352
  %coder19 = getelementptr inbounds %struct.lzma_next_coder_s, %struct.lzma_next_coder_s* %24, i32 0, i32 0, !dbg !353
  %25 = load %struct.lzma_coder_s*, %struct.lzma_coder_s** %coder19, align 8, !dbg !353
  %header = getelementptr inbounds %struct.lzma_coder_s, %struct.lzma_coder_s* %25, i32 0, i32 3, !dbg !354
  %arraydecay = getelementptr inbounds [13 x i8], [13 x i8]* %header, i32 0, i32 0, !dbg !352
  %call20 = call zeroext i1 @lzma_lzma_lclppb_encode(%struct.lzma_options_lzma* %23, i8* %arraydecay), !dbg !355
  br i1 %call20, label %if.then21, label %if.end22, !dbg !356

if.then21:                                        ; preds = %if.end16
  store i32 8, i32* %retval, align 4, !dbg !357
  br label %return, !dbg !357

if.end22:                                         ; preds = %if.end16
  %26 = load %struct.lzma_options_lzma*, %struct.lzma_options_lzma** %options.addr, align 8, !dbg !358
  %dict_size = getelementptr inbounds %struct.lzma_options_lzma, %struct.lzma_options_lzma* %26, i32 0, i32 0, !dbg !360
  %27 = load i32, i32* %dict_size, align 8, !dbg !360
  %cmp23 = icmp ult i32 %27, 4096, !dbg !361
  br i1 %cmp23, label %if.then24, label %if.end25, !dbg !362

if.then24:                                        ; preds = %if.end22
  store i32 8, i32* %retval, align 4, !dbg !363
  br label %return, !dbg !363

if.end25:                                         ; preds = %if.end22
  %28 = load %struct.lzma_options_lzma*, %struct.lzma_options_lzma** %options.addr, align 8, !dbg !364
  %dict_size26 = getelementptr inbounds %struct.lzma_options_lzma, %struct.lzma_options_lzma* %28, i32 0, i32 0, !dbg !365
  %29 = load i32, i32* %dict_size26, align 8, !dbg !365
  %sub = sub i32 %29, 1, !dbg !366
  store i32 %sub, i32* %d, align 4, !dbg !367
  %30 = load i32, i32* %d, align 4, !dbg !368
  %shr = lshr i32 %30, 2, !dbg !369
  %31 = load i32, i32* %d, align 4, !dbg !370
  %or = or i32 %31, %shr, !dbg !370
  store i32 %or, i32* %d, align 4, !dbg !370
  %32 = load i32, i32* %d, align 4, !dbg !371
  %shr27 = lshr i32 %32, 3, !dbg !372
  %33 = load i32, i32* %d, align 4, !dbg !373
  %or28 = or i32 %33, %shr27, !dbg !373
  store i32 %or28, i32* %d, align 4, !dbg !373
  %34 = load i32, i32* %d, align 4, !dbg !374
  %shr29 = lshr i32 %34, 4, !dbg !375
  %35 = load i32, i32* %d, align 4, !dbg !376
  %or30 = or i32 %35, %shr29, !dbg !376
  store i32 %or30, i32* %d, align 4, !dbg !376
  %36 = load i32, i32* %d, align 4, !dbg !377
  %shr31 = lshr i32 %36, 8, !dbg !378
  %37 = load i32, i32* %d, align 4, !dbg !379
  %or32 = or i32 %37, %shr31, !dbg !379
  store i32 %or32, i32* %d, align 4, !dbg !379
  %38 = load i32, i32* %d, align 4, !dbg !380
  %shr33 = lshr i32 %38, 16, !dbg !381
  %39 = load i32, i32* %d, align 4, !dbg !382
  %or34 = or i32 %39, %shr33, !dbg !382
  store i32 %or34, i32* %d, align 4, !dbg !382
  %40 = load i32, i32* %d, align 4, !dbg !383
  %cmp35 = icmp ne i32 %40, -1, !dbg !385
  br i1 %cmp35, label %if.then36, label %if.end37, !dbg !386

if.then36:                                        ; preds = %if.end25
  %41 = load i32, i32* %d, align 4, !dbg !387
  %inc = add i32 %41, 1, !dbg !387
  store i32 %inc, i32* %d, align 4, !dbg !387
  br label %if.end37, !dbg !387

if.end37:                                         ; preds = %if.then36, %if.end25
  %42 = load %struct.lzma_next_coder_s*, %struct.lzma_next_coder_s** %next.addr, align 8, !dbg !388
  %coder38 = getelementptr inbounds %struct.lzma_next_coder_s, %struct.lzma_next_coder_s* %42, i32 0, i32 0, !dbg !388
  %43 = load %struct.lzma_coder_s*, %struct.lzma_coder_s** %coder38, align 8, !dbg !388
  %header39 = getelementptr inbounds %struct.lzma_coder_s, %struct.lzma_coder_s* %43, i32 0, i32 3, !dbg !388
  %arraydecay40 = getelementptr inbounds [13 x i8], [13 x i8]* %header39, i32 0, i32 0, !dbg !388
  %add.ptr = getelementptr inbounds i8, i8* %arraydecay40, i64 1, !dbg !388
  %44 = load i32, i32* %d, align 4, !dbg !388
  call void @write32ne(i8* %add.ptr, i32 %44), !dbg !388
  %45 = load %struct.lzma_next_coder_s*, %struct.lzma_next_coder_s** %next.addr, align 8, !dbg !389
  %coder41 = getelementptr inbounds %struct.lzma_next_coder_s, %struct.lzma_next_coder_s* %45, i32 0, i32 0, !dbg !390
  %46 = load %struct.lzma_coder_s*, %struct.lzma_coder_s** %coder41, align 8, !dbg !390
  %header42 = getelementptr inbounds %struct.lzma_coder_s, %struct.lzma_coder_s* %46, i32 0, i32 3, !dbg !391
  %arraydecay43 = getelementptr inbounds [13 x i8], [13 x i8]* %header42, i32 0, i32 0, !dbg !389
  %add.ptr44 = getelementptr inbounds i8, i8* %arraydecay43, i64 1, !dbg !392
  %add.ptr45 = getelementptr inbounds i8, i8* %add.ptr44, i64 4, !dbg !393
  call void @llvm.memset.p0i8.i64(i8* %add.ptr45, i8 -1, i64 8, i32 1, i1 false), !dbg !394
  %47 = load %struct.lzma_next_coder_s*, %struct.lzma_next_coder_s** %next.addr, align 8, !dbg !395
  %coder46 = getelementptr inbounds %struct.lzma_next_coder_s, %struct.lzma_next_coder_s* %47, i32 0, i32 0, !dbg !396
  %48 = load %struct.lzma_coder_s*, %struct.lzma_coder_s** %coder46, align 8, !dbg !396
  %next47 = getelementptr inbounds %struct.lzma_coder_s, %struct.lzma_coder_s* %48, i32 0, i32 0, !dbg !397
  %49 = load %struct.lzma_allocator*, %struct.lzma_allocator** %allocator.addr, align 8, !dbg !398
  %arraydecay48 = getelementptr inbounds [2 x %struct.lzma_filter_info_s], [2 x %struct.lzma_filter_info_s]* %filters, i32 0, i32 0, !dbg !399
  %call49 = call i32 @lzma_next_filter_init(%struct.lzma_next_coder_s* %next47, %struct.lzma_allocator* %49, %struct.lzma_filter_info_s* %arraydecay48), !dbg !400
  store i32 %call49, i32* %retval, align 4, !dbg !401
  br label %return, !dbg !401

return:                                           ; preds = %if.end37, %if.then24, %if.then21, %if.then12
  %50 = load i32, i32* %retval, align 4, !dbg !402
  ret i32 %50, !dbg !402
}

; Function Attrs: nounwind
declare void @lzma_end(%struct.lzma_stream*) #3

declare i32 @lzma_lzma_encoder_init(%struct.lzma_next_coder_s*, %struct.lzma_allocator*, %struct.lzma_filter_info_s*) #2

declare void @lzma_next_end(%struct.lzma_next_coder_s*, %struct.lzma_allocator*) #2

declare noalias i8* @lzma_alloc(i64, %struct.lzma_allocator*) #2

; Function Attrs: nounwind uwtable
define internal i32 @alone_encode(%struct.lzma_coder_s* %coder, %struct.lzma_allocator* %allocator, i8* noalias %in, i64* noalias %in_pos, i64 %in_size, i8* noalias %out, i64* noalias %out_pos, i64 %out_size, i32 %action) #0 !dbg !223 {
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
  store %struct.lzma_coder_s* %coder, %struct.lzma_coder_s** %coder.addr, align 8
  call void @llvm.dbg.declare(metadata %struct.lzma_coder_s** %coder.addr, metadata !403, metadata !236), !dbg !404
  store %struct.lzma_allocator* %allocator, %struct.lzma_allocator** %allocator.addr, align 8
  call void @llvm.dbg.declare(metadata %struct.lzma_allocator** %allocator.addr, metadata !405, metadata !236), !dbg !406
  store i8* %in, i8** %in.addr, align 8
  call void @llvm.dbg.declare(metadata i8** %in.addr, metadata !407, metadata !236), !dbg !408
  store i64* %in_pos, i64** %in_pos.addr, align 8
  call void @llvm.dbg.declare(metadata i64** %in_pos.addr, metadata !409, metadata !236), !dbg !410
  store i64 %in_size, i64* %in_size.addr, align 8
  call void @llvm.dbg.declare(metadata i64* %in_size.addr, metadata !411, metadata !236), !dbg !412
  store i8* %out, i8** %out.addr, align 8
  call void @llvm.dbg.declare(metadata i8** %out.addr, metadata !413, metadata !236), !dbg !414
  store i64* %out_pos, i64** %out_pos.addr, align 8
  call void @llvm.dbg.declare(metadata i64** %out_pos.addr, metadata !415, metadata !236), !dbg !416
  store i64 %out_size, i64* %out_size.addr, align 8
  call void @llvm.dbg.declare(metadata i64* %out_size.addr, metadata !417, metadata !236), !dbg !418
  store i32 %action, i32* %action.addr, align 4
  call void @llvm.dbg.declare(metadata i32* %action.addr, metadata !419, metadata !236), !dbg !420
  br label %while.cond, !dbg !421

while.cond:                                       ; preds = %sw.epilog, %entry
  %0 = load i64*, i64** %out_pos.addr, align 8, !dbg !422
  %1 = load i64, i64* %0, align 8, !dbg !424
  %2 = load i64, i64* %out_size.addr, align 8, !dbg !425
  %cmp = icmp ult i64 %1, %2, !dbg !426
  br i1 %cmp, label %while.body, label %while.end, !dbg !427

while.body:                                       ; preds = %while.cond
  %3 = load %struct.lzma_coder_s*, %struct.lzma_coder_s** %coder.addr, align 8, !dbg !428
  %sequence = getelementptr inbounds %struct.lzma_coder_s, %struct.lzma_coder_s* %3, i32 0, i32 1, !dbg !429
  %4 = load i32, i32* %sequence, align 8, !dbg !429
  switch i32 %4, label %sw.default [
    i32 0, label %sw.bb
    i32 1, label %sw.bb4
  ], !dbg !430

sw.bb:                                            ; preds = %while.body
  %5 = load %struct.lzma_coder_s*, %struct.lzma_coder_s** %coder.addr, align 8, !dbg !431
  %header = getelementptr inbounds %struct.lzma_coder_s, %struct.lzma_coder_s* %5, i32 0, i32 3, !dbg !433
  %arraydecay = getelementptr inbounds [13 x i8], [13 x i8]* %header, i32 0, i32 0, !dbg !431
  %6 = load %struct.lzma_coder_s*, %struct.lzma_coder_s** %coder.addr, align 8, !dbg !434
  %header_pos = getelementptr inbounds %struct.lzma_coder_s, %struct.lzma_coder_s* %6, i32 0, i32 2, !dbg !435
  %7 = load i8*, i8** %out.addr, align 8, !dbg !436
  %8 = load i64*, i64** %out_pos.addr, align 8, !dbg !437
  %9 = load i64, i64* %out_size.addr, align 8, !dbg !438
  %call = call i64 @lzma_bufcpy(i8* %arraydecay, i64* %header_pos, i64 13, i8* %7, i64* %8, i64 %9), !dbg !439
  %10 = load %struct.lzma_coder_s*, %struct.lzma_coder_s** %coder.addr, align 8, !dbg !440
  %header_pos1 = getelementptr inbounds %struct.lzma_coder_s, %struct.lzma_coder_s* %10, i32 0, i32 2, !dbg !442
  %11 = load i64, i64* %header_pos1, align 8, !dbg !442
  %cmp2 = icmp ult i64 %11, 13, !dbg !443
  br i1 %cmp2, label %if.then, label %if.end, !dbg !444

if.then:                                          ; preds = %sw.bb
  store i32 0, i32* %retval, align 4, !dbg !445
  br label %return, !dbg !445

if.end:                                           ; preds = %sw.bb
  %12 = load %struct.lzma_coder_s*, %struct.lzma_coder_s** %coder.addr, align 8, !dbg !446
  %sequence3 = getelementptr inbounds %struct.lzma_coder_s, %struct.lzma_coder_s* %12, i32 0, i32 1, !dbg !447
  store i32 1, i32* %sequence3, align 8, !dbg !448
  br label %sw.epilog, !dbg !449

sw.bb4:                                           ; preds = %while.body
  %13 = load %struct.lzma_coder_s*, %struct.lzma_coder_s** %coder.addr, align 8, !dbg !450
  %next = getelementptr inbounds %struct.lzma_coder_s, %struct.lzma_coder_s* %13, i32 0, i32 0, !dbg !451
  %code = getelementptr inbounds %struct.lzma_next_coder_s, %struct.lzma_next_coder_s* %next, i32 0, i32 3, !dbg !452
  %14 = load i32 (%struct.lzma_coder_s*, %struct.lzma_allocator*, i8*, i64*, i64, i8*, i64*, i64, i32)*, i32 (%struct.lzma_coder_s*, %struct.lzma_allocator*, i8*, i64*, i64, i8*, i64*, i64, i32)** %code, align 8, !dbg !452
  %15 = load %struct.lzma_coder_s*, %struct.lzma_coder_s** %coder.addr, align 8, !dbg !453
  %next5 = getelementptr inbounds %struct.lzma_coder_s, %struct.lzma_coder_s* %15, i32 0, i32 0, !dbg !454
  %coder6 = getelementptr inbounds %struct.lzma_next_coder_s, %struct.lzma_next_coder_s* %next5, i32 0, i32 0, !dbg !455
  %16 = load %struct.lzma_coder_s*, %struct.lzma_coder_s** %coder6, align 8, !dbg !455
  %17 = load %struct.lzma_allocator*, %struct.lzma_allocator** %allocator.addr, align 8, !dbg !456
  %18 = load i8*, i8** %in.addr, align 8, !dbg !457
  %19 = load i64*, i64** %in_pos.addr, align 8, !dbg !458
  %20 = load i64, i64* %in_size.addr, align 8, !dbg !459
  %21 = load i8*, i8** %out.addr, align 8, !dbg !460
  %22 = load i64*, i64** %out_pos.addr, align 8, !dbg !461
  %23 = load i64, i64* %out_size.addr, align 8, !dbg !462
  %24 = load i32, i32* %action.addr, align 4, !dbg !463
  %call7 = call i32 %14(%struct.lzma_coder_s* %16, %struct.lzma_allocator* %17, i8* %18, i64* %19, i64 %20, i8* %21, i64* %22, i64 %23, i32 %24), !dbg !450
  store i32 %call7, i32* %retval, align 4, !dbg !464
  br label %return, !dbg !464

sw.default:                                       ; preds = %while.body
  call void @__assert_fail(i8* getelementptr inbounds ([2 x i8], [2 x i8]* @.str, i32 0, i32 0), i8* getelementptr inbounds ([85 x i8], [85 x i8]* @.str.1, i32 0, i32 0), i32 59, i8* getelementptr inbounds ([163 x i8], [163 x i8]* @__PRETTY_FUNCTION__.alone_encode, i32 0, i32 0)) #8, !dbg !465
  unreachable, !dbg !465

sw.epilog:                                        ; preds = %if.end
  br label %while.cond, !dbg !466

while.end:                                        ; preds = %while.cond
  store i32 0, i32* %retval, align 4, !dbg !468
  br label %return, !dbg !468

return:                                           ; preds = %while.end, %sw.bb4, %if.then
  %25 = load i32, i32* %retval, align 4, !dbg !469
  ret i32 %25, !dbg !469
}

; Function Attrs: nounwind uwtable
define internal void @alone_encoder_end(%struct.lzma_coder_s* %coder, %struct.lzma_allocator* %allocator) #0 !dbg !224 {
entry:
  %coder.addr = alloca %struct.lzma_coder_s*, align 8
  %allocator.addr = alloca %struct.lzma_allocator*, align 8
  store %struct.lzma_coder_s* %coder, %struct.lzma_coder_s** %coder.addr, align 8
  call void @llvm.dbg.declare(metadata %struct.lzma_coder_s** %coder.addr, metadata !470, metadata !236), !dbg !471
  store %struct.lzma_allocator* %allocator, %struct.lzma_allocator** %allocator.addr, align 8
  call void @llvm.dbg.declare(metadata %struct.lzma_allocator** %allocator.addr, metadata !472, metadata !236), !dbg !473
  %0 = load %struct.lzma_coder_s*, %struct.lzma_coder_s** %coder.addr, align 8, !dbg !474
  %next = getelementptr inbounds %struct.lzma_coder_s, %struct.lzma_coder_s* %0, i32 0, i32 0, !dbg !475
  %1 = load %struct.lzma_allocator*, %struct.lzma_allocator** %allocator.addr, align 8, !dbg !476
  call void @lzma_next_end(%struct.lzma_next_coder_s* %next, %struct.lzma_allocator* %1), !dbg !477
  %2 = load %struct.lzma_coder_s*, %struct.lzma_coder_s** %coder.addr, align 8, !dbg !478
  %3 = bitcast %struct.lzma_coder_s* %2 to i8*, !dbg !478
  %4 = load %struct.lzma_allocator*, %struct.lzma_allocator** %allocator.addr, align 8, !dbg !479
  call void @lzma_free(i8* %3, %struct.lzma_allocator* %4), !dbg !480
  ret void, !dbg !481
}

; Function Attrs: argmemonly nounwind
declare void @llvm.memcpy.p0i8.p0i8.i64(i8* nocapture, i8* nocapture readonly, i64, i32, i1) #4

declare zeroext i1 @lzma_lzma_lclppb_encode(%struct.lzma_options_lzma*, i8*) #2

; Function Attrs: inlinehint nounwind uwtable
define internal void @write32ne(i8* %buf, i32 %num) #5 !dbg !225 {
entry:
  %buf.addr = alloca i8*, align 8
  %num.addr = alloca i32, align 4
  store i8* %buf, i8** %buf.addr, align 8
  call void @llvm.dbg.declare(metadata i8** %buf.addr, metadata !482, metadata !236), !dbg !483
  store i32 %num, i32* %num.addr, align 4
  call void @llvm.dbg.declare(metadata i32* %num.addr, metadata !484, metadata !236), !dbg !485
  %0 = load i32, i32* %num.addr, align 4, !dbg !486
  %1 = load i8*, i8** %buf.addr, align 8, !dbg !487
  %2 = bitcast i8* %1 to i32*, !dbg !488
  store i32 %0, i32* %2, align 4, !dbg !489
  ret void, !dbg !490
}

; Function Attrs: argmemonly nounwind
declare void @llvm.memset.p0i8.i64(i8* nocapture, i8, i64, i32, i1) #4

declare i32 @lzma_next_filter_init(%struct.lzma_next_coder_s*, %struct.lzma_allocator*, %struct.lzma_filter_info_s*) #2

declare i64 @lzma_bufcpy(i8*, i64*, i64, i8*, i64*, i64) #2

; Function Attrs: noreturn nounwind
declare void @__assert_fail(i8*, i8*, i32, i8*) #6

declare void @lzma_free(i8*, %struct.lzma_allocator*) #2

attributes #0 = { nounwind uwtable "disable-tail-calls"="false" "less-precise-fpmad"="false" "no-frame-pointer-elim"="true" "no-frame-pointer-elim-non-leaf" "no-infs-fp-math"="false" "no-nans-fp-math"="false" "stack-protector-buffer-size"="8" "target-cpu"="x86-64" "target-features"="+fxsr,+mmx,+sse,+sse2" "unsafe-fp-math"="false" "use-soft-float"="false" }
attributes #1 = { nounwind readnone }
attributes #2 = { "disable-tail-calls"="false" "less-precise-fpmad"="false" "no-frame-pointer-elim"="true" "no-frame-pointer-elim-non-leaf" "no-infs-fp-math"="false" "no-nans-fp-math"="false" "stack-protector-buffer-size"="8" "target-cpu"="x86-64" "target-features"="+fxsr,+mmx,+sse,+sse2" "unsafe-fp-math"="false" "use-soft-float"="false" }
attributes #3 = { nounwind "disable-tail-calls"="false" "less-precise-fpmad"="false" "no-frame-pointer-elim"="true" "no-frame-pointer-elim-non-leaf" "no-infs-fp-math"="false" "no-nans-fp-math"="false" "stack-protector-buffer-size"="8" "target-cpu"="x86-64" "target-features"="+fxsr,+mmx,+sse,+sse2" "unsafe-fp-math"="false" "use-soft-float"="false" }
attributes #4 = { argmemonly nounwind }
attributes #5 = { inlinehint nounwind uwtable "disable-tail-calls"="false" "less-precise-fpmad"="false" "no-frame-pointer-elim"="true" "no-frame-pointer-elim-non-leaf" "no-infs-fp-math"="false" "no-nans-fp-math"="false" "stack-protector-buffer-size"="8" "target-cpu"="x86-64" "target-features"="+fxsr,+mmx,+sse,+sse2" "unsafe-fp-math"="false" "use-soft-float"="false" }
attributes #6 = { noreturn nounwind "disable-tail-calls"="false" "less-precise-fpmad"="false" "no-frame-pointer-elim"="true" "no-frame-pointer-elim-non-leaf" "no-infs-fp-math"="false" "no-nans-fp-math"="false" "stack-protector-buffer-size"="8" "target-cpu"="x86-64" "target-features"="+fxsr,+mmx,+sse,+sse2" "unsafe-fp-math"="false" "use-soft-float"="false" }
attributes #7 = { nounwind }
attributes #8 = { noreturn nounwind }

!llvm.dbg.cu = !{!0}
!llvm.module.flags = !{!232, !233}
!llvm.ident = !{!234}

!0 = distinct !DICompileUnit(language: DW_LANG_C99, file: !1, producer: "clang version 3.8.0 (tags/RELEASE_380/final)", isOptimized: false, runtimeVersion: 0, emissionKind: 1, enums: !2, retainedTypes: !154, subprograms: !158, globals: !229)
!1 = !DIFile(filename: "/data/download/cmake/cmake-master/Utilities/cmliblzma/liblzma/common/alone_encoder.c", directory: "/data/download/cmake/cmake-master/Utilities/cmliblzma")
!2 = !{!3, !18, !69, !86, !120, !139, !142, !147}
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
!18 = !DICompositeType(tag: DW_TAG_enumeration_type, scope: !19, file: !1, line: 23, size: 32, align: 32, elements: !117)
!19 = !DICompositeType(tag: DW_TAG_structure_type, name: "lzma_coder_s", file: !1, line: 20, size: 768, align: 64, elements: !20)
!20 = !{!21, !111, !112, !113}
!21 = !DIDerivedType(tag: DW_TAG_member, name: "next", scope: !19, file: !1, line: 21, baseType: !22, size: 512, align: 64)
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
!111 = !DIDerivedType(tag: DW_TAG_member, name: "sequence", scope: !19, file: !1, line: 26, baseType: !18, size: 32, align: 32, offset: 512)
!112 = !DIDerivedType(tag: DW_TAG_member, name: "header_pos", scope: !19, file: !1, line: 28, baseType: !52, size: 64, align: 64, offset: 576)
!113 = !DIDerivedType(tag: DW_TAG_member, name: "header", scope: !19, file: !1, line: 29, baseType: !114, size: 104, align: 8, offset: 640)
!114 = !DICompositeType(tag: DW_TAG_array_type, baseType: !62, size: 104, align: 8, elements: !115)
!115 = !{!116}
!116 = !DISubrange(count: 13)
!117 = !{!118, !119}
!118 = !DIEnumerator(name: "SEQ_HEADER", value: 0)
!119 = !DIEnumerator(name: "SEQ_CODE", value: 1)
!120 = !DICompositeType(tag: DW_TAG_enumeration_type, scope: !121, file: !23, line: 182, size: 32, align: 32, elements: !132)
!121 = !DICompositeType(tag: DW_TAG_structure_type, name: "lzma_internal_s", file: !23, line: 174, size: 704, align: 64, elements: !122)
!122 = !{!123, !124, !125, !126, !131}
!123 = !DIDerivedType(tag: DW_TAG_member, name: "next", scope: !121, file: !23, line: 176, baseType: !22, size: 512, align: 64)
!124 = !DIDerivedType(tag: DW_TAG_member, name: "sequence", scope: !121, file: !23, line: 189, baseType: !120, size: 32, align: 32, offset: 512)
!125 = !DIDerivedType(tag: DW_TAG_member, name: "avail_in", scope: !121, file: !23, line: 194, baseType: !52, size: 64, align: 64, offset: 576)
!126 = !DIDerivedType(tag: DW_TAG_member, name: "supported_actions", scope: !121, file: !23, line: 197, baseType: !127, size: 32, align: 8, offset: 640)
!127 = !DICompositeType(tag: DW_TAG_array_type, baseType: !128, size: 32, align: 8, elements: !129)
!128 = !DIBasicType(name: "_Bool", size: 8, align: 8, encoding: DW_ATE_boolean)
!129 = !{!130}
!130 = !DISubrange(count: 4)
!131 = !DIDerivedType(tag: DW_TAG_member, name: "allow_buf_error", scope: !121, file: !23, line: 201, baseType: !128, size: 8, align: 8, offset: 672)
!132 = !{!133, !134, !135, !136, !137, !138}
!133 = !DIEnumerator(name: "ISEQ_RUN", value: 0)
!134 = !DIEnumerator(name: "ISEQ_SYNC_FLUSH", value: 1)
!135 = !DIEnumerator(name: "ISEQ_FULL_FLUSH", value: 2)
!136 = !DIEnumerator(name: "ISEQ_FINISH", value: 3)
!137 = !DIEnumerator(name: "ISEQ_END", value: 4)
!138 = !DIEnumerator(name: "ISEQ_ERROR", value: 5)
!139 = !DICompositeType(tag: DW_TAG_enumeration_type, file: !4, line: 44, size: 32, align: 32, elements: !140)
!140 = !{!141}
!141 = !DIEnumerator(name: "LZMA_RESERVED_ENUM", value: 0)
!142 = !DICompositeType(tag: DW_TAG_enumeration_type, file: !143, line: 138, size: 32, align: 32, elements: !144)
!143 = !DIFile(filename: "/data/download/cmake/cmake-master/Utilities/cmliblzma/liblzma/api/lzma/lzma.h", directory: "/data/download/cmake/cmake-master/Utilities/cmliblzma")
!144 = !{!145, !146}
!145 = !DIEnumerator(name: "LZMA_MODE_FAST", value: 1)
!146 = !DIEnumerator(name: "LZMA_MODE_NORMAL", value: 2)
!147 = !DICompositeType(tag: DW_TAG_enumeration_type, file: !143, line: 58, size: 32, align: 32, elements: !148)
!148 = !{!149, !150, !151, !152, !153}
!149 = !DIEnumerator(name: "LZMA_MF_HC3", value: 3)
!150 = !DIEnumerator(name: "LZMA_MF_HC4", value: 4)
!151 = !DIEnumerator(name: "LZMA_MF_BT2", value: 18)
!152 = !DIEnumerator(name: "LZMA_MF_BT3", value: 19)
!153 = !DIEnumerator(name: "LZMA_MF_BT4", value: 20)
!154 = !{!51, !36, !155, !157}
!155 = !DIDerivedType(tag: DW_TAG_typedef, name: "uint32_t", file: !33, line: 51, baseType: !156)
!156 = !DIBasicType(name: "unsigned int", size: 32, align: 32, encoding: DW_ATE_unsigned)
!157 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !155, size: 64, align: 64)
!158 = !{!159, !219, !223, !224, !225}
!159 = distinct !DISubprogram(name: "lzma_alone_encoder", scope: !1, file: !1, line: 147, type: !160, isLocal: false, isDefinition: true, scopeLine: 148, flags: DIFlagPrototyped, isOptimized: false, variables: !218)
!160 = !DISubroutineType(types: !161)
!161 = !{!42, !162, !187}
!162 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !163, size: 64, align: 64)
!163 = !DIDerivedType(tag: DW_TAG_typedef, name: "lzma_stream", file: !4, line: 490, baseType: !164)
!164 = !DICompositeType(tag: DW_TAG_structure_type, file: !4, line: 453, size: 1088, align: 64, elements: !165)
!165 = !{!166, !167, !168, !169, !170, !171, !172, !173, !176, !177, !178, !179, !180, !181, !182, !183, !184, !186}
!166 = !DIDerivedType(tag: DW_TAG_member, name: "next_in", scope: !164, file: !4, line: 454, baseType: !60, size: 64, align: 64)
!167 = !DIDerivedType(tag: DW_TAG_member, name: "avail_in", scope: !164, file: !4, line: 455, baseType: !52, size: 64, align: 64, offset: 64)
!168 = !DIDerivedType(tag: DW_TAG_member, name: "total_in", scope: !164, file: !4, line: 456, baseType: !32, size: 64, align: 64, offset: 128)
!169 = !DIDerivedType(tag: DW_TAG_member, name: "next_out", scope: !164, file: !4, line: 458, baseType: !67, size: 64, align: 64, offset: 192)
!170 = !DIDerivedType(tag: DW_TAG_member, name: "avail_out", scope: !164, file: !4, line: 459, baseType: !52, size: 64, align: 64, offset: 256)
!171 = !DIDerivedType(tag: DW_TAG_member, name: "total_out", scope: !164, file: !4, line: 460, baseType: !32, size: 64, align: 64, offset: 320)
!172 = !DIDerivedType(tag: DW_TAG_member, name: "allocator", scope: !164, file: !4, line: 468, baseType: !43, size: 64, align: 64, offset: 384)
!173 = !DIDerivedType(tag: DW_TAG_member, name: "internal", scope: !164, file: !4, line: 471, baseType: !174, size: 64, align: 64, offset: 448)
!174 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !175, size: 64, align: 64)
!175 = !DIDerivedType(tag: DW_TAG_typedef, name: "lzma_internal", file: !4, line: 411, baseType: !121)
!176 = !DIDerivedType(tag: DW_TAG_member, name: "reserved_ptr1", scope: !164, file: !4, line: 479, baseType: !51, size: 64, align: 64, offset: 512)
!177 = !DIDerivedType(tag: DW_TAG_member, name: "reserved_ptr2", scope: !164, file: !4, line: 480, baseType: !51, size: 64, align: 64, offset: 576)
!178 = !DIDerivedType(tag: DW_TAG_member, name: "reserved_ptr3", scope: !164, file: !4, line: 481, baseType: !51, size: 64, align: 64, offset: 640)
!179 = !DIDerivedType(tag: DW_TAG_member, name: "reserved_ptr4", scope: !164, file: !4, line: 482, baseType: !51, size: 64, align: 64, offset: 704)
!180 = !DIDerivedType(tag: DW_TAG_member, name: "reserved_int1", scope: !164, file: !4, line: 483, baseType: !32, size: 64, align: 64, offset: 768)
!181 = !DIDerivedType(tag: DW_TAG_member, name: "reserved_int2", scope: !164, file: !4, line: 484, baseType: !32, size: 64, align: 64, offset: 832)
!182 = !DIDerivedType(tag: DW_TAG_member, name: "reserved_int3", scope: !164, file: !4, line: 485, baseType: !52, size: 64, align: 64, offset: 896)
!183 = !DIDerivedType(tag: DW_TAG_member, name: "reserved_int4", scope: !164, file: !4, line: 486, baseType: !52, size: 64, align: 64, offset: 960)
!184 = !DIDerivedType(tag: DW_TAG_member, name: "reserved_enum1", scope: !164, file: !4, line: 487, baseType: !185, size: 32, align: 32, offset: 1024)
!185 = !DIDerivedType(tag: DW_TAG_typedef, name: "lzma_reserved_enum", file: !4, line: 46, baseType: !139)
!186 = !DIDerivedType(tag: DW_TAG_member, name: "reserved_enum2", scope: !164, file: !4, line: 488, baseType: !185, size: 32, align: 32, offset: 1056)
!187 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !188, size: 64, align: 64)
!188 = !DIDerivedType(tag: DW_TAG_const_type, baseType: !189)
!189 = !DIDerivedType(tag: DW_TAG_typedef, name: "lzma_options_lzma", file: !143, line: 399, baseType: !190)
!190 = !DICompositeType(tag: DW_TAG_structure_type, file: !143, line: 185, size: 896, align: 64, elements: !191)
!191 = !{!192, !193, !194, !195, !196, !197, !198, !200, !201, !203, !204, !205, !206, !207, !208, !209, !210, !211, !212, !213, !214, !215, !216, !217}
!192 = !DIDerivedType(tag: DW_TAG_member, name: "dict_size", scope: !190, file: !143, line: 217, baseType: !155, size: 32, align: 32)
!193 = !DIDerivedType(tag: DW_TAG_member, name: "preset_dict", scope: !190, file: !143, line: 240, baseType: !60, size: 64, align: 64, offset: 64)
!194 = !DIDerivedType(tag: DW_TAG_member, name: "preset_dict_size", scope: !190, file: !143, line: 254, baseType: !155, size: 32, align: 32, offset: 128)
!195 = !DIDerivedType(tag: DW_TAG_member, name: "lc", scope: !190, file: !143, line: 281, baseType: !155, size: 32, align: 32, offset: 160)
!196 = !DIDerivedType(tag: DW_TAG_member, name: "lp", scope: !190, file: !143, line: 293, baseType: !155, size: 32, align: 32, offset: 192)
!197 = !DIDerivedType(tag: DW_TAG_member, name: "pb", scope: !190, file: !143, line: 316, baseType: !155, size: 32, align: 32, offset: 224)
!198 = !DIDerivedType(tag: DW_TAG_member, name: "mode", scope: !190, file: !143, line: 322, baseType: !199, size: 32, align: 32, offset: 256)
!199 = !DIDerivedType(tag: DW_TAG_typedef, name: "lzma_mode", file: !143, line: 155, baseType: !142)
!200 = !DIDerivedType(tag: DW_TAG_member, name: "nice_len", scope: !190, file: !143, line: 342, baseType: !155, size: 32, align: 32, offset: 288)
!201 = !DIDerivedType(tag: DW_TAG_member, name: "mf", scope: !190, file: !143, line: 345, baseType: !202, size: 32, align: 32, offset: 320)
!202 = !DIDerivedType(tag: DW_TAG_typedef, name: "lzma_match_finder", file: !143, line: 111, baseType: !147)
!203 = !DIDerivedType(tag: DW_TAG_member, name: "depth", scope: !190, file: !143, line: 375, baseType: !155, size: 32, align: 32, offset: 352)
!204 = !DIDerivedType(tag: DW_TAG_member, name: "reserved_int1", scope: !190, file: !143, line: 384, baseType: !155, size: 32, align: 32, offset: 384)
!205 = !DIDerivedType(tag: DW_TAG_member, name: "reserved_int2", scope: !190, file: !143, line: 385, baseType: !155, size: 32, align: 32, offset: 416)
!206 = !DIDerivedType(tag: DW_TAG_member, name: "reserved_int3", scope: !190, file: !143, line: 386, baseType: !155, size: 32, align: 32, offset: 448)
!207 = !DIDerivedType(tag: DW_TAG_member, name: "reserved_int4", scope: !190, file: !143, line: 387, baseType: !155, size: 32, align: 32, offset: 480)
!208 = !DIDerivedType(tag: DW_TAG_member, name: "reserved_int5", scope: !190, file: !143, line: 388, baseType: !155, size: 32, align: 32, offset: 512)
!209 = !DIDerivedType(tag: DW_TAG_member, name: "reserved_int6", scope: !190, file: !143, line: 389, baseType: !155, size: 32, align: 32, offset: 544)
!210 = !DIDerivedType(tag: DW_TAG_member, name: "reserved_int7", scope: !190, file: !143, line: 390, baseType: !155, size: 32, align: 32, offset: 576)
!211 = !DIDerivedType(tag: DW_TAG_member, name: "reserved_int8", scope: !190, file: !143, line: 391, baseType: !155, size: 32, align: 32, offset: 608)
!212 = !DIDerivedType(tag: DW_TAG_member, name: "reserved_enum1", scope: !190, file: !143, line: 392, baseType: !185, size: 32, align: 32, offset: 640)
!213 = !DIDerivedType(tag: DW_TAG_member, name: "reserved_enum2", scope: !190, file: !143, line: 393, baseType: !185, size: 32, align: 32, offset: 672)
!214 = !DIDerivedType(tag: DW_TAG_member, name: "reserved_enum3", scope: !190, file: !143, line: 394, baseType: !185, size: 32, align: 32, offset: 704)
!215 = !DIDerivedType(tag: DW_TAG_member, name: "reserved_enum4", scope: !190, file: !143, line: 395, baseType: !185, size: 32, align: 32, offset: 736)
!216 = !DIDerivedType(tag: DW_TAG_member, name: "reserved_ptr1", scope: !190, file: !143, line: 396, baseType: !51, size: 64, align: 64, offset: 768)
!217 = !DIDerivedType(tag: DW_TAG_member, name: "reserved_ptr2", scope: !190, file: !143, line: 397, baseType: !51, size: 64, align: 64, offset: 832)
!218 = !{}
!219 = distinct !DISubprogram(name: "alone_encoder_init", scope: !1, file: !1, line: 78, type: !220, isLocal: true, isDefinition: true, scopeLine: 80, flags: DIFlagPrototyped, isOptimized: false, variables: !218)
!220 = !DISubroutineType(types: !221)
!221 = !{!42, !222, !43, !187}
!222 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !22, size: 64, align: 64)
!223 = distinct !DISubprogram(name: "alone_encode", scope: !1, file: !1, line: 34, type: !40, isLocal: true, isDefinition: true, scopeLine: 40, flags: DIFlagPrototyped, isOptimized: false, variables: !218)
!224 = distinct !DISubprogram(name: "alone_encoder_end", scope: !1, file: !1, line: 68, type: !78, isLocal: true, isDefinition: true, scopeLine: 69, flags: DIFlagPrototyped, isOptimized: false, variables: !218)
!225 = distinct !DISubprogram(name: "write32ne", scope: !226, file: !226, line: 255, type: !227, isLocal: true, isDefinition: true, scopeLine: 256, flags: DIFlagPrototyped, isOptimized: false, variables: !218)
!226 = !DIFile(filename: "/data/download/cmake/cmake-master/Utilities/cmliblzma/common/tuklib_integer.h", directory: "/data/download/cmake/cmake-master/Utilities/cmliblzma")
!227 = !DISubroutineType(types: !228)
!228 = !{null, !67, !155}
!229 = !{!230}
!230 = !DIGlobalVariable(name: "LZMA_NEXT_CODER_INIT", scope: !0, file: !23, line: 159, type: !231, isLocal: true, isDefinition: true, variable: %struct.lzma_next_coder_s* @LZMA_NEXT_CODER_INIT)
!231 = !DIDerivedType(tag: DW_TAG_const_type, baseType: !22)
!232 = !{i32 2, !"Dwarf Version", i32 4}
!233 = !{i32 2, !"Debug Info Version", i32 3}
!234 = !{!"clang version 3.8.0 (tags/RELEASE_380/final)"}
!235 = !DILocalVariable(name: "strm", arg: 1, scope: !159, file: !1, line: 147, type: !162)
!236 = !DIExpression()
!237 = !DILocation(line: 147, column: 33, scope: !159)
!238 = !DILocalVariable(name: "options", arg: 2, scope: !159, file: !1, line: 147, type: !187)
!239 = !DILocation(line: 147, column: 64, scope: !159)
!240 = !DILocation(line: 149, column: 2, scope: !159)
!241 = !DILocalVariable(name: "ret_", scope: !242, file: !1, line: 149, type: !42)
!242 = distinct !DILexicalBlock(scope: !159, file: !1, line: 149, column: 2)
!243 = !DILocation(line: 149, column: 2, scope: !242)
!244 = !DILocation(line: 149, column: 2, scope: !245)
!245 = !DILexicalBlockFile(scope: !242, file: !1, discriminator: 1)
!246 = !DILocalVariable(name: "ret_", scope: !247, file: !1, line: 149, type: !248)
!247 = distinct !DILexicalBlock(scope: !242, file: !1, line: 149, column: 2)
!248 = !DIDerivedType(tag: DW_TAG_const_type, baseType: !42)
!249 = !DILocation(line: 149, column: 2, scope: !247)
!250 = !DILocation(line: 149, column: 2, scope: !251)
!251 = !DILexicalBlockFile(scope: !247, file: !1, discriminator: 2)
!252 = !DILocation(line: 149, column: 2, scope: !253)
!253 = !DILexicalBlockFile(scope: !254, file: !1, discriminator: 3)
!254 = distinct !DILexicalBlock(scope: !247, file: !1, line: 149, column: 2)
!255 = !DILocation(line: 149, column: 2, scope: !256)
!256 = !DILexicalBlockFile(scope: !247, file: !1, discriminator: 4)
!257 = !DILocation(line: 149, column: 2, scope: !258)
!258 = !DILexicalBlockFile(scope: !242, file: !1, discriminator: 5)
!259 = !DILocation(line: 149, column: 2, scope: !260)
!260 = !DILexicalBlockFile(scope: !261, file: !1, discriminator: 6)
!261 = distinct !DILexicalBlock(scope: !262, file: !1, line: 149, column: 2)
!262 = distinct !DILexicalBlock(scope: !242, file: !1, line: 149, column: 2)
!263 = !DILocation(line: 149, column: 2, scope: !264)
!264 = !DILexicalBlockFile(scope: !242, file: !1, discriminator: 7)
!265 = !DILocation(line: 151, column: 2, scope: !159)
!266 = !DILocation(line: 151, column: 8, scope: !159)
!267 = !DILocation(line: 151, column: 18, scope: !159)
!268 = !DILocation(line: 151, column: 46, scope: !159)
!269 = !DILocation(line: 152, column: 2, scope: !159)
!270 = !DILocation(line: 152, column: 8, scope: !159)
!271 = !DILocation(line: 152, column: 18, scope: !159)
!272 = !DILocation(line: 152, column: 49, scope: !159)
!273 = !DILocation(line: 154, column: 2, scope: !159)
!274 = !DILocation(line: 155, column: 1, scope: !159)
!275 = !DILocalVariable(name: "next", arg: 1, scope: !219, file: !1, line: 78, type: !222)
!276 = !DILocation(line: 78, column: 37, scope: !219)
!277 = !DILocalVariable(name: "allocator", arg: 2, scope: !219, file: !1, line: 78, type: !43)
!278 = !DILocation(line: 78, column: 59, scope: !219)
!279 = !DILocalVariable(name: "options", arg: 3, scope: !219, file: !1, line: 79, type: !187)
!280 = !DILocation(line: 79, column: 28, scope: !219)
!281 = !DILocalVariable(name: "d", scope: !219, file: !1, line: 81, type: !155)
!282 = !DILocation(line: 81, column: 11, scope: !219)
!283 = !DILocalVariable(name: "filters", scope: !219, file: !1, line: 84, type: !284)
!284 = !DICompositeType(tag: DW_TAG_array_type, baseType: !285, size: 384, align: 64, elements: !297)
!285 = !DIDerivedType(tag: DW_TAG_const_type, baseType: !286)
!286 = !DIDerivedType(tag: DW_TAG_typedef, name: "lzma_filter_info", file: !23, line: 77, baseType: !287)
!287 = !DICompositeType(tag: DW_TAG_structure_type, name: "lzma_filter_info_s", file: !23, line: 104, size: 192, align: 64, elements: !288)
!288 = !{!289, !290, !296}
!289 = !DIDerivedType(tag: DW_TAG_member, name: "id", scope: !287, file: !23, line: 107, baseType: !30, size: 64, align: 64)
!290 = !DIDerivedType(tag: DW_TAG_member, name: "init", scope: !287, file: !23, line: 111, baseType: !291, size: 64, align: 64, offset: 64)
!291 = !DIDerivedType(tag: DW_TAG_typedef, name: "lzma_init_function", file: !23, line: 81, baseType: !292)
!292 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !293, size: 64, align: 64)
!293 = !DISubroutineType(types: !294)
!294 = !{!42, !222, !43, !295}
!295 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !285, size: 64, align: 64)
!296 = !DIDerivedType(tag: DW_TAG_member, name: "options", scope: !287, file: !23, line: 114, baseType: !51, size: 64, align: 64, offset: 128)
!297 = !{!298}
!298 = !DISubrange(count: 2)
!299 = !DILocation(line: 84, column: 25, scope: !219)
!300 = !DILocation(line: 84, column: 38, scope: !219)
!301 = !DILocation(line: 85, column: 6, scope: !219)
!302 = !DILocation(line: 85, column: 45, scope: !219)
!303 = !DILocation(line: 85, column: 36, scope: !219)
!304 = !DILocation(line: 86, column: 6, scope: !219)
!305 = !DILocation(line: 89, column: 2, scope: !219)
!306 = !DILocation(line: 89, column: 2, scope: !307)
!307 = !DILexicalBlockFile(scope: !308, file: !1, discriminator: 1)
!308 = distinct !DILexicalBlock(scope: !309, file: !1, line: 89, column: 2)
!309 = distinct !DILexicalBlock(scope: !219, file: !1, line: 89, column: 2)
!310 = !DILocation(line: 89, column: 2, scope: !311)
!311 = !DILexicalBlockFile(scope: !308, file: !1, discriminator: 2)
!312 = !DILocation(line: 89, column: 2, scope: !313)
!313 = !DILexicalBlockFile(scope: !309, file: !1, discriminator: 3)
!314 = !DILocation(line: 91, column: 6, scope: !315)
!315 = distinct !DILexicalBlock(scope: !219, file: !1, line: 91, column: 6)
!316 = !DILocation(line: 91, column: 12, scope: !315)
!317 = !DILocation(line: 91, column: 18, scope: !315)
!318 = !DILocation(line: 91, column: 6, scope: !219)
!319 = !DILocation(line: 92, column: 48, scope: !320)
!320 = distinct !DILexicalBlock(scope: !315, file: !1, line: 91, column: 27)
!321 = !DILocation(line: 92, column: 17, scope: !320)
!322 = !DILocation(line: 92, column: 3, scope: !320)
!323 = !DILocation(line: 92, column: 9, scope: !320)
!324 = !DILocation(line: 92, column: 15, scope: !320)
!325 = !DILocation(line: 93, column: 7, scope: !326)
!326 = distinct !DILexicalBlock(scope: !320, file: !1, line: 93, column: 7)
!327 = !DILocation(line: 93, column: 13, scope: !326)
!328 = !DILocation(line: 93, column: 19, scope: !326)
!329 = !DILocation(line: 93, column: 7, scope: !320)
!330 = !DILocation(line: 94, column: 4, scope: !326)
!331 = !DILocation(line: 96, column: 3, scope: !320)
!332 = !DILocation(line: 96, column: 9, scope: !320)
!333 = !DILocation(line: 96, column: 14, scope: !320)
!334 = !DILocation(line: 97, column: 3, scope: !320)
!335 = !DILocation(line: 97, column: 9, scope: !320)
!336 = !DILocation(line: 97, column: 13, scope: !320)
!337 = !DILocation(line: 98, column: 3, scope: !320)
!338 = !DILocation(line: 98, column: 9, scope: !320)
!339 = !DILocation(line: 98, column: 16, scope: !320)
!340 = !DILocation(line: 98, column: 23, scope: !320)
!341 = !DILocation(line: 99, column: 2, scope: !320)
!342 = !DILocation(line: 102, column: 2, scope: !219)
!343 = !DILocation(line: 102, column: 8, scope: !219)
!344 = !DILocation(line: 102, column: 15, scope: !219)
!345 = !DILocation(line: 102, column: 24, scope: !219)
!346 = !DILocation(line: 103, column: 2, scope: !219)
!347 = !DILocation(line: 103, column: 8, scope: !219)
!348 = !DILocation(line: 103, column: 15, scope: !219)
!349 = !DILocation(line: 103, column: 26, scope: !219)
!350 = !DILocation(line: 107, column: 30, scope: !351)
!351 = distinct !DILexicalBlock(scope: !219, file: !1, line: 107, column: 6)
!352 = !DILocation(line: 107, column: 39, scope: !351)
!353 = !DILocation(line: 107, column: 45, scope: !351)
!354 = !DILocation(line: 107, column: 52, scope: !351)
!355 = !DILocation(line: 107, column: 6, scope: !351)
!356 = !DILocation(line: 107, column: 6, scope: !219)
!357 = !DILocation(line: 108, column: 3, scope: !351)
!358 = !DILocation(line: 111, column: 6, scope: !359)
!359 = distinct !DILexicalBlock(scope: !219, file: !1, line: 111, column: 6)
!360 = !DILocation(line: 111, column: 15, scope: !359)
!361 = !DILocation(line: 111, column: 25, scope: !359)
!362 = !DILocation(line: 111, column: 6, scope: !219)
!363 = !DILocation(line: 112, column: 3, scope: !359)
!364 = !DILocation(line: 118, column: 6, scope: !219)
!365 = !DILocation(line: 118, column: 15, scope: !219)
!366 = !DILocation(line: 118, column: 25, scope: !219)
!367 = !DILocation(line: 118, column: 4, scope: !219)
!368 = !DILocation(line: 119, column: 7, scope: !219)
!369 = !DILocation(line: 119, column: 9, scope: !219)
!370 = !DILocation(line: 119, column: 4, scope: !219)
!371 = !DILocation(line: 120, column: 7, scope: !219)
!372 = !DILocation(line: 120, column: 9, scope: !219)
!373 = !DILocation(line: 120, column: 4, scope: !219)
!374 = !DILocation(line: 121, column: 7, scope: !219)
!375 = !DILocation(line: 121, column: 9, scope: !219)
!376 = !DILocation(line: 121, column: 4, scope: !219)
!377 = !DILocation(line: 122, column: 7, scope: !219)
!378 = !DILocation(line: 122, column: 9, scope: !219)
!379 = !DILocation(line: 122, column: 4, scope: !219)
!380 = !DILocation(line: 123, column: 7, scope: !219)
!381 = !DILocation(line: 123, column: 9, scope: !219)
!382 = !DILocation(line: 123, column: 4, scope: !219)
!383 = !DILocation(line: 124, column: 6, scope: !384)
!384 = distinct !DILexicalBlock(scope: !219, file: !1, line: 124, column: 6)
!385 = !DILocation(line: 124, column: 8, scope: !384)
!386 = !DILocation(line: 124, column: 6, scope: !219)
!387 = !DILocation(line: 125, column: 3, scope: !384)
!388 = !DILocation(line: 127, column: 2, scope: !219)
!389 = !DILocation(line: 130, column: 9, scope: !219)
!390 = !DILocation(line: 130, column: 15, scope: !219)
!391 = !DILocation(line: 130, column: 22, scope: !219)
!392 = !DILocation(line: 130, column: 29, scope: !219)
!393 = !DILocation(line: 130, column: 33, scope: !219)
!394 = !DILocation(line: 130, column: 2, scope: !219)
!395 = !DILocation(line: 132, column: 32, scope: !219)
!396 = !DILocation(line: 132, column: 38, scope: !219)
!397 = !DILocation(line: 132, column: 45, scope: !219)
!398 = !DILocation(line: 132, column: 51, scope: !219)
!399 = !DILocation(line: 132, column: 62, scope: !219)
!400 = !DILocation(line: 132, column: 9, scope: !219)
!401 = !DILocation(line: 132, column: 2, scope: !219)
!402 = !DILocation(line: 133, column: 1, scope: !219)
!403 = !DILocalVariable(name: "coder", arg: 1, scope: !223, file: !1, line: 34, type: !27)
!404 = !DILocation(line: 34, column: 26, scope: !223)
!405 = !DILocalVariable(name: "allocator", arg: 2, scope: !223, file: !1, line: 35, type: !43)
!406 = !DILocation(line: 35, column: 19, scope: !223)
!407 = !DILocalVariable(name: "in", arg: 3, scope: !223, file: !1, line: 36, type: !59)
!408 = !DILocation(line: 36, column: 32, scope: !223)
!409 = !DILocalVariable(name: "in_pos", arg: 4, scope: !223, file: !1, line: 36, type: !64)
!410 = !DILocation(line: 36, column: 58, scope: !223)
!411 = !DILocalVariable(name: "in_size", arg: 5, scope: !223, file: !1, line: 37, type: !52)
!412 = !DILocation(line: 37, column: 10, scope: !223)
!413 = !DILocalVariable(name: "out", arg: 6, scope: !223, file: !1, line: 37, type: !66)
!414 = !DILocation(line: 37, column: 42, scope: !223)
!415 = !DILocalVariable(name: "out_pos", arg: 7, scope: !223, file: !1, line: 38, type: !64)
!416 = !DILocation(line: 38, column: 25, scope: !223)
!417 = !DILocalVariable(name: "out_size", arg: 8, scope: !223, file: !1, line: 38, type: !52)
!418 = !DILocation(line: 38, column: 41, scope: !223)
!419 = !DILocalVariable(name: "action", arg: 9, scope: !223, file: !1, line: 39, type: !68)
!420 = !DILocation(line: 39, column: 15, scope: !223)
!421 = !DILocation(line: 41, column: 2, scope: !223)
!422 = !DILocation(line: 41, column: 10, scope: !423)
!423 = !DILexicalBlockFile(scope: !223, file: !1, discriminator: 1)
!424 = !DILocation(line: 41, column: 9, scope: !423)
!425 = !DILocation(line: 41, column: 20, scope: !423)
!426 = !DILocation(line: 41, column: 18, scope: !423)
!427 = !DILocation(line: 41, column: 2, scope: !423)
!428 = !DILocation(line: 42, column: 10, scope: !223)
!429 = !DILocation(line: 42, column: 17, scope: !223)
!430 = !DILocation(line: 42, column: 2, scope: !223)
!431 = !DILocation(line: 44, column: 15, scope: !432)
!432 = distinct !DILexicalBlock(scope: !223, file: !1, line: 42, column: 27)
!433 = !DILocation(line: 44, column: 22, scope: !432)
!434 = !DILocation(line: 44, column: 31, scope: !432)
!435 = !DILocation(line: 44, column: 38, scope: !432)
!436 = !DILocation(line: 46, column: 5, scope: !432)
!437 = !DILocation(line: 46, column: 10, scope: !432)
!438 = !DILocation(line: 46, column: 19, scope: !432)
!439 = !DILocation(line: 44, column: 3, scope: !432)
!440 = !DILocation(line: 47, column: 7, scope: !441)
!441 = distinct !DILexicalBlock(scope: !432, file: !1, line: 47, column: 7)
!442 = !DILocation(line: 47, column: 14, scope: !441)
!443 = !DILocation(line: 47, column: 25, scope: !441)
!444 = !DILocation(line: 47, column: 7, scope: !432)
!445 = !DILocation(line: 48, column: 4, scope: !441)
!446 = !DILocation(line: 50, column: 3, scope: !432)
!447 = !DILocation(line: 50, column: 10, scope: !432)
!448 = !DILocation(line: 50, column: 19, scope: !432)
!449 = !DILocation(line: 51, column: 3, scope: !432)
!450 = !DILocation(line: 54, column: 10, scope: !432)
!451 = !DILocation(line: 54, column: 17, scope: !432)
!452 = !DILocation(line: 54, column: 22, scope: !432)
!453 = !DILocation(line: 54, column: 27, scope: !432)
!454 = !DILocation(line: 54, column: 34, scope: !432)
!455 = !DILocation(line: 54, column: 39, scope: !432)
!456 = !DILocation(line: 55, column: 5, scope: !432)
!457 = !DILocation(line: 55, column: 16, scope: !432)
!458 = !DILocation(line: 55, column: 20, scope: !432)
!459 = !DILocation(line: 55, column: 28, scope: !432)
!460 = !DILocation(line: 56, column: 5, scope: !432)
!461 = !DILocation(line: 56, column: 10, scope: !432)
!462 = !DILocation(line: 56, column: 19, scope: !432)
!463 = !DILocation(line: 56, column: 29, scope: !432)
!464 = !DILocation(line: 54, column: 3, scope: !432)
!465 = !DILocation(line: 59, column: 3, scope: !432)
!466 = !DILocation(line: 41, column: 2, scope: !467)
!467 = !DILexicalBlockFile(scope: !223, file: !1, discriminator: 2)
!468 = !DILocation(line: 63, column: 2, scope: !223)
!469 = !DILocation(line: 64, column: 1, scope: !223)
!470 = !DILocalVariable(name: "coder", arg: 1, scope: !224, file: !1, line: 68, type: !27)
!471 = !DILocation(line: 68, column: 31, scope: !224)
!472 = !DILocalVariable(name: "allocator", arg: 2, scope: !224, file: !1, line: 68, type: !43)
!473 = !DILocation(line: 68, column: 54, scope: !224)
!474 = !DILocation(line: 70, column: 17, scope: !224)
!475 = !DILocation(line: 70, column: 24, scope: !224)
!476 = !DILocation(line: 70, column: 30, scope: !224)
!477 = !DILocation(line: 70, column: 2, scope: !224)
!478 = !DILocation(line: 71, column: 12, scope: !224)
!479 = !DILocation(line: 71, column: 19, scope: !224)
!480 = !DILocation(line: 71, column: 2, scope: !224)
!481 = !DILocation(line: 72, column: 2, scope: !224)
!482 = !DILocalVariable(name: "buf", arg: 1, scope: !225, file: !226, line: 255, type: !67)
!483 = !DILocation(line: 255, column: 20, scope: !225)
!484 = !DILocalVariable(name: "num", arg: 2, scope: !225, file: !226, line: 255, type: !155)
!485 = !DILocation(line: 255, column: 34, scope: !225)
!486 = !DILocation(line: 257, column: 21, scope: !225)
!487 = !DILocation(line: 257, column: 15, scope: !225)
!488 = !DILocation(line: 257, column: 2, scope: !225)
!489 = !DILocation(line: 257, column: 19, scope: !225)
!490 = !DILocation(line: 258, column: 2, scope: !225)
