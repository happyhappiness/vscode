; ModuleID = '/data/download/cmake/cmake-master/Utilities/cmliblzma/liblzma/common/filter_decoder.c'
target datalayout = "e-m:e-i64:64-f80:128-n8:16:32:64-S128"
target triple = "x86_64-unknown-linux-gnu"

%struct.lzma_filter_decoder = type { i64, i32 (%struct.lzma_next_coder_s*, %struct.lzma_allocator*, %struct.lzma_filter_info_s*)*, i64 (i8*)*, i32 (i8**, %struct.lzma_allocator*, i8*, i64)* }
%struct.lzma_next_coder_s = type { %struct.lzma_coder_s*, i64, i64, i32 (%struct.lzma_coder_s*, %struct.lzma_allocator*, i8*, i64*, i64, i8*, i64*, i64, i32)*, void (%struct.lzma_coder_s*, %struct.lzma_allocator*)*, i32 (%struct.lzma_coder_s*)*, i32 (%struct.lzma_coder_s*, i64*, i64*, i64)*, i32 (%struct.lzma_coder_s*, %struct.lzma_allocator*, %struct.lzma_filter*, %struct.lzma_filter*)* }
%struct.lzma_coder_s = type opaque
%struct.lzma_filter = type { i64, i8* }
%struct.lzma_allocator = type { i8* (i8*, i64, i64)*, void (i8*, i8*)*, i8* }
%struct.lzma_filter_info_s = type { i64, {}*, i8* }
%struct.lzma_filter_coder = type { i64, i32 (%struct.lzma_next_coder_s*, %struct.lzma_allocator*, %struct.lzma_filter_info_s*)*, i64 (i8*)* }
%struct.lzma_stream = type { i8*, i64, i64, i8*, i64, i64, %struct.lzma_allocator*, %struct.lzma_internal_s*, i8*, i8*, i8*, i8*, i64, i64, i64, i64, i32, i32 }
%struct.lzma_internal_s = type { %struct.lzma_next_coder_s, i32, i64, [4 x i8], i8 }

@decoders = internal constant [9 x %struct.lzma_filter_decoder] [%struct.lzma_filter_decoder { i64 4611686018427387905, i32 (%struct.lzma_next_coder_s*, %struct.lzma_allocator*, %struct.lzma_filter_info_s*)* @lzma_lzma_decoder_init, i64 (i8*)* @lzma_lzma_decoder_memusage, i32 (i8**, %struct.lzma_allocator*, i8*, i64)* @lzma_lzma_props_decode }, %struct.lzma_filter_decoder { i64 33, i32 (%struct.lzma_next_coder_s*, %struct.lzma_allocator*, %struct.lzma_filter_info_s*)* @lzma_lzma2_decoder_init, i64 (i8*)* @lzma_lzma2_decoder_memusage, i32 (i8**, %struct.lzma_allocator*, i8*, i64)* @lzma_lzma2_props_decode }, %struct.lzma_filter_decoder { i64 4, i32 (%struct.lzma_next_coder_s*, %struct.lzma_allocator*, %struct.lzma_filter_info_s*)* @lzma_simple_x86_decoder_init, i64 (i8*)* null, i32 (i8**, %struct.lzma_allocator*, i8*, i64)* @lzma_simple_props_decode }, %struct.lzma_filter_decoder { i64 5, i32 (%struct.lzma_next_coder_s*, %struct.lzma_allocator*, %struct.lzma_filter_info_s*)* @lzma_simple_powerpc_decoder_init, i64 (i8*)* null, i32 (i8**, %struct.lzma_allocator*, i8*, i64)* @lzma_simple_props_decode }, %struct.lzma_filter_decoder { i64 6, i32 (%struct.lzma_next_coder_s*, %struct.lzma_allocator*, %struct.lzma_filter_info_s*)* @lzma_simple_ia64_decoder_init, i64 (i8*)* null, i32 (i8**, %struct.lzma_allocator*, i8*, i64)* @lzma_simple_props_decode }, %struct.lzma_filter_decoder { i64 7, i32 (%struct.lzma_next_coder_s*, %struct.lzma_allocator*, %struct.lzma_filter_info_s*)* @lzma_simple_arm_decoder_init, i64 (i8*)* null, i32 (i8**, %struct.lzma_allocator*, i8*, i64)* @lzma_simple_props_decode }, %struct.lzma_filter_decoder { i64 8, i32 (%struct.lzma_next_coder_s*, %struct.lzma_allocator*, %struct.lzma_filter_info_s*)* @lzma_simple_armthumb_decoder_init, i64 (i8*)* null, i32 (i8**, %struct.lzma_allocator*, i8*, i64)* @lzma_simple_props_decode }, %struct.lzma_filter_decoder { i64 9, i32 (%struct.lzma_next_coder_s*, %struct.lzma_allocator*, %struct.lzma_filter_info_s*)* @lzma_simple_sparc_decoder_init, i64 (i8*)* null, i32 (i8**, %struct.lzma_allocator*, i8*, i64)* @lzma_simple_props_decode }, %struct.lzma_filter_decoder { i64 3, i32 (%struct.lzma_next_coder_s*, %struct.lzma_allocator*, %struct.lzma_filter_info_s*)* @lzma_delta_decoder_init, i64 (i8*)* @lzma_delta_coder_memusage, i32 (i8**, %struct.lzma_allocator*, i8*, i64)* @lzma_delta_props_decode }], align 16

; Function Attrs: nounwind readnone uwtable
define zeroext i8 @lzma_filter_decoder_is_supported(i64 %id) #0 !dbg !163 {
entry:
  %id.addr = alloca i64, align 8
  store i64 %id, i64* %id.addr, align 8
  call void @llvm.dbg.declare(metadata i64* %id.addr, metadata !230, metadata !231), !dbg !232
  %0 = load i64, i64* %id.addr, align 8, !dbg !233
  %call = call %struct.lzma_filter_decoder* @decoder_find(i64 %0), !dbg !234
  %cmp = icmp ne %struct.lzma_filter_decoder* %call, null, !dbg !235
  %conv = zext i1 %cmp to i32, !dbg !235
  %conv1 = trunc i32 %conv to i8, !dbg !234
  ret i8 %conv1, !dbg !236
}

