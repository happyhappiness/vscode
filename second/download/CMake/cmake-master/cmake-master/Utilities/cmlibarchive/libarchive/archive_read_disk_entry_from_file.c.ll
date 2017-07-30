; ModuleID = '/data/download/cmake/cmake-master/Utilities/cmlibarchive/libarchive/archive_read_disk_entry_from_file.c'
target datalayout = "e-m:e-i64:64-f80:128-n8:16:32:64-S128"
target triple = "x86_64-unknown-linux-gnu"

%struct.archive = type { i32, i32, %struct.archive_vtable*, i32, i8*, i32, i8*, i32, i32, i8*, %struct.archive_string, i8*, i32, i32, %struct.archive_string_conv*, i8*, i64, i64, i64, i8, i64 }
%struct.archive_vtable = type { i32 (%struct.archive*)*, i32 (%struct.archive*)*, i32 (%struct.archive*, %struct.archive_entry*)*, i32 (%struct.archive*)*, i64 (%struct.archive*, i8*, i64)*, i64 (%struct.archive*, i8*, i64, i64)*, i32 (%struct.archive*, %struct.archive_entry**)*, i32 (%struct.archive*, %struct.archive_entry*)*, i32 (%struct.archive*, i8**, i64*, i64*)*, i32 (%struct.archive*)*, i64 (%struct.archive*, i32)*, i32 (%struct.archive*, i32)*, i8* (%struct.archive*, i32)* }
%struct.archive_string = type { i8*, i64, i64 }
%struct.archive_string_conv = type opaque
%struct.archive_entry = type opaque
%struct.stat = type { i64, i64, i64, i32, i32, i32, i32, i64, i64, i64, i64, %struct.timespec, %struct.timespec, %struct.timespec, [3 x i64] }
%struct.timespec = type { i64, i64 }
%struct.archive_read_disk = type { %struct.archive, %struct.archive_entry*, i8, i8, %struct.tree*, i32 (%struct.tree*, i8*, i32)*, i32 (%struct.tree*)*, i32 (%struct.tree*)*, i32, i8* (i8*, i64)*, void (i8*)*, i8*, i8* (i8*, i64)*, void (i8*)*, i8*, i32 (%struct.archive*, i8*, %struct.archive_entry*)*, i8*, %struct.archive*, void (%struct.archive*, i8*, %struct.archive_entry*)*, i8* }
%struct.tree = type opaque
%struct.fiemap = type { i64, i64, i32, i32, i32, i32, [0 x %struct.fiemap_extent] }
%struct.fiemap_extent = type { i64, i64, i64, [2 x i64], i32, [3 x i32] }

@.str = private unnamed_addr constant [12 x i8] c"Can't fstat\00", align 1
@.str.1 = private unnamed_addr constant [15 x i8] c"Can't lstat %s\00", align 1
@.str.2 = private unnamed_addr constant [14 x i8] c"Can't stat %s\00", align 1
@.str.3 = private unnamed_addr constant [24 x i8] c"Couldn't read link data\00", align 1
@.str.4 = private unnamed_addr constant [16 x i8] c"Can't open `%s'\00", align 1
@.str.5 = private unnamed_addr constant [24 x i8] c"lseek(SEEK_HOLE) failed\00", align 1
@.str.6 = private unnamed_addr constant [24 x i8] c"lseek(SEEK_DATA) failed\00", align 1

; Function Attrs: nounwind uwtable
define i32 @archive_read_disk_entry_from_file(%struct.archive* %_a, %struct.archive_entry* %entry1, i32 %fd, %struct.stat* %st) #0 !dbg !188 {
entry:
  %retval = alloca i32, align 4
  %_a.addr = alloca %struct.archive*, align 8
  %entry.addr = alloca %struct.archive_entry*, align 8
  %fd.addr = alloca i32, align 4
  %st.addr = alloca %struct.stat*, align 8
  %a = alloca %struct.archive_read_disk*, align 8
  %path = alloca i8*, align 8
  %name = alloca i8*, align 8
  %s = alloca %struct.stat, align 8
  %initial_fd = alloca i32, align 4
  %r = alloca i32, align 4
  %r1 = alloca i32, align 4
  %stflags = alloca i32, align 4
  %linkbuffer_len = alloca i64, align 8
  %linkbuffer = alloca i8*, align 8
  %lnklen = alloca i32, align 4
  store %struct.archive* %_a, %struct.archive** %_a.addr, align 8
  call void @llvm.dbg.declare(metadata %struct.archive** %_a.addr, metadata !237, metadata !238), !dbg !239
  store %struct.archive_entry* %entry1, %struct.archive_entry** %entry.addr, align 8
  call void @llvm.dbg.declare(metadata %struct.archive_entry** %entry.addr, metadata !240, metadata !238), !dbg !241
  store i32 %fd, i32* %fd.addr, align 4
  call void @llvm.dbg.declare(metadata i32* %fd.addr, metadata !242, metadata !238), !dbg !243
  store %struct.stat* %st, %struct.stat** %st.addr, align 8
  call void @llvm.dbg.declare(metadata %struct.stat** %st.addr, metadata !244, metadata !238), !dbg !245
  call void @llvm.dbg.declare(metadata %struct.archive_read_disk** %a, metadata !246, metadata !238), !dbg !247
  %0 = load %struct.archive*, %struct.archive** %_a.addr, align 8, !dbg !248
  %1 = bitcast %struct.archive* %0 to %struct.archive_read_disk*, !dbg !249
  store %struct.archive_read_disk* %1, %struct.archive_read_disk** %a, align 8, !dbg !247
  call void @llvm.dbg.declare(metadata i8** %path, metadata !250, metadata !238), !dbg !251
  call void @llvm.dbg.declare(metadata i8** %name, metadata !252, metadata !238), !dbg !253
  call void @llvm.dbg.declare(metadata %struct.stat* %s, metadata !254, metadata !238), !dbg !255
  call void @llvm.dbg.declare(metadata i32* %initial_fd, metadata !256, metadata !238), !dbg !257
  %2 = load i32, i32* %fd.addr, align 4, !dbg !258
  store i32 %2, i32* %initial_fd, align 4, !dbg !257
  call void @llvm.dbg.declare(metadata i32* %r, metadata !259, metadata !238), !dbg !260
  call void @llvm.dbg.declare(metadata i32* %r1, metadata !261, metadata !238), !dbg !262
  %3 = load %struct.archive*, %struct.archive** %_a.addr, align 8, !dbg !263
  call void @archive_clear_error(%struct.archive* %3), !dbg !264
  %4 = load %struct.archive_entry*, %struct.archive_entry** %entry.addr, align 8, !dbg !265
  %call = call i8* @archive_entry_sourcepath(%struct.archive_entry* %4), !dbg !266
  store i8* %call, i8** %path, align 8, !dbg !267
  %5 = load i8*, i8** %path, align 8, !dbg !268
  %cmp = icmp eq i8* %5, null, !dbg !270
  br i1 %cmp, label %if.then, label %if.end, !dbg !271

if.then:                                          ; preds = %entry
  %6 = load %struct.archive_entry*, %struct.archive_entry** %entry.addr, align 8, !dbg !272
  %call2 = call i8* @archive_entry_pathname(%struct.archive_entry* %6), !dbg !273
  store i8* %call2, i8** %path, align 8, !dbg !274
  br label %if.end, !dbg !275

if.end:                                           ; preds = %if.then, %entry
  %7 = load %struct.archive_read_disk*, %struct.archive_read_disk** %a, align 8, !dbg !276
  %tree = getelementptr inbounds %struct.archive_read_disk, %struct.archive_read_disk* %7, i32 0, i32 4, !dbg !278
  %8 = load %struct.tree*, %struct.tree** %tree, align 8, !dbg !278
  %cmp3 = icmp eq %struct.tree* %8, null, !dbg !279
  br i1 %cmp3, label %if.then4, label %if.end31, !dbg !280

if.then4:                                         ; preds = %if.end
  %9 = load %struct.stat*, %struct.stat** %st.addr, align 8, !dbg !281
  %cmp5 = icmp eq %struct.stat* %9, null, !dbg !284
  br i1 %cmp5, label %if.then6, label %if.end30, !dbg !285

if.then6:                                         ; preds = %if.then4
  %10 = load i32, i32* %fd.addr, align 4, !dbg !286
  %cmp7 = icmp sge i32 %10, 0, !dbg !289
  br i1 %cmp7, label %if.then8, label %if.else, !dbg !290

if.then8:                                         ; preds = %if.then6
  %11 = load i32, i32* %fd.addr, align 4, !dbg !291
  %call9 = call i32 @fstat(i32 %11, %struct.stat* %s) #6, !dbg !294
  %cmp10 = icmp ne i32 %call9, 0, !dbg !295
  br i1 %cmp10, label %if.then11, label %if.end13, !dbg !296

if.then11:                                        ; preds = %if.then8
  %12 = load %struct.archive_read_disk*, %struct.archive_read_disk** %a, align 8, !dbg !297
  %archive = getelementptr inbounds %struct.archive_read_disk, %struct.archive_read_disk* %12, i32 0, i32 0, !dbg !299
  %call12 = call i32* @__errno_location() #1, !dbg !300
  %13 = load i32, i32* %call12, align 4, !dbg !300
  call void (%struct.archive*, i32, i8*, ...) @archive_set_error(%struct.archive* %archive, i32 %13, i8* getelementptr inbounds ([12 x i8], [12 x i8]* @.str, i32 0, i32 0)), !dbg !301
  store i32 -25, i32* %retval, align 4, !dbg !303
  br label %return, !dbg !303

if.end13:                                         ; preds = %if.then8
  br label %if.end29, !dbg !304

if.else:                                          ; preds = %if.then6
  %14 = load %struct.archive_read_disk*, %struct.archive_read_disk** %a, align 8, !dbg !305
  %follow_symlinks = getelementptr inbounds %struct.archive_read_disk, %struct.archive_read_disk* %14, i32 0, i32 3, !dbg !307
  %15 = load i8, i8* %follow_symlinks, align 1, !dbg !307
  %tobool = icmp ne i8 %15, 0, !dbg !305
  br i1 %tobool, label %if.else21, label %if.then14, !dbg !308

if.then14:                                        ; preds = %if.else
  %16 = load i8*, i8** %path, align 8, !dbg !309
  %call15 = call i32 @lstat(i8* %16, %struct.stat* %s) #6, !dbg !312
  %cmp16 = icmp ne i32 %call15, 0, !dbg !313
  br i1 %cmp16, label %if.then17, label %if.end20, !dbg !314

if.then17:                                        ; preds = %if.then14
  %17 = load %struct.archive_read_disk*, %struct.archive_read_disk** %a, align 8, !dbg !315
  %archive18 = getelementptr inbounds %struct.archive_read_disk, %struct.archive_read_disk* %17, i32 0, i32 0, !dbg !317
  %call19 = call i32* @__errno_location() #1, !dbg !318
  %18 = load i32, i32* %call19, align 4, !dbg !318
  %19 = load i8*, i8** %path, align 8, !dbg !319
  call void (%struct.archive*, i32, i8*, ...) @archive_set_error(%struct.archive* %archive18, i32 %18, i8* getelementptr inbounds ([15 x i8], [15 x i8]* @.str.1, i32 0, i32 0), i8* %19), !dbg !320
  store i32 -25, i32* %retval, align 4, !dbg !322
  br label %return, !dbg !322

if.end20:                                         ; preds = %if.then14
  br label %if.end28, !dbg !323

if.else21:                                        ; preds = %if.else
  %20 = load i8*, i8** %path, align 8, !dbg !324
  %call22 = call i32 @stat(i8* %20, %struct.stat* %s) #6, !dbg !326
  %cmp23 = icmp ne i32 %call22, 0, !dbg !327
  br i1 %cmp23, label %if.then24, label %if.end27, !dbg !328

if.then24:                                        ; preds = %if.else21
  %21 = load %struct.archive_read_disk*, %struct.archive_read_disk** %a, align 8, !dbg !329
  %archive25 = getelementptr inbounds %struct.archive_read_disk, %struct.archive_read_disk* %21, i32 0, i32 0, !dbg !331
  %call26 = call i32* @__errno_location() #1, !dbg !332
  %22 = load i32, i32* %call26, align 4, !dbg !332
  %23 = load i8*, i8** %path, align 8, !dbg !333
  call void (%struct.archive*, i32, i8*, ...) @archive_set_error(%struct.archive* %archive25, i32 %22, i8* getelementptr inbounds ([14 x i8], [14 x i8]* @.str.2, i32 0, i32 0), i8* %23), !dbg !334
  store i32 -25, i32* %retval, align 4, !dbg !336
  br label %return, !dbg !336

if.end27:                                         ; preds = %if.else21
  br label %if.end28

if.end28:                                         ; preds = %if.end27, %if.end20
  br label %if.end29

if.end29:                                         ; preds = %if.end28, %if.end13
  store %struct.stat* %s, %struct.stat** %st.addr, align 8, !dbg !337
  br label %if.end30, !dbg !338

if.end30:                                         ; preds = %if.end29, %if.then4
  %24 = load %struct.archive_entry*, %struct.archive_entry** %entry.addr, align 8, !dbg !339
  %25 = load %struct.stat*, %struct.stat** %st.addr, align 8, !dbg !340
  call void @archive_entry_copy_stat(%struct.archive_entry* %24, %struct.stat* %25), !dbg !341
  br label %if.end31, !dbg !342

if.end31:                                         ; preds = %if.end30, %if.end
  %26 = load %struct.archive*, %struct.archive** %_a.addr, align 8, !dbg !343
  %27 = load %struct.archive_entry*, %struct.archive_entry** %entry.addr, align 8, !dbg !344
  %call32 = call i64 @archive_entry_uid(%struct.archive_entry* %27), !dbg !345
  %call33 = call i8* @archive_read_disk_uname(%struct.archive* %26, i64 %call32), !dbg !346
  store i8* %call33, i8** %name, align 8, !dbg !348
  %28 = load i8*, i8** %name, align 8, !dbg !349
  %cmp34 = icmp ne i8* %28, null, !dbg !351
  br i1 %cmp34, label %if.then35, label %if.end36, !dbg !352

if.then35:                                        ; preds = %if.end31
  %29 = load %struct.archive_entry*, %struct.archive_entry** %entry.addr, align 8, !dbg !353
  %30 = load i8*, i8** %name, align 8, !dbg !354
  call void @archive_entry_copy_uname(%struct.archive_entry* %29, i8* %30), !dbg !355
  br label %if.end36, !dbg !355

if.end36:                                         ; preds = %if.then35, %if.end31
  %31 = load %struct.archive*, %struct.archive** %_a.addr, align 8, !dbg !356
  %32 = load %struct.archive_entry*, %struct.archive_entry** %entry.addr, align 8, !dbg !357
  %call37 = call i64 @archive_entry_gid(%struct.archive_entry* %32), !dbg !358
  %call38 = call i8* @archive_read_disk_gname(%struct.archive* %31, i64 %call37), !dbg !359
  store i8* %call38, i8** %name, align 8, !dbg !360
  %33 = load i8*, i8** %name, align 8, !dbg !361
  %cmp39 = icmp ne i8* %33, null, !dbg !363
  br i1 %cmp39, label %if.then40, label %if.end41, !dbg !364

if.then40:                                        ; preds = %if.end36
  %34 = load %struct.archive_entry*, %struct.archive_entry** %entry.addr, align 8, !dbg !365
  %35 = load i8*, i8** %name, align 8, !dbg !366
  call void @archive_entry_copy_gname(%struct.archive_entry* %34, i8* %35), !dbg !367
  br label %if.end41, !dbg !367

if.end41:                                         ; preds = %if.then40, %if.end36
  %36 = load %struct.archive_read_disk*, %struct.archive_read_disk** %a, align 8, !dbg !368
  %flags = getelementptr inbounds %struct.archive_read_disk, %struct.archive_read_disk* %36, i32 0, i32 8, !dbg !370
  %37 = load i32, i32* %flags, align 8, !dbg !370
  %and = and i32 %37, 64, !dbg !371
  %cmp42 = icmp eq i32 %and, 0, !dbg !372
  br i1 %cmp42, label %land.lhs.true, label %if.end69, !dbg !373

land.lhs.true:                                    ; preds = %if.end41
  %38 = load %struct.stat*, %struct.stat** %st.addr, align 8, !dbg !374
  %st_mode = getelementptr inbounds %struct.stat, %struct.stat* %38, i32 0, i32 3, !dbg !374
  %39 = load i32, i32* %st_mode, align 8, !dbg !374
  %and43 = and i32 %39, 61440, !dbg !374
  %cmp44 = icmp eq i32 %and43, 32768, !dbg !374
  br i1 %cmp44, label %if.then48, label %lor.lhs.false, !dbg !375

lor.lhs.false:                                    ; preds = %land.lhs.true
  %40 = load %struct.stat*, %struct.stat** %st.addr, align 8, !dbg !376
  %st_mode45 = getelementptr inbounds %struct.stat, %struct.stat* %40, i32 0, i32 3, !dbg !376
  %41 = load i32, i32* %st_mode45, align 8, !dbg !376
  %and46 = and i32 %41, 61440, !dbg !376
  %cmp47 = icmp eq i32 %and46, 16384, !dbg !376
  br i1 %cmp47, label %if.then48, label %if.end69, !dbg !378

if.then48:                                        ; preds = %lor.lhs.false, %land.lhs.true
  %42 = load i32, i32* %fd.addr, align 4, !dbg !379
  %cmp49 = icmp slt i32 %42, 0, !dbg !382
  br i1 %cmp49, label %if.then50, label %if.end59, !dbg !383

if.then50:                                        ; preds = %if.then48
  %43 = load %struct.archive_read_disk*, %struct.archive_read_disk** %a, align 8, !dbg !384
  %tree51 = getelementptr inbounds %struct.archive_read_disk, %struct.archive_read_disk* %43, i32 0, i32 4, !dbg !387
  %44 = load %struct.tree*, %struct.tree** %tree51, align 8, !dbg !387
  %cmp52 = icmp ne %struct.tree* %44, null, !dbg !388
  br i1 %cmp52, label %if.then53, label %if.else56, !dbg !389

if.then53:                                        ; preds = %if.then50
  %45 = load %struct.archive_read_disk*, %struct.archive_read_disk** %a, align 8, !dbg !390
  %open_on_current_dir = getelementptr inbounds %struct.archive_read_disk, %struct.archive_read_disk* %45, i32 0, i32 5, !dbg !391
  %46 = load i32 (%struct.tree*, i8*, i32)*, i32 (%struct.tree*, i8*, i32)** %open_on_current_dir, align 8, !dbg !391
  %47 = load %struct.archive_read_disk*, %struct.archive_read_disk** %a, align 8, !dbg !392
  %tree54 = getelementptr inbounds %struct.archive_read_disk, %struct.archive_read_disk* %47, i32 0, i32 4, !dbg !393
  %48 = load %struct.tree*, %struct.tree** %tree54, align 8, !dbg !393
  %49 = load i8*, i8** %path, align 8, !dbg !394
  %call55 = call i32 %46(%struct.tree* %48, i8* %49, i32 526336), !dbg !390
  store i32 %call55, i32* %fd.addr, align 4, !dbg !395
  br label %if.end58, !dbg !396

if.else56:                                        ; preds = %if.then50
  %50 = load i8*, i8** %path, align 8, !dbg !397
  %call57 = call i32 (i8*, i32, ...) @open(i8* %50, i32 526336), !dbg !398
  store i32 %call57, i32* %fd.addr, align 4, !dbg !399
  br label %if.end58

if.end58:                                         ; preds = %if.else56, %if.then53
  %51 = load i32, i32* %fd.addr, align 4, !dbg !400
  call void @__archive_ensure_cloexec_flag(i32 %51), !dbg !401
  br label %if.end59, !dbg !402

if.end59:                                         ; preds = %if.end58, %if.then48
  %52 = load i32, i32* %fd.addr, align 4, !dbg !403
  %cmp60 = icmp sge i32 %52, 0, !dbg !405
  br i1 %cmp60, label %if.then61, label %if.end68, !dbg !406

if.then61:                                        ; preds = %if.end59
  call void @llvm.dbg.declare(metadata i32* %stflags, metadata !407, metadata !238), !dbg !409
  %53 = load i32, i32* %fd.addr, align 4, !dbg !410
  %call62 = call i32 (i32, i64, ...) @ioctl(i32 %53, i64 2148034049, i32* %stflags) #6, !dbg !411
  store i32 %call62, i32* %r, align 4, !dbg !412
  %54 = load i32, i32* %r, align 4, !dbg !413
  %cmp63 = icmp eq i32 %54, 0, !dbg !415
  br i1 %cmp63, label %land.lhs.true64, label %if.end67, !dbg !416

land.lhs.true64:                                  ; preds = %if.then61
  %55 = load i32, i32* %stflags, align 4, !dbg !417
  %cmp65 = icmp ne i32 %55, 0, !dbg !419
  br i1 %cmp65, label %if.then66, label %if.end67, !dbg !420

if.then66:                                        ; preds = %land.lhs.true64
  %56 = load %struct.archive_entry*, %struct.archive_entry** %entry.addr, align 8, !dbg !421
  %57 = load i32, i32* %stflags, align 4, !dbg !422
  %conv = sext i32 %57 to i64, !dbg !422
  call void @archive_entry_set_fflags(%struct.archive_entry* %56, i64 %conv, i64 0), !dbg !423
  br label %if.end67, !dbg !423

if.end67:                                         ; preds = %if.then66, %land.lhs.true64, %if.then61
  br label %if.end68, !dbg !424

if.end68:                                         ; preds = %if.end67, %if.end59
  br label %if.end69, !dbg !425

if.end69:                                         ; preds = %if.end68, %lor.lhs.false, %if.end41
  %58 = load %struct.stat*, %struct.stat** %st.addr, align 8, !dbg !426
  %st_mode70 = getelementptr inbounds %struct.stat, %struct.stat* %58, i32 0, i32 3, !dbg !426
  %59 = load i32, i32* %st_mode70, align 8, !dbg !426
  %and71 = and i32 %59, 61440, !dbg !426
  %cmp72 = icmp eq i32 %and71, 40960, !dbg !426
  br i1 %cmp72, label %if.then74, label %if.end99, !dbg !428

if.then74:                                        ; preds = %if.end69
  call void @llvm.dbg.declare(metadata i64* %linkbuffer_len, metadata !429, metadata !238), !dbg !431
  %60 = load %struct.stat*, %struct.stat** %st.addr, align 8, !dbg !432
  %st_size = getelementptr inbounds %struct.stat, %struct.stat* %60, i32 0, i32 8, !dbg !433
  %61 = load i64, i64* %st_size, align 8, !dbg !433
  %add = add nsw i64 %61, 1, !dbg !434
  store i64 %add, i64* %linkbuffer_len, align 8, !dbg !431
  call void @llvm.dbg.declare(metadata i8** %linkbuffer, metadata !435, metadata !238), !dbg !436
  call void @llvm.dbg.declare(metadata i32* %lnklen, metadata !437, metadata !238), !dbg !438
  %62 = load i64, i64* %linkbuffer_len, align 8, !dbg !439
  %call75 = call noalias i8* @malloc(i64 %62) #6, !dbg !440
  store i8* %call75, i8** %linkbuffer, align 8, !dbg !441
  %63 = load i8*, i8** %linkbuffer, align 8, !dbg !442
  %cmp76 = icmp eq i8* %63, null, !dbg !444
  br i1 %cmp76, label %if.then78, label %if.end80, !dbg !445

