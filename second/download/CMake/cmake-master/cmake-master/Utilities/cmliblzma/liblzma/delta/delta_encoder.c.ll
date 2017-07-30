; ModuleID = '/data/download/cmake/cmake-master/Utilities/cmliblzma/liblzma/delta/delta_encoder.c'
target datalayout = "e-m:e-i64:64-f80:128-n8:16:32:64-S128"
target triple = "x86_64-unknown-linux-gnu"

%struct.lzma_next_coder_s = type { %struct.lzma_coder_s*, i64, i64, i32 (%struct.lzma_coder_s*, %struct.lzma_allocator*, i8*, i64*, i64, i8*, i64*, i64, i32)*, void (%struct.lzma_coder_s*, %struct.lzma_allocator*)*, i32 (%struct.lzma_coder_s*)*, i32 (%struct.lzma_coder_s*, i64*, i64*, i64)*, i32 (%struct.lzma_coder_s*, %struct.lzma_allocator*, %struct.lzma_filter*, %struct.lzma_filter*)* }
%struct.lzma_coder_s = type { %struct.lzma_next_coder_s, i64, i8, [256 x i8] }
%struct.lzma_filter = type { i64, i8* }
%struct.lzma_allocator = type { i8* (i8*, i64, i64)*, void (i8*, i8*)*, i8* }
%struct.lzma_filter_info_s = type { i64, {}*, i8* }
%struct.lzma_options_delta = type { i32, i32, i32, i32, i32, i32, i8*, i8* }

; Function Attrs: nounwind uwtable
define i32 @lzma_delta_encoder_init(%struct.lzma_next_coder_s* %next, %struct.lzma_allocator* %allocator, %struct.lzma_filter_info_s* %filters) #0 !dbg !38 {
entry:
  %next.addr = alloca %struct.lzma_next_coder_s*, align 8
  %allocator.addr = alloca %struct.lzma_allocator*, align 8
  %filters.addr = alloca %struct.lzma_filter_info_s*, align 8
  store %struct.lzma_next_coder_s* %next, %struct.lzma_next_coder_s** %next.addr, align 8
  call void @llvm.dbg.declare(metadata %struct.lzma_next_coder_s** %next.addr, metadata !154, metadata !155), !dbg !156
  store %struct.lzma_allocator* %allocator, %struct.lzma_allocator** %allocator.addr, align 8
  call void @llvm.dbg.declare(metadata %struct.lzma_allocator** %allocator.addr, metadata !157, metadata !155), !dbg !158
  store %struct.lzma_filter_info_s* %filters, %struct.lzma_filter_info_s** %filters.addr, align 8
  call void @llvm.dbg.declare(metadata %struct.lzma_filter_info_s** %filters.addr, metadata !159, metadata !155), !dbg !160
  %0 = load %struct.lzma_next_coder_s*, %struct.lzma_next_coder_s** %next.addr, align 8, !dbg !161
  %code = getelementptr inbounds %struct.lzma_next_coder_s, %struct.lzma_next_coder_s* %0, i32 0, i32 3, !dbg !162
  store i32 (%struct.lzma_coder_s*, %struct.lzma_allocator*, i8*, i64*, i64, i8*, i64*, i64, i32)* @delta_encode, i32 (%struct.lzma_coder_s*, %struct.lzma_allocator*, i8*, i64*, i64, i8*, i64*, i64, i32)** %code, align 8, !dbg !163
  %1 = load %struct.lzma_next_coder_s*, %struct.lzma_next_coder_s** %next.addr, align 8, !dbg !164
  %update = getelementptr inbounds %struct.lzma_next_coder_s, %struct.lzma_next_coder_s* %1, i32 0, i32 7, !dbg !165
  store i32 (%struct.lzma_coder_s*, %struct.lzma_allocator*, %struct.lzma_filter*, %struct.lzma_filter*)* @delta_encoder_update, i32 (%struct.lzma_coder_s*, %struct.lzma_allocator*, %struct.lzma_filter*, %struct.lzma_filter*)** %update, align 8, !dbg !166
  %2 = load %struct.lzma_next_coder_s*, %struct.lzma_next_coder_s** %next.addr, align 8, !dbg !167
  %3 = load %struct.lzma_allocator*, %struct.lzma_allocator** %allocator.addr, align 8, !dbg !168
  %4 = load %struct.lzma_filter_info_s*, %struct.lzma_filter_info_s** %filters.addr, align 8, !dbg !169
  %call = call i32 @lzma_delta_coder_init(%struct.lzma_next_coder_s* %2, %struct.lzma_allocator* %3, %struct.lzma_filter_info_s* %4), !dbg !170
  ret i32 %call, !dbg !171
}

; Function Attrs: nounwind readnone
declare void @llvm.dbg.declare(metadata, metadata, metadata) #1

; Function Attrs: nounwind uwtable
define internal i32 @delta_encode(%struct.lzma_coder_s* %coder, %struct.lzma_allocator* %allocator, i8* noalias %in, i64* noalias %in_pos, i64 %in_size, i8* noalias %out, i64* noalias %out_pos, i64 %out_size, i32 %action) #0 !dbg !143 {
entry:
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
  %in_avail = alloca i64, align 8
  %out_avail = alloca i64, align 8
  %size = alloca i64, align 8
  %out_start = alloca i64, align 8
  store %struct.lzma_coder_s* %coder, %struct.lzma_coder_s** %coder.addr, align 8
  call void @llvm.dbg.declare(metadata %struct.lzma_coder_s** %coder.addr, metadata !172, metadata !155), !dbg !173
  store %struct.lzma_allocator* %allocator, %struct.lzma_allocator** %allocator.addr, align 8
  call void @llvm.dbg.declare(metadata %struct.lzma_allocator** %allocator.addr, metadata !174, metadata !155), !dbg !175
  store i8* %in, i8** %in.addr, align 8
  call void @llvm.dbg.declare(metadata i8** %in.addr, metadata !176, metadata !155), !dbg !177
  store i64* %in_pos, i64** %in_pos.addr, align 8
  call void @llvm.dbg.declare(metadata i64** %in_pos.addr, metadata !178, metadata !155), !dbg !179
  store i64 %in_size, i64* %in_size.addr, align 8
  call void @llvm.dbg.declare(metadata i64* %in_size.addr, metadata !180, metadata !155), !dbg !181
  store i8* %out, i8** %out.addr, align 8
  call void @llvm.dbg.declare(metadata i8** %out.addr, metadata !182, metadata !155), !dbg !183
  store i64* %out_pos, i64** %out_pos.addr, align 8
  call void @llvm.dbg.declare(metadata i64** %out_pos.addr, metadata !184, metadata !155), !dbg !185
  store i64 %out_size, i64* %out_size.addr, align 8
  call void @llvm.dbg.declare(metadata i64* %out_size.addr, metadata !186, metadata !155), !dbg !187
  store i32 %action, i32* %action.addr, align 4
  call void @llvm.dbg.declare(metadata i32* %action.addr, metadata !188, metadata !155), !dbg !189
  call void @llvm.dbg.declare(metadata i32* %ret, metadata !190, metadata !155), !dbg !191
  %0 = load %struct.lzma_coder_s*, %struct.lzma_coder_s** %coder.addr, align 8, !dbg !192
  %next = getelementptr inbounds %struct.lzma_coder_s, %struct.lzma_coder_s* %0, i32 0, i32 0, !dbg !194
  %code = getelementptr inbounds %struct.lzma_next_coder_s, %struct.lzma_next_coder_s* %next, i32 0, i32 3, !dbg !195
  %1 = load i32 (%struct.lzma_coder_s*, %struct.lzma_allocator*, i8*, i64*, i64, i8*, i64*, i64, i32)*, i32 (%struct.lzma_coder_s*, %struct.lzma_allocator*, i8*, i64*, i64, i8*, i64*, i64, i32)** %code, align 8, !dbg !195
  %cmp = icmp eq i32 (%struct.lzma_coder_s*, %struct.lzma_allocator*, i8*, i64*, i64, i8*, i64*, i64, i32)* %1, null, !dbg !196
  br i1 %cmp, label %if.then, label %if.else, !dbg !197

if.then:                                          ; preds = %entry
  call void @llvm.dbg.declare(metadata i64* %in_avail, metadata !198, metadata !155), !dbg !201
  %2 = load i64, i64* %in_size.addr, align 8, !dbg !202
  %3 = load i64*, i64** %in_pos.addr, align 8, !dbg !203
  %4 = load i64, i64* %3, align 8, !dbg !204
  %sub = sub i64 %2, %4, !dbg !205
  store i64 %sub, i64* %in_avail, align 8, !dbg !201
  call void @llvm.dbg.declare(metadata i64* %out_avail, metadata !206, metadata !155), !dbg !207
  %5 = load i64, i64* %out_size.addr, align 8, !dbg !208
  %6 = load i64*, i64** %out_pos.addr, align 8, !dbg !209
  %7 = load i64, i64* %6, align 8, !dbg !210
  %sub1 = sub i64 %5, %7, !dbg !211
  store i64 %sub1, i64* %out_avail, align 8, !dbg !207
  call void @llvm.dbg.declare(metadata i64* %size, metadata !212, metadata !155), !dbg !213
  %8 = load i64, i64* %in_avail, align 8, !dbg !214
  %9 = load i64, i64* %out_avail, align 8, !dbg !214
  %cmp2 = icmp ult i64 %8, %9, !dbg !214
  br i1 %cmp2, label %cond.true, label %cond.false, !dbg !214

