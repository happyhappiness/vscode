; ModuleID = '/data/download/cmake/cmake-master/Utilities/cmlibarchive/libarchive/archive_entry_sparse.c'
target datalayout = "e-m:e-i64:64-f80:128-n8:16:32:64-S128"
target triple = "x86_64-unknown-linux-gnu"

%struct.archive_entry = type { %struct.archive*, i8*, i32, %struct.aest, i32, %struct.archive_mstring, i64, i64, %struct.archive_mstring, %struct.archive_mstring, %struct.archive_mstring, %struct.archive_mstring, %struct.archive_mstring, %struct.archive_mstring, i8, i8*, i64, %struct.archive_acl, %struct.ae_xattr*, %struct.ae_xattr*, %struct.ae_sparse*, %struct.ae_sparse*, %struct.ae_sparse*, [12 x i8] }
%struct.archive = type { i32, i32, %struct.archive_vtable*, i32, i8*, i32, i8*, i32, i32, i8*, %struct.archive_string, i8*, i32, i32, %struct.archive_string_conv*, i8*, i64, i64, i64, i8, i64 }
%struct.archive_vtable = type { i32 (%struct.archive*)*, i32 (%struct.archive*)*, i32 (%struct.archive*, %struct.archive_entry*)*, i32 (%struct.archive*)*, i64 (%struct.archive*, i8*, i64)*, i64 (%struct.archive*, i8*, i64, i64)*, i32 (%struct.archive*, %struct.archive_entry**)*, i32 (%struct.archive*, %struct.archive_entry*)*, i32 (%struct.archive*, i8**, i64*, i64*)*, i32 (%struct.archive*)*, i64 (%struct.archive*, i32)*, i32 (%struct.archive*, i32)*, i8* (%struct.archive*, i32)* }
%struct.archive_string = type { i8*, i64, i64 }
%struct.archive_string_conv = type opaque
%struct.aest = type { i64, i32, i64, i32, i64, i32, i64, i32, i64, i64, i32, i64, i64, i32, i64, i64, i64, i32, i64, i64, i64 }
%struct.archive_mstring = type { %struct.archive_string, %struct.archive_string, %struct.archive_wstring, %struct.archive_string, i32 }
%struct.archive_wstring = type { i32*, i64, i64 }
%struct.archive_acl = type { i32, %struct.archive_acl_entry*, %struct.archive_acl_entry*, i32, i32*, i8*, i32 }
%struct.archive_acl_entry = type { %struct.archive_acl_entry*, i32, i32, i32, i32, %struct.archive_mstring }
%struct.ae_xattr = type { %struct.ae_xattr*, i8*, i8*, i64 }
%struct.ae_sparse = type { %struct.ae_sparse*, i64, i64 }

; Function Attrs: nounwind uwtable
define void @archive_entry_sparse_clear(%struct.archive_entry* %entry1) #0 !dbg !16 {
entry:
  %entry.addr = alloca %struct.archive_entry*, align 8
  %sp = alloca %struct.ae_sparse*, align 8
  store %struct.archive_entry* %entry1, %struct.archive_entry** %entry.addr, align 8
  call void @llvm.dbg.declare(metadata %struct.archive_entry** %entry.addr, metadata !227, metadata !228), !dbg !229
  call void @llvm.dbg.declare(metadata %struct.ae_sparse** %sp, metadata !230, metadata !228), !dbg !231
  br label %while.cond, !dbg !232

while.cond:                                       ; preds = %while.body, %entry
  %0 = load %struct.archive_entry*, %struct.archive_entry** %entry.addr, align 8, !dbg !233
  %sparse_head = getelementptr inbounds %struct.archive_entry, %struct.archive_entry* %0, i32 0, i32 20, !dbg !235
  %1 = load %struct.ae_sparse*, %struct.ae_sparse** %sparse_head, align 8, !dbg !235
  %cmp = icmp ne %struct.ae_sparse* %1, null, !dbg !236
  br i1 %cmp, label %while.body, label %while.end, !dbg !237

while.body:                                       ; preds = %while.cond
  %2 = load %struct.archive_entry*, %struct.archive_entry** %entry.addr, align 8, !dbg !238
  %sparse_head2 = getelementptr inbounds %struct.archive_entry, %struct.archive_entry* %2, i32 0, i32 20, !dbg !240
  %3 = load %struct.ae_sparse*, %struct.ae_sparse** %sparse_head2, align 8, !dbg !240
  %next = getelementptr inbounds %struct.ae_sparse, %struct.ae_sparse* %3, i32 0, i32 0, !dbg !241
  %4 = load %struct.ae_sparse*, %struct.ae_sparse** %next, align 8, !dbg !241
  store %struct.ae_sparse* %4, %struct.ae_sparse** %sp, align 8, !dbg !242
  %5 = load %struct.archive_entry*, %struct.archive_entry** %entry.addr, align 8, !dbg !243
  %sparse_head3 = getelementptr inbounds %struct.archive_entry, %struct.archive_entry* %5, i32 0, i32 20, !dbg !244
  %6 = load %struct.ae_sparse*, %struct.ae_sparse** %sparse_head3, align 8, !dbg !244
  %7 = bitcast %struct.ae_sparse* %6 to i8*, !dbg !243
  call void @free(i8* %7) #4, !dbg !245
  %8 = load %struct.ae_sparse*, %struct.ae_sparse** %sp, align 8, !dbg !246
  %9 = load %struct.archive_entry*, %struct.archive_entry** %entry.addr, align 8, !dbg !247
  %sparse_head4 = getelementptr inbounds %struct.archive_entry, %struct.archive_entry* %9, i32 0, i32 20, !dbg !248
  store %struct.ae_sparse* %8, %struct.ae_sparse** %sparse_head4, align 8, !dbg !249
  br label %while.cond, !dbg !250

while.end:                                        ; preds = %while.cond
  %10 = load %struct.archive_entry*, %struct.archive_entry** %entry.addr, align 8, !dbg !252
  %sparse_tail = getelementptr inbounds %struct.archive_entry, %struct.archive_entry* %10, i32 0, i32 21, !dbg !253
  store %struct.ae_sparse* null, %struct.ae_sparse** %sparse_tail, align 8, !dbg !254
  ret void, !dbg !255
}

; Function Attrs: nounwind readnone
declare void @llvm.dbg.declare(metadata, metadata, metadata) #1

; Function Attrs: nounwind
declare void @free(i8*) #2

; Function Attrs: nounwind uwtable
define void @archive_entry_sparse_add_entry(%struct.archive_entry* %entry1, i64 %offset, i64 %length) #0 !dbg !214 {
entry:
  %entry.addr = alloca %struct.archive_entry*, align 8
  %offset.addr = alloca i64, align 8
  %length.addr = alloca i64, align 8
  %sp = alloca %struct.ae_sparse*, align 8
  store %struct.archive_entry* %entry1, %struct.archive_entry** %entry.addr, align 8
  call void @llvm.dbg.declare(metadata %struct.archive_entry** %entry.addr, metadata !256, metadata !228), !dbg !257
  store i64 %offset, i64* %offset.addr, align 8
  call void @llvm.dbg.declare(metadata i64* %offset.addr, metadata !258, metadata !228), !dbg !259
  store i64 %length, i64* %length.addr, align 8
  call void @llvm.dbg.declare(metadata i64* %length.addr, metadata !260, metadata !228), !dbg !261
  call void @llvm.dbg.declare(metadata %struct.ae_sparse** %sp, metadata !262, metadata !228), !dbg !263
  %0 = load i64, i64* %offset.addr, align 8, !dbg !264
  %cmp = icmp slt i64 %0, 0, !dbg !266
  br i1 %cmp, label %if.then, label %lor.lhs.false, !dbg !267

lor.lhs.false:                                    ; preds = %entry
  %1 = load i64, i64* %length.addr, align 8, !dbg !268
  %cmp2 = icmp slt i64 %1, 0, !dbg !270
  br i1 %cmp2, label %if.then, label %if.end, !dbg !271

if.then:                                          ; preds = %lor.lhs.false, %entry
  br label %if.end49, !dbg !272

if.end:                                           ; preds = %lor.lhs.false
  %2 = load i64, i64* %offset.addr, align 8, !dbg !273
  %3 = load i64, i64* %length.addr, align 8, !dbg !275
  %sub = sub nsw i64 9223372036854775807, %3, !dbg !276
  %cmp3 = icmp sgt i64 %2, %sub, !dbg !277
  br i1 %cmp3, label %if.then6, label %lor.lhs.false4, !dbg !278

lor.lhs.false4:                                   ; preds = %if.end
  %4 = load i64, i64* %offset.addr, align 8, !dbg !279
  %5 = load i64, i64* %length.addr, align 8, !dbg !280
  %add = add nsw i64 %4, %5, !dbg !281
  %6 = load %struct.archive_entry*, %struct.archive_entry** %entry.addr, align 8, !dbg !282
  %call = call i64 @archive_entry_size(%struct.archive_entry* %6), !dbg !283
  %cmp5 = icmp sgt i64 %add, %call, !dbg !284
  br i1 %cmp5, label %if.then6, label %if.end7, !dbg !285

if.then6:                                         ; preds = %lor.lhs.false4, %if.end
  br label %if.end49, !dbg !287

if.end7:                                          ; preds = %lor.lhs.false4
  %7 = load %struct.archive_entry*, %struct.archive_entry** %entry.addr, align 8, !dbg !288
  %sparse_tail = getelementptr inbounds %struct.archive_entry, %struct.archive_entry* %7, i32 0, i32 21, !dbg !290
  %8 = load %struct.ae_sparse*, %struct.ae_sparse** %sparse_tail, align 8, !dbg !290
  store %struct.ae_sparse* %8, %struct.ae_sparse** %sp, align 8, !dbg !291
  %cmp8 = icmp ne %struct.ae_sparse* %8, null, !dbg !292
  br i1 %cmp8, label %if.then9, label %if.end31, !dbg !293