if.then78:                                        ; preds = %if.then74
  %64 = load %struct.archive_read_disk*, %struct.archive_read_disk** %a, align 8, !dbg !446
  %archive79 = getelementptr inbounds %struct.archive_read_disk, %struct.archive_read_disk* %64, i32 0, i32 0, !dbg !448
  call void (%struct.archive*, i32, i8*, ...) @archive_set_error(%struct.archive* %archive79, i32 12, i8* getelementptr inbounds ([24 x i8], [24 x i8]* @.str.3, i32 0, i32 0)), !dbg !449
  store i32 -25, i32* %retval, align 4, !dbg !450
  br label %return, !dbg !450

if.end80:                                         ; preds = %if.then74
  %65 = load %struct.archive_read_disk*, %struct.archive_read_disk** %a, align 8, !dbg !451
  %tree81 = getelementptr inbounds %struct.archive_read_disk, %struct.archive_read_disk* %65, i32 0, i32 4, !dbg !453
  %66 = load %struct.tree*, %struct.tree** %tree81, align 8, !dbg !453
  %cmp82 = icmp ne %struct.tree* %66, null, !dbg !454
  br i1 %cmp82, label %if.then84, label %if.else89, !dbg !455

if.then84:                                        ; preds = %if.end80
  %67 = load %struct.archive_read_disk*, %struct.archive_read_disk** %a, align 8, !dbg !456
  %tree_current_dir_fd = getelementptr inbounds %struct.archive_read_disk, %struct.archive_read_disk* %67, i32 0, i32 6, !dbg !458
  %68 = load i32 (%struct.tree*)*, i32 (%struct.tree*)** %tree_current_dir_fd, align 8, !dbg !458
  %69 = load %struct.archive_read_disk*, %struct.archive_read_disk** %a, align 8, !dbg !459
  %tree85 = getelementptr inbounds %struct.archive_read_disk, %struct.archive_read_disk* %69, i32 0, i32 4, !dbg !460
  %70 = load %struct.tree*, %struct.tree** %tree85, align 8, !dbg !460
  %call86 = call i32 %68(%struct.tree* %70), !dbg !456
  %71 = load i8*, i8** %path, align 8, !dbg !461
  %72 = load i8*, i8** %linkbuffer, align 8, !dbg !462
  %73 = load i64, i64* %linkbuffer_len, align 8, !dbg !463
  %call87 = call i64 @readlinkat(i32 %call86, i8* %71, i8* %72, i64 %73) #6, !dbg !464
  %conv88 = trunc i64 %call87 to i32, !dbg !466
  store i32 %conv88, i32* %lnklen, align 4, !dbg !467
  br label %if.end92, !dbg !468

if.else89:                                        ; preds = %if.end80
  %74 = load i8*, i8** %path, align 8, !dbg !469
  %75 = load i8*, i8** %linkbuffer, align 8, !dbg !470
  %76 = load i64, i64* %linkbuffer_len, align 8, !dbg !471
  %call90 = call i64 @readlink(i8* %74, i8* %75, i64 %76) #6, !dbg !472
  %conv91 = trunc i64 %call90 to i32, !dbg !472
  store i32 %conv91, i32* %lnklen, align 4, !dbg !473
  br label %if.end92

if.end92:                                         ; preds = %if.else89, %if.then84
  %77 = load i32, i32* %lnklen, align 4, !dbg !474
  %cmp93 = icmp slt i32 %77, 0, !dbg !476
  br i1 %cmp93, label %if.then95, label %if.end98, !dbg !477

if.then95:                                        ; preds = %if.end92
  %78 = load %struct.archive_read_disk*, %struct.archive_read_disk** %a, align 8, !dbg !478
  %archive96 = getelementptr inbounds %struct.archive_read_disk, %struct.archive_read_disk* %78, i32 0, i32 0, !dbg !480
  %call97 = call i32* @__errno_location() #1, !dbg !481
  %79 = load i32, i32* %call97, align 4, !dbg !481
  call void (%struct.archive*, i32, i8*, ...) @archive_set_error(%struct.archive* %archive96, i32 %79, i8* getelementptr inbounds ([24 x i8], [24 x i8]* @.str.3, i32 0, i32 0)), !dbg !482
  %80 = load i8*, i8** %linkbuffer, align 8, !dbg !484
  call void @free(i8* %80) #6, !dbg !485
  store i32 -25, i32* %retval, align 4, !dbg !486
  br label %return, !dbg !486

if.end98:                                         ; preds = %if.end92
  %81 = load i32, i32* %lnklen, align 4, !dbg !487
  %idxprom = sext i32 %81 to i64, !dbg !488
  %82 = load i8*, i8** %linkbuffer, align 8, !dbg !488
  %arrayidx = getelementptr inbounds i8, i8* %82, i64 %idxprom, !dbg !488
  store i8 0, i8* %arrayidx, align 1, !dbg !489
  %83 = load %struct.archive_entry*, %struct.archive_entry** %entry.addr, align 8, !dbg !490
  %84 = load i8*, i8** %linkbuffer, align 8, !dbg !491
  call void @archive_entry_set_symlink(%struct.archive_entry* %83, i8* %84), !dbg !492
  %85 = load i8*, i8** %linkbuffer, align 8, !dbg !493
  call void @free(i8* %85) #6, !dbg !494
  br label %if.end99, !dbg !495

if.end99:                                         ; preds = %if.end98, %if.end69
  store i32 0, i32* %r, align 4, !dbg !496
  %86 = load %struct.archive_read_disk*, %struct.archive_read_disk** %a, align 8, !dbg !497
  %flags100 = getelementptr inbounds %struct.archive_read_disk, %struct.archive_read_disk* %86, i32 0, i32 8, !dbg !499
  %87 = load i32, i32* %flags100, align 8, !dbg !499
  %and101 = and i32 %87, 32, !dbg !500
  %cmp102 = icmp eq i32 %and101, 0, !dbg !501
  br i1 %cmp102, label %if.then104, label %if.end106, !dbg !502

if.then104:                                       ; preds = %if.end99
  %88 = load %struct.archive_read_disk*, %struct.archive_read_disk** %a, align 8, !dbg !503
  %89 = load %struct.archive_entry*, %struct.archive_entry** %entry.addr, align 8, !dbg !504
  %call105 = call i32 @setup_acls(%struct.archive_read_disk* %88, %struct.archive_entry* %89, i32* %fd.addr), !dbg !505
  store i32 %call105, i32* %r, align 4, !dbg !506
  br label %if.end106, !dbg !507

if.end106:                                        ; preds = %if.then104, %if.end99
  %90 = load %struct.archive_read_disk*, %struct.archive_read_disk** %a, align 8, !dbg !508
  %flags107 = getelementptr inbounds %struct.archive_read_disk, %struct.archive_read_disk* %90, i32 0, i32 8, !dbg !510
  %91 = load i32, i32* %flags107, align 8, !dbg !510
  %and108 = and i32 %91, 16, !dbg !511
  %cmp109 = icmp eq i32 %and108, 0, !dbg !512
  br i1 %cmp109, label %if.then111, label %if.end117, !dbg !513

if.then111:                                       ; preds = %if.end106
  %92 = load %struct.archive_read_disk*, %struct.archive_read_disk** %a, align 8, !dbg !514
  %93 = load %struct.archive_entry*, %struct.archive_entry** %entry.addr, align 8, !dbg !516
  %call112 = call i32 @setup_xattrs(%struct.archive_read_disk* %92, %struct.archive_entry* %93, i32* %fd.addr), !dbg !517
  store i32 %call112, i32* %r1, align 4, !dbg !518
  %94 = load i32, i32* %r1, align 4, !dbg !519
  %95 = load i32, i32* %r, align 4, !dbg !521
  %cmp113 = icmp slt i32 %94, %95, !dbg !522
  br i1 %cmp113, label %if.then115, label %if.end116, !dbg !523

if.then115:                                       ; preds = %if.then111
  %96 = load i32, i32* %r1, align 4, !dbg !524
  store i32 %96, i32* %r, align 4, !dbg !525
  br label %if.end116, !dbg !526

if.end116:                                        ; preds = %if.then115, %if.then111
  br label %if.end117, !dbg !527

if.end117:                                        ; preds = %if.end116, %if.end106
  %97 = load %struct.archive_read_disk*, %struct.archive_read_disk** %a, align 8, !dbg !528
  %flags118 = getelementptr inbounds %struct.archive_read_disk, %struct.archive_read_disk* %97, i32 0, i32 8, !dbg !530
  %98 = load i32, i32* %flags118, align 8, !dbg !530
  %and119 = and i32 %98, 4, !dbg !531
  %tobool120 = icmp ne i32 %and119, 0, !dbg !531
  br i1 %tobool120, label %if.then121, label %if.end127, !dbg !532

if.then121:                                       ; preds = %if.end117
  %99 = load %struct.archive_read_disk*, %struct.archive_read_disk** %a, align 8, !dbg !533
  %100 = load %struct.archive_entry*, %struct.archive_entry** %entry.addr, align 8, !dbg !535
  %call122 = call i32 @setup_mac_metadata(%struct.archive_read_disk* %99, %struct.archive_entry* %100, i32* %fd.addr), !dbg !536
  store i32 %call122, i32* %r1, align 4, !dbg !537
  %101 = load i32, i32* %r1, align 4, !dbg !538
  %102 = load i32, i32* %r, align 4, !dbg !540
  %cmp123 = icmp slt i32 %101, %102, !dbg !541
  br i1 %cmp123, label %if.then125, label %if.end126, !dbg !542

if.then125:                                       ; preds = %if.then121
  %103 = load i32, i32* %r1, align 4, !dbg !543
  store i32 %103, i32* %r, align 4, !dbg !544
  br label %if.end126, !dbg !545

if.end126:                                        ; preds = %if.then125, %if.then121
  br label %if.end127, !dbg !546

if.end127:                                        ; preds = %if.end126, %if.end117
  %104 = load %struct.archive_read_disk*, %struct.archive_read_disk** %a, align 8, !dbg !547
  %105 = load %struct.archive_entry*, %struct.archive_entry** %entry.addr, align 8, !dbg !548
  %call128 = call i32 @setup_sparse(%struct.archive_read_disk* %104, %struct.archive_entry* %105, i32* %fd.addr), !dbg !549
  store i32 %call128, i32* %r1, align 4, !dbg !550
  %106 = load i32, i32* %r1, align 4, !dbg !551
  %107 = load i32, i32* %r, align 4, !dbg !553
  %cmp129 = icmp slt i32 %106, %107, !dbg !554
  br i1 %cmp129, label %if.then131, label %if.end132, !dbg !555

if.then131:                                       ; preds = %if.end127
  %108 = load i32, i32* %r1, align 4, !dbg !556
  store i32 %108, i32* %r, align 4, !dbg !557
  br label %if.end132, !dbg !558

if.end132:                                        ; preds = %if.then131, %if.end127
  %109 = load i32, i32* %initial_fd, align 4, !dbg !559
  %110 = load i32, i32* %fd.addr, align 4, !dbg !561
  %cmp133 = icmp ne i32 %109, %110, !dbg !562
  br i1 %cmp133, label %if.then135, label %if.end137, !dbg !563

if.then135:                                       ; preds = %if.end132
  %111 = load i32, i32* %fd.addr, align 4, !dbg !564
  %call136 = call i32 @close(i32 %111), !dbg !565
  br label %if.end137, !dbg !565

if.end137:                                        ; preds = %if.then135, %if.end132
  %112 = load i32, i32* %r, align 4, !dbg !566
  store i32 %112, i32* %retval, align 4, !dbg !567
  br label %return, !dbg !567

return:                                           ; preds = %if.end137, %if.then95, %if.then78, %if.then24, %if.then17, %if.then11
  %113 = load i32, i32* %retval, align 4, !dbg !568
  ret i32 %113, !dbg !568
}

; Function Attrs: nounwind readnone
declare void @llvm.dbg.declare(metadata, metadata, metadata) #1

declare void @archive_clear_error(%struct.archive*) #2

declare i8* @archive_entry_sourcepath(%struct.archive_entry*) #2

declare i8* @archive_entry_pathname(%struct.archive_entry*) #2

; Function Attrs: nounwind
declare i32 @fstat(i32, %struct.stat*) #3

declare void @archive_set_error(%struct.archive*, i32, i8*, ...) #2

; Function Attrs: nounwind readnone
declare i32* @__errno_location() #4

; Function Attrs: nounwind
declare i32 @lstat(i8*, %struct.stat*) #3

; Function Attrs: nounwind
declare i32 @stat(i8*, %struct.stat*) #3

declare void @archive_entry_copy_stat(%struct.archive_entry*, %struct.stat*) #2

declare i8* @archive_read_disk_uname(%struct.archive*, i64) #2

declare i64 @archive_entry_uid(%struct.archive_entry*) #2

declare void @archive_entry_copy_uname(%struct.archive_entry*, i8*) #2

declare i8* @archive_read_disk_gname(%struct.archive*, i64) #2

declare i64 @archive_entry_gid(%struct.archive_entry*) #2

declare void @archive_entry_copy_gname(%struct.archive_entry*, i8*) #2

declare i32 @open(i8*, i32, ...) #2

declare void @__archive_ensure_cloexec_flag(i32) #2

; Function Attrs: nounwind
declare i32 @ioctl(i32, i64, ...) #3

declare void @archive_entry_set_fflags(%struct.archive_entry*, i64, i64) #2

; Function Attrs: nounwind
declare noalias i8* @malloc(i64) #3

; Function Attrs: nounwind
declare i64 @readlinkat(i32, i8*, i8*, i64) #3

; Function Attrs: nounwind
declare i64 @readlink(i8*, i8*, i64) #3

; Function Attrs: nounwind
declare void @free(i8*) #3

declare void @archive_entry_set_symlink(%struct.archive_entry*, i8*) #2

; Function Attrs: nounwind uwtable
define internal i32 @setup_acls(%struct.archive_read_disk* %a, %struct.archive_entry* %entry1, i32* %fd) #0 !dbg !230 {
entry:
  %a.addr = alloca %struct.archive_read_disk*, align 8
  %entry.addr = alloca %struct.archive_entry*, align 8
  %fd.addr = alloca i32*, align 8
  store %struct.archive_read_disk* %a, %struct.archive_read_disk** %a.addr, align 8
  call void @llvm.dbg.declare(metadata %struct.archive_read_disk** %a.addr, metadata !569, metadata !238), !dbg !570
  store %struct.archive_entry* %entry1, %struct.archive_entry** %entry.addr, align 8
  call void @llvm.dbg.declare(metadata %struct.archive_entry** %entry.addr, metadata !571, metadata !238), !dbg !572
  store i32* %fd, i32** %fd.addr, align 8
  call void @llvm.dbg.declare(metadata i32** %fd.addr, metadata !573, metadata !238), !dbg !574
  %0 = load %struct.archive_read_disk*, %struct.archive_read_disk** %a.addr, align 8, !dbg !575
  %1 = load %struct.archive_entry*, %struct.archive_entry** %entry.addr, align 8, !dbg !576
  %2 = load i32*, i32** %fd.addr, align 8, !dbg !577
  ret i32 0, !dbg !578
}

; Function Attrs: nounwind uwtable
define internal i32 @setup_xattrs(%struct.archive_read_disk* %a, %struct.archive_entry* %entry1, i32* %fd) #0 !dbg !231 {
entry:
  %a.addr = alloca %struct.archive_read_disk*, align 8
  %entry.addr = alloca %struct.archive_entry*, align 8
  %fd.addr = alloca i32*, align 8
  store %struct.archive_read_disk* %a, %struct.archive_read_disk** %a.addr, align 8
  call void @llvm.dbg.declare(metadata %struct.archive_read_disk** %a.addr, metadata !579, metadata !238), !dbg !580
  store %struct.archive_entry* %entry1, %struct.archive_entry** %entry.addr, align 8
  call void @llvm.dbg.declare(metadata %struct.archive_entry** %entry.addr, metadata !581, metadata !238), !dbg !582
  store i32* %fd, i32** %fd.addr, align 8
  call void @llvm.dbg.declare(metadata i32** %fd.addr, metadata !583, metadata !238), !dbg !584
  %0 = load %struct.archive_read_disk*, %struct.archive_read_disk** %a.addr, align 8, !dbg !585
  %1 = load %struct.archive_entry*, %struct.archive_entry** %entry.addr, align 8, !dbg !586
  %2 = load i32*, i32** %fd.addr, align 8, !dbg !587
  ret i32 0, !dbg !588
}

; Function Attrs: nounwind uwtable
define internal i32 @setup_mac_metadata(%struct.archive_read_disk* %a, %struct.archive_entry* %entry1, i32* %fd) #0 !dbg !226 {
entry:
  %a.addr = alloca %struct.archive_read_disk*, align 8
  %entry.addr = alloca %struct.archive_entry*, align 8
  %fd.addr = alloca i32*, align 8
  store %struct.archive_read_disk* %a, %struct.archive_read_disk** %a.addr, align 8
  call void @llvm.dbg.declare(metadata %struct.archive_read_disk** %a.addr, metadata !589, metadata !238), !dbg !590
  store %struct.archive_entry* %entry1, %struct.archive_entry** %entry.addr, align 8
  call void @llvm.dbg.declare(metadata %struct.archive_entry** %entry.addr, metadata !591, metadata !238), !dbg !592
  store i32* %fd, i32** %fd.addr, align 8
  call void @llvm.dbg.declare(metadata i32** %fd.addr, metadata !593, metadata !238), !dbg !594
  %0 = load %struct.archive_read_disk*, %struct.archive_read_disk** %a.addr, align 8, !dbg !595
  %1 = load %struct.archive_entry*, %struct.archive_entry** %entry.addr, align 8, !dbg !596
  %2 = load i32*, i32** %fd.addr, align 8, !dbg !597
  ret i32 0, !dbg !598
}

; Function Attrs: nounwind uwtable
define internal i32 @setup_sparse(%struct.archive_read_disk* %a, %struct.archive_entry* %entry1, i32* %fd) #0 !dbg !232 {
entry:
  %retval = alloca i32, align 4
  %a.addr = alloca %struct.archive_read_disk*, align 8
  %entry.addr = alloca %struct.archive_entry*, align 8
  %fd.addr = alloca i32*, align 8
  %size = alloca i64, align 8
  %initial_off = alloca i64, align 8
  %off_s = alloca i64, align 8
  %off_e = alloca i64, align 8
  %exit_sts = alloca i32, align 4
  %check_fully_sparse = alloca i32, align 4
  %path = alloca i8*, align 8
  %path29 = alloca i8*, align 8
  store %struct.archive_read_disk* %a, %struct.archive_read_disk** %a.addr, align 8
  call void @llvm.dbg.declare(metadata %struct.archive_read_disk** %a.addr, metadata !599, metadata !238), !dbg !600
  store %struct.archive_entry* %entry1, %struct.archive_entry** %entry.addr, align 8
  call void @llvm.dbg.declare(metadata %struct.archive_entry** %entry.addr, metadata !601, metadata !238), !dbg !602
  store i32* %fd, i32** %fd.addr, align 8
  call void @llvm.dbg.declare(metadata i32** %fd.addr, metadata !603, metadata !238), !dbg !604
  call void @llvm.dbg.declare(metadata i64* %size, metadata !605, metadata !238), !dbg !606
  call void @llvm.dbg.declare(metadata i64* %initial_off, metadata !607, metadata !238), !dbg !608
  call void @llvm.dbg.declare(metadata i64* %off_s, metadata !609, metadata !238), !dbg !610
  call void @llvm.dbg.declare(metadata i64* %off_e, metadata !611, metadata !238), !dbg !612
  call void @llvm.dbg.declare(metadata i32* %exit_sts, metadata !613, metadata !238), !dbg !614
  store i32 0, i32* %exit_sts, align 4, !dbg !614
  call void @llvm.dbg.declare(metadata i32* %check_fully_sparse, metadata !615, metadata !238), !dbg !616
  store i32 0, i32* %check_fully_sparse, align 4, !dbg !616
  %0 = load %struct.archive_entry*, %struct.archive_entry** %entry.addr, align 8, !dbg !617
  %call = call i32 @archive_entry_filetype(%struct.archive_entry* %0), !dbg !619
  %cmp = icmp ne i32 %call, 32768, !dbg !620
  br i1 %cmp, label %if.then, label %lor.lhs.false, !dbg !621

lor.lhs.false:                                    ; preds = %entry
  %1 = load %struct.archive_entry*, %struct.archive_entry** %entry.addr, align 8, !dbg !622
  %call2 = call i64 @archive_entry_size(%struct.archive_entry* %1), !dbg !624
  %cmp3 = icmp sle i64 %call2, 0, !dbg !625
  br i1 %cmp3, label %if.then, label %lor.lhs.false4, !dbg !626

lor.lhs.false4:                                   ; preds = %lor.lhs.false
  %2 = load %struct.archive_entry*, %struct.archive_entry** %entry.addr, align 8, !dbg !627
  %call5 = call i8* @archive_entry_hardlink(%struct.archive_entry* %2), !dbg !628
  %cmp6 = icmp ne i8* %call5, null, !dbg !629
  br i1 %cmp6, label %if.then, label %if.end, !dbg !630

if.then:                                          ; preds = %lor.lhs.false4, %lor.lhs.false, %entry
  store i32 0, i32* %retval, align 4, !dbg !632
  br label %return, !dbg !632

if.end:                                           ; preds = %lor.lhs.false4
  %3 = load i32*, i32** %fd.addr, align 8, !dbg !633
  %4 = load i32, i32* %3, align 4, !dbg !635
  %cmp7 = icmp slt i32 %4, 0, !dbg !636
  br i1 %cmp7, label %land.lhs.true, label %if.end21, !dbg !637

land.lhs.true:                                    ; preds = %if.end
  %5 = load %struct.archive_read_disk*, %struct.archive_read_disk** %a.addr, align 8, !dbg !638
  %tree = getelementptr inbounds %struct.archive_read_disk, %struct.archive_read_disk* %5, i32 0, i32 4, !dbg !640
  %6 = load %struct.tree*, %struct.tree** %tree, align 8, !dbg !640
  %cmp8 = icmp ne %struct.tree* %6, null, !dbg !641
  br i1 %cmp8, label %if.then9, label %if.end21, !dbg !642

if.then9:                                         ; preds = %land.lhs.true
  call void @llvm.dbg.declare(metadata i8** %path, metadata !643, metadata !238), !dbg !645
  %7 = load %struct.archive_entry*, %struct.archive_entry** %entry.addr, align 8, !dbg !646
  %call10 = call i8* @archive_entry_sourcepath(%struct.archive_entry* %7), !dbg !647
  store i8* %call10, i8** %path, align 8, !dbg !648
  %8 = load i8*, i8** %path, align 8, !dbg !649
  %cmp11 = icmp eq i8* %8, null, !dbg !651
  br i1 %cmp11, label %if.then12, label %if.end14, !dbg !652

if.then12:                                        ; preds = %if.then9
  %9 = load %struct.archive_entry*, %struct.archive_entry** %entry.addr, align 8, !dbg !653
  %call13 = call i8* @archive_entry_pathname(%struct.archive_entry* %9), !dbg !654
  store i8* %call13, i8** %path, align 8, !dbg !655
  br label %if.end14, !dbg !656

