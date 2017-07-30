; ModuleID = '/data/download/cmake/cmake-master/Utilities/cmliblzma/liblzma/common/common.c'
target datalayout = "e-m:e-i64:64-f80:128-n8:16:32:64-S128"
target triple = "x86_64-unknown-linux-gnu"

%struct.lzma_next_coder_s = type { %struct.lzma_coder_s*, i64, i64, i32 (%struct.lzma_coder_s*, %struct.lzma_allocator*, i8*, i64*, i64, i8*, i64*, i64, i32)*, void (%struct.lzma_coder_s*, %struct.lzma_allocator*)*, i32 (%struct.lzma_coder_s*)*, i32 (%struct.lzma_coder_s*, i64*, i64*, i64)*, i32 (%struct.lzma_coder_s*, %struct.lzma_allocator*, %struct.lzma_filter*, %struct.lzma_filter*)* }
%struct.lzma_coder_s = type opaque
%struct.lzma_allocator = type { i8* (i8*, i64, i64)*, void (i8*, i8*)*, i8* }
%struct.lzma_filter = type { i64, i8* }
%struct.lzma_filter_info_s = type { i64, {}*, i8* }
%struct.lzma_stream = type { i8*, i64, i64, i8*, i64, i64, %struct.lzma_allocator*, %struct.lzma_internal_s*, i8*, i8*, i8*, i8*, i64, i64, i64, i64, i32, i32 }
%struct.lzma_internal_s = type { %struct.lzma_next_coder_s, i32, i64, [4 x i8], i8 }

@.str = private unnamed_addr constant [6 x i8] c"5.0.8\00", align 1
@.str.1 = private unnamed_addr constant [27 x i8] c"next->update != ((void*)0)\00", align 1
@.str.2 = private unnamed_addr constant [78 x i8] c"/data/download/cmake/cmake-master/Utilities/cmliblzma/liblzma/common/common.c\00", align 1
@__PRETTY_FUNCTION__.lzma_next_filter_update = private unnamed_addr constant [91 x i8] c"lzma_ret lzma_next_filter_update(lzma_next_coder *, lzma_allocator *, const lzma_filter *)\00", align 1
@LZMA_NEXT_CODER_INIT = internal constant %struct.lzma_next_coder_s { %struct.lzma_coder_s* null, i64 -1, i64 0, i32 (%struct.lzma_coder_s*, %struct.lzma_allocator*, i8*, i64*, i64, i8*, i64*, i64, i32)* null, void (%struct.lzma_coder_s*, %struct.lzma_allocator*)* null, i32 (%struct.lzma_coder_s*)* null, i32 (%struct.lzma_coder_s*, i64*, i64*, i64)* null, i32 (%struct.lzma_coder_s*, %struct.lzma_allocator*, %struct.lzma_filter*, %struct.lzma_filter*)* null }, align 8
@.str.3 = private unnamed_addr constant [22 x i8] c"ret != LZMA_BUF_ERROR\00", align 1
@__PRETTY_FUNCTION__.lzma_code = private unnamed_addr constant [47 x i8] c"lzma_ret lzma_code(lzma_stream *, lzma_action)\00", align 1

; Function Attrs: nounwind readnone uwtable
define i32 @lzma_version_number() #0 !dbg !133 {
entry:
  ret i32 50000082, !dbg !225
}

; Function Attrs: nounwind readnone uwtable
define i8* @lzma_version_string() #0 !dbg !138 {
entry:
  ret i8* getelementptr inbounds ([6 x i8], [6 x i8]* @.str, i32 0, i32 0), !dbg !226
}

; Function Attrs: nounwind uwtable
define noalias i8* @lzma_alloc(i64 %size, %struct.lzma_allocator* %allocator) #1 !dbg !144 {
entry:
  %size.addr = alloca i64, align 8
  %allocator.addr = alloca %struct.lzma_allocator*, align 8
  %ptr = alloca i8*, align 8
  store i64 %size, i64* %size.addr, align 8
  call void @llvm.dbg.declare(metadata i64* %size.addr, metadata !227, metadata !228), !dbg !229
  store %struct.lzma_allocator* %allocator, %struct.lzma_allocator** %allocator.addr, align 8
  call void @llvm.dbg.declare(metadata %struct.lzma_allocator** %allocator.addr, metadata !230, metadata !228), !dbg !231
  call void @llvm.dbg.declare(metadata i8** %ptr, metadata !232, metadata !228), !dbg !233
  %0 = load i64, i64* %size.addr, align 8, !dbg !234
  %cmp = icmp eq i64 %0, 0, !dbg !236
  br i1 %cmp, label %if.then, label %if.end, !dbg !237

if.then:                                          ; preds = %entry
  store i64 1, i64* %size.addr, align 8, !dbg !238
  br label %if.end, !dbg !239

if.end:                                           ; preds = %if.then, %entry
  %1 = load %struct.lzma_allocator*, %struct.lzma_allocator** %allocator.addr, align 8, !dbg !240
  %cmp1 = icmp ne %struct.lzma_allocator* %1, null, !dbg !242
  br i1 %cmp1, label %land.lhs.true, label %if.else, !dbg !243

land.lhs.true:                                    ; preds = %if.end
  %2 = load %struct.lzma_allocator*, %struct.lzma_allocator** %allocator.addr, align 8, !dbg !244
  %alloc = getelementptr inbounds %struct.lzma_allocator, %struct.lzma_allocator* %2, i32 0, i32 0, !dbg !246
  %3 = load i8* (i8*, i64, i64)*, i8* (i8*, i64, i64)** %alloc, align 8, !dbg !246
  %cmp2 = icmp ne i8* (i8*, i64, i64)* %3, null, !dbg !247
  br i1 %cmp2, label %if.then3, label %if.else, !dbg !248

if.then3:                                         ; preds = %land.lhs.true
  %4 = load %struct.lzma_allocator*, %struct.lzma_allocator** %allocator.addr, align 8, !dbg !249
  %alloc4 = getelementptr inbounds %struct.lzma_allocator, %struct.lzma_allocator* %4, i32 0, i32 0, !dbg !250
  %5 = load i8* (i8*, i64, i64)*, i8* (i8*, i64, i64)** %alloc4, align 8, !dbg !250
  %6 = load %struct.lzma_allocator*, %struct.lzma_allocator** %allocator.addr, align 8, !dbg !251
  %opaque = getelementptr inbounds %struct.lzma_allocator, %struct.lzma_allocator* %6, i32 0, i32 2, !dbg !252
  %7 = load i8*, i8** %opaque, align 8, !dbg !252
  %8 = load i64, i64* %size.addr, align 8, !dbg !253
  %call = call i8* %5(i8* %7, i64 1, i64 %8), !dbg !249
  store i8* %call, i8** %ptr, align 8, !dbg !254
  br label %if.end6, !dbg !255

if.else:                                          ; preds = %land.lhs.true, %if.end
  %9 = load i64, i64* %size.addr, align 8, !dbg !256
  %call5 = call noalias i8* @malloc(i64 %9) #7, !dbg !257
  store i8* %call5, i8** %ptr, align 8, !dbg !258
  br label %if.end6

if.end6:                                          ; preds = %if.else, %if.then3
  %10 = load i8*, i8** %ptr, align 8, !dbg !259
  ret i8* %10, !dbg !260
}

; Function Attrs: nounwind readnone
declare void @llvm.dbg.declare(metadata, metadata, metadata) #2

; Function Attrs: nounwind
declare noalias i8* @malloc(i64) #3

; Function Attrs: nounwind uwtable
define void @lzma_free(i8* %ptr, %struct.lzma_allocator* %allocator) #1 !dbg !147 {
entry:
  %ptr.addr = alloca i8*, align 8
  %allocator.addr = alloca %struct.lzma_allocator*, align 8
  store i8* %ptr, i8** %ptr.addr, align 8
  call void @llvm.dbg.declare(metadata i8** %ptr.addr, metadata !261, metadata !228), !dbg !262
  store %struct.lzma_allocator* %allocator, %struct.lzma_allocator** %allocator.addr, align 8
  call void @llvm.dbg.declare(metadata %struct.lzma_allocator** %allocator.addr, metadata !263, metadata !228), !dbg !264
  %0 = load %struct.lzma_allocator*, %struct.lzma_allocator** %allocator.addr, align 8, !dbg !265
  %cmp = icmp ne %struct.lzma_allocator* %0, null, !dbg !267
  br i1 %cmp, label %land.lhs.true, label %if.else, !dbg !268

land.lhs.true:                                    ; preds = %entry
  %1 = load %struct.lzma_allocator*, %struct.lzma_allocator** %allocator.addr, align 8, !dbg !269
  %free = getelementptr inbounds %struct.lzma_allocator, %struct.lzma_allocator* %1, i32 0, i32 1, !dbg !271
  %2 = load void (i8*, i8*)*, void (i8*, i8*)** %free, align 8, !dbg !271
  %cmp1 = icmp ne void (i8*, i8*)* %2, null, !dbg !272
  br i1 %cmp1, label %if.then, label %if.else, !dbg !273

if.then:                                          ; preds = %land.lhs.true
  %3 = load %struct.lzma_allocator*, %struct.lzma_allocator** %allocator.addr, align 8, !dbg !274
  %free2 = getelementptr inbounds %struct.lzma_allocator, %struct.lzma_allocator* %3, i32 0, i32 1, !dbg !275
  %4 = load void (i8*, i8*)*, void (i8*, i8*)** %free2, align 8, !dbg !275
  %5 = load %struct.lzma_allocator*, %struct.lzma_allocator** %allocator.addr, align 8, !dbg !276
  %opaque = getelementptr inbounds %struct.lzma_allocator, %struct.lzma_allocator* %5, i32 0, i32 2, !dbg !277
  %6 = load i8*, i8** %opaque, align 8, !dbg !277
  %7 = load i8*, i8** %ptr.addr, align 8, !dbg !278
  call void %4(i8* %6, i8* %7), !dbg !274
  br label %if.end, !dbg !274

if.else:                                          ; preds = %land.lhs.true, %entry
  %8 = load i8*, i8** %ptr.addr, align 8, !dbg !279
  call void @free(i8* %8) #7, !dbg !280
  br label %if.end

if.end:                                           ; preds = %if.else, %if.then
  ret void, !dbg !281
}

; Function Attrs: nounwind
declare void @free(i8*) #3

; Function Attrs: nounwind uwtable
define i64 @lzma_bufcpy(i8* noalias %in, i64* noalias %in_pos, i64 %in_size, i8* noalias %out, i64* noalias %out_pos, i64 %out_size) #1 !dbg !150 {
entry:
  %in.addr = alloca i8*, align 8
  %in_pos.addr = alloca i64*, align 8
  %in_size.addr = alloca i64, align 8
  %out.addr = alloca i8*, align 8
  %out_pos.addr = alloca i64*, align 8
  %out_size.addr = alloca i64, align 8
  %in_avail = alloca i64, align 8
  %out_avail = alloca i64, align 8
  %copy_size = alloca i64, align 8
  store i8* %in, i8** %in.addr, align 8
  call void @llvm.dbg.declare(metadata i8** %in.addr, metadata !282, metadata !228), !dbg !283
  store i64* %in_pos, i64** %in_pos.addr, align 8
  call void @llvm.dbg.declare(metadata i64** %in_pos.addr, metadata !284, metadata !228), !dbg !285
  store i64 %in_size, i64* %in_size.addr, align 8
  call void @llvm.dbg.declare(metadata i64* %in_size.addr, metadata !286, metadata !228), !dbg !287
  store i8* %out, i8** %out.addr, align 8
  call void @llvm.dbg.declare(metadata i8** %out.addr, metadata !288, metadata !228), !dbg !289
  store i64* %out_pos, i64** %out_pos.addr, align 8
  call void @llvm.dbg.declare(metadata i64** %out_pos.addr, metadata !290, metadata !228), !dbg !291
  store i64 %out_size, i64* %out_size.addr, align 8
  call void @llvm.dbg.declare(metadata i64* %out_size.addr, metadata !292, metadata !228), !dbg !293
  call void @llvm.dbg.declare(metadata i64* %in_avail, metadata !294, metadata !228), !dbg !296
  %0 = load i64, i64* %in_size.addr, align 8, !dbg !297
  %1 = load i64*, i64** %in_pos.addr, align 8, !dbg !298
  %2 = load i64, i64* %1, align 8, !dbg !299
  %sub = sub i64 %0, %2, !dbg !300
  store i64 %sub, i64* %in_avail, align 8, !dbg !296
  call void @llvm.dbg.declare(metadata i64* %out_avail, metadata !301, metadata !228), !dbg !302
  %3 = load i64, i64* %out_size.addr, align 8, !dbg !303
  %4 = load i64*, i64** %out_pos.addr, align 8, !dbg !304
  %5 = load i64, i64* %4, align 8, !dbg !305
  %sub1 = sub i64 %3, %5, !dbg !306
  store i64 %sub1, i64* %out_avail, align 8, !dbg !302
  call void @llvm.dbg.declare(metadata i64* %copy_size, metadata !307, metadata !228), !dbg !308
  %6 = load i64, i64* %in_avail, align 8, !dbg !309
  %7 = load i64, i64* %out_avail, align 8, !dbg !309
  %cmp = icmp ult i64 %6, %7, !dbg !309
  br i1 %cmp, label %cond.true, label %cond.false, !dbg !309

cond.true:                                        ; preds = %entry
  %8 = load i64, i64* %in_avail, align 8, !dbg !310
  br label %cond.end, !dbg !310

cond.false:                                       ; preds = %entry
  %9 = load i64, i64* %out_avail, align 8, !dbg !312
  br label %cond.end, !dbg !312

cond.end:                                         ; preds = %cond.false, %cond.true
  %cond = phi i64 [ %8, %cond.true ], [ %9, %cond.false ], !dbg !314
  store i64 %cond, i64* %copy_size, align 8, !dbg !316
  %10 = load i8*, i8** %out.addr, align 8, !dbg !317
  %11 = load i64*, i64** %out_pos.addr, align 8, !dbg !318
  %12 = load i64, i64* %11, align 8, !dbg !319
  %add.ptr = getelementptr inbounds i8, i8* %10, i64 %12, !dbg !320
  %13 = load i8*, i8** %in.addr, align 8, !dbg !321
  %14 = load i64*, i64** %in_pos.addr, align 8, !dbg !322
  %15 = load i64, i64* %14, align 8, !dbg !323
  %add.ptr2 = getelementptr inbounds i8, i8* %13, i64 %15, !dbg !324
  %16 = load i64, i64* %copy_size, align 8, !dbg !325
  call void @llvm.memcpy.p0i8.p0i8.i64(i8* %add.ptr, i8* %add.ptr2, i64 %16, i32 1, i1 false), !dbg !326
  %17 = load i64, i64* %copy_size, align 8, !dbg !327
  %18 = load i64*, i64** %in_pos.addr, align 8, !dbg !328
  %19 = load i64, i64* %18, align 8, !dbg !329
  %add = add i64 %19, %17, !dbg !329
  store i64 %add, i64* %18, align 8, !dbg !329
  %20 = load i64, i64* %copy_size, align 8, !dbg !330
  %21 = load i64*, i64** %out_pos.addr, align 8, !dbg !331
  %22 = load i64, i64* %21, align 8, !dbg !332
  %add3 = add i64 %22, %20, !dbg !332
  store i64 %add3, i64* %21, align 8, !dbg !332
  %23 = load i64, i64* %copy_size, align 8, !dbg !333
  ret i64 %23, !dbg !334
}

; Function Attrs: argmemonly nounwind
declare void @llvm.memcpy.p0i8.p0i8.i64(i8* nocapture, i8* nocapture readonly, i64, i32, i1) #4

; Function Attrs: nounwind uwtable
define i32 @lzma_next_filter_init(%struct.lzma_next_coder_s* %next, %struct.lzma_allocator* %allocator, %struct.lzma_filter_info_s* %filters) #1 !dbg !153 {
entry:
  %next.addr = alloca %struct.lzma_next_coder_s*, align 8
  %allocator.addr = alloca %struct.lzma_allocator*, align 8
  %filters.addr = alloca %struct.lzma_filter_info_s*, align 8
  store %struct.lzma_next_coder_s* %next, %struct.lzma_next_coder_s** %next.addr, align 8
  call void @llvm.dbg.declare(metadata %struct.lzma_next_coder_s** %next.addr, metadata !335, metadata !228), !dbg !336
  store %struct.lzma_allocator* %allocator, %struct.lzma_allocator** %allocator.addr, align 8
  call void @llvm.dbg.declare(metadata %struct.lzma_allocator** %allocator.addr, metadata !337, metadata !228), !dbg !338
  store %struct.lzma_filter_info_s* %filters, %struct.lzma_filter_info_s** %filters.addr, align 8
  call void @llvm.dbg.declare(metadata %struct.lzma_filter_info_s** %filters.addr, metadata !339, metadata !228), !dbg !340
  br label %do.body, !dbg !341

do.body:                                          ; preds = %entry
  %0 = load %struct.lzma_filter_info_s*, %struct.lzma_filter_info_s** %filters.addr, align 8, !dbg !342
  %arrayidx = getelementptr inbounds %struct.lzma_filter_info_s, %struct.lzma_filter_info_s* %0, i64 0, !dbg !342
  %init = getelementptr inbounds %struct.lzma_filter_info_s, %struct.lzma_filter_info_s* %arrayidx, i32 0, i32 1, !dbg !342
  %init1 = bitcast {}** %init to i32 (%struct.lzma_next_coder_s*, %struct.lzma_allocator*, %struct.lzma_filter_info_s*)**, !dbg !342
  %1 = load i32 (%struct.lzma_next_coder_s*, %struct.lzma_allocator*, %struct.lzma_filter_info_s*)*, i32 (%struct.lzma_next_coder_s*, %struct.lzma_allocator*, %struct.lzma_filter_info_s*)** %init1, align 8, !dbg !342
  %2 = ptrtoint i32 (%struct.lzma_next_coder_s*, %struct.lzma_allocator*, %struct.lzma_filter_info_s*)* %1 to i64, !dbg !342
  %3 = load %struct.lzma_next_coder_s*, %struct.lzma_next_coder_s** %next.addr, align 8, !dbg !342
  %init2 = getelementptr inbounds %struct.lzma_next_coder_s, %struct.lzma_next_coder_s* %3, i32 0, i32 2, !dbg !342
  %4 = load i64, i64* %init2, align 8, !dbg !342
  %cmp = icmp ne i64 %2, %4, !dbg !342
  br i1 %cmp, label %if.then, label %if.end, !dbg !342

if.then:                                          ; preds = %do.body
  %5 = load %struct.lzma_next_coder_s*, %struct.lzma_next_coder_s** %next.addr, align 8, !dbg !346
  %6 = load %struct.lzma_allocator*, %struct.lzma_allocator** %allocator.addr, align 8, !dbg !346
  call void @lzma_next_end(%struct.lzma_next_coder_s* %5, %struct.lzma_allocator* %6), !dbg !346
  br label %if.end, !dbg !346

if.end:                                           ; preds = %if.then, %do.body
  %7 = load %struct.lzma_filter_info_s*, %struct.lzma_filter_info_s** %filters.addr, align 8, !dbg !348
  %arrayidx3 = getelementptr inbounds %struct.lzma_filter_info_s, %struct.lzma_filter_info_s* %7, i64 0, !dbg !348
  %init4 = getelementptr inbounds %struct.lzma_filter_info_s, %struct.lzma_filter_info_s* %arrayidx3, i32 0, i32 1, !dbg !348
  %init5 = bitcast {}** %init4 to i32 (%struct.lzma_next_coder_s*, %struct.lzma_allocator*, %struct.lzma_filter_info_s*)**, !dbg !348
  %8 = load i32 (%struct.lzma_next_coder_s*, %struct.lzma_allocator*, %struct.lzma_filter_info_s*)*, i32 (%struct.lzma_next_coder_s*, %struct.lzma_allocator*, %struct.lzma_filter_info_s*)** %init5, align 8, !dbg !348
  %9 = ptrtoint i32 (%struct.lzma_next_coder_s*, %struct.lzma_allocator*, %struct.lzma_filter_info_s*)* %8 to i64, !dbg !348
  %10 = load %struct.lzma_next_coder_s*, %struct.lzma_next_coder_s** %next.addr, align 8, !dbg !348
  %init6 = getelementptr inbounds %struct.lzma_next_coder_s, %struct.lzma_next_coder_s* %10, i32 0, i32 2, !dbg !348
  store i64 %9, i64* %init6, align 8, !dbg !348
  br label %do.end, !dbg !348

do.end:                                           ; preds = %if.end
  %11 = load %struct.lzma_filter_info_s*, %struct.lzma_filter_info_s** %filters.addr, align 8, !dbg !350
  %arrayidx7 = getelementptr inbounds %struct.lzma_filter_info_s, %struct.lzma_filter_info_s* %11, i64 0, !dbg !350
  %id = getelementptr inbounds %struct.lzma_filter_info_s, %struct.lzma_filter_info_s* %arrayidx7, i32 0, i32 0, !dbg !351
  %12 = load i64, i64* %id, align 8, !dbg !351
  %13 = load %struct.lzma_next_coder_s*, %struct.lzma_next_coder_s** %next.addr, align 8, !dbg !352
  %id8 = getelementptr inbounds %struct.lzma_next_coder_s, %struct.lzma_next_coder_s* %13, i32 0, i32 1, !dbg !353
  store i64 %12, i64* %id8, align 8, !dbg !354
  %14 = load %struct.lzma_filter_info_s*, %struct.lzma_filter_info_s** %filters.addr, align 8, !dbg !355
  %arrayidx9 = getelementptr inbounds %struct.lzma_filter_info_s, %struct.lzma_filter_info_s* %14, i64 0, !dbg !355
  %init10 = getelementptr inbounds %struct.lzma_filter_info_s, %struct.lzma_filter_info_s* %arrayidx9, i32 0, i32 1, !dbg !356
  %init11 = bitcast {}** %init10 to i32 (%struct.lzma_next_coder_s*, %struct.lzma_allocator*, %struct.lzma_filter_info_s*)**, !dbg !356
  %15 = load i32 (%struct.lzma_next_coder_s*, %struct.lzma_allocator*, %struct.lzma_filter_info_s*)*, i32 (%struct.lzma_next_coder_s*, %struct.lzma_allocator*, %struct.lzma_filter_info_s*)** %init11, align 8, !dbg !356
  %cmp12 = icmp eq i32 (%struct.lzma_next_coder_s*, %struct.lzma_allocator*, %struct.lzma_filter_info_s*)* %15, null, !dbg !357
  br i1 %cmp12, label %cond.true, label %cond.false, !dbg !355

