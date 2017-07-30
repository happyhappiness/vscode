; ModuleID = '/data/download/cmake/cmake-master/Utilities/cmcurl/lib/getenv.c'
target datalayout = "e-m:e-i64:64-f80:128-n8:16:32:64-S128"
target triple = "x86_64-unknown-linux-gnu"

@Curl_cstrdup = external global i8* (i8*)*, align 8

; Function Attrs: nounwind uwtable
define i8* @curl_getenv(i8* %v) #0 !dbg !4 {
entry:
  %v.addr = alloca i8*, align 8
  store i8* %v, i8** %v.addr, align 8
  call void @llvm.dbg.declare(metadata i8** %v.addr, metadata !15, metadata !16), !dbg !17
  %0 = load i8*, i8** %v.addr, align 8, !dbg !18
  %call = call i8* @GetEnv(i8* %0), !dbg !19
  ret i8* %call, !dbg !20
}

; Function Attrs: nounwind readnone
declare void @llvm.dbg.declare(metadata, metadata, metadata) #1

; Function Attrs: nounwind uwtable
define internal i8* @GetEnv(i8* %variable) #0 !dbg !11 {
entry:
  %variable.addr = alloca i8*, align 8
  %env = alloca i8*, align 8
  store i8* %variable, i8** %variable.addr, align 8
  call void @llvm.dbg.declare(metadata i8** %variable.addr, metadata !21, metadata !16), !dbg !22
  call void @llvm.dbg.declare(metadata i8** %env, metadata !23, metadata !16), !dbg !24
  %0 = load i8*, i8** %variable.addr, align 8, !dbg !25
  %call = call i8* @getenv(i8* %0) #3, !dbg !26
  store i8* %call, i8** %env, align 8, !dbg !24
  %1 = load i8*, i8** %env, align 8, !dbg !27
  %tobool = icmp ne i8* %1, null, !dbg !27
  br i1 %tobool, label %land.lhs.true, label %cond.false, !dbg !28

land.lhs.true:                                    ; preds = %entry
  %2 = load i8*, i8** %env, align 8, !dbg !29
  %arrayidx = getelementptr inbounds i8, i8* %2, i64 0, !dbg !29
  %3 = load i8, i8* %arrayidx, align 1, !dbg !29
  %conv = sext i8 %3 to i32, !dbg !29
  %tobool1 = icmp ne i32 %conv, 0, !dbg !29
  br i1 %tobool1, label %cond.true, label %cond.false, !dbg !31

cond.true:                                        ; preds = %land.lhs.true
  %4 = load i8* (i8*)*, i8* (i8*)** @Curl_cstrdup, align 8, !dbg !32
  %5 = load i8*, i8** %env, align 8, !dbg !32
  %call2 = call i8* %4(i8* %5), !dbg !32
  br label %cond.end, !dbg !34

cond.false:                                       ; preds = %land.lhs.true, %entry
  br label %cond.end, !dbg !35

cond.end:                                         ; preds = %cond.false, %cond.true
  %cond = phi i8* [ %call2, %cond.true ], [ null, %cond.false ], !dbg !37
  ret i8* %cond, !dbg !39
}

; Function Attrs: nounwind
declare i8* @getenv(i8*) #2

attributes #0 = { nounwind uwtable "disable-tail-calls"="false" "less-precise-fpmad"="false" "no-frame-pointer-elim"="true" "no-frame-pointer-elim-non-leaf" "no-infs-fp-math"="false" "no-nans-fp-math"="false" "stack-protector-buffer-size"="8" "target-cpu"="x86-64" "target-features"="+fxsr,+mmx,+sse,+sse2" "unsafe-fp-math"="false" "use-soft-float"="false" }
attributes #1 = { nounwind readnone }
attributes #2 = { nounwind "disable-tail-calls"="false" "less-precise-fpmad"="false" "no-frame-pointer-elim"="true" "no-frame-pointer-elim-non-leaf" "no-infs-fp-math"="false" "no-nans-fp-math"="false" "stack-protector-buffer-size"="8" "target-cpu"="x86-64" "target-features"="+fxsr,+mmx,+sse,+sse2" "unsafe-fp-math"="false" "use-soft-float"="false" }
attributes #3 = { nounwind }