if.end14:                                         ; preds = %if.then12, %if.then9
  %10 = load %struct.archive_read_disk*, %struct.archive_read_disk** %a.addr, align 8, !dbg !657
  %open_on_current_dir = getelementptr inbounds %struct.archive_read_disk, %struct.archive_read_disk* %10, i32 0, i32 5, !dbg !658
  %11 = load i32 (%struct.tree*, i8*, i32)*, i32 (%struct.tree*, i8*, i32)** %open_on_current_dir, align 8, !dbg !658
  %12 = load %struct.archive_read_disk*, %struct.archive_read_disk** %a.addr, align 8, !dbg !659
  %tree15 = getelementptr inbounds %struct.archive_read_disk, %struct.archive_read_disk* %12, i32 0, i32 4, !dbg !660
  %13 = load %struct.tree*, %struct.tree** %tree15, align 8, !dbg !660
  %14 = load i8*, i8** %path, align 8, !dbg !661
  %call16 = call i32 %11(%struct.tree* %13, i8* %14, i32 2048), !dbg !657
  %15 = load i32*, i32** %fd.addr, align 8, !dbg !662
  store i32 %call16, i32* %15, align 4, !dbg !663
  %16 = load i32*, i32** %fd.addr, align 8, !dbg !664
  %17 = load i32, i32* %16, align 4, !dbg !666
  %cmp17 = icmp slt i32 %17, 0, !dbg !667
  br i1 %cmp17, label %if.then18, label %if.end20, !dbg !668

if.then18:                                        ; preds = %if.end14
  %18 = load %struct.archive_read_disk*, %struct.archive_read_disk** %a.addr, align 8, !dbg !669
  %archive = getelementptr inbounds %struct.archive_read_disk, %struct.archive_read_disk* %18, i32 0, i32 0, !dbg !671
  %call19 = call i32* @__errno_location() #1, !dbg !672
  %19 = load i32, i32* %call19, align 4, !dbg !672
  %20 = load i8*, i8** %path, align 8, !dbg !673
  call void (%struct.archive*, i32, i8*, ...) @archive_set_error(%struct.archive* %archive, i32 %19, i8* getelementptr inbounds ([16 x i8], [16 x i8]* @.str.4, i32 0, i32 0), i8* %20), !dbg !674
  store i32 -25, i32* %retval, align 4, !dbg !676
  br label %return, !dbg !676

if.end20:                                         ; preds = %if.end14
  br label %if.end21, !dbg !677

if.end21:                                         ; preds = %if.end20, %land.lhs.true, %if.end
  %21 = load i32*, i32** %fd.addr, align 8, !dbg !678
  %22 = load i32, i32* %21, align 4, !dbg !680
  %cmp22 = icmp sge i32 %22, 0, !dbg !681
  br i1 %cmp22, label %if.then23, label %if.else, !dbg !682

if.then23:                                        ; preds = %if.end21
  %23 = load i32*, i32** %fd.addr, align 8, !dbg !683
  %24 = load i32, i32* %23, align 4, !dbg !685
  %call24 = call i64 @lseek(i32 %24, i64 0, i32 1) #6, !dbg !686
  store i64 %call24, i64* %initial_off, align 8, !dbg !687
  %25 = load i64, i64* %initial_off, align 8, !dbg !688
  %cmp25 = icmp ne i64 %25, 0, !dbg !690
  br i1 %cmp25, label %if.then26, label %if.end28, !dbg !691

if.then26:                                        ; preds = %if.then23
  %26 = load i32*, i32** %fd.addr, align 8, !dbg !692
  %27 = load i32, i32* %26, align 4, !dbg !693
  %call27 = call i64 @lseek(i32 %27, i64 0, i32 0) #6, !dbg !694
  br label %if.end28, !dbg !694

if.end28:                                         ; preds = %if.then26, %if.then23
  br label %if.end41, !dbg !695

if.else:                                          ; preds = %if.end21
  call void @llvm.dbg.declare(metadata i8** %path29, metadata !696, metadata !238), !dbg !698
  %28 = load %struct.archive_entry*, %struct.archive_entry** %entry.addr, align 8, !dbg !699
  %call30 = call i8* @archive_entry_sourcepath(%struct.archive_entry* %28), !dbg !700
  store i8* %call30, i8** %path29, align 8, !dbg !701
  %29 = load i8*, i8** %path29, align 8, !dbg !702
  %cmp31 = icmp eq i8* %29, null, !dbg !704
  br i1 %cmp31, label %if.then32, label %if.end34, !dbg !705

if.then32:                                        ; preds = %if.else
  %30 = load %struct.archive_entry*, %struct.archive_entry** %entry.addr, align 8, !dbg !706
  %call33 = call i8* @archive_entry_pathname(%struct.archive_entry* %30), !dbg !707
  store i8* %call33, i8** %path29, align 8, !dbg !708
  br label %if.end34, !dbg !709

if.end34:                                         ; preds = %if.then32, %if.else
  %31 = load i8*, i8** %path29, align 8, !dbg !710
  %call35 = call i32 (i8*, i32, ...) @open(i8* %31, i32 526336), !dbg !711
  %32 = load i32*, i32** %fd.addr, align 8, !dbg !712
  store i32 %call35, i32* %32, align 4, !dbg !713
  %33 = load i32*, i32** %fd.addr, align 8, !dbg !714
  %34 = load i32, i32* %33, align 4, !dbg !716
  %cmp36 = icmp slt i32 %34, 0, !dbg !717
  br i1 %cmp36, label %if.then37, label %if.end40, !dbg !718

if.then37:                                        ; preds = %if.end34
  %35 = load %struct.archive_read_disk*, %struct.archive_read_disk** %a.addr, align 8, !dbg !719
  %archive38 = getelementptr inbounds %struct.archive_read_disk, %struct.archive_read_disk* %35, i32 0, i32 0, !dbg !721
  %call39 = call i32* @__errno_location() #1, !dbg !722
  %36 = load i32, i32* %call39, align 4, !dbg !722
  %37 = load i8*, i8** %path29, align 8, !dbg !723
  call void (%struct.archive*, i32, i8*, ...) @archive_set_error(%struct.archive* %archive38, i32 %36, i8* getelementptr inbounds ([16 x i8], [16 x i8]* @.str.4, i32 0, i32 0), i8* %37), !dbg !724
  store i32 -25, i32* %retval, align 4, !dbg !726
  br label %return, !dbg !726

if.end40:                                         ; preds = %if.end34
  %38 = load i32*, i32** %fd.addr, align 8, !dbg !727
  %39 = load i32, i32* %38, align 4, !dbg !728
  call void @__archive_ensure_cloexec_flag(i32 %39), !dbg !729
  store i64 0, i64* %initial_off, align 8, !dbg !730
  br label %if.end41

if.end41:                                         ; preds = %if.end40, %if.end28
  %40 = load i32*, i32** %fd.addr, align 8, !dbg !731
  %41 = load i32, i32* %40, align 4, !dbg !732
  %call42 = call i64 @lseek(i32 %41, i64 0, i32 4) #6, !dbg !733
  store i64 %call42, i64* %off_s, align 8, !dbg !734
  %42 = load i64, i64* %off_s, align 8, !dbg !735
  %cmp43 = icmp slt i64 %42, 0, !dbg !737
  br i1 %cmp43, label %if.then44, label %if.else46, !dbg !738

if.then44:                                        ; preds = %if.end41
  %43 = load %struct.archive_read_disk*, %struct.archive_read_disk** %a.addr, align 8, !dbg !739
  %44 = load %struct.archive_entry*, %struct.archive_entry** %entry.addr, align 8, !dbg !740
  %45 = load i32*, i32** %fd.addr, align 8, !dbg !741
  %call45 = call i32 @setup_sparse_fiemap(%struct.archive_read_disk* %43, %struct.archive_entry* %44, i32* %45), !dbg !742
  store i32 %call45, i32* %retval, align 4, !dbg !743
  br label %return, !dbg !743

if.else46:                                        ; preds = %if.end41
  %46 = load i64, i64* %off_s, align 8, !dbg !744
  %cmp47 = icmp sgt i64 %46, 0, !dbg !746
  br i1 %cmp47, label %if.then48, label %if.end50, !dbg !747

if.then48:                                        ; preds = %if.else46
  %47 = load i32*, i32** %fd.addr, align 8, !dbg !748
  %48 = load i32, i32* %47, align 4, !dbg !749
  %call49 = call i64 @lseek(i32 %48, i64 0, i32 0) #6, !dbg !750
  br label %if.end50, !dbg !750

if.end50:                                         ; preds = %if.then48, %if.else46
  br label %if.end51

if.end51:                                         ; preds = %if.end50
  store i64 0, i64* %off_s, align 8, !dbg !751
  %49 = load %struct.archive_entry*, %struct.archive_entry** %entry.addr, align 8, !dbg !752
  %call52 = call i64 @archive_entry_size(%struct.archive_entry* %49), !dbg !753
  store i64 %call52, i64* %size, align 8, !dbg !754
  br label %while.cond, !dbg !755

while.cond:                                       ; preds = %if.end86, %if.end51
  %50 = load i64, i64* %off_s, align 8, !dbg !756
  %51 = load i64, i64* %size, align 8, !dbg !757
  %cmp53 = icmp slt i64 %50, %51, !dbg !758
  br i1 %cmp53, label %while.body, label %while.end, !dbg !759

while.body:                                       ; preds = %while.cond
  %52 = load i32*, i32** %fd.addr, align 8, !dbg !760
  %53 = load i32, i32* %52, align 4, !dbg !762
  %54 = load i64, i64* %off_s, align 8, !dbg !763
  %call54 = call i64 @lseek(i32 %53, i64 %54, i32 3) #6, !dbg !764
  store i64 %call54, i64* %off_s, align 8, !dbg !765
  %55 = load i64, i64* %off_s, align 8, !dbg !766
  %cmp55 = icmp eq i64 %55, -1, !dbg !768
  br i1 %cmp55, label %if.then56, label %if.end67, !dbg !769

if.then56:                                        ; preds = %while.body
  %call57 = call i32* @__errno_location() #1, !dbg !770
  %56 = load i32, i32* %call57, align 4, !dbg !770
  %cmp58 = icmp eq i32 %56, 6, !dbg !773
  br i1 %cmp58, label %if.then59, label %if.end64, !dbg !774

if.then59:                                        ; preds = %if.then56
  %57 = load %struct.archive_entry*, %struct.archive_entry** %entry.addr, align 8, !dbg !775
  %call60 = call i32 @archive_entry_sparse_count(%struct.archive_entry* %57), !dbg !778
  %cmp61 = icmp eq i32 %call60, 0, !dbg !779
  br i1 %cmp61, label %if.then62, label %if.end63, !dbg !780

if.then62:                                        ; preds = %if.then59
  store i32 1, i32* %check_fully_sparse, align 4, !dbg !781
  br label %if.end63, !dbg !783

if.end63:                                         ; preds = %if.then62, %if.then59
  br label %while.end, !dbg !784

if.end64:                                         ; preds = %if.then56
  %58 = load %struct.archive_read_disk*, %struct.archive_read_disk** %a.addr, align 8, !dbg !785
  %archive65 = getelementptr inbounds %struct.archive_read_disk, %struct.archive_read_disk* %58, i32 0, i32 0, !dbg !786
  %call66 = call i32* @__errno_location() #1, !dbg !787
  %59 = load i32, i32* %call66, align 4, !dbg !787
  call void (%struct.archive*, i32, i8*, ...) @archive_set_error(%struct.archive* %archive65, i32 %59, i8* getelementptr inbounds ([24 x i8], [24 x i8]* @.str.5, i32 0, i32 0)), !dbg !788
  store i32 -25, i32* %exit_sts, align 4, !dbg !790
  br label %exit_setup_sparse, !dbg !791

if.end67:                                         ; preds = %while.body
  %60 = load i32*, i32** %fd.addr, align 8, !dbg !792
  %61 = load i32, i32* %60, align 4, !dbg !793
  %62 = load i64, i64* %off_s, align 8, !dbg !794
  %call68 = call i64 @lseek(i32 %61, i64 %62, i32 4) #6, !dbg !795
  store i64 %call68, i64* %off_e, align 8, !dbg !796
  %63 = load i64, i64* %off_e, align 8, !dbg !797
  %cmp69 = icmp eq i64 %63, -1, !dbg !799
  br i1 %cmp69, label %if.then70, label %if.end81, !dbg !800

if.then70:                                        ; preds = %if.end67
  %call71 = call i32* @__errno_location() #1, !dbg !801
  %64 = load i32, i32* %call71, align 4, !dbg !801
  %cmp72 = icmp eq i32 %64, 6, !dbg !804
  br i1 %cmp72, label %if.then73, label %if.end78, !dbg !805

if.then73:                                        ; preds = %if.then70
  %65 = load i32*, i32** %fd.addr, align 8, !dbg !806
  %66 = load i32, i32* %65, align 4, !dbg !808
  %call74 = call i64 @lseek(i32 %66, i64 0, i32 2) #6, !dbg !809
  store i64 %call74, i64* %off_e, align 8, !dbg !810
  %67 = load i64, i64* %off_e, align 8, !dbg !811
  %cmp75 = icmp ne i64 %67, -1, !dbg !813
  br i1 %cmp75, label %if.then76, label %if.end77, !dbg !814

if.then76:                                        ; preds = %if.then73
  br label %while.end, !dbg !815

if.end77:                                         ; preds = %if.then73
  br label %if.end78, !dbg !816

if.end78:                                         ; preds = %if.end77, %if.then70
  %68 = load %struct.archive_read_disk*, %struct.archive_read_disk** %a.addr, align 8, !dbg !817
  %archive79 = getelementptr inbounds %struct.archive_read_disk, %struct.archive_read_disk* %68, i32 0, i32 0, !dbg !818
  %call80 = call i32* @__errno_location() #1, !dbg !819
  %69 = load i32, i32* %call80, align 4, !dbg !819
  call void (%struct.archive*, i32, i8*, ...) @archive_set_error(%struct.archive* %archive79, i32 %69, i8* getelementptr inbounds ([24 x i8], [24 x i8]* @.str.6, i32 0, i32 0)), !dbg !820
  store i32 -25, i32* %exit_sts, align 4, !dbg !822
  br label %exit_setup_sparse, !dbg !823

if.end81:                                         ; preds = %if.end67
  %70 = load i64, i64* %off_s, align 8, !dbg !824
  %cmp82 = icmp eq i64 %70, 0, !dbg !826
  br i1 %cmp82, label %land.lhs.true83, label %if.end86, !dbg !827

land.lhs.true83:                                  ; preds = %if.end81
  %71 = load i64, i64* %off_e, align 8, !dbg !828
  %72 = load i64, i64* %size, align 8, !dbg !830
  %cmp84 = icmp eq i64 %71, %72, !dbg !831
  br i1 %cmp84, label %if.then85, label %if.end86, !dbg !832

if.then85:                                        ; preds = %land.lhs.true83
  br label %while.end, !dbg !833

if.end86:                                         ; preds = %land.lhs.true83, %if.end81
  %73 = load %struct.archive_entry*, %struct.archive_entry** %entry.addr, align 8, !dbg !834
  %74 = load i64, i64* %off_s, align 8, !dbg !835
  %75 = load i64, i64* %off_e, align 8, !dbg !836
  %76 = load i64, i64* %off_s, align 8, !dbg !837
  %sub = sub nsw i64 %75, %76, !dbg !838
  call void @archive_entry_sparse_add_entry(%struct.archive_entry* %73, i64 %74, i64 %sub), !dbg !839
  %77 = load i64, i64* %off_e, align 8, !dbg !840
  store i64 %77, i64* %off_s, align 8, !dbg !841
  br label %while.cond, !dbg !842

while.end:                                        ; preds = %if.then85, %if.then76, %if.end63, %while.cond
  %78 = load i32, i32* %check_fully_sparse, align 4, !dbg !844
  %tobool = icmp ne i32 %78, 0, !dbg !844
  br i1 %tobool, label %if.then87, label %if.end95, !dbg !846

if.then87:                                        ; preds = %while.end
  %79 = load i32*, i32** %fd.addr, align 8, !dbg !847
  %80 = load i32, i32* %79, align 4, !dbg !850
  %call88 = call i64 @lseek(i32 %80, i64 0, i32 4) #6, !dbg !851
  %cmp89 = icmp eq i64 %call88, 0, !dbg !852
  br i1 %cmp89, label %land.lhs.true90, label %if.end94, !dbg !853

land.lhs.true90:                                  ; preds = %if.then87
  %81 = load i32*, i32** %fd.addr, align 8, !dbg !854
  %82 = load i32, i32* %81, align 4, !dbg !855
  %call91 = call i64 @lseek(i32 %82, i64 0, i32 2) #6, !dbg !856
  %83 = load i64, i64* %size, align 8, !dbg !857
  %cmp92 = icmp eq i64 %call91, %83, !dbg !858
  br i1 %cmp92, label %if.then93, label %if.end94, !dbg !859

if.then93:                                        ; preds = %land.lhs.true90
  %84 = load %struct.archive_entry*, %struct.archive_entry** %entry.addr, align 8, !dbg !861
  call void @archive_entry_sparse_add_entry(%struct.archive_entry* %84, i64 0, i64 0), !dbg !863
  br label %if.end94, !dbg !864

if.end94:                                         ; preds = %if.then93, %land.lhs.true90, %if.then87
  br label %if.end95, !dbg !865

if.end95:                                         ; preds = %if.end94, %while.end
  br label %exit_setup_sparse, !dbg !866

exit_setup_sparse:                                ; preds = %if.end95, %if.end78, %if.end64
  %85 = load i32*, i32** %fd.addr, align 8, !dbg !868
  %86 = load i32, i32* %85, align 4, !dbg !869
  %87 = load i64, i64* %initial_off, align 8, !dbg !870
  %call96 = call i64 @lseek(i32 %86, i64 %87, i32 0) #6, !dbg !871
  %88 = load i32, i32* %exit_sts, align 4, !dbg !872
  store i32 %88, i32* %retval, align 4, !dbg !873
  br label %return, !dbg !873

return:                                           ; preds = %exit_setup_sparse, %if.then44, %if.then37, %if.then18, %if.then
  %89 = load i32, i32* %retval, align 4, !dbg !874
  ret i32 %89, !dbg !874
}

declare i32 @close(i32) #2

declare i32 @archive_entry_filetype(%struct.archive_entry*) #2

declare i64 @archive_entry_size(%struct.archive_entry*) #2

declare i8* @archive_entry_hardlink(%struct.archive_entry*) #2

; Function Attrs: nounwind
declare i64 @lseek(i32, i64, i32) #3

; Function Attrs: nounwind uwtable
define internal i32 @setup_sparse_fiemap(%struct.archive_read_disk* %a, %struct.archive_entry* %entry1, i32* %fd) #0 !dbg !233 {
entry:
  %retval = alloca i32, align 4
  %a.addr = alloca %struct.archive_read_disk*, align 8
  %entry.addr = alloca %struct.archive_entry*, align 8
  %fd.addr = alloca i32*, align 8
  %buff = alloca [4096 x i8], align 16
  %fm = alloca %struct.fiemap*, align 8
  %fe = alloca %struct.fiemap_extent*, align 8
  %size = alloca i64, align 8
  %count = alloca i32, align 4
  %do_fiemap = alloca i32, align 4
  %iters = alloca i32, align 4
  %exit_sts = alloca i32, align 4
  %path = alloca i8*, align 8
  %i = alloca i32, align 4
  %r = alloca i32, align 4
  %length = alloca i64, align 8
  store %struct.archive_read_disk* %a, %struct.archive_read_disk** %a.addr, align 8
  call void @llvm.dbg.declare(metadata %struct.archive_read_disk** %a.addr, metadata !875, metadata !238), !dbg !876
  store %struct.archive_entry* %entry1, %struct.archive_entry** %entry.addr, align 8
  call void @llvm.dbg.declare(metadata %struct.archive_entry** %entry.addr, metadata !877, metadata !238), !dbg !878
  store i32* %fd, i32** %fd.addr, align 8
  call void @llvm.dbg.declare(metadata i32** %fd.addr, metadata !879, metadata !238), !dbg !880
  call void @llvm.dbg.declare(metadata [4096 x i8]* %buff, metadata !881, metadata !238), !dbg !885
  call void @llvm.dbg.declare(metadata %struct.fiemap** %fm, metadata !886, metadata !238), !dbg !887
  call void @llvm.dbg.declare(metadata %struct.fiemap_extent** %fe, metadata !888, metadata !238), !dbg !890
  call void @llvm.dbg.declare(metadata i64* %size, metadata !891, metadata !238), !dbg !892
  call void @llvm.dbg.declare(metadata i32* %count, metadata !893, metadata !238), !dbg !894
  call void @llvm.dbg.declare(metadata i32* %do_fiemap, metadata !895, metadata !238), !dbg !896
  call void @llvm.dbg.declare(metadata i32* %iters, metadata !897, metadata !238), !dbg !898
  call void @llvm.dbg.declare(metadata i32* %exit_sts, metadata !899, metadata !238), !dbg !900
  store i32 0, i32* %exit_sts, align 4, !dbg !900
  %0 = load %struct.archive_entry*, %struct.archive_entry** %entry.addr, align 8, !dbg !901
  %call = call i32 @archive_entry_filetype(%struct.archive_entry* %0), !dbg !903
  %cmp = icmp ne i32 %call, 32768, !dbg !904
  br i1 %cmp, label %if.then, label %lor.lhs.false, !dbg !905

lor.lhs.false:                                    ; preds = %entry
  %1 = load %struct.archive_entry*, %struct.archive_entry** %entry.addr, align 8, !dbg !906
  %call2 = call i64 @archive_entry_size(%struct.archive_entry* %1), !dbg !908
  %cmp3 = icmp sle i64 %call2, 0, !dbg !909
  br i1 %cmp3, label %if.then, label %lor.lhs.false4, !dbg !910

lor.lhs.false4:                                   ; preds = %lor.lhs.false
  %2 = load %struct.archive_entry*, %struct.archive_entry** %entry.addr, align 8, !dbg !911
  %call5 = call i8* @archive_entry_hardlink(%struct.archive_entry* %2), !dbg !912
  %cmp6 = icmp ne i8* %call5, null, !dbg !913
  br i1 %cmp6, label %if.then, label %if.end, !dbg !914

if.then:                                          ; preds = %lor.lhs.false4, %lor.lhs.false, %entry
  store i32 0, i32* %retval, align 4, !dbg !916
  br label %return, !dbg !916

if.end:                                           ; preds = %lor.lhs.false4
  %3 = load i32*, i32** %fd.addr, align 8, !dbg !917
  %4 = load i32, i32* %3, align 4, !dbg !919
  %cmp7 = icmp slt i32 %4, 0, !dbg !920
  br i1 %cmp7, label %if.then8, label %if.end24, !dbg !921

if.then8:                                         ; preds = %if.end
  call void @llvm.dbg.declare(metadata i8** %path, metadata !922, metadata !238), !dbg !924
  %5 = load %struct.archive_entry*, %struct.archive_entry** %entry.addr, align 8, !dbg !925
  %call9 = call i8* @archive_entry_sourcepath(%struct.archive_entry* %5), !dbg !926
  store i8* %call9, i8** %path, align 8, !dbg !927
  %6 = load i8*, i8** %path, align 8, !dbg !928
  %cmp10 = icmp eq i8* %6, null, !dbg !930
  br i1 %cmp10, label %if.then11, label %if.end13, !dbg !931

if.then11:                                        ; preds = %if.then8
  %7 = load %struct.archive_entry*, %struct.archive_entry** %entry.addr, align 8, !dbg !932
  %call12 = call i8* @archive_entry_pathname(%struct.archive_entry* %7), !dbg !933
  store i8* %call12, i8** %path, align 8, !dbg !934
  br label %if.end13, !dbg !935

if.end13:                                         ; preds = %if.then11, %if.then8
  %8 = load %struct.archive_read_disk*, %struct.archive_read_disk** %a.addr, align 8, !dbg !936
  %tree = getelementptr inbounds %struct.archive_read_disk, %struct.archive_read_disk* %8, i32 0, i32 4, !dbg !938
  %9 = load %struct.tree*, %struct.tree** %tree, align 8, !dbg !938
  %cmp14 = icmp ne %struct.tree* %9, null, !dbg !939
  br i1 %cmp14, label %if.then15, label %if.else, !dbg !940