cond.true:                                        ; preds = %if.then
  %10 = load i64, i64* %in_avail, align 8, !dbg !215
  br label %cond.end, !dbg !215

cond.false:                                       ; preds = %if.then
  %11 = load i64, i64* %out_avail, align 8, !dbg !217
  br label %cond.end, !dbg !217

cond.end:                                         ; preds = %cond.false, %cond.true
  %cond = phi i64 [ %10, %cond.true ], [ %11, %cond.false ], !dbg !219
  store i64 %cond, i64* %size, align 8, !dbg !221
  %12 = load %struct.lzma_coder_s*, %struct.lzma_coder_s** %coder.addr, align 8, !dbg !222
  %13 = load i8*, i8** %in.addr, align 8, !dbg !223
  %14 = load i64*, i64** %in_pos.addr, align 8, !dbg !224
  %15 = load i64, i64* %14, align 8, !dbg !225
  %add.ptr = getelementptr inbounds i8, i8* %13, i64 %15, !dbg !226
  %16 = load i8*, i8** %out.addr, align 8, !dbg !227
  %17 = load i64*, i64** %out_pos.addr, align 8, !dbg !228
  %18 = load i64, i64* %17, align 8, !dbg !229
  %add.ptr3 = getelementptr inbounds i8, i8* %16, i64 %18, !dbg !230
  %19 = load i64, i64* %size, align 8, !dbg !231
  call void @copy_and_encode(%struct.lzma_coder_s* %12, i8* %add.ptr, i8* %add.ptr3, i64 %19), !dbg !232
  %20 = load i64, i64* %size, align 8, !dbg !233
  %21 = load i64*, i64** %in_pos.addr, align 8, !dbg !234
  %22 = load i64, i64* %21, align 8, !dbg !235
  %add = add i64 %22, %20, !dbg !235
  store i64 %add, i64* %21, align 8, !dbg !235
  %23 = load i64, i64* %size, align 8, !dbg !236
  %24 = load i64*, i64** %out_pos.addr, align 8, !dbg !237
  %25 = load i64, i64* %24, align 8, !dbg !238
  %add4 = add i64 %25, %23, !dbg !238
  store i64 %add4, i64* %24, align 8, !dbg !238
  %26 = load i32, i32* %action.addr, align 4, !dbg !239
  %cmp5 = icmp ne i32 %26, 0, !dbg !240
  br i1 %cmp5, label %land.rhs, label %land.end, !dbg !241

land.rhs:                                         ; preds = %cond.end
  %27 = load i64*, i64** %in_pos.addr, align 8, !dbg !242
  %28 = load i64, i64* %27, align 8, !dbg !243
  %29 = load i64, i64* %in_size.addr, align 8, !dbg !244
  %cmp6 = icmp eq i64 %28, %29, !dbg !245
  br label %land.end

land.end:                                         ; preds = %land.rhs, %cond.end
  %30 = phi i1 [ false, %cond.end ], [ %cmp6, %land.rhs ]
  %cond7 = select i1 %30, i32 1, i32 0, !dbg !246
  store i32 %cond7, i32* %ret, align 4, !dbg !247
  br label %if.end, !dbg !248

if.else:                                          ; preds = %entry
  call void @llvm.dbg.declare(metadata i64* %out_start, metadata !249, metadata !155), !dbg !251
  %31 = load i64*, i64** %out_pos.addr, align 8, !dbg !252
  %32 = load i64, i64* %31, align 8, !dbg !253
  store i64 %32, i64* %out_start, align 8, !dbg !251
  %33 = load %struct.lzma_coder_s*, %struct.lzma_coder_s** %coder.addr, align 8, !dbg !254
  %next8 = getelementptr inbounds %struct.lzma_coder_s, %struct.lzma_coder_s* %33, i32 0, i32 0, !dbg !255
  %code9 = getelementptr inbounds %struct.lzma_next_coder_s, %struct.lzma_next_coder_s* %next8, i32 0, i32 3, !dbg !256
  %34 = load i32 (%struct.lzma_coder_s*, %struct.lzma_allocator*, i8*, i64*, i64, i8*, i64*, i64, i32)*, i32 (%struct.lzma_coder_s*, %struct.lzma_allocator*, i8*, i64*, i64, i8*, i64*, i64, i32)** %code9, align 8, !dbg !256
  %35 = load %struct.lzma_coder_s*, %struct.lzma_coder_s** %coder.addr, align 8, !dbg !257
  %next10 = getelementptr inbounds %struct.lzma_coder_s, %struct.lzma_coder_s* %35, i32 0, i32 0, !dbg !258
  %coder11 = getelementptr inbounds %struct.lzma_next_coder_s, %struct.lzma_next_coder_s* %next10, i32 0, i32 0, !dbg !259
  %36 = load %struct.lzma_coder_s*, %struct.lzma_coder_s** %coder11, align 8, !dbg !259
  %37 = load %struct.lzma_allocator*, %struct.lzma_allocator** %allocator.addr, align 8, !dbg !260
  %38 = load i8*, i8** %in.addr, align 8, !dbg !261
  %39 = load i64*, i64** %in_pos.addr, align 8, !dbg !262
  %40 = load i64, i64* %in_size.addr, align 8, !dbg !263
  %41 = load i8*, i8** %out.addr, align 8, !dbg !264
  %42 = load i64*, i64** %out_pos.addr, align 8, !dbg !265
  %43 = load i64, i64* %out_size.addr, align 8, !dbg !266
  %44 = load i32, i32* %action.addr, align 4, !dbg !267
  %call = call i32 %34(%struct.lzma_coder_s* %36, %struct.lzma_allocator* %37, i8* %38, i64* %39, i64 %40, i8* %41, i64* %42, i64 %43, i32 %44), !dbg !254
  store i32 %call, i32* %ret, align 4, !dbg !268
  %45 = load %struct.lzma_coder_s*, %struct.lzma_coder_s** %coder.addr, align 8, !dbg !269
  %46 = load i8*, i8** %out.addr, align 8, !dbg !270
  %47 = load i64, i64* %out_start, align 8, !dbg !271
  %add.ptr12 = getelementptr inbounds i8, i8* %46, i64 %47, !dbg !272
  %48 = load i64*, i64** %out_pos.addr, align 8, !dbg !273
  %49 = load i64, i64* %48, align 8, !dbg !274
  %50 = load i64, i64* %out_start, align 8, !dbg !275
  %sub13 = sub i64 %49, %50, !dbg !276
  call void @encode_in_place(%struct.lzma_coder_s* %45, i8* %add.ptr12, i64 %sub13), !dbg !277
  br label %if.end

if.end:                                           ; preds = %if.else, %land.end
  %51 = load i32, i32* %ret, align 4, !dbg !278
  ret i32 %51, !dbg !279
}

; Function Attrs: nounwind uwtable
define internal i32 @delta_encoder_update(%struct.lzma_coder_s* %coder, %struct.lzma_allocator* %allocator, %struct.lzma_filter* %filters_null, %struct.lzma_filter* %reversed_filters) #0 !dbg !150 {
entry:
  %coder.addr = alloca %struct.lzma_coder_s*, align 8
  %allocator.addr = alloca %struct.lzma_allocator*, align 8
  %filters_null.addr = alloca %struct.lzma_filter*, align 8
  %reversed_filters.addr = alloca %struct.lzma_filter*, align 8
  store %struct.lzma_coder_s* %coder, %struct.lzma_coder_s** %coder.addr, align 8
  call void @llvm.dbg.declare(metadata %struct.lzma_coder_s** %coder.addr, metadata !280, metadata !155), !dbg !281
  store %struct.lzma_allocator* %allocator, %struct.lzma_allocator** %allocator.addr, align 8
  call void @llvm.dbg.declare(metadata %struct.lzma_allocator** %allocator.addr, metadata !282, metadata !155), !dbg !283
  store %struct.lzma_filter* %filters_null, %struct.lzma_filter** %filters_null.addr, align 8
  call void @llvm.dbg.declare(metadata %struct.lzma_filter** %filters_null.addr, metadata !284, metadata !155), !dbg !285
  store %struct.lzma_filter* %reversed_filters, %struct.lzma_filter** %reversed_filters.addr, align 8
  call void @llvm.dbg.declare(metadata %struct.lzma_filter** %reversed_filters.addr, metadata !286, metadata !155), !dbg !287
  %0 = load %struct.lzma_coder_s*, %struct.lzma_coder_s** %coder.addr, align 8, !dbg !288
  %next = getelementptr inbounds %struct.lzma_coder_s, %struct.lzma_coder_s* %0, i32 0, i32 0, !dbg !289
  %1 = load %struct.lzma_allocator*, %struct.lzma_allocator** %allocator.addr, align 8, !dbg !290
  %2 = load %struct.lzma_filter*, %struct.lzma_filter** %reversed_filters.addr, align 8, !dbg !291
  %add.ptr = getelementptr inbounds %struct.lzma_filter, %struct.lzma_filter* %2, i64 1, !dbg !292
  %call = call i32 @lzma_next_filter_update(%struct.lzma_next_coder_s* %next, %struct.lzma_allocator* %1, %struct.lzma_filter* %add.ptr), !dbg !293
  ret i32 %call, !dbg !294
}