cond.true:                                        ; preds = %do.end
  br label %cond.end, !dbg !358

cond.false:                                       ; preds = %do.end
  %16 = load %struct.lzma_filter_info_s*, %struct.lzma_filter_info_s** %filters.addr, align 8, !dbg !360
  %arrayidx13 = getelementptr inbounds %struct.lzma_filter_info_s, %struct.lzma_filter_info_s* %16, i64 0, !dbg !360
  %init14 = getelementptr inbounds %struct.lzma_filter_info_s, %struct.lzma_filter_info_s* %arrayidx13, i32 0, i32 1, !dbg !361
  %init15 = bitcast {}** %init14 to i32 (%struct.lzma_next_coder_s*, %struct.lzma_allocator*, %struct.lzma_filter_info_s*)**, !dbg !361
  %17 = load i32 (%struct.lzma_next_coder_s*, %struct.lzma_allocator*, %struct.lzma_filter_info_s*)*, i32 (%struct.lzma_next_coder_s*, %struct.lzma_allocator*, %struct.lzma_filter_info_s*)** %init15, align 8, !dbg !361
  %18 = load %struct.lzma_next_coder_s*, %struct.lzma_next_coder_s** %next.addr, align 8, !dbg !362
  %19 = load %struct.lzma_allocator*, %struct.lzma_allocator** %allocator.addr, align 8, !dbg !363
  %20 = load %struct.lzma_filter_info_s*, %struct.lzma_filter_info_s** %filters.addr, align 8, !dbg !364
  %call = call i32 %17(%struct.lzma_next_coder_s* %18, %struct.lzma_allocator* %19, %struct.lzma_filter_info_s* %20), !dbg !360
  br label %cond.end, !dbg !365

cond.end:                                         ; preds = %cond.false, %cond.true
  %cond = phi i32 [ 0, %cond.true ], [ %call, %cond.false ], !dbg !367
  ret i32 %cond, !dbg !369
}

; Function Attrs: nounwind uwtable
define void @lzma_next_end(%struct.lzma_next_coder_s* %next, %struct.lzma_allocator* %allocator) #1 !dbg !170 {
entry:
  %next.addr = alloca %struct.lzma_next_coder_s*, align 8
  %allocator.addr = alloca %struct.lzma_allocator*, align 8
  store %struct.lzma_next_coder_s* %next, %struct.lzma_next_coder_s** %next.addr, align 8
  call void @llvm.dbg.declare(metadata %struct.lzma_next_coder_s** %next.addr, metadata !370, metadata !228), !dbg !371
  store %struct.lzma_allocator* %allocator, %struct.lzma_allocator** %allocator.addr, align 8
  call void @llvm.dbg.declare(metadata %struct.lzma_allocator** %allocator.addr, metadata !372, metadata !228), !dbg !373
  %0 = load %struct.lzma_next_coder_s*, %struct.lzma_next_coder_s** %next.addr, align 8, !dbg !374
  %init = getelementptr inbounds %struct.lzma_next_coder_s, %struct.lzma_next_coder_s* %0, i32 0, i32 2, !dbg !376
  %1 = load i64, i64* %init, align 8, !dbg !376
  %cmp = icmp ne i64 %1, 0, !dbg !377
  br i1 %cmp, label %if.then, label %if.end5, !dbg !378

if.then:                                          ; preds = %entry
  %2 = load %struct.lzma_next_coder_s*, %struct.lzma_next_coder_s** %next.addr, align 8, !dbg !379
  %end = getelementptr inbounds %struct.lzma_next_coder_s, %struct.lzma_next_coder_s* %2, i32 0, i32 4, !dbg !382
  %3 = load void (%struct.lzma_coder_s*, %struct.lzma_allocator*)*, void (%struct.lzma_coder_s*, %struct.lzma_allocator*)** %end, align 8, !dbg !382
  %cmp1 = icmp ne void (%struct.lzma_coder_s*, %struct.lzma_allocator*)* %3, null, !dbg !383
  br i1 %cmp1, label %if.then2, label %if.else, !dbg !384

if.then2:                                         ; preds = %if.then
  %4 = load %struct.lzma_next_coder_s*, %struct.lzma_next_coder_s** %next.addr, align 8, !dbg !385
  %end3 = getelementptr inbounds %struct.lzma_next_coder_s, %struct.lzma_next_coder_s* %4, i32 0, i32 4, !dbg !386
  %5 = load void (%struct.lzma_coder_s*, %struct.lzma_allocator*)*, void (%struct.lzma_coder_s*, %struct.lzma_allocator*)** %end3, align 8, !dbg !386
  %6 = load %struct.lzma_next_coder_s*, %struct.lzma_next_coder_s** %next.addr, align 8, !dbg !387
  %coder = getelementptr inbounds %struct.lzma_next_coder_s, %struct.lzma_next_coder_s* %6, i32 0, i32 0, !dbg !388
  %7 = load %struct.lzma_coder_s*, %struct.lzma_coder_s** %coder, align 8, !dbg !388
  %8 = load %struct.lzma_allocator*, %struct.lzma_allocator** %allocator.addr, align 8, !dbg !389
  call void %5(%struct.lzma_coder_s* %7, %struct.lzma_allocator* %8), !dbg !385
  br label %if.end, !dbg !385

if.else:                                          ; preds = %if.then
  %9 = load %struct.lzma_next_coder_s*, %struct.lzma_next_coder_s** %next.addr, align 8, !dbg !390
  %coder4 = getelementptr inbounds %struct.lzma_next_coder_s, %struct.lzma_next_coder_s* %9, i32 0, i32 0, !dbg !391
  %10 = load %struct.lzma_coder_s*, %struct.lzma_coder_s** %coder4, align 8, !dbg !391
  %11 = bitcast %struct.lzma_coder_s* %10 to i8*, !dbg !390
  %12 = load %struct.lzma_allocator*, %struct.lzma_allocator** %allocator.addr, align 8, !dbg !392
  call void @lzma_free(i8* %11, %struct.lzma_allocator* %12), !dbg !393
  br label %if.end

if.end:                                           ; preds = %if.else, %if.then2
  %13 = load %struct.lzma_next_coder_s*, %struct.lzma_next_coder_s** %next.addr, align 8, !dbg !394
  %14 = bitcast %struct.lzma_next_coder_s* %13 to i8*, !dbg !395
  call void @llvm.memcpy.p0i8.p0i8.i64(i8* %14, i8* bitcast (%struct.lzma_next_coder_s* @LZMA_NEXT_CODER_INIT to i8*), i64 64, i32 8, i1 false), !dbg !395
  br label %if.end5, !dbg !396

if.end5:                                          ; preds = %if.end, %entry
  ret void, !dbg !397
}

; Function Attrs: nounwind uwtable
define i32 @lzma_next_filter_update(%struct.lzma_next_coder_s* %next, %struct.lzma_allocator* %allocator, %struct.lzma_filter* %reversed_filters) #1 !dbg !167 {
entry:
  %retval = alloca i32, align 4
  %next.addr = alloca %struct.lzma_next_coder_s*, align 8
  %allocator.addr = alloca %struct.lzma_allocator*, align 8
  %reversed_filters.addr = alloca %struct.lzma_filter*, align 8
  store %struct.lzma_next_coder_s* %next, %struct.lzma_next_coder_s** %next.addr, align 8
  call void @llvm.dbg.declare(metadata %struct.lzma_next_coder_s** %next.addr, metadata !398, metadata !228), !dbg !399
  store %struct.lzma_allocator* %allocator, %struct.lzma_allocator** %allocator.addr, align 8
  call void @llvm.dbg.declare(metadata %struct.lzma_allocator** %allocator.addr, metadata !400, metadata !228), !dbg !401
  store %struct.lzma_filter* %reversed_filters, %struct.lzma_filter** %reversed_filters.addr, align 8
  call void @llvm.dbg.declare(metadata %struct.lzma_filter** %reversed_filters.addr, metadata !402, metadata !228), !dbg !403
  %0 = load %struct.lzma_filter*, %struct.lzma_filter** %reversed_filters.addr, align 8, !dbg !404
  %arrayidx = getelementptr inbounds %struct.lzma_filter, %struct.lzma_filter* %0, i64 0, !dbg !404
  %id = getelementptr inbounds %struct.lzma_filter, %struct.lzma_filter* %arrayidx, i32 0, i32 0, !dbg !406
  %1 = load i64, i64* %id, align 8, !dbg !406
  %2 = load %struct.lzma_next_coder_s*, %struct.lzma_next_coder_s** %next.addr, align 8, !dbg !407
  %id1 = getelementptr inbounds %struct.lzma_next_coder_s, %struct.lzma_next_coder_s* %2, i32 0, i32 1, !dbg !408
  %3 = load i64, i64* %id1, align 8, !dbg !408
  %cmp = icmp ne i64 %1, %3, !dbg !409
  br i1 %cmp, label %if.then, label %if.end, !dbg !410

if.then:                                          ; preds = %entry
  store i32 11, i32* %retval, align 4, !dbg !411
  br label %return, !dbg !411

if.end:                                           ; preds = %entry
  %4 = load %struct.lzma_filter*, %struct.lzma_filter** %reversed_filters.addr, align 8, !dbg !412
  %arrayidx2 = getelementptr inbounds %struct.lzma_filter, %struct.lzma_filter* %4, i64 0, !dbg !412
  %id3 = getelementptr inbounds %struct.lzma_filter, %struct.lzma_filter* %arrayidx2, i32 0, i32 0, !dbg !414
  %5 = load i64, i64* %id3, align 8, !dbg !414
  %cmp4 = icmp eq i64 %5, -1, !dbg !415
  br i1 %cmp4, label %if.then5, label %if.end6, !dbg !416

if.then5:                                         ; preds = %if.end
  store i32 0, i32* %retval, align 4, !dbg !417
  br label %return, !dbg !417

if.end6:                                          ; preds = %if.end
  %6 = load %struct.lzma_next_coder_s*, %struct.lzma_next_coder_s** %next.addr, align 8, !dbg !418
  %update = getelementptr inbounds %struct.lzma_next_coder_s, %struct.lzma_next_coder_s* %6, i32 0, i32 7, !dbg !418
  %7 = load i32 (%struct.lzma_coder_s*, %struct.lzma_allocator*, %struct.lzma_filter*, %struct.lzma_filter*)*, i32 (%struct.lzma_coder_s*, %struct.lzma_allocator*, %struct.lzma_filter*, %struct.lzma_filter*)** %update, align 8, !dbg !418
  %cmp7 = icmp ne i32 (%struct.lzma_coder_s*, %struct.lzma_allocator*, %struct.lzma_filter*, %struct.lzma_filter*)* %7, null, !dbg !418
  br i1 %cmp7, label %cond.true, label %cond.false, !dbg !418

cond.true:                                        ; preds = %if.end6
  br label %cond.end, !dbg !419

cond.false:                                       ; preds = %if.end6
  call void @__assert_fail(i8* getelementptr inbounds ([27 x i8], [27 x i8]* @.str.1, i32 0, i32 0), i8* getelementptr inbounds ([78 x i8], [78 x i8]* @.str.2, i32 0, i32 0), i32 114, i8* getelementptr inbounds ([91 x i8], [91 x i8]* @__PRETTY_FUNCTION__.lzma_next_filter_update, i32 0, i32 0)) #8, !dbg !421
  unreachable, !dbg !421
                                                  ; No predecessors!
  br label %cond.end, !dbg !423

cond.end:                                         ; preds = %8, %cond.true
  %9 = load %struct.lzma_next_coder_s*, %struct.lzma_next_coder_s** %next.addr, align 8, !dbg !425
  %update8 = getelementptr inbounds %struct.lzma_next_coder_s, %struct.lzma_next_coder_s* %9, i32 0, i32 7, !dbg !426
  %10 = load i32 (%struct.lzma_coder_s*, %struct.lzma_allocator*, %struct.lzma_filter*, %struct.lzma_filter*)*, i32 (%struct.lzma_coder_s*, %struct.lzma_allocator*, %struct.lzma_filter*, %struct.lzma_filter*)** %update8, align 8, !dbg !426
  %11 = load %struct.lzma_next_coder_s*, %struct.lzma_next_coder_s** %next.addr, align 8, !dbg !427
  %coder = getelementptr inbounds %struct.lzma_next_coder_s, %struct.lzma_next_coder_s* %11, i32 0, i32 0, !dbg !428
  %12 = load %struct.lzma_coder_s*, %struct.lzma_coder_s** %coder, align 8, !dbg !428
  %13 = load %struct.lzma_allocator*, %struct.lzma_allocator** %allocator.addr, align 8, !dbg !429
  %14 = load %struct.lzma_filter*, %struct.lzma_filter** %reversed_filters.addr, align 8, !dbg !430
  %call = call i32 %10(%struct.lzma_coder_s* %12, %struct.lzma_allocator* %13, %struct.lzma_filter* null, %struct.lzma_filter* %14), !dbg !425
  store i32 %call, i32* %retval, align 4, !dbg !431
  br label %return, !dbg !431

return:                                           ; preds = %cond.end, %if.then5, %if.then
  %15 = load i32, i32* %retval, align 4, !dbg !432
  ret i32 %15, !dbg !432
}

; Function Attrs: noreturn nounwind
declare void @__assert_fail(i8*, i8*, i32, i8*) #5

; Function Attrs: nounwind uwtable
define i32 @lzma_strm_init(%struct.lzma_stream* %strm) #1 !dbg !173 {
entry:
  %retval = alloca i32, align 4
  %strm.addr = alloca %struct.lzma_stream*, align 8
  store %struct.lzma_stream* %strm, %struct.lzma_stream** %strm.addr, align 8
  call void @llvm.dbg.declare(metadata %struct.lzma_stream** %strm.addr, metadata !433, metadata !228), !dbg !434
  %0 = load %struct.lzma_stream*, %struct.lzma_stream** %strm.addr, align 8, !dbg !435
  %cmp = icmp eq %struct.lzma_stream* %0, null, !dbg !437
  br i1 %cmp, label %if.then, label %if.end, !dbg !438

if.then:                                          ; preds = %entry
  store i32 11, i32* %retval, align 4, !dbg !439
  br label %return, !dbg !439

if.end:                                           ; preds = %entry
  %1 = load %struct.lzma_stream*, %struct.lzma_stream** %strm.addr, align 8, !dbg !440
  %internal = getelementptr inbounds %struct.lzma_stream, %struct.lzma_stream* %1, i32 0, i32 7, !dbg !442
  %2 = load %struct.lzma_internal_s*, %struct.lzma_internal_s** %internal, align 8, !dbg !442
  %cmp1 = icmp eq %struct.lzma_internal_s* %2, null, !dbg !443
  br i1 %cmp1, label %if.then2, label %if.end9, !dbg !444

if.then2:                                         ; preds = %if.end
  %3 = load %struct.lzma_stream*, %struct.lzma_stream** %strm.addr, align 8, !dbg !445
  %allocator = getelementptr inbounds %struct.lzma_stream, %struct.lzma_stream* %3, i32 0, i32 6, !dbg !447
  %4 = load %struct.lzma_allocator*, %struct.lzma_allocator** %allocator, align 8, !dbg !447
  %call = call noalias i8* @lzma_alloc(i64 88, %struct.lzma_allocator* %4), !dbg !448
  %5 = bitcast i8* %call to %struct.lzma_internal_s*, !dbg !448
  %6 = load %struct.lzma_stream*, %struct.lzma_stream** %strm.addr, align 8, !dbg !449
  %internal3 = getelementptr inbounds %struct.lzma_stream, %struct.lzma_stream* %6, i32 0, i32 7, !dbg !450
  store %struct.lzma_internal_s* %5, %struct.lzma_internal_s** %internal3, align 8, !dbg !451
  %7 = load %struct.lzma_stream*, %struct.lzma_stream** %strm.addr, align 8, !dbg !452
  %internal4 = getelementptr inbounds %struct.lzma_stream, %struct.lzma_stream* %7, i32 0, i32 7, !dbg !454
  %8 = load %struct.lzma_internal_s*, %struct.lzma_internal_s** %internal4, align 8, !dbg !454
  %cmp5 = icmp eq %struct.lzma_internal_s* %8, null, !dbg !455
  br i1 %cmp5, label %if.then6, label %if.end7, !dbg !456

if.then6:                                         ; preds = %if.then2
  store i32 5, i32* %retval, align 4, !dbg !457
  br label %return, !dbg !457

if.end7:                                          ; preds = %if.then2
  %9 = load %struct.lzma_stream*, %struct.lzma_stream** %strm.addr, align 8, !dbg !458
  %internal8 = getelementptr inbounds %struct.lzma_stream, %struct.lzma_stream* %9, i32 0, i32 7, !dbg !459
  %10 = load %struct.lzma_internal_s*, %struct.lzma_internal_s** %internal8, align 8, !dbg !459
  %next = getelementptr inbounds %struct.lzma_internal_s, %struct.lzma_internal_s* %10, i32 0, i32 0, !dbg !460
  %11 = bitcast %struct.lzma_next_coder_s* %next to i8*, !dbg !461
  call void @llvm.memcpy.p0i8.p0i8.i64(i8* %11, i8* bitcast (%struct.lzma_next_coder_s* @LZMA_NEXT_CODER_INIT to i8*), i64 64, i32 8, i1 false), !dbg !461
  br label %if.end9, !dbg !462

if.end9:                                          ; preds = %if.end7, %if.end
  %12 = load %struct.lzma_stream*, %struct.lzma_stream** %strm.addr, align 8, !dbg !463
  %internal10 = getelementptr inbounds %struct.lzma_stream, %struct.lzma_stream* %12, i32 0, i32 7, !dbg !464
  %13 = load %struct.lzma_internal_s*, %struct.lzma_internal_s** %internal10, align 8, !dbg !464
  %supported_actions = getelementptr inbounds %struct.lzma_internal_s, %struct.lzma_internal_s* %13, i32 0, i32 3, !dbg !465
  %arrayidx = getelementptr inbounds [4 x i8], [4 x i8]* %supported_actions, i64 0, i64 0, !dbg !463
  store i8 0, i8* %arrayidx, align 8, !dbg !466
  %14 = load %struct.lzma_stream*, %struct.lzma_stream** %strm.addr, align 8, !dbg !467
  %internal11 = getelementptr inbounds %struct.lzma_stream, %struct.lzma_stream* %14, i32 0, i32 7, !dbg !468
  %15 = load %struct.lzma_internal_s*, %struct.lzma_internal_s** %internal11, align 8, !dbg !468
  %supported_actions12 = getelementptr inbounds %struct.lzma_internal_s, %struct.lzma_internal_s* %15, i32 0, i32 3, !dbg !469
  %arrayidx13 = getelementptr inbounds [4 x i8], [4 x i8]* %supported_actions12, i64 0, i64 1, !dbg !467
  store i8 0, i8* %arrayidx13, align 1, !dbg !470
  %16 = load %struct.lzma_stream*, %struct.lzma_stream** %strm.addr, align 8, !dbg !471
  %internal14 = getelementptr inbounds %struct.lzma_stream, %struct.lzma_stream* %16, i32 0, i32 7, !dbg !472
  %17 = load %struct.lzma_internal_s*, %struct.lzma_internal_s** %internal14, align 8, !dbg !472
  %supported_actions15 = getelementptr inbounds %struct.lzma_internal_s, %struct.lzma_internal_s* %17, i32 0, i32 3, !dbg !473
  %arrayidx16 = getelementptr inbounds [4 x i8], [4 x i8]* %supported_actions15, i64 0, i64 2, !dbg !471
  store i8 0, i8* %arrayidx16, align 2, !dbg !474
  %18 = load %struct.lzma_stream*, %struct.lzma_stream** %strm.addr, align 8, !dbg !475
  %internal17 = getelementptr inbounds %struct.lzma_stream, %struct.lzma_stream* %18, i32 0, i32 7, !dbg !476
  %19 = load %struct.lzma_internal_s*, %struct.lzma_internal_s** %internal17, align 8, !dbg !476
  %supported_actions18 = getelementptr inbounds %struct.lzma_internal_s, %struct.lzma_internal_s* %19, i32 0, i32 3, !dbg !477
  %arrayidx19 = getelementptr inbounds [4 x i8], [4 x i8]* %supported_actions18, i64 0, i64 3, !dbg !475
  store i8 0, i8* %arrayidx19, align 1, !dbg !478
  %20 = load %struct.lzma_stream*, %struct.lzma_stream** %strm.addr, align 8, !dbg !479
  %internal20 = getelementptr inbounds %struct.lzma_stream, %struct.lzma_stream* %20, i32 0, i32 7, !dbg !480
  %21 = load %struct.lzma_internal_s*, %struct.lzma_internal_s** %internal20, align 8, !dbg !480
  %sequence = getelementptr inbounds %struct.lzma_internal_s, %struct.lzma_internal_s* %21, i32 0, i32 1, !dbg !481
  store i32 0, i32* %sequence, align 8, !dbg !482
  %22 = load %struct.lzma_stream*, %struct.lzma_stream** %strm.addr, align 8, !dbg !483
  %internal21 = getelementptr inbounds %struct.lzma_stream, %struct.lzma_stream* %22, i32 0, i32 7, !dbg !484
  %23 = load %struct.lzma_internal_s*, %struct.lzma_internal_s** %internal21, align 8, !dbg !484
  %allow_buf_error = getelementptr inbounds %struct.lzma_internal_s, %struct.lzma_internal_s* %23, i32 0, i32 4, !dbg !485
  store i8 0, i8* %allow_buf_error, align 4, !dbg !486
  %24 = load %struct.lzma_stream*, %struct.lzma_stream** %strm.addr, align 8, !dbg !487
  %total_in = getelementptr inbounds %struct.lzma_stream, %struct.lzma_stream* %24, i32 0, i32 2, !dbg !488
  store i64 0, i64* %total_in, align 8, !dbg !489
  %25 = load %struct.lzma_stream*, %struct.lzma_stream** %strm.addr, align 8, !dbg !490
  %total_out = getelementptr inbounds %struct.lzma_stream, %struct.lzma_stream* %25, i32 0, i32 5, !dbg !491
  store i64 0, i64* %total_out, align 8, !dbg !492
  store i32 0, i32* %retval, align 4, !dbg !493
  br label %return, !dbg !493

