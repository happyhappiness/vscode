; ModuleID = '/data/download/cmake/cmake-master/Utilities/cmliblzma/liblzma/common/filter_encoder.c'
target datalayout = "e-m:e-i64:64-f80:128-n8:16:32:64-S128"
target triple = "x86_64-unknown-linux-gnu"

%struct.lzma_filter_encoder = type { i64, i32 (%struct.lzma_next_coder_s*, %struct.lzma_allocator*, %struct.lzma_filter_info_s*)*, i64 (i8*)*, i64 (i8*)*, i32 (i32*, i8*)*, i32, i32 (i8*, i8*)* }
%struct.lzma_next_coder_s = type { %struct.lzma_coder_s*, i64, i64, i32 (%struct.lzma_coder_s*, %struct.lzma_allocator*, i8*, i64*, i64, i8*, i64*, i64, i32)*, void (%struct.lzma_coder_s*, %struct.lzma_allocator*)*, i32 (%struct.lzma_coder_s*)*, i32 (%struct.lzma_coder_s*, i64*, i64*, i64)*, i32 (%struct.lzma_coder_s*, %struct.lzma_allocator*, %struct.lzma_filter*, %struct.lzma_filter*)* }
%struct.lzma_coder_s = type opaque
%struct.lzma_filter = type { i64, i8* }
%struct.lzma_allocator = type { i8* (i8*, i64, i64)*, void (i8*, i8*)*, i8* }
%struct.lzma_filter_info_s = type { i64, {}*, i8* }
%struct.lzma_stream = type { i8*, i64, i64, i8*, i64, i64, %struct.lzma_allocator*, %struct.lzma_internal_s*, i8*, i8*, i8*, i8*, i64, i64, i64, i64, i32, i32 }
%struct.lzma_internal_s = type { %struct.lzma_next_coder_s, i32, i64, [4 x i8], i8 }
%struct.lzma_filter_coder = type { i64, i32 (%struct.lzma_next_coder_s*, %struct.lzma_allocator*, %struct.lzma_filter_info_s*)*, i64 (i8*)* }

@encoders = internal constant [9 x %struct.lzma_filter_encoder] [%struct.lzma_filter_encoder { i64 4611686018427387905, i32 (%struct.lzma_next_coder_s*, %struct.lzma_allocator*, %struct.lzma_filter_info_s*)* @lzma_lzma_encoder_init, i64 (i8*)* @lzma_lzma_encoder_memusage, i64 (i8*)* null, i32 (i32*, i8*)* null, i32 5, i32 (i8*, i8*)* @lzma_lzma_props_encode }, %struct.lzma_filter_encoder { i64 33, i32 (%struct.lzma_next_coder_s*, %struct.lzma_allocator*, %struct.lzma_filter_info_s*)* @lzma_lzma2_encoder_init, i64 (i8*)* @lzma_lzma2_encoder_memusage, i64 (i8*)* null, i32 (i32*, i8*)* null, i32 1, i32 (i8*, i8*)* @lzma_lzma2_props_encode }, %struct.lzma_filter_encoder { i64 4, i32 (%struct.lzma_next_coder_s*, %struct.lzma_allocator*, %struct.lzma_filter_info_s*)* @lzma_simple_x86_encoder_init, i64 (i8*)* null, i64 (i8*)* null, i32 (i32*, i8*)* @lzma_simple_props_size, i32 0, i32 (i8*, i8*)* @lzma_simple_props_encode }, %struct.lzma_filter_encoder { i64 5, i32 (%struct.lzma_next_coder_s*, %struct.lzma_allocator*, %struct.lzma_filter_info_s*)* @lzma_simple_powerpc_encoder_init, i64 (i8*)* null, i64 (i8*)* null, i32 (i32*, i8*)* @lzma_simple_props_size, i32 0, i32 (i8*, i8*)* @lzma_simple_props_encode }, %struct.lzma_filter_encoder { i64 6, i32 (%struct.lzma_next_coder_s*, %struct.lzma_allocator*, %struct.lzma_filter_info_s*)* @lzma_simple_ia64_encoder_init, i64 (i8*)* null, i64 (i8*)* null, i32 (i32*, i8*)* @lzma_simple_props_size, i32 0, i32 (i8*, i8*)* @lzma_simple_props_encode }, %struct.lzma_filter_encoder { i64 7, i32 (%struct.lzma_next_coder_s*, %struct.lzma_allocator*, %struct.lzma_filter_info_s*)* @lzma_simple_arm_encoder_init, i64 (i8*)* null, i64 (i8*)* null, i32 (i32*, i8*)* @lzma_simple_props_size, i32 0, i32 (i8*, i8*)* @lzma_simple_props_encode }, %struct.lzma_filter_encoder { i64 8, i32 (%struct.lzma_next_coder_s*, %struct.lzma_allocator*, %struct.lzma_filter_info_s*)* @lzma_simple_armthumb_encoder_init, i64 (i8*)* null, i64 (i8*)* null, i32 (i32*, i8*)* @lzma_simple_props_size, i32 0, i32 (i8*, i8*)* @lzma_simple_props_encode }, %struct.lzma_filter_encoder { i64 9, i32 (%struct.lzma_next_coder_s*, %struct.lzma_allocator*, %struct.lzma_filter_info_s*)* @lzma_simple_sparc_encoder_init, i64 (i8*)* null, i64 (i8*)* null, i32 (i32*, i8*)* @lzma_simple_props_size, i32 0, i32 (i8*, i8*)* @lzma_simple_props_encode }, %struct.lzma_filter_encoder { i64 3, i32 (%struct.lzma_next_coder_s*, %struct.lzma_allocator*, %struct.lzma_filter_info_s*)* @lzma_delta_encoder_init, i64 (i8*)* @lzma_delta_coder_memusage, i64 (i8*)* null, i32 (i32*, i8*)* null, i32 1, i32 (i8*, i8*)* @lzma_delta_props_encode }], align 16

; Function Attrs: nounwind readnone uwtable
define zeroext i8 @lzma_filter_encoder_is_supported(i64 %id) #0 !dbg !163 {
entry:
  %id.addr = alloca i64, align 8
  store i64 %id, i64* %id.addr, align 8
  call void @llvm.dbg.declare(metadata i64* %id.addr, metadata !244, metadata !245), !dbg !246
  %0 = load i64, i64* %id.addr, align 8, !dbg !247
  %call = call %struct.lzma_filter_encoder* @encoder_find(i64 %0), !dbg !248
  %cmp = icmp ne %struct.lzma_filter_encoder* %call, null, !dbg !249
  %conv = zext i1 %cmp to i32, !dbg !249
  %conv1 = trunc i32 %conv to i8, !dbg !248
  ret i8 %conv1, !dbg !250
}

; Function Attrs: nounwind readnone
declare void @llvm.dbg.declare(metadata, metadata, metadata) #1

; Function Attrs: nounwind uwtable
define internal %struct.lzma_filter_encoder* @encoder_find(i64 %id) #2 !dbg !212 {
entry:
  %retval = alloca %struct.lzma_filter_encoder*, align 8
  %id.addr = alloca i64, align 8
  %i = alloca i64, align 8
  store i64 %id, i64* %id.addr, align 8
  call void @llvm.dbg.declare(metadata i64* %id.addr, metadata !251, metadata !245), !dbg !252
  call void @llvm.dbg.declare(metadata i64* %i, metadata !253, metadata !245), !dbg !254
  store i64 0, i64* %i, align 8, !dbg !255
  br label %for.cond, !dbg !257

for.cond:                                         ; preds = %for.inc, %entry
  %0 = load i64, i64* %i, align 8, !dbg !258
  %cmp = icmp ult i64 %0, 9, !dbg !261
  br i1 %cmp, label %for.body, label %for.end, !dbg !262

for.body:                                         ; preds = %for.cond
  %1 = load i64, i64* %i, align 8, !dbg !263
  %arrayidx = getelementptr inbounds [9 x %struct.lzma_filter_encoder], [9 x %struct.lzma_filter_encoder]* @encoders, i64 0, i64 %1, !dbg !265
  %id1 = getelementptr inbounds %struct.lzma_filter_encoder, %struct.lzma_filter_encoder* %arrayidx, i32 0, i32 0, !dbg !266
  %2 = load i64, i64* %id1, align 8, !dbg !266
  %3 = load i64, i64* %id.addr, align 8, !dbg !267
  %cmp2 = icmp eq i64 %2, %3, !dbg !268
  br i1 %cmp2, label %if.then, label %if.end, !dbg !269

if.then:                                          ; preds = %for.body
  %4 = load i64, i64* %i, align 8, !dbg !270
  %add.ptr = getelementptr inbounds %struct.lzma_filter_encoder, %struct.lzma_filter_encoder* getelementptr inbounds ([9 x %struct.lzma_filter_encoder], [9 x %struct.lzma_filter_encoder]* @encoders, i32 0, i32 0), i64 %4, !dbg !271
  store %struct.lzma_filter_encoder* %add.ptr, %struct.lzma_filter_encoder** %retval, align 8, !dbg !272
  br label %return, !dbg !272

if.end:                                           ; preds = %for.body
  br label %for.inc, !dbg !273

for.inc:                                          ; preds = %if.end
  %5 = load i64, i64* %i, align 8, !dbg !275
  %inc = add i64 %5, 1, !dbg !275
  store i64 %inc, i64* %i, align 8, !dbg !275
  br label %for.cond, !dbg !277

for.end:                                          ; preds = %for.cond
  store %struct.lzma_filter_encoder* null, %struct.lzma_filter_encoder** %retval, align 8, !dbg !278
  br label %return, !dbg !278

return:                                           ; preds = %for.end, %if.then
  %6 = load %struct.lzma_filter_encoder*, %struct.lzma_filter_encoder** %retval, align 8, !dbg !279
  ret %struct.lzma_filter_encoder* %6, !dbg !279
}