declare i32 @lzma_delta_coder_init(%struct.lzma_next_coder_s*, %struct.lzma_allocator*, %struct.lzma_filter_info_s*) #2

; Function Attrs: nounwind uwtable
define i32 @lzma_delta_props_encode(i8* %options, i8* %out) #0 !dbg !138 {
entry:
  %retval = alloca i32, align 4
  %options.addr = alloca i8*, align 8
  %out.addr = alloca i8*, align 8
  %opt = alloca %struct.lzma_options_delta*, align 8
  store i8* %options, i8** %options.addr, align 8
  call void @llvm.dbg.declare(metadata i8** %options.addr, metadata !295, metadata !155), !dbg !296
  store i8* %out, i8** %out.addr, align 8
  call void @llvm.dbg.declare(metadata i8** %out.addr, metadata !297, metadata !155), !dbg !298
  call void @llvm.dbg.declare(metadata %struct.lzma_options_delta** %opt, metadata !299, metadata !155), !dbg !316
  %0 = load i8*, i8** %options.addr, align 8, !dbg !317
  %1 = bitcast i8* %0 to %struct.lzma_options_delta*, !dbg !317
  store %struct.lzma_options_delta* %1, %struct.lzma_options_delta** %opt, align 8, !dbg !316
  %2 = load i8*, i8** %options.addr, align 8, !dbg !318
  %call = call i64 @lzma_delta_coder_memusage(i8* %2), !dbg !320
  %cmp = icmp eq i64 %call, -1, !dbg !321
  br i1 %cmp, label %if.then, label %if.end, !dbg !322

if.then:                                          ; preds = %entry
  store i32 11, i32* %retval, align 4, !dbg !323
  br label %return, !dbg !323

if.end:                                           ; preds = %entry
  %3 = load %struct.lzma_options_delta*, %struct.lzma_options_delta** %opt, align 8, !dbg !324
  %dist = getelementptr inbounds %struct.lzma_options_delta, %struct.lzma_options_delta* %3, i32 0, i32 1, !dbg !325
  %4 = load i32, i32* %dist, align 4, !dbg !325
  %sub = sub i32 %4, 1, !dbg !326
  %conv = trunc i32 %sub to i8, !dbg !324
  %5 = load i8*, i8** %out.addr, align 8, !dbg !327
  %arrayidx = getelementptr inbounds i8, i8* %5, i64 0, !dbg !327
  store i8 %conv, i8* %arrayidx, align 1, !dbg !328
  store i32 0, i32* %retval, align 4, !dbg !329
  br label %return, !dbg !329

return:                                           ; preds = %if.end, %if.then
  %6 = load i32, i32* %retval, align 4, !dbg !330
  ret i32 %6, !dbg !330
}

declare i64 @lzma_delta_coder_memusage(i8*) #2

; Function Attrs: nounwind uwtable
define internal void @copy_and_encode(%struct.lzma_coder_s* %coder, i8* noalias %in, i8* noalias %out, i64 %size) #0 !dbg !144 {
entry:
  %coder.addr = alloca %struct.lzma_coder_s*, align 8
  %in.addr = alloca i8*, align 8
  %out.addr = alloca i8*, align 8
  %size.addr = alloca i64, align 8
  %i = alloca i64, align 8
  %distance = alloca i64, align 8
  %tmp = alloca i8, align 1
  store %struct.lzma_coder_s* %coder, %struct.lzma_coder_s** %coder.addr, align 8
  call void @llvm.dbg.declare(metadata %struct.lzma_coder_s** %coder.addr, metadata !331, metadata !155), !dbg !332
  store i8* %in, i8** %in.addr, align 8
  call void @llvm.dbg.declare(metadata i8** %in.addr, metadata !333, metadata !155), !dbg !334
  store i8* %out, i8** %out.addr, align 8
  call void @llvm.dbg.declare(metadata i8** %out.addr, metadata !335, metadata !155), !dbg !336
  store i64 %size, i64* %size.addr, align 8
  call void @llvm.dbg.declare(metadata i64* %size.addr, metadata !337, metadata !155), !dbg !338
  call void @llvm.dbg.declare(metadata i64* %i, metadata !339, metadata !155), !dbg !340
  call void @llvm.dbg.declare(metadata i64* %distance, metadata !341, metadata !155), !dbg !342
  %0 = load %struct.lzma_coder_s*, %struct.lzma_coder_s** %coder.addr, align 8, !dbg !343
  %distance1 = getelementptr inbounds %struct.lzma_coder_s, %struct.lzma_coder_s* %0, i32 0, i32 1, !dbg !344
  %1 = load i64, i64* %distance1, align 8, !dbg !344
  store i64 %1, i64* %distance, align 8, !dbg !342
  store i64 0, i64* %i, align 8, !dbg !345
  br label %for.cond, !dbg !347

for.cond:                                         ; preds = %for.inc, %entry
  %2 = load i64, i64* %i, align 8, !dbg !348
  %3 = load i64, i64* %size.addr, align 8, !dbg !351
  %cmp = icmp ult i64 %2, %3, !dbg !352
  br i1 %cmp, label %for.body, label %for.end, !dbg !353

for.body:                                         ; preds = %for.cond
  call void @llvm.dbg.declare(metadata i8* %tmp, metadata !354, metadata !155), !dbg !356
  %4 = load i64, i64* %distance, align 8, !dbg !357
  %5 = load %struct.lzma_coder_s*, %struct.lzma_coder_s** %coder.addr, align 8, !dbg !358
  %pos = getelementptr inbounds %struct.lzma_coder_s, %struct.lzma_coder_s* %5, i32 0, i32 2, !dbg !359
  %6 = load i8, i8* %pos, align 8, !dbg !359
  %conv = zext i8 %6 to i64, !dbg !358
  %add = add i64 %4, %conv, !dbg !360
  %and = and i64 %add, 255, !dbg !361
  %7 = load %struct.lzma_coder_s*, %struct.lzma_coder_s** %coder.addr, align 8, !dbg !362
  %history = getelementptr inbounds %struct.lzma_coder_s, %struct.lzma_coder_s* %7, i32 0, i32 3, !dbg !363
  %arrayidx = getelementptr inbounds [256 x i8], [256 x i8]* %history, i64 0, i64 %and, !dbg !362
  %8 = load i8, i8* %arrayidx, align 1, !dbg !362
  store i8 %8, i8* %tmp, align 1, !dbg !356
  %9 = load i64, i64* %i, align 8, !dbg !364
  %10 = load i8*, i8** %in.addr, align 8, !dbg !365
  %arrayidx2 = getelementptr inbounds i8, i8* %10, i64 %9, !dbg !365
  %11 = load i8, i8* %arrayidx2, align 1, !dbg !365
  %12 = load %struct.lzma_coder_s*, %struct.lzma_coder_s** %coder.addr, align 8, !dbg !366
  %pos3 = getelementptr inbounds %struct.lzma_coder_s, %struct.lzma_coder_s* %12, i32 0, i32 2, !dbg !367
  %13 = load i8, i8* %pos3, align 8, !dbg !368
  %dec = add i8 %13, -1, !dbg !368
  store i8 %dec, i8* %pos3, align 8, !dbg !368
  %conv4 = zext i8 %13 to i32, !dbg !366
  %and5 = and i32 %conv4, 255, !dbg !369
  %idxprom = sext i32 %and5 to i64, !dbg !370
  %14 = load %struct.lzma_coder_s*, %struct.lzma_coder_s** %coder.addr, align 8, !dbg !370
  %history6 = getelementptr inbounds %struct.lzma_coder_s, %struct.lzma_coder_s* %14, i32 0, i32 3, !dbg !371
  %arrayidx7 = getelementptr inbounds [256 x i8], [256 x i8]* %history6, i64 0, i64 %idxprom, !dbg !370
  store i8 %11, i8* %arrayidx7, align 1, !dbg !372
  %15 = load i64, i64* %i, align 8, !dbg !373
  %16 = load i8*, i8** %in.addr, align 8, !dbg !374
  %arrayidx8 = getelementptr inbounds i8, i8* %16, i64 %15, !dbg !374
  %17 = load i8, i8* %arrayidx8, align 1, !dbg !374
  %conv9 = zext i8 %17 to i32, !dbg !374
  %18 = load i8, i8* %tmp, align 1, !dbg !375
  %conv10 = zext i8 %18 to i32, !dbg !375
  %sub = sub nsw i32 %conv9, %conv10, !dbg !376
  %conv11 = trunc i32 %sub to i8, !dbg !374
  %19 = load i64, i64* %i, align 8, !dbg !377
  %20 = load i8*, i8** %out.addr, align 8, !dbg !378
  %arrayidx12 = getelementptr inbounds i8, i8* %20, i64 %19, !dbg !378
  store i8 %conv11, i8* %arrayidx12, align 1, !dbg !379
  br label %for.inc, !dbg !380