return:                                           ; preds = %if.end9, %if.then6, %if.then
  %26 = load i32, i32* %retval, align 4, !dbg !494
  ret i32 %26, !dbg !494
}

; Function Attrs: nounwind uwtable
define i32 @lzma_code(%struct.lzma_stream* %strm, i32 %action) #1 !dbg !201 {
entry:
  %retval = alloca i32, align 4
  %strm.addr = alloca %struct.lzma_stream*, align 8
  %action.addr = alloca i32, align 4
  %in_pos = alloca i64, align 8
  %out_pos = alloca i64, align 8
  %ret = alloca i32, align 4
  store %struct.lzma_stream* %strm, %struct.lzma_stream** %strm.addr, align 8
  call void @llvm.dbg.declare(metadata %struct.lzma_stream** %strm.addr, metadata !495, metadata !228), !dbg !496
  store i32 %action, i32* %action.addr, align 4
  call void @llvm.dbg.declare(metadata i32* %action.addr, metadata !497, metadata !228), !dbg !498
  call void @llvm.dbg.declare(metadata i64* %in_pos, metadata !499, metadata !228), !dbg !500
  store i64 0, i64* %in_pos, align 8, !dbg !500
  call void @llvm.dbg.declare(metadata i64* %out_pos, metadata !501, metadata !228), !dbg !502
  store i64 0, i64* %out_pos, align 8, !dbg !502
  call void @llvm.dbg.declare(metadata i32* %ret, metadata !503, metadata !228), !dbg !504
  %0 = load %struct.lzma_stream*, %struct.lzma_stream** %strm.addr, align 8, !dbg !505
  %next_in = getelementptr inbounds %struct.lzma_stream, %struct.lzma_stream* %0, i32 0, i32 0, !dbg !507
  %1 = load i8*, i8** %next_in, align 8, !dbg !507
  %cmp = icmp eq i8* %1, null, !dbg !508
  br i1 %cmp, label %land.lhs.true, label %lor.lhs.false, !dbg !509

land.lhs.true:                                    ; preds = %entry
  %2 = load %struct.lzma_stream*, %struct.lzma_stream** %strm.addr, align 8, !dbg !510
  %avail_in = getelementptr inbounds %struct.lzma_stream, %struct.lzma_stream* %2, i32 0, i32 1, !dbg !512
  %3 = load i64, i64* %avail_in, align 8, !dbg !512
  %cmp1 = icmp ne i64 %3, 0, !dbg !513
  br i1 %cmp1, label %if.then, label %lor.lhs.false, !dbg !514

lor.lhs.false:                                    ; preds = %land.lhs.true, %entry
  %4 = load %struct.lzma_stream*, %struct.lzma_stream** %strm.addr, align 8, !dbg !515
  %next_out = getelementptr inbounds %struct.lzma_stream, %struct.lzma_stream* %4, i32 0, i32 3, !dbg !516
  %5 = load i8*, i8** %next_out, align 8, !dbg !516
  %cmp2 = icmp eq i8* %5, null, !dbg !517
  br i1 %cmp2, label %land.lhs.true3, label %lor.lhs.false5, !dbg !518

land.lhs.true3:                                   ; preds = %lor.lhs.false
  %6 = load %struct.lzma_stream*, %struct.lzma_stream** %strm.addr, align 8, !dbg !519
  %avail_out = getelementptr inbounds %struct.lzma_stream, %struct.lzma_stream* %6, i32 0, i32 4, !dbg !521
  %7 = load i64, i64* %avail_out, align 8, !dbg !521
  %cmp4 = icmp ne i64 %7, 0, !dbg !522
  br i1 %cmp4, label %if.then, label %lor.lhs.false5, !dbg !523

lor.lhs.false5:                                   ; preds = %land.lhs.true3, %lor.lhs.false
  %8 = load %struct.lzma_stream*, %struct.lzma_stream** %strm.addr, align 8, !dbg !524
  %internal = getelementptr inbounds %struct.lzma_stream, %struct.lzma_stream* %8, i32 0, i32 7, !dbg !525
  %9 = load %struct.lzma_internal_s*, %struct.lzma_internal_s** %internal, align 8, !dbg !525
  %cmp6 = icmp eq %struct.lzma_internal_s* %9, null, !dbg !526
  br i1 %cmp6, label %if.then, label %lor.lhs.false7, !dbg !527

lor.lhs.false7:                                   ; preds = %lor.lhs.false5
  %10 = load %struct.lzma_stream*, %struct.lzma_stream** %strm.addr, align 8, !dbg !528
  %internal8 = getelementptr inbounds %struct.lzma_stream, %struct.lzma_stream* %10, i32 0, i32 7, !dbg !529
  %11 = load %struct.lzma_internal_s*, %struct.lzma_internal_s** %internal8, align 8, !dbg !529
  %next = getelementptr inbounds %struct.lzma_internal_s, %struct.lzma_internal_s* %11, i32 0, i32 0, !dbg !530
  %code = getelementptr inbounds %struct.lzma_next_coder_s, %struct.lzma_next_coder_s* %next, i32 0, i32 3, !dbg !531
  %12 = load i32 (%struct.lzma_coder_s*, %struct.lzma_allocator*, i8*, i64*, i64, i8*, i64*, i64, i32)*, i32 (%struct.lzma_coder_s*, %struct.lzma_allocator*, i8*, i64*, i64, i8*, i64*, i64, i32)** %code, align 8, !dbg !531
  %cmp9 = icmp eq i32 (%struct.lzma_coder_s*, %struct.lzma_allocator*, i8*, i64*, i64, i8*, i64*, i64, i32)* %12, null, !dbg !532
  br i1 %cmp9, label %if.then, label %lor.lhs.false10, !dbg !533

lor.lhs.false10:                                  ; preds = %lor.lhs.false7
  %13 = load i32, i32* %action.addr, align 4, !dbg !534
  %cmp11 = icmp ugt i32 %13, 3, !dbg !535
  br i1 %cmp11, label %if.then, label %lor.lhs.false12, !dbg !536

lor.lhs.false12:                                  ; preds = %lor.lhs.false10
  %14 = load i32, i32* %action.addr, align 4, !dbg !537
  %idxprom = zext i32 %14 to i64, !dbg !538
  %15 = load %struct.lzma_stream*, %struct.lzma_stream** %strm.addr, align 8, !dbg !538
  %internal13 = getelementptr inbounds %struct.lzma_stream, %struct.lzma_stream* %15, i32 0, i32 7, !dbg !539
  %16 = load %struct.lzma_internal_s*, %struct.lzma_internal_s** %internal13, align 8, !dbg !539
  %supported_actions = getelementptr inbounds %struct.lzma_internal_s, %struct.lzma_internal_s* %16, i32 0, i32 3, !dbg !540
  %arrayidx = getelementptr inbounds [4 x i8], [4 x i8]* %supported_actions, i64 0, i64 %idxprom, !dbg !538
  %17 = load i8, i8* %arrayidx, align 1, !dbg !538
  %tobool = trunc i8 %17 to i1, !dbg !538
  br i1 %tobool, label %if.end, label %if.then, !dbg !541

if.then:                                          ; preds = %lor.lhs.false12, %lor.lhs.false10, %lor.lhs.false7, %lor.lhs.false5, %land.lhs.true3, %land.lhs.true
  store i32 11, i32* %retval, align 4, !dbg !543
  br label %return, !dbg !543

if.end:                                           ; preds = %lor.lhs.false12
  %18 = load %struct.lzma_stream*, %struct.lzma_stream** %strm.addr, align 8, !dbg !544
  %reserved_ptr1 = getelementptr inbounds %struct.lzma_stream, %struct.lzma_stream* %18, i32 0, i32 8, !dbg !546
  %19 = load i8*, i8** %reserved_ptr1, align 8, !dbg !546
  %cmp14 = icmp ne i8* %19, null, !dbg !547
  br i1 %cmp14, label %if.then33, label %lor.lhs.false15, !dbg !548

lor.lhs.false15:                                  ; preds = %if.end
  %20 = load %struct.lzma_stream*, %struct.lzma_stream** %strm.addr, align 8, !dbg !549
  %reserved_ptr2 = getelementptr inbounds %struct.lzma_stream, %struct.lzma_stream* %20, i32 0, i32 9, !dbg !551
  %21 = load i8*, i8** %reserved_ptr2, align 8, !dbg !551
  %cmp16 = icmp ne i8* %21, null, !dbg !552
  br i1 %cmp16, label %if.then33, label %lor.lhs.false17, !dbg !553

lor.lhs.false17:                                  ; preds = %lor.lhs.false15
  %22 = load %struct.lzma_stream*, %struct.lzma_stream** %strm.addr, align 8, !dbg !554
  %reserved_ptr3 = getelementptr inbounds %struct.lzma_stream, %struct.lzma_stream* %22, i32 0, i32 10, !dbg !555
  %23 = load i8*, i8** %reserved_ptr3, align 8, !dbg !555
  %cmp18 = icmp ne i8* %23, null, !dbg !556
  br i1 %cmp18, label %if.then33, label %lor.lhs.false19, !dbg !557

lor.lhs.false19:                                  ; preds = %lor.lhs.false17
  %24 = load %struct.lzma_stream*, %struct.lzma_stream** %strm.addr, align 8, !dbg !558
  %reserved_ptr4 = getelementptr inbounds %struct.lzma_stream, %struct.lzma_stream* %24, i32 0, i32 11, !dbg !559
  %25 = load i8*, i8** %reserved_ptr4, align 8, !dbg !559
  %cmp20 = icmp ne i8* %25, null, !dbg !560
  br i1 %cmp20, label %if.then33, label %lor.lhs.false21, !dbg !561

lor.lhs.false21:                                  ; preds = %lor.lhs.false19
  %26 = load %struct.lzma_stream*, %struct.lzma_stream** %strm.addr, align 8, !dbg !562
  %reserved_int1 = getelementptr inbounds %struct.lzma_stream, %struct.lzma_stream* %26, i32 0, i32 12, !dbg !563
  %27 = load i64, i64* %reserved_int1, align 8, !dbg !563
  %cmp22 = icmp ne i64 %27, 0, !dbg !564
  br i1 %cmp22, label %if.then33, label %lor.lhs.false23, !dbg !565

lor.lhs.false23:                                  ; preds = %lor.lhs.false21
  %28 = load %struct.lzma_stream*, %struct.lzma_stream** %strm.addr, align 8, !dbg !566
  %reserved_int2 = getelementptr inbounds %struct.lzma_stream, %struct.lzma_stream* %28, i32 0, i32 13, !dbg !567
  %29 = load i64, i64* %reserved_int2, align 8, !dbg !567
  %cmp24 = icmp ne i64 %29, 0, !dbg !568
  br i1 %cmp24, label %if.then33, label %lor.lhs.false25, !dbg !569

lor.lhs.false25:                                  ; preds = %lor.lhs.false23
  %30 = load %struct.lzma_stream*, %struct.lzma_stream** %strm.addr, align 8, !dbg !570
  %reserved_int3 = getelementptr inbounds %struct.lzma_stream, %struct.lzma_stream* %30, i32 0, i32 14, !dbg !571
  %31 = load i64, i64* %reserved_int3, align 8, !dbg !571
  %cmp26 = icmp ne i64 %31, 0, !dbg !572
  br i1 %cmp26, label %if.then33, label %lor.lhs.false27, !dbg !573

lor.lhs.false27:                                  ; preds = %lor.lhs.false25
  %32 = load %struct.lzma_stream*, %struct.lzma_stream** %strm.addr, align 8, !dbg !574
  %reserved_int4 = getelementptr inbounds %struct.lzma_stream, %struct.lzma_stream* %32, i32 0, i32 15, !dbg !575
  %33 = load i64, i64* %reserved_int4, align 8, !dbg !575
  %cmp28 = icmp ne i64 %33, 0, !dbg !576
  br i1 %cmp28, label %if.then33, label %lor.lhs.false29, !dbg !577

lor.lhs.false29:                                  ; preds = %lor.lhs.false27
  %34 = load %struct.lzma_stream*, %struct.lzma_stream** %strm.addr, align 8, !dbg !578
  %reserved_enum1 = getelementptr inbounds %struct.lzma_stream, %struct.lzma_stream* %34, i32 0, i32 16, !dbg !579
  %35 = load i32, i32* %reserved_enum1, align 8, !dbg !579
  %cmp30 = icmp ne i32 %35, 0, !dbg !580
  br i1 %cmp30, label %if.then33, label %lor.lhs.false31, !dbg !581

lor.lhs.false31:                                  ; preds = %lor.lhs.false29
  %36 = load %struct.lzma_stream*, %struct.lzma_stream** %strm.addr, align 8, !dbg !582
  %reserved_enum2 = getelementptr inbounds %struct.lzma_stream, %struct.lzma_stream* %36, i32 0, i32 17, !dbg !583
  %37 = load i32, i32* %reserved_enum2, align 4, !dbg !583
  %cmp32 = icmp ne i32 %37, 0, !dbg !584
  br i1 %cmp32, label %if.then33, label %if.end34, !dbg !585

if.then33:                                        ; preds = %lor.lhs.false31, %lor.lhs.false29, %lor.lhs.false27, %lor.lhs.false25, %lor.lhs.false23, %lor.lhs.false21, %lor.lhs.false19, %lor.lhs.false17, %lor.lhs.false15, %if.end
  store i32 8, i32* %retval, align 4, !dbg !587
  br label %return, !dbg !587

if.end34:                                         ; preds = %lor.lhs.false31
  %38 = load %struct.lzma_stream*, %struct.lzma_stream** %strm.addr, align 8, !dbg !588
  %internal35 = getelementptr inbounds %struct.lzma_stream, %struct.lzma_stream* %38, i32 0, i32 7, !dbg !589
  %39 = load %struct.lzma_internal_s*, %struct.lzma_internal_s** %internal35, align 8, !dbg !589
  %sequence = getelementptr inbounds %struct.lzma_internal_s, %struct.lzma_internal_s* %39, i32 0, i32 1, !dbg !590
  %40 = load i32, i32* %sequence, align 8, !dbg !590
  switch i32 %40, label %sw.default [
    i32 0, label %sw.bb
    i32 1, label %sw.bb46
    i32 2, label %sw.bb55
    i32 3, label %sw.bb64
    i32 4, label %sw.bb73
    i32 5, label %sw.bb74
  ], !dbg !591

sw.bb:                                            ; preds = %if.end34
  %41 = load i32, i32* %action.addr, align 4, !dbg !592
  switch i32 %41, label %sw.epilog [
    i32 0, label %sw.bb36
    i32 1, label %sw.bb37
    i32 2, label %sw.bb40
    i32 3, label %sw.bb43
  ], !dbg !594

sw.bb36:                                          ; preds = %sw.bb
  br label %sw.epilog, !dbg !595

sw.bb37:                                          ; preds = %sw.bb
  %42 = load %struct.lzma_stream*, %struct.lzma_stream** %strm.addr, align 8, !dbg !597
  %internal38 = getelementptr inbounds %struct.lzma_stream, %struct.lzma_stream* %42, i32 0, i32 7, !dbg !598
  %43 = load %struct.lzma_internal_s*, %struct.lzma_internal_s** %internal38, align 8, !dbg !598
  %sequence39 = getelementptr inbounds %struct.lzma_internal_s, %struct.lzma_internal_s* %43, i32 0, i32 1, !dbg !599
  store i32 1, i32* %sequence39, align 8, !dbg !600
  br label %sw.epilog, !dbg !601

sw.bb40:                                          ; preds = %sw.bb
  %44 = load %struct.lzma_stream*, %struct.lzma_stream** %strm.addr, align 8, !dbg !602
  %internal41 = getelementptr inbounds %struct.lzma_stream, %struct.lzma_stream* %44, i32 0, i32 7, !dbg !603
  %45 = load %struct.lzma_internal_s*, %struct.lzma_internal_s** %internal41, align 8, !dbg !603
  %sequence42 = getelementptr inbounds %struct.lzma_internal_s, %struct.lzma_internal_s* %45, i32 0, i32 1, !dbg !604
  store i32 2, i32* %sequence42, align 8, !dbg !605
  br label %sw.epilog, !dbg !606

sw.bb43:                                          ; preds = %sw.bb
  %46 = load %struct.lzma_stream*, %struct.lzma_stream** %strm.addr, align 8, !dbg !607
  %internal44 = getelementptr inbounds %struct.lzma_stream, %struct.lzma_stream* %46, i32 0, i32 7, !dbg !608
  %47 = load %struct.lzma_internal_s*, %struct.lzma_internal_s** %internal44, align 8, !dbg !608
  %sequence45 = getelementptr inbounds %struct.lzma_internal_s, %struct.lzma_internal_s* %47, i32 0, i32 1, !dbg !609
  store i32 3, i32* %sequence45, align 8, !dbg !610
  br label %sw.epilog, !dbg !611

sw.epilog:                                        ; preds = %sw.bb, %sw.bb43, %sw.bb40, %sw.bb37, %sw.bb36
  br label %sw.epilog75, !dbg !612

sw.bb46:                                          ; preds = %if.end34
  %48 = load i32, i32* %action.addr, align 4, !dbg !613
  %cmp47 = icmp ne i32 %48, 1, !dbg !615
  br i1 %cmp47, label %if.then53, label %lor.lhs.false48, !dbg !616

lor.lhs.false48:                                  ; preds = %sw.bb46
  %49 = load %struct.lzma_stream*, %struct.lzma_stream** %strm.addr, align 8, !dbg !617
  %internal49 = getelementptr inbounds %struct.lzma_stream, %struct.lzma_stream* %49, i32 0, i32 7, !dbg !619
  %50 = load %struct.lzma_internal_s*, %struct.lzma_internal_s** %internal49, align 8, !dbg !619
  %avail_in50 = getelementptr inbounds %struct.lzma_internal_s, %struct.lzma_internal_s* %50, i32 0, i32 2, !dbg !620
  %51 = load i64, i64* %avail_in50, align 8, !dbg !620
  %52 = load %struct.lzma_stream*, %struct.lzma_stream** %strm.addr, align 8, !dbg !621
  %avail_in51 = getelementptr inbounds %struct.lzma_stream, %struct.lzma_stream* %52, i32 0, i32 1, !dbg !622
  %53 = load i64, i64* %avail_in51, align 8, !dbg !622
  %cmp52 = icmp ne i64 %51, %53, !dbg !623
  br i1 %cmp52, label %if.then53, label %if.end54, !dbg !624

if.then53:                                        ; preds = %lor.lhs.false48, %sw.bb46
  store i32 11, i32* %retval, align 4, !dbg !626
  br label %return, !dbg !626

if.end54:                                         ; preds = %lor.lhs.false48
  br label %sw.epilog75, !dbg !627

sw.bb55:                                          ; preds = %if.end34
  %54 = load i32, i32* %action.addr, align 4, !dbg !628
  %cmp56 = icmp ne i32 %54, 2, !dbg !630
  br i1 %cmp56, label %if.then62, label %lor.lhs.false57, !dbg !631

lor.lhs.false57:                                  ; preds = %sw.bb55
  %55 = load %struct.lzma_stream*, %struct.lzma_stream** %strm.addr, align 8, !dbg !632
  %internal58 = getelementptr inbounds %struct.lzma_stream, %struct.lzma_stream* %55, i32 0, i32 7, !dbg !634
  %56 = load %struct.lzma_internal_s*, %struct.lzma_internal_s** %internal58, align 8, !dbg !634
  %avail_in59 = getelementptr inbounds %struct.lzma_internal_s, %struct.lzma_internal_s* %56, i32 0, i32 2, !dbg !635
  %57 = load i64, i64* %avail_in59, align 8, !dbg !635
  %58 = load %struct.lzma_stream*, %struct.lzma_stream** %strm.addr, align 8, !dbg !636
  %avail_in60 = getelementptr inbounds %struct.lzma_stream, %struct.lzma_stream* %58, i32 0, i32 1, !dbg !637
  %59 = load i64, i64* %avail_in60, align 8, !dbg !637
  %cmp61 = icmp ne i64 %57, %59, !dbg !638
  br i1 %cmp61, label %if.then62, label %if.end63, !dbg !639

if.then62:                                        ; preds = %lor.lhs.false57, %sw.bb55
  store i32 11, i32* %retval, align 4, !dbg !640
  br label %return, !dbg !640

if.end63:                                         ; preds = %lor.lhs.false57
  br label %sw.epilog75, !dbg !641

sw.bb64:                                          ; preds = %if.end34
  %60 = load i32, i32* %action.addr, align 4, !dbg !642
  %cmp65 = icmp ne i32 %60, 3, !dbg !644
  br i1 %cmp65, label %if.then71, label %lor.lhs.false66, !dbg !645