; Function Attrs: nounwind readnone
declare void @llvm.dbg.declare(metadata, metadata, metadata) #1

; Function Attrs: nounwind uwtable
define internal %struct.lzma_filter_decoder* @decoder_find(i64 %id) #2 !dbg !206 {
entry:
  %retval = alloca %struct.lzma_filter_decoder*, align 8
  %id.addr = alloca i64, align 8
  %i = alloca i64, align 8
  store i64 %id, i64* %id.addr, align 8
  call void @llvm.dbg.declare(metadata i64* %id.addr, metadata !237, metadata !231), !dbg !238
  call void @llvm.dbg.declare(metadata i64* %i, metadata !239, metadata !231), !dbg !240
  store i64 0, i64* %i, align 8, !dbg !241
  br label %for.cond, !dbg !243

for.cond:                                         ; preds = %for.inc, %entry
  %0 = load i64, i64* %i, align 8, !dbg !244
  %cmp = icmp ult i64 %0, 9, !dbg !247
  br i1 %cmp, label %for.body, label %for.end, !dbg !248

for.body:                                         ; preds = %for.cond
  %1 = load i64, i64* %i, align 8, !dbg !249
  %arrayidx = getelementptr inbounds [9 x %struct.lzma_filter_decoder], [9 x %struct.lzma_filter_decoder]* @decoders, i64 0, i64 %1, !dbg !251
  %id1 = getelementptr inbounds %struct.lzma_filter_decoder, %struct.lzma_filter_decoder* %arrayidx, i32 0, i32 0, !dbg !252
  %2 = load i64, i64* %id1, align 16, !dbg !252
  %3 = load i64, i64* %id.addr, align 8, !dbg !253
  %cmp2 = icmp eq i64 %2, %3, !dbg !254
  br i1 %cmp2, label %if.then, label %if.end, !dbg !255

if.then:                                          ; preds = %for.body
  %4 = load i64, i64* %i, align 8, !dbg !256
  %add.ptr = getelementptr inbounds %struct.lzma_filter_decoder, %struct.lzma_filter_decoder* getelementptr inbounds ([9 x %struct.lzma_filter_decoder], [9 x %struct.lzma_filter_decoder]* @decoders, i32 0, i32 0), i64 %4, !dbg !257
  store %struct.lzma_filter_decoder* %add.ptr, %struct.lzma_filter_decoder** %retval, align 8, !dbg !258
  br label %return, !dbg !258

if.end:                                           ; preds = %for.body
  br label %for.inc, !dbg !259

for.inc:                                          ; preds = %if.end
  %5 = load i64, i64* %i, align 8, !dbg !261
  %inc = add i64 %5, 1, !dbg !261
  store i64 %inc, i64* %i, align 8, !dbg !261
  br label %for.cond, !dbg !263

for.end:                                          ; preds = %for.cond
  store %struct.lzma_filter_decoder* null, %struct.lzma_filter_decoder** %retval, align 8, !dbg !264
  br label %return, !dbg !264

return:                                           ; preds = %for.end, %if.then
  %6 = load %struct.lzma_filter_decoder*, %struct.lzma_filter_decoder** %retval, align 8, !dbg !265
  ret %struct.lzma_filter_decoder* %6, !dbg !265
}

; Function Attrs: nounwind uwtable
define i32 @lzma_raw_decoder_init(%struct.lzma_next_coder_s* %next, %struct.lzma_allocator* %allocator, %struct.lzma_filter* %options) #2 !dbg !168 {
entry:
  %next.addr = alloca %struct.lzma_next_coder_s*, align 8
  %allocator.addr = alloca %struct.lzma_allocator*, align 8
  %options.addr = alloca %struct.lzma_filter*, align 8
  store %struct.lzma_next_coder_s* %next, %struct.lzma_next_coder_s** %next.addr, align 8
  call void @llvm.dbg.declare(metadata %struct.lzma_next_coder_s** %next.addr, metadata !266, metadata !231), !dbg !267
  store %struct.lzma_allocator* %allocator, %struct.lzma_allocator** %allocator.addr, align 8
  call void @llvm.dbg.declare(metadata %struct.lzma_allocator** %allocator.addr, metadata !268, metadata !231), !dbg !269
  store %struct.lzma_filter* %options, %struct.lzma_filter** %options.addr, align 8
  call void @llvm.dbg.declare(metadata %struct.lzma_filter** %options.addr, metadata !270, metadata !231), !dbg !271
  %0 = load %struct.lzma_next_coder_s*, %struct.lzma_next_coder_s** %next.addr, align 8, !dbg !272
  %1 = load %struct.lzma_allocator*, %struct.lzma_allocator** %allocator.addr, align 8, !dbg !273
  %2 = load %struct.lzma_filter*, %struct.lzma_filter** %options.addr, align 8, !dbg !274
  %call = call i32 @lzma_raw_coder_init(%struct.lzma_next_coder_s* %0, %struct.lzma_allocator* %1, %struct.lzma_filter* %2, %struct.lzma_filter_coder* (i64)* bitcast (%struct.lzma_filter_decoder* (i64)* @decoder_find to %struct.lzma_filter_coder* (i64)*), i1 zeroext false), !dbg !275
  ret i32 %call, !dbg !276
}

declare i32 @lzma_raw_coder_init(%struct.lzma_next_coder_s*, %struct.lzma_allocator*, %struct.lzma_filter*, %struct.lzma_filter_coder* (i64)*, i1 zeroext) #3

