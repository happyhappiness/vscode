; ModuleID = '/data/download/cmake/cmake-master/Utilities/cmlibarchive/libarchive/archive_entry_copy_stat.c'
target datalayout = "e-m:e-i64:64-f80:128-n8:16:32:64-S128"
target triple = "x86_64-unknown-linux-gnu"

%struct.archive_entry = type opaque
%struct.stat = type { i64, i64, i64, i32, i32, i32, i32, i64, i64, i64, i64, %struct.timespec, %struct.timespec, %struct.timespec, [3 x i64] }
%struct.timespec = type { i64, i64 }

; Function Attrs: nounwind uwtable
define void @archive_entry_copy_stat(%struct.archive_entry* %entry1, %struct.stat* %st) #0 !dbg !4 {
entry:
  %entry.addr = alloca %struct.archive_entry*, align 8
  %st.addr = alloca %struct.stat*, align 8
  store %struct.archive_entry* %entry1, %struct.archive_entry** %entry.addr, align 8
  call void @llvm.dbg.declare(metadata %struct.archive_entry** %entry.addr, metadata !57, metadata !58), !dbg !59
  store %struct.stat* %st, %struct.stat** %st.addr, align 8
  call void @llvm.dbg.declare(metadata %struct.stat** %st.addr, metadata !60, metadata !58), !dbg !61
  %0 = load %struct.archive_entry*, %struct.archive_entry** %entry.addr, align 8, !dbg !62
  %1 = load %struct.stat*, %struct.stat** %st.addr, align 8, !dbg !63
  %st_atim = getelementptr inbounds %struct.stat, %struct.stat* %1, i32 0, i32 11, !dbg !64
  %tv_sec = getelementptr inbounds %struct.timespec, %struct.timespec* %st_atim, i32 0, i32 0, !dbg !64
  %2 = load i64, i64* %tv_sec, align 8, !dbg !64
  %3 = load %struct.stat*, %struct.stat** %st.addr, align 8, !dbg !65
  %st_atim2 = getelementptr inbounds %struct.stat, %struct.stat* %3, i32 0, i32 11, !dbg !66
  %tv_nsec = getelementptr inbounds %struct.timespec, %struct.timespec* %st_atim2, i32 0, i32 1, !dbg !67
  %4 = load i64, i64* %tv_nsec, align 8, !dbg !67
  call void @archive_entry_set_atime(%struct.archive_entry* %0, i64 %2, i64 %4), !dbg !68
  %5 = load %struct.archive_entry*, %struct.archive_entry** %entry.addr, align 8, !dbg !69
  %6 = load %struct.stat*, %struct.stat** %st.addr, align 8, !dbg !70
  %st_ctim = getelementptr inbounds %struct.stat, %struct.stat* %6, i32 0, i32 13, !dbg !71
  %tv_sec3 = getelementptr inbounds %struct.timespec, %struct.timespec* %st_ctim, i32 0, i32 0, !dbg !71
  %7 = load i64, i64* %tv_sec3, align 8, !dbg !71
  %8 = load %struct.stat*, %struct.stat** %st.addr, align 8, !dbg !72
  %st_ctim4 = getelementptr inbounds %struct.stat, %struct.stat* %8, i32 0, i32 13, !dbg !73
  %tv_nsec5 = getelementptr inbounds %struct.timespec, %struct.timespec* %st_ctim4, i32 0, i32 1, !dbg !74
  %9 = load i64, i64* %tv_nsec5, align 8, !dbg !74
  call void @archive_entry_set_ctime(%struct.archive_entry* %5, i64 %7, i64 %9), !dbg !75
  %10 = load %struct.archive_entry*, %struct.archive_entry** %entry.addr, align 8, !dbg !76
  %11 = load %struct.stat*, %struct.stat** %st.addr, align 8, !dbg !77
  %st_mtim = getelementptr inbounds %struct.stat, %struct.stat* %11, i32 0, i32 12, !dbg !78
  %tv_sec6 = getelementptr inbounds %struct.timespec, %struct.timespec* %st_mtim, i32 0, i32 0, !dbg !78
  %12 = load i64, i64* %tv_sec6, align 8, !dbg !78
  %13 = load %struct.stat*, %struct.stat** %st.addr, align 8, !dbg !79
  %st_mtim7 = getelementptr inbounds %struct.stat, %struct.stat* %13, i32 0, i32 12, !dbg !80
  %tv_nsec8 = getelementptr inbounds %struct.timespec, %struct.timespec* %st_mtim7, i32 0, i32 1, !dbg !81
  %14 = load i64, i64* %tv_nsec8, align 8, !dbg !81
  call void @archive_entry_set_mtime(%struct.archive_entry* %10, i64 %12, i64 %14), !dbg !82
  %15 = load %struct.archive_entry*, %struct.archive_entry** %entry.addr, align 8, !dbg !83
  call void @archive_entry_unset_birthtime(%struct.archive_entry* %15), !dbg !84
  %16 = load %struct.archive_entry*, %struct.archive_entry** %entry.addr, align 8, !dbg !85
  %17 = load %struct.stat*, %struct.stat** %st.addr, align 8, !dbg !86
  %st_dev = getelementptr inbounds %struct.stat, %struct.stat* %17, i32 0, i32 0, !dbg !87
  %18 = load i64, i64* %st_dev, align 8, !dbg !87
  call void @archive_entry_set_dev(%struct.archive_entry* %16, i64 %18), !dbg !88
  %19 = load %struct.archive_entry*, %struct.archive_entry** %entry.addr, align 8, !dbg !89
  %20 = load %struct.stat*, %struct.stat** %st.addr, align 8, !dbg !90
  %st_gid = getelementptr inbounds %struct.stat, %struct.stat* %20, i32 0, i32 5, !dbg !91
  %21 = load i32, i32* %st_gid, align 8, !dbg !91
  %conv = zext i32 %21 to i64, !dbg !90
  call void @archive_entry_set_gid(%struct.archive_entry* %19, i64 %conv), !dbg !92
  %22 = load %struct.archive_entry*, %struct.archive_entry** %entry.addr, align 8, !dbg !93
  %23 = load %struct.stat*, %struct.stat** %st.addr, align 8, !dbg !94
  %st_uid = getelementptr inbounds %struct.stat, %struct.stat* %23, i32 0, i32 4, !dbg !95
  %24 = load i32, i32* %st_uid, align 4, !dbg !95
  %conv9 = zext i32 %24 to i64, !dbg !94
  call void @archive_entry_set_uid(%struct.archive_entry* %22, i64 %conv9), !dbg !96
  %25 = load %struct.archive_entry*, %struct.archive_entry** %entry.addr, align 8, !dbg !97
  %26 = load %struct.stat*, %struct.stat** %st.addr, align 8, !dbg !98
  %st_ino = getelementptr inbounds %struct.stat, %struct.stat* %26, i32 0, i32 1, !dbg !99
  %27 = load i64, i64* %st_ino, align 8, !dbg !99
  call void @archive_entry_set_ino(%struct.archive_entry* %25, i64 %27), !dbg !100
  %28 = load %struct.archive_entry*, %struct.archive_entry** %entry.addr, align 8, !dbg !101
  %29 = load %struct.stat*, %struct.stat** %st.addr, align 8, !dbg !102
  %st_nlink = getelementptr inbounds %struct.stat, %struct.stat* %29, i32 0, i32 2, !dbg !103
  %30 = load i64, i64* %st_nlink, align 8, !dbg !103
  %conv10 = trunc i64 %30 to i32, !dbg !102
  call void @archive_entry_set_nlink(%struct.archive_entry* %28, i32 %conv10), !dbg !104
  %31 = load %struct.archive_entry*, %struct.archive_entry** %entry.addr, align 8, !dbg !105
  %32 = load %struct.stat*, %struct.stat** %st.addr, align 8, !dbg !106
  %st_rdev = getelementptr inbounds %struct.stat, %struct.stat* %32, i32 0, i32 7, !dbg !107
  %33 = load i64, i64* %st_rdev, align 8, !dbg !107
  call void @archive_entry_set_rdev(%struct.archive_entry* %31, i64 %33), !dbg !108
  %34 = load %struct.archive_entry*, %struct.archive_entry** %entry.addr, align 8, !dbg !109
  %35 = load %struct.stat*, %struct.stat** %st.addr, align 8, !dbg !110
  %st_size = getelementptr inbounds %struct.stat, %struct.stat* %35, i32 0, i32 8, !dbg !111
  %36 = load i64, i64* %st_size, align 8, !dbg !111
  call void @archive_entry_set_size(%struct.archive_entry* %34, i64 %36), !dbg !112
  %37 = load %struct.archive_entry*, %struct.archive_entry** %entry.addr, align 8, !dbg !113
  %38 = load %struct.stat*, %struct.stat** %st.addr, align 8, !dbg !114
  %st_mode = getelementptr inbounds %struct.stat, %struct.stat* %38, i32 0, i32 3, !dbg !115
  %39 = load i32, i32* %st_mode, align 8, !dbg !115
  call void @archive_entry_set_mode(%struct.archive_entry* %37, i32 %39), !dbg !116
  ret void, !dbg !117
}