lor.lhs.false66:                                  ; preds = %sw.bb64
  %61 = load %struct.lzma_stream*, %struct.lzma_stream** %strm.addr, align 8, !dbg !646
  %internal67 = getelementptr inbounds %struct.lzma_stream, %struct.lzma_stream* %61, i32 0, i32 7, !dbg !648
  %62 = load %struct.lzma_internal_s*, %struct.lzma_internal_s** %internal67, align 8, !dbg !648
  %avail_in68 = getelementptr inbounds %struct.lzma_internal_s, %struct.lzma_internal_s* %62, i32 0, i32 2, !dbg !649
  %63 = load i64, i64* %avail_in68, align 8, !dbg !649
  %64 = load %struct.lzma_stream*, %struct.lzma_stream** %strm.addr, align 8, !dbg !650
  %avail_in69 = getelementptr inbounds %struct.lzma_stream, %struct.lzma_stream* %64, i32 0, i32 1, !dbg !651
  %65 = load i64, i64* %avail_in69, align 8, !dbg !651
  %cmp70 = icmp ne i64 %63, %65, !dbg !652
  br i1 %cmp70, label %if.then71, label %if.end72, !dbg !653

if.then71:                                        ; preds = %lor.lhs.false66, %sw.bb64
  store i32 11, i32* %retval, align 4, !dbg !654
  br label %return, !dbg !654

if.end72:                                         ; preds = %lor.lhs.false66
  br label %sw.epilog75, !dbg !655

sw.bb73:                                          ; preds = %if.end34
  store i32 1, i32* %retval, align 4, !dbg !656
  br label %return, !dbg !656

sw.bb74:                                          ; preds = %if.end34
  br label %sw.default, !dbg !657

sw.default:                                       ; preds = %if.end34, %sw.bb74
  store i32 11, i32* %retval, align 4, !dbg !658
  br label %return, !dbg !658

sw.epilog75:                                      ; preds = %if.end72, %if.end63, %if.end54, %sw.epilog
  %66 = load %struct.lzma_stream*, %struct.lzma_stream** %strm.addr, align 8, !dbg !659
  %internal76 = getelementptr inbounds %struct.lzma_stream, %struct.lzma_stream* %66, i32 0, i32 7, !dbg !660
  %67 = load %struct.lzma_internal_s*, %struct.lzma_internal_s** %internal76, align 8, !dbg !660
  %next77 = getelementptr inbounds %struct.lzma_internal_s, %struct.lzma_internal_s* %67, i32 0, i32 0, !dbg !661
  %code78 = getelementptr inbounds %struct.lzma_next_coder_s, %struct.lzma_next_coder_s* %next77, i32 0, i32 3, !dbg !662
  %68 = load i32 (%struct.lzma_coder_s*, %struct.lzma_allocator*, i8*, i64*, i64, i8*, i64*, i64, i32)*, i32 (%struct.lzma_coder_s*, %struct.lzma_allocator*, i8*, i64*, i64, i8*, i64*, i64, i32)** %code78, align 8, !dbg !662
  %69 = load %struct.lzma_stream*, %struct.lzma_stream** %strm.addr, align 8, !dbg !663
  %internal79 = getelementptr inbounds %struct.lzma_stream, %struct.lzma_stream* %69, i32 0, i32 7, !dbg !664
  %70 = load %struct.lzma_internal_s*, %struct.lzma_internal_s** %internal79, align 8, !dbg !664
  %next80 = getelementptr inbounds %struct.lzma_internal_s, %struct.lzma_internal_s* %70, i32 0, i32 0, !dbg !665
  %coder = getelementptr inbounds %struct.lzma_next_coder_s, %struct.lzma_next_coder_s* %next80, i32 0, i32 0, !dbg !666
  %71 = load %struct.lzma_coder_s*, %struct.lzma_coder_s** %coder, align 8, !dbg !666
  %72 = load %struct.lzma_stream*, %struct.lzma_stream** %strm.addr, align 8, !dbg !667
  %allocator = getelementptr inbounds %struct.lzma_stream, %struct.lzma_stream* %72, i32 0, i32 6, !dbg !668
  %73 = load %struct.lzma_allocator*, %struct.lzma_allocator** %allocator, align 8, !dbg !668
  %74 = load %struct.lzma_stream*, %struct.lzma_stream** %strm.addr, align 8, !dbg !669
  %next_in81 = getelementptr inbounds %struct.lzma_stream, %struct.lzma_stream* %74, i32 0, i32 0, !dbg !670
  %75 = load i8*, i8** %next_in81, align 8, !dbg !670
  %76 = load %struct.lzma_stream*, %struct.lzma_stream** %strm.addr, align 8, !dbg !671
  %avail_in82 = getelementptr inbounds %struct.lzma_stream, %struct.lzma_stream* %76, i32 0, i32 1, !dbg !672
  %77 = load i64, i64* %avail_in82, align 8, !dbg !672
  %78 = load %struct.lzma_stream*, %struct.lzma_stream** %strm.addr, align 8, !dbg !673
  %next_out83 = getelementptr inbounds %struct.lzma_stream, %struct.lzma_stream* %78, i32 0, i32 3, !dbg !674
  %79 = load i8*, i8** %next_out83, align 8, !dbg !674
  %80 = load %struct.lzma_stream*, %struct.lzma_stream** %strm.addr, align 8, !dbg !675
  %avail_out84 = getelementptr inbounds %struct.lzma_stream, %struct.lzma_stream* %80, i32 0, i32 4, !dbg !676
  %81 = load i64, i64* %avail_out84, align 8, !dbg !676
  %82 = load i32, i32* %action.addr, align 4, !dbg !677
  %call = call i32 %68(%struct.lzma_coder_s* %71, %struct.lzma_allocator* %73, i8* %75, i64* %in_pos, i64 %77, i8* %79, i64* %out_pos, i64 %81, i32 %82), !dbg !659
  store i32 %call, i32* %ret, align 4, !dbg !678
  %83 = load i64, i64* %in_pos, align 8, !dbg !679
  %84 = load %struct.lzma_stream*, %struct.lzma_stream** %strm.addr, align 8, !dbg !680
  %next_in85 = getelementptr inbounds %struct.lzma_stream, %struct.lzma_stream* %84, i32 0, i32 0, !dbg !681
  %85 = load i8*, i8** %next_in85, align 8, !dbg !682
  %add.ptr = getelementptr inbounds i8, i8* %85, i64 %83, !dbg !682
  store i8* %add.ptr, i8** %next_in85, align 8, !dbg !682
  %86 = load i64, i64* %in_pos, align 8, !dbg !683
  %87 = load %struct.lzma_stream*, %struct.lzma_stream** %strm.addr, align 8, !dbg !684
  %avail_in86 = getelementptr inbounds %struct.lzma_stream, %struct.lzma_stream* %87, i32 0, i32 1, !dbg !685
  %88 = load i64, i64* %avail_in86, align 8, !dbg !686
  %sub = sub i64 %88, %86, !dbg !686
  store i64 %sub, i64* %avail_in86, align 8, !dbg !686
  %89 = load i64, i64* %in_pos, align 8, !dbg !687
  %90 = load %struct.lzma_stream*, %struct.lzma_stream** %strm.addr, align 8, !dbg !688
  %total_in = getelementptr inbounds %struct.lzma_stream, %struct.lzma_stream* %90, i32 0, i32 2, !dbg !689
  %91 = load i64, i64* %total_in, align 8, !dbg !690
  %add = add i64 %91, %89, !dbg !690
  store i64 %add, i64* %total_in, align 8, !dbg !690
  %92 = load i64, i64* %out_pos, align 8, !dbg !691
  %93 = load %struct.lzma_stream*, %struct.lzma_stream** %strm.addr, align 8, !dbg !692
  %next_out87 = getelementptr inbounds %struct.lzma_stream, %struct.lzma_stream* %93, i32 0, i32 3, !dbg !693
  %94 = load i8*, i8** %next_out87, align 8, !dbg !694
  %add.ptr88 = getelementptr inbounds i8, i8* %94, i64 %92, !dbg !694
  store i8* %add.ptr88, i8** %next_out87, align 8, !dbg !694
  %95 = load i64, i64* %out_pos, align 8, !dbg !695
  %96 = load %struct.lzma_stream*, %struct.lzma_stream** %strm.addr, align 8, !dbg !696
  %avail_out89 = getelementptr inbounds %struct.lzma_stream, %struct.lzma_stream* %96, i32 0, i32 4, !dbg !697
  %97 = load i64, i64* %avail_out89, align 8, !dbg !698
  %sub90 = sub i64 %97, %95, !dbg !698
  store i64 %sub90, i64* %avail_out89, align 8, !dbg !698
  %98 = load i64, i64* %out_pos, align 8, !dbg !699
  %99 = load %struct.lzma_stream*, %struct.lzma_stream** %strm.addr, align 8, !dbg !700
  %total_out = getelementptr inbounds %struct.lzma_stream, %struct.lzma_stream* %99, i32 0, i32 5, !dbg !701
  %100 = load i64, i64* %total_out, align 8, !dbg !702
  %add91 = add i64 %100, %98, !dbg !702
  store i64 %add91, i64* %total_out, align 8, !dbg !702
  %101 = load %struct.lzma_stream*, %struct.lzma_stream** %strm.addr, align 8, !dbg !703
  %avail_in92 = getelementptr inbounds %struct.lzma_stream, %struct.lzma_stream* %101, i32 0, i32 1, !dbg !704
  %102 = load i64, i64* %avail_in92, align 8, !dbg !704
  %103 = load %struct.lzma_stream*, %struct.lzma_stream** %strm.addr, align 8, !dbg !705
  %internal93 = getelementptr inbounds %struct.lzma_stream, %struct.lzma_stream* %103, i32 0, i32 7, !dbg !706
  %104 = load %struct.lzma_internal_s*, %struct.lzma_internal_s** %internal93, align 8, !dbg !706
  %avail_in94 = getelementptr inbounds %struct.lzma_internal_s, %struct.lzma_internal_s* %104, i32 0, i32 2, !dbg !707
  store i64 %102, i64* %avail_in94, align 8, !dbg !708
  %105 = load i32, i32* %ret, align 4, !dbg !709
  switch i32 %105, label %sw.default128 [
    i32 0, label %sw.bb95
    i32 1, label %sw.bb110
    i32 2, label %sw.bb125
    i32 3, label %sw.bb125
    i32 4, label %sw.bb125
    i32 6, label %sw.bb125
  ], !dbg !710

sw.bb95:                                          ; preds = %sw.epilog75
  %106 = load i64, i64* %out_pos, align 8, !dbg !711
  %cmp96 = icmp eq i64 %106, 0, !dbg !714
  br i1 %cmp96, label %land.lhs.true97, label %if.else106, !dbg !715

land.lhs.true97:                                  ; preds = %sw.bb95
  %107 = load i64, i64* %in_pos, align 8, !dbg !716
  %cmp98 = icmp eq i64 %107, 0, !dbg !718
  br i1 %cmp98, label %if.then99, label %if.else106, !dbg !719

if.then99:                                        ; preds = %land.lhs.true97
  %108 = load %struct.lzma_stream*, %struct.lzma_stream** %strm.addr, align 8, !dbg !720
  %internal100 = getelementptr inbounds %struct.lzma_stream, %struct.lzma_stream* %108, i32 0, i32 7, !dbg !723
  %109 = load %struct.lzma_internal_s*, %struct.lzma_internal_s** %internal100, align 8, !dbg !723
  %allow_buf_error = getelementptr inbounds %struct.lzma_internal_s, %struct.lzma_internal_s* %109, i32 0, i32 4, !dbg !724
  %110 = load i8, i8* %allow_buf_error, align 4, !dbg !724
  %tobool101 = trunc i8 %110 to i1, !dbg !724
  br i1 %tobool101, label %if.then102, label %if.else, !dbg !725

if.then102:                                       ; preds = %if.then99
  store i32 10, i32* %ret, align 4, !dbg !726
  br label %if.end105, !dbg !727

if.else:                                          ; preds = %if.then99
  %111 = load %struct.lzma_stream*, %struct.lzma_stream** %strm.addr, align 8, !dbg !728
  %internal103 = getelementptr inbounds %struct.lzma_stream, %struct.lzma_stream* %111, i32 0, i32 7, !dbg !729
  %112 = load %struct.lzma_internal_s*, %struct.lzma_internal_s** %internal103, align 8, !dbg !729
  %allow_buf_error104 = getelementptr inbounds %struct.lzma_internal_s, %struct.lzma_internal_s* %112, i32 0, i32 4, !dbg !730
  store i8 1, i8* %allow_buf_error104, align 4, !dbg !731
  br label %if.end105

if.end105:                                        ; preds = %if.else, %if.then102
  br label %if.end109, !dbg !732

if.else106:                                       ; preds = %land.lhs.true97, %sw.bb95
  %113 = load %struct.lzma_stream*, %struct.lzma_stream** %strm.addr, align 8, !dbg !733
  %internal107 = getelementptr inbounds %struct.lzma_stream, %struct.lzma_stream* %113, i32 0, i32 7, !dbg !735
  %114 = load %struct.lzma_internal_s*, %struct.lzma_internal_s** %internal107, align 8, !dbg !735
  %allow_buf_error108 = getelementptr inbounds %struct.lzma_internal_s, %struct.lzma_internal_s* %114, i32 0, i32 4, !dbg !736
  store i8 0, i8* %allow_buf_error108, align 4, !dbg !737
  br label %if.end109

if.end109:                                        ; preds = %if.else106, %if.end105
  br label %sw.epilog132, !dbg !738

sw.bb110:                                         ; preds = %sw.epilog75
  %115 = load %struct.lzma_stream*, %struct.lzma_stream** %strm.addr, align 8, !dbg !739
  %internal111 = getelementptr inbounds %struct.lzma_stream, %struct.lzma_stream* %115, i32 0, i32 7, !dbg !741
  %116 = load %struct.lzma_internal_s*, %struct.lzma_internal_s** %internal111, align 8, !dbg !741
  %sequence112 = getelementptr inbounds %struct.lzma_internal_s, %struct.lzma_internal_s* %116, i32 0, i32 1, !dbg !742
  %117 = load i32, i32* %sequence112, align 8, !dbg !742
  %cmp113 = icmp eq i32 %117, 1, !dbg !743
  br i1 %cmp113, label %if.then118, label %lor.lhs.false114, !dbg !744

lor.lhs.false114:                                 ; preds = %sw.bb110
  %118 = load %struct.lzma_stream*, %struct.lzma_stream** %strm.addr, align 8, !dbg !745
  %internal115 = getelementptr inbounds %struct.lzma_stream, %struct.lzma_stream* %118, i32 0, i32 7, !dbg !747
  %119 = load %struct.lzma_internal_s*, %struct.lzma_internal_s** %internal115, align 8, !dbg !747
  %sequence116 = getelementptr inbounds %struct.lzma_internal_s, %struct.lzma_internal_s* %119, i32 0, i32 1, !dbg !748
  %120 = load i32, i32* %sequence116, align 8, !dbg !748
  %cmp117 = icmp eq i32 %120, 2, !dbg !749
  br i1 %cmp117, label %if.then118, label %if.else121, !dbg !750

if.then118:                                       ; preds = %lor.lhs.false114, %sw.bb110
  %121 = load %struct.lzma_stream*, %struct.lzma_stream** %strm.addr, align 8, !dbg !752
  %internal119 = getelementptr inbounds %struct.lzma_stream, %struct.lzma_stream* %121, i32 0, i32 7, !dbg !753
  %122 = load %struct.lzma_internal_s*, %struct.lzma_internal_s** %internal119, align 8, !dbg !753
  %sequence120 = getelementptr inbounds %struct.lzma_internal_s, %struct.lzma_internal_s* %122, i32 0, i32 1, !dbg !754
  store i32 0, i32* %sequence120, align 8, !dbg !755
  br label %if.end124, !dbg !752

if.else121:                                       ; preds = %lor.lhs.false114
  %123 = load %struct.lzma_stream*, %struct.lzma_stream** %strm.addr, align 8, !dbg !756
  %internal122 = getelementptr inbounds %struct.lzma_stream, %struct.lzma_stream* %123, i32 0, i32 7, !dbg !757
  %124 = load %struct.lzma_internal_s*, %struct.lzma_internal_s** %internal122, align 8, !dbg !757
  %sequence123 = getelementptr inbounds %struct.lzma_internal_s, %struct.lzma_internal_s* %124, i32 0, i32 1, !dbg !758
  store i32 4, i32* %sequence123, align 8, !dbg !759
  br label %if.end124

if.end124:                                        ; preds = %if.else121, %if.then118
  br label %sw.bb125, !dbg !760

sw.bb125:                                         ; preds = %sw.epilog75, %sw.epilog75, %sw.epilog75, %sw.epilog75, %if.end124
  %125 = load %struct.lzma_stream*, %struct.lzma_stream** %strm.addr, align 8, !dbg !762
  %internal126 = getelementptr inbounds %struct.lzma_stream, %struct.lzma_stream* %125, i32 0, i32 7, !dbg !763
  %126 = load %struct.lzma_internal_s*, %struct.lzma_internal_s** %internal126, align 8, !dbg !763
  %allow_buf_error127 = getelementptr inbounds %struct.lzma_internal_s, %struct.lzma_internal_s* %126, i32 0, i32 4, !dbg !764
  store i8 0, i8* %allow_buf_error127, align 4, !dbg !765
  br label %sw.epilog132, !dbg !766

sw.default128:                                    ; preds = %sw.epilog75
  %127 = load i32, i32* %ret, align 4, !dbg !767
  %cmp129 = icmp ne i32 %127, 10, !dbg !767
  br i1 %cmp129, label %cond.true, label %cond.false, !dbg !767

cond.true:                                        ; preds = %sw.default128
  br label %cond.end, !dbg !768

cond.false:                                       ; preds = %sw.default128
  call void @__assert_fail(i8* getelementptr inbounds ([22 x i8], [22 x i8]* @.str.3, i32 0, i32 0), i8* getelementptr inbounds ([78 x i8], [78 x i8]* @.str.2, i32 0, i32 0), i32 306, i8* getelementptr inbounds ([47 x i8], [47 x i8]* @__PRETTY_FUNCTION__.lzma_code, i32 0, i32 0)) #8, !dbg !769
  unreachable, !dbg !769
                                                  ; No predecessors!
  br label %cond.end, !dbg !771

cond.end:                                         ; preds = %128, %cond.true
  %129 = load %struct.lzma_stream*, %struct.lzma_stream** %strm.addr, align 8, !dbg !773
  %internal130 = getelementptr inbounds %struct.lzma_stream, %struct.lzma_stream* %129, i32 0, i32 7, !dbg !774
  %130 = load %struct.lzma_internal_s*, %struct.lzma_internal_s** %internal130, align 8, !dbg !774
  %sequence131 = getelementptr inbounds %struct.lzma_internal_s, %struct.lzma_internal_s* %130, i32 0, i32 1, !dbg !775
  store i32 5, i32* %sequence131, align 8, !dbg !776
  br label %sw.epilog132, !dbg !777

sw.epilog132:                                     ; preds = %cond.end, %sw.bb125, %if.end109
  %131 = load i32, i32* %ret, align 4, !dbg !778
  store i32 %131, i32* %retval, align 4, !dbg !779
  br label %return, !dbg !779

return:                                           ; preds = %sw.epilog132, %sw.default, %sw.bb73, %if.then71, %if.then62, %if.then53, %if.then33, %if.then
  %132 = load i32, i32* %retval, align 4, !dbg !780
  ret i32 %132, !dbg !780
}

; Function Attrs: nounwind uwtable
define void @lzma_end(%struct.lzma_stream* %strm) #1 !dbg !204 {
entry:
  %strm.addr = alloca %struct.lzma_stream*, align 8
  store %struct.lzma_stream* %strm, %struct.lzma_stream** %strm.addr, align 8
  call void @llvm.dbg.declare(metadata %struct.lzma_stream** %strm.addr, metadata !781, metadata !228), !dbg !782
  %0 = load %struct.lzma_stream*, %struct.lzma_stream** %strm.addr, align 8, !dbg !783
  %cmp = icmp ne %struct.lzma_stream* %0, null, !dbg !785
  br i1 %cmp, label %land.lhs.true, label %if.end, !dbg !786

land.lhs.true:                                    ; preds = %entry
  %1 = load %struct.lzma_stream*, %struct.lzma_stream** %strm.addr, align 8, !dbg !787
  %internal = getelementptr inbounds %struct.lzma_stream, %struct.lzma_stream* %1, i32 0, i32 7, !dbg !789
  %2 = load %struct.lzma_internal_s*, %struct.lzma_internal_s** %internal, align 8, !dbg !789
  %cmp1 = icmp ne %struct.lzma_internal_s* %2, null, !dbg !790
  br i1 %cmp1, label %if.then, label %if.end, !dbg !791

if.then:                                          ; preds = %land.lhs.true
  %3 = load %struct.lzma_stream*, %struct.lzma_stream** %strm.addr, align 8, !dbg !792
  %internal2 = getelementptr inbounds %struct.lzma_stream, %struct.lzma_stream* %3, i32 0, i32 7, !dbg !794
  %4 = load %struct.lzma_internal_s*, %struct.lzma_internal_s** %internal2, align 8, !dbg !794
  %next = getelementptr inbounds %struct.lzma_internal_s, %struct.lzma_internal_s* %4, i32 0, i32 0, !dbg !795
  %5 = load %struct.lzma_stream*, %struct.lzma_stream** %strm.addr, align 8, !dbg !796
  %allocator = getelementptr inbounds %struct.lzma_stream, %struct.lzma_stream* %5, i32 0, i32 6, !dbg !797
  %6 = load %struct.lzma_allocator*, %struct.lzma_allocator** %allocator, align 8, !dbg !797
  call void @lzma_next_end(%struct.lzma_next_coder_s* %next, %struct.lzma_allocator* %6), !dbg !798
  %7 = load %struct.lzma_stream*, %struct.lzma_stream** %strm.addr, align 8, !dbg !799
  %internal3 = getelementptr inbounds %struct.lzma_stream, %struct.lzma_stream* %7, i32 0, i32 7, !dbg !800
  %8 = load %struct.lzma_internal_s*, %struct.lzma_internal_s** %internal3, align 8, !dbg !800
  %9 = bitcast %struct.lzma_internal_s* %8 to i8*, !dbg !799
  %10 = load %struct.lzma_stream*, %struct.lzma_stream** %strm.addr, align 8, !dbg !801
  %allocator4 = getelementptr inbounds %struct.lzma_stream, %struct.lzma_stream* %10, i32 0, i32 6, !dbg !802
  %11 = load %struct.lzma_allocator*, %struct.lzma_allocator** %allocator4, align 8, !dbg !802
  call void @lzma_free(i8* %9, %struct.lzma_allocator* %11), !dbg !803
  %12 = load %struct.lzma_stream*, %struct.lzma_stream** %strm.addr, align 8, !dbg !804
  %internal5 = getelementptr inbounds %struct.lzma_stream, %struct.lzma_stream* %12, i32 0, i32 7, !dbg !805
  store %struct.lzma_internal_s* null, %struct.lzma_internal_s** %internal5, align 8, !dbg !806
  br label %if.end, !dbg !807