if.then15:                                        ; preds = %if.end13
  %10 = load %struct.archive_read_disk*, %struct.archive_read_disk** %a.addr, align 8, !dbg !941
  %open_on_current_dir = getelementptr inbounds %struct.archive_read_disk, %struct.archive_read_disk* %10, i32 0, i32 5, !dbg !942
  %11 = load i32 (%struct.tree*, i8*, i32)*, i32 (%struct.tree*, i8*, i32)** %open_on_current_dir, align 8, !dbg !942
  %12 = load %struct.archive_read_disk*, %struct.archive_read_disk** %a.addr, align 8, !dbg !943
  %tree16 = getelementptr inbounds %struct.archive_read_disk, %struct.archive_read_disk* %12, i32 0, i32 4, !dbg !944
  %13 = load %struct.tree*, %struct.tree** %tree16, align 8, !dbg !944
  %14 = load i8*, i8** %path, align 8, !dbg !945
  %call17 = call i32 %11(%struct.tree* %13, i8* %14, i32 526336), !dbg !941
  %15 = load i32*, i32** %fd.addr, align 8, !dbg !946
  store i32 %call17, i32* %15, align 4, !dbg !947
  br label %if.end19, !dbg !948

if.else:                                          ; preds = %if.end13
  %16 = load i8*, i8** %path, align 8, !dbg !949
  %call18 = call i32 (i8*, i32, ...) @open(i8* %16, i32 526336), !dbg !950
  %17 = load i32*, i32** %fd.addr, align 8, !dbg !951
  store i32 %call18, i32* %17, align 4, !dbg !952
  br label %if.end19

if.end19:                                         ; preds = %if.else, %if.then15
  %18 = load i32*, i32** %fd.addr, align 8, !dbg !953
  %19 = load i32, i32* %18, align 4, !dbg !955
  %cmp20 = icmp slt i32 %19, 0, !dbg !956
  br i1 %cmp20, label %if.then21, label %if.end23, !dbg !957

if.then21:                                        ; preds = %if.end19
  %20 = load %struct.archive_read_disk*, %struct.archive_read_disk** %a.addr, align 8, !dbg !958
  %archive = getelementptr inbounds %struct.archive_read_disk, %struct.archive_read_disk* %20, i32 0, i32 0, !dbg !960
  %call22 = call i32* @__errno_location() #1, !dbg !961
  %21 = load i32, i32* %call22, align 4, !dbg !961
  %22 = load i8*, i8** %path, align 8, !dbg !962
  call void (%struct.archive*, i32, i8*, ...) @archive_set_error(%struct.archive* %archive, i32 %21, i8* getelementptr inbounds ([16 x i8], [16 x i8]* @.str.4, i32 0, i32 0), i8* %22), !dbg !963
  store i32 -25, i32* %retval, align 4, !dbg !965
  br label %return, !dbg !965

if.end23:                                         ; preds = %if.end19
  %23 = load i32*, i32** %fd.addr, align 8, !dbg !966
  %24 = load i32, i32* %23, align 4, !dbg !967
  call void @__archive_ensure_cloexec_flag(i32 %24), !dbg !968
  br label %if.end24, !dbg !969

if.end24:                                         ; preds = %if.end23, %if.end
  %arraydecay = getelementptr inbounds [4096 x i8], [4096 x i8]* %buff, i32 0, i32 0, !dbg !970
  call void @llvm.memset.p0i8.i64(i8* %arraydecay, i8 0, i64 4096, i32 16, i1 false), !dbg !970
  store i32 72, i32* %count, align 4, !dbg !971
  %arraydecay25 = getelementptr inbounds [4096 x i8], [4096 x i8]* %buff, i32 0, i32 0, !dbg !972
  %25 = bitcast i8* %arraydecay25 to %struct.fiemap*, !dbg !973
  store %struct.fiemap* %25, %struct.fiemap** %fm, align 8, !dbg !974
  %26 = load %struct.fiemap*, %struct.fiemap** %fm, align 8, !dbg !975
  %fm_start = getelementptr inbounds %struct.fiemap, %struct.fiemap* %26, i32 0, i32 0, !dbg !976
  store i64 0, i64* %fm_start, align 8, !dbg !977
  %27 = load %struct.fiemap*, %struct.fiemap** %fm, align 8, !dbg !978
  %fm_length = getelementptr inbounds %struct.fiemap, %struct.fiemap* %27, i32 0, i32 1, !dbg !979
  store i64 -1, i64* %fm_length, align 8, !dbg !980
  %28 = load %struct.fiemap*, %struct.fiemap** %fm, align 8, !dbg !981
  %fm_flags = getelementptr inbounds %struct.fiemap, %struct.fiemap* %28, i32 0, i32 2, !dbg !982
  store i32 1, i32* %fm_flags, align 8, !dbg !983
  %29 = load i32, i32* %count, align 4, !dbg !984
  %30 = load %struct.fiemap*, %struct.fiemap** %fm, align 8, !dbg !985
  %fm_extent_count = getelementptr inbounds %struct.fiemap, %struct.fiemap* %30, i32 0, i32 4, !dbg !986
  store i32 %29, i32* %fm_extent_count, align 8, !dbg !987
  store i32 1, i32* %do_fiemap, align 4, !dbg !988
  %31 = load %struct.archive_entry*, %struct.archive_entry** %entry.addr, align 8, !dbg !989
  %call26 = call i64 @archive_entry_size(%struct.archive_entry* %31), !dbg !990
  store i64 %call26, i64* %size, align 8, !dbg !991
  store i32 0, i32* %iters, align 4, !dbg !992
  br label %for.cond, !dbg !994

for.cond:                                         ; preds = %for.inc75, %if.end24
  call void @llvm.dbg.declare(metadata i32* %i, metadata !995, metadata !238), !dbg !998
  call void @llvm.dbg.declare(metadata i32* %r, metadata !999, metadata !238), !dbg !1000
  %32 = load i32*, i32** %fd.addr, align 8, !dbg !1001
  %33 = load i32, i32* %32, align 4, !dbg !1002
  %34 = load %struct.fiemap*, %struct.fiemap** %fm, align 8, !dbg !1003
  %call27 = call i32 (i32, i64, ...) @ioctl(i32 %33, i64 3223348747, %struct.fiemap* %34) #6, !dbg !1004
  store i32 %call27, i32* %r, align 4, !dbg !1005
  %35 = load i32, i32* %r, align 4, !dbg !1006
  %cmp28 = icmp slt i32 %35, 0, !dbg !1008
  br i1 %cmp28, label %if.then29, label %if.end30, !dbg !1009

if.then29:                                        ; preds = %for.cond
  br label %exit_setup_sparse_fiemap, !dbg !1010

if.end30:                                         ; preds = %for.cond
  %36 = load %struct.fiemap*, %struct.fiemap** %fm, align 8, !dbg !1012
  %fm_mapped_extents = getelementptr inbounds %struct.fiemap, %struct.fiemap* %36, i32 0, i32 3, !dbg !1014
  %37 = load i32, i32* %fm_mapped_extents, align 4, !dbg !1014
  %cmp31 = icmp eq i32 %37, 0, !dbg !1015
  br i1 %cmp31, label %if.then32, label %if.end36, !dbg !1016

if.then32:                                        ; preds = %if.end30
  %38 = load i32, i32* %iters, align 4, !dbg !1017
  %cmp33 = icmp eq i32 %38, 0, !dbg !1020
  br i1 %cmp33, label %if.then34, label %if.end35, !dbg !1021

if.then34:                                        ; preds = %if.then32
  %39 = load %struct.archive_entry*, %struct.archive_entry** %entry.addr, align 8, !dbg !1022
  call void @archive_entry_sparse_add_entry(%struct.archive_entry* %39, i64 0, i64 0), !dbg !1024
  br label %if.end35, !dbg !1025

if.end35:                                         ; preds = %if.then34, %if.then32
  br label %for.end77, !dbg !1026

if.end36:                                         ; preds = %if.end30
  %40 = load %struct.fiemap*, %struct.fiemap** %fm, align 8, !dbg !1027
  %fm_extents = getelementptr inbounds %struct.fiemap, %struct.fiemap* %40, i32 0, i32 6, !dbg !1028
  %arraydecay37 = getelementptr inbounds [0 x %struct.fiemap_extent], [0 x %struct.fiemap_extent]* %fm_extents, i32 0, i32 0, !dbg !1027
  store %struct.fiemap_extent* %arraydecay37, %struct.fiemap_extent** %fe, align 8, !dbg !1029
  store i32 0, i32* %i, align 4, !dbg !1030
  br label %for.cond38, !dbg !1032

for.cond38:                                       ; preds = %for.inc, %if.end36
  %41 = load i32, i32* %i, align 4, !dbg !1033
  %42 = load %struct.fiemap*, %struct.fiemap** %fm, align 8, !dbg !1036
  %fm_mapped_extents39 = getelementptr inbounds %struct.fiemap, %struct.fiemap* %42, i32 0, i32 3, !dbg !1037
  %43 = load i32, i32* %fm_mapped_extents39, align 4, !dbg !1037
  %cmp40 = icmp slt i32 %41, %43, !dbg !1038
  br i1 %cmp40, label %for.body, label %for.end, !dbg !1039

for.body:                                         ; preds = %for.cond38
  %44 = load %struct.fiemap_extent*, %struct.fiemap_extent** %fe, align 8, !dbg !1040
  %fe_flags = getelementptr inbounds %struct.fiemap_extent, %struct.fiemap_extent* %44, i32 0, i32 4, !dbg !1043
  %45 = load i32, i32* %fe_flags, align 8, !dbg !1043
  %and = and i32 %45, 2048, !dbg !1044
  %tobool = icmp ne i32 %and, 0, !dbg !1044
  br i1 %tobool, label %if.end57, label %if.then41, !dbg !1045

if.then41:                                        ; preds = %for.body
  call void @llvm.dbg.declare(metadata i64* %length, metadata !1046, metadata !238), !dbg !1048
  %46 = load %struct.fiemap_extent*, %struct.fiemap_extent** %fe, align 8, !dbg !1049
  %fe_length = getelementptr inbounds %struct.fiemap_extent, %struct.fiemap_extent* %46, i32 0, i32 2, !dbg !1050
  %47 = load i64, i64* %fe_length, align 8, !dbg !1050
  store i64 %47, i64* %length, align 8, !dbg !1048
  %48 = load %struct.fiemap_extent*, %struct.fiemap_extent** %fe, align 8, !dbg !1051
  %fe_logical = getelementptr inbounds %struct.fiemap_extent, %struct.fiemap_extent* %48, i32 0, i32 0, !dbg !1053
  %49 = load i64, i64* %fe_logical, align 8, !dbg !1053
  %50 = load i64, i64* %length, align 8, !dbg !1054
  %add = add i64 %49, %50, !dbg !1055
  %51 = load i64, i64* %size, align 8, !dbg !1056
  %cmp42 = icmp ugt i64 %add, %51, !dbg !1057
  br i1 %cmp42, label %if.then43, label %if.end47, !dbg !1058

if.then43:                                        ; preds = %if.then41
  %52 = load %struct.fiemap_extent*, %struct.fiemap_extent** %fe, align 8, !dbg !1059
  %fe_logical44 = getelementptr inbounds %struct.fiemap_extent, %struct.fiemap_extent* %52, i32 0, i32 0, !dbg !1060
  %53 = load i64, i64* %fe_logical44, align 8, !dbg !1060
  %54 = load i64, i64* %length, align 8, !dbg !1061
  %add45 = add i64 %53, %54, !dbg !1062
  %55 = load i64, i64* %size, align 8, !dbg !1063
  %sub = sub i64 %add45, %55, !dbg !1064
  %56 = load i64, i64* %length, align 8, !dbg !1065
  %sub46 = sub i64 %56, %sub, !dbg !1065
  store i64 %sub46, i64* %length, align 8, !dbg !1065
  br label %if.end47, !dbg !1066

if.end47:                                         ; preds = %if.then43, %if.then41
  %57 = load %struct.fiemap_extent*, %struct.fiemap_extent** %fe, align 8, !dbg !1067
  %fe_logical48 = getelementptr inbounds %struct.fiemap_extent, %struct.fiemap_extent* %57, i32 0, i32 0, !dbg !1069
  %58 = load i64, i64* %fe_logical48, align 8, !dbg !1069
  %cmp49 = icmp eq i64 %58, 0, !dbg !1070
  br i1 %cmp49, label %land.lhs.true, label %if.end52, !dbg !1071

land.lhs.true:                                    ; preds = %if.end47
  %59 = load i64, i64* %length, align 8, !dbg !1072
  %60 = load i64, i64* %size, align 8, !dbg !1074
  %cmp50 = icmp eq i64 %59, %60, !dbg !1075
  br i1 %cmp50, label %if.then51, label %if.end52, !dbg !1076

if.then51:                                        ; preds = %land.lhs.true
  store i32 0, i32* %do_fiemap, align 4, !dbg !1077
  br label %for.end, !dbg !1079

if.end52:                                         ; preds = %land.lhs.true, %if.end47
  %61 = load i64, i64* %length, align 8, !dbg !1080
  %cmp53 = icmp sgt i64 %61, 0, !dbg !1082
  br i1 %cmp53, label %if.then54, label %if.end56, !dbg !1083

if.then54:                                        ; preds = %if.end52
  %62 = load %struct.archive_entry*, %struct.archive_entry** %entry.addr, align 8, !dbg !1084
  %63 = load %struct.fiemap_extent*, %struct.fiemap_extent** %fe, align 8, !dbg !1085
  %fe_logical55 = getelementptr inbounds %struct.fiemap_extent, %struct.fiemap_extent* %63, i32 0, i32 0, !dbg !1086
  %64 = load i64, i64* %fe_logical55, align 8, !dbg !1086
  %65 = load i64, i64* %length, align 8, !dbg !1087
  call void @archive_entry_sparse_add_entry(%struct.archive_entry* %62, i64 %64, i64 %65), !dbg !1088
  br label %if.end56, !dbg !1088

if.end56:                                         ; preds = %if.then54, %if.end52
  br label %if.end57, !dbg !1089

if.end57:                                         ; preds = %if.end56, %for.body
  %66 = load %struct.fiemap_extent*, %struct.fiemap_extent** %fe, align 8, !dbg !1090
  %fe_flags58 = getelementptr inbounds %struct.fiemap_extent, %struct.fiemap_extent* %66, i32 0, i32 4, !dbg !1092
  %67 = load i32, i32* %fe_flags58, align 8, !dbg !1092
  %and59 = and i32 %67, 1, !dbg !1093
  %tobool60 = icmp ne i32 %and59, 0, !dbg !1093
  br i1 %tobool60, label %if.then61, label %if.end62, !dbg !1094

if.then61:                                        ; preds = %if.end57
  store i32 0, i32* %do_fiemap, align 4, !dbg !1095
  br label %if.end62, !dbg !1096

if.end62:                                         ; preds = %if.then61, %if.end57
  br label %for.inc, !dbg !1097

for.inc:                                          ; preds = %if.end62
  %68 = load i32, i32* %i, align 4, !dbg !1098
  %inc = add nsw i32 %68, 1, !dbg !1098
  store i32 %inc, i32* %i, align 4, !dbg !1098
  %69 = load %struct.fiemap_extent*, %struct.fiemap_extent** %fe, align 8, !dbg !1100
  %incdec.ptr = getelementptr inbounds %struct.fiemap_extent, %struct.fiemap_extent* %69, i32 1, !dbg !1100
  store %struct.fiemap_extent* %incdec.ptr, %struct.fiemap_extent** %fe, align 8, !dbg !1100
  br label %for.cond38, !dbg !1101

for.end:                                          ; preds = %if.then51, %for.cond38
  %70 = load i32, i32* %do_fiemap, align 4, !dbg !1102
  %tobool63 = icmp ne i32 %70, 0, !dbg !1102
  br i1 %tobool63, label %if.then64, label %if.else73, !dbg !1104

if.then64:                                        ; preds = %for.end
  %71 = load %struct.fiemap*, %struct.fiemap** %fm, align 8, !dbg !1105
  %fm_extents65 = getelementptr inbounds %struct.fiemap, %struct.fiemap* %71, i32 0, i32 6, !dbg !1107
  %arraydecay66 = getelementptr inbounds [0 x %struct.fiemap_extent], [0 x %struct.fiemap_extent]* %fm_extents65, i32 0, i32 0, !dbg !1105
  %72 = load %struct.fiemap*, %struct.fiemap** %fm, align 8, !dbg !1108
  %fm_mapped_extents67 = getelementptr inbounds %struct.fiemap, %struct.fiemap* %72, i32 0, i32 3, !dbg !1109
  %73 = load i32, i32* %fm_mapped_extents67, align 4, !dbg !1109
  %idx.ext = zext i32 %73 to i64, !dbg !1110
  %add.ptr = getelementptr inbounds %struct.fiemap_extent, %struct.fiemap_extent* %arraydecay66, i64 %idx.ext, !dbg !1110
  %add.ptr68 = getelementptr inbounds %struct.fiemap_extent, %struct.fiemap_extent* %add.ptr, i64 -1, !dbg !1111
  store %struct.fiemap_extent* %add.ptr68, %struct.fiemap_extent** %fe, align 8, !dbg !1112
  %74 = load %struct.fiemap_extent*, %struct.fiemap_extent** %fe, align 8, !dbg !1113
  %fe_logical69 = getelementptr inbounds %struct.fiemap_extent, %struct.fiemap_extent* %74, i32 0, i32 0, !dbg !1114
  %75 = load i64, i64* %fe_logical69, align 8, !dbg !1114
  %76 = load %struct.fiemap_extent*, %struct.fiemap_extent** %fe, align 8, !dbg !1115
  %fe_length70 = getelementptr inbounds %struct.fiemap_extent, %struct.fiemap_extent* %76, i32 0, i32 2, !dbg !1116
  %77 = load i64, i64* %fe_length70, align 8, !dbg !1116
  %add71 = add i64 %75, %77, !dbg !1117
  %78 = load %struct.fiemap*, %struct.fiemap** %fm, align 8, !dbg !1118
  %fm_start72 = getelementptr inbounds %struct.fiemap, %struct.fiemap* %78, i32 0, i32 0, !dbg !1119
  store i64 %add71, i64* %fm_start72, align 8, !dbg !1120
  br label %if.end74, !dbg !1121

if.else73:                                        ; preds = %for.end
  br label %for.end77, !dbg !1122

if.end74:                                         ; preds = %if.then64
  br label %for.inc75, !dbg !1123

for.inc75:                                        ; preds = %if.end74
  %79 = load i32, i32* %iters, align 4, !dbg !1124
  %inc76 = add nsw i32 %79, 1, !dbg !1124
  store i32 %inc76, i32* %iters, align 4, !dbg !1124
  br label %for.cond, !dbg !1126

for.end77:                                        ; preds = %if.else73, %if.end35
  br label %exit_setup_sparse_fiemap, !dbg !1127

exit_setup_sparse_fiemap:                         ; preds = %for.end77, %if.then29
  %80 = load i32, i32* %exit_sts, align 4, !dbg !1129
  store i32 %80, i32* %retval, align 4, !dbg !1130
  br label %return, !dbg !1130

return:                                           ; preds = %exit_setup_sparse_fiemap, %if.then21, %if.then
  %81 = load i32, i32* %retval, align 4, !dbg !1131
  ret i32 %81, !dbg !1131
}

declare i32 @archive_entry_sparse_count(%struct.archive_entry*) #2

declare void @archive_entry_sparse_add_entry(%struct.archive_entry*, i64, i64) #2

; Function Attrs: argmemonly nounwind
declare void @llvm.memset.p0i8.i64(i8* nocapture, i8, i64, i32, i1) #5

attributes #0 = { nounwind uwtable "disable-tail-calls"="false" "less-precise-fpmad"="false" "no-frame-pointer-elim"="true" "no-frame-pointer-elim-non-leaf" "no-infs-fp-math"="false" "no-nans-fp-math"="false" "stack-protector-buffer-size"="8" "target-cpu"="x86-64" "target-features"="+fxsr,+mmx,+sse,+sse2" "unsafe-fp-math"="false" "use-soft-float"="false" }
attributes #1 = { nounwind readnone }
attributes #2 = { "disable-tail-calls"="false" "less-precise-fpmad"="false" "no-frame-pointer-elim"="true" "no-frame-pointer-elim-non-leaf" "no-infs-fp-math"="false" "no-nans-fp-math"="false" "stack-protector-buffer-size"="8" "target-cpu"="x86-64" "target-features"="+fxsr,+mmx,+sse,+sse2" "unsafe-fp-math"="false" "use-soft-float"="false" }
attributes #3 = { nounwind "disable-tail-calls"="false" "less-precise-fpmad"="false" "no-frame-pointer-elim"="true" "no-frame-pointer-elim-non-leaf" "no-infs-fp-math"="false" "no-nans-fp-math"="false" "stack-protector-buffer-size"="8" "target-cpu"="x86-64" "target-features"="+fxsr,+mmx,+sse,+sse2" "unsafe-fp-math"="false" "use-soft-float"="false" }
attributes #4 = { nounwind readnone "disable-tail-calls"="false" "less-precise-fpmad"="false" "no-frame-pointer-elim"="true" "no-frame-pointer-elim-non-leaf" "no-infs-fp-math"="false" "no-nans-fp-math"="false" "stack-protector-buffer-size"="8" "target-cpu"="x86-64" "target-features"="+fxsr,+mmx,+sse,+sse2" "unsafe-fp-math"="false" "use-soft-float"="false" }
attributes #5 = { argmemonly nounwind }
attributes #6 = { nounwind }

!llvm.dbg.cu = !{!0}
!llvm.module.flags = !{!234, !235}
!llvm.ident = !{!236}