; Function Attrs: nounwind readnone
declare void @llvm.dbg.declare(metadata, metadata, metadata) #1

declare void @archive_entry_set_atime(%struct.archive_entry*, i64, i64) #2

declare void @archive_entry_set_ctime(%struct.archive_entry*, i64, i64) #2

declare void @archive_entry_set_mtime(%struct.archive_entry*, i64, i64) #2

declare void @archive_entry_unset_birthtime(%struct.archive_entry*) #2

declare void @archive_entry_set_dev(%struct.archive_entry*, i64) #2

declare void @archive_entry_set_gid(%struct.archive_entry*, i64) #2

declare void @archive_entry_set_uid(%struct.archive_entry*, i64) #2

declare void @archive_entry_set_ino(%struct.archive_entry*, i64) #2

declare void @archive_entry_set_nlink(%struct.archive_entry*, i32) #2

declare void @archive_entry_set_rdev(%struct.archive_entry*, i64) #2

declare void @archive_entry_set_size(%struct.archive_entry*, i64) #2

declare void @archive_entry_set_mode(%struct.archive_entry*, i32) #2

attributes #0 = { nounwind uwtable "disable-tail-calls"="false" "less-precise-fpmad"="false" "no-frame-pointer-elim"="true" "no-frame-pointer-elim-non-leaf" "no-infs-fp-math"="false" "no-nans-fp-math"="false" "stack-protector-buffer-size"="8" "target-cpu"="x86-64" "target-features"="+fxsr,+mmx,+sse,+sse2" "unsafe-fp-math"="false" "use-soft-float"="false" }
attributes #1 = { nounwind readnone }
attributes #2 = { "disable-tail-calls"="false" "less-precise-fpmad"="false" "no-frame-pointer-elim"="true" "no-frame-pointer-elim-non-leaf" "no-infs-fp-math"="false" "no-nans-fp-math"="false" "stack-protector-buffer-size"="8" "target-cpu"="x86-64" "target-features"="+fxsr,+mmx,+sse,+sse2" "unsafe-fp-math"="false" "use-soft-float"="false" }