if.end:                                           ; preds = %if.then, %land.lhs.true, %entry
  ret void, !dbg !808
}

; Function Attrs: nounwind uwtable
define i32 @lzma_get_check(%struct.lzma_stream* %strm) #1 !dbg !207 {
entry:
  %retval = alloca i32, align 4
  %strm.addr = alloca %struct.lzma_stream*, align 8
  store %struct.lzma_stream* %strm, %struct.lzma_stream** %strm.addr, align 8
  call void @llvm.dbg.declare(metadata %struct.lzma_stream** %strm.addr, metadata !809, metadata !228), !dbg !810
  %0 = load %struct.lzma_stream*, %struct.lzma_stream** %strm.addr, align 8, !dbg !811
  %internal = getelementptr inbounds %struct.lzma_stream, %struct.lzma_stream* %0, i32 0, i32 7, !dbg !813
  %1 = load %struct.lzma_internal_s*, %struct.lzma_internal_s** %internal, align 8, !dbg !813
  %next = getelementptr inbounds %struct.lzma_internal_s, %struct.lzma_internal_s* %1, i32 0, i32 0, !dbg !814
  %get_check = getelementptr inbounds %struct.lzma_next_coder_s, %struct.lzma_next_coder_s* %next, i32 0, i32 5, !dbg !815
  %2 = load i32 (%struct.lzma_coder_s*)*, i32 (%struct.lzma_coder_s*)** %get_check, align 8, !dbg !815
  %cmp = icmp eq i32 (%struct.lzma_coder_s*)* %2, null, !dbg !816
  br i1 %cmp, label %if.then, label %if.end, !dbg !817

if.then:                                          ; preds = %entry
  store i32 0, i32* %retval, align 4, !dbg !818
  br label %return, !dbg !818

if.end:                                           ; preds = %entry
  %3 = load %struct.lzma_stream*, %struct.lzma_stream** %strm.addr, align 8, !dbg !819
  %internal1 = getelementptr inbounds %struct.lzma_stream, %struct.lzma_stream* %3, i32 0, i32 7, !dbg !820
  %4 = load %struct.lzma_internal_s*, %struct.lzma_internal_s** %internal1, align 8, !dbg !820
  %next2 = getelementptr inbounds %struct.lzma_internal_s, %struct.lzma_internal_s* %4, i32 0, i32 0, !dbg !821
  %get_check3 = getelementptr inbounds %struct.lzma_next_coder_s, %struct.lzma_next_coder_s* %next2, i32 0, i32 5, !dbg !822
  %5 = load i32 (%struct.lzma_coder_s*)*, i32 (%struct.lzma_coder_s*)** %get_check3, align 8, !dbg !822
  %6 = load %struct.lzma_stream*, %struct.lzma_stream** %strm.addr, align 8, !dbg !823
  %internal4 = getelementptr inbounds %struct.lzma_stream, %struct.lzma_stream* %6, i32 0, i32 7, !dbg !824
  %7 = load %struct.lzma_internal_s*, %struct.lzma_internal_s** %internal4, align 8, !dbg !824
  %next5 = getelementptr inbounds %struct.lzma_internal_s, %struct.lzma_internal_s* %7, i32 0, i32 0, !dbg !825
  %coder = getelementptr inbounds %struct.lzma_next_coder_s, %struct.lzma_next_coder_s* %next5, i32 0, i32 0, !dbg !826
  %8 = load %struct.lzma_coder_s*, %struct.lzma_coder_s** %coder, align 8, !dbg !826
  %call = call i32 %5(%struct.lzma_coder_s* %8), !dbg !819
  store i32 %call, i32* %retval, align 4, !dbg !827
  br label %return, !dbg !827

return:                                           ; preds = %if.end, %if.then
  %9 = load i32, i32* %retval, align 4, !dbg !828
  ret i32 %9, !dbg !828
}

; Function Attrs: nounwind readonly uwtable
define i64 @lzma_memusage(%struct.lzma_stream* %strm) #6 !dbg !212 {
entry:
  %retval = alloca i64, align 8
  %strm.addr = alloca %struct.lzma_stream*, align 8
  %memusage = alloca i64, align 8
  %old_memlimit = alloca i64, align 8
  store %struct.lzma_stream* %strm, %struct.lzma_stream** %strm.addr, align 8
  call void @llvm.dbg.declare(metadata %struct.lzma_stream** %strm.addr, metadata !829, metadata !228), !dbg !830
  call void @llvm.dbg.declare(metadata i64* %memusage, metadata !831, metadata !228), !dbg !832
  call void @llvm.dbg.declare(metadata i64* %old_memlimit, metadata !833, metadata !228), !dbg !834
  %0 = load %struct.lzma_stream*, %struct.lzma_stream** %strm.addr, align 8, !dbg !835
  %cmp = icmp eq %struct.lzma_stream* %0, null, !dbg !837
  br i1 %cmp, label %if.then, label %lor.lhs.false, !dbg !838

lor.lhs.false:                                    ; preds = %entry
  %1 = load %struct.lzma_stream*, %struct.lzma_stream** %strm.addr, align 8, !dbg !839
  %internal = getelementptr inbounds %struct.lzma_stream, %struct.lzma_stream* %1, i32 0, i32 7, !dbg !841
  %2 = load %struct.lzma_internal_s*, %struct.lzma_internal_s** %internal, align 8, !dbg !841
  %cmp1 = icmp eq %struct.lzma_internal_s* %2, null, !dbg !842
  br i1 %cmp1, label %if.then, label %lor.lhs.false2, !dbg !843

lor.lhs.false2:                                   ; preds = %lor.lhs.false
  %3 = load %struct.lzma_stream*, %struct.lzma_stream** %strm.addr, align 8, !dbg !844
  %internal3 = getelementptr inbounds %struct.lzma_stream, %struct.lzma_stream* %3, i32 0, i32 7, !dbg !845
  %4 = load %struct.lzma_internal_s*, %struct.lzma_internal_s** %internal3, align 8, !dbg !845
  %next = getelementptr inbounds %struct.lzma_internal_s, %struct.lzma_internal_s* %4, i32 0, i32 0, !dbg !846
  %memconfig = getelementptr inbounds %struct.lzma_next_coder_s, %struct.lzma_next_coder_s* %next, i32 0, i32 6, !dbg !847
  %5 = load i32 (%struct.lzma_coder_s*, i64*, i64*, i64)*, i32 (%struct.lzma_coder_s*, i64*, i64*, i64)** %memconfig, align 8, !dbg !847
  %cmp4 = icmp eq i32 (%struct.lzma_coder_s*, i64*, i64*, i64)* %5, null, !dbg !848
  br i1 %cmp4, label %if.then, label %lor.lhs.false5, !dbg !849

lor.lhs.false5:                                   ; preds = %lor.lhs.false2
  %6 = load %struct.lzma_stream*, %struct.lzma_stream** %strm.addr, align 8, !dbg !850
  %internal6 = getelementptr inbounds %struct.lzma_stream, %struct.lzma_stream* %6, i32 0, i32 7, !dbg !851
  %7 = load %struct.lzma_internal_s*, %struct.lzma_internal_s** %internal6, align 8, !dbg !851
  %next7 = getelementptr inbounds %struct.lzma_internal_s, %struct.lzma_internal_s* %7, i32 0, i32 0, !dbg !852
  %memconfig8 = getelementptr inbounds %struct.lzma_next_coder_s, %struct.lzma_next_coder_s* %next7, i32 0, i32 6, !dbg !853
  %8 = load i32 (%struct.lzma_coder_s*, i64*, i64*, i64)*, i32 (%struct.lzma_coder_s*, i64*, i64*, i64)** %memconfig8, align 8, !dbg !853
  %9 = load %struct.lzma_stream*, %struct.lzma_stream** %strm.addr, align 8, !dbg !854
  %internal9 = getelementptr inbounds %struct.lzma_stream, %struct.lzma_stream* %9, i32 0, i32 7, !dbg !855
  %10 = load %struct.lzma_internal_s*, %struct.lzma_internal_s** %internal9, align 8, !dbg !855
  %next10 = getelementptr inbounds %struct.lzma_internal_s, %struct.lzma_internal_s* %10, i32 0, i32 0, !dbg !856
  %coder = getelementptr inbounds %struct.lzma_next_coder_s, %struct.lzma_next_coder_s* %next10, i32 0, i32 0, !dbg !857
  %11 = load %struct.lzma_coder_s*, %struct.lzma_coder_s** %coder, align 8, !dbg !857
  %call = call i32 %8(%struct.lzma_coder_s* %11, i64* %memusage, i64* %old_memlimit, i64 0), !dbg !850
  %cmp11 = icmp ne i32 %call, 0, !dbg !858
  br i1 %cmp11, label %if.then, label %if.end, !dbg !859

if.then:                                          ; preds = %lor.lhs.false5, %lor.lhs.false2, %lor.lhs.false, %entry
  store i64 0, i64* %retval, align 8, !dbg !861
  br label %return, !dbg !861

if.end:                                           ; preds = %lor.lhs.false5
  %12 = load i64, i64* %memusage, align 8, !dbg !862
  store i64 %12, i64* %retval, align 8, !dbg !863
  br label %return, !dbg !863

return:                                           ; preds = %if.end, %if.then
  %13 = load i64, i64* %retval, align 8, !dbg !864
  ret i64 %13, !dbg !864
}

; Function Attrs: nounwind readonly uwtable
define i64 @lzma_memlimit_get(%struct.lzma_stream* %strm) #6 !dbg !215 {
entry:
  %retval = alloca i64, align 8
  %strm.addr = alloca %struct.lzma_stream*, align 8
  %old_memlimit = alloca i64, align 8
  %memusage = alloca i64, align 8
  store %struct.lzma_stream* %strm, %struct.lzma_stream** %strm.addr, align 8
  call void @llvm.dbg.declare(metadata %struct.lzma_stream** %strm.addr, metadata !865, metadata !228), !dbg !866
  call void @llvm.dbg.declare(metadata i64* %old_memlimit, metadata !867, metadata !228), !dbg !868
  call void @llvm.dbg.declare(metadata i64* %memusage, metadata !869, metadata !228), !dbg !870
  %0 = load %struct.lzma_stream*, %struct.lzma_stream** %strm.addr, align 8, !dbg !871
  %cmp = icmp eq %struct.lzma_stream* %0, null, !dbg !873
  br i1 %cmp, label %if.then, label %lor.lhs.false, !dbg !874

lor.lhs.false:                                    ; preds = %entry
  %1 = load %struct.lzma_stream*, %struct.lzma_stream** %strm.addr, align 8, !dbg !875
  %internal = getelementptr inbounds %struct.lzma_stream, %struct.lzma_stream* %1, i32 0, i32 7, !dbg !877
  %2 = load %struct.lzma_internal_s*, %struct.lzma_internal_s** %internal, align 8, !dbg !877
  %cmp1 = icmp eq %struct.lzma_internal_s* %2, null, !dbg !878
  br i1 %cmp1, label %if.then, label %lor.lhs.false2, !dbg !879

lor.lhs.false2:                                   ; preds = %lor.lhs.false
  %3 = load %struct.lzma_stream*, %struct.lzma_stream** %strm.addr, align 8, !dbg !880
  %internal3 = getelementptr inbounds %struct.lzma_stream, %struct.lzma_stream* %3, i32 0, i32 7, !dbg !881
  %4 = load %struct.lzma_internal_s*, %struct.lzma_internal_s** %internal3, align 8, !dbg !881
  %next = getelementptr inbounds %struct.lzma_internal_s, %struct.lzma_internal_s* %4, i32 0, i32 0, !dbg !882
  %memconfig = getelementptr inbounds %struct.lzma_next_coder_s, %struct.lzma_next_coder_s* %next, i32 0, i32 6, !dbg !883
  %5 = load i32 (%struct.lzma_coder_s*, i64*, i64*, i64)*, i32 (%struct.lzma_coder_s*, i64*, i64*, i64)** %memconfig, align 8, !dbg !883
  %cmp4 = icmp eq i32 (%struct.lzma_coder_s*, i64*, i64*, i64)* %5, null, !dbg !884
  br i1 %cmp4, label %if.then, label %lor.lhs.false5, !dbg !885

lor.lhs.false5:                                   ; preds = %lor.lhs.false2
  %6 = load %struct.lzma_stream*, %struct.lzma_stream** %strm.addr, align 8, !dbg !886
  %internal6 = getelementptr inbounds %struct.lzma_stream, %struct.lzma_stream* %6, i32 0, i32 7, !dbg !887
  %7 = load %struct.lzma_internal_s*, %struct.lzma_internal_s** %internal6, align 8, !dbg !887
  %next7 = getelementptr inbounds %struct.lzma_internal_s, %struct.lzma_internal_s* %7, i32 0, i32 0, !dbg !888
  %memconfig8 = getelementptr inbounds %struct.lzma_next_coder_s, %struct.lzma_next_coder_s* %next7, i32 0, i32 6, !dbg !889
  %8 = load i32 (%struct.lzma_coder_s*, i64*, i64*, i64)*, i32 (%struct.lzma_coder_s*, i64*, i64*, i64)** %memconfig8, align 8, !dbg !889
  %9 = load %struct.lzma_stream*, %struct.lzma_stream** %strm.addr, align 8, !dbg !890
  %internal9 = getelementptr inbounds %struct.lzma_stream, %struct.lzma_stream* %9, i32 0, i32 7, !dbg !891
  %10 = load %struct.lzma_internal_s*, %struct.lzma_internal_s** %internal9, align 8, !dbg !891
  %next10 = getelementptr inbounds %struct.lzma_internal_s, %struct.lzma_internal_s* %10, i32 0, i32 0, !dbg !892
  %coder = getelementptr inbounds %struct.lzma_next_coder_s, %struct.lzma_next_coder_s* %next10, i32 0, i32 0, !dbg !893
  %11 = load %struct.lzma_coder_s*, %struct.lzma_coder_s** %coder, align 8, !dbg !893
  %call = call i32 %8(%struct.lzma_coder_s* %11, i64* %memusage, i64* %old_memlimit, i64 0), !dbg !886
  %cmp11 = icmp ne i32 %call, 0, !dbg !894
  br i1 %cmp11, label %if.then, label %if.end, !dbg !895

if.then:                                          ; preds = %lor.lhs.false5, %lor.lhs.false2, %lor.lhs.false, %entry
  store i64 0, i64* %retval, align 8, !dbg !897
  br label %return, !dbg !897

if.end:                                           ; preds = %lor.lhs.false5
  %12 = load i64, i64* %old_memlimit, align 8, !dbg !898
  store i64 %12, i64* %retval, align 8, !dbg !899
  br label %return, !dbg !899

return:                                           ; preds = %if.end, %if.then
  %13 = load i64, i64* %retval, align 8, !dbg !900
  ret i64 %13, !dbg !900
}

; Function Attrs: nounwind uwtable
define i32 @lzma_memlimit_set(%struct.lzma_stream* %strm, i64 %new_memlimit) #1 !dbg !216 {
entry:
  %retval = alloca i32, align 4
  %strm.addr = alloca %struct.lzma_stream*, align 8
  %new_memlimit.addr = alloca i64, align 8
  %old_memlimit = alloca i64, align 8
  %memusage = alloca i64, align 8
  store %struct.lzma_stream* %strm, %struct.lzma_stream** %strm.addr, align 8
  call void @llvm.dbg.declare(metadata %struct.lzma_stream** %strm.addr, metadata !901, metadata !228), !dbg !902
  store i64 %new_memlimit, i64* %new_memlimit.addr, align 8
  call void @llvm.dbg.declare(metadata i64* %new_memlimit.addr, metadata !903, metadata !228), !dbg !904
  call void @llvm.dbg.declare(metadata i64* %old_memlimit, metadata !905, metadata !228), !dbg !906
  call void @llvm.dbg.declare(metadata i64* %memusage, metadata !907, metadata !228), !dbg !908
  %0 = load %struct.lzma_stream*, %struct.lzma_stream** %strm.addr, align 8, !dbg !909
  %cmp = icmp eq %struct.lzma_stream* %0, null, !dbg !911
  br i1 %cmp, label %if.then, label %lor.lhs.false, !dbg !912

lor.lhs.false:                                    ; preds = %entry
  %1 = load %struct.lzma_stream*, %struct.lzma_stream** %strm.addr, align 8, !dbg !913
  %internal = getelementptr inbounds %struct.lzma_stream, %struct.lzma_stream* %1, i32 0, i32 7, !dbg !915
  %2 = load %struct.lzma_internal_s*, %struct.lzma_internal_s** %internal, align 8, !dbg !915
  %cmp1 = icmp eq %struct.lzma_internal_s* %2, null, !dbg !916
  br i1 %cmp1, label %if.then, label %lor.lhs.false2, !dbg !917

lor.lhs.false2:                                   ; preds = %lor.lhs.false
  %3 = load %struct.lzma_stream*, %struct.lzma_stream** %strm.addr, align 8, !dbg !918
  %internal3 = getelementptr inbounds %struct.lzma_stream, %struct.lzma_stream* %3, i32 0, i32 7, !dbg !919
  %4 = load %struct.lzma_internal_s*, %struct.lzma_internal_s** %internal3, align 8, !dbg !919
  %next = getelementptr inbounds %struct.lzma_internal_s, %struct.lzma_internal_s* %4, i32 0, i32 0, !dbg !920
  %memconfig = getelementptr inbounds %struct.lzma_next_coder_s, %struct.lzma_next_coder_s* %next, i32 0, i32 6, !dbg !921
  %5 = load i32 (%struct.lzma_coder_s*, i64*, i64*, i64)*, i32 (%struct.lzma_coder_s*, i64*, i64*, i64)** %memconfig, align 8, !dbg !921
  %cmp4 = icmp eq i32 (%struct.lzma_coder_s*, i64*, i64*, i64)* %5, null, !dbg !922
  br i1 %cmp4, label %if.then, label %if.end, !dbg !923

if.then:                                          ; preds = %lor.lhs.false2, %lor.lhs.false, %entry
  store i32 11, i32* %retval, align 4, !dbg !925
  br label %return, !dbg !925

if.end:                                           ; preds = %lor.lhs.false2
  %6 = load i64, i64* %new_memlimit.addr, align 8, !dbg !926
  %cmp5 = icmp ne i64 %6, 0, !dbg !928
  br i1 %cmp5, label %land.lhs.true, label %if.end8, !dbg !929

land.lhs.true:                                    ; preds = %if.end
  %7 = load i64, i64* %new_memlimit.addr, align 8, !dbg !930
  %cmp6 = icmp ult i64 %7, 32768, !dbg !932
  br i1 %cmp6, label %if.then7, label %if.end8, !dbg !933

if.then7:                                         ; preds = %land.lhs.true
  store i32 6, i32* %retval, align 4, !dbg !934
  br label %return, !dbg !934

if.end8:                                          ; preds = %land.lhs.true, %if.end
  %8 = load %struct.lzma_stream*, %struct.lzma_stream** %strm.addr, align 8, !dbg !935
  %internal9 = getelementptr inbounds %struct.lzma_stream, %struct.lzma_stream* %8, i32 0, i32 7, !dbg !936
  %9 = load %struct.lzma_internal_s*, %struct.lzma_internal_s** %internal9, align 8, !dbg !936
  %next10 = getelementptr inbounds %struct.lzma_internal_s, %struct.lzma_internal_s* %9, i32 0, i32 0, !dbg !937
  %memconfig11 = getelementptr inbounds %struct.lzma_next_coder_s, %struct.lzma_next_coder_s* %next10, i32 0, i32 6, !dbg !938
  %10 = load i32 (%struct.lzma_coder_s*, i64*, i64*, i64)*, i32 (%struct.lzma_coder_s*, i64*, i64*, i64)** %memconfig11, align 8, !dbg !938
  %11 = load %struct.lzma_stream*, %struct.lzma_stream** %strm.addr, align 8, !dbg !939
  %internal12 = getelementptr inbounds %struct.lzma_stream, %struct.lzma_stream* %11, i32 0, i32 7, !dbg !940
  %12 = load %struct.lzma_internal_s*, %struct.lzma_internal_s** %internal12, align 8, !dbg !940
  %next13 = getelementptr inbounds %struct.lzma_internal_s, %struct.lzma_internal_s* %12, i32 0, i32 0, !dbg !941
  %coder = getelementptr inbounds %struct.lzma_next_coder_s, %struct.lzma_next_coder_s* %next13, i32 0, i32 0, !dbg !942
  %13 = load %struct.lzma_coder_s*, %struct.lzma_coder_s** %coder, align 8, !dbg !942
  %14 = load i64, i64* %new_memlimit.addr, align 8, !dbg !943
  %call = call i32 %10(%struct.lzma_coder_s* %13, i64* %memusage, i64* %old_memlimit, i64 %14), !dbg !935
  store i32 %call, i32* %retval, align 4, !dbg !944
  br label %return, !dbg !944