for.inc:                                          ; preds = %for.body
  %21 = load i64, i64* %i, align 8, !dbg !381
  %inc = add i64 %21, 1, !dbg !381
  store i64 %inc, i64* %i, align 8, !dbg !381
  br label %for.cond, !dbg !383

for.end:                                          ; preds = %for.cond
  ret void, !dbg !384
}

; Function Attrs: nounwind uwtable
define internal void @encode_in_place(%struct.lzma_coder_s* %coder, i8* %buffer, i64 %size) #0 !dbg !147 {
entry:
  %coder.addr = alloca %struct.lzma_coder_s*, align 8
  %buffer.addr = alloca i8*, align 8
  %size.addr = alloca i64, align 8
  %i = alloca i64, align 8
  %distance = alloca i64, align 8
  %tmp = alloca i8, align 1
  store %struct.lzma_coder_s* %coder, %struct.lzma_coder_s** %coder.addr, align 8
  call void @llvm.dbg.declare(metadata %struct.lzma_coder_s** %coder.addr, metadata !385, metadata !155), !dbg !386
  store i8* %buffer, i8** %buffer.addr, align 8
  call void @llvm.dbg.declare(metadata i8** %buffer.addr, metadata !387, metadata !155), !dbg !388
  store i64 %size, i64* %size.addr, align 8
  call void @llvm.dbg.declare(metadata i64* %size.addr, metadata !389, metadata !155), !dbg !390
  call void @llvm.dbg.declare(metadata i64* %i, metadata !391, metadata !155), !dbg !392
  call void @llvm.dbg.declare(metadata i64* %distance, metadata !393, metadata !155), !dbg !394
  %0 = load %struct.lzma_coder_s*, %struct.lzma_coder_s** %coder.addr, align 8, !dbg !395
  %distance1 = getelementptr inbounds %struct.lzma_coder_s, %struct.lzma_coder_s* %0, i32 0, i32 1, !dbg !396
  %1 = load i64, i64* %distance1, align 8, !dbg !396
  store i64 %1, i64* %distance, align 8, !dbg !394
  store i64 0, i64* %i, align 8, !dbg !397
  br label %for.cond, !dbg !399

for.cond:                                         ; preds = %for.inc, %entry
  %2 = load i64, i64* %i, align 8, !dbg !400
  %3 = load i64, i64* %size.addr, align 8, !dbg !403
  %cmp = icmp ult i64 %2, %3, !dbg !404
  br i1 %cmp, label %for.body, label %for.end, !dbg !405

for.body:                                         ; preds = %for.cond
  call void @llvm.dbg.declare(metadata i8* %tmp, metadata !406, metadata !155), !dbg !408
  %4 = load i64, i64* %distance, align 8, !dbg !409
  %5 = load %struct.lzma_coder_s*, %struct.lzma_coder_s** %coder.addr, align 8, !dbg !410
  %pos = getelementptr inbounds %struct.lzma_coder_s, %struct.lzma_coder_s* %5, i32 0, i32 2, !dbg !411
  %6 = load i8, i8* %pos, align 8, !dbg !411
  %conv = zext i8 %6 to i64, !dbg !410
  %add = add i64 %4, %conv, !dbg !412
  %and = and i64 %add, 255, !dbg !413
  %7 = load %struct.lzma_coder_s*, %struct.lzma_coder_s** %coder.addr, align 8, !dbg !414
  %history = getelementptr inbounds %struct.lzma_coder_s, %struct.lzma_coder_s* %7, i32 0, i32 3, !dbg !415
  %arrayidx = getelementptr inbounds [256 x i8], [256 x i8]* %history, i64 0, i64 %and, !dbg !414
  %8 = load i8, i8* %arrayidx, align 1, !dbg !414
  store i8 %8, i8* %tmp, align 1, !dbg !408
  %9 = load i64, i64* %i, align 8, !dbg !416
  %10 = load i8*, i8** %buffer.addr, align 8, !dbg !417
  %arrayidx2 = getelementptr inbounds i8, i8* %10, i64 %9, !dbg !417
  %11 = load i8, i8* %arrayidx2, align 1, !dbg !417
  %12 = load %struct.lzma_coder_s*, %struct.lzma_coder_s** %coder.addr, align 8, !dbg !418
  %pos3 = getelementptr inbounds %struct.lzma_coder_s, %struct.lzma_coder_s* %12, i32 0, i32 2, !dbg !419
  %13 = load i8, i8* %pos3, align 8, !dbg !420
  %dec = add i8 %13, -1, !dbg !420
  store i8 %dec, i8* %pos3, align 8, !dbg !420
  %conv4 = zext i8 %13 to i32, !dbg !418
  %and5 = and i32 %conv4, 255, !dbg !421
  %idxprom = sext i32 %and5 to i64, !dbg !422
  %14 = load %struct.lzma_coder_s*, %struct.lzma_coder_s** %coder.addr, align 8, !dbg !422
  %history6 = getelementptr inbounds %struct.lzma_coder_s, %struct.lzma_coder_s* %14, i32 0, i32 3, !dbg !423
  %arrayidx7 = getelementptr inbounds [256 x i8], [256 x i8]* %history6, i64 0, i64 %idxprom, !dbg !422
  store i8 %11, i8* %arrayidx7, align 1, !dbg !424
  %15 = load i8, i8* %tmp, align 1, !dbg !425
  %conv8 = zext i8 %15 to i32, !dbg !425
  %16 = load i64, i64* %i, align 8, !dbg !426
  %17 = load i8*, i8** %buffer.addr, align 8, !dbg !427
  %arrayidx9 = getelementptr inbounds i8, i8* %17, i64 %16, !dbg !427
  %18 = load i8, i8* %arrayidx9, align 1, !dbg !428
  %conv10 = zext i8 %18 to i32, !dbg !428
  %sub = sub nsw i32 %conv10, %conv8, !dbg !428
  %conv11 = trunc i32 %sub to i8, !dbg !428
  store i8 %conv11, i8* %arrayidx9, align 1, !dbg !428
  br label %for.inc, !dbg !429

for.inc:                                          ; preds = %for.body
  %19 = load i64, i64* %i, align 8, !dbg !430
  %inc = add i64 %19, 1, !dbg !430
  store i64 %inc, i64* %i, align 8, !dbg !430
  br label %for.cond, !dbg !432

for.end:                                          ; preds = %for.cond
  ret void, !dbg !433
}

declare i32 @lzma_next_filter_update(%struct.lzma_next_coder_s*, %struct.lzma_allocator*, %struct.lzma_filter*) #2

attributes #0 = { nounwind uwtable "disable-tail-calls"="false" "less-precise-fpmad"="false" "no-frame-pointer-elim"="true" "no-frame-pointer-elim-non-leaf" "no-infs-fp-math"="false" "no-nans-fp-math"="false" "stack-protector-buffer-size"="8" "target-cpu"="x86-64" "target-features"="+fxsr,+mmx,+sse,+sse2" "unsafe-fp-math"="false" "use-soft-float"="false" }
attributes #1 = { nounwind readnone }
attributes #2 = { "disable-tail-calls"="false" "less-precise-fpmad"="false" "no-frame-pointer-elim"="true" "no-frame-pointer-elim-non-leaf" "no-infs-fp-math"="false" "no-nans-fp-math"="false" "stack-protector-buffer-size"="8" "target-cpu"="x86-64" "target-features"="+fxsr,+mmx,+sse,+sse2" "unsafe-fp-math"="false" "use-soft-float"="false" }

!llvm.dbg.cu = !{!0}
!llvm.module.flags = !{!151, !152}
!llvm.ident = !{!153}

