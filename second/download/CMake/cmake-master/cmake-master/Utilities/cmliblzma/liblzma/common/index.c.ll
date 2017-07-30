; ModuleID = '/data/download/cmake/cmake-master/Utilities/cmliblzma/liblzma/common/index.c'
target datalayout = "e-m:e-i64:64-f80:128-n8:16:32:64-S128"
target triple = "x86_64-unknown-linux-gnu"

%struct.lzma_index_s = type { %struct.index_tree, i64, i64, i64, i64, i64, i32 }
%struct.index_tree = type { %struct.index_tree_node_s*, %struct.index_tree_node_s*, %struct.index_tree_node_s*, i32 }
%struct.index_tree_node_s = type { i64, i64, %struct.index_tree_node_s*, %struct.index_tree_node_s*, %struct.index_tree_node_s* }
%struct.lzma_allocator = type { i8* (i8*, i64, i64)*, void (i8*, i8*)*, i8* }
%struct.index_stream = type { %struct.index_tree_node_s, i32, i64, %struct.index_tree, i64, i64, %struct.lzma_stream_flags, i64 }
%struct.lzma_stream_flags = type { i32, i64, i32, i32, i32, i32, i32, i8, i8, i8, i8, i8, i8, i8, i8, i32, i32 }
%struct.index_group = type { %struct.index_tree_node_s, i64, i64, i64, [0 x %struct.index_record] }
%struct.index_record = type { i64, i64 }
%struct.index_cat_info = type { i64, i64, i64, i32, %struct.index_tree* }
%struct.lzma_index_iter = type { %struct.anon, %struct.anon.0, [6 x %union.anon] }
%struct.anon = type { %struct.lzma_stream_flags*, i8*, i8*, i8*, i64, i64, i64, i64, i64, i64, i64, i64, i64, i64, i64 }
%struct.anon.0 = type { i64, i64, i64, i64, i64, i64, i64, i64, i64, i64, i64, i64, i64, i8*, i8*, i8*, i8* }
%union.anon = type { i8* }

@.str = private unnamed_addr constant [27 x i8] c"g->node.left == ((void*)0)\00", align 1
@.str.1 = private unnamed_addr constant [77 x i8] c"/data/download/cmake/cmake-master/Utilities/cmliblzma/liblzma/common/index.c\00", align 1
@__PRETTY_FUNCTION__.lzma_index_cat = private unnamed_addr constant [86 x i8] c"lzma_ret lzma_index_cat(lzma_index *restrict, lzma_index *restrict, lzma_allocator *)\00", align 1
@.str.2 = private unnamed_addr constant [28 x i8] c"g->node.right == ((void*)0)\00", align 1
@.str.3 = private unnamed_addr constant [34 x i8] c"g->node.parent->right == &g->node\00", align 1
@.str.4 = private unnamed_addr constant [27 x i8] c"s->groups.root == &g->node\00", align 1
@.str.5 = private unnamed_addr constant [21 x i8] c"stream != ((void*)0)\00", align 1
@__PRETTY_FUNCTION__.lzma_index_iter_locate = private unnamed_addr constant [62 x i8] c"lzma_bool lzma_index_iter_locate(lzma_index_iter *, lzma_vli)\00", align 1
@.str.6 = private unnamed_addr constant [20 x i8] c"group != ((void*)0)\00", align 1
@.str.7 = private unnamed_addr constant [62 x i8] c"tree->rightmost->uncompressed_base <= node->uncompressed_base\00", align 1
@__PRETTY_FUNCTION__.index_tree_append = private unnamed_addr constant [56 x i8] c"void index_tree_append(index_tree *, index_tree_node *)\00", align 1
@.str.8 = private unnamed_addr constant [57 x i8] c"tree->rightmost->compressed_base < node->compressed_base\00", align 1
@.str.9 = private unnamed_addr constant [28 x i8] c"node->parent->right == node\00", align 1
@.str.10 = private unnamed_addr constant [38 x i8] c"vli <= ((18446744073709551615UL) / 2)\00", align 1
@.str.11 = private unnamed_addr constant [77 x i8] c"/data/download/cmake/cmake-master/Utilities/cmliblzma/liblzma/common/index.h\00", align 1
@__PRETTY_FUNCTION__.vli_ceil4 = private unnamed_addr constant [29 x i8] c"lzma_vli vli_ceil4(lzma_vli)\00", align 1
@.str.12 = private unnamed_addr constant [22 x i8] c"i == destg->allocated\00", align 1
@__PRETTY_FUNCTION__.index_dup_stream = private unnamed_addr constant [71 x i8] c"index_stream *index_dup_stream(const index_stream *, lzma_allocator *)\00", align 1
@.str.13 = private unnamed_addr constant [34 x i8] c"stream->groups.root == ((void*)0)\00", align 1
@__PRETTY_FUNCTION__.iter_set_info = private unnamed_addr constant [38 x i8] c"void iter_set_info(lzma_index_iter *)\00", align 1
@.str.14 = private unnamed_addr constant [36 x i8] c"stream->groups.root != &group->node\00", align 1
@.str.15 = private unnamed_addr constant [42 x i8] c"group->node.parent->right == &group->node\00", align 1
@.str.16 = private unnamed_addr constant [36 x i8] c"stream->groups.root == &group->node\00", align 1
@.str.17 = private unnamed_addr constant [33 x i8] c"group->node.parent == ((void*)0)\00", align 1
@.str.18 = private unnamed_addr constant [71 x i8] c"tree->leftmost == ((void*)0) || tree->leftmost->uncompressed_base == 0\00", align 1
@__PRETTY_FUNCTION__.index_tree_locate = private unnamed_addr constant [54 x i8] c"void *index_tree_locate(const index_tree *, lzma_vli)\00", align 1

; Function Attrs: nounwind uwtable
define %struct.lzma_index_s* @lzma_index_init(%struct.lzma_allocator* %allocator) #0 !dbg !133 {
entry:
  %retval = alloca %struct.lzma_index_s*, align 8
  %allocator.addr = alloca %struct.lzma_allocator*, align 8
  %s = alloca %struct.index_stream*, align 8
  %i = alloca %struct.lzma_index_s*, align 8
  store %struct.lzma_allocator* %allocator, %struct.lzma_allocator** %allocator.addr, align 8
  call void @llvm.dbg.declare(metadata %struct.lzma_allocator** %allocator.addr, metadata !340, metadata !341), !dbg !342
  call void @llvm.dbg.declare(metadata %struct.index_stream** %s, metadata !343, metadata !341), !dbg !344
  call void @llvm.dbg.declare(metadata %struct.lzma_index_s** %i, metadata !345, metadata !341), !dbg !346
  %0 = load %struct.lzma_allocator*, %struct.lzma_allocator** %allocator.addr, align 8, !dbg !347
  %call = call %struct.lzma_index_s* @index_init_plain(%struct.lzma_allocator* %0), !dbg !348
  store %struct.lzma_index_s* %call, %struct.lzma_index_s** %i, align 8, !dbg !346
  %1 = load %struct.lzma_index_s*, %struct.lzma_index_s** %i, align 8, !dbg !349
  %cmp = icmp eq %struct.lzma_index_s* %1, null, !dbg !351
  br i1 %cmp, label %if.then, label %if.end, !dbg !352

if.then:                                          ; preds = %entry
  store %struct.lzma_index_s* null, %struct.lzma_index_s** %retval, align 8, !dbg !353
  br label %return, !dbg !353

if.end:                                           ; preds = %entry
  %2 = load %struct.lzma_allocator*, %struct.lzma_allocator** %allocator.addr, align 8, !dbg !354
  %call1 = call %struct.index_stream* @index_stream_init(i64 0, i64 0, i64 1, i64 0, %struct.lzma_allocator* %2), !dbg !355
  store %struct.index_stream* %call1, %struct.index_stream** %s, align 8, !dbg !356
  %3 = load %struct.index_stream*, %struct.index_stream** %s, align 8, !dbg !357
  %cmp2 = icmp eq %struct.index_stream* %3, null, !dbg !359
  br i1 %cmp2, label %if.then3, label %if.end4, !dbg !360

if.then3:                                         ; preds = %if.end
  %4 = load %struct.lzma_index_s*, %struct.lzma_index_s** %i, align 8, !dbg !361
  %5 = bitcast %struct.lzma_index_s* %4 to i8*, !dbg !361
  %6 = load %struct.lzma_allocator*, %struct.lzma_allocator** %allocator.addr, align 8, !dbg !363
  call void @lzma_free(i8* %5, %struct.lzma_allocator* %6), !dbg !364
  store %struct.lzma_index_s* null, %struct.lzma_index_s** %retval, align 8, !dbg !365
  br label %return, !dbg !365

if.end4:                                          ; preds = %if.end
  %7 = load %struct.lzma_index_s*, %struct.lzma_index_s** %i, align 8, !dbg !366
  %streams = getelementptr inbounds %struct.lzma_index_s, %struct.lzma_index_s* %7, i32 0, i32 0, !dbg !367
  %8 = load %struct.index_stream*, %struct.index_stream** %s, align 8, !dbg !368
  %node = getelementptr inbounds %struct.index_stream, %struct.index_stream* %8, i32 0, i32 0, !dbg !369
  call void @index_tree_append(%struct.index_tree* %streams, %struct.index_tree_node_s* %node), !dbg !370
  %9 = load %struct.lzma_index_s*, %struct.lzma_index_s** %i, align 8, !dbg !371
  store %struct.lzma_index_s* %9, %struct.lzma_index_s** %retval, align 8, !dbg !372
  br label %return, !dbg !372

return:                                           ; preds = %if.end4, %if.then3, %if.then
  %10 = load %struct.lzma_index_s*, %struct.lzma_index_s** %retval, align 8, !dbg !373
  ret %struct.lzma_index_s* %10, !dbg !373
}

; Function Attrs: nounwind readnone
declare void @llvm.dbg.declare(metadata, metadata, metadata) #1

; Function Attrs: nounwind uwtable
define internal %struct.lzma_index_s* @index_init_plain(%struct.lzma_allocator* %allocator) #0 !dbg !273 {
entry:
  %allocator.addr = alloca %struct.lzma_allocator*, align 8
  %i = alloca %struct.lzma_index_s*, align 8
  store %struct.lzma_allocator* %allocator, %struct.lzma_allocator** %allocator.addr, align 8
  call void @llvm.dbg.declare(metadata %struct.lzma_allocator** %allocator.addr, metadata !374, metadata !341), !dbg !375
  call void @llvm.dbg.declare(metadata %struct.lzma_index_s** %i, metadata !376, metadata !341), !dbg !377
  %0 = load %struct.lzma_allocator*, %struct.lzma_allocator** %allocator.addr, align 8, !dbg !378
  %call = call noalias i8* @lzma_alloc(i64 80, %struct.lzma_allocator* %0), !dbg !379
  %1 = bitcast i8* %call to %struct.lzma_index_s*, !dbg !379
  store %struct.lzma_index_s* %1, %struct.lzma_index_s** %i, align 8, !dbg !377
  %2 = load %struct.lzma_index_s*, %struct.lzma_index_s** %i, align 8, !dbg !380
  %cmp = icmp ne %struct.lzma_index_s* %2, null, !dbg !382
  br i1 %cmp, label %if.then, label %if.end, !dbg !383

if.then:                                          ; preds = %entry
  %3 = load %struct.lzma_index_s*, %struct.lzma_index_s** %i, align 8, !dbg !384
  %streams = getelementptr inbounds %struct.lzma_index_s, %struct.lzma_index_s* %3, i32 0, i32 0, !dbg !386
  call void @index_tree_init(%struct.index_tree* %streams), !dbg !387
  %4 = load %struct.lzma_index_s*, %struct.lzma_index_s** %i, align 8, !dbg !388
  %uncompressed_size = getelementptr inbounds %struct.lzma_index_s, %struct.lzma_index_s* %4, i32 0, i32 1, !dbg !389
  store i64 0, i64* %uncompressed_size, align 8, !dbg !390
  %5 = load %struct.lzma_index_s*, %struct.lzma_index_s** %i, align 8, !dbg !391
  %total_size = getelementptr inbounds %struct.lzma_index_s, %struct.lzma_index_s* %5, i32 0, i32 2, !dbg !392
  store i64 0, i64* %total_size, align 8, !dbg !393
  %6 = load %struct.lzma_index_s*, %struct.lzma_index_s** %i, align 8, !dbg !394
  %record_count = getelementptr inbounds %struct.lzma_index_s, %struct.lzma_index_s* %6, i32 0, i32 3, !dbg !395
  store i64 0, i64* %record_count, align 8, !dbg !396
  %7 = load %struct.lzma_index_s*, %struct.lzma_index_s** %i, align 8, !dbg !397
  %index_list_size = getelementptr inbounds %struct.lzma_index_s, %struct.lzma_index_s* %7, i32 0, i32 4, !dbg !398
  store i64 0, i64* %index_list_size, align 8, !dbg !399
  %8 = load %struct.lzma_index_s*, %struct.lzma_index_s** %i, align 8, !dbg !400
  %prealloc = getelementptr inbounds %struct.lzma_index_s, %struct.lzma_index_s* %8, i32 0, i32 5, !dbg !401
  store i64 512, i64* %prealloc, align 8, !dbg !402
  %9 = load %struct.lzma_index_s*, %struct.lzma_index_s** %i, align 8, !dbg !403
  %checks = getelementptr inbounds %struct.lzma_index_s, %struct.lzma_index_s* %9, i32 0, i32 6, !dbg !404
  store i32 0, i32* %checks, align 8, !dbg !405
  br label %if.end, !dbg !406

if.end:                                           ; preds = %if.then, %entry
  %10 = load %struct.lzma_index_s*, %struct.lzma_index_s** %i, align 8, !dbg !407
  ret %struct.lzma_index_s* %10, !dbg !408
}

; Function Attrs: nounwind uwtable
define internal %struct.index_stream* @index_stream_init(i64 %compressed_base, i64 %uncompressed_base, i64 %stream_number, i64 %block_number_base, %struct.lzma_allocator* %allocator) #0 !dbg !278 {
entry:
  %retval = alloca %struct.index_stream*, align 8
  %compressed_base.addr = alloca i64, align 8
  %uncompressed_base.addr = alloca i64, align 8
  %stream_number.addr = alloca i64, align 8
  %block_number_base.addr = alloca i64, align 8
  %allocator.addr = alloca %struct.lzma_allocator*, align 8
  %s = alloca %struct.index_stream*, align 8
  store i64 %compressed_base, i64* %compressed_base.addr, align 8
  call void @llvm.dbg.declare(metadata i64* %compressed_base.addr, metadata !409, metadata !341), !dbg !410
  store i64 %uncompressed_base, i64* %uncompressed_base.addr, align 8
  call void @llvm.dbg.declare(metadata i64* %uncompressed_base.addr, metadata !411, metadata !341), !dbg !412
  store i64 %stream_number, i64* %stream_number.addr, align 8
  call void @llvm.dbg.declare(metadata i64* %stream_number.addr, metadata !413, metadata !341), !dbg !414
  store i64 %block_number_base, i64* %block_number_base.addr, align 8
  call void @llvm.dbg.declare(metadata i64* %block_number_base.addr, metadata !415, metadata !341), !dbg !416
  store %struct.lzma_allocator* %allocator, %struct.lzma_allocator** %allocator.addr, align 8
  call void @llvm.dbg.declare(metadata %struct.lzma_allocator** %allocator.addr, metadata !417, metadata !341), !dbg !418
  call void @llvm.dbg.declare(metadata %struct.index_stream** %s, metadata !419, metadata !341), !dbg !420
  %0 = load %struct.lzma_allocator*, %struct.lzma_allocator** %allocator.addr, align 8, !dbg !421
  %call = call noalias i8* @lzma_alloc(i64 168, %struct.lzma_allocator* %0), !dbg !422
  %1 = bitcast i8* %call to %struct.index_stream*, !dbg !422
  store %struct.index_stream* %1, %struct.index_stream** %s, align 8, !dbg !420
  %2 = load %struct.index_stream*, %struct.index_stream** %s, align 8, !dbg !423
  %cmp = icmp eq %struct.index_stream* %2, null, !dbg !425
  br i1 %cmp, label %if.then, label %if.end, !dbg !426

if.then:                                          ; preds = %entry
  store %struct.index_stream* null, %struct.index_stream** %retval, align 8, !dbg !427
  br label %return, !dbg !427

if.end:                                           ; preds = %entry
  %3 = load i64, i64* %uncompressed_base.addr, align 8, !dbg !428
  %4 = load %struct.index_stream*, %struct.index_stream** %s, align 8, !dbg !429
  %node = getelementptr inbounds %struct.index_stream, %struct.index_stream* %4, i32 0, i32 0, !dbg !430
  %uncompressed_base1 = getelementptr inbounds %struct.index_tree_node_s, %struct.index_tree_node_s* %node, i32 0, i32 0, !dbg !431
  store i64 %3, i64* %uncompressed_base1, align 8, !dbg !432
  %5 = load i64, i64* %compressed_base.addr, align 8, !dbg !433
  %6 = load %struct.index_stream*, %struct.index_stream** %s, align 8, !dbg !434
  %node2 = getelementptr inbounds %struct.index_stream, %struct.index_stream* %6, i32 0, i32 0, !dbg !435
  %compressed_base3 = getelementptr inbounds %struct.index_tree_node_s, %struct.index_tree_node_s* %node2, i32 0, i32 1, !dbg !436
  store i64 %5, i64* %compressed_base3, align 8, !dbg !437
  %7 = load %struct.index_stream*, %struct.index_stream** %s, align 8, !dbg !438
  %node4 = getelementptr inbounds %struct.index_stream, %struct.index_stream* %7, i32 0, i32 0, !dbg !439
  %parent = getelementptr inbounds %struct.index_tree_node_s, %struct.index_tree_node_s* %node4, i32 0, i32 2, !dbg !440
  store %struct.index_tree_node_s* null, %struct.index_tree_node_s** %parent, align 8, !dbg !441
  %8 = load %struct.index_stream*, %struct.index_stream** %s, align 8, !dbg !442
  %node5 = getelementptr inbounds %struct.index_stream, %struct.index_stream* %8, i32 0, i32 0, !dbg !443
  %left = getelementptr inbounds %struct.index_tree_node_s, %struct.index_tree_node_s* %node5, i32 0, i32 3, !dbg !444
  store %struct.index_tree_node_s* null, %struct.index_tree_node_s** %left, align 8, !dbg !445
  %9 = load %struct.index_stream*, %struct.index_stream** %s, align 8, !dbg !446
  %node6 = getelementptr inbounds %struct.index_stream, %struct.index_stream* %9, i32 0, i32 0, !dbg !447
  %right = getelementptr inbounds %struct.index_tree_node_s, %struct.index_tree_node_s* %node6, i32 0, i32 4, !dbg !448
  store %struct.index_tree_node_s* null, %struct.index_tree_node_s** %right, align 8, !dbg !449
  %10 = load i64, i64* %stream_number.addr, align 8, !dbg !450
  %conv = trunc i64 %10 to i32, !dbg !450
  %11 = load %struct.index_stream*, %struct.index_stream** %s, align 8, !dbg !451
  %number = getelementptr inbounds %struct.index_stream, %struct.index_stream* %11, i32 0, i32 1, !dbg !452
  store i32 %conv, i32* %number, align 8, !dbg !453
  %12 = load i64, i64* %block_number_base.addr, align 8, !dbg !454
  %13 = load %struct.index_stream*, %struct.index_stream** %s, align 8, !dbg !455
  %block_number_base7 = getelementptr inbounds %struct.index_stream, %struct.index_stream* %13, i32 0, i32 2, !dbg !456
  store i64 %12, i64* %block_number_base7, align 8, !dbg !457
  %14 = load %struct.index_stream*, %struct.index_stream** %s, align 8, !dbg !458
  %groups = getelementptr inbounds %struct.index_stream, %struct.index_stream* %14, i32 0, i32 3, !dbg !459
  call void @index_tree_init(%struct.index_tree* %groups), !dbg !460
  %15 = load %struct.index_stream*, %struct.index_stream** %s, align 8, !dbg !461
  %record_count = getelementptr inbounds %struct.index_stream, %struct.index_stream* %15, i32 0, i32 4, !dbg !462
  store i64 0, i64* %record_count, align 8, !dbg !463
  %16 = load %struct.index_stream*, %struct.index_stream** %s, align 8, !dbg !464
  %index_list_size = getelementptr inbounds %struct.index_stream, %struct.index_stream* %16, i32 0, i32 5, !dbg !465
  store i64 0, i64* %index_list_size, align 8, !dbg !466
  %17 = load %struct.index_stream*, %struct.index_stream** %s, align 8, !dbg !467
  %stream_flags = getelementptr inbounds %struct.index_stream, %struct.index_stream* %17, i32 0, i32 6, !dbg !468
  %version = getelementptr inbounds %struct.lzma_stream_flags, %struct.lzma_stream_flags* %stream_flags, i32 0, i32 0, !dbg !469
  store i32 -1, i32* %version, align 8, !dbg !470
  %18 = load %struct.index_stream*, %struct.index_stream** %s, align 8, !dbg !471
  %stream_padding = getelementptr inbounds %struct.index_stream, %struct.index_stream* %18, i32 0, i32 7, !dbg !472
  store i64 0, i64* %stream_padding, align 8, !dbg !473
  %19 = load %struct.index_stream*, %struct.index_stream** %s, align 8, !dbg !474
  store %struct.index_stream* %19, %struct.index_stream** %retval, align 8, !dbg !475
  br label %return, !dbg !475

return:                                           ; preds = %if.end, %if.then
  %20 = load %struct.index_stream*, %struct.index_stream** %retval, align 8, !dbg !476
  ret %struct.index_stream* %20, !dbg !476
}

declare void @lzma_free(i8*, %struct.lzma_allocator*) #2

; Function Attrs: nounwind uwtable
define internal void @index_tree_append(%struct.index_tree* %tree, %struct.index_tree_node_s* %node) #0 !dbg !281 {
entry:
  %tree.addr = alloca %struct.index_tree*, align 8
  %node.addr = alloca %struct.index_tree_node_s*, align 8
  %up = alloca i32, align 4
  %pivot = alloca %struct.index_tree_node_s*, align 8
  store %struct.index_tree* %tree, %struct.index_tree** %tree.addr, align 8
  call void @llvm.dbg.declare(metadata %struct.index_tree** %tree.addr, metadata !477, metadata !341), !dbg !478
  store %struct.index_tree_node_s* %node, %struct.index_tree_node_s** %node.addr, align 8
  call void @llvm.dbg.declare(metadata %struct.index_tree_node_s** %node.addr, metadata !479, metadata !341), !dbg !480
  call void @llvm.dbg.declare(metadata i32* %up, metadata !481, metadata !341), !dbg !482
  %0 = load %struct.index_tree*, %struct.index_tree** %tree.addr, align 8, !dbg !483
  %rightmost = getelementptr inbounds %struct.index_tree, %struct.index_tree* %0, i32 0, i32 2, !dbg !484
  %1 = load %struct.index_tree_node_s*, %struct.index_tree_node_s** %rightmost, align 8, !dbg !484
  %2 = load %struct.index_tree_node_s*, %struct.index_tree_node_s** %node.addr, align 8, !dbg !485
  %parent = getelementptr inbounds %struct.index_tree_node_s, %struct.index_tree_node_s* %2, i32 0, i32 2, !dbg !486
  store %struct.index_tree_node_s* %1, %struct.index_tree_node_s** %parent, align 8, !dbg !487
  %3 = load %struct.index_tree_node_s*, %struct.index_tree_node_s** %node.addr, align 8, !dbg !488
  %left = getelementptr inbounds %struct.index_tree_node_s, %struct.index_tree_node_s* %3, i32 0, i32 3, !dbg !489
  store %struct.index_tree_node_s* null, %struct.index_tree_node_s** %left, align 8, !dbg !490
  %4 = load %struct.index_tree_node_s*, %struct.index_tree_node_s** %node.addr, align 8, !dbg !491
  %right = getelementptr inbounds %struct.index_tree_node_s, %struct.index_tree_node_s* %4, i32 0, i32 4, !dbg !492
  store %struct.index_tree_node_s* null, %struct.index_tree_node_s** %right, align 8, !dbg !493
  %5 = load %struct.index_tree*, %struct.index_tree** %tree.addr, align 8, !dbg !494
  %count = getelementptr inbounds %struct.index_tree, %struct.index_tree* %5, i32 0, i32 3, !dbg !495
  %6 = load i32, i32* %count, align 8, !dbg !496
  %inc = add i32 %6, 1, !dbg !496
  store i32 %inc, i32* %count, align 8, !dbg !496
  %7 = load %struct.index_tree*, %struct.index_tree** %tree.addr, align 8, !dbg !497
  %root = getelementptr inbounds %struct.index_tree, %struct.index_tree* %7, i32 0, i32 0, !dbg !499
  %8 = load %struct.index_tree_node_s*, %struct.index_tree_node_s** %root, align 8, !dbg !499
  %cmp = icmp eq %struct.index_tree_node_s* %8, null, !dbg !500
  br i1 %cmp, label %if.then, label %if.end, !dbg !501

if.then:                                          ; preds = %entry
  %9 = load %struct.index_tree_node_s*, %struct.index_tree_node_s** %node.addr, align 8, !dbg !502
  %10 = load %struct.index_tree*, %struct.index_tree** %tree.addr, align 8, !dbg !504
  %root1 = getelementptr inbounds %struct.index_tree, %struct.index_tree* %10, i32 0, i32 0, !dbg !505
  store %struct.index_tree_node_s* %9, %struct.index_tree_node_s** %root1, align 8, !dbg !506
  %11 = load %struct.index_tree_node_s*, %struct.index_tree_node_s** %node.addr, align 8, !dbg !507
  %12 = load %struct.index_tree*, %struct.index_tree** %tree.addr, align 8, !dbg !508
  %leftmost = getelementptr inbounds %struct.index_tree, %struct.index_tree* %12, i32 0, i32 1, !dbg !509
  store %struct.index_tree_node_s* %11, %struct.index_tree_node_s** %leftmost, align 8, !dbg !510
  %13 = load %struct.index_tree_node_s*, %struct.index_tree_node_s** %node.addr, align 8, !dbg !511
  %14 = load %struct.index_tree*, %struct.index_tree** %tree.addr, align 8, !dbg !512
  %rightmost2 = getelementptr inbounds %struct.index_tree, %struct.index_tree* %14, i32 0, i32 2, !dbg !513
  store %struct.index_tree_node_s* %13, %struct.index_tree_node_s** %rightmost2, align 8, !dbg !514
  br label %return, !dbg !515

if.end:                                           ; preds = %entry
  %15 = load %struct.index_tree*, %struct.index_tree** %tree.addr, align 8, !dbg !516
  %rightmost3 = getelementptr inbounds %struct.index_tree, %struct.index_tree* %15, i32 0, i32 2, !dbg !516
  %16 = load %struct.index_tree_node_s*, %struct.index_tree_node_s** %rightmost3, align 8, !dbg !516
  %uncompressed_base = getelementptr inbounds %struct.index_tree_node_s, %struct.index_tree_node_s* %16, i32 0, i32 0, !dbg !516
  %17 = load i64, i64* %uncompressed_base, align 8, !dbg !516
  %18 = load %struct.index_tree_node_s*, %struct.index_tree_node_s** %node.addr, align 8, !dbg !516
  %uncompressed_base4 = getelementptr inbounds %struct.index_tree_node_s, %struct.index_tree_node_s* %18, i32 0, i32 0, !dbg !516
  %19 = load i64, i64* %uncompressed_base4, align 8, !dbg !516
  %cmp5 = icmp ule i64 %17, %19, !dbg !516
  br i1 %cmp5, label %cond.true, label %cond.false, !dbg !516

cond.true:                                        ; preds = %if.end
  br label %cond.end, !dbg !517

cond.false:                                       ; preds = %if.end
  call void @__assert_fail(i8* getelementptr inbounds ([62 x i8], [62 x i8]* @.str.7, i32 0, i32 0), i8* getelementptr inbounds ([77 x i8], [77 x i8]* @.str.1, i32 0, i32 0), i32 249, i8* getelementptr inbounds ([56 x i8], [56 x i8]* @__PRETTY_FUNCTION__.index_tree_append, i32 0, i32 0)) #8, !dbg !519
  unreachable, !dbg !519
                                                  ; No predecessors!
  br label %cond.end, !dbg !521

cond.end:                                         ; preds = %20, %cond.true
  %21 = load %struct.index_tree*, %struct.index_tree** %tree.addr, align 8, !dbg !523
  %rightmost6 = getelementptr inbounds %struct.index_tree, %struct.index_tree* %21, i32 0, i32 2, !dbg !523
  %22 = load %struct.index_tree_node_s*, %struct.index_tree_node_s** %rightmost6, align 8, !dbg !523
  %compressed_base = getelementptr inbounds %struct.index_tree_node_s, %struct.index_tree_node_s* %22, i32 0, i32 1, !dbg !523
  %23 = load i64, i64* %compressed_base, align 8, !dbg !523
  %24 = load %struct.index_tree_node_s*, %struct.index_tree_node_s** %node.addr, align 8, !dbg !523
  %compressed_base7 = getelementptr inbounds %struct.index_tree_node_s, %struct.index_tree_node_s* %24, i32 0, i32 1, !dbg !523
  %25 = load i64, i64* %compressed_base7, align 8, !dbg !523
  %cmp8 = icmp ult i64 %23, %25, !dbg !523
  br i1 %cmp8, label %cond.true9, label %cond.false10, !dbg !523

cond.true9:                                       ; preds = %cond.end
  br label %cond.end11, !dbg !524

cond.false10:                                     ; preds = %cond.end
  call void @__assert_fail(i8* getelementptr inbounds ([57 x i8], [57 x i8]* @.str.8, i32 0, i32 0), i8* getelementptr inbounds ([77 x i8], [77 x i8]* @.str.1, i32 0, i32 0), i32 250, i8* getelementptr inbounds ([56 x i8], [56 x i8]* @__PRETTY_FUNCTION__.index_tree_append, i32 0, i32 0)) #8, !dbg !525
  unreachable, !dbg !525
                                                  ; No predecessors!
  br label %cond.end11, !dbg !526

cond.end11:                                       ; preds = %26, %cond.true9
  %27 = load %struct.index_tree_node_s*, %struct.index_tree_node_s** %node.addr, align 8, !dbg !527
  %28 = load %struct.index_tree*, %struct.index_tree** %tree.addr, align 8, !dbg !528
  %rightmost12 = getelementptr inbounds %struct.index_tree, %struct.index_tree* %28, i32 0, i32 2, !dbg !529
  %29 = load %struct.index_tree_node_s*, %struct.index_tree_node_s** %rightmost12, align 8, !dbg !529
  %right13 = getelementptr inbounds %struct.index_tree_node_s, %struct.index_tree_node_s* %29, i32 0, i32 4, !dbg !530
  store %struct.index_tree_node_s* %27, %struct.index_tree_node_s** %right13, align 8, !dbg !531
  %30 = load %struct.index_tree_node_s*, %struct.index_tree_node_s** %node.addr, align 8, !dbg !532
  %31 = load %struct.index_tree*, %struct.index_tree** %tree.addr, align 8, !dbg !533
  %rightmost14 = getelementptr inbounds %struct.index_tree, %struct.index_tree* %31, i32 0, i32 2, !dbg !534
  store %struct.index_tree_node_s* %30, %struct.index_tree_node_s** %rightmost14, align 8, !dbg !535
  %32 = load %struct.index_tree*, %struct.index_tree** %tree.addr, align 8, !dbg !536
  %count15 = getelementptr inbounds %struct.index_tree, %struct.index_tree* %32, i32 0, i32 3, !dbg !537
  %33 = load i32, i32* %count15, align 8, !dbg !537
  %34 = load %struct.index_tree*, %struct.index_tree** %tree.addr, align 8, !dbg !538
  %count16 = getelementptr inbounds %struct.index_tree, %struct.index_tree* %34, i32 0, i32 3, !dbg !539
  %35 = load i32, i32* %count16, align 8, !dbg !539
  %call = call i32 @bsr32(i32 %35), !dbg !540
  %shl = shl i32 1, %call, !dbg !541
  %xor = xor i32 %33, %shl, !dbg !542
  store i32 %xor, i32* %up, align 4, !dbg !543
  %36 = load i32, i32* %up, align 4, !dbg !544
  %cmp17 = icmp ne i32 %36, 0, !dbg !546
  br i1 %cmp17, label %if.then18, label %if.end49, !dbg !547

if.then18:                                        ; preds = %cond.end11
  call void @llvm.dbg.declare(metadata %struct.index_tree_node_s** %pivot, metadata !548, metadata !341), !dbg !550
  %37 = load %struct.index_tree*, %struct.index_tree** %tree.addr, align 8, !dbg !551
  %count19 = getelementptr inbounds %struct.index_tree, %struct.index_tree* %37, i32 0, i32 3, !dbg !552
  %38 = load i32, i32* %count19, align 8, !dbg !552
  %call20 = call i32 @ctz32(i32 %38), !dbg !553
  %add = add i32 %call20, 2, !dbg !554
  store i32 %add, i32* %up, align 4, !dbg !555
  br label %do.body, !dbg !556

do.body:                                          ; preds = %do.cond, %if.then18
  %39 = load %struct.index_tree_node_s*, %struct.index_tree_node_s** %node.addr, align 8, !dbg !557
  %parent21 = getelementptr inbounds %struct.index_tree_node_s, %struct.index_tree_node_s* %39, i32 0, i32 2, !dbg !559
  %40 = load %struct.index_tree_node_s*, %struct.index_tree_node_s** %parent21, align 8, !dbg !559
  store %struct.index_tree_node_s* %40, %struct.index_tree_node_s** %node.addr, align 8, !dbg !560
  br label %do.cond, !dbg !561

do.cond:                                          ; preds = %do.body
  %41 = load i32, i32* %up, align 4, !dbg !562
  %dec = add i32 %41, -1, !dbg !562
  store i32 %dec, i32* %up, align 4, !dbg !562
  %cmp22 = icmp ugt i32 %dec, 0, !dbg !564
  br i1 %cmp22, label %do.body, label %do.end, !dbg !565

do.end:                                           ; preds = %do.cond
  %42 = load %struct.index_tree_node_s*, %struct.index_tree_node_s** %node.addr, align 8, !dbg !566
  %right23 = getelementptr inbounds %struct.index_tree_node_s, %struct.index_tree_node_s* %42, i32 0, i32 4, !dbg !567
  %43 = load %struct.index_tree_node_s*, %struct.index_tree_node_s** %right23, align 8, !dbg !567
  store %struct.index_tree_node_s* %43, %struct.index_tree_node_s** %pivot, align 8, !dbg !568
  %44 = load %struct.index_tree_node_s*, %struct.index_tree_node_s** %node.addr, align 8, !dbg !569
  %parent24 = getelementptr inbounds %struct.index_tree_node_s, %struct.index_tree_node_s* %44, i32 0, i32 2, !dbg !571
  %45 = load %struct.index_tree_node_s*, %struct.index_tree_node_s** %parent24, align 8, !dbg !571
  %cmp25 = icmp eq %struct.index_tree_node_s* %45, null, !dbg !572
  br i1 %cmp25, label %if.then26, label %if.else, !dbg !573

if.then26:                                        ; preds = %do.end
  %46 = load %struct.index_tree_node_s*, %struct.index_tree_node_s** %pivot, align 8, !dbg !574
  %47 = load %struct.index_tree*, %struct.index_tree** %tree.addr, align 8, !dbg !576
  %root27 = getelementptr inbounds %struct.index_tree, %struct.index_tree* %47, i32 0, i32 0, !dbg !577
  store %struct.index_tree_node_s* %46, %struct.index_tree_node_s** %root27, align 8, !dbg !578
  br label %if.end36, !dbg !579

if.else:                                          ; preds = %do.end
  %48 = load %struct.index_tree_node_s*, %struct.index_tree_node_s** %node.addr, align 8, !dbg !580
  %parent28 = getelementptr inbounds %struct.index_tree_node_s, %struct.index_tree_node_s* %48, i32 0, i32 2, !dbg !580
  %49 = load %struct.index_tree_node_s*, %struct.index_tree_node_s** %parent28, align 8, !dbg !580
  %right29 = getelementptr inbounds %struct.index_tree_node_s, %struct.index_tree_node_s* %49, i32 0, i32 4, !dbg !580
  %50 = load %struct.index_tree_node_s*, %struct.index_tree_node_s** %right29, align 8, !dbg !580
  %51 = load %struct.index_tree_node_s*, %struct.index_tree_node_s** %node.addr, align 8, !dbg !580
  %cmp30 = icmp eq %struct.index_tree_node_s* %50, %51, !dbg !580
  br i1 %cmp30, label %cond.true31, label %cond.false32, !dbg !580

cond.true31:                                      ; preds = %if.else
  br label %cond.end33, !dbg !582

cond.false32:                                     ; preds = %if.else
  call void @__assert_fail(i8* getelementptr inbounds ([28 x i8], [28 x i8]* @.str.9, i32 0, i32 0), i8* getelementptr inbounds ([77 x i8], [77 x i8]* @.str.1, i32 0, i32 0), i32 278, i8* getelementptr inbounds ([56 x i8], [56 x i8]* @__PRETTY_FUNCTION__.index_tree_append, i32 0, i32 0)) #8, !dbg !584
  unreachable, !dbg !584
                                                  ; No predecessors!
  br label %cond.end33, !dbg !586

cond.end33:                                       ; preds = %52, %cond.true31
  %53 = load %struct.index_tree_node_s*, %struct.index_tree_node_s** %pivot, align 8, !dbg !588
  %54 = load %struct.index_tree_node_s*, %struct.index_tree_node_s** %node.addr, align 8, !dbg !589
  %parent34 = getelementptr inbounds %struct.index_tree_node_s, %struct.index_tree_node_s* %54, i32 0, i32 2, !dbg !590
  %55 = load %struct.index_tree_node_s*, %struct.index_tree_node_s** %parent34, align 8, !dbg !590
  %right35 = getelementptr inbounds %struct.index_tree_node_s, %struct.index_tree_node_s* %55, i32 0, i32 4, !dbg !591
  store %struct.index_tree_node_s* %53, %struct.index_tree_node_s** %right35, align 8, !dbg !592
  br label %if.end36

if.end36:                                         ; preds = %cond.end33, %if.then26
  %56 = load %struct.index_tree_node_s*, %struct.index_tree_node_s** %node.addr, align 8, !dbg !593
  %parent37 = getelementptr inbounds %struct.index_tree_node_s, %struct.index_tree_node_s* %56, i32 0, i32 2, !dbg !594
  %57 = load %struct.index_tree_node_s*, %struct.index_tree_node_s** %parent37, align 8, !dbg !594
  %58 = load %struct.index_tree_node_s*, %struct.index_tree_node_s** %pivot, align 8, !dbg !595
  %parent38 = getelementptr inbounds %struct.index_tree_node_s, %struct.index_tree_node_s* %58, i32 0, i32 2, !dbg !596
  store %struct.index_tree_node_s* %57, %struct.index_tree_node_s** %parent38, align 8, !dbg !597
  %59 = load %struct.index_tree_node_s*, %struct.index_tree_node_s** %pivot, align 8, !dbg !598
  %left39 = getelementptr inbounds %struct.index_tree_node_s, %struct.index_tree_node_s* %59, i32 0, i32 3, !dbg !599
  %60 = load %struct.index_tree_node_s*, %struct.index_tree_node_s** %left39, align 8, !dbg !599
  %61 = load %struct.index_tree_node_s*, %struct.index_tree_node_s** %node.addr, align 8, !dbg !600
  %right40 = getelementptr inbounds %struct.index_tree_node_s, %struct.index_tree_node_s* %61, i32 0, i32 4, !dbg !601
  store %struct.index_tree_node_s* %60, %struct.index_tree_node_s** %right40, align 8, !dbg !602
  %62 = load %struct.index_tree_node_s*, %struct.index_tree_node_s** %node.addr, align 8, !dbg !603
  %right41 = getelementptr inbounds %struct.index_tree_node_s, %struct.index_tree_node_s* %62, i32 0, i32 4, !dbg !605
  %63 = load %struct.index_tree_node_s*, %struct.index_tree_node_s** %right41, align 8, !dbg !605
  %cmp42 = icmp ne %struct.index_tree_node_s* %63, null, !dbg !606
  br i1 %cmp42, label %if.then43, label %if.end46, !dbg !607

if.then43:                                        ; preds = %if.end36
  %64 = load %struct.index_tree_node_s*, %struct.index_tree_node_s** %node.addr, align 8, !dbg !608
  %65 = load %struct.index_tree_node_s*, %struct.index_tree_node_s** %node.addr, align 8, !dbg !609
  %right44 = getelementptr inbounds %struct.index_tree_node_s, %struct.index_tree_node_s* %65, i32 0, i32 4, !dbg !610
  %66 = load %struct.index_tree_node_s*, %struct.index_tree_node_s** %right44, align 8, !dbg !610
  %parent45 = getelementptr inbounds %struct.index_tree_node_s, %struct.index_tree_node_s* %66, i32 0, i32 2, !dbg !611
  store %struct.index_tree_node_s* %64, %struct.index_tree_node_s** %parent45, align 8, !dbg !612
  br label %if.end46, !dbg !609

if.end46:                                         ; preds = %if.then43, %if.end36
  %67 = load %struct.index_tree_node_s*, %struct.index_tree_node_s** %node.addr, align 8, !dbg !613
  %68 = load %struct.index_tree_node_s*, %struct.index_tree_node_s** %pivot, align 8, !dbg !614
  %left47 = getelementptr inbounds %struct.index_tree_node_s, %struct.index_tree_node_s* %68, i32 0, i32 3, !dbg !615
  store %struct.index_tree_node_s* %67, %struct.index_tree_node_s** %left47, align 8, !dbg !616
  %69 = load %struct.index_tree_node_s*, %struct.index_tree_node_s** %pivot, align 8, !dbg !617
  %70 = load %struct.index_tree_node_s*, %struct.index_tree_node_s** %node.addr, align 8, !dbg !618
  %parent48 = getelementptr inbounds %struct.index_tree_node_s, %struct.index_tree_node_s* %70, i32 0, i32 2, !dbg !619
  store %struct.index_tree_node_s* %69, %struct.index_tree_node_s** %parent48, align 8, !dbg !620
  br label %if.end49, !dbg !621

if.end49:                                         ; preds = %if.end46, %cond.end11
  br label %return, !dbg !622

return:                                           ; preds = %if.end49, %if.then
  ret void, !dbg !623
}

; Function Attrs: nounwind uwtable
define void @lzma_index_end(%struct.lzma_index_s* %i, %struct.lzma_allocator* %allocator) #0 !dbg !161 {
entry:
  %i.addr = alloca %struct.lzma_index_s*, align 8
  %allocator.addr = alloca %struct.lzma_allocator*, align 8
  store %struct.lzma_index_s* %i, %struct.lzma_index_s** %i.addr, align 8
  call void @llvm.dbg.declare(metadata %struct.lzma_index_s** %i.addr, metadata !624, metadata !341), !dbg !625
  store %struct.lzma_allocator* %allocator, %struct.lzma_allocator** %allocator.addr, align 8
  call void @llvm.dbg.declare(metadata %struct.lzma_allocator** %allocator.addr, metadata !626, metadata !341), !dbg !627
  %0 = load %struct.lzma_index_s*, %struct.lzma_index_s** %i.addr, align 8, !dbg !628
  %cmp = icmp ne %struct.lzma_index_s* %0, null, !dbg !630
  br i1 %cmp, label %if.then, label %if.end, !dbg !631

if.then:                                          ; preds = %entry
  %1 = load %struct.lzma_index_s*, %struct.lzma_index_s** %i.addr, align 8, !dbg !632
  %streams = getelementptr inbounds %struct.lzma_index_s, %struct.lzma_index_s* %1, i32 0, i32 0, !dbg !634
  %2 = load %struct.lzma_allocator*, %struct.lzma_allocator** %allocator.addr, align 8, !dbg !635
  call void @index_tree_end(%struct.index_tree* %streams, %struct.lzma_allocator* %2, void (i8*, %struct.lzma_allocator*)* @index_stream_end), !dbg !636
  %3 = load %struct.lzma_index_s*, %struct.lzma_index_s** %i.addr, align 8, !dbg !637
  %4 = bitcast %struct.lzma_index_s* %3 to i8*, !dbg !637
  %5 = load %struct.lzma_allocator*, %struct.lzma_allocator** %allocator.addr, align 8, !dbg !638
  call void @lzma_free(i8* %4, %struct.lzma_allocator* %5), !dbg !639
  br label %if.end, !dbg !640

if.end:                                           ; preds = %if.then, %entry
  ret void, !dbg !641
}

; Function Attrs: nounwind uwtable
define internal void @index_tree_end(%struct.index_tree* %tree, %struct.lzma_allocator* %allocator, void (i8*, %struct.lzma_allocator*)* %free_func) #0 !dbg !289 {
entry:
  %tree.addr = alloca %struct.index_tree*, align 8
  %allocator.addr = alloca %struct.lzma_allocator*, align 8
  %free_func.addr = alloca void (i8*, %struct.lzma_allocator*)*, align 8
  store %struct.index_tree* %tree, %struct.index_tree** %tree.addr, align 8
  call void @llvm.dbg.declare(metadata %struct.index_tree** %tree.addr, metadata !642, metadata !341), !dbg !643
  store %struct.lzma_allocator* %allocator, %struct.lzma_allocator** %allocator.addr, align 8
  call void @llvm.dbg.declare(metadata %struct.lzma_allocator** %allocator.addr, metadata !644, metadata !341), !dbg !645
  store void (i8*, %struct.lzma_allocator*)* %free_func, void (i8*, %struct.lzma_allocator*)** %free_func.addr, align 8
  call void @llvm.dbg.declare(metadata void (i8*, %struct.lzma_allocator*)** %free_func.addr, metadata !646, metadata !341), !dbg !647
  %0 = load %struct.index_tree*, %struct.index_tree** %tree.addr, align 8, !dbg !648
  %root = getelementptr inbounds %struct.index_tree, %struct.index_tree* %0, i32 0, i32 0, !dbg !650
  %1 = load %struct.index_tree_node_s*, %struct.index_tree_node_s** %root, align 8, !dbg !650
  %cmp = icmp ne %struct.index_tree_node_s* %1, null, !dbg !651
  br i1 %cmp, label %if.then, label %if.end, !dbg !652

if.then:                                          ; preds = %entry
  %2 = load %struct.index_tree*, %struct.index_tree** %tree.addr, align 8, !dbg !653
  %root1 = getelementptr inbounds %struct.index_tree, %struct.index_tree* %2, i32 0, i32 0, !dbg !654
  %3 = load %struct.index_tree_node_s*, %struct.index_tree_node_s** %root1, align 8, !dbg !654
  %4 = load %struct.lzma_allocator*, %struct.lzma_allocator** %allocator.addr, align 8, !dbg !655
  %5 = load void (i8*, %struct.lzma_allocator*)*, void (i8*, %struct.lzma_allocator*)** %free_func.addr, align 8, !dbg !656
  call void @index_tree_node_end(%struct.index_tree_node_s* %3, %struct.lzma_allocator* %4, void (i8*, %struct.lzma_allocator*)* %5), !dbg !657
  br label %if.end, !dbg !657

if.end:                                           ; preds = %if.then, %entry
  ret void, !dbg !658
}

; Function Attrs: nounwind uwtable
define internal void @index_stream_end(i8* %node, %struct.lzma_allocator* %allocator) #0 !dbg !298 {
entry:
  %node.addr = alloca i8*, align 8
  %allocator.addr = alloca %struct.lzma_allocator*, align 8
  %s = alloca %struct.index_stream*, align 8
  store i8* %node, i8** %node.addr, align 8
  call void @llvm.dbg.declare(metadata i8** %node.addr, metadata !659, metadata !341), !dbg !660
  store %struct.lzma_allocator* %allocator, %struct.lzma_allocator** %allocator.addr, align 8
  call void @llvm.dbg.declare(metadata %struct.lzma_allocator** %allocator.addr, metadata !661, metadata !341), !dbg !662
  call void @llvm.dbg.declare(metadata %struct.index_stream** %s, metadata !663, metadata !341), !dbg !664
  %0 = load i8*, i8** %node.addr, align 8, !dbg !665
  %1 = bitcast i8* %0 to %struct.index_stream*, !dbg !665
  store %struct.index_stream* %1, %struct.index_stream** %s, align 8, !dbg !664
  %2 = load %struct.index_stream*, %struct.index_stream** %s, align 8, !dbg !666
  %groups = getelementptr inbounds %struct.index_stream, %struct.index_stream* %2, i32 0, i32 3, !dbg !667
  %3 = load %struct.lzma_allocator*, %struct.lzma_allocator** %allocator.addr, align 8, !dbg !668
  call void @index_tree_end(%struct.index_tree* %groups, %struct.lzma_allocator* %3, void (i8*, %struct.lzma_allocator*)* null), !dbg !669
  ret void, !dbg !670
}

; Function Attrs: nounwind uwtable
define void @lzma_index_prealloc(%struct.lzma_index_s* %i, i64 %records) #0 !dbg !164 {
entry:
  %i.addr = alloca %struct.lzma_index_s*, align 8
  %records.addr = alloca i64, align 8
  store %struct.lzma_index_s* %i, %struct.lzma_index_s** %i.addr, align 8
  call void @llvm.dbg.declare(metadata %struct.lzma_index_s** %i.addr, metadata !671, metadata !341), !dbg !672
  store i64 %records, i64* %records.addr, align 8
  call void @llvm.dbg.declare(metadata i64* %records.addr, metadata !673, metadata !341), !dbg !674
  %0 = load i64, i64* %records.addr, align 8, !dbg !675
  %cmp = icmp ugt i64 %0, 1152921504606846971, !dbg !677
  br i1 %cmp, label %if.then, label %if.end, !dbg !678

if.then:                                          ; preds = %entry
  store i64 1152921504606846971, i64* %records.addr, align 8, !dbg !679
  br label %if.end, !dbg !680

if.end:                                           ; preds = %if.then, %entry
  %1 = load i64, i64* %records.addr, align 8, !dbg !681
  %2 = load %struct.lzma_index_s*, %struct.lzma_index_s** %i.addr, align 8, !dbg !682
  %prealloc = getelementptr inbounds %struct.lzma_index_s, %struct.lzma_index_s* %2, i32 0, i32 5, !dbg !683
  store i64 %1, i64* %prealloc, align 8, !dbg !684
  ret void, !dbg !685
}

; Function Attrs: nounwind uwtable
define i64 @lzma_index_memusage(i64 %streams, i64 %blocks) #0 !dbg !167 {
entry:
  %retval = alloca i64, align 8
  %streams.addr = alloca i64, align 8
  %blocks.addr = alloca i64, align 8
  %alloc_overhead = alloca i64, align 8
  %stream_base = alloca i64, align 8
  %group_base = alloca i64, align 8
  %groups = alloca i64, align 8
  %streams_mem = alloca i64, align 8
  %groups_mem = alloca i64, align 8
  %index_base = alloca i64, align 8
  %limit = alloca i64, align 8
  store i64 %streams, i64* %streams.addr, align 8
  call void @llvm.dbg.declare(metadata i64* %streams.addr, metadata !686, metadata !341), !dbg !687
  store i64 %blocks, i64* %blocks.addr, align 8
  call void @llvm.dbg.declare(metadata i64* %blocks.addr, metadata !688, metadata !341), !dbg !689
  call void @llvm.dbg.declare(metadata i64* %alloc_overhead, metadata !690, metadata !341), !dbg !692
  store i64 32, i64* %alloc_overhead, align 8, !dbg !692
  call void @llvm.dbg.declare(metadata i64* %stream_base, metadata !693, metadata !341), !dbg !694
  store i64 296, i64* %stream_base, align 8, !dbg !694
  call void @llvm.dbg.declare(metadata i64* %group_base, metadata !695, metadata !341), !dbg !696
  store i64 8288, i64* %group_base, align 8, !dbg !696
  call void @llvm.dbg.declare(metadata i64* %groups, metadata !697, metadata !341), !dbg !699
  %0 = load i64, i64* %blocks.addr, align 8, !dbg !700
  %add = add i64 %0, 512, !dbg !701
  %sub = sub i64 %add, 1, !dbg !702
  %div = udiv i64 %sub, 512, !dbg !703
  store i64 %div, i64* %groups, align 8, !dbg !699
  call void @llvm.dbg.declare(metadata i64* %streams_mem, metadata !704, metadata !341), !dbg !706
  %1 = load i64, i64* %streams.addr, align 8, !dbg !707
  %mul = mul i64 %1, 296, !dbg !708
  store i64 %mul, i64* %streams_mem, align 8, !dbg !706
  call void @llvm.dbg.declare(metadata i64* %groups_mem, metadata !709, metadata !341), !dbg !710
  %2 = load i64, i64* %groups, align 8, !dbg !711
  %mul1 = mul i64 %2, 8288, !dbg !712
  store i64 %mul1, i64* %groups_mem, align 8, !dbg !710
  call void @llvm.dbg.declare(metadata i64* %index_base, metadata !713, metadata !341), !dbg !714
  store i64 112, i64* %index_base, align 8, !dbg !714
  call void @llvm.dbg.declare(metadata i64* %limit, metadata !715, metadata !341), !dbg !716
  store i64 -113, i64* %limit, align 8, !dbg !716
  %3 = load i64, i64* %streams.addr, align 8, !dbg !717
  %cmp = icmp eq i64 %3, 0, !dbg !719
  br i1 %cmp, label %if.then, label %lor.lhs.false, !dbg !720

lor.lhs.false:                                    ; preds = %entry
  %4 = load i64, i64* %streams.addr, align 8, !dbg !721
  %cmp2 = icmp ugt i64 %4, 4294967295, !dbg !723
  br i1 %cmp2, label %if.then, label %lor.lhs.false3, !dbg !724

lor.lhs.false3:                                   ; preds = %lor.lhs.false
  %5 = load i64, i64* %blocks.addr, align 8, !dbg !725
  %cmp4 = icmp ugt i64 %5, 9223372036854775807, !dbg !727
  br i1 %cmp4, label %if.then, label %lor.lhs.false5, !dbg !728

lor.lhs.false5:                                   ; preds = %lor.lhs.false3
  %6 = load i64, i64* %streams.addr, align 8, !dbg !729
  %cmp6 = icmp ugt i64 %6, 62320081330099836, !dbg !730
  br i1 %cmp6, label %if.then, label %lor.lhs.false7, !dbg !731

lor.lhs.false7:                                   ; preds = %lor.lhs.false5
  %7 = load i64, i64* %groups, align 8, !dbg !732
  %cmp8 = icmp ugt i64 %7, 2225717190360708, !dbg !733
  br i1 %cmp8, label %if.then, label %lor.lhs.false9, !dbg !734

lor.lhs.false9:                                   ; preds = %lor.lhs.false7
  %8 = load i64, i64* %streams_mem, align 8, !dbg !735
  %sub10 = sub i64 -113, %8, !dbg !736
  %9 = load i64, i64* %groups_mem, align 8, !dbg !737
  %cmp11 = icmp ult i64 %sub10, %9, !dbg !738
  br i1 %cmp11, label %if.then, label %if.end, !dbg !739

if.then:                                          ; preds = %lor.lhs.false9, %lor.lhs.false7, %lor.lhs.false5, %lor.lhs.false3, %lor.lhs.false, %entry
  store i64 -1, i64* %retval, align 8, !dbg !741
  br label %return, !dbg !741

if.end:                                           ; preds = %lor.lhs.false9
  %10 = load i64, i64* %streams_mem, align 8, !dbg !742
  %add12 = add i64 112, %10, !dbg !743
  %11 = load i64, i64* %groups_mem, align 8, !dbg !744
  %add13 = add i64 %add12, %11, !dbg !745
  store i64 %add13, i64* %retval, align 8, !dbg !746
  br label %return, !dbg !746

return:                                           ; preds = %if.end, %if.then
  %12 = load i64, i64* %retval, align 8, !dbg !747
  ret i64 %12, !dbg !747
}

; Function Attrs: nounwind uwtable
define i64 @lzma_index_memused(%struct.lzma_index_s* %i) #0 !dbg !170 {
entry:
  %i.addr = alloca %struct.lzma_index_s*, align 8
  store %struct.lzma_index_s* %i, %struct.lzma_index_s** %i.addr, align 8
  call void @llvm.dbg.declare(metadata %struct.lzma_index_s** %i.addr, metadata !748, metadata !341), !dbg !749
  %0 = load %struct.lzma_index_s*, %struct.lzma_index_s** %i.addr, align 8, !dbg !750
  %streams = getelementptr inbounds %struct.lzma_index_s, %struct.lzma_index_s* %0, i32 0, i32 0, !dbg !751
  %count = getelementptr inbounds %struct.index_tree, %struct.index_tree* %streams, i32 0, i32 3, !dbg !752
  %1 = load i32, i32* %count, align 8, !dbg !752
  %conv = zext i32 %1 to i64, !dbg !750
  %2 = load %struct.lzma_index_s*, %struct.lzma_index_s** %i.addr, align 8, !dbg !753
  %record_count = getelementptr inbounds %struct.lzma_index_s, %struct.lzma_index_s* %2, i32 0, i32 3, !dbg !754
  %3 = load i64, i64* %record_count, align 8, !dbg !754
  %call = call i64 @lzma_index_memusage(i64 %conv, i64 %3) #9, !dbg !755
  ret i64 %call, !dbg !756
}

; Function Attrs: nounwind readonly uwtable
define i64 @lzma_index_block_count(%struct.lzma_index_s* %i) #3 !dbg !175 {
entry:
  %i.addr = alloca %struct.lzma_index_s*, align 8
  store %struct.lzma_index_s* %i, %struct.lzma_index_s** %i.addr, align 8
  call void @llvm.dbg.declare(metadata %struct.lzma_index_s** %i.addr, metadata !757, metadata !341), !dbg !758
  %0 = load %struct.lzma_index_s*, %struct.lzma_index_s** %i.addr, align 8, !dbg !759
  %record_count = getelementptr inbounds %struct.lzma_index_s, %struct.lzma_index_s* %0, i32 0, i32 3, !dbg !760
  %1 = load i64, i64* %record_count, align 8, !dbg !760
  ret i64 %1, !dbg !761
}

; Function Attrs: nounwind readonly uwtable
define i64 @lzma_index_stream_count(%struct.lzma_index_s* %i) #3 !dbg !178 {
entry:
  %i.addr = alloca %struct.lzma_index_s*, align 8
  store %struct.lzma_index_s* %i, %struct.lzma_index_s** %i.addr, align 8
  call void @llvm.dbg.declare(metadata %struct.lzma_index_s** %i.addr, metadata !762, metadata !341), !dbg !763
  %0 = load %struct.lzma_index_s*, %struct.lzma_index_s** %i.addr, align 8, !dbg !764
  %streams = getelementptr inbounds %struct.lzma_index_s, %struct.lzma_index_s* %0, i32 0, i32 0, !dbg !765
  %count = getelementptr inbounds %struct.index_tree, %struct.index_tree* %streams, i32 0, i32 3, !dbg !766
  %1 = load i32, i32* %count, align 8, !dbg !766
  %conv = zext i32 %1 to i64, !dbg !764
  ret i64 %conv, !dbg !767
}

; Function Attrs: nounwind readonly uwtable
define i64 @lzma_index_size(%struct.lzma_index_s* %i) #3 !dbg !179 {
entry:
  %i.addr = alloca %struct.lzma_index_s*, align 8
  store %struct.lzma_index_s* %i, %struct.lzma_index_s** %i.addr, align 8
  call void @llvm.dbg.declare(metadata %struct.lzma_index_s** %i.addr, metadata !768, metadata !341), !dbg !769
  %0 = load %struct.lzma_index_s*, %struct.lzma_index_s** %i.addr, align 8, !dbg !770
  %record_count = getelementptr inbounds %struct.lzma_index_s, %struct.lzma_index_s* %0, i32 0, i32 3, !dbg !771
  %1 = load i64, i64* %record_count, align 8, !dbg !771
  %2 = load %struct.lzma_index_s*, %struct.lzma_index_s** %i.addr, align 8, !dbg !772
  %index_list_size = getelementptr inbounds %struct.lzma_index_s, %struct.lzma_index_s* %2, i32 0, i32 4, !dbg !773
  %3 = load i64, i64* %index_list_size, align 8, !dbg !773
  %call = call i64 @index_size(i64 %1, i64 %3), !dbg !774
  ret i64 %call, !dbg !775
}

; Function Attrs: inlinehint nounwind uwtable
define internal i64 @index_size(i64 %count, i64 %index_list_size) #4 !dbg !299 {
entry:
  %count.addr = alloca i64, align 8
  %index_list_size.addr = alloca i64, align 8
  store i64 %count, i64* %count.addr, align 8
  call void @llvm.dbg.declare(metadata i64* %count.addr, metadata !776, metadata !341), !dbg !777
  store i64 %index_list_size, i64* %index_list_size.addr, align 8
  call void @llvm.dbg.declare(metadata i64* %index_list_size.addr, metadata !778, metadata !341), !dbg !779
  %0 = load i64, i64* %count.addr, align 8, !dbg !780
  %1 = load i64, i64* %index_list_size.addr, align 8, !dbg !781
  %call = call i64 @index_size_unpadded(i64 %0, i64 %1), !dbg !782
  %call1 = call i64 @vli_ceil4(i64 %call), !dbg !783
  ret i64 %call1, !dbg !785
}

; Function Attrs: nounwind readonly uwtable
define i64 @lzma_index_total_size(%struct.lzma_index_s* %i) #3 !dbg !180 {
entry:
  %i.addr = alloca %struct.lzma_index_s*, align 8
  store %struct.lzma_index_s* %i, %struct.lzma_index_s** %i.addr, align 8
  call void @llvm.dbg.declare(metadata %struct.lzma_index_s** %i.addr, metadata !786, metadata !341), !dbg !787
  %0 = load %struct.lzma_index_s*, %struct.lzma_index_s** %i.addr, align 8, !dbg !788
  %total_size = getelementptr inbounds %struct.lzma_index_s, %struct.lzma_index_s* %0, i32 0, i32 2, !dbg !789
  %1 = load i64, i64* %total_size, align 8, !dbg !789
  ret i64 %1, !dbg !790
}

; Function Attrs: nounwind readonly uwtable
define i64 @lzma_index_stream_size(%struct.lzma_index_s* %i) #3 !dbg !181 {
entry:
  %i.addr = alloca %struct.lzma_index_s*, align 8
  store %struct.lzma_index_s* %i, %struct.lzma_index_s** %i.addr, align 8
  call void @llvm.dbg.declare(metadata %struct.lzma_index_s** %i.addr, metadata !791, metadata !341), !dbg !792
  %0 = load %struct.lzma_index_s*, %struct.lzma_index_s** %i.addr, align 8, !dbg !793
  %total_size = getelementptr inbounds %struct.lzma_index_s, %struct.lzma_index_s* %0, i32 0, i32 2, !dbg !794
  %1 = load i64, i64* %total_size, align 8, !dbg !794
  %add = add i64 12, %1, !dbg !795
  %2 = load %struct.lzma_index_s*, %struct.lzma_index_s** %i.addr, align 8, !dbg !796
  %record_count = getelementptr inbounds %struct.lzma_index_s, %struct.lzma_index_s* %2, i32 0, i32 3, !dbg !797
  %3 = load i64, i64* %record_count, align 8, !dbg !797
  %4 = load %struct.lzma_index_s*, %struct.lzma_index_s** %i.addr, align 8, !dbg !798
  %index_list_size = getelementptr inbounds %struct.lzma_index_s, %struct.lzma_index_s* %4, i32 0, i32 4, !dbg !799
  %5 = load i64, i64* %index_list_size, align 8, !dbg !799
  %call = call i64 @index_size(i64 %3, i64 %5), !dbg !800
  %add1 = add i64 %add, %call, !dbg !801
  %add2 = add i64 %add1, 12, !dbg !802
  ret i64 %add2, !dbg !803
}

; Function Attrs: nounwind readonly uwtable
define i64 @lzma_index_file_size(%struct.lzma_index_s* %i) #3 !dbg !182 {
entry:
  %i.addr = alloca %struct.lzma_index_s*, align 8
  %s = alloca %struct.index_stream*, align 8
  %g = alloca %struct.index_group*, align 8
  store %struct.lzma_index_s* %i, %struct.lzma_index_s** %i.addr, align 8
  call void @llvm.dbg.declare(metadata %struct.lzma_index_s** %i.addr, metadata !804, metadata !341), !dbg !805
  call void @llvm.dbg.declare(metadata %struct.index_stream** %s, metadata !806, metadata !341), !dbg !807
  %0 = load %struct.lzma_index_s*, %struct.lzma_index_s** %i.addr, align 8, !dbg !808
  %streams = getelementptr inbounds %struct.lzma_index_s, %struct.lzma_index_s* %0, i32 0, i32 0, !dbg !809
  %rightmost = getelementptr inbounds %struct.index_tree, %struct.index_tree* %streams, i32 0, i32 2, !dbg !810
  %1 = load %struct.index_tree_node_s*, %struct.index_tree_node_s** %rightmost, align 8, !dbg !810
  %2 = bitcast %struct.index_tree_node_s* %1 to %struct.index_stream*, !dbg !811
  store %struct.index_stream* %2, %struct.index_stream** %s, align 8, !dbg !807
  call void @llvm.dbg.declare(metadata %struct.index_group** %g, metadata !812, metadata !341), !dbg !813
  %3 = load %struct.index_stream*, %struct.index_stream** %s, align 8, !dbg !814
  %groups = getelementptr inbounds %struct.index_stream, %struct.index_stream* %3, i32 0, i32 3, !dbg !815
  %rightmost1 = getelementptr inbounds %struct.index_tree, %struct.index_tree* %groups, i32 0, i32 2, !dbg !816
  %4 = load %struct.index_tree_node_s*, %struct.index_tree_node_s** %rightmost1, align 8, !dbg !816
  %5 = bitcast %struct.index_tree_node_s* %4 to %struct.index_group*, !dbg !817
  store %struct.index_group* %5, %struct.index_group** %g, align 8, !dbg !813
  %6 = load %struct.index_stream*, %struct.index_stream** %s, align 8, !dbg !818
  %node = getelementptr inbounds %struct.index_stream, %struct.index_stream* %6, i32 0, i32 0, !dbg !819
  %compressed_base = getelementptr inbounds %struct.index_tree_node_s, %struct.index_tree_node_s* %node, i32 0, i32 1, !dbg !820
  %7 = load i64, i64* %compressed_base, align 8, !dbg !820
  %8 = load %struct.index_group*, %struct.index_group** %g, align 8, !dbg !821
  %cmp = icmp eq %struct.index_group* %8, null, !dbg !822
  br i1 %cmp, label %cond.true, label %cond.false, !dbg !821

cond.true:                                        ; preds = %entry
  br label %cond.end, !dbg !823

cond.false:                                       ; preds = %entry
  %9 = load %struct.index_group*, %struct.index_group** %g, align 8, !dbg !825
  %last = getelementptr inbounds %struct.index_group, %struct.index_group* %9, i32 0, i32 3, !dbg !827
  %10 = load i64, i64* %last, align 8, !dbg !827
  %11 = load %struct.index_group*, %struct.index_group** %g, align 8, !dbg !828
  %records = getelementptr inbounds %struct.index_group, %struct.index_group* %11, i32 0, i32 4, !dbg !829
  %arrayidx = getelementptr inbounds [0 x %struct.index_record], [0 x %struct.index_record]* %records, i64 0, i64 %10, !dbg !828
  %unpadded_sum = getelementptr inbounds %struct.index_record, %struct.index_record* %arrayidx, i32 0, i32 1, !dbg !830
  %12 = load i64, i64* %unpadded_sum, align 8, !dbg !830
  br label %cond.end, !dbg !831

cond.end:                                         ; preds = %cond.false, %cond.true
  %cond = phi i64 [ 0, %cond.true ], [ %12, %cond.false ], !dbg !832
  %13 = load %struct.index_stream*, %struct.index_stream** %s, align 8, !dbg !834
  %record_count = getelementptr inbounds %struct.index_stream, %struct.index_stream* %13, i32 0, i32 4, !dbg !835
  %14 = load i64, i64* %record_count, align 8, !dbg !835
  %15 = load %struct.index_stream*, %struct.index_stream** %s, align 8, !dbg !836
  %index_list_size = getelementptr inbounds %struct.index_stream, %struct.index_stream* %15, i32 0, i32 5, !dbg !837
  %16 = load i64, i64* %index_list_size, align 8, !dbg !837
  %17 = load %struct.index_stream*, %struct.index_stream** %s, align 8, !dbg !838
  %stream_padding = getelementptr inbounds %struct.index_stream, %struct.index_stream* %17, i32 0, i32 7, !dbg !839
  %18 = load i64, i64* %stream_padding, align 8, !dbg !839
  %call = call i64 @index_file_size(i64 %7, i64 %cond, i64 %14, i64 %16, i64 %18), !dbg !840
  ret i64 %call, !dbg !841
}

; Function Attrs: nounwind uwtable
define internal i64 @index_file_size(i64 %compressed_base, i64 %unpadded_sum, i64 %record_count, i64 %index_list_size, i64 %stream_padding) #0 !dbg !303 {
entry:
  %retval = alloca i64, align 8
  %compressed_base.addr = alloca i64, align 8
  %unpadded_sum.addr = alloca i64, align 8
  %record_count.addr = alloca i64, align 8
  %index_list_size.addr = alloca i64, align 8
  %stream_padding.addr = alloca i64, align 8
  %file_size = alloca i64, align 8
  store i64 %compressed_base, i64* %compressed_base.addr, align 8
  call void @llvm.dbg.declare(metadata i64* %compressed_base.addr, metadata !842, metadata !341), !dbg !843
  store i64 %unpadded_sum, i64* %unpadded_sum.addr, align 8
  call void @llvm.dbg.declare(metadata i64* %unpadded_sum.addr, metadata !844, metadata !341), !dbg !845
  store i64 %record_count, i64* %record_count.addr, align 8
  call void @llvm.dbg.declare(metadata i64* %record_count.addr, metadata !846, metadata !341), !dbg !847
  store i64 %index_list_size, i64* %index_list_size.addr, align 8
  call void @llvm.dbg.declare(metadata i64* %index_list_size.addr, metadata !848, metadata !341), !dbg !849
  store i64 %stream_padding, i64* %stream_padding.addr, align 8
  call void @llvm.dbg.declare(metadata i64* %stream_padding.addr, metadata !850, metadata !341), !dbg !851
  call void @llvm.dbg.declare(metadata i64* %file_size, metadata !852, metadata !341), !dbg !853
  %0 = load i64, i64* %compressed_base.addr, align 8, !dbg !854
  %add = add i64 %0, 24, !dbg !855
  %1 = load i64, i64* %stream_padding.addr, align 8, !dbg !856
  %add1 = add i64 %add, %1, !dbg !857
  %2 = load i64, i64* %unpadded_sum.addr, align 8, !dbg !858
  %call = call i64 @vli_ceil4(i64 %2), !dbg !859
  %add2 = add i64 %add1, %call, !dbg !860
  store i64 %add2, i64* %file_size, align 8, !dbg !853
  %3 = load i64, i64* %file_size, align 8, !dbg !861
  %cmp = icmp ugt i64 %3, 9223372036854775807, !dbg !863
  br i1 %cmp, label %if.then, label %if.end, !dbg !864

if.then:                                          ; preds = %entry
  store i64 -1, i64* %retval, align 8, !dbg !865
  br label %return, !dbg !865

if.end:                                           ; preds = %entry
  %4 = load i64, i64* %record_count.addr, align 8, !dbg !866
  %5 = load i64, i64* %index_list_size.addr, align 8, !dbg !867
  %call3 = call i64 @index_size(i64 %4, i64 %5), !dbg !868
  %6 = load i64, i64* %file_size, align 8, !dbg !869
  %add4 = add i64 %6, %call3, !dbg !869
  store i64 %add4, i64* %file_size, align 8, !dbg !869
  %7 = load i64, i64* %file_size, align 8, !dbg !870
  %cmp5 = icmp ugt i64 %7, 9223372036854775807, !dbg !872
  br i1 %cmp5, label %if.then6, label %if.end7, !dbg !873

if.then6:                                         ; preds = %if.end
  store i64 -1, i64* %retval, align 8, !dbg !874
  br label %return, !dbg !874

if.end7:                                          ; preds = %if.end
  %8 = load i64, i64* %file_size, align 8, !dbg !875
  store i64 %8, i64* %retval, align 8, !dbg !876
  br label %return, !dbg !876

return:                                           ; preds = %if.end7, %if.then6, %if.then
  %9 = load i64, i64* %retval, align 8, !dbg !877
  ret i64 %9, !dbg !877
}

; Function Attrs: nounwind readonly uwtable
define i64 @lzma_index_uncompressed_size(%struct.lzma_index_s* %i) #3 !dbg !183 {
entry:
  %i.addr = alloca %struct.lzma_index_s*, align 8
  store %struct.lzma_index_s* %i, %struct.lzma_index_s** %i.addr, align 8
  call void @llvm.dbg.declare(metadata %struct.lzma_index_s** %i.addr, metadata !878, metadata !341), !dbg !879
  %0 = load %struct.lzma_index_s*, %struct.lzma_index_s** %i.addr, align 8, !dbg !880
  %uncompressed_size = getelementptr inbounds %struct.lzma_index_s, %struct.lzma_index_s* %0, i32 0, i32 1, !dbg !881
  %1 = load i64, i64* %uncompressed_size, align 8, !dbg !881
  ret i64 %1, !dbg !882
}

; Function Attrs: nounwind readonly uwtable
define i32 @lzma_index_checks(%struct.lzma_index_s* %i) #3 !dbg !184 {
entry:
  %i.addr = alloca %struct.lzma_index_s*, align 8
  %checks = alloca i32, align 4
  %s = alloca %struct.index_stream*, align 8
  store %struct.lzma_index_s* %i, %struct.lzma_index_s** %i.addr, align 8
  call void @llvm.dbg.declare(metadata %struct.lzma_index_s** %i.addr, metadata !883, metadata !341), !dbg !884
  call void @llvm.dbg.declare(metadata i32* %checks, metadata !885, metadata !341), !dbg !886
  %0 = load %struct.lzma_index_s*, %struct.lzma_index_s** %i.addr, align 8, !dbg !887
  %checks1 = getelementptr inbounds %struct.lzma_index_s, %struct.lzma_index_s* %0, i32 0, i32 6, !dbg !888
  %1 = load i32, i32* %checks1, align 8, !dbg !888
  store i32 %1, i32* %checks, align 4, !dbg !886
  call void @llvm.dbg.declare(metadata %struct.index_stream** %s, metadata !889, metadata !341), !dbg !890
  %2 = load %struct.lzma_index_s*, %struct.lzma_index_s** %i.addr, align 8, !dbg !891
  %streams = getelementptr inbounds %struct.lzma_index_s, %struct.lzma_index_s* %2, i32 0, i32 0, !dbg !892
  %rightmost = getelementptr inbounds %struct.index_tree, %struct.index_tree* %streams, i32 0, i32 2, !dbg !893
  %3 = load %struct.index_tree_node_s*, %struct.index_tree_node_s** %rightmost, align 8, !dbg !893
  %4 = bitcast %struct.index_tree_node_s* %3 to %struct.index_stream*, !dbg !894
  store %struct.index_stream* %4, %struct.index_stream** %s, align 8, !dbg !890
  %5 = load %struct.index_stream*, %struct.index_stream** %s, align 8, !dbg !895
  %stream_flags = getelementptr inbounds %struct.index_stream, %struct.index_stream* %5, i32 0, i32 6, !dbg !897
  %version = getelementptr inbounds %struct.lzma_stream_flags, %struct.lzma_stream_flags* %stream_flags, i32 0, i32 0, !dbg !898
  %6 = load i32, i32* %version, align 8, !dbg !898
  %cmp = icmp ne i32 %6, -1, !dbg !899
  br i1 %cmp, label %if.then, label %if.end, !dbg !900

if.then:                                          ; preds = %entry
  %7 = load %struct.index_stream*, %struct.index_stream** %s, align 8, !dbg !901
  %stream_flags2 = getelementptr inbounds %struct.index_stream, %struct.index_stream* %7, i32 0, i32 6, !dbg !902
  %check = getelementptr inbounds %struct.lzma_stream_flags, %struct.lzma_stream_flags* %stream_flags2, i32 0, i32 2, !dbg !903
  %8 = load i32, i32* %check, align 8, !dbg !903
  %shl = shl i32 1, %8, !dbg !904
  %9 = load i32, i32* %checks, align 4, !dbg !905
  %or = or i32 %9, %shl, !dbg !905
  store i32 %or, i32* %checks, align 4, !dbg !905
  br label %if.end, !dbg !906

if.end:                                           ; preds = %if.then, %entry
  %10 = load i32, i32* %checks, align 4, !dbg !907
  ret i32 %10, !dbg !908
}

; Function Attrs: nounwind uwtable
define i32 @lzma_index_padding_size(%struct.lzma_index_s* %i) #0 !dbg !187 {
entry:
  %i.addr = alloca %struct.lzma_index_s*, align 8
  store %struct.lzma_index_s* %i, %struct.lzma_index_s** %i.addr, align 8
  call void @llvm.dbg.declare(metadata %struct.lzma_index_s** %i.addr, metadata !909, metadata !341), !dbg !910
  %0 = load %struct.lzma_index_s*, %struct.lzma_index_s** %i.addr, align 8, !dbg !911
  %record_count = getelementptr inbounds %struct.lzma_index_s, %struct.lzma_index_s* %0, i32 0, i32 3, !dbg !912
  %1 = load i64, i64* %record_count, align 8, !dbg !912
  %2 = load %struct.lzma_index_s*, %struct.lzma_index_s** %i.addr, align 8, !dbg !913
  %index_list_size = getelementptr inbounds %struct.lzma_index_s, %struct.lzma_index_s* %2, i32 0, i32 4, !dbg !914
  %3 = load i64, i64* %index_list_size, align 8, !dbg !914
  %call = call i64 @index_size_unpadded(i64 %1, i64 %3), !dbg !915
  %sub = sub i64 4, %call, !dbg !916
  %and = and i64 %sub, 3, !dbg !917
  %conv = trunc i64 %and to i32, !dbg !918
  ret i32 %conv, !dbg !919
}

; Function Attrs: inlinehint nounwind uwtable
define internal i64 @index_size_unpadded(i64 %count, i64 %index_list_size) #4 !dbg !306 {
entry:
  %count.addr = alloca i64, align 8
  %index_list_size.addr = alloca i64, align 8
  store i64 %count, i64* %count.addr, align 8
  call void @llvm.dbg.declare(metadata i64* %count.addr, metadata !920, metadata !341), !dbg !921
  store i64 %index_list_size, i64* %index_list_size.addr, align 8
  call void @llvm.dbg.declare(metadata i64* %index_list_size.addr, metadata !922, metadata !341), !dbg !923
  %0 = load i64, i64* %count.addr, align 8, !dbg !924
  %call = call i32 @lzma_vli_size(i64 %0) #10, !dbg !925
  %add = add i32 1, %call, !dbg !926
  %conv = zext i32 %add to i64, !dbg !927
  %1 = load i64, i64* %index_list_size.addr, align 8, !dbg !928
  %add1 = add i64 %conv, %1, !dbg !929
  %add2 = add i64 %add1, 4, !dbg !930
  ret i64 %add2, !dbg !931
}

; Function Attrs: nounwind uwtable
define i32 @lzma_index_stream_flags(%struct.lzma_index_s* %i, %struct.lzma_stream_flags* %stream_flags) #0 !dbg !188 {
entry:
  %retval = alloca i32, align 4
  %i.addr = alloca %struct.lzma_index_s*, align 8
  %stream_flags.addr = alloca %struct.lzma_stream_flags*, align 8
  %s = alloca %struct.index_stream*, align 8
  %ret_ = alloca i32, align 4
  store %struct.lzma_index_s* %i, %struct.lzma_index_s** %i.addr, align 8
  call void @llvm.dbg.declare(metadata %struct.lzma_index_s** %i.addr, metadata !932, metadata !341), !dbg !933
  store %struct.lzma_stream_flags* %stream_flags, %struct.lzma_stream_flags** %stream_flags.addr, align 8
  call void @llvm.dbg.declare(metadata %struct.lzma_stream_flags** %stream_flags.addr, metadata !934, metadata !341), !dbg !935
  call void @llvm.dbg.declare(metadata %struct.index_stream** %s, metadata !936, metadata !341), !dbg !937
  %0 = load %struct.lzma_index_s*, %struct.lzma_index_s** %i.addr, align 8, !dbg !938
  %cmp = icmp eq %struct.lzma_index_s* %0, null, !dbg !940
  br i1 %cmp, label %if.then, label %lor.lhs.false, !dbg !941

lor.lhs.false:                                    ; preds = %entry
  %1 = load %struct.lzma_stream_flags*, %struct.lzma_stream_flags** %stream_flags.addr, align 8, !dbg !942
  %cmp1 = icmp eq %struct.lzma_stream_flags* %1, null, !dbg !944
  br i1 %cmp1, label %if.then, label %if.end, !dbg !945

if.then:                                          ; preds = %lor.lhs.false, %entry
  store i32 11, i32* %retval, align 4, !dbg !946
  br label %return, !dbg !946

if.end:                                           ; preds = %lor.lhs.false
  br label %do.body, !dbg !947

do.body:                                          ; preds = %if.end
  call void @llvm.dbg.declare(metadata i32* %ret_, metadata !948, metadata !341), !dbg !951
  %2 = load %struct.lzma_stream_flags*, %struct.lzma_stream_flags** %stream_flags.addr, align 8, !dbg !952
  %3 = load %struct.lzma_stream_flags*, %struct.lzma_stream_flags** %stream_flags.addr, align 8, !dbg !952
  %call = call i32 @lzma_stream_flags_compare(%struct.lzma_stream_flags* %2, %struct.lzma_stream_flags* %3) #10, !dbg !952
  store i32 %call, i32* %ret_, align 4, !dbg !952
  %4 = load i32, i32* %ret_, align 4, !dbg !952
  %cmp2 = icmp ne i32 %4, 0, !dbg !952
  br i1 %cmp2, label %if.then3, label %if.end4, !dbg !952

if.then3:                                         ; preds = %do.body
  %5 = load i32, i32* %ret_, align 4, !dbg !954
  store i32 %5, i32* %retval, align 4, !dbg !954
  br label %return, !dbg !954

if.end4:                                          ; preds = %do.body
  br label %do.end, !dbg !957

do.end:                                           ; preds = %if.end4
  %6 = load %struct.lzma_index_s*, %struct.lzma_index_s** %i.addr, align 8, !dbg !959
  %streams = getelementptr inbounds %struct.lzma_index_s, %struct.lzma_index_s* %6, i32 0, i32 0, !dbg !960
  %rightmost = getelementptr inbounds %struct.index_tree, %struct.index_tree* %streams, i32 0, i32 2, !dbg !961
  %7 = load %struct.index_tree_node_s*, %struct.index_tree_node_s** %rightmost, align 8, !dbg !961
  %8 = bitcast %struct.index_tree_node_s* %7 to %struct.index_stream*, !dbg !962
  store %struct.index_stream* %8, %struct.index_stream** %s, align 8, !dbg !963
  %9 = load %struct.index_stream*, %struct.index_stream** %s, align 8, !dbg !964
  %stream_flags5 = getelementptr inbounds %struct.index_stream, %struct.index_stream* %9, i32 0, i32 6, !dbg !965
  %10 = load %struct.lzma_stream_flags*, %struct.lzma_stream_flags** %stream_flags.addr, align 8, !dbg !966
  %11 = bitcast %struct.lzma_stream_flags* %stream_flags5 to i8*, !dbg !967
  %12 = bitcast %struct.lzma_stream_flags* %10 to i8*, !dbg !967
  call void @llvm.memcpy.p0i8.p0i8.i64(i8* %11, i8* %12, i64 56, i32 8, i1 false), !dbg !967
  store i32 0, i32* %retval, align 4, !dbg !968
  br label %return, !dbg !968

return:                                           ; preds = %do.end, %if.then3, %if.then
  %13 = load i32, i32* %retval, align 4, !dbg !969
  ret i32 %13, !dbg !969
}

; Function Attrs: nounwind readonly
declare i32 @lzma_stream_flags_compare(%struct.lzma_stream_flags*, %struct.lzma_stream_flags*) #5

; Function Attrs: argmemonly nounwind
declare void @llvm.memcpy.p0i8.p0i8.i64(i8* nocapture, i8* nocapture readonly, i64, i32, i1) #6

; Function Attrs: nounwind uwtable
define i32 @lzma_index_stream_padding(%struct.lzma_index_s* %i, i64 %stream_padding) #0 !dbg !194 {
entry:
  %retval = alloca i32, align 4
  %i.addr = alloca %struct.lzma_index_s*, align 8
  %stream_padding.addr = alloca i64, align 8
  %s = alloca %struct.index_stream*, align 8
  %old_stream_padding = alloca i64, align 8
  store %struct.lzma_index_s* %i, %struct.lzma_index_s** %i.addr, align 8
  call void @llvm.dbg.declare(metadata %struct.lzma_index_s** %i.addr, metadata !970, metadata !341), !dbg !971
  store i64 %stream_padding, i64* %stream_padding.addr, align 8
  call void @llvm.dbg.declare(metadata i64* %stream_padding.addr, metadata !972, metadata !341), !dbg !973
  call void @llvm.dbg.declare(metadata %struct.index_stream** %s, metadata !974, metadata !341), !dbg !975
  call void @llvm.dbg.declare(metadata i64* %old_stream_padding, metadata !976, metadata !341), !dbg !977
  %0 = load %struct.lzma_index_s*, %struct.lzma_index_s** %i.addr, align 8, !dbg !978
  %cmp = icmp eq %struct.lzma_index_s* %0, null, !dbg !980
  br i1 %cmp, label %if.then, label %lor.lhs.false, !dbg !981

lor.lhs.false:                                    ; preds = %entry
  %1 = load i64, i64* %stream_padding.addr, align 8, !dbg !982
  %cmp1 = icmp ugt i64 %1, 9223372036854775807, !dbg !984
  br i1 %cmp1, label %if.then, label %lor.lhs.false2, !dbg !985

lor.lhs.false2:                                   ; preds = %lor.lhs.false
  %2 = load i64, i64* %stream_padding.addr, align 8, !dbg !986
  %and = and i64 %2, 3, !dbg !987
  %cmp3 = icmp ne i64 %and, 0, !dbg !988
  br i1 %cmp3, label %if.then, label %if.end, !dbg !989

if.then:                                          ; preds = %lor.lhs.false2, %lor.lhs.false, %entry
  store i32 11, i32* %retval, align 4, !dbg !991
  br label %return, !dbg !991

if.end:                                           ; preds = %lor.lhs.false2
  %3 = load %struct.lzma_index_s*, %struct.lzma_index_s** %i.addr, align 8, !dbg !992
  %streams = getelementptr inbounds %struct.lzma_index_s, %struct.lzma_index_s* %3, i32 0, i32 0, !dbg !993
  %rightmost = getelementptr inbounds %struct.index_tree, %struct.index_tree* %streams, i32 0, i32 2, !dbg !994
  %4 = load %struct.index_tree_node_s*, %struct.index_tree_node_s** %rightmost, align 8, !dbg !994
  %5 = bitcast %struct.index_tree_node_s* %4 to %struct.index_stream*, !dbg !995
  store %struct.index_stream* %5, %struct.index_stream** %s, align 8, !dbg !996
  %6 = load %struct.index_stream*, %struct.index_stream** %s, align 8, !dbg !997
  %stream_padding4 = getelementptr inbounds %struct.index_stream, %struct.index_stream* %6, i32 0, i32 7, !dbg !998
  %7 = load i64, i64* %stream_padding4, align 8, !dbg !998
  store i64 %7, i64* %old_stream_padding, align 8, !dbg !999
  %8 = load %struct.index_stream*, %struct.index_stream** %s, align 8, !dbg !1000
  %stream_padding5 = getelementptr inbounds %struct.index_stream, %struct.index_stream* %8, i32 0, i32 7, !dbg !1001
  store i64 0, i64* %stream_padding5, align 8, !dbg !1002
  %9 = load %struct.lzma_index_s*, %struct.lzma_index_s** %i.addr, align 8, !dbg !1003
  %call = call i64 @lzma_index_file_size(%struct.lzma_index_s* %9) #10, !dbg !1005
  %10 = load i64, i64* %stream_padding.addr, align 8, !dbg !1006
  %add = add i64 %call, %10, !dbg !1007
  %cmp6 = icmp ugt i64 %add, 9223372036854775807, !dbg !1008
  br i1 %cmp6, label %if.then7, label %if.end9, !dbg !1009

if.then7:                                         ; preds = %if.end
  %11 = load i64, i64* %old_stream_padding, align 8, !dbg !1010
  %12 = load %struct.index_stream*, %struct.index_stream** %s, align 8, !dbg !1012
  %stream_padding8 = getelementptr inbounds %struct.index_stream, %struct.index_stream* %12, i32 0, i32 7, !dbg !1013
  store i64 %11, i64* %stream_padding8, align 8, !dbg !1014
  store i32 9, i32* %retval, align 4, !dbg !1015
  br label %return, !dbg !1015

if.end9:                                          ; preds = %if.end
  %13 = load i64, i64* %stream_padding.addr, align 8, !dbg !1016
  %14 = load %struct.index_stream*, %struct.index_stream** %s, align 8, !dbg !1017
  %stream_padding10 = getelementptr inbounds %struct.index_stream, %struct.index_stream* %14, i32 0, i32 7, !dbg !1018
  store i64 %13, i64* %stream_padding10, align 8, !dbg !1019
  store i32 0, i32* %retval, align 4, !dbg !1020
  br label %return, !dbg !1020

return:                                           ; preds = %if.end9, %if.then7, %if.then
  %15 = load i32, i32* %retval, align 4, !dbg !1021
  ret i32 %15, !dbg !1021
}

; Function Attrs: nounwind uwtable
define i32 @lzma_index_append(%struct.lzma_index_s* %i, %struct.lzma_allocator* %allocator, i64 %unpadded_size, i64 %uncompressed_size) #0 !dbg !197 {
entry:
  %retval = alloca i32, align 4
  %i.addr = alloca %struct.lzma_index_s*, align 8
  %allocator.addr = alloca %struct.lzma_allocator*, align 8
  %unpadded_size.addr = alloca i64, align 8
  %uncompressed_size.addr = alloca i64, align 8
  %s = alloca %struct.index_stream*, align 8
  %g = alloca %struct.index_group*, align 8
  %compressed_base = alloca i64, align 8
  %uncompressed_base = alloca i64, align 8
  %index_list_size_add = alloca i32, align 4
  store %struct.lzma_index_s* %i, %struct.lzma_index_s** %i.addr, align 8
  call void @llvm.dbg.declare(metadata %struct.lzma_index_s** %i.addr, metadata !1022, metadata !341), !dbg !1023
  store %struct.lzma_allocator* %allocator, %struct.lzma_allocator** %allocator.addr, align 8
  call void @llvm.dbg.declare(metadata %struct.lzma_allocator** %allocator.addr, metadata !1024, metadata !341), !dbg !1025
  store i64 %unpadded_size, i64* %unpadded_size.addr, align 8
  call void @llvm.dbg.declare(metadata i64* %unpadded_size.addr, metadata !1026, metadata !341), !dbg !1027
  store i64 %uncompressed_size, i64* %uncompressed_size.addr, align 8
  call void @llvm.dbg.declare(metadata i64* %uncompressed_size.addr, metadata !1028, metadata !341), !dbg !1029
  call void @llvm.dbg.declare(metadata %struct.index_stream** %s, metadata !1030, metadata !341), !dbg !1031
  call void @llvm.dbg.declare(metadata %struct.index_group** %g, metadata !1032, metadata !341), !dbg !1033
  call void @llvm.dbg.declare(metadata i64* %compressed_base, metadata !1034, metadata !341), !dbg !1035
  call void @llvm.dbg.declare(metadata i64* %uncompressed_base, metadata !1036, metadata !341), !dbg !1037
  call void @llvm.dbg.declare(metadata i32* %index_list_size_add, metadata !1038, metadata !341), !dbg !1039
  %0 = load %struct.lzma_index_s*, %struct.lzma_index_s** %i.addr, align 8, !dbg !1040
  %cmp = icmp eq %struct.lzma_index_s* %0, null, !dbg !1042
  br i1 %cmp, label %if.then, label %lor.lhs.false, !dbg !1043

lor.lhs.false:                                    ; preds = %entry
  %1 = load i64, i64* %unpadded_size.addr, align 8, !dbg !1044
  %cmp1 = icmp ult i64 %1, 5, !dbg !1046
  br i1 %cmp1, label %if.then, label %lor.lhs.false2, !dbg !1047

lor.lhs.false2:                                   ; preds = %lor.lhs.false
  %2 = load i64, i64* %unpadded_size.addr, align 8, !dbg !1048
  %cmp3 = icmp ugt i64 %2, 9223372036854775804, !dbg !1049
  br i1 %cmp3, label %if.then, label %lor.lhs.false4, !dbg !1050

lor.lhs.false4:                                   ; preds = %lor.lhs.false2
  %3 = load i64, i64* %uncompressed_size.addr, align 8, !dbg !1051
  %cmp5 = icmp ugt i64 %3, 9223372036854775807, !dbg !1052
  br i1 %cmp5, label %if.then, label %if.end, !dbg !1053

if.then:                                          ; preds = %lor.lhs.false4, %lor.lhs.false2, %lor.lhs.false, %entry
  store i32 11, i32* %retval, align 4, !dbg !1055
  br label %return, !dbg !1055

if.end:                                           ; preds = %lor.lhs.false4
  %4 = load %struct.lzma_index_s*, %struct.lzma_index_s** %i.addr, align 8, !dbg !1056
  %streams = getelementptr inbounds %struct.lzma_index_s, %struct.lzma_index_s* %4, i32 0, i32 0, !dbg !1057
  %rightmost = getelementptr inbounds %struct.index_tree, %struct.index_tree* %streams, i32 0, i32 2, !dbg !1058
  %5 = load %struct.index_tree_node_s*, %struct.index_tree_node_s** %rightmost, align 8, !dbg !1058
  %6 = bitcast %struct.index_tree_node_s* %5 to %struct.index_stream*, !dbg !1059
  store %struct.index_stream* %6, %struct.index_stream** %s, align 8, !dbg !1060
  %7 = load %struct.index_stream*, %struct.index_stream** %s, align 8, !dbg !1061
  %groups = getelementptr inbounds %struct.index_stream, %struct.index_stream* %7, i32 0, i32 3, !dbg !1062
  %rightmost6 = getelementptr inbounds %struct.index_tree, %struct.index_tree* %groups, i32 0, i32 2, !dbg !1063
  %8 = load %struct.index_tree_node_s*, %struct.index_tree_node_s** %rightmost6, align 8, !dbg !1063
  %9 = bitcast %struct.index_tree_node_s* %8 to %struct.index_group*, !dbg !1064
  store %struct.index_group* %9, %struct.index_group** %g, align 8, !dbg !1065
  %10 = load %struct.index_group*, %struct.index_group** %g, align 8, !dbg !1066
  %cmp7 = icmp eq %struct.index_group* %10, null, !dbg !1067
  br i1 %cmp7, label %cond.true, label %cond.false, !dbg !1066

cond.true:                                        ; preds = %if.end
  br label %cond.end, !dbg !1068

cond.false:                                       ; preds = %if.end
  %11 = load %struct.index_group*, %struct.index_group** %g, align 8, !dbg !1070
  %last = getelementptr inbounds %struct.index_group, %struct.index_group* %11, i32 0, i32 3, !dbg !1071
  %12 = load i64, i64* %last, align 8, !dbg !1071
  %13 = load %struct.index_group*, %struct.index_group** %g, align 8, !dbg !1072
  %records = getelementptr inbounds %struct.index_group, %struct.index_group* %13, i32 0, i32 4, !dbg !1073
  %arrayidx = getelementptr inbounds [0 x %struct.index_record], [0 x %struct.index_record]* %records, i64 0, i64 %12, !dbg !1072
  %unpadded_sum = getelementptr inbounds %struct.index_record, %struct.index_record* %arrayidx, i32 0, i32 1, !dbg !1074
  %14 = load i64, i64* %unpadded_sum, align 8, !dbg !1074
  %call = call i64 @vli_ceil4(i64 %14), !dbg !1075
  br label %cond.end, !dbg !1076

cond.end:                                         ; preds = %cond.false, %cond.true
  %cond = phi i64 [ 0, %cond.true ], [ %call, %cond.false ], !dbg !1077
  store i64 %cond, i64* %compressed_base, align 8, !dbg !1079
  %15 = load %struct.index_group*, %struct.index_group** %g, align 8, !dbg !1080
  %cmp8 = icmp eq %struct.index_group* %15, null, !dbg !1081
  br i1 %cmp8, label %cond.true9, label %cond.false10, !dbg !1080

cond.true9:                                       ; preds = %cond.end
  br label %cond.end14, !dbg !1082

cond.false10:                                     ; preds = %cond.end
  %16 = load %struct.index_group*, %struct.index_group** %g, align 8, !dbg !1083
  %last11 = getelementptr inbounds %struct.index_group, %struct.index_group* %16, i32 0, i32 3, !dbg !1084
  %17 = load i64, i64* %last11, align 8, !dbg !1084
  %18 = load %struct.index_group*, %struct.index_group** %g, align 8, !dbg !1085
  %records12 = getelementptr inbounds %struct.index_group, %struct.index_group* %18, i32 0, i32 4, !dbg !1086
  %arrayidx13 = getelementptr inbounds [0 x %struct.index_record], [0 x %struct.index_record]* %records12, i64 0, i64 %17, !dbg !1085
  %uncompressed_sum = getelementptr inbounds %struct.index_record, %struct.index_record* %arrayidx13, i32 0, i32 0, !dbg !1087
  %19 = load i64, i64* %uncompressed_sum, align 8, !dbg !1087
  br label %cond.end14, !dbg !1088

cond.end14:                                       ; preds = %cond.false10, %cond.true9
  %cond15 = phi i64 [ 0, %cond.true9 ], [ %19, %cond.false10 ], !dbg !1089
  store i64 %cond15, i64* %uncompressed_base, align 8, !dbg !1090
  %20 = load i64, i64* %unpadded_size.addr, align 8, !dbg !1091
  %call16 = call i32 @lzma_vli_size(i64 %20) #10, !dbg !1092
  %21 = load i64, i64* %uncompressed_size.addr, align 8, !dbg !1093
  %call17 = call i32 @lzma_vli_size(i64 %21) #10, !dbg !1094
  %add = add i32 %call16, %call17, !dbg !1095
  store i32 %add, i32* %index_list_size_add, align 4, !dbg !1096
  %22 = load %struct.index_stream*, %struct.index_stream** %s, align 8, !dbg !1097
  %node = getelementptr inbounds %struct.index_stream, %struct.index_stream* %22, i32 0, i32 0, !dbg !1099
  %compressed_base18 = getelementptr inbounds %struct.index_tree_node_s, %struct.index_tree_node_s* %node, i32 0, i32 1, !dbg !1100
  %23 = load i64, i64* %compressed_base18, align 8, !dbg !1100
  %24 = load i64, i64* %compressed_base, align 8, !dbg !1101
  %25 = load i64, i64* %unpadded_size.addr, align 8, !dbg !1102
  %add19 = add i64 %24, %25, !dbg !1103
  %26 = load %struct.index_stream*, %struct.index_stream** %s, align 8, !dbg !1104
  %record_count = getelementptr inbounds %struct.index_stream, %struct.index_stream* %26, i32 0, i32 4, !dbg !1105
  %27 = load i64, i64* %record_count, align 8, !dbg !1105
  %add20 = add i64 %27, 1, !dbg !1106
  %28 = load %struct.index_stream*, %struct.index_stream** %s, align 8, !dbg !1107
  %index_list_size = getelementptr inbounds %struct.index_stream, %struct.index_stream* %28, i32 0, i32 5, !dbg !1108
  %29 = load i64, i64* %index_list_size, align 8, !dbg !1108
  %30 = load i32, i32* %index_list_size_add, align 4, !dbg !1109
  %conv = zext i32 %30 to i64, !dbg !1109
  %add21 = add i64 %29, %conv, !dbg !1110
  %31 = load %struct.index_stream*, %struct.index_stream** %s, align 8, !dbg !1111
  %stream_padding = getelementptr inbounds %struct.index_stream, %struct.index_stream* %31, i32 0, i32 7, !dbg !1112
  %32 = load i64, i64* %stream_padding, align 8, !dbg !1112
  %call22 = call i64 @index_file_size(i64 %23, i64 %add19, i64 %add20, i64 %add21, i64 %32), !dbg !1113
  %cmp23 = icmp eq i64 %call22, -1, !dbg !1114
  br i1 %cmp23, label %if.then25, label %if.end26, !dbg !1115

if.then25:                                        ; preds = %cond.end14
  store i32 9, i32* %retval, align 4, !dbg !1116
  br label %return, !dbg !1116

if.end26:                                         ; preds = %cond.end14
  %33 = load %struct.lzma_index_s*, %struct.lzma_index_s** %i.addr, align 8, !dbg !1117
  %record_count27 = getelementptr inbounds %struct.lzma_index_s, %struct.lzma_index_s* %33, i32 0, i32 3, !dbg !1119
  %34 = load i64, i64* %record_count27, align 8, !dbg !1119
  %add28 = add i64 %34, 1, !dbg !1120
  %35 = load %struct.lzma_index_s*, %struct.lzma_index_s** %i.addr, align 8, !dbg !1121
  %index_list_size29 = getelementptr inbounds %struct.lzma_index_s, %struct.lzma_index_s* %35, i32 0, i32 4, !dbg !1122
  %36 = load i64, i64* %index_list_size29, align 8, !dbg !1122
  %37 = load i32, i32* %index_list_size_add, align 4, !dbg !1123
  %conv30 = zext i32 %37 to i64, !dbg !1123
  %add31 = add i64 %36, %conv30, !dbg !1124
  %call32 = call i64 @index_size(i64 %add28, i64 %add31), !dbg !1125
  %cmp33 = icmp ugt i64 %call32, 17179869184, !dbg !1126
  br i1 %cmp33, label %if.then35, label %if.end36, !dbg !1127

if.then35:                                        ; preds = %if.end26
  store i32 9, i32* %retval, align 4, !dbg !1128
  br label %return, !dbg !1128

if.end36:                                         ; preds = %if.end26
  %38 = load %struct.index_group*, %struct.index_group** %g, align 8, !dbg !1129
  %cmp37 = icmp ne %struct.index_group* %38, null, !dbg !1131
  br i1 %cmp37, label %land.lhs.true, label %if.else, !dbg !1132

land.lhs.true:                                    ; preds = %if.end36
  %39 = load %struct.index_group*, %struct.index_group** %g, align 8, !dbg !1133
  %last39 = getelementptr inbounds %struct.index_group, %struct.index_group* %39, i32 0, i32 3, !dbg !1135
  %40 = load i64, i64* %last39, align 8, !dbg !1135
  %add40 = add i64 %40, 1, !dbg !1136
  %41 = load %struct.index_group*, %struct.index_group** %g, align 8, !dbg !1137
  %allocated = getelementptr inbounds %struct.index_group, %struct.index_group* %41, i32 0, i32 2, !dbg !1138
  %42 = load i64, i64* %allocated, align 8, !dbg !1138
  %cmp41 = icmp ult i64 %add40, %42, !dbg !1139
  br i1 %cmp41, label %if.then43, label %if.else, !dbg !1140

if.then43:                                        ; preds = %land.lhs.true
  %43 = load %struct.index_group*, %struct.index_group** %g, align 8, !dbg !1141
  %last44 = getelementptr inbounds %struct.index_group, %struct.index_group* %43, i32 0, i32 3, !dbg !1143
  %44 = load i64, i64* %last44, align 8, !dbg !1144
  %inc = add i64 %44, 1, !dbg !1144
  store i64 %inc, i64* %last44, align 8, !dbg !1144
  br label %if.end63, !dbg !1145

if.else:                                          ; preds = %land.lhs.true, %if.end36
  %45 = load %struct.lzma_index_s*, %struct.lzma_index_s** %i.addr, align 8, !dbg !1146
  %prealloc = getelementptr inbounds %struct.lzma_index_s, %struct.lzma_index_s* %45, i32 0, i32 5, !dbg !1148
  %46 = load i64, i64* %prealloc, align 8, !dbg !1148
  %mul = mul i64 %46, 16, !dbg !1149
  %add45 = add i64 64, %mul, !dbg !1150
  %47 = load %struct.lzma_allocator*, %struct.lzma_allocator** %allocator.addr, align 8, !dbg !1151
  %call46 = call noalias i8* @lzma_alloc(i64 %add45, %struct.lzma_allocator* %47), !dbg !1152
  %48 = bitcast i8* %call46 to %struct.index_group*, !dbg !1152
  store %struct.index_group* %48, %struct.index_group** %g, align 8, !dbg !1153
  %49 = load %struct.index_group*, %struct.index_group** %g, align 8, !dbg !1154
  %cmp47 = icmp eq %struct.index_group* %49, null, !dbg !1156
  br i1 %cmp47, label %if.then49, label %if.end50, !dbg !1157

if.then49:                                        ; preds = %if.else
  store i32 5, i32* %retval, align 4, !dbg !1158
  br label %return, !dbg !1158

if.end50:                                         ; preds = %if.else
  %50 = load %struct.index_group*, %struct.index_group** %g, align 8, !dbg !1159
  %last51 = getelementptr inbounds %struct.index_group, %struct.index_group* %50, i32 0, i32 3, !dbg !1160
  store i64 0, i64* %last51, align 8, !dbg !1161
  %51 = load %struct.lzma_index_s*, %struct.lzma_index_s** %i.addr, align 8, !dbg !1162
  %prealloc52 = getelementptr inbounds %struct.lzma_index_s, %struct.lzma_index_s* %51, i32 0, i32 5, !dbg !1163
  %52 = load i64, i64* %prealloc52, align 8, !dbg !1163
  %53 = load %struct.index_group*, %struct.index_group** %g, align 8, !dbg !1164
  %allocated53 = getelementptr inbounds %struct.index_group, %struct.index_group* %53, i32 0, i32 2, !dbg !1165
  store i64 %52, i64* %allocated53, align 8, !dbg !1166
  %54 = load %struct.lzma_index_s*, %struct.lzma_index_s** %i.addr, align 8, !dbg !1167
  %prealloc54 = getelementptr inbounds %struct.lzma_index_s, %struct.lzma_index_s* %54, i32 0, i32 5, !dbg !1168
  store i64 512, i64* %prealloc54, align 8, !dbg !1169
  %55 = load i64, i64* %uncompressed_base, align 8, !dbg !1170
  %56 = load %struct.index_group*, %struct.index_group** %g, align 8, !dbg !1171
  %node55 = getelementptr inbounds %struct.index_group, %struct.index_group* %56, i32 0, i32 0, !dbg !1172
  %uncompressed_base56 = getelementptr inbounds %struct.index_tree_node_s, %struct.index_tree_node_s* %node55, i32 0, i32 0, !dbg !1173
  store i64 %55, i64* %uncompressed_base56, align 8, !dbg !1174
  %57 = load i64, i64* %compressed_base, align 8, !dbg !1175
  %58 = load %struct.index_group*, %struct.index_group** %g, align 8, !dbg !1176
  %node57 = getelementptr inbounds %struct.index_group, %struct.index_group* %58, i32 0, i32 0, !dbg !1177
  %compressed_base58 = getelementptr inbounds %struct.index_tree_node_s, %struct.index_tree_node_s* %node57, i32 0, i32 1, !dbg !1178
  store i64 %57, i64* %compressed_base58, align 8, !dbg !1179
  %59 = load %struct.index_stream*, %struct.index_stream** %s, align 8, !dbg !1180
  %record_count59 = getelementptr inbounds %struct.index_stream, %struct.index_stream* %59, i32 0, i32 4, !dbg !1181
  %60 = load i64, i64* %record_count59, align 8, !dbg !1181
  %add60 = add i64 %60, 1, !dbg !1182
  %61 = load %struct.index_group*, %struct.index_group** %g, align 8, !dbg !1183
  %number_base = getelementptr inbounds %struct.index_group, %struct.index_group* %61, i32 0, i32 1, !dbg !1184
  store i64 %add60, i64* %number_base, align 8, !dbg !1185
  %62 = load %struct.index_stream*, %struct.index_stream** %s, align 8, !dbg !1186
  %groups61 = getelementptr inbounds %struct.index_stream, %struct.index_stream* %62, i32 0, i32 3, !dbg !1187
  %63 = load %struct.index_group*, %struct.index_group** %g, align 8, !dbg !1188
  %node62 = getelementptr inbounds %struct.index_group, %struct.index_group* %63, i32 0, i32 0, !dbg !1189
  call void @index_tree_append(%struct.index_tree* %groups61, %struct.index_tree_node_s* %node62), !dbg !1190
  br label %if.end63

if.end63:                                         ; preds = %if.end50, %if.then43
  %64 = load i64, i64* %uncompressed_base, align 8, !dbg !1191
  %65 = load i64, i64* %uncompressed_size.addr, align 8, !dbg !1192
  %add64 = add i64 %64, %65, !dbg !1193
  %66 = load %struct.index_group*, %struct.index_group** %g, align 8, !dbg !1194
  %last65 = getelementptr inbounds %struct.index_group, %struct.index_group* %66, i32 0, i32 3, !dbg !1195
  %67 = load i64, i64* %last65, align 8, !dbg !1195
  %68 = load %struct.index_group*, %struct.index_group** %g, align 8, !dbg !1196
  %records66 = getelementptr inbounds %struct.index_group, %struct.index_group* %68, i32 0, i32 4, !dbg !1197
  %arrayidx67 = getelementptr inbounds [0 x %struct.index_record], [0 x %struct.index_record]* %records66, i64 0, i64 %67, !dbg !1196
  %uncompressed_sum68 = getelementptr inbounds %struct.index_record, %struct.index_record* %arrayidx67, i32 0, i32 0, !dbg !1198
  store i64 %add64, i64* %uncompressed_sum68, align 8, !dbg !1199
  %69 = load i64, i64* %compressed_base, align 8, !dbg !1200
  %70 = load i64, i64* %unpadded_size.addr, align 8, !dbg !1201
  %add69 = add i64 %69, %70, !dbg !1202
  %71 = load %struct.index_group*, %struct.index_group** %g, align 8, !dbg !1203
  %last70 = getelementptr inbounds %struct.index_group, %struct.index_group* %71, i32 0, i32 3, !dbg !1204
  %72 = load i64, i64* %last70, align 8, !dbg !1204
  %73 = load %struct.index_group*, %struct.index_group** %g, align 8, !dbg !1205
  %records71 = getelementptr inbounds %struct.index_group, %struct.index_group* %73, i32 0, i32 4, !dbg !1206
  %arrayidx72 = getelementptr inbounds [0 x %struct.index_record], [0 x %struct.index_record]* %records71, i64 0, i64 %72, !dbg !1205
  %unpadded_sum73 = getelementptr inbounds %struct.index_record, %struct.index_record* %arrayidx72, i32 0, i32 1, !dbg !1207
  store i64 %add69, i64* %unpadded_sum73, align 8, !dbg !1208
  %74 = load %struct.index_stream*, %struct.index_stream** %s, align 8, !dbg !1209
  %record_count74 = getelementptr inbounds %struct.index_stream, %struct.index_stream* %74, i32 0, i32 4, !dbg !1210
  %75 = load i64, i64* %record_count74, align 8, !dbg !1211
  %inc75 = add i64 %75, 1, !dbg !1211
  store i64 %inc75, i64* %record_count74, align 8, !dbg !1211
  %76 = load i32, i32* %index_list_size_add, align 4, !dbg !1212
  %conv76 = zext i32 %76 to i64, !dbg !1212
  %77 = load %struct.index_stream*, %struct.index_stream** %s, align 8, !dbg !1213
  %index_list_size77 = getelementptr inbounds %struct.index_stream, %struct.index_stream* %77, i32 0, i32 5, !dbg !1214
  %78 = load i64, i64* %index_list_size77, align 8, !dbg !1215
  %add78 = add i64 %78, %conv76, !dbg !1215
  store i64 %add78, i64* %index_list_size77, align 8, !dbg !1215
  %79 = load i64, i64* %unpadded_size.addr, align 8, !dbg !1216
  %call79 = call i64 @vli_ceil4(i64 %79), !dbg !1217
  %80 = load %struct.lzma_index_s*, %struct.lzma_index_s** %i.addr, align 8, !dbg !1218
  %total_size = getelementptr inbounds %struct.lzma_index_s, %struct.lzma_index_s* %80, i32 0, i32 2, !dbg !1219
  %81 = load i64, i64* %total_size, align 8, !dbg !1220
  %add80 = add i64 %81, %call79, !dbg !1220
  store i64 %add80, i64* %total_size, align 8, !dbg !1220
  %82 = load i64, i64* %uncompressed_size.addr, align 8, !dbg !1221
  %83 = load %struct.lzma_index_s*, %struct.lzma_index_s** %i.addr, align 8, !dbg !1222
  %uncompressed_size81 = getelementptr inbounds %struct.lzma_index_s, %struct.lzma_index_s* %83, i32 0, i32 1, !dbg !1223
  %84 = load i64, i64* %uncompressed_size81, align 8, !dbg !1224
  %add82 = add i64 %84, %82, !dbg !1224
  store i64 %add82, i64* %uncompressed_size81, align 8, !dbg !1224
  %85 = load %struct.lzma_index_s*, %struct.lzma_index_s** %i.addr, align 8, !dbg !1225
  %record_count83 = getelementptr inbounds %struct.lzma_index_s, %struct.lzma_index_s* %85, i32 0, i32 3, !dbg !1226
  %86 = load i64, i64* %record_count83, align 8, !dbg !1227
  %inc84 = add i64 %86, 1, !dbg !1227
  store i64 %inc84, i64* %record_count83, align 8, !dbg !1227
  %87 = load i32, i32* %index_list_size_add, align 4, !dbg !1228
  %conv85 = zext i32 %87 to i64, !dbg !1228
  %88 = load %struct.lzma_index_s*, %struct.lzma_index_s** %i.addr, align 8, !dbg !1229
  %index_list_size86 = getelementptr inbounds %struct.lzma_index_s, %struct.lzma_index_s* %88, i32 0, i32 4, !dbg !1230
  %89 = load i64, i64* %index_list_size86, align 8, !dbg !1231
  %add87 = add i64 %89, %conv85, !dbg !1231
  store i64 %add87, i64* %index_list_size86, align 8, !dbg !1231
  store i32 0, i32* %retval, align 4, !dbg !1232
  br label %return, !dbg !1232

return:                                           ; preds = %if.end63, %if.then49, %if.then35, %if.then25, %if.then
  %90 = load i32, i32* %retval, align 4, !dbg !1233
  ret i32 %90, !dbg !1233
}

; Function Attrs: inlinehint nounwind uwtable
define internal i64 @vli_ceil4(i64 %vli) #4 !dbg !307 {
entry:
  %vli.addr = alloca i64, align 8
  store i64 %vli, i64* %vli.addr, align 8
  call void @llvm.dbg.declare(metadata i64* %vli.addr, metadata !1234, metadata !341), !dbg !1235
  %0 = load i64, i64* %vli.addr, align 8, !dbg !1236
  %cmp = icmp ule i64 %0, 9223372036854775807, !dbg !1236
  br i1 %cmp, label %cond.true, label %cond.false, !dbg !1236

cond.true:                                        ; preds = %entry
  br label %cond.end, !dbg !1237

cond.false:                                       ; preds = %entry
  call void @__assert_fail(i8* getelementptr inbounds ([38 x i8], [38 x i8]* @.str.10, i32 0, i32 0), i8* getelementptr inbounds ([77 x i8], [77 x i8]* @.str.11, i32 0, i32 0), i32 41, i8* getelementptr inbounds ([29 x i8], [29 x i8]* @__PRETTY_FUNCTION__.vli_ceil4, i32 0, i32 0)) #8, !dbg !1239
  unreachable, !dbg !1239
                                                  ; No predecessors!
  br label %cond.end, !dbg !1241

cond.end:                                         ; preds = %1, %cond.true
  %2 = load i64, i64* %vli.addr, align 8, !dbg !1243
  %add = add i64 %2, 3, !dbg !1244
  %and = and i64 %add, -4, !dbg !1245
  ret i64 %and, !dbg !1246
}

; Function Attrs: nounwind readonly
declare i32 @lzma_vli_size(i64) #5

declare noalias i8* @lzma_alloc(i64, %struct.lzma_allocator*) #2

; Function Attrs: nounwind uwtable
define i32 @lzma_index_cat(%struct.lzma_index_s* noalias %dest, %struct.lzma_index_s* noalias %src, %struct.lzma_allocator* %allocator) #0 !dbg !200 {
entry:
  %retval = alloca i32, align 4
  %dest.addr = alloca %struct.lzma_index_s*, align 8
  %src.addr = alloca %struct.lzma_index_s*, align 8
  %allocator.addr = alloca %struct.lzma_allocator*, align 8
  %info = alloca %struct.index_cat_info, align 8
  %dest_file_size = alloca i64, align 8
  %dest_size = alloca i64, align 8
  %src_size = alloca i64, align 8
  %s = alloca %struct.index_stream*, align 8
  %g = alloca %struct.index_group*, align 8
  %newg = alloca %struct.index_group*, align 8
  store %struct.lzma_index_s* %dest, %struct.lzma_index_s** %dest.addr, align 8
  call void @llvm.dbg.declare(metadata %struct.lzma_index_s** %dest.addr, metadata !1247, metadata !341), !dbg !1248
  store %struct.lzma_index_s* %src, %struct.lzma_index_s** %src.addr, align 8
  call void @llvm.dbg.declare(metadata %struct.lzma_index_s** %src.addr, metadata !1249, metadata !341), !dbg !1250
  store %struct.lzma_allocator* %allocator, %struct.lzma_allocator** %allocator.addr, align 8
  call void @llvm.dbg.declare(metadata %struct.lzma_allocator** %allocator.addr, metadata !1251, metadata !341), !dbg !1252
  call void @llvm.dbg.declare(metadata %struct.index_cat_info* %info, metadata !1253, metadata !341), !dbg !1254
  call void @llvm.dbg.declare(metadata i64* %dest_file_size, metadata !1255, metadata !341), !dbg !1256
  %0 = load %struct.lzma_index_s*, %struct.lzma_index_s** %dest.addr, align 8, !dbg !1257
  %call = call i64 @lzma_index_file_size(%struct.lzma_index_s* %0) #10, !dbg !1258
  store i64 %call, i64* %dest_file_size, align 8, !dbg !1256
  %1 = load i64, i64* %dest_file_size, align 8, !dbg !1259
  %2 = load %struct.lzma_index_s*, %struct.lzma_index_s** %src.addr, align 8, !dbg !1261
  %call1 = call i64 @lzma_index_file_size(%struct.lzma_index_s* %2) #10, !dbg !1262
  %add = add i64 %1, %call1, !dbg !1263
  %cmp = icmp ugt i64 %add, 9223372036854775807, !dbg !1264
  br i1 %cmp, label %if.then, label %lor.lhs.false, !dbg !1265

lor.lhs.false:                                    ; preds = %entry
  %3 = load %struct.lzma_index_s*, %struct.lzma_index_s** %dest.addr, align 8, !dbg !1266
  %uncompressed_size = getelementptr inbounds %struct.lzma_index_s, %struct.lzma_index_s* %3, i32 0, i32 1, !dbg !1268
  %4 = load i64, i64* %uncompressed_size, align 8, !dbg !1268
  %5 = load %struct.lzma_index_s*, %struct.lzma_index_s** %src.addr, align 8, !dbg !1269
  %uncompressed_size2 = getelementptr inbounds %struct.lzma_index_s, %struct.lzma_index_s* %5, i32 0, i32 1, !dbg !1270
  %6 = load i64, i64* %uncompressed_size2, align 8, !dbg !1270
  %add3 = add i64 %4, %6, !dbg !1271
  %cmp4 = icmp ugt i64 %add3, 9223372036854775807, !dbg !1272
  br i1 %cmp4, label %if.then, label %if.end, !dbg !1273

if.then:                                          ; preds = %lor.lhs.false, %entry
  store i32 9, i32* %retval, align 4, !dbg !1275
  br label %return, !dbg !1275

if.end:                                           ; preds = %lor.lhs.false
  call void @llvm.dbg.declare(metadata i64* %dest_size, metadata !1276, metadata !341), !dbg !1278
  %7 = load %struct.lzma_index_s*, %struct.lzma_index_s** %dest.addr, align 8, !dbg !1279
  %record_count = getelementptr inbounds %struct.lzma_index_s, %struct.lzma_index_s* %7, i32 0, i32 3, !dbg !1280
  %8 = load i64, i64* %record_count, align 8, !dbg !1280
  %9 = load %struct.lzma_index_s*, %struct.lzma_index_s** %dest.addr, align 8, !dbg !1281
  %index_list_size = getelementptr inbounds %struct.lzma_index_s, %struct.lzma_index_s* %9, i32 0, i32 4, !dbg !1282
  %10 = load i64, i64* %index_list_size, align 8, !dbg !1282
  %call5 = call i64 @index_size_unpadded(i64 %8, i64 %10), !dbg !1283
  store i64 %call5, i64* %dest_size, align 8, !dbg !1278
  call void @llvm.dbg.declare(metadata i64* %src_size, metadata !1284, metadata !341), !dbg !1285
  %11 = load %struct.lzma_index_s*, %struct.lzma_index_s** %src.addr, align 8, !dbg !1286
  %record_count6 = getelementptr inbounds %struct.lzma_index_s, %struct.lzma_index_s* %11, i32 0, i32 3, !dbg !1287
  %12 = load i64, i64* %record_count6, align 8, !dbg !1287
  %13 = load %struct.lzma_index_s*, %struct.lzma_index_s** %src.addr, align 8, !dbg !1288
  %index_list_size7 = getelementptr inbounds %struct.lzma_index_s, %struct.lzma_index_s* %13, i32 0, i32 4, !dbg !1289
  %14 = load i64, i64* %index_list_size7, align 8, !dbg !1289
  %call8 = call i64 @index_size_unpadded(i64 %12, i64 %14), !dbg !1290
  store i64 %call8, i64* %src_size, align 8, !dbg !1285
  %15 = load i64, i64* %dest_size, align 8, !dbg !1291
  %16 = load i64, i64* %src_size, align 8, !dbg !1293
  %add9 = add i64 %15, %16, !dbg !1294
  %call10 = call i64 @vli_ceil4(i64 %add9), !dbg !1295
  %cmp11 = icmp ugt i64 %call10, 17179869184, !dbg !1296
  br i1 %cmp11, label %if.then12, label %if.end13, !dbg !1297

if.then12:                                        ; preds = %if.end
  store i32 9, i32* %retval, align 4, !dbg !1298
  br label %return, !dbg !1298

if.end13:                                         ; preds = %if.end
  call void @llvm.dbg.declare(metadata %struct.index_stream** %s, metadata !1299, metadata !341), !dbg !1301
  %17 = load %struct.lzma_index_s*, %struct.lzma_index_s** %dest.addr, align 8, !dbg !1302
  %streams = getelementptr inbounds %struct.lzma_index_s, %struct.lzma_index_s* %17, i32 0, i32 0, !dbg !1303
  %rightmost = getelementptr inbounds %struct.index_tree, %struct.index_tree* %streams, i32 0, i32 2, !dbg !1304
  %18 = load %struct.index_tree_node_s*, %struct.index_tree_node_s** %rightmost, align 8, !dbg !1304
  %19 = bitcast %struct.index_tree_node_s* %18 to %struct.index_stream*, !dbg !1305
  store %struct.index_stream* %19, %struct.index_stream** %s, align 8, !dbg !1301
  call void @llvm.dbg.declare(metadata %struct.index_group** %g, metadata !1306, metadata !341), !dbg !1307
  %20 = load %struct.index_stream*, %struct.index_stream** %s, align 8, !dbg !1308
  %groups = getelementptr inbounds %struct.index_stream, %struct.index_stream* %20, i32 0, i32 3, !dbg !1309
  %rightmost14 = getelementptr inbounds %struct.index_tree, %struct.index_tree* %groups, i32 0, i32 2, !dbg !1310
  %21 = load %struct.index_tree_node_s*, %struct.index_tree_node_s** %rightmost14, align 8, !dbg !1310
  %22 = bitcast %struct.index_tree_node_s* %21 to %struct.index_group*, !dbg !1311
  store %struct.index_group* %22, %struct.index_group** %g, align 8, !dbg !1307
  %23 = load %struct.index_group*, %struct.index_group** %g, align 8, !dbg !1312
  %cmp15 = icmp ne %struct.index_group* %23, null, !dbg !1314
  br i1 %cmp15, label %land.lhs.true, label %if.end86, !dbg !1315

land.lhs.true:                                    ; preds = %if.end13
  %24 = load %struct.index_group*, %struct.index_group** %g, align 8, !dbg !1316
  %last = getelementptr inbounds %struct.index_group, %struct.index_group* %24, i32 0, i32 3, !dbg !1318
  %25 = load i64, i64* %last, align 8, !dbg !1318
  %add16 = add i64 %25, 1, !dbg !1319
  %26 = load %struct.index_group*, %struct.index_group** %g, align 8, !dbg !1320
  %allocated = getelementptr inbounds %struct.index_group, %struct.index_group* %26, i32 0, i32 2, !dbg !1321
  %27 = load i64, i64* %allocated, align 8, !dbg !1321
  %cmp17 = icmp ult i64 %add16, %27, !dbg !1322
  br i1 %cmp17, label %if.then18, label %if.end86, !dbg !1323

if.then18:                                        ; preds = %land.lhs.true
  call void @llvm.dbg.declare(metadata %struct.index_group** %newg, metadata !1324, metadata !341), !dbg !1326
  %28 = load %struct.index_group*, %struct.index_group** %g, align 8, !dbg !1327
  %node = getelementptr inbounds %struct.index_group, %struct.index_group* %28, i32 0, i32 0, !dbg !1327
  %left = getelementptr inbounds %struct.index_tree_node_s, %struct.index_tree_node_s* %node, i32 0, i32 3, !dbg !1327
  %29 = load %struct.index_tree_node_s*, %struct.index_tree_node_s** %left, align 8, !dbg !1327
  %cmp19 = icmp eq %struct.index_tree_node_s* %29, null, !dbg !1327
  br i1 %cmp19, label %cond.true, label %cond.false, !dbg !1327

cond.true:                                        ; preds = %if.then18
  br label %cond.end, !dbg !1328

cond.false:                                       ; preds = %if.then18
  call void @__assert_fail(i8* getelementptr inbounds ([27 x i8], [27 x i8]* @.str, i32 0, i32 0), i8* getelementptr inbounds ([77 x i8], [77 x i8]* @.str.1, i32 0, i32 0), i32 818, i8* getelementptr inbounds ([86 x i8], [86 x i8]* @__PRETTY_FUNCTION__.lzma_index_cat, i32 0, i32 0)) #8, !dbg !1330
  unreachable, !dbg !1330
                                                  ; No predecessors!
  br label %cond.end, !dbg !1332

cond.end:                                         ; preds = %30, %cond.true
  %31 = load %struct.index_group*, %struct.index_group** %g, align 8, !dbg !1334
  %node20 = getelementptr inbounds %struct.index_group, %struct.index_group* %31, i32 0, i32 0, !dbg !1334
  %right = getelementptr inbounds %struct.index_tree_node_s, %struct.index_tree_node_s* %node20, i32 0, i32 4, !dbg !1334
  %32 = load %struct.index_tree_node_s*, %struct.index_tree_node_s** %right, align 8, !dbg !1334
  %cmp21 = icmp eq %struct.index_tree_node_s* %32, null, !dbg !1334
  br i1 %cmp21, label %cond.true22, label %cond.false23, !dbg !1334

cond.true22:                                      ; preds = %cond.end
  br label %cond.end24, !dbg !1335

cond.false23:                                     ; preds = %cond.end
  call void @__assert_fail(i8* getelementptr inbounds ([28 x i8], [28 x i8]* @.str.2, i32 0, i32 0), i8* getelementptr inbounds ([77 x i8], [77 x i8]* @.str.1, i32 0, i32 0), i32 819, i8* getelementptr inbounds ([86 x i8], [86 x i8]* @__PRETTY_FUNCTION__.lzma_index_cat, i32 0, i32 0)) #8, !dbg !1336
  unreachable, !dbg !1336
                                                  ; No predecessors!
  br label %cond.end24, !dbg !1337

cond.end24:                                       ; preds = %33, %cond.true22
  %34 = load %struct.index_group*, %struct.index_group** %g, align 8, !dbg !1338
  %last25 = getelementptr inbounds %struct.index_group, %struct.index_group* %34, i32 0, i32 3, !dbg !1339
  %35 = load i64, i64* %last25, align 8, !dbg !1339
  %add26 = add i64 %35, 1, !dbg !1340
  %mul = mul i64 %add26, 16, !dbg !1341
  %add27 = add i64 64, %mul, !dbg !1342
  %36 = load %struct.lzma_allocator*, %struct.lzma_allocator** %allocator.addr, align 8, !dbg !1343
  %call28 = call noalias i8* @lzma_alloc(i64 %add27, %struct.lzma_allocator* %36), !dbg !1344
  %37 = bitcast i8* %call28 to %struct.index_group*, !dbg !1344
  store %struct.index_group* %37, %struct.index_group** %newg, align 8, !dbg !1345
  %38 = load %struct.index_group*, %struct.index_group** %newg, align 8, !dbg !1346
  %cmp29 = icmp eq %struct.index_group* %38, null, !dbg !1348
  br i1 %cmp29, label %if.then30, label %if.end31, !dbg !1349

if.then30:                                        ; preds = %cond.end24
  store i32 5, i32* %retval, align 4, !dbg !1350
  br label %return, !dbg !1350

if.end31:                                         ; preds = %cond.end24
  %39 = load %struct.index_group*, %struct.index_group** %newg, align 8, !dbg !1351
  %node32 = getelementptr inbounds %struct.index_group, %struct.index_group* %39, i32 0, i32 0, !dbg !1352
  %40 = load %struct.index_group*, %struct.index_group** %g, align 8, !dbg !1353
  %node33 = getelementptr inbounds %struct.index_group, %struct.index_group* %40, i32 0, i32 0, !dbg !1354
  %41 = bitcast %struct.index_tree_node_s* %node32 to i8*, !dbg !1354
  %42 = bitcast %struct.index_tree_node_s* %node33 to i8*, !dbg !1354
  call void @llvm.memcpy.p0i8.p0i8.i64(i8* %41, i8* %42, i64 40, i32 8, i1 false), !dbg !1354
  %43 = load %struct.index_group*, %struct.index_group** %g, align 8, !dbg !1355
  %last34 = getelementptr inbounds %struct.index_group, %struct.index_group* %43, i32 0, i32 3, !dbg !1356
  %44 = load i64, i64* %last34, align 8, !dbg !1356
  %add35 = add i64 %44, 1, !dbg !1357
  %45 = load %struct.index_group*, %struct.index_group** %newg, align 8, !dbg !1358
  %allocated36 = getelementptr inbounds %struct.index_group, %struct.index_group* %45, i32 0, i32 2, !dbg !1359
  store i64 %add35, i64* %allocated36, align 8, !dbg !1360
  %46 = load %struct.index_group*, %struct.index_group** %g, align 8, !dbg !1361
  %last37 = getelementptr inbounds %struct.index_group, %struct.index_group* %46, i32 0, i32 3, !dbg !1362
  %47 = load i64, i64* %last37, align 8, !dbg !1362
  %48 = load %struct.index_group*, %struct.index_group** %newg, align 8, !dbg !1363
  %last38 = getelementptr inbounds %struct.index_group, %struct.index_group* %48, i32 0, i32 3, !dbg !1364
  store i64 %47, i64* %last38, align 8, !dbg !1365
  %49 = load %struct.index_group*, %struct.index_group** %g, align 8, !dbg !1366
  %number_base = getelementptr inbounds %struct.index_group, %struct.index_group* %49, i32 0, i32 1, !dbg !1367
  %50 = load i64, i64* %number_base, align 8, !dbg !1367
  %51 = load %struct.index_group*, %struct.index_group** %newg, align 8, !dbg !1368
  %number_base39 = getelementptr inbounds %struct.index_group, %struct.index_group* %51, i32 0, i32 1, !dbg !1369
  store i64 %50, i64* %number_base39, align 8, !dbg !1370
  %52 = load %struct.index_group*, %struct.index_group** %newg, align 8, !dbg !1371
  %records = getelementptr inbounds %struct.index_group, %struct.index_group* %52, i32 0, i32 4, !dbg !1372
  %arraydecay = getelementptr inbounds [0 x %struct.index_record], [0 x %struct.index_record]* %records, i32 0, i32 0, !dbg !1373
  %53 = bitcast %struct.index_record* %arraydecay to i8*, !dbg !1373
  %54 = load %struct.index_group*, %struct.index_group** %g, align 8, !dbg !1374
  %records40 = getelementptr inbounds %struct.index_group, %struct.index_group* %54, i32 0, i32 4, !dbg !1375
  %arraydecay41 = getelementptr inbounds [0 x %struct.index_record], [0 x %struct.index_record]* %records40, i32 0, i32 0, !dbg !1373
  %55 = bitcast %struct.index_record* %arraydecay41 to i8*, !dbg !1373
  %56 = load %struct.index_group*, %struct.index_group** %newg, align 8, !dbg !1376
  %allocated42 = getelementptr inbounds %struct.index_group, %struct.index_group* %56, i32 0, i32 2, !dbg !1377
  %57 = load i64, i64* %allocated42, align 8, !dbg !1377
  %mul43 = mul i64 %57, 16, !dbg !1378
  call void @llvm.memcpy.p0i8.p0i8.i64(i8* %53, i8* %55, i64 %mul43, i32 8, i1 false), !dbg !1373
  %58 = load %struct.index_group*, %struct.index_group** %g, align 8, !dbg !1379
  %node44 = getelementptr inbounds %struct.index_group, %struct.index_group* %58, i32 0, i32 0, !dbg !1381
  %parent = getelementptr inbounds %struct.index_tree_node_s, %struct.index_tree_node_s* %node44, i32 0, i32 2, !dbg !1382
  %59 = load %struct.index_tree_node_s*, %struct.index_tree_node_s** %parent, align 8, !dbg !1382
  %cmp45 = icmp ne %struct.index_tree_node_s* %59, null, !dbg !1383
  br i1 %cmp45, label %if.then46, label %if.end59, !dbg !1384

if.then46:                                        ; preds = %if.end31
  %60 = load %struct.index_group*, %struct.index_group** %g, align 8, !dbg !1385
  %node47 = getelementptr inbounds %struct.index_group, %struct.index_group* %60, i32 0, i32 0, !dbg !1385
  %parent48 = getelementptr inbounds %struct.index_tree_node_s, %struct.index_tree_node_s* %node47, i32 0, i32 2, !dbg !1385
  %61 = load %struct.index_tree_node_s*, %struct.index_tree_node_s** %parent48, align 8, !dbg !1385
  %right49 = getelementptr inbounds %struct.index_tree_node_s, %struct.index_tree_node_s* %61, i32 0, i32 4, !dbg !1385
  %62 = load %struct.index_tree_node_s*, %struct.index_tree_node_s** %right49, align 8, !dbg !1385
  %63 = load %struct.index_group*, %struct.index_group** %g, align 8, !dbg !1385
  %node50 = getelementptr inbounds %struct.index_group, %struct.index_group* %63, i32 0, i32 0, !dbg !1385
  %cmp51 = icmp eq %struct.index_tree_node_s* %62, %node50, !dbg !1385
  br i1 %cmp51, label %cond.true52, label %cond.false53, !dbg !1385

cond.true52:                                      ; preds = %if.then46
  br label %cond.end54, !dbg !1387

cond.false53:                                     ; preds = %if.then46
  call void @__assert_fail(i8* getelementptr inbounds ([34 x i8], [34 x i8]* @.str.3, i32 0, i32 0), i8* getelementptr inbounds ([77 x i8], [77 x i8]* @.str.1, i32 0, i32 0), i32 837, i8* getelementptr inbounds ([86 x i8], [86 x i8]* @__PRETTY_FUNCTION__.lzma_index_cat, i32 0, i32 0)) #8, !dbg !1389
  unreachable, !dbg !1389
                                                  ; No predecessors!
  br label %cond.end54, !dbg !1391

cond.end54:                                       ; preds = %64, %cond.true52
  %65 = load %struct.index_group*, %struct.index_group** %newg, align 8, !dbg !1393
  %node55 = getelementptr inbounds %struct.index_group, %struct.index_group* %65, i32 0, i32 0, !dbg !1394
  %66 = load %struct.index_group*, %struct.index_group** %g, align 8, !dbg !1395
  %node56 = getelementptr inbounds %struct.index_group, %struct.index_group* %66, i32 0, i32 0, !dbg !1396
  %parent57 = getelementptr inbounds %struct.index_tree_node_s, %struct.index_tree_node_s* %node56, i32 0, i32 2, !dbg !1397
  %67 = load %struct.index_tree_node_s*, %struct.index_tree_node_s** %parent57, align 8, !dbg !1397
  %right58 = getelementptr inbounds %struct.index_tree_node_s, %struct.index_tree_node_s* %67, i32 0, i32 4, !dbg !1398
  store %struct.index_tree_node_s* %node55, %struct.index_tree_node_s** %right58, align 8, !dbg !1399
  br label %if.end59, !dbg !1400

if.end59:                                         ; preds = %cond.end54, %if.end31
  %68 = load %struct.index_stream*, %struct.index_stream** %s, align 8, !dbg !1401
  %groups60 = getelementptr inbounds %struct.index_stream, %struct.index_stream* %68, i32 0, i32 3, !dbg !1403
  %leftmost = getelementptr inbounds %struct.index_tree, %struct.index_tree* %groups60, i32 0, i32 1, !dbg !1404
  %69 = load %struct.index_tree_node_s*, %struct.index_tree_node_s** %leftmost, align 8, !dbg !1404
  %70 = load %struct.index_group*, %struct.index_group** %g, align 8, !dbg !1405
  %node61 = getelementptr inbounds %struct.index_group, %struct.index_group* %70, i32 0, i32 0, !dbg !1406
  %cmp62 = icmp eq %struct.index_tree_node_s* %69, %node61, !dbg !1407
  br i1 %cmp62, label %if.then63, label %if.end76, !dbg !1408

if.then63:                                        ; preds = %if.end59
  %71 = load %struct.index_stream*, %struct.index_stream** %s, align 8, !dbg !1409
  %groups64 = getelementptr inbounds %struct.index_stream, %struct.index_stream* %71, i32 0, i32 3, !dbg !1409
  %root = getelementptr inbounds %struct.index_tree, %struct.index_tree* %groups64, i32 0, i32 0, !dbg !1409
  %72 = load %struct.index_tree_node_s*, %struct.index_tree_node_s** %root, align 8, !dbg !1409
  %73 = load %struct.index_group*, %struct.index_group** %g, align 8, !dbg !1409
  %node65 = getelementptr inbounds %struct.index_group, %struct.index_group* %73, i32 0, i32 0, !dbg !1409
  %cmp66 = icmp eq %struct.index_tree_node_s* %72, %node65, !dbg !1409
  br i1 %cmp66, label %cond.true67, label %cond.false68, !dbg !1409

cond.true67:                                      ; preds = %if.then63
  br label %cond.end69, !dbg !1411

cond.false68:                                     ; preds = %if.then63
  call void @__assert_fail(i8* getelementptr inbounds ([27 x i8], [27 x i8]* @.str.4, i32 0, i32 0), i8* getelementptr inbounds ([77 x i8], [77 x i8]* @.str.1, i32 0, i32 0), i32 842, i8* getelementptr inbounds ([86 x i8], [86 x i8]* @__PRETTY_FUNCTION__.lzma_index_cat, i32 0, i32 0)) #8, !dbg !1413
  unreachable, !dbg !1413
                                                  ; No predecessors!
  br label %cond.end69, !dbg !1415

cond.end69:                                       ; preds = %74, %cond.true67
  %75 = load %struct.index_group*, %struct.index_group** %newg, align 8, !dbg !1417
  %node70 = getelementptr inbounds %struct.index_group, %struct.index_group* %75, i32 0, i32 0, !dbg !1418
  %76 = load %struct.index_stream*, %struct.index_stream** %s, align 8, !dbg !1419
  %groups71 = getelementptr inbounds %struct.index_stream, %struct.index_stream* %76, i32 0, i32 3, !dbg !1420
  %leftmost72 = getelementptr inbounds %struct.index_tree, %struct.index_tree* %groups71, i32 0, i32 1, !dbg !1421
  store %struct.index_tree_node_s* %node70, %struct.index_tree_node_s** %leftmost72, align 8, !dbg !1422
  %77 = load %struct.index_group*, %struct.index_group** %newg, align 8, !dbg !1423
  %node73 = getelementptr inbounds %struct.index_group, %struct.index_group* %77, i32 0, i32 0, !dbg !1424
  %78 = load %struct.index_stream*, %struct.index_stream** %s, align 8, !dbg !1425
  %groups74 = getelementptr inbounds %struct.index_stream, %struct.index_stream* %78, i32 0, i32 3, !dbg !1426
  %root75 = getelementptr inbounds %struct.index_tree, %struct.index_tree* %groups74, i32 0, i32 0, !dbg !1427
  store %struct.index_tree_node_s* %node73, %struct.index_tree_node_s** %root75, align 8, !dbg !1428
  br label %if.end76, !dbg !1429

if.end76:                                         ; preds = %cond.end69, %if.end59
  %79 = load %struct.index_stream*, %struct.index_stream** %s, align 8, !dbg !1430
  %groups77 = getelementptr inbounds %struct.index_stream, %struct.index_stream* %79, i32 0, i32 3, !dbg !1432
  %rightmost78 = getelementptr inbounds %struct.index_tree, %struct.index_tree* %groups77, i32 0, i32 2, !dbg !1433
  %80 = load %struct.index_tree_node_s*, %struct.index_tree_node_s** %rightmost78, align 8, !dbg !1433
  %81 = load %struct.index_group*, %struct.index_group** %g, align 8, !dbg !1434
  %node79 = getelementptr inbounds %struct.index_group, %struct.index_group* %81, i32 0, i32 0, !dbg !1435
  %cmp80 = icmp eq %struct.index_tree_node_s* %80, %node79, !dbg !1436
  br i1 %cmp80, label %if.then81, label %if.end85, !dbg !1437

if.then81:                                        ; preds = %if.end76
  %82 = load %struct.index_group*, %struct.index_group** %newg, align 8, !dbg !1438
  %node82 = getelementptr inbounds %struct.index_group, %struct.index_group* %82, i32 0, i32 0, !dbg !1439
  %83 = load %struct.index_stream*, %struct.index_stream** %s, align 8, !dbg !1440
  %groups83 = getelementptr inbounds %struct.index_stream, %struct.index_stream* %83, i32 0, i32 3, !dbg !1441
  %rightmost84 = getelementptr inbounds %struct.index_tree, %struct.index_tree* %groups83, i32 0, i32 2, !dbg !1442
  store %struct.index_tree_node_s* %node82, %struct.index_tree_node_s** %rightmost84, align 8, !dbg !1443
  br label %if.end85, !dbg !1440

if.end85:                                         ; preds = %if.then81, %if.end76
  %84 = load %struct.index_group*, %struct.index_group** %g, align 8, !dbg !1444
  %85 = bitcast %struct.index_group* %84 to i8*, !dbg !1444
  %86 = load %struct.lzma_allocator*, %struct.lzma_allocator** %allocator.addr, align 8, !dbg !1445
  call void @lzma_free(i8* %85, %struct.lzma_allocator* %86), !dbg !1446
  br label %if.end86, !dbg !1447

if.end86:                                         ; preds = %if.end85, %land.lhs.true, %if.end13
  %87 = load %struct.lzma_index_s*, %struct.lzma_index_s** %dest.addr, align 8, !dbg !1448
  %uncompressed_size87 = getelementptr inbounds %struct.lzma_index_s, %struct.lzma_index_s* %87, i32 0, i32 1, !dbg !1449
  %88 = load i64, i64* %uncompressed_size87, align 8, !dbg !1449
  %uncompressed_size88 = getelementptr inbounds %struct.index_cat_info, %struct.index_cat_info* %info, i32 0, i32 0, !dbg !1450
  store i64 %88, i64* %uncompressed_size88, align 8, !dbg !1451
  %89 = load i64, i64* %dest_file_size, align 8, !dbg !1452
  %file_size = getelementptr inbounds %struct.index_cat_info, %struct.index_cat_info* %info, i32 0, i32 1, !dbg !1453
  store i64 %89, i64* %file_size, align 8, !dbg !1454
  %90 = load %struct.lzma_index_s*, %struct.lzma_index_s** %dest.addr, align 8, !dbg !1455
  %streams89 = getelementptr inbounds %struct.lzma_index_s, %struct.lzma_index_s* %90, i32 0, i32 0, !dbg !1456
  %count = getelementptr inbounds %struct.index_tree, %struct.index_tree* %streams89, i32 0, i32 3, !dbg !1457
  %91 = load i32, i32* %count, align 8, !dbg !1457
  %stream_number_add = getelementptr inbounds %struct.index_cat_info, %struct.index_cat_info* %info, i32 0, i32 3, !dbg !1458
  store i32 %91, i32* %stream_number_add, align 8, !dbg !1459
  %92 = load %struct.lzma_index_s*, %struct.lzma_index_s** %dest.addr, align 8, !dbg !1460
  %record_count90 = getelementptr inbounds %struct.lzma_index_s, %struct.lzma_index_s* %92, i32 0, i32 3, !dbg !1461
  %93 = load i64, i64* %record_count90, align 8, !dbg !1461
  %block_number_add = getelementptr inbounds %struct.index_cat_info, %struct.index_cat_info* %info, i32 0, i32 2, !dbg !1462
  store i64 %93, i64* %block_number_add, align 8, !dbg !1463
  %94 = load %struct.lzma_index_s*, %struct.lzma_index_s** %dest.addr, align 8, !dbg !1464
  %streams91 = getelementptr inbounds %struct.lzma_index_s, %struct.lzma_index_s* %94, i32 0, i32 0, !dbg !1465
  %streams92 = getelementptr inbounds %struct.index_cat_info, %struct.index_cat_info* %info, i32 0, i32 4, !dbg !1466
  store %struct.index_tree* %streams91, %struct.index_tree** %streams92, align 8, !dbg !1467
  %95 = load %struct.lzma_index_s*, %struct.lzma_index_s** %src.addr, align 8, !dbg !1468
  %streams93 = getelementptr inbounds %struct.lzma_index_s, %struct.lzma_index_s* %95, i32 0, i32 0, !dbg !1469
  %root94 = getelementptr inbounds %struct.index_tree, %struct.index_tree* %streams93, i32 0, i32 0, !dbg !1470
  %96 = load %struct.index_tree_node_s*, %struct.index_tree_node_s** %root94, align 8, !dbg !1470
  %97 = bitcast %struct.index_tree_node_s* %96 to %struct.index_stream*, !dbg !1471
  call void @index_cat_helper(%struct.index_cat_info* %info, %struct.index_stream* %97), !dbg !1472
  %98 = load %struct.lzma_index_s*, %struct.lzma_index_s** %src.addr, align 8, !dbg !1473
  %uncompressed_size95 = getelementptr inbounds %struct.lzma_index_s, %struct.lzma_index_s* %98, i32 0, i32 1, !dbg !1474
  %99 = load i64, i64* %uncompressed_size95, align 8, !dbg !1474
  %100 = load %struct.lzma_index_s*, %struct.lzma_index_s** %dest.addr, align 8, !dbg !1475
  %uncompressed_size96 = getelementptr inbounds %struct.lzma_index_s, %struct.lzma_index_s* %100, i32 0, i32 1, !dbg !1476
  %101 = load i64, i64* %uncompressed_size96, align 8, !dbg !1477
  %add97 = add i64 %101, %99, !dbg !1477
  store i64 %add97, i64* %uncompressed_size96, align 8, !dbg !1477
  %102 = load %struct.lzma_index_s*, %struct.lzma_index_s** %src.addr, align 8, !dbg !1478
  %total_size = getelementptr inbounds %struct.lzma_index_s, %struct.lzma_index_s* %102, i32 0, i32 2, !dbg !1479
  %103 = load i64, i64* %total_size, align 8, !dbg !1479
  %104 = load %struct.lzma_index_s*, %struct.lzma_index_s** %dest.addr, align 8, !dbg !1480
  %total_size98 = getelementptr inbounds %struct.lzma_index_s, %struct.lzma_index_s* %104, i32 0, i32 2, !dbg !1481
  %105 = load i64, i64* %total_size98, align 8, !dbg !1482
  %add99 = add i64 %105, %103, !dbg !1482
  store i64 %add99, i64* %total_size98, align 8, !dbg !1482
  %106 = load %struct.lzma_index_s*, %struct.lzma_index_s** %src.addr, align 8, !dbg !1483
  %record_count100 = getelementptr inbounds %struct.lzma_index_s, %struct.lzma_index_s* %106, i32 0, i32 3, !dbg !1484
  %107 = load i64, i64* %record_count100, align 8, !dbg !1484
  %108 = load %struct.lzma_index_s*, %struct.lzma_index_s** %dest.addr, align 8, !dbg !1485
  %record_count101 = getelementptr inbounds %struct.lzma_index_s, %struct.lzma_index_s* %108, i32 0, i32 3, !dbg !1486
  %109 = load i64, i64* %record_count101, align 8, !dbg !1487
  %add102 = add i64 %109, %107, !dbg !1487
  store i64 %add102, i64* %record_count101, align 8, !dbg !1487
  %110 = load %struct.lzma_index_s*, %struct.lzma_index_s** %src.addr, align 8, !dbg !1488
  %index_list_size103 = getelementptr inbounds %struct.lzma_index_s, %struct.lzma_index_s* %110, i32 0, i32 4, !dbg !1489
  %111 = load i64, i64* %index_list_size103, align 8, !dbg !1489
  %112 = load %struct.lzma_index_s*, %struct.lzma_index_s** %dest.addr, align 8, !dbg !1490
  %index_list_size104 = getelementptr inbounds %struct.lzma_index_s, %struct.lzma_index_s* %112, i32 0, i32 4, !dbg !1491
  %113 = load i64, i64* %index_list_size104, align 8, !dbg !1492
  %add105 = add i64 %113, %111, !dbg !1492
  store i64 %add105, i64* %index_list_size104, align 8, !dbg !1492
  %114 = load %struct.lzma_index_s*, %struct.lzma_index_s** %dest.addr, align 8, !dbg !1493
  %call106 = call i32 @lzma_index_checks(%struct.lzma_index_s* %114) #10, !dbg !1494
  %115 = load %struct.lzma_index_s*, %struct.lzma_index_s** %src.addr, align 8, !dbg !1495
  %checks = getelementptr inbounds %struct.lzma_index_s, %struct.lzma_index_s* %115, i32 0, i32 6, !dbg !1496
  %116 = load i32, i32* %checks, align 8, !dbg !1496
  %or = or i32 %call106, %116, !dbg !1497
  %117 = load %struct.lzma_index_s*, %struct.lzma_index_s** %dest.addr, align 8, !dbg !1498
  %checks107 = getelementptr inbounds %struct.lzma_index_s, %struct.lzma_index_s* %117, i32 0, i32 6, !dbg !1499
  store i32 %or, i32* %checks107, align 8, !dbg !1500
  %118 = load %struct.lzma_index_s*, %struct.lzma_index_s** %src.addr, align 8, !dbg !1501
  %119 = bitcast %struct.lzma_index_s* %118 to i8*, !dbg !1501
  %120 = load %struct.lzma_allocator*, %struct.lzma_allocator** %allocator.addr, align 8, !dbg !1502
  call void @lzma_free(i8* %119, %struct.lzma_allocator* %120), !dbg !1503
  store i32 0, i32* %retval, align 4, !dbg !1504
  br label %return, !dbg !1504

return:                                           ; preds = %if.end86, %if.then30, %if.then12, %if.then
  %121 = load i32, i32* %retval, align 4, !dbg !1505
  ret i32 %121, !dbg !1505
}

; Function Attrs: noreturn nounwind
declare void @__assert_fail(i8*, i8*, i32, i8*) #7

; Function Attrs: nounwind uwtable
define internal void @index_cat_helper(%struct.index_cat_info* %info, %struct.index_stream* %this) #0 !dbg !310 {
entry:
  %info.addr = alloca %struct.index_cat_info*, align 8
  %this.addr = alloca %struct.index_stream*, align 8
  %left = alloca %struct.index_stream*, align 8
  %right = alloca %struct.index_stream*, align 8
  store %struct.index_cat_info* %info, %struct.index_cat_info** %info.addr, align 8
  call void @llvm.dbg.declare(metadata %struct.index_cat_info** %info.addr, metadata !1506, metadata !341), !dbg !1507
  store %struct.index_stream* %this, %struct.index_stream** %this.addr, align 8
  call void @llvm.dbg.declare(metadata %struct.index_stream** %this.addr, metadata !1508, metadata !341), !dbg !1509
  call void @llvm.dbg.declare(metadata %struct.index_stream** %left, metadata !1510, metadata !341), !dbg !1511
  %0 = load %struct.index_stream*, %struct.index_stream** %this.addr, align 8, !dbg !1512
  %node = getelementptr inbounds %struct.index_stream, %struct.index_stream* %0, i32 0, i32 0, !dbg !1513
  %left1 = getelementptr inbounds %struct.index_tree_node_s, %struct.index_tree_node_s* %node, i32 0, i32 3, !dbg !1514
  %1 = load %struct.index_tree_node_s*, %struct.index_tree_node_s** %left1, align 8, !dbg !1514
  %2 = bitcast %struct.index_tree_node_s* %1 to %struct.index_stream*, !dbg !1515
  store %struct.index_stream* %2, %struct.index_stream** %left, align 8, !dbg !1511
  call void @llvm.dbg.declare(metadata %struct.index_stream** %right, metadata !1516, metadata !341), !dbg !1517
  %3 = load %struct.index_stream*, %struct.index_stream** %this.addr, align 8, !dbg !1518
  %node2 = getelementptr inbounds %struct.index_stream, %struct.index_stream* %3, i32 0, i32 0, !dbg !1519
  %right3 = getelementptr inbounds %struct.index_tree_node_s, %struct.index_tree_node_s* %node2, i32 0, i32 4, !dbg !1520
  %4 = load %struct.index_tree_node_s*, %struct.index_tree_node_s** %right3, align 8, !dbg !1520
  %5 = bitcast %struct.index_tree_node_s* %4 to %struct.index_stream*, !dbg !1521
  store %struct.index_stream* %5, %struct.index_stream** %right, align 8, !dbg !1517
  %6 = load %struct.index_stream*, %struct.index_stream** %left, align 8, !dbg !1522
  %cmp = icmp ne %struct.index_stream* %6, null, !dbg !1524
  br i1 %cmp, label %if.then, label %if.end, !dbg !1525

if.then:                                          ; preds = %entry
  %7 = load %struct.index_cat_info*, %struct.index_cat_info** %info.addr, align 8, !dbg !1526
  %8 = load %struct.index_stream*, %struct.index_stream** %left, align 8, !dbg !1527
  call void @index_cat_helper(%struct.index_cat_info* %7, %struct.index_stream* %8), !dbg !1528
  br label %if.end, !dbg !1528

if.end:                                           ; preds = %if.then, %entry
  %9 = load %struct.index_cat_info*, %struct.index_cat_info** %info.addr, align 8, !dbg !1529
  %uncompressed_size = getelementptr inbounds %struct.index_cat_info, %struct.index_cat_info* %9, i32 0, i32 0, !dbg !1530
  %10 = load i64, i64* %uncompressed_size, align 8, !dbg !1530
  %11 = load %struct.index_stream*, %struct.index_stream** %this.addr, align 8, !dbg !1531
  %node4 = getelementptr inbounds %struct.index_stream, %struct.index_stream* %11, i32 0, i32 0, !dbg !1532
  %uncompressed_base = getelementptr inbounds %struct.index_tree_node_s, %struct.index_tree_node_s* %node4, i32 0, i32 0, !dbg !1533
  %12 = load i64, i64* %uncompressed_base, align 8, !dbg !1534
  %add = add i64 %12, %10, !dbg !1534
  store i64 %add, i64* %uncompressed_base, align 8, !dbg !1534
  %13 = load %struct.index_cat_info*, %struct.index_cat_info** %info.addr, align 8, !dbg !1535
  %file_size = getelementptr inbounds %struct.index_cat_info, %struct.index_cat_info* %13, i32 0, i32 1, !dbg !1536
  %14 = load i64, i64* %file_size, align 8, !dbg !1536
  %15 = load %struct.index_stream*, %struct.index_stream** %this.addr, align 8, !dbg !1537
  %node5 = getelementptr inbounds %struct.index_stream, %struct.index_stream* %15, i32 0, i32 0, !dbg !1538
  %compressed_base = getelementptr inbounds %struct.index_tree_node_s, %struct.index_tree_node_s* %node5, i32 0, i32 1, !dbg !1539
  %16 = load i64, i64* %compressed_base, align 8, !dbg !1540
  %add6 = add i64 %16, %14, !dbg !1540
  store i64 %add6, i64* %compressed_base, align 8, !dbg !1540
  %17 = load %struct.index_cat_info*, %struct.index_cat_info** %info.addr, align 8, !dbg !1541
  %stream_number_add = getelementptr inbounds %struct.index_cat_info, %struct.index_cat_info* %17, i32 0, i32 3, !dbg !1542
  %18 = load i32, i32* %stream_number_add, align 8, !dbg !1542
  %19 = load %struct.index_stream*, %struct.index_stream** %this.addr, align 8, !dbg !1543
  %number = getelementptr inbounds %struct.index_stream, %struct.index_stream* %19, i32 0, i32 1, !dbg !1544
  %20 = load i32, i32* %number, align 8, !dbg !1545
  %add7 = add i32 %20, %18, !dbg !1545
  store i32 %add7, i32* %number, align 8, !dbg !1545
  %21 = load %struct.index_cat_info*, %struct.index_cat_info** %info.addr, align 8, !dbg !1546
  %block_number_add = getelementptr inbounds %struct.index_cat_info, %struct.index_cat_info* %21, i32 0, i32 2, !dbg !1547
  %22 = load i64, i64* %block_number_add, align 8, !dbg !1547
  %23 = load %struct.index_stream*, %struct.index_stream** %this.addr, align 8, !dbg !1548
  %block_number_base = getelementptr inbounds %struct.index_stream, %struct.index_stream* %23, i32 0, i32 2, !dbg !1549
  %24 = load i64, i64* %block_number_base, align 8, !dbg !1550
  %add8 = add i64 %24, %22, !dbg !1550
  store i64 %add8, i64* %block_number_base, align 8, !dbg !1550
  %25 = load %struct.index_cat_info*, %struct.index_cat_info** %info.addr, align 8, !dbg !1551
  %streams = getelementptr inbounds %struct.index_cat_info, %struct.index_cat_info* %25, i32 0, i32 4, !dbg !1552
  %26 = load %struct.index_tree*, %struct.index_tree** %streams, align 8, !dbg !1552
  %27 = load %struct.index_stream*, %struct.index_stream** %this.addr, align 8, !dbg !1553
  %node9 = getelementptr inbounds %struct.index_stream, %struct.index_stream* %27, i32 0, i32 0, !dbg !1554
  call void @index_tree_append(%struct.index_tree* %26, %struct.index_tree_node_s* %node9), !dbg !1555
  %28 = load %struct.index_stream*, %struct.index_stream** %right, align 8, !dbg !1556
  %cmp10 = icmp ne %struct.index_stream* %28, null, !dbg !1558
  br i1 %cmp10, label %if.then11, label %if.end12, !dbg !1559

if.then11:                                        ; preds = %if.end
  %29 = load %struct.index_cat_info*, %struct.index_cat_info** %info.addr, align 8, !dbg !1560
  %30 = load %struct.index_stream*, %struct.index_stream** %right, align 8, !dbg !1561
  call void @index_cat_helper(%struct.index_cat_info* %29, %struct.index_stream* %30), !dbg !1562
  br label %if.end12, !dbg !1562

if.end12:                                         ; preds = %if.then11, %if.end
  ret void, !dbg !1563
}

; Function Attrs: nounwind uwtable
define %struct.lzma_index_s* @lzma_index_dup(%struct.lzma_index_s* %src, %struct.lzma_allocator* %allocator) #0 !dbg !204 {
entry:
  %retval = alloca %struct.lzma_index_s*, align 8
  %src.addr = alloca %struct.lzma_index_s*, align 8
  %allocator.addr = alloca %struct.lzma_allocator*, align 8
  %srcstream = alloca %struct.index_stream*, align 8
  %deststream = alloca %struct.index_stream*, align 8
  %dest = alloca %struct.lzma_index_s*, align 8
  store %struct.lzma_index_s* %src, %struct.lzma_index_s** %src.addr, align 8
  call void @llvm.dbg.declare(metadata %struct.lzma_index_s** %src.addr, metadata !1564, metadata !341), !dbg !1565
  store %struct.lzma_allocator* %allocator, %struct.lzma_allocator** %allocator.addr, align 8
  call void @llvm.dbg.declare(metadata %struct.lzma_allocator** %allocator.addr, metadata !1566, metadata !341), !dbg !1567
  call void @llvm.dbg.declare(metadata %struct.index_stream** %srcstream, metadata !1568, metadata !341), !dbg !1569
  call void @llvm.dbg.declare(metadata %struct.index_stream** %deststream, metadata !1570, metadata !341), !dbg !1571
  call void @llvm.dbg.declare(metadata %struct.lzma_index_s** %dest, metadata !1572, metadata !341), !dbg !1573
  %0 = load %struct.lzma_allocator*, %struct.lzma_allocator** %allocator.addr, align 8, !dbg !1574
  %call = call %struct.lzma_index_s* @index_init_plain(%struct.lzma_allocator* %0), !dbg !1575
  store %struct.lzma_index_s* %call, %struct.lzma_index_s** %dest, align 8, !dbg !1573
  %1 = load %struct.lzma_index_s*, %struct.lzma_index_s** %dest, align 8, !dbg !1576
  %cmp = icmp eq %struct.lzma_index_s* %1, null, !dbg !1578
  br i1 %cmp, label %if.then, label %if.end, !dbg !1579

if.then:                                          ; preds = %entry
  store %struct.lzma_index_s* null, %struct.lzma_index_s** %retval, align 8, !dbg !1580
  br label %return, !dbg !1580

if.end:                                           ; preds = %entry
  %2 = load %struct.lzma_index_s*, %struct.lzma_index_s** %src.addr, align 8, !dbg !1581
  %uncompressed_size = getelementptr inbounds %struct.lzma_index_s, %struct.lzma_index_s* %2, i32 0, i32 1, !dbg !1582
  %3 = load i64, i64* %uncompressed_size, align 8, !dbg !1582
  %4 = load %struct.lzma_index_s*, %struct.lzma_index_s** %dest, align 8, !dbg !1583
  %uncompressed_size1 = getelementptr inbounds %struct.lzma_index_s, %struct.lzma_index_s* %4, i32 0, i32 1, !dbg !1584
  store i64 %3, i64* %uncompressed_size1, align 8, !dbg !1585
  %5 = load %struct.lzma_index_s*, %struct.lzma_index_s** %src.addr, align 8, !dbg !1586
  %total_size = getelementptr inbounds %struct.lzma_index_s, %struct.lzma_index_s* %5, i32 0, i32 2, !dbg !1587
  %6 = load i64, i64* %total_size, align 8, !dbg !1587
  %7 = load %struct.lzma_index_s*, %struct.lzma_index_s** %dest, align 8, !dbg !1588
  %total_size2 = getelementptr inbounds %struct.lzma_index_s, %struct.lzma_index_s* %7, i32 0, i32 2, !dbg !1589
  store i64 %6, i64* %total_size2, align 8, !dbg !1590
  %8 = load %struct.lzma_index_s*, %struct.lzma_index_s** %src.addr, align 8, !dbg !1591
  %record_count = getelementptr inbounds %struct.lzma_index_s, %struct.lzma_index_s* %8, i32 0, i32 3, !dbg !1592
  %9 = load i64, i64* %record_count, align 8, !dbg !1592
  %10 = load %struct.lzma_index_s*, %struct.lzma_index_s** %dest, align 8, !dbg !1593
  %record_count3 = getelementptr inbounds %struct.lzma_index_s, %struct.lzma_index_s* %10, i32 0, i32 3, !dbg !1594
  store i64 %9, i64* %record_count3, align 8, !dbg !1595
  %11 = load %struct.lzma_index_s*, %struct.lzma_index_s** %src.addr, align 8, !dbg !1596
  %index_list_size = getelementptr inbounds %struct.lzma_index_s, %struct.lzma_index_s* %11, i32 0, i32 4, !dbg !1597
  %12 = load i64, i64* %index_list_size, align 8, !dbg !1597
  %13 = load %struct.lzma_index_s*, %struct.lzma_index_s** %dest, align 8, !dbg !1598
  %index_list_size4 = getelementptr inbounds %struct.lzma_index_s, %struct.lzma_index_s* %13, i32 0, i32 4, !dbg !1599
  store i64 %12, i64* %index_list_size4, align 8, !dbg !1600
  %14 = load %struct.lzma_index_s*, %struct.lzma_index_s** %src.addr, align 8, !dbg !1601
  %streams = getelementptr inbounds %struct.lzma_index_s, %struct.lzma_index_s* %14, i32 0, i32 0, !dbg !1602
  %leftmost = getelementptr inbounds %struct.index_tree, %struct.index_tree* %streams, i32 0, i32 1, !dbg !1603
  %15 = load %struct.index_tree_node_s*, %struct.index_tree_node_s** %leftmost, align 8, !dbg !1603
  %16 = bitcast %struct.index_tree_node_s* %15 to %struct.index_stream*, !dbg !1604
  store %struct.index_stream* %16, %struct.index_stream** %srcstream, align 8, !dbg !1605
  br label %do.body, !dbg !1606

do.body:                                          ; preds = %do.cond, %if.end
  %17 = load %struct.index_stream*, %struct.index_stream** %srcstream, align 8, !dbg !1607
  %18 = load %struct.lzma_allocator*, %struct.lzma_allocator** %allocator.addr, align 8, !dbg !1609
  %call5 = call %struct.index_stream* @index_dup_stream(%struct.index_stream* %17, %struct.lzma_allocator* %18), !dbg !1610
  store %struct.index_stream* %call5, %struct.index_stream** %deststream, align 8, !dbg !1611
  %19 = load %struct.index_stream*, %struct.index_stream** %deststream, align 8, !dbg !1612
  %cmp6 = icmp eq %struct.index_stream* %19, null, !dbg !1614
  br i1 %cmp6, label %if.then7, label %if.end8, !dbg !1615

if.then7:                                         ; preds = %do.body
  %20 = load %struct.lzma_index_s*, %struct.lzma_index_s** %dest, align 8, !dbg !1616
  %21 = load %struct.lzma_allocator*, %struct.lzma_allocator** %allocator.addr, align 8, !dbg !1618
  call void @lzma_index_end(%struct.lzma_index_s* %20, %struct.lzma_allocator* %21) #9, !dbg !1619
  store %struct.lzma_index_s* null, %struct.lzma_index_s** %retval, align 8, !dbg !1620
  br label %return, !dbg !1620

if.end8:                                          ; preds = %do.body
  %22 = load %struct.lzma_index_s*, %struct.lzma_index_s** %dest, align 8, !dbg !1621
  %streams9 = getelementptr inbounds %struct.lzma_index_s, %struct.lzma_index_s* %22, i32 0, i32 0, !dbg !1622
  %23 = load %struct.index_stream*, %struct.index_stream** %deststream, align 8, !dbg !1623
  %node = getelementptr inbounds %struct.index_stream, %struct.index_stream* %23, i32 0, i32 0, !dbg !1624
  call void @index_tree_append(%struct.index_tree* %streams9, %struct.index_tree_node_s* %node), !dbg !1625
  %24 = load %struct.index_stream*, %struct.index_stream** %srcstream, align 8, !dbg !1626
  %node10 = getelementptr inbounds %struct.index_stream, %struct.index_stream* %24, i32 0, i32 0, !dbg !1627
  %call11 = call i8* @index_tree_next(%struct.index_tree_node_s* %node10), !dbg !1628
  %25 = bitcast i8* %call11 to %struct.index_stream*, !dbg !1628
  store %struct.index_stream* %25, %struct.index_stream** %srcstream, align 8, !dbg !1629
  br label %do.cond, !dbg !1630

do.cond:                                          ; preds = %if.end8
  %26 = load %struct.index_stream*, %struct.index_stream** %srcstream, align 8, !dbg !1631
  %cmp12 = icmp ne %struct.index_stream* %26, null, !dbg !1633
  br i1 %cmp12, label %do.body, label %do.end, !dbg !1634

do.end:                                           ; preds = %do.cond
  %27 = load %struct.lzma_index_s*, %struct.lzma_index_s** %dest, align 8, !dbg !1635
  store %struct.lzma_index_s* %27, %struct.lzma_index_s** %retval, align 8, !dbg !1636
  br label %return, !dbg !1636

return:                                           ; preds = %do.end, %if.then7, %if.then
  %28 = load %struct.lzma_index_s*, %struct.lzma_index_s** %retval, align 8, !dbg !1637
  ret %struct.lzma_index_s* %28, !dbg !1637
}

; Function Attrs: nounwind uwtable
define internal %struct.index_stream* @index_dup_stream(%struct.index_stream* %src, %struct.lzma_allocator* %allocator) #0 !dbg !323 {
entry:
  %retval = alloca %struct.index_stream*, align 8
  %src.addr = alloca %struct.index_stream*, align 8
  %allocator.addr = alloca %struct.lzma_allocator*, align 8
  %dest = alloca %struct.index_stream*, align 8
  %destg = alloca %struct.index_group*, align 8
  %srcg = alloca %struct.index_group*, align 8
  %i = alloca i64, align 8
  store %struct.index_stream* %src, %struct.index_stream** %src.addr, align 8
  call void @llvm.dbg.declare(metadata %struct.index_stream** %src.addr, metadata !1638, metadata !341), !dbg !1639
  store %struct.lzma_allocator* %allocator, %struct.lzma_allocator** %allocator.addr, align 8
  call void @llvm.dbg.declare(metadata %struct.lzma_allocator** %allocator.addr, metadata !1640, metadata !341), !dbg !1641
  call void @llvm.dbg.declare(metadata %struct.index_stream** %dest, metadata !1642, metadata !341), !dbg !1643
  call void @llvm.dbg.declare(metadata %struct.index_group** %destg, metadata !1644, metadata !341), !dbg !1645
  call void @llvm.dbg.declare(metadata %struct.index_group** %srcg, metadata !1646, metadata !341), !dbg !1647
  call void @llvm.dbg.declare(metadata i64* %i, metadata !1648, metadata !341), !dbg !1649
  store i64 0, i64* %i, align 8, !dbg !1649
  %0 = load %struct.index_stream*, %struct.index_stream** %src.addr, align 8, !dbg !1650
  %record_count = getelementptr inbounds %struct.index_stream, %struct.index_stream* %0, i32 0, i32 4, !dbg !1652
  %1 = load i64, i64* %record_count, align 8, !dbg !1652
  %cmp = icmp ugt i64 %1, 1152921504606846971, !dbg !1653
  br i1 %cmp, label %if.then, label %if.end, !dbg !1654

if.then:                                          ; preds = %entry
  store %struct.index_stream* null, %struct.index_stream** %retval, align 8, !dbg !1655
  br label %return, !dbg !1655

if.end:                                           ; preds = %entry
  %2 = load %struct.index_stream*, %struct.index_stream** %src.addr, align 8, !dbg !1656
  %node = getelementptr inbounds %struct.index_stream, %struct.index_stream* %2, i32 0, i32 0, !dbg !1657
  %compressed_base = getelementptr inbounds %struct.index_tree_node_s, %struct.index_tree_node_s* %node, i32 0, i32 1, !dbg !1658
  %3 = load i64, i64* %compressed_base, align 8, !dbg !1658
  %4 = load %struct.index_stream*, %struct.index_stream** %src.addr, align 8, !dbg !1659
  %node1 = getelementptr inbounds %struct.index_stream, %struct.index_stream* %4, i32 0, i32 0, !dbg !1660
  %uncompressed_base = getelementptr inbounds %struct.index_tree_node_s, %struct.index_tree_node_s* %node1, i32 0, i32 0, !dbg !1661
  %5 = load i64, i64* %uncompressed_base, align 8, !dbg !1661
  %6 = load %struct.index_stream*, %struct.index_stream** %src.addr, align 8, !dbg !1662
  %number = getelementptr inbounds %struct.index_stream, %struct.index_stream* %6, i32 0, i32 1, !dbg !1663
  %7 = load i32, i32* %number, align 8, !dbg !1663
  %conv = zext i32 %7 to i64, !dbg !1662
  %8 = load %struct.index_stream*, %struct.index_stream** %src.addr, align 8, !dbg !1664
  %block_number_base = getelementptr inbounds %struct.index_stream, %struct.index_stream* %8, i32 0, i32 2, !dbg !1665
  %9 = load i64, i64* %block_number_base, align 8, !dbg !1665
  %10 = load %struct.lzma_allocator*, %struct.lzma_allocator** %allocator.addr, align 8, !dbg !1666
  %call = call %struct.index_stream* @index_stream_init(i64 %3, i64 %5, i64 %conv, i64 %9, %struct.lzma_allocator* %10), !dbg !1667
  store %struct.index_stream* %call, %struct.index_stream** %dest, align 8, !dbg !1668
  %11 = load %struct.index_stream*, %struct.index_stream** %dest, align 8, !dbg !1669
  %cmp2 = icmp eq %struct.index_stream* %11, null, !dbg !1671
  br i1 %cmp2, label %if.then6, label %lor.lhs.false, !dbg !1672

lor.lhs.false:                                    ; preds = %if.end
  %12 = load %struct.index_stream*, %struct.index_stream** %src.addr, align 8, !dbg !1673
  %groups = getelementptr inbounds %struct.index_stream, %struct.index_stream* %12, i32 0, i32 3, !dbg !1675
  %leftmost = getelementptr inbounds %struct.index_tree, %struct.index_tree* %groups, i32 0, i32 1, !dbg !1676
  %13 = load %struct.index_tree_node_s*, %struct.index_tree_node_s** %leftmost, align 8, !dbg !1676
  %cmp4 = icmp eq %struct.index_tree_node_s* %13, null, !dbg !1677
  br i1 %cmp4, label %if.then6, label %if.end7, !dbg !1678

if.then6:                                         ; preds = %lor.lhs.false, %if.end
  %14 = load %struct.index_stream*, %struct.index_stream** %dest, align 8, !dbg !1679
  store %struct.index_stream* %14, %struct.index_stream** %retval, align 8, !dbg !1680
  br label %return, !dbg !1680

if.end7:                                          ; preds = %lor.lhs.false
  %15 = load %struct.index_stream*, %struct.index_stream** %src.addr, align 8, !dbg !1681
  %record_count8 = getelementptr inbounds %struct.index_stream, %struct.index_stream* %15, i32 0, i32 4, !dbg !1682
  %16 = load i64, i64* %record_count8, align 8, !dbg !1682
  %17 = load %struct.index_stream*, %struct.index_stream** %dest, align 8, !dbg !1683
  %record_count9 = getelementptr inbounds %struct.index_stream, %struct.index_stream* %17, i32 0, i32 4, !dbg !1684
  store i64 %16, i64* %record_count9, align 8, !dbg !1685
  %18 = load %struct.index_stream*, %struct.index_stream** %src.addr, align 8, !dbg !1686
  %index_list_size = getelementptr inbounds %struct.index_stream, %struct.index_stream* %18, i32 0, i32 5, !dbg !1687
  %19 = load i64, i64* %index_list_size, align 8, !dbg !1687
  %20 = load %struct.index_stream*, %struct.index_stream** %dest, align 8, !dbg !1688
  %index_list_size10 = getelementptr inbounds %struct.index_stream, %struct.index_stream* %20, i32 0, i32 5, !dbg !1689
  store i64 %19, i64* %index_list_size10, align 8, !dbg !1690
  %21 = load %struct.index_stream*, %struct.index_stream** %dest, align 8, !dbg !1691
  %stream_flags = getelementptr inbounds %struct.index_stream, %struct.index_stream* %21, i32 0, i32 6, !dbg !1692
  %22 = load %struct.index_stream*, %struct.index_stream** %src.addr, align 8, !dbg !1693
  %stream_flags11 = getelementptr inbounds %struct.index_stream, %struct.index_stream* %22, i32 0, i32 6, !dbg !1694
  %23 = bitcast %struct.lzma_stream_flags* %stream_flags to i8*, !dbg !1694
  %24 = bitcast %struct.lzma_stream_flags* %stream_flags11 to i8*, !dbg !1694
  call void @llvm.memcpy.p0i8.p0i8.i64(i8* %23, i8* %24, i64 56, i32 8, i1 false), !dbg !1694
  %25 = load %struct.index_stream*, %struct.index_stream** %src.addr, align 8, !dbg !1695
  %stream_padding = getelementptr inbounds %struct.index_stream, %struct.index_stream* %25, i32 0, i32 7, !dbg !1696
  %26 = load i64, i64* %stream_padding, align 8, !dbg !1696
  %27 = load %struct.index_stream*, %struct.index_stream** %dest, align 8, !dbg !1697
  %stream_padding12 = getelementptr inbounds %struct.index_stream, %struct.index_stream* %27, i32 0, i32 7, !dbg !1698
  store i64 %26, i64* %stream_padding12, align 8, !dbg !1699
  %28 = load %struct.index_stream*, %struct.index_stream** %src.addr, align 8, !dbg !1700
  %record_count13 = getelementptr inbounds %struct.index_stream, %struct.index_stream* %28, i32 0, i32 4, !dbg !1701
  %29 = load i64, i64* %record_count13, align 8, !dbg !1701
  %mul = mul i64 %29, 16, !dbg !1702
  %add = add i64 64, %mul, !dbg !1703
  %30 = load %struct.lzma_allocator*, %struct.lzma_allocator** %allocator.addr, align 8, !dbg !1704
  %call14 = call noalias i8* @lzma_alloc(i64 %add, %struct.lzma_allocator* %30), !dbg !1705
  %31 = bitcast i8* %call14 to %struct.index_group*, !dbg !1705
  store %struct.index_group* %31, %struct.index_group** %destg, align 8, !dbg !1706
  %32 = load %struct.index_group*, %struct.index_group** %destg, align 8, !dbg !1707
  %cmp15 = icmp eq %struct.index_group* %32, null, !dbg !1709
  br i1 %cmp15, label %if.then17, label %if.end18, !dbg !1710

if.then17:                                        ; preds = %if.end7
  %33 = load %struct.index_stream*, %struct.index_stream** %dest, align 8, !dbg !1711
  %34 = bitcast %struct.index_stream* %33 to i8*, !dbg !1711
  %35 = load %struct.lzma_allocator*, %struct.lzma_allocator** %allocator.addr, align 8, !dbg !1713
  call void @index_stream_end(i8* %34, %struct.lzma_allocator* %35), !dbg !1714
  store %struct.index_stream* null, %struct.index_stream** %retval, align 8, !dbg !1715
  br label %return, !dbg !1715

if.end18:                                         ; preds = %if.end7
  %36 = load %struct.index_group*, %struct.index_group** %destg, align 8, !dbg !1716
  %node19 = getelementptr inbounds %struct.index_group, %struct.index_group* %36, i32 0, i32 0, !dbg !1717
  %uncompressed_base20 = getelementptr inbounds %struct.index_tree_node_s, %struct.index_tree_node_s* %node19, i32 0, i32 0, !dbg !1718
  store i64 0, i64* %uncompressed_base20, align 8, !dbg !1719
  %37 = load %struct.index_group*, %struct.index_group** %destg, align 8, !dbg !1720
  %node21 = getelementptr inbounds %struct.index_group, %struct.index_group* %37, i32 0, i32 0, !dbg !1721
  %compressed_base22 = getelementptr inbounds %struct.index_tree_node_s, %struct.index_tree_node_s* %node21, i32 0, i32 1, !dbg !1722
  store i64 0, i64* %compressed_base22, align 8, !dbg !1723
  %38 = load %struct.index_group*, %struct.index_group** %destg, align 8, !dbg !1724
  %number_base = getelementptr inbounds %struct.index_group, %struct.index_group* %38, i32 0, i32 1, !dbg !1725
  store i64 1, i64* %number_base, align 8, !dbg !1726
  %39 = load %struct.index_stream*, %struct.index_stream** %src.addr, align 8, !dbg !1727
  %record_count23 = getelementptr inbounds %struct.index_stream, %struct.index_stream* %39, i32 0, i32 4, !dbg !1728
  %40 = load i64, i64* %record_count23, align 8, !dbg !1728
  %41 = load %struct.index_group*, %struct.index_group** %destg, align 8, !dbg !1729
  %allocated = getelementptr inbounds %struct.index_group, %struct.index_group* %41, i32 0, i32 2, !dbg !1730
  store i64 %40, i64* %allocated, align 8, !dbg !1731
  %42 = load %struct.index_stream*, %struct.index_stream** %src.addr, align 8, !dbg !1732
  %record_count24 = getelementptr inbounds %struct.index_stream, %struct.index_stream* %42, i32 0, i32 4, !dbg !1733
  %43 = load i64, i64* %record_count24, align 8, !dbg !1733
  %sub = sub i64 %43, 1, !dbg !1734
  %44 = load %struct.index_group*, %struct.index_group** %destg, align 8, !dbg !1735
  %last = getelementptr inbounds %struct.index_group, %struct.index_group* %44, i32 0, i32 3, !dbg !1736
  store i64 %sub, i64* %last, align 8, !dbg !1737
  %45 = load %struct.index_stream*, %struct.index_stream** %src.addr, align 8, !dbg !1738
  %groups25 = getelementptr inbounds %struct.index_stream, %struct.index_stream* %45, i32 0, i32 3, !dbg !1739
  %leftmost26 = getelementptr inbounds %struct.index_tree, %struct.index_tree* %groups25, i32 0, i32 1, !dbg !1740
  %46 = load %struct.index_tree_node_s*, %struct.index_tree_node_s** %leftmost26, align 8, !dbg !1740
  %47 = bitcast %struct.index_tree_node_s* %46 to %struct.index_group*, !dbg !1741
  store %struct.index_group* %47, %struct.index_group** %srcg, align 8, !dbg !1742
  br label %do.body, !dbg !1743

do.body:                                          ; preds = %do.cond, %if.end18
  %48 = load %struct.index_group*, %struct.index_group** %destg, align 8, !dbg !1744
  %records = getelementptr inbounds %struct.index_group, %struct.index_group* %48, i32 0, i32 4, !dbg !1746
  %arraydecay = getelementptr inbounds [0 x %struct.index_record], [0 x %struct.index_record]* %records, i32 0, i32 0, !dbg !1744
  %49 = load i64, i64* %i, align 8, !dbg !1747
  %add.ptr = getelementptr inbounds %struct.index_record, %struct.index_record* %arraydecay, i64 %49, !dbg !1748
  %50 = bitcast %struct.index_record* %add.ptr to i8*, !dbg !1749
  %51 = load %struct.index_group*, %struct.index_group** %srcg, align 8, !dbg !1750
  %records27 = getelementptr inbounds %struct.index_group, %struct.index_group* %51, i32 0, i32 4, !dbg !1751
  %arraydecay28 = getelementptr inbounds [0 x %struct.index_record], [0 x %struct.index_record]* %records27, i32 0, i32 0, !dbg !1749
  %52 = bitcast %struct.index_record* %arraydecay28 to i8*, !dbg !1749
  %53 = load %struct.index_group*, %struct.index_group** %srcg, align 8, !dbg !1752
  %last29 = getelementptr inbounds %struct.index_group, %struct.index_group* %53, i32 0, i32 3, !dbg !1753
  %54 = load i64, i64* %last29, align 8, !dbg !1753
  %add30 = add i64 %54, 1, !dbg !1754
  %mul31 = mul i64 %add30, 16, !dbg !1755
  call void @llvm.memcpy.p0i8.p0i8.i64(i8* %50, i8* %52, i64 %mul31, i32 8, i1 false), !dbg !1749
  %55 = load %struct.index_group*, %struct.index_group** %srcg, align 8, !dbg !1756
  %last32 = getelementptr inbounds %struct.index_group, %struct.index_group* %55, i32 0, i32 3, !dbg !1757
  %56 = load i64, i64* %last32, align 8, !dbg !1757
  %add33 = add i64 %56, 1, !dbg !1758
  %57 = load i64, i64* %i, align 8, !dbg !1759
  %add34 = add i64 %57, %add33, !dbg !1759
  store i64 %add34, i64* %i, align 8, !dbg !1759
  %58 = load %struct.index_group*, %struct.index_group** %srcg, align 8, !dbg !1760
  %node35 = getelementptr inbounds %struct.index_group, %struct.index_group* %58, i32 0, i32 0, !dbg !1761
  %call36 = call i8* @index_tree_next(%struct.index_tree_node_s* %node35), !dbg !1762
  %59 = bitcast i8* %call36 to %struct.index_group*, !dbg !1762
  store %struct.index_group* %59, %struct.index_group** %srcg, align 8, !dbg !1763
  br label %do.cond, !dbg !1764

do.cond:                                          ; preds = %do.body
  %60 = load %struct.index_group*, %struct.index_group** %srcg, align 8, !dbg !1765
  %cmp37 = icmp ne %struct.index_group* %60, null, !dbg !1767
  br i1 %cmp37, label %do.body, label %do.end, !dbg !1768

do.end:                                           ; preds = %do.cond
  %61 = load i64, i64* %i, align 8, !dbg !1769
  %62 = load %struct.index_group*, %struct.index_group** %destg, align 8, !dbg !1769
  %allocated39 = getelementptr inbounds %struct.index_group, %struct.index_group* %62, i32 0, i32 2, !dbg !1769
  %63 = load i64, i64* %allocated39, align 8, !dbg !1769
  %cmp40 = icmp eq i64 %61, %63, !dbg !1769
  br i1 %cmp40, label %cond.true, label %cond.false, !dbg !1769

cond.true:                                        ; preds = %do.end
  br label %cond.end, !dbg !1770

cond.false:                                       ; preds = %do.end
  call void @__assert_fail(i8* getelementptr inbounds ([22 x i8], [22 x i8]* @.str.12, i32 0, i32 0), i8* getelementptr inbounds ([77 x i8], [77 x i8]* @.str.1, i32 0, i32 0), i32 934, i8* getelementptr inbounds ([71 x i8], [71 x i8]* @__PRETTY_FUNCTION__.index_dup_stream, i32 0, i32 0)) #8, !dbg !1771
  unreachable, !dbg !1771
                                                  ; No predecessors!
  br label %cond.end, !dbg !1773

cond.end:                                         ; preds = %64, %cond.true
  %65 = load %struct.index_stream*, %struct.index_stream** %dest, align 8, !dbg !1775
  %groups42 = getelementptr inbounds %struct.index_stream, %struct.index_stream* %65, i32 0, i32 3, !dbg !1776
  %66 = load %struct.index_group*, %struct.index_group** %destg, align 8, !dbg !1777
  %node43 = getelementptr inbounds %struct.index_group, %struct.index_group* %66, i32 0, i32 0, !dbg !1778
  call void @index_tree_append(%struct.index_tree* %groups42, %struct.index_tree_node_s* %node43), !dbg !1779
  %67 = load %struct.index_stream*, %struct.index_stream** %dest, align 8, !dbg !1780
  store %struct.index_stream* %67, %struct.index_stream** %retval, align 8, !dbg !1781
  br label %return, !dbg !1781

return:                                           ; preds = %cond.end, %if.then17, %if.then6, %if.then
  %68 = load %struct.index_stream*, %struct.index_stream** %retval, align 8, !dbg !1782
  ret %struct.index_stream* %68, !dbg !1782
}

; Function Attrs: nounwind uwtable
define internal i8* @index_tree_next(%struct.index_tree_node_s* %node) #0 !dbg !326 {
entry:
  %retval = alloca i8*, align 8
  %node.addr = alloca %struct.index_tree_node_s*, align 8
  store %struct.index_tree_node_s* %node, %struct.index_tree_node_s** %node.addr, align 8
  call void @llvm.dbg.declare(metadata %struct.index_tree_node_s** %node.addr, metadata !1783, metadata !341), !dbg !1784
  %0 = load %struct.index_tree_node_s*, %struct.index_tree_node_s** %node.addr, align 8, !dbg !1785
  %right = getelementptr inbounds %struct.index_tree_node_s, %struct.index_tree_node_s* %0, i32 0, i32 4, !dbg !1787
  %1 = load %struct.index_tree_node_s*, %struct.index_tree_node_s** %right, align 8, !dbg !1787
  %cmp = icmp ne %struct.index_tree_node_s* %1, null, !dbg !1788
  br i1 %cmp, label %if.then, label %if.end, !dbg !1789

if.then:                                          ; preds = %entry
  %2 = load %struct.index_tree_node_s*, %struct.index_tree_node_s** %node.addr, align 8, !dbg !1790
  %right1 = getelementptr inbounds %struct.index_tree_node_s, %struct.index_tree_node_s* %2, i32 0, i32 4, !dbg !1792
  %3 = load %struct.index_tree_node_s*, %struct.index_tree_node_s** %right1, align 8, !dbg !1792
  store %struct.index_tree_node_s* %3, %struct.index_tree_node_s** %node.addr, align 8, !dbg !1793
  br label %while.cond, !dbg !1794

while.cond:                                       ; preds = %while.body, %if.then
  %4 = load %struct.index_tree_node_s*, %struct.index_tree_node_s** %node.addr, align 8, !dbg !1795
  %left = getelementptr inbounds %struct.index_tree_node_s, %struct.index_tree_node_s* %4, i32 0, i32 3, !dbg !1797
  %5 = load %struct.index_tree_node_s*, %struct.index_tree_node_s** %left, align 8, !dbg !1797
  %cmp2 = icmp ne %struct.index_tree_node_s* %5, null, !dbg !1798
  br i1 %cmp2, label %while.body, label %while.end, !dbg !1799

while.body:                                       ; preds = %while.cond
  %6 = load %struct.index_tree_node_s*, %struct.index_tree_node_s** %node.addr, align 8, !dbg !1800
  %left3 = getelementptr inbounds %struct.index_tree_node_s, %struct.index_tree_node_s* %6, i32 0, i32 3, !dbg !1801
  %7 = load %struct.index_tree_node_s*, %struct.index_tree_node_s** %left3, align 8, !dbg !1801
  store %struct.index_tree_node_s* %7, %struct.index_tree_node_s** %node.addr, align 8, !dbg !1802
  br label %while.cond, !dbg !1803

while.end:                                        ; preds = %while.cond
  %8 = load %struct.index_tree_node_s*, %struct.index_tree_node_s** %node.addr, align 8, !dbg !1805
  %9 = bitcast %struct.index_tree_node_s* %8 to i8*, !dbg !1806
  store i8* %9, i8** %retval, align 8, !dbg !1807
  br label %return, !dbg !1807

if.end:                                           ; preds = %entry
  br label %while.cond4, !dbg !1808

while.cond4:                                      ; preds = %while.body9, %if.end
  %10 = load %struct.index_tree_node_s*, %struct.index_tree_node_s** %node.addr, align 8, !dbg !1809
  %parent = getelementptr inbounds %struct.index_tree_node_s, %struct.index_tree_node_s* %10, i32 0, i32 2, !dbg !1811
  %11 = load %struct.index_tree_node_s*, %struct.index_tree_node_s** %parent, align 8, !dbg !1811
  %cmp5 = icmp ne %struct.index_tree_node_s* %11, null, !dbg !1812
  br i1 %cmp5, label %land.rhs, label %land.end, !dbg !1813

land.rhs:                                         ; preds = %while.cond4
  %12 = load %struct.index_tree_node_s*, %struct.index_tree_node_s** %node.addr, align 8, !dbg !1814
  %parent6 = getelementptr inbounds %struct.index_tree_node_s, %struct.index_tree_node_s* %12, i32 0, i32 2, !dbg !1816
  %13 = load %struct.index_tree_node_s*, %struct.index_tree_node_s** %parent6, align 8, !dbg !1816
  %right7 = getelementptr inbounds %struct.index_tree_node_s, %struct.index_tree_node_s* %13, i32 0, i32 4, !dbg !1817
  %14 = load %struct.index_tree_node_s*, %struct.index_tree_node_s** %right7, align 8, !dbg !1817
  %15 = load %struct.index_tree_node_s*, %struct.index_tree_node_s** %node.addr, align 8, !dbg !1818
  %cmp8 = icmp eq %struct.index_tree_node_s* %14, %15, !dbg !1819
  br label %land.end

land.end:                                         ; preds = %land.rhs, %while.cond4
  %16 = phi i1 [ false, %while.cond4 ], [ %cmp8, %land.rhs ]
  br i1 %16, label %while.body9, label %while.end11, !dbg !1820

while.body9:                                      ; preds = %land.end
  %17 = load %struct.index_tree_node_s*, %struct.index_tree_node_s** %node.addr, align 8, !dbg !1822
  %parent10 = getelementptr inbounds %struct.index_tree_node_s, %struct.index_tree_node_s* %17, i32 0, i32 2, !dbg !1823
  %18 = load %struct.index_tree_node_s*, %struct.index_tree_node_s** %parent10, align 8, !dbg !1823
  store %struct.index_tree_node_s* %18, %struct.index_tree_node_s** %node.addr, align 8, !dbg !1824
  br label %while.cond4, !dbg !1825

while.end11:                                      ; preds = %land.end
  %19 = load %struct.index_tree_node_s*, %struct.index_tree_node_s** %node.addr, align 8, !dbg !1827
  %parent12 = getelementptr inbounds %struct.index_tree_node_s, %struct.index_tree_node_s* %19, i32 0, i32 2, !dbg !1828
  %20 = load %struct.index_tree_node_s*, %struct.index_tree_node_s** %parent12, align 8, !dbg !1828
  %21 = bitcast %struct.index_tree_node_s* %20 to i8*, !dbg !1829
  store i8* %21, i8** %retval, align 8, !dbg !1830
  br label %return, !dbg !1830

return:                                           ; preds = %while.end11, %while.end
  %22 = load i8*, i8** %retval, align 8, !dbg !1831
  ret i8* %22, !dbg !1831
}

; Function Attrs: nounwind uwtable
define void @lzma_index_iter_init(%struct.lzma_index_iter* %iter, %struct.lzma_index_s* %i) #0 !dbg !207 {
entry:
  %iter.addr = alloca %struct.lzma_index_iter*, align 8
  %i.addr = alloca %struct.lzma_index_s*, align 8
  store %struct.lzma_index_iter* %iter, %struct.lzma_index_iter** %iter.addr, align 8
  call void @llvm.dbg.declare(metadata %struct.lzma_index_iter** %iter.addr, metadata !1832, metadata !341), !dbg !1833
  store %struct.lzma_index_s* %i, %struct.lzma_index_s** %i.addr, align 8
  call void @llvm.dbg.declare(metadata %struct.lzma_index_s** %i.addr, metadata !1834, metadata !341), !dbg !1835
  %0 = load %struct.lzma_index_s*, %struct.lzma_index_s** %i.addr, align 8, !dbg !1836
  %1 = bitcast %struct.lzma_index_s* %0 to i8*, !dbg !1836
  %2 = load %struct.lzma_index_iter*, %struct.lzma_index_iter** %iter.addr, align 8, !dbg !1837
  %internal = getelementptr inbounds %struct.lzma_index_iter, %struct.lzma_index_iter* %2, i32 0, i32 2, !dbg !1838
  %arrayidx = getelementptr inbounds [6 x %union.anon], [6 x %union.anon]* %internal, i64 0, i64 0, !dbg !1837
  %p = bitcast %union.anon* %arrayidx to i8**, !dbg !1839
  store i8* %1, i8** %p, align 8, !dbg !1840
  %3 = load %struct.lzma_index_iter*, %struct.lzma_index_iter** %iter.addr, align 8, !dbg !1841
  call void @lzma_index_iter_rewind(%struct.lzma_index_iter* %3) #9, !dbg !1842
  ret void, !dbg !1843
}

; Function Attrs: nounwind uwtable
define void @lzma_index_iter_rewind(%struct.lzma_index_iter* %iter) #0 !dbg !263 {
entry:
  %iter.addr = alloca %struct.lzma_index_iter*, align 8
  store %struct.lzma_index_iter* %iter, %struct.lzma_index_iter** %iter.addr, align 8
  call void @llvm.dbg.declare(metadata %struct.lzma_index_iter** %iter.addr, metadata !1844, metadata !341), !dbg !1845
  %0 = load %struct.lzma_index_iter*, %struct.lzma_index_iter** %iter.addr, align 8, !dbg !1846
  %internal = getelementptr inbounds %struct.lzma_index_iter, %struct.lzma_index_iter* %0, i32 0, i32 2, !dbg !1847
  %arrayidx = getelementptr inbounds [6 x %union.anon], [6 x %union.anon]* %internal, i64 0, i64 1, !dbg !1846
  %p = bitcast %union.anon* %arrayidx to i8**, !dbg !1848
  store i8* null, i8** %p, align 8, !dbg !1849
  %1 = load %struct.lzma_index_iter*, %struct.lzma_index_iter** %iter.addr, align 8, !dbg !1850
  %internal1 = getelementptr inbounds %struct.lzma_index_iter, %struct.lzma_index_iter* %1, i32 0, i32 2, !dbg !1851
  %arrayidx2 = getelementptr inbounds [6 x %union.anon], [6 x %union.anon]* %internal1, i64 0, i64 2, !dbg !1850
  %p3 = bitcast %union.anon* %arrayidx2 to i8**, !dbg !1852
  store i8* null, i8** %p3, align 8, !dbg !1853
  %2 = load %struct.lzma_index_iter*, %struct.lzma_index_iter** %iter.addr, align 8, !dbg !1854
  %internal4 = getelementptr inbounds %struct.lzma_index_iter, %struct.lzma_index_iter* %2, i32 0, i32 2, !dbg !1855
  %arrayidx5 = getelementptr inbounds [6 x %union.anon], [6 x %union.anon]* %internal4, i64 0, i64 3, !dbg !1854
  %s = bitcast %union.anon* %arrayidx5 to i64*, !dbg !1856
  store i64 0, i64* %s, align 8, !dbg !1857
  %3 = load %struct.lzma_index_iter*, %struct.lzma_index_iter** %iter.addr, align 8, !dbg !1858
  %internal6 = getelementptr inbounds %struct.lzma_index_iter, %struct.lzma_index_iter* %3, i32 0, i32 2, !dbg !1859
  %arrayidx7 = getelementptr inbounds [6 x %union.anon], [6 x %union.anon]* %internal6, i64 0, i64 4, !dbg !1858
  %s8 = bitcast %union.anon* %arrayidx7 to i64*, !dbg !1860
  store i64 0, i64* %s8, align 8, !dbg !1861
  ret void, !dbg !1862
}

; Function Attrs: nounwind uwtable
define zeroext i8 @lzma_index_iter_next(%struct.lzma_index_iter* %iter, i32 %mode) #0 !dbg !266 {
entry:
  %retval = alloca i8, align 1
  %iter.addr = alloca %struct.lzma_index_iter*, align 8
  %mode.addr = alloca i32, align 4
  %i = alloca %struct.lzma_index_s*, align 8
  %stream = alloca %struct.index_stream*, align 8
  %group = alloca %struct.index_group*, align 8
  %record = alloca i64, align 8
  store %struct.lzma_index_iter* %iter, %struct.lzma_index_iter** %iter.addr, align 8
  call void @llvm.dbg.declare(metadata %struct.lzma_index_iter** %iter.addr, metadata !1863, metadata !341), !dbg !1864
  store i32 %mode, i32* %mode.addr, align 4
  call void @llvm.dbg.declare(metadata i32* %mode.addr, metadata !1865, metadata !341), !dbg !1866
  call void @llvm.dbg.declare(metadata %struct.lzma_index_s** %i, metadata !1867, metadata !341), !dbg !1868
  call void @llvm.dbg.declare(metadata %struct.index_stream** %stream, metadata !1869, metadata !341), !dbg !1870
  call void @llvm.dbg.declare(metadata %struct.index_group** %group, metadata !1871, metadata !341), !dbg !1872
  call void @llvm.dbg.declare(metadata i64* %record, metadata !1873, metadata !341), !dbg !1874
  %0 = load i32, i32* %mode.addr, align 4, !dbg !1875
  %cmp = icmp ugt i32 %0, 3, !dbg !1877
  br i1 %cmp, label %if.then, label %if.end, !dbg !1878

if.then:                                          ; preds = %entry
  store i8 1, i8* %retval, align 1, !dbg !1879
  br label %return, !dbg !1879

if.end:                                           ; preds = %entry
  %1 = load %struct.lzma_index_iter*, %struct.lzma_index_iter** %iter.addr, align 8, !dbg !1880
  %internal = getelementptr inbounds %struct.lzma_index_iter, %struct.lzma_index_iter* %1, i32 0, i32 2, !dbg !1881
  %arrayidx = getelementptr inbounds [6 x %union.anon], [6 x %union.anon]* %internal, i64 0, i64 0, !dbg !1880
  %p = bitcast %union.anon* %arrayidx to i8**, !dbg !1882
  %2 = load i8*, i8** %p, align 8, !dbg !1882
  %3 = bitcast i8* %2 to %struct.lzma_index_s*, !dbg !1880
  store %struct.lzma_index_s* %3, %struct.lzma_index_s** %i, align 8, !dbg !1883
  %4 = load %struct.lzma_index_iter*, %struct.lzma_index_iter** %iter.addr, align 8, !dbg !1884
  %internal1 = getelementptr inbounds %struct.lzma_index_iter, %struct.lzma_index_iter* %4, i32 0, i32 2, !dbg !1885
  %arrayidx2 = getelementptr inbounds [6 x %union.anon], [6 x %union.anon]* %internal1, i64 0, i64 1, !dbg !1884
  %p3 = bitcast %union.anon* %arrayidx2 to i8**, !dbg !1886
  %5 = load i8*, i8** %p3, align 8, !dbg !1886
  %6 = bitcast i8* %5 to %struct.index_stream*, !dbg !1884
  store %struct.index_stream* %6, %struct.index_stream** %stream, align 8, !dbg !1887
  store %struct.index_group* null, %struct.index_group** %group, align 8, !dbg !1888
  %7 = load %struct.lzma_index_iter*, %struct.lzma_index_iter** %iter.addr, align 8, !dbg !1889
  %internal4 = getelementptr inbounds %struct.lzma_index_iter, %struct.lzma_index_iter* %7, i32 0, i32 2, !dbg !1890
  %arrayidx5 = getelementptr inbounds [6 x %union.anon], [6 x %union.anon]* %internal4, i64 0, i64 3, !dbg !1889
  %s = bitcast %union.anon* %arrayidx5 to i64*, !dbg !1891
  %8 = load i64, i64* %s, align 8, !dbg !1891
  store i64 %8, i64* %record, align 8, !dbg !1892
  %9 = load i32, i32* %mode.addr, align 4, !dbg !1893
  %cmp6 = icmp ne i32 %9, 1, !dbg !1895
  br i1 %cmp6, label %if.then7, label %if.end19, !dbg !1896

if.then7:                                         ; preds = %if.end
  %10 = load %struct.lzma_index_iter*, %struct.lzma_index_iter** %iter.addr, align 8, !dbg !1897
  %internal8 = getelementptr inbounds %struct.lzma_index_iter, %struct.lzma_index_iter* %10, i32 0, i32 2, !dbg !1899
  %arrayidx9 = getelementptr inbounds [6 x %union.anon], [6 x %union.anon]* %internal8, i64 0, i64 4, !dbg !1897
  %s10 = bitcast %union.anon* %arrayidx9 to i64*, !dbg !1900
  %11 = load i64, i64* %s10, align 8, !dbg !1900
  switch i64 %11, label %sw.epilog [
    i64 0, label %sw.bb
    i64 1, label %sw.bb14
    i64 2, label %sw.bb18
  ], !dbg !1901

sw.bb:                                            ; preds = %if.then7
  %12 = load %struct.lzma_index_iter*, %struct.lzma_index_iter** %iter.addr, align 8, !dbg !1902
  %internal11 = getelementptr inbounds %struct.lzma_index_iter, %struct.lzma_index_iter* %12, i32 0, i32 2, !dbg !1904
  %arrayidx12 = getelementptr inbounds [6 x %union.anon], [6 x %union.anon]* %internal11, i64 0, i64 2, !dbg !1902
  %p13 = bitcast %union.anon* %arrayidx12 to i8**, !dbg !1905
  %13 = load i8*, i8** %p13, align 8, !dbg !1905
  %14 = bitcast i8* %13 to %struct.index_group*, !dbg !1902
  store %struct.index_group* %14, %struct.index_group** %group, align 8, !dbg !1906
  br label %sw.epilog, !dbg !1907

sw.bb14:                                          ; preds = %if.then7
  %15 = load %struct.lzma_index_iter*, %struct.lzma_index_iter** %iter.addr, align 8, !dbg !1908
  %internal15 = getelementptr inbounds %struct.lzma_index_iter, %struct.lzma_index_iter* %15, i32 0, i32 2, !dbg !1909
  %arrayidx16 = getelementptr inbounds [6 x %union.anon], [6 x %union.anon]* %internal15, i64 0, i64 2, !dbg !1908
  %p17 = bitcast %union.anon* %arrayidx16 to i8**, !dbg !1910
  %16 = load i8*, i8** %p17, align 8, !dbg !1910
  %17 = bitcast i8* %16 to %struct.index_tree_node_s*, !dbg !1908
  %call = call i8* @index_tree_next(%struct.index_tree_node_s* %17), !dbg !1911
  %18 = bitcast i8* %call to %struct.index_group*, !dbg !1911
  store %struct.index_group* %18, %struct.index_group** %group, align 8, !dbg !1912
  br label %sw.epilog, !dbg !1913

sw.bb18:                                          ; preds = %if.then7
  %19 = load %struct.index_stream*, %struct.index_stream** %stream, align 8, !dbg !1914
  %groups = getelementptr inbounds %struct.index_stream, %struct.index_stream* %19, i32 0, i32 3, !dbg !1915
  %leftmost = getelementptr inbounds %struct.index_tree, %struct.index_tree* %groups, i32 0, i32 1, !dbg !1916
  %20 = load %struct.index_tree_node_s*, %struct.index_tree_node_s** %leftmost, align 8, !dbg !1916
  %21 = bitcast %struct.index_tree_node_s* %20 to %struct.index_group*, !dbg !1917
  store %struct.index_group* %21, %struct.index_group** %group, align 8, !dbg !1918
  br label %sw.epilog, !dbg !1919

sw.epilog:                                        ; preds = %if.then7, %sw.bb18, %sw.bb14, %sw.bb
  br label %if.end19, !dbg !1920

if.end19:                                         ; preds = %sw.epilog, %if.end
  br label %again, !dbg !1921

again:                                            ; preds = %if.then77, %if.then67, %if.end19
  %22 = load %struct.index_stream*, %struct.index_stream** %stream, align 8, !dbg !1923
  %cmp20 = icmp eq %struct.index_stream* %22, null, !dbg !1925
  br i1 %cmp20, label %if.then21, label %if.else, !dbg !1926

if.then21:                                        ; preds = %again
  %23 = load %struct.lzma_index_s*, %struct.lzma_index_s** %i, align 8, !dbg !1927
  %streams = getelementptr inbounds %struct.lzma_index_s, %struct.lzma_index_s* %23, i32 0, i32 0, !dbg !1929
  %leftmost22 = getelementptr inbounds %struct.index_tree, %struct.index_tree* %streams, i32 0, i32 1, !dbg !1930
  %24 = load %struct.index_tree_node_s*, %struct.index_tree_node_s** %leftmost22, align 8, !dbg !1930
  %25 = bitcast %struct.index_tree_node_s* %24 to %struct.index_stream*, !dbg !1931
  store %struct.index_stream* %25, %struct.index_stream** %stream, align 8, !dbg !1932
  %26 = load i32, i32* %mode.addr, align 4, !dbg !1933
  %cmp23 = icmp uge i32 %26, 2, !dbg !1935
  br i1 %cmp23, label %if.then24, label %if.end32, !dbg !1936

if.then24:                                        ; preds = %if.then21
  br label %while.cond, !dbg !1937

while.cond:                                       ; preds = %if.end31, %if.then24
  %27 = load %struct.index_stream*, %struct.index_stream** %stream, align 8, !dbg !1939
  %groups25 = getelementptr inbounds %struct.index_stream, %struct.index_stream* %27, i32 0, i32 3, !dbg !1941
  %leftmost26 = getelementptr inbounds %struct.index_tree, %struct.index_tree* %groups25, i32 0, i32 1, !dbg !1942
  %28 = load %struct.index_tree_node_s*, %struct.index_tree_node_s** %leftmost26, align 8, !dbg !1942
  %cmp27 = icmp eq %struct.index_tree_node_s* %28, null, !dbg !1943
  br i1 %cmp27, label %while.body, label %while.end, !dbg !1944

while.body:                                       ; preds = %while.cond
  %29 = load %struct.index_stream*, %struct.index_stream** %stream, align 8, !dbg !1945
  %node = getelementptr inbounds %struct.index_stream, %struct.index_stream* %29, i32 0, i32 0, !dbg !1947
  %call28 = call i8* @index_tree_next(%struct.index_tree_node_s* %node), !dbg !1948
  %30 = bitcast i8* %call28 to %struct.index_stream*, !dbg !1948
  store %struct.index_stream* %30, %struct.index_stream** %stream, align 8, !dbg !1949
  %31 = load %struct.index_stream*, %struct.index_stream** %stream, align 8, !dbg !1950
  %cmp29 = icmp eq %struct.index_stream* %31, null, !dbg !1952
  br i1 %cmp29, label %if.then30, label %if.end31, !dbg !1953

if.then30:                                        ; preds = %while.body
  store i8 1, i8* %retval, align 1, !dbg !1954
  br label %return, !dbg !1954

if.end31:                                         ; preds = %while.body
  br label %while.cond, !dbg !1955

while.end:                                        ; preds = %while.cond
  br label %if.end32, !dbg !1957

if.end32:                                         ; preds = %while.end, %if.then21
  %32 = load %struct.index_stream*, %struct.index_stream** %stream, align 8, !dbg !1958
  %groups33 = getelementptr inbounds %struct.index_stream, %struct.index_stream* %32, i32 0, i32 3, !dbg !1959
  %leftmost34 = getelementptr inbounds %struct.index_tree, %struct.index_tree* %groups33, i32 0, i32 1, !dbg !1960
  %33 = load %struct.index_tree_node_s*, %struct.index_tree_node_s** %leftmost34, align 8, !dbg !1960
  %34 = bitcast %struct.index_tree_node_s* %33 to %struct.index_group*, !dbg !1961
  store %struct.index_group* %34, %struct.index_group** %group, align 8, !dbg !1962
  store i64 0, i64* %record, align 8, !dbg !1963
  br label %if.end59, !dbg !1964

if.else:                                          ; preds = %again
  %35 = load %struct.index_group*, %struct.index_group** %group, align 8, !dbg !1965
  %cmp35 = icmp ne %struct.index_group* %35, null, !dbg !1968
  br i1 %cmp35, label %land.lhs.true, label %if.else38, !dbg !1969

land.lhs.true:                                    ; preds = %if.else
  %36 = load i64, i64* %record, align 8, !dbg !1970
  %37 = load %struct.index_group*, %struct.index_group** %group, align 8, !dbg !1972
  %last = getelementptr inbounds %struct.index_group, %struct.index_group* %37, i32 0, i32 3, !dbg !1973
  %38 = load i64, i64* %last, align 8, !dbg !1973
  %cmp36 = icmp ult i64 %36, %38, !dbg !1974
  br i1 %cmp36, label %if.then37, label %if.else38, !dbg !1975

if.then37:                                        ; preds = %land.lhs.true
  %39 = load i64, i64* %record, align 8, !dbg !1976
  %inc = add i64 %39, 1, !dbg !1976
  store i64 %inc, i64* %record, align 8, !dbg !1976
  br label %if.end58, !dbg !1978

if.else38:                                        ; preds = %land.lhs.true, %if.else
  store i64 0, i64* %record, align 8, !dbg !1979
  %40 = load %struct.index_group*, %struct.index_group** %group, align 8, !dbg !1981
  %cmp39 = icmp ne %struct.index_group* %40, null, !dbg !1983
  br i1 %cmp39, label %if.then40, label %if.end43, !dbg !1984

if.then40:                                        ; preds = %if.else38
  %41 = load %struct.index_group*, %struct.index_group** %group, align 8, !dbg !1985
  %node41 = getelementptr inbounds %struct.index_group, %struct.index_group* %41, i32 0, i32 0, !dbg !1986
  %call42 = call i8* @index_tree_next(%struct.index_tree_node_s* %node41), !dbg !1987
  %42 = bitcast i8* %call42 to %struct.index_group*, !dbg !1987
  store %struct.index_group* %42, %struct.index_group** %group, align 8, !dbg !1988
  br label %if.end43, !dbg !1989

if.end43:                                         ; preds = %if.then40, %if.else38
  %43 = load %struct.index_group*, %struct.index_group** %group, align 8, !dbg !1990
  %cmp44 = icmp eq %struct.index_group* %43, null, !dbg !1992
  br i1 %cmp44, label %if.then45, label %if.end57, !dbg !1993

if.then45:                                        ; preds = %if.end43
  br label %do.body, !dbg !1994

do.body:                                          ; preds = %land.end, %if.then45
  %44 = load %struct.index_stream*, %struct.index_stream** %stream, align 8, !dbg !1996
  %node46 = getelementptr inbounds %struct.index_stream, %struct.index_stream* %44, i32 0, i32 0, !dbg !1998
  %call47 = call i8* @index_tree_next(%struct.index_tree_node_s* %node46), !dbg !1999
  %45 = bitcast i8* %call47 to %struct.index_stream*, !dbg !1999
  store %struct.index_stream* %45, %struct.index_stream** %stream, align 8, !dbg !2000
  %46 = load %struct.index_stream*, %struct.index_stream** %stream, align 8, !dbg !2001
  %cmp48 = icmp eq %struct.index_stream* %46, null, !dbg !2003
  br i1 %cmp48, label %if.then49, label %if.end50, !dbg !2004

if.then49:                                        ; preds = %do.body
  store i8 1, i8* %retval, align 1, !dbg !2005
  br label %return, !dbg !2005

if.end50:                                         ; preds = %do.body
  br label %do.cond, !dbg !2006

do.cond:                                          ; preds = %if.end50
  %47 = load i32, i32* %mode.addr, align 4, !dbg !2007
  %cmp51 = icmp uge i32 %47, 2, !dbg !2009
  br i1 %cmp51, label %land.rhs, label %land.end, !dbg !2010

land.rhs:                                         ; preds = %do.cond
  %48 = load %struct.index_stream*, %struct.index_stream** %stream, align 8, !dbg !2011
  %groups52 = getelementptr inbounds %struct.index_stream, %struct.index_stream* %48, i32 0, i32 3, !dbg !2012
  %leftmost53 = getelementptr inbounds %struct.index_tree, %struct.index_tree* %groups52, i32 0, i32 1, !dbg !2013
  %49 = load %struct.index_tree_node_s*, %struct.index_tree_node_s** %leftmost53, align 8, !dbg !2013
  %cmp54 = icmp eq %struct.index_tree_node_s* %49, null, !dbg !2014
  br label %land.end

land.end:                                         ; preds = %land.rhs, %do.cond
  %50 = phi i1 [ false, %do.cond ], [ %cmp54, %land.rhs ]
  br i1 %50, label %do.body, label %do.end, !dbg !2015

do.end:                                           ; preds = %land.end
  %51 = load %struct.index_stream*, %struct.index_stream** %stream, align 8, !dbg !2017
  %groups55 = getelementptr inbounds %struct.index_stream, %struct.index_stream* %51, i32 0, i32 3, !dbg !2018
  %leftmost56 = getelementptr inbounds %struct.index_tree, %struct.index_tree* %groups55, i32 0, i32 1, !dbg !2019
  %52 = load %struct.index_tree_node_s*, %struct.index_tree_node_s** %leftmost56, align 8, !dbg !2019
  %53 = bitcast %struct.index_tree_node_s* %52 to %struct.index_group*, !dbg !2020
  store %struct.index_group* %53, %struct.index_group** %group, align 8, !dbg !2021
  br label %if.end57, !dbg !2022

if.end57:                                         ; preds = %do.end, %if.end43
  br label %if.end58

if.end58:                                         ; preds = %if.end57, %if.then37
  br label %if.end59

if.end59:                                         ; preds = %if.end58, %if.end32
  %54 = load i32, i32* %mode.addr, align 4, !dbg !2023
  %cmp60 = icmp eq i32 %54, 3, !dbg !2025
  br i1 %cmp60, label %if.then61, label %if.end80, !dbg !2026

if.then61:                                        ; preds = %if.end59
  %55 = load i64, i64* %record, align 8, !dbg !2027
  %cmp62 = icmp eq i64 %55, 0, !dbg !2030
  br i1 %cmp62, label %if.then63, label %if.else69, !dbg !2031

if.then63:                                        ; preds = %if.then61
  %56 = load %struct.index_group*, %struct.index_group** %group, align 8, !dbg !2032
  %node64 = getelementptr inbounds %struct.index_group, %struct.index_group* %56, i32 0, i32 0, !dbg !2035
  %uncompressed_base = getelementptr inbounds %struct.index_tree_node_s, %struct.index_tree_node_s* %node64, i32 0, i32 0, !dbg !2036
  %57 = load i64, i64* %uncompressed_base, align 8, !dbg !2036
  %58 = load %struct.index_group*, %struct.index_group** %group, align 8, !dbg !2037
  %records = getelementptr inbounds %struct.index_group, %struct.index_group* %58, i32 0, i32 4, !dbg !2038
  %arrayidx65 = getelementptr inbounds [0 x %struct.index_record], [0 x %struct.index_record]* %records, i64 0, i64 0, !dbg !2037
  %uncompressed_sum = getelementptr inbounds %struct.index_record, %struct.index_record* %arrayidx65, i32 0, i32 0, !dbg !2039
  %59 = load i64, i64* %uncompressed_sum, align 8, !dbg !2039
  %cmp66 = icmp eq i64 %57, %59, !dbg !2040
  br i1 %cmp66, label %if.then67, label %if.end68, !dbg !2041

if.then67:                                        ; preds = %if.then63
  br label %again, !dbg !2042

if.end68:                                         ; preds = %if.then63
  br label %if.end79, !dbg !2043

if.else69:                                        ; preds = %if.then61
  %60 = load i64, i64* %record, align 8, !dbg !2044
  %sub = sub i64 %60, 1, !dbg !2047
  %61 = load %struct.index_group*, %struct.index_group** %group, align 8, !dbg !2048
  %records70 = getelementptr inbounds %struct.index_group, %struct.index_group* %61, i32 0, i32 4, !dbg !2049
  %arrayidx71 = getelementptr inbounds [0 x %struct.index_record], [0 x %struct.index_record]* %records70, i64 0, i64 %sub, !dbg !2048
  %uncompressed_sum72 = getelementptr inbounds %struct.index_record, %struct.index_record* %arrayidx71, i32 0, i32 0, !dbg !2050
  %62 = load i64, i64* %uncompressed_sum72, align 8, !dbg !2050
  %63 = load i64, i64* %record, align 8, !dbg !2051
  %64 = load %struct.index_group*, %struct.index_group** %group, align 8, !dbg !2052
  %records73 = getelementptr inbounds %struct.index_group, %struct.index_group* %64, i32 0, i32 4, !dbg !2053
  %arrayidx74 = getelementptr inbounds [0 x %struct.index_record], [0 x %struct.index_record]* %records73, i64 0, i64 %63, !dbg !2052
  %uncompressed_sum75 = getelementptr inbounds %struct.index_record, %struct.index_record* %arrayidx74, i32 0, i32 0, !dbg !2054
  %65 = load i64, i64* %uncompressed_sum75, align 8, !dbg !2054
  %cmp76 = icmp eq i64 %62, %65, !dbg !2055
  br i1 %cmp76, label %if.then77, label %if.end78, !dbg !2048

if.then77:                                        ; preds = %if.else69
  br label %again, !dbg !2056

if.end78:                                         ; preds = %if.else69
  br label %if.end79

if.end79:                                         ; preds = %if.end78, %if.end68
  br label %if.end80, !dbg !2058

if.end80:                                         ; preds = %if.end79, %if.end59
  %66 = load %struct.index_stream*, %struct.index_stream** %stream, align 8, !dbg !2059
  %67 = bitcast %struct.index_stream* %66 to i8*, !dbg !2059
  %68 = load %struct.lzma_index_iter*, %struct.lzma_index_iter** %iter.addr, align 8, !dbg !2060
  %internal81 = getelementptr inbounds %struct.lzma_index_iter, %struct.lzma_index_iter* %68, i32 0, i32 2, !dbg !2061
  %arrayidx82 = getelementptr inbounds [6 x %union.anon], [6 x %union.anon]* %internal81, i64 0, i64 1, !dbg !2060
  %p83 = bitcast %union.anon* %arrayidx82 to i8**, !dbg !2062
  store i8* %67, i8** %p83, align 8, !dbg !2063
  %69 = load %struct.index_group*, %struct.index_group** %group, align 8, !dbg !2064
  %70 = bitcast %struct.index_group* %69 to i8*, !dbg !2064
  %71 = load %struct.lzma_index_iter*, %struct.lzma_index_iter** %iter.addr, align 8, !dbg !2065
  %internal84 = getelementptr inbounds %struct.lzma_index_iter, %struct.lzma_index_iter* %71, i32 0, i32 2, !dbg !2066
  %arrayidx85 = getelementptr inbounds [6 x %union.anon], [6 x %union.anon]* %internal84, i64 0, i64 2, !dbg !2065
  %p86 = bitcast %union.anon* %arrayidx85 to i8**, !dbg !2067
  store i8* %70, i8** %p86, align 8, !dbg !2068
  %72 = load i64, i64* %record, align 8, !dbg !2069
  %73 = load %struct.lzma_index_iter*, %struct.lzma_index_iter** %iter.addr, align 8, !dbg !2070
  %internal87 = getelementptr inbounds %struct.lzma_index_iter, %struct.lzma_index_iter* %73, i32 0, i32 2, !dbg !2071
  %arrayidx88 = getelementptr inbounds [6 x %union.anon], [6 x %union.anon]* %internal87, i64 0, i64 3, !dbg !2070
  %s89 = bitcast %union.anon* %arrayidx88 to i64*, !dbg !2072
  store i64 %72, i64* %s89, align 8, !dbg !2073
  %74 = load %struct.lzma_index_iter*, %struct.lzma_index_iter** %iter.addr, align 8, !dbg !2074
  call void @iter_set_info(%struct.lzma_index_iter* %74), !dbg !2075
  store i8 0, i8* %retval, align 1, !dbg !2076
  br label %return, !dbg !2076

return:                                           ; preds = %if.end80, %if.then49, %if.then30, %if.then
  %75 = load i8, i8* %retval, align 1, !dbg !2077
  ret i8 %75, !dbg !2077
}

; Function Attrs: nounwind uwtable
define internal void @iter_set_info(%struct.lzma_index_iter* %iter) #0 !dbg !331 {
entry:
  %iter.addr = alloca %struct.lzma_index_iter*, align 8
  %i = alloca %struct.lzma_index_s*, align 8
  %stream = alloca %struct.index_stream*, align 8
  %group = alloca %struct.index_group*, align 8
  %record = alloca i64, align 8
  %g = alloca %struct.index_group*, align 8
  store %struct.lzma_index_iter* %iter, %struct.lzma_index_iter** %iter.addr, align 8
  call void @llvm.dbg.declare(metadata %struct.lzma_index_iter** %iter.addr, metadata !2078, metadata !341), !dbg !2079
  call void @llvm.dbg.declare(metadata %struct.lzma_index_s** %i, metadata !2080, metadata !341), !dbg !2081
  %0 = load %struct.lzma_index_iter*, %struct.lzma_index_iter** %iter.addr, align 8, !dbg !2082
  %internal = getelementptr inbounds %struct.lzma_index_iter, %struct.lzma_index_iter* %0, i32 0, i32 2, !dbg !2083
  %arrayidx = getelementptr inbounds [6 x %union.anon], [6 x %union.anon]* %internal, i64 0, i64 0, !dbg !2082
  %p = bitcast %union.anon* %arrayidx to i8**, !dbg !2084
  %1 = load i8*, i8** %p, align 8, !dbg !2084
  %2 = bitcast i8* %1 to %struct.lzma_index_s*, !dbg !2082
  store %struct.lzma_index_s* %2, %struct.lzma_index_s** %i, align 8, !dbg !2081
  call void @llvm.dbg.declare(metadata %struct.index_stream** %stream, metadata !2085, metadata !341), !dbg !2086
  %3 = load %struct.lzma_index_iter*, %struct.lzma_index_iter** %iter.addr, align 8, !dbg !2087
  %internal1 = getelementptr inbounds %struct.lzma_index_iter, %struct.lzma_index_iter* %3, i32 0, i32 2, !dbg !2088
  %arrayidx2 = getelementptr inbounds [6 x %union.anon], [6 x %union.anon]* %internal1, i64 0, i64 1, !dbg !2087
  %p3 = bitcast %union.anon* %arrayidx2 to i8**, !dbg !2089
  %4 = load i8*, i8** %p3, align 8, !dbg !2089
  %5 = bitcast i8* %4 to %struct.index_stream*, !dbg !2087
  store %struct.index_stream* %5, %struct.index_stream** %stream, align 8, !dbg !2086
  call void @llvm.dbg.declare(metadata %struct.index_group** %group, metadata !2090, metadata !341), !dbg !2091
  %6 = load %struct.lzma_index_iter*, %struct.lzma_index_iter** %iter.addr, align 8, !dbg !2092
  %internal4 = getelementptr inbounds %struct.lzma_index_iter, %struct.lzma_index_iter* %6, i32 0, i32 2, !dbg !2093
  %arrayidx5 = getelementptr inbounds [6 x %union.anon], [6 x %union.anon]* %internal4, i64 0, i64 2, !dbg !2092
  %p6 = bitcast %union.anon* %arrayidx5 to i8**, !dbg !2094
  %7 = load i8*, i8** %p6, align 8, !dbg !2094
  %8 = bitcast i8* %7 to %struct.index_group*, !dbg !2092
  store %struct.index_group* %8, %struct.index_group** %group, align 8, !dbg !2091
  call void @llvm.dbg.declare(metadata i64* %record, metadata !2095, metadata !341), !dbg !2096
  %9 = load %struct.lzma_index_iter*, %struct.lzma_index_iter** %iter.addr, align 8, !dbg !2097
  %internal7 = getelementptr inbounds %struct.lzma_index_iter, %struct.lzma_index_iter* %9, i32 0, i32 2, !dbg !2098
  %arrayidx8 = getelementptr inbounds [6 x %union.anon], [6 x %union.anon]* %internal7, i64 0, i64 3, !dbg !2097
  %s = bitcast %union.anon* %arrayidx8 to i64*, !dbg !2099
  %10 = load i64, i64* %s, align 8, !dbg !2099
  store i64 %10, i64* %record, align 8, !dbg !2096
  %11 = load %struct.index_group*, %struct.index_group** %group, align 8, !dbg !2100
  %cmp = icmp eq %struct.index_group* %11, null, !dbg !2102
  br i1 %cmp, label %if.then, label %if.else, !dbg !2103

if.then:                                          ; preds = %entry
  %12 = load %struct.index_stream*, %struct.index_stream** %stream, align 8, !dbg !2104
  %groups = getelementptr inbounds %struct.index_stream, %struct.index_stream* %12, i32 0, i32 3, !dbg !2104
  %root = getelementptr inbounds %struct.index_tree, %struct.index_tree* %groups, i32 0, i32 0, !dbg !2104
  %13 = load %struct.index_tree_node_s*, %struct.index_tree_node_s** %root, align 8, !dbg !2104
  %cmp9 = icmp eq %struct.index_tree_node_s* %13, null, !dbg !2104
  br i1 %cmp9, label %cond.true, label %cond.false, !dbg !2104

cond.true:                                        ; preds = %if.then
  br label %cond.end, !dbg !2106

cond.false:                                       ; preds = %if.then
  call void @__assert_fail(i8* getelementptr inbounds ([34 x i8], [34 x i8]* @.str.13, i32 0, i32 0), i8* getelementptr inbounds ([77 x i8], [77 x i8]* @.str.1, i32 0, i32 0), i32 1009, i8* getelementptr inbounds ([38 x i8], [38 x i8]* @__PRETTY_FUNCTION__.iter_set_info, i32 0, i32 0)) #8, !dbg !2108
  unreachable, !dbg !2108
                                                  ; No predecessors!
  br label %cond.end, !dbg !2110

cond.end:                                         ; preds = %14, %cond.true
  %15 = load %struct.lzma_index_iter*, %struct.lzma_index_iter** %iter.addr, align 8, !dbg !2112
  %internal10 = getelementptr inbounds %struct.lzma_index_iter, %struct.lzma_index_iter* %15, i32 0, i32 2, !dbg !2113
  %arrayidx11 = getelementptr inbounds [6 x %union.anon], [6 x %union.anon]* %internal10, i64 0, i64 4, !dbg !2112
  %s12 = bitcast %union.anon* %arrayidx11 to i64*, !dbg !2114
  store i64 2, i64* %s12, align 8, !dbg !2115
  br label %if.end69, !dbg !2116

if.else:                                          ; preds = %entry
  %16 = load %struct.lzma_index_s*, %struct.lzma_index_s** %i, align 8, !dbg !2117
  %streams = getelementptr inbounds %struct.lzma_index_s, %struct.lzma_index_s* %16, i32 0, i32 0, !dbg !2120
  %rightmost = getelementptr inbounds %struct.index_tree, %struct.index_tree* %streams, i32 0, i32 2, !dbg !2121
  %17 = load %struct.index_tree_node_s*, %struct.index_tree_node_s** %rightmost, align 8, !dbg !2121
  %18 = load %struct.index_stream*, %struct.index_stream** %stream, align 8, !dbg !2122
  %node = getelementptr inbounds %struct.index_stream, %struct.index_stream* %18, i32 0, i32 0, !dbg !2123
  %cmp13 = icmp ne %struct.index_tree_node_s* %17, %node, !dbg !2124
  br i1 %cmp13, label %if.then18, label %lor.lhs.false, !dbg !2125

lor.lhs.false:                                    ; preds = %if.else
  %19 = load %struct.index_stream*, %struct.index_stream** %stream, align 8, !dbg !2126
  %groups14 = getelementptr inbounds %struct.index_stream, %struct.index_stream* %19, i32 0, i32 3, !dbg !2127
  %rightmost15 = getelementptr inbounds %struct.index_tree, %struct.index_tree* %groups14, i32 0, i32 2, !dbg !2128
  %20 = load %struct.index_tree_node_s*, %struct.index_tree_node_s** %rightmost15, align 8, !dbg !2128
  %21 = load %struct.index_group*, %struct.index_group** %group, align 8, !dbg !2129
  %node16 = getelementptr inbounds %struct.index_group, %struct.index_group* %21, i32 0, i32 0, !dbg !2130
  %cmp17 = icmp ne %struct.index_tree_node_s* %20, %node16, !dbg !2131
  br i1 %cmp17, label %if.then18, label %if.else22, !dbg !2132

if.then18:                                        ; preds = %lor.lhs.false, %if.else
  %22 = load %struct.lzma_index_iter*, %struct.lzma_index_iter** %iter.addr, align 8, !dbg !2134
  %internal19 = getelementptr inbounds %struct.lzma_index_iter, %struct.lzma_index_iter* %22, i32 0, i32 2, !dbg !2136
  %arrayidx20 = getelementptr inbounds [6 x %union.anon], [6 x %union.anon]* %internal19, i64 0, i64 4, !dbg !2134
  %s21 = bitcast %union.anon* %arrayidx20 to i64*, !dbg !2137
  store i64 0, i64* %s21, align 8, !dbg !2138
  br label %if.end68, !dbg !2139

if.else22:                                        ; preds = %lor.lhs.false
  %23 = load %struct.index_stream*, %struct.index_stream** %stream, align 8, !dbg !2140
  %groups23 = getelementptr inbounds %struct.index_stream, %struct.index_stream* %23, i32 0, i32 3, !dbg !2143
  %leftmost = getelementptr inbounds %struct.index_tree, %struct.index_tree* %groups23, i32 0, i32 1, !dbg !2144
  %24 = load %struct.index_tree_node_s*, %struct.index_tree_node_s** %leftmost, align 8, !dbg !2144
  %25 = load %struct.index_group*, %struct.index_group** %group, align 8, !dbg !2145
  %node24 = getelementptr inbounds %struct.index_group, %struct.index_group* %25, i32 0, i32 0, !dbg !2146
  %cmp25 = icmp ne %struct.index_tree_node_s* %24, %node24, !dbg !2147
  br i1 %cmp25, label %if.then26, label %if.else48, !dbg !2140

if.then26:                                        ; preds = %if.else22
  %26 = load %struct.index_stream*, %struct.index_stream** %stream, align 8, !dbg !2148
  %groups27 = getelementptr inbounds %struct.index_stream, %struct.index_stream* %26, i32 0, i32 3, !dbg !2148
  %root28 = getelementptr inbounds %struct.index_tree, %struct.index_tree* %groups27, i32 0, i32 0, !dbg !2148
  %27 = load %struct.index_tree_node_s*, %struct.index_tree_node_s** %root28, align 8, !dbg !2148
  %28 = load %struct.index_group*, %struct.index_group** %group, align 8, !dbg !2148
  %node29 = getelementptr inbounds %struct.index_group, %struct.index_group* %28, i32 0, i32 0, !dbg !2148
  %cmp30 = icmp ne %struct.index_tree_node_s* %27, %node29, !dbg !2148
  br i1 %cmp30, label %cond.true31, label %cond.false32, !dbg !2148

cond.true31:                                      ; preds = %if.then26
  br label %cond.end33, !dbg !2150

cond.false32:                                     ; preds = %if.then26
  call void @__assert_fail(i8* getelementptr inbounds ([36 x i8], [36 x i8]* @.str.14, i32 0, i32 0), i8* getelementptr inbounds ([77 x i8], [77 x i8]* @.str.1, i32 0, i32 0), i32 1021, i8* getelementptr inbounds ([38 x i8], [38 x i8]* @__PRETTY_FUNCTION__.iter_set_info, i32 0, i32 0)) #8, !dbg !2152
  unreachable, !dbg !2152
                                                  ; No predecessors!
  br label %cond.end33, !dbg !2154

cond.end33:                                       ; preds = %29, %cond.true31
  %30 = load %struct.index_group*, %struct.index_group** %group, align 8, !dbg !2156
  %node34 = getelementptr inbounds %struct.index_group, %struct.index_group* %30, i32 0, i32 0, !dbg !2156
  %parent = getelementptr inbounds %struct.index_tree_node_s, %struct.index_tree_node_s* %node34, i32 0, i32 2, !dbg !2156
  %31 = load %struct.index_tree_node_s*, %struct.index_tree_node_s** %parent, align 8, !dbg !2156
  %right = getelementptr inbounds %struct.index_tree_node_s, %struct.index_tree_node_s* %31, i32 0, i32 4, !dbg !2156
  %32 = load %struct.index_tree_node_s*, %struct.index_tree_node_s** %right, align 8, !dbg !2156
  %33 = load %struct.index_group*, %struct.index_group** %group, align 8, !dbg !2156
  %node35 = getelementptr inbounds %struct.index_group, %struct.index_group* %33, i32 0, i32 0, !dbg !2156
  %cmp36 = icmp eq %struct.index_tree_node_s* %32, %node35, !dbg !2156
  br i1 %cmp36, label %cond.true37, label %cond.false38, !dbg !2156

cond.true37:                                      ; preds = %cond.end33
  br label %cond.end39, !dbg !2157

cond.false38:                                     ; preds = %cond.end33
  call void @__assert_fail(i8* getelementptr inbounds ([42 x i8], [42 x i8]* @.str.15, i32 0, i32 0), i8* getelementptr inbounds ([77 x i8], [77 x i8]* @.str.1, i32 0, i32 0), i32 1022, i8* getelementptr inbounds ([38 x i8], [38 x i8]* @__PRETTY_FUNCTION__.iter_set_info, i32 0, i32 0)) #8, !dbg !2158
  unreachable, !dbg !2158
                                                  ; No predecessors!
  br label %cond.end39, !dbg !2159

cond.end39:                                       ; preds = %34, %cond.true37
  %35 = load %struct.lzma_index_iter*, %struct.lzma_index_iter** %iter.addr, align 8, !dbg !2160
  %internal40 = getelementptr inbounds %struct.lzma_index_iter, %struct.lzma_index_iter* %35, i32 0, i32 2, !dbg !2161
  %arrayidx41 = getelementptr inbounds [6 x %union.anon], [6 x %union.anon]* %internal40, i64 0, i64 4, !dbg !2160
  %s42 = bitcast %union.anon* %arrayidx41 to i64*, !dbg !2162
  store i64 1, i64* %s42, align 8, !dbg !2163
  %36 = load %struct.index_group*, %struct.index_group** %group, align 8, !dbg !2164
  %node43 = getelementptr inbounds %struct.index_group, %struct.index_group* %36, i32 0, i32 0, !dbg !2165
  %parent44 = getelementptr inbounds %struct.index_tree_node_s, %struct.index_tree_node_s* %node43, i32 0, i32 2, !dbg !2166
  %37 = load %struct.index_tree_node_s*, %struct.index_tree_node_s** %parent44, align 8, !dbg !2166
  %38 = bitcast %struct.index_tree_node_s* %37 to i8*, !dbg !2164
  %39 = load %struct.lzma_index_iter*, %struct.lzma_index_iter** %iter.addr, align 8, !dbg !2167
  %internal45 = getelementptr inbounds %struct.lzma_index_iter, %struct.lzma_index_iter* %39, i32 0, i32 2, !dbg !2168
  %arrayidx46 = getelementptr inbounds [6 x %union.anon], [6 x %union.anon]* %internal45, i64 0, i64 2, !dbg !2167
  %p47 = bitcast %union.anon* %arrayidx46 to i8**, !dbg !2169
  store i8* %38, i8** %p47, align 8, !dbg !2170
  br label %if.end, !dbg !2171

if.else48:                                        ; preds = %if.else22
  %40 = load %struct.index_stream*, %struct.index_stream** %stream, align 8, !dbg !2172
  %groups49 = getelementptr inbounds %struct.index_stream, %struct.index_stream* %40, i32 0, i32 3, !dbg !2172
  %root50 = getelementptr inbounds %struct.index_tree, %struct.index_tree* %groups49, i32 0, i32 0, !dbg !2172
  %41 = load %struct.index_tree_node_s*, %struct.index_tree_node_s** %root50, align 8, !dbg !2172
  %42 = load %struct.index_group*, %struct.index_group** %group, align 8, !dbg !2172
  %node51 = getelementptr inbounds %struct.index_group, %struct.index_group* %42, i32 0, i32 0, !dbg !2172
  %cmp52 = icmp eq %struct.index_tree_node_s* %41, %node51, !dbg !2172
  br i1 %cmp52, label %cond.true53, label %cond.false54, !dbg !2172

cond.true53:                                      ; preds = %if.else48
  br label %cond.end55, !dbg !2174

cond.false54:                                     ; preds = %if.else48
  call void @__assert_fail(i8* getelementptr inbounds ([36 x i8], [36 x i8]* @.str.16, i32 0, i32 0), i8* getelementptr inbounds ([77 x i8], [77 x i8]* @.str.1, i32 0, i32 0), i32 1028, i8* getelementptr inbounds ([38 x i8], [38 x i8]* @__PRETTY_FUNCTION__.iter_set_info, i32 0, i32 0)) #8, !dbg !2176
  unreachable, !dbg !2176
                                                  ; No predecessors!
  br label %cond.end55, !dbg !2178

cond.end55:                                       ; preds = %43, %cond.true53
  %44 = load %struct.index_group*, %struct.index_group** %group, align 8, !dbg !2180
  %node56 = getelementptr inbounds %struct.index_group, %struct.index_group* %44, i32 0, i32 0, !dbg !2180
  %parent57 = getelementptr inbounds %struct.index_tree_node_s, %struct.index_tree_node_s* %node56, i32 0, i32 2, !dbg !2180
  %45 = load %struct.index_tree_node_s*, %struct.index_tree_node_s** %parent57, align 8, !dbg !2180
  %cmp58 = icmp eq %struct.index_tree_node_s* %45, null, !dbg !2180
  br i1 %cmp58, label %cond.true59, label %cond.false60, !dbg !2180

cond.true59:                                      ; preds = %cond.end55
  br label %cond.end61, !dbg !2181

cond.false60:                                     ; preds = %cond.end55
  call void @__assert_fail(i8* getelementptr inbounds ([33 x i8], [33 x i8]* @.str.17, i32 0, i32 0), i8* getelementptr inbounds ([77 x i8], [77 x i8]* @.str.1, i32 0, i32 0), i32 1029, i8* getelementptr inbounds ([38 x i8], [38 x i8]* @__PRETTY_FUNCTION__.iter_set_info, i32 0, i32 0)) #8, !dbg !2182
  unreachable, !dbg !2182
                                                  ; No predecessors!
  br label %cond.end61, !dbg !2183

cond.end61:                                       ; preds = %46, %cond.true59
  %47 = load %struct.lzma_index_iter*, %struct.lzma_index_iter** %iter.addr, align 8, !dbg !2184
  %internal62 = getelementptr inbounds %struct.lzma_index_iter, %struct.lzma_index_iter* %47, i32 0, i32 2, !dbg !2185
  %arrayidx63 = getelementptr inbounds [6 x %union.anon], [6 x %union.anon]* %internal62, i64 0, i64 4, !dbg !2184
  %s64 = bitcast %union.anon* %arrayidx63 to i64*, !dbg !2186
  store i64 2, i64* %s64, align 8, !dbg !2187
  %48 = load %struct.lzma_index_iter*, %struct.lzma_index_iter** %iter.addr, align 8, !dbg !2188
  %internal65 = getelementptr inbounds %struct.lzma_index_iter, %struct.lzma_index_iter* %48, i32 0, i32 2, !dbg !2189
  %arrayidx66 = getelementptr inbounds [6 x %union.anon], [6 x %union.anon]* %internal65, i64 0, i64 2, !dbg !2188
  %p67 = bitcast %union.anon* %arrayidx66 to i8**, !dbg !2190
  store i8* null, i8** %p67, align 8, !dbg !2191
  br label %if.end

if.end:                                           ; preds = %cond.end61, %cond.end39
  br label %if.end68

if.end68:                                         ; preds = %if.end, %if.then18
  br label %if.end69

if.end69:                                         ; preds = %if.end68, %cond.end
  %49 = load %struct.index_stream*, %struct.index_stream** %stream, align 8, !dbg !2192
  %number = getelementptr inbounds %struct.index_stream, %struct.index_stream* %49, i32 0, i32 1, !dbg !2193
  %50 = load i32, i32* %number, align 8, !dbg !2193
  %conv = zext i32 %50 to i64, !dbg !2192
  %51 = load %struct.lzma_index_iter*, %struct.lzma_index_iter** %iter.addr, align 8, !dbg !2194
  %stream70 = getelementptr inbounds %struct.lzma_index_iter, %struct.lzma_index_iter* %51, i32 0, i32 0, !dbg !2195
  %number71 = getelementptr inbounds %struct.anon, %struct.anon* %stream70, i32 0, i32 4, !dbg !2196
  store i64 %conv, i64* %number71, align 8, !dbg !2197
  %52 = load %struct.index_stream*, %struct.index_stream** %stream, align 8, !dbg !2198
  %record_count = getelementptr inbounds %struct.index_stream, %struct.index_stream* %52, i32 0, i32 4, !dbg !2199
  %53 = load i64, i64* %record_count, align 8, !dbg !2199
  %54 = load %struct.lzma_index_iter*, %struct.lzma_index_iter** %iter.addr, align 8, !dbg !2200
  %stream72 = getelementptr inbounds %struct.lzma_index_iter, %struct.lzma_index_iter* %54, i32 0, i32 0, !dbg !2201
  %block_count = getelementptr inbounds %struct.anon, %struct.anon* %stream72, i32 0, i32 5, !dbg !2202
  store i64 %53, i64* %block_count, align 8, !dbg !2203
  %55 = load %struct.index_stream*, %struct.index_stream** %stream, align 8, !dbg !2204
  %node73 = getelementptr inbounds %struct.index_stream, %struct.index_stream* %55, i32 0, i32 0, !dbg !2205
  %compressed_base = getelementptr inbounds %struct.index_tree_node_s, %struct.index_tree_node_s* %node73, i32 0, i32 1, !dbg !2206
  %56 = load i64, i64* %compressed_base, align 8, !dbg !2206
  %57 = load %struct.lzma_index_iter*, %struct.lzma_index_iter** %iter.addr, align 8, !dbg !2207
  %stream74 = getelementptr inbounds %struct.lzma_index_iter, %struct.lzma_index_iter* %57, i32 0, i32 0, !dbg !2208
  %compressed_offset = getelementptr inbounds %struct.anon, %struct.anon* %stream74, i32 0, i32 6, !dbg !2209
  store i64 %56, i64* %compressed_offset, align 8, !dbg !2210
  %58 = load %struct.index_stream*, %struct.index_stream** %stream, align 8, !dbg !2211
  %node75 = getelementptr inbounds %struct.index_stream, %struct.index_stream* %58, i32 0, i32 0, !dbg !2212
  %uncompressed_base = getelementptr inbounds %struct.index_tree_node_s, %struct.index_tree_node_s* %node75, i32 0, i32 0, !dbg !2213
  %59 = load i64, i64* %uncompressed_base, align 8, !dbg !2213
  %60 = load %struct.lzma_index_iter*, %struct.lzma_index_iter** %iter.addr, align 8, !dbg !2214
  %stream76 = getelementptr inbounds %struct.lzma_index_iter, %struct.lzma_index_iter* %60, i32 0, i32 0, !dbg !2215
  %uncompressed_offset = getelementptr inbounds %struct.anon, %struct.anon* %stream76, i32 0, i32 7, !dbg !2216
  store i64 %59, i64* %uncompressed_offset, align 8, !dbg !2217
  %61 = load %struct.index_stream*, %struct.index_stream** %stream, align 8, !dbg !2218
  %stream_flags = getelementptr inbounds %struct.index_stream, %struct.index_stream* %61, i32 0, i32 6, !dbg !2219
  %version = getelementptr inbounds %struct.lzma_stream_flags, %struct.lzma_stream_flags* %stream_flags, i32 0, i32 0, !dbg !2220
  %62 = load i32, i32* %version, align 8, !dbg !2220
  %cmp77 = icmp eq i32 %62, -1, !dbg !2221
  br i1 %cmp77, label %cond.true79, label %cond.false80, !dbg !2218

cond.true79:                                      ; preds = %if.end69
  br label %cond.end82, !dbg !2222

cond.false80:                                     ; preds = %if.end69
  %63 = load %struct.index_stream*, %struct.index_stream** %stream, align 8, !dbg !2224
  %stream_flags81 = getelementptr inbounds %struct.index_stream, %struct.index_stream* %63, i32 0, i32 6, !dbg !2225
  br label %cond.end82, !dbg !2226

cond.end82:                                       ; preds = %cond.false80, %cond.true79
  %cond = phi %struct.lzma_stream_flags* [ null, %cond.true79 ], [ %stream_flags81, %cond.false80 ], !dbg !2228
  %64 = load %struct.lzma_index_iter*, %struct.lzma_index_iter** %iter.addr, align 8, !dbg !2230
  %stream83 = getelementptr inbounds %struct.lzma_index_iter, %struct.lzma_index_iter* %64, i32 0, i32 0, !dbg !2231
  %flags = getelementptr inbounds %struct.anon, %struct.anon* %stream83, i32 0, i32 0, !dbg !2232
  store %struct.lzma_stream_flags* %cond, %struct.lzma_stream_flags** %flags, align 8, !dbg !2233
  %65 = load %struct.index_stream*, %struct.index_stream** %stream, align 8, !dbg !2234
  %stream_padding = getelementptr inbounds %struct.index_stream, %struct.index_stream* %65, i32 0, i32 7, !dbg !2235
  %66 = load i64, i64* %stream_padding, align 8, !dbg !2235
  %67 = load %struct.lzma_index_iter*, %struct.lzma_index_iter** %iter.addr, align 8, !dbg !2236
  %stream84 = getelementptr inbounds %struct.lzma_index_iter, %struct.lzma_index_iter* %67, i32 0, i32 0, !dbg !2237
  %padding = getelementptr inbounds %struct.anon, %struct.anon* %stream84, i32 0, i32 10, !dbg !2238
  store i64 %66, i64* %padding, align 8, !dbg !2239
  %68 = load %struct.index_stream*, %struct.index_stream** %stream, align 8, !dbg !2240
  %groups85 = getelementptr inbounds %struct.index_stream, %struct.index_stream* %68, i32 0, i32 3, !dbg !2242
  %rightmost86 = getelementptr inbounds %struct.index_tree, %struct.index_tree* %groups85, i32 0, i32 2, !dbg !2243
  %69 = load %struct.index_tree_node_s*, %struct.index_tree_node_s** %rightmost86, align 8, !dbg !2243
  %cmp87 = icmp eq %struct.index_tree_node_s* %69, null, !dbg !2244
  br i1 %cmp87, label %if.then89, label %if.else92, !dbg !2245

if.then89:                                        ; preds = %cond.end82
  %call = call i64 @index_size(i64 0, i64 0), !dbg !2246
  %add = add i64 %call, 24, !dbg !2248
  %70 = load %struct.lzma_index_iter*, %struct.lzma_index_iter** %iter.addr, align 8, !dbg !2249
  %stream90 = getelementptr inbounds %struct.lzma_index_iter, %struct.lzma_index_iter* %70, i32 0, i32 0, !dbg !2250
  %compressed_size = getelementptr inbounds %struct.anon, %struct.anon* %stream90, i32 0, i32 8, !dbg !2251
  store i64 %add, i64* %compressed_size, align 8, !dbg !2252
  %71 = load %struct.lzma_index_iter*, %struct.lzma_index_iter** %iter.addr, align 8, !dbg !2253
  %stream91 = getelementptr inbounds %struct.lzma_index_iter, %struct.lzma_index_iter* %71, i32 0, i32 0, !dbg !2254
  %uncompressed_size = getelementptr inbounds %struct.anon, %struct.anon* %stream91, i32 0, i32 9, !dbg !2255
  store i64 0, i64* %uncompressed_size, align 8, !dbg !2256
  br label %if.end108, !dbg !2257

if.else92:                                        ; preds = %cond.end82
  call void @llvm.dbg.declare(metadata %struct.index_group** %g, metadata !2258, metadata !341), !dbg !2260
  %72 = load %struct.index_stream*, %struct.index_stream** %stream, align 8, !dbg !2261
  %groups93 = getelementptr inbounds %struct.index_stream, %struct.index_stream* %72, i32 0, i32 3, !dbg !2262
  %rightmost94 = getelementptr inbounds %struct.index_tree, %struct.index_tree* %groups93, i32 0, i32 2, !dbg !2263
  %73 = load %struct.index_tree_node_s*, %struct.index_tree_node_s** %rightmost94, align 8, !dbg !2263
  %74 = bitcast %struct.index_tree_node_s* %73 to %struct.index_group*, !dbg !2264
  store %struct.index_group* %74, %struct.index_group** %g, align 8, !dbg !2260
  %75 = load %struct.index_stream*, %struct.index_stream** %stream, align 8, !dbg !2265
  %record_count95 = getelementptr inbounds %struct.index_stream, %struct.index_stream* %75, i32 0, i32 4, !dbg !2266
  %76 = load i64, i64* %record_count95, align 8, !dbg !2266
  %77 = load %struct.index_stream*, %struct.index_stream** %stream, align 8, !dbg !2267
  %index_list_size = getelementptr inbounds %struct.index_stream, %struct.index_stream* %77, i32 0, i32 5, !dbg !2268
  %78 = load i64, i64* %index_list_size, align 8, !dbg !2268
  %call96 = call i64 @index_size(i64 %76, i64 %78), !dbg !2269
  %add97 = add i64 24, %call96, !dbg !2270
  %79 = load %struct.index_group*, %struct.index_group** %g, align 8, !dbg !2271
  %last = getelementptr inbounds %struct.index_group, %struct.index_group* %79, i32 0, i32 3, !dbg !2272
  %80 = load i64, i64* %last, align 8, !dbg !2272
  %81 = load %struct.index_group*, %struct.index_group** %g, align 8, !dbg !2273
  %records = getelementptr inbounds %struct.index_group, %struct.index_group* %81, i32 0, i32 4, !dbg !2274
  %arrayidx98 = getelementptr inbounds [0 x %struct.index_record], [0 x %struct.index_record]* %records, i64 0, i64 %80, !dbg !2273
  %unpadded_sum = getelementptr inbounds %struct.index_record, %struct.index_record* %arrayidx98, i32 0, i32 1, !dbg !2275
  %82 = load i64, i64* %unpadded_sum, align 8, !dbg !2275
  %call99 = call i64 @vli_ceil4(i64 %82), !dbg !2276
  %add100 = add i64 %add97, %call99, !dbg !2277
  %83 = load %struct.lzma_index_iter*, %struct.lzma_index_iter** %iter.addr, align 8, !dbg !2278
  %stream101 = getelementptr inbounds %struct.lzma_index_iter, %struct.lzma_index_iter* %83, i32 0, i32 0, !dbg !2279
  %compressed_size102 = getelementptr inbounds %struct.anon, %struct.anon* %stream101, i32 0, i32 8, !dbg !2280
  store i64 %add100, i64* %compressed_size102, align 8, !dbg !2281
  %84 = load %struct.index_group*, %struct.index_group** %g, align 8, !dbg !2282
  %last103 = getelementptr inbounds %struct.index_group, %struct.index_group* %84, i32 0, i32 3, !dbg !2283
  %85 = load i64, i64* %last103, align 8, !dbg !2283
  %86 = load %struct.index_group*, %struct.index_group** %g, align 8, !dbg !2284
  %records104 = getelementptr inbounds %struct.index_group, %struct.index_group* %86, i32 0, i32 4, !dbg !2285
  %arrayidx105 = getelementptr inbounds [0 x %struct.index_record], [0 x %struct.index_record]* %records104, i64 0, i64 %85, !dbg !2284
  %uncompressed_sum = getelementptr inbounds %struct.index_record, %struct.index_record* %arrayidx105, i32 0, i32 0, !dbg !2286
  %87 = load i64, i64* %uncompressed_sum, align 8, !dbg !2286
  %88 = load %struct.lzma_index_iter*, %struct.lzma_index_iter** %iter.addr, align 8, !dbg !2287
  %stream106 = getelementptr inbounds %struct.lzma_index_iter, %struct.lzma_index_iter* %88, i32 0, i32 0, !dbg !2288
  %uncompressed_size107 = getelementptr inbounds %struct.anon, %struct.anon* %stream106, i32 0, i32 9, !dbg !2289
  store i64 %87, i64* %uncompressed_size107, align 8, !dbg !2290
  br label %if.end108

if.end108:                                        ; preds = %if.else92, %if.then89
  %89 = load %struct.index_group*, %struct.index_group** %group, align 8, !dbg !2291
  %cmp109 = icmp ne %struct.index_group* %89, null, !dbg !2293
  br i1 %cmp109, label %if.then111, label %if.end177, !dbg !2294

if.then111:                                       ; preds = %if.end108
  %90 = load %struct.index_group*, %struct.index_group** %group, align 8, !dbg !2295
  %number_base = getelementptr inbounds %struct.index_group, %struct.index_group* %90, i32 0, i32 1, !dbg !2297
  %91 = load i64, i64* %number_base, align 8, !dbg !2297
  %92 = load i64, i64* %record, align 8, !dbg !2298
  %add112 = add i64 %91, %92, !dbg !2299
  %93 = load %struct.lzma_index_iter*, %struct.lzma_index_iter** %iter.addr, align 8, !dbg !2300
  %block = getelementptr inbounds %struct.lzma_index_iter, %struct.lzma_index_iter* %93, i32 0, i32 1, !dbg !2301
  %number_in_stream = getelementptr inbounds %struct.anon.0, %struct.anon.0* %block, i32 0, i32 3, !dbg !2302
  store i64 %add112, i64* %number_in_stream, align 8, !dbg !2303
  %94 = load %struct.lzma_index_iter*, %struct.lzma_index_iter** %iter.addr, align 8, !dbg !2304
  %block113 = getelementptr inbounds %struct.lzma_index_iter, %struct.lzma_index_iter* %94, i32 0, i32 1, !dbg !2305
  %number_in_stream114 = getelementptr inbounds %struct.anon.0, %struct.anon.0* %block113, i32 0, i32 3, !dbg !2306
  %95 = load i64, i64* %number_in_stream114, align 8, !dbg !2306
  %96 = load %struct.index_stream*, %struct.index_stream** %stream, align 8, !dbg !2307
  %block_number_base = getelementptr inbounds %struct.index_stream, %struct.index_stream* %96, i32 0, i32 2, !dbg !2308
  %97 = load i64, i64* %block_number_base, align 8, !dbg !2308
  %add115 = add i64 %95, %97, !dbg !2309
  %98 = load %struct.lzma_index_iter*, %struct.lzma_index_iter** %iter.addr, align 8, !dbg !2310
  %block116 = getelementptr inbounds %struct.lzma_index_iter, %struct.lzma_index_iter* %98, i32 0, i32 1, !dbg !2311
  %number_in_file = getelementptr inbounds %struct.anon.0, %struct.anon.0* %block116, i32 0, i32 0, !dbg !2312
  store i64 %add115, i64* %number_in_file, align 8, !dbg !2313
  %99 = load i64, i64* %record, align 8, !dbg !2314
  %cmp117 = icmp eq i64 %99, 0, !dbg !2315
  br i1 %cmp117, label %cond.true119, label %cond.false122, !dbg !2314

cond.true119:                                     ; preds = %if.then111
  %100 = load %struct.index_group*, %struct.index_group** %group, align 8, !dbg !2316
  %node120 = getelementptr inbounds %struct.index_group, %struct.index_group* %100, i32 0, i32 0, !dbg !2318
  %compressed_base121 = getelementptr inbounds %struct.index_tree_node_s, %struct.index_tree_node_s* %node120, i32 0, i32 1, !dbg !2319
  %101 = load i64, i64* %compressed_base121, align 8, !dbg !2319
  br label %cond.end127, !dbg !2320

cond.false122:                                    ; preds = %if.then111
  %102 = load i64, i64* %record, align 8, !dbg !2321
  %sub = sub i64 %102, 1, !dbg !2322
  %103 = load %struct.index_group*, %struct.index_group** %group, align 8, !dbg !2323
  %records123 = getelementptr inbounds %struct.index_group, %struct.index_group* %103, i32 0, i32 4, !dbg !2324
  %arrayidx124 = getelementptr inbounds [0 x %struct.index_record], [0 x %struct.index_record]* %records123, i64 0, i64 %sub, !dbg !2323
  %unpadded_sum125 = getelementptr inbounds %struct.index_record, %struct.index_record* %arrayidx124, i32 0, i32 1, !dbg !2325
  %104 = load i64, i64* %unpadded_sum125, align 8, !dbg !2325
  %call126 = call i64 @vli_ceil4(i64 %104), !dbg !2326
  br label %cond.end127, !dbg !2327

cond.end127:                                      ; preds = %cond.false122, %cond.true119
  %cond128 = phi i64 [ %101, %cond.true119 ], [ %call126, %cond.false122 ], !dbg !2329
  %105 = load %struct.lzma_index_iter*, %struct.lzma_index_iter** %iter.addr, align 8, !dbg !2331
  %block129 = getelementptr inbounds %struct.lzma_index_iter, %struct.lzma_index_iter* %105, i32 0, i32 1, !dbg !2332
  %compressed_stream_offset = getelementptr inbounds %struct.anon.0, %struct.anon.0* %block129, i32 0, i32 4, !dbg !2333
  store i64 %cond128, i64* %compressed_stream_offset, align 8, !dbg !2334
  %106 = load i64, i64* %record, align 8, !dbg !2335
  %cmp130 = icmp eq i64 %106, 0, !dbg !2336
  br i1 %cmp130, label %cond.true132, label %cond.false135, !dbg !2335

cond.true132:                                     ; preds = %cond.end127
  %107 = load %struct.index_group*, %struct.index_group** %group, align 8, !dbg !2337
  %node133 = getelementptr inbounds %struct.index_group, %struct.index_group* %107, i32 0, i32 0, !dbg !2338
  %uncompressed_base134 = getelementptr inbounds %struct.index_tree_node_s, %struct.index_tree_node_s* %node133, i32 0, i32 0, !dbg !2339
  %108 = load i64, i64* %uncompressed_base134, align 8, !dbg !2339
  br label %cond.end140, !dbg !2340

cond.false135:                                    ; preds = %cond.end127
  %109 = load i64, i64* %record, align 8, !dbg !2341
  %sub136 = sub i64 %109, 1, !dbg !2342
  %110 = load %struct.index_group*, %struct.index_group** %group, align 8, !dbg !2343
  %records137 = getelementptr inbounds %struct.index_group, %struct.index_group* %110, i32 0, i32 4, !dbg !2344
  %arrayidx138 = getelementptr inbounds [0 x %struct.index_record], [0 x %struct.index_record]* %records137, i64 0, i64 %sub136, !dbg !2343
  %uncompressed_sum139 = getelementptr inbounds %struct.index_record, %struct.index_record* %arrayidx138, i32 0, i32 0, !dbg !2345
  %111 = load i64, i64* %uncompressed_sum139, align 8, !dbg !2345
  br label %cond.end140, !dbg !2346

cond.end140:                                      ; preds = %cond.false135, %cond.true132
  %cond141 = phi i64 [ %108, %cond.true132 ], [ %111, %cond.false135 ], !dbg !2347
  %112 = load %struct.lzma_index_iter*, %struct.lzma_index_iter** %iter.addr, align 8, !dbg !2348
  %block142 = getelementptr inbounds %struct.lzma_index_iter, %struct.lzma_index_iter* %112, i32 0, i32 1, !dbg !2349
  %uncompressed_stream_offset = getelementptr inbounds %struct.anon.0, %struct.anon.0* %block142, i32 0, i32 5, !dbg !2350
  store i64 %cond141, i64* %uncompressed_stream_offset, align 8, !dbg !2351
  %113 = load i64, i64* %record, align 8, !dbg !2352
  %114 = load %struct.index_group*, %struct.index_group** %group, align 8, !dbg !2353
  %records143 = getelementptr inbounds %struct.index_group, %struct.index_group* %114, i32 0, i32 4, !dbg !2354
  %arrayidx144 = getelementptr inbounds [0 x %struct.index_record], [0 x %struct.index_record]* %records143, i64 0, i64 %113, !dbg !2353
  %uncompressed_sum145 = getelementptr inbounds %struct.index_record, %struct.index_record* %arrayidx144, i32 0, i32 0, !dbg !2355
  %115 = load i64, i64* %uncompressed_sum145, align 8, !dbg !2355
  %116 = load %struct.lzma_index_iter*, %struct.lzma_index_iter** %iter.addr, align 8, !dbg !2356
  %block146 = getelementptr inbounds %struct.lzma_index_iter, %struct.lzma_index_iter* %116, i32 0, i32 1, !dbg !2357
  %uncompressed_stream_offset147 = getelementptr inbounds %struct.anon.0, %struct.anon.0* %block146, i32 0, i32 5, !dbg !2358
  %117 = load i64, i64* %uncompressed_stream_offset147, align 8, !dbg !2358
  %sub148 = sub i64 %115, %117, !dbg !2359
  %118 = load %struct.lzma_index_iter*, %struct.lzma_index_iter** %iter.addr, align 8, !dbg !2360
  %block149 = getelementptr inbounds %struct.lzma_index_iter, %struct.lzma_index_iter* %118, i32 0, i32 1, !dbg !2361
  %uncompressed_size150 = getelementptr inbounds %struct.anon.0, %struct.anon.0* %block149, i32 0, i32 6, !dbg !2362
  store i64 %sub148, i64* %uncompressed_size150, align 8, !dbg !2363
  %119 = load i64, i64* %record, align 8, !dbg !2364
  %120 = load %struct.index_group*, %struct.index_group** %group, align 8, !dbg !2365
  %records151 = getelementptr inbounds %struct.index_group, %struct.index_group* %120, i32 0, i32 4, !dbg !2366
  %arrayidx152 = getelementptr inbounds [0 x %struct.index_record], [0 x %struct.index_record]* %records151, i64 0, i64 %119, !dbg !2365
  %unpadded_sum153 = getelementptr inbounds %struct.index_record, %struct.index_record* %arrayidx152, i32 0, i32 1, !dbg !2367
  %121 = load i64, i64* %unpadded_sum153, align 8, !dbg !2367
  %122 = load %struct.lzma_index_iter*, %struct.lzma_index_iter** %iter.addr, align 8, !dbg !2368
  %block154 = getelementptr inbounds %struct.lzma_index_iter, %struct.lzma_index_iter* %122, i32 0, i32 1, !dbg !2369
  %compressed_stream_offset155 = getelementptr inbounds %struct.anon.0, %struct.anon.0* %block154, i32 0, i32 4, !dbg !2370
  %123 = load i64, i64* %compressed_stream_offset155, align 8, !dbg !2370
  %sub156 = sub i64 %121, %123, !dbg !2371
  %124 = load %struct.lzma_index_iter*, %struct.lzma_index_iter** %iter.addr, align 8, !dbg !2372
  %block157 = getelementptr inbounds %struct.lzma_index_iter, %struct.lzma_index_iter* %124, i32 0, i32 1, !dbg !2373
  %unpadded_size = getelementptr inbounds %struct.anon.0, %struct.anon.0* %block157, i32 0, i32 7, !dbg !2374
  store i64 %sub156, i64* %unpadded_size, align 8, !dbg !2375
  %125 = load %struct.lzma_index_iter*, %struct.lzma_index_iter** %iter.addr, align 8, !dbg !2376
  %block158 = getelementptr inbounds %struct.lzma_index_iter, %struct.lzma_index_iter* %125, i32 0, i32 1, !dbg !2377
  %unpadded_size159 = getelementptr inbounds %struct.anon.0, %struct.anon.0* %block158, i32 0, i32 7, !dbg !2378
  %126 = load i64, i64* %unpadded_size159, align 8, !dbg !2378
  %call160 = call i64 @vli_ceil4(i64 %126), !dbg !2379
  %127 = load %struct.lzma_index_iter*, %struct.lzma_index_iter** %iter.addr, align 8, !dbg !2380
  %block161 = getelementptr inbounds %struct.lzma_index_iter, %struct.lzma_index_iter* %127, i32 0, i32 1, !dbg !2381
  %total_size = getelementptr inbounds %struct.anon.0, %struct.anon.0* %block161, i32 0, i32 8, !dbg !2382
  store i64 %call160, i64* %total_size, align 8, !dbg !2383
  %128 = load %struct.lzma_index_iter*, %struct.lzma_index_iter** %iter.addr, align 8, !dbg !2384
  %block162 = getelementptr inbounds %struct.lzma_index_iter, %struct.lzma_index_iter* %128, i32 0, i32 1, !dbg !2385
  %compressed_stream_offset163 = getelementptr inbounds %struct.anon.0, %struct.anon.0* %block162, i32 0, i32 4, !dbg !2386
  %129 = load i64, i64* %compressed_stream_offset163, align 8, !dbg !2387
  %add164 = add i64 %129, 12, !dbg !2387
  store i64 %add164, i64* %compressed_stream_offset163, align 8, !dbg !2387
  %130 = load %struct.lzma_index_iter*, %struct.lzma_index_iter** %iter.addr, align 8, !dbg !2388
  %block165 = getelementptr inbounds %struct.lzma_index_iter, %struct.lzma_index_iter* %130, i32 0, i32 1, !dbg !2389
  %compressed_stream_offset166 = getelementptr inbounds %struct.anon.0, %struct.anon.0* %block165, i32 0, i32 4, !dbg !2390
  %131 = load i64, i64* %compressed_stream_offset166, align 8, !dbg !2390
  %132 = load %struct.lzma_index_iter*, %struct.lzma_index_iter** %iter.addr, align 8, !dbg !2391
  %stream167 = getelementptr inbounds %struct.lzma_index_iter, %struct.lzma_index_iter* %132, i32 0, i32 0, !dbg !2392
  %compressed_offset168 = getelementptr inbounds %struct.anon, %struct.anon* %stream167, i32 0, i32 6, !dbg !2393
  %133 = load i64, i64* %compressed_offset168, align 8, !dbg !2393
  %add169 = add i64 %131, %133, !dbg !2394
  %134 = load %struct.lzma_index_iter*, %struct.lzma_index_iter** %iter.addr, align 8, !dbg !2395
  %block170 = getelementptr inbounds %struct.lzma_index_iter, %struct.lzma_index_iter* %134, i32 0, i32 1, !dbg !2396
  %compressed_file_offset = getelementptr inbounds %struct.anon.0, %struct.anon.0* %block170, i32 0, i32 1, !dbg !2397
  store i64 %add169, i64* %compressed_file_offset, align 8, !dbg !2398
  %135 = load %struct.lzma_index_iter*, %struct.lzma_index_iter** %iter.addr, align 8, !dbg !2399
  %block171 = getelementptr inbounds %struct.lzma_index_iter, %struct.lzma_index_iter* %135, i32 0, i32 1, !dbg !2400
  %uncompressed_stream_offset172 = getelementptr inbounds %struct.anon.0, %struct.anon.0* %block171, i32 0, i32 5, !dbg !2401
  %136 = load i64, i64* %uncompressed_stream_offset172, align 8, !dbg !2401
  %137 = load %struct.lzma_index_iter*, %struct.lzma_index_iter** %iter.addr, align 8, !dbg !2402
  %stream173 = getelementptr inbounds %struct.lzma_index_iter, %struct.lzma_index_iter* %137, i32 0, i32 0, !dbg !2403
  %uncompressed_offset174 = getelementptr inbounds %struct.anon, %struct.anon* %stream173, i32 0, i32 7, !dbg !2404
  %138 = load i64, i64* %uncompressed_offset174, align 8, !dbg !2404
  %add175 = add i64 %136, %138, !dbg !2405
  %139 = load %struct.lzma_index_iter*, %struct.lzma_index_iter** %iter.addr, align 8, !dbg !2406
  %block176 = getelementptr inbounds %struct.lzma_index_iter, %struct.lzma_index_iter* %139, i32 0, i32 1, !dbg !2407
  %uncompressed_file_offset = getelementptr inbounds %struct.anon.0, %struct.anon.0* %block176, i32 0, i32 2, !dbg !2408
  store i64 %add175, i64* %uncompressed_file_offset, align 8, !dbg !2409
  br label %if.end177, !dbg !2410

if.end177:                                        ; preds = %cond.end140, %if.end108
  ret void, !dbg !2411
}

; Function Attrs: nounwind uwtable
define zeroext i8 @lzma_index_iter_locate(%struct.lzma_index_iter* %iter, i64 %target) #0 !dbg !270 {
entry:
  %retval = alloca i8, align 1
  %iter.addr = alloca %struct.lzma_index_iter*, align 8
  %target.addr = alloca i64, align 8
  %stream = alloca %struct.index_stream*, align 8
  %group = alloca %struct.index_group*, align 8
  %left = alloca i64, align 8
  %right = alloca i64, align 8
  %i = alloca %struct.lzma_index_s*, align 8
  %pos = alloca i64, align 8
  store %struct.lzma_index_iter* %iter, %struct.lzma_index_iter** %iter.addr, align 8
  call void @llvm.dbg.declare(metadata %struct.lzma_index_iter** %iter.addr, metadata !2412, metadata !341), !dbg !2413
  store i64 %target, i64* %target.addr, align 8
  call void @llvm.dbg.declare(metadata i64* %target.addr, metadata !2414, metadata !341), !dbg !2415
  call void @llvm.dbg.declare(metadata %struct.index_stream** %stream, metadata !2416, metadata !341), !dbg !2417
  call void @llvm.dbg.declare(metadata %struct.index_group** %group, metadata !2418, metadata !341), !dbg !2419
  call void @llvm.dbg.declare(metadata i64* %left, metadata !2420, metadata !341), !dbg !2421
  call void @llvm.dbg.declare(metadata i64* %right, metadata !2422, metadata !341), !dbg !2423
  call void @llvm.dbg.declare(metadata %struct.lzma_index_s** %i, metadata !2424, metadata !341), !dbg !2425
  %0 = load %struct.lzma_index_iter*, %struct.lzma_index_iter** %iter.addr, align 8, !dbg !2426
  %internal = getelementptr inbounds %struct.lzma_index_iter, %struct.lzma_index_iter* %0, i32 0, i32 2, !dbg !2427
  %arrayidx = getelementptr inbounds [6 x %union.anon], [6 x %union.anon]* %internal, i64 0, i64 0, !dbg !2426
  %p = bitcast %union.anon* %arrayidx to i8**, !dbg !2428
  %1 = load i8*, i8** %p, align 8, !dbg !2428
  %2 = bitcast i8* %1 to %struct.lzma_index_s*, !dbg !2426
  store %struct.lzma_index_s* %2, %struct.lzma_index_s** %i, align 8, !dbg !2425
  %3 = load %struct.lzma_index_s*, %struct.lzma_index_s** %i, align 8, !dbg !2429
  %uncompressed_size = getelementptr inbounds %struct.lzma_index_s, %struct.lzma_index_s* %3, i32 0, i32 1, !dbg !2431
  %4 = load i64, i64* %uncompressed_size, align 8, !dbg !2431
  %5 = load i64, i64* %target.addr, align 8, !dbg !2432
  %cmp = icmp ule i64 %4, %5, !dbg !2433
  br i1 %cmp, label %if.then, label %if.end, !dbg !2434

if.then:                                          ; preds = %entry
  store i8 1, i8* %retval, align 1, !dbg !2435
  br label %return, !dbg !2435

if.end:                                           ; preds = %entry
  %6 = load %struct.lzma_index_s*, %struct.lzma_index_s** %i, align 8, !dbg !2436
  %streams = getelementptr inbounds %struct.lzma_index_s, %struct.lzma_index_s* %6, i32 0, i32 0, !dbg !2437
  %7 = load i64, i64* %target.addr, align 8, !dbg !2438
  %call = call i8* @index_tree_locate(%struct.index_tree* %streams, i64 %7), !dbg !2439
  %8 = bitcast i8* %call to %struct.index_stream*, !dbg !2439
  store %struct.index_stream* %8, %struct.index_stream** %stream, align 8, !dbg !2440
  %9 = load %struct.index_stream*, %struct.index_stream** %stream, align 8, !dbg !2441
  %cmp1 = icmp ne %struct.index_stream* %9, null, !dbg !2441
  br i1 %cmp1, label %cond.true, label %cond.false, !dbg !2441

cond.true:                                        ; preds = %if.end
  br label %cond.end, !dbg !2442

cond.false:                                       ; preds = %if.end
  call void @__assert_fail(i8* getelementptr inbounds ([21 x i8], [21 x i8]* @.str.5, i32 0, i32 0), i8* getelementptr inbounds ([77 x i8], [77 x i8]* @.str.1, i32 0, i32 0), i32 1246, i8* getelementptr inbounds ([62 x i8], [62 x i8]* @__PRETTY_FUNCTION__.lzma_index_iter_locate, i32 0, i32 0)) #8, !dbg !2444
  unreachable, !dbg !2444
                                                  ; No predecessors!
  br label %cond.end, !dbg !2446

cond.end:                                         ; preds = %10, %cond.true
  %11 = load %struct.index_stream*, %struct.index_stream** %stream, align 8, !dbg !2448
  %node = getelementptr inbounds %struct.index_stream, %struct.index_stream* %11, i32 0, i32 0, !dbg !2449
  %uncompressed_base = getelementptr inbounds %struct.index_tree_node_s, %struct.index_tree_node_s* %node, i32 0, i32 0, !dbg !2450
  %12 = load i64, i64* %uncompressed_base, align 8, !dbg !2450
  %13 = load i64, i64* %target.addr, align 8, !dbg !2451
  %sub = sub i64 %13, %12, !dbg !2451
  store i64 %sub, i64* %target.addr, align 8, !dbg !2451
  %14 = load %struct.index_stream*, %struct.index_stream** %stream, align 8, !dbg !2452
  %groups = getelementptr inbounds %struct.index_stream, %struct.index_stream* %14, i32 0, i32 3, !dbg !2453
  %15 = load i64, i64* %target.addr, align 8, !dbg !2454
  %call2 = call i8* @index_tree_locate(%struct.index_tree* %groups, i64 %15), !dbg !2455
  %16 = bitcast i8* %call2 to %struct.index_group*, !dbg !2455
  store %struct.index_group* %16, %struct.index_group** %group, align 8, !dbg !2456
  %17 = load %struct.index_group*, %struct.index_group** %group, align 8, !dbg !2457
  %cmp3 = icmp ne %struct.index_group* %17, null, !dbg !2457
  br i1 %cmp3, label %cond.true4, label %cond.false5, !dbg !2457

cond.true4:                                       ; preds = %cond.end
  br label %cond.end6, !dbg !2458

cond.false5:                                      ; preds = %cond.end
  call void @__assert_fail(i8* getelementptr inbounds ([20 x i8], [20 x i8]* @.str.6, i32 0, i32 0), i8* getelementptr inbounds ([77 x i8], [77 x i8]* @.str.1, i32 0, i32 0), i32 1251, i8* getelementptr inbounds ([62 x i8], [62 x i8]* @__PRETTY_FUNCTION__.lzma_index_iter_locate, i32 0, i32 0)) #8, !dbg !2459
  unreachable, !dbg !2459
                                                  ; No predecessors!
  br label %cond.end6, !dbg !2460

cond.end6:                                        ; preds = %18, %cond.true4
  store i64 0, i64* %left, align 8, !dbg !2461
  %19 = load %struct.index_group*, %struct.index_group** %group, align 8, !dbg !2462
  %last = getelementptr inbounds %struct.index_group, %struct.index_group* %19, i32 0, i32 3, !dbg !2463
  %20 = load i64, i64* %last, align 8, !dbg !2463
  store i64 %20, i64* %right, align 8, !dbg !2464
  br label %while.cond, !dbg !2465

while.cond:                                       ; preds = %if.end13, %cond.end6
  %21 = load i64, i64* %left, align 8, !dbg !2466
  %22 = load i64, i64* %right, align 8, !dbg !2467
  %cmp7 = icmp ult i64 %21, %22, !dbg !2468
  br i1 %cmp7, label %while.body, label %while.end, !dbg !2469

while.body:                                       ; preds = %while.cond
  call void @llvm.dbg.declare(metadata i64* %pos, metadata !2470, metadata !341), !dbg !2472
  %23 = load i64, i64* %left, align 8, !dbg !2473
  %24 = load i64, i64* %right, align 8, !dbg !2474
  %25 = load i64, i64* %left, align 8, !dbg !2475
  %sub8 = sub i64 %24, %25, !dbg !2476
  %div = udiv i64 %sub8, 2, !dbg !2477
  %add = add i64 %23, %div, !dbg !2478
  store i64 %add, i64* %pos, align 8, !dbg !2472
  %26 = load i64, i64* %pos, align 8, !dbg !2479
  %27 = load %struct.index_group*, %struct.index_group** %group, align 8, !dbg !2481
  %records = getelementptr inbounds %struct.index_group, %struct.index_group* %27, i32 0, i32 4, !dbg !2482
  %arrayidx9 = getelementptr inbounds [0 x %struct.index_record], [0 x %struct.index_record]* %records, i64 0, i64 %26, !dbg !2481
  %uncompressed_sum = getelementptr inbounds %struct.index_record, %struct.index_record* %arrayidx9, i32 0, i32 0, !dbg !2483
  %28 = load i64, i64* %uncompressed_sum, align 8, !dbg !2483
  %29 = load i64, i64* %target.addr, align 8, !dbg !2484
  %cmp10 = icmp ule i64 %28, %29, !dbg !2485
  br i1 %cmp10, label %if.then11, label %if.else, !dbg !2486

if.then11:                                        ; preds = %while.body
  %30 = load i64, i64* %pos, align 8, !dbg !2487
  %add12 = add i64 %30, 1, !dbg !2488
  store i64 %add12, i64* %left, align 8, !dbg !2489
  br label %if.end13, !dbg !2490

if.else:                                          ; preds = %while.body
  %31 = load i64, i64* %pos, align 8, !dbg !2491
  store i64 %31, i64* %right, align 8, !dbg !2492
  br label %if.end13

if.end13:                                         ; preds = %if.else, %if.then11
  br label %while.cond, !dbg !2493

while.end:                                        ; preds = %while.cond
  %32 = load %struct.index_stream*, %struct.index_stream** %stream, align 8, !dbg !2494
  %33 = bitcast %struct.index_stream* %32 to i8*, !dbg !2494
  %34 = load %struct.lzma_index_iter*, %struct.lzma_index_iter** %iter.addr, align 8, !dbg !2495
  %internal14 = getelementptr inbounds %struct.lzma_index_iter, %struct.lzma_index_iter* %34, i32 0, i32 2, !dbg !2496
  %arrayidx15 = getelementptr inbounds [6 x %union.anon], [6 x %union.anon]* %internal14, i64 0, i64 1, !dbg !2495
  %p16 = bitcast %union.anon* %arrayidx15 to i8**, !dbg !2497
  store i8* %33, i8** %p16, align 8, !dbg !2498
  %35 = load %struct.index_group*, %struct.index_group** %group, align 8, !dbg !2499
  %36 = bitcast %struct.index_group* %35 to i8*, !dbg !2499
  %37 = load %struct.lzma_index_iter*, %struct.lzma_index_iter** %iter.addr, align 8, !dbg !2500
  %internal17 = getelementptr inbounds %struct.lzma_index_iter, %struct.lzma_index_iter* %37, i32 0, i32 2, !dbg !2501
  %arrayidx18 = getelementptr inbounds [6 x %union.anon], [6 x %union.anon]* %internal17, i64 0, i64 2, !dbg !2500
  %p19 = bitcast %union.anon* %arrayidx18 to i8**, !dbg !2502
  store i8* %36, i8** %p19, align 8, !dbg !2503
  %38 = load i64, i64* %left, align 8, !dbg !2504
  %39 = load %struct.lzma_index_iter*, %struct.lzma_index_iter** %iter.addr, align 8, !dbg !2505
  %internal20 = getelementptr inbounds %struct.lzma_index_iter, %struct.lzma_index_iter* %39, i32 0, i32 2, !dbg !2506
  %arrayidx21 = getelementptr inbounds [6 x %union.anon], [6 x %union.anon]* %internal20, i64 0, i64 3, !dbg !2505
  %s = bitcast %union.anon* %arrayidx21 to i64*, !dbg !2507
  store i64 %38, i64* %s, align 8, !dbg !2508
  %40 = load %struct.lzma_index_iter*, %struct.lzma_index_iter** %iter.addr, align 8, !dbg !2509
  call void @iter_set_info(%struct.lzma_index_iter* %40), !dbg !2510
  store i8 0, i8* %retval, align 1, !dbg !2511
  br label %return, !dbg !2511

return:                                           ; preds = %while.end, %if.then
  %41 = load i8, i8* %retval, align 1, !dbg !2512
  ret i8 %41, !dbg !2512
}

; Function Attrs: nounwind uwtable
define internal i8* @index_tree_locate(%struct.index_tree* %tree, i64 %target) #0 !dbg !332 {
entry:
  %tree.addr = alloca %struct.index_tree*, align 8
  %target.addr = alloca i64, align 8
  %result = alloca %struct.index_tree_node_s*, align 8
  %node = alloca %struct.index_tree_node_s*, align 8
  store %struct.index_tree* %tree, %struct.index_tree** %tree.addr, align 8
  call void @llvm.dbg.declare(metadata %struct.index_tree** %tree.addr, metadata !2513, metadata !341), !dbg !2514
  store i64 %target, i64* %target.addr, align 8
  call void @llvm.dbg.declare(metadata i64* %target.addr, metadata !2515, metadata !341), !dbg !2516
  call void @llvm.dbg.declare(metadata %struct.index_tree_node_s** %result, metadata !2517, metadata !341), !dbg !2518
  store %struct.index_tree_node_s* null, %struct.index_tree_node_s** %result, align 8, !dbg !2518
  call void @llvm.dbg.declare(metadata %struct.index_tree_node_s** %node, metadata !2519, metadata !341), !dbg !2520
  %0 = load %struct.index_tree*, %struct.index_tree** %tree.addr, align 8, !dbg !2521
  %root = getelementptr inbounds %struct.index_tree, %struct.index_tree* %0, i32 0, i32 0, !dbg !2522
  %1 = load %struct.index_tree_node_s*, %struct.index_tree_node_s** %root, align 8, !dbg !2522
  store %struct.index_tree_node_s* %1, %struct.index_tree_node_s** %node, align 8, !dbg !2520
  %2 = load %struct.index_tree*, %struct.index_tree** %tree.addr, align 8, !dbg !2523
  %leftmost = getelementptr inbounds %struct.index_tree, %struct.index_tree* %2, i32 0, i32 1, !dbg !2523
  %3 = load %struct.index_tree_node_s*, %struct.index_tree_node_s** %leftmost, align 8, !dbg !2523
  %cmp = icmp eq %struct.index_tree_node_s* %3, null, !dbg !2523
  br i1 %cmp, label %cond.true, label %lor.lhs.false, !dbg !2523

lor.lhs.false:                                    ; preds = %entry
  %4 = load %struct.index_tree*, %struct.index_tree** %tree.addr, align 8, !dbg !2524
  %leftmost1 = getelementptr inbounds %struct.index_tree, %struct.index_tree* %4, i32 0, i32 1, !dbg !2524
  %5 = load %struct.index_tree_node_s*, %struct.index_tree_node_s** %leftmost1, align 8, !dbg !2524
  %uncompressed_base = getelementptr inbounds %struct.index_tree_node_s, %struct.index_tree_node_s* %5, i32 0, i32 0, !dbg !2524
  %6 = load i64, i64* %uncompressed_base, align 8, !dbg !2524
  %cmp2 = icmp eq i64 %6, 0, !dbg !2524
  br i1 %cmp2, label %cond.true, label %cond.false, !dbg !2524

cond.true:                                        ; preds = %lor.lhs.false, %entry
  br label %cond.end, !dbg !2526

cond.false:                                       ; preds = %lor.lhs.false
  call void @__assert_fail(i8* getelementptr inbounds ([71 x i8], [71 x i8]* @.str.18, i32 0, i32 0), i8* getelementptr inbounds ([77 x i8], [77 x i8]* @.str.1, i32 0, i32 0), i32 325, i8* getelementptr inbounds ([54 x i8], [54 x i8]* @__PRETTY_FUNCTION__.index_tree_locate, i32 0, i32 0)) #8, !dbg !2528
  unreachable, !dbg !2528
                                                  ; No predecessors!
  br label %cond.end, !dbg !2530

cond.end:                                         ; preds = %7, %cond.true
  br label %while.cond, !dbg !2532

while.cond:                                       ; preds = %if.end, %cond.end
  %8 = load %struct.index_tree_node_s*, %struct.index_tree_node_s** %node, align 8, !dbg !2533
  %cmp3 = icmp ne %struct.index_tree_node_s* %8, null, !dbg !2534
  br i1 %cmp3, label %while.body, label %while.end, !dbg !2535

while.body:                                       ; preds = %while.cond
  %9 = load %struct.index_tree_node_s*, %struct.index_tree_node_s** %node, align 8, !dbg !2536
  %uncompressed_base4 = getelementptr inbounds %struct.index_tree_node_s, %struct.index_tree_node_s* %9, i32 0, i32 0, !dbg !2539
  %10 = load i64, i64* %uncompressed_base4, align 8, !dbg !2539
  %11 = load i64, i64* %target.addr, align 8, !dbg !2540
  %cmp5 = icmp ugt i64 %10, %11, !dbg !2541
  br i1 %cmp5, label %if.then, label %if.else, !dbg !2542

if.then:                                          ; preds = %while.body
  %12 = load %struct.index_tree_node_s*, %struct.index_tree_node_s** %node, align 8, !dbg !2543
  %left = getelementptr inbounds %struct.index_tree_node_s, %struct.index_tree_node_s* %12, i32 0, i32 3, !dbg !2545
  %13 = load %struct.index_tree_node_s*, %struct.index_tree_node_s** %left, align 8, !dbg !2545
  store %struct.index_tree_node_s* %13, %struct.index_tree_node_s** %node, align 8, !dbg !2546
  br label %if.end, !dbg !2547

if.else:                                          ; preds = %while.body
  %14 = load %struct.index_tree_node_s*, %struct.index_tree_node_s** %node, align 8, !dbg !2548
  store %struct.index_tree_node_s* %14, %struct.index_tree_node_s** %result, align 8, !dbg !2550
  %15 = load %struct.index_tree_node_s*, %struct.index_tree_node_s** %node, align 8, !dbg !2551
  %right = getelementptr inbounds %struct.index_tree_node_s, %struct.index_tree_node_s* %15, i32 0, i32 4, !dbg !2552
  %16 = load %struct.index_tree_node_s*, %struct.index_tree_node_s** %right, align 8, !dbg !2552
  store %struct.index_tree_node_s* %16, %struct.index_tree_node_s** %node, align 8, !dbg !2553
  br label %if.end

if.end:                                           ; preds = %if.else, %if.then
  br label %while.cond, !dbg !2554

while.end:                                        ; preds = %while.cond
  %17 = load %struct.index_tree_node_s*, %struct.index_tree_node_s** %result, align 8, !dbg !2555
  %18 = bitcast %struct.index_tree_node_s* %17 to i8*, !dbg !2556
  ret i8* %18, !dbg !2557
}

; Function Attrs: nounwind uwtable
define internal void @index_tree_init(%struct.index_tree* %tree) #0 !dbg !274 {
entry:
  %tree.addr = alloca %struct.index_tree*, align 8
  store %struct.index_tree* %tree, %struct.index_tree** %tree.addr, align 8
  call void @llvm.dbg.declare(metadata %struct.index_tree** %tree.addr, metadata !2558, metadata !341), !dbg !2559
  %0 = load %struct.index_tree*, %struct.index_tree** %tree.addr, align 8, !dbg !2560
  %root = getelementptr inbounds %struct.index_tree, %struct.index_tree* %0, i32 0, i32 0, !dbg !2561
  store %struct.index_tree_node_s* null, %struct.index_tree_node_s** %root, align 8, !dbg !2562
  %1 = load %struct.index_tree*, %struct.index_tree** %tree.addr, align 8, !dbg !2563
  %leftmost = getelementptr inbounds %struct.index_tree, %struct.index_tree* %1, i32 0, i32 1, !dbg !2564
  store %struct.index_tree_node_s* null, %struct.index_tree_node_s** %leftmost, align 8, !dbg !2565
  %2 = load %struct.index_tree*, %struct.index_tree** %tree.addr, align 8, !dbg !2566
  %rightmost = getelementptr inbounds %struct.index_tree, %struct.index_tree* %2, i32 0, i32 2, !dbg !2567
  store %struct.index_tree_node_s* null, %struct.index_tree_node_s** %rightmost, align 8, !dbg !2568
  %3 = load %struct.index_tree*, %struct.index_tree** %tree.addr, align 8, !dbg !2569
  %count = getelementptr inbounds %struct.index_tree, %struct.index_tree* %3, i32 0, i32 3, !dbg !2570
  store i32 0, i32* %count, align 8, !dbg !2571
  ret void, !dbg !2572
}

; Function Attrs: inlinehint nounwind uwtable
define internal i32 @bsr32(i32 %n) #4 !dbg !284 {
entry:
  %n.addr = alloca i32, align 4
  store i32 %n, i32* %n.addr, align 4
  call void @llvm.dbg.declare(metadata i32* %n.addr, metadata !2573, metadata !341), !dbg !2574
  %0 = load i32, i32* %n.addr, align 4, !dbg !2575
  %1 = call i32 @llvm.ctlz.i32(i32 %0, i1 true), !dbg !2576
  %xor = xor i32 %1, 31, !dbg !2577
  ret i32 %xor, !dbg !2578
}

; Function Attrs: inlinehint nounwind uwtable
define internal i32 @ctz32(i32 %n) #4 !dbg !288 {
entry:
  %n.addr = alloca i32, align 4
  store i32 %n, i32* %n.addr, align 4
  call void @llvm.dbg.declare(metadata i32* %n.addr, metadata !2579, metadata !341), !dbg !2580
  %0 = load i32, i32* %n.addr, align 4, !dbg !2581
  %1 = call i32 @llvm.cttz.i32(i32 %0, i1 true), !dbg !2582
  ret i32 %1, !dbg !2583
}

; Function Attrs: nounwind readnone
declare i32 @llvm.ctlz.i32(i32, i1) #1

; Function Attrs: nounwind readnone
declare i32 @llvm.cttz.i32(i32, i1) #1

; Function Attrs: nounwind uwtable
define internal void @index_tree_node_end(%struct.index_tree_node_s* %node, %struct.lzma_allocator* %allocator, void (i8*, %struct.lzma_allocator*)* %free_func) #0 !dbg !295 {
entry:
  %node.addr = alloca %struct.index_tree_node_s*, align 8
  %allocator.addr = alloca %struct.lzma_allocator*, align 8
  %free_func.addr = alloca void (i8*, %struct.lzma_allocator*)*, align 8
  store %struct.index_tree_node_s* %node, %struct.index_tree_node_s** %node.addr, align 8
  call void @llvm.dbg.declare(metadata %struct.index_tree_node_s** %node.addr, metadata !2584, metadata !341), !dbg !2585
  store %struct.lzma_allocator* %allocator, %struct.lzma_allocator** %allocator.addr, align 8
  call void @llvm.dbg.declare(metadata %struct.lzma_allocator** %allocator.addr, metadata !2586, metadata !341), !dbg !2587
  store void (i8*, %struct.lzma_allocator*)* %free_func, void (i8*, %struct.lzma_allocator*)** %free_func.addr, align 8
  call void @llvm.dbg.declare(metadata void (i8*, %struct.lzma_allocator*)** %free_func.addr, metadata !2588, metadata !341), !dbg !2589
  %0 = load %struct.index_tree_node_s*, %struct.index_tree_node_s** %node.addr, align 8, !dbg !2590
  %left = getelementptr inbounds %struct.index_tree_node_s, %struct.index_tree_node_s* %0, i32 0, i32 3, !dbg !2592
  %1 = load %struct.index_tree_node_s*, %struct.index_tree_node_s** %left, align 8, !dbg !2592
  %cmp = icmp ne %struct.index_tree_node_s* %1, null, !dbg !2593
  br i1 %cmp, label %if.then, label %if.end, !dbg !2594

if.then:                                          ; preds = %entry
  %2 = load %struct.index_tree_node_s*, %struct.index_tree_node_s** %node.addr, align 8, !dbg !2595
  %left1 = getelementptr inbounds %struct.index_tree_node_s, %struct.index_tree_node_s* %2, i32 0, i32 3, !dbg !2596
  %3 = load %struct.index_tree_node_s*, %struct.index_tree_node_s** %left1, align 8, !dbg !2596
  %4 = load %struct.lzma_allocator*, %struct.lzma_allocator** %allocator.addr, align 8, !dbg !2597
  %5 = load void (i8*, %struct.lzma_allocator*)*, void (i8*, %struct.lzma_allocator*)** %free_func.addr, align 8, !dbg !2598
  call void @index_tree_node_end(%struct.index_tree_node_s* %3, %struct.lzma_allocator* %4, void (i8*, %struct.lzma_allocator*)* %5), !dbg !2599
  br label %if.end, !dbg !2599

if.end:                                           ; preds = %if.then, %entry
  %6 = load %struct.index_tree_node_s*, %struct.index_tree_node_s** %node.addr, align 8, !dbg !2600
  %right = getelementptr inbounds %struct.index_tree_node_s, %struct.index_tree_node_s* %6, i32 0, i32 4, !dbg !2602
  %7 = load %struct.index_tree_node_s*, %struct.index_tree_node_s** %right, align 8, !dbg !2602
  %cmp2 = icmp ne %struct.index_tree_node_s* %7, null, !dbg !2603
  br i1 %cmp2, label %if.then3, label %if.end5, !dbg !2604

if.then3:                                         ; preds = %if.end
  %8 = load %struct.index_tree_node_s*, %struct.index_tree_node_s** %node.addr, align 8, !dbg !2605
  %right4 = getelementptr inbounds %struct.index_tree_node_s, %struct.index_tree_node_s* %8, i32 0, i32 4, !dbg !2606
  %9 = load %struct.index_tree_node_s*, %struct.index_tree_node_s** %right4, align 8, !dbg !2606
  %10 = load %struct.lzma_allocator*, %struct.lzma_allocator** %allocator.addr, align 8, !dbg !2607
  %11 = load void (i8*, %struct.lzma_allocator*)*, void (i8*, %struct.lzma_allocator*)** %free_func.addr, align 8, !dbg !2608
  call void @index_tree_node_end(%struct.index_tree_node_s* %9, %struct.lzma_allocator* %10, void (i8*, %struct.lzma_allocator*)* %11), !dbg !2609
  br label %if.end5, !dbg !2609

if.end5:                                          ; preds = %if.then3, %if.end
  %12 = load void (i8*, %struct.lzma_allocator*)*, void (i8*, %struct.lzma_allocator*)** %free_func.addr, align 8, !dbg !2610
  %cmp6 = icmp ne void (i8*, %struct.lzma_allocator*)* %12, null, !dbg !2612
  br i1 %cmp6, label %if.then7, label %if.end8, !dbg !2613

if.then7:                                         ; preds = %if.end5
  %13 = load void (i8*, %struct.lzma_allocator*)*, void (i8*, %struct.lzma_allocator*)** %free_func.addr, align 8, !dbg !2614
  %14 = load %struct.index_tree_node_s*, %struct.index_tree_node_s** %node.addr, align 8, !dbg !2615
  %15 = bitcast %struct.index_tree_node_s* %14 to i8*, !dbg !2615
  %16 = load %struct.lzma_allocator*, %struct.lzma_allocator** %allocator.addr, align 8, !dbg !2616
  call void %13(i8* %15, %struct.lzma_allocator* %16), !dbg !2614
  br label %if.end8, !dbg !2614

if.end8:                                          ; preds = %if.then7, %if.end5
  %17 = load %struct.index_tree_node_s*, %struct.index_tree_node_s** %node.addr, align 8, !dbg !2617
  %18 = bitcast %struct.index_tree_node_s* %17 to i8*, !dbg !2617
  %19 = load %struct.lzma_allocator*, %struct.lzma_allocator** %allocator.addr, align 8, !dbg !2618
  call void @lzma_free(i8* %18, %struct.lzma_allocator* %19), !dbg !2619
  ret void, !dbg !2620
}

attributes #0 = { nounwind uwtable "disable-tail-calls"="false" "less-precise-fpmad"="false" "no-frame-pointer-elim"="true" "no-frame-pointer-elim-non-leaf" "no-infs-fp-math"="false" "no-nans-fp-math"="false" "stack-protector-buffer-size"="8" "target-cpu"="x86-64" "target-features"="+fxsr,+mmx,+sse,+sse2" "unsafe-fp-math"="false" "use-soft-float"="false" }
attributes #1 = { nounwind readnone }
attributes #2 = { "disable-tail-calls"="false" "less-precise-fpmad"="false" "no-frame-pointer-elim"="true" "no-frame-pointer-elim-non-leaf" "no-infs-fp-math"="false" "no-nans-fp-math"="false" "stack-protector-buffer-size"="8" "target-cpu"="x86-64" "target-features"="+fxsr,+mmx,+sse,+sse2" "unsafe-fp-math"="false" "use-soft-float"="false" }
attributes #3 = { nounwind readonly uwtable "disable-tail-calls"="false" "less-precise-fpmad"="false" "no-frame-pointer-elim"="true" "no-frame-pointer-elim-non-leaf" "no-infs-fp-math"="false" "no-nans-fp-math"="false" "stack-protector-buffer-size"="8" "target-cpu"="x86-64" "target-features"="+fxsr,+mmx,+sse,+sse2" "unsafe-fp-math"="false" "use-soft-float"="false" }
attributes #4 = { inlinehint nounwind uwtable "disable-tail-calls"="false" "less-precise-fpmad"="false" "no-frame-pointer-elim"="true" "no-frame-pointer-elim-non-leaf" "no-infs-fp-math"="false" "no-nans-fp-math"="false" "stack-protector-buffer-size"="8" "target-cpu"="x86-64" "target-features"="+fxsr,+mmx,+sse,+sse2" "unsafe-fp-math"="false" "use-soft-float"="false" }
attributes #5 = { nounwind readonly "disable-tail-calls"="false" "less-precise-fpmad"="false" "no-frame-pointer-elim"="true" "no-frame-pointer-elim-non-leaf" "no-infs-fp-math"="false" "no-nans-fp-math"="false" "stack-protector-buffer-size"="8" "target-cpu"="x86-64" "target-features"="+fxsr,+mmx,+sse,+sse2" "unsafe-fp-math"="false" "use-soft-float"="false" }
attributes #6 = { argmemonly nounwind }
attributes #7 = { noreturn nounwind "disable-tail-calls"="false" "less-precise-fpmad"="false" "no-frame-pointer-elim"="true" "no-frame-pointer-elim-non-leaf" "no-infs-fp-math"="false" "no-nans-fp-math"="false" "stack-protector-buffer-size"="8" "target-cpu"="x86-64" "target-features"="+fxsr,+mmx,+sse,+sse2" "unsafe-fp-math"="false" "use-soft-float"="false" }
attributes #8 = { noreturn nounwind }
attributes #9 = { nounwind }
attributes #10 = { nounwind readonly }

!llvm.dbg.cu = !{!0}
!llvm.module.flags = !{!337, !338}
!llvm.ident = !{!339}

!0 = distinct !DICompileUnit(language: DW_LANG_C99, file: !1, producer: "clang version 3.8.0 (tags/RELEASE_380/final)", isOptimized: false, runtimeVersion: 0, emissionKind: 1, enums: !2, retainedTypes: !47, subprograms: !132)
!1 = !DIFile(filename: "/data/download/cmake/cmake-master/Utilities/cmliblzma/liblzma/common/index.c", directory: "/data/download/cmake/cmake-master/Utilities/cmliblzma")
!2 = !{!3, !10, !14, !28, !35, !40}
!3 = !DICompositeType(tag: DW_TAG_enumeration_type, file: !4, line: 27, size: 32, align: 32, elements: !5)
!4 = !DIFile(filename: "/data/download/cmake/cmake-master/Utilities/cmliblzma/liblzma/api/lzma/check.h", directory: "/data/download/cmake/cmake-master/Utilities/cmliblzma")
!5 = !{!6, !7, !8, !9}
!6 = !DIEnumerator(name: "LZMA_CHECK_NONE", value: 0)
!7 = !DIEnumerator(name: "LZMA_CHECK_CRC32", value: 1)
!8 = !DIEnumerator(name: "LZMA_CHECK_CRC64", value: 4)
!9 = !DIEnumerator(name: "LZMA_CHECK_SHA256", value: 10)
!10 = !DICompositeType(tag: DW_TAG_enumeration_type, file: !11, line: 44, size: 32, align: 32, elements: !12)
!11 = !DIFile(filename: "/data/download/cmake/cmake-master/Utilities/cmliblzma/liblzma/api/lzma/base.h", directory: "/data/download/cmake/cmake-master/Utilities/cmliblzma")
!12 = !{!13}
!13 = !DIEnumerator(name: "LZMA_RESERVED_ENUM", value: 0)
!14 = !DICompositeType(tag: DW_TAG_enumeration_type, file: !11, line: 57, size: 32, align: 32, elements: !15)
!15 = !{!16, !17, !18, !19, !20, !21, !22, !23, !24, !25, !26, !27}
!16 = !DIEnumerator(name: "LZMA_OK", value: 0)
!17 = !DIEnumerator(name: "LZMA_STREAM_END", value: 1)
!18 = !DIEnumerator(name: "LZMA_NO_CHECK", value: 2)
!19 = !DIEnumerator(name: "LZMA_UNSUPPORTED_CHECK", value: 3)
!20 = !DIEnumerator(name: "LZMA_GET_CHECK", value: 4)
!21 = !DIEnumerator(name: "LZMA_MEM_ERROR", value: 5)
!22 = !DIEnumerator(name: "LZMA_MEMLIMIT_ERROR", value: 6)
!23 = !DIEnumerator(name: "LZMA_FORMAT_ERROR", value: 7)
!24 = !DIEnumerator(name: "LZMA_OPTIONS_ERROR", value: 8)
!25 = !DIEnumerator(name: "LZMA_DATA_ERROR", value: 9)
!26 = !DIEnumerator(name: "LZMA_BUF_ERROR", value: 10)
!27 = !DIEnumerator(name: "LZMA_PROG_ERROR", value: 11)
!28 = !DICompositeType(tag: DW_TAG_enumeration_type, file: !1, line: 979, size: 32, align: 32, elements: !29)
!29 = !{!30, !31, !32, !33, !34}
!30 = !DIEnumerator(name: "ITER_INDEX", value: 0)
!31 = !DIEnumerator(name: "ITER_STREAM", value: 1)
!32 = !DIEnumerator(name: "ITER_GROUP", value: 2)
!33 = !DIEnumerator(name: "ITER_RECORD", value: 3)
!34 = !DIEnumerator(name: "ITER_METHOD", value: 4)
!35 = !DICompositeType(tag: DW_TAG_enumeration_type, file: !1, line: 989, size: 32, align: 32, elements: !36)
!36 = !{!37, !38, !39}
!37 = !DIEnumerator(name: "ITER_METHOD_NORMAL", value: 0)
!38 = !DIEnumerator(name: "ITER_METHOD_NEXT", value: 1)
!39 = !DIEnumerator(name: "ITER_METHOD_LEFTMOST", value: 2)
!40 = !DICompositeType(tag: DW_TAG_enumeration_type, file: !41, line: 226, size: 32, align: 32, elements: !42)
!41 = !DIFile(filename: "/data/download/cmake/cmake-master/Utilities/cmliblzma/liblzma/api/lzma/index.h", directory: "/data/download/cmake/cmake-master/Utilities/cmliblzma")
!42 = !{!43, !44, !45, !46}
!43 = !DIEnumerator(name: "LZMA_INDEX_ITER_ANY", value: 0)
!44 = !DIEnumerator(name: "LZMA_INDEX_ITER_STREAM", value: 1)
!45 = !DIEnumerator(name: "LZMA_INDEX_ITER_BLOCK", value: 2)
!46 = !DIEnumerator(name: "LZMA_INDEX_ITER_NONEMPTY_BLOCK", value: 3)
!47 = !{!48, !49, !52, !112, !130, !131, !73}
!48 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: null, size: 64, align: 64)
!49 = !DIDerivedType(tag: DW_TAG_typedef, name: "size_t", file: !50, line: 62, baseType: !51)
!50 = !DIFile(filename: "/opt/llvm-build/bin/../lib/clang/3.8.0/include/stddef.h", directory: "/data/download/cmake/cmake-master/Utilities/cmliblzma")
!51 = !DIBasicType(name: "long unsigned int", size: 64, align: 64, encoding: DW_ATE_unsigned)
!52 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !53, size: 64, align: 64)
!53 = !DIDerivedType(tag: DW_TAG_const_type, baseType: !54)
!54 = !DIDerivedType(tag: DW_TAG_typedef, name: "index_stream", file: !1, line: 142, baseType: !55)
!55 = !DICompositeType(tag: DW_TAG_structure_type, file: !1, line: 107, size: 1344, align: 64, elements: !56)
!56 = !{!57, !71, !74, !75, !83, !84, !85, !111}
!57 = !DIDerivedType(tag: DW_TAG_member, name: "node", scope: !55, file: !1, line: 109, baseType: !58, size: 320, align: 64)
!58 = !DIDerivedType(tag: DW_TAG_typedef, name: "index_tree_node", file: !1, line: 29, baseType: !59)
!59 = !DICompositeType(tag: DW_TAG_structure_type, name: "index_tree_node_s", file: !1, line: 30, size: 320, align: 64, elements: !60)
!60 = !{!61, !66, !67, !69, !70}
!61 = !DIDerivedType(tag: DW_TAG_member, name: "uncompressed_base", scope: !59, file: !1, line: 34, baseType: !62, size: 64, align: 64)
!62 = !DIDerivedType(tag: DW_TAG_typedef, name: "lzma_vli", file: !63, line: 63, baseType: !64)
!63 = !DIFile(filename: "/data/download/cmake/cmake-master/Utilities/cmliblzma/liblzma/api/lzma/vli.h", directory: "/data/download/cmake/cmake-master/Utilities/cmliblzma")
!64 = !DIDerivedType(tag: DW_TAG_typedef, name: "uint64_t", file: !65, line: 55, baseType: !51)
!65 = !DIFile(filename: "/usr/include/stdint.h", directory: "/data/download/cmake/cmake-master/Utilities/cmliblzma")
!66 = !DIDerivedType(tag: DW_TAG_member, name: "compressed_base", scope: !59, file: !1, line: 37, baseType: !62, size: 64, align: 64, offset: 64)
!67 = !DIDerivedType(tag: DW_TAG_member, name: "parent", scope: !59, file: !1, line: 39, baseType: !68, size: 64, align: 64, offset: 128)
!68 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !58, size: 64, align: 64)
!69 = !DIDerivedType(tag: DW_TAG_member, name: "left", scope: !59, file: !1, line: 40, baseType: !68, size: 64, align: 64, offset: 192)
!70 = !DIDerivedType(tag: DW_TAG_member, name: "right", scope: !59, file: !1, line: 41, baseType: !68, size: 64, align: 64, offset: 256)
!71 = !DIDerivedType(tag: DW_TAG_member, name: "number", scope: !55, file: !1, line: 112, baseType: !72, size: 32, align: 32, offset: 320)
!72 = !DIDerivedType(tag: DW_TAG_typedef, name: "uint32_t", file: !65, line: 51, baseType: !73)
!73 = !DIBasicType(name: "unsigned int", size: 32, align: 32, encoding: DW_ATE_unsigned)
!74 = !DIDerivedType(tag: DW_TAG_member, name: "block_number_base", scope: !55, file: !1, line: 115, baseType: !62, size: 64, align: 64, offset: 384)
!75 = !DIDerivedType(tag: DW_TAG_member, name: "groups", scope: !55, file: !1, line: 122, baseType: !76, size: 256, align: 64, offset: 448)
!76 = !DIDerivedType(tag: DW_TAG_typedef, name: "index_tree", file: !1, line: 62, baseType: !77)
!77 = !DICompositeType(tag: DW_TAG_structure_type, file: !1, line: 46, size: 256, align: 64, elements: !78)
!78 = !{!79, !80, !81, !82}
!79 = !DIDerivedType(tag: DW_TAG_member, name: "root", scope: !77, file: !1, line: 48, baseType: !68, size: 64, align: 64)
!80 = !DIDerivedType(tag: DW_TAG_member, name: "leftmost", scope: !77, file: !1, line: 53, baseType: !68, size: 64, align: 64, offset: 64)
!81 = !DIDerivedType(tag: DW_TAG_member, name: "rightmost", scope: !77, file: !1, line: 57, baseType: !68, size: 64, align: 64, offset: 128)
!82 = !DIDerivedType(tag: DW_TAG_member, name: "count", scope: !77, file: !1, line: 60, baseType: !72, size: 32, align: 32, offset: 192)
!83 = !DIDerivedType(tag: DW_TAG_member, name: "record_count", scope: !55, file: !1, line: 125, baseType: !62, size: 64, align: 64, offset: 704)
!84 = !DIDerivedType(tag: DW_TAG_member, name: "index_list_size", scope: !55, file: !1, line: 130, baseType: !62, size: 64, align: 64, offset: 768)
!85 = !DIDerivedType(tag: DW_TAG_member, name: "stream_flags", scope: !55, file: !1, line: 136, baseType: !86, size: 448, align: 64, offset: 832)
!86 = !DIDerivedType(tag: DW_TAG_typedef, name: "lzma_stream_flags", file: !87, line: 105, baseType: !88)
!87 = !DIFile(filename: "/data/download/cmake/cmake-master/Utilities/cmliblzma/liblzma/api/lzma/stream_flags.h", directory: "/data/download/cmake/cmake-master/Utilities/cmliblzma")
!88 = !DICompositeType(tag: DW_TAG_structure_type, file: !87, line: 33, size: 448, align: 64, elements: !89)
!89 = !{!90, !91, !92, !94, !96, !97, !98, !99, !102, !103, !104, !105, !106, !107, !108, !109, !110}
!90 = !DIDerivedType(tag: DW_TAG_member, name: "version", scope: !88, file: !87, line: 51, baseType: !72, size: 32, align: 32)
!91 = !DIDerivedType(tag: DW_TAG_member, name: "backward_size", scope: !88, file: !87, line: 69, baseType: !62, size: 64, align: 64, offset: 64)
!92 = !DIDerivedType(tag: DW_TAG_member, name: "check", scope: !88, file: !87, line: 79, baseType: !93, size: 32, align: 32, offset: 128)
!93 = !DIDerivedType(tag: DW_TAG_typedef, name: "lzma_check", file: !4, line: 55, baseType: !3)
!94 = !DIDerivedType(tag: DW_TAG_member, name: "reserved_enum1", scope: !88, file: !87, line: 90, baseType: !95, size: 32, align: 32, offset: 160)
!95 = !DIDerivedType(tag: DW_TAG_typedef, name: "lzma_reserved_enum", file: !11, line: 46, baseType: !10)
!96 = !DIDerivedType(tag: DW_TAG_member, name: "reserved_enum2", scope: !88, file: !87, line: 91, baseType: !95, size: 32, align: 32, offset: 192)
!97 = !DIDerivedType(tag: DW_TAG_member, name: "reserved_enum3", scope: !88, file: !87, line: 92, baseType: !95, size: 32, align: 32, offset: 224)
!98 = !DIDerivedType(tag: DW_TAG_member, name: "reserved_enum4", scope: !88, file: !87, line: 93, baseType: !95, size: 32, align: 32, offset: 256)
!99 = !DIDerivedType(tag: DW_TAG_member, name: "reserved_bool1", scope: !88, file: !87, line: 94, baseType: !100, size: 8, align: 8, offset: 288)
!100 = !DIDerivedType(tag: DW_TAG_typedef, name: "lzma_bool", file: !11, line: 29, baseType: !101)
!101 = !DIBasicType(name: "unsigned char", size: 8, align: 8, encoding: DW_ATE_unsigned_char)
!102 = !DIDerivedType(tag: DW_TAG_member, name: "reserved_bool2", scope: !88, file: !87, line: 95, baseType: !100, size: 8, align: 8, offset: 296)
!103 = !DIDerivedType(tag: DW_TAG_member, name: "reserved_bool3", scope: !88, file: !87, line: 96, baseType: !100, size: 8, align: 8, offset: 304)
!104 = !DIDerivedType(tag: DW_TAG_member, name: "reserved_bool4", scope: !88, file: !87, line: 97, baseType: !100, size: 8, align: 8, offset: 312)
!105 = !DIDerivedType(tag: DW_TAG_member, name: "reserved_bool5", scope: !88, file: !87, line: 98, baseType: !100, size: 8, align: 8, offset: 320)
!106 = !DIDerivedType(tag: DW_TAG_member, name: "reserved_bool6", scope: !88, file: !87, line: 99, baseType: !100, size: 8, align: 8, offset: 328)
!107 = !DIDerivedType(tag: DW_TAG_member, name: "reserved_bool7", scope: !88, file: !87, line: 100, baseType: !100, size: 8, align: 8, offset: 336)
!108 = !DIDerivedType(tag: DW_TAG_member, name: "reserved_bool8", scope: !88, file: !87, line: 101, baseType: !100, size: 8, align: 8, offset: 344)
!109 = !DIDerivedType(tag: DW_TAG_member, name: "reserved_int1", scope: !88, file: !87, line: 102, baseType: !72, size: 32, align: 32, offset: 352)
!110 = !DIDerivedType(tag: DW_TAG_member, name: "reserved_int2", scope: !88, file: !87, line: 103, baseType: !72, size: 32, align: 32, offset: 384)
!111 = !DIDerivedType(tag: DW_TAG_member, name: "stream_padding", scope: !55, file: !1, line: 140, baseType: !62, size: 64, align: 64, offset: 1280)
!112 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !113, size: 64, align: 64)
!113 = !DIDerivedType(tag: DW_TAG_const_type, baseType: !114)
!114 = !DIDerivedType(tag: DW_TAG_typedef, name: "index_group", file: !1, line: 104, baseType: !115)
!115 = !DICompositeType(tag: DW_TAG_structure_type, file: !1, line: 71, size: 512, align: 64, elements: !116)
!116 = !{!117, !118, !119, !120, !121}
!117 = !DIDerivedType(tag: DW_TAG_member, name: "node", scope: !115, file: !1, line: 73, baseType: !58, size: 320, align: 64)
!118 = !DIDerivedType(tag: DW_TAG_member, name: "number_base", scope: !115, file: !1, line: 76, baseType: !62, size: 64, align: 64, offset: 320)
!119 = !DIDerivedType(tag: DW_TAG_member, name: "allocated", scope: !115, file: !1, line: 79, baseType: !49, size: 64, align: 64, offset: 384)
!120 = !DIDerivedType(tag: DW_TAG_member, name: "last", scope: !115, file: !1, line: 82, baseType: !49, size: 64, align: 64, offset: 448)
!121 = !DIDerivedType(tag: DW_TAG_member, name: "records", scope: !115, file: !1, line: 102, baseType: !122, offset: 512)
!122 = !DICompositeType(tag: DW_TAG_array_type, baseType: !123, align: 64, elements: !128)
!123 = !DIDerivedType(tag: DW_TAG_typedef, name: "index_record", file: !1, line: 68, baseType: !124)
!124 = !DICompositeType(tag: DW_TAG_structure_type, file: !1, line: 65, size: 128, align: 64, elements: !125)
!125 = !{!126, !127}
!126 = !DIDerivedType(tag: DW_TAG_member, name: "uncompressed_sum", scope: !124, file: !1, line: 66, baseType: !62, size: 64, align: 64)
!127 = !DIDerivedType(tag: DW_TAG_member, name: "unpadded_sum", scope: !124, file: !1, line: 67, baseType: !62, size: 64, align: 64, offset: 64)
!128 = !{!129}
!129 = !DISubrange(count: -1)
!130 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !54, size: 64, align: 64)
!131 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !114, size: 64, align: 64)
!132 = !{!133, !161, !164, !167, !170, !175, !178, !179, !180, !181, !182, !183, !184, !187, !188, !194, !197, !200, !204, !207, !263, !266, !270, !273, !274, !278, !281, !284, !288, !289, !295, !298, !299, !303, !306, !307, !310, !323, !326, !331, !332}
!133 = distinct !DISubprogram(name: "lzma_index_init", scope: !1, file: !1, line: 401, type: !134, isLocal: false, isDefinition: true, scopeLine: 402, flags: DIFlagPrototyped, isOptimized: false, variables: !160)
!134 = !DISubroutineType(types: !135)
!135 = !{!136, !147}
!136 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !137, size: 64, align: 64)
!137 = !DIDerivedType(tag: DW_TAG_typedef, name: "lzma_index", file: !41, line: 37, baseType: !138)
!138 = !DICompositeType(tag: DW_TAG_structure_type, name: "lzma_index_s", file: !1, line: 145, size: 640, align: 64, elements: !139)
!139 = !{!140, !141, !142, !143, !144, !145, !146}
!140 = !DIDerivedType(tag: DW_TAG_member, name: "streams", scope: !138, file: !1, line: 149, baseType: !76, size: 256, align: 64)
!141 = !DIDerivedType(tag: DW_TAG_member, name: "uncompressed_size", scope: !138, file: !1, line: 152, baseType: !62, size: 64, align: 64, offset: 256)
!142 = !DIDerivedType(tag: DW_TAG_member, name: "total_size", scope: !138, file: !1, line: 155, baseType: !62, size: 64, align: 64, offset: 320)
!143 = !DIDerivedType(tag: DW_TAG_member, name: "record_count", scope: !138, file: !1, line: 158, baseType: !62, size: 64, align: 64, offset: 384)
!144 = !DIDerivedType(tag: DW_TAG_member, name: "index_list_size", scope: !138, file: !1, line: 166, baseType: !62, size: 64, align: 64, offset: 448)
!145 = !DIDerivedType(tag: DW_TAG_member, name: "prealloc", scope: !138, file: !1, line: 171, baseType: !49, size: 64, align: 64, offset: 512)
!146 = !DIDerivedType(tag: DW_TAG_member, name: "checks", scope: !138, file: !1, line: 177, baseType: !72, size: 32, align: 32, offset: 576)
!147 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !148, size: 64, align: 64)
!148 = !DIDerivedType(tag: DW_TAG_typedef, name: "lzma_allocator", file: !11, line: 403, baseType: !149)
!149 = !DICompositeType(tag: DW_TAG_structure_type, file: !11, line: 341, size: 192, align: 64, elements: !150)
!150 = !{!151, !155, !159}
!151 = !DIDerivedType(tag: DW_TAG_member, name: "alloc", scope: !149, file: !11, line: 376, baseType: !152, size: 64, align: 64)
!152 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !153, size: 64, align: 64)
!153 = !DISubroutineType(types: !154)
!154 = !{!48, !48, !49, !49}
!155 = !DIDerivedType(tag: DW_TAG_member, name: "free", scope: !149, file: !11, line: 390, baseType: !156, size: 64, align: 64, offset: 64)
!156 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !157, size: 64, align: 64)
!157 = !DISubroutineType(types: !158)
!158 = !{null, !48, !48}
!159 = !DIDerivedType(tag: DW_TAG_member, name: "opaque", scope: !149, file: !11, line: 401, baseType: !48, size: 64, align: 64, offset: 128)
!160 = !{}
!161 = distinct !DISubprogram(name: "lzma_index_end", scope: !1, file: !1, line: 422, type: !162, isLocal: false, isDefinition: true, scopeLine: 423, flags: DIFlagPrototyped, isOptimized: false, variables: !160)
!162 = !DISubroutineType(types: !163)
!163 = !{null, !136, !147}
!164 = distinct !DISubprogram(name: "lzma_index_prealloc", scope: !1, file: !1, line: 436, type: !165, isLocal: false, isDefinition: true, scopeLine: 437, flags: DIFlagPrototyped, isOptimized: false, variables: !160)
!165 = !DISubroutineType(types: !166)
!166 = !{null, !136, !62}
!167 = distinct !DISubprogram(name: "lzma_index_memusage", scope: !1, file: !1, line: 447, type: !168, isLocal: false, isDefinition: true, scopeLine: 448, flags: DIFlagPrototyped, isOptimized: false, variables: !160)
!168 = !DISubroutineType(types: !169)
!169 = !{!64, !62, !62}
!170 = distinct !DISubprogram(name: "lzma_index_memused", scope: !1, file: !1, line: 496, type: !171, isLocal: false, isDefinition: true, scopeLine: 497, flags: DIFlagPrototyped, isOptimized: false, variables: !160)
!171 = !DISubroutineType(types: !172)
!172 = !{!64, !173}
!173 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !174, size: 64, align: 64)
!174 = !DIDerivedType(tag: DW_TAG_const_type, baseType: !137)
!175 = distinct !DISubprogram(name: "lzma_index_block_count", scope: !1, file: !1, line: 503, type: !176, isLocal: false, isDefinition: true, scopeLine: 504, flags: DIFlagPrototyped, isOptimized: false, variables: !160)
!176 = !DISubroutineType(types: !177)
!177 = !{!62, !173}
!178 = distinct !DISubprogram(name: "lzma_index_stream_count", scope: !1, file: !1, line: 510, type: !176, isLocal: false, isDefinition: true, scopeLine: 511, flags: DIFlagPrototyped, isOptimized: false, variables: !160)
!179 = distinct !DISubprogram(name: "lzma_index_size", scope: !1, file: !1, line: 517, type: !176, isLocal: false, isDefinition: true, scopeLine: 518, flags: DIFlagPrototyped, isOptimized: false, variables: !160)
!180 = distinct !DISubprogram(name: "lzma_index_total_size", scope: !1, file: !1, line: 524, type: !176, isLocal: false, isDefinition: true, scopeLine: 525, flags: DIFlagPrototyped, isOptimized: false, variables: !160)
!181 = distinct !DISubprogram(name: "lzma_index_stream_size", scope: !1, file: !1, line: 531, type: !176, isLocal: false, isDefinition: true, scopeLine: 532, flags: DIFlagPrototyped, isOptimized: false, variables: !160)
!182 = distinct !DISubprogram(name: "lzma_index_file_size", scope: !1, file: !1, line: 565, type: !176, isLocal: false, isDefinition: true, scopeLine: 566, flags: DIFlagPrototyped, isOptimized: false, variables: !160)
!183 = distinct !DISubprogram(name: "lzma_index_uncompressed_size", scope: !1, file: !1, line: 577, type: !176, isLocal: false, isDefinition: true, scopeLine: 578, flags: DIFlagPrototyped, isOptimized: false, variables: !160)
!184 = distinct !DISubprogram(name: "lzma_index_checks", scope: !1, file: !1, line: 584, type: !185, isLocal: false, isDefinition: true, scopeLine: 585, flags: DIFlagPrototyped, isOptimized: false, variables: !160)
!185 = !DISubroutineType(types: !186)
!186 = !{!72, !173}
!187 = distinct !DISubprogram(name: "lzma_index_padding_size", scope: !1, file: !1, line: 598, type: !185, isLocal: false, isDefinition: true, scopeLine: 599, flags: DIFlagPrototyped, isOptimized: false, variables: !160)
!188 = distinct !DISubprogram(name: "lzma_index_stream_flags", scope: !1, file: !1, line: 606, type: !189, isLocal: false, isDefinition: true, scopeLine: 607, flags: DIFlagPrototyped, isOptimized: false, variables: !160)
!189 = !DISubroutineType(types: !190)
!190 = !{!191, !136, !192}
!191 = !DIDerivedType(tag: DW_TAG_typedef, name: "lzma_ret", file: !11, line: 237, baseType: !14)
!192 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !193, size: 64, align: 64)
!193 = !DIDerivedType(tag: DW_TAG_const_type, baseType: !86)
!194 = distinct !DISubprogram(name: "lzma_index_stream_padding", scope: !1, file: !1, line: 625, type: !195, isLocal: false, isDefinition: true, scopeLine: 626, flags: DIFlagPrototyped, isOptimized: false, variables: !160)
!195 = !DISubroutineType(types: !196)
!196 = !{!191, !136, !62}
!197 = distinct !DISubprogram(name: "lzma_index_append", scope: !1, file: !1, line: 650, type: !198, isLocal: false, isDefinition: true, scopeLine: 652, flags: DIFlagPrototyped, isOptimized: false, variables: !160)
!198 = !DISubroutineType(types: !199)
!199 = !{!191, !136, !147, !62, !62}
!200 = distinct !DISubprogram(name: "lzma_index_cat", scope: !1, file: !1, line: 783, type: !201, isLocal: false, isDefinition: true, scopeLine: 785, flags: DIFlagPrototyped, isOptimized: false, variables: !160)
!201 = !DISubroutineType(types: !202)
!202 = !{!191, !203, !203, !147}
!203 = !DIDerivedType(tag: DW_TAG_restrict_type, baseType: !136)
!204 = distinct !DISubprogram(name: "lzma_index_dup", scope: !1, file: !1, line: 944, type: !205, isLocal: false, isDefinition: true, scopeLine: 945, flags: DIFlagPrototyped, isOptimized: false, variables: !160)
!205 = !DISubroutineType(types: !206)
!206 = !{!136, !173, !147}
!207 = distinct !DISubprogram(name: "lzma_index_iter_init", scope: !1, file: !1, line: 1100, type: !208, isLocal: false, isDefinition: true, scopeLine: 1101, flags: DIFlagPrototyped, isOptimized: false, variables: !160)
!208 = !DISubroutineType(types: !209)
!209 = !{null, !210, !173}
!210 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !211, size: 64, align: 64)
!211 = !DIDerivedType(tag: DW_TAG_typedef, name: "lzma_index_iter", file: !41, line: 220, baseType: !212)
!212 = !DICompositeType(tag: DW_TAG_structure_type, file: !41, line: 43, size: 2432, align: 64, elements: !213)
!213 = !{!214, !234, !254}
!214 = !DIDerivedType(tag: DW_TAG_member, name: "stream", scope: !212, file: !41, line: 114, baseType: !215, size: 960, align: 64)
!215 = !DICompositeType(tag: DW_TAG_structure_type, scope: !212, file: !41, line: 44, size: 960, align: 64, elements: !216)
!216 = !{!217, !218, !221, !222, !223, !224, !225, !226, !227, !228, !229, !230, !231, !232, !233}
!217 = !DIDerivedType(tag: DW_TAG_member, name: "flags", scope: !215, file: !41, line: 51, baseType: !192, size: 64, align: 64)
!218 = !DIDerivedType(tag: DW_TAG_member, name: "reserved_ptr1", scope: !215, file: !41, line: 53, baseType: !219, size: 64, align: 64, offset: 64)
!219 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !220, size: 64, align: 64)
!220 = !DIDerivedType(tag: DW_TAG_const_type, baseType: null)
!221 = !DIDerivedType(tag: DW_TAG_member, name: "reserved_ptr2", scope: !215, file: !41, line: 54, baseType: !219, size: 64, align: 64, offset: 128)
!222 = !DIDerivedType(tag: DW_TAG_member, name: "reserved_ptr3", scope: !215, file: !41, line: 55, baseType: !219, size: 64, align: 64, offset: 192)
!223 = !DIDerivedType(tag: DW_TAG_member, name: "number", scope: !215, file: !41, line: 62, baseType: !62, size: 64, align: 64, offset: 256)
!224 = !DIDerivedType(tag: DW_TAG_member, name: "block_count", scope: !215, file: !41, line: 70, baseType: !62, size: 64, align: 64, offset: 320)
!225 = !DIDerivedType(tag: DW_TAG_member, name: "compressed_offset", scope: !215, file: !41, line: 78, baseType: !62, size: 64, align: 64, offset: 384)
!226 = !DIDerivedType(tag: DW_TAG_member, name: "uncompressed_offset", scope: !215, file: !41, line: 86, baseType: !62, size: 64, align: 64, offset: 448)
!227 = !DIDerivedType(tag: DW_TAG_member, name: "compressed_size", scope: !215, file: !41, line: 94, baseType: !62, size: 64, align: 64, offset: 512)
!228 = !DIDerivedType(tag: DW_TAG_member, name: "uncompressed_size", scope: !215, file: !41, line: 99, baseType: !62, size: 64, align: 64, offset: 576)
!229 = !DIDerivedType(tag: DW_TAG_member, name: "padding", scope: !215, file: !41, line: 108, baseType: !62, size: 64, align: 64, offset: 640)
!230 = !DIDerivedType(tag: DW_TAG_member, name: "reserved_vli1", scope: !215, file: !41, line: 110, baseType: !62, size: 64, align: 64, offset: 704)
!231 = !DIDerivedType(tag: DW_TAG_member, name: "reserved_vli2", scope: !215, file: !41, line: 111, baseType: !62, size: 64, align: 64, offset: 768)
!232 = !DIDerivedType(tag: DW_TAG_member, name: "reserved_vli3", scope: !215, file: !41, line: 112, baseType: !62, size: 64, align: 64, offset: 832)
!233 = !DIDerivedType(tag: DW_TAG_member, name: "reserved_vli4", scope: !215, file: !41, line: 113, baseType: !62, size: 64, align: 64, offset: 896)
!234 = !DIDerivedType(tag: DW_TAG_member, name: "block", scope: !212, file: !41, line: 208, baseType: !235, size: 1088, align: 64, offset: 960)
!235 = !DICompositeType(tag: DW_TAG_structure_type, scope: !212, file: !41, line: 116, size: 1088, align: 64, elements: !236)
!236 = !{!237, !238, !239, !240, !241, !242, !243, !244, !245, !246, !247, !248, !249, !250, !251, !252, !253}
!237 = !DIDerivedType(tag: DW_TAG_member, name: "number_in_file", scope: !235, file: !41, line: 122, baseType: !62, size: 64, align: 64)
!238 = !DIDerivedType(tag: DW_TAG_member, name: "compressed_file_offset", scope: !235, file: !41, line: 132, baseType: !62, size: 64, align: 64, offset: 64)
!239 = !DIDerivedType(tag: DW_TAG_member, name: "uncompressed_file_offset", scope: !235, file: !41, line: 147, baseType: !62, size: 64, align: 64, offset: 128)
!240 = !DIDerivedType(tag: DW_TAG_member, name: "number_in_stream", scope: !235, file: !41, line: 154, baseType: !62, size: 64, align: 64, offset: 192)
!241 = !DIDerivedType(tag: DW_TAG_member, name: "compressed_stream_offset", scope: !235, file: !41, line: 162, baseType: !62, size: 64, align: 64, offset: 256)
!242 = !DIDerivedType(tag: DW_TAG_member, name: "uncompressed_stream_offset", scope: !235, file: !41, line: 170, baseType: !62, size: 64, align: 64, offset: 320)
!243 = !DIDerivedType(tag: DW_TAG_member, name: "uncompressed_size", scope: !235, file: !41, line: 179, baseType: !62, size: 64, align: 64, offset: 384)
!244 = !DIDerivedType(tag: DW_TAG_member, name: "unpadded_size", scope: !235, file: !41, line: 188, baseType: !62, size: 64, align: 64, offset: 448)
!245 = !DIDerivedType(tag: DW_TAG_member, name: "total_size", scope: !235, file: !41, line: 197, baseType: !62, size: 64, align: 64, offset: 512)
!246 = !DIDerivedType(tag: DW_TAG_member, name: "reserved_vli1", scope: !235, file: !41, line: 199, baseType: !62, size: 64, align: 64, offset: 576)
!247 = !DIDerivedType(tag: DW_TAG_member, name: "reserved_vli2", scope: !235, file: !41, line: 200, baseType: !62, size: 64, align: 64, offset: 640)
!248 = !DIDerivedType(tag: DW_TAG_member, name: "reserved_vli3", scope: !235, file: !41, line: 201, baseType: !62, size: 64, align: 64, offset: 704)
!249 = !DIDerivedType(tag: DW_TAG_member, name: "reserved_vli4", scope: !235, file: !41, line: 202, baseType: !62, size: 64, align: 64, offset: 768)
!250 = !DIDerivedType(tag: DW_TAG_member, name: "reserved_ptr1", scope: !235, file: !41, line: 204, baseType: !219, size: 64, align: 64, offset: 832)
!251 = !DIDerivedType(tag: DW_TAG_member, name: "reserved_ptr2", scope: !235, file: !41, line: 205, baseType: !219, size: 64, align: 64, offset: 896)
!252 = !DIDerivedType(tag: DW_TAG_member, name: "reserved_ptr3", scope: !235, file: !41, line: 206, baseType: !219, size: 64, align: 64, offset: 960)
!253 = !DIDerivedType(tag: DW_TAG_member, name: "reserved_ptr4", scope: !235, file: !41, line: 207, baseType: !219, size: 64, align: 64, offset: 1024)
!254 = !DIDerivedType(tag: DW_TAG_member, name: "internal", scope: !212, file: !41, line: 219, baseType: !255, size: 384, align: 64, offset: 2048)
!255 = !DICompositeType(tag: DW_TAG_array_type, baseType: !256, size: 384, align: 64, elements: !261)
!256 = !DICompositeType(tag: DW_TAG_union_type, scope: !212, file: !41, line: 215, size: 64, align: 64, elements: !257)
!257 = !{!258, !259, !260}
!258 = !DIDerivedType(tag: DW_TAG_member, name: "p", scope: !256, file: !41, line: 216, baseType: !219, size: 64, align: 64)
!259 = !DIDerivedType(tag: DW_TAG_member, name: "s", scope: !256, file: !41, line: 217, baseType: !49, size: 64, align: 64)
!260 = !DIDerivedType(tag: DW_TAG_member, name: "v", scope: !256, file: !41, line: 218, baseType: !62, size: 64, align: 64)
!261 = !{!262}
!262 = !DISubrange(count: 6)
!263 = distinct !DISubprogram(name: "lzma_index_iter_rewind", scope: !1, file: !1, line: 1109, type: !264, isLocal: false, isDefinition: true, scopeLine: 1110, flags: DIFlagPrototyped, isOptimized: false, variables: !160)
!264 = !DISubroutineType(types: !265)
!265 = !{null, !210}
!266 = distinct !DISubprogram(name: "lzma_index_iter_next", scope: !1, file: !1, line: 1120, type: !267, isLocal: false, isDefinition: true, scopeLine: 1121, flags: DIFlagPrototyped, isOptimized: false, variables: !160)
!267 = !DISubroutineType(types: !268)
!268 = !{!100, !210, !269}
!269 = !DIDerivedType(tag: DW_TAG_typedef, name: "lzma_index_iter_mode", file: !41, line: 268, baseType: !40)
!270 = distinct !DISubprogram(name: "lzma_index_iter_locate", scope: !1, file: !1, line: 1232, type: !271, isLocal: false, isDefinition: true, scopeLine: 1233, flags: DIFlagPrototyped, isOptimized: false, variables: !160)
!271 = !DISubroutineType(types: !272)
!272 = !{!100, !210, !62}
!273 = distinct !DISubprogram(name: "index_init_plain", scope: !1, file: !1, line: 383, type: !134, isLocal: true, isDefinition: true, scopeLine: 384, flags: DIFlagPrototyped, isOptimized: false, variables: !160)
!274 = distinct !DISubprogram(name: "index_tree_init", scope: !1, file: !1, line: 182, type: !275, isLocal: true, isDefinition: true, scopeLine: 183, flags: DIFlagPrototyped, isOptimized: false, variables: !160)
!275 = !DISubroutineType(types: !276)
!276 = !{null, !277}
!277 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !76, size: 64, align: 64)
!278 = distinct !DISubprogram(name: "index_stream_init", scope: !1, file: !1, line: 344, type: !279, isLocal: true, isDefinition: true, scopeLine: 347, flags: DIFlagPrototyped, isOptimized: false, variables: !160)
!279 = !DISubroutineType(types: !280)
!280 = !{!130, !62, !62, !62, !62, !147}
!281 = distinct !DISubprogram(name: "index_tree_append", scope: !1, file: !1, line: 231, type: !282, isLocal: true, isDefinition: true, scopeLine: 232, flags: DIFlagPrototyped, isOptimized: false, variables: !160)
!282 = !DISubroutineType(types: !283)
!283 = !{null, !277, !68}
!284 = distinct !DISubprogram(name: "bsr32", scope: !285, file: !285, line: 372, type: !286, isLocal: true, isDefinition: true, scopeLine: 373, flags: DIFlagPrototyped, isOptimized: false, variables: !160)
!285 = !DIFile(filename: "/data/download/cmake/cmake-master/Utilities/cmliblzma/common/tuklib_integer.h", directory: "/data/download/cmake/cmake-master/Utilities/cmliblzma")
!286 = !DISubroutineType(types: !287)
!287 = !{!72, !72}
!288 = distinct !DISubprogram(name: "ctz32", scope: !285, file: !285, line: 469, type: !286, isLocal: true, isDefinition: true, scopeLine: 470, flags: DIFlagPrototyped, isOptimized: false, variables: !160)
!289 = distinct !DISubprogram(name: "index_tree_end", scope: !1, file: !1, line: 218, type: !290, isLocal: true, isDefinition: true, scopeLine: 220, flags: DIFlagPrototyped, isOptimized: false, variables: !160)
!290 = !DISubroutineType(types: !291)
!291 = !{null, !277, !147, !292}
!292 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !293, size: 64, align: 64)
!293 = !DISubroutineType(types: !294)
!294 = !{null, !48, !147}
!295 = distinct !DISubprogram(name: "index_tree_node_end", scope: !1, file: !1, line: 194, type: !296, isLocal: true, isDefinition: true, scopeLine: 196, flags: DIFlagPrototyped, isOptimized: false, variables: !160)
!296 = !DISubroutineType(types: !297)
!297 = !{null, !68, !147, !292}
!298 = distinct !DISubprogram(name: "index_stream_end", scope: !1, file: !1, line: 374, type: !293, isLocal: true, isDefinition: true, scopeLine: 375, flags: DIFlagPrototyped, isOptimized: false, variables: !160)
!299 = distinct !DISubprogram(name: "index_size", scope: !300, file: !300, line: 57, type: !301, isLocal: true, isDefinition: true, scopeLine: 58, flags: DIFlagPrototyped, isOptimized: false, variables: !160)
!300 = !DIFile(filename: "/data/download/cmake/cmake-master/Utilities/cmliblzma/liblzma/common/index.h", directory: "/data/download/cmake/cmake-master/Utilities/cmliblzma")
!301 = !DISubroutineType(types: !302)
!302 = !{!62, !62, !62}
!303 = distinct !DISubprogram(name: "index_file_size", scope: !1, file: !1, line: 541, type: !304, isLocal: true, isDefinition: true, scopeLine: 544, flags: DIFlagPrototyped, isOptimized: false, variables: !160)
!304 = !DISubroutineType(types: !305)
!305 = !{!62, !62, !62, !62, !62, !62}
!306 = distinct !DISubprogram(name: "index_size_unpadded", scope: !300, file: !300, line: 48, type: !301, isLocal: true, isDefinition: true, scopeLine: 49, flags: DIFlagPrototyped, isOptimized: false, variables: !160)
!307 = distinct !DISubprogram(name: "vli_ceil4", scope: !300, file: !300, line: 39, type: !308, isLocal: true, isDefinition: true, scopeLine: 40, flags: DIFlagPrototyped, isOptimized: false, variables: !160)
!308 = !DISubroutineType(types: !309)
!309 = !{!62, !62}
!310 = distinct !DISubprogram(name: "index_cat_helper", scope: !1, file: !1, line: 761, type: !311, isLocal: true, isDefinition: true, scopeLine: 762, flags: DIFlagPrototyped, isOptimized: false, variables: !160)
!311 = !DISubroutineType(types: !312)
!312 = !{null, !313, !130}
!313 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !314, size: 64, align: 64)
!314 = !DIDerivedType(tag: DW_TAG_const_type, baseType: !315)
!315 = !DIDerivedType(tag: DW_TAG_typedef, name: "index_cat_info", file: !1, line: 754, baseType: !316)
!316 = !DICompositeType(tag: DW_TAG_structure_type, file: !1, line: 736, size: 320, align: 64, elements: !317)
!317 = !{!318, !319, !320, !321, !322}
!318 = !DIDerivedType(tag: DW_TAG_member, name: "uncompressed_size", scope: !316, file: !1, line: 738, baseType: !62, size: 64, align: 64)
!319 = !DIDerivedType(tag: DW_TAG_member, name: "file_size", scope: !316, file: !1, line: 741, baseType: !62, size: 64, align: 64, offset: 64)
!320 = !DIDerivedType(tag: DW_TAG_member, name: "block_number_add", scope: !316, file: !1, line: 744, baseType: !62, size: 64, align: 64, offset: 128)
!321 = !DIDerivedType(tag: DW_TAG_member, name: "stream_number_add", scope: !316, file: !1, line: 749, baseType: !72, size: 32, align: 32, offset: 192)
!322 = !DIDerivedType(tag: DW_TAG_member, name: "streams", scope: !316, file: !1, line: 752, baseType: !277, size: 64, align: 64, offset: 256)
!323 = distinct !DISubprogram(name: "index_dup_stream", scope: !1, file: !1, line: 880, type: !324, isLocal: true, isDefinition: true, scopeLine: 881, flags: DIFlagPrototyped, isOptimized: false, variables: !160)
!324 = !DISubroutineType(types: !325)
!325 = !{!130, !52, !147}
!326 = distinct !DISubprogram(name: "index_tree_next", scope: !1, file: !1, line: 298, type: !327, isLocal: true, isDefinition: true, scopeLine: 299, flags: DIFlagPrototyped, isOptimized: false, variables: !160)
!327 = !DISubroutineType(types: !328)
!328 = !{!48, !329}
!329 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !330, size: 64, align: 64)
!330 = !DIDerivedType(tag: DW_TAG_const_type, baseType: !58)
!331 = distinct !DISubprogram(name: "iter_set_info", scope: !1, file: !1, line: 997, type: !264, isLocal: true, isDefinition: true, scopeLine: 998, flags: DIFlagPrototyped, isOptimized: false, variables: !160)
!332 = distinct !DISubprogram(name: "index_tree_locate", scope: !1, file: !1, line: 319, type: !333, isLocal: true, isDefinition: true, scopeLine: 320, flags: DIFlagPrototyped, isOptimized: false, variables: !160)
!333 = !DISubroutineType(types: !334)
!334 = !{!48, !335, !62}
!335 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !336, size: 64, align: 64)
!336 = !DIDerivedType(tag: DW_TAG_const_type, baseType: !76)
!337 = !{i32 2, !"Dwarf Version", i32 4}
!338 = !{i32 2, !"Debug Info Version", i32 3}
!339 = !{!"clang version 3.8.0 (tags/RELEASE_380/final)"}
!340 = !DILocalVariable(name: "allocator", arg: 1, scope: !133, file: !1, line: 401, type: !147)
!341 = !DIExpression()
!342 = !DILocation(line: 401, column: 33, scope: !133)
!343 = !DILocalVariable(name: "s", scope: !133, file: !1, line: 403, type: !130)
!344 = !DILocation(line: 403, column: 16, scope: !133)
!345 = !DILocalVariable(name: "i", scope: !133, file: !1, line: 405, type: !136)
!346 = !DILocation(line: 405, column: 14, scope: !133)
!347 = !DILocation(line: 405, column: 35, scope: !133)
!348 = !DILocation(line: 405, column: 18, scope: !133)
!349 = !DILocation(line: 406, column: 6, scope: !350)
!350 = distinct !DILexicalBlock(scope: !133, file: !1, line: 406, column: 6)
!351 = !DILocation(line: 406, column: 8, scope: !350)
!352 = !DILocation(line: 406, column: 6, scope: !133)
!353 = !DILocation(line: 407, column: 3, scope: !350)
!354 = !DILocation(line: 409, column: 36, scope: !133)
!355 = !DILocation(line: 409, column: 6, scope: !133)
!356 = !DILocation(line: 409, column: 4, scope: !133)
!357 = !DILocation(line: 410, column: 6, scope: !358)
!358 = distinct !DILexicalBlock(scope: !133, file: !1, line: 410, column: 6)
!359 = !DILocation(line: 410, column: 8, scope: !358)
!360 = !DILocation(line: 410, column: 6, scope: !133)
!361 = !DILocation(line: 411, column: 13, scope: !362)
!362 = distinct !DILexicalBlock(scope: !358, file: !1, line: 410, column: 17)
!363 = !DILocation(line: 411, column: 16, scope: !362)
!364 = !DILocation(line: 411, column: 3, scope: !362)
!365 = !DILocation(line: 412, column: 3, scope: !362)
!366 = !DILocation(line: 415, column: 21, scope: !133)
!367 = !DILocation(line: 415, column: 24, scope: !133)
!368 = !DILocation(line: 415, column: 34, scope: !133)
!369 = !DILocation(line: 415, column: 37, scope: !133)
!370 = !DILocation(line: 415, column: 2, scope: !133)
!371 = !DILocation(line: 417, column: 9, scope: !133)
!372 = !DILocation(line: 417, column: 2, scope: !133)
!373 = !DILocation(line: 418, column: 1, scope: !133)
!374 = !DILocalVariable(name: "allocator", arg: 1, scope: !273, file: !1, line: 383, type: !147)
!375 = !DILocation(line: 383, column: 34, scope: !273)
!376 = !DILocalVariable(name: "i", scope: !273, file: !1, line: 385, type: !136)
!377 = !DILocation(line: 385, column: 14, scope: !273)
!378 = !DILocation(line: 385, column: 49, scope: !273)
!379 = !DILocation(line: 385, column: 18, scope: !273)
!380 = !DILocation(line: 386, column: 6, scope: !381)
!381 = distinct !DILexicalBlock(scope: !273, file: !1, line: 386, column: 6)
!382 = !DILocation(line: 386, column: 8, scope: !381)
!383 = !DILocation(line: 386, column: 6, scope: !273)
!384 = !DILocation(line: 387, column: 20, scope: !385)
!385 = distinct !DILexicalBlock(scope: !381, file: !1, line: 386, column: 17)
!386 = !DILocation(line: 387, column: 23, scope: !385)
!387 = !DILocation(line: 387, column: 3, scope: !385)
!388 = !DILocation(line: 388, column: 3, scope: !385)
!389 = !DILocation(line: 388, column: 6, scope: !385)
!390 = !DILocation(line: 388, column: 24, scope: !385)
!391 = !DILocation(line: 389, column: 3, scope: !385)
!392 = !DILocation(line: 389, column: 6, scope: !385)
!393 = !DILocation(line: 389, column: 17, scope: !385)
!394 = !DILocation(line: 390, column: 3, scope: !385)
!395 = !DILocation(line: 390, column: 6, scope: !385)
!396 = !DILocation(line: 390, column: 19, scope: !385)
!397 = !DILocation(line: 391, column: 3, scope: !385)
!398 = !DILocation(line: 391, column: 6, scope: !385)
!399 = !DILocation(line: 391, column: 22, scope: !385)
!400 = !DILocation(line: 392, column: 3, scope: !385)
!401 = !DILocation(line: 392, column: 6, scope: !385)
!402 = !DILocation(line: 392, column: 15, scope: !385)
!403 = !DILocation(line: 393, column: 3, scope: !385)
!404 = !DILocation(line: 393, column: 6, scope: !385)
!405 = !DILocation(line: 393, column: 13, scope: !385)
!406 = !DILocation(line: 394, column: 2, scope: !385)
!407 = !DILocation(line: 396, column: 9, scope: !273)
!408 = !DILocation(line: 396, column: 2, scope: !273)
!409 = !DILocalVariable(name: "compressed_base", arg: 1, scope: !278, file: !1, line: 344, type: !62)
!410 = !DILocation(line: 344, column: 28, scope: !278)
!411 = !DILocalVariable(name: "uncompressed_base", arg: 2, scope: !278, file: !1, line: 344, type: !62)
!412 = !DILocation(line: 344, column: 54, scope: !278)
!413 = !DILocalVariable(name: "stream_number", arg: 3, scope: !278, file: !1, line: 345, type: !62)
!414 = !DILocation(line: 345, column: 12, scope: !278)
!415 = !DILocalVariable(name: "block_number_base", arg: 4, scope: !278, file: !1, line: 345, type: !62)
!416 = !DILocation(line: 345, column: 36, scope: !278)
!417 = !DILocalVariable(name: "allocator", arg: 5, scope: !278, file: !1, line: 346, type: !147)
!418 = !DILocation(line: 346, column: 19, scope: !278)
!419 = !DILocalVariable(name: "s", scope: !278, file: !1, line: 348, type: !130)
!420 = !DILocation(line: 348, column: 16, scope: !278)
!421 = !DILocation(line: 348, column: 53, scope: !278)
!422 = !DILocation(line: 348, column: 20, scope: !278)
!423 = !DILocation(line: 349, column: 6, scope: !424)
!424 = distinct !DILexicalBlock(scope: !278, file: !1, line: 349, column: 6)
!425 = !DILocation(line: 349, column: 8, scope: !424)
!426 = !DILocation(line: 349, column: 6, scope: !278)
!427 = !DILocation(line: 350, column: 3, scope: !424)
!428 = !DILocation(line: 352, column: 30, scope: !278)
!429 = !DILocation(line: 352, column: 2, scope: !278)
!430 = !DILocation(line: 352, column: 5, scope: !278)
!431 = !DILocation(line: 352, column: 10, scope: !278)
!432 = !DILocation(line: 352, column: 28, scope: !278)
!433 = !DILocation(line: 353, column: 28, scope: !278)
!434 = !DILocation(line: 353, column: 2, scope: !278)
!435 = !DILocation(line: 353, column: 5, scope: !278)
!436 = !DILocation(line: 353, column: 10, scope: !278)
!437 = !DILocation(line: 353, column: 26, scope: !278)
!438 = !DILocation(line: 354, column: 2, scope: !278)
!439 = !DILocation(line: 354, column: 5, scope: !278)
!440 = !DILocation(line: 354, column: 10, scope: !278)
!441 = !DILocation(line: 354, column: 17, scope: !278)
!442 = !DILocation(line: 355, column: 2, scope: !278)
!443 = !DILocation(line: 355, column: 5, scope: !278)
!444 = !DILocation(line: 355, column: 10, scope: !278)
!445 = !DILocation(line: 355, column: 15, scope: !278)
!446 = !DILocation(line: 356, column: 2, scope: !278)
!447 = !DILocation(line: 356, column: 5, scope: !278)
!448 = !DILocation(line: 356, column: 10, scope: !278)
!449 = !DILocation(line: 356, column: 16, scope: !278)
!450 = !DILocation(line: 358, column: 14, scope: !278)
!451 = !DILocation(line: 358, column: 2, scope: !278)
!452 = !DILocation(line: 358, column: 5, scope: !278)
!453 = !DILocation(line: 358, column: 12, scope: !278)
!454 = !DILocation(line: 359, column: 25, scope: !278)
!455 = !DILocation(line: 359, column: 2, scope: !278)
!456 = !DILocation(line: 359, column: 5, scope: !278)
!457 = !DILocation(line: 359, column: 23, scope: !278)
!458 = !DILocation(line: 361, column: 19, scope: !278)
!459 = !DILocation(line: 361, column: 22, scope: !278)
!460 = !DILocation(line: 361, column: 2, scope: !278)
!461 = !DILocation(line: 363, column: 2, scope: !278)
!462 = !DILocation(line: 363, column: 5, scope: !278)
!463 = !DILocation(line: 363, column: 18, scope: !278)
!464 = !DILocation(line: 364, column: 2, scope: !278)
!465 = !DILocation(line: 364, column: 5, scope: !278)
!466 = !DILocation(line: 364, column: 21, scope: !278)
!467 = !DILocation(line: 365, column: 2, scope: !278)
!468 = !DILocation(line: 365, column: 5, scope: !278)
!469 = !DILocation(line: 365, column: 18, scope: !278)
!470 = !DILocation(line: 365, column: 26, scope: !278)
!471 = !DILocation(line: 366, column: 2, scope: !278)
!472 = !DILocation(line: 366, column: 5, scope: !278)
!473 = !DILocation(line: 366, column: 20, scope: !278)
!474 = !DILocation(line: 368, column: 9, scope: !278)
!475 = !DILocation(line: 368, column: 2, scope: !278)
!476 = !DILocation(line: 369, column: 1, scope: !278)
!477 = !DILocalVariable(name: "tree", arg: 1, scope: !281, file: !1, line: 231, type: !277)
!478 = !DILocation(line: 231, column: 31, scope: !281)
!479 = !DILocalVariable(name: "node", arg: 2, scope: !281, file: !1, line: 231, type: !68)
!480 = !DILocation(line: 231, column: 54, scope: !281)
!481 = !DILocalVariable(name: "up", scope: !281, file: !1, line: 233, type: !72)
!482 = !DILocation(line: 233, column: 11, scope: !281)
!483 = !DILocation(line: 234, column: 17, scope: !281)
!484 = !DILocation(line: 234, column: 23, scope: !281)
!485 = !DILocation(line: 234, column: 2, scope: !281)
!486 = !DILocation(line: 234, column: 8, scope: !281)
!487 = !DILocation(line: 234, column: 15, scope: !281)
!488 = !DILocation(line: 235, column: 2, scope: !281)
!489 = !DILocation(line: 235, column: 8, scope: !281)
!490 = !DILocation(line: 235, column: 13, scope: !281)
!491 = !DILocation(line: 236, column: 2, scope: !281)
!492 = !DILocation(line: 236, column: 8, scope: !281)
!493 = !DILocation(line: 236, column: 14, scope: !281)
!494 = !DILocation(line: 238, column: 4, scope: !281)
!495 = !DILocation(line: 238, column: 10, scope: !281)
!496 = !DILocation(line: 238, column: 2, scope: !281)
!497 = !DILocation(line: 241, column: 6, scope: !498)
!498 = distinct !DILexicalBlock(scope: !281, file: !1, line: 241, column: 6)
!499 = !DILocation(line: 241, column: 12, scope: !498)
!500 = !DILocation(line: 241, column: 17, scope: !498)
!501 = !DILocation(line: 241, column: 6, scope: !281)
!502 = !DILocation(line: 242, column: 16, scope: !503)
!503 = distinct !DILexicalBlock(scope: !498, file: !1, line: 241, column: 26)
!504 = !DILocation(line: 242, column: 3, scope: !503)
!505 = !DILocation(line: 242, column: 9, scope: !503)
!506 = !DILocation(line: 242, column: 14, scope: !503)
!507 = !DILocation(line: 243, column: 20, scope: !503)
!508 = !DILocation(line: 243, column: 3, scope: !503)
!509 = !DILocation(line: 243, column: 9, scope: !503)
!510 = !DILocation(line: 243, column: 18, scope: !503)
!511 = !DILocation(line: 244, column: 21, scope: !503)
!512 = !DILocation(line: 244, column: 3, scope: !503)
!513 = !DILocation(line: 244, column: 9, scope: !503)
!514 = !DILocation(line: 244, column: 19, scope: !503)
!515 = !DILocation(line: 245, column: 3, scope: !503)
!516 = !DILocation(line: 249, column: 2, scope: !281)
!517 = !DILocation(line: 249, column: 2, scope: !518)
!518 = !DILexicalBlockFile(scope: !281, file: !1, discriminator: 1)
!519 = !DILocation(line: 249, column: 2, scope: !520)
!520 = !DILexicalBlockFile(scope: !281, file: !1, discriminator: 2)
!521 = !DILocation(line: 249, column: 2, scope: !522)
!522 = !DILexicalBlockFile(scope: !281, file: !1, discriminator: 3)
!523 = !DILocation(line: 250, column: 2, scope: !281)
!524 = !DILocation(line: 250, column: 2, scope: !518)
!525 = !DILocation(line: 250, column: 2, scope: !520)
!526 = !DILocation(line: 250, column: 2, scope: !522)
!527 = !DILocation(line: 254, column: 27, scope: !281)
!528 = !DILocation(line: 254, column: 2, scope: !281)
!529 = !DILocation(line: 254, column: 8, scope: !281)
!530 = !DILocation(line: 254, column: 19, scope: !281)
!531 = !DILocation(line: 254, column: 25, scope: !281)
!532 = !DILocation(line: 255, column: 20, scope: !281)
!533 = !DILocation(line: 255, column: 2, scope: !281)
!534 = !DILocation(line: 255, column: 8, scope: !281)
!535 = !DILocation(line: 255, column: 18, scope: !281)
!536 = !DILocation(line: 262, column: 7, scope: !281)
!537 = !DILocation(line: 262, column: 13, scope: !281)
!538 = !DILocation(line: 262, column: 43, scope: !281)
!539 = !DILocation(line: 262, column: 49, scope: !281)
!540 = !DILocation(line: 262, column: 37, scope: !281)
!541 = !DILocation(line: 262, column: 34, scope: !281)
!542 = !DILocation(line: 262, column: 19, scope: !281)
!543 = !DILocation(line: 262, column: 5, scope: !281)
!544 = !DILocation(line: 263, column: 6, scope: !545)
!545 = distinct !DILexicalBlock(scope: !281, file: !1, line: 263, column: 6)
!546 = !DILocation(line: 263, column: 9, scope: !545)
!547 = !DILocation(line: 263, column: 6, scope: !281)
!548 = !DILocalVariable(name: "pivot", scope: !549, file: !1, line: 264, type: !68)
!549 = distinct !DILexicalBlock(scope: !545, file: !1, line: 263, column: 15)
!550 = !DILocation(line: 264, column: 20, scope: !549)
!551 = !DILocation(line: 267, column: 14, scope: !549)
!552 = !DILocation(line: 267, column: 20, scope: !549)
!553 = !DILocation(line: 267, column: 8, scope: !549)
!554 = !DILocation(line: 267, column: 27, scope: !549)
!555 = !DILocation(line: 267, column: 6, scope: !549)
!556 = !DILocation(line: 268, column: 3, scope: !549)
!557 = !DILocation(line: 269, column: 11, scope: !558)
!558 = distinct !DILexicalBlock(scope: !549, file: !1, line: 268, column: 6)
!559 = !DILocation(line: 269, column: 17, scope: !558)
!560 = !DILocation(line: 269, column: 9, scope: !558)
!561 = !DILocation(line: 270, column: 3, scope: !558)
!562 = !DILocation(line: 270, column: 12, scope: !563)
!563 = !DILexicalBlockFile(scope: !549, file: !1, discriminator: 1)
!564 = !DILocation(line: 270, column: 17, scope: !563)
!565 = !DILocation(line: 270, column: 3, scope: !563)
!566 = !DILocation(line: 273, column: 11, scope: !549)
!567 = !DILocation(line: 273, column: 17, scope: !549)
!568 = !DILocation(line: 273, column: 9, scope: !549)
!569 = !DILocation(line: 275, column: 7, scope: !570)
!570 = distinct !DILexicalBlock(scope: !549, file: !1, line: 275, column: 7)
!571 = !DILocation(line: 275, column: 13, scope: !570)
!572 = !DILocation(line: 275, column: 20, scope: !570)
!573 = !DILocation(line: 275, column: 7, scope: !549)
!574 = !DILocation(line: 276, column: 17, scope: !575)
!575 = distinct !DILexicalBlock(scope: !570, file: !1, line: 275, column: 29)
!576 = !DILocation(line: 276, column: 4, scope: !575)
!577 = !DILocation(line: 276, column: 10, scope: !575)
!578 = !DILocation(line: 276, column: 15, scope: !575)
!579 = !DILocation(line: 277, column: 3, scope: !575)
!580 = !DILocation(line: 278, column: 4, scope: !581)
!581 = distinct !DILexicalBlock(scope: !570, file: !1, line: 277, column: 10)
!582 = !DILocation(line: 278, column: 4, scope: !583)
!583 = !DILexicalBlockFile(scope: !581, file: !1, discriminator: 1)
!584 = !DILocation(line: 278, column: 4, scope: !585)
!585 = !DILexicalBlockFile(scope: !581, file: !1, discriminator: 2)
!586 = !DILocation(line: 278, column: 4, scope: !587)
!587 = !DILexicalBlockFile(scope: !581, file: !1, discriminator: 3)
!588 = !DILocation(line: 279, column: 26, scope: !581)
!589 = !DILocation(line: 279, column: 4, scope: !581)
!590 = !DILocation(line: 279, column: 10, scope: !581)
!591 = !DILocation(line: 279, column: 18, scope: !581)
!592 = !DILocation(line: 279, column: 24, scope: !581)
!593 = !DILocation(line: 282, column: 19, scope: !549)
!594 = !DILocation(line: 282, column: 25, scope: !549)
!595 = !DILocation(line: 282, column: 3, scope: !549)
!596 = !DILocation(line: 282, column: 10, scope: !549)
!597 = !DILocation(line: 282, column: 17, scope: !549)
!598 = !DILocation(line: 284, column: 17, scope: !549)
!599 = !DILocation(line: 284, column: 24, scope: !549)
!600 = !DILocation(line: 284, column: 3, scope: !549)
!601 = !DILocation(line: 284, column: 9, scope: !549)
!602 = !DILocation(line: 284, column: 15, scope: !549)
!603 = !DILocation(line: 285, column: 7, scope: !604)
!604 = distinct !DILexicalBlock(scope: !549, file: !1, line: 285, column: 7)
!605 = !DILocation(line: 285, column: 13, scope: !604)
!606 = !DILocation(line: 285, column: 19, scope: !604)
!607 = !DILocation(line: 285, column: 7, scope: !549)
!608 = !DILocation(line: 286, column: 26, scope: !604)
!609 = !DILocation(line: 286, column: 4, scope: !604)
!610 = !DILocation(line: 286, column: 10, scope: !604)
!611 = !DILocation(line: 286, column: 17, scope: !604)
!612 = !DILocation(line: 286, column: 24, scope: !604)
!613 = !DILocation(line: 288, column: 17, scope: !549)
!614 = !DILocation(line: 288, column: 3, scope: !549)
!615 = !DILocation(line: 288, column: 10, scope: !549)
!616 = !DILocation(line: 288, column: 15, scope: !549)
!617 = !DILocation(line: 289, column: 18, scope: !549)
!618 = !DILocation(line: 289, column: 3, scope: !549)
!619 = !DILocation(line: 289, column: 9, scope: !549)
!620 = !DILocation(line: 289, column: 16, scope: !549)
!621 = !DILocation(line: 290, column: 2, scope: !549)
!622 = !DILocation(line: 292, column: 2, scope: !281)
!623 = !DILocation(line: 293, column: 1, scope: !281)
!624 = !DILocalVariable(name: "i", arg: 1, scope: !161, file: !1, line: 422, type: !136)
!625 = !DILocation(line: 422, column: 28, scope: !161)
!626 = !DILocalVariable(name: "allocator", arg: 2, scope: !161, file: !1, line: 422, type: !147)
!627 = !DILocation(line: 422, column: 47, scope: !161)
!628 = !DILocation(line: 426, column: 6, scope: !629)
!629 = distinct !DILexicalBlock(scope: !161, file: !1, line: 426, column: 6)
!630 = !DILocation(line: 426, column: 8, scope: !629)
!631 = !DILocation(line: 426, column: 6, scope: !161)
!632 = !DILocation(line: 427, column: 19, scope: !633)
!633 = distinct !DILexicalBlock(scope: !629, file: !1, line: 426, column: 17)
!634 = !DILocation(line: 427, column: 22, scope: !633)
!635 = !DILocation(line: 427, column: 31, scope: !633)
!636 = !DILocation(line: 427, column: 3, scope: !633)
!637 = !DILocation(line: 428, column: 13, scope: !633)
!638 = !DILocation(line: 428, column: 16, scope: !633)
!639 = !DILocation(line: 428, column: 3, scope: !633)
!640 = !DILocation(line: 429, column: 2, scope: !633)
!641 = !DILocation(line: 431, column: 2, scope: !161)
!642 = !DILocalVariable(name: "tree", arg: 1, scope: !289, file: !1, line: 218, type: !277)
!643 = !DILocation(line: 218, column: 28, scope: !289)
!644 = !DILocalVariable(name: "allocator", arg: 2, scope: !289, file: !1, line: 218, type: !147)
!645 = !DILocation(line: 218, column: 50, scope: !289)
!646 = !DILocalVariable(name: "free_func", arg: 3, scope: !289, file: !1, line: 219, type: !292)
!647 = !DILocation(line: 219, column: 10, scope: !289)
!648 = !DILocation(line: 221, column: 6, scope: !649)
!649 = distinct !DILexicalBlock(scope: !289, file: !1, line: 221, column: 6)
!650 = !DILocation(line: 221, column: 12, scope: !649)
!651 = !DILocation(line: 221, column: 17, scope: !649)
!652 = !DILocation(line: 221, column: 6, scope: !289)
!653 = !DILocation(line: 222, column: 23, scope: !649)
!654 = !DILocation(line: 222, column: 29, scope: !649)
!655 = !DILocation(line: 222, column: 35, scope: !649)
!656 = !DILocation(line: 222, column: 46, scope: !649)
!657 = !DILocation(line: 222, column: 3, scope: !649)
!658 = !DILocation(line: 224, column: 2, scope: !289)
!659 = !DILocalVariable(name: "node", arg: 1, scope: !298, file: !1, line: 374, type: !48)
!660 = !DILocation(line: 374, column: 24, scope: !298)
!661 = !DILocalVariable(name: "allocator", arg: 2, scope: !298, file: !1, line: 374, type: !147)
!662 = !DILocation(line: 374, column: 46, scope: !298)
!663 = !DILocalVariable(name: "s", scope: !298, file: !1, line: 376, type: !130)
!664 = !DILocation(line: 376, column: 16, scope: !298)
!665 = !DILocation(line: 376, column: 20, scope: !298)
!666 = !DILocation(line: 377, column: 18, scope: !298)
!667 = !DILocation(line: 377, column: 21, scope: !298)
!668 = !DILocation(line: 377, column: 29, scope: !298)
!669 = !DILocation(line: 377, column: 2, scope: !298)
!670 = !DILocation(line: 378, column: 2, scope: !298)
!671 = !DILocalVariable(name: "i", arg: 1, scope: !164, file: !1, line: 436, type: !136)
!672 = !DILocation(line: 436, column: 33, scope: !164)
!673 = !DILocalVariable(name: "records", arg: 2, scope: !164, file: !1, line: 436, type: !62)
!674 = !DILocation(line: 436, column: 45, scope: !164)
!675 = !DILocation(line: 438, column: 6, scope: !676)
!676 = distinct !DILexicalBlock(scope: !164, file: !1, line: 438, column: 6)
!677 = !DILocation(line: 438, column: 14, scope: !676)
!678 = !DILocation(line: 438, column: 6, scope: !164)
!679 = !DILocation(line: 439, column: 11, scope: !676)
!680 = !DILocation(line: 439, column: 3, scope: !676)
!681 = !DILocation(line: 441, column: 25, scope: !164)
!682 = !DILocation(line: 441, column: 2, scope: !164)
!683 = !DILocation(line: 441, column: 5, scope: !164)
!684 = !DILocation(line: 441, column: 14, scope: !164)
!685 = !DILocation(line: 442, column: 2, scope: !164)
!686 = !DILocalVariable(name: "streams", arg: 1, scope: !167, file: !1, line: 447, type: !62)
!687 = !DILocation(line: 447, column: 30, scope: !167)
!688 = !DILocalVariable(name: "blocks", arg: 2, scope: !167, file: !1, line: 447, type: !62)
!689 = !DILocation(line: 447, column: 48, scope: !167)
!690 = !DILocalVariable(name: "alloc_overhead", scope: !167, file: !1, line: 456, type: !691)
!691 = !DIDerivedType(tag: DW_TAG_const_type, baseType: !49)
!692 = !DILocation(line: 456, column: 15, scope: !167)
!693 = !DILocalVariable(name: "stream_base", scope: !167, file: !1, line: 461, type: !691)
!694 = !DILocation(line: 461, column: 15, scope: !167)
!695 = !DILocalVariable(name: "group_base", scope: !167, file: !1, line: 465, type: !691)
!696 = !DILocation(line: 465, column: 15, scope: !167)
!697 = !DILocalVariable(name: "groups", scope: !167, file: !1, line: 471, type: !698)
!698 = !DIDerivedType(tag: DW_TAG_const_type, baseType: !62)
!699 = !DILocation(line: 471, column: 17, scope: !167)
!700 = !DILocation(line: 472, column: 7, scope: !167)
!701 = !DILocation(line: 472, column: 14, scope: !167)
!702 = !DILocation(line: 472, column: 33, scope: !167)
!703 = !DILocation(line: 472, column: 38, scope: !167)
!704 = !DILocalVariable(name: "streams_mem", scope: !167, file: !1, line: 475, type: !705)
!705 = !DIDerivedType(tag: DW_TAG_const_type, baseType: !64)
!706 = !DILocation(line: 475, column: 17, scope: !167)
!707 = !DILocation(line: 475, column: 31, scope: !167)
!708 = !DILocation(line: 475, column: 39, scope: !167)
!709 = !DILocalVariable(name: "groups_mem", scope: !167, file: !1, line: 476, type: !705)
!710 = !DILocation(line: 476, column: 17, scope: !167)
!711 = !DILocation(line: 476, column: 30, scope: !167)
!712 = !DILocation(line: 476, column: 37, scope: !167)
!713 = !DILocalVariable(name: "index_base", scope: !167, file: !1, line: 479, type: !705)
!714 = !DILocation(line: 479, column: 17, scope: !167)
!715 = !DILocalVariable(name: "limit", scope: !167, file: !1, line: 484, type: !705)
!716 = !DILocation(line: 484, column: 17, scope: !167)
!717 = !DILocation(line: 485, column: 6, scope: !718)
!718 = distinct !DILexicalBlock(scope: !167, file: !1, line: 485, column: 6)
!719 = !DILocation(line: 485, column: 14, scope: !718)
!720 = !DILocation(line: 485, column: 19, scope: !718)
!721 = !DILocation(line: 485, column: 22, scope: !722)
!722 = !DILexicalBlockFile(scope: !718, file: !1, discriminator: 1)
!723 = !DILocation(line: 485, column: 30, scope: !722)
!724 = !DILocation(line: 485, column: 43, scope: !722)
!725 = !DILocation(line: 485, column: 46, scope: !726)
!726 = !DILexicalBlockFile(scope: !718, file: !1, discriminator: 2)
!727 = !DILocation(line: 485, column: 53, scope: !726)
!728 = !DILocation(line: 486, column: 4, scope: !718)
!729 = !DILocation(line: 486, column: 7, scope: !722)
!730 = !DILocation(line: 486, column: 15, scope: !722)
!731 = !DILocation(line: 487, column: 4, scope: !718)
!732 = !DILocation(line: 487, column: 7, scope: !722)
!733 = !DILocation(line: 487, column: 14, scope: !722)
!734 = !DILocation(line: 488, column: 4, scope: !718)
!735 = !DILocation(line: 488, column: 15, scope: !722)
!736 = !DILocation(line: 488, column: 13, scope: !722)
!737 = !DILocation(line: 488, column: 29, scope: !722)
!738 = !DILocation(line: 488, column: 27, scope: !722)
!739 = !DILocation(line: 485, column: 6, scope: !740)
!740 = !DILexicalBlockFile(scope: !167, file: !1, discriminator: 3)
!741 = !DILocation(line: 489, column: 3, scope: !718)
!742 = !DILocation(line: 491, column: 22, scope: !167)
!743 = !DILocation(line: 491, column: 20, scope: !167)
!744 = !DILocation(line: 491, column: 36, scope: !167)
!745 = !DILocation(line: 491, column: 34, scope: !167)
!746 = !DILocation(line: 491, column: 2, scope: !167)
!747 = !DILocation(line: 492, column: 1, scope: !167)
!748 = !DILocalVariable(name: "i", arg: 1, scope: !170, file: !1, line: 496, type: !173)
!749 = !DILocation(line: 496, column: 38, scope: !170)
!750 = !DILocation(line: 498, column: 29, scope: !170)
!751 = !DILocation(line: 498, column: 32, scope: !170)
!752 = !DILocation(line: 498, column: 40, scope: !170)
!753 = !DILocation(line: 498, column: 47, scope: !170)
!754 = !DILocation(line: 498, column: 50, scope: !170)
!755 = !DILocation(line: 498, column: 9, scope: !170)
!756 = !DILocation(line: 498, column: 2, scope: !170)
!757 = !DILocalVariable(name: "i", arg: 1, scope: !175, file: !1, line: 503, type: !173)
!758 = !DILocation(line: 503, column: 42, scope: !175)
!759 = !DILocation(line: 505, column: 9, scope: !175)
!760 = !DILocation(line: 505, column: 12, scope: !175)
!761 = !DILocation(line: 505, column: 2, scope: !175)
!762 = !DILocalVariable(name: "i", arg: 1, scope: !178, file: !1, line: 510, type: !173)
!763 = !DILocation(line: 510, column: 43, scope: !178)
!764 = !DILocation(line: 512, column: 9, scope: !178)
!765 = !DILocation(line: 512, column: 12, scope: !178)
!766 = !DILocation(line: 512, column: 20, scope: !178)
!767 = !DILocation(line: 512, column: 2, scope: !178)
!768 = !DILocalVariable(name: "i", arg: 1, scope: !179, file: !1, line: 517, type: !173)
!769 = !DILocation(line: 517, column: 35, scope: !179)
!770 = !DILocation(line: 519, column: 20, scope: !179)
!771 = !DILocation(line: 519, column: 23, scope: !179)
!772 = !DILocation(line: 519, column: 37, scope: !179)
!773 = !DILocation(line: 519, column: 40, scope: !179)
!774 = !DILocation(line: 519, column: 9, scope: !179)
!775 = !DILocation(line: 519, column: 2, scope: !179)
!776 = !DILocalVariable(name: "count", arg: 1, scope: !299, file: !300, line: 57, type: !62)
!777 = !DILocation(line: 57, column: 21, scope: !299)
!778 = !DILocalVariable(name: "index_list_size", arg: 2, scope: !299, file: !300, line: 57, type: !62)
!779 = !DILocation(line: 57, column: 37, scope: !299)
!780 = !DILocation(line: 59, column: 39, scope: !299)
!781 = !DILocation(line: 59, column: 46, scope: !299)
!782 = !DILocation(line: 59, column: 19, scope: !299)
!783 = !DILocation(line: 59, column: 9, scope: !784)
!784 = !DILexicalBlockFile(scope: !299, file: !300, discriminator: 1)
!785 = !DILocation(line: 59, column: 2, scope: !299)
!786 = !DILocalVariable(name: "i", arg: 1, scope: !180, file: !1, line: 524, type: !173)
!787 = !DILocation(line: 524, column: 41, scope: !180)
!788 = !DILocation(line: 526, column: 9, scope: !180)
!789 = !DILocation(line: 526, column: 12, scope: !180)
!790 = !DILocation(line: 526, column: 2, scope: !180)
!791 = !DILocalVariable(name: "i", arg: 1, scope: !181, file: !1, line: 531, type: !173)
!792 = !DILocation(line: 531, column: 42, scope: !181)
!793 = !DILocation(line: 534, column: 35, scope: !181)
!794 = !DILocation(line: 534, column: 38, scope: !181)
!795 = !DILocation(line: 534, column: 33, scope: !181)
!796 = !DILocation(line: 535, column: 17, scope: !181)
!797 = !DILocation(line: 535, column: 20, scope: !181)
!798 = !DILocation(line: 535, column: 34, scope: !181)
!799 = !DILocation(line: 535, column: 37, scope: !181)
!800 = !DILocation(line: 535, column: 6, scope: !181)
!801 = !DILocation(line: 535, column: 4, scope: !181)
!802 = !DILocation(line: 536, column: 4, scope: !181)
!803 = !DILocation(line: 534, column: 2, scope: !181)
!804 = !DILocalVariable(name: "i", arg: 1, scope: !182, file: !1, line: 565, type: !173)
!805 = !DILocation(line: 565, column: 40, scope: !182)
!806 = !DILocalVariable(name: "s", scope: !182, file: !1, line: 567, type: !52)
!807 = !DILocation(line: 567, column: 22, scope: !182)
!808 = !DILocation(line: 567, column: 49, scope: !182)
!809 = !DILocation(line: 567, column: 52, scope: !182)
!810 = !DILocation(line: 567, column: 60, scope: !182)
!811 = !DILocation(line: 567, column: 26, scope: !182)
!812 = !DILocalVariable(name: "g", scope: !182, file: !1, line: 568, type: !112)
!813 = !DILocation(line: 568, column: 21, scope: !182)
!814 = !DILocation(line: 568, column: 47, scope: !182)
!815 = !DILocation(line: 568, column: 50, scope: !182)
!816 = !DILocation(line: 568, column: 57, scope: !182)
!817 = !DILocation(line: 568, column: 25, scope: !182)
!818 = !DILocation(line: 569, column: 25, scope: !182)
!819 = !DILocation(line: 569, column: 28, scope: !182)
!820 = !DILocation(line: 569, column: 33, scope: !182)
!821 = !DILocation(line: 570, column: 4, scope: !182)
!822 = !DILocation(line: 570, column: 6, scope: !182)
!823 = !DILocation(line: 570, column: 4, scope: !824)
!824 = !DILexicalBlockFile(scope: !182, file: !1, discriminator: 1)
!825 = !DILocation(line: 570, column: 31, scope: !826)
!826 = !DILexicalBlockFile(scope: !182, file: !1, discriminator: 2)
!827 = !DILocation(line: 570, column: 34, scope: !826)
!828 = !DILocation(line: 570, column: 20, scope: !826)
!829 = !DILocation(line: 570, column: 23, scope: !826)
!830 = !DILocation(line: 570, column: 40, scope: !826)
!831 = !DILocation(line: 570, column: 4, scope: !826)
!832 = !DILocation(line: 570, column: 4, scope: !833)
!833 = !DILexicalBlockFile(scope: !182, file: !1, discriminator: 3)
!834 = !DILocation(line: 571, column: 4, scope: !182)
!835 = !DILocation(line: 571, column: 7, scope: !182)
!836 = !DILocation(line: 571, column: 21, scope: !182)
!837 = !DILocation(line: 571, column: 24, scope: !182)
!838 = !DILocation(line: 572, column: 4, scope: !182)
!839 = !DILocation(line: 572, column: 7, scope: !182)
!840 = !DILocation(line: 569, column: 9, scope: !824)
!841 = !DILocation(line: 569, column: 2, scope: !824)
!842 = !DILocalVariable(name: "compressed_base", arg: 1, scope: !303, file: !1, line: 541, type: !62)
!843 = !DILocation(line: 541, column: 26, scope: !303)
!844 = !DILocalVariable(name: "unpadded_sum", arg: 2, scope: !303, file: !1, line: 541, type: !62)
!845 = !DILocation(line: 541, column: 52, scope: !303)
!846 = !DILocalVariable(name: "record_count", arg: 3, scope: !303, file: !1, line: 542, type: !62)
!847 = !DILocation(line: 542, column: 12, scope: !303)
!848 = !DILocalVariable(name: "index_list_size", arg: 4, scope: !303, file: !1, line: 542, type: !62)
!849 = !DILocation(line: 542, column: 35, scope: !303)
!850 = !DILocalVariable(name: "stream_padding", arg: 5, scope: !303, file: !1, line: 543, type: !62)
!851 = !DILocation(line: 543, column: 12, scope: !303)
!852 = !DILocalVariable(name: "file_size", scope: !303, file: !1, line: 550, type: !62)
!853 = !DILocation(line: 550, column: 11, scope: !303)
!854 = !DILocation(line: 550, column: 23, scope: !303)
!855 = !DILocation(line: 550, column: 39, scope: !303)
!856 = !DILocation(line: 551, column: 6, scope: !303)
!857 = !DILocation(line: 551, column: 4, scope: !303)
!858 = !DILocation(line: 551, column: 33, scope: !303)
!859 = !DILocation(line: 551, column: 23, scope: !303)
!860 = !DILocation(line: 551, column: 21, scope: !303)
!861 = !DILocation(line: 552, column: 6, scope: !862)
!862 = distinct !DILexicalBlock(scope: !303, file: !1, line: 552, column: 6)
!863 = !DILocation(line: 552, column: 16, scope: !862)
!864 = !DILocation(line: 552, column: 6, scope: !303)
!865 = !DILocation(line: 553, column: 3, scope: !862)
!866 = !DILocation(line: 556, column: 26, scope: !303)
!867 = !DILocation(line: 556, column: 40, scope: !303)
!868 = !DILocation(line: 556, column: 15, scope: !303)
!869 = !DILocation(line: 556, column: 12, scope: !303)
!870 = !DILocation(line: 557, column: 6, scope: !871)
!871 = distinct !DILexicalBlock(scope: !303, file: !1, line: 557, column: 6)
!872 = !DILocation(line: 557, column: 16, scope: !871)
!873 = !DILocation(line: 557, column: 6, scope: !303)
!874 = !DILocation(line: 558, column: 3, scope: !871)
!875 = !DILocation(line: 560, column: 9, scope: !303)
!876 = !DILocation(line: 560, column: 2, scope: !303)
!877 = !DILocation(line: 561, column: 1, scope: !303)
!878 = !DILocalVariable(name: "i", arg: 1, scope: !183, file: !1, line: 577, type: !173)
!879 = !DILocation(line: 577, column: 48, scope: !183)
!880 = !DILocation(line: 579, column: 9, scope: !183)
!881 = !DILocation(line: 579, column: 12, scope: !183)
!882 = !DILocation(line: 579, column: 2, scope: !183)
!883 = !DILocalVariable(name: "i", arg: 1, scope: !184, file: !1, line: 584, type: !173)
!884 = !DILocation(line: 584, column: 37, scope: !184)
!885 = !DILocalVariable(name: "checks", scope: !184, file: !1, line: 586, type: !72)
!886 = !DILocation(line: 586, column: 11, scope: !184)
!887 = !DILocation(line: 586, column: 20, scope: !184)
!888 = !DILocation(line: 586, column: 23, scope: !184)
!889 = !DILocalVariable(name: "s", scope: !184, file: !1, line: 589, type: !52)
!890 = !DILocation(line: 589, column: 22, scope: !184)
!891 = !DILocation(line: 589, column: 49, scope: !184)
!892 = !DILocation(line: 589, column: 52, scope: !184)
!893 = !DILocation(line: 589, column: 60, scope: !184)
!894 = !DILocation(line: 589, column: 26, scope: !184)
!895 = !DILocation(line: 590, column: 6, scope: !896)
!896 = distinct !DILexicalBlock(scope: !184, file: !1, line: 590, column: 6)
!897 = !DILocation(line: 590, column: 9, scope: !896)
!898 = !DILocation(line: 590, column: 22, scope: !896)
!899 = !DILocation(line: 590, column: 30, scope: !896)
!900 = !DILocation(line: 590, column: 6, scope: !184)
!901 = !DILocation(line: 591, column: 28, scope: !896)
!902 = !DILocation(line: 591, column: 31, scope: !896)
!903 = !DILocation(line: 591, column: 44, scope: !896)
!904 = !DILocation(line: 591, column: 25, scope: !896)
!905 = !DILocation(line: 591, column: 10, scope: !896)
!906 = !DILocation(line: 591, column: 3, scope: !896)
!907 = !DILocation(line: 593, column: 9, scope: !184)
!908 = !DILocation(line: 593, column: 2, scope: !184)
!909 = !DILocalVariable(name: "i", arg: 1, scope: !187, file: !1, line: 598, type: !173)
!910 = !DILocation(line: 598, column: 43, scope: !187)
!911 = !DILocation(line: 601, column: 4, scope: !187)
!912 = !DILocation(line: 601, column: 7, scope: !187)
!913 = !DILocation(line: 601, column: 21, scope: !187)
!914 = !DILocation(line: 601, column: 24, scope: !187)
!915 = !DILocation(line: 600, column: 26, scope: !187)
!916 = !DILocation(line: 600, column: 24, scope: !187)
!917 = !DILocation(line: 601, column: 42, scope: !187)
!918 = !DILocation(line: 600, column: 9, scope: !187)
!919 = !DILocation(line: 600, column: 2, scope: !187)
!920 = !DILocalVariable(name: "count", arg: 1, scope: !306, file: !300, line: 48, type: !62)
!921 = !DILocation(line: 48, column: 30, scope: !306)
!922 = !DILocalVariable(name: "index_list_size", arg: 2, scope: !306, file: !300, line: 48, type: !62)
!923 = !DILocation(line: 48, column: 46, scope: !306)
!924 = !DILocation(line: 51, column: 27, scope: !306)
!925 = !DILocation(line: 51, column: 13, scope: !306)
!926 = !DILocation(line: 51, column: 11, scope: !306)
!927 = !DILocation(line: 51, column: 9, scope: !306)
!928 = !DILocation(line: 51, column: 36, scope: !306)
!929 = !DILocation(line: 51, column: 34, scope: !306)
!930 = !DILocation(line: 51, column: 52, scope: !306)
!931 = !DILocation(line: 51, column: 2, scope: !306)
!932 = !DILocalVariable(name: "i", arg: 1, scope: !188, file: !1, line: 606, type: !136)
!933 = !DILocation(line: 606, column: 37, scope: !188)
!934 = !DILocalVariable(name: "stream_flags", arg: 2, scope: !188, file: !1, line: 606, type: !192)
!935 = !DILocation(line: 606, column: 65, scope: !188)
!936 = !DILocalVariable(name: "s", scope: !188, file: !1, line: 608, type: !130)
!937 = !DILocation(line: 608, column: 16, scope: !188)
!938 = !DILocation(line: 610, column: 6, scope: !939)
!939 = distinct !DILexicalBlock(scope: !188, file: !1, line: 610, column: 6)
!940 = !DILocation(line: 610, column: 8, scope: !939)
!941 = !DILocation(line: 610, column: 16, scope: !939)
!942 = !DILocation(line: 610, column: 19, scope: !943)
!943 = !DILexicalBlockFile(scope: !939, file: !1, discriminator: 1)
!944 = !DILocation(line: 610, column: 32, scope: !943)
!945 = !DILocation(line: 610, column: 6, scope: !943)
!946 = !DILocation(line: 611, column: 3, scope: !939)
!947 = !DILocation(line: 614, column: 2, scope: !188)
!948 = !DILocalVariable(name: "ret_", scope: !949, file: !1, line: 614, type: !950)
!949 = distinct !DILexicalBlock(scope: !188, file: !1, line: 614, column: 2)
!950 = !DIDerivedType(tag: DW_TAG_const_type, baseType: !191)
!951 = !DILocation(line: 614, column: 2, scope: !949)
!952 = !DILocation(line: 614, column: 2, scope: !953)
!953 = !DILexicalBlockFile(scope: !949, file: !1, discriminator: 1)
!954 = !DILocation(line: 614, column: 2, scope: !955)
!955 = !DILexicalBlockFile(scope: !956, file: !1, discriminator: 2)
!956 = distinct !DILexicalBlock(scope: !949, file: !1, line: 614, column: 2)
!957 = !DILocation(line: 614, column: 2, scope: !958)
!958 = !DILexicalBlockFile(scope: !949, file: !1, discriminator: 3)
!959 = !DILocation(line: 617, column: 23, scope: !188)
!960 = !DILocation(line: 617, column: 26, scope: !188)
!961 = !DILocation(line: 617, column: 34, scope: !188)
!962 = !DILocation(line: 617, column: 6, scope: !188)
!963 = !DILocation(line: 617, column: 4, scope: !188)
!964 = !DILocation(line: 618, column: 2, scope: !188)
!965 = !DILocation(line: 618, column: 5, scope: !188)
!966 = !DILocation(line: 618, column: 21, scope: !188)
!967 = !DILocation(line: 618, column: 20, scope: !188)
!968 = !DILocation(line: 620, column: 2, scope: !188)
!969 = !DILocation(line: 621, column: 1, scope: !188)
!970 = !DILocalVariable(name: "i", arg: 1, scope: !194, file: !1, line: 625, type: !136)
!971 = !DILocation(line: 625, column: 39, scope: !194)
!972 = !DILocalVariable(name: "stream_padding", arg: 2, scope: !194, file: !1, line: 625, type: !62)
!973 = !DILocation(line: 625, column: 51, scope: !194)
!974 = !DILocalVariable(name: "s", scope: !194, file: !1, line: 627, type: !130)
!975 = !DILocation(line: 627, column: 16, scope: !194)
!976 = !DILocalVariable(name: "old_stream_padding", scope: !194, file: !1, line: 628, type: !62)
!977 = !DILocation(line: 628, column: 11, scope: !194)
!978 = !DILocation(line: 630, column: 6, scope: !979)
!979 = distinct !DILexicalBlock(scope: !194, file: !1, line: 630, column: 6)
!980 = !DILocation(line: 630, column: 8, scope: !979)
!981 = !DILocation(line: 630, column: 16, scope: !979)
!982 = !DILocation(line: 630, column: 19, scope: !983)
!983 = !DILexicalBlockFile(scope: !979, file: !1, discriminator: 1)
!984 = !DILocation(line: 630, column: 34, scope: !983)
!985 = !DILocation(line: 631, column: 4, scope: !979)
!986 = !DILocation(line: 631, column: 8, scope: !983)
!987 = !DILocation(line: 631, column: 23, scope: !983)
!988 = !DILocation(line: 631, column: 28, scope: !983)
!989 = !DILocation(line: 630, column: 6, scope: !990)
!990 = !DILexicalBlockFile(scope: !194, file: !1, discriminator: 2)
!991 = !DILocation(line: 632, column: 3, scope: !979)
!992 = !DILocation(line: 634, column: 23, scope: !194)
!993 = !DILocation(line: 634, column: 26, scope: !194)
!994 = !DILocation(line: 634, column: 34, scope: !194)
!995 = !DILocation(line: 634, column: 6, scope: !194)
!996 = !DILocation(line: 634, column: 4, scope: !194)
!997 = !DILocation(line: 637, column: 23, scope: !194)
!998 = !DILocation(line: 637, column: 26, scope: !194)
!999 = !DILocation(line: 637, column: 21, scope: !194)
!1000 = !DILocation(line: 638, column: 2, scope: !194)
!1001 = !DILocation(line: 638, column: 5, scope: !194)
!1002 = !DILocation(line: 638, column: 20, scope: !194)
!1003 = !DILocation(line: 639, column: 27, scope: !1004)
!1004 = distinct !DILexicalBlock(scope: !194, file: !1, line: 639, column: 6)
!1005 = !DILocation(line: 639, column: 6, scope: !1004)
!1006 = !DILocation(line: 639, column: 32, scope: !1004)
!1007 = !DILocation(line: 639, column: 30, scope: !1004)
!1008 = !DILocation(line: 639, column: 47, scope: !1004)
!1009 = !DILocation(line: 639, column: 6, scope: !194)
!1010 = !DILocation(line: 640, column: 23, scope: !1011)
!1011 = distinct !DILexicalBlock(scope: !1004, file: !1, line: 639, column: 63)
!1012 = !DILocation(line: 640, column: 3, scope: !1011)
!1013 = !DILocation(line: 640, column: 6, scope: !1011)
!1014 = !DILocation(line: 640, column: 21, scope: !1011)
!1015 = !DILocation(line: 641, column: 3, scope: !1011)
!1016 = !DILocation(line: 644, column: 22, scope: !194)
!1017 = !DILocation(line: 644, column: 2, scope: !194)
!1018 = !DILocation(line: 644, column: 5, scope: !194)
!1019 = !DILocation(line: 644, column: 20, scope: !194)
!1020 = !DILocation(line: 645, column: 2, scope: !194)
!1021 = !DILocation(line: 646, column: 1, scope: !194)
!1022 = !DILocalVariable(name: "i", arg: 1, scope: !197, file: !1, line: 650, type: !136)
!1023 = !DILocation(line: 650, column: 31, scope: !197)
!1024 = !DILocalVariable(name: "allocator", arg: 2, scope: !197, file: !1, line: 650, type: !147)
!1025 = !DILocation(line: 650, column: 50, scope: !197)
!1026 = !DILocalVariable(name: "unpadded_size", arg: 3, scope: !197, file: !1, line: 651, type: !62)
!1027 = !DILocation(line: 651, column: 12, scope: !197)
!1028 = !DILocalVariable(name: "uncompressed_size", arg: 4, scope: !197, file: !1, line: 651, type: !62)
!1029 = !DILocation(line: 651, column: 36, scope: !197)
!1030 = !DILocalVariable(name: "s", scope: !197, file: !1, line: 653, type: !130)
!1031 = !DILocation(line: 653, column: 16, scope: !197)
!1032 = !DILocalVariable(name: "g", scope: !197, file: !1, line: 654, type: !131)
!1033 = !DILocation(line: 654, column: 15, scope: !197)
!1034 = !DILocalVariable(name: "compressed_base", scope: !197, file: !1, line: 655, type: !62)
!1035 = !DILocation(line: 655, column: 11, scope: !197)
!1036 = !DILocalVariable(name: "uncompressed_base", scope: !197, file: !1, line: 656, type: !62)
!1037 = !DILocation(line: 656, column: 11, scope: !197)
!1038 = !DILocalVariable(name: "index_list_size_add", scope: !197, file: !1, line: 657, type: !72)
!1039 = !DILocation(line: 657, column: 11, scope: !197)
!1040 = !DILocation(line: 660, column: 6, scope: !1041)
!1041 = distinct !DILexicalBlock(scope: !197, file: !1, line: 660, column: 6)
!1042 = !DILocation(line: 660, column: 8, scope: !1041)
!1043 = !DILocation(line: 660, column: 16, scope: !1041)
!1044 = !DILocation(line: 660, column: 19, scope: !1045)
!1045 = !DILexicalBlockFile(scope: !1041, file: !1, discriminator: 1)
!1046 = !DILocation(line: 660, column: 33, scope: !1045)
!1047 = !DILocation(line: 661, column: 4, scope: !1041)
!1048 = !DILocation(line: 661, column: 7, scope: !1045)
!1049 = !DILocation(line: 661, column: 21, scope: !1045)
!1050 = !DILocation(line: 662, column: 4, scope: !1041)
!1051 = !DILocation(line: 662, column: 7, scope: !1045)
!1052 = !DILocation(line: 662, column: 25, scope: !1045)
!1053 = !DILocation(line: 660, column: 6, scope: !1054)
!1054 = !DILexicalBlockFile(scope: !197, file: !1, discriminator: 2)
!1055 = !DILocation(line: 663, column: 3, scope: !1041)
!1056 = !DILocation(line: 665, column: 23, scope: !197)
!1057 = !DILocation(line: 665, column: 26, scope: !197)
!1058 = !DILocation(line: 665, column: 34, scope: !197)
!1059 = !DILocation(line: 665, column: 6, scope: !197)
!1060 = !DILocation(line: 665, column: 4, scope: !197)
!1061 = !DILocation(line: 666, column: 22, scope: !197)
!1062 = !DILocation(line: 666, column: 25, scope: !197)
!1063 = !DILocation(line: 666, column: 32, scope: !197)
!1064 = !DILocation(line: 666, column: 6, scope: !197)
!1065 = !DILocation(line: 666, column: 4, scope: !197)
!1066 = !DILocation(line: 668, column: 20, scope: !197)
!1067 = !DILocation(line: 668, column: 22, scope: !197)
!1068 = !DILocation(line: 668, column: 20, scope: !1069)
!1069 = !DILexicalBlockFile(scope: !197, file: !1, discriminator: 1)
!1070 = !DILocation(line: 669, column: 27, scope: !197)
!1071 = !DILocation(line: 669, column: 30, scope: !197)
!1072 = !DILocation(line: 669, column: 16, scope: !197)
!1073 = !DILocation(line: 669, column: 19, scope: !197)
!1074 = !DILocation(line: 669, column: 36, scope: !197)
!1075 = !DILocation(line: 669, column: 6, scope: !197)
!1076 = !DILocation(line: 668, column: 20, scope: !1054)
!1077 = !DILocation(line: 668, column: 20, scope: !1078)
!1078 = !DILexicalBlockFile(scope: !197, file: !1, discriminator: 3)
!1079 = !DILocation(line: 668, column: 18, scope: !1078)
!1080 = !DILocation(line: 670, column: 22, scope: !197)
!1081 = !DILocation(line: 670, column: 24, scope: !197)
!1082 = !DILocation(line: 670, column: 22, scope: !1069)
!1083 = !DILocation(line: 671, column: 17, scope: !197)
!1084 = !DILocation(line: 671, column: 20, scope: !197)
!1085 = !DILocation(line: 671, column: 6, scope: !197)
!1086 = !DILocation(line: 671, column: 9, scope: !197)
!1087 = !DILocation(line: 671, column: 26, scope: !197)
!1088 = !DILocation(line: 670, column: 22, scope: !1054)
!1089 = !DILocation(line: 670, column: 22, scope: !1078)
!1090 = !DILocation(line: 670, column: 20, scope: !1078)
!1091 = !DILocation(line: 672, column: 38, scope: !197)
!1092 = !DILocation(line: 672, column: 24, scope: !197)
!1093 = !DILocation(line: 673, column: 20, scope: !197)
!1094 = !DILocation(line: 673, column: 6, scope: !197)
!1095 = !DILocation(line: 673, column: 4, scope: !197)
!1096 = !DILocation(line: 672, column: 22, scope: !197)
!1097 = !DILocation(line: 676, column: 22, scope: !1098)
!1098 = distinct !DILexicalBlock(scope: !197, file: !1, line: 676, column: 6)
!1099 = !DILocation(line: 676, column: 25, scope: !1098)
!1100 = !DILocation(line: 676, column: 30, scope: !1098)
!1101 = !DILocation(line: 677, column: 4, scope: !1098)
!1102 = !DILocation(line: 677, column: 22, scope: !1098)
!1103 = !DILocation(line: 677, column: 20, scope: !1098)
!1104 = !DILocation(line: 677, column: 37, scope: !1098)
!1105 = !DILocation(line: 677, column: 40, scope: !1098)
!1106 = !DILocation(line: 677, column: 53, scope: !1098)
!1107 = !DILocation(line: 678, column: 4, scope: !1098)
!1108 = !DILocation(line: 678, column: 7, scope: !1098)
!1109 = !DILocation(line: 678, column: 25, scope: !1098)
!1110 = !DILocation(line: 678, column: 23, scope: !1098)
!1111 = !DILocation(line: 679, column: 4, scope: !1098)
!1112 = !DILocation(line: 679, column: 7, scope: !1098)
!1113 = !DILocation(line: 676, column: 6, scope: !1098)
!1114 = !DILocation(line: 679, column: 23, scope: !1098)
!1115 = !DILocation(line: 676, column: 6, scope: !197)
!1116 = !DILocation(line: 680, column: 3, scope: !1098)
!1117 = !DILocation(line: 684, column: 17, scope: !1118)
!1118 = distinct !DILexicalBlock(scope: !197, file: !1, line: 684, column: 6)
!1119 = !DILocation(line: 684, column: 20, scope: !1118)
!1120 = !DILocation(line: 684, column: 33, scope: !1118)
!1121 = !DILocation(line: 685, column: 4, scope: !1118)
!1122 = !DILocation(line: 685, column: 7, scope: !1118)
!1123 = !DILocation(line: 685, column: 25, scope: !1118)
!1124 = !DILocation(line: 685, column: 23, scope: !1118)
!1125 = !DILocation(line: 684, column: 6, scope: !1118)
!1126 = !DILocation(line: 686, column: 4, scope: !1118)
!1127 = !DILocation(line: 684, column: 6, scope: !197)
!1128 = !DILocation(line: 687, column: 3, scope: !1118)
!1129 = !DILocation(line: 689, column: 6, scope: !1130)
!1130 = distinct !DILexicalBlock(scope: !197, file: !1, line: 689, column: 6)
!1131 = !DILocation(line: 689, column: 8, scope: !1130)
!1132 = !DILocation(line: 689, column: 16, scope: !1130)
!1133 = !DILocation(line: 689, column: 19, scope: !1134)
!1134 = !DILexicalBlockFile(scope: !1130, file: !1, discriminator: 1)
!1135 = !DILocation(line: 689, column: 22, scope: !1134)
!1136 = !DILocation(line: 689, column: 27, scope: !1134)
!1137 = !DILocation(line: 689, column: 33, scope: !1134)
!1138 = !DILocation(line: 689, column: 36, scope: !1134)
!1139 = !DILocation(line: 689, column: 31, scope: !1134)
!1140 = !DILocation(line: 689, column: 6, scope: !1134)
!1141 = !DILocation(line: 691, column: 5, scope: !1142)
!1142 = distinct !DILexicalBlock(scope: !1130, file: !1, line: 689, column: 47)
!1143 = !DILocation(line: 691, column: 8, scope: !1142)
!1144 = !DILocation(line: 691, column: 3, scope: !1142)
!1145 = !DILocation(line: 692, column: 2, scope: !1142)
!1146 = !DILocation(line: 695, column: 7, scope: !1147)
!1147 = distinct !DILexicalBlock(scope: !1130, file: !1, line: 692, column: 9)
!1148 = !DILocation(line: 695, column: 10, scope: !1147)
!1149 = !DILocation(line: 695, column: 19, scope: !1147)
!1150 = !DILocation(line: 695, column: 5, scope: !1147)
!1151 = !DILocation(line: 696, column: 5, scope: !1147)
!1152 = !DILocation(line: 694, column: 7, scope: !1147)
!1153 = !DILocation(line: 694, column: 5, scope: !1147)
!1154 = !DILocation(line: 697, column: 7, scope: !1155)
!1155 = distinct !DILexicalBlock(scope: !1147, file: !1, line: 697, column: 7)
!1156 = !DILocation(line: 697, column: 9, scope: !1155)
!1157 = !DILocation(line: 697, column: 7, scope: !1147)
!1158 = !DILocation(line: 698, column: 4, scope: !1155)
!1159 = !DILocation(line: 700, column: 3, scope: !1147)
!1160 = !DILocation(line: 700, column: 6, scope: !1147)
!1161 = !DILocation(line: 700, column: 11, scope: !1147)
!1162 = !DILocation(line: 701, column: 18, scope: !1147)
!1163 = !DILocation(line: 701, column: 21, scope: !1147)
!1164 = !DILocation(line: 701, column: 3, scope: !1147)
!1165 = !DILocation(line: 701, column: 6, scope: !1147)
!1166 = !DILocation(line: 701, column: 16, scope: !1147)
!1167 = !DILocation(line: 705, column: 3, scope: !1147)
!1168 = !DILocation(line: 705, column: 6, scope: !1147)
!1169 = !DILocation(line: 705, column: 15, scope: !1147)
!1170 = !DILocation(line: 708, column: 31, scope: !1147)
!1171 = !DILocation(line: 708, column: 3, scope: !1147)
!1172 = !DILocation(line: 708, column: 6, scope: !1147)
!1173 = !DILocation(line: 708, column: 11, scope: !1147)
!1174 = !DILocation(line: 708, column: 29, scope: !1147)
!1175 = !DILocation(line: 709, column: 29, scope: !1147)
!1176 = !DILocation(line: 709, column: 3, scope: !1147)
!1177 = !DILocation(line: 709, column: 6, scope: !1147)
!1178 = !DILocation(line: 709, column: 11, scope: !1147)
!1179 = !DILocation(line: 709, column: 27, scope: !1147)
!1180 = !DILocation(line: 710, column: 20, scope: !1147)
!1181 = !DILocation(line: 710, column: 23, scope: !1147)
!1182 = !DILocation(line: 710, column: 36, scope: !1147)
!1183 = !DILocation(line: 710, column: 3, scope: !1147)
!1184 = !DILocation(line: 710, column: 6, scope: !1147)
!1185 = !DILocation(line: 710, column: 18, scope: !1147)
!1186 = !DILocation(line: 713, column: 22, scope: !1147)
!1187 = !DILocation(line: 713, column: 25, scope: !1147)
!1188 = !DILocation(line: 713, column: 34, scope: !1147)
!1189 = !DILocation(line: 713, column: 37, scope: !1147)
!1190 = !DILocation(line: 713, column: 3, scope: !1147)
!1191 = !DILocation(line: 718, column: 6, scope: !197)
!1192 = !DILocation(line: 718, column: 26, scope: !197)
!1193 = !DILocation(line: 718, column: 24, scope: !197)
!1194 = !DILocation(line: 717, column: 13, scope: !197)
!1195 = !DILocation(line: 717, column: 16, scope: !197)
!1196 = !DILocation(line: 717, column: 2, scope: !197)
!1197 = !DILocation(line: 717, column: 5, scope: !197)
!1198 = !DILocation(line: 717, column: 22, scope: !197)
!1199 = !DILocation(line: 718, column: 4, scope: !197)
!1200 = !DILocation(line: 720, column: 6, scope: !197)
!1201 = !DILocation(line: 720, column: 24, scope: !197)
!1202 = !DILocation(line: 720, column: 22, scope: !197)
!1203 = !DILocation(line: 719, column: 13, scope: !197)
!1204 = !DILocation(line: 719, column: 16, scope: !197)
!1205 = !DILocation(line: 719, column: 2, scope: !197)
!1206 = !DILocation(line: 719, column: 5, scope: !197)
!1207 = !DILocation(line: 719, column: 22, scope: !197)
!1208 = !DILocation(line: 720, column: 4, scope: !197)
!1209 = !DILocation(line: 723, column: 4, scope: !197)
!1210 = !DILocation(line: 723, column: 7, scope: !197)
!1211 = !DILocation(line: 723, column: 2, scope: !197)
!1212 = !DILocation(line: 724, column: 24, scope: !197)
!1213 = !DILocation(line: 724, column: 2, scope: !197)
!1214 = !DILocation(line: 724, column: 5, scope: !197)
!1215 = !DILocation(line: 724, column: 21, scope: !197)
!1216 = !DILocation(line: 726, column: 29, scope: !197)
!1217 = !DILocation(line: 726, column: 19, scope: !197)
!1218 = !DILocation(line: 726, column: 2, scope: !197)
!1219 = !DILocation(line: 726, column: 5, scope: !197)
!1220 = !DILocation(line: 726, column: 16, scope: !197)
!1221 = !DILocation(line: 727, column: 26, scope: !197)
!1222 = !DILocation(line: 727, column: 2, scope: !197)
!1223 = !DILocation(line: 727, column: 5, scope: !197)
!1224 = !DILocation(line: 727, column: 23, scope: !197)
!1225 = !DILocation(line: 728, column: 4, scope: !197)
!1226 = !DILocation(line: 728, column: 7, scope: !197)
!1227 = !DILocation(line: 728, column: 2, scope: !197)
!1228 = !DILocation(line: 729, column: 24, scope: !197)
!1229 = !DILocation(line: 729, column: 2, scope: !197)
!1230 = !DILocation(line: 729, column: 5, scope: !197)
!1231 = !DILocation(line: 729, column: 21, scope: !197)
!1232 = !DILocation(line: 731, column: 2, scope: !197)
!1233 = !DILocation(line: 732, column: 1, scope: !197)
!1234 = !DILocalVariable(name: "vli", arg: 1, scope: !307, file: !300, line: 39, type: !62)
!1235 = !DILocation(line: 39, column: 20, scope: !307)
!1236 = !DILocation(line: 41, column: 2, scope: !307)
!1237 = !DILocation(line: 41, column: 2, scope: !1238)
!1238 = !DILexicalBlockFile(scope: !307, file: !300, discriminator: 1)
!1239 = !DILocation(line: 41, column: 2, scope: !1240)
!1240 = !DILexicalBlockFile(scope: !307, file: !300, discriminator: 2)
!1241 = !DILocation(line: 41, column: 2, scope: !1242)
!1242 = !DILexicalBlockFile(scope: !307, file: !300, discriminator: 3)
!1243 = !DILocation(line: 42, column: 10, scope: !307)
!1244 = !DILocation(line: 42, column: 14, scope: !307)
!1245 = !DILocation(line: 42, column: 19, scope: !307)
!1246 = !DILocation(line: 42, column: 2, scope: !307)
!1247 = !DILocalVariable(name: "dest", arg: 1, scope: !200, file: !1, line: 783, type: !203)
!1248 = !DILocation(line: 783, column: 42, scope: !200)
!1249 = !DILocalVariable(name: "src", arg: 2, scope: !200, file: !1, line: 783, type: !203)
!1250 = !DILocation(line: 783, column: 74, scope: !200)
!1251 = !DILocalVariable(name: "allocator", arg: 3, scope: !200, file: !1, line: 784, type: !147)
!1252 = !DILocation(line: 784, column: 19, scope: !200)
!1253 = !DILocalVariable(name: "info", scope: !200, file: !1, line: 786, type: !315)
!1254 = !DILocation(line: 786, column: 17, scope: !200)
!1255 = !DILocalVariable(name: "dest_file_size", scope: !200, file: !1, line: 787, type: !698)
!1256 = !DILocation(line: 787, column: 17, scope: !200)
!1257 = !DILocation(line: 787, column: 55, scope: !200)
!1258 = !DILocation(line: 787, column: 34, scope: !200)
!1259 = !DILocation(line: 790, column: 6, scope: !1260)
!1260 = distinct !DILexicalBlock(scope: !200, file: !1, line: 790, column: 6)
!1261 = !DILocation(line: 790, column: 44, scope: !1260)
!1262 = !DILocation(line: 790, column: 23, scope: !1260)
!1263 = !DILocation(line: 790, column: 21, scope: !1260)
!1264 = !DILocation(line: 790, column: 49, scope: !1260)
!1265 = !DILocation(line: 791, column: 4, scope: !1260)
!1266 = !DILocation(line: 791, column: 7, scope: !1267)
!1267 = !DILexicalBlockFile(scope: !1260, file: !1, discriminator: 1)
!1268 = !DILocation(line: 791, column: 13, scope: !1267)
!1269 = !DILocation(line: 791, column: 33, scope: !1267)
!1270 = !DILocation(line: 791, column: 38, scope: !1267)
!1271 = !DILocation(line: 791, column: 31, scope: !1267)
!1272 = !DILocation(line: 792, column: 5, scope: !1260)
!1273 = !DILocation(line: 790, column: 6, scope: !1274)
!1274 = !DILexicalBlockFile(scope: !200, file: !1, discriminator: 1)
!1275 = !DILocation(line: 793, column: 3, scope: !1260)
!1276 = !DILocalVariable(name: "dest_size", scope: !1277, file: !1, line: 802, type: !698)
!1277 = distinct !DILexicalBlock(scope: !200, file: !1, line: 801, column: 2)
!1278 = !DILocation(line: 802, column: 18, scope: !1277)
!1279 = !DILocation(line: 803, column: 5, scope: !1277)
!1280 = !DILocation(line: 803, column: 11, scope: !1277)
!1281 = !DILocation(line: 803, column: 25, scope: !1277)
!1282 = !DILocation(line: 803, column: 31, scope: !1277)
!1283 = !DILocation(line: 802, column: 30, scope: !1277)
!1284 = !DILocalVariable(name: "src_size", scope: !1277, file: !1, line: 804, type: !698)
!1285 = !DILocation(line: 804, column: 18, scope: !1277)
!1286 = !DILocation(line: 805, column: 5, scope: !1277)
!1287 = !DILocation(line: 805, column: 10, scope: !1277)
!1288 = !DILocation(line: 805, column: 24, scope: !1277)
!1289 = !DILocation(line: 805, column: 29, scope: !1277)
!1290 = !DILocation(line: 804, column: 29, scope: !1277)
!1291 = !DILocation(line: 806, column: 17, scope: !1292)
!1292 = distinct !DILexicalBlock(scope: !1277, file: !1, line: 806, column: 7)
!1293 = !DILocation(line: 806, column: 29, scope: !1292)
!1294 = !DILocation(line: 806, column: 27, scope: !1292)
!1295 = !DILocation(line: 806, column: 7, scope: !1292)
!1296 = !DILocation(line: 806, column: 39, scope: !1292)
!1297 = !DILocation(line: 806, column: 7, scope: !1277)
!1298 = !DILocation(line: 807, column: 4, scope: !1292)
!1299 = !DILocalVariable(name: "s", scope: !1300, file: !1, line: 813, type: !130)
!1300 = distinct !DILexicalBlock(scope: !200, file: !1, line: 812, column: 2)
!1301 = !DILocation(line: 813, column: 17, scope: !1300)
!1302 = !DILocation(line: 813, column: 38, scope: !1300)
!1303 = !DILocation(line: 813, column: 44, scope: !1300)
!1304 = !DILocation(line: 813, column: 52, scope: !1300)
!1305 = !DILocation(line: 813, column: 21, scope: !1300)
!1306 = !DILocalVariable(name: "g", scope: !1300, file: !1, line: 814, type: !131)
!1307 = !DILocation(line: 814, column: 16, scope: !1300)
!1308 = !DILocation(line: 814, column: 36, scope: !1300)
!1309 = !DILocation(line: 814, column: 39, scope: !1300)
!1310 = !DILocation(line: 814, column: 46, scope: !1300)
!1311 = !DILocation(line: 814, column: 20, scope: !1300)
!1312 = !DILocation(line: 815, column: 7, scope: !1313)
!1313 = distinct !DILexicalBlock(scope: !1300, file: !1, line: 815, column: 7)
!1314 = !DILocation(line: 815, column: 9, scope: !1313)
!1315 = !DILocation(line: 815, column: 17, scope: !1313)
!1316 = !DILocation(line: 815, column: 20, scope: !1317)
!1317 = !DILexicalBlockFile(scope: !1313, file: !1, discriminator: 1)
!1318 = !DILocation(line: 815, column: 23, scope: !1317)
!1319 = !DILocation(line: 815, column: 28, scope: !1317)
!1320 = !DILocation(line: 815, column: 34, scope: !1317)
!1321 = !DILocation(line: 815, column: 37, scope: !1317)
!1322 = !DILocation(line: 815, column: 32, scope: !1317)
!1323 = !DILocation(line: 815, column: 7, scope: !1317)
!1324 = !DILocalVariable(name: "newg", scope: !1325, file: !1, line: 816, type: !131)
!1325 = distinct !DILexicalBlock(scope: !1313, file: !1, line: 815, column: 48)
!1326 = !DILocation(line: 816, column: 17, scope: !1325)
!1327 = !DILocation(line: 818, column: 4, scope: !1325)
!1328 = !DILocation(line: 818, column: 4, scope: !1329)
!1329 = !DILexicalBlockFile(scope: !1325, file: !1, discriminator: 1)
!1330 = !DILocation(line: 818, column: 4, scope: !1331)
!1331 = !DILexicalBlockFile(scope: !1325, file: !1, discriminator: 2)
!1332 = !DILocation(line: 818, column: 4, scope: !1333)
!1333 = !DILexicalBlockFile(scope: !1325, file: !1, discriminator: 3)
!1334 = !DILocation(line: 819, column: 4, scope: !1325)
!1335 = !DILocation(line: 819, column: 4, scope: !1329)
!1336 = !DILocation(line: 819, column: 4, scope: !1331)
!1337 = !DILocation(line: 819, column: 4, scope: !1333)
!1338 = !DILocation(line: 822, column: 9, scope: !1325)
!1339 = !DILocation(line: 822, column: 12, scope: !1325)
!1340 = !DILocation(line: 822, column: 17, scope: !1325)
!1341 = !DILocation(line: 823, column: 6, scope: !1325)
!1342 = !DILocation(line: 822, column: 6, scope: !1325)
!1343 = !DILocation(line: 824, column: 6, scope: !1325)
!1344 = !DILocation(line: 821, column: 11, scope: !1325)
!1345 = !DILocation(line: 821, column: 9, scope: !1325)
!1346 = !DILocation(line: 825, column: 8, scope: !1347)
!1347 = distinct !DILexicalBlock(scope: !1325, file: !1, line: 825, column: 8)
!1348 = !DILocation(line: 825, column: 13, scope: !1347)
!1349 = !DILocation(line: 825, column: 8, scope: !1325)
!1350 = !DILocation(line: 826, column: 5, scope: !1347)
!1351 = !DILocation(line: 828, column: 4, scope: !1325)
!1352 = !DILocation(line: 828, column: 10, scope: !1325)
!1353 = !DILocation(line: 828, column: 17, scope: !1325)
!1354 = !DILocation(line: 828, column: 20, scope: !1325)
!1355 = !DILocation(line: 829, column: 22, scope: !1325)
!1356 = !DILocation(line: 829, column: 25, scope: !1325)
!1357 = !DILocation(line: 829, column: 30, scope: !1325)
!1358 = !DILocation(line: 829, column: 4, scope: !1325)
!1359 = !DILocation(line: 829, column: 10, scope: !1325)
!1360 = !DILocation(line: 829, column: 20, scope: !1325)
!1361 = !DILocation(line: 830, column: 17, scope: !1325)
!1362 = !DILocation(line: 830, column: 20, scope: !1325)
!1363 = !DILocation(line: 830, column: 4, scope: !1325)
!1364 = !DILocation(line: 830, column: 10, scope: !1325)
!1365 = !DILocation(line: 830, column: 15, scope: !1325)
!1366 = !DILocation(line: 831, column: 24, scope: !1325)
!1367 = !DILocation(line: 831, column: 27, scope: !1325)
!1368 = !DILocation(line: 831, column: 4, scope: !1325)
!1369 = !DILocation(line: 831, column: 10, scope: !1325)
!1370 = !DILocation(line: 831, column: 22, scope: !1325)
!1371 = !DILocation(line: 833, column: 11, scope: !1325)
!1372 = !DILocation(line: 833, column: 17, scope: !1325)
!1373 = !DILocation(line: 833, column: 4, scope: !1325)
!1374 = !DILocation(line: 833, column: 26, scope: !1325)
!1375 = !DILocation(line: 833, column: 29, scope: !1325)
!1376 = !DILocation(line: 833, column: 38, scope: !1325)
!1377 = !DILocation(line: 833, column: 44, scope: !1325)
!1378 = !DILocation(line: 834, column: 6, scope: !1325)
!1379 = !DILocation(line: 836, column: 8, scope: !1380)
!1380 = distinct !DILexicalBlock(scope: !1325, file: !1, line: 836, column: 8)
!1381 = !DILocation(line: 836, column: 11, scope: !1380)
!1382 = !DILocation(line: 836, column: 16, scope: !1380)
!1383 = !DILocation(line: 836, column: 23, scope: !1380)
!1384 = !DILocation(line: 836, column: 8, scope: !1325)
!1385 = !DILocation(line: 837, column: 5, scope: !1386)
!1386 = distinct !DILexicalBlock(scope: !1380, file: !1, line: 836, column: 32)
!1387 = !DILocation(line: 837, column: 5, scope: !1388)
!1388 = !DILexicalBlockFile(scope: !1386, file: !1, discriminator: 1)
!1389 = !DILocation(line: 837, column: 5, scope: !1390)
!1390 = !DILexicalBlockFile(scope: !1386, file: !1, discriminator: 2)
!1391 = !DILocation(line: 837, column: 5, scope: !1392)
!1392 = !DILexicalBlockFile(scope: !1386, file: !1, discriminator: 3)
!1393 = !DILocation(line: 838, column: 30, scope: !1386)
!1394 = !DILocation(line: 838, column: 36, scope: !1386)
!1395 = !DILocation(line: 838, column: 5, scope: !1386)
!1396 = !DILocation(line: 838, column: 8, scope: !1386)
!1397 = !DILocation(line: 838, column: 13, scope: !1386)
!1398 = !DILocation(line: 838, column: 21, scope: !1386)
!1399 = !DILocation(line: 838, column: 27, scope: !1386)
!1400 = !DILocation(line: 839, column: 4, scope: !1386)
!1401 = !DILocation(line: 841, column: 8, scope: !1402)
!1402 = distinct !DILexicalBlock(scope: !1325, file: !1, line: 841, column: 8)
!1403 = !DILocation(line: 841, column: 11, scope: !1402)
!1404 = !DILocation(line: 841, column: 18, scope: !1402)
!1405 = !DILocation(line: 841, column: 31, scope: !1402)
!1406 = !DILocation(line: 841, column: 34, scope: !1402)
!1407 = !DILocation(line: 841, column: 27, scope: !1402)
!1408 = !DILocation(line: 841, column: 8, scope: !1325)
!1409 = !DILocation(line: 842, column: 5, scope: !1410)
!1410 = distinct !DILexicalBlock(scope: !1402, file: !1, line: 841, column: 40)
!1411 = !DILocation(line: 842, column: 5, scope: !1412)
!1412 = !DILexicalBlockFile(scope: !1410, file: !1, discriminator: 1)
!1413 = !DILocation(line: 842, column: 5, scope: !1414)
!1414 = !DILexicalBlockFile(scope: !1410, file: !1, discriminator: 2)
!1415 = !DILocation(line: 842, column: 5, scope: !1416)
!1416 = !DILexicalBlockFile(scope: !1410, file: !1, discriminator: 3)
!1417 = !DILocation(line: 843, column: 27, scope: !1410)
!1418 = !DILocation(line: 843, column: 33, scope: !1410)
!1419 = !DILocation(line: 843, column: 5, scope: !1410)
!1420 = !DILocation(line: 843, column: 8, scope: !1410)
!1421 = !DILocation(line: 843, column: 15, scope: !1410)
!1422 = !DILocation(line: 843, column: 24, scope: !1410)
!1423 = !DILocation(line: 844, column: 23, scope: !1410)
!1424 = !DILocation(line: 844, column: 29, scope: !1410)
!1425 = !DILocation(line: 844, column: 5, scope: !1410)
!1426 = !DILocation(line: 844, column: 8, scope: !1410)
!1427 = !DILocation(line: 844, column: 15, scope: !1410)
!1428 = !DILocation(line: 844, column: 20, scope: !1410)
!1429 = !DILocation(line: 845, column: 4, scope: !1410)
!1430 = !DILocation(line: 847, column: 8, scope: !1431)
!1431 = distinct !DILexicalBlock(scope: !1325, file: !1, line: 847, column: 8)
!1432 = !DILocation(line: 847, column: 11, scope: !1431)
!1433 = !DILocation(line: 847, column: 18, scope: !1431)
!1434 = !DILocation(line: 847, column: 32, scope: !1431)
!1435 = !DILocation(line: 847, column: 35, scope: !1431)
!1436 = !DILocation(line: 847, column: 28, scope: !1431)
!1437 = !DILocation(line: 847, column: 8, scope: !1325)
!1438 = !DILocation(line: 848, column: 28, scope: !1431)
!1439 = !DILocation(line: 848, column: 34, scope: !1431)
!1440 = !DILocation(line: 848, column: 5, scope: !1431)
!1441 = !DILocation(line: 848, column: 8, scope: !1431)
!1442 = !DILocation(line: 848, column: 15, scope: !1431)
!1443 = !DILocation(line: 848, column: 25, scope: !1431)
!1444 = !DILocation(line: 850, column: 14, scope: !1325)
!1445 = !DILocation(line: 850, column: 17, scope: !1325)
!1446 = !DILocation(line: 850, column: 4, scope: !1325)
!1447 = !DILocation(line: 851, column: 3, scope: !1325)
!1448 = !DILocation(line: 856, column: 27, scope: !200)
!1449 = !DILocation(line: 856, column: 33, scope: !200)
!1450 = !DILocation(line: 856, column: 7, scope: !200)
!1451 = !DILocation(line: 856, column: 25, scope: !200)
!1452 = !DILocation(line: 857, column: 19, scope: !200)
!1453 = !DILocation(line: 857, column: 7, scope: !200)
!1454 = !DILocation(line: 857, column: 17, scope: !200)
!1455 = !DILocation(line: 858, column: 27, scope: !200)
!1456 = !DILocation(line: 858, column: 33, scope: !200)
!1457 = !DILocation(line: 858, column: 41, scope: !200)
!1458 = !DILocation(line: 858, column: 7, scope: !200)
!1459 = !DILocation(line: 858, column: 25, scope: !200)
!1460 = !DILocation(line: 859, column: 26, scope: !200)
!1461 = !DILocation(line: 859, column: 32, scope: !200)
!1462 = !DILocation(line: 859, column: 7, scope: !200)
!1463 = !DILocation(line: 859, column: 24, scope: !200)
!1464 = !DILocation(line: 860, column: 18, scope: !200)
!1465 = !DILocation(line: 860, column: 24, scope: !200)
!1466 = !DILocation(line: 860, column: 7, scope: !200)
!1467 = !DILocation(line: 860, column: 15, scope: !200)
!1468 = !DILocation(line: 862, column: 43, scope: !200)
!1469 = !DILocation(line: 862, column: 48, scope: !200)
!1470 = !DILocation(line: 862, column: 56, scope: !200)
!1471 = !DILocation(line: 862, column: 26, scope: !200)
!1472 = !DILocation(line: 862, column: 2, scope: !200)
!1473 = !DILocation(line: 865, column: 29, scope: !200)
!1474 = !DILocation(line: 865, column: 34, scope: !200)
!1475 = !DILocation(line: 865, column: 2, scope: !200)
!1476 = !DILocation(line: 865, column: 8, scope: !200)
!1477 = !DILocation(line: 865, column: 26, scope: !200)
!1478 = !DILocation(line: 866, column: 22, scope: !200)
!1479 = !DILocation(line: 866, column: 27, scope: !200)
!1480 = !DILocation(line: 866, column: 2, scope: !200)
!1481 = !DILocation(line: 866, column: 8, scope: !200)
!1482 = !DILocation(line: 866, column: 19, scope: !200)
!1483 = !DILocation(line: 867, column: 24, scope: !200)
!1484 = !DILocation(line: 867, column: 29, scope: !200)
!1485 = !DILocation(line: 867, column: 2, scope: !200)
!1486 = !DILocation(line: 867, column: 8, scope: !200)
!1487 = !DILocation(line: 867, column: 21, scope: !200)
!1488 = !DILocation(line: 868, column: 27, scope: !200)
!1489 = !DILocation(line: 868, column: 32, scope: !200)
!1490 = !DILocation(line: 868, column: 2, scope: !200)
!1491 = !DILocation(line: 868, column: 8, scope: !200)
!1492 = !DILocation(line: 868, column: 24, scope: !200)
!1493 = !DILocation(line: 869, column: 35, scope: !200)
!1494 = !DILocation(line: 869, column: 17, scope: !200)
!1495 = !DILocation(line: 869, column: 43, scope: !200)
!1496 = !DILocation(line: 869, column: 48, scope: !200)
!1497 = !DILocation(line: 869, column: 41, scope: !200)
!1498 = !DILocation(line: 869, column: 2, scope: !200)
!1499 = !DILocation(line: 869, column: 8, scope: !200)
!1500 = !DILocation(line: 869, column: 15, scope: !200)
!1501 = !DILocation(line: 872, column: 12, scope: !200)
!1502 = !DILocation(line: 872, column: 17, scope: !200)
!1503 = !DILocation(line: 872, column: 2, scope: !200)
!1504 = !DILocation(line: 874, column: 2, scope: !200)
!1505 = !DILocation(line: 875, column: 1, scope: !200)
!1506 = !DILocalVariable(name: "info", arg: 1, scope: !310, file: !1, line: 761, type: !313)
!1507 = !DILocation(line: 761, column: 40, scope: !310)
!1508 = !DILocalVariable(name: "this", arg: 2, scope: !310, file: !1, line: 761, type: !130)
!1509 = !DILocation(line: 761, column: 60, scope: !310)
!1510 = !DILocalVariable(name: "left", scope: !310, file: !1, line: 763, type: !130)
!1511 = !DILocation(line: 763, column: 16, scope: !310)
!1512 = !DILocation(line: 763, column: 40, scope: !310)
!1513 = !DILocation(line: 763, column: 46, scope: !310)
!1514 = !DILocation(line: 763, column: 51, scope: !310)
!1515 = !DILocation(line: 763, column: 23, scope: !310)
!1516 = !DILocalVariable(name: "right", scope: !310, file: !1, line: 764, type: !130)
!1517 = !DILocation(line: 764, column: 16, scope: !310)
!1518 = !DILocation(line: 764, column: 41, scope: !310)
!1519 = !DILocation(line: 764, column: 47, scope: !310)
!1520 = !DILocation(line: 764, column: 52, scope: !310)
!1521 = !DILocation(line: 764, column: 24, scope: !310)
!1522 = !DILocation(line: 766, column: 6, scope: !1523)
!1523 = distinct !DILexicalBlock(scope: !310, file: !1, line: 766, column: 6)
!1524 = !DILocation(line: 766, column: 11, scope: !1523)
!1525 = !DILocation(line: 766, column: 6, scope: !310)
!1526 = !DILocation(line: 767, column: 20, scope: !1523)
!1527 = !DILocation(line: 767, column: 26, scope: !1523)
!1528 = !DILocation(line: 767, column: 3, scope: !1523)
!1529 = !DILocation(line: 769, column: 34, scope: !310)
!1530 = !DILocation(line: 769, column: 40, scope: !310)
!1531 = !DILocation(line: 769, column: 2, scope: !310)
!1532 = !DILocation(line: 769, column: 8, scope: !310)
!1533 = !DILocation(line: 769, column: 13, scope: !310)
!1534 = !DILocation(line: 769, column: 31, scope: !310)
!1535 = !DILocation(line: 770, column: 32, scope: !310)
!1536 = !DILocation(line: 770, column: 38, scope: !310)
!1537 = !DILocation(line: 770, column: 2, scope: !310)
!1538 = !DILocation(line: 770, column: 8, scope: !310)
!1539 = !DILocation(line: 770, column: 13, scope: !310)
!1540 = !DILocation(line: 770, column: 29, scope: !310)
!1541 = !DILocation(line: 771, column: 18, scope: !310)
!1542 = !DILocation(line: 771, column: 24, scope: !310)
!1543 = !DILocation(line: 771, column: 2, scope: !310)
!1544 = !DILocation(line: 771, column: 8, scope: !310)
!1545 = !DILocation(line: 771, column: 15, scope: !310)
!1546 = !DILocation(line: 772, column: 29, scope: !310)
!1547 = !DILocation(line: 772, column: 35, scope: !310)
!1548 = !DILocation(line: 772, column: 2, scope: !310)
!1549 = !DILocation(line: 772, column: 8, scope: !310)
!1550 = !DILocation(line: 772, column: 26, scope: !310)
!1551 = !DILocation(line: 773, column: 20, scope: !310)
!1552 = !DILocation(line: 773, column: 26, scope: !310)
!1553 = !DILocation(line: 773, column: 36, scope: !310)
!1554 = !DILocation(line: 773, column: 42, scope: !310)
!1555 = !DILocation(line: 773, column: 2, scope: !310)
!1556 = !DILocation(line: 775, column: 6, scope: !1557)
!1557 = distinct !DILexicalBlock(scope: !310, file: !1, line: 775, column: 6)
!1558 = !DILocation(line: 775, column: 12, scope: !1557)
!1559 = !DILocation(line: 775, column: 6, scope: !310)
!1560 = !DILocation(line: 776, column: 20, scope: !1557)
!1561 = !DILocation(line: 776, column: 26, scope: !1557)
!1562 = !DILocation(line: 776, column: 3, scope: !1557)
!1563 = !DILocation(line: 778, column: 2, scope: !310)
!1564 = !DILocalVariable(name: "src", arg: 1, scope: !204, file: !1, line: 944, type: !173)
!1565 = !DILocation(line: 944, column: 34, scope: !204)
!1566 = !DILocalVariable(name: "allocator", arg: 2, scope: !204, file: !1, line: 944, type: !147)
!1567 = !DILocation(line: 944, column: 55, scope: !204)
!1568 = !DILocalVariable(name: "srcstream", scope: !204, file: !1, line: 946, type: !130)
!1569 = !DILocation(line: 946, column: 16, scope: !204)
!1570 = !DILocalVariable(name: "deststream", scope: !204, file: !1, line: 947, type: !130)
!1571 = !DILocation(line: 947, column: 16, scope: !204)
!1572 = !DILocalVariable(name: "dest", scope: !204, file: !1, line: 950, type: !136)
!1573 = !DILocation(line: 950, column: 14, scope: !204)
!1574 = !DILocation(line: 950, column: 38, scope: !204)
!1575 = !DILocation(line: 950, column: 21, scope: !204)
!1576 = !DILocation(line: 951, column: 6, scope: !1577)
!1577 = distinct !DILexicalBlock(scope: !204, file: !1, line: 951, column: 6)
!1578 = !DILocation(line: 951, column: 11, scope: !1577)
!1579 = !DILocation(line: 951, column: 6, scope: !204)
!1580 = !DILocation(line: 952, column: 3, scope: !1577)
!1581 = !DILocation(line: 955, column: 28, scope: !204)
!1582 = !DILocation(line: 955, column: 33, scope: !204)
!1583 = !DILocation(line: 955, column: 2, scope: !204)
!1584 = !DILocation(line: 955, column: 8, scope: !204)
!1585 = !DILocation(line: 955, column: 26, scope: !204)
!1586 = !DILocation(line: 956, column: 21, scope: !204)
!1587 = !DILocation(line: 956, column: 26, scope: !204)
!1588 = !DILocation(line: 956, column: 2, scope: !204)
!1589 = !DILocation(line: 956, column: 8, scope: !204)
!1590 = !DILocation(line: 956, column: 19, scope: !204)
!1591 = !DILocation(line: 957, column: 23, scope: !204)
!1592 = !DILocation(line: 957, column: 28, scope: !204)
!1593 = !DILocation(line: 957, column: 2, scope: !204)
!1594 = !DILocation(line: 957, column: 8, scope: !204)
!1595 = !DILocation(line: 957, column: 21, scope: !204)
!1596 = !DILocation(line: 958, column: 26, scope: !204)
!1597 = !DILocation(line: 958, column: 31, scope: !204)
!1598 = !DILocation(line: 958, column: 2, scope: !204)
!1599 = !DILocation(line: 958, column: 8, scope: !204)
!1600 = !DILocation(line: 958, column: 24, scope: !204)
!1601 = !DILocation(line: 961, column: 31, scope: !204)
!1602 = !DILocation(line: 961, column: 36, scope: !204)
!1603 = !DILocation(line: 961, column: 44, scope: !204)
!1604 = !DILocation(line: 961, column: 14, scope: !204)
!1605 = !DILocation(line: 961, column: 12, scope: !204)
!1606 = !DILocation(line: 962, column: 2, scope: !204)
!1607 = !DILocation(line: 963, column: 33, scope: !1608)
!1608 = distinct !DILexicalBlock(scope: !204, file: !1, line: 962, column: 5)
!1609 = !DILocation(line: 963, column: 44, scope: !1608)
!1610 = !DILocation(line: 963, column: 16, scope: !1608)
!1611 = !DILocation(line: 963, column: 14, scope: !1608)
!1612 = !DILocation(line: 964, column: 7, scope: !1613)
!1613 = distinct !DILexicalBlock(scope: !1608, file: !1, line: 964, column: 7)
!1614 = !DILocation(line: 964, column: 18, scope: !1613)
!1615 = !DILocation(line: 964, column: 7, scope: !1608)
!1616 = !DILocation(line: 965, column: 19, scope: !1617)
!1617 = distinct !DILexicalBlock(scope: !1613, file: !1, line: 964, column: 27)
!1618 = !DILocation(line: 965, column: 25, scope: !1617)
!1619 = !DILocation(line: 965, column: 4, scope: !1617)
!1620 = !DILocation(line: 966, column: 4, scope: !1617)
!1621 = !DILocation(line: 969, column: 22, scope: !1608)
!1622 = !DILocation(line: 969, column: 28, scope: !1608)
!1623 = !DILocation(line: 969, column: 38, scope: !1608)
!1624 = !DILocation(line: 969, column: 50, scope: !1608)
!1625 = !DILocation(line: 969, column: 3, scope: !1608)
!1626 = !DILocation(line: 971, column: 32, scope: !1608)
!1627 = !DILocation(line: 971, column: 43, scope: !1608)
!1628 = !DILocation(line: 971, column: 15, scope: !1608)
!1629 = !DILocation(line: 971, column: 13, scope: !1608)
!1630 = !DILocation(line: 972, column: 2, scope: !1608)
!1631 = !DILocation(line: 972, column: 11, scope: !1632)
!1632 = !DILexicalBlockFile(scope: !204, file: !1, discriminator: 1)
!1633 = !DILocation(line: 972, column: 21, scope: !1632)
!1634 = !DILocation(line: 972, column: 2, scope: !1632)
!1635 = !DILocation(line: 974, column: 9, scope: !204)
!1636 = !DILocation(line: 974, column: 2, scope: !204)
!1637 = !DILocation(line: 975, column: 1, scope: !204)
!1638 = !DILocalVariable(name: "src", arg: 1, scope: !323, file: !1, line: 880, type: !52)
!1639 = !DILocation(line: 880, column: 38, scope: !323)
!1640 = !DILocalVariable(name: "allocator", arg: 2, scope: !323, file: !1, line: 880, type: !147)
!1641 = !DILocation(line: 880, column: 59, scope: !323)
!1642 = !DILocalVariable(name: "dest", scope: !323, file: !1, line: 882, type: !130)
!1643 = !DILocation(line: 882, column: 16, scope: !323)
!1644 = !DILocalVariable(name: "destg", scope: !323, file: !1, line: 883, type: !131)
!1645 = !DILocation(line: 883, column: 15, scope: !323)
!1646 = !DILocalVariable(name: "srcg", scope: !323, file: !1, line: 884, type: !131)
!1647 = !DILocation(line: 884, column: 15, scope: !323)
!1648 = !DILocalVariable(name: "i", scope: !323, file: !1, line: 885, type: !49)
!1649 = !DILocation(line: 885, column: 9, scope: !323)
!1650 = !DILocation(line: 888, column: 6, scope: !1651)
!1651 = distinct !DILexicalBlock(scope: !323, file: !1, line: 888, column: 6)
!1652 = !DILocation(line: 888, column: 11, scope: !1651)
!1653 = !DILocation(line: 888, column: 24, scope: !1651)
!1654 = !DILocation(line: 888, column: 6, scope: !323)
!1655 = !DILocation(line: 889, column: 3, scope: !1651)
!1656 = !DILocation(line: 892, column: 27, scope: !323)
!1657 = !DILocation(line: 892, column: 32, scope: !323)
!1658 = !DILocation(line: 892, column: 37, scope: !323)
!1659 = !DILocation(line: 893, column: 4, scope: !323)
!1660 = !DILocation(line: 893, column: 9, scope: !323)
!1661 = !DILocation(line: 893, column: 14, scope: !323)
!1662 = !DILocation(line: 893, column: 33, scope: !323)
!1663 = !DILocation(line: 893, column: 38, scope: !323)
!1664 = !DILocation(line: 894, column: 4, scope: !323)
!1665 = !DILocation(line: 894, column: 9, scope: !323)
!1666 = !DILocation(line: 894, column: 28, scope: !323)
!1667 = !DILocation(line: 892, column: 9, scope: !323)
!1668 = !DILocation(line: 892, column: 7, scope: !323)
!1669 = !DILocation(line: 898, column: 6, scope: !1670)
!1670 = distinct !DILexicalBlock(scope: !323, file: !1, line: 898, column: 6)
!1671 = !DILocation(line: 898, column: 11, scope: !1670)
!1672 = !DILocation(line: 898, column: 19, scope: !1670)
!1673 = !DILocation(line: 898, column: 22, scope: !1674)
!1674 = !DILexicalBlockFile(scope: !1670, file: !1, discriminator: 1)
!1675 = !DILocation(line: 898, column: 27, scope: !1674)
!1676 = !DILocation(line: 898, column: 34, scope: !1674)
!1677 = !DILocation(line: 898, column: 43, scope: !1674)
!1678 = !DILocation(line: 898, column: 6, scope: !1674)
!1679 = !DILocation(line: 899, column: 10, scope: !1670)
!1680 = !DILocation(line: 899, column: 3, scope: !1670)
!1681 = !DILocation(line: 902, column: 23, scope: !323)
!1682 = !DILocation(line: 902, column: 28, scope: !323)
!1683 = !DILocation(line: 902, column: 2, scope: !323)
!1684 = !DILocation(line: 902, column: 8, scope: !323)
!1685 = !DILocation(line: 902, column: 21, scope: !323)
!1686 = !DILocation(line: 903, column: 26, scope: !323)
!1687 = !DILocation(line: 903, column: 31, scope: !323)
!1688 = !DILocation(line: 903, column: 2, scope: !323)
!1689 = !DILocation(line: 903, column: 8, scope: !323)
!1690 = !DILocation(line: 903, column: 24, scope: !323)
!1691 = !DILocation(line: 904, column: 2, scope: !323)
!1692 = !DILocation(line: 904, column: 8, scope: !323)
!1693 = !DILocation(line: 904, column: 23, scope: !323)
!1694 = !DILocation(line: 904, column: 28, scope: !323)
!1695 = !DILocation(line: 905, column: 25, scope: !323)
!1696 = !DILocation(line: 905, column: 30, scope: !323)
!1697 = !DILocation(line: 905, column: 2, scope: !323)
!1698 = !DILocation(line: 905, column: 8, scope: !323)
!1699 = !DILocation(line: 905, column: 23, scope: !323)
!1700 = !DILocation(line: 911, column: 6, scope: !323)
!1701 = !DILocation(line: 911, column: 11, scope: !323)
!1702 = !DILocation(line: 911, column: 24, scope: !323)
!1703 = !DILocation(line: 911, column: 4, scope: !323)
!1704 = !DILocation(line: 912, column: 4, scope: !323)
!1705 = !DILocation(line: 910, column: 10, scope: !323)
!1706 = !DILocation(line: 910, column: 8, scope: !323)
!1707 = !DILocation(line: 913, column: 6, scope: !1708)
!1708 = distinct !DILexicalBlock(scope: !323, file: !1, line: 913, column: 6)
!1709 = !DILocation(line: 913, column: 12, scope: !1708)
!1710 = !DILocation(line: 913, column: 6, scope: !323)
!1711 = !DILocation(line: 914, column: 20, scope: !1712)
!1712 = distinct !DILexicalBlock(scope: !1708, file: !1, line: 913, column: 21)
!1713 = !DILocation(line: 914, column: 26, scope: !1712)
!1714 = !DILocation(line: 914, column: 3, scope: !1712)
!1715 = !DILocation(line: 915, column: 3, scope: !1712)
!1716 = !DILocation(line: 919, column: 2, scope: !323)
!1717 = !DILocation(line: 919, column: 9, scope: !323)
!1718 = !DILocation(line: 919, column: 14, scope: !323)
!1719 = !DILocation(line: 919, column: 32, scope: !323)
!1720 = !DILocation(line: 920, column: 2, scope: !323)
!1721 = !DILocation(line: 920, column: 9, scope: !323)
!1722 = !DILocation(line: 920, column: 14, scope: !323)
!1723 = !DILocation(line: 920, column: 30, scope: !323)
!1724 = !DILocation(line: 921, column: 2, scope: !323)
!1725 = !DILocation(line: 921, column: 9, scope: !323)
!1726 = !DILocation(line: 921, column: 21, scope: !323)
!1727 = !DILocation(line: 922, column: 21, scope: !323)
!1728 = !DILocation(line: 922, column: 26, scope: !323)
!1729 = !DILocation(line: 922, column: 2, scope: !323)
!1730 = !DILocation(line: 922, column: 9, scope: !323)
!1731 = !DILocation(line: 922, column: 19, scope: !323)
!1732 = !DILocation(line: 923, column: 16, scope: !323)
!1733 = !DILocation(line: 923, column: 21, scope: !323)
!1734 = !DILocation(line: 923, column: 34, scope: !323)
!1735 = !DILocation(line: 923, column: 2, scope: !323)
!1736 = !DILocation(line: 923, column: 9, scope: !323)
!1737 = !DILocation(line: 923, column: 14, scope: !323)
!1738 = !DILocation(line: 926, column: 25, scope: !323)
!1739 = !DILocation(line: 926, column: 30, scope: !323)
!1740 = !DILocation(line: 926, column: 37, scope: !323)
!1741 = !DILocation(line: 926, column: 9, scope: !323)
!1742 = !DILocation(line: 926, column: 7, scope: !323)
!1743 = !DILocation(line: 927, column: 2, scope: !323)
!1744 = !DILocation(line: 928, column: 10, scope: !1745)
!1745 = distinct !DILexicalBlock(scope: !323, file: !1, line: 927, column: 5)
!1746 = !DILocation(line: 928, column: 17, scope: !1745)
!1747 = !DILocation(line: 928, column: 27, scope: !1745)
!1748 = !DILocation(line: 928, column: 25, scope: !1745)
!1749 = !DILocation(line: 928, column: 3, scope: !1745)
!1750 = !DILocation(line: 928, column: 30, scope: !1745)
!1751 = !DILocation(line: 928, column: 36, scope: !1745)
!1752 = !DILocation(line: 929, column: 6, scope: !1745)
!1753 = !DILocation(line: 929, column: 12, scope: !1745)
!1754 = !DILocation(line: 929, column: 17, scope: !1745)
!1755 = !DILocation(line: 929, column: 22, scope: !1745)
!1756 = !DILocation(line: 930, column: 8, scope: !1745)
!1757 = !DILocation(line: 930, column: 14, scope: !1745)
!1758 = !DILocation(line: 930, column: 19, scope: !1745)
!1759 = !DILocation(line: 930, column: 5, scope: !1745)
!1760 = !DILocation(line: 931, column: 27, scope: !1745)
!1761 = !DILocation(line: 931, column: 33, scope: !1745)
!1762 = !DILocation(line: 931, column: 10, scope: !1745)
!1763 = !DILocation(line: 931, column: 8, scope: !1745)
!1764 = !DILocation(line: 932, column: 2, scope: !1745)
!1765 = !DILocation(line: 932, column: 11, scope: !1766)
!1766 = !DILexicalBlockFile(scope: !323, file: !1, discriminator: 1)
!1767 = !DILocation(line: 932, column: 16, scope: !1766)
!1768 = !DILocation(line: 932, column: 2, scope: !1766)
!1769 = !DILocation(line: 934, column: 2, scope: !323)
!1770 = !DILocation(line: 934, column: 2, scope: !1766)
!1771 = !DILocation(line: 934, column: 2, scope: !1772)
!1772 = !DILexicalBlockFile(scope: !323, file: !1, discriminator: 2)
!1773 = !DILocation(line: 934, column: 2, scope: !1774)
!1774 = !DILexicalBlockFile(scope: !323, file: !1, discriminator: 3)
!1775 = !DILocation(line: 937, column: 21, scope: !323)
!1776 = !DILocation(line: 937, column: 27, scope: !323)
!1777 = !DILocation(line: 937, column: 36, scope: !323)
!1778 = !DILocation(line: 937, column: 43, scope: !323)
!1779 = !DILocation(line: 937, column: 2, scope: !323)
!1780 = !DILocation(line: 939, column: 9, scope: !323)
!1781 = !DILocation(line: 939, column: 2, scope: !323)
!1782 = !DILocation(line: 940, column: 1, scope: !323)
!1783 = !DILocalVariable(name: "node", arg: 1, scope: !326, file: !1, line: 298, type: !329)
!1784 = !DILocation(line: 298, column: 40, scope: !326)
!1785 = !DILocation(line: 300, column: 6, scope: !1786)
!1786 = distinct !DILexicalBlock(scope: !326, file: !1, line: 300, column: 6)
!1787 = !DILocation(line: 300, column: 12, scope: !1786)
!1788 = !DILocation(line: 300, column: 18, scope: !1786)
!1789 = !DILocation(line: 300, column: 6, scope: !326)
!1790 = !DILocation(line: 301, column: 10, scope: !1791)
!1791 = distinct !DILexicalBlock(scope: !1786, file: !1, line: 300, column: 27)
!1792 = !DILocation(line: 301, column: 16, scope: !1791)
!1793 = !DILocation(line: 301, column: 8, scope: !1791)
!1794 = !DILocation(line: 302, column: 3, scope: !1791)
!1795 = !DILocation(line: 302, column: 10, scope: !1796)
!1796 = !DILexicalBlockFile(scope: !1791, file: !1, discriminator: 1)
!1797 = !DILocation(line: 302, column: 16, scope: !1796)
!1798 = !DILocation(line: 302, column: 21, scope: !1796)
!1799 = !DILocation(line: 302, column: 3, scope: !1796)
!1800 = !DILocation(line: 303, column: 11, scope: !1791)
!1801 = !DILocation(line: 303, column: 17, scope: !1791)
!1802 = !DILocation(line: 303, column: 9, scope: !1791)
!1803 = !DILocation(line: 302, column: 3, scope: !1804)
!1804 = !DILexicalBlockFile(scope: !1791, file: !1, discriminator: 2)
!1805 = !DILocation(line: 305, column: 19, scope: !1791)
!1806 = !DILocation(line: 305, column: 10, scope: !1791)
!1807 = !DILocation(line: 305, column: 3, scope: !1791)
!1808 = !DILocation(line: 308, column: 2, scope: !326)
!1809 = !DILocation(line: 308, column: 9, scope: !1810)
!1810 = !DILexicalBlockFile(scope: !326, file: !1, discriminator: 1)
!1811 = !DILocation(line: 308, column: 15, scope: !1810)
!1812 = !DILocation(line: 308, column: 22, scope: !1810)
!1813 = !DILocation(line: 308, column: 30, scope: !1810)
!1814 = !DILocation(line: 308, column: 33, scope: !1815)
!1815 = !DILexicalBlockFile(scope: !326, file: !1, discriminator: 2)
!1816 = !DILocation(line: 308, column: 39, scope: !1815)
!1817 = !DILocation(line: 308, column: 47, scope: !1815)
!1818 = !DILocation(line: 308, column: 56, scope: !1815)
!1819 = !DILocation(line: 308, column: 53, scope: !1815)
!1820 = !DILocation(line: 308, column: 2, scope: !1821)
!1821 = !DILexicalBlockFile(scope: !326, file: !1, discriminator: 3)
!1822 = !DILocation(line: 309, column: 10, scope: !326)
!1823 = !DILocation(line: 309, column: 16, scope: !326)
!1824 = !DILocation(line: 309, column: 8, scope: !326)
!1825 = !DILocation(line: 308, column: 2, scope: !1826)
!1826 = !DILexicalBlockFile(scope: !326, file: !1, discriminator: 4)
!1827 = !DILocation(line: 311, column: 18, scope: !326)
!1828 = !DILocation(line: 311, column: 24, scope: !326)
!1829 = !DILocation(line: 311, column: 9, scope: !326)
!1830 = !DILocation(line: 311, column: 2, scope: !326)
!1831 = !DILocation(line: 312, column: 1, scope: !326)
!1832 = !DILocalVariable(name: "iter", arg: 1, scope: !207, file: !1, line: 1100, type: !210)
!1833 = !DILocation(line: 1100, column: 39, scope: !207)
!1834 = !DILocalVariable(name: "i", arg: 2, scope: !207, file: !1, line: 1100, type: !173)
!1835 = !DILocation(line: 1100, column: 63, scope: !207)
!1836 = !DILocation(line: 1102, column: 33, scope: !207)
!1837 = !DILocation(line: 1102, column: 2, scope: !207)
!1838 = !DILocation(line: 1102, column: 8, scope: !207)
!1839 = !DILocation(line: 1102, column: 29, scope: !207)
!1840 = !DILocation(line: 1102, column: 31, scope: !207)
!1841 = !DILocation(line: 1103, column: 25, scope: !207)
!1842 = !DILocation(line: 1103, column: 2, scope: !207)
!1843 = !DILocation(line: 1104, column: 2, scope: !207)
!1844 = !DILocalVariable(name: "iter", arg: 1, scope: !263, file: !1, line: 1109, type: !210)
!1845 = !DILocation(line: 1109, column: 41, scope: !263)
!1846 = !DILocation(line: 1111, column: 2, scope: !263)
!1847 = !DILocation(line: 1111, column: 8, scope: !263)
!1848 = !DILocation(line: 1111, column: 30, scope: !263)
!1849 = !DILocation(line: 1111, column: 32, scope: !263)
!1850 = !DILocation(line: 1112, column: 2, scope: !263)
!1851 = !DILocation(line: 1112, column: 8, scope: !263)
!1852 = !DILocation(line: 1112, column: 29, scope: !263)
!1853 = !DILocation(line: 1112, column: 31, scope: !263)
!1854 = !DILocation(line: 1113, column: 2, scope: !263)
!1855 = !DILocation(line: 1113, column: 8, scope: !263)
!1856 = !DILocation(line: 1113, column: 30, scope: !263)
!1857 = !DILocation(line: 1113, column: 32, scope: !263)
!1858 = !DILocation(line: 1114, column: 2, scope: !263)
!1859 = !DILocation(line: 1114, column: 8, scope: !263)
!1860 = !DILocation(line: 1114, column: 30, scope: !263)
!1861 = !DILocation(line: 1114, column: 32, scope: !263)
!1862 = !DILocation(line: 1115, column: 2, scope: !263)
!1863 = !DILocalVariable(name: "iter", arg: 1, scope: !266, file: !1, line: 1120, type: !210)
!1864 = !DILocation(line: 1120, column: 39, scope: !266)
!1865 = !DILocalVariable(name: "mode", arg: 2, scope: !266, file: !1, line: 1120, type: !269)
!1866 = !DILocation(line: 1120, column: 66, scope: !266)
!1867 = !DILocalVariable(name: "i", scope: !266, file: !1, line: 1122, type: !173)
!1868 = !DILocation(line: 1122, column: 20, scope: !266)
!1869 = !DILocalVariable(name: "stream", scope: !266, file: !1, line: 1123, type: !52)
!1870 = !DILocation(line: 1123, column: 22, scope: !266)
!1871 = !DILocalVariable(name: "group", scope: !266, file: !1, line: 1124, type: !112)
!1872 = !DILocation(line: 1124, column: 21, scope: !266)
!1873 = !DILocalVariable(name: "record", scope: !266, file: !1, line: 1125, type: !49)
!1874 = !DILocation(line: 1125, column: 9, scope: !266)
!1875 = !DILocation(line: 1128, column: 21, scope: !1876)
!1876 = distinct !DILexicalBlock(scope: !266, file: !1, line: 1128, column: 6)
!1877 = !DILocation(line: 1128, column: 27, scope: !1876)
!1878 = !DILocation(line: 1128, column: 6, scope: !266)
!1879 = !DILocation(line: 1129, column: 3, scope: !1876)
!1880 = !DILocation(line: 1131, column: 6, scope: !266)
!1881 = !DILocation(line: 1131, column: 12, scope: !266)
!1882 = !DILocation(line: 1131, column: 33, scope: !266)
!1883 = !DILocation(line: 1131, column: 4, scope: !266)
!1884 = !DILocation(line: 1132, column: 11, scope: !266)
!1885 = !DILocation(line: 1132, column: 17, scope: !266)
!1886 = !DILocation(line: 1132, column: 39, scope: !266)
!1887 = !DILocation(line: 1132, column: 9, scope: !266)
!1888 = !DILocation(line: 1133, column: 8, scope: !266)
!1889 = !DILocation(line: 1134, column: 11, scope: !266)
!1890 = !DILocation(line: 1134, column: 17, scope: !266)
!1891 = !DILocation(line: 1134, column: 39, scope: !266)
!1892 = !DILocation(line: 1134, column: 9, scope: !266)
!1893 = !DILocation(line: 1139, column: 6, scope: !1894)
!1894 = distinct !DILexicalBlock(scope: !266, file: !1, line: 1139, column: 6)
!1895 = !DILocation(line: 1139, column: 11, scope: !1894)
!1896 = !DILocation(line: 1139, column: 6, scope: !266)
!1897 = !DILocation(line: 1142, column: 11, scope: !1898)
!1898 = distinct !DILexicalBlock(scope: !1894, file: !1, line: 1139, column: 38)
!1899 = !DILocation(line: 1142, column: 17, scope: !1898)
!1900 = !DILocation(line: 1142, column: 39, scope: !1898)
!1901 = !DILocation(line: 1142, column: 3, scope: !1898)
!1902 = !DILocation(line: 1144, column: 12, scope: !1903)
!1903 = distinct !DILexicalBlock(scope: !1898, file: !1, line: 1142, column: 42)
!1904 = !DILocation(line: 1144, column: 18, scope: !1903)
!1905 = !DILocation(line: 1144, column: 39, scope: !1903)
!1906 = !DILocation(line: 1144, column: 10, scope: !1903)
!1907 = !DILocation(line: 1145, column: 4, scope: !1903)
!1908 = !DILocation(line: 1148, column: 28, scope: !1903)
!1909 = !DILocation(line: 1148, column: 34, scope: !1903)
!1910 = !DILocation(line: 1148, column: 55, scope: !1903)
!1911 = !DILocation(line: 1148, column: 12, scope: !1903)
!1912 = !DILocation(line: 1148, column: 10, scope: !1903)
!1913 = !DILocation(line: 1149, column: 4, scope: !1903)
!1914 = !DILocation(line: 1153, column: 6, scope: !1903)
!1915 = !DILocation(line: 1153, column: 14, scope: !1903)
!1916 = !DILocation(line: 1153, column: 21, scope: !1903)
!1917 = !DILocation(line: 1152, column: 12, scope: !1903)
!1918 = !DILocation(line: 1152, column: 10, scope: !1903)
!1919 = !DILocation(line: 1154, column: 4, scope: !1903)
!1920 = !DILocation(line: 1156, column: 2, scope: !1898)
!1921 = !DILocation(line: 1139, column: 14, scope: !1922)
!1922 = !DILexicalBlockFile(scope: !1894, file: !1, discriminator: 1)
!1923 = !DILocation(line: 1159, column: 6, scope: !1924)
!1924 = distinct !DILexicalBlock(scope: !266, file: !1, line: 1159, column: 6)
!1925 = !DILocation(line: 1159, column: 13, scope: !1924)
!1926 = !DILocation(line: 1159, column: 6, scope: !266)
!1927 = !DILocation(line: 1162, column: 35, scope: !1928)
!1928 = distinct !DILexicalBlock(scope: !1924, file: !1, line: 1159, column: 22)
!1929 = !DILocation(line: 1162, column: 38, scope: !1928)
!1930 = !DILocation(line: 1162, column: 46, scope: !1928)
!1931 = !DILocation(line: 1162, column: 12, scope: !1928)
!1932 = !DILocation(line: 1162, column: 10, scope: !1928)
!1933 = !DILocation(line: 1163, column: 7, scope: !1934)
!1934 = distinct !DILexicalBlock(scope: !1928, file: !1, line: 1163, column: 7)
!1935 = !DILocation(line: 1163, column: 12, scope: !1934)
!1936 = !DILocation(line: 1163, column: 7, scope: !1928)
!1937 = !DILocation(line: 1167, column: 4, scope: !1938)
!1938 = distinct !DILexicalBlock(scope: !1934, file: !1, line: 1163, column: 38)
!1939 = !DILocation(line: 1167, column: 11, scope: !1940)
!1940 = !DILexicalBlockFile(scope: !1938, file: !1, discriminator: 1)
!1941 = !DILocation(line: 1167, column: 19, scope: !1940)
!1942 = !DILocation(line: 1167, column: 26, scope: !1940)
!1943 = !DILocation(line: 1167, column: 35, scope: !1940)
!1944 = !DILocation(line: 1167, column: 4, scope: !1940)
!1945 = !DILocation(line: 1168, column: 31, scope: !1946)
!1946 = distinct !DILexicalBlock(scope: !1938, file: !1, line: 1167, column: 44)
!1947 = !DILocation(line: 1168, column: 39, scope: !1946)
!1948 = !DILocation(line: 1168, column: 14, scope: !1946)
!1949 = !DILocation(line: 1168, column: 12, scope: !1946)
!1950 = !DILocation(line: 1169, column: 9, scope: !1951)
!1951 = distinct !DILexicalBlock(scope: !1946, file: !1, line: 1169, column: 9)
!1952 = !DILocation(line: 1169, column: 16, scope: !1951)
!1953 = !DILocation(line: 1169, column: 9, scope: !1946)
!1954 = !DILocation(line: 1170, column: 6, scope: !1951)
!1955 = !DILocation(line: 1167, column: 4, scope: !1956)
!1956 = !DILexicalBlockFile(scope: !1938, file: !1, discriminator: 2)
!1957 = !DILocation(line: 1172, column: 3, scope: !1938)
!1958 = !DILocation(line: 1175, column: 33, scope: !1928)
!1959 = !DILocation(line: 1175, column: 41, scope: !1928)
!1960 = !DILocation(line: 1175, column: 48, scope: !1928)
!1961 = !DILocation(line: 1175, column: 11, scope: !1928)
!1962 = !DILocation(line: 1175, column: 9, scope: !1928)
!1963 = !DILocation(line: 1176, column: 10, scope: !1928)
!1964 = !DILocation(line: 1178, column: 2, scope: !1928)
!1965 = !DILocation(line: 1178, column: 13, scope: !1966)
!1966 = !DILexicalBlockFile(scope: !1967, file: !1, discriminator: 1)
!1967 = distinct !DILexicalBlock(scope: !1924, file: !1, line: 1178, column: 13)
!1968 = !DILocation(line: 1178, column: 19, scope: !1966)
!1969 = !DILocation(line: 1178, column: 27, scope: !1966)
!1970 = !DILocation(line: 1178, column: 30, scope: !1971)
!1971 = !DILexicalBlockFile(scope: !1967, file: !1, discriminator: 2)
!1972 = !DILocation(line: 1178, column: 39, scope: !1971)
!1973 = !DILocation(line: 1178, column: 46, scope: !1971)
!1974 = !DILocation(line: 1178, column: 37, scope: !1971)
!1975 = !DILocation(line: 1178, column: 13, scope: !1971)
!1976 = !DILocation(line: 1180, column: 3, scope: !1977)
!1977 = distinct !DILexicalBlock(scope: !1967, file: !1, line: 1178, column: 52)
!1978 = !DILocation(line: 1182, column: 2, scope: !1977)
!1979 = !DILocation(line: 1185, column: 10, scope: !1980)
!1980 = distinct !DILexicalBlock(scope: !1967, file: !1, line: 1182, column: 9)
!1981 = !DILocation(line: 1189, column: 7, scope: !1982)
!1982 = distinct !DILexicalBlock(scope: !1980, file: !1, line: 1189, column: 7)
!1983 = !DILocation(line: 1189, column: 13, scope: !1982)
!1984 = !DILocation(line: 1189, column: 7, scope: !1980)
!1985 = !DILocation(line: 1190, column: 29, scope: !1982)
!1986 = !DILocation(line: 1190, column: 36, scope: !1982)
!1987 = !DILocation(line: 1190, column: 12, scope: !1982)
!1988 = !DILocation(line: 1190, column: 10, scope: !1982)
!1989 = !DILocation(line: 1190, column: 4, scope: !1982)
!1990 = !DILocation(line: 1192, column: 7, scope: !1991)
!1991 = distinct !DILexicalBlock(scope: !1980, file: !1, line: 1192, column: 7)
!1992 = !DILocation(line: 1192, column: 13, scope: !1991)
!1993 = !DILocation(line: 1192, column: 7, scope: !1980)
!1994 = !DILocation(line: 1196, column: 4, scope: !1995)
!1995 = distinct !DILexicalBlock(scope: !1991, file: !1, line: 1192, column: 22)
!1996 = !DILocation(line: 1197, column: 31, scope: !1997)
!1997 = distinct !DILexicalBlock(scope: !1995, file: !1, line: 1196, column: 7)
!1998 = !DILocation(line: 1197, column: 39, scope: !1997)
!1999 = !DILocation(line: 1197, column: 14, scope: !1997)
!2000 = !DILocation(line: 1197, column: 12, scope: !1997)
!2001 = !DILocation(line: 1198, column: 9, scope: !2002)
!2002 = distinct !DILexicalBlock(scope: !1997, file: !1, line: 1198, column: 9)
!2003 = !DILocation(line: 1198, column: 16, scope: !2002)
!2004 = !DILocation(line: 1198, column: 9, scope: !1997)
!2005 = !DILocation(line: 1199, column: 6, scope: !2002)
!2006 = !DILocation(line: 1200, column: 4, scope: !1997)
!2007 = !DILocation(line: 1200, column: 13, scope: !2008)
!2008 = !DILexicalBlockFile(scope: !1995, file: !1, discriminator: 1)
!2009 = !DILocation(line: 1200, column: 18, scope: !2008)
!2010 = !DILocation(line: 1201, column: 6, scope: !1995)
!2011 = !DILocation(line: 1201, column: 9, scope: !2008)
!2012 = !DILocation(line: 1201, column: 17, scope: !2008)
!2013 = !DILocation(line: 1201, column: 24, scope: !2008)
!2014 = !DILocation(line: 1201, column: 33, scope: !2008)
!2015 = !DILocation(line: 1200, column: 4, scope: !2016)
!2016 = !DILexicalBlockFile(scope: !1997, file: !1, discriminator: 2)
!2017 = !DILocation(line: 1204, column: 6, scope: !1995)
!2018 = !DILocation(line: 1204, column: 14, scope: !1995)
!2019 = !DILocation(line: 1204, column: 21, scope: !1995)
!2020 = !DILocation(line: 1203, column: 12, scope: !1995)
!2021 = !DILocation(line: 1203, column: 10, scope: !1995)
!2022 = !DILocation(line: 1205, column: 3, scope: !1995)
!2023 = !DILocation(line: 1208, column: 6, scope: !2024)
!2024 = distinct !DILexicalBlock(scope: !266, file: !1, line: 1208, column: 6)
!2025 = !DILocation(line: 1208, column: 11, scope: !2024)
!2026 = !DILocation(line: 1208, column: 6, scope: !266)
!2027 = !DILocation(line: 1211, column: 7, scope: !2028)
!2028 = distinct !DILexicalBlock(scope: !2029, file: !1, line: 1211, column: 7)
!2029 = distinct !DILexicalBlock(scope: !2024, file: !1, line: 1208, column: 46)
!2030 = !DILocation(line: 1211, column: 14, scope: !2028)
!2031 = !DILocation(line: 1211, column: 7, scope: !2029)
!2032 = !DILocation(line: 1212, column: 8, scope: !2033)
!2033 = distinct !DILexicalBlock(scope: !2034, file: !1, line: 1212, column: 8)
!2034 = distinct !DILexicalBlock(scope: !2028, file: !1, line: 1211, column: 20)
!2035 = !DILocation(line: 1212, column: 15, scope: !2033)
!2036 = !DILocation(line: 1212, column: 20, scope: !2033)
!2037 = !DILocation(line: 1213, column: 9, scope: !2033)
!2038 = !DILocation(line: 1213, column: 16, scope: !2033)
!2039 = !DILocation(line: 1213, column: 27, scope: !2033)
!2040 = !DILocation(line: 1213, column: 6, scope: !2033)
!2041 = !DILocation(line: 1212, column: 8, scope: !2034)
!2042 = !DILocation(line: 1214, column: 5, scope: !2033)
!2043 = !DILocation(line: 1215, column: 3, scope: !2034)
!2044 = !DILocation(line: 1215, column: 29, scope: !2045)
!2045 = !DILexicalBlockFile(scope: !2046, file: !1, discriminator: 1)
!2046 = distinct !DILexicalBlock(scope: !2028, file: !1, line: 1215, column: 14)
!2047 = !DILocation(line: 1215, column: 36, scope: !2045)
!2048 = !DILocation(line: 1215, column: 14, scope: !2045)
!2049 = !DILocation(line: 1215, column: 21, scope: !2045)
!2050 = !DILocation(line: 1215, column: 41, scope: !2045)
!2051 = !DILocation(line: 1216, column: 23, scope: !2046)
!2052 = !DILocation(line: 1216, column: 8, scope: !2046)
!2053 = !DILocation(line: 1216, column: 15, scope: !2046)
!2054 = !DILocation(line: 1216, column: 31, scope: !2046)
!2055 = !DILocation(line: 1216, column: 5, scope: !2046)
!2056 = !DILocation(line: 1217, column: 4, scope: !2057)
!2057 = distinct !DILexicalBlock(scope: !2046, file: !1, line: 1216, column: 49)
!2058 = !DILocation(line: 1219, column: 2, scope: !2029)
!2059 = !DILocation(line: 1221, column: 34, scope: !266)
!2060 = !DILocation(line: 1221, column: 2, scope: !266)
!2061 = !DILocation(line: 1221, column: 8, scope: !266)
!2062 = !DILocation(line: 1221, column: 30, scope: !266)
!2063 = !DILocation(line: 1221, column: 32, scope: !266)
!2064 = !DILocation(line: 1222, column: 33, scope: !266)
!2065 = !DILocation(line: 1222, column: 2, scope: !266)
!2066 = !DILocation(line: 1222, column: 8, scope: !266)
!2067 = !DILocation(line: 1222, column: 29, scope: !266)
!2068 = !DILocation(line: 1222, column: 31, scope: !266)
!2069 = !DILocation(line: 1223, column: 34, scope: !266)
!2070 = !DILocation(line: 1223, column: 2, scope: !266)
!2071 = !DILocation(line: 1223, column: 8, scope: !266)
!2072 = !DILocation(line: 1223, column: 30, scope: !266)
!2073 = !DILocation(line: 1223, column: 32, scope: !266)
!2074 = !DILocation(line: 1225, column: 16, scope: !266)
!2075 = !DILocation(line: 1225, column: 2, scope: !266)
!2076 = !DILocation(line: 1227, column: 2, scope: !266)
!2077 = !DILocation(line: 1228, column: 1, scope: !266)
!2078 = !DILocalVariable(name: "iter", arg: 1, scope: !331, file: !1, line: 997, type: !210)
!2079 = !DILocation(line: 997, column: 32, scope: !331)
!2080 = !DILocalVariable(name: "i", scope: !331, file: !1, line: 999, type: !173)
!2081 = !DILocation(line: 999, column: 20, scope: !331)
!2082 = !DILocation(line: 999, column: 24, scope: !331)
!2083 = !DILocation(line: 999, column: 30, scope: !331)
!2084 = !DILocation(line: 999, column: 51, scope: !331)
!2085 = !DILocalVariable(name: "stream", scope: !331, file: !1, line: 1000, type: !52)
!2086 = !DILocation(line: 1000, column: 22, scope: !331)
!2087 = !DILocation(line: 1000, column: 31, scope: !331)
!2088 = !DILocation(line: 1000, column: 37, scope: !331)
!2089 = !DILocation(line: 1000, column: 59, scope: !331)
!2090 = !DILocalVariable(name: "group", scope: !331, file: !1, line: 1001, type: !112)
!2091 = !DILocation(line: 1001, column: 21, scope: !331)
!2092 = !DILocation(line: 1001, column: 29, scope: !331)
!2093 = !DILocation(line: 1001, column: 35, scope: !331)
!2094 = !DILocation(line: 1001, column: 56, scope: !331)
!2095 = !DILocalVariable(name: "record", scope: !331, file: !1, line: 1002, type: !691)
!2096 = !DILocation(line: 1002, column: 15, scope: !331)
!2097 = !DILocation(line: 1002, column: 24, scope: !331)
!2098 = !DILocation(line: 1002, column: 30, scope: !331)
!2099 = !DILocation(line: 1002, column: 52, scope: !331)
!2100 = !DILocation(line: 1007, column: 6, scope: !2101)
!2101 = distinct !DILexicalBlock(scope: !331, file: !1, line: 1007, column: 6)
!2102 = !DILocation(line: 1007, column: 12, scope: !2101)
!2103 = !DILocation(line: 1007, column: 6, scope: !331)
!2104 = !DILocation(line: 1009, column: 3, scope: !2105)
!2105 = distinct !DILexicalBlock(scope: !2101, file: !1, line: 1007, column: 21)
!2106 = !DILocation(line: 1009, column: 3, scope: !2107)
!2107 = !DILexicalBlockFile(scope: !2105, file: !1, discriminator: 1)
!2108 = !DILocation(line: 1009, column: 3, scope: !2109)
!2109 = !DILexicalBlockFile(scope: !2105, file: !1, discriminator: 2)
!2110 = !DILocation(line: 1009, column: 3, scope: !2111)
!2111 = !DILexicalBlockFile(scope: !2105, file: !1, discriminator: 3)
!2112 = !DILocation(line: 1010, column: 3, scope: !2105)
!2113 = !DILocation(line: 1010, column: 9, scope: !2105)
!2114 = !DILocation(line: 1010, column: 31, scope: !2105)
!2115 = !DILocation(line: 1010, column: 33, scope: !2105)
!2116 = !DILocation(line: 1012, column: 2, scope: !2105)
!2117 = !DILocation(line: 1012, column: 13, scope: !2118)
!2118 = !DILexicalBlockFile(scope: !2119, file: !1, discriminator: 1)
!2119 = distinct !DILexicalBlock(scope: !2101, file: !1, line: 1012, column: 13)
!2120 = !DILocation(line: 1012, column: 16, scope: !2118)
!2121 = !DILocation(line: 1012, column: 24, scope: !2118)
!2122 = !DILocation(line: 1012, column: 38, scope: !2118)
!2123 = !DILocation(line: 1012, column: 46, scope: !2118)
!2124 = !DILocation(line: 1012, column: 34, scope: !2118)
!2125 = !DILocation(line: 1013, column: 4, scope: !2119)
!2126 = !DILocation(line: 1013, column: 7, scope: !2118)
!2127 = !DILocation(line: 1013, column: 15, scope: !2118)
!2128 = !DILocation(line: 1013, column: 22, scope: !2118)
!2129 = !DILocation(line: 1013, column: 36, scope: !2118)
!2130 = !DILocation(line: 1013, column: 43, scope: !2118)
!2131 = !DILocation(line: 1013, column: 32, scope: !2118)
!2132 = !DILocation(line: 1012, column: 13, scope: !2133)
!2133 = !DILexicalBlockFile(scope: !2101, file: !1, discriminator: 2)
!2134 = !DILocation(line: 1015, column: 3, scope: !2135)
!2135 = distinct !DILexicalBlock(scope: !2119, file: !1, line: 1013, column: 49)
!2136 = !DILocation(line: 1015, column: 9, scope: !2135)
!2137 = !DILocation(line: 1015, column: 31, scope: !2135)
!2138 = !DILocation(line: 1015, column: 33, scope: !2135)
!2139 = !DILocation(line: 1017, column: 2, scope: !2135)
!2140 = !DILocation(line: 1017, column: 13, scope: !2141)
!2141 = !DILexicalBlockFile(scope: !2142, file: !1, discriminator: 1)
!2142 = distinct !DILexicalBlock(scope: !2119, file: !1, line: 1017, column: 13)
!2143 = !DILocation(line: 1017, column: 21, scope: !2141)
!2144 = !DILocation(line: 1017, column: 28, scope: !2141)
!2145 = !DILocation(line: 1017, column: 41, scope: !2141)
!2146 = !DILocation(line: 1017, column: 48, scope: !2141)
!2147 = !DILocation(line: 1017, column: 37, scope: !2141)
!2148 = !DILocation(line: 1021, column: 3, scope: !2149)
!2149 = distinct !DILexicalBlock(scope: !2142, file: !1, line: 1017, column: 54)
!2150 = !DILocation(line: 1021, column: 3, scope: !2151)
!2151 = !DILexicalBlockFile(scope: !2149, file: !1, discriminator: 1)
!2152 = !DILocation(line: 1021, column: 3, scope: !2153)
!2153 = !DILexicalBlockFile(scope: !2149, file: !1, discriminator: 2)
!2154 = !DILocation(line: 1021, column: 3, scope: !2155)
!2155 = !DILexicalBlockFile(scope: !2149, file: !1, discriminator: 3)
!2156 = !DILocation(line: 1022, column: 3, scope: !2149)
!2157 = !DILocation(line: 1022, column: 3, scope: !2151)
!2158 = !DILocation(line: 1022, column: 3, scope: !2153)
!2159 = !DILocation(line: 1022, column: 3, scope: !2155)
!2160 = !DILocation(line: 1023, column: 3, scope: !2149)
!2161 = !DILocation(line: 1023, column: 9, scope: !2149)
!2162 = !DILocation(line: 1023, column: 31, scope: !2149)
!2163 = !DILocation(line: 1023, column: 33, scope: !2149)
!2164 = !DILocation(line: 1024, column: 34, scope: !2149)
!2165 = !DILocation(line: 1024, column: 41, scope: !2149)
!2166 = !DILocation(line: 1024, column: 46, scope: !2149)
!2167 = !DILocation(line: 1024, column: 3, scope: !2149)
!2168 = !DILocation(line: 1024, column: 9, scope: !2149)
!2169 = !DILocation(line: 1024, column: 30, scope: !2149)
!2170 = !DILocation(line: 1024, column: 32, scope: !2149)
!2171 = !DILocation(line: 1026, column: 2, scope: !2149)
!2172 = !DILocation(line: 1028, column: 3, scope: !2173)
!2173 = distinct !DILexicalBlock(scope: !2142, file: !1, line: 1026, column: 9)
!2174 = !DILocation(line: 1028, column: 3, scope: !2175)
!2175 = !DILexicalBlockFile(scope: !2173, file: !1, discriminator: 1)
!2176 = !DILocation(line: 1028, column: 3, scope: !2177)
!2177 = !DILexicalBlockFile(scope: !2173, file: !1, discriminator: 2)
!2178 = !DILocation(line: 1028, column: 3, scope: !2179)
!2179 = !DILexicalBlockFile(scope: !2173, file: !1, discriminator: 3)
!2180 = !DILocation(line: 1029, column: 3, scope: !2173)
!2181 = !DILocation(line: 1029, column: 3, scope: !2175)
!2182 = !DILocation(line: 1029, column: 3, scope: !2177)
!2183 = !DILocation(line: 1029, column: 3, scope: !2179)
!2184 = !DILocation(line: 1030, column: 3, scope: !2173)
!2185 = !DILocation(line: 1030, column: 9, scope: !2173)
!2186 = !DILocation(line: 1030, column: 31, scope: !2173)
!2187 = !DILocation(line: 1030, column: 33, scope: !2173)
!2188 = !DILocation(line: 1031, column: 3, scope: !2173)
!2189 = !DILocation(line: 1031, column: 9, scope: !2173)
!2190 = !DILocation(line: 1031, column: 30, scope: !2173)
!2191 = !DILocation(line: 1031, column: 32, scope: !2173)
!2192 = !DILocation(line: 1034, column: 24, scope: !331)
!2193 = !DILocation(line: 1034, column: 32, scope: !331)
!2194 = !DILocation(line: 1034, column: 2, scope: !331)
!2195 = !DILocation(line: 1034, column: 8, scope: !331)
!2196 = !DILocation(line: 1034, column: 15, scope: !331)
!2197 = !DILocation(line: 1034, column: 22, scope: !331)
!2198 = !DILocation(line: 1035, column: 29, scope: !331)
!2199 = !DILocation(line: 1035, column: 37, scope: !331)
!2200 = !DILocation(line: 1035, column: 2, scope: !331)
!2201 = !DILocation(line: 1035, column: 8, scope: !331)
!2202 = !DILocation(line: 1035, column: 15, scope: !331)
!2203 = !DILocation(line: 1035, column: 27, scope: !331)
!2204 = !DILocation(line: 1036, column: 35, scope: !331)
!2205 = !DILocation(line: 1036, column: 43, scope: !331)
!2206 = !DILocation(line: 1036, column: 48, scope: !331)
!2207 = !DILocation(line: 1036, column: 2, scope: !331)
!2208 = !DILocation(line: 1036, column: 8, scope: !331)
!2209 = !DILocation(line: 1036, column: 15, scope: !331)
!2210 = !DILocation(line: 1036, column: 33, scope: !331)
!2211 = !DILocation(line: 1037, column: 37, scope: !331)
!2212 = !DILocation(line: 1037, column: 45, scope: !331)
!2213 = !DILocation(line: 1037, column: 50, scope: !331)
!2214 = !DILocation(line: 1037, column: 2, scope: !331)
!2215 = !DILocation(line: 1037, column: 8, scope: !331)
!2216 = !DILocation(line: 1037, column: 15, scope: !331)
!2217 = !DILocation(line: 1037, column: 35, scope: !331)
!2218 = !DILocation(line: 1041, column: 23, scope: !331)
!2219 = !DILocation(line: 1041, column: 31, scope: !331)
!2220 = !DILocation(line: 1041, column: 44, scope: !331)
!2221 = !DILocation(line: 1041, column: 52, scope: !331)
!2222 = !DILocation(line: 1041, column: 23, scope: !2223)
!2223 = !DILexicalBlockFile(scope: !331, file: !1, discriminator: 1)
!2224 = !DILocation(line: 1042, column: 14, scope: !331)
!2225 = !DILocation(line: 1042, column: 22, scope: !331)
!2226 = !DILocation(line: 1041, column: 23, scope: !2227)
!2227 = !DILexicalBlockFile(scope: !331, file: !1, discriminator: 2)
!2228 = !DILocation(line: 1041, column: 23, scope: !2229)
!2229 = !DILexicalBlockFile(scope: !331, file: !1, discriminator: 3)
!2230 = !DILocation(line: 1041, column: 2, scope: !2229)
!2231 = !DILocation(line: 1041, column: 8, scope: !2229)
!2232 = !DILocation(line: 1041, column: 15, scope: !2229)
!2233 = !DILocation(line: 1041, column: 21, scope: !2229)
!2234 = !DILocation(line: 1043, column: 25, scope: !331)
!2235 = !DILocation(line: 1043, column: 33, scope: !331)
!2236 = !DILocation(line: 1043, column: 2, scope: !331)
!2237 = !DILocation(line: 1043, column: 8, scope: !331)
!2238 = !DILocation(line: 1043, column: 15, scope: !331)
!2239 = !DILocation(line: 1043, column: 23, scope: !331)
!2240 = !DILocation(line: 1045, column: 6, scope: !2241)
!2241 = distinct !DILexicalBlock(scope: !331, file: !1, line: 1045, column: 6)
!2242 = !DILocation(line: 1045, column: 14, scope: !2241)
!2243 = !DILocation(line: 1045, column: 21, scope: !2241)
!2244 = !DILocation(line: 1045, column: 31, scope: !2241)
!2245 = !DILocation(line: 1045, column: 6, scope: !331)
!2246 = !DILocation(line: 1047, column: 34, scope: !2247)
!2247 = distinct !DILexicalBlock(scope: !2241, file: !1, line: 1045, column: 40)
!2248 = !DILocation(line: 1048, column: 5, scope: !2247)
!2249 = !DILocation(line: 1047, column: 3, scope: !2247)
!2250 = !DILocation(line: 1047, column: 9, scope: !2247)
!2251 = !DILocation(line: 1047, column: 16, scope: !2247)
!2252 = !DILocation(line: 1047, column: 32, scope: !2247)
!2253 = !DILocation(line: 1049, column: 3, scope: !2247)
!2254 = !DILocation(line: 1049, column: 9, scope: !2247)
!2255 = !DILocation(line: 1049, column: 16, scope: !2247)
!2256 = !DILocation(line: 1049, column: 34, scope: !2247)
!2257 = !DILocation(line: 1050, column: 2, scope: !2247)
!2258 = !DILocalVariable(name: "g", scope: !2259, file: !1, line: 1051, type: !112)
!2259 = distinct !DILexicalBlock(scope: !2241, file: !1, line: 1050, column: 9)
!2260 = !DILocation(line: 1051, column: 22, scope: !2259)
!2261 = !DILocation(line: 1052, column: 5, scope: !2259)
!2262 = !DILocation(line: 1052, column: 13, scope: !2259)
!2263 = !DILocation(line: 1052, column: 20, scope: !2259)
!2264 = !DILocation(line: 1051, column: 26, scope: !2259)
!2265 = !DILocation(line: 1056, column: 18, scope: !2259)
!2266 = !DILocation(line: 1056, column: 26, scope: !2259)
!2267 = !DILocation(line: 1057, column: 6, scope: !2259)
!2268 = !DILocation(line: 1057, column: 14, scope: !2259)
!2269 = !DILocation(line: 1056, column: 7, scope: !2259)
!2270 = !DILocation(line: 1056, column: 5, scope: !2259)
!2271 = !DILocation(line: 1058, column: 28, scope: !2259)
!2272 = !DILocation(line: 1058, column: 31, scope: !2259)
!2273 = !DILocation(line: 1058, column: 17, scope: !2259)
!2274 = !DILocation(line: 1058, column: 20, scope: !2259)
!2275 = !DILocation(line: 1058, column: 37, scope: !2259)
!2276 = !DILocation(line: 1058, column: 7, scope: !2259)
!2277 = !DILocation(line: 1058, column: 5, scope: !2259)
!2278 = !DILocation(line: 1055, column: 3, scope: !2259)
!2279 = !DILocation(line: 1055, column: 9, scope: !2259)
!2280 = !DILocation(line: 1055, column: 16, scope: !2259)
!2281 = !DILocation(line: 1055, column: 32, scope: !2259)
!2282 = !DILocation(line: 1060, column: 18, scope: !2259)
!2283 = !DILocation(line: 1060, column: 21, scope: !2259)
!2284 = !DILocation(line: 1060, column: 7, scope: !2259)
!2285 = !DILocation(line: 1060, column: 10, scope: !2259)
!2286 = !DILocation(line: 1060, column: 27, scope: !2259)
!2287 = !DILocation(line: 1059, column: 3, scope: !2259)
!2288 = !DILocation(line: 1059, column: 9, scope: !2259)
!2289 = !DILocation(line: 1059, column: 16, scope: !2259)
!2290 = !DILocation(line: 1060, column: 5, scope: !2259)
!2291 = !DILocation(line: 1063, column: 6, scope: !2292)
!2292 = distinct !DILexicalBlock(scope: !331, file: !1, line: 1063, column: 6)
!2293 = !DILocation(line: 1063, column: 12, scope: !2292)
!2294 = !DILocation(line: 1063, column: 6, scope: !331)
!2295 = !DILocation(line: 1064, column: 34, scope: !2296)
!2296 = distinct !DILexicalBlock(scope: !2292, file: !1, line: 1063, column: 21)
!2297 = !DILocation(line: 1064, column: 41, scope: !2296)
!2298 = !DILocation(line: 1064, column: 55, scope: !2296)
!2299 = !DILocation(line: 1064, column: 53, scope: !2296)
!2300 = !DILocation(line: 1064, column: 3, scope: !2296)
!2301 = !DILocation(line: 1064, column: 9, scope: !2296)
!2302 = !DILocation(line: 1064, column: 15, scope: !2296)
!2303 = !DILocation(line: 1064, column: 32, scope: !2296)
!2304 = !DILocation(line: 1065, column: 32, scope: !2296)
!2305 = !DILocation(line: 1065, column: 38, scope: !2296)
!2306 = !DILocation(line: 1065, column: 44, scope: !2296)
!2307 = !DILocation(line: 1066, column: 7, scope: !2296)
!2308 = !DILocation(line: 1066, column: 15, scope: !2296)
!2309 = !DILocation(line: 1066, column: 5, scope: !2296)
!2310 = !DILocation(line: 1065, column: 3, scope: !2296)
!2311 = !DILocation(line: 1065, column: 9, scope: !2296)
!2312 = !DILocation(line: 1065, column: 15, scope: !2296)
!2313 = !DILocation(line: 1065, column: 30, scope: !2296)
!2314 = !DILocation(line: 1069, column: 7, scope: !2296)
!2315 = !DILocation(line: 1069, column: 14, scope: !2296)
!2316 = !DILocation(line: 1069, column: 21, scope: !2317)
!2317 = !DILexicalBlockFile(scope: !2296, file: !1, discriminator: 1)
!2318 = !DILocation(line: 1069, column: 28, scope: !2317)
!2319 = !DILocation(line: 1069, column: 33, scope: !2317)
!2320 = !DILocation(line: 1069, column: 7, scope: !2317)
!2321 = !DILocation(line: 1071, column: 6, scope: !2296)
!2322 = !DILocation(line: 1071, column: 13, scope: !2296)
!2323 = !DILocation(line: 1070, column: 17, scope: !2296)
!2324 = !DILocation(line: 1070, column: 24, scope: !2296)
!2325 = !DILocation(line: 1071, column: 18, scope: !2296)
!2326 = !DILocation(line: 1070, column: 7, scope: !2296)
!2327 = !DILocation(line: 1069, column: 7, scope: !2328)
!2328 = !DILexicalBlockFile(scope: !2296, file: !1, discriminator: 2)
!2329 = !DILocation(line: 1069, column: 7, scope: !2330)
!2330 = !DILexicalBlockFile(scope: !2296, file: !1, discriminator: 3)
!2331 = !DILocation(line: 1068, column: 3, scope: !2296)
!2332 = !DILocation(line: 1068, column: 9, scope: !2296)
!2333 = !DILocation(line: 1068, column: 15, scope: !2296)
!2334 = !DILocation(line: 1069, column: 5, scope: !2330)
!2335 = !DILocation(line: 1073, column: 7, scope: !2296)
!2336 = !DILocation(line: 1073, column: 14, scope: !2296)
!2337 = !DILocation(line: 1073, column: 21, scope: !2317)
!2338 = !DILocation(line: 1073, column: 28, scope: !2317)
!2339 = !DILocation(line: 1073, column: 33, scope: !2317)
!2340 = !DILocation(line: 1073, column: 7, scope: !2317)
!2341 = !DILocation(line: 1074, column: 22, scope: !2296)
!2342 = !DILocation(line: 1074, column: 29, scope: !2296)
!2343 = !DILocation(line: 1074, column: 7, scope: !2296)
!2344 = !DILocation(line: 1074, column: 14, scope: !2296)
!2345 = !DILocation(line: 1074, column: 34, scope: !2296)
!2346 = !DILocation(line: 1073, column: 7, scope: !2328)
!2347 = !DILocation(line: 1073, column: 7, scope: !2330)
!2348 = !DILocation(line: 1072, column: 3, scope: !2296)
!2349 = !DILocation(line: 1072, column: 9, scope: !2296)
!2350 = !DILocation(line: 1072, column: 15, scope: !2296)
!2351 = !DILocation(line: 1073, column: 5, scope: !2330)
!2352 = !DILocation(line: 1077, column: 22, scope: !2296)
!2353 = !DILocation(line: 1077, column: 7, scope: !2296)
!2354 = !DILocation(line: 1077, column: 14, scope: !2296)
!2355 = !DILocation(line: 1077, column: 30, scope: !2296)
!2356 = !DILocation(line: 1078, column: 7, scope: !2296)
!2357 = !DILocation(line: 1078, column: 13, scope: !2296)
!2358 = !DILocation(line: 1078, column: 19, scope: !2296)
!2359 = !DILocation(line: 1078, column: 5, scope: !2296)
!2360 = !DILocation(line: 1076, column: 3, scope: !2296)
!2361 = !DILocation(line: 1076, column: 9, scope: !2296)
!2362 = !DILocation(line: 1076, column: 15, scope: !2296)
!2363 = !DILocation(line: 1077, column: 5, scope: !2296)
!2364 = !DILocation(line: 1080, column: 22, scope: !2296)
!2365 = !DILocation(line: 1080, column: 7, scope: !2296)
!2366 = !DILocation(line: 1080, column: 14, scope: !2296)
!2367 = !DILocation(line: 1080, column: 30, scope: !2296)
!2368 = !DILocation(line: 1081, column: 7, scope: !2296)
!2369 = !DILocation(line: 1081, column: 13, scope: !2296)
!2370 = !DILocation(line: 1081, column: 19, scope: !2296)
!2371 = !DILocation(line: 1081, column: 5, scope: !2296)
!2372 = !DILocation(line: 1079, column: 3, scope: !2296)
!2373 = !DILocation(line: 1079, column: 9, scope: !2296)
!2374 = !DILocation(line: 1079, column: 15, scope: !2296)
!2375 = !DILocation(line: 1080, column: 5, scope: !2296)
!2376 = !DILocation(line: 1082, column: 38, scope: !2296)
!2377 = !DILocation(line: 1082, column: 44, scope: !2296)
!2378 = !DILocation(line: 1082, column: 50, scope: !2296)
!2379 = !DILocation(line: 1082, column: 28, scope: !2296)
!2380 = !DILocation(line: 1082, column: 3, scope: !2296)
!2381 = !DILocation(line: 1082, column: 9, scope: !2296)
!2382 = !DILocation(line: 1082, column: 15, scope: !2296)
!2383 = !DILocation(line: 1082, column: 26, scope: !2296)
!2384 = !DILocation(line: 1084, column: 3, scope: !2296)
!2385 = !DILocation(line: 1084, column: 9, scope: !2296)
!2386 = !DILocation(line: 1084, column: 15, scope: !2296)
!2387 = !DILocation(line: 1085, column: 5, scope: !2296)
!2388 = !DILocation(line: 1088, column: 7, scope: !2296)
!2389 = !DILocation(line: 1088, column: 13, scope: !2296)
!2390 = !DILocation(line: 1088, column: 19, scope: !2296)
!2391 = !DILocation(line: 1089, column: 7, scope: !2296)
!2392 = !DILocation(line: 1089, column: 13, scope: !2296)
!2393 = !DILocation(line: 1089, column: 20, scope: !2296)
!2394 = !DILocation(line: 1089, column: 5, scope: !2296)
!2395 = !DILocation(line: 1087, column: 3, scope: !2296)
!2396 = !DILocation(line: 1087, column: 9, scope: !2296)
!2397 = !DILocation(line: 1087, column: 15, scope: !2296)
!2398 = !DILocation(line: 1088, column: 5, scope: !2296)
!2399 = !DILocation(line: 1091, column: 7, scope: !2296)
!2400 = !DILocation(line: 1091, column: 13, scope: !2296)
!2401 = !DILocation(line: 1091, column: 19, scope: !2296)
!2402 = !DILocation(line: 1092, column: 7, scope: !2296)
!2403 = !DILocation(line: 1092, column: 13, scope: !2296)
!2404 = !DILocation(line: 1092, column: 20, scope: !2296)
!2405 = !DILocation(line: 1092, column: 5, scope: !2296)
!2406 = !DILocation(line: 1090, column: 3, scope: !2296)
!2407 = !DILocation(line: 1090, column: 9, scope: !2296)
!2408 = !DILocation(line: 1090, column: 15, scope: !2296)
!2409 = !DILocation(line: 1091, column: 5, scope: !2296)
!2410 = !DILocation(line: 1093, column: 2, scope: !2296)
!2411 = !DILocation(line: 1095, column: 2, scope: !331)
!2412 = !DILocalVariable(name: "iter", arg: 1, scope: !270, file: !1, line: 1232, type: !210)
!2413 = !DILocation(line: 1232, column: 41, scope: !270)
!2414 = !DILocalVariable(name: "target", arg: 2, scope: !270, file: !1, line: 1232, type: !62)
!2415 = !DILocation(line: 1232, column: 56, scope: !270)
!2416 = !DILocalVariable(name: "stream", scope: !270, file: !1, line: 1234, type: !52)
!2417 = !DILocation(line: 1234, column: 22, scope: !270)
!2418 = !DILocalVariable(name: "group", scope: !270, file: !1, line: 1235, type: !112)
!2419 = !DILocation(line: 1235, column: 21, scope: !270)
!2420 = !DILocalVariable(name: "left", scope: !270, file: !1, line: 1236, type: !49)
!2421 = !DILocation(line: 1236, column: 9, scope: !270)
!2422 = !DILocalVariable(name: "right", scope: !270, file: !1, line: 1236, type: !49)
!2423 = !DILocation(line: 1236, column: 15, scope: !270)
!2424 = !DILocalVariable(name: "i", scope: !270, file: !1, line: 1238, type: !173)
!2425 = !DILocation(line: 1238, column: 20, scope: !270)
!2426 = !DILocation(line: 1238, column: 24, scope: !270)
!2427 = !DILocation(line: 1238, column: 30, scope: !270)
!2428 = !DILocation(line: 1238, column: 51, scope: !270)
!2429 = !DILocation(line: 1241, column: 6, scope: !2430)
!2430 = distinct !DILexicalBlock(scope: !270, file: !1, line: 1241, column: 6)
!2431 = !DILocation(line: 1241, column: 9, scope: !2430)
!2432 = !DILocation(line: 1241, column: 30, scope: !2430)
!2433 = !DILocation(line: 1241, column: 27, scope: !2430)
!2434 = !DILocation(line: 1241, column: 6, scope: !270)
!2435 = !DILocation(line: 1242, column: 3, scope: !2430)
!2436 = !DILocation(line: 1245, column: 30, scope: !270)
!2437 = !DILocation(line: 1245, column: 33, scope: !270)
!2438 = !DILocation(line: 1245, column: 42, scope: !270)
!2439 = !DILocation(line: 1245, column: 11, scope: !270)
!2440 = !DILocation(line: 1245, column: 9, scope: !270)
!2441 = !DILocation(line: 1246, column: 2, scope: !270)
!2442 = !DILocation(line: 1246, column: 2, scope: !2443)
!2443 = !DILexicalBlockFile(scope: !270, file: !1, discriminator: 1)
!2444 = !DILocation(line: 1246, column: 2, scope: !2445)
!2445 = !DILexicalBlockFile(scope: !270, file: !1, discriminator: 2)
!2446 = !DILocation(line: 1246, column: 2, scope: !2447)
!2447 = !DILexicalBlockFile(scope: !270, file: !1, discriminator: 3)
!2448 = !DILocation(line: 1247, column: 12, scope: !270)
!2449 = !DILocation(line: 1247, column: 20, scope: !270)
!2450 = !DILocation(line: 1247, column: 25, scope: !270)
!2451 = !DILocation(line: 1247, column: 9, scope: !270)
!2452 = !DILocation(line: 1250, column: 29, scope: !270)
!2453 = !DILocation(line: 1250, column: 37, scope: !270)
!2454 = !DILocation(line: 1250, column: 45, scope: !270)
!2455 = !DILocation(line: 1250, column: 10, scope: !270)
!2456 = !DILocation(line: 1250, column: 8, scope: !270)
!2457 = !DILocation(line: 1251, column: 2, scope: !270)
!2458 = !DILocation(line: 1251, column: 2, scope: !2443)
!2459 = !DILocation(line: 1251, column: 2, scope: !2445)
!2460 = !DILocation(line: 1251, column: 2, scope: !2447)
!2461 = !DILocation(line: 1258, column: 7, scope: !270)
!2462 = !DILocation(line: 1259, column: 10, scope: !270)
!2463 = !DILocation(line: 1259, column: 17, scope: !270)
!2464 = !DILocation(line: 1259, column: 8, scope: !270)
!2465 = !DILocation(line: 1261, column: 2, scope: !270)
!2466 = !DILocation(line: 1261, column: 9, scope: !2443)
!2467 = !DILocation(line: 1261, column: 16, scope: !2443)
!2468 = !DILocation(line: 1261, column: 14, scope: !2443)
!2469 = !DILocation(line: 1261, column: 2, scope: !2443)
!2470 = !DILocalVariable(name: "pos", scope: !2471, file: !1, line: 1262, type: !691)
!2471 = distinct !DILexicalBlock(scope: !270, file: !1, line: 1261, column: 23)
!2472 = !DILocation(line: 1262, column: 16, scope: !2471)
!2473 = !DILocation(line: 1262, column: 22, scope: !2471)
!2474 = !DILocation(line: 1262, column: 30, scope: !2471)
!2475 = !DILocation(line: 1262, column: 38, scope: !2471)
!2476 = !DILocation(line: 1262, column: 36, scope: !2471)
!2477 = !DILocation(line: 1262, column: 44, scope: !2471)
!2478 = !DILocation(line: 1262, column: 27, scope: !2471)
!2479 = !DILocation(line: 1263, column: 22, scope: !2480)
!2480 = distinct !DILexicalBlock(scope: !2471, file: !1, line: 1263, column: 7)
!2481 = !DILocation(line: 1263, column: 7, scope: !2480)
!2482 = !DILocation(line: 1263, column: 14, scope: !2480)
!2483 = !DILocation(line: 1263, column: 27, scope: !2480)
!2484 = !DILocation(line: 1263, column: 47, scope: !2480)
!2485 = !DILocation(line: 1263, column: 44, scope: !2480)
!2486 = !DILocation(line: 1263, column: 7, scope: !2471)
!2487 = !DILocation(line: 1264, column: 11, scope: !2480)
!2488 = !DILocation(line: 1264, column: 15, scope: !2480)
!2489 = !DILocation(line: 1264, column: 9, scope: !2480)
!2490 = !DILocation(line: 1264, column: 4, scope: !2480)
!2491 = !DILocation(line: 1266, column: 12, scope: !2480)
!2492 = !DILocation(line: 1266, column: 10, scope: !2480)
!2493 = !DILocation(line: 1261, column: 2, scope: !2445)
!2494 = !DILocation(line: 1269, column: 34, scope: !270)
!2495 = !DILocation(line: 1269, column: 2, scope: !270)
!2496 = !DILocation(line: 1269, column: 8, scope: !270)
!2497 = !DILocation(line: 1269, column: 30, scope: !270)
!2498 = !DILocation(line: 1269, column: 32, scope: !270)
!2499 = !DILocation(line: 1270, column: 33, scope: !270)
!2500 = !DILocation(line: 1270, column: 2, scope: !270)
!2501 = !DILocation(line: 1270, column: 8, scope: !270)
!2502 = !DILocation(line: 1270, column: 29, scope: !270)
!2503 = !DILocation(line: 1270, column: 31, scope: !270)
!2504 = !DILocation(line: 1271, column: 34, scope: !270)
!2505 = !DILocation(line: 1271, column: 2, scope: !270)
!2506 = !DILocation(line: 1271, column: 8, scope: !270)
!2507 = !DILocation(line: 1271, column: 30, scope: !270)
!2508 = !DILocation(line: 1271, column: 32, scope: !270)
!2509 = !DILocation(line: 1273, column: 16, scope: !270)
!2510 = !DILocation(line: 1273, column: 2, scope: !270)
!2511 = !DILocation(line: 1275, column: 2, scope: !270)
!2512 = !DILocation(line: 1276, column: 1, scope: !270)
!2513 = !DILocalVariable(name: "tree", arg: 1, scope: !332, file: !1, line: 319, type: !335)
!2514 = !DILocation(line: 319, column: 37, scope: !332)
!2515 = !DILocalVariable(name: "target", arg: 2, scope: !332, file: !1, line: 319, type: !62)
!2516 = !DILocation(line: 319, column: 52, scope: !332)
!2517 = !DILocalVariable(name: "result", scope: !332, file: !1, line: 321, type: !329)
!2518 = !DILocation(line: 321, column: 25, scope: !332)
!2519 = !DILocalVariable(name: "node", scope: !332, file: !1, line: 322, type: !329)
!2520 = !DILocation(line: 322, column: 25, scope: !332)
!2521 = !DILocation(line: 322, column: 32, scope: !332)
!2522 = !DILocation(line: 322, column: 38, scope: !332)
!2523 = !DILocation(line: 324, column: 2, scope: !332)
!2524 = !DILocation(line: 324, column: 2, scope: !2525)
!2525 = !DILexicalBlockFile(scope: !332, file: !1, discriminator: 1)
!2526 = !DILocation(line: 324, column: 2, scope: !2527)
!2527 = !DILexicalBlockFile(scope: !332, file: !1, discriminator: 2)
!2528 = !DILocation(line: 324, column: 2, scope: !2529)
!2529 = !DILexicalBlockFile(scope: !332, file: !1, discriminator: 3)
!2530 = !DILocation(line: 324, column: 2, scope: !2531)
!2531 = !DILexicalBlockFile(scope: !332, file: !1, discriminator: 4)
!2532 = !DILocation(line: 329, column: 2, scope: !332)
!2533 = !DILocation(line: 329, column: 9, scope: !2525)
!2534 = !DILocation(line: 329, column: 14, scope: !2525)
!2535 = !DILocation(line: 329, column: 2, scope: !2525)
!2536 = !DILocation(line: 330, column: 7, scope: !2537)
!2537 = distinct !DILexicalBlock(scope: !2538, file: !1, line: 330, column: 7)
!2538 = distinct !DILexicalBlock(scope: !332, file: !1, line: 329, column: 23)
!2539 = !DILocation(line: 330, column: 13, scope: !2537)
!2540 = !DILocation(line: 330, column: 33, scope: !2537)
!2541 = !DILocation(line: 330, column: 31, scope: !2537)
!2542 = !DILocation(line: 330, column: 7, scope: !2538)
!2543 = !DILocation(line: 331, column: 11, scope: !2544)
!2544 = distinct !DILexicalBlock(scope: !2537, file: !1, line: 330, column: 41)
!2545 = !DILocation(line: 331, column: 17, scope: !2544)
!2546 = !DILocation(line: 331, column: 9, scope: !2544)
!2547 = !DILocation(line: 332, column: 3, scope: !2544)
!2548 = !DILocation(line: 333, column: 13, scope: !2549)
!2549 = distinct !DILexicalBlock(scope: !2537, file: !1, line: 332, column: 10)
!2550 = !DILocation(line: 333, column: 11, scope: !2549)
!2551 = !DILocation(line: 334, column: 11, scope: !2549)
!2552 = !DILocation(line: 334, column: 17, scope: !2549)
!2553 = !DILocation(line: 334, column: 9, scope: !2549)
!2554 = !DILocation(line: 329, column: 2, scope: !2527)
!2555 = !DILocation(line: 338, column: 18, scope: !332)
!2556 = !DILocation(line: 338, column: 9, scope: !332)
!2557 = !DILocation(line: 338, column: 2, scope: !332)
!2558 = !DILocalVariable(name: "tree", arg: 1, scope: !274, file: !1, line: 182, type: !277)
!2559 = !DILocation(line: 182, column: 29, scope: !274)
!2560 = !DILocation(line: 184, column: 2, scope: !274)
!2561 = !DILocation(line: 184, column: 8, scope: !274)
!2562 = !DILocation(line: 184, column: 13, scope: !274)
!2563 = !DILocation(line: 185, column: 2, scope: !274)
!2564 = !DILocation(line: 185, column: 8, scope: !274)
!2565 = !DILocation(line: 185, column: 17, scope: !274)
!2566 = !DILocation(line: 186, column: 2, scope: !274)
!2567 = !DILocation(line: 186, column: 8, scope: !274)
!2568 = !DILocation(line: 186, column: 18, scope: !274)
!2569 = !DILocation(line: 187, column: 2, scope: !274)
!2570 = !DILocation(line: 187, column: 8, scope: !274)
!2571 = !DILocation(line: 187, column: 14, scope: !274)
!2572 = !DILocation(line: 188, column: 2, scope: !274)
!2573 = !DILocalVariable(name: "n", arg: 1, scope: !284, file: !285, line: 372, type: !72)
!2574 = !DILocation(line: 372, column: 16, scope: !284)
!2575 = !DILocation(line: 383, column: 23, scope: !284)
!2576 = !DILocation(line: 383, column: 9, scope: !284)
!2577 = !DILocation(line: 383, column: 26, scope: !284)
!2578 = !DILocation(line: 383, column: 2, scope: !284)
!2579 = !DILocalVariable(name: "n", arg: 1, scope: !288, file: !285, line: 469, type: !72)
!2580 = !DILocation(line: 469, column: 16, scope: !288)
!2581 = !DILocation(line: 475, column: 23, scope: !288)
!2582 = !DILocation(line: 475, column: 9, scope: !288)
!2583 = !DILocation(line: 475, column: 2, scope: !288)
!2584 = !DILocalVariable(name: "node", arg: 1, scope: !295, file: !1, line: 194, type: !68)
!2585 = !DILocation(line: 194, column: 38, scope: !295)
!2586 = !DILocalVariable(name: "allocator", arg: 2, scope: !295, file: !1, line: 194, type: !147)
!2587 = !DILocation(line: 194, column: 60, scope: !295)
!2588 = !DILocalVariable(name: "free_func", arg: 3, scope: !295, file: !1, line: 195, type: !292)
!2589 = !DILocation(line: 195, column: 10, scope: !295)
!2590 = !DILocation(line: 199, column: 6, scope: !2591)
!2591 = distinct !DILexicalBlock(scope: !295, file: !1, line: 199, column: 6)
!2592 = !DILocation(line: 199, column: 12, scope: !2591)
!2593 = !DILocation(line: 199, column: 17, scope: !2591)
!2594 = !DILocation(line: 199, column: 6, scope: !295)
!2595 = !DILocation(line: 200, column: 23, scope: !2591)
!2596 = !DILocation(line: 200, column: 29, scope: !2591)
!2597 = !DILocation(line: 200, column: 35, scope: !2591)
!2598 = !DILocation(line: 200, column: 46, scope: !2591)
!2599 = !DILocation(line: 200, column: 3, scope: !2591)
!2600 = !DILocation(line: 202, column: 6, scope: !2601)
!2601 = distinct !DILexicalBlock(scope: !295, file: !1, line: 202, column: 6)
!2602 = !DILocation(line: 202, column: 12, scope: !2601)
!2603 = !DILocation(line: 202, column: 18, scope: !2601)
!2604 = !DILocation(line: 202, column: 6, scope: !295)
!2605 = !DILocation(line: 203, column: 23, scope: !2601)
!2606 = !DILocation(line: 203, column: 29, scope: !2601)
!2607 = !DILocation(line: 203, column: 36, scope: !2601)
!2608 = !DILocation(line: 203, column: 47, scope: !2601)
!2609 = !DILocation(line: 203, column: 3, scope: !2601)
!2610 = !DILocation(line: 205, column: 6, scope: !2611)
!2611 = distinct !DILexicalBlock(scope: !295, file: !1, line: 205, column: 6)
!2612 = !DILocation(line: 205, column: 16, scope: !2611)
!2613 = !DILocation(line: 205, column: 6, scope: !295)
!2614 = !DILocation(line: 206, column: 3, scope: !2611)
!2615 = !DILocation(line: 206, column: 13, scope: !2611)
!2616 = !DILocation(line: 206, column: 19, scope: !2611)
!2617 = !DILocation(line: 208, column: 12, scope: !295)
!2618 = !DILocation(line: 208, column: 18, scope: !295)
!2619 = !DILocation(line: 208, column: 2, scope: !295)
!2620 = !DILocation(line: 209, column: 2, scope: !295)