return:                                           ; preds = %if.end8, %if.then7, %if.then
  %15 = load i32, i32* %retval, align 4, !dbg !945
  ret i32 %15, !dbg !945
}

attributes #0 = { nounwind readnone uwtable "disable-tail-calls"="false" "less-precise-fpmad"="false" "no-frame-pointer-elim"="true" "no-frame-pointer-elim-non-leaf" "no-infs-fp-math"="false" "no-nans-fp-math"="false" "stack-protector-buffer-size"="8" "target-cpu"="x86-64" "target-features"="+fxsr,+mmx,+sse,+sse2" "unsafe-fp-math"="false" "use-soft-float"="false" }
attributes #1 = { nounwind uwtable "disable-tail-calls"="false" "less-precise-fpmad"="false" "no-frame-pointer-elim"="true" "no-frame-pointer-elim-non-leaf" "no-infs-fp-math"="false" "no-nans-fp-math"="false" "stack-protector-buffer-size"="8" "target-cpu"="x86-64" "target-features"="+fxsr,+mmx,+sse,+sse2" "unsafe-fp-math"="false" "use-soft-float"="false" }
attributes #2 = { nounwind readnone }
attributes #3 = { nounwind "disable-tail-calls"="false" "less-precise-fpmad"="false" "no-frame-pointer-elim"="true" "no-frame-pointer-elim-non-leaf" "no-infs-fp-math"="false" "no-nans-fp-math"="false" "stack-protector-buffer-size"="8" "target-cpu"="x86-64" "target-features"="+fxsr,+mmx,+sse,+sse2" "unsafe-fp-math"="false" "use-soft-float"="false" }
attributes #4 = { argmemonly nounwind }
attributes #5 = { noreturn nounwind "disable-tail-calls"="false" "less-precise-fpmad"="false" "no-frame-pointer-elim"="true" "no-frame-pointer-elim-non-leaf" "no-infs-fp-math"="false" "no-nans-fp-math"="false" "stack-protector-buffer-size"="8" "target-cpu"="x86-64" "target-features"="+fxsr,+mmx,+sse,+sse2" "unsafe-fp-math"="false" "use-soft-float"="false" }
attributes #6 = { nounwind readonly uwtable "disable-tail-calls"="false" "less-precise-fpmad"="false" "no-frame-pointer-elim"="true" "no-frame-pointer-elim-non-leaf" "no-infs-fp-math"="false" "no-nans-fp-math"="false" "stack-protector-buffer-size"="8" "target-cpu"="x86-64" "target-features"="+fxsr,+mmx,+sse,+sse2" "unsafe-fp-math"="false" "use-soft-float"="false" }
attributes #7 = { nounwind }
attributes #8 = { noreturn nounwind }

!llvm.dbg.cu = !{!0}
!llvm.module.flags = !{!222, !223}
!llvm.ident = !{!224}