; Function Attrs: nounwind uwtable
define i32 @lzma_filters_update(%struct.lzma_stream* %strm, %struct.lzma_filter* %filters) #2 !dbg !168 {
entry:
  %retval = alloca i32, align 4
  %strm.addr = alloca %struct.lzma_stream*, align 8
  %filters.addr = alloca %struct.lzma_filter*, align 8
  %i = alloca i64, align 8
  %count = alloca i64, align 8
  %reversed_filters = alloca [5 x %struct.lzma_filter], align 16
  store %struct.lzma_stream* %strm, %struct.lzma_stream** %strm.addr, align 8
  call void @llvm.dbg.declare(metadata %struct.lzma_stream** %strm.addr, metadata !280, metadata !245), !dbg !281
  store %struct.lzma_filter* %filters, %struct.lzma_filter** %filters.addr, align 8
  call void @llvm.dbg.declare(metadata %struct.lzma_filter** %filters.addr, metadata !282, metadata !245), !dbg !283
  call void @llvm.dbg.declare(metadata i64* %i, metadata !284, metadata !245), !dbg !285
  call void @llvm.dbg.declare(metadata i64* %count, metadata !286, metadata !245), !dbg !287
  store i64 1, i64* %count, align 8, !dbg !287
  call void @llvm.dbg.declare(metadata [5 x %struct.lzma_filter]* %reversed_filters, metadata !288, metadata !245), !dbg !292
  %0 = load %struct.lzma_stream*, %struct.lzma_stream** %strm.addr, align 8, !dbg !293
  %internal = getelementptr inbounds %struct.lzma_stream, %struct.lzma_stream* %0, i32 0, i32 7, !dbg !295
  %1 = load %struct.lzma_internal_s*, %struct.lzma_internal_s** %internal, align 8, !dbg !295
  %next = getelementptr inbounds %struct.lzma_internal_s, %struct.lzma_internal_s* %1, i32 0, i32 0, !dbg !296
  %update = getelementptr inbounds %struct.lzma_next_coder_s, %struct.lzma_next_coder_s* %next, i32 0, i32 7, !dbg !297
  %2 = load i32 (%struct.lzma_coder_s*, %struct.lzma_allocator*, %struct.lzma_filter*, %struct.lzma_filter*)*, i32 (%struct.lzma_coder_s*, %struct.lzma_allocator*, %struct.lzma_filter*, %struct.lzma_filter*)** %update, align 8, !dbg !297
  %cmp = icmp eq i32 (%struct.lzma_coder_s*, %struct.lzma_allocator*, %struct.lzma_filter*, %struct.lzma_filter*)* %2, null, !dbg !298
  br i1 %cmp, label %if.then, label %if.end, !dbg !299

if.then:                                          ; preds = %entry
  store i32 11, i32* %retval, align 4, !dbg !300
  br label %return, !dbg !300

if.end:                                           ; preds = %entry
  %3 = load %struct.lzma_filter*, %struct.lzma_filter** %filters.addr, align 8, !dbg !301
  %call = call i64 @lzma_raw_encoder_memusage(%struct.lzma_filter* %3) #7, !dbg !303
  %cmp1 = icmp eq i64 %call, -1, !dbg !304
  br i1 %cmp1, label %if.then2, label %if.end3, !dbg !305

if.then2:                                         ; preds = %if.end
  store i32 8, i32* %retval, align 4, !dbg !306
  br label %return, !dbg !306

if.end3:                                          ; preds = %if.end
  br label %while.cond, !dbg !307

while.cond:                                       ; preds = %while.body, %if.end3
  %4 = load i64, i64* %count, align 8, !dbg !308
  %5 = load %struct.lzma_filter*, %struct.lzma_filter** %filters.addr, align 8, !dbg !310
  %arrayidx = getelementptr inbounds %struct.lzma_filter, %struct.lzma_filter* %5, i64 %4, !dbg !310
  %id = getelementptr inbounds %struct.lzma_filter, %struct.lzma_filter* %arrayidx, i32 0, i32 0, !dbg !311
  %6 = load i64, i64* %id, align 8, !dbg !311
  %cmp4 = icmp ne i64 %6, -1, !dbg !312
  br i1 %cmp4, label %while.body, label %while.end, !dbg !313

while.body:                                       ; preds = %while.cond
  %7 = load i64, i64* %count, align 8, !dbg !314
  %inc = add i64 %7, 1, !dbg !314
  store i64 %inc, i64* %count, align 8, !dbg !314
  br label %while.cond, !dbg !315

while.end:                                        ; preds = %while.cond
  store i64 0, i64* %i, align 8, !dbg !317
  br label %for.cond, !dbg !319

for.cond:                                         ; preds = %for.inc, %while.end
  %8 = load i64, i64* %i, align 8, !dbg !320
  %9 = load i64, i64* %count, align 8, !dbg !323
  %cmp5 = icmp ult i64 %8, %9, !dbg !324
  br i1 %cmp5, label %for.body, label %for.end, !dbg !325

for.body:                                         ; preds = %for.cond
  %10 = load i64, i64* %count, align 8, !dbg !326
  %11 = load i64, i64* %i, align 8, !dbg !327
  %sub = sub i64 %10, %11, !dbg !328
  %sub6 = sub i64 %sub, 1, !dbg !329
  %arrayidx7 = getelementptr inbounds [5 x %struct.lzma_filter], [5 x %struct.lzma_filter]* %reversed_filters, i64 0, i64 %sub6, !dbg !330
  %12 = load i64, i64* %i, align 8, !dbg !331
  %13 = load %struct.lzma_filter*, %struct.lzma_filter** %filters.addr, align 8, !dbg !332
  %arrayidx8 = getelementptr inbounds %struct.lzma_filter, %struct.lzma_filter* %13, i64 %12, !dbg !332
  %14 = bitcast %struct.lzma_filter* %arrayidx7 to i8*, !dbg !332
  %15 = bitcast %struct.lzma_filter* %arrayidx8 to i8*, !dbg !332
  call void @llvm.memcpy.p0i8.p0i8.i64(i8* %14, i8* %15, i64 16, i32 8, i1 false), !dbg !332
  br label %for.inc, !dbg !330

for.inc:                                          ; preds = %for.body
  %16 = load i64, i64* %i, align 8, !dbg !333
  %inc9 = add i64 %16, 1, !dbg !333
  store i64 %inc9, i64* %i, align 8, !dbg !333
  br label %for.cond, !dbg !335

for.end:                                          ; preds = %for.cond
  %17 = load i64, i64* %count, align 8, !dbg !336
  %arrayidx10 = getelementptr inbounds [5 x %struct.lzma_filter], [5 x %struct.lzma_filter]* %reversed_filters, i64 0, i64 %17, !dbg !337
  %id11 = getelementptr inbounds %struct.lzma_filter, %struct.lzma_filter* %arrayidx10, i32 0, i32 0, !dbg !338
  store i64 -1, i64* %id11, align 16, !dbg !339
  %18 = load %struct.lzma_stream*, %struct.lzma_stream** %strm.addr, align 8, !dbg !340
  %internal12 = getelementptr inbounds %struct.lzma_stream, %struct.lzma_stream* %18, i32 0, i32 7, !dbg !341
  %19 = load %struct.lzma_internal_s*, %struct.lzma_internal_s** %internal12, align 8, !dbg !341
  %next13 = getelementptr inbounds %struct.lzma_internal_s, %struct.lzma_internal_s* %19, i32 0, i32 0, !dbg !342
  %update14 = getelementptr inbounds %struct.lzma_next_coder_s, %struct.lzma_next_coder_s* %next13, i32 0, i32 7, !dbg !343
  %20 = load i32 (%struct.lzma_coder_s*, %struct.lzma_allocator*, %struct.lzma_filter*, %struct.lzma_filter*)*, i32 (%struct.lzma_coder_s*, %struct.lzma_allocator*, %struct.lzma_filter*, %struct.lzma_filter*)** %update14, align 8, !dbg !343
  %21 = load %struct.lzma_stream*, %struct.lzma_stream** %strm.addr, align 8, !dbg !344
  %internal15 = getelementptr inbounds %struct.lzma_stream, %struct.lzma_stream* %21, i32 0, i32 7, !dbg !345
  %22 = load %struct.lzma_internal_s*, %struct.lzma_internal_s** %internal15, align 8, !dbg !345
  %next16 = getelementptr inbounds %struct.lzma_internal_s, %struct.lzma_internal_s* %22, i32 0, i32 0, !dbg !346
  %coder = getelementptr inbounds %struct.lzma_next_coder_s, %struct.lzma_next_coder_s* %next16, i32 0, i32 0, !dbg !347
  %23 = load %struct.lzma_coder_s*, %struct.lzma_coder_s** %coder, align 8, !dbg !347
  %24 = load %struct.lzma_stream*, %struct.lzma_stream** %strm.addr, align 8, !dbg !348
  %allocator = getelementptr inbounds %struct.lzma_stream, %struct.lzma_stream* %24, i32 0, i32 6, !dbg !349
  %25 = load %struct.lzma_allocator*, %struct.lzma_allocator** %allocator, align 8, !dbg !349
  %26 = load %struct.lzma_filter*, %struct.lzma_filter** %filters.addr, align 8, !dbg !350
  %arraydecay = getelementptr inbounds [5 x %struct.lzma_filter], [5 x %struct.lzma_filter]* %reversed_filters, i32 0, i32 0, !dbg !351
  %call17 = call i32 %20(%struct.lzma_coder_s* %23, %struct.lzma_allocator* %25, %struct.lzma_filter* %26, %struct.lzma_filter* %arraydecay), !dbg !340
  store i32 %call17, i32* %retval, align 4, !dbg !352
  br label %return, !dbg !352

return:                                           ; preds = %for.end, %if.then2, %if.then
  %27 = load i32, i32* %retval, align 4, !dbg !353
  ret i32 %27, !dbg !353
}

; Function Attrs: nounwind readonly uwtable
define i64 @lzma_raw_encoder_memusage(%struct.lzma_filter* %filters) #3 !dbg !200 {
entry:
  %filters.addr = alloca %struct.lzma_filter*, align 8
  store %struct.lzma_filter* %filters, %struct.lzma_filter** %filters.addr, align 8
  call void @llvm.dbg.declare(metadata %struct.lzma_filter** %filters.addr, metadata !354, metadata !245), !dbg !355
  %0 = load %struct.lzma_filter*, %struct.lzma_filter** %filters.addr, align 8, !dbg !356
  %call = call i64 @lzma_raw_coder_memusage(%struct.lzma_filter_coder* (i64)* bitcast (%struct.lzma_filter_encoder* (i64)* @encoder_find to %struct.lzma_filter_coder* (i64)*), %struct.lzma_filter* %0), !dbg !357
  ret i64 %call, !dbg !358
}

; Function Attrs: argmemonly nounwind
declare void @llvm.memcpy.p0i8.p0i8.i64(i8* nocapture, i8* nocapture readonly, i64, i32, i1) #4