!llvm.dbg.cu = !{!0}
!llvm.module.flags = !{!12, !13}
!llvm.ident = !{!14}

!0 = distinct !DICompileUnit(language: DW_LANG_C99, file: !1, producer: "clang version 3.8.0 (tags/RELEASE_380/final)", isOptimized: false, runtimeVersion: 0, emissionKind: 1, enums: !2, subprograms: !3)
!1 = !DIFile(filename: "/data/download/cmake/cmake-master/Utilities/cmcurl/lib/getenv.c", directory: "/data/download/cmake/cmake-master/Utilities/cmcurl/lib")
!2 = !{}
!3 = !{!4, !11}
!4 = distinct !DISubprogram(name: "curl_getenv", scope: !1, file: !1, line: 51, type: !5, isLocal: false, isDefinition: true, scopeLine: 52, flags: DIFlagPrototyped, isOptimized: false, variables: !2)
!5 = !DISubroutineType(types: !6)
!6 = !{!7, !9}
!7 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !8, size: 64, align: 64)
!8 = !DIBasicType(name: "char", size: 8, align: 8, encoding: DW_ATE_signed_char)
!9 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !10, size: 64, align: 64)
!10 = !DIDerivedType(tag: DW_TAG_const_type, baseType: !8)
!11 = distinct !DISubprogram(name: "GetEnv", scope: !1, file: !1, line: 31, type: !5, isLocal: true, isDefinition: true, scopeLine: 32, flags: DIFlagPrototyped, isOptimized: false, variables: !2)
!12 = !{i32 2, !"Dwarf Version", i32 4}
!13 = !{i32 2, !"Debug Info Version", i32 3}
!14 = !{!"clang version 3.8.0 (tags/RELEASE_380/final)"}
!15 = !DILocalVariable(name: "v", arg: 1, scope: !4, file: !1, line: 51, type: !9)
!16 = !DIExpression()
!17 = !DILocation(line: 51, column: 31, scope: !4)
!18 = !DILocation(line: 53, column: 17, scope: !4)
!19 = !DILocation(line: 53, column: 10, scope: !4)
!20 = !DILocation(line: 53, column: 3, scope: !4)
!21 = !DILocalVariable(name: "variable", arg: 1, scope: !11, file: !1, line: 31, type: !9)
!22 = !DILocation(line: 31, column: 26, scope: !11)
!23 = !DILocalVariable(name: "env", scope: !11, file: !1, line: 45, type: !7)
!24 = !DILocation(line: 45, column: 9, scope: !11)
!25 = !DILocation(line: 45, column: 22, scope: !11)
!26 = !DILocation(line: 45, column: 15, scope: !11)
!27 = !DILocation(line: 46, column: 11, scope: !11)
!28 = !DILocation(line: 46, column: 15, scope: !11)
!29 = !DILocation(line: 46, column: 18, scope: !30)
!30 = !DILexicalBlockFile(scope: !11, file: !1, discriminator: 1)
!31 = !DILocation(line: 46, column: 10, scope: !30)
!32 = !DILocation(line: 46, column: 26, scope: !33)
!33 = !DILexicalBlockFile(scope: !11, file: !1, discriminator: 2)
!34 = !DILocation(line: 46, column: 10, scope: !33)
!35 = !DILocation(line: 46, column: 10, scope: !36)
!36 = !DILexicalBlockFile(scope: !11, file: !1, discriminator: 3)
!37 = !DILocation(line: 46, column: 10, scope: !38)
!38 = !DILexicalBlockFile(scope: !11, file: !1, discriminator: 4)
!39 = !DILocation(line: 46, column: 3, scope: !38)