if.then9:                                         ; preds = %if.end7
  %9 = load %struct.ae_sparse*, %struct.ae_sparse** %sp, align 8, !dbg !294
  %offset10 = getelementptr inbounds %struct.ae_sparse, %struct.ae_sparse* %9, i32 0, i32 1, !dbg !297
  %10 = load i64, i64* %offset10, align 8, !dbg !297
  %11 = load %struct.ae_sparse*, %struct.ae_sparse** %sp, align 8, !dbg !298
  %length11 = getelementptr inbounds %struct.ae_sparse, %struct.ae_sparse* %11, i32 0, i32 2, !dbg !299
  %12 = load i64, i64* %length11, align 8, !dbg !299
  %add12 = add nsw i64 %10, %12, !dbg !300
  %13 = load i64, i64* %offset.addr, align 8, !dbg !301
  %cmp13 = icmp sgt i64 %add12, %13, !dbg !302
  br i1 %cmp13, label %if.then14, label %if.end15, !dbg !303

if.then14:                                        ; preds = %if.then9
  br label %if.end49, !dbg !304

if.end15:                                         ; preds = %if.then9
  %14 = load %struct.ae_sparse*, %struct.ae_sparse** %sp, align 8, !dbg !305
  %offset16 = getelementptr inbounds %struct.ae_sparse, %struct.ae_sparse* %14, i32 0, i32 1, !dbg !307
  %15 = load i64, i64* %offset16, align 8, !dbg !307
  %16 = load %struct.ae_sparse*, %struct.ae_sparse** %sp, align 8, !dbg !308
  %length17 = getelementptr inbounds %struct.ae_sparse, %struct.ae_sparse* %16, i32 0, i32 2, !dbg !309
  %17 = load i64, i64* %length17, align 8, !dbg !309
  %add18 = add nsw i64 %15, %17, !dbg !310
  %18 = load i64, i64* %offset.addr, align 8, !dbg !311
  %cmp19 = icmp eq i64 %add18, %18, !dbg !312
  br i1 %cmp19, label %if.then20, label %if.end30, !dbg !313

if.then20:                                        ; preds = %if.end15
  %19 = load %struct.ae_sparse*, %struct.ae_sparse** %sp, align 8, !dbg !314
  %offset21 = getelementptr inbounds %struct.ae_sparse, %struct.ae_sparse* %19, i32 0, i32 1, !dbg !317
  %20 = load i64, i64* %offset21, align 8, !dbg !317
  %21 = load %struct.ae_sparse*, %struct.ae_sparse** %sp, align 8, !dbg !318
  %length22 = getelementptr inbounds %struct.ae_sparse, %struct.ae_sparse* %21, i32 0, i32 2, !dbg !319
  %22 = load i64, i64* %length22, align 8, !dbg !319
  %add23 = add nsw i64 %20, %22, !dbg !320
  %23 = load i64, i64* %length.addr, align 8, !dbg !321
  %add24 = add nsw i64 %add23, %23, !dbg !322
  %cmp25 = icmp slt i64 %add24, 0, !dbg !323
  br i1 %cmp25, label %if.then26, label %if.end27, !dbg !324

if.then26:                                        ; preds = %if.then20
  br label %if.end49, !dbg !325

if.end27:                                         ; preds = %if.then20
  %24 = load i64, i64* %length.addr, align 8, !dbg !326
  %25 = load %struct.ae_sparse*, %struct.ae_sparse** %sp, align 8, !dbg !327
  %length28 = getelementptr inbounds %struct.ae_sparse, %struct.ae_sparse* %25, i32 0, i32 2, !dbg !328
  %26 = load i64, i64* %length28, align 8, !dbg !329
  %add29 = add nsw i64 %26, %24, !dbg !329
  store i64 %add29, i64* %length28, align 8, !dbg !329
  br label %if.end49, !dbg !330

if.end30:                                         ; preds = %if.end15
  br label %if.end31, !dbg !331

if.end31:                                         ; preds = %if.end30, %if.end7
  %call32 = call noalias i8* @malloc(i64 24) #4, !dbg !332
  %27 = bitcast i8* %call32 to %struct.ae_sparse*, !dbg !334
  store %struct.ae_sparse* %27, %struct.ae_sparse** %sp, align 8, !dbg !335
  %cmp33 = icmp eq %struct.ae_sparse* %27, null, !dbg !336
  br i1 %cmp33, label %if.then34, label %if.end35, !dbg !337

if.then34:                                        ; preds = %if.end31
  br label %if.end49, !dbg !338

if.end35:                                         ; preds = %if.end31
  %28 = load i64, i64* %offset.addr, align 8, !dbg !339
  %29 = load %struct.ae_sparse*, %struct.ae_sparse** %sp, align 8, !dbg !340
  %offset36 = getelementptr inbounds %struct.ae_sparse, %struct.ae_sparse* %29, i32 0, i32 1, !dbg !341
  store i64 %28, i64* %offset36, align 8, !dbg !342
  %30 = load i64, i64* %length.addr, align 8, !dbg !343
  %31 = load %struct.ae_sparse*, %struct.ae_sparse** %sp, align 8, !dbg !344
  %length37 = getelementptr inbounds %struct.ae_sparse, %struct.ae_sparse* %31, i32 0, i32 2, !dbg !345
  store i64 %30, i64* %length37, align 8, !dbg !346
  %32 = load %struct.ae_sparse*, %struct.ae_sparse** %sp, align 8, !dbg !347
  %next = getelementptr inbounds %struct.ae_sparse, %struct.ae_sparse* %32, i32 0, i32 0, !dbg !348
  store %struct.ae_sparse* null, %struct.ae_sparse** %next, align 8, !dbg !349
  %33 = load %struct.archive_entry*, %struct.archive_entry** %entry.addr, align 8, !dbg !350
  %sparse_head = getelementptr inbounds %struct.archive_entry, %struct.archive_entry* %33, i32 0, i32 20, !dbg !352
  %34 = load %struct.ae_sparse*, %struct.ae_sparse** %sparse_head, align 8, !dbg !352
  %cmp38 = icmp eq %struct.ae_sparse* %34, null, !dbg !353
  br i1 %cmp38, label %if.then39, label %if.else, !dbg !354

if.then39:                                        ; preds = %if.end35
  %35 = load %struct.ae_sparse*, %struct.ae_sparse** %sp, align 8, !dbg !355
  %36 = load %struct.archive_entry*, %struct.archive_entry** %entry.addr, align 8, !dbg !356
  %sparse_tail40 = getelementptr inbounds %struct.archive_entry, %struct.archive_entry* %36, i32 0, i32 21, !dbg !357
  store %struct.ae_sparse* %35, %struct.ae_sparse** %sparse_tail40, align 8, !dbg !358
  %37 = load %struct.archive_entry*, %struct.archive_entry** %entry.addr, align 8, !dbg !359
  %sparse_head41 = getelementptr inbounds %struct.archive_entry, %struct.archive_entry* %37, i32 0, i32 20, !dbg !360
  store %struct.ae_sparse* %35, %struct.ae_sparse** %sparse_head41, align 8, !dbg !361
  br label %if.end49, !dbg !359

if.else:                                          ; preds = %if.end35
  %38 = load %struct.archive_entry*, %struct.archive_entry** %entry.addr, align 8, !dbg !362
  %sparse_tail42 = getelementptr inbounds %struct.archive_entry, %struct.archive_entry* %38, i32 0, i32 21, !dbg !365
  %39 = load %struct.ae_sparse*, %struct.ae_sparse** %sparse_tail42, align 8, !dbg !365
  %cmp43 = icmp ne %struct.ae_sparse* %39, null, !dbg !366
  br i1 %cmp43, label %if.then44, label %if.end47, !dbg !367

if.then44:                                        ; preds = %if.else
  %40 = load %struct.ae_sparse*, %struct.ae_sparse** %sp, align 8, !dbg !368
  %41 = load %struct.archive_entry*, %struct.archive_entry** %entry.addr, align 8, !dbg !369
  %sparse_tail45 = getelementptr inbounds %struct.archive_entry, %struct.archive_entry* %41, i32 0, i32 21, !dbg !370
  %42 = load %struct.ae_sparse*, %struct.ae_sparse** %sparse_tail45, align 8, !dbg !370
  %next46 = getelementptr inbounds %struct.ae_sparse, %struct.ae_sparse* %42, i32 0, i32 0, !dbg !371
  store %struct.ae_sparse* %40, %struct.ae_sparse** %next46, align 8, !dbg !372
  br label %if.end47, !dbg !369

if.end47:                                         ; preds = %if.then44, %if.else
  %43 = load %struct.ae_sparse*, %struct.ae_sparse** %sp, align 8, !dbg !373
  %44 = load %struct.archive_entry*, %struct.archive_entry** %entry.addr, align 8, !dbg !374
  %sparse_tail48 = getelementptr inbounds %struct.archive_entry, %struct.archive_entry* %44, i32 0, i32 21, !dbg !375
  store %struct.ae_sparse* %43, %struct.ae_sparse** %sparse_tail48, align 8, !dbg !376
  br label %if.end49

if.end49:                                         ; preds = %if.then, %if.then6, %if.then14, %if.then26, %if.end27, %if.then34, %if.end47, %if.then39
  ret void, !dbg !377
}

declare i64 @archive_entry_size(%struct.archive_entry*) #3

; Function Attrs: nounwind
declare noalias i8* @malloc(i64) #2

; Function Attrs: nounwind uwtable
define i32 @archive_entry_sparse_count(%struct.archive_entry* %entry1) #0 !dbg !217 {
entry:
  %entry.addr = alloca %struct.archive_entry*, align 8
  %sp = alloca %struct.ae_sparse*, align 8
  %count = alloca i32, align 4
  store %struct.archive_entry* %entry1, %struct.archive_entry** %entry.addr, align 8
  call void @llvm.dbg.declare(metadata %struct.archive_entry** %entry.addr, metadata !378, metadata !228), !dbg !379
  call void @llvm.dbg.declare(metadata %struct.ae_sparse** %sp, metadata !380, metadata !228), !dbg !381
  call void @llvm.dbg.declare(metadata i32* %count, metadata !382, metadata !228), !dbg !383
  store i32 0, i32* %count, align 4, !dbg !383
  %0 = load %struct.archive_entry*, %struct.archive_entry** %entry.addr, align 8, !dbg !384
  %sparse_head = getelementptr inbounds %struct.archive_entry, %struct.archive_entry* %0, i32 0, i32 20, !dbg !386
  %1 = load %struct.ae_sparse*, %struct.ae_sparse** %sparse_head, align 8, !dbg !386
  store %struct.ae_sparse* %1, %struct.ae_sparse** %sp, align 8, !dbg !387
  br label %for.cond, !dbg !388