!0 = distinct !DICompileUnit(language: DW_LANG_C99, file: !1, producer: "clang version 3.8.0 (tags/RELEASE_380/final)", isOptimized: false, runtimeVersion: 0, emissionKind: 1, enums: !2, retainedTypes: !130, subprograms: !132, globals: !219)
!1 = !DIFile(filename: "/data/download/cmake/cmake-master/Utilities/cmliblzma/liblzma/common/common.c", directory: "/data/download/cmake/cmake-master/Utilities/cmliblzma")
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
!130 = !{!65, !50, !131}
!131 = !DIBasicType(name: "unsigned int", size: 32, align: 32, encoding: DW_ATE_unsigned)
!132 = !{!133, !138, !144, !147, !150, !153, !167, !170, !173, !201, !204, !207, !212, !215, !216}
!133 = distinct !DISubprogram(name: "lzma_version_number", scope: !1, file: !1, line: 21, type: !134, isLocal: false, isDefinition: true, scopeLine: 22, flags: DIFlagPrototyped, isOptimized: false, variables: !137)
!134 = !DISubroutineType(types: !135)
!135 = !{!136}
!136 = !DIDerivedType(tag: DW_TAG_typedef, name: "uint32_t", file: !47, line: 51, baseType: !131)
!137 = !{}
!138 = distinct !DISubprogram(name: "lzma_version_string", scope: !1, file: !1, line: 28, type: !139, isLocal: false, isDefinition: true, scopeLine: 29, flags: DIFlagPrototyped, isOptimized: false, variables: !137)
!139 = !DISubroutineType(types: !140)
!140 = !{!141}
!141 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !142, size: 64, align: 64)
!142 = !DIDerivedType(tag: DW_TAG_const_type, baseType: !143)
!143 = !DIBasicType(name: "char", size: 8, align: 8, encoding: DW_ATE_signed_char)
!144 = distinct !DISubprogram(name: "lzma_alloc", scope: !1, file: !1, line: 39, type: !145, isLocal: false, isDefinition: true, scopeLine: 40, flags: DIFlagPrototyped, isOptimized: false, variables: !137)
!145 = !DISubroutineType(types: !146)
!146 = !{!65, !66, !57}
!147 = distinct !DISubprogram(name: "lzma_free", scope: !1, file: !1, line: 57, type: !148, isLocal: false, isDefinition: true, scopeLine: 58, flags: DIFlagPrototyped, isOptimized: false, variables: !137)
!148 = !DISubroutineType(types: !149)
!149 = !{null, !65, !57}
!150 = distinct !DISubprogram(name: "lzma_bufcpy", scope: !1, file: !1, line: 73, type: !151, isLocal: false, isDefinition: true, scopeLine: 76, flags: DIFlagPrototyped, isOptimized: false, variables: !137)
!151 = !DISubroutineType(types: !152)
!152 = !{!66, !73, !78, !66, !80, !78, !66}
!153 = distinct !DISubprogram(name: "lzma_next_filter_init", scope: !1, file: !1, line: 91, type: !154, isLocal: false, isDefinition: true, scopeLine: 93, flags: DIFlagPrototyped, isOptimized: false, variables: !137)
!154 = !DISubroutineType(types: !155)
!155 = !{!56, !156, !57, !157}
!156 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !36, size: 64, align: 64)
!157 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !158, size: 64, align: 64)
!158 = !DIDerivedType(tag: DW_TAG_const_type, baseType: !159)
!159 = !DIDerivedType(tag: DW_TAG_typedef, name: "lzma_filter_info", file: !32, line: 77, baseType: !160)
!160 = !DICompositeType(tag: DW_TAG_structure_type, name: "lzma_filter_info_s", file: !32, line: 104, size: 192, align: 64, elements: !161)
!161 = !{!162, !163, !166}
!162 = !DIDerivedType(tag: DW_TAG_member, name: "id", scope: !160, file: !32, line: 107, baseType: !44, size: 64, align: 64)
!163 = !DIDerivedType(tag: DW_TAG_member, name: "init", scope: !160, file: !32, line: 111, baseType: !164, size: 64, align: 64, offset: 64)
!164 = !DIDerivedType(tag: DW_TAG_typedef, name: "lzma_init_function", file: !32, line: 81, baseType: !165)
!165 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !154, size: 64, align: 64)
!166 = !DIDerivedType(tag: DW_TAG_member, name: "options", scope: !160, file: !32, line: 114, baseType: !65, size: 64, align: 64, offset: 128)
!167 = distinct !DISubprogram(name: "lzma_next_filter_update", scope: !1, file: !1, line: 102, type: !168, isLocal: false, isDefinition: true, scopeLine: 104, flags: DIFlagPrototyped, isOptimized: false, variables: !137)
!168 = !DISubroutineType(types: !169)
!169 = !{!56, !156, !57, !104}
!170 = distinct !DISubprogram(name: "lzma_next_end", scope: !1, file: !1, line: 120, type: !171, isLocal: false, isDefinition: true, scopeLine: 121, flags: DIFlagPrototyped, isOptimized: false, variables: !137)
!171 = !DISubroutineType(types: !172)
!172 = !{null, !156, !57}
!173 = distinct !DISubprogram(name: "lzma_strm_init", scope: !1, file: !1, line: 145, type: !174, isLocal: false, isDefinition: true, scopeLine: 146, flags: DIFlagPrototyped, isOptimized: false, variables: !137)
!174 = !DISubroutineType(types: !175)
!175 = !{!56, !176}
!176 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !177, size: 64, align: 64)
!177 = !DIDerivedType(tag: DW_TAG_typedef, name: "lzma_stream", file: !4, line: 490, baseType: !178)
!178 = !DICompositeType(tag: DW_TAG_structure_type, file: !4, line: 453, size: 1088, align: 64, elements: !179)
!179 = !{!180, !181, !182, !183, !184, !185, !186, !187, !190, !191, !192, !193, !194, !195, !196, !197, !198, !200}
!180 = !DIDerivedType(tag: DW_TAG_member, name: "next_in", scope: !178, file: !4, line: 454, baseType: !74, size: 64, align: 64)
!181 = !DIDerivedType(tag: DW_TAG_member, name: "avail_in", scope: !178, file: !4, line: 455, baseType: !66, size: 64, align: 64, offset: 64)
!182 = !DIDerivedType(tag: DW_TAG_member, name: "total_in", scope: !178, file: !4, line: 456, baseType: !46, size: 64, align: 64, offset: 128)
!183 = !DIDerivedType(tag: DW_TAG_member, name: "next_out", scope: !178, file: !4, line: 458, baseType: !81, size: 64, align: 64, offset: 192)
!184 = !DIDerivedType(tag: DW_TAG_member, name: "avail_out", scope: !178, file: !4, line: 459, baseType: !66, size: 64, align: 64, offset: 256)
!185 = !DIDerivedType(tag: DW_TAG_member, name: "total_out", scope: !178, file: !4, line: 460, baseType: !46, size: 64, align: 64, offset: 320)
!186 = !DIDerivedType(tag: DW_TAG_member, name: "allocator", scope: !178, file: !4, line: 468, baseType: !57, size: 64, align: 64, offset: 384)
!187 = !DIDerivedType(tag: DW_TAG_member, name: "internal", scope: !178, file: !4, line: 471, baseType: !188, size: 64, align: 64, offset: 448)
!188 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !189, size: 64, align: 64)
!189 = !DIDerivedType(tag: DW_TAG_typedef, name: "lzma_internal", file: !4, line: 411, baseType: !33)
!190 = !DIDerivedType(tag: DW_TAG_member, name: "reserved_ptr1", scope: !178, file: !4, line: 479, baseType: !65, size: 64, align: 64, offset: 512)
!191 = !DIDerivedType(tag: DW_TAG_member, name: "reserved_ptr2", scope: !178, file: !4, line: 480, baseType: !65, size: 64, align: 64, offset: 576)
!192 = !DIDerivedType(tag: DW_TAG_member, name: "reserved_ptr3", scope: !178, file: !4, line: 481, baseType: !65, size: 64, align: 64, offset: 640)
!193 = !DIDerivedType(tag: DW_TAG_member, name: "reserved_ptr4", scope: !178, file: !4, line: 482, baseType: !65, size: 64, align: 64, offset: 704)
!194 = !DIDerivedType(tag: DW_TAG_member, name: "reserved_int1", scope: !178, file: !4, line: 483, baseType: !46, size: 64, align: 64, offset: 768)
!195 = !DIDerivedType(tag: DW_TAG_member, name: "reserved_int2", scope: !178, file: !4, line: 484, baseType: !46, size: 64, align: 64, offset: 832)
!196 = !DIDerivedType(tag: DW_TAG_member, name: "reserved_int3", scope: !178, file: !4, line: 485, baseType: !66, size: 64, align: 64, offset: 896)
!197 = !DIDerivedType(tag: DW_TAG_member, name: "reserved_int4", scope: !178, file: !4, line: 486, baseType: !66, size: 64, align: 64, offset: 960)
!198 = !DIDerivedType(tag: DW_TAG_member, name: "reserved_enum1", scope: !178, file: !4, line: 487, baseType: !199, size: 32, align: 32, offset: 1024)
!199 = !DIDerivedType(tag: DW_TAG_typedef, name: "lzma_reserved_enum", file: !4, line: 46, baseType: !127)
!200 = !DIDerivedType(tag: DW_TAG_member, name: "reserved_enum2", scope: !178, file: !4, line: 488, baseType: !199, size: 32, align: 32, offset: 1056)
!201 = distinct !DISubprogram(name: "lzma_code", scope: !1, file: !1, line: 174, type: !202, isLocal: false, isDefinition: true, scopeLine: 175, flags: DIFlagPrototyped, isOptimized: false, variables: !137)
!202 = !DISubroutineType(types: !203)
!203 = !{!56, !176, !82}
!204 = distinct !DISubprogram(name: "lzma_end", scope: !1, file: !1, line: 316, type: !205, isLocal: false, isDefinition: true, scopeLine: 317, flags: DIFlagPrototyped, isOptimized: false, variables: !137)
!205 = !DISubroutineType(types: !206)
!206 = !{null, !176}
!207 = distinct !DISubprogram(name: "lzma_get_check", scope: !1, file: !1, line: 329, type: !208, isLocal: false, isDefinition: true, scopeLine: 330, flags: DIFlagPrototyped, isOptimized: false, variables: !137)
!208 = !DISubroutineType(types: !209)
!209 = !{!92, !210}
!210 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !211, size: 64, align: 64)
!211 = !DIDerivedType(tag: DW_TAG_const_type, baseType: !177)
!212 = distinct !DISubprogram(name: "lzma_memusage", scope: !1, file: !1, line: 341, type: !213, isLocal: false, isDefinition: true, scopeLine: 342, flags: DIFlagPrototyped, isOptimized: false, variables: !137)
!213 = !DISubroutineType(types: !214)
!214 = !{!46, !210}
!215 = distinct !DISubprogram(name: "lzma_memlimit_get", scope: !1, file: !1, line: 358, type: !213, isLocal: false, isDefinition: true, scopeLine: 359, flags: DIFlagPrototyped, isOptimized: false, variables: !137)
!216 = distinct !DISubprogram(name: "lzma_memlimit_set", scope: !1, file: !1, line: 375, type: !217, isLocal: false, isDefinition: true, scopeLine: 376, flags: DIFlagPrototyped, isOptimized: false, variables: !137)
!217 = !DISubroutineType(types: !218)
!218 = !{!56, !176, !46}
!219 = !{!220}
!220 = !DIGlobalVariable(name: "LZMA_NEXT_CODER_INIT", scope: !0, file: !32, line: 159, type: !221, isLocal: true, isDefinition: true, variable: %struct.lzma_next_coder_s* @LZMA_NEXT_CODER_INIT)
!221 = !DIDerivedType(tag: DW_TAG_const_type, baseType: !36)
!222 = !{i32 2, !"Dwarf Version", i32 4}
!223 = !{i32 2, !"Debug Info Version", i32 3}
!224 = !{!"clang version 3.8.0 (tags/RELEASE_380/final)"}
!225 = !DILocation(line: 23, column: 2, scope: !133)
!226 = !DILocation(line: 30, column: 2, scope: !138)
!227 = !DILocalVariable(name: "size", arg: 1, scope: !144, file: !1, line: 39, type: !66)
!228 = !DIExpression()
!229 = !DILocation(line: 39, column: 19, scope: !144)
!230 = !DILocalVariable(name: "allocator", arg: 2, scope: !144, file: !1, line: 39, type: !57)
!231 = !DILocation(line: 39, column: 41, scope: !144)
!232 = !DILocalVariable(name: "ptr", scope: !144, file: !1, line: 41, type: !65)
!233 = !DILocation(line: 41, column: 8, scope: !144)
!234 = !DILocation(line: 44, column: 6, scope: !235)
!235 = distinct !DILexicalBlock(scope: !144, file: !1, line: 44, column: 6)
!236 = !DILocation(line: 44, column: 11, scope: !235)
!237 = !DILocation(line: 44, column: 6, scope: !144)
!238 = !DILocation(line: 45, column: 8, scope: !235)
!239 = !DILocation(line: 45, column: 3, scope: !235)
!240 = !DILocation(line: 47, column: 6, scope: !241)
!241 = distinct !DILexicalBlock(scope: !144, file: !1, line: 47, column: 6)
!242 = !DILocation(line: 47, column: 16, scope: !241)
!243 = !DILocation(line: 47, column: 24, scope: !241)
!244 = !DILocation(line: 47, column: 27, scope: !245)
!245 = !DILexicalBlockFile(scope: !241, file: !1, discriminator: 1)
!246 = !DILocation(line: 47, column: 38, scope: !245)
!247 = !DILocation(line: 47, column: 44, scope: !245)
!248 = !DILocation(line: 47, column: 6, scope: !245)
!249 = !DILocation(line: 48, column: 9, scope: !241)
!250 = !DILocation(line: 48, column: 20, scope: !241)
!251 = !DILocation(line: 48, column: 26, scope: !241)
!252 = !DILocation(line: 48, column: 37, scope: !241)
!253 = !DILocation(line: 48, column: 48, scope: !241)
!254 = !DILocation(line: 48, column: 7, scope: !241)
!255 = !DILocation(line: 48, column: 3, scope: !241)
!256 = !DILocation(line: 50, column: 16, scope: !241)
!257 = !DILocation(line: 50, column: 9, scope: !241)
!258 = !DILocation(line: 50, column: 7, scope: !241)
!259 = !DILocation(line: 52, column: 9, scope: !144)
!260 = !DILocation(line: 52, column: 2, scope: !144)
!261 = !DILocalVariable(name: "ptr", arg: 1, scope: !147, file: !1, line: 57, type: !65)
!262 = !DILocation(line: 57, column: 17, scope: !147)
!263 = !DILocalVariable(name: "allocator", arg: 2, scope: !147, file: !1, line: 57, type: !57)
!264 = !DILocation(line: 57, column: 38, scope: !147)
!265 = !DILocation(line: 59, column: 6, scope: !266)
!266 = distinct !DILexicalBlock(scope: !147, file: !1, line: 59, column: 6)
!267 = !DILocation(line: 59, column: 16, scope: !266)
!268 = !DILocation(line: 59, column: 24, scope: !266)
!269 = !DILocation(line: 59, column: 27, scope: !270)
!270 = !DILexicalBlockFile(scope: !266, file: !1, discriminator: 1)
!271 = !DILocation(line: 59, column: 38, scope: !270)
!272 = !DILocation(line: 59, column: 43, scope: !270)
!273 = !DILocation(line: 59, column: 6, scope: !270)
!274 = !DILocation(line: 60, column: 3, scope: !266)
!275 = !DILocation(line: 60, column: 14, scope: !266)
!276 = !DILocation(line: 60, column: 19, scope: !266)
!277 = !DILocation(line: 60, column: 30, scope: !266)
!278 = !DILocation(line: 60, column: 38, scope: !266)
!279 = !DILocation(line: 62, column: 8, scope: !266)
!280 = !DILocation(line: 62, column: 3, scope: !266)
!281 = !DILocation(line: 64, column: 2, scope: !147)
!282 = !DILocalVariable(name: "in", arg: 1, scope: !150, file: !1, line: 73, type: !73)
!283 = !DILocation(line: 73, column: 42, scope: !150)
!284 = !DILocalVariable(name: "in_pos", arg: 2, scope: !150, file: !1, line: 73, type: !78)
!285 = !DILocation(line: 73, column: 68, scope: !150)
!286 = !DILocalVariable(name: "in_size", arg: 3, scope: !150, file: !1, line: 74, type: !66)
!287 = !DILocation(line: 74, column: 10, scope: !150)
!288 = !DILocalVariable(name: "out", arg: 4, scope: !150, file: !1, line: 74, type: !80)
!289 = !DILocation(line: 74, column: 42, scope: !150)
!290 = !DILocalVariable(name: "out_pos", arg: 5, scope: !150, file: !1, line: 75, type: !78)
!291 = !DILocation(line: 75, column: 25, scope: !150)
!292 = !DILocalVariable(name: "out_size", arg: 6, scope: !150, file: !1, line: 75, type: !66)
!293 = !DILocation(line: 75, column: 41, scope: !150)
!294 = !DILocalVariable(name: "in_avail", scope: !150, file: !1, line: 77, type: !295)
!295 = !DIDerivedType(tag: DW_TAG_const_type, baseType: !66)
!296 = !DILocation(line: 77, column: 15, scope: !150)
!297 = !DILocation(line: 77, column: 26, scope: !150)
!298 = !DILocation(line: 77, column: 37, scope: !150)
!299 = !DILocation(line: 77, column: 36, scope: !150)
!300 = !DILocation(line: 77, column: 34, scope: !150)
!301 = !DILocalVariable(name: "out_avail", scope: !150, file: !1, line: 78, type: !295)
!302 = !DILocation(line: 78, column: 15, scope: !150)
!303 = !DILocation(line: 78, column: 27, scope: !150)
!304 = !DILocation(line: 78, column: 39, scope: !150)
!305 = !DILocation(line: 78, column: 38, scope: !150)
!306 = !DILocation(line: 78, column: 36, scope: !150)
!307 = !DILocalVariable(name: "copy_size", scope: !150, file: !1, line: 79, type: !295)
!308 = !DILocation(line: 79, column: 15, scope: !150)
!309 = !DILocation(line: 79, column: 27, scope: !150)
!310 = !DILocation(line: 79, column: 27, scope: !311)
!311 = !DILexicalBlockFile(scope: !150, file: !1, discriminator: 1)
!312 = !DILocation(line: 79, column: 27, scope: !313)
!313 = !DILexicalBlockFile(scope: !150, file: !1, discriminator: 2)
!314 = !DILocation(line: 79, column: 27, scope: !315)
!315 = !DILexicalBlockFile(scope: !150, file: !1, discriminator: 3)
!316 = !DILocation(line: 79, column: 15, scope: !315)
!317 = !DILocation(line: 81, column: 9, scope: !150)
!318 = !DILocation(line: 81, column: 16, scope: !150)
!319 = !DILocation(line: 81, column: 15, scope: !150)
!320 = !DILocation(line: 81, column: 13, scope: !150)
!321 = !DILocation(line: 81, column: 25, scope: !150)
!322 = !DILocation(line: 81, column: 31, scope: !150)
!323 = !DILocation(line: 81, column: 30, scope: !150)
!324 = !DILocation(line: 81, column: 28, scope: !150)
!325 = !DILocation(line: 81, column: 39, scope: !150)
!326 = !DILocation(line: 81, column: 2, scope: !150)
!327 = !DILocation(line: 83, column: 13, scope: !150)
!328 = !DILocation(line: 83, column: 3, scope: !150)
!329 = !DILocation(line: 83, column: 10, scope: !150)
!330 = !DILocation(line: 84, column: 14, scope: !150)
!331 = !DILocation(line: 84, column: 3, scope: !150)
!332 = !DILocation(line: 84, column: 11, scope: !150)
!333 = !DILocation(line: 86, column: 9, scope: !150)
!334 = !DILocation(line: 86, column: 2, scope: !150)
!335 = !DILocalVariable(name: "next", arg: 1, scope: !153, file: !1, line: 91, type: !156)
!336 = !DILocation(line: 91, column: 40, scope: !153)
!337 = !DILocalVariable(name: "allocator", arg: 2, scope: !153, file: !1, line: 91, type: !57)
!338 = !DILocation(line: 91, column: 62, scope: !153)
!339 = !DILocalVariable(name: "filters", arg: 3, scope: !153, file: !1, line: 92, type: !157)
!340 = !DILocation(line: 92, column: 27, scope: !153)
!341 = !DILocation(line: 94, column: 2, scope: !153)
!342 = !DILocation(line: 94, column: 2, scope: !343)
!343 = !DILexicalBlockFile(scope: !344, file: !1, discriminator: 1)
!344 = distinct !DILexicalBlock(scope: !345, file: !1, line: 94, column: 2)
!345 = distinct !DILexicalBlock(scope: !153, file: !1, line: 94, column: 2)
!346 = !DILocation(line: 94, column: 2, scope: !347)
!347 = !DILexicalBlockFile(scope: !344, file: !1, discriminator: 2)
!348 = !DILocation(line: 94, column: 2, scope: !349)
!349 = !DILexicalBlockFile(scope: !345, file: !1, discriminator: 3)
!350 = !DILocation(line: 95, column: 13, scope: !153)
!351 = !DILocation(line: 95, column: 24, scope: !153)
!352 = !DILocation(line: 95, column: 2, scope: !153)
!353 = !DILocation(line: 95, column: 8, scope: !153)
!354 = !DILocation(line: 95, column: 11, scope: !153)
!355 = !DILocation(line: 96, column: 9, scope: !153)
!356 = !DILocation(line: 96, column: 20, scope: !153)
!357 = !DILocation(line: 96, column: 25, scope: !153)
!358 = !DILocation(line: 96, column: 9, scope: !359)
!359 = !DILexicalBlockFile(scope: !153, file: !1, discriminator: 1)
!360 = !DILocation(line: 97, column: 16, scope: !153)
!361 = !DILocation(line: 97, column: 27, scope: !153)
!362 = !DILocation(line: 97, column: 32, scope: !153)
!363 = !DILocation(line: 97, column: 38, scope: !153)
!364 = !DILocation(line: 97, column: 49, scope: !153)
!365 = !DILocation(line: 96, column: 9, scope: !366)
!366 = !DILexicalBlockFile(scope: !153, file: !1, discriminator: 2)
!367 = !DILocation(line: 96, column: 9, scope: !368)
!368 = !DILexicalBlockFile(scope: !153, file: !1, discriminator: 3)
!369 = !DILocation(line: 96, column: 2, scope: !368)
!370 = !DILocalVariable(name: "next", arg: 1, scope: !170, file: !1, line: 120, type: !156)
!371 = !DILocation(line: 120, column: 32, scope: !170)
!372 = !DILocalVariable(name: "allocator", arg: 2, scope: !170, file: !1, line: 120, type: !57)
!373 = !DILocation(line: 120, column: 54, scope: !170)
!374 = !DILocation(line: 122, column: 6, scope: !375)
!375 = distinct !DILexicalBlock(scope: !170, file: !1, line: 122, column: 6)
!376 = !DILocation(line: 122, column: 12, scope: !375)
!377 = !DILocation(line: 122, column: 17, scope: !375)
!378 = !DILocation(line: 122, column: 6, scope: !170)
!379 = !DILocation(line: 126, column: 7, scope: !380)
!380 = distinct !DILexicalBlock(scope: !381, file: !1, line: 126, column: 7)
!381 = distinct !DILexicalBlock(scope: !375, file: !1, line: 122, column: 39)
!382 = !DILocation(line: 126, column: 13, scope: !380)
!383 = !DILocation(line: 126, column: 17, scope: !380)
!384 = !DILocation(line: 126, column: 7, scope: !381)
!385 = !DILocation(line: 127, column: 4, scope: !380)
!386 = !DILocation(line: 127, column: 10, scope: !380)
!387 = !DILocation(line: 127, column: 14, scope: !380)
!388 = !DILocation(line: 127, column: 20, scope: !380)
!389 = !DILocation(line: 127, column: 27, scope: !380)
!390 = !DILocation(line: 129, column: 14, scope: !380)
!391 = !DILocation(line: 129, column: 20, scope: !380)
!392 = !DILocation(line: 129, column: 27, scope: !380)
!393 = !DILocation(line: 129, column: 4, scope: !380)
!394 = !DILocation(line: 133, column: 4, scope: !381)
!395 = !DILocation(line: 133, column: 11, scope: !381)
!396 = !DILocation(line: 134, column: 2, scope: !381)
!397 = !DILocation(line: 136, column: 2, scope: !170)
!398 = !DILocalVariable(name: "next", arg: 1, scope: !167, file: !1, line: 102, type: !156)
!399 = !DILocation(line: 102, column: 42, scope: !167)
!400 = !DILocalVariable(name: "allocator", arg: 2, scope: !167, file: !1, line: 102, type: !57)
!401 = !DILocation(line: 102, column: 64, scope: !167)
!402 = !DILocalVariable(name: "reversed_filters", arg: 3, scope: !167, file: !1, line: 103, type: !104)
!403 = !DILocation(line: 103, column: 22, scope: !167)
!404 = !DILocation(line: 108, column: 6, scope: !405)
!405 = distinct !DILexicalBlock(scope: !167, file: !1, line: 108, column: 6)
!406 = !DILocation(line: 108, column: 26, scope: !405)
!407 = !DILocation(line: 108, column: 32, scope: !405)
!408 = !DILocation(line: 108, column: 38, scope: !405)
!409 = !DILocation(line: 108, column: 29, scope: !405)
!410 = !DILocation(line: 108, column: 6, scope: !167)
!411 = !DILocation(line: 109, column: 3, scope: !405)
!412 = !DILocation(line: 111, column: 6, scope: !413)
!413 = distinct !DILexicalBlock(scope: !167, file: !1, line: 111, column: 6)
!414 = !DILocation(line: 111, column: 26, scope: !413)
!415 = !DILocation(line: 111, column: 29, scope: !413)
!416 = !DILocation(line: 111, column: 6, scope: !167)
!417 = !DILocation(line: 112, column: 3, scope: !413)
!418 = !DILocation(line: 114, column: 2, scope: !167)
!419 = !DILocation(line: 114, column: 2, scope: !420)
!420 = !DILexicalBlockFile(scope: !167, file: !1, discriminator: 1)
!421 = !DILocation(line: 114, column: 2, scope: !422)
!422 = !DILexicalBlockFile(scope: !167, file: !1, discriminator: 2)
!423 = !DILocation(line: 114, column: 2, scope: !424)
!424 = !DILexicalBlockFile(scope: !167, file: !1, discriminator: 3)
!425 = !DILocation(line: 115, column: 9, scope: !167)
!426 = !DILocation(line: 115, column: 15, scope: !167)
!427 = !DILocation(line: 115, column: 22, scope: !167)
!428 = !DILocation(line: 115, column: 28, scope: !167)
!429 = !DILocation(line: 115, column: 35, scope: !167)
!430 = !DILocation(line: 115, column: 52, scope: !167)
!431 = !DILocation(line: 115, column: 2, scope: !167)
!432 = !DILocation(line: 116, column: 1, scope: !167)
!433 = !DILocalVariable(name: "strm", arg: 1, scope: !173, file: !1, line: 145, type: !176)
!434 = !DILocation(line: 145, column: 29, scope: !173)
!435 = !DILocation(line: 147, column: 6, scope: !436)
!436 = distinct !DILexicalBlock(scope: !173, file: !1, line: 147, column: 6)
!437 = !DILocation(line: 147, column: 11, scope: !436)
!438 = !DILocation(line: 147, column: 6, scope: !173)
!439 = !DILocation(line: 148, column: 3, scope: !436)
!440 = !DILocation(line: 150, column: 6, scope: !441)
!441 = distinct !DILexicalBlock(scope: !173, file: !1, line: 150, column: 6)
!442 = !DILocation(line: 150, column: 12, scope: !441)
!443 = !DILocation(line: 150, column: 21, scope: !441)
!444 = !DILocation(line: 150, column: 6, scope: !173)
!445 = !DILocation(line: 152, column: 5, scope: !446)
!446 = distinct !DILexicalBlock(scope: !441, file: !1, line: 150, column: 30)
!447 = !DILocation(line: 152, column: 11, scope: !446)
!448 = !DILocation(line: 151, column: 20, scope: !446)
!449 = !DILocation(line: 151, column: 3, scope: !446)
!450 = !DILocation(line: 151, column: 9, scope: !446)
!451 = !DILocation(line: 151, column: 18, scope: !446)
!452 = !DILocation(line: 153, column: 7, scope: !453)
!453 = distinct !DILexicalBlock(scope: !446, file: !1, line: 153, column: 7)
!454 = !DILocation(line: 153, column: 13, scope: !453)
!455 = !DILocation(line: 153, column: 22, scope: !453)
!456 = !DILocation(line: 153, column: 7, scope: !446)
!457 = !DILocation(line: 154, column: 4, scope: !453)
!458 = !DILocation(line: 156, column: 3, scope: !446)
!459 = !DILocation(line: 156, column: 9, scope: !446)
!460 = !DILocation(line: 156, column: 19, scope: !446)
!461 = !DILocation(line: 156, column: 26, scope: !446)
!462 = !DILocation(line: 157, column: 2, scope: !446)
!463 = !DILocation(line: 159, column: 2, scope: !173)
!464 = !DILocation(line: 159, column: 8, scope: !173)
!465 = !DILocation(line: 159, column: 18, scope: !173)
!466 = !DILocation(line: 159, column: 46, scope: !173)
!467 = !DILocation(line: 160, column: 2, scope: !173)
!468 = !DILocation(line: 160, column: 8, scope: !173)
!469 = !DILocation(line: 160, column: 18, scope: !173)
!470 = !DILocation(line: 160, column: 53, scope: !173)
!471 = !DILocation(line: 161, column: 2, scope: !173)
!472 = !DILocation(line: 161, column: 8, scope: !173)
!473 = !DILocation(line: 161, column: 18, scope: !173)
!474 = !DILocation(line: 161, column: 53, scope: !173)
!475 = !DILocation(line: 162, column: 2, scope: !173)
!476 = !DILocation(line: 162, column: 8, scope: !173)
!477 = !DILocation(line: 162, column: 18, scope: !173)
!478 = !DILocation(line: 162, column: 49, scope: !173)
!479 = !DILocation(line: 163, column: 2, scope: !173)
!480 = !DILocation(line: 163, column: 8, scope: !173)
!481 = !DILocation(line: 163, column: 18, scope: !173)
!482 = !DILocation(line: 163, column: 27, scope: !173)
!483 = !DILocation(line: 164, column: 2, scope: !173)
!484 = !DILocation(line: 164, column: 8, scope: !173)
!485 = !DILocation(line: 164, column: 18, scope: !173)
!486 = !DILocation(line: 164, column: 34, scope: !173)
!487 = !DILocation(line: 166, column: 2, scope: !173)
!488 = !DILocation(line: 166, column: 8, scope: !173)
!489 = !DILocation(line: 166, column: 17, scope: !173)
!490 = !DILocation(line: 167, column: 2, scope: !173)
!491 = !DILocation(line: 167, column: 8, scope: !173)
!492 = !DILocation(line: 167, column: 18, scope: !173)
!493 = !DILocation(line: 169, column: 2, scope: !173)
!494 = !DILocation(line: 170, column: 1, scope: !173)
!495 = !DILocalVariable(name: "strm", arg: 1, scope: !201, file: !1, line: 174, type: !176)
!496 = !DILocation(line: 174, column: 24, scope: !201)
!497 = !DILocalVariable(name: "action", arg: 2, scope: !201, file: !1, line: 174, type: !82)
!498 = !DILocation(line: 174, column: 42, scope: !201)
!499 = !DILocalVariable(name: "in_pos", scope: !201, file: !1, line: 176, type: !66)
!500 = !DILocation(line: 176, column: 9, scope: !201)
!501 = !DILocalVariable(name: "out_pos", scope: !201, file: !1, line: 177, type: !66)
!502 = !DILocation(line: 177, column: 9, scope: !201)
!503 = !DILocalVariable(name: "ret", scope: !201, file: !1, line: 178, type: !56)
!504 = !DILocation(line: 178, column: 11, scope: !201)
!505 = !DILocation(line: 181, column: 7, scope: !506)
!506 = distinct !DILexicalBlock(scope: !201, file: !1, line: 181, column: 6)
!507 = !DILocation(line: 181, column: 13, scope: !506)
!508 = !DILocation(line: 181, column: 21, scope: !506)
!509 = !DILocation(line: 181, column: 29, scope: !506)
!510 = !DILocation(line: 181, column: 32, scope: !511)
!511 = !DILexicalBlockFile(scope: !506, file: !1, discriminator: 1)
!512 = !DILocation(line: 181, column: 38, scope: !511)
!513 = !DILocation(line: 181, column: 47, scope: !511)
!514 = !DILocation(line: 182, column: 4, scope: !506)
!515 = !DILocation(line: 182, column: 8, scope: !511)
!516 = !DILocation(line: 182, column: 14, scope: !511)
!517 = !DILocation(line: 182, column: 23, scope: !511)
!518 = !DILocation(line: 182, column: 31, scope: !511)
!519 = !DILocation(line: 182, column: 34, scope: !520)
!520 = !DILexicalBlockFile(scope: !506, file: !1, discriminator: 2)
!521 = !DILocation(line: 182, column: 40, scope: !520)
!522 = !DILocation(line: 182, column: 50, scope: !520)
!523 = !DILocation(line: 183, column: 4, scope: !506)
!524 = !DILocation(line: 183, column: 7, scope: !511)
!525 = !DILocation(line: 183, column: 13, scope: !511)
!526 = !DILocation(line: 183, column: 22, scope: !511)
!527 = !DILocation(line: 184, column: 4, scope: !506)
!528 = !DILocation(line: 184, column: 7, scope: !511)
!529 = !DILocation(line: 184, column: 13, scope: !511)
!530 = !DILocation(line: 184, column: 23, scope: !511)
!531 = !DILocation(line: 184, column: 28, scope: !511)
!532 = !DILocation(line: 184, column: 33, scope: !511)
!533 = !DILocation(line: 185, column: 4, scope: !506)
!534 = !DILocation(line: 185, column: 22, scope: !511)
!535 = !DILocation(line: 185, column: 30, scope: !511)
!536 = !DILocation(line: 186, column: 4, scope: !506)
!537 = !DILocation(line: 186, column: 42, scope: !511)
!538 = !DILocation(line: 186, column: 8, scope: !511)
!539 = !DILocation(line: 186, column: 14, scope: !511)
!540 = !DILocation(line: 186, column: 24, scope: !511)
!541 = !DILocation(line: 181, column: 6, scope: !542)
!542 = !DILexicalBlockFile(scope: !201, file: !1, discriminator: 2)
!543 = !DILocation(line: 187, column: 3, scope: !506)
!544 = !DILocation(line: 191, column: 6, scope: !545)
!545 = distinct !DILexicalBlock(scope: !201, file: !1, line: 191, column: 6)
!546 = !DILocation(line: 191, column: 12, scope: !545)
!547 = !DILocation(line: 191, column: 26, scope: !545)
!548 = !DILocation(line: 192, column: 4, scope: !545)
!549 = !DILocation(line: 192, column: 7, scope: !550)
!550 = !DILexicalBlockFile(scope: !545, file: !1, discriminator: 1)
!551 = !DILocation(line: 192, column: 13, scope: !550)
!552 = !DILocation(line: 192, column: 27, scope: !550)
!553 = !DILocation(line: 193, column: 4, scope: !545)
!554 = !DILocation(line: 193, column: 7, scope: !550)
!555 = !DILocation(line: 193, column: 13, scope: !550)
!556 = !DILocation(line: 193, column: 27, scope: !550)
!557 = !DILocation(line: 194, column: 4, scope: !545)
!558 = !DILocation(line: 194, column: 7, scope: !550)
!559 = !DILocation(line: 194, column: 13, scope: !550)
!560 = !DILocation(line: 194, column: 27, scope: !550)
!561 = !DILocation(line: 195, column: 4, scope: !545)
!562 = !DILocation(line: 195, column: 7, scope: !550)
!563 = !DILocation(line: 195, column: 13, scope: !550)
!564 = !DILocation(line: 195, column: 27, scope: !550)
!565 = !DILocation(line: 196, column: 4, scope: !545)
!566 = !DILocation(line: 196, column: 7, scope: !550)
!567 = !DILocation(line: 196, column: 13, scope: !550)
!568 = !DILocation(line: 196, column: 27, scope: !550)
!569 = !DILocation(line: 197, column: 4, scope: !545)
!570 = !DILocation(line: 197, column: 7, scope: !550)
!571 = !DILocation(line: 197, column: 13, scope: !550)
!572 = !DILocation(line: 197, column: 27, scope: !550)
!573 = !DILocation(line: 198, column: 4, scope: !545)
!574 = !DILocation(line: 198, column: 7, scope: !550)
!575 = !DILocation(line: 198, column: 13, scope: !550)
!576 = !DILocation(line: 198, column: 27, scope: !550)
!577 = !DILocation(line: 199, column: 4, scope: !545)
!578 = !DILocation(line: 199, column: 7, scope: !550)
!579 = !DILocation(line: 199, column: 13, scope: !550)
!580 = !DILocation(line: 199, column: 28, scope: !550)
!581 = !DILocation(line: 200, column: 4, scope: !545)
!582 = !DILocation(line: 200, column: 7, scope: !550)
!583 = !DILocation(line: 200, column: 13, scope: !550)
!584 = !DILocation(line: 200, column: 28, scope: !550)
!585 = !DILocation(line: 191, column: 6, scope: !586)
!586 = !DILexicalBlockFile(scope: !201, file: !1, discriminator: 1)
!587 = !DILocation(line: 201, column: 3, scope: !545)
!588 = !DILocation(line: 203, column: 10, scope: !201)
!589 = !DILocation(line: 203, column: 16, scope: !201)
!590 = !DILocation(line: 203, column: 26, scope: !201)
!591 = !DILocation(line: 203, column: 2, scope: !201)
!592 = !DILocation(line: 205, column: 11, scope: !593)
!593 = distinct !DILexicalBlock(scope: !201, file: !1, line: 203, column: 36)
!594 = !DILocation(line: 205, column: 3, scope: !593)
!595 = !DILocation(line: 207, column: 4, scope: !596)
!596 = distinct !DILexicalBlock(scope: !593, file: !1, line: 205, column: 19)
!597 = !DILocation(line: 210, column: 4, scope: !596)
!598 = !DILocation(line: 210, column: 10, scope: !596)
!599 = !DILocation(line: 210, column: 20, scope: !596)
!600 = !DILocation(line: 210, column: 29, scope: !596)
!601 = !DILocation(line: 211, column: 4, scope: !596)
!602 = !DILocation(line: 214, column: 4, scope: !596)
!603 = !DILocation(line: 214, column: 10, scope: !596)
!604 = !DILocation(line: 214, column: 20, scope: !596)
!605 = !DILocation(line: 214, column: 29, scope: !596)
!606 = !DILocation(line: 215, column: 4, scope: !596)
!607 = !DILocation(line: 218, column: 4, scope: !596)
!608 = !DILocation(line: 218, column: 10, scope: !596)
!609 = !DILocation(line: 218, column: 20, scope: !596)
!610 = !DILocation(line: 218, column: 29, scope: !596)
!611 = !DILocation(line: 219, column: 4, scope: !596)
!612 = !DILocation(line: 222, column: 3, scope: !593)
!613 = !DILocation(line: 227, column: 7, scope: !614)
!614 = distinct !DILexicalBlock(scope: !593, file: !1, line: 227, column: 7)
!615 = !DILocation(line: 227, column: 14, scope: !614)
!616 = !DILocation(line: 228, column: 5, scope: !614)
!617 = !DILocation(line: 228, column: 8, scope: !618)
!618 = !DILexicalBlockFile(scope: !614, file: !1, discriminator: 1)
!619 = !DILocation(line: 228, column: 14, scope: !618)
!620 = !DILocation(line: 228, column: 24, scope: !618)
!621 = !DILocation(line: 228, column: 36, scope: !618)
!622 = !DILocation(line: 228, column: 42, scope: !618)
!623 = !DILocation(line: 228, column: 33, scope: !618)
!624 = !DILocation(line: 227, column: 7, scope: !625)
!625 = !DILexicalBlockFile(scope: !593, file: !1, discriminator: 1)
!626 = !DILocation(line: 229, column: 4, scope: !614)
!627 = !DILocation(line: 231, column: 3, scope: !593)
!628 = !DILocation(line: 234, column: 7, scope: !629)
!629 = distinct !DILexicalBlock(scope: !593, file: !1, line: 234, column: 7)
!630 = !DILocation(line: 234, column: 14, scope: !629)
!631 = !DILocation(line: 235, column: 5, scope: !629)
!632 = !DILocation(line: 235, column: 8, scope: !633)
!633 = !DILexicalBlockFile(scope: !629, file: !1, discriminator: 1)
!634 = !DILocation(line: 235, column: 14, scope: !633)
!635 = !DILocation(line: 235, column: 24, scope: !633)
!636 = !DILocation(line: 235, column: 36, scope: !633)
!637 = !DILocation(line: 235, column: 42, scope: !633)
!638 = !DILocation(line: 235, column: 33, scope: !633)
!639 = !DILocation(line: 234, column: 7, scope: !625)
!640 = !DILocation(line: 236, column: 4, scope: !629)
!641 = !DILocation(line: 238, column: 3, scope: !593)
!642 = !DILocation(line: 241, column: 7, scope: !643)
!643 = distinct !DILexicalBlock(scope: !593, file: !1, line: 241, column: 7)
!644 = !DILocation(line: 241, column: 14, scope: !643)
!645 = !DILocation(line: 242, column: 5, scope: !643)
!646 = !DILocation(line: 242, column: 8, scope: !647)
!647 = !DILexicalBlockFile(scope: !643, file: !1, discriminator: 1)
!648 = !DILocation(line: 242, column: 14, scope: !647)
!649 = !DILocation(line: 242, column: 24, scope: !647)
!650 = !DILocation(line: 242, column: 36, scope: !647)
!651 = !DILocation(line: 242, column: 42, scope: !647)
!652 = !DILocation(line: 242, column: 33, scope: !647)
!653 = !DILocation(line: 241, column: 7, scope: !625)
!654 = !DILocation(line: 243, column: 4, scope: !643)
!655 = !DILocation(line: 245, column: 3, scope: !593)
!656 = !DILocation(line: 248, column: 3, scope: !593)
!657 = !DILocation(line: 248, column: 3, scope: !625)
!658 = !DILocation(line: 252, column: 3, scope: !593)
!659 = !DILocation(line: 255, column: 8, scope: !201)
!660 = !DILocation(line: 255, column: 14, scope: !201)
!661 = !DILocation(line: 255, column: 24, scope: !201)
!662 = !DILocation(line: 255, column: 29, scope: !201)
!663 = !DILocation(line: 256, column: 4, scope: !201)
!664 = !DILocation(line: 256, column: 10, scope: !201)
!665 = !DILocation(line: 256, column: 20, scope: !201)
!666 = !DILocation(line: 256, column: 25, scope: !201)
!667 = !DILocation(line: 256, column: 32, scope: !201)
!668 = !DILocation(line: 256, column: 38, scope: !201)
!669 = !DILocation(line: 257, column: 4, scope: !201)
!670 = !DILocation(line: 257, column: 10, scope: !201)
!671 = !DILocation(line: 257, column: 28, scope: !201)
!672 = !DILocation(line: 257, column: 34, scope: !201)
!673 = !DILocation(line: 258, column: 4, scope: !201)
!674 = !DILocation(line: 258, column: 10, scope: !201)
!675 = !DILocation(line: 258, column: 30, scope: !201)
!676 = !DILocation(line: 258, column: 36, scope: !201)
!677 = !DILocation(line: 258, column: 47, scope: !201)
!678 = !DILocation(line: 255, column: 6, scope: !201)
!679 = !DILocation(line: 260, column: 19, scope: !201)
!680 = !DILocation(line: 260, column: 2, scope: !201)
!681 = !DILocation(line: 260, column: 8, scope: !201)
!682 = !DILocation(line: 260, column: 16, scope: !201)
!683 = !DILocation(line: 261, column: 20, scope: !201)
!684 = !DILocation(line: 261, column: 2, scope: !201)
!685 = !DILocation(line: 261, column: 8, scope: !201)
!686 = !DILocation(line: 261, column: 17, scope: !201)
!687 = !DILocation(line: 262, column: 20, scope: !201)
!688 = !DILocation(line: 262, column: 2, scope: !201)
!689 = !DILocation(line: 262, column: 8, scope: !201)
!690 = !DILocation(line: 262, column: 17, scope: !201)
!691 = !DILocation(line: 264, column: 20, scope: !201)
!692 = !DILocation(line: 264, column: 2, scope: !201)
!693 = !DILocation(line: 264, column: 8, scope: !201)
!694 = !DILocation(line: 264, column: 17, scope: !201)
!695 = !DILocation(line: 265, column: 21, scope: !201)
!696 = !DILocation(line: 265, column: 2, scope: !201)
!697 = !DILocation(line: 265, column: 8, scope: !201)
!698 = !DILocation(line: 265, column: 18, scope: !201)
!699 = !DILocation(line: 266, column: 21, scope: !201)
!700 = !DILocation(line: 266, column: 2, scope: !201)
!701 = !DILocation(line: 266, column: 8, scope: !201)
!702 = !DILocation(line: 266, column: 18, scope: !201)
!703 = !DILocation(line: 268, column: 29, scope: !201)
!704 = !DILocation(line: 268, column: 35, scope: !201)
!705 = !DILocation(line: 268, column: 2, scope: !201)
!706 = !DILocation(line: 268, column: 8, scope: !201)
!707 = !DILocation(line: 268, column: 18, scope: !201)
!708 = !DILocation(line: 268, column: 27, scope: !201)
!709 = !DILocation(line: 270, column: 10, scope: !201)
!710 = !DILocation(line: 270, column: 2, scope: !201)
!711 = !DILocation(line: 276, column: 7, scope: !712)
!712 = distinct !DILexicalBlock(scope: !713, file: !1, line: 276, column: 7)
!713 = distinct !DILexicalBlock(scope: !201, file: !1, line: 270, column: 15)
!714 = !DILocation(line: 276, column: 15, scope: !712)
!715 = !DILocation(line: 276, column: 20, scope: !712)
!716 = !DILocation(line: 276, column: 23, scope: !717)
!717 = !DILexicalBlockFile(scope: !712, file: !1, discriminator: 1)
!718 = !DILocation(line: 276, column: 30, scope: !717)
!719 = !DILocation(line: 276, column: 7, scope: !717)
!720 = !DILocation(line: 277, column: 8, scope: !721)
!721 = distinct !DILexicalBlock(scope: !722, file: !1, line: 277, column: 8)
!722 = distinct !DILexicalBlock(scope: !712, file: !1, line: 276, column: 36)
!723 = !DILocation(line: 277, column: 14, scope: !721)
!724 = !DILocation(line: 277, column: 24, scope: !721)
!725 = !DILocation(line: 277, column: 8, scope: !722)
!726 = !DILocation(line: 278, column: 9, scope: !721)
!727 = !DILocation(line: 278, column: 5, scope: !721)
!728 = !DILocation(line: 280, column: 5, scope: !721)
!729 = !DILocation(line: 280, column: 11, scope: !721)
!730 = !DILocation(line: 280, column: 21, scope: !721)
!731 = !DILocation(line: 280, column: 37, scope: !721)
!732 = !DILocation(line: 281, column: 3, scope: !722)
!733 = !DILocation(line: 282, column: 4, scope: !734)
!734 = distinct !DILexicalBlock(scope: !712, file: !1, line: 281, column: 10)
!735 = !DILocation(line: 282, column: 10, scope: !734)
!736 = !DILocation(line: 282, column: 20, scope: !734)
!737 = !DILocation(line: 282, column: 36, scope: !734)
!738 = !DILocation(line: 284, column: 3, scope: !713)
!739 = !DILocation(line: 287, column: 7, scope: !740)
!740 = distinct !DILexicalBlock(scope: !713, file: !1, line: 287, column: 7)
!741 = !DILocation(line: 287, column: 13, scope: !740)
!742 = !DILocation(line: 287, column: 23, scope: !740)
!743 = !DILocation(line: 287, column: 32, scope: !740)
!744 = !DILocation(line: 288, column: 5, scope: !740)
!745 = !DILocation(line: 288, column: 8, scope: !746)
!746 = !DILexicalBlockFile(scope: !740, file: !1, discriminator: 1)
!747 = !DILocation(line: 288, column: 14, scope: !746)
!748 = !DILocation(line: 288, column: 24, scope: !746)
!749 = !DILocation(line: 288, column: 33, scope: !746)
!750 = !DILocation(line: 287, column: 7, scope: !751)
!751 = !DILexicalBlockFile(scope: !713, file: !1, discriminator: 1)
!752 = !DILocation(line: 289, column: 4, scope: !740)
!753 = !DILocation(line: 289, column: 10, scope: !740)
!754 = !DILocation(line: 289, column: 20, scope: !740)
!755 = !DILocation(line: 289, column: 29, scope: !740)
!756 = !DILocation(line: 291, column: 4, scope: !740)
!757 = !DILocation(line: 291, column: 10, scope: !740)
!758 = !DILocation(line: 291, column: 20, scope: !740)
!759 = !DILocation(line: 291, column: 29, scope: !740)
!760 = !DILocation(line: 288, column: 36, scope: !761)
!761 = !DILexicalBlockFile(scope: !740, file: !1, discriminator: 2)
!762 = !DILocation(line: 301, column: 3, scope: !713)
!763 = !DILocation(line: 301, column: 9, scope: !713)
!764 = !DILocation(line: 301, column: 19, scope: !713)
!765 = !DILocation(line: 301, column: 35, scope: !713)
!766 = !DILocation(line: 302, column: 3, scope: !713)
!767 = !DILocation(line: 306, column: 3, scope: !713)
!768 = !DILocation(line: 306, column: 3, scope: !751)
!769 = !DILocation(line: 306, column: 3, scope: !770)
!770 = !DILexicalBlockFile(scope: !713, file: !1, discriminator: 2)
!771 = !DILocation(line: 306, column: 3, scope: !772)
!772 = !DILexicalBlockFile(scope: !713, file: !1, discriminator: 3)
!773 = !DILocation(line: 307, column: 3, scope: !713)
!774 = !DILocation(line: 307, column: 9, scope: !713)
!775 = !DILocation(line: 307, column: 19, scope: !713)
!776 = !DILocation(line: 307, column: 28, scope: !713)
!777 = !DILocation(line: 308, column: 3, scope: !713)
!778 = !DILocation(line: 311, column: 9, scope: !201)
!779 = !DILocation(line: 311, column: 2, scope: !201)
!780 = !DILocation(line: 312, column: 1, scope: !201)
!781 = !DILocalVariable(name: "strm", arg: 1, scope: !204, file: !1, line: 316, type: !176)
!782 = !DILocation(line: 316, column: 23, scope: !204)
!783 = !DILocation(line: 318, column: 6, scope: !784)
!784 = distinct !DILexicalBlock(scope: !204, file: !1, line: 318, column: 6)
!785 = !DILocation(line: 318, column: 11, scope: !784)
!786 = !DILocation(line: 318, column: 19, scope: !784)
!787 = !DILocation(line: 318, column: 22, scope: !788)
!788 = !DILexicalBlockFile(scope: !784, file: !1, discriminator: 1)
!789 = !DILocation(line: 318, column: 28, scope: !788)
!790 = !DILocation(line: 318, column: 37, scope: !788)
!791 = !DILocation(line: 318, column: 6, scope: !788)
!792 = !DILocation(line: 319, column: 18, scope: !793)
!793 = distinct !DILexicalBlock(scope: !784, file: !1, line: 318, column: 46)
!794 = !DILocation(line: 319, column: 24, scope: !793)
!795 = !DILocation(line: 319, column: 34, scope: !793)
!796 = !DILocation(line: 319, column: 40, scope: !793)
!797 = !DILocation(line: 319, column: 46, scope: !793)
!798 = !DILocation(line: 319, column: 3, scope: !793)
!799 = !DILocation(line: 320, column: 13, scope: !793)
!800 = !DILocation(line: 320, column: 19, scope: !793)
!801 = !DILocation(line: 320, column: 29, scope: !793)
!802 = !DILocation(line: 320, column: 35, scope: !793)
!803 = !DILocation(line: 320, column: 3, scope: !793)
!804 = !DILocation(line: 321, column: 3, scope: !793)
!805 = !DILocation(line: 321, column: 9, scope: !793)
!806 = !DILocation(line: 321, column: 18, scope: !793)
!807 = !DILocation(line: 322, column: 2, scope: !793)
!808 = !DILocation(line: 324, column: 2, scope: !204)
!809 = !DILocalVariable(name: "strm", arg: 1, scope: !207, file: !1, line: 329, type: !210)
!810 = !DILocation(line: 329, column: 35, scope: !207)
!811 = !DILocation(line: 333, column: 6, scope: !812)
!812 = distinct !DILexicalBlock(scope: !207, file: !1, line: 333, column: 6)
!813 = !DILocation(line: 333, column: 12, scope: !812)
!814 = !DILocation(line: 333, column: 22, scope: !812)
!815 = !DILocation(line: 333, column: 27, scope: !812)
!816 = !DILocation(line: 333, column: 37, scope: !812)
!817 = !DILocation(line: 333, column: 6, scope: !207)
!818 = !DILocation(line: 334, column: 3, scope: !812)
!819 = !DILocation(line: 336, column: 9, scope: !207)
!820 = !DILocation(line: 336, column: 15, scope: !207)
!821 = !DILocation(line: 336, column: 25, scope: !207)
!822 = !DILocation(line: 336, column: 30, scope: !207)
!823 = !DILocation(line: 336, column: 40, scope: !207)
!824 = !DILocation(line: 336, column: 46, scope: !207)
!825 = !DILocation(line: 336, column: 56, scope: !207)
!826 = !DILocation(line: 336, column: 61, scope: !207)
!827 = !DILocation(line: 336, column: 2, scope: !207)
!828 = !DILocation(line: 337, column: 1, scope: !207)
!829 = !DILocalVariable(name: "strm", arg: 1, scope: !212, file: !1, line: 341, type: !210)
!830 = !DILocation(line: 341, column: 34, scope: !212)
!831 = !DILocalVariable(name: "memusage", scope: !212, file: !1, line: 343, type: !46)
!832 = !DILocation(line: 343, column: 11, scope: !212)
!833 = !DILocalVariable(name: "old_memlimit", scope: !212, file: !1, line: 344, type: !46)
!834 = !DILocation(line: 344, column: 11, scope: !212)
!835 = !DILocation(line: 346, column: 6, scope: !836)
!836 = distinct !DILexicalBlock(scope: !212, file: !1, line: 346, column: 6)
!837 = !DILocation(line: 346, column: 11, scope: !836)
!838 = !DILocation(line: 346, column: 19, scope: !836)
!839 = !DILocation(line: 346, column: 22, scope: !840)
!840 = !DILexicalBlockFile(scope: !836, file: !1, discriminator: 1)
!841 = !DILocation(line: 346, column: 28, scope: !840)
!842 = !DILocation(line: 346, column: 37, scope: !840)
!843 = !DILocation(line: 347, column: 4, scope: !836)
!844 = !DILocation(line: 347, column: 7, scope: !840)
!845 = !DILocation(line: 347, column: 13, scope: !840)
!846 = !DILocation(line: 347, column: 23, scope: !840)
!847 = !DILocation(line: 347, column: 28, scope: !840)
!848 = !DILocation(line: 347, column: 38, scope: !840)
!849 = !DILocation(line: 348, column: 4, scope: !836)
!850 = !DILocation(line: 348, column: 7, scope: !840)
!851 = !DILocation(line: 348, column: 13, scope: !840)
!852 = !DILocation(line: 348, column: 23, scope: !840)
!853 = !DILocation(line: 348, column: 28, scope: !840)
!854 = !DILocation(line: 349, column: 5, scope: !836)
!855 = !DILocation(line: 349, column: 11, scope: !836)
!856 = !DILocation(line: 349, column: 21, scope: !836)
!857 = !DILocation(line: 349, column: 26, scope: !836)
!858 = !DILocation(line: 350, column: 34, scope: !836)
!859 = !DILocation(line: 346, column: 6, scope: !860)
!860 = !DILexicalBlockFile(scope: !212, file: !1, discriminator: 2)
!861 = !DILocation(line: 351, column: 3, scope: !836)
!862 = !DILocation(line: 353, column: 9, scope: !212)
!863 = !DILocation(line: 353, column: 2, scope: !212)
!864 = !DILocation(line: 354, column: 1, scope: !212)
!865 = !DILocalVariable(name: "strm", arg: 1, scope: !215, file: !1, line: 358, type: !210)
!866 = !DILocation(line: 358, column: 38, scope: !215)
!867 = !DILocalVariable(name: "old_memlimit", scope: !215, file: !1, line: 360, type: !46)
!868 = !DILocation(line: 360, column: 11, scope: !215)
!869 = !DILocalVariable(name: "memusage", scope: !215, file: !1, line: 361, type: !46)
!870 = !DILocation(line: 361, column: 11, scope: !215)
!871 = !DILocation(line: 363, column: 6, scope: !872)
!872 = distinct !DILexicalBlock(scope: !215, file: !1, line: 363, column: 6)
!873 = !DILocation(line: 363, column: 11, scope: !872)
!874 = !DILocation(line: 363, column: 19, scope: !872)
!875 = !DILocation(line: 363, column: 22, scope: !876)
!876 = !DILexicalBlockFile(scope: !872, file: !1, discriminator: 1)
!877 = !DILocation(line: 363, column: 28, scope: !876)
!878 = !DILocation(line: 363, column: 37, scope: !876)
!879 = !DILocation(line: 364, column: 4, scope: !872)
!880 = !DILocation(line: 364, column: 7, scope: !876)
!881 = !DILocation(line: 364, column: 13, scope: !876)
!882 = !DILocation(line: 364, column: 23, scope: !876)
!883 = !DILocation(line: 364, column: 28, scope: !876)
!884 = !DILocation(line: 364, column: 38, scope: !876)
!885 = !DILocation(line: 365, column: 4, scope: !872)
!886 = !DILocation(line: 365, column: 7, scope: !876)
!887 = !DILocation(line: 365, column: 13, scope: !876)
!888 = !DILocation(line: 365, column: 23, scope: !876)
!889 = !DILocation(line: 365, column: 28, scope: !876)
!890 = !DILocation(line: 366, column: 5, scope: !872)
!891 = !DILocation(line: 366, column: 11, scope: !872)
!892 = !DILocation(line: 366, column: 21, scope: !872)
!893 = !DILocation(line: 366, column: 26, scope: !872)
!894 = !DILocation(line: 367, column: 34, scope: !872)
!895 = !DILocation(line: 363, column: 6, scope: !896)
!896 = !DILexicalBlockFile(scope: !215, file: !1, discriminator: 2)
!897 = !DILocation(line: 368, column: 3, scope: !872)
!898 = !DILocation(line: 370, column: 9, scope: !215)
!899 = !DILocation(line: 370, column: 2, scope: !215)
!900 = !DILocation(line: 371, column: 1, scope: !215)
!901 = !DILocalVariable(name: "strm", arg: 1, scope: !216, file: !1, line: 375, type: !176)
!902 = !DILocation(line: 375, column: 32, scope: !216)
!903 = !DILocalVariable(name: "new_memlimit", arg: 2, scope: !216, file: !1, line: 375, type: !46)
!904 = !DILocation(line: 375, column: 47, scope: !216)
!905 = !DILocalVariable(name: "old_memlimit", scope: !216, file: !1, line: 378, type: !46)
!906 = !DILocation(line: 378, column: 11, scope: !216)
!907 = !DILocalVariable(name: "memusage", scope: !216, file: !1, line: 379, type: !46)
!908 = !DILocation(line: 379, column: 11, scope: !216)
!909 = !DILocation(line: 381, column: 6, scope: !910)
!910 = distinct !DILexicalBlock(scope: !216, file: !1, line: 381, column: 6)
!911 = !DILocation(line: 381, column: 11, scope: !910)
!912 = !DILocation(line: 381, column: 19, scope: !910)
!913 = !DILocation(line: 381, column: 22, scope: !914)
!914 = !DILexicalBlockFile(scope: !910, file: !1, discriminator: 1)
!915 = !DILocation(line: 381, column: 28, scope: !914)
!916 = !DILocation(line: 381, column: 37, scope: !914)
!917 = !DILocation(line: 382, column: 4, scope: !910)
!918 = !DILocation(line: 382, column: 7, scope: !914)
!919 = !DILocation(line: 382, column: 13, scope: !914)
!920 = !DILocation(line: 382, column: 23, scope: !914)
!921 = !DILocation(line: 382, column: 28, scope: !914)
!922 = !DILocation(line: 382, column: 38, scope: !914)
!923 = !DILocation(line: 381, column: 6, scope: !924)
!924 = !DILexicalBlockFile(scope: !216, file: !1, discriminator: 2)
!925 = !DILocation(line: 383, column: 3, scope: !910)
!926 = !DILocation(line: 385, column: 6, scope: !927)
!927 = distinct !DILexicalBlock(scope: !216, file: !1, line: 385, column: 6)
!928 = !DILocation(line: 385, column: 19, scope: !927)
!929 = !DILocation(line: 385, column: 24, scope: !927)
!930 = !DILocation(line: 385, column: 27, scope: !931)
!931 = !DILexicalBlockFile(scope: !927, file: !1, discriminator: 1)
!932 = !DILocation(line: 385, column: 40, scope: !931)
!933 = !DILocation(line: 385, column: 6, scope: !931)
!934 = !DILocation(line: 386, column: 3, scope: !927)
!935 = !DILocation(line: 388, column: 9, scope: !216)
!936 = !DILocation(line: 388, column: 15, scope: !216)
!937 = !DILocation(line: 388, column: 25, scope: !216)
!938 = !DILocation(line: 388, column: 30, scope: !216)
!939 = !DILocation(line: 388, column: 40, scope: !216)
!940 = !DILocation(line: 388, column: 46, scope: !216)
!941 = !DILocation(line: 388, column: 56, scope: !216)
!942 = !DILocation(line: 388, column: 61, scope: !216)
!943 = !DILocation(line: 389, column: 30, scope: !216)
!944 = !DILocation(line: 388, column: 2, scope: !216)
!945 = !DILocation(line: 390, column: 1, scope: !216)