!0 = distinct !DICompileUnit(language: DW_LANG_C99, file: !1, producer: "clang version 3.8.0 (tags/RELEASE_380/final)", isOptimized: false, runtimeVersion: 0, emissionKind: 1, enums: !2, retainedTypes: !3, subprograms: !187)
!1 = !DIFile(filename: "/data/download/cmake/cmake-master/Utilities/cmlibarchive/libarchive/archive_read_disk_entry_from_file.c", directory: "/data/download/cmake/cmake-master/Utilities/cmlibarchive/libarchive")
!2 = !{}
!3 = !{!4, !130, !150, !152, !154, !23, !186}
!4 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !5, size: 64, align: 64)
!5 = !DICompositeType(tag: DW_TAG_structure_type, name: "archive_read_disk", file: !6, line: 39, size: 2432, align: 64, elements: !7)
!6 = !DIFile(filename: "/data/download/cmake/cmake-master/Utilities/cmlibarchive/libarchive/archive_read_disk_private.h", directory: "/data/download/cmake/cmake-master/Utilities/cmlibarchive/libarchive")
!7 = !{!8, !110, !111, !112, !113, !116, !120, !124, !125, !126, !131, !135, !136, !137, !138, !139, !143, !144, !145, !149}
!8 = !DIDerivedType(tag: DW_TAG_member, name: "archive", scope: !5, file: !6, line: 40, baseType: !9, size: 1280, align: 64)
!9 = !DICompositeType(tag: DW_TAG_structure_type, name: "archive", file: !10, line: 89, size: 1280, align: 64, elements: !11)
!10 = !DIFile(filename: "/data/download/cmake/cmake-master/Utilities/cmlibarchive/libarchive/archive_private.h", directory: "/data/download/cmake/cmake-master/Utilities/cmlibarchive/libarchive")
!11 = !{!12, !14, !15, !83, !84, !85, !86, !87, !88, !89, !90, !98, !99, !100, !101, !104, !105, !106, !107, !108, !109}
!12 = !DIDerivedType(tag: DW_TAG_member, name: "magic", scope: !9, file: !10, line: 96, baseType: !13, size: 32, align: 32)
!13 = !DIBasicType(name: "unsigned int", size: 32, align: 32, encoding: DW_ATE_unsigned)
!14 = !DIDerivedType(tag: DW_TAG_member, name: "state", scope: !9, file: !10, line: 97, baseType: !13, size: 32, align: 32, offset: 32)
!15 = !DIDerivedType(tag: DW_TAG_member, name: "vtable", scope: !9, file: !10, line: 103, baseType: !16, size: 64, align: 64, offset: 64)
!16 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !17, size: 64, align: 64)
!17 = !DICompositeType(tag: DW_TAG_structure_type, name: "archive_vtable", file: !10, line: 63, size: 832, align: 64, elements: !18)
!18 = !{!19, !25, !26, !33, !34, !48, !54, !59, !60, !67, !68, !72, !76}
!19 = !DIDerivedType(tag: DW_TAG_member, name: "archive_close", scope: !17, file: !10, line: 64, baseType: !20, size: 64, align: 64)
!20 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !21, size: 64, align: 64)
!21 = !DISubroutineType(types: !22)
!22 = !{!23, !24}
!23 = !DIBasicType(name: "int", size: 32, align: 32, encoding: DW_ATE_signed)
!24 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !9, size: 64, align: 64)
!25 = !DIDerivedType(tag: DW_TAG_member, name: "archive_free", scope: !17, file: !10, line: 65, baseType: !20, size: 64, align: 64, offset: 64)
!26 = !DIDerivedType(tag: DW_TAG_member, name: "archive_write_header", scope: !17, file: !10, line: 66, baseType: !27, size: 64, align: 64, offset: 128)
!27 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !28, size: 64, align: 64)
!28 = !DISubroutineType(types: !29)
!29 = !{!23, !24, !30}
!30 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !31, size: 64, align: 64)
!31 = !DICompositeType(tag: DW_TAG_structure_type, name: "archive_entry", file: !32, line: 180, flags: DIFlagFwdDecl)
!32 = !DIFile(filename: "/data/download/cmake/cmake-master/Utilities/cmlibarchive/libarchive/archive.h", directory: "/data/download/cmake/cmake-master/Utilities/cmlibarchive/libarchive")
!33 = !DIDerivedType(tag: DW_TAG_member, name: "archive_write_finish_entry", scope: !17, file: !10, line: 68, baseType: !20, size: 64, align: 64, offset: 192)
!34 = !DIDerivedType(tag: DW_TAG_member, name: "archive_write_data", scope: !17, file: !10, line: 69, baseType: !35, size: 64, align: 64, offset: 256)
!35 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !36, size: 64, align: 64)
!36 = !DISubroutineType(types: !37)
!37 = !{!38, !24, !43, !45}
!38 = !DIDerivedType(tag: DW_TAG_typedef, name: "ssize_t", file: !39, line: 109, baseType: !40)
!39 = !DIFile(filename: "/usr/include/x86_64-linux-gnu/sys/types.h", directory: "/data/download/cmake/cmake-master/Utilities/cmlibarchive/libarchive")
!40 = !DIDerivedType(tag: DW_TAG_typedef, name: "__ssize_t", file: !41, line: 172, baseType: !42)
!41 = !DIFile(filename: "/usr/include/x86_64-linux-gnu/bits/types.h", directory: "/data/download/cmake/cmake-master/Utilities/cmlibarchive/libarchive")
!42 = !DIBasicType(name: "long int", size: 64, align: 64, encoding: DW_ATE_signed)
!43 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !44, size: 64, align: 64)
!44 = !DIDerivedType(tag: DW_TAG_const_type, baseType: null)
!45 = !DIDerivedType(tag: DW_TAG_typedef, name: "size_t", file: !46, line: 62, baseType: !47)
!46 = !DIFile(filename: "/opt/llvm-build/bin/../lib/clang/3.8.0/include/stddef.h", directory: "/data/download/cmake/cmake-master/Utilities/cmlibarchive/libarchive")
!47 = !DIBasicType(name: "long unsigned int", size: 64, align: 64, encoding: DW_ATE_unsigned)
!48 = !DIDerivedType(tag: DW_TAG_member, name: "archive_write_data_block", scope: !17, file: !10, line: 71, baseType: !49, size: 64, align: 64, offset: 320)
!49 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !50, size: 64, align: 64)
!50 = !DISubroutineType(types: !51)
!51 = !{!38, !24, !43, !45, !52}
!52 = !DIDerivedType(tag: DW_TAG_typedef, name: "int64_t", file: !53, line: 40, baseType: !42)
!53 = !DIFile(filename: "/usr/include/stdint.h", directory: "/data/download/cmake/cmake-master/Utilities/cmlibarchive/libarchive")
!54 = !DIDerivedType(tag: DW_TAG_member, name: "archive_read_next_header", scope: !17, file: !10, line: 74, baseType: !55, size: 64, align: 64, offset: 384)
!55 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !56, size: 64, align: 64)
!56 = !DISubroutineType(types: !57)
!57 = !{!23, !24, !58}
!58 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !30, size: 64, align: 64)
!59 = !DIDerivedType(tag: DW_TAG_member, name: "archive_read_next_header2", scope: !17, file: !10, line: 76, baseType: !27, size: 64, align: 64, offset: 448)
!60 = !DIDerivedType(tag: DW_TAG_member, name: "archive_read_data_block", scope: !17, file: !10, line: 78, baseType: !61, size: 64, align: 64, offset: 512)
!61 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !62, size: 64, align: 64)
!62 = !DISubroutineType(types: !63)
!63 = !{!23, !24, !64, !65, !66}
!64 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !43, size: 64, align: 64)
!65 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !45, size: 64, align: 64)
!66 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !52, size: 64, align: 64)
!67 = !DIDerivedType(tag: DW_TAG_member, name: "archive_filter_count", scope: !17, file: !10, line: 81, baseType: !20, size: 64, align: 64, offset: 576)
!68 = !DIDerivedType(tag: DW_TAG_member, name: "archive_filter_bytes", scope: !17, file: !10, line: 82, baseType: !69, size: 64, align: 64, offset: 640)
!69 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !70, size: 64, align: 64)
!70 = !DISubroutineType(types: !71)
!71 = !{!52, !24, !23}
!72 = !DIDerivedType(tag: DW_TAG_member, name: "archive_filter_code", scope: !17, file: !10, line: 83, baseType: !73, size: 64, align: 64, offset: 704)
!73 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !74, size: 64, align: 64)
!74 = !DISubroutineType(types: !75)
!75 = !{!23, !24, !23}
!76 = !DIDerivedType(tag: DW_TAG_member, name: "archive_filter_name", scope: !17, file: !10, line: 84, baseType: !77, size: 64, align: 64, offset: 768)
!77 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !78, size: 64, align: 64)
!78 = !DISubroutineType(types: !79)
!79 = !{!80, !24, !23}
!80 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !81, size: 64, align: 64)
!81 = !DIDerivedType(tag: DW_TAG_const_type, baseType: !82)
!82 = !DIBasicType(name: "char", size: 8, align: 8, encoding: DW_ATE_signed_char)
!83 = !DIDerivedType(tag: DW_TAG_member, name: "archive_format", scope: !9, file: !10, line: 105, baseType: !23, size: 32, align: 32, offset: 128)
!84 = !DIDerivedType(tag: DW_TAG_member, name: "archive_format_name", scope: !9, file: !10, line: 106, baseType: !80, size: 64, align: 64, offset: 192)
!85 = !DIDerivedType(tag: DW_TAG_member, name: "compression_code", scope: !9, file: !10, line: 108, baseType: !23, size: 32, align: 32, offset: 256)
!86 = !DIDerivedType(tag: DW_TAG_member, name: "compression_name", scope: !9, file: !10, line: 109, baseType: !80, size: 64, align: 64, offset: 320)
!87 = !DIDerivedType(tag: DW_TAG_member, name: "file_count", scope: !9, file: !10, line: 112, baseType: !23, size: 32, align: 32, offset: 384)
!88 = !DIDerivedType(tag: DW_TAG_member, name: "archive_error_number", scope: !9, file: !10, line: 114, baseType: !23, size: 32, align: 32, offset: 416)
!89 = !DIDerivedType(tag: DW_TAG_member, name: "error", scope: !9, file: !10, line: 115, baseType: !80, size: 64, align: 64, offset: 448)
!90 = !DIDerivedType(tag: DW_TAG_member, name: "error_string", scope: !9, file: !10, line: 116, baseType: !91, size: 192, align: 64, offset: 512)
!91 = !DICompositeType(tag: DW_TAG_structure_type, name: "archive_string", file: !92, line: 58, size: 192, align: 64, elements: !93)
!92 = !DIFile(filename: "/data/download/cmake/cmake-master/Utilities/cmlibarchive/libarchive/archive_string.h", directory: "/data/download/cmake/cmake-master/Utilities/cmlibarchive/libarchive")
!93 = !{!94, !96, !97}
!94 = !DIDerivedType(tag: DW_TAG_member, name: "s", scope: !91, file: !92, line: 59, baseType: !95, size: 64, align: 64)
!95 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !82, size: 64, align: 64)
!96 = !DIDerivedType(tag: DW_TAG_member, name: "length", scope: !91, file: !92, line: 60, baseType: !45, size: 64, align: 64, offset: 64)
!97 = !DIDerivedType(tag: DW_TAG_member, name: "buffer_length", scope: !91, file: !92, line: 61, baseType: !45, size: 64, align: 64, offset: 128)
!98 = !DIDerivedType(tag: DW_TAG_member, name: "current_code", scope: !9, file: !10, line: 118, baseType: !95, size: 64, align: 64, offset: 704)
!99 = !DIDerivedType(tag: DW_TAG_member, name: "current_codepage", scope: !9, file: !10, line: 119, baseType: !13, size: 32, align: 32, offset: 768)
!100 = !DIDerivedType(tag: DW_TAG_member, name: "current_oemcp", scope: !9, file: !10, line: 120, baseType: !13, size: 32, align: 32, offset: 800)
!101 = !DIDerivedType(tag: DW_TAG_member, name: "sconv", scope: !9, file: !10, line: 121, baseType: !102, size: 64, align: 64, offset: 832)
!102 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !103, size: 64, align: 64)
!103 = !DICompositeType(tag: DW_TAG_structure_type, name: "archive_string_conv", file: !92, line: 70, flags: DIFlagFwdDecl)
!104 = !DIDerivedType(tag: DW_TAG_member, name: "read_data_block", scope: !9, file: !10, line: 127, baseType: !80, size: 64, align: 64, offset: 896)
!105 = !DIDerivedType(tag: DW_TAG_member, name: "read_data_offset", scope: !9, file: !10, line: 128, baseType: !52, size: 64, align: 64, offset: 960)
!106 = !DIDerivedType(tag: DW_TAG_member, name: "read_data_output_offset", scope: !9, file: !10, line: 129, baseType: !52, size: 64, align: 64, offset: 1024)
!107 = !DIDerivedType(tag: DW_TAG_member, name: "read_data_remaining", scope: !9, file: !10, line: 130, baseType: !45, size: 64, align: 64, offset: 1088)
!108 = !DIDerivedType(tag: DW_TAG_member, name: "read_data_is_posix_read", scope: !9, file: !10, line: 137, baseType: !82, size: 8, align: 8, offset: 1152)
!109 = !DIDerivedType(tag: DW_TAG_member, name: "read_data_requested", scope: !9, file: !10, line: 138, baseType: !45, size: 64, align: 64, offset: 1216)
!110 = !DIDerivedType(tag: DW_TAG_member, name: "entry", scope: !5, file: !6, line: 43, baseType: !30, size: 64, align: 64, offset: 1280)
!111 = !DIDerivedType(tag: DW_TAG_member, name: "symlink_mode", scope: !5, file: !6, line: 51, baseType: !82, size: 8, align: 8, offset: 1344)
!112 = !DIDerivedType(tag: DW_TAG_member, name: "follow_symlinks", scope: !5, file: !6, line: 58, baseType: !82, size: 8, align: 8, offset: 1352)
!113 = !DIDerivedType(tag: DW_TAG_member, name: "tree", scope: !5, file: !6, line: 61, baseType: !114, size: 64, align: 64, offset: 1408)
!114 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !115, size: 64, align: 64)
!115 = !DICompositeType(tag: DW_TAG_structure_type, name: "tree", file: !6, line: 36, flags: DIFlagFwdDecl)
!116 = !DIDerivedType(tag: DW_TAG_member, name: "open_on_current_dir", scope: !5, file: !6, line: 62, baseType: !117, size: 64, align: 64, offset: 1472)
!117 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !118, size: 64, align: 64)
!118 = !DISubroutineType(types: !119)
!119 = !{!23, !114, !80, !23}
!120 = !DIDerivedType(tag: DW_TAG_member, name: "tree_current_dir_fd", scope: !5, file: !6, line: 63, baseType: !121, size: 64, align: 64, offset: 1536)
!121 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !122, size: 64, align: 64)
!122 = !DISubroutineType(types: !123)
!123 = !{!23, !114}
!124 = !DIDerivedType(tag: DW_TAG_member, name: "tree_enter_working_dir", scope: !5, file: !6, line: 64, baseType: !121, size: 64, align: 64, offset: 1600)
!125 = !DIDerivedType(tag: DW_TAG_member, name: "flags", scope: !5, file: !6, line: 67, baseType: !23, size: 32, align: 32, offset: 1664)
!126 = !DIDerivedType(tag: DW_TAG_member, name: "lookup_gname", scope: !5, file: !6, line: 69, baseType: !127, size: 64, align: 64, offset: 1728)
!127 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !128, size: 64, align: 64)
!128 = !DISubroutineType(types: !129)
!129 = !{!80, !130, !52}
!130 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: null, size: 64, align: 64)
!131 = !DIDerivedType(tag: DW_TAG_member, name: "cleanup_gname", scope: !5, file: !6, line: 70, baseType: !132, size: 64, align: 64, offset: 1792)
!132 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !133, size: 64, align: 64)
!133 = !DISubroutineType(types: !134)
!134 = !{null, !130}
!135 = !DIDerivedType(tag: DW_TAG_member, name: "lookup_gname_data", scope: !5, file: !6, line: 71, baseType: !130, size: 64, align: 64, offset: 1856)
!136 = !DIDerivedType(tag: DW_TAG_member, name: "lookup_uname", scope: !5, file: !6, line: 72, baseType: !127, size: 64, align: 64, offset: 1920)
!137 = !DIDerivedType(tag: DW_TAG_member, name: "cleanup_uname", scope: !5, file: !6, line: 73, baseType: !132, size: 64, align: 64, offset: 1984)
!138 = !DIDerivedType(tag: DW_TAG_member, name: "lookup_uname_data", scope: !5, file: !6, line: 74, baseType: !130, size: 64, align: 64, offset: 2048)
!139 = !DIDerivedType(tag: DW_TAG_member, name: "metadata_filter_func", scope: !5, file: !6, line: 76, baseType: !140, size: 64, align: 64, offset: 2112)
!140 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !141, size: 64, align: 64)
!141 = !DISubroutineType(types: !142)
!142 = !{!23, !24, !130, !30}
!143 = !DIDerivedType(tag: DW_TAG_member, name: "metadata_filter_data", scope: !5, file: !6, line: 78, baseType: !130, size: 64, align: 64, offset: 2176)
!144 = !DIDerivedType(tag: DW_TAG_member, name: "matching", scope: !5, file: !6, line: 81, baseType: !24, size: 64, align: 64, offset: 2240)
!145 = !DIDerivedType(tag: DW_TAG_member, name: "excluded_cb_func", scope: !5, file: !6, line: 84, baseType: !146, size: 64, align: 64, offset: 2304)
!146 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !147, size: 64, align: 64)
!147 = !DISubroutineType(types: !148)
!148 = !{null, !24, !130, !30}
!149 = !DIDerivedType(tag: DW_TAG_member, name: "excluded_cb_data", scope: !5, file: !6, line: 86, baseType: !130, size: 64, align: 64, offset: 2368)
!150 = !DIDerivedType(tag: DW_TAG_typedef, name: "mode_t", file: !39, line: 70, baseType: !151)
!151 = !DIDerivedType(tag: DW_TAG_typedef, name: "__mode_t", file: !41, line: 129, baseType: !13)
!152 = !DIDerivedType(tag: DW_TAG_typedef, name: "off_t", file: !39, line: 86, baseType: !153)
!153 = !DIDerivedType(tag: DW_TAG_typedef, name: "__off_t", file: !41, line: 131, baseType: !42)
!154 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !155, size: 64, align: 64)
!155 = !DICompositeType(tag: DW_TAG_structure_type, name: "fiemap", file: !156, line: 27, size: 256, align: 64, elements: !157)
!156 = !DIFile(filename: "/usr/include/linux/fiemap.h", directory: "/data/download/cmake/cmake-master/Utilities/cmlibarchive/libarchive")
!157 = !{!158, !162, !163, !165, !166, !167, !168}
!158 = !DIDerivedType(tag: DW_TAG_member, name: "fm_start", scope: !155, file: !156, line: 28, baseType: !159, size: 64, align: 64)
!159 = !DIDerivedType(tag: DW_TAG_typedef, name: "__u64", file: !160, line: 30, baseType: !161)
!160 = !DIFile(filename: "/usr/include/asm-generic/int-ll64.h", directory: "/data/download/cmake/cmake-master/Utilities/cmlibarchive/libarchive")
!161 = !DIBasicType(name: "long long unsigned int", size: 64, align: 64, encoding: DW_ATE_unsigned)
!162 = !DIDerivedType(tag: DW_TAG_member, name: "fm_length", scope: !155, file: !156, line: 30, baseType: !159, size: 64, align: 64, offset: 64)
!163 = !DIDerivedType(tag: DW_TAG_member, name: "fm_flags", scope: !155, file: !156, line: 32, baseType: !164, size: 32, align: 32, offset: 128)
!164 = !DIDerivedType(tag: DW_TAG_typedef, name: "__u32", file: !160, line: 26, baseType: !13)
!165 = !DIDerivedType(tag: DW_TAG_member, name: "fm_mapped_extents", scope: !155, file: !156, line: 33, baseType: !164, size: 32, align: 32, offset: 160)
!166 = !DIDerivedType(tag: DW_TAG_member, name: "fm_extent_count", scope: !155, file: !156, line: 34, baseType: !164, size: 32, align: 32, offset: 192)
!167 = !DIDerivedType(tag: DW_TAG_member, name: "fm_reserved", scope: !155, file: !156, line: 35, baseType: !164, size: 32, align: 32, offset: 224)
!168 = !DIDerivedType(tag: DW_TAG_member, name: "fm_extents", scope: !155, file: !156, line: 36, baseType: !169, align: 64, offset: 256)
!169 = !DICompositeType(tag: DW_TAG_array_type, baseType: !170, align: 64, elements: !184)
!170 = !DICompositeType(tag: DW_TAG_structure_type, name: "fiemap_extent", file: !156, line: 16, size: 448, align: 64, elements: !171)
!171 = !{!172, !173, !174, !175, !179, !180}
!172 = !DIDerivedType(tag: DW_TAG_member, name: "fe_logical", scope: !170, file: !156, line: 17, baseType: !159, size: 64, align: 64)
!173 = !DIDerivedType(tag: DW_TAG_member, name: "fe_physical", scope: !170, file: !156, line: 19, baseType: !159, size: 64, align: 64, offset: 64)
!174 = !DIDerivedType(tag: DW_TAG_member, name: "fe_length", scope: !170, file: !156, line: 21, baseType: !159, size: 64, align: 64, offset: 128)
!175 = !DIDerivedType(tag: DW_TAG_member, name: "fe_reserved64", scope: !170, file: !156, line: 22, baseType: !176, size: 128, align: 64, offset: 192)
!176 = !DICompositeType(tag: DW_TAG_array_type, baseType: !159, size: 128, align: 64, elements: !177)
!177 = !{!178}
!178 = !DISubrange(count: 2)
!179 = !DIDerivedType(tag: DW_TAG_member, name: "fe_flags", scope: !170, file: !156, line: 23, baseType: !164, size: 32, align: 32, offset: 320)
!180 = !DIDerivedType(tag: DW_TAG_member, name: "fe_reserved", scope: !170, file: !156, line: 24, baseType: !181, size: 96, align: 32, offset: 352)
!181 = !DICompositeType(tag: DW_TAG_array_type, baseType: !164, size: 96, align: 32, elements: !182)
!182 = !{!183}
!183 = !DISubrange(count: 3)
!184 = !{!185}
!185 = !DISubrange(count: 0)
!186 = !DIDerivedType(tag: DW_TAG_typedef, name: "uint64_t", file: !53, line: 55, baseType: !47)
!187 = !{!188, !226, !230, !231, !232, !233}
!188 = distinct !DISubprogram(name: "archive_read_disk_entry_from_file", scope: !1, file: !1, line: 149, type: !189, isLocal: false, isDefinition: true, scopeLine: 153, flags: DIFlagPrototyped, isOptimized: false, variables: !2)
!189 = !DISubroutineType(types: !190)
!190 = !{!23, !24, !30, !23, !191}
!191 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !192, size: 64, align: 64)
!192 = !DIDerivedType(tag: DW_TAG_const_type, baseType: !193)
!193 = !DICompositeType(tag: DW_TAG_structure_type, name: "stat", file: !194, line: 46, size: 1152, align: 64, elements: !195)
!194 = !DIFile(filename: "/usr/include/x86_64-linux-gnu/bits/stat.h", directory: "/data/download/cmake/cmake-master/Utilities/cmlibarchive/libarchive")
!195 = !{!196, !198, !200, !202, !203, !205, !207, !208, !209, !210, !212, !214, !222, !223, !224}
!196 = !DIDerivedType(tag: DW_TAG_member, name: "st_dev", scope: !193, file: !194, line: 48, baseType: !197, size: 64, align: 64)
!197 = !DIDerivedType(tag: DW_TAG_typedef, name: "__dev_t", file: !41, line: 124, baseType: !47)
!198 = !DIDerivedType(tag: DW_TAG_member, name: "st_ino", scope: !193, file: !194, line: 53, baseType: !199, size: 64, align: 64, offset: 64)
!199 = !DIDerivedType(tag: DW_TAG_typedef, name: "__ino_t", file: !41, line: 127, baseType: !47)
!200 = !DIDerivedType(tag: DW_TAG_member, name: "st_nlink", scope: !193, file: !194, line: 61, baseType: !201, size: 64, align: 64, offset: 128)
!201 = !DIDerivedType(tag: DW_TAG_typedef, name: "__nlink_t", file: !41, line: 130, baseType: !47)
!202 = !DIDerivedType(tag: DW_TAG_member, name: "st_mode", scope: !193, file: !194, line: 62, baseType: !151, size: 32, align: 32, offset: 192)
!203 = !DIDerivedType(tag: DW_TAG_member, name: "st_uid", scope: !193, file: !194, line: 64, baseType: !204, size: 32, align: 32, offset: 224)
!204 = !DIDerivedType(tag: DW_TAG_typedef, name: "__uid_t", file: !41, line: 125, baseType: !13)
!205 = !DIDerivedType(tag: DW_TAG_member, name: "st_gid", scope: !193, file: !194, line: 65, baseType: !206, size: 32, align: 32, offset: 256)
!206 = !DIDerivedType(tag: DW_TAG_typedef, name: "__gid_t", file: !41, line: 126, baseType: !13)
!207 = !DIDerivedType(tag: DW_TAG_member, name: "__pad0", scope: !193, file: !194, line: 67, baseType: !23, size: 32, align: 32, offset: 288)
!208 = !DIDerivedType(tag: DW_TAG_member, name: "st_rdev", scope: !193, file: !194, line: 69, baseType: !197, size: 64, align: 64, offset: 320)
!209 = !DIDerivedType(tag: DW_TAG_member, name: "st_size", scope: !193, file: !194, line: 74, baseType: !153, size: 64, align: 64, offset: 384)
!210 = !DIDerivedType(tag: DW_TAG_member, name: "st_blksize", scope: !193, file: !194, line: 78, baseType: !211, size: 64, align: 64, offset: 448)
!211 = !DIDerivedType(tag: DW_TAG_typedef, name: "__blksize_t", file: !41, line: 153, baseType: !42)
!212 = !DIDerivedType(tag: DW_TAG_member, name: "st_blocks", scope: !193, file: !194, line: 80, baseType: !213, size: 64, align: 64, offset: 512)
!213 = !DIDerivedType(tag: DW_TAG_typedef, name: "__blkcnt_t", file: !41, line: 158, baseType: !42)
!214 = !DIDerivedType(tag: DW_TAG_member, name: "st_atim", scope: !193, file: !194, line: 91, baseType: !215, size: 128, align: 64, offset: 576)
!215 = !DICompositeType(tag: DW_TAG_structure_type, name: "timespec", file: !216, line: 120, size: 128, align: 64, elements: !217)
!216 = !DIFile(filename: "/usr/include/time.h", directory: "/data/download/cmake/cmake-master/Utilities/cmlibarchive/libarchive")
!217 = !{!218, !220}
!218 = !DIDerivedType(tag: DW_TAG_member, name: "tv_sec", scope: !215, file: !216, line: 122, baseType: !219, size: 64, align: 64)
!219 = !DIDerivedType(tag: DW_TAG_typedef, name: "__time_t", file: !41, line: 139, baseType: !42)
!220 = !DIDerivedType(tag: DW_TAG_member, name: "tv_nsec", scope: !215, file: !216, line: 123, baseType: !221, size: 64, align: 64, offset: 64)
!221 = !DIDerivedType(tag: DW_TAG_typedef, name: "__syscall_slong_t", file: !41, line: 175, baseType: !42)
!222 = !DIDerivedType(tag: DW_TAG_member, name: "st_mtim", scope: !193, file: !194, line: 92, baseType: !215, size: 128, align: 64, offset: 704)
!223 = !DIDerivedType(tag: DW_TAG_member, name: "st_ctim", scope: !193, file: !194, line: 93, baseType: !215, size: 128, align: 64, offset: 832)
!224 = !DIDerivedType(tag: DW_TAG_member, name: "__glibc_reserved", scope: !193, file: !194, line: 106, baseType: !225, size: 192, align: 64, offset: 960)
!225 = !DICompositeType(tag: DW_TAG_array_type, baseType: !221, size: 192, align: 64, elements: !182)
!226 = distinct !DISubprogram(name: "setup_mac_metadata", scope: !1, file: !1, line: 419, type: !227, isLocal: true, isDefinition: true, scopeLine: 421, flags: DIFlagPrototyped, isOptimized: false, variables: !2)
!227 = !DISubroutineType(types: !228)
!228 = !{!23, !4, !30, !229}
!229 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !23, size: 64, align: 64)
!230 = distinct !DISubprogram(name: "setup_acls", scope: !1, file: !1, line: 1403, type: !227, isLocal: true, isDefinition: true, scopeLine: 1405, flags: DIFlagPrototyped, isOptimized: false, variables: !2)
!231 = distinct !DISubprogram(name: "setup_xattrs", scope: !1, file: !1, line: 1738, type: !227, isLocal: true, isDefinition: true, scopeLine: 1740, flags: DIFlagPrototyped, isOptimized: false, variables: !2)
!232 = distinct !DISubprogram(name: "setup_sparse", scope: !1, file: !1, line: 1875, type: !227, isLocal: true, isDefinition: true, scopeLine: 1877, flags: DIFlagPrototyped, isOptimized: false, variables: !2)
!233 = distinct !DISubprogram(name: "setup_sparse_fiemap", scope: !1, file: !1, line: 1767, type: !227, isLocal: true, isDefinition: true, scopeLine: 1769, flags: DIFlagPrototyped, isOptimized: false, variables: !2)
!234 = !{i32 2, !"Dwarf Version", i32 4}
!235 = !{i32 2, !"Debug Info Version", i32 3}
!236 = !{!"clang version 3.8.0 (tags/RELEASE_380/final)"}
!237 = !DILocalVariable(name: "_a", arg: 1, scope: !188, file: !1, line: 149, type: !24)
!238 = !DIExpression()
!239 = !DILocation(line: 149, column: 51, scope: !188)
!240 = !DILocalVariable(name: "entry", arg: 2, scope: !188, file: !1, line: 150, type: !30)
!241 = !DILocation(line: 150, column: 27, scope: !188)
!242 = !DILocalVariable(name: "fd", arg: 3, scope: !188, file: !1, line: 151, type: !23)
!243 = !DILocation(line: 151, column: 9, scope: !188)
!244 = !DILocalVariable(name: "st", arg: 4, scope: !188, file: !1, line: 152, type: !191)
!245 = !DILocation(line: 152, column: 24, scope: !188)
!246 = !DILocalVariable(name: "a", scope: !188, file: !1, line: 154, type: !4)
!247 = !DILocation(line: 154, column: 28, scope: !188)
!248 = !DILocation(line: 154, column: 60, scope: !188)
!249 = !DILocation(line: 154, column: 32, scope: !188)
!250 = !DILocalVariable(name: "path", scope: !188, file: !1, line: 155, type: !80)
!251 = !DILocation(line: 155, column: 14, scope: !188)
!252 = !DILocalVariable(name: "name", scope: !188, file: !1, line: 155, type: !80)
!253 = !DILocation(line: 155, column: 21, scope: !188)
!254 = !DILocalVariable(name: "s", scope: !188, file: !1, line: 156, type: !193)
!255 = !DILocation(line: 156, column: 14, scope: !188)
!256 = !DILocalVariable(name: "initial_fd", scope: !188, file: !1, line: 157, type: !23)
!257 = !DILocation(line: 157, column: 6, scope: !188)
!258 = !DILocation(line: 157, column: 19, scope: !188)
!259 = !DILocalVariable(name: "r", scope: !188, file: !1, line: 158, type: !23)
!260 = !DILocation(line: 158, column: 6, scope: !188)
!261 = !DILocalVariable(name: "r1", scope: !188, file: !1, line: 158, type: !23)
!262 = !DILocation(line: 158, column: 9, scope: !188)
!263 = !DILocation(line: 160, column: 22, scope: !188)
!264 = !DILocation(line: 160, column: 2, scope: !188)
!265 = !DILocation(line: 161, column: 34, scope: !188)
!266 = !DILocation(line: 161, column: 9, scope: !188)
!267 = !DILocation(line: 161, column: 7, scope: !188)
!268 = !DILocation(line: 162, column: 6, scope: !269)
!269 = distinct !DILexicalBlock(scope: !188, file: !1, line: 162, column: 6)
!270 = !DILocation(line: 162, column: 11, scope: !269)
!271 = !DILocation(line: 162, column: 6, scope: !188)
!272 = !DILocation(line: 163, column: 33, scope: !269)
!273 = !DILocation(line: 163, column: 10, scope: !269)
!274 = !DILocation(line: 163, column: 8, scope: !269)
!275 = !DILocation(line: 163, column: 3, scope: !269)
!276 = !DILocation(line: 165, column: 6, scope: !277)
!277 = distinct !DILexicalBlock(scope: !188, file: !1, line: 165, column: 6)
!278 = !DILocation(line: 165, column: 9, scope: !277)
!279 = !DILocation(line: 165, column: 14, scope: !277)
!280 = !DILocation(line: 165, column: 6, scope: !188)
!281 = !DILocation(line: 166, column: 7, scope: !282)
!282 = distinct !DILexicalBlock(scope: !283, file: !1, line: 166, column: 7)
!283 = distinct !DILexicalBlock(scope: !277, file: !1, line: 165, column: 23)
!284 = !DILocation(line: 166, column: 10, scope: !282)
!285 = !DILocation(line: 166, column: 7, scope: !283)
!286 = !DILocation(line: 168, column: 8, scope: !287)
!287 = distinct !DILexicalBlock(scope: !288, file: !1, line: 168, column: 8)
!288 = distinct !DILexicalBlock(scope: !282, file: !1, line: 166, column: 19)
!289 = !DILocation(line: 168, column: 11, scope: !287)
!290 = !DILocation(line: 168, column: 8, scope: !288)
!291 = !DILocation(line: 169, column: 15, scope: !292)
!292 = distinct !DILexicalBlock(scope: !293, file: !1, line: 169, column: 9)
!293 = distinct !DILexicalBlock(scope: !287, file: !1, line: 168, column: 17)
!294 = !DILocation(line: 169, column: 9, scope: !292)
!295 = !DILocation(line: 169, column: 23, scope: !292)
!296 = !DILocation(line: 169, column: 9, scope: !293)
!297 = !DILocation(line: 170, column: 25, scope: !298)
!298 = distinct !DILexicalBlock(scope: !292, file: !1, line: 169, column: 29)
!299 = !DILocation(line: 170, column: 28, scope: !298)
!300 = !DILocation(line: 170, column: 37, scope: !298)
!301 = !DILocation(line: 170, column: 6, scope: !302)
!302 = !DILexicalBlockFile(scope: !298, file: !1, discriminator: 1)
!303 = !DILocation(line: 172, column: 6, scope: !298)
!304 = !DILocation(line: 174, column: 4, scope: !293)
!305 = !DILocation(line: 177, column: 9, scope: !306)
!306 = distinct !DILexicalBlock(scope: !287, file: !1, line: 177, column: 8)
!307 = !DILocation(line: 177, column: 12, scope: !306)
!308 = !DILocation(line: 177, column: 8, scope: !287)
!309 = !DILocation(line: 178, column: 15, scope: !310)
!310 = distinct !DILexicalBlock(scope: !311, file: !1, line: 178, column: 9)
!311 = distinct !DILexicalBlock(scope: !306, file: !1, line: 177, column: 29)
!312 = !DILocation(line: 178, column: 9, scope: !310)
!313 = !DILocation(line: 178, column: 25, scope: !310)
!314 = !DILocation(line: 178, column: 9, scope: !311)
!315 = !DILocation(line: 179, column: 25, scope: !316)
!316 = distinct !DILexicalBlock(scope: !310, file: !1, line: 178, column: 31)
!317 = !DILocation(line: 179, column: 28, scope: !316)
!318 = !DILocation(line: 179, column: 37, scope: !316)
!319 = !DILocation(line: 180, column: 28, scope: !316)
!320 = !DILocation(line: 179, column: 6, scope: !321)
!321 = !DILexicalBlockFile(scope: !316, file: !1, discriminator: 1)
!322 = !DILocation(line: 181, column: 6, scope: !316)
!323 = !DILocation(line: 183, column: 4, scope: !311)
!324 = !DILocation(line: 185, column: 13, scope: !325)
!325 = distinct !DILexicalBlock(scope: !306, file: !1, line: 185, column: 8)
!326 = !DILocation(line: 185, column: 8, scope: !325)
!327 = !DILocation(line: 185, column: 23, scope: !325)
!328 = !DILocation(line: 185, column: 8, scope: !306)
!329 = !DILocation(line: 186, column: 24, scope: !330)
!330 = distinct !DILexicalBlock(scope: !325, file: !1, line: 185, column: 29)
!331 = !DILocation(line: 186, column: 27, scope: !330)
!332 = !DILocation(line: 186, column: 36, scope: !330)
!333 = !DILocation(line: 187, column: 26, scope: !330)
!334 = !DILocation(line: 186, column: 5, scope: !335)
!335 = !DILexicalBlockFile(scope: !330, file: !1, discriminator: 1)
!336 = !DILocation(line: 188, column: 5, scope: !330)
!337 = !DILocation(line: 190, column: 7, scope: !288)
!338 = !DILocation(line: 191, column: 3, scope: !288)
!339 = !DILocation(line: 192, column: 27, scope: !283)
!340 = !DILocation(line: 192, column: 34, scope: !283)
!341 = !DILocation(line: 192, column: 3, scope: !283)
!342 = !DILocation(line: 193, column: 2, scope: !283)
!343 = !DILocation(line: 196, column: 33, scope: !188)
!344 = !DILocation(line: 196, column: 55, scope: !188)
!345 = !DILocation(line: 196, column: 37, scope: !188)
!346 = !DILocation(line: 196, column: 9, scope: !347)
!347 = !DILexicalBlockFile(scope: !188, file: !1, discriminator: 1)
!348 = !DILocation(line: 196, column: 7, scope: !188)
!349 = !DILocation(line: 197, column: 6, scope: !350)
!350 = distinct !DILexicalBlock(scope: !188, file: !1, line: 197, column: 6)
!351 = !DILocation(line: 197, column: 11, scope: !350)
!352 = !DILocation(line: 197, column: 6, scope: !188)
!353 = !DILocation(line: 198, column: 28, scope: !350)
!354 = !DILocation(line: 198, column: 35, scope: !350)
!355 = !DILocation(line: 198, column: 3, scope: !350)
!356 = !DILocation(line: 199, column: 33, scope: !188)
!357 = !DILocation(line: 199, column: 55, scope: !188)
!358 = !DILocation(line: 199, column: 37, scope: !188)
!359 = !DILocation(line: 199, column: 9, scope: !347)
!360 = !DILocation(line: 199, column: 7, scope: !188)
!361 = !DILocation(line: 200, column: 6, scope: !362)
!362 = distinct !DILexicalBlock(scope: !188, file: !1, line: 200, column: 6)
!363 = !DILocation(line: 200, column: 11, scope: !362)
!364 = !DILocation(line: 200, column: 6, scope: !188)
!365 = !DILocation(line: 201, column: 28, scope: !362)
!366 = !DILocation(line: 201, column: 35, scope: !362)
!367 = !DILocation(line: 201, column: 3, scope: !362)
!368 = !DILocation(line: 215, column: 7, scope: !369)
!369 = distinct !DILexicalBlock(scope: !188, file: !1, line: 215, column: 6)
!370 = !DILocation(line: 215, column: 10, scope: !369)
!371 = !DILocation(line: 215, column: 16, scope: !369)
!372 = !DILocation(line: 215, column: 46, scope: !369)
!373 = !DILocation(line: 215, column: 51, scope: !369)
!374 = !DILocation(line: 216, column: 7, scope: !369)
!375 = !DILocation(line: 216, column: 28, scope: !369)
!376 = !DILocation(line: 216, column: 31, scope: !377)
!377 = !DILexicalBlockFile(scope: !369, file: !1, discriminator: 1)
!378 = !DILocation(line: 215, column: 6, scope: !347)
!379 = !DILocation(line: 217, column: 7, scope: !380)
!380 = distinct !DILexicalBlock(scope: !381, file: !1, line: 217, column: 7)
!381 = distinct !DILexicalBlock(scope: !369, file: !1, line: 216, column: 54)
!382 = !DILocation(line: 217, column: 10, scope: !380)
!383 = !DILocation(line: 217, column: 7, scope: !381)
!384 = !DILocation(line: 218, column: 8, scope: !385)
!385 = distinct !DILexicalBlock(scope: !386, file: !1, line: 218, column: 8)
!386 = distinct !DILexicalBlock(scope: !380, file: !1, line: 217, column: 15)
!387 = !DILocation(line: 218, column: 11, scope: !385)
!388 = !DILocation(line: 218, column: 16, scope: !385)
!389 = !DILocation(line: 218, column: 8, scope: !386)
!390 = !DILocation(line: 219, column: 10, scope: !385)
!391 = !DILocation(line: 219, column: 13, scope: !385)
!392 = !DILocation(line: 219, column: 33, scope: !385)
!393 = !DILocation(line: 219, column: 36, scope: !385)
!394 = !DILocation(line: 219, column: 42, scope: !385)
!395 = !DILocation(line: 219, column: 8, scope: !385)
!396 = !DILocation(line: 219, column: 5, scope: !385)
!397 = !DILocation(line: 222, column: 15, scope: !385)
!398 = !DILocation(line: 222, column: 10, scope: !385)
!399 = !DILocation(line: 222, column: 8, scope: !385)
!400 = !DILocation(line: 224, column: 34, scope: !386)
!401 = !DILocation(line: 224, column: 4, scope: !386)
!402 = !DILocation(line: 225, column: 3, scope: !386)
!403 = !DILocation(line: 226, column: 7, scope: !404)
!404 = distinct !DILexicalBlock(scope: !381, file: !1, line: 226, column: 7)
!405 = !DILocation(line: 226, column: 10, scope: !404)
!406 = !DILocation(line: 226, column: 7, scope: !381)
!407 = !DILocalVariable(name: "stflags", scope: !408, file: !1, line: 227, type: !23)
!408 = distinct !DILexicalBlock(scope: !404, file: !1, line: 226, column: 16)
!409 = !DILocation(line: 227, column: 8, scope: !408)
!410 = !DILocation(line: 228, column: 14, scope: !408)
!411 = !DILocation(line: 228, column: 8, scope: !408)
!412 = !DILocation(line: 228, column: 6, scope: !408)
!413 = !DILocation(line: 235, column: 8, scope: !414)
!414 = distinct !DILexicalBlock(scope: !408, file: !1, line: 235, column: 8)
!415 = !DILocation(line: 235, column: 10, scope: !414)
!416 = !DILocation(line: 235, column: 15, scope: !414)
!417 = !DILocation(line: 235, column: 18, scope: !418)
!418 = !DILexicalBlockFile(scope: !414, file: !1, discriminator: 1)
!419 = !DILocation(line: 235, column: 26, scope: !418)
!420 = !DILocation(line: 235, column: 8, scope: !418)
!421 = !DILocation(line: 236, column: 30, scope: !414)
!422 = !DILocation(line: 236, column: 37, scope: !414)
!423 = !DILocation(line: 236, column: 5, scope: !414)
!424 = !DILocation(line: 237, column: 3, scope: !408)
!425 = !DILocation(line: 238, column: 2, scope: !381)
!426 = !DILocation(line: 242, column: 6, scope: !427)
!427 = distinct !DILexicalBlock(scope: !188, file: !1, line: 242, column: 6)
!428 = !DILocation(line: 242, column: 6, scope: !188)
!429 = !DILocalVariable(name: "linkbuffer_len", scope: !430, file: !1, line: 243, type: !45)
!430 = distinct !DILexicalBlock(scope: !427, file: !1, line: 242, column: 28)
!431 = !DILocation(line: 243, column: 10, scope: !430)
!432 = !DILocation(line: 243, column: 27, scope: !430)
!433 = !DILocation(line: 243, column: 31, scope: !430)
!434 = !DILocation(line: 243, column: 39, scope: !430)
!435 = !DILocalVariable(name: "linkbuffer", scope: !430, file: !1, line: 244, type: !95)
!436 = !DILocation(line: 244, column: 9, scope: !430)
!437 = !DILocalVariable(name: "lnklen", scope: !430, file: !1, line: 245, type: !23)
!438 = !DILocation(line: 245, column: 7, scope: !430)
!439 = !DILocation(line: 247, column: 23, scope: !430)
!440 = !DILocation(line: 247, column: 16, scope: !430)
!441 = !DILocation(line: 247, column: 14, scope: !430)
!442 = !DILocation(line: 248, column: 7, scope: !443)
!443 = distinct !DILexicalBlock(scope: !430, file: !1, line: 248, column: 7)
!444 = !DILocation(line: 248, column: 18, scope: !443)
!445 = !DILocation(line: 248, column: 7, scope: !430)
!446 = !DILocation(line: 249, column: 23, scope: !447)
!447 = distinct !DILexicalBlock(scope: !443, file: !1, line: 248, column: 27)
!448 = !DILocation(line: 249, column: 26, scope: !447)
!449 = !DILocation(line: 249, column: 4, scope: !447)
!450 = !DILocation(line: 251, column: 4, scope: !447)
!451 = !DILocation(line: 253, column: 7, scope: !452)
!452 = distinct !DILexicalBlock(scope: !430, file: !1, line: 253, column: 7)
!453 = !DILocation(line: 253, column: 10, scope: !452)
!454 = !DILocation(line: 253, column: 15, scope: !452)
!455 = !DILocation(line: 253, column: 7, scope: !430)
!456 = !DILocation(line: 255, column: 24, scope: !457)
!457 = distinct !DILexicalBlock(scope: !452, file: !1, line: 253, column: 24)
!458 = !DILocation(line: 255, column: 27, scope: !457)
!459 = !DILocation(line: 255, column: 47, scope: !457)
!460 = !DILocation(line: 255, column: 50, scope: !457)
!461 = !DILocation(line: 256, column: 8, scope: !457)
!462 = !DILocation(line: 256, column: 14, scope: !457)
!463 = !DILocation(line: 256, column: 26, scope: !457)
!464 = !DILocation(line: 255, column: 13, scope: !465)
!465 = !DILexicalBlockFile(scope: !457, file: !1, discriminator: 1)
!466 = !DILocation(line: 255, column: 13, scope: !457)
!467 = !DILocation(line: 255, column: 11, scope: !457)
!468 = !DILocation(line: 266, column: 3, scope: !457)
!469 = !DILocation(line: 267, column: 22, scope: !452)
!470 = !DILocation(line: 267, column: 28, scope: !452)
!471 = !DILocation(line: 267, column: 40, scope: !452)
!472 = !DILocation(line: 267, column: 13, scope: !452)
!473 = !DILocation(line: 267, column: 11, scope: !452)
!474 = !DILocation(line: 268, column: 7, scope: !475)
!475 = distinct !DILexicalBlock(scope: !430, file: !1, line: 268, column: 7)
!476 = !DILocation(line: 268, column: 14, scope: !475)
!477 = !DILocation(line: 268, column: 7, scope: !430)
!478 = !DILocation(line: 269, column: 23, scope: !479)
!479 = distinct !DILexicalBlock(scope: !475, file: !1, line: 268, column: 19)
!480 = !DILocation(line: 269, column: 26, scope: !479)
!481 = !DILocation(line: 269, column: 35, scope: !479)
!482 = !DILocation(line: 269, column: 4, scope: !483)
!483 = !DILexicalBlockFile(scope: !479, file: !1, discriminator: 1)
!484 = !DILocation(line: 271, column: 9, scope: !479)
!485 = !DILocation(line: 271, column: 4, scope: !479)
!486 = !DILocation(line: 272, column: 4, scope: !479)
!487 = !DILocation(line: 274, column: 14, scope: !430)
!488 = !DILocation(line: 274, column: 3, scope: !430)
!489 = !DILocation(line: 274, column: 22, scope: !430)
!490 = !DILocation(line: 275, column: 29, scope: !430)
!491 = !DILocation(line: 275, column: 36, scope: !430)
!492 = !DILocation(line: 275, column: 3, scope: !430)
!493 = !DILocation(line: 276, column: 8, scope: !430)
!494 = !DILocation(line: 276, column: 3, scope: !430)
!495 = !DILocation(line: 277, column: 2, scope: !430)
!496 = !DILocation(line: 280, column: 4, scope: !188)
!497 = !DILocation(line: 281, column: 7, scope: !498)
!498 = distinct !DILexicalBlock(scope: !188, file: !1, line: 281, column: 6)
!499 = !DILocation(line: 281, column: 10, scope: !498)
!500 = !DILocation(line: 281, column: 16, scope: !498)
!501 = !DILocation(line: 281, column: 43, scope: !498)
!502 = !DILocation(line: 281, column: 6, scope: !188)
!503 = !DILocation(line: 282, column: 18, scope: !498)
!504 = !DILocation(line: 282, column: 21, scope: !498)
!505 = !DILocation(line: 282, column: 7, scope: !498)
!506 = !DILocation(line: 282, column: 5, scope: !498)
!507 = !DILocation(line: 282, column: 3, scope: !498)
!508 = !DILocation(line: 283, column: 7, scope: !509)
!509 = distinct !DILexicalBlock(scope: !188, file: !1, line: 283, column: 6)
!510 = !DILocation(line: 283, column: 10, scope: !509)
!511 = !DILocation(line: 283, column: 16, scope: !509)
!512 = !DILocation(line: 283, column: 45, scope: !509)
!513 = !DILocation(line: 283, column: 6, scope: !188)
!514 = !DILocation(line: 284, column: 21, scope: !515)
!515 = distinct !DILexicalBlock(scope: !509, file: !1, line: 283, column: 51)
!516 = !DILocation(line: 284, column: 24, scope: !515)
!517 = !DILocation(line: 284, column: 8, scope: !515)
!518 = !DILocation(line: 284, column: 6, scope: !515)
!519 = !DILocation(line: 285, column: 7, scope: !520)
!520 = distinct !DILexicalBlock(scope: !515, file: !1, line: 285, column: 7)
!521 = !DILocation(line: 285, column: 12, scope: !520)
!522 = !DILocation(line: 285, column: 10, scope: !520)
!523 = !DILocation(line: 285, column: 7, scope: !515)
!524 = !DILocation(line: 286, column: 8, scope: !520)
!525 = !DILocation(line: 286, column: 6, scope: !520)
!526 = !DILocation(line: 286, column: 4, scope: !520)
!527 = !DILocation(line: 287, column: 2, scope: !515)
!528 = !DILocation(line: 288, column: 6, scope: !529)
!529 = distinct !DILexicalBlock(scope: !188, file: !1, line: 288, column: 6)
!530 = !DILocation(line: 288, column: 9, scope: !529)
!531 = !DILocation(line: 288, column: 15, scope: !529)
!532 = !DILocation(line: 288, column: 6, scope: !188)
!533 = !DILocation(line: 289, column: 27, scope: !534)
!534 = distinct !DILexicalBlock(scope: !529, file: !1, line: 288, column: 48)
!535 = !DILocation(line: 289, column: 30, scope: !534)
!536 = !DILocation(line: 289, column: 8, scope: !534)
!537 = !DILocation(line: 289, column: 6, scope: !534)
!538 = !DILocation(line: 290, column: 7, scope: !539)
!539 = distinct !DILexicalBlock(scope: !534, file: !1, line: 290, column: 7)
!540 = !DILocation(line: 290, column: 12, scope: !539)
!541 = !DILocation(line: 290, column: 10, scope: !539)
!542 = !DILocation(line: 290, column: 7, scope: !534)
!543 = !DILocation(line: 291, column: 8, scope: !539)
!544 = !DILocation(line: 291, column: 6, scope: !539)
!545 = !DILocation(line: 291, column: 4, scope: !539)
!546 = !DILocation(line: 292, column: 2, scope: !534)
!547 = !DILocation(line: 293, column: 20, scope: !188)
!548 = !DILocation(line: 293, column: 23, scope: !188)
!549 = !DILocation(line: 293, column: 7, scope: !188)
!550 = !DILocation(line: 293, column: 5, scope: !188)
!551 = !DILocation(line: 294, column: 6, scope: !552)
!552 = distinct !DILexicalBlock(scope: !188, file: !1, line: 294, column: 6)
!553 = !DILocation(line: 294, column: 11, scope: !552)
!554 = !DILocation(line: 294, column: 9, scope: !552)
!555 = !DILocation(line: 294, column: 6, scope: !188)
!556 = !DILocation(line: 295, column: 7, scope: !552)
!557 = !DILocation(line: 295, column: 5, scope: !552)
!558 = !DILocation(line: 295, column: 3, scope: !552)
!559 = !DILocation(line: 298, column: 6, scope: !560)
!560 = distinct !DILexicalBlock(scope: !188, file: !1, line: 298, column: 6)
!561 = !DILocation(line: 298, column: 20, scope: !560)
!562 = !DILocation(line: 298, column: 17, scope: !560)
!563 = !DILocation(line: 298, column: 6, scope: !188)
!564 = !DILocation(line: 299, column: 9, scope: !560)
!565 = !DILocation(line: 299, column: 3, scope: !560)
!566 = !DILocation(line: 300, column: 10, scope: !188)
!567 = !DILocation(line: 300, column: 2, scope: !188)
!568 = !DILocation(line: 301, column: 1, scope: !188)
!569 = !DILocalVariable(name: "a", arg: 1, scope: !230, file: !1, line: 1403, type: !4)
!570 = !DILocation(line: 1403, column: 38, scope: !230)
!571 = !DILocalVariable(name: "entry", arg: 2, scope: !230, file: !1, line: 1404, type: !30)
!572 = !DILocation(line: 1404, column: 27, scope: !230)
!573 = !DILocalVariable(name: "fd", arg: 3, scope: !230, file: !1, line: 1404, type: !229)
!574 = !DILocation(line: 1404, column: 39, scope: !230)
!575 = !DILocation(line: 1406, column: 8, scope: !230)
!576 = !DILocation(line: 1407, column: 8, scope: !230)
!577 = !DILocation(line: 1408, column: 8, scope: !230)
!578 = !DILocation(line: 1409, column: 2, scope: !230)
!579 = !DILocalVariable(name: "a", arg: 1, scope: !231, file: !1, line: 1738, type: !4)
!580 = !DILocation(line: 1738, column: 40, scope: !231)
!581 = !DILocalVariable(name: "entry", arg: 2, scope: !231, file: !1, line: 1739, type: !30)
!582 = !DILocation(line: 1739, column: 27, scope: !231)
!583 = !DILocalVariable(name: "fd", arg: 3, scope: !231, file: !1, line: 1739, type: !229)
!584 = !DILocation(line: 1739, column: 39, scope: !231)
!585 = !DILocation(line: 1741, column: 8, scope: !231)
!586 = !DILocation(line: 1742, column: 8, scope: !231)
!587 = !DILocation(line: 1743, column: 8, scope: !231)
!588 = !DILocation(line: 1744, column: 2, scope: !231)
!589 = !DILocalVariable(name: "a", arg: 1, scope: !226, file: !1, line: 419, type: !4)
!590 = !DILocation(line: 419, column: 46, scope: !226)
!591 = !DILocalVariable(name: "entry", arg: 2, scope: !226, file: !1, line: 420, type: !30)
!592 = !DILocation(line: 420, column: 27, scope: !226)
!593 = !DILocalVariable(name: "fd", arg: 3, scope: !226, file: !1, line: 420, type: !229)
!594 = !DILocation(line: 420, column: 39, scope: !226)
!595 = !DILocation(line: 422, column: 8, scope: !226)
!596 = !DILocation(line: 423, column: 8, scope: !226)
!597 = !DILocation(line: 424, column: 8, scope: !226)
!598 = !DILocation(line: 425, column: 2, scope: !226)
!599 = !DILocalVariable(name: "a", arg: 1, scope: !232, file: !1, line: 1875, type: !4)
!600 = !DILocation(line: 1875, column: 40, scope: !232)
!601 = !DILocalVariable(name: "entry", arg: 2, scope: !232, file: !1, line: 1876, type: !30)
!602 = !DILocation(line: 1876, column: 27, scope: !232)
!603 = !DILocalVariable(name: "fd", arg: 3, scope: !232, file: !1, line: 1876, type: !229)
!604 = !DILocation(line: 1876, column: 39, scope: !232)
!605 = !DILocalVariable(name: "size", scope: !232, file: !1, line: 1878, type: !52)
!606 = !DILocation(line: 1878, column: 10, scope: !232)
!607 = !DILocalVariable(name: "initial_off", scope: !232, file: !1, line: 1879, type: !152)
!608 = !DILocation(line: 1879, column: 8, scope: !232)
!609 = !DILocalVariable(name: "off_s", scope: !232, file: !1, line: 1880, type: !152)
!610 = !DILocation(line: 1880, column: 8, scope: !232)
!611 = !DILocalVariable(name: "off_e", scope: !232, file: !1, line: 1880, type: !152)
!612 = !DILocation(line: 1880, column: 15, scope: !232)
!613 = !DILocalVariable(name: "exit_sts", scope: !232, file: !1, line: 1881, type: !23)
!614 = !DILocation(line: 1881, column: 6, scope: !232)
!615 = !DILocalVariable(name: "check_fully_sparse", scope: !232, file: !1, line: 1882, type: !23)
!616 = !DILocation(line: 1882, column: 6, scope: !232)
!617 = !DILocation(line: 1884, column: 29, scope: !618)
!618 = distinct !DILexicalBlock(scope: !232, file: !1, line: 1884, column: 6)
!619 = !DILocation(line: 1884, column: 6, scope: !618)
!620 = !DILocation(line: 1884, column: 36, scope: !618)
!621 = !DILocation(line: 1885, column: 6, scope: !618)
!622 = !DILocation(line: 1885, column: 28, scope: !623)
!623 = !DILexicalBlockFile(scope: !618, file: !1, discriminator: 1)
!624 = !DILocation(line: 1885, column: 9, scope: !623)
!625 = !DILocation(line: 1885, column: 35, scope: !623)
!626 = !DILocation(line: 1886, column: 6, scope: !618)
!627 = !DILocation(line: 1886, column: 32, scope: !623)
!628 = !DILocation(line: 1886, column: 9, scope: !623)
!629 = !DILocation(line: 1886, column: 39, scope: !623)
!630 = !DILocation(line: 1884, column: 6, scope: !631)
!631 = !DILexicalBlockFile(scope: !232, file: !1, discriminator: 1)
!632 = !DILocation(line: 1887, column: 3, scope: !618)
!633 = !DILocation(line: 1890, column: 7, scope: !634)
!634 = distinct !DILexicalBlock(scope: !232, file: !1, line: 1890, column: 6)
!635 = !DILocation(line: 1890, column: 6, scope: !634)
!636 = !DILocation(line: 1890, column: 10, scope: !634)
!637 = !DILocation(line: 1890, column: 14, scope: !634)
!638 = !DILocation(line: 1890, column: 17, scope: !639)
!639 = !DILexicalBlockFile(scope: !634, file: !1, discriminator: 1)
!640 = !DILocation(line: 1890, column: 20, scope: !639)
!641 = !DILocation(line: 1890, column: 25, scope: !639)
!642 = !DILocation(line: 1890, column: 6, scope: !639)
!643 = !DILocalVariable(name: "path", scope: !644, file: !1, line: 1891, type: !80)
!644 = distinct !DILexicalBlock(scope: !634, file: !1, line: 1890, column: 34)
!645 = !DILocation(line: 1891, column: 15, scope: !644)
!646 = !DILocation(line: 1893, column: 35, scope: !644)
!647 = !DILocation(line: 1893, column: 10, scope: !644)
!648 = !DILocation(line: 1893, column: 8, scope: !644)
!649 = !DILocation(line: 1894, column: 7, scope: !650)
!650 = distinct !DILexicalBlock(scope: !644, file: !1, line: 1894, column: 7)
!651 = !DILocation(line: 1894, column: 12, scope: !650)
!652 = !DILocation(line: 1894, column: 7, scope: !644)
!653 = !DILocation(line: 1895, column: 34, scope: !650)
!654 = !DILocation(line: 1895, column: 11, scope: !650)
!655 = !DILocation(line: 1895, column: 9, scope: !650)
!656 = !DILocation(line: 1895, column: 4, scope: !650)
!657 = !DILocation(line: 1896, column: 9, scope: !644)
!658 = !DILocation(line: 1896, column: 12, scope: !644)
!659 = !DILocation(line: 1896, column: 32, scope: !644)
!660 = !DILocation(line: 1896, column: 35, scope: !644)
!661 = !DILocation(line: 1896, column: 41, scope: !644)
!662 = !DILocation(line: 1896, column: 4, scope: !644)
!663 = !DILocation(line: 1896, column: 7, scope: !644)
!664 = !DILocation(line: 1898, column: 8, scope: !665)
!665 = distinct !DILexicalBlock(scope: !644, file: !1, line: 1898, column: 7)
!666 = !DILocation(line: 1898, column: 7, scope: !665)
!667 = !DILocation(line: 1898, column: 11, scope: !665)
!668 = !DILocation(line: 1898, column: 7, scope: !644)
!669 = !DILocation(line: 1899, column: 23, scope: !670)
!670 = distinct !DILexicalBlock(scope: !665, file: !1, line: 1898, column: 16)
!671 = !DILocation(line: 1899, column: 26, scope: !670)
!672 = !DILocation(line: 1899, column: 35, scope: !670)
!673 = !DILocation(line: 1900, column: 27, scope: !670)
!674 = !DILocation(line: 1899, column: 4, scope: !675)
!675 = !DILexicalBlockFile(scope: !670, file: !1, discriminator: 1)
!676 = !DILocation(line: 1901, column: 4, scope: !670)
!677 = !DILocation(line: 1903, column: 2, scope: !644)
!678 = !DILocation(line: 1905, column: 7, scope: !679)
!679 = distinct !DILexicalBlock(scope: !232, file: !1, line: 1905, column: 6)
!680 = !DILocation(line: 1905, column: 6, scope: !679)
!681 = !DILocation(line: 1905, column: 10, scope: !679)
!682 = !DILocation(line: 1905, column: 6, scope: !232)
!683 = !DILocation(line: 1910, column: 24, scope: !684)
!684 = distinct !DILexicalBlock(scope: !679, file: !1, line: 1905, column: 16)
!685 = !DILocation(line: 1910, column: 23, scope: !684)
!686 = !DILocation(line: 1910, column: 17, scope: !684)
!687 = !DILocation(line: 1910, column: 15, scope: !684)
!688 = !DILocation(line: 1911, column: 7, scope: !689)
!689 = distinct !DILexicalBlock(scope: !684, file: !1, line: 1911, column: 7)
!690 = !DILocation(line: 1911, column: 19, scope: !689)
!691 = !DILocation(line: 1911, column: 7, scope: !684)
!692 = !DILocation(line: 1912, column: 11, scope: !689)
!693 = !DILocation(line: 1912, column: 10, scope: !689)
!694 = !DILocation(line: 1912, column: 4, scope: !689)
!695 = !DILocation(line: 1913, column: 2, scope: !684)
!696 = !DILocalVariable(name: "path", scope: !697, file: !1, line: 1914, type: !80)
!697 = distinct !DILexicalBlock(scope: !679, file: !1, line: 1913, column: 9)
!698 = !DILocation(line: 1914, column: 15, scope: !697)
!699 = !DILocation(line: 1916, column: 35, scope: !697)
!700 = !DILocation(line: 1916, column: 10, scope: !697)
!701 = !DILocation(line: 1916, column: 8, scope: !697)
!702 = !DILocation(line: 1917, column: 7, scope: !703)
!703 = distinct !DILexicalBlock(scope: !697, file: !1, line: 1917, column: 7)
!704 = !DILocation(line: 1917, column: 12, scope: !703)
!705 = !DILocation(line: 1917, column: 7, scope: !697)
!706 = !DILocation(line: 1918, column: 34, scope: !703)
!707 = !DILocation(line: 1918, column: 11, scope: !703)
!708 = !DILocation(line: 1918, column: 9, scope: !703)
!709 = !DILocation(line: 1918, column: 4, scope: !703)
!710 = !DILocation(line: 1924, column: 14, scope: !697)
!711 = !DILocation(line: 1924, column: 9, scope: !697)
!712 = !DILocation(line: 1924, column: 4, scope: !697)
!713 = !DILocation(line: 1924, column: 7, scope: !697)
!714 = !DILocation(line: 1925, column: 8, scope: !715)
!715 = distinct !DILexicalBlock(scope: !697, file: !1, line: 1925, column: 7)
!716 = !DILocation(line: 1925, column: 7, scope: !715)
!717 = !DILocation(line: 1925, column: 11, scope: !715)
!718 = !DILocation(line: 1925, column: 7, scope: !697)
!719 = !DILocation(line: 1926, column: 23, scope: !720)
!720 = distinct !DILexicalBlock(scope: !715, file: !1, line: 1925, column: 16)
!721 = !DILocation(line: 1926, column: 26, scope: !720)
!722 = !DILocation(line: 1926, column: 35, scope: !720)
!723 = !DILocation(line: 1927, column: 27, scope: !720)
!724 = !DILocation(line: 1926, column: 4, scope: !725)
!725 = !DILexicalBlockFile(scope: !720, file: !1, discriminator: 1)
!726 = !DILocation(line: 1928, column: 4, scope: !720)
!727 = !DILocation(line: 1930, column: 34, scope: !697)
!728 = !DILocation(line: 1930, column: 33, scope: !697)
!729 = !DILocation(line: 1930, column: 3, scope: !697)
!730 = !DILocation(line: 1931, column: 15, scope: !697)
!731 = !DILocation(line: 1936, column: 17, scope: !232)
!732 = !DILocation(line: 1936, column: 16, scope: !232)
!733 = !DILocation(line: 1936, column: 10, scope: !232)
!734 = !DILocation(line: 1936, column: 8, scope: !232)
!735 = !DILocation(line: 1937, column: 6, scope: !736)
!736 = distinct !DILexicalBlock(scope: !232, file: !1, line: 1937, column: 6)
!737 = !DILocation(line: 1937, column: 12, scope: !736)
!738 = !DILocation(line: 1937, column: 6, scope: !232)
!739 = !DILocation(line: 1939, column: 30, scope: !736)
!740 = !DILocation(line: 1939, column: 33, scope: !736)
!741 = !DILocation(line: 1939, column: 40, scope: !736)
!742 = !DILocation(line: 1939, column: 10, scope: !736)
!743 = !DILocation(line: 1939, column: 3, scope: !736)
!744 = !DILocation(line: 1943, column: 11, scope: !745)
!745 = distinct !DILexicalBlock(scope: !736, file: !1, line: 1943, column: 11)
!746 = !DILocation(line: 1943, column: 17, scope: !745)
!747 = !DILocation(line: 1943, column: 11, scope: !736)
!748 = !DILocation(line: 1944, column: 10, scope: !745)
!749 = !DILocation(line: 1944, column: 9, scope: !745)
!750 = !DILocation(line: 1944, column: 3, scope: !745)
!751 = !DILocation(line: 1947, column: 8, scope: !232)
!752 = !DILocation(line: 1948, column: 28, scope: !232)
!753 = !DILocation(line: 1948, column: 9, scope: !232)
!754 = !DILocation(line: 1948, column: 7, scope: !232)
!755 = !DILocation(line: 1949, column: 2, scope: !232)
!756 = !DILocation(line: 1949, column: 9, scope: !631)
!757 = !DILocation(line: 1949, column: 17, scope: !631)
!758 = !DILocation(line: 1949, column: 15, scope: !631)
!759 = !DILocation(line: 1949, column: 2, scope: !631)
!760 = !DILocation(line: 1950, column: 18, scope: !761)
!761 = distinct !DILexicalBlock(scope: !232, file: !1, line: 1949, column: 23)
!762 = !DILocation(line: 1950, column: 17, scope: !761)
!763 = !DILocation(line: 1950, column: 22, scope: !761)
!764 = !DILocation(line: 1950, column: 11, scope: !761)
!765 = !DILocation(line: 1950, column: 9, scope: !761)
!766 = !DILocation(line: 1951, column: 7, scope: !767)
!767 = distinct !DILexicalBlock(scope: !761, file: !1, line: 1951, column: 7)
!768 = !DILocation(line: 1951, column: 13, scope: !767)
!769 = !DILocation(line: 1951, column: 7, scope: !761)
!770 = !DILocation(line: 1952, column: 8, scope: !771)
!771 = distinct !DILexicalBlock(scope: !772, file: !1, line: 1952, column: 8)
!772 = distinct !DILexicalBlock(scope: !767, file: !1, line: 1951, column: 27)
!773 = !DILocation(line: 1952, column: 14, scope: !771)
!774 = !DILocation(line: 1952, column: 8, scope: !772)
!775 = !DILocation(line: 1954, column: 36, scope: !776)
!776 = distinct !DILexicalBlock(scope: !777, file: !1, line: 1954, column: 9)
!777 = distinct !DILexicalBlock(scope: !771, file: !1, line: 1952, column: 24)
!778 = !DILocation(line: 1954, column: 9, scope: !776)
!779 = !DILocation(line: 1954, column: 43, scope: !776)
!780 = !DILocation(line: 1954, column: 9, scope: !777)
!781 = !DILocation(line: 1956, column: 25, scope: !782)
!782 = distinct !DILexicalBlock(scope: !776, file: !1, line: 1954, column: 49)
!783 = !DILocation(line: 1957, column: 5, scope: !782)
!784 = !DILocation(line: 1958, column: 5, scope: !777)
!785 = !DILocation(line: 1960, column: 23, scope: !772)
!786 = !DILocation(line: 1960, column: 26, scope: !772)
!787 = !DILocation(line: 1960, column: 35, scope: !772)
!788 = !DILocation(line: 1960, column: 4, scope: !789)
!789 = !DILexicalBlockFile(scope: !772, file: !1, discriminator: 1)
!790 = !DILocation(line: 1962, column: 13, scope: !772)
!791 = !DILocation(line: 1963, column: 4, scope: !772)
!792 = !DILocation(line: 1965, column: 18, scope: !761)
!793 = !DILocation(line: 1965, column: 17, scope: !761)
!794 = !DILocation(line: 1965, column: 22, scope: !761)
!795 = !DILocation(line: 1965, column: 11, scope: !761)
!796 = !DILocation(line: 1965, column: 9, scope: !761)
!797 = !DILocation(line: 1966, column: 7, scope: !798)
!798 = distinct !DILexicalBlock(scope: !761, file: !1, line: 1966, column: 7)
!799 = !DILocation(line: 1966, column: 13, scope: !798)
!800 = !DILocation(line: 1966, column: 7, scope: !761)
!801 = !DILocation(line: 1967, column: 8, scope: !802)
!802 = distinct !DILexicalBlock(scope: !803, file: !1, line: 1967, column: 8)
!803 = distinct !DILexicalBlock(scope: !798, file: !1, line: 1966, column: 27)
!804 = !DILocation(line: 1967, column: 14, scope: !802)
!805 = !DILocation(line: 1967, column: 8, scope: !803)
!806 = !DILocation(line: 1968, column: 20, scope: !807)
!807 = distinct !DILexicalBlock(scope: !802, file: !1, line: 1967, column: 24)
!808 = !DILocation(line: 1968, column: 19, scope: !807)
!809 = !DILocation(line: 1968, column: 13, scope: !807)
!810 = !DILocation(line: 1968, column: 11, scope: !807)
!811 = !DILocation(line: 1969, column: 9, scope: !812)
!812 = distinct !DILexicalBlock(scope: !807, file: !1, line: 1969, column: 9)
!813 = !DILocation(line: 1969, column: 15, scope: !812)
!814 = !DILocation(line: 1969, column: 9, scope: !807)
!815 = !DILocation(line: 1970, column: 6, scope: !812)
!816 = !DILocation(line: 1971, column: 4, scope: !807)
!817 = !DILocation(line: 1972, column: 23, scope: !803)
!818 = !DILocation(line: 1972, column: 26, scope: !803)
!819 = !DILocation(line: 1972, column: 35, scope: !803)
!820 = !DILocation(line: 1972, column: 4, scope: !821)
!821 = !DILexicalBlockFile(scope: !803, file: !1, discriminator: 1)
!822 = !DILocation(line: 1974, column: 13, scope: !803)
!823 = !DILocation(line: 1975, column: 4, scope: !803)
!824 = !DILocation(line: 1977, column: 7, scope: !825)
!825 = distinct !DILexicalBlock(scope: !761, file: !1, line: 1977, column: 7)
!826 = !DILocation(line: 1977, column: 13, scope: !825)
!827 = !DILocation(line: 1977, column: 18, scope: !825)
!828 = !DILocation(line: 1977, column: 21, scope: !829)
!829 = !DILexicalBlockFile(scope: !825, file: !1, discriminator: 1)
!830 = !DILocation(line: 1977, column: 30, scope: !829)
!831 = !DILocation(line: 1977, column: 27, scope: !829)
!832 = !DILocation(line: 1977, column: 7, scope: !829)
!833 = !DILocation(line: 1978, column: 4, scope: !825)
!834 = !DILocation(line: 1979, column: 34, scope: !761)
!835 = !DILocation(line: 1979, column: 41, scope: !761)
!836 = !DILocation(line: 1980, column: 4, scope: !761)
!837 = !DILocation(line: 1980, column: 12, scope: !761)
!838 = !DILocation(line: 1980, column: 10, scope: !761)
!839 = !DILocation(line: 1979, column: 3, scope: !761)
!840 = !DILocation(line: 1981, column: 11, scope: !761)
!841 = !DILocation(line: 1981, column: 9, scope: !761)
!842 = !DILocation(line: 1949, column: 2, scope: !843)
!843 = !DILexicalBlockFile(scope: !232, file: !1, discriminator: 2)
!844 = !DILocation(line: 1984, column: 6, scope: !845)
!845 = distinct !DILexicalBlock(scope: !232, file: !1, line: 1984, column: 6)
!846 = !DILocation(line: 1984, column: 6, scope: !232)
!847 = !DILocation(line: 1985, column: 14, scope: !848)
!848 = distinct !DILexicalBlock(scope: !849, file: !1, line: 1985, column: 7)
!849 = distinct !DILexicalBlock(scope: !845, file: !1, line: 1984, column: 26)
!850 = !DILocation(line: 1985, column: 13, scope: !848)
!851 = !DILocation(line: 1985, column: 7, scope: !848)
!852 = !DILocation(line: 1985, column: 32, scope: !848)
!853 = !DILocation(line: 1985, column: 37, scope: !848)
!854 = !DILocation(line: 1986, column: 11, scope: !848)
!855 = !DILocation(line: 1986, column: 10, scope: !848)
!856 = !DILocation(line: 1986, column: 4, scope: !848)
!857 = !DILocation(line: 1986, column: 31, scope: !848)
!858 = !DILocation(line: 1986, column: 28, scope: !848)
!859 = !DILocation(line: 1985, column: 7, scope: !860)
!860 = !DILexicalBlockFile(scope: !849, file: !1, discriminator: 1)
!861 = !DILocation(line: 1988, column: 35, scope: !862)
!862 = distinct !DILexicalBlock(scope: !848, file: !1, line: 1986, column: 37)
!863 = !DILocation(line: 1988, column: 4, scope: !862)
!864 = !DILocation(line: 1989, column: 3, scope: !862)
!865 = !DILocation(line: 1990, column: 2, scope: !849)
!866 = !DILocation(line: 1984, column: 6, scope: !867)
!867 = !DILexicalBlockFile(scope: !845, file: !1, discriminator: 1)
!868 = !DILocation(line: 1992, column: 9, scope: !232)
!869 = !DILocation(line: 1992, column: 8, scope: !232)
!870 = !DILocation(line: 1992, column: 13, scope: !232)
!871 = !DILocation(line: 1992, column: 2, scope: !232)
!872 = !DILocation(line: 1993, column: 10, scope: !232)
!873 = !DILocation(line: 1993, column: 2, scope: !232)
!874 = !DILocation(line: 1994, column: 1, scope: !232)
!875 = !DILocalVariable(name: "a", arg: 1, scope: !233, file: !1, line: 1767, type: !4)
!876 = !DILocation(line: 1767, column: 47, scope: !233)
!877 = !DILocalVariable(name: "entry", arg: 2, scope: !233, file: !1, line: 1768, type: !30)
!878 = !DILocation(line: 1768, column: 27, scope: !233)
!879 = !DILocalVariable(name: "fd", arg: 3, scope: !233, file: !1, line: 1768, type: !229)
!880 = !DILocation(line: 1768, column: 39, scope: !233)
!881 = !DILocalVariable(name: "buff", scope: !233, file: !1, line: 1770, type: !882)
!882 = !DICompositeType(tag: DW_TAG_array_type, baseType: !82, size: 32768, align: 8, elements: !883)
!883 = !{!884}
!884 = !DISubrange(count: 4096)
!885 = !DILocation(line: 1770, column: 7, scope: !233)
!886 = !DILocalVariable(name: "fm", scope: !233, file: !1, line: 1771, type: !154)
!887 = !DILocation(line: 1771, column: 17, scope: !233)
!888 = !DILocalVariable(name: "fe", scope: !233, file: !1, line: 1772, type: !889)
!889 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !170, size: 64, align: 64)
!890 = !DILocation(line: 1772, column: 24, scope: !233)
!891 = !DILocalVariable(name: "size", scope: !233, file: !1, line: 1773, type: !52)
!892 = !DILocation(line: 1773, column: 10, scope: !233)
!893 = !DILocalVariable(name: "count", scope: !233, file: !1, line: 1774, type: !23)
!894 = !DILocation(line: 1774, column: 6, scope: !233)
!895 = !DILocalVariable(name: "do_fiemap", scope: !233, file: !1, line: 1774, type: !23)
!896 = !DILocation(line: 1774, column: 13, scope: !233)
!897 = !DILocalVariable(name: "iters", scope: !233, file: !1, line: 1774, type: !23)
!898 = !DILocation(line: 1774, column: 24, scope: !233)
!899 = !DILocalVariable(name: "exit_sts", scope: !233, file: !1, line: 1775, type: !23)
!900 = !DILocation(line: 1775, column: 6, scope: !233)
!901 = !DILocation(line: 1777, column: 29, scope: !902)
!902 = distinct !DILexicalBlock(scope: !233, file: !1, line: 1777, column: 6)
!903 = !DILocation(line: 1777, column: 6, scope: !902)
!904 = !DILocation(line: 1777, column: 36, scope: !902)
!905 = !DILocation(line: 1778, column: 6, scope: !902)
!906 = !DILocation(line: 1778, column: 28, scope: !907)
!907 = !DILexicalBlockFile(scope: !902, file: !1, discriminator: 1)
!908 = !DILocation(line: 1778, column: 9, scope: !907)
!909 = !DILocation(line: 1778, column: 35, scope: !907)
!910 = !DILocation(line: 1779, column: 6, scope: !902)
!911 = !DILocation(line: 1779, column: 32, scope: !907)
!912 = !DILocation(line: 1779, column: 9, scope: !907)
!913 = !DILocation(line: 1779, column: 39, scope: !907)
!914 = !DILocation(line: 1777, column: 6, scope: !915)
!915 = !DILexicalBlockFile(scope: !233, file: !1, discriminator: 1)
!916 = !DILocation(line: 1780, column: 3, scope: !902)
!917 = !DILocation(line: 1782, column: 7, scope: !918)
!918 = distinct !DILexicalBlock(scope: !233, file: !1, line: 1782, column: 6)
!919 = !DILocation(line: 1782, column: 6, scope: !918)
!920 = !DILocation(line: 1782, column: 10, scope: !918)
!921 = !DILocation(line: 1782, column: 6, scope: !233)
!922 = !DILocalVariable(name: "path", scope: !923, file: !1, line: 1783, type: !80)
!923 = distinct !DILexicalBlock(scope: !918, file: !1, line: 1782, column: 15)
!924 = !DILocation(line: 1783, column: 15, scope: !923)
!925 = !DILocation(line: 1785, column: 35, scope: !923)
!926 = !DILocation(line: 1785, column: 10, scope: !923)
!927 = !DILocation(line: 1785, column: 8, scope: !923)
!928 = !DILocation(line: 1786, column: 7, scope: !929)
!929 = distinct !DILexicalBlock(scope: !923, file: !1, line: 1786, column: 7)
!930 = !DILocation(line: 1786, column: 12, scope: !929)
!931 = !DILocation(line: 1786, column: 7, scope: !923)
!932 = !DILocation(line: 1787, column: 34, scope: !929)
!933 = !DILocation(line: 1787, column: 11, scope: !929)
!934 = !DILocation(line: 1787, column: 9, scope: !929)
!935 = !DILocation(line: 1787, column: 4, scope: !929)
!936 = !DILocation(line: 1788, column: 7, scope: !937)
!937 = distinct !DILexicalBlock(scope: !923, file: !1, line: 1788, column: 7)
!938 = !DILocation(line: 1788, column: 10, scope: !937)
!939 = !DILocation(line: 1788, column: 15, scope: !937)
!940 = !DILocation(line: 1788, column: 7, scope: !923)
!941 = !DILocation(line: 1789, column: 10, scope: !937)
!942 = !DILocation(line: 1789, column: 13, scope: !937)
!943 = !DILocation(line: 1789, column: 33, scope: !937)
!944 = !DILocation(line: 1789, column: 36, scope: !937)
!945 = !DILocation(line: 1789, column: 42, scope: !937)
!946 = !DILocation(line: 1789, column: 5, scope: !937)
!947 = !DILocation(line: 1789, column: 8, scope: !937)
!948 = !DILocation(line: 1789, column: 4, scope: !937)
!949 = !DILocation(line: 1792, column: 15, scope: !937)
!950 = !DILocation(line: 1792, column: 10, scope: !937)
!951 = !DILocation(line: 1792, column: 5, scope: !937)
!952 = !DILocation(line: 1792, column: 8, scope: !937)
!953 = !DILocation(line: 1793, column: 8, scope: !954)
!954 = distinct !DILexicalBlock(scope: !923, file: !1, line: 1793, column: 7)
!955 = !DILocation(line: 1793, column: 7, scope: !954)
!956 = !DILocation(line: 1793, column: 11, scope: !954)
!957 = !DILocation(line: 1793, column: 7, scope: !923)
!958 = !DILocation(line: 1794, column: 23, scope: !959)
!959 = distinct !DILexicalBlock(scope: !954, file: !1, line: 1793, column: 16)
!960 = !DILocation(line: 1794, column: 26, scope: !959)
!961 = !DILocation(line: 1794, column: 35, scope: !959)
!962 = !DILocation(line: 1795, column: 27, scope: !959)
!963 = !DILocation(line: 1794, column: 4, scope: !964)
!964 = !DILexicalBlockFile(scope: !959, file: !1, discriminator: 1)
!965 = !DILocation(line: 1796, column: 4, scope: !959)
!966 = !DILocation(line: 1798, column: 34, scope: !923)
!967 = !DILocation(line: 1798, column: 33, scope: !923)
!968 = !DILocation(line: 1798, column: 3, scope: !923)
!969 = !DILocation(line: 1799, column: 2, scope: !923)
!970 = !DILocation(line: 1802, column: 2, scope: !233)
!971 = !DILocation(line: 1803, column: 8, scope: !233)
!972 = !DILocation(line: 1804, column: 24, scope: !233)
!973 = !DILocation(line: 1804, column: 7, scope: !233)
!974 = !DILocation(line: 1804, column: 5, scope: !233)
!975 = !DILocation(line: 1805, column: 2, scope: !233)
!976 = !DILocation(line: 1805, column: 6, scope: !233)
!977 = !DILocation(line: 1805, column: 15, scope: !233)
!978 = !DILocation(line: 1806, column: 2, scope: !233)
!979 = !DILocation(line: 1806, column: 6, scope: !233)
!980 = !DILocation(line: 1806, column: 16, scope: !233)
!981 = !DILocation(line: 1807, column: 2, scope: !233)
!982 = !DILocation(line: 1807, column: 6, scope: !233)
!983 = !DILocation(line: 1807, column: 15, scope: !233)
!984 = !DILocation(line: 1808, column: 24, scope: !233)
!985 = !DILocation(line: 1808, column: 2, scope: !233)
!986 = !DILocation(line: 1808, column: 6, scope: !233)
!987 = !DILocation(line: 1808, column: 22, scope: !233)
!988 = !DILocation(line: 1809, column: 12, scope: !233)
!989 = !DILocation(line: 1810, column: 28, scope: !233)
!990 = !DILocation(line: 1810, column: 9, scope: !233)
!991 = !DILocation(line: 1810, column: 7, scope: !233)
!992 = !DILocation(line: 1811, column: 13, scope: !993)
!993 = distinct !DILexicalBlock(scope: !233, file: !1, line: 1811, column: 2)
!994 = !DILocation(line: 1811, column: 7, scope: !993)
!995 = !DILocalVariable(name: "i", scope: !996, file: !1, line: 1812, type: !23)
!996 = distinct !DILexicalBlock(scope: !997, file: !1, line: 1811, column: 29)
!997 = distinct !DILexicalBlock(scope: !993, file: !1, line: 1811, column: 2)
!998 = !DILocation(line: 1812, column: 7, scope: !996)
!999 = !DILocalVariable(name: "r", scope: !996, file: !1, line: 1812, type: !23)
!1000 = !DILocation(line: 1812, column: 10, scope: !996)
!1001 = !DILocation(line: 1814, column: 14, scope: !996)
!1002 = !DILocation(line: 1814, column: 13, scope: !996)
!1003 = !DILocation(line: 1814, column: 33, scope: !996)
!1004 = !DILocation(line: 1814, column: 7, scope: !996)
!1005 = !DILocation(line: 1814, column: 5, scope: !996)
!1006 = !DILocation(line: 1815, column: 7, scope: !1007)
!1007 = distinct !DILexicalBlock(scope: !996, file: !1, line: 1815, column: 7)
!1008 = !DILocation(line: 1815, column: 9, scope: !1007)
!1009 = !DILocation(line: 1815, column: 7, scope: !996)
!1010 = !DILocation(line: 1819, column: 4, scope: !1011)
!1011 = distinct !DILexicalBlock(scope: !1007, file: !1, line: 1815, column: 14)
!1012 = !DILocation(line: 1821, column: 7, scope: !1013)
!1013 = distinct !DILexicalBlock(scope: !996, file: !1, line: 1821, column: 7)
!1014 = !DILocation(line: 1821, column: 11, scope: !1013)
!1015 = !DILocation(line: 1821, column: 29, scope: !1013)
!1016 = !DILocation(line: 1821, column: 7, scope: !996)
!1017 = !DILocation(line: 1822, column: 8, scope: !1018)
!1018 = distinct !DILexicalBlock(scope: !1019, file: !1, line: 1822, column: 8)
!1019 = distinct !DILexicalBlock(scope: !1013, file: !1, line: 1821, column: 35)
!1020 = !DILocation(line: 1822, column: 14, scope: !1018)
!1021 = !DILocation(line: 1822, column: 8, scope: !1019)
!1022 = !DILocation(line: 1824, column: 36, scope: !1023)
!1023 = distinct !DILexicalBlock(scope: !1018, file: !1, line: 1822, column: 20)
!1024 = !DILocation(line: 1824, column: 5, scope: !1023)
!1025 = !DILocation(line: 1825, column: 4, scope: !1023)
!1026 = !DILocation(line: 1826, column: 4, scope: !1019)
!1027 = !DILocation(line: 1828, column: 8, scope: !996)
!1028 = !DILocation(line: 1828, column: 12, scope: !996)
!1029 = !DILocation(line: 1828, column: 6, scope: !996)
!1030 = !DILocation(line: 1829, column: 10, scope: !1031)
!1031 = distinct !DILexicalBlock(scope: !996, file: !1, line: 1829, column: 3)
!1032 = !DILocation(line: 1829, column: 8, scope: !1031)
!1033 = !DILocation(line: 1829, column: 15, scope: !1034)
!1034 = !DILexicalBlockFile(scope: !1035, file: !1, discriminator: 1)
!1035 = distinct !DILexicalBlock(scope: !1031, file: !1, line: 1829, column: 3)
!1036 = !DILocation(line: 1829, column: 24, scope: !1034)
!1037 = !DILocation(line: 1829, column: 28, scope: !1034)
!1038 = !DILocation(line: 1829, column: 17, scope: !1034)
!1039 = !DILocation(line: 1829, column: 3, scope: !1034)
!1040 = !DILocation(line: 1830, column: 10, scope: !1041)
!1041 = distinct !DILexicalBlock(scope: !1042, file: !1, line: 1830, column: 8)
!1042 = distinct !DILexicalBlock(scope: !1035, file: !1, line: 1829, column: 58)
!1043 = !DILocation(line: 1830, column: 14, scope: !1041)
!1044 = !DILocation(line: 1830, column: 23, scope: !1041)
!1045 = !DILocation(line: 1830, column: 8, scope: !1042)
!1046 = !DILocalVariable(name: "length", scope: !1047, file: !1, line: 1833, type: !52)
!1047 = distinct !DILexicalBlock(scope: !1041, file: !1, line: 1830, column: 51)
!1048 = !DILocation(line: 1833, column: 13, scope: !1047)
!1049 = !DILocation(line: 1833, column: 22, scope: !1047)
!1050 = !DILocation(line: 1833, column: 26, scope: !1047)
!1051 = !DILocation(line: 1834, column: 9, scope: !1052)
!1052 = distinct !DILexicalBlock(scope: !1047, file: !1, line: 1834, column: 9)
!1053 = !DILocation(line: 1834, column: 13, scope: !1052)
!1054 = !DILocation(line: 1834, column: 26, scope: !1052)
!1055 = !DILocation(line: 1834, column: 24, scope: !1052)
!1056 = !DILocation(line: 1834, column: 45, scope: !1052)
!1057 = !DILocation(line: 1834, column: 33, scope: !1052)
!1058 = !DILocation(line: 1834, column: 9, scope: !1047)
!1059 = !DILocation(line: 1835, column: 16, scope: !1052)
!1060 = !DILocation(line: 1835, column: 20, scope: !1052)
!1061 = !DILocation(line: 1835, column: 33, scope: !1052)
!1062 = !DILocation(line: 1835, column: 31, scope: !1052)
!1063 = !DILocation(line: 1835, column: 42, scope: !1052)
!1064 = !DILocation(line: 1835, column: 40, scope: !1052)
!1065 = !DILocation(line: 1835, column: 13, scope: !1052)
!1066 = !DILocation(line: 1835, column: 6, scope: !1052)
!1067 = !DILocation(line: 1836, column: 9, scope: !1068)
!1068 = distinct !DILexicalBlock(scope: !1047, file: !1, line: 1836, column: 9)
!1069 = !DILocation(line: 1836, column: 13, scope: !1068)
!1070 = !DILocation(line: 1836, column: 24, scope: !1068)
!1071 = !DILocation(line: 1836, column: 29, scope: !1068)
!1072 = !DILocation(line: 1836, column: 32, scope: !1073)
!1073 = !DILexicalBlockFile(scope: !1068, file: !1, discriminator: 1)
!1074 = !DILocation(line: 1836, column: 42, scope: !1073)
!1075 = !DILocation(line: 1836, column: 39, scope: !1073)
!1076 = !DILocation(line: 1836, column: 9, scope: !1073)
!1077 = !DILocation(line: 1838, column: 16, scope: !1078)
!1078 = distinct !DILexicalBlock(scope: !1068, file: !1, line: 1836, column: 48)
!1079 = !DILocation(line: 1839, column: 6, scope: !1078)
!1080 = !DILocation(line: 1841, column: 9, scope: !1081)
!1081 = distinct !DILexicalBlock(scope: !1047, file: !1, line: 1841, column: 9)
!1082 = !DILocation(line: 1841, column: 16, scope: !1081)
!1083 = !DILocation(line: 1841, column: 9, scope: !1047)
!1084 = !DILocation(line: 1842, column: 37, scope: !1081)
!1085 = !DILocation(line: 1843, column: 10, scope: !1081)
!1086 = !DILocation(line: 1843, column: 14, scope: !1081)
!1087 = !DILocation(line: 1843, column: 26, scope: !1081)
!1088 = !DILocation(line: 1842, column: 6, scope: !1081)
!1089 = !DILocation(line: 1844, column: 4, scope: !1047)
!1090 = !DILocation(line: 1845, column: 8, scope: !1091)
!1091 = distinct !DILexicalBlock(scope: !1042, file: !1, line: 1845, column: 8)
!1092 = !DILocation(line: 1845, column: 12, scope: !1091)
!1093 = !DILocation(line: 1845, column: 21, scope: !1091)
!1094 = !DILocation(line: 1845, column: 8, scope: !1042)
!1095 = !DILocation(line: 1846, column: 15, scope: !1091)
!1096 = !DILocation(line: 1846, column: 5, scope: !1091)
!1097 = !DILocation(line: 1847, column: 3, scope: !1042)
!1098 = !DILocation(line: 1829, column: 48, scope: !1099)
!1099 = !DILexicalBlockFile(scope: !1035, file: !1, discriminator: 2)
!1100 = !DILocation(line: 1829, column: 54, scope: !1099)
!1101 = !DILocation(line: 1829, column: 3, scope: !1099)
!1102 = !DILocation(line: 1848, column: 7, scope: !1103)
!1103 = distinct !DILexicalBlock(scope: !996, file: !1, line: 1848, column: 7)
!1104 = !DILocation(line: 1848, column: 7, scope: !996)
!1105 = !DILocation(line: 1849, column: 9, scope: !1106)
!1106 = distinct !DILexicalBlock(scope: !1103, file: !1, line: 1848, column: 18)
!1107 = !DILocation(line: 1849, column: 13, scope: !1106)
!1108 = !DILocation(line: 1849, column: 26, scope: !1106)
!1109 = !DILocation(line: 1849, column: 30, scope: !1106)
!1110 = !DILocation(line: 1849, column: 24, scope: !1106)
!1111 = !DILocation(line: 1849, column: 48, scope: !1106)
!1112 = !DILocation(line: 1849, column: 7, scope: !1106)
!1113 = !DILocation(line: 1850, column: 19, scope: !1106)
!1114 = !DILocation(line: 1850, column: 23, scope: !1106)
!1115 = !DILocation(line: 1850, column: 36, scope: !1106)
!1116 = !DILocation(line: 1850, column: 40, scope: !1106)
!1117 = !DILocation(line: 1850, column: 34, scope: !1106)
!1118 = !DILocation(line: 1850, column: 4, scope: !1106)
!1119 = !DILocation(line: 1850, column: 8, scope: !1106)
!1120 = !DILocation(line: 1850, column: 17, scope: !1106)
!1121 = !DILocation(line: 1851, column: 3, scope: !1106)
!1122 = !DILocation(line: 1852, column: 4, scope: !1103)
!1123 = !DILocation(line: 1853, column: 2, scope: !996)
!1124 = !DILocation(line: 1811, column: 20, scope: !1125)
!1125 = !DILexicalBlockFile(scope: !997, file: !1, discriminator: 1)
!1126 = !DILocation(line: 1811, column: 2, scope: !1125)
!1127 = !DILocation(line: 1853, column: 2, scope: !1128)
!1128 = !DILexicalBlockFile(scope: !993, file: !1, discriminator: 1)
!1129 = !DILocation(line: 1855, column: 10, scope: !233)
!1130 = !DILocation(line: 1855, column: 2, scope: !233)
!1131 = !DILocation(line: 1856, column: 1, scope: !233)