for.cond:                                         ; preds = %for.inc, %entry
  %2 = load %struct.ae_sparse*, %struct.ae_sparse** %sp, align 8, !dbg !389
  %cmp = icmp ne %struct.ae_sparse* %2, null, !dbg !392
  br i1 %cmp, label %for.body, label %for.end, !dbg !393

for.body:                                         ; preds = %for.cond
  %3 = load i32, i32* %count, align 4, !dbg !394
  %inc = add nsw i32 %3, 1, !dbg !394
  store i32 %inc, i32* %count, align 4, !dbg !394
  br label %for.inc, !dbg !395

for.inc:                                          ; preds = %for.body
  %4 = load %struct.ae_sparse*, %struct.ae_sparse** %sp, align 8, !dbg !396
  %next = getelementptr inbounds %struct.ae_sparse, %struct.ae_sparse* %4, i32 0, i32 0, !dbg !398
  %5 = load %struct.ae_sparse*, %struct.ae_sparse** %next, align 8, !dbg !398
  store %struct.ae_sparse* %5, %struct.ae_sparse** %sp, align 8, !dbg !399
  br label %for.cond, !dbg !400

for.end:                                          ; preds = %for.cond
  %6 = load i32, i32* %count, align 4, !dbg !401
  %cmp2 = icmp eq i32 %6, 1, !dbg !403
  br i1 %cmp2, label %if.then, label %if.end7, !dbg !404

if.then:                                          ; preds = %for.end
  %7 = load %struct.archive_entry*, %struct.archive_entry** %entry.addr, align 8, !dbg !405
  %sparse_head3 = getelementptr inbounds %struct.archive_entry, %struct.archive_entry* %7, i32 0, i32 20, !dbg !407
  %8 = load %struct.ae_sparse*, %struct.ae_sparse** %sparse_head3, align 8, !dbg !407
  store %struct.ae_sparse* %8, %struct.ae_sparse** %sp, align 8, !dbg !408
  %9 = load %struct.ae_sparse*, %struct.ae_sparse** %sp, align 8, !dbg !409
  %offset = getelementptr inbounds %struct.ae_sparse, %struct.ae_sparse* %9, i32 0, i32 1, !dbg !411
  %10 = load i64, i64* %offset, align 8, !dbg !411
  %cmp4 = icmp eq i64 %10, 0, !dbg !412
  br i1 %cmp4, label %land.lhs.true, label %if.end, !dbg !413

land.lhs.true:                                    ; preds = %if.then
  %11 = load %struct.ae_sparse*, %struct.ae_sparse** %sp, align 8, !dbg !414
  %length = getelementptr inbounds %struct.ae_sparse, %struct.ae_sparse* %11, i32 0, i32 2, !dbg !415
  %12 = load i64, i64* %length, align 8, !dbg !415
  %13 = load %struct.archive_entry*, %struct.archive_entry** %entry.addr, align 8, !dbg !416
  %call = call i64 @archive_entry_size(%struct.archive_entry* %13), !dbg !417
  %cmp5 = icmp sge i64 %12, %call, !dbg !418
  br i1 %cmp5, label %if.then6, label %if.end, !dbg !419

if.then6:                                         ; preds = %land.lhs.true
  store i32 0, i32* %count, align 4, !dbg !421
  %14 = load %struct.archive_entry*, %struct.archive_entry** %entry.addr, align 8, !dbg !423
  call void @archive_entry_sparse_clear(%struct.archive_entry* %14), !dbg !424
  br label %if.end, !dbg !425

if.end:                                           ; preds = %if.then6, %land.lhs.true, %if.then
  br label %if.end7, !dbg !426

if.end7:                                          ; preds = %if.end, %for.end
  %15 = load i32, i32* %count, align 4, !dbg !427
  ret i32 %15, !dbg !428
}

; Function Attrs: nounwind uwtable
define i32 @archive_entry_sparse_reset(%struct.archive_entry* %entry1) #0 !dbg !220 {
entry:
  %entry.addr = alloca %struct.archive_entry*, align 8
  store %struct.archive_entry* %entry1, %struct.archive_entry** %entry.addr, align 8
  call void @llvm.dbg.declare(metadata %struct.archive_entry** %entry.addr, metadata !429, metadata !228), !dbg !430
  %0 = load %struct.archive_entry*, %struct.archive_entry** %entry.addr, align 8, !dbg !431
  %sparse_head = getelementptr inbounds %struct.archive_entry, %struct.archive_entry* %0, i32 0, i32 20, !dbg !432
  %1 = load %struct.ae_sparse*, %struct.ae_sparse** %sparse_head, align 8, !dbg !432
  %2 = load %struct.archive_entry*, %struct.archive_entry** %entry.addr, align 8, !dbg !433
  %sparse_p = getelementptr inbounds %struct.archive_entry, %struct.archive_entry* %2, i32 0, i32 22, !dbg !434
  store %struct.ae_sparse* %1, %struct.ae_sparse** %sparse_p, align 8, !dbg !435
  %3 = load %struct.archive_entry*, %struct.archive_entry** %entry.addr, align 8, !dbg !436
  %call = call i32 @archive_entry_sparse_count(%struct.archive_entry* %3), !dbg !437
  ret i32 %call, !dbg !438
}

; Function Attrs: nounwind uwtable
define i32 @archive_entry_sparse_next(%struct.archive_entry* %entry1, i64* %offset, i64* %length) #0 !dbg !221 {
entry:
  %retval = alloca i32, align 4
  %entry.addr = alloca %struct.archive_entry*, align 8
  %offset.addr = alloca i64*, align 8
  %length.addr = alloca i64*, align 8
  store %struct.archive_entry* %entry1, %struct.archive_entry** %entry.addr, align 8
  call void @llvm.dbg.declare(metadata %struct.archive_entry** %entry.addr, metadata !439, metadata !228), !dbg !440
  store i64* %offset, i64** %offset.addr, align 8
  call void @llvm.dbg.declare(metadata i64** %offset.addr, metadata !441, metadata !228), !dbg !442
  store i64* %length, i64** %length.addr, align 8
  call void @llvm.dbg.declare(metadata i64** %length.addr, metadata !443, metadata !228), !dbg !444
  %0 = load %struct.archive_entry*, %struct.archive_entry** %entry.addr, align 8, !dbg !445
  %sparse_p = getelementptr inbounds %struct.archive_entry, %struct.archive_entry* %0, i32 0, i32 22, !dbg !447
  %1 = load %struct.ae_sparse*, %struct.ae_sparse** %sparse_p, align 8, !dbg !447
  %tobool = icmp ne %struct.ae_sparse* %1, null, !dbg !445
  br i1 %tobool, label %if.then, label %if.else, !dbg !448

if.then:                                          ; preds = %entry
  %2 = load %struct.archive_entry*, %struct.archive_entry** %entry.addr, align 8, !dbg !449
  %sparse_p2 = getelementptr inbounds %struct.archive_entry, %struct.archive_entry* %2, i32 0, i32 22, !dbg !451
  %3 = load %struct.ae_sparse*, %struct.ae_sparse** %sparse_p2, align 8, !dbg !451
  %offset3 = getelementptr inbounds %struct.ae_sparse, %struct.ae_sparse* %3, i32 0, i32 1, !dbg !452
  %4 = load i64, i64* %offset3, align 8, !dbg !452
  %5 = load i64*, i64** %offset.addr, align 8, !dbg !453
  store i64 %4, i64* %5, align 8, !dbg !454
  %6 = load %struct.archive_entry*, %struct.archive_entry** %entry.addr, align 8, !dbg !455
  %sparse_p4 = getelementptr inbounds %struct.archive_entry, %struct.archive_entry* %6, i32 0, i32 22, !dbg !456
  %7 = load %struct.ae_sparse*, %struct.ae_sparse** %sparse_p4, align 8, !dbg !456
  %length5 = getelementptr inbounds %struct.ae_sparse, %struct.ae_sparse* %7, i32 0, i32 2, !dbg !457
  %8 = load i64, i64* %length5, align 8, !dbg !457
  %9 = load i64*, i64** %length.addr, align 8, !dbg !458
  store i64 %8, i64* %9, align 8, !dbg !459
  %10 = load %struct.archive_entry*, %struct.archive_entry** %entry.addr, align 8, !dbg !460
  %sparse_p6 = getelementptr inbounds %struct.archive_entry, %struct.archive_entry* %10, i32 0, i32 22, !dbg !461
  %11 = load %struct.ae_sparse*, %struct.ae_sparse** %sparse_p6, align 8, !dbg !461
  %next = getelementptr inbounds %struct.ae_sparse, %struct.ae_sparse* %11, i32 0, i32 0, !dbg !462
  %12 = load %struct.ae_sparse*, %struct.ae_sparse** %next, align 8, !dbg !462
  %13 = load %struct.archive_entry*, %struct.archive_entry** %entry.addr, align 8, !dbg !463
  %sparse_p7 = getelementptr inbounds %struct.archive_entry, %struct.archive_entry* %13, i32 0, i32 22, !dbg !464
  store %struct.ae_sparse* %12, %struct.ae_sparse** %sparse_p7, align 8, !dbg !465
  store i32 0, i32* %retval, align 4, !dbg !466
  br label %return, !dbg !466

if.else:                                          ; preds = %entry
  %14 = load i64*, i64** %offset.addr, align 8, !dbg !467
  store i64 0, i64* %14, align 8, !dbg !469
  %15 = load i64*, i64** %length.addr, align 8, !dbg !470
  store i64 0, i64* %15, align 8, !dbg !471
  store i32 -20, i32* %retval, align 4, !dbg !472
  br label %return, !dbg !472

return:                                           ; preds = %if.else, %if.then
  %16 = load i32, i32* %retval, align 4, !dbg !473
  ret i32 %16, !dbg !473
}