; Function Attrs: nounwind uwtable
define i32 @lzma_raw_encoder_init(%struct.lzma_next_coder_s* %next, %struct.lzma_allocator* %allocator, %struct.lzma_filter* %options) #2 !dbg !196 {
entry:
  %next.addr = alloca %struct.lzma_next_coder_s*, align 8
  %allocator.addr = alloca %struct.lzma_allocator*, align 8
  %options.addr = alloca %struct.lzma_filter*, align 8
  store %struct.lzma_next_coder_s* %next, %struct.lzma_next_coder_s** %next.addr, align 8
  call void @llvm.dbg.declare(metadata %struct.lzma_next_coder_s** %next.addr, metadata !359, metadata !245), !dbg !360
  store %struct.lzma_allocator* %allocator, %struct.lzma_allocator** %allocator.addr, align 8
  call void @llvm.dbg.declare(metadata %struct.lzma_allocator** %allocator.addr, metadata !361, metadata !245), !dbg !362
  store %struct.lzma_filter* %options, %struct.lzma_filter** %options.addr, align 8
  call void @llvm.dbg.declare(metadata %struct.lzma_filter** %options.addr, metadata !363, metadata !245), !dbg !364
  %0 = load %struct.lzma_next_coder_s*, %struct.lzma_next_coder_s** %next.addr, align 8, !dbg !365
  %1 = load %struct.lzma_allocator*, %struct.lzma_allocator** %allocator.addr, align 8, !dbg !366
  %2 = load %struct.lzma_filter*, %struct.lzma_filter** %options.addr, align 8, !dbg !367
  %call = call i32 @lzma_raw_coder_init(%struct.lzma_next_coder_s* %0, %struct.lzma_allocator* %1, %struct.lzma_filter* %2, %struct.lzma_filter_coder* (i64)* bitcast (%struct.lzma_filter_encoder* (i64)* @encoder_find to %struct.lzma_filter_coder* (i64)*), i1 zeroext true), !dbg !368
  ret i32 %call, !dbg !369
}

declare i32 @lzma_raw_coder_init(%struct.lzma_next_coder_s*, %struct.lzma_allocator*, %struct.lzma_filter*, %struct.lzma_filter_coder* (i64)*, i1 zeroext) #5

; Function Attrs: nounwind uwtable
define i32 @lzma_raw_encoder(%struct.lzma_stream* %strm, %struct.lzma_filter* %options) #2 !dbg !199 {
entry:
  %retval = alloca i32, align 4
  %strm.addr = alloca %struct.lzma_stream*, align 8
  %options.addr = alloca %struct.lzma_filter*, align 8
  %ret_ = alloca i32, align 4
  %ret_2 = alloca i32, align 4
  store %struct.lzma_stream* %strm, %struct.lzma_stream** %strm.addr, align 8
  call void @llvm.dbg.declare(metadata %struct.lzma_stream** %strm.addr, metadata !370, metadata !245), !dbg !371
  store %struct.lzma_filter* %options, %struct.lzma_filter** %options.addr, align 8
  call void @llvm.dbg.declare(metadata %struct.lzma_filter** %options.addr, metadata !372, metadata !245), !dbg !373
  br label %do.body, !dbg !374

do.body:                                          ; preds = %entry
  call void @llvm.dbg.declare(metadata i32* %ret_, metadata !375, metadata !245), !dbg !377
  br label %do.body1, !dbg !378

do.body1:                                         ; preds = %do.body
  call void @llvm.dbg.declare(metadata i32* %ret_2, metadata !380, metadata !245), !dbg !383
  %0 = load %struct.lzma_stream*, %struct.lzma_stream** %strm.addr, align 8, !dbg !384
  %call = call i32 @lzma_strm_init(%struct.lzma_stream* %0), !dbg !384
  store i32 %call, i32* %ret_2, align 4, !dbg !384
  %1 = load i32, i32* %ret_2, align 4, !dbg !384
  %cmp = icmp ne i32 %1, 0, !dbg !384
  br i1 %cmp, label %if.then, label %if.end, !dbg !384

if.then:                                          ; preds = %do.body1
  %2 = load i32, i32* %ret_2, align 4, !dbg !386
  store i32 %2, i32* %retval, align 4, !dbg !386
  br label %return, !dbg !386

if.end:                                           ; preds = %do.body1
  br label %do.end, !dbg !389

do.end:                                           ; preds = %if.end
  %3 = load %struct.lzma_stream*, %struct.lzma_stream** %strm.addr, align 8, !dbg !391
  %internal = getelementptr inbounds %struct.lzma_stream, %struct.lzma_stream* %3, i32 0, i32 7, !dbg !391
  %4 = load %struct.lzma_internal_s*, %struct.lzma_internal_s** %internal, align 8, !dbg !391
  %next = getelementptr inbounds %struct.lzma_internal_s, %struct.lzma_internal_s* %4, i32 0, i32 0, !dbg !391
  %5 = load %struct.lzma_stream*, %struct.lzma_stream** %strm.addr, align 8, !dbg !391
  %allocator = getelementptr inbounds %struct.lzma_stream, %struct.lzma_stream* %5, i32 0, i32 6, !dbg !391
  %6 = load %struct.lzma_allocator*, %struct.lzma_allocator** %allocator, align 8, !dbg !391
  %7 = load %struct.lzma_filter*, %struct.lzma_filter** %options.addr, align 8, !dbg !391
  %call3 = call i32 @lzma_raw_coder_init(%struct.lzma_next_coder_s* %next, %struct.lzma_allocator* %6, %struct.lzma_filter* %7, %struct.lzma_filter_coder* (i64)* bitcast (%struct.lzma_filter_encoder* (i64)* @encoder_find to %struct.lzma_filter_coder* (i64)*), i1 zeroext true), !dbg !391
  store i32 %call3, i32* %ret_, align 4, !dbg !391
  %8 = load i32, i32* %ret_, align 4, !dbg !391
  %cmp4 = icmp ne i32 %8, 0, !dbg !391
  br i1 %cmp4, label %if.then5, label %if.end6, !dbg !391

if.then5:                                         ; preds = %do.end
  %9 = load %struct.lzma_stream*, %struct.lzma_stream** %strm.addr, align 8, !dbg !393
  call void @lzma_end(%struct.lzma_stream* %9) #8, !dbg !393
  %10 = load i32, i32* %ret_, align 4, !dbg !393
  store i32 %10, i32* %retval, align 4, !dbg !393
  br label %return, !dbg !393

if.end6:                                          ; preds = %do.end
  br label %do.end7, !dbg !397

do.end7:                                          ; preds = %if.end6
  %11 = load %struct.lzma_stream*, %struct.lzma_stream** %strm.addr, align 8, !dbg !399
  %internal8 = getelementptr inbounds %struct.lzma_stream, %struct.lzma_stream* %11, i32 0, i32 7, !dbg !400
  %12 = load %struct.lzma_internal_s*, %struct.lzma_internal_s** %internal8, align 8, !dbg !400
  %supported_actions = getelementptr inbounds %struct.lzma_internal_s, %struct.lzma_internal_s* %12, i32 0, i32 3, !dbg !401
  %arrayidx = getelementptr inbounds [4 x i8], [4 x i8]* %supported_actions, i64 0, i64 0, !dbg !399
  store i8 1, i8* %arrayidx, align 8, !dbg !402
  %13 = load %struct.lzma_stream*, %struct.lzma_stream** %strm.addr, align 8, !dbg !403
  %internal9 = getelementptr inbounds %struct.lzma_stream, %struct.lzma_stream* %13, i32 0, i32 7, !dbg !404
  %14 = load %struct.lzma_internal_s*, %struct.lzma_internal_s** %internal9, align 8, !dbg !404
  %supported_actions10 = getelementptr inbounds %struct.lzma_internal_s, %struct.lzma_internal_s* %14, i32 0, i32 3, !dbg !405
  %arrayidx11 = getelementptr inbounds [4 x i8], [4 x i8]* %supported_actions10, i64 0, i64 1, !dbg !403
  store i8 1, i8* %arrayidx11, align 1, !dbg !406
  %15 = load %struct.lzma_stream*, %struct.lzma_stream** %strm.addr, align 8, !dbg !407
  %internal12 = getelementptr inbounds %struct.lzma_stream, %struct.lzma_stream* %15, i32 0, i32 7, !dbg !408
  %16 = load %struct.lzma_internal_s*, %struct.lzma_internal_s** %internal12, align 8, !dbg !408
  %supported_actions13 = getelementptr inbounds %struct.lzma_internal_s, %struct.lzma_internal_s* %16, i32 0, i32 3, !dbg !409
  %arrayidx14 = getelementptr inbounds [4 x i8], [4 x i8]* %supported_actions13, i64 0, i64 3, !dbg !407
  store i8 1, i8* %arrayidx14, align 1, !dbg !410
  store i32 0, i32* %retval, align 4, !dbg !411
  br label %return, !dbg !411

return:                                           ; preds = %do.end7, %if.then5, %if.then
  %17 = load i32, i32* %retval, align 4, !dbg !412
  ret i32 %17, !dbg !412
}

declare i32 @lzma_strm_init(%struct.lzma_stream*) #5

; Function Attrs: nounwind
declare void @lzma_end(%struct.lzma_stream*) #6

declare i64 @lzma_raw_coder_memusage(%struct.lzma_filter_coder* (i64)*, %struct.lzma_filter*) #5

; Function Attrs: nounwind uwtable
define i32 @lzma_properties_size(i32* %size, %struct.lzma_filter* %filter) #2 !dbg !203 {
entry:
  %retval = alloca i32, align 4
  %size.addr = alloca i32*, align 8
  %filter.addr = alloca %struct.lzma_filter*, align 8
  %fe = alloca %struct.lzma_filter_encoder*, align 8
  store i32* %size, i32** %size.addr, align 8
  call void @llvm.dbg.declare(metadata i32** %size.addr, metadata !413, metadata !245), !dbg !414
  store %struct.lzma_filter* %filter, %struct.lzma_filter** %filter.addr, align 8
  call void @llvm.dbg.declare(metadata %struct.lzma_filter** %filter.addr, metadata !415, metadata !245), !dbg !416
  call void @llvm.dbg.declare(metadata %struct.lzma_filter_encoder** %fe, metadata !417, metadata !245), !dbg !419
  %0 = load %struct.lzma_filter*, %struct.lzma_filter** %filter.addr, align 8, !dbg !420
  %id = getelementptr inbounds %struct.lzma_filter, %struct.lzma_filter* %0, i32 0, i32 0, !dbg !421
  %1 = load i64, i64* %id, align 8, !dbg !421
  %call = call %struct.lzma_filter_encoder* @encoder_find(i64 %1), !dbg !422
  store %struct.lzma_filter_encoder* %call, %struct.lzma_filter_encoder** %fe, align 8, !dbg !419
  %2 = load %struct.lzma_filter_encoder*, %struct.lzma_filter_encoder** %fe, align 8, !dbg !423
  %cmp = icmp eq %struct.lzma_filter_encoder* %2, null, !dbg !425
  br i1 %cmp, label %if.then, label %if.end, !dbg !426