; Function Attrs: nounwind uwtable
define i32 @lzma_raw_decoder(%struct.lzma_stream* %strm, %struct.lzma_filter* %options) #2 !dbg !171 {
entry:
  %retval = alloca i32, align 4
  %strm.addr = alloca %struct.lzma_stream*, align 8
  %options.addr = alloca %struct.lzma_filter*, align 8
  %ret_ = alloca i32, align 4
  %ret_2 = alloca i32, align 4
  store %struct.lzma_stream* %strm, %struct.lzma_stream** %strm.addr, align 8
  call void @llvm.dbg.declare(metadata %struct.lzma_stream** %strm.addr, metadata !277, metadata !231), !dbg !278
  store %struct.lzma_filter* %options, %struct.lzma_filter** %options.addr, align 8
  call void @llvm.dbg.declare(metadata %struct.lzma_filter** %options.addr, metadata !279, metadata !231), !dbg !280
  br label %do.body, !dbg !281

do.body:                                          ; preds = %entry
  call void @llvm.dbg.declare(metadata i32* %ret_, metadata !282, metadata !231), !dbg !284
  br label %do.body1, !dbg !285

do.body1:                                         ; preds = %do.body
  call void @llvm.dbg.declare(metadata i32* %ret_2, metadata !287, metadata !231), !dbg !290
  %0 = load %struct.lzma_stream*, %struct.lzma_stream** %strm.addr, align 8, !dbg !291
  %call = call i32 @lzma_strm_init(%struct.lzma_stream* %0), !dbg !291
  store i32 %call, i32* %ret_2, align 4, !dbg !291
  %1 = load i32, i32* %ret_2, align 4, !dbg !291
  %cmp = icmp ne i32 %1, 0, !dbg !291
  br i1 %cmp, label %if.then, label %if.end, !dbg !291

if.then:                                          ; preds = %do.body1
  %2 = load i32, i32* %ret_2, align 4, !dbg !293
  store i32 %2, i32* %retval, align 4, !dbg !293
  br label %return, !dbg !293

if.end:                                           ; preds = %do.body1
  br label %do.end, !dbg !296

do.end:                                           ; preds = %if.end
  %3 = load %struct.lzma_stream*, %struct.lzma_stream** %strm.addr, align 8, !dbg !298
  %internal = getelementptr inbounds %struct.lzma_stream, %struct.lzma_stream* %3, i32 0, i32 7, !dbg !298
  %4 = load %struct.lzma_internal_s*, %struct.lzma_internal_s** %internal, align 8, !dbg !298
  %next = getelementptr inbounds %struct.lzma_internal_s, %struct.lzma_internal_s* %4, i32 0, i32 0, !dbg !298
  %5 = load %struct.lzma_stream*, %struct.lzma_stream** %strm.addr, align 8, !dbg !298
  %allocator = getelementptr inbounds %struct.lzma_stream, %struct.lzma_stream* %5, i32 0, i32 6, !dbg !298
  %6 = load %struct.lzma_allocator*, %struct.lzma_allocator** %allocator, align 8, !dbg !298
  %7 = load %struct.lzma_filter*, %struct.lzma_filter** %options.addr, align 8, !dbg !298
  %call3 = call i32 @lzma_raw_decoder_init(%struct.lzma_next_coder_s* %next, %struct.lzma_allocator* %6, %struct.lzma_filter* %7), !dbg !298
  store i32 %call3, i32* %ret_, align 4, !dbg !298
  %8 = load i32, i32* %ret_, align 4, !dbg !298
  %cmp4 = icmp ne i32 %8, 0, !dbg !298
  br i1 %cmp4, label %if.then5, label %if.end6, !dbg !298

if.then5:                                         ; preds = %do.end
  %9 = load %struct.lzma_stream*, %struct.lzma_stream** %strm.addr, align 8, !dbg !300
  call void @lzma_end(%struct.lzma_stream* %9) #6, !dbg !300
  %10 = load i32, i32* %ret_, align 4, !dbg !300
  store i32 %10, i32* %retval, align 4, !dbg !300
  br label %return, !dbg !300

if.end6:                                          ; preds = %do.end
  br label %do.end7, !dbg !304

do.end7:                                          ; preds = %if.end6
  %11 = load %struct.lzma_stream*, %struct.lzma_stream** %strm.addr, align 8, !dbg !306
  %internal8 = getelementptr inbounds %struct.lzma_stream, %struct.lzma_stream* %11, i32 0, i32 7, !dbg !307
  %12 = load %struct.lzma_internal_s*, %struct.lzma_internal_s** %internal8, align 8, !dbg !307
  %supported_actions = getelementptr inbounds %struct.lzma_internal_s, %struct.lzma_internal_s* %12, i32 0, i32 3, !dbg !308
  %arrayidx = getelementptr inbounds [4 x i8], [4 x i8]* %supported_actions, i64 0, i64 0, !dbg !306
  store i8 1, i8* %arrayidx, align 8, !dbg !309
  %13 = load %struct.lzma_stream*, %struct.lzma_stream** %strm.addr, align 8, !dbg !310
  %internal9 = getelementptr inbounds %struct.lzma_stream, %struct.lzma_stream* %13, i32 0, i32 7, !dbg !311
  %14 = load %struct.lzma_internal_s*, %struct.lzma_internal_s** %internal9, align 8, !dbg !311
  %supported_actions10 = getelementptr inbounds %struct.lzma_internal_s, %struct.lzma_internal_s* %14, i32 0, i32 3, !dbg !312
  %arrayidx11 = getelementptr inbounds [4 x i8], [4 x i8]* %supported_actions10, i64 0, i64 3, !dbg !310
  store i8 1, i8* %arrayidx11, align 1, !dbg !313
  store i32 0, i32* %retval, align 4, !dbg !314
  br label %return, !dbg !314

return:                                           ; preds = %do.end7, %if.then5, %if.then
  %15 = load i32, i32* %retval, align 4, !dbg !315
  ret i32 %15, !dbg !315
}

declare i32 @lzma_strm_init(%struct.lzma_stream*) #3

; Function Attrs: nounwind
declare void @lzma_end(%struct.lzma_stream*) #4