!0 = distinct !DICompileUnit(language: DW_LANG_C99, file: !1, producer: "clang version 3.8.0 (tags/RELEASE_380/final)", isOptimized: false, runtimeVersion: 0, emissionKind: 1, enums: !2, retainedTypes: !35, subprograms: !37)
!1 = !DIFile(filename: "/data/download/cmake/cmake-master/Utilities/cmliblzma/liblzma/delta/delta_encoder.c", directory: "/data/download/cmake/cmake-master/Utilities/cmliblzma")
!2 = !{!3, !18, !24, !31}
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
!31 = !DICompositeType(tag: DW_TAG_enumeration_type, file: !32, line: 35, size: 32, align: 32, elements: !33)
!32 = !DIFile(filename: "/data/download/cmake/cmake-master/Utilities/cmliblzma/liblzma/api/lzma/delta.h", directory: "/data/download/cmake/cmake-master/Utilities/cmliblzma")
!33 = !{!34}
!34 = !DIEnumerator(name: "LZMA_DELTA_TYPE_BYTE", value: 0)
!35 = !{!36}
!36 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: null, size: 64, align: 64)
!37 = !{!38, !138, !143, !144, !147, !150}
!38 = distinct !DISubprogram(name: "lzma_delta_encoder_init", scope: !1, file: !1, line: 102, type: !39, isLocal: false, isDefinition: true, scopeLine: 104, flags: DIFlagPrototyped, isOptimized: false, variables: !137)
!39 = !DISubroutineType(types: !40)
!40 = !{!41, !42, !77, !127}
!41 = !DIDerivedType(tag: DW_TAG_typedef, name: "lzma_ret", file: !4, line: 237, baseType: !3)
!42 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !43, size: 64, align: 64)
!43 = !DIDerivedType(tag: DW_TAG_typedef, name: "lzma_next_coder", file: !44, line: 75, baseType: !45)
!44 = !DIFile(filename: "/data/download/cmake/cmake-master/Utilities/cmliblzma/liblzma/common/common.h", directory: "/data/download/cmake/cmake-master/Utilities/cmliblzma")
!45 = !DICompositeType(tag: DW_TAG_structure_type, name: "lzma_next_coder_s", file: !44, line: 119, size: 512, align: 64, elements: !46)
!46 = !{!47, !66, !70, !72, !98, !103, !110, !115}
!47 = !DIDerivedType(tag: DW_TAG_member, name: "coder", scope: !45, file: !44, line: 121, baseType: !48, size: 64, align: 64)
!48 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !49, size: 64, align: 64)
!49 = !DIDerivedType(tag: DW_TAG_typedef, name: "lzma_coder", file: !44, line: 73, baseType: !50)
!50 = !DICompositeType(tag: DW_TAG_structure_type, name: "lzma_coder_s", file: !51, line: 18, size: 2688, align: 64, elements: !52)
!51 = !DIFile(filename: "/data/download/cmake/cmake-master/Utilities/cmliblzma/liblzma/delta/delta_private.h", directory: "/data/download/cmake/cmake-master/Utilities/cmliblzma")
!52 = !{!53, !54, !58, !62}
!53 = !DIDerivedType(tag: DW_TAG_member, name: "next", scope: !50, file: !51, line: 20, baseType: !43, size: 512, align: 64)
!54 = !DIDerivedType(tag: DW_TAG_member, name: "distance", scope: !50, file: !51, line: 23, baseType: !55, size: 64, align: 64, offset: 512)
!55 = !DIDerivedType(tag: DW_TAG_typedef, name: "size_t", file: !56, line: 62, baseType: !57)
!56 = !DIFile(filename: "/opt/llvm-build/bin/../lib/clang/3.8.0/include/stddef.h", directory: "/data/download/cmake/cmake-master/Utilities/cmliblzma")
!57 = !DIBasicType(name: "long unsigned int", size: 64, align: 64, encoding: DW_ATE_unsigned)
!58 = !DIDerivedType(tag: DW_TAG_member, name: "pos", scope: !50, file: !51, line: 26, baseType: !59, size: 8, align: 8, offset: 576)
!59 = !DIDerivedType(tag: DW_TAG_typedef, name: "uint8_t", file: !60, line: 48, baseType: !61)
!60 = !DIFile(filename: "/usr/include/stdint.h", directory: "/data/download/cmake/cmake-master/Utilities/cmliblzma")
!61 = !DIBasicType(name: "unsigned char", size: 8, align: 8, encoding: DW_ATE_unsigned_char)
!62 = !DIDerivedType(tag: DW_TAG_member, name: "history", scope: !50, file: !51, line: 29, baseType: !63, size: 2048, align: 8, offset: 584)
!63 = !DICompositeType(tag: DW_TAG_array_type, baseType: !59, size: 2048, align: 8, elements: !64)
!64 = !{!65}
!65 = !DISubrange(count: 256)
!66 = !DIDerivedType(tag: DW_TAG_member, name: "id", scope: !45, file: !44, line: 125, baseType: !67, size: 64, align: 64, offset: 64)
!67 = !DIDerivedType(tag: DW_TAG_typedef, name: "lzma_vli", file: !68, line: 63, baseType: !69)
!68 = !DIFile(filename: "/data/download/cmake/cmake-master/Utilities/cmliblzma/liblzma/api/lzma/vli.h", directory: "/data/download/cmake/cmake-master/Utilities/cmliblzma")
!69 = !DIDerivedType(tag: DW_TAG_typedef, name: "uint64_t", file: !60, line: 55, baseType: !57)
!70 = !DIDerivedType(tag: DW_TAG_member, name: "init", scope: !45, file: !44, line: 131, baseType: !71, size: 64, align: 64, offset: 128)
!71 = !DIDerivedType(tag: DW_TAG_typedef, name: "uintptr_t", file: !60, line: 122, baseType: !57)
!72 = !DIDerivedType(tag: DW_TAG_member, name: "code", scope: !45, file: !44, line: 134, baseType: !73, size: 64, align: 64, offset: 192)
!73 = !DIDerivedType(tag: DW_TAG_typedef, name: "lzma_code_function", file: !44, line: 89, baseType: !74)
!74 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !75, size: 64, align: 64)
!75 = !DISubroutineType(types: !76)
!76 = !{!41, !48, !77, !90, !93, !55, !95, !93, !55, !97}
!77 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !78, size: 64, align: 64)
!78 = !DIDerivedType(tag: DW_TAG_typedef, name: "lzma_allocator", file: !4, line: 403, baseType: !79)
!79 = !DICompositeType(tag: DW_TAG_structure_type, file: !4, line: 341, size: 192, align: 64, elements: !80)
!80 = !{!81, !85, !89}
!81 = !DIDerivedType(tag: DW_TAG_member, name: "alloc", scope: !79, file: !4, line: 376, baseType: !82, size: 64, align: 64)
!82 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !83, size: 64, align: 64)
!83 = !DISubroutineType(types: !84)
!84 = !{!36, !36, !55, !55}
!85 = !DIDerivedType(tag: DW_TAG_member, name: "free", scope: !79, file: !4, line: 390, baseType: !86, size: 64, align: 64, offset: 64)
!86 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !87, size: 64, align: 64)
!87 = !DISubroutineType(types: !88)
!88 = !{null, !36, !36}
!89 = !DIDerivedType(tag: DW_TAG_member, name: "opaque", scope: !79, file: !4, line: 401, baseType: !36, size: 64, align: 64, offset: 128)
!90 = !DIDerivedType(tag: DW_TAG_restrict_type, baseType: !91)
!91 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !92, size: 64, align: 64)
!92 = !DIDerivedType(tag: DW_TAG_const_type, baseType: !59)
!93 = !DIDerivedType(tag: DW_TAG_restrict_type, baseType: !94)
!94 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !55, size: 64, align: 64)
!95 = !DIDerivedType(tag: DW_TAG_restrict_type, baseType: !96)
!96 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !59, size: 64, align: 64)
!97 = !DIDerivedType(tag: DW_TAG_typedef, name: "lzma_action", file: !4, line: 322, baseType: !18)
!98 = !DIDerivedType(tag: DW_TAG_member, name: "end", scope: !45, file: !44, line: 139, baseType: !99, size: 64, align: 64, offset: 256)
!99 = !DIDerivedType(tag: DW_TAG_typedef, name: "lzma_end_function", file: !44, line: 97, baseType: !100)
!100 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !101, size: 64, align: 64)
!101 = !DISubroutineType(types: !102)
!102 = !{null, !48, !77}
!103 = !DIDerivedType(tag: DW_TAG_member, name: "get_check", scope: !45, file: !44, line: 143, baseType: !104, size: 64, align: 64, offset: 320)
!104 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !105, size: 64, align: 64)
!105 = !DISubroutineType(types: !106)
!106 = !{!107, !108}
!107 = !DIDerivedType(tag: DW_TAG_typedef, name: "lzma_check", file: !25, line: 55, baseType: !24)
!108 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !109, size: 64, align: 64)
!109 = !DIDerivedType(tag: DW_TAG_const_type, baseType: !49)
!110 = !DIDerivedType(tag: DW_TAG_member, name: "memconfig", scope: !45, file: !44, line: 147, baseType: !111, size: 64, align: 64, offset: 384)
!111 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !112, size: 64, align: 64)
!112 = !DISubroutineType(types: !113)
!113 = !{!41, !48, !114, !114, !69}
!114 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !69, size: 64, align: 64)
!115 = !DIDerivedType(tag: DW_TAG_member, name: "update", scope: !45, file: !44, line: 152, baseType: !116, size: 64, align: 64, offset: 448)
!116 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !117, size: 64, align: 64)
!117 = !DISubroutineType(types: !118)
!118 = !{!41, !48, !77, !119, !119}
!119 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !120, size: 64, align: 64)
!120 = !DIDerivedType(tag: DW_TAG_const_type, baseType: !121)
!121 = !DIDerivedType(tag: DW_TAG_typedef, name: "lzma_filter", file: !122, line: 65, baseType: !123)
!122 = !DIFile(filename: "/data/download/cmake/cmake-master/Utilities/cmliblzma/liblzma/api/lzma/filter.h", directory: "/data/download/cmake/cmake-master/Utilities/cmliblzma")
!123 = !DICompositeType(tag: DW_TAG_structure_type, file: !122, line: 43, size: 128, align: 64, elements: !124)
!124 = !{!125, !126}
!125 = !DIDerivedType(tag: DW_TAG_member, name: "id", scope: !123, file: !122, line: 54, baseType: !67, size: 64, align: 64)
!126 = !DIDerivedType(tag: DW_TAG_member, name: "options", scope: !123, file: !122, line: 63, baseType: !36, size: 64, align: 64, offset: 64)
!127 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !128, size: 64, align: 64)
!128 = !DIDerivedType(tag: DW_TAG_const_type, baseType: !129)
!129 = !DIDerivedType(tag: DW_TAG_typedef, name: "lzma_filter_info", file: !44, line: 77, baseType: !130)
!130 = !DICompositeType(tag: DW_TAG_structure_type, name: "lzma_filter_info_s", file: !44, line: 104, size: 192, align: 64, elements: !131)
!131 = !{!132, !133, !136}
!132 = !DIDerivedType(tag: DW_TAG_member, name: "id", scope: !130, file: !44, line: 107, baseType: !67, size: 64, align: 64)
!133 = !DIDerivedType(tag: DW_TAG_member, name: "init", scope: !130, file: !44, line: 111, baseType: !134, size: 64, align: 64, offset: 64)
!134 = !DIDerivedType(tag: DW_TAG_typedef, name: "lzma_init_function", file: !44, line: 81, baseType: !135)
!135 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !39, size: 64, align: 64)
!136 = !DIDerivedType(tag: DW_TAG_member, name: "options", scope: !130, file: !44, line: 114, baseType: !36, size: 64, align: 64, offset: 128)
!137 = !{}
!138 = distinct !DISubprogram(name: "lzma_delta_props_encode", scope: !1, file: !1, line: 112, type: !139, isLocal: false, isDefinition: true, scopeLine: 113, flags: DIFlagPrototyped, isOptimized: false, variables: !137)
!139 = !DISubroutineType(types: !140)
!140 = !{!41, !141, !96}
!141 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !142, size: 64, align: 64)
!142 = !DIDerivedType(tag: DW_TAG_const_type, baseType: null)
!143 = distinct !DISubprogram(name: "delta_encode", scope: !1, file: !1, line: 54, type: !75, isLocal: true, isDefinition: true, scopeLine: 58, flags: DIFlagPrototyped, isOptimized: false, variables: !137)
!144 = distinct !DISubprogram(name: "copy_and_encode", scope: !1, file: !1, line: 21, type: !145, isLocal: true, isDefinition: true, scopeLine: 23, flags: DIFlagPrototyped, isOptimized: false, variables: !137)
!145 = !DISubroutineType(types: !146)
!146 = !{null, !48, !90, !95, !55}
!147 = distinct !DISubprogram(name: "encode_in_place", scope: !1, file: !1, line: 39, type: !148, isLocal: true, isDefinition: true, scopeLine: 40, flags: DIFlagPrototyped, isOptimized: false, variables: !137)
!148 = !DISubroutineType(types: !149)
!149 = !{null, !48, !96, !55}
!150 = distinct !DISubprogram(name: "delta_encoder_update", scope: !1, file: !1, line: 89, type: !117, isLocal: true, isDefinition: true, scopeLine: 92, flags: DIFlagPrototyped, isOptimized: false, variables: !137)
!151 = !{i32 2, !"Dwarf Version", i32 4}
!152 = !{i32 2, !"Debug Info Version", i32 3}
!153 = !{!"clang version 3.8.0 (tags/RELEASE_380/final)"}
!154 = !DILocalVariable(name: "next", arg: 1, scope: !38, file: !1, line: 102, type: !42)
!155 = !DIExpression()
!156 = !DILocation(line: 102, column: 42, scope: !38)
!157 = !DILocalVariable(name: "allocator", arg: 2, scope: !38, file: !1, line: 102, type: !77)
!158 = !DILocation(line: 102, column: 64, scope: !38)
!159 = !DILocalVariable(name: "filters", arg: 3, scope: !38, file: !1, line: 103, type: !127)
!160 = !DILocation(line: 103, column: 27, scope: !38)
!161 = !DILocation(line: 105, column: 2, scope: !38)
!162 = !DILocation(line: 105, column: 8, scope: !38)
!163 = !DILocation(line: 105, column: 13, scope: !38)
!164 = !DILocation(line: 106, column: 2, scope: !38)
!165 = !DILocation(line: 106, column: 8, scope: !38)
!166 = !DILocation(line: 106, column: 15, scope: !38)
!167 = !DILocation(line: 107, column: 31, scope: !38)
!168 = !DILocation(line: 107, column: 37, scope: !38)
!169 = !DILocation(line: 107, column: 48, scope: !38)
!170 = !DILocation(line: 107, column: 9, scope: !38)
!171 = !DILocation(line: 107, column: 2, scope: !38)
!172 = !DILocalVariable(name: "coder", arg: 1, scope: !143, file: !1, line: 54, type: !48)
!173 = !DILocation(line: 54, column: 26, scope: !143)
!174 = !DILocalVariable(name: "allocator", arg: 2, scope: !143, file: !1, line: 54, type: !77)
!175 = !DILocation(line: 54, column: 49, scope: !143)
!176 = !DILocalVariable(name: "in", arg: 3, scope: !143, file: !1, line: 55, type: !90)
!177 = !DILocation(line: 55, column: 32, scope: !143)
!178 = !DILocalVariable(name: "in_pos", arg: 4, scope: !143, file: !1, line: 55, type: !93)
!179 = !DILocation(line: 55, column: 58, scope: !143)
!180 = !DILocalVariable(name: "in_size", arg: 5, scope: !143, file: !1, line: 56, type: !55)
!181 = !DILocation(line: 56, column: 10, scope: !143)
!182 = !DILocalVariable(name: "out", arg: 6, scope: !143, file: !1, line: 56, type: !95)
!183 = !DILocation(line: 56, column: 42, scope: !143)
!184 = !DILocalVariable(name: "out_pos", arg: 7, scope: !143, file: !1, line: 57, type: !93)
!185 = !DILocation(line: 57, column: 25, scope: !143)
!186 = !DILocalVariable(name: "out_size", arg: 8, scope: !143, file: !1, line: 57, type: !55)
!187 = !DILocation(line: 57, column: 41, scope: !143)
!188 = !DILocalVariable(name: "action", arg: 9, scope: !143, file: !1, line: 57, type: !97)
!189 = !DILocation(line: 57, column: 63, scope: !143)
!190 = !DILocalVariable(name: "ret", scope: !143, file: !1, line: 59, type: !41)
!191 = !DILocation(line: 59, column: 11, scope: !143)
!192 = !DILocation(line: 61, column: 6, scope: !193)
!193 = distinct !DILexicalBlock(scope: !143, file: !1, line: 61, column: 6)
!194 = !DILocation(line: 61, column: 13, scope: !193)
!195 = !DILocation(line: 61, column: 18, scope: !193)
!196 = !DILocation(line: 61, column: 23, scope: !193)
!197 = !DILocation(line: 61, column: 6, scope: !143)
!198 = !DILocalVariable(name: "in_avail", scope: !199, file: !1, line: 62, type: !200)
!199 = distinct !DILexicalBlock(scope: !193, file: !1, line: 61, column: 32)
!200 = !DIDerivedType(tag: DW_TAG_const_type, baseType: !55)
!201 = !DILocation(line: 62, column: 16, scope: !199)
!202 = !DILocation(line: 62, column: 27, scope: !199)
!203 = !DILocation(line: 62, column: 38, scope: !199)
!204 = !DILocation(line: 62, column: 37, scope: !199)
!205 = !DILocation(line: 62, column: 35, scope: !199)
!206 = !DILocalVariable(name: "out_avail", scope: !199, file: !1, line: 63, type: !200)
!207 = !DILocation(line: 63, column: 16, scope: !199)
!208 = !DILocation(line: 63, column: 28, scope: !199)
!209 = !DILocation(line: 63, column: 40, scope: !199)
!210 = !DILocation(line: 63, column: 39, scope: !199)
!211 = !DILocation(line: 63, column: 37, scope: !199)
!212 = !DILocalVariable(name: "size", scope: !199, file: !1, line: 64, type: !200)
!213 = !DILocation(line: 64, column: 16, scope: !199)
!214 = !DILocation(line: 64, column: 23, scope: !199)
!215 = !DILocation(line: 64, column: 23, scope: !216)
!216 = !DILexicalBlockFile(scope: !199, file: !1, discriminator: 1)
!217 = !DILocation(line: 64, column: 23, scope: !218)
!218 = !DILexicalBlockFile(scope: !199, file: !1, discriminator: 2)
!219 = !DILocation(line: 64, column: 23, scope: !220)
!220 = !DILexicalBlockFile(scope: !199, file: !1, discriminator: 3)
!221 = !DILocation(line: 64, column: 16, scope: !220)
!222 = !DILocation(line: 66, column: 19, scope: !199)
!223 = !DILocation(line: 66, column: 26, scope: !199)
!224 = !DILocation(line: 66, column: 32, scope: !199)
!225 = !DILocation(line: 66, column: 31, scope: !199)
!226 = !DILocation(line: 66, column: 29, scope: !199)
!227 = !DILocation(line: 66, column: 40, scope: !199)
!228 = !DILocation(line: 66, column: 47, scope: !199)
!229 = !DILocation(line: 66, column: 46, scope: !199)
!230 = !DILocation(line: 66, column: 44, scope: !199)
!231 = !DILocation(line: 66, column: 56, scope: !199)
!232 = !DILocation(line: 66, column: 3, scope: !199)
!233 = !DILocation(line: 68, column: 14, scope: !199)
!234 = !DILocation(line: 68, column: 4, scope: !199)
!235 = !DILocation(line: 68, column: 11, scope: !199)
!236 = !DILocation(line: 69, column: 15, scope: !199)
!237 = !DILocation(line: 69, column: 4, scope: !199)
!238 = !DILocation(line: 69, column: 12, scope: !199)
!239 = !DILocation(line: 71, column: 9, scope: !199)
!240 = !DILocation(line: 71, column: 16, scope: !199)
!241 = !DILocation(line: 71, column: 28, scope: !199)
!242 = !DILocation(line: 71, column: 32, scope: !216)
!243 = !DILocation(line: 71, column: 31, scope: !216)
!244 = !DILocation(line: 71, column: 42, scope: !216)
!245 = !DILocation(line: 71, column: 39, scope: !216)
!246 = !DILocation(line: 71, column: 9, scope: !218)
!247 = !DILocation(line: 71, column: 7, scope: !218)
!248 = !DILocation(line: 74, column: 2, scope: !199)
!249 = !DILocalVariable(name: "out_start", scope: !250, file: !1, line: 75, type: !200)
!250 = distinct !DILexicalBlock(scope: !193, file: !1, line: 74, column: 9)
!251 = !DILocation(line: 75, column: 16, scope: !250)
!252 = !DILocation(line: 75, column: 29, scope: !250)
!253 = !DILocation(line: 75, column: 28, scope: !250)
!254 = !DILocation(line: 77, column: 9, scope: !250)
!255 = !DILocation(line: 77, column: 16, scope: !250)
!256 = !DILocation(line: 77, column: 21, scope: !250)
!257 = !DILocation(line: 77, column: 26, scope: !250)
!258 = !DILocation(line: 77, column: 33, scope: !250)
!259 = !DILocation(line: 77, column: 38, scope: !250)
!260 = !DILocation(line: 77, column: 45, scope: !250)
!261 = !DILocation(line: 78, column: 5, scope: !250)
!262 = !DILocation(line: 78, column: 9, scope: !250)
!263 = !DILocation(line: 78, column: 17, scope: !250)
!264 = !DILocation(line: 78, column: 26, scope: !250)
!265 = !DILocation(line: 78, column: 31, scope: !250)
!266 = !DILocation(line: 78, column: 40, scope: !250)
!267 = !DILocation(line: 79, column: 5, scope: !250)
!268 = !DILocation(line: 77, column: 7, scope: !250)
!269 = !DILocation(line: 81, column: 19, scope: !250)
!270 = !DILocation(line: 81, column: 26, scope: !250)
!271 = !DILocation(line: 81, column: 32, scope: !250)
!272 = !DILocation(line: 81, column: 30, scope: !250)
!273 = !DILocation(line: 81, column: 44, scope: !250)
!274 = !DILocation(line: 81, column: 43, scope: !250)
!275 = !DILocation(line: 81, column: 54, scope: !250)
!276 = !DILocation(line: 81, column: 52, scope: !250)
!277 = !DILocation(line: 81, column: 3, scope: !250)
!278 = !DILocation(line: 84, column: 9, scope: !143)
!279 = !DILocation(line: 84, column: 2, scope: !143)
!280 = !DILocalVariable(name: "coder", arg: 1, scope: !150, file: !1, line: 89, type: !48)
!281 = !DILocation(line: 89, column: 34, scope: !150)
!282 = !DILocalVariable(name: "allocator", arg: 2, scope: !150, file: !1, line: 89, type: !77)
!283 = !DILocation(line: 89, column: 57, scope: !150)
!284 = !DILocalVariable(name: "filters_null", arg: 3, scope: !150, file: !1, line: 90, type: !119)
!285 = !DILocation(line: 90, column: 22, scope: !150)
!286 = !DILocalVariable(name: "reversed_filters", arg: 4, scope: !150, file: !1, line: 91, type: !119)
!287 = !DILocation(line: 91, column: 22, scope: !150)
!288 = !DILocation(line: 97, column: 5, scope: !150)
!289 = !DILocation(line: 97, column: 12, scope: !150)
!290 = !DILocation(line: 97, column: 18, scope: !150)
!291 = !DILocation(line: 97, column: 29, scope: !150)
!292 = !DILocation(line: 97, column: 46, scope: !150)
!293 = !DILocation(line: 96, column: 9, scope: !150)
!294 = !DILocation(line: 96, column: 2, scope: !150)
!295 = !DILocalVariable(name: "options", arg: 1, scope: !138, file: !1, line: 112, type: !141)
!296 = !DILocation(line: 112, column: 37, scope: !138)
!297 = !DILocalVariable(name: "out", arg: 2, scope: !138, file: !1, line: 112, type: !96)
!298 = !DILocation(line: 112, column: 55, scope: !138)
!299 = !DILocalVariable(name: "opt", scope: !138, file: !1, line: 114, type: !300)
!300 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !301, size: 64, align: 64)
!301 = !DIDerivedType(tag: DW_TAG_const_type, baseType: !302)
!302 = !DIDerivedType(tag: DW_TAG_typedef, name: "lzma_options_delta", file: !32, line: 77, baseType: !303)
!303 = !DICompositeType(tag: DW_TAG_structure_type, file: !32, line: 45, size: 320, align: 64, elements: !304)
!304 = !{!305, !307, !310, !311, !312, !313, !314, !315}
!305 = !DIDerivedType(tag: DW_TAG_member, name: "type", scope: !303, file: !32, line: 47, baseType: !306, size: 32, align: 32)
!306 = !DIDerivedType(tag: DW_TAG_typedef, name: "lzma_delta_type", file: !32, line: 37, baseType: !31)
!307 = !DIDerivedType(tag: DW_TAG_member, name: "dist", scope: !303, file: !32, line: 59, baseType: !308, size: 32, align: 32, offset: 32)
!308 = !DIDerivedType(tag: DW_TAG_typedef, name: "uint32_t", file: !60, line: 51, baseType: !309)
!309 = !DIBasicType(name: "unsigned int", size: 32, align: 32, encoding: DW_ATE_unsigned)
!310 = !DIDerivedType(tag: DW_TAG_member, name: "reserved_int1", scope: !303, file: !32, line: 70, baseType: !308, size: 32, align: 32, offset: 64)
!311 = !DIDerivedType(tag: DW_TAG_member, name: "reserved_int2", scope: !303, file: !32, line: 71, baseType: !308, size: 32, align: 32, offset: 96)
!312 = !DIDerivedType(tag: DW_TAG_member, name: "reserved_int3", scope: !303, file: !32, line: 72, baseType: !308, size: 32, align: 32, offset: 128)
!313 = !DIDerivedType(tag: DW_TAG_member, name: "reserved_int4", scope: !303, file: !32, line: 73, baseType: !308, size: 32, align: 32, offset: 160)
!314 = !DIDerivedType(tag: DW_TAG_member, name: "reserved_ptr1", scope: !303, file: !32, line: 74, baseType: !36, size: 64, align: 64, offset: 192)
!315 = !DIDerivedType(tag: DW_TAG_member, name: "reserved_ptr2", scope: !303, file: !32, line: 75, baseType: !36, size: 64, align: 64, offset: 256)
!316 = !DILocation(line: 114, column: 28, scope: !138)
!317 = !DILocation(line: 114, column: 34, scope: !138)
!318 = !DILocation(line: 118, column: 32, scope: !319)
!319 = distinct !DILexicalBlock(scope: !138, file: !1, line: 118, column: 6)
!320 = !DILocation(line: 118, column: 6, scope: !319)
!321 = !DILocation(line: 118, column: 41, scope: !319)
!322 = !DILocation(line: 118, column: 6, scope: !138)
!323 = !DILocation(line: 119, column: 3, scope: !319)
!324 = !DILocation(line: 121, column: 11, scope: !138)
!325 = !DILocation(line: 121, column: 16, scope: !138)
!326 = !DILocation(line: 121, column: 21, scope: !138)
!327 = !DILocation(line: 121, column: 2, scope: !138)
!328 = !DILocation(line: 121, column: 9, scope: !138)
!329 = !DILocation(line: 123, column: 2, scope: !138)
!330 = !DILocation(line: 124, column: 1, scope: !138)
!331 = !DILocalVariable(name: "coder", arg: 1, scope: !144, file: !1, line: 21, type: !48)
!332 = !DILocation(line: 21, column: 29, scope: !144)
!333 = !DILocalVariable(name: "in", arg: 2, scope: !144, file: !1, line: 22, type: !90)
!334 = !DILocation(line: 22, column: 32, scope: !144)
!335 = !DILocalVariable(name: "out", arg: 3, scope: !144, file: !1, line: 22, type: !95)
!336 = !DILocation(line: 22, column: 59, scope: !144)
!337 = !DILocalVariable(name: "size", arg: 4, scope: !144, file: !1, line: 22, type: !55)
!338 = !DILocation(line: 22, column: 71, scope: !144)
!339 = !DILocalVariable(name: "i", scope: !144, file: !1, line: 24, type: !55)
!340 = !DILocation(line: 24, column: 9, scope: !144)
!341 = !DILocalVariable(name: "distance", scope: !144, file: !1, line: 25, type: !200)
!342 = !DILocation(line: 25, column: 15, scope: !144)
!343 = !DILocation(line: 25, column: 26, scope: !144)
!344 = !DILocation(line: 25, column: 33, scope: !144)
!345 = !DILocation(line: 27, column: 9, scope: !346)
!346 = distinct !DILexicalBlock(scope: !144, file: !1, line: 27, column: 2)
!347 = !DILocation(line: 27, column: 7, scope: !346)
!348 = !DILocation(line: 27, column: 14, scope: !349)
!349 = !DILexicalBlockFile(scope: !350, file: !1, discriminator: 1)
!350 = distinct !DILexicalBlock(scope: !346, file: !1, line: 27, column: 2)
!351 = !DILocation(line: 27, column: 18, scope: !349)
!352 = !DILocation(line: 27, column: 16, scope: !349)
!353 = !DILocation(line: 27, column: 2, scope: !349)
!354 = !DILocalVariable(name: "tmp", scope: !355, file: !1, line: 28, type: !92)
!355 = distinct !DILexicalBlock(scope: !350, file: !1, line: 27, column: 29)
!356 = !DILocation(line: 28, column: 17, scope: !355)
!357 = !DILocation(line: 29, column: 6, scope: !355)
!358 = !DILocation(line: 29, column: 17, scope: !355)
!359 = !DILocation(line: 29, column: 24, scope: !355)
!360 = !DILocation(line: 29, column: 15, scope: !355)
!361 = !DILocation(line: 29, column: 29, scope: !355)
!362 = !DILocation(line: 28, column: 23, scope: !355)
!363 = !DILocation(line: 28, column: 30, scope: !355)
!364 = !DILocation(line: 30, column: 44, scope: !355)
!365 = !DILocation(line: 30, column: 41, scope: !355)
!366 = !DILocation(line: 30, column: 18, scope: !355)
!367 = !DILocation(line: 30, column: 25, scope: !355)
!368 = !DILocation(line: 30, column: 28, scope: !355)
!369 = !DILocation(line: 30, column: 31, scope: !355)
!370 = !DILocation(line: 30, column: 3, scope: !355)
!371 = !DILocation(line: 30, column: 10, scope: !355)
!372 = !DILocation(line: 30, column: 39, scope: !355)
!373 = !DILocation(line: 31, column: 15, scope: !355)
!374 = !DILocation(line: 31, column: 12, scope: !355)
!375 = !DILocation(line: 31, column: 20, scope: !355)
!376 = !DILocation(line: 31, column: 18, scope: !355)
!377 = !DILocation(line: 31, column: 7, scope: !355)
!378 = !DILocation(line: 31, column: 3, scope: !355)
!379 = !DILocation(line: 31, column: 10, scope: !355)
!380 = !DILocation(line: 32, column: 2, scope: !355)
!381 = !DILocation(line: 27, column: 24, scope: !382)
!382 = !DILexicalBlockFile(scope: !350, file: !1, discriminator: 2)
!383 = !DILocation(line: 27, column: 2, scope: !382)
!384 = !DILocation(line: 33, column: 1, scope: !144)
!385 = !DILocalVariable(name: "coder", arg: 1, scope: !147, file: !1, line: 39, type: !48)
!386 = !DILocation(line: 39, column: 29, scope: !147)
!387 = !DILocalVariable(name: "buffer", arg: 2, scope: !147, file: !1, line: 39, type: !96)
!388 = !DILocation(line: 39, column: 45, scope: !147)
!389 = !DILocalVariable(name: "size", arg: 3, scope: !147, file: !1, line: 39, type: !55)
!390 = !DILocation(line: 39, column: 60, scope: !147)
!391 = !DILocalVariable(name: "i", scope: !147, file: !1, line: 41, type: !55)
!392 = !DILocation(line: 41, column: 9, scope: !147)
!393 = !DILocalVariable(name: "distance", scope: !147, file: !1, line: 42, type: !200)
!394 = !DILocation(line: 42, column: 15, scope: !147)
!395 = !DILocation(line: 42, column: 26, scope: !147)
!396 = !DILocation(line: 42, column: 33, scope: !147)
!397 = !DILocation(line: 44, column: 9, scope: !398)
!398 = distinct !DILexicalBlock(scope: !147, file: !1, line: 44, column: 2)
!399 = !DILocation(line: 44, column: 7, scope: !398)
!400 = !DILocation(line: 44, column: 14, scope: !401)
!401 = !DILexicalBlockFile(scope: !402, file: !1, discriminator: 1)
!402 = distinct !DILexicalBlock(scope: !398, file: !1, line: 44, column: 2)
!403 = !DILocation(line: 44, column: 18, scope: !401)
!404 = !DILocation(line: 44, column: 16, scope: !401)
!405 = !DILocation(line: 44, column: 2, scope: !401)
!406 = !DILocalVariable(name: "tmp", scope: !407, file: !1, line: 45, type: !92)
!407 = distinct !DILexicalBlock(scope: !402, file: !1, line: 44, column: 29)
!408 = !DILocation(line: 45, column: 17, scope: !407)
!409 = !DILocation(line: 46, column: 6, scope: !407)
!410 = !DILocation(line: 46, column: 17, scope: !407)
!411 = !DILocation(line: 46, column: 24, scope: !407)
!412 = !DILocation(line: 46, column: 15, scope: !407)
!413 = !DILocation(line: 46, column: 29, scope: !407)
!414 = !DILocation(line: 45, column: 23, scope: !407)
!415 = !DILocation(line: 45, column: 30, scope: !407)
!416 = !DILocation(line: 47, column: 48, scope: !407)
!417 = !DILocation(line: 47, column: 41, scope: !407)
!418 = !DILocation(line: 47, column: 18, scope: !407)
!419 = !DILocation(line: 47, column: 25, scope: !407)
!420 = !DILocation(line: 47, column: 28, scope: !407)
!421 = !DILocation(line: 47, column: 31, scope: !407)
!422 = !DILocation(line: 47, column: 3, scope: !407)
!423 = !DILocation(line: 47, column: 10, scope: !407)
!424 = !DILocation(line: 47, column: 39, scope: !407)
!425 = !DILocation(line: 48, column: 16, scope: !407)
!426 = !DILocation(line: 48, column: 10, scope: !407)
!427 = !DILocation(line: 48, column: 3, scope: !407)
!428 = !DILocation(line: 48, column: 13, scope: !407)
!429 = !DILocation(line: 49, column: 2, scope: !407)
!430 = !DILocation(line: 44, column: 24, scope: !431)
!431 = !DILexicalBlockFile(scope: !402, file: !1, discriminator: 2)
!432 = !DILocation(line: 44, column: 2, scope: !431)
!433 = !DILocation(line: 50, column: 1, scope: !147)