if.then:                                          ; preds = %entry
  %3 = load %struct.lzma_filter*, %struct.lzma_filter** %filter.addr, align 8, !dbg !427
  %id1 = getelementptr inbounds %struct.lzma_filter, %struct.lzma_filter* %3, i32 0, i32 0, !dbg !429
  %4 = load i64, i64* %id1, align 8, !dbg !429
  %cmp2 = icmp ule i64 %4, 9223372036854775807, !dbg !430
  %cond = select i1 %cmp2, i32 8, i32 11, !dbg !427
  store i32 %cond, i32* %retval, align 4, !dbg !431
  br label %return, !dbg !431

if.end:                                           ; preds = %entry
  %5 = load %struct.lzma_filter_encoder*, %struct.lzma_filter_encoder** %fe, align 8, !dbg !432
  %props_size_get = getelementptr inbounds %struct.lzma_filter_encoder, %struct.lzma_filter_encoder* %5, i32 0, i32 4, !dbg !434
  %6 = load i32 (i32*, i8*)*, i32 (i32*, i8*)** %props_size_get, align 8, !dbg !434
  %cmp3 = icmp eq i32 (i32*, i8*)* %6, null, !dbg !435
  br i1 %cmp3, label %if.then4, label %if.end5, !dbg !436

if.then4:                                         ; preds = %if.end
  %7 = load %struct.lzma_filter_encoder*, %struct.lzma_filter_encoder** %fe, align 8, !dbg !437
  %props_size_fixed = getelementptr inbounds %struct.lzma_filter_encoder, %struct.lzma_filter_encoder* %7, i32 0, i32 5, !dbg !439
  %8 = load i32, i32* %props_size_fixed, align 8, !dbg !439
  %9 = load i32*, i32** %size.addr, align 8, !dbg !440
  store i32 %8, i32* %9, align 4, !dbg !441
  store i32 0, i32* %retval, align 4, !dbg !442
  br label %return, !dbg !442

if.end5:                                          ; preds = %if.end
  %10 = load %struct.lzma_filter_encoder*, %struct.lzma_filter_encoder** %fe, align 8, !dbg !443
  %props_size_get6 = getelementptr inbounds %struct.lzma_filter_encoder, %struct.lzma_filter_encoder* %10, i32 0, i32 4, !dbg !444
  %11 = load i32 (i32*, i8*)*, i32 (i32*, i8*)** %props_size_get6, align 8, !dbg !444
  %12 = load i32*, i32** %size.addr, align 8, !dbg !445
  %13 = load %struct.lzma_filter*, %struct.lzma_filter** %filter.addr, align 8, !dbg !446
  %options = getelementptr inbounds %struct.lzma_filter, %struct.lzma_filter* %13, i32 0, i32 1, !dbg !447
  %14 = load i8*, i8** %options, align 8, !dbg !447
  %call7 = call i32 %11(i32* %12, i8* %14), !dbg !443
  store i32 %call7, i32* %retval, align 4, !dbg !448
  br label %return, !dbg !448

return:                                           ; preds = %if.end5, %if.then4, %if.then
  %15 = load i32, i32* %retval, align 4, !dbg !449
  ret i32 %15, !dbg !449
}

; Function Attrs: nounwind uwtable
define i32 @lzma_properties_encode(%struct.lzma_filter* %filter, i8* %props) #2 !dbg !209 {
entry:
  %retval = alloca i32, align 4
  %filter.addr = alloca %struct.lzma_filter*, align 8
  %props.addr = alloca i8*, align 8
  %fe = alloca %struct.lzma_filter_encoder*, align 8
  store %struct.lzma_filter* %filter, %struct.lzma_filter** %filter.addr, align 8
  call void @llvm.dbg.declare(metadata %struct.lzma_filter** %filter.addr, metadata !450, metadata !245), !dbg !451
  store i8* %props, i8** %props.addr, align 8
  call void @llvm.dbg.declare(metadata i8** %props.addr, metadata !452, metadata !245), !dbg !453
  call void @llvm.dbg.declare(metadata %struct.lzma_filter_encoder** %fe, metadata !454, metadata !245), !dbg !455
  %0 = load %struct.lzma_filter*, %struct.lzma_filter** %filter.addr, align 8, !dbg !456
  %id = getelementptr inbounds %struct.lzma_filter, %struct.lzma_filter* %0, i32 0, i32 0, !dbg !457
  %1 = load i64, i64* %id, align 8, !dbg !457
  %call = call %struct.lzma_filter_encoder* @encoder_find(i64 %1), !dbg !458
  store %struct.lzma_filter_encoder* %call, %struct.lzma_filter_encoder** %fe, align 8, !dbg !455
  %2 = load %struct.lzma_filter_encoder*, %struct.lzma_filter_encoder** %fe, align 8, !dbg !459
  %cmp = icmp eq %struct.lzma_filter_encoder* %2, null, !dbg !461
  br i1 %cmp, label %if.then, label %if.end, !dbg !462

if.then:                                          ; preds = %entry
  store i32 11, i32* %retval, align 4, !dbg !463
  br label %return, !dbg !463

if.end:                                           ; preds = %entry
  %3 = load %struct.lzma_filter_encoder*, %struct.lzma_filter_encoder** %fe, align 8, !dbg !464
  %props_encode = getelementptr inbounds %struct.lzma_filter_encoder, %struct.lzma_filter_encoder* %3, i32 0, i32 6, !dbg !466
  %4 = load i32 (i8*, i8*)*, i32 (i8*, i8*)** %props_encode, align 8, !dbg !466
  %cmp1 = icmp eq i32 (i8*, i8*)* %4, null, !dbg !467
  br i1 %cmp1, label %if.then2, label %if.end3, !dbg !468

if.then2:                                         ; preds = %if.end
  store i32 0, i32* %retval, align 4, !dbg !469
  br label %return, !dbg !469

if.end3:                                          ; preds = %if.end
  %5 = load %struct.lzma_filter_encoder*, %struct.lzma_filter_encoder** %fe, align 8, !dbg !470
  %props_encode4 = getelementptr inbounds %struct.lzma_filter_encoder, %struct.lzma_filter_encoder* %5, i32 0, i32 6, !dbg !471
  %6 = load i32 (i8*, i8*)*, i32 (i8*, i8*)** %props_encode4, align 8, !dbg !471
  %7 = load %struct.lzma_filter*, %struct.lzma_filter** %filter.addr, align 8, !dbg !472
  %options = getelementptr inbounds %struct.lzma_filter, %struct.lzma_filter* %7, i32 0, i32 1, !dbg !473
  %8 = load i8*, i8** %options, align 8, !dbg !473
  %9 = load i8*, i8** %props.addr, align 8, !dbg !474
  %call5 = call i32 %6(i8* %8, i8* %9), !dbg !470
  store i32 %call5, i32* %retval, align 4, !dbg !475
  br label %return, !dbg !475

return:                                           ; preds = %if.end3, %if.then2, %if.then
  %10 = load i32, i32* %retval, align 4, !dbg !476
  ret i32 %10, !dbg !476
}

declare i32 @lzma_lzma_encoder_init(%struct.lzma_next_coder_s*, %struct.lzma_allocator*, %struct.lzma_filter_info_s*) #5

declare i64 @lzma_lzma_encoder_memusage(i8*) #5

declare i32 @lzma_lzma_props_encode(i8*, i8*) #5

declare i32 @lzma_lzma2_encoder_init(%struct.lzma_next_coder_s*, %struct.lzma_allocator*, %struct.lzma_filter_info_s*) #5

declare i64 @lzma_lzma2_encoder_memusage(i8*) #5

declare i32 @lzma_lzma2_props_encode(i8*, i8*) #5

declare i32 @lzma_simple_x86_encoder_init(%struct.lzma_next_coder_s*, %struct.lzma_allocator*, %struct.lzma_filter_info_s*) #5

declare i32 @lzma_simple_props_size(i32*, i8*) #5

declare i32 @lzma_simple_props_encode(i8*, i8*) #5

declare i32 @lzma_simple_powerpc_encoder_init(%struct.lzma_next_coder_s*, %struct.lzma_allocator*, %struct.lzma_filter_info_s*) #5

declare i32 @lzma_simple_ia64_encoder_init(%struct.lzma_next_coder_s*, %struct.lzma_allocator*, %struct.lzma_filter_info_s*) #5

declare i32 @lzma_simple_arm_encoder_init(%struct.lzma_next_coder_s*, %struct.lzma_allocator*, %struct.lzma_filter_info_s*) #5

declare i32 @lzma_simple_armthumb_encoder_init(%struct.lzma_next_coder_s*, %struct.lzma_allocator*, %struct.lzma_filter_info_s*) #5

declare i32 @lzma_simple_sparc_encoder_init(%struct.lzma_next_coder_s*, %struct.lzma_allocator*, %struct.lzma_filter_info_s*) #5

declare i32 @lzma_delta_encoder_init(%struct.lzma_next_coder_s*, %struct.lzma_allocator*, %struct.lzma_filter_info_s*) #5

declare i64 @lzma_delta_coder_memusage(i8*) #5

declare i32 @lzma_delta_props_encode(i8*, i8*) #5

attributes #0 = { nounwind readnone uwtable "disable-tail-calls"="false" "less-precise-fpmad"="false" "no-frame-pointer-elim"="true" "no-frame-pointer-elim-non-leaf" "no-infs-fp-math"="false" "no-nans-fp-math"="false" "stack-protector-buffer-size"="8" "target-cpu"="x86-64" "target-features"="+fxsr,+mmx,+sse,+sse2" "unsafe-fp-math"="false" "use-soft-float"="false" }
attributes #1 = { nounwind readnone }
attributes #2 = { nounwind uwtable "disable-tail-calls"="false" "less-precise-fpmad"="false" "no-frame-pointer-elim"="true" "no-frame-pointer-elim-non-leaf" "no-infs-fp-math"="false" "no-nans-fp-math"="false" "stack-protector-buffer-size"="8" "target-cpu"="x86-64" "target-features"="+fxsr,+mmx,+sse,+sse2" "unsafe-fp-math"="false" "use-soft-float"="false" }
attributes #3 = { nounwind readonly uwtable "disable-tail-calls"="false" "less-precise-fpmad"="false" "no-frame-pointer-elim"="true" "no-frame-pointer-elim-non-leaf" "no-infs-fp-math"="false" "no-nans-fp-math"="false" "stack-protector-buffer-size"="8" "target-cpu"="x86-64" "target-features"="+fxsr,+mmx,+sse,+sse2" "unsafe-fp-math"="false" "use-soft-float"="false" }
attributes #4 = { argmemonly nounwind }
attributes #5 = { "disable-tail-calls"="false" "less-precise-fpmad"="false" "no-frame-pointer-elim"="true" "no-frame-pointer-elim-non-leaf" "no-infs-fp-math"="false" "no-nans-fp-math"="false" "stack-protector-buffer-size"="8" "target-cpu"="x86-64" "target-features"="+fxsr,+mmx,+sse,+sse2" "unsafe-fp-math"="false" "use-soft-float"="false" }
attributes #6 = { nounwind "disable-tail-calls"="false" "less-precise-fpmad"="false" "no-frame-pointer-elim"="true" "no-frame-pointer-elim-non-leaf" "no-infs-fp-math"="false" "no-nans-fp-math"="false" "stack-protector-buffer-size"="8" "target-cpu"="x86-64" "target-features"="+fxsr,+mmx,+sse,+sse2" "unsafe-fp-math"="false" "use-soft-float"="false" }
attributes #7 = { nounwind readonly }
attributes #8 = { nounwind }