; Function Attrs: nounwind readonly uwtable
define i64 @lzma_raw_decoder_memusage(%struct.lzma_filter* %filters) #5 !dbg !199 {
entry:
  %filters.addr = alloca %struct.lzma_filter*, align 8
  store %struct.lzma_filter* %filters, %struct.lzma_filter** %filters.addr, align 8
  call void @llvm.dbg.declare(metadata %struct.lzma_filter** %filters.addr, metadata !316, metadata !231), !dbg !317
  %0 = load %struct.lzma_filter*, %struct.lzma_filter** %filters.addr, align 8, !dbg !318
  %call = call i64 @lzma_raw_coder_memusage(%struct.lzma_filter_coder* (i64)* bitcast (%struct.lzma_filter_decoder* (i64)* @decoder_find to %struct.lzma_filter_coder* (i64)*), %struct.lzma_filter* %0), !dbg !319
  ret i64 %call, !dbg !320
}

declare i64 @lzma_raw_coder_memusage(%struct.lzma_filter_coder* (i64)*, %struct.lzma_filter*) #3

; Function Attrs: nounwind uwtable
define i32 @lzma_properties_decode(%struct.lzma_filter* %filter, %struct.lzma_allocator* %allocator, i8* %props, i64 %props_size) #2 !dbg !202 {
entry:
  %retval = alloca i32, align 4
  %filter.addr = alloca %struct.lzma_filter*, align 8
  %allocator.addr = alloca %struct.lzma_allocator*, align 8
  %props.addr = alloca i8*, align 8
  %props_size.addr = alloca i64, align 8
  %fd = alloca %struct.lzma_filter_decoder*, align 8
  store %struct.lzma_filter* %filter, %struct.lzma_filter** %filter.addr, align 8
  call void @llvm.dbg.declare(metadata %struct.lzma_filter** %filter.addr, metadata !321, metadata !231), !dbg !322
  store %struct.lzma_allocator* %allocator, %struct.lzma_allocator** %allocator.addr, align 8
  call void @llvm.dbg.declare(metadata %struct.lzma_allocator** %allocator.addr, metadata !323, metadata !231), !dbg !324
  store i8* %props, i8** %props.addr, align 8
  call void @llvm.dbg.declare(metadata i8** %props.addr, metadata !325, metadata !231), !dbg !326
  store i64 %props_size, i64* %props_size.addr, align 8
  call void @llvm.dbg.declare(metadata i64* %props_size.addr, metadata !327, metadata !231), !dbg !328
  call void @llvm.dbg.declare(metadata %struct.lzma_filter_decoder** %fd, metadata !329, metadata !231), !dbg !331
  %0 = load %struct.lzma_filter*, %struct.lzma_filter** %filter.addr, align 8, !dbg !332
  %id = getelementptr inbounds %struct.lzma_filter, %struct.lzma_filter* %0, i32 0, i32 0, !dbg !333
  %1 = load i64, i64* %id, align 8, !dbg !333
  %call = call %struct.lzma_filter_decoder* @decoder_find(i64 %1), !dbg !334
  store %struct.lzma_filter_decoder* %call, %struct.lzma_filter_decoder** %fd, align 8, !dbg !331
  %2 = load %struct.lzma_filter*, %struct.lzma_filter** %filter.addr, align 8, !dbg !335
  %options = getelementptr inbounds %struct.lzma_filter, %struct.lzma_filter* %2, i32 0, i32 1, !dbg !336
  store i8* null, i8** %options, align 8, !dbg !337
  %3 = load %struct.lzma_filter_decoder*, %struct.lzma_filter_decoder** %fd, align 8, !dbg !338
  %cmp = icmp eq %struct.lzma_filter_decoder* %3, null, !dbg !340
  br i1 %cmp, label %if.then, label %if.end, !dbg !341

if.then:                                          ; preds = %entry
  store i32 8, i32* %retval, align 4, !dbg !342
  br label %return, !dbg !342

if.end:                                           ; preds = %entry
  %4 = load %struct.lzma_filter_decoder*, %struct.lzma_filter_decoder** %fd, align 8, !dbg !343
  %props_decode = getelementptr inbounds %struct.lzma_filter_decoder, %struct.lzma_filter_decoder* %4, i32 0, i32 3, !dbg !345
  %5 = load i32 (i8**, %struct.lzma_allocator*, i8*, i64)*, i32 (i8**, %struct.lzma_allocator*, i8*, i64)** %props_decode, align 8, !dbg !345
  %cmp1 = icmp eq i32 (i8**, %struct.lzma_allocator*, i8*, i64)* %5, null, !dbg !346
  br i1 %cmp1, label %if.then2, label %if.end4, !dbg !347

if.then2:                                         ; preds = %if.end
  %6 = load i64, i64* %props_size.addr, align 8, !dbg !348
  %cmp3 = icmp eq i64 %6, 0, !dbg !349
  %cond = select i1 %cmp3, i32 0, i32 8, !dbg !348
  store i32 %cond, i32* %retval, align 4, !dbg !350
  br label %return, !dbg !350

if.end4:                                          ; preds = %if.end
  %7 = load %struct.lzma_filter_decoder*, %struct.lzma_filter_decoder** %fd, align 8, !dbg !351
  %props_decode5 = getelementptr inbounds %struct.lzma_filter_decoder, %struct.lzma_filter_decoder* %7, i32 0, i32 3, !dbg !352
  %8 = load i32 (i8**, %struct.lzma_allocator*, i8*, i64)*, i32 (i8**, %struct.lzma_allocator*, i8*, i64)** %props_decode5, align 8, !dbg !352
  %9 = load %struct.lzma_filter*, %struct.lzma_filter** %filter.addr, align 8, !dbg !353
  %options6 = getelementptr inbounds %struct.lzma_filter, %struct.lzma_filter* %9, i32 0, i32 1, !dbg !354
  %10 = load %struct.lzma_allocator*, %struct.lzma_allocator** %allocator.addr, align 8, !dbg !355
  %11 = load i8*, i8** %props.addr, align 8, !dbg !356
  %12 = load i64, i64* %props_size.addr, align 8, !dbg !357
  %call7 = call i32 %8(i8** %options6, %struct.lzma_allocator* %10, i8* %11, i64 %12), !dbg !351
  store i32 %call7, i32* %retval, align 4, !dbg !358
  br label %return, !dbg !358