attributes #0 = { nounwind uwtable "disable-tail-calls"="false" "less-precise-fpmad"="false" "no-frame-pointer-elim"="true" "no-frame-pointer-elim-non-leaf" "no-infs-fp-math"="false" "no-nans-fp-math"="false" "stack-protector-buffer-size"="8" "target-cpu"="x86-64" "target-features"="+fxsr,+mmx,+sse,+sse2" "unsafe-fp-math"="false" "use-soft-float"="false" }
attributes #1 = { nounwind readnone }
attributes #2 = { nounwind "disable-tail-calls"="false" "less-precise-fpmad"="false" "no-frame-pointer-elim"="true" "no-frame-pointer-elim-non-leaf" "no-infs-fp-math"="false" "no-nans-fp-math"="false" "stack-protector-buffer-size"="8" "target-cpu"="x86-64" "target-features"="+fxsr,+mmx,+sse,+sse2" "unsafe-fp-math"="false" "use-soft-float"="false" }
attributes #3 = { "disable-tail-calls"="false" "less-precise-fpmad"="false" "no-frame-pointer-elim"="true" "no-frame-pointer-elim-non-leaf" "no-infs-fp-math"="false" "no-nans-fp-math"="false" "stack-protector-buffer-size"="8" "target-cpu"="x86-64" "target-features"="+fxsr,+mmx,+sse,+sse2" "unsafe-fp-math"="false" "use-soft-float"="false" }
attributes #4 = { nounwind }

!llvm.dbg.cu = !{!0}
!llvm.module.flags = !{!224, !225}
!llvm.ident = !{!226}