!llvm.dbg.cu = !{!0}
!llvm.module.flags = !{!241, !242}
!llvm.ident = !{!243}

!0 = distinct !DICompileUnit(language: DW_LANG_C99, file: !1, producer: "clang version 3.8.0 (tags/RELEASE_380/final)", isOptimized: false, runtimeVersion: 0, emissionKind: 1, enums: !2, retainedTypes: !130, subprograms: !162, globals: !236)
!1 = !DIFile(filename: "/data/download/cmake/cmake-master/Utilities/cmliblzma/liblzma/common/filter_encoder.c", directory: "/data/download/cmake/cmake-master/Utilities/cmliblzma")
!2 = !{!3, !18, !24, !31, !127}
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
!31 = !DICompositeType(tag: DW_TAG_enumeration_type, scope: !33, file: !32, line: 182, size: 32, align: 32, elements: !120)
!32 = !DIFile(filename: "/data/download/cmake/cmake-master/Utilities/cmliblzma/liblzma/common/common.h", directory: "/data/download/cmake/cmake-master/Utilities/cmliblzma")
!33 = !DICompositeType(tag: DW_TAG_structure_type, name: "lzma_internal_s", file: !32, line: 174, size: 704, align: 64, elements: !34)
!34 = !{!35, !112, !113, !114, !119}
!35 = !DIDerivedType(tag: DW_TAG_member, name: "next", scope: !33, file: !32, line: 176, baseType: !36, size: 512, align: 64)
!36 = !DIDerivedType(tag: DW_TAG_typedef, name: "lzma_next_coder", file: !32, line: 75, baseType: !37)
!37 = !DICompositeType(tag: DW_TAG_structure_type, name: "lzma_next_coder_s", file: !32, line: 119, size: 512, align: 64, elements: !38)
!38 = !{!39, !43, !49, !51, !83, !88, !95, !100}
!39 = !DIDerivedType(tag: DW_TAG_member, name: "coder", scope: !37, file: !32, line: 121, baseType: !40, size: 64, align: 64)
!40 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !41, size: 64, align: 64)
!41 = !DIDerivedType(tag: DW_TAG_typedef, name: "lzma_coder", file: !32, line: 73, baseType: !42)
!42 = !DICompositeType(tag: DW_TAG_structure_type, name: "lzma_coder_s", file: !32, line: 73, flags: DIFlagFwdDecl)
!43 = !DIDerivedType(tag: DW_TAG_member, name: "id", scope: !37, file: !32, line: 125, baseType: !44, size: 64, align: 64, offset: 64)
!44 = !DIDerivedType(tag: DW_TAG_typedef, name: "lzma_vli", file: !45, line: 63, baseType: !46)
!45 = !DIFile(filename: "/data/download/cmake/cmake-master/Utilities/cmliblzma/liblzma/api/lzma/vli.h", directory: "/data/download/cmake/cmake-master/Utilities/cmliblzma")
!46 = !DIDerivedType(tag: DW_TAG_typedef, name: "uint64_t", file: !47, line: 55, baseType: !48)
!47 = !DIFile(filename: "/usr/include/stdint.h", directory: "/data/download/cmake/cmake-master/Utilities/cmliblzma")
!48 = !DIBasicType(name: "long unsigned int", size: 64, align: 64, encoding: DW_ATE_unsigned)
!49 = !DIDerivedType(tag: DW_TAG_member, name: "init", scope: !37, file: !32, line: 131, baseType: !50, size: 64, align: 64, offset: 128)
!50 = !DIDerivedType(tag: DW_TAG_typedef, name: "uintptr_t", file: !47, line: 122, baseType: !48)
!51 = !DIDerivedType(tag: DW_TAG_member, name: "code", scope: !37, file: !32, line: 134, baseType: !52, size: 64, align: 64, offset: 192)
!52 = !DIDerivedType(tag: DW_TAG_typedef, name: "lzma_code_function", file: !32, line: 89, baseType: !53)
!53 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !54, size: 64, align: 64)
!54 = !DISubroutineType(types: !55)
!55 = !{!56, !40, !57, !73, !78, !66, !80, !78, !66, !82}
!56 = !DIDerivedType(tag: DW_TAG_typedef, name: "lzma_ret", file: !4, line: 237, baseType: !3)
!57 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !58, size: 64, align: 64)
!58 = !DIDerivedType(tag: DW_TAG_typedef, name: "lzma_allocator", file: !4, line: 403, baseType: !59)
!59 = !DICompositeType(tag: DW_TAG_structure_type, file: !4, line: 341, size: 192, align: 64, elements: !60)
!60 = !{!61, !68, !72}
!61 = !DIDerivedType(tag: DW_TAG_member, name: "alloc", scope: !59, file: !4, line: 376, baseType: !62, size: 64, align: 64)
!62 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !63, size: 64, align: 64)
!63 = !DISubroutineType(types: !64)
!64 = !{!65, !65, !66, !66}
!65 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: null, size: 64, align: 64)
!66 = !DIDerivedType(tag: DW_TAG_typedef, name: "size_t", file: !67, line: 62, baseType: !48)
!67 = !DIFile(filename: "/opt/llvm-build/bin/../lib/clang/3.8.0/include/stddef.h", directory: "/data/download/cmake/cmake-master/Utilities/cmliblzma")
!68 = !DIDerivedType(tag: DW_TAG_member, name: "free", scope: !59, file: !4, line: 390, baseType: !69, size: 64, align: 64, offset: 64)
!69 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !70, size: 64, align: 64)
!70 = !DISubroutineType(types: !71)
!71 = !{null, !65, !65}
!72 = !DIDerivedType(tag: DW_TAG_member, name: "opaque", scope: !59, file: !4, line: 401, baseType: !65, size: 64, align: 64, offset: 128)
!73 = !DIDerivedType(tag: DW_TAG_restrict_type, baseType: !74)
!74 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !75, size: 64, align: 64)
!75 = !DIDerivedType(tag: DW_TAG_const_type, baseType: !76)
!76 = !DIDerivedType(tag: DW_TAG_typedef, name: "uint8_t", file: !47, line: 48, baseType: !77)
!77 = !DIBasicType(name: "unsigned char", size: 8, align: 8, encoding: DW_ATE_unsigned_char)
!78 = !DIDerivedType(tag: DW_TAG_restrict_type, baseType: !79)
!79 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !66, size: 64, align: 64)
!80 = !DIDerivedType(tag: DW_TAG_restrict_type, baseType: !81)
!81 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !76, size: 64, align: 64)
!82 = !DIDerivedType(tag: DW_TAG_typedef, name: "lzma_action", file: !4, line: 322, baseType: !18)
!83 = !DIDerivedType(tag: DW_TAG_member, name: "end", scope: !37, file: !32, line: 139, baseType: !84, size: 64, align: 64, offset: 256)
!84 = !DIDerivedType(tag: DW_TAG_typedef, name: "lzma_end_function", file: !32, line: 97, baseType: !85)
!85 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !86, size: 64, align: 64)
!86 = !DISubroutineType(types: !87)
!87 = !{null, !40, !57}
!88 = !DIDerivedType(tag: DW_TAG_member, name: "get_check", scope: !37, file: !32, line: 143, baseType: !89, size: 64, align: 64, offset: 320)
!89 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !90, size: 64, align: 64)
!90 = !DISubroutineType(types: !91)
!91 = !{!92, !93}
!92 = !DIDerivedType(tag: DW_TAG_typedef, name: "lzma_check", file: !25, line: 55, baseType: !24)
!93 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !94, size: 64, align: 64)
!94 = !DIDerivedType(tag: DW_TAG_const_type, baseType: !41)
!95 = !DIDerivedType(tag: DW_TAG_member, name: "memconfig", scope: !37, file: !32, line: 147, baseType: !96, size: 64, align: 64, offset: 384)
!96 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !97, size: 64, align: 64)
!97 = !DISubroutineType(types: !98)
!98 = !{!56, !40, !99, !99, !46}
!99 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !46, size: 64, align: 64)
!100 = !DIDerivedType(tag: DW_TAG_member, name: "update", scope: !37, file: !32, line: 152, baseType: !101, size: 64, align: 64, offset: 448)
!101 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !102, size: 64, align: 64)
!102 = !DISubroutineType(types: !103)
!103 = !{!56, !40, !57, !104, !104}
!104 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !105, size: 64, align: 64)
!105 = !DIDerivedType(tag: DW_TAG_const_type, baseType: !106)
!106 = !DIDerivedType(tag: DW_TAG_typedef, name: "lzma_filter", file: !107, line: 65, baseType: !108)
!107 = !DIFile(filename: "/data/download/cmake/cmake-master/Utilities/cmliblzma/liblzma/api/lzma/filter.h", directory: "/data/download/cmake/cmake-master/Utilities/cmliblzma")
!108 = !DICompositeType(tag: DW_TAG_structure_type, file: !107, line: 43, size: 128, align: 64, elements: !109)
!109 = !{!110, !111}
!110 = !DIDerivedType(tag: DW_TAG_member, name: "id", scope: !108, file: !107, line: 54, baseType: !44, size: 64, align: 64)
!111 = !DIDerivedType(tag: DW_TAG_member, name: "options", scope: !108, file: !107, line: 63, baseType: !65, size: 64, align: 64, offset: 64)
!112 = !DIDerivedType(tag: DW_TAG_member, name: "sequence", scope: !33, file: !32, line: 189, baseType: !31, size: 32, align: 32, offset: 512)
!113 = !DIDerivedType(tag: DW_TAG_member, name: "avail_in", scope: !33, file: !32, line: 194, baseType: !66, size: 64, align: 64, offset: 576)
!114 = !DIDerivedType(tag: DW_TAG_member, name: "supported_actions", scope: !33, file: !32, line: 197, baseType: !115, size: 32, align: 8, offset: 640)
!115 = !DICompositeType(tag: DW_TAG_array_type, baseType: !116, size: 32, align: 8, elements: !117)
!116 = !DIBasicType(name: "_Bool", size: 8, align: 8, encoding: DW_ATE_boolean)
!117 = !{!118}
!118 = !DISubrange(count: 4)
!119 = !DIDerivedType(tag: DW_TAG_member, name: "allow_buf_error", scope: !33, file: !32, line: 201, baseType: !116, size: 8, align: 8, offset: 672)
!120 = !{!121, !122, !123, !124, !125, !126}
!121 = !DIEnumerator(name: "ISEQ_RUN", value: 0)
!122 = !DIEnumerator(name: "ISEQ_SYNC_FLUSH", value: 1)
!123 = !DIEnumerator(name: "ISEQ_FULL_FLUSH", value: 2)
!124 = !DIEnumerator(name: "ISEQ_FINISH", value: 3)
!125 = !DIEnumerator(name: "ISEQ_END", value: 4)
!126 = !DIEnumerator(name: "ISEQ_ERROR", value: 5)
!127 = !DICompositeType(tag: DW_TAG_enumeration_type, file: !4, line: 44, size: 32, align: 32, elements: !128)
!128 = !{!129}
!129 = !DIEnumerator(name: "LZMA_RESERVED_ENUM", value: 0)
!130 = !{!65, !131}
!131 = !DIDerivedType(tag: DW_TAG_typedef, name: "lzma_filter_find", file: !132, line: 35, baseType: !133)
!132 = !DIFile(filename: "/data/download/cmake/cmake-master/Utilities/cmliblzma/liblzma/common/filter_common.h", directory: "/data/download/cmake/cmake-master/Utilities/cmliblzma")
!133 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !134, size: 64, align: 64)
!134 = !DISubroutineType(types: !135)
!135 = !{!136, !44}
!136 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !137, size: 64, align: 64)
!137 = !DIDerivedType(tag: DW_TAG_const_type, baseType: !138)
!138 = !DIDerivedType(tag: DW_TAG_typedef, name: "lzma_filter_coder", file: !132, line: 32, baseType: !139)
!139 = !DICompositeType(tag: DW_TAG_structure_type, file: !132, line: 20, size: 192, align: 64, elements: !140)
!140 = !{!141, !142, !156}
!141 = !DIDerivedType(tag: DW_TAG_member, name: "id", scope: !139, file: !132, line: 22, baseType: !44, size: 64, align: 64)
!142 = !DIDerivedType(tag: DW_TAG_member, name: "init", scope: !139, file: !132, line: 26, baseType: !143, size: 64, align: 64, offset: 64)
!143 = !DIDerivedType(tag: DW_TAG_typedef, name: "lzma_init_function", file: !32, line: 81, baseType: !144)
!144 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !145, size: 64, align: 64)
!145 = !DISubroutineType(types: !146)
!146 = !{!56, !147, !57, !148}
!147 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !36, size: 64, align: 64)
!148 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !149, size: 64, align: 64)
!149 = !DIDerivedType(tag: DW_TAG_const_type, baseType: !150)
!150 = !DIDerivedType(tag: DW_TAG_typedef, name: "lzma_filter_info", file: !32, line: 77, baseType: !151)
!151 = !DICompositeType(tag: DW_TAG_structure_type, name: "lzma_filter_info_s", file: !32, line: 104, size: 192, align: 64, elements: !152)
!152 = !{!153, !154, !155}
!153 = !DIDerivedType(tag: DW_TAG_member, name: "id", scope: !151, file: !32, line: 107, baseType: !44, size: 64, align: 64)
!154 = !DIDerivedType(tag: DW_TAG_member, name: "init", scope: !151, file: !32, line: 111, baseType: !143, size: 64, align: 64, offset: 64)
!155 = !DIDerivedType(tag: DW_TAG_member, name: "options", scope: !151, file: !32, line: 114, baseType: !65, size: 64, align: 64, offset: 128)
!156 = !DIDerivedType(tag: DW_TAG_member, name: "memusage", scope: !139, file: !132, line: 30, baseType: !157, size: 64, align: 64, offset: 128)
!157 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !158, size: 64, align: 64)
!158 = !DISubroutineType(types: !159)
!159 = !{!46, !160}
!160 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !161, size: 64, align: 64)
!161 = !DIDerivedType(tag: DW_TAG_const_type, baseType: null)
!162 = !{!163, !168, !196, !199, !200, !203, !209, !212}
!163 = distinct !DISubprogram(name: "lzma_filter_encoder_is_supported", scope: !1, file: !1, line: 172, type: !164, isLocal: false, isDefinition: true, scopeLine: 173, flags: DIFlagPrototyped, isOptimized: false, variables: !167)
!164 = !DISubroutineType(types: !165)
!165 = !{!166, !44}
!166 = !DIDerivedType(tag: DW_TAG_typedef, name: "lzma_bool", file: !4, line: 29, baseType: !77)
!167 = !{}
!168 = distinct !DISubprogram(name: "lzma_filters_update", scope: !1, file: !1, line: 179, type: !169, isLocal: false, isDefinition: true, scopeLine: 180, flags: DIFlagPrototyped, isOptimized: false, variables: !167)
!169 = !DISubroutineType(types: !170)
!170 = !{!56, !171, !104}
!171 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !172, size: 64, align: 64)
!172 = !DIDerivedType(tag: DW_TAG_typedef, name: "lzma_stream", file: !4, line: 490, baseType: !173)
!173 = !DICompositeType(tag: DW_TAG_structure_type, file: !4, line: 453, size: 1088, align: 64, elements: !174)
!174 = !{!175, !176, !177, !178, !179, !180, !181, !182, !185, !186, !187, !188, !189, !190, !191, !192, !193, !195}
!175 = !DIDerivedType(tag: DW_TAG_member, name: "next_in", scope: !173, file: !4, line: 454, baseType: !74, size: 64, align: 64)
!176 = !DIDerivedType(tag: DW_TAG_member, name: "avail_in", scope: !173, file: !4, line: 455, baseType: !66, size: 64, align: 64, offset: 64)
!177 = !DIDerivedType(tag: DW_TAG_member, name: "total_in", scope: !173, file: !4, line: 456, baseType: !46, size: 64, align: 64, offset: 128)
!178 = !DIDerivedType(tag: DW_TAG_member, name: "next_out", scope: !173, file: !4, line: 458, baseType: !81, size: 64, align: 64, offset: 192)
!179 = !DIDerivedType(tag: DW_TAG_member, name: "avail_out", scope: !173, file: !4, line: 459, baseType: !66, size: 64, align: 64, offset: 256)
!180 = !DIDerivedType(tag: DW_TAG_member, name: "total_out", scope: !173, file: !4, line: 460, baseType: !46, size: 64, align: 64, offset: 320)
!181 = !DIDerivedType(tag: DW_TAG_member, name: "allocator", scope: !173, file: !4, line: 468, baseType: !57, size: 64, align: 64, offset: 384)
!182 = !DIDerivedType(tag: DW_TAG_member, name: "internal", scope: !173, file: !4, line: 471, baseType: !183, size: 64, align: 64, offset: 448)
!183 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !184, size: 64, align: 64)
!184 = !DIDerivedType(tag: DW_TAG_typedef, name: "lzma_internal", file: !4, line: 411, baseType: !33)
!185 = !DIDerivedType(tag: DW_TAG_member, name: "reserved_ptr1", scope: !173, file: !4, line: 479, baseType: !65, size: 64, align: 64, offset: 512)
!186 = !DIDerivedType(tag: DW_TAG_member, name: "reserved_ptr2", scope: !173, file: !4, line: 480, baseType: !65, size: 64, align: 64, offset: 576)
!187 = !DIDerivedType(tag: DW_TAG_member, name: "reserved_ptr3", scope: !173, file: !4, line: 481, baseType: !65, size: 64, align: 64, offset: 640)
!188 = !DIDerivedType(tag: DW_TAG_member, name: "reserved_ptr4", scope: !173, file: !4, line: 482, baseType: !65, size: 64, align: 64, offset: 704)
!189 = !DIDerivedType(tag: DW_TAG_member, name: "reserved_int1", scope: !173, file: !4, line: 483, baseType: !46, size: 64, align: 64, offset: 768)
!190 = !DIDerivedType(tag: DW_TAG_member, name: "reserved_int2", scope: !173, file: !4, line: 484, baseType: !46, size: 64, align: 64, offset: 832)
!191 = !DIDerivedType(tag: DW_TAG_member, name: "reserved_int3", scope: !173, file: !4, line: 485, baseType: !66, size: 64, align: 64, offset: 896)
!192 = !DIDerivedType(tag: DW_TAG_member, name: "reserved_int4", scope: !173, file: !4, line: 486, baseType: !66, size: 64, align: 64, offset: 960)
!193 = !DIDerivedType(tag: DW_TAG_member, name: "reserved_enum1", scope: !173, file: !4, line: 487, baseType: !194, size: 32, align: 32, offset: 1024)
!194 = !DIDerivedType(tag: DW_TAG_typedef, name: "lzma_reserved_enum", file: !4, line: 46, baseType: !127)
!195 = !DIDerivedType(tag: DW_TAG_member, name: "reserved_enum2", scope: !173, file: !4, line: 488, baseType: !194, size: 32, align: 32, offset: 1056)
!196 = distinct !DISubprogram(name: "lzma_raw_encoder_init", scope: !1, file: !1, line: 208, type: !197, isLocal: false, isDefinition: true, scopeLine: 210, flags: DIFlagPrototyped, isOptimized: false, variables: !167)
!197 = !DISubroutineType(types: !198)
!198 = !{!56, !147, !57, !104}
!199 = distinct !DISubprogram(name: "lzma_raw_encoder", scope: !1, file: !1, line: 217, type: !169, isLocal: false, isDefinition: true, scopeLine: 218, flags: DIFlagPrototyped, isOptimized: false, variables: !167)
!200 = distinct !DISubprogram(name: "lzma_raw_encoder_memusage", scope: !1, file: !1, line: 231, type: !201, isLocal: false, isDefinition: true, scopeLine: 232, flags: DIFlagPrototyped, isOptimized: false, variables: !167)
!201 = !DISubroutineType(types: !202)
!202 = !{!46, !104}
!203 = distinct !DISubprogram(name: "lzma_properties_size", scope: !1, file: !1, line: 264, type: !204, isLocal: false, isDefinition: true, scopeLine: 265, flags: DIFlagPrototyped, isOptimized: false, variables: !167)
!204 = !DISubroutineType(types: !205)
!205 = !{!56, !206, !104}
!206 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !207, size: 64, align: 64)
!207 = !DIDerivedType(tag: DW_TAG_typedef, name: "uint32_t", file: !47, line: 51, baseType: !208)
!208 = !DIBasicType(name: "unsigned int", size: 32, align: 32, encoding: DW_ATE_unsigned)
!209 = distinct !DISubprogram(name: "lzma_properties_encode", scope: !1, file: !1, line: 287, type: !210, isLocal: false, isDefinition: true, scopeLine: 288, flags: DIFlagPrototyped, isOptimized: false, variables: !167)
!210 = !DISubroutineType(types: !211)
!211 = !{!56, !104, !81}
!212 = distinct !DISubprogram(name: "encoder_find", scope: !1, file: !1, line: 160, type: !213, isLocal: true, isDefinition: true, scopeLine: 161, flags: DIFlagPrototyped, isOptimized: false, variables: !167)
!213 = !DISubroutineType(types: !214)
!214 = !{!215, !44}
!215 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !216, size: 64, align: 64)
!216 = !DIDerivedType(tag: DW_TAG_const_type, baseType: !217)
!217 = !DIDerivedType(tag: DW_TAG_typedef, name: "lzma_filter_encoder", file: !1, line: 53, baseType: !218)
!218 = !DICompositeType(tag: DW_TAG_structure_type, file: !1, line: 21, size: 448, align: 64, elements: !219)
!219 = !{!220, !221, !222, !223, !227, !231, !232}
!220 = !DIDerivedType(tag: DW_TAG_member, name: "id", scope: !218, file: !1, line: 23, baseType: !44, size: 64, align: 64)
!221 = !DIDerivedType(tag: DW_TAG_member, name: "init", scope: !218, file: !1, line: 27, baseType: !143, size: 64, align: 64, offset: 64)
!222 = !DIDerivedType(tag: DW_TAG_member, name: "memusage", scope: !218, file: !1, line: 31, baseType: !157, size: 64, align: 64, offset: 128)
!223 = !DIDerivedType(tag: DW_TAG_member, name: "chunk_size", scope: !218, file: !1, line: 37, baseType: !224, size: 64, align: 64, offset: 192)
!224 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !225, size: 64, align: 64)
!225 = !DISubroutineType(types: !226)
!226 = !{!44, !160}
!227 = !DIDerivedType(tag: DW_TAG_member, name: "props_size_get", scope: !218, file: !1, line: 42, baseType: !228, size: 64, align: 64, offset: 256)
!228 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !229, size: 64, align: 64)
!229 = !DISubroutineType(types: !230)
!230 = !{!56, !206, !160}
!231 = !DIDerivedType(tag: DW_TAG_member, name: "props_size_fixed", scope: !218, file: !1, line: 43, baseType: !207, size: 32, align: 32, offset: 320)
!232 = !DIDerivedType(tag: DW_TAG_member, name: "props_encode", scope: !218, file: !1, line: 51, baseType: !233, size: 64, align: 64, offset: 384)
!233 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !234, size: 64, align: 64)
!234 = !DISubroutineType(types: !235)
!235 = !{!56, !160, !81}
!236 = !{!237}
!237 = !DIGlobalVariable(name: "encoders", scope: !0, file: !1, line: 56, type: !238, isLocal: true, isDefinition: true, variable: [9 x %struct.lzma_filter_encoder]* @encoders)
!238 = !DICompositeType(tag: DW_TAG_array_type, baseType: !216, size: 4032, align: 64, elements: !239)
!239 = !{!240}
!240 = !DISubrange(count: 9)
!241 = !{i32 2, !"Dwarf Version", i32 4}
!242 = !{i32 2, !"Debug Info Version", i32 3}
!243 = !{!"clang version 3.8.0 (tags/RELEASE_380/final)"}
!244 = !DILocalVariable(name: "id", arg: 1, scope: !163, file: !1, line: 172, type: !44)
!245 = !DIExpression()
!246 = !DILocation(line: 172, column: 43, scope: !163)
!247 = !DILocation(line: 174, column: 22, scope: !163)
!248 = !DILocation(line: 174, column: 9, scope: !163)
!249 = !DILocation(line: 174, column: 26, scope: !163)
!250 = !DILocation(line: 174, column: 2, scope: !163)
!251 = !DILocalVariable(name: "id", arg: 1, scope: !212, file: !1, line: 160, type: !44)
!252 = !DILocation(line: 160, column: 23, scope: !212)
!253 = !DILocalVariable(name: "i", scope: !212, file: !1, line: 162, type: !66)
!254 = !DILocation(line: 162, column: 9, scope: !212)
!255 = !DILocation(line: 163, column: 9, scope: !256)
!256 = distinct !DILexicalBlock(scope: !212, file: !1, line: 163, column: 2)
!257 = !DILocation(line: 163, column: 7, scope: !256)
!258 = !DILocation(line: 163, column: 14, scope: !259)
!259 = !DILexicalBlockFile(scope: !260, file: !1, discriminator: 1)
!260 = distinct !DILexicalBlock(scope: !256, file: !1, line: 163, column: 2)
!261 = !DILocation(line: 163, column: 16, scope: !259)
!262 = !DILocation(line: 163, column: 2, scope: !259)
!263 = !DILocation(line: 164, column: 16, scope: !264)
!264 = distinct !DILexicalBlock(scope: !260, file: !1, line: 164, column: 7)
!265 = !DILocation(line: 164, column: 7, scope: !264)
!266 = !DILocation(line: 164, column: 19, scope: !264)
!267 = !DILocation(line: 164, column: 25, scope: !264)
!268 = !DILocation(line: 164, column: 22, scope: !264)
!269 = !DILocation(line: 164, column: 7, scope: !260)
!270 = !DILocation(line: 165, column: 22, scope: !264)
!271 = !DILocation(line: 165, column: 20, scope: !264)
!272 = !DILocation(line: 165, column: 4, scope: !264)
!273 = !DILocation(line: 164, column: 25, scope: !274)
!274 = !DILexicalBlockFile(scope: !264, file: !1, discriminator: 1)
!275 = !DILocation(line: 163, column: 40, scope: !276)
!276 = !DILexicalBlockFile(scope: !260, file: !1, discriminator: 2)
!277 = !DILocation(line: 163, column: 2, scope: !276)
!278 = !DILocation(line: 167, column: 2, scope: !212)
!279 = !DILocation(line: 168, column: 1, scope: !212)
!280 = !DILocalVariable(name: "strm", arg: 1, scope: !168, file: !1, line: 179, type: !171)
!281 = !DILocation(line: 179, column: 34, scope: !168)
!282 = !DILocalVariable(name: "filters", arg: 2, scope: !168, file: !1, line: 179, type: !104)
!283 = !DILocation(line: 179, column: 59, scope: !168)
!284 = !DILocalVariable(name: "i", scope: !168, file: !1, line: 181, type: !66)
!285 = !DILocation(line: 181, column: 9, scope: !168)
!286 = !DILocalVariable(name: "count", scope: !168, file: !1, line: 182, type: !66)
!287 = !DILocation(line: 182, column: 9, scope: !168)
!288 = !DILocalVariable(name: "reversed_filters", scope: !168, file: !1, line: 183, type: !289)
!289 = !DICompositeType(tag: DW_TAG_array_type, baseType: !106, size: 640, align: 64, elements: !290)
!290 = !{!291}
!291 = !DISubrange(count: 5)
!292 = !DILocation(line: 183, column: 14, scope: !168)
!293 = !DILocation(line: 185, column: 6, scope: !294)
!294 = distinct !DILexicalBlock(scope: !168, file: !1, line: 185, column: 6)
!295 = !DILocation(line: 185, column: 12, scope: !294)
!296 = !DILocation(line: 185, column: 22, scope: !294)
!297 = !DILocation(line: 185, column: 27, scope: !294)
!298 = !DILocation(line: 185, column: 34, scope: !294)
!299 = !DILocation(line: 185, column: 6, scope: !168)
!300 = !DILocation(line: 186, column: 3, scope: !294)
!301 = !DILocation(line: 189, column: 32, scope: !302)
!302 = distinct !DILexicalBlock(scope: !168, file: !1, line: 189, column: 6)
!303 = !DILocation(line: 189, column: 6, scope: !302)
!304 = !DILocation(line: 189, column: 41, scope: !302)
!305 = !DILocation(line: 189, column: 6, scope: !168)
!306 = !DILocation(line: 190, column: 3, scope: !302)
!307 = !DILocation(line: 194, column: 2, scope: !168)
!308 = !DILocation(line: 194, column: 17, scope: !309)
!309 = !DILexicalBlockFile(scope: !168, file: !1, discriminator: 1)
!310 = !DILocation(line: 194, column: 9, scope: !309)
!311 = !DILocation(line: 194, column: 24, scope: !309)
!312 = !DILocation(line: 194, column: 27, scope: !309)
!313 = !DILocation(line: 194, column: 2, scope: !309)
!314 = !DILocation(line: 195, column: 3, scope: !168)
!315 = !DILocation(line: 194, column: 2, scope: !316)
!316 = !DILexicalBlockFile(scope: !168, file: !1, discriminator: 2)
!317 = !DILocation(line: 197, column: 9, scope: !318)
!318 = distinct !DILexicalBlock(scope: !168, file: !1, line: 197, column: 2)
!319 = !DILocation(line: 197, column: 7, scope: !318)
!320 = !DILocation(line: 197, column: 14, scope: !321)
!321 = !DILexicalBlockFile(scope: !322, file: !1, discriminator: 1)
!322 = distinct !DILexicalBlock(scope: !318, file: !1, line: 197, column: 2)
!323 = !DILocation(line: 197, column: 18, scope: !321)
!324 = !DILocation(line: 197, column: 16, scope: !321)
!325 = !DILocation(line: 197, column: 2, scope: !321)
!326 = !DILocation(line: 198, column: 20, scope: !322)
!327 = !DILocation(line: 198, column: 28, scope: !322)
!328 = !DILocation(line: 198, column: 26, scope: !322)
!329 = !DILocation(line: 198, column: 30, scope: !322)
!330 = !DILocation(line: 198, column: 3, scope: !322)
!331 = !DILocation(line: 198, column: 45, scope: !322)
!332 = !DILocation(line: 198, column: 37, scope: !322)
!333 = !DILocation(line: 197, column: 25, scope: !334)
!334 = !DILexicalBlockFile(scope: !322, file: !1, discriminator: 2)
!335 = !DILocation(line: 197, column: 2, scope: !334)
!336 = !DILocation(line: 200, column: 19, scope: !168)
!337 = !DILocation(line: 200, column: 2, scope: !168)
!338 = !DILocation(line: 200, column: 26, scope: !168)
!339 = !DILocation(line: 200, column: 29, scope: !168)
!340 = !DILocation(line: 202, column: 9, scope: !168)
!341 = !DILocation(line: 202, column: 15, scope: !168)
!342 = !DILocation(line: 202, column: 25, scope: !168)
!343 = !DILocation(line: 202, column: 30, scope: !168)
!344 = !DILocation(line: 202, column: 37, scope: !168)
!345 = !DILocation(line: 202, column: 43, scope: !168)
!346 = !DILocation(line: 202, column: 53, scope: !168)
!347 = !DILocation(line: 202, column: 58, scope: !168)
!348 = !DILocation(line: 203, column: 4, scope: !168)
!349 = !DILocation(line: 203, column: 10, scope: !168)
!350 = !DILocation(line: 203, column: 21, scope: !168)
!351 = !DILocation(line: 203, column: 30, scope: !168)
!352 = !DILocation(line: 202, column: 2, scope: !168)
!353 = !DILocation(line: 204, column: 1, scope: !168)
!354 = !DILocalVariable(name: "filters", arg: 1, scope: !200, file: !1, line: 231, type: !104)
!355 = !DILocation(line: 231, column: 46, scope: !200)
!356 = !DILocation(line: 234, column: 39, scope: !200)
!357 = !DILocation(line: 233, column: 9, scope: !200)
!358 = !DILocation(line: 233, column: 2, scope: !200)
!359 = !DILocalVariable(name: "next", arg: 1, scope: !196, file: !1, line: 208, type: !147)
!360 = !DILocation(line: 208, column: 40, scope: !196)
!361 = !DILocalVariable(name: "allocator", arg: 2, scope: !196, file: !1, line: 208, type: !57)
!362 = !DILocation(line: 208, column: 62, scope: !196)
!363 = !DILocalVariable(name: "options", arg: 3, scope: !196, file: !1, line: 209, type: !104)
!364 = !DILocation(line: 209, column: 22, scope: !196)
!365 = !DILocation(line: 211, column: 29, scope: !196)
!366 = !DILocation(line: 211, column: 35, scope: !196)
!367 = !DILocation(line: 212, column: 4, scope: !196)
!368 = !DILocation(line: 211, column: 9, scope: !196)
!369 = !DILocation(line: 211, column: 2, scope: !196)
!370 = !DILocalVariable(name: "strm", arg: 1, scope: !199, file: !1, line: 217, type: !171)
!371 = !DILocation(line: 217, column: 31, scope: !199)
!372 = !DILocalVariable(name: "options", arg: 2, scope: !199, file: !1, line: 217, type: !104)
!373 = !DILocation(line: 217, column: 56, scope: !199)
!374 = !DILocation(line: 219, column: 2, scope: !199)
!375 = !DILocalVariable(name: "ret_", scope: !376, file: !1, line: 219, type: !56)
!376 = distinct !DILexicalBlock(scope: !199, file: !1, line: 219, column: 2)
!377 = !DILocation(line: 219, column: 2, scope: !376)
!378 = !DILocation(line: 219, column: 2, scope: !379)
!379 = !DILexicalBlockFile(scope: !376, file: !1, discriminator: 1)
!380 = !DILocalVariable(name: "ret_", scope: !381, file: !1, line: 219, type: !382)
!381 = distinct !DILexicalBlock(scope: !376, file: !1, line: 219, column: 2)
!382 = !DIDerivedType(tag: DW_TAG_const_type, baseType: !56)
!383 = !DILocation(line: 219, column: 2, scope: !381)
!384 = !DILocation(line: 219, column: 2, scope: !385)
!385 = !DILexicalBlockFile(scope: !381, file: !1, discriminator: 2)
!386 = !DILocation(line: 219, column: 2, scope: !387)
!387 = !DILexicalBlockFile(scope: !388, file: !1, discriminator: 3)
!388 = distinct !DILexicalBlock(scope: !381, file: !1, line: 219, column: 2)
!389 = !DILocation(line: 219, column: 2, scope: !390)
!390 = !DILexicalBlockFile(scope: !381, file: !1, discriminator: 4)
!391 = !DILocation(line: 219, column: 2, scope: !392)
!392 = !DILexicalBlockFile(scope: !376, file: !1, discriminator: 5)
!393 = !DILocation(line: 219, column: 2, scope: !394)
!394 = !DILexicalBlockFile(scope: !395, file: !1, discriminator: 6)
!395 = distinct !DILexicalBlock(scope: !396, file: !1, line: 219, column: 2)
!396 = distinct !DILexicalBlock(scope: !376, file: !1, line: 219, column: 2)
!397 = !DILocation(line: 219, column: 2, scope: !398)
!398 = !DILexicalBlockFile(scope: !376, file: !1, discriminator: 7)
!399 = !DILocation(line: 222, column: 2, scope: !199)
!400 = !DILocation(line: 222, column: 8, scope: !199)
!401 = !DILocation(line: 222, column: 18, scope: !199)
!402 = !DILocation(line: 222, column: 46, scope: !199)
!403 = !DILocation(line: 223, column: 2, scope: !199)
!404 = !DILocation(line: 223, column: 8, scope: !199)
!405 = !DILocation(line: 223, column: 18, scope: !199)
!406 = !DILocation(line: 223, column: 53, scope: !199)
!407 = !DILocation(line: 224, column: 2, scope: !199)
!408 = !DILocation(line: 224, column: 8, scope: !199)
!409 = !DILocation(line: 224, column: 18, scope: !199)
!410 = !DILocation(line: 224, column: 49, scope: !199)
!411 = !DILocation(line: 226, column: 2, scope: !199)
!412 = !DILocation(line: 227, column: 1, scope: !199)
!413 = !DILocalVariable(name: "size", arg: 1, scope: !203, file: !1, line: 264, type: !206)
!414 = !DILocation(line: 264, column: 32, scope: !203)
!415 = !DILocalVariable(name: "filter", arg: 2, scope: !203, file: !1, line: 264, type: !104)
!416 = !DILocation(line: 264, column: 57, scope: !203)
!417 = !DILocalVariable(name: "fe", scope: !203, file: !1, line: 266, type: !418)
!418 = !DIDerivedType(tag: DW_TAG_const_type, baseType: !215)
!419 = !DILocation(line: 266, column: 35, scope: !203)
!420 = !DILocation(line: 266, column: 53, scope: !203)
!421 = !DILocation(line: 266, column: 61, scope: !203)
!422 = !DILocation(line: 266, column: 40, scope: !203)
!423 = !DILocation(line: 267, column: 6, scope: !424)
!424 = distinct !DILexicalBlock(scope: !203, file: !1, line: 267, column: 6)
!425 = !DILocation(line: 267, column: 9, scope: !424)
!426 = !DILocation(line: 267, column: 6, scope: !203)
!427 = !DILocation(line: 272, column: 10, scope: !428)
!428 = distinct !DILexicalBlock(scope: !424, file: !1, line: 267, column: 18)
!429 = !DILocation(line: 272, column: 18, scope: !428)
!430 = !DILocation(line: 272, column: 21, scope: !428)
!431 = !DILocation(line: 272, column: 3, scope: !428)
!432 = !DILocation(line: 276, column: 6, scope: !433)
!433 = distinct !DILexicalBlock(scope: !203, file: !1, line: 276, column: 6)
!434 = !DILocation(line: 276, column: 10, scope: !433)
!435 = !DILocation(line: 276, column: 25, scope: !433)
!436 = !DILocation(line: 276, column: 6, scope: !203)
!437 = !DILocation(line: 278, column: 11, scope: !438)
!438 = distinct !DILexicalBlock(scope: !433, file: !1, line: 276, column: 34)
!439 = !DILocation(line: 278, column: 15, scope: !438)
!440 = !DILocation(line: 278, column: 4, scope: !438)
!441 = !DILocation(line: 278, column: 9, scope: !438)
!442 = !DILocation(line: 279, column: 3, scope: !438)
!443 = !DILocation(line: 282, column: 9, scope: !203)
!444 = !DILocation(line: 282, column: 13, scope: !203)
!445 = !DILocation(line: 282, column: 28, scope: !203)
!446 = !DILocation(line: 282, column: 34, scope: !203)
!447 = !DILocation(line: 282, column: 42, scope: !203)
!448 = !DILocation(line: 282, column: 2, scope: !203)
!449 = !DILocation(line: 283, column: 1, scope: !203)
!450 = !DILocalVariable(name: "filter", arg: 1, scope: !209, file: !1, line: 287, type: !104)
!451 = !DILocation(line: 287, column: 43, scope: !209)
!452 = !DILocalVariable(name: "props", arg: 2, scope: !209, file: !1, line: 287, type: !81)
!453 = !DILocation(line: 287, column: 60, scope: !209)
!454 = !DILocalVariable(name: "fe", scope: !209, file: !1, line: 289, type: !418)
!455 = !DILocation(line: 289, column: 35, scope: !209)
!456 = !DILocation(line: 289, column: 53, scope: !209)
!457 = !DILocation(line: 289, column: 61, scope: !209)
!458 = !DILocation(line: 289, column: 40, scope: !209)
!459 = !DILocation(line: 290, column: 6, scope: !460)
!460 = distinct !DILexicalBlock(scope: !209, file: !1, line: 290, column: 6)
!461 = !DILocation(line: 290, column: 9, scope: !460)
!462 = !DILocation(line: 290, column: 6, scope: !209)
!463 = !DILocation(line: 291, column: 3, scope: !460)
!464 = !DILocation(line: 293, column: 6, scope: !465)
!465 = distinct !DILexicalBlock(scope: !209, file: !1, line: 293, column: 6)
!466 = !DILocation(line: 293, column: 10, scope: !465)
!467 = !DILocation(line: 293, column: 23, scope: !465)
!468 = !DILocation(line: 293, column: 6, scope: !209)
!469 = !DILocation(line: 294, column: 3, scope: !465)
!470 = !DILocation(line: 296, column: 9, scope: !209)
!471 = !DILocation(line: 296, column: 13, scope: !209)
!472 = !DILocation(line: 296, column: 26, scope: !209)
!473 = !DILocation(line: 296, column: 34, scope: !209)
!474 = !DILocation(line: 296, column: 43, scope: !209)
!475 = !DILocation(line: 296, column: 2, scope: !209)
!476 = !DILocation(line: 297, column: 1, scope: !209)