return:                                           ; preds = %if.end4, %if.then2, %if.then
  %13 = load i32, i32* %retval, align 4, !dbg !359
  ret i32 %13, !dbg !359
}

declare i32 @lzma_lzma_decoder_init(%struct.lzma_next_coder_s*, %struct.lzma_allocator*, %struct.lzma_filter_info_s*) #3

declare i64 @lzma_lzma_decoder_memusage(i8*) #3

declare i32 @lzma_lzma_props_decode(i8**, %struct.lzma_allocator*, i8*, i64) #3

declare i32 @lzma_lzma2_decoder_init(%struct.lzma_next_coder_s*, %struct.lzma_allocator*, %struct.lzma_filter_info_s*) #3

declare i64 @lzma_lzma2_decoder_memusage(i8*) #3

declare i32 @lzma_lzma2_props_decode(i8**, %struct.lzma_allocator*, i8*, i64) #3

declare i32 @lzma_simple_x86_decoder_init(%struct.lzma_next_coder_s*, %struct.lzma_allocator*, %struct.lzma_filter_info_s*) #3

declare i32 @lzma_simple_props_decode(i8**, %struct.lzma_allocator*, i8*, i64) #3

declare i32 @lzma_simple_powerpc_decoder_init(%struct.lzma_next_coder_s*, %struct.lzma_allocator*, %struct.lzma_filter_info_s*) #3

declare i32 @lzma_simple_ia64_decoder_init(%struct.lzma_next_coder_s*, %struct.lzma_allocator*, %struct.lzma_filter_info_s*) #3

declare i32 @lzma_simple_arm_decoder_init(%struct.lzma_next_coder_s*, %struct.lzma_allocator*, %struct.lzma_filter_info_s*) #3

declare i32 @lzma_simple_armthumb_decoder_init(%struct.lzma_next_coder_s*, %struct.lzma_allocator*, %struct.lzma_filter_info_s*) #3

declare i32 @lzma_simple_sparc_decoder_init(%struct.lzma_next_coder_s*, %struct.lzma_allocator*, %struct.lzma_filter_info_s*) #3

declare i32 @lzma_delta_decoder_init(%struct.lzma_next_coder_s*, %struct.lzma_allocator*, %struct.lzma_filter_info_s*) #3

declare i64 @lzma_delta_coder_memusage(i8*) #3

declare i32 @lzma_delta_props_decode(i8**, %struct.lzma_allocator*, i8*, i64) #3

attributes #0 = { nounwind readnone uwtable "disable-tail-calls"="false" "less-precise-fpmad"="false" "no-frame-pointer-elim"="true" "no-frame-pointer-elim-non-leaf" "no-infs-fp-math"="false" "no-nans-fp-math"="false" "stack-protector-buffer-size"="8" "target-cpu"="x86-64" "target-features"="+fxsr,+mmx,+sse,+sse2" "unsafe-fp-math"="false" "use-soft-float"="false" }
attributes #1 = { nounwind readnone }
attributes #2 = { nounwind uwtable "disable-tail-calls"="false" "less-precise-fpmad"="false" "no-frame-pointer-elim"="true" "no-frame-pointer-elim-non-leaf" "no-infs-fp-math"="false" "no-nans-fp-math"="false" "stack-protector-buffer-size"="8" "target-cpu"="x86-64" "target-features"="+fxsr,+mmx,+sse,+sse2" "unsafe-fp-math"="false" "use-soft-float"="false" }
attributes #3 = { "disable-tail-calls"="false" "less-precise-fpmad"="false" "no-frame-pointer-elim"="true" "no-frame-pointer-elim-non-leaf" "no-infs-fp-math"="false" "no-nans-fp-math"="false" "stack-protector-buffer-size"="8" "target-cpu"="x86-64" "target-features"="+fxsr,+mmx,+sse,+sse2" "unsafe-fp-math"="false" "use-soft-float"="false" }
attributes #4 = { nounwind "disable-tail-calls"="false" "less-precise-fpmad"="false" "no-frame-pointer-elim"="true" "no-frame-pointer-elim-non-leaf" "no-infs-fp-math"="false" "no-nans-fp-math"="false" "stack-protector-buffer-size"="8" "target-cpu"="x86-64" "target-features"="+fxsr,+mmx,+sse,+sse2" "unsafe-fp-math"="false" "use-soft-float"="false" }
attributes #5 = { nounwind readonly uwtable "disable-tail-calls"="false" "less-precise-fpmad"="false" "no-frame-pointer-elim"="true" "no-frame-pointer-elim-non-leaf" "no-infs-fp-math"="false" "no-nans-fp-math"="false" "stack-protector-buffer-size"="8" "target-cpu"="x86-64" "target-features"="+fxsr,+mmx,+sse,+sse2" "unsafe-fp-math"="false" "use-soft-float"="false" }
attributes #6 = { nounwind }

!llvm.dbg.cu = !{!0}
!llvm.module.flags = !{!227, !228}
!llvm.ident = !{!229}