!0 = distinct !DICompileUnit(language: DW_LANG_C99, file: !1, producer: "clang version 3.8.0 (tags/RELEASE_380/final)", isOptimized: false, runtimeVersion: 0, emissionKind: 1, enums: !2, retainedTypes: !3, subprograms: !15)
!1 = !DIFile(filename: "/data/download/cmake/cmake-master/Utilities/cmlibarchive/libarchive/archive_entry_sparse.c", directory: "/data/download/cmake/cmake-master/Utilities/cmlibarchive/libarchive")
!2 = !{}
!3 = !{!4, !5}
!4 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: null, size: 64, align: 64)
!5 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !6, size: 64, align: 64)
!6 = !DICompositeType(tag: DW_TAG_structure_type, name: "ae_sparse", file: !7, line: 46, size: 192, align: 64, elements: !8)
!7 = !DIFile(filename: "/data/download/cmake/cmake-master/Utilities/cmlibarchive/libarchive/archive_entry_private.h", directory: "/data/download/cmake/cmake-master/Utilities/cmlibarchive/libarchive")
!8 = !{!9, !10, !14}
!9 = !DIDerivedType(tag: DW_TAG_member, name: "next", scope: !6, file: !7, line: 47, baseType: !5, size: 64, align: 64)
!10 = !DIDerivedType(tag: DW_TAG_member, name: "offset", scope: !6, file: !7, line: 49, baseType: !11, size: 64, align: 64, offset: 64)
!11 = !DIDerivedType(tag: DW_TAG_typedef, name: "int64_t", file: !12, line: 40, baseType: !13)
!12 = !DIFile(filename: "/usr/include/stdint.h", directory: "/data/download/cmake/cmake-master/Utilities/cmlibarchive/libarchive")
!13 = !DIBasicType(name: "long int", size: 64, align: 64, encoding: DW_ATE_signed)
!14 = !DIDerivedType(tag: DW_TAG_member, name: "length", scope: !6, file: !7, line: 50, baseType: !11, size: 64, align: 64, offset: 128)
!15 = !{!16, !214, !217, !220, !221}
!16 = distinct !DISubprogram(name: "archive_entry_sparse_clear", scope: !1, file: !1, line: 40, type: !17, isLocal: false, isDefinition: true, scopeLine: 41, flags: DIFlagPrototyped, isOptimized: false, variables: !2)
!17 = !DISubroutineType(types: !18)
!18 = !{null, !19}
!19 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !20, size: 64, align: 64)
!20 = !DICompositeType(tag: DW_TAG_structure_type, name: "archive_entry", file: !7, line: 73, size: 8640, align: 64, elements: !21)
!21 = !{!22, !118, !119, !120, !149, !150, !165, !166, !167, !168, !169, !170, !171, !172, !173, !174, !175, !176, !198, !206, !207, !208, !209, !210}
!22 = !DIDerivedType(tag: DW_TAG_member, name: "archive", scope: !20, file: !7, line: 74, baseType: !23, size: 64, align: 64)
!23 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !24, size: 64, align: 64)
!24 = !DICompositeType(tag: DW_TAG_structure_type, name: "archive", file: !25, line: 89, size: 1280, align: 64, elements: !26)
!25 = !DIFile(filename: "/data/download/cmake/cmake-master/Utilities/cmlibarchive/libarchive/archive_private.h", directory: "/data/download/cmake/cmake-master/Utilities/cmlibarchive/libarchive")
!26 = !{!27, !29, !30, !91, !92, !93, !94, !95, !96, !97, !98, !106, !107, !108, !109, !112, !113, !114, !115, !116, !117}
!27 = !DIDerivedType(tag: DW_TAG_member, name: "magic", scope: !24, file: !25, line: 96, baseType: !28, size: 32, align: 32)
!28 = !DIBasicType(name: "unsigned int", size: 32, align: 32, encoding: DW_ATE_unsigned)
!29 = !DIDerivedType(tag: DW_TAG_member, name: "state", scope: !24, file: !25, line: 97, baseType: !28, size: 32, align: 32, offset: 32)
!30 = !DIDerivedType(tag: DW_TAG_member, name: "vtable", scope: !24, file: !25, line: 103, baseType: !31, size: 64, align: 64, offset: 64)
!31 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !32, size: 64, align: 64)
!32 = !DICompositeType(tag: DW_TAG_structure_type, name: "archive_vtable", file: !25, line: 63, size: 832, align: 64, elements: !33)
!33 = !{!34, !39, !40, !44, !45, !58, !62, !67, !68, !75, !76, !80, !84}
!34 = !DIDerivedType(tag: DW_TAG_member, name: "archive_close", scope: !32, file: !25, line: 64, baseType: !35, size: 64, align: 64)
!35 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !36, size: 64, align: 64)
!36 = !DISubroutineType(types: !37)
!37 = !{!38, !23}
!38 = !DIBasicType(name: "int", size: 32, align: 32, encoding: DW_ATE_signed)
!39 = !DIDerivedType(tag: DW_TAG_member, name: "archive_free", scope: !32, file: !25, line: 65, baseType: !35, size: 64, align: 64, offset: 64)
!40 = !DIDerivedType(tag: DW_TAG_member, name: "archive_write_header", scope: !32, file: !25, line: 66, baseType: !41, size: 64, align: 64, offset: 128)
!41 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !42, size: 64, align: 64)
!42 = !DISubroutineType(types: !43)
!43 = !{!38, !23, !19}
!44 = !DIDerivedType(tag: DW_TAG_member, name: "archive_write_finish_entry", scope: !32, file: !25, line: 68, baseType: !35, size: 64, align: 64, offset: 192)
!45 = !DIDerivedType(tag: DW_TAG_member, name: "archive_write_data", scope: !32, file: !25, line: 69, baseType: !46, size: 64, align: 64, offset: 256)
!46 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !47, size: 64, align: 64)
!47 = !DISubroutineType(types: !48)
!48 = !{!49, !23, !53, !55}
!49 = !DIDerivedType(tag: DW_TAG_typedef, name: "ssize_t", file: !50, line: 102, baseType: !51)
!50 = !DIFile(filename: "/usr/include/stdio.h", directory: "/data/download/cmake/cmake-master/Utilities/cmlibarchive/libarchive")
!51 = !DIDerivedType(tag: DW_TAG_typedef, name: "__ssize_t", file: !52, line: 172, baseType: !13)
!52 = !DIFile(filename: "/usr/include/x86_64-linux-gnu/bits/types.h", directory: "/data/download/cmake/cmake-master/Utilities/cmlibarchive/libarchive")
!53 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !54, size: 64, align: 64)
!54 = !DIDerivedType(tag: DW_TAG_const_type, baseType: null)
!55 = !DIDerivedType(tag: DW_TAG_typedef, name: "size_t", file: !56, line: 62, baseType: !57)
!56 = !DIFile(filename: "/opt/llvm-build/bin/../lib/clang/3.8.0/include/stddef.h", directory: "/data/download/cmake/cmake-master/Utilities/cmlibarchive/libarchive")
!57 = !DIBasicType(name: "long unsigned int", size: 64, align: 64, encoding: DW_ATE_unsigned)
!58 = !DIDerivedType(tag: DW_TAG_member, name: "archive_write_data_block", scope: !32, file: !25, line: 71, baseType: !59, size: 64, align: 64, offset: 320)
!59 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !60, size: 64, align: 64)
!60 = !DISubroutineType(types: !61)
!61 = !{!49, !23, !53, !55, !11}
!62 = !DIDerivedType(tag: DW_TAG_member, name: "archive_read_next_header", scope: !32, file: !25, line: 74, baseType: !63, size: 64, align: 64, offset: 384)
!63 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !64, size: 64, align: 64)
!64 = !DISubroutineType(types: !65)
!65 = !{!38, !23, !66}
!66 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !19, size: 64, align: 64)
!67 = !DIDerivedType(tag: DW_TAG_member, name: "archive_read_next_header2", scope: !32, file: !25, line: 76, baseType: !41, size: 64, align: 64, offset: 448)
!68 = !DIDerivedType(tag: DW_TAG_member, name: "archive_read_data_block", scope: !32, file: !25, line: 78, baseType: !69, size: 64, align: 64, offset: 512)
!69 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !70, size: 64, align: 64)
!70 = !DISubroutineType(types: !71)
!71 = !{!38, !23, !72, !73, !74}
!72 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !53, size: 64, align: 64)
!73 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !55, size: 64, align: 64)
!74 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !11, size: 64, align: 64)
!75 = !DIDerivedType(tag: DW_TAG_member, name: "archive_filter_count", scope: !32, file: !25, line: 81, baseType: !35, size: 64, align: 64, offset: 576)
!76 = !DIDerivedType(tag: DW_TAG_member, name: "archive_filter_bytes", scope: !32, file: !25, line: 82, baseType: !77, size: 64, align: 64, offset: 640)
!77 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !78, size: 64, align: 64)
!78 = !DISubroutineType(types: !79)
!79 = !{!11, !23, !38}
!80 = !DIDerivedType(tag: DW_TAG_member, name: "archive_filter_code", scope: !32, file: !25, line: 83, baseType: !81, size: 64, align: 64, offset: 704)
!81 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !82, size: 64, align: 64)
!82 = !DISubroutineType(types: !83)
!83 = !{!38, !23, !38}
!84 = !DIDerivedType(tag: DW_TAG_member, name: "archive_filter_name", scope: !32, file: !25, line: 84, baseType: !85, size: 64, align: 64, offset: 768)
!85 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !86, size: 64, align: 64)
!86 = !DISubroutineType(types: !87)
!87 = !{!88, !23, !38}
!88 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !89, size: 64, align: 64)
!89 = !DIDerivedType(tag: DW_TAG_const_type, baseType: !90)
!90 = !DIBasicType(name: "char", size: 8, align: 8, encoding: DW_ATE_signed_char)
!91 = !DIDerivedType(tag: DW_TAG_member, name: "archive_format", scope: !24, file: !25, line: 105, baseType: !38, size: 32, align: 32, offset: 128)
!92 = !DIDerivedType(tag: DW_TAG_member, name: "archive_format_name", scope: !24, file: !25, line: 106, baseType: !88, size: 64, align: 64, offset: 192)
!93 = !DIDerivedType(tag: DW_TAG_member, name: "compression_code", scope: !24, file: !25, line: 108, baseType: !38, size: 32, align: 32, offset: 256)
!94 = !DIDerivedType(tag: DW_TAG_member, name: "compression_name", scope: !24, file: !25, line: 109, baseType: !88, size: 64, align: 64, offset: 320)
!95 = !DIDerivedType(tag: DW_TAG_member, name: "file_count", scope: !24, file: !25, line: 112, baseType: !38, size: 32, align: 32, offset: 384)
!96 = !DIDerivedType(tag: DW_TAG_member, name: "archive_error_number", scope: !24, file: !25, line: 114, baseType: !38, size: 32, align: 32, offset: 416)
!97 = !DIDerivedType(tag: DW_TAG_member, name: "error", scope: !24, file: !25, line: 115, baseType: !88, size: 64, align: 64, offset: 448)
!98 = !DIDerivedType(tag: DW_TAG_member, name: "error_string", scope: !24, file: !25, line: 116, baseType: !99, size: 192, align: 64, offset: 512)
!99 = !DICompositeType(tag: DW_TAG_structure_type, name: "archive_string", file: !100, line: 58, size: 192, align: 64, elements: !101)
!100 = !DIFile(filename: "/data/download/cmake/cmake-master/Utilities/cmlibarchive/libarchive/archive_string.h", directory: "/data/download/cmake/cmake-master/Utilities/cmlibarchive/libarchive")
!101 = !{!102, !104, !105}
!102 = !DIDerivedType(tag: DW_TAG_member, name: "s", scope: !99, file: !100, line: 59, baseType: !103, size: 64, align: 64)
!103 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !90, size: 64, align: 64)
!104 = !DIDerivedType(tag: DW_TAG_member, name: "length", scope: !99, file: !100, line: 60, baseType: !55, size: 64, align: 64, offset: 64)
!105 = !DIDerivedType(tag: DW_TAG_member, name: "buffer_length", scope: !99, file: !100, line: 61, baseType: !55, size: 64, align: 64, offset: 128)
!106 = !DIDerivedType(tag: DW_TAG_member, name: "current_code", scope: !24, file: !25, line: 118, baseType: !103, size: 64, align: 64, offset: 704)
!107 = !DIDerivedType(tag: DW_TAG_member, name: "current_codepage", scope: !24, file: !25, line: 119, baseType: !28, size: 32, align: 32, offset: 768)
!108 = !DIDerivedType(tag: DW_TAG_member, name: "current_oemcp", scope: !24, file: !25, line: 120, baseType: !28, size: 32, align: 32, offset: 800)
!109 = !DIDerivedType(tag: DW_TAG_member, name: "sconv", scope: !24, file: !25, line: 121, baseType: !110, size: 64, align: 64, offset: 832)
!110 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !111, size: 64, align: 64)
!111 = !DICompositeType(tag: DW_TAG_structure_type, name: "archive_string_conv", file: !100, line: 70, flags: DIFlagFwdDecl)
!112 = !DIDerivedType(tag: DW_TAG_member, name: "read_data_block", scope: !24, file: !25, line: 127, baseType: !88, size: 64, align: 64, offset: 896)
!113 = !DIDerivedType(tag: DW_TAG_member, name: "read_data_offset", scope: !24, file: !25, line: 128, baseType: !11, size: 64, align: 64, offset: 960)
!114 = !DIDerivedType(tag: DW_TAG_member, name: "read_data_output_offset", scope: !24, file: !25, line: 129, baseType: !11, size: 64, align: 64, offset: 1024)
!115 = !DIDerivedType(tag: DW_TAG_member, name: "read_data_remaining", scope: !24, file: !25, line: 130, baseType: !55, size: 64, align: 64, offset: 1088)
!116 = !DIDerivedType(tag: DW_TAG_member, name: "read_data_is_posix_read", scope: !24, file: !25, line: 137, baseType: !90, size: 8, align: 8, offset: 1152)
!117 = !DIDerivedType(tag: DW_TAG_member, name: "read_data_requested", scope: !24, file: !25, line: 138, baseType: !55, size: 64, align: 64, offset: 1216)
!118 = !DIDerivedType(tag: DW_TAG_member, name: "stat", scope: !20, file: !7, line: 96, baseType: !4, size: 64, align: 64, offset: 64)
!119 = !DIDerivedType(tag: DW_TAG_member, name: "stat_valid", scope: !20, file: !7, line: 97, baseType: !38, size: 32, align: 32, offset: 128)
!120 = !DIDerivedType(tag: DW_TAG_member, name: "ae_stat", scope: !20, file: !7, line: 129, baseType: !121, size: 1344, align: 64, offset: 192)
!121 = !DICompositeType(tag: DW_TAG_structure_type, name: "aest", file: !7, line: 99, size: 1344, align: 64, elements: !122)
!122 = !{!123, !124, !126, !127, !128, !129, !130, !131, !132, !133, !134, !135, !137, !138, !139, !143, !144, !145, !146, !147, !148}
!123 = !DIDerivedType(tag: DW_TAG_member, name: "aest_atime", scope: !121, file: !7, line: 100, baseType: !11, size: 64, align: 64)
!124 = !DIDerivedType(tag: DW_TAG_member, name: "aest_atime_nsec", scope: !121, file: !7, line: 101, baseType: !125, size: 32, align: 32, offset: 64)
!125 = !DIDerivedType(tag: DW_TAG_typedef, name: "uint32_t", file: !12, line: 51, baseType: !28)
!126 = !DIDerivedType(tag: DW_TAG_member, name: "aest_ctime", scope: !121, file: !7, line: 102, baseType: !11, size: 64, align: 64, offset: 128)
!127 = !DIDerivedType(tag: DW_TAG_member, name: "aest_ctime_nsec", scope: !121, file: !7, line: 103, baseType: !125, size: 32, align: 32, offset: 192)
!128 = !DIDerivedType(tag: DW_TAG_member, name: "aest_mtime", scope: !121, file: !7, line: 104, baseType: !11, size: 64, align: 64, offset: 256)
!129 = !DIDerivedType(tag: DW_TAG_member, name: "aest_mtime_nsec", scope: !121, file: !7, line: 105, baseType: !125, size: 32, align: 32, offset: 320)
!130 = !DIDerivedType(tag: DW_TAG_member, name: "aest_birthtime", scope: !121, file: !7, line: 106, baseType: !11, size: 64, align: 64, offset: 384)
!131 = !DIDerivedType(tag: DW_TAG_member, name: "aest_birthtime_nsec", scope: !121, file: !7, line: 107, baseType: !125, size: 32, align: 32, offset: 448)
!132 = !DIDerivedType(tag: DW_TAG_member, name: "aest_gid", scope: !121, file: !7, line: 108, baseType: !11, size: 64, align: 64, offset: 512)
!133 = !DIDerivedType(tag: DW_TAG_member, name: "aest_ino", scope: !121, file: !7, line: 109, baseType: !11, size: 64, align: 64, offset: 576)
!134 = !DIDerivedType(tag: DW_TAG_member, name: "aest_nlink", scope: !121, file: !7, line: 110, baseType: !125, size: 32, align: 32, offset: 640)
!135 = !DIDerivedType(tag: DW_TAG_member, name: "aest_size", scope: !121, file: !7, line: 111, baseType: !136, size: 64, align: 64, offset: 704)
!136 = !DIDerivedType(tag: DW_TAG_typedef, name: "uint64_t", file: !12, line: 55, baseType: !57)
!137 = !DIDerivedType(tag: DW_TAG_member, name: "aest_uid", scope: !121, file: !7, line: 112, baseType: !11, size: 64, align: 64, offset: 768)
!138 = !DIDerivedType(tag: DW_TAG_member, name: "aest_dev_is_broken_down", scope: !121, file: !7, line: 121, baseType: !38, size: 32, align: 32, offset: 832)
!139 = !DIDerivedType(tag: DW_TAG_member, name: "aest_dev", scope: !121, file: !7, line: 122, baseType: !140, size: 64, align: 64, offset: 896)
!140 = !DIDerivedType(tag: DW_TAG_typedef, name: "dev_t", file: !141, line: 44, baseType: !142)
!141 = !DIFile(filename: "/usr/include/x86_64-linux-gnu/sys/stat.h", directory: "/data/download/cmake/cmake-master/Utilities/cmlibarchive/libarchive")
!142 = !DIDerivedType(tag: DW_TAG_typedef, name: "__dev_t", file: !52, line: 124, baseType: !57)
!143 = !DIDerivedType(tag: DW_TAG_member, name: "aest_devmajor", scope: !121, file: !7, line: 123, baseType: !140, size: 64, align: 64, offset: 960)
!144 = !DIDerivedType(tag: DW_TAG_member, name: "aest_devminor", scope: !121, file: !7, line: 124, baseType: !140, size: 64, align: 64, offset: 1024)
!145 = !DIDerivedType(tag: DW_TAG_member, name: "aest_rdev_is_broken_down", scope: !121, file: !7, line: 125, baseType: !38, size: 32, align: 32, offset: 1088)
!146 = !DIDerivedType(tag: DW_TAG_member, name: "aest_rdev", scope: !121, file: !7, line: 126, baseType: !140, size: 64, align: 64, offset: 1152)
!147 = !DIDerivedType(tag: DW_TAG_member, name: "aest_rdevmajor", scope: !121, file: !7, line: 127, baseType: !140, size: 64, align: 64, offset: 1216)
!148 = !DIDerivedType(tag: DW_TAG_member, name: "aest_rdevminor", scope: !121, file: !7, line: 128, baseType: !140, size: 64, align: 64, offset: 1280)
!149 = !DIDerivedType(tag: DW_TAG_member, name: "ae_set", scope: !20, file: !7, line: 131, baseType: !38, size: 32, align: 32, offset: 1536)
!150 = !DIDerivedType(tag: DW_TAG_member, name: "ae_fflags_text", scope: !20, file: !7, line: 145, baseType: !151, size: 832, align: 64, offset: 1600)
!151 = !DICompositeType(tag: DW_TAG_structure_type, name: "archive_mstring", file: !100, line: 209, size: 832, align: 64, elements: !152)
!152 = !{!153, !154, !155, !163, !164}
!153 = !DIDerivedType(tag: DW_TAG_member, name: "aes_mbs", scope: !151, file: !100, line: 210, baseType: !99, size: 192, align: 64)
!154 = !DIDerivedType(tag: DW_TAG_member, name: "aes_utf8", scope: !151, file: !100, line: 211, baseType: !99, size: 192, align: 64, offset: 192)
!155 = !DIDerivedType(tag: DW_TAG_member, name: "aes_wcs", scope: !151, file: !100, line: 212, baseType: !156, size: 192, align: 64, offset: 384)
!156 = !DICompositeType(tag: DW_TAG_structure_type, name: "archive_wstring", file: !100, line: 64, size: 192, align: 64, elements: !157)
!157 = !{!158, !161, !162}
!158 = !DIDerivedType(tag: DW_TAG_member, name: "s", scope: !156, file: !100, line: 65, baseType: !159, size: 64, align: 64)
!159 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !160, size: 64, align: 64)
!160 = !DIDerivedType(tag: DW_TAG_typedef, name: "wchar_t", file: !56, line: 90, baseType: !38)
!161 = !DIDerivedType(tag: DW_TAG_member, name: "length", scope: !156, file: !100, line: 66, baseType: !55, size: 64, align: 64, offset: 64)
!162 = !DIDerivedType(tag: DW_TAG_member, name: "buffer_length", scope: !156, file: !100, line: 67, baseType: !55, size: 64, align: 64, offset: 128)
!163 = !DIDerivedType(tag: DW_TAG_member, name: "aes_mbs_in_locale", scope: !151, file: !100, line: 213, baseType: !99, size: 192, align: 64, offset: 576)
!164 = !DIDerivedType(tag: DW_TAG_member, name: "aes_set", scope: !151, file: !100, line: 218, baseType: !38, size: 32, align: 32, offset: 768)
!165 = !DIDerivedType(tag: DW_TAG_member, name: "ae_fflags_set", scope: !20, file: !7, line: 146, baseType: !57, size: 64, align: 64, offset: 2432)
!166 = !DIDerivedType(tag: DW_TAG_member, name: "ae_fflags_clear", scope: !20, file: !7, line: 147, baseType: !57, size: 64, align: 64, offset: 2496)
!167 = !DIDerivedType(tag: DW_TAG_member, name: "ae_gname", scope: !20, file: !7, line: 148, baseType: !151, size: 832, align: 64, offset: 2560)
!168 = !DIDerivedType(tag: DW_TAG_member, name: "ae_hardlink", scope: !20, file: !7, line: 149, baseType: !151, size: 832, align: 64, offset: 3392)
!169 = !DIDerivedType(tag: DW_TAG_member, name: "ae_pathname", scope: !20, file: !7, line: 150, baseType: !151, size: 832, align: 64, offset: 4224)
!170 = !DIDerivedType(tag: DW_TAG_member, name: "ae_symlink", scope: !20, file: !7, line: 151, baseType: !151, size: 832, align: 64, offset: 5056)
!171 = !DIDerivedType(tag: DW_TAG_member, name: "ae_uname", scope: !20, file: !7, line: 152, baseType: !151, size: 832, align: 64, offset: 5888)
!172 = !DIDerivedType(tag: DW_TAG_member, name: "ae_sourcepath", scope: !20, file: !7, line: 155, baseType: !151, size: 832, align: 64, offset: 6720)
!173 = !DIDerivedType(tag: DW_TAG_member, name: "encryption", scope: !20, file: !7, line: 160, baseType: !90, size: 8, align: 8, offset: 7552)
!174 = !DIDerivedType(tag: DW_TAG_member, name: "mac_metadata", scope: !20, file: !7, line: 162, baseType: !4, size: 64, align: 64, offset: 7616)
!175 = !DIDerivedType(tag: DW_TAG_member, name: "mac_metadata_size", scope: !20, file: !7, line: 163, baseType: !55, size: 64, align: 64, offset: 7680)
!176 = !DIDerivedType(tag: DW_TAG_member, name: "acl", scope: !20, file: !7, line: 166, baseType: !177, size: 448, align: 64, offset: 7744)
!177 = !DICompositeType(tag: DW_TAG_structure_type, name: "archive_acl", file: !178, line: 46, size: 448, align: 64, elements: !179)
!178 = !DIFile(filename: "/data/download/cmake/cmake-master/Utilities/cmlibarchive/libarchive/archive_acl_private.h", directory: "/data/download/cmake/cmake-master/Utilities/cmlibarchive/libarchive")
!179 = !{!180, !183, !193, !194, !195, !196, !197}
!180 = !DIDerivedType(tag: DW_TAG_member, name: "mode", scope: !177, file: !178, line: 47, baseType: !181, size: 32, align: 32)
!181 = !DIDerivedType(tag: DW_TAG_typedef, name: "mode_t", file: !141, line: 63, baseType: !182)
!182 = !DIDerivedType(tag: DW_TAG_typedef, name: "__mode_t", file: !52, line: 129, baseType: !28)
!183 = !DIDerivedType(tag: DW_TAG_member, name: "acl_head", scope: !177, file: !178, line: 48, baseType: !184, size: 64, align: 64, offset: 64)
!184 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !185, size: 64, align: 64)
!185 = !DICompositeType(tag: DW_TAG_structure_type, name: "archive_acl_entry", file: !178, line: 37, size: 1024, align: 64, elements: !186)
!186 = !{!187, !188, !189, !190, !191, !192}
!187 = !DIDerivedType(tag: DW_TAG_member, name: "next", scope: !185, file: !178, line: 38, baseType: !184, size: 64, align: 64)
!188 = !DIDerivedType(tag: DW_TAG_member, name: "type", scope: !185, file: !178, line: 39, baseType: !38, size: 32, align: 32, offset: 64)
!189 = !DIDerivedType(tag: DW_TAG_member, name: "tag", scope: !185, file: !178, line: 40, baseType: !38, size: 32, align: 32, offset: 96)
!190 = !DIDerivedType(tag: DW_TAG_member, name: "permset", scope: !185, file: !178, line: 41, baseType: !38, size: 32, align: 32, offset: 128)
!191 = !DIDerivedType(tag: DW_TAG_member, name: "id", scope: !185, file: !178, line: 42, baseType: !38, size: 32, align: 32, offset: 160)
!192 = !DIDerivedType(tag: DW_TAG_member, name: "name", scope: !185, file: !178, line: 43, baseType: !151, size: 832, align: 64, offset: 192)
!193 = !DIDerivedType(tag: DW_TAG_member, name: "acl_p", scope: !177, file: !178, line: 49, baseType: !184, size: 64, align: 64, offset: 128)
!194 = !DIDerivedType(tag: DW_TAG_member, name: "acl_state", scope: !177, file: !178, line: 50, baseType: !38, size: 32, align: 32, offset: 192)
!195 = !DIDerivedType(tag: DW_TAG_member, name: "acl_text_w", scope: !177, file: !178, line: 51, baseType: !159, size: 64, align: 64, offset: 256)
!196 = !DIDerivedType(tag: DW_TAG_member, name: "acl_text", scope: !177, file: !178, line: 52, baseType: !103, size: 64, align: 64, offset: 320)
!197 = !DIDerivedType(tag: DW_TAG_member, name: "acl_types", scope: !177, file: !178, line: 53, baseType: !38, size: 32, align: 32, offset: 384)
!198 = !DIDerivedType(tag: DW_TAG_member, name: "xattr_head", scope: !20, file: !7, line: 169, baseType: !199, size: 64, align: 64, offset: 8192)
!199 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !200, size: 64, align: 64)
!200 = !DICompositeType(tag: DW_TAG_structure_type, name: "ae_xattr", file: !7, line: 38, size: 256, align: 64, elements: !201)
!201 = !{!202, !203, !204, !205}
!202 = !DIDerivedType(tag: DW_TAG_member, name: "next", scope: !200, file: !7, line: 39, baseType: !199, size: 64, align: 64)
!203 = !DIDerivedType(tag: DW_TAG_member, name: "name", scope: !200, file: !7, line: 41, baseType: !103, size: 64, align: 64, offset: 64)
!204 = !DIDerivedType(tag: DW_TAG_member, name: "value", scope: !200, file: !7, line: 42, baseType: !4, size: 64, align: 64, offset: 128)
!205 = !DIDerivedType(tag: DW_TAG_member, name: "size", scope: !200, file: !7, line: 43, baseType: !55, size: 64, align: 64, offset: 192)
!206 = !DIDerivedType(tag: DW_TAG_member, name: "xattr_p", scope: !20, file: !7, line: 170, baseType: !199, size: 64, align: 64, offset: 8256)
!207 = !DIDerivedType(tag: DW_TAG_member, name: "sparse_head", scope: !20, file: !7, line: 173, baseType: !5, size: 64, align: 64, offset: 8320)
!208 = !DIDerivedType(tag: DW_TAG_member, name: "sparse_tail", scope: !20, file: !7, line: 174, baseType: !5, size: 64, align: 64, offset: 8384)
!209 = !DIDerivedType(tag: DW_TAG_member, name: "sparse_p", scope: !20, file: !7, line: 175, baseType: !5, size: 64, align: 64, offset: 8448)
!210 = !DIDerivedType(tag: DW_TAG_member, name: "strmode", scope: !20, file: !7, line: 178, baseType: !211, size: 96, align: 8, offset: 8512)
!211 = !DICompositeType(tag: DW_TAG_array_type, baseType: !90, size: 96, align: 8, elements: !212)
!212 = !{!213}
!213 = !DISubrange(count: 12)
!214 = distinct !DISubprogram(name: "archive_entry_sparse_add_entry", scope: !1, file: !1, line: 53, type: !215, isLocal: false, isDefinition: true, scopeLine: 55, flags: DIFlagPrototyped, isOptimized: false, variables: !2)
!215 = !DISubroutineType(types: !216)
!216 = !{null, !19, !11, !11}
!217 = distinct !DISubprogram(name: "archive_entry_sparse_count", scope: !1, file: !1, line: 103, type: !218, isLocal: false, isDefinition: true, scopeLine: 104, flags: DIFlagPrototyped, isOptimized: false, variables: !2)
!218 = !DISubroutineType(types: !219)
!219 = !{!38, !19}
!220 = distinct !DISubprogram(name: "archive_entry_sparse_reset", scope: !1, file: !1, line: 129, type: !218, isLocal: false, isDefinition: true, scopeLine: 130, flags: DIFlagPrototyped, isOptimized: false, variables: !2)
!221 = distinct !DISubprogram(name: "archive_entry_sparse_next", scope: !1, file: !1, line: 137, type: !222, isLocal: false, isDefinition: true, scopeLine: 139, flags: DIFlagPrototyped, isOptimized: false, variables: !2)
!222 = !DISubroutineType(types: !223)
!223 = !{!38, !19, !74, !74}
!224 = !{i32 2, !"Dwarf Version", i32 4}
!225 = !{i32 2, !"Debug Info Version", i32 3}
!226 = !{!"clang version 3.8.0 (tags/RELEASE_380/final)"}
!227 = !DILocalVariable(name: "entry", arg: 1, scope: !16, file: !1, line: 40, type: !19)
!228 = !DIExpression()
!229 = !DILocation(line: 40, column: 50, scope: !16)
!230 = !DILocalVariable(name: "sp", scope: !16, file: !1, line: 42, type: !5)
!231 = !DILocation(line: 42, column: 20, scope: !16)
!232 = !DILocation(line: 44, column: 2, scope: !16)
!233 = !DILocation(line: 44, column: 9, scope: !234)
!234 = !DILexicalBlockFile(scope: !16, file: !1, discriminator: 1)
!235 = !DILocation(line: 44, column: 16, scope: !234)
!236 = !DILocation(line: 44, column: 28, scope: !234)
!237 = !DILocation(line: 44, column: 2, scope: !234)
!238 = !DILocation(line: 45, column: 8, scope: !239)
!239 = distinct !DILexicalBlock(scope: !16, file: !1, line: 44, column: 37)
!240 = !DILocation(line: 45, column: 15, scope: !239)
!241 = !DILocation(line: 45, column: 28, scope: !239)
!242 = !DILocation(line: 45, column: 6, scope: !239)
!243 = !DILocation(line: 46, column: 8, scope: !239)
!244 = !DILocation(line: 46, column: 15, scope: !239)
!245 = !DILocation(line: 46, column: 3, scope: !239)
!246 = !DILocation(line: 47, column: 24, scope: !239)
!247 = !DILocation(line: 47, column: 3, scope: !239)
!248 = !DILocation(line: 47, column: 10, scope: !239)
!249 = !DILocation(line: 47, column: 22, scope: !239)
!250 = !DILocation(line: 44, column: 2, scope: !251)
!251 = !DILexicalBlockFile(scope: !16, file: !1, discriminator: 2)
!252 = !DILocation(line: 49, column: 2, scope: !16)
!253 = !DILocation(line: 49, column: 9, scope: !16)
!254 = !DILocation(line: 49, column: 21, scope: !16)
!255 = !DILocation(line: 50, column: 1, scope: !16)
!256 = !DILocalVariable(name: "entry", arg: 1, scope: !214, file: !1, line: 53, type: !19)
!257 = !DILocation(line: 53, column: 54, scope: !214)
!258 = !DILocalVariable(name: "offset", arg: 2, scope: !214, file: !1, line: 54, type: !11)
!259 = !DILocation(line: 54, column: 10, scope: !214)
!260 = !DILocalVariable(name: "length", arg: 3, scope: !214, file: !1, line: 54, type: !11)
!261 = !DILocation(line: 54, column: 26, scope: !214)
!262 = !DILocalVariable(name: "sp", scope: !214, file: !1, line: 56, type: !5)
!263 = !DILocation(line: 56, column: 20, scope: !214)
!264 = !DILocation(line: 58, column: 6, scope: !265)
!265 = distinct !DILexicalBlock(scope: !214, file: !1, line: 58, column: 6)
!266 = !DILocation(line: 58, column: 13, scope: !265)
!267 = !DILocation(line: 58, column: 17, scope: !265)
!268 = !DILocation(line: 58, column: 20, scope: !269)
!269 = !DILexicalBlockFile(scope: !265, file: !1, discriminator: 1)
!270 = !DILocation(line: 58, column: 27, scope: !269)
!271 = !DILocation(line: 58, column: 6, scope: !269)
!272 = !DILocation(line: 60, column: 3, scope: !265)
!273 = !DILocation(line: 61, column: 6, scope: !274)
!274 = distinct !DILexicalBlock(scope: !214, file: !1, line: 61, column: 6)
!275 = !DILocation(line: 61, column: 27, scope: !274)
!276 = !DILocation(line: 61, column: 25, scope: !274)
!277 = !DILocation(line: 61, column: 13, scope: !274)
!278 = !DILocation(line: 61, column: 34, scope: !274)
!279 = !DILocation(line: 62, column: 6, scope: !274)
!280 = !DILocation(line: 62, column: 15, scope: !274)
!281 = !DILocation(line: 62, column: 13, scope: !274)
!282 = !DILocation(line: 62, column: 43, scope: !274)
!283 = !DILocation(line: 62, column: 24, scope: !274)
!284 = !DILocation(line: 62, column: 22, scope: !274)
!285 = !DILocation(line: 61, column: 6, scope: !286)
!286 = !DILexicalBlockFile(scope: !214, file: !1, discriminator: 1)
!287 = !DILocation(line: 64, column: 3, scope: !274)
!288 = !DILocation(line: 65, column: 12, scope: !289)
!289 = distinct !DILexicalBlock(scope: !214, file: !1, line: 65, column: 6)
!290 = !DILocation(line: 65, column: 19, scope: !289)
!291 = !DILocation(line: 65, column: 10, scope: !289)
!292 = !DILocation(line: 65, column: 32, scope: !289)
!293 = !DILocation(line: 65, column: 6, scope: !214)
!294 = !DILocation(line: 66, column: 7, scope: !295)
!295 = distinct !DILexicalBlock(scope: !296, file: !1, line: 66, column: 7)
!296 = distinct !DILexicalBlock(scope: !289, file: !1, line: 65, column: 41)
!297 = !DILocation(line: 66, column: 11, scope: !295)
!298 = !DILocation(line: 66, column: 20, scope: !295)
!299 = !DILocation(line: 66, column: 24, scope: !295)
!300 = !DILocation(line: 66, column: 18, scope: !295)
!301 = !DILocation(line: 66, column: 33, scope: !295)
!302 = !DILocation(line: 66, column: 31, scope: !295)
!303 = !DILocation(line: 66, column: 7, scope: !296)
!304 = !DILocation(line: 68, column: 4, scope: !295)
!305 = !DILocation(line: 69, column: 7, scope: !306)
!306 = distinct !DILexicalBlock(scope: !296, file: !1, line: 69, column: 7)
!307 = !DILocation(line: 69, column: 11, scope: !306)
!308 = !DILocation(line: 69, column: 20, scope: !306)
!309 = !DILocation(line: 69, column: 24, scope: !306)
!310 = !DILocation(line: 69, column: 18, scope: !306)
!311 = !DILocation(line: 69, column: 34, scope: !306)
!312 = !DILocation(line: 69, column: 31, scope: !306)
!313 = !DILocation(line: 69, column: 7, scope: !296)
!314 = !DILocation(line: 70, column: 8, scope: !315)
!315 = distinct !DILexicalBlock(scope: !316, file: !1, line: 70, column: 8)
!316 = distinct !DILexicalBlock(scope: !306, file: !1, line: 69, column: 42)
!317 = !DILocation(line: 70, column: 12, scope: !315)
!318 = !DILocation(line: 70, column: 21, scope: !315)
!319 = !DILocation(line: 70, column: 25, scope: !315)
!320 = !DILocation(line: 70, column: 19, scope: !315)
!321 = !DILocation(line: 70, column: 34, scope: !315)
!322 = !DILocation(line: 70, column: 32, scope: !315)
!323 = !DILocation(line: 70, column: 41, scope: !315)
!324 = !DILocation(line: 70, column: 8, scope: !316)
!325 = !DILocation(line: 73, column: 5, scope: !315)
!326 = !DILocation(line: 75, column: 18, scope: !316)
!327 = !DILocation(line: 75, column: 4, scope: !316)
!328 = !DILocation(line: 75, column: 8, scope: !316)
!329 = !DILocation(line: 75, column: 15, scope: !316)
!330 = !DILocation(line: 76, column: 4, scope: !316)
!331 = !DILocation(line: 78, column: 2, scope: !296)
!332 = !DILocation(line: 80, column: 32, scope: !333)
!333 = distinct !DILexicalBlock(scope: !214, file: !1, line: 80, column: 6)
!334 = !DILocation(line: 80, column: 12, scope: !333)
!335 = !DILocation(line: 80, column: 10, scope: !333)
!336 = !DILocation(line: 80, column: 53, scope: !333)
!337 = !DILocation(line: 80, column: 6, scope: !214)
!338 = !DILocation(line: 82, column: 3, scope: !333)
!339 = !DILocation(line: 84, column: 15, scope: !214)
!340 = !DILocation(line: 84, column: 2, scope: !214)
!341 = !DILocation(line: 84, column: 6, scope: !214)
!342 = !DILocation(line: 84, column: 13, scope: !214)
!343 = !DILocation(line: 85, column: 15, scope: !214)
!344 = !DILocation(line: 85, column: 2, scope: !214)
!345 = !DILocation(line: 85, column: 6, scope: !214)
!346 = !DILocation(line: 85, column: 13, scope: !214)
!347 = !DILocation(line: 86, column: 2, scope: !214)
!348 = !DILocation(line: 86, column: 6, scope: !214)
!349 = !DILocation(line: 86, column: 11, scope: !214)
!350 = !DILocation(line: 88, column: 6, scope: !351)
!351 = distinct !DILexicalBlock(scope: !214, file: !1, line: 88, column: 6)
!352 = !DILocation(line: 88, column: 13, scope: !351)
!353 = !DILocation(line: 88, column: 25, scope: !351)
!354 = !DILocation(line: 88, column: 6, scope: !214)
!355 = !DILocation(line: 89, column: 45, scope: !351)
!356 = !DILocation(line: 89, column: 24, scope: !351)
!357 = !DILocation(line: 89, column: 31, scope: !351)
!358 = !DILocation(line: 89, column: 43, scope: !351)
!359 = !DILocation(line: 89, column: 3, scope: !351)
!360 = !DILocation(line: 89, column: 10, scope: !351)
!361 = !DILocation(line: 89, column: 22, scope: !351)
!362 = !DILocation(line: 92, column: 7, scope: !363)
!363 = distinct !DILexicalBlock(scope: !364, file: !1, line: 92, column: 7)
!364 = distinct !DILexicalBlock(scope: !351, file: !1, line: 90, column: 7)
!365 = !DILocation(line: 92, column: 14, scope: !363)
!366 = !DILocation(line: 92, column: 26, scope: !363)
!367 = !DILocation(line: 92, column: 7, scope: !364)
!368 = !DILocation(line: 93, column: 31, scope: !363)
!369 = !DILocation(line: 93, column: 4, scope: !363)
!370 = !DILocation(line: 93, column: 11, scope: !363)
!371 = !DILocation(line: 93, column: 24, scope: !363)
!372 = !DILocation(line: 93, column: 29, scope: !363)
!373 = !DILocation(line: 94, column: 24, scope: !364)
!374 = !DILocation(line: 94, column: 3, scope: !364)
!375 = !DILocation(line: 94, column: 10, scope: !364)
!376 = !DILocation(line: 94, column: 22, scope: !364)
!377 = !DILocation(line: 96, column: 1, scope: !214)
!378 = !DILocalVariable(name: "entry", arg: 1, scope: !217, file: !1, line: 103, type: !19)
!379 = !DILocation(line: 103, column: 50, scope: !217)
!380 = !DILocalVariable(name: "sp", scope: !217, file: !1, line: 105, type: !5)
!381 = !DILocation(line: 105, column: 20, scope: !217)
!382 = !DILocalVariable(name: "count", scope: !217, file: !1, line: 106, type: !38)
!383 = !DILocation(line: 106, column: 6, scope: !217)
!384 = !DILocation(line: 108, column: 12, scope: !385)
!385 = distinct !DILexicalBlock(scope: !217, file: !1, line: 108, column: 2)
!386 = !DILocation(line: 108, column: 19, scope: !385)
!387 = !DILocation(line: 108, column: 10, scope: !385)
!388 = !DILocation(line: 108, column: 7, scope: !385)
!389 = !DILocation(line: 108, column: 32, scope: !390)
!390 = !DILexicalBlockFile(scope: !391, file: !1, discriminator: 1)
!391 = distinct !DILexicalBlock(scope: !385, file: !1, line: 108, column: 2)
!392 = !DILocation(line: 108, column: 35, scope: !390)
!393 = !DILocation(line: 108, column: 2, scope: !390)
!394 = !DILocation(line: 109, column: 8, scope: !391)
!395 = !DILocation(line: 109, column: 3, scope: !391)
!396 = !DILocation(line: 108, column: 49, scope: !397)
!397 = !DILexicalBlockFile(scope: !391, file: !1, discriminator: 2)
!398 = !DILocation(line: 108, column: 53, scope: !397)
!399 = !DILocation(line: 108, column: 47, scope: !397)
!400 = !DILocation(line: 108, column: 2, scope: !397)
!401 = !DILocation(line: 116, column: 6, scope: !402)
!402 = distinct !DILexicalBlock(scope: !217, file: !1, line: 116, column: 6)
!403 = !DILocation(line: 116, column: 12, scope: !402)
!404 = !DILocation(line: 116, column: 6, scope: !217)
!405 = !DILocation(line: 117, column: 8, scope: !406)
!406 = distinct !DILexicalBlock(scope: !402, file: !1, line: 116, column: 18)
!407 = !DILocation(line: 117, column: 15, scope: !406)
!408 = !DILocation(line: 117, column: 6, scope: !406)
!409 = !DILocation(line: 118, column: 7, scope: !410)
!410 = distinct !DILexicalBlock(scope: !406, file: !1, line: 118, column: 7)
!411 = !DILocation(line: 118, column: 11, scope: !410)
!412 = !DILocation(line: 118, column: 18, scope: !410)
!413 = !DILocation(line: 118, column: 23, scope: !410)
!414 = !DILocation(line: 119, column: 7, scope: !410)
!415 = !DILocation(line: 119, column: 11, scope: !410)
!416 = !DILocation(line: 119, column: 40, scope: !410)
!417 = !DILocation(line: 119, column: 21, scope: !410)
!418 = !DILocation(line: 119, column: 18, scope: !410)
!419 = !DILocation(line: 118, column: 7, scope: !420)
!420 = !DILexicalBlockFile(scope: !406, file: !1, discriminator: 1)
!421 = !DILocation(line: 120, column: 10, scope: !422)
!422 = distinct !DILexicalBlock(scope: !410, file: !1, line: 119, column: 48)
!423 = !DILocation(line: 121, column: 31, scope: !422)
!424 = !DILocation(line: 121, column: 4, scope: !422)
!425 = !DILocation(line: 122, column: 3, scope: !422)
!426 = !DILocation(line: 123, column: 2, scope: !406)
!427 = !DILocation(line: 125, column: 10, scope: !217)
!428 = !DILocation(line: 125, column: 2, scope: !217)
!429 = !DILocalVariable(name: "entry", arg: 1, scope: !220, file: !1, line: 129, type: !19)
!430 = !DILocation(line: 129, column: 51, scope: !220)
!431 = !DILocation(line: 131, column: 20, scope: !220)
!432 = !DILocation(line: 131, column: 27, scope: !220)
!433 = !DILocation(line: 131, column: 2, scope: !220)
!434 = !DILocation(line: 131, column: 9, scope: !220)
!435 = !DILocation(line: 131, column: 18, scope: !220)
!436 = !DILocation(line: 133, column: 36, scope: !220)
!437 = !DILocation(line: 133, column: 9, scope: !220)
!438 = !DILocation(line: 133, column: 2, scope: !220)
!439 = !DILocalVariable(name: "entry", arg: 1, scope: !221, file: !1, line: 137, type: !19)
!440 = !DILocation(line: 137, column: 50, scope: !221)
!441 = !DILocalVariable(name: "offset", arg: 2, scope: !221, file: !1, line: 138, type: !74)
!442 = !DILocation(line: 138, column: 11, scope: !221)
!443 = !DILocalVariable(name: "length", arg: 3, scope: !221, file: !1, line: 138, type: !74)
!444 = !DILocation(line: 138, column: 28, scope: !221)
!445 = !DILocation(line: 140, column: 6, scope: !446)
!446 = distinct !DILexicalBlock(scope: !221, file: !1, line: 140, column: 6)
!447 = !DILocation(line: 140, column: 13, scope: !446)
!448 = !DILocation(line: 140, column: 6, scope: !221)
!449 = !DILocation(line: 141, column: 13, scope: !450)
!450 = distinct !DILexicalBlock(scope: !446, file: !1, line: 140, column: 23)
!451 = !DILocation(line: 141, column: 20, scope: !450)
!452 = !DILocation(line: 141, column: 30, scope: !450)
!453 = !DILocation(line: 141, column: 4, scope: !450)
!454 = !DILocation(line: 141, column: 11, scope: !450)
!455 = !DILocation(line: 142, column: 13, scope: !450)
!456 = !DILocation(line: 142, column: 20, scope: !450)
!457 = !DILocation(line: 142, column: 30, scope: !450)
!458 = !DILocation(line: 142, column: 4, scope: !450)
!459 = !DILocation(line: 142, column: 11, scope: !450)
!460 = !DILocation(line: 144, column: 21, scope: !450)
!461 = !DILocation(line: 144, column: 28, scope: !450)
!462 = !DILocation(line: 144, column: 38, scope: !450)
!463 = !DILocation(line: 144, column: 3, scope: !450)
!464 = !DILocation(line: 144, column: 10, scope: !450)
!465 = !DILocation(line: 144, column: 19, scope: !450)
!466 = !DILocation(line: 146, column: 3, scope: !450)
!467 = !DILocation(line: 148, column: 4, scope: !468)
!468 = distinct !DILexicalBlock(scope: !446, file: !1, line: 147, column: 9)
!469 = !DILocation(line: 148, column: 11, scope: !468)
!470 = !DILocation(line: 149, column: 4, scope: !468)
!471 = !DILocation(line: 149, column: 11, scope: !468)
!472 = !DILocation(line: 150, column: 3, scope: !468)
!473 = !DILocation(line: 152, column: 1, scope: !221)