!llvm.dbg.cu = !{!0}
!llvm.module.flags = !{!54, !55}
!llvm.ident = !{!56}

!0 = distinct !DICompileUnit(language: DW_LANG_C99, file: !1, producer: "clang version 3.8.0 (tags/RELEASE_380/final)", isOptimized: false, runtimeVersion: 0, emissionKind: 1, enums: !2, subprograms: !3)
!1 = !DIFile(filename: "/data/download/cmake/cmake-master/Utilities/cmlibarchive/libarchive/archive_entry_copy_stat.c", directory: "/data/download/cmake/cmake-master/Utilities/cmlibarchive/libarchive")
!2 = !{}
!3 = !{!4}
!4 = distinct !DISubprogram(name: "archive_entry_copy_stat", scope: !1, file: !1, line: 37, type: !5, isLocal: false, isDefinition: true, scopeLine: 38, flags: DIFlagPrototyped, isOptimized: false, variables: !2)
!5 = !DISubroutineType(types: !6)
!6 = !{null, !7, !10}
!7 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !8, size: 64, align: 64)
!8 = !DICompositeType(tag: DW_TAG_structure_type, name: "archive_entry", file: !9, line: 180, flags: DIFlagFwdDecl)
!9 = !DIFile(filename: "/data/download/cmake/cmake-master/Utilities/cmlibarchive/libarchive/archive.h", directory: "/data/download/cmake/cmake-master/Utilities/cmlibarchive/libarchive")
!10 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !11, size: 64, align: 64)
!11 = !DIDerivedType(tag: DW_TAG_const_type, baseType: !12)
!12 = !DICompositeType(tag: DW_TAG_structure_type, name: "stat", file: !13, line: 46, size: 1152, align: 64, elements: !14)
!13 = !DIFile(filename: "/usr/include/x86_64-linux-gnu/bits/stat.h", directory: "/data/download/cmake/cmake-master/Utilities/cmlibarchive/libarchive")
!14 = !{!15, !19, !21, !23, !26, !28, !30, !32, !33, !36, !38, !40, !48, !49, !50}
!15 = !DIDerivedType(tag: DW_TAG_member, name: "st_dev", scope: !12, file: !13, line: 48, baseType: !16, size: 64, align: 64)
!16 = !DIDerivedType(tag: DW_TAG_typedef, name: "__dev_t", file: !17, line: 124, baseType: !18)
!17 = !DIFile(filename: "/usr/include/x86_64-linux-gnu/bits/types.h", directory: "/data/download/cmake/cmake-master/Utilities/cmlibarchive/libarchive")
!18 = !DIBasicType(name: "long unsigned int", size: 64, align: 64, encoding: DW_ATE_unsigned)
!19 = !DIDerivedType(tag: DW_TAG_member, name: "st_ino", scope: !12, file: !13, line: 53, baseType: !20, size: 64, align: 64, offset: 64)
!20 = !DIDerivedType(tag: DW_TAG_typedef, name: "__ino_t", file: !17, line: 127, baseType: !18)
!21 = !DIDerivedType(tag: DW_TAG_member, name: "st_nlink", scope: !12, file: !13, line: 61, baseType: !22, size: 64, align: 64, offset: 128)
!22 = !DIDerivedType(tag: DW_TAG_typedef, name: "__nlink_t", file: !17, line: 130, baseType: !18)
!23 = !DIDerivedType(tag: DW_TAG_member, name: "st_mode", scope: !12, file: !13, line: 62, baseType: !24, size: 32, align: 32, offset: 192)
!24 = !DIDerivedType(tag: DW_TAG_typedef, name: "__mode_t", file: !17, line: 129, baseType: !25)
!25 = !DIBasicType(name: "unsigned int", size: 32, align: 32, encoding: DW_ATE_unsigned)
!26 = !DIDerivedType(tag: DW_TAG_member, name: "st_uid", scope: !12, file: !13, line: 64, baseType: !27, size: 32, align: 32, offset: 224)
!27 = !DIDerivedType(tag: DW_TAG_typedef, name: "__uid_t", file: !17, line: 125, baseType: !25)
!28 = !DIDerivedType(tag: DW_TAG_member, name: "st_gid", scope: !12, file: !13, line: 65, baseType: !29, size: 32, align: 32, offset: 256)
!29 = !DIDerivedType(tag: DW_TAG_typedef, name: "__gid_t", file: !17, line: 126, baseType: !25)
!30 = !DIDerivedType(tag: DW_TAG_member, name: "__pad0", scope: !12, file: !13, line: 67, baseType: !31, size: 32, align: 32, offset: 288)
!31 = !DIBasicType(name: "int", size: 32, align: 32, encoding: DW_ATE_signed)
!32 = !DIDerivedType(tag: DW_TAG_member, name: "st_rdev", scope: !12, file: !13, line: 69, baseType: !16, size: 64, align: 64, offset: 320)
!33 = !DIDerivedType(tag: DW_TAG_member, name: "st_size", scope: !12, file: !13, line: 74, baseType: !34, size: 64, align: 64, offset: 384)
!34 = !DIDerivedType(tag: DW_TAG_typedef, name: "__off_t", file: !17, line: 131, baseType: !35)
!35 = !DIBasicType(name: "long int", size: 64, align: 64, encoding: DW_ATE_signed)
!36 = !DIDerivedType(tag: DW_TAG_member, name: "st_blksize", scope: !12, file: !13, line: 78, baseType: !37, size: 64, align: 64, offset: 448)
!37 = !DIDerivedType(tag: DW_TAG_typedef, name: "__blksize_t", file: !17, line: 153, baseType: !35)
!38 = !DIDerivedType(tag: DW_TAG_member, name: "st_blocks", scope: !12, file: !13, line: 80, baseType: !39, size: 64, align: 64, offset: 512)
!39 = !DIDerivedType(tag: DW_TAG_typedef, name: "__blkcnt_t", file: !17, line: 158, baseType: !35)
!40 = !DIDerivedType(tag: DW_TAG_member, name: "st_atim", scope: !12, file: !13, line: 91, baseType: !41, size: 128, align: 64, offset: 576)
!41 = !DICompositeType(tag: DW_TAG_structure_type, name: "timespec", file: !42, line: 120, size: 128, align: 64, elements: !43)
!42 = !DIFile(filename: "/usr/include/time.h", directory: "/data/download/cmake/cmake-master/Utilities/cmlibarchive/libarchive")
!43 = !{!44, !46}
!44 = !DIDerivedType(tag: DW_TAG_member, name: "tv_sec", scope: !41, file: !42, line: 122, baseType: !45, size: 64, align: 64)
!45 = !DIDerivedType(tag: DW_TAG_typedef, name: "__time_t", file: !17, line: 139, baseType: !35)
!46 = !DIDerivedType(tag: DW_TAG_member, name: "tv_nsec", scope: !41, file: !42, line: 123, baseType: !47, size: 64, align: 64, offset: 64)
!47 = !DIDerivedType(tag: DW_TAG_typedef, name: "__syscall_slong_t", file: !17, line: 175, baseType: !35)
!48 = !DIDerivedType(tag: DW_TAG_member, name: "st_mtim", scope: !12, file: !13, line: 92, baseType: !41, size: 128, align: 64, offset: 704)
!49 = !DIDerivedType(tag: DW_TAG_member, name: "st_ctim", scope: !12, file: !13, line: 93, baseType: !41, size: 128, align: 64, offset: 832)
!50 = !DIDerivedType(tag: DW_TAG_member, name: "__glibc_reserved", scope: !12, file: !13, line: 106, baseType: !51, size: 192, align: 64, offset: 960)
!51 = !DICompositeType(tag: DW_TAG_array_type, baseType: !47, size: 192, align: 64, elements: !52)
!52 = !{!53}
!53 = !DISubrange(count: 3)
!54 = !{i32 2, !"Dwarf Version", i32 4}
!55 = !{i32 2, !"Debug Info Version", i32 3}
!56 = !{!"clang version 3.8.0 (tags/RELEASE_380/final)"}
!57 = !DILocalVariable(name: "entry", arg: 1, scope: !4, file: !1, line: 37, type: !7)
!58 = !DIExpression()
!59 = !DILocation(line: 37, column: 47, scope: !4)
!60 = !DILocalVariable(name: "st", arg: 2, scope: !4, file: !1, line: 37, type: !10)
!61 = !DILocation(line: 37, column: 73, scope: !4)
!62 = !DILocation(line: 44, column: 26, scope: !4)
!63 = !DILocation(line: 44, column: 33, scope: !4)
!64 = !DILocation(line: 44, column: 37, scope: !4)
!65 = !DILocation(line: 44, column: 47, scope: !4)
!66 = !DILocation(line: 44, column: 51, scope: !4)
!67 = !DILocation(line: 44, column: 59, scope: !4)
!68 = !DILocation(line: 44, column: 2, scope: !4)
!69 = !DILocation(line: 45, column: 26, scope: !4)
!70 = !DILocation(line: 45, column: 33, scope: !4)
!71 = !DILocation(line: 45, column: 37, scope: !4)
!72 = !DILocation(line: 45, column: 47, scope: !4)
!73 = !DILocation(line: 45, column: 51, scope: !4)
!74 = !DILocation(line: 45, column: 59, scope: !4)
!75 = !DILocation(line: 45, column: 2, scope: !4)
!76 = !DILocation(line: 46, column: 26, scope: !4)
!77 = !DILocation(line: 46, column: 33, scope: !4)
!78 = !DILocation(line: 46, column: 37, scope: !4)
!79 = !DILocation(line: 46, column: 47, scope: !4)
!80 = !DILocation(line: 46, column: 51, scope: !4)
!81 = !DILocation(line: 46, column: 59, scope: !4)
!82 = !DILocation(line: 46, column: 2, scope: !4)
!83 = !DILocation(line: 73, column: 32, scope: !4)
!84 = !DILocation(line: 73, column: 2, scope: !4)
!85 = !DILocation(line: 75, column: 24, scope: !4)
!86 = !DILocation(line: 75, column: 31, scope: !4)
!87 = !DILocation(line: 75, column: 35, scope: !4)
!88 = !DILocation(line: 75, column: 2, scope: !4)
!89 = !DILocation(line: 76, column: 24, scope: !4)
!90 = !DILocation(line: 76, column: 31, scope: !4)
!91 = !DILocation(line: 76, column: 35, scope: !4)
!92 = !DILocation(line: 76, column: 2, scope: !4)
!93 = !DILocation(line: 77, column: 24, scope: !4)
!94 = !DILocation(line: 77, column: 31, scope: !4)
!95 = !DILocation(line: 77, column: 35, scope: !4)
!96 = !DILocation(line: 77, column: 2, scope: !4)
!97 = !DILocation(line: 78, column: 24, scope: !4)
!98 = !DILocation(line: 78, column: 31, scope: !4)
!99 = !DILocation(line: 78, column: 35, scope: !4)
!100 = !DILocation(line: 78, column: 2, scope: !4)
!101 = !DILocation(line: 79, column: 26, scope: !4)
!102 = !DILocation(line: 79, column: 33, scope: !4)
!103 = !DILocation(line: 79, column: 37, scope: !4)
!104 = !DILocation(line: 79, column: 2, scope: !4)
!105 = !DILocation(line: 80, column: 25, scope: !4)
!106 = !DILocation(line: 80, column: 32, scope: !4)
!107 = !DILocation(line: 80, column: 36, scope: !4)
!108 = !DILocation(line: 80, column: 2, scope: !4)
!109 = !DILocation(line: 81, column: 25, scope: !4)
!110 = !DILocation(line: 81, column: 32, scope: !4)
!111 = !DILocation(line: 81, column: 36, scope: !4)
!112 = !DILocation(line: 81, column: 2, scope: !4)
!113 = !DILocation(line: 82, column: 25, scope: !4)
!114 = !DILocation(line: 82, column: 32, scope: !4)
!115 = !DILocation(line: 82, column: 36, scope: !4)
!116 = !DILocation(line: 82, column: 2, scope: !4)
!117 = !DILocation(line: 83, column: 1, scope: !4)