!0 = distinct !DICompileUnit(language: DW_LANG_C99, file: !1, producer: "clang version 3.8.0 (tags/RELEASE_380/final)", isOptimized: false, runtimeVersion: 0, emissionKind: 1, enums: !2, retainedTypes: !130, subprograms: !162, globals: !222)
!1 = !DIFile(filename: "/data/download/cmake/cmake-master/Utilities/cmliblzma/liblzma/common/filter_decoder.c", directory: "/data/download/cmake/cmake-master/Utilities/cmliblzma")
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
!162 = !{!163, !168, !171, !199, !202, !206}
!163 = distinct !DISubprogram(name: "lzma_filter_decoder_is_supported", scope: !1, file: !1, line: 133, type: !164, isLocal: false, isDefinition: true, scopeLine: 134, flags: DIFlagPrototyped, isOptimized: false, variables: !167)
!164 = !DISubroutineType(types: !165)
!165 = !{!166, !44}
!166 = !DIDerivedType(tag: DW_TAG_typedef, name: "lzma_bool", file: !4, line: 29, baseType: !77)
!167 = !{}
!168 = distinct !DISubprogram(name: "lzma_raw_decoder_init", scope: !1, file: !1, line: 140, type: !169, isLocal: false, isDefinition: true, scopeLine: 142, flags: DIFlagPrototyped, isOptimized: false, variables: !167)
!169 = !DISubroutineType(types: !170)
!170 = !{!56, !147, !57, !104}
!171 = distinct !DISubprogram(name: "lzma_raw_decoder", scope: !1, file: !1, line: 149, type: !172, isLocal: false, isDefinition: true, scopeLine: 150, flags: DIFlagPrototyped, isOptimized: false, variables: !167)
!172 = !DISubroutineType(types: !173)
!173 = !{!56, !174, !104}
!174 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !175, size: 64, align: 64)
!175 = !DIDerivedType(tag: DW_TAG_typedef, name: "lzma_stream", file: !4, line: 490, baseType: !176)
!176 = !DICompositeType(tag: DW_TAG_structure_type, file: !4, line: 453, size: 1088, align: 64, elements: !177)
!177 = !{!178, !179, !180, !181, !182, !183, !184, !185, !188, !189, !190, !191, !192, !193, !194, !195, !196, !198}
!178 = !DIDerivedType(tag: DW_TAG_member, name: "next_in", scope: !176, file: !4, line: 454, baseType: !74, size: 64, align: 64)
!179 = !DIDerivedType(tag: DW_TAG_member, name: "avail_in", scope: !176, file: !4, line: 455, baseType: !66, size: 64, align: 64, offset: 64)
!180 = !DIDerivedType(tag: DW_TAG_member, name: "total_in", scope: !176, file: !4, line: 456, baseType: !46, size: 64, align: 64, offset: 128)
!181 = !DIDerivedType(tag: DW_TAG_member, name: "next_out", scope: !176, file: !4, line: 458, baseType: !81, size: 64, align: 64, offset: 192)
!182 = !DIDerivedType(tag: DW_TAG_member, name: "avail_out", scope: !176, file: !4, line: 459, baseType: !66, size: 64, align: 64, offset: 256)
!183 = !DIDerivedType(tag: DW_TAG_member, name: "total_out", scope: !176, file: !4, line: 460, baseType: !46, size: 64, align: 64, offset: 320)
!184 = !DIDerivedType(tag: DW_TAG_member, name: "allocator", scope: !176, file: !4, line: 468, baseType: !57, size: 64, align: 64, offset: 384)
!185 = !DIDerivedType(tag: DW_TAG_member, name: "internal", scope: !176, file: !4, line: 471, baseType: !186, size: 64, align: 64, offset: 448)
!186 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !187, size: 64, align: 64)
!187 = !DIDerivedType(tag: DW_TAG_typedef, name: "lzma_internal", file: !4, line: 411, baseType: !33)
!188 = !DIDerivedType(tag: DW_TAG_member, name: "reserved_ptr1", scope: !176, file: !4, line: 479, baseType: !65, size: 64, align: 64, offset: 512)
!189 = !DIDerivedType(tag: DW_TAG_member, name: "reserved_ptr2", scope: !176, file: !4, line: 480, baseType: !65, size: 64, align: 64, offset: 576)
!190 = !DIDerivedType(tag: DW_TAG_member, name: "reserved_ptr3", scope: !176, file: !4, line: 481, baseType: !65, size: 64, align: 64, offset: 640)
!191 = !DIDerivedType(tag: DW_TAG_member, name: "reserved_ptr4", scope: !176, file: !4, line: 482, baseType: !65, size: 64, align: 64, offset: 704)
!192 = !DIDerivedType(tag: DW_TAG_member, name: "reserved_int1", scope: !176, file: !4, line: 483, baseType: !46, size: 64, align: 64, offset: 768)
!193 = !DIDerivedType(tag: DW_TAG_member, name: "reserved_int2", scope: !176, file: !4, line: 484, baseType: !46, size: 64, align: 64, offset: 832)
!194 = !DIDerivedType(tag: DW_TAG_member, name: "reserved_int3", scope: !176, file: !4, line: 485, baseType: !66, size: 64, align: 64, offset: 896)
!195 = !DIDerivedType(tag: DW_TAG_member, name: "reserved_int4", scope: !176, file: !4, line: 486, baseType: !66, size: 64, align: 64, offset: 960)
!196 = !DIDerivedType(tag: DW_TAG_member, name: "reserved_enum1", scope: !176, file: !4, line: 487, baseType: !197, size: 32, align: 32, offset: 1024)
!197 = !DIDerivedType(tag: DW_TAG_typedef, name: "lzma_reserved_enum", file: !4, line: 46, baseType: !127)
!198 = !DIDerivedType(tag: DW_TAG_member, name: "reserved_enum2", scope: !176, file: !4, line: 488, baseType: !197, size: 32, align: 32, offset: 1056)
!199 = distinct !DISubprogram(name: "lzma_raw_decoder_memusage", scope: !1, file: !1, line: 161, type: !200, isLocal: false, isDefinition: true, scopeLine: 162, flags: DIFlagPrototyped, isOptimized: false, variables: !167)
!200 = !DISubroutineType(types: !201)
!201 = !{!46, !104}
!202 = distinct !DISubprogram(name: "lzma_properties_decode", scope: !1, file: !1, line: 169, type: !203, isLocal: false, isDefinition: true, scopeLine: 171, flags: DIFlagPrototyped, isOptimized: false, variables: !167)
!203 = !DISubroutineType(types: !204)
!204 = !{!56, !205, !57, !74, !66}
!205 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !106, size: 64, align: 64)
!206 = distinct !DISubprogram(name: "decoder_find", scope: !1, file: !1, line: 121, type: !207, isLocal: true, isDefinition: true, scopeLine: 122, flags: DIFlagPrototyped, isOptimized: false, variables: !167)
!207 = !DISubroutineType(types: !208)
!208 = !{!209, !44}
!209 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !210, size: 64, align: 64)
!210 = !DIDerivedType(tag: DW_TAG_const_type, baseType: !211)
!211 = !DIDerivedType(tag: DW_TAG_typedef, name: "lzma_filter_decoder", file: !1, line: 41, baseType: !212)
!212 = !DICompositeType(tag: DW_TAG_structure_type, file: !1, line: 21, size: 256, align: 64, elements: !213)
!213 = !{!214, !215, !216, !217}
!214 = !DIDerivedType(tag: DW_TAG_member, name: "id", scope: !212, file: !1, line: 23, baseType: !44, size: 64, align: 64)
!215 = !DIDerivedType(tag: DW_TAG_member, name: "init", scope: !212, file: !1, line: 27, baseType: !143, size: 64, align: 64, offset: 64)
!216 = !DIDerivedType(tag: DW_TAG_member, name: "memusage", scope: !212, file: !1, line: 31, baseType: !157, size: 64, align: 64, offset: 128)
!217 = !DIDerivedType(tag: DW_TAG_member, name: "props_decode", scope: !212, file: !1, line: 38, baseType: !218, size: 64, align: 64, offset: 192)
!218 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !219, size: 64, align: 64)
!219 = !DISubroutineType(types: !220)
!220 = !{!56, !221, !57, !74, !66}
!221 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !65, size: 64, align: 64)
!222 = !{!223}
!223 = !DIGlobalVariable(name: "decoders", scope: !0, file: !1, line: 44, type: !224, isLocal: true, isDefinition: true, variable: [9 x %struct.lzma_filter_decoder]* @decoders)
!224 = !DICompositeType(tag: DW_TAG_array_type, baseType: !210, size: 2304, align: 64, elements: !225)
!225 = !{!226}
!226 = !DISubrange(count: 9)
!227 = !{i32 2, !"Dwarf Version", i32 4}
!228 = !{i32 2, !"Debug Info Version", i32 3}
!229 = !{!"clang version 3.8.0 (tags/RELEASE_380/final)"}
!230 = !DILocalVariable(name: "id", arg: 1, scope: !163, file: !1, line: 133, type: !44)
!231 = !DIExpression()
!232 = !DILocation(line: 133, column: 43, scope: !163)
!233 = !DILocation(line: 135, column: 22, scope: !163)
!234 = !DILocation(line: 135, column: 9, scope: !163)
!235 = !DILocation(line: 135, column: 26, scope: !163)
!236 = !DILocation(line: 135, column: 2, scope: !163)
!237 = !DILocalVariable(name: "id", arg: 1, scope: !206, file: !1, line: 121, type: !44)
!238 = !DILocation(line: 121, column: 23, scope: !206)
!239 = !DILocalVariable(name: "i", scope: !206, file: !1, line: 123, type: !66)
!240 = !DILocation(line: 123, column: 9, scope: !206)
!241 = !DILocation(line: 124, column: 9, scope: !242)
!242 = distinct !DILexicalBlock(scope: !206, file: !1, line: 124, column: 2)
!243 = !DILocation(line: 124, column: 7, scope: !242)
!244 = !DILocation(line: 124, column: 14, scope: !245)
!245 = !DILexicalBlockFile(scope: !246, file: !1, discriminator: 1)
!246 = distinct !DILexicalBlock(scope: !242, file: !1, line: 124, column: 2)
!247 = !DILocation(line: 124, column: 16, scope: !245)
!248 = !DILocation(line: 124, column: 2, scope: !245)
!249 = !DILocation(line: 125, column: 16, scope: !250)
!250 = distinct !DILexicalBlock(scope: !246, file: !1, line: 125, column: 7)
!251 = !DILocation(line: 125, column: 7, scope: !250)
!252 = !DILocation(line: 125, column: 19, scope: !250)
!253 = !DILocation(line: 125, column: 25, scope: !250)
!254 = !DILocation(line: 125, column: 22, scope: !250)
!255 = !DILocation(line: 125, column: 7, scope: !246)
!256 = !DILocation(line: 126, column: 22, scope: !250)
!257 = !DILocation(line: 126, column: 20, scope: !250)
!258 = !DILocation(line: 126, column: 4, scope: !250)
!259 = !DILocation(line: 125, column: 25, scope: !260)
!260 = !DILexicalBlockFile(scope: !250, file: !1, discriminator: 1)
!261 = !DILocation(line: 124, column: 40, scope: !262)
!262 = !DILexicalBlockFile(scope: !246, file: !1, discriminator: 2)
!263 = !DILocation(line: 124, column: 2, scope: !262)
!264 = !DILocation(line: 128, column: 2, scope: !206)
!265 = !DILocation(line: 129, column: 1, scope: !206)
!266 = !DILocalVariable(name: "next", arg: 1, scope: !168, file: !1, line: 140, type: !147)
!267 = !DILocation(line: 140, column: 40, scope: !168)
!268 = !DILocalVariable(name: "allocator", arg: 2, scope: !168, file: !1, line: 140, type: !57)
!269 = !DILocation(line: 140, column: 62, scope: !168)
!270 = !DILocalVariable(name: "options", arg: 3, scope: !168, file: !1, line: 141, type: !104)
!271 = !DILocation(line: 141, column: 22, scope: !168)
!272 = !DILocation(line: 143, column: 29, scope: !168)
!273 = !DILocation(line: 143, column: 35, scope: !168)
!274 = !DILocation(line: 144, column: 4, scope: !168)
!275 = !DILocation(line: 143, column: 9, scope: !168)
!276 = !DILocation(line: 143, column: 2, scope: !168)
!277 = !DILocalVariable(name: "strm", arg: 1, scope: !171, file: !1, line: 149, type: !174)
!278 = !DILocation(line: 149, column: 31, scope: !171)
!279 = !DILocalVariable(name: "options", arg: 2, scope: !171, file: !1, line: 149, type: !104)
!280 = !DILocation(line: 149, column: 56, scope: !171)
!281 = !DILocation(line: 151, column: 2, scope: !171)
!282 = !DILocalVariable(name: "ret_", scope: !283, file: !1, line: 151, type: !56)
!283 = distinct !DILexicalBlock(scope: !171, file: !1, line: 151, column: 2)
!284 = !DILocation(line: 151, column: 2, scope: !283)
!285 = !DILocation(line: 151, column: 2, scope: !286)
!286 = !DILexicalBlockFile(scope: !283, file: !1, discriminator: 1)
!287 = !DILocalVariable(name: "ret_", scope: !288, file: !1, line: 151, type: !289)
!288 = distinct !DILexicalBlock(scope: !283, file: !1, line: 151, column: 2)
!289 = !DIDerivedType(tag: DW_TAG_const_type, baseType: !56)
!290 = !DILocation(line: 151, column: 2, scope: !288)
!291 = !DILocation(line: 151, column: 2, scope: !292)
!292 = !DILexicalBlockFile(scope: !288, file: !1, discriminator: 2)
!293 = !DILocation(line: 151, column: 2, scope: !294)
!294 = !DILexicalBlockFile(scope: !295, file: !1, discriminator: 3)
!295 = distinct !DILexicalBlock(scope: !288, file: !1, line: 151, column: 2)
!296 = !DILocation(line: 151, column: 2, scope: !297)
!297 = !DILexicalBlockFile(scope: !288, file: !1, discriminator: 4)
!298 = !DILocation(line: 151, column: 2, scope: !299)
!299 = !DILexicalBlockFile(scope: !283, file: !1, discriminator: 5)
!300 = !DILocation(line: 151, column: 2, scope: !301)
!301 = !DILexicalBlockFile(scope: !302, file: !1, discriminator: 6)
!302 = distinct !DILexicalBlock(scope: !303, file: !1, line: 151, column: 2)
!303 = distinct !DILexicalBlock(scope: !283, file: !1, line: 151, column: 2)
!304 = !DILocation(line: 151, column: 2, scope: !305)
!305 = !DILexicalBlockFile(scope: !283, file: !1, discriminator: 7)
!306 = !DILocation(line: 153, column: 2, scope: !171)
!307 = !DILocation(line: 153, column: 8, scope: !171)
!308 = !DILocation(line: 153, column: 18, scope: !171)
!309 = !DILocation(line: 153, column: 46, scope: !171)
!310 = !DILocation(line: 154, column: 2, scope: !171)
!311 = !DILocation(line: 154, column: 8, scope: !171)
!312 = !DILocation(line: 154, column: 18, scope: !171)
!313 = !DILocation(line: 154, column: 49, scope: !171)
!314 = !DILocation(line: 156, column: 2, scope: !171)
!315 = !DILocation(line: 157, column: 1, scope: !171)
!316 = !DILocalVariable(name: "filters", arg: 1, scope: !199, file: !1, line: 161, type: !104)
!317 = !DILocation(line: 161, column: 46, scope: !199)
!318 = !DILocation(line: 164, column: 39, scope: !199)
!319 = !DILocation(line: 163, column: 9, scope: !199)
!320 = !DILocation(line: 163, column: 2, scope: !199)
!321 = !DILocalVariable(name: "filter", arg: 1, scope: !202, file: !1, line: 169, type: !205)
!322 = !DILocation(line: 169, column: 37, scope: !202)
!323 = !DILocalVariable(name: "allocator", arg: 2, scope: !202, file: !1, line: 169, type: !57)
!324 = !DILocation(line: 169, column: 61, scope: !202)
!325 = !DILocalVariable(name: "props", arg: 3, scope: !202, file: !1, line: 170, type: !74)
!326 = !DILocation(line: 170, column: 18, scope: !202)
!327 = !DILocalVariable(name: "props_size", arg: 4, scope: !202, file: !1, line: 170, type: !66)
!328 = !DILocation(line: 170, column: 32, scope: !202)
!329 = !DILocalVariable(name: "fd", scope: !202, file: !1, line: 172, type: !330)
!330 = !DIDerivedType(tag: DW_TAG_const_type, baseType: !209)
!331 = !DILocation(line: 172, column: 35, scope: !202)
!332 = !DILocation(line: 172, column: 53, scope: !202)
!333 = !DILocation(line: 172, column: 61, scope: !202)
!334 = !DILocation(line: 172, column: 40, scope: !202)
!335 = !DILocation(line: 175, column: 2, scope: !202)
!336 = !DILocation(line: 175, column: 10, scope: !202)
!337 = !DILocation(line: 175, column: 18, scope: !202)
!338 = !DILocation(line: 177, column: 6, scope: !339)
!339 = distinct !DILexicalBlock(scope: !202, file: !1, line: 177, column: 6)
!340 = !DILocation(line: 177, column: 9, scope: !339)
!341 = !DILocation(line: 177, column: 6, scope: !202)
!342 = !DILocation(line: 178, column: 3, scope: !339)
!343 = !DILocation(line: 180, column: 6, scope: !344)
!344 = distinct !DILexicalBlock(scope: !202, file: !1, line: 180, column: 6)
!345 = !DILocation(line: 180, column: 10, scope: !344)
!346 = !DILocation(line: 180, column: 23, scope: !344)
!347 = !DILocation(line: 180, column: 6, scope: !202)
!348 = !DILocation(line: 181, column: 10, scope: !344)
!349 = !DILocation(line: 181, column: 21, scope: !344)
!350 = !DILocation(line: 181, column: 3, scope: !344)
!351 = !DILocation(line: 183, column: 9, scope: !202)
!352 = !DILocation(line: 183, column: 13, scope: !202)
!353 = !DILocation(line: 184, column: 5, scope: !202)
!354 = !DILocation(line: 184, column: 13, scope: !202)
!355 = !DILocation(line: 184, column: 22, scope: !202)
!356 = !DILocation(line: 184, column: 33, scope: !202)
!357 = !DILocation(line: 184, column: 40, scope: !202)
!358 = !DILocation(line: 183, column: 2, scope: !202)
!359 = !DILocation(line: 185, column: 1, scope: !202)
